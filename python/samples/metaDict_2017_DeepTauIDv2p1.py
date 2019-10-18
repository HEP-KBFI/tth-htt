from tthAnalysis.HiggsToTauTau.samples.metaDict_2017_data_DeepTauIDv2p1 import meta_dictionary as meta_dictionary_data
from tthAnalysis.HiggsToTauTau.samples.metaDict_2017_mc_DeepTauIDv2p1 import meta_dictionary as meta_dictionary_mc
from tthAnalysis.HiggsToTauTau.samples.metaDict_2017_mc_DeepTauIDv2p1 import sum_events

import itertools, collections

meta_dictionary = collections.OrderedDict(itertools.chain(
  meta_dictionary_data.items(), meta_dictionary_mc.items()
))
