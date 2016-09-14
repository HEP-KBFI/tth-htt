#include <iostream> // std::cerr, std::fixed
#include <fstream> // std::ofstream
#include <string> // std::string
#include <vector> // std::vector<>
#include <cstdlib> // EXIT_SUCCESS, EXIT_FAILURE
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
#include "DataFormats/Math/interface/deltaR.h" // deltaR

#include <Rtypes.h> // Int_t, Long64_t, Double_t
#include <TChain.h> // TChain
#include <TTree.h> // TTree
#include <TBenchmark.h> // TBenchmark
#include <TString.h> // TString, Form

#include <boost/filesystem.hpp> // boost::filesystem::
#include <boost/algorithm/string/predicate.hpp> // boost::iequals()

#include "tthAnalysis/HiggsToTauTau/interface/GenericHistManager.h" // GenericHistManager, join_strings()
#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h" // RecoLepton
#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h" // RecoHadTau
#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h" // GenLepton
#include "tthAnalysis/HiggsToTauTau/interface/GenJet.h" // GenJet
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTau.h" // GenHadTau
#include "tthAnalysis/HiggsToTauTau/interface/TMVAInterface.h" // TMVAInterface
#include "tthAnalysis/HiggsToTauTau/interface/mvaInputVariables.h" // auxiliary functions for computing input variables of the MVA used for signal extraction in the 2lss_1tau category 
#include "tthAnalysis/HiggsToTauTau/interface/KeyTypes.h"
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronReader.h" // RecoElectronReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonReader.h" // RecoMuonReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauReader.h" // RecoHadTauReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetReader.h" // RecoJetReader
#include "tthAnalysis/HiggsToTauTau/interface/GenLeptonReader.h" // GenLeptonReader
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTauReader.h" // GenHadTauReader
#include "tthAnalysis/HiggsToTauTau/interface/GenJetReader.h" // GenJetReader
#include "tthAnalysis/HiggsToTauTau/interface/convert_to_ptrs.h" // convert_to_ptrs
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorLoose.h" // RecoElectronCollectionSelectorLoose
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorFakeable.h" // RecoElectronCollectionSelectorFakeable
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorTight.h" // RecoElectronCollectionSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorLoose.h" // RecoMuonCollectionSelectorLoose
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorFakeable.h" // RecoMuonCollectionSelectorFakeable
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorTight.h" // RecoMuonCollectionSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauCollectionSelectorTight.h" // RecoHadTauCollectionSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelector.h" // RecoJetCollectionSelector
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelectorBtag.h" // RecoJetCollectionSelectorBtagLoose, RecoJetCollectionSelectorBtagMedium
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_2015, kEra_2016

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
 * @brief Auxiliary function used for sorting leptons by decreasing pT
 * @param Given pair of leptons
 * @return True, if first lepton has higher pT; false if second lepton has higher pT
 */
