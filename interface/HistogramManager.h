#ifndef HISTOGRAMMANAGER_H
#define HISTOGRAMMANAGER_H

#include <string> // std::string
#include <map> // std::map<>
#include <vector> // std::vector<>
#include <utility> // std::pair<>
#include <type_traits> // std::enable_if<>, std::is_enum<>
#include <iostream> // std::cerr

#include <Rtypes.h> // Double_t, Int_t, kTRUE
#include <TH1D.h> // TH1D
#include <TFile.h> // TFile
#include <TCanvas.h> // TCanvas

/**
 * @brief Joins strings with a delimiter
 * @param v     Vector containing the strings, e.g. {"a", "b", "c"}
 * @param delim Delimiter separating the strings,
 *              by default it's ";"
 * @return      A joined string, e.g. "a;b;c"
 */
std::string
join_strings(const std::vector<std::string> & v,
             const std::string & delim = ";")
{
  return std::accumulate
    (
      v.begin(),
      v.end(),
      std::string {},
      [&delim] (const std::string & lhs,
                const std::string & rhs)
      {
        return lhs.empty() ? rhs : lhs + delim + rhs;
      }
    );
}

/**
 * @brief A struct holding all necessary information to construct
 *        a ROOT histogram:
 *           - histogram name and title (the same)
 *           - number of bins
 *           - minimum value on the x axis
 *           - maximum value on the x axis
 *           - label on the x axis (by default -- name of the histogram)
 *           - label on the y axis (by default -- number of events)
 */
struct HistogramVariable
{
public:
  HistogramVariable() = default;
  ~HistogramVariable() = default;
  /**
   * @brief Constructs the class with the following information.
   *        Default labels on the x axis on the y axis are used here
   *        (name of the histogram and "number of events", respectively).
   * @param name  Name (and title) of the histogram.
   * @param nbins Number of bins.
   * @param xmin  Minimum value on the x axis.
   * @param xmax  Maximum value on the x axis.
   */
  HistogramVariable(const std::string & name,
                    Int_t nbins,
                    Double_t xmin,
                    Double_t xmax)
    : name(name)
    , nbins(nbins)
    , xmin(xmin)
    , xmax(xmax)
    , xlabel(name)
    , ylabel("nevents")
  {}
  /**
   * @brief Constructs the class with the following information.
   * @param name   Name (and title) of the histogram.
   * @param nbins  Number of bins.
   * @param xmin   Minimum value on the x axis.
   * @param xmax   Maximum value on the x axis.
   * @param xlabel Label on the x axis.
   * @param ylabel Label on the y axis.
   */
  HistogramVariable(const std::string & name,
                    Int_t nbins,
                    Double_t xmin,
                    Double_t xmax,
                    const std::string & xlabel,
                    const std::string & ylabel)
    : name(name)
    , nbins(nbins)
    , xmin(xmin)
    , xmax(xmax)
    , xlabel(xlabel)
    , ylabel(ylabel)
  {}
  const std::string name;
  const Int_t nbins;
  const Double_t xmin;
  const Double_t xmax;
  const std::string xlabel;
  const std::string ylabel;
};

/**
 * @brief A class containing all histograms for a set of variables
 */
class HistogramCollection
{
public:
  /**
    * @brief Do not use; only there for to use it as a map value
    */
  HistogramCollection() = default;
  /**
   * @brief Initializes the histograms with a vector, where each element
   *        specifies a variable name, number of bins and the endpoints
   *        for each histogram.
   * @param The vector containing the above information. The order of its
   *        elements is really important, as invoking fill(Double_t)
   *        would fill only the histogram that matches to the first element
   *        of the vector.
   */
  HistogramCollection(const std::vector<HistogramVariable> & _variables)
  {
    for(const auto & var: _variables)
    {
      const std::string & var_name = var.name;
      variables.push_back(var_name);
      TH1D h
        (
          var_name.c_str(),
          var_name.c_str(),
          var.nbins,
          var.xmin,
          var.xmax
        );
      h.Sumw2(kTRUE);
      h.GetXaxis()->SetTitle(var.xlabel.c_str());
      h.GetYaxis()->SetTitle(var.ylabel.c_str());
      histograms[var_name] = h;
    }
  }
  ~HistogramCollection() = default;

