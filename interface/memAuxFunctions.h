#ifndef MEMAUXFUNCTIONS_H
#define MEMAUXFUNCTIONS_H

#include <string> // std::string
#include <vector> // std::vector<>
#include <tuple> // std::tuple<..>
#include <cassert> // std::assert()

std::string
get_memBranchName(const std::string & identifier,
                  const std::string & channel,
                  const std::string & lepSelection);
std::string
get_memBranchName(const std::string & identifier,
                  const std::string & channel,
                  const std::string & lepSelection,
                  const std::string & hadTauSelection,
                  const std::string & hadTauWorkingPoint);

std::string
get_memObjectBranchName(const std::string & channel,
                        const std::string & lepSelection);
std::string
get_memObjectBranchName(const std::string & channel,
                        const std::string & lepSelection,
                        const std::string & hadTauSelection,
                        const std::string & hadTauWorkingPoint);

std::string
get_memPermutationBranchName(const std::string & channel,
                             const std::string & lepSelection);
std::string
get_memPermutationBranchName(const std::string & channel,
                             const std::string & lepSelection,
                             const std::string & hadTauSelection,
                             const std::string & hadTauWorkingPoint);

template <typename T>
std::vector<T>
reset_or_assign(const std::vector<T> & original_values,
                std::size_t reference_size,
                T value)
{
  std::vector<double> new_values;
  if(! original_values.empty())
  {
    assert(original_values.size() == reference_size);
    new_values = original_values;
  }
  else
  {
    new_values.resize(reference_size, value);
  };
  return new_values;
}

double
square_product_sum(const std::vector<double> & lhs,
                   const std::vector<double> & rhs);

double
nan_protection(double value,
               double reset_value = 0.);

std::tuple<double, double, bool>
compMEMLR(const std::vector<double> & signal_probabilities,
          const std::vector<double> & background_probabilities,
          const std::vector<double> & signal_probability_errors = {},
          const std::vector<double> & background_probability_errors = {},
          const std::vector<double> & signal_kappas = {},
          const std::vector<double> & background_kappas = {});

#endif // MEMAUXFUNCTIONS_H
