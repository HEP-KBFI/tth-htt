import os, sys
from tthAnalysis.HiggsToTauTau.tthAnalyzeSamples_2los_1tau import samples

def generate_input_list(job_ids, secondary_files, primary_store, secondary_store, debug = False):
  input_list = []
  for job in job_ids:
    input_file = ""
    subdir = "000" + str(job / 1000)
    if job in secondary_files:
      input_file = os.path.join(secondary_store, subdir, "tree_" + str(job) + ".root")
    else:
      input_file = os.path.join(primary_store, subdir, "tree_" + str(job) + ".root")
    if debug:
      if not os.path.exists(input_file):
        raise ValueError("File %s doesn't exists!\n" % input_file)
    input_list.append(input_file)
  return input_list

def get_process_list():
  process_list = [v["process_name_specific"] for k, v in samples.iteritems()]
  return process_list

def get_sample(process_name):
  for k, v in samples.iteritems():
    if v["process_name_specific"].lower() == process_name.lower():
      return v
  return None

def get_filelist(process_name, debug = False):
  v = get_sample(process_name)
  if v is None: raise ValueError("No such sample w/ process name: %s" % process_name)

  nof_files = v["nof_files"]
  store_dirs = v["local_paths"]
  assert(len(store_dirs) <= 2), "There is more than one secondary dir!"
  primary_store, secondary_store = "", ""
  secondary_files = []
  for store_dir in store_dirs:
    if store_dir["selection"] == "*": primary_store = store_dir["path"]
    else:
      secondary_store = store_dir["path"]
      secondary_files = map(lambda x: int(x), store_dir["selection"].split(","))
  job_ids = range(1, nof_files)
  filelist = generate_input_list(job_ids, secondary_files,
                                  primary_store, secondary_store, debug)
  return filelist

if __name__ == '__main__':

  # examples

  TT_ext3 = get_filelist('TT_TuneCUETP8M1_ext3')
  for f in TT_ext3: print(f)
  print(get_process_list())
