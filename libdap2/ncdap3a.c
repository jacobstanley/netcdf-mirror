/*********************************************************************
 *   Copyright 1993, UCAR/Unidata
 *   See netcdf/COPYRIGHT file for copying and redistribution conditions.
 *********************************************************************/

#include "ncdap3.h"
#include "nc3dispatch.h"
#include "ncd3dispatch.h"
#include "dapalign.h"
#include "dapdump.h"
#include "oc.h"

#define getncid(drno) (((NC*)drno)->ext_ncid)

/*Forward*/
static NCerror getseqdimsize(NCDAPCOMMON*, CDFnode* seq, size_t* sizep);
static int fieldindex(CDFnode* parent, CDFnode* child);
static NCerror countsequence(NCDAPCOMMON*, CDFnode* node, size_t*);
static NCerror makeseqdim(NCDAPCOMMON*, CDFnode* node, size_t, CDFnode**);
static NCerror computeminconstraints3(NCDAPCOMMON*,CDFnode*,NCbytes*);

void
freegetvara(Getvara* vara)
{
    if(vara == NULL) return;
    dcefree((DCEnode*)vara->varaprojection);
    nullfree(vara);
}

NCerror
cleanNCDAPCOMMON(NCDAPCOMMON* dapcomm)
{
    /* abort the metadata file */
    (void)nc_abort(getncid(dapcomm));
    freenccache(dapcomm,dapcomm->cdf.cache);
    nclistfree(dapcomm->cdf.varnodes);
    nclistfree(dapcomm->cdf.seqnodes);
    nclistfree(dapcomm->cdf.gridnodes);
    nclistfree(dapcomm->cdf.usertypes);
    nullfree(dapcomm->cdf.recorddimname);

    /* free the trees */
    freecdfroot34(dapcomm->cdf.ddsroot);
    dapcomm->cdf.ddsroot = NULL;
    if(dapcomm->oc.ocdasroot != NULL)
        oc_root_free(dapcomm->oc.conn,dapcomm->oc.ocdasroot);
    dapcomm->oc.ocdasroot = NULL;
    oc_close(dapcomm->oc.conn); /* also reclaims remaining OC trees */
    nc_urifree(dapcomm->oc.url);
    nullfree(dapcomm->oc.urltext);
    nullfree(dapcomm->oc.rawurltext);

    dcefree((DCEnode*)dapcomm->oc.dapconstraint);
    dapcomm->oc.dapconstraint = NULL;

    return NC_NOERR;
}

#ifdef IGNORE
I think this dups a procedure in common34
/* Given a path, collect the set of dimensions along that path */
static void
collectdims3(NClist* path, NClist* dimset)
{
    int i,j;
    nclistclear(dimset);
    for(i=0;i<nclistlength(path);i++) {
	CDFnode* node = (CDFnode*)nclistget(path,i);
	if(node->nctype == NC_Sequence) {
	    CDFnode* sqdim = (CDFnode*)nclistget(node->array.dimensions,0);
	    if(DIMFLAG(sqdim,CDFDIMUNLIM))
		nclistclear(dimset); /* unlimited is always first */
        }
	for(j=0;j<nclistlength(node->array.dimensions);j++) {
	    CDFnode* dim = (CDFnode*)nclistget(node->array.dimensions,j);
	    nclistpush(dimset,(ncelem)dim);
	}
	if(node->array.stringdim != NULL) 
	    nclistpush(dimset,(ncelem)node->array.stringdim);
    }
}
#endif

