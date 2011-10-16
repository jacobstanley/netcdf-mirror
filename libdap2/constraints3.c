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

static NCerror unifyprojection3r(DCEprojection*, DCEprojection*);

static NCerror matchpartialname3(NClist*, NClist*, CDFnode**);
static int matchsuffix3(NClist* matchpath, NClist* segments);
static void completesegments3(NClist* fullpath, NClist* segments);

static NCerror qualifyconstraints3(DCEconstraint*);
static NCerror qualifyprojectionnames3(DCEprojection*);
static NCerror qualifyprojectionsizes3(DCEprojection*);
static NCerror qualifyselectionnames3(DCEselection*);
static NClist* compressprojectionnodes3(NClist* varlist);
static int treecontains3(CDFnode* var, CDFnode* root);

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
				   &proj->var->cdfleaf);
	if(ncstat) goto done;
    }

    /* Convert the selection paths to leaves in the dds tree */
    for(i=0;i<nclistlength(dceselections);i++) {
	DCEselection* sel = (DCEselection*)nclistget(dceselections,i);
	if(sel->lhs->discrim != CES_VAR) continue;
	ncstat = matchpartialname3(nodes,sel->lhs->var->segments,&sel->lhs->var->cdfleaf);
	if(ncstat) goto done;
    }
   
    /* Convert the selection path values to leaves in the dds tree */
    for(i=0;i<nclistlength(dceselections);i++) {
	int j;
	DCEselection* sel = (DCEselection*)nclistget(dceselections,i);
	for(j=0;j<nclistlength(sel->rhs);j++) {
	    DCEvalue* value = (DCEvalue*)nclistget(sel->rhs,j);
	    if(value->discrim != CES_VAR) continue;
	    ncstat = matchpartialname3(nodes,value->var->segments,&value->var->cdfnode);
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
            && proj->var->cdfleaf != NULL
            && proj->var->cdfleaf->dds != OCNULL));
    collectnodepath3(proj->var->cdfleaf,fullpath,!WITHDATASET);
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
    collectnodepath3(sel->lhs->var->cdfleaf,fullpath,!WITHDATASET);
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
        collectnodepath3(value->var->cdfnode,fullpath,!WITHDATASET);
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

#ifdef IGNORE
static void
collectsegmentnames3(NClist* segments, NClist* path)
{
    int i;
    ncbytesclear(path);
    for(i=0;i<nclistlength(segments);i++) {
	DCEsegment* segment = (DCEsegment*)nclistget(segments,i);
	nclistpush(path,(ncelem)segment->name);
    }
}
#endif /*IGNORE*/

/*
Compute the projection using heuristics
that take into account the current
fetch limit and the various variable sizes.

Define the heuristic tactics for
retrieving data.

The rules are as follows:
1. if we can read the whole dataset under the limit,
   then do so => tactic_all
2. if we can read the vara variable + all the small
   variables, then do so => tactic_partial
3. if we can read the containing grid
   then do so => tactic_grid
3. (default) read the containing vara variable => tactic_var

Note in particular, that the retrieval may return a result
that is a superset of the vara parameters and so the data
walking routines must be able to handle this situation.  So,
a secondary goal is to produce a projection that can be used
by the data walking routines to obtain the proper subset of
the returned data.

Note also that we need to make sure to match the relevant
dimensions against the relevant nodes in which the ultimate
target is contained. Must take sequence-related dimensions
and string pseudo-dimension into account.

This routine returns (in getvar argument) two results:
1. the set of DCEprojection instances that are to be used
   for retrieval (getvar->tactic.fetch).
2. the set of DCEprojection instances that are to be used
   for walking the data (getvar->tactic.walk).

*/


/*
The original URL projections
will define the maximum set of
variables that will be retrieved.
However, our tactic may restrict that
set further, so we modify the projection
set to remove projections not
referring to the specified variables.
Additionally, try to merge projections
into larger projections when possible.
We also need to watch out for one projection
enlarging on another (e.g. types.i32 vs types).
The larger one must be removed to avoid
changing the DDS metadata in a way that is
inconsistent with the DDS metadata.
*/

