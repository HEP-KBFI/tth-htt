#!/usr/bin/env python

from tthAnalysis.HiggsToTauTau.common import logging, SmartFormatter
from tthAnalysis.HiggsToTauTau.safe_root import ROOT

ROOT.gROOT.SetBatch(True)

import numpy as np

import argparse
import os.path
import array

ACCEPTED_PLOT_EXTS = [ 'pdf', 'png' ]
ACCEPTED_PLOT_EXTS_TUPLE = tuple([ '.{}'.format(ext) for ext in ACCEPTED_PLOT_EXTS ])
GENWEIGHT_NAME = 'genWeight'
PLOT_BINS = 100
MAX_CUTOFF = 3

def create_output_dir(file_name):
  output_dir = os.path.dirname(file_name)
  if not os.path.isdir(output_dir):
    if not os.makedirs(output_dir):
      raise RuntimeError("Unable to create directory for the output file: %s" % file_name)

parser = argparse.ArgumentParser(
  formatter_class = lambda prog: SmartFormatter(prog, max_help_position = 50)
)
parser.add_argument('-i', '--input',
  type = str, dest = 'input', metavar = 'file', required = True,
  help = 'R|Input',
)
parser.add_argument('-o', '--output',
  type = str, dest = 'output', metavar = 'file', required = True,
  help = 'R|Output file',
)
parser.add_argument('-p', '--plot',
  type = str, dest = 'plot', metavar = 'file', required = False, nargs = '+', default = [],
  help = 'R|Output plot',
)
parser.add_argument('-v', '--verbose',
  dest = 'verbose', action = 'store_true', default = False,
  help = 'R|Enable verbose output',
)
args = parser.parse_args()

if args.verbose:
  logging.getLogger().setLevel(logging.DEBUG)

input_txt_file = args.input
output_file = args.output
plot_files = args.plot

if not os.path.isfile(input_txt_file):
  raise RuntimeError("No such file: %s" % input_txt_file)

create_output_dir(output_file)

if plot_files:
  for plot_file in plot_files:
    if not plot_file.endswith(ACCEPTED_PLOT_EXTS_TUPLE):
      raise RuntimeError(
        "Expected extensions %s, instead of whatever this is: %s" % (', '.join(ACCEPTED_PLOT_EXTS), plot_file)
      )
    create_output_dir(plot_file)

input_files = []
with open(input_txt_file, 'r') as input_file_ptr:
  for line in input_file_ptr:
    input_file_cand = line.rstrip()
    if not os.path.isfile(input_file_cand):
      raise RuntimeError("No such file: %s" % input_file_cand)
    input_files.append(input_file_cand)
logging.info("Found {} input files".format(len(input_files)))

weights_map = {}

def record_weights(file_name):
  fptr = ROOT.TFile.Open(file_name, 'read')
  tree = fptr.Get('Events')

  genWeight = array.array('f', [0.])
  tree.SetBranchAddress(GENWEIGHT_NAME, genWeight)

  tree.SetBranchStatus("*", 0)
  tree.SetBranchStatus(GENWEIGHT_NAME, 1)

  nof_events = tree.GetEntries()
  logging.info("Processing {} events from file {}".format(nof_events, file_name))
  for event_idx in range(nof_events):
    tree.GetEntry(event_idx)
    genWeight_val = genWeight[0]
    if genWeight_val not in weights_map:
      weights_map[genWeight_val] = 0
    weights_map[genWeight_val] += 1
  fptr.Close()

for input_file in input_files:
  record_weights(input_file)

weights_by_frequency = list(sorted(
  [ (weight, frequency) for weight, frequency in weights_map.items() ],
  key = lambda kv: kv[1],
  reverse = True,
))
most_frequent_weight = weights_by_frequency[0][0]
logging.info("The most frequent LHE weight is: {:.6e}".format(most_frequent_weight))
with open(output_file, 'w') as output_file_ptr:
  output_file_ptr.write('{:.6e}'.format(most_frequent_weight))
logging.info("Wrote output file: {}".format(output_file))

if plot_files:
  has_neg_weights = any(weight_freq[0] < 0 for weight_freq in weights_by_frequency)
  binning_max = MAX_CUTOFF * most_frequent_weight
  binning_min = -MAX_CUTOFF * most_frequent_weight
  if not has_neg_weights:
    binning_min = max(0., binning_min)
  binning = array.array('f', list(np.linspace(binning_min, binning_max, PLOT_BINS + 1)))

  histogram = ROOT.TH1D(GENWEIGHT_NAME, GENWEIGHT_NAME, PLOT_BINS, binning)
  for weight_freq in weights_by_frequency:
    histogram.Fill(weight_freq[0], weight_freq[1])
  histogram.GetXaxis().SetRange(0, histogram.GetNbinsX() + 1)

  for plot_file in plot_files:
    title = os.path.splitext(os.path.basename(plot_file))[0]
    histogram.SetTitle(title)

    canvas = ROOT.TCanvas()
    canvas.SetCanvasSize(1000, 800)
    canvas.SetLogy(True)
    histogram.Draw('hist')
    canvas.SaveAs(plot_file)
    canvas.Close()
    del canvas
  del histogram
