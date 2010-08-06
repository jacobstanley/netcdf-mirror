#!/usr/bin/perl

# Initialize
use strict;
use File::Copy;

our $debug=1;

# topdir is top src dir of the netcdf installation
# Assume vsdir == $topdir/win32/NET
our $topdir=$0;
$topdir=~s|(.*)/win32/NET|$1|;
if ($debug > 0) {print "topdir=$topdir\n";}

#define arguments
my $cmd = ($ARGV[0] || "");

my %nullmap = ();

# List directories whose Makefile.am files must be modified
my @mamdirs = (
".",
"include",
"libdispatch",
"libsrc",
"libsrc4",
"libncdap3",
"liblib",
"ncgen3",
"ncgen",
"ncdump",
"nctest",
"nc_test",
);

#The following is a Kludge because perl doe not
# accept nested arrays or hashes.

#The following is a Kludge because perl doe not
# accept nested arrays or hashes.

# map Makefile dir => (project => source files)
my %dir2projects2src = (
"." => "",
"include" => "netcdf \$(include_HEADERS) \$(noinst_HEADERS)",
"libdispatch" => "netcdf \$(libdispatch_la_SOURCES)",
"libsrc" => "netcdf \$(libnetcdf3_la_SOURCES)",
"libsrc4" => "netcdf \$(libnetcdf4_la_SOURCES)",
"libncdap3" => "netcdf \$(libncdap3_la_SOURCES)",
"liblib" => "netcdf \$(libnetcdf_la_SOURCES)",
"ncgen3" => "ncgen3 \$(ncgen3_SOURCES)",
"ncgen" => "ncgen \$(ncgen_SOURCES)",
"ncdump" => "ncdump \$(ncdump_SOURCES);nccopy \$(nccopy_SOURCES)",
"nctest" => "nctest \$(nctest_SOURCES)",
"nc_test" => "nc_test \$(nc_test_SOURCES);large_files large_files.c;quick_large_files quick_large_files.c"
);

my $dir;
foreach $dir (@mamdirs) {
    if(! -e "${dir}/Makefile.am.bak") { copy("${dir}/Makefile.am",
                                             "${dir}/Makefile.am.bak");}
}

if($cmd eq "add") {
    foreach $dir (@mamdirs) {
	my $mam = "$dir/Makefile.am";
	unlink "${mam}";
	copy("${mam}.bak","${mam}");
	open DST, ">>${mam}";
	if($dir eq ".") { #special case
	    print DST "#begin visualstudio\n";
	    print DST "if USE_NETCDF4\n";
	    print DST "USENETCDF4=1\n";
	    print DST "else\n";
	    print DST "USENETCDF4=0\n";
	    print DST "endif\n";
	    print DST "if USE_DAP\n";
	    print DST "USEDAP=1\n";
	    print DST "else\n";
	    print DST "USEDAP=0\n";
	    print DST "endif\n";
	    
	    print DST "VSTUDIODIRS=include \$(DISPATCHDIR) \$(LIBSRC_DIR) \$(ASSEMBLEDIR) \$(NCGEN) \$(NCGEN3) \$(NCDUMP) \$(V2_TEST) \$(NC_TEST_DIR)\n";
	    print DST ".PHONY: visualstudio\n";
	    print DST "visualstudio:\n";
	    print DST "\tperl -w \$(abs_top_srcdir)/win32/NET/vs start\n";
	    print DST "\tfor dir in \$(VSTUDIODIRS); do \$(MAKE) -C \$\$dir visualstudio ; done\n";
	    print DST "\tperl -w \$(abs_top_srcdir)/win32/NET/vs build \$(USENETCDF4) \$(USEDAP)\n";
	    print DST "#end visualstudio\n";
	} else {
	    #undo kludges
	    my $pair;
	    my $tmp = $dir2projects2src{$dir};
	    my @pairs = split(';',$tmp);

	    print DST "#begin visualstudio\n";
	    print DST ".PHONY: visualstudio\n";
	    print DST "visualstudio:\n";
	    # deal with possible multiple projects per directory
	    foreach $pair (@pairs) {
		my @apair = split(' ',$pair);
		my $project = shift @apair;
		my $sources = "@apair";
		if($sources eq "") {next;} # ignore
		# undo kludge
	        print DST "\tperl -w \$(abs_top_srcdir)/win32/NET/vs add $project \${abs_srcdir} \"$sources\"\n";
	    }
            print DST "#end visualstudio\n";
	    close DST;
	}
    }

} elsif($cmd eq "remove") {
    foreach $dir (@mamdirs) {
	my $state="print";
	open SRC, "<${dir}/Makefile.am.bak"
             || die "file not readable: ${dir}/Makefile.am.bak";
	open DST, "+>${dir}/Makefile.am"
             || die "file not writeable: ${dir}/Makefile.am";
	while(<SRC>) {
	    my $line=$_;
	    # remove trailing newlines
	    $line =~ s/[\r\n]//g;
	    if( $_ =~ m/#begin visualstudio/) {
		$state="skip";
		if($debug > 0) {print "xx: $state: skip=|$line|\n";}
		next;
	    }elsif( $_ =~ m/#end visualstudio/) {
		$state="print";
		if($debug > 0) {print "xx: $state: skip=|$line|\n";}
		next;
	    }
	    if( $state eq "skip") {
		if($debug > 0) {print "xx: $state: skip=|$line|\n";}
	    } else {
	        print DST "$line\n";
	    }
        }
	close SRC;
	close DST;
    }        

} elsif($cmd eq "keep") {
    my $dir;
    foreach $dir (@mamdirs) {
        if( -e "${dir}/Makefile.am.bak") { unlink "${dir}/Makefile.am.bak";}
    }

} else {
  die "Unknown command: $cmd"
}

my %dir2projects = (
"." => "netcdf",
"include" => "global",
"libdispatch" => "netcdf",
"libsrc" => "netcdf",
"libsrc4" => "netcdf",
"libncdap3" => "netcdf",
"liblib" => "netcdf",
"ncgen3" => "ncgen3",
"ncgen" => "ncgen",
"ncdump" => "ncdump nccopy",
"nctest" => "nctest",
"nc_test" => "nc_test large_files quick_large_files"
);

exit

