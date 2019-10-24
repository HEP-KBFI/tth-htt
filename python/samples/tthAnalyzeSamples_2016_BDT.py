from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2016 import samples_2016

bdt_samples = [
  "ttHToNonbb_M125_powheg",
  #"THQ",
  "THQ_ctcvcp",
  #"THW",
  #"THW_ctcvcp",
  "TTZJets_LO",
  "TTWJets_LO",
  "TTTo2L2Nu",
  "TTToSemiLeptonic",
  "TTToHadronic",
]

for sample_name, sample_info in samples_2016.items():
  if sample_name == 'sum_events': continue
  sample_info["use_it"] = sample_info["process_name_specific"] in bdt_samples
