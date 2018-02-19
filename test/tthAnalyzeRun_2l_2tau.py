#!/usr/bin/env python
import os, logging, sys, getpass

from tthAnalysis.HiggsToTauTau.analyzeConfig_2l_2tau import analyzeConfig_2l_2tau
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no

#--------------------------------------------------------------------------------
# NOTE: set mode flag to
#   'VHbb'           : to run the analysis on the VHbb Ntuples, with the nominal event selection
#   'forBDTtraining' : to run the analysis on the Fastsim Ntuples, with a relaxed event selection,
#                      to increase the BDT training statistics
#   'forBDTtraining_VHbb' : to run the analysis on the VHbb Ntuples, with a relaxed event selection,
#                      to increase the BDT training statistics
#--------------------------------------------------------------------------------
# E.g. to run: python tthAnalyzeRun_2l_2tau.py --version "2l_2tau_2018Feb07_BDT_LLepVLTau" --mode "forBDTtraining" --use_prod_ntuples
from optparse import OptionParser
parser = OptionParser()
parser.add_option("--version ", type="string", dest="version", help="Name of output reository with results\n Trees will be stored in /hdfs/local/USER/ttHAnalysis/2016/VERSION/", default='dumb')
parser.add_option("--mode", type="string", dest="mode", help="Set the mode flag, read the script for options", default="VHbb")
parser.add_option("--ERA", type="string", dest="ERA", help="Era of data", default='2016')
parser.add_option("--use_prod_ntuples", action="store_true", dest="use_prod_ntuples", help="Production flag", default=False)
(options, args) = parser.parse_args()

use_prod_ntuples     = options.use_prod_ntuples #True
mode                 = options.mode #"VHbb"
ERA                  = options.ERA #"2016"
version              = options.version #"2017Oct24"
changeBranchNames    = use_prod_ntuples
max_job_resubmission = 3
max_files_per_job    = 10 if use_prod_ntuples else 100

samples                            = None
LUMI                               = None
hadTau_selection                   = None
hadTau_selection_relaxed           = None
applyFakeRateWeights               = None
hadTauFakeRateWeight_inputFileName = "tthAnalysis/HiggsToTauTau/data/FR_tau_2016.root" #

if use_prod_ntuples and ERA == "2015":
  raise ValueError("No production Ntuples for 2015 data & MC")

if mode.find("forBDTtraining") != -1 and ERA == "2015":
  raise ValueError("No fastsim samples for 2015")

if mode == "VHbb":
  if use_prod_ntuples:
    from tthAnalysis.HiggsToTauTau.tthAnalyzeSamples_prodNtuples_2016 import samples_2016
  else:
    from tthAnalysis.HiggsToTauTau.tthAnalyzeSamples_2015 import samples_2015
    from tthAnalysis.HiggsToTauTau.tthAnalyzeSamples_2016 import samples_2016
  hadTau_selection     =  "dR03mvaVTight" # "dR03mvaVVLoose" #  "dR03mvaMedium" #
  applyFakeRateWeights = "4L"
elif mode.find("forBDTtraining") != -1 :
  if mode == "forBDTtraining" :
      if use_prod_ntuples:
        from tthAnalysis.HiggsToTauTau.tthAnalyzeSamples_prodNtuples_2016_FastSim import samples_2016
      else:
        from tthAnalysis.HiggsToTauTau.tthAnalyzeSamples_2016_FastSim import samples_2016
  if mode == "forBDTtraining_VHbb" : from tthAnalysis.HiggsToTauTau.tthAnalyzeSamples_prodNtuples_2016 import samples_2016
  hadTau_selection         = "dR03mvaVTight"
  hadTau_selection_relaxed = "dR03mvaVVLoose"
  # "dR03mvaMedium" # "dR03mvaTight" # "dR03mvaVTight" # "dR03mvaLoose" #
  if hadTau_selection_relaxed=="dR03mvaVVLoose" : hadTauFakeRateWeight_inputFileName = "tthAnalysis/HiggsToTauTau/data/FR_tau_2016_vvLoosePresel.root"
  elif hadTau_selection_relaxed=="dR03mvaVLoose" : hadTauFakeRateWeight_inputFileName = "tthAnalysis/HiggsToTauTau/data/FR_tau_2016_vLoosePresel.root"
  else : hadTauFakeRateWeight_inputFileName = "tthAnalysis/HiggsToTauTau/data/FR_tau_2016.root"
  applyFakeRateWeights     = "4L"
else:
  raise ValueError("Invalid Configuration parameter 'mode' = %s !!" % mode)

if ERA == "2015":
  samples = samples_2015
  LUMI    = 2.3e+3 # 1/pb
elif ERA == "2016":
  samples = samples_2016
  LUMI    = 35.9e+3 # 1/pb
