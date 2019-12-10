from hhAnalysis.multilepton.common import is_nonresonant

import collections
import itertools
import copy
import re

def reclassifySamples(samples_era_base, samples_era_hh_multilepton = None, samples_era_hh_bbww = None, analysis_type = 'default'):
  assert(analysis_type in [ 'default', 'aux' ])
  samples_era_base_copy = copy.deepcopy(samples_era_base)
  samples_era_hh_multilepton_copy = copy.deepcopy(samples_era_hh_multilepton) if samples_era_hh_multilepton else None
  samples_era_hh_bbww_copy = copy.deepcopy(samples_era_hh_bbww) if samples_era_hh_bbww else None

  sum_events_base = copy.deepcopy(samples_era_base_copy['sum_events'])
  sum_events_hh_multilepton = copy.deepcopy(samples_era_hh_multilepton_copy['sum_events']) if samples_era_hh_multilepton_copy else []
  sum_events_hh_bbww = copy.deepcopy(samples_era_hh_bbww_copy['sum_events']) if samples_era_hh_bbww_copy else []

  del samples_era_base_copy['sum_events']
  if samples_era_hh_multilepton_copy:
    del samples_era_hh_multilepton_copy['sum_events']
  if samples_era_hh_bbww_copy:
    del samples_era_hh_bbww_copy['sum_events']

  samples = collections.OrderedDict(itertools.chain(
    samples_era_base_copy.items(),
    samples_era_hh_multilepton_copy.items() if samples_era_hh_multilepton_copy else [],
    samples_era_hh_bbww_copy.items() if samples_era_hh_bbww_copy else [],
  ))

  samples['sum_events'] = sum_events_base + sum_events_hh_multilepton + sum_events_hh_bbww

  from collections import OrderedDict as OD
  for sample_name, sample_info in samples.items():

    if not isinstance(sample_info, OD):
      continue

    if 'CountWeightedLHEWeightScale' in sample_info["nof_events"] and \
        sample_info["nof_events"]['CountWeightedLHEWeightScale'] == [ 0 ]:
      sample_info["has_LHE"] = False

    if analysis_type == 'default':
      # see https://github.com/HEP-KBFI/tth-htt/issues/91
      # https://gitlab.cern.ch/ttH_leptons/doc/blob/53e8220a045118cdecd03c85a677736417e0ea74/Legacy/datacards_and_systematics.md#12-bkg-collective-names
      if re.match("/DY(\d)?Jets", sample_name):
        sample_info["sample_category"] = "ZZ"
      elif re.match("/W(\d)?Jets", sample_name):
        sample_info["sample_category"] = "WZ"
      elif sample_name.startswith(("/TTTo", "/TTJets")):
        sample_info["sample_category"] = "TTZ"
      elif sample_name.startswith("/ST_"):
        sample_info["sample_category"] = "Rares"

    if sample_info["process_name_specific"].startswith('signal') and 'hh' in sample_info["process_name_specific"]:
      if is_nonresonant(sample_info["sample_category"]):
        sample_info["use_it"] = True
        sample_info["sample_category_hh"] = sample_info["sample_category"]
        sample_info["sample_category"] = "HH"
        # SM XS taken from: https://twiki.cern.ch/twiki/bin/view/LHCPhysics/LHCHXSWGHH?rev=48#Current_recommendations_for_HH_c
        sample_info["xsection"] *= 31.05 / 1000. # HH processes are normalized to 1 pb -> change it to the SM XS
        sample_info["use_it"] = analysis_type == "default"
      else:
        # remove the HH sample for safety reasons
        del samples[sample_name]

    # disable Tau PD by default -- to avoid double-counting the data events in all analysis channels but 0l+2tau
    # where the PD is the only one enabled
    if sample_name.startswith('/Tau/'):
      sample_info["use_it"] = False

  return samples
