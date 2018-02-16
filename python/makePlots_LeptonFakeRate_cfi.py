import FWCore.ParameterSet.Config as cms

process = cms.PSet()

process.fwliteInput = cms.PSet(
    fileNames = cms.vstring(),
)

process.makePlots = cms.PSet(

    applyAutoBlinding = cms.bool(False),
    processData = cms.string("data_obs"),
    processesBackground = cms.vstring(
        "TTl_plus_t",
        "TTWl_plus_t",
        "TTZl_plus_t",
        "EWKl_plus_t",
        "Raresl_plus_t"
    ),
    processSignal = cms.string("signall_plus_t"),
    categories = cms.VPSet(
        cms.PSet(
            name = cms.string("LeptonFakeRate"),
            label = cms.string("Control_plot")
        )
    ),

    distributions = cms.VPSet(),
#    distributions = cms.VPSet(
#        cms.PSet(
#            histogramName = cms.string("denominator/electrons_fakeable/incl/$PROCESS/numElectrons"),
#            xAxisTitle = cms.string("e Multiplicity"),
#            yAxisTitle = cms.string("N")
#        ),
#        cms.PSet(
#            histogramName = cms.string("denominator/electrons_fakeable/incl/$PROCESS/pt"),
#            xMin = cms.double(10.),
#            xMax = cms.double(200.),
#            xAxisTitle = cms.string("e p_{T} [GeV]"),
#            yAxisTitle = cms.string("dN/dp_{T} [1/GeV]")
#        ),
#        cms.PSet(
#            histogramName = cms.string("denominator/electrons_fakeable/incl/$PROCESS/eta"),
#            xAxisTitle = cms.string("e #eta"),
#            yAxisTitle = cms.string("dN/d#eta")
#        ),
#        cms.PSet(
#            histogramName = cms.string("denominator/electrons_fakeable/incl/$PROCESS/phi"),
#            xAxisTitle = cms.string("e #phi"),
#            yAxisTitle = cms.string("dN/d#phi")
#        ),
#        cms.PSet(
#            histogramName = cms.string("denominator/electrons_fakeable/incl/$PROCESS/abs_genPdgId"),
#            xAxisTitle = cms.string("e gen. Match"),
#            xAxisOffset = cms.double(1.45),
#            yAxisTitle = cms.string("N")
#        ),
#        cms.PSet(
#            histogramName = cms.string("denominator/electron_fakeable/incl/$PROCESS/gen_times_recCharge"),
#            xAxisTitle = cms.string("e gen. times rec. Charge"),
#            xAxisOffset = cms.double(1.45),
#            yAxisTitle = cms.string("N")
#        ),
#        cms.PSet(
#            histogramName = cms.string("denominator/muons_fakeable/incl/$PROCESS/numMuons"),
#            xAxisTitle = cms.string("#mu Multiplicity"),
#            yAxisTitle = cms.string("N")
#        ),
#        cms.PSet(
#            histogramName = cms.string("denominator/muons_fakeable/incl/$PROCESS/pt"),
#            xMin = cms.double(10.),
#            xMax = cms.double(200.),
#            xAxisTitle = cms.string("#mu p_{T} [GeV]"),
#            yAxisTitle = cms.string("dN/dp_{T} [1/GeV]")
#        ),
#        cms.PSet(
#            histogramName = cms.string("denominator/muons_fakeable/incl/$PROCESS/eta"),
#            xAxisTitle = cms.string("#mu #eta"),
#            yAxisTitle = cms.string("dN/d#eta")
#        ),
#        cms.PSet(
#            histogramName = cms.string("denominator/muons_fakeable/incl/$PROCESS/phi"),
#            xAxisTitle = cms.string("#mu #phi"),
#            yAxisTitle = cms.string("dN/d#phi")
#        ),
#        cms.PSet(
#            histogramName = cms.string("denominator/muons_fakeable/incl/$PROCESS/abs_genPdgId"),
#            xAxisTitle = cms.string("#mu gen. Match"),
#            xAxisOffset = cms.double(1.45),
#            yAxisTitle = cms.string("N")
#        )
#    ),

    nuisanceParameters = cms.PSet(
        normalization = cms.PSet(
            signall_plus_t = cms.string("1.0 +/- 0.20"),
            TTl_plus_t = cms.string("1.0 +/- 0.20"),
            TTWl_plus_t = cms.string("1.0 +/- 0.20"),
            TTZl_plus_t = cms.string("1.0 +/- 0.20"),
            EWKl_plus_t = cms.string("1.0 +/- 0.20"),
#            fakes_data = cms.string("1.0 +/- 0.20"),
            Raresl_plus_t = cms.string("1.0 +/- 0.20")
        ),
        shape = cms.PSet()
#        shape = cms.PSet(
#            CMS_ttHl_btag_HF = cms.string("0.00 +/- 1.00"),
#            CMS_ttHl_btag_HFStats1 = cms.string("0.00 +/- 1.00"),
#            CMS_ttHl_btag_HFStats2 = cms.string("0.00 +/- 1.00"),
#            CMS_ttHl_btag_LF = cms.string("0.00 +/- 1.00"),
#            CMS_ttHl_btag_LFStats1 = cms.string("0.00 +/- 1.00"),
#            CMS_ttHl_btag_LFStats2 = cms.string("0.00 +/- 1.00"),
#            CMS_ttHl_btag_cErr1 = cms.string("0.00 +/- 1.00"),
#            CMS_ttHl_btag_cErr2 = cms.string("0.00 +/- 1.00"),
#            CMS_ttHl_JES = cms.string("0.00 +/- 1.00")
#        )
    ),
    showUncertainty = cms.bool(False),

    labelOnTop = cms.string("CMS Preliminary; ttH, H #rightarrow #tau#tau; %1.1f fb^{-1} at #sqrt{s} = 13 TeV"),    
    intLumiData = cms.double(35.9), # in units of fb^-1

    outputFileName = cms.string("makePlots.png")
)
