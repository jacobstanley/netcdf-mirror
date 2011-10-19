/*********************************************************************
 *   Copyright 1993, UCAR/Unidata
 *   See netcdf/COPYRIGHT file for copying and redistribution conditions.
 *   $Header: /upc/share/CVS/netcdf-3/libncdce3/constraints3.c,v 1.40 2010/05/27 21:34:07 dmh Exp $
 *********************************************************************/

#include "ncdap3.h"
#include "dapodom.h"
#include "dapdebug.h"
#include "dapdump.h"
#include "dceparselex.h"

static NCerror qualifyconstraints3(DCEconstraint* constraint);
static void completesegments3(NClist* fullpath, NClist* segments);
static NCerror qualifyprojectionnames3(DCEprojection* proj);
static NCerror qualifyprojectionsizes3(DCEprojection* proj);
static NCerror qualifyselectionnames3(DCEselection* sel);
static NCerror matchpartialname3(NClist* nodes, NClist* segments, CDFnode** nodep);
static int matchsuffix3(NClist* matchpath, NClist* segments);
static int iscontainer(CDFnode* node);
static DCEprojection* projectify(CDFnode* field, DCEprojection* container);
static int slicematch(NClist* seglist1, NClist* seglist2);
static void removepseudodims3(DCEprojection* clone);

/* Parse incoming url constraints, if any,
   to check for syntactic correctness */ 
NCerror
parsedapconstraints(NCDAPCOMMON* dapcomm, char* constraints,
		    DCEconstraint* dceconstraint)
{
    NCerror ncstat = NC_NOERR;
    char* errmsg;

    ASSERT(dceconstraint != NULL);
    nclistclear(dceconstraint->projections);
    nclistclear(dceconstraint->selections);

    ncstat = dapceparse(constraints,dceconstraint,&errmsg);
    if(ncstat) {
	nclog(NCLOGWARN,"DCE constraint parse failure: %s",errmsg);
	nullfree(errmsg);
        nclistclear(dceconstraint->projections);
        nclistclear(dceconstraint->selections);
    } else {
#ifdef IGNORE
	int i;
#ifdef DEBUG
	NClist* allnodes;
fprintf(stderr,"constraint: %s",dumpconstraint(dceconstraint));
#endif
        /* Go thru each node and add annotation */
        allnodes = dceallnodes((DCEnode*)dceconstraint,CES_NIL);    
	for(i=0;i<nclistlength(allnodes);i++) {
	    DCEnode* node = (DCEnode*)nclistget(allnodes,i);
	}
#endif
    }
    return ncstat;
}

/* Map constraint paths to CDFnode paths in specified tree; the difficulty
   is that suffix paths are legal.
*/

NCerror
mapconstraints3(DCEconstraint* constraint,
		CDFnode* root)
{
    int i;
    NCerror ncstat = NC_NOERR;
    NClist* nodes = root->tree->nodes;
    NClist* dceprojections;
    NClist* dceselections;

    dceprojections = constraint->projections;
    dceselections = constraint->selections;

    /* Convert the projection paths to leaves in the dds tree */
    for(i=0;i<nclistlength(dceprojections);i++) {
	DCEprojection* proj = (DCEprojection*)nclistget(dceprojections,i);
	if(proj->discrim != CES_VAR) continue; // ignore functions
	ncstat = matchpartialname3(nodes,proj->var->segments,
#ifdef IGNORE
				   &proj->var->cdfleaf);
#else
				   &proj->var->cdfvar);
#endif
	if(ncstat) goto done;
    }

    /* Convert the selection paths to leaves in the dds tree */
    for(i=0;i<nclistlength(dceselections);i++) {
	DCEselection* sel = (DCEselection*)nclistget(dceselections,i);
	if(sel->lhs->discrim != CES_VAR) continue;
	ncstat = matchpartialname3(nodes,sel->lhs->var->segments,
#ifdef IGNORE
					&sel->lhs->var->cdfleaf);
#else
					&sel->lhs->var->cdfvar);
