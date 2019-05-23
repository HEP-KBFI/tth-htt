#!/usr/bin/env python
# -*- coding: utf-8 -*-

'''
A script for comparing two sync Ntuples by dR-matching individual objects.

TODO: Add examples here.

Author: K. Ehatäht
'''

import argparse
import array
import collections
import copy
import logging
import math
import matplotlib.pyplot as plt
import numpy as np
import os
import re
import ROOT
import sys

# Mapping between ROOT data types and python's array data types
TYPE_MAP = {
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

# Default placeholder value for a variable that is not filled in sync Ntuples
PLACEHOLDER = -9999

# A map that contains information about each object collection
# The map keys serve as shorthand prefixes for the branch names (e.g. mu = muon); the three values:
# - n -- number of the objects per event;
# - human_name -- human-readable name for the collection
# - branch_names -- list of branch names associated with the collection
# Example: the sync Ntuples are expected to hold information about two muons; variables such as
#          pt and mediumID should be present for both muons. Consequently, both sync Ntuples
#          should contain branches: mu1_pt, mu2_pt, mu1_mediumID, mu2_mediumID.
# As a side note, it's not necessary to specify all variable names that are supposed be present in
# both Ntuples because we could only look for the intersection of the branch names derived from
# both Ntuples and use these. However, we still decided against it because of two reasons:
# - otherwise we would not be able to tell, which variables are missing yet expected according
#   to the documentation of synchronization
# - when investigating a particular problem, there's no need to fire up the documentation page in
#   order to search for the correct branch names; instead, the user can copy the name from this file
OBJECTS_MAP = collections.OrderedDict()
OBJECTS_MAP['mu']       = { 'n' : 2, 'human_name' : 'muon'        }
OBJECTS_MAP['ele']      = { 'n' : 2, 'human_name' : 'electron'    }
OBJECTS_MAP['tau']      = { 'n' : 2, 'human_name' : 'tau'         }
OBJECTS_MAP['jet']      = { 'n' : 4, 'human_name' : 'jet'         }
OBJECTS_MAP['jetFwd']   = { 'n' : 4, 'human_name' : 'forward jet' }
OBJECTS_MAP['jetAK8']   = { 'n' : 2, 'human_name' : 'AK8 jet'     }
OBJECTS_MAP['jetHTTv2'] = { 'n' : 2, 'human_name' : 'HTTv2 jet'   }
OBJECTS_MAP['ak4Jet']   = { 'n' : 2, 'human_name' : 'ak4 jet'     }
OBJECTS_MAP['ak8Jet']   = { 'n' : 2, 'human_name' : 'ak8 jet'     }
OBJECTS_MAP['ak8lsJet'] = { 'n' : 2, 'human_name' : 'ak8 LS jet'  }

# For counting the number of preselected objects
PRESELECTION_COUNTER_BRANCHES = [ 'n_presel_%s' % object_prefix for object_prefix in OBJECTS_MAP ]
MAX_PRESELECTION_BRANCH_NAME_LEN = max(map(len, PRESELECTION_COUNTER_BRANCHES))

# 4-momentum should be written for all objects
COMMON_BRANCH_NAMES = { 'pt', 'eta', 'phi', 'E', }

# Common to both electrons and muons
LEPTON_BRANCH_NAMES = COMMON_BRANCH_NAMES | {
  'charge', 'dxy', 'dz', 'miniRelIso', 'miniIsoCharged', 'miniIsoNeutral', 'PFRelIso04',
  'jetNDauChargedMVASel', 'jetPtRel', 'jetPtRatio', 'jetCSV', 'jetDeepCSV', 'jetDeepJet',
  'sip3D', 'dxyAbs', 'isfakeablesel', 'ismvasel', 'leptonMVA', 'conept', 'isGenMatched',
}

OBJECTS_MAP['mu']['branch_names'] = LEPTON_BRANCH_NAMES | {
  'segmentCompatibility', 'mediumID', 'dpt_div_pt', 'isGenMatched'
}

OBJECTS_MAP['ele']['branch_names'] = LEPTON_BRANCH_NAMES | {
  'ntMVAeleID', 'isChargeConsistent', 'passesConversionVeto', 'nMissingHits',
  'sigmaEtaEta', 'HoE', 'deltaEta', 'deltaPhi', 'OoEminusOoP',
}

OBJECTS_MAP['tau']['branch_names'] = COMMON_BRANCH_NAMES | {
  'charge', 'dxy', 'dz',
  'decayModeFindingOldDMs', 'decayModeFindingNewDMs',

  'byVLooseIsolationMVArun2v1DBdR03oldDMwLT',
  'byLooseIsolationMVArun2v1DBdR03oldDMwLT',
  'byMediumIsolationMVArun2v1DBdR03oldDMwLT',
  'byTightIsolationMVArun2v1DBdR03oldDMwLT',
  'byVTightIsolationMVArun2v1DBdR03oldDMwLT',
  'rawMVArun2v1DBdR03oldDMwLT',

  'againstMuonLoose3', 'againstMuonTight3',

  'againstElectronVLooseMVA6', 'againstElectronLooseMVA6',
  'againstElectronMediumMVA6', 'againstElectronTightMVA6',
}

OBJECTS_MAP['jet']['branch_names'] = COMMON_BRANCH_NAMES | { 'CSV', 'DeepCSV', 'DeepJet', 'QGdiscr' }

OBJECTS_MAP['jetFwd']['branch_names'] = COMMON_BRANCH_NAMES

OBJECTS_MAP['jetAK8']['branch_names'] = COMMON_BRANCH_NAMES

OBJECTS_MAP['jetHTTv2']['branch_names'] = COMMON_BRANCH_NAMES

OBJECTS_MAP['ak4Jet']['branch_names'] = COMMON_BRANCH_NAMES | { 'CSV', }

SUBJET_BRANCHES = { 'subjet%d_%s' % (idx, variable) for idx in range(2) for variable in set(COMMON_BRANCH_NAMES | { 'CSV', }) }

OBJECTS_MAP['ak8Jet']['branch_names'] = COMMON_BRANCH_NAMES | { 'msoftdrop', 'tau1', 'tau2' } | SUBJET_BRANCHES

OBJECTS_MAP['ak8lsJet']['branch_names'] = COMMON_BRANCH_NAMES | { 'msoftdrop', 'tau1', 'tau2' } | SUBJET_BRANCHES

LEADING_TYPES = [ 'leading', 'subleading', 'third', 'fourth' ]

RLE_PATTERN = re.compile('\d+:\d+:\d+')
OBJ_PATTERN = re.compile('(?P<pfx>\w+)(?P<idx>\d+)')

class ParticleBase(object):
  '''A dummy class (needed by the ParticleWrapper class to initialize the diff member variable)
  '''
  pass

class Particle(ParticleBase):
  '''Holds data for certain type of source (either reference or test) and for certain type of
     object (e.g. mu1, jet2)
  '''
  def __init__(self, prefix, branches, branch_names):
    '''
    :param prefix: string, full prefix name that stands for the type of collection
    :param branches: list of array instances, already bound to the Ntuple
    :param branch_names: list of strings, valid list list of variables/branch names for this
                                          particular collection (e.g. pt, eta, phi)
    '''
    # Initialize individual variables (such as pt, eta phi); they'll be accessible as ordinary
    # member variables (e.g. self.pt, self.eta, self.phi)
    for branch_name in branch_names:
      setattr(self, branch_name, branches['%s_%s' % (prefix, branch_name)][0])

    # Already check if the object was actually selected to the Ntuple
    # We check eta and phi because these are needed to perform dR-matching in parent classes
    self.is_valid = not (self.eta == PLACEHOLDER or self.phi == PLACEHOLDER)

class ParticleWrapper(object):
  '''Container for the variables of a particular collection, for both reference and test data
     Also auto-computes differences (test values subtracted from respective reference values)
  '''
  def __init__(self, prefix, branch_names, branches_ref, branches_test, dr_max):
    '''
    :param prefix: string, full prefix name for the collection (e.g. mu1, jet2)
    :param branch_names: list of strings, a valid list of variables/branch names for this collection
    :param branches_ref: map (key = string, value = array instance), variables for the reference data
    :param branches_test: map (key = string, value = array instance), variables for the test data
    :param dr_max: float, maximum dR within which the two objects from reference and test Ntuples
                          must be in order to consider them ,,dR-matched''
    '''
    self.prefix        = prefix
    self.branch_names  = branch_names
    self.dr_max        = dr_max
    self.branches_ref  = branches_ref
    self.branches_test = branches_test

    self.ref  = None
    self.test = None
    self.diff = ParticleBase()

    # To book-keep the number of objects stored in both reference and test sync Ntuples, as well
    # as the number of dR-matched objects.
    self.counter = {
      'ref'    : collections.OrderedDict([( 'ispresel', 0 )]),
      'test'   : collections.OrderedDict([( 'ispresel', 0 )]),
      'common' : collections.OrderedDict([( 'ispresel', 0 )]),
    }
    self.recordings = {} # data for plotting
    self.is_matched = False
    self.max_branch_name_len = max(map(lambda branch_name: len(branch_name), self.branch_names)) + 1

    self.selection_branches = [ 'isfakeablesel', 'ismvasel' ]
    self.record_fakeable_and_tight = not bool(set(self.selection_branches) - set(self.branch_names))
    if self.record_fakeable_and_tight:
      for branch_name in self.selection_branches:
        for record_entry in self.counter.values():
          record_entry[branch_name] = 0

  def update(self):
    '''Update the values of all variables in this collection
    :return: None
    '''
    # Create new instances of Particle class
    self.ref  = Particle(self.prefix, self.branches_ref,  self.branch_names)
    self.test = Particle(self.prefix, self.branches_test, self.branch_names)

    # Compute the differences b/w the variables in the reference data and in the data data
    for branch_name in self.branch_names:
      setattr(
        self.diff, branch_name, getattr(self.ref, branch_name) - getattr(self.test, branch_name)
      )

    # Already check if the objects are dR-matched or not
    self.is_matched = self.get_matching()

    # Record the findings
    self.counter['ref']['ispresel']    += int(self.ref.is_valid)
    self.counter['test']['ispresel']   += int(self.test.is_valid)
    self.counter['common']['ispresel'] += int(self.is_matched)

    if self.record_fakeable_and_tight:
      for branch_name in self.selection_branches:
        for record_type in [ 'ref', 'test' ]:
          source = getattr(self, record_type)

          is_valid = int(getattr(source, 'is_valid'))
          passes_selection = int(getattr(source, branch_name))

          # Increment the counter only if the object is actually a valid one -- in case
          # the isfakeablesel and ismvasel branches are filled incorrectly, we might overestimate
          # the number of fakeable and tight objects
          self.counter[record_type][branch_name] += max(min(is_valid, passes_selection), 0)

        passes_selection_ref  = getattr(self.ref,  branch_name)
        passes_selection_test = getattr(self.test, branch_name)
        self.counter['common'][branch_name] += int(
          passes_selection_ref and passes_selection_test and self.is_matched
        )

  def get_matching(self):
    '''Check if the object in the refernce data matches to the object in the test data
    :return: bool, True if there's a match, False otherwise

    Also, if either of the objects is not filled (i.e. eta and/or phi variables have been set to
    a placeholder value) then objects are not considered to be ,,dR-matched''.
    '''
    if not (self.ref.is_valid or self.test.is_valid):
      return False
    dr = math.sqrt(self.diff.eta ** 2 + self.diff.phi ** 2)
    return dr < self.dr_max

  def printVars(self, branch_names_selection = []):
    '''Print a selection of variables and their differences in this collection
    :param branch_names_selection: list of strings, variables to be printed
    :return: None
    '''
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

      ref_str  = ref_format.format(ref_value)   if ref_value  != PLACEHOLDER else '{:^13}'.format('-')
      test_str = test_format.format(test_value) if test_value != PLACEHOLDER else '{:^13}'.format('-')
      diff_str = diff_format.format(diff_value) if ref_value  != PLACEHOLDER and \
                                                   test_value != PLACEHOLDER else '{:^13}'.format('-')

      print('  {}  {:{len}}  {}  vs  {}  => {}'.format(
        self.prefix, branch_name, ref_str, test_str, diff_str, len = self.max_branch_name_len
      ))

  def get_summary(self):
    '''Printout of statistics: how many objects were in the reference and test data, and how many
       objects were actually dR-matched.
    :return: None
    '''
    preselection_keys = [ 'ispresel' ]
    all_selection_keys = preselection_keys + self.selection_branches

    selection_keys = all_selection_keys if self.record_fakeable_and_tight else preselection_keys
    max_key_len = max(map(len, all_selection_keys))

    for selection_key in selection_keys:
      print(
        '{:<{len}}  {:<6} {:>7} ({:>7}) in ref, {:>7} ({:>7}) in test, {:>7} dR-matched'.format(
          selection_key,
          '%s:' % self.prefix,
          self.counter['ref'][selection_key],
          self.counter['ref'][selection_key] - self.counter['common'][selection_key],
          self.counter['test'][selection_key],
          self.counter['test'][selection_key] - self.counter['common'][selection_key],
          self.counter['common'][selection_key],
          len = max_key_len,
      ))

  def record(self, branch_names_selection = []):
    '''Record current values for a selection of variables only if the object at hand is dR-matched
       b/w reference and test data
    :param branch_names_selection: list of strings, (valid) list of variables to be recorded;
                                                    if none provided, all variables are recorded
    :return: None

    Example: record(['pt', 'eta']) will record only the current values of 'pt' and 'eta'.
    '''

    # If the user provided a custom list of variables for recording, make sure that these variables
    # are actually valid and available in this class
    missing_branch_names = set(branch_names_selection) - set(self.branch_names)
    if missing_branch_names:
      raise ValueError(
        'Invalid branch names requested for %s: %s' % (self.prefix, ', '.join(missing_branch_names))
      )
    branch_names_to_plot = branch_names_selection if branch_names_selection else self.branch_names

    # Do not record if the objects don't match (in synchronization, we're interested in
    # discrepancies b/w the same, i.e dR-matched objects taken from two different sync Ntuples)
    if not self.is_matched:
      return

    # Loop over the variables subject to recording
    for branch_name in branch_names_to_plot:
      if branch_name not in self.recordings:
        self.recordings[branch_name] = { 'ref' : [], 'test' : [] }
      # Save both reference and test variables separately
      for source in self.recordings[branch_name]:
        source_instance = getattr(self, source)
        recorded_value  = getattr(source_instance, branch_name)
        self.recordings[branch_name][source].append(recorded_value)

  def plot(self, output_dir, plot_types, scales, ref_label, test_label, extension, bins):
    '''Plots all recorded data held by both reference and test Ntuples for this collection
    :param output_dir: string, path to the directory where the plots are saved
    :param plot_types: list of strings, types of plots (allowed choices: scatter, histogram)
    :param scales: list of strings, axis scales of the plots (allowed choices: linear, log)
    :param ref_label: string, a label for the reference data
    :param test_label: string, a label for the test data
    :param extension: list of string, file extensions of the plots (allowed choices: png, pdf)
    :param bins: int, number of bins (valid only for a histogram and for data of floating point type)
    :return: None
    '''
    for branch_name in self.recordings:
      # We enter here only if there's something recorded for variable (branch_name)
      ref_values  = self.recordings[branch_name]['ref']  # reference data
      test_values = self.recordings[branch_name]['test'] # test data

      # Make sure that we have exactly the same amount of reference data as test data
      assert(len(ref_values) == len(test_values))

      # Loop over individual scales and types
      for scale in scales:
        for plot_type in plot_types:
          plot(
            prefix        = self.prefix,
            variable_name = branch_name,
            ref_values    = ref_values,
            test_values   = test_values,
            output_dir    = output_dir,
            plot_type     = plot_type,
            scale         = scale,
            ref_label     = ref_label,
            test_label    = test_label,
            extensions    = extension,
            nof_bins      = bins,
          )

class Event(object):
  '''Event-level container for storing, retrieving and updating data from multiple sync Ntuple
     for the same object collection.
  '''
  def __init__(self, max_events, objects_map, branches_ref, branches_test, dr_max):
    '''
    :param max_events: int, maximum number of events to be considered
    :param objects_map: map of maps, meta-information about each collection (such as the prefix,
                                     number of objects, valid branch names)
    :param branches_ref: map (key = string, value = array instance), variables for the reference data
    :param branches_test: map (key = string, value = array instance), variables for the test data
    :param dr_max: float, maximum cone size used in dR-matching
    '''
    self.max_events = max_events
    self.counter    = 0 # increased every time we read a new object

    # Here we want to construct the full prefix from the collection names and object multiplicities
    # (i.e. mu1, mu2, ele1, ele2, etc etc). These prefixes can be used to access individual
    # ParticleWrapper instances in some other parts of the code. However, when we want to update
    # these instances, plot some data held by these instances, or retrieve a summary from them, we
    # need keep track of the member variables which refer to these instances.
    self.objects_list = []
    for obj_prefix, obj_entry in objects_map.items():
      for obj_idx in range(1, obj_entry['n'] + 1):
        # Construct the full prefix name
        prefix = '%s%d' % (obj_prefix, obj_idx)

        # Initialize the instance and save the full prefix name
        setattr(self, prefix, ParticleWrapper(
          prefix, obj_entry['branch_names'], branches_ref, branches_test, dr_max
        ))
        self.objects_list.append(prefix)

  def update(self):
    '''Update individual ParticleWrapper instances (such as mu1, mu2, ele1, ele2 etc)
    :return: None

    Increments the counter variable by one.
    '''
    for obj_prefix in self.objects_list:
      particle_instance = getattr(self, obj_prefix)
      particle_instance.update()
    self.counter += 1

  def cont(self):
    '''Check if it's possible to process more events
    :return: True if it is, False otherwise

    The check if the counter variable is below the user-specified limit on the number of events
    that should be processed.
    '''
    return self.max_events < 0 or (0 <= self.counter < self.max_events)

  def get_summary(self):
    '''Print a summary for each ParticleWrapper instance (such as mu1, mu2, ele1, ele2 etc)
    :return: None
    '''
    print('Total number of events considered: %d' % self.counter)
    for obj_prefix in self.objects_list:
      particle_instance = getattr(self, obj_prefix)
      particle_instance.get_summary()

  def plot(self, output_dir, types, scales, ref_label, test_label, extensions, bins):
    '''Plots all recorded data held by individual ParticleWrapper instances (such as mu1, mu2 etc)
    :param output_dir: string, path to the output directory where the plots will be saved
    :param types: list of strings, types of plots (allowed choices: scatter, histogram)
    :param scales: list of strings, types of scales (allowed choices: linear, log)
    :param ref_label: string, a label for the reference data
    :param test_label: string, a label for the test data
    :param extensions: list of strings, file extensions for the plot files (allowed choices: png, pdf)
    :param bins: int, number of bins (valid only in histograms for data of floating point type)
    :return: None
    '''
    for obj_prefix in self.objects_list:
      particle_instance = getattr(self, obj_prefix)
      particle_instance.plot(output_dir, types, scales, ref_label, test_label, extensions, bins)

class SmartFormatter(argparse.ArgumentDefaultsHelpFormatter):
  '''Auxiliary class for argparse.ArgumentParser instance
  '''
  def _split_lines(self, text, width):
    '''Auxiliary function to increase the width of the help message.
       Basically overloads the functionality of argparse.ArgumentDefaultsHelpFormatter._split_lines()
    :param text: string, the help message
    :param width: int, maximum width allocated for the option and its metavar(s)
    :return: whatever argparse.ArgumentDefaultsHelpFormatter._split_lines() returns

    In order to extend the field width of the option and its metavar(s), the help message must
    start with 'R|' (without quotes). This prefix is automatically removed in the actual help message.
    '''
    if text.startswith('R|'):
      return text[2:].splitlines()
    return argparse.ArgumentDefaultsHelpFormatter._split_lines(self, text, width)

def explicit_branch_names(obj_branch_names, obj_prefix, nmax_obj):
  '''Constructs explicit branch names from the object prefix, multiplicity and variable names
  :param obj_branch_names: list of strings, object level branch/variable names (e.g. pt, eta, phi)
  :param obj_prefix: string, object prefix (e.g. mu)
  :param nmax_obj: int, number of objects (e.g. 2)
  :return: set of strings, each string is explicit branch name (e.g. mu1_pt, mu2_phi)
  '''
  return {
    '%s%d_%s' % (obj_prefix, obj_idx, obj_branch_name) \
    for obj_idx in range(1, nmax_obj + 1)              \
    for obj_branch_name in obj_branch_names
  }

def get_array(tree_object, branch, maxlen = 1):
  '''Returns an array object that is bound to a TTree, given the ROOT.TBranch instance
  :param tree_object: ROOT.TTree, to which the array is bound
  :param branch: ROOT.TBranch, corresponding to the array instance
  :param maxlen: int, maximum array length for the array instance
  :return: array instance, that is bound to the TTree
  '''
  # First we check if the TTree contains the TBranch (by comparing the names)
  branch_name = branch.GetName()
  branch_list = [ br for br in tree_object.GetListOfBranches() ]
  branch_list_filtered = list(filter(lambda br: br.GetName() == branch_name, branch_list))

  # Make sure that the branch name is unique to this TTree
  assert(len(branch_list_filtered) == 1)

  # Obtain a TLeaf object that helps us to deduce the type of the variable
  leaf_object = branch_list_filtered[0].GetLeaf(branch_name)
  leaf_type = leaf_object.GetTypeName()
  if leaf_type not in TYPE_MAP:
    raise ValueError('Unrecognized type found in branch %s: %s' % (branch_name, leaf_type))

  # Retrieve a string that is used to define the array type in python
  array_type = TYPE_MAP[leaf_type]

  # Initialize the array, given the type
  array_unit = [0.] if array_type in ['f', 'd'] else [0]
  branch_array = array.array(array_type, array_unit * maxlen)

  # Bind the array to the TTree
  tree_object.SetBranchAddress(branch_name, branch_array)

  return branch_array

def get_branches(tree, branch_names):
  '''Construct a map, where the keys are explicit branch names and values correspond to the array
     object that is bound to the TBranch of the same name as the branch name
  :param tree: ROOT.TTree, instance to which the address binding is done
  :param branch_names: list of strings, branch names subject to address binding
  :return: map (key = string, value = array instance)
  '''
  return {
    branch.GetName() : get_array(tree, branch) for branch in tree.GetListOfBranches() \
    if branch.GetName() in branch_names
  }

def filter_branch_names(obj_branch_names, obj_prefix, nmax_obj, branch_names_common):
  '''Returns list of variable/branch names of an object that is present in the list of common branch
     names
  :param obj_branch_names: list of strings, the list of variable/branch names (e.g. pt, eta, phi)
  :param obj_prefix: string, collection name (e.g. mu, ele, tau, jet)
  :param nmax_obj: int, expected multiplicty of the objects in the collection
  :param branch_names_common: list of strings, list of common branch names
  :return: list of strings, list of variable/branch names that corresponds to the object collection
                            and is present in the list common branch names
  '''
  # Collect the list of variables which we want to remove from the provided (full) list of variables
  # because we want to make sure that the variables are the same at all indices (see below)
  obj_branch_names_to_remove = set()
  for obj_branch_name in obj_branch_names:
    # We first assume that the variable is present in the collection, regardless of the multiplicity
    # If it turns out that a variable (e.g. pt) is present in the collection (say, mu) for at certain
    # index (e.g. mu1_pt) but not present at some other index (e.g. mu2_pt), then we discard
    # the variable. This is to ensure that the list of variables is the same within the collection.
    is_present = True
    for obj_idx in range(1, nmax_obj + 1):
      # Construct the full branch name, based on the collection prefix, object index and variable name
      branch_name_full = '%s%d_%s' % (obj_prefix, obj_idx, obj_branch_name)
      if branch_name_full not in branch_names_common:
        # The branch is not present in the full list of common branch names at this particular object
        # index, which means that we have to disregard the variable
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

def get_rles(tree, branches, event_branch_names_list):
  '''Map all run, lumi and event numbers to placement indices in a TTree
  :param tree: ROOT.TTree, where the placement indices are taken from
  :param branches: map (key = string, value = array instance)
  :param event_branch_names_list: list of strings, containing the branch names for run, lumi and
                                                   and event numbers (exactly in this order)
  :return: map (key = string, value = int), that maps run, lumi and event numbers (formatted as
                                            run:lumi:event) to the placement index in the TTree
  '''
  nof_entries = tree.GetEntries()
  rles = collections.OrderedDict()
  for event_idx in range(nof_entries):
    tree.GetEntry(event_idx)
    rle = ':'.join(map(lambda branch_name: str(int(branches[branch_name][0])), event_branch_names_list))
    rles[rle] = event_idx
  return rles

def isinteger(x):
  '''Checks if the input numpy array is compatible to an integer array
     Credit to: https://stackoverflow.com/a/7236784
  :param x: numpy array
  :return: bool, True if the array contains only integers, false otherwise

  Note that if the array technically contains floats such as 1. and 2., they would still be
  considered as integers by this function. This is handy if some people have saved an integer
  variable as a float to the Ntuple and we want to still treat these floats as integers.
  '''
  return np.equal(np.mod(x, 1), 0).all()

def get_human_name(prefix):
  '''
  :param prefix: string, name of the collection, including the object index (e.g. mu2)
  :return: string, corresponding human-readable string to the prefix (e.g. subleading muons)
  '''
  # First check if the prefix actually follows the expected format <collection name><index>
  prefix_match = OBJ_PATTERN.match(prefix)
  if not prefix_match:
    raise ValueError("Invalid prefix: %s" % prefix)
  # Recover generic collection name and object index (e.g. mu and 2)
  obj_name = prefix_match['pfx']
  obj_idx  = int(prefix_match['idx'])

  # Make sure that the object index can be translated into a human-readable string
  assert (obj_idx <= len(LEADING_TYPES))

  human_name = '%s %ss' % (LEADING_TYPES[obj_idx - 1], OBJECTS_MAP[obj_name]['human_name'])
  return human_name

def plot(prefix, variable_name, ref_values, test_values, output_dir, plot_type, scale, ref_label,
         test_label, extensions, nof_bins):
  '''Creates and save the plot, given the information from two sync Ntuples
  :param prefix: string, collection name (including the ordering index, e.g. 'mu1')
  :param variable_name: string, variable name (e.g. pt)
  :param ref_values: list of floats/integers, reference values to be plotted
  :param test_values: list of floats/integers, test values to be plotted
  :param output_dir: string, output directory where the plots will be saved
  :param plot_type: string, plot type (allowed choices: scatter, histogram)
  :param scale: string, plot scale (allowed choices: linear, log)
  :param ref_label: string, label for the reference data (x-axis label in scatter plot,
                            legend label in histogram)
  :param test_label: string, label for the test data (y-axis label in scatter plot, legend label
                             in histogram)
  :param extensions: list of strings, file extensions for the plots
  :param nof_bins: int, number of bins to be considered in a histogram (valid only for floating
                        point data)
  :return: None
  '''

  logging.debug(
    'Creating {} {} plot for {} variable using {} collection'.format(
      plot_type, scale, variable_name, prefix
    )
  )

  human_name = get_human_name(prefix) # need this later when giving the plot a title
  fig = plt.figure(figsize = (10, 8)) # in inches
  skip_plot = False # can only be set to True in case of a scatter plot w/ log axes and negative data

  if plot_type == 'scatter':
    # We want to avoid the case that one group filled the sync Ntuple w/ valid values but the other
    # forgot to do so, thus filling the branch w/ a placeholder value (a large negative number).
    # If we were to keep such erroneous values, the scatter plot would stretch beyond the region
    # of interest.
    filtered_values = list(filter(
      lambda value_pair: value_pair[0] != PLACEHOLDER and value_pair[1] != PLACEHOLDER and \
                         not math.isnan(value_pair[0]) and not math.isnan(value_pair[1]),
      zip(ref_values, test_values)
    ))
    ref_values_filtered  = np.asarray([ filtered_value[0] for filtered_value in filtered_values ])
    test_values_filtered = np.asarray([ filtered_value[1] for filtered_value in filtered_values ])

    xmin = ref_values_filtered.min()
    xmax = ref_values_filtered.max()
    ymin = test_values_filtered.min()
    ymax = test_values_filtered.max()

    if isinteger(ref_values_filtered) and isinteger(test_values_filtered):
      # If the data is of integer type, we'll increase the plot limits by 0.5 from the maximum and
      # minimum values in the data, so that all points would be visible on the plot
      xmin -= 0.5
      xmax += 0.5
      ymin -= 0.5
      ymax += 0.5
    else:
      # If the data is of floating point type, we'll increase the plot limits by 5% so that all
      # points would be visible on the plot. Negative limits must be treated separately: if xmin
      # is, say, -100, and we would want to decrease it to -105; if xmin is 100, we would want to
      # decrease it to 95.
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
          'Skipping scatter plot w/ logarithmic axes b/c %s contains negative values' % variable_name
        )
        skip_plot = True
  elif plot_type == 'histogram':
    # Unlike to the case of scatter plot, we don't care if a group has filled a variable
    # consistently or not at all: we can still plot the histogram of the other group
    ref_values_filtered  = np.asarray([
      value for value in ref_values  if value != PLACEHOLDER and not math.isnan(value)
    ])
    test_values_filtered = np.asarray([
      value for value in test_values if value != PLACEHOLDER and not math.isnan(value)
    ])

    xmin = min(ref_values_filtered.min(), test_values_filtered.min())
    xmax = max(ref_values_filtered.max(), test_values_filtered.max())

    if isinteger(ref_values_filtered) and isinteger(test_values_filtered):
      # If the data is of integer type, we plot one empty bin on both sides of the histogram.
      xmin -= 1.5
      xmax += 1.5
      nof_bins = int(xmax - xmin + 1)
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
    plt.xlabel(variable_name)
    plt.ylabel('# of dR-matched %s' % human_name)

    if scale == 'log':
      plt.yscale('log', nonposy = 'clip')
  else:
    raise ValueError('Invalid plot type: %s' % plot_type)

  plt.title('%s of dR-matched %s (%d)' % (variable_name, human_name, len(ref_values)))
  plt.grid(True)

  if not skip_plot:
    for extension in extensions:
      output_filename = os.path.join(
        output_dir, '%s_%s_%s_%s.%s' % (prefix, variable_name, plot_type, scale, extension)
      )
      plt.savefig(output_filename, bbox_inches = 'tight')
      logging.debug('Created plot: %s' % output_filename)
  fig.clf()
  plt.clf()