NCerror
addstringdims(NCDAPCOMMON* dapcomm)
{
    /* for all variables of string type, we will need another dimension
       to represent the string; Accumulate the needed sizes and create
       the dimensions with a specific name: either as specified
       in DODS{...} attribute set or defaulting to the variable name.
       All such dimensions are global.
    */
    int i;
    NClist* varnodes = dapcomm->cdf.varnodes;
    NClist* stringdims = nclistnew();
    CDFnode* sdim = NULL;
    char dimname[4096];
    size_t dimsize;

    /* Start by creating the global string dimension */
    snprintf(dimname,sizeof(dimname),"maxStrlen%lu",
	    (unsigned long)dapcomm->cdf.defaultstringlength);
    sdim = makecdfnode34(dapcomm, dimname, OC_Dimension, OCNULL,
                                 dapcomm->cdf.ddsroot);
    nclistpush(dapcomm->cdf.ddsroot->tree->nodes,(ncelem)sdim);
    sdim->dim.dimflags |= CDFDIMSTRING;
    sdim->dim.declsize = dapcomm->cdf.defaultstringlength;
    sdim->dim.declsize0 = sdim->dim.declsize;
    sdim->dim.array = dapcomm->cdf.ddsroot;
    sdim->ncbasename = cdflegalname3(dimname);
    sdim->ncfullname = nulldup(sdim->ncbasename);
    dapcomm->cdf.globalstringdim = sdim;
    nclistpush(stringdims,(ncelem)sdim);

    for(i=0;i<nclistlength(varnodes);i++) {
	CDFnode* var = (CDFnode*)nclistget(varnodes,i);

	/* Does this node need a string dim? */
	if(var->etype != NC_STRING && var->etype != NC_URL) continue;

	dimsize = 0;
	if(var->dodsspecial.maxstrlen > 0)
	    dimsize = var->dodsspecial.maxstrlen;
	else
	    dimsize = var->maxstringlength;

	/* check is a variable-specific string length was specified */
	if(dimsize == 0) 
	    sdim = dapcomm->cdf.globalstringdim; /* use default */
	else {
	    /* create a psuedo dimension for the charification of the string*/
	    if(var->dodsspecial.dimname != NULL)
	        strncpy(dimname,var->dodsspecial.dimname,sizeof(dimname));
	    else
	        snprintf(dimname,sizeof(dimname),"maxStrlen%lu",
			 (unsigned long)dimsize);
	    sdim = makecdfnode34(dapcomm, dimname, OC_Dimension, OCNULL,
                                 dapcomm->cdf.ddsroot);
	    if(sdim == NULL) return THROW(NC_ENOMEM);
	    nclistpush(dapcomm->cdf.ddsroot->tree->nodes,(ncelem)sdim);
	    sdim->dim.dimflags |= CDFDIMSTRING;
	    sdim->dim.declsize = dimsize;
	    sdim->dim.array = var;
	    sdim->ncbasename = cdflegalname3(sdim->ocname);
	    sdim->ncfullname = nulldup(sdim->ncbasename);
	}
	/* tag the variable with its string dimension*/
	var->array.stringdim = sdim;
    }
    return NC_NOERR;
}

NCerror
defrecorddim3(NCDAPCOMMON* dapcomm)
{
    unsigned int i;
    NCerror ncstat = NC_NOERR;
    NClist* basedims;

    ASSERT((dapcomm->cdf.recorddimname != NULL
	    && nclistlength(dapcomm->cdf.seqnodes) == 0));

    /* Locate the base dimension matching the record dim */
    basedims = dapcomm->cdf.dimnodes;
    for(i=0;i<nclistlength(basedims);i++) {
        CDFnode* dim = (CDFnode*)nclistget(basedims,i);
	if(strcmp(dim->ocname,dapcomm->cdf.recorddimname) != 0) continue;
        DIMFLAGSET(dim,CDFDIMRECORD);
	dapcomm->cdf.recorddim = dim;
	break;
    }

#ifdef IGNORE
    /* Now, locate all the string dims and see if they are the record dim,
       then replace */
    if(dapcomm->cdf.unlimited != NULL) {
	CDFnode* unlim = dapcomm->cdf.unlimited;
        for(i=0;i<nclistlength(dapcomm->cdf.varnodes);i++) {
            CDFnode* var = (CDFnode*)nclistget(dapcomm->cdf.varnodes,i);
	    CDFnode* sdim = var->array.stringdim;
            if(sdim == NULL) continue;
	    if(strcmp(sdim->ncfullname,unlim->ncfullname)==0
	       && sdim->dim.declsize == unlim->dim.declsize) {
	        var->array.stringdim = unlim;
	        nclistpop(var->array.dimsetplus);
	        nclistpush(var->array.dimsetplus,(ncelem)dapcomm->cdf.unlimited);
	        nclistpop(var->array.dimsetall);
	        nclistpush(var->array.dimsetall,(ncelem)dapcomm->cdf.unlimited);
	    }
	}
    }
#endif

    return ncstat;
}

