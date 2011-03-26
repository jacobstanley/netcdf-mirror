/*********************************************************************
 *   Copyright 2010, UCAR/Unidata
 *   See netcdf/COPYRIGHT file for copying and redistribution conditions.
 *   $Id$
 *   $Header$
 *********************************************************************/

#include "config.h"

#include <curl/curl.h>
#include "curlwrap.h"

#include "netcdf.h"
#include "nc.h"
#include "nc4internal.h"
#include "nclist.h"
#include "ncaux.h"

#include "nccr.h"
#include "crdebug.h"
#include "ast.h"

#include "ncstreamx.h"

/*Forward*/
static int crpredefinedtypes(NCCR*,nc_type);
static char* crtypename(char*);
static int crbbasetype(nc_type, char*, nc_type, int ndims, Dimension**, nc_type*);
static int crdeffieldvar(nc_type, int tag, Variable*);
static int crdeffieldstruct(nc_type, int tag, Structure*);
static int crfillgroup(NCCR*, Group*, nc_type);
static nc_type cvtstreamtonc(DataType);
static enum Dimcase classifydim(Dimension*);
static int dimsize(Dimension*);
static int dimsizes(int ndims, Dimension**, int sizes[NC_MAX_VAR_DIMS]);
static int validate_dimensions(size_t ndims, Dimension**, int nounlim);
static int buildfield(int ncid,void* cmpd,char*,nc_type,int ndims,Dimension**);
static int buildvlenchain(int ncid,char*,nc_type,int ndims,Dimension**,int index,nc_type* vidp);
static int locateleftvlen(int ndims, Dimension**, int index);


enum Dimcase {DC_UNKNOWN, DC_FIXED, DC_UNLIMITED, DC_VLEN, DC_PRIVATE};

static int uid = 0;

/*
Fetch the metadata and define in the temporary netcdf-4 file
*/
int
nccr_buildnc(NCCR* nccr, Header* hdr)
{
    int ncstat = NC_NOERR;
    nc_type ncid = nccr->info.ext_ncid; /*root id*/

    ncstat = crpredefinedtypes(nccr,ncid);
    if(ncstat != NC_NOERR) {THROWCHK(ncstat); goto done;}

    ncstat = crfillgroup(nccr, hdr->root, ncid);
    if(ncstat != NC_NOERR) {THROWCHK(ncstat); goto done;}

#ifdef IGNORE
    ncstat = crbuilddims(cdmr,hdr);
    if(ncstat != NC_NOERR) {THROWCHK(ncstat); goto done;}
    ncstat = crbuildtypes(cdmr);
    if(ncstat != NC_NOERR) {THROWCHK(ncstat); goto done;}
    ncstat = crbuildvars(cdmr);
    if(ncstat != NC_NOERR) {THROWCHK(ncstat); goto done;}
    ncstat = crbuildglobalattrs(cdmr,getncid(cdmr),dds);
    if(ncstat != NC_NOERR) {THROWCHK(ncstat); goto done;}
#endif

done:
    return THROW(ncstat);
}

/* Define needed predefine types in root */
static int
crpredefinedtypes(NCCR* nccr, nc_type ncid)
{
    int ncstat = NC_NOERR;
    nc_type tid;

    /* NC_UBYTE(*) bytes_t */
    ncstat = nc_def_vlen(ncid,"bytes_t",NC_UBYTE,&tid);
    if(ncstat != NC_NOERR) goto done;

done:
    return ncstat;
}

static char*
crtypename(char* name)
{
    static char tname[NC_MAX_NAME];
    strncpy(tname,name,NC_MAX_NAME-2);
    strncat(tname,"_t",NC_MAX_NAME-2);
    tname[NC_MAX_NAME-1] = '\0';
    return tname; /* Naughty Naughty */
}


