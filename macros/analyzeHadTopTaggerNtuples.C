
#include <TBenchmark.h>
#include <TFile.h>
#include <TH1.h>
#include <TMath.h>
#include <TROOT.h>
#include <TString.h>
#include <TSystem.h>
#include <TTree.h>

#include "TMVA/Factory.h"
#include "TMVA/Reader.h"
#include "TMVA/Tools.h"

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <iomanip>
#include <assert.h>
#include <math.h>
#include <limits>

void fillWithOverFlow(TH1* histogram, double x)
{
  TAxis* xAxis = histogram->GetXaxis();
  const double epsilon = 1.e-3;
  double xMin = xAxis->GetXmin() + epsilon;
  double xMax = xAxis->GetXmax() - epsilon;
  if ( x < xMin ) x = xMin;
  if ( x > xMax ) x = xMax;
  histogram->Fill(x);
}

void analyze(const std::string& sample, TFile* outputFile, const std::string& inputFilePath, const std::vector<std::string>& inputFileNames)
{
  std::cout << "<analyze>: processing sample = '" << sample << "'" << std::endl;

  TBenchmark clock;
  clock.Start("analyze");

  TDirectory* outputDir = outputFile->mkdir(sample.data());
  outputDir->cd();

  TH1* histogram_numTriplets = new TH1D("numTriplets", "numTriplets", 1000, -0.5, +999.5);

  TH1* histogram_mvaOutput_S = new TH1D("mvaOutput_S", "mvaOutput_S", 200, -1., +1.);
  TH1* histogram_mvaOutput_B = new TH1D("mvaOutput_B", "mvaOutput_B", 200, -1., +1.);
  TH1* histogram_max_mvaOutput_S = new TH1D("max_mvaOutput_S", "max_mvaOutput_S", 200, -1., +1.);
  TH1* histogram_max_mvaOutput_B = new TH1D("max_mvaOutput_B", "max_mvaOutput_B", 200, -1., +1.);

  TH1* histogram_CSV_b_S = new TH1D("CSV_b_S", "CSV_b_S", 200, -1., +1.);
  TH1* histogram_CSV_b_B = new TH1D("CSV_b_B", "CSV_b_B", 200, -1., +1.);

  TH1* histogram_nllKinFit_S = new TH1D("nllKinFit_S", "nllKinFit_S", 100, 0., 100.);
  TH1* histogram_nllKinFit_B = new TH1D("nllKinFit_B", "nllKinFit_B", 100, 0., 100.);

  for ( std::vector<std::string>::const_iterator inputFileName = inputFileNames.begin();
	inputFileName != inputFileNames.end(); ++inputFileName ) {
    std::string inputFileName_full = inputFilePath;
    if ( inputFileName_full.find_last_of("/") != (inputFileName_full.size() - 1) ) inputFileName_full.append("/");
    inputFileName_full.append(*inputFileName);
    TFile* inputFile = new TFile(inputFileName_full.data());
    if ( !inputFile ) {
      std::cerr << "Failed to open input file = '" << inputFileName_full << "' !!" << std::endl;
      assert(0);
    }

    std::string treeName = Form("analyze_hadTopTagger/evtntuple/%s/evtTree", sample.data());
    TTree* tree = dynamic_cast<TTree*>(inputFile->Get(treeName.data()));
    if ( !inputFile ) {
      std::cerr << "Failed to load tree = '" << treeName << "' from input file = '" << inputFileName_full << "' !!" << std::endl;
      assert(0);
    }

    UInt_t run;
    tree->SetBranchAddress("run", &run);
    UInt_t lumi;
    tree->SetBranchAddress("lumi", &lumi);
    ULong64_t evt;
    tree->SetBranchAddress("evt", &evt);

    Float_t CSV_Wj1;
    tree->SetBranchAddress("CSV_Wj1", &CSV_Wj1);
    Float_t CSV_b;
    tree->SetBranchAddress("CSV_b", &CSV_b);
    Float_t dR_Wj1Wj2;
    tree->SetBranchAddress("dR_Wj1Wj2", &dR_Wj1Wj2);
    Float_t dR_bW;
    tree->SetBranchAddress("dR_bW", &dR_bW);
    Float_t m_Wj1Wj2;
    tree->SetBranchAddress("m_Wj1Wj2", &m_Wj1Wj2);
    Float_t nllKinFit;
    tree->SetBranchAddress("nllKinFit", &nllKinFit);
    Float_t pT_Wj2;
    tree->SetBranchAddress("pT_Wj2", &pT_Wj2);
    Float_t pT_bWj1Wj2;
    tree->SetBranchAddress("pT_bWj1Wj2", &pT_bWj1Wj2);
    Float_t qg_Wj2;
    tree->SetBranchAddress("qg_Wj2", &qg_Wj2);

    Int_t b_isGenMatched;
    tree->SetBranchAddress("b_isGenMatched", &b_isGenMatched);
    Int_t bWj1Wj2_isGenMatched;
    tree->SetBranchAddress("bWj1Wj2_isGenMatched", &bWj1Wj2_isGenMatched);

    TMVA::Tools::Instance();
    TMVA::Reader* mva = new TMVA::Reader("!V:!Silent");
    mva->AddVariable("CSV_Wj1", &CSV_Wj1);
    mva->AddVariable("CSV_b", &CSV_b);
    mva->AddVariable("dR_Wj1Wj2", &dR_Wj1Wj2);
    mva->AddVariable("dR_bW", &dR_bW);
    mva->AddVariable("m_Wj1Wj2", &m_Wj1Wj2);
    mva->AddVariable("nllKinFit", &nllKinFit);
    mva->AddVariable("pT_Wj2", &pT_Wj2);
    mva->AddVariable("pT_bWj1Wj2", &pT_bWj1Wj2);
    mva->AddVariable("qg_Wj2", &qg_Wj2);
    std::string mvaFileName = "/home/veelken/VHbbNtuples_8_0_x/CMSSW_8_0_19/src/tthAnalysis/HiggsToTauTau/data/TMVABDT_hadTopTagger_maxDepth3_9Var_ttH.xml";
    mva->BookMVA("BDTG", mvaFileName.data());

    //const int maxEvents = -1;
    const int maxEvents = 10000000;

    Int_t last_run = -1;
    Int_t last_lumi = -1;
    Int_t last_evt = -1;
    int numJetTriplets = 0;
    Float_t max_mvaOutput = -1.e+3;
    Int_t max_mvaOutput_isGenMatched = false;

    int numEntries = tree->GetEntries();
    std::cout << "processing input file = '" << inputFileName_full << "' (" << numEntries << " entries)" << std::endl;
    for ( int idxEntry = 0; idxEntry < numEntries && (idxEntry < maxEvents || maxEvents == -1); ++idxEntry ) {
      if ( idxEntry > 0 && (idxEntry % 100000) == 0 ) {
	std::cout << " processing entry " << idxEntry << std::endl;
      }
    
      tree->GetEntry(idxEntry);

      double mvaOutput = mva->EvaluateMVA("BDTG");

      TH1* histogram_mvaOutput = 0;
      TH1* histogram_CSV_b = 0;
      TH1* histogram_nllKinFit = 0;
      if ( bWj1Wj2_isGenMatched ) {
	histogram_mvaOutput = histogram_mvaOutput_S;
	histogram_CSV_b = histogram_CSV_b_S;
	histogram_nllKinFit = histogram_nllKinFit_S;
      } else {
	histogram_mvaOutput = histogram_mvaOutput_B;
	histogram_CSV_b = histogram_CSV_b_B;
	histogram_nllKinFit = histogram_nllKinFit_B;
      }
      fillWithOverFlow(histogram_mvaOutput, mvaOutput);
      fillWithOverFlow(histogram_CSV_b, CSV_b);
      fillWithOverFlow(histogram_nllKinFit, nllKinFit);
      
      numJetTriplets++;
      if ( mvaOutput > max_mvaOutput ) {
	max_mvaOutput = mvaOutput;
	max_mvaOutput_isGenMatched = bWj1Wj2_isGenMatched;
      }

      if ( run != last_run || lumi != last_lumi || evt != last_evt ) {
	if ( !(last_run == -1 && lumi == -1 && evt == -1) ) {
	  fillWithOverFlow(histogram_numTriplets, numJetTriplets);
	  TH1* histogram_mvaOutput = 0;
	  if ( max_mvaOutput_isGenMatched ) histogram_mvaOutput = histogram_mvaOutput_S;
	  else histogram_mvaOutput = histogram_mvaOutput_B;
	  fillWithOverFlow(histogram_mvaOutput, max_mvaOutput);
	}	
	last_run = run;
	last_lumi = lumi;
	last_evt = evt;
	numJetTriplets = 0;
	max_mvaOutput = -1.e+3;
      }
    }

    TMVA::Tools::DestroyInstance();
    delete mva;

    delete inputFile;
  }

  outputDir->cd();
  histogram_numTriplets->Write();
  histogram_mvaOutput_S->Write();
  histogram_mvaOutput_B->Write();
  histogram_max_mvaOutput_S->Write();
  histogram_max_mvaOutput_B->Write();
  histogram_CSV_b_S->Write();
  histogram_CSV_b_B->Write();
  histogram_nllKinFit_S->Write();
  histogram_nllKinFit_B->Write();

  clock.Show("analyze");
}

