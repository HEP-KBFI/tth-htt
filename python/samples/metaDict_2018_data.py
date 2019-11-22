from collections import OrderedDict as OD

# file generated at 2019-11-22 13:35:41 with the following command:
# find_samples.py -V -m python/samples/metaDict_2018_data.py -d ../NanoAOD/test/datasets/txt/datasets_data_2018_17Sep18.txt -p SingleMuon EGamma DoubleMuon MuonEG Tau -g ../NanoAOD/data/Cert_314472-325175_13TeV_17SeptEarlyReReco2018ABC_PromptEraD_Collisions18_JSON.txt -v 10_2_4_patch1 -r 2018 -C +17Sep2018 +Run2018D-PromptReco -c python/samples/sampleLocations_2018_nanoAOD.txt

meta_dictionary = OD()

meta_dictionary["/SingleMuon/Run2018A-17Sep2018-v2/MINIAOD"] =  OD([
  ("crab_string",           "2018_2019Jun26_SingleMuon__Run2018A-17Sep2018-v2"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleMuon_Run2018A_17Sep2018_v2"),
  ("nof_db_events",         241608232),
  ("nof_db_files",          3224),
  ("fsize_db",              8135831594497),
  ("xsection",              None),
  ("use_it",                True),
  ("genWeight",             False),
  ("run_range",             [315257, 316995]),
  ("golden_run_range",      [315257, 316995]),
  ("comment",               "100.0%; status: VALID; size: 8.14TB; nevents: 241.61M; release: 10_2_4_patch1; last modified: 2018-10-25 11:05:39"),
])

meta_dictionary["/SingleMuon/Run2018B-17Sep2018-v1/MINIAOD"] =  OD([
  ("crab_string",           "2018_2019Jun26_SingleMuon__Run2018B-17Sep2018-v1"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleMuon_Run2018B_17Sep2018_v1"),
  ("nof_db_events",         119918017),
  ("nof_db_files",          1551),
  ("fsize_db",              3900746978900),
  ("xsection",              None),
  ("use_it",                True),
  ("genWeight",             False),
  ("run_range",             [317080, 319310]),
  ("golden_run_range",      [317080, 319077]),
  ("comment",               "100.0%; status: VALID; size: 3.90TB; nevents: 119.92M; release: 10_2_4_patch1; last modified: 2018-10-15 08:23:13"),
])

meta_dictionary["/SingleMuon/Run2018C-17Sep2018-v1/MINIAOD"] =  OD([
  ("crab_string",           "2018_2019Jun26_SingleMuon__Run2018C-17Sep2018-v1"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleMuon_Run2018C_17Sep2018_v1"),
  ("nof_db_events",         110032072),
  ("nof_db_files",          1556),
  ("fsize_db",              3645461800472),
  ("xsection",              None),
  ("use_it",                True),
  ("genWeight",             False),
  ("run_range",             [319337, 320065]),
  ("golden_run_range",      [319337, 320065]),
  ("comment",               "100.0%; status: VALID; size: 3.65TB; nevents: 110.03M; release: 10_2_4_patch1; last modified: 2018-10-10 07:01:43"),
])

meta_dictionary["/SingleMuon/Run2018D-PromptReco-v2/MINIAOD"] =  OD([
  ("crab_string",           "2018prompt_2019Jul23_SingleMuon__Run2018D-PromptReco-v2"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleMuon_Run2018D_PromptReco_v2"),
  ("nof_db_events",         506717754),
  ("nof_db_files",          5533),
  ("fsize_db",              17033911936949),
  ("xsection",              None),
  ("use_it",                True),
  ("genWeight",             False),
  ("run_range",             [320500, 325175]),
  ("golden_run_range",      [320673, 325172]),
  ("comment",               "100.0%; status: VALID; size: 17.03TB; nevents: 506.72M; release: 10_2_1,10_2_5_patch1; last modified: 2018-08-01 16:17:08"),
])

meta_dictionary["/EGamma/Run2018A-17Sep2018-v2/MINIAOD"] =  OD([
  ("crab_string",           "2018_2019Jul04_EGamma__Run2018A-17Sep2018-v2"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "EGamma_Run2018A_17Sep2018_v2"),
  ("nof_db_events",         327843843),
  ("nof_db_files",          4790),
  ("fsize_db",              12503613778334),
  ("xsection",              None),
  ("use_it",                True),
  ("genWeight",             False),
  ("run_range",             [315257, 316995]),
  ("golden_run_range",      [315257, 316995]),
  ("comment",               "100.0%; status: VALID; size: 12.50TB; nevents: 327.84M; release: 10_2_4_patch1; last modified: 2019-01-14 22:34:35"),
])

meta_dictionary["/EGamma/Run2018B-17Sep2018-v1/MINIAOD"] =  OD([
  ("crab_string",           "2018_2019Jul23_EGamma__Run2018B-17Sep2018-v1"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "EGamma_Run2018B_17Sep2018_v1"),
  ("nof_db_events",         153822427),
  ("nof_db_files",          1941),
  ("fsize_db",              5638019764583),
  ("xsection",              None),
  ("use_it",                True),
  ("genWeight",             False),
  ("run_range",             [317080, 319310]),
  ("golden_run_range",      [317080, 319077]),
  ("comment",               "100.0%; status: VALID; size: 5.64TB; nevents: 153.82M; release: 10_2_4_patch1; last modified: 2018-11-26 16:21:55"),
])

meta_dictionary["/EGamma/Run2018C-17Sep2018-v1/MINIAOD"] =  OD([
  ("crab_string",           "2018_2019Jul23_EGamma__Run2018C-17Sep2018-v1"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "EGamma_Run2018C_17Sep2018_v1"),
  ("nof_db_events",         147827904),
  ("nof_db_files",          2183),
  ("fsize_db",              5494089856214),
  ("xsection",              None),
  ("use_it",                True),
  ("genWeight",             False),
  ("run_range",             [319337, 320065]),
  ("golden_run_range",      [319337, 320065]),
  ("comment",               "100.0%; status: VALID; size: 5.49TB; nevents: 147.83M; release: 10_2_4_patch1; last modified: 2018-10-17 11:12:09"),
])

meta_dictionary["/EGamma/Run2018D-PromptReco-v2/MINIAOD"] =  OD([
  ("crab_string",           "2018prompt_2019Jul04_EGamma__Run2018D-PromptReco-v2"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "EGamma_Run2018D_PromptReco_v2"),
  ("nof_db_events",         738976078),
  ("nof_db_files",          8663),
  ("fsize_db",              28473919391099),
  ("xsection",              None),
  ("use_it",                True),
  ("genWeight",             False),
  ("run_range",             [320497, 325175]),
  ("golden_run_range",      [320673, 325172]),
  ("comment",               "100.0%; status: VALID; size: 28.47TB; nevents: 738.98M; release: 10_2_1,10_2_5_patch1; last modified: 2018-08-01 10:55:01"),
])

meta_dictionary["/DoubleMuon/Run2018A-17Sep2018-v2/MINIAOD"] =  OD([
  ("crab_string",           "2018_2019Jun26_DoubleMuon__Run2018A-17Sep2018-v2"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleMuon_Run2018A_17Sep2018_v2"),
  ("nof_db_events",         75499908),
  ("nof_db_files",          1260),
  ("fsize_db",              3053758672673),
  ("xsection",              None),
  ("use_it",                True),
  ("genWeight",             False),
  ("run_range",             [315257, 316995]),
  ("golden_run_range",      [315257, 316995]),
  ("comment",               "100.0%; status: VALID; size: 3.05TB; nevents: 75.50M; release: 10_2_4_patch1; last modified: 2018-11-02 00:30:12"),
])

meta_dictionary["/DoubleMuon/Run2018B-17Sep2018-v1/MINIAOD"] =  OD([
  ("crab_string",           "2018_2019Jun26_DoubleMuon__Run2018B-17Sep2018-v1"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleMuon_Run2018B_17Sep2018_v1"),
  ("nof_db_events",         35057758),
  ("nof_db_files",          614),
  ("fsize_db",              1382907754207),
  ("xsection",              None),
  ("use_it",                True),
  ("genWeight",             False),
  ("run_range",             [317080, 319310]),
  ("golden_run_range",      [317080, 319077]),
  ("comment",               "100.0%; status: VALID; size: 1.38TB; nevents: 35.06M; release: 10_2_4_patch1; last modified: 2018-10-11 09:00:06"),
])

meta_dictionary["/DoubleMuon/Run2018C-17Sep2018-v1/MINIAOD"] =  OD([
  ("crab_string",           "2018_2019Jun26_DoubleMuon__Run2018C-17Sep2018-v1"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleMuon_Run2018C_17Sep2018_v1"),
  ("nof_db_events",         34565869),
  ("nof_db_files",          526),
  ("fsize_db",              1367635187361),
  ("xsection",              None),
  ("use_it",                True),
  ("genWeight",             False),
  ("run_range",             [319337, 320065]),
  ("golden_run_range",      [319337, 320065]),
  ("comment",               "100.0%; status: VALID; size: 1.37TB; nevents: 34.57M; release: 10_2_4_patch1; last modified: 2018-10-29 11:52:00"),
])

meta_dictionary["/DoubleMuon/Run2018D-PromptReco-v2/MINIAOD"] =  OD([
  ("crab_string",           "2018prompt_2019Jun26_DoubleMuon__Run2018D-PromptReco-v2"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleMuon_Run2018D_PromptReco_v2"),
  ("nof_db_events",         169225355),
  ("nof_db_files",          2353),
  ("fsize_db",              6064326232889),
  ("xsection",              None),
  ("use_it",                True),
  ("genWeight",             False),
  ("run_range",             [320500, 325175]),
  ("golden_run_range",      [320673, 325172]),
  ("comment",               "100.0%; status: VALID; size: 6.06TB; nevents: 169.23M; release: 10_2_1,10_2_5_patch1; last modified: 2018-08-02 03:29:41"),
])

meta_dictionary["/MuonEG/Run2018A-17Sep2018-v1/MINIAOD"] =  OD([
  ("crab_string",           "2018_2019Jul23_MuonEG__Run2018A-17Sep2018-v1"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "MuonEG_Run2018A_17Sep2018_v1"),
  ("nof_db_events",         32958503),
  ("nof_db_files",          541),
  ("fsize_db",              1494542711348),
  ("xsection",              None),
  ("use_it",                True),
  ("genWeight",             False),
  ("run_range",             [315257, 316995]),
  ("golden_run_range",      [315257, 316995]),
  ("comment",               "100.0%; status: VALID; size: 1.49TB; nevents: 32.96M; release: 10_2_4_patch1; last modified: 2018-12-21 01:20:07"),
])

meta_dictionary["/MuonEG/Run2018B-17Sep2018-v1/MINIAOD"] =  OD([
  ("crab_string",           "2018_2019Jul23_MuonEG__Run2018B-17Sep2018-v1"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "MuonEG_Run2018B_17Sep2018_v1"),
  ("nof_db_events",         16211567),
  ("nof_db_files",          333),
  ("fsize_db",              715534319571),
  ("xsection",              None),
  ("use_it",                True),
  ("genWeight",             False),
  ("run_range",             [317080, 319310]),
  ("golden_run_range",      [317080, 319077]),
  ("comment",               "100.0%; status: VALID; size: 715.53GB; nevents: 16.21M; release: 10_2_4_patch1; last modified: 2019-01-31 14:17:15"),
])

meta_dictionary["/MuonEG/Run2018C-17Sep2018-v1/MINIAOD"] =  OD([
  ("crab_string",           "2018_2019Jun26_MuonEG__Run2018C-17Sep2018-v1"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "MuonEG_Run2018C_17Sep2018_v1"),
  ("nof_db_events",         15652198),
  ("nof_db_files",          292),
  ("fsize_db",              700749792293),
  ("xsection",              None),
  ("use_it",                True),
  ("genWeight",             False),
  ("run_range",             [319337, 320065]),
  ("golden_run_range",      [319337, 320065]),
  ("comment",               "100.0%; status: VALID; size: 700.75GB; nevents: 15.65M; release: 10_2_4_patch1; last modified: 2019-01-23 05:46:20"),
])

meta_dictionary["/MuonEG/Run2018D-PromptReco-v2/MINIAOD"] =  OD([
  ("crab_string",           "2018prompt_2019Jun26_MuonEG__Run2018D-PromptReco-v2"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "MuonEG_Run2018D_PromptReco_v2"),
  ("nof_db_events",         71962991),
  ("nof_db_files",          1373),
  ("fsize_db",              2962155247807),
  ("xsection",              None),
  ("use_it",                True),
  ("genWeight",             False),
  ("run_range",             [320500, 325175]),
  ("golden_run_range",      [320673, 325172]),
  ("comment",               "100.0%; status: VALID; size: 2.96TB; nevents: 71.96M; release: 10_2_1,10_2_5_patch1; last modified: 2018-08-02 04:37:51"),
])

meta_dictionary["/Tau/Run2018A-17Sep2018-v1/MINIAOD"] =  OD([
  ("crab_string",           "2018_2019Jul23_Tau__Run2018A-17Sep2018-v1"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "Tau_Run2018A_17Sep2018_v1"),
  ("nof_db_events",         63153347),
  ("nof_db_files",          1071),
  ("fsize_db",              2565556827398),
  ("xsection",              None),
  ("use_it",                True),
  ("genWeight",             False),
  ("run_range",             [315257, 316995]),
  ("golden_run_range",      [315257, 316995]),
  ("comment",               "100.0%; status: VALID; size: 2.57TB; nevents: 63.15M; release: 10_2_4_patch1; last modified: 2018-11-25 08:28:53"),
])

meta_dictionary["/Tau/Run2018B-17Sep2018-v1/MINIAOD"] =  OD([
  ("crab_string",           "2018_2019Jun26_Tau__Run2018B-17Sep2018-v1"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "Tau_Run2018B_17Sep2018_v1"),
  ("nof_db_events",         32678961),
  ("nof_db_files",          569),
  ("fsize_db",              1287030479908),
  ("xsection",              None),
  ("use_it",                True),
  ("genWeight",             False),
  ("run_range",             [317080, 319310]),
  ("golden_run_range",      [317080, 319077]),
  ("comment",               "100.0%; status: VALID; size: 1.29TB; nevents: 32.68M; release: 10_2_4_patch1; last modified: 2018-11-07 09:58:00"),
])

meta_dictionary["/Tau/Run2018C-17Sep2018-v1/MINIAOD"] =  OD([
  ("crab_string",           "2018_2019Jun26_Tau__Run2018C-17Sep2018-v1"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "Tau_Run2018C_17Sep2018_v1"),
  ("nof_db_events",         31974422),
  ("nof_db_files",          525),
  ("fsize_db",              1270696103853),
  ("xsection",              None),
  ("use_it",                True),
  ("genWeight",             False),
  ("run_range",             [319337, 320065]),
  ("golden_run_range",      [319337, 320065]),
  ("comment",               "100.0%; status: VALID; size: 1.27TB; nevents: 31.97M; release: 10_2_4_patch1; last modified: 2018-10-22 12:02:05"),
])

meta_dictionary["/Tau/Run2018D-PromptReco-v2/MINIAOD"] =  OD([
  ("crab_string",           "2018prompt_2019Jun26_Tau__Run2018D-PromptReco-v2"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "Tau_Run2018D_PromptReco_v2"),
  ("nof_db_events",         167889795),
  ("nof_db_files",          2372),
  ("fsize_db",              6001276268600),
  ("xsection",              None),
  ("use_it",                True),
  ("genWeight",             False),
  ("run_range",             [320497, 325175]),
  ("golden_run_range",      [320673, 325172]),
  ("comment",               "100.0%; status: VALID; size: 6.00TB; nevents: 167.89M; release: 10_2_1,10_2_5_patch1; last modified: 2018-08-01 10:55:12"),
])

