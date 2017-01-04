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
    root_file_exists = os.path.isfile(root_result_file)

    grepped_error = run_cmd('cat %(temp_dir)s/call_histogram_aggregation_on_cluster_node_with_invalid_input/logs/create__home_%(user)s_tmp__call_histogram_aggregation_on_cluster_node_with_invalid_input_result.root_executable.log | grep "ERROR: root input file is broken"')
    log_does_not_contain_error = grepped_error == ''

    result_unsuccessful = root_file_exists or log_does_not_contain_error


    # Output result

    if result_unsuccessful:
        error_reasons = ""

        if root_file_exists:
            error_reasons = 'Root file should not exist'

        if log_does_not_contain_error:
            error_reasons = error_reasons + ' and log file does not contain error'

        print('FAILED: HADD on cluster node failed silently and this is bad: ' + error_reasons)

    else:
        print('PASSED: HADD on cluster node with invalid input was interrupted as expected')

    return result_unsuccessful
