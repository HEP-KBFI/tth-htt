#!/usr/bin/env python

import argparse
import importlib
import collections
import itertools

from tthAnalysis.HiggsToTauTau.common import SmartFormatter, load_samples

METADICT = 'meta_dictionary'

parser = argparse.ArgumentParser(
  formatter_class = lambda prog: SmartFormatter(prog, max_help_position = 55)
)
parser.add_argument('-a', '--attribute',
  type = str, dest = 'attribute', metavar = 'id', required = False, choices = [ 'dbs', 'name' ], default = 'dbs',
  help = 'R|Attribute of the missing sample in the printout',
)
parser.add_argument('-e', '--era',
  type = str, dest = 'era', metavar = 'year', required = True, choices = list([ str(era) for era in range(2016, 2019) ]),
  help = 'R|Era',
)
parser.add_argument('-c', '--compare',
  type = str, dest = 'compare', metavar = 'stage', required = False, choices = [ 'pre', 'post', 'skimmed' ], default = 'post',
  help = 'R|Compare the status of samples to its previous stage',
)
args = parser.parse_args()

era = args.era
attr = args.attribute
comparison = args.compare

# load the meta dictionaries first
hh_suffix = "_hh" if era != "2017" else ""
module_tth = importlib.import_module("tthAnalysis.HiggsToTauTau.samples.metaDict_{}".format(era))
module_hh_multilepton = importlib.import_module("hhAnalysis.multilepton.samples.metaDict_{}{}".format(era, hh_suffix))
module_hh_bbww = importlib.import_module("hhAnalysis.bbww.samples.metaDict_{}_hh".format(era))
module_hh_bbww_ttbar = importlib.import_module("hhAnalysis.bbww.samples.metaDict_{}_ttbar".format(era))

metaDict_tth = getattr(module_tth, METADICT)
metaDict_hh_multilepton = getattr(module_hh_multilepton, METADICT)
metaDict_hh_bbww = getattr(module_hh_bbww, METADICT)
metaDict_hh_bbww_ttbar = getattr(module_hh_bbww_ttbar, METADICT)
metaDict = collections.OrderedDict(itertools.chain(
  metaDict_tth.items(), metaDict_hh_multilepton.items(), metaDict_hh_bbww.items(), metaDict_hh_bbww_ttbar.items()
))
dbs_names_metaDict = list(metaDict.keys())

samples_pre_processed = load_samples(era, False, 'all')
samples_post_processed = load_samples(era, True, 'all')

samples_tth_skimmed            = load_samples(era, True,                   suffix = 'preselected_base')
samples_hh_bbww_ttbar_skimmed  = load_samples(era, True, base = 'hh_bbww', suffix = 'ttbar_preselected')
del samples_tth_skimmed['sum_events']
del samples_hh_bbww_ttbar_skimmed['sum_events']
samples_skimmed = collections.OrderedDict(
  itertools.chain(samples_tth_skimmed.items(), samples_hh_bbww_ttbar_skimmed.items())
)

if comparison == 'pre':
  samples_before = metaDict
  samples_after = samples_pre_processed
elif comparison == 'post':
  samples_before = samples_pre_processed
  samples_after = samples_post_processed
elif comparison == 'skimmed':
  samples_before = samples_post_processed
  samples_after = samples_skimmed
else:
  raise RuntimeError("Invalid comparison choice: %s" % comparison)

missing_samples = list(sorted(set(samples_before.keys()) - set(samples_after.keys())))
for sample_name in missing_samples:
  print(sample_name if attr == 'dbs' else samples_before[sample_name]['process_name_specific'])


