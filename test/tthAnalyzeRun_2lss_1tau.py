import json, os, codecs, stat, logging, sys, jinja2, subprocess, getpass, time
import tthAnalyzeSamples_2lss_1tau

LUMI = 2301. # 1/pb
DKEY_JOBS = "jobs"       # dir for jobs aka bash scripts that run a single analysis executable
DKEY_CFGS = "cfgs"       # dir for python configuration file for each job
DKEY_HIST = "histograms" # dir for histograms = output of the jobs
DKEY_LOGS = "logs"       # dir for log files (stdout/stderr of jobs)
DKEY_DCRD = "datacards"  # dir for the datacard

version = "2016Jul11_dR03mvaTight"

"""
TODO:
  * isMC is always False in the analysis config since we're missing some necessary input files for MC
"""

def initDict(dictionary, keys):
    """Auxiliary function to initialize dictionary for access with multiple keys
    """
    dictionary_at_keylevel = dictionary
    numKeys = len(keys)
    for idxKey in range(numKeys - 1):
        key = keys[idxKey]
        if key not in dictionary_at_keylevel.keys():
            dictionary_at_keylevel[key] = {}
        dictionary_at_keylevel = dictionary_at_keylevel[key]

class analyzeConfig:
  """Configuration metadata needed to run analysis in a single go.
  
  Sets up a folder structure by defining full path names; no directory creation is delegated here.
  
  Args:
    output_dir: The root output dir -- all configuration, log and output files are stored in its subdirectories
    exec_name: Name of the executable that runs the analysis; possible values are `analyze_2lss_1tau`, `analyze_2los_1tau` and `analyze_1l_2tau`
    charge_selection: either `OS` or `SS` (opposite-sign or same-sign)
    lepton_selection: either `Tight`, `Loose` or `Fakeable`
    max_files_per_job: maximum number of input root files (Ntuples) are allowed to chain together per job
    use_lumi: if True, use lumiSection aka event weight ( = xsection * luminosity / nof events), otherwise uses plain event count
    debug: if True, checks each input root file (Ntuple) before creating the python configuration files
    running_method: either `sbatch` (uses SLURM) or `Makefile`
    nof_parallel_jobs: number of jobs that can be run in parallel (matters only if `running_method` is set to `Makefile`)
    poll_interval: the interval of checking whether all sbatch jobs are completed (matters only if `running_method` is set to `sbatch`)
    addFakes_exec: executable for estimating 'Fakes' background from data
    addFakes_exec: executable for estimating 'Flips' background from data
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
    histogram_files_jobs: the histogram files produced by 'analyze_2lss_1tau' jobs
    histogram_files_jobs_exists: flags indicating if histogram files already exist from a previous execution of 'tthAnalyzeRun_2lss_1tau.py', so that 'analyze_2lss_1tau' jobs do not have to be submitted again	
    histogram_file_hadd_stage1: the histogram file obtained by hadding the output of all jobs
    histogram_file_addFakes: the histogram file containing 'Fakes' background 
    histogram_file_addFlips: the histogram file containing 'Flips' background 
    histogram_file_hadd_stage2: the final histogram file with data-driven background estimates added
    datacard_outputfile: the datacard -- final output file of this execution flow
    addFakes_cfg_fullpath: python configuration file for executable that estimates 'Fakes' background from data 
    addFlips_cfg_fullpath: python configuration file for executable that estimates 'Flips' background from data 
    prep_dcard_cfg_fullpath: python configuration file for datacard preparation executable
  """
  def __init__(self, output_dir, exec_name, lepton_selections, charge_selections, central_or_shifts,
               max_files_per_job, use_lumi, debug, running_method, nof_parallel_jobs, poll_interval, 
	       addFakes_exec, addFlips_exec, prep_dcard_exec, histogram_to_fit):

    assert(exec_name in [ "analyze_2lss_1tau", "analyze_2los_1tau", "analyze_1l_2tau", "analyze_charge_flip" ]), "Invalid exec name: %s" % exec_name
    for charge_selection in charge_selections:
      assert(charge_selection in ["OS", "SS"]),                                         "Invalid charge selection: %s" % charge_selection
    for lepton_selection in lepton_selections:
      assert(lepton_selection in ["Tight", "Loose", "Fakeable"]),                       "Invalid lepton selection: %s" % lepton_selection
    assert(running_method.lower() in ["sbatch", "makefile"]),                           "Invalid running method: %s" % running_method

    self.output_dir = output_dir
    self.exec_name = exec_name
    self.lepton_selections = lepton_selections
    self.charge_selections = charge_selections
    self.central_or_shifts = central_or_shifts
    self.max_files_per_job = max_files_per_job
    self.use_lumi = use_lumi
    self.debug = debug
    self.running_method = running_method
    self.nof_parallel_jobs = nof_parallel_jobs
    self.poll_interval = poll_interval
    self.addFakes_exec = addFakes_exec
    self.addFlips_exec = addFlips_exec
    self.prep_dcard_exec = prep_dcard_exec
    self.histogram_to_fit = histogram_to_fit
    
    self.is_sbatch = False
    self.is_makefile = False
    if self.running_method.lower() == "sbatch": self.is_sbatch = True
    else:                                       self.is_makefile = True

    self.output_category = self.exec_name.replace("analyze_", "")
    self.subdir = {} 
    for lepton_selection in self.lepton_selections:
      for charge_selection in self.charge_selections:
        initDict(self.subdir, [ lepton_selection, charge_selection ])
    	self.subdir[lepton_selection][charge_selection] = \
          "_".join([self.output_category, lepton_selection, charge_selection])
    self.dirs = {} 
    for lepton_selection in self.lepton_selections:
      for charge_selection in self.charge_selections:
        dir_types = [ DKEY_JOBS, DKEY_CFGS, DKEY_HIST, DKEY_LOGS, DKEY_DCRD ]
        initDict(self.dirs, [ lepton_selection, charge_selection ])
        self.dirs[lepton_selection][charge_selection] = \
          { dkey: os.path.join(self.output_dir, dkey, self.subdir[lepton_selection][charge_selection]) for dkey in dir_types }
    print "self.dirs = ", self.dirs

    self.makefile_fullpath = os.path.join(self.output_dir, "Makefile_2lss_1tau")
    self.sbatch_fullpath = os.path.join(self.output_dir, "sbatch_2lss_1tau.sh")
    self.histogram_files_jobs = {}
    self.histogram_files_jobs_exist = {}
    self.histogram_file_hadd_stage1 = os.path.join(self.output_dir, DKEY_HIST, "histograms_harvested_2lss_1tau.root")
    self.histogram_file_addFakes = os.path.join(self.output_dir, DKEY_HIST, "addBackgroundLeptonFakes_2lss_1tau.root")
    self.addFakes_cfg_fullpath = os.path.join(self.output_dir, DKEY_CFGS, "addBackgroundLeptonFakes_2lss_1tau_cfg.py")
    self.histogram_file_addFlips = os.path.join(self.output_dir, DKEY_HIST, "addBackgroundLeptonFlips_2lss_1tau.root")
    self.addFlips_cfg_fullpath = os.path.join(self.output_dir, DKEY_CFGS, "addBackgroundLeptonFlips_2lss_1tau_cfg.py")
    self.histogram_file_hadd_stage2 = os.path.join(self.output_dir, DKEY_HIST, "allHistograms_2lss_1tau.root")
    self.datacard_outputfile = os.path.join(self.output_dir, DKEY_DCRD, "prepareDatacards_2lss_1tau.root")
    self.prep_dcard_cfg_fullpath = os.path.join(self.output_dir, DKEY_CFGS, "prepareDatacards_2lss_1tau_cfg.py")

