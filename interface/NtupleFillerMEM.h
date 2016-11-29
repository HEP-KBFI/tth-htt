#ifndef NTUPLEFILLERMEM_H
#define NTUPLEFILLERMEM_H

#include "tthAnalysis/HiggsToTauTau/interface/NtupleFillerUnits.h"
#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h"
#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h"

#include <TFile.h>
#include <TTree.h>

#include <boost/math/special_functions/sign.hpp> // boost::math::sign()

#include <vector> // std::vector<>
#include <array> // std::array<>
#include <algorithm> // std::sort(), std::find(), std::remove_if()

#define NOF_RECO_JETS 4

#define NTUPLE_ERR_OK                                       0ull
#define NTUPLE_ERR_HIGGS_DECAY_MODE                         1ull << 0
#define NTUPLE_ERR_NO_2_JETS                                1ull << 1
#define NTUPLE_ERR_NO_3_LEPTONS                             1ull << 2
#define NTUPLE_ERR_NO_HAD_TAU                               1ull << 3
#define NTUPLE_ERR_SAME_SIGN_TOPS                           1ull << 4
#define NTUPLE_ERR_SAME_SIGN_WS                             1ull << 5
#define NTUPLE_ERR_SAME_FLAVOR_BQUARKS                      1ull << 6
#define NTUPLE_ERR_SAME_SIGN_TAUS                           1ull << 7
#define NTUPLE_ERR_SAME_SIGN_LEPS_FROM_TOP                  1ull << 8
#define NTUPLE_ERR_SAME_FLAVOR_NUS_FROM_TOP                 1ull << 9
#define NTUPLE_ERR_NO_2_GEN_TOPS                            1ull << 10
#define NTUPLE_ERR_NO_2_GEN_BQUARKS                         1ull << 11
#define NUTPLE_ERR_NO_2_GEN_WBOSONS                         1ull << 12
#define NTUPLE_ERR_NO_2_GEN_TAUS                            1ull << 13
#define NTUPLE_ERR_NO_2_GEN_NU_FROM_TOP                     1ull << 14
#define NTUPLE_ERR_NO_2_GEN_LEP_FROM_TOP                    1ull << 15
#define NTUPLE_ERR_NO_GEN_HAD_TAU                           1ull << 16
#define NTUPLE_ERR_NO_SINGLE_GEN_LEPT_FROM_TAU              1ull << 17
#define NTUPLE_ERR_NO_3_GEN_NUS_FROM_TAU                    1ull << 18
#define NUTPLE_ERR_NO_GEN_NU_LEP_FROM_TAU                   1ull << 19
#define NUTPLE_ERR_NO_GEN_NU_LEP_FROM_LTAU                  1ull << 20
#define NUTPLE_ERR_NO_GEN_NU_LEP_FROM_HTAU                  1ull << 21
#define NTUPLE_ERR_NO_SINGLE_HADRONIC_TAU                   1ull << 22
#define NTUPLE_ERR_LTAU_MASS_OFF                            1ull << 23
#define NTUPLE_ERR_HTAU_MASS_OFF                            1ull << 24
#define NTUPLE_ERR_DITAU_MASS_OFF                           1ull << 25
#define NTUPLE_ERR_WPOS_MASS_NOT_RECONSTRUCTED              1ull << 26
#define NTUPLE_ERR_WNEG_MASS_NOT_RECONSTRUCTED              1ull << 27
#define NTUPLE_ERR_T_MASS_OFF                               1ull << 28
#define NTUPLE_ERR_TBAR_MASS_OFF                            1ull << 29
#define NTUPLE_ERR_HAD_TAU_MISMATCH                         1ull << 30
#define NTUPLE_ERR_LEP_FROM_TAU_MISMATCH                    1ull << 31
#define NTUPLE_ERR_LEP_FROM_T_MISMATCH                      1ull << 32
#define NTUPLE_ERR_LEP_FROM_TBAR_MISMATCH                   1ull << 33
#define NTUPLE_ERR_SAME_LEPTON_MULTIPLE_CANDIDATE           1ull << 34
#define NUTPLE_ERR_B_MISMATCH                               1ull << 35
#define NUTPLE_ERR_BBAR_MISMATCH                            1ull << 36
#define NTUPLE_ERR_SAME_B_BBAR_CANDIDATES                   1ull << 37

#define NTUPLE_WARN_OK                                0ull
#define NTUPLE_WARN_MULTIPLE_LEP_FROM_TAU_CANDIDATES  1ull << 0
#define NTUPLE_WARN_MULTIPLE_LEP_FROM_T_CANDIDATES    1ull << 1
#define NTUPLE_WARN_MULTIPLE_LEP_FROM_TBAR_CANDIDATES 1ull << 2
#define NTUPLE_WARN_MULTIPLE_B_CANDIDATES             1ull << 3
#define NTUPLE_WARN_MULTIPLE_BBAR_CANDIDATES          1ull << 4
#define NTUPLE_WARN_B_MATCH_OUTSIDE_2_SELJETS         1ull << 5
#define NTUPLE_WARN_BBAR_MATCH_OUTSIDE_2_SELJETS      1ull << 6

