#!/usr/bin/env python

from tthAnalysis.HiggsToTauTau.common import load_samples

import ROOT

import collections
import prettytable
import copy
import os

MODES = [ 'stxsOnly', 'inclusiveOnly' ]
BASEDIR = '/hdfs/local/karl/ttHAnalysis/{era}/2020Nov27/histograms'
OUTPUTDIR = os.path.join(os.getenv('HOME'), 'stxs_rescaled')

CHANNELS = collections.OrderedDict([
  ('0l_2tau',   {
    'dir' : 'Tight_OS',
    'title' : 'OS_Tight',
    'fitvar' : 'mvaOutput_Legacy',
  }),
  ('1l_1tau',   {
    'dir' : 'Tight_disabled',
    'title' : 'Tight',
    'fitvar' : 'mvaOutput_Legacy_6',
  }),
  ('1l_2tau',   {
    'dir' : 'Tight_OS',
    'title' : 'OS_Tight',
    'fitvar' : 'mvaOutput_legacy',
  }),
  ('2l_2tau',   {
    'dir' : 'Tight_sumOS',
    'title' : 'sumOS_Tight',
    'fitvar' : 'mvaOutput_final',
    'file' : 'lepdisabled_taudisabled_Tight_sumOS',
  }),
  ('2los_1tau', {
    'dir' : 'Tight',
    'title' : 'Tight',
    'fitvar' : 'mvaOutput_legacy',
  }),
  ('2lss_1tau', {
    'dir' : 'Tight_SS_OS',
    'title' : 'lepSS_sumOS_Tight',
    'fitvar' : {
      'rest' : 'output_NN_rest',
      'tH'  : 'output_NN_tH',
      'ttH' : 'output_NN_ttH',
    },
    'file' : 'Tight_lepSS_sumOS',
  }),
  ('3l_1tau',   {
    'dir' : 'Tight_OS',
    'title' : 'OS_lepTight_hadTauTight',
    'fitvar' : 'mvaOutput_legacy',
  }),
])

PROCS = [ 'ttH', 'ggH', 'qqH', 'VH', 'WH', 'ZH' ]
DMS = [ 'htt', 'hzz', 'hww', 'hzg', 'hmm' ]

STXS_RENAME = {
  'QQ2HLNU' : '',
  'QQ2HLL'  : '',
  'QQ2HQQ'  : 'had',
}

def mkdir_p(dname):
  if not os.path.isdir(dname):
    os.makedirs(dname)

def get_counts(counts, key, proc_cat):
  result = collections.OrderedDict()
  result['central'] = counts[key][0]
  result['pileupUp'] = counts[key][1]
  result['pileupDown'] = counts[key][2]
  key_l1pref = key.replace('L1PrefireNom', 'L1Prefire')
  if key_l1pref in counts:
    result['l1PreFireUp'] = counts[key_l1pref][1]
    result['l1PreFireDown'] = counts[key_l1pref][2]
  key_lhe = key.replace('CountWeighted', 'CountWeightedLHEEnvelope')
  if key_lhe in counts and proc_cat.lower() == 'tth':
    result['thu_shape_ttHUp'] = counts[key_lhe][0]
    result['thu_shape_ttHDown'] = counts[key_lhe][1]
  return result

def rename_bin(key):
  key = key.replace('to', '_').replace('pt', 'PTH_').replace('fwd', 'PTH_fwd')
  if 'Gt' in key:
    key = key.replace('Gt', '')
    key += '_infty'
  return key

