import subprocess
import time
import os
import sys
from tthAnalysis.HiggsToTauTau.jobTools import run_cmd
from tthAnalysis.HiggsToTauTau.sbatchManager import sbatchManager

def main():
    output_histogram = sys.argv[1]
    input_histograms_list = sys.argv[2]

    print('hadd_in_cluster.py %s %s' % (output_histogram, input_histograms_list))

    if (not (output_histogram and input_histograms_list)):
        print("Usage: hadd_in_cluster.py /full/path/ouput_histogram.root /full/path/input_histograms_list.txt")
        return False

    input_histograms = []

    with file(input_histograms_list) as f:
        input_histograms = f.read().strip().split("\n")

    print("hadd_in_cluster.py will read %s and add them into %s." % (input_histograms, output_histogram))

    m = sbatchManager()
    m.setWorkingDir('/tmp/') # Why SBatch manager even needs to know this?

    m.hadd_on_cluster_node(
        input_histograms=input_histograms,
        output_histogram=output_histogram,
        output_dir=output_histogram.split("/")[0:-1].join("/") # Output to same directory as histogram itself goes (less hassel)
    )

    m.waitForJobs()



main()
