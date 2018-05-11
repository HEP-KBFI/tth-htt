#include "tthAnalysis/HiggsToTauTau/interface/HadTopTagger.h" // HadTopTagger

#include "tthAnalysis/HiggsToTauTau/interface/HadTopKinFit.h" // HadTopKinFit
#include "tthAnalysis/HiggsToTauTau/interface/TMVAInterface.h" // TMVAInterface
#include "tthAnalysis/HiggsToTauTau/interface/XGBInterface.h" // XGBInterface
#include <TLorentzVector.h> // TLorentzVector

HadTopTagger::HadTopTagger(
  const std::string & mvaFileNameWithKinFit,
  const std::string & mvaFileNameWithKinFitNew ,
  const std::string & mvaFileNameNoKinFit
)
  : kinFit_(new HadTopKinFit())
  , mva_hadTopTagger_xgb_withKinFit_(nullptr)
  , mva_hadTopTagger_xgb_withKinFitNew_(nullptr)
  , mva_hadTopTagger_xgb_NoKinFit_(nullptr)
{
  mvaInputsWithKinFitSort = {
    "CSV_b",
    "qg_Wj2",
    "pT_bWj1Wj2",
    "m_Wj1Wj2",
    "nllKinFit",
    "pT_b_o_kinFit_pT_b",
    "pT_Wj2"
  };
  mva_hadTopTagger_xgb_withKinFit_ = new TMVAInterface(
    mvaFileNameWithKinFit, mvaInputsWithKinFitSort
  );
  mva_hadTopTagger_xgb_withKinFit_->enableBDTTransform();

  ///*
  mvaInputsWithKinFitSortNew =  {
    "btagDisc", "qg_Wj1", "qg_Wj2",
    "cosThetaWj1_restW", "m_Wj1Wj2",
    "pT_Wj1", "pT_Wj2", "pT_bWj1Wj2", "nllKinFit"
  };
  mva_hadTopTagger_xgb_withKinFitNew_ = new XGBInterface(
    mvaFileNameWithKinFitNew, mvaInputsWithKinFitSortNew
  );
  //*/

  ///*
  mvaInputsNoKinFitSort =  {
    "btagDisc", "qg_Wj1", "qg_Wj2",
    "cosThetaWj1_restW", "m_Wj1Wj2",
    "pT_Wj1", "pT_Wj2", "pT_bWj1Wj2"
  };
  mva_hadTopTagger_xgb_NoKinFit_ = new XGBInterface(
    mvaFileNameNoKinFit, mvaInputsNoKinFitSort
  );
  //*/
}

HadTopTagger::~HadTopTagger()
{
  delete kinFit_;
  delete mva_hadTopTagger_xgb_withKinFit_;
  delete mva_hadTopTagger_xgb_withKinFitNew_;
  delete mva_hadTopTagger_xgb_NoKinFit_;
}

std::map<int, double>
HadTopTagger::operator()(const RecoJet & recBJet,
                         const RecoJet & recWJet1,
                         const RecoJet & recWJet2)
{
  std::map<int, double> result = {
    { kXGB_with_kinFit,  -1. },
    { kXGB_with_kinFitNew,  -1. },
    { kXGB_no_kinFit,  -1. },
  };

  const Particle::LorentzVector p4_bWj1Wj2 = recBJet.p4() + recWJet1.p4() + recWJet2.p4();
  const Particle::LorentzVector p4_Wj1Wj2  = recWJet1.p4() + recWJet2.p4();
  kinFit_->fit(recBJet.p4(), recWJet1.p4(), recWJet2.p4());

  mvaInputsWithKinFit["CSV_b"]              = recBJet.BtagCSV();
  mvaInputsWithKinFit["qg_Wj2"]             = recWJet2.QGDiscr();
  mvaInputsWithKinFit["pT_bWj1Wj2"]         = p4_bWj1Wj2.pt();
  mvaInputsWithKinFit["m_Wj1Wj2"]           = p4_Wj1Wj2.mass();
  mvaInputsWithKinFit["nllKinFit"]          = kinFit_->nll();
  mvaInputsWithKinFit["pT_b_o_kinFit_pT_b"] = recBJet.pt() / kinFit_->fittedBJet().pt();
  mvaInputsWithKinFit["pT_Wj2"]             = recWJet2.pt();
  const double HTT_WithKin_xgb = (*mva_hadTopTagger_xgb_withKinFit_)(mvaInputsWithKinFit);
  result[kXGB_with_kinFit] = HTT_WithKin_xgb;

  ///*
  mvaInputsWithKinFitNew["btagDisc"]           = recBJet.BtagCSV();
  mvaInputsWithKinFitNew["qg_Wj1"]             = recWJet2.QGDiscr();
  mvaInputsWithKinFitNew["qg_Wj2"]             = recWJet2.QGDiscr();
  TLorentzVector PWj1, PWj2;
  PWj1.SetPtEtaPhiM(recWJet1.pt(), recWJet1.eta(), recWJet1.phi(), recWJet1.mass());
  PWj2.SetPtEtaPhiM(recWJet2.pt(), recWJet2.eta(), recWJet2.phi(), recWJet2.mass());
  const TLorentzVector PW = PWj1 + PWj2;
  TLorentzVector PWj1boost = PWj1;
  PWj1boost.Boost(-PW.BoostVector());
  mvaInputsWithKinFitNew["cosThetaWj1_restW"]  = PWj1boost.CosTheta();
  mvaInputsWithKinFitNew["m_Wj1Wj2"]           = p4_Wj1Wj2.mass();
  mvaInputsWithKinFitNew["pT_Wj1"]             = recWJet1.pt();
  mvaInputsWithKinFitNew["pT_Wj2"]             = recWJet2.pt();
  mvaInputsWithKinFitNew["pT_bWj1Wj2"]         = p4_bWj1Wj2.pt();
  mvaInputsWithKinFitNew["nllKinFit"]          = kinFit_->nll();
  const double HTT_WithKin_xgbNew = (*mva_hadTopTagger_xgb_withKinFitNew_)(mvaInputsWithKinFitNew);
  result[kXGB_with_kinFitNew] = HTT_WithKin_xgbNew;
  //*/

  ///*
  mvaInputsNoKinFit["btagDisc"]           = recBJet.BtagCSV();
  mvaInputsNoKinFit["qg_Wj1"]             = recWJet2.QGDiscr();
  mvaInputsNoKinFit["qg_Wj2"]             = recWJet2.QGDiscr();
  mvaInputsNoKinFit["cosThetaWj1_restW"]  = PWj1boost.CosTheta();
  mvaInputsNoKinFit["m_Wj1Wj2"]           = p4_Wj1Wj2.mass();
  mvaInputsNoKinFit["pT_Wj1"]             = recWJet1.pt();
  mvaInputsNoKinFit["pT_Wj2"]             = recWJet2.pt();
  mvaInputsNoKinFit["pT_bWj1Wj2"]         = p4_bWj1Wj2.pt();
  const double HTT_NoKin_xgb = (*mva_hadTopTagger_xgb_NoKinFit_)(mvaInputsNoKinFit);
  result[kXGB_no_kinFit] = HTT_NoKin_xgb;
  //*/

  return result;
}

const std::map<std::string, double> &
HadTopTagger::mvaInputs() const
{
  return mvaInputsWithKinFit;
}

const HadTopKinFit *
HadTopTagger::kinFit() const
{
  return kinFit_;
}
