
/** \executable trainTTHMVA_1l_2tau
 *
 * Train MVA (BDTG) to separate ttH from TTbar events
 *
 * \author Aruna Nayak 
 *
 */

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/PythonParameterSet/interface/MakeParameterSets.h"

#include "FWCore/Utilities/interface/Exception.h"

#include "PhysicsTools/FWLite/interface/TFileService.h"
#include "DataFormats/FWLite/interface/InputSource.h"
#include "DataFormats/FWLite/interface/OutputFiles.h"

#include "CondFormats/EgammaObjects/interface/GBRForest.h"

#include "TMVA/Factory.h"
#include "TMVA/MethodBase.h"
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/DataLoader.h"

#include <TFile.h>
#include <TChain.h>
#include <TTree.h>
#include <TBenchmark.h>
#include <TH1.h>
#include <TH2.h>
#include <TString.h>
#include <TObjArray.h>
#include <TObjString.h>
#include <TError.h> // gErrorAbortLevel, kError

#include <iostream>
#include <string>
#include <vector>
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

  std::cout << "<trainTTHMVA_1l_2tau>:" << std::endl;

//--- keep track of time it takes the macro to execute
  TBenchmark clock;
  clock.Start("trainTTHMVA_1l_2tau");

//--- read python configuration parameters
  if ( !edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process") ) 
    throw cms::Exception("trainTTHMVA_1l_2tau") 
      << "No ParameterSet 'process' found in configuration file = " << argv[1] << " !!\n";

  edm::ParameterSet cfg = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");

  edm::ParameterSet cfgTrainTTHMVA = cfg.getParameter<edm::ParameterSet>("trainTTHMVA_1l_2tau");
  
  std::string treeName = cfgTrainTTHMVA.getParameter<std::string>("treeName");

  std::string signalDirPath = cfgTrainTTHMVA.getParameter<std::string>("signalDirPath");
  std::string backgroundDirPath = cfgTrainTTHMVA.getParameter<std::string>("backgroundDirPath");
  std::string backgroundDirPath2 = cfgTrainTTHMVA.getUntrackedParameter<std::string>("backgroundDirPath2", "");
  std::string preselection = cfgTrainTTHMVA.getUntrackedParameter<std::string>("preselection", "");
  std::string signalPreselection = cfgTrainTTHMVA.getUntrackedParameter<std::string>("signalPreselection", "");

  vstring inputVariables = cfgTrainTTHMVA.getParameter<vstring>("inputVariables");

  vstring spectatorVariables = cfgTrainTTHMVA.getParameter<vstring>("spectatorVariables");

  std::string branchNameEvtWeight = cfgTrainTTHMVA.getParameter<std::string>("branchNameEvtWeight");

  fwlite::InputSource inputFiles(cfg); 

  std::string outputFileName = cfgTrainTTHMVA.getParameter<std::string>("outputFileName");
  std::cout << " outputFileName = " << outputFileName << std::endl;
  TFile* outputFile = new TFile(outputFileName.data(), "RECREATE");

  TChain* tree_signal = new TChain((signalDirPath+'/'+treeName).data());
  TChain* tree_background = new TChain((backgroundDirPath+'/'+treeName).data());
  TChain* tree_background2 = new TChain((backgroundDirPath2+'/'+treeName).data());
  for ( vstring::const_iterator inputFileName = inputFiles.files().begin();
	inputFileName != inputFiles.files().end(); ++inputFileName ) {
    std::cout << "signal Tree: adding file = " << (*inputFileName) << std::endl;
    tree_signal->AddFile(inputFileName->data());
    std::cout << "background Tree: adding file = " << (*inputFileName) << std::endl;
    tree_background->AddFile(inputFileName->data());
    if(backgroundDirPath2 != "")tree_background2->AddFile(inputFileName->data());
  }
  
  if ( !(tree_signal->GetListOfFiles()->GetEntries() >= 1) ) {
    throw cms::Exception("trainTTHMVA_1l_2tau") 
      << "Failed to identify signal Tree !!\n";
  }
  if ( !(tree_background->GetListOfFiles()->GetEntries() >= 1) ) {
    throw cms::Exception("trainTTHMVA_1l_2tau") 
      << "Failed to identify background Tree !!\n";
  }

  //     need to call TChain::LoadTree before processing first event 
  //     in order to prevent ROOT causing a segmentation violation,
  //     cf. http://root.cern.ch/phpBB3/viewtopic.php?t=10062
  //tree_signal->LoadTree(0);
  //tree_background->LoadTree(0);

  std::cout << "signal Tree contains " << tree_signal->GetEntries() << " Entries in " << tree_signal->GetListOfFiles()->GetEntries() << " files." << std::endl;
  tree_signal->Print();
  tree_signal->Scan("*", "", "", 20, 0);

  std::cout << "background Tree contains " << tree_background->GetEntries() << " Entries in " << tree_background->GetListOfFiles()->GetEntries() << " files." << std::endl;
  tree_background->Print();
  tree_background->Scan("*", "", "", 20, 0);

//--- train MVA
  std::string mvaName = cfgTrainTTHMVA.getParameter<std::string>("mvaName");
  std::string mvaMethodType = cfgTrainTTHMVA.getParameter<std::string>("mvaMethodType");
  std::string mvaMethodName = cfgTrainTTHMVA.getParameter<std::string>("mvaMethodName");

  std::string mvaTrainingOptions = cfgTrainTTHMVA.getParameter<std::string>("mvaTrainingOptions");

  TMVA::Tools::Instance();
  TMVA::DataLoader * dataLoader = new TMVA::DataLoader();
  TMVA::Factory* factory = new TMVA::Factory(mvaName.data(), outputFile, "!V:!Silent");
  
  TCut signalCut = TCut(signalPreselection.c_str());
  dataLoader->AddTree(tree_signal, "Signal", 1.0, signalCut);
  dataLoader->AddBackgroundTree(tree_background);
  if(backgroundDirPath2 != "")dataLoader->AddBackgroundTree(tree_background2);

  for ( vstring::const_iterator inputVariable = inputVariables.begin();
	inputVariable != inputVariables.end(); ++inputVariable ) {
    unsigned int idx = inputVariable->find_last_of("/");
    if ( idx == (inputVariable->length() - 2) ) {
      std::string inputVariableName = std::string(*inputVariable, 0, idx);      
      char inputVariableType = (*inputVariable)[idx + 1];
      dataLoader->AddVariable(inputVariableName.data(), inputVariableType);
    } else {
      throw cms::Exception("trainTTHMVA_1l_2tau") 
	<< "Failed to determine name & type for inputVariable = " << (*inputVariable) << " !!\n";
    }
  }
  for ( vstring::const_iterator spectatorVariable = spectatorVariables.begin();
	spectatorVariable != spectatorVariables.end(); ++spectatorVariable ) {
    int idxSpectatorVariable = spectatorVariable->find_last_of("/");
    std::string spectatorVariableName = std::string(*spectatorVariable, 0, idxSpectatorVariable);      
    bool isInputVariable = false;
    for ( vstring::const_iterator inputVariable = inputVariables.begin();
	  inputVariable != inputVariables.end(); ++inputVariable ) {
      int idxInputVariable = inputVariable->find_last_of("/");
      std::string inputVariableName = std::string(*inputVariable, 0, idxInputVariable); 
      if ( spectatorVariableName == inputVariableName ) isInputVariable = true;
    }
    if ( !isInputVariable ) {
      dataLoader->AddSpectator(spectatorVariableName.data());
    }
  }
  if ( branchNameEvtWeight != "" ){
    dataLoader->SetSignalWeightExpression(branchNameEvtWeight.data());
    dataLoader->SetBackgroundWeightExpression(branchNameEvtWeight.data());
  }

  TCut cut = TCut(preselection.c_str());
  std::cout<<"preselection : "<<cut<<std::endl;
  dataLoader->PrepareTrainingAndTestTree(cut, "nTrain_Signal=0:nTrain_Background=0:nTest_Signal=0:nTest_Background=0:SplitMode=Random:NormMode=NumEvents:!V");
  factory->BookMethod(dataLoader, mvaMethodType.data(), mvaMethodName.data(), mvaTrainingOptions.data());

  std::cout << "Info: calling TMVA::Factory::TrainAllMethods" << std::endl;
  factory->TrainAllMethods();
  std::cout << "Info: calling TMVA::Factory::TestAllMethods" << std::endl;
  factory->TestAllMethods();
  std::cout << "Info: calling TMVA::Factory::EvaluateAllMethods" << std::endl;
  factory->EvaluateAllMethods();  
  
  delete factory;
  TMVA::Tools::DestroyInstance();
  delete outputFile;

  delete tree_signal;
  delete tree_background;

  /*
  std::cout << "Info: converting MVA to GBRForest format" << std::endl;
  TMVA::Tools::Instance();
  TMVA::Reader* reader = new TMVA::Reader("!V:!Silent");
  Float_t dummyVariable;
  for ( vstring::const_iterator inputVariable = inputVariables.begin();
	inputVariable != inputVariables.end(); ++inputVariable ) {
    int idx = inputVariable->find_last_of("/");
    std::string inputVariableName = std::string(*inputVariable, 0, idx);
    reader->AddVariable(inputVariableName.data(), &dummyVariable);    
  }
  for ( vstring::const_iterator spectatorVariable = spectatorVariables.begin();
	spectatorVariable != spectatorVariables.end(); ++spectatorVariable ) {
    int idxSpectatorVariable = spectatorVariable->find_last_of("/");
    std::string spectatorVariableName = std::string(*spectatorVariable, 0, idxSpectatorVariable);      
    bool isInputVariable = false;
    for ( vstring::const_iterator inputVariable = inputVariables.begin();
	  inputVariable != inputVariables.end(); ++inputVariable ) {
      int idxInputVariable = inputVariable->find_last_of("/");
      std::string inputVariableName = std::string(*inputVariable, 0, idxInputVariable); 
      if ( spectatorVariableName == inputVariableName ) isInputVariable = true;
    }
    if ( !isInputVariable ) {
      reader->AddSpectator(spectatorVariableName.data(), &dummyVariable);
    }
  }
  TMVA::IMethod* mva = reader->BookMVA(mvaMethodName.data(), Form("weights/%s_%s.weights.xml", mvaName.data(), mvaMethodName.data()));
  saveAsGBRForest(mva, mvaName, outputFileName);
  delete mva;
  */
  
  clock.Show("trainTTHMVA_1l_2tau");

  return 0;
}