/* Use for var fields or top level vars.
   Returns the basetype to use for defining
   field or var. Assumes v's dimensions have been
   validated.
*/
static int
crbbasetype(nc_type grpid, char* name, nc_type basetype,
		int ndims, Dimension** dims,
		nc_type* newbasetype)
{
    int ncstat = NC_NOERR;
    int dimsize[NC_MAX_VAR_DIMS];	        		
    int index;
	
    *newbasetype = basetype;

    if(ndims == 0) goto done;

    /* Locate the first * dimension */
    index = locateleftvlen(ndims,dims,0);

    if(index > 0) {
	/* Ok, we have to build up the vlen/struct chain to handle * dimensions */
	ncstat = buildvlenchain(grpid,name,basetype,ndims,dims,index,newbasetype);
	if(ncstat != NC_NOERR) goto done;	
    }

done:
    return ncstat;
}

static int
crdeffieldvar(nc_type grpid, int tag, Variable* v)
{
    int ncstat = NC_NOERR;
    nc_type basetype = nctypefor(v->dataType);
    int index,i;
    int ndims = v->shape.count;
    Dimension** dims = v->shape.values;

    if(ndims == 0) {
        ncstat = nc_add_field(tag,v->name,basetype,0,NULL);
        if(ncstat != NC_NOERR) goto done;	
    } else {
	int dimsizes[NC_MAX_VAR_DIMS];
	/* Validate the set of dimensions for a field */
	if(!validate_dimensions(ndims,dims,1))
	    {ncstat = NC_EBADDIM; goto done;}

	/* Locate the first * dimension */
        index = locateleftvlen(ndims,dims,0);
	if(index > 0) {
	    /* Get the true basetype */
	    ncstat = crbbasetype(grpid, v->name, basetype,ndims,dims,&basetype);
            if(ncstat != NC_NOERR) goto done;
	}
        for(i=0;i<index;i++) {
	    dimsizes[i] = dimsize(dims[i]);
        }
        ncstat = nc_add_field(tag,v->name,basetype,index,dimsizes);	
        if(ncstat != NC_NOERR) goto done;	
    }

done:
    return ncstat;
}

static int
crdeffieldstruct(nc_type grpid, int tag, Structure* s)
{
    int ncstat = NC_NOERR;
    nc_type basetype = s->notes.ncid;
    int index,i;
    int ndims = s->shape.count;
    Dimension** dims = s->shape.values;

    if(ndims == 0) {
        ncstat = nc_add_field(tag,s->name,basetype,0,NULL);
        if(ncstat != NC_NOERR) goto done;	
    } else {
	int dimsizes[NC_MAX_VAR_DIMS];
	/* Validate the set of dimensions for a field */
	if(!validate_dimensions(ndims,s->shape.values,1))
	    {ncstat = NC_EBADDIM; goto done;}

	/* Locate the first * dimension */
	index = locateleftvlen(ndims,dims,0);
	if(index > 0) {
	    /* Get the true basetype */
	    ncstat = crbbasetype(grpid, s->name, basetype, ndims, dims, &basetype);
	    if(ncstat != NC_NOERR) goto done;	
	}
	/* Now define the simple case for the non-star leading dimensions */
        for(i=0;i<index;i++) {
	    dimsizes[i] = dimsize(dims[i]);
        }
        ncstat = nc_add_field(tag,s->name,basetype,index,dimsizes);	
        if(ncstat != NC_NOERR) goto done;	
    }

done:
    return ncstat;
}

