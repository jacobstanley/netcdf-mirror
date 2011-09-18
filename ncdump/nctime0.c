/*********************************************************************
 *   Copyright 2008, University Corporation for Atmospheric Research
 *   See netcdf/COPYRIGHT file for copying and redistribution conditions.
 *   $Id: nctime.c,v 1.9 2010/05/05 22:15:39 dmh Exp $
 *********************************************************************/

/* 
 * This code was extracted with permission from the CDMS time
 * conversion and arithmetic routines developed by Bob Drach, Lawrence
 * Livermore National Laboratory as part of the cdtime library.  Russ
 * Rew of the UCAR Unidata Program made changes and additions to
 * support the "-t" option of the netCDF ncdump utility, including a
 * 366-day climate calendar.
 *
 * For the complete time conversion and climate calendar facilities of
 * the CDMS library, get the original sources from LLNL.
 */

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>
#include "utils.h"
#include "nccomps.h"
#include "dumplib.h"		/* for sbuf_... prototypes */
#include "ncdump.h"		/* for fspec_t def */
#include "vardata.h"
#include "nctime0.h"


static struct {
    size_t nbnds;		/* number of bounds variables */
    bounds_node_t *first;
} bounds_list;

extern fspec_t formatting_specs; /* set from command-line options */

/* rkr: added bounds functions to detect bounds variables of time variables */
void
bounds_add(char *bounds_name, int ncid, int varid) {
    bounds_node_t *bnode = emalloc(sizeof(bounds_node_t) + 1);
    bounds_list.nbnds++;
    bnode->ncid = ncid;
    bnode->varid = varid;
    bnode->bounds_name = strdup(bounds_name);
    bnode->next = bounds_list.first;
    bounds_list.first = bnode;
}

/* Check for optional "calendar" attribute and return specified
 * calendar type, if present. */
cdCalenType
calendar_type(int ncid, int varid) {
    int ctype;
    int stat;
    ncatt_t catt;
    static struct {
	char* attname;
	int type;
    } calmap[] = {
	{"gregorian", cdMixed},
	{"standard", cdMixed}, /* synonym */
	{"proleptic_gregorian", cdStandard},
	{"noleap", cdNoLeap},
	{"no_leap", cdNoLeap},
	{"365_day", cdNoLeap},	/* synonym */
	{"allleap", cd366},
	{"all_leap", cd366},	/* synonym */
	{"366_day", cd366},	/* synonym */
	{"360_day", cd360},
	{"julian", cdJulian},
	{"none", cdClim}	/* TODO: test this */
    };
#define CF_CAL_ATT_NAME "calendar"
    int ncals = (sizeof calmap)/(sizeof calmap[0]);
    ctype = cdMixed;  /* default mixed Gregorian/Julian ala udunits */
    stat = nc_inq_att(ncid, varid, CF_CAL_ATT_NAME, &catt.type, &catt.len);
    if(stat == NC_NOERR && catt.type == NC_CHAR && catt.len > 0) {
	char *calstr = (char *)emalloc(catt.len + 1);
	int itype;
	NC_CHECK(nc_get_att(ncid, varid, CF_CAL_ATT_NAME, calstr));	
	calstr[catt.len] = '\0';
	for(itype = 0; itype < ncals; itype++) {
	    if(strncmp(calstr, calmap[itype].attname, catt.len) == 0) {
		ctype = calmap[itype].type;
		break;
	    }
	}
	free(calstr);
    }
    return ctype;
}

boolean
is_bounds_var(char *varname, int *pargrpidp, int *parvaridp) {
    bounds_node_t *bp = bounds_list.first;
    for(; bp; bp = bp->next) {
	if(STREQ(bp->bounds_name, varname)) {
	    *pargrpidp = bp->ncid;
	    *parvaridp = bp->varid;
	    return true;
	}
    }
    return false;
} 

/* Return true only if this is a "bounds" attribute */
boolean
is_bounds_att(ncatt_t *attp) {
    if(attp->type == NC_CHAR && attp->valgp && STREQ((char *)attp->name, "bounds")) {
	return true;
    }
#ifdef USE_NETCDF4
    if(attp->type == NC_STRING && attp->valgp && STREQ((char *)attp->name, "bounds")) {
	return true;
    }
#endif /* USE_NETCDF4 */
    return false;
}

/* Insert info about a bounds attribute into bounds list, so we can
 * later determine which variables are bounds variables for which
 * other variables.  att must be a variable "bounds" attribute.  */
void
insert_bounds_info(int ncid, int varid, ncatt_t att) {
    static boolean uninitialized = true;
    if(uninitialized) {
	bounds_list.nbnds = 0;
	bounds_list.first = NULL;
    }
    assert(is_bounds_att(&att));
    bounds_add(att.valgp, ncid, varid);
}

