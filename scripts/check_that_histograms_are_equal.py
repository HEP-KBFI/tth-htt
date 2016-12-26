import subprocess
import time
import os
import sys
from tthAnalysis.HiggsToTauTau.jobTools import run_cmd
import ROOT
import sys

def main():

    output_histogram = sys.argv[1]
    input_histograms = sys.argv[2:len(sys.argv)]

    print('check_that_histograms_are_equal.py %s %s' % (output_histogram, input_histograms))
    print('check_that_histograms_are_equal.py will always exit with success. TODO')
    sys.exit(0)

main()
