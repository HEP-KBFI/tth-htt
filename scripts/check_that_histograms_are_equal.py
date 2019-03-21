#!/usr/bin/env python

import sys
import ROOT

ROOT.gSystem.ResetSignals()

def get_events_count(root_file):
    f = ROOT.TFile(root_file)
    count = f.Get("analyzedEntries")
    has_entries_count = hasattr(count, 'GetEntries')

    if has_entries_count:
        entries_count = count.GetEntries()
        print("Input file '%s' contains %i analyzed events." % (root_file, entries_count))
        return entries_count
    else:
        entries_count = 0.0
        print("ERROR: Failed to read number of analyzed events in input file '%s' !! Will set number of analyzed events to zero." % root_file)
        return entries_count

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
        print("Event counts (%i) match between output file and sum of input files." % output_histogram_events_total_count)
        sys.exit(0)
    else:
        print("ERROR: Event counts between output file (%i) and sum of input files (%i) does not match !!" % (output_histogram_events_total_count, input_histograms_events_total_count))
        print("output file = '%s'" % output_histogram)
        print("input files = '%s'" % " ".join(input_histograms))
        sys.exit(1)

main()
