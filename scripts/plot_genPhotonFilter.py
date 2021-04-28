#!/usr/bin/env python

import matplotlib
matplotlib.use('Agg')

import ROOT
import sys
import os.path
import matplotlib.pyplot as plt
import matplotlib.backends.backend_pdf as pdf

plt.rc('font', size = 14)

PROCESSES = [
  { 'WGamma'            : { 'option' : 'selected', 'label' : r'W+$\gamma$',             'rank' : 'subleading' },
    'WJets'             : { 'option' : 'rejected', 'label' : 'W+jets',                  'rank' : 'subleading' } },
   { 'ZGamma'           : { 'option' : 'selected', 'label' : r'Z+$\gamma$',             'rank' : 'third'      },
     'ZJets'            : { 'option' : 'rejected', 'label' : 'Z+jets',                  'rank' : 'third'      } },
   { 'TGamma'           : { 'option' : 'selected', 'label' : r't+$\gamma$',             'rank' : 'subleading' },
     'TJets_tChannel'   : { 'option' : 'rejected', 'label' : 't+jets (t-channel)',      'rank' : 'subleading'  } },
   { 'TTGamma_SemiLept' : { 'option' : 'selected', 'label' : r'$t\bar{t}+\gamma$ (SL)', 'rank' : 'subleading' },
     'TTJets_SemiLept'  : { 'option' : 'rejected', 'label' : r'$t\bar{t}$+jets (SL)',   'rank' : 'subleading' } },
   { 'TTGamma_DiLept'   : { 'option' : 'selected', 'label' : r'$t\bar{t}+\gamma$ (DL)', 'rank' : 'third'      },
     'TTJets_DiLept'    : { 'option' : 'rejected', 'label' : r'$t\bar{t}$+jets (DL)',   'rank' : 'third'      } },
]
SELECTIONS = [ 'selected', 'rejected' ]
LEPTONS = [ 'lepton', 'electron', 'muon' ]
RANKS = [ 'subleading', 'third' ]
SUM_KEY = 'sum'
PLOT_XMIN = 10.

def read_hist(fptr, process, selection, lepton_type, rank):
  assert(selection in SELECTIONS)
  assert(lepton_type in LEPTONS)
  path = os.path.join('genPhotonFilter', selection, process, '{}_{}_pt'.format(rank, lepton_type))
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
      result[lepton_type][selection] = {}
      for rank in RANKS:
        result[lepton_type][selection][rank] = read_hist(fptr, process, selection, lepton_type, rank)
    binning = result[lepton_type][SELECTIONS[0]][RANKS[0]]['xval']
    assert(all(result[lepton_type][selection][rank]['xval'] == binning for selection in SELECTIONS for rank in RANKS))
    nof_bins = len(binning)
    assert(SUM_KEY not in result[lepton_type])
    result[lepton_type][SUM_KEY] = {}
    for rank in RANKS:
      result[lepton_type][SUM_KEY][rank] = {
        'xval' : binning,
        'yval' : [
          sum(result[lepton_type][selection][rank]['yval'][bin_idx] for selection in SELECTIONS) \
          for bin_idx in range(nof_bins)
        ],
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

        option = PROCESSES[pair_idx][process]['option']
        label = PROCESSES[pair_idx][process]['label']
        rank = PROCESSES[pair_idx][process]['rank']

        plot_xmin = min(histograms[pair_idx][process][lepton_type][SUM_KEY][rank]['xval'])
        plot_xmax = max(histograms[pair_idx][process][lepton_type][SUM_KEY][rank]['xval'])
        plt.step(
          histograms[pair_idx][process][lepton_type][option][rank]['xval'],
          histograms[pair_idx][process][lepton_type][option][rank]['yval'],
          lw = 2, linestyle = '-', label = '{}, after {} by veto'.format(label, option.replace('selected', 'accepted')),
        )
        plt.step(
          histograms[pair_idx][process][lepton_type][SUM_KEY][rank]['xval'],
          histograms[pair_idx][process][lepton_type][SUM_KEY][rank]['yval'],
          lw = 2, linestyle = '--', label = r'{}, inclusive'.format(label),
        )
        nof_bins = len(histograms[pair_idx][process][lepton_type][SUM_KEY][rank]['xval'])
        plot_ymin = min(
          min(
            histograms[pair_idx][process][lepton_type][option][rank]['yval'][bin_idx],
            histograms[pair_idx][process][lepton_type][SUM_KEY][rank]['yval'][bin_idx]
          ) for bin_idx in range(nof_bins)
        )
        plot_ymin *= 1.05 if plot_ymin < 0. else 0
        plot_ymax = max(
          max(
            histograms[pair_idx][process][lepton_type][option][rank]['yval'][bin_idx],
            histograms[pair_idx][process][lepton_type][SUM_KEY][rank]['yval'][bin_idx]
          ) for bin_idx in range(nof_bins)
        )
        plot_ymax *= 1.05
        plt.xlabel(r'{} {} $p_T$ [GeV]'.format(rank.capitalize(), lepton_type))
        plt.ylabel('Weighted number of events')
        plt.grid(True)
        plt.xlim(plot_xmin, plot_xmax)
        plt.ylim(plot_ymin, plot_ymax)
        plt.legend(loc = 'upper right')
        output.savefig(bbox_inches = 'tight')
        plt.close()

      assert(len(process_pair) > 0)
      plt.figure(figsize = (10, 8), dpi = 150)

      rank = PROCESSES[pair_idx][list(process_pair.keys())[0]]['rank']
      assert(all(PROCESSES[pair_idx][process]['rank'] == rank for process in process_pair))
      binning = histograms[pair_idx][list(process_pair.keys())[0]][lepton_type][SUM_KEY][rank]['xval']
      assert(all(binning == histograms[pair_idx][process][lepton_type][SUM_KEY][rank]['xval'] for process in process_pair))
      yvals_sum = [
        sum(
          histograms[pair_idx][process][lepton_type][PROCESSES[pair_idx][process]['option']][rank]['yval'][bin_idx] \
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
          histograms[pair_idx][process][lepton_type][option][rank]['yval'],
          lw = 2, linestyle = '-', label = '{}, after {} by veto'.format(label, option.replace('selected', 'accepted')),
        )
      plt.step(binning, yvals_sum, lw = 2, linestyle = '-', label = 'Sum of the above')

      plt.xlabel(r'{} {} $p_T$ [GeV]'.format(rank.capitalize(), lepton_type))
      plt.ylabel('Weighted number of events')
      plt.grid(True)
      plt.xlim(plot_xmin, plot_xmax)
      plt.ylim(plot_ymin, plot_ymax)
      plt.legend(loc = 'upper right')
      output.savefig(bbox_inches = 'tight')
      plt.close()
