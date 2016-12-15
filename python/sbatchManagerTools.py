import os

from tthAnalysis.HiggsToTauTau.jobTools import run_cmd
from tthAnalysis.HiggsToTauTau.analysisTools import createFile

executable_rm = 'rm'

def createScript_sbatch(sbatch_script_file_name,
                        executable, cfg_file_names, input_file_names, output_file_names, log_file_names = None,
                        working_dir = None, max_num_jobs = 100000, cvmfs_error_log = None):
    """Creates the python script necessary to submit analysis and/or Ntuple production jobs to the batch system
    """
    if not working_dir:
        working_dir = os.getcwd()
    sbatch_analyze_lines = generate_sbatch_lines(
      executable,
      cfg_file_names, input_file_names, output_file_names, log_file_names,
      working_dir, max_num_jobs, cvmfs_error_log)
    createFile(sbatch_script_file_name, sbatch_analyze_lines)
    
def generate_sbatch_lines(executable, cfg_file_names, input_file_names, output_file_names, log_file_names,
                          working_dir, max_num_jobs, cvmfs_error_log = None):
    lines_sbatch = []
    lines_sbatch.append("from tthAnalysis.HiggsToTauTau.sbatchManager import sbatchManager")
    lines_sbatch.append("")
    lines_sbatch.append("m = sbatchManager()")
    lines_sbatch.append("m.setWorkingDir('%s')" % working_dir)

    num_jobs = 0
    for key_file, cfg_file_name in cfg_file_names.items():
        log_file_name = None
        if log_file_names:
            log_file_name = log_file_names[key_file]
        if num_jobs <= max_num_jobs:
            sbatch_line = generate_sbatch_line(
                executable = executable,
                cfg_file_name = cfg_file_name,
                input_file_names = input_file_names[key_file],
                output_file_name = output_file_names[key_file],
                log_file_name = log_file_name,
                cvmfs_error_log = cvmfs_error_log
            )
            if sbatch_line:
                lines_sbatch.append(sbatch_line)
        num_jobs = num_jobs + 1
    if num_jobs > max_num_jobs:
        print "Warning: number of jobs = %i exceeds limit of %i --> skipping submission of %i jobs !!" % \
          (num_jobs, max_num_jobs, num_jobs - max_num_jobs)

    lines_sbatch.append("m.waitForJobs()")
    return lines_sbatch

def generate_sbatch_line(executable, cfg_file_name, input_file_names, output_file_name, log_file_name = None,
                         cvmfs_error_log = None):
    if os.path.exists(output_file_name):
        output_file_size = os.stat(output_file_name).st_size
        print "output file %s already exists, size = %i" % (output_file_name, output_file_size)
        if output_file_size > 20000:
            print "--> skipping job because it has size creater than 20000"
            return None
        else:
            print "--> deleting output file and resubmitting job because it has size smaller 20000"
            command = "%s %s" % (executable_rm, output_file_name)
            run_cmd(command)

        if log_file_name and os.path.exists(log_file_name):
            log_file = open(log_file_name)
            is_time = False
            time = None
            is_hostname = False
            hostname = None
            is_cvmfs_error = False
            for line in log_file:
                if line.find("Time") != -1:
                    time = line.split(':')[1].strip()
                if line.find("Hostname") != -1:
                    hostname = line.split(':')[1].strip()
                if line.find("Transport endpoint is not connected") != -1:
                    is_cvmfs_error = True
            log_file.close()
            if is_cvmfs_error:
                print "Problem with cvmfs access reported in log file = '%s':" % log_file_name
                print " host = '%s': time = %s" % (hostname, time)
                if cvmfs_error_log:
                    if not hostname in cvmfs_error_log.keys():
                        cvmfs_error_log[hostname] = []
                    cvmfs_error_log[hostname].append(time)

    return "m.submitJob(%s, '%s', '%s', '%s', %s, '%s', True)" % (
        input_file_names,
        executable,
        cfg_file_name,
        os.path.dirname(output_file_name),
        [ os.path.basename(output_file_name) ],
        log_file_name
    )

def createScript_sbatch_hadd(sbatch_script_file_name, input_file_names, output_file_name, hadd_stage_name,
                             working_dir = None):
    """Creates the python script necessary to submit 'hadd' jobs to the batch system
    """
    if not working_dir:
        working_dir = os.getcwd()
    sbatch_hadd_lines = generate_sbatch_lines_hadd(
        input_file_names = input_file_names,
        output_file_name = output_file_name,
        working_dir = working_dir
    )
    createFile(sbatch_script_file_name, sbatch_hadd_lines)

def generate_sbatch_lines_hadd(input_file_names, output_file_name, working_dir):
    template_vars = {
        'working_dir': working_dir,
        'input_file_names': input_file_names,
        'output_file_name': output_file_name
    }

    sbatch_code = """
from tthAnalysis.HiggsToTauTau.sbatchManager import sbatchManager
m = sbatchManager()
m.setWorkingDir('%(working_dir)s')
m.hadd_in_cluster(
    inputFiles=%(input_file_names)s,
    outputFile='%(output_file_name)s'
)
""" % template_vars

    return sbatch_code.splitlines()
