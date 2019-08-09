#!/usr/bin/env python

#Load modules here
from array import array
from ROOT import *
from math import sqrt, sin, cos, tan, exp

if 0>1 :
    source="/home/acaan/ttHAnalysis/2016/2017Dec05-VHbb/datacards/1l_2tau/prepareDatacards_1l_2tau_mvaOutput_1l_2tau_ttbar_"
    originalBinning=500
    nbin=[50,25,10,5,1]
    files=["Old","OldVar","OldVarHTT","HTTWithKinFit_MVAonly","HTTWithKinFit","HTTLepID"] #

source="/home/acaan/ttHAnalysis/2016/2017Dec21-limFirstOpt/datacards/2lss_1tau/prepareDatacards_2lss_1tau_sumSS_"
originalBinning=600
nbin=[20,15,12,8,6,5,4,3]
files=["mvaOutput_2lss_oldVar_tt","mvaOutput_2lss_oldVar_ttV",
        "mvaOutput_2lss_HTT_tt",
        "mvaOutput_2lss_noHTT_tt","mvaOutput_2lss_noHTT_ttV"]

for fileN in files :
    file = TFile(source+fileN+".root");
    file.cd()
    file2 = open(source+fileN+"_rebin.log","w")
    file2.write("nbins Integral Err Content Err/Cont (all in lastbin)\n")
    for nbins in nbin :
        fileOut  = TFile(source+fileN+"_"+str(nbins)+"bins.root", "recreate");
        h2 = TH1F()
        for keyO in file.GetListOfKeys() :
           obj =  keyO.ReadObj()
           if type(obj) is not TH1F : continue #isinstance(obj, TH1) : continue
           h2 = obj;
           factor=1.
           if  not h2.GetSumw2N() : h2.Sumw2()
           #if "OldVar" in fileN : factor=2.
           h2.Rebin(int(originalBinning/(nbins*factor)))
           #if "OldVar" in fileN :
           #    h2.GetXaxis().SetLimits(0.,1.)
           #    h2.GetXaxis().SetRangeUser(0.,1.)
           h2.Write();
           if keyO.GetName() == "data_fakes" :
               ratio=100000
               if h2.GetBinContent(h2.GetNbinsX()) >0 : ratio=h2.GetBinError(h2.GetNbinsX())/h2.GetBinContent(h2.GetNbinsX())
               file2.write(str(nbins)+" "+str(h2.Integral())+" "+str(h2.GetBinContent(h2.GetNbinsX()))+" "+str(h2.GetBinError(h2.GetNbinsX()))+" "+str(ratio)+ "\n")
               print keyO.GetName()+" done "+fileN+" with nbins = "+str(nbins)+" "+str(h2.Integral())+" "+str(h2.GetBinContent(h2.GetNbinsX()))+" "+str(h2.GetBinError(h2.GetNbinsX()))+" "+str(ratio)
        fileOut.Write()
    file2.close()
    print "\n"
