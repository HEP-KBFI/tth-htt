from tthAnalysis.HiggsToTauTau.configs.analyzeConfig import *
from tthAnalysis.HiggsToTauTau.jobTools import create_if_not_exists, add_chmodX
from tthAnalysis.HiggsToTauTau.analysisTools import initDict, getKey, create_cfg, generateInputFileList
from tthAnalysis.HiggsToTauTau.common import logging

import jinja2
import codecs

jinja_template_dir = os.path.join(
  os.getenv('CMSSW_BASE'), 'src', 'tthAnalysis', 'HiggsToTauTau', 'python', 'templates', 'LeptonEfficiency'
)
jinja2.filters.FILTERS['os.path.basename'] = os.path.basename

def getBinName(label, minValue, maxValue):
  binName = ''
  if minValue > 0. and maxValue > 0.:
    binName = '%s%1.1fto%1.1f' % (label, minValue, maxValue)
  elif minValue > 0.:
    binName = '%sGt%1.1f' % (label, minValue)
  elif maxValue > 0.:
    binName = '%sLt%1.1f' % (label, maxValue)
  binName = binName.replace('.', '_')
  return binName

def getEtaBin(minAbsEta, maxAbsEta):
  return getBinName("absEta", minAbsEta, maxAbsEta)

def getPtBin(minPt, maxPt):
  return getBinName("Pt", minPt, maxPt)

