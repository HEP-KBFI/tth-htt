#include "tthAnalysis/HiggsToTauTau/interface/HadTopTagger.h" // HadTopTagger

#include "tthAnalysis/HiggsToTauTau/interface/HadTopKinFit.h" // HadTopKinFit
#include "tthAnalysis/HiggsToTauTau/interface/TMVAInterface.h" // TMVAInterface
#include "tthAnalysis/HiggsToTauTau/interface/Particle.h" // Particle
#include "tthAnalysis/HiggsToTauTau/interface/hadTopTaggerAuxFunctions_internal.h" // isGenMatchedJetTriplet
#include "tthAnalysis/HiggsToTauTau/interface/hadTopTaggerAuxFunctions_geral.h" // kGenTop...
#include "DataFormats/Math/interface/deltaR.h" // deltaR

#include <TLorentzVector.h> // TLorentzVector

HadTopTagger::HadTopTagger(void)
  : mva_xgb_HTT_CSVsort4rd_(nullptr)
  , mva_hadTopTagger_multilep_(nullptr)
{

  std::string mvaFileNameHTT_multilep = "tthAnalysis/HiggsToTauTau/data/multilep_BDTs_2018/resTop_xgb_csv_order_qgl.xml";
  std::string mvaFileNameHTT_CSVsort4rd = "tthAnalysis/HiggsToTauTau/data/BDTs_2017MC_postPAS/HTT_HadTopTagger_2017_nomasscut_nvar17_resolved.xml";

  mvaInputsHTT_multilepSort =  {
    "var_b_pt", "var_b_mass", "var_b_csv",
    "var_wj1_pt", "var_wj1_mass", "var_wj1_csv", "var_wj1_qgl",
    "var_wj2_pt", "var_wj2_mass", "var_wj2_csv", "var_wj2_qgl",
    "var_b_wj1_deltaR", "var_b_wj1_mass", "var_b_wj2_deltaR",
    "var_b_wj2_mass", "var_wcand_deltaR", "var_wcand_mass", "var_b_wcand_deltaR", "var_topcand_mass"
  };
  mva_hadTopTagger_multilep_ = new TMVAInterface(
    mvaFileNameHTT_multilep, mvaInputsHTT_multilepSort
  );

  mvaInputsHTTSort =  {
    "btagDisc_b", "btagDisc_Wj1", "btagDisc_Wj2", "qg_Wj1", "qg_Wj2",
    "m_Wj1Wj2_div_m_bWj1Wj2", "pT_Wj1Wj2", "dR_Wj1Wj2", "m_bWj1Wj2", "dR_bW", "m_bWj1", "m_bWj2",
    "mass_Wj1", "pT_Wj2", "mass_Wj2", "pT_b", "mass_b"
  };
  mva_xgb_HTT_CSVsort4rd_ = new TMVAInterface(
    mvaFileNameHTT_CSVsort4rd, mvaInputsHTTSort
  );
  mva_xgb_HTT_CSVsort4rd_->enableBDTTransform();
}

HadTopTagger::~HadTopTagger()
{
  delete mva_hadTopTagger_multilep_;
  delete mva_xgb_HTT_CSVsort4rd_;
}

