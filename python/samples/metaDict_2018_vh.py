from tthAnalysis.HiggsToTauTau.samples.metaDict_2018_mc import meta_dictionary as meta_dictionary_mc
from tthAnalysis.HiggsToTauTau.analysisSettings import VH_keys

import copy
import re

meta_dictionary = copy.deepcopy(meta_dictionary_mc)
dbs_to_delete = []
dbs_to_keep = []
for dbs_name, dbs_info in meta_dictionary.items():
  if not dbs_info["process_name_specific"].startswith("VH"):
    dbs_to_delete.append(dbs_name)
  else:
    dbs_to_keep.append(dbs_name)

for dbs_name in dbs_to_delete:
  del meta_dictionary[dbs_name]

for dbs_name in dbs_to_keep:
  for vh_key in VH_keys:
    dbs_copy = copy.deepcopy(meta_dictionary[dbs_name])
    dbs_name_new = re.sub('^/VH', '/{}'.format(vh_key), dbs_name)
    assert(dbs_name != dbs_name_new)
    dbs_copy["xsection"] *= VH_keys[vh_key]
    dbs_copy["process_name_specific"] = re.sub("^VH", vh_key, dbs_copy["process_name_specific"])
    dbs_copy["crab_string"] = ""
    assert(dbs_name_new not in meta_dictionary)
    meta_dictionary[dbs_name_new] = dbs_copy
  del meta_dictionary[dbs_name]
