#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauSelectorBase.h" // RecoHadTauSelectorBase

#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

RecoHadTauSelectorBase::RecoHadTauSelectorBase(int era,
                                               int index,
                                               bool debug,
                                               bool set_selection_flags)
  : set_selection_flags_(set_selection_flags)
  , debug_(debug)
  , min_pt_(20.)
  , max_absEta_(2.3)
  , max_dz_(0.2)
  , apply_decayModeFinding_(true)
  , min_id_mva_dR03_(-1000)
  , min_raw_mva_dR03_(-1.e+6)
  , min_id_mva_dR05_(-1000)
  , min_raw_mva_dR05_(-1.e+6)
  , min_id_cut_dR03_(-1000)
  , max_raw_cut_dR03_(1.e+6)
  , min_id_cut_dR05_(-1000)
  , max_raw_cut_dR05_(1.e+6)
  , min_antiElectron_(-1000)
  , min_antiMuon_(-1000)
{}

void
RecoHadTauSelectorBase::set_min_pt(double min_pt)
{
  min_pt_ = min_pt;
}

void
RecoHadTauSelectorBase::set_max_absEta(double max_absEta)
{
  max_absEta_ = max_absEta;
}

double
RecoHadTauSelectorBase::get_min_pt() const
{
  return min_pt_;
}

double
RecoHadTauSelectorBase::get_max_absEta() const
{
  return max_absEta_;
}

void
RecoHadTauSelectorBase::set_min_id_mva_dR03(int min_id_mva_dR03)
{
  min_id_mva_dR03_ = min_id_mva_dR03;
}

void
RecoHadTauSelectorBase::set_min_raw_mva_dR03(double min_raw_mva_dR03)
{
  min_raw_mva_dR03_ = min_raw_mva_dR03;
}

void
RecoHadTauSelectorBase::set_min_id_mva_dR05(int min_id_mva_dR05)
{
  min_id_mva_dR05_ = min_id_mva_dR05;
}

void
RecoHadTauSelectorBase::set_min_raw_mva_dR05(double min_raw_mva_dR05)
{
  min_raw_mva_dR05_ = min_raw_mva_dR05;
}

void
RecoHadTauSelectorBase::set_min_id_cut_dR03(int min_id_cut_dR03)
{
  min_id_cut_dR03_ = min_id_cut_dR03;
}

void
RecoHadTauSelectorBase::set_max_raw_cut_dR03(double max_raw_cut_dR03)
{
  max_raw_cut_dR03_ = max_raw_cut_dR03;
}

void
RecoHadTauSelectorBase::set_min_id_cut_dR05(int min_id_cut_dR05)
{
  min_id_cut_dR05_ = min_id_cut_dR05;
}

void
RecoHadTauSelectorBase::set_max_raw_cut_dR05(double max_raw_cut_dR05)
{
  max_raw_cut_dR05_ = max_raw_cut_dR05;
}

int
RecoHadTauSelectorBase::get_min_id_mva_dR03() const
{
  return min_id_mva_dR03_;
}

double
RecoHadTauSelectorBase::get_min_raw_mva_dR03() const
{
  return min_raw_mva_dR03_;
}

int
RecoHadTauSelectorBase::get_min_id_mva_dR05() const
{
  return min_id_mva_dR05_;
}

double
RecoHadTauSelectorBase::get_min_raw_mva_dR05() const
{
  return min_raw_mva_dR05_;
}

int
RecoHadTauSelectorBase::get_min_id_cut_dR03() const
{
  return min_id_cut_dR03_;
}

double
RecoHadTauSelectorBase::get_max_raw_cut_dR03() const
{
  return max_raw_cut_dR03_;
}

int
RecoHadTauSelectorBase::get_min_id_cut_dR05() const
{
  return min_id_cut_dR05_;
}

double
RecoHadTauSelectorBase::get_max_raw_cut_dR05() const
{
  return max_raw_cut_dR05_;
}

void
RecoHadTauSelectorBase::set_min_antiElectron(int min_antiElectron)
{
  min_antiElectron_ = min_antiElectron;
}

void
RecoHadTauSelectorBase::set_min_antiMuon(int min_antiMuon)
{
  min_antiMuon_ = min_antiMuon;
}

int
RecoHadTauSelectorBase::get_min_antiElectron() const
{
  return min_antiElectron_;
}

int
RecoHadTauSelectorBase::get_min_antiMuon() const
{
  return min_antiMuon_;
}