  /**
   * @brief Modifies the histogram name and title by adding
   *        a prefix and a suffix to already existing name.
   *        The variable name that corresponds to some histogram
   *        and is used to access it remains unchanged.
   * @param prefix The prefix.
   * @param sufix  The sufix.
   */
  void set_name_title(const std::string & prefix,
                      const std::string & sufix)
  {
    for(const std::string & var_name: variables)
    {
      const std::string new_name = join_strings
        (
          {prefix, var_name, sufix}, "_"
        );
      histograms[var_name].SetNameTitle
        (
          new_name.c_str(),
          new_name.c_str()
        );
    }
  }

  /**
   * @brief Fills the histogram corresponding to the given variable.
   * @param var_name The variable name.
   * @param val      Its value.
   */
  void fill(const std::string var_name,
            Double_t val)
  {
    histograms[var_name].Fill(val);
  }
  /**
   * @brief Fills the histogram corresponding to the first element
   *        in the vector that was used to initialize this class.
   *        Used as the base case in variadic version of this function.
   * @param The value to fill it with.
   */
  void fill(Double_t val)
  {
    histograms[variables[pos]].Fill(val);
    pos = 0;
  }
  /**
   * @brief Fills all histograms in the same order as the vector that
   *        was used to initialize this class.
   *        E.g. if the vector was something like {"pt, "eta", ...}
   *        then the first argument fills "pt" histogram, the second
   *        argument fills "eta" histogram and so on...
   * @param val  The value to fill the first histogram with.
   * @param args The rest of the values (unpacked).
   */
  template <typename... Args>
  void fill(Double_t val,
            Args... args)
  {
    const std::size_t nof_arguments = sizeof...(args) + 1;
    if(nof_arguments > variables.size() - pos)
    {
      std::cerr << "Too many arguments to fill the histogram: "
                << nof_arguments
                << "\nResetting.\n";
      pos = 0;
    }
    histograms[variables[pos++]].Fill(val);
    fill(args...);
  }

  /**
   * @brief Returns a histogram by its variable name.
   * @param var_name The variable name.
   * @return         The histogram corresponding to the variable name.
   */
  TH1D &
  get_histogram(const std::string & var_name)
  {
    return histograms[var_name];
  }

private:
  std::map<std::string, TH1D> histograms;
  std::vector<std::string> variables;
  std::size_t pos = 0;
};

/**
 * @brief A class that manages individual HistogramCollection instances.
 *        The histograms are stored in two levels:
 *          - Channel, which holds all histograms corresponding to
 *            a particular channel
 *          - Cutpoint, which holds all histograms corresponding to
 *            a specific point in code where the histogram shoudl be filled.
 *        An examples: say we want histograms for "ee" and "mumu" channel
 *        and we want to fill them in the beginning and in the end of
 *        the program lifetime. A way to go is to construct enums, pass
 *        these enums a template arguments, preconstruct enum-to-string map
 *        and pass these in the member functions. With this the order of
 *        channels and cut points are preserved in the same way as they
 *        are defined. Using strings as map keys is shortsighted, as
 *        the order is not preserved.
 */
template <typename Channel,
          typename Cutpoint,
          typename = typename std::enable_if<
              std::is_enum<Channel>::value,
              Channel
            >::type,
          typename = typename std::enable_if<
              std::is_enum<Cutpoint>::value,
              Cutpoint
            >::type
         >
class HistogramManager
{
public:
  HistogramManager() = default;
  ~HistogramManager() = default;