def positive_float_type(value):
  '''Auxiliary function to define a positive float type
  :param value: string, value provided by the user via CLI
  :return: float, the input value converted to a float

  May raise ArgumentTypeError if the user didn't provide a string convertible to a positive float
  '''
  try:
    value_float = float(value)
  except ValueError:
    raise argparse.ArgumentTypeError('Not a float: %s' % value)
  if value_float <= 0.:
    raise argparse.ArgumentTypeError('Must be a positive float: %s' % value)
  return value_float

def positive_int_type(value):
  '''Auxiliary function to define a positive int type
    :param value: string, value provided by the user via CLI
    :return: int, the input value converted to a int

    May raise ArgumentTypeError if the user didn't provide a string convertible to a positive int
    '''
  try:
    value_int = int(value)
  except ValueError:
    raise argparse.ArgumentTypeError('Not a float: %s' % value)
  if value_int <= 0.:
    raise argparse.ArgumentTypeError('Must be a positive integer: %s' % value)
  return value_int

def get_stats(filenames, object_tree_name, count_objects):
  for filename in filenames:
    if not os.path.isfile(filename):
      raise ValueError('No such file: %s' % filename)
    root_file = ROOT.TFile.Open(filename, 'read')
    if not root_file:
      raise ValueError('Not a valid ROOT file: %s' % filename)
    tree_keys = [ key.GetName() for key in root_file.GetListOfKeys() if key.GetClassName() == 'TTree' ]
    event_counts = { tree_name : root_file.Get(tree_name).GetEntries() for tree_name in tree_keys }
    max_tree_len = max(map(len, event_counts)) + 1
    print('%s:' % filename)
    for tree_name in sorted(event_counts.keys()):
      print('  {:<{len}} {}'.format('%s:' % tree_name, event_counts[tree_name], len = max_tree_len))
    if count_objects:
      if object_tree_name not in tree_keys:
        raise ValueError('No such TTree in %s: %s' % (object_tree_name, filename))
      object_tree = root_file.Get(object_tree_name)
      available_object_branches = {
        branch.GetName() : branch for branch in object_tree.GetListOfBranches()
      }
      missing_branches = set(PRESELECTION_COUNTER_BRANCHES) - set(available_object_branches.keys())
      if missing_branches:
        raise ValueError(
          'TTree %s in file %s is missing the following branches: %s' % \
          (object_tree_name, filename, ', '.join(missing_branches))
        )
      counter_map = collections.OrderedDict()
      for preselection_branch_name in PRESELECTION_COUNTER_BRANCHES:
        counter_map[preselection_branch_name] = {
          'counter' : 0,
          'branch'  : get_array(object_tree, available_object_branches[preselection_branch_name])
        }
      nof_entries = object_tree.GetEntries()
      for event_idx in range(nof_entries):
        object_tree.GetEntry(event_idx)
        for map_entry in counter_map.values():
          map_entry['counter'] += int(map_entry['branch'][0] > 0)
      for branch_name, map_entry in counter_map.items():
        print('  {:<{len}} {}'.format(
          '%s:' % branch_name, map_entry['counter'], len = MAX_PRESELECTION_BRANCH_NAME_LEN + 1
        ))


