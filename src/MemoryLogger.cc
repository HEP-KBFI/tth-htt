#include "tthAnalysis/HiggsToTauTau/interface/MemoryLogger.h"

#include <iostream> // std::ostream, std::ios::
#include <cassert> // assert()
#include <algorithm> // std::find()
#include <fstream> // std::ifstream
#include <unistd.h> // sysconf(), _SC_PAGESIZE
#include <numeric> // std::accumulate()

#include <TString.h> // Form()

std::pair<double, std::string>
MemoryUnit::display_memory(int value_in_bytes,
                                         bool use_si_units)
{
  const static std::vector<std::string> units_si     = { "B", "KB",  "MB",  "GB"  };
  const static std::vector<std::string> units_binary = { "B", "KiB", "MiB", "GiB" };
  double converted_value = value_in_bytes;
  const double division_unit = use_si_units ? 1000. : 1024;
  const std::vector<std::string> & units = use_si_units ? units_si : units_binary;
  unsigned int order = 0;
  while(converted_value > division_unit && order < (units.size() - 1))
  {
    ++order;
    converted_value /= division_unit;
  }
  return std::make_pair(converted_value, units.at(order));
}

MemoryLogger::MemoryLogger(int line_count)
  : line_count_(line_count)
{}

MemoryLogger::~MemoryLogger()
{
  std::cout << *this << '\n';
}

void
MemoryLogger::log(const std::string & key)
{
  if(std::find(keys_.cbegin(), keys_.cend(), key) == keys_.cend())
  {
    assert(! recordings_.count(key));
    keys_.push_back(key);
  }
  recordings_[key].push_back(record());
}

void
MemoryLogger::log(int line,
                  const std::string & fmt)
{
  return this->log(Form(fmt.data(), line));
}

void
MemoryLogger::display_lines(int count)
{
  line_count_ = count;
}

MemoryUnit
MemoryLogger::record() const
{
  unsigned long long vsize = 0;
  unsigned long long rss = 0;
  // see http://man7.org/linux/man-pages/man5/proc.5.html
  std::ifstream buffer("/proc/self/statm");
  buffer >> vsize >> rss;
  // sizes are given in number of pages -> multiply by the page size in bytes
  const long page_size = sysconf(_SC_PAGESIZE);
  vsize *= page_size;
  rss *= page_size;
  return { vsize, rss };
}

bool
operator<(const MemoryUnit & lhs,
          const MemoryUnit & rhs)
{
  return lhs.vsize < rhs.vsize;
}

std::ostream &
operator<<(std::ostream & stream,
           const MemoryUnit & unit)
{
  const auto vsize_display = MemoryUnit::display_memory(unit.vsize);
  const auto rss_display = MemoryUnit::display_memory(unit.rss);
  std::ios_base::fmtflags stream_flags(stream.flags());
  stream.setf(std::ios::fixed);
  stream.precision(2);
  stream
    << "VSIZE = " << vsize_display.first << ' ' << vsize_display.second << " , "
       "RSS = "   << rss_display.first   << ' ' << rss_display.second
  ;
  stream.flags(stream_flags);
  return stream;
}

std::ostream &
operator<<(std::ostream & stream,
           const MemoryLogger & logger)
{
  if(! logger.keys_.empty())
  {
    stream << std::string(80, '=') << '\n';
  }
  for(const std::string & key: logger.keys_)
  {
    const auto & recordings = logger.recordings_.at(key);
    assert(! recordings.empty());

    const auto max = std::max_element(recordings.cbegin(), recordings.cend());

    unsigned long long vsize_sum = std::accumulate(
      recordings.cbegin(), recordings.cend(), 0ULL,
      [](unsigned long long sum, const MemoryUnit & unit) -> unsigned long long { return sum + unit.vsize; }
    );
    unsigned long long rss_sum = std::accumulate(
      recordings.cbegin(), recordings.cend(), 0ULL,
      [](unsigned long long sum, const MemoryUnit & unit) -> unsigned long long { return sum + unit.rss; }
    );
    std::size_t recordings_sz = recordings.size();
    const unsigned long long vsize_avg = static_cast<unsigned long long>(vsize_sum / recordings_sz);
    const unsigned long long rss_avg = static_cast<unsigned long long>(rss_sum / recordings_sz);
    const MemoryUnit unit_avg{ vsize_avg, rss_avg };

    stream << "Memory consumption at '" << key << "' -> "
              "count: " << recordings_sz << " ; "
              "maximum: " << *max << " ; "
              "average: " << unit_avg << '\n'
    ;
    const unsigned int line_count_unsigned = logger.line_count_ > 0 ? static_cast<unsigned int>(logger.line_count_) : 0u;
    if(logger.line_count_ < 0 || (logger.line_count_ > 0 && recordings_sz > 1))
    {
      stream << "  " << std::string(80, '-') << '\n';
      if(logger.line_count_ < 0 || 2 * line_count_unsigned >= recordings_sz)
      {
        // display all
        for(std::size_t counter = 0; counter < recordings_sz; ++counter)
        {
          stream << "  #" << counter << ' ' << recordings.at(counter) << '\n';
        }
      }
      else
      {
        // display first N
        for(std::size_t counter = 0; counter < line_count_unsigned; ++counter)
        {
          stream << "  #" << counter << ' ' << recordings.at(counter) << '\n';
        }
        stream << "  ...\n";
        // display last N
        for(std::size_t counter = (recordings_sz - line_count_unsigned); counter < recordings_sz; ++counter)
        {
          stream << "  #" << counter << ' ' << recordings.at(counter) << '\n';
        }
      }
      stream << "  " << std::string(80, '-') << '\n';
    }
  }
  if(! logger.keys_.empty())
  {
    stream << std::string(80, '=') << '\n';
  }
  return stream;
}
