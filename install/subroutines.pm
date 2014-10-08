# package install::subroutines;
# use strict;
# use warnings;
# BEGIN { #require Exporter;
#     use Exporter(); #
#     our @ISA = qw(Exporter);
# #    our @Export = qw();
#     our @EXPORT_OK = qw(
# CraftOptionDispatchTable
# CraftOptionList
# );
# }
use warnings;
use strict;
sub CheckFileForPattern {
    my $infile  = shift @_;
    my $pattern = shift @_; 
    my $INPUT;
    my $found=0;
    $infile =~ s/~/$ENV{"HOME"}/gx;# substitute ~ for ${HOME}
    $pattern =~ s|(/\|[ ])|\\$1|gx;
    if (-f $infile && open($INPUT, $infile) ){
	#print("looking up pattern $pattern in file $infile\n");
	while(<$INPUT>) {
	    if (m/$pattern/x) {
#	if ( $_=~/$pattern/) {
#		print;
		$found += 1;
		# exit; # put the exit here, if only the first match is required
	    } else {
		#print "nomatch ".$_;
	    }
	} 
# 	else {
# 	    warn "Error opening $infile : $!\n" ;
# 	    $found =0;
# 	}
	close($INPUT);
	#print ("CheckFile out $found\n");
    } else {
	#$found=-1;
    }
    return $found;
}

sub CraftOptionDispatchTable  {
    my $t_ref = shift @_;
    #my %table = %{$t_ref};
    #my $table = shift @_;
    my $dir= shift @_;
    my $prefix = shift @_;
    if ( ! defined $prefix ) {
	$prefix="inst";
    }
    #my $table = $_[0];
    #my $dir = $_[1];
    #Installer must be called while in the software dirctory.\n 
    opendir(D, "$dir") or die "Can't open directory $dir.\nERROR: $!\n";
    my @list = readdir(D);
    closedir(D);
    for my $file (@list) {
	if ( $file =~ m/^$prefix-(.*)[.]pl$/x){
#	if ( $file =~ m/^$prefix-(.*)(?:-(.*))?[.]pl$/x){
	    my $name=$1;
#	    my $type=$2;
	    my $first_letter=substr($name,0,1);
#	    print("inserting funct reference for $name\n");	    
	    require $file;
	    #eval $name;
	    $t_ref->{$name}= eval '\&$name';
	    
	    # check for colliding names on first letter.
	    my $l_num=0;
	    my $l_txt='';
	    while( defined($t_ref->{$first_letter.$l_txt} ) ) {
		$l_num++;
		$l_txt=$l_num;
		#print ("lbump$l_num\n");
	    }
	    #### all in one... 
	    #$t_ref->{"$name".'|'."$first_letter.$l_txt"}= eval '\&$name';
	    if( !defined($t_ref->{$first_letter.$l_txt} ) ) {
		#print("and $first_letter$l_txt\n");
		#$t_ref->{$first_letter.$l_txt}= eval '\&$name';
	    } else {
		print ( "couldnt get a letter to use for simplified optioning, only assigned by name $name\n");
	    }
	}
    }
#     for my $key ( keys(%{$t_ref}) ){
# 	print("codt::Opt inserted! ( $key )\n");
#     }
#    print("Done craftingoption dispatch\n");
    return;
}

