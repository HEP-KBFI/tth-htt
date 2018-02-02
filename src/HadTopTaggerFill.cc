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


double
HadTopTaggerFill::operator()(const RecoJet & recBJet,
                             const RecoJet & recWJet1,
                             const RecoJet & recWJet2)
{
  const Particle::LorentzVector p4_bWj1Wj2 = recBJet.p4() + recWJet1.p4() + recWJet2.p4();
  const Particle::LorentzVector p4_Wj1Wj2  = recWJet1.p4() + recWJet2.p4();

  const double dR_bWj1   = deltaR(recBJet.p4(), recWJet1.p4());
  const double dR_bWj2   = deltaR(recBJet.p4(), recWJet2.p4());
  const double dR_Wj1Wj2 = deltaR(recWJet1.p4(), recWJet2.p4());

  mvaInputs_["m_bWj1Wj2"]              = p4_bWj1Wj2.mass();
  mvaInputs_["m_Wj1Wj2"]               = p4_Wj1Wj2.mass();
  mvaInputs_["m_bWj1"]                 = (recBJet.p4() + recWJet1.p4()).mass();
  mvaInputs_["m_bWj2"]                 = (recBJet.p4() + recWJet2.p4()).mass();
  mvaInputs_["m_Wj1Wj2_div_m_bWj1Wj2"] = p4_bWj1Wj2.mass() > 0. ? p4_Wj1Wj2.mass() / p4_bWj1Wj2.mass() : -1.;
  mvaInputs_["CSV_b"]                  = recBJet.BtagCSV();
  mvaInputs_["CSV_Wj1"]                = recWJet1.BtagCSV();
  mvaInputs_["CSV_Wj2"]                = recWJet2.BtagCSV();
  mvaInputs_["pT_b"]                   = recBJet.pt();
  mvaInputs_["eta_b"]                  = recBJet.eta();
  mvaInputs_["phi_b"]                  = recBJet.phi();
  mvaInputs_["mass_b"]                 = recBJet.mass();
  mvaInputs_["pT_Wj1"]                 = recWJet1.pt();
  mvaInputs_["eta_Wj1"]                = recWJet1.eta();
  mvaInputs_["phi_Wj1"]                = recWJet1.phi();
  mvaInputs_["mass_Wj1"]               = recWJet1.mass();
  mvaInputs_["pT_Wj2"]                 = recWJet2.pt();
  mvaInputs_["eta_Wj2"]                = recWJet2.eta();
  mvaInputs_["phi_Wj2"]                = recWJet2.phi();
  mvaInputs_["mass_Wj2"]               = recWJet2.mass();
  mvaInputs_["dR_bWj1"]                = dR_bWj1;
  mvaInputs_["dR_bWj2"]                = dR_bWj2;
  mvaInputs_["dR_Wj1Wj2"]              = dR_Wj1Wj2;
  mvaInputs_["dR_bW"]                  = deltaR(recBJet.p4(), p4_Wj1Wj2);

  kinFit_->fit(recBJet.p4(), recWJet1.p4(), recWJet2.p4());

  mvaInputs_["statusKinFit"]           = kinFit_->fit_status();
  mvaInputs_["nllKinFit"]              = kinFit_->nll();
  mvaInputs_["alphaKinFit"]            = kinFit_->alpha();

  mvaInputs_["kinFit_pT_b"]            = kinFit_->fittedBJet().pt();
  mvaInputs_["kinFit_eta_b"]           = kinFit_->fittedBJet().eta();
  mvaInputs_["kinFit_phi_b"]           = kinFit_->fittedBJet().phi();
  mvaInputs_["kinFit_mass_b"]          = kinFit_->fittedBJet().mass();
  mvaInputs_["kinFit_pT_Wj1"]          = kinFit_->fittedWJet1().pt();
  mvaInputs_["kinFit_eta_Wj1"]         = kinFit_->fittedWJet1().eta();
  mvaInputs_["kinFit_phi_Wj1"]         = kinFit_->fittedWJet1().phi();
  mvaInputs_["kinFit_mass_Wj1"]        = kinFit_->fittedWJet1().mass();
  mvaInputs_["kinFit_pT_Wj2"]          = kinFit_->fittedWJet2().pt();
  mvaInputs_["kinFit_eta_Wj2"]         = kinFit_->fittedWJet2().eta();
  mvaInputs_["kinFit_phi_Wj2"]         = kinFit_->fittedWJet2().phi();
  mvaInputs_["kinFit_mass_Wj2"]        = kinFit_->fittedWJet2().mass();

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

  kinFit_->integrate(recBJet.p4(), recWJet1.p4(), recWJet2.p4());
  mvaInputs_["logPKinFit"]         = kinFit_->p()    > 0. ? std::log(kinFit_->p())    : -1.e+3;
  mvaInputs_["logPErrKinFit"]      = kinFit_->pErr() > 0. ? std::log(kinFit_->pErr()) : -1.e+3;
  mvaInputs_["qg_b"]               = recBJet.QGDiscr();
  mvaInputs_["qg_Wj1"]             = recWJet1.QGDiscr();
  mvaInputs_["qg_Wj2"]             = recWJet2.QGDiscr();
  mvaInputs_["pT_bWj1Wj2"]         = p4_bWj1Wj2.pt();
  mvaInputs_["pT_Wj1Wj2"]          = p4_Wj1Wj2.pt();
  mvaInputs_["max_dR_div_expRjet"] = 1.0;
#if 0
  const double expRjet = p4_bWj1Wj2.pt() > 0. ? 327. / p4_bWj1Wj2.pt() : -1.;
  mvaInputs_["max_dR_div_expRjet"]     = std::max({dR_bWj1, dR_bWj2, dR_Wj1Wj2}) / expRjet;
#endif

  return 0;
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
  wrapper.defineBinning("CSV_Wj1",                100, 0., 1.);
  wrapper.defineBinning("CSV_Wj2",                100, 0., 1.);

  wrapper.defineBinning("pT_b",   100, 0., 5.e+2);
  wrapper.defineBinning("pT_Wj1", 100, 0., 5.e+2);
  wrapper.defineBinning("pT_Wj2", 100, 0., 5.e+2);

  wrapper.defineBinning("eta_b",   100, -5., 5.);
  wrapper.defineBinning("eta_Wj1", 100, -5., 5.);
  wrapper.defineBinning("eta_Wj2", 100, -5., 5.);

  wrapper.defineBinning("phi_b",   100, -5., 5.);
  wrapper.defineBinning("phi_Wj1", 100, -5., 5.);
  wrapper.defineBinning("phi_Wj2", 100, -5., 5.);

  wrapper.defineBinning("mass_b",   100, 0., 5.e+2);
  wrapper.defineBinning("mass_Wj1", 100, 0., 5.e+2);
  wrapper.defineBinning("mass_Wj2", 100, 0., 5.e+2);

  wrapper.defineBinning("kinFit_pT_b",   100, 0., 5.e+2);
  wrapper.defineBinning("kinFit_pT_Wj1", 100, 0., 5.e+2);
  wrapper.defineBinning("kinFit_pT_Wj2", 100, 0., 5.e+2);

  wrapper.defineBinning("kinFit_eta_b",   100, -5., 5.);
  wrapper.defineBinning("kinFit_eta_Wj1", 100, -5., 5.);
  wrapper.defineBinning("kinFit_eta_Wj2", 100, -5., 5.);

  wrapper.defineBinning("kinFit_phi_b",   100, -5., 5.);
  wrapper.defineBinning("kinFit_phi_Wj1", 100, -5., 5.);
  wrapper.defineBinning("kinFit_phi_Wj2", 100, -5., 5.);

  wrapper.defineBinning("kinFit_mass_b",   100, 0., 5.e+2);
  wrapper.defineBinning("kinFit_mass_Wj1", 100, 0., 5.e+2);
  wrapper.defineBinning("kinFit_mass_Wj2", 100, 0., 5.e+2);

  wrapper.defineBinning("cosTheta_leadWj_restTop",        100, -1., 1.);
  wrapper.defineBinning("cosTheta_subleadWj_restTop",     100, -1., 1.);
  wrapper.defineBinning("cosTheta_Kin_leadWj_restTop",    100, -1., 1.);
  wrapper.defineBinning("cosTheta_Kin_subleadWj_restTop", 100, -1., 1.);

  wrapper.defineBinning("cosTheta_leadEWj_restTop",        100, -1., 1.);
  wrapper.defineBinning("cosTheta_subleadEWj_restTop",     100, -1., 1.);
  wrapper.defineBinning("cosTheta_Kin_leadEWj_restTop",    100, -1., 1.);
  wrapper.defineBinning("cosTheta_Kin_subleadEWj_restTop", 100, -1., 1.);

  wrapper.defineBinning("cosThetaW_rest",    100, -1., 1.);
  wrapper.defineBinning("cosThetaKinW_rest", 100, -1., 1.);
  wrapper.defineBinning("cosThetaW_lab",     100, -1., 1.);
  wrapper.defineBinning("cosThetaKinW_lab",  100, -1., 1.);

  wrapper.defineBinning("cosThetab_rest",    100, -1., 1.);
  wrapper.defineBinning("cosThetaKinb_rest", 100, -1., 1.);
  wrapper.defineBinning("cosThetab_lab",     100, -1., 1.);
  wrapper.defineBinning("cosThetaKinb_lab",  100, -1., 1.);


  wrapper.defineBinning("Dphi_Wj1_Wj2_lab",       100, -5., 5.);
  wrapper.defineBinning("Dphi_KinWj1_KinWj2_lab", 100, -5., 5.);

  wrapper.defineBinning("Dphi_Wb_rest",    100, -5., 5.);
  wrapper.defineBinning("Dphi_KinWb_rest", 100, -5., 5.);
  wrapper.defineBinning("Dphi_Wb_lab",     100, -5., 5.);
  wrapper.defineBinning("Dphi_KinWb_lab",  100, -5., 5.);

  wrapper.defineBinning("cosThetaWj1_restW",   100, -1., 1.);
  wrapper.defineBinning("cosThetaKinWj_restW", 100, -1., 1.);

  wrapper.defineBinning("dR_bWj1",            100,   0.,  5.);
  wrapper.defineBinning("dR_bWj2",            100,   0.,  5.);
  wrapper.defineBinning("dR_Wj1Wj2",          100,   0.,  5.);
  wrapper.defineBinning("dR_bW",              100,   0.,  5.);
  wrapper.defineBinning("statusKinFit",         6,  -1., +5.);
  wrapper.defineBinning("nllKinFit",          150, -10., +5.);
  wrapper.defineBinning("alphaKinFit",        200,   0.,  2.);
  wrapper.defineBinning("logPKinFit",         150, -10., +5.);
  wrapper.defineBinning("logPErrKinFit",      250, -20., +5.);
  wrapper.defineBinning("qg_b",               100,   0.,  1.);
  wrapper.defineBinning("qg_Wj1",             100,   0.,  1.);
  wrapper.defineBinning("qg_Wj2",             100,   0.,  1.);
  wrapper.defineBinning("pT_bWj1Wj2",         100,   0.,  5.e+2);
  wrapper.defineBinning("pT_Wj1Wj2",          100,   0.,  5.e+2);
  wrapper.defineBinning("max_dR_div_expRjet", 200,   0.,  2.);

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
