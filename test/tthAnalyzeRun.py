import json, os, codecs, stat, logging, sys, jinja2, subprocess, getpass, time
import tthAnalyzeSamples

LUMI = 10000.
DKEY_JOBS = "jobs"
DKEY_CFGS = "cfgs"
DKEY_HIST = "histograms"
DKEY_LOGS = "logs"
DKEY_DCRD = "datacards"

class analyzeConfig:
  def __init__(self, output_dir, exec_name, charge_selection, lepton_selection,
               max_files_per_job, use_lumi, debug, running_method, nof_parallel_jobs,
               poll_interval, prep_dcard_exec, histogram_to_fit):

    assert(exec_name in ["analyze_2lss_1tau", "analyze_2los_1tau", "analyze_1l_2tau"]), "Invalid exec name: %s" % exec_name
    assert(charge_selection in ["OS", "SS"]),                                           "Invalid charge selection: %s" % charge_selection
    assert(lepton_selection in ["Tight", "Loose", "Fakeable"]),                         "Invalid lepton selection: %s" % lepton_selection
    assert(running_method.lower() in ["sbatch", "makefile"]),                           "Invalid running method: %s" % running_method

    self.output_dir = output_dir
    self.exec_name = exec_name
    self.charge_selection = charge_selection
    self.lepton_selection = lepton_selection
    self.max_files_per_job = max_files_per_job
    self.use_lumi = use_lumi
    self.debug = debug
    self.running_method = running_method
    self.nof_parallel_jobs = nof_parallel_jobs
    self.poll_interval = poll_interval
    self.prep_dcard_exec = prep_dcard_exec
    self.histogram_to_fit = histogram_to_fit
    
    self.is_sbatch = False
    self.is_makefile = False
    if self.running_method.lower() == "sbatch": self.is_sbatch = True
    else:                                       self.is_makefile = True

    self.output_category = self.exec_name.replace("analyze_", "")
    self.subdir = "_".join([self.output_category, self.charge_selection, self.lepton_selection])
    self.analysis_type = self.subdir
    dir_types = [DKEY_JOBS, DKEY_CFGS, DKEY_HIST, DKEY_LOGS, DKEY_DCRD]
    self.dirs = {dkey: os.path.join(self.output_dir, dkey, self.subdir) for dkey in dir_types}

    self.makefile_fullpath = os.path.join(self.output_dir, "Makefile")
    self.sbatch_fullpath = os.path.join(self.output_dir, "sbatch.sh")
    self.histogram_file = os.path.join(self.dirs[DKEY_HIST], "allHistograms.root")
    self.datacard_outputfile = os.path.join(self.dirs[DKEY_DCRD], "prepareDatacards.root")
    self.dcard_cfg_fullpath = os.path.join(self.dirs[DKEY_CFGS], "prepareDatacards_cfg.py")

def query_yes_no(question, default = "yes"):
  default = default.lower()
  valid = { "yes": True, "y": True, "ye": True, "no": False, "n": False }
  if default is None:    prompt = " [y/n] "
  elif default == "yes": prompt = " [Y/n] "
  elif default == "no":  prompt = " [y/N] "
  else:
    raise ValueError("Invalid default answer: '%s'" % default)

  while True:
    sys.stdout.write(question + prompt)
    choice = raw_input().lower()
    if default is not None and choice == "": return valid[default]
    elif choice in valid:                    return valid[choice]
    else:
      sys.stdout.write("Please respond with 'yes' or 'no' (or 'y' or 'n').\n")

def add_chmodX(fullpath):
  st = os.stat(fullpath)
  os.chmod(fullpath, st.st_mode | stat.S_IEXEC)

def create_config(root_filenames, output_file, category_name, is_mc, lumi_scale, cfg, idx):
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
    use_triggers_1e = cms.bool(True),
    triggers_1mu = cms.vstring("HLT_BIT_HLT_IsoMu20_v", "HLT_BIT_HLT_IsoTkMu20_v"),
    use_triggers_1mu = cms.bool(True),
    {% if execName != "analyze_1l_2tau" %}
    triggers_2e = cms.vstring("HLT_BIT_HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v"),
    use_triggers_2e = cms.bool(True),
    triggers_2mu = cms.vstring("HLT_BIT_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v",
                               "HLT_BIT_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v"),
    use_triggers_2mu = cms.bool(True),
    triggers_1e1mu = cms.vstring("HLT_BIT_HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v",
                                 "HLT_BIT_HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v"),
    use_triggers_1e1mu = cms.bool(True),
    {% endif %}
    chargeSelection = cms.string('{{ chargeSelection }}'),
    leptonSelection = cms.string('{{ leptonSelection }}'),
    
    isMC = cms.bool({{ isMC }}),
    central_or_shift = cms.string('central'),
    lumiScale = cms.double({{ lumiScale }}),

    selEventsFileName_input = cms.string(''),
    selEventsFileName_output = cms.string('')
)

