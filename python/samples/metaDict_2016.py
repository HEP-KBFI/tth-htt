from tthAnalysis.HiggsToTauTau.samples.metaDict_2016_data import meta_dictionary as meta_dictionary_data
from tthAnalysis.HiggsToTauTau.samples.metaDict_2016_mc import meta_dictionary as meta_dictionary_mc
from tthAnalysis.HiggsToTauTau.samples.metaDict_2016_mc import sum_events

import itertools, collections

meta_dictionary = collections.OrderedDict(itertools.chain(
  meta_dictionary_data.items(), meta_dictionary_mc.items()
))
