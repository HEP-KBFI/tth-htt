#!/usr/bin/env python

# Finds the sum of LHE weights for a selection of samples
#
# Example #1: MINIAODs are on a local drive
#
# comp_lhe_weightsum.py \
#   -i /some/local/path/THQ_4f_Hincl_13TeV_madgraph_pythia8_Fall17 \
#      /some/local/path/THW_5f_Hincl_13TeV_madgraph_pythia8_Fall17 \
#   -o ~/output_directory/THQ.txt ~/output_directory/THW.txt \
#   -v
#
# Prints the results on the screen and also saves the weights to text files
# (~/output_directory/THQ.txt and ~/output_directory/THW.txt); also prints debug output
# on the screen (enabled w/ -v flag).
#
# Example #2: MINIAODs on eos, eos commands are available in the system (such as lxplus); if eos
#             commands are not available, then the script attempts to access the ROOT files
#             via XRD:
#
# comp_lhe_weightsum.py \
#   -i /eos/cms/store/some/paths/inbetween/THQ_4f_Hincl_13TeV_madgraph_pythia8_Fall17/MINIAODSIM
#      /eos/cms/store/some/paths/inbetween/THW_5f_Hincl_13TeV_madgraph_pythia8_Fall17/MINIAODSIM
#
# Option -o and flag -v in Example #1 are applicable here as well.

from DataFormats.FWLite import Events, Handle

import collections
import os
import math
import sys
import subprocess
import logging
import argparse

def cmd_execute(cmd_str):
  cmd = subprocess.Popen(cmd_str.split(), stdout = subprocess.PIPE, stderr = subprocess.PIPE)
  cmd_out, cmd_err = cmd.communicate()
  if cmd_err:
    raise ValueError('Got an error while executing %s: %s' % (cmd_str, cmd_err))
  return cmd_out.rstrip('\n')

def get_filelist(basedir):
  if basedir.startswith('/eos'):
    try:
      logging.debug('Trying eos on %s' % basedir)
      filelist = cmd_execute('eos ls %s' % basedir)
      return map(lambda filename: os.path.join(basedir, filename), filelist.split('\n'))
    except Exception as err:
      pass
    try:
      logging.debug('Trying XRD on %s' % basedir)
      filelist = cmd_execute('xrdfs root://eoscms.cern.ch ls %s' % basedir)
      return map(lambda filename: 'root://eoscms.cern.ch/%s' % filename, filelist.split('\n'))
    except Exception as err:
      pass
    raise ValueError('Cannot access files on %s because: %s' % (basedir, err))
  else:
    logging.debug('Trying local file system on %s' % basedir)
    return map(lambda filename: os.path.join(basedir, filename), os.listdir(basedir))

def exists(filename):
  if filename.startswith('/eos'):
    try:
      logging.debug('Trying eos on %s' % filename)
      result = cmd_execute('eos stat %s' % filename)
      return result.split()[1].replace('`','').replace("'",'') == filename
    except Exception as err:
      raise ValueError('Cannot access file %s on eos because: %s' % (filename, err))
  elif filename.startswith('root://eoscms.cern.ch/'):
    try:
      logging.debug('Trying XRD on %s' % filename)
      filename_noprefix = filename.replace('root://eoscms.cern.ch/','')
      result = cmd_execute('xrdfs root://eoscms.cern.ch stat %s' % filename_noprefix)
      return result.split()[1] == filename_noprefix
    except Exception as err:
      raise ValueError('Cannot access file %s on eos because: %s' % (filename, err))
  else:
    logging.debug('Trying local file system on %s' % filename)
    return os.path.isfile(filename)

class SmartFormatter(argparse.HelpFormatter):
  def _split_lines(self, text, width):
    if text.startswith('R|'):
      return text[2:].splitlines()
    return argparse.HelpFormatter._split_lines(self, text, width)

