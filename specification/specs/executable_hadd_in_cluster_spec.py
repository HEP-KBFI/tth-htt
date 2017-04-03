import os
from tthAnalysis.HiggsToTauTau.jobTools import run_cmd
from config import config

def executable_hadd_in_cluster_spec():

    # Prepare

    run_cmd("rm -rf %(temp_dir)s/executable_hadd_in_cluster_spec/*" % config)
    run_cmd("mkdir -p %(temp_dir)s/executable_hadd_in_cluster_spec/" % config)
    run_cmd("""echo "%(fixtures_dir)s/histogram_1.root\n%(fixtures_dir)s/histogram_2.root\n" > """ \
            """%(temp_dir)s/executable_hadd_in_cluster_spec/input_histograms_list.txt""" % config)


    # Run task

    run_cmd('python %(cmssw_base)s/src/tthAnalysis/HiggsToTauTau/scripts/hadd_in_cluster.py ' \
            '%(temp_dir)s/executable_hadd_in_cluster_spec/output_histogram.root ' \
            '%(temp_dir)s/executable_hadd_in_cluster_spec/input_histograms_list.txt' % config)


    # Check the result

    root_result_file = '%(temp_dir)s/executable_hadd_in_cluster_spec/output_histogram.root' % config
    result_successful = os.path.isfile(root_result_file)


    # Output result

    if result_successful:
        print('PASSED: Executable for HADD in cluster is WORKING')
    else:
        print('FAILED: Executable for HADD in cluster is NOT WORKING')

    return result_successful