####################################################################################################

# The actual program starts here

# Define the list of command line arguments
parent_parser = argparse.ArgumentParser(
  formatter_class = lambda prog: SmartFormatter(prog, max_help_position = 55)
)
subparsers = parent_parser.add_subparsers(title = 'commands', dest = 'command')
count_parser = subparsers.add_parser(
  'count', formatter_class = lambda prog: SmartFormatter(prog, max_help_position = 55)
)
inspect_parser = subparsers.add_parser(
  'inspect', formatter_class = lambda prog: SmartFormatter(prog, max_help_position = 55)
)
plot_parser = subparsers.add_parser(
  'plot', formatter_class = lambda prog: SmartFormatter(prog, max_help_position = 55)
)
count_parser.add_argument('-i', '--input',
  type = str, nargs = '+', dest = 'input', metavar = 'path', required = True,
  help = 'R|Input files',
)
count_parser.add_argument('-t', '--tree',
  type = str, dest = 'tree', metavar = 'name', default = 'syncTree', required = False,
  help = 'R|TTree name',
)
count_parser.add_argument('-o', '--count-objects',
  dest = 'count_objects', action = 'store_true', default = False,
  help = 'R|Count the number of preselected objects',
)
count_parser.add_argument('-a', '--analysis',
  type = str, dest = 'analysis', metavar = 'analysis', required = False, default = 'tth', choices = [ 'tth', 'hh_bbww' ],
  help = 'R|Type of analysis the sync Ntuple was produced in',
)
for parser_name, parser in subparsers.choices.items():
  if parser_name == 'count':
    continue
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
    type = str, dest = 'rle', nargs = '+', metavar = 'path/list', default = [], required = False,
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
  parser.add_argument('-a', '--analysis',
    type = str, dest = 'analysis', metavar = 'analysis', required = False, default = 'tth', choices = [ 'tth', 'hh_bbww' ],
    help = 'R|Type of analysis the sync Ntuple was produced in',
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

# Parse the command line arguments
args = parent_parser.parse_args()

if args.analysis == 'tth':
  del OBJECTS_MAP['ak4Jet']
  del OBJECTS_MAP['ak8Jet']
  del OBJECTS_MAP['ak8lsJet']
  del OBJECTS_MAP['jetAK8']
  del OBJECTS_MAP['jetHTTv2']
elif args.analysis == 'hh_bbww':
  del OBJECTS_MAP['jet']
  del OBJECTS_MAP['jetFwd']
  del OBJECTS_MAP['jetAK8']
  del OBJECTS_MAP['jetHTTv2']
  del OBJECTS_MAP['tau']
  del OBJECTS_MAP['ak8lsJet']
PRESELECTION_COUNTER_BRANCHES = [ 'n_presel_%s' % object_prefix for object_prefix in OBJECTS_MAP ]

if args.command == 'count':
  get_stats(args.input, args.tree, args.count_objects)
  sys.exit(0)

filename_ref  = args.input_ref
filename_test = args.input_test
tree_name     = args.tree
max_events    = args.max_events
dr_max        = args.dr

enable_plot = args.command == 'plot'
if enable_plot:
  plot_output_dir = args.output_dir
  plot_type       = args.plot_type
  plot_scale      = args.plot_scale
  plot_bins       = args.bins
  plot_ref_label  = args.ref_label  if args.ref_label  else os.path.basename(filename_ref)
  plot_test_label = args.test_label if args.test_label else os.path.basename(filename_test)
  plot_force      = args.force
  plot_extension  = args.extension

# Enable verbose output if the user requested so
logging.basicConfig(
  stream = sys.stdout,
  level  = logging.DEBUG if args.verbose else logging.INFO,
  format = '%(asctime)s - %(levelname)s: %(message)s'
)

# Check if the output directory for the plots exists; if it doesn't, then create it if
# the user has provided a relevant command line flag for this action
if enable_plot and not os.path.isdir(plot_output_dir):
  if plot_force:
    logging.debug('Directory %s does not exist; attempting to create it')
    try:
      os.path.mkdirs(plot_output_dir)
    except IOError as reason:
      raise ValueError('Could not create directory %s because: %s' % (plot_output_dir, reason))
  else:
    raise ValueError('Directory %s does not exist (use -f/--force to create it)' % plot_output_dir)

rle_selection = []
if len(args.rle) == 1:
  if RLE_PATTERN.match(args.rle[0]):
    # The user has provided a single run, lumi and event number, in the format run:lumi:event
    rle_selection = args.rle
  else:
    # The user may gave provided a path to the file containing run, lumi and event numbers,
    # one per line; let's make sure that the file actually exists
    if not os.path.isfile(args.rle[0]):
      raise ValueError('No such file: %s' % args.rle[0])
    with open(args.rle[0], 'r') as rle_f:
      for line in rle_f:
        line_stripped = line.rstrip('\n')
        # Make sure that each run, lumi and event number follows the format run:lumi:event; if it
        # doesn't, raise an exception
        if RLE_PATTERN.match(line_stripped):
          rle_selection.append(line_stripped)
        else:
          raise ValueError(
            "The following line in %s doesn't adhere to format 'run:lumi:event': %s" % \
            (args.rle[0], line_stripped)
          )
else:
  # The user provided a space-delimited list of run, lumi and event numbers
  # We check that these numbers are specified in the format 'run:lumi:event'; if not, then
  # raise an exception
  unmatched_rles = [ rle_nr for rle_nr in args.rle if not RLE_PATTERN.match(rle_nr) ]
  if unmatched_rles:
    raise ValueError(
      "Not all RLE numbers adhere to the format 'run:lumi:event': %s" % ', '.join(unmatched_rles)
    )
  rle_selection = args.rle

for filename in [filename_ref, filename_test]:
  if not os.path.isfile(filename):
    raise ValueError('No such file: %s' % filename)

# Initialize TFile pointers; if the provided file names aren't ROOT files, the pointers
# will be null (or None in python bindings)
file_ref = ROOT.TFile.Open(filename_ref, 'read')
if not file_ref:
  raise ValueError('File %s is not a valid ROOT file' % filename_ref)
file_test = ROOT.TFile.Open(filename_test, 'read')
if not file_test:
  raise ValueError('File %s is not a valid ROOT file' % filename_test)

# Initialize TTree pointers; if the provided TTree name isn't present in the files, the pointers
# will be null (or None in python bindings)
tree_ref = file_ref.Get(tree_name)
if not tree_ref:
  raise ValueError('File %s does not contain TTree named %s' % (filename_ref, tree_name))
tree_test = file_test.Get(tree_name)
if not tree_test:
  raise ValueError('File %s does not contain TTree named %s' % (filename_test, tree_name))

# Get the full list of branch names from both TTrees; also find the list of common branch names
branch_names_ref    = { branch.GetName() for branch in tree_ref.GetListOfBranches()  }
branch_names_test   = { branch.GetName() for branch in tree_test.GetListOfBranches() }
branch_names_common = branch_names_ref & branch_names_test

# The following branch names are for run, lumi and event numbers; these must defintiely be present
# in both TTrees
run_branch_name = 'run'
ls_branch_name  = 'ls'
evt_branch_name = 'nEvent' if args.analysis == 'tth' else 'event'

# The branch names of run, lumi and event numbers should definitely be in the sync Ntuple
event_branch_names_list = [ run_branch_name, ls_branch_name, evt_branch_name ]
event_branch_names      = set(event_branch_names_list)
if event_branch_names - branch_names_common:
  raise ValueError(
    'Invalid branch names for run, lumi and event numbers: %s, %s, %s' % \
    (run_branch_name, ls_branch_name, evt_branch_name)
  )

# Deep-copy the existing objects map
objects_map = copy.deepcopy(OBJECTS_MAP)

# Remove object-specific branch names that are missing from the list of common branch names
for obj_prefix, obj_entry in objects_map.items():
  obj_entry['branch_names'] = filter_branch_names(
    obj_entry['branch_names'], obj_prefix, obj_entry['n'], branch_names_common
  )

# Reconstruct the list of common branch names from the branch names that are both defined in this
# script and present in the Ntuples; if we were to only remove the branch names defined in this
# script that are missing from the list of common branch names, we would bind too many addresses
# in the TTrees, thus slowing the file processing down. In other words, we want to keep the list
# of addresses that are bound to the TTrees minimal; otherwise we would also bind event-level
# variables, but we would never read them.
branch_names_common_final = event_branch_names
for obj_prefix, obj_entry in objects_map.items():
  branch_names_common_final = branch_names_common_final | explicit_branch_names(
    obj_entry['branch_names'], obj_prefix, obj_entry['n']
  )

# Bind the addresses in both TTrees; the resulting map is accessible via full branch name
branches_ref  = get_branches(tree_ref,  branch_names_common_final)
branches_test = get_branches(tree_test, branch_names_common_final)

# Get the mapping b/w run, lumi and event numbers, and the placement index of the event
# in the TTrees. The run, lumi and event numbers are expected to be ordered the same way as they're
# stored in the Ntuples. In other words, the placement indices are sequentially stored in the maps.
rle_ref  = get_rles(tree_ref,  branches_ref,  event_branch_names_list)
rle_test = get_rles(tree_test, branches_test, event_branch_names_list)

# Find the list of common run, lumi and event numbers. Since we want to preserve the order of
# run, lumi and event numbers so that the corresponding indices are in ascending order, we have
# to explicitly loop over the map (and not use python sets), because otherwise the indices will be
# reordered by the hashes of map keys (i.e. hashes of the run, lumi and event numbers). If were
# to use a set here, we would lose immensely in computing time, because ROOT files are not well
# suited for random, rather sequential access.
common_rles = []
for rle in rle_ref:
  if rle in rle_test:
    common_rles.append(rle)
logging.debug(
  'Found %d/%d/%d common/in ref/in test events by run, lumi and event numbers' % \
  (len(common_rles), len(rle_ref), len(rle_test))
)

# If the user provided an explicit list of run, lumi and event numbers to select only a subset of
# events from both Ntuples, then make sure that they really are present in both Ntuples;
# if not, then ignore such run, lumi and event number(s) specified by the user
rle_loop = common_rles
if rle_selection:
  rle_loop = []
  for rle in rle_selection:
    if rle not in common_rles:
      logging.debug('RLE %s not present in both Ntuples' % rle)
    else:
      rle_loop.append(rle)

# Construct the event object that holds all information about the event
# Each object is a member of this class, e.g. evt.jet1 gives a subleading object.
# To be fair, these ,,objects'' are not actually objects but a wrapper to objects constructed
# from the information in both Ntuples: one is a reference object (evt.jet1.ref) and the other
# is a test object (evt.jet1.test). Individual variables associated with these objects are
# accessible via corresponding branch names (e.g. pt of jet1 in the reference Ntuple can be
# accessed by reading evt.jet1.ref.pt). For convenience reasons, there's also a third ,,object''
# called diff (as in evt.jet1.diff), which is constructed by subtracting test values from respective
# reference values (e.g. evt.jet1.diff.phi is defined as evt.jet1.ref.phi - evt.jet1.test.phi).
# Both reference and test objects contain auxiliary variables and methods such as:
# - is_matched -- checks if both particles have been initialized and they're dR-matched
# - print() -- pretty-prints all variables and their differences associated with the object
# - record() -- save variables from both Ntuples to later use them in plotting
# Individual values are updated once the user has called GetEntry() on both TTrees, as well as
# update() on the Event object. The Event class comes with auxiliary functions as well:
# - cont() -- continue if the number of events hasn't reached the limit (as provided in the ctor)
# - get_summary() -- returns multiplicities of dR-matched objects
# - plot() -- plots everything that's been recorded in invidiual object wrappers
evt = Event(max_events, objects_map, branches_ref, branches_test, dr_max)

for rle in rle_loop:
  # If the number of processed events has reached a limit, end the loop
  if not evt.cont():
    break

  # Retrieve new information about the event
  tree_ref.GetEntry(rle_ref[rle])
  tree_test.GetEntry(rle_test[rle])
  evt.update()


  # Modify only between these long lines
  ##################################################################################################
  if not evt.mu1.is_matched:
    continue

#  if not (evt.mu1.ref.isfakeablesel == 1 and evt.mu1.test.isfakeablesel == 0):
#    continue

  if abs(evt.mu1.diff.leptonMVA) < 1e-2:
    continue

#  if abs(evt.mu1.diff.conept) < 1e-2:
#    continue

#  if abs(evt.mu1.diff.leptonMVA) > 1e-3:
#    continue

  print('RLE %s' % rle)
#  evt.mu1.printVars(['pt', 'eta', 'phi', 'conept', 'leptonMVA', 'isfakeablesel', 'ismvasel'])
  evt.mu1.printVars()
#  evt.mu1.record()
  ##################################################################################################

# Print the summary of dR-matched objects
evt.get_summary()

if enable_plot:
  # Plot everything that has been recorded so far
  evt.plot(
    output_dir = plot_output_dir,
    types      = plot_type,
    scales     = plot_scale,
    ref_label  = plot_ref_label,
    test_label = plot_test_label,
    extensions = plot_extension,
    bins       = plot_bins,
  )