#### CERN BINNING SCHEME ####
fit_param_range_map = {
  'electron' : {
    'bbWW_SL':{
      'tight' : {
        'incl'                            : '0.01,10.0',
        'absEtaLt0_9_Pt10_0to15_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt15_0to20_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt20_0to25_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt25_0to30_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt30_0to35_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt35_0to40_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt40_0to45_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt45_0to60_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt60_0to80_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt80_0to120_0'       : '0.01,10.0',
        'absEta0_9to1_2_Pt10_0to15_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt15_0to20_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt20_0to25_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt25_0to30_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt30_0to35_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt35_0to40_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt40_0to45_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt45_0to60_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt60_0to80_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt80_0to120_0'    : '0.01,10.0',
        'absEta1_2to2_1_Pt10_0to15_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt15_0to20_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt20_0to25_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt25_0to30_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt30_0to35_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt35_0to40_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt40_0to45_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt45_0to60_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt60_0to80_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt80_0to120_0'    : '0.01,10.0',
        'absEta2_1to2_5_Pt10_0to15_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt15_0to20_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt20_0to25_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt25_0to30_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt30_0to35_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt35_0to40_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt40_0to45_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt45_0to60_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt60_0to80_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt80_0to120_0'    : '0.01,10.0',
      },
      'presel_not_tight' : {
        'incl'                            : '0.01,10.0',
        'absEtaLt0_9_Pt10_0to15_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt15_0to20_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt20_0to25_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt25_0to30_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt30_0to35_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt35_0to40_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt40_0to45_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt45_0to60_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt60_0to80_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt80_0to120_0'       : '0.01,10.0',
        'absEta0_9to1_2_Pt10_0to15_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt15_0to20_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt20_0to25_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt25_0to30_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt30_0to35_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt35_0to40_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt40_0to45_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt45_0to60_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt60_0to80_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt80_0to120_0'    : '0.01,10.0',
        'absEta1_2to2_1_Pt10_0to15_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt15_0to20_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt20_0to25_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt25_0to30_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt30_0to35_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt35_0to40_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt40_0to45_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt45_0to60_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt60_0to80_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt80_0to120_0'    : '0.01,10.0',
        'absEta2_1to2_5_Pt10_0to15_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt15_0to20_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt20_0to25_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt25_0to30_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt30_0to35_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt35_0to40_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt40_0to45_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt45_0to60_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt60_0to80_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt80_0to120_0'    : '0.01,10.0',
      },
    },
    'HHorTTH':{
      'tight' : {
        'incl'                            : '0.01,10.0',
        'absEtaLt0_9_Pt10_0to15_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt15_0to20_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt20_0to25_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt25_0to30_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt30_0to35_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt35_0to40_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt40_0to45_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt45_0to60_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt60_0to80_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt80_0to120_0'       : '0.01,10.0',
        'absEta0_9to1_2_Pt10_0to15_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt15_0to20_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt20_0to25_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt25_0to30_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt30_0to35_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt35_0to40_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt40_0to45_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt45_0to60_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt60_0to80_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt80_0to120_0'    : '0.01,10.0',
        'absEta1_2to2_1_Pt10_0to15_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt15_0to20_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt20_0to25_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt25_0to30_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt30_0to35_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt35_0to40_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt40_0to45_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt45_0to60_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt60_0to80_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt80_0to120_0'    : '0.01,10.0',
        'absEta2_1to2_5_Pt10_0to15_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt15_0to20_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt20_0to25_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt25_0to30_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt30_0to35_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt35_0to40_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt40_0to45_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt45_0to60_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt60_0to80_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt80_0to120_0'    : '0.01,10.0',
      },
      'presel_not_tight' : {
        'incl'                            : '0.01,10.0',
        'absEtaLt0_9_Pt10_0to15_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt15_0to20_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt20_0to25_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt25_0to30_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt30_0to35_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt35_0to40_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt40_0to45_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt45_0to60_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt60_0to80_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt80_0to120_0'       : '0.01,10.0',
        'absEta0_9to1_2_Pt10_0to15_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt15_0to20_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt20_0to25_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt25_0to30_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt30_0to35_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt35_0to40_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt40_0to45_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt45_0to60_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt60_0to80_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt80_0to120_0'    : '0.01,10.0',
        'absEta1_2to2_1_Pt10_0to15_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt15_0to20_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt20_0to25_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt25_0to30_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt30_0to35_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt35_0to40_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt40_0to45_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt45_0to60_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt60_0to80_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt80_0to120_0'    : '0.01,10.0',
        'absEta2_1to2_5_Pt10_0to15_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt15_0to20_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt20_0to25_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt25_0to30_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt30_0to35_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt35_0to40_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt40_0to45_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt45_0to60_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt60_0to80_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt80_0to120_0'    : '0.01,10.0',
      },
    },
  },
  'muon' : {
    'bbWW_SL':{
      'tight' : {
        'incl'                            : '0.01,10.0',
        'absEtaLt0_9_Pt10_0to15_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt15_0to20_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt20_0to25_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt25_0to30_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt30_0to35_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt35_0to40_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt40_0to45_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt45_0to60_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt60_0to80_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt80_0to120_0'       : '0.01,10.0',
        'absEta0_9to1_2_Pt10_0to15_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt15_0to20_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt20_0to25_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt25_0to30_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt30_0to35_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt35_0to40_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt40_0to45_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt45_0to60_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt60_0to80_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt80_0to120_0'    : '0.01,10.0',
        'absEta1_2to2_1_Pt10_0to15_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt15_0to20_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt20_0to25_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt25_0to30_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt30_0to35_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt35_0to40_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt40_0to45_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt45_0to60_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt60_0to80_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt80_0to120_0'    : '0.01,10.0',
        'absEta2_1to2_5_Pt10_0to15_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt15_0to20_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt20_0to25_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt25_0to30_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt30_0to35_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt35_0to40_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt40_0to45_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt45_0to60_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt60_0to80_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt80_0to120_0'    : '0.01,10.0',
      },
      'presel_not_tight' : {
        'incl'                            : '0.01,10.0',
        'absEtaLt0_9_Pt10_0to15_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt15_0to20_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt20_0to25_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt25_0to30_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt30_0to35_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt35_0to40_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt40_0to45_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt45_0to60_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt60_0to80_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt80_0to120_0'       : '0.01,10.0',
        'absEta0_9to1_2_Pt10_0to15_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt15_0to20_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt20_0to25_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt25_0to30_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt30_0to35_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt35_0to40_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt40_0to45_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt45_0to60_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt60_0to80_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt80_0to120_0'    : '0.01,10.0',
        'absEta1_2to2_1_Pt10_0to15_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt15_0to20_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt20_0to25_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt25_0to30_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt30_0to35_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt35_0to40_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt40_0to45_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt45_0to60_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt60_0to80_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt80_0to120_0'    : '0.01,10.0',
        'absEta2_1to2_5_Pt10_0to15_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt15_0to20_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt20_0to25_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt25_0to30_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt30_0to35_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt35_0to40_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt40_0to45_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt45_0to60_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt60_0to80_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt80_0to120_0'    : '0.01,10.0',
      }
    },
    'HHorTTH':{
      'tight' : {
        'incl'                            : '0.01,10.0',
        'absEtaLt0_9_Pt10_0to15_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt15_0to20_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt20_0to25_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt25_0to30_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt30_0to35_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt35_0to40_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt40_0to45_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt45_0to60_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt60_0to80_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt80_0to120_0'       : '0.01,10.0',
        'absEta0_9to1_2_Pt10_0to15_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt15_0to20_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt20_0to25_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt25_0to30_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt30_0to35_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt35_0to40_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt40_0to45_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt45_0to60_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt60_0to80_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt80_0to120_0'    : '0.01,10.0',
        'absEta1_2to2_1_Pt10_0to15_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt15_0to20_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt20_0to25_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt25_0to30_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt30_0to35_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt35_0to40_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt40_0to45_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt45_0to60_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt60_0to80_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt80_0to120_0'    : '0.01,10.0',
        'absEta2_1to2_5_Pt10_0to15_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt15_0to20_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt20_0to25_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt25_0to30_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt30_0to35_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt35_0to40_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt40_0to45_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt45_0to60_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt60_0to80_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt80_0to120_0'    : '0.01,10.0',
      },
      'presel_not_tight' : {
        'incl'                            : '0.01,10.0',
        'absEtaLt0_9_Pt10_0to15_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt15_0to20_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt20_0to25_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt25_0to30_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt30_0to35_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt35_0to40_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt40_0to45_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt45_0to60_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt60_0to80_0'        : '0.01,10.0',
        'absEtaLt0_9_Pt80_0to120_0'       : '0.01,10.0',
        'absEta0_9to1_2_Pt10_0to15_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt15_0to20_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt20_0to25_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt25_0to30_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt30_0to35_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt35_0to40_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt40_0to45_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt45_0to60_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt60_0to80_0'     : '0.01,10.0',
        'absEta0_9to1_2_Pt80_0to120_0'    : '0.01,10.0',
        'absEta1_2to2_1_Pt10_0to15_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt15_0to20_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt20_0to25_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt25_0to30_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt30_0to35_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt35_0to40_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt40_0to45_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt45_0to60_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt60_0to80_0'     : '0.01,10.0',
        'absEta1_2to2_1_Pt80_0to120_0'    : '0.01,10.0',
        'absEta2_1to2_5_Pt10_0to15_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt15_0to20_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt20_0to25_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt25_0to30_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt30_0to35_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt35_0to40_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt40_0to45_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt45_0to60_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt60_0to80_0'     : '0.01,10.0',
        'absEta2_1to2_5_Pt80_0to120_0'    : '0.01,10.0',
      }
    },
  }
}

def construct_lepton_params(lepton, lepton_short, LFR_type, selection, absEtaPtBinString, error_msg):
  if absEtaPtBinString not in fit_param_range_map[lepton][LFR_type][selection]:
    raise ValueError(error_msg)
  lepton_id = '%ss_%s_%s' % (lepton, selection, absEtaPtBinString)
  lepton_id_short = lepton_id.replace('%ss_' % lepton, '%s_' % lepton_short)
  lepton_range = fit_param_range_map[lepton][LFR_type][selection][absEtaPtBinString]
  return (lepton_id_short, lepton_range, lepton_id)

