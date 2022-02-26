#!/usr/bin/env python

# example usage:
# project_vpt.py -i wjets.txt -o WJets.root -x 61526.7

from tthAnalysis.HiggsToTauTau.common import SmartFormatter, logging
from tthAnalysis.HiggsToTauTau.safe_root import ROOT

import numpy as np
import collections
import argparse
import array
import os.path

MAX_LHE_NB = 2
LUMI = 1.e+3 # effective luminosity
HISTO_NAME_WGT = 'LHEVpt_wgt'
LHEVPT_BRANCH_NAME = 'LHE_Vpt'
LHE_NB_BRANCH_NAME = 'LHE_Nb'
GENWEIGHT_BRANCH_NAME = 'genWeight'

if __name__ == '__main__':
  parser = argparse.ArgumentParser(
    formatter_class = lambda prog: SmartFormatter(prog, max_help_position = 50)
  )
  parser.add_argument('-i', '--input',
    type = str, dest = 'input', metavar = 'file', required = True,
    help = 'R|Text file containing list of input files (one per line)',
  )
  parser.add_argument('-o', '--output',
    type = str, dest = 'output', metavar = 'path', required = True,
    help = 'R|Output file name',
  )
  parser.add_argument('-x', '--cross-section',
    type = float, dest = 'cross_section', metavar = 'nr', required = True,
    help = 'R|Cross section of the process in pb',
  )
  args = parser.parse_args()

  input_txt_fn = args.input
  output_fn = args.output
  xsec = args.cross_section

  if os.path.isfile(output_fn):
    raise RuntimeError("Output file already exists: %s" % output_fn)

  assert(xsec > 0.)
  input_fns = []
  with open(input_txt_fn, 'r') as input_txt_f:
    for line in input_txt_f:
      line_stripped = line.rstrip('\n')
      if not line_stripped.endswith('.root'):
        raise RuntimeError("ROOT file expected, but got: %s" % line_stripped)
      if not os.path.isfile(line_stripped):
        raise RuntimeError("No such file: %s" % line_stripped)
      input_fns.append(line_stripped)
  logging.info('Detected {} input file(s)'.format(len(input_fns)))

  # create the output file, set up histograms
  binning = array.array('f', list(np.arange(1, 1001, 1)))

  histograms = collections.OrderedDict()
  for nb_int in range(MAX_LHE_NB + 1):
    nb = str(nb_int)
    histName = '{}_LHENb{}'.format(HISTO_NAME_WGT, nb)
    histograms[nb] = ROOT.TH1D(histName, histName, len(binning) - 1, binning)
    histograms[nb].Sumw2()
  histograms['incl'] = ROOT.TH1D(HISTO_NAME_WGT, HISTO_NAME_WGT, len(binning) - 1, binning)
  histograms['incl'].Sumw2()

  for input_fn in input_fns:
    input_fptr = ROOT.TFile.Open(input_fn, 'read')
    tree = input_fptr.Get('Events')
    nof_events = tree.GetEntries()
    logging.info('Processing {} ({} events)'.format(input_fn, nof_events))

    lhe_vpt = array.array('f', [0.])
    lhe_nb = array.array('B', [0])
    genWeight = array.array('f', [0.])
    tree.SetBranchAddress(LHEVPT_BRANCH_NAME, lhe_vpt)
    tree.SetBranchAddress(LHE_NB_BRANCH_NAME, lhe_nb)
    tree.SetBranchAddress(GENWEIGHT_BRANCH_NAME, genWeight)

    tree.SetBranchStatus('*', 0)
    tree.SetBranchStatus(LHEVPT_BRANCH_NAME, 1)
    tree.SetBranchStatus(LHE_NB_BRANCH_NAME, 1)
    tree.SetBranchStatus(GENWEIGHT_BRANCH_NAME, 1)

    for event_idx in range(nof_events):
      tree.GetEntry(event_idx)
      histograms['incl'].Fill(lhe_vpt[0], genWeight[0])
      histograms[str(min(lhe_nb[0], MAX_LHE_NB))].Fill(lhe_vpt[0], genWeight[0])

    input_fptr.Close()

  # write the histograms and close the output file
  output_fptr = ROOT.TFile.Open(output_fn, 'recreate')
  if not output_fptr:
    raise RuntimeError("Unable to create file: %s" % output_fn)
  output_fptr.cd()

  for histogram_name, histogram in histograms.items():
    sf = histogram.Integral() / histograms['incl'].Integral()
    histogram.Scale(sf * LUMI * xsec / histogram.Integral())
    histogram.Write()
  output_fptr.Close()
  logging.info('Wrote file: {}'.format(output_fn))
