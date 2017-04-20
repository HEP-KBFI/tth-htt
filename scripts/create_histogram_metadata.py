from tthAnalysis.HiggsToTauTau.commands import *
from tthAnalysis.HiggsToTauTau.jobTools import run_cmd

def main():
    histogram = sys.argv[1]
    metadata_file = histogram + '.metadata'
    metadata_txt = get_histogram_metadata(histogram)
    run_cmd("echo %s > %s" % (metadata_txt, metadata_file_file))

    print("Created metadata file %s with contents: \n%s" % (metadata_file, metadata_txt))

main()
