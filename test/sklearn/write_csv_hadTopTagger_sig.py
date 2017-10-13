import FWCore.ParameterSet.Config as cms

process = cms.PSet()

#sampleName = 'signal'
sampleName = 'TT'
#sampleName = 'TTW'
#sampleName = 'TTZ'
#sampleName = 'EWK'

if sampleName == 'signal':
    outfile = 'hadTopTagger_ttH_09Oct2017_sig.csv'
    files = cms.vstring('/scratch/arun/mvaTraining/22Sep2017/histograms_harvested_stage1_hadTopTagger_ttHToNonbb_fastsim.root')
elif sampleName == 'TT':
    outfile = 'hadTopTagger_%s_09Oct2017_sig_p3.csv' %sampleName
    files = cms.vstring(
        '/scratch/arun/mvaTraining/22Sep2017/histograms_harvested_stage1_hadTopTagger_TTToSemilepton_fastsim.root'
        #'/hdfs/local/veelken/ttHAnalysis/2016/2017Aug31/histograms/hadTopTagger/histograms_harvested_stage1_hadTopTagger_TTToSemilepton_fastsim_p1.root',
        #'/hdfs/local/veelken/ttHAnalysis/2016/2017Aug31/histograms/hadTopTagger/histograms_harvested_stage1_hadTopTagger_TTToSemilepton_fastsim_p2.root',
        #'/hdfs/local/veelken/ttHAnalysis/2016/2017Aug31/histograms/hadTopTagger/histograms_harvested_stage1_hadTopTagger_TTToSemilepton_fastsim_p3.root'
        )
elif sampleName == 'TTZ':
    outfile = 'hadTopTagger_%s_09Oct2017_sig.csv' %sampleName
    files = cms.vstring('/hdfs/local/veelken/ttHAnalysis/2016/2017Aug31/histograms/hadTopTagger/histograms_harvested_stage1_hadTopTagger_TTZToLLNuNu_fastsim.root')
elif sampleName == 'TTW':
    outfile = 'hadTopTagger_%s_09Oct2017_sig.csv' %sampleName
    files = cms.vstring('/hdfs/local/veelken/ttHAnalysis/2016/2017Aug31/histograms/hadTopTagger/histograms_harvested_stage1_hadTopTagger_TTWJetsToLNu_fastsim.root')
inputTree = 'analyze_hadTopTagger/evtntuple/%s/evtTree' %sampleName


process.fwliteInput = cms.PSet(
    fileNames = files,
    ##maxEvents = cms.int32(100000),
    maxEvents = cms.int32(-1),
      
    outputEvery = cms.uint32(10000000)
)

process.fwliteOutput = cms.PSet(
    fileName = cms.string(outfile)
)

process.write_csv = cms.PSet(    

    treeName = cms.string(inputTree),
    #preselection = cms.string("(lep1_isTight>0.5) && (lep2_isTight>0.5) && (lep3_isTight>0.5) && (tau_isTight>0.5)"),
    preselection = cms.string("bWj1Wj2_isGenMatched>0.5"),
    prescale = cms.int32(3),
    branches_to_write = cms.PSet(
        # list of branches in input Ntuple that will be written to CSV output file
        CSV_Wj1=cms.string('CSV_Wj1/F'),
        CSV_Wj2=cms.string('CSV_Wj2/F'),
        CSV_b=cms.string('CSV_b/F'),
        alphaKinFit=cms.string('alphaKinFit/F'),
        dR_Wj1Wj2=cms.string('dR_Wj1Wj2/F'),
        dR_bW=cms.string('dR_bW/F'),
        dR_bWj1=cms.string('dR_bWj1/F'),
        dR_bWj2=cms.string('dR_bWj2/F'),
        logPErrKinFit=cms.string('logPErrKinFit/F'),
        logPKinFit=cms.string('logPKinFit/F'),
        m_Wj1Wj2=cms.string('m_Wj1Wj2/F'),
        m_Wj1Wj2_div_m_bWj1Wj2=cms.string('m_Wj1Wj2_div_m_bWj1Wj2/F'),
        m_bWj1=cms.string('m_bWj1/F'),
        m_bWj1Wj2=cms.string('m_bWj1Wj2/F'),
        m_bWj2=cms.string('m_bWj2/F'),
        max_dR_div_expRjet=cms.string('max_dR_div_expRjet/F'),
        nllKinFit=cms.string('nllKinFit/F'),
        pT_Wj1=cms.string('pT_Wj1/F'),
        pT_Wj1Wj2=cms.string('pT_Wj1Wj2/F'),
        pT_Wj2=cms.string('pT_Wj2/F'),
        pT_b=cms.string('pT_b/F'),
        pT_bWj1Wj2=cms.string('pT_bWj1Wj2/F'),
        qg_Wj1=cms.string('qg_Wj1/F'),
        qg_Wj2=cms.string('qg_Wj2/F'),
        qg_b=cms.string('qg_b/F'),
        statusKinFit=cms.string('statusKinFit/F'),
        bWj1Wj2_isGenMatched=cms.string('bWj1Wj2_isGenMatched/I')
        )
)
