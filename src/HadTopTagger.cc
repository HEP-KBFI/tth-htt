#include "tthAnalysis/HiggsToTauTau/interface/HadTopTagger.h" // HadTopTagger

#include "tthAnalysis/HiggsToTauTau/interface/TMVAInterface.h" // TMVAInterface
#include "tthAnalysis/HiggsToTauTau/interface/hadTopTaggerAuxFunctions_internal.h" // isGenMatchedJetTriplet()
#include "tthAnalysis/HiggsToTauTau/interface/hadTopTaggerAuxFunctions_geral.h" // kGen*
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // Btag::kDeepCSV

#include <DataFormats/Math/interface/deltaR.h> // deltaR()

HadTopTagger::HadTopTagger(void)
  : mva_xgb_HTT_CSVsort4rd_(nullptr)
{
  const std::string mvaFileNameHTT_CSVsort4rd =
    "tthAnalysis/HiggsToTauTau/data/BDTs_2017MC_postPAS/HTT_HadTopTagger_2017_nomasscut_nvar17_resolved.xml"
  ;

  mvaInputsHTTSort =  {
    "btagDisc_b",
    "btagDisc_Wj1",
    "btagDisc_Wj2",
    "qg_Wj1",
    "qg_Wj2",
    "m_Wj1Wj2_div_m_bWj1Wj2",
    "pT_Wj1Wj2",
    "dR_Wj1Wj2",
    "m_bWj1Wj2",
    "dR_bW",
    "m_bWj1",
    "m_bWj2",
    "mass_Wj1",
    "pT_Wj2",
    "mass_Wj2",
    "pT_b",
    "mass_b",
  };
  mva_xgb_HTT_CSVsort4rd_ = new TMVAInterface(
    mvaFileNameHTT_CSVsort4rd, mvaInputsHTTSort
  );
  mva_xgb_HTT_CSVsort4rd_->enableBDTTransform();
}

HadTopTagger::~HadTopTagger()
{
  delete mva_xgb_HTT_CSVsort4rd_;
}

std::map<int, double>
HadTopTagger::operator()(const RecoJet & recBJet,
                         const RecoJet & recWJet1,
                         const RecoJet & recWJet2,
                         bool & calculate_matching,
                         bool & isGenMatched,
                         double & genTopPt,
                         const std::map<int, Particle::LorentzVector> & genVar,
                         const std::map<int, Particle::LorentzVector> & genVarAnti,
                         const bool isDebug)
{
  const Particle::LorentzVector p4_bWj1Wj2 = recBJet.p4() + recWJet1.p4() + recWJet2.p4();
  const Particle::LorentzVector p4_Wj1Wj2  = recWJet1.p4() + recWJet2.p4();

  if(calculate_matching)
  {
    const std::map<int, bool> genMatchingTop = isGenMatchedJetTriplet(
      recBJet.p4(),
      recWJet1.p4(),
      recWJet2.p4(),
      genVar.at(kGenTop),
      genVar.at(kGenTopB),
      genVar.at(kGenTopW),
      genVar.at(kGenTopWj1),
      genVar.at(kGenTopWj2)
    );

    const std::map<int, bool> genMatchingAntiTop = isGenMatchedJetTriplet(
      recBJet.p4(),
      recWJet1.p4(),
      recWJet2.p4(),
      genVarAnti.at(kGenTop),
      genVarAnti.at(kGenTopB),
      genVarAnti.at(kGenTopW),
      genVarAnti.at(kGenTopWj1),
      genVarAnti.at(kGenTopWj2)
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
    { "btagDisc_b",             recBJet.BtagCSV(Btag::kDeepCSV)                     },
    { "btagDisc_Wj1",           recWJet1.BtagCSV(Btag::kDeepCSV)                    },
    { "btagDisc_Wj2",           recWJet2.BtagCSV(Btag::kDeepCSV)                    },
    { "qg_Wj1",                 recWJet1.QGDiscr()                                  },
    { "qg_Wj2",                 recWJet2.QGDiscr()                                  },
    { "m_Wj1Wj2_div_m_bWj1Wj2", p4_Wj1Wj2.mass() / p4_bWj1Wj2.mass()                },
    { "pT_Wj1Wj2",              p4_Wj1Wj2.pt()                                      },
    { "dR_Wj1Wj2",              deltaR(recWJet1.p4(), recWJet2.p4())                },
    { "m_bWj1Wj2",              p4_bWj1Wj2.mass()                                   },
    { "dR_bW",                  deltaR(recBJet.p4(), recWJet1.p4() + recWJet2.p4()) },
    { "m_bWj1",                 (recBJet.p4() + recWJet1.p4()).mass()               },
    { "m_bWj2",                 (recBJet.p4() + recWJet2.p4()).mass()               },
    { "mass_Wj1",               recWJet1.mass()                                     },
    { "pT_Wj2",                 recWJet2.pt()                                       },
    { "mass_Wj2",               recWJet2.mass()                                     },
    { "pT_b",                   recBJet.pt()                                        },
    { "mass_b",                 recBJet.mass()                                      },
  };
  const double HTT_CSVsort4rd = (*mva_xgb_HTT_CSVsort4rd_)(mvaInputsHTT);
  if ( isDebug ) {
    std::cout << "variables HTT \n";
    for (auto elem : mvaInputsHTT) std::cout << elem.first << " " << elem.second << "\n";
    std::cout << std::endl;
    std::cout << "result: " << HTT_CSVsort4rd<< std::endl;
    std::cout << "recWJet1.hasBtag (Btag::kDeepCSV): " << recWJet1.hasBtag (Btag::kDeepCSV) << "\n";
    std::cout << std::endl;
    std::cout << std::endl;
  }


  return { { kXGB_CSVsort4rd, HTT_CSVsort4rd } };
}

const std::map<std::string, double> &
HadTopTagger::mvaInputs() const
{
  return mvaInputsHTT;
}
