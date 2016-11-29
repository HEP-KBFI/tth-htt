import subprocess
import time
import os
from tthAnalysis.HiggsToTauTau.jobTools import run_cmd
from tthAnalysis.HiggsToTauTau.sbatchManager import sbatchManager

from config import config

def run_test():

    # Prepare

    run_cmd("rm -rf /home/%(user)s/tmp/call_histogram_aggregation_on_cluster_node" % config)
    run_cmd("mkdir -p /home/%(user)s/tmp/call_histogram_aggregation_on_cluster_node/" % config)


    # Add histograms and run task

    m = sbatchManager()
    m.setWorkingDir('/home/%(user)s/VHbbNtuples_7_6_x/CMSSW_7_6_3/src/analysis2mu1b1j/analysis2mu1b1j/test' % config)

    m.hadd_on_cluster_node(
        input_histograms=[
            '/home/%(user)s/VHbbNtuples_7_6_x/CMSSW_7_6_3/src/tthAnalysis/HiggsToTauTau/specs/fixtures/histogram_1.root' % config,
            '/home/%(user)s/VHbbNtuples_7_6_x/CMSSW_7_6_3/src/tthAnalysis/HiggsToTauTau/specs/fixtures/histogram_2.root' % config
        ],
        output_histogram='/home/%(user)s/tmp/call_histogram_aggregation_on_cluster_node/result.root' % config,
        output_dir='/home/%(user)s/tmp/call_histogram_aggregation_on_cluster_node/' % config
    )

    m.waitForJobs()


    # Check result

    root_result_file = '/home/%(user)s/tmp/call_histogram_aggregation_on_cluster_node/result.root' % config
    result_successful = os.path.isfile(root_result_file)


    # Output result

    if result_successful:
        print('HADD on cluster node worked')
    else:
        print('HADD on cluster node failed')

    return result_successful


run_test()
