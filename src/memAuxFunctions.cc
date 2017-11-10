#include "tthAnalysis/HiggsToTauTau/interface/memAuxFunctions.h" // get_addMEM_systematics()

#include "tthAnalysis/HiggsToTauTau/interface/RecoJetReader.h" // RecoJetReader::
#include "tthAnalysis/HiggsToTauTau/interface/RecoMEtReader.h" // kMEt_*
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauReader.h" // RecoHadTauReader::

#include <TString.h> // Form()

#include <boost/algorithm/string/predicate.hpp> // boost::algorithm::starts_with(), boost::algorithm::ends_with()

int
get_addMEM_systematics(const std::string & central_or_shift,
                       int & jetPt_option,
                       int & hadTauPt_option,
                       int & met_option)
{
  if(boost::algorithm::starts_with(central_or_shift, "CMS_ttHl_JES"))
  {
    if(boost::algorithm::ends_with(central_or_shift, "Up"))
    {
      jetPt_option = RecoJetReader::kJetPt_jecUp;
      met_option   = kMEt_shifted_JetEnUp;
    }
    else if(boost::algorithm::ends_with(central_or_shift, "Down"))
    {
      jetPt_option = RecoJetReader::kJetPt_jecDown;
      met_option   = kMEt_shifted_JetEnDown;
    }
    else
    {
      std::cerr << "Invalid JES systematics: " << central_or_shift;
      throw 1;
    }
  }
  else if(boost::algorithm::starts_with(central_or_shift, "CMS_ttHl_tauES"))
  {
    if(boost::algorithm::ends_with(central_or_shift, "Up"))
    {
      hadTauPt_option = RecoHadTauReader::kHadTauPt_shiftUp;
    }
    else if(boost::algorithm::ends_with(central_or_shift, "Down"))
    {
      hadTauPt_option = RecoHadTauReader::kHadTauPt_shiftDown;
    }
    else
    {
      std::cerr << "Invalid tauES systematics: " << central_or_shift << '\n';
      throw 1;
    }
  }
  else if(boost::algorithm::starts_with(central_or_shift, "CMS_ttHl_JER"))
  {
    if(boost::algorithm::ends_with(central_or_shift, "Up"))
    {
      met_option = kMEt_shifted_JetResUp;
    }
    else if(boost::algorithm::ends_with(central_or_shift, "Down"))
    {
      met_option = kMEt_shifted_JetResDown;
    }
    else
    {
      std::cerr << "Invalid JER systematics: " << central_or_shift << '\n';
      throw 1;
    }
  }
  else if(boost::algorithm::starts_with(central_or_shift, "CMS_ttHl_UnclusteredEn"))
  {
    if(boost::algorithm::ends_with(central_or_shift, "Up"))
    {
      met_option = kMEt_shifted_UnclusteredEnUp;
    }
    else if(boost::algorithm::ends_with(central_or_shift, "Down"))
    {
      met_option = kMEt_shifted_UnclusteredEnDown;
    }
    else
    {
      std::cerr << "Invalid UnclusteredEn systematics: " << central_or_shift << '\n';
      throw 1;
    }
  }
  else if(central_or_shift != "central")
  {
    return 1;
  }

  return 0;
}

std::string
get_memBranchName(const std::string & identifier,
                  const std::string & channel,
                  const std::string & lepSelection,
                  const std::string & hadTauSelection,
                  const std::string & hadTauWorkingPoint)
{
  return Form(
    "%s_%s_lep%s_tau%s_%s",
    identifier.data(), channel.data(), lepSelection.data(), hadTauSelection.data(), hadTauWorkingPoint.data()
  );
}

std::string
get_memObjectBranchName(const std::string & channel,
                        const std::string & lepSelection,
                        const std::string & hadTauSelection,
                        const std::string & hadTauWorkingPoint)
{
  return get_memBranchName("memObjects", channel, lepSelection, hadTauSelection, hadTauWorkingPoint);
}

std::string
get_memPermutationBranchName(const std::string & channel,
                             const std::string & lepSelection,
                             const std::string & hadTauSelection,
                             const std::string & hadTauWorkingPoint)
{
  return get_memBranchName("maxPermutations_addMEM", channel, lepSelection, hadTauSelection, hadTauWorkingPoint);
}
