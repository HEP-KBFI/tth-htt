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
  , max_dxy_(1000.)
  , max_dz_(0.2)
  , apply_decayModeFinding_(TauDecayModeE::kOld)
  , min_antiElectron_(DEFAULT_TAUID_ID_VALUE)
  , min_antiMuon_(DEFAULT_TAUID_ID_VALUE)
{
  for(const auto & kv: TauID_levels)
  {
    min_id_mva_[kv.first] = DEFAULT_TAUID_ID_VALUE;
    min_raw_mva_[kv.first] = DEFAULT_TAUID_RAW_VALUE;
  }
}

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
RecoHadTauSelectorBase::set_min_id_mva(TauID tauId,
                                       int min_id_mva)
{
  if(! min_id_mva_.count(tauId))
  {
    throw cmsException(this, __func__, __LINE__)
      << "Unrecognizable tau ID = " << as_integer(tauId)
    ;
  }
  min_id_mva_[tauId] = min_id_mva;
}

void
RecoHadTauSelectorBase::set_min_raw_mva(TauID tauId,
                                        double min_raw_mva)
{
  if(! min_raw_mva_.count(tauId))
  {
    throw cmsException(this, __func__, __LINE__)
      << "Unrecognizable tau ID = " << as_integer(tauId)
    ;
  }
  min_raw_mva_[tauId] = min_raw_mva;
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

  const std::vector<std::string> cut_parts = edm::tokenize(cut, TAU_WP_SEPARATOR);

  for(const std::string & cut_part: cut_parts)
  {
    const std::string mva_type = cut_part.substr(0, 7);
    if(! TauID_PyMap.count(mva_type))
    {
      throw cmsException(this, __func__, __LINE__)
        << "Unrecognizable tau discriminator '" << mva_type << "' found in string: " << cut
      ;
    }
    const TauID tauId = TauID_PyMap.at(mva_type);
    const std::string wp = cut_part.substr(7);
    const int wp_int = get_tau_id_wp_int(tauId, wp);
    set_min_id_mva(tauId, wp_int);
    if(tauId == TauID::DeepTau2017v2VSe ||
       tauId == TauID::DeepTau2017v2VSmu ||
       tauId == TauID::DeepTau2017v2VSjet)
    {
      apply_decayModeFinding_ = TauDecayModeE::kDeep;
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
  std::cout << "Attempting to replace cut from '" << cut_ << "' to '" << cut << "'\n";

  // if the old cut is an OR of multiple WPs, then throw an error; otherwise loop over individual cuts and decide:
  // i) if the MVA WP from the new cut is strictly looser than the old WP, then replace it w/ the new WP
  // ii) if the MVA WP from the new cut is not strictly looser than the old WP, then keep the cut as is
  const std::vector<std::string> cut_parts_old = edm::tokenize(cut_, TAU_WP_SEPARATOR);
  if(cut_parts_old.size() != 1)
  {
    throw cmsException(this, __func__, __LINE__)
        << "Can overwrite a single tau ID WP but got more of them: " << boost::algorithm::join(cut_parts_old, ", ")
     ;
  }
  const std::string mva_old = cut_.substr(0, 7);
  const TauID tauId_old = TauID_PyMap.at(mva_old);
  const std::string wp_old  = cut_.substr(7);
  const int wp_int_old = get_tau_id_wp_int(tauId_old, wp_old);

  std::string cut_new = "";
  const std::vector<std::string> cut_parts = edm::tokenize(cut, TAU_WP_SEPARATOR);
  for(const std::string & cut_part: cut_parts)
  {
    const std::string mva_new = cut_part.substr(0, 7);
    const TauID tauId_new = TauID_PyMap.at(mva_new);

    std::string cut_part_new = cut_part;
    if(tauId_new == tauId_old)
    {
      const std::string wp_new  = cut_part.substr(7);
      const int wp_int_new = get_tau_id_wp_int(tauId_new, wp_new);
      if(wp_int_new < wp_int_old)
      {
        cut_part_new = mva_old + wp_new;
        std::cout << "Relaxing old cut for '" << mva_new << "' from '" << wp_old << "' to '" << wp_new << "'\n";
      }
      else
      {
        cut_part_new = mva_old + wp_old;
        std::cout << "Keeping old cut for '" << mva_new << "' at '" << wp_old << "'\n";
      }
    }

    if(! cut_new.empty())
    {
      cut_new += TAU_WP_SEPARATOR;
    }
    cut_new += cut_part_new;
  }

  if(cut_ != cut_new)
  {
    std::cout << "Changed tau ID WP from '" << cut_ << "' to '" << cut_new << "'\n";
    set(cut_new);
    return true;
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
  if(! hadTau.decayModeFinding(apply_decayModeFinding_))
  {
    if(debug_)
    {
      std::cout << "FAILS decayModeFinding cut = " << as_integer(apply_decayModeFinding_) << "\n";
    }
    return false;
  }

  std::vector<TauID> min_id_mva_cuts;
  for(const auto & kv: min_id_mva_)
  {
    if(kv.second > DEFAULT_TAUID_ID_VALUE)
    {
      min_id_mva_cuts.push_back(kv.first);
    }
  }
  if(! min_id_mva_cuts.empty() &&
     std::none_of(min_id_mva_cuts.begin(), min_id_mva_cuts.end(),
       [this, &hadTau](TauID tauId) -> bool
        {
          return hadTau.id_mva(tauId) >= min_id_mva_.at(tauId);
        }
      )
    )
  {
    if(debug_)
    {
      std::cout << "FAILS id_mva cuts: ";
      for(std::size_t min_id_mva_idx = 0; min_id_mva_idx < min_id_mva_cuts.size(); ++min_id_mva_idx)
      {
        const TauID tauId = min_id_mva_cuts[min_id_mva_idx];
        std::cout << "id" << TauID_names.at(tauId) << " (= " << hadTau.id_mva(tauId) << ") >= " << min_id_mva_.at(tauId);
        if(min_id_mva_idx < min_id_mva_cuts.size() - 1)
        {
          std::cout << " OR ";
        }
        else
        {
          std::cout << '\n';
        }
      }
    }
    return false;
  }

  std::vector<TauID> min_raw_mva_cuts;
  for(const auto & kv: min_raw_mva_)
  {
    if(kv.second > DEFAULT_TAUID_RAW_VALUE)
    {
      min_raw_mva_cuts.push_back(kv.first);
    }
  }
  if(! min_raw_mva_cuts.empty() &&
     std::none_of(min_raw_mva_cuts.begin(), min_raw_mva_cuts.end(),
       [this, &hadTau](TauID tauId) -> bool
        {
          return hadTau.raw_mva(tauId) >= min_raw_mva_.at(tauId);
        }
      )
    )
  {
    if(debug_)
    {
      std::cout << "FAILS raw_mva cuts: ";
      for(std::size_t min_raw_mva_idx = 0; min_raw_mva_idx < min_raw_mva_cuts.size(); ++min_raw_mva_idx)
      {
        const TauID tauId = min_raw_mva_cuts[min_raw_mva_idx];
        std::cout << "raw" << TauID_names.at(tauId) << " (= " << hadTau.raw_mva(tauId) << ") >= " << min_raw_mva_.at(tauId);
        if(min_raw_mva_idx < min_raw_mva_cuts.size() - 1)
        {
          std::cout << " OR ";
        }
        else
        {
          std::cout << '\n';
        }
      }
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
