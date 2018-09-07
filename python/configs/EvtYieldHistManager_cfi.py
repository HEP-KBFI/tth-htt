import FWCore.ParameterSet.Config as cms

EvtYieldHistManager_2016 = cms.PSet(
    Run2017B = cms.PSet(
        runRange = cms.string("273150-275376"),
        luminosity = cms.double(5.750)
    ),
    Run2017C = cms.PSet(
        runRange = cms.string("275656-276283"),
        luminosity = cms.double(2.573)
    ),
    Run2017D = cms.PSet(
        runRange = cms.string("276315-276811"),
        luminosity = cms.double(4.242)
    ),
    Run2017E = cms.PSet(
        runRange = cms.string("276831-277420"),
        luminosity = cms.double(4.025)
    ),
    Run2017F = cms.PSet(
        runRange = cms.string("277932-278808"),
        luminosity = cms.double(3.105)
    ),
    Run2017G = cms.PSet(
        runRange = cms.string("278820-280385"),
        luminosity = cms.double(7.576)
    ),
    Run2017H = cms.PSet(
        runRange = cms.string("281613-284044"),
        luminosity = cms.double(8.651)
    ),
)

EvtYieldHistManager_2017 = cms.PSet(
    Run2017B = cms.PSet(
        runRange = cms.string("297047-299329"),
        luminosity = cms.double(4.794)
    ),
    Run2017C = cms.PSet(
        runRange = cms.string("299368-302029"),
        luminosity = cms.double(9.631)
    ),
    Run2017D = cms.PSet(
        runRange = cms.string("302030-302663"),
        luminosity = cms.double(4.248)
    ),
    Run2017E = cms.PSet(
        runRange = cms.string("303818-304797"),
        luminosity = cms.double(9.314)
    ),
    Run2017F = cms.PSet(
        runRange = cms.string("305040-306462"),
        luminosity = cms.double(13.539)
    )
)
