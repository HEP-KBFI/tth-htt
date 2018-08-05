#!/usr/bin/env python

# Example usage:
#
# validate_lumiscale.py \
#   -i /some/path/to/histograms_harvested_stage1_2lss_1tau_{sample_name}_Tight_lepSS_sumOS.root \
#   -o ~/some/output/dir -f -v -e 2017
#
# The script creates plots showing the expected effective event counts (dashed black) and
# actual effective event counts (solid, colored) with error bars attached to the latter.
# Prints warning statements if the expected effective event count is outside any error bars;
# prints error messages if input files are missing; throws runtime errors if there are inconsistencies
# in the number of files or histograms that cover the same phase space, or if the number of entries
# doesn't match to the expected nof entries.

import argparse
import os
import sys
import logging
import ROOT
import math

# the first entry in each array must be inclusive
samples_to_sum_2017 = [
  [
    'DYJetsToLL_M-50',                'DYJetsToLL_M-50_ext1',
    'DY1JetsToLL_M-50',               'DY1JetsToLL_M-50_ext1',
    'DY2JetsToLL_M-50',               'DY2JetsToLL_M-50_ext1',
    'DY3JetsToLL_M-50',               'DY3JetsToLL_M-50_ext1',
    'DY4JetsToLL_M-50',
    'DYJetsToLL_M50_HT100to200',      'DYJetsToLL_M50_HT100to200_ext1',
    'DYJetsToLL_M50_HT200to400',      'DYJetsToLL_M50_HT200to400_ext1',
    'DYJetsToLL_M50_HT400to600',      'DYJetsToLL_M50_HT400to600_ext1',
    'DYJetsToLL_M50_HT600to800',
    'DYJetsToLL_M50_HT800to1200',
    'DYJetsToLL_M50_HT1200to2500',
    'DYJetsToLL_M50_HT2500toInf',
  ],
  [
    'DYJetsToLL_M-10to50',
    'DYJetsToLL_M-4to50_HT-70to100',  'DYJetsToLL_M-4to50_HT-70to100_ext1',
    'DYJetsToLL_M-4to50_HT-100to200', 'DYJetsToLL_M-4to50_HT-100to200_ext1',
    'DYJetsToLL_M-4to50_HT-200to400', 'DYJetsToLL_M-4to50_HT-200to400_ext1',
    'DYJetsToLL_M-4to50_HT-400to600', 'DYJetsToLL_M-4to50_HT-400to600_ext1',
    'DYJetsToLL_M-4to50_HT-600toInf',
  ],
  [
    'WJetsToLNu',
    'W1JetsToLNu',
    'W2JetsToLNu',
    'W3JetsToLNu',
    'W4JetsToLNu',
    'WJetsToLNu_HT100To200',
    'WJetsToLNu_HT200To400',
    'WJetsToLNu_HT400To600',
    'WJetsToLNu_HT600To800',
    'WJetsToLNu_HT800To1200',
    'WJetsToLNu_HT1200To2500',
    'WJetsToLNu_HT2500ToInf',
  ],
  [ 'GluGluHToZZTo4L',                'GluGluHToZZTo4L_ext1',                   ],
  [ 'ST_s-channel_4f_leptonDecays',   'ST_s-channel_4f_leptonDecays_PSweights', ],
  [ 'ST_tW_top_5f_inclusiveDecays',   'ST_tW_top_5f_inclusiveDecays_PSweights', ],
  [ 'ZZTo4L',                         'ZZTo4L_ext1',                            ],
  [ 'TTToHadronic',                   'TTToHadronic_PSweights',                 ],
  [ 'TTToSemiLeptonic',               'TTToSemiLeptonic_PSweights',             ],
  [ 'TTTo2L2Nu',                      'TTTo2L2Nu_PSweights',                    ],
  [ 'TTWJetsToLNu',                   'TTWJetsToLNu_PSweights',                 ],
  [ 'TTZToLL_M10',                    'TTZToLL_M10_PSweights',                  ],
  [ 'TTGJets',                        'TTGJets_ext1',                           ],
  [ 'WWToLNuQQ',                      'WWToLNuQQ_ext1',                         ],
]

