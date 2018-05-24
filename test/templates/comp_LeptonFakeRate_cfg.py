import FWCore.ParameterSet.Config as cms

process = cms.PSet()

process.fwliteInput = cms.PSet(
    fileNames = cms.vstring('/hdfs/local/karl/ttHAnalysis/2016/2017Dec05/histograms/LeptonFakeRate/histograms_harvested_stage2.root', '/home/veelken/VHbbNtuples_8_0_x/CMSSW_8_0_19/src/tthAnalysis/HiggsToTauTau/test/DEBUG/fit_values.txt'),
    maxEvents = cms.int32(-1),
    outputEvery = cms.uint32(100000)
)

process.fwliteOutput = cms.PSet(
    fileName = cms.string('comp_LeptonFakeRate.root')
)

process.comp_LeptonFakeRate = cms.PSet(

    histogramName_e = cms.string("FR_mva090_el_data_comb"),
    absEtaBins_e = cms.vdouble(0., 1.479, 9.9),
    ptBins_e = cms.vdouble(15., 20., 30., 45., 65., 100000.),

    histogramName_mu = cms.string("FR_mva090_mu_data_comb"),
    absEtaBins_mu = cms.vdouble(0., 1.479, 9.9),
    ptBins_mu = cms.vdouble(10., 15., 20., 30., 45., 65., 100000.),

    outputFileName = cms.string("plots/comp_LeptonFakeRate.png")
)
