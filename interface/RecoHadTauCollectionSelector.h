#ifndef RECOHADTAUCOLLECTIONSELECTOR_H
#define RECOHADTAUCOLLECTIONSELECTOR_H

template<typename T>
class RecoHadTauCollectionSelector
{
public:
  explicit
  RecoHadTauCollectionSelector(int era,
                               int index = -1,
                               bool debug = false)
    : selIndex_(index)
    , selector_(era, index, debug)
  {}
  ~RecoHadTauCollectionSelector() {}

  void
  set_min_pt(double min_pt)
  {
    selector_.set_min_pt(min_pt);
  }

  void
  set_max_absEta(double max_absEta)
  {
    selector_.set_max_absEta(max_absEta);
  }

  void
  set_min_id_mva_dR03(int min_id_mva_dR03)
  {
    selector_.set_min_id_mva_dR03(min_id_mva_dR03);
  }

  void
  set_min_raw_mva_dR03(double min_raw_mva_dR03)
  {
    selector_.set_min_raw_mva_dR03(min_raw_mva_dR03);
  }

  void
  set_min_id_mva_dR05(int min_id_mva_dR05)
  {
    selector_.set_min_id_mva_dR05(min_id_mva_dR05);
  }

  void
  set_min_raw_mva_dR05(double min_raw_mva_dR05)
  {
    selector_.set_min_raw_mva_dR05(min_raw_mva_dR05);
  }

  void
  set_min_id_cut_dR03(int min_id_cut_dR03)
  {
    selector_.set_min_id_cut_dR03(min_id_cut_dR03);
  }

  void
  set_max_raw_cut_dR03(double max_raw_cut_dR03)
  {
    selector_.set_max_raw_cut_dR03(max_raw_cut_dR03);
  }

  void
  set_min_id_cut_dR05(int min_id_cut_dR05)
  {
    selector_.set_min_id_cut_dR05(min_id_cut_dR05);
  }

  void
  set_max_raw_cut_dR05(double max_raw_cut_dR05)
  {
    selector_.set_max_raw_cut_dR05(max_raw_cut_dR05);
  }

  void
  set(const std::string & cut)
  {
    selector_.set(cut);
  }

  void
  set_min_antiElectron(int min_antiElectron)
  {
    selector_.set_min_antiElectron(min_antiElectron);
  }

  void
  set_min_antiMuon(int min_antiMuon)
  {
    selector_.set_min_antiMuon(min_antiMuon);
  }

  std::vector<const RecoHadTau *>
  operator()(const std::vector<const RecoHadTau *> & hadTaus) const
  {
    std::vector<const RecoHadTau *> selHadTaus;
    int idx = 0;
    for(const RecoHadTau * hadTau: hadTaus)
    {
      if(selector_(*hadTau))
      {
        if(idx == selIndex_ || selIndex_ == -1)
        {
          selHadTaus.push_back(hadTau);
        }
        ++idx;
      }
    }
    return selHadTaus;
  }

protected:
  int selIndex_;
  T selector_;
};

#endif // RECOHADTAUCOLLECTIONSELECTOR_H
