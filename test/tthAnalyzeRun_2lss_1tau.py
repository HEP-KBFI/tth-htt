#!/usr/bin/env python
import os, logging, sys, getpass, argparse, datetime
from tthAnalysis.HiggsToTauTau.configs.analyzeConfig_2lss_1tau import analyzeConfig_2lss_1tau
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no
from tthAnalysis.HiggsToTauTau.analysisSettings import systematics

#--------------------------------------------------------------------------------
# NOTE: set mode flag to
#   'VHbb'                        : to run the analysis directly on the VHbb Ntuples
#                                  (to e.g. produce the RLE files to run the tthProdNtuple and ttHAddMEM steps)
#   'addMEM'                      : to run the analysis on the Ntuples with MEM variables added
#   'forBDTtraining_beforeAddMEM' : to run the analysis on the Ntuples without MEM variables added,
#                                   and with a relaxed event selection, to increase the BDT training statistics
#   'forBDTtraining_afterAddMEM'  : to run the analysis on the Ntuples with MEM variables added,
#                                   and with a relaxed event selection, to increase the BDT training statistics
#--------------------------------------------------------------------------------

# E.g. to run: ./tthAnalyzeRun_2lss_1tau.py -v 2017Dec13 -mode VHbb -e 2017 --use-prod-ntuples

#TODO: needs actual Ntuples

mode_choices               = ['VHbb', 'addMEM', 'forBDTtraining_beforeAddMEM', 'forBDTtraining_afterAddMEM', 'sync']
era_choices                = ['2017']
sys_choices                = [ 'central', 'full', 'extended' ]
default_resubmission_limit = 4
systematics.full           = systematics.an_common
systematics.extended       = systematics.an_extended

class SmartFormatter(argparse.HelpFormatter):
  def _split_lines(self, text, width):
    if text.startswith('R|'):
      return text[2:].splitlines()
    return argparse.HelpFormatter._split_lines(self, text, width)

parser = argparse.ArgumentParser(
  formatter_class = lambda prog: SmartFormatter(prog, max_help_position = 45)
)
run_parser = parser.add_mutually_exclusive_group()
parser.add_argument('-v', '--version',
  type = str, dest = 'version', metavar = 'version', default = None, required = True,
  help = 'R|Analysis version (e.g. %s)' % datetime.date.today().strftime('%Y%b%d'),
)
parser.add_argument('-m', '--mode',
  type = str, dest = 'mode', metavar = 'mode', default = None, required = True,
  choices = mode_choices,
  help = 'R|Analysis type (choices: %s)' % ', '.join(map(lambda choice: "'%s'" % choice, mode_choices)),
)
parser.add_argument('-e', '--era',
  type = str, dest = 'era', metavar = 'era', choices = era_choices, default = None, required = True,
  help = 'R|Era of data/MC (choices: %s)' % ', '.join(map(lambda choice: "'%s'" % choice, era_choices)),
)
parser.add_argument('-s', '--systematics',
  type = str, dest = 'systematics', metavar = 'mode', choices = sys_choices,
  default = 'central', required = False,
  help = 'R|Systematic uncertainties (choices: %s)' % ', '.join(map(lambda choice: "'%s'" % choice, sys_choices)),
)
parser.add_argument('-p', '--use-production-ntuples',
  dest = 'use_production_ntuples', action = 'store_true', default = False,
  help = 'R|Use production Ntuples'
)
parser.add_argument('-d', '--dry-run',
  dest = 'dry_run', action = 'store_true', default = False,
  help = 'R|Do not submit the jobs, just generate the necessary shell scripts'
)
parser.add_argument('-r', '--resubmission-limit',
  type = int, dest = 'resubmission_limit', metavar = 'number', default = default_resubmission_limit,
  required = False,
  help = 'R|Maximum number of resubmissions (default: %i)' % default_resubmission_limit
)
parser.add_argument('-R', '--disable-resubmission',
  dest = 'disable_resubmission', action = 'store_false', default = True,
  help = 'R|Disable resubmission (overwrites option -r/--resubmission-limit)'
)
run_parser.add_argument('-E', '--no-exec',
  dest = 'no_exec', action = 'store_true', default = False,
  help = 'R|Do not submit the jobs (ignore prompt)',
)
run_parser.add_argument('-A', '--auto-exec',
  dest = 'auto_exec', action = 'store_true', default = False,
  help = 'R|Automatically submit the jobs (ignore prompt)',
)
parser.add_argument('-V', '--verbose',
  dest = 'verbose', action = 'store_true', default = False,
  help = 'R|Increase verbosity level in sbatchManager'
)
args = parser.parse_args()