def query_yes_no(question, default = "yes"):
  """Prompts user yes/no

  Args:
    question: question to ask from the user
    default: default option to use; acceptable values: "yes", "no" or None
  """
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
  """Adds execution rights to a given file.

  Args:
    fullpath: full path of the file to give execution rights (effectively chmod +x'es the thing)
  """
  st = os.stat(fullpath)
  os.chmod(fullpath, st.st_mode | stat.S_IEXEC)

def create_config(root_filenames, output_file, category_name, triggers, lepton_selection, charge_selection, is_mc, central_or_shift, lumi_scale, selEventsFileName_output, cfg, idx):
  """Fill python configuration file for the job exectuable (analysis code)

  Args:
    root_filesnames: list of full path to the input root files (Ntuples)
    output_file: output file of the job -- a histogram
    category_name: either `TTW`, `TTZ`, `WZ`, `Rares`, `data_obs`, `ttH_hww`, `ttH_hzz` or `ttH_htt`
    is_mc: is a given sample an MC (True) or data (False)
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
    triggers_1mu = cms.vstring("HLT_BIT_HLT_IsoMu20_v", "HLT_BIT_HLT_IsoTkMu20_v"),
    use_triggers_1mu = cms.bool({{ use_triggers_1mu }}),
    {% if execName != "analyze_1l_2tau" %}
    triggers_2e = cms.vstring("HLT_BIT_HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v"),
    use_triggers_2e = cms.bool({{ use_triggers_2e }}),
    triggers_2mu = cms.vstring("HLT_BIT_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v",
                               "HLT_BIT_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v"),
    use_triggers_2mu = cms.bool({{ use_triggers_2mu }}),
    triggers_1e1mu = cms.vstring("HLT_BIT_HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v",
                                 "HLT_BIT_HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v"),
    use_triggers_1e1mu = cms.bool({{ use_triggers_1e1mu }}),
    {% endif %}
    apply_offline_e_trigger_cuts_1e = cms.bool(True),
    apply_offline_e_trigger_cuts_2e = cms.bool(False),
    apply_offline_e_trigger_cuts_1e1mu = cms.bool(False),
    
    chargeSelection = cms.string('{{ chargeSelection }}'),
    leptonSelection = cms.string('{{ leptonSelection }}'),

    leptonFakeRateLooseToTightWeight = cms.PSet(
        inputFileName = cms.string('{{ leptonFakeRateLooseToTightWeight_inputFileName }}'),
        histogramName_e = cms.string("FR_mva075_el_data_comb"),
        histogramName_mu = cms.string("FR_mva075_mu_data_comb")
    ),			
    
    isMC = cms.bool({{ isMC }}),
    central_or_shift = cms.string('{{ central_or_shift }}'),
    lumiScale = cms.double({{ lumiScale }}),

    selEventsFileName_input = cms.string(''),
    selEventsFileName_output = cms.string('{{ selEventsFileName_output }}')
)

"""
  leptonFakeRateLooseToTightWeight_inputFileName = None
  if lepton_selection == "Fakeable":
    leptonFakeRateLooseToTightWeight_inputFileName = "tthAnalysis/HiggsToTauTau/data/FR_data_ttH_mva.root"
  else:
    leptonFakeRateLooseToTightWeight_inputFileName = ""	
  leptonFakeRateLooseToTightWeight_inputFileName
  return jinja2.Template(cfg_file).render(
    fileNames = root_filenames,
    execName = cfg.exec_name,
    outputFile = output_file,
    categoryName = category_name,
    use_triggers_1e = "1e" in triggers,
    use_triggers_1mu = "1mu" in triggers,
    use_triggers_2e = "2e" in triggers,
    use_triggers_2mu = "2mu" in triggers,
    use_triggers_1e1mu = "1e1mu" in triggers,	
    chargeSelection = charge_selection,
    leptonSelection = lepton_selection,
    leptonFakeRateLooseToTightWeight_inputFileName = leptonFakeRateLooseToTightWeight_inputFileName,
    isMC = is_mc,      
    central_or_shift = central_or_shift,
    lumiScale = lumi_scale,
    selEventsFileName_output = selEventsFileName_output,  
    idx = idx)

