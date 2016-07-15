import json, os, codecs, stat, logging, sys, jinja2, subprocess, getpass, time
import tthAnalysis.HiggsToTauTau.tthAnalyzeSamples_chargeflip as samples
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no, add_chmodX, create_job, create_if_not_exists, generate_file_ids, generate_input_list




LUMI = 2260. # 1/pb
DKEY_JOBS = "jobs"       # dir for jobs aka bash scripts that run a single analysis executable
DKEY_CFGS = "cfgs"       # dir for python configuration file for each job
DKEY_HIST = "histograms" # dir for histograms = output of the jobs
DKEY_LOGS = "logs"       # dir for log files (stdout/stderr of jobs)
DKEY_DCRD = "datacards"  # dir for the datacard
DKEY_EVLIST = "eventlists"  # dir for the datacard

"""
TODO:
  * isMC is always False in the analysis config since we're missing some necessary input files for MC
"""

class analyzeCFConfig:
  """Configuration metadata needed to run analysis in a single go.

  Sets up a folder structure by defining full path names; no directory creation is delegated here.

  Args:
    output_dir: The root output dir -- all configuration, log and output files are stored in its subdirectories
    lepton_selection: either `Tight`, `Loose` or `Fakeable`
    max_files_per_job: maximum number of input root files (Ntuples) are allowed to chain together per job
    use_lumi: if True, use lumiSection aka event weight ( = xsection * luminosity / nof events), otherwise uses plain event count
    use_data: if False, use metadat generated from MC
    debug: if True, checks each input root file (Ntuple) before creating the python configuration files
    running_method: either `sbatch` (uses SLURM) or `Makefile`
    nof_parallel_jobs: number of jobs that can be run in parallel (matters only if `running_method` is set to `Makefile`)
    poll_interval: the interval of checking whether all sbatch jobs are completed (matters only if `running_method` is set to `sbatch`)
    prep_dcard_exec: executable name for preparing the datacards
    histogram_to_fit: what histograms are filtered in datacard preparation

  Other:
    is_sbatch: boolean that is True if the `running_method` is set to `sbatch`; False otherwise
    is_makefile: boolean that is True if the `running_method` is set to `Makefile`; False otherwise
    output_category: output category of the datacard
    subdir: all analysis-specific files are placed under this subdirectory
    dirs: list of subdirectories under `subdir` -- jobs, cfgs, histograms, logs, datacards
    makefile_fullpath: full path to the Makefile
    sbatch_fullpath: full path to the bash script that submits all jobs to SLURM
    histogram_file: the histogram file obtained by hadding the output of all jobs
    datacard_outputfile: the datacard -- final output file of this execution flow
    dcard_cfg_fullpath: python configuration file for datacard preparation executable
  """
  def __init__(self, output_dir, exec_name, lepton_selection,
               max_files_per_job, use_lumi, use_data, debug, running_method, nof_parallel_jobs,
               poll_interval, selected_datasets, sel_events_file, prep_dcard_exec):

    assert(exec_name in ["analyze_charge_flip"]), "Invalid exec name: %s" % exec_name
    assert(lepton_selection in ["Tight", "Loose", "Fakeable"]),                          "Invalid lepton selection: %s" % lepton_selection
    assert(running_method.lower() in ["sbatch", "makefile"]),                           "Invalid running method: %s" % running_method

    self.output_dir = output_dir
    self.exec_name = exec_name
    self.lepton_selection = lepton_selection
    self.max_files_per_job = max_files_per_job
    self.use_lumi = use_lumi
    self.use_data = use_data
    self.debug = debug
    self.running_method = running_method
    self.nof_parallel_jobs = nof_parallel_jobs
    self.poll_interval = poll_interval
    self.selected_datasets = selected_datasets
    self.sel_events_file = sel_events_file
    self.prep_dcard_exec = prep_dcard_exec
    
    self.is_sbatch = False
    self.is_makefile = False
    if self.running_method.lower() == "sbatch": self.is_sbatch = True
    else:                                       self.is_makefile = True

    self.output_category = self.exec_name.replace("analyze_", "")
    self.subdir = "_".join([self.output_category, self.lepton_selection])
    self.analysis_type = self.subdir
    dir_types = [DKEY_JOBS, DKEY_CFGS, DKEY_HIST, DKEY_LOGS, DKEY_DCRD, DKEY_EVLIST]
    self.dirs = {dkey: os.path.join(self.output_dir, dkey, self.subdir) for dkey in dir_types}

    self.makefile_fullpath = os.path.join(self.output_dir, "Makefile")
    self.sbatch_fullpath = os.path.join(self.output_dir, "sbatch.sh")
    self.histogram_file = os.path.join(self.dirs[DKEY_HIST], "allHistogramsCF.root")
    self.datacard_outputfile = os.path.join(self.dirs[DKEY_DCRD], "prepareDatacardsCF.root")
    self.dcard_cfg_fullpath = os.path.join(self.dirs[DKEY_CFGS], "prepareDatacardsCF_cfg.py")

