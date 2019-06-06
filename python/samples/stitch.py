import copy

samples_to_stitch_DYJets_2016 = [
  {
    'inclusive' : {
      'samples'   : [ 'DYJetsToLL_M-50_ext1', 'DYJetsToLL_M-50_ext2' ],
      'LHE_Njets' : [ 0, 5 ],
      'LHE_HT'    : [ 0., 100000. ],
    },
    'LHE_Njets' : [
      { 'value' : [ 1, 2 ], 'samples' : [ 'DY1JetsToLL_M-50' ] },
      { 'value' : [ 2, 3 ], 'samples' : [ 'DY2JetsToLL_M-50' ] },
      { 'value' : [ 3, 4 ], 'samples' : [ 'DY3JetsToLL_M-50' ] },
      { 'value' : [ 4, 5 ], 'samples' : [ 'DY4JetsToLL_M-50' ] },
    ],
    'LHE_HT'    : [
      { 'value' : [  100.,    200. ], 'samples' : [ 'DYJetsToLL_M50_HT100to200', 'DYJetsToLL_M50_HT100to200_ext1' ] },
      { 'value' : [  200.,    400. ], 'samples' : [ 'DYJetsToLL_M50_HT200to400', 'DYJetsToLL_M50_HT200to400_ext1' ] },
      { 'value' : [  400.,    600. ], 'samples' : [ 'DYJetsToLL_M50_HT400to600', 'DYJetsToLL_M50_HT400to600_ext1' ] },
      { 'value' : [  600.,    800. ], 'samples' : [ 'DYJetsToLL_M50_HT600to800'                                   ] },
      { 'value' : [  800.,   1200. ], 'samples' : [ 'DYJetsToLL_M50_HT800to1200'                                  ] },
      { 'value' : [ 1200.,   2500. ], 'samples' : [ 'DYJetsToLL_M50_HT1200to2500'                                 ] },
      { 'value' : [ 2500., 100000. ], 'samples' : [ 'DYJetsToLL_M50_HT2500toInf'                                  ] },
    ],
  },
  {
    'inclusive' : {
      'samples' : [ 'DYJetsToLL_M-10to50' ],
      'LHE_HT'  : [ 0., 100000. ]
    },
    'LHE_HT'    : [
      { 'value' : [ 100.,    200. ], 'samples' : [ 'DYJetsToLL_M-5to50_HT-100to200', 'DYJetsToLL_M-5to50_HT-100to200_ext1' ] },
      { 'value' : [ 200.,    400. ], 'samples' : [ 'DYJetsToLL_M-5to50_HT-200to400', 'DYJetsToLL_M-5to50_HT-200to400_ext1' ] },
      { 'value' : [ 400.,    600. ], 'samples' : [ 'DYJetsToLL_M-5to50_HT-400to600', 'DYJetsToLL_M-5to50_HT-400to600_ext1' ] },
      { 'value' : [ 600., 100000. ], 'samples' : [ 'DYJetsToLL_M-5to50_HT-600toInf', 'DYJetsToLL_M-5to50_HT-600toInf_ext1' ] },
    ],
  }
]

samples_to_stitch_WJets_2016 = [
  {
    'inclusive' : {
      'samples'   : [ 'WJetsToLNu_madgraphMLM', 'WJetsToLNu_madgraphMLM_ext2' ],
      'LHE_Njets' : [ 0, 5 ],
      'LHE_HT'    : [ 0., 100000. ],
    },
    'LHE_Njets' : [
      { 'value' : [ 1, 2 ], 'samples' : [ 'W1JetsToLNu'                     ] },
      { 'value' : [ 2, 3 ], 'samples' : [ 'W2JetsToLNu', 'W2JetsToLNu_ext1' ] },
      { 'value' : [ 3, 4 ], 'samples' : [ 'W3JetsToLNu', 'W3JetsToLNu_ext1' ] },
      { 'value' : [ 4, 5 ], 'samples' : [ 'W4JetsToLNu', 'W4JetsToLNu_ext2' ] },
    ],
    'LHE_HT'    : [
      { 'value' : [   70.,    100. ], 'samples' : [ 'WJetsToLNu_HT70To100'                                                                ] },
      { 'value' : [  100.,    200. ], 'samples' : [ 'WJetsToLNu_HT100To200',   'WJetsToLNu_HT100To200_ext1'                               ] },
      { 'value' : [  200.,    400. ], 'samples' : [ 'WJetsToLNu_HT200To400',   'WJetsToLNu_HT200To400_ext1', 'WJetsToLNu_HT200To400_ext2' ] },
      { 'value' : [  400.,    600. ], 'samples' : [ 'WJetsToLNu_HT400To600',   'WJetsToLNu_HT400To600_ext1'                               ] },
      { 'value' : [  600.,    800. ], 'samples' : [ 'WJetsToLNu_HT600To800',   'WJetsToLNu_HT600To800_ext1'                               ] },
      { 'value' : [  800.,   1200. ], 'samples' : [ 'WJetsToLNu_HT800To1200',  'WJetsToLNu_HT800To1200_ext1'                              ] },
      { 'value' : [ 1200.,   2500. ], 'samples' : [ 'WJetsToLNu_HT1200To2500', 'WJetsToLNu_HT1200To2500_ext1'                             ] },
      { 'value' : [ 2500., 100000. ], 'samples' : [ 'WJetsToLNu_HT2500ToInf',  'WJetsToLNu_HT2500ToInf_ext1'                              ] },
    ],
  },
]

