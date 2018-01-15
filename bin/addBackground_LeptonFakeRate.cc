/** \executable addBackground_LeptonFakeRate
 *
 * Compute shape templates and normalization for fake lepton background to be used for LeptonFakeRate computation.
 *
 * \author Ram Krishna Dewanjee, Tallinn
 *
 */

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/PythonParameterSet/interface/MakeParameterSets.h"

#include "FWCore/Utilities/interface/Exception.h"

#include "PhysicsTools/FWLite/interface/TFileService.h"
#include "DataFormats/FWLite/interface/InputSource.h"
#include "DataFormats/FWLite/interface/OutputFiles.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h"
#include "tthAnalysis/HiggsToTauTau/interface/addBackgroundsAuxFunctions.h" // getSubdirectories

#include <TFile.h>
#include <TH1.h>
#include <TBenchmark.h>
#include <TMath.h>
#include <TError.h> // gErrorAbortLevel, kError
#include "TDirectory.h"
#include "TList.h"
#include "TKey.h"
#include "TObject.h"

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <cstdlib> // EXIT_SUCCESS, EXIT_FAILURE
#include <assert.h>

typedef std::vector<std::string> vstring;

double square(double x)
{
  return x*x;
}

namespace
{
  struct categoryEntryType
  {
    categoryEntryType(const edm::ParameterSet& cfg)
    {	
      numerator_   = cfg.getParameter<std::string>("numerator");
      denominator_ = cfg.getParameter<std::string>("denominator");
      lepton_      = cfg.getParameter<std::string>("lepton");
    }
    ~categoryEntryType() {}
    std::string numerator_;
    std::string denominator_;
    std::string lepton_;
  };
}

TH1* copyHistogram(const TH1* histogram_input, const std::string& histogramName_output)
{
  TH1* histogram_output = 0;
  const TAxis* xAxis = histogram_input->GetXaxis();
  if ( xAxis->GetXbins() ) histogram_output = new TH1D(histogramName_output.data(), histogram_input->GetTitle(), xAxis->GetNbins(), xAxis->GetXbins()->GetArray());
  else histogram_output = new TH1D(histogramName_output.data(), histogram_input->GetTitle(), xAxis->GetNbins(), xAxis->GetXmin(), xAxis->GetXmax());
  int numBins = xAxis->GetNbins();
  for ( int idxBin = 0; idxBin <= (numBins + 1); ++idxBin ) {
    double binContent = histogram_input->GetBinContent(idxBin);
    histogram_output->SetBinContent(idxBin, binContent);
    double binError = histogram_input->GetBinError(idxBin);
    histogram_output->SetBinError(idxBin, binError);
  }
  return histogram_output;
}

