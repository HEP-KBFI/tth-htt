import os, jinja2, ROOT, logging

from tthAnalysis.HiggsToTauTau.jobTools import run_cmd
from tthAnalysis.HiggsToTauTau.analysisTools import createFile

executable_rm = 'rm'

def createScript_sbatch(
    sbatch_script_file_name,
    executable,
    command_line_parameters,
    input_file_names,
    output_file_names,
    script_file_names,
    log_file_names    = None,
    working_dir       = None,
    max_num_jobs      = 100000,
    cvmfs_error_log   = None,
    pool_id           = '',
    cmssw_base_dir    = None,
    verbose           = False,
    job_template_file = 'sbatch-node.sh.template',
    dry_run           = False,
    skipFileSizeCheck = False,
    use_home          = True,
  ):
    """Creates the python script necessary to submit analysis and/or Ntuple production jobs to the batch system
    """
    if not working_dir:
        working_dir = os.getcwd()

    if not cmssw_base_dir:
        cmssw_base_dir = os.environ['CMSSW_BASE']

    if not pool_id:
        raise ValueError('pool_id is empty')
    sbatch_analyze_lines, num_jobs = generate_sbatch_lines(
        executable              = executable,
        command_line_parameters = command_line_parameters,
        input_file_names        = input_file_names,
        output_file_names       = output_file_names,
        script_file_names       = script_file_names,
        log_file_names          = log_file_names,
        working_dir             = working_dir,
        max_num_jobs            = max_num_jobs,
        cvmfs_error_log         = cvmfs_error_log,
        pool_id                 = pool_id,
        cmssw_base_dir          = cmssw_base_dir,
        verbose                 = verbose,
        job_template_file       = job_template_file,
        dry_run                 = dry_run,
        skipFileSizeCheck       = skipFileSizeCheck,
        use_home                = use_home,
    )
    createFile(sbatch_script_file_name, sbatch_analyze_lines)
    return num_jobs

def generate_sbatch_lines(
    executable,
    command_line_parameters,
    input_file_names,
    output_file_names,
    script_file_names,
    log_file_names,
    working_dir,
    max_num_jobs,
    cvmfs_error_log   = None,
    pool_id           = '',
    cmssw_base_dir    = None,
    verbose           = False,
    job_template_file = 'sbatch-node.sh.template',
    dry_run           = False,
    skipFileSizeCheck = False,
    use_home          = True,
  ):
    if not pool_id:
        raise ValueError('pool_id is empty')
    lines_sbatch = [
        "from tthAnalysis.HiggsToTauTau.sbatchManager import sbatchManager",
        "",
        "m = sbatchManager('%s', verbose = %s, dry_run = %s, use_home = %s)" % \
          (pool_id, verbose, dry_run, use_home),
        "m.setWorkingDir('%s')"                 % working_dir,
        "m.setcmssw_base_dir('%s')"             % cmssw_base_dir,
        "m.log_completion = %s"                 % verbose,
    ]

    num_jobs = 0
    for key_file, command_line_parameter in command_line_parameters.items():
        log_file_name = None
        if log_file_names:
            log_file_name = log_file_names[key_file]
        if num_jobs <= max_num_jobs:
            sbatch_line = generate_sbatch_line(
                executable = executable,
                command_line_parameter = command_line_parameter,
                input_file_names       = input_file_names[key_file],
                output_file_name       = output_file_names[key_file],
                script_file_name       = script_file_names[key_file],
                log_file_name          = log_file_name,
                cvmfs_error_log        = cvmfs_error_log,
                job_template_file      = job_template_file,
                skipFileSizeCheck      = skipFileSizeCheck,
            )
            if sbatch_line:
                lines_sbatch.append(sbatch_line)
                num_jobs = num_jobs + 1
    if num_jobs > max_num_jobs:
        logging.warning(
          "number of jobs = %i exceeds limit of %i --> skipping submission of %i jobs !!" % \
          (num_jobs, max_num_jobs, num_jobs - max_num_jobs)
        )

    lines_sbatch.append("m.waitForJobs()")
    return lines_sbatch, num_jobs

def is_file_ok(output_file_name, min_file_size = 20000, skipFileSizeCheck = False):
  command = "%s %s" % (executable_rm, output_file_name)
  output_file_size = os.stat(output_file_name).st_size
  logging.info("output file %s already exists, size = %i" % (output_file_name, output_file_size))
  if output_file_size > min_file_size or skipFileSizeCheck:
    root_tfile = ROOT.TFile(output_file_name, "read")
    if root_tfile.IsZombie():
      logging.info("--> output file is corrupted, deleting file and resubmitting job")
      run_cmd(command)
    else:
      # Let's open the file via bash as well to see if ROOT tries to recover the file
      open_cmd = "root -b -l -q %s 2>&1 > /dev/null | grep 'trying to recover' | wc -l" % output_file_name
      open_out = run_cmd(open_cmd)
      if open_out.rstrip('\n') != '0':
        logging.info("--> output file is probably corrupted, deleting file and resubmitting job")
        command = "%s %s" % (executable_rm, output_file_name)
        run_cmd(command)
      else:
        root_tfile.Close()
        logging.info("--> skipping job because it has size greater than 20000")
        return True
    root_tfile.Close()
  else:
    logging.info(
      "--> deleting output file and resubmitting job because it has size smaller %i" % min_file_size
    )
    run_cmd(command)
  return False

