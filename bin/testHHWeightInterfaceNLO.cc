#include "tthAnalysis/HiggsToTauTau/interface/HHWeightInterfaceCouplings.h"
//#include "tthAnalysis/HiggsToTauTau/interface/HHWeightInterfaceLO.h"
#include "tthAnalysis/HiggsToTauTau/interface/HHWeightInterfaceNLO.h"
#include "tthAnalysis/HiggsToTauTau/interface/generalAuxFunctions.h" // format_vdouble(), to_string_with_precision<>()

#include <boost/algorithm/string/replace.hpp> // boost::replace_all()

int
main(int argc,
     char ** argv)
{
  const std::string line(120, '-');

  edm::ParameterSet hhWeight;
  hhWeight.addParameter<std::string>("denominator_file_lo", "hhAnalysis/multilepton/data/denom_2017.root");
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

  HHWeightInterfaceCouplings couplings(hhWeight);

//  // test LO normalization factors in separate scope
//  {
//    const HHWeightInterfaceLO HHWeightLO_calc(&couplings, hhWeight);
//    const std::vector<double> norm = HHWeightLO_calc.getNorm();
//    std::cout << "LO normalization coefficients: " << std::fixed << std::setprecision(5) << format_vdouble(norm) << '\n';
//  }
//  std::cout << line << '\n';

  // add c2 scan points
  std::vector<double> c2;
  std::vector<std::string> c2_names;
  for(int i = 0; i < 22; ++i) { c2.push_back((i - 20) / 10.); }
  for(int i = 0; i < 10; ++i) { c2.push_back((i +  3) / 20.); }
  for(int i = 0; i < 24; ++i) { c2.push_back((i +  7) / 10.); }
  assert(c2.size() == 56);
  for(std::size_t i = 0; i < c2.size(); ++i)
  {
    std::string name = "c2_" + to_string_with_precision(c2.at(i));
    boost::replace_all(name, "-", "m");
    boost::replace_all(name, ".", "p");
    couplings.add({{ 1., 1., c2.at(i), 0., 0. }}, name);
    c2_names.push_back(name);
  }

  // NLO demo
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
  std::cout << line << '\n';

  // c2 demo
  const std::size_t mHH_idx = 1;
  const std::size_t cosTheta_idx = 0;
  const double mHH_mid = (mHH_bins[mHH_idx] + mHH_bins[mHH_idx + 1]) / 2.;
  const double cosTheta_mid = (cosTheta_bins[cosTheta_idx] + cosTheta_bins[cosTheta_idx]) / 2.;
  std::cout << "mHH = [" << std::setw(4) << mHH_bins[mHH_idx] << ", " << std::setw(4) << mHH_bins[mHH_idx + 1] << "], "
               "cosTheta = [" << std::fixed << std::setprecision(1) << std::setw(3)
                              << cosTheta_bins[cosTheta_idx] << ", "<< cosTheta_bins[cosTheta_idx + 1] << "]:"
  ;
  for(std::size_t i = 0; i < c2.size(); ++i)
  {
    if(i % 5 == 0)
    {
      std::cout << "\n\t";
    }
    const TH2 * const dXsec = HHWeightNLO_calc.get_dXsec_V2_nlo(c2_names.at(i));
    std::cout << "[c2 = " << std::setw(5) << std::setprecision(2) << c2.at(i) << " => "
              << std::fixed << std::setprecision(6) << std::setw(8)
              << HHWeightInterfaceCouplings::getBinContent(dXsec, mHH_mid, cosTheta_mid)
              << "] "
    ;
  }
  std::cout << '\n' << line << '\n';

  // total cross section demo
  std::cout << "Total LO / NLO cross section [ab] for:\n";
  for(std::size_t i = 0; i < 13; ++i)
  {
    const std::string bmName = i > 0 ? Form("BM%lu", i) : "SM";
    std::cout << "  " << bmName << " -> "
        << std::fixed << std::setprecision(1) << std::setw(17 - bmName.size()) << HHWeightNLO_calc.get_totalXsec_lo(bmName) << " / "
        << std::fixed << std::setprecision(1) << std::setw(15)                 << HHWeightNLO_calc.get_totalXsec_nlo(bmName) << '\n'
    ;
  }
  // NLO-to-NNLO k-factor is 1.115
  const double sm_nnlo_expected = (70.3874 - 50.4111 + 11.0595); // in fb
  const double sm_nnlo = HHWeightNLO_calc.get_totalXsec_nlo("SM") * 1.115 / 1.e3; // need to divide by 1000 to get in fb
  const double sm_nnlo_reldiff = (sm_nnlo - sm_nnlo_expected) / sm_nnlo_expected * 100.;
  std::cout << "\n"
       "Expected NNLO SM XS =           " << std::setprecision(4) << std::setw(8) << sm_nnlo_expected << " fb\n"
       "NNLO SM XS returned by our FW = " << std::setprecision(4) << std::setw(8) << sm_nnlo          << " fb\n"
       " -> relative difference = " << std::setprecision(3) << sm_nnlo_reldiff << "%\n"
  ;

  return EXIT_SUCCESS;
}
