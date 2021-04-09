#include "tthAnalysis/HiggsToTauTau/interface/HHWeightInterfaceCouplings.h"
#include "tthAnalysis/HiggsToTauTau/interface/HHWeightInterfaceNLO.h"

int
main(int argc,
     char ** argv)
{
  edm::ParameterSet hhWeight;
  hhWeight.addParameter<std::string>("denominator_file_lo", "");
  hhWeight.addParameter<std::string>("denominator_file_nlo", "hhAnalysis/multilepton/data/denom_2017_nlo.root");
  hhWeight.addParameter<std::string>("klScan_file", "");
  hhWeight.addParameter<std::string>("ktScan_file", "");
  hhWeight.addParameter<std::string>("c2Scan_file", "");
  hhWeight.addParameter<std::string>("cgScan_file", "");
  hhWeight.addParameter<std::string>("c2gScan_file", "");
  hhWeight.addParameter<std::string>("coefFile", "HHStatAnalysis/AnalyticalModels/data/coefficientsByBin_extended_3M_costHHSim_19-4.txt");
  hhWeight.addParameter<std::string>("histtitle", "signal_ggf_nonresonant_hh_wwww");
  hhWeight.addParameter<bool>("isDEBUG", false);
  hhWeight.addParameter<bool>("apply_rwgt_lo", false);
  hhWeight.addParameter<std::string>("scanMode", "default");
  hhWeight.addParameter<bool>("apply_rwgt_nlo", true);
  hhWeight.addParameter<std::string>("rwgt_nlo_mode", "v3");

  const HHWeightInterfaceCouplings couplings(hhWeight);
  const HHWeightInterfaceNLO HHWeightNLO_calc(&couplings, Era::k2017);

  const std::vector<int> mHH_bins = {
    250, 270, 290, 310, 330, 350, 370, 390, 410, 430, 450, 470, 490, 510, 530, 550, 570, 590, 610, 630, 650, 670, 700,
    750, 800, 850, 900, 950, 1000, 1100, 1200, 1300, 1400, 1500, 1750, 2000, 5000
  };
  const std::vector<double> cosTheta_bins = { 0.0, 0.4, 0.6, 0.8, 1.0 };
  for(std::size_t mHH_idx = 0; mHH_idx < mHH_bins.size() - 1; ++mHH_idx)
  {
    const double mHH_mid = (mHH_bins[mHH_idx] + mHH_bins[mHH_idx + 1]) / 2.;
    std::cout << "mHH = [" << std::setw(4) << mHH_bins[mHH_idx] << ", " << std::setw(4) << mHH_bins[mHH_idx + 1] << "]: ";

    for(std::size_t cosTheta_idx = 0; cosTheta_idx < cosTheta_bins.size() - 1; ++cosTheta_idx)
    {
      const double cosTheta_mid = (cosTheta_bins[cosTheta_idx] + cosTheta_bins[cosTheta_idx]) / 2.;
      const double weight = HHWeightNLO_calc.getWeight_LOtoNLO("SM", mHH_mid, cosTheta_mid);
      std::cout
          << "cosTheta = [" << std::fixed << std::setprecision(1) << std::setw(3)
          << cosTheta_bins[cosTheta_idx] << ", " << cosTheta_bins[cosTheta_idx + 1] << "] => "
          << std::fixed << std::setprecision(6) << std::setw(8) << weight
      ;
      if(cosTheta_idx < cosTheta_bins.size() - 2)
      {
        std::cout << "; ";
      }
    }
    std::cout << '\n';
  }

  return EXIT_SUCCESS;
}