void analyzeHadTopTaggerNtuples()
{
//--- stop ROOT from keeping references to all histograms
  TH1::AddDirectory(false);

//--- suppress the output canvas 
  gROOT->SetBatch(true);

  std::string inputFilePath = "/hdfs/local/veelken/ttHAnalysis/2016/2017Aug31/histograms/hadTopTagger/";

  std::vector<std::string> inputFiles_ttH;
  inputFiles_ttH.push_back("histograms_harvested_stage1_hadTopTagger_ttHToNonbb_fastsim_p1.root");
  inputFiles_ttH.push_back("histograms_harvested_stage1_hadTopTagger_ttHToNonbb_fastsim_p2.root");
  inputFiles_ttH.push_back("histograms_harvested_stage1_hadTopTagger_ttHToNonbb_fastsim_p3.root");

  std::vector<std::string> inputFiles_ttZ;
  inputFiles_ttZ.push_back("histograms_harvested_stage1_hadTopTagger_TTZToLLNuNu_fastsim.root");

  std::vector<std::string> inputFiles_ttW;
  inputFiles_ttW.push_back("histograms_harvested_stage1_hadTopTagger_TTWJetsToLNu_fastsim.root");

  std::vector<std::string> inputFiles_ttbar;
  inputFiles_ttbar.push_back("histograms_harvested_stage1_hadTopTagger_TTToSemilepton_fastsim_p1.root");
  inputFiles_ttbar.push_back("histograms_harvested_stage1_hadTopTagger_TTToSemilepton_fastsim_p2.root");
  inputFiles_ttbar.push_back("histograms_harvested_stage1_hadTopTagger_TTToSemilepton_fastsim_p3.root");

  TFile* outputFile = new TFile("analyzeHadTopTaggerNtuples.root", "RECREATE");

  analyze("signal", outputFile, inputFilePath, inputFiles_ttH);
  analyze("TTZ", outputFile, inputFilePath, inputFiles_ttZ);
  analyze("TTW", outputFile, inputFilePath, inputFiles_ttW);
  analyze("TT", outputFile, inputFilePath, inputFiles_ttbar);

  delete outputFile;
}