void
restrictprojection34(NClist* varlist, NClist* projections)
{
    int i,j,len;

#ifdef DEBUG
fprintf(stderr,"restriction.before=|%s|\n",
		dumpprojections(projections));
#endif

    if(nclistlength(varlist) == 0) goto done; /* nothing to add or remove */

    /* If the projection list is empty, then add
       a projection for every variable in varlist
    */
    if(nclistlength(projections) == 0) {
        NClist* path = nclistnew();
	NClist* nodeset = NULL;
	/* Attempt to unify the vars into larger units
	   (like a complete grid) */
	nodeset = compressprojectionnodes3(varlist);	
        for(i=0;i<nclistlength(nodeset);i++) {
	    DCEprojection* newp;
	    CDFnode* var = (CDFnode*)nclistget(nodeset,i);
#ifdef DEBUG
fprintf(stderr,"restriction.candidate=|%s|\n",var->ncfullname);
#endif
	    newp = (DCEprojection*)dcecreate(CES_PROJECT);

	    newp->discrim = CES_VAR;
	    newp->var = (DCEvar*)dcecreate(CES_VAR);

	    newp->var->cdfleaf = var;
	    nclistclear(path);
	    collectnodepath3(var,path,!WITHDATASET);
	    newp->var->segments = nclistnew();
	    for(j=0;j<nclistlength(path);j++) {
	        CDFnode* node = (CDFnode*)nclistget(path,j);
	        DCEsegment* newseg = (DCEsegment*)dcecreate(CES_SEGMENT);
	        newseg->name = nulldup(node->ocname);
	        makewholesegment3(newseg,node);/*treat as simple projections*/
	        newseg->cdfnode = node;
	        nclistpush(newp->var->segments,(ncelem)newseg);
	    }
	    nclistpush(projections,(ncelem)newp);
	}
	nclistfree(path);
	nclistfree(nodeset);
    } else {
       /* Otherwise, walk all the projections and see if they
	   intersect any of the variables. If not,
	   then remove from the projection list.
	*/
	NClist* suppress = nclistnew();
	DCEprojection* proj;
	len = nclistlength(projections);
	for(i=0;i<len;i++) {
	    int intersect = 0;
	    proj = (DCEprojection*)nclistget(projections,i);
	    if(proj->discrim != CES_VAR) continue;
	    for(j=0;j<nclistlength(varlist);j++) {
		CDFnode* var = (CDFnode*)nclistget(varlist,j);
		/* Note that intersection could go either way */
		if(treecontains3(var,proj->var->cdfleaf)) {
		    intersect = 1;
		    break;
		} else if(treecontains3(proj->var->cdfleaf,var)) {
		    intersect = 1;
		    break;
		}
	    }	    
	    if(!intersect) {
		/* suppress this projection */
		nclistpush(suppress,(ncelem)proj);
	    }
	}
	if(nclistlength(suppress) > 0) {
	    for(i=0;i<nclistlength(suppress);i++) {
		nclistelemremove(projections,nclistget(suppress,i));
	    }
	    nclistfree(suppress);
	}
	/* Now looks for containment between projections and only keep
           the more restrictive. Is this algorithm stable against reordering?.
	*/
	for(;;) {
	    int removed = 0;
	    for(i=0;i<nclistlength(projections);i++) {
	        DCEprojection* pi = (DCEprojection*)nclistget(projections,i);
	        if(pi->discrim != CES_VAR) continue;
	        for(j=0;j<i;j++) {
	            DCEprojection* pj = (DCEprojection*)nclistget(projections,j);
	            if(pj->discrim != CES_VAR) continue;
		    if(treecontains3(pi->var->cdfleaf,pj->var->cdfleaf)) {
		        DCEprojection* p = (DCEprojection*)nclistremove(projections,j);
			dcefree((DCEnode*)p);
			removed = 1;
			break;
		    } else if(treecontains3(pj->var->cdfleaf,pi->var->cdfleaf)) {
		        DCEprojection* p = (DCEprojection*)nclistremove(projections,i);
			dcefree((DCEnode*)p);
			removed = 1;
			break;
		    }
		}
	    }
	    if(!removed) break;
	}
    }
    
done:
#ifdef DEBUG
fprintf(stderr,"restriction.after=|%s|\n",
		dumpprojections(projections));
#endif
    return;
}

