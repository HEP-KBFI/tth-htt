from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017 import samples_2017

sync_key = "/ttHJetToNonbb_M125_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"

samples_2017[sync_key]['local_paths'][0]['path'] = '/hdfs/local/karl/ttHNtupleProduction/2017/2018Mar05_wNanoPrep_woPresel_sync/ntuples/ttHJetToNonbb_M125_amcatnlo'
samples_2017[sync_key]['nof_files'] = 1

for sample_key in samples_2017:
  samples_2017[sample_key]['use_it'] = (sample_key == sync_key)
