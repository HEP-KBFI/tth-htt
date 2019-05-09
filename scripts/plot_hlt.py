#!/usr/bin/env python

# Example:
# plot_htl.py -i HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL.csv -j HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ.csv -o ~/plots -e 2016

import math
import collections
import datetime
import argparse
import os

import numpy as np
import matplotlib.pyplot as plt
import matplotlib.offsetbox as obox

runs = {
  '2016' : collections.OrderedDict([
    ('B', { 'ranges' : (273150,275376), 'delivered' : 5.991, 'recorded' : 5.750 }),
    ('C', { 'ranges' : (275656,276283), 'delivered' : 2.685, 'recorded' : 2.573 }),
    ('D', { 'ranges' : (276315,276811), 'delivered' : 4.411, 'recorded' : 4.242 }),
    ('E', { 'ranges' : (276831,277420), 'delivered' : 4.222, 'recorded' : 4.025 }),
    ('F', { 'ranges' : (277932,278808), 'delivered' : 3.283, 'recorded' : 3.105 }),
    ('G', { 'ranges' : (278820,280385), 'delivered' : 7.865, 'recorded' : 7.576 }),
    ('H', { 'ranges' : (281613,284044), 'delivered' : 8.985, 'recorded' : 8.651 }),
  ]),
  '2017' : collections.OrderedDict([
    ('B', { 'ranges' : (297047,299329), 'delivered' :  5.023, 'recorded' :  4.794 }),
    ('C', { 'ranges' : (299368,302029), 'delivered' : 10.308, 'recorded' :  9.633 }),
    ('D', { 'ranges' : (302030,302663), 'delivered' :  4.368, 'recorded' :  4.248 }),
    ('E', { 'ranges' : (303818,304797), 'delivered' :  9.760, 'recorded' :  9.314 }),
    ('F', { 'ranges' : (305040,306462), 'delivered' : 14.185, 'recorded' : 13.539 }),
  ]),
  '2018' : collections.OrderedDict([
    ('A', { 'ranges' : (315257,316995), 'delivered' : 14.497, 'recorded' : 14.027 }),
    ('B', { 'ranges' : (317080,319310), 'delivered' :  7.310, 'recorded' :  7.061 }),
    ('C', { 'ranges' : (319337,320065), 'delivered' :  7.143, 'recorded' :  6.895 }),
    ('D', { 'ranges' : (320497,325175), 'delivered' : 33.011, 'recorded' : 31.743 }),
  ])
}

class SmartFormatter(argparse.ArgumentDefaultsHelpFormatter):
  def _split_lines(self, text, width):
    if text.startswith('R|'):
      return text[2:].splitlines()
    return argparse.ArgumentDefaultsHelpFormatter._split_lines(self, text, width)

def get_acq_era(run_nr, era):
  for acq_era, run_range in runs[era].items():
    if run_range['ranges'][0] <= run_nr <= run_range['ranges'][1]:
      return acq_era
  raise RuntimeError('Invalid run nr: %d' % run_nr)

def read_data(filename, era):
  data = []
  # TODO PARSE UNITS
  with open(filename, 'r') as file_ptr:
    cumul_delivered, cumul_recorded = 0., 0.
    for line in file_ptr:
      if line.startswith('#'):
        continue
      line_stripped = line.rstrip('\n')
      if not line_stripped:
        continue
      line_split = line_stripped.split(',')

      run       = int(line_split[0].split(':')[0])
      fill      = int(line_split[0].split(':')[1])
      dt        = datetime.datetime.strptime(line_split[1], '%m/%d/%y %H:%M:%S')
      ncms      = int(line_split[2])
      hltpath   = line_split[3]
      delivered = float(line_split[4])
      recorded  = float(line_split[5])

      era_key = get_acq_era(run, era)

      cumul_delivered += delivered
      cumul_recorded += recorded

      data.append({
        'run'                  : run,
        'era'                  : era_key,
        'fill'                 : fill,
        'dt'                   : dt,
        'ncms'                 : ncms,
        'hltpath'              : hltpath,
        'delivered'            : delivered,
        'recorded'             : recorded,
        'cumulative_delivered' : cumul_delivered,
        'cumulative_recorded'  : cumul_recorded,
      })
  return data

