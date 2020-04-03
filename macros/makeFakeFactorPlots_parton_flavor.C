
#include <TFile.h>
#include <TString.h>
#include <TCanvas.h>
#include <TGraphAsymmErrors.h>
#include <TGraphErrors.h>
#include <TGraph.h>
#include <TH1.h>
#include <TAxis.h>
#include <TF1.h>
#include <TLegend.h>
#include <TPaveText.h>
#include <TMath.h>
#include <TROOT.h>
#include <TStyle.h>

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <iomanip>
#include <assert.h>

//-------------------------------------------------------------------------------
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

TH1* loadHistogram(TFile* inputFile, const std::string& directoryName, const std::string& histogramName)
{
  std::string histogramName_full = directoryName;
  if ( histogramName_full.find_last_of("/") != (histogramName_full.size() - 1) ) histogramName_full.append("/");
  histogramName_full.append(histogramName);
  TH1* histogram = dynamic_cast<TH1*>(inputFile->Get(histogramName_full.data()));
  if ( !histogram ) {
    std::cerr << "Failed to load histogram = " << histogramName_full << " from file = " << inputFile->GetName() << " !!" << std::endl;
    assert(0);
  }
  if ( !histogram->GetSumw2N() ) histogram->Sumw2();
  histogram->Rebin(2);
  return histogram;
}
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
double square(double x)
{
  return x*x;
}

// function compFakeRate taken from tthAnalysis/HiggsToTauTau/src/compFakeRateAuxFunctions.cc
void
compFakeRate(double nPass,
             double nPassErr,
             double nFail,
             double nFailErr,
             double & avFakeRate,
             double & avFakeRateErrUp,
             double & avFakeRateErrDown,
             bool & errorFlag)
{ 
  const double sumWeights = nPass + nFail;
  const double sumWeights2 = square(nPassErr) + square(nFailErr);

  if(sumWeights > 0. && sumWeights2 > 0.)
  {
    const double n_eff = square(sumWeights/std::sqrt(sumWeights2));
    const double sf = n_eff/(sumWeights);
    const Int_t nPass_int = std::max(TMath::Nint(sf * nPass), 0);

    TH1 * const histogram_pass_tmp = new TH1D(
      "histogram_pass_tmp", "histogram_pass_tmp", 1, -0.5, +0.5
    );
    histogram_pass_tmp->SetBinContent(1, nPass_int);
    histogram_pass_tmp->SetBinError  (1, std::sqrt(nPass_int));
    const Int_t nFail_int = std::max(TMath::Nint(sf * nFail), 0);

    TH1 * const histogram_pass_plus_fail_tmp = new TH1D(
      "histogram_pass_plus_fail_tmp", "histogram_pass_plus_fail_tmp", 1, -0.5, +0.5
    );
    histogram_pass_plus_fail_tmp->SetBinContent(1, nPass_int + nFail_int);
    histogram_pass_plus_fail_tmp->SetBinError(1, std::sqrt(nPass_int + nFail_int));

    TGraphAsymmErrors * const graph_pass_div_pass_plus_fail_tmp = new TGraphAsymmErrors(1);
    graph_pass_div_pass_plus_fail_tmp->Divide(histogram_pass_tmp, histogram_pass_plus_fail_tmp, "cp");

    double dummy;
    graph_pass_div_pass_plus_fail_tmp->GetPoint(0, dummy, avFakeRate);

    avFakeRateErrUp   = std::max(graph_pass_div_pass_plus_fail_tmp->GetErrorYhigh(0), 2.e-2);
    avFakeRateErrDown = std::max(graph_pass_div_pass_plus_fail_tmp->GetErrorYlow(0), 2.e-2);

    delete histogram_pass_tmp;
    delete histogram_pass_plus_fail_tmp;
    delete graph_pass_div_pass_plus_fail_tmp;
    errorFlag = false;

    std::cout << " nPass = "      << nPass      << " +/- " << nPassErr << " (int = " << nPass_int << "),"
                 " nFail = "      << nFail      << " +/- " << nFailErr << " (int = " << nFail_int << ") -->"
                 " avFakeRate = " << avFakeRate << " + "   << avFakeRateErrUp
                                                << " - "   << avFakeRateErrDown
              << '\n'
    ;
  }
  else
  {
    avFakeRate        = 0.5;
    avFakeRateErrUp   = 0.5;
    avFakeRateErrDown = 0.5;
    errorFlag = true;
    std::cout << " sumWeights = "  << sumWeights << ","
                 " sumWeights2 = " << sumWeights2 << " -->"
                 " avFakeRate = "  << avFakeRate << " + " << avFakeRateErrUp
                                                 << " - " << avFakeRateErrDown
              << '\n'
    ;
  }
}

