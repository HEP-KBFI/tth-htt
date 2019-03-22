#!/usr/bin/env python

from tthAnalysis.HiggsToTauTau.jobTools import run_cmd, create_if_not_exists
from tthAnalysis.HiggsToTauTau.common import ROOT

from DataFormats.FWLite import Events, Handle

import argparse
import logging
import sys
import os
import imp
import array

def load_dict(path, name):
  if not os.path.isfile(path):
    logging.error("No such dictionary file: {dict_path}".format(dict_path = path))
    sys.exit(1)
  imp_dict = imp.load_source('', path)
  if not hasattr(imp_dict, name):
    logging.error("No such dictionary in the file '{dict_path}': {dict_name}".format(
      dict_path = path, dict_name = name,
    ))
    sys.exit(1)
  samples = getattr(imp_dict, name)
  return samples

class SmartFormatter(argparse.ArgumentDefaultsHelpFormatter):
  def _split_lines(self, text, width):
    if text.startswith('R|'):
      return text[2:].splitlines()
    return argparse.ArgumentDefaultsHelpFormatter._split_lines(self, text, width)

def plot(input_files, output_files, title, legend):
  handle_lhe = Handle('LHEEventProduct')
  label_lhe = ('externalLHEProducer')

  bins = array.array('f', [1. * i for i in range(0, 201)])
  h = ROOT.TH1F(legend, legend, len(bins) - 1, bins)

  for input_file in input_files:
    events = Events(input_file)

    for event in events:
      event.getByLabel(label_lhe, handle_lhe)
      lhe = handle_lhe.product()
      invmass = []

      for status, pdg, mom in zip(lhe.hepeup().ISTUP, lhe.hepeup().IDUP, lhe.hepeup().PUP):
        if status == 1 and abs(pdg) in [ 11, 13, 15 ]:
          l = ROOT.TLorentzVector(mom.x[0], mom.x[1], mom.x[2], mom.x[3])
          invmass.append(l)

      if len(invmass) == 2:
        h.Fill((invmass[0] + invmass[1]).M())
      else:
        raise RuntimeError(
          'Did not find exactly 2 but %d LHE leptons in %s' % (len(invmass), input_file)
        )

  c = ROOT.TCanvas('c', 'c')
  c.SetLogy()
  c.SetGrid()
  h.SetTitle(title)
  h.GetXaxis().SetTitle('m_ll [GeV]')
  h.GetYaxis().SetTitle('# events')
  h.Draw()
  for output_file in output_files:
    c.SaveAs(output_file)
  del h
  del c

