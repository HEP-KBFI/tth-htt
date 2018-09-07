import FWCore.ParameterSet.Config as cms

process = cms.PSet()

process.fwliteInput = cms.PSet(
    fileNames = cms.vstring(),
    maxEvents = cms.int32(-1),
    outputEvery = cms.uint32(10000)
)

process.fwliteOutput = cms.PSet(
    fileName = cms.string('')
)

process.write_csv = cms.PSet(
    treeName = cms.string("Events"),
    branches_to_write = cms.PSet(
        # CV: list of branches in input Ntuple that will be written to CSV output file
        #     in the format
        #       columnName = cms.string('expression'),
        #     where expression that can be any string understood by the TTreeFormula class of ROOT
        #...
    )
)
