#!/usr/bin/env python

from tthAnalysis.HiggsToTauTau.common import load_samples, SmartFormatter

import collections
import copy
import itertools
import prettytable
import re
import jinja2
import datetime
import numpy as np
import ROOT
import array
import importlib
import argparse
import os

ERA_CHOICES = [ '2016', '2017', '2018' ]

SPLIT_VAR_MAP = {
  'LHE_Njets' : { 'name' : 'LHENjet', 'encode_end' : False },
  'LHE_HT'    : { 'name' : 'LHEHT',   'encode_end' : True  },
}
SPLIT_VAR_NAMES = [ SPLIT_VAR_MAP[split_var]['name'] for split_var in SPLIT_VAR_MAP ]

COLORS = [
  [ '#517994', '#B2CFD8', '#DFEBF1', '#3b586b' ],
  [ '#8c5194', '#cbb2d8', '#eadff1', '#5c3561' ],
  [ '#519458', '#b2d8ba', '#dff1e5', '#345e38' ],
  [ '#949251', '#d8d7b2', '#ebebd1', '#6b6a3c' ],
  [ '#945151', '#d8b2b2', '#f1dfdf', '#5e3333' ],
  [ '#519482', '#b2d8cd', '#dff1ed', '#355e53' ],
  [ '#7a9451', '#c8d8b2', '#dee6d5', '#45542e' ],
  [ '#515294', '#b2b5d8', '#dfe1f1', '#2d2d52' ],
  [ '#94518c', '#d5b2d8', '#f0dff1', '#512d52' ],
  [ '#948751', '#d8d0b2', '#f1eddf', '#52462d' ],
]

HTML_TEMPLATE = '''
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="utf-8">

    <title>Stitching weight report</title>
    <meta name="description" content="Stitching weight report">

    <style>
    table {
      font-family: "Courier New", Courier, monospace;
      font-size: 14px;
      color: #333333;
      border-width: 1px;
      border-color: #3A3A3A;
      border-collapse: collapse;
      margin-bottom: 40px;
      margin-left: 60px;
    }

    table th {
      border-width: 1px;
      padding: 8px;
      border-style: solid;
    }

    table td {
      border-width: 1px;
      padding: 8px;
      border-style: solid;
      background-color: #ffffff;
    }

    .caption {
      font-size: 16px;
      font-weight: bold;
      margin-left: 30px;
      margin-bottom: 10px;
      font-family: Arial, Helvetica, sans-serif;
    }

    html {
      overflow-y: scroll;
    }

    .collapsible {
      background-color: #777;
      color: white;
      cursor: pointer;
      padding: 18px;
      min-width: 600px;
      width: 60%;
      border: none;
      text-align: left;
      outline: none;
      font-size: 18px;
      font-family: Arial, Helvetica, sans-serif;
      font-weight: bold;
    }

    .active, .collapsible:hover {
      background-color: #555;
    }

    .collapsible:after {
      content: '\\002B';
      color: white;
      font-weight: bold;
      float: right;
      margin-left: 5px;
    }

    .active:after {
      content: "\\2212";
    }

    .content {
      padding: 0 18px;
      display: none;
      overflow: hidden;
      background-color: #f1f1f1;
    }

    {% for color in colors %}
    {% set color_idx = loop.index - 1 %}
    .color{{ color_idx }} table th {
      border-color: {{color[0]}};
      background-color: {{color[1]}};
    }
    .color{{ color_idx }} table td {
      border-color: {{color[0]}};
    }
    .color{{ color_idx }} table tr:hover td {
      background-color: {{color[2]}};
    }
    .collapsible.bar{{ color_idx }} {
      background-color: {{color[0]}};
    }

    .active, .collapsible.bar{{ color_idx }}:hover {
      background-color: {{color[3]}};
    }
    {% endfor %}

    </style>
  </head>
  <p style="font-family: Arial, Helvetica, sans-serif;"><em>{{ meta }}</em></p>
  <body>
  {% for entry_set in content %}
    {% set color_idx = (loop.index - 1) % colors|length %}
    {% set outer_idx = loop.index %}
    <div><a name="point{{ outer_idx }}"></a></div>
    <button type="button" class="collapsible bar{{ color_idx }}" onclick="location.href='#point{{ outer_idx }}'">{{ entry_set[2] }}</button>
    <div class="content">
    {% for entry in entry_set[1] %}
      <p  class="caption">{{ entry[1] }}</p>
      <div class="color{{ color_idx }}">
      {{ entry[0] }}
      </div>
    {% endfor %}
    </div><div></div>
  {% endfor %}

  <script>
    var coll = document.getElementsByClassName("collapsible");
    var i;

    for (i = 0; i < coll.length; i++) {
      coll[i].addEventListener("click", function() {
        this.classList.toggle("active");
        var content = this.nextElementSibling;
        if (content.style.display === "inline") {
          content.style.display = "none";
        } else {
          content.style.display = "inline";
          content.style.width = "100%";
        }
      });
    }
    </script>

  </body>
</html>
'''

CAPTIONS_BASE = [
  "Dataset info", "Binned event counts", "Lumiscale by bin", "Stitching weights", "Fraction of events per bin"
]

def get_weight_name(era, use_full_weight):
  count_var = 'CountWeighted' if era == '2018' else 'CountWeightedL1PrefireNom'
  if use_full_weight:
    count_var = count_var.replace('CountWeighted', 'CountWeightedFull')
  return count_var

def rfmt(nr, force_scientific = False):
  if nr == 0.:
    return '0'
  elif nr < 1e-3 or force_scientific:
    return '{:.3e}'.format(nr)
  else:
    return '{:.3f}'.format(nr)

def load_sample(era):
  stitch_module = importlib.import_module("tthAnalysis.HiggsToTauTau.samples.stitch")
  samples_to_stitch_dict = getattr(stitch_module, "samples_to_stitch_{}".format(era))
  samples = load_samples(era)
  return samples, samples_to_stitch_dict