samples_to_stitch_DYJets_2017 = [
  {
    'inclusive' : {
      'samples'   : [ 'DYJetsToLL_M-50', 'DYJetsToLL_M-50_ext1' ],
      'LHE_Njets' : [ 0, 5 ],
      'LHE_HT'    : [ 0., 100000. ],
    },
    'LHE_Njets' : [
      { 'value' : [ 1, 2 ], 'samples' : [ 'DY1JetsToLL_M-50', 'DY1JetsToLL_M-50_ext1' ] },
      { 'value' : [ 2, 3 ], 'samples' : [ 'DY2JetsToLL_M-50', 'DY2JetsToLL_M-50_ext1' ] },
      { 'value' : [ 3, 4 ], 'samples' : [ 'DY3JetsToLL_M-50', 'DY3JetsToLL_M-50_ext1' ] },
      { 'value' : [ 4, 5 ], 'samples' : [ 'DY4JetsToLL_M-50'                          ] },
    ],
    'LHE_HT'    : [
      { 'value' : [   70.,    100. ], 'samples' : [ 'DYJetsToLL_M50_HT70to100'                                    ] },
      { 'value' : [  100.,    200. ], 'samples' : [ 'DYJetsToLL_M50_HT100to200', 'DYJetsToLL_M50_HT100to200_ext1' ] },
      { 'value' : [  200.,    400. ], 'samples' : [ 'DYJetsToLL_M50_HT200to400', 'DYJetsToLL_M50_HT200to400_ext1' ] },
      { 'value' : [  400.,    600. ], 'samples' : [ 'DYJetsToLL_M50_HT400to600', 'DYJetsToLL_M50_HT400to600_ext1' ] },
      { 'value' : [  600.,    800. ], 'samples' : [ 'DYJetsToLL_M50_HT600to800'                                   ] },
      { 'value' : [  800.,   1200. ], 'samples' : [ 'DYJetsToLL_M50_HT800to1200'                                  ] },
      { 'value' : [ 1200.,   2500. ], 'samples' : [ 'DYJetsToLL_M50_HT1200to2500'                                 ] },
      { 'value' : [ 2500., 100000. ], 'samples' : [ 'DYJetsToLL_M50_HT2500toInf'                                  ] },
    ],
  },
  {
    'inclusive' : {
      'samples' : [ 'DYJetsToLL_M-10to50', 'DYJetsToLL_M-10to50_ext1' ],
      'LHE_HT'  : [ 0., 100000. ]
    },
    'LHE_HT'    : [
      { 'value' : [ 100.,    200. ], 'samples' : [ 'DYJetsToLL_M-4to50_HT-100to200', 'DYJetsToLL_M-4to50_HT-100to200_ext1' ] },
      { 'value' : [ 200.,    400. ], 'samples' : [ 'DYJetsToLL_M-4to50_HT-200to400', 'DYJetsToLL_M-4to50_HT-200to400_ext1' ] },
      { 'value' : [ 400.,    600. ], 'samples' : [ 'DYJetsToLL_M-4to50_HT-400to600', 'DYJetsToLL_M-4to50_HT-400to600_ext1' ] },
      { 'value' : [ 600., 100000. ], 'samples' : [ 'DYJetsToLL_M-4to50_HT-600toInf', 'DYJetsToLL_M-4to50_HT-600toInf_ext1' ] },
    ],
  }
]

