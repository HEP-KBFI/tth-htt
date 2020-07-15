samples_to_stitch_DYJets_NLO_2016 = {
  'inclusive' : {
    'samples' : [ 'DYJetsToLL_M-50_amcatnloFXFX_ext2' ],
    'LHE_Njets' : [ 0, 4 ],
  },
  'LHE_Njets' : [
    { 'value' : [ 0, 2 ], 'samples' : [ 'DYToLL_0J_ext1', 'DYToLL_0J_backup', ] },
    { 'value' : [ 1, 3 ], 'samples' : [ 'DYToLL_1J_ext1', 'DYToLL_1J_backup', ] },
    { 'value' : [ 2, 4 ], 'samples' : [ 'DYToLL_2J',      'DYToLL_2J_ext1'    ] },
  ],
}

samples_to_stitch_DYJets_NLO_2017 = {
  'inclusive' : {
    'samples' : [ 'DYJetsToLL_M-50_amcatnloFXFX', 'DYJetsToLL_M-50_amcatnloFXFX_ext1' ],
    'LHE_Njets' : [ 0, 4 ],
  },
  'LHE_Njets' : [
    { 'value' : [ 0, 2 ], 'samples' : [ 'DYToLL_0J' ] },
    { 'value' : [ 1, 3 ], 'samples' : [ 'DYToLL_1J' ] },
    { 'value' : [ 2, 4 ], 'samples' : [ 'DYToLL_2J' ] },
  ],
}

samples_to_stitch_DYJets_NLO_2018 = {
  'inclusive' : {
    'samples' : [ 'DYJetsToLL_M-50_amcatnloFXFX', 'DYJetsToLL_M-50_amcatnloFXFX_ext2' ],
    'LHE_Njets' : [ 0, 4 ],
  },
  'LHE_Njets' : [
    { 'value' : [ 0, 2 ], 'samples' : [ 'DYToLL_0J' ] },
    { 'value' : [ 1, 3 ], 'samples' : [ 'DYToLL_1J' ] },
    { 'value' : [ 2, 4 ], 'samples' : [ 'DYToLL_2J' ] },
  ],
}

samples_to_stitch_nlo_2016 = []
samples_to_stitch_nlo_2016.append(samples_to_stitch_DYJets_NLO_2016)

samples_to_stitch_nlo_2017 = []
samples_to_stitch_nlo_2017.append(samples_to_stitch_DYJets_NLO_2017)

samples_to_stitch_nlo_2018 = []
samples_to_stitch_nlo_2018.append(samples_to_stitch_DYJets_NLO_2018)
