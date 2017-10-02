from tthAnalyzeSamples_2016 import samples_2016 as s
import os.path

prod_rles_path = "/hdfs/local/karl/ttHAnalysis/2016/2017Sep26/output_rle/1l_2tau/Tight_OS"
orig_rles_path = "/hdfs/local/karl/ttHAnalysis/2016/2017Sep27/output_rle/1l_2tau/Tight_OS"

def get_rles(dname):
  rles = []
  for rle_file in os.listdir(dname):
    if rle_file.endswith('.txt'):
      rle_file_path = os.path.join(dname, rle_file)
      with open(rle_file_path, 'r') as f:
        for line in f:
          line = line.rstrip('\n')
          if line:
            rles.append(line)
  return rles

prod_cat = {}
orig_cat = {}

for k, v in s.items():
  if not v['use_it'] or v['sample_category'] == 'additional_signal_overlap':
    continue
  pns = v['process_name_specific']
  cat = v['sample_category']
  if cat not in prod_cat:
    prod_cat[cat] = 0
  if cat not in orig_cat:
    orig_cat[cat] = 0

  prod_dir = os.path.join(prod_rles_path, pns)
  orig_dir = os.path.join(orig_rles_path, pns)
  for d in [prod_dir, orig_dir]:
    if not os.path.isdir(d):
      raise ValueError("Directory %s does not exist" % d)

  prod_rles = set(get_rles(prod_dir))
  orig_rles = set(get_rles(orig_dir))

  common_rles = list(prod_rles & orig_rles)
  only_in_prod = list(prod_rles - orig_rles)
  only_in_orig = list(orig_rles - prod_rles)

  prod_cat[cat] += len(common_rles) + len(only_in_prod)
  orig_cat[cat] += len(common_rles) + len(only_in_orig)

  print(pns)
  print("Common: %i" % len(common_rles))
  print("Only in prod: %i" % len(only_in_prod))
  if only_in_prod:
    print('\n'.join(only_in_prod))
  print("Only in orig: %i" % len(only_in_orig))
  if only_in_orig:
    print('\n'.join(only_in_orig))
  print("-" * 80)

for k in prod_cat:
  print(' '.join(map(str, [k, prod_cat[k], orig_cat[k]])))