NCerror
defseqdims(NCDAPCOMMON* dapcomm)
{
    unsigned int i;
    NCerror ncstat = NC_NOERR;
    int seqdims = 1; /* default is to compute seq dims counts */

    /* Does the user want to see which dims are sequence dims? */
    if(paramcheck34(dapcomm,"show","seqdims")) seqdims = 0;
  
    /* Compute and define pseudo dimensions for all sequences */

    for(i=0;i<nclistlength(dapcomm->cdf.seqnodes);i++) {
        CDFnode* seq = (CDFnode*)nclistget(dapcomm->cdf.seqnodes,i);
	size_t seqsize;
	CDFnode* sqdim = NULL;

	/* Does the user want us to compute the sequence dim size? */
	if(seqdims) {
	    ncstat = getseqdimsize(dapcomm,seq,&seqsize);
	    if(ncstat != NC_NOERR) {
                /* Cannot read sequence; mark as unusable */
	        seq->usesequence = 0;
	    }
	} else { /* !seqdims default to size = 1 */
	    seqsize = 1; 
	}
	if(seq->usesequence) {
	    /* Note: we are making the dimension in the dds root tree */
            ncstat = makeseqdim(dapcomm,seq,seqsize,&sqdim);
            if(ncstat) goto fail;
	}
        seq->array.seqdim = sqdim;
    }

fail:
    return ncstat;
}

static NCerror
getseqdimsize(NCDAPCOMMON* dapcomm, CDFnode* seq, size_t* sizep)
{
    NCerror ncstat = NC_NOERR;
    OCerror ocstat = OC_NOERR;
    OCconnection conn = dapcomm->oc.conn;
    OCdata rootcontent = OCNULL;
    OCobject ocroot;
    CDFnode* dxdroot;
    CDFnode* xseq;
    NCbytes* minconstraints = ncbytesnew();
    size_t seqsize;

    /* Read the minimal amount of data in order to get the count */
    /* If the url is unconstrainable, then get the whole thing */
    computeminconstraints3(dapcomm,seq,minconstraints);
#ifdef DEBUG
fprintf(stderr,"minconstraints: %s\n",ncbytescontents(minconstraints));
#endif
    /* Obtain the record counts for the sequence */
    if(FLAGSET(dapcomm->controls,NCF_UNCONSTRAINABLE))
        ocstat = dap_fetch(dapcomm,conn,NULL,OCDATADDS,&ocroot);
    else
        ocstat = dap_fetch(dapcomm,conn,ncbytescontents(minconstraints),OCDATADDS,&ocroot);
    if(ocstat) goto fail;
    ncstat = buildcdftree34(dapcomm,ocroot,OCDATA,&dxdroot);
    if(ncstat) goto fail;	
    /* attach DATADDS to DDS */
    ncstat = attach34(dxdroot,seq);
    if(ncstat) goto fail;	
    /* WARNING: we are now switching to datadds tree */
    xseq = seq->attachment;
    ncstat = countsequence(dapcomm,xseq,&seqsize);
    if(ncstat) goto fail;
#ifdef DEBUG
fprintf(stderr,"sequencesize: %s = %lu\n",seq->ocname,(unsigned long)seqsize);
#endif
    /* throw away the fetch'd trees */
    unattach34(dapcomm->cdf.ddsroot);
    freecdfroot34(dxdroot);
    if(ncstat != NC_NOERR) {
        /* Cannot get DATADDDS*/
	char* code;
	char* msg;
	long httperr;
	oc_svcerrordata(dapcomm->oc.conn,&code,&msg,&httperr);
	if(code != NULL) {
	    nclog(NCLOGERR,"oc_fetch_datadds failed: %s %s %l",
			code,msg,httperr);
	}
	ocstat = OC_NOERR;
    }		
    if(sizep) *sizep = seqsize;

fail:
    ncbytesfree(minconstraints);
    oc_data_free(conn,rootcontent);
    if(ocstat) ncstat = ocerrtoncerr(ocstat);
    return ncstat;
}

