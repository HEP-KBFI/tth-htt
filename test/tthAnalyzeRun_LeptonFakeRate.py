#!/usr/bin/env python

##---------IMPORTANT MESSAGE BEFORE RUNNING LEPTON FAKE RATE CODE ----------##
## PLEASE CHANGE THE TRIGGER LOGIC INSIDE THE TOP OF FILE:
## $CMSSW_BASE/src/tthAnalysis/NanoAOD/python/triggers.py
## DEPENDING ON THE TYPE OF LEPTON FAKE RATE YOU WANT BY FOLLOWING ONE OF THESE 
## 2 CASES BELOW:
## CASE-1: IF YOU WANT TO COMPUTE FAKE RATES FOR ttH/HH MULTI-LEPTON ANALYSES,
##         PLEASE UN-COMMENT (COMMENT) LINE-1 (LINE-2) OF THE ABOVE FILE 
## CASE-2: IF YOU WANT TO COMPUTE FAKE RATES FOR bbWW SINGLE LEPTON ANALYSIS,
##         PLEASE UN-COMMENT (COMMENT) LINE-2 (LINE-1) OF THE ABOVE FILE 
## (N.B: BY DEFAULT CASE-1 TRIGGER LOGIC IS IMPLEMENTED IN THE CODE)
##--------------------------------------------------------------------------##      

from tthAnalysis.HiggsToTauTau.configs.analyzeConfig_LeptonFakeRate import analyzeConfig_LeptonFakeRate
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no
from tthAnalysis.HiggsToTauTau.analysisSettings import systematics, get_lumi
from tthAnalysis.HiggsToTauTau.runConfig import tthAnalyzeParser, filter_samples
from tthAnalysis.HiggsToTauTau.common import logging, load_samples_aux as load_samples, load_samples_stitched

import os
import sys
import getpass

##------ Example commands for generating Lepton Fake Rate configs (w Full Systematics) --------## 
## For Run-2 Legacy ttH Multi-Lepton Analysis [HIG-19-008] ##
## ./tthAnalyzeRun_LeptonFakeRate.py -m default -v 2021Jan10_wttHLeptonID_LFR_FullSyst_woMETSysts_2016 -e 2016 -s full -L default -L_useTightChargeCut False

## For Run-2 Legacy ttH Multi-Lepton Analysis [HIG-19-008] for 2lss channel (w Tight Charge cuts) ##
## ./tthAnalyzeRun_LeptonFakeRate.py -m default -v 2021Jan16_wttHLeptonID_LFR_FullSyst_woMETSysts_wTightChargeCut_2016 -e 2016 -s full -L default -L_useTightChargeCut True

## For Run-2 Legacy HH Multi-Lepton Analysis [HIG-21-002] ##
## ./tthAnalyzeRun_LeptonFakeRate.py -m default -v 2020Dec21_LFR_FullSyst_woMETSysts_2016 -e 2016 -s full -L hh_multilepton -L_useTightChargeCut False

## For Run-2 Legacy HH Multi-Lepton Analysis [HIG-21-002] for 2lss channel (w Tight Charge cuts) ##
## ./tthAnalyzeRun_LeptonFakeRate.py -m default -v 2021Jan18_wHHLeptonID_LFR_FullSyst_woMETSysts_wTightChargeCut_2016 -e 2016 -s full -L hh_multilepton -L_useTightChargeCut True 

## For Run-2 Legacy HH bbWW Single Lepton Analysis [HIG-XX-YYY] ##
## ./tthAnalyzeRun_LeptonFakeRate.py -m default -v 2021Feb3_wHHLeptonID_LFR_bbWWSL_FullSyst_woMETSysts_2016  -e 2016 -s full -L hh_multilepton -L_useTightChargeCut False -L_enable_LeptonFakeRate_bbwSL True 
##------------------------------------------------------------------------------------##      


