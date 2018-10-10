#include "tthAnalysis/HiggsToTauTau/interface/MEMPermutationWriter.h" // MEMPermutationWriter

#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // z_mass, z_window, kLoose, kMedium, kTight, id_mva_dr0*_map
#include "tthAnalysis/HiggsToTauTau/interface/memAuxFunctions.h" // get_memPermutationBranchName()
#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h" // RecoLepton
#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

#include <TTree.h> // TTree

#include <boost/algorithm/string/predicate.hpp> // boost::starts_with()
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wswitch-enum"
#include <boost/algorithm/string/split.hpp> // boost::split()
#pragma GCC diagnostic pop

MEMPermutationWriter::~MEMPermutationWriter()
{
  for(auto & kv: hadTauSelectorsLoose_)
  {
    if(hadTauSelectorsLoose_[kv.first])
    {
      delete hadTauSelectorsLoose_[kv.first];
      hadTauSelectorsLoose_[kv.first] = nullptr;
    }
    if(hadTauSelectorsFakeable_[kv.first])
    {
      delete hadTauSelectorsFakeable_[kv.first];
      hadTauSelectorsFakeable_[kv.first] = nullptr;
    }
    if(hadTauSelectorsTight_[kv.first])
    {
      delete hadTauSelectorsTight_[kv.first];
      hadTauSelectorsTight_[kv.first] = nullptr;
    }
  }
}

MEMPermutationWriter &
MEMPermutationWriter::setLepSelection(int minLepSelection,
                                      int maxLepSelection)
{
  minLepSelection_ = minLepSelection;
  maxLepSelection_ = maxLepSelection;
  return *this;
}

MEMPermutationWriter &
MEMPermutationWriter::setHadTauSelection(int minHadTauSelection,
                                         int maxHadTauSelection)
{
  minHadTauSelection_ = minHadTauSelection;
  maxHadTauSelection_ = maxHadTauSelection;
  return *this;
}

MEMPermutationWriter &
MEMPermutationWriter::setHadTauWorkingPoints(const std::string & minHadTauWorkingPoint)
{
  std::vector<std::string> cut_parts;
  boost::split(cut_parts, minHadTauWorkingPoint, [](char c) -> bool { return c == '&'; });
  assert(cut_parts.size() == 1 || cut_parts.size() == 2);

  std::map<std::string, int> cut_mvas;
  for(const std::string & cut_part: cut_parts)
  {
    const std::string cut_mva = cut_part.substr(0, 7);
    const std::string cut_wp_str = cut_part.substr(7);
    const int cut_wp = get_tau_id_wp_int(cut_wp_str);
    cut_mvas[cut_mva] = cut_wp;
  }

  const int tau_max_selection = get_tau_id_wp_int("VVTight");
  for(const auto & kv: cut_mvas)
  {
    const int tau_min_selection = kv.second;
    for(int tau_selection = tau_min_selection; tau_selection <= tau_max_selection; ++tau_selection)
    {
      const std::string hadTauWorkingPoint = kv.first + get_tau_id_wp_str(tau_selection);
      hadTauWorkingPoints_.push_back(hadTauWorkingPoint);
    }
  }
  return *this;
}

MEMPermutationWriter &
MEMPermutationWriter::addCondition(const std::string & channel,
                                   const MEMPremutationCondition & condition)
{
  if(conditions_.count(channel))
  {
    throw cmsException(this, __func__) << "Channel '" << channel << "' already supplied";
  }
  conditions_[channel] = condition;
  return *this;
}

