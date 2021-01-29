
#include <TFile.h>
#include <TString.h>
#include <TH1.h>
#include <TH2.h>
#include <TGraph.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TMath.h>
#include <TROOT.h>
#include <TStyle.h>

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <iomanip>
#include <assert.h>

TFile* openFile(const std::string& inputFilePath, const std::string& inputFileName)
{
  TString inputFileName_full = inputFilePath.data();
  if ( !inputFileName_full.EndsWith("/") ) inputFileName_full.Append("/");
  inputFileName_full.Append(inputFileName.data());
  TFile* inputFile = new TFile(inputFileName_full.Data());
  if ( !inputFile ) {
    std::cerr << "Failed to open file = " << inputFileName_full.Data() << " !!" << std::endl;
    assert(0);
  }
  return inputFile;
}

TH1* loadHistogram(TFile* inputFile, const std::string& directoryName, const std::string& histogramName)
{
  TString histogramName_full = directoryName.data();
  if ( !histogramName_full.EndsWith("/") ) histogramName_full.Append("/");
  histogramName_full.Append(histogramName.data());
  std::cout << "loading histogram = " << histogramName_full.Data() << " from file = " << inputFile->GetName() << std::endl;
  TH1* histogram = dynamic_cast<TH1*>(inputFile->Get(histogramName_full.Data()));
  std::cout << "histogram = " << histogram << std::endl;
  if ( !histogram ) {
    std::cerr << "Failed to load histogram = " << histogramName_full << " from file = " << inputFile->GetName() << " !!" << std::endl;
    assert(0);
  }
  if ( !histogram->GetSumw2N() ) histogram->Sumw2();
  return histogram;
}

void
showHistogram2d(double canvasSizeX,
                double canvasSizeY,
                TH2* histogram,
                const std::string& outputFileName)
{
  TCanvas* canvas = new TCanvas("canvas", "canvas", canvasSizeX, canvasSizeY);
  canvas->SetFillColor(10);
  canvas->SetBorderSize(2);
  canvas->SetLeftMargin(0.18);
  canvas->SetTopMargin(0.05);
  canvas->SetRightMargin(0.05);
  canvas->SetBottomMargin(0.15);

  histogram->SetTitle("");
  histogram->SetStats(false);

  gStyle->SetPaintTextFormat("1.4f");

  histogram->Draw("TEXT");
  
  canvas->Update();
  const std::size_t idx = outputFileName.find_last_of('.');
  std::string outputFileName_plot(outputFileName, 0, idx);
  canvas->Print(std::string(outputFileName_plot).append(std::string(outputFileName, idx)).data());
  canvas->Print(std::string(outputFileName_plot).append(".png").data());
  canvas->Print(std::string(outputFileName_plot).append(".pdf").data());
  
  delete canvas;  
}

void
fillWithOverFlow(TH1 * histogram,
                 double x,
                 double evtWeight = 1.)
{
  if ( !histogram ) return;
  const TAxis* xAxis = histogram->GetXaxis();
  double x_constrained = x;
  const double epsilon = 1.e-3;
  if ( x_constrained > (xAxis->GetXmax() - epsilon) ) x_constrained = xAxis->GetXmax() - epsilon;
  if ( x_constrained < (xAxis->GetXmin() + epsilon) ) x_constrained = xAxis->GetXmin() + epsilon;
  histogram->Fill(x_constrained, evtWeight);
}

