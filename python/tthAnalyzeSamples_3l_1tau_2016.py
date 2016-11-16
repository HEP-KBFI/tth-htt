from collections import OrderedDict as OD

from tthAnalyzeSamples_2016 import samples_2016

for sample_name, sample_info in samples_2016.items():
  if sample_name in [
      "/Tau/Run2016B-PromptReco-v2/MINIAOD",
      "/Tau/Run2016C-PromptReco-v2/MINIAOD",
      "/Tau/Run2016D-PromptReco-v2/MINIAOD",
      "/Tau/Run2016E-PromptReco-v2/MINIAOD",
      "/Tau/Run2016F-PromptReco-v1/MINIAOD",
      "/Tau/Run2016G-PromptReco-v1/MINIAOD" ]:
    sample_info["use_it"] = False
