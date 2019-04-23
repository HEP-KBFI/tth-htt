#include "tthAnalysis/HiggsToTauTau/interface/memAuxFunctions.h" // get_addMEM_systematics()

#include <TString.h> // Form()

std::string
get_memBranchName(const std::string & identifier,
                  const std::string & channel,
                  const std::string & lepSelection)
{
  return get_memBranchName(identifier, channel, lepSelection, "", "");
}

std::string
get_memBranchName(const std::string & identifier,
                  const std::string & channel,
                  const std::string & lepSelection,
                  const std::string & hadTauSelection,
                  const std::string & hadTauWorkingPoint)
{
  if ( hadTauSelection != "" )
  {
    return Form(
      "%s_%s_lep%s_tau%s_%s",
      identifier.data(), channel.data(), lepSelection.data(), hadTauSelection.data(), hadTauWorkingPoint.data()
    );
  }
  else 
  {
    return Form(
      "%s_%s_lep%s",
      identifier.data(), channel.data(), lepSelection.data()
    );
  }
}

std::string
get_memObjectBranchName(const std::string & channel,
                        const std::string & lepSelection)
{
  return get_memObjectBranchName(channel, lepSelection, "", "");
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
                             const std::string & lepSelection)
{
  return get_memPermutationBranchName(channel, lepSelection, "", "");
}

std::string
get_memPermutationBranchName(const std::string & channel,
                             const std::string & lepSelection,
                             const std::string & hadTauSelection,
                             const std::string & hadTauWorkingPoint)
{
  return get_memBranchName("maxPermutations_addMEM", channel, lepSelection, hadTauSelection, hadTauWorkingPoint);
}
