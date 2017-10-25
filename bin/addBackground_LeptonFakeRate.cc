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

  std::vector<TDirectory*> getSubdirectories(const TDirectory* dir)
  {
    std::vector<TDirectory*> subdirectories;
    TList* list = dir->GetListOfKeys();
    TIter next(list);
    TKey* key = 0;
    while ( (key = dynamic_cast<TKey*>(next())) ) {
      TObject* object = key->ReadObj();
      TDirectory* subdirectory = dynamic_cast<TDirectory*>(object);
      if ( subdirectory ) subdirectories.push_back(subdirectory);
    }
    return subdirectories;
  }
}


void processHistogram(const TFile* inputFile, const TDirectory* dir_den, const TDirectory* dir_num, const std::string& processData, const std::string& processLeptonFakes, 
       const vstring& processesToSubtract, const vstring& central_or_shifts, fwlite::TFileService& fs, const std::string& cat_num){
  /*
  // TDirectory* dirData_num = dynamic_cast<TDirectory*>( dir_num->Get(processData.data()) );
  TDirectory* dirData_num = (TDirectory*)( dir_num->Get(processData.data()) );

  if(!dirData_num){ 
    std::cout << "Failed to find subdirectory = " << processData << " within directory = " << dirData_num->GetName() << std::endl; 
    return;
  }
  */
   // TDirectory* dirData_den = dynamic_cast<TDirectory*>( dir_den->Get(processData.data()) );
  //  std::cout<< "Inside processhistogram "<< std::endl;

  const TDirectory* dirData_den = getSubdirectory(dir_den, processData, false);
  if(!dirData_den){ 
    std::cout << "Failed to find subdirectory = " << processData << " within directory = " << dir_den->GetPath() << std::endl; 
    return;
  }


  // dir_den->Get(processData.data()) );

  
  if(!dirData_den){ 
    std::cout << "Failed to find subdirectory = " << processData << " within directory = " << dirData_den->GetName() << std::endl; 
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
      // std::cout << "adding histogram = " << histogramName.Data() << std::endl;                                                                                                                      
      histograms.insert(histogramName.Data());                                                                                                                                                      
    }                                                                                                                                                                                               
  }                             

  for(std::set<std::string>::const_iterator histogram = histograms.begin();histogram != histograms.end(); ++histogram){                                                                      
           // std::cout << "histogram = " << (*histogram) << std::endl;                                                                                                                                
      for(vstring::const_iterator central_or_shift = central_or_shifts.begin();central_or_shift != central_or_shifts.end(); ++central_or_shift){     
     	    //int verbosity = ( histogram->find("EventCounter") != std::string::npos && ((*central_or_shift) == "" || (*central_or_shift) == "central") ) ? 1 : 0;
	    int verbosity = ( histogram->find("mvaOutput_1l_2tau_ttbar_Matthias") != std::string::npos && ((*central_or_shift) == "" || (*central_or_shift) == "central") ) ? 1 : 0;
	    //int verbosity = ( histogram->find("EventCounter") != std::string::npos ) ? 1 : 0;

        TH1* histogramData_den = getHistogram(dir_den, processData, *histogram, *central_or_shift, false);                                                                             
        if(!histogramData_den){                                                                                                                                                                       
         	histogramData_den = getHistogram(dir_den, processData, *histogram, "central", true);                                                                                         
        	// histogramData_den = getHistogram(dir_den, processData, *histogram, "", true);                                                                                         
        }                                                                                                                                                                                             

        if(verbosity){                                                                                                                                                                            
	    std::cout << " Den. integral(data_obs) = " << histogramData_den->Integral() << std::endl;                                                                                            
        }                  

        TH1* histogramData_num = getHistogram(dir_num, processData, *histogram, *central_or_shift, false);                                                                             
        if ( !histogramData_num ) {                                                                                  
	        histogramData_num = getHistogram(dir_num, processData, *histogram, "central", true);
        	// histogramData_num = getHistogram(dir_num, processData, *histogram, "", true);
                                                                                         
        }                                                                                                                                                                                             

        if ( verbosity ) {                                                                                                                                                                            
	    std::cout << " Num. integral(data_obs) = " << histogramData_num->Integral() << std::endl;                                                                                                
            }                  

        std::vector<TH1*> histogramsToSubtract_den;                                                                                                                                                     
        std::vector<TH1*> histogramsToSubtract_num;                                                                                                                                                   

	for(vstring::const_iterator processToSubtract = processesToSubtract.begin(); processToSubtract != processesToSubtract.end(); ++processToSubtract){                                           
             TH1* histogramToSubtract_den = getHistogram(dir_den, *processToSubtract, *histogram, *central_or_shift, false);                                                        
	     TH1* histogramToSubtract_num = getHistogram(dir_num, *processToSubtract, *histogram, *central_or_shift, false);                                                        

             if(!histogramToSubtract_den) histogramToSubtract_den = getHistogram(dir_den, *processToSubtract, *histogram, "central", true);                                                
	     if(verbosity){                                                                                                                                                                          
	        std::cout << " Den. integral(" << (*processToSubtract) << ") = " << histogramToSubtract_den->Integral() << std::endl;                                                           
             }                                                                      

             if(!histogramToSubtract_num) histogramToSubtract_num = getHistogram(dir_num, *processToSubtract, *histogram, "central", true);                                                
	     if(verbosity){                                                                                                                                                                          
	        std::cout << " Num. integral(" << (*processToSubtract) << ") = " << histogramToSubtract_num->Integral() << std::endl;                                                        
             }

          histogramsToSubtract_den.push_back(histogramToSubtract_den);                                                                                                                              
          histogramsToSubtract_num.push_back(histogramToSubtract_num);                                                                                                                            
       	}                        

	// std::string subdirName_output = Form("%s%s/%s", cat_num.data(), dir_num->GetName(), processLeptonFakes.data());        

	TString subdirName_num = TString(dir_num->GetPath());
	std::string subdirName_string = subdirName_num.Data();
	size_t pos = subdirName_string.find(":/");
        assert(pos < (subdirName_string.length() - 2));
        subdirName_string = std::string(subdirName_string, pos + 2);
        subdirName_num = subdirName_string.data();

	std::string subdirName2_string = subdirName_num.Data();
	std::string subdirName_output = Form("%s/%s", subdirName2_string.data(), processLeptonFakes.data());        
       
	// std::cout<< " subdirName_output " << subdirName_output << std::endl;
        TDirectory* subdir_output = createSubdirectory_recursively(fs, subdirName_output);
      	subdir_output->cd();                                                                                                                                                                          

	std::string histogramNameLeptonFakes;                                                                                                                                                         
	if ( !((*central_or_shift) == "" || (*central_or_shift) == "central") ) histogramNameLeptonFakes.append(*central_or_shift);                                                                   
	if ( histogramNameLeptonFakes.length() > 0 ) histogramNameLeptonFakes.append("_");                                                                                                            
	histogramNameLeptonFakes.append(*histogram);                                                                                                                                                  
	TH1* histogramLeptonFakes = subtractHistograms(histogramNameLeptonFakes, histogramData_den, histogramsToSubtract_den, verbosity);  
      	if ( verbosity ) {                                                                                                                                                                            
	  std::cout << " integral(Fakes) before scaling = " << histogramLeptonFakes->Integral() << std::endl;                                                                                   
                   }                                                                                                                                                                        
	makeBinContentsPositive(histogramLeptonFakes, verbosity);

        double integral_num = compIntegral(histogramData_num, true, true);
        for ( std::vector<TH1*>::const_iterator histogramToSubtract_num = histogramsToSubtract_num.begin();
	      histogramToSubtract_num != histogramsToSubtract_num.end(); ++histogramToSubtract_num ) {
          integral_num -= compIntegral(*histogramToSubtract_num, true, true);
        }
        double integral_den = compIntegral(histogramLeptonFakes, true, true);
        if ( integral_den > 0. ) {
          histogramLeptonFakes->Scale(integral_num/integral_den);
	  std::cout<< "integral_num " << integral_num << " integral_den " << integral_den << " integral_num/integral_den " << (integral_num/integral_den) << std::endl;
          std::cout<< " integral(Fakes) after scaling = " << histogramLeptonFakes->Integral() << std::endl;                                                                                   
	}

    }
  }

}


