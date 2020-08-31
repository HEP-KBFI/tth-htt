HT_BINNING = [ 0., 70., 100., 200., 400., 600., 800., 1200., 2500., 100000. ]

samples_to_stitch_2016 = [
  {
    'inclusive' : {
      'samples'   : [ 'DYJetsToLL_M-50_ext1', 'DYJetsToLL_M-50_ext2' ],
      'LHE_Njets' : list(range(6)),
      'LHE_HT'    : HT_BINNING,
    },
    'exclusive' : {
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
    'order' : 'LO',
    'meta' : 'DY',
  },
  {
    'inclusive' : {
      'samples' : [ 'DYJetsToLL_M-10to50' ],
      'LHE_Njets' : list(range(6)),
    },
    'exclusive' : {
      'LHE_Njets'    : [
        { 'value' : [ 1, 2 ], 'samples' : [ 'DY1JetsToLL_M-10to50' ] },
        { 'value' : [ 2, 3 ], 'samples' : [ 'DY2JetsToLL_M-10to50' ] },
        { 'value' : [ 3, 4 ], 'samples' : [ 'DY3JetsToLL_M-10to50' ] },
        { 'value' : [ 4, 5 ], 'samples' : [ 'DY4JetsToLL_M-10to50' ] },
      ],
    },
    'order' : 'LO',
    'meta' : 'DY (low mll)',
  },
  {
    'inclusive' : {
      'samples'   : [ 'WJetsToLNu_madgraphMLM', 'WJetsToLNu_madgraphMLM_ext2' ],
      'LHE_Njets' : list(range(6)),
      'LHE_HT'    : HT_BINNING,
    },
    'exclusive' : {
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
    'order' : 'LO',
    'meta' : 'W+jets',
  },
  {
    'inclusive' : {
      'samples' : [ 'DYJetsToLL_M-50_amcatnloFXFX_ext2' ],
      'LHE_Njets' : list(range(5)),
    },
    'exclusive' : {
      'LHE_Njets' : [
        { 'value' : [ 0, 1, 2 ], 'samples' : [ 'DYToLL_0J_ext1', 'DYToLL_0J_backup', ] },
        { 'value' : [ 1, 2, 3 ], 'samples' : [ 'DYToLL_1J_ext1', 'DYToLL_1J_backup', ] },
        { 'value' : [ 2, 3, 4 ], 'samples' : [ 'DYToLL_2J',      'DYToLL_2J_ext1'    ] },
      ],
    },
    'order' : 'NLO',
    'meta' : 'DY',
  },
]
samples_to_stitch_2017 =  [
  {
    'inclusive' : {
      'samples'   : [ 'DYJetsToLL_M-50', 'DYJetsToLL_M-50_ext1' ],
      'LHE_Njets' : list(range(6)),
      'LHE_HT'    : HT_BINNING,
    },
    'exclusive' : {
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
    'order' : 'LO',
    'meta' : 'DY',
  },
  {
    'inclusive' : {
      'samples'   : [ 'WJetsToLNu_madgraphMLM', 'WJetsToLNu_madgraphMLM_ext1' ],
      'LHE_Njets' : list(range(6)),
      'LHE_HT'    : HT_BINNING,
    },
    'exclusive' : {
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
    'order' : 'LO',
    'meta' : 'W+jets',
  },
  {
    'inclusive' : {
      'samples' : [ 'DYJetsToLL_M-50_amcatnloFXFX', 'DYJetsToLL_M-50_amcatnloFXFX_ext1' ],
      'LHE_Njets' : list(range(5)),
    },
    'exclusive' : {
      'LHE_Njets' : [
        { 'value' : [ 0, 1, 2 ], 'samples' : [ 'DYToLL_0J' ] },
        { 'value' : [ 1, 2, 3 ], 'samples' : [ 'DYToLL_1J' ] },
        { 'value' : [ 2, 3, 4 ], 'samples' : [ 'DYToLL_2J' ] },
      ],
    },
    'order' : 'NLO',
    'meta' : 'DY',
  },
]

samples_to_stitch_2018 = [
  {
    'inclusive' : {
      'samples'   : [ 'DYJetsToLL_M-50' ],
      'LHE_Njets' : list(range(6)),
      'LHE_HT'    : HT_BINNING,
    },
    'exclusive' : {
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
    'order' : 'LO',
    'meta' : 'DY',
  },
  {
    'inclusive' : {
      'samples'   : [ 'WJetsToLNu_madgraphMLM' ],
      'LHE_Njets' : list(range(6)),
      'LHE_HT'    : HT_BINNING,
    },
    'exclusive' : {
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
    'order' : 'LO',
    'meta' : 'W+jets',
  },
  {
    'inclusive' : {
      'samples' : [ 'DYJetsToLL_M-50_amcatnloFXFX', 'DYJetsToLL_M-50_amcatnloFXFX_ext2' ],
      'LHE_Njets' : list(range(5)),
    },
    'exclusive' : {
      'LHE_Njets' : [
        { 'value' : [ 0, 1, 2 ], 'samples' : [ 'DYToLL_0J' ] },
        { 'value' : [ 1, 2, 3 ], 'samples' : [ 'DYToLL_1J' ] },
        { 'value' : [ 2, 3, 4 ], 'samples' : [ 'DYToLL_2J' ] },
      ],
    },
    'order' : 'NLO',
    'meta' : 'DY',
  },
]

samples_to_stitch_lo_2016 = [ samples for samples in samples_to_stitch_2016 if samples['order'] == 'LO' ]
samples_to_stitch_lo_2017 = [ samples for samples in samples_to_stitch_2017 if samples['order'] == 'LO' ]
samples_to_stitch_lo_2018 = [ samples for samples in samples_to_stitch_2018 if samples['order'] == 'LO' ]

samples_to_stitch_nlo_2016 = [ samples for samples in samples_to_stitch_2016 if samples['order'] == 'NLO' ]
samples_to_stitch_nlo_2017 = [ samples for samples in samples_to_stitch_2017 if samples['order'] == 'NLO' ]
samples_to_stitch_nlo_2018 = [ samples for samples in samples_to_stitch_2018 if samples['order'] == 'NLO' ]

def get_branch_type(branch_name):
  if not branch_name:
    return ''
  elif branch_name == 'LHE_Njets':
    return 'UChar_t'
  elif branch_name == 'LHE_HT':
    return 'Float_t'
  else:
    raise ValueError('Unrecognized branch name: %s' % branch_name)
