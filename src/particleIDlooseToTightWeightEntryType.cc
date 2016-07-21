#include "tthAnalysis/HiggsToTauTau/interface/particleIDlooseToTightWeightEntryType.h"

#include "FWCore/Utilities/interface/Exception.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h"

namespace
{
  TF1* loadFitFunction(TFile* inputFile, const std::string& fitFunctionName, const std::string& particleEtaBin_label)
  {
    std::string fitFunctionName_particleEtaBin = TString(fitFunctionName.data()).ReplaceAll("$particleEtaBin", particleEtaBin_label.data()).Data();
    TF1* fitFunction = dynamic_cast<TF1*>(inputFile->Get(fitFunctionName_particleEtaBin.data()));
    if ( !fitFunction ) throw cms::Exception("analyze_1l_2tau") 
      << "Failed to load fitFunction = " << fitFunctionName_particleEtaBin << " from file = " << inputFile->GetName() << " !!\n";
    TF1* fitFunction_cloned = (TF1*)fitFunction->Clone();
    return fitFunction_cloned;
  }
  TGraphAsymmErrors* loadGraph(TFile* inputFile, const std::string& graphName, const std::string& particleEtaBin_label)
  {
    std::string graphName_particleEtaBin = TString(graphName.data()).ReplaceAll("$particleEtaBin", particleEtaBin_label.data()).Data();
    TGraphAsymmErrors* graph = dynamic_cast<TGraphAsymmErrors*>(inputFile->Get(graphName_particleEtaBin.data()));
    if ( !graph ) throw cms::Exception("FWLiteTauTauAnalyzer") 
      << "Failed to load graph = " << graphName_particleEtaBin << " from file = " << inputFile->GetName() << " !!\n";
    TGraphAsymmErrors* graph_cloned = (TGraphAsymmErrors*)graph->Clone();
    return graph_cloned;
  }

  enum { kCentral, kShiftUp, kShiftDown };

  TGraphAsymmErrors* getGraphErr(TGraphAsymmErrors* graph_central, int central_or_shift)
  {
    int numPoints = graph_central->GetN();
    TGraphAsymmErrors* graph_shift = new TGraphAsymmErrors(numPoints);
    for ( int iPoint = 0; iPoint < numPoints; ++iPoint ) {
      double x, y;
      graph_central->GetPoint(iPoint, x, y);
      double xErrUp = graph_central->GetErrorXhigh(iPoint);
      double xErrDown = graph_central->GetErrorXlow(iPoint);
      double yErrUp = graph_central->GetErrorYhigh(iPoint);
      double yErrDown = graph_central->GetErrorYlow(iPoint);
      if ( central_or_shift == kShiftUp   ) y += yErrUp;
      if ( central_or_shift == kShiftDown ) y -= yErrDown;
      graph_shift->SetPoint(iPoint, x, y);
      graph_shift->SetPointError(iPoint, xErrDown, xErrUp, yErrDown, yErrUp);
    }
    return graph_shift;
  }

  double square(double x)
  {
    return x*x;
  }

  std::string getParticleEtaLabel(const std::string& particleType, double particle1EtaMin, double particle1EtaMax, double particle2EtaMin, double particle2EtaMax)
  {
    std::string particleEtaBin_label = "";
    if ( particle1EtaMin > 0. && particle1EtaMax < 5. ) {
      particleEtaBin_label.append(Form("%s1Eta%1.1fto%1.1f", particleType.data(), particle1EtaMin, particle1EtaMax));
    } else if ( particle1EtaMin > 0. ) {
      particleEtaBin_label.append(Form("%s1EtaGt%1.1f", particleType.data(), particle1EtaMin));
    } else if ( particle1EtaMax < 5. ) {
      particleEtaBin_label.append(Form("%s1EtaLt%1.1f", particleType.data(), particle1EtaMax));
    }
    if ( particle2EtaMin > 0. && particle2EtaMax < 5. ) {
      particleEtaBin_label.append(Form("%s2Eta%1.1fto%1.1f", particleType.data(), particle2EtaMin, particle2EtaMax));
    } else if ( particle2EtaMin > 0. ) {
      particleEtaBin_label.append(Form("%s2EtaGt%1.1f", particleType.data(), particle2EtaMin));
    } else if ( particle2EtaMax < 5. ) {
      particleEtaBin_label.append(Form("%s2EtaLt%1.1f", particleType.data(), particle2EtaMax));
    }
    particleEtaBin_label = TString(particleEtaBin_label).ReplaceAll(".", "").Data();
    return particleEtaBin_label;
  }
}

