#!/usr/bin/env python

import ROOT
import sys
import os.path
import array

# usage: extract_htxs_stage1p2.py [ output tree ] [ output ] [ input1 [ input 2 [ ... ] ] ]

assert(len(sys.argv) > 3)
tn_out = sys.argv[1]
fn_out = os.path.abspath(sys.argv[2])
fns_in = [ os.path.abspath(fn) for fn in sys.argv[3:] ]
for fn_in in fns_in:
  assert(os.path.isfile(fn_in))
  assert(fn_in != fn_out)

assert(fn_out.endswith('.root'))
assert(os.path.isdir(os.path.dirname(fn_out)))

f_out = ROOT.TFile.Open(fn_out, 'recreate')
f_out.cd()
t_out = ROOT.TTree(tn_out, tn_out)

run = array.array('I', [0])
ls = array.array('I', [0])
evt = array.array('L', [0])
htxs = array.array('i', [0])

t_out.Branch("run", run, "run/i")
t_out.Branch("luminosityBlock", ls, "luminosityBlock/i")
t_out.Branch("event", evt, "event/l")
t_out.Branch("HTXS_stage1_2_cat_pTjet30GeV", htxs, "HTXS_stage1_2_cat_pTjet30GeV/I")

n_cum = 0
for fn_in in fns_in:
  f_in = ROOT.TFile.Open(fn_in, 'read')
  t_in = f_in.Get('Events')
  n = t_in.GetEntries()
  n_cum += n
  print('Copying {} events from {}'.format(n, fn_in))

  t_in.SetBranchStatus("*", 0)
  t_in.SetBranchStatus("run", 1)
  t_in.SetBranchStatus("luminosityBlock", 1)
  t_in.SetBranchStatus("event", 1)
  t_in.SetBranchStatus("HTXS_stage1_2_cat_pTjet30GeV", 1)

  t_in.SetBranchAddress("run", run)
  t_in.SetBranchAddress("luminosityBlock", ls)
  t_in.SetBranchAddress("event", evt)
  t_in.SetBranchAddress("HTXS_stage1_2_cat_pTjet30GeV", htxs)

  for i in range(n):
    t_in.GetEntry(i)
    t_out.Fill()
  f_in.Close()

n_out = t_out.GetEntries()
assert(n_cum == n_out)
f_out.cd()
t_out.Write()
f_out.Close()
print('Saved {} events to {}'.format(n_out, fn_out))