use_prod_ntuples     = args.use_production_ntuples
mode                 = args.mode
era                  = args.era
version              = args.version
resubmit             = args.disable_resubmission
no_exec              = args.no_exec
auto_exec            = args.auto_exec
max_job_resubmission = args.resubmission_limit if resubmit else 1
max_files_per_job    = 10 if use_prod_ntuples else 100
central_or_shift     = getattr(systematics, args.systematics)

hadTau_selection                   = None
hadTau_selection_relaxed           = None
changeBranchNames                  = use_prod_ntuples
applyFakeRateWeights               = None
MEMbranch                          = ''
hadTauFakeRateWeight_inputFileName = "tthAnalysis/HiggsToTauTau/data/FR_tau_2016.root" #TODO update

# Karl: temporarily disable other modes until we've proper Ntuples
if mode not in ['VHbb', 'sync']:
  raise ValueError("Only VHbb and sync mode available")

if mode == "VHbb":
  if use_prod_ntuples:
    from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017_prodNtuples import samples_2017
  else:
    from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017 import samples_2017

  hadTau_selection     = "dR03mvaMedium"
  applyFakeRateWeights = "2lepton"
elif mode == "addMEM":
#  from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017_2lss1tau_addMEM import samples_2017
  changeBranchNames    = True
  MEMbranch            = 'memObjects_2lss_1tau_lepFakeable_tauTight_dR03mvaMedium'
  hadTau_selection     = "dR03mvaMedium"
  applyFakeRateWeights = "2lepton"
elif mode == "forBDTtraining_beforeAddMEM":
#  if use_prod_ntuples:
#    from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017_prodNtuples_FastSim import samples_2017
#  else:
#    from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017_FastSim import samples_2017
  hadTau_selection         = "dR03mvaMedium"
  hadTau_selection_relaxed = "dR03mvaMedium"
  applyFakeRateWeights     = "2lepton"
elif mode == "forBDTtraining_afterAddMEM":
#  from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017_addMEM_2lss1tau import samples_2017
  changeBranchNames        = True
  MEMbranch                = 'memObjects_2lss_1tau_lepLoose_tauTight_dR03mvaMedium'
  hadTau_selection         = "dR03mvaMedium"
  hadTau_selection_relaxed = "dR03mvaMedium"
  applyFakeRateWeights     =  "2lepton"
  max_files_per_job        = 10
elif mode == "sync":
  from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017_addMEM_sync import samples_2017

  changeBranchNames    = True
  MEMbranch            = 'memObjects_2lss_1tau_lepFakeable_tauTight_dR03mvaMedium'
  hadTau_selection     = "dR03mvaMedium"
  applyFakeRateWeights = "2lepton"
else:
  raise ValueError("Invalid Configuration parameter 'mode' = %s !!" % mode)

if era == "2017":
  from tthAnalysis.HiggsToTauTau.analysisSettings import lumi_2017 as lumi
  samples = samples_2017
else:
  raise ValueError("Invalid Configuration parameter 'era' = %s !!" % era)

for sample_name, sample_info in samples.items():
  if sample_name.startswith('/Tau/Run'):
    sample_info["use_it"] = False

