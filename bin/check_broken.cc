#include <iostream> // std::cerr, std::cout
#include <string> // std::string
#include <cstdlib> // EXIT_SUCCESS, EXIT_FAILURE, setenv()
#include <vector> // std::vector<>
#include <map> // std::map<,>
#include <exception> // std::exception
#include <stdexcept> // std::runtime_error
#include <chrono> // std::chrono::
#include <iomanip> // std::setprecision()
#include <fstream> // std::ofstream
#include <algorithm> // std::set_difference(), std::accumulate(), std::any_of()
#include <set> // std::set<>
#include <iterator> // std::inserter()

#include <boost/filesystem.hpp> // boost::filesystem::
#include <boost/program_options.hpp> // boost::program_options::
#include <boost/regex.hpp> // boost::regex::
#include <boost/lexical_cast.hpp> // boost::lexical_cast<>()
#include <boost/iterator/counting_iterator.hpp> // boost::counting_iterator<>
#include <boost/algorithm/string/join.hpp> // boost::algorithm::join()
#include <boost/xpressive/xpressive.hpp> // boost::xpressive::

#include <TFile.h> // TFile
#include <TH1F.h> // TH1F
#include <TROOT.h> // gROOT
#include <TError.h> // kError
#include <TString.h> // Form()

#define IMPROPER_FILE_C -1
#define ZOMBIE_FILE_C   -2

#define IMPROPER_FILE_P boost::filesystem::path("improper_files.txt")
#define ZOMBIE_FILE_P   boost::filesystem::path("broken_files.txt")
#define ZEROFS_FILE_P   boost::filesystem::path("zerofs_files.txt")
#define PYTHON_FILE_P   boost::filesystem::path("samples_2016.py")

#define LINE std::string(80, '*') + '\n'

/**
 * @file
 * Check broken root files in the file system
 *
 * You are encouraged to build it with scram, but if you are keen to not use it,
 * then proceed with the following command in order to build the executable:
 *
   g++ -std=c++11 \
     -I/cvmfs/cms.cern.ch/slc6_amd64_gcc493/external/boost/1.57.0-kpegke/include \
     -I/cvmfs/cms.cern.ch/slc6_amd64_gcc493/lcg/root/6.02.12-kpegke4/include \
     check_broken.cc -o check_broken \
     -L/cvmfs/cms.cern.ch/slc6_amd64_gcc493/external/boost/1.57.0-kpegke/lib \
     -L/cvmfs/cms.cern.ch/slc6_amd64_gcc493/cms/cmssw/CMSSW_7_6_3/external/slc6_amd64_gcc493/lib \
     -L/cvmfs/cms.cern.ch/slc6_amd64_gcc493/lcg/root/6.02.12-kpegke4/lib \
     -lboost_system -lboost_filesystem -lboost_program_options -lboost_regex \
     -llzma -lCore -lRIO -lThread \
     -Wl,-rpath=/cvmfs/cms.cern.ch/slc6_amd64_gcc493/external/boost/1.57.0-kpegke/lib \
     -Wl,-rpath=/cvmfs/cms.cern.ch/slc6_amd64_gcc493/cms/cmssw/CMSSW_7_6_3/external/slc6_amd64_gcc493/lib \
     -Wl,-rpath=/cvmfs/cms.cern.ch/slc6_amd64_gcc493/lcg/root/6.02.12-kpegke4/lib

 * Example output:

  check_broken -h
  Allowed options:
    -h [ --help ]               produce help message
    -p [ --path ] arg           full path to the directory to scan
    -t [ --tree ] arg (=tree)   expected TTree name
    -o [ --output ] [=arg(=./)] dump the results to given directory
    -z [ --zerofs ]             save the list of files with zero file size to a
                                file
    -i [ --improper ]           save the list of files that don't contain correct
                                TTree
    -P [ --python ]             generate rudimentary python configuration file
    -v [ --verbose ]            log every file and folder

 * Example usage:

   check_broken -p /hdfs/local/lucia/VHBBHeppyV24bis/ --histo Count --output=/home/lucia/sandbox -P -z -v
 */



namespace std
{
  using vstring = std::vector<std::string>;
  using vunsigned = std::vector<unsigned>;

  template<typename T>
  std::set<T>
  operator-(const std::set<T> & lhs,
            const std::set<T> & rhs)
  {
    std::set<T> s;
    std::set_difference(
      lhs.begin(), lhs.end(), rhs.begin(), rhs.end(),
      std::inserter(s, s.end())
    );
    return s;
  }
}

/**
 * @brief Helper struct needed to iterate over the directory tree recursively
 */
struct recursive_directory_range
{
  /**
   * @brief Simple constructor
   * @param p Path, the starting point of the file system scan
   */
  recursive_directory_range(boost::filesystem::path p)
    : p_(p)
  {}

  /**
   * @brief begin iterator (needed by for-range loops)
   * @return iterator to the starting point
   */
  boost::filesystem::recursive_directory_iterator
  begin()
  {
    return boost::filesystem::recursive_directory_iterator(p_);
  }

  /**
   * @brief end iterator (needed by for-range loops)
   * @return an empty iterator
   */
  boost::filesystem::recursive_directory_iterator
  end()
  {
    return boost::filesystem::recursive_directory_iterator();
  }

  boost::filesystem::path p_;
};

/**
 * @brief Checks whether a given root file is broken or not
 * @param path Full path to an actual root file
 * @param tree TTree name
 * @return IMPROPER_FILE_C if the file doesn't have TTree called 'tree',
 *         ZOMBIE_FILE_C   if the file is broken,
 *         otherwise the number of events in that file
 */
long int
check_broken(const std::string & path,
             const std::string & histo)
{
  TFile f(path.c_str());
  long int ret_val = ZOMBIE_FILE_C;
  if(! f.IsZombie())
  {
    if(f.GetListOfKeys() -> Contains(histo.c_str()))
    {
      TH1 * h = dynamic_cast<TH1 *>(f.Get("Count"));
      ret_val = h -> GetEntries();
    }
    else
      return IMPROPER_FILE_C;
  }
  f.Close();
  return ret_val;
}

