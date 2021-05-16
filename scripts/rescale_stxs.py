#!/usr/bin/env python

from tthAnalysis.HiggsToTauTau.common import load_samples

import collections
import prettytable
import copy

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

    if not (proc_cat in ['ttH', 'ggH', 'qqH', 'VH', 'WH', 'ZH'] and sample_info['use_it']):
      continue

    nof_events = sample_info['nof_events']
    results[era][proc_name] = {
      'xs'     : sample_info['xsection'],
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
  print(era)
  for proc_name in results[era]:
    nof_events = results[era][proc_name]['counts']
    xs = results[era][proc_name]['xs']
    assert('inclusive' in nof_events)
    systs = list(nof_events['inclusive'].keys())
    table = prettytable.PrettyTable([ proc_name ] + systs)
    for bin_name in nof_events:
      if bin_name == 'inclusive':
        continue
      row = [ bin_name ] + [
        '{:.3e}'.format(xs * nof_events[bin_name][syst] / nof_events['inclusive'][syst]) for syst in systs
      ]
      table.add_row(row)
    print(table)
