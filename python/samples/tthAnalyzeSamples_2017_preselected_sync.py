from collections import OrderedDict as OD

# file generated at 2020-10-24 22:36:07 with the following command:
# create_dictionary.py -m python/samples/metaDict_2017_sync.py -p /hdfs/local/karl/ttHNtupleProduction/2017/2020Oct24_wPresel_nonNom_tth_sync/ntuples -N samples_2017 -E 2017 -o python/samples -g tthAnalyzeSamples_2017_preselected_sync.py -M

samples_2017 = OD()
samples_2017["/ttHJetToNonbb_M125_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "ttH"),
  ("process_name_specific",           "ttHJetToNonbb_M125_amcatnlo"),
  ("nof_files",                       1),
  ("nof_db_files",                    208),
  ("nof_events",                      {
    'Count'                                                                          : [ 65452, ],
    'CountWeighted'                                                                  : [ 2.24047031e+04, 2.24060469e+04, 2.24102617e+04, ],
    'CountWeightedLHEWeightScale'                                                    : [ 2.28575117e+04, 2.32592617e+04, 2.36476738e+04, 2.27572305e+04, 2.24044316e+04, 2.21269707e+04, 2.13462832e+04, 2.06416992e+04, 2.00599531e+04, ],
    'CountWeightedLHEEnvelope'                                                       : [ 2.64254922e+04, 1.76606816e+04, ],
    'CountWeightedFull'                                                              : [ 6.43864453e+04, 6.43908906e+04, 6.44024258e+04, ],
    'CountWeightedFullLHEWeightScale'                                                : [ 6.56884531e+04, 6.68425938e+04, 6.79600312e+04, 6.54005273e+04, 6.43841406e+04, 6.35894414e+04, 6.13456758e+04, 5.93203945e+04, 5.76492656e+04, ],
    'CountWeightedFullLHEEnvelope'                                                   : [ 7.59421250e+04, 5.07542969e+04, ],
    'CountWeightedL1PrefireNom'                                                      : [ 2.16109141e+04, 2.16123809e+04, 2.16111621e+04, ],
    'CountWeightedL1Prefire'                                                         : [ 2.16109141e+04, 2.14187305e+04, 2.17982676e+04, ],
    'CountWeightedLHEWeightScaleL1PrefireNom'                                        : [ 2.20066367e+04, 2.24151426e+04, 2.28095312e+04, 2.19325137e+04, 2.16105488e+04, 2.13593359e+04, 2.05860547e+04, 1.99223984e+04, 1.93749414e+04, ],
    'CountWeightedLHEEnvelopeL1PrefireNom'                                           : [ 2.54595605e+04, 1.70505352e+04, ],
    'CountWeightedFullL1PrefireNom'                                                  : [ 6.21050273e+04, 6.21103594e+04, 6.21063086e+04, ],
    'CountWeightedFullL1Prefire'                                                     : [ 6.21050273e+04, 6.15529961e+04, 6.26441094e+04, ],
    'CountWeightedFullLHEWeightScaleL1PrefireNom'                                    : [ 6.32432695e+04, 6.44164766e+04, 6.55507109e+04, 6.30308516e+04, 6.21031484e+04, 6.13832695e+04, 5.91609375e+04, 5.72536680e+04, 5.56804180e+04, ],
    'CountWeightedFullLHEEnvelopeL1PrefireNom'                                       : [ 7.31665625e+04, 4.90006914e+04, ],
  }),
  ("nof_tree_events",                 14786),
  ("nof_db_events",                   9779592),
  ("fsize_local",                     88692411), # 88.69MB, avg file size 88.69MB
  ("fsize_db",                        625507074411), # 625.51GB, avg file size 3.01GB
  ("use_it",                          True),
  ("xsection",                        0.2118),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("nof_PSweights",                   1),
  ("LHE_set",                         "LHA IDs 91400 - 91432 -> PDF4LHC15_nnlo_30_pdfas PDF set, expecting 33 weights (counted 33 weights)"),
  ("nof_reweighting",                 0),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2020Oct24_wPresel_nonNom_tth_sync/ntuples/ttHJetToNonbb_M125_amcatnlo"),
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

