/*********************************************************************
 *   Copyright 2009, UCAR/Unidata
 *   See netcdf/COPYRIGHT file for copying and redistribution conditions.
 *********************************************************************/

#include "includes.h"

/******************************************************/
/* Code for generating char variables etc; mostly
   language independent */
/******************************************************/

static size_t gen_charconstant(Constant*, Bytebuffer*, int fillchar);
static int getfillchar(Datalist* fillsrc);

/*
Matching strings to char variables, attributes, and vlen
constants is challenging because it is desirable to mimic
the original ncgen. The "algorithms" used there have no
simple characterization (such as "abc" == {'a','b','c'}).
So, this rather ugly code is kept in this file
and a variety of heuristics are used to mimic ncgen.

The core algorithm is as follows.
1. Assume we have a set of dimensions D1..Dn,
   where D1 may optionally be an Unlimited dimension.
   It is assumed that the sizes of the Di are all known.
2. Given a sequence of string or character constants
   C1..Cm, our goal is to construct a single string
   whose length is the cross product of D1 thru Dn.
3. For purposes of this algorithm, character constants
   are treated as strings of size 1.
4. Construct Dx = cross product of D1 thru D(n-1).
5. For each constant Ci, add fill characters, if necessary,
   so that its length is a multiple of Dn.
6. Concatenate the modified C1..Cm to produce string S.
7. Add fill characters to S to make its size be a multiple of
   Dn.
8. If S is longer than the Dx * Dn, then truncate
   and generate a warning.

Two other cases:
1. character vlen: char(*) vlen_t.
    For this case, we simply concat all the elements.
2. character attribute.
    For this case, we simply concat all the elements.
*/

void
gen_chararray(Dimset* dimset, Datalist* data, Bytebuffer* databuf, Datalist* fillsrc)
{
    int i,j,ndims;
    int fillchar = getfillchar(fillsrc);
    size_t xproduct,dimproduct;
    size_t unitsize;
    Constant* c;

    ASSERT(bbLength(databuf) == 0);

    ndims = dimset->ndims;
    ASSERT(ndims > 0);

    unitsize = dimset->dimsyms[ndims-1]->dim.declsize;

    xproduct = crossproduct(dimset,0,ndims-1);

    dimproduct = (xproduct * unitsize);

    for(i=0;i<data->length;i++) {
	c = datalistith(data,i);
	ASSERT(!islistconst(c));
	if(isstringable(c->nctype)) {
	    size_t constsize,padsize;
	    constsize = gen_charconstant(c,databuf,fillchar);
	    padsize = constsize % unitsize;
	    for(j=0;j<padsize;j++) bbAppend(databuf,fillchar);
	} else {
	    semwarn(c->lineno,
		     "Encountered non-string and non-char constant in datalist; ignored");
	}
    }
    /* If |databuf| > dimproduct, complain */
    if(bbLength(databuf) > dimproduct) {
	semwarn(data->data[0].lineno,"character data list to long");
    } else {
	/* Pad to size dimproduct size */
	size_t padsize = bbLength(databuf) % dimproduct;
	for(i=0;i<padsize;i++)
	    bbAppend(databuf,fillchar);
    }
}

void
gen_charattr(Datalist* data, Bytebuffer* databuf)
{
    gen_charvlen(data,databuf);
}

void
gen_charvlen(Datalist* data, Bytebuffer* databuf)
{
    int i;
    Constant* c;

    ASSERT(bbLength(databuf) == 0);

    for(i=0;i<data->length;i++) {
	c = datalistith(data,i);
	if(isstringable(c->nctype)) {
	    (void)gen_charconstant(c,databuf,NC_FILL_CHAR);
	} else {
	    semerror(c->lineno,
		     "Encountered non-string and non-char constant in datalist");
	    return;
	}
    }
}

static size_t
gen_charconstant(Constant* con, Bytebuffer* databuf, int fillchar)
{
    /* Following cases should be consistent with isstringable */
    size_t constsize = 1;
    switch (con->nctype) {
    case NC_CHAR:
        bbAppend(databuf,con->value.charv);
        break;
    case NC_BYTE:
        bbAppend(databuf,con->value.int8v);
        break;
    case NC_UBYTE:
        bbAppend(databuf,con->value.uint8v);
        break;
    case NC_STRING:
	constsize = con->value.stringv.len;
        bbCat(databuf,con->value.stringv.stringv);
        bbNull(databuf);
        break;
    case NC_FILL:
        bbAppend(databuf,fillchar);
        break;
    default:
	PANIC("unexpected constant type");
    }
    return constsize;
}

static int
getfillchar(Datalist* fillsrc)
{
    /* Determine the fill char */
    int fillchar = 0;
    if(fillsrc != NULL && fillsrc->length > 0) {
	Constant* ccon = fillsrc->data;
	if(ccon->nctype == NC_CHAR) {
	    fillchar = ccon->value.charv;
	} else if(ccon->nctype == NC_STRING) {	    
	    if(ccon->value.stringv.len > 0) {
	        fillchar = ccon->value.stringv.stringv[0];
	    }
	}
    }
    if(fillchar == 0) fillchar = NC_FILL_CHAR; /* default */
    return fillchar;
}