void
showHistogram1d(double canvasSizeX,
                double canvasSizeY,
                TH1* histogram,
                const std::string& outputFileName)
{
  TCanvas* canvas = new TCanvas("canvas", "canvas", canvasSizeX, canvasSizeY);
  canvas->SetFillColor(10);
  canvas->SetBorderSize(2);
  canvas->SetLeftMargin(0.12);
  canvas->SetTopMargin(0.05);
  canvas->SetRightMargin(0.05);
  canvas->SetBottomMargin(0.12);

  histogram->SetTitle("");
  histogram->SetStats(true);

  TAxis* xAxis = histogram->GetXaxis();
  xAxis->SetTitle("r_{data} - r_{mc}");
  xAxis->SetTitleOffset(1.5);

  TAxis* yAxis = histogram->GetYaxis();
  yAxis->SetTitle("Pairs of observables");
  yAxis->SetTitleOffset(1.65);

  histogram->SetMarkerColor(1);
  histogram->SetMarkerStyle(8);
  histogram->SetMarkerSize(2);
  histogram->SetLineColor(1);
  histogram->SetLineWidth(1);

  histogram->Draw("e1p");
  
  canvas->Update();
  const std::size_t idx = outputFileName.find_last_of('.');
  std::string outputFileName_plot(outputFileName, 0, idx);
  canvas->Print(std::string(outputFileName_plot).append(std::string(outputFileName, idx)).data());
  canvas->Print(std::string(outputFileName_plot).append(".png").data());
  canvas->Print(std::string(outputFileName_plot).append(".pdf").data());
  
  delete canvas;  
}