// function getGraph_jetToTauFakeRate taken from tthAnalysis/HiggsToTauTau/bin/comp_jetToTauFakeRate.cc
TGraphAsymmErrors* 
getGraph_jetToTauFakeRate(TH1* histogram_loose, TH1* histogram_tight, const std::string& graphName_jetToTauFakeRate)
{
  std::cout << "<getGraph_jetToTauFakeRate>:" << std::endl;
  assert(histogram_loose->GetNbinsX() == histogram_tight->GetNbinsX());
  int numBins = histogram_loose->GetNbinsX();
  std::vector<double> points_x;
  std::vector<double> points_xErrUp;
  std::vector<double> points_xErrDown;
  std::vector<double> points_y;
  std::vector<double> points_yErrUp;
  std::vector<double> points_yErrDown;
  for ( int idxBin = 1; idxBin <= numBins; ++idxBin ) {
    double nLoose = histogram_loose->GetBinContent(idxBin);
    double nLooseErr = histogram_loose->GetBinError(idxBin);
    double nTight = histogram_tight->GetBinContent(idxBin);
    double nTightErr = histogram_tight->GetBinError(idxBin);     
    
    double nPass = nTight;
    double nPassErr = nTightErr;
    double nFail = nLoose - nTight;
    double nFailErr = TMath::Sqrt(TMath::Max(0., square(nLooseErr) - square(nTightErr)));
    
    double jetToTauFakeRate, jetToTauFakeRateErrUp, jetToTauFakeRateErrDown;
    bool errorFlag;
    std::cout << "bin #" << idxBin << " (x = " << histogram_loose->GetBinCenter(idxBin) << ")" << ":";	  
    compFakeRate(nPass, nPassErr, nFail, nFailErr, jetToTauFakeRate, jetToTauFakeRateErrUp, jetToTauFakeRateErrDown, errorFlag);
    if ( errorFlag ) {
      std::cerr << "Warning: Cannot compute fake rate for nPass = " << nPass << " +/- " << nPassErr << ", nFail = " << nFail << " +/- " << nFailErr 
		<< " --> setting jetToTauFakeRate = " << jetToTauFakeRate << " + " << jetToTauFakeRateErrUp << " - " << jetToTauFakeRateErrDown << " !!" << std::endl;
    }
    double binCenter_loose = histogram_loose->GetBinCenter(idxBin);
    double binCenter_tight = histogram_tight->GetBinCenter(idxBin);
    assert(TMath::Abs(binCenter_loose - binCenter_tight) < 1.e-3*TMath::Abs(binCenter_loose + binCenter_tight));
    TAxis* xAxis = histogram_loose->GetXaxis();
    double x = xAxis->GetBinCenter(idxBin);
    points_x.push_back(x);
    double y = jetToTauFakeRate;
    points_y.push_back(y);
    double xErrUp = xAxis->GetBinUpEdge(idxBin) - xAxis->GetBinCenter(idxBin);
    points_xErrUp.push_back(xErrUp);
    double xErrDown = xAxis->GetBinCenter(idxBin) - xAxis->GetBinLowEdge(idxBin);
    points_xErrDown.push_back(xErrDown);
    double yErrUp = jetToTauFakeRateErrUp;
    points_yErrUp.push_back(yErrUp);
    double yErrDown = jetToTauFakeRateErrDown;
    points_yErrDown.push_back(yErrDown);
  }
  int numPoints = points_x.size();
  TGraphAsymmErrors* graph_jetToTauFakeRate = new TGraphAsymmErrors(numPoints);
  for ( int idxPoint = 0; idxPoint < numPoints; ++idxPoint ) {
    graph_jetToTauFakeRate->SetPoint(idxPoint, points_x[idxPoint], points_y[idxPoint]);
    graph_jetToTauFakeRate->SetPointError(idxPoint, points_xErrDown[idxPoint], points_xErrUp[idxPoint], points_yErrDown[idxPoint], points_yErrUp[idxPoint]);
  }
  graph_jetToTauFakeRate->SetName(graphName_jetToTauFakeRate.data());
  return graph_jetToTauFakeRate;
}

