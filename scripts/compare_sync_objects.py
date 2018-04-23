#!/usr/bin/env python

import ROOT
import array
import math
import collections
import argparse
import os
import re
import logging
import sys
import matplotlib.pyplot as plt
import numpy as np

typeMap = {
  'Int_t'     : 'i',
  'UInt_t'    : 'I',
  'Float_t'   : 'f',
  'Double_t'  : 'd',
  'Char_t'    : 'b',
  'UChar_t'   : 'B',
  'Long64_t'  : 'l',
  'ULong64_t' : 'L',
  'Bool_t'    : 'b',
}

def get_array(tree_object, branch, maxlen = 1):
  branch_name = branch.GetName()
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

class SmartFormatter(argparse.ArgumentDefaultsHelpFormatter):
  def _split_lines(self, text, width):
    if text.startswith('R|'):
      return text[2:].splitlines()
    return argparse.ArgumentDefaultsHelpFormatter._split_lines(self, text, width)

def positive_float_type(value):
  try:
    value_float = float(value)
  except ValueError:
    raise argparse.ArgumentTypeError('Not a float: %s' % value)
  if value_float <= 0.:
    raise argparse.ArgumentTypeError('Must be a positive float: %s' % value)
  return value_float

def positive_int_type(value):
  try:
    value_int = int(value)
  except ValueError:
    raise argparse.ArgumentTypeError('Not a float: %s' % value)
  if value_int <= 0.:
    raise argparse.ArgumentTypeError('Must be a positive integer: %s' % value)
  return value_int

parent_parser = argparse.ArgumentParser(
  formatter_class = lambda prog: SmartFormatter(prog, max_help_position = 55)
)
subparsers = parent_parser.add_subparsers(title = 'commands', dest = 'command')
inspect_parser = subparsers.add_parser(
  'inspect', formatter_class = lambda prog: SmartFormatter(prog, max_help_position = 55)
)
plot_parser = subparsers.add_parser(
  'plot', formatter_class = lambda prog: SmartFormatter(prog, max_help_position = 55)
)
for parser in subparsers.choices.values():
  parser.add_argument('-i', '--input-ref',
    type = str, dest = 'input_ref', metavar = 'path', required = True,
    help = 'R|Input reference file',
  )
  parser.add_argument('-j', '--input-test',
    type = str, dest = 'input_test', metavar = 'path', required = True,
    help = 'R|Input test file',
  )
  parser.add_argument('-t', '--tree',
    type = str, dest = 'tree', metavar = 'name', default = 'syncTree', required = False,
    help = 'R|TTree name',
  )
  parser.add_argument('-r', '--rle',
    type = str, dest = 'rle', metavar = 'path/list', default = [], required = False,
    help = 'R|Path to the list of run:lumi:event numbers, or explicit space-separated list of those',
  )
  parser.add_argument('-n', '--max-events',
    type = int, dest = 'max_events', metavar = 'number', default = -1, required = False,
    help = 'R|Maximum number of events to be considered (default: -1, i.e. all dR-matched objects)',
  )
  parser.add_argument('-d', '--dr',
    type = positive_float_type, dest = 'dr', metavar = 'cone size', default = 0.01, required = False,
    help = 'R|Maximum cone size used in object dR-matching'
  )
  parser.add_argument('-v', '--verbose',
    dest = 'verbose', action = 'store_true', default = False,
    help = 'R|Enable verbose output',
  )
