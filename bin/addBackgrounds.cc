
/** \executable addBackgrounds
 *
 * Add "background" contributions of different MC samples.
 *
 * \author Christian Veelken, Tallinn
 *
 */

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/PythonParameterSet/interface/MakeParameterSets.h"

#include "FWCore/Utilities/interface/Exception.h"

#include "PhysicsTools/FWLite/interface/TFileService.h"
#include "DataFormats/FWLite/interface/InputSource.h"
#include "DataFormats/FWLite/interface/OutputFiles.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h"
#include "tthAnalysis/HiggsToTauTau/interface/addBackgroundsAuxFunctions.h" // getSubdirectories, getSubdirectoryNames
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

#include <TFile.h>
#include <TH1.h>
#include <TBenchmark.h>
#include <TMath.h>
#include <TError.h> // gErrorAbortLevel, kError
#include "TPRegexp.h"
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

int main(int argc, char* argv[])
{
//--- throw an exception in case ROOT encounters an error
  gErrorAbortLevel = kError;

//--- parse command-line arguments
  if ( argc < 2 ) {
    std::cout << "Usage: " << argv[0] << " [parameters.py]" << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << "<addBackgrounds>:\n";

//--- keep track of time it takes the macro to execute
  TBenchmark clock;
  clock.Start("addBackgrounds");

//--- read python configuration parameters
  if ( !edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process") )
    throw cmsException(__func__, __LINE__)
      << "No ParameterSet 'process' found in configuration file = " << argv[1];

  edm::ParameterSet cfg = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");

  edm::ParameterSet cfgAddBackgrounds = cfg.getParameter<edm::ParameterSet>("addBackgrounds");

  vstring categories = cfgAddBackgrounds.getParameter<vstring>("categories");

  vstring processes_input = cfgAddBackgrounds.getParameter<vstring>("processes_input");
  std::string process_output = cfgAddBackgrounds.getParameter<std::string>("process_output");

  vstring central_or_shifts = cfgAddBackgrounds.getParameter<vstring>("sysShifts");
  central_or_shifts.push_back(""); // CV: add central value

  fwlite::InputSource inputFiles(cfg);
  if ( !(inputFiles.files().size() == 1) )
    throw cmsException(__func__, __LINE__) << "Exactly one input file expected";
  TFile* inputFile = new TFile(inputFiles.files().front().data());

  fwlite::OutputFiles outputFile(cfg);
  fwlite::TFileService fs = fwlite::TFileService(outputFile.file().data());

  if ( categories.size() == 0 ) categories = getSubdirectoryNames(inputFile);

  for(const std::string & category: categories)
  {

    TDirectory* dir = getDirectory(inputFile, category, true);
    assert(dir);

    std::cout << "processing category = " << category << '\n';

    std::vector<const TDirectory*> subdirs_level1 = getSubdirectories(dir);
    for(const TDirectory * subdir_level1: subdirs_level1)
    {

      std::vector<const TDirectory*> subdirs_level2 = getSubdirectories(subdir_level1);
      for(const TDirectory * subdir_level2: subdirs_level2)
      {

        std::cout << " processing directory = " << Form("%s/%s", subdir_level1->GetName(), subdir_level2->GetName()) << '\n';

        std::string the_process_input = processes_input.front();

        TDirectory * dir_input = dynamic_cast<TDirectory *>((const_cast<TDirectory *>(subdir_level2))->Get(the_process_input.data()));
        if ( !dir_input ) {
          if ( the_process_input.find("ttH_htt") != std::string::npos ||
               the_process_input.find("ttH_hww") != std::string::npos ||
               the_process_input.find("ttH_hzz") != std::string::npos ||
               the_process_input.find("ttH_hzg") != std::string::npos ||
               the_process_input.find("ttH_hmm") != std::string::npos  ) {
            continue;
          }
          if ( std::string(subdir_level2->GetName()).find("genEvt")    != std::string::npos ||
               std::string(subdir_level2->GetName()).find("lheInfo")   != std::string::npos ||
               std::string(subdir_level2->GetName()).find("cutFlow")   != std::string::npos ||
               std::string(subdir_level2->GetName()).find("evtntuple") != std::string::npos ) {
            continue;
          }
          throw cmsException(__func__, __LINE__)
            << "Failed to find subdirectory = " << the_process_input << " within directory = " << subdir_level2->GetName();
        }
        std::set<std::string> histograms;
        TList* list = dir_input->GetListOfKeys();
        TIter next(list);
        TKey* key = 0;
        while ( (key = dynamic_cast<TKey*>(next())) ) {
          TObject* object = key->ReadObj();
          TH1* histogram = dynamic_cast<TH1*>(object);
          if ( !histogram ) continue;
          TString histogramName = TString(histogram->GetName()).ReplaceAll(Form("%s_", the_process_input.data()), "");
          for ( vstring::const_iterator central_or_shift = central_or_shifts.begin();
                central_or_shift != central_or_shifts.end(); ++central_or_shift ) {
            if ( !((*central_or_shift) == "" || (*central_or_shift) == "central") ) {
              histogramName = histogramName.ReplaceAll(Form("%s_", central_or_shift->data()), "");
            }
          }
          if ( histogramName.Contains("CMS_") ) continue;
          if ( histograms.find(histogramName.Data()) == histograms.end() ) {
            std::cout << "adding histogram = " << histogramName.Data() << std::endl;
            histograms.insert(histogramName.Data());
          }
        }

        for(const std::string & histogram: histograms)
        {
          for(const std::string & central_or_shift: central_or_shifts)
          {
            std::vector<TH1 *> histograms_input;
            for(const std::string & process_input: processes_input)
            {
              bool enableException = (central_or_shift.empty() || central_or_shift == "central") ? true : false;
              TH1 * histogram_input = getHistogram(subdir_level2, process_input, histogram, central_or_shift, enableException);
              if (! histogram_input)
              {
                histogram_input = getHistogram(subdir_level2, process_input, histogram, "", true);
              }
              if(std::find(histograms_input.begin(), histograms_input.end(), histogram_input) != histograms_input.end())
              {
                throw cmsException(__func__, __LINE__)
                  << "Attempting to add the same histogram twice: " << histogram_input->GetName() << " from " << process_input;
              }
              histograms_input.push_back(histogram_input);
            }

            std::string subdirName_output = Form(
              "%s/%s/%s/%s", category.data(), subdir_level1->GetName(), subdir_level2->GetName(), process_output.data()
            );
            TDirectory * subdir_output = createSubdirectory_recursively(fs, subdirName_output);
            subdir_output->cd();

            std::string histogramName_output;
            if(! (central_or_shift.empty() || central_or_shift == "central"))
            {
              histogramName_output.append(central_or_shift);
            }
            if(histogramName_output.length() > 0)
            {
              histogramName_output.append("_");
            }
            histogramName_output.append(histogram);
            TH1 * tmp = addHistograms(histogramName_output, histograms_input);
            tmp->Write();

            for(auto & histogram_input: histograms_input)
            {
              delete histogram_input;
            }
            delete tmp;
          }
        }
        delete dir_input;
      }
      for(auto & subdir_level2: subdirs_level2)
      {
        delete subdir_level2;
      }
      subdirs_level2.clear();
    }
    for(auto & subdir_level1: subdirs_level1)
    {
      delete subdir_level1;
    }
    subdirs_level1.clear();
  }

  //---------------------------------------------------------------------------------------------------
  // CV: Add (dummy) histograms for number of analyzed and processed events
  //     This is needed to avoid run-time errors/warnings when executing python/commands/get_events_count.py (called by python/sbatch-node.template.hadd.sh)
  fs.make<TH1D>("analyzedEntries", "analyzedEntries", 1, -0.5, +0.5);
  fs.make<TH1D>("selectedEntries", "selectedEntries", 1, -0.5, +0.5);
  //---------------------------------------------------------------------------------------------------

  delete inputFile;

  clock.Show("addBackgrounds");

  std::cout << "returning exit code = " << EXIT_SUCCESS << " (EXIT_SUCCESS)." << std::endl;
  return EXIT_SUCCESS;
}