#endif
	if(ncstat) goto done;
    }
   
    /* Convert the selection path values to leaves in the dds tree */
    for(i=0;i<nclistlength(dceselections);i++) {
	int j;
	DCEselection* sel = (DCEselection*)nclistget(dceselections,i);
	for(j=0;j<nclistlength(sel->rhs);j++) {
	    DCEvalue* value = (DCEvalue*)nclistget(sel->rhs,j);
	    if(value->discrim != CES_VAR) continue;
	    ncstat = matchpartialname3(nodes,value->var->segments,
#ifdef IGNORE
					&value->var->cdfnode);
#else
					&value->var->cdfvar);
#endif
	    if(ncstat) goto done;
	}
    }
    /* Fill in segment information */
    ncstat = qualifyconstraints3(constraint);
    if(ncstat != NC_NOERR) goto done;

#ifdef DEBUG
fprintf(stderr,"mapconstraint.projections: %s\n",
		dumpprojections(dceprojections));
fprintf(stderr,"mapconstraint.selections: %s\n",
		dumpselections(dceselections));
#endif

done:
    return THROW(ncstat);
}


/* Fill in:
    1. projection segments
    2. projection segment slices declsize
    3. selection path
*/
static NCerror
qualifyconstraints3(DCEconstraint* constraint)
{
    NCerror ncstat = NC_NOERR;
    int i;
    if(constraint != NULL) {
        for(i=0;i<nclistlength(constraint->projections);i++) {  
            DCEprojection* p = (DCEprojection*)nclistget(constraint->projections,i);
            ncstat = qualifyprojectionnames3(p);
            ncstat = qualifyprojectionsizes3(p);
        }
        for(i=0;i<nclistlength(constraint->selections);i++) {   
            DCEselection* s = (DCEselection*)nclistget(constraint->selections,i);
            ncstat = qualifyselectionnames3(s);
        }
    }
    return ncstat;
}

static void
completesegments3(NClist* fullpath, NClist* segments)
{
    int i,delta;
    /* add path nodes to create full path */
    delta = (nclistlength(fullpath) - nclistlength(segments));
    ASSERT((delta >= 0));
    for(i=0;i<delta;i++) {
	int j;
        DCEsegment* seg = (DCEsegment*)dcecreate(CES_SEGMENT);
        CDFnode* node = (CDFnode*)nclistget(fullpath,i);
        seg->name = nulldup(node->ocname);
        seg->cdfnode = node;
	seg->rank = nclistlength(node->array.dimensions);
	for(j=0;j<seg->rank;j++) {
            CDFnode* dim = (CDFnode*)nclistget(node->array.dimensions0,j);
            dcemakewholeslice(seg->slices+j,dim->dim.declsize);
        }
        nclistinsert(segments,j,(ncelem)seg);
    }
    /* Now modify the segments to point to the appropriate node
       and fill in the slices.
    */
    for(i=delta;i<nclistlength(segments);i++) {
        DCEsegment* seg = (DCEsegment*)nclistget(segments,i);
        CDFnode* node = (CDFnode*)nclistget(fullpath,i);
	seg->cdfnode = node;
        if(!seg->slicesdefined) {
	    makewholesegment3(seg,node);
	}
    }
}

/* convert all names in projections in paths to be fully qualified
   by adding prefix segment objects. Also verify ranks
*/
static NCerror
qualifyprojectionnames3(DCEprojection* proj)
{
    NCerror ncstat = NC_NOERR;
    NClist* fullpath = nclistnew();

    ASSERT((proj->discrim == CES_VAR
#ifdef IGNORE
            && proj->var->cdfleaf != NULL
            && proj->var->cdfleaf->dds != OCNULL));
    collectnodepath3(proj->var->cdfleaf,fullpath,!WITHDATASET);
#else
            && proj->var->cdfvar != NULL
            && proj->var->cdfvar->dds != OCNULL));
    collectnodepath3(proj->var->cdfvar,fullpath,!WITHDATASET);
#endif
#ifdef DEBUG
fprintf(stderr,"qualify: %s -> ",
	dumpprojection(proj));
#endif
    /* Now add path nodes to create full path */
    completesegments3(fullpath,proj->var->segments);

#ifdef DEBUG
fprintf(stderr,"%s\n",
	dumpprojection(proj));
#endif
    nclistfree(fullpath);
    return ncstat;
}

