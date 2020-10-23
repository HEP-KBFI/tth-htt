import sys
import logging
import collections
import itertools

DEPENDENCIES = [
  "",  # CMSSW_BASE/src
  "PhysicsTools/NanoAODTools",
  "tthAnalysis/NanoAODTools",
  "tthAnalysis/NanoAOD",
  "tthAnalysis/HiggsToTauTau",
  "tthAnalysis/tthMEM",
  "tthAnalysis/MEMmultilepton",
  "ttH_Htautau_MEM_Analysis",
  "TauPOG/TauIDSFs",
  "TauAnalysisTools/TauTriggerSFs",
  "TauAnalysis/ClassicSVfit4tau",
  "TauAnalysis/ClassicSVfit",
  "TauAnalysis/SVfitTF",
  "hhAnalysis/multilepton",
  "hhAnalysis/bbww",
  "hhAnalysis/bbwwMEM",
  "hhAnalysis/Heavymassestimator",
  "HHStatAnalysis",
  "Support",
  "TopAnalysis/KinematicReconstruction",
]

logging.basicConfig(
  stream = sys.stdout,
  level  = logging.INFO,
  format = '%(asctime)s - %(levelname)s: %(message)s',
)

import argparse
class SmartFormatter(argparse.ArgumentDefaultsHelpFormatter):
  def _split_lines(self, text, width):
    if text.startswith('R|'):
      return text[2:].splitlines()
    return argparse.ArgumentDefaultsHelpFormatter._split_lines(self, text, width)

import importlib
def load_samples(era, is_postproc = True, base = 'tth', suffix = '', analysis_type = 'default'):
  assert(analysis_type in [ 'default', 'aux' ])
  if base == 'tth':
    base_str = 'tthAnalysis.HiggsToTauTau'
    sample_prefix = 'tthAnalyzeSamples'
  elif base == 'hh_multilepton':
    base_str = 'hhAnalysis.multilepton'
    sample_prefix = 'hhAnalyzeSamples'
  elif base == 'hh_bbww':
    base_str = 'hhAnalysis.bbww'
    sample_prefix = 'hhAnalyzeSamples'
  elif base == 'all':
    if is_postproc:
      samples_tth            = load_samples(era, True,                          suffix = 'base')
      samples_hh_multilepton = load_samples(era, True, base = 'hh_multilepton', suffix = 'hh')
      samples_hh_bbww        = load_samples(era, True, base = 'hh_bbww',        suffix = 'hh')
      samples_hh_bbww_ttbar  = load_samples(era, True, base = 'hh_bbww',        suffix = 'ttbar')
    else:
      samples_tth            = load_samples(era, False)
      samples_hh_multilepton = load_samples(era, False, base = 'hh_multilepton')
      samples_hh_bbww        = load_samples(era, False, base = 'hh_bbww')
      samples_hh_bbww_ttbar  = load_samples(era, False, base = 'hh_bbww', suffix = 'ttbar')
    del samples_tth['sum_events']
    del samples_hh_multilepton['sum_events']
    del samples_hh_bbww['sum_events']
    del samples_hh_bbww_ttbar['sum_events']
    samples = collections.OrderedDict(itertools.chain(
      samples_tth.items(), samples_hh_multilepton.items(), samples_hh_bbww.items(), samples_hh_bbww_ttbar.items()
    ))
    return samples
  else:
    raise ValueError("Invalid base: %s" % base)
  assert(base_str and sample_prefix)
  assert(era in [ "2016", "2017", "2018" ])

  sample_name = 'samples_{}'.format(era)
  if analysis_type != 'default':
    sample_name = '{}_{}'.format(sample_name, analysis_type)
  sample_location = "{}.samples.{}_{}".format(base_str, sample_prefix, era)

  if not is_postproc:
    suffix_tmp = "nanoAOD"
    if suffix:
      suffix_tmp += "_{}".format(suffix)
    suffix = suffix_tmp

  if suffix:
    sample_location += "_{}".format(suffix)

  sample_module = importlib.import_module(sample_location)
  sample = getattr(sample_module, sample_name)

  return sample

def load_samples_aux(era, is_postproc = True, base = 'tth', suffix = ''):
  return load_samples(era, is_postproc, base, suffix, analysis_type = 'aux')

def load_samples_hh_multilepton(era, is_postproc = True, suffix = ''):
  return load_samples(era, is_postproc, "hh_multilepton", suffix)

def load_samples_hh_bbww(era, is_postproc = True, suffix = ''):
  return load_samples(era, is_postproc, "hh_bbww", suffix)

STITCHING_OPTIONS = [
  'dy_lowmll_lo',  'dy_lowmll_lo_incl',  'dy_lowmll_lo_noincl',
  'dy_lo',         'dy_lo_incl',         'dy_lo_noincl',
  'dy_nlo',        'dy_nlo_incl',        'dy_nlo_noincl',
  'wjets',         'wjets_incl',         'wjets_noincl',
]

