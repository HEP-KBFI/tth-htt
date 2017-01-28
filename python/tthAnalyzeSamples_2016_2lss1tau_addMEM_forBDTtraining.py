from tthAnalysis.HiggsToTauTau.tthAnalyzeSamples_2016_2lss1tau_prodNtuples_forBDTtraining import samples_2016 as production_samples_2016
from collections import OrderedDict as OD
import copy, os

samples_2016 = copy.deepcopy(production_samples_2016)
sample_root_path = "/hdfs/local/karl/addMEM/2016/2017Jan26_dR03mvaVVLoose/final_ntuples/2lss_1tau/"

for sample_dasname, sample_dict in samples_2016.iteritems():
  sample_dict["nof_files"] = 1
  sample_dict["local_paths"] = [OD([
    ("path", os.path.join(sample_root_path, sample_dict["process_name_specific"])),
    ("selection", "*"),
    ("blacklist", []),
  ])]
