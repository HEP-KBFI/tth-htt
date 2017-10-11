
#include <TFile.h>
#include <TString.h>
#include <TH1.h>
#include <TMath.h>
#include <TROOT.h>
#include <TStyle.h>

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <iomanip>
#include <assert.h>

TH1* loadHistogram(TFile* inputFile, const std::string& histogramName)
{
  TH1* histogram = dynamic_cast<TH1*>(inputFile->Get(histogramName.data()));
  if ( !histogram ) {
    std::cerr << "Failed to load histogram = " << histogramName << " from file = " << inputFile->GetName() << " !!" << std::endl;
    assert(0);
  }
  if ( !histogram->GetSumw2N() ) histogram->Sumw2();
  return histogram;
}

void dumpEventYields()
{
  gROOT->SetBatch(true);

  TH1::AddDirectory(false);

  typedef std::vector<std::string> vstring;
  vstring channels;
  //channels.push_back("0l_2tau");
  //channels.push_back("1l_1tau");
  //channels.push_back("0l_3tau");
  //channels.push_back("1l_2tau");
  //channels.push_back("2lss_1tau");
  //channels.push_back("2los_1tau");
  channels.push_back("2l_2tau");
  //channels.push_back("3l_1tau_2jets");
  //channels.push_back("3l_1tau_1or2jets");

  std::string inputFilePath = "/home/veelken/ttHAnalysis/";
  //std::string inputFilePath = "/home/veelken/public/HIG16022_datacards/Tallinn/";
  std::map<std::string, std::string> inputFileNames; // key = channel
  inputFileNames["0l_2tau"] = "2016Aug15_dR03mvaTight/datacards/prepareDatacards_0l_2tau_mTauTauVis.root";
  inputFileNames["1l_1tau"] = "2016Aug15_dR03mvaVVTight/datacards/prepareDatacards_1l_1tau_numJets.root";
  inputFileNames["1l_2tau"] = "2016Aug15_dR03mvaVVTight/datacards/prepareDatacards_1l_2tau_mTauTauVis.root";
  inputFileNames["0l_3tau"] = "2016Aug15_dR03mvaTight/datacards/prepareDatacards_0l_3tau_mTauTauVis.root";
  inputFileNames["2lss_1tau"] = "2016Aug15_dR03mvaTight/datacards/prepareDatacards_2lss_1tau_mvaDiscr_2lss.root";
  inputFileNames["2los_1tau"] = "2016Aug15_dR03mvaVVTight/datacards/prepareDatacards_2los_1tau_mvaOutput_2los_1tau_ttbar.root";
  //inputFileNames["2l_2tau"] = "2016Aug15_dR03mvaTight/datacards/prepareDatacards_2l_2tau_mTauTauVis.root";
  inputFileNames["2l_2tau"] = "2016/2017Oct01_vTight/datacards/2l_2tau/prepareDatacards_2l_2tau_EventCounter.root";
  inputFileNames["3l_1tau_2jets"] = "ttH_3l_1tau_35.9fb_mvaDiscr_3l_2017Mar10.input.root";
  inputFileNames["3l_1tau_1or2jets"] = "ttH_3l_1tau_35.9fb_mvaDiscr_3l_2017Mar23_1or2jets.input.root";

  std::map<std::string, vstring> signal_processes; // key = channel
  signal_processes["0l_2tau"].push_back("ttH_htt");
  signal_processes["0l_2tau"].push_back("ttH_hww");
  signal_processes["0l_2tau"].push_back("ttH_hzz");
  signal_processes["1l_1tau"] = signal_processes["0l_2tau"];
  signal_processes["0l_3tau"] = signal_processes["0l_2tau"];
  signal_processes["1l_2tau"] = signal_processes["0l_2tau"];
  signal_processes["2lss_1tau"] = signal_processes["0l_2tau"];
  signal_processes["2los_1tau"] = signal_processes["0l_2tau"];
  signal_processes["2l_2tau"] = signal_processes["0l_2tau"];
  signal_processes["3l_1tau_2jets"] = signal_processes["0l_2tau"];
  signal_processes["3l_1tau_1or2jets"] = signal_processes["0l_2tau"];

  std::map<std::string, vstring> background_processes; // key = channel
  //background_processes["0l_2tau"].push_back("TT");
  background_processes["0l_2tau"].push_back("TTW");
  background_processes["0l_2tau"].push_back("TTWW");
  background_processes["0l_2tau"].push_back("TTZ");
  background_processes["0l_2tau"].push_back("EWK");
  background_processes["0l_2tau"].push_back("Rares");
  background_processes["0l_2tau"].push_back("fakes_data");
  background_processes["0l_2tau"].push_back("fakes_mc");
  background_processes["1l_1tau"] = background_processes["0l_2tau"];
  background_processes["0l_3tau"] = background_processes["0l_2tau"];
  background_processes["1l_2tau"] = background_processes["0l_2tau"];
  background_processes["2lss_1tau"].push_back("TTW");
  background_processes["2lss_1tau"].push_back("TTZ");
  background_processes["2lss_1tau"].push_back("WZ");
  background_processes["2lss_1tau"].push_back("Rares");
  background_processes["2lss_1tau"].push_back("fakes_data");
  background_processes["2lss_1tau"].push_back("flips_data");
  background_processes["2los_1tau"] = background_processes["0l_2tau"];
  background_processes["2l_2tau"] = background_processes["0l_2tau"];
  background_processes["3l_1tau_2jets"] = background_processes["0l_2tau"];
  background_processes["3l_1tau_1or2jets"] = background_processes["0l_2tau"];

  double lumi_datacard = 35.9;
  double lumi_projection = 35.9;
  double lumi_SF = lumi_projection/lumi_datacard;
  std::cout << "scaling signal and background yields to L=" << lumi_projection << "fb^-1 @ 13 TeV." << std::endl;

  for ( vstring::const_iterator channel = channels.begin();
	channel != channels.end(); ++channel ) {
    std::cout << "channel = " << (*channel) << std::endl;

    TString inputFileName_full = inputFilePath.data();
    if ( !inputFileName_full.EndsWith("/") ) inputFileName_full.Append("/");
    inputFileName_full.Append(inputFileNames[*channel].data());
    TFile* inputFile = new TFile(inputFileName_full.Data());
    if ( !inputFile ) {
      std::cerr << "Failed to open input file = " << inputFileName_full.Data() << " !!" << std::endl;
      assert(0);
    }

    for ( vstring::const_iterator signal_process = signal_processes[*channel].begin();
	  signal_process != signal_processes[*channel].end(); ++signal_process ) {
      std::string histogramName = Form("x_%s", signal_process->data());
      TH1* histogram = loadHistogram(inputFile, histogramName);
      histogram->Scale(lumi_SF);
      std::cout << " " << (*signal_process) << ": " << histogram->Integral() << std::endl;
    }

    for ( vstring::const_iterator background_process = background_processes[*channel].begin();
	  background_process != background_processes[*channel].end(); ++background_process ) {
      std::string histogramName = Form("x_%s", background_process->data());
      TH1* histogram = loadHistogram(inputFile, histogramName);
      histogram->Scale(lumi_SF);
      std::cout << " " << (*background_process) << ": " << histogram->Integral() << std::endl;
    }

    std::string histogramName = "x_data_obs";
    TH1* histogram = loadHistogram(inputFile, histogramName);
    histogram->Scale(lumi_SF);
    std::cout << " data_obs: " << histogram->Integral() << std::endl;

    std::cout << std::endl;

    delete inputFile;
  }
}