sub CraftOptionList {
# o_ref isnt really used for this, this should be updated to make it optional
# maybe we should take another hash ref for out output placements.
    #my %table = %{shift @_};
    #my %opt_list = %{shift @_};
    my $t_ref = shift @_;# reference to hash of functions, our dispatch table.
    #my %table = %{$t_ref};
    my $o_ref = shift @_; # reference to hash of supported options,
#    my %opt_list = %{$o_ref};
    #print ("OptionList setup\n");
    my $o_string='';
    for my $key ( keys(%{$t_ref}) ){
	#$o_ref->{$key}="$key";
	
	#$o_ref->{$key}='\$options{$key}';
	#$o_ref->{$key}='\\$options{$key}';
	#$o_ref->{$key}='\\\$options{$key}';
	#$o_ref->{$key}='\$key';
	my $type='';
	#if ( $type eq '' ) {
	    $type=':s';
        #} 
	#$o_ref->{"$key$type"}='\$options{'.$key.'}'; # an string to be used with eval... 
	if (1 ) { 
	$o_ref->{"$key$type"}='\$options{skip_'.$key.'}';;
	$o_ref->{"skip_".$key}='\$options{skip_'.$key.'}';
	} else {
	$o_ref->{"$key"}="$type";
	$o_ref->{"skip_".$key}='\$options{skip_'.$key.'}';
	}

	#$o_string="'$key' => ".$o_ref->{$key}.",".$o_string;
	$o_string="'$key$type' => ".'\$options{'.$key.'}'.",".$o_string;#$o_ref->{"$key$type"}
	$o_string="'skip_$key' => ".'\$options{skip_'.$key.'}'.",".$o_string;
	#print("col::Adding to understood opts, $key <- ".$o_ref->{$key}." \n");
    }
    return $o_string;
}

sub ProcessStages {
    print("Begin real work of $0\n");
    # dispatch_ref,output_status_ref, Stage_enableflags_ref,stage_order_arrrayref
    my( $d_ref,$s_ref,$s_flags,$o_ref)= @_;

    die print("No dispatch found, cannot continue\n") unless( defined $d_ref ); 

    my $debug_mode=$s_flags->{"debug"};
#    print ("\n\ntest\n\n");

    if ( ! defined $debug_mode ) {
	print("Debug not set, proceding in quiet mode\n");
	$debug_mode=0;
    } else {
	print ("debug level ".$debug_mode."\n");
    }
    my @order=();
#    print ref( $o_ref) ."\n";
    #pprint  (join(':',@{$o_ref})."\n");
    if ( defined $o_ref ) {
	@order=@{$o_ref};
	print("defined order ".join(':',@order)."\n") unless $debug_mode < 15;
    } else {
	@order=keys %{$d_ref};
	print("undefined order ".join(':',@order)."\n") unless $debug_mode < 15;
    }
    my $first_stage=shift @_;
    my $prefix = shift @_;
    if ( ! defined $prefix ) {
	$prefix="inst";
    }
    
    my $found_first=0;
    for my $opt ( @order ) {
	if ( ! $s_flags->{'skip_'.$opt} ) {
	    # for default behavior optinos{opt} is undefined, for force on it is is 1, for force off it is 0.
	    #print("$d_ref->{$opt}->$s_flags->{$opt}\n"); #put params in here.
	    my $status=$d_ref->{$opt}->($s_flags->{$opt} #put params in here.
		);
	    $s_ref->{$opt}=$status;
	    if (! $status ) {
		print("Stage exit clean:$opt\n");
	    } else {
		print("Stage error:$opt\n");
	    } 
	}
    }
    
    return;   
}

sub FileAddText { 
    my $file=shift @_;
    my $text=shift @_;
    my $FB;
#    print("Writing to $file\n");
    # could add optional $before_pattern $after_pattern to insert before or after some pattern found
    open($FB, '>>', $file) or die "Error opening $file : $!\n";
    print $FB ($text);
    close $FB;
    return;
}

sub FileClear {
    my $file=shift @_;
    my $FB;
    # could add optional $before_pattern $after_pattern to insert before or after some pattern found
    open($FB, '>', $file) or die "Error opening $file : $!\n";
    print $FB ('');
    close $FB;
    return;
}

