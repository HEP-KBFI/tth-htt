#!/usr/bin/env python

import ROOT
import array
import collections
import numpy as np
import os

plot_dir = ''
apply_mll_cut = True

if plot_dir and not os.path.isdir(plot_dir):
  os.makedirs(plot_dir)

if True:
  x_var = 'LHE_HT'
  y_var = ''
else:
  x_var = 'LHE_Njets'
  y_var = 'LHE_HT'

def get_type(var_name):
  if var_name == 'LHE_HT':
    return ('f', [0.])
  elif var_name == 'LHE_Njets':
    return ('B', [0])
  else:
    raise ValueError('Invalid branch name: %s' % var_name)

assert(x_var != '')
is2D = y_var != ''

def dump_yields(fn, fn_out):

  print('Dumping event yields from %s to %s' % (fn, fn_out))

  f = ROOT.TFile.Open(fn)
  t = f.Get('Events')

  x_branch = array.array(*get_type(x_var))
  y_branch = array.array(*get_type(y_var)) if is2D else None

  req_nLHESW = 9

  run = array.array('I', [0])
  luminosityBlock = array.array('I', [0])
  event = array.array('L', [0])

  genWeight = array.array('f', [0.])
  puWeight = array.array('f', [0.])
  puWeightUp = array.array('f', [0.])
  puWeightDown = array.array('f', [0.])
  nLHEScaleWeight = array.array('I', [0])
  LHEScaleWeight = array.array('f', [0.] * req_nLHESW)

  max_objs = 32
  nLHEPart = array.array('B', [0])
  LHEPart_pt = array.array('f', [0.] * max_objs)
  LHEPart_eta = array.array('f', [0.] * max_objs)
  LHEPart_phi = array.array('f', [0.] * max_objs)
  LHEPart_mass = array.array('f', [0.] * max_objs)
  LHEPart_pdgId = array.array('i', [0] * max_objs)

  t.SetBranchAddress('run', run)
  t.SetBranchAddress('luminosityBlock', luminosityBlock)
  t.SetBranchAddress('event', event)

  t.SetBranchAddress(x_var, x_branch)
  if is2D:
    t.SetBranchAddress(y_var, y_branch)

  t.SetBranchAddress('genWeight', genWeight)
  t.SetBranchAddress('puWeight', puWeight)
  t.SetBranchAddress('puWeightUp', puWeightUp)
  t.SetBranchAddress('puWeightDown', puWeightDown)
  t.SetBranchAddress('nLHEScaleWeight', nLHEScaleWeight)
  t.SetBranchAddress('LHEScaleWeight', LHEScaleWeight)

  if apply_mll_cut:
    t.SetBranchAddress('nLHEPart', nLHEPart)
    t.SetBranchAddress('LHEPart_pt', LHEPart_pt)
    t.SetBranchAddress('LHEPart_eta', LHEPart_eta)
    t.SetBranchAddress('LHEPart_phi', LHEPart_phi)
    t.SetBranchAddress('LHEPart_mass', LHEPart_mass)
    t.SetBranchAddress('LHEPart_pdgId', LHEPart_pdgId)

  bins = {
    'LHE_Njets' : list(map(float, range(6))),
    'LHE_HT'    : [ 0., 100., 200., 400., 600., 800., 1200., 2500., 1.e5 ]
  }

  bins_arr = { key : array.array('d', bins[key]) for key in bins }
  mll_bins  = [ 10., 50. ]

  def get_mll_str(val):
    assert(len(mll_bins) == 2)
    if val < mll_bins[0]:
      return 'lt%s' % str(int(mll_bins[0]))
    elif mll_bins[0] <= val < mll_bins[1]:
      return '%sto%s' % (str(int(mll_bins[0])), str(int(mll_bins[1])))
    elif val >= mll_bins[1]:
      return 'gt%s' % (str(int(mll_bins[1])))
    else:
      raise RuntimeError('Unexpected value: %f (%s)' % (val, mll_bins))

  histograms = collections.OrderedDict()

  bins_x = bins_arr[x_var]
  bins_y = bins_arr[y_var] if is2D else None

  def create_histogram(key, title):
    if is2D:
      histograms[key] = ROOT.TH2D(key, title, len(bins_x) - 1, bins_x, len(bins_y) - 1, bins_y)
      for bin_idx in range(len(bins_x) - 1):
        histograms[key].GetXaxis().SetBinLabel(bin_idx + 1, '%d <= %s < %d' % (bins_x[bin_idx], x_var, bins_x[bin_idx + 1]))
      for bin_idx in range(len(bins_y) - 1):
        histograms[key].GetYaxis().SetBinLabel(bin_idx + 1, '%d <= %s < %d' % (bins_y[bin_idx], y_var, bins_y[bin_idx + 1]))
      histograms[key].SetXTitle(x_var)
      histograms[key].SetYTitle(y_var)
    else:
      histograms[key] = ROOT.TH1D(key, title, len(bins_x) - 1, bins_x)
      for bin_idx in range(len(bins_x) - 1):
        histograms[key].GetXaxis().SetBinLabel(bin_idx + 1, '%d <= %s < %d' % (bins_x[bin_idx], x_var, bins_x[bin_idx + 1]))
      histograms[key].SetXTitle(x_var)

  count_keys = collections.OrderedDict([
    ('Count',                               { 'nbins' :          1, 'title' : 'sum(1)',                                   }),
    ('CountFullWeighted',                   { 'nbins' :          3, 'title' : 'sum(gen * PU(central,up,down))',           }),
    ('CountWeighted',                       { 'nbins' :          3, 'title' : 'sum(sgn(gen) * PU(central,up,down))',      }),
    ('CountFullWeightedNoPU',               { 'nbins' :          1, 'title' : 'sum(gen)',                                 }),
    ('CountPosWeight',                      { 'nbins' :          1, 'title' : 'sum(gen > 0)'                              }),
    ('CountNegWeight',                      { 'nbins' :          1, 'title' : 'sum(gen < 0)'                              }),
    ('CountWeightedNoPU',                   { 'nbins' :          1, 'title' : 'sum(sgn(gen))',                            }),
    ('CountWeightedLHEWeightScale',         { 'nbins' : req_nLHESW, 'title' : 'sum(sgn(gen) * PU(central) * LHE(scale))', }),
    ('CountWeightedLHEWeightScaleNoPU',     { 'nbins' : req_nLHESW, 'title' : 'sum(sgn(gen) * LHE(scale))',               }),
    ('CountFullWeightedLHEWeightScale',     { 'nbins' : req_nLHESW, 'title' : 'sum(gen * PU(central) * LHE(scale))',      }),
    ('CountFullWeightedLHEWeightScaleNoPU', { 'nbins' : req_nLHESW, 'title' : 'sum(gen * LHE(scale))',                    }),
  ])

  if apply_mll_cut:
    for val in [ mll_bins[0] - 1., (mll_bins[0] + mll_bins[1]) / 2., mll_bins[1] + 1 ]:
      for count_key, count_settings in count_keys.items():
        for histogram_idx in range(count_settings['nbins']):
          mll_str = get_mll_str(val)
          key = '%s_%d_%s' % (count_key, histogram_idx, mll_str)
          title = count_settings['title']
          if count_settings['nbins'] > 1:
            title += ' [bin = %d]' % histogram_idx
          title += ' (mll %s)' % mll_str
          create_histogram(key, title)
  else:
    for count_key, count_settings in count_keys.items():
      for histogram_idx in range(count_settings['nbins']):
        key = '%s_%d' % (count_key, histogram_idx)
        title = count_settings['title']
        if count_settings['nbins'] > 1:
          title += ' [bin = %d]' % histogram_idx
        create_histogram(key, title)

  def clip(value, min_val = -10., max_val = 10.):
    return min(max(value, min_val), max_val)

  def plot2d(histogram, plot_fn_base, width = 1200, height = 900):
    canvas = ROOT.TCanvas('c1', 'c1', width, height)
    ROOT.gStyle.SetOptStat(0)
    histogram.Draw('col text')
    canvas.SetLogy()
    canvas.SaveAs('%s.png' % plot_fn_base)
    canvas.SaveAs('%s.pdf' % plot_fn_base)
    del canvas

  def plot1d(histogram, plot_fn_base, width = 1200, height = 900):
    canvas = ROOT.TCanvas('c1', 'c1', width, height)
    ROOT.gStyle.SetOptStat(0)
    histogram.SetLineWidth(2)
    histogram.Draw('hist')
    canvas.SetLogx()
    canvas.SetLogy()
    canvas.SetGrid()
    canvas.SaveAs('%s.png' % plot_fn_base)
    canvas.SaveAs('%s.pdf' % plot_fn_base)
    del canvas

  n = t.GetEntries()
  printEvery = 100000

  for i in range(n):
    t.GetEntry(i)
    if i % printEvery == 0:
      rle = ':'.join(map(lambda x: str(x[0]), [ run, luminosityBlock, event ]))
      print('Processing event %d: %s' % (i, rle))

    if apply_mll_cut:
      invmass = []
      for j in range(nLHEPart[0]):
        if abs(LHEPart_pdgId[j]) in [ 11, 13, 15 ]:
          lv = ROOT.TLorentzVector()
          lv.SetPtEtaPhiM(LHEPart_pt[j], LHEPart_eta[j], LHEPart_phi[j], LHEPart_mass[j])
          invmass.append(lv)
      if len(invmass) != 2:
        continue
      mll = (invmass[0] + invmass[1]).M()
      suffix = '_%s' % get_mll_str(mll)
    else:
      suffix = ''


    genWeight_sign = np.sign(genWeight[0])
    counts = {
      'Count_0'                  : 1.,
      'CountWeighted_0'         : genWeight_sign * puWeight[0],
      'CountWeighted_1'         : genWeight_sign * puWeightUp[0],
      'CountWeighted_2'         : genWeight_sign * puWeightDown[0],
      'CountFullWeighted_0'     : genWeight[0]   * puWeight[0],
      'CountFullWeighted_1'     : genWeight[0]   * puWeightUp[0],
      'CountFullWeighted_2'     : genWeight[0]   * puWeightDown[0],
      'CountWeightedNoPU_0'     : genWeight_sign,
      'CountFullWeightedNoPU_0' : genWeight[0],
      'CountPosWeight_0'        : genWeight[0]   * (genWeight_sign > 0),
      'CountNegWeight_0'        : genWeight[0]   * (genWeight_sign < 0),
    }
    if nLHEScaleWeight[0] != req_nLHESW:
      print('Error: event #%d' % i)
      continue
    for j in range(nLHEScaleWeight[0]):
      LHEScaleWeight_clipped = clip(LHEScaleWeight[j])
      counts['CountWeightedLHEWeightScale_%d' % j]         = genWeight_sign * puWeight[0] * LHEScaleWeight_clipped
      counts['CountWeightedLHEWeightScaleNoPU_%d' % j]     = genWeight_sign               * LHEScaleWeight_clipped
      counts['CountFullWeightedLHEWeightScale_%d' % j]     = genWeight[0]   * puWeight[0] * LHEScaleWeight_clipped
      counts['CountFullWeightedLHEWeightScaleNoPU_%d' % j] = genWeight[0]                 * LHEScaleWeight_clipped
    for count_key in counts:
      key = count_key + suffix
      evtWeight = counts[count_key]
      if is2D:
        histograms[key].Fill(x_branch[0], y_branch[0], evtWeight)
      else:
        histograms[key].Fill(x_branch[0], evtWeight)

  f_out = ROOT.TFile.Open(fn_out, 'recreate')
  f_out.cd()
  for histogram in histograms.values():
    histogram.Write()
    if plot_dir:
      if is2D:
        plot2d(histogram, os.path.join(plot_dir, histogram.GetName()))
      else:
        plot1d(histogram, os.path.join(plot_dir, histogram.GetName()))

  f.Close()
  f_out.Close()