def plot(input_files, output_files, title, expected_neff, mode):
  histogram_dict = {}
  for sample_name, sample_entry in input_files.items():
    if not os.path.isfile(sample_entry['input']):
      logging.error('Could not find file {}'.format(sample_entry['input']))
      continue
    root_file = ROOT.TFile.Open(sample_entry['input'], 'read')
    logging.debug('Opened file {}'.format(sample_entry['input']))
    root_directories = list(filter(
      lambda root_dir: root_dir != None, [
        root_file.Get(os.path.join(key.GetName(), mode, 'genEvt')) \
        for key in root_file.GetListOfKeys() if key.GetClassName() == 'TDirectoryFile'
      ]
    ))
    if len(root_directories) != 1:
      raise RuntimeError('Expected single directory in %s' % sample_entry['input'])
    root_dir = root_directories[0]
    histogram_dirs = [
      root_dir.Get(key.GetName()) \
      for key in root_dir.GetListOfKeys() if key.GetClassName() == 'TDirectoryFile'
    ]
    if len(histogram_dirs) != 1:
      raise RuntimeError(
        'Expected single directory containing lumiScale histograms in %s' % sample_entry['input']
      )
    histogram_dir = histogram_dirs[0]
    histograms = [
      key.GetName() for key in histogram_dir.GetListOfKeys() \
      if key.GetClassName().startswith('TH1') and 'lumiScale' in key.GetName()
    ]
    for histogram_name_actual in histograms:
      histogram_name = histogram_name_actual.replace('_lumiScale', '').replace('CMS_ttHl_', '') \
                       if histogram_name_actual != 'lumiScale' else 'central'
      histogram = histogram_dir.Get(histogram_name_actual).Clone()
      histogram.SetDirectory(0)
      if histogram.GetEntries() != sample_entry['nentries'] and mode == 'unbiased':
        raise RuntimeError('Expected {} entries from {} in file {}, but got {} entries'.format(
          sample_entry['nentries'], histogram_name, sample_entry['input'], histogram.GetEntries(),
        ))
      if histogram_name not in histogram_dict:
        histogram_dict[histogram_name] = {
          'histogram' : histogram,
          'nentries'  : histogram.GetEntries(),
          'nfiles'    : 1,
        }
      else:
        histogram_dict[histogram_name]['histogram'].Add(histogram)
        histogram_dict[histogram_name]['nentries'] += histogram.GetEntries()
        histogram_dict[histogram_name]['nfiles'] += 1

    root_file.Close()

  if not histogram_dict:
    logging.error('Could not find histograms for samples {}'.format(', '.join(list(input_files.keys()))))
    return

  if len(set(histogram_dict[histogram_name]['nfiles'] for histogram_name in histogram_dict)) != 1:
    raise RuntimeError(
      'Inconsistent number of files found for samples %s' % ', '.join(list(input_files.keys()))
    )
  if len(set(histogram_dict[histogram_name]['nentries'] for histogram_name in histogram_dict)) != 1:
    raise RuntimeError(
      'Inconsistent number of entries found in samples %s' % ', '.join(list(input_files.keys()))
    )

  min_y = -1
  max_y = -1
  nentries = -1
  for histograms in histogram_dict.values():
    histogram = histograms['histogram']
    y_content = histogram.GetBinContent(1)
    y_error   = histogram.GetBinError(1)

    y_down = y_content - y_error
    y_up   = y_content + y_error

    if min_y < 0:
      min_y = y_down
    if max_y < 0:
      max_y = y_up
    if y_down < min_y:
      min_y = y_down
    if y_up > max_y:
      max_y = y_up

    if nentries < 0:
      nentries = histograms['nentries']
    else:
      assert(nentries == histograms['nentries'])

    if not (y_down < expected_neff < y_up) and mode == 'unbiased':
      logging.warning(
        "Effective event count {} not within {} +- {}".format(expected_neff, y_content, y_error)
      )

  if mode == 'unbiased':
    min_y = min(min_y, expected_neff)
    max_y = max(max_y, expected_neff)
  diff = 0.2 * (max_y - min_y)
  min_y -= diff
  max_y += diff

  canvas = ROOT.TCanvas('c', 'c', 1200, 900)
  canvas.SetGrid()
  ROOT.gStyle.SetOptStat(0)

  legend = ROOT.TLegend(0.1, 0.7, 0.48, 0.9)
  legend.SetHeader('N_{eff} (%d entries)' % nentries)

  expected_histogram = None

  line_width = 3
  marker_style = 20
  fill_style = 4000

  lines = []

  for idx, histogram_name in enumerate(sorted(histogram_dict.keys())):
    histogram = histogram_dict[histogram_name]['histogram']
    color = 2 + idx

    histogram.SetTitle(title)
    histogram.SetAxisRange(min_y, max_y, "Y")
    histogram.SetLineColor(color)
    histogram.SetMarkerColor(color)
    histogram.SetLineWidth(line_width)
    histogram.SetMarkerStyle(marker_style)
    histogram.SetFillStyle(fill_style)
    histogram.Draw("l e1%s" % (" same" if idx > 0 else ""))

    y_content = histogram.GetBinContent(1)
    y_error   = histogram.GetBinError(1)
    y_up      = y_content + y_error
    y_down    = y_content - y_error

    bin_width  = histogram.GetBinWidth(1)
    bin_center = histogram.GetBinCenter(1)
    line_min_x = bin_center - bin_width / 4
    line_max_x = bin_center + bin_width / 4

    line_down = ROOT.TLine(line_min_x, y_down, line_max_x, y_down)
    line_down.SetLineColor(color)
    line_down.SetLineWidth(line_width)
    line_down.Draw()
    lines.append(line_down)

    line_up = ROOT.TLine(line_min_x, y_up, line_max_x, y_up)
    line_up.SetLineColor(color)
    line_up.SetLineWidth(line_width)
    line_up.Draw()
    lines.append(line_up)

    sig_digits = max(8 - int(math.ceil(math.log10(y_content))), 1) if y_content > 0. else 1
    leg_pattern = '%s (%.{}f #pm %.{}f)'.format(sig_digits, sig_digits)
    leg_name = leg_pattern % (histogram_name, y_content, y_error)
    legend.AddEntry(histogram, leg_name)

    logging.debug(
      'Effective event count for the sys unc option {} is {} +- {}'.format(
        histogram_name, y_content, y_error
      )
    )

    if not expected_histogram and mode == 'unbiased':
      expected_histogram = histogram.Clone()
      expected_histogram.Reset()
      expected_histogram.SetBinContent(1, expected_neff)
      expected_histogram.SetBinError(1, 0)
      expected_histogram.SetLineColor(ROOT.kBlack)
      expected_histogram.SetMarkerColor(ROOT.kBlack)
      expected_histogram.SetLineWidth(line_width)
      expected_histogram.SetMarkerStyle(marker_style)
      expected_histogram.SetLineStyle(9)
      expected_histogram.SetFillStyle(fill_style)

  if expected_histogram:
    logging.debug('Expecting {} events'.format(expected_neff))
    expected_histogram.Draw("e2 same")
    legend.AddEntry(expected_histogram, 'expected (%.1f)' % expected_neff)

  legend.Draw()

  for output_file in output_files:
    canvas.SaveAs(output_file)

  canvas.Close()
  legend.Delete()
  if expected_histogram:
    expected_histogram.Delete()
  for histogram_name in histogram_dict:
    histogram_dict[histogram_name]['histogram'].Delete()
  for line in lines:
    line.Delete()

