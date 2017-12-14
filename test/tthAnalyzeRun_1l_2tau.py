#!/usr/bin/env python
import os, logging, sys, getpass, argparse, datetime
from tthAnalysis.HiggsToTauTau.analyzeConfig_1l_2tau import analyzeConfig_1l_2tau
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no

#--------------------------------------------------------------------------------
# NOTE: set mode flag to
#   'VHbb'           : to run the analysis on the VHbb Ntuples, with the nominal event selection
#   'forBDTtraining' : to run the analysis on the VHbb Ntuples, with a relaxed event selection,
#                      to increase the BDT training statistics
#--------------------------------------------------------------------------------

# E.g.: ./tthAnalyzeRun_1l_2tau.py -v 2017Dec13 -mode VHbb -e 2017 --use-prod-ntuples

#TODO: needs actual Ntuples
#TODO: needs an updated value of integrated luminosity for 2017 data

mode_choices               = ['VHbb', 'forBDTtraining']
era_choices                = ['2017']
default_resubmission_limit = 4

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
parser.add_argument(
  '-p', '--use-production-ntuples',
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

samples                            = None
lumi                               = None
hadTau_selection                   = None
hadTau_selection_relaxed           = None
changeBranchNames                  = use_prod_ntuples
applyFakeRateWeights               = None
hadTauFakeRateWeight_inputFileName = "tthAnalysis/HiggsToTauTau/data/FR_tau_2016.root" #TODO update

if mode != "VHbb":
  raise ValueError("Only VHbb mode available")

if mode == "VHbb":
  if use_prod_ntuples:
    from tthAnalysis.HiggsToTauTau.tthAnalyzeSamples_prodNtuples_2017_test import samples_2017
  else:
    from tthAnalysis.HiggsToTauTau.tthAnalyzeSamples_2017_test import samples_2017

  for sample_name, sample_info in samples_2017.items():
    if sample_info["type"] == "mc":
      sample_info["triggers"] = ["1e", "1mu"]
    if sample_name in [
        #TODO list of samples collected with tau, 2e, 2mu and e-mu cross-triggers
      ]:
      sample_info["use_it"] = False

  hadTau_selection         = "dR03mvaVTight"
  applyFakeRateWeights     = "3L"
elif mode == "forBDTtraining":
#  if use_prod_ntuples:
#    from tthAnalysis.HiggsToTauTau.tthAnalyzeSamples_prodNtuples_2017_FastSim import samples_2017
#  else:
#    from tthAnalysis.HiggsToTauTau.tthAnalyzeSamples_2017_FastSim import samples_2017
  hadTau_selection                   = "dR03mvaVTight"
  hadTau_selection_relaxed           = "dR03mvaLoose"
  applyFakeRateWeights               = "3L"
else:
  raise ValueError("Invalid Configuration parameter 'mode' = %s !!" % mode)

if era == "2017":
  samples = samples_2017
  lumi    = 35.9e+3 # 1/pb
  # TODO: update lumi
else:
  raise ValueError("Invalid Configuration parameter 'era' = %s !!" % era)

if __name__ == '__main__':
  logging.basicConfig(
    stream = sys.stdout,
    level  = logging.INFO,
    format = '%(asctime)s - %(levelname)s: %(message)s'
  )

  job_statistics_summary = {}
  run_analysis           = False
  is_last_resubmission   = False

  for idx_job_resubmission in range(max_job_resubmission):
    if is_last_resubmission:
      continue
    logging.info("Job submission #%i:" % (idx_job_resubmission + 1))

    analysis = analyzeConfig_1l_2tau(
      configDir          = os.path.join("/home",       getpass.getuser(), "ttHAnalysis", era, version),
      outputDir          = os.path.join("/hdfs/local", getpass.getuser(), "ttHAnalysis", era, version),
      executable_analyze       = "analyze_1l_2tau",
      cfgFile_analyze          = "analyze_1l_2tau_cfg.py",
      samples                  = samples,
      changeBranchNames        = changeBranchNames,
      hadTau_selection         = hadTau_selection,
      hadTau_charge_selections =  [ "OS"] if mode == "forBDTtraining" else [ "OS", "SS" ], #
      applyFakeRateWeights     = applyFakeRateWeights,
      central_or_shifts = [
        "central",
##        "CMS_ttHl_btag_HFUp",
##        "CMS_ttHl_btag_HFDown",
##        "CMS_ttHl_btag_HFStats1Up",
##        "CMS_ttHl_btag_HFStats1Down",
##        "CMS_ttHl_btag_HFStats2Up",
##        "CMS_ttHl_btag_HFStats2Down",
##        "CMS_ttHl_btag_LFUp",
##        "CMS_ttHl_btag_LFDown",
##        "CMS_ttHl_btag_LFStats1Up",
##        "CMS_ttHl_btag_LFStats1Down",
##        "CMS_ttHl_btag_LFStats2Up",
##        "CMS_ttHl_btag_LFStats2Down",
##        "CMS_ttHl_btag_cErr1Up",
##        "CMS_ttHl_btag_cErr1Down",
##        "CMS_ttHl_btag_cErr2Up",
##        "CMS_ttHl_btag_cErr2Down",
##        "CMS_ttHl_JESUp",
##        "CMS_ttHl_JESDown",
##        "CMS_ttHl_tauESUp",
##        "CMS_ttHl_tauESDown",
##        "CMS_ttHl_FRjt_normUp",
##        "CMS_ttHl_FRjt_normDown",
##        "CMS_ttHl_FRjt_shapeUp",
##        "CMS_ttHl_FRjt_shapeDown",
##        "CMS_ttHl_FRet_shiftUp",
##        "CMS_ttHl_FRet_shiftDown",
##        "CMS_ttHl_FRmt_shiftUp",
##        "CMS_ttHl_FRmt_shiftDown",
##        "CMS_ttHl_thu_shape_ttH_x1Up",
##        "CMS_ttHl_thu_shape_ttH_x1Down",
##        "CMS_ttHl_thu_shape_ttH_y1Up",
##        "CMS_ttHl_thu_shape_ttH_y1Down",
##        "CMS_ttHl_thu_shape_ttW_x1Up",
##        "CMS_ttHl_thu_shape_ttW_x1Down",
##        "CMS_ttHl_thu_shape_ttW_y1Up",
##        "CMS_ttHl_thu_shape_ttW_y1Down",
##        "CMS_ttHl_thu_shape_ttZ_x1Up",
##        "CMS_ttHl_thu_shape_ttZ_x1Down",
##        "CMS_ttHl_thu_shape_ttZ_y1Up",
##        "CMS_ttHl_thu_shape_ttZ_y1Down",
      ],
      max_files_per_job                     = max_files_per_job,
      era                                   = era,
      use_lumi                              = True,
      lumi                                  = lumi,
      debug                                 = False,
      running_method                        = "sbatch",
      num_parallel_jobs                     = 100,
      executable_addBackgrounds             = "addBackgrounds",
      executable_addBackgroundJetToTauFakes = "addBackgroundLeptonFakes", # CV: use common executable for estimating jet->lepton and jet->tau_h fake background
      histograms_to_fit                     = [
        "EventCounter",
        "numJets",
        "mvaOutput_1l_2tau_ttbar_HTTWithKinFit_MVAonly",
        "mvaOutput_1l_2tau_ttbar_HTTWithKinFit",
        "mvaOutput_1l_2tau_ttbar",
        "mvaOutput_1l_2tau_ttbar_Old",
        "mvaOutput_1l_2tau_ttbar_OldVar",
        "mvaOutput_1l_2tau_ttbar_OldVarHTT",
        "mvaOutput_1l_2tau_ttbar_HTTLepID",
#       "mvaOutput_1l_2tau_ttbar_withLepID",
#       "mvaOutput_1l_2tau_ttbar_withLepID_HTTbase",
#       "mvaOutput_1l_2tau_ttbar_baseline",
#       "mvaOutput_1l_2tau_ttbar_baseline_HTTbase",
#       "mvaDiscr_1l_2tau",
        "mTauTauVis"
      ],
      select_rle_output                     = True,
      verbose                               = idx_job_resubmission > 0,
      dry_run                               = args.dry_run,
    )

    if mode == "forBDTtraining" :
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