  /**
   * @brief Add channel enum and the corresponding string;
   *        the latter used in naming individual histograms.
   *        The function is used as the base case for the variadic version.
   * @param channel The enum-string pair.
   */
  void add_channel(const std::pair<Channel,
                                   std::string> & channel)
  {
    channels.emplace(channel);
  }
  /**
   * @brief Add channel enum and the corresponding string;
   *        the latter used in naming individual histograms.
   *        The function takes variable number of such pairs as an argument.
   * @param channel The first enum-string pair.
   * @param args    The rest of the pairs (unpacked).
   */
  template <typename... Args>
  void add_channel(const std::pair<Channel,
                                   std::string> & channel,
                   Args... args)
  {
    channels.emplace(channel);
    add_channel(args...);
  }
  /**
   * @brief Add a map of channel enums and the corresponding strings;
   *        the latter used in naming individual histograms.
   * @param channel_map The map containing enum-string pairs.
   */
  void add_channel(const std::map<Channel,
                                  std::string> & channel_map)
  {
    channels.insert(channel_map.begin(), channel_map.end());
  }

  /**
   * @brief Add cut points (i.e. stages where the histogram should be filled)
   *        and the corresponding string, which is used in naming individual
   *        histograms.
   *        This is a function object, i.e. the user can stack the function
   *        calls sequentially.
   * @param cut_point The cut point-string pair.
   * @return Reference to this instance.
   */
  HistogramManager & add_cutpoint(const std::pair<Cutpoint,
                                  std::string> & cut_point)
  {
    cut_points.emplace(cut_point);
    return * this;
  }
  /**
   * @brief Add a map of cut points (i.e. stages where the histogram should be
   *        filled) and the corresponding string, which is used in naming
   *        individual histograms.
   * @param cut_point_map The map containing cut point-string pairs.
   */
  void add_cutpoint(const std::map<Cutpoint,
                                   std::string> & cut_point_map)
  {
    cut_points.insert(cut_point_map.begin(), cut_point_map.end());
  }

  /**
   * @brief Adds the information about the given variable for which
   *        the histograms should be filled. This information is used in
   *        initializing HistogramCollection instances.
   *        This is a function object, i.e. the user can stack the function
   *        call sequentially.
   * @param variable The variable instance containing all information to
   *                 construct a histogram (name, axis labels, x axis limits,
   *                 number of bins).
   * @return Reference to this instance.
   */
  HistogramManager & add_variable(HistogramVariable variable)
  {
    variables.push_back(variable);
    return * this;
  }

  /**
   * @brief Initialize all histograms.
   *        Constructs HistogramCollection instances and sets them
   *        a proper name and title.
   */
  void initialize()
  {
    for(auto & ch: channels)
    {
      for(auto & cp: cut_points)
      {
        HistogramCollection hc(variables);
        hc.set_name_title(ch.second, cp.second);
        histograms[ch.first][cp.first] = hc;
      }
    }
  }

  /**
   * @brief The subscript operator.
   *        It's here for syntactic sugar only. Instead of filling
   *        particular histogram with a function, it's more convenient
   *        to access the underlying map via subscript operator.
   *        The expected usage would be along the lines of
   *
   *        histogram_manager_instance[channel_enum][cutpoint_enum].fill(...)
   *
   * @param ch The channel enum key used to access the corresponding
   *           cutpoint map.
   * @return Reference to the cutpoint map.
   */
  std::map<Cutpoint, HistogramCollection> &
  operator[] (Channel ch)
  {
    return histograms[ch];
  }

  /**
   * @brief Writes all histograms to a single file.
   * @param file_path The path where to save the histograms.
   */
  void write(const std::string & file_path)
  {
    TFile f(file_path.c_str(), "recreate");
    for(auto & ch: channels)
    {
      for(auto & var: variables)
      {
        for(auto & cp: cut_points)
        {
          TCanvas c;
          TH1D & h = histograms[ch.first][cp.first].get_histogram(var.name);
          h.Draw("hist e");
          c.Update();
          h.Write();
        }
      }
    }
    f.Close();
  }

private:
  std::map<Channel, std::map<Cutpoint, HistogramCollection>> histograms;

  std::map<Channel, std::string> channels;
  std::map<Cutpoint, std::string> cut_points;
  std::vector<HistogramVariable> variables;
};

#endif // HISTOGRAMMANAGER_H
