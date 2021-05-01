
/** \executable compShapeSyst
 *
 * Compute a few "special" shape systematics for ttH, H->tautau analysis,
 * e.g. CMS_ttHl_FRe_2lss_corr1Up/Down, CMS_ttHl_FRe_2lss_anticorr1Up/Down, 
 *      CMS_ttHl_FRm_2lss_corr1Up/Down, CMS_ttHl_FRm_2lss_anticorr1Up/Down
 *
 * \author Christian Veelken, Tallinn
 *
 */

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#if __has_include (<FWCore/ParameterSetReader/interface/ParameterSetReader.h>)
#  include <FWCore/ParameterSetReader/interface/ParameterSetReader.h> // edm::readPSetsFrom()
#else
#  include <FWCore/PythonParameterSet/interface/MakeParameterSets.h> // edm::readPSetsFrom()
#endif

#include "FWCore/Utilities/interface/Exception.h"

#include "PhysicsTools/FWLite/interface/TFileService.h"
#include "DataFormats/FWLite/interface/InputSource.h"
#include "DataFormats/FWLite/interface/OutputFiles.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h"
#include "tthAnalysis/HiggsToTauTau/interface/generalAuxFunctions.h"

#include <TFile.h>
#include <TH1.h>
#include <TF1.h>
#include <TBenchmark.h>
#include <TMath.h>
#include <TError.h> // gErrorAbortLevel, kError
#include "TDirectory.h"
#include "TList.h"
#include "TKey.h"
#include "TObject.h"
#include "TString.h"

#include <iostream>
#include <string>
#include <vector>
#include <assert.h>

typedef std::vector<std::string> vstring;

namespace
{
  struct compShapeSystType
  {
    compShapeSystType(const edm::ParameterSet& cfg)
    {
      categories_ = cfg.getParameter<vstring>("categories");
      processes_ = cfg.getParameter<vstring>("processes");
      shifts_ = cfg.getParameter<vstring>("shifts");
      histogramDir_ = cfg.getParameter<std::string>("histogramDir");
      histogramsToFit_ = cfg.getParameter<vstring>("histogramsToFit");
      outputHistogramName1_ = cfg.getParameter<std::string>("outputHistogramName1");
      outputHistogramName2_ = cfg.getParameter<std::string>("outputHistogramName2");
    }
    ~compShapeSystType() {}
    void print(std::ostream& stream) const
    {
      stream << "<compShapeSystType>:" << std::endl;
      stream << " categories = " << format_vstring(categories_) << std::endl;
      stream << " processes = " << format_vstring(processes_) << std::endl;
      stream << " shifts = " << format_vstring(shifts_) << std::endl;
      stream << " histogramDir = " << histogramDir_ << std::endl;
      stream << " histogramsToFit = " << format_vstring(histogramsToFit_) << std::endl;
      stream << " outputHistogramName1 = " << outputHistogramName1_ << std::endl;
      stream << " outputHistogramName2 = " << outputHistogramName2_ << std::endl;
    }
    vstring categories_;
    vstring processes_;
    vstring shifts_;
    std::string histogramDir_;
    vstring histogramsToFit_;
    std::string outputFileName_;
    std::string outputHistogramName1_;
    std::string outputHistogramName2_;
  };

  bool isMatched(const vstring& names, const std::string& name_ref)
  {
    for ( vstring::const_iterator name = names.begin();
	  name != names.end(); ++name ) {
      if ( (*name) == name_ref ) return true;
    }
    return false;
  }

  TH1* cloneHistogram(const TH1* histogram, const std::string& histogramName_clone)
  {
    TH1* histogram_cloned = (TH1*)histogram->Clone(histogramName_clone.data());
    histogram_cloned->Reset();
    if ( !histogram_cloned->GetSumw2N() ) histogram_cloned->Sumw2();
    return histogram_cloned;
  }

