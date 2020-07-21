#!/usr/bin/env python

from tthAnalysis.HiggsToTauTau.common import load_samples

event_sums = {}
nof_events = {}
xs = -1.
for era in list(map(str, range(2016, 2019))):
  count_key_base = 'CountWeighted{}'.format('L1PrefireNom' if era != '2018' else '')
  nof_events[era] = {}
  count_keys = ( '{}_pt'.format(count_key_base), '{}_fwd'.format(count_key_base))
  
  samples = load_samples(era)
  for sample_key, sample_info in samples.items():
    if sample_key == 'sum_events':
      continue
    if not sample_info['process_name_specific'].startswith('ttHJetToNonbb_M125_amcatnlo'):
      continue
    if xs < 0.:
      xs = sample_info['xsection']
    else:
      assert(xs == sample_info['xsection'])
    for count_key in sample_info['nof_events']:
      if count_key == count_key_base:
        assert(era not in event_sums)
        event_sums[era] = sample_info['nof_events'][count_key][0]
        continue
      if not count_key.startswith(count_keys):
        continue
      count_key_new = count_key.replace('{}_'.format(count_key_base), '')
      assert(count_key_new not in nof_events[era])
      nof_events[era][count_key_new] = sample_info['nof_events'][count_key][0]

assert(xs > 0.)
print('{:<12} -> {:>8}   {:>8}   {:>8}'.format('BIN', *(era for era in nof_events)))
print('-' * 46)
for count_key in sorted(nof_events['2016'].keys()):
  print('{:<12} -> {:.6f}   {:.6f}   {:.6f}'.format(
    count_key, *(nof_events[era][count_key] * xs / event_sums[era] for era in nof_events)
  ))
