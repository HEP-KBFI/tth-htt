from hhAnalysis.multilepton.common import is_nonresonant

import collections
import itertools
import copy

def reclassifySamples(samples_era_base, samples_era_hh_multilepton, samples_era_hh_bbww):
  sum_events_base = copy.deepcopy(samples_era_base['sum_events'])
  sum_events_hh_multilepton = copy.deepcopy(samples_era_hh_multilepton['sum_events'])
  sum_events_hh_bbww = copy.deepcopy(samples_era_hh_bbww['sum_events'])

  del samples_era_base['sum_events']
  del samples_era_hh_multilepton['sum_events']
  del samples_era_hh_bbww['sum_events']

  samples = collections.OrderedDict(itertools.chain(
    samples_era_base.items(), samples_era_hh_multilepton.items(), samples_era_hh_bbww.items()
  ))

  samples['sum_events'] = sum_events_base + sum_events_hh_multilepton + sum_events_hh_bbww

  from collections import OrderedDict as OD
  for sample_name, sample_info in samples.items():

    if not isinstance(sample_info, OD):
      continue

    if 'CountWeightedLHEWeightScale' in sample_info["nof_events"] and \
        sample_info["nof_events"]['CountWeightedLHEWeightScale'] == [ 0 ]:
      sample_info["has_LHE"] = False

    if sample_info["process_name_specific"].startswith('signal') and 'hh' in sample_info["process_name_specific"]:
      if is_nonresonant(sample_info["sample_category"], require_sm = True):
        sample_info["use_it"] = True
        sample_info["sample_category"] = "HH"
        sample_info["xsection"] *= 0.03345 # HH processes are normalized to 1 pb -> change it to the SM XS
      else:
        sample_info["use_it"] = False

  return samples
