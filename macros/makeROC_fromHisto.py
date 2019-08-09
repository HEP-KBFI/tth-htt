#!/usr/bin/env python

#Load modules here
from array import array
from ROOT import *
from math import sqrt, sin, cos, tan, exp

#Set plotting style
gStyle.SetOptStat(0)
gStyle.SetOptFit(0)

SavePlots = True
verbose = True
Nverbose = 10
veryverbose = False

# Calculate ROC curve from two histograms:
def CalcROC(histSig, histBkg) :

    # Loop over histogram bins and calculate vectors of efficiencies:
    # ---------------------------------------------------------------
    effSig = array( "f" )
    effBkg = array( "f" )

    # Check that the two histograms have the same number of bins and same range:
    if (histSig.GetNbinsX() == histBkg.GetNbinsX()) :
        if ( abs(histSig.GetXaxis().GetXmax() - histBkg.GetXaxis().GetXmax()) < 0.0001 and
             abs(histSig.GetXaxis().GetXmin() - histBkg.GetXaxis().GetXmin()) < 0.0001) :
            Nbins = histSig.GetNbinsX()

            # Get integral (including underflow and overflow):
            integralSig = 0.0
            integralBkg = 0.0
            for ibin in range(Nbins+2) :
                integralSig += histSig.GetBinContent(ibin)
                integralBkg += histBkg.GetBinContent(ibin)

            # Integrate each bin, and add result to ROC curve (contained in effSig and effBkg):
            effSig.append(0.0)
            effBkg.append(0.0)
            sumSig = 0.0
            sumBkg = 0.0
            for ibin in range (Nbins+1, 0, -1) :
                sumSig += histSig.GetBinContent(ibin)
                sumBkg += histBkg.GetBinContent(ibin)
                effSig.append(sumSig/integralSig)
                effBkg.append(sumBkg/integralBkg)
                if (veryverbose) :
                    print "  bin %3d:   effSig = %5.3f   effBkg = %5.3f"%(ibin, effSig[-1], effBkg[-1])

            # Make ROC curve in a TGraph of the two arrays, and return this:
            graphROC = TGraph(len(effSig), effSig, effBkg)
            return graphROC

        else :
            print "ERROR: Signal and Background histograms have different ranges!"
            return None

    else :
        print "ERROR: Signal and Background histograms have different binning!"
        return None

    return None

#file=TFile("/home/acaan/ttHAnalysis/2016/2017Nov30-VHbb/datacards/1l_2tau/prepareDatacards_1l_2tau_mvaOutput_1l_2tau_ttbar_Old.root")
##print file.GetListOfKeys().Print()

file=TFile("/hdfs/local/acaan/ttHAnalysis/2016/2017Dec05-VHbb/histograms/1l_2tau/histograms_harvested_stage2_1l_2tau_Tight_OS.root")
file.cd('1l_2tau_OS_Tight/sel/evt/signal')
signal_mvaOutput_1l_2tau_ttbar_HTTWithKinFit_MVAonly = file.Get('1l_2tau_OS_Tight/sel/evt/signal/mvaOutput_1l_2tau_ttbar_HTTWithKinFit_MVAonly')
signal_mvaOutput_1l_2tau_ttbar_Old = file.Get('1l_2tau_OS_Tight/sel/evt/signal/mvaOutput_1l_2tau_ttbar_Old')
signal_mvaOutput_1l_2tau_ttbar_OldVar = file.Get('1l_2tau_OS_Tight/sel/evt/signal/mvaOutput_1l_2tau_ttbar_OldVar')
signal_mvaOutput_1l_2tau_ttbar_OldVarHTT = file.Get('1l_2tau_OS_Tight/sel/evt/signal/mvaOutput_1l_2tau_ttbar_OldVarHTT')
signal_mvaOutput_1l_2tau_ttbar_HTTWithKinFit = file.Get('1l_2tau_OS_Tight/sel/evt/signal/mvaOutput_1l_2tau_ttbar_HTTWithKinFit')
signal_mvaOutput_1l_2tau_ttbar_HTTLepID = file.Get('1l_2tau_OS_Tight/sel/evt/signal/mvaOutput_1l_2tau_ttbar_HTTLepID')

