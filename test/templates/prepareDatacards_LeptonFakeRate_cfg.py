import FWCore.ParameterSet.Config as cms

process = cms.PSet()

process.fwliteInput = cms.PSet(
    fileNames = cms.vstring("histograms_harvested_stage2.root")
)

process.fwliteOutput = cms.PSet(
    fileName = cms.string('prepareDatacards_mT_fix_L.root')
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
    ),

    sf_signal = cms.double(1.),
    signals = cms.vstring(
        "signal",
    ),

    categories = cms.VPSet(
        ## electrons and muons inclusive
        ### Electrons pT and eta bins
        ### Muons pT and eta bins
    ),
    makeSubDir = cms.bool(True),

    histogramToFit = cms.string("mT_fix_L"),
    histogramToFit_xMin = cms.double(-1.),
    histogramToFit_xMax = cms.double(-1.),
    histogramToFit_rebin = cms.int32(1),
    histogramToFit_makeBinContentsPositive = cms.bool(True),

    sysShifts = cms.vstring(
      "central",
      "CMS_ttHl_JESUp",
      "CMS_ttHl_JESDown",
      "CMS_ttHl_JERUp",
      "CMS_ttHl_JERDown",
      "CMS_ttHl_UnclusteredEnUp",
      "CMS_ttHl_UnclusteredEnDown",
    ),
    apply_automatic_rebinning = cms.bool(False),
    minEvents_automatic_rebinning = cms.double(0.1),
    quantile_rebinning_in_fakes = cms.bool(False), ## THIS IS NOT APPLICABLE TO LEPTON FR STUDIES
    nbin_quantile_rebinning = cms.int32(0),
    explicit_binning = cms.vdouble()
)



