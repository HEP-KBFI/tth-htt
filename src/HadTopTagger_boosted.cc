#include "tthAnalysis/HiggsToTauTau/interface/HadTopTagger_boosted.h" // HadTopTagger_boosted

//#include "tthAnalysis/HiggsToTauTau/interface/HadTopKinFit.h" // HadTopKinFit
#include "tthAnalysis/HiggsToTauTau/interface/TMVAInterface.h" // TMVAInterface
#include "tthAnalysis/HiggsToTauTau/interface/XGBInterface.h" // XGBInterface
#include "tthAnalysis/HiggsToTauTau/interface/Particle.h" // Particle
#include "tthAnalysis/HiggsToTauTau/interface/hadTopTaggerAuxFunctions_internal.h" // isGenMatchedJetTriplet
#include "tthAnalysis/HiggsToTauTau/interface/hadTopTaggerAuxFunctions_geral.h" // kGenTop...
#include "DataFormats/Math/interface/deltaR.h" // deltaR
#include <TLorentzVector.h> // TLorentzVector


HadTopTagger_boosted::HadTopTagger_boosted(void)
  : mva_xgb_HTT_highestCSV_(nullptr)
{

  std::string mvaFileNameHTT_highestCSV = "tthAnalysis/HiggsToTauTau/data/BDTs_2017MC_postPAS/HTT_HadTopTagger_2017_nomasscut_nvar13_boosted.xml";

  mvaInputsHTTSort =  {
    "tau32Top", "btagDisc_b",
    "m_Wj1Wj2_div_m_bWj1Wj2", "pT_Wj1Wj2", "dR_Wj1Wj2", "m_bWj1Wj2", "pT_bWj1Wj2", "m_bWj2",
    "mass_Wj1", "pT_Wj2", "mass_Wj2",
    "pT_b", "mass_b"
  };
  mva_xgb_HTT_highestCSV_ = new TMVAInterface(
    mvaFileNameHTT_highestCSV, mvaInputsHTTSort
  );
  mva_xgb_HTT_highestCSV_->enableBDTTransform();

}

HadTopTagger_boosted::~HadTopTagger_boosted()
{
  //delete kinFit_;
  delete mva_xgb_HTT_highestCSV_;
}

std::map<int, double>
HadTopTagger_boosted::operator()(
  const RecoJetHTTv2 & jet_HTTv2,
  bool & calculate_matching, bool & isGenMatched,
  double & genTopPt,
  std::map<int, Particle::LorentzVector> genVar, std::map<int, Particle::LorentzVector> genVarAnti
)
{
  std::map<int, double> result = {
    { kXGB_boosted_no_kinFit,  0. }
  };

  Particle::LorentzVector recBJet, recWJet1, recWJet2 ;
  const RecoSubjetHTTv2* recSubJet[3];
  recSubJet[0] = jet_HTTv2.subJet1();
  recSubJet[1] = jet_HTTv2.subJet2();
  recSubJet[2] = jet_HTTv2.subJet3();
  std::vector<double> btag_disc = {recSubJet[0]->BtagCSV(), recSubJet[1]->BtagCSV(), recSubJet[2]->BtagCSV()};
  auto btag_order = sort_indexes(btag_disc);
  recBJet = recSubJet[btag_order[0]]->p4();
  recWJet1 = recSubJet[btag_order[1]]->p4();
  recWJet2 = recSubJet[btag_order[2]]->p4();

  double m_bWj1Wj2 = jet_HTTv2.p4().mass();
  double  m_Wj1Wj2 = (recWJet1 + recWJet2).mass();

  if ( calculate_matching ) {
    int typeTop = 1;
    std::map<int, bool> genMatchingTop = isGenMatchedJetTriplet(
      recBJet, recWJet1, recWJet2,
      genVar[kGenTop], genVar[kGenTopB], genVar[kGenTopW], genVar[kGenTopWj1], genVar[kGenTopWj2],
      kGenTop, typeTop, jet_HTTv2.p4()
    );
    std::map<int, bool> genMatchingAntiTop = isGenMatchedJetTriplet(
      recBJet, recWJet1, recWJet2,
      genVarAnti[kGenTop], genVarAnti[kGenTopB], genVarAnti[kGenTopW], genVarAnti[kGenTopWj1], genVarAnti[kGenTopWj2],
      kGenAntiTop, typeTop, jet_HTTv2.p4()
    );
    if(genMatchingTop[kGenMatchedTriplet]) { genTopPt = genVar[kGenTop].pt();}
    if(genMatchingAntiTop[kGenMatchedTriplet]) { genTopPt = genVarAnti[kGenTop].pt();}

    isGenMatched = (genMatchingTop[kGenMatchedTriplet] || genMatchingAntiTop[kGenMatchedTriplet]);
    //fatjet_isGenMatched = (genMatchingTop[kGenMatchedFatJet] || genMatchingAntiTop[kGenMatchedFatJet]);
  } // close gen matching

  mvaInputsHTT["tau32Top"]           = jet_HTTv2.tau3()/jet_HTTv2.tau2();
  mvaInputsHTT["btagDisc_b"]         = recSubJet[btag_order[0]]->BtagCSV();
  mvaInputsHTT["m_Wj1Wj2_div_m_bWj1Wj2"]  = m_Wj1Wj2/m_bWj1Wj2;
  mvaInputsHTT["pT_Wj1Wj2"]          = (recWJet1 + recWJet2).pt();
  mvaInputsHTT["dR_Wj1Wj2"]          = deltaR(recWJet1,recWJet2);
  mvaInputsHTT["m_bWj1Wj2"]          = jet_HTTv2.p4().mass();
  mvaInputsHTT["pT_bWj1Wj2"]          = jet_HTTv2.p4().pt();
  mvaInputsHTT["m_bWj2"]             = (recBJet + recWJet2).mass();
  mvaInputsHTT["mass_Wj1"]           = recWJet1.mass();
  mvaInputsHTT["pT_Wj2"]             = recWJet2.pt();
  mvaInputsHTT["mass_Wj2"]           = recWJet2.mass();
  mvaInputsHTT["pT_b"]               = recBJet.pt();
  mvaInputsHTT["mass_b"]             = recBJet.mass();
  const double HTT_highestCSV = (*mva_xgb_HTT_highestCSV_)(mvaInputsHTT);
  result[kXGB_boosted_no_kinFit] = HTT_highestCSV;
  //std::cout << "boosted HTT_highestCSV " << HTT_highestCSV << " " << jet_HTTv2.tau3()/jet_HTTv2.tau2() << std::endl;

  return result;
}

const std::map<std::string, double> &
HadTopTagger_boosted::mvaInputs() const
{
  return mvaInputsHTT;
}

//const HadTopKinFit *
//HadTopTagger_boosted::kinFit() const
//{
//  return kinFit_;
//}
