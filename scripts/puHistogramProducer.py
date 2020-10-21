#!/usr/bin/env python

# generate PU histogram from remote NANOAODSIM files for the synchronization exercise
# in case the sample have not been processed yet

import argparse
import subprocess
import os
import shutil

from tthAnalysis.HiggsToTauTau.common import logging, SmartFormatter

ERAS = {
  '2016' : {
    'dbs' : '/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/RunIISummer16NanoAODv4-PUMoriond17_Nano14Dec2018_102X_mcRun2_asymptotic_v6-v1/NANOAODSIM',
    'cat' : 'ttHToNonbb_M125_powheg',
  },
  '2017' : {
    'dbs' : '/ttHJetToNonbb_M125_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8/RunIIFall17NanoAODv4-PU2017_12Apr2018_Nano14Dec2018_new_pmx_102X_mc2017_realistic_v6-v1/NANOAODSIM',
    'cat' : 'ttHJetToNonbb_M125_amcatnlo',
  },
  '2018' : {
    'dbs' : '/ttHToNonbb_M125_TuneCP5_13TeV-powheg-pythia8/RunIIAutumn18NanoAODv4-Nano14Dec2018_102X_upgrade2018_realistic_v16-v1/NANOAODSIM',
    'cat' : 'ttHToNonbb_M125_powheg',
  },
}

parser = argparse.ArgumentParser(
  formatter_class = lambda prog: SmartFormatter(prog, max_help_position = 50)
)

parser.add_argument('-e', '--era',
  type = str, dest = 'era', metavar = 'year', required = True, choices = ERAS.keys(),
  help = 'R|Era',
)
parser.add_argument('-o', '--output',
  type = str, dest = 'output', metavar = 'file', required = True,
  help = 'R|Output directory',
)
parser.add_argument('-t', '--tmp-dir',
  type = str, dest = 'tmp_dir', metavar = 'directory', required = False, default = os.path.expanduser('~/puProduction'),
  help = 'R|Directory where intermediate output files are stored',
)
parser.add_argument('-v', '--verbose',
  dest = 'verbose', action = 'store_true', default = False,
  help = 'R|Enable verbose output',
)

args = parser.parse_args()

era = args.era
dbs = ERAS[era]['dbs']
cat = ERAS[era]['cat']

output = args.output
tmp_dir = os.path.join(args.tmp_dir, era, cat)

if args.verbose:
  logging.getLogger().setLevel(logging.DEBUG)

min_hours = 3
min_seconds = min_hours * 3600
timeleft_cmd = subprocess.Popen(['voms-proxy-info', '--timeleft'], stdout = subprocess.PIPE, stderr = subprocess.PIPE)
timeleft_out, timeleft_err = timeleft_cmd.communicate()
if timeleft_err:
  raise RuntimeError(timeleft_err)
timeleft_int = int(timeleft_out)
if min_seconds > timeleft_int:
  raise RuntimeError(
    'Proxy must be open at least %d seconds (or %d hours) but is currently open just %d seconds' % \
    (min_seconds, min_hours, timeleft_int)
  )

logging.debug('Querying DAS for input files')
filelist_cmd = subprocess.Popen(
  "dasgoclient -query='file dataset={} | grep file.name'".format(dbs),
  stdout = subprocess.PIPE,
  stderr = subprocess.PIPE,
  shell = True,
)
filelist_out, filelist_err = filelist_cmd.communicate()
if filelist_err:
  raise RuntimeError(filelist_err)
input_files = list(map(
  lambda filename: 'root://cms-xrd-global.cern.ch/{}'.format(filename),
  filelist_out.rstrip('\n').split('\n')
))
logging.debug('Found {} input files'.format(len(input_files)))

if not os.path.isdir(tmp_dir):
  logging.debug('Directory {} does not exist, creating it'.format(tmp_dir))
  os.makedirs(tmp_dir)

cfg_fn = '{}_cfg.txt'.format(cat)
cfg_path = os.path.join(tmp_dir, cfg_fn)
tmp_output = '{}.root'.format(os.path.join(tmp_dir, cat))
logging.debug('Creating cfg file: {}'.format(cfg_path))
with open(cfg_path, 'w') as f:
  f.write('\n'.join(input_files))
  f.write('\n\n{} {} {}'.format(era, cat, tmp_output))

logging.debug('Obtaining PU distribution')
producer_cmd = subprocess.Popen(
  'puHistogramProducer.sh {}'.format(cfg_fn),
  stdout = subprocess.PIPE, stderr = subprocess.PIPE, shell = True, cwd = tmp_dir
)
producer_out, producer_err = producer_cmd.communicate()

if not os.path.isfile(tmp_output):
  raise RuntimeError('Could not find temporary output file: %s' % tmp_output)

output_dir = os.path.dirname(output)
if not os.path.isdir(output_dir):
  logging.debug('Directory {} does not exist, creating it'.format(tmp_dir))
  os.makedirs(output_dir)

logging.debug('Copying from {} to {}'.format(tmp_output, output))
shutil.copy(tmp_output, output)
