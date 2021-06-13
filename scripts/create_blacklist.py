#!/usr/bin/env python

from tthAnalysis.HiggsToTauTau.common import SmartFormatter, logging, \
                                             load_samples, load_samples_hh_multilepton, load_samples_hh_bbww
from tthAnalysis.HiggsToTauTau.safe_root import ROOT

import math
import os.path
import array
import collections
import multiprocessing
import signal
import sys
import argparse
import re

def get_1st_rle(fn):
  assert(os.path.isfile(fn))
  fptr = ROOT.TFile.Open(fn, 'read')
  tree = fptr.Get('Events')
  run = array.array('I', [0])
  lumi = array.array('I', [0])
  evt = array.array('L', [0])
  tree.SetBranchAddress('run', run)
  tree.SetBranchAddress('luminosityBlock', lumi)
  tree.SetBranchAddress('event', evt)
  tree.SetBranchStatus('*', 0)
  tree.SetBranchStatus('run', 1)
  tree.SetBranchStatus('luminosityBlock', 1)
  tree.SetBranchStatus('event', 1)
  tree.GetEntry(0)
  rle = ':'.join([ str(x[0]) for x in [ run, lumi, evt ] ])
  fptr.Close()
  return rle

def process_file_explicitly(fn):
  assert (os.path.isfile(fn))
  fptr = ROOT.TFile.Open(fn, 'read')
  tree = fptr.Get('Events')
  run = array.array('I', [0])
  lumi = array.array('I', [0])
  evt = array.array('L', [0])
  pv_x = array.array('f', [0.])
  pv_y = array.array('f', [0.])
  pv_z = array.array('f', [0.])
  met_pt = array.array('f', [0.])
  met_phi = array.array('f', [0.])
  tree.SetBranchAddress('run', run)
  tree.SetBranchAddress('luminosityBlock', lumi)
  tree.SetBranchAddress('event', evt)
  tree.SetBranchAddress('PV_x', pv_x)
  tree.SetBranchAddress('PV_y', pv_y)
  tree.SetBranchAddress('PV_z', pv_z)
  tree.SetBranchAddress('PuppiMET_pt', met_pt)
  tree.SetBranchAddress('PuppiMET_phi', met_phi)
  tree.SetBranchStatus('*', 0)
  tree.SetBranchStatus('run', 1)
  tree.SetBranchStatus('luminosityBlock', 1)
  tree.SetBranchStatus('event', 1)
  tree.SetBranchStatus('PV_x', 1)
  tree.SetBranchStatus('PV_y', 1)
  tree.SetBranchStatus('PV_z', 1)
  tree.SetBranchStatus('PuppiMET_pt', 1)
  tree.SetBranchStatus('PuppiMET_phi', 1)
  nof_events = tree.GetEntries()

  rles = []
  pv_x_prev, pv_y_prev, pv_z_prev, met_pt_prev, met_phi_prev = -1e6,  -1e6,  -1e6, -1e6, -1e6
  for event_idx in range(nof_events):
    tree.GetEntry(event_idx)
    if abs(pv_x_prev - pv_x[0]) < 1e-4 and abs(pv_y_prev - pv_y[0]) < 1e-4 and abs(pv_z_prev - pv_z[0]) < 1e-4 and \
        abs(met_pt_prev - met_pt[0]) < 1e-4 and abs(met_phi_prev - met_phi[0]) < 1e-4:
      rle = ':'.join([ str(x[0]) for x in [run, lumi, evt] ])
      rles.append(rle)
    pv_x_prev = pv_x[0]
    pv_y_prev = pv_y[0]
    pv_z_prev = pv_z[0]
    met_pt_prev = met_pt[0]
    met_phi_prev = met_phi[0]
  fptr.Close()
  return rles