std::map<int, double>
HadTopTagger::operator()(const RecoJet & recBJet,
                         const RecoJet & recWJet1,
                         const RecoJet & recWJet2,
                         bool & calculate_matching, bool & isGenMatched,
                         double & genTopPt,
                         std::map<int, Particle::LorentzVector> genVar, std::map<int, Particle::LorentzVector> genVarAnti,
                         bool massCut = true
                       )
{
  std::map<int, double> result = {
    { kXGB_multilep,  -1. },
    { kXGB_CSVsort4rd,  0. },
  };

  const Particle::LorentzVector p4_bWj1Wj2 = recBJet.p4() + recWJet1.p4() + recWJet2.p4();
  const Particle::LorentzVector p4_Wj1Wj2  = recWJet1.p4() + recWJet2.p4();

  if ( calculate_matching ) {
    // calculate matching
    std::map<int, bool> genMatchingTop = isGenMatchedJetTriplet(
      recBJet.p4(), recWJet1.p4(), recWJet2.p4(),
      genVar[kGenTop], genVar[kGenTopB], genVar[kGenTopW], genVar[kGenTopWj1], genVar[kGenTopWj2],
      kGenTop
    );
    std::map<int, bool> genMatchingAntiTop = isGenMatchedJetTriplet(
      recBJet.p4(), recWJet1.p4(), recWJet2.p4(),
      genVarAnti[kGenTop], genVarAnti[kGenTopB], genVarAnti[kGenTopW], genVarAnti[kGenTopWj1], genVarAnti[kGenTopWj2],
      kGenAntiTop
    );
    if(genMatchingTop[kGenMatchedTriplet]) { genTopPt = genVar[kGenTop].pt(); }
    if(genMatchingAntiTop[kGenMatchedTriplet]) { genTopPt = genVarAnti[kGenTop].pt(); }
    isGenMatched = (genMatchingTop[kGenMatchedTriplet] || genMatchingAntiTop[kGenMatchedTriplet]);
  }

  mvaInputsHTT["btagDisc_b"]         = recBJet.BtagCSV();
  mvaInputsHTT["btagDisc_Wj1"]       = recWJet1.BtagCSV();
  mvaInputsHTT["btagDisc_Wj2"]       = recWJet2.BtagCSV();
  mvaInputsHTT["qg_Wj1"]             = recWJet2.QGDiscr();
  mvaInputsHTT["qg_Wj2"]             = recWJet2.QGDiscr();
  mvaInputsHTT["m_Wj1Wj2_div_m_bWj1Wj2"]  = p4_Wj1Wj2.mass()/p4_bWj1Wj2.mass();
  mvaInputsHTT["pT_Wj1Wj2"]          = p4_Wj1Wj2.pt();
  mvaInputsHTT["dR_Wj1Wj2"]          = deltaR(recWJet1.p4(),recWJet2.p4());
  mvaInputsHTT["m_bWj1Wj2"]          = p4_bWj1Wj2.mass();
  mvaInputsHTT["dR_bW"]              = deltaR(recBJet.p4(), recWJet1.p4()+recWJet2.p4());
  mvaInputsHTT["m_bWj1"]            = deltaR(recBJet.p4(), recWJet1.p4());
  mvaInputsHTT["m_bWj2"]            = deltaR(recBJet.p4(), recWJet2.p4());
  mvaInputsHTT["mass_Wj1"]           = recWJet1.mass();
  mvaInputsHTT["pT_Wj2"]             = recWJet2.pt();
  mvaInputsHTT["mass_Wj2"]           = recWJet2.mass();
  mvaInputsHTT["pT_b"]               = recBJet.pt();
  mvaInputsHTT["mass_b"]             = recBJet.mass();
  const double HTT_CSVsort4rd = (*mva_xgb_HTT_CSVsort4rd_)(mvaInputsHTT);
  result[kXGB_CSVsort4rd] = HTT_CSVsort4rd;
  //std::cout << " HTT_CSVsort4rd " << HTT_CSVsort4rd << std::endl;

  if ( massCut && !(p4_bWj1Wj2.mass() > 75. && p4_bWj1Wj2.mass() < 275.)) {
    result[kXGB_multilep] = -1.;
  } else {
    ///*
    mvaInputsHTT_multilep["var_b_pt"]             = recBJet.pt();
    mvaInputsHTT_multilep["var_b_mass"]           = recBJet.p4().mass();
    mvaInputsHTT_multilep["var_b_csv"]            = recBJet.BtagCSV();
    mvaInputsHTT_multilep["var_wj1_pt"]           = recWJet1.pt();
    mvaInputsHTT_multilep["var_wj1_mass"]         = recWJet1.p4().mass();
    mvaInputsHTT_multilep["var_wj1_csv"]          = recWJet1.BtagCSV();
    mvaInputsHTT_multilep["var_wj1_qgl"]          = recWJet1.QGDiscr();
    mvaInputsHTT_multilep["var_wj2_pt"]           = recWJet2.pt();
    mvaInputsHTT_multilep["var_wj2_mass"]         = recWJet2.p4().mass();
    mvaInputsHTT_multilep["var_wj2_csv"]          = recWJet2.BtagCSV();
    mvaInputsHTT_multilep["var_wj2_qgl"]          = recWJet2.QGDiscr();
    mvaInputsHTT_multilep["var_b_wj1_deltaR"]     = deltaR(recBJet.p4(), recWJet1.p4());
    mvaInputsHTT_multilep["var_b_wj1_mass"]       = (recBJet.p4()+recWJet1.p4()).mass();
    mvaInputsHTT_multilep["var_b_wj2_deltaR"]     = deltaR(recBJet.p4(), recWJet2.p4());
    mvaInputsHTT_multilep["var_b_wj2_mass"]       = (recBJet.p4()+recWJet2.p4()).mass();
    mvaInputsHTT_multilep["var_wcand_deltaR"]     = deltaR(recWJet2.p4(), recWJet1.p4());
    mvaInputsHTT_multilep["var_wcand_mass"]       = (recWJet2.p4()+recWJet1.p4()).mass();
    mvaInputsHTT_multilep["var_b_wcand_deltaR"]   = deltaR(recBJet.p4(), recWJet1.p4()+recWJet2.p4());
    mvaInputsHTT_multilep["var_topcand_mass"]     = (recBJet.p4()+ recWJet1.p4()+recWJet2.p4()).mass();
    const double HTT_multilep = (*mva_hadTopTagger_multilep_)(mvaInputsHTT_multilep);
    result[kXGB_multilep] = HTT_multilep;
    //std::cout << " HTT_multilep " << HTT_multilep << std::endl;
  }

  return result;
}

const std::map<std::string, double> &
HadTopTagger::mvaInputs() const
{
  return mvaInputsHTT;
}
