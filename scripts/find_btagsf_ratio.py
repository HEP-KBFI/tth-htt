#!/usr/bin/env python

from tthAnalysis.HiggsToTauTau.safe_root import ROOT
from tthAnalysis.HiggsToTauTau.common import SmartFormatter, logging

import matplotlib
matplotlib.use('Agg') # headless mode

import matplotlib.pyplot as plt
import matplotlib.backends.backend_pdf as backend_pdf
import numpy as np

import functools
import re
import collections
import array
import argparse
import math
import os

def create_dir_if_not_exists(output_filename, force):
  output_dirname = os.path.dirname(output_filename)
  if not os.path.isdir(output_dirname):
    if not force:
      raise RuntimeError("Output directory %s does not exist" % output_dirname)
    else:
      os.makedirs(output_dirname)

def quadsum(arr):
  return math.sqrt(functools.reduce(lambda x, y: x + y ** 2, arr, 0.))

def read_histogram(fp, histogram_name, max_bins):
  histogram = fp.Get(histogram_name)
  nbins = histogram.GetXaxis().GetNbins()
  histogram_values = [ histogram.GetBinContent(bin_idx) for bin_idx in range(1, nbins + 1) ]
  histogram_errors = [ histogram.GetBinError(bin_idx) for bin_idx in range(1, nbins + 1) ]
  if max_bins > 1 and max_bins < nbins:
    histogram_values = histogram_values[:max_bins - 1] + [ sum(histogram_values[max_bins - 1:]) ]
    histogram_errors = histogram_errors[:max_bins - 1] + [ quadsum(histogram_errors[max_bins - 1:]) ]
  return histogram_values, histogram_errors

def extract_from_name(name):
  match = re.match('(?P<sample>.*)_(wBtag|woBtag)(?P<sys>.*)', name)
  if not match:
    raise RuntimeError("Invalid histogram name: %s" % name)

  sample_name = match.group('sample')
  sys_name = match.group('sys')
  if sys_name:
    sys_name = sys_name[1:]
  return sample_name, sys_name

def get_ratios(wobtag_count, wbtag_count, wobtag_label, wbtag_label):
  ratios = []
  for bin_idx in range(len(wobtag_count)):
    wobtag_count_bin_idx = wobtag_count[bin_idx]
    wbtag_count_bin_idx = wbtag_count[bin_idx]
    if wobtag_count_bin_idx == 0. and wbtag_count_bin_idx == 0.:
      ratios.append(1.)
    elif wobtag_count_bin_idx != 0. and wbtag_count_bin_idx == 0.:
      raise RuntimeError(
        'Found bin idx %d in histogram %s with zero events but %.2f events in histogram %s' % \
        (bin_idx, wbtag_label, wobtag_count_bin_idx, wobtag_label)
      )
    elif wobtag_count_bin_idx == 0. and wbtag[bin_idx] != 0.:
      raise RuntimeError(
        'Found bin idx %d in histogram %s with zero events but %.2f events in histogram %s' % \
        (bin_idx, wobtag_label, wbtag_count_bin_idx, wbtag_label)
      )
    else:
      ratio = wobtag_count_bin_idx / wbtag_count_bin_idx
      if ratio < 0.:
        logging.warning(
          'Found event sums with opposite sign at bin {} in histograms {} and {}: {:.2f} and {:.2f} '
          '-> setting ratio to 1 instead'.format(
            bin_idx, wobtag_label, wbtag_label, wobtag_count_bin_idx, wbtag_count_bin_idx
          )
        )
        ratio = 1.
      ratios.append(ratio)
  return ratios

