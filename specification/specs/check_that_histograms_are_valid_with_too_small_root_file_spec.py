from tthAnalysis.HiggsToTauTau.jobTools import run_cmd

from config import config

def check_that_histograms_are_valid_with_too_small_root_file_spec():

    # Prepare

    too_small_histogram = "%(fixtures_dir)s/histogram_too_small.root" % config

    histograms = [
        "%(fixtures_dir)s/histogram_1.root" % config,
        too_small_histogram
    ]

    # Run task

    command = 'python %(cmssw_base)s/src/tthAnalysis/HiggsToTauTau/scripts/check_that_histograms_are_valid.py' % config
    command_arguments = " ".join(histograms)
    command_with_arguments = command + " " + command_arguments + "; echo EXIT_STATUS_WAS: $?;"

    result = run_cmd(command_with_arguments)

    # Check result

    if result.find('ERROR: root input file is too small (2 bytes): %s' % too_small_histogram) == -1:
        print('Ouput must contain error information what file was too small')
        return False

    if result.find('EXIT_STATUS_WAS: 1') == -1:
        print('Exit status must be 1 if file was too small')
        return False

    return True
