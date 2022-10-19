from collections import OrderedDict as OD

# file generated at 2020-10-26 12:35:49 with the following command:
# create_dictionary.py -m python/samples/metaDict_2016_sync.py -p /local/karl/ttHNtupleProduction/2016/2020Oct26_woPresel_nonNom_tth_sync/ntuples -N samples_2016 -E 2016 -o python/samples -g tthAnalyzeSamples_2016_sync.py -M

samples_2016 = OD()
samples_2016["/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "ttH"),
  ("process_name_specific",           "ttHToNonbb_M125_powheg"),
  ("nof_files",                       1),
  ("nof_db_files",                    35),
  ("nof_events",                      {
    'Count'                                                                          : [ 77700, ],
    'CountWeighted'                                                                  : [ 7.62215859e+04, 7.62243594e+04, 7.62014844e+04, ],
    'CountWeightedLHEWeightScale'                                                    : [ 8.07497578e+04, 7.98802734e+04, 7.95600312e+04, 7.81780938e+04, 7.62215859e+04, 7.47790703e+04, 7.37387266e+04, 7.11818828e+04, 6.91620547e+04, ],
    'CountWeightedLHEEnvelope'                                                       : [ 8.83985469e+04, 6.34939727e+04, ],
    'CountWeightedFull'                                                              : [ 4.37314258e+04, 4.37351914e+04, 4.37203164e+04, ],
    'CountWeightedFullLHEWeightScale'                                                : [ 4.63339492e+04, 4.58348633e+04, 4.56511758e+04, 4.48582695e+04, 4.37314258e+04, 4.29078906e+04, 4.23106367e+04, 4.08443125e+04, 3.96848906e+04, ],
    'CountWeightedFullLHEEnvelope'                                                   : [ 5.07229023e+04, 3.64326328e+04, ],
    'CountWeightedL1PrefireNom'                                                      : [ 7.45196250e+04, 7.45266875e+04, 7.45034062e+04, ],
    'CountWeightedL1Prefire'                                                         : [ 7.45196250e+04, 7.40834531e+04, 7.49561484e+04, ],
    'CountWeightedLHEWeightScaleL1PrefireNom'                                        : [ 7.88878281e+04, 7.80649688e+04, 7.77760703e+04, 7.64148203e+04, 7.45196250e+04, 7.31370781e+04, 7.20990547e+04, 6.96213359e+04, 6.76637812e+04, ],
    'CountWeightedLHEEnvelopeL1PrefireNom'                                           : [ 8.63798984e+04, 6.21137500e+04, ],
    'CountWeightedFullL1PrefireNom'                                                  : [ 4.27568555e+04, 4.27621289e+04, 4.27474062e+04, ],
    'CountWeightedFullL1Prefire'                                                     : [ 4.27568555e+04, 4.25067734e+04, 4.30074570e+04, ],
    'CountWeightedFullLHEWeightScaleL1PrefireNom'                                    : [ 4.52656641e+04, 4.47936016e+04, 4.46275938e+04, 4.38465664e+04, 4.27568555e+04, 4.19652969e+04, 4.13702617e+04, 3.99483828e+04, 3.88253398e+04, ],
    'CountWeightedFullLHEEnvelopeL1PrefireNom'                                       : [ 4.95646445e+04, 3.56407969e+04, ],
    'Count_fwd'                                                                      : [ 1086, ],
    'CountWeighted_fwd'                                                              : [ 1.06692981e+03, 1.06302161e+03, 1.06999255e+03, ],
    'CountWeightedLHEWeightScale_fwd'                                                : [ 1.08291016e+03, 1.07884851e+03, 1.08143616e+03, 1.09486292e+03, 1.06692981e+03, 1.04762561e+03, 1.05860962e+03, 1.01815271e+03, 9.87119690e+02, ],
    'CountWeightedLHEEnvelope_fwd'                                                   : [ 1.21396362e+03, 8.79459961e+02, ],
    'CountWeightedFull_fwd'                                                          : [ 6.12203247e+02, 6.09959106e+02, 6.13961243e+02, ],
    'CountWeightedFullLHEWeightScale_fwd'                                            : [ 6.21371582e+02, 6.19041138e+02, 6.20526489e+02, 6.28230774e+02, 6.12203247e+02, 6.01126343e+02, 6.07428101e+02, 5.84213867e+02, 5.66406799e+02, ],
    'CountWeightedFullLHEEnvelope_fwd'                                               : [ 6.96570190e+02, 5.04632507e+02, ],
    'CountWeightedL1PrefireNom_fwd'                                                  : [ 9.79331299e+02, 9.76271912e+02, 9.81846680e+02, ],
    'CountWeightedL1Prefire_fwd'                                                     : [ 9.79331299e+02, 9.58078857e+02, 1.00091376e+03, ],
    'CountWeightedLHEWeightScaleL1PrefireNom_fwd'                                    : [ 9.92791870e+02, 9.89366943e+02, 9.92058960e+02, 1.00459027e+03, 9.79331299e+02, 9.61942078e+02, 9.71750183e+02, 9.35027100e+02, 9.06875366e+02, ],
    'CountWeightedLHEEnvelopeL1PrefireNom_fwd'                                       : [ 1.11402490e+03, 8.07158997e+02, ],
    'CountWeightedFullL1PrefireNom_fwd'                                              : [ 5.61938599e+02, 5.60183044e+02, 5.63381836e+02, ],
    'CountWeightedFullL1Prefire_fwd'                                                 : [ 5.61938599e+02, 5.49743408e+02, 5.74321716e+02, ],
    'CountWeightedFullLHEWeightScaleL1PrefireNom_fwd'                                : [ 5.69663269e+02, 5.67696411e+02, 5.69241394e+02, 5.76432190e+02, 5.61938599e+02, 5.51960999e+02, 5.57588013e+02, 5.36516479e+02, 5.20363098e+02, ],
    'CountWeightedFullLHEEnvelopeL1PrefireNom_fwd'                                   : [ 6.39226074e+02, 4.63146698e+02, ],
    'Count_pt0to60'                                                                  : [ 17948, ],
    'CountWeighted_pt0to60'                                                          : [ 1.76922324e+04, 1.77020332e+04, 1.76849512e+04, ],
    'CountWeightedLHEWeightScale_pt0to60'                                            : [ 1.87117344e+04, 1.85336289e+04, 1.85088262e+04, 1.80901152e+04, 1.76922324e+04, 1.74248828e+04, 1.70415508e+04, 1.65203594e+04, 1.61169199e+04, ],
    'CountWeightedLHEEnvelope_pt0to60'                                               : [ 2.04636953e+04, 1.48678027e+04, ],
    'CountWeightedFull_pt0to60'                                                      : [ 1.01516191e+04, 1.01573828e+04, 1.01477383e+04, ],
    'CountWeightedFullLHEWeightScale_pt0to60'                                        : [ 1.07367783e+04, 1.06345928e+04, 1.06203271e+04, 1.03800654e+04, 1.01516191e+04, 9.99832715e+03, 9.77840430e+03, 9.47932031e+03, 9.24785645e+03, ],
    'CountWeightedFullLHEEnvelope_pt0to60'                                           : [ 1.17420557e+04, 8.53114160e+03, ],
    'CountWeightedL1PrefireNom_pt0to60'                                              : [ 1.73503145e+04, 1.73609199e+04, 1.73424316e+04, ],
    'CountWeightedL1Prefire_pt0to60'                                                 : [ 1.73503145e+04, 1.72599531e+04, 1.74402891e+04, ],
    'CountWeightedLHEWeightScaleL1PrefireNom_pt0to60'                                : [ 1.83410410e+04, 1.81696465e+04, 1.81485430e+04, 1.77370391e+04, 1.73503145e+04, 1.70912070e+04, 1.67123809e+04, 1.62045117e+04, 1.58116543e+04, ],
    'CountWeightedLHEEnvelopeL1PrefireNom_pt0to60'                                   : [ 2.00567266e+04, 1.45898389e+04, ],
    'CountWeightedFullL1PrefireNom_pt0to60'                                          : [ 9.95550000e+03, 9.96163086e+03, 9.95115527e+03, ],
    'CountWeightedFullL1Prefire_pt0to60'                                             : [ 9.95550000e+03, 9.90366895e+03, 1.00071484e+04, ],
    'CountWeightedFullLHEWeightScaleL1PrefireNom_pt0to60'                            : [ 1.05240361e+04, 1.04257246e+04, 1.04135781e+04, 1.01774561e+04, 9.95550000e+03, 9.80687598e+03, 9.58955664e+03, 9.29811621e+03, 9.07267969e+03, ],
    'CountWeightedFullLHEEnvelopeL1PrefireNom_pt0to60'                               : [ 1.15085273e+04, 8.37161523e+03, ],
    'Count_pt60to120'                                                                : [ 27127, ],
    'CountWeighted_pt60to120'                                                        : [ 2.67056621e+04, 2.67144922e+04, 2.66943203e+04, ],
    'CountWeightedLHEWeightScale_pt60to120'                                          : [ 2.82614785e+04, 2.80192344e+04, 2.79737344e+04, 2.73239590e+04, 2.67056621e+04, 2.62688125e+04, 2.57287441e+04, 2.49103301e+04, 2.42695547e+04, ],
    'CountWeightedLHEEnvelope_pt60to120'                                             : [ 3.09063242e+04, 2.23653047e+04, ],
    'CountWeightedFull_pt60to120'                                                    : [ 1.53224297e+04, 1.53292744e+04, 1.53169131e+04, ],
    'CountWeightedFullLHEWeightScale_pt60to120'                                      : [ 1.62162100e+04, 1.60773154e+04, 1.60512314e+04, 1.56784795e+04, 1.53224297e+04, 1.50729863e+04, 1.47631201e+04, 1.42935527e+04, 1.39258164e+04, ],
    'CountWeightedFullLHEEnvelope_pt60to120'                                         : [ 1.77338984e+04, 1.28331934e+04, ],
    'CountWeightedL1PrefireNom_pt60to120'                                            : [ 2.61598438e+04, 2.61705273e+04, 2.61487266e+04, ],
    'CountWeightedL1Prefire_pt60to120'                                               : [ 2.61598438e+04, 2.60172969e+04, 2.63021211e+04, ],
    'CountWeightedLHEWeightScaleL1PrefireNom_pt60to120'                              : [ 2.76635430e+04, 2.74343750e+04, 2.73969902e+04, 2.67593848e+04, 2.61598438e+04, 2.57386641e+04, 2.52050957e+04, 2.44094727e+04, 2.37867109e+04, ],
    'CountWeightedLHEEnvelopeL1PrefireNom_pt60to120'                                 : [ 3.02613184e+04, 2.19159102e+04, ],
    'CountWeightedFullL1PrefireNom_pt60to120'                                        : [ 1.50097910e+04, 1.50168066e+04, 1.50039268e+04, ],
    'CountWeightedFullL1Prefire_pt60to120'                                           : [ 1.50097910e+04, 1.49280684e+04, 1.50914141e+04, ],
    'CountWeightedFullLHEWeightScaleL1PrefireNom_pt60to120'                          : [ 1.58731963e+04, 1.57417383e+04, 1.57203291e+04, 1.53544609e+04, 1.50097910e+04, 1.47687637e+04, 1.44626504e+04, 1.40061641e+04, 1.36487871e+04, ],
    'CountWeightedFullLHEEnvelopeL1PrefireNom_pt60to120'                             : [ 1.73637852e+04, 1.25753027e+04, ],
    'Count_pt120to200'                                                               : [ 19368, ],
    'CountWeighted_pt120to200'                                                       : [ 1.90307031e+04, 1.90037324e+04, 1.90522930e+04, ],
    'CountWeightedLHEWeightScale_pt120to200'                                         : [ 2.01976738e+04, 1.99546426e+04, 1.98395762e+04, 1.95570059e+04, 1.90307031e+04, 1.86415801e+04, 1.84487363e+04, 1.77778828e+04, 1.72453828e+04, ],
    'CountWeightedLHEEnvelope_pt120to200'                                            : [ 2.20903223e+04, 1.58260791e+04, ],
    'CountWeightedFull_pt120to200'                                                   : [ 1.09194756e+04, 1.09044355e+04, 1.09322393e+04, ],
    'CountWeightedFullLHEWeightScale_pt120to200'                                     : [ 1.15893486e+04, 1.14499648e+04, 1.13839727e+04, 1.12218018e+04, 1.09194756e+04, 1.06964951e+04, 1.05858359e+04, 1.02009277e+04, 9.89530273e+03, ],
    'CountWeightedFullLHEEnvelope_pt120to200'                                        : [ 1.26753262e+04, 9.08094727e+03, ],
    'CountWeightedL1PrefireNom_pt120to200'                                           : [ 1.86081094e+04, 1.85803672e+04, 1.86310742e+04, ],
    'CountWeightedL1Prefire_pt120to200'                                              : [ 1.86081094e+04, 1.84998828e+04, 1.87162559e+04, ],
    'CountWeightedLHEWeightScaleL1PrefireNom_pt120to200'                             : [ 1.97304551e+04, 1.95009629e+04, 1.93954199e+04, 1.91161523e+04, 1.86081094e+04, 1.82333340e+04, 1.80396875e+04, 1.73893301e+04, 1.68733145e+04, ],
    'CountWeightedLHEEnvelopeL1PrefireNom_pt120to200'                                : [ 2.15859219e+04, 1.54822344e+04, ],
    'CountWeightedFullL1PrefireNom_pt120to200'                                       : [ 1.06771436e+04, 1.06613955e+04, 1.06904805e+04, ],
    'CountWeightedFullL1Prefire_pt120to200'                                          : [ 1.06771436e+04, 1.06150459e+04, 1.07391846e+04, ],
    'CountWeightedFullLHEWeightScaleL1PrefireNom_pt120to200'                         : [ 1.13212715e+04, 1.11895918e+04, 1.11291064e+04, 1.09688213e+04, 1.06771436e+04, 1.04622617e+04, 1.03511611e+04, 9.97798926e+03, 9.68179004e+03, ],
    'CountWeightedFullLHEEnvelopeL1PrefireNom_pt120to200'                            : [ 1.23859385e+04, 8.88360449e+03, ],
    'Count_pt200to300'                                                               : [ 8261, ],
    'CountWeighted_pt200to300'                                                       : [ 8.03225391e+03, 8.03128174e+03, 8.03329980e+03, ],
    'CountWeightedLHEWeightScale_pt200to300'                                         : [ 8.54317578e+03, 8.42660352e+03, 8.35481250e+03, 8.28169727e+03, 8.03225391e+03, 7.83661279e+03, 7.83232910e+03, 7.51068994e+03, 7.24956592e+03, ],
    'CountWeightedLHEEnvelope_pt200to300'                                            : [ 9.38738086e+03, 6.57693848e+03, ],
    'CountWeightedFull_pt200to300'                                                   : [ 4.60884473e+03, 4.60825195e+03, 4.60958008e+03, ],
    'CountWeightedFullLHEWeightScale_pt200to300'                                     : [ 4.90204102e+03, 4.83516895e+03, 4.79397363e+03, 4.75201758e+03, 4.60884473e+03, 4.49663574e+03, 4.49417285e+03, 4.30962744e+03, 4.15979443e+03, ],
    'CountWeightedFullLHEEnvelope_pt200to300'                                        : [ 5.38645654e+03, 3.77383105e+03, ],
    'CountWeightedL1PrefireNom_pt200to300'                                           : [ 7.82845996e+03, 7.82854590e+03, 7.82819189e+03, ],
    'CountWeightedL1Prefire_pt200to300'                                              : [ 7.82845996e+03, 7.77760986e+03, 7.87939014e+03, ],
    'CountWeightedLHEWeightScaleL1PrefireNom_pt200to300'                             : [ 8.31530371e+03, 8.20655176e+03, 8.14077344e+03, 8.06759424e+03, 7.82845996e+03, 7.64103076e+03, 7.63405225e+03, 7.32379346e+03, 7.07188672e+03, ],
    'CountWeightedLHEEnvelopeL1PrefireNom_pt200to300'                                : [ 9.14085645e+03, 6.41431934e+03, ],
    'CountWeightedFullL1PrefireNom_pt200to300'                                       : [ 4.49193018e+03, 4.49197070e+03, 4.49184424e+03, ],
    'CountWeightedFullL1Prefire_pt200to300'                                          : [ 4.49193018e+03, 4.46274316e+03, 4.52115674e+03, ],
    'CountWeightedFullLHEWeightScaleL1PrefireNom_pt200to300'                         : [ 4.77129248e+03, 4.70889404e+03, 4.67116211e+03, 4.62917236e+03, 4.49193018e+03, 4.38439941e+03, 4.38040479e+03, 4.20238525e+03, 4.05783813e+03, ],
    'CountWeightedFullLHEEnvelopeL1PrefireNom_pt200to300'                            : [ 5.24500391e+03, 3.68052295e+03, ],
    'Count_ptGt300'                                                                  : [ 3910, ],
    'CountWeighted_ptGt300'                                                          : [ 3.68138062e+03, 3.69903442e+03, 3.66266357e+03, ],
    'CountWeightedLHEWeightScale_ptGt300'                                            : [ 3.95278320e+03, 3.86764209e+03, 3.80163794e+03, 3.83061255e+03, 3.68138062e+03, 3.55947632e+03, 3.62866992e+03, 3.44471069e+03, 3.29359497e+03, ],
    'CountWeightedLHEEnvelope_ptGt300'                                               : [ 4.33694727e+03, 2.97827319e+03, ],
    'CountWeightedFull_ptGt300'                                                      : [ 2.11239209e+03, 2.12250952e+03, 2.10159814e+03, ],
    'CountWeightedFullLHEWeightScale_ptGt300'                                        : [ 2.26810034e+03, 2.21924414e+03, 2.18137036e+03, 2.19799609e+03, 2.11239209e+03, 2.04242334e+03, 2.08212183e+03, 1.97656677e+03, 1.88986023e+03, ],
    'CountWeightedFullLHEEnvelope_ptGt300'                                           : [ 2.48853442e+03, 1.70893018e+03, ],
    'CountWeightedL1PrefireNom_ptGt300'                                              : [ 3.58713477e+03, 3.60443604e+03, 3.56881177e+03, ],
    'CountWeightedL1Prefire_ptGt300'                                                 : [ 3.58713477e+03, 3.56370557e+03, 3.61056665e+03, ],
    'CountWeightedLHEWeightScaleL1PrefireNom_ptGt300'                                : [ 3.84431738e+03, 3.76433765e+03, 3.70255347e+03, 3.73016724e+03, 3.58713477e+03, 3.47028223e+03, 3.53639551e+03, 3.35906177e+03, 3.21334229e+03, ],
    'CountWeightedLHEEnvelopeL1PrefireNom_ptGt300'                                   : [ 4.22093408e+03, 2.90414893e+03, ],
    'CountWeightedFullL1PrefireNom_ptGt300'                                          : [ 2.05830347e+03, 2.06822437e+03, 2.04776062e+03, ],
    'CountWeightedFullL1Prefire_ptGt300'                                             : [ 2.05830347e+03, 2.04485999e+03, 2.07174927e+03, ],
    'CountWeightedFullLHEWeightScaleL1PrefireNom_ptGt300'                            : [ 2.20586279e+03, 2.15996582e+03, 2.12451538e+03, 2.14035986e+03, 2.05830347e+03, 1.99124048e+03, 2.02917603e+03, 1.92742151e+03, 1.84381018e+03, ],
    'CountWeightedFullLHEEnvelopeL1PrefireNom_ptGt300'                               : [ 2.42196509e+03, 1.66639709e+03, ],
    'Count_pt300to450'                                                               : [ 3004, ],
    'CountWeighted_pt300to450'                                                       : [ 2.86785083e+03, 2.88568042e+03, 2.84927856e+03, ],
    'CountWeightedLHEWeightScale_pt300to450'                                         : [ 3.09899512e+03, 3.02415723e+03, 2.96889893e+03, 2.98688452e+03, 2.86785083e+03, 2.77225879e+03, 2.81850220e+03, 2.67575220e+03, 2.55953516e+03, ],
    'CountWeightedLHEEnvelope_pt300to450'                                            : [ 3.38923438e+03, 2.32303735e+03, ],
    'CountWeightedFull_pt300to450'                                                   : [ 1.64557910e+03, 1.65580237e+03, 1.63489453e+03, ],
    'CountWeightedFullLHEWeightScale_pt300to450'                                     : [ 1.77820044e+03, 1.73525793e+03, 1.70354614e+03, 1.71386621e+03, 1.64557910e+03, 1.59071777e+03, 1.61725195e+03, 1.53534314e+03, 1.46865613e+03, ],
    'CountWeightedFullLHEEnvelope_pt300to450'                                        : [ 1.94473682e+03, 1.33295508e+03, ],
    'CountWeightedL1PrefireNom_pt300to450'                                           : [ 2.79362134e+03, 2.81163452e+03, 2.77495703e+03, ],
    'CountWeightedL1Prefire_pt300to450'                                              : [ 2.79362134e+03, 2.77515527e+03, 2.81210107e+03, ],
    'CountWeightedLHEWeightScaleL1PrefireNom_pt300to450'                             : [ 3.01235156e+03, 2.94229468e+03, 2.89078198e+03, 2.90734326e+03, 2.79362134e+03, 2.70226270e+03, 2.74589600e+03, 2.60861865e+03, 2.49678638e+03, ],
    'CountWeightedLHEEnvelopeL1PrefireNom_pt300to450'                                : [ 3.29750220e+03, 2.26428027e+03, ],
    'CountWeightedFullL1PrefireNom_pt300to450'                                       : [ 1.60298108e+03, 1.61331348e+03, 1.59225720e+03, ],
    'CountWeightedFullL1Prefire_pt300to450'                                          : [ 1.60298108e+03, 1.59238318e+03, 1.61358350e+03, ],
    'CountWeightedFullLHEWeightScaleL1PrefireNom_pt300to450'                         : [ 1.72848523e+03, 1.68828223e+03, 1.65872485e+03, 1.66822681e+03, 1.60298108e+03, 1.55055310e+03, 1.57558984e+03, 1.49682129e+03, 1.43264990e+03, ],
    'CountWeightedFullLHEEnvelopeL1PrefireNom_pt300to450'                            : [ 1.89209998e+03, 1.29924097e+03, ],
    'Count_ptGt450'                                                                  : [ 906, ],
    'CountWeighted_ptGt450'                                                          : [ 8.13549744e+02, 8.13370117e+02, 8.13367065e+02, ],
    'CountWeightedLHEWeightScale_ptGt450'                                            : [ 8.53786438e+02, 8.43482544e+02, 8.32736755e+02, 8.43730835e+02, 8.13549744e+02, 7.87216736e+02, 8.10164368e+02, 7.68953491e+02, 7.34061829e+02, ],
    'CountWeightedLHEEnvelope_ptGt450'                                               : [ 9.47711731e+02, 6.55237366e+02, ],
    'CountWeightedFull_ptGt450'                                                      : [ 4.66813599e+02, 4.66710144e+02, 4.66710327e+02, ],
    'CountWeightedFullLHEWeightScale_ptGt450'                                        : [ 4.89900940e+02, 4.83988495e+02, 4.77823151e+02, 4.84131134e+02, 4.66813599e+02, 4.51703125e+02, 4.64871277e+02, 4.41223602e+02, 4.21203430e+02, ],
    'CountWeightedFullLHEEnvelope_ptGt450'                                           : [ 5.43795227e+02, 3.75973877e+02, ],
    'CountWeightedL1PrefireNom_ptGt450'                                              : [ 7.93522888e+02, 7.92813110e+02, 7.93844727e+02, ],
    'CountWeightedL1Prefire_ptGt450'                                                 : [ 7.93522888e+02, 7.88560974e+02, 7.98481201e+02, ],
    'CountWeightedLHEWeightScaleL1PrefireNom_ptGt450'                                : [ 8.31964905e+02, 8.22040955e+02, 8.11767578e+02, 8.22822632e+02, 7.93522888e+02, 7.68015137e+02, 7.90497864e+02, 7.50438354e+02, 7.16558350e+02, ],
    'CountWeightedLHEEnvelopeL1PrefireNom_ptGt450'                                   : [ 9.23437134e+02, 6.39871338e+02, ],
    'CountWeightedFullL1PrefireNom_ptGt450'                                          : [ 4.55322083e+02, 4.54914520e+02, 4.55507874e+02, ],
    'CountWeightedFullL1Prefire_ptGt450'                                             : [ 4.55322083e+02, 4.52475037e+02, 4.58167297e+02, ],
    'CountWeightedFullLHEWeightScaleL1PrefireNom_ptGt450'                            : [ 4.77379730e+02, 4.71685486e+02, 4.65791138e+02, 4.72133972e+02, 4.55322083e+02, 4.40685669e+02, 4.53586334e+02, 4.30600006e+02, 4.11160065e+02, ],
    'CountWeightedFullLHEEnvelopeL1PrefireNom_ptGt450'                               : [ 5.29866577e+02, 3.67157166e+02, ],
  }),
  ("nof_tree_events",                 77700),
  ("nof_db_events",                   3981250),
  ("fsize_local",                     515906656), # 515.91MB, avg file size 515.91MB
  ("fsize_db",                        208884155497), # 208.88GB, avg file size 5.97GB
  ("use_it",                          True),
  ("xsection",                        0.2118),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("nof_PSweights",                   1),
  ("LHE_set",                         "LHA IDs 260001 - 260100 -> NNPDF30_nlo_as_0118 PDF set, expecting 101 weights (counted 100 weights)"),
  ("nof_reweighting",                 0),
  ("local_paths",
    [
      OD([
        ("path",      "/local/karl/ttHNtupleProduction/2016/2020Oct26_woPresel_nonNom_tth_sync/ntuples/ttHToNonbb_M125_powheg"),
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

samples_2016["sum_events"] = [
]

