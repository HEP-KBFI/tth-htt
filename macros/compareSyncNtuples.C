
/** \macro compareSyncNtuples.C
 *
 * Compare branches in synchronization Ntuples produced by different groups for ttH, H -> tautau analysis
 *
 * See https://twiki.cern.ch/twiki/bin/viewauth/CMS/TTHtautauFor13TeV for details.
 *
 * \authors Thomas Strebler, LLR
 *          Christian Veelken, Tallinn
 *
 * (modified by Karl Ehatäht)
 */

#include <TFile.h>
#include <TTree.h>
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
#include <TError.h>

#include <string> // std::string
#include <vector> // std::vector<>
#include <map> // std::map<>
#include <iostream> // std::cout, std::cerr, std::endl
#include <assert.h> // assert()
#include <cstdio> // std::snprintf()

#include <sys/stat.h> // mkdir(), S_IRWXU
#include <unistd.h> // uid_t
#include <pwd.h> // struct passwd, getpwuid()

//-------------------------------------------------------------------------------

static void _mkdir(const char *dir)
{
  char tmp[256];
  char *p = NULL;
  std::size_t len;

  std::snprintf(tmp, sizeof(tmp), "%s", dir);
  len = strlen(tmp);
  if(tmp[len - 1] == '/') tmp[len - 1] = 0;
  for(p = tmp + 1; *p; p++)
    if(*p == '/') {
      *p = 0;
      mkdir(tmp, S_IRWXU);
      *p = '/';
    }
  mkdir(tmp, S_IRWXU);
}

static std::string _whoami()
{
  uid_t uid = geteuid();
  struct passwd *pw = getpwuid(uid);
  if (pw)
  {
    return pw->pw_name;
  }

  return "";
}

//-------------------------------------------------------------------------------

struct
NtupleMetaData
{
  NtupleMetaData() = default;
  NtupleMetaData(const std::string & inputFilePath_,
                 const std::string & inputFileName_,
                 const std::string & dirName_,
                 const std::string & treeName_,
                 const std::string & legendEntry_,
                 const std::string & selection_)
  : inputFilePath(inputFilePath_)
  , inputFileName(inputFileName_)
  , dirName(dirName_)
  , treeName(treeName_)
  , legendEntry(legendEntry_)
  , selection(selection_)
  {}
  const std::string inputFilePath;
  const std::string inputFileName;
  const std::string dirName;
  const std::string treeName;
  const std::string legendEntry;
  const std::string selection;
};

//-------------------------------------------------------------------------------
/* *************************** EDIT THIS ***************************************/

const std::string base_dir = "/home/" + _whoami() + "/sandbox/sync_ntuples/";
//const std::string inputbase_dir = "/hdfs/local/karl/syncNtuples/comparison/";
const std::string inputbase_dir = "/home/karl/cms/root_files/sync_ntuples/";
const std::map<std::string, std::map<std::string, NtupleMetaData>> ntupleMetadataMap = {
  { "tth", { { "llr",     { inputbase_dir + "llr",     "syncNtuple_ttH_80X.root",               "", "syncTree", "LLR",     "" } },
             { "tallinn", { inputbase_dir + "tallinn", "ttHJetToNonbb_M125_13TeV_sync_v0.root", "", "tree",     "Tallinn", "" } } } }
};

//-------------------------------------------------------------------------------

TFile* openFile(const std::string& filePath, const std::string& fileName)
{
  TString fileName_full = filePath.data();
  if ( !fileName_full.EndsWith("/") ) fileName_full.Append("/");
  fileName_full.Append(fileName.data());
  TFile* file = TFile::Open(fileName_full.Data());
  if ( !file ) {
    std::cerr << "Failed to open file = " << fileName_full.Data() << " --> aborting !!" << std::endl;
    assert(0);
  }
  return file;
}

TTree* loadTree(TFile* file, const std::string& treeName, const std::string & dirName = "")
{
  TTree* tree = nullptr;
  if(dirName != "")
  {
    TDirectory * dir = dynamic_cast<TDirectory *>(file->Get(dirName.c_str()));
    if(!dir)
    {
      std::cerr << "Failed to open subdirectory = " << dirName << " from file = " << file->GetName() << " --> aborting !!\n";
      assert(0);
    }
    tree = dynamic_cast<TTree*>(dir->Get(treeName.data()));
  }
  else
    tree = dynamic_cast<TTree*>(file->Get(treeName.data()));

  if ( !tree ) {
    std::cerr << "Failed to load tree = " << treeName << " from file = " << file->GetName() << " --> aborting !!" << std::endl;
    assert(0);
  }
  return tree;
}

void normalizeHistogram(TH1* histogram)
{
  //if ( !histogram->GetSumw2() ) histogram->Sumw2();
  if ( histogram->Integral() > 0. ) histogram->Scale(1./histogram->Integral());
}

enum { kUndefined, kInt, kFloat };