unsigned
get_nr_str(const std::string & str)
{
//--- set up the regex
  static const boost::regex re("\\d+");
  boost::sregex_iterator it(str.begin(), str.end(), re);
  decltype(it) end;
  std::vstring matches;
  for(; it != end; ++it)
    matches.push_back(it -> str());
  if(matches.size() != 1)
    throw std::runtime_error("Something's wrong");
  return boost::lexical_cast<unsigned>(matches[0]);
}


struct Sample
{
  enum class Info
  {
    kPresent   = 0,
    kZombie    = 1,
    kZerofs    = 2,
    kImproper  = 3
  };

  Sample() = default;
  Sample(boost::filesystem::path path)
    : path(path)
    , name(path.filename().string())
    , pathStr(path.string())
    , x_sec(0)
    , max_nr(0)
    , nof_events(0)
  {}
  Sample(boost::filesystem::path path,
         boost::filesystem::path parent)
    : path(path)
    , parent(parent)
    , name(path.filename().string())
    , pathStr(path.string())
    , parentStr(parent.string())
    , x_sec(0)
    , max_nr(0)
    , nof_events(0)
  {}

  /**
   * @brief Checks whether there are any missing files
   *
   * Essentially does some cross-checks with the tree numbers;
   * for example, if a given sample has files: tree_1.root, tree_2.root, ..., tree_N.root
   * we expect no missing tree files between numbers 1 and N
   * From what follows, we check for ,,missing'' root files that proves to be useful
   * in blacklisting missing entries in the python configuration file
   */
  void
  check_completion()
  {
    auto present_set        = get_set(present);
    const auto zombie_set   = get_set(zombies);
    const auto zerofs_set   = get_set(zerofs);
    const auto improper_set = get_set(improper);

    if(present_set.size())
    {
//--- subtract faulty files from present_set
      for(const auto & s: { zombie_set, zerofs_set, improper_set })
	      present_set = present_set - s;

      max_nr = *present_set.rbegin();
      std::set<unsigned> blacklist_set;
      std::set_difference(
        boost::counting_iterator<unsigned>(1),
        boost::counting_iterator<unsigned>(max_nr),
        present_set.begin(), present_set.end(),
        std::inserter(blacklist_set, blacklist_set.end())
      );
      const std::vunsigned blacklist_u(blacklist_set.begin(), blacklist_set.end());
      std::transform(blacklist_u.begin(), blacklist_u.end(), std::back_inserter(blacklist),
                     [](unsigned x) -> std::string { return std::to_string(x); });
    }

  }

  /**
   * @brief Converts full path strings 'a/b/c/tree_N.root' into number set { N }
   * @param v String vector of full paths
   * @return Number set
   */
  std::set<unsigned>
  get_set(const std::vstring & v)
  {
    std::vunsigned v_unsigned;
    std::transform(
      v.begin(), v.end(), std::back_inserter(v_unsigned),
      [](const std::string & str) -> unsigned
      {
        return get_nr_str(boost::filesystem::path(str).filename().string());
      }
    );
    return std::set<unsigned>(v_unsigned.begin(), v_unsigned.end());
  }

  /**
   * @brief Creates an OrderedDict (OD) entry in Python configuration file
   * @return The entry as a string
   */

  std::string
  get_cfg() const 
  {
    const std::map<std::string, std::string> env = {
      { "sample_name",     name                                    },
      { "sample_dbs_name", dbs_name                                },
      { "category",        category                                }, 
      { "process_name",    process_name                            }, 
      { "x_sec",           std::to_string(x_sec)                   },
      { "max_nr",          std::to_string(max_nr)                  },
      { "nof_events",      std::to_string(nof_events)              },
      { "nof_dbs_events",  std::to_string(nof_dbs_events)          },
      { "super_parent",    fileSuperParent                         },
      { "blacklist",       boost::algorithm::join(blacklist, ", ") }
    };
    auto fmt_fun = [&env](const boost::xpressive::smatch & what) -> const std::string &
    {
      return env.at(what[1].str());
    };
    const std::string input =
      "samples[\"$(sample_dbs_name)\"] = OD([\n"
      "  (\"type\",                  \"mc\"),\n"
      "  (\"sample_category\",       \"$(category)\"),\n"       //LUCIA
      "  (\"process_name_specific\", \"$(process_name)\"),\n"   //LUCIA
      "  (\"nof_files\",             $(max_nr)),\n"
      "  (\"nof_events\",            $(nof_events)),\n"
      "  (\"nof_dbs_events\",        $(nof_dbs_events)),\n"
      "  (\"use_it\",                True),\n"
      "  (\"xsection\",              $(x_sec)),\n"
      "  (\"triggers\",              [ \"1e\", \"2e\", \"1mu\", \"2mu\", \"1e1mu\" ]),\n"
      "  (\"reHLT\",                 False),\n"
      "  (\"local_paths\",\n"
      "    [\n"
      "      OD([\n"
      "        (\"path\",      \"$(super_parent)\"),\n"
      "        (\"selection\", \"*\"),\n"
      "        (\"blacklist\", [$(blacklist)]),\n"
      "      ]),\n"
      "    ]\n"
      "  ),\n"
      "])\n"
    ;
    const boost::xpressive::sregex envar =
      "$(" >> (boost::xpressive::s1 = +boost::xpressive::_w) >> ')';
    const std::string output = boost::xpressive::regex_replace(input, envar, fmt_fun);
    return output;
  }

  boost::filesystem::path path;
  boost::filesystem::path parent;

  std::string name;
  std::string dbs_name;
  std::string pathStr;
  std::string parentStr;
  std::string fileSuperParent; ///< NB!! Its only a string not a vector
  std::string category;
  std::string process_name;

  std::vstring zombies, zerofs, improper, present, blacklist;

  double    x_sec;
  unsigned max_nr;
  unsigned long long nof_events;
  unsigned long long nof_dbs_events;
};