//bool isHigherPt(const GenParticle& particle1, const GenParticle& particle2)
//{
//  return (particle1.pt_ > particle2.pt_);
//}
bool isHigherPt_ptr(const GenParticle* particle1, const GenParticle* particle2)
{
  return (particle1->pt_ > particle2->pt_);
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
  bool isMC = cfg_presel.getParameter<bool>("isMC"); 
  std::string jet_btagWeight_branch = ( isMC ) ? "Jet_bTagWeight" : "";
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
  GenericHistManager<ch, cp> hm;
  hm.add_channel(ch::ee, "ee")
    .add_channel(ch::mumu, "mumu")
    .add_channel(ch::emu, "emu");
  hm.add_cutpoint({cp::final, "final"});
  hm.add_variable({"pT(l2)", 16, 10, 90})
    .add_variable({"|eta(l2)|", 12, 0, 2.4})
    .add_variable({"min(dR(l2,j))", 12, 0, 4})
    .add_variable({"mT(MET,l1)", 15, 0, 200})
    .add_variable({"HT", 15, 0, 1200})
    .add_variable({"MHT", 12, 0, 250})
    .add_variable({"mvaDiscr_2lss", 6, 0.5, 6.5});
  hm.initialize();

//--- set up PDG ID plots
  enum match_type { same, flipped, gen_match, due_jets, no_overlap };
  GenericHistManager<match_type, ch> pdg_id_plots;
  pdg_id_plots.add_channel(match_type::same,       "same_sign")
              .add_channel(match_type::flipped,    "flipped_sign")
              .add_channel(match_type::gen_match,  "gen_match")
              .add_channel(match_type::due_jets,   "due_jets")
              .add_channel(match_type::no_overlap, "no_overlap");
  pdg_id_plots.add_cutpoint({ch::ee,       "ee"})
              .add_cutpoint({ch::mumu,     "mumu"})
              .add_cutpoint({ch::emu,      "emu"})
              .add_cutpoint({ch::_3l,      "3l"})
              .add_cutpoint({ch::_4l,      "4l"})
              .add_cutpoint({ch::_1l_2tau, "1l_2tau"})
              .add_cutpoint({ch::_2l_1tau, "2l_1tau"});
  pdg_id_plots.add_variable({"e", 3, 0, 3})
              .add_variable({"mu", 3, 0, 3})
              .add_variable({"tau", 3, 0, 3});
  pdg_id_plots.initialize();
  const std::map<int, std::string> pdg_id_keys =
  {
    {11, "e"},
    {13, "mu"},
    {15, "tau"}
  };
  auto fill_pdg_plot = [&pdg_id_keys, &pdg_id_plots]
                         (const std::vector<GenLepton> & gen_leptons,
                          const std::vector<GenJet> & gen_jets,
                          const std::vector<const RecoLepton*> & leptons,
                          const std::vector<const RecoHadTau*> * const taus,
                          const std::vector<GenHadTau> * const gen_taus,
                          ch channel,
                          bool check_pdg_id, double evtWeight = 1.) -> void
  {
    for(auto & lepton: leptons)
    {
      bool any_overlap = false;
      std::string pdg_id_key = pdg_id_keys.at(std::abs(lepton->pdgId_));

      for(auto & gen_lepton: gen_leptons)
        if(lepton->is_overlap(gen_lepton, 0.3))
        {
          if(check_pdg_id)
          {
            if(lepton->pdgId_ == gen_lepton.pdgId_)
            {
              pdg_id_plots[match_type::same][channel].fill(pdg_id_key, evtWeight, 1);
              any_overlap = true;
              break;
            }
            else if(lepton->pdgId_ == -gen_lepton.pdgId_)
            {
              pdg_id_plots[match_type::flipped][channel].fill(pdg_id_key, evtWeight, 1);
              any_overlap = true;
              break;
            }
          }
          else
          {
            if(std::abs(lepton->pdgId_) == std::abs(gen_lepton.pdgId_))
            {
              pdg_id_plots[match_type::gen_match][channel].fill(pdg_id_key, evtWeight, 1);
              any_overlap = true;
              break;
            }
          }
        }

      if(any_overlap) continue;
      for(auto & gen_jet: gen_jets)
        if(lepton->is_overlap(gen_jet, 0.3))
        {
          pdg_id_plots[match_type::due_jets][channel].fill(pdg_id_key, evtWeight, 1);
          any_overlap = true;
          break;
        }

      if(any_overlap) continue;
      pdg_id_plots[match_type::no_overlap][channel].fill(pdg_id_key, evtWeight, 1);
    }

    if(taus && gen_taus)
    {
      for(auto & tau: *taus)
      {
        bool any_overlap = false;
	int tau_pdgId = -15*tau->charge_;
        std::string pdg_id_key = pdg_id_keys.at(std::abs(tau_pdgId));
        for(auto & gen_tau: *gen_taus)
          if(tau->is_overlap(gen_tau, 0.3))
          {
            pdg_id_plots[match_type::gen_match][channel].fill(pdg_id_key, evtWeight, 1);
            any_overlap = true;
            break;
          }

        if(any_overlap) continue;
        for(auto & gen_jet: gen_jets)
          if(tau->is_overlap(gen_jet, 0.3))
          {
            pdg_id_plots[match_type::due_jets][channel].fill(pdg_id_key, evtWeight, 1);
            any_overlap = true;
            break;
          }

        if(any_overlap) continue;
        pdg_id_plots[match_type::no_overlap][channel].fill(pdg_id_key, evtWeight, 1);
      }
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

//--- declare data-taking period
  int era = kEra_2015;

//--- declare the variables
  RUN_TYPE run;
  chain.SetBranchAddress(RUN_KEY, &run);
  LUMI_TYPE lumi;
  chain.SetBranchAddress(LUMI_KEY, &lumi);
  EVT_TYPE evt;
  chain.SetBranchAddress(EVT_KEY, &evt);
  
  RecoElectronReader* electronReader = new RecoElectronReader("nselLeptons", "selLeptons");
  electronReader->setBranchAddresses(&chain);
  RecoElectronCollectionSelectorLoose preselElectronSelector;
  RecoElectronCollectionSelectorTight tightElectronSelector(era);
  RecoMuonReader* muonReader = new RecoMuonReader(era, "nselLeptons", "selLeptons");
  muonReader->setBranchAddresses(&chain);
  RecoMuonCollectionSelectorLoose preselMuonSelector;
  RecoMuonCollectionSelectorTight tightMuonSelector(era);
  RecoHadTauReader* hadTauReader = new RecoHadTauReader("nTauGood", "TauGood");
  hadTauReader->setBranchAddresses(&chain);
  RecoHadTauCollectionSelectorTight hadTauSelector;
  RecoJetReader* jetReader = new RecoJetReader("nJet", "Jet");
  jetReader->setBranchName_BtagWeight(jet_btagWeight_branch);
  jetReader->setBranchAddresses(&chain);
  RecoJetCollectionSelector jetSelector;
  RecoJetCollectionSelectorBtagLoose jetSelectorBtagLoose(era);
  RecoJetCollectionSelectorBtagMedium jetSelectorBtagMedium(era);

  MET_PT_TYPE met_pt;
  chain.SetBranchAddress(MET_PT_KEY, &met_pt);
  MET_ETA_TYPE met_eta;
  chain.SetBranchAddress(MET_ETA_KEY, &met_eta);
  MET_PHI_TYPE met_phi;
  chain.SetBranchAddress(MET_PHI_KEY, &met_phi);
  LV met_p4(met_pt, met_eta, met_phi, 0.);

  GenLeptonReader* genLeptonReader = new GenLeptonReader("nGenLep", "GenLep");
  genLeptonReader->setBranchAddresses(&chain);
  GenHadTauReader* genHadTauReader = new GenHadTauReader("nGenHadTaus", "GenHadTaus");
  genHadTauReader->setBranchAddresses(&chain);
  GenJetReader* genJetReader = new GenJetReader("nGenJet", "GenJet");
  genJetReader->setBranchAddresses(&chain);

//--- initialize BDTs used to discriminate ttH vs. ttV and ttH vs. ttbar 
//    in 2lss_1tau category of ttH multilepton analysis
  std::string mvaFileName_2lss_ttV = "tthAnalysis/HiggsToTauTau/data/2lss_ttV_BDTG.weights.xml";
  std::vector<std::string> mvaInputVariables_2lss_ttV;
  mvaInputVariables_2lss_ttV.push_back("max(abs(LepGood_eta[iF_Recl[0]]),abs(LepGood_eta[iF_Recl[1]]))");
  mvaInputVariables_2lss_ttV.push_back("MT_met_lep1");
  mvaInputVariables_2lss_ttV.push_back("nJet25_Recl");
  mvaInputVariables_2lss_ttV.push_back("mindr_lep1_jet");
  mvaInputVariables_2lss_ttV.push_back("mindr_lep2_jet");
  mvaInputVariables_2lss_ttV.push_back("LepGood_conePt[iF_Recl[0]]");
  mvaInputVariables_2lss_ttV.push_back("LepGood_conePt[iF_Recl[1]]");
  TMVAInterface mva_2lss_ttV(mvaFileName_2lss_ttV, mvaInputVariables_2lss_ttV, { "iF_Recl[0]", "iF_Recl[1]", "iF_Recl[2]" });

  std::string mvaFileName_2lss_ttbar = "tthAnalysis/HiggsToTauTau/data/2lss_ttbar_BDTG.weights.xml";
  std::vector<std::string> mvaInputVariables_2lss_ttbar;
  mvaInputVariables_2lss_ttbar.push_back("max(abs(LepGood_eta[iF_Recl[0]]),abs(LepGood_eta[iF_Recl[1]]))");
  mvaInputVariables_2lss_ttbar.push_back("nJet25_Recl");
  mvaInputVariables_2lss_ttbar.push_back("mindr_lep1_jet");
  mvaInputVariables_2lss_ttbar.push_back("mindr_lep2_jet");
  mvaInputVariables_2lss_ttbar.push_back("min(met_pt,400)");
  mvaInputVariables_2lss_ttbar.push_back("avg_dr_jet");
  mvaInputVariables_2lss_ttbar.push_back("MT_met_lep1");
  TMVAInterface mva_2lss_ttbar(mvaFileName_2lss_ttbar, mvaInputVariables_2lss_ttbar, { "iF_Recl[0]", "iF_Recl[1]", "iF_Recl[2]" });

  std::map<std::string, double> mvaInputs;

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
    std::vector<RecoElectron> electrons = electronReader->read();
    std::vector<const RecoElectron*> electron_ptrs = convert_to_ptrs(electrons);
    std::vector<const RecoElectron*> preselElectrons = preselElectronSelector(electron_ptrs);
    std::vector<const RecoElectron*> tightElectrons = tightElectronSelector(preselElectrons);
    std::vector<RecoMuon> muons = muonReader->read();
    std::vector<const RecoMuon*> muon_ptrs = convert_to_ptrs(muons);
    std::vector<const RecoMuon*> preselMuons = preselMuonSelector(muon_ptrs);
    std::vector<const RecoMuon*> tightMuons = tightMuonSelector(preselMuons);

//--- create the jet collection
    std::vector<RecoJet> jets = jetReader->read();
    std::vector<const RecoJet*> jet_ptrs = convert_to_ptrs(jets);
    std::vector<const RecoJet*> selJets = jetSelector(jet_ptrs);
    // TO-DO: clean selJets collection w.r.t tightLeptons and selHadTaus

//--- compute event-level weight for data/MC correction of b-tagging efficiency and mistag rate
//   (using the method "Event reweighting using scale factors calculated with a tag and probe method", 
//    described on the BTV POG twiki https://twiki.cern.ch/twiki/bin/view/CMS/BTagShapeCalibration )
    double evtWeight = 1.;
    for ( auto & jet: selJets )
      evtWeight *= jet->BtagWeight_;

//--- create the generator level jet collection
    std::vector<GenJet> genJets = genJetReader->read();

//--- create the tau collection
    std::vector<RecoHadTau> hadTaus = hadTauReader->read();
    std::vector<const RecoHadTau*> hadTau_ptrs = convert_to_ptrs(hadTaus);
    std::vector<const RecoHadTau*> selHadTaus = hadTauSelector(hadTau_ptrs);

//--- create the collection of generator level leptons
    std::vector<GenLepton> genLeptons = genLeptonReader->read();

//--- create the collection of generator level hadronic taus
    std::vector<GenHadTau> genHadTaus = genHadTauReader->read();

//--- select b-jets
    std::map<std::string, std::vector<const RecoJet*>> bjets;
    bjets["loose"] = jetSelectorBtagLoose(jet_ptrs);
    bjets["medium"] = jetSelectorBtagMedium(jet_ptrs);

//------------------------------------------------------------ COUNTER STARTS
    increment_all(cuts::entry_point);
    ++counter[ch::_1l_2tau][cuts::entry_point];

//-------------------------------------------------------------- PRESELECTION
    std::vector<const RecoLepton*> preselLeptons;    
    preselLeptons.reserve(preselElectrons.size() + preselMuons.size());
    preselLeptons.insert(preselLeptons.end(), preselElectrons.begin(), preselElectrons.end());
    preselLeptons.insert(preselLeptons.end(), preselMuons.begin(), preselMuons.end());

    std::vector<const RecoLepton*> tightLeptons;    
    tightLeptons.reserve(tightElectrons.size() + tightMuons.size());
    tightLeptons.insert(tightLeptons.end(), tightElectrons.begin(), tightElectrons.end());
    tightLeptons.insert(tightLeptons.end(), tightMuons.begin(), tightMuons.end());

    if(preselLeptons.size() == 1)
    {
//====================== 2 TAU SINGLE LEPTON CHANNEL =========================
      ++counter[ch::_1l_2tau][cuts::PS];

//--- single tight lepton
      if ( !(tightLeptons.size() >= 1) )
        continue;
      ++counter[ch::_1l_2tau][cuts::tight_lepton];

//--- at least two jets
      if ( !(selJets.size() >= 2) ) continue;
      ++counter[ch::_1l_2tau][cuts::j2_plus];

//--- at least two loose bjets or one medium bjet
      if ( !(bjets["loose"].size() >= 2 || bjets["medium"].size() >= 1) ) continue;
      ++counter[ch::_1l_2tau][cuts::bjet_2l_1m];

//--- two good taus
      if ( !(selHadTaus.size() >= 2) ) continue;
      ++counter[ch::_1l_2tau][cuts::good_tau];
      fill_pdg_plot(genLeptons, genJets, preselLeptons,
		    &selHadTaus, &genHadTaus, ch::_1l_2tau, false);

      continue;
    }
    else if(preselLeptons.size() == 0) continue;

    increment_all(cuts::PS);

//---------------------------------------------------------- NOF GOOD LEPTONS
//--- we need to count, how many tight and loose leptons we have

//--- require exactly 2/3 tight leptons or 4 loose leptons
    std::vector<const RecoLepton*> selLeptons;
    if( tightLeptons.size() == 2 ||
        tightLeptons.size() == 3  ) selLeptons = tightLeptons;
    //CV: 4l category not used by ttH multilepton analysis of 2015 data
    //else
    //if(looseLeptons.size() == 4) selLeptons = looseLeptons;
    else continue;
//--- sort selected leptons by decreasing pT
    std::sort(selLeptons.begin(), selLeptons.end(), isHigherPt_ptr);
    const std::size_t nSelLeptons = selLeptons.size();

    increment_all(cuts::good_leptons);

//------------------------------------------------------- DANGLING LEPTON CUT
    if((nSelLeptons == 2 && preselLeptons.size() != 2) ||
       (nSelLeptons == 3 && preselLeptons.size() != 3))
      continue;

    for(ch channel: {ch::ee, ch::emu, ch::mumu, ch::_3l})
      ++counter[channel][cuts::dangling];

//------------------------------------------ DILEPTON INVARIANT MASS > 12 GeV
    bool proceed = true; // this guy is used throughout the analysis
    for(unsigned j = 0; j < nSelLeptons && proceed; ++j)
      for(unsigned k = 0; k < j && proceed; ++k)
        if((selLeptons[j]->p4_ + selLeptons[k]->p4_).mass() < 12.0)
          proceed = false;
    if(! proceed) continue;

    increment_all(cuts::min_dilep_mass);

//-------------------------------------------------------- LEPTON PT > 20, 10
    if(! (selLeptons[0]->pt_ > 20. &&           // leading lepton
          selLeptons[1]->pt_ > 10.) ) continue; // subleading lepton

    increment_all(cuts::pT2010);

//------------------------------------------------ 2+ JETS (>25 GeV)
    if ( !(selJets.size() >= 2) ) continue;

    increment_all(cuts::j2_plus);

//---------------------------------------- 2+ LOOSE B JETS / 1+ MEDIUM B JETS
    if ( !(bjets["loose"].size() >= 2 || bjets["medium"].size() >= 1) ) continue;

    increment_all(cuts::bjet_2l_1m);

//-------------------------------------------------------------- MEDIUM MU ID
//--- CV: not neccessary anymore ?
    //for ( auto & lepton: selLeptons)
    //  if(lept.is_muon() && lept.muon_passesMediumIdPOG_ < 1)
    //  {
    //    proceed = false;
    //    break;
    //  }
    if(! proceed) continue;

    for(ch channel: {ch::emu, ch::mumu, ch::_3l, ch::_4l})
      ++counter[channel][cuts::medium_mu_id];

//--- tight lepton cuts
    if ( nSelLeptons < 4 )
    {
//-------------------------------------------------- ELECTRON CONVERSION VETO
//--- CV: not neccessary anymore ?
      //for(auto & lept: selected_leptons)
      //  if(lept.is_electron() && lept.electron_passesConversionVeto_ < 1)
      //  {
      //    proceed = false;
      //    break;
      //  }
      if(! proceed) continue;
      for(ch channel: {ch::ee, ch::emu, ch::_3l})
        ++counter[channel][cuts::conv_veto];

//--------------------------------------------------------------- 0 LOST HITS
//--- CV: not neccessary anymore ?
      //for(auto & lept: selected_leptons)
      //  if(lept.is_electron() && lept.electron_nLostHits_ != 0)
      //  {
      //    proceed = false;
      //    break;
      //  }
      if(! proceed) continue;

      for(ch channel: {ch::ee, ch::emu, ch::_3l})
        ++counter[channel][cuts::lost_hits_0];

//--------------------------------------------------- ELECTRON IDENTIFICATION
//--- CV: not neccessary anymore ?
      //for(auto & lept: selected_leptons)
      //  if(lept.is_electron() && lept.electron_mvaRawPOG_ < 2)
      //  {
      //    proceed = false;
      //    break;
      //  }
      if(! proceed) continue;

      for(ch channel: {ch::ee, ch::emu, ch::_3l})
        ++counter[channel][cuts::ele_id];

      ++counter[ch::_2l_1tau][cuts::specific_cuts]; // for dilepton + tau

//-------------------------------------------------- RELATIVE ISOLATION < 0.1
//--- CV: not neccessary anymore ?
      //for(auto & lept: selected_leptons)
      //  if(lept.rel_iso >= 0.1)
      //  {
      //    proceed = false;
      //    break;
      //  }
      if(! proceed) continue;

      for(ch channel: {ch::ee, ch::mumu, ch::emu, ch::_3l, ch::_2l_1tau})
        ++counter[channel][cuts::rel_iso_01];

//--------------------------------------------------------------- SIP3D < 4.0
//--- CV: not neccessary anymore ?
      //for(auto & lept: selected_leptons)
      //  if(lept.sip3d_ >= 4.0)
      //  {
      //    proceed = false;
      //    break;
      //  }
      if(! proceed) continue;

      for(ch channel: {ch::ee, ch::mumu, ch::emu, ch::_3l, ch::_2l_1tau})
        ++counter[channel][cuts::sip3d_4];
    }

//=========================== DILEPTON CHANNEL ==============================
    if ( nSelLeptons == 2 )
    {
      const RecoLepton * lepton1 = selLeptons[0]; // leading lepton
      const RecoLepton * lepton2 = selLeptons[1]; // subleading lepton
      assert(lepton1 && lepton2);

      ch channel = ch::unspecified;

      if      ( lepton1->is_electron() && lepton2->is_electron() ) channel = ch::ee;
      else if ( lepton1->is_muon()     && lepton2->is_muon()     ) channel = ch::mumu;
      else                                                         channel = ch::emu;

      ++counter[channel][cuts::tight_mva];
      ++counter[ch::_2l_1tau][cuts::tight_mva];

//----------------------------------------------------------------- SAME SIGN
      if ( !(lepton1->pdgId_ * lepton2->pdgId_) > 0 ) continue;

      ++counter[channel][cuts::ss];
      ++counter[ch::_2l_1tau][cuts::ss];

//------------------------------------------------------------------- 4+ JETS
      if ( !(selJets.size() >= 4) ) continue;

      ++counter[channel][cuts::j4_plus];
      ++counter[ch::_2l_1tau][cuts::j4_plus];

//-------------------------------------------------------------- MET_LD > 0.2
//--- calculate MHT
      LV mht_vec(0,0,0,0);
      for ( auto & jet: selJets )
        mht_vec += jet->p4_;
      mht_vec += lepton1->p4_ + lepton2->p4_;
      const Double_t mht_pt = mht_vec.pt();
      const Double_t met_ld = met_coef * met_pt + mht_coef * mht_pt;
      if ( !(met_ld >= 0.2) ) continue;

      ++counter[channel][cuts::met_ld_02];
      ++counter[ch::_2l_1tau][cuts::met_ld_02];

//-------------------------------------------------------- LEPTON PT > 20, 20
      if ( !(lepton1->pt_ >= 20. && lepton2->pt_ >= 20.) ) continue;

      ++counter[channel][cuts::pT2020];
      ++counter[ch::_2l_1tau][cuts::pT2020];

//----------------------------------------- SCALAR SUM(L0, L1, MET) > 100 GeV
      if ( !(lepton1->pt_ + lepton2->pt_ + met_pt >= 100) ) continue;

      ++counter[channel][cuts::ht_l1l2_met_100];
      ++counter[ch::_2l_1tau][cuts::ht_l1l2_met_100];

//-------------------------------------------------------------------- Z VETO
      if ( std::fabs((lepton1->p4_ + lepton2->p4_).mass() - z_mass) <= z_window ) continue;

      ++counter[channel][cuts::zveto];
      ++counter[ch::_2l_1tau][cuts::zveto];

//-------------------------------------------------------------- TIGHT CHARGE
      if ( !(lepton1->tightCharge_ >= 2 && lepton2->tightCharge_ >= 2) ) continue;

      ++counter[channel][cuts::charge_quality];
      ++counter[ch::_2l_1tau][cuts::charge_quality];

//--- compute output of BDTs used to discriminate ttH vs. ttV and ttH vs. ttbar 
//    in 2lss_1tau category of ttH multilepton analysis 
      mvaInputs["max(abs(LepGood_eta[iF_Recl[0]]),abs(LepGood_eta[iF_Recl[1]]))"] = std::max(std::fabs(lepton1->eta_), std::fabs(lepton2->eta_));
      mvaInputs["MT_met_lep1"]                = comp_MT_met_lep1(*lepton1, met_pt, met_phi);
      mvaInputs["nJet25_Recl"]                = comp_n_jet25_recl(selJets);
      mvaInputs["mindr_lep1_jet"]             = comp_mindr_lep1_jet(*lepton1, selJets);
      mvaInputs["mindr_lep2_jet"]             = comp_mindr_lep2_jet(*lepton2, selJets);
      mvaInputs["LepGood_conePt[iF_Recl[0]]"] = comp_lep1_conePt(*lepton1);
      mvaInputs["LepGood_conePt[iF_Recl[1]]"] = comp_lep2_conePt(*lepton2);
      mvaInputs["min(met_pt,400)"]            = std::min(met_pt, (Float_t)400.);
      mvaInputs["avg_dr_jet"]                 = comp_avg_dr_jet(selJets);

      double mvaOutput_2lss_ttV = mva_2lss_ttV(mvaInputs);
      double mvaOutput_2lss_ttbar = mva_2lss_ttbar(mvaInputs);

//--- compute integer discriminant based on both BDT outputs,
//    as defined in Table X of AN-2015/321
      Double_t mvaDiscr_2lss = -1;
      if      ( mvaOutput_2lss_ttbar > +0.3 && mvaOutput_2lss_ttV >  -0.1 ) mvaDiscr_2lss = 6.;
      else if ( mvaOutput_2lss_ttbar > +0.3 && mvaOutput_2lss_ttV <= -0.1 ) mvaDiscr_2lss = 5.;
      else if ( mvaOutput_2lss_ttbar > -0.2 && mvaOutput_2lss_ttV >  -0.1 ) mvaDiscr_2lss = 4.;
      else if ( mvaOutput_2lss_ttbar > -0.2 && mvaOutput_2lss_ttV <= -0.1 ) mvaDiscr_2lss = 3.;
      else if (                                mvaOutput_2lss_ttV >  -0.1 ) mvaDiscr_2lss = 2.;
      else                                                                  mvaDiscr_2lss = 1.;

//======================== DILEPTON + TAU CHANNEL ===========================

//---------------------------------------------------------------- PDG ID PLOT
      if ( selHadTaus.size() >= 1 )
      {
        ++counter[ch::_2l_1tau][cuts::good_tau]; // add fill_pdg_plot here as well
        fill_pdg_plot(genLeptons, genJets, selLeptons,
                      &selHadTaus, &genHadTaus, ch::_2l_1tau, true);
      }
      else
        fill_pdg_plot(genLeptons, genJets, selLeptons,
                      nullptr, nullptr, channel, true);

//------------------------------------------------ PLOT OF KINEMATIC VARIABLES
      {
        Double_t min_dR_l2j = 1000;
        Double_t ht = lepton1->pt_ + lepton2->pt_;
        LV ht_vec = lepton1->p4_ + lepton2->p4_;
        for ( auto & jet: selJets )
        {
          const Double_t dR = deltaR(lepton2->eta_, lepton2->phi_, jet->eta_, jet->phi_);
          if ( dR < min_dR_l2j ) min_dR_l2j = dR;
          ht += jet->pt_;
          ht_vec += jet->p4_;
        }
        const Double_t pt_trailing = lepton2->pt_;
        const Double_t eta_trailing = std::fabs(lepton2->eta_);
        const Double_t mt_metl1 = comp_MT_met_lep1(*lepton1, met_pt, met_phi);
        const Double_t mht = std::fabs(ht_vec.pt());
        hm[channel][cp::final].fill(evtWeight,
          pt_trailing, eta_trailing, min_dR_l2j, mt_metl1, ht, mht, mvaDiscr_2lss);
      }

    }

//=========================== TRILEPTON CHANNEL =============================
    else if ( nSelLeptons == 3 )
    {
      ++counter[ch::_3l][cuts::tight_mva];

//--------------------------------------------------- 4+ JETS or MET_LD > 0.2
      if ( selJets.size() < 4 )
      {

//--- calculate MHT
        LV mht_vec(0,0,0,0);
        for ( auto & jet: selJets )
          mht_vec += jet->p4_;
        for ( auto & lepton: selLeptons )
          mht_vec += lepton->p4_;
        const Double_t mht_pt = mht_vec.pt();
        const Double_t met_ld = met_coef * met_pt + mht_coef * mht_pt;
        if ( !(met_ld >= 0.2) ) continue;
      }
      ++counter[ch::_3l][cuts::j4_plus_met_ld_02];

//---------------------------------------------------------------- SFOS ZVETO
      for ( unsigned j = 0; j < 3 && proceed; ++j )
        for ( unsigned k = 0; k < j && proceed; ++k )
          if ( selLeptons[j]->pdgId_ == -selLeptons[k]->pdgId_ &&
             std::fabs((selLeptons[j]->p4_ +
                        selLeptons[k]->p4_).mass() - z_mass) <= z_window )
              proceed = false;
      if ( !proceed ) continue;

      ++counter[ch::_3l][cuts::sfos_zveto];

//---------------------------------------------------------------- PDG ID PLOT
      fill_pdg_plot(genLeptons, genJets, selLeptons,
                    nullptr, nullptr, ch::_3l, false);
    }

//=========================== 4-LEPTON CHANNEL ==============================
    else
    {
      ++counter[ch::_4l][cuts::loose_mva];

//-------------------------------------------------------- NEUTRAL CHARGE SUM
      const Int_t charge_sum = std::accumulate
        (
	  selLeptons.begin(),
          selLeptons.end(),
          0,
          [](Int_t lhs, const RecoLepton * rhs)
          {
            const Int_t charge = ( rhs->pdgId_ > 0 ) ? 1 : -1;
            return lhs + charge;
          }
        );
      if ( charge_sum != 0 ) continue;

      ++counter[ch::_4l][cuts::neutral_sum];

//---------------------------------------------------------------- SFOS ZVETO
      for ( unsigned j = 0; j < 4 && proceed; ++j )
        for ( unsigned k = 0; k < j && proceed; ++k )
          if ( selLeptons[j]->pdgId_ == -selLeptons[k]->pdgId_ &&
             std::fabs((selLeptons[j]->p4_ +
                        selLeptons[k]->p4_).mass() - z_mass) <= z_window)
              proceed = false;
      if ( !proceed ) continue;

      ++counter[ch::_4l][cuts::sfos_zveto];

//---------------------------------------------------------------- PDG ID PLOT
      fill_pdg_plot(genLeptons, genJets, selLeptons,
                    nullptr, nullptr, ch::_4l, false);
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
