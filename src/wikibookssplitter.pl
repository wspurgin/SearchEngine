#! /usr/bin/env perl -w
if ($#ARGV == -1) {
    $outputString = "\nUsage: wikibooksplitter.pl <WikiDump File> [Pages per file] [Max Files] [Output Directory]\n";
    $outputString .= "\tWikiDump File: The path and name of the WikiDump File\n";
    $outputString .= "\tPages Per File: The number of <page> documents per file (default = 1000)\n";
    $outputString .= "\tMax Files: The maximum number of files to generate (default = as many as necessary to run through the input file)\n\n";
    die $outputString;
}

my $maxFiles = 1000;
my $pagesPerFile = 1000;
my $outputDir = "WikiDump";
if ($#ARGV == 0) {
# #Party like a rockstar
} 
if ($#ARGV >= 1) {
    $pagesPerFile = int($ARGV[1]);
} 
if ($#ARGV >= 2) {
    $maxFiles = int($ARGV[2]);
    print $maxFiles."\n";
}
if ($#ARGV >= 3) {
    $outputDir = $ARGV[3];
}

unless (-e $outputDir or mkdir $outputDir) {
    die "\nUnable to create the output directory '".$outputDir."'. Do you have write permission in this folder?\n\n";
}

open (WIKIFILE, $ARGV[0]) or die "\nFailed to open input file".$ARGV[0].". Are you sure the path is correct?\n\n";
my $fileName = '/WikiDumpPart';
my $title = <WIKIFILE>;
my $pageCount = 0;
my $fileCount = 1;


open (OUTPUTFILE, '>'.$outputDir.$fileName.$fileCount.'.xml');
print OUTPUTFILE $title;

while (<WIKIFILE>) {
    if ($pageCount == $pagesPerFile) {
        print OUTPUTFILE '</mediawiki>';
        close(OUTPUTFILE);

        if ($fileCount == $maxFiles) {
            close(WIKIFILE);
            die "\n\nDone! Your files are in the". $outputDir ."folder\n\n";
        }

        $fileCount = $fileCount + 1;
        open (OUTPUTFILE, '>'.$outputDir.$fileName.$fileCount.'.xml');
        print OUTPUTFILE $title;
        $pageCount = 0;

        if ($fileCount % 20 == 0) {
            print "Done with $fileCount files\n";
        }
    }

    print OUTPUTFILE $_; 
    if (index($_, '</page>') != -1) {
        $pageCount = $pageCount + 1;
    }
}

close(WIKIFILE);
close(OUTPUTFILE);

print "\n\nDone! Your files are in the $outputDir folder\n\n";

