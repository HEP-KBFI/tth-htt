from tthAnalyzeSamples_2017 import samples_2017

for sample_name, sample_info in samples_2017.items():
  if sample_info["type"] == "mc":
    sample_info["triggers"] = [ "1e", "1mu", "1e1mu" ]
  if sample_name.startswith(("/DoubleMuon/", "/DoubleEG/", "/Tau/")) and sample_name.find("PromptReco-v3") == -1:
    #TODO: taken from 2016 samples config, needs a review
    sample_info["use_it"] = False