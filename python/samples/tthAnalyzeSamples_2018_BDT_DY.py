from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2018 import samples_2018
from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2018_BDT import bdt_samples as bdt_samples_common
from tthAnalysis.HiggsToTauTau.samples.stitch import samples_to_stitch_2018
from tthAnalysis.HiggsToTauTau.analysisTools import split_stitched

dy_samples_inclusive, dy_samples_binned = split_stitched(samples_to_stitch_2018, 'DY')
bdt_samples = bdt_samples_common + dy_samples_inclusive + dy_samples_binned 

for sample_name, sample_info in samples_2018.items():
  if sample_name == 'sum_events': continue
  sample_info["use_it"] = sample_info["process_name_specific"] in bdt_samples