def read_samples(sample_list, samples, is_lo):
  event_counts = collections.OrderedDict()
  xsection = -1.
  for sample_key, sample_info in samples.items():
    if sample_key == 'sum_events':
      continue

    process_name = sample_info["process_name_specific"]
    if process_name not in sample_list:
      continue

    xsection_current = sample_info["xsection"]
    if xsection < 0.:
      xsection = xsection_current
    else:
      assert(xsection == xsection_current)

    nof_events = sample_info["nof_events"]
    for count_key in nof_events:
      if count_key not in event_counts:
        event_counts[count_key] = [0.] * len(nof_events[count_key])
      assert(len(event_counts[count_key]) == len(nof_events[count_key]))

      for count_idx in range(len(nof_events[count_key])):
        if is_lo == 'LO' and nof_events[count_key][count_idx] < -1.:
          raise RuntimeError(
            "Negative event count found in %s sample, %s event count, idx %d: %.1f" % \
            (process_name, count_key, count_idx, nof_events[count_key][count_idx])
          )
        event_counts[count_key][count_idx] += nof_events[count_key][count_idx]
  return event_counts, xsection

def read_dict(samples_to_stitch_dict, samples, sample_set_idx):
  assert(sample_set_idx < len(samples_to_stitch_dict))
  samples_to_stitch = copy.deepcopy(samples_to_stitch_dict[sample_set_idx])

  inclusive_counts, inclusive_xs = read_samples(
    samples_to_stitch['inclusive']['samples'], samples, samples_to_stitch['order']
  )
  samples_to_stitch['inclusive']['counts'] = inclusive_counts
  samples_to_stitch['inclusive']['xsec'] = inclusive_xs

  for split_var in get_split_vars(samples_to_stitch, check_inclusive = False):
    for sample_idx in range(len(samples_to_stitch['exclusive'][split_var])):
      exclusive_counts, exclusive_xs = read_samples(
        samples_to_stitch['exclusive'][split_var][sample_idx]['samples'], samples, samples_to_stitch['order']
      )
      samples_to_stitch['exclusive'][split_var][sample_idx]['counts'] = exclusive_counts
      samples_to_stitch['exclusive'][split_var][sample_idx]['xsec'] = exclusive_xs
  return samples_to_stitch

def flatten(list_of_lists):
  return [ it for sublist in list_of_lists for it in sublist ]

def get_split_vars(samples_to_stitch, check_inclusive = True):
  split_vars_exc = sorted([ var_name for var_name in samples_to_stitch['exclusive'] ], reverse = True)
  if check_inclusive and 'inclusive' in samples_to_stitch:
    split_vars_inc = [
      var_name for var_name in samples_to_stitch['inclusive'] if var_name not in [ 'samples', 'counts', 'xsec' ]
    ]
    assert(set(split_vars_inc) == set(split_vars_exc))
  return split_vars_exc

def get_unbinned_event_count_names(samples_to_stitch, split_vars):
  assert(all(split_var in SPLIT_VAR_MAP for split_var in split_vars))

  event_counts_unbinned = collections.OrderedDict()
  for split_var in get_split_vars(samples_to_stitch, check_inclusive = False):
    for sample_idx in range(len(samples_to_stitch['exclusive'][split_var])):
      event_counts = samples_to_stitch['exclusive'][split_var][sample_idx]['counts']
      for event_count_key in event_counts:
        if any(split_var_name in event_count_key for split_var_name in SPLIT_VAR_NAMES):
          continue
        if event_count_key == 'Count' or '_' in event_count_key:
          continue
        if event_count_key not in event_counts_unbinned:
          event_counts_unbinned[event_count_key] = [0.] * len(event_counts[event_count_key])
        else:
          assert(len(event_counts_unbinned[event_count_key]) == len(event_counts[event_count_key]))
  return event_counts_unbinned

def get_bin_name(split_var, split_var_ranges, split_var_idx = 0):
  assert(split_var in SPLIT_VAR_MAP)
  split_var_name = SPLIT_VAR_MAP[split_var]['name']
  split_var_encode_end = SPLIT_VAR_MAP[split_var]['encode_end']

  assert(split_var_idx < len(split_var_ranges) - 1)
  split_range_min = split_var_ranges[split_var_idx]
  split_range_max = split_var_ranges[split_var_idx + 1]

  split_range_min_str = '{:.0f}'.format(split_range_min)
  split_range_max_str = '{:.0f}'.format(split_range_max) if split_range_max < 1e5 else 'Inf'
  split_range_str = '{}to{}'.format(split_range_min_str, split_range_max_str) if split_var_encode_end else \
                    split_range_min_str
  return '{}{}'.format(split_var_name, split_range_str)

def get_split_var_ranges(return_ranges_for_grid, samples_to_stitch):
  split_vars = get_split_vars(samples_to_stitch, check_inclusive = False)
  if 'inclusive' in samples_to_stitch:
    split_var_ranges_incl = [ samples_to_stitch['inclusive'][split_var] for split_var in split_vars ]
  else:
    split_var_ranges_incl = [[]] * len(split_vars)

  split_var_ranges_excl = [
    list(sorted(set(flatten(
      sample_entry['value'] for sample_entry in samples_to_stitch['exclusive'][split_var]
    )))) for split_var in split_vars
  ]

  if return_ranges_for_grid:
    split_var_ranges = []
    for split_var_idx in range(len(split_vars)):
      split_var_range_candidate = copy.deepcopy(split_var_ranges_excl[split_var_idx])

      if 'inclusive' in samples_to_stitch:
        split_var_min_val = min(split_var_ranges_incl[split_var_idx])
        split_var_max_val = max(split_var_ranges_incl[split_var_idx])
        if split_var_min_val not in split_var_range_candidate:
          split_var_range_candidate.insert(0, split_var_min_val)
        if split_var_max_val not in split_var_range_candidate:
          split_var_range_candidate.append(split_var_max_val)

      split_var_ranges.append(split_var_range_candidate)
    return split_var_ranges
  else:
    split_var_ranges_full = [
      list(
        sorted(set(split_var_ranges_incl[split_var_idx]) | \
               set(split_var_ranges_excl[split_var_idx]))
      ) for split_var_idx in range(len(split_vars))
    ]
    return split_var_ranges_full

