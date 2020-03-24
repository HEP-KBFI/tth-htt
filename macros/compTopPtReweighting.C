
#include <TAxis.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TGraphAsymmErrors.h>
#include <TH1.h>
#include <TH2.h>
#include <TF1.h>
#include <TLegend.h>
#include <TMath.h>
#include <TPaveText.h>
#include <TROOT.h>
#include <TString.h>
#include <TSystem.h>

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <iomanip>
#include <assert.h>
#include <math.h>
#include <limits>

TFile* openFile(const std::string& inputFilePath, const std::string& inputFileName)
{
  std::string inputFileName_full = inputFilePath;
  if ( inputFileName_full.find_last_of("/") != (inputFileName_full.size() - 1) ) inputFileName_full.append("/");
  inputFileName_full.append(inputFileName);
  TFile* inputFile = new TFile(inputFileName_full.data());
  if ( !inputFile ) {
    std::cerr << "Failed to open input file = '" << inputFileName_full << "' !!" << std::endl;
    assert(0);
  }
  return inputFile;
}

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

void process(const std::string& era, TH1* histogram, TH1* histogram_fine_binning, int numBins, Float_t* binning, Float_t* xSections, const std::string& outputFileName)
{
  double sum_histogram = 0.;
  double sum_xSections = 0.;
  for ( int idxBin = 0; idxBin < numBins; ++idxBin ) 
  {
    sum_histogram += histogram->GetBinContent(idxBin + 1); // CV: leftmost bin of TH1 has index 1 (index 0 corresponds to the underflow bin)
    sum_xSections += xSections[idxBin];
  }

  TGraphAsymmErrors* graph = new TGraphAsymmErrors(numBins);
  for ( int idxBin = 0; idxBin < numBins; ++idxBin ) 
  {
    double xMin_idxBin = binning[idxBin];
    double xMax_idxBin = binning[idxBin + 1];
    assert(TMath::Abs(histogram->GetXaxis()->GetBinLowEdge(idxBin) - xMin_idxBin) < 1.e-3);
    assert(TMath::Abs(histogram->GetXaxis()->GetBinUpEdge(idxBin)  - xMax_idxBin) < 1.e-3);
    histogram_fine_binning->GetXaxis()->SetRangeUser(xMin_idxBin, xMax_idxBin);
    double graph_x = histogram_fine_binning->GetMean();
    double graph_y = (xSections[idxBin]/sum_xSections)/(histogram->GetBinContent(idxBin + 1)/sum_histogram);
    graph->SetPoint(idxBin, graph_x, graph_y);
    double graphErrLo_x = graph_x - xMin_idxBin;
    double graphErrHi_x = xMax_idxBin - graph_x;
    double graphErrLo_y = graph_y*(histogram->GetBinError(idxBin + 1)/histogram->GetBinContent(idxBin + 1));
    //std::cout << "bin #" << idxBin + 1 << ": binContent = " << histogram->GetBinContent(idxBin + 1) << ", binError = " << histogram->GetBinError(idxBin + 1) << std::endl;
    double graphErrHi_y = graphErrLo_y;
    graph->SetPointError(idxBin, graphErrLo_x, graphErrHi_x, graphErrLo_y, graphErrHi_y);
  }

  double xMin = binning[0];
  double xMax = binning[numBins];
  TF1* fitFunction = new TF1("fitFunction", "TMath::Exp([0] + [1]*x + [2]*x*x)", xMin, xMax); 
  graph->Fit(fitFunction, "W");
  std::cout << "Era = '" << era << "': par0 = " << fitFunction->GetParameter(0) << ", par1 = " << fitFunction->GetParameter(1) << std::endl;

  TCanvas* canvas = new TCanvas("canvas", "canvas", 800, 600);
  canvas->SetFillColor(10);
  canvas->SetBorderSize(2);
  canvas->SetLeftMargin(0.13);
  canvas->SetBottomMargin(0.13);

  TH1* dummyHistogram = new TH1D("dummyHistogram", "dummyHistogram", 10, xMin, xMax);
  dummyHistogram->SetStats(false);
  dummyHistogram->SetTitle("");
  dummyHistogram->SetMinimum(0.5);
  dummyHistogram->SetMaximum(1.5);

  TAxis* xAxis = dummyHistogram->GetXaxis();
  xAxis->SetTitle("Top p_{T} [GeV]");
  xAxis->SetTitleSize(0.045);
  xAxis->SetTitleOffset(1.3);

  TAxis* yAxis = dummyHistogram->GetYaxis();
  yAxis->SetTitle("NNLO/Powheg + Pythia8");
  yAxis->SetTitleSize(0.045);
  yAxis->SetTitleOffset(1.45);

  dummyHistogram->Draw("axis");

  fitFunction->SetLineColor(2);
  fitFunction->SetLineWidth(2);
  fitFunction->Draw("same");

  TF1* fitFunction_Top_PAG = new TF1("fitFunction_Top_PAG", "TMath::Exp([0] - [1]*x)", xMin, xMax); 
  fitFunction_Top_PAG->SetParameter(0, 0.0615);
  fitFunction_Top_PAG->SetParameter(1, 0.0005);
  
  fitFunction_Top_PAG->SetLineColor(4);
  fitFunction_Top_PAG->SetLineWidth(2);
  fitFunction_Top_PAG->Draw("same");

  graph->SetMarkerColor(1);
  graph->SetMarkerStyle(20);
  graph->SetMarkerSize(1);
  graph->SetLineColor(1);
  graph->SetLineStyle(1);
  graph->SetLineWidth(1);
  graph->Draw("P");

  TLegend* legend = new TLegend(0.61, 0.71, 0.89, 0.89, "", "brNDC"); 
  legend->SetBorderSize(0);
  legend->SetFillColor(0);
  legend->SetTextSize(0.045);
  legend->AddEntry(graph, "Our ratio", "p");
  legend->AddEntry(fitFunction, "Our fit", "l");
  legend->AddEntry(fitFunction_Top_PAG, "Fit by Top PAG", "l");
  legend->Draw();

  canvas->Update();
  std::string outputFileName_plot = "plots/";
  size_t idx = outputFileName.find_last_of('.');
  outputFileName_plot.append(std::string(outputFileName, 0, idx));
  if ( idx != std::string::npos ) canvas->Print(std::string(outputFileName_plot).append(std::string(outputFileName, idx)).data());
  canvas->Print(std::string(outputFileName_plot).append(".png").data());
  canvas->Print(std::string(outputFileName_plot).append(".pdf").data());

  delete graph;
  delete dummyHistogram;
  delete fitFunction;
  delete fitFunction_Top_PAG;
  delete legend;
  delete canvas;
}