MEMPermutationWriter &
MEMPermutationWriter::addCondition(const std::string & channel,
                                   unsigned minSelLeptons,
                                   unsigned minSelHadTaus,
                                   unsigned minSelBJets_loose,
                                   unsigned minSelBJets_medium)
{
  const MEMPremutationCondition condition = [
      minSelLeptons, minSelHadTaus, minSelBJets_loose, minSelBJets_medium
    ](
      const std::vector<const RecoLepton *> & selLeptons,
      const std::vector<const RecoHadTau *> & selHadTaus,
      const std::vector<const RecoJet *> & selBJets_loose,
      const std::vector<const RecoJet *> & selBJets_medium,
      bool failsZbosonMassVeto
    ) -> int
  {
    return (
        (selBJets_loose.size() >= minSelBJets_loose || selBJets_medium.size() >= minSelBJets_medium) &&
        ! failsZbosonMassVeto                                                                        &&
        selLeptons.size() >= minSelLeptons                                                           &&
        selHadTaus.size() >= minSelHadTaus
    ) ? nCombinationsK(selLeptons.size(), minSelLeptons) * nCombinationsK(selHadTaus.size(), minSelHadTaus) : 0;
  };
  return addCondition(channel, condition);
}

void
MEMPermutationWriter::setBranchNames(TTree * tree,
                                     int era,
                                     bool verbose)
{
  // initialize the selector classes
  for(const std::string & hadTauWorkingPoint: hadTauWorkingPoints_)
  {
    hadTauSelectorsLoose_[hadTauWorkingPoint] = new RecoHadTauCollectionSelectorLoose(era);
    hadTauSelectorsLoose_[hadTauWorkingPoint] -> set(hadTauWorkingPoint);
    hadTauSelectorsLoose_[hadTauWorkingPoint] -> set_min_antiElectron(-1);
    hadTauSelectorsLoose_[hadTauWorkingPoint] -> set_min_antiMuon(-1);
    hadTauSelectorsLoose_[hadTauWorkingPoint] -> set_min_pt(18.);

    hadTauSelectorsFakeable_[hadTauWorkingPoint] = new RecoHadTauCollectionSelectorFakeable(era);
    hadTauSelectorsFakeable_[hadTauWorkingPoint] -> set(hadTauWorkingPoint);
    hadTauSelectorsFakeable_[hadTauWorkingPoint] -> set_min_antiElectron(-1);
    hadTauSelectorsFakeable_[hadTauWorkingPoint] -> set_min_antiMuon(-1);
    hadTauSelectorsFakeable_[hadTauWorkingPoint] -> set_min_pt(18.);

    hadTauSelectorsTight_[hadTauWorkingPoint] = new RecoHadTauCollectionSelectorTight(era);
    hadTauSelectorsTight_[hadTauWorkingPoint] -> set(hadTauWorkingPoint);
    hadTauSelectorsTight_[hadTauWorkingPoint] -> set_min_antiElectron(-1);
    hadTauSelectorsTight_[hadTauWorkingPoint] -> set_min_antiMuon(-1);
    hadTauSelectorsTight_[hadTauWorkingPoint] -> set_min_pt(18.);
  }

  // initialize the branches
  for(const auto & kv: conditions_)
  {
    const std::string & channel = kv.first;
    branches_[channel] = {};
    for(int leptonSelection_idx = minLepSelection_; leptonSelection_idx <= maxLepSelection_; ++leptonSelection_idx)
    {
      const std::string leptonSelection_str = find_selection_str(leptonSelection_idx);
      branches_[channel][leptonSelection_idx] = {};
      for(int hadTauSelection_idx = minHadTauSelection_; hadTauSelection_idx <= maxHadTauSelection_; ++hadTauSelection_idx)
      {
        const std::string hadTauSelection_str = find_selection_str(hadTauSelection_idx);
        branches_[channel][leptonSelection_idx][hadTauSelection_idx] = {};
        for(const std::string & hadTauWorkingPoint: hadTauWorkingPoints_)
        {
          const std::string maxPermutations_addMEM_str = get_memPermutationBranchName(
            channel, leptonSelection_str, hadTauSelection_str, hadTauWorkingPoint
          );
          branches_[channel][leptonSelection_idx][hadTauSelection_idx][hadTauWorkingPoint] = 0;
          tree -> Branch(
            maxPermutations_addMEM_str.c_str(),
            &branches_[channel][leptonSelection_idx][hadTauSelection_idx][hadTauWorkingPoint],
            Form("%s/I", maxPermutations_addMEM_str.c_str())
          );
          if(verbose)
          {
            std::cout << "adding branch: " << maxPermutations_addMEM_str << " (type = I)\n";
          } // verbose
        } // hadTauWorkingPoint
      } // hadTauSelection_idx
    } // leptonSelection_idx
  } // kv
  return;
}

