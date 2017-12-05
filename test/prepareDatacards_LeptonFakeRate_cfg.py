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
        "TTW",
        "TTZ",
        "TT",
        "Rares",
        "fakes_data",
        "EWK",
        "tH",
        "TTWW",
        "ttH_hbb"
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
    histogramToFit_rebin = cms.int32(1),
    histogramToFit_makeBinContentsPositive = cms.bool(True),
    setBinsToZeroBelow = cms.double(-1.),

    sysShifts = cms.vstring(
      "central",
      "CMS_ttHl_JESUp",
      "CMS_ttHl_JESDown",
      "CMS_ttHl_JERUp",
      "CMS_ttHl_JERDown",
      "CMS_ttHl_UnclusteredEnUp",
      "CMS_ttHl_UnclusteredEnDown",
    )
)
