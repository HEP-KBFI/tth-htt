import subprocess
import time
import os
import sys
from tthAnalysis.HiggsToTauTau.jobTools import run_cmd
import ROOT
import sys

sys.exit(1)

def main():
    input_histograms = sys.argv[1:len(sys.argv)]

    print('check_that_histograms_are_valid.py %s' % input_histograms)

    for input_histogram in input_histograms:
        root_tfile = ROOT.TFile(input_histogram, "read")

        if root_tfile.IsZombie():
            print('ERROR: root input file is broken: %s' % input_histogram)
            sys.exit(1)

        print('All input files are ok.')

        sys.exit(0)

main()
