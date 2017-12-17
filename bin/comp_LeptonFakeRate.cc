/** \executable comp_LeptonFakeRate
 *
 * Determine probability for jets to get misidentified as hadronic tau candidates,
 * measured in tt+jets events selected by requiring the presence of two b-jets, plus an electron and muon pair of opposite charge.
 *
 * \authors Ram Krishna Dewanjee, Christian Veelken; Tallinn
 *
 */

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/PythonParameterSet/interface/MakeParameterSets.h"

#include "FWCore/Utilities/interface/Exception.h"

#include "PhysicsTools/FWLite/interface/TFileService.h"
#include "DataFormats/FWLite/interface/InputSource.h"
#include "DataFormats/FWLite/interface/OutputFiles.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h"
#include "tthAnalysis/HiggsToTauTau/interface/jetToTauFakeRateAuxFunctions.h" // getEtaBin, getPtBin
#include "tthAnalysis/HiggsToTauTau/interface/compFakeRateAuxFunctions.h" // compFakeRate

#include <TArrayD.h>
#include <TAxis.h>
#include <TBenchmark.h>
#include <TCanvas.h>
#include <TError.h> // gErrorAbortLevel, kError
#include <TGraphAsymmErrors.h>
#include <TH1.h>
#include <TMath.h>
#include <TPaveText.h>
#include <TObjArray.h>
#include <TObjString.h>
#include <TRandom3.h>
#include <TString.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <assert.h>

typedef std::vector<double> vdouble;

namespace
{
  std::string readString(TObject* item_tobject, bool& parseError)
  {
    TObjString* item_tstring = dynamic_cast<TObjString*>(item_tobject);
    assert(item_tstring);
    return item_tstring->GetString().Data();
  }
  double readFloat(TObject* item_tobject, bool& parseError)
  {
    TObjString* item_tstring = dynamic_cast<TObjString*>(item_tobject);
    assert(item_tstring);
    if ( item_tstring->GetString().IsFloat() ) {
      return item_tstring->GetString().Atof();
    } else {
      parseError = true;
      return -1.;
    }
  }
}

struct fitResultType
{
  fitResultType(const std::string& line)
  {
    TString line_tstring(line.data());
    bool parseError = false;
    TObjArray* items = line_tstring.Tokenize(" ");
    if ( items->GetEntries() == 12 ) {
      std::string lepton_type_string = readString(items->At(0), parseError);
      if      ( lepton_type_string == "e"  ) lepton_type_ = kElectron;
      else if ( lepton_type_string == "mu" ) lepton_type_ = kMuon;
      else parseError = true;
      std::string pass_or_fail_string = readString(items->At(1), parseError);
      if      ( pass_or_fail_string == "num" ) pass_or_fail_ = kPass;
      else if ( pass_or_fail_string == "den" ) pass_or_fail_ = kFail;
      else parseError = true;
      minAbsEta_ = readFloat(items->At(4), parseError);
      maxAbsEta_ = readFloat(items->At(5), parseError);
      minPt_ = readFloat(items->At(6), parseError);
      maxPt_ = readFloat(items->At(7), parseError);
      key_ = Form("%s_%s", getPtBin(minPt_, maxPt_).data(), getEtaBin(minAbsEta_, maxAbsEta_).data());
      norm_ = readFloat(items->At(10), parseError);
      normErr_ = readFloat(items->At(11), parseError);
    } else parseError = true;
    if ( parseError ) {
      throw cms::Exception("fitResultType") 
	<< "Failed to parse line = '" << line << "' !!\n";
    }
  }
  ~fitResultType() {}
  enum { kElectron, kMuon };
  int lepton_type_;
  enum { kPass, kFail };
  int pass_or_fail_;
  double minAbsEta_;
  double maxAbsEta_;
  double minPt_;
  double maxPt_;
  std::string key_;
  double norm_;
  double normErr_;

};

