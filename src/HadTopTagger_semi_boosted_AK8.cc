#include "tthAnalysis/HiggsToTauTau/interface/HadTopTagger_semi_boosted_AK8.h" // HadTopTagger_boosted
#include "tthAnalysis/HiggsToTauTau/interface/TMVAInterface.h" // TMVAInterface
#include "tthAnalysis/HiggsToTauTau/interface/Particle.h" // Particle
#include "tthAnalysis/HiggsToTauTau/interface/hadTopTaggerAuxFunctions_internal.h" // isGenMatchedJetTriplet
#include "tthAnalysis/HiggsToTauTau/interface/hadTopTaggerAuxFunctions_geral.h" // kGenTop...
#include "DataFormats/Math/interface/deltaR.h" // deltaR
#include <TLorentzVector.h> // TLorentzVector


HadTopTagger_semi_boosted_AK8::HadTopTagger_semi_boosted_AK8(void)
  : mva_xgb_HTT_AK8_(nullptr)
{

  std::string mvaFileNameHTT_CSVsort3rd = "tthAnalysis/HiggsToTauTau/data/BDTs_2017MC_postPAS/HTT_HadTopTagger_2017_nomasscut_nvar12_semi_boosted_AK8.xml";

  mvaInputsHTT_AK8Sort =  {
    "massW_SD", "tau21W", "btagDisc_b",
    "m_Wj1Wj2_div_m_bWj1Wj2", "dR_Wj1Wj2", "m_bWj1Wj2", "pT_bWj1Wj2", //"m_bWj2",
    "mass_Wj1", "pT_Wj2", "mass_Wj2", "pT_b", "mass_b"
  };
  mva_xgb_HTT_AK8_ = new TMVAInterface(
    mvaFileNameHTT_CSVsort3rd, mvaInputsHTT_AK8Sort
  );
  mva_xgb_HTT_AK8_->enableBDTTransform();

}

HadTopTagger_semi_boosted_AK8::~HadTopTagger_semi_boosted_AK8()
{
  delete mva_xgb_HTT_AK8_;
}

std::map<int, double>
HadTopTagger_semi_boosted_AK8::operator()(
  const RecoJetAK8 & jet_ptrsAK8, const RecoJet & b_jet_candidate,
  bool & calculate_matching, bool & isGenMatched,
  double & genTopPt,
  std::map<int, Particle::LorentzVector> genVar, std::map<int, Particle::LorentzVector> genVarAnti
)
{
  std::map<int, double> result = {
    { kXGB_semi_boosted_AK8_no_kinFit,  0. }
  };

  if ( !(jet_ptrsAK8.subJet1() && jet_ptrsAK8.subJet2()) ) {
    result[kXGB_semi_boosted_AK8_no_kinFit] = 0.;
    return result;
  }

  Particle::LorentzVector recBJet, recWJet1, recWJet2 ;
  recBJet = b_jet_candidate.p4();
  recWJet1 = jet_ptrsAK8.subJet1()->p4();
  recWJet2 = jet_ptrsAK8.subJet2()->p4();

  double m_bWj1Wj2 = (recWJet1 + recWJet2 + recBJet).mass();
  double  m_Wj1Wj2 = (recWJet1 + recWJet2).mass();

  if ( calculate_matching ) {
    int typeTop = 2;
    std::map<int, bool> genMatchingTop = isGenMatchedJetTriplet(
      recBJet, recWJet1, recWJet2,
      genVar[kGenTop], genVar[kGenTopB], genVar[kGenTopW], genVar[kGenTopWj1], genVar[kGenTopWj2],
      kGenTop, typeTop, jet_ptrsAK8.p4()
    );
    std::map<int, bool> genMatchingAntiTop = isGenMatchedJetTriplet(
      recBJet, recWJet1, recWJet2,
      genVarAnti[kGenTop], genVarAnti[kGenTopB], genVarAnti[kGenTopW], genVarAnti[kGenTopWj1], genVarAnti[kGenTopWj2],
      kGenAntiTop, typeTop, jet_ptrsAK8.p4()
    );
    if(genMatchingTop[kGenMatchedTriplet]) { genTopPt = genVar[kGenTop].pt();}
    if(genMatchingAntiTop[kGenMatchedTriplet]) { genTopPt = genVarAnti[kGenTop].pt();}

    isGenMatched = (genMatchingTop[kGenMatchedTriplet] || genMatchingAntiTop[kGenMatchedTriplet]);
    //fatjet_isGenMatched = (genMatchingTop[kGenMatchedFatJet] || genMatchingAntiTop[kGenMatchedFatJet]);
  } // close gen matching


  mvaInputsHTT_AK8["massW_SD"]           = jet_ptrsAK8.msoftdrop();
  mvaInputsHTT_AK8["tau21W"]           = jet_ptrsAK8.tau2()/jet_ptrsAK8.tau1();
  mvaInputsHTT_AK8["btagDisc_b"]         = b_jet_candidate.BtagCSV();
  mvaInputsHTT_AK8["m_Wj1Wj2_div_m_bWj1Wj2"]  = m_Wj1Wj2/m_bWj1Wj2;
  mvaInputsHTT_AK8["dR_Wj1Wj2"]          = deltaR(recWJet1, recWJet2);
  mvaInputsHTT_AK8["m_bWj1Wj2"]          = (recWJet1 + recWJet2 + recBJet).mass();
  mvaInputsHTT_AK8["pT_bWj1Wj2"]          = (recWJet1 + recWJet2 + recBJet).pt();
  mvaInputsHTT_AK8["mass_Wj1"]           = recWJet1.mass();
  mvaInputsHTT_AK8["pT_Wj2"]             = recWJet2.pt();
  mvaInputsHTT_AK8["mass_Wj2"]           = recWJet2.mass();
  mvaInputsHTT_AK8["pT_b"]               = recBJet.pt();
  mvaInputsHTT_AK8["mass_b"]             = recBJet.mass();
  const double HTT_CSVsort3rd = (*mva_xgb_HTT_AK8_)(mvaInputsHTT_AK8);
  result[kXGB_semi_boosted_AK8_no_kinFit] = HTT_CSVsort3rd;
  //std::cout << "semi-boosted HTT_CSVsort3rd " << HTT_CSVsort3rd << jet_ptrsAK8.tau2()/jet_ptrsAK8.tau1() << std::endl;
  return result;
}

const std::map<std::string, double> &
HadTopTagger_semi_boosted_AK8::mvaInputs() const
{
  return mvaInputsHTT_AK8;
}
