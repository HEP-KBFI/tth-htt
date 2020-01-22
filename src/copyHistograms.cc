#include "tthAnalysis/HiggsToTauTau/interface/copyHistograms.h"

#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

#include <TFile.h> // TFile
#include <TKey.h>  // TKey
#include <TH1.h>   // TH1, TH1F, TH1D

#include <iostream> // std::cout, std::endl
#include <assert.h> // assert

void 
copyHistograms(const fwlite::InputSource& inputFiles, const std::vector<std::regex>& copy_histograms_regex, fwlite::TFileService& fs)
{
//--- copy histograms keeping track of number of processed events from input files to output file

  std::cout << "copying histograms:\n";
  std::map<std::string, TH1*> histograms;
  std::smatch histogram_match;
  for ( const std::string & inputFileName: inputFiles.files() )
  {
    TFile* inputFile = new TFile(inputFileName.data());
    if ( !inputFile || inputFile -> IsZombie() )
    {
      throw cmsException(__func__) << "Failed to open input File = '" << inputFileName << "' !!\n";
    }

    TIter next(inputFile->GetListOfKeys());
    TKey * key = nullptr;
    while((key = static_cast<TKey *>(next())))
    {
      const std::string histogramName = key->GetName();
      bool is_match = false;
      for(const std::regex & copy_histogram_regex: copy_histograms_regex)
      {
        if(std::regex_match(histogramName, histogram_match, copy_histogram_regex))
        {
          is_match = true;
          break;
        }
      }
      if(! is_match)
      {
        continue;
      }

      if(inputFiles.files().size() > 1)
      {
        std::cout << ' ' << histogramName << " from input File = '" << inputFileName << "'\n";
      }
      else
      {
        std::cout << ' ' << histogramName << '\n';
      }
      TH1 * const histogram_input = dynamic_cast<TH1 *>(inputFile->Get(histogramName.data()));
      if(! histogram_input)
      {
        continue;
      }

      TH1 * histogram_output = histograms[histogramName];
      if(histogram_output)
      {
        histogram_output->Add(histogram_input);
      }
      else
      {
        if(dynamic_cast<TH1F *>(histogram_input))
        {
          histogram_output = fs.make<TH1F>(*(dynamic_cast<TH1F *>(histogram_input)));
        }
        else if(dynamic_cast<TH1D*>(histogram_input))
        {
          histogram_output = fs.make<TH1D>(*(dynamic_cast<TH1D *>(histogram_input)));
        }
        assert(histogram_output);
        histograms[histogramName] = histogram_output;
      }
    }
    delete inputFile;
  } // inputFileName
}
