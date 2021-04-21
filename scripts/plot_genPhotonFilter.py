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

PROCESSES = [
  { 'WGamma'  : { 'option' : 'selected', 'label' : r'W+$\gamma$'        },
    'WJets'   : { 'option' : 'rejected', 'label' : 'W+jets'             } },
  { 'ZGamma'  : { 'option' : 'selected', 'label' : r'Z+$\gamma$'        },
    'ZJets'   : { 'option' : 'rejected', 'label' : 'Z+jets'             } },
  { 'TGamma'  : { 'option' : 'selected', 'label' : r't+$\gamma$'        },
    'TJets'   : { 'option' : 'rejected', 'label' : 't+jets'             } },
  { 'TTGamma' : { 'option' : 'selected', 'label' : r'$t\bar{t}+\gamma$' },
    'TTJets'  : { 'option' : 'rejected', 'label' : r'$t\bar{t}$+jets'   } },
]
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

histograms = []
for process_pair in PROCESSES:
  results = {}
  for process in process_pair:
    assert(process not in results)
    results[process] = read_process(f, process)
  histograms.append(results)
f.Close()

with pdf.PdfPages(outfn) as output:
  for pair_idx, process_pair in enumerate(PROCESSES):
    for lepton_type in LEPTONS:
      for process in process_pair:
        plt.figure(figsize = (10, 8), dpi = 150)

        plot_xmin = min(histograms[pair_idx][process][lepton_type][SUM_KEY]['xval'])
        plot_xmax = max(histograms[pair_idx][process][lepton_type][SUM_KEY]['xval'])
        option = PROCESSES[pair_idx][process]['option']
        label = PROCESSES[pair_idx][process]['label']
        plt.step(
          histograms[pair_idx][process][lepton_type][option]['xval'],
          histograms[pair_idx][process][lepton_type][option]['yval'],
          lw = 2, linestyle = '-', label = '{}, after {} by veto'.format(label, option.replace('selected', 'accepted')),
        )
        plt.step(
          histograms[pair_idx][process][lepton_type][SUM_KEY]['xval'],
          histograms[pair_idx][process][lepton_type][SUM_KEY]['yval'],
          lw = 2, linestyle = '--', label = r'{}, inclusive'.format(label),
        )
        plt.xlabel(r'Subleading {} $p_T$ [GeV]'.format(lepton_type))
        plt.ylabel('Weighted number of events')
        plt.grid(True)
        plt.xlim(plot_xmin, plot_xmax)
        plt.legend(loc = 'upper right')
        output.savefig(bbox_inches = 'tight')
        plt.close()

      assert(len(process_pair) > 0)
      plt.figure(figsize = (10, 8), dpi = 150)

      binning = histograms[pair_idx][process_pair.keys()[0]][lepton_type][SUM_KEY]['xval']
      assert(all(binning == histograms[pair_idx][process][lepton_type][SUM_KEY]['xval'] for process in process_pair))
      yvals_sum = [
        sum(
          histograms[pair_idx][process][lepton_type][PROCESSES[pair_idx][process]['option']]['yval'][bin_idx] \
          for process in process_pair
        ) for bin_idx in range(len(binning))
      ]

      plot_xmin = min(binning)
      plot_xmax = max(binning)
      plot_ymin = min(yvals_sum)
      plot_ymin *= 1.05 if plot_ymin < 0. else 0
      plot_ymax = max(yvals_sum) * 1.05
      for process in process_pair:
        option = PROCESSES[pair_idx][process]['option']
        label = PROCESSES[pair_idx][process]['label']
        plt.step(
          binning,
          histograms[pair_idx][process][lepton_type][option]['yval'],
          lw = 2, linestyle = '-', label = '{}, after {} by veto'.format(label, option.replace('selected', 'accepted')),
        )
      plt.step(binning, yvals_sum, lw = 2, linestyle = '-', label = 'Sum of the above')

      plt.xlabel(r'Subleading {} $p_T$ [GeV]'.format(lepton_type))
      plt.ylabel('Weighted number of events')
      plt.grid(True)
      plt.xlim(plot_xmin, plot_xmax)
      plt.ylim(plot_ymin, plot_ymax)
      plt.legend(loc = 'upper right')
      output.savefig(bbox_inches = 'tight')
      plt.close()