// function compRatioGraph taken from tthAnalysis/HiggsToTauTau/src/graphAuxFunctions.cc
TGraphAsymmErrors *
compRatioGraph(const std::string & ratioGraphName,
               const TGraph * numerator,
               const TGraph * denominator)
{
  assert(numerator->GetN() == denominator->GetN());
  const int nPoints = numerator->GetN();

  TGraphAsymmErrors * const graphRatio = new TGraphAsymmErrors(nPoints);
  graphRatio->SetName(ratioGraphName.data());

  for( int idxPoint = 0; idxPoint < nPoints; ++idxPoint)
  {
    double x_numerator, y_numerator;
    numerator->GetPoint(idxPoint, x_numerator, y_numerator);

    double xErrUp_numerator = 0.;
    double xErrDown_numerator = 0.;
    double yErrUp_numerator = 0.;
    double yErrDown_numerator = 0.;
    if(dynamic_cast<const TGraphAsymmErrors *>(numerator))
    {
      const TGraphAsymmErrors * const numerator_asymmerrors = dynamic_cast<const TGraphAsymmErrors *>(numerator);
      xErrUp_numerator = numerator_asymmerrors->GetErrorXhigh(idxPoint);
      xErrDown_numerator = numerator_asymmerrors->GetErrorXlow(idxPoint);
      yErrUp_numerator = numerator_asymmerrors->GetErrorYhigh(idxPoint);
      yErrDown_numerator = numerator_asymmerrors->GetErrorYlow(idxPoint);
    }
    else if(dynamic_cast<const TGraphErrors *>(numerator))
    {
      const TGraphErrors * const numerator_errors = dynamic_cast<const TGraphErrors *>(numerator);
      xErrUp_numerator = numerator_errors->GetErrorX(idxPoint);
      xErrDown_numerator = xErrUp_numerator;
      yErrUp_numerator = numerator_errors->GetErrorY(idxPoint);
      yErrDown_numerator = yErrUp_numerator;
    }

    double x_denominator, y_denominator;
    denominator->GetPoint(idxPoint, x_denominator, y_denominator);
    assert(std::fabs(x_denominator - x_numerator) < 1.e-5);

    double xErrUp_denominator = 0.;
    double xErrDown_denominator = 0.;
    double yErrUp_denominator = 0.;
    double yErrDown_denominator = 0.;
    if(dynamic_cast<const TGraphAsymmErrors *>(denominator))
    {
      const TGraphAsymmErrors * const denominator_asymmerrors = dynamic_cast<const TGraphAsymmErrors *>(denominator);
      xErrUp_denominator = denominator_asymmerrors->GetErrorXhigh(idxPoint);
      xErrDown_denominator = denominator_asymmerrors->GetErrorXlow(idxPoint);
      yErrUp_denominator = denominator_asymmerrors->GetErrorYhigh(idxPoint);
      yErrDown_denominator = denominator_asymmerrors->GetErrorYlow(idxPoint);
    }
    else if( dynamic_cast<const TGraphErrors *>(denominator))
    {
      const TGraphErrors * const denominator_errors = dynamic_cast<const TGraphErrors *>(denominator);
      xErrUp_denominator = denominator_errors->GetErrorX(idxPoint);
      xErrDown_denominator = xErrUp_denominator;
      yErrUp_denominator = denominator_errors->GetErrorY(idxPoint);
      yErrDown_denominator = yErrUp_denominator;
    }

    const double x_ratio = x_numerator;
    const double y_ratio = y_denominator > 0. ? y_numerator / y_denominator : 0.;

    const double xErrUp_ratio = std::max(xErrUp_numerator, xErrUp_denominator);
    const double xErrDown_ratio = std::max(xErrDown_numerator, xErrDown_denominator);
    double yErr2Up_ratio =
      square(yErrUp_numerator     / (y_numerator   != 0. ? y_numerator   : 1.)) +
      square(yErrDown_denominator / (y_denominator != 0. ? y_denominator : 1.))
    ;

    double yErrUp_ratio = std::sqrt(yErr2Up_ratio) * (y_ratio != 0. ? std::fabs(y_ratio) : 1.);
    double yErr2Down_ratio =
      square(yErrDown_numerator / (y_numerator   != 0. ? y_numerator   : 1.)) +
      square(yErrUp_denominator / (y_denominator != 0. ? y_denominator : 1.))
    ;
    double yErrDown_ratio = std::sqrt(yErr2Down_ratio) * (y_ratio != 0. ? std::fabs(y_ratio) : 1.);

    graphRatio->SetPoint(idxPoint, x_ratio, y_ratio);
    graphRatio->SetPointError(idxPoint, xErrDown_ratio, xErrUp_ratio, yErrDown_ratio, yErrUp_ratio);
  }
  
  graphRatio->SetLineColor(numerator->GetLineColor());
  graphRatio->SetLineWidth(numerator->GetLineWidth());
  graphRatio->SetMarkerColor(numerator->GetMarkerColor());
  graphRatio->SetMarkerStyle(numerator->GetMarkerStyle());
  graphRatio->SetMarkerSize(numerator->GetMarkerSize());

  return graphRatio;
}
//-------------------------------------------------------------------------------