void processHistogram(
       const TFile* inputFile, 
       const TDirectory* dir_den, const TDirectory* dir_num, 
       const std::string& processData, const std::string& processLeptonFakes, const vstring& processesToSubtract, 
       const vstring& central_or_shifts, fwlite::TFileService& fs, const std::string& cat_num) 
{
  const TDirectory* dirData_den = getSubdirectory(dir_den, processData, false);
  if ( !dirData_den ) { 
    std::cout << "Failed to find subdirectory = '" << processData << "' within directory = '" << dir_den->GetPath() << "' !!" << std::endl; 
    return;
  }

  std::set<std::string> histograms;      
  TList* list = dirData_den->GetListOfKeys();
  TIter next(list); 
  TKey* key = 0;                                                                                                                                                                        
  while ( (key = dynamic_cast<TKey*>(next())) ) {        
    TObject* object = key->ReadObj(); 
    TH1* histogram = dynamic_cast<TH1*>(object);  
    if ( !histogram ) continue;
    TString histogramName = TString(histogram->GetName()).ReplaceAll(Form("%s_", processData.data()), "");  
    for ( vstring::const_iterator central_or_shift = central_or_shifts.begin();  
	  central_or_shift != central_or_shifts.end(); ++central_or_shift ) {   
      if ( !((*central_or_shift) == "" || (*central_or_shift) == "central") ) {
	histogramName = histogramName.ReplaceAll(Form("%s_", central_or_shift->data()), "");  
      }
    }
    if ( histogramName.Contains("CMS_") ) continue; 
    if ( histogramName.Contains("cutFlow") ) continue;
    if ( histograms.find(histogramName.Data()) == histograms.end() ) {   
      //std::cout << "adding histogram = " << histogramName.Data() << std::endl; 
      histograms.insert(histogramName.Data());
    }
  }

  for ( std::set<std::string>::const_iterator histogram = histograms.begin();
	histogram != histograms.end(); ++histogram ) {                                                                      
    //std::cout << "processing histogram = " << (*histogram) << std::endl; 
    
    for ( vstring::const_iterator central_or_shift = central_or_shifts.begin();
	  central_or_shift != central_or_shifts.end(); ++central_or_shift ) {     
      
      int verbosity = ( histogram->find("EventCounter") != std::string::npos && ((*central_or_shift) == "" || (*central_or_shift) == "central") ) ? 1 : 0;
      
      TH1* histogramData_den = getHistogram(dir_den, processData, *histogram, *central_or_shift, false);                                                                             
      if ( !histogramData_den ) {
	histogramData_den = getHistogram(dir_den, processData, *histogram, "central", true);                                                                                         
      }                                                                                            
      if ( verbosity ) {
	std::cout << " Den. integral(data_obs) = " << histogramData_den->Integral() << std::endl;
      }                  

      TH1* histogramData_num = getHistogram(dir_num, processData, *histogram, *central_or_shift, false);                                                                             
      if ( !histogramData_num ) {                                                                                  
	histogramData_num = getHistogram(dir_num, processData, *histogram, "central", true);
      }
      if ( verbosity ) {   
	std::cout << " Num. integral(data_obs) = " << histogramData_num->Integral() << std::endl;  
      }

      std::vector<TH1*> histogramsToSubtract_den; 
      std::vector<TH1*> histogramsToSubtract_num;   
      for ( vstring::const_iterator processToSubtract = processesToSubtract.begin(); 
	    processToSubtract != processesToSubtract.end(); ++processToSubtract ) {
	TH1* histogramToSubtract_den = getHistogram(dir_den, *processToSubtract, *histogram, *central_or_shift, false);                                                        
	if ( !histogramToSubtract_den ) {
	  histogramToSubtract_den = getHistogram(dir_den, *processToSubtract, *histogram, "central", true);                                                
	}
	if ( verbosity ) {
	  std::cout << " Den. integral(" << (*processToSubtract) << ") = " << histogramToSubtract_den->Integral() << std::endl;                                                           
	} 
	histogramsToSubtract_den.push_back(histogramToSubtract_den);   

	TH1* histogramToSubtract_num = getHistogram(dir_num, *processToSubtract, *histogram, *central_or_shift, false);                                                        
	if ( !histogramToSubtract_num ) {
	  histogramToSubtract_num = getHistogram(dir_num, *processToSubtract, *histogram, "central", true);                                                
	}
	if ( verbosity ) {
	  std::cout << " Num. integral(" << (*processToSubtract) << ") = " << histogramToSubtract_num->Integral() << std::endl;                                                        
	}
	histogramsToSubtract_num.push_back(histogramToSubtract_num);  
      }                        

      TString subdirName_den_tstring = TString(dir_num->GetPath()).ReplaceAll("numerator", "denominator");
      subdirName_den_tstring = subdirName_den_tstring.ReplaceAll("tight", "fakeable");         
      std::string subdirName_den = subdirName_den_tstring.Data();
      size_t pos_den = subdirName_den.find(":/");
      assert(pos_den < (subdirName_den.length() - 2));
      subdirName_den = std::string(subdirName_den, pos_den + 2);

      TString subdirName_num_tstring = TString(dir_num->GetPath());
      std::string subdirName_num = subdirName_num_tstring.Data();
      size_t pos_num = subdirName_num.find(":/");
      assert(pos_num < (subdirName_num.length() - 2));
      subdirName_num = std::string(subdirName_num, pos_num + 2);

      //-------- compute fakes_data histogram for denominator 
      //        (= data_obs - sum(prompt MC) histograms for fakeable lepton selection)
      std::string subdirName_output_den = Form("%s/%s", subdirName_den.data(), processLeptonFakes.data());       
      std::cout << " subdirName_output_den = '" << subdirName_output_den << "'" << std::endl;
      TDirectory* subdir_output_den = createSubdirectory_recursively(fs, subdirName_output_den);
      subdir_output_den->cd();                                                                                                                                             
                 
      std::string histogramNameFakeBg_den;
      if ( !((*central_or_shift) == "" || (*central_or_shift) == "central") ) histogramNameFakeBg_den.append(*central_or_shift);
      if ( histogramNameFakeBg_den.length() > 0 ) histogramNameFakeBg_den.append("_");
      histogramNameFakeBg_den.append(*histogram);
      TH1* histogramFakeBg_den = subtractHistograms(histogramNameFakeBg_den, histogramData_den, histogramsToSubtract_den, verbosity);  
      if ( verbosity ) {
	std::cout << " Den. integral(" << processLeptonFakes << ") = " << histogramFakeBg_den->Integral() << std::endl;
      }
      makeBinContentsPositive(histogramFakeBg_den, verbosity);
      //histogramFakeBg_den->Write();      
      //--------

      //-------- compute fakes_data histogram for numerator 
      //        (take fakes_data shape from denominator and normalize the shape to data_obs - sum(prompt MC) for tight lepton selection;
      //         in case the difference data_obs - sum(prompt MC) is below 10% times data_obs, normalize the fakes_data histogram for the numerator to 10% times data_obs
      //         and rescale the histograms for the prompt MC "backgrounds" such that the sum(prompt MC) + fakes_data = data_obs)
      std::string subdirName_output_num = Form("%s/%s", subdirName_num.data(), processLeptonFakes.data());        
      std::cout<< " subdirName_output_num = '" << subdirName_output_num << "'" << std::endl;
      TDirectory* subdir_output_num = createSubdirectory_recursively(fs, subdirName_output_num);
      subdir_output_num->cd();   

      std::string histogramNameFakeBg_num;  
      if ( !((*central_or_shift) == "" || (*central_or_shift) == "central") ) histogramNameFakeBg_num.append(*central_or_shift);  
      if ( histogramNameFakeBg_num.length() > 0 ) histogramNameFakeBg_num.append("_");
      histogramNameFakeBg_num.append(*histogram);  
      TH1* histogramFakeBg_num = subtractHistograms(histogramNameFakeBg_num, histogramData_den, histogramsToSubtract_den, verbosity);  // Doing (Data - Sum Bg.)
      if ( verbosity ) { 
	std::cout << " Den. integral(" << processLeptonFakes << ") before scaling = " << histogramFakeBg_num->Integral() << std::endl;
      }
      makeBinContentsPositive(histogramFakeBg_den, verbosity);

      double integralData_num = compIntegral(histogramData_num, true, true);
      double integralPromptBg_num = 0.;
      for ( std::vector<TH1*>::const_iterator histogramToSubtract_num = histogramsToSubtract_num.begin();
	    histogramToSubtract_num != histogramsToSubtract_num.end(); ++histogramToSubtract_num ) {
	integralPromptBg_num += compIntegral(*histogramToSubtract_num, true, true);
      }
      double integralFakeBg_num = integralData_num - integralPromptBg_num;
      
      double sfPromptBg_num = 1.;
      if ( integralFakeBg_num < (0.10*integralData_num) ) {
	integralFakeBg_num = 0.10*integralData_num;
	sfPromptBg_num = (integralData_num - integralFakeBg_num)/integralPromptBg_num;
      }
      double integralFakeBg_den = compIntegral(histogramFakeBg_den, true, true);
      double sfFakeBg_num = integralFakeBg_num/integralFakeBg_den;
      histogramFakeBg_num->Scale(sfFakeBg_num);
      if ( verbosity ) { 
	std::cout << " Num. integral(" << processLeptonFakes << ") after scaling = " << histogramFakeBg_num->Integral() << std::endl;
      }
      makeBinContentsPositive(histogramFakeBg_num, verbosity);
      //histogramFakeBg_num->Write();
      //--------

      //-------- copy histograms for data_obs and prompt MC to output file
      subdir_output_den->cd(); 
      //TH1* histogramData_den_copied = copyHistogram(histogramData_den, histogramData_den->GetName());
      copyHistogram(histogramData_den, histogramData_den->GetName());
      //histogramData_den_copied->Write();
      for ( std::vector<TH1*>::const_iterator histogramToSubtract_den = histogramsToSubtract_den.begin();
	    histogramToSubtract_den != histogramsToSubtract_den.end(); ++histogramToSubtract_den ) {
	//TH1* histogramPromptBg_den_copied = copyHistogram(*histogramToSubtract_den, (*histogramToSubtract_den)->GetName());
	copyHistogram(*histogramToSubtract_den, (*histogramToSubtract_den)->GetName());
	//histogramPromptBg_den_copied->Write();
      }

      subdir_output_num->cd(); 
      //TH1* histogramData_num_copied = copyHistogram(histogramData_num, histogramData_num->GetName());
      copyHistogram(histogramData_num, histogramData_num->GetName());
      //histogramData_num_copied->Write();
      for ( std::vector<TH1*>::const_iterator histogramToSubtract_num = histogramsToSubtract_num.begin();
	    histogramToSubtract_num != histogramsToSubtract_num.end(); ++histogramToSubtract_num ) {
	TH1* histogramPromptBg_num_copied = copyHistogram(*histogramToSubtract_num, (*histogramToSubtract_num)->GetName());
	if ( sfPromptBg_num != 1. ) histogramPromptBg_num_copied->Scale(sfPromptBg_num);
	//histogramPromptBg_num_copied->Write();
      }
      //--------
    }
  }
}

