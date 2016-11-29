import subprocess
import time
from tthAnalysis.HiggsToTauTau.jobTools import run_cmd
from tthAnalysis.HiggsToTauTau.sbatchManager import sbatchManager


def run_test():

    # Prepare

    run_cmd("rm -rf /home/%(user)s/tmp/execute_command_on_cluster_node_spec/*" % config)

    m = sbatchManager()
    m.setWorkingDir('/home/%(user)s/VHbbNtuples_7_6_x/CMSSW_7_6_3/src/analysis2mu1b1j/analysis2mu1b1j/test' % config)


    # Run task

    m.submit_job_version2(
        task_name = 'creating_result.txt', # BUG: Task name can't include space
        command = '''
            export TEST_DIR=/home/%(user)s/tmp/execute_command_on_cluster_node_spec/
            mkdir -p $TEST_DIR
            echo "Worked" > $TEST_DIR/result.txt
        '''  % config,
        output_dir = '/home/%(user)s/tmp/execute_command_on_cluster_node_spec/' % config
    )

    m.waitForJobs()

    # Check the result

    with file('/home/%(user)s/tmp/execute_command_on_cluster_node_spec/result.txt' % config) as f:
        result = f.read().strip()

        if result == 'Worked':
            print('Execute on cluster node passed.')
            return True

    print("$TEST_DIR/result.txt did not contain result.txt with 'Worked'.")
    print('Execute on cluster node failed.')

    return False


# Run test and print result

run_test()
