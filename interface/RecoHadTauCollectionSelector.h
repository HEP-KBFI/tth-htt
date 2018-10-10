#ifndef RECOHADTAUCOLLECTIONSELECTOR_H
#define RECOHADTAUCOLLECTIONSELECTOR_H

#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionSelector.h" // ParticleCollectionSelector

template<typename T>
class RecoHadTauCollectionSelector
  : public ParticleCollectionSelector<RecoHadTau, T>
{
public:
  explicit
  RecoHadTauCollectionSelector(int era,
                               int index = -1,
                               bool debug = false)
    : ParticleCollectionSelector<RecoHadTau, T>(era, index, debug)
  {}
  ~RecoHadTauCollectionSelector() {}

  void
  set_min_pt(double min_pt)
  {
    this->selector_.set_min_pt(min_pt);
  }

  void
  set_max_absEta(double max_absEta)
  {
    this->selector_.set_max_absEta(max_absEta);
  }

  void
  set_min_id_mva_dR03(int min_id_mva_dR03)
  {
    this->selector_.set_min_id_mva_dR03(min_id_mva_dR03);
  }

  void
  set_min_raw_mva_dR03(double min_raw_mva_dR03)
  {
    this->selector_.set_min_raw_mva_dR03(min_raw_mva_dR03);
  }

  void
  set_min_id_mva_dR05(int min_id_mva_dR05)
  {
    this->selector_.set_min_id_mva_dR05(min_id_mva_dR05);
  }

  void
  set_min_raw_mva_dR05(double min_raw_mva_dR05)
  {
    this->selector_.set_min_raw_mva_dR05(min_raw_mva_dR05);
  }

  void
  set_min_id_cut_dR03(int min_id_cut_dR03)
  {
    this->selector_.set_min_id_cut_dR03(min_id_cut_dR03);
  }

  void
  set_max_raw_cut_dR03(double max_raw_cut_dR03)
  {
    this->selector_.set_max_raw_cut_dR03(max_raw_cut_dR03);
  }

  void
  set_min_id_cut_dR05(int min_id_cut_dR05)
  {
    this->selector_.set_min_id_cut_dR05(min_id_cut_dR05);
  }

  void
  set_max_raw_cut_dR05(double max_raw_cut_dR05)
  {
    this->selector_.set_max_raw_cut_dR05(max_raw_cut_dR05);
  }

  void
  set(const std::string & cut)
  {
    this->selector_.set(cut);
  }

  bool
  set_if_looser(const std::string & cut)
  {
    return this->selector_.set_if_looser(cut);
  }

  void
  set_min_antiElectron(int min_antiElectron)
  {
    this->selector_.set_min_antiElectron(min_antiElectron);
  }

  void
  set_min_antiMuon(int min_antiMuon)
  {
    this->selector_.set_min_antiMuon(min_antiMuon);
  }
};

#endif // RECOHADTAUCOLLECTIONSELECTOR_H