def rescale(hadd_stage1_fn, output_fn, channel, sample_info, fitvar, mode):
  assert(mode in MODES)
  print('Rescaling: {}'.format(hadd_stage1_fn))
  inputf = ROOT.TFile.Open(hadd_stage1_fn, 'read')
  dir_title = '{}_{}'.format(channel, CHANNELS[channel]['title'])
  dirptr = inputf.Get(os.path.join(dir_title, 'sel', 'evt'))
  assert(dirptr)

  cat = sample_info['cat']
  name = sample_info['name']
  xs = sample_info['xs']

  dirkeys = [ k.GetName() for k in dirptr.GetListOfKeys() ]
  hists = collections.OrderedDict()
  for dirkey in dirkeys:
    if cat != 'VH':
      assert(cat in dirkey)
    else:
      assert('WH' in dirkey or 'ZH' in dirkey or 'VH' in dirkey)
    if any(region_type in dirkey for region_type in [ 'Convs', 'flip' ]) or \
        ('fake' in dirkey and 'faketau' not in dirkey) or \
        'VH' in dirkey or \
        'GG2HLL' in dirkey:
      continue
    if cat == 'VH':
      if name.startswith('/WH'):
        if'WH' not in dirkey:
          continue
      if 'QQ2HLL' in dirkey and 'WH' in dirkey:
        continue
      if name.startswith('/ZH'):
        if'ZH' not in dirkey:
          continue
      if 'QQ2HLNU' in dirkey and 'ZH' in dirkey:
        continue
      if name.startswith('/ZH_HToBB_ZToLL') and 'QQ2HQQ' in dirkey:
        continue

    if (mode == 'stxsOnly' and not dirkey.startswith('htxs')) or (mode == 'inclusiveOnly' and dirkey.startswith('htxs')):
      continue

    prefix = dirkey
    stxs_bin = ''
    if dirkey.startswith('htxs'):
      proc_name = ''
      dirkey_split = dirkey.split('_')
      tau_match = ''
      dm = ''
      if dirkey_split[-1] in [ 'gentau', 'faketau' ]:
        assert(channel in [ '2lss_1tau', '3l_1tau' ])
        tau_match = dirkey_split[-1]
        dirkey_split = dirkey_split[:-1]
      if dirkey_split[-1] in DMS:
        # exclusive in STXS, exclusive in Higgs decay mode
        dm = dirkey_split[-1]
        dirkey_split = dirkey_split[:-1]

      assert(dirkey_split[-1] in PROCS)
      proc_name = dirkey_split[-1]
      stxs_bin = '_'.join(dirkey_split[1:-1])

      prefix = '{}_{}'.format(proc_name, stxs_bin)
      if dm:
        prefix += '_{}'.format(dm)
      if tau_match:
        prefix += '_{}'.format(tau_match)

      if stxs_bin not in sample_info['counts']:
        raise RuntimeError("Unable to find STXS bin %s; available bins are: %s" % (stxs_bin, ', '.join(sample_info["counts"])))

      assert(proc_name)
      if cat != 'VH':
        assert(proc_name == cat)
      else:
        assert(proc_name in ['WH', 'ZH'])
        assert(any(stxs_rename in prefix for stxs_rename in STXS_RENAME))
        for stxs_rename in STXS_RENAME:
          if stxs_rename in prefix:
            prefix = prefix.replace(stxs_rename, STXS_RENAME[stxs_rename])
            while '__' in prefix:
              prefix = prefix.replace('__', '_')
            break

    dirkey_ptr = dirptr.Get(dirkey)
    hist_names = [ histkey.GetName() for histkey in dirkey_ptr.GetListOfKeys() ]
    for hist_name in hist_names:
      if not hist_name.endswith(fitvar):
        continue
      hist_name_new = '{}_{}'.format(prefix, hist_name.replace(fitvar, ''))
      if hist_name_new.endswith('_'):
        hist_name_new = hist_name_new[:-1]

      if hist_name_new in hists:
        raise RuntimeError("Found duplicate histogram name (%s, %s -> %s)" % (dirkey, hist_name, hist_name_new))

      hist = dirkey_ptr.Get(hist_name)
      hist.SetDirectory(0)
      hist.SetTitle(hist_name_new)
      hist.SetName(hist_name_new)

      if stxs_bin:
        syst_name = 'central'
        for syst in sample_info['counts']['inclusive']:
          syst_cand = 'CMS_ttHl_{}'.format(syst)
          if syst_cand in hist_name_new:
            syst_name = syst
            break
        sf = xs * sample_info['counts'][stxs_bin][syst_name] / sample_info['counts']['inclusive'][syst_name]
        hist.Scale(sf)

      hists[hist_name_new] = hist

  inputf.Close()

  outputf = ROOT.TFile.Open(output_fn, 'recreate')
  outputf.cd()
  for hist_name in sorted(hists.keys()):
    hists[hist_name].Write()
  outputf.Close()
  print("  => {}".format(output_fn))

results = collections.OrderedDict()

