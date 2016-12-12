from collections import OrderedDict as OD

from tthAnalyzeSamples_2016 import samples_2016

#----------------------------------------
# ONLY FOR TESTING !!!
## samples_2016 = OD()

## samples_2016["/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
##   ("type",                  "mc"),
##   ("sample_category",       "EWK"),
##   ("process_name_specific", "DYJetsToLL_M-10to50"),
##   ("nof_files",             369),
##   ("nof_events",            30915886),
##   ("use_it",                True),
##   ("xsection",              18610.000000),
##   ("genWeight",             True),  
##   ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
##   ("reHLT",                 False),
##   ("local_paths",
##     [
##       OD([
##         ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/VHBB_HEPPY_V24bis_DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/160911_223234"),
##         ("selection", "*"),
##         ("blacklist", []),
##       ]),
##     ]
##   ),
## ])
# FOR TESTING ONLY !!!
#----------------------------------------

for sample_name, sample_info in samples_2016.items():
  if sample_name in [
      "/Tau/Run2016B-PromptReco-v2/MINIAOD",
      "/Tau/Run2016C-PromptReco-v2/MINIAOD",
      "/Tau/Run2016D-PromptReco-v2/MINIAOD",
      "/Tau/Run2016E-PromptReco-v2/MINIAOD",
      "/Tau/Run2016F-PromptReco-v1/MINIAOD",
      "/Tau/Run2016G-PromptReco-v1/MINIAOD" ]:
    sample_info["use_it"] = False