/* Return 1 if the specified var is in
the projection's leaf's subtree and is
visible
*/

static int
treecontains3(CDFnode* var, CDFnode* root)
{
    int i;

    if(root->visible == 0)
	return 0;
    if(var == root)
	return 1;
    for(i=0;i<nclistlength(root->subnodes);i++) {
        CDFnode* subnode = (CDFnode*)nclistget(root->subnodes,i);
	if(treecontains3(var,subnode)) return 1;
    }
    return 0; 
}

/* See if we can unify sets of nodes to be projected
   into larger units.
*/
static NClist*
compressprojectionnodes3(NClist* varlist)
{
    int i;
    NClist* nodeset = nclistnew();
    NClist* containerset = nclistnew();
    NClist* containernodes = nclistnew();

    nclistsetalloc(nodeset,nclistlength(varlist));
    nclistsetalloc(containerset,nclistlength(varlist));
    /* Duplicate the varlist so we can modify it;
       simultaneously collect unique container set.
    */
    for(i=0;i<nclistlength(varlist);i++) {
	CDFnode* var = (CDFnode*)nclistget(varlist,i);
	CDFnode* container = var->container;
	nclistpush(nodeset,(ncelem)var);
	switch (container->nctype) {
	case NC_Sequence: case NC_Structure: case NC_Grid: case NC_Dataset:
	    /* add (uniquely) to container set */
	    if(!nclistcontains(containerset,(ncelem)container)) 
	        nclistpush(containerset,(ncelem)container);
	    break;
	default: break;
	}
    }

    /* Now, try to find containers whose subnodes are all in the
	varlist; repeat until no more changes */
    for(;;) {
	int changed = 0;
        for(i=0;i<nclistlength(containerset);i++) {
            int j, allfound;
            CDFnode* container = (CDFnode*)nclistget(containerset,i);
	    if(container == NULL) continue;
            nclistclear(containernodes);
            for(allfound=1,j=0;j<nclistlength(container->subnodes);j++) {
                CDFnode* subnode = (CDFnode*)nclistget(container->subnodes,j);
                if(!nclistcontains(varlist,(ncelem)subnode)) {allfound=0;break;}
                nclistpush(containernodes,(ncelem)subnode);
            }
            if(allfound) {
                nclistpush(nodeset,(ncelem)container);
                nclistset(containerset,i,(ncelem)NULL); /* remove */
                for(j=nclistlength(nodeset)-1;j>=0;j--) { /* walk backwards */
                    CDFnode* testnode = (CDFnode*)nclistget(nodeset,j);
                    if(nclistcontains(containernodes,(ncelem)testnode))
                        nclistremove(nodeset,j);/* remove */
                }
		changed = 1;
            }
        }
	if(!changed) break; /* apparently we have reached a stable situation */
    }
    /* If there is only the dataset left as a projection, then remove it */
    if(nclistlength(nodeset) == 1) {
	CDFnode* thenode = (CDFnode*)nclistget(nodeset,0);
	if(thenode->nctype == NC_Dataset) nclistclear(nodeset);
    }
    nclistfree(containerset);
    nclistfree(containernodes);
    return nodeset;
}

/*
Given a projection list, merge
the projections taking 
overlapping projections into acct.
Assume that name qualification has occured.
Argument will be modified.
*/
NCerror
unifyprojections3(NClist* list)
{
    int i,j;
    NCerror ncstat = NC_NOERR;

#ifdef DEBUG
fprintf(stderr,"unifyprojection: list = %s\n",dumpprojections(list));
#endif

    ASSERT(nclistlength(list) != 0);

    /* Repeatedly pull elements from the list
       merge with all duplicates, and stick into
       the result
    */
    for(i=0;i<nclistlength(list);i++) {
	DCEprojection* target = (DCEprojection*)nclistget(list,0);
	if(target == NULL) continue;
        if(target->discrim != CES_VAR)
	    continue; /* dont try to unify functions */
        for(j=i;j<nclistlength(list);j++) {
	    DCEprojection* p2 = (DCEprojection*)nclistget(list,j);
	    if(p2 == NULL) continue;
	    if(p2->discrim != CES_VAR) continue;
	    if(target->var->cdfleaf != p2->var->cdfleaf) continue;
	    /* This entry matches our current target; merge  */
	    ncstat = unifyprojection3r(target,p2);
	    /* null out this merged entry and release it */
	    nclistset(list,j,(ncelem)NULL);	    
	    dcefree((DCEnode*)p2);	    
	}		    
    }	    
    /* compress out null entries */
    for(i=nclistlength(list)-1;i>=0;i--) {
	if(nclistget(list,i) == (ncelem)NULL)
	    nclistremove(list,i);
    }
    return ncstat;
}

