#!/usr/bin/env python

import ROOT
import array
import os

ROOT.gStyle.SetOptStat(0)

HISTOGRAM_NAME = 'histo_eff_data'

def get_data(fn):
  assert(os.path.isfile(fn))
  fptr = ROOT.TFile.Open(fn, 'read')
  assert(fptr)
  histogram = fptr.Get(HISTOGRAM_NAME)
  assert(histogram)
  assert(type(histogram) == ROOT.TH1D)
  axis = histogram.GetXaxis()
  nbins = axis.GetNbins()
  binning = [ axis.GetBinUpEdge(bin_idx) for bin_idx in range(nbins + 1) ]
  content = [ histogram.GetBinContent(bin_idx) for bin_idx in range(1, nbins + 1) ]
  fptr.Close()
  abs_differences = [ abs(1. - bin_content) for bin_content in content ]
  return binning, abs_differences

def create_histogram(name, binning_x, binning_y, content):
  binning_x_arr = array.array('f', binning_x)
  binning_y_arr = array.array('f', binning_y)
  histogram = ROOT.TH2D(name, name, len(binning_x_arr) - 1, binning_x_arr, len(binning_y_arr) - 1, binning_y_arr)
  histogram.SetOption("colz;text")
  for row_idx in range(len(content)):
    for col_idx in range(len(content[row_idx])):
      histogram.SetBinContent(row_idx + 1, col_idx + 1, content[row_idx][col_idx])
  return histogram

def create_file(filename_pt, filename_eta, filename_out):

  bins_pt, diffs_pt = get_data(filename_pt)
  bins_eta, diffs_eta = get_data(filename_eta)

  results_min, results_max = [], []
  for sgn in [ +1, -1 ]:
    comparison = max if sgn > 0 else min
    for eta_idx, diff_eta in enumerate(diffs_eta):
      shift_eta = 1. + sgn * diff_eta
      row = []
      for pt_idx, diff_pt in enumerate(diffs_pt):
        shift_pt = 1. + sgn * diff_pt
        row.append(comparison(shift_pt, shift_eta))
      if sgn > 0:
        results_max.append(row)
      else:
        results_min.append(row)

  histogram_min_sf = create_histogram('{}_min'.format(HISTOGRAM_NAME), bins_eta, bins_pt, results_min)
  histogram_max_sf = create_histogram('{}_max'.format(HISTOGRAM_NAME), bins_eta, bins_pt, results_max)

  for row_idx in range(len(bins_eta) - 1):
    for col_idx in range(len(bins_pt) - 1):
      val_min = histogram_min_sf.GetBinContent(row_idx + 1, col_idx + 1)
      assert(val_min <= 1.)
      val_max = histogram_max_sf.GetBinContent(row_idx + 1, col_idx + 1)
      assert(val_max >= 1.)
      val_avg = (val_min + val_max) / 2
      assert(val_avg == 1.)

  fptr_out = ROOT.TFile.Open(filename_out, 'recreate')
  histogram_min_sf.Write()
  histogram_max_sf.Write()
  fptr_out.Close()

if __name__ == '__main__':
  basedir = os.path.join(os.environ['CMSSW_BASE'], 'src/tthAnalysis/HiggsToTauTau/data/leptonSF')
  assert(os.path.isdir(basedir))
  for era in [ 2016, 2017, 2018 ]:
    basedir_era = os.path.join(basedir, str(era))
    for lepton in [ 'e', 'm' ]:
      filename_base = 'lepMVAEffSF_{}_error'.format(lepton)
      filename_pt = os.path.join(basedir_era, '{}_pt.root'.format(filename_base))
      assert(os.path.isfile(filename_pt))
      filename_eta = os.path.join(basedir_era, '{}_eta.root'.format(filename_base))
      assert(os.path.isfile(filename_eta))
      filename_out = os.path.join(basedir_era, '{}.root'.format(filename_base))
      create_file(filename_pt, filename_eta, filename_out)
      assert(os.path.isfile(filename_out))
