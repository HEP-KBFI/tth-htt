#!/usr/bin/env python

import ROOT
import sys
import os.path

FLAVORS = [ 0, 4, 5 ]
WORKING_POINTS = [ 'l', 'm' ]
BINNING_SCHEMES = [ 'coarse' ] #[ 'fine', 'coarse' ]

input_filename = sys.argv[1]
if not os.path.isfile(input_filename):
  raise RuntimeError("Missing input file: %s" % input_filename)

output_filename = '{}_ratio{}'.format(*os.path.splitext(os.path.basename(input_filename)))
if os.path.isfile(output_filename):
  raise RuntimeError("Output file already exists: %s" % output_filename)

input_file = ROOT.TFile.Open(input_filename, 'read')
output_file = ROOT.TFile.Open(output_filename, 'recreate')

samples = []
for key in input_file.GetListOfKeys():
  key_name = key.GetName()
  sample = '_'.join(key_name.split('_')[3:])
  if sample in samples:
    continue
  samples.append(sample)

  for binning in BINNING_SCHEMES:
    for flavor_int in FLAVORS:
      flavor = str(flavor_int)

      hn_total = '_'.join([ binning, flavor, 'total', sample ])
      h_total = input_file.Get(hn_total)
      nxbins = h_total.GetXaxis().GetNbins()
      nybins = h_total.GetYaxis().GetNbins()

      for wp in WORKING_POINTS:
        hn_wp = '_'.join([ binning, flavor, wp, sample ])
        h_wp = input_file.Get(hn_wp)

        ratio_title = '_'.join([ binning, flavor, wp, 'ratio', sample ])
        hout = h_total.Clone(ratio_title)
        hout.Reset()
        hout.SetTitle(ratio_title)
        hout.SetStats(0)

        if binning == 'fine':
          hout.SetOption('col')
        for ix in range(1, nxbins + 1):
          for iy in range(1, nybins + 1):
            num = h_wp.GetBinContent(ix, iy)
            denom = h_total.GetBinContent(ix, iy)
            if denom == 0:
              assert(num == 0.)
              hout.SetBinContent(ix, iy, 0.)
            else:
              hout.SetBinContent(ix, iy, num / denom)
        output_file.cd()
        hout.Write()

input_file.Close()
output_file.Close()
