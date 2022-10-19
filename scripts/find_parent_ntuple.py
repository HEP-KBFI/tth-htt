#!/usr/bin/env python
# -*- coding: utf-8 -*-

from tthAnalysis.HiggsToTauTau.safe_root import ROOT
from tthAnalysis.HiggsToTauTau.common import SmartFormatter, load_samples

import xml.etree.ElementTree as ET
import argparse
import os.path
import re
import math
import array
import tarfile

RLE_REGEX = re.compile(r'\d+:\d+:\d+')
TREE_REGEX = re.compile(r'tree_(?P<idx>\d+)\.root')
ALLOWED_MODES = {
  'all'                : [
                          { 'base' : 'tth',            'suffix' : 'base'       },
                          { 'base' : 'hh_multilepton', 'suffix' : ''           },
                          { 'base' : 'hh_bbww',        'suffix' : 'base'       },
                         ],
  'sync'               : [{ 'base' : 'tth',            'suffix' : 'sync'       }],
  'hh'                 : [{ 'base' : 'hh_multilepton', 'suffix' : 'hh'         }],
  'hh_bbww'            : [{ 'base' : 'hh_bbww',        'suffix' : 'hh'         }],
  'hh_bbww_sync'       : [{ 'base' : 'hh_bbww',        'suffix' : 'sync'       }],
  'hh_bbww_ttbar'      : [{ 'base' : 'hh_bbww',        'suffix' : 'ttbar'      }],
  'hh_bbww_sync_ttbar' : [{ 'base' : 'hh_bbww',        'suffix' : 'sync_ttbar' }],
}

def has_rles(input_filename, rles):
  if not os.path.isfile(input_filename):
    raise RuntimeError("No such file: %s" % input_filename)
  input_file = ROOT.TFile.Open(input_filename, 'read')
  assert(input_file)
  events_tree = input_file.Get('Events')
  assert (events_tree)
  run_branch = array.array('I', [0])
  ls_branch = array.array('I', [0])
  events_branch = array.array('L', [0])
  events_tree.SetBranchAddress('run', run_branch)
  events_tree.SetBranchAddress('luminosityBlock', ls_branch)
  events_tree.SetBranchAddress('event', events_branch)

  rle_matches = []
  nof_events = events_tree.GetEntries()
  for idx in range(nof_events):
    events_tree.GetEntry(idx)
    rle = ':'.join(map(lambda x: str(x[0]), [ run_branch, ls_branch, events_branch ]))
    if rle in rles:
      rle_matches.append(rle)
    if len(rle_matches) == len(rles):
      break
  input_file.Close()
  return rle_matches

