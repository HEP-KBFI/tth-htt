#!/usr/bin/env python

import os
import sys
import copy
import logging

CHANNEL_OPTIONS = {
  '0l_2tau' : {
    'SR'           : 'Tight_OS',
    'Fake AR'      : 'Fakeable_wFakeRateWeights_OS',
    'MC closure t' : 'Fakeable_mcClosure_t_wFakeRateWeights_OS',
  },
  '1l_2tau' : {
    'SR'           : 'Tight_OS',
    'Fake AR'      : 'Fakeable_wFakeRateWeights_OS',
    'MC closure e' : 'Fakeable_mcClosure_e_wFakeRateWeights_OS',
    'MC closure m' : 'Fakeable_mcClosure_m_wFakeRateWeights_OS',
    'MC closure t' : 'Fakeable_mcClosure_t_wFakeRateWeights_OS',
  },
  '2l_2tau' : {
    'SR'           : 'Tight_sumOS',
    'Fake AR'      : 'Fakeable_wFakeRateWeights_sumOS',
    'MC closure e' : 'Fakeable_mcClosure_e_wFakeRateWeights_sumOS',
    'MC closure m' : 'Fakeable_mcClosure_m_wFakeRateWeights_sumOS',
    'MC closure t' : 'Fakeable_mcClosure_t_wFakeRateWeights_sumOS',
  },
  '2lss' : {
    'SR'           : 'Tight_SS',
    'Fake AR'      : 'Fakeable_wFakeRateWeights_SS',
    'Charge flip'  : 'Tight_OS',
    'MC closure e' : 'Fakeable_mcClosure_e_wFakeRateWeights_SS',
    'MC closure m' : 'Fakeable_mcClosure_m_wFakeRateWeights_SS',
  },
  '2los_1tau' : {
    'SR'           : 'Tight',
    'Fake AR'      : 'Fakeable_wFakeRateWeights',
    'MC closure e' : 'Fakeable_mcClosure_e_wFakeRateWeights',
    'MC closure m' : 'Fakeable_mcClosure_m_wFakeRateWeights',
    'MC closure t' : 'Fakeable_mcClosure_t_wFakeRateWeights',
  },
  '2lss_1tau' : {
    'SR'           : 'Tight_SS_OS',
    'Fake AR'      : 'Fakeable_wFakeRateWeights_SS_OS',
    'Charge flip'  : 'Tight_OS_OS',
    'MC closure e' : 'Fakeable_mcClosure_e_wFakeRateWeights_SS_OS',
    'MC closure m' : 'Fakeable_mcClosure_m_wFakeRateWeights_SS_OS',
    'MC closure t' : 'Fakeable_mcClosure_t_wFakeRateWeights_SS_OS',
  },
  '3l' : {
    'SR'           : 'Tight_OS',
    'Fake AR'      : 'Fakeable_wFakeRateWeights_OS',
    'MC closure e' : 'Fakeable_mcClosure_e_wFakeRateWeights_OS',
    'MC closure m' : 'Fakeable_mcClosure_m_wFakeRateWeights_OS',
  },
  '3l_1tau' : {
    'SR'           : 'Tight_OS',
    'Fake AR'      : 'Fakeable_wFakeRateWeights_OS',
    'MC closure e' : 'Fakeable_mcClosure_e_wFakeRateWeights_OS',
    'MC closure m' : 'Fakeable_mcClosure_m_wFakeRateWeights_OS',
    'MC closure t' : 'Fakeable_mcClosure_t_wFakeRateWeights_OS',
  },
  '4l': {
    'SR'          : 'Tight_OS',
    'Fake AR'     : 'Fakeable_wFakeRateWeights_OS',
    'MC closure e': 'Fakeable_mcClosure_e_wFakeRateWeights_OS',
    'MC closure m': 'Fakeable_mcClosure_m_wFakeRateWeights_OS',
  },
  'ttWctrl' : {
    'SR'           : 'Tight_SS',
    'Fake AR'      : 'Fakeable_wFakeRateWeights_SS',
    'Charge flip'  : 'Tight_OS',
    'MC closure e' : 'Fakeable_mcClosure_e_wFakeRateWeights_SS',
    'MC closure m' : 'Fakeable_mcClosure_m_wFakeRateWeights_SS',
  },
  'ttZctrl' : {
    'SR'           : 'Tight',
    'Fake AR'      : 'Fakeable_wFakeRateWeights',
    'MC closure e' : 'Fakeable_mcClosure_e_wFakeRateWeights',
    'MC closure m' : 'Fakeable_mcClosure_m_wFakeRateWeights',
  },
  'WZctrl' : {
    'SR'           : 'Tight',
    'Fake AR'      : 'Fakeable_wFakeRateWeights',
    'MC closure e' : 'Fakeable_mcClosure_e_wFakeRateWeights',
    'MC closure m' : 'Fakeable_mcClosure_m_wFakeRateWeights',
  },
}

