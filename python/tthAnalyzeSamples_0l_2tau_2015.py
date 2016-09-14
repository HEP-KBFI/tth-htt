from collections import OrderedDict as OD

from tthAnalyzeSamples_2015 import samples_2015

for sample_name, sample_info in samples_2015.items():
  if sample_info["type"] == "mc":
    sample_info["triggers"] = [ "2tau" ]
  if sample_name in [
      "/DoubleMuon/Run2015C_25ns-16Dec2015-v1/MINIAOD",
      "/DoubleMuon/Run2015D-16Dec2015-v1/MINIAOD",
      "/DoubleEG/Run2015C_25ns-16Dec2015-v1/MINIAOD",
      "/DoubleEG/Run2015D-16Dec2015-v2/MINIAOD",
      "/MuonEG/Run2015C_25ns-16Dec2015-v1/MINIAOD", 
      "/MuonEG/Run2015D-16Dec2015-v1/MINIAOD",
      "/SingleMuon/Run2015C_25ns-16Dec2015-v1/MINIAOD",
      "/SingleMuon/Run2015D-16Dec2015-v1/MINIAOD",
      "/SingleElectron/Run2015C_25ns-16Dec2015-v1/MINIAOD",
      "/SingleElectron/Run2015D-16Dec2015-v1/MINIAOD" ]:
    sample_info["use_it"] = False

# CV: this sample is used as place-holder to fill some data_obs histograms at all;
#     we really need to process the TauPlusX datasets in order to compare data_obs with expected backgrounds in the 0l_2tau channel !!
samples_2015["/DoubleMuon/Run2015C_25ns-16Dec2015-v1/MINIAOD"]["triggers"] = [ "2mu" ]
samples_2015["/DoubleMuon/Run2015C_25ns-16Dec2015-v1/MINIAOD"]["use_it"] = True
