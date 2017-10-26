
#include <TBenchmark.h>
#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
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

TMVA::Reader* bookMVA(const std::string& mvaFilePath, const std::string& mvaFileName,  
		      Float_t* CSV_Wj1, Float_t* CSV_b, Float_t* dR_Wj1Wj2, Float_t* dR_bW, Float_t* m_Wj1Wj2, Float_t* nllKinFit, Float_t* pT_Wj2, Float_t* pT_bWj1Wj2, Float_t* qg_Wj2)
{
  TMVA::Reader* mva = new TMVA::Reader("!V:!Silent");
  mva->AddVariable("CSV_Wj1", CSV_Wj1);
  mva->AddVariable("CSV_b", CSV_b);
  mva->AddVariable("dR_Wj1Wj2", dR_Wj1Wj2);
  mva->AddVariable("dR_bW", dR_bW);
  mva->AddVariable("m_Wj1Wj2", m_Wj1Wj2);
  mva->AddVariable("nllKinFit", nllKinFit);
  mva->AddVariable("pT_Wj2", pT_Wj2);
  mva->AddVariable("pT_bWj1Wj2", pT_bWj1Wj2);
  mva->AddVariable("qg_Wj2", qg_Wj2);
  std::string mvaFileName_full = mvaFilePath;
  if ( mvaFileName_full.back() != '/' ) mvaFileName_full.append("/");
  mvaFileName_full.append(mvaFileName);
  mva->BookMVA("BDTG", mvaFileName_full.data());
  return mva;
}

double evalMVA(TMVA::Reader* mva)
{
  double mvaOutput = mva->EvaluateMVA("BDTG");
  mvaOutput = -TMath::Log(0.5*(1 - mvaOutput) + 1.e-12);
  return mvaOutput;
}

TH1* bookHistogram1d(const std::string& histogramName, int numBinsX, double xMin, double xMax)
{
  TH1* histogram = new TH1D(histogramName.data(), histogramName.data(), numBinsX, xMin, xMax);
  return histogram;
}

TH2* bookHistogram2d(const std::string& histogramName, int numBinsX, double xMin, double xMax, int numBinsY, double yMin, double yMax)
{
  TH2* histogram = new TH2D(histogramName.data(), histogramName.data(), numBinsX, xMin, xMax, numBinsY, yMin, yMax);
  return histogram;
}

void fillWithOverFlow(TH1* histogram, double x)
{
  const double epsilon = 1.e-3;
  TAxis* xAxis = histogram->GetXaxis();
  double xMin = xAxis->GetXmin() + epsilon;
  double xMax = xAxis->GetXmax() - epsilon;
  if ( x < xMin ) x = xMin;
  if ( x > xMax ) x = xMax;
  histogram->Fill(x);
}

void fillWithOverFlow2d(TH2* histogram, double x, double y)
{
  const double epsilon = 1.e-3;
  TAxis* xAxis = histogram->GetXaxis();
  double xMin = xAxis->GetXmin() + epsilon;
  double xMax = xAxis->GetXmax() - epsilon;
  if ( x < xMin ) x = xMin;
  if ( x > xMax ) x = xMax;
  TAxis* yAxis = histogram->GetYaxis();
  double yMin = yAxis->GetXmin() + epsilon;
  double yMax = yAxis->GetXmax() - epsilon;
  if ( y < yMin ) y = yMin;
  if ( y > yMax ) y = yMax;
  histogram->Fill(x, y);
}

