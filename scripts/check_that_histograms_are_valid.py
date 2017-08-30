from tthAnalysis.HiggsToTauTau.jobTools import run_cmd
import time, os, sys, ROOT
from tthAnalysis.HiggsToTauTau.commands import *

def main():
    input_files = sys.argv[1:len(sys.argv)]

    print("<check_that_histograms_are_valid.py>: input files = '%s'" % " ".join(input_files))

    run_cmd('sleep 20')

    for input_file in input_files:
        check_that_histogram_is_valid(input_file)

    print("All input files are ok.")
    sys.exit(0)


def check_that_histogram_is_valid(input_file):

    check_that_histogram_exists(input_file)
    check_that_metadata_is_ok(input_file)
    # check_that_histogram_is_ready_for_usage(input_file)
    check_that_histogram_is_big_enough(input_file)
    check_that_histogram_is_not_zombie(input_file)

    print("Input file '%s' is ok." % input_file)


def check_that_histogram_exists(input_file):
    print("<check_that_histogram_exists>: input file = '%s'" % input_file)

    if not os.path.isfile(input_file):
        print("ERROR: Input file '%s' does not exist !!" % input_file)
        sys.exit(1)


def check_that_metadata_is_ok(input_file):
    print("<check_that_metadata_is_ok>: input file = '%s'" % input_file)

    metadata_file = input_file + '.metadata'
    expected_metadata_txt = run_cmd('cat %s' % metadata_file)
    real_metadata_txt = get_histogram_metadata(input_file)

    if real_metadata_txt.find(expected_metadata_txt) == -1:
        print("ERROR: Metadata for input file '%s' does not match expected value !!" % input_file)
        print("computed metadata = '%s'" % real_metadata_txt)
        print("expected metadata = '%s'" % expected_metadata_txt)
        sys.exit(1)


def check_that_histogram_is_ready_for_usage(input_file):
    print("<check_that_histogram_is_ready_for_usage>: input file = '%s'" % input_file)
    
    polling_delay    = 1 # in seconds
    polling_cmd      = "fuser %s" % input_file

    is_file_ready = False
    while not is_file_ready:

        stdout, stderr = run_cmd(polling_cmd, return_stderr = True)

        print("Executed command '%s':" % polling_cmd)
        print("stdout = '%s'" % stdout)
        print("stderr = '%s'" % stderr)

        if not stdout and not stderr:
            # No one uses this file, it's free to use for everyone
            break
        if not stdout and stderr:
            # The file still doesn't exist?
            print(stderr.rstrip('\n'))
            sys.exit(1)
        else:
            # Both stdout and stderr contain text (PID and filename, respectively); wait ...
            time.sleep(polling_delay)

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
