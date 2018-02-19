#!/usr/bin/env python
import os, logging, sys, getpass, argparse, datetime
from tthAnalysis.HiggsToTauTau.configs.analyzeConfig_3l_1tau import analyzeConfig_3l_1tau
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no
from tthAnalysis.HiggsToTauTau.analysisSettings import systematics

#--------------------------------------------------------------------------------
# NOTE: set mode flag to
#   'VHbb'                        : to run the analysis directly on the VHbb Ntuples
#                                   (to e.g. produce the RLE files to run the tthProdNtuple and ttHAddMEM steps)
#   'addMEM'                      : to run the analysis on the Ntuples with MEM variables added
#   'forBDTtraining_beforeAddMEM' : to run the analysis with a relaxed event selection,
#                                   to increase the BDT training statistics
#   'forBDTtraining_afterAddMEM'  : to run the analysis on the Ntuples with MEM variables added, and
#                                   with a relaxed event selection, to increase the BDT training statistics
#--------------------------------------------------------------------------------

# E.g.: ./tthAnalyzeRun_3l_1tau.py -v 2017Dec13 -mode VHbb -e 2017 --use-prod-ntuples

#TODO: needs actual Ntuples

mode_choices               = ['VHbb', 'addMEM', 'forBDTtraining_beforeAddMEM', 'forBDTtraining_afterAddMEM']
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
max_job_resubmission = args.resubmission_limit if resubmit else 1
max_files_per_job    = 10 if use_prod_ntuples else 100
central_or_shift     = getattr(systematics, args.systematics)

hadTau_selection                   = None
hadTau_selection_relaxed           = None
changeBranchNames                  = use_prod_ntuples
applyFakeRateWeights               = None
MEMbranch                          = ''
hadTauFakeRateWeight_inputFileName = "tthAnalysis/HiggsToTauTau/data/FR_tau_2016.root" #TODO update

if mode != "VHbb":
  raise ValueError("Only VHbb mode available")

if mode == "VHbb":
  if use_prod_ntuples:
    from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017_prodNtuples_test import samples_2017
  else:
    from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017_test import samples_2017

  for sample_name, sample_info in samples_2017.items():
    if sample_name in [
        #TODO list of samples collected with tau triggers?
      ]:
      sample_info["use_it"] = False

  hadTau_selection = "dR03mvaMedium"
  applyFakeRateWeights = "3lepton"
elif mode == "addMEM":
#  from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017_3l1tau_addMEM import samples_2017
  hadTau_selection     = "dR03mvaMedium"
  changeBranchNames    = True
  applyFakeRateWeights = "3lepton"
  MEMbranch            = 'memObjects_3l_1tau_lepFakeable_tauTight_dR03mvaMedium'
elif mode == "forBDTtraining_beforeAddMEM":
#  if use_prod_ntuples:
#    from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017_prodNtuples_FastSim import samples_2017
#  else:
#    from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017_FastSim import samples_2017
  applyFakeRateWeights     = "4L"
  hadTau_selection         = "dR03mvaVTight"
  hadTau_selection_relaxed = "dR03mvaVVLoose"
elif mode == "forBDTtraining_afterAddMEM":
#  from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017_3l1tau_addMEM_forBDTtraining import samples_2017
  changeBranchNames        = True
  applyFakeRateWeights     = "4L"
  hadTau_selection         = "dR03mvaVTight"
  hadTau_selection_relaxed = "dR03mvaVVLoose"
  MEMbranch                = 'memObjects_3l_1tau_lepLoose_tauTight_dR03mvaVVLoose'
else:
  raise ValueError("Invalid Configuration parameter 'mode' = %s!" % mode)

if era == "2017":
  from tthAnalysis.HiggsToTauTau.analysisSettings import lumi_2017 as lumi
  samples = samples_2017
else:
  raise ValueError("Invalid Configuration parameter 'era' = %s!" % era)

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

  job_statistics_summary = {}
  run_analysis           = False
  is_last_resubmission   = False

  for idx_job_resubmission in range(max_job_resubmission):
    if is_last_resubmission:
      continue
    logging.info("Job submission #%i:" % (idx_job_resubmission + 1))

    analysis = analyzeConfig_3l_1tau(
      configDir = os.path.join("/home",       getpass.getuser(), "ttHAnalysis", era, version),
      outputDir = os.path.join("/hdfs/local", getpass.getuser(), "ttHAnalysis", era, version),
      executable_analyze                    = "analyze_3l_1tau",
      cfgFile_analyze                       = "analyze_3l_1tau_cfg.py",
      samples                               = samples,
      changeBranchNames                     = changeBranchNames,
      MEMbranch                             = MEMbranch,
      hadTau_selection                      = hadTau_selection,
      # CV: apply "fake" background estimation to leptons only and not to hadronic taus, as discussed on slide 10 of
      #     https://indico.cern.ch/event/597028/contributions/2413742/attachments/1391684/2120220/16.12.22_ttH_Htautau_-_Review_of_systematics.pdf
      applyFakeRateWeights                  = applyFakeRateWeights,
      chargeSumSelections                   = [ "OS" ] if "forBDTtraining" in mode else [ "OS", "SS" ],
      central_or_shifts                     = central_or_shift,
      max_files_per_job                     = max_files_per_job,
      era                                   = era,
      use_lumi                              = True,
      lumi                                  = lumi,
      debug                                 = False,
      running_method                        = "sbatch",
      num_parallel_jobs                     = 100, # KE: run up to 100 'hadd' jobs in parallel on batch system
      executable_addBackgrounds             = "addBackgrounds",
      # CV: use common executable for estimating jet->lepton and jet->tau_h fake background
      executable_addBackgroundJetToTauFakes = "addBackgroundLeptonFakes",
      histograms_to_fit                     = [
        "EventCounter",
        "numJets",
        "mvaDiscr_3l",
        "mTauTauVis",
        "mvaDiscr_3l_1tau",
      ],
      select_rle_output                     = True,
      select_root_output                    = False,
      verbose                               = idx_job_resubmission > 0,
      dry_run                               = args.dry_run,
    )

    if mode.find("forBDTtraining") != -1:
      analysis.set_BDT_training(hadTau_selection_relaxed, hadTauFakeRateWeight_inputFileName)

    job_statistics = analysis.create()
    for job_type, num_jobs in job_statistics.items():
      logging.info(" #jobs of type '%s' = %i" % (job_type, num_jobs))
    job_statistics_summary[idx_job_resubmission] = job_statistics

    if idx_job_resubmission == 0:
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