void addLabel_CMS_simulation(double x0, double y0)
{
  TPaveText* label_cms = new TPaveText(x0, y0 - 0.0075, x0 + 0.0900, y0 + 0.0475, "NDC");
  label_cms->AddText("CMS");
  label_cms->SetTextFont(61);
  label_cms->SetTextAlign(13);
  label_cms->SetTextSize(0.055);
  label_cms->SetTextColor(1);
  label_cms->SetFillStyle(0);
  label_cms->SetBorderSize(0);
  label_cms->Draw();
  
  TPaveText* label_preliminary = new TPaveText(x0 + 0.1100, y0 - 0.0050, x0 + 0.3200, y0 + 0.0450, "NDC");
  label_preliminary->AddText("Simulation");
  label_preliminary->SetTextFont(52);
  label_preliminary->SetTextAlign(13);
  label_preliminary->SetTextSize(0.050);
  label_preliminary->SetTextColor(1);
  label_preliminary->SetFillStyle(0);
  label_preliminary->SetBorderSize(0);
  label_preliminary->Draw();
}

void copyGraphStyle(const TGraph* graph_source, TGraph* graph_target)
{
  graph_target->SetMarkerStyle(graph_source->GetMarkerStyle());
  graph_target->SetMarkerColor(graph_source->GetMarkerColor());
  graph_target->SetMarkerSize(graph_source->GetMarkerSize());
  graph_target->SetLineStyle(graph_source->GetLineStyle());
  graph_target->SetLineColor(graph_source->GetLineColor());
  graph_target->SetLineWidth(graph_source->GetLineWidth());
  graph_target->SetFillStyle(graph_source->GetFillStyle());
  graph_target->SetFillColor(graph_source->GetFillColor());
}

