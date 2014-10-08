#!/usr/bin/perl
# unfortunately involved installer to set up workstaion code including shell settings currently only works for bash shell.
#
# uses a subtroutines file to build a list of work to do. The subroutines are stored in a folder named install. 
# later this could be changed to be named after the script.
# 
# requirements! and assumptions!
#    a working directory, it assumes the current directory is where you started from and 
# that you've checked out/cloned the current version of code from there.
#  
# HAS NOT BEEN TESTED WELL, tests show not much cleanup has been requred for additional test cases. 
# the user running the script has administrative access, IF NOT, will still update shell settings.
# 
use strict;
use warnings;
use POSIX;
use File::Basename;
use Cwd 'abs_path';
use Sys::Hostname;
use File::Find;
use Getopt::Std;
use Getopt::Long;
use Scalar::Util qw(looks_like_number);
use List::MoreUtils qw(uniq);
use lib $ENV{PWD}.'/install';
#use lib split(':',$RADISH_PERL_LIB);
use vars qw($IS_MAC $IS_LINUX $MAIN_DIR $HOSTNAME);
require install::subroutines;
require install::order;
our $DEBUG=30;
$MAIN_DIR=$ENV{PWD};

Getopt::Long::Configure ("bundling", "ignorecase_always");


my %dispatch_table=(); # look up of option function names to function references
my %dispatch_status=();# look up to hold if we've run a function or not.
my %option_list=();    # list of options recognized, built from the dispatch table.
my %options=();        # the options specified on the command line.

CraftOptionDispatchTable(\%dispatch_table,$ENV{PWD}."/install","inst");
#CraftOptionDispatchTable($hash_ref,dir_to_examine,file_prefix_to_use);
#CraftOptionDispatchTable(\%dispatch_table,$ENV{PWD}.'/install'); 

my $opt_eval_string=CraftOptionList( \%dispatch_table, \%option_list);
# option_list isnt really used for this, this should be updated to make it optional

### debug check to seee we got functions for each option
# print ("Option_list is:\n");
# foreach ( keys %option_list ) {
#     #print "option:".$_."-> ".$option_list{$_}."\n";
#     print "option:".$_."\t\n";
# }

##################
## work directly on the dispatch table, but this doesnt suit our use case
## we want a default of do all options
## this is equiavalent to  GetOptions ('opt=i' => \&handler);
# if ( !GetOptions(%dispatch_table ) ) { 
#     print("Option error\n");
#     exit;
# }
##################


###
# get system information.
###
$HOSTNAME=hostname;
our $ARCH=`uname -m`; chomp($ARCH);
my @alist = split(/\./, $HOSTNAME) ;
$HOSTNAME=$alist[0];
#our $IS_MAC=0;#false always for now, should fix this to find linux
#our $IS_LINUX=0;
$IS_MAC=0;#false always for now, should fix this to find linux
$IS_LINUX=0;
our $OS="$^O\n";
if ( $OS =~ /^darwin$/x ) {
    $IS_MAC=1;
} elsif( $OS =~ /^linux$/x )  { 
    $IS_LINUX=1;
} else {
    #unix windows or something else, we should probalby quit here.
    warn("Unexpected OS, good luck!");
}
###
# get user information
###
our $DATA_HOME;
our $SHELL    = basename($ENV{SHELL});
our $WKS_HOME = dirname(abs_path($0));
our $HOME=$ENV{HOME};
#wks_home= /volumes/workstation_home/software
#if hostname is cluster
if ( !$IS_MAC ) {
   $DATA_HOME="$WKS_HOME/../data"
} else {
#    print("Mac system, perhaps the old install.mac.pl would be more appropriate\n");
   $DATA_HOME="/Volumes/workstation_data/data";
}
# admin_group is allowed to modifiy any files and permissions, 
# edit_group  is allowed to edit code and run recon/workstation code.
# user_group  is allowed to run recon/workstation code. 
our $ADMIN_GROUP="admin";
our $EDIT_GROUP;
our $USER_GROUP="ipl";
if ( $IS_MAC ) {
    $EDIT_GROUP="recon" 
}else {
    $EDIT_GROUP="coders" 
}
our $IS_ADMIN=0;
our $IS_CODER=0;
our $IS_USER=0;
###
# gather options
###
my $first_stage='';
my $last_stage ='';
my $only_stage ='';