particleIDlooseToTightWeightEntryType::particleIDlooseToTightWeightEntryType(
  TFile* inputFile, 
  const std::string& particleType, double particle1EtaMin, double particle1EtaMax, 
  const std::string& fitFunctionNormName, 
  const std::string& graphShapeName_particle1, const std::string& fitFunctionShapeName_particle1_central, const std::string& fitFunctionShapeName_particle1_shift, 
  bool applyFitFunction_or_graph_tau1, double fitFunctionShapePower_particle1)
  : particle1EtaMin_(particle1EtaMin),
    particle1EtaMax_(particle1EtaMax),
    particle2EtaMin_(-1.),
    particle2EtaMax_(9.9),
    norm_(0),
    graphShapeCorr_particle1_(0),
    graphShapeCorrErrUp_particle1_(0),
    graphShapeCorrErrDown_particle1_(0),
    fitFunctionShapeCorr_particle1_central_(0),
    fitFunctionShapeCorr_particle1_shift_(0),
    shapeCorrPow_particle1_(fitFunctionShapePower_particle1),	
    applyFitFunction_or_graph_tau1_(applyFitFunction_or_graph_tau1),
    graphShapeCorr_particle2_(0),
    graphShapeCorrErrUp_particle2_(0),
    graphShapeCorrErrDown_particle2_(0),
    fitFunctionShapeCorr_particle2_central_(0),
    fitFunctionShapeCorr_particle2_shift_(0),
    shapeCorrPow_particle2_(0.),
    applyFitFunction_or_graph_tau2_(false)
{
  std::string particleEtaBin_label = getParticleEtaLabel(particleType, particle1EtaMin_, particle1EtaMax_, particle2EtaMin_, particle2EtaMax_);

  norm_ = loadFitFunction(inputFile, fitFunctionNormName, particleEtaBin_label);

  if ( applyFitFunction_or_graph_tau1_ == kGraph ) {
    graphShapeCorr_particle1_ = loadGraph(inputFile, graphShapeName_particle1, particleEtaBin_label);
    graphShapeCorrErrUp_particle1_ = getGraphErr(graphShapeCorr_particle1_, kShiftUp);
    graphShapeCorrErrDown_particle1_ = getGraphErr(graphShapeCorr_particle1_, kShiftDown);
    fitFunctionShapeCorr_particle1_central_ = loadFitFunction(inputFile, fitFunctionShapeName_particle1_central, particleEtaBin_label);
    if ( fitFunctionShapeName_particle1_shift != "" ) { 
      fitFunctionShapeCorr_particle1_shift_ = loadFitFunction(inputFile, fitFunctionShapeName_particle1_shift, particleEtaBin_label);
    }
  } else if ( applyFitFunction_or_graph_tau1_ == kFitFunction ) {
    fitFunctionShapeCorr_particle1_central_ = loadFitFunction(inputFile, fitFunctionShapeName_particle1_central, particleEtaBin_label);
  }
}