plot_parser.add_argument('-o', '--output-dir',
  type = str, dest = 'output_dir', metavar = 'path', default = '.', required = False,
  help = 'R|Output directory for the plots',
)
plot_parser.add_argument('-p', '--plot-type',
  type = str, nargs = '+', dest = 'plot_type', metavar = 'style', required = False,
  choices = [ 'scatter', 'histogram' ], default = [ 'scatter', 'histogram' ],
  help = 'R|Plot type',
)
plot_parser.add_argument('-s', '--plot-scale',
  type = str, nargs = '+', dest = 'plot_scale', metavar = 'scale', required = False,
  choices = [ 'log', 'linear' ], default = [ 'log', 'linear' ],
  help = 'R|Plot scale',
)
plot_parser.add_argument('-b', '--bins',
  type = positive_int_type, dest = 'bins', metavar = 'number', required = False, default = 101,
  help = 'R|Number of bins (for the floating point histogram)',
)
plot_parser.add_argument('-e', '-extension',
  type = str, nargs = '+', dest = 'extension', metavar = 'extension', required = False,
  choices = [ 'png', 'pdf' ], default = [ 'png' ],
  help = 'R|Output format of the plot',
)
plot_parser.add_argument('-R', '--ref-label',
  type = str, dest = 'ref_label', metavar = 'name', required = False, default = '',
  help = 'R|Plotting label for reference data',
)
plot_parser.add_argument('-T', '--test-label',
  type = str, dest = 'test_label', metavar = 'name', required = False, default = '',
  help = 'R|Plotting label for test data',
)
plot_parser.add_argument('-f', '--force',
  dest = 'force', action = 'store_true', default = False,
  help = "R|Create the output directory if it doesn't exist",
)
args = parent_parser.parse_args()

filename_ref    = args.input_ref
filename_test   = args.input_test
tree_name       = args.tree
max_events      = args.max_events
dr_max          = args.dr

enable_plot     = args.command == 'plot'
plot_output_dir = args.output_dir
plot_type       = args.plot_type
plot_scale      = args.plot_scale
plot_bins       = args.bins
plot_ref_label  = args.ref_label  if args.ref_label  else os.path.basename(filename_ref)
plot_test_label = args.test_label if args.test_label else os.path.basename(filename_test)
plot_force      = args.force
plot_extension  = args.extension

logging.basicConfig(
  stream = sys.stdout,
  level  = logging.DEBUG if args.verbose else logging.INFO,
  format = '%(asctime)s - %(levelname)s: %(message)s'
)

if enable_plot and not os.path.isdir(plot_output_dir):
  if plot_force:
    logging.debug('Directory %s does not exist; attempting to create it')
    try:
      os.makedirs(plot_output_dir)
    except IOError as reason:
      raise ValueError('Could not create directory %s because: %s' % (plot_output_dir, reason))
  else:
    raise ValueError('Directory %s does not exist (use -f/--force to create it)' % plot_output_dir)

rle_selection = []
rle_pattern = re.compile('\d+:\d+:\d+')
if len(args.rle) == 1:
  if rle_pattern.match(args.rle[0]):
    rle_selection = args.rle
  else:
    if not os.path.isfile(args.rle[0]):
      raise ValueError('No such file: %s' % args.rle[0])
    with open(args.rle[0], 'r') as rle_f:
      for line in rle_f:
        line_stripped = line.rstrip('\n')
        if rle_pattern.match(line_stripped):
          rle_selection.append(line_stripped)
        else:
          raise ValueError(
            "The following line in %s doesn't adhere to format 'run:lumi:event': %s" % \
            (args.rle[0], line_stripped)
          )
else:
  if not all(map(lambda rle_nr: rle_pattern.match(rle_nr), args.rle)):
    raise ValueError("Not all RLE numbers adhere to format 'run:lumi:event'")
  rle_selection = args.rle

for filename in [filename_ref, filename_test]:
  if not os.path.isfile(filename):
    raise ValueError('No such file: %s' % filename)

file_ref = ROOT.TFile.Open(filename_ref, 'read')
if not file_ref:
  raise ValueError('File %s is not a valid ROOT file' % filename_ref)
file_test = ROOT.TFile.Open(filename_test, 'read')
if not file_test:
  raise ValueError('File %s is not a valid ROOT file' % filename_test)

tree_ref = file_ref.Get(tree_name)
if not tree_ref:
  raise ValueError('File %s does not contain TTree named %s' % (filename_ref, tree_name))
tree_test = file_test.Get(tree_name)
if not tree_test:
  raise ValueError('File %s does not contain TTree named %s' % (filename_test, tree_name))

branch_names_ref    = { branch.GetName() for branch in tree_ref.GetListOfBranches()  }
branch_names_test   = { branch.GetName() for branch in tree_test.GetListOfBranches() }
branch_names_common = branch_names_ref & branch_names_test

run_branch_name = 'run'
ls_branch_name  = 'ls'
evt_branch_name = 'nEvent'