namespace
{
  TH2* bookHistogram(fwlite::TFileService& fs, const std::string& histogramName, const TArrayD& ptBins, const TArrayD& absEtaBins)
  {
    int numBinsX = ptBins.GetSize() - 1;
    int numBinsY = absEtaBins.GetSize() - 1;
    TH2* histogram = fs.make<TH2D>(histogramName.data(), histogramName.data(), numBinsX, ptBins.GetArray(), numBinsY, absEtaBins.GetArray());
    return histogram;
  }
   
  void fillHistogram(TH2* histogram, const std::map<std::string, fitResultType*>& fitResults_pass, const std::map<std::string, fitResultType*>& fitResults_fail)
  {
    const TAxis* xAxis = histogram->GetXaxis();
    const TAxis* yAxis = histogram->GetYaxis();
    for ( int idxBinX = 1; idxBinX <= xAxis->GetNbins(); ++idxBinX ) {
      double minPt = xAxis->GetBinLowEdge(idxBinX);
      double maxPt = xAxis->GetBinUpEdge(idxBinX);
      for ( int idxBinY = 1; idxBinY <= yAxis->GetNbins(); ++idxBinY ) {
	double minAbsEta = yAxis->GetBinLowEdge(idxBinY);
	double maxAbsEta = yAxis->GetBinUpEdge(idxBinY);
	
	std::string key = Form("%s_%s", getPtBin(minPt, maxPt).data(), getEtaBin(minAbsEta, maxAbsEta).data());
	std::map<std::string, fitResultType*>::const_iterator fitResult_pass = fitResults_pass.find(key);
	std::map<std::string, fitResultType*>::const_iterator fitResult_fail = fitResults_fail.find(key);
	if ( fitResult_pass != fitResults_pass.end() && fitResult_fail != fitResults_fail.end() ) {
	  double nPass = fitResult_pass->second->norm_;
	  double nPassErr = fitResult_pass->second->normErr_;
	  double nFail = fitResult_fail->second->norm_;
	  double nFailErr = fitResult_fail->second->normErr_;
	  double avFakeRate, avFakeRateErrUp, avFakeRateErrDown;
	  bool errorFlag;
	  compFakeRate(nPass, nPassErr, nFail, nFailErr, avFakeRate, avFakeRateErrUp, avFakeRateErrDown, errorFlag);
	  if ( !errorFlag ) {
	    double avFakeRateErr = TMath::Sqrt(0.5*(avFakeRateErrUp*avFakeRateErrUp + avFakeRateErrDown*avFakeRateErrDown));
	    histogram->SetBinContent(idxBinX, idxBinY, avFakeRate);
	    histogram->SetBinError(idxBinX, idxBinY, avFakeRateErr);
	  } else {
	    throw cms::Exception("fillHistogram") 
	      << "Failed to compute fake rate for " << minPt << " < pT < " << maxPt << " && " << minAbsEta << "abs(eta)" << maxAbsEta 
	    << " (nPass = " << nPass << " +/- " << nPassErr << ", nFail = " << nFail << " +/- " << nFailErr << ") !!\n";
	  }
	} else {
	  throw cms::Exception("fillHistogram") 
	    << "Failed to find fitResult for " << minPt << " < pT < " << maxPt << " && " << minAbsEta << "abs(eta)" << maxAbsEta << " !!\n";
	}
      }
    }
  }
  
  TGraphAsymmErrors* bookGraph(fwlite::TFileService& fs, const std::string& graphName, const TArrayD& ptBins)
  {
    int numPoints = ptBins.GetSize() - 1;
    assert(numPoints >= 1);
    TGraphAsymmErrors* graph = new TGraphAsymmErrors(numPoints);
    return graph;
  }

