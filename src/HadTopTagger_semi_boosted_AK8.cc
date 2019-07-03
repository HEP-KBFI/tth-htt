#include "tthAnalysis/HiggsToTauTau/interface/HadTopTagger_semi_boosted_AK8.h" // HadTopTagger_boosted

#include "tthAnalysis/HiggsToTauTau/interface/TMVAInterface.h" // TMVAInterface
#include "tthAnalysis/HiggsToTauTau/interface/hadTopTaggerAuxFunctions_internal.h" // isGenMatchedJetTriplet()
#include "tthAnalysis/HiggsToTauTau/interface/hadTopTaggerAuxFunctions_geral.h" // kGen*

#include <DataFormats/Math/interface/deltaR.h> // deltaR()

HadTopTagger_semi_boosted_AK8::HadTopTagger_semi_boosted_AK8(void)
  : mva_xgb_HTT_AK8_(nullptr)
{
  const std::string mvaFileNameHTT_CSVsort3rd =
    "tthAnalysis/HiggsToTauTau/data/BDTs_2017MC_postPAS/HTT_HadTopTagger_2017_nomasscut_nvar12_semi_boosted_AK8.xml"
  ;
  mvaInputsHTT_AK8Sort = {
    "massW_SD",
    "tau21W",
    "btagDisc_b",
    "m_Wj1Wj2_div_m_bWj1Wj2",
    "dR_Wj1Wj2",
    "m_bWj1Wj2",
    "pT_bWj1Wj2",
    "mass_Wj1",
    "pT_Wj2",
    "mass_Wj2",
    "pT_b",
    "mass_b",
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
HadTopTagger_semi_boosted_AK8::operator()(const RecoJetAK8 & jet_ptrsAK8,
                                          const RecoJet & b_jet_candidate,
                                          bool & calculate_matching,
                                          bool & isGenMatched,
                                          double & genTopPt,
                                          const std::map<int, Particle::LorentzVector> & genVar,
                                          const std::map<int, Particle::LorentzVector> & genVarAnti
)
{
  if(! (jet_ptrsAK8.subJet1() && jet_ptrsAK8.subJet2()))
  {
    return { { kXGB_semi_boosted_AK8_no_kinFit,  0. } };
  }

  const Particle::LorentzVector recBJet = b_jet_candidate.p4();
  const Particle::LorentzVector recWJet1 = jet_ptrsAK8.subJet1()->p4();
  const Particle::LorentzVector recWJet2 = jet_ptrsAK8.subJet2()->p4();

  const double m_bWj1Wj2 = (recWJet1 + recWJet2 + recBJet).mass();
  const double  m_Wj1Wj2 = (recWJet1 + recWJet2).mass();

  if(calculate_matching)
  {
    const int typeTop = 2;
    const std::map<int, bool> genMatchingTop = isGenMatchedJetTriplet(
      recBJet,
      recWJet1,
      recWJet2,
      genVar.at(kGenTop),
      genVar.at(kGenTopB),
      genVar.at(kGenTopW),
      genVar.at(kGenTopWj1),
      genVar.at(kGenTopWj2),
      typeTop,
      jet_ptrsAK8.p4()
    );
    const std::map<int, bool> genMatchingAntiTop = isGenMatchedJetTriplet(
      recBJet,
      recWJet1,
      recWJet2,
      genVarAnti.at(kGenTop),
      genVarAnti.at(kGenTopB),
      genVarAnti.at(kGenTopW),
      genVarAnti.at(kGenTopWj1),
      genVarAnti.at(kGenTopWj2),
      typeTop, jet_ptrsAK8.p4()
    );
    if(genMatchingTop.at(kGenMatchedTriplet))
    {
      genTopPt = genVar.at(kGenTop).pt();
    }
    if(genMatchingAntiTop.at(kGenMatchedTriplet))
    {
      genTopPt = genVarAnti.at(kGenTop).pt();
    }

    isGenMatched = genMatchingTop.at(kGenMatchedTriplet) || genMatchingAntiTop.at(kGenMatchedTriplet);
  }

  mvaInputsHTT_AK8 = {
    { "massW_SD",               jet_ptrsAK8.msoftdrop()                },
    { "tau21W",                 jet_ptrsAK8.tau2()/jet_ptrsAK8.tau1()  },
    { "btagDisc_b",             b_jet_candidate.BtagCSV()              },
    { "m_Wj1Wj2_div_m_bWj1Wj2", m_Wj1Wj2 / m_bWj1Wj2                   },
    { "dR_Wj1Wj2",              deltaR(recWJet1, recWJet2)             },
    { "m_bWj1Wj2",              (recWJet1 + recWJet2 + recBJet).mass() },
    { "pT_bWj1Wj2",             (recWJet1 + recWJet2 + recBJet).pt()   },
    { "mass_Wj1",               recWJet1.mass()                        },
    { "pT_Wj2",                 recWJet2.pt()                          },
    { "mass_Wj2",               recWJet2.mass()                        },
    { "pT_b",                   recBJet.pt()                           },
    { "mass_b",                 recBJet.mass()                         },
  };
  const double HTT_CSVsort3rd = (*mva_xgb_HTT_AK8_)(mvaInputsHTT_AK8);

  return {{ kXGB_semi_boosted_AK8_no_kinFit, HTT_CSVsort3rd }};
}

const std::map<std::string, double> &
HadTopTagger_semi_boosted_AK8::mvaInputs() const
{
  return mvaInputsHTT_AK8;
}