def create_config(root_filenames, output_file, category_name, triggers, is_mc, use_data, lumi_scale, cfg, idx):
  """Fill python configuration file for the job exectuable (analysis code)

  Args:
    root_filesnames: list of full path to the input root files (Ntupes)
    output_file: output file of the job -- a histogram
    category_name: either `TTW`, `TTZ`, `WZ`, `Rares`, `data_obs`, `ttH_hww`, `ttH_hzz` or `ttH_htt`
    is_mc: is a given sample an MC (True) or data (False)
    use_data:
    lumi_scale: event weight ( = xsection * luminosity / nof events)
    cfg: configuration instance that contains paths; see `analyzeConfig`
    idx: job index

  Returns:
    Filled template
  """
  cfg_file = """import os
import FWCore.ParameterSet.Config as cms

process = cms.PSet()
process.fwliteInput = cms.PSet(
    fileNames = cms.vstring('{{ fileNames|join("',\n                            '") }}'),
    maxEvents = cms.int32(-1),
    outputEvery = cms.uint32(100000)
)

process.fwliteOutput = cms.PSet(
    fileName = cms.string('{{ outputFile }}')
)

process.{{ execName }} = cms.PSet(
    treeName = cms.string('tree'),
    process = cms.string('{{ categoryName }}'),

    triggers_1e = cms.vstring("HLT_BIT_HLT_Ele23_WPLoose_Gsf_v"),
    use_triggers_1e = cms.bool({{ use_triggers_1e }}),
    triggers_2e = cms.vstring("HLT_BIT_HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v"),
    use_triggers_2e = cms.bool({{ use_triggers_2e }}),
    triggers_1mu = cms.vstring("HLT_BIT_HLT_IsoMu20_v", "HLT_BIT_HLT_IsoTkMu20_v"),
    use_triggers_1mu = cms.bool({{ use_triggers_1mu }}),
    triggers_2mu = cms.vstring("HLT_BIT_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v",
                               "HLT_BIT_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v"),
    use_triggers_2mu = cms.bool({{ use_triggers_2mu }}),
    triggers_1e1mu = cms.vstring("HLT_BIT_HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v",
                                 "HLT_BIT_HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v"),
    use_triggers_1e1mu = cms.bool({{ use_triggers_1e1mu }}),
    chargeSelection = cms.string('{{ chargeSelection }}'),
    leptonSelection = cms.string('{{ leptonSelection }}'),

    isMC = cms.bool({{ isMC }}),
    useData = cms.bool({{ useData }}),
    central_or_shift = cms.string('central'),
    lumiScale = cms.double({{ lumiScale }}),

    selEventsFileName_input = cms.string('{{ selEvents }}'),
    selEventsFileName_output = cms.string('{{ outEvents }}')
)

"""
  return jinja2.Template(cfg_file).render(
    fileNames = root_filenames,
    execName = cfg.exec_name,
    outputFile = output_file,
    categoryName = category_name,
    use_triggers_1e = "1e" in triggers,
    use_triggers_2e = "2e" in triggers,
    use_triggers_1mu = False,
    use_triggers_2mu = False,
    use_triggers_1e1mu = False,
    leptonSelection = cfg.lepton_selection,
    #isMC = False, # NOTE: temporary fix; previously: is_mc
    isMC = is_mc,
    useData = use_data,
    lumiScale = lumi_scale,
    selEvents = cfg.sel_events_file,
    outEvents = output_file.replace("histograms", "eventlists").replace(".root", ".txt"),
    idx = idx)

