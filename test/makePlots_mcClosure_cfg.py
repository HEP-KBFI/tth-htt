import FWCore.ParameterSet.Config as cms

import os

process = cms.PSet()

process.fwliteInput = cms.PSet(
    fileNames = cms.vstring(),
)

process.makePlots = cms.PSet(

    process_signal = cms.string("fakes_mc"),
    process_sideband = cms.string("fakes_mc"),
                                 
    categories = cms.VPSet(
        cms.PSet(
            signal = cms.string("1l_2tau_OS_Tight"),
            sideband = cms.string("1l_2tau_OS_Fakeable"),
            label = cms.string("1l_2tau")
        )
    ),

    distributions = cms.VPSet(
        cms.PSet(
            histogramName = cms.string("sel/evt/$PROCESS/numJets"),
            xAxisTitle = cms.string("jet Multiplicity"),
            yAxisTitle = cms.string("N")
        )     
    ),

    nuisanceParameters = cms.PSet(
        normalization = cms.PSet(
            fakes_mc = cms.string("1.0 +/- 0.00")
        ),
        shape = cms.PSet(
            CMS_ttHl_btag_HF = cms.string("0.00 +/- 1.00"),
            CMS_ttHl_btag_HFStats1 = cms.string("0.00 +/- 1.00"),
            CMS_ttHl_btag_HFStats2 = cms.string("0.00 +/- 1.00"),
            CMS_ttHl_btag_LF = cms.string("0.00 +/- 1.00"),
            CMS_ttHl_btag_LFStats1 = cms.string("0.00 +/- 1.00"),
            CMS_ttHl_btag_LFStats2 = cms.string("0.00 +/- 1.00"),
            CMS_ttHl_btag_cErr1 = cms.string("0.00 +/- 1.00"),
            CMS_ttHl_btag_cErr2 = cms.string("0.00 +/- 1.00"),
            CMS_ttHl_JES = cms.string("0.00 +/- 1.00")
        )
    ),
    showUncertainty = cms.bool(True),

    labelOnTop = cms.string("CMS Simulation; ttH, H #rightarrow #tau#tau; %1.1f fb^{-1} at #sqrt{s} = 13 TeV"),    
    intLumiData = cms.double(2.3), # in units of fb^-1

    outputFileName = cms.string("plots/makePlots_mcClosure.png")
)
