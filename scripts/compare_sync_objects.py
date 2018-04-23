#!/usr/bin/env python

import ROOT
import array
import math
import collections
import argparse
import os.path
import re
import logging
import sys

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

def pos_float(value):
  try:
    value_float = float(value)
  except ValueError:
    raise argparse.ArgumentTypeError('Not a float: %s' % value)
  if value_float <= 0.:
    raise argparse.ArgumentTypeError('Must be a positive float: %s' % value)
  return value_float

parser = argparse.ArgumentParser(
  formatter_class = lambda prog: SmartFormatter(prog, max_help_position = 55)
)

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
  type = pos_float, dest = 'dr', metavar = 'cone size', default = 0.01, required = False,
  help = 'R|Maximum cone size used in object dR-matching'
)
parser.add_argument('-v', '--verbose',
  dest = 'verbose', action = 'store_true', default = False,
  help = 'R|Enable verbose output',
)
args = parser.parse_args()

fn_ref  = args.input_ref
fn_test = args.input_test
tn      = args.tree
maxn    = args.max_events
dr_max  = args.dr

logging.basicConfig(
  stream = sys.stdout,
  level  = logging.DEBUG if args.verbose else logging.INFO,
  format = '%(asctime)s - %(levelname)s: %(message)s'
)

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

for fn in [fn_ref, fn_test]:
  if not os.path.isfile(fn):
    raise ValueError('No such file: %s' % fn)

f_ref  = ROOT.TFile.Open(fn_ref,  'read')
if not f_ref:
  raise ValueError('File %s is not a valid ROOT file' % fn_ref)
f_test = ROOT.TFile.Open(fn_test, 'read')
if not f_test:
  raise ValueError('File %s is not a valid ROOT file' % fn_test)

t_ref = f_ref.Get(tn)
if not t_ref:
  raise ValueError('File %s does not contain TTree named %s' % (fn_ref, tn))
t_test = f_test.Get(tn)
if not t_test:
  raise ValueError('File %s does not contain TTree named %s' % (fn_test, tn))

brns_ref    = { br.GetName() for br in t_ref.GetListOfBranches()  }
brns_test   = { br.GetName() for br in t_test.GetListOfBranches() }
brns_common = brns_ref & brns_test

run_bn = 'run'
ls_bn  = 'ls'
evt_bn = 'nEvent'

objs = {
  'mu'  : { 'n' : 2 },
  'ele' : { 'n' : 2 },
  'tau' : { 'n' : 2 },
  'jet' : { 'n' : 4 },
}

common_brns = { 'pt', 'eta', 'phi', 'E', }

lep_brns = common_brns | {
  'charge', 'dxy', 'dz', 'miniRelIso', 'miniIsoCharged', 'miniIsoNeutral', 'PFRelIso04',
  'jetNDauChargedMVASel', 'jetPtRel', 'jetPtRatio', 'jetCSV', 'sip3D', 'dxyAbs',
  'isfakeablesel', 'ismvasel', 'leptonMVA',
}

objs['mu']['brns'] = lep_brns | {
  'segmentCompatibility', 'mediumID', 'dpt_div_pt',
}

objs['ele']['brns'] = lep_brns | {
  'ntMVAeleID', 'isChargeConsistent', 'passesConversionVeto', 'nMissingHits',
  'sigmaEtaEta', 'HoE', 'deltaEta', 'deltaPhi', 'OoEminusOoP',
}

