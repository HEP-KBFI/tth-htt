import sys , time
#import sklearn_to_tmva
import sklearn
from sklearn import datasets
from sklearn.ensemble import GradientBoostingClassifier
from sklearn.cross_validation import train_test_split
import pandas
#from pandas import HDFStore,DataFrame
import math
import sklearn_to_tmva
import xgboost2tmva
import skTMVA
import matplotlib
matplotlib.use('agg')
#matplotlib.use('PS')   # generate postscript output by default
import matplotlib.pyplot as plt
from matplotlib import cm as cm
import numpy as np

import pickle

from sklearn.externals import joblib
import root_numpy
from root_numpy import root2array, rec2array, array2root

#from xgboost import XGBClassifier
import xgboost as xgb

#import numpy
import catboost as catboost #import CatBoostRegressor
#from catboost import CatBoostRegressor

#import gnosis.xml.pickle

from sklearn.model_selection import GridSearchCV
from sklearn.metrics import classification_report
from sklearn.metrics import roc_curve, auc
import ROOT
from tqdm import trange


def trainVars():
        return [
		'avg_dr_jet', 
		'dr_lep1_tau', 
		'dr_lep2_tau', 
		'dr_leps', 
		'htmiss', 
		'ptmiss',  
		#'lep1_frWeight', 
		#'lep1_isTight', 
		'lep1_pt',
		'lep2_pt', 
		'lep1_abs_eta',
		'lep2_abs_eta',
		'lep1_conePt',		
		'lep2_conePt', 
		#'lep2_frWeight', 
		#'lep2_isTight',  
		'lep1_tth_mva', 
		'lep2_tth_mva', 
		#'log_memOutput_tt', 
		#'log_memOutput_ttH', 
		#'log_memOutput_ttZ', 
		#'log_memOutput_ttZ_Zll', 
		#'lumiScale', 
		'mT_lep1', 
		'mT_lep2', 
		'mTauTauVis1', 
		'mTauTauVis2', 
		'max_lep_eta', 
		'memOutput_LR', 
		#'memOutput_isValid', 
		#'evtWeight', 
		#'memOutput_ttZ_Zll_LR', 
		'memOutput_tt_LR', 
		#'memOutput_type', 
		#'mindr_lep1_jet', 
		'mindr_lep2_jet', 
		'mindr_tau_jet', 
		'nBJetLoose', 
		'nBJetMedium', 
		'nJet', 
		'tau_abs_eta', 
		#'tau_frWeight', 
		#'tau_isTight', 
		'tau_mva', 
		'tau_pt' 
		#'target' 
		#'totalWeight'
		]

data_signal = pandas.read_csv("2lss_1tau_signal_fastsim_28Mar2017.csv")
data_signal["target"] = 1
data_signal["totalWeight"] = data_signal.evtWeight * data_signal.tau_frWeight * data_signal.lep1_frWeight * data_signal.lep2_frWeight #
print (data_signal["totalWeight"].sum())
data_signal["totalWeight"] = 100000*data_signal["totalWeight"] /data_signal["totalWeight"].sum()
#data_signal["evtWeight"] = data_signal["evtWeight"] /data_signal["evtWeight"].sum()
#data_signal = data_signal[data_signal.eval("(memOutput_errorFlag==0)")]
data_tt = pandas.read_csv("2lss_1tau_TT_fastsim_28Mar2017.csv")
data_tt["target"] = 0
data_tt["totalWeight"] = data_tt.evtWeight * data_tt.tau_frWeight * data_tt.lep1_frWeight * data_tt.lep2_frWeight #
print (data_tt["totalWeight"].sum())
data_tt["totalWeight"] = 100000*data_tt["totalWeight"] /data_tt["totalWeight"].sum()
#data_tt["evtWeight"] = data_tt["evtWeight"] /data_tt["evtWeight"].sum()
#data_tt = data_tt[data_tt.eval("(memOutput_errorFlag==0)")]
nS = len(data_signal)
nB = len(data_tt)
print "length of sig, bkg: ", nS, nB
data = pandas.concat([data_signal, data_tt])
print "length of sig+bkg: ", len(data)
#targets = np.concatenate((np.ones(nS),np.zeros(nB)))
#data_train = np.array(data[trainVars()])
#data_weights = np.array(data['evtWeight'])

#data["totalWeight"] = data.evtWeight * data.tau_frWeight * data.lep1_frWeight * data.lep2_frWeight   
#data.ix[data.target.values == 0, "totalWeight"] = data["totalWeight"]/

# evtWeight *= ( prob_chargeMisId_lead + prob_chargeMisId_sublead);
data_weights = np.array(data['totalWeight'])
weights = "totalWeight"
print (list(data))
#print (data.index)
#data["mva1"] = 0.0
#data["mva2"] = 0.0

