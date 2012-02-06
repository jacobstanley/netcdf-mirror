/*********************************************************************
 *   Copyright 1993, UCAR/Unidata
 *   See netcdf/COPYRIGHT file for copying and redistribution conditions.
 *   $Header: /upc/share/CVS/netcdf-3/ncgen/genbin.c,v 1.4 2010/05/27 21:34:17 dmh Exp $
 *********************************************************************/

#include "includes.h"
#include <ctype.h>	/* for isprint() */

#ifdef ENABLE_BINARY

#undef TRACE

#ifdef IGNORE
extern List* vlenconstants;
#endif

/* Forward*/
static void genbin_defineattr(Symbol* asym,Bytebuffer*);
static void genbin_definevardata(Symbol* vsym);
static int  genbin_write(Symbol*,Bytebuffer*,int,size_t*,size_t*,...);

#ifdef USE_NETCDF4
static void genbin_deftype(Symbol* tsym);
static void genbin_definespecialattributes(Symbol* var);
#endif

/*
 * Generate C code for creating netCDF from in-memory structure.
 */
void
gen_netcdf(const char *filename)
{
    int stat, ncid;
    int idim, ivar, iatt;
    int ndims, nvars, natts, ngatts;

#ifdef USE_NETCDF4
    int ntyps, ngrps, igrp;
#endif

    Bytebuffer* databuf = bbNew();

    ndims = listlength(dimdefs);
    nvars = listlength(vardefs);
    natts = listlength(attdefs);
    ngatts = listlength(gattdefs);
#ifdef USE_NETCDF4
    ntyps = listlength(typdefs);
    ngrps = listlength(grpdefs);
#endif /*USE_NETCDF4*/

    /* create netCDF file, uses NC_CLOBBER mode */
    cmode_modifier |= NC_CLOBBER;
#ifdef USE_NETCDF4
    if(!usingclassic)
        cmode_modifier |= NC_NETCDF4;
#endif

    stat = nc_create(filename, cmode_modifier, &ncid);
    check_err(stat,__LINE__,__FILE__);
    
    /* ncid created above is also root group*/
    rootgroup->ncid = ncid;

#ifdef USE_NETCDF4
    /* Define the group structure */
    /* walking grdefs list will do a preorder walk of all defined groups*/
    for(igrp=0;igrp<ngrps;igrp++) {
	Symbol* gsym = (Symbol*)listget(grpdefs,igrp);
	if(gsym == rootgroup) continue; /* ignore root group*/
	stat = nc_def_grp(gsym->container->ncid,gsym->name,&gsym->ncid);
	check_err(stat,__LINE__,__FILE__);
    }
#endif

#ifdef USE_NETCDF4
    /* Define the types*/
    if (ntyps > 0) {
	int ityp;
	for(ityp = 0; ityp < ntyps; ityp++) {
	    Symbol* tsym = (Symbol*)listget(typdefs,ityp);
	    genbin_deftype(tsym);
	}
    }
#endif

    /* define dimensions from info in dims array */
    if (ndims > 0) {
        for(idim = 0; idim < ndims; idim++) {
            Symbol* dsym = (Symbol*)listget(dimdefs,idim);
	    stat = nc_def_dim(dsym->container->ncid,
			      dsym->name,
			      dsym->dim.declsize,
			      &dsym->ncid);
	    check_err(stat,__LINE__,__FILE__);
       }
    }

    /* define variables from info in vars array */
    if (nvars > 0) {
	for(ivar = 0; ivar < nvars; ivar++) {
            Symbol* vsym = (Symbol*)listget(vardefs,ivar);
	    if (vsym->typ.dimset.ndims > 0) {	/* a dimensioned variable */
		/* construct a vector of dimension ids*/
		int dimids[NC_MAX_VAR_DIMS];
		for(idim=0;idim<vsym->typ.dimset.ndims;idim++)
		    dimids[idim] = vsym->typ.dimset.dimsyms[idim]->ncid;
		stat = nc_def_var(vsym->container->ncid,
				  vsym->name,
			          vsym->typ.basetype->ncid,
		        	  vsym->typ.dimset.ndims,
				  dimids,
				  &vsym->ncid);
	    } else { /* a scalar */
		stat = nc_def_var(vsym->container->ncid,
				  vsym->name,
			          vsym->typ.basetype->ncid,
		        	  vsym->typ.dimset.ndims,
				  NULL,
				  &vsym->ncid);
	    }
	    check_err(stat,__LINE__,__FILE__);
	}
    }

#ifdef USE_NETCDF4
    /* Collect vlen data*/
#ifdef IGNORE
    bindata_vlenconstants(vlenconstants);
#endif

    /* define special variable properties */
    if(nvars > 0) {
	for(ivar = 0; ivar < nvars; ivar++) {
            Symbol* var = (Symbol*)listget(vardefs,ivar);
	    genbin_definespecialattributes(var);
	}
    }
#endif /*USE_NETCDF4*/

/* define global attributes */
    if(ngatts > 0) {
	for(iatt = 0; iatt < ngatts; iatt++) {
	    Symbol* gasym = (Symbol*)listget(gattdefs,iatt);
	    bbClear(databuf);
	    genbin_defineattr(gasym,databuf);	    
	}
    }
    
    /* define per-variable attributes */
    if(natts > 0) {
	for(iatt = 0; iatt < natts; iatt++) {
	    Symbol* asym = (Symbol*)listget(attdefs,iatt);
	    bbClear(databuf);
	    genbin_defineattr(asym,databuf);
	}
    }

    if (nofill_flag) {
	stat = nc_set_fill(rootgroup->ncid, NC_NOFILL, 0);
	check_err(stat,__LINE__,__FILE__);
    }

    /* leave define mode */
    stat = nc_enddef(rootgroup->ncid);
    check_err(stat,__LINE__,__FILE__);

    /* Load values into those variables with defined data */
    if(nvars > 0) {
        for(ivar = 0; ivar < nvars; ivar++) {
	    Symbol* vsym = (Symbol*)listget(vardefs,ivar);
	    if(vsym->data != NULL) {
	        bbClear(databuf);
		genbin_definevardata(vsym);
	    }
	}
    }
    bbFree(databuf);
}

