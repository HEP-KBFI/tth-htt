from tthAnalysis.HiggsToTauTau.jobTools import run_cmd
from config import config

def check_that_histograms_are_equal_with_unequal_data():

    # Prepare

    output_histogram = "%(fixtures_dir)s/hadd_of_histogram_1_and_broken.root" % config

    input_histograms = [
        "%(fixtures_dir)s/histogram_1.root" % config,
        "%(fixtures_dir)s/histogram_2.root" % config
    ]

    # Run task

    command = 'python %(cmssw_base)s/src/tthAnalysis/HiggsToTauTau/scripts/check_that_histograms_are_equal.py' % config
    command_arguments = output_histogram + " " + " ".join(input_histograms)
    command_with_arguments = command + " " + command_arguments + "; echo EXIT_STATUS_WAS: $?;"

    result = run_cmd(command_with_arguments)

    # Check result

    if result.find('ERROR: count(output_histogram.events) != count(input_histograms.events)') == -1:
        print('Result must contain string "ERROR: count(output_histogram.events) != count(input_histograms.events)"')
        return False

    if result.find('EXIT_STATUS_WAS: 1') == -1:
        print('Exit status was not 1')
        return False

    return True