objects_map = {
  'mu'  : { 'n' : 2, 'human_name' : 'muon'     },
  'ele' : { 'n' : 2, 'human_name' : 'electron' },
  'tau' : { 'n' : 2, 'human_name' : 'tau'      },
  'jet' : { 'n' : 4, 'human_name' : 'jet'      },
}

common_branch_names = { 'pt', 'eta', 'phi', 'E', }

lepton_branch_names = common_branch_names | {
  'charge', 'dxy', 'dz', 'miniRelIso', 'miniIsoCharged', 'miniIsoNeutral', 'PFRelIso04',
  'jetNDauChargedMVASel', 'jetPtRel', 'jetPtRatio', 'jetCSV', 'sip3D', 'dxyAbs',
  'isfakeablesel', 'ismvasel', 'leptonMVA',
}

objects_map['mu']['branch_names'] = lepton_branch_names | {
  'segmentCompatibility', 'mediumID', 'dpt_div_pt',
}

objects_map['ele']['branch_names'] = lepton_branch_names | {
  'ntMVAeleID', 'isChargeConsistent', 'passesConversionVeto', 'nMissingHits',
  'sigmaEtaEta', 'HoE', 'deltaEta', 'deltaPhi', 'OoEminusOoP',
}

objects_map['tau']['branch_names'] = common_branch_names | {
  'charge', 'dxy', 'dz',
  'decayModeFindingOldDMs', 'decayModeFindingNewDMs',

  'byVLooseIsolationMVArun2v1DBdR03oldDMwLT',
  'byLooseIsolationMVArun2v1DBdR03oldDMwLT',
  'byMediumIsolationMVArun2v1DBdR03oldDMwLT',
  'byTightIsolationMVArun2v1DBdR03oldDMwLT',
  'byVTightIsolationMVArun2v1DBdR03oldDMwLT',
  'rawMVArun2v1DBdR03oldDMwLT',

  'byCombinedIsolationDeltaBetaCorr3Hits',
  'byLooseCombinedIsolationDeltaBetaCorr3Hits',
  'byMediumCombinedIsolationDeltaBetaCorr3Hits',
  'byTightCombinedIsolationDeltaBetaCorr3Hits',

  'byLooseCombinedIsolationDeltaBetaCorr3HitsdR03',
  'byMediumCombinedIsolationDeltaBetaCorr3HitsdR03',
  'byTightCombinedIsolationDeltaBetaCorr3HitsdR03',

  'againstMuonLoose3', 'againstMuonTight3',

  'againstElectronVLooseMVA6', 'againstElectronLooseMVA6',
  'againstElectronMediumMVA6', 'againstElectronTightMVA6',
}

objects_map['jet']['branch_names'] = common_branch_names | { 'CSV', }

# The branch names of run, lumi and event numbers should definitely be in the sync Ntuple
event_branch_names_list = [ run_branch_name, ls_branch_name, evt_branch_name ]
event_branch_names      = set(event_branch_names_list)
if event_branch_names - branch_names_common:
  raise ValueError(
    'Invalid branch names for run, lumi and event numbers: %s, %s, %s' % \
    (run_branch_name, ls_branch_name, evt_branch_name)
  )

# Remove object-specific branch names that are missing from the common list of branch names
def filter_branch_names(obj_branch_names, obj_prefix, nmax_obj):
  obj_branch_names_to_remove = set()
  for obj_branch_name in obj_branch_names:
    is_present = True
    for obj_idx in range(1, nmax_obj + 1):
      br = '%s%d_%s' % (obj_prefix, obj_idx, obj_branch_name)
      if br not in branch_names_common:
        is_present = False
    if not is_present:
      logging.debug("Removing missing attribute '{}' from collection {}".format(
        obj_branch_name, obj_prefix,
      ))
      obj_branch_names_to_remove.add(obj_branch_name)
  filtered_obj_branch_names = obj_branch_names - obj_branch_names_to_remove
  for obj_branch_name in filtered_obj_branch_names:
    logging.debug("Attribute '%s' available for collection %s" % (obj_branch_name, obj_prefix))
  return list(sorted(list(filtered_obj_branch_names)))