def plot_single(data, label, era, output_dir, is_cumul, is_sequential, is_recorded = True):
  fig, ax = plt.subplots(figsize = (10, 8), dpi = 120)

  figure_type = 'recorded' if is_recorded else 'delivered'
  subject = '{}{}'.format('cumulative_' if is_cumul else '', figure_type)

  ylim = (
    10 ** math.floor(math.log10(min(map(lambda x: x[subject], data)))),
    10 ** math.ceil (math.log10(max(map(lambda x: x[subject], data))))
  )

  run_count = 0
  runmap = {}
  expected_cumul = 0.

  has_labeled = False
  for era_idx, era_key in enumerate(runs[era]):
    if not has_labeled:
      has_labeled = True
      label_on_plot = label
    else:
      label_on_plot = ''

    run_len = len(list(map(lambda x: x['run'], filter(lambda y: y['era'] == era_key, data))))
    xrange_run_count = list(range(run_count, run_count + run_len))

    xrange_run_real = list(map(lambda x: x['run'], filter(lambda y: y['era'] == era_key, data)))

    xrange_plot = xrange_run_count if is_sequential else xrange_run_real

    ax.plot(
      xrange_plot,
      list(map(lambda x: x[subject], filter(lambda y: y['era'] == era_key, data))), c = '#1f77b4', ls = '-',
      label = label_on_plot
    )

    if is_cumul and xrange_plot:
      expected_cumul += runs[era][era_key][figure_type] * 1e3
      ax.hlines(
        y = expected_cumul, xmin = xrange_plot[0], xmax=xrange_plot[-1], color = 'black', linestyle=':',
      )
      if expected_cumul > ylim[1]:
        ylim = (ylim[0], expected_cumul * 5)

    runmap[era_key] = (run_count, run_count + run_len)
    run_count += run_len

  ax.set_ylim(ylim)

  if not is_sequential:
    runmap = { era_key : runs[era][era_key]['ranges'] for era_key in runs[era] }

  era_colors = ['gray', 'olive']
  for era_idx, era_key in enumerate(runs[era]):
    ax.fill_between(runmap[era_key], *ylim, facecolor = era_colors[era_idx % 2], alpha = 0.2)
    runb_avg = (runmap[era_key][0] + runmap[era_key][1]) / 2
    ab = obox.AnnotationBbox(obox.TextArea(era_key), xy = (runb_avg, 10 * ylim[0]), xycoords = 'data')
    ax.add_artist(ab)

  plt.xlabel('Run {}'.format('index' if is_sequential else 'number'))
  plt.ylabel('{} [/pb]'.format(subject.replace('_', ' ').capitalize()))
  plt.yscale('log')
  plt.grid(True)
  plt.legend(loc = 'best')
  plt.title('Run {}'.format(era))
  out_path = os.path.join(output_dir, '{}_{}'.format(label, subject))
  if is_sequential:
    out_path += '_seq'
  out_path += '.png'
  plt.savefig(out_path, bbox_inches = 'tight')
  plt.close()

