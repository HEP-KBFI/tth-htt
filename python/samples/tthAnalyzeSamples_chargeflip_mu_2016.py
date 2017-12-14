from tthAnalyzeSamples_2016 import samples_2016

for sample_name, sample_info in samples_2016.items():
  if sample_info["use_it"] == False: continue
  if sample_info["type"] == "mc":
    sample_info["triggers"] = [ "1mu", "2mu" ]
  if sample_name in [
      "/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM",
      "/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v2/MINIAODSIM",
      "/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/MINIAODSIM"]:
    sample_info["sample_category"] = "DY"
  elif "TTJets" in sample_name:
    sample_info["sample_category"] = "TTbar"
  elif sample_name in [
      "/WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"]:
    sample_info["sample_category"] = "WJets"
  elif "ST_" in sample_name:
    sample_info["sample_category"] = "Singletop"
  elif sample_name in [
      "/WWTo2L2Nu_13TeV-powheg/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM",
      "/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM",
      "/ZZTo4L_13TeV_powheg_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"]:
    sample_info["sample_category"] = "Diboson"
  elif "Muon" in sample_name:
      sample_info["use_it"] = True
  elif sample_info["sample_category"] == "data_obs":
    sample_info["use_it"] = False
  else:
    sample_info["use_it"] = False