def process_files(sample_name, files_to_check, process_explicitly):
  nof_files_to_check = len(files_to_check)
  logging.info(
    "Processing {} file{} from {}".format(nof_files_to_check, 's' if nof_files_to_check != 1 else '', sample_name)
  )
  rles = []
  for file_to_check in files_to_check:
    if process_explicitly:
      logging.info("Processing {}".format(file_to_check))
      rles.extend(process_file_explicitly(file_to_check))
    else:
      rles.append(get_1st_rle(file_to_check))
  return sample_name, rles

def get_blacklist(predecessors, successors, nof_threads, files_to_ignore, condition):
  blacklist = []
  results = []

  def update_blacklist(job_result):
    blacklist.append(job_result)

  original_sigint_handler = signal.signal(signal.SIGINT, signal.SIG_IGN)
  pool = multiprocessing.Pool(nof_threads)
  signal.signal(signal.SIGINT, original_sigint_handler)

  for dbs_key, sample_info in predecessors.items():
    if dbs_key == 'sum_events':
      continue
    if dbs_key not in successors:
      logging.warning("Cannot find {} in the successor dictionary".format(dbs_key))
      continue

    sample_path = sample_info['local_paths'][0]['path']
    nof_files_post = successors[dbs_key]['nof_files']
    sample_name = sample_info['process_name_specific']

    if '2021Feb' in sample_path and sample_info['type'] == 'data' and condition == 'pre':
      logging.info("Need to explicitly process {} since the Ntuples were recreated later".format(dbs_key))
      sample_path_post = successors[dbs_key]['local_paths'][0]['path']
      file_candidates = [
        os.path.join(sample_path_post, '{:04d}'.format(file_idx // 1000), 'tree_{}.root'.format(file_idx)) \
        for file_idx in range(1, nof_files_post + 1)
      ]
      files_to_check = [
        file_candidate for file_candidate in file_candidates if file_candidate not in files_to_ignore
      ]
      try:
        result = pool.apply_async(process_files, args = (sample_name, files_to_check, True), callback = update_blacklist)
        results.append(result)
      except KeyboardInterrupt:
        pool.terminate()
        sys.exit(1)
    else:
      nof_files_pre = sample_info['nof_files']
      blacklist_pre = sample_info['local_paths'][0]['blacklist']
      nof_files_pre_eff = nof_files_pre - len(blacklist_pre)
      assert(nof_files_pre_eff > 0)
      sample_categpry = sample_info['sample_category'] if condition != 'post_sl' else successors[dbs_key]['sample_category']
      if condition == 'pre':
        splitting_expected = 20 if sample_info['type'] == 'data' else 5
        if 'ctcvcp' in dbs_key or dbs_key.startswith(('/THQ', '/THW')):
          splitting_expected = 2
      elif condition == 'post':
        splitting_expected = 20 if sample_info['type'] == 'data' else 10
        if re.match('(TT|EWK)', sample_categpry):
          splitting_expected = 4
      elif condition == 'post_sl':
        splitting_expected = 20 if sample_info['type'] == 'data' else 10
        if re.match('^TT.*', sample_categpry):
          splitting_expected = 2
        elif re.match('(DY|^W$)', sample_categpry):
          splitting_expected = 4
        if re.match('(.*TGJets|ttH)', sample_name):
          splitting_expected = 2
      else:
        assert(False)
      nof_files_post_expected = int(math.ceil(float(nof_files_pre_eff) / splitting_expected))
      if nof_files_post != nof_files_post_expected:
        raise RuntimeError(
          "Incompatible splitting found for sample: %s (%d before, %d after, tried %d; category: %s; name: %s)" % \
          (dbs_key, nof_files_pre_eff, nof_files_post, splitting_expected, sample_categpry, sample_name)
        )
      file_idxs_flat = [ file_idx for file_idx in range(1, nof_files_pre + 1) if file_idx not in blacklist_pre ]
      assert(len(file_idxs_flat) == nof_files_pre_eff)
      file_idx_chunks = [ file_idxs_flat[chunk_idx:chunk_idx + splitting_expected] for chunk_idx in range(nof_files_post) ]
      assert(len(file_idx_chunks) == nof_files_post and all(len(chunk) <= splitting_expected for chunk in file_idx_chunks))

      files_skipped = 0
      files_to_check = []
      for chunk in file_idx_chunks:
        idxs_beyond_1st = chunk[1:]
        file_candidates = [
          os.path.join(sample_path, '{:04d}'.format(file_idx // 1000), 'tree_{}.root'.format(file_idx)) for file_idx in idxs_beyond_1st
        ]
        files_to_check.extend([
          file_candidate for file_candidate in file_candidates if file_candidate not in files_to_ignore
        ])
        files_skipped += len([ file_candidate for file_candidate in file_candidates if file_candidate in files_to_ignore ])

      try:
        result = pool.apply_async(process_files, args = (sample_name, files_to_check, False), callback = update_blacklist)
        results.append(result)
      except KeyboardInterrupt:
        pool.terminate()
        sys.exit(1)

  for result in results:
    result.wait()
  pool.close()
  pool.join()

  return collections.OrderedDict(blacklist)

if __name__ == '__main__':
  parser = argparse.ArgumentParser(
    formatter_class = lambda prog: SmartFormatter(prog, max_help_position = 50)
  )
  parser.add_argument('-e', '--era',
    type = str, dest = 'era', metavar = 'year', required = True, choices = list(map(str, list(range(2016, 2019)))),
    help = 'R|Era',
  )
  parser.add_argument('-n', '--nthreads',
    type = int, dest = 'nthreads', metavar = 'number', required = False, default = 16,
    help = 'R|Number of threads',
  )
  parser.add_argument('-i', '--ignore',
    type = str, dest = 'ignore', metavar = 'path', required = False,
    help = 'R|File listing files that should be ignored',
  )
  parser.add_argument('-o', '--output',
    type = str, dest = 'output', metavar = 'path', required = False, default = '.',
    help = 'R|Output directory',
  )
  args = parser.parse_args()

  files_to_ignore_txt = args.ignore
  era = args.era
  output_dir = os.path.abspath(args.output)
  nof_threads = args.nthreads

  if not os.path.isdir(output_dir):
    raise RuntimeError("No such directory: %s" % output_dir)

  files_to_ignore = []
  if files_to_ignore_txt:
    with open(files_to_ignore_txt, 'r') as f:
      for line in f:
        files_to_ignore.append(line.strip().replace('.corrupted', ''))

  samples_preprocessed        = load_samples(era, is_postproc = False, base = 'all')
  samples_postprocessed       = load_samples(era, is_postproc = True, base = 'all')
  samples_skimmed_multilepton = load_samples_hh_multilepton(era, suffix = "preselected")
  samples_skimmed_bbww        = load_samples_hh_bbww(era, suffix = "preselected")
  samples_skimmed_bbww_sl     = load_samples_hh_bbww(era, suffix = "preselected_sl")

  blacklist = collections.OrderedDict([
    ('postproc',            get_blacklist(samples_preprocessed,  samples_postprocessed,       nof_threads, files_to_ignore, 'pre')),
    ('skimmed_multilepton', get_blacklist(samples_postprocessed, samples_skimmed_multilepton, nof_threads, files_to_ignore, 'post')),
    ('skimmed_bbww',        get_blacklist(samples_postprocessed, samples_skimmed_bbww,        nof_threads, files_to_ignore, 'post')),
    ('skimmed_bbww_sl',     get_blacklist(samples_postprocessed, samples_skimmed_bbww_sl,     nof_threads, files_to_ignore, 'post_sl')),
  ])

  for blacklist_type in blacklist:
    output_fn = os.path.join(output_dir, 'blacklist_{}_{}.txt'.format(blacklist_type, era))
    with open(output_fn, 'w') as f:
       for sample_name in blacklist[blacklist_type]:
         f.write('{} {}\n'.format(sample_name, ';'.join(blacklist[blacklist_type][sample_name])))
    logging.info('Wrote file {}'.format(output_fn))
