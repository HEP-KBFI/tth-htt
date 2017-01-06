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

    output_histogram_events_total_count = get_events_count(output_histogram)
    input_histograms_events_counts = []

    for input_histogram in input_histograms:
        input_histograms_events_count = get_events_count(input_histogram)
        input_histograms_events_counts.append(input_histograms_events_count)

    input_histograms_events_total_count = sum(input_histograms_events_counts)

    if abs(output_histogram_events_total_count - input_histograms_events_total_count) < 2.0:
        print('Output histogram event count is same as input histograms event counts sum (%s and %s)' % (output_histogram_events_total_count, input_histograms_events_total_count))
        sys.exit(0)
    else:
        print('ERROR: count(output_histogram.events) != count(input_histograms.events) (%s and %s)' % (output_histogram_events_total_count, input_histograms_events_total_count))
        sys.exit(1)

def get_events_count(root_file):
    f = ROOT.TFile(root_file)
    count = f.Get("Count")
    has_entries_count = hasattr(count, 'GetEntries')

    if has_entries_count:
        entries_count = count.GetEntries()
        print('Event count for %s is %s' % (root_file, entries_count))
        return entries_count
    else:
        entries_count = 0.0
        print('Event count for %s is %s, because files does not have count entries' % (root_file, entries_count))
        return entries_count


main()
