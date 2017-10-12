import sys
import sklearn_to_tmva
import sklearn
from sklearn import datasets
from sklearn.ensemble import GradientBoostingClassifier
from sklearn.cross_validation import train_test_split
import pandas
import math
import numpy as np
#import matplotlib.pyplot as plt
import pickle

def trainVars():
        return [
		#'nJet',
		'mindr_lep1_jet',
		'mindr_lep2_jet',
		'avg_dr_jet',
		#'lep1_pt',
		#'lep1_abs_eta',
		#'lep2_pt',
		#'lep2_abs_eta',
		'max_lep_eta',
		'lep1_conePt',
		'lep2_conePt',
		#'mindr_tau_jet',
		#'ptmiss',
		'mT_lep1',
		#'mT_lep2',
		#'htmiss',
		'dr_leps',
		#'tau_pt',
		#'tau_abs_eta',
		#'dr_lep1_tau',
		#'dr_lep2_tau',
		'mTauTauVis1',
		'mTauTauVis2',
		'memOutput_LR'
		#'memOutput_ttZ_LR',
		#'memOutput_ttZ_Zll_LR'
		]

data_signal = pandas.read_csv("2lss_1tau_signal_fastsim_28Mar2017.csv")
data_ttw = pandas.read_csv("2lss_1tau_TTW_fastsim_28Mar2017.csv")
data_ttz = pandas.read_csv("2lss_1tau_TTZ_fastsim_28Mar2017.csv")
data_ttv = pandas.concat([data_ttw, data_ttz])
nS = len(data_signal)
nB = len(data_ttv)
print "length of sig, bkg: ", nS, nB
data = pandas.concat([data_signal, data_ttv])
print "length of sig+bkg: ", len(data)
targets = np.concatenate((np.ones(nS),np.zeros(nB)))
data_train = np.array(data[trainVars()])
#data_weights = np.array(data['evtWeight'])
data["totalWeight"] = data.evtWeight * data.lep1_frWeight * data.lep2_frWeight * data.tau_frWeight
data_weights = np.array(data['totalWeight'])
#data["mva1"] = 0.0
#data["mva2"] = 0.0

cls = GradientBoostingClassifier(
    max_depth=3,
    learning_rate=0.01,
    n_estimators=100,
    verbose=True,
    min_samples_leaf=10,
    min_samples_split=10
)
d_train, d_test, t_train, t_test, w_train, w_test = train_test_split(data_train, targets, data_weights, test_size=0.2, random_state=7)
#cls.fit(data_train, targets)
cls.fit(d_train, t_train, w_train)

sklearn_to_tmva.gbr_to_tmva(
    cls,
    data[trainVars()],
    "TMVABDT_2lss_1tau_ttV_maxDepth3_10Var_frWt_wMEMall.xml",
    coef=2
)

import ROOT, array
from ROOT import TFile, TH1F, TGraph, TCanvas, TLegend

fout = TFile("2lss_1tau_ttV_performance_maxDepth3_10Var_frWt_wMEMall.root", "RECREATE")
c1 = TCanvas()
c1.SetFillColor(10)
c1.SetBorderSize(2)
c1.SetLeftMargin(0.12)
c1.SetBottomMargin(0.12)
c1.SetRightMargin(0.05)
c1.SetLogy()

histogram_base = TH1F("histogram_base", "", 100, 0., 1.)
histogram_base.SetTitle("")
histogram_base.SetStats(False)
histogram_base.SetMinimum(0.001)
histogram_base.SetMaximum(10.)
histogram_base.GetXaxis().SetTitle("Signal Eff.")
histogram_base.GetYaxis().SetTitle("Background Eff.")
histogram_base.Draw("hist")

x_train = array.array("f", [0])
y_train = array.array("f", [0])
x_test = array.array("f", [0])
y_test = array.array("f", [0])

effs = np.linspace(0, 1, 50)

train_scores = cls.decision_function(d_train)
fpr_tr, tpr_tr, tresholds_tr = sklearn.metrics.roc_curve(t_train, train_scores, pos_label=None, sample_weight=w_train)
for eff in effs:
	#print 'Fake rate at signal eff', eff, fpr_tr[np.argmax(tpr_tr>eff)]
	x_train.append(eff)
	y_train.append(fpr_tr[np.argmax(tpr_tr>eff)])
	
print 'from test sample'
test_scores = cls.decision_function(d_test)
fpr_te, tpr_te, tresholds_te = sklearn.metrics.roc_curve(t_test, test_scores, pos_label=None, sample_weight=w_test)
for eff in effs:
	#print 'Fake rate at signal eff', eff, fpr_te[np.argmax(tpr_te>eff)]
	x_test.append(eff)
	y_test.append(fpr_te[np.argmax(tpr_te>eff)])

roc_train = TGraph(50, x_train, y_train)
roc_train.SetName("roc_train")
roc_train.SetTitle("roc_train")
roc_test = TGraph(50, x_test, y_test)
roc_test.SetName("roc_test")
roc_test.SetTitle("roc_test")

roc_train.SetLineColor(2)
roc_test.SetLineColor(4)
roc_train.Write()
roc_test.Write()
	
leg = TLegend(0.2, 0.65, 0.5, 0.9)
leg.SetBorderSize(0)
leg.SetFillColor(10)
leg.SetLineColor(0)
leg.SetFillStyle(0)
leg.SetTextSize(0.04)
leg.SetTextFont(42)

leg.AddEntry(roc_train, "training", "l")
leg.AddEntry(roc_test, "testing", "l")

roc_train.Draw("Lsame")
roc_test.Draw("Lsame")
leg.Draw()

c1.SaveAs("roc_overtraining_2lss_1tau_ttV_maxDepth3_10Var_frWt_wMEMall.pdf")
fout.Write()
fout.Close()

#print variable ranking
#print cls.feature_importances_
#
#varList = trainVars()
#for i, imp in enumerate(cls.feature_importances_):
#	print imp, varList[i] if i<len(varList) else 'N/A'
print "Variable Ranking"
varList = trainVars()
importances = cls.feature_importances_
indices = np.argsort(importances)[::-1]
for f in range(len(varList)):
	print format("%d" %(f+1), '>5'), format(varList[indices[f]], '>20'), format("%f" %(importances[indices[f]]), '>20')

#save the training to file for later use
filename = 'sklearn_2lss_1tau_ttV_maxDepth3_10Var_frWt_wMEMall.pkl'
pickle.dump(cls, open(filename, 'wb'))
 