#################################################################################
### Plot some histograms
################################################################################# 
### against QCD
hist_params = {'normed': False, 'bins': 18, 'alpha': 0.4}
plt.figure(figsize=(30, 30))
for n, feature in enumerate(trainVars()):
    # add sub plot on our figure
	plt.subplot(6, 6, n+1)
    # define range for histograms by cutting 1% of data from both ends
	if n == 0 or n == 1 or n == 2 or n == 4 or n == 5 : min_value, max_value = np.percentile(data[feature], [1, 99])
	else : min_value, max_value = np.percentile(data[feature], [1, 99])
	values, bins, _ = plt.hist(data.ix[data.target.values == 0, feature].values,  weights= data.ix[data.target.values == 0, weights].values , 
                               range=(min_value, max_value), label="TT", **hist_params )
	values, bins, _ = plt.hist(data.ix[data.target.values == 1, feature].values, weights= data.ix[data.target.values == 1, weights].values , 
                               range=(min_value, max_value), label='Signal', **hist_params)
	areaSig = sum(np.diff(bins)*values)
	#print areaBKG, " ",areaBKG2 ," ",areaSig
	if n == 0 : plt.legend(loc='best')
	plt.title(feature)
plt.savefig("Variables_BDT.pdf")
plt.clf()
#########################################################################################
#print (data.ix[data.target.values == 0, weights])
#print (data.ix[data.target.values == 1, weights])
traindataset, valdataset  = train_test_split(data, test_size=0.5, random_state=7)


#raindataset, valdataset, t_train, t_test, w_train, w_test = train_test_split(data, np.array(data['target']), data_weights, test_size=0.5, random_state=7)
#cls.fit(data_train, targets)
#ls.fit(traindataset, t_train, w_train)



keys=["evtLevelTT_TTH","evtLevelTTW_TTH"]

## do the report 
evals_result={}
param=[('max_depth', 6), ('objective', 'binary:logistic'), # ('eval_metric', 'logloss'), 
	('n_estimators', 100),('min_child_weight', 30)] 
num_round = 2
#cls = xgb(param)
"""
evals_result = {}
dtrain = xgb.DMatrix(traindataset, label = traindataset["target"], 
	weight = (traindataset[weights].astype(np.float64)), silent=True)
dtest = xgb.DMatrix(valdataset, label = valdataset["target"],
	weight = (valdataset[weights].astype(np.float64)), silent=True)
watchlist  = [(dtest,'eval'), (dtrain,'train')]
cls=xgb.train(param, dtrain, num_round, watchlist , evals_result=evals_result)
print (evals_result)
model = cls.get_dump() # #pickle.dumps(cls)
"""
cls = xgb.XGBClassifier()
cls.fit(
	traindataset[trainVars()].values,  
	traindataset.target.astype(np.bool),  
	#sample_weight= (traindataset[weights].astype(np.float64)),
	#eval_set=[(traindataset[trainVars()].values,  traindataset.target.astype(np.bool),traindataset[weights].astype(np.float64)),
	#(valdataset[trainVars()].values,  valdataset.target.astype(np.bool), valdataset[weights].astype(np.float64))] ,  
	#eval_metric='logloss'
	)
#print (cls.evals_result())
#print (cls.evals_result()['validation_0']['logloss'])
#"""
model = cls.booster().get_dump(fmap='', with_stats=False) #.get_dump() #pickle.dumps(cls)
xgboost2tmva.convert_model(model, trainVars(), "TMVABDT_2lss_1tau_XGB_wMEMallVars.xml")
# xmllint --format TMVABDT_2lss_1tau_XGB_wMEMallVars.xml
#skTMVA.convert_bdt_sklearn_tmva(cls, trainVars(), "TMVABDT_2lss_1tau_XGB_wMEMallVars.xml")  
#sklearn_to_tmva.xgbr_to_tmva(cls,evals_result,data[trainVars()],trainVars(),"TMVABDT_2lss_1tau_XGB_wMEMallVars.xml",coef=2)
# run cross validation
print ("XGBoost trained") 
proba = cls.predict_proba(traindataset[trainVars()].values  )
fpr, tpr, thresholds = roc_curve(traindataset["target"], proba[:,1] )
train_auc = auc(fpr, tpr, reorder = True) 
print("XGBoost train set auc - {}".format(train_auc)) 
proba = cls.predict_proba(valdataset[trainVars()].values)
fprt, tprt, thresholds = roc_curve(valdataset["target"], proba[:,1] )
test_auct = auc(fprt, tprt, reorder = True)
print("XGBoost test set auc - {}".format(test_auct))
""" 
sklearn_to_tmva.gbr_to_tmva(
    cls,
    data[trainVars()],
	trainVars(),
    "TMVABDT_2lss_1tau_XGB_wMEMallVars.xml",
    coef=2
)
#"""
##################################################
clc = catboost.CatBoostClassifier()
clc.fit(
	traindataset[trainVars()].values,  
	traindataset.target.astype(np.bool),  
	#sample_weight= np.absolute((traindataset[weights].astype(np.float64))),
	#eval_set=[(traindataset[trainVars()].values,  traindataset.target.astype(np.bool),traindataset[weights].astype(np.float64)),
	#(valdataset[trainVars()].values,  valdataset.target.astype(np.bool), valdataset[weights].astype(np.float64))] ,  
	#eval_metric='logloss'
	)