static NCerror
makeseqdim(NCDAPCOMMON* dapcomm, CDFnode* seq, size_t count, CDFnode** sqdimp)
{
    CDFnode* sqdim;
    CDFnode* root = seq->root;
    CDFtree* tree = root->tree;

    /* build the dimension with given size; keep the dimension anonymous */
    sqdim = makecdfnode34(dapcomm,seq->ocname,OC_Dimension,OCNULL,root);
    if(sqdim == NULL) return THROW(NC_ENOMEM);
    nclistpush(tree->nodes,(ncelem)sqdim);
    /* Assign a name to the sequence node */
    sqdim->ncbasename = cdflegalname3(seq->ocname);
    sqdim->ncfullname = nulldup(sqdim->ncbasename);
    DIMFLAGSET(sqdim,CDFDIMSEQ);
    sqdim->dim.declsize = count;
    sqdim->dim.declsize0 = count;
    sqdim->dim.array = seq;
    sqdim->dim.index1 = 1;    
    if(sqdimp) *sqdimp = sqdim;
    return NC_NOERR;
}

static NCerror
countsequence(NCDAPCOMMON* dapcomm, CDFnode* xseq, size_t* sizep)
{
    unsigned int i;
    NClist* path = nclistnew();
    OCdata parent = OCNULL;
    OCdata child = OCNULL;
    OCdata tmp;
    CDFnode* prev = NULL;
    int index;
    OCerror ocstat = OC_NOERR;
    NCerror ncstat = NC_NOERR;
    OCconnection conn = dapcomm->oc.conn;
    size_t recordcount;
    CDFnode* xroot;

    ASSERT((xseq->nctype == NC_Sequence));

    parent = oc_data_new(conn);
    child = oc_data_new(conn);

    collectnodepath3(xseq,path,WITHDATASET);

    prev = (CDFnode*)nclistget(path,0);
    ASSERT((prev->nctype == NC_Dataset));

    xroot = xseq->root;
    ocstat = oc_data_root(conn,xroot->tree->ocroot,parent);
    if(ocstat) goto fail;

    for(i=1;i<nclistlength(path);i++) {
	xseq = (CDFnode*)nclistget(path,i);
	index = fieldindex(prev,xseq);
	ocstat = oc_data_ith(conn,parent,index,child);
	if(ocstat) goto fail;
	prev = xseq;
	/* swap the content markers */
	tmp = parent;
	parent = child;
	child = tmp;
    }
    oc_data_count(conn,parent,&recordcount);
    if(sizep) *sizep = recordcount;

fail:
    nclistfree(path);
    if(ocstat) ncstat = ocerrtoncerr(ocstat);
    oc_data_free(conn,parent);
    oc_data_free(conn,child);
    return ncstat;
}

static int
fieldindex(CDFnode* parent, CDFnode* child)
{
    unsigned int i;
    for(i=0;i<nclistlength(parent->subnodes);i++) {
	CDFnode* node = (CDFnode*)nclistget(parent->subnodes,i);
	if(node == child) return i;
    }
    return -1;
}

