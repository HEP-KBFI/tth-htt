import FWCore.ParameterSet.Config as cms

process = cms.PSet()

process.fwliteInput = cms.PSet(
    fileNames = cms.vstring()
)

process.fwliteOutput = cms.PSet(
    fileName = cms.string("")
)

process.prepareDatacards = cms.PSet(
    processesToCopy = cms.vstring(
        "data_obs",
        "fakes_data",
#        "TTWl_plus_t",
#        "TTZl_plus_t",
        "TTl_plus_t",
        "Raresl_plus_t",
        "EWKl_plus_t",
#        "TTWWl_plus_t",
#        "tHl_plus_t",
#        "ttH_hbbl_plus_t",
#        "signall_plus_t"
        "QCD",
    ),

    sf_signal = cms.double(1.),
    signals = cms.vstring(
        "signal",
    ),

    categories = cms.VPSet(),
    makeSubDir = cms.bool(True),

    histogramToFit = cms.string("mT_fix_L"),
    histogramToFit_xMin = cms.double(-1.),
    histogramToFit_xMax = cms.double(-1.),
    histogramToFit_rebin = cms.int32(1),
    histogramToFit_makeBinContentsPositive = cms.bool(True),

    sysShifts = cms.vstring(),
    apply_automatic_rebinning = cms.bool(False),
    minEvents_automatic_rebinning = cms.double(0.1),
    quantile_rebinning_in_fakes = cms.bool(False), ## THIS IS NOT APPLICABLE TO LEPTON FR STUDIES
    nbin_quantile_rebinning = cms.int32(0),
    explicit_binning = cms.vdouble()
)



