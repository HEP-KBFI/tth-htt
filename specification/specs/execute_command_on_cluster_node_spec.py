import subprocess
import time
from tthAnalysis.HiggsToTauTau.jobTools import run_cmd
from tthAnalysis.HiggsToTauTau.sbatchManager import sbatchManager

from config import config

def execute_command_on_cluster_node_spec():

    # Prepare

    run_cmd("rm -rf /%(temp_dir)s/execute_command_on_cluster_node_spec/*" % config)


    # Run task

    m = sbatchManager()
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

    m.waitForJobs()

    with file('%(temp_dir)s/execute_command_on_cluster_node_spec/result.txt' % config) as f:
        result = f.read().strip()

        if result != 'Worked':
            print("$TEST_DIR/ did not contain result.txt with content 'Worked'.")
            print('FAILED: Execute on cluster node failed.')
            return False


    # Log RAM and CPU usage information

    m.log_ram_and_cpu_usage_information(
        log_file = '%(temp_dir)s/execute_command_on_cluster_node_spec/cpu_and_ram_info.log' % config
    )

    with file('%(temp_dir)s/execute_command_on_cluster_node_spec/cpu_and_ram_info.log' % config) as f:
        result = f.read().strip()

        if result.find('MaxVMSize') == -1:
            print("$TEST_DIR/ did not contain cpu_and_ram_info.log with content 'MaxVMSize'.")
            print('FAILED: Execute on cluster node failed.')
            return False


    print('PASSED: Execute on cluster node passed.')
    return True