void compTopPtReweighting()
{
//--- stop ROOT from keeping references to all histograms
  TH1::AddDirectory(false);

//--- suppress the output canvas 
  gROOT->SetBatch(true);

  std::vector<std::string> eras;
  eras.push_back("2016");
  eras.push_back("2017");
  eras.push_back("2018");  

  std::string inputFilePath = "/home/veelken/CMSSW_10_2_10_centOS/CMSSW_10_2_10/src/tthAnalysis/HiggsToTauTau/test/templates/";
  std::map<std::string, std::string> inputFileNames; // key = era
  inputFileNames["2016"] = "analyze_genTopPt_2016.root";
  inputFileNames["2017"] = "analyze_genTopPt_2017.root";
  inputFileNames["2018"] = "analyze_genTopPt_2018.root";
  
  std::string histogramName = "genTopQuark_pt_binning1";
  std::string histogramName_fine_binning = "genTopQuark_pt_fine_binning";

//--- define NNLO cross-sections (with electroweak corrections),
//    taken from arXiv:1705.04105
//   (downloaded from http://www.precision.hep.phy.cam.ac.uk/wp-content/results/ttbar-nnloQCD-nloEW/LHC13-ttbar-CMS_bin-ancillary-files-172_5.tar.gz,
//    using the file LHC13-CMS-mt_172.5-PTavt-MT2-NNPDF31-pheno.dat;
//    the binning in top pT is defined in TOP-16-011, shown in Fig. 26 of CMS AN-2015/309 v7)
  int numBins = 6;
  Float_t* binning = new Float_t[numBins + 1];
  binning[0] =   0.;
  binning[1] =  65.;
  binning[2] = 125.;
  binning[3] = 200.;
  binning[4] = 290.;
  binning[5] = 400.;
  binning[6] = 550.;

  Float_t* xSections = new Float_t[numBins];
  xSections[0] = 2.1053398799999999e+02;
  xSections[1] = 3.0159929299999999e+02;
  xSections[2] = 2.0868522600000000e+02;
  xSections[3] = 7.8802675300000004e+01;
  xSections[4] = 2.2525836999999999e+01;
  xSections[5] = 5.6874119900000002e+00;

  for ( std::vector<std::string>::const_iterator era = eras.begin();
	era != eras.end(); ++era ) {
    TFile* inputFile = openFile(inputFilePath, inputFileNames[*era]);

    TH1* histogram = loadHistogram(inputFile, histogramName);
    TH1* histogram_fine_binning = loadHistogram(inputFile, histogramName_fine_binning);

    std::string outputFileName = Form("compTopPtReweighting_%s.png", era->data());
    process(*era, histogram, histogram_fine_binning, numBins, binning, xSections, outputFileName);

    delete inputFile;
  }
}