my %optlist=(
		  "admin_group=s" => \$ADMIN_GROUP,
		  "WKS_HOME=s" => \$WKS_HOME,
		  "start_at=s" => \$first_stage,
		  "first_stage" => \$first_stage,
		  "stop_at=s" => \$last_stage,
                  "debug:i" => \$options{"debug"},
		  "last_stage=s" => \$last_stage,
		  "help" => \$options{"help"},
		  "h" => \$options{"help"},
		  "only=s" => \$only_stage,
		  "only_stage=s" => \$only_stage,
		  "only_step=s" => \$only_stage,
		  "print_order" => \$options{"print_order"},
    );
### display option_list and optlist

if ( $DEBUG > 90 ) { 
    for my $key ( keys %option_list ) { 
	eval $option_list{$key}.'=1;';
	$option_list{$key}=eval $option_list{$key};
	print ("k:$key <= $option_list{$key}\n");
    }
    for my $key ( keys %optlist ) { 
	print ("k:$key <= $optlist{$key}\n");
    }
}

# opt_eval_string is gatherd from CraftOptionList function, 
if ( 1 ) { #help only options
    # insert option_list into optlist
    #sr=&$scalar ? 
    #s_ref=\$scalar
    for my $key ( keys %option_list ) { 
	# ignore skip_ keys, and cut off any =.*, or :.* from the key
	# setting optlist{key}=\options{key_noextra};
	if ( 1 ) {
	    my ($k_ne,$e) = $key =~ /^(.+)(?:([=:].+))?$/x;
	    $optlist{$key}=\$options{$k_ne};
	    if( defined $e ) {
		print ("rm ex $e\n") if($DEBUG > 50);
	    }
	}else{
	    $optlist{$key}=eval $option_list{$key};
	}
	print ("k:$key <= $option_list{$key} <=") if($DEBUG > 50);
	print ("\t $optlist{$key}\n") if($DEBUG > 50);
    }
    if ( !GetOptions( %optlist,
	 )
	) { 
	print("Option error:\n$!");
	if ( $DEBUG>50 ) {
	    for my $key ( keys %optlist ) { 
		print ("k:$key <= $optlist{$key}\n");
	    }
	}
    	exit;
    }
} else {
    print("OPT EVAL STRING VERSION\n");
    print("opt_eval_string:$opt_eval_string\n");
    if ( !GetOptions( eval $opt_eval_string,
		      %optlist,
	 )
	) { 
	print("Option error:\n$!");
	exit;
    }
}

if ( length($only_stage)>0) { 
    $last_stage=$only_stage;
    $first_stage=$only_stage;
}

###
# get the options from the user
###
# wholly unnecessary due to using the order array
#my @force_on=();  # force on is a reprocess option, implying to reprocess that scetion. This is actually handled by the given section where skip just doesnt run a section.

my @input_order=();
for my $opt ( keys %options)  {
    if ( $opt =~ m/^skip_(.*)$/x  ){ # if option is true, and called skip_ , do nothing else
	print("-ignore-$opt\n") unless (  $DEBUG<95 ) ;
    } else {
	# ( $options{$opt} ) && 
	print ("force_processing for $opt") unless ( ( $DEBUG<25 ) && ( $opt !~ m/^skip_(.*)$/x ) );
	if( ($options{$opt} ) ){
	    push(@input_order,$opt);
	    print (":on.") unless ( $DEBUG<25 );
	    #print("\t$opt FORCE ON\n");
	    if ( defined $dispatch_table{$opt} ) {
		print("\n\tFUNCT_CALL:$dispatch_table{$opt}");
	    } else {
		print("\tNOT IN DISPATCH(is not funct?)!");
	    }
	} else {
	    print(":off.") unless (  $DEBUG<25 ) ;
	}
	print("\n") unless (  $DEBUG<25 ) ; 
    }
}
print("input_order=\n\t".join(",\n\t",@input_order)."\n") if ( $DEBUG > 25 ) ;

