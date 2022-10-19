#!/usr/bin/env python

from tthAnalysis.HiggsToTauTau.safe_root import ROOT
from tthAnalysis.HiggsToTauTau.common import SmartFormatter, logging

import collections
import argparse
import os.path
import logging

parser = argparse.ArgumentParser(
  formatter_class = lambda prog: SmartFormatter(prog, max_help_position = 35)
)
parser.add_argument('-i', '--input',
  type = str, dest = 'input', metavar = 'path', required = True, nargs = '+',
  help = 'R|ROOT files',
)
parser.add_argument('-o', '--output',
  type = str, dest = 'output', metavar = 'file', required = True,
  help = 'R|Output file',
)
parser.add_argument('-n', '--name',
  type = str, dest = 'name', metavar = 'str', required = True,
  help = 'R|TDirectory name',
)
args = parser.parse_args()

inputs = args.input
output = args.output
name = args.name

output_dir = os.path.dirname(os.path.abspath(output))
if not os.path.isdir(output_dir):
  raise RuntimeError("The directory for the file %s does not exist" % output)

histograms = collections.OrderedDict()
for input_fn in inputs:
  logging.info("Reading file: {}".format(input_fn))
  if not os.path.isfile(input_fn):
    raise RuntimeError("No such directory: %s" % input_fn)
  input_fptr = ROOT.TFile.Open(input_fn, 'read')
  keys = [ key.GetName() for key in input_fptr.GetListOfKeys() ]
  for key in keys:
    obj = input_fptr.Get(key)
    if not obj.InheritsFrom("TH1"):
      continue
    obj.SetDirectory(0)
    if key in histograms:
      histograms[key].Add(obj)
    else:
      histograms[key] = obj
  input_fptr.Close()

output_fptr = ROOT.TFile.Open(output, 'recreate')
output_dptr = output_fptr.mkdir(name)
output_dptr.cd()
for key in histograms:
  histograms[key].Write()
output_fptr.Close()
