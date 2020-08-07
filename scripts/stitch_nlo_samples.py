#!/usr/bin/env python

from tthAnalysis.HiggsToTauTau.safe_root import ROOT
from tthAnalysis.HiggsToTauTau.common import SmartFormatter, load_samples

import matplotlib
matplotlib.use('Agg') # headless mode

from matplotlib.backends.backend_pdf import PdfPages
import matplotlib.pyplot as plt

import argparse
import re
import collections
import copy
import array
import os

parser = argparse.ArgumentParser(
    formatter_class = lambda prog: SmartFormatter(prog, max_help_position = 35)
)
parser.add_argument('-e', '--era',
  type = str, dest = 'era', metavar = 'era', required = True, choices = [ '2016', '2017', '2018' ],
  help = 'R|Era',
)
parser.add_argument('-o', '--output',
  type = str, dest = 'output', metavar = 'path', required = False,
  help = 'R|Output file name',
)
parser.add_argument('-p', '--plot',
  type = str, dest = 'plot', metavar = 'path', required = False,
  help = 'R|Plot file name',
)
args = parser.parse_args()

era = args.era
output = args.output
plot = args.plot

if not output:
  output = os.path.join(
    os.environ['CMSSW_BASE'], 'src', 'tthAnalysis', 'HiggsToTauTau', 'data', 'stitched_weights_nlo_{}.root'.format(era)
  )

samples = load_samples(era)

if era == '2016':
  from tthAnalysis.HiggsToTauTau.samples.stitch_nlo import samples_to_stitch_DYJets_NLO_2016 as samples_to_stitch
elif era == '2017':
  from tthAnalysis.HiggsToTauTau.samples.stitch_nlo import samples_to_stitch_DYJets_NLO_2017 as samples_to_stitch
elif era == '2018':
  from tthAnalysis.HiggsToTauTau.samples.stitch_nlo import samples_to_stitch_DYJets_NLO_2018 as samples_to_stitch
else:
  raise RuntimeError("Invalid era: %s" % era)

if plot and not plot.endswith('.pdf'):
  raise ValueError("Can only accept the path to plot in pdf format: %s" % plot)

SPLITVAR = 'LHE_Njets'
COUNT_LHENJET = 'LHENjet'
COUNT_NAME_KEY = 'weight'
COUNT_BIN_KEY = 'bin'
COUNT_REGEX = re.compile(
  '(?P<{}>\w+)_{}(?P<{}>\d)'.format(
    COUNT_NAME_KEY, COUNT_LHENJET, COUNT_BIN_KEY
  )
)
assert(SPLITVAR in samples_to_stitch)
exclusive_sample_lists = [ sample_list['samples'] for sample_list in samples_to_stitch[SPLITVAR] ]

def get_sample_stats(sample_name, sample_dict):
  sample_xsec = -1.
  sample_yields = dict()
  has_lhe = False
  for sample_key, sample_info in sample_dict.items():
    if sample_key == 'sum_events':
      continue
    if sample_info['process_name_specific'] == sample_name:
      sample_yields = sample_info['nof_events']
      sample_xsec = sample_info['xsection']
      has_lhe = sample_info['has_LHE']
      break
  if not sample_yields:
    raise RuntimeError("Unable to find sample %s in era %s" % (sample_name, era))
  assert(sample_xsec > 0.)

  sample_yields_agg = collections.OrderedDict()
  for sample_count in sample_yields:
    sample_count_match = COUNT_REGEX.match(sample_count)
    if not sample_count_match:
      assert(COUNT_LHENJET not in sample_count)
      continue
    sample_count_name = sample_count_match.group(COUNT_NAME_KEY)
    sample_count_bin = int(sample_count_match.group(COUNT_BIN_KEY))
    if sample_count_name == 'Count':
      # skip unweighted counts
      continue
    if sample_count_name == 'CountWeightedPSWeightOriginalXWGTUP':
      # mega hack: in 2018 the numbers are bogus, easier to skip because these counts will be ignored anyways
      continue
    if sample_count_name not in sample_yields_agg:
      sample_yields_agg[sample_count_name] = {}
    assert(sample_count_bin not in sample_yields_agg[sample_count_name])
    sample_yields_agg[sample_count_name][sample_count_bin] = copy.deepcopy(sample_yields[sample_count])
  return sample_yields_agg, sample_xsec

