import FWCore.ParameterSet.Config as cms
import os

from tthAnalysis.HiggsToTauTau.analysisSettings import *

process = cms.PSet()

process.fwliteInput = cms.PSet(
    fileNames = cms.vstring(),
    maxEvents = cms.int32(-1),
    outputEvery = cms.uint32(100000)
)

process.fwliteOutput = cms.PSet(
    fileName = cms.string('')
)

process.analyze_genTopPt = cms.PSet(
    treeName = cms.string('Events'),

    process = cms.string('TT'),

    histogramDir = cms.string('unskimmed'),

    era = cms.string(''),

    isMC = cms.bool(True),
    lumiScale = cms.VPSet([
        cms.PSet(
            central_or_shift = cms.string('central'),
            lumi = cms.double(1.)
        )
    ]),
    apply_genWeight = cms.bool(True),
    apply_topPtReweighting = cms.bool(False),

    branchName_genTopQuarks = cms.string('GenTop'),

    hasLHE = cms.bool(True),

    evtWeight = cms.PSet(
        apply = cms.bool(False),
        histogramFile = cms.string(''),
        histogramName = cms.string(''),
        branchNameXaxis = cms.string(''),
        branchNameYaxis = cms.string(''),
        branchTypeXaxis = cms.string(''),
        branchTypeYaxis = cms.string(''),
    )
)

era = "2016"
#era = "2017"
#era = "2018"

inputFilePath = None
if   era == "2016":
    inputFilePath = "/hdfs/local/karl/ttHNtupleProduction/2016/2020Jan29_woPresel_nom_all/ntuples/TTTo2L2Nu/0000/"
elif era == "2017":
    inputFilePath = "/hdfs/local/karl/ttHNtupleProduction/2017/2020Jan29_woPresel_nom_all/ntuples/TTTo2L2Nu/0000/"
elif era == "2018":
    inputFilePath = "/hdfs/local/karl/ttHNtupleProduction/2018/2020Jan29_woPresel_nom_all/ntuples/TTTo2L2Nu/0000/"
else:
    raise ValueError("Invalid Configuration parameter 'era' = '%s' !!" % era)
maxInputFiles = -1
zombie_files = []
import os
def getInputFiles(inputFilePath):
    inputFiles = []
    files_and_subdirectories = os.listdir(inputFilePath)
    for file_or_subdirectory in files_and_subdirectories:
        if file_or_subdirectory in zombie_files:
            continue
        file_or_subdirectory = os.path.join(inputFilePath, file_or_subdirectory)
        if os.path.isfile(file_or_subdirectory):
            if file_or_subdirectory.endswith(".root"):
                inputFiles.append(file_or_subdirectory)
        if os.path.isdir(file_or_subdirectory):
            inputFiles.extend(getInputFiles(file_or_subdirectory))
    return inputFiles
inputFiles = getInputFiles(inputFilePath)
if maxInputFiles > 0:
    inputFiles = inputFiles[0:maxInputFiles]
process.fwliteInput.fileNames = cms.vstring(inputFiles)
print "inputFiles = ", process.fwliteInput.fileNames
process.fwliteOutput.fileName = cms.string("analyze_genTopPt_%s.root" % era)
process.analyze_genTopPt.era = era = cms.string(era)
