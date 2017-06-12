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

std::string getPtBin(double minPt, double maxPt)
{
  std::string PtBin = "";
  if ( minPt > 0. && maxPt > 0. ) PtBin.append(Form("Pt%1.1fto%1.1f", minPt, maxPt));
  else if ( minPt > 0. ) PtBin.append(Form("PtGt%1.1f", minPt));
  else if ( maxPt > 0. ) PtBin.append(Form("PtLt%1.1f", maxPt));
  PtBin = TString(PtBin.data()).ReplaceAll(".", "_").Data();
  return PtBin;
}
