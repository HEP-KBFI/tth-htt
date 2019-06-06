import copy

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

def add_part(arr, idx):
  return list(map(lambda sample_name: '%s_part%d' % (sample_name, idx), arr))

nof_parts = 2
for part_idx in range(1, nof_parts + 1):
  samples_part = copy.deepcopy(samples_to_stitch_WJets_2017[0])
  samples_part['inclusive']['samples'] = add_part(samples_part['inclusive']['samples'], part_idx)
  for split_key in [ 'LHE_Njets', 'LHE_HT' ]:
    for split_samples in samples_part[split_key]:
      split_samples['samples'] = add_part(split_samples['samples'], part_idx)
  samples_to_stitch_WJets_2017.append(samples_part)

samples_to_stitch_2017 = []
samples_to_stitch_2017.extend(samples_to_stitch_DYJets_2017)
samples_to_stitch_2017.extend(samples_to_stitch_WJets_2017)

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
