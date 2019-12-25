import FWCore.ParameterSet.Config as cms

from tthAnalysis.HiggsToTauTau.configs.makePlots_cfi import process

process.makePlots.distributions.extend([
    cms.PSet(
        histogramName = cms.string("sel/evt/$PROCESS/mvaOutput_2lss_ttV"),
        xAxisTitle = cms.string("MVA Discriminant (2lss ttV)"),
        yAxisTitle = cms.string("dN/dMVA")
    ),
    cms.PSet(
        histogramName = cms.string("sel/evt/$PROCESS/mvaOutput_2lss_ttbar"),
        xAxisTitle = cms.string("MVA Discriminant (2lss tt)"),
        yAxisTitle = cms.string("dN/dMVA")
    ),
    cms.PSet(
        histogramName = cms.string("sel/evt/$PROCESS/mvaDiscr_2lss"),
        xAxisTitle = cms.string("MVA Discriminant (2lss)"),
        yAxisTitle = cms.string("dN/dMVA")
    ),
    cms.PSet(
        histogramName = cms.string("sel/evt/$PROCESS/mvaOutput_Hj_tagger"),
        xAxisTitle = cms.string("MVA Discriminant (Hj)"),
        yAxisTitle = cms.string("dN/dMVA")
    ),
])

for dilept in [ 'ee', 'em', 'mm' ]:
    for category in [ 'ttH', 'ttW', 'rest', 'tH' ]:
        process.makePlots.distributions.append(
            cms.PSet(
                histogramName = cms.string("sel/evt/$PROCESS/output_NN_{}_{}".format(category, dilept)),
                xAxisTitle = cms.string("MVA Discriminant ({}, {})".format(category, dilept)),
                yAxisTitle = cms.string("dN/dMVA")
            )
        )
    for jetCount in [ 'lj', 'hj' ]:
        for chargeType in [ 'pos', 'neg' ]:
            process.makePlots.distributions.append(
                cms.PSet(
                    histogramName = cms.string("sel/evt/$PROCESS/mass_2L_{}_{}_{}".format(dilept, jetCount, chargeType)),
                    xAxisTitle = cms.string("m_{#ell#ell} (%s, %s, %s) [GeV]" % (dilept, jetCount, chargeType)),
                    yAxisTitle = cms.string("dN/dm_{#ell#ell} [1/GeV]")
                )
            )

