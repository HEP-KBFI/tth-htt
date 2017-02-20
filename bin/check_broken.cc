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
#include <boost/algorithm/string/predicate.hpp>

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
#define PYTHON_FILE_P   boost::filesystem::path("tthAnalyzeSamples_2016.py")

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
    -n [ --no_njets_cut ]       cut on number of jets >= 2 was not applied
    -f [ --filter ]             only look at datasets containing specified string

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
double
check_broken(const std::string & path,
             const std::string & histo,
             const bool isData = false)
{
  TFile f(path.c_str());
  double ret_val = ZOMBIE_FILE_C;
  if(! f.IsZombie())
  {
    if(f.GetListOfKeys() -> Contains(histo.c_str()))
    {
      TH1 * h;
      if(isData == true)
        h = dynamic_cast<TH1 *>(f.Get("Count"));
      else
        h = dynamic_cast<TH1 *>(f.Get(histo.c_str()));
      ret_val = h -> Integral();
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

  bool use_it;
  bool gen_weight;
  double x_sec;
  unsigned max_nr;
  unsigned long long nof_events;
  unsigned long long nof_events_unweighted;
  unsigned long long nof_dbs_events;
  bool found_on_disk;

  Sample() = default;
  /*Sample(boost::filesystem::path path)
    : path(path)
    , name(path.filename().string())
    , pathStr(path.string())
    , gen_weight(false)
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
    , gen_weight(false)
    , x_sec(0)
    , max_nr(0)
    , nof_events(0)
  {}*/

  Sample(std::string sample_name, std::string dbs_name, std::string sample_category, std::string process_name, double xs, unsigned long long dbsevents, bool use_it, bool gen_weight)
    : name(sample_name)
    , dbs_name(dbs_name)
    , category(sample_category)
    , process_name(process_name)
    , use_it(use_it)
    , gen_weight(gen_weight)
    , x_sec(xs)
    , nof_events(0)
    , nof_events_unweighted(0)
    , nof_dbs_events(dbsevents)
    , found_on_disk(false)    
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
      { "g_weight",        gen_weight ? "True" : "False"           },
      { "use_it",          use_it     ? "True" : "False"           },
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
    
    std::string input = "";
    if(category.find("data_obs")!=std::string::npos){
      input = input + "samples_2016[\"$(sample_dbs_name)\"] = OD([\n";
  	  input = input +
		    "  (\"type\",                  \"data\"),\n"
		    "  (\"sample_category\",       \"$(category)\"),\n"       
		    "  (\"process_name_specific\", \"$(process_name)\"),\n"   
		    "  (\"nof_files\",             $(max_nr)),\n"
		    "  (\"nof_events\",            $(nof_events)),\n";
		    //"  (\"nof_dbs_events\",        $(nof_dbs_events)),\n";
		    if(process_name.find("2016B")!=std::string::npos ||
		       process_name.find("2016C")!=std::string::npos ||
		       process_name.find("2016D")!=std::string::npos ||
		       process_name.find("2016E")!=std::string::npos ||
		       process_name.find("2016F")!=std::string::npos){
		      input = input + "  (\"use_HIP_mitigation_bTag\", True),\n";
		      input = input + "  (\"use_HIP_mitigation_mediumMuonId\", True),\n";
		    } else {
		      input = input + "  (\"use_HIP_mitigation_bTag\", False),\n";
		      input = input + "  (\"use_HIP_mitigation_mediumMuonId\", False),\n";
		    }
		    input = input + "  (\"use_it\",                $(use_it)),\n";
			if(process_name.find("SingleElec")!=std::string::npos) input = input + "  (\"triggers\",              [ \"1e\" ]),\n";
	    if(process_name.find("SingleMuon")!=std::string::npos) input = input + "  (\"triggers\",              [ \"1mu\" ]),\n";
	    if(process_name.find("DoubleEG")!=std::string::npos  ) input = input + "  (\"triggers\",              [ \"2e\", \"3e\" ]),\n";
	    if(process_name.find("DoubleMuon")!=std::string::npos) input = input + "  (\"triggers\",              [ \"2mu\", \"3mu\" ]),\n";
	    if(process_name.find("MuonEG")!=std::string::npos    ) input = input + "  (\"triggers\",              [ \"1e1mu\", \"2e1mu\", \"1e2mu\" ]),\n";
	    if(process_name.find("Tau")!=std::string::npos       ) input = input + "  (\"triggers\",              [ \"1e1tau\", \"1mu1tau\", \"2tau\" ]),\n";
	    input = input +	  
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
		    "])\n";
    }else{
	    input = input + "samples_2016[\"$(sample_dbs_name)\"] = OD([\n";
  	  input = input +
		    "  (\"type\",                  \"mc\"),\n"
		    "  (\"sample_category\",       \"$(category)\"),\n"       
		    "  (\"process_name_specific\", \"$(process_name)\"),\n"   
		    "  (\"nof_files\",             $(max_nr)),\n"
		    "  (\"nof_events\",            $(nof_events)),\n";
		    //"  (\"nof_dbs_events\",        $(nof_dbs_events)),\n"
		  input = input + "  (\"use_it\",                $(use_it)),\n";
		  input = input + "  (\"xsection\",              $(x_sec)),\n"
		    "  (\"genWeight\",             $(g_weight)),\n"
		    "  (\"triggers\",              [ \"1e\", \"1mu\", \"2e\", \"1e1mu\", \"2mu\", \"3e\", \"2e1mu\", \"1e2mu\", \"3mu\", \"1e1tau\", \"1mu1tau\", \"2tau\" ]),\n";
		  input = input + "  (\"reHLT\",                 True),\n";
	    input = input + "  (\"local_paths\",\n"
		    "    [\n"
		    "      OD([\n"
		    "        (\"path\",      \"$(super_parent)\"),\n"
		    "        (\"selection\", \"*\"),\n"
		    "        (\"blacklist\", [$(blacklist)]),\n"
		    "      ]),\n"
		    "    ]\n"
		    "  ),\n"
		    "])\n";
    }

    const boost::xpressive::sregex envar =
	    "$(" >> (boost::xpressive::s1 = +boost::xpressive::_w) >> ')';
    const std::string output = boost::xpressive::regex_replace(input, envar, fmt_fun);
    return output;
  }  
};

std::vstring
operator|(const std::vector<Sample*> samples,
          Sample::Info key)
{
  std::vstring result;
  for(Sample* sample: samples)
    if     (key == Sample::Info::kPresent)
      result.insert(result.end(), sample->present.begin(),   sample->present.end());
    else if(key == Sample::Info::kZombie)
      result.insert(result.end(), sample->zombies.begin(),   sample->zombies.end());
    else if(key == Sample::Info::kZerofs)
      result.insert(result.end(), sample->zerofs.begin(),    sample->zerofs.end());
    else if(key == Sample::Info::kImproper)
      result.insert(result.end(), sample->improper.begin(),  sample->improper.end());
  return result;
}


struct Samples
{
  std::map<std::string, Sample*> sample_list;
  std::map<std::string, int> parent_counter;
  
  Samples() = default;
  
  void add(boost::filesystem::path path, boost::filesystem::path parent)
  {
    std::string sample_name = path.filename().string();
    std::string sample_parent = parent.filename().string();
    
    //std::cout << "Sample name is: " << sample_name << ", parent: " << sample_parent << " " << sample_list.count(sample_name) << " " << path.string() << " " << parent.string() << std::endl; 
    if (sample_list.count(sample_name) == 1)
    {
      Sample* s = sample_list.at(sample_name);
      s->path = path;
      s->parent = parent;
      s->pathStr = path.string();
      s->parentStr = sample_parent;
      s->found_on_disk = true;
      *sample_list[sample_name] = *s;
    }
    else
    {
      std::cout << "WARNING: Directory does not correspond to any defined sample: " << path.string() << std::endl;
      //throw std::runtime_error("Directory does not correspond to any defined sample");
    }    
  }
  
  /*void add(boost::filesystem::path path, boost::filesystem::path parent)
  {
    std::str sample_name = path.filename().string();
    add(boost::filesystem::path path)
    
  }*/
  
  void define(const std::string sample_name, const std::string dbs_name, const std::string sample_category, const std::string process_name, double xs, int dbsevents, bool use_it = true, bool genweights = true)
  {
    sample_list[sample_name] = new Sample(sample_name, dbs_name, sample_category, process_name, xs, dbsevents, use_it, genweights);
  }
  
  std::vector<Sample*> get_list()
  {
    std::vector<Sample*> sl;
    for(auto &ent : sample_list) {
      auto &s = ent.second;
      if(s->found_on_disk == true)
        sl.push_back(s);
    }
    return sl;
  }
  
  std::vector<Sample*> get_missing_list()
  {
    std::vector<Sample*> sl;
    for(auto &ent : sample_list) {
      auto &s = ent.second;
      if(s->found_on_disk == false)
        sl.push_back(s);
    }
    return sl;
  }
};






int
main(int argc,
     char * argv[])
{
  setenv("TZ", "/etc/localtime", 1); // needed by std::chrono::
  gROOT -> ProcessLine(Form("gErrorIgnoreLevel = %d;", kBreak));


  Samples samples;
  //Data
  samples.define("VHBB_HEPPY_V25tthtautau_v2_DoubleEG__Run2016B-23Sep2016-v3",
    "/DoubleEG/Run2016B-23Sep2016-v3/MINIAOD",
    "data_obs", "DoubleEG_Run2016B_v3", 1, 143073268, true, false);
  samples.define("VHBB_HEPPY_V25tthtautau_v2_DoubleEG__Run2016C-23Sep2016-v1",
    "/DoubleEG/Run2016C-23Sep2016-v1/MINIAOD",
    "data_obs", "DoubleEG_Run2016C_v1", 1, 47677856, true, false);
  samples.define("VHBB_HEPPY_V25tthtautau_v2_DoubleEG__Run2016D-23Sep2016-v1",
    "/DoubleEG/Run2016D-23Sep2016-v1/MINIAOD",
    "data_obs", "DoubleEG_Run2016D_v1", 1, 53324960, true, false);
  samples.define("VHBB_HEPPY_V25tthtautau_v2_DoubleEG__Run2016E-23Sep2016-v1",
    "/DoubleEG/Run2016E-23Sep2016-v1/MINIAOD",
    "data_obs", "DoubleEG_Run2016E_v1", 1, 49877710, true, false);
  samples.define("VHBB_HEPPY_V25tthtautau_v2_DoubleEG__Run2016F-23Sep2016-v1",
    "/DoubleEG/Run2016F-23Sep2016-v1/MINIAOD",
    "data_obs", "DoubleEG_Run2016F_v1", 1, 34577629, true, false);
  samples.define("VHBB_HEPPY_V25tthtautau_v2_DoubleEG__Run2016G-23Sep2016-v1",
    "/DoubleEG/Run2016G-23Sep2016-v1/MINIAOD",
    "data_obs", "DoubleEG_Run2016G_v1", 1, 78797031, true, false);
  samples.define("VHBB_HEPPY_V25tthtautau_v2_DoubleEG__Run2016H-PromptReco-v2",
    "/DoubleEG/Run2016H-PromptReco-v2/MINIAOD",
    "data_obs", "DoubleEG_Run2016H_v2_promptReco", 1, 84344490, true, false);
  samples.define("VHBB_HEPPY_V25tthtautau_v2_DoubleEG__Run2016H-PromptReco-v3",
    "/DoubleEG/Run2016H-PromptReco-v3/MINIAOD",
    "data_obs", "DoubleEG_Run2016H_v3_promptReco", 1, 2460002, true, false);
  
  samples.define("VHBB_HEPPY_V25tthtautau_v2_DoubleMuon__Run2016B-23Sep2016-v3",
    "/DoubleMuon/Run2016B-23Sep2016-v3/MINIAOD",
    "data_obs", "DoubleMuon_Run2016B_v3", 1, 82535526, true, false);
  samples.define("VHBB_HEPPY_V25tthtautau_v2_DoubleMuon__Run2016C-23Sep2016-v1",
    "/DoubleMuon/Run2016C-23Sep2016-v1/MINIAOD",
    "data_obs", "DoubleMuon_Run2016C_v1", 1, 27934629, true, false);
  samples.define("VHBB_HEPPY_V25tthtautau_v2_DoubleMuon__Run2016D-23Sep2016-v1",
    "/DoubleMuon/Run2016D-23Sep2016-v1/MINIAOD",
    "data_obs", "DoubleMuon_Run2016D_v1", 1, 33861745, true, false);
  samples.define("VHBB_HEPPY_V25tthtautau_v2_DoubleMuon__Run2016E-23Sep2016-v1",
    "/DoubleMuon/Run2016E-23Sep2016-v1/MINIAOD",
    "data_obs", "DoubleMuon_Run2016E_v1", 1, 28246946, true, false);
  samples.define("VHBB_HEPPY_V25tthtautau_v2_DoubleMuon__Run2016F-23Sep2016-v1",
    "/DoubleMuon/Run2016F-23Sep2016-v1/MINIAOD",
    "data_obs", "DoubleMuon_Run2016F_v1", 1, 20329921, true, false);
  samples.define("VHBB_HEPPY_V25tthtautau_v2_DoubleMuon__Run2016G-23Sep2016-v1",
    "/DoubleMuon/Run2016G-23Sep2016-v1/MINIAOD",
    "data_obs", "DoubleMuon_Run2016G_v1", 1, 45235604, true, false);
  samples.define("VHBB_HEPPY_V25tthtautau_DoubleMuon__Run2016H-PromptReco-v2",
    "/DoubleMuon/Run2016H-PromptReco-v2/MINIAOD",
    "data_obs", "DoubleMuon_Run2016H_v2_promptReco", 1, 48093751, true, false);
  samples.define("VHBB_HEPPY_V25tthtautau_DoubleMuon__Run2016H-PromptReco-v3",
    "/DoubleMuon/Run2016H-PromptReco-v3/MINIAOD",
    "data_obs", "DoubleMuon_Run2016H_v3_promptReco", 1, 1219733, true, false);
    
  samples.define("VHBB_HEPPY_V25tthtautau_v2_MuonEG__Run2016B-23Sep2016-v3",
    "/MuonEG/Run2016B-23Sep2016-v3/MINIAOD",
    "data_obs", "MuonEG_Run2016B_v3", 1, 32727796, true, false);
  samples.define("VHBB_HEPPY_V25tthtautau_v2_MuonEG__Run2016C-23Sep2016-v1",
    "/MuonEG/Run2016C-23Sep2016-v1/MINIAOD",
    "data_obs", "MuonEG_Run2016C_v1", 1, 15405678, true, false);
  samples.define("VHBB_HEPPY_V25tthtautau_MuonEG__Run2016D-23Sep2016-v1",
    "/MuonEG/Run2016D-23Sep2016-v1/MINIAOD",
    "data_obs", "MuonEG_Run2016D_v1", 1, 23482352, true, false);
  samples.define("VHBB_HEPPY_V25tthtautau_v2_MuonEG__Run2016E-23Sep2016-v1",
    "/MuonEG/Run2016E-23Sep2016-v1/MINIAOD",
    "data_obs", "MuonEG_Run2016E_v1", 1, 22519303, true, false);
  samples.define("VHBB_HEPPY_V25tthtautau_v2_MuonEG__Run2016F-23Sep2016-v1",
    "/MuonEG/Run2016F-23Sep2016-v1/MINIAOD",
    "data_obs", "MuonEG_Run2016F_v1", 1, 16002165, true, false);
  samples.define("VHBB_HEPPY_V25tthtautau_v2_MuonEG__Run2016G-23Sep2016-v1",
    "/MuonEG/Run2016G-23Sep2016-v1/MINIAOD",
    "data_obs", "MuonEG_Run2016G_v1", 1, 33854612, true, false);
  samples.define("VHBB_HEPPY_V25tthtautau_MuonEG__Run2016H-PromptReco-v2",
    "/MuonEG/Run2016H-PromptReco-v2/MINIAOD",
    "data_obs", "MuonEG_Run2016H_v2_promptReco", 1, 28705853, true, false);
  samples.define("VHBB_HEPPY_V25tthtautau_MuonEG__Run2016H-PromptReco-v3",
    "/MuonEG/Run2016H-PromptReco-v3/MINIAOD",
    "data_obs", "MuonEG_Run2016H_v3_promptReco", 1, 770494, true, false);
    
  samples.define("VHBB_HEPPY_V25tthtautau_v2_SingleElectron__Run2016B-23Sep2016-v3",
    "/SingleElectron/Run2016B-23Sep2016-v3/MINIAOD",
    "data_obs", "SingleElectron_Run2016B_v3", 1, 246440440, true, false);
  samples.define("VHBB_HEPPY_V25tthtautau_v2_SingleElectron__Run2016C-23Sep2016-v1",
    "/SingleElectron/Run2016C-23Sep2016-v1/MINIAOD",
    "data_obs", "SingleElectron_Run2016C_v1", 1, 97259854, true, false);
  samples.define("VHBB_HEPPY_V25tthtautau_v2_SingleElectron__Run2016D-23Sep2016-v1",
    "/SingleElectron/Run2016D-23Sep2016-v1/MINIAOD",
    "data_obs", "SingleElectron_Run2016D_v1", 1, 148167727, true, false);
  samples.define("VHBB_HEPPY_V25tthtautau_v2_SingleElectron__Run2016E-23Sep2016-v1",
    "/SingleElectron/Run2016E-23Sep2016-v1/MINIAOD",
    "data_obs", "SingleElectron_Run2016E_v1", 1, 117321545, true, false);
  samples.define("VHBB_HEPPY_V25tthtautau_v2_SingleElectron__Run2016F-23Sep2016-v1",
    "/SingleElectron/Run2016F-23Sep2016-v1/MINIAOD",
    "data_obs", "SingleElectron_Run2016F_v1", 1, 70593532, true, false);
  samples.define("VHBB_HEPPY_V25tthtautau_v2_SingleElectron__Run2016G-23Sep2016-v1",
    "/SingleElectron/Run2016G-23Sep2016-v1/MINIAOD",
    "data_obs", "SingleElectron_Run2016G_v1", 1, 153363109, true, false);
  samples.define("VHBB_HEPPY_V25tthtautau_SingleElectron__Run2016H-PromptReco-v2",
    "/SingleElectron/Run2016H-PromptReco-v2/MINIAOD",
    "data_obs", "SingleElectron_Run2016H_v2_promptReco", 1, 126863489, true, false);
  samples.define("VHBB_HEPPY_V25tthtautau_SingleElectron__Run2016H-PromptReco-v3",
    "/SingleElectron/Run2016H-PromptReco-v3/MINIAOD",
    "data_obs", "SingleElectron_Run2016H_v3_promptReco", 1, 3191585, true, false);
      
  samples.define("VHBB_HEPPY_V25tthtautau_v2_SingleMuon__Run2016B-23Sep2016-v3",
    "/SingleMuon/Run2016B-23Sep2016-v3/MINIAOD",
    "data_obs", "SingleMuon_Run2016B_v3", 1, 158145722, true, false);
  samples.define("VHBB_HEPPY_V25tthtautau_v2_SingleMuon__Run2016C-23Sep2016-v1",
    "/SingleMuon/Run2016C-23Sep2016-v1/MINIAOD",
    "data_obs", "SingleMuon_Run2016C_v1", 1, 67441308, true, false);
  samples.define("VHBB_HEPPY_V25tthtautau_v2_SingleMuon__Run2016D-23Sep2016-v1",
    "/SingleMuon/Run2016D-23Sep2016-v1/MINIAOD",
    "data_obs", "SingleMuon_Run2016D_v1", 1, 98017996, true, false);
  samples.define("VHBB_HEPPY_V25tthtautau_v2_SingleMuon__Run2016E-23Sep2016-v1",
    "/SingleMuon/Run2016E-23Sep2016-v1/MINIAOD",
    "data_obs", "SingleMuon_Run2016E_v1", 1, 90984718, true, false);
  samples.define("VHBB_HEPPY_V25tthtautau_SingleMuon__Run2016F-23Sep2016-v1",
    "/SingleMuon/Run2016F-23Sep2016-v1/MINIAOD",
    "data_obs", "SingleMuon_Run2016F_v1", 1, 65489554, true, false);
  samples.define("VHBB_HEPPY_V25tthtautau_v2_SingleMuon__Run2016G-23Sep2016-v1",
    "/SingleMuon/Run2016G-23Sep2016-v1/MINIAOD",
    "data_obs", "SingleMuon_Run2016G_v1", 1, 149916849, true, false);
  samples.define("VHBB_HEPPY_V25tthtautau_SingleMuon__Run2016H-PromptReco-v2",
    "/SingleMuon/Run2016H-PromptReco-v2/MINIAOD",
    "data_obs", "SingleMuon_Run2016H_v2_promptReco", 1, 171134793, true, false);
  samples.define("VHBB_HEPPY_V25tthtautau_SingleMuon__Run2016H-PromptReco-v3",
    "/SingleMuon/Run2016H-PromptReco-v3/MINIAOD",
    "data_obs", "SingleMuon_Run2016H_v3_promptReco", 1, 4393222, true, false);
      
  samples.define("VHBB_HEPPY_V25tthtautau_HLT_Tau__Run2016B-23Sep2016-v3",
    "/Tau/Run2016B-23Sep2016-v3/MINIAOD",
    "data_obs", "Tau_Run2016B_v3", 1, 68727458, true, false);
  samples.define("VHBB_HEPPY_V25tthtautau_HLT_Tau__Run2016C-23Sep2016-v1",
    "/Tau/Run2016C-23Sep2016-v1/MINIAOD",
    "data_obs", "Tau_Run2016C_v1", 1, 36931473, true, false);
  samples.define("VHBB_HEPPY_V25tthtautau_HLT_Tau__Run2016D-23Sep2016-v1",
    "/Tau/Run2016D-23Sep2016-v1/MINIAOD",
    "data_obs", "Tau_Run2016D_v1", 1, 56827771, true, false);
  samples.define("VHBB_HEPPY_V25tthtautau_HLT_Tau__Run2016E-23Sep2016-v1",
    "/Tau/Run2016E-23Sep2016-v1/MINIAOD",
    "data_obs", "Tau_Run2016E_v1", 1, 58348773, true, false);
  samples.define("VHBB_HEPPY_V25tthtautau_HLT_Tau__Run2016F-23Sep2016-v1",
    "/Tau/Run2016F-23Sep2016-v1/MINIAOD",
    "data_obs", "Tau_Run2016F_v1", 1, 40549716, true, false);
  samples.define("VHBB_HEPPY_V25tthtautau_v2_Tau__Run2016G-23Sep2016-v1",
    "/Tau/Run2016G-23Sep2016-v1/MINIAOD",
    "data_obs", "Tau_Run2016G_v1", 1, 79578661, true, false);
  samples.define("VHBB_HEPPY_V25tthtautau_Tau__Run2016H-PromptReco-v2",
    "/Tau/Run2016H-PromptReco-v2/MINIAOD",
    "data_obs", "Tau_Run2016H_v2_promptReco", 1, 76504267, true, false);
  samples.define("VHBB_HEPPY_V25tthtautau_Tau__Run2016H-PromptReco-v3",
    "/Tau/Run2016H-PromptReco-v3/MINIAOD",
    "data_obs", "Tau_Run2016H_v3_promptReco", 1, 1898072, true, false);

  //MC
  samples.define("VHBB_HEPPY_V25tthtautau_DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v1",
    "/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM",
    "EWK", "DYJetsToLL_M-10to50", 18610, 40381391);
  samples.define("VHBB_HEPPY_V25tthtautau_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-Py8__RunIISummer16MAv2-PUMoriond17_HCALDebug_80r2as_2016_TrancheIV_v6-v1",
    "/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_HCALDebug_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM",
    "EWK", "DYJetsToLL_M-50", 6025.2, 28968252);
  samples.define("VHBB_HEPPY_V25tthtautau_GluGluHToZZTo4L_M125_13TeV_powheg2_JHUgenV6_Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1",
    "/GluGluHToZZTo4L_M125_13TeV_powheg2_JHUgenV6_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM",
    "additional_signal_overlap", "GluGluHToZZTo4L", 0.0119, 999800);
  
  samples.define("VHBB_HEPPY_V25tthtautau_ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-Py8_TuneCUETP8M1__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1",
    "/ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM",
    "TT", "ST_s-channel_4f_leptonDecays", 3.68, 1000000);
  samples.define("VHBB_HEPPY_V25tt_ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-Py8_TuneCUETP8M1__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1", 
    "/ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM", 
    "TT", "ST_t-channel_antitop_4f_inclusiveDecays", 80.95, 38811017);
  samples.define("VHBB_HEPPY_V25tthtautau_ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-Py8_TuneCUETP8M1__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1",
    "/ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM", 
    "TT", "ST_t-channel_top_4f_inclusiveDecays", 136.02, 67240808);
  samples.define("VHBB_HEPPY_V25tthtautau_ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-Py8_TuneCUETP8M1__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v1",
    "/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM",
    "TT", "ST_tW_antitop_5f_inclusiveDecays", 35.6, 6933094);
  samples.define("VHBB_HEPPY_V25tthtautau_ST_tW_top_5f_inclusiveDecays_13TeV-powheg-Py8_TuneCUETP8M1__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v1",
    "/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM",
    "TT", "ST_tW_top_5f_inclusiveDecays", 35.6, 6952830);
  
  samples.define("VHBB_HEPPY_V25tthtautau_TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v1",
    "/TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM",
    "Rares", "TGJets_ext1", 2.967, 1556996);
  samples.define("VHBB_HEPPY_V25tthtautau_TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1",
    "/TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM",
    "Rares", "TGJets", 2.967, 292508);
  samples.define("VHBB_HEPPY_V25tthtautau_THW_Hincl_13TeV-madgraph-Py8_TuneCUETP8M1__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1",
    "/THW_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM",
    "additional_signal_overlap", "THW_Hincl", 0.01561, 1499200);
  samples.define("VHBB_HEPPY_V25tthtautau_TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v1",
    "/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM",
    "Rares", "TTGJets_ext1", 3.697, 9885348);
  samples.define("VHBB_HEPPY_V25tthtautau_TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1",
    "/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM",
    "Rares", "TTGJets", 3.697, 4870911);
  samples.define("VHBB_HEPPY_V25tthtautau_v2_ttHJetTobb_M125_13TeV_amcatnloFXFX_madspin_Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext3-v1",
    "/ttHJetTobb_M125_13TeV_amcatnloFXFX_madspin_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext3-v1/MINIAODSIM",
    "ttH_hbb", "ttHJetTobb_M125", 0.2934, 9794226); 
  samples.define("VHBB_HEPPY_V25tthtautau_ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_Py8_mWCutfix__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v1",
    "/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM",
    "signal", "ttHJetToNonbb_M125_amcatnlo", 0.2151, 10045633);
  samples.define("VHBB_HEPPY_V25tthtautau_ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1",
    "/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM",
    "signal", "ttHToNonbb_M125_powheg", 0.2151, 3981250);
      
  samples.define("VHBB_HEPPY_V25tthtautau_TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v1",
    "/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM",
    "TT", "TTJets_DiLept_ext1", 87.3, 24350202);
  samples.define("VHBB_HEPPY_V25tthtautau_TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1",
    "/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM",
    "TT", "TTJets_DiLept", 87.3, 6094476);
  samples.define("VHBB_HEPPY_V25tthtautau_v2_TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v1",
    "/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM",
    "TT", "TTJets_SingleLeptFromTbar_ext1", 182.18, 48266353);
  samples.define("VHBB_HEPPY_V25tthtautau_TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1",
    "/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM",
    "TT", "TTJets_SingleLeptFromTbar", 182.18, 11944041);
  samples.define("VHBB_HEPPY_V25tthtautau_TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v1",
    "/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM",
    "TT", "TTJets_SingleLeptFromT_ext1", 182.18, 50016934);
  samples.define("VHBB_HEPPY_V25tthtautau_TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1",
    "/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM",
    "TT", "TTJets_SingleLeptFromT", 182.18, 11957043);
  samples.define("VHBB_HEPPY_V25tthtautau_TTTT_TuneCUETP8M1_13TeV-amcatnlo-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1",
    "/TTTT_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM",
    "Rares", "TTTT", 0.009103, 250000);
  samples.define("VHBB_HEPPY_V25tthtautau_TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v3",
    "/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v3/MINIAODSIM",
    "TTW", "TTWJetsToLNu_ext1", 0.2043, 2160168);
  samples.define("VHBB_HEPPY_V25tthtautau_TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext2-v1",
    "/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/MINIAODSIM",
    "TTW", "TTWJetsToLNu_ext2", 0.2043, 3120397); 
  samples.define("VHBB_HEPPY_V25tthtautau_TTZToLL_M-1to10_TuneCUETP8M1_13TeV-madgraphMLM-Py8__RunIISummer16MAv2-80r2as_2016_TrancheIV_v6-v1",
    "/TTZToLL_M-1to10_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM",
    "TTZ", "TTZToLL_M-1to10", 0.0493, 246792);
  samples.define("VHBB_HEPPY_V25tthtautau_TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v1",
    "/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM",
    "TTZ", "TTZToLL_M10_ext1", 0.2529, 1992438);
  samples.define("VHBB_HEPPY_V25tthtautau_TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext2-v1",
    "/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/MINIAODSIM",
    "TTZ", "TTZToLL_M10_ext2", 0.2529, 5982035); 
  samples.define("VHBB_HEPPY_V25tthtautau_tZq_ll_4f_13TeV-amcatnlo-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v1",
    "/tZq_ll_4f_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM", 
    "Rares", "tZq_ll_4f", 0.0758, 14509520);
  samples.define("VHBB_HEPPY_V25tthtautau_WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v1",
    "/WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM",
    "Rares", "WGToLNuG_ext1", 585.8, 5048470);
  samples.define("VHBB_HEPPY_V25tthtautau_WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext2-v1",
    "/WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/MINIAODSIM",
    "Rares", "WGToLNuG_ext2", 585.8, 10231994);
  samples.define("VHBB_HEPPY_V25tthtautau_WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1",
    "/WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM",
    "EWK", "WJetsToLNu", 61526.7, 24120319);
  samples.define("VHBB_HEPPY_V25tthtautau_WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1",
    "/WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM",
    "Rares", "WpWpJJ_EWK-QCD", 0.03711, 149681);
  samples.define("VHBB_HEPPY_V25tthtautau_WWTo2L2Nu_13TeV-powheg__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1",
    "/WWTo2L2Nu_13TeV-powheg/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM",
    "EWK", "WWTo2L2Nu", 10.481, 1999000);
  samples.define("VHBB_HEPPY_V25tthtautau_WWTo2L2Nu_DoubleScattering_13TeV-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1",
    "/WWTo2L2Nu_DoubleScattering_13TeV-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM",
    "Rares", "WWTo2L2Nu_DoubleScattering", 1.64, 999367);
  samples.define("VHBB_HEPPY_V25tthtautau_WWW_4F_TuneCUETP8M1_13TeV-amcatnlo-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1",
    "/WWW_4F_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM",
    "Rares", "WWW_4F", 0.2086, 240000);
  samples.define("VHBB_HEPPY_V25tthtautau_WWZ_TuneCUETP8M1_13TeV-amcatnlo-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1",
    "/WWZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM",
    "Rares", "WWZ", 0.1651, 250000);
  samples.define("VHBB_HEPPY_V25tthtautau_WZTo3LNu_TuneCUETP8M1_13TeV-powheg-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1",
    "/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM",
    "EWK", "WZTo3LNu", 4.42965, 1993200);
  samples.define("VHBB_HEPPY_V25tthtautau_WZZ_TuneCUETP8M1_13TeV-amcatnlo-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1",
    "/WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM",
    "Rares", "WZZ", 0.05565, 246800);
  samples.define("VHBB_HEPPY_V25tthtautau_ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v1",
    "/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM",
    "Rares", "ZGTo2LG", 131.3, 14372682);
  samples.define("VHBB_HEPPY_V25tthtautau_ZZTo4L_13TeV_powheg_Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1",
    "/ZZTo4L_13TeV_powheg_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM",
    "EWK", "ZZTo4L", 1.256, 6669988);
  samples.define("VHBB_HEPPY_V25tthtautau_ZZZ_TuneCUETP8M1_13TeV-amcatnlo-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1",
    "/ZZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM",
    "Rares", "ZZZ", 0.01398, 249237);
  

  //Fastsim
  samples.define("VHBB_HEPPY_V25tthtautau_ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-Py8__matze-faster_v8_ttH_maod_p1_3a2fa29ab1d54ae0995b28f27b405be9-v1",
    "/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/matze-faster_v8_ttH_maod_p1_3a2fa29ab1d54ae0995b28f27b405be9-v1/USER", 
    "signal", "ttHToNonbb_fastsim_p1", 0.2151, 3364164, false);
  samples.define("VHBB_HEPPY_V25tthtautau_ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-Py8__matze-faster_v8_ttH_maod_p2_3a2fa29ab1d54ae0995b28f27b405be9-v1",
    "/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/matze-faster_v8_ttH_maod_p2_3a2fa29ab1d54ae0995b28f27b405be9-v1/USER", 
    "signal", "ttHToNonbb_fastsim_p2", 0.2151, 6730644, false);
  samples.define("VHBB_HEPPY_V25tthtautau_ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-Py8__matze-faster_v8_ttH_maod_p3_3a2fa29ab1d54ae0995b28f27b405be9-v1",
    "/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/matze-faster_v8_ttH_maod_p3_3a2fa29ab1d54ae0995b28f27b405be9-v1/USER", 
    "signal", "ttHToNonbb_fastsim_p3", 0.2151, 6730644, false);
  
  samples.define("VHBB_HEPPY_V25tthtautau_TTTo2L2Nu_TuneCUETP8M2_ttHtranche3_13TeV-powheg-Py8__matze-faster_v8_ttjets_dl_maod_p1_3a2fa29ab1d54ae0995b28f27b405be9-v1",
    "/TTTo2L2Nu_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/matze-faster_v8_ttjets_dl_maod_p1_3a2fa29ab1d54ae0995b28f27b405be9-v1/USER", 
    "TT", "TTTo2L2Nu_fastsim_p1", 87.3, 18104800, false);
  samples.define("VHBB_HEPPY_V25tthtautau_TTTo2L2Nu_TuneCUETP8M2_ttHtranche3_13TeV-powheg-Py8__matze-faster_v8_ttjets_dl_maod_p2_3a2fa29ab1d54ae0995b28f27b405be9-v1",
    "/TTTo2L2Nu_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/matze-faster_v8_ttjets_dl_maod_p2_3a2fa29ab1d54ae0995b28f27b405be9-v1/USER", 
    "TT", "TTTo2L2Nu_fastsim_p2", 87.3, 36233819, false);
  samples.define("VHBB_HEPPY_V25tthtautau_TTTo2L2Nu_TuneCUETP8M2_ttHtranche3_13TeV-powheg-Py8__matze-faster_v8_ttjets_dl_maod_p3_3a2fa29ab1d54ae0995b28f27b405be9-v1",
    "/TTTo2L2Nu_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/matze-faster_v8_ttjets_dl_maod_p3_3a2fa29ab1d54ae0995b28f27b405be9-v1/USER", 
    "TT", "TTTo2L2Nu_fastsim_p3", 87.3, 36199711, false);
  
  samples.define("VHBB_HEPPY_V25tthtautau_TTToSemilepton_TuneCUETP8M2_ttHtranche3_13TeV-powheg-Py8__matze-faster_v8_ttjets_sl_maod_p1_3a2fa29ab1d54ae0995b28f27b405be9-v1",
    "/TTToSemilepton_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/matze-faster_v8_ttjets_sl_maod_p1_3a2fa29ab1d54ae0995b28f27b405be9-v1/USER", 
    "TT", "TTToSemilepton_fastsim_p1", 245, 17071373, false);
  samples.define("VHBB_HEPPY_V25tthtautau_TTToSemilepton_TuneCUETP8M2_ttHtranche3_13TeV-powheg-Py8__matze-faster_v8_ttjets_sl_maod_p2_3a2fa29ab1d54ae0995b28f27b405be9-v1",
    "/TTToSemilepton_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/matze-faster_v8_ttjets_sl_maod_p2_3a2fa29ab1d54ae0995b28f27b405be9-v1/USER", 
    "TT", "TTToSemilepton_fastsim_p2", 245, 34133550, false);
  samples.define("VHBB_HEPPY_V25tthtautau_TTToSemilepton_TuneCUETP8M2_ttHtranche3_13TeV-powheg-Py8__matze-faster_v8_ttjets_sl_maod_p3_3a2fa29ab1d54ae0995b28f27b405be9-v1",
    "/TTToSemilepton_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/matze-faster_v8_ttjets_sl_maod_p3_3a2fa29ab1d54ae0995b28f27b405be9-v1/USER", 
    "TT", "TTToSemilepton_fastsim_p3", 245, 34137312, false);
  
  samples.define("VHBB_HEPPY_V25tthtautau_TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-Py8__matze-faster_v9_ttW_maod_54aa74f75231422e9f4d3766cb92a64a-v1",
    "/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/matze-faster_v9_ttW_maod_54aa74f75231422e9f4d3766cb92a64a-v1/USER",
    "TTW", "TTWJetsToLNu_fastsim", 0.2043, 14045606, false);
  samples.define("VHBB_HEPPY_V25tthtautau_TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-Py8__matze-faster_v9_ttZ_maod_54aa74f75231422e9f4d3766cb92a64a-v1",
    "/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/matze-faster_v9_ttZ_maod_54aa74f75231422e9f4d3766cb92a64a-v1/USER",
    "TTZ", "TTZToLLNuNu_fastsim", 0.2529, 19365805, false);
  samples.define("VHBB_HEPPY_V25tthtautau_WZTo3LNu_TuneCUETP8M1_13TeV-powheg-Py8__matze-faster_v9_WZ_maod_54aa74f75231422e9f4d3766cb92a64a-v1",
    "/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/matze-faster_v9_WZ_maod_54aa74f75231422e9f4d3766cb92a64a-v1/USER",
    "EWK", "WZTo3LNu_fastsim", 4.102, 18814150, false);
  
  //--- parse command line arguments
  std::string histo_str, output_dir_str, filter;
  std::vector<std::string> target_strs;
  bool save_zerofs, save_improper, save_python, verbose, data_only;
  try
  {
    boost::program_options::options_description desc("Allowed options");
    desc.add_options()
      ("help,h",     "produce help message")
      ("path,p",     boost::program_options::value<std::vector<std::string>>(&target_strs) -> multitoken() -> required(),
                     "full path to the directories to scan")
      ("histo,H",     boost::program_options::value<std::string>(&histo_str) -> default_value("CountWeighted"),
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
      ("dataonly,d", boost::program_options::bool_switch(&data_only) -> default_value(false),
                     "only go through data directories")
      ("filter,f",   boost::program_options::value<std::string>(&filter) -> default_value(""),
                     "check only dataset containing specified string")
                     
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
  for (const std::string &target_str: target_strs){
    if(! boost::filesystem::is_directory(target_str))
    {
      std::cerr << "No such directory: '" << target_str << "'\n";
      return EXIT_FAILURE;
    }
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
  for (const std::string &target_str: target_strs){
    std::cout << "Directory to analyze: " << target_str << '\n';
  }
  std::cout << "TH1F name: "            << histo_str << '\n'
            << "Verbose printout: "     << std::boolalpha << verbose << '\n';
  if(! output_dir_path.empty())
    std::cout << "Output directory: " << output_dir_path.string() << '\n';
  std::cout << LINE;

//--- start the clock
  const std::chrono::high_resolution_clock::time_point start_t =
    std::chrono::high_resolution_clock::now();

//--- create a list of immediate subdirectories of a given directory
  //std::vector<Sample> samples;
  for (const std::string &target_str: target_strs){
    const boost::filesystem::path target_path(target_str);
    boost::filesystem::directory_iterator target_it(target_path);
    for(const boost::filesystem::path & p: target_it){
      if(boost::filesystem::is_directory(p))
      {
        if(filter.length() > 0 && !boost::contains(p.string(), filter))
          continue;
        if(data_only == true && (boost::ends_with(p.string(), "MC") || boost::ends_with(p.string(), "MC_fastsim")))
          continue;
        else if(boost::ends_with(p.string(), "MC") || boost::ends_with(p.string(), "MC_fastsim")) //MC got accidentally arranged one level below
        {
          const boost::filesystem::path target_path2(p.string());
          boost::filesystem::directory_iterator target_it2(target_path2);
          for(const boost::filesystem::path & p2: target_it2)
          {
            if(boost::filesystem::is_directory(p2))
            {
              if(filter.length() > 0 && !boost::contains(p2.string(), filter))
                continue;
              if(verbose) std::cout << "Found sample directory: " << p2.string() << std::endl;
              std::vector<boost::filesystem::path> immediate_subsubdirs;
              boost::filesystem::directory_iterator sub_it(p2);
              for(const boost::filesystem::path & sub_p: sub_it)
                if(boost::filesystem::is_directory(sub_p))
                  immediate_subsubdirs.push_back(sub_p);
              for(const boost::filesystem::path & sub_p: immediate_subsubdirs)
                samples.add(sub_p, p2);
            }
          }
        }
        else
        {
          if(verbose) std::cout << "Found sample directory: " << p.string() << std::endl;
          std::vector<boost::filesystem::path> immediate_subsubdirs;
          boost::filesystem::directory_iterator sub_it(p);
          for(const boost::filesystem::path & sub_p: sub_it)
            if(boost::filesystem::is_directory(sub_p))
              immediate_subsubdirs.push_back(sub_p);
          for(const boost::filesystem::path & sub_p: immediate_subsubdirs)
            samples.add(sub_p, p);
        }
      }
      if(verbose) std::cout << LINE;
    }
  }

//--- loop over the list of immediate subdirectories recursively
  for(Sample *sample: samples.get_list())
  {
    if(verbose) std::cout << ">> Looping over: " << sample->pathStr << std::endl;
    for(const boost::filesystem::directory_entry & it: recursive_directory_range(sample->path))
    {
      //std::cout << "it " << it << std::endl;
      const boost::filesystem::path file = it.path();
      //std::cout << "path " << it.path() << std::endl;
      const std::string file_str = file.string();
      //std::cout << "file_str " << file_str << std::endl;
//--- if we're dealing with a valid root file
      if(boost::filesystem::is_regular_file(file) &&
         boost::filesystem::extension(file) == ".root")
      {
        //if(verbose) std::cout << "Sample name: " << sample.dbs_name << '\n';
        //if(verbose) std::cout << "Sample category: " << sample.category << '\n';
        //if(verbose) std::cout << "Process name: " << sample.process_name << '\n';
        //if(verbose) std::cout << "Checking: " << file_str << '\n';
//--- parse the tree number
        sample->present.push_back(file_str);
//--- read the file size before checking the zombiness
        const boost::uintmax_t file_size = boost::filesystem::file_size(file);
        if(! file_size)
        {
          sample->zerofs.push_back(file_str);
//--- don't even bother checking whether the file is zombie or not
          continue;
        }
        bool isData = false;
        if(sample->category.find("data_obs")!=std::string::npos) isData = true;
        const double nof_events = check_broken(file_str, histo_str, isData); //tree_str);
        const double nof_events_unweighted = check_broken(file_str, "Count", isData); //tree_str);
        
        if     (nof_events > 0)                sample->nof_events += nof_events;
        else if(nof_events -0.5 < ZOMBIE_FILE_C)   sample->zombies.push_back(file_str);
        else if(nof_events -0.5 < IMPROPER_FILE_C) sample->improper.push_back(file_str);
        
        if     (nof_events_unweighted > 0)                sample->nof_events_unweighted += nof_events_unweighted;
        
//--- if the valid root file has path ../<grid job id>/000X/tree_i.root, then in order
//--- to build the Python configuration file is to gather the paths to <grid job id>
        if(sample->fileSuperParent.empty())
          sample->fileSuperParent = file.parent_path().parent_path().string();

      } // is root file
    } // recursive loop
    if (sample->nof_events_unweighted > sample->nof_dbs_events)
    {
      std::cout << sample->nof_events_unweighted << " > " << sample->nof_dbs_events << std::endl;
      //throw std::runtime_error("Sample has more events than specified in DBS");
      std::cout << "WARNING: Sample has more events than specified in DBS" << std::endl;
    }
    else if(sample->nof_events_unweighted < sample->nof_dbs_events)
      std::cout << "WARNING: " << sample->name << " missing " << sample->nof_dbs_events - sample->nof_events_unweighted << " events." << std::endl;
    //else everything is fine - all events have been processed
    
  } // immediate subdirectory loop
  if(verbose) std::cout << LINE;

//--- post-process

  std::cout << "Post-processing ...\n";
  for(Sample* sample: samples.get_list())
    sample->check_completion();
  const auto present   = samples.get_list() | Sample::Info::kPresent;
  const auto zombies   = samples.get_list() | Sample::Info::kZombie;
  const auto zerofs    = samples.get_list() | Sample::Info::kZerofs;
  const auto improper  = samples.get_list() | Sample::Info::kImproper;
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
  if(std::any_of(samples.get_list().begin(), samples.get_list().end(),
                 [](const Sample* sample) { return sample->blacklist.size() > 0; }))
  {
    std::cout << "Missing numbers (to be blacklisted):\n";
    for(const Sample* sample: samples.get_list())
    {
      if(! sample->blacklist.size()) continue;
      std::cout << "\t* " << sample->name << ": "
                << boost::algorithm::join(sample->blacklist, ", ") << '\n';
    } // samples
    std::cout << LINE;
  } // any blacklist

//--- sum the event counts in the samples that have common ,,parent''
  std::map<std::string, unsigned long long> event_sums;
  for(const Sample* sample: samples.get_list())
  {
    std::cout << "Events before adding: " << sample->nof_events << " " << sample->name << std::endl;
    if(! sample->parentStr.empty())
    {
      if(! event_sums.count(sample->parentStr))
        event_sums[sample->parentStr] = sample->nof_events;
      else
        event_sums[sample->parentStr] += sample->nof_events;
    }
  }
  
  for(auto &ent : event_sums) {
      auto &par = ent.first;
      auto &num = ent.second;
      std::cout << "Parent: " << par << " " << num << std::endl;
  }
  
  std::cout << "List of defined samples not found on disk: " << std::endl;
  for(const Sample* missing_sample: samples.get_missing_list())
  {
    std::cout << "\t* " << missing_sample->name << std::endl;
  }
  std::cout << std::endl;
  
   
  std::cout << "Total event counts:\n";
  for(Sample* sample: samples.get_list())
  {
    if(! sample->parentStr.empty() && sample->category.find("data_obs")==std::string::npos) //don't add for data
      sample->nof_events = event_sums[sample->parentStr];
    std::cout << "\t* " << sample->name << ": "
                        << sample->nof_events << '\n';
  }

  std::cout << "Final statistics:\n";
  std::cout << "\tTotal number of files present:  " << present.size() << '\n';
  std::cout << "\tNumber of broken files:         " << zombies.size() << '\n';
  std::cout << "\tNumber of files w/ 0 file size: " << zerofs.size()  << '\n';
  std::cout << "\tNumber of files that hadn't '" << histo_str << "' "
            << "as their TH1F: " << improper.size() << '\n';
  std::cout << "Total file counts:\n";
  for(const Sample* sample: samples.get_list())
    std::cout << "\t* " << sample->name << ": "
                        << sample->present.size() << '\n';

//--- generate basic python dictionaries out of the results
  if(! output_dir_str.empty() && save_python)
  {
    boost::filesystem::path filename = PYTHON_FILE_P;
    std::ofstream out((output_dir_path / filename).string());
    out << "from collections import OrderedDict as OD\n\n"
      << "samples_2016 = OD()\n\n";
    out << "# file generated with command:\n# "
        << boost::algorithm::join(std::vector<std::string>(argv, argv + argc), " ")
        << "\n\n";

    for(const Sample* sample: samples.get_list())
      out << sample->get_cfg();
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