#ifdef USE_NETCDF4
static void
genbin_definespecialattributes(Symbol* var)
{
    int stat;
    Specialdata* special = &var->var.special;
    if(special->flags & _STORAGE_FLAG) {
        int storage = special->_Storage;
        size_t* chunks = special->_ChunkSizes;
        if(special->nchunks == 0 || chunks == NULL) chunks = NULL;
        stat = nc_def_var_chunking(var->container->ncid,
                                   var->ncid,
                                   (storage == NC_CONTIGUOUS?NC_CONTIGUOUS
                                                            :NC_CHUNKED),
                                   chunks);
        check_err(stat,__LINE__,__FILE__);
    }   
    if(special->flags & _FLETCHER32_FLAG) {
        stat = nc_def_var_fletcher32(var->container->ncid,
                                     var->ncid,
                                     special->_Fletcher32);
        check_err(stat,__LINE__,__FILE__);
    }
    if(special->flags & (_DEFLATE_FLAG | _SHUFFLE_FLAG)) {
        stat = nc_def_var_deflate(var->container->ncid,
                                  var->ncid,
                                  (special->_Shuffle == 1?1:0),
                                  (special->_DeflateLevel >= 0?1:0),
                                  (special->_DeflateLevel >= 0?special->_DeflateLevel
                                                              :0));
        check_err(stat,__LINE__,__FILE__);
    }   
    if(special->flags & _ENDIAN_FLAG) {
        stat = nc_def_var_endian(var->container->ncid,
                                 var->ncid,
                                 (special->_Endianness == NC_ENDIAN_LITTLE?
                                        NC_ENDIAN_LITTLE
                                       :NC_ENDIAN_BIG));
        check_err(stat,__LINE__,__FILE__);
    }   
    if(special->flags & _NOFILL_FLAG) {
        stat = nc_def_var_fill(var->container->ncid,
                                 var->ncid,
		                 (special->_Fill?NC_FILL:NC_NOFILL),
                                 NULL);
        check_err(stat,__LINE__,__FILE__);
    }   
}
#endif /*USE_NETCDF4*/


void
cl_netcdf(void)
{
    int stat;
    stat = nc_close(rootgroup->ncid);
    check_err(stat,__LINE__,__FILE__);
}

