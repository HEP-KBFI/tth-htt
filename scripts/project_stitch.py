#!/usr/bin/env python

from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017_nanoAOD import samples_2017 as samples
from tthAnalysis.HiggsToTauTau.samples.stitch_2017 import samples_to_stitch_2017 as samples_to_stitch
from tthAnalysis.HiggsToTauTau.jobTools import create_if_not_exists, run_cmd

import itertools
import os
import ROOT
import array

def project(input_file, output_file, binnings):
  if not os.path.isfile(input_file):
    raise RuntimeError('No such file: %s' % input_file)
  root_file = ROOT.TFile.Open(input_file, 'read')
  if not root_file:
    print('Unable to read file %s' % input_file)
    return False
  events = root_file.Get('Events')
  assert(events)

  histograms = []
  for branch_name, binning_array in binnings.items():
    binning = array.array('f', binning_array)
    histogram = ROOT.TH1F(branch_name, branch_name, len(binning) - 1, binning)
    assert(histogram)
    events.Project(branch_name, branch_name)
    histograms.append(histogram)

  out_file = ROOT.TFile.Open(output_file, 'recreate')
  out_file.cd()
  for histogram in histograms:
    histogram.Write()

  out_file.Close()
  root_file.Close()
  return True

def hadd(input_files, output_file):
  cmd_str = 'hadd -f %s %s' % (output_file, ' '.join(input_files))
  stdout, stderr = run_cmd(cmd_str, do_not_log = True, return_stderr = True)
  if not stdout or stderr:
    raise RuntimeError('Error: %s' % stderr)

output_root_dir = os.path.expanduser('~/sandbox/stitch_samples/root_files')
output_plot_dir = os.path.expanduser('~/sandbox/stitch_samples/plots')

for output_dir in [ output_root_dir, output_plot_dir ]:
  create_if_not_exists(output_dir)

for sample_set_to_stich in samples_to_stitch:
  binning_keys = filter(lambda key: key != 'inclusive', sample_set_to_stich.keys())

  sample_list = []
  for key in sample_set_to_stich:
    if key == 'inclusive':
      sample_list.extend(sample_set_to_stich[key]['samples'])
    else:
      for binned_sample in sample_set_to_stich[key]:
        sample_list.extend(binned_sample['samples'])
  assert(len(sample_list) == len(set(sample_list)))

  binning = {}
  for binning_key in binning_keys:
    inclusive_binning = sample_set_to_stich['inclusive'][binning_key]
    split_binning = [ curr_binning['value'] for curr_binning in sample_set_to_stich[binning_key] ]
    complete_binning = list(sorted(list(
      map(float, set(inclusive_binning) | set(list(itertools.chain.from_iterable(split_binning))))
    )))
    print('Full binning for %s: %s' % (binning_key, ', '.join(map(str, complete_binning))))
    binning[binning_key] = complete_binning

  for sample_key, sample_entry in samples.items():
    if sample_key == 'sum_events': continue
    sample_name = sample_entry['process_name_specific']
    if sample_name in sample_list:
      base_path = sample_entry['local_paths'][0]['path']
      nof_files = sample_entry['nof_files']
      blacklist = sample_entry['local_paths'][0]['blacklist']

      current_subfolder = os.path.join(output_root_dir, sample_name)
      create_if_not_exists(current_subfolder)

      output_files = []
      final_output_file = os.path.join(output_root_dir, '%s.root' % sample_name)

      for idx in range(1, nof_files + 1):
        if idx in blacklist:
          continue
        input_file = os.path.join(base_path, '%04d' % (idx // 1000), 'tree_%d.root' % idx)
        output_file = os.path.join(current_subfolder, 'histogram_%d.root' % idx)
        file_exists = project(input_file, output_file, binning)
        if file_exists:
          output_files.append(output_file)

      hadd(output_files, final_output_file)

      root_file = ROOT.TFile.Open(final_output_file, 'read')
      for binning_key in binning:
        canvas = ROOT.TCanvas('c', 'c', 1200, 900)

        histogram = root_file.Get(binning_key)
        canvas.SetLogy()
        if binning_key == 'LHE_HT':
          canvas.SetLogx()
        histogram.SetTitle(sample_name)
        histogram.SetXTitle(binning_key)
        histogram.Draw()
        for extension in [ 'pdf', 'png' ]:
          plot_file = os.path.join(output_plot_dir, '%s_%s.%s' % (sample_name, binning_key, extension))
          canvas.SaveAs(plot_file)
        del histogram
        del canvas
      root_file.Close()




