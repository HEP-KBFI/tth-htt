#!/usr/bin/env python

from tthAnalysis.HiggsToTauTau.common import SmartFormatter
from tthAnalysis.HiggsToTauTau.jobTools import human_size

import argparse
import importlib
import collections
import prettytable

if __name__ == '__main__':
  parser = argparse.ArgumentParser(
    formatter_class = lambda prog: SmartFormatter(prog, max_help_position = 55)
  )
  parser.add_argument('-e', '--era',
    type = str, dest = 'era', metavar = 'year', required = True, choices = [ '2016', '2017', '2018' ],
    help = 'R|Era',
  )
  args = parser.parse_args()

  sample_module = importlib.import_module('tthAnalysis.HiggsToTauTau.samples.metaDict_{}'.format(args.era))
  meta = getattr(sample_module, 'meta_dictionary')

  categories = collections.OrderedDict()
  for dbs_name, sample_info in meta.items():
    category = sample_info['sample_category']
    if category not in categories:
      categories[category] = { 'expected' : 0, 'completed' : 0 }
    categories[category]['expected'] += sample_info['nof_db_events']
    completion_percentage = 0.
    comment_first = sample_info['comment'].split(';')[0]
    if '%' in comment_first:
      completion_percentage = float(comment_first.replace('%', '')) / 100
    categories[category]['completed'] += int(completion_percentage * sample_info['nof_db_events'])

  header = [ 'Category', 'Expected', 'Completed (%)' ]
  table = prettytable.PrettyTable(header)

  for category, results in categories.items():
    row = [
      category,
      human_size(results['expected'], byte_suffix = ''),
      '%s (%.2f%%)' % (human_size(results['completed'], byte_suffix = ''), 100. * results['completed'] / results['expected']),
    ]
    table.add_row(row)
  print(table)