for obj_prefix, obj_entry in objects_map.items():
  obj_entry['branch_names'] = filter_branch_names(
    obj_entry['branch_names'], obj_prefix, obj_entry['n']
  )

# Reconstruct the list of common branch names once again
def explicit_branch_names(obj_branch_names, obj_prefix, nmax_obj):
  return {
    '%s%d_%s' % (obj_prefix, obj_idx, obj_branch_name) \
    for obj_idx in range(1, nmax_obj + 1)           \
    for obj_branch_name in obj_branch_names
  }

branch_names_common_final = event_branch_names
for obj_prefix, obj_entry in objects_map.items():
  branch_names_common_final = branch_names_common_final | explicit_branch_names(
    obj_entry['branch_names'], obj_prefix, obj_entry['n']
  )

def get_branches(tree):
  return {
    branch.GetName() : get_array(tree, branch) for branch in tree.GetListOfBranches() \
    if branch.GetName() in branch_names_common_final
  }

branches_ref  = get_branches(tree_ref)
branches_test = get_branches(tree_test)

def get_rles(tree, branches):
  nof_entries = tree.GetEntries()
  rles = collections.OrderedDict()
  for event_idx in range(nof_entries):
    tree.GetEntry(event_idx)
    rle = ':'.join(map(lambda branch_name: str(branches[branch_name][0]), event_branch_names_list))
    rles[rle] = event_idx
  return rles

rle_ref  = get_rles(tree_ref, branches_ref)
rle_test = get_rles(tree_test, branches_test)

# Find the list of common RLE numbers
common_rles = []
for rle in rle_ref:
  if rle in rle_test:
    common_rles.append(rle)
logging.debug(
  'Found %d/%d/%d common/in ref/in test events by run, lumi and event numbers' % \
  (len(common_rles), len(rle_ref), len(rle_test))
)

# Make sure that if the user provided a list of RLE numbers for selection, that they are present
# in both Ntuples; if not, then ignore the RLE number(s) specified by the user
rle_loop = common_rles
if rle_selection:
  rle_loop = []
  for rle in rle_selection:
    if rle not in common_rles:
      logging.debug('RLE %s not present in both Ntuples' % rle)
    else:
      rle_loop.append(rle)

def isinteger(x):
  # Credit to: https://stackoverflow.com/a/7236784
  return np.equal(np.mod(x, 1), 0).all()

def plot(var_name, ref_values, test_values, output_dir, plot_type, scale, ref_label, test_label,
         human_name, prefix, extensions, nof_bins):

  skip_plot = False
  fig = plt.figure(figsize = (10, 8))
  if plot_type == 'scatter':
    filtered_values = list(filter(
      lambda value_pair: value_pair[0] != -9999 and value_pair[1] != -9999,
      zip(ref_values, test_values)
    ))
    ref_values_filtered  = np.asarray([ filtered_value[0] for filtered_value in filtered_values ])
    test_values_filtered = np.asarray([ filtered_value[1] for filtered_value in filtered_values ])

    xmin = ref_values_filtered.min()
    xmax = ref_values_filtered.max()
    ymin = test_values_filtered.min()
    ymax = test_values_filtered.max()

    if isinteger(ref_values_filtered) and isinteger(test_values_filtered):
      xmin -= 0.5
      xmax += 0.5
      ymin -= 0.5
      ymax += 0.5
    else:
      xmin *= 0.95 if xmin > 0. else 1.05
      xmax *= 1.05 if xmax > 0. else 0.95
      ymin *= 0.95 if ymin > 0. else 1.05
      ymax *= 1.05 if ymax > 0. else 0.95

    plt.xlim(xmin, xmax)
    plt.ylim(ymin, ymax)

    plt.plot(ref_values_filtered, test_values_filtered, 'o')
    plt.xlabel(ref_label)
    plt.ylabel(test_label)

    if scale == 'log':
      if xmin > 0 and xmax > 0:
        plt.xscale('log')
        plt.yscale('log')
      else:
        logging.debug(
          'Skipping scatter plot w/ logarithmic axes b/c %s contains negative values' % var_name
        )
        skip_plot = True
  elif plot_type == 'histogram':
    ref_values_filtered  = np.asarray([ value for value in ref_values  if value != -9999 ])
    test_values_filtered = np.asarray([ value for value in test_values if value != -9999 ])

    xmin = min(ref_values_filtered.min(), test_values_filtered.min())
    xmax = max(ref_values_filtered.max(), test_values_filtered.max())

    if isinteger(ref_values_filtered) and isinteger(test_values_filtered):
      xmin -= 1
      xmax += 2
      nof_bins = xmax - xmin + 1
    else:
      xmin *= 0.95 if xmin > 0. else 1.05
      xmax *= 1.05 if xmax > 0. else 0.95

    plt.xlim(xmin, xmax)
    bins = np.linspace(xmin, xmax, nof_bins)

    ref_label  = '%s (%d)' % (ref_label,  len(ref_values_filtered))
    test_label = '%s (%d)' % (test_label, len(test_values_filtered))

    plt.hist(ref_values_filtered,  bins = bins, label = ref_label,  alpha = 0.4, edgecolor = 'black')
    plt.hist(test_values_filtered, bins = bins, label = test_label, alpha = 0.4, edgecolor = 'black')
    plt.legend(loc = 'upper right')
    plt.xlabel(var_name)
    plt.ylabel('# of dR-matched %s' % human_name)

    if scale == 'log':
      plt.yscale('log', nonposy = 'clip')
  else:
    raise ValueError('Invalid plot type: %s' % plot_type)

  plt.title('%s of dR-matched %s (%d)' % (var_name, human_name, len(ref_values)))
  plt.grid(True)

  if not skip_plot:
    for extension in extensions:
      output_filename = os.path.join(
        output_dir, '%s_%s_%s_%s.%s' % (prefix, var_name, plot_type, scale, extension)
      )
      plt.savefig(output_filename, bbox_inches = 'tight')
      logging.debug('Created plot: %s' % output_filename)
  plt.clf()