def create_makefile(commands, num):
  """Fills Makefile template

  Args:
    commands: list of commands (full paths to the bash scripts, followed by redirection clauses)
    num: number of rules per one line (so that the file still remains human-readable)

  Returns:
    Filled template
  """
  nof_jobs = len(commands)
  job_labels_seq = map(lambda x: "j" + str(x), range(1, nof_jobs))
  job_labels_nested = [job_labels_seq[i:i + num] for i  in range(0, nof_jobs, num)]
  job_labels_nested_spaced = [" ".join(x) for x in job_labels_nested]

  makefile_template = """
.PHONY: {% for jobList in jobLabelsNestedSpaced %} {{ jobList }} \\
{% endfor %}

all: {% for jobList in jobLabelsNestedSpaced %} {{ jobList }} \\
{% endfor %}

{% for command in commands %}
j{{ loop.index }}:
\t@bash {{ command }}
{% endfor %}
"""
  return jinja2.Template(makefile_template).render(
    commands = commands,
    jobLabelsNestedSpaced = job_labels_nested_spaced)

def create_sbatch(sbatch_logfiles, commands, sbatch_queue = "short"):
  """Fills sbatch submission template (a bash script)
  Args:
    sbatch_logfiles: list of full paths to the log files for each jobs
    commands: list of commands (full paths to the bash scripts)
  Returns:
    Filled template
  """
  sbatch_meta = zip(sbatch_logfiles, commands)
  sbatch_template = """#!/bin/bash
{% for logfile,command in sbatch_meta %}
sbatch --partition={{ sbatch_queue }} --output={{ logfile }} {{ command }}{% endfor %}
"""
  return jinja2.Template(sbatch_template).render(sbatch_meta = sbatch_meta, sbatch_queue = sbatch_queue)

def create_prep_dcard_cfg(cfg):
  """Fills the template of python configuration file for datacard preparation

  Args:
    cfg: contains full paths to the relevant files (input, output, analysis type); see `analyzeConfig`

  Returns:
    Filled template
  """
  cfg_file = """
import FWCore.ParameterSet.Config as cms
import os

process = cms.PSet()
process.fwliteInput = cms.PSet(
    fileNames = cms.vstring('{{ histogramFile }}'),
    maxEvents = cms.int32(-1),
    outputEvery = cms.uint32(100000)
)

process.fwliteOutput = cms.PSet(
    fileName = cms.string('{{ outputFile }}')
)
process.prepareDatacards = cms.PSet(
    processesToCopy = cms.vstring(
        "data_obs",
        "TTW",
        "TTZ",
        "WZ",
        "Rares",
        "fakes_data",
        "flips_data"
    ),
    sf_signal = cms.double(1.),
    signals = cms.vstring(
        "ttH_hww",
        "ttH_hzz",
        "ttH_htt"
    ),
    categories = cms.VPSet(
        cms.PSet(
            input = cms.string("{{ analysisType }}/sel/evt"),
            output = cms.string("ttH_{{ outputCategory }}")
        )
    ),

    histogramToFit = cms.string("{{ histogramToFit }}"),
    histogramToFit_rebin = cms.int32(1),
    setBinsToZeroBelow = cms.double(-1.),

    sysShifts = cms.vstring(
        "CMS_ttHl_btag_HFUp",
        "CMS_ttHl_btag_HFDown",
        "CMS_ttHl_btag_HFStats1Up",
        "CMS_ttHl_btag_HFStats1Down",
        "CMS_ttHl_btag_HFStats2Up",
        "CMS_ttHl_btag_HFStats2Down",
        "CMS_ttHl_btag_LFUp",
        "CMS_ttHl_btag_LFDown",
        "CMS_ttHl_btag_LFStats1Up",
        "CMS_ttHl_btag_LFStats1Down",
        "CMS_ttHl_btag_LFStats2Up",
        "CMS_ttHl_btag_LFStats2Down",
        "CMS_ttHl_btag_cErr1Up",
        "CMS_ttHl_btag_cErr1Down",
        "CMS_ttHl_btag_cErr2Up",
        "CMS_ttHl_btag_cErr2Down",
        "CMS_ttHl_JESUp",
        "CMS_ttHl_JESDown"
    )
)
"""
  return jinja2.Template(cfg_file).render(
    histogramFile = cfg.histogram_file,
    outputFile = cfg.datacard_outputfile,
    analysisType = cfg.analysis_type,
    outputCategory = cfg.output_category)


