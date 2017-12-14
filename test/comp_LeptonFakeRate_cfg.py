import FWCore.ParameterSet.Config as cms

import os

process = cms.PSet()

#process.fwliteInput = cms.PSet(
#    fileNames = cms.vstring('/hdfs/local/ram/ttHAnalysis_LeptonFakeRate_trial_2017Nov4/2016/2017Nov4/histograms/LeptonFakeRate/histograms_harvested_stage2.root'),
#    fileNames = cms.vstring('histograms_harvested_stage2_LeptonFakeRate.root'),
#    maxEvents = cms.int32(-1),
#    outputEvery = cms.uint32(100000)
#)

process.fwliteOutput = cms.PSet(
    fileName = cms.string('comp_LeptonFakeRate.root')
)


process.comp_LeptonFakeRate = cms.PSet(
    inputfiles = cms.VPSet(
        cms.PSet(
            num_file = cms.string("fit_results_num_e_tight_absEta1_5to9_9_Pt45_0to65_0.txt"),
            den_file = cms.string("fit_results_den_e_fakeable_absEta1_5to9_9_Pt45_0to65_0.txt")
            ),
        cms.PSet(
            num_file = cms.string("fit_results_num_e_tight_absEta1_5to9_9_Pt20_0to30_0.txt"),
            den_file = cms.string("fit_results_den_e_fakeable_absEta1_5to9_9_Pt20_0to30_0.txt")
            ),
        cms.PSet(
            num_file = cms.string("fit_results_num_mu_tight_absEta1_5to9_9_Pt45_0to65_0.txt"),
            den_file = cms.string("fit_results_den_mu_fakeable_absEta1_5to9_9_Pt45_0to65_0.txt")
            ),
        cms.PSet(
            num_file = cms.string("fit_results_num_mu_tight_absEtaLt1_5_Pt10_0to15_0.txt"),
            den_file = cms.string("fit_results_den_mu_fakeable_absEtaLt1_5_Pt10_0to15_0.txt")
            )

#        cms.PSet(
#            num_file = cms.string("/home/ram/VHBB_NTUPLES_2017/CMSSW_7_4_7_CombineHarvestor/src/CombineHarvester/ttH_htt_LeptonFakeRate/output/mlfit_LeptonFakeRate_mT_fix_L/e_tight_absEta1_5to9_9_Pt45_0to65_0/fit_results_e_tight_absEta1_5to9_9_Pt45_0to65_0.txt"),
#            den_file = cms.string("/home/ram/VHBB_NTUPLES_2017/CMSSW_7_4_7_CombineHarvestor/src/CombineHarvester/ttH_htt_LeptonFakeRate/output/mlfit_LeptonFakeRate_EventCounter/e_fakeable_absEta1_5to9_9_Pt45_0to65_0/fit_results_den_e_fakeable_absEta1_5to9_9_Pt45_0to65_0.txt")
#        )
        ),
    absEtaBins_e = cms.vdouble(0., 1.479, 9.9),
    absEtaBins_mu = cms.vdouble(0., 1.479, 9.9),
    absPtBins_e = cms.vdouble(15., 20., 30., 45., 65., 100000.),
    absPtBins_mu = cms.vdouble(10., 15., 20., 30., 45., 65., 100000.)
    )

'''
### -------- MY STUFF ---------------- ###
process.comp_LeptonFakeRate = cms.PSet(

    looseRegion_mu = cms.string("LeptonFakeRate/denominator/muons_fakeable"),
    tightRegion_mu = cms.string("LeptonFakeRate/numerator/muons_tight"),
    looseRegion_e = cms.string("LeptonFakeRate/denominator/electrons_fakeable"),
    tightRegion_e = cms.string("LeptonFakeRate/numerator/electrons_tight"),

    process = cms.string("EWK"),
    isMC = cms.bool(True),
#    absEtaBins_e = cms.vdouble(1.0, 1.479, 9.9),
#    absEtaBins_mu = cms.vdouble(1.0, 1.479, 9.9),
#    absPtBins_e = cms.vdouble(20., 30., 100000.),
#    absPtBins_mu = cms.vdouble(10.,30.,100000.),

    absEtaBins_e  = cms.vdouble(0., 1.479, 9.9 ),
    absEtaBins_mu = cms.vdouble( 0., 1.479, 9.9 ),
    absPtBins_e   = cms.vdouble( 15., 20., 30., 45., 65., 100000. ),
    absPtBins_mu  = cms.vdouble(10., 15., 20., 30., 45., 65., 100000. ),



#    histogramName = cms.string("mT_fix_L"),
    histogramName = cms.string("pt"),
    processesToSubtract = cms.vstring(
#        "TTt",
#        "TTl", 
#        "EWK",
#        "Rares",
#        "TTW",
#        "TTZ",
#        "signal"
    ),
#    processData = cms.string("EWK"),
#    processMC = cms.string("TTj"),
#    hadTauSelections = cms.vstring(
        #"dR03mvaVLoose", # CV: Loose discriminator applied in denominator; cannot use looser discriminator in numerator
        #"dR03mvaLoose", # CV: Loose discriminator applied in denominator, so cannot be used in numerator
#        "dR03mvaMedium",
#        "dR03mvaTight",
#        "dR03mvaVTight",
#        "dR03mvaVVTight"
#    ),
#    absEtaBins = cms.vdouble(-1., 1.479, 9.9),
#    ptBins = cms.vdouble(20., 25., 30., 35., 40., 45., 50., 60., 70., 80., 100., 200.),
#    histogramsToFit = cms.vstring("hadTaus/pt"),
#    fitFunction = cms.string("[0] + [1]*x"),
#    xMin = cms.double(0.),
#    xMax = cms.double(200.)
)
## ------------ MY STUFF --------- ###
'''
