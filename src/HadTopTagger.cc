#include "tthAnalysis/HiggsToTauTau/interface/HadTopTagger.h" // HadTopTagger

#include "FWCore/Utilities/interface/Exception.h" // cms::Exception

#include "tthAnalysis/HiggsToTauTau/interface/Particle.h" // Particle::LorentzVector
#include "tthAnalysis/HiggsToTauTau/interface/mvaAuxFunctions.h" // check_mvaInputs

HadTopTagger::HadTopTagger(const std::string& mvaFileName)
  : kinFit_(0),
    mva_(0),
    mvaOutput_(-1.)
{
  kinFit_ = new HadTopKinFit();

  mvaInputVariables_.push_back("m_bWj1Wj2");
  mvaInputVariables_.push_back("m_Wj1Wj2");
  mvaInputVariables_.push_back("m_bWj1");
  mvaInputVariables_.push_back("m_bWj2");
  mvaInputVariables_.push_back("m_Wj1Wj2_div_m_bWj1Wj2");
  mvaInputVariables_.push_back("CSV_b");
  mvaInputVariables_.push_back("CSV_Wj1");
  mvaInputVariables_.push_back("CSV_Wj2");
  mvaInputVariables_.push_back("pT_b");
  mvaInputVariables_.push_back("pT_Wj1");
  mvaInputVariables_.push_back("pT_Wj2");
  mvaInputVariables_.push_back("dR_bWj1");
  mvaInputVariables_.push_back("dR_bWj2");
  mvaInputVariables_.push_back("dR_Wj1Wj2");
  mvaInputVariables_.push_back("dR_bW");
  mvaInputVariables_.push_back("nllKinFit");
  mvaInputVariables_.push_back("alphaKinFit");
  mvaInputVariables_.push_back("logPKinFit");
  mvaInputVariables_.push_back("logPErrKinFit");
  mvaInputVariables_.push_back("qg_b");
  mvaInputVariables_.push_back("qg_Wj1");
  mvaInputVariables_.push_back("qg_Wj2");
  mvaInputVariables_.push_back("pT_bWj1Wj2");
  mvaInputVariables_.push_back("pT_Wj1Wj2");
  mvaInputVariables_.push_back("max_dR_div_expRjet");
  if ( mvaFileName != "" ) {
    mva_ = new TMVAInterface(mvaFileName, mvaInputVariables_, {});
  }
}

HadTopTagger::~HadTopTagger()
{
  delete kinFit_;
  delete mva_;
}

namespace
{
  double max(double value1, double value2, double value3)
  {
    double max12 = std::max(value1, value2);
    return std::max(max12, value3);
  } 
}

double HadTopTagger::operator()(const RecoJet& recBJet, const RecoJet& recWJet1, const RecoJet& recWJet2)
{
  Particle::LorentzVector p4_bWj1Wj2 = recBJet.p4() + recWJet1.p4() + recWJet2.p4();
  mvaInputs_["m_bWj1Wj2"]              = p4_bWj1Wj2.mass();
  Particle::LorentzVector p4_Wj1Wj2 = recWJet1.p4() + recWJet2.p4();
  mvaInputs_["m_Wj1Wj2"]               = p4_Wj1Wj2.mass();
  mvaInputs_["m_bWj1"]                 = (recBJet.p4() + recWJet1.p4()).mass();
  mvaInputs_["m_bWj2"]                 = (recBJet.p4() + recWJet2.p4()).mass();
  mvaInputs_["m_Wj1Wj2_div_m_bWj1Wj2"] = ( p4_bWj1Wj2.mass() > 0. ) ? p4_Wj1Wj2.mass()/p4_bWj1Wj2.mass() : -1.;
  mvaInputs_["CSV_b"]                  = recBJet.BtagCSV();
  mvaInputs_["CSV_Wj1"]                = recWJet1.BtagCSV();
  mvaInputs_["CSV_Wj2"]                = recWJet2.BtagCSV();
  mvaInputs_["pT_b"]                   = recBJet.pt();
  mvaInputs_["pT_Wj1"]                 = recWJet1.pt();
  mvaInputs_["pT_Wj2"]                 = recWJet2.pt(); 
  double dR_bWj1 = deltaR(recBJet.p4(), recWJet1.p4());
  mvaInputs_["dR_bWj1"]                = dR_bWj1;
  double dR_bWj2 = deltaR(recBJet.p4(), recWJet2.p4());
  mvaInputs_["dR_bWj2"]                = dR_bWj2;
  double dR_Wj1Wj2 = deltaR(recWJet1.p4(), recWJet2.p4());
  mvaInputs_["dR_Wj1Wj2"]              = dR_Wj1Wj2;
  mvaInputs_["dR_bW"]                  = deltaR(recBJet.p4(), p4_Wj1Wj2);
  kinFit_->fit(recBJet.p4(), recWJet1.p4(), recWJet2.p4());
  mvaInputs_["statusKinFit"]           = kinFit_->fit_status();
  mvaInputs_["nllKinFit"]              = kinFit_->nll();
  mvaInputs_["alphaKinFit"]            = kinFit_->alpha();
  kinFit_->integrate(recBJet.p4(), recWJet1.p4(), recWJet2.p4());
  mvaInputs_["logPKinFit"]             = ( kinFit_->p()    > 0. ) ? log(kinFit_->p())    : -1.e+3;
  mvaInputs_["logPErrKinFit"]          = ( kinFit_->pErr() > 0. ) ? log(kinFit_->pErr()) : -1.e+3;
  mvaInputs_["qg_b"]                   = recBJet.QGDiscr();
  mvaInputs_["qg_Wj1"]                 = recWJet1.QGDiscr();
  mvaInputs_["qg_Wj2"]                 = recWJet2.QGDiscr();
  mvaInputs_["pT_bWj1Wj2"]             = p4_bWj1Wj2.pt();
  mvaInputs_["pT_Wj1Wj2"]              = p4_Wj1Wj2.pt();
  double expRjet = ( p4_bWj1Wj2.pt() > 0. ) ? 327./p4_bWj1Wj2.pt() : -1.;
  mvaInputs_["max_dR_div_expRjet"]     = max(dR_bWj1, dR_bWj2, dR_Wj1Wj2)/expRjet;
  if ( mva_ ) {
    check_mvaInputs(mvaInputs_);
    mvaOutput_ = (*mva_)(mvaInputs_);
  }
  return mvaOutput_;
}

const std::vector<std::string>& HadTopTagger::mvaInputVariables() const
{ 
  return mvaInputVariables_; 
}

const std::map<std::string, double>& HadTopTagger::mvaInputs() const
{ 
  return mvaInputs_; 
}

