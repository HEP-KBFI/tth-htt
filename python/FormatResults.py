from TTH13TeVsamples import Samples, RESULTS_DIR, LUMI
import codecs, logging, os, sys, itertools, collections, copy

"""This script generates a nice cutflow table from the output of SynchTTH program.
   Execute the script in the same folder where you have "results" directory
   (i.e. where you executed RunCuts.py). The output is stored in the current directory
   where you executed this script (i.e. parent of "results").
   
   Input: results/<sample key>/table.txt
   Output: cutflow.txt (overwriting enabled) 
   
   Hopefully, nobody has to debug it b/c it's super messy.
"""

def print_cuts(_rows, col_width, xsection = False):
  rows = copy.deepcopy(_rows)
  res = ""
  
  for c in rows:
    fmt = "-- %s -- %s\n\n"
    if xsection:
      res += fmt % (c, "10/fb")
    else:
      res += fmt % (c, "Raw MC")
    for r in rows[c]:
      s = rows[c][r][0].rjust(col_width)
      if r == 0:
        rows[c][r] = rows[c][r] + ["ALL BKG"]
      else:
        if xsection:
          new_row = [rows[c][r][0]]
          for i in xrange(len(rows[c][r][1:])):
            weight = Samples[rows[c][0][i + 1]]["x_section"] * LUMI / \
                     Samples[rows[c][0][i + 1]]["nof_events"]
            new_row.append(weight * rows[c][r][1:][i])
          rows[c][r] = new_row
        rows[c][r] = rows[c][r] + [sum(rows[c][r][2:])]
      for i in xrange(1, len(rows[c][r])):
        val = rows[c][r][i]
        if r > 0:
          perc = 100.0
          if r > 1 and rows[c][r - 1][i] > 0:
            prev = rows[c][r - 1][i]
            perc = 100 * (1 - float(prev - val) / prev)
          if xsection:
            val = "{0:.3f}".format(round(val,3))
          else:
            val = str(val)
          val += (" {0:.2f}".format(round(perc,2)) + "%").rjust(10)
        else:
          val = str(val).replace("_", "+") + "".join([" " for x in xrange(7)])
        s += "".join(val.rjust(24))
      res += s + "\n"
      if r == 0: res += "\n"
    res += "\n\n"
  
  return res

if __name__ == '__main__':
  logging.basicConfig(stream=sys.stdout,
                      level=logging.INFO,
                      format='%(asctime)s - %(levelname)s: %(message)s')
  
  samples = Samples.keys()
  
  results_file = "table.txt"
  cutflow_file = "cutflow.txt"
  
  cuts = collections.OrderedDict()
  cut_labels = collections.OrderedDict()
  
  for s in samples:
    rf_path = os.path.join(RESULTS_DIR, s, results_file)
    if not os.path.isfile(rf_path):
      logging.error("The file %s doesn't exists. Aborting")
      sys.exit(1)
    with codecs.open(rf_path, 'r', 'utf-8') as f:
      logging.info("Opened %s" % rf_path)
      for l1, l2 in itertools.izip_longest(*[f]*2):
        l2 = l2.rstrip("\n") # <channel name>;n1;n2;n3;n4;...
        l1 = l1.rstrip("\n") # channel;entry point;preselection;cut1;cut2;...
        numbers = l2.split(";")
        labels = l1.split(";")
        if len(numbers) != len(labels):
          logging.error("Something's fishy ..."
                        "The number of results in %s sample "
                        "doesn't match the number of labels." % s)
          sys.exit(1)
        
        # this corresponds to channel <-> channel name entry
        # e.g. "channel <-> 3l" or "channel <-> mumu"
        channel_label = numbers[0]
        if channel_label not in cuts:
          cuts[channel_label] = collections.OrderedDict()
        
        if channel_label not in cut_labels:
          cut_labels[channel_label] = labels[1:]
        else:
          if cut_labels[channel_label] != labels[1:]:
            logging.error("Something's fishy ..."
                          "The cuts for one sample/channel combo doesn't match "
                          "with the other sample/channel combo.")
            logging.error("The combinations is %s/%s" % (s, channel_label))
            sys.exit(1)
        
        cuts[channel_label][s] = [int(x) for x in numbers[1:]]
  
  rows = collections.OrderedDict()
  col_width = 0
  for c in cuts:
    if c not in rows:
      rows[c] = {}
    for x in xrange(len(cut_labels[c])):
      rows[c][x + 1] = [cut_labels[c][x]]
      col_width = max(col_width, len(cut_labels[c][x]))
    rows[c][0] = ["cut"]
    for k in cuts[c]:
      rows[c][0].append(k)
      for j in range(len(cuts[c][k])):
        rows[c][j + 1].append(cuts[c][k][j])
  
  raw_mc = print_cuts(rows, col_width, xsection = False)
  xsect = print_cuts(rows, col_width, xsection = True)
  
  with codecs.open(cutflow_file, 'w', 'utf-8') as f:
    logging.info("Wrote reformatted event counts to %s" % cutflow_file)
    f.write(raw_mc)
    f.write(xsect)
  