objs['tau']['brns'] = common_brns | {
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

objs['jet']['brns'] = common_brns | { 'CSV', }

# The branch names of run, lumi and event numbers should definitely be in the sync Ntuple
evt_brns_list = [ run_bn, ls_bn, evt_bn ]
evt_brns = set(evt_brns_list)
if evt_brns - brns_common:
  raise ValueError(
    'Invalid branch names for run, lumi and event numbers: %s, %s, %s' % (run_bn, ls_bn, evt_bn)
  )

# Construct explicit object-level branch names
expl = lambda obj_pfx, obj_brns, nmax_obj: {
  '%s%d_%s' % (obj_pfx, idx, obj_brn) for idx in range(1, nmax_obj + 1) for obj_brn in obj_brns
}

# Remove object-specific branch names that are missing from the common list of branch names
def clean_brns(obj_brns, obj_pfx, nmax_obj):
  obj_brns_to_remove = set()
  for obj_brn in obj_brns:
    is_present = True
    for obj_idx in range(1, nmax_obj + 1):
      br = '%s%d_%s' % (obj_pfx, obj_idx, obj_brn)
      if br not in brns_common:
        is_present = False
    if not is_present:
      logging.debug("Removing missing attribute '%s' from collection %s" % (obj_brn, obj_pfx))
      obj_brns_to_remove.add(obj_brn)
  cleaned_obj_brns = obj_brns - obj_brns_to_remove
  for obj_brn in cleaned_obj_brns:
    logging.debug("Attribute '%s' available for collection %s" % (obj_brn, obj_pfx))
  return list(sorted(list(cleaned_obj_brns)))

for obj_pfx, obj_entry in objs.items():
  obj_entry['brns'] = clean_brns(obj_entry['brns'], obj_pfx, obj_entry['n'])

# Reconstruct the list of common branch names once again
def expl_brns(obj_brns, obj_pfx, nmax_obj):
  return {
    '%s%d_%s' % (obj_pfx, obj_idx, obj_brn) \
    for obj_idx in range(1, nmax_obj + 1)   \
    for obj_brn in obj_brns
  }

brns_common_final = evt_brns
for obj_pfx, obj_entry in objs.items():
  brns_common_final = brns_common_final | expl_brns(obj_entry['brns'], obj_pfx, obj_entry['n'])

def get_brs(t):
  return {
    br.GetName() : get_array(t, br) for br in t.GetListOfBranches() \
    if br.GetName() in brns_common_final
  }

brs_ref  = get_brs(t_ref)
brs_test = get_brs(t_test)

def get_rles(t, brs):
  n = t.GetEntries()
  rles = collections.OrderedDict()
  for i in range(n):
    t.GetEntry(i)
    rle = ':'.join(map(lambda brn: str(brs[brn][0]), evt_brns_list))
    rles[rle] = i
  return rles

rle_ref  = get_rles(t_ref,  brs_ref)
rle_test = get_rles(t_test, brs_test)

# Find the list of common RLE numbers
common_rles = []
for rle in rle_ref:
  if rle in rle_test:
    common_rles.append(rle)
logging.debug('Found %d common events by run, lumi and event numbers' % len(common_rles))

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

class ParticleBase(object):
  pass

class Particle(ParticleBase):
  def __init__(self, pfx, brs, brns):
    for brn in brns:
      setattr(self, brn, brs['%s_%s' % (pfx, brn)][0])

  def isValid(self):
    return not (self.eta < -10. or self.phi < -10.)

class ParticleWrapper(object):
  def __init__(self, pfx, brns):
    self.pfx  = pfx
    self.brns = brns
    self.ref  = None
    self.test = None
    self.diff = ParticleBase()
    self.counter = {
      'ref'    : 0,
      'test'   : 0,
      'common' : 0,
    }
    self.isMatched = False
    self.maxBrnLen = max(map(lambda brn: len(brn), self.brns)) + 1

  def update(self):
    self.ref  = Particle(self.pfx, brs_ref,  self.brns)
    self.test = Particle(self.pfx, brs_test, self.brns)
    for brn in self.brns:
      setattr(self.diff, brn, getattr(self.ref, brn) - getattr(self.test, brn))
    self.isMatched = self.get_matching()
    self.counter['ref']    += int(self.ref.isValid())
    self.counter['test']   += int(self.test.isValid())
    self.counter['common'] += int(self.isMatched)

  def get_matching(self):
    if not (self.ref.isValid() or self.test.isValid()):
      return False
    dr = math.sqrt(self.diff.eta ** 2 + self.diff.phi ** 2)
    return dr < dr_max

  def print(self, brns_selection = []):
    missing_brns = set(brns_selection) - set(self.brns)
    if missing_brns:
      raise ValueError(
        'Invalid branch names requested for %s: %s' % (self.pfx, ', '.join(missing_brns))
      )
    brns_to_print = brns_selection if brns_selection else self.brns
    for brn in brns_to_print:
      ref_val  = getattr(self.ref,  brn)
      test_val = getattr(self.test, brn)
      diff_val = getattr(self.diff, brn)

      ref_fmt  = '{:>13.6f}' if type(ref_val)  == float else '{:^13}'
      test_fmt = '{:>13.6f}' if type(test_val) == float else '{:^13}'
      diff_fmt = '{:>13.6f}' if type(diff_val) == float else '{:^13}'

      ref_print  = ref_fmt.format(ref_val)   if ref_val  != -9999 else '{:^13}'.format('-')
      test_print = test_fmt.format(test_val) if test_val != -9999 else '{:^13}'.format('-')
      diff_print = diff_fmt.format(diff_val) if ref_val  != -9999 and \
                                                test_val != -9999 else '{:^13}'.format('-')

      print('  {}  {:{len}}  {}  vs  {}  => {}'.format(
        self.pfx, brn, ref_print, test_print, diff_print, len = self.maxBrnLen
      ))

  def get_summary(self):
    print(
      '{:<6} {:>7} in ref, {:>7} in test, {:>7} dR-matched'.format(
      '%s:' % self.pfx, self.counter['ref'], self.counter['test'], self.counter['common']
    ))

class Event(object):
  def __init__(self, maxn):
    self.maxn    = maxn
    self.counter = 0
    self.obj_list = []
    for obj_pfx, obj_entry in objs.items():
      for obj_idx in range(1, obj_entry['n'] + 1):
        pfx = '%s%d' % (obj_pfx, obj_idx)
        setattr(self, pfx, ParticleWrapper(pfx, obj_entry['brns']))
        self.obj_list.append(pfx)

  def update(self):
    for obj_pfx in self.obj_list:
      pw = getattr(self, obj_pfx)
      pw.update()
    self.counter += 1

  def cont(self):
    return self.maxn < 0 or (0 <= self.counter < self.maxn)

  def get_summary(self):
    print('Total number of events considered: %d' % self.counter)
    for obj_pfx in self.obj_list:
      pw = getattr(self, obj_pfx)
      pw.get_summary()

evt = Event(maxn)

for rle in rle_loop:
  if not evt.cont():
    break

  t_ref.GetEntry(rle_ref[rle])
  t_test.GetEntry(rle_test[rle])

  evt.update()

  # Modify start
  if not evt.tau1.isMatched:
    continue

  print('RLE %s' % rle)
  evt.tau1.print()

  # Modify end

evt.get_summary()
