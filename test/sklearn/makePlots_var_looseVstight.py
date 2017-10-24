import sys
import pandas
import math
import numpy as np
import root_numpy
import ROOT, array
from ROOT import TFile, TH1F, TGraph, TCanvas, TLegend, TString
print sys.argv
process =  sys.argv[1] 

if process=="signal":
	data = pandas.read_csv("3l_1tau_signal_07Apr2017.csv")   
	#data_tight = pandas.read_csv("3l_1tau_signal_tauTight_07Apr2017.csv")
	#data_tight = pandas.read_csv("3l_1tau_signal_tight_07Apr2017.csv")
	data_tight = pandas.read_csv("3l_1tau_signal_tauGenMatch_07Apr2017.csv")
elif process=="TT":
	data = pandas.read_csv("3l_1tau_TT_07Apr2017.csv")
	#data_tight = pandas.read_csv("3l_1tau_TT_tight_07Apr2017.csv")
	#data_tight = pandas.read_csv("3l_1tau_TT_tauTight_07Apr2017.csv")
	data_tight = pandas.read_csv("3l_1tau_TT_tauGenMatch_07Apr2017.csv")
elif process=="TTW":
        data = pandas.read_csv("3l_1tau_TTW_07Apr2017.csv")
        #data_tight = pandas.read_csv("3l_1tau_TTW_tight_07Apr2017.csv")
	#data_tight = pandas.read_csv("3l_1tau_TTW_tauTight_07Apr2017.csv")
	data_tight = pandas.read_csv("3l_1tau_TTW_tauGenMatch_07Apr2017.csv")
elif process=="TTZ":
        data = pandas.read_csv("3l_1tau_TTZ_07Apr2017.csv")
        #data_tight = pandas.read_csv("3l_1tau_TTZ_tight_07Apr2017.csv")
	#data_tight = pandas.read_csv("3l_1tau_TTZ_tauTight_07Apr2017.csv")
	data_tight = pandas.read_csv("3l_1tau_TTZ_tauGenMatch_07Apr2017.csv")

nAll = len(data)
nTight = len(data_tight)
print "length of loose, tight: ", nAll, nTight

def trainVars():
        return [
		#'nJet',
                #'mindr_lep1_jet',
                #'mindr_lep2_jet',
	        #'mindr_lep3_jet',
                #'avg_dr_jet',
                ###'lep1_pt',
                ##'lep1_abs_eta',
                ###'lep2_pt',
                ##'lep2_abs_eta',
                ##'max_lep_eta',
                #'lep1_conePt',
                #'lep2_conePt',
		#'lep3_conePt',
                #'mindr_tau_jet',
                ##'ptmiss',
                #'mT_lep1',
                #'mT_lep2',
	        #'mT_lep3',
                ##'htmiss',
                #'dr_leps',
                'tau_pt',
                #'tau_abs_eta',
                #'dr_lep1_tau',
                #'dr_lep2_tau',
		#'dr_lep3_tau',
                #'mTauTauVis1',
                #'mTauTauVis2',
		]

def makePlot(variable):
	data_var = np.array(data[variable])
	data["totalWeight"] = data.evtWeight * data.lep1_frWeight * data.lep2_frWeight * data.lep3_frWeight * data.tau_frWeight
	data_weights = np.array(data['totalWeight'])
	
	data_tight_var = np.array(data_tight[variable])
        #data_tight_weights = np.array(data_tight['evtWeight'])
	data_tight["totalWeight"] = data_tight.evtWeight * data_tight.lep1_frWeight * data_tight.lep2_frWeight * data_tight.lep3_frWeight * data_tight.tau_frWeight
        data_tight_weights = np.array(data_tight['totalWeight'])

	c1 = TCanvas()
	c1.SetFillColor(10)
	c1.SetBorderSize(2)
	c1.SetLeftMargin(0.12)
	c1.SetBottomMargin(0.12)
	c1.SetRightMargin(0.05)
	c1.SetLogy()

	histogram_base = TH1F("histogram_base", "", 100, np.nanmin(data_var), np.nanmax(data_var))
	histogram_base.SetTitle("")
	histogram_base.SetStats(False)
	histogram_base.SetMinimum(0.001)
	histogram_base.SetMaximum(10.0)
	histogram_base.GetXaxis().SetTitle(variable)
	histogram_base.GetYaxis().SetTitle("Events")
	histogram_base.Draw("hist")

	hist_loose = TH1F("hist_loose", "", 100, np.nanmin(data_var), np.nanmax(data_var))
	hist_tight = TH1F("hist_tight", "", 100, np.nanmin(data_var), np.nanmax(data_var))
	root_numpy.fill_hist(hist_loose, data_var,weights=data_weights)
	root_numpy.fill_hist(hist_tight, data_tight_var,weights=data_tight_weights)
	hist_loose.SetLineColor(2)
	hist_tight.SetLineColor(4)
	hist_loose.SetFillColor(2)
	hist_tight.SetFillColor(4)
	hist_loose.SetFillStyle(3004)
	hist_tight.SetFillStyle(3005)

	leg = TLegend(0.2, 0.65, 0.5, 0.9)
	leg.SetBorderSize(0)
	leg.SetFillColor(10)
	leg.SetLineColor(0)
	leg.SetFillStyle(0)
	leg.SetTextSize(0.04)
	leg.SetTextFont(42)

	leg.AddEntry(hist_loose, "l-loose, tau-vvloose", "F")
	leg.AddEntry(hist_tight, "l-loose,, tau-vvloose genMatch", "F")
	
	hist_loose.DrawNormalized("histsame")
	hist_tight.DrawNormalized("histsame")
	leg.Draw()

	#c1.SaveAs("plots/"+variable+"_"+process+"_loose_vs_tight.png")
	#c1.SaveAs("plots/"+variable+"_"+process+"_loose_vs_tauTight.png")
	c1.SaveAs("plots/"+variable+"_"+process+"_loose_vs_tau-vvloose-GenMatch.png")
	
for var in trainVars():
	makePlot(var)

