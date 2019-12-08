from collections import OrderedDict as OD

# file generated at 2019-12-08 17:39:12 with the following command:
# create_dictionary.py -m python/samples/metaDict_2017_sync.py -p /hdfs/local/karl/addMEM/2017/2019Dec06_sync_nonNom/final_ntuples/3l -N samples_2017 -E 2017 -o python/samples -g tthAnalyzeSamples_2017_addMEM_3l_deepVSjVLoose_sync.py -M

samples_2017 = OD()
samples_2017["/ttHJetToNonbb_M125_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "ttH"),
  ("process_name_specific",           "ttHJetToNonbb_M125_amcatnlo"),
  ("nof_files",                       1),
  ("nof_db_files",                    208),
  ("nof_events",                      {
    'Count'                                                      : [        65452, ],
    'CountWeighted'                                              : [        22405,        22406,        22410, ],
    'CountWeightedLHEWeightScale'                                : [        22858,        23259,        23648,        22757,        22404,        22127,        21346,        20642,        20060, ],
    'CountWeightedL1PrefireNom'                                  : [        21611,        21612,        21611, ],
    'CountWeightedL1Prefire'                                     : [        21611,        21419,        21798, ],
    'CountWeightedLHEWeightScaleL1PrefireNom'                    : [        22007,        22415,        22810,        21933,        21611,        21359,        20586,        19922,        19375, ],
  }),
  ("nof_tree_events",                 14776),
  ("nof_db_events",                   9779592),
  ("fsize_local",                     82398900), # 82.40MB, avg file size 82.40MB
  ("fsize_db",                        625507074411), # 625.51GB, avg file size 3.01GB
  ("use_it",                          True),
  ("xsection",                        0.2118),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("LHE_set",                         "LHA IDs 91400 - 91432 -> PDF4LHC15_nnlo_30_pdfas PDF set, expecting 33 weights (counted 33 weights)"),
  ("nof_reweighting",                 0),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2017/2019Dec06_sync_nonNom/final_ntuples/3l/ttHJetToNonbb_M125_amcatnlo"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_completely",           [
    # not computed
  ]),
  ("missing_from_superset",        [
    # not computed
  ]),
  ("missing_hlt_paths",            [

  ]),
  ("hlt_paths",                    [
    # not computed
  ]),
])

samples_2017["sum_events"] = [
]