struct mvaHistogramType
{
  mvaHistogramType(const std::string& mvaName)
    : mvaName_(mvaName)
  {
    last_run_ = 0;
    last_lumi_ = 0;
    last_evt_ = 0;
    idxJetTriplet_ = 0;
    max_mvaOutput_ = -1.e+3;
    max_mvaOutput_idxGenMatching_ = -1;
    max_mvaOutput_idxJetTriplet_ = -1;
  }
  ~mvaHistogramType() {}
  void bookHistograms()
  {
    histogram_mvaOutput_S_ = bookHistogram1d(Form("mvaOutput_%s_S", mvaName_.data()), 1000, 0., 10.);
    histogram_mvaOutput_B_ = bookHistogram1d(Form("mvaOutput_%s_B", mvaName_.data()), 1000, 0., 10.);
    histogram_mvaOutput_vs_idxGenMatching_ = bookHistogram2d(Form("mvaOutput_%s_vs_idxGenMatching", mvaName_.data()), 9, -1.5, +7.5, 1000, 0., 10.);
    histogram_max_mvaOutput_S_ = bookHistogram1d(Form("max_mvaOutput_%s_S", mvaName_.data()), 1000, 0., 10.);
    histogram_max_mvaOutput_B_ = bookHistogram1d(Form("max_mvaOutput_%s_B", mvaName_.data()), 1000, 0., 10.);
    histogram_max_mvaOutput_vs_idxGenMatching_ = bookHistogram2d(Form("max_mvaOutput_%s_vs_idxGenMatching", mvaName_.data()), 9, -1.5, +7.5, 1000, 0., 10.); 
    histogram_max_mvaOutput_idxJetTriplet_ = bookHistogram1d(Form("max_mvaOutput_%s_idxJetTriplet", mvaName_.data()), 1001, -1.5, +999.5);
  }
  void fillHistograms(UInt_t run, UInt_t lumi, ULong64_t evt, double mvaOutput, int idxGenMatching)
  {
    TH1* histogram_mvaOutput = 0;
    if ( idxGenMatching == 7 ) {
      histogram_mvaOutput = histogram_mvaOutput_S_;
    } else {
      histogram_mvaOutput = histogram_mvaOutput_B_;
    }
    fillWithOverFlow(histogram_mvaOutput, mvaOutput);
    fillWithOverFlow2d(histogram_mvaOutput_vs_idxGenMatching_, idxGenMatching, mvaOutput);

    if ( mvaOutput > max_mvaOutput_ ) {
      max_mvaOutput_ = mvaOutput;
      max_mvaOutput_idxGenMatching_ = idxGenMatching;
      max_mvaOutput_idxJetTriplet_ = idxJetTriplet_;	
    }
    ++idxJetTriplet_;
    
    if ( run != last_run_ || lumi != last_lumi_ || evt != last_evt_ ) {
      if ( !(last_run_ == 0 && last_lumi_ == 0 && last_evt_ == 0) ) {
	TH1* histogram_max_mvaOutput = 0;
	if ( max_mvaOutput_idxGenMatching_ == 7 ) {
	  histogram_max_mvaOutput = histogram_max_mvaOutput_S_;
	} else {
	  histogram_max_mvaOutput = histogram_max_mvaOutput_B_;
	}
	fillWithOverFlow(histogram_max_mvaOutput, max_mvaOutput_);
	fillWithOverFlow2d(histogram_max_mvaOutput_vs_idxGenMatching_, max_mvaOutput_idxGenMatching_, max_mvaOutput_);
	fillWithOverFlow(histogram_max_mvaOutput_idxJetTriplet_, max_mvaOutput_idxJetTriplet_);
      }
      last_run_ = run;
      last_lumi_ = lumi;
      last_evt_ = evt;
      idxJetTriplet_ = 0;
      max_mvaOutput_ = -1.e+3;
      max_mvaOutput_idxGenMatching_ = -1;
      max_mvaOutput_idxJetTriplet_ = -1;
    }
  }
  void writeHistograms()
  {
    histogram_mvaOutput_S_->Write();
    histogram_mvaOutput_B_->Write();
    histogram_mvaOutput_vs_idxGenMatching_->Write();
    histogram_max_mvaOutput_S_->Write();
    histogram_max_mvaOutput_B_->Write();
    histogram_max_mvaOutput_vs_idxGenMatching_->Write();
    histogram_max_mvaOutput_idxJetTriplet_->Write();
  }
  std::string mvaName_;
  TH1* histogram_mvaOutput_S_;
  TH1* histogram_mvaOutput_B_;
  TH2* histogram_mvaOutput_vs_idxGenMatching_;
  TH1* histogram_max_mvaOutput_S_;
  TH1* histogram_max_mvaOutput_B_;
  TH2* histogram_max_mvaOutput_vs_idxGenMatching_;
  TH1* histogram_max_mvaOutput_idxJetTriplet_;
  UInt_t last_run_;
  UInt_t last_lumi_;
  ULong64_t last_evt_;
  Int_t idxJetTriplet_;
  Float_t max_mvaOutput_;
  Int_t max_mvaOutput_idxGenMatching_;
  Int_t max_mvaOutput_idxJetTriplet_;
};