def merge_samples(sample_list, sample_dict):
  if len(sample_list) > 1:
    equal_lists = False
    event_sums = sample_dict['sum_events']
    for sample_list_name in sample_list:
      for event_sum_list in event_sums:
        if sample_list_name in event_sum_list:
          equal_lists = set(event_sum_list) == set(sample_list)
          break
      if equal_lists:
        break
    if not equal_lists:
      raise RuntimeError("Unbale to verify that the list of samples should be merged: %s" % ', '.join(sample_list))
  sample_xsec_final = -1.
  sample_yields_final = None
  for sample_name in sample_list:
    sample_yields_agg, sample_xsec = get_sample_stats(sample_name, sample_dict)
    if sample_xsec_final < 0.:
      sample_xsec_final = sample_xsec
      assert(not sample_yields_final)
      sample_yields_final = copy.deepcopy(sample_yields_agg)
    else:
      assert(sample_xsec_final == sample_xsec)
      assert(sample_yields_final)
      assert(set(sample_yields_final.keys()) == set(sample_yields_agg.keys()))
      for count_key in sample_yields_agg:
        assert(set(sample_yields_agg[count_key].keys()) == set(sample_yields_final[count_key].keys()))
        for bin_key in sample_yields_agg[count_key]:
          assert(len(sample_yields_agg[count_key][bin_key]) == len(sample_yields_final[count_key][bin_key]))
          for bin_idx, bin_value in enumerate(sample_yields_agg[count_key][bin_key]):
            sample_yields_final[count_key][bin_key][bin_idx] += bin_value
  return sample_yields_final, sample_xsec_final

inclusive_count, inclusive_xsec = merge_samples(samples_to_stitch['inclusive']['samples'], samples)
exclusive_counts = []
exclusive_xsecs = []
for exclusive_sample_list in exclusive_sample_lists:
  exclusive_count, exclusive_xsec = merge_samples(exclusive_sample_list, samples)
  exclusive_counts.append(exclusive_count)
  exclusive_xsecs.append(exclusive_xsec)
exclusive_xsec_sum = sum(exclusive_xsecs)
if abs(exclusive_xsec_sum - inclusive_xsec) / inclusive_xsec > 1e-4:
  raise RuntimeError(
    "Cross section of inclusive sample (%.3f) not equal to the sum of cross sections of exclusive samples (%.3f)" % \
    (inclusive_xsec, exclusive_xsec_sum)
  )

# pad missing bins with zeros in the exclusive case
bin_keys = []
bin_lens = collections.OrderedDict()
for exclusive_idx in range(len(exclusive_counts)):
  for count_key in inclusive_count:
    assert(count_key in exclusive_counts[exclusive_idx])
    for bin_key in inclusive_count[count_key]:
      if bin_key not in bin_keys:
        bin_keys.append(bin_key)
      bin_len = len(inclusive_count[count_key][bin_key])
      if count_key not in bin_lens:
        bin_lens[count_key] = bin_len
      if bin_key not in exclusive_counts[exclusive_idx][count_key]:
        exclusive_counts[exclusive_idx][count_key][bin_key] = [0] * bin_len
bin_keys = list(sorted(bin_keys))

# make sure that all event counts are compatible across all samples
for exclusive_idx in range(len(exclusive_counts)):
  assert(set(exclusive_counts[exclusive_idx].keys()) == set(inclusive_count.keys()))
  for count_key in exclusive_counts[exclusive_idx]:
    assert(set(exclusive_counts[exclusive_idx][count_key].keys()) == set(inclusive_count[count_key].keys()))
    for bin_key in exclusive_counts[exclusive_idx][count_key]:
      assert(len(exclusive_counts[exclusive_idx][count_key][bin_key]) == len(inclusive_count[count_key][bin_key]))
  for exclusive_jdx in range(exclusive_idx + 1, len(exclusive_counts)):
    assert(set(exclusive_counts[exclusive_idx].keys()) == set(exclusive_counts[exclusive_jdx].keys()))
    for count_key in exclusive_counts[exclusive_idx]:
      assert(set(exclusive_counts[exclusive_idx][count_key].keys()) == set(exclusive_counts[exclusive_jdx][count_key].keys()))
      for bin_key in exclusive_counts[exclusive_idx][count_key]:
        assert(len(exclusive_counts[exclusive_idx][count_key][bin_key]) == len(exclusive_counts[exclusive_jdx][count_key][bin_key]))

bin_sums = collections.OrderedDict()
for count_key in bin_lens:
  for count_idx in range(bin_lens[count_key]):
    bin_count_name = '{}_{}'.format(count_key, count_idx)
    bin_sums[bin_count_name] = [
      inclusive_count[count_key][bin_idx][count_idx] + sum(
        exclusive_counts[sample_idx][count_key][bin_idx][count_idx] for sample_idx in range(len(exclusive_counts))
      ) for bin_idx in bin_keys
    ]

