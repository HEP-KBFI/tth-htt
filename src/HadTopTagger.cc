#include "tthAnalysis/HiggsToTauTau/interface/HadTopTagger.h" // HadTopTagger

#include "tthAnalysis/HiggsToTauTau/interface/HadTopKinFit.h" // HadTopKinFit
#include "tthAnalysis/HiggsToTauTau/interface/TMVAInterface.h" // TMVAInterface

HadTopTagger::HadTopTagger(const std::string & mvaFileNameWithKinFit)
  : kinFit_(new HadTopKinFit())
  , mva_hadTopTagger_xgb_withKinFit_(nullptr)
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
}

HadTopTagger::~HadTopTagger()
{
  delete kinFit_;
  delete mva_hadTopTagger_xgb_withKinFit_;
}

std::map<int, double>
HadTopTagger::operator()(const RecoJet & recBJet,
                         const RecoJet & recWJet1,
                         const RecoJet & recWJet2)
{
  std::map<int, double> result = {
    { kXGB_with_kinFit,  -1. }
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
