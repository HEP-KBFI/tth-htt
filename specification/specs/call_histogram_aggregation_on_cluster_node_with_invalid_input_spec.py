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
    result_unsuccessful = not os.path.isfile(root_result_file)


    # Output result

    if result_unsuccessful:
        print('PASSED: HADD on cluster node with invalid input was interrupted as expected')
    else:
        print('FAILED: HADD on cluster node failed silently and this is bad')

    return result_unsuccessful