def create_setup(cfg):
  """Creates the whole workflow setup -- directory tree, configuration files, job execution files
  Args:
    cfg: Configuration object containig relevant full paths (see `analyzeConfig`)
  """

  for k, d in cfg.dirs.items(): create_if_not_exists(d)
  cfg_basenames = []

  for k, v in samples.samples.items():
    if not v["use_it"] or \
        (v["sample_category"] in ["background_data_estimate"] and "DY" not in v["process_name_specific"]): continue
    if not cfg.use_data and v["sample_category"] == "data_obs": continue
    if len(cfg.selected_datasets) > 0 and v["sample_category"] not in cfg.selected_datasets and v["process_name_specific"] not in cfg.selected_datasets: continue
    #if not (v["sample_category"] in ["background_data_estimate"] and "DY" in v["process_name_specific"]): continue

    is_mc = v["type"] == "mc"
    process_name = v["process_name_specific"]
    category_name = v["sample_category"]
    triggers = v["triggers"]


    cfg_outputdir = os.path.join(cfg.dirs[DKEY_CFGS], process_name)
    histogram_outputdir = os.path.join(cfg.dirs[DKEY_HIST], category_name)
    eventlist_outputdir = os.path.join(cfg.dirs[DKEY_EVLIST], category_name)
    for d in [cfg_outputdir, histogram_outputdir, eventlist_outputdir]: create_if_not_exists(d)
    logging.info("Created config and job files for sample %s" % process_name)

    nof_files = v["nof_files"]
    store_dirs = v["local_paths"]
    assert(len(store_dirs) <= 2), "There is more than one secondary dir!"
    primary_store, secondary_store = "", ""
    secondary_files = []
    for store_dir in store_dirs:
      if store_dir["selection"] == "*": primary_store = store_dir["path"]
      else:
        secondary_store = store_dir["path"]
        secondary_files = map(lambda x: int(x), store_dir["selection"].split(","))
    job_ids = generate_file_ids(nof_files, cfg.max_files_per_job)

    lumi_scale = 1. if not (cfg.use_lumi and is_mc) else v["xsection"] * LUMI / v["nof_events"]
    for idx in range(len(job_ids)):
      cfg_basename = "_".join([process_name, str(idx)])
      cfg_basenames.append(cfg_basename)

      cfg_filelist = generate_input_list(job_ids[idx], secondary_files,
                                         primary_store, secondary_store, cfg.debug)
      cfg_outputfile = "_".join([process_name, cfg.lepton_selection, str(idx)]) + ".root"
      cfg_outputfile_fullpath = os.path.join(histogram_outputdir, cfg_outputfile)

      cfg_contents = create_config(cfg_filelist, cfg_outputfile_fullpath, category_name, triggers, is_mc, cfg.use_data, lumi_scale, cfg, idx)
      cfg_file_fullpath = os.path.join(cfg_outputdir,  cfg_basename + ".py")
      with codecs.open(cfg_file_fullpath, "w", "utf-8") as f: f.write(cfg_contents)

      bsh_contents = create_job(cfg.exec_name, cfg_file_fullpath)
      bsh_file_fullpath = os.path.join(cfg.dirs[DKEY_JOBS], cfg_basename + ".sh")
      with codecs.open(bsh_file_fullpath, "w", "utf-8") as f: f.write(bsh_contents)
      add_chmodX(bsh_file_fullpath)

  if cfg.is_makefile:
    commands = map(lambda x: os.path.join(cfg.dirs[DKEY_JOBS], x + ".sh") + \
      " >> " + os.path.join(cfg.dirs[DKEY_LOGS], x + ".log") + " 2>&1", cfg_basenames)
    logging.info("Creating Makefile")
    makefile_contents = create_makefile(commands, num = 20)
    with codecs.open(cfg.makefile_fullpath, 'w', 'utf-8') as f: f.write(makefile_contents)
  elif cfg.is_sbatch:
    logging.info("Creating SLURM jobs")
    commands = map(lambda x: os.path.join(cfg.dirs[DKEY_JOBS], x + ".sh"), cfg_basenames)

    sbatch_logfiles = map(lambda x: os.path.join(cfg.dirs[DKEY_LOGS], x + "-%a.out"), cfg_basenames)
    sbatch_contents = create_sbatch(sbatch_logfiles, commands)
    with codecs.open(cfg.sbatch_fullpath, 'w', 'utf-8') as f: f.write(sbatch_contents)
    add_chmodX(cfg.sbatch_fullpath)

  logging.info("Creating configuration file for data cards")
  dcard_cfg_contents = create_prep_dcard_cfg(cfg)
  with codecs.open(cfg.dcard_cfg_fullpath, 'w', 'utf-8') as f: f.write(dcard_cfg_contents)

  logging.info("Done")

