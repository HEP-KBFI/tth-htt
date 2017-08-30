import sys
from tthAnalysis.HiggsToTauTau.commands import *

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
