#!/usr/bin/env python

from tthAnalysis.HiggsToTauTau.safe_root import ROOT
from tthAnalysis.HiggsToTauTau.common import SmartFormatter

import os
import shutil
import collections
import argparse

if __name__ == '__main__':
  
  parser = argparse.ArgumentParser(
      formatter_class = lambda prog: SmartFormatter(prog, max_help_position = 35)
  )
  parser.add_argument('-d', '--datacard',
    type = str, dest = 'datacard', metavar = 'file', required = True,
    help = 'R|Input datacard ROOT file (output of prepareDatacards or addSystFakeRates)',
  )
  parser.add_argument('-i', '--input-hadd2',
    type = str, dest = 'input_hadd2', metavar = 'file', required = True,
    help = 'R|Input hadd stage2 file',
  )
  parser.add_argument('-o', '--output',
    type = str, dest = 'output', metavar = 'file', required = True,
    help = 'R|Output file name',
  )
  parser.add_argument('-b', '--basedir',
    type = str, dest = 'basedir', metavar = 'name', required = True,
    help = 'R|Top directory name in hadd stage2 file',
  )
  parser.add_argument('-f', '--fitvar',
    type = str, dest = 'fitvar', metavar = 'name', required = True,
    help = 'R|Fit variable (aka histogram) name',
  )
  parser.add_argument('-F', '--force',
    dest = 'force', action = 'store_true', default = False,
    help = 'R|Create output directory if it does not exist'
  )
  args = parser.parse_args()

  input_dcard_fn = args.datacard
  input_hadd2_fn = args.input_hadd2

  output_fn = os.path.abspath(args.output)
  output_dir = os.path.dirname(output_fn)
  use_force = args.force

  parent_dirname = args.basedir
  fitvar = args.fitvar

  if not os.path.isfile(input_dcard_fn):
    raise ValueError("No such file: %s" % input_dcard_fn)

  if not os.path.isfile(input_hadd2_fn):
    raise ValueError("No such file: %s" % input_hadd2_fn)

  if output_fn.startswith('/hdfs'):
    raise ValueError("Cannot accept path as it is not possible to open files in append mode there: %s" % output_fn)

  if not os.path.isdir(output_dir):
    if not use_force:
      raise ValueError("Cannot write file %s as its directory does not exist" % output_dir)
    else:
      os.makedirs(output_dir)

  if os.path.isfile(output_fn):
    os.remove(output_fn)
  shutil.copyfile(input_dcard_fn, output_fn)
  assert(os.path.isfile(output_fn))

  output = ROOT.TFile.Open(output_fn, 'update')
  input_hadd2 = ROOT.TFile.Open(input_hadd2_fn, 'read')

  evt_dirname = '{}/sel/evt'.format(parent_dirname)
  evt_dir = input_hadd2.Get(evt_dirname)
  if not evt_dir:
    raise RuntimeError("Unable to find directory %s from file %s" % (evt_dirname, input_hadd2_fn))

  htxs_dirnames = [ key.GetName() for key in evt_dir.GetListOfKeys() if key.GetName().startswith('htxs_') ]
  if not htxs_dirnames:
    raise RuntimeError(
      "Unable to find any subdirectories of %s that start with name 'htxs' in file %s" % (evt_dirname, input_hadd2_fn)
    )

  fitvar_len_plus_1 = len(fitvar) + 1
  histograms = collections.OrderedDict()
  for htxs_dirname in htxs_dirnames:
    htxs_dir = evt_dir.Get(htxs_dirname)

    htxs_dirname_noprefix = htxs_dirname.replace('htxs_', '')
    htxs_dirname_noprefix_split = htxs_dirname_noprefix.split('_')
    assert (htxs_dirname_noprefix_split[1] == 'ttH')

    ptbin_name = htxs_dirname_noprefix_split[0]
    ptbin_name = ptbin_name.replace('pt', 'PTH_').replace('to', '_').replace('fwd', 'PTH_fwd')
    if 'Gt' in ptbin_name:
      ptbin_name = ptbin_name.replace('Gt', '')
      ptbin_name += '_infty'

    histogram_name_base = 'ttH_{}_{}'.format(ptbin_name, '_'.join(htxs_dirname_noprefix_split[2:]))

    histogram_names = [ key.GetName() for key in htxs_dir.GetListOfKeys() if key.GetName().endswith(fitvar) ]
    if not histogram_names:
      raise RuntimeError(
        "Unable to find any histograms ending with '%s' in directory %s/%s of file %s" % \
        (fitvar, evt_dirname, htxs_dirname, input_hadd2_fn)
      )

    for histogram_name in histogram_names:
      histogram_name_new = histogram_name_base
      if histogram_name != fitvar:
        sysname = histogram_name[:-fitvar_len_plus_1]
        if not sysname.endswith(('Down', 'Up')):
          raise RuntimeError("Invalid systematics in histogram name %s" % histogram_name)
        histogram_name_new += '_{}'.format(sysname)
      assert(histogram_name_new not in histograms)
      histograms[histogram_name_new] = htxs_dir.Get(histogram_name)

  output.cd()

  for histogram_name in histograms:
    histograms[histogram_name].SetName(histogram_name)
    histograms[histogram_name].SetTitle(histogram_name)
    histograms[histogram_name].Write()

  output.Close()
  input_hadd2.Close()