if __name__ == '__main__':
  parser = argparse.ArgumentParser(
    formatter_class = lambda prog: SmartFormatter(prog, max_help_position = 55)
  )

  parser.add_argument('-m', '--min-event',
    type = int, dest = 'min_event', metavar = 'int', required = False, default = 50000,
    help = 'R|Minimum number of events in the ROOT file (non-positive == any number)',
  )
  parser.add_argument('-M', '--max-event',
    type = int, dest = 'max_event', metavar = 'int', required = False, default = 60000,
    help = 'R|Maximum number of events in the ROOT file (non-positive == any number)',
  )
  parser.add_argument('-n', '--nof-files',
    type = int, dest = 'nof_files', metavar = 'int', required = False, default = 1,
    help = 'R|Number of files per sample (non-positive == all files)',
  )
  parser.add_argument('-o', '--output-dir',
    type = str, dest = 'output_dir', metavar = 'path', required = False, default = '.',
    help = 'R|Output dir where the plots are saved',
  )
  parser.add_argument('-e', '--extension',
    type = str, nargs = '+', dest = 'extensions', metavar = 'extension', required = False,
    choices = [ 'png', 'pdf' ], default = [ 'png', 'pdf' ],
    help = 'R|File extensions for the plots',
  )
  parser.add_argument('-d', '--dictionary',
    type = str, dest = 'dictionary', metavar = 'path', required = False,
    default = os.path.join(
      os.environ['CMSSW_BASE'], 'src/tthAnalysis/HiggsToTauTau/python/samples/tthAnalyzeSamples_2017.py'
    ),
    help = 'R|Path to the dictionary',
  )
  parser.add_argument('-s', '--sample-name',
    type = str, dest = 'sample_name', metavar = 'var', required = False, default = 'samples_2017',
    help = 'Sample name',
  )
  parser.add_argument('-f', '--force',
    dest = 'force', action = 'store_true', default = False, required = False,
    help = 'R|Create the output dir if it does not exist',
  )
  parser.add_argument('-v', '--verbose',
    dest = 'verbose', action = 'store_true', default = False, required = False,
    help = 'R|Verbose output',
  )
  args = parser.parse_args()

  logging.basicConfig(
    stream = sys.stdout,
    level  = logging.DEBUG if args.verbose else logging.INFO,
    format = '%(asctime)s - %(levelname)s: %(message)s',
  )

  samples = load_dict(args.dictionary, args.sample_name)

  has_dasgoclient = run_cmd(
    'which dasgoclient 2>/dev/null | wc -l', do_not_log = True, return_stderr = False
  )
  if has_dasgoclient.rstrip('\n') != "1":
    raise ValueError("dasgoclient not available! Set up your 94x environment")
  has_voms_proxy = run_cmd(
    'which voms-proxy-info 2>/dev/null | wc -l', do_not_log = True, return_stderr = False
  )
  if has_voms_proxy.rstrip('\n') != "1":
    raise ValueError("voms-proxy-* not available! Set up your 94x environment")

  min_voms_proxy_timeleft_hours = 3
  voms_proxy_timeleft = int(run_cmd(
    'voms-proxy-info --timeleft', do_not_log = True, return_stderr = False
  ).rstrip('\n'))
  if voms_proxy_timeleft < 3600 * min_voms_proxy_timeleft_hours:
    raise ValueError(
      "proxy not open at least %i minutes to run this script; " \
      "update your proxy with: voms-proxy-init -voms cms -valid %i:00" % \
      (min_voms_proxy_timeleft_hours, min_voms_proxy_timeleft_hours + 1)
    )

  if not os.path.isdir(args.output_dir):
    if not args.force:
      raise ValueError('Use -f/--force to create output dir %s' % args.output_dir)
    else:
      os.makedirs(args.output_dir)

  # Let's get the list of DY samples
  dy_samples = { dbs_name : [] for dbs_name in samples if dbs_name.startswith('/DY') }
  for dy_sample in dy_samples:
    logging.debug('Found sample: {}'.format(dy_sample))

  # Get files
  for dy_sample in dy_samples:
    query = "dasgoclient -query='file dataset={} | grep file.name | grep file.nevents'".format(dy_sample)
    stdout, stderr = run_cmd(query, do_not_log = True, return_stderr = True)
    if not stdout or stderr:
      raise RuntimeError("Unsuccessful DBS query '%s': %s" % (query, stderr))
    files = map(lambda y: (y[0], int(y[1])), map(lambda x: x.split(), stdout.rstrip('\n').split('\n')))
    selected_files = []
    for file_cand in files:
      if args.min_event > 0 and file_cand[1] < args.min_event:
        continue
      if args.max_event > 0 and file_cand[1] > args.max_event:
        continue
      fp = 'root://cms-xrd-global.cern.ch/%s' % file_cand[0]
      try:
        f = ROOT.TFile.Open(fp, 'read')
        f.Close()
      except Exception:
        break
      logging.debug('Selected file {} ({} events)'.format(file_cand[0], file_cand[1]))
      selected_files.append(fp)
      if args.nof_files > 0 and len(selected_files) >= args.nof_files:
        break
    dy_samples[dy_sample] = selected_files

  for dy_sample, files in dy_samples.items():
    if not files:
      logging.warning('Could not find a file for {}'.format(dy_sample))
      continue
    logging.info('Plotting {}'.format(dy_sample))
    output_file_basename = dy_sample.split('/')[1].replace('-', '_')
    if 'ext' in dy_sample:
       output_file_basename += '_ext'
    output_file_fullpath_wo_ext = os.path.join(args.output_dir, output_file_basename)
    output_files = map(lambda ext: '{}.{}'.format(output_file_fullpath_wo_ext, ext), args.extensions)
    title = ' + '.join(map(lambda f: os.path.basename(f).replace('.root', ''), files))
    plot(files, output_files, title, output_file_basename)
