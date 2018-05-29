import FWCore.ParameterSet.Config as cms

process = cms.PSet()

process.fwliteInput = cms.PSet(
    fileNames = cms.vstring(),
)

process.makePlots = cms.PSet(

    applyRebinning = cms.bool(True),
    apply_fixed_rebinning = cms.int32(2),
    apply_automatic_rebinning = cms.bool(True),
    minEvents_automatic_rebinning = cms.double(0.5),
    applyAutoBlinding = cms.bool(True),
    divideByBinWidth = cms.bool(False),
    processData = cms.string("data_obs"),
    processesBackground = cms.vstring(
        ##"TT",
        "TTW",
        "TTWW",
        "TTZ",
        "EWK",
        "Rares",
        "conversions",
        "fakes_data"
    ),
    processSignal = cms.string("signal"),

    categories = cms.VPSet(
        cms.PSet(
            name = cms.string("2lss_1tau_SS_Tight"),
            label = cms.string("2lss_1tau")
        )
    ),

    distributions = cms.VPSet(
        cms.PSet(
            histogramName = cms.string("sel/evt/$PROCESS/numJets"),
            xAxisTitle = cms.string("jet Multiplicity"),
            yAxisTitle = cms.string("Events")
            ),
    ),

    nuisanceParameters = cms.PSet(
        normalization = cms.PSet(
            signal = cms.string("1.0 +/- 0.20"),
            tH = cms.string("1.0 +/- 0.20"),
            TT = cms.string("1.0 +/- 0.20"),
            TTW = cms.string("1.0 +/- 0.20"),
            TTWW = cms.string("1.0 +/- 0.20"),
            TTZ = cms.string("1.0 +/- 0.20"),
            EWK = cms.string("1.0 +/- 0.20"),
            Rares = cms.string("1.0 +/- 0.20"),
            conversions = cms.string("1.0 +/- 0.20"),
            fakes_data = cms.string("1.0 +/- 0.20"),
            VH = cms.string("1.0 +/- 0.20"),
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
            CMS_ttHl_JES = cms.string("0.00 +/- 1.00")
        )
    ),
    showUncertainty = cms.bool(False),

    labelOnTop = cms.string("CMS Preliminary; ttH, H #rightarrow #tau#tau; %1.1f fb^{-1} at #sqrt{s} = 13 TeV"),
    intLumiData = cms.double(41.5), # in units of fb^-1 #TODO make it era-dependent

    outputFileName = cms.string("plots/makePlots.png")
)
