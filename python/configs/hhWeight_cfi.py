import FWCore.ParameterSet.Config as cms

hhWeight = cms.PSet(
    denominator_file = cms.string(''),
    klScan_file = cms.string(''),
    ktScan_file = cms.string(''),
    c2Scan_file = cms.string(''),
    cgScan_file = cms.string(''),
    c2gScan_file = cms.string(''),
    coefFile = cms.string('HHStatAnalysis/AnalyticalModels/data/coefficientsByBin_extended_3M_costHHSim_19-4.txt'),
    histtitle = cms.string(''),
    isDEBUG = cms.bool(False),
    do_scan = cms.bool(True),
    do_ktscan = cms.bool(False),
    apply_rwgt = cms.bool(False),
    scanMode = cms.string('default'),
    apply_rwgt_LOtoNLO = cms.bool(False),
    apply_coupling_fix_Run2 = cms.bool(True)
)
