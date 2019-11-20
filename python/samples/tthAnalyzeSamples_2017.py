from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017_base import samples_2017 as samples_2017_base
from hhAnalysis.multilepton.samples.hhAnalyzeSamples_2017_hh import samples_2017 as samples_2017_hh_multilepton
from hhAnalysis.bbww.samples.hhAnalyzeSamples_2017_hh import samples_2017 as samples_2017_hh_bbww

from tthAnalysis.HiggsToTauTau.samples.reclassifySamples import reclassifySamples
samples_2017     = reclassifySamples(samples_2017_base, samples_2017_hh_multilepton, samples_2017_hh_bbww)
samples_2017_aux = reclassifySamples(samples_2017_base, samples_2017_hh_multilepton, samples_2017_hh_bbww, analysis_type = 'aux')
