#!/usr/bin/env python

from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017_nanoAOD import samples_2017 as samples
from hhAnalysis.multilepton.samples.hhAnalyzeSamples_2017_wjets_nanoAOD import samples_2017 as samples_hh
from tthAnalysis.HiggsToTauTau.safe_root import ROOT

import argparse
import os

class SmartFormatter(argparse.HelpFormatter):
  def _split_lines(self, text, width):
    if text.startswith('R|'):
      return text[2:].splitlines()
    return argparse.HelpFormatter._split_lines(self, text, width)

parser = argparse.ArgumentParser(formatter_class = lambda prog: SmartFormatter(prog, max_help_position = 35))
parser.add_argument(
  '-i', '--input', dest = 'input', metavar = 'file', required = False, type = str,
  default = os.path.join(os.environ['CMSSW_BASE'], 'src', 'tthAnalysis', 'HiggsToTauTau', 'data', 'pileup_2017.root'),
  help = 'R|Input ROOT file containing MC PU distributions',
)
parser.add_argument(
  '-d', '--output', dest = 'output', metavar = 'file', required = False, type = str,
  default = os.path.join(os.environ['CMSSW_BASE'], 'src', 'hhAnalysis', 'multilepton', 'data', 'pileup_wjets_2017.root'),
  help = 'R|Output',
)
args = parser.parse_args()

src_file = args.input
dst_file = args.output

if not os.path.isfile(src_file):
  raise ValueError('No such file: %s' % src_file)
dst_file_dir = os.path.dirname(dst_file)
if not os.path.isdir(dst_file_dir):
  raise ValueError('Directory %s does not exist' % dst_file_dir)

sample_mapping = {}
for sample_key, sample_val in samples_hh.items():
  if sample_key == 'sum_events': continue
  process_name = sample_val['process_name_specific']
  sample_key_split = sample_key.split('/')
  assert(len(sample_key_split) == 5)
  sample_key_true = '/'.join(sample_key_split[:-1])
  sample_mapping[process_name] = samples[sample_key_true]['process_name_specific']

src_file_ptr = ROOT.TFile.Open(src_file, 'read')
dst_file_ptr = ROOT.TFile.Open(dst_file, 'recreate')

for h_dst_name in list(sorted(sample_mapping)):
  h_src_name = sample_mapping[h_dst_name]
  h_src = src_file_ptr.Get(h_src_name)
  assert(h_src)
  h_dst = h_src.Clone()
  h_dst.SetName(h_dst_name)
  h_dst.SetTitle(h_dst_name)
  dst_file_ptr.cd()
  h_dst.Write()

src_file_ptr.Close()
dst_file_ptr.Close()


