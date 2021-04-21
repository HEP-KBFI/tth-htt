#!/usr/bin/env python

import matplotlib
matplotlib.use('Agg')

import ROOT
import sys
import os.path
import collections
import matplotlib.pyplot as plt
import matplotlib.backends.backend_pdf as pdf

plt.rc('font', size = 14)

PROCESSES = collections.OrderedDict([
  ('WGamma' ,  { 'option' : 'selected', 'label' : r'W+$\gamma$'        }),
  ('WJets',    { 'option' : 'rejected', 'label' : 'W+jets'             }),
  ('ZGamma' ,  { 'option' : 'selected', 'label' : r'Z+$\gamma$'        }),
  ('ZJets',    { 'option' : 'rejected', 'label' : 'Z+jets'             }),
  ('TGamma' ,  { 'option' : 'selected', 'label' : r't+$\gamma$'        }),
  ('TJets',    { 'option' : 'rejected', 'label' : 't+jets'             }),
  ('TTGamma' , { 'option' : 'selected', 'label' : r'$t\bar{t}+\gamma$' }),
  ('TTJets',   { 'option' : 'rejected', 'label' : r'$t\bar{t}$+jets'   }),
])
SELECTIONS = [ 'selected', 'rejected' ]
LEPTONS = [ 'lepton', 'electron', 'muon' ]
SUM_KEY = 'sum'
PLOT_XMIN = 10.

def read_hist(fptr, process, selection, lepton_type):
  assert(selection in SELECTIONS)
  assert(lepton_type in LEPTONS)
  path = os.path.join('genPhotonFilter', selection, process, 'subleading_{}_pt'.format(lepton_type))
  hist = fptr.Get(path)
  assert(hist)
  nof_bins = hist.GetXaxis().GetNbins()
  xvals = [ hist.GetBinCenter(bin_idx) for bin_idx in range(1, nof_bins + 1) ]
  yvals = [ hist.GetBinContent(bin_idx) for bin_idx in range(1, nof_bins + 1) ]
  yvals = [ yvals[bin_idx] for bin_idx in range(nof_bins) if xvals[bin_idx] >= PLOT_XMIN ]
  xvals = [ xval for xval in xvals if xval >= PLOT_XMIN ]
  return { 'xval' : xvals, 'yval' : yvals }

def read_process(fptr, process):
  result = {}
  for lepton_type in LEPTONS:
    result[lepton_type] = {}
    for selection in SELECTIONS:
      result[lepton_type][selection] = read_hist(fptr, process, selection, lepton_type)
    binning = result[lepton_type][SELECTIONS[0]]['xval']
    assert(all(result[lepton_type][selection]['xval'] == binning for selection in SELECTIONS))
    nof_bins = len(binning)
    assert(SUM_KEY not in result[lepton_type])
    result[lepton_type][SUM_KEY] = {
      'xval' : binning,
      'yval' : [ sum(result[lepton_type][selection]['yval'][bin_idx] for selection in SELECTIONS) for bin_idx in range(nof_bins) ],
    }
  return result

assert(len(sys.argv) == 3)
fn = sys.argv[1]
outfn = sys.argv[2]
assert(os.path.isfile(fn))
assert(outfn.endswith('.pdf'))
f = ROOT.TFile.Open(fn, 'read')

histograms = collections.OrderedDict()
for process in PROCESSES:
  assert(process not in histograms)
  histograms[process] = read_process(f, process)
f.Close()

with pdf.PdfPages(outfn) as output:
  for process in PROCESSES:
    for lepton_type in LEPTONS:
      plt.figure(figsize = (10, 8), dpi = 150)

      plot_xmin = min(histograms[process][lepton_type][SUM_KEY]['xval'])
      plot_xmax = max(histograms[process][lepton_type][SUM_KEY]['xval'])
      option = PROCESSES[process]['option']
      label = PROCESSES[process]['label']
      plt.step(
        histograms[process][lepton_type][option]['xval'],
        histograms[process][lepton_type][option]['yval'],
        lw = 2, linestyle = '-', label = '{}, after {} by veto'.format(label, option.replace('selected', 'accepted')),
      )
      plt.step(
        histograms[process][lepton_type][SUM_KEY]['xval'],
        histograms[process][lepton_type][SUM_KEY]['yval'],
        lw = 2, linestyle = '--', label = r'{}, inclusive'.format(label),
      )
      plt.xlabel(r'Subleading {} $p_T$ [GeV]'.format(lepton_type))
      plt.ylabel('Weighted number of events')
      plt.grid(True)
      plt.xlim(plot_xmin, plot_xmax)
      plt.legend(loc = 'upper right')
      output.savefig(bbox_inches = 'tight')
      plt.close()
