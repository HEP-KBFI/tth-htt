#!/usr/bin/env python
import os, logging, sys, getpass

from tthAnalysis.HiggsToTauTau.tthAnalyzeSamples_2016 import samples_2016
from tthAnalysis.HiggsToTauTau.analyzeConfig_LeptonFakeRate import analyzeConfig_LeptonFakeRate
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no

ERA                    = "2016"
version                = "2018Jan24_RED_BGS_ALL_CONE_PT_TIGHT_FAKE_EXCLUSIVE_LOGIC_CORR"
## cmssw_base_dir_combine = os.path.expanduser('~/CMSSW_7_4_7') # immediate parent dir to src folder
cmssw_base_dir_combine = os.path.expanduser('~/VHBB_NTUPLES_2017/CMSSW_7_4_7_CombineHarvestor') # immediate parent dir to src folder                                                                      
if ERA == "2016":
  samples = samples_2016
  for sample_name, sample_info in samples_2016.items():
    if sample_info["type"] == "mc":
      sample_info["triggers"] = [ "1e", "1mu", "2e", "2mu" ]
    if sample_name in [
      "/MuonEG/Run2016B-PromptReco-v2/MINIAOD",
      "/MuonEG/Run2016C-PromptReco-v2/MINIAOD",
      "/MuonEG/Run2016D-PromptReco-v2/MINIAOD",
      "/MuonEG/Run2016E-PromptReco-v2/MINIAOD",
      "/MuonEG/Run2016F-PromptReco-v1/MINIAOD",
      "/MuonEG/Run2016G-PromptReco-v1/MINIAOD",
      "/Tau/Run2016B-PromptReco-v2/MINIAOD",
      "/Tau/Run2016C-PromptReco-v2/MINIAOD",
      "/Tau/Run2016D-PromptReco-v2/MINIAOD",
      "/Tau/Run2016E-PromptReco-v2/MINIAOD",
      "/Tau/Run2016F-PromptReco-v1/MINIAOD",
      "/Tau/Run2016G-PromptReco-v1/MINIAOD" ]:
      sample_info["use_it"] = False
  LUMI = 35.9e+3 # 1/pb
else:
  raise ValueError("Invalid Configuration parameter 'ERA' = %s !!" % ERA)

### FOR DEBUGGING ONLY (W/O CHANGING PT AND ETA BINS) ###
#for sample_key, sample_value in samples.items():
#  sample_value["use_it"] = False
###########################

if __name__ == '__main__':
  logging.basicConfig(
    stream = sys.stdout,
    level = logging.INFO,
    format = '%(asctime)s - %(levelname)s: %(message)s')

  analysis = analyzeConfig_LeptonFakeRate(
    configDir = os.path.join("/home",       getpass.getuser(), "ttHAnalysis", ERA, version),
    outputDir = os.path.join("/hdfs/local", getpass.getuser(), "ttHAnalysis", ERA, version),
    cmssw_base_dir_combine = cmssw_base_dir_combine,
    executable_analyze     = "analyze_LeptonFakeRate",
    samples                = samples,
    absEtaBins_e           = [ 0., 1.479, 9.9 ],
    ptBins_e               = [ 15., 20., 30., 45., 65., 100000. ],
    absEtaBins_mu          = [ 0., 1.479, 9.9 ],
    ptBins_mu              = [ 10., 15., 20., 30., 45., 65., 100000. ],
    fillGenEvtHistograms   = False,
    central_or_shifts      = [
      "central",
      "CMS_ttHl_JESUp",
      "CMS_ttHl_JESDown",
      "CMS_ttHl_JERUp",
      "CMS_ttHl_JERDown",
      "CMS_ttHl_UnclusteredEnUp",
      "CMS_ttHl_UnclusteredEnDown",
##       "CMS_ttHl_btag_HFUp",
##       "CMS_ttHl_btag_HFDown",
##       "CMS_ttHl_btag_HFStats1Up",
##       "CMS_ttHl_btag_HFStats1Down",
##       "CMS_ttHl_btag_HFStats2Up",
##       "CMS_ttHl_btag_HFStats2Down",
##       "CMS_ttHl_btag_LFUp",
##       "CMS_ttHl_btag_LFDown",
##       "CMS_ttHl_btag_LFStats1Up",
##       "CMS_ttHl_btag_LFStats1Down",
##       "CMS_ttHl_btag_LFStats2Up",
##       "CMS_ttHl_btag_LFStats2Down",
##       "CMS_ttHl_btag_cErr1Up",
##       "CMS_ttHl_btag_cErr1Down",
##       "CMS_ttHl_btag_cErr2Up",
##       "CMS_ttHl_btag_cErr2Down",
##       "CMS_ttHl_JESUp",
##       "CMS_ttHl_JESDown",
##       "CMS_ttHl_tauESUp",
##       "CMS_ttHl_tauESDown",
##       "CMS_ttHl_FRet_shiftUp",
##       "CMS_ttHl_FRet_shiftDown",
##       "CMS_ttHl_FRmt_shiftUp",
##       "CMS_ttHl_FRmt_shiftDown",
##       "CMS_ttHl_thu_shape_ttH_x1Up",
##       "CMS_ttHl_thu_shape_ttH_x1Down",
##       "CMS_ttHl_thu_shape_ttH_y1Up",
##       "CMS_ttHl_thu_shape_ttH_y1Down",
##       "CMS_ttHl_thu_shape_ttW_x1Up",
##       "CMS_ttHl_thu_shape_ttW_x1Down",
##       "CMS_ttHl_thu_shape_ttW_y1Up",
##       "CMS_ttHl_thu_shape_ttW_y1Down",
##       "CMS_ttHl_thu_shape_ttZ_x1Up",
##       "CMS_ttHl_thu_shape_ttZ_x1Down",
##       "CMS_ttHl_thu_shape_ttZ_y1Up",
##       "CMS_ttHl_thu_shape_ttZ_y1Down",
    ],
    numerator_histogram                      = ("mT_fix_L", "m_{T}^{fix}"), # or ("pt", "p_{T}"),
    denominator_histogram                    = ("EventCounter", "Number of events"),
    prep_dcard                               = True,
    max_files_per_job                        = 100,
    era                                      = ERA,
    use_lumi                                 = True,
    lumi                                     = LUMI,
    debug                                    = False,    
    running_method                           = "sbatch",
    num_parallel_jobs                        = 100, # KE: run up to 100 'hadd' jobs in parallel on batch system
    executable_addBackgrounds                = "addBackgrounds",
    executable_addBackgrounds_recursively    = "addBackgrounds_recursively",
    executable_addBackgrounds_LeptonFakeRate = "addBackground_LeptonFakeRate",
    executable_prep_dcard                    = "prepareDatacards",
    executable_comp_LeptonFakeRate           = "comp_LeptonFakeRate",
  )

  analysis.create()

  run_analysis = query_yes_no("Start jobs ?")
  ## run_analysis = False
  if run_analysis:
    analysis.run()
  else:
    sys.exit(0)
