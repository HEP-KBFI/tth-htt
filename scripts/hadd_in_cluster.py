import subprocess
import time
import os
import sys
from tthAnalysis.HiggsToTauTau.jobTools import run_cmd
from tthAnalysis.HiggsToTauTau.sbatchManager import sbatchManager

def main():
    output_histogram_file = sys.argv(1)
    input_histograms_list_file = sys.argv(2)

    if (not (output_histogram_file and input_histograms_list_file)):
        print("Usage: hadd_in_cluster.py /full/path/ouput_histogram.root /full/path/input_histograms_list.txt")
        return False

    input_histograms = []

    with file(input_histograms_list_file) as f:
        input_histograms = f.read().strip().split("\n")

    print("hadd_in_cluster.py will read %s and add them into %s." % (input_histograms, output_histogram))

    m = sbatchManager()
    m.setWorkingDir('/tmp/') # Why SBatch manager even needs to know this?

    m.hadd_on_cluster_node(
        input_histograms=input_histograms,
        output_histogram=output_histogram_file,
        output_dir=output_histogram_file.split("/")[0:-1].join("/") # Output to same directory as histogram itself goes (less hassel)
    )

    m.waitForJobs()



main()
