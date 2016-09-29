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
  setDiTauMass(double diTauMass);

  /**
   * @brief Updates the run-lumi-event related branches to new values
   * @param rleUnit The struct holding run-lumi-event numbers
   * @return 0
   */
  int
  add(const RLEUnit & rleUnit);

  /**
   * @brief Updates the MET related branches to new values
   * @param metUnit
   * @return
   */
  int
  add(const METUnit<double> & metUnit);

  /**
   * @brief Updates the MVA related input/output branches to new values
   * @param mva   The map containing MVA input values (string-double map)
   * @param ttV   MVA output value
   * @param ttbar Another MVA output value
   * @return
   */
  int
  add(const std::map<std::string, double> mva,
      double ttV,
      double ttbar);

  /**
   * @brief Updates the selected reco b-jet branches to new values
   * @param selBJets_loose  Selected loose b-jets
   * @param selBJets_medium Selected medium b-jets
   * @param selJets Selected hadronic jets
   * @return 0 if there are at least 2 unique jets, 1 otherwize
   *
   * Note that the function tries to sort the medium, loose and hadronic jets by their CSV,
   * which is followed by unique merge of medium, loose and hadronic jets. The reason why
   * we do this because in the analysis we might select a hadronic jet instead of a b-jet
   * if the first selected b-jet is a medium one and there are no other b-jets. However, the
   * subset relation b/w the jets is: medium < loose < hadronic; therefore, we need to find
   * unique set of jets. It's fortunately easy since we just need to compare pointer values
   * and nothing else.
   */
  int
  add(const std::vector<const RecoJet*> & selBJets_loose,
      const std::vector<const RecoJet*> & selBJets_medium,
      const std::vector<const RecoJet*> & selJets);

  /**
   * @brief Updates the selected reco lepton branches to new values
   * @param selLeptons Selected leptons
   * @return 0 if there are at least 3 selected leptons, 1 otherwise
   */
  int
  add(const std::vector<const RecoLepton*> & selLeptons);

  /**
   * @brief Updates the selected reco hadronic tau branches to new values
   * @param selHadTau Selected hadronic tau
   * @return 0 if the hadronic tau pointer is non-null, 1 otherwise
   */
  int
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
   * @return 0 if the underlying event (ttH/Z) could be constructed, 1 otherwise
   */
  int
  add(const std::vector<GenHadTau> & genHadTaus,
      const std::vector<GenLepton> & genBQuarkFromTop,
      const std::vector<GenLepton> & genLepFromTau,
      const std::vector<GenLepton> & genNuFromTau,
      const std::vector<GenLepton> & genTau,
      const std::vector<GenLepton> & genLepFromTop,
      const std::vector<GenLepton> & genNuFromTop);

  /**
   * @brief Fills the tree (ofc if it's initialized) and clears whatever
   *        vectors have been saved during add() functions
   */
  void
  fill();

  /**
   * @brief Closes the file and sets related pointers to zero
   */
  void
  close();

protected:

  TFile * file_;
  TTree * tree_;

  bool use2016_;
  double diTauMass_;

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
  RLEFiller rle_f_;
  METFiller<double> met_f_;

  /* mva */
  MapFiller<double> mva_f_; // provide map (below)
  BasicFiller<double> ttV_f_;
  BasicFiller<double> ttbar_f_;

  /* reconstructed */
  std::array<RecoLeptonFiller<double>, 3> leptons_f_;
  std::array<RecoJetFiller<double>, 2> jets_f_;
  RecoHadTauFiller<double> hTau_f_;

  /* generator level, enabled only if use2016_ is true */
  std::array<GenTauFiller<double>, 2>    genTaus_f_;
  std::array<GenLeptonFiller<double>, 2> genLepFromTop_f_;
  std::array<GenJetFiller<double>, 2>    genBQuark_f_;
  std::array<GenNuFiller<double>, 2>     genNuFromTop_f_;
  GenHadTauFiller<double> genHtau_f_;
  GenLeptonFiller<double> genLepFromTau_f_;
  GenNuFiller<double>     genNuLepFromTau_f_,
                          genNuFromHTau_f_,
                          genNuFromLTau_f_;

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

  std::vector<const RecoJet*> selBJetsMerged_;
  std::vector<const RecoLepton*> selLeptons_;
  const RecoHadTau * selHadTau_;
};

#endif // NTUPLEFILLERMEM_H