  void fillGraph(TGraphAsymmErrors* graph, TH2* histogram, double absEta)
  {
    const TAxis* xAxis = histogram->GetXaxis();
    int numPoints = xAxis->GetNbins();
    const TAxis* yAxis = histogram->GetYaxis();
    int idxBinY = yAxis->FindBin(absEta);
    if ( !(idxBinY >= 1 && idxBinY <= yAxis->GetNbins()) ) {
      throw cms::Exception("fillGraph") 
	<< "Failed to find fitResult for abs(eta) = " << absEta << " !!\n";
    }
    for ( int idxBinX = 1; idxBinX <= xAxis->GetNbins(); ++idxBinX ) {
      double minPt = xAxis->GetBinLowEdge(idxBinX);
      double maxPt = xAxis->GetBinUpEdge(idxBinX);
      double pt = xAxis->GetBinCenter(idxBinX); 
      
      double binContent = histogram->GetBinContent(idxBinX, idxBinY);
      double binError = histogram->GetBinError(idxBinX, idxBinY);
      
      int idxPoint = idxBinX - 1;
      assert(idxPoint >= 0 && idxPoint < numPoints);
      graph->SetPoint(idxPoint, pt, binContent);
      graph->SetPointError(idxPoint, pt - minPt, maxPt - pt, binError, binError);
    }
  }

  void makeControlPlot(TGraphAsymmErrors* graph, const TArrayD& ptBins, double minAbsEta, double maxAbsEta, const std::string& outputFileName)
  {
    TCanvas* canvas = new TCanvas("canvas", "canvas", 1200, 1050);
    canvas->SetFillColor(10);
    canvas->SetBorderSize(2);
    canvas->SetTopMargin(0.04);
    canvas->SetLeftMargin(0.15);
    canvas->SetBottomMargin(0.17);
    canvas->SetRightMargin(0.04);
    canvas->SetGridx();
    canvas->SetGridy();

    TH1* dummyHistogram = new TH1D("dummyHistogram", "dummyHistogram", ptBins.GetSize() - 1, ptBins.GetArray());
    dummyHistogram->SetTitle("");
    dummyHistogram->SetStats(false);
    dummyHistogram->SetMaximum(0.20);
    dummyHistogram->SetMinimum(0.00);
  
    TAxis* xAxis = dummyHistogram->GetXaxis();
    xAxis->SetTitle("p_{T} [GeV]");
    xAxis->SetTitleOffset(1.2);
    xAxis->SetTitleSize(0.06);
    xAxis->SetLabelOffset(0.02);
    xAxis->SetLabelSize(0.06);
    xAxis->SetTickLength(0.04);
    xAxis->SetNdivisions(505);

    TAxis* yAxis = dummyHistogram->GetYaxis();
    yAxis->SetTitle("Fake rate");
    yAxis->SetTitleOffset(1.2);
    yAxis->SetTitleSize(0.06);
    yAxis->SetLabelOffset(0.02);
    yAxis->SetLabelSize(0.06);
    yAxis->SetTickLength(0.04);
    yAxis->SetNdivisions(505);

    dummyHistogram->Draw("axis");

    graph->SetMarkerStyle(24);
    graph->SetMarkerSize(2);
    graph->SetMarkerColor(1);
    graph->SetLineStyle(1);
    graph->SetLineWidth(1);
    graph->SetLineColor(1);

    graph->Draw("p");
  
    TPaveText* label = 0;
    std::string label_text;
    if      ( minAbsEta > 0. && maxAbsEta < 5. ) label_text = Form("%1.1f < |#eta| < %1.1f", minAbsEta, maxAbsEta);
    else if ( minAbsEta > 0.                   ) label_text = Form("|#eta| > %1.1f", minAbsEta);
    else if (                   maxAbsEta < 5. ) label_text = Form("|#eta| < %1.1f", maxAbsEta);
    if ( label_text != "" ) {
      label = new TPaveText(0.71, 0.83, 0.88, 0.88, "brNDC");
      label->AddText(label_text.data());
      label->SetFillColor(10);
      label->SetBorderSize(0);
      label->SetTextColor(1);
      label->SetTextAlign(22);
      label->SetTextSize(0.050);
      label->Draw();
    }

    canvas->Update();
    size_t idx = outputFileName.find_last_of('.');
    std::string outputFileName_plot = std::string(outputFileName, 0, idx);
    if ( idx != std::string::npos ) canvas->Print(std::string(outputFileName_plot).append(std::string(outputFileName, idx)).data());
    canvas->Print(std::string(outputFileName_plot).append(".png").data());
    canvas->Print(std::string(outputFileName_plot).append(".pdf").data());
    canvas->Print(std::string(outputFileName_plot).append(".root").data());
  
    delete dummyHistogram;
    delete label;
    delete canvas;
  }
}