void
RecoHadTauSelectorBase::set(const std::string & cut)
{
  set_min_id_mva_dR03(-1000);
  set_min_raw_mva_dR03(-1.e+6);
  set_min_id_mva_dR05(-1000);
  set_min_raw_mva_dR05(-1.e+6);
  set_min_id_cut_dR03(-1000);
  set_max_raw_cut_dR03(1.e+6);
  set_min_id_cut_dR05(-1000);
  set_max_raw_cut_dR05(1.e+6);
  if     (cut == "dR03mvaVVLoose") set_min_id_mva_dR03(1);
  else if(cut == "dR03mvaVLoose" ) set_min_id_mva_dR03(2);
  else if(cut == "dR03mvaLoose"  ) set_min_id_mva_dR03(3);
  else if(cut == "dR03mvaMedium" ) set_min_id_mva_dR03(4);
  else if(cut == "dR03mvaTight"  ) set_min_id_mva_dR03(5);
  else if(cut == "dR03mvaVTight" ) set_min_id_mva_dR03(6);
  else if(cut == "dR03mvaVVTight") set_min_id_mva_dR03(7);
  else
  {
    throw cmsException(this, __func__)
      << "Invalid Configuration parameter 'cut' = " << cut;
  }
  cut_ = cut;
}

const std::string &
RecoHadTauSelectorBase::get() const
{
  return cut_;
}

bool
RecoHadTauSelectorBase::operator()(const RecoHadTau & hadTau) const
{
  if(debug_)
  {
    std::cout << get_human_line(this, __func__) << ":\n hadTau: " << hadTau << '\n';
  }

  if(hadTau.pt() < min_pt_)
  {
    if(debug_)
    {
      std::cout << "FAILS pT >= " << min_pt_ << " cut\n";
    }
    return false;
  }
  if(hadTau.absEta() > max_absEta_)
  {
    if(debug_)
    {
      std::cout << "FAILS abs(eta) <= " << max_absEta_ << " cut\n";
    }
    return false;
  }
  if(std::fabs(hadTau.dz()) > max_dz_)
  {
    if(debug_)
    {
      std::cout << "FAILS abs(dz) <= " << max_dz_ << " cut\n";
    }
    return false;
  }
  if(apply_decayModeFinding_ && ! hadTau.decayModeFinding())
  {
    if(debug_)
    {
      std::cout << "FAILS decayModeFinding cut\n";
    }
    return false;
  }
  if(hadTau.id_mva_dR03() < min_id_mva_dR03_)
  {
    if(debug_)
    {
      std::cout << "FAILS id_mva_dR03 >= " << min_id_mva_dR03_ << " cut\n";
    }
    return false;
  }
  if(hadTau.raw_mva_dR03() < min_raw_mva_dR03_)
  {
    if(debug_)
    {
      std::cout << "FAILS raw_mva_dR03 >= " << min_raw_mva_dR03_ << "cut\n";
    }
    return false;
  }
  if(hadTau.id_mva_dR05() < min_id_mva_dR05_)
  {
    if(debug_)
    {
      std::cout << "FAILS id_mva_dR05 >= " << min_id_mva_dR05_ << " cut\n";
    }
    return false;
  }
  if(hadTau.raw_mva_dR05() < min_raw_mva_dR05_)
  {
    if(debug_)
    {
      std::cout << "FAILS raw_mva_dR05 >= " << min_raw_mva_dR05_ << " cut\n";
    }
    return false;
  }
  if(hadTau.id_cut_dR03() < min_id_cut_dR03_)
  {
    if(debug_)
    {
      std::cout << "FAILS id_cut_dR03 >= " << min_id_cut_dR03_ << " cut\n";
    }
    return false;
  }
  if(hadTau.raw_cut_dR03() > max_raw_cut_dR03_)
  {
    if(debug_)
    {
      std::cout << "FAILS raw_cut_dR03 <= " << max_raw_cut_dR03_ << " cut\n";
    }
    return false;
  }
  if(hadTau.id_cut_dR05() < min_id_cut_dR05_)
  {
    if(debug_)
    {
      std::cout << "FAILS id_cut_dR05 >= " << min_id_cut_dR05_ << " cut\n";
    }
    return false;
  }
  if(hadTau.raw_cut_dR05() > max_raw_cut_dR05_)
  {
    if(debug_)
    {
      std::cout << "FAILS raw_cut_dR05 <= " << max_raw_cut_dR05_ << " cut\n";
    }
    return false;
  }
  if(hadTau.antiElectron() < min_antiElectron_)
  {
    if(debug_)
    {
      std::cout << "FAILS antiElectron >= " << min_antiElectron_ << " cut\n";
    }
    return false;
  }
  if(hadTau.antiMuon() < min_antiMuon_)
  {
    if(debug_)
    {
      std::cout << "FAILS antiMuon >= " << min_antiMuon_ << "cut\n";
    }
    return false;
  }

  // hadTau passes all cuts
  if(set_selection_flags_)
  {
    set_selection_flags(hadTau);
  }
  return true;
}