def get_grid(return_full_grid, samples_to_stitch, event_counts_unbinned):
  split_vars = get_split_vars(samples_to_stitch, check_inclusive = False)
  split_var_ranges = get_split_var_ranges(return_full_grid, samples_to_stitch)
  split_var_grid_linear = [
    [
      get_bin_name(split_var, split_var_ranges[split_var_idx], split_var_range_idx) \
      for split_var_range_idx in range(len(split_var_ranges[split_var_idx]) - 1)
    ] for split_var_idx, split_var in enumerate(split_vars)
  ]

  split_var_grid = collections.OrderedDict([
    ('_'.join(keyname), copy.deepcopy(event_counts_unbinned)) \
    for keyname in itertools.product(*split_var_grid_linear)
  ])
  return split_var_grid if return_full_grid else list(split_var_grid.keys())

def get_sum_mapping(split_var_grid, split_var_names_full):
  split_var_lhs = list(sorted(set(split_var_names_full) - set(split_var_grid.keys())))
  split_var_rhs = list(sorted(set(split_var_grid.keys()) - set(split_var_names_full)))
  assert(not (bool(split_var_lhs) != bool(split_var_rhs)))
  split_var_sum_mapping = collections.OrderedDict()

  if split_var_rhs:
    nof_merge = int(len(split_var_lhs) / len(split_var_rhs))
    assert(len(split_var_rhs) * nof_merge == len(split_var_lhs))
    for bin_idx, bin_name in enumerate(split_var_rhs):
      # crude assumption that we get the right mapping just by sorting the names
      split_var_sum_mapping[bin_name] = split_var_lhs[nof_merge * bin_idx:nof_merge * (bin_idx + 1)]
      bin_name_split = bin_name.split('_')
      split_var_lhs_split = [
        split_var_lhs_entry.split('_') for split_var_lhs_entry in split_var_sum_mapping[bin_name]
      ]
      map_key = '_'.join(bin_name_split[1:])
      if not map_key:
        continue
      split_var_sum_mapping[map_key] = [
        '_'.join(split_var_lhs_entry[1:]) for split_var_lhs_entry in split_var_lhs_split
      ]
  return split_var_sum_mapping

def bin_event_counts(sample_dict, nof_split_vars, split_var_grid, split_var_names_full, event_counts_unbinned,
                     split_var_sum_mapping, split_var_names_full_linear, keyname = '', order = '', del_var = ''):
  sample_counts = sample_dict['counts']
  sample_grid = copy.deepcopy(split_var_grid)
  if not keyname:
    # inclusive
    bin_names = list(split_var_names_full)
  else:
    # excluisve
    bin_names = split_var_names_full_linear if (nof_split_vars > 1 or order == 'NLO') else ['']
  for event_count_unbinned in event_counts_unbinned:
    for bin_name in bin_names:
      if nof_split_vars == 1 and keyname and order != 'NLO':
        event_count_key_re = '^{}$'.format(event_count_unbinned)
      else:
        event_count_key_re = '^{ev_name}(_{del_var}.*)?_{bin_name}(_{del_var}.*)?$'.format(
          ev_name = event_count_unbinned,
          bin_name = bin_name,
          del_var = del_var,
        )
      matches = [
        sample_count for sample_count in sample_counts if re.match(event_count_key_re, sample_count)
      ]
      if not matches:
        continue
      bin_name_grid = bin_name
      if not keyname:
        if bin_name not in sample_grid:
          for sum_key in split_var_sum_mapping:
            if bin_name in split_var_sum_mapping[sum_key]:
              bin_name_grid = sum_key
              break
      else:
        if nof_split_vars == 1:
          if order != 'NLO':
            bin_name_grid = keyname
          else:
            bin_name_grid = bin_name
        else:
          bin_name_grid_cand = bin_name
          if bin_name not in sample_grid:
            for sum_key in split_var_sum_mapping:
              if bin_name in split_var_sum_mapping[sum_key]:
                bin_name_grid_cand = sum_key
                break
          bin_name_grid_cand_var1 = '{}_{}'.format(bin_name_grid_cand, keyname)
          bin_name_grid_cand_var2 = '{}_{}'.format(keyname, bin_name_grid_cand)
          if bin_name_grid_cand_var1 in sample_grid:
            bin_name_grid = bin_name_grid_cand_var1
          elif bin_name_grid_cand_var2 in sample_grid:
            bin_name_grid = bin_name_grid_cand_var2
          else:
            assert(False)

      assert(bin_name_grid)
      assert(bin_name_grid in sample_grid)
      assert(event_count_unbinned in sample_grid[bin_name_grid])
      for event_count_key in matches:
        for event_count_idx in range(len(sample_counts[event_count_key])):
          sample_grid[bin_name_grid][event_count_unbinned][event_count_idx] += \
            sample_counts[event_count_key][event_count_idx]
  return sample_grid

def comp_lumiscale(samples_to_stitch_in):
  samples_to_stitch_out = copy.deepcopy(samples_to_stitch_in)
  if 'inclusive' in samples_to_stitch_out:
    lumiscale_inc = collections.OrderedDict()
    for event_key in samples_to_stitch_out['inclusive']['counts']:
      lumiscale_inc[event_key] = [
        samples_to_stitch_out['inclusive']['xsec'] / event_count \
        for event_count in samples_to_stitch_out['inclusive']['counts'][event_key]
      ]
    samples_to_stitch_out['inclusive']['lumiscale'] = lumiscale_inc
  for split_var in get_split_vars(samples_to_stitch_out, check_inclusive = False):
    for sample_idx in range(len(samples_to_stitch_out['exclusive'][split_var])):
      exclusive_sample = samples_to_stitch_out['exclusive'][split_var][sample_idx]
      lumiscale_exc = collections.OrderedDict()
      for event_key in exclusive_sample['counts']:
        lumiscale_exc[event_key] = [
          exclusive_sample['xsec'] / event_count if abs(event_count) > 0. else 0. \
          for event_count in exclusive_sample['counts'][event_key]
        ]
      samples_to_stitch_out['exclusive'][split_var][sample_idx]['lumiscale'] = lumiscale_exc
  return samples_to_stitch_out

