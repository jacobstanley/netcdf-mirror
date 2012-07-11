/* Copyright 2009, UCAR/Unidata and OPeNDAP, Inc.
   See the COPYRIGHT file for more information. */

#include "config.h"

#include "ocinternal.h"
#include <stdio.h>
#include <fcntl.h>

#define PREFIXLEN 8

#define ENVFLAG "OCLOGFILE"

static int ocloginit = 0;
static int oclogging = 0;
static char* oclogfile = NULL;
static FILE* oclogstream = NULL;

/*!\defgroup OClog OClog Management
@{*/

/*!\internal
*/

void
oc_loginit(void)
{
    ocloginit = 1;
    oc_setlogging(0);
    oclogfile = NULL;
    oclogstream = NULL;
    /* Use environment variables to preset oclogging state*/
    /* I hope this is portable*/
    if(getenv(ENVFLAG) != NULL) {
	const char* file = getenv(ENVFLAG);
	oc_setlogging(1);
	oc_logopen(file);
    }
}

/*!
Enable/Disable logging.

\param[in] tf If 1, then turn on logging, if 0, then turn off logging.

\return The previous value of the logging flag.
*/

int
oc_setlogging(int tf)
{
    if(!ocloginit) oc_loginit();
    int was = oclogging;
    oclogging = tf;
    return was;
}

/*!
Specify a file into which to place logging output.

\param[in] file The name of the file into which to place logging output.
If the file has the value NULL, then send logging output to
stderr.

\return zero if the open failed, one otherwise.
*/

int
oc_logopen(const char* file)
{
    if(!ocloginit) oc_loginit();
    if(oclogfile != NULL) {
	fclose(oclogstream);
	free(oclogfile);
	oclogfile = NULL;
	return 0;
    }
    if(file == NULL || strlen(file) == 0) {
	/* use stderr*/
	oclogstream = stderr;
	oclogfile = NULL;
    } else {
	int fd;
	oclogfile = (char*)malloc(strlen(file)+1);
	strcpy(oclogfile,file);
	oclogstream = NULL;
	/* We need to deal with this file carefully
	   to avoid unauthorized access*/
	fd = open(oclogfile,O_WRONLY|O_APPEND|O_CREAT,0600);
	if(fd >= 0) {
	    oclogstream = fdopen(fd,"a");
	} else {
	    free(oclogfile);
	    oclogfile = NULL;
	    oc_setlogging(0);
	    return 0;
	}
    }
    return 1;
}

/*!
Close the logging output file (unless it is stderr).
Logging is still enabled.
*/

void
oc_logclose(void)
{
    if(oclogfile != NULL && oclogstream != NULL) {
	fclose(oclogstream);
	oclogstream = NULL;
	if(oclogfile != NULL) free(oclogfile);
	oclogfile = NULL;
    }
}

/*!
Send logging messages. This uses a variable
number of arguments and operates like the stdio
printf function.

\param[in] tag Indicate the kind of this log message.
\param[in] format Format specification as with printf.
*/

void
oc_log(int tag, const char* format, ...)
{
    va_list args;
    char* prefix;
    if(!oclogging || oclogstream == NULL) return;

    switch (tag) {
    case LOGWARN: prefix = "Warning:"; break;
    case LOGERR:  prefix = "Error:  "; break;
    case LOGNOTE: prefix = "Note:   "; break;
    case LOGDBG:  prefix = "Debug:  "; break;
    default:
        fprintf(oclogstream,"Error:  Bad log prefix: %d\n",tag);
	prefix = "Error:  ";
	break;
    }
    fprintf(oclogstream,"%s:",prefix);

    if(format != NULL) {
      va_start(args, format);
      vfprintf(oclogstream, format, args);
      va_end( args );
    }
    fprintf(oclogstream, "\n" );
    fflush(oclogstream);
}

/*!
Send arbitrarily long text as a logging message.
Each line will be sent using oc_log with the specified tag.

\param[in] tag Indicate the kind of this log message.
\param[in] text Arbitrary text to send as a logging message.
*/

void
oc_logtext(int tag, const char* text)
{
    char line[1024];
    size_t delta = 0;
    const char* eol = text;

    if(!oclogging || oclogstream == NULL) return;

    while(*text) {
	eol = strchr(text,'\n');
	if(eol == NULL)
	    delta = strlen(text);
	else
	    delta = (eol - text);
	if(delta > 0) memcpy(line,text,delta);
	line[delta] = '\0';
	fprintf(oclogstream,"        %s\n",line);
	text = eol+1;
    }
}

/**@}*/