def find_parents(input_file, input_rles):
  if input_file.startswith('/store'):
    return []
  if not os.path.isfile(input_file):
    raise RuntimeError("No such file: %s" % input_file)
  if not all(RLE_REGEX.match(rle) for rle in input_rles):
    raise RuntimeError("Not all input run:lumi:event numbers conform to the expected format")

  input_file_basename = os.path.basename(input_file)
  tree_match = TREE_REGEX.match(input_file_basename)
  if not tree_match:
    raise RuntimeError("Not a valid Ntuple: %s" % input_file)

  tree_idx = int(tree_match.group('idx'))
  assert(tree_idx > 0)

  parent_candidates = []
  if input_file.startswith('/local'):
    input_file_split = input_file.split(os.path.sep)
    assert(len(input_file_split) == 11)
    process_name = input_file_split[-3]
    version = input_file_split[-5]
    era = input_file_split[-6]

    for lepton_wp in [ 'hh_multilepton', 'default', 'ttZctrl' ]:
      if version.endswith(lepton_wp):
        version = version[:-len(lepton_wp) - 1]
        break

    modes = [ mode for mode in ALLOWED_MODES.keys() if version.endswith(mode) ]
    if len(modes) != 1:
      raise RuntimeError("Unable to deduce mode from input path: %s" % input_file)
    mode = modes[0]
    version_no_mode = version[:-len(mode) - 1]
    nom_signifier = version_no_mode.split('_')[-1]
    version_no_mode_nom = version_no_mode[:-len(nom_signifier) - 1]
    presel_signifier = version_no_mode_nom.split('_')[-1]

    dbs_key = ''
    for mode_val in ALLOWED_MODES[mode]:
      sample_base = mode_val['base']
      sample_suffix = mode_val['suffix']
      if presel_signifier == 'wPresel':
        if mode == 'all' and sample_suffix:
          sample_suffix = 'preselected_{}'.format(sample_suffix)
        elif mode != 'all':
          sample_suffix = '{}_preselected'.format(sample_suffix)
      try:
        samples = load_samples(era, True, base = sample_base, suffix = sample_suffix)
      except ImportError:
        continue
      for sample_key, sample_info in samples.items():
        if sample_key == 'sum_events':
          continue
        if sample_info['process_name_specific'] == process_name:
          dbs_key = sample_key
          break
      if dbs_key:
        break

    if not dbs_key:
      raise RuntimeError("Unable to find an entry from sample dictionary that corresponds to file: %s" % input_file)
    sample_nfiles = samples[dbs_key]['nof_files']
    if sample_nfiles < tree_idx:
      raise RuntimeError(
        "Tree index found from input path %s larger than expected number of Ntuples: %d" % (input_file, sample_nfiles)
      )
    if presel_signifier == 'wPresel':
      parent_samples = load_samples(era, True, base = sample_base,
        suffix = sample_suffix.replace('preselected_', '').replace('_preselected', '')
      )
      parent_sample = parent_samples[dbs_key]

    elif presel_signifier == 'woPresel':
      parent_samples = load_samples(era, False, base = sample_base)
      parent_sample = parent_samples[dbs_key]
    else:
      raise RuntimeError("Invalid preselection signifier found from input file %s: %s" % (input_file, presel_signifier))
    parent_sample_nfiles = parent_sample['nof_files']
    parent_sample_path = parent_sample['local_paths'][0]['path']
    parent_sample_blacklist = parent_sample['local_paths'][0]['blacklist']
    assert(parent_sample_nfiles >= sample_nfiles)
    whitelisted_indices = [ idx for idx in range(1, parent_sample_nfiles + 1) if idx not in parent_sample_blacklist ]
    len_whitelisted_indices = len(whitelisted_indices)
    if len_whitelisted_indices == sample_nfiles:
      # it's 1-1 correspondence
      parent_candidate = os.path.join(parent_sample_path, "%04d" % (tree_idx // 1000), 'tree_%d.root' % tree_idx)
      rle_matches = has_rles(parent_candidate, input_rles)
      if len(rle_matches) == len(input_rles):
        parent_candidates.append((parent_candidate, rle_matches))
      else:
        raise RuntimeError("Unable to find parent for: %s" % input_file)
    elif len_whitelisted_indices > sample_nfiles:
      # partition
      chunk_len = int(math.ceil(float(len_whitelisted_indices) / sample_nfiles))
      chunks = [ whitelisted_indices[idx:idx + chunk_len] for idx in range(0, len_whitelisted_indices, chunk_len) ]
      assert(len(chunks) == sample_nfiles)
      parent_chunk = chunks[tree_idx - 1]
      for parent_idx in parent_chunk:
        parent_candidate = os.path.join(parent_sample_path, "%04d" % (parent_idx // 1000), 'tree_%d.root' % parent_idx)
        rle_matches = has_rles(parent_candidate, input_rles)
        if rle_matches:
          parent_candidates.append((parent_candidate, rle_matches))
    else:
      raise RuntimeError("Fewer parent Ntuples than sibling Ntuples for the Ntuple: %s" % input_file)
  elif input_file.startswith('/store/user'):
    input_file_dirname = os.path.dirname(input_file)
    log_file = os.path.join(input_file_dirname, 'log', 'cmsRun_{}.log.tar.gz'.format(tree_idx))
    if os.path.isfile(log_file):
      tar = tarfile.open(log_file, 'r:gz')
      tar_contents = tar.getnames()
      xml_filename = 'FrameworkJobReport-{}.xml'.format(tree_idx)
      if xml_filename in tar_contents:
        xml_tarmember = tar.getmember(xml_filename)
        xml_file = tar.extractfile(xml_tarmember)
        xml_contents = xml_file.read()
        xml_tree = ET.ElementTree(ET.fromstring(xml_contents))
        last_lfn = ''
        matched_ls = []
        expected_ls = { int(rle.split(':')[1]) : rle for rle in input_rles }
        for elem in xml_tree.iter():
          if elem.tag == 'Inputs' or len(expected_ls) == len(matched_ls):
            break
          if elem.tag == 'LFN':
            if last_lfn and matched_ls:
              parent_candidates.append((last_lfn, matched_ls))
            last_lfn = elem.text
            matched_ls = []
          elif elem.tag == 'LumiSection':
            ls = int(elem.attrib['ID'])
            if ls in expected_ls:
              matched_ls.append(expected_ls[ls])
        if last_lfn and matched_ls:
          parent_candidates.append((last_lfn, matched_ls))
      tar.close()
  else:
    raise RuntimeError("Invalid path: %s" % input_file)
  return parent_candidates

if __name__ == '__main__':
  parser = argparse.ArgumentParser(
    formatter_class = lambda prog: SmartFormatter(prog, max_help_position = 35)
  )
  parser.add_argument('-i', '--input',
    type = str, dest = 'input', metavar = 'file', required = True, nargs = '+',
    help = 'R|Input file containing Ntuple locations produced by CRAB',
  )
  parser.add_argument('-r', '--rle',
    type = str, dest = 'rles', metavar = 'nr', required = True, nargs = '+',
    help = 'R|Run:lumi:event numbers from the input file',
  )
  args = parser.parse_args()

  input_files = args.input
  input_rles = args.rles

  input_files_it = [ (input_file, has_rles(input_file, input_rles), 0) for input_file in input_files ]
  while input_files_it:
    input_file, input_rle, level = input_files_it.pop(0)
    indent = ''
    if level == 1:
      indent = '  '
    elif level > 1:
      indent = ' ' * (4 * (level - 1)) + '  '
    if indent:
      indent += '└──'
    print('{}{} ({})'.format(indent, input_file, ', '.join(input_rle)))
    parents = find_parents(input_file, input_rle)
    input_files_it = [ (parent[0], parent[1], level + 1) for parent in parents ] + input_files_it
