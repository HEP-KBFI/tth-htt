from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017 import samples_2017

sync_key = "/ttHJetToNonbb_M125_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"

samples_2017[sync_key]['local_paths'][0]['path'] = '/hdfs/local/karl/ttHNtupleProduction/2017/2018May29_woPresel_nonNom_sync/ntuples/ttHJetToNonbb_M125_amcatnlo'
samples_2017[sync_key]['nof_files'] = 1
samples_2017[sync_key]['nof_tree_events'] = 56465

for sample_key in samples_2017:
  if sample_key != sync_key:
    del samples_2017[sample_key]
