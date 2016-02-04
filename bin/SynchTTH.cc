#include <iostream> // std::cerr, std::fixed
#include <fstream> // std::ofstream
#include <string> // std::string
#include <vector> // std::vector<>
#include <cstdlib> // EXIT_SUCCESS, EXIT_FAILURE
#include <memory> // std::unique_ptr<>
#include <utility> // std::pair<>
#include <map> // std::map<>
#include <iomanip> // std::setprecision(), std::setw()
#include <algorithm> // std::for_each(), std::accumulate(), std::set_union()
#include <sstream> // std::stringstream
#include <iterator> // std::back_inserter()

#include "FWCore/ParameterSet/interface/ParameterSet.h" // edm::ParameterSet
#include "FWCore/PythonParameterSet/interface/MakeParameterSets.h" // edm::readPSetsFrom()
#include "FWCore/Utilities/interface/Exception.h" // cms::Exception
#include "DataFormats/FWLite/interface/InputSource.h" // fwlite::InputSource
#include "DataFormats/Math/interface/LorentzVector.h" // math::PtEtaPhiMLorentzVector

#include <Rtypes.h> // Int_t, Long64_t, Double_t
#include <TChain.h> // TChain
#include <TTree.h> // TTree
#include <TBenchmark.h> // TBenchmark

#include <boost/filesystem.hpp> // boost::filesystem::
#include <boost/algorithm/string/predicate.hpp> // boost::iequals()

#include "tthAnalysis/HiggsToTauTau/interface/HistogramManager.h" // HistogramManager, join_strings()
#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h" // RecoLepton
#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/HadronicTau.h" // HardronicTau
#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h" // GenLepton
#include "tthAnalysis/HiggsToTauTau/interface/GenJet.h" // GenJet

#if defined(M125)
#include "tthAnalysis/HiggsToTauTau/interface/KeyTypes125.h"
#elif defined(M120)
#include "tthAnalysis/HiggsToTauTau/interface/KeyTypes120.h"
#endif

typedef math::PtEtaPhiMLorentzVector LV;

/**
 * @brief Check if given path is an existing directory.
 * @param path Path as a boost::filesystem::path.
 * @return true if it's a directory, false otherwise
 */
inline bool
is_dir(const boost::filesystem::path & path)
{
  return boost::filesystem::exists(path) &&
         boost::filesystem::is_directory(path);
}

/**
 * @brief Check if given path is an existing directory.
 * @param path Path as a string.
 * @return true if it's a directory, false otherwise
 */
inline bool
is_dir(const std::string & path)
{
  const boost::filesystem::path _path(path);
  return is_dir(_path);
}

/**
 * @brief Creates a directory for the log file(s)
 *        If the directory exists, it tries to create a directory
 *        with suffix _N, where N is the least positive number available
 * @param output_dir Original directory name
 * @return 0 if the creation succeeded, 1 otherwise
 */
int
create_log_folder(std::string & output_dir,
                  bool force_overwrite)
{
  bool output_dir_exists = is_dir(output_dir);
  if(! force_overwrite)
  {
    int suffix = 0;
    while(output_dir_exists)
    {
      ++suffix;
      const std::string tmp = output_dir + "_" + std::to_string(suffix);
      output_dir_exists = is_dir(tmp);
    }
    if(suffix)
      output_dir += "_" + std::to_string(suffix);
  }

  boost::system::error_code errc;
  const boost::filesystem::path dir_path(output_dir);
  boost::filesystem::create_directories(dir_path, errc);
  if(errc)
  {
    std::cerr << "couldn't create directory: "
              << output_dir
              << "\n";
    return 1;
  }
  return 0;
}

/**
 * @brief Function that sort tight leptons by their pT
 * @param vec The vector containing [index, pT] pair
 */
void
leading_lept(std::vector<std::pair<Int_t, Double_t>> & vec)
{
  std::sort
  (
    vec.begin(),
    vec.end(),
    [](std::pair<Int_t, Double_t> A,
       std::pair<Int_t, Double_t> B) -> bool
    {
      return A.second > B.second;
    }
  );
}

/**
 * @brief Finds all files with specified extension in a given directory.
 * @param dir       Full path to the directory.
 * @param ext       Required file extension.
 * @param file_list Vector containig all files.
 * @return 0 if the function succeeded;
 *         1 if the directory doesn't exist;
 *         2 if the extension is an empty string
 *         3 if there are no files with the extension in the given directory.
 */
int
get_all_files(const std::string & dir,
              const std::string & ext,
              std::vector<std::string> & file_list)
{
  const boost::filesystem::path dir_path(dir);
  if(! is_dir(dir_path)) return 1;

  if(! ext.size()) return 2;

  const std::string _ext = (ext[0] != '.') ? "." + ext : ext;
  boost::filesystem::recursive_directory_iterator it(dir_path);
  boost::filesystem::recursive_directory_iterator endit;

  while(it != endit)
  {
    if(boost::filesystem::is_regular_file(*it) &&
       boost::iequals(it -> path().extension().string(), _ext))
      file_list.push_back((dir_path / it -> path().filename()).string());
    ++it;
  }

  if(! file_list.size()) return 3;

  return 0;
}

/**
 * @brief Checks whether a given lepton passes preselection criteria
 * @param Given lepton
 * @return True, if passes; false otherwise
 */
inline bool
passes_preselection(const RecoLepton & lept)
{
  if(std::fabs(lept.dxy)     <= 0.05 && // 500um in cm
     std::fabs(lept.dz)      < 0.1   && // 1 mm in cm
     lept.rel_iso            < 0.5    )
  {
    if(lept.is_electron()      &&
       lept.lost_hits  <= 1    &&
       lept.ele_mva_id >= 1    &&
       lept.pt         > 7.0   &&
       std::fabs(lept.eta) < 2.5)
      return true;
    else if(lept.is_muon()          &&
            lept.loose_id >= 1      &&
            lept.pt       > 5.0     &&
            std::fabs(lept.eta) < 2.4)
      return true;
  }
  return false;
}

/**
 * @brief Cutflow code.
 *        The resulting file needs post-processing (use FormatResults.py).
 *
 * Partial expected output (as a file tree):
 *   ./
 *   |
 *   |----results/
 *        |
 *        |---- ttH/
 *        |     |
 *        |     |---- histograms.root (contains all histograms for this sample)
 *        |     |---- log.txt         (log file about file i/o and progress)
 *        |     |---- table.txt       (the results)
 *        |
 *        |---- ZZ/
 *        |     |---- histograms.root
 *        |     |---- log.txt
 *        |     |---- table.txt
 *        |
 *       ...
 *
 * The file `table.txt` is later needed by Python scripts which do the parsing;
 * the file contains semicolon-separated cut labels (e.g. "lepton mva" or
 * "Z veto") and corresponding event yield.
 */