def print_lumiscale(samples_to_stitch, era, use_full_weight, count_var = '', count_idx = 0):
  if not count_var:
    count_var = get_weight_name(era, use_full_weight)
  header = ['Sample', 'XS [pb]', 'Event sum', 'Lumiscale', 'Datasets']
  table = prettytable.PrettyTable(header)
  row_dict = collections.OrderedDict()

  if 'inclusive' in samples_to_stitch:
    sample_inc = samples_to_stitch['inclusive']
    row_dict['inclusive'] = [
      '{:.3f}'.format(sample_inc['xsec']),
      rfmt(sample_inc['counts'][count_var][count_idx], True),
      '{:.3e}'.format(sample_inc['lumiscale'][count_var][count_idx]),
      ',\n'.join(sample_inc['samples']),
    ]
  exc_total = collections.OrderedDict()
  for split_var in get_split_vars(samples_to_stitch, check_inclusive = False):
    exc_total[split_var] = {
      'xsec': 0.,
      'evsum': 0.,
      'samples': [],
    }
    for sample_idx in range(len(samples_to_stitch['exclusive'][split_var])):
      sample_exc = samples_to_stitch['exclusive'][split_var][sample_idx]
      keyname = get_bin_name(split_var, sample_exc['value'])
      row_dict[keyname] = [
        '{:.3f}'.format(sample_exc['xsec']),
        rfmt(sample_exc['counts'][count_var][count_idx], True),
        '{:.3e}'.format(sample_exc['lumiscale'][count_var][count_idx]),
        ',\n'.join(sample_exc['samples']),
      ]
      exc_total[split_var]['xsec'] += sample_exc['xsec']
      exc_total[split_var]['evsum'] += sample_exc['counts'][count_var][count_idx]
      exc_total[split_var]['samples'].extend(sample_exc['samples'])
  for split_var in exc_total:
    row_dict['{} (total)'.format(split_var)] = [
      '{:.3f}'.format(exc_total[split_var]['xsec']),
      rfmt(exc_total[split_var]['evsum'], True),
      'x',
      ',\n'.join(exc_total[split_var]['samples']),
    ]
  for bin_key in row_dict:
    row = [bin_key, ] + row_dict[bin_key]
    table.add_row(row)
  return table.get_html_string()

def get_binned_counts(samples_to_stitch_in, split_var_grid, split_var_names_full, event_counts_unbinned,
                      split_var_sum_mapping, split_var_names_full_linear, del_var):
  nof_split_vars = len(samples_to_stitch_in['exclusive'].keys())
  samples_to_stitch_out = copy.deepcopy(samples_to_stitch_in)
  if del_var and del_var != 'inclusive':
    assert(del_var in SPLIT_VAR_MAP)
    del_var_name = SPLIT_VAR_MAP[del_var]['name']
  else:
    del_var_name = ''
  if 'inclusive' in samples_to_stitch_out:
    samples_to_stitch_out['inclusive']['binned_counts'] = bin_event_counts(
      samples_to_stitch_out['inclusive'],
      nof_split_vars,
      split_var_grid,
      split_var_names_full,
      event_counts_unbinned,
      split_var_sum_mapping,
      split_var_names_full_linear,
      order = samples_to_stitch_out['order'],
      del_var = del_var_name,
    )
  for sample_var in get_split_vars(samples_to_stitch_out, check_inclusive = False):
    for sample_var_idx in range(len(samples_to_stitch_out['exclusive'][sample_var])):
      keyname = get_bin_name(sample_var, samples_to_stitch_out['exclusive'][sample_var][sample_var_idx]['value'])
      samples_to_stitch_out['exclusive'][sample_var][sample_var_idx]['binned_counts'] = bin_event_counts(
        samples_to_stitch_out['exclusive'][sample_var][sample_var_idx],
        nof_split_vars,
        split_var_grid,
        split_var_names_full,
        event_counts_unbinned,
        split_var_sum_mapping,
        split_var_names_full_linear,
        keyname,
        order = samples_to_stitch_out['order'],
      )
  return samples_to_stitch_out

def print_event_counts(samples_to_stitch, era, use_full_weight, count_var = '', count_idx = 0):
  split_vars = get_split_vars(samples_to_stitch, check_inclusive = False)
  if not count_var:
    count_var = get_weight_name(era, use_full_weight)
  header = ['Bin', ]
  if 'inclusive' in samples_to_stitch:
    header.append('Inclusive\nsample')
  for split_var in split_vars:
    header.extend(
      '{}\nsample'.format(
        get_bin_name(split_var, samples_to_stitch['exclusive'][split_var][sample_idx]['value'])
      ) for sample_idx in range(len(samples_to_stitch['exclusive'][split_var]))
    )

  table = prettytable.PrettyTable(header)
  row_dict = collections.OrderedDict()
  if 'inclusive' in samples_to_stitch:
    for bin_key in samples_to_stitch['inclusive']['binned_counts']:
      row_dict[bin_key] = [samples_to_stitch['inclusive']['binned_counts'][bin_key][count_var][count_idx]]

  for split_var in split_vars:
    for sample_idx in range(len(samples_to_stitch['exclusive'][split_var])):
      for bin_key in samples_to_stitch['exclusive'][split_var][sample_idx]['binned_counts']:
        if bin_key not in row_dict:
          row_dict[bin_key] = []
        row_dict[bin_key].append(
          samples_to_stitch['exclusive'][split_var][sample_idx]['binned_counts'][bin_key][count_var][count_idx]
        )
  for bin_key in row_dict:
    row = [ bin_key, ] + [ rfmt(row_elem, True) for row_elem in row_dict[bin_key] ]
    table.add_row(row)

  return table.get_html_string()