struct branchEntryType
{
  branchEntryType()
    : histogram_(0)
  {}
  branchEntryType(const std::string& branchName, const std::string& branchType, const std::string& extraSelection, int numBins, double xMin, double xMax)
    : branchName_(branchName),
      branchType_(branchType),
      extraSelection_(extraSelection),
      numBins_(numBins),
      xMin_(xMin),
      xMax_(xMax)
  {
    histogramName_ = Form("histogram_%s", branchName_.data());
    histogram_ = new TH1D(histogramName_.data(), histogramName_.data(), numBins_, xMin_, xMax_);
    histogram_->Sumw2();
  }
  ~branchEntryType() 
  {
    delete histogram_;
  }
  branchEntryType* Clone(const std::string& label) const
  {
    branchEntryType* clone = new branchEntryType();
    clone->branchName_ = branchName_;
    clone->branchType_ = branchType_;
    clone->extraSelection_ = extraSelection_;
    clone->numBins_ = numBins_;
    clone->xMin_ = xMin_;
    clone->xMax_ = xMax_;
    clone->histogramName_ = Form("histogram_%s_%s", clone->branchName_.data(), label.data());
    clone->histogram_ = new TH1D(clone->histogramName_.data(), clone->histogramName_.data(), clone->numBins_, clone->xMin_, clone->xMax_);
    clone->histogram_->Sumw2();
    return clone;
  }
  int fillHistogram(TTree* tree, const std::string& selection)
  {
    std::string half_pipe = ">";
    std::string drawCommand = Form("%s >> %s", branchName_.data(), histogramName_.data());
    std::string selection_full;
    if      ( selection != "" && extraSelection_ != "" ) selection_full = Form("(%s) && (%s)", selection.data(), extraSelection_.data());
    else if ( selection != ""                          ) selection_full = selection;
    else if (                    extraSelection_ != "" ) selection_full = extraSelection_;
    int err_code = tree->Draw(drawCommand.data(), selection_full.data(), "goff");
    //normalizeHistogram(histogram_);
    return err_code;
  }
  std::string branchName_;
  std::string branchType_;
  std::string extraSelection_;
  int numBins_;
  double xMin_;
  double xMax_;
  std::string histogramName_;
  TH1D* histogram_;
};

//-------------------------------------------------------------------------------

std::string getLegendEntry(const std::string& legendEntry, const TH1* histogram)
{
  std::string legendEntry_full = Form("%s: Entries = %1.0f, Mean = %1.2f, RMS = %1.2f", legendEntry.data(), histogram->GetEntries(), histogram->GetMean(), histogram->GetRMS());
  return legendEntry_full;
}

TH1* compRatioHistogram(const std::string& ratioHistogramName, const TH1* numerator, const TH1* denominator)
{
  TH1* histogramRatio = 0;
  
  if ( numerator->GetDimension() == denominator->GetDimension() &&
       numerator->GetNbinsX() == denominator->GetNbinsX() ) {
    histogramRatio = (TH1*)numerator->Clone(ratioHistogramName.data());
    histogramRatio->Divide(denominator);
    
    int nBins = histogramRatio->GetNbinsX();
    for ( int iBin = 1; iBin <= nBins; ++iBin ){
      double binContent = histogramRatio->GetBinContent(iBin);
      histogramRatio->SetBinContent(iBin, binContent - 1.);
    }
    
    histogramRatio->SetLineColor(numerator->GetLineColor());
    histogramRatio->SetLineWidth(numerator->GetLineWidth());
    histogramRatio->SetMarkerColor(numerator->GetMarkerColor());
    histogramRatio->SetMarkerStyle(numerator->GetMarkerStyle());
    histogramRatio->SetMarkerSize(numerator->GetMarkerSize());
  }

  return histogramRatio;
}