typedef GenLepton GenParticleExt;

template <typename FloatType>
using RecoLeptonFiller = GenLeptonFiller<FloatType>;

template <typename FloatType>
using RecoJetFiller = GenParticleFiller<FloatType>;

template <typename FloatType>
using GenTauFiller = GenLeptonFiller<FloatType>;

template <typename FloatType>
using GenJetFiller = GenLeptonFiller<FloatType>;

template <typename FloatType>
using GenNuFiller = GenLeptonFiller<FloatType>;

struct NtupleFillerMEM // only for 3l1tau analysis
{
  /**
   * @brief Initialize file pointer to zero;
   *        do not use gen lvl info by default
   */
  NtupleFillerMEM();

  /**
    * Destructor; close the file
    * (WOOO, RAII)
    */
  ~NtupleFillerMEM();

  /**
   * @brief Basically, tell the class to use generator lvl info
   * @param use2016 Use true, if you want to use gen lvl info
   *
   * @note Use this function before setFileName() !!!
   */
  void
  use2016(bool use2016);

  /**
   * @brief Creates the file and initializes the tree
   * @param fileName
   */
  void
  setFileName(const std::string & fileName);

  /**
   * @brief Set the mass of two taus in ttH/ttZ (H/Z -> tau tau)
   * @param diTauMass The di-tau mass
   */
  void
  isSignal(bool isSignal_b);

  /**
   * @brief Updates Higgs decay mode at generator level
   * @param genHiggsDecayMode The decay mode
   */
  void
  add(double genHiggsDecayMode);

  /**
   * @brief Updates the run-lumi-event related branches to new values
   * @param rleUnit The struct holding run-lumi-event numbers
   */
  void
  add(const RLEUnit & rleUnit);

  /**
   * @brief Updates the MET related branches to new values
   * @param metUnit
   */
  void
  add(const METUnit<double> & metUnit);

  /**
   * @brief Updates the MVA related input/output branches to new values
   * @param mva   The map containing MVA input values (string-double map)
   * @param ttV   MVA output value
   * @param ttbar Another MVA output value
   */
  void
  add(const std::map<std::string, double> mva,
      double ttV,
      double ttbar);

  /**
   * @brief Updates the selected reco b-jet branches to new values
   * @param selBJets_loose  Selected loose b-jets
   * @param selBJets_medium Selected medium b-jets
   * @param selJets Selected hadronic jets
   *
   * Note that the function tries to sort the medium, loose and hadronic jets by their CSV,
   * which is followed by unique merge of medium, loose and hadronic jets. The reason why
   * we do this because in the analysis we might select a hadronic jet instead of a b-jet
   * if the first selected b-jet is a medium one and there are no other b-jets. However, the
   * subset relation b/w the jets is: medium < loose < hadronic; therefore, we need to find
   * unique set of jets. It's fortunately easy since we just need to compare pointer values
   * and nothing else.
   */
  void
  add(const std::vector<const RecoJet*> & selBJets_loose,
      const std::vector<const RecoJet*> & selBJets_medium,
      const std::vector<const RecoJet*> & selJets);

  /**
   * @brief Updates the selected reco lepton branches to new values
   * @param selLeptons Selected leptons
   */
  void
  add(const std::vector<const RecoLepton*> & selLeptons);

  /**
   * @brief Updates the selected reco hadronic tau branches to new values
   * @param selHadTau Selected hadronic tau
   */
  void
  add(const RecoHadTau * selHadTau);

  /**
   * @brief Updates the generator level branches to new values
   * @param genHadTaus       Generator level hadronic taus
   * @param genBQuarkFromTop Generator level b quarks from top
   * @param genLepFromTau    Generator level leptons from tau
   * @param genNuFromTau     Generator level neutrinos from tau
   * @param genTau           Generator level taus
   * @param genLepFromTop    Generator level leptons from top
   * @param genNuFromTop     Generator level neutrinos from top
   */
  void
  add(const std::vector<GenHadTau> & genHadTaus,
      const std::vector<GenLepton> & genBQuarkFromTop,
      const std::vector<GenLepton> & genLepFromTau,
      const std::vector<GenLepton> & genNuFromTau,
      const std::vector<GenLepton> & genTau,
      const std::vector<GenLepton> & genLepFromTop,
      const std::vector<GenLepton> & genNuFromTop,
      const std::vector<GenLepton> & genTop,
      const std::vector<GenLepton> & genVbosons);