else:
  raise ValueError("Invalid Configuration parameter 'ERA' = %s !!" % ERA)

if __name__ == '__main__':
  logging.basicConfig(
    stream = sys.stdout,
    level  = logging.INFO,
    format = '%(asctime)s - %(levelname)s: %(message)s',
  )

  job_statistics_summary = {}
  run_analysis           = False
  is_last_resubmission   = False

  for idx_job_resubmission in range(max_job_resubmission):
    if is_last_resubmission:
      continue
    logging.info("Job submission #%i:" % (idx_job_resubmission + 1))

    analysis = analyzeConfig_2l_2tau(
      configDir          = os.path.join("/home",       getpass.getuser(), "ttHAnalysis", ERA, version),
      outputDir          = os.path.join("/hdfs/local", getpass.getuser(), "ttHAnalysis", ERA, version),
      executable_analyze       = "analyze_2l_2tau",
      cfgFile_analyze          = "analyze_2l_2tau_cfg.py",
      samples                  = samples,
      changeBranchNames        = changeBranchNames,
      lepton_charge_selections = [ "disabled" ],
      hadTau_selection         = hadTau_selection,
      hadTau_charge_selections = [ "disabled" ],
      applyFakeRateWeights     = applyFakeRateWeights,
      chargeSumSelections      = [ "OS"] if mode.find("forBDTtraining") != -1 else [ "OS", "SS" ],  #[ "OS", "SS" ],
      central_or_shifts        = [
        "central",
##         "CMS_ttHl_btag_HFUp",
##         "CMS_ttHl_btag_HFDown",
##         "CMS_ttHl_btag_HFStats1Up",
##         "CMS_ttHl_btag_HFStats1Down",
##         "CMS_ttHl_btag_HFStats2Up",
##         "CMS_ttHl_btag_HFStats2Down",
##         "CMS_ttHl_btag_LFUp",
##         "CMS_ttHl_btag_LFDown",
##         "CMS_ttHl_btag_LFStats1Up",
##         "CMS_ttHl_btag_LFStats1Down",
##         "CMS_ttHl_btag_LFStats2Up",
##         "CMS_ttHl_btag_LFStats2Down",
##         "CMS_ttHl_btag_cErr1Up",
##         "CMS_ttHl_btag_cErr1Down",
##         "CMS_ttHl_btag_cErr2Up",
##         "CMS_ttHl_btag_cErr2Down",
##         "CMS_ttHl_JESUp",
##         "CMS_ttHl_JESDown",
##         "CMS_ttHl_tauESUp",
##         "CMS_ttHl_tauESDown",
##         "CMS_ttHl_FRjt_normUp",
##         "CMS_ttHl_FRjt_normDown",
##         "CMS_ttHl_FRjt_shapeUp",
##         "CMS_ttHl_FRjt_shapeDown",
##         "CMS_ttHl_FRet_shiftUp",
##         "CMS_ttHl_FRet_shiftDown",
##         "CMS_ttHl_FRmt_shiftUp",
##         "CMS_ttHl_FRmt_shiftDown",
##         "CMS_ttHl_thu_shape_ttH_x1Up",
##         "CMS_ttHl_thu_shape_ttH_x1Down",
##         "CMS_ttHl_thu_shape_ttH_y1Up",
##         "CMS_ttHl_thu_shape_ttH_y1Down",
##         "CMS_ttHl_thu_shape_ttW_x1Up",
##         "CMS_ttHl_thu_shape_ttW_x1Down",
##         "CMS_ttHl_thu_shape_ttW_y1Up",
##         "CMS_ttHl_thu_shape_ttW_y1Down",
##         "CMS_ttHl_thu_shape_ttZ_x1Up",
##         "CMS_ttHl_thu_shape_ttZ_x1Down",
##         "CMS_ttHl_thu_shape_ttZ_y1Up",
##         "CMS_ttHl_thu_shape_ttZ_y1Down",
      ],
      max_files_per_job                     = max_files_per_job,
      era                                   = ERA,
      use_lumi                              = True,
      lumi                                  = LUMI,
      debug                                 = False,
      running_method                        = "sbatch",
      num_parallel_jobs                     = 100, # KE: run up to 100 'hadd' jobs in parallel on batch system
      executable_addBackgrounds             = "addBackgrounds",
      executable_addBackgroundJetToTauFakes = "addBackgroundLeptonFakes", # CV: use common executable for estimating jet->lepton and jet->tau_h fake background
      histograms_to_fit                     = [
        "EventCounter",
        "numJets",
        "mTauTauVis",
        "mvaDiscr_2l_2tau"
      ],
      select_rle_output                     = True,
      verbose                               = idx_job_resubmission > 0,
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
