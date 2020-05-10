from collections import OrderedDict as OD

# file generated at 2020-05-10 12:39:05 with the following command:
# create_dictionary.py -m python/samples/metaDict_2017_sync.py -p /hdfs/local/karl/ttHNtupleProduction/2017/2020May10_wPresel_nonNom_sync/ntuples -N samples_2017 -E 2017 -o python/samples -g tthAnalyzeSamples_2017_preselected_sync.py -M

samples_2017 = OD()
samples_2017["/ttHJetToNonbb_M125_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "ttH"),
  ("process_name_specific",           "ttHJetToNonbb_M125_amcatnlo"),
  ("nof_files",                       1),
  ("nof_db_files",                    208),
  ("nof_events",                      {
    'Count'                                                                          : [        65452, ],
    'CountWeighted'                                                                  : [        22405,        22406,        22410, ],
    'CountWeightedLHEWeightScale'                                                    : [        22858,        23259,        23648,        22757,        22404,        22127,        21346,        20642,        20060, ],
    'CountWeightedLHEEnvelope'                                                       : [        26425,        17661, ],
    'CountWeightedL1PrefireNom'                                                      : [        21611,        21612,        21611, ],
    'CountWeightedL1Prefire'                                                         : [        21611,        21419,        21798, ],
    'CountWeightedLHEWeightScaleL1PrefireNom'                                        : [        22007,        22415,        22810,        21933,        21611,        21359,        20586,        19922,        19375, ],
    'CountWeightedLHEEnvelopeL1PrefireNom'                                           : [        25460,        17051, ],
    'Count_fwd'                                                                      : [          758, ],
    'CountWeighted_fwd'                                                              : [          292,          289,          297, ],
    'CountWeightedLHEWeightScale_fwd'                                                : [          303,          306,          308,          298,          292,          287,          280,          269,          260, ],
    'CountWeightedLHEEnvelope_fwd'                                                   : [          350,          230, ],
    'CountWeightedL1PrefireNom_fwd'                                                  : [          248,          246,          251, ],
    'CountWeightedL1Prefire_fwd'                                                     : [          248,          238,          258, ],
    'CountWeightedLHEWeightScaleL1PrefireNom_fwd'                                    : [          253,          258,          262,          252,          248,          245,          237,          229,          223, ],
    'CountWeightedLHEEnvelopeL1PrefireNom_fwd'                                       : [          295,          196, ],
    'Count_pt0to60'                                                                  : [        14086, ],
    'CountWeighted_pt0to60'                                                          : [         4976,         4995,         4943, ],
    'CountWeightedLHEWeightScale_pt0to60'                                            : [         5132,         5182,         5253,         5064,         4976,         4911,         4726,         4576,         4455, ],
    'CountWeightedLHEEnvelope_pt0to60'                                               : [         5851,         3984, ],
    'CountWeightedL1PrefireNom_pt0to60'                                              : [         4833,         4852,         4798, ],
    'CountWeightedL1Prefire_pt0to60'                                                 : [         4833,         4797,         4867, ],
    'CountWeightedLHEWeightScaleL1PrefireNom_pt0to60'                                : [         4981,         5031,         5103,         4915,         4832,         4772,         4588,         4446,         4330, ],
    'CountWeightedLHEEnvelopeL1PrefireNom_pt0to60'                                   : [         5681,         3871, ],
    'Count_pt60to120'                                                                : [        22761, ],
    'CountWeighted_pt60to120'                                                        : [         7868,         7880,         7865, ],
    'CountWeightedLHEWeightScale_pt60to120'                                          : [         8151,         8222,         8312,         8023,         7868,         7751,         7476,         7218,         7009, ],
    'CountWeightedLHEEnvelope_pt60to120'                                             : [         9383,         6172, ],
    'CountWeightedL1PrefireNom_pt60to120'                                            : [         7600,         7610,         7598, ],
    'CountWeightedL1Prefire_pt60to120'                                               : [         7600,         7535,         7664, ],
    'CountWeightedLHEWeightScaleL1PrefireNom_pt60to120'                              : [         7859,         7936,         8030,         7744,         7600,         7493,         7220,         6977,         6779, ],
    'CountWeightedLHEEnvelopeL1PrefireNom_pt60to120'                                 : [         9051,         5970, ],
    'Count_pt120to200'                                                               : [        17127, ],
    'CountWeighted_pt120to200'                                                       : [         5749,         5733,         5779, ],
    'CountWeightedLHEWeightScale_pt120to200'                                         : [         5705,         5868,         6012,         5813,         5749,         5701,         5515,         5345,         5204, ],
    'CountWeightedLHEEnvelope_pt120to200'                                            : [         6710,         4515, ],
    'CountWeightedL1PrefireNom_pt120to200'                                           : [         5543,         5529,         5567, ],
    'CountWeightedL1Prefire_pt120to200'                                              : [         5543,         5493,         5591, ],
    'CountWeightedLHEWeightScaleL1PrefireNom_pt120to200'                             : [         5485,         5648,         5792,         5599,         5543,         5500,         5318,         5158,         5025, ],
    'CountWeightedLHEEnvelopeL1PrefireNom_pt120to200'                                : [         6461,         4356, ],
    'Count_pt200to300'                                                               : [         7300, ],
    'CountWeighted_pt200to300'                                                       : [         2542,         2533,         2546, ],
    'CountWeightedLHEWeightScale_pt200to300'                                         : [         2623,         2674,         2711,         2589,         2542,         2500,         2423,         2329,         2249, ],
    'CountWeightedLHEEnvelope_pt200to300'                                            : [         3029,         1976, ],
    'CountWeightedL1PrefireNom_pt200to300'                                           : [         2445,         2435,         2450, ],
    'CountWeightedL1Prefire_pt200to300'                                              : [         2445,         2422,         2467, ],
    'CountWeightedLHEWeightScaleL1PrefireNom_pt200to300'                             : [         2517,         2569,         2609,         2487,         2445,         2407,         2329,         2241,         2166, ],
    'CountWeightedLHEEnvelopeL1PrefireNom_pt200to300'                                : [         2909,         1902, ],
    'Count_ptGt300'                                                                  : [         3420, ],
    'CountWeighted_ptGt300'                                                          : [          977,          977,          981, ],
    'CountWeightedLHEWeightScale_ptGt300'                                            : [          943,         1008,         1051,          970,          977,          977,          927,          905,          883, ],
    'CountWeightedLHEEnvelope_ptGt300'                                               : [         1103,          783, ],
    'CountWeightedL1PrefireNom_ptGt300'                                              : [          942,          940,          946, ],
    'CountWeightedL1Prefire_ptGt300'                                                 : [          942,          934,          950, ],
    'CountWeightedLHEWeightScaleL1PrefireNom_ptGt300'                                : [          912,          972,         1013,          936,          942,          942,          894,          872,          851, ],
    'CountWeightedLHEEnvelopeL1PrefireNom_ptGt300'                                   : [         1064,          755, ],
    'Count_pt300to450'                                                               : [         2678, ],
    'CountWeighted_pt300to450'                                                       : [          820,          816,          826, ],
    'CountWeightedLHEWeightScale_pt300to450'                                         : [          820,          861,          890,          820,          820,          816,          773,          751,          731, ],
    'CountWeightedLHEEnvelope_pt300to450'                                            : [          954,          645, ],
    'CountWeightedL1PrefireNom_pt300to450'                                           : [          790,          785,          796, ],
    'CountWeightedL1Prefire_pt300to450'                                              : [          790,          783,          797, ],
    'CountWeightedLHEWeightScaleL1PrefireNom_pt300to450'                             : [          792,          831,          858,          791,          790,          786,          744,          723,          704, ],
    'CountWeightedLHEEnvelopeL1PrefireNom_pt300to450'                                : [          920,          622, ],
    'Count_ptGt450'                                                                  : [          742, ],
    'CountWeighted_ptGt450'                                                          : [          157,          161,          155, ],
    'CountWeightedLHEWeightScale_ptGt450'                                            : [          124,          146,          161,          150,          157,          161,          155,          154,          151, ],
    'CountWeightedLHEEnvelope_ptGt450'                                               : [          149,          137, ],
    'CountWeightedL1PrefireNom_ptGt450'                                              : [          152,          155,          150, ],
    'CountWeightedL1Prefire_ptGt450'                                                 : [          152,          151,          154, ],
    'CountWeightedLHEWeightScaleL1PrefireNom_ptGt450'                                : [          120,          142,          156,          146,          152,          156,          150,          149,          147, ],
    'CountWeightedLHEEnvelopeL1PrefireNom_ptGt450'                                   : [          144,          133, ],
  }),
  ("nof_tree_events",                 14786),
  ("nof_db_events",                   9779592),
  ("fsize_local",                     89601610), # 89.60MB, avg file size 89.60MB
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
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2020May10_wPresel_nonNom_sync/ntuples/ttHJetToNonbb_M125_amcatnlo"),
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

