#!/usr/bin/env python
import argparse, os, sys, logging, imp

def load_dict(path, name):
  if not os.path.isfile(path):
    logging.error("No such dictionary file: {dict_path}".format(dict_path = path))
    sys.exit(1)
  imp_dict = imp.load_source('', path)
  if not hasattr(imp_dict, name):
    logging.error("No such dictionary in the file '{dict_path}': {dict_name}".format(
      dict_path = path, dict_name = name,
    ))
    sys.exit(1)
  samples = getattr(imp_dict, name)
  return samples

if __name__ == '__main__':
  logging.basicConfig(
    stream = sys.stdout,
    level  = logging.INFO,
    format = '%(asctime)s - %(levelname)s: %(message)s'
  )
  class SmartFormatter(argparse.HelpFormatter):
    def _split_lines(self, text, width):
      if text.startswith('R|'):
        return text[2:].splitlines()
      return argparse.HelpFormatter._split_lines(self, text, width)

  parser = argparse.ArgumentParser(formatter_class = lambda prog: SmartFormatter(prog, max_help_position = 35))
  parser.add_argument('-d', '--dictionary-1', dest = 'dictionary_1', metavar = 'file', required = True, type = str,
                      help = 'R|Path to the reference dictionary')
  parser.add_argument('-D', '--dictionary-2', dest = 'dictionary_2', metavar = 'file', required = True, type = str,
                      help = 'R|Path to the test dictionary')
  parser.add_argument('-n', '--dict_name', dest = 'dict_name', metavar = 'name', required = True, type = str,
                      help = 'R|Name of the dictionary (specified by -D), e.g. samples_2016')
  parser.add_argument('-v', '--verbose', dest = 'verbose', action = 'store_true', default = False,
                      help = 'R|Enable verbose printout')
  args = parser.parse_args()

  dictionary_1 = args.dictionary_1
  dictionary_2 = args.dictionary_2
  dict_name    = args.dict_name
  verbose      = args.verbose

  if verbose:
    logging.getLogger().setLevel(logging.DEBUG)

  # load the dictionaries
  ref_dict  = load_dict(dictionary_1, dict_name)
  test_dict = load_dict(dictionary_2, dict_name)

  logging.debug('Reference dictionary is: %s::%s' % (dictionary_1, dict_name))
  logging.debug('Test      dictionary is: %s::%s' % (dictionary_2, dict_name))

  # compare dictionary keys
  ref_keys  = ref_dict.keys()
  test_keys = test_dict.keys()
  missing_keys  = set(ref_keys) - set(test_keys)
  overflow_keys = set(test_keys) - set(ref_keys)
  common_keys   = set(ref_keys) & set(test_keys)
  logging.info('There are %d missing  keys: %s' % (len(missing_keys),  ','.join(missing_keys)))
  logging.info('There are %d overflow keys: %s' % (len(overflow_keys), ','.join(overflow_keys)))
  logging.info('There are %d common   keys' % len(common_keys))

  endtree = lambda x: os.sep.join(x.split(os.sep)[-3:])
  funcmap = {
    'process_name_specific' : (lambda d: d['process_name_specific']),
    'nof_files'             : (lambda d: d['nof_files']),
    'nof_events'            : (lambda d: d['nof_events']),
    'nof_tree_events'       : (lambda d: d['nof_tree_events']),
    'nof_db_events'         : (lambda d: d['nof_db_events']),
    'path'                  : (lambda d: endtree(d['local_paths'][0]['path'])),
    'blacklist'             : (lambda d: d['local_paths'][0]['blacklist'] if 'blacklist' in d['local_paths'][0] else []),
    'selection'             : (lambda d: d['local_paths'][0]['selection']),
    'selection2'            : (lambda d: d['local_paths'][1]['selection'] if len(d['local_paths']) > 1 else True),
    'use_it'                : (lambda d: d['use_it']),
    'xsection'              : (lambda d: d['xsection'] if 'xsection' in d else True),
    'triggers'              : (lambda d: list(sorted(d['triggers']))),
    'genWeight'             : (lambda d: d['genWeight'] if 'genWeight' in d else True),
  }

  # loop over common keys
  dictmap = {}
  for dict_probe, name in zip([ref_dict, test_dict], ['ref', 'test']):
    dictmap[name] = {}
    for func_key, func in funcmap.iteritems():
      dictmap[name][func_key] = {}
      for key in common_keys:
        dictmap[name][func_key][key] = func(dict_probe[key])

  diffs = { key : [k for k, v in dictmap['ref'][key].iteritems() if dictmap['test'][key][k] != v ] for key in funcmap.keys()}
  for key, vals in diffs.iteritems():
    if vals:
      logging.warning('There are differences in %s' % key)
      for val in vals:
        ref_val  = str(dictmap['ref'][key][val])
        test_val = str(dictmap['test'][key][val])
        ref_name  = dictmap['ref']['process_name_specific'][val]
        test_name = dictmap['test']['process_name_specific'][val]
        logging.warning('%s in reference dictionary: %s [%s]' % (key, ref_val, ref_name))
        logging.warning('%s in test      dictionary: %s [%s]' % (key, test_val, test_name))

