import subprocess
import time
import os
from tthAnalysis.HiggsToTauTau.jobTools import run_cmd
from tthAnalysis.HiggsToTauTau.sbatchManager import sbatchManager

from config import config

def call_histogram_aggregation_on_cluster_node_with_invalid_input_spec():

    # Prepare

    run_cmd("rm -rf %(temp_dir)s/call_histogram_aggregation_on_cluster_node_with_invalid_input" % config)
    run_cmd("mkdir -p %(temp_dir)s/call_histogram_aggregation_on_cluster_node_with_invalid_input/" % config)


    # Add histograms and run task

    m = sbatchManager()
    m.setWorkingDir('%(cmssw_base)s/src/analysis2mu1b1j/analysis2mu1b1j/test' % config)

    m.hadd_in_cluster(
        inputFiles=[
            '%(fixtures_dir)s/histogram_1.root' % config,
            '%(fixtures_dir)s/histogram_broken.root' % config
        ],
        outputFile='%(temp_dir)s/call_histogram_aggregation_on_cluster_node_with_invalid_input/result.root' % config
    )

    m.waitForJobs()


    # Check result

    root_result_file = '%(temp_dir)s/call_histogram_aggregation_on_cluster_node_with_invalid_input/result.root' % config
    root_file_does_not_exist = not os.path.isfile(root_result_file)

    grepped_error = run_cmd('cat %(temp_dir)s/call_histogram_aggregation_on_cluster_node_with_invalid_input/logs/create__home_%(user)s_tmp__call_histogram_aggregation_on_cluster_node_with_invalid_input_result.root_executable.log | grep "ERROR Some of the input histograms are not valid. Will stop execution."' % config)
    log_does_contain_error = not (grepped_error == '')

    result_successful = root_file_does_not_exist and log_does_contain_error


    # Output result

    if result_successful:
        print('PASSED: HADD on cluster node with invalid input was interrupted as expected')
    else:
        error_reasons = ""

        if not root_file_does_not_exist:
            error_reasons = 'root file should not exist; '

        if not log_does_contain_error:
            error_reasons = error_reasons + 'log file does not contain error; '

        print('FAILED: HADD on cluster node failed silently and this is bad: ' + error_reasons)

    return result_successful
