import uuid

from tthAnalysis.HiggsToTauTau.jobTools import run_cmd
from tthAnalysis.HiggsToTauTau.sbatchManager import sbatchManager

from config import config

def execute_command_on_cluster_node_spec():

    # Prepare

    run_cmd("rm -rf /%(temp_dir)s/execute_command_on_cluster_node_spec/*" % config)


    # Run task

    pool_id = uuid.uuid4()
    m = sbatchManager(pool_id)
    m.setWorkingDir('%(cmssw_base)s/src/analysis2mu1b1j/analysis2mu1b1j/test' % config)

    m.submit_job_version2(
        task_name = 'creating_result.txt', # BUG: Task name can't include space
        command = '''
            export TEST_DIR=%(temp_dir)s/execute_command_on_cluster_node_spec/
            mkdir -p $TEST_DIR
            echo "Worked" > $TEST_DIR/result.txt
        '''  % config,
        output_dir = '%(temp_dir)s/execute_command_on_cluster_node_spec/' % config
    )


    # Check the result

    try:
        m.waitForJobs()
    except:
        got_exception = True
    else:
        got_exception = False

    if got_exception:
        return False

    with file('%(temp_dir)s/execute_command_on_cluster_node_spec/result.txt' % config) as f:
        result = f.read().strip()

        if result != 'Worked':
            print("$TEST_DIR/ did not contain result.txt with content 'Worked'.")
            print('FAILED: Execute on cluster node failed.')
            return False

    return True
