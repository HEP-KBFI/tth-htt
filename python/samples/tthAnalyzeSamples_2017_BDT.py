from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017 import samples_2017

for sample_name, sample_info in samples_2017.items():
  if sample_name == 'sum_events':
    continue
  if sample_info["process_name_specific"] in [
        "ttHToNonbb_M125_powheg",
        "TTZJets_LO",
        "TTZJets_LO_ext1",
        "TTWJets_LO",
        "TTWJets_LO_ext1",
        "TTTo2L2Nu",
        "TTTo2L2Nu_PSweights",
        "TTToSemiLeptonic",
        "TTToSemiLeptonic_PSweights",
        "TTToHadronic",
        "TTToHadronic_PSweights",
      ]:
    sample_info["use_it"] = True
  else:
    sample_info["use_it"] = False
