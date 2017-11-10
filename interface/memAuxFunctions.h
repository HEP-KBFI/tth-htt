#ifndef MEMAUXFUNCTIONS_H
#define MEMAUXFUNCTIONS_H

#include <string> // std::string

int
get_addMEM_systematics(const std::string & central_or_shift,
                       int & jetPt_option,
                       int & hadTauPt_option,
                       int & met_option);

std::string
get_memBranchName(const std::string & identifier,
                  const std::string & channel,
                  const std::string & lepSelection,
                  const std::string & hadTauSelection,
                  const std::string & hadTauWorkingPoint);

std::string
get_memObjectBranchName(const std::string & channel,
                        const std::string & lepSelection,
                        const std::string & hadTauSelection,
                        const std::string & hadTauWorkingPoint);

std::string
get_memPermutationBranchName(const std::string & channel,
                             const std::string & lepSelection,
                             const std::string & hadTauSelection,
                             const std::string & hadTauWorkingPoint);

#endif // MEMAUXFUNCTIONS_H
