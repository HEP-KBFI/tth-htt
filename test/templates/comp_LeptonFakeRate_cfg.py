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

process.comp_LeptonFakeRate = cms.PSet(

    histogramName_e = cms.string(""),
    absEtaBins_e = cms.vdouble(),
    ptBins_e = cms.vdouble(),

    histogramName_mu = cms.string(""),
    absEtaBins_mu = cms.vdouble(),
    ptBins_mu = cms.vdouble(),

    processName = cms.string('QCD'),
    HistogramName_num = cms.string(''),
    Conversion_uncert = cms.double(0.50),

    outputFileName = cms.string(""),

    HistogramName_den = cms.string(''),
#    use_fakes_from_MC = cms.bool(False),
)
