from collections import OrderedDict as OD

samples = OD()

samples["/TT_TuneCUETP8M1_13TeV-powheg-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12_ext3-v1/MINIAODSIM"] = OD([
    ("type", "mc"),
    ("sample_category", "TT"),
    ("process_name_specific", "TT_TuneCUETP8M1_ext3"),
    ("nof_files", 2413),
    ("nof_events", 97994442),
    ("use_it", True),
    ("xsection", 831.76),
    ("triggers", [ "1e", "1mu"]),
    ("local_paths",
     [
         OD([
             ("path", "/hdfs/cms/store/user/kaehatah/TT_TuneCUETP8M1_13TeV-powheg-pythia8/VHBB_HEPPY_V12_TT_TuneCUETP8M1_13TeV-powheg-Py8__fall15MAv2-pu25ns15v1_76r2as_v12_ext3-v1/160721_133505"),
             ("selection", "*")
             ])
         ]
     )
])
samples["/TT_TuneCUETP8M1_13TeV-powheg-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12_ext4-v1/MINIAODSIM"] = OD([
    ("type", "mc"),
    ("sample_category", "TT"),
    ("process_name_specific", "TT_TuneCUETP8M1_ext4"),
    ("nof_files", 4653),
    ("nof_events", 187626200),
    ("use_it", True),
    ("xsection", 831.76),
    ("triggers", [ "1e", "1mu" ]),
    ("local_paths",
     [
         OD([
             ("path", "/hdfs/cms/store/user/kaehatah/TT_TuneCUETP8M1_13TeV-powheg-pythia8/VHBB_HEPPY_V12_TT_TuneCUETP8M1_13TeV-powheg-Py8__fall15MAv2-pu25ns15v1_76r2as_v12_ext4-v1/160721_133402"),
             ("selection", "*")
             ])
         ]
     )
])
samples["/ttHToNonbb_M125_13TeV_powheg_pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"] = OD([
  ("type", "mc"),
  ("sample_category", "signal"),
  ("process_name_specific", "ttHToNonbb_M125"),
  ("nof_files", 91),
  ("nof_events", 3945824),
  ("use_it", True),
  ("xsection", 0.2151), # (1 - BR(ttH -> bb)) * sigma(ttH) = (1 - 0.577) * 0.5085 pb according to https://twiki.cern.ch/twiki/bin/view/LHCPhysics/CrossSections#Higgs_cross_sections_and_decay_b
  ("triggers", [ "1e", "1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/ttHToNonbb_M125_13TeV_powheg_pythia8/VHBB_HEPPY_V12_ttHToNonbb_M125_13TeV_powheg_Py8__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160330_172641"),
        ("selection", "*"),
      ])
    ]
  )
])
