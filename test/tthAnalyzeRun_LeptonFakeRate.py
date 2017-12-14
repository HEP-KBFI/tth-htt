#!/usr/bin/env python
import os, logging, sys, getpass

from tthAnalysis.HiggsToTauTau.tthAnalyzeSamples_jetToTauFakeRate_2016 import samples_2016
from tthAnalysis.HiggsToTauTau.configs.analyzeConfig_LeptonFakeRate import analyzeConfig_LeptonFakeRate
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no

ERA                    = "2016"
version                = "2017Dec05"
cmssw_base_dir_combine = os.path.expanduser('~/CMSSW_7_4_7') # immediate parent dir to src folder

if ERA == "2016":
  samples = samples_2016
  LUMI = 35.9e+3 # 1/pb
else:
  raise ValueError("Invalid Configuration parameter 'ERA' = %s !!" % ERA)

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
    absEtaBins_mu          = [ 0., 1.479, 9.9 ],
    absPtBins_e            = [ 15., 20., 30., 45., 65., 100000. ],
    absPtBins_mu           = [ 10., 15., 20., 30., 45., 65., 100000. ],
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
    numerator_histogram                      = ("mT_fix_L",     "m_{T}^{fix}"), # or ("pt", "p_{T}"),
    denominator_histogram                    = ("EventCounter", "Number of events"),
    prep_dcard                               = True,
    max_files_per_job                        = 100,
    era                                      = ERA,
    use_lumi                                 = True,
    lumi                                     = LUMI,
    debug                                    = False,
    running_method                           = "sbatch",
    executable_addBackgrounds_LeptonFakeRate = "addBackground_LeptonFakeRate",
    executable_prep_dcard                    = "prepareDatacards",
    executable_comp_LeptonFakeRate           = "comp_LeptonFakeRate",
    num_parallel_jobs                        = 8,
  )

  analysis.create()

  run_analysis = query_yes_no("Start jobs ?")
  if run_analysis:
    analysis.run()
  else:
    sys.exit(0)