samples_to_stitch_WJets_2017 = [
  {
    'inclusive' : {
      'samples'   : [ 'WJetsToLNu_madgraphMLM', 'WJetsToLNu_madgraphMLM_ext1' ],
      'LHE_Njets' : [ 0, 5 ],
      'LHE_HT'    : [ 0., 100000. ],
    },
    'LHE_Njets' : [
      { 'value' : [ 1, 2 ], 'samples' : [ 'W1JetsToLNu' ] },
      { 'value' : [ 2, 3 ], 'samples' : [ 'W2JetsToLNu' ] },
      { 'value' : [ 3, 4 ], 'samples' : [ 'W3JetsToLNu' ] },
      { 'value' : [ 4, 5 ], 'samples' : [ 'W4JetsToLNu' ] },
    ],
    'LHE_HT'    : [
      { 'value' : [   70.,    100. ], 'samples' : [ 'WJetsToLNu_HT70To100'    ] },
      { 'value' : [  100.,    200. ], 'samples' : [ 'WJetsToLNu_HT100To200'   ] },
      { 'value' : [  200.,    400. ], 'samples' : [ 'WJetsToLNu_HT200To400'   ] },
      { 'value' : [  400.,    600. ], 'samples' : [ 'WJetsToLNu_HT400To600'   ] },
      { 'value' : [  600.,    800. ], 'samples' : [ 'WJetsToLNu_HT600To800'   ] },
      { 'value' : [  800.,   1200. ], 'samples' : [ 'WJetsToLNu_HT800To1200'  ] },
      { 'value' : [ 1200.,   2500. ], 'samples' : [ 'WJetsToLNu_HT1200To2500' ] },
      { 'value' : [ 2500., 100000. ], 'samples' : [ 'WJetsToLNu_HT2500ToInf'  ] },
    ],
  },
]

samples_to_stitch_DYJets_2018 = [
  {
    'inclusive' : {
      'samples'   : [ 'DYJetsToLL_M-50' ],
      'LHE_Njets' : [ 0, 5 ],
      'LHE_HT'    : [ 0., 100000. ],
    },
    'LHE_Njets' : [
      { 'value' : [ 1, 2 ], 'samples' : [ 'DY1JetsToLL_M-50' ] },
      { 'value' : [ 2, 3 ], 'samples' : [ 'DY2JetsToLL_M-50' ] },
      { 'value' : [ 3, 4 ], 'samples' : [ 'DY3JetsToLL_M-50' ] },
      { 'value' : [ 4, 5 ], 'samples' : [ 'DY4JetsToLL_M-50' ] },
    ],
    'LHE_HT'    : [
      { 'value' : [   70.,    100. ], 'samples' : [ 'DYJetsToLL_M50_HT70to100_PSweights'                                              ] },
      { 'value' : [  100.,    200. ], 'samples' : [ 'DYJetsToLL_M50_HT100to200_PSweights'                                             ] },
      { 'value' : [  200.,    400. ], 'samples' : [ 'DYJetsToLL_M50_HT200to400_PSweights'                                             ] },
      { 'value' : [  400.,    600. ], 'samples' : [ 'DYJetsToLL_M50_HT400to600_PSweights', 'DYJetsToLL_M50_HT400to600_PSweights_ext2' ] },
      { 'value' : [  600.,    800. ], 'samples' : [ 'DYJetsToLL_M50_HT600to800_PSweights'                                             ] },
      { 'value' : [  800.,   1200. ], 'samples' : [ 'DYJetsToLL_M50_HT800to1200_PSweights'                                            ] },
      { 'value' : [ 1200.,   2500. ], 'samples' : [ 'DYJetsToLL_M50_HT1200to2500_PSweights'                                           ] },
      { 'value' : [ 2500., 100000. ], 'samples' : [ 'DYJetsToLL_M50_HT2500toInf_PSweights'                                            ] },
    ],
  },
  {
    'inclusive' : {
      'samples' : [ 'DYJetsToLL_M-10to50' ],
      'LHE_HT'  : [ 0., 100000. ]
    },
    'LHE_HT'    : [
      { 'value' : [ 100.,    200. ], 'samples' : [ 'DYJetsToLL_M-4to50_HT-100to200_PSweights' ] },
      { 'value' : [ 200.,    400. ], 'samples' : [ 'DYJetsToLL_M-4to50_HT-200to400_PSweights' ] },
      { 'value' : [ 400.,    600. ], 'samples' : [ 'DYJetsToLL_M-4to50_HT-400to600_PSweights' ] },
      { 'value' : [ 600., 100000. ], 'samples' : [ 'DYJetsToLL_M-4to50_HT-600toInf_PSweights' ] },
    ],
  }
]

