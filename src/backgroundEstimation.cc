#include "tthAnalysis/HiggsToTauTau/interface/backgroundEstimation.h"

#include "tthAnalysis/HiggsToTauTau/interface/leptonTypes.h"          // kElectron, kMuon
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // Era::k*

#include <cmath> // std::fabs()
#include <cassert> // assert()

/**
 * @brief Evaluate probability to mismeasure charge of electrons and
 *        muons passing tight charge requirement (Table 33 in AN-2018/098)
 * @param type (either kElectron or kMuon), pT and eta 
 * @return Charge misassignment probability measured in data, to be applied as
 *         event weight to events selected in the OS control region in order to
 *         estimate "charge flip" background in SS signal region
 */
double
prob_chargeMisId(Era era,
                 int lepton_type,
                 double lepton_pt,
                 double lepton_eta,
		 const std::string lep_mva_wp,
		 bool        wTightCharge)
{
  double prob = 1.;

  if ( lep_mva_wp != "hh_multilepton")
  {
    if(lepton_type == kElectron)
    {
      const double abs_lepton_eta = std::fabs(lepton_eta);
      if(era == Era::k2016)
      {
	if(abs_lepton_eta >= 0. && abs_lepton_eta < 1.479)
	{
	  if     (lepton_pt >= 10. && lepton_pt < 25.) prob = 5.56576e-4;
	  else if(lepton_pt >= 25. && lepton_pt < 50.) prob = 9.15632e-5;
	  else if(lepton_pt >= 50.                   ) prob = 1.51503e-4;
	}
	else if(abs_lepton_eta >= 1.479 && abs_lepton_eta < 2.5)
	{
	  if     (lepton_pt >= 10. && lepton_pt < 25.) prob = 6.08021e-4;
	  else if(lepton_pt >= 25. && lepton_pt < 50.) prob = 1.01904e-3;
	  else if(lepton_pt >= 50.                   ) prob = 1.62015e-3;
	}
      }
      else if(era == Era::k2017)
      {
	if(abs_lepton_eta >= 0. && abs_lepton_eta < 1.479)
	{
	  if     (lepton_pt >= 10. && lepton_pt < 25.) prob = 1.18082e-4;
	  else if(lepton_pt >= 25. && lepton_pt < 50.) prob = 5.25915e-5;
	  else if(lepton_pt >= 50.                   ) prob = 1.04939e-4;
	}
	else if(abs_lepton_eta >= 1.479 && abs_lepton_eta < 2.5)
	{
	  if     (lepton_pt >= 10. && lepton_pt < 25.) prob = 4.26689e-4;
	  else if(lepton_pt >= 25. && lepton_pt < 50.) prob = 4.99121e-4;
	  else if(lepton_pt >= 50.                   ) prob = 8.84194e-4;
	}
      }
      else if(era == Era::k2018)
      {
	if(abs_lepton_eta >= 0. && abs_lepton_eta < 1.479)
	{
	  if     (lepton_pt >= 10. && lepton_pt < 25.) prob = 3.50000e-5;
	  else if(lepton_pt >= 25. && lepton_pt < 50.) prob = 6.00118e-5;
	  else if(lepton_pt >= 50.                   ) prob = 1.08467e-4;
	}
	else if(abs_lepton_eta >= 1.479 && abs_lepton_eta < 2.5)
	{
	  if     (lepton_pt >= 10. && lepton_pt < 25.) prob = 3.56487e-4;
	  else if(lepton_pt >= 25. && lepton_pt < 50.) prob = 5.08117e-4;
	  else if(lepton_pt >= 50.                   ) prob = 9.65946e-4;
	}
      }
    }
    else if(lepton_type == kMuon)
    {
      prob = 0.;
    }
    else
    {
      assert(0);
    }
  }
  else 
  { // hh_multilepton
    if ( wTightCharge )
    { // hh_multilepton w/ TightCharge
      if(lepton_type == kElectron)
      {
	const double abs_lepton_eta = std::fabs(lepton_eta);
	if(era == Era::k2016) 
	{ 
	  if(abs_lepton_eta >= 0. && abs_lepton_eta < 1.479) 
	  { 
	    if     (lepton_pt >= 10. && lepton_pt < 25.) prob = 1.26977e-03; // 1.26977e-03 +- 2.54198e-04, wTightCharge 
	    else if(lepton_pt >= 25. && lepton_pt < 50.) prob = 2.46335e-04; // 2.46335e-04 +- 6.53991e-06, wTightCharge 
	    else if(lepton_pt >= 50.                   ) prob = 2.57724e-04; // 2.57724e-04 +- 4.63882e-05, wTightCharge 
	  } 
	  else if(abs_lepton_eta >= 1.479 && abs_lepton_eta < 2.5) 
	  { 
	    if     (lepton_pt >= 10. && lepton_pt < 25.) prob = 1.87976e-03; // 1.87976e-03 +- 1.06149e-04, wTightCharge 
	    else if(lepton_pt >= 25. && lepton_pt < 50.) prob = 3.22252e-03; // 3.22252e-03 +- 5.53815e-05, wTightCharge 
	    else if(lepton_pt >= 50.                   ) prob = 3.45272e-03; // 3.45272e-03 +- 1.02196e-04, wTightCharge 
	  } 
	} 
	else if(era == Era::k2017) 
	{ 
	  if(abs_lepton_eta >= 0. && abs_lepton_eta < 1.479) 
	  { 
	    if     (lepton_pt >= 10. && lepton_pt < 25.) prob = 3.09811e-04; // 3.09811e-04 +- 8.82112e-05, wTightCharge 
	    else if(lepton_pt >= 25. && lepton_pt < 50.) prob = 3.50000e-05; // 3.50000e-05 +- 8.62968e-05, wTightCharge 
	    else if(lepton_pt >= 50.                   ) prob = 1.08334e-04; // 1.08334e-04 +- 2.31315e-05, wTightCharge 
	  } 
	  else if(abs_lepton_eta >= 1.479 && abs_lepton_eta < 2.5) 
	  { 
	    if     (lepton_pt >= 10. && lepton_pt < 25.) prob = 1.35006e-03; // 1.35006e-03 +- 9.30259e-05, wTightCharge 
	    else if(lepton_pt >= 25. && lepton_pt < 50.) prob = 1.63372e-03; // 1.63372e-03 +- 8.18262e-05, wTightCharge 
	    else if(lepton_pt >= 50.                   ) prob = 1.76237e-03; // 1.76237e-03 +- 9.91491e-05, wTightCharge 
	  } 
	} 
	else if(era == Era::k2018) 
	{ 
	  if(abs_lepton_eta >= 0. && abs_lepton_eta < 1.479) 
	  { 
	    if     (lepton_pt >= 10. && lepton_pt < 25.) prob = 2.81745e-04; // 2.81745e-04 +- 5.37271e-05, wTightCharge 
	    else if(lepton_pt >= 25. && lepton_pt < 50.) prob = 1.24803e-04; // 1.24803e-04 +- 6.19475e-06, wTightCharge 
	    else if(lepton_pt >= 50.                   ) prob = 9.26723e-05; // 9.26723e-05 +- 2.29148e-05, wTightCharge 
	  } 
	  else if(abs_lepton_eta >= 1.479 && abs_lepton_eta < 2.5) 
	  { 
	    if     (lepton_pt >= 10. && lepton_pt < 25.) prob = 8.99672e-04; // 8.99672e-04 +- 6.17177e-05, wTightCharge 
	    else if(lepton_pt >= 25. && lepton_pt < 50.) prob = 1.29464e-03; // 1.29464e-03 +- 6.63515e-05, wTightCharge 
	    else if(lepton_pt >= 50.                   ) prob = 1.58391e-03; // 1.58391e-03 +- 6.36324e-05, wTightCharge 
	  } 
	}
      }
      else if(lepton_type == kMuon)
      {
	prob = 0.;
      }
      else
      {
	assert(0);
      }      
    }
    else
    { // hh_multilepton w/o TightCharge
      if(lepton_type == kElectron)
      {
	const double abs_lepton_eta = std::fabs(lepton_eta);
	if(era == Era::k2016) 
	{ 
	  if(abs_lepton_eta >= 0. && abs_lepton_eta < 1.479) 
	  { 
	    if     (lepton_pt >= 10. && lepton_pt < 25.) prob = 1.73323e-03; // 1.73323e-03 +- 1.68237e-04, woTightCharge 
	    else if(lepton_pt >= 25. && lepton_pt < 50.) prob = 2.33808e-03; // 2.33808e-03 +- 1.60294e-05, woTightCharge 
	    else if(lepton_pt >= 50.                   ) prob = 3.13454e-03; // 3.13454e-03 +- 9.48521e-05, woTightCharge 
	  } 
	  else if(abs_lepton_eta >= 1.479 && abs_lepton_eta < 2.5) 
	  { 
	    if     (lepton_pt >= 10. && lepton_pt < 25.) prob = 9.35101e-03; // 9.35101e-03 +- 1.63805e-04, woTightCharge 
	    else if(lepton_pt >= 25. && lepton_pt < 50.) prob = 1.56746e-02; // 1.56746e-02 +- 2.67618e-04, woTightCharge 
	    else if(lepton_pt >= 50.                   ) prob = 2.31998e-02; // 2.31998e-02 +- 2.57037e-04, woTightCharge 
	  } 
	} 
	else if(era == Era::k2017) 
	{ 
	  if(abs_lepton_eta >= 0. && abs_lepton_eta < 1.479) 
	  { 
	    if     (lepton_pt >= 10. && lepton_pt < 25.) prob = 1.53862e-03; // 1.53862e-03 +- 1.37339e-04, woTightCharge 
	    else if(lepton_pt >= 25. && lepton_pt < 50.) prob = 1.52094e-03; // 1.52094e-03 +- 2.59404e-04, woTightCharge 
	    else if(lepton_pt >= 50.                   ) prob = 1.39978e-03; // 1.39978e-03 +- 7.37236e-05, woTightCharge 
	  } 
	  else if(abs_lepton_eta >= 1.479 && abs_lepton_eta < 2.5) 
	  { 
	    if     (lepton_pt >= 10. && lepton_pt < 25.) prob = 5.15612e-03; // 5.15612e-03 +- 2.17592e-04, woTightCharge 
	    else if(lepton_pt >= 25. && lepton_pt < 50.) prob = 7.58614e-03; // 7.58614e-03 +- 2.65292e-04, woTightCharge 
	    else if(lepton_pt >= 50.                   ) prob = 1.07534e-02; // 1.07534e-02 +- 3.11587e-04, woTightCharge 
	  } 
	} 
	else if(era == Era::k2018) 
	{ 
	  if(abs_lepton_eta >= 0. && abs_lepton_eta < 1.479) 
	  { 
	    if     (lepton_pt >= 10. && lepton_pt < 25.) prob = 1.31994e-03; // 1.31994e-03 +- 1.13166e-04, woTightCharge 
	    else if(lepton_pt >= 25. && lepton_pt < 50.) prob = 7.96068e-04; // 7.96068e-04 +- 3.03981e-04, woTightCharge 
	    else if(lepton_pt >= 50.                   ) prob = 1.50958e-03; // 1.50958e-03 +- 6.50541e-05, woTightCharge 
	  } 
	  else if(abs_lepton_eta >= 1.479 && abs_lepton_eta < 2.5) 
	  { 
	    if     (lepton_pt >= 10. && lepton_pt < 25.) prob = 5.15070e-03; // 5.15070e-03 +- 2.75222e-04, woTightCharge 
	    else if(lepton_pt >= 25. && lepton_pt < 50.) prob = 8.41303e-03; // 8.41303e-03 +- 3.08113e-04, woTightCharge 
	    else if(lepton_pt >= 50.                   ) prob = 1.44350e-02; // 1.44350e-02 +- 4.52523e-04, woTightCharge 
	  } 
	} 
      }
      else if(lepton_type == kMuon)
      {
	prob = 0.;
      }
      else
      {
	assert(0);
      }
    }  
  }  



  
  return prob;
}
