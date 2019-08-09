## import CombineHarvester.CombineTools.plotting as plot
import plotting as plot

import ROOT
import argparse
from copy import deepcopy

ROOT.PyConfig.IgnoreCommandLineOptions = True
ROOT.gROOT.SetBatch(ROOT.kTRUE)
plot.ModTDRStyle()

CHANNELS = {
    'e': 'Electron',
    'mu': 'Muon'
}

LAYOUTS = {
    "generic": [
        ('data_fakes', {
            'entries': ['data_fakes'],
            'legend': 'Fakes',
            'color': ROOT.TColor.GetColor(250, 202, 255)
        }
        )
     ]
}


LAYOUTS1 = { ## FOR tt
    "e": [
        ('data_fakes', {
            'entries': ['data_fakes'],
            'legend': 'Fakes',
            'color': ROOT.TColor.GetColor(250, 202, 255)
        }
        ),
        ('Rares', {
            'entries': ['Raresl'],
            'legend': 'Rares',
            'color': ROOT.TColor.GetColor(0,255,0)
        }
        ),
        ('TT', {
            'entries': ['TTl'],
            'legend': 't#bar{t}',
            'color': ROOT.TColor.GetColor(155, 152, 204)
        }
        ),
        ('EWK', {
            'entries': ['EWKl'],
            'legend': 'Electroweak',
            'color': ROOT.TColor.GetColor(222, 90, 106)
        }
        ),
    ],

    "mu": [
        ('data_fakes', {
            'entries': ['data_fakes'],
            'legend': 'Fakes',
            'color': ROOT.TColor.GetColor(250, 202, 255)
        }
        ),
        ('Rares', {
            'entries': ['Raresl'],
            'legend': 'Rares',
            'color': ROOT.TColor.GetColor(0,255,0)
        }
        ),
        ('TT', {
            'entries': ['TTl'],
            'legend': 't#bar{t}',
            'color': ROOT.TColor.GetColor(155, 152, 204)
        }
        ),
        ('EWK', {
            'entries': ['EWKl'],
            'legend': 'Electroweak',
            'color': ROOT.TColor.GetColor(222, 90, 106)
        }
        ),
    ]
}


# customise the layouts for each channel
LAYOUTS['e'] = deepcopy(LAYOUTS1['e'])
LAYOUTS['mu'] = deepcopy(LAYOUTS1['mu'])

parser = argparse.ArgumentParser()
parser.add_argument('--input', '-i', help='Output of PostFitShapes or PostFitShapesFromWorkspace, specified as FILE:BIN')
parser.add_argument('--output', '-o', default=None, help='Output name')
parser.add_argument('--channel', '-c', default='e', choices=['e', 'mu'], help='Channel')
parser.add_argument('--x-title', default='mT^{fix}_{L}', help='x-axis variable, without GeV')
parser.add_argument('--logy', action='store_true')
parser.add_argument('--y-min', type=float, default=1)
parser.add_argument('--x-min', type=float, default=1)
parser.add_argument('--lumi', '-l', type=float, default=0.)

args = parser.parse_args()

intLumiData = args.lumi

filename, folder = args.input.split(':')
file = ROOT.TFile(filename)

if args.output is None:
    args.output = folder

# Canvas and pads
canv = ROOT.TCanvas(args.output, args.output)
pads = plot.TwoPadSplit(0.27, 0.01, 0.01)

## MY LINE
print canv.ClassName()
print canv.GetName()

# Get the data and create axis hist
h_data = file.Get('%s/data_obs' % folder)
name = h_data.GetName()
print name
print h_data.Integral()

h_axes = [h_data.Clone() for x in pads]
for h in h_axes:
    h.Reset()

h_tot = file.Get('%s/TotalProcs' % folder)
h_tot.SetFillColor(plot.CreateTransparentColor(12, 0.3))
h_tot.SetMarkerSize(0)

plot.StandardAxes(h_axes[0].GetXaxis(), h_axes[0].GetYaxis(), args.x_title, 'GeV', fmt='.0f') ## DEF LINE
# plot.StandardAxes(h_axes[0].GetXaxis(), h_axes[0].GetYaxis(), args.x_title, 'GeV')


h_axes[0].Draw()

# A dict to keep track of the hists
h_store = {}

layout = LAYOUTS[args.channel]

stack = ROOT.THStack()
legend = ROOT.TLegend(0.67, 0.86 - 0.04*len(layout), 0.90, 0.91, '', 'NBNDC')

for ele in layout:
    info = ele[1]
    hist = file.Get('%s/%s' % (folder, info['entries'][0]))
    print "hist name is %s and its yield is %f" % (hist.GetName(), hist.Integral())
    plot.Set(hist, FillColor=info['color'], Title=info['legend'])
    if len(info['entries']) > 1:
        for other in info['entries'][1:]:
            hist.Add(file.Get('%s/%s' % (folder, other)))
    h_store[ele[0]] = hist
    stack.Add(hist)

legend.AddEntry(h_data, 'Observed', 'PL')
for ele in reversed(layout):
    legend.AddEntry(h_store[ele[0]], '', 'F')
legend.AddEntry(h_tot, 'Uncertainty', 'F')

stack.Draw('HISTSAME')
h_tot.Draw("E2SAME")
h_data.Draw('SAME')

# if args.x_min > 1:
#     stack.GetXaxis().SetLimits(args.x_min, 300.); ## MY LINE

if args.logy:
    h_axes[0].SetMinimum(args.y_min)
    pads[0].SetLogy(True)

# h_axes[1].SetMinimum(args.x_min)  ## MY LINE

if args.x_min > 1.:
    pads[0].RangeAxis(args.x_min, 1., 300., 10000.);


plot.FixTopRange(pads[0], plot.GetPadYMax(pads[0]), 0.30)
legend.Draw()
plot.FixBoxPadding(pads[0], legend, 0.05)

# Do the ratio plot
pads[1].cd()
pads[1].SetGrid(0, 1)
h_axes[1].Draw()

r_data = plot.MakeRatioHist(h_data, h_tot, True, False)
r_tot = plot.MakeRatioHist(h_tot, h_tot, True, False)
r_tot.Draw('E2SAME')
r_data.Draw('SAME')

plot.SetupTwoPadSplitAsRatio(
    pads, plot.GetAxisHist(
        pads[0]), plot.GetAxisHist(pads[1]), 'Obs/Exp', True, 0.61, 1.39)

# Go back and tidy up the axes and frame
pads[0].cd()
pads[0].GetFrame().Draw()
pads[0].RedrawAxis()

# CMS logo
plot.DrawCMSLogo(pads[0], 'CMS', 'Preliminary', 11, 0.045, 0.05, 1.0, '', 1.0)
plot.DrawTitle(pads[0], '%.1f pb^{-1} (13 TeV)' % intLumiData, 3)

# latex = ROOT.TLatex()
# plot.Set(latex, NDC=None, TextFont=42, TextSize=0.08)
# latex.DrawLatex(0.67, 0.57, CHANNELS[args.channel])
plot.DrawTitle(pads[0], CHANNELS[args.channel], 1)

# ... and we're done
canv.Print('.png')
canv.Print('.pdf')
canv.Print('.root')