class SmartFormatter(argparse.HelpFormatter):
  def _split_lines(self, text, width):
    if text.startswith('R|'):
      return text[2:].splitlines()
    return argparse.HelpFormatter._split_lines(self, text, width)

parser = argparse.ArgumentParser(
    formatter_class = lambda prog: SmartFormatter(prog, max_help_position = 35)
)

parser.add_argument('-e', '--era',
  type = str, dest = 'era', metavar = 'era', required = False, choices = [ '2017' ], default = '2017',
  help = 'R|Path to the sample dictionary',
)
parser.add_argument('-m', '--mode',
  type = str, dest = 'mode', metavar = 'mode', required = True, choices = [ 'sel', 'unbiased' ],
  default = 'unbiased',
  help = 'R|Draw effective event counts for fully inclusive or for selected events',
)
parser.add_argument('-i', '--input',
  type = str, dest = 'input', metavar = 'pattern', required = True,
  help = 'R|Input pattern to stage 1 histograms (must contain {sample_name} !)',
)
parser.add_argument('-o', '--output',
  type = str, dest = 'output', metavar = 'path', required = True,
  help = 'R|Output directory where the plots are saved',
)
parser.add_argument('-x', '--extension',
  type = str, nargs = '+', dest = 'extension', metavar ='ext', required = False,
  choices = [ 'png', 'pdf' ], default = [ 'png', 'pdf' ],
  help = 'R|Extension of the output files',
)
parser.add_argument('-f', '--force',
  dest = 'force', action = 'store_true', default = False,
  help = 'R|Create the output directory if it does not exist',
)
parser.add_argument('-v', '--verbose',
  dest = 'verbose', action = 'store_true', default = False,
  help = 'R|Enable verbose output',
)

