import subprocess
from tthAnalysis.HiggsToTauTau.sbatchManager import sbatchManager

def run_test():

    # Prepare

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


    # Check the result

    with file('/home/margusp/tmp/execute_command_on_cluster_node_spec/result.txt') as f:
        result = f.read()

    if result == 'Worked':
        subprocess.call("rm -rf /home/margusp/tmp/creating_result/*")
        return True
        
    return False


# Run test and print result

test_was_successful = run_test()

if test_was_successful():
    print('Execute on cluster node passed.')
else:
    print('Execute on cluster node failed.')
