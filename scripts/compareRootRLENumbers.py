#!/usr/bin/env python

# Suitable for comparing the run, lumi and event numbers between synchronization Ntuples
# The only requirement is that the TTree names and RLE branch names are common in both Ntuples
#
# Example usage:
#
# compareRootRLENumbers.py \
# -i sync_LLR_v1.root -I sync_Tallinn_v5.root -o ~/sandbox/rle_venn_v1 -f -R LLR -T Tallinn

import argparse, ROOT, array, os, logging, sys, re

class SmartFormatter(argparse.HelpFormatter):
  def _split_lines(self, text, width):
    if text.startswith('R|'):
      return text[2:].splitlines()
    return argparse.HelpFormatter._split_lines(self, text, width)

parser = argparse.ArgumentParser(
  formatter_class = lambda prog: SmartFormatter(prog, max_help_position = 45)
)

parser.add_argument('-i', '--input-ref',
  type = str, dest = 'input_ref', metavar = 'file', default = None, required = True,
  help = 'R|Reference input file',
)
parser.add_argument('-I', '--input-test',
  type = str, dest = 'input_test', metavar = 'file', default = None, required = True,
  help = 'R|Test input file',
)
parser.add_argument('-t', '--trees',
  type = str, nargs = '+', dest = 'trees', metavar = 'tree', default = [], required = False,
  help = 'R|Trees for which the RLE numbers will be compared',
)
parser.add_argument('-r', '--run-name',
  type = str, dest = 'run_name', metavar = 'name', default = 'run', required = False,
  help = 'R|Branch name for run numbers'
)
parser.add_argument('-l', '--lumi-name',
  type = str, dest = 'lumi_name', metavar = 'name', default = 'ls', required = False,
  help = 'R|Branch name for luminosityBlock numbers'
)
parser.add_argument('-e', '--event-name',
  type = str, dest = 'event_name', metavar = 'name', default = 'nEvent', required = False,
  help = 'R|Branch name for event numbers'
)
parser.add_argument('-o', '--output-dir',
  type = str, dest = 'output_dir', metavar = 'path', default = None, required = True,
  help = 'R|Output directory where the RLE text files will be written to'
)
parser.add_argument('-R', '--ref-name',
  type = str, dest = 'ref_name', metavar = 'name', default = 'ref', required = False,
  help = 'R|Some name that refers to the reference input file (e.g. LLR)',
)
parser.add_argument('-T', '--test-name',
  type = str, dest = 'test_name', metavar = 'name', default = 'test', required = False,
  help = 'R|Some name that refers to the test input file (e.g. Tallinn)',
)
parser.add_argument('-v', '--verbose',
  dest = 'verbose', action = 'store_true', default = False,
  help = 'R|Enable verbose output',
)
parser.add_argument('-f', '--force',
  dest = 'force', action = 'store_true', default = False,
  help = "R|Force creating the output directory if it doesn't exist",
)
args          = parser.parse_args()
input_ref_fn  = args.input_ref
input_test_fn = args.input_test
trees         = args.trees
run_name      = args.run_name
lumi_name     = args.lumi_name
event_name    = args.event_name
output_dir    = args.output_dir
ref_name      = args.ref_name
test_name     = args.test_name
verbose       = args.verbose
force         = args.force

name_regex = re.compile(r'^[a-zA-Z0-9_]+$')
ref_name_match  = name_regex.match(ref_name)
if not ref_name_match:
  raise ValueError('The reference name %s contains invalid characters' % ref_name)
test_name_match = name_regex.match(test_name)
if not test_name_match:
  raise ValueError('The test name %s contains invalid characters' % test_name)

logging.basicConfig(
  stream = sys.stdout,
  level  = logging.DEBUG if verbose else logging.INFO,
  format = '%(asctime)s - %(levelname)s: %(message)s',
)

# Check if the input files actually exist
if not os.path.isfile(input_ref_fn):
  raise ValueError('Input file %s does not exist' % input_ref_fn)
if not os.path.isfile(input_test_fn):
  raise ValueError('Input file %s does not exist' % input_test_fn)
if not os.path.isdir(output_dir):
  if not force:
    raise ValueError('Output directory %s does not exist (use -f/--force to create it)' % output_dir)
  else:
    try:
      os.makedirs(output_dir)
    except IOError as err:
      raise ValueError('Unable to create directory %s because: %s' % (output_dir, err))

# Open the ROOT files
input_ref_file  = ROOT.TFile.Open(input_ref_fn)
if not input_ref_file:
  raise ValueError('Unable to open %s ROOT file: %s' % (ref_name, input_ref_fn))

input_test_file = ROOT.TFile.Open(input_test_fn)
if not input_test_file:
  raise ValueError('Unable to open %s ROOT file: %s' % (test_name, input_test_fn))

