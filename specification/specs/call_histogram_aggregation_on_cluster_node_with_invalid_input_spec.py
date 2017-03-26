import os, uuid
from tthAnalysis.HiggsToTauTau.jobTools import run_cmd
from tthAnalysis.HiggsToTauTau.sbatchManager import sbatchManager, sbatchManagerRuntimeError

from config import config

def call_histogram_aggregation_on_cluster_node_with_invalid_input_spec():

    # Prepare

    run_cmd("rm -rf %(temp_dir)s/call_histogram_aggregation_on_cluster_node_with_invalid_input" % config)
    run_cmd("mkdir -p %(temp_dir)s/call_histogram_aggregation_on_cluster_node_with_invalid_input/" % config)


    # Add histograms and run task

    pool_id = uuid.uuid4()
    m = sbatchManager(pool_id)
    m.setWorkingDir('%(cmssw_base)s/src/analysis2mu1b1j/analysis2mu1b1j/test' % config)

    try:
        m.hadd_in_cluster(
            inputFiles=[
                '%(fixtures_dir)s/histogram_1.root' % config,
                '%(fixtures_dir)s/histogram_broken.root' % config
            ],
            outputFile='%(temp_dir)s/call_histogram_aggregation_on_cluster_node_with_invalid_input/result.root' % config
        )

        m.waitForJobs()
    except sbatchManagerRuntimeError:
        got_exception = True
    except:
        got_exception = False # Got wrong exception
    else:
        got_exception = False # Didn't get any exceptions, although we should've

    # Check result

    root_result_file = '%(temp_dir)s/call_histogram_aggregation_on_cluster_node_with_invalid_input/result.root' % config
    root_file_does_not_exist = not os.path.isfile(root_result_file)

    result_successful = root_file_does_not_exist and got_exception


    # Output result

    if result_successful:
        print('PASSED: HADD on cluster node with invalid input was interrupted as expected')
    else:
        error_reasons = ""

        if not root_file_does_not_exist:
            error_reasons = 'root file should not exist; '

        if not got_exception:
            error_reasons = error_reasons + "didn't catch sbatchManagerRuntimeError; "

        print('FAILED: HADD on cluster node failed silently and this is bad: ' + error_reasons)

    return result_successful