inclusive_sums = collections.OrderedDict()
for count_key in bin_lens:
  for count_idx in range(bin_lens[count_key]):
    bin_count_name = '{}_{}'.format(count_key, count_idx)
    inclusive_sums[bin_count_name] = sum(inclusive_count[count_key][bin_idx][count_idx] for bin_idx in bin_keys)

exclusive_sums = []
for exclusive_idx in range(len(exclusive_counts)):
  exclusive_sum = collections.OrderedDict()
  for count_key in bin_lens:
    for count_idx in range(bin_lens[count_key]):
      bin_count_name = '{}_{}'.format(count_key, count_idx)
      assert(bin_count_name not in exclusive_sum)
      exclusive_sum[bin_count_name] = sum(exclusive_counts[exclusive_idx][count_key][bin_idx][count_idx] for bin_idx in bin_keys)
  exclusive_sums.append(exclusive_sum)

inclusive_weights = collections.OrderedDict()
for sample_sum_key in inclusive_sums:
  inclusive_weights[sample_sum_key] = inclusive_xsec / inclusive_sums[sample_sum_key]

exclusive_weights = []
for exclusive_idx, exclusive_xsec in enumerate(exclusive_xsecs):
  exclusive_weight = collections.OrderedDict()
  for sample_sum_key in exclusive_sums[exclusive_idx]:
    exclusive_weight[sample_sum_key] = exclusive_xsec / exclusive_sums[exclusive_idx][sample_sum_key]
  exclusive_weights.append(exclusive_weight)

bin_xsecs = collections.OrderedDict()
for count_key in bin_lens:
  for count_idx in range(bin_lens[count_key]):
    bin_count_name = '{}_{}'.format(count_key, count_idx)
    bin_xsecs[bin_count_name] = [
      (
          sum(
            exclusive_xsecs[exclusive_idx] * exclusive_counts[exclusive_idx][count_key][bin_idx][count_idx] /
            exclusive_sums[exclusive_idx][bin_count_name]
            for exclusive_idx in range(len(exclusive_counts))
          ) +
          inclusive_xsec * inclusive_count[count_key][bin_idx][count_idx] / inclusive_sums[bin_count_name]
      ) / 2
      for bin_idx in bin_keys
    ]

bin_weights = collections.OrderedDict()
for bin_count_name in bin_xsecs:
  bin_weights[bin_count_name] = [
    bin_xsecs[bin_count_name][bin_idx] / bin_sums[bin_count_name][bin_idx] for bin_idx in bin_keys
  ]

inclusive_stitching = collections.OrderedDict()
for count_key in bin_lens:
  for count_idx in range(bin_lens[count_key]):
    bin_count_name = '{}_{}'.format(count_key, count_idx)
    inclusive_stitching[bin_count_name] = [
      bin_weights[bin_count_name][bin_idx] / inclusive_weights[bin_count_name] \
      if abs(inclusive_count[count_key][bin_idx][count_idx]) > 0. else 0. for bin_idx in bin_keys
    ]

exclusive_stitchings = []
for exclusive_idx in range(len(exclusive_counts)):
  exclusive_stitching = collections.OrderedDict()
  for count_key in bin_lens:
    for count_idx in range(bin_lens[count_key]):
      bin_count_name = '{}_{}'.format(count_key, count_idx)
      exclusive_stitching[bin_count_name] = [
        bin_weights[bin_count_name][bin_idx] / exclusive_weights[exclusive_idx][bin_count_name] \
        if abs(exclusive_counts[exclusive_idx][count_key][bin_idx][count_idx]) > 0. else 0. for bin_idx in bin_keys
      ]
  exclusive_stitchings.append(exclusive_stitching)

for count_key in bin_lens:
  for count_idx in range(bin_lens[count_key]):
    bin_count_name = '{}_{}'.format(count_key, count_idx)
    xsec = sum(
      inclusive_stitching[bin_count_name][bin_idx] * inclusive_weights[bin_count_name] * \
      inclusive_count[count_key][bin_idx][count_idx] +
      sum(
        exclusive_stitchings[exclusive_idx][bin_count_name][bin_idx] * exclusive_weights[exclusive_idx][bin_count_name] * \
        exclusive_counts[exclusive_idx][count_key][bin_idx][count_idx]
        for exclusive_idx in range(len(exclusive_counts))
      )
      for bin_idx in bin_keys
    )
    assert(abs(xsec - inclusive_xsec) / inclusive_xsec < 1e-5)

bin_ratio_inclusive = collections.OrderedDict()
for count_key in bin_lens:
  for count_idx in range(bin_lens[count_key]):
    bin_count_name = '{}_{}'.format(count_key, count_idx)
    bin_ratio_inclusive[bin_count_name] = [
      float(inclusive_count[count_key][bin_idx][count_idx]) / inclusive_sums[bin_count_name] for bin_idx in bin_keys
    ]
    assert(abs(sum(bin_ratio_inclusive[bin_count_name]) - 1.) < 1e-5)