int
main(int argc,
     char ** argv)
{
//--- parse command-line arguments
  if ( argc < 2 )
  {
    std::cerr << "Usage: "
              << argv[0]
              << " [parameters.py]\n";
    return EXIT_SUCCESS;
  }

//--- keep track of time it takes the macro to execute
  TBenchmark clock;
  clock.Start("PreselectionTTH");

//--- read the parameters from python configuration file
  if (! edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process"))
    throw cms::Exception("PreselectionTTH")
      << "No ParameterSet 'process' found in configuration file = "
      << argv[1]
      << "!\n";

  const edm::ParameterSet cfg = edm::readPSetsFrom(argv[1]) ->
      getParameter<edm::ParameterSet>("process");
  const edm::ParameterSet cfg_presel =
      cfg.getParameter<edm::ParameterSet>("SynchTTH");
  std::string output_dir =
      cfg_presel.getParameter<std::string>("outputDir");
  const bool force_overwrite =
      cfg_presel.getParameter<bool>("forceOverwrite");
  const fwlite::InputSource input_files_cfg(cfg);
  if (input_files_cfg.files().size() != 1)
    throw cms::Exception("SynchTTH")
      << "Exactly one input file expected!\n";
  const Long64_t logging_frequency = input_files_cfg.reportAfter();
  const Long64_t max_nevents = input_files_cfg.maxEvents();

  const std::string input_path = input_files_cfg.files().front();
  std::vector<std::string> file_list;
  if(is_dir(input_path))
  {
    if(get_all_files(input_path, "root", file_list))
    {
      std::cerr << "no *.root files in the given path: "
                << input_path
                << "\n";
      return EXIT_FAILURE;
    }
  }
  else
    file_list.push_back(input_path);

//--- create the log folder
  if(create_log_folder(output_dir, force_overwrite))
    return EXIT_FAILURE;

//--- place the log and histogram root files into the log directory
  const std::string log_fn =
    (boost::filesystem::path(output_dir) /
     boost::filesystem::path("log.txt")).string();
  const std::string histogram_fn =
      (boost::filesystem::path(output_dir) /
       boost::filesystem::path("histograms.root")).string();
  const std::string pdgid_histogram_fn =
      (boost::filesystem::path(output_dir) /
       boost::filesystem::path("pdg_id.root")).string();

//--- create the log file
  std::ofstream log_file;
  try
  {
    log_file.open(log_fn);
  }
  catch(std::exception & e)
  {
    std::cerr << "couldn't open the log file: "
              << log_fn
              << ": "
              << e.what()
              << "\n";
    return EXIT_FAILURE;
  }

//--- counter map keys
  enum cuts {
    entry_point = 0,
    PS,
    tight_lepton,
    dangling,
    good_leptons,
    min_dilep_mass,
    pT2010,
    j2_plus,
    bjet_2l_1m,
    specific_cuts,
    medium_mu_id,
    conv_veto,
    lost_hits_0,
    ele_id,
    rel_iso_01,
    sip3d_4,
    tight_mva,
    ss,
    j4_plus,
    met_ld_02,
    pT2020,
    ht_l1l2_met_100,
    zveto,
    charge_quality,
    j4_plus_met_ld_02,
    loose_mva,
    neutral_sum,
    sfos_zveto,
    good_tau
  };
  enum ch {
    ee = 0,
    mumu,
    emu,
    _3l,
    _4l,
    _2l_1tau,
    _1l_2tau,
    unspecified
  };

  const std::map<cuts, std::string> cuts_str =
  {
    {cuts::entry_point,       "entry point"},
    {cuts::PS,                "preselection"},
    {cuts::tight_lepton,      "tight lepton"},
    {cuts::good_leptons,      "2/3 T leptons or 4 L leptons"},
    {cuts::dangling,          "dangling lepton cut"},
    {cuts::min_dilep_mass,    "minDilepMass>12 GeV"},
    {cuts::pT2010,            "pT(l1),pT(l2) >20,>10 GeV"},
    {cuts::j2_plus,           "nJet>=2 (25 GeV)"},
    {cuts::bjet_2l_1m,        "2+L bJet or 1+M bJet"},
    {cuts::specific_cuts,     "2l1t: dilepton-specific cuts"},
    {cuts::medium_mu_id,      "medium muon ID"},
    {cuts::conv_veto,         "electron conversion veto"},
    {cuts::lost_hits_0,       "lost hits == 0"},
    {cuts::ele_id,            "electron identification"},
    {cuts::rel_iso_01,        "relative isolation < 0.1"},
    {cuts::sip3d_4,           "SIP3D < 4.0"},
    {cuts::tight_mva,         "tight lepton mva"},
    {cuts::ss,                "same sign"},
    {cuts::j4_plus,           "nJet>=4 (25 GeV)"},
    {cuts::met_ld_02,         "MET_LD>0.2"},
    {cuts::pT2020,            "pT(l1),pT(l2) >20,>20 GeV"},
    {cuts::ht_l1l2_met_100,   "pT(l1)+pT(l2)+MET > 100 GeV"},
    {cuts::zveto,             "Z veto"},
    {cuts::charge_quality,    "tight charge"},
    {cuts::j4_plus_met_ld_02, "nJet>=4 (25 GeV) or MET_LD>0.2"},
    {cuts::loose_mva,         "loose lepton mva"},
    {cuts::neutral_sum,       "neutral charge sum"},
    {cuts::sfos_zveto,        "SFOS Z veto"},
    {cuts::good_tau,          "good tau"}
  };
  const std::map<ch, std::string> ch_str =
  {
    {ch::ee,       "ee"},
    {ch::mumu,     "mumu"},
    {ch::emu,      "emu"},
    {ch::_3l,      "3l"},
    {ch::_4l,      "4l"},
    {ch::_2l_1tau, "2l1tau"},
    {ch::_1l_2tau, "1l2tau"}
  };

//--- set up event counter for each channel
  std::map<ch, std::map<cuts, Long64_t>> counter =
  {
    {ch::ee,
      {
        {cuts::entry_point,     0},
        {cuts::PS,              0},
        {cuts::good_leptons,    0},
        {cuts::dangling,        0},
        {cuts::min_dilep_mass,  0},
        {cuts::pT2010,          0},
        {cuts::j2_plus,         0},
        {cuts::bjet_2l_1m,      0}, // common end
        {cuts::conv_veto,       0},
        {cuts::lost_hits_0,     0},
        {cuts::ele_id,          0},
        {cuts::rel_iso_01,      0},
        {cuts::sip3d_4,         0},
        {cuts::tight_mva,       0},
        {cuts::ss,              0},
        {cuts::j4_plus,         0},
        {cuts::met_ld_02,       0},
        {cuts::pT2020,          0},
        {cuts::ht_l1l2_met_100, 0},
        {cuts::zveto,           0},
        {cuts::charge_quality,  0}
      }
    },
    {ch::mumu,
      {
        {cuts::entry_point,     0},
        {cuts::PS,              0},
        {cuts::good_leptons,    0},
        {cuts::dangling,        0},
        {cuts::min_dilep_mass,  0},
        {cuts::pT2010,          0},
        {cuts::j2_plus,         0},
        {cuts::bjet_2l_1m,      0}, // common end
        {cuts::medium_mu_id,    0},
        {cuts::rel_iso_01,      0},
        {cuts::sip3d_4,         0},
        {cuts::tight_mva,       0},
        {cuts::ss,              0},
        {cuts::j4_plus,         0},
        {cuts::met_ld_02,       0},
        {cuts::pT2020,          0},
        {cuts::ht_l1l2_met_100, 0},
        {cuts::zveto,           0},
        {cuts::charge_quality,  0}
      }
    },
    {ch::emu,
      {
        {cuts::entry_point,     0},
        {cuts::PS,              0},
        {cuts::good_leptons,    0},
        {cuts::dangling,        0},
        {cuts::min_dilep_mass,  0},
        {cuts::pT2010,          0},
        {cuts::j2_plus,         0},
        {cuts::bjet_2l_1m,      0}, // common end
        {cuts::medium_mu_id,    0},
        {cuts::conv_veto,       0},
        {cuts::lost_hits_0,     0},
        {cuts::ele_id,          0},
        {cuts::rel_iso_01,      0},
        {cuts::sip3d_4,         0},
        {cuts::tight_mva,       0},
        {cuts::ss,              0},
        {cuts::j4_plus,         0},
        {cuts::met_ld_02,       0},
        {cuts::pT2020,          0},
        {cuts::ht_l1l2_met_100, 0},
        {cuts::zveto,           0},
        {cuts::charge_quality,  0}
      }
    },
    {ch::_3l,
      {
        {cuts::entry_point,       0},
        {cuts::PS,                0},
        {cuts::good_leptons,      0},
        {cuts::dangling,          0},
        {cuts::min_dilep_mass,    0},
        {cuts::pT2010,            0},
        {cuts::j2_plus,           0},
        {cuts::bjet_2l_1m,        0}, // common end
        {cuts::medium_mu_id,      0},
        {cuts::conv_veto,         0},
        {cuts::lost_hits_0,       0},
        {cuts::ele_id,            0},
        {cuts::rel_iso_01,        0},
        {cuts::sip3d_4,           0},
        {cuts::tight_mva,         0},
        {cuts::j4_plus_met_ld_02, 0},
        {cuts::sfos_zveto,        0}
      }
    },
    {ch::_4l,
      {
        {cuts::entry_point,    0},
        {cuts::PS,             0},
        {cuts::good_leptons,   0},
        {cuts::min_dilep_mass, 0},
        {cuts::pT2010,         0},
        {cuts::j2_plus,        0},
        {cuts::bjet_2l_1m,     0}, // common end
        {cuts::medium_mu_id,   0},
        {cuts::loose_mva,      0},
        {cuts::neutral_sum,    0},
        {cuts::sfos_zveto,     0}
      }
    },
    {ch::_2l_1tau,
      {
        {cuts::entry_point,     0},
        {cuts::PS,              0},
        {cuts::good_leptons,    0},
        {cuts::dangling,        0},
        {cuts::min_dilep_mass,  0},
        {cuts::pT2010,          0},
        {cuts::j2_plus,         0},
        {cuts::bjet_2l_1m,      0},
        {cuts::specific_cuts,   0}, // med_mu_id, conv_veto, lost_hits, ele_mva
        {cuts::rel_iso_01,      0},
        {cuts::sip3d_4,         0},
        {cuts::tight_mva,       0},
        {cuts::ss,              0},
        {cuts::j4_plus,         0},
        {cuts::met_ld_02,       0},
        {cuts::pT2020,          0},
        {cuts::ht_l1l2_met_100, 0},
        {cuts::zveto,           0},
        {cuts::charge_quality,  0},
        {cuts::good_tau,        0}
     }
    },
    {ch::_1l_2tau,
      {
        {cuts::entry_point,  0},
        {cuts::PS,           0},
        {cuts::tight_lepton, 0},
        {cuts::j2_plus,      0},
        {cuts::bjet_2l_1m,   0},
        {cuts::good_tau,     0}
      }
    }
  };
  /**
   * Increments all but 1 lepton + 2 tau channel.
   */
  auto increment_all = [&counter](cuts c)
  {
    for(auto channel: {ch::ee, ch::mumu, ch::emu, ch::_3l, ch::_4l, ch::_2l_1tau})
      ++counter[channel][c];
  };

//--- set up the histogram manager
  enum cp { final };
  HistogramManager<ch, cp> hm;
  hm.add_channel(ch::ee, "ee")
    .add_channel(ch::mumu, "mumu")
    .add_channel(ch::emu, "emu");
  hm.add_cutpoint({cp::final, "final"});
  hm.add_variable({"pT(l2)", 16, 10, 90})
    .add_variable({"|eta(l2)|", 12, 0, 2.4})
    .add_variable({"min(dR(l2,j))", 12, 0, 4})
    .add_variable({"mT(MET,l1)", 15, 0, 200})
    .add_variable({"HT", 15, 0, 1200})
    .add_variable({"MHT", 12, 0, 250});
  hm.initialize();

//--- set up PDG ID plots
  enum charge { same, flipped, due_jets, no_overlap };
  HistogramManager<charge, ch> pdg_id_plots;
  pdg_id_plots.add_channel(charge::same,       "same_sign")
              .add_channel(charge::flipped,    "flipped_sign")
              .add_channel(charge::due_jets,   "due_jets")
              .add_channel(charge::no_overlap, "no_overlap");
  pdg_id_plots.add_cutpoint({ch::ee,   "ee"})
              .add_cutpoint({ch::mumu, "mumu"})
              .add_cutpoint({ch::emu,  "emu"})
              .add_cutpoint({ch::_3l,  "3l"})
              .add_cutpoint({ch::_4l,  "4l"});
  pdg_id_plots.add_variable({"e-", 3, 0, 3})
              .add_variable({"e+", 3, 0, 3})
              .add_variable({"mu-", 3, 0, 3})
              .add_variable({"mu+", 3, 0, 3});
  pdg_id_plots.initialize();
  const std::map<int, std::string> pdg_id_keys =
  {
    { 11, "e-"},
    {-11, "e+"},
    { 13, "mu-"},
    {-13, "mu+"}
  };
  auto fill_pdg_plot = [&pdg_id_keys, &pdg_id_plots]
                         (const std::vector<GenLepton> & gen_leptons,
                          const std::vector<GenJet> & gen_jets,
                          const std::vector<RecoLepton> & leptons,
                          ch channel) -> void
  {
    for(auto & lepton: leptons)
    {
      bool any_overlap = false;
      const std::string pdg_id_key = pdg_id_keys.at(lepton.pdg_id);

      for(auto & gen_lepton: gen_leptons)
        if(lepton.is_overlap(gen_lepton, 0.3))
        {
          if(lepton.pdg_id == gen_lepton.pdg_id)
          {
            pdg_id_plots[charge::same][channel].fill(pdg_id_key, 1);
            any_overlap = true;
            break;
          }
          else if(lepton.pdg_id == -gen_lepton.pdg_id)
          {
            pdg_id_plots[charge::flipped][channel].fill(pdg_id_key, 1);
            any_overlap = true;
            break;
          }
        }

      if(any_overlap) continue;
      for(auto & gen_jet: gen_jets)
        if(lepton.is_overlap(gen_jet, 0.3) &&
           lepton.rel_pT_diff(gen_jet, 0.1) )
        {
          pdg_id_plots[charge::due_jets][channel].fill(pdg_id_key, 1);
          any_overlap = true;
          break;
        }

      if(any_overlap) continue;
      pdg_id_plots[charge::no_overlap][channel].fill(pdg_id_key, 1);
    }
  };

//--- open the ROOT file and the tree
  TChain chain("tree");
  for(const std::string & file: file_list)
  {
    chain.Add(file.c_str());
    log_file << "Chaining file: "
             << file
             << "\n";
  }

//--- declare the constants
  const double tight_mva_wp = 0.8;
  const double loose_mva_wp = 0.5;
  const double loose_csv_wp = 0.244;
  const double medium_csv_wp = 0.679;
  const unsigned max_nleptons = 32;
  const unsigned max_njets = 32;
  const unsigned max_ntaus = 32;
  const unsigned max_ngenlept = 32;
  const unsigned max_ngenjet = 32;
  const double z_mass = 91.1876;
  const double z_th = 10;
  const double met_coef = 0.00397;
  const double mht_coef = 0.00265;

//--- declare the variables
  RUN_TYPE                 run;
  LUMI_TYPE                lumi;
  EVT_TYPE                 evt;

  NLEPTONS_TYPE nleptons;
  LEPT_PT_TYPE             pt             [max_nleptons];
  LEPT_ETA_TYPE            eta            [max_nleptons];
  LEPT_PHI_TYPE            phi            [max_nleptons];
  LEPT_MASS_TYPE           mass           [max_nleptons];
  LEPT_DXY_TYPE            dxy            [max_nleptons];
  LEPT_DZ_TYPE             dz             [max_nleptons];
  LEPT_REL_ISO_TYPE        rel_iso        [max_nleptons];
  LEPT_SIP3D_TYPE          sip3d          [max_nleptons];
  LEPT_MVA_TTH_TYPE        mva_tth        [max_nleptons];
  LEPT_MED_MU_ID_TYPE      med_mu_id      [max_nleptons];
  LEPT_PDG_ID_TYPE         pdg_id         [max_nleptons];
  LEPT_ELE_MVA_ID_TYPE     ele_mva_id     [max_nleptons];
  LEPT_LOST_HITS_TYPE      lost_hits      [max_nleptons];
  LEPT_LOOSE_ID_TYPE       loose_id       [max_nleptons];
  LEPT_TIGHT_CHARGE_TYPE   tight_charge   [max_nleptons];
  LEPT_CONV_VETO_TYPE      pass_conv_veto [max_nleptons];

  MET_PT_TYPE              met_pt;
  MET_ETA_TYPE             met_eta;
  MET_PHI_TYPE             met_phi;
  MET_MASS_TYPE            met_mass;

  NJETS_TYPE               njets;
  JET_PT_TYPE              jet_pt         [max_njets];
  JET_ETA_TYPE             jet_eta        [max_njets];
  JET_PHI_TYPE             jet_phi        [max_njets];
  JET_MASS_TYPE            jet_mass       [max_njets];
  JET_CSV_TYPE             jet_csv        [max_njets];

  NTAUS_TYPE               ntaus;
  TAU_PT_TYPE              tau_pt         [max_ntaus];
  TAU_ETA_TYPE             tau_eta        [max_ntaus];
  TAU_PHI_TYPE             tau_phi        [max_ntaus];
  TAU_MASS_TYPE            tau_mass       [max_ntaus];
  TAU_DECMODE_TYPE         tau_decmode    [max_ntaus];
  TAU_ID_MVA_TYPE          tau_id_mva     [max_ntaus];
  TAU_ANTI_E_TYPE          tau_anti_e     [max_ntaus];
  TAU_ANTI_MU_TYPE         tau_anti_mu    [max_ntaus];

  GEN_NLEPTONS_TYPE        gen_nleptons;
  GEN_PT_TYPE              gen_pt         [max_ngenlept];
  GEN_ETA_TYPE             gen_eta        [max_ngenlept];
  GEN_PHI_TYPE             gen_phi        [max_ngenlept];
  GEN_MASS_TYPE            gen_mass       [max_ngenlept];
  GEN_PDG_ID_TYPE          gen_pdgid      [max_ngenlept];

  GEN_NJETS_TYPE           gen_njets;
  GEN_JET_PT_TYPE          gen_jet_pt     [max_ngenjet];
  GEN_JET_ETA_TYPE         gen_jet_eta    [max_ngenjet];
  GEN_JET_PHI_TYPE         gen_jet_phi    [max_ngenjet];
  GEN_JET_MASS_TYPE        gen_jet_mass   [max_ngenjet];

  chain.SetBranchAddress(RUN_KEY,               &run);
  chain.SetBranchAddress(LUMI_KEY,              &lumi);
  chain.SetBranchAddress(EVT_KEY,               &evt);

  chain.SetBranchAddress(NLEPTONS_KEY,          &nleptons);
  chain.SetBranchAddress(LEPT_PT_KEY,           &pt);
  chain.SetBranchAddress(LEPT_ETA_KEY,          &eta);
  chain.SetBranchAddress(LEPT_PHI_KEY,          &phi);
  chain.SetBranchAddress(LEPT_MASS_KEY,         &mass);
  chain.SetBranchAddress(LEPT_DXY_KEY,          &dxy);
  chain.SetBranchAddress(LEPT_DZ_KEY,           &dz);
  chain.SetBranchAddress(LEPT_REL_ISO_KEY,      &rel_iso);
  chain.SetBranchAddress(LEPT_SIP3D_KEY,        &sip3d);
  chain.SetBranchAddress(LEPT_MVA_TTH_KEY,      &mva_tth);
  chain.SetBranchAddress(LEPT_MED_MU_ID_KEY,    &med_mu_id);
  chain.SetBranchAddress(LEPT_PDG_ID_KEY,       &pdg_id);
  chain.SetBranchAddress(LEPT_ELE_MVA_ID_KEY,   &ele_mva_id);
  chain.SetBranchAddress(LEPT_LOST_HITS_KEY,    &lost_hits);
  chain.SetBranchAddress(LEPT_LOOSE_ID_KEY,     &loose_id);
  chain.SetBranchAddress(LEPT_TIGHT_CHARGE_KEY, &tight_charge);
  chain.SetBranchAddress(LEPT_CONV_VETO_KEY,    &pass_conv_veto);

  chain.SetBranchAddress(MET_PT_KEY,            &met_pt);
  chain.SetBranchAddress(MET_ETA_KEY,           &met_eta);
  chain.SetBranchAddress(MET_PHI_KEY,           &met_phi);
  chain.SetBranchAddress(MET_MASS_KEY,          &met_mass);

  chain.SetBranchAddress(NJETS_KEY,             &njets);
  chain.SetBranchAddress(JET_PT_KEY,            &jet_pt);
  chain.SetBranchAddress(JET_ETA_KEY,           &jet_eta);
  chain.SetBranchAddress(JET_PHI_KEY,           &jet_phi);
  chain.SetBranchAddress(JET_CSV_KEY,           &jet_csv);
  chain.SetBranchAddress(JET_MASS_KEY,          &jet_mass);

  chain.SetBranchAddress(NTAUS_KEY,             &ntaus);
  chain.SetBranchAddress(TAU_PT_KEY,            &tau_pt);
  chain.SetBranchAddress(TAU_ETA_KEY,           &tau_eta);
  chain.SetBranchAddress(TAU_PHI_KEY,           &tau_phi);
  chain.SetBranchAddress(TAU_MASS_KEY,          &tau_mass);
  chain.SetBranchAddress(TAU_DECMODE_KEY,       &tau_decmode);
  chain.SetBranchAddress(TAU_ID_MVA_KEY,        &tau_id_mva);
  chain.SetBranchAddress(TAU_ANTI_E_KEY,        &tau_anti_e);
  chain.SetBranchAddress(TAU_ANTI_MU_KEY,       &tau_anti_mu);

  chain.SetBranchAddress(GEN_NLEPTONS_KEY,      &gen_nleptons);
  chain.SetBranchAddress(GEN_PT_KEY,            &gen_pt);
  chain.SetBranchAddress(GEN_ETA_KEY,           &gen_eta);
  chain.SetBranchAddress(GEN_PHI_KEY,           &gen_phi);
  chain.SetBranchAddress(GEN_MASS_KEY,          &gen_mass);
  chain.SetBranchAddress(GEN_PDG_ID_KEY,        &gen_pdgid);

  chain.SetBranchAddress(GEN_NJETS_KEY,         &gen_njets);
  chain.SetBranchAddress(GEN_JET_PT_KEY,        &gen_jet_pt);
  chain.SetBranchAddress(GEN_JET_ETA_KEY,       &gen_jet_eta);
  chain.SetBranchAddress(GEN_JET_PHI_KEY,       &gen_jet_phi);
  chain.SetBranchAddress(GEN_JET_MASS_KEY,      &gen_jet_mass);

  Long64_t nof_events = chain.GetEntries();
  log_file << "Total number of events: "
           << nof_events
           << "\n";
  if(max_nevents > 0)
  {
    const Long64_t _nof_events = std::min(max_nevents, nof_events);
    if(_nof_events != nof_events)
      log_file << "Looping over the first "
               << _nof_events
               << " instead.\n";
    nof_events = _nof_events;
  }

//--- loop over the events
  for(Long64_t i = 0; i < nof_events; ++i)
  {
    if(i % logging_frequency == 0 || i == nof_events - 1)
    {
      std::stringstream ss;
      ss << std::fixed << std::setprecision(2)
         << 100.0 * (i + 1) / nof_events;
      log_file << std::setw(10) << std::left
               << ("[" + ss.str() + "%]")
               << "Event: " << (i + 1)
               << "\n";
    }

//--- get the event
    chain.GetEntry(i);

//--- create the lepton collection
    std::vector<RecoLepton> leptons;
    leptons.reserve(nleptons);
    for(Int_t n = 0; n < nleptons; ++n)
      leptons.push_back({ pt[n], eta[n], phi[n], mass[n], pdg_id[n],
                          dxy[n], dz[n], rel_iso[n], sip3d[n], mva_tth[n],
                          med_mu_id[n], ele_mva_id[n], lost_hits[n], loose_id[n],
                          tight_charge[n], pass_conv_veto[n] });

//--- create the jet collection
    std::vector<RecoJet> jets;
    jets.reserve(njets);
    for(Int_t n = 0; n < njets; ++n)
      jets.push_back({ jet_pt[n], jet_eta[n], jet_phi[n], jet_mass[n],
                       jet_csv[n], n });

//--- create the generator level jet collection
    std::vector<GenJet> gen_jets;
    gen_jets.reserve(gen_njets);
    for(Int_t n = 0; n < gen_njets; ++n)
      gen_jets.push_back({ gen_jet_pt[n], gen_jet_eta[n],
                           gen_jet_phi[n], gen_jet_mass[n] });

//--- create the tau collection
    std::vector<HadronicTau> taus;
    taus.reserve(ntaus);
    for(Int_t n = 0; n < ntaus; ++n)
      taus.push_back({ tau_pt[n], tau_eta[n], tau_phi[n], tau_mass[n],
                       tau_decmode[n], tau_id_mva[n], tau_anti_e[n],
                       tau_anti_mu[n] });

//--- create the collection of generator level leptons
    std::vector<GenLepton> gen_leptons;
    for(Int_t n = 0; n < gen_nleptons; ++n)
      gen_leptons.push_back({ gen_pt[n], gen_eta[n], gen_phi[n], gen_mass[n],
                              gen_pdgid[n] });

//--- collect the hadronic jets
    std::vector<RecoJet> hadronic_jets;
    for(auto & jet: jets)
      if(jet.pt > 25) hadronic_jets.push_back(jet);

//--- collect bjets
    std::map<std::string, std::vector<RecoJet>> bjets =
    {
      { "loose",  {} },
      { "medium", {} }
    };
    for(auto & jet: jets)
      if(std::fabs(jet.eta) < 2.4)
      {
        if(jet.csv > loose_csv_wp)  bjets["loose"].push_back(jet);
        if(jet.csv > medium_csv_wp) bjets["medium"].push_back(jet);
        // note: consider the case where a loose bjet might be a medium one
        //       this could be crucial in some cases
      }

//------------------------------------------------------------ COUNTER STARTS
    increment_all(cuts::entry_point);
    ++counter[ch::_1l_2tau][cuts::entry_point];

//-------------------------------------------------------------- PRESELECTION
    std::vector<RecoLepton> preselected_leptons;
    preselected_leptons.reserve(nleptons);
    for(auto & lept: leptons)
      if(passes_preselection(lept)) preselected_leptons.push_back(lept);

    if(preselected_leptons.size() == 1)
    {
//====================== 2 TAU SINGLE LEPTON CHANNEL =========================
      ++counter[ch::_1l_2tau][cuts::PS];

//--- single tight lepton
      const auto & lepton = preselected_leptons[0];
      if(! (lepton.mva_tth > tight_mva_wp &&
            lepton.pt > 20                &&
            lepton.rel_iso < 0.1          &&
            lepton.sip3d < 4.0            &&
            ((lepton.is_muon()       &&
              lepton.med_mu_id >= 1   )   ||
             (lepton.is_electron()   && lepton.pass_conv_veto >= 1 &&
                                       lepton.lost_hits == 0       &&
                                       lepton.ele_mva_id >= 2       ))))
        continue;
      ++counter[ch::_1l_2tau][cuts::tight_lepton];

//--- at least two hadronic jets
      if(hadronic_jets.size() < 2) continue;
      ++counter[ch::_1l_2tau][cuts::j2_plus];

//--- at least two loose bjets or one medium bjet
      if(bjets["loose"].size() < 2 && bjets["medium"].size() < 1) continue;
      ++counter[ch::_1l_2tau][cuts::bjet_2l_1m];

//--- exactly two good taus
      std::vector<HadronicTau> good_taus;
      for(auto & tau: taus)
        if(tau.pt > 20              &&
           std::fabs(tau.eta) < 2.3 &&
           tau.decmode >= 1         &&
           tau.id_mva >= 4          &&
           tau.anti_e >= 2          &&
           tau.anti_mu >= 2          )
          good_taus.push_back(tau);
//--- TODO: check if our tau overlaps with some other object; remove duplicates

      if(good_taus.size() == 2)
        ++counter[ch::_1l_2tau][cuts::good_tau];

      continue;
    }
    else if(preselected_leptons.size() == 0) continue;

    increment_all(cuts::PS);

//--- let's order the leptons by their pT beforehand
    std::sort(preselected_leptons.begin(),
              preselected_leptons.end(),
              [](const RecoLepton & lhs,
                 const RecoLepton & rhs) -> bool
      {
        return rhs.pt < lhs.pt;
      });

//---------------------------------------------------------- NOF GOOD LEPTONS
//--- we need to count, how many tight and loose leptons we have
    std::vector<RecoLepton> loose_leptons,
                            tight_leptons;
    for(auto & lept: preselected_leptons)
    {
      if(lept.mva_tth > loose_mva_wp) loose_leptons.push_back(lept);
      if(lept.mva_tth > tight_mva_wp) tight_leptons.push_back(lept);
    }

//--- require exactly 2/3 tight leptons or 4 loose leptons
    std::vector<RecoLepton> selected_leptons;
    if(tight_leptons.size() == 2 ||
       tight_leptons.size() == 3  ) selected_leptons = tight_leptons;
    else
    if(loose_leptons.size() == 4)   selected_leptons = loose_leptons;
    else continue;
    const std::size_t nof_selected_leptons = selected_leptons.size();

    increment_all(cuts::good_leptons);

//------------------------------------------------------- DANGLING LEPTON CUT
    if((nof_selected_leptons == 2 && loose_leptons.size() == 1) ||
       (nof_selected_leptons == 3 && loose_leptons.size() == 1))
      continue;

    for(ch channel: {ch::ee, ch::emu, ch::mumu, ch::_3l})
      ++counter[channel][cuts::dangling];

//------------------------------------------ DILEPTON INVARIANT MASS > 12 GeV
    bool proceed = true; // this guy is used throughout the analysis
    for(unsigned j = 0; j < nof_selected_leptons && proceed; ++j)
      for(unsigned k = 0; k < j && proceed; ++k)
        if((selected_leptons[j].p4 + selected_leptons[k].p4).mass() < 12.0)
          proceed = false;
    if(! proceed) continue;

    increment_all(cuts::min_dilep_mass);

//-------------------------------------------------------- LEPTON PT > 20, 10
    if(! (selected_leptons[0].pt > 20 &&           // leading lepton
          selected_leptons[1].pt > 10) ) continue; // subleading lepton

    increment_all(cuts::pT2010);

//------------------------------------------------ 2+ HADRONIC JETS (>25 GeV)
    if(hadronic_jets.size() < 2) continue;

    increment_all(cuts::j2_plus);

//---------------------------------------- 2+ LOOSE B JETS / 1+ MEDIUM B JETS
    if(bjets["loose"].size() < 2 && bjets["medium"].size() < 1) continue;

    increment_all(cuts::bjet_2l_1m);

//-------------------------------------------------------------- MEDIUM MU ID
//--- applies to all muons?
    for(auto & lept: selected_leptons)
      if(lept.is_muon() && lept.med_mu_id < 1)
      {
        proceed = false;
        break;
      }
    if(! proceed) continue;

    for(ch channel: {ch::emu, ch::mumu, ch::_3l, ch::_4l})
      ++counter[channel][cuts::medium_mu_id];

//--- tight lepton cuts
    if(nof_selected_leptons < 4)
    {
//-------------------------------------------------- ELECTRON CONVERSION VETO
//--- applies to tight electrons only
      for(auto & lept: selected_leptons)
        if(lept.is_electron() && lept.pass_conv_veto < 1)
        {
          proceed = false;
          break;
        }
      if(! proceed) continue;
      for(ch channel: {ch::ee, ch::emu, ch::_3l})
        ++counter[channel][cuts::conv_veto];

//--------------------------------------------------------------- 0 LOST HITS
//--- applies to tight electrons only
      for(auto & lept: selected_leptons)
        if(lept.is_electron() && lept.lost_hits != 0)
        {
          proceed = false;
          break;
        }

      if(! proceed) continue;

      for(ch channel: {ch::ee, ch::emu, ch::_3l})
        ++counter[channel][cuts::lost_hits_0];

//--------------------------------------------------- ELECTRON IDENTIFICATION
//--- applies to tight electrons only
      for(auto & lept: selected_leptons)
        if(lept.is_electron() && lept.ele_mva_id < 2)
        {
          proceed = false;
          break;
        }

      if(! proceed) continue;

      for(ch channel: {ch::ee, ch::emu, ch::_3l})
        ++counter[channel][cuts::ele_id];

      ++counter[ch::_2l_1tau][cuts::specific_cuts]; // for dilepton + tau

//-------------------------------------------------- RELATIVE ISOLATION < 0.1
//--- applies to tight leptons only
      for(auto & lept: selected_leptons)
        if(lept.rel_iso >= 0.1)
        {
          proceed = false;
          break;
        }
      if(! proceed) continue;

      for(ch channel: {ch::ee, ch::mumu, ch::emu, ch::_3l, ch::_2l_1tau})
        ++counter[channel][cuts::rel_iso_01];

//--------------------------------------------------------------- SIP3D < 4.0
//--- applies to tight leptons only
      for(auto & lept: selected_leptons)
        if(lept.sip3d >= 4.0)
        {
          proceed = false;
          break;
        }

      if(! proceed) continue;

      for(ch channel: {ch::ee, ch::mumu, ch::emu, ch::_3l, ch::_2l_1tau})
        ++counter[channel][cuts::sip3d_4];
    }

//=========================== DILEPTON CHANNEL ==============================
    if(nof_selected_leptons == 2)
    {
      const RecoLepton & lept_0 = selected_leptons[0]; // make it const?
      const RecoLepton & lept_1 = selected_leptons[1];

      ch channel = ch::unspecified;

      if(lept_0.is_electron() && lept_1.is_electron()) channel = ch::ee;
      else if(lept_0.is_muon() && lept_1.is_muon())    channel = ch::mumu;
      else channel = ch::emu;

      ++counter[channel][cuts::tight_mva];
      ++counter[ch::_2l_1tau][cuts::tight_mva];

//----------------------------------------------------------------- SAME SIGN
      if(lept_0.pdg_id * lept_1.pdg_id < 0) continue;

      ++counter[channel][cuts::ss];
      ++counter[ch::_2l_1tau][cuts::ss];

//---------------------------------------------------------- 4+ HADRONIC JETS
      if(hadronic_jets.size() < 4) continue;

      ++counter[channel][cuts::j4_plus];
      ++counter[ch::_2l_1tau][cuts::j4_plus];

//-------------------------------------------------------------- MET_LD > 0.2
//--- merge all jets
      std::vector<RecoJet> all_bjets,
                           all_selected_jets;
      std::set_union
        (
          bjets["loose"].begin(), bjets["loose"].end(),
          bjets["medium"].begin(), bjets["medium"].end(),
          std::back_inserter(all_bjets),
          [](const RecoJet & lhs, const RecoJet & rhs) -> bool
          {
            return lhs.idx < rhs.idx;
          }
        );
      std::set_union
        (
          all_bjets.begin(), all_bjets.end(),
          hadronic_jets.begin(), hadronic_jets.end(),
          std::back_inserter(all_selected_jets),
          [](const RecoJet & lhs, const RecoJet & rhs) -> bool
          {
            return lhs.idx < rhs.idx;
          }
        );

//--- calculate MHT
      LV mht_vec(0, 0, 0, 0);
      for(auto & jet: all_selected_jets)
        mht_vec += jet.p4;
      mht_vec += lept_0.p4 + lept_1.p4;
      const Double_t mht_pt = mht_vec.pt();
      const Double_t met_ld = met_coef * met_pt + mht_coef * mht_pt;
      if(met_ld <= 0.2) continue;

      ++counter[channel][cuts::met_ld_02];
      ++counter[ch::_2l_1tau][cuts::met_ld_02];

//-------------------------------------------------------- LEPTON PT > 20, 20
      if(lept_0.pt <= 20 || lept_1.pt <= 20) continue;

      ++counter[channel][cuts::pT2020];
      ++counter[ch::_2l_1tau][cuts::pT2020];

//----------------------------------------- SCALAR SUM(L0, L1, MET) > 100 GeV
      if(lept_0.pt + lept_1.pt + met_pt <= 100) continue;

      ++counter[channel][cuts::ht_l1l2_met_100];
      ++counter[ch::_2l_1tau][cuts::ht_l1l2_met_100];

//-------------------------------------------------------------------- Z VETO
      if(std::fabs((lept_0.p4 + lept_1.p4).mass() - z_mass) <= z_th) continue;

      ++counter[channel][cuts::zveto];
      ++counter[ch::_2l_1tau][cuts::zveto];

//-------------------------------------------------------------- TIGHT CHARGE
      if(lept_0.tight_charge < 2 || lept_1.tight_charge < 2) continue;

      ++counter[channel][cuts::charge_quality];
      ++counter[ch::_2l_1tau][cuts::charge_quality];

//======================== DILEPTON + TAU CHANNEL ===========================
      {
//--- see if any of our taus is a good candidate
        std::vector<HadronicTau> good_taus;
        for(auto & tau: taus)
          if(tau.pt > 20              &&
             std::fabs(tau.eta) < 2.3 &&
             tau.decmode >= 1         &&
             tau.id_mva >= 4          &&
             tau.anti_e >= 2          &&
             tau.anti_mu >= 2          )
            good_taus.push_back(tau);
//--- TODO: check if our tau overlaps with some other object; remove duplicates

        if(good_taus.size() == 1)
          ++counter[ch::_2l_1tau][cuts::good_tau];
      }

//------------------------------------------------ PLOT OF KINEMATIC VARIABLES
      {
        Double_t min_dR_l2j = 1000;
        Double_t ht = lept_0.pt + lept_1.pt;
        LV ht_vec = lept_0.p4 + lept_1.p4;
        for(auto & jet: hadronic_jets)
        {
          const Double_t dR_tmp =
            std::sqrt(std::pow(lept_1.eta - jet.eta, 2) +
                      std::pow(lept_1.phi - jet.phi, 2));
          if(dR_tmp < min_dR_l2j) min_dR_l2j = dR_tmp;
          ht += jet.pt;
          ht_vec += jet.p4;
        }
        const Double_t pt_trailing = lept_1.pt;
        const Double_t eta_trailing = std::fabs(lept_1.eta);
        const Double_t mt_metl1 =
            (lept_0.p4 + LV(met_pt, met_eta, met_phi, met_mass)).mass();
        const Double_t mht = std::fabs(ht_vec.pt());
        hm[channel][cp::final].fill(pt_trailing, eta_trailing, min_dR_l2j,
                                    mt_metl1, ht, mht);
      }

//---------------------------------------------------------------- PDG ID PLOT
      fill_pdg_plot(gen_leptons, gen_jets, selected_leptons, channel);

    }

//=========================== TRILEPTON CHANNEL =============================
    else if(nof_selected_leptons == 3)
    {
      ++counter[ch::_3l][cuts::tight_mva];

//------------------------------------------ 4+ HADRONIC JETS or MET_LD > 0.2
      if(hadronic_jets.size() < 4)
      {
        std::vector<RecoJet> all_bjets,
                             all_selected_jets;
        std::set_union
          (
            bjets["loose"].begin(), bjets["loose"].end(),
            bjets["medium"].begin(), bjets["medium"].end(),
            std::back_inserter(all_bjets),
            [](const RecoJet & lhs, const RecoJet & rhs) -> bool
            {
              return lhs.idx < rhs.idx;
            }
          );
        std::set_union
          (
            all_bjets.begin(), all_bjets.end(),
            hadronic_jets.begin(), hadronic_jets.end(),
            std::back_inserter(all_selected_jets),
            [](const RecoJet & lhs, const RecoJet & rhs) -> bool
            {
              return lhs.idx < rhs.idx;
            }
          );

//--- calculate MHT
        LV mht_vec(0, 0, 0, 0);
        for(auto & jet: all_selected_jets)
          mht_vec += jet.p4;
        for(auto & lept: selected_leptons)
          mht_vec += lept.p4;
        const Double_t mht_pt = mht_vec.pt();
        const Double_t met_ld = met_coef * met_pt + mht_coef * mht_pt;
        if(met_ld <= 0.2) continue;
      }
      ++counter[ch::_3l][cuts::j4_plus_met_ld_02];

//---------------------------------------------------------------- SFOS ZVETO
      for(unsigned j = 0; j < 3 && proceed; ++j)
        for(unsigned k = 0; k < j && proceed; ++k)
          if(selected_leptons[j].pdg_id == -selected_leptons[k].pdg_id &&
             std::fabs((selected_leptons[j].p4 +
                        selected_leptons[k].p4).mass() - z_mass) <= z_th)
              proceed = false;
      if(! proceed) continue;

      ++counter[ch::_3l][cuts::sfos_zveto];

//---------------------------------------------------------------- PDG ID PLOT
      fill_pdg_plot(gen_leptons, gen_jets, selected_leptons, ch::_3l);
    }

//=========================== 4-LEPTON CHANNEL ==============================
    else
    {
      ++counter[ch::_4l][cuts::loose_mva];

//-------------------------------------------------------- NEUTRAL CHARGE SUM
      const Int_t charge_sum = std::accumulate
        (
          selected_leptons.begin(),
          selected_leptons.end(),
          0,
          [](Int_t lhs, const RecoLepton & rhs)
          {
            const Int_t charge = rhs.pdg_id > 0 ? 1 : -1;
            return lhs + charge;
          }
        );
      if(charge_sum != 0) continue;

      ++counter[ch::_4l][cuts::neutral_sum];

//---------------------------------------------------------------- SFOS ZVETO
      for(unsigned j = 0; j < 4 && proceed; ++j)
        for(unsigned k = 0; k < j && proceed; ++k)
          if(selected_leptons[j].pdg_id == -selected_leptons[k].pdg_id &&
             std::fabs((selected_leptons[j].p4 +
                        selected_leptons[k].p4).mass() - z_mass) <= z_th)
              proceed = false;
      if(! proceed) continue;

      ++counter[ch::_4l][cuts::sfos_zveto];

//---------------------------------------------------------------- PDG ID PLOT
      fill_pdg_plot(gen_leptons, gen_jets, selected_leptons, ch::_4l);
    }
  }
//===========================================================================
//===========================================================================

//--- write the results to table.txt
  const std::string results_fn =
    (boost::filesystem::path(output_dir) /
     boost::filesystem::path("table.txt")).string();
  std::ofstream results(results_fn);
  if(results.is_open())
  {
    log_file << "Writing results to file: "
             << results_fn
             << "\n";

    for(auto & channels: counter)
    {
      std::vector<std::string> counter_labels,
                               counter_numbers;

      counter_labels.push_back("channel");
      counter_numbers.push_back(ch_str.at(channels.first));
      for(auto & kv: channels.second)
      {
        counter_labels.push_back(cuts_str.at(kv.first));
        counter_numbers.push_back(std::to_string(kv.second));
      }

      const std::string label_str = join_strings(counter_labels);
      const std::string numbers_str = join_strings(counter_numbers);

      results << label_str << "\n"
              << numbers_str << "\n";
    }

    results.close();
  }
  else
    log_file << "Couldn't open the following file for writing: "
             << results_fn
             << "\n";

  hm.write(histogram_fn);
  log_file << "Wrote the histograms to: "
           << histogram_fn
           << "\n";
  pdg_id_plots.write(pdgid_histogram_fn);
  log_file << "Wrote PDG ID plots to: "
           << pdgid_histogram_fn
           << "\n";

  log_file.close();
  clock.Show("SynchTTH");

  return EXIT_SUCCESS;
}