if __name__ == '__main__':
  logging.basicConfig(
    stream = sys.stdout,
    level  = logging.INFO,
    format = '%(asctime)s - %(levelname)s: %(message)s',
  )

  logging.info(
    "Running the jobs with the following systematic uncertainties enabled: %s" % \
    ', '.join(central_or_shift)
  )

  configDir = os.path.join("/home",       getpass.getuser(), "ttHAnalysis", era, version)
  outputDir = os.path.join("/hdfs/local", getpass.getuser(), "ttHAnalysis", era, version)

  job_statistics_summary = {}
  run_analysis           = False
  is_last_resubmission   = False

  for idx_job_resubmission in range(max_job_resubmission):
    if is_last_resubmission:
      continue
    logging.info("Job submission #%i:" % (idx_job_resubmission + 1))

    # histograms for 2D bin optimization
    listOfHistNames = [
      '%s_from%i_to_%i' % (varName, nbinsStart, nbinsTarget)
        for varName     in ['HTT', 'noHTT', 'HTTMEM', 'oldVarA']
        for nbinsStart  in [15, 20]
        for nbinsTarget in range(5, 11)
    ]

    analysis = analyzeConfig_2lss_1tau(
      configDir                 = configDir,
      outputDir                 = outputDir,
      executable_analyze        = "analyze_2lss_1tau",
      cfgFile_analyze           = "analyze_2lss_1tau_cfg.py",
      samples                   = samples,
      changeBranchNames         = changeBranchNames,
      MEMbranch                 = MEMbranch,
      lepton_charge_selections  = [ "SS" ] if mode.find("forBDTtraining") != -1 else [ "OS", "SS" ],
      hadTau_selection          = hadTau_selection,
      # CV: apply "fake" background estimation to leptons only and not to hadronic taus, as discussed on slide 10 of
      #     https://indico.cern.ch/event/597028/contributions/2413742/attachments/1391684/2120220/16.12.22_ttH_Htautau_-_Review_of_systematics.pdf
      applyFakeRateWeights      = applyFakeRateWeights,
      chargeSumSelections       = [ "OS"] if mode.find("forBDTtraining") != -1 else [ "OS", "SS" ],
      central_or_shifts         = central_or_shift,
      max_files_per_job         = max_files_per_job,
      era                       = era,
      use_lumi                  = True,
      lumi                      = lumi,
      debug                     = False,
      running_method            = "sbatch",
      num_parallel_jobs         = 100, # KE: run up to 100 'hadd' jobs in parallel on batch system
      executable_addBackgrounds = "addBackgrounds",
      # CV: use common executable for estimating jet->lepton and jet->tau_h fake background
      executable_addFakes       = "addBackgroundLeptonFakes",
      executable_addFlips       = "addBackgroundLeptonFlips",
      histograms_to_fit         = [
        "EventCounter",
        "numJets",
        "mvaOutput_2lss_ttV",
        "mvaOutput_2lss_ttbar",
        "mvaDiscr_2lss",
        "mvaOutput_2lss_1tau_ttV",
        "mvaOutput_2lss_1tau_ttbar",
        "mvaDiscr_2lss_1tau",
        "mvaOutput_2lss_1tau_ttV_wMEM",
        "mvaOutput_2lss_1tau_ttbar_wMEM",
        "mvaDiscr_2lss_1tau_wMEM",
        "mvaOutput_Hj_tagger",
        "mvaOutput_Hjj_tagger",
        "mTauTauVis1_sel",
        "mTauTauVis2_sel",
        "memOutput_LR",
        "memDiscr",
        #
        "mvaOutput_2lss_oldVarA_tt",
        "mvaOutput_2lss_oldVarA_ttV",
        "mvaOutput_2lss_noHTT_tt",
        "mvaOutput_2lss_noHTT_ttV",
        "mvaOutput_2lss_HTT_tt",
        "mvaOutput_2lss_HTTMEM_tt",
        "mvaOutput_2lss_HTTMEM_ttV",
        "mvaOutput_2lss_HTT_LepID_tt",
        #
        "mvaOutput_2lss_HTTMEM_1B",
        "mvaOutput_2lss_HTT_1B",
        "mvaOutput_2lss_noHTT_1B",
        "mvaOutput_2lss_oldVarA_1B",
        "mvaOutput_2lss_oldVarA_2MEM",
        "mvaOutput_2lss_noHTT_2MEM",
        "mvaOutput_2lss_noHTT_2HTT",
      ] + listOfHistNames,
      select_rle_output         = True,
      verbose                   = idx_job_resubmission > 0,
      dry_run                   = args.dry_run,
      do_sync                   = mode == 'sync',
    )

    if mode.find("forBDTtraining") != -1:
      analysis.set_BDT_training(hadTau_selection_relaxed, hadTauFakeRateWeight_inputFileName)

    job_statistics = analysis.create()
    for job_type, num_jobs in job_statistics.items():
      logging.info(" #jobs of type '%s' = %i" % (job_type, num_jobs))
    job_statistics_summary[idx_job_resubmission] = job_statistics

    if idx_job_resubmission == 0:
      if auto_exec:
        run_analysis = True
      elif no_exec:
        run_analysis = False
      else:
        run_analysis = query_yes_no("Start jobs ?")
    if run_analysis:
      analysis.run()
    else:
      sys.exit(0)

    if job_statistics['analyze'] == 0:
      is_last_resubmission = True

  for idx_job_resubmission in job_statistics_summary.keys():
    logging.info("Job submission #%i:" % (idx_job_resubmission + 1))
    for job_type, num_jobs in job_statistics_summary[idx_job_resubmission].items():
      logging.info(" #jobs of type '%s' = %i" % (job_type, num_jobs))
