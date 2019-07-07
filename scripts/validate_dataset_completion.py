#!/usr/bin/env python

from tthAnalysis.HiggsToTauTau.common import load_samples, SmartFormatter

import argparse

def validate(samples):
  for dbs_name, sample_info in samples.items():
    if dbs_name == 'sum_events':
      continue
    if sample_info["type"] != "mc":
      continue
    if sample_info["nof_tree_events"] != sample_info["nof_db_events"]:
      missing_events = sample_info["nof_db_events"] - sample_info["nof_tree_events"]
      assert(missing_events > 0)
      print("{} {} ({:.1f}%)".format(dbs_name, missing_events, missing_events * 100. / sample_info["nof_db_events"]))

if __name__ == '__main__':
  parser = argparse.ArgumentParser(
    formatter_class = lambda prog: SmartFormatter(prog, max_help_position = 55)
  )
  parser.add_argument('-e', '--era',
    type = str, dest = 'era', metavar = 'year', required = True, choices = [ '2016', '2017', '2018' ],
    help = 'R|Era',
  )
  parser.add_argument('-p', '--postproc',
    dest = 'postproc', action = 'store_true', default = False, required = False,
    help = 'R|Validate sample dictionary for post-processed Ntuples',
  )
  parser.add_argument('-b', '--base',
    type = str, dest = 'base', metavar = 'string', required = False, choices = [ 'tth', 'hh_multilepton', 'hh_bbww' ],
    default = 'tth',
    help = 'R|Choice of analysis',
  )
  parser.add_argument('-s', '--suffix',
    type = str, dest = 'suffix', metavar = 'string', required = False, default = '',
    help = 'R|Suffix in the name of sample dictionary',
  )
  args = parser.parse_args()

  samples = load_samples(era = args.era, is_postproc = args.postproc, base = args.base, suffix = args.suffix)
  validate(samples)
