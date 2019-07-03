#include "tthAnalysis/HiggsToTauTau/interface/HadTopTagger_boosted.h" // HadTopTagger_boosted

#include "tthAnalysis/HiggsToTauTau/interface/TMVAInterface.h" // TMVAInterface
#include "tthAnalysis/HiggsToTauTau/interface/hadTopTaggerAuxFunctions.h" // sort_indexes()
#include "tthAnalysis/HiggsToTauTau/interface/hadTopTaggerAuxFunctions_internal.h" // isGenMatchedJetTriplet()
#include "tthAnalysis/HiggsToTauTau/interface/hadTopTaggerAuxFunctions_geral.h" // kGen*

#include <DataFormats/Math/interface/deltaR.h> // deltaR()

HadTopTagger_boosted::HadTopTagger_boosted(void)
  : mva_xgb_HTT_highestCSV_(nullptr)
{
  const std::string mvaFileNameHTT_highestCSV =
    "tthAnalysis/HiggsToTauTau/data/BDTs_2017MC_postPAS/HTT_HadTopTagger_2017_nomasscut_nvar13_boosted.xml"
  ;

  mvaInputsHTTSort = {
    "tau32Top",
    "btagDisc_b",
    "m_Wj1Wj2_div_m_bWj1Wj2",
    "pT_Wj1Wj2",
    "dR_Wj1Wj2",
    "m_bWj1Wj2",
    "pT_bWj1Wj2",
    "m_bWj2",
    "mass_Wj1",
    "pT_Wj2",
    "mass_Wj2",
    "pT_b",
    "mass_b",
  };
  mva_xgb_HTT_highestCSV_ = new TMVAInterface(
    mvaFileNameHTT_highestCSV, mvaInputsHTTSort
  );
  mva_xgb_HTT_highestCSV_->enableBDTTransform();
}

HadTopTagger_boosted::~HadTopTagger_boosted()
{
  delete mva_xgb_HTT_highestCSV_;
}

std::map<int, double>
HadTopTagger_boosted::operator()(const RecoJetHTTv2 & jet_HTTv2,
                                 bool & calculate_matching, bool & isGenMatched,
                                 double & genTopPt,
                                 const std::map<int, Particle::LorentzVector> & genVar,
                                 const std::map<int, Particle::LorentzVector> & genVarAnti)
{
  const std::vector<const RecoSubjetHTTv2 *> recSubJet = {
    jet_HTTv2.subJet1(),
    jet_HTTv2.subJet2(),
    jet_HTTv2.subJet3(),
  };
  const std::vector<double> btag_disc = { recSubJet[0]->BtagCSV(), recSubJet[1]->BtagCSV(), recSubJet[2]->BtagCSV() };
  const auto btag_order = sort_indexes(btag_disc);

  const Particle::LorentzVector recBJet = recSubJet[btag_order[0]]->p4();
  const Particle::LorentzVector recWJet1 = recSubJet[btag_order[1]]->p4();
  const Particle::LorentzVector recWJet2 = recSubJet[btag_order[2]]->p4();

  const double m_bWj1Wj2 = jet_HTTv2.p4().mass();
  const double  m_Wj1Wj2 = (recWJet1 + recWJet2).mass();

  if(calculate_matching)
  {
    const int typeTop = 1;
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
      jet_HTTv2.p4()
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
      typeTop,
      jet_HTTv2.p4()
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

  mvaInputsHTT = {
    { "tau32Top",               jet_HTTv2.tau3()/jet_HTTv2.tau2()   },
    { "btagDisc_b",             recSubJet[btag_order[0]]->BtagCSV() },
    { "m_Wj1Wj2_div_m_bWj1Wj2", m_Wj1Wj2 / m_bWj1Wj2                },
    { "pT_Wj1Wj2",              (recWJet1 + recWJet2).pt()          },
    { "dR_Wj1Wj2",              deltaR(recWJet1,recWJet2)           },
    { "m_bWj1Wj2",              jet_HTTv2.p4().mass()               },
    { "pT_bWj1Wj2",             jet_HTTv2.p4().pt()                 },
    { "m_bWj2",                 (recBJet + recWJet2).mass()         },
    { "mass_Wj1",               recWJet1.mass()                     },
    { "pT_Wj2",                 recWJet2.pt()                       },
    { "mass_Wj2",               recWJet2.mass()                     },
    { "pT_b",                   recBJet.pt()                        },
    { "mass_b",                 recBJet.mass()                      },
  };
  const double HTT_highestCSV = (*mva_xgb_HTT_highestCSV_)(mvaInputsHTT);

  return { { kXGB_boosted_no_kinFit,  HTT_highestCSV } };
}

const std::map<std::string, double> &
HadTopTagger_boosted::mvaInputs() const
{
  return mvaInputsHTT;
}