void
MEMPermutationWriter::write(const std::array<const std::vector<const RecoLepton*>, 3> & leptons,
                            const std::array<const std::vector<const RecoJet*>, 2> & selBJets,
                            const std::vector<const RecoHadTau*> & cleanedHadTaus)
{
  // compute if the event passes the Z boson veto
  bool failsZbosonMassVeto = false;
  const std::vector<const RecoLepton*> & fakeableLeptons = leptons.at(kFakeable);
  for(std::size_t lepton1_idx = 0; lepton1_idx < fakeableLeptons.size(); ++lepton1_idx)
  {
    for(std::size_t lepton2_idx = lepton1_idx + 1; lepton2_idx < fakeableLeptons.size(); ++lepton2_idx)
    {
      const RecoLepton* lepton1 = fakeableLeptons.at(lepton1_idx);
      const RecoLepton* lepton2 = fakeableLeptons.at(lepton2_idx);
      const double mass = (lepton1->p4() + lepton2->p4()).mass();
      if(lepton1->is_electron() && lepton2->is_electron() && std::fabs(mass - z_mass) < z_window)
      {
        failsZbosonMassVeto = true;
      }
    } // lepton2_idx
  } // lepton1_idx

  // get the b jets
  const std::vector<const RecoJet *> & selBJets_loose  = selBJets.at(0);
  const std::vector<const RecoJet *> & selBJets_medium = selBJets.at(1);

  // loop over the lepton, had tau and had tau wp branches
  for(int leptonSelection_idx = minLepSelection_; leptonSelection_idx <= maxLepSelection_; ++leptonSelection_idx)
  {
    const std::vector<const RecoLepton *> & selLeptons = leptons.at(leptonSelection_idx);
    for(int hadTauSelection_idx = minHadTauSelection_; hadTauSelection_idx <= maxHadTauSelection_; ++hadTauSelection_idx)
    {
      for(const std::string & hadTauWorkingPoint: hadTauWorkingPoints_)
      {
        const std::vector<const RecoHadTau *> selHadTaus = [&]()
        {
          // pick the had tau selector
          switch(hadTauSelection_idx)
          {
            case kLoose:    return (*hadTauSelectorsLoose_   [hadTauWorkingPoint])(cleanedHadTaus);
            case kFakeable: return (*hadTauSelectorsFakeable_[hadTauWorkingPoint])(cleanedHadTaus);
            case kTight:    return (*hadTauSelectorsTight_   [hadTauWorkingPoint])(cleanedHadTaus);
            default:        throw cmsException(this, __func__) << "Unexpected had tau selection: " << hadTauSelection_idx;
          }
        }(); // selHadTaus

        // loop over the channels and assign an estimate for the MEM permutations
        for(const auto & kv: branches_)
        {
          const std::string & channel = kv.first;
          branches_[channel][leptonSelection_idx][hadTauSelection_idx][hadTauWorkingPoint] =
            conditions_[channel](selLeptons, selHadTaus, selBJets_loose, selBJets_medium, failsZbosonMassVeto);
        } // branches
      } // hadTauWorkingPoint
    } // hadTauSelection_idx
  } // leptonSelection_idx
  return;
}

std::string
MEMPermutationWriter::find_selection_str(int selection_idx)
{
  if(selection_idx == kLoose)    return "Loose";
  if(selection_idx == kFakeable) return "Fakeable";
  if(selection_idx == kTight)    return "Tight";
  throw cmsException(__func__, __LINE__) << "Invalid index: " << selection_idx;
}