#ifdef USE_NETCDF4
/*
Generate type definitions
*/
static void
genbin_deftype(Symbol* tsym)
{
    int i,stat;

    ASSERT(tsym->objectclass == NC_TYPE);
    switch (tsym->subclass) {
    case NC_PRIM: break; /* these are already taken care of*/
    case NC_OPAQUE:
	stat = nc_def_opaque(tsym->container->ncid,
			     tsym->typ.size,
			     tsym->name,
			     &tsym->ncid);
        check_err(stat,__LINE__,__FILE__);	
	break;
    case NC_ENUM: {
        Bytebuffer* datum;
        Datalist* ecdl;
	stat = nc_def_enum(tsym->container->ncid,
			   tsym->typ.basetype->typ.typecode,
			   tsym->name,
			   &tsym->ncid);
        check_err(stat,__LINE__,__FILE__);	
	datum = bbNew();
        ecdl = builddatalist(1);
        dlextend(ecdl); /* make room for one constant*/
	ecdl->length = 1;
	for(i=0;i<listlength(tsym->subnodes);i++) {
	    Symbol* econst = (Symbol*)listget(tsym->subnodes,i);
	    ASSERT(econst->subclass == NC_ECONST);
	    bin_generator->reset(bin_generator,NULL);
	    bbClear(datum);
	    generate_basetype(econst->typ.basetype,&econst->typ.econst,datum,NULL,bin_generator);
	    stat = nc_insert_enum(tsym->container->ncid,
				  tsym->ncid,
				  econst->name,
				  bbContents(datum));
	    check_err(stat,__LINE__,__FILE__);	
	}
	bbFree(datum);
	} break;
    case NC_VLEN:
	stat = nc_def_vlen(tsym->container->ncid,
			   tsym->name,
			   tsym->typ.basetype->ncid,
			   &tsym->ncid);
        check_err(stat,__LINE__,__FILE__);	
	break;
    case NC_COMPOUND:
	stat = nc_def_compound(tsym->container->ncid,
			       tsym->typ.size,			       
			       tsym->name,
			       &tsym->ncid);			       
        check_err(stat,__LINE__,__FILE__);	
	for(i=0;i<listlength(tsym->subnodes);i++) {
	    Symbol* efield = (Symbol*)listget(tsym->subnodes,i);
	    ASSERT(efield->subclass == NC_FIELD);
	    if(efield->typ.dimset.ndims == 0){ 
	        stat = nc_insert_compound(
				tsym->container->ncid,
				tsym->ncid,
				efield->name,
			        efield->typ.offset,
				efield->typ.basetype->ncid);
	    } else {
		int j;
		Bytebuffer* dimbuf = bbNew();
		/* Generate the field dimension constants*/
		for(j=0;j<efield->typ.dimset.ndims;j++) {
		     unsigned int size = efield->typ.dimset.dimsyms[j]->dim.declsize;
		     bbAppendn(dimbuf,(char*)&size,sizeof(size));
		}
	        stat = nc_insert_array_compound(
				tsym->container->ncid,
				tsym->ncid,
				efield->name,
			        efield->typ.offset,
				efield->typ.basetype->ncid,
				efield->typ.dimset.ndims,
				(int*)bbContents(dimbuf));
		bbFree(dimbuf);
	    }
            check_err(stat,__LINE__,__FILE__);	
	}
	break;
    default: panic("definectype: unexpected type subclass");
    }
}
#endif /*USE_NETCDF4*/

static void
genbin_defineattr(Symbol* asym,Bytebuffer* databuf)
{
    grpid = asym->container->ncid,
    varid = (asym->att.var == NULL?NC_GLOBAL : asym->att.var->ncid);
    typid = basetype->ncid;

    list = asym->data;
    len = list->length;

    bin_generator->reset(bin_generator,NULL);
    generate_attrdata(asym,bin_generator);
}


/* Following is patterned after the walk functions in semantics.c */
static void
genbin_definevardata(Symbol* vsym)
{
    if(vsym->data == NULL) return;
    bin_generator->reset(bin_generator,NULL);
    generate_vardata(asym,bin_generator);
}

static int
genbin_write(Symbol* sym, Bytebuffer* memory,
             int rank, size_t* start, size_t* count,...);
{
    int stat = NC_NOERR;

if(rank > 0 && debug > 0) {
    int i;
    fprintf(stderr,"startset = [");
    for(i=0;i<rank;i++)
	fprintf(stderr,"%s%lu",(i>0?", ":""),(unsigned long)start[i]);
    fprintf(stderr,"] ");
    fprintf(stderr,"countset = [");
    for(i=0;i<odom->rank;i++)
	fprintf(stderr,"%s%lu",(i>0?", ":""),(unsigned long)count[i]);
    fprintf(stderr,"]\n");
    fflush(stderr);
}
	
    if(rank == 0) {
	size_t count[1] = {1};
        stat = nc_put_var1(vsym->container->ncid, vsym->ncid, count,
                           bbContents(memory));
    } else {
        stat = nc_put_vara(vsym->container->ncid, vsym->ncid,
                       odom->start, odom->count,
                       bbContents(memory));
    }
    check_err(stat,__LINE__,__FILE__);
    bbClear(memory);
}

#endif /*ENABLE_BINARY*/