void processDirectory(
       const TFile* inputFile, 
       const TDirectory* dir_den, const TDirectory* dir_num, 
       const std::string& processData, const std::string& processLeptonFakes, const vstring& processesToSubtract, 
       const vstring& central_or_shifts, fwlite::TFileService& fs, const std::string& cat_num, const std::string& cat_den) {

  processHistogram(inputFile, dir_den, dir_num, processData, processLeptonFakes, processesToSubtract, central_or_shifts, fs, cat_num);   

  std::vector<const TDirectory*> subdirs_den = getSubdirectories(dir_den);  
  for(std::vector<const TDirectory*>::iterator subdir_den = subdirs_den.begin();
      subdir_den != subdirs_den.end(); ++subdir_den){ 
    TString subdirName_num = TString((*subdir_den)->GetPath()).ReplaceAll("denominator", "numerator"); 
    subdirName_num = subdirName_num.ReplaceAll("fakeable", "tight"); 
    if ( subdirName_num.First(":/") < (subdirName_num.Length() - 2) ) {
      std::string subdirName_string = subdirName_num.Data();
      size_t pos = subdirName_string.find(":/");
      assert(pos < (subdirName_string.length() - 2));
      subdirName_string = std::string(subdirName_string, pos + 2); 
      subdirName_num = subdirName_string.data();
    }
        
    TDirectory* subdir_num = getDirectory(inputFile, subdirName_num.Data(), true);  
    if ( subdir_num && (*subdir_den) ) { 
      processDirectory(inputFile, *subdir_den, subdir_num, processData, processLeptonFakes, processesToSubtract, central_or_shifts, fs, cat_num, cat_den);
    }
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

  std::cout << "<addBackground_LeptonFakeRate>:" << std::endl;

//--- keep track of time it takes the macro to execute
  TBenchmark clock;
  clock.Start("addBackground_LeptonFakeRate");

//--- read python configuration parameters
  if ( !edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process") ) 
    throw cms::Exception("addBackground_LeptonFakeRate") 
      << "No ParameterSet 'process' found in configuration file = " << argv[1] << " !!\n";
  
  edm::ParameterSet cfg = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");

  edm::ParameterSet cfgAddBackground_LeptonFakeRate = cfg.getParameter<edm::ParameterSet>("addBackground_LeptonFakeRate");
  
  std::vector<categoryEntryType*> categories;
  edm::VParameterSet cfgCategories = cfgAddBackground_LeptonFakeRate.getParameter<edm::VParameterSet>("categories");
  for ( edm::VParameterSet::const_iterator cfgCategory = cfgCategories.begin();
	cfgCategory != cfgCategories.end(); ++cfgCategory ) {
    categoryEntryType* category = new categoryEntryType(*cfgCategory);
    categories.push_back(category);
  }

  std::string processData = cfgAddBackground_LeptonFakeRate.getParameter<std::string>("processData");
  std::string processLeptonFakes = cfgAddBackground_LeptonFakeRate.getParameter<std::string>("processLeptonFakes");
  vstring processesToSubtract = cfgAddBackground_LeptonFakeRate.getParameter<vstring>("processesToSubtract");

  vstring central_or_shifts = cfgAddBackground_LeptonFakeRate.getParameter<vstring>("sysShifts");
  bool contains_central_value = false;
  for ( vstring::const_iterator central_or_shift = central_or_shifts.begin();
	central_or_shift != central_or_shifts.end(); ++central_or_shift ) {
    if ( (*central_or_shift) == "" || (*central_or_shift) == "central" ) contains_central_value = true;
  }
  if ( !contains_central_value ) central_or_shifts.push_back(""); // CV: add central value

  fwlite::InputSource inputFiles(cfg); 
  if ( !(inputFiles.files().size() == 1) )
    throw cms::Exception("addBackground_LeptonFakeRate") 
      << "Exactly one input file expected !!\n";
  TFile* inputFile = new TFile(inputFiles.files().front().data());
  if ( !inputFile ) 
    throw cms::Exception("addBackground_LeptonFakeRate") 
      << "Failed to open input file = '" << inputFiles.files().front() << "' !!\n";
  
  fwlite::OutputFiles outputFile(cfg);
  fwlite::TFileService fs = fwlite::TFileService(outputFile.file().data());

  for ( std::vector<categoryEntryType*>::const_iterator category = categories.begin();
	category != categories.end(); ++category ) {                                                                  
    std::cout << "processing category: numerator = " << (*category)->numerator_ << ", denominator = " << (*category)->denominator_ << std::endl;

    TDirectory* dir_denominator = getDirectory(inputFile, (*category)->denominator_, true); 
    assert(dir_denominator);                                                                                                                                                                      
    TDirectory* dir_numerator = getDirectory(inputFile, (*category)->numerator_, true); 
    assert(dir_numerator);  

    processDirectory(
      inputFile, 
      dir_denominator, dir_numerator, 
      processData, processLeptonFakes, processesToSubtract, 
      central_or_shifts, fs, (*category)->numerator_, (*category)->denominator_);
  }

  delete inputFile;

  clock.Show("addBackground_LeptonFakeRate");

  return EXIT_SUCCESS;
}
