#!/usr/bin/env python

# Suitable for comparing the run, lumi and event numbers between synchronization Ntuples
# The only requirement is that the TTree names and RLE branch names are common in both Ntuples
#
# Example usage:
#
# compareRootRLENumbers.py \
# -i sync_LLR_v1.root sync_Tallinn_v5.root -o ~/sandbox/rle_venn_v1 -f -n LLR Tallinn

import argparse, ROOT, array, os, logging, sys, re, itertools

def get_venn(sets, select_idxs, reject_idxs):
  assert(select_idxs)
  select = sets[select_idxs[0]]
  for i in range(1, len(select_idxs)):
    select = select & sets[select_idxs[i]]
  if not reject_idxs:
    return select
  reject = sets[reject_idxs[0]]
  for i in range(1, len(reject_idxs)):
    reject = reject | sets[reject_idxs[i]]
  return select - reject

def get_idx_combinations(x):
  # Generates two groups of combinations
  return [
    [ list(y), list(set(x) - set(y)) ] \
    for i in range(1, len(x) + 1)      \
    for y in itertools.combinations(x, i)
  ]

class SmartFormatter(argparse.HelpFormatter):
  def _split_lines(self, text, width):
    if text.startswith('R|'):
      return text[2:].splitlines()
    return argparse.HelpFormatter._split_lines(self, text, width)

parser = argparse.ArgumentParser(
  formatter_class = lambda prog: SmartFormatter(prog, max_help_position = 50)
)

parser.add_argument('-i', '--input',
  type = str, nargs = '+', dest = 'input_fns', metavar = 'file', default = None, required = True,
  help = 'R|Input files',
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
parser.add_argument('-n', '--names',
  type = str, nargs = '+', dest = 'names', metavar = 'name', default = None, required = True,
  help = 'R|Labels that refer to the input files (e.g. LLR, Tallinn, Cornell)',
)
parser.add_argument('-v', '--verbose',
  dest = 'verbose', action = 'store_true', default = False,
  help = 'R|Enable verbose output',
)
parser.add_argument('-f', '--force',
  dest = 'force', action = 'store_true', default = False,
  help = "R|Force creating the output directory if it doesn't exist",
)
args       = parser.parse_args()
input_fns  = args.input_fns
trees      = args.trees
run_name   = args.run_name
lumi_name  = args.lumi_name
event_name = args.event_name
output_dir = args.output_dir
names      = args.names
verbose    = args.verbose
force      = args.force

nof_groups = len(input_fns)
assert(nof_groups == len(names) and nof_groups > 1)

name_regex = re.compile(r'^[a-zA-Z0-9_]+$')
for name in names:
  name_match  = name_regex.match(name)
  if not name_match:
    raise ValueError('The name %s contains invalid characters' % name)

logging.basicConfig(
  stream = sys.stdout,
  level  = logging.DEBUG if verbose else logging.INFO,
  format = '%(asctime)s - %(levelname)s: %(message)s',
)

# Check if the input files actually exist
for input_fn in input_fns:
  if not os.path.isfile(input_fn):
    raise ValueError('Input file %s does not exist' % input_fn)
if not os.path.isdir(output_dir):
  if not force:
    raise ValueError('Output directory %s does not exist (use -f/--force to create it)' % output_dir)
  else:
    try:
      logging.debug("Creating directory: %s" % output_dir)
      os.makedirs(output_dir)
    except IOError as err:
      raise ValueError('Unable to create directory %s because: %s' % (output_dir, err))

# Open the ROOT files
file_handles = [ ROOT.TFile.Open(input_fn, 'read') for input_fn in input_fns ]
for i, file_handle in enumerate(file_handles):
  if not file_handle:
    raise ValueError('Unable to open %s ROOT file: %s' % (i, input_fns[i]))

# Check if the user requested to find the RLE Venn diagram for all the branches or for specific ones
# In case all branches were requested, the user should've left the trees argument empty
if not trees:
  # Let's get common list of TTree names
  input_trees = [
    { key.GetName() for key in file_handle.GetListOfKeys() if key.GetClassName() == 'TTree' } \
    for file_handle in file_handles
  ]
  superset_trees = input_trees[0]
  for i in range(1, nof_groups):
    superset_trees = superset_trees | input_trees[i]
  trees = superset_trees
  logging.debug('Found the following common TTree(s): %s' % ', '.join(trees))

# Make sure that the run, lumi and event branch names are present in all common TTrees in all files
rle_brs = { run_name, lumi_name, event_name }
tree_idxs = {}
for tree in trees:
  tree_idxs[tree] = []
  for i, file_handle in enumerate(file_handles):
    tree_handle = file_handle.Get(tree)
    if not tree_handle:
      continue
    tree_idxs[tree].append(i)
    brs = { br.GetName() for br in tree_handle.GetListOfBranches()  }
    if (rle_brs & brs) != rle_brs:
      raise ValueError(
        'Could not find the run, lumi and event branches (%s, %s and %s) in tree %s of the %s file %s' % \
        (run_name, lumi_name, event_name, tree, names[i], input_fns[i])
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
    if rles:
      f.write('\n')

# Now we can start looping over the entries in each TTree simultaneously and construct the so-called
# Venn diagram
for tree, idxs in tree_idxs.items():
  sets = {}
  if len(idxs) < 2:
    continue
  for idx in idxs:
    tree_handle = file_handles[idx].Get(tree)
    nentries = tree_handle.GetEntries()

    logging.debug('Found %d entries in tree %s of file %s' % (nentries, tree, input_fns[idx]))

    # Construct the array objects that will be bound to the TTree
    run_array = get_branch_array(tree_handle, run_name)
    lumi_array = get_branch_array(tree_handle, lumi_name)
    event_array = get_branch_array(tree_handle, event_name)

    rles = set()
    for j in range(nentries):
      tree_handle.GetEntry(j)
      rles.add(':'.join(map(lambda br: str(br[0]), [run_array, lumi_array, event_array])))
    sets[idx] = rles

  # Generate the combinations of groups that select and reject events
  unique_idx_combinations = [
    combination                                       \
    for combination_length in range(2, len(idxs) + 1) \
    for combination in itertools.combinations(idxs, combination_length)
  ]
  for unique_idx_combination in unique_idx_combinations:
    idx_combinations = get_idx_combinations(unique_idx_combination)
    for idx_combination in idx_combinations:
      select_idxs = idx_combination[0]
      reject_idxs = idx_combination[1]

      venn = get_venn(sets, select_idxs, reject_idxs)

      # Construct the file name
      select_names = list(sorted([ names[select_idx] for select_idx in select_idxs ]))
      reject_names = list(sorted([ names[reject_idx] for reject_idx in reject_idxs ]))
      logging.debug(
        'Found %d event(s) which are selected by %s, but rejected by %s' % \
        (len(venn), ', '.join(select_names), ', '.join(reject_names))
      )
      out_fn = '%s_%s_select' % (tree, '_'.join(select_names))
      if reject_names:
        out_fn += '_%s_reject' % '_'.join(reject_names)
      out_fn += '.txt'
      out_fn_full = os.path.join(output_dir, out_fn)

      # Write the files to the output
      write_rles(out_fn_full, venn)

logging.info('All done: check the results in %s' % output_dir)
