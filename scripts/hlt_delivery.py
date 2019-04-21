#!/usr/bin/env python

from tthAnalysis.HiggsToTauTau.common import logging, SmartFormatter
from tthAnalysis.HiggsToTauTau.hltDelivery import run_brilcalc

import argparse
import os.path

LUMI_UNITS = [ '/fb', '/pb', '/nb', '/ub' ]

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
  parser.add_argument('-v', '--verbose',
    dest = 'verbose', action = 'store_true', default = False, required = False,
    help = 'R|Verbose output',
  )
  args = parser.parse_args()

  if args.verbose:
    logging.getLogger().setLevel(logging.DEBUG)

  run_brilcalc(args.input, args.json, args.normtag, args.units, args.brilcalc_path)