def plot_double(data1, data2, label1, label2, era, output_dir, is_cumul, is_sequential, is_recorded = True):
  fig, ax = plt.subplots(figsize = (10, 8), dpi = 120)

  figure_type = 'recorded' if is_recorded else 'delivered'
  subject = '{}{}'.format('cumulative_' if is_cumul else '', figure_type)

  ylim = (
    10 ** math.floor(math.log10(min(min(map(lambda x: x[subject], data1)), min(map(lambda x: x[subject], data2))))),
    10 ** math.ceil (math.log10(max(max(map(lambda x: x[subject], data1)), max(map(lambda x: x[subject], data2)))))
  )
  ax.set_ylim(ylim)

  run_count = 0
  runmap = {}
  expected_cumul = 0.

  has_labeled = False
  for era_idx, era_key in enumerate(runs[era]):
    if not has_labeled:
      has_labeled = True
      label1_on_plot = label1
      label2_on_plot = label2
    else:
      label1_on_plot = ''
      label2_on_plot = ''

    run_len_1 = len(list(map(lambda x: x['run'], filter(lambda y: y['era'] == era_key, data1))))
    run_len_2 = len(list(map(lambda x: x['run'], filter(lambda y: y['era'] == era_key, data2))))
    assert(run_len_1 == run_len_2)
    run_len = run_len_1
    xrange_run_count = list(range(run_count, run_count + run_len))

    xrange_run_real_1 = list(map(lambda x: x['run'], filter(lambda y: y['era'] == era_key, data1)))
    xrange_run_real_2 = list(map(lambda x: x['run'], filter(lambda y: y['era'] == era_key, data2)))
    assert(xrange_run_real_1 == xrange_run_real_2)
    xrange_run_real = xrange_run_real_1

    xrange_plot = xrange_run_count if is_sequential else xrange_run_real

    ax.plot(
      xrange_plot,
      list(map(lambda x: x[subject], filter(lambda y: y['era'] == era_key, data2))), c = '#1f77b4', ls = '-',
      label = label2_on_plot
    )
    ax.plot(
      xrange_plot,
      list(map(lambda x: x[subject], filter(lambda y: y['era'] == era_key, data1))), c = '#ff7f0e', ls = '--',
      label = label1_on_plot
    )

    if is_cumul and xrange_plot:
      expected_cumul += runs[era][era_key][figure_type] * 1e3
      ax.hlines(
        y = expected_cumul, xmin = xrange_plot[0], xmax=xrange_plot[-1], color = 'black', linestyle=':',
      )

    runmap[era_key] = (run_count, run_count + run_len)
    run_count += run_len

  if not is_sequential:
    runmap = { era_key : runs[era][era_key]['ranges'] for era_key in runs[era] }

  era_colors = ['gray', 'olive']
  for era_idx, era_key in enumerate(runs[era]):
    ax.fill_between(runmap[era_key], *ylim, facecolor = era_colors[era_idx % 2], alpha = 0.2)
    runb_avg = (runmap[era_key][0] + runmap[era_key][1]) / 2
    ab = obox.AnnotationBbox(obox.TextArea(era_key), xy = (runb_avg, 10 * ylim[0]), xycoords = 'data')
    ax.add_artist(ab)

  plt.xlabel('Run {}'.format('index' if is_sequential else 'number'))
  plt.ylabel('{} [/pb]'.format(subject.replace('_', ' ').capitalize()))
  plt.yscale('log')
  plt.grid(True)
  plt.legend(loc = 'best')
  plt.title('Run {}'.format(era))
  out_path = os.path.join(output_dir, '{}_vs_{}_{}'.format(label1, label2, subject))
  if is_sequential:
    out_path += '_seq'
  out_path += '.png'
  plt.savefig(out_path, bbox_inches = 'tight')
  plt.close()

def plot_ratio(data1, data2, label1, label2, era, output_dir, is_cumul, is_recorded = True):
  fig, ax = plt.subplots(figsize=(10, 8), dpi=120)

  subject = '{}{}'.format('cumulative_' if is_cumul else '', 'recorded' if is_recorded else 'delivered')

  run_count = 0
  runmap = {}

  min_ratio, max_ratio = 1e+6, -1

  has_labeled = False
  for era_idx, era_key in enumerate(runs[era]):

    run_len_1 = len(list(map(lambda x: x['run'], filter(lambda y: y['era'] == era_key, data1))))
    run_len_2 = len(list(map(lambda x: x['run'], filter(lambda y: y['era'] == era_key, data2))))
    assert(run_len_1 == run_len_2)
    run_len = run_len_1

    data2_vals = list(map(lambda x: x[subject], filter(lambda y: y['era'] == era_key, data2)))
    data1_vals = list(map(lambda x: x[subject], filter(lambda y: y['era'] == era_key, data1)))
    data2_data1_ratio = [data2_vals[run_idx] / data1_vals[run_idx] for run_idx in range(run_len)]

    if not data2_data1_ratio:
      continue

    data2_data1_ratio_min = min(data2_data1_ratio)
    data2_data1_ratio_max = max(data2_data1_ratio)
    if data2_data1_ratio_min < min_ratio:
      min_ratio = data2_data1_ratio_min
    if data2_data1_ratio_max > max_ratio:
      max_ratio = data2_data1_ratio_max
    ratio_mean = np.mean(data2_data1_ratio)

    if abs(1. - ratio_mean) > 1e-3 and not is_cumul:
      ax.hlines(
        y = ratio_mean, xmin = run_count, xmax = run_count + run_len, color = 'black', linestyle='--',
        label = 'Average prescale: %.1f' % ratio_mean
      )

    if not has_labeled:
      has_labeled = True
      label_on_plot = '{} / {}'.format(label2, label1)
    else:
      label_on_plot = ''

    ax.plot(
      list(range(run_count, run_count + run_len)), data2_data1_ratio, c = '#1f77b4', ls = '-', label = label_on_plot
    )

    runmap[era_key] = (run_count, run_count + run_len)
    run_count += run_len


  ylim = (min_ratio * (0.7 if is_cumul else 0), max_ratio / 0.7)
  ax.set_ylim(ylim)

  era_colors = ['gray', 'olive']
  for era_idx, era_key in enumerate(runs[era]):
    if era_key not in runmap:
      continue
    ax.fill_between(runmap[era_key], *ylim, facecolor = era_colors[era_idx % 2], alpha = 0.2)
    runb_avg = (runmap[era_key][0] + runmap[era_key][1]) / 2
    ab = obox.AnnotationBbox(obox.TextArea(era_key), xy = (runb_avg, ylim[1] * 0.8), xycoords = 'data')
    ax.add_artist(ab)

  plt.xlabel('run (indexed)')
  plt.ylabel('Ratio of {}'.format(subject.replace('_', ' ')))

  plt.grid(True)
  plt.legend(loc = 'best')
  plt.title('Run {}'.format(era))

  out_path = os.path.join(output_dir, '{}_vs_{}_{}_ratio.png'.format(label1, label2, subject))
  plt.savefig(out_path, bbox_inches = 'tight')
  plt.close()