#print (cls.evals_result())
#print (cls.evals_result()['validation_0']['logloss'])
#"""
#model = pickle.dumps(clc) # clc.get_dump() #
#xgboost2tmva.convert_model(model, trainVars(), "TMVABDT_2lss_1tau_CB_wMEMallVars.xml")
# xmllint --format TMVABDT_2lss_1tau_XGB_wMEMallVars.xml
print ("CatBoost trained") 
proba = clc.predict_proba(traindataset[trainVars()].values  )
fprc, tprc, thresholds = roc_curve(traindataset["target"], proba[:,1] )
train_aucc = auc(fprc, tprc, reorder = True) 
print("CatBoost train set auc - {}".format(train_aucc)) 
proba = clc.predict_proba(valdataset[trainVars()].values)
fprtc, tprtc, thresholds = roc_curve(valdataset["target"], proba[:,1] )
test_auctc = auc(fprtc, tprtc, reorder = True)
print("CatBoost test set auc - {}".format(test_auctc))
##################################################
clf = GradientBoostingClassifier(max_depth=3,learning_rate=0.01,n_estimators=100,verbose=True,min_samples_leaf=10,min_samples_split=10)
clf.fit(traindataset[trainVars()].values,  
	traindataset.target.astype(np.bool) #,  
	#sample_weight= (traindataset[weights].astype(np.float64))
	)
sklearn_to_tmva.gbr_to_tmva(clf,data[trainVars()],trainVars(),"TMVABDT_2lss_1tau_GB_wMEMallVars.xml",coef=2)
print ("GradientBoosting trained")
proba = clf.predict_proba(traindataset[trainVars()].values  )
fprf, tprf, thresholdsf = roc_curve(traindataset["target"], proba[:,1] )
train_aucf = auc(fprf, tprf, reorder = True) 
print("GradientBoosting train set auc - {}".format(train_aucf)) 
proba = clf.predict_proba(valdataset[trainVars()].values)
fprtf, tprtf, thresholdsf = roc_curve(valdataset["target"], proba[:,1] )
test_auctf = auc(fprtf, tprtf, reorder = True)
print("GradientBoosting test set auc - {}".format(test_auctf)) 
##################################################

#roc_auc = auc(fpr, tpr, reorder = True)
#roc_aucf = auc(fpr, tpr, reorder = True)
fig, ax = plt.subplots()
## ROC curve
ax.plot(fpr, tpr, lw=1, label='XGBoost train (area = %0.3f)'%(train_auc))
ax.plot(fprt, tprt, lw=1, label='XGBoost test (area = %0.3f)'%(test_auct))

ax.plot(fprf, tprf, lw=1, label='GradientBoost train (area = %0.3f)'%(train_aucf))
ax.plot(fprtf, tprtf, lw=1, label='GradientBoost test (area = %0.3f)'%(test_auctf))

ax.plot(fprc, tprc, lw=1, label='CatBoost train (area = %0.3f)'%(train_aucc))
ax.plot(fprtc, tprtc, lw=1, label='CatBoost test (area = %0.3f)'%(test_auctc))
ax.set_ylim([0.7,1.0])
ax.set_xlabel('False Positive Rate')
ax.set_ylabel('True Positive Rate')
#ax.set_title('Test set ROC')
ax.legend(loc="lower right")
ax.grid()
fig.savefig("{}_test_roc.png".format(keys[0]))
fig.savefig("{}_test_roc.pdf".format(keys[0]))
## feature importance plot
fig, ax = plt.subplots()
f_score_dict =cls.booster().get_fscore()
f_score_dict = {trainVars()[int(k[1:])] : v for k,v in f_score_dict.items()}
feat_imp = pandas.Series(f_score_dict).sort_values(ascending=True)
feat_imp.plot(kind='barh', title='Feature Importances')
fig.tight_layout()
fig.savefig("{}_importance.png".format(keys[0]))
fig.savefig("{}_importance.pdf".format(keys[0]))


#save the training to file for later use
filename = 'sklearn_2lss_1tau_maxDepth3_8Var_frWt_wMEMall.pkl'
#obj=pickle.dump(cls, open(filename, 'wb'))
#xml_str = gnosis.xml.pickle.dumps(obj)
#o2 = gnosis.xml.pickle.loads('test.xml')
