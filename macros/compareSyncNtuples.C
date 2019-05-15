
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
  NtupleMetaData(const std::vector<std::string> & inputFileNames_,
                 const std::string & legendEntry_,
                 const std::string & selection_,
                 const std::string & inputbase_dir_)
  : inputFileNames(inputFileNames_)
  , legendEntry(legendEntry_)
  , selection(selection_)
  , inputbase_dir(inputbase_dir_)
  {
    for(const std::string inputFileName: inputFileNames)
    {
      const std::string fullPathInputFile = inputbase_dir + "/" + inputFileName;
      TFile * inputFile = TFile::Open(fullPathInputFile.c_str(), "read");
      TList * fileKeys = inputFile->GetListOfKeys();
      TIter it(fileKeys);
      TKey * key = nullptr;
      while((key = static_cast<TKey *>(it())))
      {
        const std::string className(key->GetClassName());
        if(className == "TTree")
        {
          if(! treeNames.count(inputFileName))
          {
            treeNames[inputFileName] = {};
          }
          treeNames[inputFileName].push_back(key->GetName());
        }
      }
      inputFile->Close();
    }
  }
  const std::vector<std::string> inputFileNames;
  std::map<std::string, std::vector<std::string>> treeNames;
  const std::string legendEntry;
  const std::string selection;
  const std::string inputbase_dir;
};

//-------------------------------------------------------------------------------

/* *************************** EDIT THIS ***************************************/

