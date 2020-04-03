#include "tthAnalysis/HiggsToTauTau/interface/JetToTauFakeRateWeightEntry.h"

#include "tthAnalysis/HiggsToTauTau/interface/jetToTauFakeRateAuxFunctions.h" // getEtaBin()
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/sysUncertOptions.h" // kFRjt_*

#include <TFile.h>             // TFile
#include <TString.h>           // TString
#include <TGraphAsymmErrors.h> // TGraphAsymmErrors
#include <TF1.h>               // TF1

#include <boost/algorithm/string/replace.hpp> // boost::replace_all_copy()

namespace
{
  std::string
  getEtaHadTauSelectionName(const std::string & pattern,
                            const std::string & etaBin,
                            const std::string & hadTauSelection)
  {
    return boost::replace_all_copy(
      boost::replace_all_copy(pattern,
         "$etaBin",          etaBin
      ), "$hadTauSelection", hadTauSelection
    );
  }

  TGraphAsymmErrors *
  loadGraph(TFile * inputFile,
            const std::string & graphName,
            const std::string & etaBin,
            const std::string & hadTauSelection)
  {
    const std::string graphName_etaBin = getEtaHadTauSelectionName(graphName, etaBin, hadTauSelection);
    const TGraphAsymmErrors * const graph = dynamic_cast<const TGraphAsymmErrors * const>(
      inputFile->Get(graphName_etaBin.data())
    );
    if(! graph)
    {
      throw cmsException(__func__, __LINE__)
        << "Failed to load graph = " << graphName_etaBin << " from file = " << inputFile->GetName();
    }
    TGraphAsymmErrors * graph_cloned = static_cast<TGraphAsymmErrors *>(graph->Clone());
    return graph_cloned;
  }

  TF1 *
  loadFitFunction(TFile * inputFile,
                  const std::string & fitFunctionName,
                  const std::string & etaBin,
                  const std::string & hadTauSelection)
  {
    const std::string fitFunctionName_etaBin = getEtaHadTauSelectionName(fitFunctionName, etaBin, hadTauSelection);
    const TF1 * const fitFunction = dynamic_cast<const TF1 * const>(inputFile->Get(fitFunctionName_etaBin.data()));
    if(! fitFunction)
    {
      throw cmsException(__func__, __LINE__)
        << "Failed to load fitFunction = " << fitFunctionName_etaBin << " from file = " << inputFile->GetName();
    }
    TF1 * fitFunction_cloned = static_cast<TF1 *>(fitFunction->Clone());
    return fitFunction_cloned;
  }
}

JetToTauFakeRateWeightEntry::JetToTauFakeRateWeightEntry(double absEtaMin,
                                                         double absEtaMax,
                                                         const std::string & hadTauSelection,
                                                         TFile * inputFile,
                                                         const edm::ParameterSet & cfg,
                                                         const std::string& trigMatching,
                                                         int central_or_shift)
  : absEtaMin_(absEtaMin)
  , absEtaMax_(absEtaMax)
  , hadTauSelection_(hadTauSelection)
  , graph_(nullptr)
  , applyGraph_(cfg.getParameter<bool>("applyGraph"))
  , fitFunction_(nullptr)
  , applyFitFunction_(cfg.getParameter<bool>("applyFitFunction"))
{
  const std::string etaBin = getEtaBin(absEtaMin_, absEtaMax_);
  TString graphName = cfg.getParameter<std::string>("graphName").data();
  graphName.ReplaceAll("jetToTauFakeRate/", Form("jetToTauFakeRate_%s/", trigMatching.data()));
  graphName_ = graphName.Data();
  graph_ = loadGraph(inputFile, graphName_, etaBin, hadTauSelection_);

  TString fitFunctionName = cfg.getParameter<std::string>("fitFunctionName").data();
  fitFunctionName.ReplaceAll("jetToTauFakeRate/", Form("jetToTauFakeRate_%s/", trigMatching.data()));
  switch(central_or_shift)
  {
    case kFRjt_central:   fitFunctionName_ = fitFunctionName.Data();                      break;
    case kFRjt_normUp:    fitFunctionName_ = Form("%s_par1Up",   fitFunctionName.Data()); break;
    case kFRjt_normDown:  fitFunctionName_ = Form("%s_par1Down", fitFunctionName.Data()); break;
    case kFRjt_shapeUp:   fitFunctionName_ = Form("%s_par2Up",   fitFunctionName.Data()); break;
    case kFRjt_shapeDown: fitFunctionName_ = Form("%s_par2Down", fitFunctionName.Data()); break;
    default: throw cmsException(this)
               << "Invalid Configuration parameter 'central_or_shift' = " << central_or_shift;
  }
  fitFunction_ = loadFitFunction(inputFile, fitFunctionName_, etaBin, hadTauSelection_);
}

JetToTauFakeRateWeightEntry::~JetToTauFakeRateWeightEntry()
{
  delete graph_;
  delete fitFunction_;
}

double
JetToTauFakeRateWeightEntry::absEtaMin() const
{
  return absEtaMin_;
}

double
JetToTauFakeRateWeightEntry::absEtaMax() const
{
  return absEtaMax_;
}

double
JetToTauFakeRateWeightEntry::getWeight(double pt) const
{
  double weight = 1.;
  if(applyGraph_)
  {
    weight *= graph_->Eval(pt);
  }
  if(applyFitFunction_)
  {
    weight *= fitFunction_->Eval(pt);
  }
  weight = std::max(weight, 0.);
  return weight;
}

double
JetToTauFakeRateWeightEntry::getSF(double pt) const
{
  double sf = 1.;
  if(applyFitFunction_)
  {
    sf *= fitFunction_->Eval(pt);
  }
  sf = std::max(sf, 0.);
  return sf;
}