# Check if the user requested to find the RLE Venn diagram for all the branches or for specific ones
# In case all branches were requested, the user should've left the trees argument empty
if not trees:
  ref_ts  = { key.GetName() for key in input_ref_file.GetListOfKeys()  if key.GetClassName() == 'TTree' }
  test_ts = { key.GetName() for key in input_test_file.GetListOfKeys() if key.GetClassName() == 'TTree' }
  trees = list(sorted(list(ref_ts & test_ts)))
  if not trees:
    raise ValueError('No common TTrees found in the input files')
  only_in_ref_ts  = list(sorted(list(ref_ts  - test_ts)))
  only_in_test_ts = list(sorted(list(test_ts - ref_ts)))
  if only_in_ref_ts:
    logging.debug(
      'Found the following TTree(s) present only in %s file %s: %s' % \
      (ref_name, input_ref_fn, ', '.join(only_in_ref_ts))
    )
  if only_in_test_ts:
    logging.debug(
      'Found the following TTree(s) present only in %s file %s: %s' % \
      (test_name, input_test_fn, ', '.join(only_in_test_ts))
    )
  logging.debug('Found the following common TTree(s): %s' % ', '.join(trees))

# Make sure that the run, lumi and event branch names are present in all the TTrees
rle_brs = { run_name, lumi_name, event_name }
for tree in trees:
  ref_t  = input_ref_file.Get(tree)
  test_t = input_test_file.Get(tree)
  ref_brs  = { br.GetName() for br in ref_t.GetListOfBranches()  }
  test_brs = { br.GetName() for br in test_t.GetListOfBranches() }
  if (rle_brs & ref_brs) != rle_brs:
    raise ValueError(
      'Could not find the run, lumi and event branches (%s, %s and %s) in tree %s of the %s file %s' % \
      (run_name, lumi_name, event_name, tree, ref_name, input_ref_fn)
    )
  if (rle_brs & test_brs) != rle_brs:
    raise ValueError(
      'Could not find the run, lumi and event branches (%s, %s and %s) in tree %s of the %s file %s' % \
      (run_name, lumi_name, event_name, tree, test_name, input_test_fn)
    )

typeMap = {
  'Int_t'     : 'i',
  'UInt_t'    : 'I',
  'Float_t'   : 'f',
  'Double_t'  : 'd',
  'Char_t'    : 'b',
  'UChar_t'   : 'B',
  'Long64_t'  : 'l',
  'ULong64_t' : 'L',
}

def get_branch_array(tree_object, branch_name, maxlen = 1):
  branch_list = [ br for br in tree_object.GetListOfBranches() ]
  branch_list_filtered = list(filter(lambda br: br.GetName() == branch_name, branch_list))
  assert(len(branch_list_filtered) == 1)

  leaf_object = branch_list_filtered[0].GetLeaf(branch_name)
  leaf_type = leaf_object.GetTypeName()
  if leaf_type not in typeMap:
    raise ValueError('Unrecognized type found in branch %s: %s' % (branch_name, leaf_type))

  array_type = typeMap[leaf_type]
  array_unit = [0.] if array_type in ['f', 'd'] else [0]
  branch_array = array.array(array_type, array_unit * maxlen)
  tree_object.SetBranchAddress(branch_name, branch_array)

  return branch_array

def write_rles(fn, rles):
  logging.debug('Writing file %s' % fn)
  with open(fn, 'w') as f:
    f.write('\n'.join(rles))

# Now we can start looping over the entries in each TTree simulatanously and construct the so-called
# Venn diagram
for tree in trees:
  ref_t  = input_ref_file.Get(tree)
  test_t = input_test_file.Get(tree)
  logging.debug(
    'Opened TTree %s in files %s (%s) and %s (%s)' % \
    (tree, input_ref_fn, ref_name, input_test_fn, test_name)
  )

  ref_nof_entries  = ref_t.GetEntries()
  test_nof_entries = test_t.GetEntries()
  logging.debug(
    'Found %d entries in the ref file and %d entries in the test file' % \
    (ref_nof_entries, test_nof_entries)
  )

  # Construct the array objects that will be bound to the TTree
  ref_run   = get_branch_array(ref_t, run_name)
  ref_lumi  = get_branch_array(ref_t, lumi_name)
  ref_event = get_branch_array(ref_t, event_name)

  test_run   = get_branch_array(test_t, run_name)
  test_lumi  = get_branch_array(test_t, lumi_name)
  test_event = get_branch_array(test_t, event_name)

  ref_rles  = set()
  for i in range(ref_nof_entries):
    ref_t.GetEntry(i)
    ref_rles.add(':'.join(map(lambda br: str(br[0]), [ref_run, ref_lumi, ref_event])))

  test_rles = set()
  for i in range(test_nof_entries):
    test_t.GetEntry(i)
    test_rles.add(':'.join(map(lambda br: str(br[0]), [test_run, test_lumi, test_event])))

  rles_common    = list(sorted(list(ref_rles & test_rles)))
  rles_ref_only  = list(sorted(list(ref_rles - test_rles)))
  rles_test_only = list(sorted(list(test_rles - ref_rles)))

  logging.debug('Found %d common events in TTree %s'     % (len(rles_common), tree))
  logging.debug('Found %d events present in %s TTree %s' % (len(rles_ref_only), ref_name, tree))
  logging.debug('Found %d events present in %s TTree %s' % (len(rles_test_only), test_name, tree))

  # Write the files to the output
  common_fn    = os.path.join(output_dir, '%s_common.txt' % tree)
  ref_only_fn  = os.path.join(output_dir, '%s_%s.txt'     % (tree, ref_name))
  test_only_fn = os.path.join(output_dir, '%s_%s.txt'     % (tree, test_name))

  write_rles(common_fn,    rles_common)
  write_rles(ref_only_fn,  rles_ref_only)
  write_rles(test_only_fn, rles_test_only)

logging.info('All done: check the results in %s' % output_dir)
