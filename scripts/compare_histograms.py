#!/usr/bin/env python

import ROOT
import os.path
import argparse

def read_hists(input_fn, dirname):
  if not os.path.isfile(input_fn):
    raise RuntimeError("No such file: %s" % input_fn)
  fptr = ROOT.TFile.Open(input_fn, 'read')
  assert(fptr)
  dirptr = fptr.Get(dirname) if dirname else fptr
  assert(dirptr)
  hists = {}
  hist_keys = [ key.GetName() for key in dirptr.GetListOfKeys() ]
  for hist_key in hist_keys:
    hist = dirptr.Get(hist_key)
    content = [ hist.GetBinContent(idx) for idx in range(1, hist.GetXaxis().GetNbins() + 1) ]
    integral = hist.Integral()
    hists[hist_key] = { 'content' : content, 'integral' : integral }
  fptr.Close()
  return hists

if __name__ == '__main__':
  parser = argparse.ArgumentParser()
  parser.add_argument('-i', '--in1', type = str, dest = 'input1', metavar = 'path', help = '1st input', required = True)
  parser.add_argument('-j', '--in2', type = str, dest = 'input2', metavar = 'path', help = '2nd input', required = True)
  parser.add_argument('-d', '--dname1', type = str, dest = 'dir_name1', metavar = 'str', help = 'Dir name of the 1st input', default = '', required = False)
  parser.add_argument('-D', '--dname2', type = str, dest = 'dir_name2', metavar = 'str', help = 'Dir name of the 2nd input', default = '', required = False)
  args = parser.parse_args()

  input1 = args.input1
  input2 = args.input2
  hists1 = read_hists(input1, args.dir_name1)
  hists2 = read_hists(input2, args.dir_name2)

  hists1_keyset = set(hists1.keys())
  hists2_keyset = set(hists2.keys())
  common_keyset = hists1_keyset & hists2_keyset
  missing_from2 = list(sorted(hists1_keyset - common_keyset))
  missing_from1 = list(sorted(hists2_keyset - common_keyset))

  print("Comparing {} to {}".format(input1, input2))
  if missing_from1:
    print("  WARNING: first input missing histograms: %s" % (', '.join(missing_from1)))
  if missing_from2:
    print("  WARNING: second input missing histograms: %s" % (', '.join(missing_from2)))
  if not common_keyset:
    raise RuntimeError("Nothing to compare")

  for common_key in sorted(common_keyset):
    hist1 = hists1[common_key]
    hist2 = hists2[common_key]
    integral_diff = hist1['integral'] - hist2['integral']
    if abs(integral_diff) > 1e-4:
      out_str = '  {} INT diff {:.3e} ({:.3e} vs {:.3e})'.format(
        common_key, integral_diff, hist1['integral'], hist2['integral']
      )
      nof_bins1 = len(hist1['content'])
      nof_bins2 = len(hist2['content'])
      assert(nof_bins1 == nof_bins2)
      content_diff = [ hist1['content'][idx] - hist2['content'][idx] for idx in range(nof_bins1) ]
      content_diff_str = ', '.join([ 'bin #{} -> {:.3e} ({:.3e} vs {:.3e})'.format(
          idx, val, hist1['content'][idx], hist2['content'][idx]
        ) for idx, val in enumerate(content_diff) if abs(val) > 1e-4 ])
      if content_diff_str:
        out_str += ' {} (total # bins: {})'.format(content_diff_str, nof_bins1)
      print(out_str)