NCerror
showprojection3(NCDAPCOMMON* dapcomm, CDFnode* var)
{
    int i,rank;
    NCerror ncstat = NC_NOERR;
    NCbytes* projection = ncbytesnew();
    NClist* path = nclistnew();
    NC* drno = dapcomm->controller;

    /* Collect the set of DDS node name forming the xpath */
    collectnodepath3(var,path,WITHOUTDATASET);
    for(i=0;i<nclistlength(path);i++) {
        CDFnode* node = (CDFnode*)nclistget(path,i);
	if(i > 0) ncbytescat(projection,".");
	ncbytescat(projection,node->ocname);
    }
    /* Now, add the dimension info */
    rank = nclistlength(var->array.dimset0);
    for(i=0;i<rank;i++) {
	CDFnode* dim = (CDFnode*)nclistget(var->array.dimset0,i);
	char tmp[32];
	ncbytescat(projection,"[");
	snprintf(tmp,sizeof(tmp),"%lu",(unsigned long)dim->dim.declsize);
	ncbytescat(projection,tmp);
	ncbytescat(projection,"]");
    }    
    /* Define the attribute */
    ncstat = nc_put_att_text(getncid(drno),var->ncid,
                               "_projection",
		               ncbyteslength(projection),
			       ncbytescontents(projection));
    return ncstat;
}

#ifdef IGNORE
NCerror
detachdatadds3(NCDAPCOMMON* dapcomm)
{
    int i;
    for(i=0;i<nclistlength(dapcomm->cdf.dds->tree.nodes);i++) {
	CDFnode* node = (CDFnode*)nclistget(dapcomm->cdf.dds->tree.nodes,i);
	node->active = 0;
	node->dim.datasize = node->dim.declsize;
   }
   return NC_NOERR;
}

NCerror
attachdatadds3(NCDAPCOMMON* dapcomm)
{
    int i;
    NClist* cdfnodes = dapcomm->cdf.dds->tree.nodes;
    for(i=0;i<nclistlength(cdfnodes);i++) {
	CDFnode* node = (CDFnode*)nclistget(cdfnodes,i);
	OCobject dds = node->dds;
	if(dds == OCNULL) continue;
	node->active = oc_datadds_active(dapcomm->oc.conn,dds);
	if(node->nctype == NC_Dimension) {
	    oc_datadds_dimsize(dapcomm->oc.conn,node->dds,&node->dim.datasize);
	}
    }
    return NC_NOERR;
}
#endif

/*
This is more complex than one might think. We want to find
a path to a variable inside the given node so that we can
ask for a single instance of that variable to minimize the
amount of data we retrieve. However, we want to avoid passing
through any nested sequence. This is possible because of the way
that sequencecheck() works.
TODO: some servers will not accept an unconstrained fetch, so
make sure we always have a constraint.
*/