void compMVAInputVarCorrelation()
{
  gROOT->SetBatch(true);

  TH1::AddDirectory(false);

  std::string channel = "2lss";
  //std::string channel = "3l";

  std::string inputFilePath, inputFileName, directoryName;
  if ( channel == "2lss" ) {
    inputFilePath = "/hdfs/local/veelken/hhAnalysis/2016/2021Jan27_2lss_mvaInputVarCorrelation/histograms/hh_2lss/Tight_SS/hadd/";
    inputFileName = "hadd_stage2_Tight_SS.root";
    directoryName = "hh_2lss_SS_Tight/sel/mvaInputVarCorrelation/%s/";
  } else if ( channel == "3l" ) {
    inputFilePath = "/hdfs/local/veelken/hhAnalysis/2016/2021Jan27_3l_mvaInputVarCorrelation/histograms/hh_3l/Tight_OS/hadd/";
    inputFileName = "hadd_stage2_Tight_OS.root";
    directoryName = "hh_3l_OS_Tight/sel/mvaInputVarCorrelation/%s/";
  } else assert(0);
  std::string histogramNameX       = "sumX";
  std::string histogramNameX2      = "sumX2";
  std::string histogramNameXY      = "sumXY";
  std::string histogramNameWeights = "sumWeights";

  std::vector<std::string> processes;
  processes.push_back("Convs");
  processes.push_back("TTH");
  processes.push_back("tHq");
  processes.push_back("tHW");
  processes.push_back("ggH");
  processes.push_back("qqH");
  processes.push_back("TTZ");
  processes.push_back("TTW");
  processes.push_back("TTWW");
  processes.push_back("TT");
  processes.push_back("Other");
  processes.push_back("ZH");
  processes.push_back("DY");
  processes.push_back("W");
  processes.push_back("WW");
  processes.push_back("WZ");
  processes.push_back("qqZZ");
  processes.push_back("ggZZ");
  processes.push_back("WH");
  processes.push_back("data_fakes");
  if ( channel == "2lss" ) {
    processes.push_back("data_flips");
  }
  processes.push_back("data_obs");

  TFile* inputFile = openFile(inputFilePath, inputFileName);

  TH1* histogramX_data       = nullptr;
  TH1* histogramX2_data      = nullptr;
  TH2* histogramXY_data      = nullptr;
  TH1* histogramWeights_data = nullptr;

  TH1* histogramX_mc         = nullptr;
  TH1* histogramX2_mc        = nullptr;
  TH2* histogramXY_mc        = nullptr;
  TH1* histogramWeights_mc   = nullptr;

  for ( std::vector<std::string>::const_iterator process = processes.begin();
        process != processes.end(); ++process ) {
    std::string directoryName_process = Form(directoryName.data(), process->data());

    TH1* histogramX_process       = loadHistogram(inputFile, directoryName_process, histogramNameX);
    TH1* histogramX2_process      = loadHistogram(inputFile, directoryName_process, histogramNameX2);
    TH2* histogramXY_process      = dynamic_cast<TH2*>(loadHistogram(inputFile, directoryName_process, histogramNameXY));
    TH1* histogramWeights_process = loadHistogram(inputFile, directoryName_process, histogramNameWeights);

    assert(histogramX_process && histogramX2_process && histogramXY_process && histogramWeights_process);

    if ( (*process) == "data_obs" ) {
      histogramX_data       = (TH1*)histogramX_process->Clone(histogramNameX.data());
      histogramX2_data      = (TH1*)histogramX2_process->Clone(histogramNameX2.data());
      histogramXY_data      = (TH2*)histogramXY_process->Clone(histogramNameXY.data());
      histogramWeights_data = (TH1*)histogramWeights_process->Clone(histogramNameWeights.data());
    } else {
     if ( !(histogramX_mc && histogramX2_mc && histogramXY_mc && histogramWeights_mc) ) {
        histogramX_mc       = (TH1*)histogramX_process->Clone(histogramNameX.data());
        histogramX2_mc      = (TH1*)histogramX2_process->Clone(histogramNameX2.data());
        histogramXY_mc      = (TH2*)histogramXY_process->Clone(histogramNameXY.data());
        histogramWeights_mc = (TH1*)histogramWeights_process->Clone(histogramNameWeights.data());
      } else {
        histogramX_mc->Add(histogramX_process);
        histogramX2_mc->Add(histogramX2_process);
        histogramXY_mc->Add(histogramXY_process);
        histogramWeights_mc->Add(histogramWeights_process);
      }
    }
  }

  assert(histogramX_data && histogramX2_data && histogramXY_data && histogramWeights_data);
  assert(histogramX_mc && histogramX2_mc && histogramXY_mc && histogramWeights_mc);

  TAxis* axis = histogramX_data->GetXaxis();
  int numBins = axis->GetNbins();
  assert(histogramX2_data->GetNbinsX() == numBins);
  assert(histogramXY_data->GetNbinsX() == numBins && histogramXY_data->GetNbinsY() == numBins);
  assert(histogramWeight_data->GetNbinsX() == numBins);
  assert(histogramX_mc->GetNbinsX() == numBins);
  assert(histogramX2_mc->GetNbinsX() == numBins);
  assert(histogramXY_mc->GetNbinsX() == numBins && histogramXY_mc->GetNbinsY() == numBins);
  assert(histogramWeight_mc->GetNbinsX() == numBins);

  TH2* histogramCorr_data = new TH2D("corr_data", "corr_data", numBins, -0.5, numBins - 0.5, numBins, -0.5, numBins - 0.5);
  histogramCorr_data->Sumw2();
  TH2* histogramCorr_mc = new TH2D("corr_mc", "corr_mc", numBins, -0.5, numBins - 0.5, numBins, -0.5, numBins - 0.5);
  histogramCorr_mc->Sumw2();

  TH1* histogramCorr_diff = new TH1D("corr_diff", "corr_diff", 100, -0.5, +0.5);

  for ( int idxBinX = 1; idxBinX <= numBins; ++idxBinX ) {
    std::string mvaInputVariableX = axis->GetBinLabel(idxBinX);

    double sumX_data = histogramX_data->GetBinContent(idxBinX);
    double sumX2_data = histogramX2_data->GetBinContent(idxBinX);
    double sumWeights_data = histogramWeights_data->GetBinContent(1);

    double sumX_mc = histogramX_mc->GetBinContent(idxBinX);
    double sumX2_mc = histogramX2_mc->GetBinContent(idxBinX);
    double sumWeights_mc = histogramWeights_mc->GetBinContent(1);

    for ( int idxBinY = 1; idxBinY <= numBins; ++idxBinY ) {
      std::string mvaInputVariableY = axis->GetBinLabel(idxBinY);

      double sumY_data = histogramX_data->GetBinContent(idxBinY);
      double sumY2_data = histogramX2_data->GetBinContent(idxBinY);
      double sumXY_data = histogramXY_data->GetBinContent(idxBinX, idxBinY);
      //std::cout << "idxBinX = " << idxBinX << ", idxBinY = " << idxBinY << ":" 
      //          << " sumX_data = " << sumX_data << ", sumX2_data = " << sumX2_data << ","
      //          << " sumY_data = " << sumY_data << ", sumY2_data = " << sumY2_data << ","
      //          << " sumXY_data = " << sumXY_data << std::endl;
      //std::cout << "sumWeights_data = " << sumWeights_data << std::endl;

      double sumY_mc = histogramX_mc->GetBinContent(idxBinY);
      double sumY2_mc = histogramX2_mc->GetBinContent(idxBinY);
      double sumXY_mc = histogramXY_mc->GetBinContent(idxBinX, idxBinY);
      //std::cout << "idxBinX = " << idxBinX << ", idxBinY = " << idxBinY << ":" 
      //          << " sumX_mc = " << sumX_mc << ", sumX2_mc = " << sumX2_mc << ","
      //          << " sumY_mc = " << sumY_mc << ", sumY2_mc = " << sumY2_mc << ","
      //          << " sumXY_mc = " << sumXY_mc << std::endl;
      //std::cout << "sumWeights_mc = " << sumWeights_mc << std::endl;

      double corr_data = (sumWeights_data*sumXY_data - sumX_data*sumY_data)/
        (TMath::Sqrt(sumWeights_data*sumX2_data - sumX_data*sumX_data)*TMath::Sqrt(sumWeights_data*sumY2_data - sumY_data*sumY_data));
      double corr_mc = (sumWeights_mc*sumXY_mc - sumX_mc*sumY_mc)/
        (TMath::Sqrt(sumWeights_mc*sumX2_mc - sumX_mc*sumX_mc)*TMath::Sqrt(sumWeights_mc*sumY2_mc - sumY_mc*sumY_mc));
      double corr_diff = corr_data - corr_mc;
      std::cout << "corr(" << mvaInputVariableX << "," << mvaInputVariableY << "): data = " << corr_data << ", mc = " << corr_mc << " --> diff = " << corr_diff << std::endl;

      histogramCorr_data->SetBinContent(idxBinX, idxBinY, corr_data);
      histogramCorr_data->SetBinError(idxBinX, idxBinY, 0.);
      histogramCorr_data->GetXaxis()->SetBinLabel(idxBinX, mvaInputVariableX.data());
      histogramCorr_data->GetYaxis()->SetBinLabel(idxBinY, mvaInputVariableY.data());

      histogramCorr_mc->SetBinContent(idxBinX, idxBinY, corr_mc);
      histogramCorr_mc->SetBinError(idxBinX, idxBinY, 0.);
      histogramCorr_mc->GetXaxis()->SetBinLabel(idxBinX, mvaInputVariableX.data());
      histogramCorr_mc->GetYaxis()->SetBinLabel(idxBinY, mvaInputVariableY.data());

      if ( idxBinX > idxBinY ) {
        fillWithOverFlow(histogramCorr_diff, corr_diff);
      }
    }
  }

  delete inputFile;

  showHistogram2d(1500, 800, histogramCorr_data, Form("compMVAInputVarCorrelation_%s_data.pdf", channel.data()));
  showHistogram2d(1500, 800, histogramCorr_mc, Form("compMVAInputVarCorrelation_%s_mc.pdf", channel.data()));
  
  showHistogram1d(1000, 800, histogramCorr_diff, Form("compMVAInputVarCorrelation_%s_diff.pdf", channel.data()));

  TFile* outputFile = new TFile(Form("compMVAInputVarCorrelation_%s.root", channel.data()), "RECREATE");
  outputFile->cd();
  histogramCorr_data->Write();
  histogramCorr_mc->Write();
  histogramCorr_diff->Write();
  delete outputFile;
}