"""
  return jinja2.Template(cfg_file).render(
    fileNames = root_filenames,
    execName = cfg.exec_name,
    outputFile = output_file,
    categoryName = category_name,
    chargeSelection = cfg.charge_selection,
    leptonSelection = cfg.lepton_selection,
    isMC = False, # NOTE: temporary fix; previously: is_mc
    lumiScale = lumi_scale,
    idx = idx)

def create_job(exec_name, py_cfg):
  contents = """#!/bin/bash
{{ exec_name }} {{ py_cfg }}

"""
  return jinja2.Template(contents).render(exec_name = exec_name, py_cfg = py_cfg)

def create_makefile(commands, num):
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

def create_sbatch(sbatch_logfiles, commands):
  sbatch_meta = zip(sbatch_logfiles, commands)
  sbatch_template = """#!/bin/bash
{% for logfile,command in sbatch_meta %}
sbatch --output={{ logfile }} {{ command }}{% endfor %}
"""
  return jinja2.Template(sbatch_template).render(sbatch_meta = sbatch_meta)

def create_prep_dcard_cfg(cfg):
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
    outputCategory = cfg.output_category,
    histogramToFit = cfg.histogram_to_fit)

def create_if_not_exists(dir_fullpath):
  if not os.path.exists(dir_fullpath): os.makedirs(dir_fullpath)

def generate_job_ids(nof_files, max_files_per_job):
  file_limits = range(1, nof_files, max_files_per_job)
  file_limits.append(nof_files + 1)
  job_ids = [range(file_limits[i], file_limits[i + 1]) for i in range(len(file_limits) - 1)]
  return job_ids

def generate_input_list(job_ids, secondary_files, primary_store, secondary_store, debug = False):
  input_list = []
  for job in job_ids:
    actual_storedir = secondary_store if job in secondary_files else primary_store
    input_file = os.path.join(actual_storedir, "000" + str(job / 1000), "tree_" + str(job) + ".root")
    if debug and not os.path.exists(input_file):
      logging.error("File %s doesn't exists!" % input_file)
      sys.exit(2)
    input_list.append(input_file)
  return input_list

def create_setup(cfg):
  for k, d in cfg.dirs.items(): create_if_not_exists(d)
  cfg_basenames = []

  for k, v in tthAnalyzeSamples.samples.items():
    if not v["use_it"] or v["sample_category"] in \
      ["additional_signal_overlap", "background_data_estimate"]: continue

    is_mc = v["type"] == "mc"
    process_name = v["process_name_specific"]
    category_name = v["sample_category"]
    
    cfg_outputdir = os.path.join(cfg.dirs[DKEY_CFGS], process_name)
    histogram_outputdir = os.path.join(cfg.dirs[DKEY_HIST], category_name)
    for d in [cfg_outputdir, histogram_outputdir]: create_if_not_exists(d)
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
    job_ids = generate_job_ids(nof_files, cfg.max_files_per_job)

    lumi_scale = 1. if not (cfg.use_lumi and is_mc) else v["xsection"] * LUMI / v["nof_events"]
    for idx in range(len(job_ids)):
      cfg_basename = "_".join([process_name, str(idx)])
      cfg_basenames.append(cfg_basename)

      cfg_filelist = generate_input_list(job_ids[idx], secondary_files,
                                         primary_store, secondary_store, cfg.debug)
      cfg_outputfile = "_".join([process_name, cfg.charge_selection, cfg.lepton_selection, str(idx)]) + ".root"
      cfg_outputfile_fullpath = os.path.join(histogram_outputdir, cfg_outputfile)

      cfg_contents = create_config(cfg_filelist, cfg_outputfile_fullpath, category_name, is_mc, lumi_scale, cfg, idx)
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
  stdout_file = codecs.open(os.path.join(cfg.output_dir, "stdout.log"), 'w', 'utf-8')
  stderr_file = codecs.open(os.path.join(cfg.output_dir, "stderr.log"), 'w', 'utf-8')

  def run_cmd(command, do_not_log = False):
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
    sbatch_taskids = "\\|".join([x.split()[-1] for x in stdout.split("\n")[:-1]])
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

  logging.info("Running %s on the resulting histogram file %s ..." % (cfg.prep_dcard_exec, cfg.histogram_file))
  command_dcard = "%s %s" % (cfg.prep_dcard_exec, cfg.dcard_cfg_fullpath)
  run_cmd(command_dcard)

  stdout_file.close()
  stderr_file.close()

  logging.info("Done")

if __name__ == '__main__':
  logging.basicConfig(stream = sys.stdout,
                      level = logging.INFO,
                      format = '%(asctime)s - %(levelname)s: %(message)s')

  cfg = analyzeConfig(output_dir = "/home/karl/test",
                      exec_name = "analyze_2lss_1tau",
                      charge_selection = "SS",
                      lepton_selection = "Tight",
                      max_files_per_job = 30,
                      use_lumi = True,
                      debug = False,
                      running_method = "sbatch",
                      nof_parallel_jobs = 10,
                      poll_interval = 30,
                      prep_dcard_exec = "prepareDatacards",
                      histogram_to_fit = "mvaDiscr_2lss")

  create_setup(cfg)
  run_jobs = query_yes_no("Run %s, hadder and %s?" % (cfg.running_method, cfg.prep_dcard_exec))
  if run_jobs: run_setup(cfg)
  else:        sys.exit(0)