if ( 0 ) {
    for my $opt ( keys %options)  {
	print ("force_processing for $opt") unless ( ( $DEBUG<25 ) && ( $opt !~ m/^skip_(.*)$/x ) );
	if ( ( $options{$opt} ) && ( $opt =~ m/^skip_(.*)$/x ) ){ # if option is true, and called skip_ , do nothing else
	}elsif( ($options{$opt} ) ){
#	push @force_on,$opt;
	    print (" on: $1\n")unless ( $DEBUG<25 );;
	} else {
	    print("\n") unless (  $DEBUG<25 ) ;
	}
	
	for my $opt ( keys %options)  {
	    if ($opt =~ m/^skip_(.*)$/x ) {}
	    elsif($options{$opt}) {
		print ("$opt force!\n");
		if ( defined $dispatch_table{$opt} ) {
		    print("\tFUNCT_CALL:$dispatch_table{$opt}\n");
		} 
	    }
	}
    }
}
# if allowed to check.
#my $name=getpwuid( $< ) ;
#print ("My name is $name\n");
# using the id field, check for groups, $ADMIN_GROUP, $EDIT_GROUP, and $USER_GROUP.

#check install.pl is in wks_home to make sure we're running in right dir.
# ... later
# svn info to check installpl location.

###
# get run order
###
#my @order_new = OptionOrder("inst");# alternateive way to get order
my @order = OptionOrder("install/inst-order.txt");# could make this text file an option later....
# set all known elements of order to 1 in dispatch_status for found.
my @o_temp=@order;

### 
# add our input order to our order (gotta make sure unique)
###
# save loaded order to o_temp,
# set order to the input order.
# for each element of o_temp, add to order if not exist
@order=@input_order;
foreach (@o_temp ){
    my $reg=join('|',@order);
    if  ( $_ !~ m/^($reg)$/x ){
	push(@order,"$_");
    }

}


@o_temp=();
for my $opt ( @order) {
    if ( defined(  $dispatch_table{$opt} &&! $options{"skip_".$opt} ) ) {
        $dispatch_status{$opt}=1;#serving as an is found count.
	push (@o_temp,$opt);
    } elsif ( $options{"skip_".$opt} ){
	print("force off $opt\n");
    } else {
	print("stage $opt not available, perhaps old entries still in inst-order.txt or this is an option from main\n");
    }
}

# check that all keys of dispatch_table have an entry in dispatch_status, add any that do not to the order array and set 0 status for all.
@order=@o_temp;
for my $key ( sort( keys( %dispatch_table ) ) ) {
    print ("finding $key in order\n");
    if ( ! defined $dispatch_status{$key} &&! $options{"skip_".$key} ){
	push @order, $key;
	print("\t missing, now added.\n");
    }
    $dispatch_status{$key}=0;
}


@o_temp=();
for my $opt ( @order) {
    if ( ( $opt ne $last_stage ) || ( $#o_temp>0 ) ) {
	push(@o_temp,$opt) ;
    } elsif ( $opt eq $first_stage ) {
	push(@o_temp,$opt);
    } elsif ($opt eq $last_stage) {
	push(@o_temp,$opt);
	#last;
    } else {
	print ( "skip $opt\n"); 
    }
}

# remove any entries in order array before the first stage.
while($order[0] ne $first_stage && length( $first_stage) && $#order>=0 ) {
    my $opt=shift @order;
    print("removeing $opt becauase: not after requested first $first_stage.\n");
}
# remove any entries in order array after the last stage
while($order[$#order] ne $last_stage && length ($last_stage) && $#order>=0 ) {
    my $opt=pop @order;
    print("removeing $opt becauase: after requested last $last_stage.\n");
}
###
# run the installer stages
###
# using the @order variable, 
# run each function of dispatch table, pass each function the value of $option{funct_name}
# storting the output status to dispatch_status
# 
if ( ! -f "$MAIN_DIR/.gitignore" ) {
    FileAddText("$MAIN_DIR/.gitignore",".gitignore\n");
}

if ( defined $options{"help"} ) {
    print ("help settings for $0\n");
    foreach (keys %optlist,sort(uniq(keys %options))) {
    #foreach ((keys %options)) {
	if (! defined $options{$_} ) {
	    $options{$_}='';
	}
	    
	print("\t$_ $options{$_}\n");
    }
	   
    exit 0 ;
}
if ( defined $options{"print_order"} ){
    
    print("working order is :\n\t".join("\n\t",@order )."\n");
    exit 0 ;
}
ProcessStages(\%dispatch_table,\%dispatch_status,\%options,\@order);


print ("$0 Completed.\n");
exit;
#quit;
stop();
error();



print("use source ~/.bashrc to enable settings now, otherwise quit terminal or restart computer\n");