def get_ratio_errs(ratios, wobtag_count, wbtag_count, wobtag_err, wbtag_err):
  ratio_errs = []
  for bin_idx in range(len(wobtag_err)):
    if wobtag_count[bin_idx] != 0. and wbtag_count[bin_idx] != 0.:
      ratio_err = ratios[bin_idx] * math.sqrt(
        (wobtag_err[bin_idx] / wobtag_count[bin_idx]) ** 2 + (wbtag_err[bin_idx] / wbtag_count[bin_idx]) ** 2
      )
    else:
      ratio_err = 0.
    ratio_errs.append(ratio_err)
  return ratio_errs

parser = argparse.ArgumentParser(
    formatter_class = lambda prog: SmartFormatter(prog, max_help_position = 35)
)
parser.add_argument('-i', '--input',
  type = str, dest = 'input', metavar = 'path', required = True,
  help = 'R|Input file name',
)
parser.add_argument('-o', '--output',
  type = str, dest = 'output', metavar = 'path', required = True,
  help = 'R|Output file name',
)
parser.add_argument('-n', '--max-bins',
  type = int, dest = 'max_bins', metavar = 'int', required = False, default = -1,
  help = 'R|Max number of bins (negative or zero: use the default)',
)
parser.add_argument('-p', '--plot',
  type = str, dest = 'plot', metavar = 'path', required = False,
  help = 'R|Plot file name',
)
parser.add_argument('-c', '--central-only',
  dest = 'central_only', action = 'store_true', default = False,
  help = 'R|Save only the central ratios to the output file',
)
parser.add_argument('-f', '--force',
  dest = 'force', action = 'store_true', default = False,
  help = 'R|Create output directory if it does not exist',
)
args = parser.parse_args()

input = args.input
output = os.path.abspath(args.output)
max_bins = args.max_bins
plot = os.path.abspath(args.plot)
central_only = args.central_only
force = args.force

if not os.path.isfile(input):
  raise ValueError("No such input file: %s" % input)

output_dir = os.path.dirname(output)
create_dir_if_not_exists(output, force)

if plot:
  create_dir_if_not_exists(plot, force)

if plot and not plot.endswith('.pdf'):
  raise ValueError("Can only accept the path to plot in pdf format: %s" % plot)

fptr = ROOT.TFile.Open(input, 'read')
histogram_names = [ key.GetName() for key in fptr.GetListOfKeys() ]

results = collections.OrderedDict()
for histogram_name_wobtag in histogram_names:
  if 'woBtag' not in histogram_name_wobtag:
    continue
  histogram_name_wbtag = histogram_name_wobtag.replace('woBtag', 'wBtag')

  sample_name, sys_name = extract_from_name(histogram_name_wobtag)
  if sample_name not in results:
    results[sample_name] = collections.OrderedDict()
  assert(sys_name not in results[sample_name])

  wobtag, wobtag_err = read_histogram(fptr, histogram_name_wobtag, max_bins)
  wbtag, wbtag_err = read_histogram(fptr, histogram_name_wbtag, max_bins)
  ratios = get_ratios(wobtag, wbtag, histogram_name_wobtag, histogram_name_wbtag)
  ratio_errs = get_ratio_errs(ratios, wobtag, wbtag, wobtag_err, wbtag_err)
  results[sample_name][sys_name] = {
    'wobtag': {
      'count' : wobtag,
      'err'   : wobtag_err,
    },
    'wbtag': {
      'count' : wbtag,
      'err'   : wbtag_err,
    },
    'ratio' : {
      'count' : ratios,
      'err'   : ratio_errs,
    },
  }

for sample_name in results:
    assert('central' in results[sample_name])
    nbins = len(results[sample_name]['central']['ratio']['count'])
    min_ratios = [ +1e+3 ] * nbins
    max_ratios = [ -1e+3 ] * nbins
    for sys_name in results[sample_name]:
        if not sys_name:
            continue
        ratios = results[sample_name][sys_name]['ratio']['count']
        assert(len(ratios) == nbins)
        for bin_idx in range(nbins):
            min_ratios[bin_idx] = min(min_ratios[bin_idx], ratios[bin_idx])
            max_ratios[bin_idx] = max(max_ratios[bin_idx], ratios[bin_idx])
    results[sample_name]['envelopeMin'] = min_ratios
    results[sample_name]['envelopeMax'] = max_ratios