category_template = """{% for input, output in categories %}
  cms.PSet(
    input = cms.string("{{ input }}"),
    output = cms.string("{{ output }}"),
  ),{% endfor %}
"""

class analyzeConfig_LeptonEfficiency(analyzeConfig):
  """Configuration metadata needed to run analysis in a single go.

  Sets up a folder structure by defining full path names; no directory creation is delegated here.

  Args specific to analyzeConfig_LeptonEfficiency:
    charge_selection: either `OS` or `SS` (opposite-sign or same-sign of the electron+muon pair)
    hadTau_selections: list of tau ID discriminators to check

  See $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/python/analyzeConfig.py
  for documentation of further Args.

  """
  def __init__(self,
        configDir,
        outputDir,
        cmssw_base_dir_combine,
        executable_analyze,
        samples,
        absEtaBins_e,
        absEtaBins_mu,
        ptBins_e,
        ptBins_mu,
        lepton_type_string,       
        lep_mva_wp,
        lep_useTightChargeCut,       
        lepton_selection_string,
        fillGenEvtHistograms,
        jet_cleaning_by_index,
        gen_matching_by_index,
        central_or_shifts,
        numerator_histogram,
        denominator_histogram,
        prep_dcard,
        max_files_per_job,
        era,
        use_lumi,
        lumi,
        check_output_files,
        running_method,
        num_parallel_jobs,
        executable_prep_dcard, 
        executable_comp_LeptonEfficiency,
        select_rle_output = False,
        verbose           = False,
        dry_run           = False,
        isDebug           = False,
        use_home          = False,
        submission_cmd    = None,
      ):
    analyzeConfig.__init__(self,
      configDir             = configDir,
      outputDir             = outputDir,
      executable_analyze    = executable_analyze,
      channel               = "LeptonEfficiency",
      samples               = samples,
      central_or_shifts     = central_or_shifts,
      jet_cleaning_by_index = jet_cleaning_by_index,
      gen_matching_by_index = gen_matching_by_index,
      max_files_per_job     = max_files_per_job,
      era                   = era,
      use_lumi              = use_lumi,
      lumi                  = lumi,
      check_output_files    = check_output_files,
      running_method        = running_method,
      num_parallel_jobs     = num_parallel_jobs,
      histograms_to_fit     = { numerator_histogram[0] : {}, denominator_histogram[0] : {} },
      executable_prep_dcard = executable_prep_dcard,
      triggers              = (['1e'] if (lepton_type_string == "e") else ['1mu']),
      verbose               = verbose,
      dry_run               = dry_run,
      isDebug               = isDebug,
      use_home              = use_home,
      lep_mva_wp            = lep_mva_wp,
      lep_useTightChargeCut = lep_useTightChargeCut,
      submission_cmd        = submission_cmd,
      apply_nc_correction   = None,
    )

    self.cmssw_base_dir_combine = cmssw_base_dir_combine
    if not os.path.isdir(os.path.join(self.cmssw_base_dir_combine, 'src', 'CombineHarvester')) or \
       not os.path.isdir(os.path.join(self.cmssw_base_dir_combine, 'src', 'HiggsAnalysis', 'CombinedLimit')):
      raise ValueError('CMSSW path for combine not valid: %s' % self.cmssw_base_dir_combine)

    self.lepton_type_string = lepton_type_string  
    self.lepton_selection_string = lepton_selection_string

    self.lep_mva_wp = lep_mva_wp 
    self.absEtaBins_e = absEtaBins_e
    self.ptBins_e = ptBins_e
    self.absEtaBins_mu = absEtaBins_mu
    self.ptBins_mu = ptBins_mu

    self.cfgFile_analyze = os.path.join(self.template_dir, "analyze_LeptonEfficiency_cfg.py")

    self.fillGenEvtHistograms = fillGenEvtHistograms
    self.executable_prep_dcard = executable_prep_dcard ## LFR SPECIFIC (NEEDED)
    self.cfgFile_prep_dcard = os.path.join(self.template_dir, "prepareDatacards_LeptonEfficiency_cfg.py")
    self.executable_comp_LeptonEfficiency = executable_comp_LeptonEfficiency ## LFR SPECIFIC (NEEDED) 
    self.cfgFile_comp_LeptonEfficiency = os.path.join(self.template_dir, "comp_LeptonEfficiency_cfg.py")
    self.jobOptions_comp_LeptonEfficiency = {}

    self.prep_dcard_processesToCopy = [ "data_obs", "DY", "DY_signal", "DY_fake", "WJets", "TTbar", "Singletop", "Diboson" ]
    self.sig_proc = "DY_signal"
    self.histogramDir_prep_dcard = "LeptonEfficiency"
    self.prep_dcard = prep_dcard

    self.numerator_histogram = numerator_histogram[0]
    self.denominator_histogram = denominator_histogram[0]
    self.numerator_plotLabel = numerator_histogram[1]
    self.denominator_plotLabel = denominator_histogram[1] 

    self.select_rle_output = select_rle_output

    self.jobOptions_combine = {}

  def createCfg_analyze(self, jobOptions, sample_info):
    """Create python configuration file for the analyze_LeptonEfficiency executable (analysis code)

    Args:
      inputFiles: list of input files (Ntuples)
      outputFile: output file of the job -- a ROOT file containing histogram
      process: either "data_obs", "DY", "WJets", "TTbar", "Singletop", "Diboson"
      is_mc: flag indicating whether job runs on MC (True) or data (False)
      lumi_scale: event weight (= xsection * luminosity / number of events)
      central_or_shift: either 'central' or one of the systematic uncertainties defined in $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/bin/analyze_LeptonEfficiency.cc
    """
    additionalJobOptions = [
      'absEtaBins_e',
      'ptBins_e',
      'absEtaBins_mu',
      'ptBins_mu',
      'triggers',
    ]
    lines = super(analyzeConfig_LeptonEfficiency, self).createCfg_analyze(
      jobOptions, sample_info, additionalJobOptions, isLeptonFR = False
    )
    lines.append("process.analyze_LeptonEfficiency.lepton_type = cms.string('%s')" % self.lepton_type_string)
    lines.append("process.analyze_LeptonEfficiency.leptonSelection = cms.string('%s')" % self.lepton_selection_string)
    if(self.lepton_type_string == 'e'):
          lines.append("process.analyze_LeptonEfficiency.apply_offline_e_trigger_cuts_1e = cms.bool(True)")
    create_cfg(self.cfgFile_analyze, jobOptions['cfgFile_modified'], lines)


  def createCfg_comp_LeptonEfficiency(self, jobOptions):
    """Create python configuration file for the comp_LeptonEfficiency executable

    Args:
      inputFiles: input file (the ROOT file produced by hadd_stage1)
      outputFile: output file of the job
    """
    lines = []
    lines.append("process.fwliteInput.fileNames = cms.vstring(%s)" % jobOptions['inputFile'])
    lines.append("process.fwliteOutput.fileName = cms.string('%s')" % jobOptions['outputFile'])
    lines.append("process.comp_LeptonEfficiency.histogramName_e = cms.string('LeptonIDEff_mva%s_el_data_comb')" % convert_lep_wp(self.lep_mva_cut_e))
    lines.append("process.comp_LeptonEfficiency.absEtaBins_e = cms.vdouble(%s)" % jobOptions['absEtaBins_e'])
    lines.append("process.comp_LeptonEfficiency.ptBins_e = cms.vdouble(%s)" % jobOptions['ptBins_e'])
    lines.append("process.comp_LeptonEfficiency.histogramName_mu = cms.string('LeptonIDEff_mva%s_mu_data_comb')" % convert_lep_wp(self.lep_mva_cut_mu))
    lines.append("process.comp_LeptonEfficiency.absEtaBins_mu = cms.vdouble(%s)" % jobOptions['absEtaBins_mu'])
    lines.append("process.comp_LeptonEfficiency.ptBins_mu = cms.vdouble(%s)" % jobOptions['ptBins_mu'])
    lines.append("process.comp_LeptonEfficiency.outputFileName = cms.string('%s')" % jobOptions['plots_outputFileName'])
    lines.append("process.comp_LeptonEfficiency.HistogramName_num = cms.string('%s')" % self.numerator_histogram)
    lines.append("process.comp_LeptonEfficiency.HistogramName_den = cms.string('%s')" % self.denominator_histogram)
    lines.append("process.comp_LeptonEfficiency.lepton_type = cms.string('%s')" % self.lepton_type_string) 
    lines.append("process.comp_LeptonEfficiency.processName = cms.string('%s')" % self.sig_proc)
    create_cfg(self.cfgFile_comp_LeptonEfficiency, jobOptions['cfgFile_modified'], lines)

  def createCfg_prep_dcard_LeptonEfficiency(self, jobOptions):
    """
    Fills the template of python configuration file for datacard preparation
    Args:
      histogramToFit: name of the histogram used for signal extraction
      """
    category_output = self.channel
    if jobOptions['label']:
      category_output += "_%s" % jobOptions['label']
    lines = []
    lines.append("process.fwliteInput.fileNames = cms.vstring('%s')" % jobOptions['inputFile'])
    lines.append("process.fwliteOutput.fileName = cms.string('%s')" % jobOptions['datacardFile'])
    lines.append("process.prepareDatacards.histogramToFit = cms.string('%s')" % jobOptions['histogramToFit'])
    lines.append("process.prepareDatacards.processesToCopy = cms.vstring('data_obs', 'DY', 'DY_signal', 'DY_fake', 'TTbar', 'Diboson', 'WJets', 'Singletop')")
    if jobOptions['histogramToFit'] in ["m_ll"]:
      lines.append("process.prepareDatacards.histogramToFit_xMin = cms.double(0.)")
      lines.append("process.prepareDatacards.histogramToFit_xMax = cms.double(150.)")
      lines.append("process.prepareDatacards.minEvents_automatic_rebinning = cms.double(10.)")
    category_entries = jinja2.Template(category_template).render(categories = jobOptions['categories'])
    lines.append(
      "process.prepareDatacards.categories = cms.VPSet(%s\n)" % category_entries
    )
    lines.append(
      "process.prepareDatacards.sysShifts = cms.vstring(\n  %s,\n)" % \
      ',\n  '.join(map(lambda central_or_shift: "'%s'" % central_or_shift, self.central_or_shifts))
    )
    create_cfg(self.cfgFile_prep_dcard, jobOptions['cfgFile_modified'], lines)

  def addToMakefile_backgrounds(self, lines_makefile):
    max_input_files_per_job = 10 if len(self.central_or_shifts) == 1 else 5
    self.addToMakefile_hadd_stage1_5(lines_makefile, "phony_hadd_stage1_5", "phony_hadd_stage1", max_input_files_per_job)

  def addToMakefile_combine(self, lines_makefile):
    jobOptions = self.jobOptions_combine
    lines_makefile.append("%s: %s" % (jobOptions['outputFile'], jobOptions['inputFile']))
    lines_makefile.append("\tmake -f %s clean" % jobOptions['makefile_path'])
    lines_makefile.append("\tmake -f %s -j16 &> %s" % (jobOptions['makefile_path'], jobOptions['logFile']))
    lines_makefile.append("")
    self.filesToClean.append(jobOptions['outputFile'])

  def addToMakefile_comp_LeptonEfficiency(self, lines_makefile):
    for jobOptions in self.jobOptions_comp_LeptonEfficiency.values():
      lines_makefile.append("%s: %s" % (jobOptions['outputFile'], " ".join(jobOptions['inputFile'])))
      lines_makefile.append("\t%s %s" % (self.executable_comp_LeptonEfficiency, jobOptions['cfgFile_modified']))
      lines_makefile.append("")
      self.filesToClean.append(jobOptions['outputFile'])

  def addToMakefile_add_CERNSysts_LeptonEfficiency(self, lines_makefile): 
     for jobOptions in self.jobOptions_add_CERNSysts.values():
       lines_makefile.append("%s: %s" % (jobOptions['outputFile'], jobOptions['inputFile']))
       lines_makefile.append("\tpython %s -i %s -o %s -a %s -n %s" % (jobOptions['script'], jobOptions['inputFile'], jobOptions['outputFile'], jobOptions['mode'], jobOptions['useNorm']))
       lines_makefile.append("")
       self.filesToClean.append(jobOptions['outputFile'])

  def create(self):
    """Creates all necessary config files and runs the complete analysis workfow -- either locally or on the batch system
    """
    LFR_type = "HHorTTH"  

    for sample_name, sample_info in self.samples.items():
      if not sample_info["use_it"]:
        continue
      process_name = sample_info["process_name_specific"]
      sample_category = sample_info["sample_category"]
      is_mc = (sample_info["type"] == "mc")

      logging.info("Building dictionaries for sample %s..." % process_name)
      central_or_shift_extensions = ["", "hadd"]
      central_or_shifts_extended = central_or_shift_extensions + self.central_or_shifts
      for central_or_shift_or_dummy in central_or_shifts_extended:
        process_name_extended = [ process_name, "hadd" ]
        for process_name_or_dummy in process_name_extended:
          if central_or_shift_or_dummy in [ "hadd"] and process_name_or_dummy in [ "hadd" ]:
            continue  
          if central_or_shift_or_dummy != "central" and central_or_shift_or_dummy not in central_or_shift_extensions:
            if not is_mc:
              continue
            if not self.accept_central_or_shift(central_or_shift_or_dummy, sample_info):
              continue
          
          key_dir = getKey(process_name_or_dummy, central_or_shift_or_dummy)
          for dir_type in [ DKEY_CFGS, DKEY_HIST, DKEY_LOGS, DKEY_RLES ]:
            initDict(self.dirs, [ key_dir, dir_type ])
            if dir_type in [ DKEY_CFGS, DKEY_LOGS ]:
              self.dirs[key_dir][dir_type] = os.path.join(self.configDir, dir_type, self.channel, process_name_or_dummy, central_or_shift_or_dummy)
            else:
              self.dirs[key_dir][dir_type] = os.path.join(self.outputDir, dir_type, self.channel, process_name_or_dummy)
    for subdirectory in [ "prepareDatacards" ]:
      key_dir = getKey(subdirectory)
      for dir_type in [ DKEY_CFGS, DKEY_HIST, DKEY_LOGS, DKEY_DCRD, DKEY_PLOT ]:
        initDict(self.dirs, [ key_dir, dir_type ])
        if dir_type in [ DKEY_CFGS, DKEY_LOGS, DKEY_DCRD, DKEY_PLOT ]:
          self.dirs[key_dir][dir_type] = os.path.join(self.configDir, dir_type, self.channel, subdirectory)
        else:
          self.dirs[key_dir][dir_type] = os.path.join(self.outputDir, dir_type, self.channel, subdirectory)
    for dir_type in [ DKEY_CFGS, DKEY_SCRIPTS, DKEY_LOGS, DKEY_HIST, DKEY_DCRD, DKEY_PLOT, DKEY_HADD_RT, DKEY_COMBINE_OUTPUT ]:
      initDict(self.dirs, [ dir_type ])
      if dir_type in [ DKEY_CFGS, DKEY_SCRIPTS, DKEY_LOGS, DKEY_DCRD, DKEY_HADD_RT, DKEY_PLOT, DKEY_COMBINE_OUTPUT ]:
        self.dirs[dir_type] = os.path.join(self.configDir, dir_type, self.channel)
      else:
        self.dirs[dir_type] = os.path.join(self.outputDir, dir_type, self.channel)

    numDirectories = 0
    for key in self.dirs.keys():
      if type(self.dirs[key]) == dict:
        numDirectories += len(self.dirs[key])
      else:
        numDirectories += 1
    logging.info("Creating directory structure (numDirectories = %i)" % numDirectories)
    numDirectories_created = 0;
    frac = 1
    for key in self.dirs.keys():
      if type(self.dirs[key]) == dict:
        for dir_type in self.dirs[key].keys():
          create_if_not_exists(self.dirs[key][dir_type])
        numDirectories_created += len(self.dirs[key])
      else:
        create_if_not_exists(self.dirs[key])
        numDirectories_created = numDirectories_created + 1
      while 100*numDirectories_created >= frac*numDirectories:
        logging.info(" %i%% completed" % frac)
        frac = frac + 1
    logging.info("Done.")

    inputFileLists = {}
    for sample_name, sample_info in self.samples.items():
      if not sample_info["use_it"]:
        continue
      logging.info("Checking input files for sample %s" % sample_info["process_name_specific"])
      inputFileLists[sample_name] = generateInputFileList(sample_info, self.max_files_per_job)

    self.inputFileIds = {}
    for sample_name, sample_info in self.samples.items():
      if not sample_info["use_it"]:
        continue

      process_name = sample_info["process_name_specific"]

      logging.info("Creating configuration files to run '%s' for sample %s" % (self.executable_analyze, process_name))
      inputFileList = inputFileLists[sample_name]

      is_mc = (sample_info["type"] == "mc")
      sample_category = sample_info["sample_category"]

      for central_or_shift in self.central_or_shifts:
        if central_or_shift != "central" and not is_mc:
          continue

        # build config files for executing analysis code  
        key_analyze_dir = getKey(process_name, central_or_shift)

        for jobId in inputFileList.keys():

          analyze_job_tuple = (process_name, central_or_shift, jobId)
          key_analyze_job = getKey(*analyze_job_tuple)
          ntupleFiles = inputFileList[jobId]
          if len(ntupleFiles) == 0:
            logging.warning("No input ntuples for %s --> skipping job !!" % (key_analyze_job))
            continue

          rleOutputFile = os.path.join(
            self.dirs[key_analyze_dir][DKEY_RLES],
            "rle_{channel}_{process_name}_{central_or_shift}_{jobId}_%s_%s.txt".format(
              channel          = self.channel,
              process_name     = process_name,
              central_or_shift = central_or_shift,
              jobId            = jobId,
            )) if self.select_rle_output else ""

          cfgFile_modified_path = os.path.join(self.dirs[key_analyze_dir][DKEY_CFGS], "analyze_%s_%s_%i_cfg.py" % analyze_job_tuple)
          logFile_path          = os.path.join(self.dirs[key_analyze_dir][DKEY_LOGS], "analyze_%s_%s_%i.log" % analyze_job_tuple)
          histogramFile_path    = os.path.join(self.dirs[key_analyze_dir][DKEY_HIST], "analyze_%s_%s_%i.root" % analyze_job_tuple)
          self.jobOptions_analyze[key_analyze_job] = {
            'ntupleFiles'              : ntupleFiles,
            'cfgFile_modified'         : cfgFile_modified_path,
            'histogramFile'            : histogramFile_path,
            'selEventsFileName_output' : rleOutputFile,
            'logFile'                  : logFile_path,
            'absEtaBins_e'             : self.absEtaBins_e,
            'ptBins_e'                 : self.ptBins_e,
            'absEtaBins_mu'            : self.absEtaBins_mu,
            'ptBins_mu'                : self.ptBins_mu,
            'central_or_shift'         : central_or_shift,
            'fillGenEvtHistograms'     : self.fillGenEvtHistograms,
          }
          self.createCfg_analyze(self.jobOptions_analyze[key_analyze_job], sample_info)

          # initialize input and output file names for hadd_stage1
          key_hadd_stage1_dir = getKey(process_name)
          key_hadd_stage1_job = getKey(process_name)
          if not key_hadd_stage1_job in self.inputFiles_hadd_stage1:
            self.inputFiles_hadd_stage1[key_hadd_stage1_job] = []
          self.inputFiles_hadd_stage1[key_hadd_stage1_job].append(self.jobOptions_analyze[key_analyze_job]['histogramFile'])
          self.outputFile_hadd_stage1[key_hadd_stage1_job] = os.path.join(self.dirs[key_hadd_stage1_dir][DKEY_HIST],
                                                                          "hadd_stage1_%s.root" % process_name)

    # initialize input and output file names for hadd_stage2
    key_hadd_stage1_job = getKey(process_name)
    key_hadd_stage2_dir = getKey("hadd")
    key_hadd_stage2_job = getKey('')
    if not key_hadd_stage2_job in self.inputFiles_hadd_stage2:
      self.inputFiles_hadd_stage2[key_hadd_stage2_job] = []
    self.inputFiles_hadd_stage2[key_hadd_stage2_job].append(self.outputFile_hadd_stage1[key_hadd_stage1_job])
    self.outputFile_hadd_stage2[key_hadd_stage2_job] = os.path.join(self.dirs[key_hadd_stage2_dir][DKEY_HIST], "hadd_stage2.root")

    # We need to generate the eta and pt bins for electrons and muons
    lepton_bins = {}
    categories = []
    for lepton in ['electron', 'muon']:
      if ((self.lepton_type_string == 'e' and lepton == 'muon') 
          or (self.lepton_type_string == 'mu' and lepton == 'electron')):
        continue 

      if lepton not in lepton_bins:
        lepton_bins[lepton] = {}

      absEtaBins = None
      ptBins = None
      lepton_short = None
      if lepton == 'electron':
        absEtaBins = self.absEtaBins_e
        ptBins = self.ptBins_e
        lepton_short = 'e'
      elif lepton == 'muon':
        absEtaBins = self.absEtaBins_mu
        ptBins = self.ptBins_mu
        lepton_short = 'mu'
      else:
        raise ValueError('Invalid lepton type: %s' % lepton)
      for selection in ['tight', 'presel_not_tight']:
        if selection not in lepton_bins[lepton]:
          lepton_bins[lepton][selection] = []
        num_or_den = None
        if selection == 'tight':
          num_or_den = 'numerator'
        elif selection == 'presel_not_tight':
          num_or_den = 'denominator'
        else:
          raise ValueError('Invalid lepton selection: %s' % selection)
        for absEtaBin_idx in range(0, len(absEtaBins) - 1):
          absEtaBinLowerEdge = absEtaBins[absEtaBin_idx]
          absEtaBinUpperEdge = absEtaBins[absEtaBin_idx + 1]
          absEtaBinString = getEtaBin(absEtaBinLowerEdge, absEtaBinUpperEdge)
          for ptBin_idx in range(0, len(ptBins) - 1):
            ptBinsLowerEdge = ptBins[ptBin_idx]
            ptBinsUpperEdge = ptBins[ptBin_idx + 1]
            ptBinString = getPtBin(ptBinsLowerEdge, ptBinsUpperEdge)
            absEta_and_ptBinString = '%s_%s' % (absEtaBinString, ptBinString)

            lepton_bins[lepton][selection].append(
              construct_lepton_params(
                lepton, lepton_short, LFR_type, selection, absEta_and_ptBinString,
                error_msg = "No fit parameter range specified for abs(eta) range = (%.3f, %.3f) and "
                            "pT range = (%.3f, %.3f) for lepton type '%s' !!" % \
                            (absEtaBinLowerEdge, absEtaBinUpperEdge, ptBinsLowerEdge, ptBinsUpperEdge, lepton)
              ) + (absEtaBinLowerEdge, absEtaBinUpperEdge, ptBinsLowerEdge, ptBinsUpperEdge, 0)
            )

            categories.append(
              (
                "LeptonEfficiency/%s/%ss_%s/%s/%s" % (num_or_den, lepton, selection, absEtaBinString, ptBinString),
                "%ss_%s_%s_shapes" % (lepton, selection, absEta_and_ptBinString),
              )
            )

        # Let's also add inclusive category
        lepton_bins[lepton][selection].append(
          construct_lepton_params(
            lepton, lepton_short, LFR_type, selection, 'incl',
            error_msg = "No fit parameter range specified for lepton type %s" % lepton
          ) + (-1., -1., -1., -1., 1)
        )
        categories.append(
          (
            "LeptonEfficiency/%s/%ss_%s/incl" % (num_or_den, lepton, selection),
            "%ss_%s_incl_shapes" % (lepton, selection),
          )
        )
    lepton_bins_merged = []
    for lepton_type in lepton_bins:
      for lepton_selection in lepton_bins[lepton_type]:
        lepton_bins_merged.extend(lepton_bins[lepton_type][lepton_selection])

    if self.prep_dcard:
      logging.info("Creating configuration files to run 'prepareDatacards_LeptonEfficiency'")
      datacards = []
      for histogramToFit in self.histograms_to_fit:
        key_prep_dcard_dir = getKey("prepareDatacards")
        key_prep_dcard_job = getKey(histogramToFit)
        datacard = os.path.join(self.dirs[key_prep_dcard_dir][DKEY_DCRD], "prepareDatacards_%s.root" % (histogramToFit))
        self.jobOptions_prep_dcard[key_prep_dcard_job] = {
          'inputFile' : self.outputFile_hadd_stage2[key_hadd_stage2_job],
          'cfgFile_modified' : os.path.join(self.dirs[key_prep_dcard_dir][DKEY_CFGS], "prepareDatacards_LeptonEfficiency_%s_cfg.py" % histogramToFit),
          'datacardFile' : datacard,
          'histogramDir' : (self.histogramDir_prep_dcard),
          'histogramToFit' : histogramToFit,
          'label' : None,
          'categories' : categories,
        }
        datacards.append(datacard)
        self.createCfg_prep_dcard_LeptonEfficiency(self.jobOptions_prep_dcard[key_prep_dcard_job])

      # Create setupDatacards_LeptonEfficiency.py script from the template
      systematics_leptonFR = []
      for systematic in self.central_or_shifts:
        if systematic == 'central':
          continue
        systematic_name = systematic.replace('Up', '').replace('Down', '')
        if systematic_name not in systematics_leptonFR:
          systematics_leptonFR.append(systematic_name)
      setup_dcards_template_file = os.path.join(jinja_template_dir, 'setupDatacards_LeptonEfficiency.py.template')
      with open(setup_dcards_template_file, 'r') as setup_dcards_template_file_ptr:
        setup_dcards_template = setup_dcards_template_file_ptr.read()
      setup_dcards_script = jinja2.Template(setup_dcards_template).render(
        leptons           = lepton_bins_merged,
        central_or_shifts = systematics_leptonFR,
        signal_process    = self.sig_proc,
        era               = self.era, 
      )
      setup_dcards_script_path = os.path.join(self.dirs[DKEY_SCRIPTS], 'setupDatacards_LeptonEfficiency.py')
      logging.debug("writing setupDatacards_LeptonEfficiency script file = '%s'" % setup_dcards_script_path)
      with codecs.open(setup_dcards_script_path, "w", "utf-8") as setup_dcards_script_file:
        setup_dcards_script_file.write(setup_dcards_script)
        setup_dcards_script_file.flush()
        os.fsync(setup_dcards_script_file.fileno())
      add_chmodX(setup_dcards_script_path)

      postfit_plot_script_path = os.path.join(os.environ['CMSSW_BASE'], 'src/tthAnalysis/HiggsToTauTau/data/leptonIDEff/scripts/postFitPlot_fakes_from_mc.py')
      yieldtable_script_path   = os.path.join(os.environ['CMSSW_BASE'], 'src/tthAnalysis/HiggsToTauTau/data/leptonIDEff/scripts/yieldTable_fakes_from_mc.py')

      # Create run_postFit.sh script from the template
      combine_output_dir = os.path.join(self.dirs[DKEY_COMBINE_OUTPUT], 'output')
      postfit_template_file = os.path.join(jinja_template_dir, 'run_postFit.sh.template')
      with open(postfit_template_file, 'r') as postfit_template_file_ptr:
        postfit_template = postfit_template_file_ptr.read()
      for lepton in ['electron', 'muon']:
        if ((self.lepton_type_string == 'e' and lepton == 'muon') 
          or (self.lepton_type_string == 'mu' and lepton == 'electron')):
          continue
        for selection in ['presel_not_tight', 'tight']:
          is_num = selection == 'tight'
          for params in lepton_bins[lepton][selection]:
            l_array, l_range, l_sub_dir, l_eta_low, l_eta_high, l_pt_low, l_pt_high, l_is_inclusive = params
            postfit_script = jinja2.Template(postfit_template).render(
              new_cmssw_base         = self.cmssw_base_dir_combine,
              setup_dcards_script    = setup_dcards_script_path,
              postfit_plot_script    = postfit_plot_script_path,
              int_lumi_data          = self.lumi,
              yieldtable_script      = yieldtable_script_path,
              output_dir             = combine_output_dir,
              numerator_plotLabel    = self.numerator_plotLabel,
              denominator_plotLabel  = self.denominator_plotLabel,
              l_array                = l_array,
              l_range                = l_range,
              l_sub_dir              = l_sub_dir,
              l_eta_low              = l_eta_low,
              l_eta_high             = l_eta_high,
              l_pt_low               = l_pt_low,
              l_pt_high              = l_pt_high,
              l_is_inclusive         = l_is_inclusive,
              is_num                 = is_num,
              numerator_output_dir   = os.path.join(combine_output_dir, 'mlfit_LeptonEfficiency_%s' % self.numerator_histogram),
              denominator_output_dir = os.path.join(combine_output_dir, 'mlfit_LeptonEfficiency_%s' % self.denominator_histogram),
              selection              = selection,
              lepton_letter          = 'e' if lepton == 'electron' else 'mu',
              grep_value             = self.sig_proc,
            )
            postfit_script_path = os.path.join(
              self.dirs[DKEY_SCRIPTS],
              'mlfit_%s_%s.sh' % (self.numerator_histogram if is_num else self.denominator_histogram, l_array)
            )
            logging.debug("Writing run_postFit script file = '%s'" % postfit_script_path)
            with codecs.open(postfit_script_path, "w", "utf-8") as postfit_script_file:
              postfit_script_file.write(postfit_script)
              postfit_script_file.flush()
              os.fsync(postfit_script_file.fileno())
            add_chmodX(postfit_script_path)

      key_prep_dcard_dir = getKey("prepareDatacards")
      fit_value_file = os.path.join(combine_output_dir, 'fit_values.txt')
      makefile_template_file = os.path.join(jinja_template_dir, 'Makefile_postFit_%s.template' % self.lepton_type_string)
      makefile_template = open(makefile_template_file, 'r').read()
      makefile_templatized = jinja2.Template(makefile_template).render(
        new_cmssw_base = self.cmssw_base_dir_combine,
        setup_dcards_script = setup_dcards_script_path,
        numerator_histogram = self.numerator_histogram,
        denominator_histogram = self.denominator_histogram,
        scripts_dir = self.dirs[DKEY_SCRIPTS],
        numerator_datacard = os.path.join(self.dirs[key_prep_dcard_dir][DKEY_DCRD], "prepareDatacards_%s.root" % self.numerator_histogram),
        denominator_datacard = os.path.join(self.dirs[key_prep_dcard_dir][DKEY_DCRD], "prepareDatacards_%s.root" % self.denominator_histogram),
        output_dir = combine_output_dir,
        numerator_output_dir = os.path.join(combine_output_dir, 'mlfit_LeptonEfficiency_%s' % self.numerator_histogram),
        denominator_output_dir = os.path.join(combine_output_dir, 'mlfit_LeptonEfficiency_%s' % self.denominator_histogram),
        lepton_bins = lepton_bins,
        fit_values = fit_value_file,
      )
      makefile_path = os.path.join(self.dirs[DKEY_SCRIPTS], 'Makefile_postFit_%s' % self.lepton_type_string) 
      logging.debug("Writing run_postFit script file = '%s'" % makefile_path)
      with codecs.open(makefile_path, "w", "utf-8") as makefile_path_file:
        makefile_path_file.write(makefile_templatized)
        makefile_path_file.flush()
        os.fsync(makefile_path_file.fileno())

      self.jobOptions_combine = {
        'inputFile'       : ' '.join(datacards),
        'outputFile'      : fit_value_file,
        'makefile_path'   : makefile_path,
        'logFile'         : os.path.join(self.dirs[DKEY_LOGS], 'postFit.log'),
      }

      key_comp_LeptonEfficiency = getKey('')
      leptonFR_final_output = os.path.join(combine_output_dir, 'LeptonIDEfficiency_%s.root' % self.lepton_type_string)
      self.jobOptions_comp_LeptonEfficiency[key_comp_LeptonEfficiency] = {
        'inputFile'            : [ fit_value_file, self.outputFile_hadd_stage2[key_hadd_stage2_job] ],
        'outputFile'           : leptonFR_final_output,
        'absEtaBins_e'         : self.absEtaBins_e,
        'ptBins_e'             : self.ptBins_e,
        'absEtaBins_mu'        : self.absEtaBins_mu,
        'ptBins_mu'            : self.ptBins_mu,
        'logFile'              : os.path.join(self.dirs[DKEY_LOGS], os.path.basename(self.cfgFile_comp_LeptonEfficiency).replace('_cfg.py', '.log')),
        'cfgFile_modified'     : os.path.join(self.dirs[DKEY_CFGS], os.path.basename(self.cfgFile_comp_LeptonEfficiency)),
        'plots_outputFileName' : os.path.join(self.dirs[DKEY_PLOT], "comp_LeptonEfficiency_%s.png" % self.lepton_type_string)
      }
      self.createCfg_comp_LeptonEfficiency(self.jobOptions_comp_LeptonEfficiency[key_comp_LeptonEfficiency])
      self.targets.append(self.jobOptions_comp_LeptonEfficiency[key_comp_LeptonEfficiency]['outputFile'])


    self.sbatchFile_analyze = os.path.join(self.dirs[DKEY_SCRIPTS], "sbatch_analyze_LeptonEfficiency.py") 
    self.sbatchFile_comp_LeptonEfficiency = os.path.join(self.dirs[DKEY_SCRIPTS], "sbatch_comp_LeptonEfficiency.py")
    if self.is_sbatch:
      logging.info("Creating script for submitting '%s' jobs to batch system" % self.executable_analyze)
      self.createScript_sbatch_analyze(self.executable_analyze, self.sbatchFile_analyze, self.jobOptions_analyze)
      logging.info("Creating script for submitting '%s' jobs to batch system" % self.executable_comp_LeptonEfficiency)
      self.createScript_sbatch(self.executable_comp_LeptonEfficiency, self.sbatchFile_comp_LeptonEfficiency, self.jobOptions_comp_LeptonEfficiency)

    lines_makefile = []
    self.addToMakefile_analyze(lines_makefile)
    self.addToMakefile_hadd_stage1(lines_makefile)
    self.addToMakefile_hadd_stage2(lines_makefile, make_dependency = "phony_hadd_stage1")
    self.addToMakefile_prep_dcard(lines_makefile)
    self.addToMakefile_combine(lines_makefile)
    self.addToMakefile_comp_LeptonEfficiency(lines_makefile)
    self.createMakefile(lines_makefile)

    logging.info("Done.")

    return self.num_jobs



