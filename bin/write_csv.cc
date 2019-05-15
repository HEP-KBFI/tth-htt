
/** \executable write_csv
 *
 * Convert files from ROOT to CSV file format.
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

#include "tthAnalysis/HiggsToTauTau/interface/branchEntryType.h"

#include <TChain.h>
#include <TTree.h>
#include <TBranch.h>
#include <TString.h>
#include <TObjArray.h>
#include <TObjString.h>
#include <TBenchmark.h>

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <ostream>
#include <assert.h>

typedef std::vector<std::string> vstring;

namespace
{
  void writeInt(std::ostream& outputStream, Int_t value, bool isLast)
  {
    outputStream << value;
    if ( !isLast ) outputStream << ",";
  }
  
  void writeFloat(std::ostream& outputStream, Float_t value, int precision, bool isLast)
  {
    std::ostringstream value_string_tmp;
    value_string_tmp << std::setprecision(precision);
    value_string_tmp << std::fixed;
    value_string_tmp << value;
    std::string value_string = value_string_tmp.str();
    for ( int iDigit = 0; iDigit < (precision - 1); ++iDigit ) {
      if ( value_string[value_string.length() - 1] == '0' ) {
	value_string = std::string(value_string, 0, value_string.length() - 1);
      } else {
	break;
      }
    }
    outputStream << value_string;
    if ( !isLast ) outputStream << ",";
  }
  
  void writeFloat_scientific(std::ostream& outputStream, Float_t value, bool isLast)
  {
    std::ostringstream value_string;    
    value_string << std::setprecision(3);
    value_string << std::scientific;
    value_string << value;
    outputStream << value_string.str();
    if ( !isLast ) outputStream << ",";
  }

  void writeDouble(std::ostream& outputStream, Double_t value, int precision, bool isLast)
  {
    std::ostringstream value_string_tmp;
    value_string_tmp << std::setprecision(precision);
    value_string_tmp << std::fixed;
    value_string_tmp << value;
    std::string value_string = value_string_tmp.str();
    for ( int iDigit = 0; iDigit < (precision - 1); ++iDigit ) {
      if ( value_string[value_string.length() - 1] == '0' ) {
	value_string = std::string(value_string, 0, value_string.length() - 1);
      } else {
	break;
      }
    }
    outputStream << value_string;
    if ( !isLast ) outputStream << ",";
  }
  
  void writeDouble_scientific(std::ostream& outputStream, Double_t value, bool isLast)
  {
    std::ostringstream value_string;    
    value_string << std::setprecision(3);
    value_string << std::scientific;
    value_string << value;
    outputStream << value_string.str();
    if ( !isLast ) outputStream << ",";
  }
}

struct EventType
{
  EventType(const std::string& line)
    : line_(line)
  {}
  ~EventType() {}
  std::string line_;
};


bool contains(const std::string& fullstring, const std::string& substring)
{
  return (fullstring.find(substring) != std::string::npos);
}

int main(int argc, char* argv[]) 
{
//--- parse command-line arguments
  if ( argc < 2 ) {
    std::cout << "Usage: " << argv[0] << " [parameters.py]" << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << "<write_csv>:" << std::endl;

//--- keep track of time it takes the macro to execute
  TBenchmark clock;
  clock.Start("write_csv");

//--- read python configuration parameters
  if ( !edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process") ) 
    throw cms::Exception("write_csv") 
      << "No ParameterSet 'process' found in configuration file = " << argv[1] << " !!\n";

  edm::ParameterSet cfg = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");

  edm::ParameterSet cfg_write_csv = cfg.getParameter<edm::ParameterSet>("write_csv");

  std::string treeName = cfg_write_csv.getParameter<std::string>("treeName");

  edm::ParameterSet cfg_branches_to_write = cfg_write_csv.getParameter<edm::ParameterSet>("branches_to_write");

  fwlite::InputSource inputFiles(cfg); 
  int maxEvents = inputFiles.maxEvents();
  std::cout << " maxEvents = " << maxEvents << std::endl;
  unsigned reportEvery = inputFiles.reportAfter();

  fwlite::OutputFiles cfg_outputFile(cfg);
  std::string outputFileName = cfg_outputFile.file();
  std::cout << " outputFileName = " << outputFileName << std::endl;
  std::ofstream* outputFile = new std::ofstream(outputFileName.data());

  std::string inputTreeName = treeName;
  TChain* inputTree = new TChain(inputTreeName.data());
  for ( std::vector<std::string>::const_iterator inputFileName = inputFiles.files().begin();
	inputFileName != inputFiles.files().end(); ++inputFileName ) {
    std::cout << "input Tree: adding file = " << (*inputFileName) << std::endl;
    inputTree->AddFile(inputFileName->data());
  }

  if ( !(inputTree->GetListOfFiles()->GetEntries() >= 1) ) {
    throw cms::Exception("write_csv") 
      << "Failed to identify input Tree !!\n";
  }

  std::vector<branchEntryBaseType*> branches; 
  int idxColumn = 0;
  vstring columnNames = cfg_branches_to_write.getParameterNamesForType<std::string>();
  for ( vstring::const_iterator columnName = columnNames.begin();
        columnName != columnNames.end(); ++columnName ) {
    std::string inputBranchName_and_Type = cfg_branches_to_write.getParameter<std::string>(*columnName);
    addBranch(branches, *columnName, inputBranchName_and_Type, "", idxColumn);
    ++idxColumn;
  }
      
  // CV: need to call TChain::LoadTree before processing first event 
  //     in order to prevent ROOT causing a segmentation violation,
  //     cf. http://root.cern.ch/phpBB3/viewtopic.php?t=10062
  inputTree->LoadTree(0);
  
  int currentTreeNumber = inputTree->GetTreeNumber();

  int numEntries = inputTree->GetEntries();
  std::cout << "input Tree contains " << numEntries << " Entries in " << inputTree->GetListOfFiles()->GetEntries() << " files." << std::endl;

  for ( std::vector<branchEntryBaseType*>::iterator branch = branches.begin();
	branch != branches.end(); ++branch ) {
    (*branch)->setInputTree(inputTree);
  }

  std::cout << "reading events from ROOT file" << std::endl;

  std::vector<EventType> events;

  for ( int iEntry = 0; iEntry < numEntries && (maxEvents == -1 || iEntry < maxEvents); ++iEntry ) {
    if ( iEntry > 0 && (iEntry % reportEvery) == 0 ) {
      std::cout << "processing Entry " << iEntry << std::endl;
    }

    inputTree->GetEntry(iEntry);

    if ( inputTree->GetTreeNumber() != currentTreeNumber ) {
      for ( std::vector<branchEntryBaseType*>::iterator branch = branches.begin();
            branch != branches.end(); ++branch ) {
        (*branch)->update();
      } 
      currentTreeNumber = inputTree->GetTreeNumber();
    }

    std::ostringstream line;
    size_t numBranches = branches.size();
    for ( size_t iBranch = 0; iBranch < numBranches; ++iBranch ) {
      branchEntryBaseType* branch = branches[iBranch];
      branch->copyBranch();
      bool isLast = (iBranch == (numBranches - 1));
      if ( branch->outputBranchType_ == branchEntryBaseType::kI ) {
	Int_t value = branch->getValue_int();
	writeInt(line, value, isLast);
      } else if ( branch->outputBranchType_ == branchEntryBaseType::kF ) {
	Float_t value = branch->getValue_float();
	if      ( branch->outputBranchFormat_ == branchEntryBaseType::kFixed      ) writeFloat(line, value, branch->outputBranchPrecision_, isLast);
	else if ( branch->outputBranchFormat_ == branchEntryBaseType::kScientific ) writeFloat_scientific(line, value, isLast);
	else assert(0);
      } else if ( branch->outputBranchType_ == branchEntryBaseType::kD ) {
	Double_t value = branch->getValue_double();
	if      ( branch->outputBranchFormat_ == branchEntryBaseType::kFixed      ) writeDouble(line, value, branch->outputBranchPrecision_, isLast);
	else if ( branch->outputBranchFormat_ == branchEntryBaseType::kScientific ) writeDouble_scientific(line, value, isLast);
	else assert(0);
      } else assert(0);
    }
    
    EventType event(line.str());

    events.push_back(event);
  }

  std::cout << "writing events to CSV file" << std::endl;

  std::ostringstream header;
  for ( std::vector<branchEntryBaseType*>::iterator branch = branches.begin();
	branch != branches.end(); ++branch ) {
    if ( branch != branches.begin() ) header << ",";
    header << (*branch)->outputBranchName_;
  }
  (*outputFile) << header.str() << std::endl;
    
  int iEntry = 0;
  for ( std::vector<EventType>::const_iterator event = events.begin();
	event != events.end(); ++event ) {
    if ( iEntry > 0 && (iEntry % reportEvery) == 0 ) {
      std::cout << "processing Entry " << iEntry << std::endl;
    }

    (*outputFile) << event->line_ << std::endl;

    ++iEntry;
  }
  
  std::cout << "num. Entries = " << events.size() << std::endl;

  for ( std::vector<branchEntryBaseType*>::iterator it = branches.begin();
	it != branches.end(); ++it ) {
    delete (*it);
  }

  delete inputTree;

  delete outputFile;

  clock.Show("write_csv");

  return 0;
}
