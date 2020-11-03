#!/usr/bin/env python

'''
Example usage:

recomp_leptonSF.py -i data/leptonSF/2016/lepMVAEffSF_e_3l.root -e 2016 -l electron -t disabled -o lepMVAEffSF_e_2016_recomp.root
'''


from tthAnalysis.HiggsToTauTau.safe_root import ROOT
from tthAnalysis.HiggsToTauTau.common import SmartFormatter

import argparse
import os

HISTNAME = 'EGamma_SF2D'
HISTNAME_UP = '{}_Up'.format(HISTNAME)
HISTNAME_DOWN = '{}_Down'.format(HISTNAME)

CORRFACTORS = {
  '2016' : {
    'disabled' : {
      'electron' : (1. - 0.875) / (1. - 0.796),
      'muon' : (1. - 1.028) / (1. - 0.922),
    },
    'enabled' : {
      'electron' : (1. - 0.867) / (1. - 0.790),
      'muon' : (1. - 1.026) / (1. - 0.922),
    },
  },
  '2017' : {
    'disabled' : {
      'electron' : (1. - 0.886) / (1. - 0.755),
      'muon' : (1. - 0.986) / (1. - 0.881),
    },
    'enabled' : {
      'electron' : (1. - 0.871) / (1. - 0.750),
      'muon' : (1. - 0.981) / (1. - 0.882),
    },
  },
  '2018' : {
    'disabled' : {
      'electron' : (1. - 0.929) / (1. - 0.834),
      'muon' : (1. - 0.956) / (1. - 0.915),
    },
    'enabled' : {
      'electron' : (1. - 0.918) / (1. - 0.832),
      'muon' : (1. - 0.950) / (1. - 0.915),
    },
  },
}

parser = argparse.ArgumentParser(
  formatter_class = lambda prog: SmartFormatter(prog, max_help_position = 55)
)
parser.add_argument('-i', '--input',
  type = str, dest = 'input', metavar = 'file', required = True,
  help = 'R|Original SF',
)
parser.add_argument('-o', '--output',
  type = str, dest = 'output', metavar = 'file', required = True,
  help = 'R|Output file name',
)
parser.add_argument('-e', '--era',
  type = str, dest = 'era', metavar = 'year', required = True, choices = [ '2016', '2017', '2018' ],
  help = 'R|Era',
)
parser.add_argument('-l', '--lepton',
  type = str, dest = 'lepton', metavar = 'flavor', required = True, choices = [ 'electron', 'muon' ],
  help = 'R|Lepton flavor',
)
parser.add_argument('-t', '--tight-charge',
  type = str, dest = 'tight_charge', metavar = 'option', required = True, choices = [ 'enabled', 'disabled' ],
  help = 'R|Enable or disable tight charge',
)
parser.add_argument('-v', '--verbose',
  dest = 'verbose', action = 'store_true', default = False,
  help = 'R|Enable verbose output',
)
args = parser.parse_args()
input_file = os.path.abspath(args.input)
output_file = os.path.abspath(args.output)

if not os.path.isfile(input_file):
  raise RuntimeError("No such input file: %s" % input_file)

output_dir = os.path.dirname(output_file)
if not os.path.isdir(output_dir):
  try:
    os.makedirs(output_dir)
  except OSError as err:
    raise RuntimeError("Unable to create directory for the output file %s because: %s" % (output_file, err))

correction = CORRFACTORS[args.era][args.tight_charge][args.lepton]

input_file = ROOT.TFile.Open(input_file, 'read')
sf_in = input_file.Get(HISTNAME)
sf_in.SetDirectory(0)
input_file.Close()

sf_out = sf_in.Clone()
sf_out.Reset()
sf_out.SetName(HISTNAME)
sf_out.SetTitle(HISTNAME)
sf_out.SetOption("col text")

sf_out_up = sf_out.Clone()
sf_out_up.SetName(HISTNAME_UP)
sf_out_up.SetTitle(HISTNAME_UP)

sf_out_down = sf_out.Clone()
sf_out_down.SetName(HISTNAME_DOWN)
sf_out_down.SetTitle(HISTNAME_DOWN)

nbins_x = sf_out.GetXaxis().GetNbins()
nbins_y = sf_out.GetYaxis().GetNbins()
for xidx in range(1, nbins_x + 1):
  for yidx in range(1, nbins_y + 1):
    sf_original = sf_in.GetBinContent(xidx, yidx)
    sf_new = 1. - (1. - sf_original) * correction
    sf_out.SetBinContent(xidx, yidx, sf_new)
    sf_error = abs(sf_original - sf_new) / 2
    sf_new_up = sf_new + sf_error
    sf_new_down = sf_new - sf_error
    sf_out_up.SetBinContent(xidx, yidx, sf_new_up)
    sf_out_down.SetBinContent(xidx, yidx, sf_new_down)

out = ROOT.TFile.Open(output_file, 'recreate')
sf_out.Write()
sf_out_up.Write()
sf_out_down.Write()
out.Close()
