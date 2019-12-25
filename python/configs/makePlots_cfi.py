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
        cms.PSet(
            histogramName = cms.string('sel/met/$PROCESS/met_pt'),
            xAxisTitle = cms.string('E_{T}^{miss} [GeV]'),
            yAxisTitle = cms.string('dN/dE_{T}^{miss} [1/GeV]')
        ),
        cms.PSet(
            histogramName = cms.string('sel/met/$PROCESS/mht_pt'),
            xAxisTitle = cms.string('H_{T}^{miss} [GeV]'),
            yAxisTitle = cms.string('dN/dH_{T}^{miss} [1/GeV]')
        ),
        cms.PSet(
            histogramName = cms.string('sel/met/$PROCESS/met_LD'),
            xAxisTitle = cms.string('E_{T}^{miss}-LD [GeV]'),
            yAxisTitle = cms.string('dN/dE_{T}^{miss}-LD [1/GeV]')
        )
    ),

    nuisanceParameters = cms.PSet(
        normalization = cms.PSet(
            ttH = cms.string("1.0 +/- 0.20"),
            tHq = cms.string("1.0 +/- 0.20"),
            tHW = cms.string("1.0 +/- 0.20"),
            ggH = cms.string("1.0 +/- 0.20"),
            qqH = cms.string("1.0 +/- 0.20"),
            TT = cms.string("1.0 +/- 0.20"),
            DY = cms.string("1.0 +/- 0.20"),
            TTW = cms.string("1.0 +/- 0.20"),
            TTWW = cms.string("1.0 +/- 0.20"),
            TTZ = cms.string("1.0 +/- 0.20"),
            EWK = cms.string("1.0 +/- 0.20"),
            Rares = cms.string("1.0 +/- 0.20"),
            Convs = cms.string("1.0 +/- 0.20"),
            data_fakes = cms.string("1.0 +/- 0.20"),
            data_flips = cms.string("1.0 +/- 0.20"),
            VH = cms.string("1.0 +/- 0.20"),
            WW = cms.string("1.0 +/- 0.20"),
            WZ = cms.string("1.0 +/- 0.20"),
            ZZ = cms.string("1.0 +/- 0.20"),
            TTWH = cms.string("1.0 +/- 0.20"),
            TTZH = cms.string("1.0 +/- 0.20"),
            HH = cms.string("1.0 +/- 0.20"),
        ),
        shape = cms.PSet()
    ),
    showUncertainty = cms.bool(False),

    legendTextSize = cms.double(0.040),
    legendPosX = cms.double(0.700),
    legendPosY = cms.double(0.510),
    legendSizeX = cms.double(0.230),
    legendSizeY = cms.double(0.420),

    labelOnTop = cms.string("CMS Preliminary; ttH, H #rightarrow #tau#tau; %1.1f fb^{-1} at #sqrt{s} = 13 TeV"),
    intLumiData = cms.double(0.), # in units of fb^-1

    outputFileName = cms.string("")
)
