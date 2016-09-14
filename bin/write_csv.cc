
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

  void writeChar(std::ostream& outputStream, Char_t value, bool isLast)
  {
    outputStream << value;
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
    return 0;
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

  typedef std::vector<std::string> vstring;
  vstring branches_to_write = cfg_write_csv.getParameter<vstring>("branches_to_write");

  fwlite::InputSource inputFiles(cfg); 
  int maxEvents = inputFiles.maxEvents();
  std::cout << " maxEvents = " << maxEvents << std::endl;
  unsigned reportEvery = inputFiles.reportAfter();

  fwlite::OutputFiles cfg_outputFile(cfg);
  std::string outputFileName = cfg_outputFile.file();
  std::cout << " outputFileName = " << outputFileName << std::endl;
  std::ofstream* outputFile = new std::ofstream(outputFileName.data());

  std::string inputTreeName = "HiggsBosonMachineLearningChallenge";
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

  std::vector<branchEntryType*> branches; 
  enum { kFixed, kScientific };
  std::map<std::string, int> branch_format;    // key = branchName
  std::map<std::string, int> branch_precision; // key = branchName
  int idxColumn = 0;
  for ( vstring::const_iterator branchName_to_write = branches_to_write.begin();
	branchName_to_write != branches_to_write.end(); ++branchName_to_write ) {
    TBranch* inputTree_branch = inputTree->GetBranch(branchName_to_write->data());
    if ( !inputTree_branch )
      throw cms::Exception("write_csv") 
	<< "No branch = '" << (*branchName_to_write) << "' found in input tree !!\n";
    std::string name_and_type = inputTree_branch->GetTitle();
    std::cout << "adding branch = " << (*branchName_to_write) << std::endl;
    if ( contains(name_and_type, "/I") ) {
      addBranch(branches, *branchName_to_write, branchEntryType::kInt, idxColumn);
    } else if ( contains(name_and_type, "/F") ) {
      addBranch(branches, *branchName_to_write, branchEntryType::kFloat, idxColumn);
      branch_format[*branchName_to_write] = kScientific;
      branch_precision[*branchName_to_write] = 6;
    } else if ( contains(name_and_type, "/D") ) {
      addBranch(branches, *branchName_to_write, branchEntryType::kDouble, idxColumn);
      branch_format[*branchName_to_write] = kScientific;
      branch_precision[*branchName_to_write] = 6;      
    } else if ( contains(name_and_type, "/C") ) {
      addBranch(branches, *branchName_to_write, branchEntryType::kChar, idxColumn);
    } else throw cms::Exception("write_csv") 
	<< "Branch = " << (*branchName_to_write) << " has invalid type !!\n";
    ++idxColumn;
  }
      
  // CV: need to call TChain::LoadTree before processing first event 
  //     in order to prevent ROOT causing a segmentation violation,
  //     cf. http://root.cern.ch/phpBB3/viewtopic.php?t=10062
  inputTree->LoadTree(0);
  
  int numEntries = inputTree->GetEntries();
  std::cout << "input Tree contains " << numEntries << " Entries in " << inputTree->GetListOfFiles()->GetEntries() << " files." << std::endl;

  for ( std::vector<branchEntryType*>::iterator branch = branches.begin();
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

    std::ostringstream line;
    size_t numBranches = branches.size();
    for ( size_t iBranch = 0; iBranch < numBranches; ++iBranch ) {
      branchEntryType* branch = branches[iBranch];
      branch->copyInputToOutputValue();
      const std::string& branchName = branch->name_;
      bool isLast = (iBranch == (numBranches - 1));
      if ( branch->type_ == branchEntryType::kInt ) {
	writeInt(line, branch->getValue_int(), isLast);
      } else if ( branch->type_ == branchEntryType::kFloat ) {
	float value = branch->getValue_float();
	if      ( branch_format[branchName] == kFixed      ) writeFloat(line, value, branch_precision[branchName], isLast);
	else if ( branch_format[branchName] == kScientific ) writeFloat_scientific(line, value, isLast);
	else assert(0);
      } else if ( branch->type_ == branchEntryType::kDouble ) {
	double value = branch->getValue_double();
	if      ( branch_format[branchName] == kFixed      ) writeDouble(line, value, branch_precision[branchName], isLast);
	else if ( branch_format[branchName] == kScientific ) writeDouble_scientific(line, value, isLast);
	else assert(0);
      } else if ( branch->type_ == branchEntryType::kChar ) {
	writeChar(line, branch->getValue_char(), isLast);
      } else assert(0);
    }
    
    EventType event(line.str());

    events.push_back(event);
  }

  std::cout << "writing events to CSV file" << std::endl;

  std::ostringstream header;
  for ( std::vector<branchEntryType*>::iterator branch = branches.begin();
	branch != branches.end(); ++branch ) {
    if ( branch != branches.begin() ) header << ",";
    header << (*branch)->name_;
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

  for ( std::vector<branchEntryType*>::iterator it = branches.begin();
	it != branches.end(); ++it ) {
    delete (*it);
  }

  delete inputTree;

  delete outputFile;

  clock.Show("write_csv");

  return 0;
}