/* Make sure that the slice declsizes are all defined for this projection */
static NCerror
qualifyprojectionsizes3(DCEprojection* proj)
{
    int i,j;
    ASSERT(proj->discrim == CES_VAR);
    for(i=0;i<nclistlength(proj->var->segments);i++) {
        DCEsegment* seg = (DCEsegment*)nclistget(proj->var->segments,i);
	NClist* dimset = NULL;
	int rank;
	ASSERT(seg->cdfnode != NULL);
	/* Must use dimensions0 of the template because
           the segments are wrt the underlying dce DDS */
        dimset = seg->cdfnode->array.dimensions0;
        rank = nclistlength(dimset);
        for(j=0;j<rank;j++) {
	    CDFnode* dim = (CDFnode*)nclistget(dimset,j);
	    dim = dim->basenode;
            assert(dim != null);
            seg->slices[j].declsize = dim->dim.declsize;	    
	}
    }
    return NC_NOERR;
}

   
/* convert all names in selections to be fully qualified */
static NCerror
qualifyselectionnames3(DCEselection* sel)
{
    NCerror ncstat = NC_NOERR;
    int i;
    NClist* segments = NULL;
    NClist* fullpath = nclistnew();

    ASSERT(sel->lhs->discrim == CES_VAR);
#ifdef IGNORE
    collectnodepath3(sel->lhs->var->cdfleaf,fullpath,!WITHDATASET);
#else
    collectnodepath3(sel->lhs->var->cdfvar,fullpath,!WITHDATASET);
#endif
#ifdef DEBUG
fprintf(stderr,"qualify.sel: %s -> ",
	dumpselection(sel));
#endif
    /* Now add path nodes to create full path */
    completesegments3(fullpath,sel->lhs->var->segments);
    for(i=0;i<nclistlength(sel->rhs);i++) {
        DCEvalue* value = (DCEvalue*)nclistget(sel->rhs,i);
        if(value->discrim != CES_VAR) continue;
        nclistclear(fullpath);
#ifdef IGNORE
        collectnodepath3(value->var->cdfnode,fullpath,!WITHDATASET);
#else
        collectnodepath3(value->var->cdfvar,fullpath,!WITHDATASET);
#endif
	completesegments3(fullpath,value->var->segments);
    }
    nclistfree(segments);
    nclistfree(fullpath);
    return THROW(ncstat);
}

/*
We are given a set of segments (in path)
representing a partial path for a CDFnode variable.
Our goal is to locate all matching
variables for which the path of that
variable has a suffix matching
the given partial path.
If one node matches exactly, then use that one;
otherwise there had better be exactly one
match else ambiguous.
Additional constraints (4/12/2010):
1. if a segment is dimensioned, then use that info
   to distinguish e.g a grid node from a possible
   grid array within it of the same name.
   Treat sequences as of rank 1.
2. if there are two matches, and one is the grid
   and the other is the grid array within that grid,
   then choose the grid array.
3. If there are multiple matches choose the one with the
   shortest path
4. otherwise complain about ambiguity
*/

/**
 * Given a path as segments,
 * try to locate the CDFnode
 * instance (from a given set)
 * that corresponds to the path.
 * The key difficulty is that the
 * path may only be a suffix of the
 * complete path.
 */