cfg_options = {
  '2l_2tau' : '/hdfs/local/karl/ttHAnalysis/2017/2018Jun26',
}

logging.basicConfig(
  stream = sys.stdout,
  level  = logging.DEBUG,
  format = '%(asctime)s - %(levelname)s: %(message)s',
)

rles = {}
for channel in cfg_options:
  logging.info('Inspecting channel {}'.format(channel))
  base_path = os.path.join(cfg_options[channel], 'output_rle', channel)
  if not os.path.isdir(base_path):
    raise ValueError('No such directory: %s' % base_path)
  rles[channel] = {}
  for region_name, region in CHANNEL_OPTIONS[channel].items():
    region_path = os.path.join(base_path, region)
    if not os.path.isdir(region_path):
      continue
    logging.info('Inspecting region {}'.format(region_name))
    rles[channel][region_name] = {}
    for sample_name in os.listdir(region_path):
      if sample_name != 'ttHJetToNonbb_M125_amcatnlo': continue
      logging.info('Inspecting sample {}'.format(sample_name))
      sample_path = os.path.join(region_path, sample_name)
      rles[channel][region_name][sample_name] = {}
      for rle_file in os.listdir(sample_path):
        rle_file_path = os.path.join(sample_path, rle_file)
        sys_option = ''
        if 'central' in rle_file:
          sys_option = 'central'
        elif 'CMS' in rle_file:
          sys_option = rle_file[rle_file.find('CMS') : rle_file.find(rle_file.split('_')[-1]) - 1]
        else:
          raise RuntimeError('Unrecognizable file: %s' % rle_file_path)
        assert(sys_option)

        rle_arr = set()
        with open(rle_file_path, 'r') as rle_file_ptr:
          for line in rle_file_ptr:
            rle_arr.add(line.rstrip('\n'))
        rles[channel][region_name][sample_name][sys_option] = copy.deepcopy(rle_arr)

      sys_options = list(sorted(rles[channel][region_name][sample_name].keys()))
      if 'central' in sys_options:
        sys_options.remove('central')
        sys_options = [ 'central' ] + sys_options
      header = [ '' ] + sys_options
      rows = [ header ]
      for sys_option_outer in sys_options:
        row = []
        row.append(sys_option_outer)
      for sys_option_outer in rles[channel][region_name][sample_name]:
        for sys_option_inner in rles[channel][region_name][sample_name]:
          outer_set = rles[channel][region_name][sample_name][sys_option_outer]
          inner_set = rles[channel][region_name][sample_name][sys_option_inner]
          logging.debug('{} vs {}: {} common, {} ({}) exclusively in {} ({})'.format(
            sys_option_outer, sys_option_inner, len(outer_set & inner_set),
            len(outer_set - inner_set), len(inner_set - outer_set), sys_option_outer, sys_option_inner
          ))



