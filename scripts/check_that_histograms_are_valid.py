import subprocess
import time
import os
import sys
from tthAnalysis.HiggsToTauTau.jobTools import run_cmd
import ROOT
import sys

def main():
    input_histograms = sys.argv[1:len(sys.argv)]

    print('check_that_histograms_are_valid.py %s' % input_histograms)

    for input_histogram in input_histograms:

        if not os.path.isfile(input_histogram):
            print('ERROR: root input file is missing: %s' % input_histogram)
            sys.exit(1)

        if os.path.getsize(path) < 5:
            print('ERROR: root input file is too small: %s' % input_histogram)
            sys.exit(1)

        root_tfile = ROOT.TFile(input_histogram, "read")

        if root_tfile.IsZombie(): # THIS IS NOT WORKING :(
            print('ERROR: root input file is broken: %s' % input_histogram)
            sys.exit(1)

        print('All input files are ok.')
        sys.exit(0)

main()