particleIDlooseToTightWeightEntryType::particleIDlooseToTightWeightEntryType(
  TFile* inputFile, 
  const std::string& particleType, double particle1EtaMin, double particle1EtaMax, double particle2EtaMin, double particle2EtaMax,
  const std::string& fitFunctionNormName, 
  const std::string& graphShapeName_particle1, const std::string& fitFunctionShapeName_particle1_central, const std::string& fitFunctionShapeName_particle1_shift, 
  bool applyFitFunction_or_graph_tau1, double fitFunctionShapePower_particle1, 
  const std::string& graphShapeName_particle2, const std::string& fitFunctionShapeName_particle2_central, const std::string& fitFunctionShapeName_particle2_shift, 
  bool applyFitFunction_or_graph_tau2, double fitFunctionShapePower_particle2)
  : particle1EtaMin_(particle1EtaMin),
    particle1EtaMax_(particle1EtaMax),
    particle2EtaMin_(particle2EtaMin),
    particle2EtaMax_(particle2EtaMax),
    norm_(0),
    graphShapeCorr_particle1_(0),
    graphShapeCorrErrUp_particle1_(0),
    graphShapeCorrErrDown_particle1_(0),
    fitFunctionShapeCorr_particle1_central_(0),
    fitFunctionShapeCorr_particle1_shift_(0),
    shapeCorrPow_particle1_(fitFunctionShapePower_particle1),
    applyFitFunction_or_graph_tau1_(applyFitFunction_or_graph_tau1),
    graphShapeCorr_particle2_(0),
    graphShapeCorrErrUp_particle2_(0),
    graphShapeCorrErrDown_particle2_(0),
    fitFunctionShapeCorr_particle2_central_(0),
    fitFunctionShapeCorr_particle2_shift_(0),
    shapeCorrPow_particle2_(fitFunctionShapePower_particle2),
    applyFitFunction_or_graph_tau2_(applyFitFunction_or_graph_tau2)
{
  std::string particleEtaBin_label = getParticleEtaLabel(particleType, particle1EtaMin_, particle1EtaMax_, particle2EtaMin_, particle2EtaMax_);

  norm_ = loadFitFunction(inputFile, fitFunctionNormName, particleEtaBin_label);

  if ( applyFitFunction_or_graph_tau1_ == kGraph ) {
    graphShapeCorr_particle1_ = loadGraph(inputFile, graphShapeName_particle1, particleEtaBin_label);
    graphShapeCorrErrUp_particle1_ = getGraphErr(graphShapeCorr_particle1_, kShiftUp);
    graphShapeCorrErrDown_particle1_ = getGraphErr(graphShapeCorr_particle1_, kShiftDown);
    fitFunctionShapeCorr_particle1_central_ = loadFitFunction(inputFile, fitFunctionShapeName_particle1_central, particleEtaBin_label);
    if ( fitFunctionShapeName_particle1_shift != "" ) { 
      fitFunctionShapeCorr_particle1_shift_ = loadFitFunction(inputFile, fitFunctionShapeName_particle1_shift, particleEtaBin_label);
    }
  } else if ( applyFitFunction_or_graph_tau1_ == kFitFunction ) {
    fitFunctionShapeCorr_particle1_central_ = loadFitFunction(inputFile, fitFunctionShapeName_particle1_central, particleEtaBin_label);
  }
  if ( applyFitFunction_or_graph_tau2_ == kGraph ) {
    graphShapeCorr_particle2_ = loadGraph(inputFile, graphShapeName_particle2, particleEtaBin_label);
    graphShapeCorrErrUp_particle2_ = getGraphErr(graphShapeCorr_particle2_, kShiftUp);
    graphShapeCorrErrDown_particle2_ = getGraphErr(graphShapeCorr_particle2_, kShiftDown);
    fitFunctionShapeCorr_particle2_central_ = loadFitFunction(inputFile, fitFunctionShapeName_particle2_central, particleEtaBin_label);
    if ( fitFunctionShapeName_particle2_shift != "" ) { 
      fitFunctionShapeCorr_particle2_shift_ = loadFitFunction(inputFile, fitFunctionShapeName_particle2_shift, particleEtaBin_label);
    }
  } else if ( applyFitFunction_or_graph_tau2_ == kFitFunction ) {
    fitFunctionShapeCorr_particle2_central_ = loadFitFunction(inputFile, fitFunctionShapeName_particle2_central, particleEtaBin_label);
  }
}

particleIDlooseToTightWeightEntryType::~particleIDlooseToTightWeightEntryType()
{
  delete norm_;
  delete graphShapeCorr_particle1_;
  delete graphShapeCorrErrUp_particle1_;
  delete graphShapeCorrErrDown_particle1_;
  delete fitFunctionShapeCorr_particle1_central_;
  delete fitFunctionShapeCorr_particle1_shift_;
  delete graphShapeCorr_particle2_;
  delete graphShapeCorrErrUp_particle2_;
  delete graphShapeCorrErrDown_particle2_;
  delete fitFunctionShapeCorr_particle2_central_;
  delete fitFunctionShapeCorr_particle2_shift_;
}