def parse_bin(bin_key):
  bin_key_split = bin_key.split('_')
  bin_parsed = {}
  for bin_key_part in bin_key_split:
    orig_key = ''
    for orig_key_cand in SPLIT_VAR_MAP:
      if bin_key_part.startswith(SPLIT_VAR_MAP[orig_key_cand]['name']):
        orig_key = orig_key_cand
        break
    assert(orig_key)
    suffix = bin_key_part[len(SPLIT_VAR_MAP[orig_key]['name']):]
    bins = suffix.split('to')
    assert(len(bins) in [1, 2])
    if bins[-1] == 'Inf':
      bins[-1] = str(int(1e5))
    bins_int = [int(b) for b in bins]
    assert(orig_key not in bin_parsed)
    bin_parsed[orig_key] = bins_int
  return bin_parsed

def get_binstats(samples_to_stitch, split_var_grid):
  binstat = copy.deepcopy(split_var_grid)
  binstat_meta = collections.OrderedDict()
  for bin_key in binstat:
    bin_key_parsed = parse_bin(bin_key)

    binstat_evs = []
    inc_shared_ps = False
    if 'inclusive' in samples_to_stitch:
      inclusive_sample = samples_to_stitch['inclusive']

      assert(all(split_var_orig in inclusive_sample for split_var_orig in bin_key_parsed))

      for split_var_orig in bin_key_parsed:
        if len(bin_key_parsed[split_var_orig]) == 1 and \
            bin_key_parsed[split_var_orig][0] in inclusive_sample[split_var_orig]:
          inc_shared_ps = True
          break
        elif len(bin_key_parsed[split_var_orig]) == 2:
          inc_split_min_val = min(inclusive_sample[split_var_orig])
          inc_split_max_val = max(inclusive_sample[split_var_orig])
          if min(bin_key_parsed[split_var_orig]) >= inc_split_min_val and \
              max(bin_key_parsed[split_var_orig]) <= inc_split_max_val:
            inc_shared_ps = True
            break
      if inc_shared_ps:
        binstat_evs.append({
          'xsec': inclusive_sample['xsec'],
          'counts': inclusive_sample['binned_counts'][bin_key],
          'name': 'inclusive',
          'sums': inclusive_sample['counts'],
        })
    covering_split_vars = []
    for split_var in get_split_vars(samples_to_stitch, check_inclusive = False):
      for sample_idx in range(len(samples_to_stitch['exclusive'][split_var])):
        exclusive_sample = samples_to_stitch['exclusive'][split_var][sample_idx]
        for value_idx in range(len(exclusive_sample['value']) - 1):
          keyname = get_bin_name(split_var, exclusive_sample['value'], split_var_idx = value_idx)
          if keyname in bin_key:
            binstat_evs.append({
              'xsec': exclusive_sample['xsec'],
              'counts': exclusive_sample['binned_counts'][bin_key],
              'name': keyname,
              'sums': exclusive_sample['counts'],
            })
            if split_var not in covering_split_vars:
              covering_split_vars.append(split_var)
    binstat_meta[bin_key] = copy.deepcopy(binstat_evs)
    nof_binstat_evs = len(covering_split_vars) + int(inc_shared_ps)
    for count_name in binstat[bin_key]:
      for count_idx in range(len(binstat[bin_key][count_name])):
        binstat_xsec = sum(
          binstat_ev['xsec'] * binstat_ev['counts'][count_name][count_idx] / \
          binstat_ev['sums'][count_name][count_idx] \
          for binstat_ev in binstat_evs
        ) / nof_binstat_evs
        binstat_sum = sum(
          binstat_ev['counts'][count_name][count_idx] for binstat_ev in binstat_evs
        )
        binstat_lumiscale = binstat_xsec / binstat_sum if abs(binstat_sum) > 0 else 1.
        binstat[bin_key][count_name][count_idx] = {
          'xsec': binstat_xsec,
          'sum': binstat_sum,
          'lumiscale': binstat_lumiscale,
        }
  return binstat, binstat_meta

def print_binstats(binstat, binstat_meta, era, use_full_weight, count_var = '', count_idx = 0):
  if not count_var:
    count_var = get_weight_name(era, use_full_weight)
  header = ['Bin', 'XS [pb]', 'Event sum', 'Lumiscale', '# samples', 'Samples']
  table = prettytable.PrettyTable(header)
  row_dict = collections.OrderedDict()
  for bin_key in binstat:
    row_dict[bin_key] = [
      '{:.3f}'.format(binstat[bin_key][count_var][count_idx]['xsec']),
      rfmt(binstat[bin_key][count_var][count_idx]['sum'], True),
      '{:.3e}'.format(binstat[bin_key][count_var][count_idx]['lumiscale']),
      len(binstat_meta[bin_key]),
      ',\n'.join(binstat_entry['name'] for binstat_entry in binstat_meta[bin_key]),
    ]
  for bin_key in row_dict:
    row = [bin_key, ] + row_dict[bin_key]
    table.add_row(row)

  return table.get_html_string()

def stitch_sample(sample, binstat):
  stitching_weights = collections.OrderedDict()
  for binkey in binstat:
    stitching_weights[binkey] = collections.OrderedDict()
    for count_name in binstat[binkey]:
      stitching_weights[binkey][count_name] = []
      count_size = len(binstat[binkey][count_name])
      for count_idx in range(count_size):
        assert(binkey in sample['binned_counts'])
        assert(count_name in sample['binned_counts'][binkey])
        assert(len(sample['binned_counts'][binkey][count_name]) == count_size)
        if abs(sample['binned_counts'][binkey][count_name][count_idx]) > 0.:
          assert(count_name in sample['lumiscale'])
          assert(len(sample['lumiscale'][count_name]) == count_size)
          stitching_weights[binkey][count_name].append(
            binstat[binkey][count_name][count_idx]['lumiscale'] / \
            sample['lumiscale'][count_name][count_idx]
          )
        else:
          stitching_weights[binkey][count_name].append(0.)  # no stitching weight
  return stitching_weights