#file.cd()
file.cd('1l_2tau_OS_Tight/sel/evt/data_fakes')
data_fakes_mvaOutput_1l_2tau_ttbar_HTTWithKinFit_MVAonly  =  file.Get('1l_2tau_OS_Tight/sel/evt/data_fakes/mvaOutput_1l_2tau_ttbar_HTTWithKinFit_MVAonly')
data_fakes_mvaOutput_1l_2tau_ttbar_Old  =  file.Get('1l_2tau_OS_Tight/sel/evt/data_fakes/mvaOutput_1l_2tau_ttbar_Old')
data_fakes_mvaOutput_1l_2tau_ttbar_OldVar  =  file.Get('1l_2tau_OS_Tight/sel/evt/data_fakes/mvaOutput_1l_2tau_ttbar_OldVar')
data_fakes_mvaOutput_1l_2tau_ttbar_OldVarHTT  =  file.Get('1l_2tau_OS_Tight/sel/evt/data_fakes/mvaOutput_1l_2tau_ttbar_OldVarHTT')
data_fakes_mvaOutput_1l_2tau_ttbar_HTTWithKinFit  =  file.Get('1l_2tau_OS_Tight/sel/evt/data_fakes/mvaOutput_1l_2tau_ttbar_HTTWithKinFit')
data_fakes_mvaOutput_1l_2tau_ttbar_HTTLepID  =  file.Get('1l_2tau_OS_Tight/sel/evt/data_fakes/mvaOutput_1l_2tau_ttbar_HTTLepID')
c1 = TCanvas( 'c1', '@ Analysis level ',  400, 400 )


xl1=.45
yl1=0.15
xl2=xl1+.5
yl2=yl1+.2;
leg = TLegend(xl1,yl1,xl2,yl2);
leg.SetHeader("@ Analysis level")
#
roc=CalcROC(data_fakes_mvaOutput_1l_2tau_ttbar_HTTWithKinFit_MVAonly,signal_mvaOutput_1l_2tau_ttbar_HTTWithKinFit_MVAonly)
roc.SetLineColor(kViolet)
roc.SetLineWidth(2)
leg.AddEntry(roc,"HTTWithKinFit_MVAonly","l") # str(1-roc.Integral())
roc.Draw()

roc1=CalcROC(data_fakes_mvaOutput_1l_2tau_ttbar_HTTWithKinFit,signal_mvaOutput_1l_2tau_ttbar_HTTWithKinFit)
roc1.SetLineColor(kMagenta+4)
roc1.SetLineWidth(2)
leg.AddEntry(roc1,"HTTWithKinFit","l")
roc1.Draw("same")

roc2=CalcROC(data_fakes_mvaOutput_1l_2tau_ttbar_HTTLepID,signal_mvaOutput_1l_2tau_ttbar_HTTLepID)
roc2.SetLineColor(kCyan)
roc2.SetLineWidth(2)
leg.AddEntry(roc2,"HTT + LepID ","l")
roc2.Draw("same")

roc_Old=CalcROC(data_fakes_mvaOutput_1l_2tau_ttbar_Old,signal_mvaOutput_1l_2tau_ttbar_Old)
roc_Old.SetLineColor(kGreen)
roc_Old.SetLineWidth(2)
leg.AddEntry(roc_Old,"Old training","l")
roc_Old.Draw("same")

roc_OldVar=CalcROC(data_fakes_mvaOutput_1l_2tau_ttbar_OldVar,signal_mvaOutput_1l_2tau_ttbar_OldVar)
roc_OldVar.SetLineColor(kRed)
roc_OldVar.SetLineWidth(2)
leg.AddEntry(roc_OldVar,"Old variables","l")
roc_OldVar.Draw("same")

leg.Draw("same")
c1.SaveAs('test_roc.pdf')
#_file0->cd("1l_2tau_OS_Tight/sel/signal/evt")
#mvaOutput_1l_2tau_ttbar_HTTWithKinFit_MVAonly
#mvaOutput_1l_2tau_ttbar_Old
