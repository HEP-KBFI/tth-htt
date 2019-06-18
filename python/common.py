import sys
import logging

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
def load_samples(era, is_postproc = True, base = 'tth', suffix = ''):
  if base == 'tth':
    base_str = 'tthAnalysis.HiggsToTauTau'
    sample_prefix = 'tthAnalyzeSamples'
  elif base == 'hh_multilepton':
    base_str = 'hhAnalysis.multilepton'
    sample_prefix = 'hhAnalyzeSamples'
  elif base == 'hh_bbww':
    base_str = 'hhAnalysis.bbww'
    sample_prefix = 'hhAnalyzeSamples'
  else:
    raise ValueError("Invalid base: %s" % base)
  assert(base_str and sample_prefix)
  assert(era in [ "2016", "2017", "2018" ])

  sample_name = 'samples_{}'.format(era)
  sample_location = "{}.samples.{}_{}".format(base_str, sample_prefix, era)

  if not is_postproc:
    suffix = "nanoAOD_{}".format(suffix)

  if suffix:
    sample_location += "_{}".format(suffix)

  sample_module = importlib.import_module(sample_location)
  sample = getattr(sample_module, sample_name)

  return sample

def load_samples_hh_multilepton(era, is_postproc = True, suffix = ''):
  return load_samples(era, is_postproc, "hh_multilepton", suffix)

def load_samples_hh_bbww(era, is_postproc = True, suffix = ''):
  return load_samples(era, is_postproc, "hh_bbww", suffix)

# X: dictionary taken from https://github.com/HEP-KBFI/tth-nanoAOD-tools/blob/master/python/tHweights_cfi.py
# I am not sure it would be handy to read cms.VPSet at this level
def couplings_tH_tags():
    #    kt   kv
    tHweights = [
      [-1.0, 1.0],
      [-3.0, 1.0],
      [-2.0, 1.0],
      [-1.5, 1.0],
      [-1.25, 1.0],
      [-0.75, 1.0],
      [-0.5, 1.0],
      [-0.25, 1.0],
      [0.0, 1.0],
      [0.25, 1.0],
      [0.5, 1.0],
      [0.75, 1.0],
      #[1.0, 1.0], - the SM does not have coupling on the name
      [1.25, 1.0],
      [1.5, 1.0],
      [2.0, 1.0],
      [3.0, 1.0],
      [-2.0, 1.5],
      [-1.25, 1.5],
      [-1.0, 1.5],
      [-0.5, 1.5],
      [-0.25, 1.5],
      [0.25, 1.5],
      [0.5, 1.5],
      [1.0, 1.5],
      [1.25, 1.5],
      [2.0, 1.5],
      [-3.0, 0.5],
      [-2.0, 0.5],
      [-1.25, 0.5],
      [1.25, 0.5],
      [2.0, 0.5],
      [3.0, 0.5],
    ]
    couplings_tH_tag = []
    for combination in tHweights :
      # kt_m0p25_kv_1
      tag = "kt_%s_kv_%s" % (str(combination[0]).replace("-","m").replace(".","p").replace("p0",""), str(combination[1]).replace("-","m").replace(".","p").replace("p0",""))
      couplings_tH_tag += [tag]
    return couplings_tH_tag
