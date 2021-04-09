#!/usr/bin/env python

# This script is equivalent to the small test progrem implemented in bin/testHHWeightInterfaceNLO.cc of this repository,
# and is based on Fabio's example implemented in $CMSSW_BASE/src/HHStatAnalysis/AnalyticalModels/python/usage_example.py
# In order to run this script, make sure you've checked out Fabio's fork:
#
# cd $CMSSW_BASE/src/HHStatAnalysis
# git remote add fabio https://github.com/fabio-mon/HHStatAnalysis.git
# git fetch fabio
# git checkout NLO_model
# scram b

from HHStatAnalysis.AnalyticalModels.NonResonantModelNLO import NonResonantModelNLO

import ROOT
import os

MHH_BINNING = [
  250, 270, 290, 310, 330, 350, 370, 390, 410, 430, 450, 470, 490, 510, 530, 550, 570, 590, 610, 630, 650, 670, 700,
  750, 800, 850, 900, 950, 1000, 1100, 1200, 1300, 1400, 1500, 1750, 2000, 5000
]
COST_BINNING = [ 0.0, 0.4, 0.6, 0.8, 1.0 ]

cmssw_base = os.path.join(os.environ['CMSSW_BASE'], 'src')

model = NonResonantModelNLO()
model.ReadCoefficients(os.path.join(cmssw_base, 'tthAnalysis/HiggsToTauTau/data/HHWeightInterfaceNLO/pm_pw_NLO-Ais-13TeV_V2.txt'))

inputevfile = ROOT.TFile(os.path.join(cmssw_base, 'hhAnalysis/multilepton/data/denom_2017_nlo.root'))
histo_Nev = inputevfile.Get("signal_ggf_nonresonant_hh_wwww")
histo_Nev.SetDirectory(0)
inputevfile.Close()
Nevtot = histo_Nev.Integral()

iBM = 0 # stands for SM
BMcouplings = model.getBenchmark(iBM)
kl, kt, c2, cg, c2g = BMcouplings[0], BMcouplings[1], BMcouplings[2], BMcouplings[3], BMcouplings[4]

for mhh_idx in range(len(MHH_BINNING) - 1):
  event_mHH = (MHH_BINNING[mhh_idx] + MHH_BINNING[mhh_idx + 1]) / 2.
  line = 'mHH = [{:>4}, {:>4}]: '.format(MHH_BINNING[mhh_idx], MHH_BINNING[mhh_idx + 1])
  for cost_idx in range(len(COST_BINNING) - 1):
    event_costhetaHH = (COST_BINNING[cost_idx] + COST_BINNING[cost_idx + 1]) / 2.
    XStot = model.getTotalXS(kl, kt, c2, cg, c2g)
    Nev = histo_Nev.GetBinContent(histo_Nev.FindBin(event_mHH, event_costhetaHH))
    XS = model.getDifferentialXS2D(event_mHH, event_costhetaHH, kl, kt, c2, cg, c2g)
    Noutputev = XS * model.getmHHbinwidth(event_mHH) * model.getcosthetabinwidth(event_costhetaHH)
    weight = Noutputev / Nev * Nevtot / XStot
    line += "cosTheta = [{:.1f}, {:.1f}] => {:.6f}".format(COST_BINNING[cost_idx], COST_BINNING[cost_idx + 1], weight)
    if cost_idx < len(COST_BINNING) - 2:
      line += "; "
  print(line)