void showHistograms(double canvasSizeX, double canvasSizeY,
		    TH1* histogram_ref, const std::string& legendEntry_ref, 
		    TH1* histogram2, const std::string& legendEntry2, 
		    TH1* histogram3, const std::string& legendEntry3, 
		    TH1* histogram4, const std::string& legendEntry4, 
		    TH1* histogram5, const std::string& legendEntry5, 
		    TH1* histogram6, const std::string& legendEntry6, 
		    const std::string& xAxisTitle, double xAxisOffset,
		    bool useLogScale, double yMin, double yMax, const std::string& yAxisTitle, double yAxisOffset,
		    double legendX0, double legendY0, 
		    const std::string& outputFilePath, const std::string& outputFileName)
{
  if(! histogram_ref) return;

  TCanvas* canvas = new TCanvas("canvas", "canvas", canvasSizeX, canvasSizeY);
  canvas->SetFillColor(10);
  canvas->SetBorderSize(2);
  canvas->SetLeftMargin(0.12);
  canvas->SetBottomMargin(0.12);

  TPad* topPad = new TPad("topPad", "topPad", 0.00, 0.35, 1.00, 1.00);
  topPad->SetFillColor(10);
  topPad->SetTopMargin(0.04);
  topPad->SetLeftMargin(0.15);
  topPad->SetBottomMargin(0.03);
  topPad->SetRightMargin(0.05);
  topPad->SetLogy(useLogScale);

  TPad* bottomPad = new TPad("bottomPad", "bottomPad", 0.00, 0.00, 1.00, 0.35);
  bottomPad->SetFillColor(10);
  bottomPad->SetTopMargin(0.02);
  bottomPad->SetLeftMargin(0.15);
  bottomPad->SetBottomMargin(0.24);
  bottomPad->SetRightMargin(0.05);
  bottomPad->SetLogy(false);

  canvas->cd();
  topPad->Draw();
  topPad->cd();

  //int colors[6] = { kBlack, kGreen - 6, kBlue - 7,  kMagenta - 7, kCyan - 6, kRed - 6 };
  int colors[6] = { kBlack, kRed, kBlue - 7,  kMagenta - 7, kCyan - 6, kRed - 6 };
  int markerStyles[6] = { 24, 25, 20, 21, 22, 23 };
  int markerSizes[6] = { 1, 1, 1, 1, 1, 1 };

  TLegend* legend = new TLegend(legendX0, legendY0, 0.87, 0.93, "", "brNDC"); 
  legend->SetBorderSize(0);
  legend->SetFillColor(0);
  legend->SetTextSize(0.040);

  histogram_ref->SetTitle("");
  histogram_ref->SetStats(false);
  histogram_ref->SetMinimum(yMin);
  histogram_ref->SetMaximum(yMax);
  histogram_ref->SetLineColor(colors[0]);
  histogram_ref->SetLineWidth(2);
  histogram_ref->SetMarkerColor(colors[0]);
  histogram_ref->SetMarkerStyle(markerStyles[0]);
  histogram_ref->SetMarkerSize(markerSizes[0]);
  histogram_ref->Draw("e1p");
  legend->AddEntry(histogram_ref, getLegendEntry(legendEntry_ref, histogram_ref).data(), "p");

  TAxis* xAxis_top = histogram_ref->GetXaxis();
  xAxis_top->SetTitle(xAxisTitle.data());
  xAxis_top->SetTitleOffset(xAxisOffset);
  xAxis_top->SetLabelColor(10);
  xAxis_top->SetTitleColor(10);

  TAxis* yAxis_top = histogram_ref->GetYaxis();
  yAxis_top->SetTitle(yAxisTitle.data());
  yAxis_top->SetTitleOffset(yAxisOffset);

  if ( histogram2 ) {
    histogram2->SetLineColor(colors[1]);
    histogram2->SetLineWidth(2);
    histogram2->SetMarkerColor(colors[1]);
    histogram2->SetMarkerStyle(markerStyles[1]);
    histogram2->SetMarkerSize(markerSizes[1]);
    histogram2->Draw("e1psame");
    legend->AddEntry(histogram2, getLegendEntry(legendEntry2, histogram2).data(), "p");
  }

  if ( histogram3 ) {
    histogram3->SetLineColor(colors[2]);
    histogram3->SetLineWidth(2);
    histogram3->SetMarkerColor(colors[2]);
    histogram3->SetMarkerStyle(markerStyles[2]);
    histogram3->SetMarkerSize(markerSizes[2]);
    histogram3->Draw("e1psame");
    legend->AddEntry(histogram3, getLegendEntry(legendEntry3, histogram3).data(), "p");
  }

  if ( histogram4 ) {
    histogram4->SetLineColor(colors[3]);
    histogram4->SetLineWidth(2);
    histogram4->SetMarkerColor(colors[3]);
    histogram4->SetMarkerStyle(markerStyles[3]);
    histogram4->SetMarkerSize(markerSizes[3]);
    histogram4->Draw("e1psame");
    legend->AddEntry(histogram4, getLegendEntry(legendEntry4, histogram4).data(), "p");
  }

  if ( histogram5 ) {
    histogram5->SetLineColor(colors[4]);
    histogram5->SetLineWidth(2);
    histogram5->SetMarkerColor(colors[4]);
    histogram5->SetMarkerStyle(markerStyles[4]);
    histogram5->SetMarkerSize(markerSizes[4]);
    histogram5->Draw("e1psame");
    legend->AddEntry(histogram5, getLegendEntry(legendEntry5, histogram5).data(), "p");
  }

  if ( histogram6 ) {
    histogram6->SetLineColor(colors[5]);
    histogram6->SetLineWidth(2);
    histogram6->SetMarkerColor(colors[5]);
    histogram6->SetMarkerStyle(markerStyles[5]);
    histogram6->SetMarkerSize(markerSizes[5]);
    histogram6->Draw("e1psame");
    legend->AddEntry(histogram6, getLegendEntry(legendEntry6, histogram6).data(), "p");
  }

  legend->Draw();

  canvas->cd();
  bottomPad->Draw();
  bottomPad->cd();

  TH1* histogram2_div_ref = 0;
  if ( histogram2 ) {
    std::string histogramName2_div_ref = std::string(histogram2->GetName()).append("_div_").append(histogram_ref->GetName());
    histogram2_div_ref = compRatioHistogram(histogramName2_div_ref, histogram2, histogram_ref);
    if ( histogram2_div_ref ) {
      histogram2_div_ref->SetTitle("");
      histogram2_div_ref->SetStats(false);
      histogram2_div_ref->SetMinimum(-0.50);
      histogram2_div_ref->SetMaximum(+0.50);
      
      TAxis* xAxis_bottom = histogram2_div_ref->GetXaxis();
      xAxis_bottom->SetTitle(xAxis_top->GetTitle());
      xAxis_bottom->SetLabelColor(1);
      xAxis_bottom->SetTitleColor(1);
      xAxis_bottom->SetTitleOffset(1.20);
      xAxis_bottom->SetTitleSize(0.08);
      xAxis_bottom->SetLabelOffset(0.02);
      xAxis_bottom->SetLabelSize(0.08);
      xAxis_bottom->SetTickLength(0.055);
      
      TAxis* yAxis_bottom = histogram2_div_ref->GetYaxis();
      yAxis_bottom->SetTitle(Form("#frac{%s - %s}{%s}", legendEntry2.data(), legendEntry_ref.data(), legendEntry_ref.data()));
      yAxis_bottom->SetTitleOffset(0.85);
      yAxis_bottom->SetNdivisions(505);
      yAxis_bottom->CenterTitle();
      yAxis_bottom->SetTitleSize(0.08);
      yAxis_bottom->SetLabelSize(0.08);
      yAxis_bottom->SetTickLength(0.04);  
      
      histogram2_div_ref->Draw("e1p");
    }
  }

  TH1* histogram3_div_ref = 0;
  if ( histogram3 ) {
    std::string histogramName3_div_ref = std::string(histogram3->GetName()).append("_div_").append(histogram_ref->GetName());
    histogram3_div_ref = compRatioHistogram(histogramName3_div_ref, histogram3, histogram_ref);
    if ( histogram3_div_ref ) {
      histogram3_div_ref->SetTitle("");
      histogram3_div_ref->SetStats(false);
      histogram3_div_ref->SetMinimum(-0.50);
      histogram3_div_ref->SetMaximum(+0.50);
      
      TAxis* xAxis_bottom = histogram3_div_ref->GetXaxis();
      xAxis_bottom->SetTitle(xAxis_top->GetTitle());
      xAxis_bottom->SetLabelColor(1);
      xAxis_bottom->SetTitleColor(1);
      xAxis_bottom->SetTitleOffset(1.20);
      xAxis_bottom->SetTitleSize(0.08);
      xAxis_bottom->SetLabelOffset(0.02);
      xAxis_bottom->SetLabelSize(0.08);
      xAxis_bottom->SetTickLength(0.055);
      
      TAxis* yAxis_bottom = histogram3_div_ref->GetYaxis();
      yAxis_bottom->SetTitle(Form("#frac{%s - %s}{%s}", legendEntry3.data(), legendEntry_ref.data(), legendEntry_ref.data()));
      yAxis_bottom->SetTitleOffset(0.85);
      yAxis_bottom->SetNdivisions(505);
      yAxis_bottom->CenterTitle();
      yAxis_bottom->SetTitleSize(0.08);
      yAxis_bottom->SetLabelSize(0.08);
      yAxis_bottom->SetTickLength(0.04);  
      
      if ( histogram2 ) histogram3_div_ref->Draw("e1psame");
      else histogram3_div_ref->Draw("e1p");
    }
  }

  TGraph* graph_line = new TGraph(2);
  graph_line->SetPoint(0, xAxis_top->GetXmin(), 0.);
  graph_line->SetPoint(1, xAxis_top->GetXmax(), 0.);
  graph_line->SetLineColor(8);
  graph_line->SetLineWidth(1);
  graph_line->Draw("L");

  if ( histogram2_div_ref ) histogram2_div_ref->Draw("e1psame");
  if ( histogram3_div_ref ) histogram3_div_ref->Draw("e1psame");

  TH1* histogram4_div_ref = 0;
  if ( histogram4 ) {
    std::string histogramName4_div_ref = std::string(histogram4->GetName()).append("_div_").append(histogram_ref->GetName());
    histogram4_div_ref = compRatioHistogram(histogramName4_div_ref, histogram4, histogram_ref);
    if ( histogram4_div_ref ) {
      histogram4_div_ref->Draw("e1psame");
    }
  }

  TH1* histogram5_div_ref = 0;
  if ( histogram5 ) {
    std::string histogramName5_div_ref = std::string(histogram5->GetName()).append("_div_").append(histogram_ref->GetName());
    histogram5_div_ref = compRatioHistogram(histogramName5_div_ref, histogram5, histogram_ref);
    if ( histogram5_div_ref ) {
      histogram5_div_ref->Draw("e1psame");
    }
  }

  TH1* histogram6_div_ref = 0;
  if ( histogram6 ) {
    std::string histogramName6_div_ref = std::string(histogram6->GetName()).append("_div_").append(histogram_ref->GetName());
    histogram6_div_ref = compRatioHistogram(histogramName6_div_ref, histogram6, histogram_ref);
    if ( histogram6_div_ref ) {
      histogram6_div_ref->Draw("e1psame");
    }
  }
  
  canvas->Update();

  TString outputFileName_full_tstring = outputFilePath.data();
  if ( !outputFileName_full_tstring.EndsWith("/") ) outputFileName_full_tstring.Append("/");
  outputFileName_full_tstring.Append(outputFileName.data());
  std::string outputFileName_full = outputFileName_full_tstring.Data();
  size_t idx = outputFileName_full.find_last_of('.');
  std::string outputFileName_plot = std::string(outputFileName_full, 0, idx);
  if ( useLogScale ) outputFileName_plot.append("_log");
  else outputFileName_plot.append("_linear");
  if ( idx != std::string::npos ) canvas->Print(std::string(outputFileName_plot).append(std::string(outputFileName_full, idx)).data());
  canvas->Print(std::string(outputFileName_plot).append(".png").data());
  
  delete legend;
  delete histogram2_div_ref;
  delete histogram3_div_ref;
  delete histogram4_div_ref;
  delete histogram5_div_ref;
  delete histogram6_div_ref;
  delete topPad;
  delete bottomPad;
  delete canvas;  
}
//-------------------------------------------------------------------------------

