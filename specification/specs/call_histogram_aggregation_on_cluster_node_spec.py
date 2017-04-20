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
        return False


    # Check result

    root_result_file = '%(temp_dir)s/call_histogram_aggregation_on_cluster_node/result.root' % config
    root_file_exists = os.path.isfile(root_result_file)

    if not root_file_exists:
        print('FAILED: HADD on cluster node failed - file is missing')
        return False

    histogram_metadata_file = root_result_file + '.metadata'
    root_file_metadata_txt = run_cmd('cat %s' % histogram_metadata_file)

    expected_metadata_txt = "sha1sum: 34754a9cc5e0359f2b73c5b18cc6a60214f2c047\nevents_count: 1831527.0\n"

    if root_file_metadata_txt.find(expected_metadata_txt) == -1:
        print('FAILED: Metadata "%s" is not correct, should be "%s"' % (root_file_metadata_txt, expected_metadata_txt))
        return False

    print('PASSED: HADD on cluster node worked')

    return True
