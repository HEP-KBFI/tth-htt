import FWCore.ParameterSet.Config as cms

# use full run range (instead of golden) and max recorded integrated luminosity per acquisition era
# sources:
# https://github.com/HEP-KBFI/tth-nanoAOD/blob/39eabfec8c21613c7133cff5ce197add27c433a6/test/datasets/txt/datasets_data_2016_17Jul18.txt
# https://github.com/HEP-KBFI/tth-nanoAOD/blob/39eabfec8c21613c7133cff5ce197add27c433a6/test/datasets/txt/datasets_data_2017_31Mar18.txt
# https://github.com/HEP-KBFI/tth-nanoAOD/blob/39eabfec8c21613c7133cff5ce197add27c433a6/test/datasets/txt/datasets_data_2018_17Sep18.txt

EvtYieldHistManager_2016 = cms.PSet(
    Run2016B = cms.PSet(
        runRange = cms.string("273150-275376"),
        luminosity = cms.double(5.750)
    ),
    Run2016C = cms.PSet(
        runRange = cms.string("275656-276283"),
        luminosity = cms.double(2.573)
    ),
    Run2016D = cms.PSet(
        runRange = cms.string("276315-276811"),
        luminosity = cms.double(4.242)
    ),
    Run2016E = cms.PSet(
        runRange = cms.string("276831-277420"),
        luminosity = cms.double(4.025)
    ),
    Run2016F = cms.PSet(
        runRange = cms.string("277932-278808"),
        luminosity = cms.double(3.105)
    ),
    Run2016G = cms.PSet(
        runRange = cms.string("278820-280385"),
        luminosity = cms.double(7.576)
    ),
    Run2016H = cms.PSet(
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
        luminosity = cms.double(9.633)
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
    ),
)

EvtYieldHistManager_2018 = cms.PSet(
    Run2018A = cms.PSet(
        runRange = cms.string("315257-316995"),
        luminosity = cms.double(14.027)
    ),
    Run2018B = cms.PSet(
        runRange = cms.string("317080-319310"),
        luminosity = cms.double(7.061)
    ),
    Run2018C = cms.PSet(
        runRange = cms.string("319337-320065"),
        luminosity = cms.double(6.895)
    ),
    Run2018D = cms.PSet(
        runRange = cms.string("320497-325175"),
        luminosity = cms.double(31.743)
    ),
)