  double square(double x)
  {
    return x*x;
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

  std::cout << "<compShapeSyst>:" << std::endl;

//--- keep track of time it takes the macro to execute
  TBenchmark clock;
  clock.Start("compShapeSyst");

//--- read python configuration parameters
  if ( !edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process") ) 
    throw cms::Exception("compShapeSyst") 
      << "No ParameterSet 'process' found in configuration file = " << argv[1] << " !!\n";
  
  edm::ParameterSet cfg = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");

  edm::ParameterSet cfg_compShapeSyst = cfg.getParameter<edm::ParameterSet>("compShapeSyst");
  
  std::string category = cfg_compShapeSyst.getParameter<std::string>("category");

  vstring histogramsToFit = cfg_compShapeSyst.getParameter<vstring>("histogramsToFit");

  std::vector<compShapeSystType> compSystConfigs;
  edm::VParameterSet cfg_compSystConfigs = cfg_compShapeSyst.getParameter<edm::VParameterSet>("compSyst");
  for ( edm::VParameterSet::const_iterator cfgCompSystConfig = cfg_compSystConfigs.begin();
	cfgCompSystConfig != cfg_compSystConfigs.end(); ++cfgCompSystConfig ) {
    compSystConfigs.push_back(compShapeSystType(*cfgCompSystConfig));
  }

  fwlite::InputSource inputFiles(cfg); 
  if ( !(inputFiles.files().size() == 1) )
    throw cms::Exception("addSystDatacards") 
      << "Exactly one input file expected !!\n";
  TFile* inputFile = new TFile(inputFiles.files().front().data());

  fwlite::OutputFiles outputFile(cfg);
  fwlite::TFileService fs = fwlite::TFileService(outputFile.file().data());

//--- start computing shape systematics
  for ( std::vector<compShapeSystType>::const_iterator compSystConfig = compSystConfigs.begin();
	compSystConfig != compSystConfigs.end(); ++compSystConfig ) {
    for ( vstring::const_iterator histogramToFit = compSystConfig->histogramsToFit_.begin();
	  histogramToFit != compSystConfig->histogramsToFit_.end(); ++histogramToFit ) {

      bool matchesCategory = isMatched(compSystConfig->categories_, category);
      //std::cout << "matchesCategory = " << matchesCategory << std::endl;
      if ( !matchesCategory ) continue;

      bool matchesHistogramToFit = isMatched(histogramsToFit, *histogramToFit);
      //std::cout << "matchesHistogramToFit = " << matchesHistogramToFit << std::endl;
      if ( !matchesHistogramToFit ) continue;

      TDirectory* dir = getDirectory(inputFile, compSystConfig->histogramDir_, true);
      assert(dir);
      
      for ( vstring::const_iterator process = compSystConfig->processes_.begin();
	    process != compSystConfig->processes_.end(); ++process ) {
	TH1* histogram_central = getHistogram(dir, *process, *histogramToFit, "", true);
	//std::cout << "histogram_central (name = " << histogram_central->GetName() << ") = " << histogram_central << std::endl;

	int numBins = histogram_central->GetNbinsX();
	
	std::map<std::string, TH1*> histograms_shift; // key = systematic uncertainty ("shift")
	for ( vstring::const_iterator shift = compSystConfig->shifts_.begin();
	      shift != compSystConfig->shifts_.end(); ++shift ) {
	  TH1* histogram_shift = getHistogram(dir, *process, *histogramToFit, *shift, true);
	  //std::cout << "histogram_shift (name = " << histogram_shift->GetName() << ") = " << histogram_shift << std::endl;
	  assert(histogram_shift->GetNbinsX() == numBins);
	  histograms_shift[*shift] = histogram_shift;
	}
	
	std::vector<double> binErr2(numBins + 2);
	
	for ( int idxBin = 0; idxBin <= (numBins + 1); ++idxBin ) {
	  double binContent_central = histogram_central->GetBinContent(idxBin);
	  //std::cout << "bin #" << idxBin << ":" << std::endl;
	  for ( std::map<std::string, TH1*>::const_iterator histogram_shift = histograms_shift.begin();
		histogram_shift != histograms_shift.end(); ++histogram_shift ) {
	    double binContent_shift = histogram_shift->second->GetBinContent(idxBin);
	    double diff = binContent_central - binContent_shift;
	    //std::cout << " shift = " << histogram_shift->first << ": diff = " << diff << std::endl;
	    binErr2[idxBin] += square(diff);
	  }
	}

	TH1* histogram_diff = (TH1*)histogram_central->Clone("histogram_diff");
	for ( int idxBin = 0; idxBin <= (numBins + 1); ++idxBin ) {
	  double binContent = 0.;
	  histogram_diff->SetBinContent(idxBin, binContent);
	  double binError = TMath::Sqrt(binErr2[idxBin]);
	  if ( binError < 1.e-3 ) binError = 1.; // CV: avoid constraining fit with empty and low-statistics bins
	  histogram_diff->SetBinError(idxBin, binError);
	  std::cout << "bin #" << idxBin << ": diff = " << binContent << " +/- " << binError << std::endl;
	}

	TAxis* xAxis = histogram_central->GetXaxis();
	double xMin = xAxis->GetXmin();
	double xMax = xAxis->GetXmax();
	double x0 = 0.5*(xMin + xMax);

	std::string fitFunction_formula = Form("[0] + [1]*(x - %1.2f) + [2]*(x - %1.2f)*(x - %1.2f)", x0, x0, x0);
	TF1* fitFunction = new TF1("fitFunction", fitFunction_formula.data(), xMin, xMax);
	histogram_diff->Fit(fitFunction);

	double p1 = fitFunction->GetParameter(1);
	double p1Err = fitFunction->GetParError(1);
	std::cout << "p1 = " << p1 << " +/- " << p1Err << std::endl;
	double p2 = fitFunction->GetParameter(2);
	double p2Err = fitFunction->GetParError(2);
	std::cout << "p2 = " << p2 << " +/- " << p2Err << std::endl;

	TFileDirectory* dir_output = &fs;
	dir_output->cd();

	TH1* outputHistogram1Up   = cloneHistogram(histogram_central, compSystConfig->outputHistogramName1_ + "Up");
	TH1* outputHistogram1Down = cloneHistogram(histogram_central, compSystConfig->outputHistogramName1_ + "Down");
	TH1* outputHistogram2Up   = cloneHistogram(histogram_central, compSystConfig->outputHistogramName2_ + "Up");
	TH1* outputHistogram2Down = cloneHistogram(histogram_central, compSystConfig->outputHistogramName2_ + "Down");

	for ( int idxBin = 1; idxBin <= numBins; ++idxBin ) {
	  double binCenter = xAxis->GetBinCenter(idxBin);
	  
	  double binError = histogram_central->GetBinError(idxBin);

	  double binContent1Up = +p1Err*(binCenter - x0);
	  outputHistogram1Up->SetBinError(idxBin, binError);
	  outputHistogram1Up->SetBinContent(idxBin, binContent1Up);

	  double binContent1Down = -p1Err*(binCenter - x0);
	  outputHistogram1Down->SetBinError(idxBin, binError);
	  outputHistogram1Down->SetBinContent(idxBin, binContent1Down);

	  double binContent2Up = +p2Err*square(binCenter - x0);
	  outputHistogram2Up->SetBinError(idxBin, binError);
	  outputHistogram2Up->SetBinContent(idxBin, binContent2Up);

	  double binContent2Down = -p2Err*square(binCenter - x0);
	  outputHistogram2Down->SetBinError(idxBin, binError);
	  outputHistogram2Down->SetBinContent(idxBin, binContent2Down);
	}

	delete histogram_diff;
	delete fitFunction;
      }
    }
  }
  
  clock.Show("compShapeSyst");
  
  return 0;
}
