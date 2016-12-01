import subprocess
import time
from tthAnalysis.HiggsToTauTau.jobTools import run_cmd
from tthAnalysis.HiggsToTauTau.sbatchManager import sbatchManager

from config import config

def executable_hadd_in_cluster_spec():

    # Prepare

    run_cmd("rm -rf /home/%(user)s/tmp/hadd_in_cluster_spec/*" % config)
    fixtures_dir = '/home/%(user)s/VHbbNtuples_7_6_x/CMSSW_7_6_3/src/tthAnalysis/HiggsToTauTau/specs/fixtures/' % config
    run_cmd("""echo "%(fixtures_dir)s/histogram_1.root\n\%(fixtures_dir)s/histogram_2.root\n" > /home/%(user)s/tmp/hadd_in_cluster_spec/input_histograms_list.txt""" % { 'fixtures_dir': fixtures_dir, 'user': config.user })


    # Run task

    run_cmd('python /home/%(user)s/VHbbNtuples_7_6_x/CMSSW_7_6_3/src/tthAnalysis/HiggsToTauTau/scripts/hadd_in_cluster.py /home/%(user)s/tmp/hadd_in_cluster_spec/output_histogram.root /home/%(user)s/tmp/hadd_in_cluster_spec/input_histograms_list.txt' % config)


    # Check the result

    root_result_file = '/home/%(user)s/tmp/hadd_in_cluster_spec/output_histogram.root' % config
    result_successful = os.path.isfile(root_result_file)


    # Output result

    if result_successful:
        print('Executable for HADD in cluster is WORKING')
    else:
        print('Executable for HADD in cluster is NOT WORKING')

    return result_successful
