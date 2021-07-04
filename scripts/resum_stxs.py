#!/usr/bin/env python

import ROOT
import sys
import os
import collections

assert(len(sys.argv) == 2)
fn = sys.argv[1]
assert(fn.endswith(('_stxsOnly.root', '_THUstxsOnly.root')))
assert(os.path.isfile(fn))
print("Resumming: %s" % fn)

f = ROOT.TFile.Open(fn, 'read')
ks = [ k.GetName() for k in f.GetListOfKeys() ]
hists = collections.OrderedDict()

for k in ks:
  hname = k
  syst = ''
  syst_idx = hname.find('CMS_ttHl')
  if syst_idx > 0:
    syst = hname[syst_idx:]
    hname = hname[:syst_idx - 1]

  tau_match = ''
  if hname.endswith(('gentau', 'faketau')):
    hname_split = hname.split('_')
    tau_match = hname_split[-1]
    hname = '_'.join(hname_split[:-1])
  dm = ''
  if hname.endswith(('hzz', 'hww', 'htt', 'hzg', 'hmm')):
    hname_split = hname.split('_')
    dm = hname_split[-1]
    hname = '_'.join(hname_split[:-1])
  
  hname_split = hname.split('_')
  proc = hname_split[0]
  assert(proc in [ 'ttH', 'WH', 'ZH', 'qqH', 'ggH' ])
  stxs_bin = '_'.join(hname_split[1:])
  
  hname_new = proc
  if dm:
    hname_new += '_{}'.format(dm)
  if tau_match:
    hname_new += '_{}'.format(tau_match)
  if syst:
    hname_new += '_{}'.format(syst)
  
  hist = f.Get(k)
  if hname_new not in hists:
    hists[hname_new] = hist.Clone()
    hists[hname_new].Reset()
    hists[hname_new].SetName(hname_new)
    hists[hname_new].SetTitle(hname_new)
    hists[hname_new].SetDirectory(0)
  hists[hname_new].Add(hist)

f.Close()

ofn = fn.replace('stxsOnly.root', 'stxsResummed.root')
of = ROOT.TFile.Open(ofn, 'recreate')
of.cd()
for hname in sorted(list(hists.keys())):
  hists[hname].Write()
of.Close()
print(" => wrote %s" % ofn)
