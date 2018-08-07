import FWCore.ParameterSet.Config as cms

process = cms.PSet()

process.fwliteInput = cms.PSet(
    fileNames = cms.vstring(),
)

process.makePlots = cms.PSet(
    pluginType = cms.string("Plotter_ttH"),

    applyRebinning = cms.bool(True),
    apply_fixed_rebinning = cms.int32(2),
    apply_automatic_rebinning = cms.bool(True),
    minEvents_automatic_rebinning = cms.double(0.5),
    applyAutoBlinding = cms.bool(True),
    divideByBinWidth = cms.bool(False),
    processData = cms.string("data_obs"),
    processesBackground = cms.vstring(),
    processSignal = cms.string(""),
    categories = cms.VPSet(),
    distributions = cms.VPSet(
        cms.PSet(
            histogramName = cms.string("sel/evt/$PROCESS/numJets"),
            xAxisTitle = cms.string("jet Multiplicity"),
            yAxisTitle = cms.string("Events")
        ),
        cms.PSet(
            histogramName = cms.string("sel/evt/$PROCESS/numBJets_loose"),
            xAxisTitle = cms.string("loose b-jet Multiplicity"),
            yAxisTitle = cms.string("Events")
        ),
        cms.PSet(
            histogramName = cms.string("sel/evt/$PROCESS/numBJets_medium"),
            xAxisTitle = cms.string("medium b-jet Multiplicity"),
            yAxisTitle = cms.string("Events")
        ),
        cms.PSet(
            histogramName = cms.string("sel/evt/$PROCESS/numElectrons"),
            xAxisTitle = cms.string("electron Multiplicity"),
            yAxisTitle = cms.string("Events")
        ),
        cms.PSet(
            histogramName = cms.string("sel/evt/$PROCESS/numMuons"),
            xAxisTitle = cms.string("muon Multiplicity"),
            yAxisTitle = cms.string("Events")
        ),
        cms.PSet(
            histogramName = cms.string("sel/evtYield/$PROCESS/evtYield"),
            xAxisTitle = cms.string("Run Period"),
            yAxisTitle = cms.string("Events / 1 fb^{-1}")
        ),
    ),

    nuisanceParameters = cms.PSet(
        normalization = cms.PSet(
            signal = cms.string("1.0 +/- 0.20"),
            tHq = cms.string("1.0 +/- 0.20"),
            tHW = cms.string("1.0 +/- 0.20"),
            TT = cms.string("1.0 +/- 0.20"),
            TTW = cms.string("1.0 +/- 0.20"),
            TTWW = cms.string("1.0 +/- 0.20"),
            TTZ = cms.string("1.0 +/- 0.20"),
            EWK = cms.string("1.0 +/- 0.20"),
            Rares = cms.string("1.0 +/- 0.20"),
            conversions = cms.string("1.0 +/- 0.20"),
            fakes_data = cms.string("1.0 +/- 0.20"),
            flips_data = cms.string("1.0 +/- 0.20"),
            VH = cms.string("1.0 +/- 0.20"),
            WZ = cms.string("1.0 +/- 0.20"),
        ),
        shape = cms.PSet(
            CMS_ttHl_btag_HF = cms.string("0.00 +/- 1.00"),
            CMS_ttHl_btag_HFStats1 = cms.string("0.00 +/- 1.00"),
            CMS_ttHl_btag_HFStats2 = cms.string("0.00 +/- 1.00"),
            CMS_ttHl_btag_LF = cms.string("0.00 +/- 1.00"),
            CMS_ttHl_btag_LFStats1 = cms.string("0.00 +/- 1.00"),
            CMS_ttHl_btag_LFStats2 = cms.string("0.00 +/- 1.00"),
            CMS_ttHl_btag_cErr1 = cms.string("0.00 +/- 1.00"),
            CMS_ttHl_btag_cErr2 = cms.string("0.00 +/- 1.00"),
            CMS_ttHl_JES = cms.string("0.00 +/- 1.00"),
        )
    ),
    showUncertainty = cms.bool(False),

    labelOnTop = cms.string("CMS Preliminary; ttH, H #rightarrow #tau#tau; %1.1f fb^{-1} at #sqrt{s} = 13 TeV"),
    intLumiData = cms.double(0.), # in units of fb^-1

    outputFileName = cms.string("")
)