def create_job(working_dir, exec_name, py_cfg):
  """Fills bash job template (run by either sbatch or make)

  Args:
    exec_name: analysis code executable
    py_cfg: full path to the python configuration file

  Returns:
    Filled template
  """
  contents = """#!/bin/bash
echo "current time:"
date
echo "executing 'hostname':"
hostname
echo "initializing cmssw run-time environment"
source /cvmfs/cms.cern.ch/cmsset_default.sh 
cd {{ working_dir }}
cmsenv
cd -
echo "executing 'pwd'"
pwd
{{ exec_name }} {{ py_cfg }}

"""
  return jinja2.Template(contents).render(working_dir = working_dir, exec_name = exec_name, py_cfg = py_cfg)

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

def create_addFakes_cfg(cfg):
  """Fills the template of python configuration file for estimating 'Fakes' background from data

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

process.addBackgroundLeptonFakes = cms.PSet(

    categories = cms.VPSet(
        cms.PSet(
            signal = cms.string("2lss_1tau_SS_Tight"),
	    sideband = cms.string("2lss_1tau_SS_Fakeable")
        ),
        cms.PSet(
            signal = cms.string("2epp_1tau_bloose_SS_Tight"),
	    sideband = cms.string("2epp_1tau_bloose_SS_Fakeable")
        ),        
        cms.PSet(
            signal = cms.string("2epp_1tau_btight_SS_Tight"),
	    sideband = cms.string("2epp_1tau_btight_SS_Fakeable")
        ),        
        cms.PSet(
            signal = cms.string("2emm_1tau_bloose_SS_Tight"),
	    sideband = cms.string("2emm_1tau_bloose_SS_Fakeable")
        ),        
        cms.PSet(
            signal = cms.string("2emm_1tau_btight_SS_Tight"),
	    sideband = cms.string("2emm_1tau_btight_SS_Fakeable")
        ),        
        cms.PSet(
            signal = cms.string("1e1mupp_1tau_bloose_SS_Tight"),
	    sideband = cms.string("1e1mupp_1tau_bloose_SS_Fakeable")
        ),        
        cms.PSet(
            signal = cms.string("1e1mupp_1tau_btight_SS_Tight"),
	    sideband = cms.string("1e1mupp_1tau_btight_SS_Fakeable")
        ),        
        cms.PSet(
            signal = cms.string("1e1mumm_1tau_bloose_SS_Tight"),
	    sideband = cms.string("1e1mumm_1tau_bloose_SS_Fakeable")
        ),        
        cms.PSet(
            signal = cms.string("1e1mumm_1tau_btight_SS_Tight"),
	    sideband = cms.string("1e1mumm_1tau_btight_SS_Fakeable")
        ),        
	cms.PSet(
            signal = cms.string("2mupp_1tau_bloose_SS_Tight"),
	    sideband = cms.string("2mupp_1tau_bloose_SS_Fakeable")
        ),        
        cms.PSet(
            signal = cms.string("2mupp_1tau_btight_SS_Tight"),
	    sideband = cms.string("2mupp_1tau_btight_SS_Fakeable")
        ),        
        cms.PSet(
            signal = cms.string("2mumm_1tau_bloose_SS_Tight"),
	    sideband = cms.string("2mumm_1tau_bloose_SS_Fakeable")
        ),        
        cms.PSet(
            signal = cms.string("2mumm_1tau_btight_SS_Tight"),
	    sideband = cms.string("2mumm_1tau_btight_SS_Fakeable")
        )
    ),

    processData = cms.string("data_obs"),
    processLeptonFakes = cms.string("fakes_data"),
    processesToSubtract = cms.vstring(
	"TTW",
        "TTZ",
        "WZ",
        "Rares"
    ),

    sysShifts = cms.vstring()
)
"""
  return jinja2.Template(cfg_file).render(
    histogramFile = cfg.histogram_file_hadd_stage1,
    outputFile = cfg.histogram_file_addFakes)