void makePlot_FF(TGraphAsymmErrors* graph_uds, 
                 TGraphAsymmErrors* graph_c, 
                 TGraphAsymmErrors* graph_b,  
                 TGraphAsymmErrors* graph_gluon,
                 double xMin, double xMax, const std::string& xAxisTitle,
                 bool useLogScale, double yMin, double yMax, double yMin_ratio, double yMax_ratio,
                 const std::string& outputFilePath, const std::string& outputFileName)
{
  TCanvas* canvas = new TCanvas("canvas", "canvas", 850, 1100);
  canvas->SetFillColor(10);
  canvas->SetBorderSize(2);
  canvas->Draw();

  TPad* topPad = new TPad("topPad", "topPad", 0.00, 0.32, 1.00, 1.00);
  topPad->SetFillColor(10);
  topPad->SetTopMargin(0.08);
  topPad->SetLeftMargin(0.18);
  topPad->SetBottomMargin(0.03);
  topPad->SetRightMargin(0.04);
  topPad->SetLogy(useLogScale);
  
  TPad* bottomPad = new TPad("bottomPad", "bottomPad", 0.00, 0.00, 1.00, 0.34);
  bottomPad->SetFillColor(10);
  bottomPad->SetTopMargin(0.00);
  bottomPad->SetLeftMargin(0.18);
  bottomPad->SetBottomMargin(0.35);
  bottomPad->SetRightMargin(0.04);
  bottomPad->SetLogy(false);

  canvas->cd();
  topPad->Draw();
  topPad->cd();

  TH1* dummyHistogram_top = new TH1F("dummyHistogram_top", "dummyHistogram_top", 10, xMin, xMax);
  dummyHistogram_top->SetTitle("");
  dummyHistogram_top->SetStats(false);
  dummyHistogram_top->SetMinimum(yMin);
  dummyHistogram_top->SetMaximum(yMax);

  TAxis* xAxis_top = dummyHistogram_top->GetXaxis();
  xAxis_top->SetTitleOffset(1.20);
  xAxis_top->SetLabelColor(10);
  xAxis_top->SetTitleColor(10);
  TAxis* yAxis_top = dummyHistogram_top->GetYaxis();
  yAxis_top->SetTitle("Misidentification rate");
  yAxis_top->SetTitleOffset(1.10);
  yAxis_top->SetTitleSize(0.085);
  yAxis_top->SetLabelSize(0.055);
  yAxis_top->SetLabelOffset(0.01);
  canvas->SetTickx(1);
  canvas->SetTicky(1);
  dummyHistogram_top->Draw("axis");

  graph_uds->SetMarkerStyle(20);
  graph_uds->SetMarkerColor(1);
  graph_uds->SetMarkerSize(2);
  graph_uds->SetLineColor(1);
  graph_uds->SetLineWidth(1);
  graph_uds->Draw("Psame");

  graph_c->SetMarkerStyle(21);
  graph_c->SetMarkerColor(8);
  graph_c->SetMarkerSize(2);
  graph_c->SetLineColor(8);
  graph_c->SetLineWidth(1);
  graph_c->Draw("Psame");

  graph_b->SetMarkerStyle(22);
  graph_b->SetMarkerColor(38);
  graph_b->SetMarkerSize(2);
  graph_b->SetLineColor(38);
  graph_b->SetLineWidth(1);
  graph_b->Draw("Psame");
  
  graph_gluon->SetMarkerStyle(23);
  graph_gluon->SetMarkerColor(2);
  graph_gluon->SetMarkerSize(2);
  graph_gluon->SetLineColor(2);
  graph_gluon->SetLineWidth(1);
  graph_gluon->Draw("Psame");

  dummyHistogram_top->Draw("axissame");

  TLegend* legend = new TLegend(0.75, 0.62, 0.93, 0.90, NULL, "brNDC");
  legend->SetFillStyle(0);
  legend->SetBorderSize(0);
  legend->SetFillColor(10);
  legend->SetTextFont(62);
  legend->SetTextSize(0.060);
  legend->SetMargin(0.10);
  legend->AddEntry(graph_uds, " uds", "p");
  legend->AddEntry(graph_c, " c", "p");
  legend->AddEntry(graph_b, " b", "p");
  legend->AddEntry(graph_gluon, " gluon", "p");
  legend->Draw();

  addLabel_CMS_simulation(0.1850, 0.9600);

  canvas->cd();
  bottomPad->Draw();
  bottomPad->cd();
  
  TH1* dummyHistogram_bottom = new TH1F("dummyHistogram_bottom", "dummyHistogram_bottom", 10, xMin, xMax);
  dummyHistogram_bottom->SetTitle("");
  dummyHistogram_bottom->SetStats(false);
  dummyHistogram_bottom->SetMinimum(yMin_ratio);
  dummyHistogram_bottom->SetMaximum(yMax_ratio);

  TAxis* xAxis_bottom = dummyHistogram_bottom->GetXaxis();
  xAxis_bottom->SetTitle(xAxisTitle.data());
  xAxis_bottom->SetNdivisions(505);
  xAxis_bottom->SetTitleOffset(1.08);
  xAxis_bottom->SetTitleSize(1.9*0.080);
  xAxis_bottom->SetLabelSize(1.9*0.060);
  xAxis_bottom->SetLabelOffset(0.02);
  xAxis_bottom->SetTickLength(0.065);
  TAxis* yAxis_bottom = dummyHistogram_bottom->GetYaxis();
  yAxis_bottom->SetTitle("Ratio to uds");
  yAxis_bottom->CenterTitle();
  yAxis_bottom->SetNdivisions(505);
  yAxis_bottom->SetTitleOffset(0.70);
  yAxis_bottom->SetTitleSize(1.5*0.085);
  yAxis_bottom->SetLabelSize(1.7*0.075);
  yAxis_bottom->SetLabelOffset(0.02);
  yAxis_bottom->SetTickLength(0.04);  
  dummyHistogram_bottom->Draw("axis");

  TF1* line = new TF1("line", "1", xAxis_bottom->GetXmin(), xAxis_bottom->GetXmax());
  line->SetLineStyle(3);
  line->SetLineWidth(1.5);
  line->SetLineColor(kBlack);
  line->Draw("same");

  std::string graphName_c_ratio = "graph_c_ratio";
  TGraphAsymmErrors* graph_c_ratio = compRatioGraph(
    graphName_c_ratio, graph_c, graph_uds);
  std::string graphName_b_ratio = "graph_b_ratio";
  TGraphAsymmErrors* graph_b_ratio = compRatioGraph(
    graphName_b_ratio, graph_b, graph_uds);
  std::string graphName_gluon_ratio = "graph_gluon_ratio";
  TGraphAsymmErrors* graph_gluon_ratio = compRatioGraph(
    graphName_gluon_ratio, graph_gluon, graph_uds);
  
  copyGraphStyle(graph_c, graph_c_ratio);
  graph_c_ratio->Draw("Psame");

  copyGraphStyle(graph_b, graph_b_ratio);
  graph_b_ratio->Draw("Psame");

  copyGraphStyle(graph_gluon, graph_gluon_ratio);
  graph_gluon_ratio->Draw("Psame");

  dummyHistogram_bottom->Draw("axissame");

  std::string outputFileName_full = outputFilePath;
  if ( outputFileName_full.find_last_of("/") != (outputFileName_full.size() - 1) ) outputFileName_full.append("/");
  outputFileName_full.append(outputFileName);
  size_t idx = outputFileName_full.find_last_of('.');
  std::string outputFileName_plot = std::string(outputFileName_full, 0, idx);
  canvas->Print(std::string(outputFileName_plot).append(".png").data());
  canvas->Print(std::string(outputFileName_plot).append(".pdf").data());

  delete dummyHistogram_top;
  delete legend;
  delete topPad;
  delete dummyHistogram_bottom;
  delete line;
  delete graph_c_ratio;
  delete graph_b_ratio;
  delete graph_gluon_ratio;
  delete bottomPad;
  delete canvas;
}