class ParticleBase(object):
  pass

class Particle(ParticleBase):
  def __init__(self, prefix, branches, branch_names):
    for branch_name in branch_names:
      setattr(self, branch_name, branches['%s_%s' % (prefix, branch_name)][0])

  def isValid(self):
    return not (self.eta == -9999. or self.phi == -9999.)

class ParticleWrapper(object):
  def __init__(self, prefix, branch_names, human_name):
    self.prefix       = prefix
    self.branch_names = branch_names
    self.human_name   = human_name

    self.ref  = None
    self.test = None
    self.diff = ParticleBase()

    self.counter = {
      'ref'    : 0,
      'test'   : 0,
      'common' : 0,
    }
    self.recordings = {}
    self.isMatched = False
    self.max_branch_name_len = max(map(lambda branch_name: len(branch_name), self.branch_names)) + 1

  def update(self):
    self.ref  = Particle(self.prefix, branches_ref, self.branch_names)
    self.test = Particle(self.prefix, branches_test, self.branch_names)
    for branch_name in self.branch_names:
      setattr(
        self.diff, branch_name, getattr(self.ref, branch_name) - getattr(self.test, branch_name)
      )
    self.isMatched = self.get_matching()
    self.counter['ref']    += int(self.ref.isValid())
    self.counter['test']   += int(self.test.isValid())
    self.counter['common'] += int(self.isMatched)

  def get_matching(self):
    if not (self.ref.isValid() or self.test.isValid()):
      return False
    dr = math.sqrt(self.diff.eta ** 2 + self.diff.phi ** 2)
    return dr < dr_max

  def print(self, branch_names_selection = []):
    missing_branch_names = set(branch_names_selection) - set(self.branch_names)
    if missing_branch_names:
      raise ValueError(
        'Invalid branch names requested for %s: %s' % (self.prefix, ', '.join(missing_branch_names))
      )
    branch_names_to_print = branch_names_selection if branch_names_selection else self.branch_names
    for branch_name in branch_names_to_print:
      ref_value  = getattr(self.ref,  branch_name)
      test_value = getattr(self.test, branch_name)
      diff_value = getattr(self.diff, branch_name)

      ref_format  = '{:>13.6f}' if type(ref_value)  == float else '{:^13}'
      test_format = '{:>13.6f}' if type(test_value) == float else '{:^13}'
      diff_format = '{:>13.6f}' if type(diff_value) == float else '{:^13}'

      ref_str  = ref_format.format(ref_value)   if ref_value  != -9999 else '{:^13}'.format('-')
      test_str = test_format.format(test_value) if test_value != -9999 else '{:^13}'.format('-')
      diff_str = diff_format.format(diff_value) if ref_value  != -9999 and \
                                                   test_value != -9999 else '{:^13}'.format('-')

      print('  {}  {:{len}}  {}  vs  {}  => {}'.format(
        self.prefix, branch_name, ref_str, test_str, diff_str, len = self.max_branch_name_len
      ))

  def get_summary(self):
    print(
      '{:<6} {:>7} in ref, {:>7} in test, {:>7} dR-matched'.format(
      '%s:' % self.prefix, self.counter['ref'], self.counter['test'], self.counter['common']
    ))

  def record(self, branch_names_selection = []):
    missing_branch_names = set(branch_names_selection) - set(self.branch_names)
    if missing_branch_names:
      raise ValueError(
        'Invalid branch names requested for %s: %s' % (self.prefix, ', '.join(missing_branch_names))
      )
    branch_names_to_plot = branch_names_selection if branch_names_selection else self.branch_names

    if not self.isMatched:
      return

    for branch_name in branch_names_to_plot:
      if branch_name not in self.recordings:
        self.recordings[branch_name] = { 'ref' : [], 'test' : [] }
      for source in self.recordings[branch_name]:
        source_instance = getattr(self, source)
        recorded_value  = getattr(source_instance, branch_name)
        self.recordings[branch_name][source].append(recorded_value)

  def plot(self, output_dir, plot_types, scales, ref_label, test_label, extension, bins):
    human_name = '%ss' % self.human_name
    for branch_name in self.recordings:
      ref_values  = self.recordings[branch_name]['ref']
      test_values = self.recordings[branch_name]['test']
      assert(len(ref_values) == len(test_values))
      for scale in scales:
        for plot_type in plot_types:
          plot(
            branch_name, ref_values, test_values, output_dir, plot_type, scale, ref_label,
            test_label, human_name, self.prefix, extension, bins
          )

