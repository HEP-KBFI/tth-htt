#!/usr/bin/env python

# Example usage:
# plot_from_histogram.py -i input.root -j autoPU -o output.png -x '# PU interactions' -y '# events' -t 'ttHJetToNonbb' -g

import ROOT
import argparse
import os

ROOT.gROOT.SetBatch(True)

def positive_int_type(value):
  try:
    value_int = int(value)
  except ValueError:
    raise argparse.ArgumentTypeError('Not an integer: %s' % value)
  if value_int <= 0:
    raise argparse.ArgumentTypeError('Must be a positive integer: %d' % value_int)
  return value_int

parser = argparse.ArgumentParser()
parser.add_argument('-i', '--input',
  type = str, metavar = 'path', required = True, help = "Input file",
)
parser.add_argument('-j', '--input-histogram',
  type = str, dest = 'input_histogram', metavar = 'name', required = True, help = 'Input histogram',
)
parser.add_argument('-o', '--output',
  type = str, metavar = 'path', required = True, help = "Output file",
)
parser.add_argument('-t', '--title',
  type = str, metavar = 'str', required = False, default = '', help = "Title",
)
parser.add_argument('-W', '--width',
  type = positive_int_type, metavar = 'int', required = False, default = 1200, help = "Width",
)
parser.add_argument('-H', '--height',
  type = positive_int_type, metavar = 'int', required = False, default = 900,  help = "Height",
)
parser.add_argument('-x', '--x-title',
  type = str, dest = 'x_title', metavar = 'text', required = False, default = '', help = 'Title of x-axis',
)
parser.add_argument('-y', '--y-title',
  type = str, dest = 'y_title', metavar = 'text', required = False, default = '', help = 'Title of y-axis',
)
parser.add_argument('-g', '--grid',
  dest = 'grid', action = 'store_true', default = False, help = "Enable grid lines",
)
parser.add_argument('-l', '--log-y',
  dest = 'logy', action = 'store_true', default = False, help = "Use logarithmic scale for y-axis",
)
parser.add_argument('-L', '--log-x',
  dest = 'logx', action = 'store_true', default = False, help = "Use logarithmic scale for x-axis",
)
parser.add_argument('-f', '--force',
  dest = 'force', action = 'store_true', default = False, help = "Create output dir if it doesn't exist",
)

args = parser.parse_args()
input_filename  = args.input
input_histogram = args.input_histogram
output_filename = args.output
title           = args.title
width           = args.width
height          = args.height
x_title         = args.x_title
y_title         = args.y_title
grid            = args.grid
use_log_y       = args.logy
use_log_x       = args.logx
force           = args.force

if not os.path.isfile(input_filename):
  raise ValueError('No such file: %s' % input_filename)

output_directory = os.path.realpath(os.path.dirname(output_filename))
if not os.path.isdir(output_directory):
  if not force:
    raise ValueError('Directory %s does not exist; use -f/--force to create it' % output_directory)
  else:
    try:
      os.makedirs(output_directory)
    except OSError as err:
      raise ValueError('Could not create directory %s because: %s' % (output_directory, err))

root_file = ROOT.TFile.Open(input_filename, 'read')
if not root_file:
  raise ValueError('Not a valid ROOT file: %s' % input_filename)

histogram = root_file.Get(input_histogram)
if not histogram:
  raise ValueError('No such histogram in %s: %s' % (input_filename, input_histogram))

canvas = ROOT.TCanvas('c1', 'c1', width, height)
if title:
  histogram.SetTitle(title)
if x_title:
  histogram.SetXTitle(x_title)
if y_title:
  histogram.SetYTitle(y_title)
histogram.Draw()

if use_log_y:
  canvas.SetLogy()
if use_log_x:
  canvas.SetLogx()
if grid:
  canvas.SetGrid()
canvas.SaveAs(output_filename)
