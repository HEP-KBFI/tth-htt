from ComparisonResults import cg, nd
from TTH13TeVsamples import Samples, RESULTS_DIR, LUMI
import codecs, os, logging, sys, itertools, collections

"""Finds relative (expressed in percentages) and absolute differences
   in our cutflow table and the tables produced by other groups.
   The differences are found after the very last cut of each channel-sample combo.
   
   Input: cutflow.txt
   Output: diff.txt
"""

def add_all_bkg(d, samples):
  for kk, kv in d.iteritems():
    for sk, sv in kv.iteritems():
      tmp = []
      for x in sv.items()[1:]:
        if x[0] in samples:
          tmp.append(x[1])
      sv["ALL BKG"] = sum(tmp)

if __name__ == '__main__':
  logging.basicConfig(stream=sys.stdout,
                      level=logging.INFO,
                      format='%(asctime)s - %(levelname)s: %(message)s')
  
  samples = Samples.keys()
  
  diff_file = "diff.txt"
  
  results = {}
  results["Nevents"] = collections.OrderedDict()
  results["weighted"] = collections.OrderedDict()
  channels = ["ee", "mumu", "emu", "3l", "4l"]
  
  for s in samples:
    results_file = os.path.join(RESULTS_DIR, s, "table.txt")
    if not os.path.exists(results_file):
      logging.error("No such file: %s" % results_file)
    with codecs.open(results_file, 'r', 'utf-8') as f:
      logging.info("Opened %s" % results_file)
      for l1, l2 in itertools.izip_longest(*[f]*2):
        # neglect l1
        l2 = l2.rstrip("\n").split(";")
        channel = l2[0]
        if channel not in channels: continue
        final_cut = int(l2[-1])
        
        if channel not in results["Nevents"]:
          results["Nevents"][channel] = collections.OrderedDict()
        results["Nevents"][channel][s] = final_cut
        
        if channel not in results["weighted"]:
          results["weighted"][channel] = collections.OrderedDict()
        weight = Samples[s]["x_section"] * LUMI / Samples[s]["nof_events"]
        results["weighted"][channel][s] = final_cut * weight
  
  add_all_bkg(results, samples)
  add_all_bkg(nd, samples)
  add_all_bkg(cg, samples)
  group_str = {"cg" : "CERN group", "nd" : "Notre-Dame"}
  
  diffs = {}
  for group in ["cg", "nd"]:
    for err_type in ["dif", "rel"]:
      diff_key = group + "_" + err_type
      diffs[diff_key] = collections.OrderedDict()
      
      for result_type in ["Nevents", "weighted"]:
        diffs[diff_key][result_type] = collections.OrderedDict()
        
        for channel in results[result_type]:
          diffs[diff_key][result_type][channel] = collections.OrderedDict()
          
          for sample in results[result_type][channel]:
            expected = cg[result_type][channel][sample] if group == "cg" else \
                       nd[result_type][channel][sample]
            calc = results[result_type][channel][sample]
            err = calc - expected
            
            if err_type == "rel":
              if expected == 0:
                if err != 0:
                  err = "NaN"
              else:
                err /= float(expected)
                err *= 100
            if not isinstance(err, str):
              err = "{0:.3f}".format(round(err,3))
            if err_type == "rel":
              err += " %"
            diffs[diff_key][result_type][channel][sample] = err
  
  samples += ["ALL BKG"]
  rjust_val = 15
  samples_header = "".join([s.replace("_", "+").rjust(rjust_val) for s in samples])
  printout = collections.OrderedDict()
  for channel in channels:
    printout[channel] = ""
    for result_type in ["Nevents", "weighted"]:
      printout[channel] += result_type.rjust(rjust_val)
      if result_type != "weighted":
        printout[channel] += samples_header
      printout[channel] += "\n"
      for err_type in ["dif", "rel"]:
        for group in ["cg", "nd"]:
          diff_key = group + "_" + err_type
          diff_key_str = group_str[group] + " " + err_type
          printout[channel] += diff_key_str.rjust(rjust_val)
          vals = []
          for x, y in diffs[diff_key][result_type][channel].iteritems():
            if x in samples:
              vals.append(y)
          printout[channel] += "".join(v.rjust(rjust_val) for v in vals)
          printout[channel] += "\n"
      printout[channel] += "\n"
  
  with codecs.open(diff_file, 'w', 'utf-8') as f:
    for channel in printout:
      f.write(channel + "\n")
      f.write(printout[channel] + "\n")
  