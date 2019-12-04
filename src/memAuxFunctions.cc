#include "tthAnalysis/HiggsToTauTau/interface/memAuxFunctions.h" // get_addMEM_systematics()

#include <TString.h> // Form()

#include <numeric> // std::accumulate(), std::inner_product()
#include <algorithm> // std::transform()

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

double
square_product_sum(const std::vector<double> & lhs,
           const std::vector<double> & rhs)
{
  std::vector<double> products;
  std::transform(
    lhs.cbegin(), lhs.cend(),
    rhs.cbegin(), std::back_inserter(products),
    std::multiplies<double>()
  );
  return std::inner_product(
    products.cbegin(), products.cend(), products.cbegin(), 0.
  );
}

double
nan_protection(double value,
               double reset_value)
{
  return std::isnan(value) ? reset_value : value;
}

std::tuple<double, double, bool>
compMEMLR(const std::vector<double> & signal_probabilities,
          const std::vector<double> & background_probabilities,
          const std::vector<double> & signal_probability_errors,
          const std::vector<double> & background_probability_errors,
          const std::vector<double> & signal_kappas,
          const std::vector<double> & background_kappas)
{
  const std::vector<double> signal_weights = reset_or_assign(signal_kappas, signal_probabilities.size(), 1.);
  const std::vector<double> background_weights = reset_or_assign(background_kappas, background_probabilities.size(), 1.);

  const double signal_sums = std::inner_product(
    signal_probabilities.cbegin(), signal_probabilities.cend(),
    signal_weights.cbegin(), 0.
  );
  const double background_sums = std::inner_product(
    background_probabilities.cbegin(), background_probabilities.cend(),
    background_weights.cbegin(), 0.
  );
  const double & numerator = signal_sums;
  const double denominator = numerator + background_sums;
  if(denominator > 0.)
  {
    const double LR = numerator / denominator;

    const std::vector<double> signal_errors = reset_or_assign(
      signal_probability_errors, signal_probabilities.size(), 0.
    );
    const std::vector<double> background_errors = reset_or_assign(
      background_probability_errors, background_probabilities.size(), 0.
    );
    const double signal_error_square_sum = square_product_sum(signal_errors, signal_weights);
    const double background_error_square_sum = square_product_sum(background_errors, background_weights);

    const double LR_error = std::sqrt(
      background_sums * background_sums * signal_error_square_sum +
      signal_sums     * signal_sums     * background_error_square_sum
    ) / (denominator * denominator);
    return std::make_tuple(LR, LR_error, true);
  }
  else
  {
    return std::make_tuple(-1., 0., false);
  }
}
