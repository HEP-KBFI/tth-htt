#!/usr/bin/env python

from tthAnalysis.HiggsToTauTau.safe_root import ROOT
from tthAnalysis.HiggsToTauTau.common import logging, SmartFormatter
from tthAnalysis.HiggsToTauTau.configs.EvtYieldHistManager_cfi import * # EvtYieldHistManager_201*

import logging
import argparse
import os
import hashlib

# Credit to: https://stackoverflow.com/a/3431838/4056193
def md5(fname):
  hash_md5 = hashlib.md5()
  with open(fname, "rb") as f:
    for chunk in iter(lambda: f.read(4096), b""):
      hash_md5.update(chunk)
  return hash_md5.hexdigest()

class Histograms(object):
  def __init__(self, fn, sf):
    self.fn = fn
    logging.info("Scaling histograms in file {} ({}) by SF {}".format(self.fn, md5(self.fn), sf))

    fptr = ROOT.TFile.Open(self.fn, 'read')
    keys = [ key.GetName() for key in fptr.GetListOfKeys() ]
    self.histograms = {}
    for key in keys:
      histogram = fptr.Get(key).Clone()
      histogram.SetDirectory(0)
      assert(type(histogram) == ROOT.TH2D)
      assert(key not in self.histograms)
      histogram.Scale(sf)
      logging.info("Found histogram {} in file {}".format(key, self.fn))
      self.histograms[key] = histogram

    fptr.Close()

  def get_excess(self, common_histograms):
    return list(sorted(set(self.histograms.keys()) - common_histograms))

def compatible_binning(lhs, rhs):
  lhs_axis_x = lhs.GetXaxis()
  lhs_axis_y = lhs.GetYaxis()
  rhs_axis_x = rhs.GetXaxis()
  rhs_axis_y = rhs.GetYaxis()

  lhs_nbinsx = lhs_axis_x.GetNbins()
  lhs_nbinsy = lhs_axis_y.GetNbins()
  rhs_nbinsx = rhs_axis_x.GetNbins()
  rhs_nbinsy = rhs_axis_y.GetNbins()
  if lhs_nbinsx != rhs_nbinsx:
    return False
  if lhs_nbinsy != rhs_nbinsy:
    return False
  lhs_binning_x = [ lhs_axis_x.GetBinUpEdge(i) for i in range(lhs_nbinsx + 1) ]
  lhs_binning_y = [ lhs_axis_y.GetBinUpEdge(i) for i in range(lhs_nbinsy + 1) ]
  rhs_binning_x = [ rhs_axis_x.GetBinUpEdge(i) for i in range(rhs_nbinsx + 1) ]
  rhs_binning_y = [ rhs_axis_y.GetBinUpEdge(i) for i in range(rhs_nbinsy + 1) ]
  if lhs_binning_x != rhs_binning_x:
    return False
  if lhs_binning_y != rhs_binning_y:
    return False
  return True

def get_sfs(era, periods):
  if era == 2016:
    evt_yields = EvtYieldHistManager_2016
  elif era == 2017:
    evt_yields = EvtYieldHistManager_2017
  elif era == 2018:
    evt_yields = EvtYieldHistManager_2018
  else:
    raise RuntimeError("Invalid era: %d" % era)

  subtotals = []
  for period in periods:
    subtotal = 0.
    for acquisition_era in period:
      key = 'Run{}{}'.format(era, acquisition_era)
      if not hasattr(evt_yields, key):
        raise RuntimeError("No such acquisition era found in year %d: %s" % (era, acquisition_era))
      subtotal += float(getattr(evt_yields, key).luminosity.configValue())
    logging.info("Sum of integrated luminosity across eras {} in year {}: {}".format(period, era, subtotal))
    subtotals.append(subtotal)
  lumi_sum = sum(subtotals)
  logging.info("Total integrated luminosity in year {}: {}".format(era, lumi_sum))
  sfs = [ subtotal / lumi_sum for subtotal in subtotals ]
  return sfs

if __name__ == '__main__':
  parser = argparse.ArgumentParser()
  parser.add_argument('-i', '--input',
    type = str, dest = 'input', metavar = 'directory', required = True, nargs = '+',
    help = 'R|Input TH2 SFs',
  )
  parser.add_argument('-e', '--era',
    type = int, dest = 'era', metavar = 'year', required = True, choices = [ 2016, 2017, 2018 ],
    help = 'R|Era',
  )
  parser.add_argument('-p', '--periods',
    type = str, dest = 'periods', metavar = 'period', required = True, nargs = '+',
    help = 'R|Acquisition eras (eg AB and CDE)',
  )
  parser.add_argument('-o', '--output',
    type = str, dest = 'output', metavar = 'file', required = True,
    help = 'R|Output file path',
  )
  args = parser.parse_args()

  if len(args.input) != len(args.periods):
    raise ValueError("Number of input files must equal to the number of acquisition eras")
  sfs = get_sfs(args.era, args.periods)

  assert(all([ os.path.isfile(fn) for fn in args.input ]))
  assert(len(args.input) == len(sfs))
  inputs = [ Histograms(args.input[i], sfs[i]) for i in range(len(args.input)) ]
  
  # make sure that all input ROOT files the same histograms in them
  assert(len(inputs) > 0)
  common_histograms = set(inputs[0].histograms.keys())
  for input in inputs[1:]:
    common_histograms.intersection_update(set(input.histograms.keys()))
  for input in inputs:
    excess = input.get_excess(common_histograms)
    if excess:
      raise RuntimeError("Found uncommon histograms in file %s: %s" % (input.fn, ', '.join(excess)))
  
  # add the histograms
  result = {}
  for common_histogram in common_histograms:
    histogram_base = inputs[0].histograms[common_histogram].Clone()
    for input in inputs[1:]:
      other_histogram = input.histograms[common_histogram]
      assert(compatible_binning(histogram_base, other_histogram))
      histogram_base.Add(other_histogram)
    result[common_histogram] = histogram_base

  output_dir = os.path.dirname(os.path.abspath(args.output))
  if not os.path.isdir(output_dir):
    os.makedirs(output_dir)

  output_f = ROOT.TFile.Open(args.output, 'recreate')
  output_f.cd()
  for common_histogram in common_histograms:
    result[common_histogram].Write()
  output_f.Close()
  logging.info("Wrote file: {}".format(args.output))
