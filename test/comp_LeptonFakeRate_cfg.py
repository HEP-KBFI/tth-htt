import FWCore.ParameterSet.Config as cms

import os

process = cms.PSet()

process.fwliteInput = cms.PSet(
    fileNames = cms.vstring('ZZTo4L_central_1.root'),
    
    maxEvents = cms.int32(-1),
    
    outputEvery = cms.uint32(100000)
)

process.fwliteOutput = cms.PSet(
    fileName = cms.string('comp_LeptonFakeRate.root')
)

process.comp_LeptonFakeRate = cms.PSet(

    looseRegion = cms.string("LeptonFakeRate/denominator/muons_fakeable/"),
    tightRegion = cms.string("LeptonFakeRate/numerator/muons_tight/"),
    process = cms.string("EWK"),

    absEtaBins_e = cms.vdouble(-1., 1.479, 9.9),
    absEtaBins_mu = cms.vdouble(-1., 1.479, 9.9),
    absPtBins_e = cms.vdouble(20., 30., 100000.),
    absPtBins_mu = cms.vdouble(10.,30.,100000.),


    isMC = cms.bool(True)



#    processData = cms.string("EWK"),
#    processesToSubtract = cms.vstring(
#        "TTt",
#        "TTl", 
#        "EWK",
#        "Rares",
#        "TTW",
#        "TTZ",
#        "signal"
#    ),

#    processMC = cms.string("TTj"),
#    hadTauSelections = cms.vstring(
        #"dR03mvaVLoose", # CV: Loose discriminator applied in denominator; cannot use looser discriminator in numerator
        #"dR03mvaLoose", # CV: Loose discriminator applied in denominator, so cannot be used in numerator
#        "dR03mvaMedium",
#        "dR03mvaTight",
#        "dR03mvaVTight",
#        "dR03mvaVVTight"
#    ),
#    absEtaBins = cms.vdouble(-1., 1.479, 9.9),
#    ptBins = cms.vdouble(20., 25., 30., 35., 40., 45., 50., 60., 70., 80., 100., 200.),



#    histogramsToFit = cms.vstring("hadTaus/pt"),

#    fitFunction = cms.string("[0] + [1]*x"),
#    xMin = cms.double(0.),
#    xMax = cms.double(200.)
)
