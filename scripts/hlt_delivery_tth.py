#!/usr/bin/env python

from tthAnalysis.HiggsToTauTau.common import logging, SmartFormatter
from tthAnalysis.HiggsToTauTau.hltDelivery import run_brilcalc, LUMI_UNITS
from tthAnalysis.HiggsToTauTau.analysisSettings import Triggers

import argparse
import os

ERA_CHOICES   = [ "2016", "2017", "2018" ]
TRIGGER_TYPES = [ "analysis", "leptonFR" ]

BASEDIR = os.path.join(os.environ["CMSSW_BASE"], "src", "tthAnalysis", "NanoAOD")
JSONS = {
  "2016" : os.path.join(BASEDIR, "data", "Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt"),
  "2017" : os.path.join(BASEDIR, "data", "Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON_v1.txt"),
  "2018" : os.path.join(BASEDIR, "data", "Cert_314472-325175_13TeV_17SeptEarlyReReco2018ABC_PromptEraD_Collisions18_JSON.txt"),
}
DATA_TABLES = {
  "2016" : os.path.join(BASEDIR, "test", "datasets", "txt", "datasets_data_2016_17Jul18.txt"),
  "2017" : os.path.join(BASEDIR, "test", "datasets", "txt", "datasets_data_2017_31Mar18.txt"),
  "2018" : os.path.join(BASEDIR, "test", "datasets", "txt", "datasets_data_2018_17Sep18.txt"),
}

if __name__ == '__main__':

  parser = argparse.ArgumentParser(
    formatter_class = lambda prog: SmartFormatter(prog, max_help_position = 55)
  )
  parser.add_argument('-e', '--era',
    type = str, dest = 'era', metavar = 'year', required = True, nargs = '+', choices = ERA_CHOICES,
    default = ERA_CHOICES,
    help = 'R|Era',
  )
  parser.add_argument('-t', '--trigger-type',
    type = str, dest = 'trigger_type', metavar = 'type', required = False, nargs = '+', choices = TRIGGER_TYPES,
    default = TRIGGER_TYPES,
    help = 'R|Type of triggers to consider',
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

  for era in args.era:
    triggers_attr = ""
    assert (0 < len(args.trigger_type) < 3)
    if len(args.trigger_type) == 2:
      triggers_attr = "triggers_flat"
    else:
      triggers_attr = "triggers_{}".format(args.trigger_type[0])
    assert(triggers_attr)

    triggers = Triggers(era)
    hlt_paths = getattr(triggers, triggers_attr)

    run_brilcalc(hlt_paths, JSONS[era], args.normtag, args.units, args.brilcalc_path, DATA_TABLES[era], args.output)
