from collections import OrderedDict as OD

from tthAnalyzeSamples_2016 import samples_2016

for sample_name, sample_info in samples_2016.items():
  if sample_name in [
      "/Tau/Run2016B-23Sep2016-v3/MINIAOD",
      "/Tau/Run2016C-23Sep2016-v1/MINIAOD",
      "/Tau/Run2016D-23Sep2016-v1/MINIAOD",
      "/Tau/Run2016E-23Sep2016-v1/MINIAOD",
      "/Tau/Run2016F-23Sep2016-v1/MINIAOD",
      "/Tau/Run2016G-23Sep2016-v1/MINIAOD",
      "/Tau/Run2016H-PromptReco-v2/MINIAOD",
      "/Tau/Run2016H-PromptReco-v3/MINIAOD" ]:
    sample_info["use_it"] = False