def comp_stitching_weights(samples_to_stitch_in, binstat):
  samples_to_stitch_out = copy.deepcopy(samples_to_stitch_in)
  if 'inclusive' in samples_to_stitch_out:
    sample_inc = samples_to_stitch_in['inclusive']
    samples_to_stitch_out['inclusive']['stitching'] = stitch_sample(sample_inc, binstat)
  for split_var in get_split_vars(samples_to_stitch_in, check_inclusive = False):
    for sample_idx in range(len(samples_to_stitch_in['exclusive'][split_var])):
      sample_exc = samples_to_stitch_in['exclusive'][split_var][sample_idx]
      samples_to_stitch_out['exclusive'][split_var][sample_idx]['stitching'] = stitch_sample(
        sample_exc, binstat
      )
  return samples_to_stitch_out

def print_stitching_weights(samples_to_stitch, era, use_full_weight, count_var = '', count_idx = 0):
  if not count_var:
    count_var = get_weight_name(era, use_full_weight)
  header = ['Bin']
  if 'inclusive' in samples_to_stitch:
    header.append('Inclusive\nsample')
  for split_var in get_split_vars(samples_to_stitch, check_inclusive = False):
    for sample_idx in range(len(samples_to_stitch['exclusive'][split_var])):
      header.append(
        '{}\nsample'.format(
          get_bin_name(split_var, samples_to_stitch['exclusive'][split_var][sample_idx]['value']))
      )

  table = prettytable.PrettyTable(header)
  row_dict = collections.OrderedDict()

  if 'inclusive' in samples_to_stitch:
    sample_inc = samples_to_stitch['inclusive']
    for binkey in sample_inc['stitching']:
      row_dict[binkey] = [sample_inc['stitching'][binkey][count_var][count_idx]]

  for split_var in get_split_vars(samples_to_stitch, check_inclusive = False):
    for sample_idx in range(len(samples_to_stitch['exclusive'][split_var])):
      for binkey in samples_to_stitch['exclusive'][split_var][sample_idx]['stitching']:
        if binkey not in row_dict:
          row_dict[binkey] = []
        row_dict[binkey].append(
          samples_to_stitch['exclusive'][split_var][sample_idx]['stitching'][binkey][count_var][count_idx]
        )

  for binkey in row_dict:
    row = [ binkey, ] + [ rfmt(count_nr) for count_nr in row_dict[binkey] ]
    table.add_row(row)

  return table.get_html_string()

def get_ratios(samples_to_stitch, era, inclusive_xs, use_full_weight, count_var = '', count_idx = 0):
  if not count_var:
    count_var = get_weight_name(era, use_full_weight)

  ratios = collections.OrderedDict()

  if 'inclusive' in samples_to_stitch:
    assert (inclusive_xs == samples_to_stitch['inclusive']['xsec'])
    for bin_key in samples_to_stitch['inclusive']['binned_counts']:
      ratio = samples_to_stitch['inclusive']['binned_counts'][bin_key][count_var][count_idx] / \
              samples_to_stitch['inclusive']['counts'][count_var][count_idx]
      ratios[bin_key] = collections.OrderedDict([('inclusive', [ ratio ])])

  for split_var in samples_to_stitch['exclusive']:
    bin_keys = list(samples_to_stitch['exclusive'][split_var][0]['binned_counts'].keys())
    for bin_key in bin_keys:
      if bin_key not in ratios:
        ratios[bin_key] = collections.OrderedDict()
      if split_var not in ratios[bin_key]:
        ratios[bin_key][split_var] = []
      for sample_idx in range(len(samples_to_stitch['exclusive'][split_var])):
        ratio = samples_to_stitch['exclusive'][split_var][sample_idx]['binned_counts'][bin_key][count_var][count_idx] / \
                samples_to_stitch['exclusive'][split_var][sample_idx]['counts'][count_var][count_idx] * \
                samples_to_stitch['exclusive'][split_var][sample_idx]['xsec'] / \
                inclusive_xs
        ratios[bin_key][split_var].append(ratio)
  return ratios

def get_ratio_table(samples_to_stitch, era, inclusive_xs, use_full_weight):
  ratios = get_ratios(samples_to_stitch, era, inclusive_xs, use_full_weight)
  header = [ 'Bin' ]
  rows = collections.OrderedDict()
  for bin_key in ratios:
    nonzero_weights = []
    row = []
    for sample_type in ratios[bin_key]:
      if sample_type not in header:
        header.append(sample_type)
      weight_sum = sum(ratios[bin_key][sample_type])
      nof_nonzero_contrib = len([val for val in ratios[bin_key][sample_type] if abs(val) != 0.])
      if nof_nonzero_contrib:
        nonzero_weights.append(weight_sum)
      row.append(weight_sum)
    stitch_avg = sum(nonzero_weights) / len(nonzero_weights) if nonzero_weights else 0.
    if 'stitched' not in header:
      header.append('stitched')
    row.append(stitch_avg)
    rows[bin_key] = row

  ratio_table = prettytable.PrettyTable(header)
  for bin_key in rows:
    row = [ bin_key, ] + [ rfmt(bin_content, force_scientific = True) for bin_content in rows[bin_key] ]
    ratio_table.add_row(row)
  return ratio_table.get_html_string()

def write_report(output_fn, content):
  meta = 'File generated on: {}'.format(str(datetime.datetime.now()))
  with open(output_fn, 'w') as html_out:
    html_out.write(jinja2.Template(HTML_TEMPLATE).render(
      content = content, colors = COLORS, meta = meta,
    ))
  return

