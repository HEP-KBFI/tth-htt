#!/usr/bin/env python

from tthAnalysis.HiggsToTauTau.samples.stitch_2017 import samples_to_stitch_2017 as samples_to_stitch
from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017 import samples_2017 as samples

import ROOT
import array
import itertools
import copy

def comp_weights(f, samples_to_stitch, split_var):
  inclusive_samples  = samples_to_stitch['inclusive']['samples']
  inclusive_binning  = samples_to_stitch['inclusive'][split_var]

  split_dict       = samples_to_stitch[split_var]
  split_binning    = [ sample['value'] for sample in split_dict ]
  complete_binning = list(sorted(list(
    map(float, set(inclusive_binning) | set(list(itertools.chain.from_iterable(split_binning))))
  )))

  inclusive_xs = -1
  for sample_key, sample_entry in samples.items():
    if sample_key == 'sum_events': continue
    if sample_entry['process_name_specific'] == inclusive_samples[0]:
      inclusive_xs = sample_entry['xsection']
  assert(inclusive_xs > 0)

  # sum the inclusive nof events
  inclusive_nof_events = {}
  for sample_key, sample_entry in samples.items():
    if sample_key == 'sum_events': continue
    if sample_entry['process_name_specific'] in inclusive_samples:
      if not inclusive_nof_events:
        inclusive_nof_events = copy.deepcopy(sample_entry['nof_events'])
      else:
        assert(set(sample_entry['nof_events'].keys()) == set(inclusive_nof_events))
        for nof_key, nof_arr in sample_entry['nof_events'].items():
          assert(len(nof_arr) == len(inclusive_nof_events[nof_key]))
          for idx, nof in enumerate(nof_arr):
            inclusive_nof_events[nof_key][idx] += abs(nof) #TODO remove once the event counts are fixed

  # sum the binned nof events
  for binned_sample in split_dict:
    nof_events = {}
    xs = -1
    for sample_key, sample_entry in samples.items():
      if sample_key == 'sum_events': continue
      if sample_entry['process_name_specific'] in binned_sample['samples']:
        if not nof_events:
          nof_events = copy.deepcopy(sample_entry['nof_events'])
          assert(set(inclusive_nof_events.keys()) == set(nof_events.keys()))
        else:
          assert(set(sample_entry['nof_events'].keys()) == set(nof_events.keys()))
          for nof_key, nof_arr in sample_entry['nof_events'].items():
            assert(len(nof_arr) == len(nof_events[nof_key]))
            for idx, nof in enumerate(nof_arr):
              nof_events[nof_key][idx] += abs(nof) #TODO remove once the event counts are fixed
        if xs < 0:
          xs = sample_entry['xsection']
    assert(xs > 0)
    binned_sample['xsection'] = xs
    binned_sample['nof_events'] = nof_events

    lumis = {}
    for nof_key, nof_arr in binned_sample['nof_events'].items():
      lumis[nof_key] = list(map(lambda nof: nof / binned_sample['xsection'], nof_arr))
    binned_sample['lumis'] = lumis

  # compute integrated luminosities for the inclusive sample
  inclusive_lumis = {}
  for nof_key, nof_arr in inclusive_nof_events.items():
    inclusive_lumis[nof_key] = list(map(lambda nof: nof / inclusive_xs, nof_arr))

  # decide on the bin indices
  idxs_split_sample = []
  for binned_sample in split_dict:
    binned_idx = complete_binning.index(binned_sample['value'][0]) + 1
    binned_sample['idx'] = binned_idx
    idxs_split_sample.append(binned_idx)

  for inclusive_sample in inclusive_samples:
    histogram_dir = f.mkdir(inclusive_sample)
    histogram_dir.cd()

    for nof_key, lumi_arr in inclusive_lumis.items():
      for idx, lumi_incl in enumerate(lumi_arr):
        histogram_name = '%s_%d' % (nof_key, idx)
        binning = array.array('f', complete_binning)

        histogram = ROOT.TH1D(histogram_name, histogram_name, len(binning) - 1, binning)
        histogram.SetXTitle(split_var)

        for split_idx in range(1, len(binning)):
          if split_idx in idxs_split_sample:
            for binned_sample in split_dict:
              if split_idx == binned_sample['idx']:
                lumi_split = binned_sample['lumis'][nof_key][idx]
                weight = lumi_incl / (lumi_incl + lumi_split)
                histogram.SetBinContent(split_idx, weight)
          else:
            histogram.SetBinContent(split_idx, 1.)
          histogram.GetXaxis().SetBinLabel(
            split_idx, '%.0f <= %s < %.0f' % (
              complete_binning[split_idx - 1], split_var, complete_binning[split_idx]
            )
          )

        histogram.Write()

  for binned_sample in split_dict:
    for sample_name in binned_sample['samples']:
      histogram_dir = f.mkdir(sample_name)
      histogram_dir.cd()

      for nof_key, lumi_arr in inclusive_lumis.items():
        for idx, lumi_incl in enumerate(lumi_arr):

          histogram_name = '%s_%d' % (nof_key, idx)
          binning = array.array('f', complete_binning)

          histogram = ROOT.TH1D(histogram_name, histogram_name, len(binning) - 1, binning)
          histogram.SetXTitle(split_var)

          lumi_split = -1
          for split_idx in range(1, len(binning)):
            if split_idx == binned_sample['idx']:
              lumi_split = binned_sample['lumis'][nof_key][idx]
              weight = lumi_incl / (lumi_incl + lumi_split)
              histogram.SetBinContent(split_idx, weight)
            else:
              histogram.SetBinContent(split_idx, 0.)
            histogram.GetXaxis().SetBinLabel(
              split_idx, '%.0f <= %s < %.0f' % (
                complete_binning[split_idx - 1], split_var, complete_binning[split_idx]
              )
            )

          assert(lumi_split > 0.)
          sf = lumi_split / lumi_incl
          histogram.Scale(sf)
          histogram.Write()

fp = ROOT.TFile.Open('python/event_weights.root', 'recreate')
comp_weights(fp, samples_to_stitch[1], 'LHE_HT')
comp_weights(fp, samples_to_stitch[2], 'LHE_Njets')
fp.Close()