  /**
   * @brief Fills the tree (ofc if it's initialized) and clears whatever
   *        vectors have been saved during add() functions
   * @param force If true, fills anyways
   */
  void
  fill(bool force = false);

  /**
   * @brief Closes the file and sets related pointers to zero
   */
  void
  close();

protected:

  TFile * file_;
  TTree * tree_;

  bool use2016_;
  bool isSignal_b_;

  const std::map<std::string, std::string> mvaMap_ = {
    { "max(abs(LepGood_eta[iF_Recl[0]]),abs(LepGood_eta[iF_Recl[1]]))", "max2LeptonEta"  },
    { "MT_met_lep1",                                                    "MT_met_lep1"    },
    { "nJet25_Recl",                                                    "nJet25_Recl"    },
    { "mindr_lep1_jet",                                                 "mindr_lep1_jet" },
    { "mindr_lep2_jet",                                                 "mindr_lep2_jet" },
    { "LepGood_conePt[iF_Recl[0]]",                                     "lep1_cone_pt"   },
    { "LepGood_conePt[iF_Recl[2]]",                                     "lep3_cone_pt"   },
    { "avg_dr_jet",                                                     "avg_dr_jet"     },
    { "mhtJet25_Recl",                                                  "mhtJet25_Recl"  }
  };

  /* basics */
  RLEUnit rle_;
  RLEFiller rle_f_;
  METFiller<double> met_f_;

  /* mva */
  MapFiller<double> mva_f_; // provide map (below)
  BasicFiller<double> ttV_f_;
  BasicFiller<double> ttbar_f_;

  /* reconstructed */
  std::array<RecoLeptonFiller<double>, 3> leptons_f_;
  BasicFiller<int> njet_f_;
  std::array<RecoJetFiller<double>, NOF_RECO_JETS> jets_f_;
  RecoHadTauFiller<double> hTau_f_;

  /* generator level, enabled only if use2016_ is true */
  std::array<GenTauFiller<double>, 2>    genTaus_f_;
  std::array<GenLeptonFiller<double>, 2> genLepFromTop_f_,
                                         genW_f_,
                                         genT_f_;
  std::array<GenJetFiller<double>, 2>    genBQuark_f_;
  std::array<GenNuFiller<double>, 2>     genNuFromTop_f_;
  GenHadTauFiller<double> genHtau_f_;
  GenLeptonFiller<double> genLepFromTau_f_,
                          genHZ_f_;
  GenNuFiller<double>     genNuLepFromTau_f_,
                          genNuFromHTau_f_,
                          genNuFromLTau_f_;
  BasicFiller<double> genHiggsDecayMode_; // use only if signal sample

  /* multiplicity counter of generator level objects */
  std::array<BasicFiller<unsigned int>, 9> genMultiplicity_f_;

private:

  /**
   * @brief Auxiliary function for sorting a collection of RecoJet pointers
   *        by their b-tagging CSV score
   * @param jet1 The first jet
   * @param jet2 The second jet
   * @return True, if the 1st jet has higher CSV score
   */
  static bool
  isHigherCSV(const RecoJet * jet1,
              const RecoJet * jet2);

  /**
   * @brief Recalculates b-quark's mass and energy from top and b-quark mass requirements
   * @param b     Original b-quark, the direction of which is kept the same
   * @param W     The W boson (not changed)
   * @param pdgId PDG id of the b-quark
   * @return A new b-quark
   *
   * This method is needed b/c soft activity in the top decays spoils 4-momentum conservation
   * due to the way generator level particles are stored in the Ntuples (only immediate daughters
   * are stored). The workaround is to redefine b quark's 3-momentum and mass so that
   *  1) it always has the PDG value for its mass;
   *  2) if by adding b and W, the resulting top also has the PDG value for its mass;
   *  3) while b's direction remains untouched.
   */
  static GenLepton
  getB(const GenLepton & b,
       const GenLepton & W,
       Int_t pdgId);

  /**
   * @brief Recalculates neutrino's 4-momentum from its older self and complementary lepton
   * @param l       The complementary lepton
   * @param nu      The old neutrino
   * @param momMass Desired mass of the mother particle
   * @param pdgId   The PDG id of the resulting neutrino
   * @return The new neutrino
   */
  static GenLepton
  getNu(const GenLepton & l,
        const GenLepton & nu,
        double momMass,
        Int_t pdgId);

  std::vector<const RecoJet*> selBJetsMerged_;
  std::vector<const RecoLepton*> selLeptons_;
  const RecoHadTau * selHadTau_;

  unsigned long long errCode_, warnCode_;
  BasicFiller<unsigned long long> errCode_f_, warnCode_f_;
};

#endif // NTUPLEFILLERMEM_H