/*
  Make plots of the probabilities for gluon and quark jets of different flavour to be misidentified as hadronic tau decays, 
  as shown in Fig. 1 of HIG-15-007 paper

  CV: macro has been adapted to run on hadd_stage2.root files produce by tthAnalyzeRun_jetToTauFakeRate.py jobs
*/
void makeFakeFactorPlots_parton_flavor()
{
  gROOT->SetBatch(true);

  TH1::AddDirectory(false);

  std::vector<std::string> modes;
  modes.push_back("TTemu");
  //modes.push_back("DYmumu");

  std::string inputFilePath = "/hdfs/local/veelken/ttHAnalysis/2017/";
  std::map<std::string, std::string> inputFileNames; // key = mode 
  inputFileNames["TTemu"]  = "2020Mar31/histograms/jetToTauFakeRateTTemu/OS/hadd/hadd_stage2_OS.root";
  inputFileNames["DYmumu"] = "2020Mar31/histograms/jetToTauFakeRateDYmumu/OS/hadd/hadd_stage2_OS.root";

  std::map<std::string, std::string> process_of_interest; // key = mode 
  process_of_interest["TTemu"]  = "TTj";
  process_of_interest["DYmumu"] = "EWKj";

  std::vector<std::string> etaBins;
  etaBins.push_back("absEtaLt1_5");
  //etaBins.push_back("absEta1_5to9_9");

  std::string denominator = "deepVSjVVLoose"; // corresponding to "fakeable" tau definition

  std::vector<std::string> numerators;
  //numerators.push_back("deepVSjVLoose");
  numerators.push_back("deepVSjLoose");
  //numerators.push_back("deepVSjMedium");
  //numerators.push_back("deepVSjTight");
  //numerators.push_back("deepVSjVTight");
  //numerators.push_back("deepVSjVVTight");

  std::vector<std::string> observables;
  observables.push_back("pt");
  //observables.push_back("eta");

  std::string outputFilePath = "/home/veelken/CMSSW_10_2_10_centOS/CMSSW_10_2_10/src/tthAnalysis/HiggsToTauTau/macros/plots/";

  std::map<std::string, std::map<std::string, double>> xMin; // key = etaBin, observable
  xMin["absEtaLt1_5"]["pt"]     =  20.;
  xMin["absEta1_5to9_9"]["pt"]  =  20.;
  xMin["absEtaLt1_5"]["eta"]    =   0.;
  xMin["absEta1_5to9_9"]["eta"] =   1.5;

  std::map<std::string, std::map<std::string, double>> xMax; // key = etaBin, observable
  xMax["absEtaLt1_5"]["pt"]     = 100.;
  xMax["absEta1_5to9_9"]["pt"]  = 100.;
  xMax["absEtaLt1_5"]["eta"]    =   1.5;
  xMax["absEta1_5to9_9"]["eta"] =   2.5;

  std::map<std::string, std::string> xAxisTitles; // key = observable
  xAxisTitles["pt"]             = "p_{T} [GeV]";
  xAxisTitles["eta"]            = "#eta";

  bool useLogScale = false;

  std::map<std::string, std::map<std::string, double>> yMin; // key = etaBin, observable
  yMin["absEtaLt1_5"]["pt"]     =   0.11;
  yMin["absEta1_5to9_9"]["pt"]  =   0.11;
  yMin["absEtaLt1_5"]["eta"]    =   0.11;
  yMin["absEta1_5to9_9"]["eta"] =   0.11;

  std::map<std::string, std::map<std::string, double>> yMax; // key = etaBin, observable
  yMax["absEtaLt1_5"]["pt"]     =   0.49;
  yMax["absEta1_5to9_9"]["pt"]  =   0.49;
  yMax["absEtaLt1_5"]["eta"]    =   0.49;
  yMax["absEta1_5to9_9"]["eta"] =   0.49;

  std::string yAxisTitle = "Misidentification rate";

  for ( std::vector<std::string>::const_iterator mode = modes.begin();
        mode != modes.end(); ++mode ) {
    TFile* inputFile = openFile(inputFilePath, inputFileNames[*mode]);

    for ( std::vector<std::string>::const_iterator etaBin = etaBins.begin();
          etaBin != etaBins.end(); ++etaBin ) {
      for ( std::vector<std::string>::const_iterator observable = observables.begin();
            observable != observables.end(); ++observable ) {

        std::string directoryName_denominator = "jetToTauFakeRate_OS_woTriggerMatching/denominator/";

        std::string histogramName_denominator_uds = Form("%s_pdgId1&2&3/hadTaus/%s/%s", 
          etaBin->data(), process_of_interest[*mode].data(), observable->data());
        TH1* histogram_denominator_uds = loadHistogram(inputFile, directoryName_denominator, histogramName_denominator_uds);
        std::string histogramName_denominator_c = Form("%s_pdgId4/hadTaus/%s/%s", 
          etaBin->data(), process_of_interest[*mode].data(), observable->data());
        TH1* histogram_denominator_c = loadHistogram(inputFile, directoryName_denominator, histogramName_denominator_c);
        std::string histogramName_denominator_b = Form("%s_pdgId5/hadTaus/%s/%s", 
          etaBin->data(), process_of_interest[*mode].data(), observable->data());
        TH1* histogram_denominator_b = loadHistogram(inputFile, directoryName_denominator, histogramName_denominator_b);
        std::string histogramName_denominator_gluon = Form("%s_pdgId21/hadTaus/%s/%s", 
          etaBin->data(), process_of_interest[*mode].data(), observable->data());
        TH1* histogram_denominator_gluon = loadHistogram(inputFile, directoryName_denominator, histogramName_denominator_gluon);

        for ( std::vector<std::string>::const_iterator numerator = numerators.begin();
              numerator != numerators.end(); ++numerator ) {

          std::string directoryName_numerator = Form("jetToTauFakeRate_OS_woTriggerMatching/numerator/%s/", numerator->data());

          std::string histogramName_numerator_uds = Form("%s_pdgId1&2&3/hadTaus/%s/%s", 
            etaBin->data(), process_of_interest[*mode].data(), observable->data());
          TH1* histogram_numerator_uds = loadHistogram(inputFile, directoryName_numerator, histogramName_numerator_uds);
          std::string histogramName_numerator_c = Form("%s_pdgId4/hadTaus/%s/%s", 
            etaBin->data(), process_of_interest[*mode].data(), observable->data());
          TH1* histogram_numerator_c = loadHistogram(inputFile, directoryName_numerator, histogramName_numerator_c);
          std::string histogramName_numerator_b = Form("%s_pdgId5/hadTaus/%s/%s", 
            etaBin->data(), process_of_interest[*mode].data(), observable->data());
          TH1* histogram_numerator_b = loadHistogram(inputFile, directoryName_numerator, histogramName_numerator_b);
          std::string histogramName_numerator_gluon = Form("%s_pdgId21/hadTaus/%s/%s", 
            etaBin->data(), process_of_interest[*mode].data(), observable->data());
          TH1* histogram_numerator_gluon = loadHistogram(inputFile, directoryName_numerator, histogramName_numerator_gluon);

          std::string graphName_uds = "graph_uds";
          TGraphAsymmErrors* graph_uds = getGraph_jetToTauFakeRate(
            histogram_denominator_uds, histogram_numerator_uds, graphName_uds);
          std::string graphName_c = "graph_c";
          TGraphAsymmErrors* graph_c = getGraph_jetToTauFakeRate(
            histogram_denominator_c, histogram_numerator_c, graphName_c);
          std::string graphName_b = "graph_b";
          TGraphAsymmErrors* graph_b = getGraph_jetToTauFakeRate(
            histogram_denominator_b, histogram_numerator_b, graphName_b);
          std::string graphName_gluon = "graph_gluon";
          TGraphAsymmErrors* graph_gluon = getGraph_jetToTauFakeRate(
            histogram_denominator_gluon, histogram_numerator_gluon, graphName_gluon);

          std::string outputFileName = Form("makeFakeFactorPlots_%s_%s_%s_vs_%s.png", 
            mode->data(), numerator->data(), etaBin->data(), observable->data());
          makePlot_FF(
            graph_uds, 
            graph_c, 
            graph_b,  
            graph_gluon,
            xMin[*etaBin][*observable], xMax[*etaBin][*observable], xAxisTitles[*observable],
            useLogScale, yMin[*etaBin][*observable], yMax[*etaBin][*observable], 0.01, 1.99, 
            outputFilePath, outputFileName);

          delete graph_uds;
          delete graph_c;
          delete graph_b;
          delete graph_gluon;
        }
      }
    }

    delete inputFile;
  }
}