class Event(object):
  def __init__(self, max_events):
    self.max_events = max_events
    self.counter    = 0

    leading_types = [ 'leading', 'subleading', 'third', 'fourth' ]

    self.objects_list = []
    for obj_prefix, obj_entry in objects_map.items():
      for obj_idx in range(1, obj_entry['n'] + 1):
        prefix = '%s%d' % (obj_prefix, obj_idx)
        assert(obj_idx <= len(leading_types))
        human_name = '%s %s' % (leading_types[obj_idx - 1], obj_entry['human_name'])
        setattr(self, prefix, ParticleWrapper(prefix, obj_entry['branch_names'], human_name))
        self.objects_list.append(prefix)

  def update(self):
    for obj_prefix in self.objects_list:
      particle_instance = getattr(self, obj_prefix)
      particle_instance.update()
    self.counter += 1

  def cont(self):
    return self.max_events < 0 or (0 <= self.counter < self.max_events)

  def get_summary(self):
    print('Total number of events considered: %d' % self.counter)
    for obj_prefix in self.objects_list:
      particle_instance = getattr(self, obj_prefix)
      particle_instance.get_summary()

  def plot(self, output_dir, plot_type, scale, ref_label, test_label, extension, bins):
    for obj_prefix in self.objects_list:
      particle_instance = getattr(self, obj_prefix)
      particle_instance.plot(output_dir, plot_type, scale, ref_label, test_label, extension, bins)

evt = Event(max_events)

for rle in rle_loop:
  if not evt.cont():
    break

  tree_ref.GetEntry(rle_ref[rle])
  tree_test.GetEntry(rle_test[rle])

  evt.update()

  # Modify start

  if not evt.mu1.isMatched:
    continue

  if evt.mu1.ref.isfakeablesel == evt.mu1.test.isfakeablesel:
    continue

  print('RLE %s' % rle)
  evt.mu1.print()
  evt.mu1.record()

  # Modify end

evt.get_summary()
if enable_plot:
  evt.plot(
    plot_output_dir, plot_type, plot_scale, plot_ref_label, plot_test_label, plot_extension,
    plot_bins
  )