static NCerror
computeminconstraints3(NCDAPCOMMON* dapcomm, CDFnode* seq, NCbytes* minconstraints)
{
    NClist* path = nclistnew();
    CDFnode* var;
    CDFnode* candidate;
    unsigned int i,j,ndims;
    char* prefix;

    /* Locate a variable that is inside this sequence */
    /* Preferably one that is a numeric type*/
    for(candidate=NULL,var=NULL,i=0;i<nclistlength(dapcomm->cdf.varnodes);i++){
        CDFnode* node = (CDFnode*)nclistget(dapcomm->cdf.varnodes,i);
	if(node->array.sequence == seq) {
	    if(node->nctype == NC_Primitive) {
		switch(node->etype) {
		case NC_BYTE: case NC_SHORT: case NC_INT:
		case NC_FLOAT: case NC_DOUBLE:
		case NC_UBYTE: case NC_USHORT: case NC_UINT:
		case NC_INT64: case NC_UINT64:
		    if(var == NULL) {
			var = node; /* good choice */
		    }
		    break;
		case NC_CHAR: case NC_STRING:
		default:
		    candidate = node; /* usable */
		    break;
		}
	    }
	}
    }
    if(var == NULL && candidate != NULL) var = candidate;
    else if(var == NULL) return THROW(NC_EINVAL);

    /* collect seq path prefix */
    prefix = makecdfpathstring3(seq->container,".");
    ncbytescat(minconstraints,prefix);
    if(strlen(prefix) > 0) ncbytescat(minconstraints,".");

    /* Compute a short path from the var back to and including
       the sequence
    */
    collectnodepath3(var,path,WITHOUTDATASET);
    while(nclistlength(path) > 0) {
	CDFnode* node = (CDFnode*)nclistget(path,0);
	if(node == seq) break;
	nclistremove(path,0);
    }
    ASSERT((nclistlength(path) > 0));

    /* construct the projection path using minimal index values */
    for(i=0;i<nclistlength(path);i++) {
	CDFnode* node = (CDFnode*)nclistget(path,i);
	if(i > 0) ncbytescat(minconstraints,".");
	ncbytescat(minconstraints,node->ocname);
	if(node == seq) {
	    /* Use the limit */
	    if(node->sequencelimit > 0) {
		char tmp[64];
		snprintf(tmp,sizeof(tmp),"[0:%lu]",
		         (unsigned long)(node->sequencelimit - 1));
		ncbytescat(minconstraints,tmp);
	    }
	} else if(nclistlength(node->array.dimset0) > 0) {
	    ndims = nclistlength(node->array.dimset0);
	    for(j=0;j<ndims;j++) {
		CDFnode* dim = (CDFnode*)nclistget(node->array.dimset0,j);
		if(dim->dim.dimflags & CDFDIMSTRING) {
		    ASSERT((j == (ndims - 1)));
		    break;
		}
		ncbytescat(minconstraints,"[0]");
	    }
	}
    }
    nclistfree(path);
    /* Finally, add in any selection from the original URL */
    if(dapcomm->oc.url->selection != NULL)
        ncbytescat(minconstraints,dapcomm->oc.url->selection);
    nullfree(prefix);
    return NC_NOERR;
}

static unsigned long
cdftotalsize3(NClist* dimensions)
{
    unsigned int i;
    unsigned long total = 1;
    if(dimensions != NULL) {
	for(i=0;i<nclistlength(dimensions);i++) {
	    CDFnode* dim = (CDFnode*)nclistget(dimensions,i);
	    total *= dim->dim.declsize;
	}
    }
    return total;
}

/* Estimate variables sizes and then resort the variable list
   by that size
*/
void
estimatevarsizes3(NCDAPCOMMON* dapcomm)
{
    int ivar;
    unsigned int rank;
    size_t totalsize = 0;

    for(ivar=0;ivar<nclistlength(dapcomm->cdf.varnodes);ivar++) {
        CDFnode* var = (CDFnode*)nclistget(dapcomm->cdf.varnodes,ivar);
	NClist* ncdims = var->array.dimset0;
	rank = nclistlength(ncdims);
	if(rank == 0) { /* use instance size of the type */
	    var->estimatedsize = nctypesizeof(var->etype);
#ifdef DEBUG1
fprintf(stderr,"scalar %s.estimatedsize = %lu\n",
	makecdfpathstring3(var,"."),var->estimatedsize);
#endif
	} else {
	    unsigned long size = cdftotalsize3(ncdims);
	    size *= nctypesizeof(var->etype);
#ifdef DEBUG1
fprintf(stderr,"array %s(%u).estimatedsize = %lu\n",
	makecdfpathstring3(var,"."),rank,size);
#endif
	    var->estimatedsize = size;
	}
	totalsize += var->estimatedsize;
    }
#ifdef DEBUG1
fprintf(stderr,"total estimatedsize = %lu\n",totalsize);
#endif
    dapcomm->cdf.totalestimatedsize = totalsize;
}