def run_stitch(era, samples_to_stitch_orig, del_var, use_full_weight, counter = -1):
  inclusive_xs = samples_to_stitch_orig['inclusive']['xsec']
  samples_to_stitch = copy.deepcopy(samples_to_stitch_orig)
  if del_var:
    if del_var == 'inclusive':
      del samples_to_stitch['inclusive']
    else:
      del samples_to_stitch['exclusive'][del_var]
      del samples_to_stitch['inclusive'][del_var]
  split_vars = get_split_vars(samples_to_stitch)
  event_counts_unbinned = get_unbinned_event_count_names(samples_to_stitch, split_vars)
  split_var_grid = get_grid(True, samples_to_stitch, event_counts_unbinned)
  split_var_names_full = get_grid(False, samples_to_stitch, event_counts_unbinned)
  split_var_sum_mapping = get_sum_mapping(split_var_grid, split_var_names_full)
  split_var_names_full_linear = list(sorted(set(flatten(
    split_var_name_full.split('_') for split_var_name_full in split_var_names_full
  ))))
  samples_to_stitch_wlumiscale = comp_lumiscale(samples_to_stitch)
  lumiscale_table = print_lumiscale(samples_to_stitch_wlumiscale, era, use_full_weight)

  samples_to_stitch_wbinnedcounts = get_binned_counts(
    samples_to_stitch_wlumiscale, split_var_grid, split_var_names_full, event_counts_unbinned,
    split_var_sum_mapping, split_var_names_full_linear, del_var
  )
  binned_count_table = print_event_counts(samples_to_stitch_wbinnedcounts, era, use_full_weight)

  binstat, binstat_meta = get_binstats(samples_to_stitch_wbinnedcounts, split_var_grid)
  binstats_table = print_binstats(binstat, binstat_meta, era, use_full_weight)

  samples_to_stitch_wstitching = comp_stitching_weights(samples_to_stitch_wbinnedcounts, binstat)
  stitching_table = print_stitching_weights(samples_to_stitch_wstitching, era, use_full_weight)

  ratio_table = get_ratio_table(samples_to_stitch_wstitching, era, inclusive_xs, use_full_weight)

  content_entries = []
  block_title = ''
  if counter >= 0:
    tables = [
      lumiscale_table, binned_count_table, binstats_table, stitching_table, ratio_table
    ]
    exclude_str = ''
    if del_var:
      if del_var == 'inclusive':
        exclude_str = ', excluding inclusive samples'
      else:
        exclude_str = ', excluding samples binned by {}'.format(del_var)
    block_title = '{}{}, at {}, {}'.format(
      samples_to_stitch['meta'], exclude_str, samples_to_stitch['order'], era
    )
    captions = [
      '{} ({})'.format(caption_base, block_title) for caption_base in CAPTIONS_BASE
    ]

    for content_idx in range(len(tables)):
      content_entries.append([
        tables[content_idx], captions[content_idx]
      ])
  return samples_to_stitch_wstitching, content_entries, block_title

def stitch(era, use_full_weight):
  samples, samples_to_stitch_dict = load_sample(era)
  content = []
  counter = 0
  for idx in range(len(samples_to_stitch_dict)):
    samples_to_stitch_orig = read_dict(samples_to_stitch_dict, samples, idx)
    del_vars = ['']
    if len(samples_to_stitch_orig['exclusive']) > 1:
      del_vars.extend(list(samples_to_stitch_orig['exclusive'].keys()))
      del_vars.append('inclusive')
    for del_var in del_vars:
      stitch_results = run_stitch(era, samples_to_stitch_orig, del_var, use_full_weight, counter)
      stitch_results += (era, idx, del_var)
      content.append(stitch_results)

      counter += 1
  return content

def build_grid(split_vars, bin_keys):
  parsed_keys = collections.OrderedDict()
  for bin_key in bin_keys:
    parsed_keys[bin_key] = parse_bin(bin_key)
  spectrum = collections.OrderedDict([(split_var, []) for split_var in split_vars])
  for bin_key in parsed_keys:
    for split_var in parsed_keys[bin_key]:
      assert(split_var in spectrum)
      for split_val in parsed_keys[bin_key][split_var]:
        if split_val not in spectrum[split_var]:
          spectrum[split_var].append(split_val)
  for split_var in spectrum:
    spectrum[split_var] = list(sorted(spectrum[split_var]))
    if not SPLIT_VAR_MAP[split_var]['encode_end']:
      spectrum[split_var].append(spectrum[split_var][-1] + 1)

  labels = []
  for split_var in split_vars:
    label_arr = []
    for var_idx in range(len(spectrum[split_var]) - 1):
      label_arr.append('{} <= {} < {}'.format(
        spectrum[split_var][var_idx], split_var, spectrum[split_var][var_idx + 1]
      ))
    labels.append(label_arr)

  grid = collections.OrderedDict()
  for bin_key in parsed_keys:
    idxs = [spectrum[split_var].index(parsed_keys[bin_key][split_var][0]) for split_var in split_vars]
    assert(all(idx >= 0 for idx in idxs))
    assert(all(
      idxs[split_var_idx] < len(labels[split_var_idx]) for split_var_idx in range(len(split_vars))
    ))
    grid[bin_key] = idxs

  return grid, labels, spectrum