def generate_sbatch_line(
    executable,
    command_line_parameter,
    input_file_names,
    output_file_name,
    script_file_name,
    log_file_name     = None,
    cvmfs_error_log   = None,
    min_file_size     = 20000,
    job_template_file = 'sbatch-node.sh.template',
    skipFileSizeCheck = False,
  ):
    if output_file_name and os.path.exists(output_file_name):
        if not output_file_name.lower().endswith('.root'):
           return None
        if is_file_ok(output_file_name, min_file_size, skipFileSizeCheck):
          return None

        if log_file_name and os.path.exists(log_file_name):
            log_file = open(log_file_name)
            time           = None
            hostname       = None
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
                logging.error("Problem with cvmfs access reported in log file = '%s':" % log_file_name)
                logging.error(" host = '%s': time = %s" % (hostname, time))
                if cvmfs_error_log:
                    if not hostname in cvmfs_error_log.keys():
                        cvmfs_error_log[hostname] = []
                    cvmfs_error_log[hostname].append(time)

    if type(input_file_names) is str:
        input_file_names = [ input_file_names ]

    submissionStatement = "m.submitJob(\n"                            \
      "  inputFiles             = {input_file_names},\n"              \
      "  executable             = '{executable}',\n"                  \
      "  command_line_parameter = '{command_line_parameter}',\n"      \
      "  outputFilePath         = '{output_file_name}',\n"            \
      "  outputFiles            = {output_file_basename},\n"          \
      "  scriptFile             = '{script_file_name}',\n"            \
      "  logFile                = '{log_file_name}',\n"               \
      "  skipIfOutputFileExists = {skipIfOutputFileExists},\n"        \
      "  job_template_file      = '{job_template_file}',\n"           \
      ")".format(
        input_file_names       = input_file_names,
        executable             = executable,
        command_line_parameter = command_line_parameter,
        output_file_name       = os.path.dirname(output_file_name) if output_file_name else '',
        output_file_basename   = [ os.path.basename(output_file_name) ] if output_file_name else [],
        script_file_name       = script_file_name,
        log_file_name          = log_file_name,
        skipIfOutputFileExists = str(bool(output_file_name)),
        job_template_file      = job_template_file,
    )
    return submissionStatement

def createScript_sbatch_hadd(
    sbatch_script_file_name,
    input_file_names,
    output_file_name,
    script_file_name,
    log_file_name           = None,
    working_dir             = None,
    waitForJobs             = True,
    auxDirName              = '',
    pool_id                 = '',
    verbose                 = False,
    dry_run                 = False,
    max_input_files_per_job = 5,
    use_home                = True,
  ):
    """Creates the python script necessary to submit 'hadd' jobs to the batch system
    """
    if not working_dir:
        working_dir = os.getcwd()
    if not pool_id:
        raise ValueError('pool_id is empty')
    sbatch_hadd_lines, num_jobs = generate_sbatch_lines_hadd(
        input_file_names        = input_file_names,
        output_file_name        = output_file_name,
        script_file_name        = script_file_name,
        log_file_name           = log_file_name,
        working_dir             = working_dir,
        waitForJobs             = waitForJobs,
        auxDirName              = auxDirName,
        pool_id                 = pool_id,
        verbose                 = verbose,
        dry_run                 = dry_run,
        max_input_files_per_job = max_input_files_per_job,
        use_home                = use_home,
    )
    createFile(sbatch_script_file_name, sbatch_hadd_lines)
    return num_jobs

def generate_sbatch_lines_hadd(
    input_file_names,
    output_file_name,
    script_file_name,
    log_file_name,
    working_dir,
    waitForJobs             = True,
    auxDirName              = '',
    pool_id                 = '',
    verbose                 = False,
    dry_run                 = False,
    max_input_files_per_job = 5,
    use_home                = True,
  ):
    template_vars = {
        'working_dir'             : working_dir,
        'input_file_names'        : input_file_names,
        'output_file_name'        : output_file_name,
        'waitForJobs'             : waitForJobs,
        'auxDirName'              : auxDirName,
        'pool_id'                 : pool_id,
        'max_input_files_per_job' : max_input_files_per_job,
        'script_file_name'        : script_file_name,
        'log_file_name'           : log_file_name,
        'verbose'                 : verbose,
        'dry_run'                 : dry_run,
        'use_home'                : use_home,
    }
    if not pool_id:
        raise ValueError('pool_id is empty')
    sbatch_template = """
from tthAnalysis.HiggsToTauTau.sbatchManager import sbatchManager
from tthAnalysis.HiggsToTauTau.ClusterHistogramAggregator import ClusterHistogramAggregator

m = sbatchManager('{{pool_id}}', verbose = {{verbose}}, dry_run = {{dry_run}}, use_home = {{use_home}})
m.setWorkingDir('{{working_dir}}')
m.log_completion = {{verbose}}

cluster_histogram_aggregator = ClusterHistogramAggregator(
  input_files             = {{input_file_names}},
  final_output_file       = '{{output_file_name}}',
  max_input_files_per_job = {{max_input_files_per_job}},
  waitForJobs             = {{waitForJobs}},
  sbatch_manager          = m,
  auxDirName              = '{{auxDirName}}',
  script_file_name        = '{{script_file_name}}',
  log_file_name           = '{{log_file_name}}',
)
cluster_histogram_aggregator.create_output_file()
"""
    sbatch_code = jinja2.Template(sbatch_template).render(**template_vars)
    num_jobs = 1

    return sbatch_code.splitlines(), num_jobs