static NCerror
matchpartialname3(NClist* nodes, NClist* segments, CDFnode** nodep)
{
    int i,nsegs;
    NCerror ncstat = NC_NOERR;
    DCEsegment* lastseg = NULL;
    NClist* namematches = nclistnew();
    NClist* matches = nclistnew();
    NClist* matchpath = nclistnew();

    /* Locate all nodes with the same name
       as the last element in the segment path
    */
    nsegs = nclistlength(segments);
    lastseg = (DCEsegment*)nclistget(segments,nsegs-1);
    for(i=0;i<nclistlength(nodes);i++) {
        CDFnode* node = (CDFnode*)nclistget(nodes,i);
	if(node->ocname == null)
	    continue;
	/* Path names come from oc space */
        if(strcmp(node->ocname,lastseg->name) != 0)
	    continue;
	/* Only look at selected kinds of nodes */
	if(node->nctype != NC_Sequence
               && node->nctype != NC_Structure
               && node->nctype != NC_Grid
               && node->nctype != NC_Primitive
          )
	    continue;
	nclistpush(namematches,(ncelem)node);
    }    
    if(nclistlength(namematches)==0) {
        nclog(NCLOGERR,"No match for projection name: %s",lastseg->name);
        ncstat = NC_EDDS;
	goto done;
    }

    /* Now, collect and compare paths of the matching nodes */
    for(i=0;i<nclistlength(namematches);i++) {
        CDFnode* matchnode = (CDFnode*)nclistget(namematches,i);
	nclistclear(matchpath);
	collectnodepath3(matchnode,matchpath,0);
	/* Do a suffix match */
        if(matchsuffix3(matchpath,segments)) {
	    nclistpush(matches,(ncelem)matchnode);
#ifdef DEBUG
fprintf(stderr,"matchpartialname: pathmatch: %s :: %s\n",
matchnode->ncfullname,dumpsegments(segments));
#endif
	}
    }
    /* |matches|==0 => no match; |matches|>1 => ambiguity */
    switch (nclistlength(matches)) {
    case 0:
        nclog(NCLOGERR,"No match for projection name: %s",lastseg->name);
        ncstat = NC_EDDS;
	break;
    case 1:
        if(nodep)
	    *nodep = (CDFnode*)nclistget(matches,0);
	break;
    default: {
	CDFnode* minnode = NULL;
	int minpath = 0;
	int nmin = 0; /* to catch multiple ones with same short path */
	/* ok, see if one of the matches has a path that is shorter
           then all the others */
	for(i=0;i<nclistlength(matches);i++) {
	    CDFnode* candidate = (CDFnode*)nclistget(matches,i);
	    nclistclear(matchpath);
	    collectnodepath3(candidate,matchpath,0);
	    if(minpath == 0) {
		minpath = nclistlength(matchpath);
		minnode = candidate;
	    } else if(nclistlength(matchpath) == minpath) {
	        nmin++;		
	    } else if(nclistlength(matchpath) < minpath) {
		minpath = nclistlength(matchpath);
		minnode = candidate;
		nmin = 1;
	    }
	} /*for*/
	if(minnode == NULL || nmin > 1) {	
	    nclog(NCLOGERR,"Ambiguous match for projection name: %s",
			lastseg->name);
            ncstat = NC_EDDS;
	} else if(nodep)
	    *nodep = minnode;
	} break;
    }
#ifdef DEBUG
fprintf(stderr,"matchpartialname: choice: %s %s for %s\n",
(nclistlength(matches) > 1?"":"forced"),
(*nodep)->ncfullname,dumpsegments(segments));
#endif

done:
    return THROW(ncstat);
}

static int
matchsuffix3(NClist* matchpath, NClist* segments)
{
    int i,j;
    int nsegs = nclistlength(segments);
    int pathlen = nclistlength(matchpath);
    ASSERT(pathlen >= nsegs);
    for(i=0;i<pathlen;i++) {
        int pathmatch = 1;
	/* Starting at this point in the path, try to match the segment list */
        for(j=0;j<nsegs && (i+j < pathlen);j++) {
            int segmatch = 1;
	    DCEsegment* seg = (DCEsegment*)nclistget(segments,j);
   	    CDFnode* node = (CDFnode*)nclistget(matchpath,i+j);
	    int rank = seg->rank;
	    /* Do the names match (in oc name space) */
	    if(strcmp(seg->name,node->ocname) != 0) {
		segmatch = 0;/* no match */
	    } else
	    /* Do the ranks match (watch out for sequences) */
	    if(rank == 0) /* rank == 9 matches any set of dimensions */
		segmatch = 1;
	    else if(node->nctype == NC_Sequence)
	        segmatch = (rank == 1?1:0);
	    else /*!NC_Sequence*/
	        segmatch = (rank == nclistlength(node->array.dimensions0)?1:0);
	    if(!segmatch) pathmatch = 0;
	}
	if(pathmatch) return 1;
   }
   return 0;
}


/* Convert a DCEprojection instance into a string
   that can be used with the url
*/

char*
buildprojectionstring3(NClist* projections)
{
    char* pstring;
    NCbytes* buf = ncbytesnew();
    dcelisttobuffer(projections,buf,",");
    pstring = ncbytesdup(buf);
    ncbytesfree(buf);
    return pstring;
}

char*
buildselectionstring3(NClist* selections)
{
    NCbytes* buf = ncbytesnew();
    char* sstring;
    dcelisttobuffer(selections,buf,"&");
    sstring = ncbytesdup(buf);
    ncbytesfree(buf);
    return sstring;
}