def save_root(content, required_era, output_fn):
  root_data = collections.OrderedDict()
  for content_entry in content:
    samples_to_stitch, content_data, block_title, era, idx, del_var = content_entry
    if era != required_era:
      continue
    split_vars = get_split_vars(samples_to_stitch, check_inclusive = False)
    combo_name = '_v_'.join(split_vars)
    if del_var:
      assert(del_var not in samples_to_stitch['exclusive'])
    if 'inclusive' not in samples_to_stitch:
      assert(del_var == 'inclusive')
      combo_name += '_wo_inclusive'

    if 'inclusive' in samples_to_stitch:
      sample_inc = samples_to_stitch['inclusive']
      for sample_name in sample_inc['samples']:
        if sample_name not in root_data:
          root_data[sample_name] = collections.OrderedDict()
        assert(combo_name not in root_data[sample_name])
        root_data[sample_name][combo_name] = collections.OrderedDict()
        grid, labels, spectrum = build_grid(split_vars, sample_inc['stitching'].keys())
        dims = [len(label_arr) for label_arr in labels]
        root_data[sample_name][combo_name]['labels'] = labels
        root_data[sample_name][combo_name]['binning'] = spectrum
        for bin_name in sample_inc['stitching']:
          for count_name in sample_inc['stitching'][bin_name]:
            count_name_len = len(sample_inc['stitching'][bin_name][count_name])
            count_names = [
              '{}_{}'.format(count_name, count_idx) for count_idx in range(count_name_len)
            ]
            for count_idx, count_name_cand in enumerate(count_names):
              if count_name_cand not in root_data[sample_name][combo_name]:
                root_data[sample_name][combo_name][count_name_cand] = np.zeros(dims)
              bin_idxs = tuple(grid[bin_name])
              root_data[sample_name][combo_name][count_name_cand][bin_idxs] = \
                sample_inc['stitching'][bin_name][count_name][count_idx]
    for split_var in split_vars:
      for sample_idx in range(len(samples_to_stitch['exclusive'][split_var])):
        sample_exc = samples_to_stitch['exclusive'][split_var][sample_idx]
        for sample_name in sample_exc['samples']:
          if sample_name not in root_data:
            root_data[sample_name] = collections.OrderedDict()
          assert(combo_name not in root_data[sample_name])
          root_data[sample_name][combo_name] = collections.OrderedDict()
          grid, labels, spectrum = build_grid(split_vars, sample_exc['stitching'].keys())
          dims = [len(label_arr) for label_arr in labels]
          root_data[sample_name][combo_name]['labels'] = labels
          root_data[sample_name][combo_name]['binning'] = spectrum
          for bin_name in sample_exc['stitching']:
            for count_name in sample_exc['stitching'][bin_name]:
              count_name_len = len(sample_exc['stitching'][bin_name][count_name])
              count_names = [
                '{}_{}'.format(count_name, count_idx) for count_idx in range(count_name_len)
              ]
              for count_idx, count_name_cand in enumerate(count_names):
                if count_name_cand not in root_data[sample_name][combo_name]:
                  root_data[sample_name][combo_name][count_name_cand] = np.zeros(dims)
                bin_idxs = tuple(grid[bin_name])
                root_data[sample_name][combo_name][count_name_cand][bin_idxs] = \
                  sample_exc['stitching'][bin_name][count_name][count_idx]

  fptr = ROOT.TFile.Open(output_fn, 'recreate')
  for sample_name in root_data:
    sample_dir = fptr.mkdir(sample_name)
    sample_dir.cd()
    for combo_name in root_data[sample_name]:
      combo_dir = sample_dir.mkdir(combo_name)
      combo_dir.cd()

      assert('labels' in root_data[sample_name][combo_name])
      labels = copy.deepcopy(root_data[sample_name][combo_name]['labels'])
      del root_data[sample_name][combo_name]['labels']

      assert('binning' in root_data[sample_name][combo_name])
      binning = copy.deepcopy(root_data[sample_name][combo_name]['binning'])
      del root_data[sample_name][combo_name]['binning']

      axis_labels = list(binning.keys())

      for count_name in root_data[sample_name][combo_name]:
        if len(labels) == 1:
          assert(len(binning) == 1)
          xlabels = labels[0]
          xaxis_title = axis_labels[0]
          xbinning = array.array('f', binning[xaxis_title])

          histogram = ROOT.TH1D(
            count_name, count_name, len(xbinning) - 1, xbinning
          )
          histogram.SetDirectory(combo_dir)
          histogram.SetXTitle(xaxis_title)

          for bin_idx, bin_label in enumerate(xlabels):
            histogram.GetXaxis().SetBinLabel(bin_idx + 1, bin_label)

          for xidx in range(len(xlabels)):
            histogram.SetBinContent(xidx + 1, root_data[sample_name][combo_name][count_name][xidx])

          histogram.Write()
        elif len(labels) == 2:
          assert(len(binning) == 2)
          xlabels = labels[0]
          ylabels = labels[1]

          xaxis_title = axis_labels[0]
          yaxis_title = axis_labels[1]
          xbinning = array.array('f', binning[xaxis_title])
          ybinning = array.array('f', binning[yaxis_title])

          histogram = ROOT.TH2D(
            count_name, count_name, len(xbinning) - 1, xbinning, len(ybinning) - 1, ybinning
          )
          histogram.SetDirectory(combo_dir)
          histogram.SetXTitle(xaxis_title)
          histogram.SetYTitle(yaxis_title)
          for bin_idx, bin_label in enumerate(xlabels):
            histogram.GetXaxis().SetBinLabel(bin_idx + 1, bin_label)
          for bin_idx, bin_label in enumerate(ylabels):
            histogram.GetYaxis().SetBinLabel(bin_idx + 1, bin_label)
          histogram.SetOption("col text")

          for xidx in range(len(xlabels)):
            for yidx in range(len(ylabels)):
              histogram.SetBinContent(
                xidx + 1, yidx + 1, root_data[sample_name][combo_name][count_name][xidx, yidx]
              )

          histogram.Write()
        else:
          raise RuntimeError("Unexpected dimension: %d" % len(labels))
  fptr.Close()
  return

parser = argparse.ArgumentParser(
    formatter_class = lambda prog: SmartFormatter(prog, max_help_position = 35)
)
parser.add_argument('-e', '--era',
  type = str, dest = 'era', metavar = 'era', required = False, choices = ERA_CHOICES, nargs = '+', default = ERA_CHOICES,
  help = 'R|Era',
)
parser.add_argument('-r', '--report',
  type = str, dest = 'report', metavar = 'path', required = False,
  help = 'R|Report file name',
)
parser.add_argument('-f', '--full-weight',
  dest = 'full_weight', action = 'store_true', default = False,
  help = 'R|Use the full generator level weights in the final report',
)
parser.add_argument('-o', '--output',
  type = str, dest = 'output', metavar = 'path', required = False,
  default = os.path.join(os.environ['CMSSW_BASE'], 'src', 'tthAnalysis', 'HiggsToTauTau', 'data'),
  help = 'R|Output directory',
)
args = parser.parse_args()
eras = args.era
use_full_weight = args.full_weight
report_name = args.report
output = os.path.abspath(args.output)

if report_name:
  if not report_name.lower().endswith('.html'):
    raise ValueError("Report name must end with HTML extension")
  report_dir = os.path.abspath(os.path.dirname(report_name))
  if not os.path.isdir(report_dir):
    raise ValueError("Directory of the requested report file does not exist: %s" % report_dir)

if not os.path.isdir(output):
  raise ValueError("No such directory: %s" % output)

content = []
for era in eras:
  content.extend(stitch(era, use_full_weight))

if report_name:
  write_report(report_name, content)

for era in eras:
  output_file_name = os.path.join(output, 'stitched_weights_{}.root'.format(era))
  save_root(content, era, output_file_name)
