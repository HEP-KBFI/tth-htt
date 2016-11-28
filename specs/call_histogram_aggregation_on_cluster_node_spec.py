import subprocess
import time
from tthAnalysis.HiggsToTauTau.jobTools import run_cmd
from tthAnalysis.HiggsToTauTau.sbatchManager import sbatchManager

def run_test():

    # Prepare


    # Add histograms and run task

    m = sbatchManager()
    m.setWorkingDir('/home/margusp/VHbbNtuples_7_6_x/CMSSW_7_6_3/src/analysis2mu1b1j/analysis2mu1b1j/test')

    m.submit_job_version2(
        task_name = 'call_histogram_aggregation_on_cluster_node', # BUG: Task name can't include space
        command = '''
            export TEST_DIR=/home/margusp/tmp/execute_command_on_cluster_node_spec/
            mkdir -p $TEST_DIR
            echo "Worked" > $TEST_DIR/result.txt
        ''',
        output_dir = '/home/margusp/tmp/execute_command_on_cluster_node_spec/'
    )

    m.waitForJobs()


    # Check result

    # Output result


run_test()