if plot:
  with backend_pdf.PdfPages(plot) as pdf:
    for sample_name in results:
      fig, ax = plt.subplots(2, 1, sharex = True, figsize = (10, 12), dpi = 100)
      fig.subplots_adjust(hspace = 0)

      plot_y = results[sample_name]['central']['ratio']['count']
      plot_yerr = results[sample_name]['central']['ratio']['err']
      plot_sys_ymin = results[sample_name]['envelopeMin']
      plot_sys_ymax = results[sample_name]['envelopeMax']
      nbins = len(plot_y)
      assert(nbins == len(plot_yerr))
      plot_x = list(range(nbins))

      ax[0].axhline(y = 1.0, color = 'black', linestyle = '-')
      ax[0].fill_between(
        plot_x, plot_sys_ymin, plot_sys_ymax, alpha = 0.2, color = 'green', label = 'Syst unc (JES, JER, btag)'
      )
      ax[0].errorbar(plot_x, plot_y, yerr = plot_yerr, fmt = 'o', markersize = 4, label = 'Central + stat unc')
      ax[0].grid(True)
      ax[0].set_xticks(np.arange(0, nbins + 1, 1.))
      ax[0].set_yticks(np.arange(-0.5, 1.5, 0.1))
      ax[0].set_xlim(-0.5, nbins - 0.5)
      ax[0].set_ylim(0.5, 1.5)
      ax[0].set_ylabel(r'$\sum w(\mathrm{no\;btag\;SF}) / \sum w(\mathrm{with\;btag\;SF})$')
      ax[0].set_title(sample_name)
      ax[0].legend(loc = 'upper right', fontsize = 8)

      plot_y1 = results[sample_name]['central']['wobtag']['count']
      plot_y2 = results[sample_name]['central']['wbtag']['count']
      nbins1 = len(plot_y1)
      nbins2 = len(plot_y2)
      assert(nbins == nbins1)
      assert(nbins == nbins2)

      ax[1].step(plot_x, plot_y1, label = 'Without b-tagging SF (central)', where = 'mid')
      ax[1].step(plot_x, plot_y2, label = 'With b-tagging SF (central)', where = 'mid')
      ax[1].set_yscale('log')
      ax[1].grid(True, which = 'both')
      ax[1].set_xlabel('# preselected jets')
      ax[1].set_ylabel('Sum of event weights per bin')
      ax[1].legend(loc = 'upper left', fontsize = 8)

      plt.savefig(pdf, format = 'pdf', bbox_inches = 'tight')
      plt.close()

out_fptr = ROOT.TFile.Open(output, 'recreate')
for sample_key in results:
  sample_dir = out_fptr.mkdir(sample_key)
  sample_dir.cd()
  assert('central' in results[sample_key])
  for sys_key in results[sample_key]:
    if central_only and sys_key != 'central':
      continue
    if not sys_key or sys_key.startswith('envelope'):
      continue
    ratios = results[sample_key][sys_key]['ratio']['count']
    ratio_errs = results[sample_key][sys_key]['ratio']['err']
    nbins = len(ratios)
    xbins = array.array('f', range(nbins))
    histogram = ROOT.TH1D(sys_key, sys_key, len(xbins) - 1, xbins)
    histogram.SetDirectory(sample_dir)
    histogram.SetXTitle('# preselected jets')
    histogram.SetTitle('{} ({})'.format(sample_key, sys_key))
    for bin_idx in range(nbins):
      histogram.SetBinContent(bin_idx + 1, ratios[bin_idx])
      histogram.SetBinError(bin_idx + 1, ratio_errs[bin_idx])
    histogram.Write()
    del histogram
out_fptr.Close()
