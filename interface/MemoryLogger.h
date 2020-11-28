#ifndef tthAnalysis_HiggsToTauTau_MemoryLogger_h
#define tthAnalysis_HiggsToTauTau_MemoryLogger_h

#include <string> // std::string
#include <vector> // std::vector<>
#include <map> // std::map<,>
#include <iosfwd> // std::ostream

/**
 * @author Karl Ehatäht
 */

struct MemoryUnit
{
  unsigned long long vsize;
  unsigned long long rss;

  static std::pair<double, std::string>
  display_memory(int value_in_bytes,
                 bool use_si_units = true);
};

/**
 * @brief Logs VSIZE and RSS of the current process
 *
 * The class records the memory consumption whenever log() is called. Calling log() with a specific argument
 * associates the memory consumption with the argument. For example, if the user wants to know the memory consumption
 * in two different places of the program, they can distinguish them by providing different arguments to log().
 * The argument may be user-defined, but the best practice is to provide a line number and convert it to string like so:
 *
 * MemoryLogger memLogger;
 * // some code
 * memLogger.log(__LINE__);
 * // some more code
 * memLogger.log(__LINE__);
 *
 * The results are printed when the class is destroyed. In order to display first and last N measurements at any given
 * point, either inialize the MemoryLogger class with integer N, or call display_lines().
 *
 * NB! The class affects the measurements if log() is called too frequently.
 *
 */
class MemoryLogger
{
public:
  MemoryLogger(int line_count = 0);
  ~MemoryLogger();

  void
  log(const std::string & key);

  void
  log(int line,
      const std::string & fmt = "Line %d");

  void
  display_lines(int count);

  void
  record_last(bool flag = true);

protected:
  friend bool
  operator<(const MemoryUnit & lhs,
            const MemoryUnit & rhs);

  friend std::ostream &
  operator<<(std::ostream & stream,
             const MemoryUnit & unit);

  friend std::ostream &
  operator<<(std::ostream & stream,
             const MemoryLogger & unit);

  MemoryUnit
  record() const;

  int line_count_;
  bool record_last_;
  std::vector<std::string> keys_;
  std::map<std::string, std::vector<MemoryUnit>> recordings_;
};

#endif // tthAnalysis_HiggsToTauTau_MemoryLogger_h