double particleIDlooseToTightWeightEntryType::weight(double particle1Pt) const
{
  //std::cout << "<particleIDlooseToTightWeightEntryType::weight>:" << std::endl;
  double weight = norm_->Eval(1.);
  //std::cout << " norm = " << norm_->Eval(1.) << std::endl;
  double shapeCorr_particle1 = 1.;
  if ( applyFitFunction_or_graph_tau1_ == kGraph ) {
    assert(graphShapeCorr_particle1_);
    shapeCorr_particle1 = graphShapeCorr_particle1_->Eval(particle1Pt);
    if ( fitFunctionShapeCorr_particle1_central_ && fitFunctionShapeCorr_particle1_shift_ ) {
      double shapeCorr_particle1_central = fitFunctionShapeCorr_particle1_central_->Eval(particle1Pt);
      double shapeCorr_particle1_shift = fitFunctionShapeCorr_particle1_shift_->Eval(particle1Pt);
      if ( shapeCorr_particle1_central > 0. ) shapeCorr_particle1 *= (shapeCorr_particle1_shift/shapeCorr_particle1_central);
    }
  } else if ( applyFitFunction_or_graph_tau1_ == kFitFunction ) {
    assert(fitFunctionShapeCorr_particle1_central_);
    shapeCorr_particle1 = fitFunctionShapeCorr_particle1_central_->Eval(particle1Pt);
    //std::cout << " shape(tau1) = " << fitFunctionShapeCorr_particle1_central_->Eval(particle1Pt) << std::endl;
  }
  weight *= TMath::Power(TMath::Max(0., shapeCorr_particle1), shapeCorrPow_particle1_);
  if ( weight < 0.    ) weight = 0.;
  if ( weight > 1.e+1 ) weight = 1.e+1; // CV: ratio anti-iso/iso can indeed be greater than 1.0 in case anti-iso sideband is very "narrow"
  return weight;
}

double particleIDlooseToTightWeightEntryType::weightErr_relative(double particle1Pt) const
{
  double weightErr_relative = 0.;
  if ( applyFitFunction_or_graph_tau1_ == kGraph ) {
    assert(graphShapeCorr_particle1_);
    double shapeCorr_particle1 = graphShapeCorr_particle1_->Eval(particle1Pt);
    if ( shapeCorr_particle1 > 0. ) {
      double shapeCorrErrUp_particle1 = graphShapeCorrErrUp_particle1_->Eval(particle1Pt);
      double shapeCorrErrDown_particle1 = graphShapeCorrErrDown_particle1_->Eval(particle1Pt);
      weightErr_relative += TMath::Sqrt(0.5*(square(shapeCorrErrUp_particle1 - shapeCorr_particle1) + square(shapeCorr_particle1 - shapeCorrErrDown_particle1)))/shapeCorr_particle1;      
      }
  }
  return weightErr_relative;
}