int main(int argc, char* argv[]) 
{
//--- throw an exception in case ROOT encounters an error
  gErrorAbortLevel = kError;

//--- parse command-line arguments
  if ( argc < 2 ) {
    std::cout << "Usage: " << argv[0] << " [parameters.py]" << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << "<comp_LeptonFakeRate>:" << std::endl;

//--- keep track of time it takes the macro to execute
  TBenchmark clock;
  clock.Start("comp_LeptonFakeRate");

//--- read python configuration parameters
  if ( !edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process") ) 
    throw cms::Exception("comp_LeptonFakeRate") 
      << "No ParameterSet 'process' found in configuration file = " << argv[1] << " !!\n";

  edm::ParameterSet cfg = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");

  edm::ParameterSet cfg_comp = cfg.getParameter<edm::ParameterSet>("comp_LeptonFakeRate");

  std::string histogramName_e = cfg_comp.getParameter<std::string>("histogramName_e");
  vdouble absEtaBins_e = cfg_comp.getParameter<vdouble>("absEtaBins_e");
  if ( absEtaBins_e.size() < 2 ) throw cms::Exception("comp_LeptonFakeRate") 
    << "Invalid Configuration parameter 'absEtaBins_e' !!\n";
  TArrayD absEtaBins_e_array = convertToTArrayD(absEtaBins_e);
  vdouble ptBins_e = cfg_comp.getParameter<vdouble>("ptBins_e");
  if ( ptBins_e.size() < 2 ) throw cms::Exception("comp_LeptonFakeRate") 
    << "Invalid Configuration parameter 'ptBins_e' !!\n";
  TArrayD ptBins_e_array = convertToTArrayD(ptBins_e);
  
  std::string histogramName_mu = cfg_comp.getParameter<std::string>("histogramName_mu");
  vdouble absEtaBins_mu = cfg_comp.getParameter<vdouble>("absEtaBins_mu");
  if ( absEtaBins_mu.size() < 2 ) throw cms::Exception("comp_LeptonFakeRate") 
    << "Invalid Configuration parameter 'absEtaBins_mu' !!\n";
  TArrayD absEtaBins_mu_array = convertToTArrayD(absEtaBins_mu);
  vdouble ptBins_mu = cfg_comp.getParameter<vdouble>("ptBins_mu");
  if ( ptBins_mu.size() < 2 ) throw cms::Exception("comp_LeptonFakeRate") 
    << "Invalid Configuration parameter 'ptBins_mu' !!\n";
  TArrayD ptBins_mu_array = convertToTArrayD(ptBins_mu);
    
  std::map<std::string, fitResultType*> fitResults_e_pass;    // key = pT and eta bin
  std::map<std::string, fitResultType*> fitResults_e_fail;  // key = pT and eta bin
  std::map<std::string, fitResultType*> fitResults_mu_pass;   // key = pT and eta bin
  std::map<std::string, fitResultType*> fitResults_mu_fail; // key = pT and eta bin

  std::string outputFileName = cfg_comp.getParameter<std::string>("outputFileName"); // for control plots

  fwlite::InputSource inputFiles(cfg); 
  if ( !(inputFiles.files().size() == 1) )
    throw cms::Exception("comp_LeptonFakeRate") 
      << "Exactly one input file expected !!\n";
  std::ifstream* inputFile = new std::ifstream(inputFiles.files().front());
  if ( inputFile->is_open() ) {
    std::string line;
    while ( getline(*inputFile, line) ) {
      std::cout << "reading line = '" << line << "'" << std::endl;
      fitResultType* fitResult = new fitResultType(line);
      if        ( fitResult->lepton_type_ == fitResultType::kElectron && fitResult->pass_or_fail_ == fitResultType::kPass ) {
	fitResults_e_pass[fitResult->key_]  = fitResult;
      } else if ( fitResult->lepton_type_ == fitResultType::kElectron && fitResult->pass_or_fail_ == fitResultType::kFail ) {
	fitResults_e_fail[fitResult->key_]  = fitResult;
      } else if ( fitResult->lepton_type_ == fitResultType::kMuon     && fitResult->pass_or_fail_ == fitResultType::kPass ) {
	fitResults_mu_pass[fitResult->key_] = fitResult;
      } else if ( fitResult->lepton_type_ == fitResultType::kElectron && fitResult->pass_or_fail_ == fitResultType::kFail ) {
	fitResults_mu_fail[fitResult->key_] = fitResult;
      } else assert(0);
    }
    inputFile->close();
  } else {
    throw cms::Exception("comp_LeptonFakeRate") 
      << "Failed to open input file !!\n";
  }
  delete inputFile;

  fwlite::OutputFiles outputFile(cfg);
  fwlite::TFileService fs = fwlite::TFileService(outputFile.file().data());

  TH2* histogram_e = bookHistogram(fs, histogramName_e, ptBins_e_array, absEtaBins_e_array);
  fillHistogram(histogram_e, fitResults_e_pass, fitResults_e_fail);
  TAxis* yAxis_e = histogram_e->GetYaxis();
  for ( int idxBinY = 1; idxBinY < yAxis_e->GetNbins(); ++idxBinY ) {
    double minAbsEta = yAxis_e->GetBinLowEdge(idxBinY);
    double maxAbsEta = yAxis_e->GetBinUpEdge(idxBinY);
    double absEta = 0.5*(minAbsEta + maxAbsEta);
    std::string graphName = TString(Form("graph_e_absEta%1.2fto%1.2f", minAbsEta, maxAbsEta)).ReplaceAll(".", "_").Data();
    TGraphAsymmErrors* graph = bookGraph(fs, graphName, ptBins_e_array);
    fillGraph(graph, histogram_e, absEta);
    std::string outputFileName_plot = std::string(outputFileName, 0, outputFileName.find_last_of('.'));
    outputFileName_plot.append(Form("_e_%s.png", getEtaBin(minAbsEta, maxAbsEta).data()));
    makeControlPlot(graph, ptBins_e_array, minAbsEta, maxAbsEta, outputFileName_plot);
  }

  TH2* histogram_mu = bookHistogram(fs, histogramName_mu, ptBins_mu_array, absEtaBins_mu_array);
  fillHistogram(histogram_mu, fitResults_mu_pass, fitResults_mu_fail);
  TAxis* yAxis_mu = histogram_mu->GetYaxis();
  for ( int idxBinY = 1; idxBinY < yAxis_mu->GetNbins(); ++idxBinY ) {
    double minAbsEta = yAxis_mu->GetBinLowEdge(idxBinY);
    double maxAbsEta = yAxis_mu->GetBinUpEdge(idxBinY);
    double absEta = 0.5*(minAbsEta + maxAbsEta);
    std::string graphName = TString(Form("graph_mu_absEta%1.2fto%1.2f", minAbsEta, maxAbsEta)).ReplaceAll(".", "_").Data();
    TGraphAsymmErrors* graph = bookGraph(fs, graphName, ptBins_mu_array);
    fillGraph(graph, histogram_mu, absEta);
    std::string outputFileName_plot = std::string(outputFileName, 0, outputFileName.find_last_of('.'));
    outputFileName_plot.append(Form("_mu_%s.png", getEtaBin(minAbsEta, maxAbsEta).data()));
    makeControlPlot(graph, ptBins_mu_array, minAbsEta, maxAbsEta, outputFileName_plot);
  }

  clock.Show("comp_LeptonFakeRate");

  return 0;
}