char*
buildconstraintstring3(DCEconstraint* constraints)
{
    NCbytes* buf = ncbytesnew();
    char* result = NULL;
    dcetobuffer((DCEnode*)constraints,buf);
    result = ncbytesdup(buf);
    ncbytesfree(buf);
    return result;
}


/* Given the arguments to vara,
   construct a corresponding projection
   with any pseudo dimensions removed
*/
NCerror
buildvaraprojection3(Getvara* getvar,
		     const size_t* startp, const size_t* countp, const ptrdiff_t* stridep,
		     DCEprojection** projectionp)
{
    int i,j;
    int ncrank = 0;
    NCerror ncstat = NC_NOERR;
    CDFnode* var = getvar->target;
    DCEprojection* projection = NULL;
    NClist* path = nclistnew();
    NClist* segments = NULL;
    int dimindex;

    ncstat = dapvar2projection(var,&projection);

    /* We need to assign the start/count/stride info to each segment;
       declsize will have been set
    */
    dimindex = 0; /* point to next subset of slices */
    segments = projection->var->segments;
    ncrank = nclistlength(var->array.dimensions);
    for(i=0;i<nclistlength(segments);i++) {
	DCEsegment* segment = (DCEsegment*)nclistget(segments,i);
        for(j=0;j<segment->rank;j++) {
	    DCEslice* slice = &segment->slices[j];
	    /* make each slice represent the corresponding
               start/count/stride */
	    slice->first = startp[dimindex+j];
	    slice->stride = stridep[dimindex+j];
	    slice->count = countp[dimindex+j];
	    slice->length = slice->count * slice->stride;
	    if(slice->length > slice->declsize)
		slice->length = slice->declsize;
	    slice->stop = (slice->first + slice->length);
	    if(slice->stop > slice->declsize)
		slice->stop = slice->declsize;
	}
	dimindex += segment->rank;
	ASSERT((dimindex <= ncrank));
    }

    ASSERT((dimindex == ncrank));

    removepseudodims3(projection);

#ifdef DEBUG
fprintf(stderr,"buildvaraprojection3: projection=%s\n",
        dumpprojection(projection));
#endif

    if(projectionp) *projectionp = projection;

    nclistfree(path);
    if(ncstat) dcefree((DCEnode*)projection);
    return ncstat;
}

static void
removepseudodims3(DCEprojection* clone)
{
    int i;
    int nsegs;
    DCEsegment* seg;

    ASSERT((clone != NULL));
    nsegs = nclistlength(clone->var->segments);

    /* 1. scan for sequences and remove
	  any index projections. */
    for(i=0;i<nsegs;i++) {
	seg = (DCEsegment*)nclistget(clone->var->segments,i);
	if(seg->cdfnode->nctype != NC_Sequence) continue; /* not a sequence */
	seg->rank = 0;
    }

    /* 2. Check the terminal segment to see if it is a String primitive,
          and if so, then remove the string dimension */
    ASSERT((nsegs > 0));
    seg = (DCEsegment*)nclistget(clone->var->segments,nsegs-1);
    /* See if the node has a string dimension */
    if(seg->cdfnode->nctype == NC_Primitive
       && seg->cdfnode->array.stringdim != NULL) {
	/* Remove the string dimension projection from the segment */
	seg->rank--;
    }
}

int
iswholeslice(DCEslice* slice, CDFnode* dim)
{
    if(slice->first != 0 || slice->stride != 1) return 0;
    if(dim != NULL) {
	if(slice->stop != dim->dim.declsize) return 0;
    } else if(dim == NULL) {
	if(slice->declsize == 0
	   || slice->count != slice->declsize) return 0;
    }
    return 1;
}

int
iswholesegment(DCEsegment* seg)
{
    int i,whole;
    NClist* dimset = NULL;
    unsigned int rank;
    
    if(seg->rank == 0) return 1;
    if(!seg->slicesdefined) return 0;
    if(seg->cdfnode == NULL) return 0;
    dimset = seg->cdfnode->array.dimensions;
    rank = nclistlength(dimset);
    whole = 1; /* assume so */
    for(i=0;i<rank;i++) {
	CDFnode* dim = (CDFnode*)nclistget(dimset,i);
	if(!iswholeslice(&seg->slices[i],dim)) {whole = 0; break;}	
    }
    return whole;
}