def create_addFlips_cfg(cfg):
  """Fills the template of python configuration file for estimating 'Flips' background from data

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

process.addBackgroundLeptonFlips = cms.PSet(

    categories = cms.VPSet(
        cms.PSet(
            signal = cms.string("2lss_1tau_SS_Tight"),
	    sideband = cms.string("2lss_1tau_OS_Tight")
        ),
        cms.PSet(
            signal = cms.string("2epp_1tau_bloose_SS_Tight"),
	    sideband = cms.string("2epp_1tau_bloose_OS_Tight")
        ),        
        cms.PSet(
            signal = cms.string("2epp_1tau_btight_SS_Tight"),
	    sideband = cms.string("2epp_1tau_btight_OS_Tight")
        ),        
        cms.PSet(
            signal = cms.string("2emm_1tau_bloose_SS_Tight"),
	    sideband = cms.string("2emm_1tau_bloose_OS_Tight")
        ),        
        cms.PSet(
            signal = cms.string("2emm_1tau_btight_SS_Tight"),
	    sideband = cms.string("2emm_1tau_btight_OS_Tight")
        ),        
        cms.PSet(
            signal = cms.string("1e1mupp_1tau_bloose_SS_Tight"),
	    sideband = cms.string("1e1mupp_1tau_bloose_OS_Tight")
        ),        
        cms.PSet(
            signal = cms.string("1e1mupp_1tau_btight_SS_Tight"),
	    sideband = cms.string("1e1mupp_1tau_btight_OS_Tight")
        ),        
        cms.PSet(
            signal = cms.string("1e1mumm_1tau_bloose_SS_Tight"),
	    sideband = cms.string("1e1mumm_1tau_bloose_OS_Tight")
        ),        
        cms.PSet(
            signal = cms.string("1e1mumm_1tau_btight_SS_Tight"),
	    sideband = cms.string("1e1mumm_1tau_btight_OS_Tight")
        ),        
	cms.PSet(
            signal = cms.string("2mupp_1tau_bloose_SS_Tight"),
	    sideband = cms.string("2mupp_1tau_bloose_OS_Tight")
        ),        
        cms.PSet(
            signal = cms.string("2mupp_1tau_btight_SS_Tight"),
	    sideband = cms.string("2mupp_1tau_btight_OS_Tight")
        ),        
        cms.PSet(
            signal = cms.string("2mumm_1tau_bloose_SS_Tight"),
	    sideband = cms.string("2mumm_1tau_bloose_OS_Tight")
        ),        
        cms.PSet(
            signal = cms.string("2mumm_1tau_btight_SS_Tight"),
	    sideband = cms.string("2mumm_1tau_btight_OS_Tight")
        )
    ),

    processData = cms.string("data_obs"),
    processLeptonFlips = cms.string("flips_data"),
    processesToSubtract = cms.vstring(
	"TTW",
        "TTZ",
        "WZ",
        "Rares"
    ),

    sysShifts = cms.vstring()
)
"""
  return jinja2.Template(cfg_file).render(
    histogramFile = cfg.histogram_file_hadd_stage1,
    outputFile = cfg.histogram_file_addFlips)

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
            input = cms.string("{{ dir }}/sel/evt"),
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
    histogramFile = cfg.histogram_file_hadd_stage2,
    outputFile = cfg.datacard_outputfile,
    dir = "2lss_1tau_SS_Tight",
    outputCategory = cfg.output_category,
    histogramToFit = cfg.histogram_to_fit)