/* Actual group is created by caller */
static int
crfillgroup(NCCR* nccr, Group* grp, nc_type grpid)
{
    int ncstat = NC_NOERR;
    size_t i,j,k;
    
    /* Create the dimensions */
    for(i=0;i<grp->dims.count;i++) {
	Dimension* dim = grp->dims.values[i];
	if(dim->name.defined) {
	    size_t length = (dim->length.defined?dim->length.value:1);
	    if(dim->isUnlimited.defined && dim->isUnlimited.value != 0)
		length = NC_UNLIMITED;
	    ncstat = nc_def_dim(grpid,dim->name.value, length, &dim->notes.ncid);
	    if(ncstat != NC_NOERR) goto done;
	}
    }

    /* Create the enum types */
    for(i=0;i<grp->enumTypes.count;i++) {
	EnumTypedef* en = grp->enumTypes.values[i];
	int enid;
	if(en->map.count == 0) continue;
	ncstat = nc_def_enum(grpid,NC_INT,crtypename(en->name),&en->notes.ncid);
	if(ncstat != NC_NOERR) goto done;
        for(j=0;j<en->map.count;i++) {
	    EnumType* econst = en->map.values[i];
	    ncstat = nc_insert_enum(grpid,en->notes.ncid,econst->value,&econst->code);
   	    if(ncstat != NC_NOERR) goto done;	
	}
    }

    /* Create the structs (compound) types */
    /* Note: structs here are also variables */
    for(i=0;i<grp->structs.count;i++) {
	int tag;
	Structure* struc = grp->structs.values[i];
	ncstat = nc_begin_compound(grpid,crtypename(struc->name),&tag);
	if(ncstat != NC_NOERR) goto done;	
	/* Define the non-structure type fields */
	for(j=0;j<struc->vars.count;j++) {
	    Variable* v = struc->vars.values[i];
	    ncstat = crdeffieldvar(grpid,tag,v);
	    if(ncstat != NC_NOERR) goto done;	
	}
	/* Define the structure type fields */
	for(j=0;j<struc->structs.count;j++) {
	    Structure* s = struc->structs.values[i];
	    ncstat = crdeffieldstruct(grpid,tag,s);
	    if(ncstat != NC_NOERR) goto done;	
	}
	ncstat = nc_end_compound(tag,&struc->notes.ncid);
    }

    /* Create the group global attributes */
    for(i=0;i<grp->atts.count;i++) {
	Attribute* att = grp->atts.values[i];
	if(att->data.defined) {
	    ncstat = nc_put_att(grpid,NC_GLOBAL,att->name,
				cvtstreamtonc(att->type),
				att->len,
				att->data.value.bytes);
	} else {
	    switch (att->type) {
	    case STRING: {
	        ncstat = nc_put_att(grpid,NC_GLOBAL,att->name,
				cvtstreamtonc(att->type),
				att->sdata.count,
				att->sdata.values);
		} break;
	    case OPAQUE:
	    default: abort();
	    }
	}
        if(ncstat != NC_NOERR) goto done;
    }

    /* Create the group non-struct variables */
    for(i=0;i<grp->vars.count;i++) {
        Variable* v = grp->vars.values[i];
	int ndims = v->shape.count;
	Dimension** dims = v->shape.values;
	nc_type basetype = cvtstreamtonc(v->dataType);

	/* Validate as non-field */
	if(!validate_dimensions(ndims,dims,0))
	    {ncstat = NC_EBADDIM; goto done;}

	if(ndims == 0) {
            ncstat = nc_def_var(grpid,v->name,basetype,0,NULL,&v->notes.ncid);
	} else {
	    nc_type dimids[NC_MAX_VAR_DIMS];
	    int index;
	    /* Get the proper basetype */
	    index = locateleftvlen(ndims,dims,0);
	    if(index > 0) {
	        ncstat = crbbasetype(grpid, v->name, basetype, ndims,
				dims,&basetype);
	        if(ncstat != NC_NOERR) goto done;	
	    }
	    for(j=0;j<index;j++) dimids[j] = dims[j]->notes.ncid;
            ncstat = nc_def_var(grpid,v->name,basetype,index,dimids,&v->notes.ncid);
	}
    }

    /* Create the group struct variables */
    for(i=0;i<grp->structs.count;i++) {
        Structure* s = grp->structs.values[i];
	int ndims = s->shape.count;
	Dimension** dims = s->shape.values;
	nc_type basetype = s->notes.ncid;

	/* Validate as non-field */
	if(!validate_dimensions(ndims,dims,0))
	    {ncstat = NC_EBADDIM; goto done;}

	if(ndims == 0) {
            ncstat = nc_def_var(grpid,s->name,basetype,0,NULL,&s->notes.ncid);
	} else {
	    nc_type dimids[NC_MAX_VAR_DIMS];
	    int index;
	    /* Get the proper basetype */
	    index = locateleftvlen(ndims,dims,0);
	    if(index > 0) {
	        ncstat = crbbasetype(grpid, s->name, basetype, s->shape.count,
				s->shape.values,&basetype);
	        if(ncstat != NC_NOERR) goto done;	
	    }
	    for(j=0;j<index;j++) dimids[j] = dims[j]->notes.ncid;
            ncstat = nc_def_var(grpid,s->name,basetype,index,dimids,&s->notes.ncid);
	}
    }

done:
    return ncstat;
}