NCerror
fetchtemplatemetadata3(NCDAPCOMMON* dapcomm)
{
    NCerror ncstat = NC_NOERR;
    OCerror ocstat = OC_NOERR;
    OCobject ocroot = OCNULL;
    CDFnode* ddsroot = NULL;
    char* ce = NULL;

    /* Temporary hack: we need to get the selection string
       from the url
    */
    /* Get (almost) unconstrained DDS; In order to handle functions
       correctly, those selections must always be included
    */
    if(FLAGSET(dapcomm->controls,NCF_UNCONSTRAINABLE))
	ce = NULL;
    else
        ce = nulldup(dapcomm->oc.url->selection);

    /* Get selection constrained DDS */
    ocstat = dap_fetch(dapcomm,dapcomm->oc.conn,ce,OCDDS,&ocroot);
    if(ocstat != OC_NOERR) {
	/* Special Hack. If the protocol is file, then see if
           we can get the dds from the .dods file
        */
	if(strcmp(dapcomm->oc.url->protocol,"file") != 0) {
	    THROWCHK(ocstat); goto done;
	}
	/* Fetch the data dds */
        ocstat = dap_fetch(dapcomm,dapcomm->oc.conn,ce,OCDATADDS,&ocroot);
        if(ocstat != OC_NOERR) {
	    THROWCHK(ocstat); goto done;
	}
	/* Note what we did */
	nclog(NCLOGWARN,"Cannot locate .dds file, using .dods file");
    }

    /* Get selection constrained DAS */
    ocstat = dap_fetch(dapcomm,dapcomm->oc.conn,ce,OCDAS,&dapcomm->oc.ocdasroot);
    if(ocstat != OC_NOERR) {
	/* Ignore but complain */
	nclog(NCLOGWARN,"Could not read DAS; ignored");
        dapcomm->oc.ocdasroot = OCNULL;	
	ocstat = OC_NOERR;
    }

    /* Construct our parallel dds tree */
    ncstat = buildcdftree34(dapcomm,ocroot,OCDDS,&ddsroot);
    if(ncstat != NC_NOERR) {THROWCHK(ncstat); goto done;}
    dapcomm->cdf.fullddsroot = ddsroot;

#ifdef NOTUSED
    /* Combine DDS and DAS */
    ncstat = dapmerge3(dapcomm,ddsroot,dapcomm->oc.ocdasroot);
    if(ncstat != NC_NOERR) {THROWCHK(ncstat); goto done;}
#endif

done:
    nullfree(ce);
    if(ocstat != OC_NOERR) ncstat = ocerrtoncerr(ocstat);
    return ncstat;
}

NCerror
fetchconstrainedmetadata3(NCDAPCOMMON* dapcomm)
{
    NCerror ncstat = NC_NOERR;
    OCerror ocstat = OC_NOERR;
    OCobject ocroot;
    CDFnode* ddsroot; /* constrained */
    char* ce = NULL;

    if(FLAGSET(dapcomm->controls,NCF_UNCONSTRAINABLE))
	ce = NULL;
    else
        ce = buildconstraintstring3(dapcomm->oc.dapconstraint);

#ifdef NOTUSED
    if(ce == NULL || strlen(ce) == 0) {
	/* no need to get the dds again; just imprint on self */
        ncstat = imprintself3(dapcomm->cdf.ddsroot);
        if(ncstat) goto fail;
    } else
#endif
    {
        ocstat = dap_fetch(dapcomm,dapcomm->oc.conn,ce,OCDDS,&ocroot);
        if(ocstat != OC_NOERR) {THROWCHK(ocstat); goto fail;}

        /* Construct our parallel dds tree; including attributes*/
        ncstat = buildcdftree34(dapcomm,ocroot,OCDDS,&ddsroot);
        if(ncstat) goto fail;

	dapcomm->cdf.ddsroot = ddsroot;

        if(!FLAGSET(dapcomm->controls,NCF_UNCONSTRAINABLE)) {
            /* fix DAP server problem by adding back any missing grid structure nodes */
            ncstat = regrid3(ddsroot,dapcomm->cdf.fullddsroot,dapcomm->oc.dapconstraint->projections);    
            if(ncstat) goto fail;
	}

#ifdef DEBUG
fprintf(stderr,"constrained:\n%s",dumptree(ddsroot));
#endif

        /* Combine DDS and DAS */
	if(dapcomm->oc.ocdasroot != NULL) {
            ncstat = dapmerge3(dapcomm,ddsroot,dapcomm->oc.ocdasroot);
            if(ncstat != NC_NOERR) {THROWCHK(ncstat); goto fail;}
	}

        /* map the constrained DDS to the unconstrained DDS */
        ncstat = mapnodes3(ddsroot,dapcomm->cdf.fullddsroot);
        if(ncstat) goto fail;

    }

fail:
    nullfree(ce);
    if(ocstat != OC_NOERR) ncstat = ocerrtoncerr(ocstat);
    return ncstat;
}

