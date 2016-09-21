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
#include <TTree.h> // TTree
#include <TROOT.h> // gROOT
#include <TError.h> // kError
#include <TString.h> // Form()

#define IMPROPER_FILE_C -1
#define ZOMBIE_FILE_C   -2

#define IMPROPER_FILE_P boost::filesystem::path("improper_files.txt")
#define ZOMBIE_FILE_P   boost::filesystem::path("broken_files.txt")
#define ZEROFS_FILE_P   boost::filesystem::path("zerofs_files.txt")
#define PYTHON_FILE_P   boost::filesystem::path("samples.py")

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

   check_broken -p /hdfs/local/karl/FinalNtuples -t tree --output=/home/karl/sandbox -P -z -v
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
             const std::string & tree)
{
  TFile f(path.c_str());
  long int ret_val = ZOMBIE_FILE_C;
  if(! f.IsZombie())
  {
    if(f.GetListOfKeys() -> Contains(tree.c_str()))
    {
      TTree * t = static_cast<TTree *>(f.Get("tree"));
      ret_val = t -> GetEntries();
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
      { "sample_name",  name                                    },
      { "max_nr",       std::to_string(max_nr)                  },
      { "nof_events",   std::to_string(nof_events)              },
      { "super_parent", fileSuperParent                         },
      { "blacklist",    boost::algorithm::join(blacklist, ", ") }
    };
    auto fmt_fun = [&env](const boost::xpressive::smatch & what) -> const std::string &
    {
      return env.at(what[1].str());
    };
    const std::string input =
      "samples[\"$(sample_name)\"] = OD([\n"
      "  (\"type\",                  \"mc\"),\n"
      "  (\"sample_category\",       \"\"),\n"
      "  (\"process_name_specific\", \"\"),\n"
      "  (\"nof_files\",             $(max_nr)),\n"
      "  (\"nof_events\",            $(nof_events)),\n"
      "  (\"use_it\",                True),\n"
      "  (\"xsection\",              0.),\n"
      "  (\"triggers\",              [ \"1e\", \"2e\", \"1mu\", \"2mu\", \"1e1mu\" ]),\n"
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
  std::string pathStr;
  std::string parentStr;
  std::string fileSuperParent; ///< NB!! Its only a string not a vector

  std::vstring zombies, zerofs, improper, present, blacklist;

  unsigned max_nr;
  unsigned long long nof_events;
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

//--- parse command line arguments
  std::string target_str, tree_str, output_dir_str;
  bool save_zerofs, save_improper, save_python, verbose;

  try
  {
    boost::program_options::options_description desc("Allowed options");
    desc.add_options()
      ("help,h",     "produce help message")
      ("path,p",     boost::program_options::value<std::string>(&target_str) -> required(),
                     "full path to the directory to scan")
      ("tree,t",     boost::program_options::value<std::string>(&tree_str) -> default_value("tree"),
                     "expected TTree name")
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
            << "TTree name: "           << tree_str << '\n'
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
    if(verbose) std::cout << ">> Looping over: " << sample.pathStr << "\n";
    for(const boost::filesystem::directory_entry & it: recursive_directory_range(sample.path))
    {
      const boost::filesystem::path file = it.path();
      const std::string file_str = file.string();
//--- if we're dealing with a valid root file
      if(boost::filesystem::is_regular_file(file) &&
         boost::filesystem::extension(file) == ".root")
      {
        if(verbose) std::cout << "Checking: " << file_str << '\n';
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
        const long int nof_events = check_broken(file_str, tree_str);
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
  for(Sample & sample: samples)
    sample.check_completion();
  const auto present   = samples | Sample::Info::kPresent;
  const auto zombies   = samples | Sample::Info::kZombie;
  const auto zerofs    = samples | Sample::Info::kZerofs;
  const auto improper  = samples | Sample::Info::kImproper;

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
    std::cout << "List of files which didn't have '" << tree_str << "' "
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
  std::cout << "\tNumber of files that hadn't '" << tree_str << "' "
            << "as their TTree: " << improper.size() << '\n';
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
