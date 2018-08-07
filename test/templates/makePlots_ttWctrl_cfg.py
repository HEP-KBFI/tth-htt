import FWCore.ParameterSet.Config as cms

from tthAnalysis.HiggsToTauTau.configs.makePlots_cfi import process

process.makePlots.pluginType = cms.string("Plotter_ttH")
process.makePlots.applyRebinning = cms.bool(False)
process.makePlots.apply_automatic_rebinning = cms.bool(False)
process.makePlots.applyAutoBlinding = cms.bool(False)

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
        histogramName = cms.string("sel/evt/$PROCESS/sumLeptonPt"),
        xAxisTitle = cms.string("#Sigma lepton p_{T} [GeV]"),
        yAxisTitle = cms.string("dN/d#Sigma p_{T} [1/GeV]")
    ),
    cms.PSet(
        histogramName = cms.string("sel/evt/$PROCESS/mvaOutput_2lss_ttV"),
        xAxisTitle = cms.string("MVA Discriminant (2lss ttV)"),
        yAxisTitle = cms.string("dN/dMVA"),
    ),
    cms.PSet(
        histogramName = cms.string("sel/evt/$PROCESS/mvaOutput_2lss_ttbar"),
        xAxisTitle = cms.string("MVA Discriminant (2lss tt)"),
        yAxisTitle = cms.string("dN/dMVA"),
    ),
    cms.PSet(
        histogramName = cms.string("sel/evt/$PROCESS/mvaDiscr_2lss"),
        xAxisTitle = cms.string("MVA"),
        yAxisTitle = cms.string("dN/dMVA"),
    ),
    cms.PSet(
        histogramName = cms.string("sel/mvaInputs_2lss/$PROCESS/LepGood_conePt[iF_Recl[0]]"),
        xAxisTitle = cms.string("leading lepton p_{T} [GeV]"),
        yAxisTitle = cms.string("dN/dp_{T} [1/GeV]")
    ),
    cms.PSet(
        histogramName = cms.string("sel/mvaInputs_2lss/$PROCESS/LepGood_conePt[iF_Recl[1]]"),
        xAxisTitle = cms.string("subleading lepton p_{T} [GeV]"),
        yAxisTitle = cms.string("dN/dp_{T} [1/GeV]")
    ),
    cms.PSet(
        histogramName = cms.string("sel/mvaInputs_2lss/$PROCESS/max(abs(LepGood_eta[iF_Recl[0]]),abs(LepGood_eta[iF_Recl[1]]))"),
        xAxisTitle = cms.string("max. lepton #eta"),
        yAxisTitle = cms.string("dN/d#eta")
    ),
    cms.PSet(
        histogramName = cms.string("sel/mvaInputs_2lss/$PROCESS/mindr_lep1_jet"),
        xAxisTitle = cms.string("min. #Delta R(leading lepton, jets)"),
        yAxisTitle = cms.string("dN/d#Delta R")
    ),
    cms.PSet(
        histogramName = cms.string("sel/mvaInputs_2lss/$PROCESS/mindr_lep2_jet"),
        xAxisTitle = cms.string("min. #Delta R(subleading lepton, jets)"),
        yAxisTitle = cms.string("dN/d#Delta R")
    ),
    cms.PSet(
        histogramName = cms.string("sel/mvaInputs_2lss/$PROCESS/avg_dr_jet"),
        xAxisTitle = cms.string("average #Delta R(jets)"),
        yAxisTitle = cms.string("dN/d#Delta R")
    ),
    cms.PSet(
        histogramName = cms.string("sel/mvaInputs_2lss/$PROCESS/min(met_pt,400)"),
        xAxisTitle = cms.string("E_{T}^{miss} [GeV]"),
        yAxisTitle = cms.string("dN/dE_{T}^{miss} [1/GeV]")
    ),
    cms.PSet(
        histogramName = cms.string("sel/mvaInputs_2lss/$PROCESS/MT_met_lep1"),
        xAxisTitle = cms.string("m_{T}(leading lepton, E_{T}^{miss}) [GeV]"),
        yAxisTitle = cms.string("dN/dm_{T} [1/GeV]")
    ),
    cms.PSet(
        histogramName = cms.string("sel/mvaInputs_2lss/$PROCESS/nJet25_Recl"),
        xAxisTitle = cms.string("jet Multiplicity"),
        yAxisTitle = cms.string("N")
    )
])

process.makePlots.nuisanceParameters.normalization = cms.PSet(
    signal = cms.string("1.0 +/- 0.20"),
    TT = cms.string("1.0 +/- 0.20"),
    tHq = cms.string("1.0 +/- 0.20"),
    tHW = cms.string("1.0 +/- 0.20"),
    TTW = cms.string("1.0 +/- 0.20"),
    TTWW = cms.string("1.0 +/- 0.20"),
    TTZ = cms.string("1.0 +/- 0.20"),
    EWK = cms.string("1.0 +/- 0.20"),
    Rares = cms.string("1.0 +/- 0.20"),
    conversions = cms.string("1.0 +/- 0.20"),
    fakes_data = cms.string("1.0 +/- 0.20"),
    flips_data = cms.string("1.0 +/- 0.20")
)