const std::string base_dir = "/home/" + _whoami() + "/sandbox/compare_syncNtuples/plots_Cornell_v9_vs_Tallinn_v22_vs_IHEP_v9_vs_LLR_v11/";
const std::string inputbase_dir = "/home/" + _whoami() + "/sandbox/compare_syncNtuples/";
const std::vector<NtupleMetaData> ntupleMetadataMap = {
    { { "sync_LLR_object_v11.root",          "sync_LLR_event_v3.root"           }, "LLR",     "", inputbase_dir },
    { { "sync_Tallinn_v22.root",             "sync_Tallinn_v22.root"            }, "Tallinn", "", inputbase_dir },
    { { "syncNtuple_object_cornell_v9.root", "syncNtuple_event_cornell_v7.root" }, "Cornell", "", inputbase_dir },
    { { "IHEP_ttHsyncV9.root",               "IHEP_EvtSync_V4.root"             }, "IHEP",    "", inputbase_dir },
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

TTree* loadTree(TFile* file, const std::string& treeName)
{
  TTree* tree = dynamic_cast<TTree*>(file->Get(treeName.data()));

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

void compareSyncNtuples(const std::string & ref_name,
                        const std::string & test_name,
                        const std::string & ref_inputFileName,
                        const std::string & test_inputFileName,
                        const std::string & ref_selection,
                        const std::string & test_selection,
                        const std::string & treeName)
{
  gROOT->SetBatch(true);
  gErrorIgnoreLevel = kWarning;

  std::cout << "Plotting " << treeName << " between "
            << ref_name << " (" << ref_inputFileName << ") and "
            << test_name << " (" << test_inputFileName << ")\n"
  ;

  TFile* inputFile_ref = openFile(inputbase_dir, ref_inputFileName);
  TTree* tree_ref = loadTree(inputFile_ref, treeName);
  TFile* inputFile_test = openFile(inputbase_dir, test_inputFileName);
  TTree* tree_test = loadTree(inputFile_test, treeName);

  const std::string outputFilePath = base_dir + "/" + treeName + "/" + ref_name + "_vs_" + test_name;
  struct stat st = {0};
  if(stat(outputFilePath.c_str(), &st) == -1)
  {
    _mkdir(outputFilePath.c_str());
  }

  std::vector<branchEntryType*> branchesToCompare;
  branchesToCompare.push_back(new branchEntryType("n_presel_mu", "I", "", 20, -0.5, 19.5));
  branchesToCompare.push_back(new branchEntryType("n_fakeablesel_mu", "I", "", 20, -0.5, 19.5));
  branchesToCompare.push_back(new branchEntryType("n_mvasel_mu", "I", "", 20, -0.5, 19.5));
  branchesToCompare.push_back(new branchEntryType("n_presel_ele", "I", "", 20, -0.5, 19.5));
  branchesToCompare.push_back(new branchEntryType("n_fakeablesel_ele", "I", "", 20, -0.5, 19.5));
  branchesToCompare.push_back(new branchEntryType("n_mvasel_ele", "I", "", 20, -0.5, 19.5));
  branchesToCompare.push_back(new branchEntryType("n_presel_tau", "I", "", 20, -0.5, 19.5));
  branchesToCompare.push_back(new branchEntryType("n_presel_jet", "I", "", 20, -0.5, 19.5));
  branchesToCompare.push_back(new branchEntryType("n_presel_jetFwd", "I", "", 20, -0.5, 19.5));
  branchesToCompare.push_back(new branchEntryType("mu1_charge", "I", "n_presel_mu >= 1", 3, -1.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("mu1_jetNDauChargedMVASel", "F", "n_presel_mu >= 1", 20, -0.5, 19.5));
  branchesToCompare.push_back(new branchEntryType("mu1_jetPtRel", "F", "n_presel_mu >= 1", 100., -0.01, 10.));
  branchesToCompare.push_back(new branchEntryType("mu1_miniIsoNeutral", "F", "n_presel_mu >= 1", 100, -0.01, 0.5));
  branchesToCompare.push_back(new branchEntryType("mu1_miniIsoCharged", "F", "n_presel_mu >= 1", 100, -0.01, 0.5));
  branchesToCompare.push_back(new branchEntryType("mu1_PFRelIso04", "F", "n_presel_mu >= 1", 100, -0.01, 10.));
  branchesToCompare.push_back(new branchEntryType("mu1_E", "F", "n_presel_mu >= 1", 100, 0., 250.));
  branchesToCompare.push_back(new branchEntryType("mu1_conept", "F", "", 100, 0., 1000.));
  branchesToCompare.push_back(new branchEntryType("mu1_jetPtRatio", "F", "n_presel_mu >= 1", 100, -0.01, 3.));
  branchesToCompare.push_back(new branchEntryType("mu1_leptonMVA", "F", "n_presel_mu >= 1", 100, -1., +1.));
  branchesToCompare.push_back(new branchEntryType("mu1_jetCSV", "F", "n_presel_mu >= 1", 100, 0., +1.));
  branchesToCompare.push_back(new branchEntryType("mu1_jetDeepCSV", "F", "n_presel_mu >= 1", 100, 0., +1.));
  branchesToCompare.push_back(new branchEntryType("mu1_jetDeepJet", "F", "n_presel_mu >= 1", 100, 0., +1.));
  branchesToCompare.push_back(new branchEntryType("mu1_dpt_div_pt", "F", "n_presel_mu >= 1", 100, 0., +0.25));
  branchesToCompare.push_back(new branchEntryType("mu1_segmentCompatibility", "F", "n_presel_mu >= 1", 100, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("mu1_phi", "F", "n_presel_mu >= 1", 36, -TMath::Pi(), +TMath::Pi()));
  branchesToCompare.push_back(new branchEntryType("mu1_sip3D", "F", "n_presel_mu >= 1", 100, 0., +10.));
  branchesToCompare.push_back(new branchEntryType("mu1_pt", "F", "n_presel_mu >= 1", 100, 0., 250.));
  branchesToCompare.push_back(new branchEntryType("mu1_miniRelIso", "F", "n_presel_mu >= 1", 100, -0.01, 1.));
  branchesToCompare.push_back(new branchEntryType("mu1_dxyAbs", "F", "n_presel_mu >= 1", 100, -0.1, +0.1));
  branchesToCompare.push_back(new branchEntryType("mu1_eta", "F", "n_presel_mu >= 1", 100, -3., +3.));
  branchesToCompare.push_back(new branchEntryType("mu1_dz", "F", "n_presel_mu >= 1", 100, -0.2, +0.2));
  branchesToCompare.push_back(new branchEntryType("mu1_isfakeablesel", "I", "n_presel_mu >= 1", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("mu1_ismvasel", "I", "n_presel_mu >= 1", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("mu1_isGenMatched", "I", "n_presel_mu >= 1", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("mu2_charge", "I", "n_presel_mu >= 2", 3, -1.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("mu2_jetNDauChargedMVASel", "F", "n_presel_mu >= 2", 20, -0.5, 19.5));
  branchesToCompare.push_back(new branchEntryType("mu2_jetPtRel", "F", "n_presel_mu >= 2", 100., -0.01, 10.));
  branchesToCompare.push_back(new branchEntryType("mu2_miniIsoNeutral", "F", "n_presel_mu >= 2", 100, -0.01, 0.5));
  branchesToCompare.push_back(new branchEntryType("mu2_miniIsoCharged", "F", "n_presel_mu >= 2", 100, -0.01, 0.5));
  branchesToCompare.push_back(new branchEntryType("mu2_PFRelIso04", "F", "n_presel_mu >= 2", 100, -0.01, 10.));
  branchesToCompare.push_back(new branchEntryType("mu2_E", "F", "n_presel_mu >= 2", 100, 0., 250.));
  branchesToCompare.push_back(new branchEntryType("mu2_conept", "F", "", 100, 0., 500.));
  branchesToCompare.push_back(new branchEntryType("mu2_jetPtRatio", "F", "n_presel_mu >= 2", 100, -0.01, 3.));
  branchesToCompare.push_back(new branchEntryType("mu2_leptonMVA", "F", "n_presel_mu >= 2", 100, -1., +1.));
  branchesToCompare.push_back(new branchEntryType("mu2_jetCSV", "F", "n_presel_mu >= 2", 100, 0., +1.));
  branchesToCompare.push_back(new branchEntryType("mu2_jetDeepCSV", "F", "n_presel_mu >= 2", 100, 0., +1.));
  branchesToCompare.push_back(new branchEntryType("mu2_jetDeepJet", "F", "n_presel_mu >= 2", 100, 0., +1.));
  branchesToCompare.push_back(new branchEntryType("mu2_dpt_div_pt", "F", "n_presel_mu >= 2", 100, 0., +0.25));
  branchesToCompare.push_back(new branchEntryType("mu2_segmentCompatibility", "F", "n_presel_mu >= 2", 100, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("mu2_phi", "F", "n_presel_mu >= 2", 36, -TMath::Pi(), +TMath::Pi()));
  branchesToCompare.push_back(new branchEntryType("mu2_sip3D", "F", "n_presel_mu >= 2", 100, 0., +10.));
  branchesToCompare.push_back(new branchEntryType("mu2_pt", "F", "n_presel_mu >= 2", 100, 0., 250.));
  branchesToCompare.push_back(new branchEntryType("mu2_miniRelIso", "F", "n_presel_mu >= 2", 100, -0.01, 1.));
  branchesToCompare.push_back(new branchEntryType("mu2_dxyAbs", "F", "n_presel_mu >= 2", 100, -0.1, +0.1));
  branchesToCompare.push_back(new branchEntryType("mu2_eta", "F", "n_presel_mu >= 2", 100, -3., +3.));
  branchesToCompare.push_back(new branchEntryType("mu2_dz", "F", "n_presel_mu >= 2", 100, -0.2, +0.2));
  branchesToCompare.push_back(new branchEntryType("mu2_isfakeablesel", "I", "n_presel_mu >= 2", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("mu2_ismvasel", "I", "n_presel_mu >= 2", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("mu2_isGenMatched", "I", "n_presel_mu >= 2", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("ele1_ntMVAeleID", "F", "n_presel_ele >= 1", 100, -1., +1.));
  branchesToCompare.push_back(new branchEntryType("ele1_charge", "I", "n_presel_ele >= 1", 3, -1.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("ele1_jetNDauChargedMVASel", "F", "n_presel_ele >= 1", 20, -0.5, +19.5));
  branchesToCompare.push_back(new branchEntryType("ele1_jetPtRel", "F", "n_presel_ele >= 1", 100, -0.01, 10.));
  branchesToCompare.push_back(new branchEntryType("ele1_miniIsoNeutral", "F", "n_presel_ele >= 1", 100, -0.01, 0.5));
  branchesToCompare.push_back(new branchEntryType("ele1_miniIsoCharged", "F", "n_presel_ele >= 1", 100, -0.01, 0.5));
  branchesToCompare.push_back(new branchEntryType("ele1_PFRelIso04", "F", "n_presel_ele >= 1", 100, -0.01, 10.));
  branchesToCompare.push_back(new branchEntryType("ele1_E", "F", "n_presel_ele >= 1", 100, 0., 250.));
  branchesToCompare.push_back(new branchEntryType("ele1_conept", "F", "n_presel_ele >= 1", 100, 0., 1000.));
  branchesToCompare.push_back(new branchEntryType("ele1_jetPtRatio", "F", "n_presel_ele >= 1", 100, -0.01, 3.));
  branchesToCompare.push_back(new branchEntryType("ele1_leptonMVA", "F", "n_presel_ele >= 1", 100, -1., +1.));
  branchesToCompare.push_back(new branchEntryType("ele1_jetCSV", "F", "n_presel_ele >= 1", 100, 0., +1.));
  branchesToCompare.push_back(new branchEntryType("ele1_jetDeepCSV", "F", "n_presel_ele >= 1", 100, 0., +1.));
  branchesToCompare.push_back(new branchEntryType("ele1_jetDeepJet", "F", "n_presel_ele >= 1", 100, 0., +1.));
  branchesToCompare.push_back(new branchEntryType("ele1_phi", "F", "n_presel_ele >= 1", 36, -TMath::Pi(), +TMath::Pi()));
  branchesToCompare.push_back(new branchEntryType("ele1_sip3D", "F", "n_presel_ele >= 1", 100, 0., +10.));
  branchesToCompare.push_back(new branchEntryType("ele1_pt", "F", "n_presel_ele >= 1", 100, 0., 250.));
  branchesToCompare.push_back(new branchEntryType("ele1_miniRelIso", "F", "n_presel_ele >= 1", 100, -0.01, 1.));
  branchesToCompare.push_back(new branchEntryType("ele1_dxyAbs", "F", "n_presel_ele >= 1", 100, -0.1, +0.1));
  branchesToCompare.push_back(new branchEntryType("ele1_eta", "F", "n_presel_ele >= 1", 100, -3.0, +3.0));
  branchesToCompare.push_back(new branchEntryType("ele1_dz", "F", "n_presel_ele >= 1", 100, -0.2, +0.2));
  branchesToCompare.push_back(new branchEntryType("ele1_nMissingHits", "I", "n_presel_ele >= 1", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("ele1_sigmaEtaEta", "F", "n_presel_ele >= 1", 100, -0., +0.1));
  branchesToCompare.push_back(new branchEntryType("ele1_HoE", "F", "n_presel_ele >= 1", 100, 0., +0.1));
  branchesToCompare.push_back(new branchEntryType("ele1_deltaEta", "F", "n_presel_ele >= 1", 100, 0., +0.02));
  branchesToCompare.push_back(new branchEntryType("ele1_deltaPhi", "F", "n_presel_ele >= 1", 100, 0., +0.1));
  branchesToCompare.push_back(new branchEntryType("ele1_OoEminusOoP", "F", "n_presel_ele >= 1", 100, 0., +0.02));
  branchesToCompare.push_back(new branchEntryType("ele1_isChargeConsistent", "I", "n_presel_ele >= 1", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("ele1_isfakeablesel", "I", "n_presel_ele >= 1", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("ele1_ismvasel", "I", "n_presel_ele >= 1", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("ele1_isGenMatched", "I", "n_presel_ele >= 1", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("ele2_ntMVAeleID", "F", "n_presel_ele >= 2", 100, -1., +1.));
  branchesToCompare.push_back(new branchEntryType("ele2_charge", "I", "n_presel_ele >= 2", 3, -1.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("ele2_jetNDauChargedMVASel", "F", "n_presel_ele >= 2", 20, -0.5, +19.5));
  branchesToCompare.push_back(new branchEntryType("ele2_jetPtRel", "F", "n_presel_ele >= 2", 100, -0.01, 10.));
  branchesToCompare.push_back(new branchEntryType("ele2_miniIsoNeutral", "F", "n_presel_ele >= 2", 100, -0.01, 0.5));
  branchesToCompare.push_back(new branchEntryType("ele2_miniIsoCharged", "F", "n_presel_ele >= 2", 100, -0.01, 0.5));
  branchesToCompare.push_back(new branchEntryType("ele2_PFRelIso04", "F", "n_presel_ele >= 2", 100, -0.01, 10.));
  branchesToCompare.push_back(new branchEntryType("ele2_E", "F", "n_presel_ele >= 2", 100, 0., 250.));
  branchesToCompare.push_back(new branchEntryType("ele2_conept", "F", "n_presel_ele >= 2", 100, 0., 500.));
  branchesToCompare.push_back(new branchEntryType("ele2_jetPtRatio", "F", "n_presel_ele >= 2", 100, -0.01, 3.));
  branchesToCompare.push_back(new branchEntryType("ele2_leptonMVA", "F", "n_presel_ele >= 2", 100, -1., +1.));
  branchesToCompare.push_back(new branchEntryType("ele2_jetCSV", "F", "n_presel_ele >= 2", 100, 0., +1.));
  branchesToCompare.push_back(new branchEntryType("ele2_jetDeepCSV", "F", "n_presel_ele >= 2", 100, 0., +1.));
  branchesToCompare.push_back(new branchEntryType("ele2_jetDeepJet", "F", "n_presel_ele >= 2", 100, 0., +1.));
  branchesToCompare.push_back(new branchEntryType("ele2_phi", "F", "n_presel_ele >= 2", 36, -TMath::Pi(), +TMath::Pi()));
  branchesToCompare.push_back(new branchEntryType("ele2_sip3D", "F", "n_presel_ele >= 2", 100, 0., +10.));
  branchesToCompare.push_back(new branchEntryType("ele2_pt", "F", "n_presel_ele >= 2", 100, 0., 250.));
  branchesToCompare.push_back(new branchEntryType("ele2_miniRelIso", "F", "n_presel_ele >= 2", 100, -0.01, 1.));
  branchesToCompare.push_back(new branchEntryType("ele2_dxyAbs", "F", "n_presel_ele >= 2", 100, -0.1, +0.1));
  branchesToCompare.push_back(new branchEntryType("ele2_eta", "F", "n_presel_ele >= 2", 100, -3.0, +3.0));
  branchesToCompare.push_back(new branchEntryType("ele2_dz", "F", "n_presel_ele >= 2", 100, -0.2, +0.2));
  branchesToCompare.push_back(new branchEntryType("ele2_nMissingHits", "I", "n_presel_ele >= 2", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("ele2_sigmaEtaEta", "F", "n_presel_ele >= 2", 100, -0., +0.1));
  branchesToCompare.push_back(new branchEntryType("ele2_HoE", "F", "n_presel_ele >= 2", 100, 0., +0.1));
  branchesToCompare.push_back(new branchEntryType("ele2_deltaEta", "F", "n_presel_ele >= 2", 100, 0., +0.02));
  branchesToCompare.push_back(new branchEntryType("ele2_deltaPhi", "F", "n_presel_ele >= 2", 100, 0., +0.1));
  branchesToCompare.push_back(new branchEntryType("ele2_OoEminusOoP", "F", "n_presel_ele >= 2", 100, 0., +0.02));
  branchesToCompare.push_back(new branchEntryType("ele2_isChargeConsistent", "I", "n_presel_ele >= 2", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("ele2_isfakeablesel", "I", "n_presel_ele >= 2", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("ele2_ismvasel", "I", "n_presel_ele >= 2", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("ele2_isGenMatched", "I", "n_presel_ele >= 2", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau1_againstElectronVTightMVA6", "I", "n_presel_tau >= 1", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau1_againstElectronTightMVA6", "I", "n_presel_tau >= 1", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau1_againstElectronMediumMVA6", "I", "n_presel_tau >= 1", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau1_againstElectronLooseMVA6", "I", "n_presel_tau >= 1", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau1_againstElectronVLooseMVA6", "I", "n_presel_tau >= 1", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau1_againstMuonLoose3", "I", "n_presel_tau >= 1", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau1_byVTightIsolationMVArun2v1DBdR03oldDMwLT", "I", "n_presel_tau >= 1", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau1_byTightIsolationMVArun2v1DBdR03oldDMwLT", "I", "n_presel_tau >= 1", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau1_byMediumIsolationMVArun2v1DBdR03oldDMwLT", "I", "n_presel_tau >= 1", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau1_decayModeFindingOldDMs", "I", "n_presel_tau >= 1", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau1_againstMuonTight3", "I", "n_presel_tau >= 1", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau1_decayModeFindingNewDMs", "I", "n_presel_tau >= 1", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau1_charge", "I", "n_presel_tau >= 1", 3, -1.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau1_byLooseIsolationMVArun2v1DBdR03oldDMwLT", "F", "n_presel_tau >= 1", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau1_byVLooseIsolationMVArun2v1DBdR03oldDMwLT", "F", "n_presel_tau >= 1", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau1_rawMVArun2v1DBdR03oldDMwLT", "F", "n_presel_tau >= 1", 100, -0.5, +1.1));
  branchesToCompare.push_back(new branchEntryType("tau1_dz", "F", "n_presel_tau >= 1", 100, -0.3, +0.3));
  branchesToCompare.push_back(new branchEntryType("tau1_dxy", "F", "n_presel_tau >= 1", 100, -0.2, +0.2));
  branchesToCompare.push_back(new branchEntryType("tau1_pt", "F", "n_presel_tau >= 1", 100, 0., 250.));
  branchesToCompare.push_back(new branchEntryType("tau1_eta", "F", "n_presel_tau >= 1", 100, -3., +3.));
  branchesToCompare.push_back(new branchEntryType("tau1_phi", "F", "n_presel_tau >= 1", 36, -TMath::Pi(), +TMath::Pi()));
  branchesToCompare.push_back(new branchEntryType("tau1_E", "F", "n_presel_tau >= 1", 100, 0., 250.));
  branchesToCompare.push_back(new branchEntryType("tau1_isGenMatched", "I", "n_presel_tau >= 1", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau2_againstElectronVTightMVA6", "I", "n_presel_tau >= 2", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau2_againstElectronTightMVA6", "I", "n_presel_tau >= 2", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau2_againstElectronMediumMVA6", "I", "n_presel_tau >= 2", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau2_againstElectronLooseMVA6", "I", "n_presel_tau >= 2", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau2_againstElectronVLooseMVA6", "I", "n_presel_tau >= 2", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau2_againstMuonLoose3", "I", "n_presel_tau >= 2", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau2_byVTightIsolationMVArun2v1DBdR03oldDMwLT", "I", "n_presel_tau >= 2", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau2_byTightIsolationMVArun2v1DBdR03oldDMwLT", "I", "n_presel_tau >= 2", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau2_byMediumIsolationMVArun2v1DBdR03oldDMwLT", "I", "n_presel_tau >= 2", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau2_decayModeFindingOldDMs", "I", "n_presel_tau >= 2", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau2_againstMuonTight3", "I", "n_presel_tau >= 2", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau2_decayModeFindingNewDMs", "I", "n_presel_tau >= 2", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau2_charge", "I", "n_presel_tau >= 2", 3, -1.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau2_byLooseIsolationMVArun2v1DBdR03oldDMwLT", "F", "n_presel_tau >= 2", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau2_byVLooseIsolationMVArun2v1DBdR03oldDMwLT", "F", "n_presel_tau >= 2", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("tau2_rawMVArun2v1DBdR03oldDMwLT", "F", "n_presel_tau >= 2", 100, -0.5, +1.1));
  branchesToCompare.push_back(new branchEntryType("tau2_dz", "F", "n_presel_tau >= 2", 100, -0.3, +0.3));
  branchesToCompare.push_back(new branchEntryType("tau2_dxy", "F", "n_presel_tau >= 2", 100, -0.2, +0.2));
  branchesToCompare.push_back(new branchEntryType("tau2_pt", "F", "n_presel_tau >= 2", 100, 0., 250.));
  branchesToCompare.push_back(new branchEntryType("tau2_eta", "F", "n_presel_tau >= 2", 100, -3., +3.));
  branchesToCompare.push_back(new branchEntryType("tau2_phi", "F", "n_presel_tau >= 2", 36, -TMath::Pi(), +TMath::Pi()));
  branchesToCompare.push_back(new branchEntryType("tau2_E", "F", "n_presel_tau >= 2", 100, 0., 250.));
  branchesToCompare.push_back(new branchEntryType("tau2_isGenMatched", "I", "n_presel_tau >= 2", 2, -0.5, +1.5));
  branchesToCompare.push_back(new branchEntryType("jet1_CSV", "F", "n_presel_jet >= 1", 100, 0., +1.));
  branchesToCompare.push_back(new branchEntryType("jet1_DeepCSV", "F", "n_presel_jet >= 1", 100, 0., +1.));
  branchesToCompare.push_back(new branchEntryType("jet1_DeepJet", "F", "n_presel_jet >= 1", 100, 0., +1.));
  branchesToCompare.push_back(new branchEntryType("jet1_pt", "F", "n_presel_jet >= 1", 100, 0., 250.));
  branchesToCompare.push_back(new branchEntryType("jet1_eta", "F", "n_presel_jet >= 1", 100, -3., +3.));
  branchesToCompare.push_back(new branchEntryType("jet1_phi", "F", "n_presel_jet >= 1", 36, -TMath::Pi(), +TMath::Pi()));
  branchesToCompare.push_back(new branchEntryType("jet1_E", "F", "n_presel_jet >= 1", 100, 0., 250.));
  branchesToCompare.push_back(new branchEntryType("jet1_QGdiscr", "F", "n_presel_jet >= 1", 100, 0., 1.));
  branchesToCompare.push_back(new branchEntryType("jet2_CSV", "F", "n_presel_jet >= 2", 100, 0., +1.));
  branchesToCompare.push_back(new branchEntryType("jet2_DeepCSV", "F", "n_presel_jet >= 2", 100, 0., +1.));
  branchesToCompare.push_back(new branchEntryType("jet2_DeepJet", "F", "n_presel_jet >= 2", 100, 0., +1.));
  branchesToCompare.push_back(new branchEntryType("jet2_pt", "F", "n_presel_jet >= 2", 100, 0., 250.));
  branchesToCompare.push_back(new branchEntryType("jet2_eta", "F", "n_presel_jet >= 2", 100, -3., +3.));
  branchesToCompare.push_back(new branchEntryType("jet2_phi", "F", "n_presel_jet >= 2", 36, -TMath::Pi(), +TMath::Pi()));
  branchesToCompare.push_back(new branchEntryType("jet2_E", "F", "n_presel_jet >= 2", 100, 0., 250.));
  branchesToCompare.push_back(new branchEntryType("jet2_QGdiscr", "F", "n_presel_jet >= 1", 100, 0., 1.));
  branchesToCompare.push_back(new branchEntryType("jet3_CSV", "F", "n_presel_jet >= 3", 100, 0., +1.));
  branchesToCompare.push_back(new branchEntryType("jet3_DeepCSV", "F", "n_presel_jet >= 3", 100, 0., +1.));
  branchesToCompare.push_back(new branchEntryType("jet3_DeepJet", "F", "n_presel_jet >= 3", 100, 0., +1.));
  branchesToCompare.push_back(new branchEntryType("jet3_pt", "F", "n_presel_jet >= 3", 100, 0., 250.));
  branchesToCompare.push_back(new branchEntryType("jet3_eta", "F", "n_presel_jet >= 3", 100, -3., +3.));
  branchesToCompare.push_back(new branchEntryType("jet3_phi", "F", "n_presel_jet >= 3", 36, -TMath::Pi(), +TMath::Pi()));
  branchesToCompare.push_back(new branchEntryType("jet3_E", "F", "n_presel_jet >= 3", 100, 0., 250.));
  branchesToCompare.push_back(new branchEntryType("jet3_QGdiscr", "F", "n_presel_jet >= 1", 100, 0., 1.));
  branchesToCompare.push_back(new branchEntryType("jet4_CSV", "F", "n_presel_jet >= 4", 100, 0., +1.));
  branchesToCompare.push_back(new branchEntryType("jet4_DeepCSV", "F", "n_presel_jet >= 4", 100, 0., +1.));
  branchesToCompare.push_back(new branchEntryType("jet4_DeepJet", "F", "n_presel_jet >= 4", 100, 0., +1.));
  branchesToCompare.push_back(new branchEntryType("jet4_pt", "F", "n_presel_jet >= 4", 100, 0., 250.));
  branchesToCompare.push_back(new branchEntryType("jet4_eta", "F", "n_presel_jet >= 4", 100, -3., +3.));
  branchesToCompare.push_back(new branchEntryType("jet4_phi", "F", "n_presel_jet >= 4", 36, -TMath::Pi(), +TMath::Pi()));
  branchesToCompare.push_back(new branchEntryType("jet4_E", "F", "n_presel_jet >= 4", 100, 0., 250.));
  branchesToCompare.push_back(new branchEntryType("jet4_QGdiscr", "F", "n_presel_jet >= 1", 100, 0., 1.));
  branchesToCompare.push_back(new branchEntryType("jetFwd1_pt", "F", "n_presel_jetFwd >= 1", 100, 0., 250.));
  branchesToCompare.push_back(new branchEntryType("jetFwd1_eta", "F", "n_presel_jetFwd >= 1", 100, -5.1, +5.1));
  branchesToCompare.push_back(new branchEntryType("jetFwd1_phi", "F", "n_presel_jetFwd >= 1", 36, -TMath::Pi(), +TMath::Pi()));
  branchesToCompare.push_back(new branchEntryType("jetFwd1_E", "F", "n_presel_jetFwd >= 1", 100, 0., 600.));
  branchesToCompare.push_back(new branchEntryType("jetFwd2_pt", "F", "n_presel_jetFwd >= 2", 100, 0., 250.));
  branchesToCompare.push_back(new branchEntryType("jetFwd2_eta", "F", "n_presel_jetFwd >= 2", 100, -5.1, +5.1));
  branchesToCompare.push_back(new branchEntryType("jetFwd2_phi", "F", "n_presel_jetFwd >= 2", 36, -TMath::Pi(), +TMath::Pi()));
  branchesToCompare.push_back(new branchEntryType("jetFwd2_E", "F", "n_presel_jetFwd >= 2", 100, 0., 600.));
  branchesToCompare.push_back(new branchEntryType("jetFwd3_pt", "F", "n_presel_jetFwd >= 3", 100, 0., 250.));
  branchesToCompare.push_back(new branchEntryType("jetFwd3_eta", "F", "n_presel_jetFwd >= 3", 100, -5.1, +5.1));
  branchesToCompare.push_back(new branchEntryType("jetFwd3_phi", "F", "n_presel_jetFwd >= 3", 36, -TMath::Pi(), +TMath::Pi()));
  branchesToCompare.push_back(new branchEntryType("jetFwd3_E", "F", "n_presel_jetFwd >= 3", 100, 0., 600.));
  branchesToCompare.push_back(new branchEntryType("jetFwd4_pt", "F", "n_presel_jetFwd >= 4", 100, 0., 250.));
  branchesToCompare.push_back(new branchEntryType("jetFwd4_eta", "F", "n_presel_jetFwd >= 4", 100, -5.1, +5.1));
  branchesToCompare.push_back(new branchEntryType("jetFwd4_phi", "F", "n_presel_jetFwd >= 4", 36, -TMath::Pi(), +TMath::Pi()));
  branchesToCompare.push_back(new branchEntryType("jetFwd4_E", "F", "n_presel_jetFwd >= 4", 100, 0., 600.));
  branchesToCompare.push_back(new branchEntryType("PFMET", "F", "", 100, 0., 250.));
  branchesToCompare.push_back(new branchEntryType("PFMETphi", "F", "", 36, -TMath::Pi(), +TMath::Pi()));
  branchesToCompare.push_back(new branchEntryType("MHT", "F", "", 100, 0., 600.));
  branchesToCompare.push_back(new branchEntryType("metLD", "F", "", 100, 0., 2.));
  branchesToCompare.push_back(new branchEntryType("lep1_conePt", "F", "", 100, 0., 1000.));
  branchesToCompare.push_back(new branchEntryType("lep2_conePt", "F", "", 100, 0., 500.));
  branchesToCompare.push_back(new branchEntryType("lep3_conePt", "F", "", 100, 0., 500.));
  branchesToCompare.push_back(new branchEntryType("mindr_lep1_jet", "F", "", 100, 0., 5.));
  branchesToCompare.push_back(new branchEntryType("mindr_lep2_jet", "F", "", 100, 0., 5.));
  branchesToCompare.push_back(new branchEntryType("mindr_lep3_jet", "F", "", 100, 0., 5.));
  branchesToCompare.push_back(new branchEntryType("mindr_lep4_jet", "F", "", 100, 0., 5.));
  branchesToCompare.push_back(new branchEntryType("mindr_tau1_jet", "F", "", 100, 0., 5.));
  branchesToCompare.push_back(new branchEntryType("mindr_tau2_jet", "F", "", 100, 0., 5.));
  branchesToCompare.push_back(new branchEntryType("avg_dr_jet", "F", "", 100, 0., 6.));
  branchesToCompare.push_back(new branchEntryType("avr_dr_lep_tau", "F", "", 100, 0., 6.));
  branchesToCompare.push_back(new branchEntryType("max_dr_jet", "F", "", 100, 0., 6.));
  branchesToCompare.push_back(new branchEntryType("max_dr_lep_tau", "F", "", 100, 0., 6.));
  branchesToCompare.push_back(new branchEntryType("mindr_tau_jet", "F", "", 100, 0., 6.));
  branchesToCompare.push_back(new branchEntryType("min_dr_lep_tau", "F", "", 100, 0., 6.));
  branchesToCompare.push_back(new branchEntryType("min_dr_lep_jet", "F", "", 100, 0., 6.));
  branchesToCompare.push_back(new branchEntryType("dr_leps", "F", "", 100, 0., 6.));
  branchesToCompare.push_back(new branchEntryType("dr_taus", "F", "", 100, 0., 6.));
  branchesToCompare.push_back(new branchEntryType("dr_lep_tau_ss", "F", "", 100, 0., 6.));
  branchesToCompare.push_back(new branchEntryType("dr_lep1_tau", "F", "", 100, 0., 6.));
  branchesToCompare.push_back(new branchEntryType("dr_lep2_tau", "F", "", 100, 0., 6.));
  branchesToCompare.push_back(new branchEntryType("dr_lep3_tau", "F", "", 100, 0., 6.));
  branchesToCompare.push_back(new branchEntryType("dr_lep1_tau2", "F", "", 100, 0., 6.));
  branchesToCompare.push_back(new branchEntryType("dr_lep2_tau2", "F", "", 100, 0., 6.));
  branchesToCompare.push_back(new branchEntryType("max_lep_eta", "F", "", 100, -3., 3.));
  branchesToCompare.push_back(new branchEntryType("mT_lep1", "F", "", 100, 0., 500.));
  branchesToCompare.push_back(new branchEntryType("mT_lep2", "F", "", 100, 0., 500.));
  branchesToCompare.push_back(new branchEntryType("mT_lep3", "F", "", 100, 0., 500.));
  branchesToCompare.push_back(new branchEntryType("mT_lep4", "F", "", 100, 0., 500.));
  branchesToCompare.push_back(new branchEntryType("mTauTauVis", "F", "", 100, 0., 500.));
  branchesToCompare.push_back(new branchEntryType("mTauTauVis1", "F", "", 100, 0., 500.));
  branchesToCompare.push_back(new branchEntryType("mTauTauVis2", "F", "", 100, 0., 500.));
  branchesToCompare.push_back(new branchEntryType("mbb", "F", "", 100, 0., 500.));
  branchesToCompare.push_back(new branchEntryType("mbb_loose", "F", "", 100, 0., 500.));
  branchesToCompare.push_back(new branchEntryType("cosThetaS_hadTau", "F", "", 100, -1., 1.));
  branchesToCompare.push_back(new branchEntryType("HTT", "F", "", 100, -1., 1.));
  branchesToCompare.push_back(new branchEntryType("HadTop_pt", "F", "", 100, 0., 500.));
  branchesToCompare.push_back(new branchEntryType("Hj_tagger", "F", "", 100, -1., 1.));
  branchesToCompare.push_back(new branchEntryType("mvaOutput_plainKin_ttV", "F", "", 100, 0., 1.));
  branchesToCompare.push_back(new branchEntryType("mvaOutput_plainKin_ttbar", "F", "", 100, 0., 1.));
  branchesToCompare.push_back(new branchEntryType("mvaOutput_1l_2tau_HTT_SUM_VT", "F", "", 100, 0., 1.));
  branchesToCompare.push_back(new branchEntryType("mvaOutput_2l_2tau_plainKin_1B_VT", "F", "", 100, 0., 1.));
  branchesToCompare.push_back(new branchEntryType("mvaOutput_2l_2tau_plainKin_SUM_VT", "F", "", 100, 0., 1.));
  branchesToCompare.push_back(new branchEntryType("mvaOutput_2lss_ttV", "F", "", 100, 0., 1.));
  branchesToCompare.push_back(new branchEntryType("mvaOutput_2lss_ttbar", "F", "", 100, 0., 1.));
  branchesToCompare.push_back(new branchEntryType("mvaOutput_2lss_1tau_plainKin_ttbar", "F", "", 100, 0., 1.));
  branchesToCompare.push_back(new branchEntryType("mvaOutput_2lss_1tau_plainKin_ttV", "F", "", 100, 0., 1.));
  branchesToCompare.push_back(new branchEntryType("mvaOutput_2lss_1tau_plainKin_1B_M", "F", "", 100, 0., 1.));
  branchesToCompare.push_back(new branchEntryType("mvaOutput_2lss_1tau_plainKin_SUM_M", "F", "", 100, 0., 1.));
  branchesToCompare.push_back(new branchEntryType("mvaOutput_2lss_1tau_HTT_SUM_M", "F", "", 100, 0., 1.));
  branchesToCompare.push_back(new branchEntryType("mvaOutput_2lss_1tau_HTTMEM_SUM_M", "F", "", 100, 0., 1.));
  branchesToCompare.push_back(new branchEntryType("mvaOutput_3l_ttV", "F", "", 100, 0., 1.));
  branchesToCompare.push_back(new branchEntryType("mvaOutput_3l_ttbar", "F", "", 100, 0., 1.));
  branchesToCompare.push_back(new branchEntryType("mvaOutput_3l_1tau_plainKin_SUM_M", "F", "", 100, 0., 1.));
  branchesToCompare.push_back(new branchEntryType("mvaOutput_3l_1tau_plainKin_1B_M", "F", "", 100, 0., 1.));
  branchesToCompare.push_back(new branchEntryType("FR_weight", "F", "", 100, 0., 1.));
  branchesToCompare.push_back(new branchEntryType("triggerSF_weight", "F", "", 100, 0., 2.));
  branchesToCompare.push_back(new branchEntryType("leptonSF_weight", "F", "", 100, 0., 2.));
  branchesToCompare.push_back(new branchEntryType("tauSF_weight", "F", "", 100, 0., 2.));
  branchesToCompare.push_back(new branchEntryType("bTagSF_weight", "F", "", 100, 0., 2.));
  branchesToCompare.push_back(new branchEntryType("PU_weight", "F", "", 100, 0., 2.));
  branchesToCompare.push_back(new branchEntryType("MC_weight", "F", "", 3, -1.5, 1.5));
  branchesToCompare.push_back(new branchEntryType("memOutput_LR", "F", "", 100, 0., 1.));
  branchesToCompare.push_back(new branchEntryType("nBJetMedium", "I", "", 12, 0, 12));
  branchesToCompare.push_back(new branchEntryType("nBJetLoose", "I", "", 12, 0, 12));
  branchesToCompare.push_back(new branchEntryType("nLightJet", "I", "", 12, 0, 12));

  for ( std::vector<branchEntryType*>::const_iterator branch = branchesToCompare.begin();
        branch != branchesToCompare.end(); ++branch ) {
    std::cout << "plotting " << (*branch)->branchName_ << "..." << std::endl;

    branchEntryType* branch_ref = (*branch)->Clone("ref");
    if(branch_ref->fillHistogram(tree_ref, ref_selection) < 0)
      branch_ref->histogram_ = nullptr;
    else
      normalizeHistogram(branch_ref->histogram_);

    branchEntryType* branch_test = (*branch)->Clone("test");
    if(branch_test->fillHistogram(tree_test, test_selection) < 0)
      branch_test->histogram_ = nullptr;
    else
      normalizeHistogram(branch_test->histogram_);

    std::string outputFileName = Form("compareSyncNtuples_%s.png", (*branch)->branchName_.data());
    showHistograms(800, 900,
                   branch_ref->histogram_, ref_name,
                   branch_test->histogram_, test_name,
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

void compareSyncNtuples()
{
  for(std::size_t i = 0; i < ntupleMetadataMap.size(); ++i)
  {
    for(std::size_t j = i + 1; j < ntupleMetadataMap.size(); ++j)
    {
      const NtupleMetaData & ref = ntupleMetadataMap[i];
      const NtupleMetaData & test = ntupleMetadataMap[j];
      assert(ref.inputFileNames.size() == test.inputFileNames.size());

      for(std::size_t k = 0; k < ref.inputFileNames.size(); ++k)
      {
        const std::string ref_inputFileName = ref.inputFileNames[k];
        const std::string test_inputFileName = test.inputFileNames[k];

        for(const std::string & treeName: ref.treeNames.at(ref_inputFileName))
        {
          const std::vector<std::string> & test_treeNames = test.treeNames.at(test_inputFileName);
          if(std::find(test_treeNames.cbegin(), test_treeNames.cend(), treeName) == test_treeNames.cend())
          {
            continue;
          }
          compareSyncNtuples(
            ref.legendEntry, test.legendEntry,
            ref_inputFileName, test_inputFileName,
            ref.selection, test.selection,
            treeName
          );
        }
      }
    }
  }
}
