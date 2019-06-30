#include "tthAnalysis/HiggsToTauTau/interface/HadTopTaggerFill.h" // HadTopTagger

#include "tthAnalysis/HiggsToTauTau/interface/HadTopKinFit.h" // HadTopKinFit
#include "tthAnalysis/HiggsToTauTau/interface/MVAInputVarHistManager.h" // MVAInputVarHistManager

#include <DataFormats/Math/interface/deltaR.h> // deltaR()

#include <TLorentzVector.h> // TLorentzVector

HadTopTaggerFill::HadTopTaggerFill()
  : kinFit_(new HadTopKinFit())
{}

HadTopTaggerFill::~HadTopTaggerFill()
{
  delete kinFit_;
}

void
HadTopTaggerFill::operator()(const Particle::LorentzVector & recBJet,
                             const Particle::LorentzVector & recWJet1,
                             const Particle::LorentzVector & recWJet2)
{
	mvaInputs_.clear();
  const Particle::LorentzVector p4_bWj1Wj2 = recBJet + recWJet1 + recWJet2;
  const Particle::LorentzVector p4_Wj1Wj2  = recWJet1 + recWJet2;

  mvaInputs_["m_bWj1Wj2"]              = p4_bWj1Wj2.mass();
  mvaInputs_["m_Wj1Wj2"]               = p4_Wj1Wj2.mass();
  mvaInputs_["m_bWj1"]                 = (recBJet + recWJet1).mass();
  mvaInputs_["m_bWj2"]                 = (recBJet + recWJet2).mass();
  mvaInputs_["m_Wj1Wj2_div_m_bWj1Wj2"] = p4_bWj1Wj2.mass() > 0. ? p4_Wj1Wj2.mass() / p4_bWj1Wj2.mass() : -1.;
  mvaInputs_["pT_b"]                   = recBJet.pt();
  mvaInputs_["eta_b"]                  = abs(recBJet.eta());
  mvaInputs_["pT_Wj1"]                 = recWJet1.pt();
  mvaInputs_["eta_Wj1"]                = abs(recWJet1.eta());
  mvaInputs_["pT_Wj2"]                 = recWJet2.pt();
  mvaInputs_["eta_Wj2"]                = abs(recWJet2.eta());
  mvaInputs_["dR_bWj1"]                = deltaR(recBJet, recWJet1);
  mvaInputs_["dR_bWj2"]                = deltaR(recBJet, recWJet2);
  mvaInputs_["dR_Wj1Wj2"]              = deltaR(recWJet1, recWJet2);
  mvaInputs_["dR_bW"]                  = deltaR(recBJet, p4_Wj1Wj2);

  kinFit_->fit(recBJet, recWJet1, recWJet2);

  mvaInputs_["statusKinFit"]           = kinFit_->fit_status();
  mvaInputs_["nllKinFit"]              = kinFit_->nll();
  mvaInputs_["alphaKinFit"]            = kinFit_->alpha();

  mvaInputs_["kinFit_pT_b"]            = kinFit_->fittedBJet().pt();
  mvaInputs_["kinFit_pT_Wj1"]          = kinFit_->fittedWJet1().pt();
  mvaInputs_["kinFit_pT_Wj2"]          = kinFit_->fittedWJet2().pt();

//--- star angle computation
  TLorentzVector PWj1, PWj2;
  PWj1.SetPtEtaPhiM(recWJet1.pt(), recWJet1.eta(), recWJet1.phi(), recWJet1.mass());
  PWj2.SetPtEtaPhiM(recWJet2.pt(), recWJet2.eta(), recWJet2.phi(), recWJet2.mass());
  const TLorentzVector PW = PWj1 + PWj2;

  TLorentzVector Pb;
  Pb.SetPtEtaPhiM(recBJet.pt(), recBJet.eta(), recBJet.phi(), recBJet.mass());
  const TLorentzVector Ptop = PW + Pb;

  TLorentzVector PWboost, Pbboost;
  PWboost = PW;
  Pbboost = Pb;
  PWboost.Boost(-Ptop.BoostVector());
  Pbboost.Boost(-Ptop.BoostVector());

  TLorentzVector PWj1boost;
  PWj1boost = PWj1;
  PWj1boost.Boost(-PW.BoostVector());

  TLorentzVector PWj1boostTop, PWj2boostTop;
  PWj1boostTop=PWj1;
  PWj1boostTop.Boost(-Ptop.BoostVector());
  PWj2boostTop=PWj2;
  PWj2boostTop.Boost(-Ptop.BoostVector());

  double leadingCostS_Wj_top    = -100;
  double subleadingCostS_Wj_top = -100;
  if(PWj1boostTop.Pt() > PWj2boostTop.Pt())
  {
    leadingCostS_Wj_top    = PWj1boostTop.CosTheta();
    subleadingCostS_Wj_top = PWj2boostTop.CosTheta();
  }
  else
  {
    leadingCostS_Wj_top    = PWj2boostTop.CosTheta();
    subleadingCostS_Wj_top = PWj1boostTop.CosTheta();
  }

  double leadingECostS_Wj_top    = -100;
  double subleadingECostS_Wj_top = -100;
  if(PWj1boostTop.E() > PWj2boostTop.E())
  {
    leadingECostS_Wj_top    = PWj1boostTop.CosTheta();
    subleadingECostS_Wj_top = PWj2boostTop.CosTheta();
  }
  else
  {
    leadingECostS_Wj_top    = PWj2boostTop.CosTheta();
    subleadingECostS_Wj_top = PWj1boostTop.CosTheta();
  }

//---
  TLorentzVector kinFit_PWj1, kinFit_PWj2;
  const Particle::LorentzVector & kinFit_WJet1 = kinFit_->fittedWJet1();
  const Particle::LorentzVector & kinFit_WJet2 = kinFit_->fittedWJet2();
  kinFit_PWj1.SetPtEtaPhiM(kinFit_WJet1.pt(), kinFit_WJet1.eta(), kinFit_WJet1.phi(), kinFit_WJet1.mass());
  kinFit_PWj2.SetPtEtaPhiM(kinFit_WJet2.pt(), kinFit_WJet2.eta(), kinFit_WJet2.phi(), kinFit_WJet2.mass());
  const TLorentzVector kinFit_PW = kinFit_PWj1 + kinFit_PWj2;

  TLorentzVector kinFit_Pb;
  const Particle::LorentzVector & kinFit_BJet = kinFit_->fittedBJet();
  kinFit_Pb.SetPtEtaPhiM(kinFit_BJet.pt(), kinFit_BJet.eta(), kinFit_BJet.phi(), kinFit_BJet.mass());
  const TLorentzVector kinFit_Ptop = kinFit_PW + kinFit_Pb;

  TLorentzVector kinFit_PWboost, kinFit_Pbboost;
  kinFit_PWboost = kinFit_PW;
  kinFit_Pbboost = kinFit_Pb;
  kinFit_PWboost.Boost(-kinFit_Ptop.BoostVector());
  kinFit_Pbboost.Boost(-kinFit_Ptop.BoostVector());

  TLorentzVector kinFit_PWj1boost;
  kinFit_PWj1boost = kinFit_PWj1;
  kinFit_PWj1boost.Boost(-kinFit_PW.BoostVector());

  TLorentzVector kinFit_PWj1boostTop, kinFit_PWj2boostTop;
  kinFit_PWj1boostTop = kinFit_PWj1;
  kinFit_PWj1boostTop.Boost(-kinFit_Ptop.BoostVector());
  kinFit_PWj2boostTop = kinFit_PWj2;
  kinFit_PWj2boostTop.Boost(-kinFit_Ptop.BoostVector());

  double kinFit_leadingCostS_Wj_top    = -100;
  double kinFit_subleadingCostS_Wj_top = -100;
  if(kinFit_PWj1boostTop.Pt() > kinFit_PWj2boostTop.Pt())
  {
    kinFit_leadingCostS_Wj_top    = kinFit_PWj1boostTop.CosTheta();
    kinFit_subleadingCostS_Wj_top = kinFit_PWj2boostTop.CosTheta();
  }
  else
  {
    kinFit_leadingCostS_Wj_top    = kinFit_PWj2boostTop.CosTheta();
    kinFit_subleadingCostS_Wj_top = kinFit_PWj1boostTop.CosTheta();
  }

  mvaInputs_["cosTheta_leadWj_restTop"]        = leadingCostS_Wj_top;
  mvaInputs_["cosTheta_subleadWj_restTop"]     = subleadingCostS_Wj_top;
  mvaInputs_["cosTheta_Kin_leadWj_restTop"]    = kinFit_leadingCostS_Wj_top;
  mvaInputs_["cosTheta_Kin_subleadWj_restTop"] = kinFit_subleadingCostS_Wj_top;

  double kinFit_leadingECostS_Wj_top    = -100;
  double kinFit_subleadingECostS_Wj_top = -100;
  if(kinFit_PWj1boostTop.E() > kinFit_PWj2boostTop.E())
  {
    kinFit_leadingECostS_Wj_top    = kinFit_PWj1boostTop.CosTheta();
    kinFit_subleadingECostS_Wj_top = kinFit_PWj2boostTop.CosTheta();
  }
  else
  {
    kinFit_leadingECostS_Wj_top    = kinFit_PWj2boostTop.CosTheta();
    kinFit_subleadingECostS_Wj_top = kinFit_PWj1boostTop.CosTheta();
  }

  mvaInputs_["cosTheta_leadEWj_restTop"]        = leadingECostS_Wj_top;
  mvaInputs_["cosTheta_subleadEWj_restTop"]     = subleadingECostS_Wj_top;
  mvaInputs_["cosTheta_Kin_leadEWj_restTop"]    = kinFit_leadingECostS_Wj_top;
  mvaInputs_["cosTheta_Kin_subleadEWj_restTop"] = kinFit_subleadingECostS_Wj_top;

  mvaInputs_["cosThetaW_rest"]    = PWboost.CosTheta();
  mvaInputs_["cosThetaKinW_rest"] = kinFit_PWboost.CosTheta();
  mvaInputs_["cosThetaW_lab"]     = PW.CosTheta();
  mvaInputs_["cosThetaKinW_lab"]  = kinFit_PW.CosTheta();

  mvaInputs_["cosThetab_rest"]    = Pbboost.CosTheta();
  mvaInputs_["cosThetaKinb_rest"] = kinFit_Pbboost.CosTheta();
  mvaInputs_["cosThetab_lab"]     = Pb.CosTheta();
  mvaInputs_["cosThetaKinb_lab"]  = kinFit_Pb.CosTheta();

  mvaInputs_["Dphi_Wj1_Wj2_lab"]       = PWj1.DeltaPhi(PWj2);
  mvaInputs_["Dphi_KinWj1_KinWj2_lab"] = kinFit_PWj1.DeltaPhi(kinFit_PWj2);

  mvaInputs_["Dphi_Wb_rest"]    = Pbboost.DeltaPhi(PWboost);
  mvaInputs_["Dphi_KinWb_rest"] = kinFit_Pbboost.DeltaPhi(kinFit_PWboost);
  mvaInputs_["Dphi_Wb_lab"]     = Pb.DeltaPhi(PW);
  mvaInputs_["Dphi_KinWb_lab"]  = kinFit_Pb.DeltaPhi(kinFit_PW);

  mvaInputs_["cosThetaWj1_restW"]   = PWj1boost.CosTheta();
  mvaInputs_["cosThetaKinWj_restW"] = kinFit_PWj1boost.CosTheta();

  mvaInputs_["pT_bWj1Wj2"]         = p4_bWj1Wj2.pt();
  mvaInputs_["pT_Wj1Wj2"]          = p4_Wj1Wj2.pt();
}

