import FWCore.ParameterSet.Config as cms

from tthAnalysis.HiggsToTauTau.configs.makePlots_mcClosure_cfi import process

def extend(isCR):
    if isCR:
        process.makePlots.distributions.extend([
            cms.PSet(
                histogramName = cms.string('sel/evt/$PROCESS/control'),
                xAxisTitle = cms.string('CR category'),
                yAxisTitle = cms.string('N')
            ),
        ])
    else:
        process.makePlots.distributions.extend([
            cms.PSet(
                histogramName = cms.string('sel/evt/$PROCESS/mass_4L'),
                xAxisTitle = cms.string('m_{4#ell}'),
                yAxisTitle = cms.string('dN/dm_{4#ell} [1/GeV]')
            ),
        ])
        process.makePlots.distributions.extend([
            cms.PSet(
                histogramName = cms.string('sel/evt/$PROCESS/mva_4l'),
                xAxisTitle = cms.string('MVA Discriminant'),
                yAxisTitle = cms.string('dN/dMVA')
            ),
        ])
