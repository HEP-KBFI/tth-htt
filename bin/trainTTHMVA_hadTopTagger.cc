
/** \executable trainTTHMVA_hadTopTagger
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

  std::cout << "<trainTTHMVA_hadTopTagger>:" << std::endl;

//--- keep track of time it takes the macro to execute
  TBenchmark clock;
  clock.Start("trainTTHMVA_hadTopTagger");

//--- read python configuration parameters
  if ( !edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process") ) 
    throw cms::Exception("trainTTHMVA_hadTopTagger") 
      << "No ParameterSet 'process' found in configuration file = " << argv[1] << " !!\n";

  edm::ParameterSet cfg = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");

  edm::ParameterSet cfgTrainTTHMVA = cfg.getParameter<edm::ParameterSet>("trainTTHMVA_hadTopTagger");
  
  std::string treeName = cfgTrainTTHMVA.getParameter<std::string>("treeName");

  std::string treeDirPath = cfgTrainTTHMVA.getParameter<std::string>("treeDirPath");
  std::string treeDirPath2 = cfgTrainTTHMVA.getUntrackedParameter<std::string>("treeDirPath2", "");
  std::string treeDirPath3 = cfgTrainTTHMVA.getUntrackedParameter<std::string>("treeDirPath3", "");
  std::string preselection = cfgTrainTTHMVA.getUntrackedParameter<std::string>("preselection", "");
  std::string signalPreselection = cfgTrainTTHMVA.getUntrackedParameter<std::string>("signalPreselection", "");
  std::string bkgPreselection = cfgTrainTTHMVA.getUntrackedParameter<std::string>("bkgPreselection", "");

  vstring inputVariables = cfgTrainTTHMVA.getParameter<vstring>("inputVariables");

  vstring spectatorVariables = cfgTrainTTHMVA.getParameter<vstring>("spectatorVariables");

  std::string branchNameEvtWeight = cfgTrainTTHMVA.getParameter<std::string>("branchNameEvtWeight");

  fwlite::InputSource inputFiles(cfg); 

  std::string outputFileName = cfgTrainTTHMVA.getParameter<std::string>("outputFileName");
  std::cout << " outputFileName = " << outputFileName << std::endl;
  TFile* outputFile = new TFile(outputFileName.data(), "RECREATE");

  TChain* tree1 = new TChain((treeDirPath+'/'+treeName).data());
  TChain* tree2 = new TChain((treeDirPath2+'/'+treeName).data());
  TChain* tree3 = new TChain((treeDirPath3+'/'+treeName).data());
  for ( vstring::const_iterator inputFileName = inputFiles.files().begin();
	inputFileName != inputFiles.files().end(); ++inputFileName ) {
    std::cout << "Tree-1: adding file = " << (*inputFileName) << std::endl;
    if((*inputFileName).find("ttHToNonbb") != std::string::npos)
      tree1->AddFile(inputFileName->data());
    std::cout << "Tree-2: adding file = " << (*inputFileName) << std::endl;
    if(treeDirPath2 != "")
      if((*inputFileName).find("TTToSemilepton") != std::string::npos)
	tree2->AddFile(inputFileName->data());
    if(treeDirPath3 != "")
      if((*inputFileName).find("TTZToLLNuNu") != std::string::npos)
	tree3->AddFile(inputFileName->data());
  }
  
  if ( !(tree1->GetListOfFiles()->GetEntries() >= 1) ) {
    throw cms::Exception("trainTTHMVA_hadTopTagger") 
      << "Failed to identify Tree-1 !!\n";
  }
  if ( treeDirPath2 != "" && !(tree2->GetListOfFiles()->GetEntries() >= 1) ) {
    throw cms::Exception("trainTTHMVA_hadTopTagger") 
      << "Failed to identify background Tree-2 !!\n";
  }
  if ( treeDirPath3 != "" && !(tree3->GetListOfFiles()->GetEntries() >= 1) ) {
    throw cms::Exception("trainTTHMVA_hadTopTagger")
      << "Failed to identify background Tree-3 !!\n";
  }

  //     need to call TChain::LoadTree before processing first event 
  //     in order to prevent ROOT causing a segmentation violation,
  //     cf. http://root.cern.ch/phpBB3/viewtopic.php?t=10062
  //tree_signal->LoadTree(0);
  //tree2->LoadTree(0);

  std::cout << "Tree1 contains " << tree1->GetEntries() << " Entries in " << tree1->GetListOfFiles()->GetEntries() << " files." << std::endl;
  tree1->Print();
  tree1->Scan("*", "", "", 20, 0);

  //std::cout << "Tree2 contains " << tree2->GetEntries() << " Entries in " << tree2->GetListOfFiles()->GetEntries() << " files." << std::endl;
  //tree2->Print();
  //tree2->Scan("*", "", "", 20, 0);

//--- train MVA
  std::string mvaName = cfgTrainTTHMVA.getParameter<std::string>("mvaName");
  std::string mvaMethodType = cfgTrainTTHMVA.getParameter<std::string>("mvaMethodType");
  std::string mvaMethodName = cfgTrainTTHMVA.getParameter<std::string>("mvaMethodName");

  std::string mvaTrainingOptions = cfgTrainTTHMVA.getParameter<std::string>("mvaTrainingOptions");

  TMVA::Tools::Instance();
  TMVA::Factory* factory = new TMVA::Factory(mvaName.data(), outputFile, "!V:!Silent");
  
  //factory->AddSignalTree(tree1);
  TCut signalCut = TCut(signalPreselection.c_str());
  factory->AddTree(tree1, "Signal", 1.0, signalCut);
  if(treeDirPath2 != "")factory->AddTree(tree2, "Signal", 1.0, signalCut);
  if(treeDirPath3 != "")factory->AddTree(tree3, "Signal", 1.0, signalCut);
  //factory->AddBackgroundTree(tree2);
  TCut bkgCut = TCut(bkgPreselection.c_str());
  factory->AddTree(tree1, "Background", 1.0, bkgCut);
  if(treeDirPath2 != "")factory->AddTree(tree2, "Background", 1.0, bkgCut);
  if(treeDirPath3 != "")factory->AddTree(tree3, "Background", 1.0, bkgCut);

  for ( vstring::const_iterator inputVariable = inputVariables.begin();
	inputVariable != inputVariables.end(); ++inputVariable ) {
    unsigned int idx = inputVariable->find_last_of("/");
    if ( idx == (inputVariable->length() - 2) ) {
      std::string inputVariableName = std::string(*inputVariable, 0, idx);      
      char inputVariableType = (*inputVariable)[idx + 1];
      factory->AddVariable(inputVariableName.data(), inputVariableType);
    } else {
      throw cms::Exception("trainTTHMVA_hadTopTagger") 
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
      factory->AddSpectator(spectatorVariableName.data());
    }
  }
  if ( branchNameEvtWeight != "" ){
    factory->SetSignalWeightExpression(branchNameEvtWeight.data());
    factory->SetBackgroundWeightExpression(branchNameEvtWeight.data());
  }

  TCut cut = TCut(preselection.c_str());
  std::cout<<"preselection : "<<cut<<std::endl;
  factory->PrepareTrainingAndTestTree(cut, "nTrain_Signal=0:nTrain_Background=0:nTest_Signal=0:nTest_Background=0:SplitMode=Random:NormMode=NumEvents:!V");
  factory->BookMethod(mvaMethodType.data(), mvaMethodName.data(), mvaTrainingOptions.data());

  std::cout << "Info: calling TMVA::Factory::TrainAllMethods" << std::endl;
  factory->TrainAllMethods();
  std::cout << "Info: calling TMVA::Factory::TestAllMethods" << std::endl;
  factory->TestAllMethods();
  std::cout << "Info: calling TMVA::Factory::EvaluateAllMethods" << std::endl;
  factory->EvaluateAllMethods();  
  
  delete factory;
  TMVA::Tools::DestroyInstance();
  delete outputFile;

  delete tree1;
  delete tree2;
  delete tree3;
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
  
  clock.Show("trainTTHMVA_hadTopTagger");

  return 0;
}