/***************************************************/

/* Map ncstream primitive datatypes to netcdf primitive datatypes */
static nc_type
cvtstreamtonc(DataType datatype)
{
    switch (datatype) {
    case CHAR: return NC_CHAR;
    case BYTE: return NC_BYTE;
    case SHORT: return NC_SHORT;
    case INT: return NC_INT;
    case INT64: return NC_INT64;
    case FLOAT: return NC_FLOAT;
    case DOUBLE: return NC_DOUBLE;
    case STRING: return NC_STRING;
    case UBYTE: return NC_UBYTE;
    case USHORT: return NC_USHORT;
    case UINT: return NC_UINT;
    case UINT64: return NC_UINT64;
    }
    return NC_NAT;
}


/* Classify a dimension */
static enum Dimcase
classifydim(Dimension* dim)
{
    int len=0, unlim=0, vlen=0, priv=0;
    if(dim->length.defined) len=(dim->length.value?1:0);
    if(dim->isUnlimited.defined) unlim=(dim->isUnlimited.value?1:0);
    if(dim->isVlen.defined) vlen=(dim->isVlen.value?1:0);
    if(dim->isPrivate.defined) priv=(dim->isPrivate.value?1:0);

    if(len+unlim+vlen+priv > 1) goto fail;
    if(len) return DC_FIXED;
    if(unlim) return DC_UNLIMITED;
    if(vlen) return DC_VLEN;
    if(priv) return DC_PRIVATE;

fail:
    return DC_UNKNOWN;
}


static int
dimsize(Dimension* dim)
{
    if(dim->isUnlimited.defined && dim->isUnlimited.value)
	return NC_UNLIMITED;
    if(dim->isVlen.defined && dim->isVlen.value)
	return -1;
    if(dim->length.defined)
	return dim->length.value;
    return -1;
}

static int
dimsizes(int ndims, Dimension** dims, int sizes[NC_MAX_VAR_DIMS])
{
    int i;
    if(ndims > NC_MAX_VAR_DIMS) return NC_EINVAL;
    for(i=0;i<ndims;i++) {
        sizes[i] = dimsize(dims[i]);
    }
    return NC_NOERR;
}


/* Validate that the set of dimensions can be translated */
static int
validate_dimensions(size_t ndims, Dimension** dims, int nounlim)
{
    int i,j;

    if(ndims == 0) return NC_NOERR;

    /* Validate the dimensions to check for
       non-translatable situations
	- UNLIMITED following a star
	- Any occurrence of Private
	- no occurrences of unlimited (if nounlim is set)
    */

    /* Look for untranslatable dimensions */
    for(i=0;i<ndims;i++) {
        Dimension* dim = dims[i];
	enum Dimcase dc = classify(dim);
	switch (dc) {
	case DC_FIXED: break;
	case DC_VLEN: break;
	case DC_UNLIMITED: if(nounlim) goto untranslatable; else break;
	default: goto untranslatable;
	}
    }

    /* Look for unlimited after vlen */
    for(i=0;i<ndims;i++) {
        Dimension* dim0 = dims[i];
	enum Dimcase dc = classify(dim0);
	if(dc != DC_VLEN) continue;
        for(j=i+1;j<ndims;j++) {
            Dimension* dim1 = dims[j];
	    dc = classify(dim1);	
	    if(dc == DC_UNLIMITED) goto untranslatable;
	}	   
    }    
    return NC_NOERR;

untranslatable:
    return NC_ETRANSLATION;
}


/**
Given a variable of the form
T v(d1,d2,d3,*,d4,*,d5)
We need to create the following compound and vlen types.
compound v_1 {T v(d5);
v_1(*) v_2;
compound v_2 {v_1 v(d4);}
v_2(*) v_3;

and then finally
v3 v(d1,d2,d3)

Handle special cases:
1. when last dim is a vlen

*/

