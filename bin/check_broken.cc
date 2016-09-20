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
#include <algorithm> // std::sort(), std::set_difference(), std::copy(), ...
  // ... std::accumulate()
#include <set> // std::set<>
#include <iterator> // std::inserter(), std::ostream_iterator<>

#include <boost/filesystem.hpp> // boost::filesystem::
#include <boost/program_options.hpp> // boost::program_options::
#include <boost/regex.hpp> // boost::regex::
#include <boost/lexical_cast.hpp> // boost::lexical_cast<>()
#include <boost/iterator/counting_iterator.hpp> // boost::counting_iterator<>

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
    -v [ --verbose ]            log every file and folder

 * Example usage:

   check_broken -p /hdfs/local/karl/FinalNtuples -t tree --output=/home/karl/sandbox -o -v
 */

namespace std
{
  using vstring = std::vector<std::string>;
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

/**
 * @brief Not-so-elegant check to see whether a given path is
 *        a subpath of some (presumably) parent folder
 * @param test_path   The path to check
 * @param parent_path The parent folder
 * @return
 */
bool
is_subdir(const boost::filesystem::path & test_path,
          const boost::filesystem::path & parent_path)
{
  return test_path.string().find(parent_path.string()) != std::string::npos;
}

int
main(int argc,
     char * argv[])
{
  setenv("TZ", "/etc/localtime", 1); // needed by std::chrono::
  gROOT -> ProcessLine(Form("gErrorIgnoreLevel = %d;", kBreak));

//--- parse command line arguments
  std::string target_str, tree_str, output_dir_str;
  bool save_zerofs, save_improper, verbose;

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

//--- quick printout of the chosen options
  std::cout << "Directory to analyze: " << target_str << '\n'
            << "TTree name: "           << tree_str << '\n'
            << "Verbose printout: "     << std::boolalpha << verbose << '\n';
  if(! output_dir_path.empty())
    std::cout << "Output directory: " << output_dir_path.string() << '\n';
  std::cout << LINE;

//--- set up the regex
  const boost::regex re("\\d+");

//--- start the clock
  const std::chrono::high_resolution_clock::time_point start_t =
      std::chrono::high_resolution_clock::now();

//--- create a list of immediate subdirectories of a given directory
  const boost::filesystem::path target_path(target_str);
  boost::filesystem::directory_iterator target_it(target_path);
  std::vector<boost::filesystem::path> immediate_subdirs;
  std::map<boost::filesystem::path, std::vector<boost::filesystem::path>>
    immediate_subsubdirs;
  for(const boost::filesystem::path & p: target_it)
    if(boost::filesystem::is_directory(p))
    {
      immediate_subdirs.push_back(p);
      if(verbose) std::cout << "Found sample directory: " << p.string() << '\n';
      boost::filesystem::directory_iterator sub_it(p);
      for(const boost::filesystem::path & sub_p: sub_it)
        if(boost::filesystem::is_directory(sub_p))
          immediate_subsubdirs[p].push_back(sub_p);
    }
  if(verbose) std::cout << LINE;

//--- loop over the list of immediate subdirectories recursively
  std::vstring zombie_files, zerofs_files, improper_files;
  std::map<std::string, unsigned long long> event_counter;
  std::map<std::string, std::vector<unsigned>> present_counter;

  for(const boost::filesystem::path & dir_path: immediate_subdirs)
  {
    const std::string dir = dir_path.string();
    const std::string sample_name = dir_path.filename().string();
    unsigned long long nof_total_events = 0;
    if(verbose) std::cout << ">> Looping over: " << dir << "\n";
    for(const boost::filesystem::directory_entry & it: recursive_directory_range(dir))
    {
      const boost::filesystem::path file = it.path();
      const std::string file_str = file.string();
//--- if we're dealing with a valid root file
      if(boost::filesystem::is_regular_file(file) &&
         boost::filesystem::extension(file) == ".root")
      {
        const std::string sample_name_actual = [&]
        {
//--- a given ,,immediate'' subdirectory might include multiple directories for which
//--- we have to count the number of files separately
//--- so basically we decide in which subdirectory a given file belongs to
          const auto & immediate_subsubdir_list = immediate_subsubdirs[dir];
          if(immediate_subsubdir_list.size() == 1)
            return sample_name;
          for(const auto & subsubdir: immediate_subsubdir_list)
            if(is_subdir(file, subsubdir))
              return subsubdir.filename().string();
          // we should never reach here
          throw std::runtime_error("Something's seriously wrong here");
        }();
        if(verbose) std::cout << "Checking: " << file_str << '\n';
//--- parse the tree number
        const std::string file_filename = file.filename().string();
        boost::sregex_iterator it(file_filename.begin(), file_filename.end(), re);
        decltype(it) end;
        std::vstring matches;
        for(; it != end; ++it) matches.push_back(it -> str());
        if(matches.size() != 1) throw std::runtime_error("Something's wrong");
        const unsigned tree_nr = boost::lexical_cast<unsigned>(matches[0]);
        present_counter[sample_name_actual].push_back(tree_nr);
//--- read the file size before checking the zombiness
        const boost::uintmax_t file_size = boost::filesystem::file_size(file);
        if(! file_size)
        {
          zerofs_files.push_back(file_str);
//--- don't even bother checking whether the file is zombie or not
          continue;
        }
        const long int nof_events = check_broken(file_str, tree_str);
        if     (nof_events > 0)                nof_total_events += nof_events;
        else if(nof_events == ZOMBIE_FILE_C)   zombie_files.push_back(file_str);
        else if(nof_events == IMPROPER_FILE_C) improper_files.push_back(file_str);
      } // is root file
    } // recursive loop
    event_counter[sample_name] = nof_total_events;
  } // immediate subdirectory loop
  if(verbose) std::cout << LINE;

//--- print the results; save them to a file?
  if(zombie_files.size())
  {
    std::cout << "List of broken files:\n";
    for(const std::string & zombie: zombie_files)
      std::cout << zombie << '\n';
    std::cout << LINE;
  }
  if(zerofs_files.size())
  {
    std::cout << "List of files with zero size:\n";
    for(const std::string & zerofs: zerofs_files)
      std::cout << zerofs << '\n';
    std::cout << LINE;
  }
  if(improper_files.size())
  {
    std::cout << "List of files which didn't have '" << tree_str << "' "
              << "as immediate key in the root file:\n";
    for(const std::string & improper: improper_files)
      std::cout << improper << '\n';
    std::cout << LINE;
  }
//--- do some cross-checks with the tree numbers
//--- for example, if a given sample has files: tree_1.root, tree_2.root, ..., tree_N.root
//--- we expect no missing tree files between numbers 1 and N
//--- from what follows we check for ,,missing'' root files that proves to be useful
//--- in blacklisting missing entries in the python configuration file
  std::map<std::string, unsigned> file_counter_map;
  for(auto & kv: present_counter)
  {
    const std::string sample_name = kv.first;
    std::vector<unsigned> & nrs = kv.second;
    std::sort(nrs.begin(), nrs.end());
    const unsigned nof_files = nrs.size();
    if(nof_files)
    {
      const unsigned N = std::max(nof_files, nrs[nof_files - 1]);
      file_counter_map[sample_name] = N;
      std::set<unsigned> N_diff_set;
      std::set<unsigned> nrs_set(nrs.begin(), nrs.end());
      std::set_difference(
        boost::counting_iterator<unsigned>(1), boost::counting_iterator<unsigned>(N),
        nrs_set.begin(), nrs_set.end(), std::inserter(N_diff_set, N_diff_set.end())
      );
      if(N_diff_set.size())
      {
        const std::vector<unsigned> N_diff(N_diff_set.begin(), N_diff_set.end());
        std::cout << "MISSING NUMBERS FOR SAMPLE '" << sample_name << "': ";
        std::ostream_iterator<unsigned> out_it(std::cout, ", ");
        std::copy(N_diff.begin(), N_diff.end() - 1, out_it);
        std::cout << N_diff[N_diff.size() - 1] << '\n';
      }
    } // if there are any root files
  } // present_counter
  std::cout << "Total event counts:\n";
  for(const auto & kv: event_counter)
    std::cout << kv.first << ": " << kv.second << '\n';
  const unsigned file_counter = std::accumulate(
    present_counter.begin(), present_counter.end(), 0,
    [&](unsigned lhs,
        typename decltype(present_counter)::value_type rhs)
    {
      return lhs + rhs.second.size();
    }
  );
  std::cout << "Final statistics:\n";
  std::cout << "\tTotal number of files: " << file_counter << '\n';
  std::cout << "\tNumber of broken files: " << zombie_files.size() << '\n';
  std::cout << "\tNumber of files w/ 0 file size: " << zerofs_files.size() << '\n';
  std::cout << "\tNumber of files that hadn't '" << tree_str << "' "
            << "as their TTree: " << improper_files.size() << '\n';
  std::cout << "Total file counts:\n";
  for(const auto & kv: file_counter_map)
    std::cout << kv.first << ": " << kv.second << '\n';

//--- optional: dump the results to files
  if(! output_dir_str.empty())
  {
    if(zombie_files.size())
    {
      const std::string zombie_path = (output_dir_path / ZOMBIE_FILE_P).string();
      std::ofstream zombie_outfile(zombie_path);
      for(const std::string & zombie: zombie_files)
        zombie_outfile << zombie << '\n';
      std::cout << "Wrote file: '" << zombie_path << "'\n";
    }
    if(save_improper && improper_files.size())
    {
      const std::string improper_path = (output_dir_path / IMPROPER_FILE_P).string();
      std::ofstream improper_outfile(improper_path);
      for(const std::string & improper: improper_files)
        improper_outfile << improper << '\n';
      std::cout << "Wrote file: '" << improper_path << "'\n";
    }
    if(save_zerofs && zerofs_files.size())
    {
      const std::string zerofs_path = (output_dir_path / ZEROFS_FILE_P).string();
      std::ofstream zerofs_outfile(zerofs_path);
      for(const std::string & zerofs: zerofs_files)
        zerofs_outfile << zerofs << '\n';
      std::cout << "Wrote file: '" << zerofs_path << "'\n";
    }
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