samples_to_stitch_WJets_2018 = [
  {
    'inclusive' : {
      'samples'   : [ 'WJetsToLNu_madgraphMLM' ],
      'LHE_Njets' : [ 0, 5 ],
      'LHE_HT'    : [ 0., 100000. ],
    },
    'LHE_Njets' : [
      { 'value' : [ 1, 2 ], 'samples' : [ 'W1JetsToLNu' ] },
      { 'value' : [ 2, 3 ], 'samples' : [ 'W2JetsToLNu' ] },
      { 'value' : [ 3, 4 ], 'samples' : [ 'W3JetsToLNu' ] },
      { 'value' : [ 4, 5 ], 'samples' : [ 'W4JetsToLNu' ] },
    ],
    'LHE_HT'    : [
      { 'value' : [   70.,    100. ], 'samples' : [ 'WJetsToLNu_HT70To100'    ] },
      { 'value' : [  100.,    200. ], 'samples' : [ 'WJetsToLNu_HT100To200'   ] },
      { 'value' : [  200.,    400. ], 'samples' : [ 'WJetsToLNu_HT200To400'   ] },
      { 'value' : [  400.,    600. ], 'samples' : [ 'WJetsToLNu_HT400To600'   ] },
      { 'value' : [  600.,    800. ], 'samples' : [ 'WJetsToLNu_HT600To800'   ] },
      { 'value' : [  800.,   1200. ], 'samples' : [ 'WJetsToLNu_HT800To1200'  ] },
      { 'value' : [ 1200.,   2500. ], 'samples' : [ 'WJetsToLNu_HT1200To2500' ] },
      { 'value' : [ 2500., 100000. ], 'samples' : [ 'WJetsToLNu_HT2500ToInf'  ] },
    ],
  },
]

def add_part(arr, idx):
  return list(map(lambda sample_name: '%s_part%d' % (sample_name, idx), arr))

nof_parts = 2
eras = [ 2016, 2017, 2018 ]

for era in eras:
  for part_idx in range(1, nof_parts + 1):
    if era == 2016:
      samples_part = copy.deepcopy(samples_to_stitch_WJets_2016[0])
    elif era == 2017:
      samples_part = copy.deepcopy(samples_to_stitch_WJets_2017[0])
    elif era == 2018:
      samples_part = copy.deepcopy(samples_to_stitch_WJets_2018[0])
    else:
      raise RuntimeError("Invalid era: %d" % era)

    samples_part['inclusive']['samples'] = add_part(samples_part['inclusive']['samples'], part_idx)
    for split_key in [ 'LHE_Njets', 'LHE_HT' ]:
      for split_samples in samples_part[split_key]:
        split_samples['samples'] = add_part(split_samples['samples'], part_idx)

    if era == 2016:
      samples_to_stitch_WJets_2017.append(samples_part)
    elif era == 2017:
      samples_to_stitch_WJets_2017.append(samples_part)
    elif era == 2018:
      samples_to_stitch_WJets_2017.append(samples_part)
    else:
      raise RuntimeError("Invalid era: %d" % era)

samples_to_stitch_2016 = []
samples_to_stitch_2016.extend(samples_to_stitch_DYJets_2016)
samples_to_stitch_2016.extend(samples_to_stitch_WJets_2016)

samples_to_stitch_2017 = []
samples_to_stitch_2017.extend(samples_to_stitch_DYJets_2017)
samples_to_stitch_2017.extend(samples_to_stitch_WJets_2017)

samples_to_stitch_2018 = []
samples_to_stitch_2018.extend(samples_to_stitch_DYJets_2018)
samples_to_stitch_2018.extend(samples_to_stitch_WJets_2018)

def get_branch_type(branch_name):
  if not branch_name:
    return ''
  elif branch_name == 'LHE_Njets':
    return 'UChar_t'
  elif branch_name == 'LHE_HT':
    return 'Float_t'
  else:
    raise ValueError('Unrecognized branch name: %s' % branch_name)

# [*] not used b/c the sample was produced w/ incorrect gridpack (or, to be precise, w/ incorrect MG cards)
# see https://hypernews.cern.ch/HyperNews/CMS/get/generators/4005.html for more information
