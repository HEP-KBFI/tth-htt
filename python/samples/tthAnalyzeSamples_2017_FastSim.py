from tthAnalyzeSamples_2017 import samples_2017

for sample_name, sample_info in samples_2017.items():
  if sample_info["process_name_specific"].find("_fastsim_") != -1:
    sample_info["use_it"] = True
  else:
    sample_info["use_it"] = False