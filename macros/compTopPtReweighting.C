
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
#include <TPRegexp.h>
#include <TObjString.h>
#include <TObjArray.h>

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
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

double square(double x)
{
  return x*x;
}

void read_xSection(const std::string& inputFileName, int numBins, Float_t* binning, Float_t* xSections, Float_t* xSectionsErr)
{
  std::ifstream inputFile;
  inputFile.open(inputFileName);

  TPRegexp regexpParser("([0-9.e+/-]+)\\s+([0-9.e+/-]+)\\s+([0-9.e+/-]+)\\s+([0-9.e+/-]+)\\s+([0-9.e+/-]+)\\s+([0-9.e+/-]+)\\s+([0-9.e+/-]+)\\s+([0-9.e+/-]+)\\s+([0-9.e+/-]+)\\s*");

  std::string line;
  int idxBin = 0;
  while ( std::getline(inputFile, line) ) {
    const TObjArray * const subStrings = regexpParser.MatchS(line.data());
    if ( subStrings->GetEntries() == 10 ) {
      double binCenter          = (static_cast<TObjString *>(subStrings->At(1)))->GetString().Atof();
      double binWidth           = (static_cast<TObjString *>(subStrings->At(9)))->GetString().Atof();
      double binEdgeLo          = binCenter - 0.5*binWidth;
      double binEdgeHi          = binCenter + 0.5*binWidth;
      assert(TMath::Abs(binEdgeLo - binning[idxBin]    ) < 1.e-3);
      assert(TMath::Abs(binEdgeHi - binning[idxBin + 1]) < 1.e-3);
      double xSection_central   = (static_cast<TObjString *>(subStrings->At(2)))->GetString().Atof();
      double xSection_scaleDown = (static_cast<TObjString *>(subStrings->At(3)))->GetString().Atof();
      double xSection_scaleUp   = (static_cast<TObjString *>(subStrings->At(4)))->GetString().Atof();
      double xSection_pdfDown   = (static_cast<TObjString *>(subStrings->At(5)))->GetString().Atof();
      double xSection_pdfUp     = (static_cast<TObjString *>(subStrings->At(6)))->GetString().Atof();
      double xSectionErr        = TMath::Sqrt(
         0.5*(square(xSection_central - xSection_scaleDown) + square(xSection_scaleUp - xSection_central)) 
       + 0.5*(square(xSection_central - xSection_pdfDown  ) + square(xSection_pdfUp   - xSection_central)));
      std::cout << "xSection[" << binEdgeLo << "-" << binEdgeHi << "] = " << xSection_central << " +/- " << xSectionErr << std::endl;
      //assert(idxBin < numBins);
      if ( idxBin < numBins ) {
        xSections[idxBin]         = xSection_central;
        xSectionsErr[idxBin]      = xSectionErr;
      }
      ++idxBin;
    }
  }
  inputFile.close();
}

