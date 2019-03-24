import sys
argv = sys.argv
sys.argv = []
import ROOT
ROOT.gSystem.ResetSignals()
sys.argv = argv