def run_setup(cfg):
  """Runs jobs, hadds output files and prepares the datacard

  Either submits the jobs to SLURM or runs make in parallel, depending on the configuration.
  In the latter case we have to wait it out until subprocess module handles the script execution
  over to this very function. In the former case, however, we have to periodically check SLURM
  queue and see how many submitted jobs are finished. This is done periodically (every cfg.poll_interval
  seconds). If all jobs have finished, the resulting histograms are hadded and passed to
  the datacard preparation binary, which is the final stage of this workflow.
  Stdout and stderr are logged to the files in the upmost directory.

  Args:
    cfg: Configuration object containig relevant full paths (see `analyzeConfig`)
  """
  stdout_file = codecs.open(os.path.join(cfg.output_dir, "stdout.log"), 'w', 'utf-8')
  stderr_file = codecs.open(os.path.join(cfg.output_dir, "stderr.log"), 'w', 'utf-8')

  def run_cmd(command, do_not_log = False):
    """Runs given commands and logs stdout and stderr to files
    """
    if not do_not_log: logging.info(command)
    p = subprocess.Popen(command, shell = True, stdout = subprocess.PIPE, stderr = subprocess.PIPE)
    stdout, stderr = p.communicate()
    stdout_file.write(command + "\n")
    stdout_file.write(stdout)
    stderr_file.write(stderr)
    return stdout

  sbatch_command = cfg.sbatch_fullpath if cfg.is_sbatch \
                   else "make -f %s -j %d" % (cfg.makefile_fullpath, cfg.nof_parallel_jobs)

  stdout = run_cmd(sbatch_command)
  if cfg.is_sbatch:
    sbatch_taskids = "\\|".join([x.split()[-1] for x in stdout.split("\n")[:-1]]) # sbatch job nr is the last one
    whoami = getpass.getuser()
    command_poll = "squeue -u %s | grep \"%s\" | wc -l" % (whoami, sbatch_taskids)
    while True:
      nof_jobs_left = int(run_cmd(command_poll, True).rstrip("\n"))
      if nof_jobs_left != 0: time.sleep(cfg.poll_interval)
      else:                  break
      logging.info("Waiting for sbatch to finish (%d still left) ..." % nof_jobs_left)

  logging.info("Running hadd on all the histograms ...")
  subd_list = []
  for subd_name in os.listdir(cfg.dirs[DKEY_HIST]):
    subd = os.path.join(cfg.dirs[DKEY_HIST], subd_name, "*.root")
    subd_list.append(subd)
  command_hadd = " ".join(["hadd", cfg.histogram_file] + subd_list)
  run_cmd(command_hadd)

  #logging.info("Running %s on the resulting histogram file %s ..." % (cfg.prep_dcard_exec, cfg.histogram_file))
  #command_dcard = "%s %s" % (cfg.prep_dcard_exec, cfg.dcard_cfg_fullpath)
  #run_cmd(command_dcard)

  stdout_file.close()
  stderr_file.close()

  logging.info("Done! The datacard is at %s" % cfg.datacard_outputfile)


if __name__ == '__main__':
  logging.basicConfig(stream = sys.stdout,
                      level = logging.DEBUG,
                      format = '%(asctime)s - %(levelname)s: %(message)s')

  cfg = analyzeCFConfig(output_dir = os.path.join("/home", getpass.getuser(), "tth", "test_triggercutsON"),
                      exec_name = "analyze_charge_flip",
                      lepton_selection = "Tight",
                      max_files_per_job = 20,
                      use_lumi = True,
                      use_data = True,
                      debug = False,
                      running_method = "sbatch",
                      nof_parallel_jobs = 10,
                      poll_interval = 30,
                      selected_datasets = ["data_obs", "DY"],
                      sel_events_file = '',#os.path.join(os.environ["CMSSW_BASE"] , "src/tthAnalysis/HiggsToTauTau/data/eventlist_diff.txt"),
                      prep_dcard_exec = "prepareDatacardsCF"
                      )

  create_setup(cfg)
  run_jobs = query_yes_no("Run %s, hadder and %s?" % (cfg.running_method, cfg.prep_dcard_exec))
  if run_jobs: run_setup(cfg)
  else:        sys.exit(0)
