import os, logging, sys, getpass

from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_WZctrl_2015 import samples_2015
from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_WZctrl_2016 import samples_2016
from tthAnalysis.HiggsToTauTau.configs.analyzeConfig_WZctrl import analyzeConfig_WZctrl
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no

#ERA = "2015"
ERA = "2016"

samples = None
LUMI = None
if ERA == "2015":
  samples = samples_2015
  LUMI =  2.3e+3 # 1/pb
elif ERA == "2016":
  samples = samples_2016
  LUMI = 35.9e+3 # 1/pb
else:
  raise ValueError("Invalid Configuration parameter 'ERA' = %s !!" % ERA)

version = "2017Feb27"

if __name__ == '__main__':
  logging.basicConfig(
    stream = sys.stdout,
    level = logging.INFO,
    format = '%(asctime)s - %(levelname)s: %(message)s')

  analysis = analyzeConfig_WZctrl(
    configDir = os.path.join("/home", getpass.getuser(), "ttHAnalysis", ERA, version),
    ##outputDir = os.path.join("/hdfs/local/ttH_2tau", getpass.getuser(), "ttHAnalysis", ERA, version),
    outputDir = os.path.join("/home", getpass.getuser(), "ttHAnalysis", ERA, version),
    executable_analyze = "analyze_WZctrl", cfgFile_analyze = "analyze_WZctrl_cfg.py",
    samples = samples,
    hadTau_selection = "dR03mvaLoose",
    central_or_shifts = [
      "central",
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
##       "CMS_ttHl_thu_shape_ttZ_y1Down"
    ],
    max_files_per_job = 100,
    era = ERA, use_lumi = True, lumi = LUMI,
    debug = False,
    running_method = "sbatch",
    num_parallel_jobs = 8,
    histograms_to_fit = [ "EventCounter", "numJets", "mLL", "mT" ],
    select_rle_output = True)

  analysis.create()

  run_analysis = query_yes_no("Start jobs ?")
  if run_analysis:
    analysis.run()
  else:
    sys.exit(0)