from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017 import samples_2017 as samples

allowed_sample_names = [
  'DYJetsToLL_M-4to50_HT-100to200',
  'DYJetsToLL_M-4to50_HT-100to200_ext1',
  'DYJetsToLL_M-4to50_HT-200to400',
  'DYJetsToLL_M-4to50_HT-200to400_ext1',
  'DYJetsToLL_M-4to50_HT-400to600',
  'DYJetsToLL_M-4to50_HT-400to600_ext1',
  'DYJetsToLL_M-4to50_HT-600toInf',
  'DYJetsToLL_M-10to50',
]
output_dir_base = os.path.expanduser('~/sandbox/project_event_counts')

for sample_key, sample_info in samples.items():
  sample_name = sample_info['process_name_specific']
  if sample_name in allowed_sample_names:
    fp = sample_info['local_paths'][0]['path']
    nof_files = sample_info['nof_files']
    fns = [ os.path.join(fp, '%04d' % (idx // 1000), 'tree_%d.root' % idx) for idx in range(1, nof_files + 1) ]
    output_dir = os.path.join(output_dir_base, sample_name)
    if not os.path.isdir(output_dir):
      os.makedirs(output_dir)
    for fn in fns:
      fn_base = os.path.basename(fn).replace('tree', 'hist')
      fn_out = os.path.join(output_dir, fn_base)
      dump_yields(fn, fn_out)
