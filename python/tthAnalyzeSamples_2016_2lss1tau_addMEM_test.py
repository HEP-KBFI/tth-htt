from collections import OrderedDict as OD

samples_2016 = OD()

# file generated with command:
# check_broken -p /hdfs/local/karl/addMEM_tth_quarter/2016/2016Dec16/ntuples/2lss_1tau -v -o -P

samples_2016["/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14_ext1-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "signal"),
  ("process_name_specific", "ttHJetToNonbb_M125"),
  ("nof_files",             9),
  ("nof_events",            52967720),
  ("use_it",                True),
  ("xsection",              0.215100),
  ("genWeight",             True),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM_tth_quarter/2016/2016Dec16/ntuples/2lss_1tau/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/VHBB_HEPPY_V24bis_ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_Py8_mWCutfix__spr16MAv2-puspr16_HLT_80r2as_v14_ext1-v1/160911_223711"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
