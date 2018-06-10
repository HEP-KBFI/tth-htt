import FWCore.ParameterSet.Config as cms

import os

from tthAnalysis.HiggsToTauTau.configs.makePlots_cfi import process

process.makePlots.applyAutoBlinding = cms.bool(False)

process.makePlots.processesBackground = cms.vstring(
    "TT",
    "TTW",
    "TTZ",
    "signal",
    "EWK",
    "Rares"
)
process.makePlots.processSignal = cms.string("WZ")

process.makePlots.categories = cms.VPSet(
    cms.PSet(
        name = cms.string("WZctrl_2lepton"),
        label = cms.string("WZ control region")
    )
)

process.makePlots.distributions.extend([
    cms.PSet(
        histogramName = cms.string("sel/evt/$PROCESS/numElectrons"),
        xAxisTitle = cms.string("e Multiplicity"),
        yAxisTitle = cms.string("N")
    ),
    cms.PSet(
        histogramName = cms.string("sel/electrons/$PROCESS/pt"),
        xMin = cms.double(10.),
        xMax = cms.double(200.),
        xAxisTitle = cms.string("e p_{T} [GeV]"),
        yAxisTitle = cms.string("dN/dp_{T} [1/GeV]")
    ),
    cms.PSet(
        histogramName = cms.string("sel/electrons/$PROCESS/eta"),
        xAxisTitle = cms.string("e #eta"),
        yAxisTitle = cms.string("dN/d#eta")
    ),
    cms.PSet(
        histogramName = cms.string("sel/electrons/$PROCESS/phi"),
        xAxisTitle = cms.string("e #phi"),
        yAxisTitle = cms.string("dN/d#phi")
    ),
    cms.PSet(
        histogramName = cms.string("sel/electrons/$PROCESS/abs_genPdgId"),
        xAxisTitle = cms.string("e gen. Match"),
        xAxisOffset = cms.double(1.45),
        yAxisTitle = cms.string("N")
    ),
    cms.PSet(
        histogramName = cms.string("sel/electrons/$PROCESS/gen_times_recCharge"),
        xAxisTitle = cms.string("e gen. times rec. Charge"),
        xAxisOffset = cms.double(1.45),
        yAxisTitle = cms.string("N")
    ),
    cms.PSet(
        histogramName = cms.string("sel/evt/$PROCESS/numMuons"),
        xAxisTitle = cms.string("#mu Multiplicity"),
        yAxisTitle = cms.string("N")
    ),
    cms.PSet(
        histogramName = cms.string("sel/muons/$PROCESS/pt"),
        xMin = cms.double(10.),
        xMax = cms.double(200.),
        xAxisTitle = cms.string("#mu p_{T} [GeV]"),
        yAxisTitle = cms.string("dN/dp_{T} [1/GeV]")
    ),
    cms.PSet(
        histogramName = cms.string("sel/muons/$PROCESS/eta"),
        xAxisTitle = cms.string("#mu #eta"),
        yAxisTitle = cms.string("dN/d#eta")
    ),
    cms.PSet(
        histogramName = cms.string("sel/muons/$PROCESS/phi"),
        xAxisTitle = cms.string("#mu #phi"),
        yAxisTitle = cms.string("dN/d#phi")
    ),
    cms.PSet(
        histogramName = cms.string("sel/muons/$PROCESS/abs_genPdgId"),
        xAxisTitle = cms.string("#mu gen. Match"),
        xAxisOffset = cms.double(1.45),
        yAxisTitle = cms.string("N")
    ),
    cms.PSet(
        histogramName = cms.string("sel/evt/$PROCESS/numHadTaus"),
        xAxisTitle = cms.string("#tau_{h} Multiplicity"),
        yAxisTitle = cms.string("N")
    ),
    cms.PSet(
        histogramName = cms.string("sel/hadTaus/$PROCESS/pt"),
        xMin = cms.double(20.),
        xMax = cms.double(200.),
        xAxisTitle = cms.string("#tau_{h} p_{T} [GeV]"),
        yAxisTitle = cms.string("dN/dp_{T} [1/GeV]")
    ),
    cms.PSet(
        histogramName = cms.string("sel/hadTaus/$PROCESS/eta"),
        xAxisTitle = cms.string("#tau_{h} #eta"),
        yAxisTitle = cms.string("dN/d#eta")
    ),
    cms.PSet(
        histogramName = cms.string("sel/hadTaus/$PROCESS/phi"),
        xAxisTitle = cms.string("#tau_{h} #phi"),
        yAxisTitle = cms.string("dN/d#phi")
    ),
    cms.PSet(
        histogramName = cms.string("sel/hadTaus/$PROCESS/abs_genPdgId"),
        xAxisTitle = cms.string("#tau_{h} gen. match"),
        xAxisOffset = cms.double(1.45),
        yAxisTitle = cms.string("N")
    ),
    cms.PSet(
        histogramName = cms.string("sel/evt/$PROCESS/numJets"),
        xAxisTitle = cms.string("jet Multiplicity"),
        yAxisTitle = cms.string("N")
    ),
    cms.PSet(
        histogramName = cms.string("sel/jets/$PROCESS/pt"),
        xMin = cms.double(20.),
        xMax = cms.double(200.),
        xAxisTitle = cms.string("jet p_{T} [GeV]"),
        yAxisTitle = cms.string("dN/dp_{T} [1/GeV]")
    ),
    cms.PSet(
        histogramName = cms.string("sel/jets/$PROCESS/eta"),
        xAxisTitle = cms.string("jet #eta"),
        yAxisTitle = cms.string("dN/d#eta")
    ),
    cms.PSet(
        histogramName = cms.string("sel/jets/$PROCESS/phi"),
        xAxisTitle = cms.string("jet #phi"),
        yAxisTitle = cms.string("dN/d#phi")
    ),
    cms.PSet(
        histogramName = cms.string("sel/evt/$PROCESS/numBJets_loose"),
        xAxisTitle = cms.string("b-jet (loose) Multiplicity"),
        yAxisTitle = cms.string("N")
    ),
    cms.PSet(
        histogramName = cms.string("sel/BJets_loose/$PROCESS/pt"),
        xMin = cms.double(20.),
        xMax = cms.double(200.),
        xAxisTitle = cms.string("b-jet (loose) p_{T} [GeV]"),
        yAxisTitle = cms.string("dN/dp_{T} [1/GeV]")
    ),
    cms.PSet(
        histogramName = cms.string("sel/BJets_loose/$PROCESS/eta"),
        xAxisTitle = cms.string("b-jet (loose) #eta"),
        yAxisTitle = cms.string("dN/d#eta")
    ),
    cms.PSet(
        histogramName = cms.string("sel/BJets_loose/$PROCESS/phi"),
        xAxisTitle = cms.string("b-jet (loose) #phi"),
        yAxisTitle = cms.string("dN/d#phi")
    ),
    cms.PSet(
        histogramName = cms.string("sel/evt/$PROCESS/numBJets_medium"),
        xAxisTitle = cms.string("b-jet (medium) Multiplicity"),
        yAxisTitle = cms.string("N")
    ),
    cms.PSet(
        histogramName = cms.string("sel/BJets_medium/$PROCESS/pt"),
        xMin = cms.double(20.),
        xMax = cms.double(200.),
        xAxisTitle = cms.string("b-jet (medium) p_{T} [GeV]"),
        yAxisTitle = cms.string("dN/dp_{T} [1/GeV]")
    ),
    cms.PSet(
        histogramName = cms.string("sel/BJets_medium/$PROCESS/eta"),
        xAxisTitle = cms.string("b-jet (medium) #eta"),
        yAxisTitle = cms.string("dN/d#eta")
    ),
    cms.PSet(
        histogramName = cms.string("sel/BJets_medium/$PROCESS/phi"),
        xAxisTitle = cms.string("b-jet (medium) #phi"),
        yAxisTitle = cms.string("dN/d#phi")
    ),
    cms.PSet(
        histogramName = cms.string("sel/met/$PROCESS/met_pt"),
        xAxisTitle = cms.string("E_{T}^{miss} [GeV]"),
        yAxisTitle = cms.string("dN/dE_{T}^{miss} [1/GeV]")
    ),
    cms.PSet(
        histogramName = cms.string("sel/met/$PROCESS/met_phi"),
        xAxisTitle = cms.string("#phi^{miss}"),
        yAxisTitle = cms.string("dN/d#phi^{miss}")
    ),
    cms.PSet(
        histogramName = cms.string("sel/met/$PROCESS/met_LD"),
        xAxisTitle = cms.string("E_{T}^{miss} LD [GeV]"),
        yAxisTitle = cms.string("dN/dE_{T}^{miss} LD [1/GeV]")
    ),
    cms.PSet(
        histogramName = cms.string("sel/evt/$PROCESS/mLL"),
        xAxisTitle = cms.string("m_{ll} [GeV]"),
        yAxisTitle = cms.string("dN/dm_{ll} [1/GeV]")
    ),
    cms.PSet(
        histogramName = cms.string("sel/evt/$PROCESS/mT"),
        xAxisTitle = cms.string("m_{T} [GeV]"),
        yAxisTitle = cms.string("dN/dm_{T} [1/GeV]")
    ),
    cms.PSet(
        histogramName = cms.string("sel/evt/$PROCESS/mvaDiscr_2lss"),
        xAxisTitle = cms.string("MVA"),
        yAxisTitle = cms.string("dN/dMVA")
    ),
    cms.PSet(
        histogramName = cms.string("sel/evt/$PROCESS/mvaDiscr_3l"),
        xAxisTitle = cms.string("MVA"),
        yAxisTitle = cms.string("dN/dMVA")
    ),
    cms.PSet(            
        histogramName = cms.string("sel/mvaInputs_2lss_1tau/$PROCESS/lep1_pt"),
        xAxisTitle = cms.string("leading lepton p_{T} [GeV]"),
        yAxisTitle = cms.string("dN/dp_{T} [1/GeV]")
    ),
    cms.PSet(            
        histogramName = cms.string("sel/mvaInputs_2lss_1tau/$PROCESS/lep2_pt"),
        xAxisTitle = cms.string("subleading lepton p_{T} [GeV]"),
        yAxisTitle = cms.string("dN/dp_{T} [1/GeV]")
    ),
    cms.PSet(            
        histogramName = cms.string("sel/mvaInputs_2lss_1tau/$PROCESS/max_lep_eta"),
        xAxisTitle = cms.string("max. lepton #eta"),
        yAxisTitle = cms.string("dN/d#eta")
    ),
    cms.PSet(            
        histogramName = cms.string("sel/mvaInputs_2lss_1tau/$PROCESS/mindr_lep1_jet"),
        xAxisTitle = cms.string("min. #Delta R(leading lepton, jets)"),
        yAxisTitle = cms.string("dN/d#Delta R")
    ),
    cms.PSet(            
        histogramName = cms.string("sel/mvaInputs_2lss_1tau/$PROCESS/mindr_lep2_jet"),
        xAxisTitle = cms.string("min. #Delta R(subleading lepton, jets)"),
        yAxisTitle = cms.string("dN/d#Delta R")
    ),
    cms.PSet(            
        histogramName = cms.string("sel/mvaInputs_2lss_1tau/$PROCESS/avg_dr_jet"),
        xAxisTitle = cms.string("average #Delta R(jets)"),
        yAxisTitle = cms.string("dN/d#Delta R")
    ),
    cms.PSet(            
        histogramName = cms.string("sel/mvaInputs_2lss_1tau/$PROCESS/ptmiss"),
        xAxisTitle = cms.string("E_{T}^{miss} [GeV]"),
        yAxisTitle = cms.string("dN/dE_{T}^{miss} [1/GeV]")
    ),
    cms.PSet(            
        histogramName = cms.string("sel/mvaInputs_2lss_1tau/$PROCESS/mT_lep1"),
        xAxisTitle = cms.string("m_{T}(leading lepton, E_{T}^{miss}) [GeV]"),
        yAxisTitle = cms.string("dN/dm_{T} [1/GeV]")
    ),
    cms.PSet(            
        histogramName = cms.string("sel/mvaInputs_2lss_1tau/$PROCESS/htmiss"),
        xAxisTitle = cms.string("H_{T}^{miss} [GeV]"),
        yAxisTitle = cms.string("dN/dH_{T}^{miss} [1/GeV]")
    ),
    cms.PSet(            
        histogramName = cms.string("sel/mvaInputs_2lss_1tau/$PROCESS/dr_leps"),
        xAxisTitle = cms.string("#Delta R(leading lepton, subleading lepton)"),
        yAxisTitle = cms.string("dN/d#Delta R")
    ),
    cms.PSet(            
        histogramName = cms.string("sel/mvaInputs_2lss_1tau/$PROCESS/nJet"),
        xAxisTitle = cms.string("jet Multiplicity"),
        yAxisTitle = cms.string("N")
    ),
    cms.PSet(            
        histogramName = cms.string("sel/mvaInputs_2lss_1tau/$PROCESS/tau_pt"),
        xAxisTitle = cms.string("#tau_{h} p_{T} [GeV]"),
        yAxisTitle = cms.string("dN/dp_{T} [1/GeV]")
    ),
    cms.PSet(            
        histogramName = cms.string("sel/mvaInputs_2lss_1tau/$PROCESS/dr_lep1_tau"),
        xAxisTitle = cms.string("#Delta R(leading lepton, #tau_{h}) [GeV]"),
        yAxisTitle = cms.string("dN/d#Delta R")
    ),
    cms.PSet(            
        histogramName = cms.string("sel/mvaInputs_2lss_1tau/$PROCESS/mTauTauVis1"),
        xAxisTitle = cms.string("m_{vis}(leading lepton, #tau_{h}) [GeV]"),
        yAxisTitle = cms.string("dN/dm_{vis}")
    ),
    cms.PSet(            
        histogramName = cms.string("sel/mvaInputs_2lss_1tau/$PROCESS/mTauTauVis2"),
        xAxisTitle = cms.string("m_{vis}(leading lepton, #tau_{h}) [GeV]"),
        yAxisTitle = cms.string("dN/dm_{vis}")
    )
])

process.makePlots.nuisanceParameters.normalization.WZ = cms.string("1.0 +/- 0.20")