std::vstring
operator|(const std::vector<Sample> & samples,
          Sample::Info key)
{
  std::vstring result;
  for(const Sample & sample: samples)
    if     (key == Sample::Info::kPresent)
      result.insert(result.end(), sample.present.begin(),   sample.present.end());
    else if(key == Sample::Info::kZombie)
      result.insert(result.end(), sample.zombies.begin(),   sample.zombies.end());
    else if(key == Sample::Info::kZerofs)
      result.insert(result.end(), sample.zerofs.begin(),    sample.zerofs.end());
    else if(key == Sample::Info::kImproper)
      result.insert(result.end(), sample.improper.begin(),  sample.improper.end());
  return result;
}

int
main(int argc,
     char * argv[])
{
  setenv("TZ", "/etc/localtime", 1); // needed by std::chrono::
  gROOT -> ProcessLine(Form("gErrorIgnoreLevel = %d;", kBreak));

//map definitions
std::map<std::string, std::string> sample_name; // key = sample
sample_name["ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix"]="/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14_ext1-v1/MINIAODSIM";
sample_name["ttHToNonbb_M125_13TeV_powheg_pythia8"]="/ttHToNonbb_M125_13TeV_powheg_pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM";
sample_name["THW_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1"]="/THW_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM";
sample_name["GluGluHToZZTo4L_M125_13TeV_powheg2_JHUgenV6_pythia8"]="/GluGluHToZZTo4L_M125_13TeV_powheg2_JHUgenV6_pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM";
sample_name["DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"]="/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14_ext1-v1/MINIAODSIM";
sample_name["DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8"]="/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM";
sample_name["WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8"]="/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM";
sample_name["WWTo2L2Nu_13TeV-powheg"]="/WWTo2L2Nu_13TeV-powheg/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM";
sample_name["ZZTo4L_13TeV-amcatnloFXFX-pythia8"]="/ZZTo4L_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM";
sample_name["ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1"]="/ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM";
sample_name["ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1"]="/ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM";
sample_name["ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1"]="/ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM";
sample_name["ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1"]="/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM";
sample_name["ST_tW_top_5f_NoFullyHadronicDecays_13TeV-powheg_TuneCUETP8M1"]="/ST_tW_top_5f_NoFullyHadronicDecays_13TeV-powheg_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM";
sample_name["VHBB_HEPPY_V24bis_TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v4"]="/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v4/MINIAODSIM";
sample_name["VHBB_HEPPY_V24bis_TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0_ext1-v1"]="/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM";
sample_name["VHBB_HEPPY_V24bis_TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1"]="/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM";
sample_name["VHBB_HEPPY_V24bis_TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0_ext1-v1"]="/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM";
sample_name["VHBB_HEPPY_V24bis_TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1"]="/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM";
sample_name["VHBB_HEPPY_V24bis_TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0_ext1-v1"]="/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM";
sample_name["TT_TuneCUETP8M1_13TeV-powheg-pythia8"]="/TT_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISpring16MiniAODv1-PUSpring16_80X_mcRun2_asymptotic_2016_v3_ext3-v1/MINIAODSIM";
sample_name["TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8"]="/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM";
sample_name["VHBB_HEPPY_V24bis_TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1"]="/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM";
sample_name["VHBB_HEPPY_V24bis_TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-Py8__spr16MAv2-premix_withHLT_80r2as_v14_ext1-v1"]="/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISpring16MiniAODv2-premix_withHLT_80X_mcRun2_asymptotic_v14_ext1-v1/MINIAODSIM";
sample_name["WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8"]="/WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM";
sample_name["WGToLNuG_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"]="/WGToLNuG_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM";
sample_name["VHBB_HEPPY_V24bis_ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1"]="/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM";
sample_name["VHBB_HEPPY_V24bis_ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0_ext1-v1"]="/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM";
sample_name["TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8"]="/TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM";
sample_name["TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8"]="/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM";
sample_name["WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8"]="/WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v2/MINIAODSIM";
sample_name["WW_DoubleScattering_13TeV-pythia8"]="/WW_DoubleScattering_13TeV-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM";
sample_name["tZq_ll_4f_13TeV-amcatnlo-pythia8_TuneCUETP8M1"]="/tZq_ll_4f_13TeV-amcatnlo-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM";
sample_name["TTTT_TuneCUETP8M1_13TeV-amcatnlo-pythia8"]="/TTTT_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM";
sample_name["VHBB_HEPPY_V24_MuonEG__Run2016B-PromptReco-v2"]="/MuonEG/Run2016B-PromptReco-v2/MINIAOD";
sample_name["VHBB_HEPPY_V24_MuonEG__Run2016C-PromptReco-v2"]="/MuonEG/Run2016C-PromptReco-v2/MINIAOD";
sample_name["VHBB_HEPPY_V24_MuonEG__Run2016D-PromptReco-v2"]="/MuonEG/Run2016D-PromptReco-v2/MINIAOD";
sample_name["VHBB_HEPPY_V24_MuonEG__Run2016E-PromptReco-v2"]="/MuonEG/Run2016E-PromptReco-v2/MINIAOD";
sample_name["VHBB_HEPPY_V24_MuonEG__Run2016F-PromptReco-v1"]="/MuonEG/Run2016F-PromptReco-v1/MINIAOD";
sample_name["VHBB_HEPPY_V24_MuonEG__Run2016G-PromptReco-v1"]="/MuonEG/Run2016G-PromptReco-v1/MINIAOD";
sample_name["VHBB_HEPPY_V24_SingleElectron__Run2016B-PromptReco-v2"]="/SingleElectron/Run2016B-PromptReco-v2/MINIAOD";
sample_name["VHBB_HEPPY_V24_SingleElectron__Run2016C-PromptReco-v2"]="/SingleElectron/Run2016C-PromptReco-v2/MINIAOD";
sample_name["VHBB_HEPPY_V24_SingleElectron__Run2016D-PromptReco-v2"]="/SingleElectron/Run2016D-PromptReco-v2/MINIAOD";
sample_name["VHBB_HEPPY_V24_SingleElectron__Run2016E-PromptReco-v2"]="/SingleElectron/Run2016E-PromptReco-v2/MINIAOD";
sample_name["VHBB_HEPPY_V24_SingleElectron__Run2016F-PromptReco-v1"]="/SingleElectron/Run2016F-PromptReco-v1/MINIAOD";
sample_name["VHBB_HEPPY_V24_SingleElectron__Run2016G-PromptReco-v1"]="/SingleElectron/Run2016G-PromptReco-v1/MINIAOD";
sample_name["VHBB_HEPPY_V24_SingleMuon__Run2016B-PromptReco-v2"]="/SingleMuon/Run2016B-PromptReco-v2/MINIAOD";
sample_name["VHBB_HEPPY_V24_SingleMuon__Run2016C-PromptReco-v2"]="/SingleMuon/Run2016C-PromptReco-v2/MINIAOD";
sample_name["VHBB_HEPPY_V24_SingleMuon__Run2016D-PromptReco-v2"]="/SingleMuon/Run2016D-PromptReco-v2/MINIAOD";
sample_name["VHBB_HEPPY_V24_SingleMuon__Run2016E-PromptReco-v2"]="/SingleMuon/Run2016E-PromptReco-v2/MINIAOD";
sample_name["VHBB_HEPPY_V24_SingleMuon__Run2016F-PromptReco-v1"]="/SingleMuon/Run2016F-PromptReco-v1/MINIAOD";
sample_name["VHBB_HEPPY_V24_SingleMuon__Run2016G-PromptReco-v1"]="/SingleMuon/Run2016G-PromptReco-v1/MINIAOD";
sample_name["VHBB_HEPPY_V24_Tau__Run2016B-PromptReco-v2"]="/Tau/Run2016B-PromptReco-v2/MINIAOD";
sample_name["VHBB_HEPPY_V24_Tau__Run2016D-PromptReco-v2"]="/Tau/Run2016D-PromptReco-v2/MINIAOD";

std::map<std::string, std::string> sample_category; // key = sample
sample_category["/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14_ext1-v1/MINIAODSIM"]="signal";
sample_category["/ttHToNonbb_M125_13TeV_powheg_pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"]="signal";
sample_category["/THW_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"]="additional_signal_overlap";
sample_category["/GluGluHToZZTo4L_M125_13TeV_powheg2_JHUgenV6_pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"]="additional_signal_overlap";
sample_category["/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14_ext1-v1/MINIAODSIM"]="EWK";
sample_category["/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]="EWK";
sample_category["/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]="EWK";
sample_category["/WWTo2L2Nu_13TeV-powheg/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]="EWK";
sample_category["/ZZTo4L_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"]="EWK";
sample_category["/ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]="TT";
sample_category["/ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]="TT";
sample_category["/ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]="TT";
sample_category["/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]="TT";
sample_category["/ST_tW_top_5f_NoFullyHadronicDecays_13TeV-powheg_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]="TT";
sample_category["/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v4/MINIAODSIM"]="TT";
sample_category["/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM"]="TT";
sample_category["/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]="TT";
sample_category["/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM"]="TT";
sample_category["/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]="TT";
sample_category["/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM"]="TT";
sample_category["/TT_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISpring16MiniAODv1-PUSpring16_80X_mcRun2_asymptotic_2016_v3_ext3-v1/MINIAODSIM"]="TT";
sample_category["/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]="TTW";
sample_category["/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]="TTZ";
sample_category["/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISpring16MiniAODv2-premix_withHLT_80X_mcRun2_asymptotic_v14_ext1-v1/MINIAODSIM"]="TTZ";
sample_category["/WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]="Rares";
sample_category["/WGToLNuG_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]="Rares";
sample_category["/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]="Rares";
sample_category["/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM"]="Rares";
sample_category["/TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM"]="Rares";
sample_category["/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]="Rares";
sample_category["/WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v2/MINIAODSIM"]="Rares";
sample_category["/WW_DoubleScattering_13TeV-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]="Rares";
sample_category["/tZq_ll_4f_13TeV-amcatnlo-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]="Rares";
sample_category["/TTTT_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM"]="Rares";
sample_category["/MuonEG/Run2016B-PromptReco-v2/MINIAOD"]="data_obs";
sample_category["/MuonEG/Run2016C-PromptReco-v2/MINIAOD"]="data_obs";
sample_category["/MuonEG/Run2016D-PromptReco-v2/MINIAOD"]="data_obs";
sample_category["/MuonEG/Run2016E-PromptReco-v2/MINIAOD"]="data_obs";
sample_category["/MuonEG/Run2016F-PromptReco-v1/MINIAOD"]="data_obs";
sample_category["/MuonEG/Run2016G-PromptReco-v1/MINIAOD"]="data_obs";
sample_category["/SingleElectron/Run2016B-PromptReco-v2/MINIAOD"]="data_obs";
sample_category["/SingleElectron/Run2016C-PromptReco-v2/MINIAOD"]="data_obs";
sample_category["/SingleElectron/Run2016D-PromptReco-v2/MINIAOD"]="data_obs";
sample_category["/SingleElectron/Run2016E-PromptReco-v2/MINIAOD"]="data_obs";
sample_category["/SingleElectron/Run2016F-PromptReco-v1/MINIAOD"]="data_obs";
sample_category["/SingleElectron/Run2016G-PromptReco-v1/MINIAOD"]="data_obs";
sample_category["/SingleMuon/Run2016B-PromptReco-v2/MINIAOD"]="data_obs";
sample_category["/SingleMuon/Run2016C-PromptReco-v2/MINIAOD"]="data_obs";
sample_category["/SingleMuon/Run2016D-PromptReco-v2/MINIAOD"]="data_obs";
sample_category["/SingleMuon/Run2016E-PromptReco-v2/MINIAOD"]="data_obs";
sample_category["/SingleMuon/Run2016F-PromptReco-v1/MINIAOD"]="data_obs";
sample_category["/SingleMuon/Run2016G-PromptReco-v1/MINIAOD"]="data_obs";
sample_category["/Tau/Run2016B-PromptReco-v2/MINIAOD"]="data_obs";
sample_category["/Tau/Run2016D-PromptReco-v2/MINIAOD"]="data_obs";

std::map<std::string, std::string> process_name; // key = sample
process_name["/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14_ext1-v1/MINIAODSIM"]="ttHJetToNonbb_M125";
process_name["/ttHToNonbb_M125_13TeV_powheg_pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"]="ttHToNonbb_M125";
process_name["/THW_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"]="THW_Hincl";
process_name["/GluGluHToZZTo4L_M125_13TeV_powheg2_JHUgenV6_pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"]="GluGluHToZZTo4L";
process_name["/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14_ext1-v1/MINIAODSIM"]="DYJetsToLL_M-50";
process_name["/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]="DYJetsToLL_M-10to50";
process_name["/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]="WZTo3LNu";
process_name["/WWTo2L2Nu_13TeV-powheg/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]="WWTo2L2Nu";
process_name["/ZZTo4L_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"]="ZZTo4L";
process_name["/ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]="ST_s-channel_4f_leptonDecays";
process_name["/ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]="ST_t-channel_antitop_4f_inclusiveDecays";
process_name["/ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]="ST_t-channel_top_4f_inclusiveDecays";
process_name["/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]="ST_tW_antitop_5f_inclusiveDecays";
process_name["/ST_tW_top_5f_NoFullyHadronicDecays_13TeV-powheg_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]="ST_tW_top_5f_NoFullyHadronicDecays";
process_name["/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v4/MINIAODSIM"]="TTJets_DiLept";
process_name["/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM"]="TTJets_DiLept_ext1";
process_name["/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]="TTJets_SingleLeptFromT";
process_name["/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM"]="TTJets_SingleLeptFromT_ext1";
process_name["/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]="TTJets_SingleLeptFromTbar";
process_name["/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM"]="TTJets_SingleLeptFromTbar_ext1";
process_name["/TT_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISpring16MiniAODv1-PUSpring16_80X_mcRun2_asymptotic_2016_v3_ext3-v1/MINIAODSIM"]="TT_ext3";
process_name["/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]="TTWJetsToLNu";
process_name["/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]="TTZToLLNuNu_M-10";
process_name["/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISpring16MiniAODv2-premix_withHLT_80X_mcRun2_asymptotic_v14_ext1-v1/MINIAODSIM"]="TTZToLLNuNu_M-10_ext1";
process_name["/WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]="WZZ";
process_name["/WGToLNuG_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]="WGToLNuG";
process_name["/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]="ZGTo2LG";
process_name["/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM"]="ZGTo2LG_ext1";
process_name["/TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM"]="TGJets_ext1";
process_name["/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]="TTGJets";
process_name["/WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v2/MINIAODSIM"]="WpWpJJ_EWK-QCD";
process_name["/WW_DoubleScattering_13TeV-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]="WW_DoubleScattering";
process_name["/tZq_ll_4f_13TeV-amcatnlo-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]="tZq_ll_4f";
process_name["/TTTT_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM"]="TTTT";
process_name["/MuonEG/Run2016B-PromptReco-v2/MINIAOD"]="MuonEG_Run2016B_v2";
process_name["/MuonEG/Run2016C-PromptReco-v2/MINIAOD"]="MuonEG_Run2016C";
process_name["/MuonEG/Run2016D-PromptReco-v2/MINIAOD"]="MuonEG_Run2016D";
process_name["/MuonEG/Run2016E-PromptReco-v2/MINIAOD"]="MuonEG_Run2016E";
process_name["/MuonEG/Run2016F-PromptReco-v1/MINIAOD"]="MuonEG_Run2016F";
process_name["/MuonEG/Run2016G-PromptReco-v1/MINIAOD"]="MuonEG_Run2016G";
process_name["/SingleElectron/Run2016B-PromptReco-v2/MINIAOD"]="SingleElectron_Run2016B_v2";
process_name["/SingleElectron/Run2016C-PromptReco-v2/MINIAOD"]="SingleElectron_Run2016C";
process_name["/SingleElectron/Run2016D-PromptReco-v2/MINIAOD"]="SingleElectron_Run2016D";
process_name["/SingleElectron/Run2016E-PromptReco-v2/MINIAOD"]="SingleElectron_Run2016E";
process_name["/SingleElectron/Run2016F-PromptReco-v1/MINIAOD"]="SingleElectron_Run2016F";
process_name["/SingleElectron/Run2016G-PromptReco-v1/MINIAOD"]="SingleElectron_Run2016G";
process_name["/SingleMuon/Run2016B-PromptReco-v2/MINIAOD"]="SingleMuon_Run2016B_v2";
process_name["/SingleMuon/Run2016C-PromptReco-v2/MINIAOD"]="SingleMuon_Run2016C";
process_name["/SingleMuon/Run2016D-PromptReco-v2/MINIAOD"]="SingleMuon_Run2016D";
process_name["/SingleMuon/Run2016E-PromptReco-v2/MINIAOD"]="SingleMuon_Run2016E";
process_name["/SingleMuon/Run2016F-PromptReco-v1/MINIAOD"]="SingleMuon_Run2016F";
process_name["/SingleMuon/Run2016G-PromptReco-v1/MINIAOD"]="SingleMuon_Run2016G";
process_name["/Tau/Run2016B-PromptReco-v2/MINIAOD"]="Tau_Run2016B_v2";
process_name["/Tau/Run2016D-PromptReco-v2/MINIAOD"]="Tau_Run2016D";

std::map<std::string, double> xsection; // key = sample
xsection["/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14_ext1-v1/MINIAODSIM"]=0.2151;
xsection["/ttHToNonbb_M125_13TeV_powheg_pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"]=0.2151;
xsection["/THW_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"]=0.01561;
xsection["/GluGluHToZZTo4L_M125_13TeV_powheg2_JHUgenV6_pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"]=0.0119;
xsection["/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14_ext1-v1/MINIAODSIM"]=6025.2;
xsection["/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]=18610.;
xsection["/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]=4.102;
xsection["/WWTo2L2Nu_13TeV-powheg/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]=10.481;
xsection["/ZZTo4L_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"]=1.256;
xsection["/ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]=3.75;
xsection["/ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]=70.69;
xsection["/ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]=70.69;
xsection["/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]=35.6;
xsection["/ST_tW_top_5f_NoFullyHadronicDecays_13TeV-powheg_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]=35.6;
xsection["/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v4/MINIAODSIM"]=87.3;
xsection["/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM"]=87.3;
xsection["/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]=182.;
xsection["/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM"]=182.;
xsection["/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]=182.;
xsection["/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM"]=182.;
xsection["/TT_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISpring16MiniAODv1-PUSpring16_80X_mcRun2_asymptotic_2016_v3_ext3-v1/MINIAODSIM"]=831.76;
xsection["/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]=0.2043;
xsection["/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]=0.2529;
xsection["/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISpring16MiniAODv2-premix_withHLT_80X_mcRun2_asymptotic_v14_ext1-v1/MINIAODSIM"]=0.2529;
xsection["/WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]=0.05565;
xsection["/WGToLNuG_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]=585.8;
xsection["/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]=131.3;
xsection["/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM"]=131.3;
xsection["/TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM"]=2.967;
xsection["/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]=3.697;
xsection["/WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v2/MINIAODSIM"]=0.03711;
xsection["/WW_DoubleScattering_13TeV-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]=1.64;
xsection["/tZq_ll_4f_13TeV-amcatnlo-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]=0.0758;
xsection["/TTTT_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM"]=0.009103;
xsection["/MuonEG/Run2016B-PromptReco-v2/MINIAOD"]=1;
xsection["/MuonEG/Run2016C-PromptReco-v2/MINIAOD"]=1;
xsection["/MuonEG/Run2016D-PromptReco-v2/MINIAOD"]=1;
xsection["/MuonEG/Run2016E-PromptReco-v2/MINIAOD"]=1;
xsection["/MuonEG/Run2016F-PromptReco-v1/MINIAOD"]=1;
xsection["/MuonEG/Run2016G-PromptReco-v1/MINIAOD"]=1;
xsection["/SingleElectron/Run2016B-PromptReco-v2/MINIAOD"]=1;
xsection["/SingleElectron/Run2016C-PromptReco-v2/MINIAOD"]=1;
xsection["/SingleElectron/Run2016D-PromptReco-v2/MINIAOD"]=1;
xsection["/SingleElectron/Run2016E-PromptReco-v2/MINIAOD"]=1;
xsection["/SingleElectron/Run2016F-PromptReco-v1/MINIAOD"]=1;
xsection["/SingleElectron/Run2016G-PromptReco-v1/MINIAOD"]=1;
xsection["/SingleMuon/Run2016B-PromptReco-v2/MINIAOD"]=1;
xsection["/SingleMuon/Run2016C-PromptReco-v2/MINIAOD"]=1;
xsection["/SingleMuon/Run2016D-PromptReco-v2/MINIAOD"]=1;
xsection["/SingleMuon/Run2016E-PromptReco-v2/MINIAOD"]=1;
xsection["/SingleMuon/Run2016F-PromptReco-v1/MINIAOD"]=1;
xsection["/SingleMuon/Run2016G-PromptReco-v1/MINIAOD"]=1;
xsection["/Tau/Run2016B-PromptReco-v2/MINIAOD"]=1;
xsection["/Tau/Run2016D-PromptReco-v2/MINIAOD"]=1;

std::map<std::string, long int> dbsevents; // key = sample
dbsevents["/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14_ext1-v1/MINIAODSIM"]=9992683;
dbsevents["/ttHToNonbb_M125_13TeV_powheg_pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"]=3860872;
dbsevents["/THW_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"]=1499200;
dbsevents["/GluGluHToZZTo4L_M125_13TeV_powheg2_JHUgenV6_pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"]=969200;
dbsevents["/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14_ext1-v1/MINIAODSIM"]=91350867;
dbsevents["/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]=30915886;
dbsevents["/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]=2000000;
dbsevents["/WWTo2L2Nu_13TeV-powheg/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]=1996600;
dbsevents["/ZZTo4L_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"]=10348531;
dbsevents["/ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]=1000000;
dbsevents["/ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]=19825855;
dbsevents["/ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]=32808300;
dbsevents["/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]=985000;
dbsevents["/ST_tW_top_5f_NoFullyHadronicDecays_13TeV-powheg_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]=5405726;
dbsevents["/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v4/MINIAODSIM"]=6058236;
dbsevents["/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM"]=24623997;
dbsevents["/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]=9468936;
dbsevents["/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM"]=43588107;
dbsevents["/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]=11947951;
dbsevents["/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM"]=48546872;
dbsevents["/TT_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISpring16MiniAODv1-PUSpring16_80X_mcRun2_asymptotic_2016_v3_ext3-v1/MINIAODSIM"]=33364899;//not known;
dbsevents["/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]=252673;
dbsevents["/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]=398600;
dbsevents["/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISpring16MiniAODv2-premix_withHLT_80X_mcRun2_asymptotic_v14_ext1-v1/MINIAODSIM"]=1981476;
dbsevents["/WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]=249800;
dbsevents["/WGToLNuG_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]=5916785;
dbsevents["/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]=4391376;
dbsevents["/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM"]=14377546;
dbsevents["/TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM"]=1535543;
dbsevents["/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]=4874091;
dbsevents["/WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v2/MINIAODSIM"]=138235;
dbsevents["/WW_DoubleScattering_13TeV-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]=844954;
dbsevents["/tZq_ll_4f_13TeV-amcatnlo-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"]=2973639;
dbsevents["/TTTT_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM"]=989025;
dbsevents["/MuonEG/Run2016B-PromptReco-v2/MINIAOD"]=32648217;
dbsevents["/MuonEG/Run2016C-PromptReco-v2/MINIAOD"]=15416170;
dbsevents["/MuonEG/Run2016D-PromptReco-v2/MINIAOD"]=23482352;
dbsevents["/MuonEG/Run2016E-PromptReco-v2/MINIAOD"]=22519319;
dbsevents["/MuonEG/Run2016F-PromptReco-v1/MINIAOD"]=15932356;
dbsevents["/MuonEG/Run2016G-PromptReco-v1/MINIAOD"]=33854830;
dbsevents["/SingleElectron/Run2016B-PromptReco-v2/MINIAOD"]=246175191;
dbsevents["/SingleElectron/Run2016C-PromptReco-v2/MINIAOD"]=97292079;
dbsevents["/SingleElectron/Run2016D-PromptReco-v2/MINIAOD"]=148167727;
dbsevents["/SingleElectron/Run2016E-PromptReco-v2/MINIAOD"]=117321545;
dbsevents["/SingleElectron/Run2016F-PromptReco-v1/MINIAOD"]=70402684;
dbsevents["/SingleElectron/Run2016G-PromptReco-v1/MINIAOD"]=153364066;
dbsevents["/SingleMuon/Run2016B-PromptReco-v2/MINIAOD"]=158188719;
dbsevents["/SingleMuon/Run2016C-PromptReco-v2/MINIAOD"]=68492270;
dbsevents["/SingleMuon/Run2016D-PromptReco-v2/MINIAOD"]=98175265;
dbsevents["/SingleMuon/Run2016E-PromptReco-v2/MINIAOD"]=90986344;
dbsevents["/SingleMuon/Run2016F-PromptReco-v1/MINIAOD"]=65235075;
dbsevents["/SingleMuon/Run2016G-PromptReco-v1/MINIAOD"]=152881545;
dbsevents["/Tau/Run2016B-PromptReco-v2/MINIAOD"]=71901374;
dbsevents["/Tau/Run2016D-PromptReco-v2/MINIAOD"]=61113729;

//--- parse command line arguments
  std::string target_str, histo_str, output_dir_str;
  bool save_zerofs, save_improper, save_python, verbose;
  try
  {
    boost::program_options::options_description desc("Allowed options");
    desc.add_options()
      ("help,h",     "produce help message")
      ("path,p",     boost::program_options::value<std::string>(&target_str) -> required(),
                     "full path to the directory to scan")
      ("histo,h",     boost::program_options::value<std::string>(&histo_str) -> default_value("Count"),
                     "expected TH1F name")
      ("output,o",   boost::program_options::value<std::string>(&output_dir_str) -> default_value("")
                                                                                 -> implicit_value("./"),
                     "dump the results to given directory")
      ("zerofs,z",   boost::program_options::bool_switch(&save_zerofs) -> default_value(false),
                     "save the list of files with zero file size to a file")
      ("improper,i", boost::program_options::bool_switch(&save_improper) -> default_value(false),
                     "save the list of files that don't contain correct TTree")
      ("python,P",   boost::program_options::bool_switch(&save_python) -> default_value(false),
                     "generate rudimentary python configuration file")
      ("verbose,v",  boost::program_options::bool_switch(&verbose) -> default_value(false),
                     "log every file and folder")
    ;
    boost::program_options::variables_map vm;
    boost::program_options::store(
          boost::program_options::parse_command_line(argc, argv, desc), vm
    );
    if(vm.count("help"))
    {
      std::cout << desc << '\n';
      return EXIT_SUCCESS;
    }
    boost::program_options::notify(vm); // might throw
  }
  catch(boost::program_options::error & e)
  {
    std::cerr << "User error: " << e.what() << '\n';
    return EXIT_FAILURE;
  }
  catch(std::exception & e)
  {
    std::cerr << "Error: " << e.what() << '\n';
    return EXIT_FAILURE;
  }
  catch(...)
  {
    std::cerr << "Unknown error!\n";
    return EXIT_FAILURE;
  }
  if(! boost::filesystem::is_directory(target_str))
  {
    std::cerr << "No such directory: '" << target_str << "'\n";
    return EXIT_FAILURE;
  }

  const boost::filesystem::path output_dir_path =
    boost::filesystem::canonical(output_dir_str);
  if(! output_dir_path.empty() && ! boost::filesystem::is_directory(output_dir_path))
  {
    std::cerr << "No such directory: '" << output_dir_str << "'\n";
    return EXIT_FAILURE;
  }
  if((save_zerofs || save_improper || save_python) && output_dir_path.empty())
  {
    std::cerr << "Output directory not specified\n";
    return EXIT_FAILURE;
  }

//--- quick printout of the chosen options
  std::cout << "Command entered: "
            << boost::algorithm::join(std::vstring(argv, argv + argc), " ") << '\n';
  std::cout << "Directory to analyze: " << target_str << '\n'
            << "TH1F name: "            << histo_str << '\n'
            << "Verbose printout: "     << std::boolalpha << verbose << '\n';
  if(! output_dir_path.empty())
    std::cout << "Output directory: " << output_dir_path.string() << '\n';
  std::cout << LINE;

//--- start the clock
  const std::chrono::high_resolution_clock::time_point start_t =
    std::chrono::high_resolution_clock::now();

//--- create a list of immediate subdirectories of a given directory
  std::vector<Sample> samples;
  const boost::filesystem::path target_path(target_str);
  boost::filesystem::directory_iterator target_it(target_path);
  for(const boost::filesystem::path & p: target_it)
    if(boost::filesystem::is_directory(p))
    {
      if(verbose) std::cout << "Found sample directory: " << p.string() << '\n';
      std::vector<boost::filesystem::path> immediate_subsubdirs;
      boost::filesystem::directory_iterator sub_it(p);
      for(const boost::filesystem::path & sub_p: sub_it)
        if(boost::filesystem::is_directory(sub_p))
          immediate_subsubdirs.push_back(sub_p);
      if(immediate_subsubdirs.size() == 1)
        samples.push_back({p});
      else
        for(const boost::filesystem::path & sub_p: immediate_subsubdirs)
          samples.push_back({sub_p, p});
    }
  if(verbose) std::cout << LINE;

//--- loop over the list of immediate subdirectories recursively
  for(Sample & sample: samples)
  {

    //if(sample.name.find("ttHToNonbb")==std::string::npos) continue;
    if(verbose) std::cout << ">> Looping over: " << sample.pathStr << "\n";
    for(const boost::filesystem::directory_entry & it: recursive_directory_range(sample.path))
    {
      const boost::filesystem::path file = it.path();
      const std::string file_str = file.string();
//--- if we're dealing with a valid root file
      if(boost::filesystem::is_regular_file(file) &&
         boost::filesystem::extension(file) == ".root")
      {

        sample.dbs_name      = sample_name[sample.name];
        sample.category      = sample_category[sample.dbs_name];
        sample.process_name  = process_name[sample.dbs_name];
        sample.x_sec         = xsection[sample.dbs_name];
        sample.nof_dbs_events    = dbsevents[sample.dbs_name];

        //if(verbose) std::cout << "Sample name: " << sample.dbs_name << '\n';
        //if(verbose) std::cout << "Sample category: " << sample.category << '\n';
        //if(verbose) std::cout << "Process name: " << sample.process_name << '\n';
        //if(verbose) std::cout << "Checking: " << file_str << '\n';
//--- parse the tree number
        sample.present.push_back(file_str);
//--- read the file size before checking the zombiness
        const boost::uintmax_t file_size = boost::filesystem::file_size(file);
        if(! file_size)
        {
          sample.zerofs.push_back(file_str);
//--- don't even bother checking whether the file is zombie or not
          continue;
        }
        const long int nof_events = check_broken(file_str, histo_str); //tree_str);
        if     (nof_events > 0)                sample.nof_events += nof_events;
        else if(nof_events == ZOMBIE_FILE_C)   sample.zombies.push_back(file_str);
        else if(nof_events == IMPROPER_FILE_C) sample.improper.push_back(file_str);
//--- if the valid root file has path ../<grid job id>/000X/tree_i.root, then in order
//--- to build the Python configuration file is to gather the paths to <grid job id>
        if(sample.fileSuperParent.empty())
          sample.fileSuperParent = file.parent_path().parent_path().string();
      } // is root file
    } // recursive loop
  } // immediate subdirectory loop
  if(verbose) std::cout << LINE;

//--- post-process

  std::cout << "in the post process phase "<< std::endl;
  for(Sample & sample: samples)
    sample.check_completion();
  const auto present   = samples | Sample::Info::kPresent;
  const auto zombies   = samples | Sample::Info::kZombie;
  const auto zerofs    = samples | Sample::Info::kZerofs;
  const auto improper  = samples | Sample::Info::kImproper;

  std::cout << "print the results; save them to a file? "<< std::endl;
//--- print the results; save them to a file?
  if(zombies.size())
  {
    const std::string zombie_str = boost::algorithm::join(zombies, "\n");
    std::cout << "List of broken files:\n" << zombie_str << '\n';

    if(! output_dir_str.empty())
    {
      const std::string zombie_path = (output_dir_path / ZOMBIE_FILE_P).string();
      std::ofstream out(zombie_path);
      out << zombie_str << '\n';
      std::cout << "Wrote file '" << zombie_path << "'\n";
    }
    std::cout << LINE;
  }
  if(zerofs.size())
  {
    const std::string zerofs_str = boost::algorithm::join(zerofs, "\n");
    std::cout << "List of files with zero size:\n" << zerofs_str << '\n';

    if(! output_dir_str.empty() && save_zerofs)
    {
      const std::string zerofs_path = (output_dir_path / ZEROFS_FILE_P).string();
      std::ofstream out(zerofs_path);
      out << zerofs_str << '\n';
      std::cout << "Wrote file '" << zerofs_path << "'\n";
    }
    std::cout << LINE;
  }
  if(improper.size())
  {
    const std::string improper_str = boost::algorithm::join(improper, "\n");
    std::cout << "List of files which didn't have '" << histo_str << "' "
              << "as immediate key in the root file:\n" << improper_str << '\n';

    if(! output_dir_str.empty() && save_improper)
    {
      const std::string improper_path = (output_dir_path / IMPROPER_FILE_P).string();
      std::ofstream out(improper_path);
      out << improper_str << '\n';
      std::cout << "Wrote file '" << improper_path << "'\n";
    }
    std::cout << LINE;
  }
  if(std::any_of(samples.begin(), samples.end(),
                 [](const Sample & sample) { return sample.blacklist.size() > 0; }))
  {
    std::cout << "Missing numbers (to be blacklisted):\n";
    for(const Sample & sample: samples)
    {
      if(! sample.blacklist.size()) continue;
      std::cout << "\t* " << sample.name << ": "
                << boost::algorithm::join(sample.blacklist, ", ") << '\n';
    } // samples
    std::cout << LINE;
  } // any blacklist

//--- sum the event counts in the samples that have common ,,parent''
  std::map<std::string, unsigned long long> event_sums;
  for(const Sample & sample: samples)
    if(! sample.parentStr.empty())
    {
      if(! event_sums.count(sample.parentStr))
        event_sums[sample.parentStr] = sample.nof_events;
      else
        event_sums[sample.parentStr] += sample.nof_events;
    }
  std::cout << "Total event counts:\n";
  for(Sample & sample: samples)
  {
    if(! sample.parentStr.empty())
      sample.nof_events = event_sums[sample.parentStr];
    std::cout << "\t* " << sample.name << ": "
                        << sample.nof_events << '\n';
  }

  std::cout << "Final statistics:\n";
  std::cout << "\tTotal number of files present:  " << present.size() << '\n';
  std::cout << "\tNumber of broken files:         " << zombies.size() << '\n';
  std::cout << "\tNumber of files w/ 0 file size: " << zerofs.size()  << '\n';
  std::cout << "\tNumber of files that hadn't '" << histo_str << "' "
            << "as their TH1F: " << improper.size() << '\n';
  std::cout << "Total file counts:\n";
  for(const Sample & sample: samples)
    std::cout << "\t* " << sample.name << ": "
                        << sample.present.size() << '\n';

//--- generate basic python dictionaries out of the results
  if(! output_dir_str.empty() && save_python)
  {
    std::ofstream out((output_dir_path / PYTHON_FILE_P).string());
    out << "from collections import OrderedDict as OD\n\n"
        << "samples = OD()\n\n";
    for(const Sample & sample: samples)
      out << sample.get_cfg();
  }

//--- stop the clock
  const std::chrono::high_resolution_clock::time_point end_t =
      std::chrono::high_resolution_clock::now();
  const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>
    (end_t - start_t).count() / 1000.;
  std::cout << "Total execution time: " << std::setprecision(3) << std::fixed
            << duration << "s\n";

  return EXIT_SUCCESS;
}