void compareSyncNtuples(const std::string & ref_str,
                        const std::string & test_str,
                        const std::string & sample_str)
{
  gROOT->SetBatch(true);
  gErrorIgnoreLevel = kWarning;

  const NtupleMetaData & ref = ntupleMetadataMap.at(sample_str).at(ref_str);
  const NtupleMetaData & test = ntupleMetadataMap.at(sample_str).at(test_str);

  TFile* inputFile_ref = openFile(ref.inputFilePath, ref.inputFileName);
  TTree* tree_ref = loadTree(inputFile_ref, ref.treeName, ref.dirName);
  TFile* inputFile_test = openFile(test.inputFilePath, test.inputFileName);
  TTree* tree_test = loadTree(inputFile_test, test.treeName, test.dirName);

  const std::string outputFilePath = base_dir + "plots/" +
                                     sample_str + "/" + ref.legendEntry + "_vs_" + test.legendEntry;
  struct stat st = {0};
  if(stat(outputFilePath.c_str(), &st) == -1)
    _mkdir(outputFilePath.c_str());

  std::vector<branchEntryType*> branchesToCompare;
  branchesToCompare.push_back(new branchEntryType("n_presel_mu", "I", "", 20, -0.5, 19.5));
  branchesToCompare.push_back(new branchEntryType("n_fakeablesel_mu", "I", "", 20, -0.5, 19.5));
//  branchesToCompare.push_back(new branchEntryType("n_cutsel_mu", "I", "", 20, -0.5, 19.5));
  branchesToCompare.push_back(new branchEntryType("n_mvasel_mu", "I", "", 20, -0.5, 19.5));
  branchesToCompare.push_back(new branchEntryType("n_presel_ele", "I", "", 20, -0.5, 19.5));
  branchesToCompare.push_back(new branchEntryType("n_fakeablesel_ele", "I", "", 20, -0.5, 19.5));
//  branchesToCompare.push_back(new branchEntryType("n_cutsel_ele", "I", "", 20, -0.5, 19.5));
  branchesToCompare.push_back(new branchEntryType("n_mvasel_ele", "I", "", 20, -0.5, 19.5));
  branchesToCompare.push_back(new branchEntryType("n_presel_tau", "I", "", 20, -0.5, 19.5));
  branchesToCompare.push_back(new branchEntryType("n_presel_jet", "I", "", 20, -0.5, 19.5));
  branchesToCompare.push_back(new branchEntryType("mu0_charge", "I", "n_presel_mu >= 1", 3, -1.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("mu0_jetNDauChargedMVASel", "F", "n_presel_mu >= 1", 20, -0.5, 19.5));
  branchesToCompare.push_back(new branchEntryType("mu0_jetPtRel", "F", "n_presel_mu >= 1", 100., -0.01, 10.));
  branchesToCompare.push_back(new branchEntryType("mu0_miniIsoNeutral", "F", "n_presel_mu >= 1", 100, -0.01, 100.));
  branchesToCompare.push_back(new branchEntryType("mu0_miniIsoCharged", "F", "n_presel_mu >= 1", 100, -0.01, 100.));
  branchesToCompare.push_back(new branchEntryType("mu0_E", "F", "n_presel_mu >= 1", 100, 0., 250.));
  branchesToCompare.push_back(new branchEntryType("mu0_conept", "F", "", 100, 0., 1000.));
  branchesToCompare.push_back(new branchEntryType("mu0_jetPtRatio", "F", "n_presel_mu >= 1", 100, -0.01, 3.));
  branchesToCompare.push_back(new branchEntryType("mu0_leptonMVA", "F", "n_presel_mu >= 1", 100, -1., +1.));
  branchesToCompare.push_back(new branchEntryType("mu0_jetCSV", "F", "n_presel_mu >= 1", 100, 0., +1.));
  branchesToCompare.push_back(new branchEntryType("mu0_dpt_div_pt", "F", "n_presel_mu >= 1", 100, 0., +0.25));
  branchesToCompare.push_back(new branchEntryType("mu0_segmentCompatibility", "F", "n_presel_mu >= 1", 100, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("mu0_phi", "F", "n_presel_mu >= 1", 36, -TMath::Pi(), +TMath::Pi()));
  branchesToCompare.push_back(new branchEntryType("mu0_sip3D", "F", "n_presel_mu >= 1", 100, 0., +10.));
  branchesToCompare.push_back(new branchEntryType("mu0_pt", "F", "n_presel_mu >= 1", 100, 0., 250.));
  branchesToCompare.push_back(new branchEntryType("mu0_miniRelIso", "F", "n_presel_mu >= 1", 100, -0.01, 1.));
  branchesToCompare.push_back(new branchEntryType("mu0_dxy", "F", "n_presel_mu >= 1", 100, -0.1, +0.1));
  branchesToCompare.push_back(new branchEntryType("mu0_eta", "F", "n_presel_mu >= 1", 100, -3., +3.));
  branchesToCompare.push_back(new branchEntryType("mu0_dz", "F", "n_presel_mu >= 1", 100, -0.2, +0.2));
  branchesToCompare.push_back(new branchEntryType("mu0_isfakeablesel", "I", "n_presel_mu >= 1", 2, -0.5, +1.5));
//  branchesToCompare.push_back(new branchEntryType("mu0_iscutsel", "I", "n_presel_mu >= 1", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("mu0_ismvasel", "I", "n_presel_mu >= 1", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("mu1_charge", "I", "n_presel_mu >= 2", 3, -1.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("mu1_jetNDauChargedMVASel", "F", "n_presel_mu >= 2", 20, -0.5, 19.5));
  branchesToCompare.push_back(new branchEntryType("mu1_jetPtRel", "F", "n_presel_mu >= 2", 100., -0.01, 10.));
  branchesToCompare.push_back(new branchEntryType("mu1_miniIsoNeutral", "F", "n_presel_mu >= 2", 100, -0.01, 100.));
  branchesToCompare.push_back(new branchEntryType("mu1_miniIsoCharged", "F", "n_presel_mu >= 2", 100, -0.01, 100.));
  branchesToCompare.push_back(new branchEntryType("mu1_E", "F", "n_presel_mu >= 2", 100, 0., 250.));
  branchesToCompare.push_back(new branchEntryType("mu1_conept", "F", "", 100, 0., 500.));
  branchesToCompare.push_back(new branchEntryType("mu1_jetPtRatio", "F", "n_presel_mu >= 2", 100, -0.01, 3.));
  branchesToCompare.push_back(new branchEntryType("mu1_leptonMVA", "F", "n_presel_mu >= 2", 100, -1., +1.));
  branchesToCompare.push_back(new branchEntryType("mu1_jetCSV", "F", "n_presel_mu >= 2", 100, 0., +1.));
  branchesToCompare.push_back(new branchEntryType("mu1_dpt_div_pt", "F", "n_presel_mu >= 2", 100, 0., +0.25));
  branchesToCompare.push_back(new branchEntryType("mu1_segmentCompatibility", "F", "n_presel_mu >= 2", 100, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("mu1_phi", "F", "n_presel_mu >= 2", 36, -TMath::Pi(), +TMath::Pi()));
  branchesToCompare.push_back(new branchEntryType("mu1_sip3D", "F", "n_presel_mu >= 2", 100, 0., +10.));
  branchesToCompare.push_back(new branchEntryType("mu1_pt", "F", "n_presel_mu >= 2", 100, 0., 250.));
  branchesToCompare.push_back(new branchEntryType("mu1_miniRelIso", "F", "n_presel_mu >= 2", 100, -0.01, 1.));
  branchesToCompare.push_back(new branchEntryType("mu1_dxy", "F", "n_presel_mu >= 2", 100, -0.1, +0.1));
  branchesToCompare.push_back(new branchEntryType("mu1_eta", "F", "n_presel_mu >= 2", 100, -3., +3.));
  branchesToCompare.push_back(new branchEntryType("mu1_dz", "F", "n_presel_mu >= 2", 100, -0.2, +0.2));
  branchesToCompare.push_back(new branchEntryType("mu1_isfakeablesel", "I", "n_presel_mu >= 1", 2, -0.5, +1.5));
//  branchesToCompare.push_back(new branchEntryType("mu1_iscutsel", "I", "n_presel_mu >= 2", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("mu1_ismvasel", "I", "n_presel_mu >= 2", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("ele0_ntMVAeleID", "F", "n_presel_ele >= 1", 100, -1., +1.));
  branchesToCompare.push_back(new branchEntryType("ele0_charge", "I", "n_presel_ele >= 1", 3, -1.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("ele0_jetNDauChargedMVASel", "F", "n_presel_ele >= 1", 20, -0.5, +19.5));
  branchesToCompare.push_back(new branchEntryType("ele0_jetPtRel", "F", "n_presel_ele >= 1", 100, -0.01, 10.));
  branchesToCompare.push_back(new branchEntryType("ele0_miniIsoNeutral", "F", "n_presel_ele >= 1", 100, -0.01, 100.));
  branchesToCompare.push_back(new branchEntryType("ele0_miniIsoCharged", "F", "n_presel_ele >= 1", 100, -0.01, 100.));
  branchesToCompare.push_back(new branchEntryType("ele0_E", "F", "n_presel_ele >= 1", 100, 0., 250.));
  branchesToCompare.push_back(new branchEntryType("ele0_conept", "F", "", 100, 0., 1000.));
  branchesToCompare.push_back(new branchEntryType("ele0_jetPtRatio", "F", "n_presel_ele >= 1", 100, -0.01, 3.));
  branchesToCompare.push_back(new branchEntryType("ele0_leptonMVA", "F", "n_presel_ele >= 1", 100, -1., +1.));
  branchesToCompare.push_back(new branchEntryType("ele0_jetCSV", "F", "n_presel_ele >= 1", 100, 0., +1.));
  branchesToCompare.push_back(new branchEntryType("ele0_phi", "F", "n_presel_ele >= 1", 36, -TMath::Pi(), +TMath::Pi()));
  branchesToCompare.push_back(new branchEntryType("ele0_sip3D", "F", "n_presel_ele >= 1", 100, 0., +10.));
  branchesToCompare.push_back(new branchEntryType("ele0_pt", "F", "n_presel_ele >= 1", 100, 0., 250.));
  branchesToCompare.push_back(new branchEntryType("ele0_miniRelIso", "F", "n_presel_ele >= 1", 100, -0.01, 1.));
  branchesToCompare.push_back(new branchEntryType("ele0_dxy", "F", "n_presel_ele >= 1", 100, -0.1, +0.1));
  branchesToCompare.push_back(new branchEntryType("ele0_eta", "F", "n_presel_ele >= 1", 100, -3.0, +3.0));
  branchesToCompare.push_back(new branchEntryType("ele0_dz", "F", "n_presel_ele >= 1", 100, -0.2, +0.2));
  branchesToCompare.push_back(new branchEntryType("ele0_nMissingHits", "I", "n_presel_ele >= 1", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("ele0_isChargeConsistent", "I", "n_presel_ele >= 1", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("ele0_isfakeablesel", "I", "n_presel_ele >= 1", 2, -0.5, +1.5));
//  branchesToCompare.push_back(new branchEntryType("ele0_iscutsel", "I", "n_presel_ele >= 1", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("ele0_ismvasel", "I", "n_presel_ele >= 1", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("ele1_ntMVAeleID", "F", "n_presel_ele >= 2", 100, -1., +1.));
  branchesToCompare.push_back(new branchEntryType("ele1_charge", "I", "n_presel_ele >= 2", 3, -1.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("ele1_jetNDauChargedMVASel", "F", "n_presel_ele >= 2", 20, -0.5, +19.5));
  branchesToCompare.push_back(new branchEntryType("ele1_jetPtRel", "F", "n_presel_ele >= 2", 100, -0.01, 10.));
  branchesToCompare.push_back(new branchEntryType("ele1_miniIsoNeutral", "F", "n_presel_ele >= 2", 100, -0.01, 100.));
  branchesToCompare.push_back(new branchEntryType("ele1_miniIsoCharged", "F", "n_presel_ele >= 2", 100, -0.01, 100.));
  branchesToCompare.push_back(new branchEntryType("ele1_E", "F", "n_presel_ele >= 2", 100, 0., 250.));
  branchesToCompare.push_back(new branchEntryType("ele1_conept", "F", "", 100, 0., 500.));
  branchesToCompare.push_back(new branchEntryType("ele1_jetPtRatio", "F", "n_presel_ele >= 2", 100, -0.01, 3.));
  branchesToCompare.push_back(new branchEntryType("ele1_leptonMVA", "F", "n_presel_ele >= 2", 100, -1., +1.));
  branchesToCompare.push_back(new branchEntryType("ele1_jetCSV", "F", "n_presel_ele >= 2", 100, 0., +1.));
  branchesToCompare.push_back(new branchEntryType("ele1_phi", "F", "n_presel_ele >= 2", 36, -TMath::Pi(), +TMath::Pi()));
  branchesToCompare.push_back(new branchEntryType("ele1_sip3D", "F", "n_presel_ele >= 2", 100, 0., +10.));
  branchesToCompare.push_back(new branchEntryType("ele1_pt", "F", "n_presel_ele >= 2", 100, 0., 250.));
  branchesToCompare.push_back(new branchEntryType("ele1_miniRelIso", "F", "n_presel_ele >= 2", 100, -0.01, 1.));
  branchesToCompare.push_back(new branchEntryType("ele1_dxy", "F", "n_presel_ele >= 2", 100, -0.1, +0.1));
  branchesToCompare.push_back(new branchEntryType("ele1_eta", "F", "n_presel_ele >= 2", 100, -3.0, +3.0));
  branchesToCompare.push_back(new branchEntryType("ele1_dz", "F", "n_presel_ele >= 2", 100, -0.2, +0.2));
  branchesToCompare.push_back(new branchEntryType("ele1_nMissingHits", "I", "n_presel_ele >= 2", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("ele1_isChargeConsistent", "I", "n_presel_ele >= 2", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("ele1_isfakeablesel", "I", "n_presel_ele >= 2", 2, -0.5, +1.5));
//  branchesToCompare.push_back(new branchEntryType("ele1_iscutsel", "I", "n_presel_ele >= 2", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("ele1_ismvasel", "I", "n_presel_ele >= 2", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau0_againstElectronVTightMVA6", "I", "n_presel_tau >= 1", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau0_againstElectronTightMVA6", "I", "n_presel_tau >= 1", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau0_againstElectronMediumMVA6", "I", "n_presel_tau >= 1", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau0_againstElectronLooseMVA6", "I", "n_presel_tau >= 1", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau0_againstElectronVLooseMVA6", "I", "n_presel_tau >= 1", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau0_againstMuonLoose3", "I", "n_presel_tau >= 1", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau0_byVTightIsolationMVArun2v1DBdR03oldDMwLT", "I", "n_presel_tau >= 1", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau0_byTightIsolationMVArun2v1DBdR03oldDMwLT", "I", "n_presel_tau >= 1", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau0_byMediumIsolationMVArun2v1DBdR03oldDMwLT", "I", "n_presel_tau >= 1", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau0_byLooseCombinedIsolationDeltaBetaCorr3Hits", "I", "n_presel_tau >= 1", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau0_decayModeFindingOldDMs", "I", "n_presel_tau >= 1", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau0_againstMuonTight3", "I", "n_presel_tau >= 1", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau0_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03", "I", "n_presel_tau >= 1", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau0_decayModeFindingNewDMs", "I", "n_presel_tau >= 1", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau0_charge", "I", "n_presel_tau >= 1", 3, -1.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau0_byTightCombinedIsolationDeltaBetaCorr3Hits", "I", "n_presel_tau >= 1", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau0_byMediumCombinedIsolationDeltaBetaCorr3Hits", "I", "n_presel_tau >= 1", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau0_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03", "I", "n_presel_tau >= 1", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau0_byTightCombinedIsolationDeltaBetaCorr3HitsdR03", "I", "n_presel_tau >= 1", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau0_byLooseIsolationMVArun2v1DBdR03oldDMwLT", "F", "n_presel_tau >= 1", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau0_byCombinedIsolationDeltaBetaCorr3Hits", "F", "n_presel_tau >= 1", 100, -0.01, 5.));
  branchesToCompare.push_back(new branchEntryType("tau0_dz", "F", "n_presel_tau >= 1", 100, -0.3, +0.3));
  branchesToCompare.push_back(new branchEntryType("tau0_dxy", "F", "n_presel_tau >= 1", 100, -0.2, +0.2));
  branchesToCompare.push_back(new branchEntryType("tau0_pt", "F", "n_presel_tau >= 1", 100, 0., 250.));
  branchesToCompare.push_back(new branchEntryType("tau0_eta", "F", "n_presel_tau >= 1", 100, -3., +3.));
  branchesToCompare.push_back(new branchEntryType("tau0_phi", "F", "n_presel_tau >= 1", 36, -TMath::Pi(), +TMath::Pi()));
  branchesToCompare.push_back(new branchEntryType("tau0_E", "F", "n_presel_tau >= 1", 100, 0., 250.));
  branchesToCompare.push_back(new branchEntryType("tau1_againstElectronVTightMVA6", "I", "n_presel_tau >= 2", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau1_againstElectronTightMVA6", "I", "n_presel_tau >= 2", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau1_againstElectronMediumMVA6", "I", "n_presel_tau >= 2", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau1_againstElectronLooseMVA6", "I", "n_presel_tau >= 2", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau1_againstElectronVLooseMVA6", "I", "n_presel_tau >= 2", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau1_againstMuonLoose3", "I", "n_presel_tau >= 2", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau1_byVTightIsolationMVArun2v1DBdR03oldDMwLT", "I", "n_presel_tau >= 2", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau1_byTightIsolationMVArun2v1DBdR03oldDMwLT", "I", "n_presel_tau >= 2", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau1_byMediumIsolationMVArun2v1DBdR03oldDMwLT", "I", "n_presel_tau >= 2", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau1_byLooseCombinedIsolationDeltaBetaCorr3Hits", "I", "n_presel_tau >= 2", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau1_decayModeFindingOldDMs", "I", "n_presel_tau >= 2", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau1_againstMuonTight3", "I", "n_presel_tau >= 2", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau1_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03", "I", "n_presel_tau >= 2", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau1_decayModeFindingNewDMs", "I", "n_presel_tau >= 2", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau1_charge", "I", "n_presel_tau >= 2", 3, -1.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau1_byTightCombinedIsolationDeltaBetaCorr3Hits", "I", "n_presel_tau >= 2", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau1_byMediumCombinedIsolationDeltaBetaCorr3Hits", "I", "n_presel_tau >= 2", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau1_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03", "I", "n_presel_tau >= 2", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau1_byTightCombinedIsolationDeltaBetaCorr3HitsdR03", "I", "n_presel_tau >= 2", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau1_byLooseIsolationMVArun2v1DBdR03oldDMwLT", "F", "n_presel_tau >= 2", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau1_byCombinedIsolationDeltaBetaCorr3Hits", "F", "n_presel_tau >= 2", 100, -0.01, 5.));
  branchesToCompare.push_back(new branchEntryType("tau1_dz", "F", "n_presel_tau >= 2", 100, -0.3, +0.3));
  branchesToCompare.push_back(new branchEntryType("tau1_dxy", "F", "n_presel_tau >= 2", 100, -0.2, +0.2));
  branchesToCompare.push_back(new branchEntryType("tau1_pt", "F", "n_presel_tau >= 2", 100, 0., 250.));
  branchesToCompare.push_back(new branchEntryType("tau1_eta", "F", "n_presel_tau >= 2", 100, -3., +3.));
  branchesToCompare.push_back(new branchEntryType("tau1_phi", "F", "n_presel_tau >= 2", 36, -TMath::Pi(), +TMath::Pi()));
  branchesToCompare.push_back(new branchEntryType("tau1_E", "F", "n_presel_tau >= 2", 100, 0., 250.));
  branchesToCompare.push_back(new branchEntryType("jet0_CSV", "F", "n_presel_jet >= 1", 100, 0., +1.));
  branchesToCompare.push_back(new branchEntryType("jet0_pt", "F", "n_presel_jet >= 1", 100, 0., 250.));
  branchesToCompare.push_back(new branchEntryType("jet0_eta", "F", "n_presel_jet >= 1", 100, -3., +3.));
  branchesToCompare.push_back(new branchEntryType("jet0_phi", "F", "n_presel_jet >= 1", 36, -TMath::Pi(), +TMath::Pi()));
  branchesToCompare.push_back(new branchEntryType("jet0_E", "F", "n_presel_jet >= 1", 100, 0., 250.));
  branchesToCompare.push_back(new branchEntryType("jet1_CSV", "F", "n_presel_jet >= 2", 100, 0., +1.));
  branchesToCompare.push_back(new branchEntryType("jet1_pt", "F", "n_presel_jet >= 2", 100, 0., 250.));
  branchesToCompare.push_back(new branchEntryType("jet1_eta", "F", "n_presel_jet >= 2", 100, -3., +3.));
  branchesToCompare.push_back(new branchEntryType("jet1_phi", "F", "n_presel_jet >= 2", 36, -TMath::Pi(), +TMath::Pi()));
  branchesToCompare.push_back(new branchEntryType("jet1_E", "F", "n_presel_jet >= 2", 100, 0., 250.));
  branchesToCompare.push_back(new branchEntryType("jet2_CSV", "F", "n_presel_jet >= 3", 100, 0., +1.));
  branchesToCompare.push_back(new branchEntryType("jet2_pt", "F", "n_presel_jet >= 3", 100, 0., 250.));
  branchesToCompare.push_back(new branchEntryType("jet2_eta", "F", "n_presel_jet >= 3", 100, -3., +3.));
  branchesToCompare.push_back(new branchEntryType("jet2_phi", "F", "n_presel_jet >= 3", 36, -TMath::Pi(), +TMath::Pi()));
  branchesToCompare.push_back(new branchEntryType("jet2_E", "F", "n_presel_jet >= 3", 100, 0., 250.));
  branchesToCompare.push_back(new branchEntryType("jet3_CSV", "F", "n_presel_jet >= 4", 100, 0., +1.));
  branchesToCompare.push_back(new branchEntryType("jet3_pt", "F", "n_presel_jet >= 4", 100, 0., 250.));
  branchesToCompare.push_back(new branchEntryType("jet3_eta", "F", "n_presel_jet >= 4", 100, -3., +3.));
  branchesToCompare.push_back(new branchEntryType("jet3_phi", "F", "n_presel_jet >= 4", 36, -TMath::Pi(), +TMath::Pi()));
  branchesToCompare.push_back(new branchEntryType("jet3_E", "F", "n_presel_jet >= 4", 100, 0., 250.));
  branchesToCompare.push_back(new branchEntryType("PFMET", "F", "", 100, 0., 250.));
  branchesToCompare.push_back(new branchEntryType("PFMETphi", "F", "", 36, -TMath::Pi(), +TMath::Pi()));
  branchesToCompare.push_back(new branchEntryType("MHT", "F", "", 100, 0., 600.));
  branchesToCompare.push_back(new branchEntryType("metLD", "F", "", 100, 0., 2.));
  branchesToCompare.push_back(new branchEntryType("lep0_conept", "F", "", 100, 0., 1000.));
  branchesToCompare.push_back(new branchEntryType("lep1_conept", "F", "", 100, 0., 500.));
  branchesToCompare.push_back(new branchEntryType("mindr_lep0_jet", "F", "", 100, 0., 5.));
  branchesToCompare.push_back(new branchEntryType("mindr_lep1_jet", "F", "", 100, 0., 5.));
//  branchesToCompare.push_back(new branchEntryType("n_jet25_recl", "F", "", 100, 0., 50.));
  branchesToCompare.push_back(new branchEntryType("MT_met_lep0", "F", "", 100, 0., 500.));
  branchesToCompare.push_back(new branchEntryType("avg_dr_jet", "F", "", 100, 0., 6.));
  branchesToCompare.push_back(new branchEntryType("MVA_2lss_ttV", "F", "", 100, -1., 1.));
  branchesToCompare.push_back(new branchEntryType("MVA_2lss_ttbar", "F", "", 100, -1., 1.));

  for ( std::vector<branchEntryType*>::const_iterator branch = branchesToCompare.begin();
        branch != branchesToCompare.end(); ++branch ) {
    std::cout << "plotting " << (*branch)->branchName_ << "..." << std::endl;

    branchEntryType* branch_ref = (*branch)->Clone("ref");
    if(branch_ref->fillHistogram(tree_ref, ref.selection) < 0)
      branch_ref->histogram_ = nullptr;
    else
      normalizeHistogram(branch_ref->histogram_);
    
    branchEntryType* branch_test = (*branch)->Clone("test");
    if(branch_test->fillHistogram(tree_test, test.selection) < 0)
      branch_test->histogram_ = nullptr;
    else
      normalizeHistogram(branch_test->histogram_);

    std::string outputFileName = Form("compareSyncNtuples_%s.png", (*branch)->branchName_.data());
    showHistograms(800, 900, 
                   branch_ref->histogram_, ref.legendEntry,
                   branch_test->histogram_, test.legendEntry,
                   NULL, "",
                   NULL, "",
                   NULL, "",
                   NULL, "",
                   (*branch)->branchName_, 1.10,
                   true, 1.e-4, 1.e+1, "N", 1.30,
                   0.16, 0.80,
                   outputFilePath, outputFileName);

    delete branch_ref;
    delete branch_test;
  }
  
  for ( std::vector<branchEntryType*>::const_iterator it = branchesToCompare.end();
        it != branchesToCompare.end(); ++it ) {
    delete (*it);
  }

  delete inputFile_ref;
  delete inputFile_test;
}