if __name__ == '__main__':
  parser = argparse.ArgumentParser(
    formatter_class = lambda prog: SmartFormatter(prog, max_help_position=55)
  )
  parser.add_argument('-i', '--input',
    type = str, dest = 'input', metavar = 'file', required = True,
    help = 'R|First input file',
  )
  parser.add_argument('-j', '--input-second',
    type = str, dest = 'input_second', metavar = 'file', required = False,
    help = 'R|Second input file',
  )
  parser.add_argument('-o', '--output',
    type = str, dest = 'output', metavar = 'directory', required = True,
    help = 'R|Output directory where the plots will be saved',
  )
  parser.add_argument('-e', '--era',
    type = str, dest = 'era', metavar = 'year', required = True, choices = list(runs.keys()),
    help = 'R|Era',
  )
  parser.add_argument('-s', '--singles-disable',
    dest = 'singles_disable', action = 'store_true', default = False,
    help = 'R|Disable plotting single HLT paths when two inputs are given',
  )
  args = parser.parse_args()
  if args.singles_disable and not args.input_second:
    raise ValueError("Doesn't make any sense to disable single plotting")

  if not os.path.isfile(args.input):
    raise ValueError("No such file: %s" % args.input)

  if not args.singles_disable and args.input_second:
    if not os.path.isfile(args.input_second):
      raise ValueError("No such file: %s" % args.input_second)

  if not os.path.isdir(args.output):
    os.makedirs(args.output)


  data1 = read_data(args.input, args.era)
  label1 = os.path.basename(args.input).replace('.csv', '')

  if not args.singles_disable:
    plot_single(data1, label1, args.era, args.output, True, False)
    plot_single(data1, label1, args.era, args.output, False, False)
    plot_single(data1, label1, args.era, args.output, True, True)
    plot_single(data1, label1, args.era, args.output, False, True)

  if args.input_second:
    data2 = read_data(args.input_second, args.era)
    label2 = os.path.basename(args.input_second).replace('.csv', '')

    if not args.singles_disable:
      plot_single(data2, label2, args.era, args.output, True, False)
      plot_single(data2, label2, args.era, args.output, False, False)
      plot_single(data2, label2, args.era, args.output, True, True)
      plot_single(data2, label2, args.era, args.output, False, True)

    plot_double(data1, data2, label1, label2, args.era, args.output, True, False)
    plot_double(data1, data2, label1, label2, args.era, args.output, False, False)
    plot_double(data1, data2, label1, label2, args.era, args.output, True, True)
    plot_double(data1, data2, label1, label2, args.era, args.output, False, True)

    plot_ratio(data1, data2, label1, label2, args.era, args.output, False)
    plot_ratio(data1, data2, label1, label2, args.era, args.output, True)
