#include "tthAnalysis/HiggsToTauTau/interface/jetToTauFakeRateAuxFunctions.h"

#include <TString.h> // TString, Form

std::string getEtaBin(double minAbsEta, double maxAbsEta)
{
  std::string absEtaBin = "";
  if      ( minAbsEta > 0. && maxAbsEta > 0. ) absEtaBin.append(Form("absEta%1.1fto%1.1f", minAbsEta, maxAbsEta));
  else if ( minAbsEta > 0.                   ) absEtaBin.append(Form("absEtaGt%1.1f", minAbsEta));
  else if (                   maxAbsEta > 0. ) absEtaBin.append(Form("absEtaLt%1.1f", maxAbsEta));
  absEtaBin = TString(absEtaBin.data()).ReplaceAll(".", "_").Data();
  return absEtaBin;
}