void processDirectory(const TFile* inputFile, const TDirectory* den, const TDirectory* num, const std::string& processData, const std::string& processLeptonFakes, const vstring& processesToSubtract, const vstring& central_or_shifts, fwlite::TFileService& fs, const std::string& cat_num, const std::string& cat_den){
 
        processHistogram(inputFile, den, num, processData, processLeptonFakes, processesToSubtract, central_or_shifts, fs, cat_num);   

  std::vector<TDirectory*> subdirs_denominator = getSubdirectories(den);  
  for(std::vector<TDirectory*>::iterator subdir_denominator = subdirs_denominator.begin();
      subdir_denominator != subdirs_denominator.end(); ++subdir_denominator){ 
      TString subdirName_num = TString((*subdir_denominator)->GetPath()).ReplaceAll("denominator", "numerator"); 
      subdirName_num = subdirName_num.ReplaceAll("fakeable", "tight"); 
      if ( subdirName_num.First(":/") < (subdirName_num.Length() - 2) ) {
	std::string subdirName_string = subdirName_num.Data();
        size_t pos = subdirName_string.find(":/");
        assert(pos < (subdirName_string.length() - 2));
        subdirName_string = std::string(subdirName_string, pos + 2); 
        subdirName_num = subdirName_string.data();
      }

      // std::cout<< "*subdir_denominator " << (*subdir_denominator)->GetPath() << std::endl;
      // std::cout<< "subdirName_num " << subdirName_num << std::endl;

      TDirectory* subdir_num = getDirectory(inputFile, subdirName_num.Data(), true);

      if(subdir_num && (*subdir_denominator)){
	processDirectory(inputFile, *subdir_denominator, subdir_num, processData, processLeptonFakes, processesToSubtract, central_or_shifts, fs, cat_num, cat_den);
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

  std::cout << "<addBackground_LeptsonFakeRate>:" << std::endl;

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

  fwlite::OutputFiles outputFile(cfg);
  fwlite::TFileService fs = fwlite::TFileService(outputFile.file().data());


  for(std::vector<categoryEntryType*>::const_iterator category = categories.begin();category != categories.end(); ++category){                                                                  
      std::cout << "processing category: numerator = " << (*category)->numerator_ << ", denominator = " << (*category)->denominator_ << std::endl;                                                   
   
    TDirectory* dir_denominator = getDirectory(inputFile, (*category)->denominator_, true);                                                                                                      
    assert(dir_denominator);                                                                                                                                                                      
    TDirectory* dir_numerator = getDirectory(inputFile, (*category)->numerator_, true);                                                                                                           
    assert(dir_numerator);  

    // void processDirectory(TFile* inputFile, TDirectory* den, TDirectory* num, std::string processData, std::string processLeptonFakes, vstring processesToSubtract, vstring central_or_shifts, fwlite::TFileService fs, std::string cat_num, std::string cat_den){

    processDirectory(inputFile, dir_denominator, dir_numerator, processData, processLeptonFakes, processesToSubtract, central_or_shifts, fs, (*category)->numerator_, (*category)->denominator_);

  }



/*
  for ( std::vector<categoryEntryType*>::const_iterator category = categories.begin();category != categories.end(); ++category ) {
    std::cout << "processing category: numerator = " << (*category)->numerator_ << ", denominator = " << (*category)->denominator_ << std::endl;

    TDirectory* dir_denominator = getDirectory(inputFile, (*category)->denominator_, true);
    assert(dir_denominator); 	
    TDirectory* dir_numerator = getDirectory(inputFile, (*category)->numerator_, true);
    assert(dir_numerator); 	

    std::vector<TDirectory*> subdirs_denominator_level1 = getSubdirectories(dir_denominator);
    std::vector<TDirectory*> subdirs_numerator_level1 = getSubdirectories(dir_numerator);

    for(std::vector<TDirectory*>::iterator subdir_denominator_level1 = subdirs_denominator_level1.begin();
         subdir_denominator_level1 != subdirs_denominator_level1.end(); ++subdir_denominator_level1){  
         std::cout<< (*subdir_denominator_level1)->GetName() << std::endl;


      std::vector<TDirectory*> subdirs_denominator_level2 = getSubdirectories(*subdir_denominator_level1);
      for ( std::vector<TDirectory*>::iterator subdir_denominator_level2 = subdirs_denominator_level2.begin();
	    subdir_denominator_level2 != subdirs_denominator_level2.end(); ++subdir_denominator_level2 ) {
	

          TDirectory* dirData = dynamic_cast<TDirectory*>((*subdir_denominator_level2)->Get(processData.data()));
          if ( !dirData ) {
	     // std::cout << "Failed to find subdirectory = " << processData << " within directory = " << (*subdir_denominator_level2)->GetName() << " --> skipping !!\n";
	     continue;
	  }
          std::cout << " processing directory = " << Form("%s/%s", (*subdir_denominator_level1)->GetName(), (*subdir_denominator_level2)->GetName()) << std::endl;

      }
    }


    for(std::vector<TDirectory*>::iterator subdir_numerator_level1 = subdirs_numerator_level1.begin();
         subdir_numerator_level1 != subdirs_numerator_level1.end(); ++subdir_numerator_level1){  
         std::cout<< (*subdir_numerator_level1)->GetName() << std::endl;

      std::vector<TDirectory*> subdirs_numerator_level2 = getSubdirectories(*subdir_numerator_level1);
      for ( std::vector<TDirectory*>::iterator subdir_numerator_level2 = subdirs_numerator_level2.begin();
	    subdir_numerator_level2 != subdirs_numerator_level2.end(); ++subdir_numerator_level2 ) {

          TDirectory* dirData = dynamic_cast<TDirectory*>((*subdir_numerator_level2)->Get(processData.data()));
          if ( !dirData ) {
              // std::cout << "Failed to find subdirectory = " << processData << " within directory = " << (*subdir_numerator_level2)->GetName() << " --> skipping !!\n";
	     continue;
	  }
	  std::cout << " processing directory = " << Form("%s/%s", (*subdir_numerator_level1)->GetName(), (*subdir_numerator_level2)->GetName()) << std::endl;

      }
    }



  }
*/




/*

// ------------ DEF BLOCK ---------------  
  for ( std::vector<categoryEntryType*>::const_iterator category = categories.begin();
	category != categories.end(); ++category ) {
    std::cout << "processing category: numerator = " << (*category)->numerator_ << ", denominator = " << (*category)->denominator_ << std::endl;

    TDirectory* dir_denominator = getDirectory(inputFile, (*category)->denominator_, true);
    assert(dir_denominator); 	

    std::vector<TDirectory*> subdirs_denominator_level1 = getSubdirectories(dir_denominator);
    for ( std::vector<TDirectory*>::iterator subdir_denominator_level1 = subdirs_denominator_level1.begin();
	  subdir_denominator_level1 != subdirs_denominator_level1.end(); ++subdir_denominator_level1 ) {
      std::vector<TDirectory*> subdirs_denominator_level2 = getSubdirectories(*subdir_denominator_level1);
      for ( std::vector<TDirectory*>::iterator subdir_denominator_level2 = subdirs_denominator_level2.begin();
	    subdir_denominator_level2 != subdirs_denominator_level2.end(); ++subdir_denominator_level2 ) {
	std::cout << " processing directory = " << Form("%s/%s", (*subdir_denominator_level1)->GetName(), (*subdir_denominator_level2)->GetName()) << std::endl;

        TDirectory* dirData = dynamic_cast<TDirectory*>((*subdir_denominator_level2)->Get(processData.data()));
        if ( !dirData ) {
	  std::cout << "Failed to find subdirectory = " << processData << " within directory = " << (*subdir_denominator_level2)->GetName() << " --> skipping !!\n";
	  continue;
	}

        std::set<std::string> histograms;
        TList* list = dirData->GetListOfKeys();
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
	    std::cout << "adding histogram = " << histogramName.Data() << std::endl;
	    histograms.insert(histogramName.Data());
	  }
	}
	
	for ( std::set<std::string>::const_iterator histogram = histograms.begin();
	      histogram != histograms.end(); ++histogram ) {
	  std::cout << "histogram = " << (*histogram) << std::endl;
	  for ( vstring::const_iterator central_or_shift = central_or_shifts.begin();
		central_or_shift != central_or_shifts.end(); ++central_or_shift ) {

	    //int verbosity = ( histogram->find("EventCounter") != std::string::npos && ((*central_or_shift) == "" || (*central_or_shift) == "central") ) ? 1 : 0;
	    int verbosity = ( histogram->find("mvaOutput_1l_2tau_ttbar_Matthias") != std::string::npos && ((*central_or_shift) == "" || (*central_or_shift) == "central") ) ? 1 : 0;
	    //int verbosity = ( histogram->find("EventCounter") != std::string::npos ) ? 1 : 0;

	    TH1* histogramData = getHistogram(*subdir_denominator_level2, processData, *histogram, *central_or_shift, false);
	    if ( !histogramData ) {
	      histogramData = getHistogram(*subdir_denominator_level2, processData, *histogram, "central", true);
	    }
	    if ( verbosity ) {
	      std::cout << " integral(data_obs) = " << histogramData->Integral() << std::endl;
	    }
	    
	    std::vector<TH1*> histogramsToSubtract;
	    for ( vstring::const_iterator processToSubtract = processesToSubtract.begin();
		  processToSubtract != processesToSubtract.end(); ++processToSubtract ) {
	      TH1* histogramToSubtract = getHistogram(*subdir_denominator_level2, *processToSubtract, *histogram, *central_or_shift, false);
	      if ( !histogramToSubtract ) histogramToSubtract = getHistogram(*subdir_denominator_level2, *processToSubtract, *histogram, "central", true);
	      if ( verbosity ) {
		std::cout << " integral(" << (*processToSubtract) << ") = " << histogramToSubtract->Integral() << std::endl;
	      }
	      histogramsToSubtract.push_back(histogramToSubtract);
	    }
	    
	    std::string subdirName_output = Form("%s/%s/%s/%s", (*category)->numerator_.data(), (*subdir_denominator_level1)->GetName(), (*subdir_denominator_level2)->GetName(), processLeptonFakes.data());
	    TDirectory* subdir_output = createSubdirectory_recursively(fs, subdirName_output);
	    subdir_output->cd();

	    std::string histogramNameLeptonFakes;
	    if ( !((*central_or_shift) == "" || (*central_or_shift) == "central") ) histogramNameLeptonFakes.append(*central_or_shift);
	    if ( histogramNameLeptonFakes.length() > 0 ) histogramNameLeptonFakes.append("_");
	    histogramNameLeptonFakes.append(*histogram);
	    TH1* histogramLeptonFakes = subtractHistograms(histogramNameLeptonFakes, histogramData, histogramsToSubtract, verbosity);
	    if ( verbosity ) {
	      std::cout << " integral(Fakes) = " << histogramLeptonFakes->Integral() << std::endl;
	    }
	    makeBinContentsPositive(histogramLeptonFakes, verbosity);	  
          }
	}

      }
    }
  }
// --------------------------------

*/



  delete inputFile;

  clock.Show("addBackground_LeptonFakeRate");

  return EXIT_SUCCESS;
}