cmssw_base_dir_combine = os.path.expanduser('~/CMSSW_10_2_13') # immediate parent dir to src folder
cmssw_base_dir_combine = os.path.expanduser('~/VHbbNtuples_10_x/CMSSW_10_2_13') if 'ssawant' in cmssw_base_dir_combine else cmssw_base_dir_combine
qcd_inclusive = True # set to True if you want to process inclusive muon-enriched sample

mode_choices     = [ 'default', 'sync' ]
sys_choices      = [ 'full' ] + systematics.an_leptonFR_opts
systematics.full = systematics.an_leptonFR

parser = tthAnalyzeParser()
parser.add_modes(mode_choices)
parser.add_sys(sys_choices)
parser.add_lep_mva_wp()
parser.add_lep_useTightChargeCut(default_option = 'False')
parser.enable_leptonFR_bbWW_SL_mode(default_option = 'False')
parser.add_files_per_job()
parser.add_use_home()
parser.add_jet_cleaning()
parser.add_gen_matching()
parser.add_stitched([ 'dy_lo', 'wjets' ])
args = parser.parse_args()

# Common arguments
era                = args.era
version            = args.version
dry_run            = args.dry_run
no_exec            = args.no_exec
auto_exec          = args.auto_exec
check_output_files = not args.not_check_input_files
debug              = args.debug
sample_filter      = args.filter
num_parallel_jobs  = args.num_parallel_jobs
running_method     = args.running_method

# Additional arguments
mode              = args.mode
systematics_label = args.systematics
lep_mva_wp        = args.lep_mva_wp
lep_useTightChargeCut       = args.lep_useTightChargeCut
enable_LeptonFakeRate_bbwSL = args.enable_LeptonFakeRate_bbwSL
files_per_job     = args.files_per_job
use_home          = args.use_home
jet_cleaning      = args.jet_cleaning
gen_matching      = args.gen_matching
use_stitched      = args.use_stitched

# Use the arguments
central_or_shifts = []
for systematic_label in systematics_label:
  for central_or_shift in getattr(systematics, systematic_label):
    if central_or_shift not in central_or_shifts:
      central_or_shifts.append(central_or_shift)
lumi = get_lumi(era)
jet_cleaning_by_index = (jet_cleaning == 'by_index')
gen_matching_by_index = (gen_matching == 'by_index')

if mode == 'default':
  samples = load_samples(era)
elif mode == 'sync':
  samples = load_samples(era, suffix = 'leptonFR_sync')
else:
  raise ValueError('Invalid mode: %s' % mode)

samples = load_samples_stitched(samples, era, use_stitched)
for sample_name, sample_info in samples.items():
  if sample_name == 'sum_events':
    continue
  if sample_info["type"] == "mc":
    sample_info["triggers"] = ([ "1e", "1mu", "2e", "2mu" ] if enable_LeptonFakeRate_bbwSL == 'False' else [ "1e", "1mu"])
  if sample_info["sample_category"] == "QCD": 
    sample_info["use_it"] = True
    if sample_info["process_name_specific"].endswith("_Mu5"):
      sample_info["use_it"] = qcd_inclusive
    elif sample_info["process_name_specific"] == "QCD_Mu15":
      sample_info["use_it"] = qcd_inclusive
  if enable_LeptonFakeRate_bbwSL == 'False': ## For TTH or HH Lepton Fake Rates    
    if sample_name.startswith(('/MuonEG/Run', '/Tau/Run')):
      sample_info["use_it"] = False
    if era == "2016":
        if sample_name.startswith('/SingleElectron'):
          # SingleElectron excluded since no 1e triggers used
          #TODO verify claim
          sample_info["use_it"] = False
    elif era == "2017":
          if sample_name.startswith(('/DoubleEG/Run', '/SingleElectron/Run2017B')):
            # DoubleEG excluded since no 2e triggers used
            # SingleElectron B run excluded since no useful triggers present in that dataset
            sample_info["use_it"] = False
  else:   ## For bbWW SL Lepton Fake Rates    
    ## Restricting ourselves to /SingleElectron (2016,2017), /EGamma (2018), /SingleMuon (2016,2017,2018)     
    if sample_name.startswith(('/MuonEG/Run', '/Tau/Run', '/DoubleMuon', '/DoubleEG')): 
      sample_info["use_it"] = False


