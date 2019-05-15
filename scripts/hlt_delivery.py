#!/usr/bin/env python

# Example:
# hlt_delivery.py -i HLT_IsoMu24 HLT_IsoMu27 \
#   -j $CMSSW_BASE/src/tthAnalysis/NanoAOD/data/Cert_314472-325175_13TeV_17SeptEarlyReReco2018ABC_PromptEraD_Collisions18_JSON.txt \
#   -p $CMSSW_BASE/src/tthAnalysis/NanoAOD/test/datasets/txt/datasets_data_2016_17Jul18.txt -v
#
# Or, you can pass a file containing the list of HLT paths to option -i/--input
# Option -p/--prescale is optional (as is the option -j/--json, but it's strongly suggested)

from tthAnalysis.HiggsToTauTau.common import logging, SmartFormatter
from tthAnalysis.HiggsToTauTau.hltDelivery import run_brilcalc, LUMI_UNITS

import argparse
import os.path

if __name__ == '__main__':
  parser = argparse.ArgumentParser(
    formatter_class = lambda prog: SmartFormatter(prog, max_help_position = 55)
  )
  parser.add_argument('-i', '--input',
    type = str, dest = 'input', metavar = 'path', required = True, nargs = '+',
    help = 'R|Input HLT path or a file containing HLT paths',
  )
  parser.add_argument('-j', '--json',
    type = str, dest = 'json', metavar = 'path', required = False, default = '',
    help = 'R|Golden JSON',
  )
  parser.add_argument('-n', '--normtag',
    type = str, dest = 'normtag', metavar = 'path', required = False,
    default = os.path.expanduser('~/Normtags/normtag_PHYSICS.json'),
    help = 'R|Normtag',
  )
  parser.add_argument('-u', '--units',
    type = str, dest = 'units', metavar = 'unit', required = False, default = '/pb', choices = LUMI_UNITS,
    help = 'R|Units of integrated luminosity',
  )
  parser.add_argument('-b', '--brilcalc-path',
    type = str, dest = 'brilcalc_path', metavar = 'path', required = False,
    default = os.path.expanduser('~/brilconda/bin/brilcalc'),
    help = 'R|Location of brilcalc',
  )
  parser.add_argument('-p', '--prescale',
    type = str, dest = 'prescale', metavar = 'file', required = False, default = '',
    help = 'R|File containing run ranges and integrated luminosities per acquisition era and primary dataset type',
  )
  parser.add_argument('-o', '--output',
    type = str, dest = 'output', metavar = 'directory', required = False, default = '',
    help = 'R|Directory for the output of brilcalc commands',
  )
  parser.add_argument('-v', '--verbose',
    dest = 'verbose', action = 'store_true', default = False, required = False,
    help = 'R|Verbose output',
  )
  args = parser.parse_args()

  if args.verbose:
    logging.getLogger().setLevel(logging.DEBUG)

  hlt_paths = []
  for input_arg in args.input:
    if input_arg.startswith('HLT'):
      hlt_paths.append(input_arg)
    else:
      if not os.path.isfile(input_arg):
        raise ValueError("No such file: %s" % input_arg)
      with open(input_arg, 'r') as input_file:
        for line in input_file:
          line_stripped = line.rstrip('\n')
          if not line_stripped:
            # empty line
            continue
          if not line_stripped.startswith('HLT'):
            raise RuntimeError("Invalid HLT path: %s" % line_stripped)
          hlt_paths.append(line_stripped)

  run_brilcalc(hlt_paths, args.json, args.normtag, args.units, args.brilcalc_path, args.prescale, args.output)