/* Suppress variables not in usable sequences*/
NCerror
suppressunusablevars3(NCDAPCOMMON* dapcomm)
{
    int i,j;
    int found = 1;
    NClist* path = nclistnew();

    while(found) {
	found = 0;
	/* Walk backwards to aid removal semantics */
	for(i=nclistlength(dapcomm->cdf.varnodes)-1;i>=0;i--) {
	    CDFnode* var = (CDFnode*)nclistget(dapcomm->cdf.varnodes,i);
	    /* See if this var is under an unusable sequence */
	    nclistclear(path);
	    collectnodepath3(var,path,WITHOUTDATASET);
	    for(j=0;j<nclistlength(path);j++) {
		CDFnode* node = (CDFnode*)nclistget(path,j);
		if(node->nctype == NC_Sequence
		   && !node->usesequence) {
#ifdef DEBUG
fprintf(stderr,"suppressing var in unusable sequence: %s.%s\n",node->ncfullname,var->ncbasename);
#endif
		    found = 1;
		    break;
		}
	    }
	    if(found) break;
	}
        if(found) nclistremove(dapcomm->cdf.varnodes,i);
    }
    nclistfree(path);
    return NC_NOERR;
}


/*
For variables which have a zero size dimension,
make them invisible.
*/
NCerror
fixzerodims3(NCDAPCOMMON* dapcomm)
{
    int i,j;
    for(i=0;i<nclistlength(dapcomm->cdf.varnodes);i++) {
	CDFnode* var = (CDFnode*)nclistget(dapcomm->cdf.varnodes,i);
        NClist* ncdims = var->array.dimsetplus;
	if(nclistlength(ncdims) == 0) continue;
        for(j=0;j<nclistlength(ncdims);j++) {
	    CDFnode* dim = (CDFnode*)nclistget(ncdims,j);
	    if(dim->dim.declsize == 0) {
	 	/* make node invisible */
		var->visible = 0;
		var->zerodim = 1;
	    }
	}
    }
    return NC_NOERR;
}

void
applyclientparamcontrols3(NCDAPCOMMON* dapcomm)
{
    /* enable/disable caching */
    if(paramcheck34(dapcomm,"cache",NULL))
	SETFLAG(dapcomm->controls,NCF_CACHE);
    else
	SETFLAG(dapcomm->controls,DFALTCACHEFLAG);

    if(FLAGSET(dapcomm->controls,NCF_UNCONSTRAINABLE))
	SETFLAG(dapcomm->controls,NCF_CACHE);

    nclog(NCLOGNOTE,"Caching=%d",FLAGSET(dapcomm->controls,NCF_CACHE));

    if(paramcheck34(dapcomm,"show","fetch"))
	SETFLAG(dapcomm->controls,NCF_SHOWFETCH);

    SETFLAG(dapcomm->controls,(NCF_NC3|NCF_NCDAP));

}
