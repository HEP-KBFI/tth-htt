from tthAnalysis.HiggsToTauTau.tthAnalyzeSamples_2016_2lss1tau_addMEM_v3 import samples_2016

for sample_name, sample_info in samples_2016.items():
  if sample_info['process_name_specific'] in [
    'TTTo2L2Nu_fastsim_p1',
    'TTTo2L2Nu_fastsim_p2',
    'TTTo2L2Nu_fastsim_p3',
    'TTToSemilepton_fastsim_p1',
    'TTToSemilepton_fastsim_p2',
    'TTToSemilepton_fastsim_p3',
    'TTWJetsToLNu_fastsim',
    'TTZToLLNuNu_fastsim',
    'WZTo3LNu_fastsim',
    'ttHToNonbb_fastsim_p1',
    'ttHToNonbb_fastsim_p2',
    'ttHToNonbb_fastsim_p3',
  ]:
    sample_info["use_it"] = True
  else:
    sample_info["use_it"] = False