void process(const std::string& era, 
             TH1* histogram, TH1* histogram_fine_binning, 
             TH1* histogram_theory, 
             const std::string& outputFileName)
{
  assert(histogram->GetNbinsX() == histogram_theory->GetNbinsX());
  int numBins = histogram->GetXaxis()->GetNbins();

  double sum_histogram = 0.;
  double sum_histogram_theory = 0.;
  for ( int idxBin = 0; idxBin < numBins; ++idxBin ) 
  {
    sum_histogram += histogram->GetBinContent(idxBin + 1); // CV: leftmost bin of TH1 has index 1 (index 0 corresponds to the underflow bin)
    sum_histogram_theory += histogram_theory->GetBinContent(idxBin + 1);
  }

  TGraphAsymmErrors* graph = new TGraphAsymmErrors(numBins);
  for ( int idxBin = 0; idxBin < numBins; ++idxBin ) 
  {
    double xMin_idxBin = histogram->GetXaxis()->GetBinLowEdge(idxBin + 1);
    double xMax_idxBin = histogram->GetXaxis()->GetBinUpEdge(idxBin + 1);
    assert(TMath::Abs(histogram_theory->GetXaxis()->GetBinLowEdge(idxBin) - xMin_idxBin) < 1.e-3);
    assert(TMath::Abs(histogram_theory->GetXaxis()->GetBinUpEdge(idxBin)  - xMax_idxBin) < 1.e-3);    
    histogram_fine_binning->GetXaxis()->SetRangeUser(xMin_idxBin, xMax_idxBin);
    double graph_x = histogram_fine_binning->GetMean();
    double graph_y = (histogram_theory->GetBinContent(idxBin + 1)/sum_histogram_theory)/(histogram->GetBinContent(idxBin + 1)/sum_histogram);
    graph->SetPoint(idxBin, graph_x, graph_y);
    double graphErrLo_x = graph_x - xMin_idxBin;
    double graphErrHi_x = xMax_idxBin - graph_x;
    // sum statistical uncertainty on Powheg distribution
    //  + systematic (scale + PDF) uncertainty on NNLO cross section
    // in quadrature
    double graphRelErr = TMath::Sqrt(
       square(histogram->GetBinError(idxBin + 1)/histogram->GetBinContent(idxBin + 1))
     + square(histogram_theory->GetBinError(idxBin + 1)/histogram_theory->GetBinContent(idxBin + 1)));
    // CV: increase uncertainties by factor 3, 
    //     in order for fit to better converges
    const double fudgeFactor = 3.;
    graphRelErr *= fudgeFactor;
    double graphErrLo_y = graph_y*graphRelErr;
    double graphErrHi_y = graphErrLo_y;
    graph->SetPointError(idxBin, graphErrLo_x, graphErrHi_x, graphErrLo_y, graphErrHi_y);
  }

  double xMin = histogram->GetXaxis()->GetXmin();
  double xMax = histogram->GetXaxis()->GetXmax();

  TF1* fitFunction1 = new TF1("fitFunction1", "TMath::Exp([0] + [1]*x + [2]*x*x)", xMin, xMax); 
  graph->Fit(fitFunction1, "N");
  std::cout << "Era = '" << era << "': par0 = " << fitFunction1->GetParameter(0) << ", par1 = " << fitFunction1->GetParameter(1) << std::endl;

  TF1* fitFunction2 = new TF1("fitFunction2", "TMath::Exp([0] + [1]*x + [2]*x*x + [3]/(x + [4]))", xMin, xMax); 
  graph->Fit(fitFunction2, "N");

  TCanvas* canvas = new TCanvas("canvas", "canvas", 800, 600);
  canvas->SetFillColor(10);
  canvas->SetBorderSize(2);
  canvas->SetLeftMargin(0.13);
  canvas->SetBottomMargin(0.13);

  TH1* dummyHistogram = new TH1D("dummyHistogram", "dummyHistogram", 10, xMin, xMax);
  dummyHistogram->SetStats(false);
  dummyHistogram->SetTitle("");
  dummyHistogram->SetMinimum(0.3);
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

  fitFunction1->SetLineColor(1);
  fitFunction1->SetLineWidth(1);
  fitFunction1->Draw("same");

  fitFunction2->SetLineColor(1);
  fitFunction2->SetLineWidth(2);
  fitFunction2->SetLineStyle(7);
  fitFunction2->Draw("same");

  TF1* fitFunction_Top_PAG = new TF1("fitFunction_Top_PAG", "TMath::Exp([0] + [1]*TMath::Min(550., x))", xMin, xMax); 
  fitFunction_Top_PAG->SetParameter(0,  0.0615);
  fitFunction_Top_PAG->SetParameter(1, -0.0005);
  
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

  TLegend* legend = new TLegend(0.58, 0.56, 0.89, 0.89, "", "brNDC"); 
  legend->SetBorderSize(0);
  legend->SetFillColor(0);
  legend->SetTextSize(0.045);
  legend->AddEntry(graph, "HIG-19-008 ratio", "p");
  legend->AddEntry(fitFunction1, "HIG-19-008 fit1", "l");
  legend->AddEntry(fitFunction2, "HIG-19-008 fit2", "l");
  legend->AddEntry(fitFunction_Top_PAG, "Fit by Top PAG", "l");
  legend->Draw();

  canvas->Update();
  std::string outputFileName_plot = "plots/";
  size_t idx = outputFileName.find_last_of('.');
  outputFileName_plot.append(std::string(outputFileName, 0, idx));
  if ( idx != std::string::npos ) canvas->Print(std::string(outputFileName_plot).append(std::string(outputFileName, idx)).data());
  canvas->Print(std::string(outputFileName_plot).append(".png").data());
  canvas->Print(std::string(outputFileName_plot).append(".pdf").data());

  delete dummyHistogram;
  delete graph;
  delete fitFunction1;
  delete fitFunction2;
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
  
  std::string histogramName = "genTopQuark_pt_binning3";
  std::string histogramName_fine_binning = "genTopQuark_pt_fine_binning";

//--- define NNLO cross-sections (with electroweak corrections),
//    taken from arXiv:1705.04105
//   (downloaded from http://www.precision.hep.phy.cam.ac.uk/wp-content/results/ttbar-nnloQCD-nloEW/ttbar-LHC13-LHC8-NNLOQCD+NLOEW.tar.gz,
//    using the file LHC13-PTavt-MT2-NNPDF30QED-pheno.dat;
//    the binning in top pT is defined in that file)
  int numBins = 26;
  Float_t* binning = new Float_t[numBins + 1];
  binning[0]  =    0.;
  binning[1]  =   50.;
  binning[2]  =  100.;
  binning[3]  =  150.;
  binning[4]  =  200.;
  binning[5]  =  250.;
  binning[6]  =  300.;
  binning[7]  =  350.;
  binning[8]  =  400.;
  binning[9]  =  450.;
  binning[10] =  500.;
  binning[11] =  550.;
  binning[12] =  600.;
  binning[13] =  650.;
  binning[14] =  700.;
  binning[15] =  800.;
  binning[16] =  900.;
  binning[17] = 1000.;
  binning[18] = 1100.;
  binning[19] = 1200.;
  binning[20] = 1400.;
  binning[21] = 1600.;
  binning[22] = 1800.;
  binning[23] = 2000.;
  binning[24] = 2200.;
  binning[25] = 2600.;
  binning[26] = 3000.;

  Float_t* xSections    = new Float_t[numBins];
  Float_t* xSectionsErr = new Float_t[numBins];
  std::string inputFilePath_xSection = "/home/veelken/CMSSW_10_2_10_centOS/CMSSW_10_2_10/src/tthAnalysis/HiggsToTauTau/macros/";
  std::string inputFileName_xSection = "LHC13-PTavt-MT2-NNPDF30QED-pheno.dat";
  std::string inputFileName_xSection_full = inputFilePath_xSection;
  if ( inputFileName_xSection_full.find_last_of("/") != (inputFileName_xSection_full.size() - 1) ) inputFileName_xSection_full.append("/");
  inputFileName_xSection_full.append(inputFileName_xSection);
  read_xSection(inputFileName_xSection_full, numBins, binning, xSections, xSectionsErr);
  TH1* histogram_theory = new TH1D("histogram_theory", "histogram_theory", numBins, binning);
  for ( int idxBin = 0; idxBin < numBins; ++idxBin ) {
    histogram_theory->SetBinContent(idxBin + 1, xSections[idxBin]);
    histogram_theory->SetBinError(idxBin + 1, xSectionsErr[idxBin]);
  }
  histogram_theory->Rebin(2);

  TH1* histogram_allEras = nullptr;
  TH1* histogram_fine_binning_allEras = nullptr;

  for ( std::vector<std::string>::const_iterator era = eras.begin();
	era != eras.end(); ++era ) {
    TFile* inputFile = openFile(inputFilePath, inputFileNames[*era]);

    TH1* histogram = loadHistogram(inputFile, histogramName);
    histogram->Rebin(2);
    if ( !histogram_allEras ) {
      histogram_allEras = (TH1*)histogram->Clone("histogram_allEras");
    } else {
      histogram_allEras->Add(histogram);
    }
    TH1* histogram_fine_binning = loadHistogram(inputFile, histogramName_fine_binning);
    if ( !histogram_fine_binning_allEras ) {
      histogram_fine_binning_allEras = (TH1*)histogram_fine_binning->Clone("histogram_fine_binning_allEras");
    } else {
      histogram_fine_binning_allEras->Add(histogram_fine_binning);
    }

    std::string outputFileName = Form("compTopPtReweighting_%s.png", era->data());
    process(*era, histogram, histogram_fine_binning, histogram_theory, outputFileName);

    delete inputFile;
  }

  std::string outputFileName_allEras = Form("compTopPtReweighting_allEras.png");
  process("allEras", histogram_allEras, histogram_fine_binning_allEras, histogram_theory, outputFileName_allEras);
}