int
iswholeprojection(DCEprojection* proj)
{
    int i,whole;
    
    ASSERT((proj->discrim == CES_VAR));

    whole = 1; /* assume so */
    for(i=0;i<nclistlength(proj->var->segments);i++) {
        DCEsegment* segment = (DCEsegment*)nclistget(proj->var->segments,i);
	if(!iswholesegment(segment)) {whole = 0; break;}	
    }
    return whole;
}

int
iswholeconstraint(DCEconstraint* con)
{
    int i;
    if(con == NULL) return 1;
    if(con->projections != NULL) {
	for(i=0;i<nclistlength(con->projections);i++) {
	 if(!iswholeprojection((DCEprojection*)nclistget(con->projections,i)))
	    return 0;
	}
    }
    if(con->selections != NULL)
	return 0;
    return 1;
}

void
makewholesegment3(DCEsegment* seg, CDFnode* node)
{
    int i;
    NClist* dimset = NULL;
    unsigned int rank;

    dimset = node->array.dimensions;
    rank = nclistlength(dimset);

    seg->rank = rank;
    for(i=0;i<rank;i++) {
	CDFnode* dim = (CDFnode*)nclistget(dimset,i);
	dcemakewholeslice(&seg->slices[i],dim->dim.declsize);
    }
    seg->slicesdefined  = 1;
    seg->slicesdeclized = 1;
}


/*
Given a set of projections, we need to produce
an expanded, correct, and equivalent set of projections.
The term "correct" means we must fix the following cases:
1. Multiple occurrences of the same leaf variable
   with differing projection slices. Fix is to complain.
2. Occurrences of container and one or more of its fields.
   Fix is to suppress the container.
The term "expanded" means
1. Expand all occurrences of only a container by
   replacing it with all of its fields.
*/

