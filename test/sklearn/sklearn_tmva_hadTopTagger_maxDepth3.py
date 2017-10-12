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

def clean_dataset(df):
    assert isinstance(df, pandas.DataFrame), "df needs to be a pd.DataFrame"
    df.dropna(inplace=True)
    indices_to_keep = ~df.isin([np.nan, np.inf, -np.inf]).any(1)
    return df[indices_to_keep].astype(np.float64)

def trainVars():
        return [
		'CSV_Wj1',
		#'CSV_Wj2',
		'CSV_b',
		#'alphaKinFit',
		'dR_Wj1Wj2',
		'dR_bW',
		#'dR_bWj1',
		#'dR_bWj2',
		##'logPErrKinFit',
		##'logPKinFit',
		'm_Wj1Wj2',
		#'m_Wj1Wj2_div_m_bWj1Wj2',
		#'m_bWj1',
		#'m_bWj1Wj2',
		#'m_bWj2',
		#'max_dR_div_expRjet',
		'nllKinFit',
		#'pT_Wj1',
		#'pT_Wj1Wj2',
		'pT_Wj2',
		#'pT_b',
		'pT_bWj1Wj2',
		#'qg_Wj1',
		'qg_Wj2',
		#'qg_b',
		#'statusKinFit'
		]

data_signal1 = pandas.read_csv("/scratch/arun/mvaTraining/22Sep2017/hadTopTagger_ttH_09Oct2017_sig.csv")
data_signal2 = pandas.read_csv("/scratch/arun/mvaTraining/22Sep2017/hadTopTagger_TT_09Oct2017_sig_p3.csv")
data_signal3 = pandas.read_csv("/scratch/arun/mvaTraining/22Sep2017/hadTopTagger_TTW_09Oct2017_sig.csv")
data_signal4 = pandas.read_csv("/scratch/arun/mvaTraining/22Sep2017/hadTopTagger_TTZ_09Oct2017_sig.csv")

data_bkg1 = pandas.read_csv("/scratch/arun/mvaTraining/22Sep2017/hadTopTagger_ttH_09Oct2017_bkg_p75.csv")
data_bkg2 = pandas.read_csv("/scratch/arun/mvaTraining/22Sep2017/hadTopTagger_TT_09Oct2017_bkg_p75.csv")
data_bkg3 = pandas.read_csv("/scratch/arun/mvaTraining/22Sep2017/hadTopTagger_TTW_09Oct2017_bkg_p75.csv")
data_bkg4 = pandas.read_csv("/scratch/arun/mvaTraining/22Sep2017/hadTopTagger_TTZ_09Oct2017_bkg_p75.csv")

data_signal_temp = pandas.concat([data_signal1, data_signal2, data_signal3, data_signal4])
data_signal = clean_dataset(data_signal_temp)
data_bkg_temp = pandas.concat([data_bkg1, data_bkg2, data_bkg3, data_bkg4])
data_bkg = clean_dataset(data_bkg_temp)

nS = len(data_signal)
nB = len(data_bkg)
print "length of sig, bkg: ", nS, nB
data = pandas.concat([data_signal, data_bkg])
print "length of sig+bkg: ", len(data)
targets = np.concatenate((np.ones(nS),np.zeros(nB)))
data_train = np.array(data[trainVars()])
#targets = np.array(data['bWj1Wj2_isGenMatched'])
#data_weights = np.array(data['evtWeight'])

cls = GradientBoostingClassifier(
    max_depth=3,
    learning_rate=0.01,
    n_estimators=100,
    verbose=True,
    min_samples_leaf=10,
    min_samples_split=10
)
#d_train, d_test, t_train, t_test, w_train, w_test = train_test_split(data_train, targets, data_weights, test_size=0.2, random_state=7)
d_train, d_test, t_train, t_test = train_test_split(data_train, targets, test_size=0.2, random_state=12345)
#cls.fit(data_train, targets)
#cls.fit(d_train, t_train, w_train)
cls.fit(d_train, t_train)

sklearn_to_tmva.gbr_to_tmva(
    cls,
    data[trainVars()],
    "TMVABDT_hadTopTagger_maxDepth3_9Var_ps75.xml",
    coef=2
)

import ROOT, array
from ROOT import TFile, TH1F, TGraph, TCanvas, TLegend

fout = TFile("hadTopTagger_performance_maxDepth3_9Var_ps75.root", "RECREATE")
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
fpr_tr, tpr_tr, tresholds_tr = sklearn.metrics.roc_curve(t_train, train_scores, pos_label=None)
for eff in effs:
	#print 'Fake rate at signal eff', eff, fpr_tr[np.argmax(tpr_tr>eff)]
	x_train.append(eff)
	y_train.append(fpr_tr[np.argmax(tpr_tr>eff)])
	
print 'from test sample'
test_scores = cls.decision_function(d_test)
fpr_te, tpr_te, tresholds_te = sklearn.metrics.roc_curve(t_test, test_scores, pos_label=None)
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

c1.SaveAs("roc_overtraining_hadTopTagger_maxDepth3_9Var_ps75.pdf")
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
filename = 'sklearn_hadTopTagger_maxDepth3_9Var_ps75.pkl'
pickle.dump(cls, open(filename, 'wb'))
 
