from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2018 import samples_2018

bdt_samples = [
  "ttHToNonbb_M125_powheg",
  "THQ_ctcvcp",
  #"THW_ctcvcp",
  "TTZJets_LO_ext1",
  "TTWJets_LO_ext1",
  "TTJets_DiLept",
  "TTJets_SingleLeptFromT",
  "TTJets_SingleLeptFromTbar",
]

for sample_name, sample_info in samples_2018.items():
  if sample_name == 'sum_events': continue
  sample_info["use_it"] = sample_info["process_name_specific"] in bdt_samples