parser = argparse.ArgumentParser(
  formatter_class = lambda prog: SmartFormatter(prog, max_help_position = 50)
)
parser.add_argument('-i', '--input',
  type = str, nargs = '+', dest = 'input_basedirs', metavar = 'dir', default = None, required = True,
  help = 'R|Input basedirs',
)
parser.add_argument('-o', '--output-filenames',
  type = str, nargs = '+', dest = 'output_filenames', metavar = 'path', default = [], required = False,
  help = 'R|Output filenames where the RLE text files will be written to'
)
parser.add_argument('-f', '--force',
  dest = 'force', action = 'store_true', default = False,
  help = "R|Force creating the output directory if it doesn't exist",
)
parser.add_argument('-v', '--verbose',
  dest = 'verbose', action = 'store_true', default = False,
  help = 'R|Enable verbose output',
)
args = parser.parse_args()

logging.basicConfig(
  stream = sys.stdout,
  level  = logging.DEBUG if args.verbose else logging.INFO,
  format = '%(asctime)s - %(levelname)s: %(message)s',
)
basedirs = args.input_basedirs
output_filenames = args.output_filenames

if output_filenames:
  if len(basedirs) != len(output_filenames):
    raise ValueError(
      "The number of output file names (%d) does not coincide w/ the number of "
      "input base directories (%d); either drop the list of output filenames or "
      "provide the exact same number of output file names as input base directories" % \
      (len(output_filenames), len(basedirs))
    )

for output_filename in output_filenames:
  output_dir = os.path.dirname(output_filename)
  if not os.path.isdir(output_dir):
    logging.debug('Directory %s does not exist' % output_dir)
    if args.force:
      try:
        os.makedirs(output_dir)
      except OSError as err:
        raise ValueError('Could not create directory %s because: %s' % (output_dir, err))
    else:
      raise ValueError('Use -f/--force to create the output directory %s' % output_dir)

for basedir_idx, basedir in enumerate(basedirs):
  logging.info('Finding sum of weights for %s' % basedir)
  filenames = get_filelist(basedir)

  weight_map = collections.OrderedDict()
  for filename in filenames:
    assert(exists(filename))
    neg_weights = collections.OrderedDict()
    logging.debug('Processing %s ...' % filename)
    events = Events(filename)
    nof_events = events.size()
    logging.debug('Found %d events' % nof_events)
    lheinfo = Handle('LHEEventProduct')
    for event_idx, event in enumerate(events):
      event.getByLabel('externalLHEProducer', lheinfo)
      LHEEventProducts = lheinfo.product()
      weights = LHEEventProducts.weights()
      nom_weight = LHEEventProducts.originalXWGTUP()
      for weight in weights:
        if not weight.id.startswith('rwgt_'):
          continue
        if weight.id not in weight_map:
          weight_map[weight.id] = []
        if weight.wgt < 0.:
          if weight.id not in neg_weights:
            neg_weights[weight.id] = []
          neg_weights[weight.id].append((event_idx, weight.wgt))
        weight_map[weight.id].append(weight.wgt / nom_weight)
    if neg_weights:
      for weight_id, neg_array in neg_weights.items():
        logging.warning(
          'Found %d negative %s weights in file %s in the following events: %s' % \
          (len(neg_array), weight_id, filename, ', '.join(map(lambda x: '%d (%.6f)' % x, neg_array)))
        )

  logging.info('Found %d LHE weights:' % len(weight_map))
  weight_sums = collections.OrderedDict()
  for weight_id, weight_array in weight_map.items():
    weight_sums[weight_id] = math.fsum(weight_array)

  max_weight_id_len = max(map(len, list(weight_sums.keys())))
  for weight_id, weight_sum in weight_sums.items():
    print('{:<{len}} {:20.8f}'.format(
      weight_id, weight_sum, len = max_weight_id_len
    ))

  if output_filenames:
    with open(output_filenames[basedir_idx], 'w') as f:
      for weight_id, weight_sum in weight_sums.items():
        f.write('{:<{len}} {:20.8f}\n'.format(
          weight_id, weight_sum, len = max_weight_id_len
        ))
    logging.info('Wrote file %s' % output_filenames[basedir_idx])
