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
    dangling,
    good_leptons,
    minDilepMass,
    pT2010,
    j2_plus,
    bjet_2l_1m,
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
    sfos_zveto
  };
  enum ch {
    ee = 0,
    mumu,
    emu,
    _3l,
    _4l,
    unspecified
  };

  const std::map<cuts, std::string> cuts_str =
  {
    {cuts::entry_point,       "entry point"},
    {cuts::PS,                "preselection"},
    {cuts::good_leptons,      "2/3 T leptons or 4 L leptons"},
    {cuts::dangling,          "dangling lepton cut"},
    {cuts::minDilepMass,      "minDilepMass>12 GeV"},
    {cuts::pT2010,            "pT(l1),pT(l2) >20,>10 GeV"},
    {cuts::j2_plus,           "nJet>=2 (25 GeV)"},
    {cuts::bjet_2l_1m,        "2+L bJet or 1+M bJet"},
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
    {cuts::sfos_zveto,        "SFOS Z veto"}
  };
  const std::map<ch, std::string> ch_str =
  {
    {ch::ee,   "ee"},
    {ch::mumu, "mumu"},
    {ch::emu,  "emu"},
    {ch::_3l,  "3l"},
    {ch::_4l,  "4l"}
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
        {cuts::minDilepMass,    0},
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
        {cuts::minDilepMass,    0},
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
        {cuts::minDilepMass,    0},
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
        {cuts::minDilepMass,      0},
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
        {cuts::entry_point,  0},
        {cuts::PS,           0},
        {cuts::good_leptons, 0},
        {cuts::minDilepMass, 0},
        {cuts::pT2010,       0},
        {cuts::j2_plus,      0},
        {cuts::bjet_2l_1m,   0}, // common end
        {cuts::medium_mu_id, 0},
        {cuts::loose_mva,    0},
        {cuts::neutral_sum,  0},
        {cuts::sfos_zveto,   0}
      }
    }
  };
  auto increment_all = [&counter](cuts c)
  {
    std::for_each
    (
      counter.begin(),
      counter.end(),
      [&counter,c] (typename decltype(counter)::value_type & p) -> void
      {
        ++p.second[c];
      }
    );
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
  const unsigned max_nleptons = 16;
  const unsigned max_njets = 32;
  const double z_mass = 91.1876;
  const double z_th = 10;
  const double met_coef = 0.00397;
  const double mht_coef = 0.00265;

//--- declare the variables
  Int_t nleptons;
  Int_t run;
  Int_t lumi;
  Int_t evt;
  Int_t njets;
  Double_t met_pt;
  Double_t met_eta;
  Double_t met_phi;
  Double_t met_mass;
  Double_t dxy        [max_nleptons];
  Double_t dz         [max_nleptons];
  Double_t rel_iso    [max_nleptons];
  Double_t sip3d      [max_nleptons];
  Double_t pt         [max_nleptons];
  Double_t eta        [max_nleptons];
  Double_t mva_tth    [max_nleptons];
  Double_t phi        [max_nleptons];
  Double_t mass       [max_nleptons];
  Double_t jet_pt     [max_njets];
  Double_t jet_eta    [max_njets];
  Double_t jet_phi    [max_njets];
  Double_t jet_csv    [max_njets];
  Double_t jet_mass   [max_njets];
  Int_t med_mu_id     [max_nleptons];
  Int_t pdg_id        [max_nleptons];
  Int_t ele_mva_id    [max_nleptons];
  Int_t lost_hits     [max_nleptons];
  Int_t loose_id      [max_nleptons];
  Int_t tight_charge  [max_nleptons];
  Int_t pass_conv_veto[max_nleptons];

  chain.SetBranchAddress("nselLeptons",               &nleptons);
  chain.SetBranchAddress("run",                       &run);
  chain.SetBranchAddress("lumi",                      &lumi);
  chain.SetBranchAddress("evt",                       &evt);
  chain.SetBranchAddress("nJet",                      &njets);
  chain.SetBranchAddress("met_pt",                    &met_pt);
  chain.SetBranchAddress("met_eta",                   &met_eta);
  chain.SetBranchAddress("met_phi",                   &met_phi);
  chain.SetBranchAddress("met_mass",                  &met_mass);
  chain.SetBranchAddress("selLeptons_dxy",            &dxy);
  chain.SetBranchAddress("selLeptons_dz",             &dz);
  chain.SetBranchAddress("selLeptons_relIso03",       &rel_iso);
  chain.SetBranchAddress("selLeptons_sip3d",          &sip3d);
  chain.SetBranchAddress("selLeptons_pt",             &pt);
  chain.SetBranchAddress("selLeptons_eta",            &eta);
  chain.SetBranchAddress("selLeptons_mvaTTH",         &mva_tth);
  chain.SetBranchAddress("selLeptons_phi",            &phi);
  chain.SetBranchAddress("selLeptons_mass",           &mass);
  chain.SetBranchAddress("Jet_pt",                    &jet_pt);
  chain.SetBranchAddress("Jet_eta",                   &jet_eta);
  chain.SetBranchAddress("Jet_phi",                   &jet_phi);
  chain.SetBranchAddress("Jet_btagCSV",               &jet_csv);
  chain.SetBranchAddress("Jet_mass",                  &jet_mass);
  chain.SetBranchAddress("selLeptons_mediumMuonId",   &med_mu_id);
  chain.SetBranchAddress("selLeptons_pdgId",          &pdg_id);
  chain.SetBranchAddress("selLeptons_eleMVAIdPhys14", &ele_mva_id);
  chain.SetBranchAddress("selLeptons_lostHits",       &lost_hits);
  chain.SetBranchAddress("selLeptons_looseIdPOG",     &loose_id);
  chain.SetBranchAddress("selLeptons_tightCharge",    &tight_charge);
  chain.SetBranchAddress("selLeptons_convVeto",       &pass_conv_veto);

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

//------------------------------------------------------------ COUNTER STARTS
    increment_all(cuts::entry_point);

    std::vector<std::pair<Int_t, Double_t>> preselected_leptons;

//--- loop over all leptons
    for(Int_t j = 0; j < nleptons; ++j)
    {
//-------------------------------------------------------------- PRESELECTION
//---  - dxy <= 500 um
//---  - dz < 1 mm
//---  - rel_iso < 0.5
      if(std::fabs(dxy[j])     <= 0.05 && // 500um in cm
         std::fabs(dz[j])      < 0.1   && // 1 mm in cm
         rel_iso[j]            < 0.5    )
      {
//--- we have a lepton

//--- electron
        if(std::abs(pdg_id[j]) == 11  &&
           lost_hits [j] <= 1         &&
           ele_mva_id[j] >= 1         &&
           pt        [j] > 7.0        &&
           std::fabs(eta[j]) < 2.5     )
          preselected_leptons.push_back(std::make_pair(j, pt[j]));

//--- muon
        else if(std::abs(pdg_id[j]) == 13 &&
                loose_id[j] >= 1          &&
                pt      [j] > 5.0         &&
                std::fabs(eta[j]) < 2.4    )
          preselected_leptons.push_back(std::make_pair(j, pt[j]));
      }
    }
    if(preselected_leptons.size() < 2) continue;

    increment_all(cuts::PS);

//--- let's order the leptons by their pT beforehand
    leading_lept(preselected_leptons);

//---------------------------------------------------------- NOF GOOD LEPTONS
//--- we need to count, how many tight and loose leptons we have
    std::vector<Int_t> loose_leptons,
                       tight_leptons;
    for(auto & lept: preselected_leptons)
    {
      const Int_t k = lept.first;
      if(mva_tth[k] > loose_mva_wp) loose_leptons.push_back(k);
      if(mva_tth[k] > tight_mva_wp) tight_leptons.push_back(k);
    }

//--- require exactly 2/3 tight leptons or 4 loose leptons
    std::vector<Int_t> selected_leptons;
    if(tight_leptons.size() == 2 ||
       tight_leptons.size() == 3  ) selected_leptons = tight_leptons;
    else
    if(loose_leptons.size() == 4  ) selected_leptons = loose_leptons; // >=4?
    else continue;
    const std::size_t nof_selected_leptons = selected_leptons.size();

    increment_all(cuts::good_leptons);

//------------------------------------------------------- DANGLING LEPTON CUT
    if((nof_selected_leptons == 2 && loose_leptons.size() == 1) ||
       (nof_selected_leptons == 3 && loose_leptons.size() == 1)  ) continue;

    for(ch channel: {ch::ee, ch::emu, ch::mumu, ch::_3l})
      ++counter[channel][cuts::dangling];

//------------------------------------------ DILEPTON INVARIANT MASS > 12 GeV
    bool proceed = true; // this guy is used throughout the analysis
    for(std::size_t j = 0; j < nof_selected_leptons; ++j)
    {
      for(std::size_t k = 0; k < j; ++k)
        {
          const LV p4_j(pt[j], eta[j], phi[j], mass[j]);
          const LV p4_k(pt[k], eta[k], phi[k], mass[k]);
          if((p4_j + p4_k).mass() < 12.0)
          {
            proceed = false;
            break;
          }
        }
      if(! proceed) break;
    }
    if(! proceed) continue;

    increment_all(cuts::minDilepMass);

//-------------------------------------------------------- LEPTON PT > 20, 10
    if(! (pt[selected_leptons[0]] > 20 &&            // leading lepton
          pt[selected_leptons[1]] > 10  )) continue; // subleading lepton
    increment_all(cuts::pT2010);

//------------------------------------------------ 2+ HADRONIC JETS (>25 GeV)
    std::vector<Int_t> hadronic_jets;
    for(Int_t j = 0; j < njets; ++j)
      if(jet_pt[j] > 25) hadronic_jets.push_back(j);
    if(hadronic_jets.size() < 2) continue;

    increment_all(cuts::j2_plus);

//---------------------------------------- 2+ LOOSE B JETS / 1+ MEDIUM B JETS
    std::map<std::string, std::vector<Int_t>> bjets =
      {
        {"loose",  {} },
        {"medium", {} }
      };
    for(Int_t j = 0; j < njets; ++j)
      if(std::fabs(jet_eta[j]) < 2.4)
      {
        if(jet_csv[j] > loose_csv_wp)  bjets["loose"].push_back(j);
        if(jet_csv[j] > medium_csv_wp) bjets["medium"].push_back(j);
      }
    if(bjets["loose"].size() < 2 && bjets["medium"].size() < 1) continue;

    increment_all(cuts::bjet_2l_1m);

//-------------------------------------------------------------- MEDIUM MU ID
//--- applies to all muons?
    for(Int_t j: selected_leptons)
    {
      if(std::abs(pdg_id[j]) == 13 &&
         med_mu_id[j] < 1           )
      {
        proceed = false;
        break;
      }
    }
    if(! proceed) continue;

    for(ch channel: {ch::emu, ch::mumu, ch::_3l, ch::_4l})
      ++counter[channel][cuts::medium_mu_id];

//--- tight lepton cuts
    if(nof_selected_leptons < 4)
    {
//-------------------------------------------------- ELECTRON CONVERSION VETO
//--- applies to tight electrons only
      for(Int_t j: selected_leptons)
      {
        if(std::abs(pdg_id[j]) == 11 &&
           pass_conv_veto[j] < 1      )
        {
          proceed = false;
          break;
        }
      }
      if(! proceed) continue;

      for(ch channel: {ch::ee, ch::emu, ch::_3l})
        ++counter[channel][cuts::conv_veto];

//--------------------------------------------------------------- 0 LOST HITS
//--- applies to tight electrons only
      for(Int_t j: selected_leptons)
      {
        if(std::abs(pdg_id[j]) == 11 &&
           lost_hits[j] != 0          )
        {
          proceed = false;
          break;
        }
      }

      if(! proceed) continue;

      for(ch channel: {ch::ee, ch::emu, ch::_3l})
        ++counter[channel][cuts::lost_hits_0];

//--------------------------------------------------- ELECTRON IDENTIFICATION
//--- applies to tight electrons only

      for(Int_t j: selected_leptons)
      {
        if(std::abs(pdg_id[j]) == 11 &&
           ele_mva_id[j] < 2          )
        {
          proceed = false;
          break;
        }
      }
      if(! proceed) continue;

      for(ch channel: {ch::ee, ch::emu, ch::_3l})
        ++counter[channel][cuts::ele_id];

//-------------------------------------------------- RELATIVE ISOLATION < 0.1
//--- applies to tight leptons only

      for(Int_t j: selected_leptons)
      {
        if(rel_iso[j] >= 0.1)
        {
          proceed = false;
          break;
        }
      }
      if(! proceed) continue;

      for(ch channel: {ch::ee, ch::mumu, ch::emu, ch::_3l})
        ++counter[channel][cuts::rel_iso_01];

//--------------------------------------------------------------- SIP3D < 4.0
//--- applies to tight leptons only

      for(Int_t j: selected_leptons)
      {
        if(sip3d[j] >= 4.0)
        {
          proceed = false;
          break;
        }
      }
      if(! proceed) continue;

      for(ch channel: {ch::ee, ch::mumu, ch::emu, ch::_3l})
        ++counter[channel][cuts::sip3d_4];
    }

//=========================== DILEPTON CHANNEL ==============================
    if(nof_selected_leptons == 2)
    {
      const Int_t lept_0 = selected_leptons[0];
      const Int_t lept_1 = selected_leptons[1];

      ch channel = ch::unspecified;
      if(std::abs(pdg_id[lept_0]) == 11 && std::abs(pdg_id[lept_1]) == 11)
        channel = ch::ee;
      else
      if(std::abs(pdg_id[lept_0]) == 13 && std::abs(pdg_id[lept_1]) == 13)
        channel = ch::mumu;
      else
        channel = ch::emu;

      ++counter[channel][cuts::tight_mva];

//----------------------------------------------------------------- SAME SIGN
      if(pdg_id[lept_0] * pdg_id[lept_1] < 0) continue;

      ++counter[channel][cuts::ss];

//---------------------------------------------------------- 4+ HADRONIC JETS
      if(hadronic_jets.size() < 4) continue;

      ++counter[channel][cuts::j4_plus];

//-------------------------------------------------------------- MET_LD > 0.2
//--- merge all jets
      std::vector<Int_t> all_bjets,
                         selected_jets;
      std::set_union
        (
          bjets["loose"].begin(), bjets["loose"].end(),
          bjets["medium"].begin(), bjets["medium"].end(),
          std::back_inserter(all_bjets)
        );
      std::set_union
        (
          all_bjets.begin(), all_bjets.end(),
          hadronic_jets.begin(), hadronic_jets.end(),
          std::back_inserter(selected_jets)
        );

//--- calculate MHT
      LV mht_vec(0, 0, 0, 0);
      for(Int_t j: hadronic_jets)
        mht_vec += LV(jet_pt[j], jet_eta[j], jet_phi[j], jet_mass[j]);

      const LV p4_0(pt[lept_0], eta[lept_0], phi[lept_0], mass[lept_0]);
      const LV p4_1(pt[lept_1], eta[lept_1], phi[lept_1], mass[lept_1]);
      mht_vec += p4_0 + p4_1;

      const Double_t mht_pt = mht_vec.pt();

      const Double_t met_ld = met_coef * met_pt + mht_coef * mht_pt;
      if(met_ld <= 0.2) continue;

      ++counter[channel][cuts::met_ld_02];

//-------------------------------------------------------- LEPTON PT > 20, 20
      if(pt[lept_0] <= 20 || pt[lept_1] <= 20) continue;

      ++counter[channel][cuts::pT2020];

//----------------------------------------- SCALAR SUM(L0, L1, MET) > 100 GeV
      if(pt[lept_0] + pt[lept_1] + met_pt <= 100) continue;

      ++counter[channel][cuts::ht_l1l2_met_100];

//-------------------------------------------------------------------- Z VETO
      if(std::fabs((p4_0 + p4_1).mass() - z_mass) <= z_th) continue;

      ++counter[channel][cuts::zveto];

//-------------------------------------------------------------- TIGHT CHARGE
      if(tight_charge[lept_0] < 2 || tight_charge[lept_1] < 2) continue;

      ++counter[channel][cuts::charge_quality];

//---------------------------------------------------------------------- PLOT
      {

        Double_t min_dR_l2j = 1000;
        Double_t ht = pt[lept_0] + pt[lept_1];
        LV ht_vec = p4_0 + p4_1;
        for(Int_t h: hadronic_jets)
        {
          const Double_t dR_tmp =
            std::sqrt(std::pow(eta[lept_1] - jet_eta[h], 2) +
                      std::pow(phi[lept_1] - jet_phi[h], 2));
          const LV hjet(jet_pt[h], jet_eta[h], jet_phi[h], jet_mass[h]);
          if(dR_tmp < min_dR_l2j) min_dR_l2j = dR_tmp;
          ht += jet_pt[h];
          ht_vec += hjet;
        }
        const Double_t pt_trailing = pt[lept_1];
        const Double_t eta_trailing = std::fabs(eta[lept_1]);
        const Double_t mt_metl1 =
            (p4_0 + LV(met_pt, met_eta, met_phi, met_mass)).mass();
        const Double_t mht = std::fabs(ht_vec.pt());
        hm[channel][cp::final].fill(pt_trailing, eta_trailing, min_dR_l2j,
                                    mt_metl1, ht, mht);
      }

    }

//=========================== TRILEPTON CHANNEL =============================
    else if(nof_selected_leptons == 3)
    {
      ++counter[ch::_3l][cuts::tight_mva];

//------------------------------------------ 4+ HADRONIC JETS or MET_LD > 0.2
      if(hadronic_jets.size() < 4)
      {
//--- merge all jets
        std::vector<Int_t> all_bjets,
                           selected_jets;
        std::set_union
          (
            bjets["loose"].begin(), bjets["loose"].end(),
            bjets["medium"].begin(), bjets["medium"].end(),
            std::back_inserter(all_bjets)
          );
        std::set_union
          (
            all_bjets.begin(), all_bjets.end(),
            hadronic_jets.begin(), hadronic_jets.end(),
            std::back_inserter(selected_jets)
          );

//--- calculate MHT
        LV mht_vec(0, 0, 0, 0);
        for(Int_t j: hadronic_jets)
          mht_vec += LV(jet_pt[j], jet_eta[j], jet_phi[j], jet_mass[j]);
        for(Int_t j: selected_leptons)
          mht_vec += LV(pt[j], eta[j], phi[j], mass[j]);
        const Double_t mht_pt = mht_vec.pt();

        const Double_t met_ld = met_coef * met_pt + mht_coef * mht_pt;
        if(met_ld <= 0.2) continue;
      }
      ++counter[ch::_3l][cuts::j4_plus_met_ld_02];

//---------------------------------------------------------------- SFOS ZVETO
      for(std::size_t j = 0; j < 3; ++j)
      {
        for(std::size_t k = 0; k < j; ++k)
        {
          if(pdg_id[j] == -pdg_id[k])
          {
            const Int_t lept_j = selected_leptons[j];
            const Int_t lept_k = selected_leptons[k];
            const LV p4_j(pt[lept_j], eta[lept_j], phi[lept_j], mass[lept_j]);
            const LV p4_k(pt[lept_k], eta[lept_k], phi[lept_k], mass[lept_k]);
            if(std::fabs((p4_j + p4_k).mass() - z_mass) <= z_th)
            {
              proceed = false;
              break;
            }
          }
          if(! proceed) break;
        }
        if(! proceed) break;
      }
      if(! proceed) continue;

      ++counter[ch::_3l][cuts::sfos_zveto];
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
          [&pdg_id](Int_t j, Int_t k) -> Int_t
          {
            const Int_t charge = pdg_id[k] > 0 ? 1 : -1;
            return j + charge;
          }
        );
      if(charge_sum != 0) continue;

      ++counter[ch::_4l][cuts::neutral_sum];

//---------------------------------------------------------------- SFOS ZVETO
      for(std::size_t j = 0; j < 4; ++j)
      {
        for(std::size_t k = 0; k < j; ++k)
        {
          if(pdg_id[j] == -pdg_id[k])
          {
            const Int_t lept_j = selected_leptons[j];
            const Int_t lept_k = selected_leptons[k];
            const LV p4_j(pt[lept_j], eta[lept_j], phi[lept_j], mass[lept_j]);
            const LV p4_k(pt[lept_k], eta[lept_k], phi[lept_k], mass[lept_k]);
            if(std::fabs((p4_j + p4_k).mass() - z_mass) <= z_th)
            {
              proceed = false;
              break;
            }
          }
          if(! proceed) break;
        }
        if(! proceed) break;
      }
      if(! proceed) continue;

      ++counter[ch::_4l][cuts::sfos_zveto];
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

  log_file.close();
  clock.Show("SynchTTH");

  return EXIT_SUCCESS;
}
