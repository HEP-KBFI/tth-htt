import FWCore.ParameterSet.Config as cms

EvtYieldHistManager_2017 = cms.PSet(
    runPeriods = cms.PSet(
        Run2017B = cms.PSet(
            runRange = cms.string("297047~299329"),
            luminosity = cms.double(4.79)
        ),
        Run2017C = cms.PSet(
            runRange = cms.string("299368~30202"),
            luminosity = cms.double(9.63)
        ),
        Run2017D = cms.PSet(
            runRange = cms.string("302030~302663"),
            luminosity = cms.double(4.25)
        ),
        Run2017E = cms.PSet(
            runRange = cms.string("303818~304797"),
            luminosity = cms.double(9.31)
        ),
        Run2017F = cms.PSet(
            runRange = cms.string("305040~306460"),
            luminosity = cms.double(13.54)
        )
    )
)
