import FWCore.ParameterSet.Config as cms

from tthAnalysis.HiggsToTauTau.configs.makePlots_cfi import process

process.makePlots.distributions.extend([
    cms.PSet(
        histogramName = cms.string("sel/evt/$PROCESS/mvaOutput_3l_ttV"),
        xAxisTitle = cms.string("MVA Discriminant (3l ttV)"),
        yAxisTitle = cms.string("dN/dMVA")
    ),
    cms.PSet(
        histogramName = cms.string("sel/evt/$PROCESS/mvaOutput_3l_ttbar"),
        xAxisTitle = cms.string("MVA Discriminant (3l tt)"),
        yAxisTitle = cms.string("dN/dMVA")
    ),
])

def extend(isCR):
    if isCR:
        for leptonTriplet in [ 'eee', 'eem', 'emm', 'mmm' ]:
            process.makePlots.distributions.extend([
                cms.PSet(
                    histogramName = cms.string('sel/evt/$PROCESS/control_{}'.format(leptonTriplet)),
                    xAxisTitle = cms.string('CR category ({})'.format(leptonTriplet)),
                    yAxisTitle = cms.string('N')
                ),
            ])
    else:
        for jetCount in [ "lj", "hj" ]:
            for chargeSum in [ "pos", "neg" ]:
                process.makePlots.distributions.extend([
                    cms.PSet(
                        histogramName = cms.string('sel/evt/$PROCESS/mass_3L_{}_{}'.format(jetCount, chargeSum)),
                        xAxisTitle = cms.string('m_{3#ell} (%s, %s)' % (jetCount, chargeSum)),
                        yAxisTitle = cms.string('dN/dm_{3#ell} [1/GeV]')
                    ),
                ])
        process.makePlots.distributions.extend([
            cms.PSet(
                histogramName = cms.string('sel/evt/$PROCESS/mass_3L_rest'),
                xAxisTitle = cms.string('m_{3#ell} (rest)'),
                yAxisTitle = cms.string('dN/dm_{3#ell} [1/GeV]')
            ),
        ])
        for bjet in [ 'bl', 'bt' ]:
            for leptonTriplet in [ 'eee', 'eem', 'emm', 'mmm' ]:
                if bjet == 'bt':
                    continue
                suffix = "{}_{}".format(leptonTriplet, bjet) if leptonTriplet != 'eee' else leptonTriplet
                process.makePlots.distributions.extend([
                    cms.PSet(
                        histogramName = cms.string('sel/evt/$PROCESS/output_NN_rest_{}'.format(suffix)),
                        xAxisTitle = cms.string('MVA Discriminant (rest, {}, {})'.format(leptonTriplet, bjet)),
                        yAxisTitle = cms.string('dN/dMVA')
                    ),
                ])
            for proc in [ 'ttH', 'tH' ]:
                process.makePlots.distributions.extend([
                    cms.PSet(
                        histogramName = cms.string('sel/evt/$PROCESS/output_NN_{}_{}'.format(proc, bjet)),
                        xAxisTitle = cms.string('MVA discriminant ({}, {})'.format(proc, bjet)),
                        yAxisTitle = cms.string('dN/dMVA')
                    ),
                ])
