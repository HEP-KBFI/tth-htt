#!/usr/bin/env python

from tthAnalysis.HiggsToTauTau.safe_root import ROOT
from tthAnalysis.HiggsToTauTau.common import SmartFormatter, logging

import matplotlib
matplotlib.use('Agg')

import matplotlib.pyplot as plt
import matplotlib.backends.backend_pdf as backend_pdf

import os
import argparse
import collections
import re

PILEUP_HISTOGRAM_NAME = 'pileup'

DATA_PILEUP = {
  2016 : os.path.join(os.environ['CMSSW_BASE'], 'src/PhysicsTools/NanoAODTools/python/postprocessing/data/pileup/PileupData_ReRecoJSON_Full2016.root'),
  2017 : os.path.join(os.environ['CMSSW_BASE'], 'src/PhysicsTools/NanoAODTools/python/postprocessing/data/pileup/PileupData_ReRecoJSON_v1_Full2017.root'),
  2018 : os.path.join(os.environ['CMSSW_BASE'], 'src/PhysicsTools/NanoAODTools/python/postprocessing/data/pileup/PileupData_EarlyReRecoJSON_2018ABC_PromptEraD_Full2018.root'),
}

MC_PILEUP = [
  os.path.join(os.environ['CMSSW_BASE'], 'src/tthAnalysis/HiggsToTauTau/data/pileup_{era}.root'),
  os.path.join(os.environ['CMSSW_BASE'], 'src/hhAnalysis/multilepton/data/pileup_hh_{era}.root'),
  os.path.join(os.environ['CMSSW_BASE'], 'src/hhAnalysis/bbww/data/pileup_hh_{era}.root'),
  os.path.join(os.environ['CMSSW_BASE'], 'src/hhAnalysis/bbww/data/pileup_hh_{era}_ttbar.root'),
]

def get_histogram(filename, read_mc):
  if not os.path.isfile(filename):
    raise RuntimeError("No such file: %s" % filename)
  fptr = ROOT.TFile.Open(filename, 'read')
  histogram_names = [ key.GetName() for key in fptr.GetListOfKeys() ]
  histograms = collections.OrderedDict()
  for histogram_name in histogram_names:
    if not read_mc and histogram_name != PILEUP_HISTOGRAM_NAME:
        continue
    histogram = fptr.Get(histogram_name)
    histogram.Scale(1. / histogram.Integral())
    histograms[histogram_name] = [ histogram.GetBinContent(bin_idx) for bin_idx in range(1, histogram.GetNbinsX() + 1) ]
  fptr.Close()
  return histograms[PILEUP_HISTOGRAM_NAME] if not read_mc else histograms

def plot(era, pdf, threshold, samples, plot_all):
  logging.info("Processing era {}".format(era))

  data_filename = DATA_PILEUP[era]
  data = get_histogram(data_filename, False)
  data_len = len(data)
  plot_x = list(range(0, data_len))

  for mc_filename_idx, mc_filename_expr in enumerate(MC_PILEUP):
    mc_filename = mc_filename_expr.format(era = era)
    mc = get_histogram(mc_filename, True)

    for sample_idx, sample_name in enumerate(mc.keys()):
      logging.info('Processing {} {}/{} ({}/{})'.format(sample_name, sample_idx + 1, len(mc), mc_filename_idx + 1, len(MC_PILEUP)))
      if samples and not any(re.match(sample, sample_name) for sample in samples):
        continue

      mc_histogram = mc[sample_name]
      assert(data_len == len(mc_histogram))

      ratios = [
        data[bin_idx] / mc_histogram[bin_idx] if mc_histogram[bin_idx] > 0. else 1. for bin_idx in range(data_len)
      ]
      ratios_over_threshold = [ ratio for ratio in enumerate(ratios) if ratio[1] > threshold ]

      if not ratios_over_threshold and not plot_all:
        continue

      plt.figure(figsize = (10, 8), dpi = 150)
      plt.step(plot_x, data, label = 'Data', where = 'post')
      plt.step(plot_x, mc_histogram, label = 'MC', where = 'post')
      plt.xlim(0, data_len)
      plt.yscale('log')
      plt.grid(True)
      for ratio in ratios_over_threshold:
        ratio_idx = ratio[0]
        rec = matplotlib.patches.Rectangle((ratio_idx - 1, 0), 1, 1, color = 'yellow', alpha = 0.5)
        plt.gca().add_patch(rec)
      plt.title('{} ({})'.format(sample_name, era))
      plt.legend(loc = 'lower left')
      plt.xlabel('# PU interactions')
      plt.ylabel('Number of events, normalized to 1')
      plt.savefig(pdf, format = 'pdf', bbox_inches = 'tight')
      plt.close()

parser = argparse.ArgumentParser(
    formatter_class = lambda prog: SmartFormatter(prog, max_help_position = 35)
)
parser.add_argument('-e', '--era',
  type = int, dest = 'era', metavar = 'year', required = False, nargs = '+', choices = list(DATA_PILEUP.keys()),
  default = list(DATA_PILEUP.keys()),
  help = 'R|Era',
)
parser.add_argument('-o', '--output',
  type = str, dest = 'output', metavar = 'path', required = True,
  help = 'R|PDF file name',
)
parser.add_argument('-t', '--threshold',
  type = float, dest = 'threshold', metavar = 'number', required = False, default = 3.0,
  help = 'R|PU weight threshold for highlighting',
)
parser.add_argument('-s', '--sample',
  type = str, dest = 'sample', metavar = 'name', required = False, nargs = '+', default = [],
  help = 'R|Plot specific samples',
)
parser.add_argument('-a', '--all-plot',
  dest = 'all_plot', action = 'store_true', default = False,
  help = 'R|Also include PU profiles not exceeding the threshold',
)
args = parser.parse_args()

eras = args.era
output = os.path.abspath(args.output)
threshold = args.threshold
sample = args.sample
plot_all = args.all_plot

if not output.lower().endswith('.pdf'):
  raise ValueError("Output file can be in PDF format only: %s" % output)

if not os.path.isdir(os.path.dirname(output)):
  raise ValueError("Cannot create file %s because its directory does not exist" % output)

with backend_pdf.PdfPages(output) as pdf:
  for era in eras:
    plot(era, pdf, threshold, sample, plot_all)