def load_samples_stitched(samples, era, load = None):
  if not load:
    return samples
  assert(type(load) == list)
  assert(load_option in STITCHING_OPTIONS for load_option in load)

  load_wjets         = 'wjets'        in load or 'wjets_incl'        in load or 'wjets_noincl'        in load
  load_nlo_dy        = 'dy_nlo'       in load or 'dy_nlo_incl'       in load or 'dy_nlo_noincl'       in load
  load_lo_dy         = 'dy_lo'        in load or 'dy_lo_incl'        in load or 'dy_lo_noincl'        in load
  load_lowmll_lo_dy  = 'dy_lowmll_lo' in load or 'dy_lowmll_lo_incl' in load or 'dy_lowmll_lo_noincl' in load

  if load_wjets:
    if sum(load_option in [ 'wjets', 'wjets_incl', 'wjets_noincl' ] for load_option in load) > 1:
      raise ValueError("Conflicting options given: %s" % ', '.join(load))
  if load_nlo_dy:
    if sum(load_option in [ 'dy_nlo', 'dy_nlo_incl', 'dy_nlo_noincl' ] for load_option in load) > 1:
      raise ValueError("Conflicting options given: %s" % ', '.join(load))
  if load_lo_dy:
    if sum(load_option in [ 'dy_lo', 'dy_lo_incl', 'dy_lo_noincl' ] for load_option in load) > 1:
      raise ValueError("Conflicting options given: %s" % ', '.join(load))
  if load_lowmll_lo_dy:
    if sum(load_option in [ 'dy_lowmll_lo', 'dy_lowmll_lo_incl', 'dy_lowmll_lo_noincl' ] for load_option in load) > 1:
      raise ValueError("Conflicting options given: %s" % ', '.join(load))

  if load_nlo_dy and load_lo_dy:
    raise ValueError("Conflictiong options: %s; cannot load LO and NLO DY samples simultaneously" % ', '.join(load))

  sample_module = importlib.import_module('tthAnalysis.HiggsToTauTau.samples.stitch')
  samples_to_stitch = getattr(sample_module, 'samples_to_stitch_{}'.format(era))

  samples_binned = []
  if load_lo_dy:
    samples_binned.extend([ sample for sample in samples_to_stitch if sample['order'] == 'LO' and sample['meta'] == 'DY' ])
  elif load_nlo_dy:
    samples_binned.extend([ sample for sample in samples_to_stitch if sample['order'] == 'NLO' and sample['meta'] == 'DY' ])
  if load_wjets:
    samples_binned.extend([ sample for sample in samples_to_stitch if sample['order'] == 'LO' and sample['meta'] == 'W+jets' ])
  if load_lowmll_lo_dy:
    samples_binned.extend([ sample for sample in samples_to_stitch if sample['order'] == 'LO' and sample['meta'] == 'DY (low mll)' ])

  if not (load_lowmll_lo_dy and era != '2016'):
    assert(samples_binned)
  if not samples_binned:
    return samples

  sample_names_exclusive = []
  sample_names_inclusive = []
  for sample_set in samples_binned:
    for sample_key, sample_value in sample_set.items():
      if sample_key == 'inclusive':
        sample_names_inclusive.extend(sample_value['samples'])
      elif sample_key == 'exclusive':
        for split_var in sample_value:
          for sample_entry in sample_value[split_var]:
            sample_names_exclusive.extend(sample_entry['samples'])
  sample_names = sample_names_inclusive + sample_names_exclusive

  for sample_key, sample_info in samples.items():
    if sample_key == 'sum_events':
      continue
    process_name = sample_info['process_name_specific']
    if load_wjets and process_name.startswith(('WJetsToLNu', 'W1JetsToLNu', 'W2JetsToLNu', 'W3JetsToLNu', 'W4JetsToLNu')):
      if 'wjets' in load:
        sample_info["use_it"] = process_name in sample_names
      elif 'wjets_incl' in load:
        sample_info["use_it"] = process_name in sample_names_inclusive
      elif 'wjets_noincl' in load:
        sample_info["use_it"] = process_name in sample_names_exclusive
      else:
        assert(False)
    elif (load_lo_dy or load_nlo_dy) and process_name.startswith('DY') and '10to50' not in process_name:
      if 'dy_lo' in load or 'dy_nlo' in load:
        sample_info["use_it"] = process_name in sample_names
      elif 'dy_lo_incl' in load or 'dy_nlo_incl' in load:
        sample_info["use_it"] = process_name in sample_names_inclusive
      elif 'dy_lo_noincl' in load or 'dy_nlo_noincl' in load:
        sample_info["use_it"] = process_name in sample_names_exclusive
      else:
        assert(False)
    elif load_lowmll_lo_dy and process_name.startswith('DY') and '10to50' in process_name:
      if 'dy_lowmll_lo' in load:
        sample_info["use_it"] = process_name in sample_names
      elif 'dy_lowmll_lo_incl' in load:
        sample_info["use_it"] = process_name in sample_names_inclusive
      elif 'dy_lowmll_lo_noincl' in load:
        sample_info["use_it"] = process_name in sample_names_exclusive
      else:
        assert(False)

  return samples