static int
buildfield(int ncid,
	   void* cmpd,
	   char* name,
	   nc_type basetype,
	   int ndims,
	   Dimension** dims)
{
    int status = NC_NOERR;
    /* Do some special cases */
    if(ndims == 0) {
	status = ncaux_add_field(cmpd,name,basetype,0,NULL);
    } else {
        /* Need to create the needed subsidiary vlen types */ 
	int vlenid,pos;
	pos = locateleftvldn(ndims,dims,0);
	status = buildvlenchain(ncid,name,basetype,ndims,dims,pos+1,&vlenid);
        if(status != NC_NOERR) goto done;
	if(pos == 0) {
            status = ncaux_add_field(cmpd,name,vlenid,0,NULL);
	} else { /* pos > 0 */
	    int i;
	    int dimsizes[NC_MAX_VAR_DIMS];
	    for(i=0;i<pos;i++)
		dimsizes[i] = dimsize(dims[i]);
            status = ncaux_add_field(cmpd,name,vlenid,pos,dimsizes);
	}
        if(status != NC_NOERR) goto done;
    }

done:
    return status;
}

static int
buildvlenchain(int ncid,
		char* name,
		nc_type basetype,
		int ndims,
		Dimension** dims,
		int index,
		nc_type* vidp)
{
    int i, pos;
    int status = NC_NOERR;
    nc_type vlenid = basetype;
    char suid[4];
    char typename[NC_MAX_NAME+3+1];
    void* tag;
    int nidims;
    int idims[NC_MAX_VAR_DIMS];
    nc_type newid;
   
    /* Locate the leftmost * dimension starting at index*/
    pos = locateleftvlen(ndims,dims,index);
    if(pos < 0) { 
	/* We have hit the terminal set of dimensions; create a compound type */
	strcpy(typename,name);
	snprintf(suid,sizeof(suid),"%3d",index);
	strcat(typename,suid);
	status = ncaux_begin_compound(ncid,typename,NCAUX_ALIGN_C,&tag);
	if(status != NC_NOERR) goto done;
	/* Create a single field */
	nidims = (ndims - index);
	for(i=index;i<ndims;i++)
	    idims[i] = dimsize(dims[i]);
	status = ncaux_add_field(tag,name,basetype,nidims,idims);
	if(status != NC_NOERR) goto done;
	status = ncaux_end_compound(tag,vidp);
	if(status != NC_NOERR) goto done;		
    } else if(pos == (ndims - 1)) {
	/* Create a terminal vlen
	strcpy(typename,name);
	snprintf(suid,sizeof(suid),"%3d",index);
	strcat(typename,suid);
	status = nc_def_vlen(ncid,typename,basetype,vidp);
	if(status != NC_NOERR) goto done;
    } else { /* recurse */
        status = buildvlenchain(ncid,name,basetype,ndims,dims,pos+1,&newid);
	if(status != NC_NOERR) goto done;
	/* Create the compound if needed */
	if(pos > (index + 1)) {
	    /* intermediate dimensions, so create compound */
	    strcpy(typename,name);
	    snprintf(suid,sizeof(suid),"%3d",index+1);
	    strcat(typename,suid);
	    status = ncaux_begin_compound(ncid,typename,NCAUX_ALIGN_C,&tag);
	    if(status != NC_NOERR) goto done;
	    /* Create a single field */
	    nidims = (ndims - index);
	    for(i=index;i<ndims;i++)
	        idims[i] = dimsize(dims[i]);
	    status = ncaux_add_field(tag,name,basetype,nidims,idims);
	    if(status != NC_NOERR) goto done;
	    status = ncaux_end_compound(tag,&newid);
	    if(status != NC_NOERR) goto done;		
	} else
	    newid = basetype;
	/* create the vlen */
	strcpy(typename,name);
	snprintf(suid,sizeof(suid),"%3d",index);
	strcat(typename,suid);
	status = nc_def_vlen(ncid,typename,newid,vidp);
	if(status != NC_NOERR) goto done;
    }

done:
    return status;
}

static int
locateleftvlen(int ndims, Dimension** dims, int index)
{
    int i;
    /* Locate the leftmost * dimension starting at index*/
    for(i=0;i<ndims;i++) {
	Dimension* dim = dims[i];
        enum Dimcase dc = classifydim(dim);
        if(dc == DC_VLEN) return i;
    }
    return -1; /* no vlen located */
}

