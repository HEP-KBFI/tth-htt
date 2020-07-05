from tthAnalysis.HiggsToTauTau.samples.stitch_lo import samples_to_stitch_lo_2016, samples_to_stitch_lo_2017, samples_to_stitch_lo_2018
from tthAnalysis.HiggsToTauTau.samples.stitch_nlo import samples_to_stitch_nlo_2016, samples_to_stitch_nlo_2017, samples_to_stitch_nlo_2018

samples_to_stitch_2016 = samples_to_stitch_lo_2016 + samples_to_stitch_nlo_2016
samples_to_stitch_2017 = samples_to_stitch_lo_2017 + samples_to_stitch_nlo_2017
samples_to_stitch_2018 = samples_to_stitch_lo_2018 + samples_to_stitch_nlo_2018

def get_branch_type(branch_name):
  if not branch_name:
    return ''
  elif branch_name == 'LHE_Njets':
    return 'UChar_t'
  elif branch_name == 'LHE_HT':
    return 'Float_t'
  else:
    raise ValueError('Unrecognized branch name: %s' % branch_name)
