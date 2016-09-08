#include "tthAnalysis/HiggsToTauTau/interface/JetToTauFakeRateWeightEntry.h"

#include "FWCore/Utilities/interface/Exception.h" // cms::Exception

#include "tthAnalysis/HiggsToTauTau/interface/jetToTauFakeRateAuxFunctions.h"

namespace
{
  TGraphAsymmErrors* loadGraph(TFile* inputFile, const std::string& graphName, const std::string& etaBin, const std::string& hadTauSelection)
  {
    std::string graphName_etaBin = TString(graphName.data()).ReplaceAll("$particleEtaBin", etaBin.data()).ReplaceAll("$hadTauSelection", hadTauSelection.data()).Data();
    TGraphAsymmErrors* graph = dynamic_cast<TGraphAsymmErrors*>(inputFile->Get(graphName_etaBin.data()));
    if ( !graph ) throw cms::Exception("JetToTauFakeRateWeightEntry") 
      << "Failed to load graph = " << graphName_etaBin << " from file = " << inputFile->GetName() << " !!\n";
    TGraphAsymmErrors* graph_cloned = (TGraphAsymmErrors*)graph->Clone();
    return graph_cloned;
  }
  
  TF1* loadFitFunction(TFile* inputFile, const std::string& fitFunctionName, const std::string& etaBin, const std::string& hadTauSelection)
  {
    std::string fitFunctionName_etaBin = TString(fitFunctionName.data()).ReplaceAll("$etaBin", etaBin.data()).ReplaceAll("$hadTauSelection", hadTauSelection.data()).Data();
    TF1* fitFunction = dynamic_cast<TF1*>(inputFile->Get(fitFunctionName_etaBin.data()));
    if ( !fitFunction ) throw cms::Exception("JetToTauFakeRateWeightEntry") 
      << "Failed to load fitFunction = " << fitFunctionName_etaBin << " from file = " << inputFile->GetName() << " !!\n";
    TF1* fitFunction_cloned = (TF1*)fitFunction->Clone();
    return fitFunction_cloned;
  }
}

JetToTauFakeRateWeightEntry::JetToTauFakeRateWeightEntry(
  double absEtaMin, double absEtaMax, const std::string& hadTauSelection,
  TFile* inputFile, const edm::ParameterSet& cfg, int central_or_shift)
  : absEtaMin_(absEtaMin),
    absEtaMax_(absEtaMax),
    hadTauSelection_(hadTauSelection),
    graph_(0),
    fitFunction_(0)
{
  std::string etaBin = getEtaBin(absEtaMin_, absEtaMax_);
  graphName_ = cfg.getParameter<std::string>("graphName");
  graph_ = loadGraph(inputFile, graphName_, etaBin, hadTauSelection_);
  applyGraph_ = cfg.getParameter<bool>("applyGraph");
  std::string fitFunctionName = cfg.getParameter<std::string>("fitFunctionName");
  if      ( central_or_shift == kFRt_central   ) fitFunctionName_ = fitFunctionName;
  else if ( central_or_shift == kFRt_normUp    ) fitFunctionName_ = Form("%s_par0Up", fitFunctionName.data());
  else if ( central_or_shift == kFRt_normDown  ) fitFunctionName_ = Form("%s_par0Down", fitFunctionName.data());
  else if ( central_or_shift == kFRt_shapeUp   ) fitFunctionName_ = Form("%s_par1Up", fitFunctionName.data());
  else if ( central_or_shift == kFRt_shapeDown ) fitFunctionName_ = Form("%s_par1Down", fitFunctionName.data());
  else throw cms::Exception("JetToTauFakeRateWeightEntry")
	 << "Invalid Configuration parameter 'central_or_shift' = " << central_or_shift << " !!\n";
  fitFunction_ = loadFitFunction(inputFile, fitFunctionName_, etaBin, hadTauSelection_);
  applyFitFunction_ = cfg.getParameter<bool>("applyFitFunction");
}

JetToTauFakeRateWeightEntry::~JetToTauFakeRateWeightEntry()
{
  delete graph_;
  delete fitFunction_;
}

double JetToTauFakeRateWeightEntry::getWeight(double pt) const
{
  double weight = 1.;
  if ( applyGraph_ ) {
    weight *= graph_->Eval(pt);
  }
  if ( applyFitFunction_ ) {
    weight *= fitFunction_->Eval(pt);
  }
  return weight;
}
