import os, uuid
from tthAnalysis.HiggsToTauTau.jobTools import run_cmd
from tthAnalysis.HiggsToTauTau.sbatchManager import sbatchManager

from config import config

def call_histogram_aggregation_on_cluster_node_spec():

    # Prepare

    run_cmd("rm -rf %(temp_dir)s/call_histogram_aggregation_on_cluster_node" % config)
    run_cmd("mkdir -p %(temp_dir)s/call_histogram_aggregation_on_cluster_node/" % config)


    # Add histograms and run task

    pool_id = uuid.uuid4()
    m = sbatchManager(pool_id)
    m.setWorkingDir('%(cmssw_base)s/src/analysis2mu1b1j/analysis2mu1b1j/test' % config)

    try:
        m.hadd_in_cluster(
            inputFiles=[
                '%(fixtures_dir)s/histogram_1.root' % config,
                '%(fixtures_dir)s/histogram_2.root' % config
            ],
            outputFile='%(temp_dir)s/call_histogram_aggregation_on_cluster_node/result.root' % config
        )

        m.waitForJobs()
    except:
        got_exception = True
    else:
        got_exception = False


    # Check result

    root_result_file = '%(temp_dir)s/call_histogram_aggregation_on_cluster_node/result.root' % config
    result_successful = os.path.isfile(root_result_file)


    # Output result

    if result_successful:
        print('PASSED: HADD on cluster node worked')
    else:
        print('FAILED: HADD on cluster node failed')

    return result_successful and not got_exception
