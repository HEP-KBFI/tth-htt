#!/usr/bin/env python

from tthAnalysis.HiggsToTauTau.safe_root import ROOT

import sys
import time
import os.path

def main():
    input_files = sys.argv[1:len(sys.argv)]

    print("<check_that_histograms_are_valid.py>: input files = '%s'" % " ".join(input_files))

    time.sleep(20)

    for input_file in input_files:
        check_that_histogram_is_valid(input_file)

    print("All input files are ok.")
    sys.exit(0)


def check_that_histogram_is_valid(input_file):

    check_that_histogram_exists(input_file)
    check_that_histogram_is_big_enough(input_file)
    check_that_histogram_is_not_zombie(input_file)

    print("Input file '%s' is ok." % input_file)


def check_that_histogram_exists(input_file):
    print("<check_that_histogram_exists>: input file = '%s'" % input_file)

    if not os.path.isfile(input_file):
        print("ERROR: Input file '%s' does not exist !!" % input_file)
        sys.exit(1)


def check_that_histogram_is_big_enough(input_file):
    print("<check_that_histogram_is_big_enough>: input file = '%s'" % input_file)
    
    filesize = os.path.getsize(input_file)

    if filesize < 5:
        print("ERROR: Input file '%s' has too small size (%s bytes)" % (input_file, filesize))
        sys.exit(1)
    else:
        print("Input file '%s' has size of %s bytes" % (input_file, filesize))


def check_that_histogram_is_not_zombie(input_file):
    print("<check_that_histogram_is_not_zombie>: input file = '%s'" % input_file)

    root_tfile = ROOT.TFile(input_file, "read")

    if root_tfile.IsZombie(): # MP: THIS IS NOT WORKING :(
        print("ERROR: Input file '%s' is zombie !!" % input_file)
        sys.exit(1)

main()
