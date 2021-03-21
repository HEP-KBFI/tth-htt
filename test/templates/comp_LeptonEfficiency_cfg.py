import FWCore.ParameterSet.Config as cms

process = cms.PSet()

process.fwliteInput = cms.PSet(
    fileNames = cms.vstring(),
    maxEvents = cms.int32(-1),
    outputEvery = cms.uint32(100000)
)

process.fwliteOutput = cms.PSet(
    fileName = cms.string('')
)

process.comp_LeptonEfficiency = cms.PSet(
    lepton_type = cms.string("e"),

    histogramName_e = cms.string(""),
    absEtaBins_e = cms.vdouble(),
    ptBins_e = cms.vdouble(),

    histogramName_mu = cms.string(""),
    absEtaBins_mu = cms.vdouble(),
    ptBins_mu = cms.vdouble(),

    processName = cms.string('DY_signal'),

    HistogramName_num = cms.string(''),
    HistogramName_den = cms.string(''),

    outputFileName = cms.string(""),
)