bin_ratio_exclusive = collections.OrderedDict()
for count_key in bin_lens:
  for count_idx in range(bin_lens[count_key]):
    bin_count_name = '{}_{}'.format(count_key, count_idx)
    bin_ratios_nonorm = [
      sum(
        exclusive_counts[exclusive_idx][count_key][bin_idx][count_idx] * exclusive_weights[exclusive_idx][bin_count_name]
        for exclusive_idx in range(len(exclusive_counts))
      ) for bin_idx in bin_keys
    ]
    bin_ratios_sum = sum(bin_ratios_nonorm)
    bin_ratio_exclusive[bin_count_name] = [ bin_ratios_nonorm[bin_idx] / bin_ratios_sum for bin_idx in bin_keys ]
    assert(abs(sum(bin_ratio_exclusive[bin_count_name]) - 1.) < 1e-5)

bin_ratios_stitched = collections.OrderedDict()
for count_key in bin_lens:
  for count_idx in range(bin_lens[count_key]):
    bin_count_name = '{}_{}'.format(count_key, count_idx)
    bin_ratios_nonorm = [
      inclusive_stitching[bin_count_name][bin_idx] * inclusive_count[count_key][bin_idx][count_idx] *
      inclusive_weights[bin_count_name] +
      sum(
        exclusive_stitchings[exclusive_idx][bin_count_name][bin_idx] * exclusive_counts[exclusive_idx][count_key][bin_idx][count_idx] *
        exclusive_weights[exclusive_idx][bin_count_name] for exclusive_idx in range(len(exclusive_counts))
      )
      for bin_idx in bin_keys
    ]
    bin_ratios_sum = sum(bin_ratios_nonorm)
    bin_ratios_stitched[bin_count_name] = [ bin_ratios_nonorm[bin_idx] / bin_ratios_sum for bin_idx in bin_keys ]
    assert(abs(sum(bin_ratios_stitched[bin_count_name]) - 1.) < 1e-5)

if plot:
  with PdfPages(plot) as pdf:
    lhe_njets = list(map(float, range(max(bin_keys) + 2)))
    for bin_key in bin_ratio_inclusive:
      bin_ratio_expected_inclusive = bin_ratio_inclusive[bin_key] + [0.]
      bin_ratio_expected_exclusive = bin_ratio_exclusive[bin_key] + [0.]
      bin_ratio_stitched = bin_ratios_stitched[bin_key] + [0.]
      plt.figure(figsize = (8, 6), dpi = 150)
      plt.grid(True)
      plt.step(lhe_njets, bin_ratio_expected_inclusive, where = 'post', label = 'Expected (inclusive only)')
      plt.step(lhe_njets, bin_ratio_expected_exclusive, where = 'post', label = 'Expected (exclusive only)')
      plt.step(lhe_njets, bin_ratio_stitched, where = 'post', label = 'Stitched')
      plt.xlim(min(bin_keys), max(bin_keys) + 1)
      plt.legend(loc = 'upper right')
      plt.title('{}, ERA = {}'.format(bin_key, era))
      plt.xlabel('# LHE jets')
      plt.ylabel('Fraction of events to the total number of events')
      plt.savefig(pdf, format = 'pdf', bbox_inches = 'tight')
      plt.close()

def save_weights(fp, sample_names, stitching_dict):
  for sample_name in sample_names:
    sample_dir = fp.mkdir(sample_name)
    hist_dir = sample_dir.mkdir(SPLITVAR)
    hist_dir.cd()
    for bin_count_name in stitching_dict:
      bin_array = array.array('f', list(range(max(bin_keys) + 2)))
      hist = ROOT.TH1D(bin_count_name, bin_count_name, len(bin_array) - 1, bin_array)
      hist.SetDirectory(hist_dir)
      hist.SetTitle(bin_count_name)
      hist.SetXTitle(SPLITVAR)
      for bin_idx in bin_keys:
        hist.SetBinContent(bin_idx + 1, stitching_dict[bin_count_name][bin_idx])
        hist.GetXaxis().SetBinLabel(bin_idx + 1, "%d <= %s < %d" % (bin_idx, SPLITVAR, bin_idx + 1))
      hist.Write()

fp = ROOT.TFile.Open(output, 'recreate')
save_weights(fp, samples_to_stitch['inclusive']['samples'], inclusive_stitching)
for exclusive_idx in range(len(exclusive_sample_lists)):
  save_weights(fp, exclusive_sample_lists[exclusive_idx], exclusive_stitchings[exclusive_idx])
fp.Close()
