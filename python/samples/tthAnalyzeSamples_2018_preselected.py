from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2018_preselected_base import samples_2018 as samples_2018_base
from hhAnalysis.bbww.samples.hhAnalyzeSamples_2018_hh import samples_2018 as samples_2018_hh_bbww

from tthAnalysis.HiggsToTauTau.samples.reclassifySamples import reclassifySamples
samples_2018     = reclassifySamples(samples_2018_base, None, samples_2018_hh_bbww)
samples_2018_aux = reclassifySamples(samples_2018_base, None, samples_2018_hh_bbww, analysis_type = 'aux')