static NCerror
unifyprojection3r(DCEprojection* dst, DCEprojection* src)
{
    NCerror ncstat = NC_NOERR;
    int i,j;

    /* merge segment by segment */
    ASSERT((dst->discrim == CES_VAR && src->discrim == CES_VAR));
    ASSERT((nclistlength(dst->var->segments) == nclistlength(src->var->segments)));    
    for(i=0;i<nclistlength(dst->var->segments);i++) {
	DCEsegment* dstseg = (DCEsegment*)nclistget(dst->var->segments,i);
	DCEsegment* srcseg = (DCEsegment*)nclistget(src->var->segments,i);
	ASSERT((dstseg->cdfnode == srcseg->cdfnode)); /* by construction */
	ASSERT((dstseg->rank == srcseg->rank)); /* by construction */
	for(j=0;j<dstseg->rank;j++) {
	    dceslicemerge(&dstseg->slices[j],&srcseg->slices[j]);
	}
    }
    return ncstat;
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

#ifdef IGNORE
/* Remove all CDFnode* references from constraint */
void
dereference3(DCEconstraint* constraint)
{
    int i;
    NClist* allnodes = dceallnodes((DCEnode*)constraint,CES_NIL);
    for(i=0;i<nclistlength(allnodes);i++) {
	DCEnode* node = (DCEnode*)nclistget(allnodes,i);
	switch(node->sort) {
	case CES_SEGMENT:
	    ((DCEsegment*)node)->cdfnode = NULL;
	    break;
	case CES_VAR:
	    ((DCEvar*)node)->cdfnode = NULL;
	    ((DCEvar*)node)->cdfleaf = NULL;
	    break;
	default: break; /* ignore */
	}
    }
    nclistfree(allnodes);
}

static NCerror
fillsegmentpath(DCEprojection* p, NClist* nodes)
{
    int i;
    NCerror ncstat = NC_NOERR;
    NClist* path = nclistnew();

    ASSERT(p->discrim == CES_VAR);
    collectsegmentnames3(p->var->segments,path);
    ncstat = matchpartialname3(nodes,path,&p->var->cdfleaf);
    if(ncstat) goto done;
    /* Now complete the segment path */
    nclistclear(path);
    collectnodepath3(p->var->cdfleaf,path,!WITHDATASET);
    if(nclistlength(path) != nclistlength(p->var->segments)) {
	ncstat = NC_EINVAL;
	goto done;
    }
    for(i=0;i<nclistlength(p->var->segments);i++) {
        DCEsegment* seg = (DCEsegment*)nclistget(p->var->segments,i);
	CDFnode* node = (CDFnode*)nclistget(path,i);
	seg->cdfnode = node;
#ifdef DEBUG
fprintf(stderr,"reref: %s -> %s\n",seg->name,node->ocname);
#endif
    }
    
done:
    nclistfree(path);
    return ncstat;
}

static NCerror
fillselectionpath(DCEselection* s, NClist* nodes)
{
    int i;
    NCerror ncstat = NC_NOERR;
    NClist* path = nclistnew();
    DCEvar* var;

    ASSERT(s->lhs->discrim == CES_VAR);
    var = s->lhs->var;
    ncstat = matchpartialname3(nodes,var->segments,&var->cdfleaf);
    if(ncstat) goto done;
    /* Now find the value paths */
    for(i=0;i<nclistlength(s->rhs);i++) {
        DCEvalue* v = (DCEvalue*)nclistget(s->rhs,i);
	if(v->discrim != CES_VAR) continue;
        ncstat = matchpartialname3(nodes,v->var->segments,&v->var->cdfnode);
        if(ncstat) goto done;
    }
    
done:
    nclistfree(path);
    return ncstat;
}

/* Inverse of dereference:
   add back all CDFnode* references to
   constraint based on a new set of varnodes,
   which by construction should be a 1-1
   with the constraint vars.
*/
NCerror
rereference3(DCEconstraint* constraint, NClist* nodeset)
{
    int i;
    NCerror ncstat = NC_NOERR;
    for(i=0;i<nclistlength(constraint->projections);i++) {
        DCEprojection* p = (DCEprojection*)nclistget(constraint->projections,i);
        ncstat = fillsegmentpath(p, nodeset);
	if(!ncstat) goto done;
    }
    for(i=0;i<nclistlength(constraint->selections);i++) {
        DCEselection* s = (DCEselection*)nclistget(constraint->selections,i);
	ncstat = fillselectionpath(s, nodeset);
	if(!ncstat) goto done;
    }
done:
    return ncstat;
}

#endif /*IGNORE*/

NCerror
buildvaraprojection3(Getvara* getvar,
		     const size_t* startp, const size_t* countp, const ptrdiff_t* stridep,
		     DCEprojection** projectionp)
{
    int i,j;
    int ncrank;
    NCerror ncstat = NC_NOERR;
    CDFnode* var = getvar->target;
    DCEprojection* projection = NULL;
    NClist* path = nclistnew();
    NClist* segments = NULL;
    int dimindex;
    NClist* dimset = NULL;

    /* Collect the nodes needed to construct the projection segment */    
    collectnodepath3(var,path,!WITHDATASET);

    dimset = var->array.dimensions;
    ncrank = nclistlength(dimset);

    segments = nclistnew();
    nclistsetalloc(segments,nclistlength(path));
    for(i=0;i<nclistlength(path);i++) {
	DCEsegment* segment = (DCEsegment*)dcecreate(CES_SEGMENT);
	CDFnode* n = (CDFnode*)nclistget(path,i);
	segment->cdfnode = n;
	ASSERT((segment->cdfnode != NULL));
        segment->name = nulldup(n->ocname);
	segment->slicesdefined = 0; /* temporary */
	segment->slicesdeclized = 0; /* temporary */
	nclistpush(segments,(ncelem)segment);
    }
    
    projection = (DCEprojection*)dcecreate(CES_PROJECT);
    projection->discrim = CES_VAR;
    projection->var = (DCEvar*)dcecreate(CES_VAR);
    projection->var->cdfleaf = var;
    projection->var->segments = segments;

    /* We need to assign slices to each segment */
    dimindex = 0; /* point to next subset of slices */
    for(i=0;i<nclistlength(segments);i++) {
	DCEsegment* segment = (DCEsegment*)nclistget(segments,i);
	int localrank = nclistlength(segment->cdfnode->array.dimensions0);
        if(segment->cdfnode->array.stringdim != NULL) localrank++;
        if(segment->cdfnode->array.seqdim != NULL) localrank++;
        segment->rank = localrank;
        for(j=0;j<localrank;j++) {
	    DCEslice* slice = &segment->slices[j];
	    CDFnode* dim = (CDFnode*)nclistget(dimset,dimindex+j);
	    /* make each slice represent the corresponding
               start/count/stride */
	    slice->first = startp[dimindex+j];
	    slice->stride = stridep[dimindex+j];
	    slice->count = countp[dimindex+j];
	    slice->length = slice->count * slice->stride;
	    if(slice->length > dim->dim.declsize)
		slice->length = dim->dim.declsize;
	    slice->stop = (slice->first + slice->length);
	    if(slice->stop > dim->dim.declsize)
		slice->stop = dim->dim.declsize;
	    slice->declsize = dim->dim.declsize;
	}
	segment->slicesdefined = 1;
	segment->slicesdeclized = 1;
	dimindex += localrank;
	ASSERT((dimindex <= ncrank));
    }

    ASSERT((dimindex == ncrank));

#ifdef DEBUG
fprintf(stderr,"buildvaraprojection3: projection=%s\n",
        dumpprojection(projection));
#endif

    if(projectionp) *projectionp = projection;

    nclistfree(path);
    if(ncstat) dcefree((DCEnode*)projection);
    return ncstat;
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