for era in list(map(str, range(2016, 2019))):
  samples = load_samples(era)

  count_key_base = 'CountWeighted{}'.format('L1PrefireNom' if era != '2018' else '')
  results[era] = collections.OrderedDict()

  sample_remap = {}
  for sample_key, sample_info in samples.items():
    if sample_key == 'sum_events':
      continue

    proc_cat = sample_info['sample_category']
    proc_name = sample_info['process_name_specific']
    sample_remap[proc_name] = sample_key

    if not (proc_cat in PROCS and sample_info['use_it']):
      continue

    nof_events = sample_info['nof_events']
    results[era][proc_name] = {
      'name'   : sample_key,
      'xs'     : sample_info['xsection'],
      'cat'    : proc_cat,
      'counts' : collections.OrderedDict(),
    }
    for count_key in nof_events:
      if count_key == count_key_base:
        results[era][proc_name]['counts']['inclusive'] = get_counts(nof_events, count_key, proc_cat)
      elif count_key.startswith('{}_'.format(count_key_base)):
        bin_name = count_key[count_key.find('_') + 1:]
        if proc_cat.lower() == 'tth':
          bin_name = rename_bin(bin_name)
        results[era][proc_name]['counts'][bin_name] = get_counts(nof_events, count_key, proc_cat)

  for common_procs in samples['sum_events']:
    if any(proc in results[era] for proc in common_procs):
      assert(all(samples[sample_remap[proc]]['use_it'] for proc in common_procs))
      counts = None
      xs = -1.
      for proc in common_procs:
        if not counts:
          counts = copy.deepcopy(results[era][proc]['counts'])
          xs = results[era][proc]['xs']
        else:
          assert(xs == results[era][proc]['xs'])
          assert(all(bin_name in counts for bin_name in results[era][proc]['counts']))
          for bin_name in results[era][proc]['counts']:
            assert(all(syst_name in counts[bin_name] for syst_name in results[era][proc]['counts'][bin_name]))
            for syst_name in results[era][proc]['counts'][bin_name]:
              counts[bin_name][syst_name] += results[era][proc]['counts'][bin_name][syst_name]
      assert(counts)
      for proc in common_procs:
        results[era][proc]['counts'] = counts

for era in results:
  for proc_name in results[era]:
    nof_events = results[era][proc_name]['counts']
    xs = results[era][proc_name]['xs']
    assert('inclusive' in nof_events)
    systs = list(nof_events['inclusive'].keys())
    table = prettytable.PrettyTable([ '{} ({})'.format(proc_name, era) ] + systs)
    for bin_name in nof_events:
      if bin_name == 'inclusive':
        continue
      row = [ bin_name ] + [
        '{:.3e}'.format(xs * nof_events[bin_name][syst] / nof_events['inclusive'][syst]) for syst in systs
      ]
      table.add_row(row)
    #print(table)

  era_dir = os.path.join(OUTPUTDIR, era)
  mkdir_p(era_dir)
  bdir = BASEDIR.format(era = era)
  for channel in CHANNELS:
    if channel not in [ '0l_2tau', '2lss_1tau', '3l_1tau' ]: continue
    region = CHANNELS[channel]['dir']
    file_suffix = CHANNELS[channel]['file'] if 'file' in CHANNELS[channel] else region

    region_dir = os.path.join(bdir, channel, region)
    if not os.path.isdir(region_dir):
      raise RuntimeError("No such directory: %s" % region_dir)
    proc_names = [ dname for dname in os.listdir(region_dir) if dname != 'hadd' ]
    if not all(proc_name in results[era] for proc_name in proc_names):
      missing_procs = [ proc_name for proc_name in proc_names if proc_name not in results[era] ]
      raise RuntimeError("No event counts found for sample %s in era %s" % (proc_name, era))
    for proc_name in proc_names:
      hadd_stage1_fn = os.path.join(region_dir, proc_name, 'hadd_stage1_{}_{}.root'.format(proc_name, file_suffix))
      if not os.path.isfile(hadd_stage1_fn):
        raise RuntimeError("No such file found: %s" % hadd_stage1_fn)
      subchannels = {}
      if type(CHANNELS[channel]['fitvar']) == str:
        subchannels[channel] = CHANNELS[channel]['fitvar']
      elif type(CHANNELS[channel]['fitvar']) == dict:
        for fitvar in CHANNELS[channel]['fitvar']:
          subchannels['{}_{}'.format(channel, fitvar)] = CHANNELS[channel]['fitvar'][fitvar]
      else:
        assert(False)
      for subchannel in subchannels:
        for mode in MODES:
          output_fn = os.path.join(era_dir, 'hadd_stage1_rescaled_{}_{}_{}.root'.format(subchannel, proc_name, mode))
          rescale(hadd_stage1_fn, output_fn, channel, results[era][proc_name], subchannels[subchannel], mode)