void analyze(const std::string& sample, TFile* outputFile, const std::string& inputFilePath, const std::vector<std::string>& inputFileNames)
{
  std::cout << "<analyze>: processing sample = '" << sample << "'" << std::endl;

  TBenchmark clock;
  clock.Start("analyze");

  TDirectory* outputDir = outputFile->mkdir(sample.data());
  outputDir->cd();

  TH1* histogram_numTriplets = new TH1D("numTriplets", "numTriplets", 1000, -0.5, +999.5);
  TH1* histogram_numTriplets_genMatched = new TH1D("numTriplets_genMatched", "numTriplets_genMatched", 3, -0.5, +2.5);

  mvaHistogramType histograms_mva_old("old");
  histograms_mva_old.bookHistograms();
  mvaHistogramType histograms_mva_opt1("opt1");
  histograms_mva_opt1.bookHistograms();
  mvaHistogramType histograms_mva_opt2("opt2");
  histograms_mva_opt2.bookHistograms();
  mvaHistogramType histograms_mva_opt3("opt3");
  histograms_mva_opt3.bookHistograms();
  
  TH1* histogram_CSV_b_S = new TH1D("CSV_b_S", "CSV_b_S", 200, -1., +1.);
  TH1* histogram_CSV_b_B = new TH1D("CSV_b_B", "CSV_b_B", 200, -1., +1.);
  
  TH1* histogram_nllKinFit_S = new TH1D("nllKinFit_S", "nllKinFit_S", 100, 0., 100.);
  TH1* histogram_nllKinFit_B = new TH1D("nllKinFit_B", "nllKinFit_B", 100, 0., 100.);

  TH2* histogram_nllKinFit_vs_CSV_b_S = new TH2D("nllKinFit_vs_CSV_b_S", "nllKinFit_vs_CSV_b_S", 200, -1., +1., 100, 0., 100.);
  TH2* histogram_nllKinFit_vs_CSV_b_B = new TH2D("nllKinFit_vs_CSV_b_B", "nllKinFit_vs_CSV_b_B", 200, -1., +1., 100, 0., 100.);
    
  TH1* histogram_logPKinFit_S = new TH1D("logPKinFit_S", "logPKinFit_S", 200, -100., +100.);
  TH1* histogram_logPKinFit_B = new TH1D("logPKinFit_B", "logPKinFit_B", 200, -100., +100.);

  TH2* histogram_logPKinFit_vs_CSV_b_S = new TH2D("logPKinFit_vs_CSV_b_S", "logPKinFit_vs_CSV_b_S", 200, -1., +1., 200, -100., +100.);
  TH2* histogram_logPKinFit_vs_CSV_b_B = new TH2D("logPKinFit_vs_CSV_b_B", "logPKinFit_vs_CSV_b_B", 200, -1., +1., 200, -100., +100.);

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

    Float_t logPKinFit;
    tree->SetBranchAddress("logPKinFit", &logPKinFit);

    Int_t b_isGenMatched;
    tree->SetBranchAddress("b_isGenMatched", &b_isGenMatched);
    Int_t Wj1_isGenMatched;
    tree->SetBranchAddress("Wj1_isGenMatched", &Wj1_isGenMatched);
    Int_t Wj2_isGenMatched;
    tree->SetBranchAddress("Wj2_isGenMatched", &Wj2_isGenMatched);

    TMVA::Tools::Instance();
    std::string mvaFilePath = "/home/veelken/VHbbNtuples_8_0_x/CMSSW_8_0_19/src/tthAnalysis/HiggsToTauTau/data/";
    std::string mvaFileName_old = "TMVABDT_hadTopTagger_maxDepth3_9Var_ttH.xml";
    TMVA::Reader* mva_old = bookMVA(mvaFilePath, mvaFileName_old, &CSV_Wj1, &CSV_b, &dR_Wj1Wj2, &dR_bW, &m_Wj1Wj2, &nllKinFit, &pT_Wj2, &pT_bWj1Wj2, &qg_Wj2);
    std::string mvaFileName_opt1 = "hadTopTagger_BDTG_2017Oct10_opt1.xml";
    TMVA::Reader* mva_opt1 = bookMVA(mvaFilePath, mvaFileName_opt1, &CSV_Wj1, &CSV_b, &dR_Wj1Wj2, &dR_bW, &m_Wj1Wj2, &nllKinFit, &pT_Wj2, &pT_bWj1Wj2, &qg_Wj2);
    std::string mvaFileName_opt2 = "hadTopTagger_BDTG_2017Oct10_opt2.xml";
    TMVA::Reader* mva_opt2 = bookMVA(mvaFilePath, mvaFileName_opt2, &CSV_Wj1, &CSV_b, &dR_Wj1Wj2, &dR_bW, &m_Wj1Wj2, &nllKinFit, &pT_Wj2, &pT_bWj1Wj2, &qg_Wj2);
    std::string mvaFileName_opt3 = "hadTopTagger_BDTG_2017Oct10_opt3.xml";
    TMVA::Reader* mva_opt3 = bookMVA(mvaFilePath, mvaFileName_opt3, &CSV_Wj1, &CSV_b, &dR_Wj1Wj2, &dR_bW, &m_Wj1Wj2, &nllKinFit, &pT_Wj2, &pT_bWj1Wj2, &qg_Wj2);

    //const int maxEvents = -1;
    const int maxEvents = 100000000;

    UInt_t last_run = 0;
    UInt_t last_lumi = 0;
    ULong64_t last_evt = 0;
    int numJetTriplets = 0;
    int numJetTriplets_genMatched = 0;

    int numEntries = tree->GetEntries();
    std::cout << "processing input file = '" << inputFileName_full << "' (" << numEntries << " entries)" << std::endl;
    for ( int idxEntry = 0; idxEntry < numEntries && (idxEntry < maxEvents || maxEvents == -1); ++idxEntry ) {
      if ( idxEntry > 0 && (idxEntry % 100000) == 0 ) {
	std::cout << " processing entry " << idxEntry << std::endl;
      }
    
      tree->GetEntry(idxEntry);

      int idxGenMatching = 0;
      if ( b_isGenMatched   ) idxGenMatching += 4;
      if ( Wj1_isGenMatched ) idxGenMatching += 2;
      if ( Wj2_isGenMatched ) idxGenMatching += 1;

      TH1* histogram_CSV_b = 0;
      TH1* histogram_nllKinFit = 0;
      TH2* histogram_nllKinFit_vs_CSV_b = 0;
      TH1* histogram_logPKinFit = 0;
      TH2* histogram_logPKinFit_vs_CSV_b = 0;
      if ( idxGenMatching == 7 ) {
	histogram_CSV_b = histogram_CSV_b_S;
	histogram_nllKinFit = histogram_nllKinFit_S;
	histogram_nllKinFit_vs_CSV_b = histogram_nllKinFit_vs_CSV_b_S;
	histogram_logPKinFit = histogram_logPKinFit_S;
	histogram_logPKinFit_vs_CSV_b = histogram_logPKinFit_vs_CSV_b_S;
      } else {
	histogram_CSV_b = histogram_CSV_b_B;
	histogram_nllKinFit = histogram_nllKinFit_B;
	histogram_nllKinFit_vs_CSV_b = histogram_nllKinFit_vs_CSV_b_B;
	histogram_logPKinFit = histogram_logPKinFit_B;
	histogram_logPKinFit_vs_CSV_b = histogram_logPKinFit_vs_CSV_b_B;
      }
      fillWithOverFlow(histogram_CSV_b, CSV_b);
      fillWithOverFlow(histogram_nllKinFit, nllKinFit);
      fillWithOverFlow2d(histogram_nllKinFit_vs_CSV_b, CSV_b, nllKinFit);
      fillWithOverFlow(histogram_logPKinFit, logPKinFit);
      fillWithOverFlow2d(histogram_logPKinFit_vs_CSV_b, CSV_b, logPKinFit);

      double mvaOutput_old = evalMVA(mva_old);
      histograms_mva_old.fillHistograms(run, lumi, evt, mvaOutput_old, idxGenMatching);
      double mvaOutput_opt1 = evalMVA(mva_opt1);
      histograms_mva_opt1.fillHistograms(run, lumi, evt, mvaOutput_opt1, idxGenMatching);
      double mvaOutput_opt2 = evalMVA(mva_opt2);
      histograms_mva_opt2.fillHistograms(run, lumi, evt, mvaOutput_opt2, idxGenMatching);
      double mvaOutput_opt3 = evalMVA(mva_opt3);
      histograms_mva_opt3.fillHistograms(run, lumi, evt, mvaOutput_opt3, idxGenMatching);
      
      ++numJetTriplets;
      if ( idxGenMatching == 7 ) ++numJetTriplets_genMatched;

      if ( run != last_run || lumi != last_lumi || evt != last_evt ) {
	if ( !(last_run == 0 && last_lumi == 0 && last_evt == 0) ) {
	  fillWithOverFlow(histogram_numTriplets, numJetTriplets);
	  fillWithOverFlow(histogram_numTriplets_genMatched, numJetTriplets_genMatched);
	}	
	last_run = run;
	last_lumi = lumi;
	last_evt = evt;
	numJetTriplets = 0;
	numJetTriplets_genMatched = 0;
      }
    }

    TMVA::Tools::DestroyInstance();
    delete mva_old;
    delete mva_opt1;
    delete mva_opt2;
    delete mva_opt3;

    delete inputFile;
  }

  outputDir->cd();
  histogram_numTriplets->Write();
  histogram_numTriplets_genMatched->Write();
  histograms_mva_old.writeHistograms();
  histograms_mva_opt1.writeHistograms();
  histograms_mva_opt2.writeHistograms();
  histograms_mva_opt3.writeHistograms();
  histogram_CSV_b_S->Write();
  histogram_CSV_b_B->Write();
  histogram_nllKinFit_S->Write();
  histogram_nllKinFit_B->Write();
  histogram_nllKinFit_vs_CSV_b_S->Write();
  histogram_nllKinFit_vs_CSV_b_B->Write();
  histogram_logPKinFit_S->Write();
  histogram_logPKinFit_B->Write();
  histogram_logPKinFit_vs_CSV_b_S->Write();
  histogram_logPKinFit_vs_CSV_b_B->Write();
    
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