NCerror
fixprojections(NClist* list)
{
    int i,j,k;
    NCerror ncstat = NC_NOERR;
    NClist* tmp = nclistnew(); /* misc. uses */

#ifdef DEBUG
fprintf(stderr,"unifyprojection: list = %s\n",dumpprojections(list));
#endif

    if(nclistlength(list) == 0) goto done;

    /* Step 1: remove duplicates and complain about slice mismatches */
    for(i=0;i<nclistlength(list);i++) {
	DCEprojection* p1 = (DCEprojection*)nclistget(list,i);
	if(p1 == NULL) continue;
        if(p1->discrim != CES_VAR) continue; /* dont try to unify functions */
        for(j=i;j<nclistlength(list);j++) {
	    DCEprojection* p2 = (DCEprojection*)nclistget(list,j);
	    if(p2 == NULL) continue;
	    if(p2->discrim != CES_VAR) continue;
#ifdef IGNORE
	    if(p1->var->cdfleaf != p2->var->cdfleaf) continue;
#else
	    if(p1->var->cdfvar != p2->var->cdfvar) continue;
#endif
	    /* check for slice mismatches */
	    if(!slicematch(p1->var->segments,p2->var->segments)) {
		/* complain */
		nclog(NCLOGWARN,"Malformed projection: same variable with different slicing");
	    }
	    /* remove p32 */
	    nclistset(list,j,(ncelem)NULL);	    
	    dcefree((DCEnode*)p2);	    
	}	
    }

    /* Step 2: remove containers when a field is also present */
    for(i=0;i<nclistlength(list);i++) {
	DCEprojection* p1 = (DCEprojection*)nclistget(list,i);
	if(p1 == NULL) continue;
        if(p1->discrim != CES_VAR) continue; /* dont try to unify functions */
#ifdef IGNORE
	if(!iscontainer(p1->var->cdfleaf))
#else
	if(!iscontainer(p1->var->cdfvar))
#endif
	    continue;
        for(j=i;j<nclistlength(list);j++) {
	    DCEprojection* p2 = (DCEprojection*)nclistget(list,j);
	    if(p2 == NULL) continue;
	    if(p2->discrim != CES_VAR) continue;
	    nclistclear(tmp);
#ifdef IGNORE
	    collectnodepath3(p2->var->cdfleaf,tmp,WITHDATASET);
#else
	    collectnodepath3(p2->var->cdfvar,tmp,WITHDATASET);
#endif
	    for(k=0;k<nclistlength(tmp);k++) {
		CDFnode* candidate = (CDFnode*)nclistget(tmp,k);
#ifdef IGNORE
	        if(candidate == p1->var->cdfleaf) {
#else
	        if(candidate == p1->var->cdfvar) {
#endif
		    nclistset(list,i,(ncelem)NULL);	    
	            dcefree((DCEnode*)p1);
		    goto next;
		}
	    }
	}
next:   continue;
    }

    /* Step 3: expand all containers recursively down to the leaf nodes */
    for(;;) {
	nclistclear(tmp);
        for(i=0;i<nclistlength(list);i++) {
            DCEprojection* target = (DCEprojection*)nclistget(list,i);
            CDFnode* leaf;
            if(target == NULL) continue;
            if(target->discrim != CES_VAR)
                continue; /* dont try to unify functions */
#ifdef IGNORE
            leaf = target->var->cdfleaf;
#else
            leaf = target->var->cdfvar;
#endif
            ASSERT(leaf != NULL);
            if(iscontainer(leaf)) {/* capture container */
		if(!nclistcontains(tmp,(ncelem)target))
                    nclistpush(tmp,(ncelem)target);
                nclistset(list,i,(ncelem)NULL);
            }
        }
	if(nclistlength(tmp) == 0) break; /*done*/
        /* Now explode the containers */
        for(i=0;i<nclistlength(tmp);i++) {
            DCEprojection* container = (DCEprojection*)nclistget(tmp,i);
#ifdef IGNORE
	    CDFnode* leaf = container->var->cdfleaf;
#else
	    CDFnode* leaf = container->var->cdfvar;
#endif
            for(j=0;i<nclistlength(leaf->subnodes);j++) {
                CDFnode* field = (CDFnode*)nclistget(leaf->subnodes,j);
		/* Convert field node to a proper constraint */
		DCEprojection* proj = projectify(field,container);
		nclistpush(list,(ncelem)proj);
	    }	    
            /* reclaim the container */
	    dcefree((DCEnode*)container);
	}
    } /*for(;;)*/

    /* remove all NULL elements */
    for(i=nclistlength(list)-1;i>=0;i--) {
        DCEprojection* target = (DCEprojection*)nclistget(list,i);
	if(target == NULL)
	    nclistremove(list,i);	
    }	

done:
#ifdef DEBUG
fprintf(stderr,"unifyprojection: exploded = %s\n",dumpprojections(list));
#endif
    return ncstat;
}

static int
iscontainer(CDFnode* node)
{
    return (node->nctype == NC_Dataset
               || node->nctype == NC_Sequence
               || node->nctype == NC_Structure
               || node->nctype == NC_Grid);
}

static DCEprojection*
projectify(CDFnode* field, DCEprojection* container)
{
    DCEprojection* proj  = (DCEprojection*)dcecreate(CES_PROJECT);
    DCEvar* var  = (DCEvar*)dcecreate(CES_VAR);
    DCEsegment* seg  = (DCEsegment*)dcecreate(CES_SEGMENT);
    proj->discrim = CES_VAR;
    proj->var = var;
#ifdef IGNORE
    var->cdfnode = field;
    var->cdfleaf = field;
#else
    var->cdfvar = field;
#endif
    /* Dup the segment list */
    var->segments = dceclonelist(container->var->segments);
    seg->rank = 0;
    nclistpush(var->segments,(ncelem)seg);
    return proj;
}

static int
slicematch(NClist* seglist1, NClist* seglist2)
{
    int i,j;
    if((seglist1 == NULL || seglist2 == NULL) && seglist1 != seglist2)
	return 0;
    if(nclistlength(seglist1) != nclistlength(seglist2))
	return 0;
    for(i=0;i<nclistlength(seglist1);i++) {
	DCEsegment* seg1 = (DCEsegment*)nclistget(seglist1,i);
	DCEsegment* seg2 = (DCEsegment*)nclistget(seglist2,i);
	if(seg1->rank != seg2->rank)
	    return 0;
	for(j=0;j<seg1->rank;j++) {
	    if(seg1->slices[j].first != seg2->slices[j].first 
	       || seg1->slices[j].count != seg2->slices[j].count
	       || seg1->slices[j].stride != seg2->slices[j].stride)
		return 0;
	}
    }
    return 1;
}

/* Convert a CDFnode var to a projection; include
   pseudodimensions
*/
int
dapvar2projection(CDFnode* var, DCEprojection** projectionp)
{
    int i,j;
    int ncstat = NC_NOERR;
    NClist* path = nclistnew();
    NClist* dimset = NULL;
    int ncrank, dimindex;
    NClist* segments;
    DCEprojection* projection = NULL;

    /* Collect the nodes needed to construct the projection segment */    
    collectnodepath3(var,path,!WITHDATASET);

    dimset = var->array.dimensions;
    ncrank = nclistlength(dimset);

    segments = nclistnew();
    dimindex = 0; /* point to next subset of slices */
    nclistsetalloc(segments,nclistlength(path));
    for(i=0;i<nclistlength(path);i++) {
	DCEsegment* segment = (DCEsegment*)dcecreate(CES_SEGMENT);
	CDFnode* n = (CDFnode*)nclistget(path,i);
	int localrank;
	segment->cdfnode = n;
	ASSERT((segment->cdfnode != NULL));
        segment->name = nulldup(n->ocname);
        /* We need to assign whole slices to each segment */
	localrank = nclistlength(segment->cdfnode->array.dimensions0);
        if(segment->cdfnode->array.stringdim != NULL) localrank++;
        if(segment->cdfnode->array.seqdim != NULL)
	    localrank++;
        segment->rank = localrank;
        for(j=0;j<localrank;j++) {
	    DCEslice* slice;
	    CDFnode* dim;
	    ASSERT((dimindex+j) < ncrank);
	    slice = &segment->slices[j];
	    dim = (CDFnode*)nclistget(dimset,dimindex+j);
	    dcemakewholeslice(slice,dim->dim.declsize);
	}
	segment->slicesdefined = 1;
	segment->slicesdeclized = 1;
	dimindex += localrank;
	ASSERT((dimindex <= ncrank));
	nclistpush(segments,(ncelem)segment);
    }
    ASSERT((dimindex == ncrank));
    
    projection = (DCEprojection*)dcecreate(CES_PROJECT);
    projection->discrim = CES_VAR;
    projection->var = (DCEvar*)dcecreate(CES_VAR);
#ifdef IGNORE
    projection->var->cdfleaf = var;
#else
    projection->var->cdfvar = var;
#endif
    projection->var->segments = segments;

#ifdef DEBUG
fprintf(stderr,"dapvar2projection: projection=%s\n",
        dumpprojection(projection));
#endif

    nclistfree(path);
    if(ncstat) dcefree((DCEnode*)projection);
    else if(projectionp) *projectionp = projection;
    return ncstat;
}    

/*
Given a set of projections and a projection
representing a variable (from, say vara or prefetch)
construct a single projection for fetching that variable
with the proper constraints
*/
int
daprestrictprojection1(NClist* projections, DCEprojection* var, DCEprojection** resultp)
{
    int ncstat = NC_NOERR;
    int i;
    DCEprojection* result = NULL;
#ifdef DEBUG
fprintf(stderr,"restrictprojection.before: constraints=|%s| var=|%s|\n",
		dumpprojections(projections),
		dumpprojection(var));
#endif

    ASSERT(var != NULL);

    /* the projection list will contain at most 1 match for the var by construction */
    for(result=null,i=0;i<nclistlength(projections);i++) {
	DCEprojection* p1 = (DCEprojection*)nclistget(projections,i);
	if(p1 == NULL || p1->discrim != CES_VAR) continue;
#ifdef IGNORE
	if(p1->var->cdfleaf == var->var->cdfleaf) {
#else
	if(p1->var->cdfvar == var->var->cdfvar) {
#endif
	    result = p1;
	    break;
	}
    }
    if(result == NULL) {
	result = (DCEprojection*)dceclone((DCEnode*)var); /* use only the var projection */
 	goto done;	
    }

    /* We need to merge the projection from the projection list
       with the var projection
    */
    result = (DCEprojection*)dceclone((DCEnode*)result); /* so we can modify */
    ncstat = dcemergeprojections(result,var); /* result will be modified */    

done:
    if(resultp) *resultp = result;
#ifdef DEBUG
fprintf(stderr,"restrictprojection.after=|%s|\n",
		dumpprojection(result));
#endif
    return ncstat;
}

