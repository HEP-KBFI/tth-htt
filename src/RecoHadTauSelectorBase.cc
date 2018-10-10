#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauSelectorBase.h" // RecoHadTauSelectorBase

#include <FWCore/Utilities/interface/Parse.h> // edm::tokenize()

#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // get_tau_id_wp_int()

#include <boost/algorithm/string/join.hpp> // boost::algorithm::join()

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
  , mva_selection_(MVASelection::kNone)
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
  if(cut.empty())
  {
    return;
  }

  set_min_id_mva_dR03(-1000);
  set_min_raw_mva_dR03(-1.e+6);
  set_min_id_mva_dR05(-1000);
  set_min_raw_mva_dR05(-1.e+6);
  set_min_id_cut_dR03(-1000);
  set_max_raw_cut_dR03(1.e+6);
  set_min_id_cut_dR05(-1000);
  set_max_raw_cut_dR05(1.e+6);
  mva_selection_ = MVASelection::kNone;

  const std::vector<std::string> cut_parts = edm::tokenize(cut, "&");
  assert(cut_parts.size() == 1 || cut_parts.size() == 2);

  for(const std::string & cut_part: cut_parts)
  {
    const std::string wp = cut_part.substr(7);
    const std::string mva_type = cut_part.substr(0, 7);
    const int wp_int = get_tau_id_wp_int(wp);

    if(mva_type == "dR03mva")
    {
      set_min_id_mva_dR03(wp_int);
    }
    else if(mva_type == "dR05mva")
    {
      set_min_id_mva_dR05(wp_int);
    }
    else
    {
      throw cmsException(this, __func__, __LINE__)
          << "Invalid mva_type = " << mva_type
      ;
    }
  }

  if(cut_parts.size() == 2)
  {
    if(std::find(cut.begin(), cut.end(), '&') != cut.end())
    {
      mva_selection_ = MVASelection::kOR;
    }
    else
    {
      assert(0);
    }
  }

  cut_ = cut;
}

const std::string &
RecoHadTauSelectorBase::get() const
{
  return cut_;
}

bool
RecoHadTauSelectorBase::set_if_looser(const std::string & cut)
{
  if(cut.empty())
  {
    return false;
  }

  // if the old cut is an OR of two WPs, then throw an error; otherwise:
  // a) new cut is a single WP
  //   i) the MVAs are different -> replace the MVA
  //   ii) the MVAs are the same -> if the old MVA WP is strictly looser than the old WP, then replace it w/ the new WP
  // b) the new cut consists of two MVA WPs
  //   i) if the MVA WP from the new cut is strictly looser than the old WP, then replace it w/ the new WP and
  //      OR it w/ the second provided WP
  //   ii) if the MVA WP from the new cut is not strictly looser than the old WP, then just OR the old WP and new WP
  const std::vector<std::string> cut_parts_old = edm::tokenize(cut_, "&");
  if(cut_parts_old.size() != 1)
  {
    throw cmsException(this, __func__, __LINE__)
        << "Can overwrite a single tau WP but got 2 of them: " << cut_parts_old[0] << " and " << cut_parts_old[1]
     ;
  }
  const std::string mva_old = cut_.substr(0, 7);
  const std::string wp_old  = cut_.substr(7);

  const std::vector<std::string> cut_parts = edm::tokenize(cut, "&");
  if(cut_parts.size() == 1)
  {
    const std::string cut_new = cut_parts[0];
    const std::string mva_new = cut_new.substr(0, 7);
    const std::string wp_new  = cut_new.substr(7);
    if((mva_old == mva_new && get_tau_id_wp_int(wp_old) > get_tau_id_wp_int(wp_new)) ||
       (mva_old != mva_new))
    {
      std::cout << "Changing tau ID WP from '" << cut_ << "' to '" << cut_new << "'\n";
      set(cut_new);
      return  true;
    }
    else
    {
      std::cout << "Not replacing ID WP '" << cut_ << "' w/ '" << cut_new << "' b/c the new WP is tighter\n";
    }
  }
  else if(cut_parts.size() == 2)
  {
    std::string cut_to_replace, cut_to_keep;
    for(const std::string & cut_new: cut_parts)
    {
      const std::string mva_new = cut_new.substr(0, 7);
      const std::string wp_new  = cut_new.substr(7);

      if(mva_old == mva_new)
      {
        if(get_tau_id_wp_int(wp_old) > get_tau_id_wp_int(wp_new))
        {
          cut_to_replace = cut_new;
        }
        else
        {
          cut_to_replace = cut_;
        }
      }
      else
      {
        cut_to_keep = cut_new;
      }
    }
    if(cut_to_replace.empty() || cut_to_keep.empty())
    {
      throw cmsException(this, __func__, __LINE__)
          << "Unable to replace tau ID WP '" << cut_ << "' with '" << cut << '\''
      ;
    }
    const std::string cut_new = cut_to_replace + "&" + cut_to_keep;
    std::cout << "Changing tau ID WP from '" << cut_ << "' to '" << cut_new << "'\n";
    set(cut_new);
    return true;
  }
  else
  {
    throw cmsException(this, __func__, __LINE__)
      << "More than 2 WPs: " << boost::algorithm::join(cut_parts, ", ") << " is " << cut_parts.size() << " WPs"
    ;
  }

  return false;
}

bool
RecoHadTauSelectorBase::operator()(const RecoHadTau & hadTau) const
{
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

  if(mva_selection_ == MVASelection::kOR)
  {
    if(hadTau.id_mva_dR03() < min_id_mva_dR03_ && hadTau.id_mva_dR05() < min_id_mva_dR05_)
    {
      if(debug_)
      {
        std::cout << "FAILS id_mva_dR03 >= " << min_id_mva_dR03_ << " || id_mva_dR05 >= " << min_id_mva_dR05_ << " cut\n";
      }
      return false;
    }
  }
  else if(mva_selection_ == MVASelection::kNone)
  {
    if(hadTau.id_mva_dR03() < min_id_mva_dR03_)
    {
      if(debug_)
      {
        std::cout << "FAILS id_mva_dR03 >= " << min_id_mva_dR03_ << " cut\n";
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
  }
  else
  {
    assert(0);
  }

  if(hadTau.raw_mva_dR03() < min_raw_mva_dR03_)
  {
    if(debug_)
    {
      std::cout << "FAILS raw_mva_dR03 >= " << min_raw_mva_dR03_ << "cut\n";
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