def create_if_not_exists(dir_fullpath):
  """Creates a given directory if it doesn't exist yet

  Args:
    dir_fullpath: full path to the directory
  """
  if not os.path.exists(dir_fullpath): os.makedirs(dir_fullpath)

def generate_file_ids(nof_files, max_files_per_job):
  """Subsets file ids

    Given N total number of input files, the function splits them into sublists, each
    containing up to M files (maximum number of input files). The function only workds with
    indexes, not full paths, though.

  Args:
    nof_files: Total number of input files
    max_files_per_job: Maximum number of input files a job can take

  Returns:
    File ids split into sublists of length `max_files_per_job`
  """
  file_limits = range(1, nof_files, max_files_per_job)
  file_limits.append(nof_files + 1)
  job_ids = [range(file_limits[i], file_limits[i + 1]) for i in range(len(file_limits) - 1)]
  return job_ids

def generate_input_list(job_ids, secondary_files, primary_store, secondary_store, debug = False):
  """Generates input file list for each job

    Since CRAB was unable to resubmit failed jobs, we had to run the jobs 2nd time. Thus, the full sample
    is complete if we include both storage directories.
    The primary directory contains most of the input files, and the secondary the missing ones.

  Args:
    job_ids: list of file ids (one of the sublists generated in `generate_file_ids`)
    secondary_files: list of input file id's missing in the primary storage
    primary_store: full path to the primary subdirectory containing most of the sample
    secondary_store: full path to the second subdirectory
    debug: if True, checks whether each file is present in the file system
  """
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
  """Creates the whole workflow setup -- directory tree, configuration files, job execution files

  Args:
    cfg: Configuration object containig relevant full paths (see `analyzeConfig`)
  """
  for lepton_selection in cfg.lepton_selections:
    for charge_selection in cfg.charge_selections:	
      for sample_name, dir in cfg.dirs[lepton_selection][charge_selection].items(): 
        create_if_not_exists(dir)

  cfg_basenames = {}   
  for sample_name, sample_info in tthAnalyzeSamples_2lss_1tau.samples.items():
    if not sample_info["use_it"] or sample_info["sample_category"] in \
      ["additional_signal_overlap", "background_data_estimate"]: continue
      
    is_mc = sample_info["type"] == "mc"
    process_name = sample_info["process_name_specific"]
    category_name = sample_info["sample_category"]
    triggers = sample_info["triggers"]

    cfg_outputdir = {}
    histogram_outputdir = {}
    for lepton_selection in cfg.lepton_selections: 
      for charge_selection in cfg.charge_selections:   
        initDict(cfg_outputdir, [ lepton_selection, charge_selection ])
        cfg_outputdir[lepton_selection][charge_selection] = os.path.join(cfg.dirs[lepton_selection][charge_selection][DKEY_CFGS], process_name)
        create_if_not_exists(cfg_outputdir[lepton_selection][charge_selection])
        initDict(histogram_outputdir, [ lepton_selection, charge_selection ])
        histogram_outputdir[lepton_selection][charge_selection] = os.path.join(cfg.dirs[lepton_selection][charge_selection][DKEY_HIST], category_name)
        create_if_not_exists(histogram_outputdir[lepton_selection][charge_selection])
    logging.info("Created config and job files for sample %s" % process_name)

    nof_files = sample_info["nof_files"]
    store_dirs = sample_info["local_paths"]
    assert(len(store_dirs) <= 2), "There is more than one secondary dir!"
    primary_store, secondary_store = "", ""
    secondary_files = []
    for store_dir in store_dirs:
      if store_dir["selection"] == "*": primary_store = store_dir["path"]
      else:
        secondary_store = store_dir["path"]
        secondary_files = map(lambda x: int(x), store_dir["selection"].split(","))
    job_ids = generate_file_ids(nof_files, cfg.max_files_per_job)
    
    lumi_scale = 1. if not (cfg.use_lumi and is_mc) else sample_info["xsection"] * LUMI / sample_info["nof_events"]
    ##print "sample = %s: lumi_scale = %f" % (sample_name, lumi_scale)
    
    for lepton_selection in cfg.lepton_selections:
      for charge_selection in cfg.charge_selections:
	for central_or_shift in cfg.central_or_shifts:
          for idx in range(len(job_ids)):
	    if central_or_shift != "central" and not (lepton_selection == "Tight" and charge_selection == "SS"):
	      continue
            if central_or_shift != "central" and not is_mc:
	      continue
      	    cfg_basename = "_".join([process_name, str(idx), lepton_selection, charge_selection, central_or_shift])
            initDict(cfg_basenames, [ sample_name, lepton_selection, charge_selection, central_or_shift, idx ])
            cfg_basenames[sample_name][lepton_selection][charge_selection][central_or_shift][idx] = cfg_basename

            cfg_filelist = generate_input_list(job_ids[idx], secondary_files, primary_store, secondary_store, cfg.debug)
            cfg_outputfile = "_".join([process_name, lepton_selection, charge_selection, central_or_shift, str(idx)]) + ".root"
            cfg_outputfile_fullpath = os.path.join(histogram_outputdir[lepton_selection][charge_selection], cfg_outputfile)
            initDict(cfg.histogram_files_jobs, [ sample_name, lepton_selection, charge_selection, central_or_shift, idx ])
            cfg.histogram_files_jobs[sample_name][lepton_selection][charge_selection][central_or_shift][idx] = cfg_outputfile_fullpath

            selEventsFileName_output = None
            if central_or_shift == "central" and lepton_selection == "Tight" and charge_selection == "SS" and not is_mc:
              selEventsFileName_output = "selEvents_%s_%s_%s_%i.txt" % (process_name, lepton_selection, charge_selection, idx) 
	    else:
              selEventsFileName_output = ""
            cfg_contents = create_config(cfg_filelist, cfg_outputfile_fullpath, category_name, triggers, lepton_selection, charge_selection, 
	      is_mc, central_or_shift, lumi_scale, selEventsFileName_output, cfg, idx)
            cfg_file_fullpath = os.path.join(cfg_outputdir[lepton_selection][charge_selection], cfg_basename + ".py")
            with codecs.open(cfg_file_fullpath, "w", "utf-8") as f: f.write(cfg_contents)

	    working_dir = os.getcwd()    
            bsh_contents = create_job(working_dir, cfg.exec_name, cfg_file_fullpath)
            bsh_file_fullpath = os.path.join(cfg.dirs[lepton_selection][charge_selection][DKEY_JOBS], cfg_basename + ".sh")
            with codecs.open(bsh_file_fullpath, "w", "utf-8") as f: f.write(bsh_contents)
            add_chmodX(bsh_file_fullpath)
  
  # check if output files already exist from a previous execution of 'tthAnalyzeRun.py'
  for sample_name in cfg.histogram_files_jobs.keys(): 
    for lepton_selection in cfg.histogram_files_jobs[sample_name].keys():
      for charge_selection in cfg.histogram_files_jobs[sample_name][lepton_selection].keys():
	for central_or_shift in cfg.histogram_files_jobs[sample_name][lepton_selection][charge_selection].keys():
          for idx in cfg.histogram_files_jobs[sample_name][lepton_selection][charge_selection][central_or_shift].keys():
            initDict(cfg.histogram_files_jobs_exist, [ sample_name, lepton_selection, charge_selection, central_or_shift, idx ])
	    cfg.histogram_files_jobs_exist[sample_name][lepton_selection][charge_selection][central_or_shift][idx] = \
	      os.path.isfile(cfg.histogram_files_jobs[sample_name][lepton_selection][charge_selection][central_or_shift][idx])

  if cfg.is_makefile:
    commands = []
    for sample_name in cfg.histogram_files_jobs.keys(): 
      for lepton_selection in cfg.histogram_files_jobs[sample_name].keys():
        for charge_selection in cfg.histogram_files_jobs[sample_name][lepton_selection].keys():
	  for central_or_shift in cfg.histogram_files_jobs[sample_name][lepton_selection][charge_selection].keys():
            for idx in cfg.histogram_files_jobs[sample_name][lepton_selection][charge_selection][central_or_shift].keys():	
              if cfg.histogram_files_jobs_exist[sample_name][lepton_selection][charge_selection][central_or_shift][idx]:
                print "output file %s already exists" % \
                  cfg.histogram_files_jobs[sample_name][lepton_selection][charge_selection][central_or_shift][idx]
              else:
                cfg_basename = cfg_basenames[sample_name][lepton_selection][charge_selection][central_or_shift][idx]
                commands.append(os.path.join(cfg.dirs[lepton_selection][charge_selection][DKEY_JOBS], cfg_basename + ".sh") + \
                  " >> " + os.path.join(cfg.dirs[lepton_selection][charge_selection][DKEY_LOGS], cfg_basename + ".log") + " 2>&1")
    logging.info("Creating Makefile")
    makefile_contents = create_makefile(commands, num = 20)
    with codecs.open(cfg.makefile_fullpath, 'w', 'utf-8') as f: f.write(makefile_contents)
  elif cfg.is_sbatch:
    logging.info("Creating SLURM jobs")
    commands = []
    sbatch_logfiles = []
    for sample_name in cfg.histogram_files_jobs.keys(): 
      for lepton_selection in cfg.histogram_files_jobs[sample_name].keys():
        for charge_selection in cfg.histogram_files_jobs[sample_name][lepton_selection].keys():
	  for central_or_shift in cfg.histogram_files_jobs[sample_name][lepton_selection][charge_selection].keys():
            for idx in cfg.histogram_files_jobs[sample_name][lepton_selection][charge_selection][central_or_shift].keys():
              if cfg.histogram_files_jobs_exist[sample_name][lepton_selection][charge_selection][central_or_shift][idx]:
                print "output file %s already exists" % \
                  cfg.histogram_files_jobs[sample_name][lepton_selection][charge_selection][central_or_shift][idx]
              else:
                cfg_basename = cfg_basenames[sample_name][lepton_selection][charge_selection][central_or_shift][idx]
                commands.append(os.path.join(cfg.dirs[lepton_selection][charge_selection][DKEY_JOBS], cfg_basename + ".sh"))
                sbatch_logfiles.append(os.path.join(cfg.dirs[lepton_selection][charge_selection][DKEY_LOGS], cfg_basename + "-%a.out"))
    sbatch_contents = create_sbatch(sbatch_logfiles, commands)
    with codecs.open(cfg.sbatch_fullpath, 'w', 'utf-8') as f: f.write(sbatch_contents)
    add_chmodX(cfg.sbatch_fullpath)

  logging.info("Creating configuration file for executing 'addBackgroundLeptonFakes'")
  addFakes_cfg_contents = create_addFakes_cfg(cfg)
  with codecs.open(cfg.addFakes_cfg_fullpath, 'w', 'utf-8') as f: f.write(addFakes_cfg_contents)

  logging.info("Creating configuration file for executing 'addBackgroundLeptonFlips'")
  addFlips_cfg_contents = create_addFlips_cfg(cfg)
  with codecs.open(cfg.addFlips_cfg_fullpath, 'w', 'utf-8') as f: f.write(addFlips_cfg_contents)  

  logging.info("Creating configuration file for executing 'prepareDatacards'")
  prep_dcard_cfg_contents = create_prep_dcard_cfg(cfg)
  with codecs.open(cfg.prep_dcard_cfg_fullpath, 'w', 'utf-8') as f: f.write(prep_dcard_cfg_contents)

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
  stdout_file = codecs.open(os.path.join(cfg.output_dir, "stdout_2lss_1tau.log"), 'w', 'utf-8')
  stderr_file = codecs.open(os.path.join(cfg.output_dir, "stderr_2lss_1tau.log"), 'w', 'utf-8')

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
    if len(sbatch_taskids) > 0:
      whoami = getpass.getuser()
      command_poll = "squeue -u %s | grep \"%s\" | wc -l" % (whoami, sbatch_taskids)
      while True:
        nof_jobs_left = int(run_cmd(command_poll, True).rstrip("\n"))
        if nof_jobs_left != 0: time.sleep(cfg.poll_interval)
        else:                  break
        logging.info("Waiting for sbatch to finish (%d still left) ..." % nof_jobs_left)
  
  logging.info("Running 'hadd' on histograms produced by 'analyze_2lss_1tau' jobs ...")
  inputFiles_stage1 = []  
  for sample_name, sample_info in tthAnalyzeSamples_2lss_1tau.samples.items():
    if not sample_name in cfg.histogram_files_jobs.keys():
      continue
    inputFiles_sample = []
    for lepton_selection in cfg.histogram_files_jobs[sample_name].keys():
      for charge_selection in cfg.histogram_files_jobs[sample_name][lepton_selection].keys():
	for central_or_shift in cfg.histogram_files_jobs[sample_name][lepton_selection][charge_selection].keys():
          for idx in cfg.histogram_files_jobs[sample_name][lepton_selection][charge_selection][central_or_shift].keys():
            inputFile = cfg.histogram_files_jobs[sample_name][lepton_selection][charge_selection][central_or_shift][idx]
            inputFiles_sample.append(inputFile)
    process_name = sample_info["process_name_specific"]
    histogram_file_hadd_sample = cfg.histogram_file_hadd_stage1.replace(".root", "_%s.root" % process_name)
    if os.path.isfile(histogram_file_hadd_sample):
      print "hadd file %s already exists" % histogram_file_hadd_sample
    else:
      run_cmd(" ".join(["rm", histogram_file_hadd_sample]))
      command_hadd_sample = " ".join(["hadd", histogram_file_hadd_sample] + inputFiles_sample)
      run_cmd(command_hadd_sample)
      inputFiles_stage1.append(histogram_file_hadd_sample)
  if os.path.isfile(cfg.histogram_file_hadd_stage1):
    print "hadd file %s already exists" % cfg.histogram_file_hadd_stage1
  else:
    run_cmd(" ".join(["rm", cfg.histogram_file_hadd_stage1]))
    command_hadd_stage1 = " ".join(["hadd", cfg.histogram_file_hadd_stage1] + inputFiles_stage1)
    run_cmd(command_hadd_stage1)

  logging.info("Running 'addBackgroundLeptonFakes' ...")
  command_addFakes = "%s %s" % (cfg.addFakes_exec, cfg.addFakes_cfg_fullpath)
  run_cmd(command_addFakes)

  logging.info("Running 'addBackgroundLeptonFlips' ...")
  command_addFlips = "%s %s" % (cfg.addFlips_exec, cfg.addFlips_cfg_fullpath)
  run_cmd(command_addFlips)

  logging.info("Running 'hadd' to produce final file containing all histograms ...")
  subd_list_stage2 = []
  subd_list_stage2.append(cfg.histogram_file_hadd_stage1)
  subd_list_stage2.append(cfg.histogram_file_addFakes)
  subd_list_stage2.append(cfg.histogram_file_addFlips)	
  run_cmd(" ".join(["rm", cfg.histogram_file_hadd_stage2]))
  command_hadd_stage2 = " ".join(["hadd", cfg.histogram_file_hadd_stage2] + subd_list_stage2)
  run_cmd(command_hadd_stage2)

  logging.info("Running '%s' on the resulting histogram file %s ..." % (cfg.prep_dcard_exec, cfg.histogram_file_hadd_stage2))
  command_dcard = "%s %s" % (cfg.prep_dcard_exec, cfg.prep_dcard_cfg_fullpath)
  run_cmd(command_dcard)

  stdout_file.close()
  stderr_file.close()

  logging.info("Done! The datacard is at %s" % cfg.datacard_outputfile)

if __name__ == '__main__':
  logging.basicConfig(stream = sys.stdout,
                      level = logging.INFO,
                      format = '%(asctime)s - %(levelname)s: %(message)s')

  cfg = analyzeConfig(output_dir = os.path.join("/home", getpass.getuser(), "ttHAnalysis", version),
                      exec_name = "analyze_2lss_1tau",
		      lepton_selections = [ "Tight", "Fakeable" ],	
                      charge_selections = [ "OS", "SS" ],
		      central_or_shifts = [ 
			"central",
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
	              ],
                      max_files_per_job = 30,
                      use_lumi = True,
                      debug = False,
                      running_method = "sbatch",
                      nof_parallel_jobs = 10,
                      poll_interval = 30,
		      addFakes_exec = "addBackgroundLeptonFakes",
                      addFlips_exec = "addBackgroundLeptonFlips", 
                      prep_dcard_exec = "prepareDatacards",
                      histogram_to_fit = "mvaDiscr_2lss")

  create_setup(cfg)
  run_jobs = query_yes_no("Run %s, hadder and %s?" % (cfg.running_method, cfg.prep_dcard_exec))
  if run_jobs: run_setup(cfg)
  else:        sys.exit(0)