void
get_timeinfo(int ncid1, int varid1, ncvar_t *vp) {
    ncatt_t uatt;		/* units attribute */
    int nc_status;		/* return from netcdf calls */
    char *units;
    int ncid = ncid1;
    int varid = varid1;

    vp->has_timeval = false; /* by default, turn on if criteria met */
    vp->timeinfo = 0;
    vp->is_bnds_var = false;
    /* for timeinfo, treat a bounds variable like its "parent" time variable */
    if(is_bounds_var(vp->name, &ncid, &varid)) {
	vp->is_bnds_var = true;
    }

    /* time variables must have appropriate units attribute or be a bounds variable */
    nc_status = nc_inq_att(ncid, varid, "units", &uatt.type, &uatt.len);
    if(nc_status == NC_NOERR && uatt.type == NC_CHAR) { /* TODO: NC_STRING? */
	units = emalloc(uatt.len + 1);
	NC_CHECK(nc_get_att(ncid, varid, "units", units));
	units[uatt.len] = '\0';
	/* check for calendar attribute (not required even for time vars) */
	vp->timeinfo = (timeinfo_t *)emalloc(sizeof(timeinfo_t));
	memset((void*)vp->timeinfo,0,sizeof(timeinfo_t));
	vp->timeinfo->calendar = calendar_type(ncid, varid);
	/* Parse relative units, returning the unit and base component time. */
 	if(cdParseRelunits(vp->timeinfo->calendar, units, 
			   &vp->timeinfo->unit, &vp->timeinfo->origin) != 0) {
	    /* error parsing units so just treat as not a time variable */
	    free(vp->timeinfo);
	    free(units);
	    vp->timeinfo = NULL;
	    return;
	}
	/* Currently this gets reparsed for every value, need function
	 * like cdRel2Comp that resuses parsed units? */
	vp->timeinfo->units = strdup(units);
	vp->has_timeval = true;
	free(units);
    }
    return;
}

/* print_att_times 
 * by Dave Allured, NOAA/PSD/CIRES.  
 * This version supports only primitive attribute types; do not call
 * for user defined types.  Print interpreted, human readable (ISO)
 * time strings for an attribute of a CF-like time variable.
 *
 * Print strings as CDL comments, following the normal non-decoded
 * numeric values, which were already printed by the calling function.
 * In the following example, this function prints only the right hand
 * side, starting at the two slashes:
 *
 *    time:actual_range = 51133., 76670. ; // "1940-01-01", "2009-12-01"
 *
 * This function may be called for ALL primitive attributes.
 * This function qualifies the attribute for numeric type and
 * inheriting valid time attributes (has_time).  If the attribute
 * does not qualify, this function prints nothing and safely
 * returns.
 *
 * This function interprets and formats time values with the SAME
 * methods already used in ncdump -t for data variables.
 *
 * This version has special line wrapping rules:
 *
 * (1) If the attribute has one or two values, the time strings are
 *     always printed on the same line.
 *
 * (2) If the attribute has three or more values, the time strings
 *     are always printed on successive lines, with line wrapping
 *     as needed.
 *
 * Assume: Preceeding call to pr_att_valgs has already screened
 * this attribute for valid primitive types for the current netcdf
 * model (netcdf 3 or 4).
 */

void
print_att_times(
    int ncid,
    int varid,			/* parent var ID */
    ncatt_t att			/* attribute structure */
    )
{
    nc_type type = att.type;	/* local copy */
    boolean wrap;
    boolean first_item;

    ncvar_t var;		/* fake var structure for the att values; */
				/* will add only the minimum necessary info */

/* For common disqualifications, print nothing and return immediately. */

    if (type == NC_CHAR || type == NC_STRING)	/* must be numeric */
	return;

    if (varid == NC_GLOBAL)	/* time units not defined for global atts */
	return;

    assert (att.len > 0);	/* should already be eliminated by caller */

#ifdef USE_NETCDF4
    assert ( type == NC_BYTE   || type == NC_SHORT  || type == NC_INT
          || type == NC_FLOAT  || type == NC_DOUBLE || type == NC_UBYTE
          || type == NC_USHORT || type == NC_UINT   || type == NC_INT64
          || type == NC_UINT64 );
#else   /* NETCDF3 */
    assert ( type == NC_BYTE   || type == NC_SHORT  || type == NC_INT
          || type == NC_FLOAT  || type == NC_DOUBLE );
#endif

/* Get time info from parent variable, and qualify. */

    memset((void*)&var,0,sizeof(var));	/* clear the fake var structure */
    get_timeinfo(ncid, varid, &var);	/* sets has_timeval, timeinfo members */
    
    if (var.has_timeval) {		/* no print unless time qualified */

/* Convert each value to ISO date/time string, and print. */
	
	size_t iel;				     /* attrib index */
	const char *valp = (const char *)att.valgp;  /* attrib value pointer */
	safebuf_t *sb = sbuf_new();		/* allocate new string buffer */
#ifdef NOTUSED
        int func;				/* line wrap control */
#endif
	int separator = ' ';			/* default between data and time */
	if(formatting_specs.iso_separator)
	    separator = 'T';
        
	var.type = att.type;		/* insert attrib type into fake var */

	for (iel = 0; iel < att.len; iel++) {
	    nctime_val_tostring(&var, sb, (void *)valp);  /* convert to str. */
	    valp += att.tinfo->size;	/* increment value pointer, by type */
	    if (iel < att.len - 1)	/* add comma, except for final value */
		sbuf_cat(sb, ",");

            first_item = (iel == 0);	/* identify start of list */
            
            wrap = (att.len > 2);	/* specify line wrap variations:     */
					/* 1 or 2 values: keep on same line, */
					/* more than 2: enable line wrap     */

            lput2 (sbuf_str(sb), first_item, wrap);
            				/* print string in CDL comment, */
            				/* with auto newline            */
	}

        sbuf_free(sb);			/* clean up */

	if(var.timeinfo->units)		/* clean up from get_timeinfo */
	    free(var.timeinfo->units);
	free(var.timeinfo);
    }
}
