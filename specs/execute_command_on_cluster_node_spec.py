import subprocess
from tthAnalysis.HiggsToTauTau.sbatchManager import sbatchManager
import time
from tthAnalysis.HiggsToTauTau.jobTools import run_cmd

def run_test():

    # Prepare

    run_cmd("rm -rf /home/margusp/tmp/execute_command_on_cluster_node_spec/*")

    m = sbatchManager()
    m.setWorkingDir('/home/margusp/VHbbNtuples_7_6_x/CMSSW_7_6_3/src/analysis2mu1b1j/analysis2mu1b1j/test')


    # Run task

    m.submit_job_version2(
        task_name = 'creating_result_0-0.root',
        command = '''
            export TEST_DIR=/home/margusp/tmp/execute_command_on_cluster_node_spec/
            mkdir -p $TEST_DIR
            echo "Worked" > $TEST_DIR/result.txt
        ''',
        output_dir = '/home/margusp/tmp/execute_command_on_cluster_node_spec/'
    )

    m.waitForJobs()
    time.sleep(2)

    # Check the result

    with file('/home/margusp/tmp/execute_command_on_cluster_node_spec/result.txt') as f:
        result = f.read().strip()

        if result == 'Worked':
            print('Execute on cluster node passed.')
            return True

    print("$TEST_DIR/result.txt did not contain result.txt with 'Worked'.")
    print('Execute on cluster node failed.')

    return False


# Run test and print result

run_test()
