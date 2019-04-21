from tthAnalysis.HiggsToTauTau.jobTools import run_cmd
from tthAnalysis.HiggsToTauTau.common import logging

import os.path
import re
import multiprocessing
import signal
import sys

HLT_SUFFIX = re.compile(r'(.*_v\*$)|(.*_v[0-9]+)$')

def hlt_version(hlt_path):
  if not HLT_SUFFIX.match(hlt_path):
    new_hlt_path = '{}_v*'.format(hlt_path)
    logging.debug("Changing {} to {} in brilcalc queries".format(hlt_path, new_hlt_path))
    return new_hlt_path
  else:
    return hlt_path

def process_hlt(hlt_path, golden_json, brilcalc_path, normtag, units):
  brilcalc_cmd = '{brilcalc_path} lumi -c web {json} {normtag} --output-style csv --hltpath "{hlt_path}" -u {units}'.format(
    brilcalc_path = brilcalc_path,
    json          = ('-i {}'.format(golden_json)    if golden_json else ''),
    normtag       = ('--normtag {}'.format(normtag) if normtag     else ''),
    hlt_path      = hlt_path,
    units         = units,
  )
  logging.debug("Running: {}".format(brilcalc_cmd))
  brilcalc_out, brilcalc_err = run_cmd(brilcalc_cmd, do_not_log = True, return_stderr = True)
  if brilcalc_err:
    raise ValueError("brilcalc return an error: %s" % brilcalc_err)
  logging.debug("Parsing results for {}".format(hlt_path))
  brilcalc_out_split = brilcalc_out.rstrip('\n').split('\n')
  brilcalc_out_split = list(map(lambda line: line.rstrip('\r'), brilcalc_out_split))

  read_runs = 0
  delivered, recorded = 0., 0.
  runs = []
  hlt_paths = []
  for line in brilcalc_out_split:
    if line.startswith("#run:fill,time,ncms,hltpath"):
      if read_runs == 0:
        read_runs = 1
    elif line.startswith("#Summary:"):
      read_runs = -1
    elif line.startswith("#HLT_"):
      line_split = line.replace('#', '').split(',')
      hlt_paths.append({
        'hltpath'      : line_split[0],
        'nfill'        : int(line_split[1]),
        'nrun'         : int(line_split[2]),
        'ncms'         : int(line_split[3]),
        'totdelivered' : float(line_split[4]),
        'totrecorded'  : float(line_split[5]),
      })
    elif line.startswith("#Sum delivered"):
      delivered = float(line.split()[-1])
    elif line.startswith("#Sum recorded"):
      recorded = float(line.split()[-1])
    else:
      if read_runs > 0:
        runs.append(int(line.split(':')[0]))
      else:
        pass

  dict_entry = {
    'runs' : runs,
    'delivered' : delivered,
    'recorded'  : recorded,
    'paths'     : hlt_paths,
  }
  return hlt_path, dict_entry

trigger_results = {}

def get_trigger_results(results):
  trigger_results[results[0]] = results[1]

def run_brilcalc(inputs_arg, json, normtag, units, brilcalc_path):
  for input_file in (json, normtag):
    if input_file and not os.path.isfile(input_file):
      raise ValueError("No such file: %s" % input_file)
  if not os.path.isfile(brilcalc_path):
    raise ValueError("No such file: %s" % brilcalc_path)

  hlt_paths = []
  for input_arg in inputs_arg:
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
  assert(all(map(lambda hlt_path: hlt_path.startswith('HLT'), hlt_paths)))
  hlt_paths = { hlt_path : hlt_version(hlt_path) for hlt_path in hlt_paths }

  # prepare the jobs
  original_sigint_handler = signal.signal(signal.SIGINT, signal.SIG_IGN)
  pool_size = 12
  pool = lumi_pool = multiprocessing.Pool(pool_size)
  signal.signal(signal.SIGINT, original_sigint_handler)

  logging.debug("Constructing pool for {} HLT paths".format(len(hlt_paths)))
  for hlt_path in hlt_paths:
    try:
      pool.apply_async(
        process_hlt,
        args     = (hlt_paths[hlt_path], json, brilcalc_path, normtag, units),
        callback = get_trigger_results,
      )
    except KeyboardInterrupt:
      lumi_pool.terminate()
      sys.exit(1)

  pool.close()
  pool.join()
  logging.debug("Pool finished")

  # parse trigger_results
  for hlt_path in hlt_paths:
    dict_entry = trigger_results[hlt_paths[hlt_path]]
    print("HLT path: {} nrun = {} totdelivered = {} totrecorded = {} (units = {})".format(
      hlt_path, len(dict_entry['runs']), dict_entry['delivered'], dict_entry['recorded'], units,
    ))
    for hlt_dict in dict_entry['paths']:
      print("\t{} nfill = {} nrun = {} ncms = {} totdelivered = {} totrecorded = {}".format(
        hlt_dict['hltpath'], hlt_dict['nfill'], hlt_dict['nrun'], hlt_dict['ncms'], hlt_dict['totdelivered'],
        hlt_dict['totrecorded'],
      ))

  # end