const std::vector<std::string> &
HadTopTaggerFill::defineBinnings(MVAInputVarHistManager * mvaInputHistManager)
{
  MVAInputVarHistManagerWrapper wrapper(this, mvaInputHistManager);

  wrapper.defineBinning("m_bWj1Wj2",              100, 0., 1.e+3);
  wrapper.defineBinning("m_Wj1Wj2",               100, 0., 1.e+3);
  wrapper.defineBinning("m_bWj1",                 100, 0., 1.e+3);
  wrapper.defineBinning("m_bWj2",                 100, 0., 1.e+3);
  wrapper.defineBinning("m_Wj1Wj2_div_m_bWj1Wj2", 100, 0., 1.);
  wrapper.defineBinning("CSV_b",                  100, 0., 1.);

  return mvaInputVariables_;
}

const std::map<std::string, double> &
HadTopTaggerFill::mvaInputs() const
{
  return mvaInputs_;
}

const HadTopKinFit *
HadTopTaggerFill::kinFit() const
{
  return kinFit_;
}

HadTopTaggerFill::MVAInputVarHistManagerWrapper::MVAInputVarHistManagerWrapper(HadTopTaggerFill * outer,
                                                                               MVAInputVarHistManager * mvaInputHistManager)
  : outer_(outer)
  , mvaInputHistManager_(mvaInputHistManager)
{}

void
HadTopTaggerFill::MVAInputVarHistManagerWrapper::defineBinning(const std::string & histogramName,
                                                               int numBinsX,
                                                               double xMin,
                                                               double xMax)
{
  mvaInputHistManager_->defineBinningOption(histogramName, numBinsX, xMin, xMax);
  outer_->mvaInputVariables_.push_back(histogramName);
}
