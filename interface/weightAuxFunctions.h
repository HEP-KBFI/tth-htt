#ifndef tthAnalysis_HiggsToTauTau_weightAuxFunctions_h
#define tthAnalysis_HiggsToTauTau_weightAuxFunctions_h

double
get_tHq_sf(double kt,
           double kv)
{
  return 2.63 * kt * kt + 3.588 * kv * kv - 5.21 * kt * kv;
}

double
get_tHW_sf(double kt,
           double kv)
{
  return 2.91 * kt * kt + 2.31 * kv * kv - 4.22 * kt * kv;
}

#endif