args = parser.parse_args()

logging.basicConfig(
  stream = sys.stdout,
  level  = logging.DEBUG if args.verbose else logging.INFO,
  format = '%(asctime)s - %(levelname)s: %(message)s'
)

pattern = args.input
if '{sample_name}' not in pattern:
  raise ValueError('No {sample_name} found in pattern %s' % pattern)

input_dir = os.path.dirname(pattern)
if not os.path.isdir(input_dir):
  raise ValueError('No such input directory: %s' % input_dir)

if args.era == '2017':
  from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017 import samples_2017 as samples
  from tthAnalysis.HiggsToTauTau.analysisSettings import lumi_2017 as lumi
  samples_to_sum = samples_to_sum_2017

  # We need to add DY 4-jet cross section to the inclusive cross section b/c it's not covered
  # by the inclusive sample, but is covered by HT-binned samples which overlap w/ the inclusive sample.
  samples_lut = {}
  for sample_key, sample_entry in samples.items():
    if sample_key == 'sum_events': continue
    sample_name = sample_entry['process_name_specific']
    assert(sample_name not in samples_lut)
    samples_lut[sample_name] = sample_key
  samples[samples_lut['DYJetsToLL_M-50']]['xsection'] += samples[samples_lut['DY4JetsToLL_M-50']]['xsection']
else:
  raise RuntimeError('Invalid era: %s' % args.era)
if 'sum_events' in samples:
  del samples['sum_events']

# construct a list of samples that cover the same phase space
valid_samples_to_sum = []
valid_samples_to_sum_flat = []
for sample_list in samples_to_sum:
  inclusive_sample = sample_list[0]
  inclusive_xs = -1
  valid_samples = []
  nentries = {}
  for sample in sample_list:
    for sample_entry in samples.values():
      sample_name = sample_entry['process_name_specific']
      if sample_name in sample_list:
        if sample_entry['use_it'] and sample_name not in valid_samples:
          valid_samples.append(sample_name)
          nentries[sample_name] = sample_entry['nof_tree_events']
          if sample_name not in valid_samples_to_sum_flat:
            valid_samples_to_sum_flat.append(sample_name)
          if sample_name == inclusive_sample:
            inclusive_xs = sample_entry['xsection']
  if inclusive_xs < 0:
    raise RuntimeError('No xs inclusive xs found for samples: %s' % ', '.join(sample_list))
  valid_samples_to_sum.append({
    'xs'       : inclusive_xs,
    'samples'  : valid_samples,
    'nentries' : nentries,
    'label'    : inclusive_sample,
  })

for sample_entry in samples.values():
  sample_name = sample_entry['process_name_specific']
  if sample_name not in valid_samples_to_sum_flat and sample_entry['type'] != 'data':
    valid_samples_to_sum.append({
      'xs'       : sample_entry['xsection'],
      'samples'  : [ sample_name ],
      'nentries' : { sample_name : sample_entry['nof_tree_events'] },
      'label'    : sample_name,
    })

if not os.path.isdir(args.output):
  if not args.force:
    raise ValueError('Use -f/--force to create output directory %s' % args.output)
  os.makedirs(args.output)

for valid_samples in valid_samples_to_sum:
  input_files = {
    sample_name : {
        'input'    : pattern.format(sample_name = sample_name),
        'nentries' : valid_samples['nentries'][sample_name],
    } for sample_name in valid_samples['samples']
  }
  output_files = [
    os.path.join(args.output, '%s.%s' % (valid_samples['label'], ext)) for ext in args.extension
  ]
  expected_neff = lumi * valid_samples['xs']
  plot(input_files, output_files, valid_samples['label'], expected_neff, args.mode)
