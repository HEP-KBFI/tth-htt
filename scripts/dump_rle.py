#!/usr/bin/env python

from tthAnalysis.HiggsToTauTau.safe_root import ROOT
from tthAnalysis.HiggsToTauTau.common import logging, SmartFormatter
from tthAnalysis.HiggsToTauTau.common import load_samples

import argparse
import os
import sys
import array

def dump_rle(input_file, output_file, tree_name = 'Events',
             run_br = 'run', lumi_br = 'luminosityBlock', event_br = 'event'):
  with open(output_file, 'w') as f:
    ch_root = ROOT.TChain(tree_name)
    ch_root.AddFile(input_file)

    run_a  = array.array('I', [0])
    lumi_a = array.array('I', [0])
    evt_a  = array.array('L', [0])

    ch_root.SetBranchAddress(run_br,   run_a)
    ch_root.SetBranchAddress(lumi_br,  lumi_a)
    ch_root.SetBranchAddress(event_br, evt_a)

    nof_entries = ch_root.GetEntries()
    rle_i_arr = []
    for i in range(nof_entries):
      ch_root.GetEntry(i)
      rle_i_arr.append(':'.join(map(str, [run_a[0], lumi_a[0], evt_a[0]])))

    f.write("{rle_lines}\n".format(rle_lines='\n'.join(rle_i_arr)))

  logging.debug("Wrote {nof_bytes} kB to {filename}".format(
    nof_bytes = os.path.getsize(output_file) / 1000,
    filename  = output_file,
  ))
  return

def check_dir(dirname, use_force):
  if not os.path.isdir(dirname):
    if not use_force:
      logging.error("Directory '{output_dir}' does not exist".format(
        output_dir = dirname,
      ))
      return False
    else:
      logging.debug("Creating directory '{output_dir}' since it's missing".format(
        output_dir = dirname,
      ))
      try:
        os.makedirs(dirname)
      except IOError as err:
        logging.error("Caught an error while creating directory '{output_dir}': {reason}".format(
          output_dir = dirname,
          reason     = err,
        ))
        return False
  return True

if __name__ == '__main__':
  parser = argparse.ArgumentParser(formatter_class = lambda prog: SmartFormatter(prog, max_help_position = 40))
  group = parser.add_mutually_exclusive_group()
  group.add_argument('-i', '--input', metavar = 'input', required = False, type = str, default = '',
                     help = 'R|Path to ROOT file the RLE numbers of which will be dumped')
  group.add_argument('-s', '--sample', metavar = 'name', required = False, type = str, default = 'all',
                     help = 'R|Sample the RLE numbers of which will be dumped (default: all)')
  parser.add_argument('-E', '--era', metavar = 'era', required = False, type = str, choices = [ '2016', '2017', '2018' ],
                      help = 'R|Era')
  parser.add_argument('-o', '--output', metavar = 'path', required = False, type = str, default = '',
                      help = 'R|Directory (or file if -i/--input is used) where the list of RLE numbers will be saved')
  parser.add_argument('-t', '--tree', metavar = 'name', required = False, type = str, default = 'Events',
                      help = 'R|Event tree')
  parser.add_argument('-r', '--run', metavar = 'name', required = False, type = str, default = 'run',
                      help = 'R|Name of the run branch')
  parser.add_argument('-l', '--lumi', metavar = 'name', required = False, type = str, default = 'luminosityBlock',
                      help = 'R|Name of the lumi branch')
  parser.add_argument('-e', '--event', metavar = 'name', required = False, type = str, default = 'event',
                      help = 'R|Name of the event branch')
  parser.add_argument('-f', '--force', dest = 'force', action = 'store_true', default = False,
                      help = 'R|Force the creation of output directory if missing')
  parser.add_argument('-p', '--post-processed', dest = 'post_processed', action = 'store_true', default = False,
                      help = 'R|Skim post-processed samples')
  parser.add_argument('-v', '--verbose', dest = 'verbose', action = 'store_true', default = False,
                      help = 'R|Enable verbose printout')
  args = parser.parse_args()

  if args.verbose:
    logging.getLogger().setLevel(logging.DEBUG)

  use_force = args.force
  output    = args.output

  if args.input:

    input_file = args.input
    if not os.path.isfile(input_file):
      logging.error("No such file: {input_filename}".format(input_filename = input_file))
      sys.exit(1)

    output_file = output
    parent_dir  = os.path.dirname(os.path.abspath(output_file))
    if not check_dir(parent_dir, use_force):
      sys.exit(1)

    logging.debug("Saving RLE numbers from {input_file} to {output_file}".format(
      input_file  = input_file,
      output_file = output_file,
    ))

    dump_rle(input_file, output_file, args.tree, args.run, args.lumi, args.event)

  else:

    samples = load_samples(args.era, is_postproc = args.post_processed)

    output_dir = output
    if not check_dir(output_dir, use_force):
      sys.exit(1)

    idx = lambda x: int(x[x.rfind('_') + 1: x.rfind('.')])

    sample_keys = { v['process_name_specific'] : k for k, v in samples.iteritems() if k != 'sum_events' }
    if args.sample:
      if args.sample not in sample_keys:
        raise ValueError("Unrecognized key: {sample_key}".format(sample_key = args.sample))
      sample_keys = [sample_keys[args.sample]]
    else:
      sample_keys = sample_keys.values()

    for s_key in sample_keys:
      s_value = samples[s_key]

      sample_name = s_value['process_name_specific']
      sample_path = s_value['local_paths'][0]['path']
      logging.debug("Processing sample '{sample_name}'".format(
        sample_name = sample_name,
      ))

      output_dir_parent = os.path.join(output_dir, sample_name)
      if not os.path.isdir(output_dir_parent):
        os.makedirs(output_dir_parent)

      for sample_subdir_basename in os.listdir(sample_path):
        sample_subdir = os.path.join(sample_path, sample_subdir_basename)

        for rootfile_basename in os.listdir(sample_subdir):
          rootfile = os.path.join(sample_subdir, rootfile_basename)
          if not os.path.isfile(rootfile):
            continue
          logging.debug("Dumping RLE numbers for file '{rootfile_name}'".format(
            rootfile_name = rootfile,
          ))

          rootfile_idx = idx(rootfile_basename)
          outfile_idx = os.path.join(output_dir_parent, "{i}.txt".format(i = rootfile_idx))
          if os.path.isfile(outfile_idx):
            logging.warning("Whoops, file already exists; skipping that")
            continue

          dump_rle(rootfile, outfile_idx, args.tree, args.run, args.lumi, args.event)

  logging.debug("Done!")