double particleIDlooseToTightWeightEntryType::weight(double particle1Pt, double particle2Pt) const
{
  //std::cout << "<particleIDlooseToTightWeightEntryType::weight>:" << std::endl;
  double weight = norm_->Eval(1.);
  //std::cout << " norm = " << norm_->Eval(1.) << std::endl;
  double shapeCorr_particle1 = 1.;
  if ( applyFitFunction_or_graph_tau1_ == kGraph ) {
    assert(graphShapeCorr_particle1_);
    shapeCorr_particle1 = graphShapeCorr_particle1_->Eval(particle1Pt);
    if ( fitFunctionShapeCorr_particle1_central_ && fitFunctionShapeCorr_particle1_shift_ ) {
      double shapeCorr_particle1_central = fitFunctionShapeCorr_particle1_central_->Eval(particle1Pt);
      double shapeCorr_particle1_shift = fitFunctionShapeCorr_particle1_shift_->Eval(particle1Pt);
      if ( shapeCorr_particle1_central > 0. ) shapeCorr_particle1 *= (shapeCorr_particle1_shift/shapeCorr_particle1_central);
    }
  } else if ( applyFitFunction_or_graph_tau1_ == kFitFunction ) {
    assert(fitFunctionShapeCorr_particle1_central_);
    shapeCorr_particle1 = fitFunctionShapeCorr_particle1_central_->Eval(particle1Pt);
    //std::cout << " shape(tau1) = " << fitFunctionShapeCorr_particle1_central_->Eval(particle1Pt) << std::endl;
  }
  weight *= TMath::Power(TMath::Max(0., shapeCorr_particle1), shapeCorrPow_particle1_);
  double shapeCorr_particle2 = 1.;
  if ( applyFitFunction_or_graph_tau2_ == kGraph ) {
    assert(graphShapeCorr_particle2_);
    shapeCorr_particle2 = graphShapeCorr_particle2_->Eval(particle2Pt);
    if ( fitFunctionShapeCorr_particle2_central_ && fitFunctionShapeCorr_particle2_shift_ ) {
      double shapeCorr_particle2_central = fitFunctionShapeCorr_particle2_central_->Eval(particle2Pt);
      double shapeCorr_particle2_shift = fitFunctionShapeCorr_particle2_shift_->Eval(particle2Pt);
      if ( shapeCorr_particle2_central > 0. ) shapeCorr_particle2 *= (shapeCorr_particle2_shift/shapeCorr_particle2_central);
    }
  } else if ( applyFitFunction_or_graph_tau2_ == kFitFunction ) {
    assert(fitFunctionShapeCorr_particle2_central_);
    shapeCorr_particle2 = fitFunctionShapeCorr_particle2_central_->Eval(particle2Pt);
    //std::cout << " shape(tau2) = " << fitFunctionShapeCorr_particle2_central_->Eval(particle2Pt) << std::endl;
  }
  weight *= TMath::Power(TMath::Max(0., shapeCorr_particle2), shapeCorrPow_particle2_);
  if ( weight < 0.    ) weight = 0.;
  if ( weight > 1.e+1 ) weight = 1.e+1; // CV: ratio anti-iso/iso can indeed be greater than 1.0 in case anti-iso sideband is very "narrow"
  return weight;
}

double particleIDlooseToTightWeightEntryType::weightErr_relative(double particle1Pt, double particle2Pt) const
{
  double weightErr_relative = 0.;
  if ( applyFitFunction_or_graph_tau1_ == kGraph ) {
    assert(graphShapeCorr_particle1_);
    double shapeCorr_particle1 = graphShapeCorr_particle1_->Eval(particle1Pt);
    if ( shapeCorr_particle1 > 0. ) {
      double shapeCorrErrUp_particle1 = graphShapeCorrErrUp_particle1_->Eval(particle1Pt);
      double shapeCorrErrDown_particle1 = graphShapeCorrErrDown_particle1_->Eval(particle1Pt);
      weightErr_relative += TMath::Sqrt(0.5*(square(shapeCorrErrUp_particle1 - shapeCorr_particle1) + square(shapeCorr_particle1 - shapeCorrErrDown_particle1)))/shapeCorr_particle1;      
      }
  }
  if ( applyFitFunction_or_graph_tau2_ == kGraph ) {
    assert(graphShapeCorr_particle2_);
    double shapeCorr_particle2 = graphShapeCorr_particle2_->Eval(particle2Pt);
    if ( shapeCorr_particle2 > 0. ) {
      double shapeCorrErrUp_particle2 = graphShapeCorrErrUp_particle2_->Eval(particle2Pt);
      double shapeCorrErrDown_particle2 = graphShapeCorrErrDown_particle2_->Eval(particle2Pt);
      weightErr_relative += TMath::Sqrt(0.5*(square(shapeCorrErrUp_particle2 - shapeCorr_particle2) + square(shapeCorr_particle2 - shapeCorrErrDown_particle2)))/shapeCorr_particle2;      
    }
  }
  return weightErr_relative;
}


