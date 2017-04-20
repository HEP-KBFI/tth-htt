from tthAnalysis.HiggsToTauTau.jobTools import run_cmd

from config import config

def check_that_histograms_are_valid_spec():

    # Prepare

    valid_histograms = [
        "%(fixtures_dir)s/histogram_1.root" % config,
        "%(fixtures_dir)s/histogram_2.root" % config
    ]

    # Run task

    command = 'python %(scripts_dir)s/check_that_histograms_are_valid.py' % config
    command_arguments = " ".join(valid_histograms)
    command_with_arguments = command + " " + command_arguments + "; echo EXIT_STATUS_WAS: $?;"

    result = run_cmd(command_with_arguments)

    # Check result

    if result.find('All input files are ok.') == -1:
        print('Result must contain string "All input files are ok."')
        return False

    if result.find('EXIT_STATUS_WAS: 0') == -1:
        print('Exit status was not 0')
        return False

    return True
