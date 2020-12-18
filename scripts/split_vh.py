#!/usr/bin/env python

from tthAnalysis.HiggsToTauTau.safe_root import ROOT
from tthAnalysis.HiggsToTauTau.common import SmartFormatter
from tthAnalysis.HiggsToTauTau.hdfs import hdfs

import os.path
import array
import argparse

parser = argparse.ArgumentParser(formatter_class = lambda prog: SmartFormatter(prog, max_help_position = 45))
group = parser.add_mutually_exclusive_group(required = True)
parser.add_argument('-i', '--input', metavar = 'file', required = True, type = str, default = '',
                    help = 'R|Input Ntuple')
group.add_argument ('-z', '--select-zh', dest = 'select_zh', action = 'store_true', default = False,
                    help = 'R|Select ZH events')
group.add_argument ('-w', '--select-wh', dest = 'select_wh', action = 'store_true', default = False,
                    help = 'R|Select WH events')
args = parser.parse_args()

input_fn = args.input
select_wh = args.select_wh
select_zh = args.select_zh

assert(hdfs.isfile(input_fn))

input_f = ROOT.TFile.Open(input_fn, 'read')
tree = input_f.Get('Events')

max_ngen = 512
ngen = array.array('I', [0])
gen_pdgId = array.array('i', [0] * max_ngen)
gen_status = array.array('I', [0] * max_ngen)
gen_statusFlag = array.array('I', [0] * max_ngen)

tree.SetBranchAddress('nGenPart', ngen)
tree.SetBranchAddress('GenPart_pdgId', gen_pdgId)
tree.SetBranchAddress('GenPart_status', gen_status)
tree.SetBranchAddress('GenPart_statusFlags', gen_statusFlag)

output_fn = os.path.basename(input_fn)
output_f = ROOT.TFile.Open(output_fn, 'recreate')
tree_out = tree.CloneTree(0)

ntree = tree.GetEntries()
for idx in range(ntree):
  tree.GetEntry(idx)
  found_wh, found_zh = False, False
  for jdx in range(ngen[0]):
    if (gen_statusFlag[jdx] & 4481) == 4481 and gen_status[jdx] == 22:
      abs_pdgId = abs(gen_pdgId[jdx])
      found_zh |= abs_pdgId == 23
      found_wh |= abs_pdgId == 24
      if found_zh or found_wh:
        break
  assert(found_wh != found_zh)
  if (found_wh and select_wh) or (found_zh and select_zh):
    tree_out.Fill()

tree_out.AutoSave()
input_f.Close()