if __name__ == '__main__':
  logging.info(
    "Running the jobs with the following systematic uncertainties enabled: %s" % \
    ', '.join(central_or_shifts)
  )

  if sample_filter:
    samples = filter_samples(samples, sample_filter)

  analysis = analyzeConfig_LeptonFakeRate(
    configDir = os.path.join("/home",       getpass.getuser(), "ttHAnalysis", era, version),
    outputDir = os.path.join("/hdfs/local", getpass.getuser(), "ttHAnalysis", era, version),
    cmssw_base_dir_combine                   = cmssw_base_dir_combine,
    executable_analyze                       = "analyze_LeptonFakeRate",
    samples                                  = samples,
    absEtaBins_e                             = [ 0., 1.479, 2.5 ],                     ## CERN binning scheme
    absEtaBins_mu                            = [ 0., 1.2, 2.4 ],                       ## CERN binning scheme
    ptBins_e                                 = ([ 15., 25., 35., 45., 65., 100. ] if enable_LeptonFakeRate_bbwSL == 'False' else [ 32., 45., 65., 100. ]),      ## CERN (Reduced) bins for ttH/HH (bbWW)
    ptBins_mu                                = ([ 10., 15., 20., 32., 45., 65., 100. ] if enable_LeptonFakeRate_bbwSL == 'False' else [ 25., 45., 65., 100. ]), ## CERN (Reduced) bins for ttH/HH (bbWW)
    lep_mva_wp                               = lep_mva_wp,
    lep_useTightChargeCut                    = lep_useTightChargeCut,
    enable_LeptonFakeRate_bbwSL              = enable_LeptonFakeRate_bbwSL,
    fillGenEvtHistograms                     = False,
    jet_cleaning_by_index                    = jet_cleaning_by_index,
    gen_matching_by_index                    = gen_matching_by_index,
    central_or_shifts                        = central_or_shifts,
    numerator_histogram                      = ("mT_fix_L_num",     "m_{T}^{fix,num}"), # or ("pt", "p_{T}"),
    denominator_histogram                    = ("mT_fix_L_den",     "m_{T}^{fix,den}"), # or ("EventCounter", "Number of events"),
    prep_dcard                               = True,
    enable_MC_Closure_sidebands              = True, # boolean handle to control inclusion of MC Closure sidebands: (TT Semi-Leptonic: 2lss, TT Hadronic)
    fillNtuple                               = False, # boolean handle to include Ntuples for optmizing Lepton I.D. cuts for MC Closure sidebands (TT Semi-Leptonic: 2lss, TTHadronic) 
    max_files_per_job                        = files_per_job,
    era                                      = era,
    use_lumi                                 = True,
    lumi                                     = lumi,
    check_output_files                       = check_output_files,
    running_method                           = running_method,
    executable_addBackgrounds                = "addBackgrounds",
    executable_addBackgrounds_recursively    = "addBackgrounds_recursively",
    executable_addBackgrounds_LeptonFakeRate = "addBackground_LeptonFakeRate",
    executable_prep_dcard                    = "prepareDatacards",
    executable_comp_LeptonFakeRate           = "comp_LeptonFakeRate",
    use_QCD_fromMC                           = False,
    num_parallel_jobs                        = num_parallel_jobs,
    select_rle_output                        = True,
    dry_run                                  = dry_run,
    isDebug                                  = debug,
    use_home                                 = use_home,
    submission_cmd                           = sys.argv,
  )

  job_statistics = analysis.create()
  for job_type, num_jobs in job_statistics.items():
    logging.info(" #jobs of type '%s' = %i" % (job_type, num_jobs))

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
