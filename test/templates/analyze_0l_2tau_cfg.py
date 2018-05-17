import FWCore.ParameterSet.Config as cms
import os

from tthAnalysis.HiggsToTauTau.recommendedMEtFilters_cfi import recommendedMEtFilters

process = cms.PSet()

process.fwliteInput = cms.PSet(
    fileNames = cms.vstring(''),
    maxEvents = cms.int32(-1),
    outputEvery = cms.uint32(100000)
)

process.fwliteOutput = cms.PSet(
    fileName = cms.string('analyze_0l_2tau.root')
)

process.analyze_0l_2tau = cms.PSet(
    treeName = cms.string('Events'),

    process = cms.string('ttH'),

    histogramDir = cms.string('0l_2tau_OS_Tight'),

    era = cms.string('2017'),

    triggers_2tau = cms.vstring(""),
    use_triggers_2tau = cms.bool(True),

    hadTauSelection = cms.string('Tight|dR03mvaTight'),
    hadTauChargeSelection = cms.string('OS'),
    apply_hadTauGenMatching = cms.bool(False),

    applyFakeRateWeights = cms.string("disabled"), # either "disabled", or "2tau"
    hadTauFakeRateWeight = cms.PSet(
        inputFileName = cms.string("tthAnalysis/HiggsToTauTau/data/FR_tau_2016.root"),
        lead = cms.PSet(
            absEtaBins = cms.vdouble(-1., 1.479, 9.9),
            graphName = cms.string("jetToTauFakeRate/$hadTauSelection/$etaBin/jetToTauFakeRate_mc_hadTaus_pt"),
            applyGraph = cms.bool(True),
            fitFunctionName = cms.string("jetToTauFakeRate/$hadTauSelection/$etaBin/fitFunction_data_div_mc_hadTaus_pt"),
            applyFitFunction = cms.bool(True)
        ),
        sublead = cms.PSet(
            absEtaBins = cms.vdouble(-1., 1.479, 9.9),
            graphName = cms.string("jetToTauFakeRate/$hadTauSelection/$etaBin/jetToTauFakeRate_mc_hadTaus_pt"),
            applyGraph = cms.bool(True),
            fitFunctionName = cms.string("jetToTauFakeRate/$hadTauSelection/$etaBin/fitFunction_data_div_mc_hadTaus_pt"),
            applyFitFunction = cms.bool(True)
        )
    ),

    triggerSF_2tau = cms.PSet(),

    isMC = cms.bool(False),
    central_or_shift = cms.string('central'),
    lumiScale = cms.double(1.),
    apply_trigger_bits = cms.bool(True),
    apply_hlt_filter = cms.bool(False),
    apply_met_filters = cms.bool(True),
    cfgMEtFilter = recommendedMEtFilters,

    fillGenEvtHistograms = cms.bool(False),

    branchName_electrons = cms.string('Electron'),
    branchName_muons = cms.string('Muon'),
    branchName_hadTaus = cms.string('Tau'),
    branchName_jets = cms.string('Jet'),
    branchName_met = cms.string('MET'),

    branchName_genLeptons = cms.string('GenLep'),
    branchName_genHadTaus = cms.string('GenVisTau'),
    branchName_genJets = cms.string('GenJet'),

    selEventsFileName_input = cms.string(''),
    selEventsFileName_output = cms.string(''),
    selectBDT = cms.bool(False),
    isDEBUG = cms.bool(False),
    hasLHE = cms.bool(True),
)

#--------------------------------------------------------------------------------
# CV: add data/MC corrections for efficiency of DoubleTau trigger
jsonFileName = os.path.expandvars("$CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/data/triggerSF/2016/trigger_sf_tt.json")
jsonFile = open(jsonFileName)
import json
jsonData = json.load(jsonFile)
##print "jsonData:"
##print jsonData
for fit, parameters in jsonData.items():
    ##print "fit = %s:" % fit
    pset = cms.PSet()
    for parameterName, parameterValue in parameters.items():
        ##print " %s = %1.2f" % (parameterName, parameterValue)
        setattr(pset, parameterName, cms.double(parameterValue))
    setattr(process.analyze_0l_2tau.triggerSF_2tau, fit, pset)
#--------------------------------------------------------------------------------

##processDumpFile = open('analyze_0l_2tau.dump', 'w')
##print >> processDumpFile, process.dumpPython()