sub FileRmText {
    my $file  = shift @_;
    my $text = shift @_; 
    my $INPUT;
    my $FB;

    my $found=0;
    $file =~ s/~/$ENV{"HOME"}/gx;# substitute ~ for ${HOME}
    $text =~ s|(/\|[ ])|\\$1|gx;
    if (-f $file && open($INPUT, $file) ){
	open($FB, '>>', "${file}.next") or close($INPUT) and die "Error opening ${file}.next : $!\n";
	#print("looking up text $text in file $file\n");
	while(<$INPUT>) {
	    if (m/^$text$/x) {
#	if ( $_=~/$text/) {
#		print;
		$found += 1;
		# exit; # put the exit here, if only the first match is required
	    } else {
		print $FB ($text);    
	    }
	} 
# 	else {
# 	    warn "Error opening $file : $!\n" ;
# 	    $found =0;
# 	}
	close($INPUT);
	close($FB);
	if ( -f "${file}.bak" ){
	    warn("backup found from last time, error may have occured.\n");
	    unlink("${file}.bak");
	}
	rename($file,"${file}.bak");
	rename("${file}.next",${file}) and unlink("${file}.bak");
	#print ("CheckFile out $found\n");
    } else {
	#$found=-1;
    }
    return $found;
}
sub GetEngineHosts {
    #require ..::shared::pipeline_utilities::civm_simple_util;
    #import ..::shared::pipeline_utilities::civm_simple_util qw/get_engine_hosts/;
    #import ..::shared::pipeline_utilities::civm_simple_util qw/get_engine_hosts/;
    #my @hosts=shared::civm_simple_util::get_engine_hosts('pipeline_settings',90);
#     require shared::pipeline_utilities::civm_simple_util;
#     use civm_simple_util qw(get_engine_hosts);
    #my @hosts=get_engine_hosts('pipeline_settings',90);
        
    my @hosts;
    if ( 1 ) {
	#get all hosts
	#use lib $ENV{PWD}.'/shared/pipeline_utilities/';
	unshift @INC,($ENV{PWD}.'/shared/pipeline_utilities/');
	#require civm_simple_util;
	use autouse civm_simple_util => qw(get_engine_hosts($) ) ;
	@hosts=get_engine_hosts('pipeline_settings');
	
	
	#remove any unresponsive hosts
	my @available_hosts;
	foreach (@hosts) {
	    print;
	    if (SSH_Works($_,-1)){
		#print(" added!\n");
		push(@available_hosts,$_);
	    } else {
		#print(" ignored!\n");
	    }
	}
	
	@hosts=@available_hosts;
    } elsif ( 0 ) {
# 	use warnings;
# 	use strict;
# 	use lib $ENV{PWD}.'/shared/pipeline_utilities/';
# 	#unshift @INC,($ENV{PWD}.'/shared/pipeline_utilities/');
# 	#require civm_simple_util;
# 	use autouse civm_simple_util => qw(get_engine_hosts($) ) ;
# 	@hosts=civm_simple_util::get_engine_hosts('pipeline_settings');
    } else {
#     use warnings;
#     use strict;
#     print("lib is $ENV{PWD}/shared/pipeline_utilities/\n");
#     unshift @INC,($ENV{PWD}.'/shared/pipeline_utilities/');
#     #use civm_simple_util qw(get_engine_hosts) ;
#     #require civm_simple_util;
#     import civm_simple_util qw(get_engine_hosts);
#     @hosts=get_engine_hosts('pipeline_settings');
    }
#     import civm_simple_util qw(get_engine_hosts);
    
    
    #
    #import civm_simple_util qw(get_engine_hosts);
    
    #my @hosts=get_engine_hosts('pipeline_settings');
    
    
    #my @hosts=civm_simple_util::get_engine_hosts('pipeline_settings');
    return @hosts;

#     BEGIN {
# 	use Sys::Hostname;
# 	if ( hostname() eq 'foo.bar.org' ) {
# 	    unshift @INC, ('/alternate/libdir');
# 	} else {
# 	    unshift @INC, ('/default/libdir');
# 	}
#     }

#    require Fcntl;
#    Fcntl->import(qw(O_EXCL O_CREAT O_RDWR));
}

sub SSH_Works($) {
    my ($host)=@_;
    unshift @INC,($ENV{PWD}.'/shared/pipeline_utilities/');
    use autouse ssh_call => qw(works($;$) );
    return works($host,-1);
}

sub isnum ($) {
    no warnings;
    return 0 if $_[0] eq '';
    $_[0] ^ $_[0] ? 0 : 1
}
1;
