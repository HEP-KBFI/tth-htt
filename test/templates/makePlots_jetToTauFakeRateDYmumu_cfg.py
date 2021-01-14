import FWCore.ParameterSet.Config as cms

from tthAnalysis.HiggsToTauTau.configs.makePlots_cfi import process

process.makePlots.distributions = cms.VPSet(
    cms.PSet(
        histogramName = cms.string("evt/$PROCESS/numMuons"),
        xAxisTitle = cms.string("#mu Multiplicity"),
        yAxisTitle = cms.string("N")
    ),
    cms.PSet(
    #     histogramName = cms.string("leadMuon/$PROCESS/cone_pt"),
    #     xMin = cms.double(10.),
    #     xMax = cms.double(200.),
    #     xAxisTitle = cms.string("#mu p_{T} [GeV]"),
    #     yAxisTitle = cms.string("dN/dp_{T} [1/GeV]")
    # ),
    # cms.PSet(
    #     histogramName = cms.string("leadMuon/$PROCESS/eta"),
    #     xAxisTitle = cms.string("#mu #eta"),
    #     yAxisTitle = cms.string("dN/d#eta")
    # ),
    # cms.PSet(
    #     histogramName = cms.string("leadMuon/$PROCESS/phi"),
    #     xAxisTitle = cms.string("#mu #phi"),
    #     yAxisTitle = cms.string("dN/d#phi")
    # ),
    # cms.PSet(
    #     histogramName = cms.string("subleadMuon/$PROCESS/cone_pt"),
    #     xMin = cms.double(10.),
    #     xMax = cms.double(200.),
    #     xAxisTitle = cms.string("#mu p_{T} [GeV]"),
    #     yAxisTitle = cms.string("dN/dp_{T} [1/GeV]")
    # ),
    # cms.PSet(
    #     histogramName = cms.string("subleadMuon/$PROCESS/eta"),
    #     xAxisTitle = cms.string("#mu #eta"),
    #     yAxisTitle = cms.string("dN/d#eta")
    # ),
    # cms.PSet(
    #     histogramName = cms.string("subleadMuon/$PROCESS/phi"),
    #     xAxisTitle = cms.string("#mu #phi"),
    #     yAxisTitle = cms.string("dN/d#phi")
    # ),
    cms.PSet(
        histogramName = cms.string("evt/$PROCESS/numJets"),
        xAxisTitle = cms.string("jet Multiplicity"),
        yAxisTitle = cms.string("N")
    ),
    cms.PSet(
        histogramName = cms.string("jets/$PROCESS/pt"),
        xMin = cms.double(20.),
        xMax = cms.double(200.),
        xAxisTitle = cms.string("jet p_{T} [GeV]"),
        yAxisTitle = cms.string("dN/dp_{T} [1/GeV]")
    ),
    cms.PSet(
        histogramName = cms.string("jets/$PROCESS/eta"),
        xAxisTitle = cms.string("jet #eta"),
        yAxisTitle = cms.string("dN/d#eta")
    ),
    cms.PSet(
        histogramName = cms.string("jets/$PROCESS/phi"),
        xAxisTitle = cms.string("jet #phi"),
        yAxisTitle = cms.string("dN/d#phi")
    ),
    cms.PSet(
        histogramName = cms.string("evt/$PROCESS/numBJets_loose"),
        xAxisTitle = cms.string("b-jet (loose) Multiplicity"),
        yAxisTitle = cms.string("N")
    ),
    cms.PSet(
        histogramName = cms.string("met/$PROCESS/met_pt"),
        xAxisTitle = cms.string("E_{T}^{miss} [GeV]"),
        yAxisTitle = cms.string("dN/dE_{T}^{miss} [1/GeV]")
    ),
    cms.PSet(
        histogramName = cms.string("met/$PROCESS/met_phi"),
        xAxisTitle = cms.string("#phi^{miss}"),
        yAxisTitle = cms.string("dN/d#phi^{miss}")
    ),
    cms.PSet(
        histogramName = cms.string("met/$PROCESS/met_LD"),
        xAxisTitle = cms.string("E_{T}^{miss} LD [GeV]"),
        yAxisTitle = cms.string("dN/dE_{T}^{miss} LD [1/GeV]")
    ),
    cms.PSet(
        histogramName = cms.string("evt/$PROCESS/m_ll"),
        xAxisTitle = cms.string("m_{ll} [GeV]"),
        yAxisTitle = cms.string("dN/dm_{ll} [1/GeV]")
    )
)

process.makePlots.nuisanceParameters.normalization = cms.PSet(
    ttH = cms.string("1.0 +/- 0.20"),
    TT = cms.string("1.0 +/- 0.20"),
    TTW = cms.string("1.0 +/- 0.20"),
    TTWW = cms.string("1.0 +/- 0.20"),
    TTZ = cms.string("1.0 +/- 0.20"),
    EWK = cms.string("1.0 +/- 0.20"),
    Rares = cms.string("1.0 +/- 0.20")
)
