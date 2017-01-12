#!/usr/bin/env python

import logging, argparse, os, sys, ROOT, array
from tthAnalysis.HiggsToTauTau.tthAnalyzeSamples_2016 import samples_2016 as samples

if __name__ == '__main__':
  logging.basicConfig(
    stream = sys.stdout,
    level  = logging.INFO,
    format = '%(asctime)s - %(levelname)s: %(message)s'
  )

  class SmartFormatter(argparse.HelpFormatter):
    def _split_lines(self, text, width):
      if text.startswith('R|'):
        return text[2:].splitlines()
      return argparse.HelpFormatter._split_lines(self, text, width)

  parser = argparse.ArgumentParser(formatter_class = lambda prog: SmartFormatter(prog, max_help_position = 35))
  parser.add_argument('-o', '--output', metavar = 'directory', required = False, type = str, default = '',
                      help = 'R|Directory where the list of RLE numbers will be saved')
  parser.add_argument('-f', '--force', dest = 'force', action = 'store_true', default = False,
                      help = 'R|Force the creation of output directory if missing')
  parser.add_argument('-v', '--verbose', dest = 'verbose', action = 'store_true', default = False,
                      help = 'R|Enable verbose printout')
  args = parser.parse_args()

  if args.verbose:
    logging.getLogger().setLevel(logging.DEBUG)

  use_force = args.force
  output_dir = args.output

  if not os.path.isdir(output_dir):
    if not use_force:
      logging.error("Directory '{output_dir}' does not exist".format(
        output_dir = output_dir,
      ))
    else:
      logging.debug("Creating directory '{output_dir}' since it's missing".format(
        output_dir = output_dir,
      ))

  idx = lambda x: int(x[x.rfind('_') + 1: x.rfind('.')])

  for s_key, s_value in samples.iteritems():
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
        logging.debug("Dumping RLE numbers for file '{rootfile_name}'".format(
          rootfile_name = rootfile,
        ))

        rootfile_idx = idx(rootfile_basename)
        outfile_idx = os.path.join(output_dir_parent, "{i}.txt".format(i = rootfile_idx))
        if os.path.isfile(outfile_idx):
          logging.warning("Whoops, file already exists; skipping that")
          continue

        with open(outfile_idx, 'w') as f:

          ch_root = ROOT.TChain("tree")
          ch_root.AddFile(rootfile)

          run_a  = array.array('I', [0])
          lumi_a = array.array('I', [0])
          evt_a  = array.array('L', [0])

          ch_root.SetBranchAddress("run",  run_a)
          ch_root.SetBranchAddress("lumi", lumi_a)
          ch_root.SetBranchAddress("evt",  evt_a)

          nof_entries = ch_root.GetEntries()
          rle_i_arr = []
          for i in range(nof_entries):
            ch_root.GetEntry(i)
            rle_i_arr.append(':'.join(map(str, [run_a[0], lumi_a[0], evt_a[0]])))

          f.write("{rle_lines}\n".format(rle_lines = '\n'.join(rle_i_arr)))

        logging.debug("Wrote {nof_bytes} kB to {filename}".format(
          nof_bytes = os.path.getsize(outfile_idx) / 1000,
          filename = outfile_idx,
        ))

  logging.debug("Done!")
