import subprocess
import time
from tthAnalysis.HiggsToTauTau.jobTools import run_cmd
from tthAnalysis.HiggsToTauTau.sbatchManager import sbatchManager

def run_test():

    # Prepare

    run_cmd("rm -rf /home/margusp/tmp/call_histogram_aggregation_on_cluster_node")
    run_cmd("mkdir -p /home/margusp/tmp/call_histogram_aggregation_on_cluster_node/")


    # Add histograms and run task

    m = sbatchManager()
    m.setWorkingDir('/home/margusp/VHbbNtuples_7_6_x/CMSSW_7_6_3/src/analysis2mu1b1j/analysis2mu1b1j/test')

    m.hadd_on_cluster_node(
        input_histograms=[
            '/home/margusp/VHbbNtuples_7_6_x/CMSSW_7_6_3/src/tthAnalysis/HiggsToTauTau/specs/fixtures/histogram_1.root',
            '/home/margusp/VHbbNtuples_7_6_x/CMSSW_7_6_3/src/tthAnalysis/HiggsToTauTau/specs/fixtures/histogram_2.root'
        ],
        output_histogram='/home/margusp/tmp/call_histogram_aggregation_on_cluster_node/result.root'
    )

    m.waitForJobs()


    # Check result

    root_result_file = Path('/home/margusp/tmp/call_histogram_aggregation_on_cluster_node/result.root')
    result_successful = root_result_file.is_file()


    # Output result

    if result_successful:
        print('HADD on cluster node worked')
    else:
        print('HADD on cluster node failed')

    return result_successful


run_test()
