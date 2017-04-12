from tthAnalysis.HiggsToTauTau.jobTools import run_cmd
import time, os, sys, ROOT

def main():
    input_histograms = sys.argv[1:len(sys.argv)]
    polling_delay    = 1 # in seconds
    polling_cmd      = "fuser {filename}"
    filesize_cmd     = 'stat --printf="%s" {filename}' # use format method!

    print('check_that_histograms_are_valid.py %s' % input_histograms)

    for input_histogram in input_histograms:

        if not os.path.isfile(input_histogram):
            print('ERROR: root input file is missing: %s' % input_histogram)
            sys.exit(1)

        is_file_ready = False
        while not is_file_ready:
            stdout, stderr = run_cmd(polling_cmd.format(filename = input_histogram), return_stderr = True)
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

        # or go with filesize_cmd ?
        if os.path.getsize(input_histogram) < 5:
            print('ERROR: root input file is too small: %s' % input_histogram)
            sys.exit(1)

        root_tfile = ROOT.TFile(input_histogram, "read")

        if root_tfile.IsZombie(): # THIS IS NOT WORKING :(
            print('ERROR: root input file is broken: %s' % input_histogram)
            sys.exit(1)

        print('File is ok: %s' % input_histogram )

    print('All input files are ok.')
    sys.exit(0)

main()
