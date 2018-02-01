#ifndef tthAnalysis_HiggsToTauTau_cutFlowTable_h
#define tthAnalysis_HiggsToTauTau_cutFlowTable_h

#include <string> // std::string
#include <map> // std::map<>
#include <ostream> // ostream

/**
 * @brief Auxiliary data structure for printing cut-flow tables at the end of analysis jobs
 */
namespace cutFlowTable_namespace
{
  struct rowType
  {
    rowType(const std::string & cut,
            int idx,
            int selEvents = 0,
            double selEvents_weighted = 0.)
      : idx_(idx)
      , selEvents_(selEvents)
      , selEvents_weighted_(selEvents_weighted)
      , cut_(cut)
    {}

    int idx_;
    int selEvents_;
    double selEvents_weighted_;
    std::string cut_;
  };

  bool constexpr
  isLowerIdx(const rowType * row1,
             const rowType * row2)
  {
    return row1->idx_ < row2->idx_;
  }
}

class cutFlowTableType
{
public:
  cutFlowTableType(bool isDEBUG = false);
  ~cutFlowTableType();

  void
  update(const std::string & cut,
         double evtWeight = 1.);

  void
  print(std::ostream & stream) const;

  friend std::ostream &
  operator<<(std::ostream & os,
             const cutFlowTableType & cutFlowTable);

protected:
  bool isDEBUG_;
  int row_idx_;
  std::map<std::string, cutFlowTable_namespace::rowType *> rows_;
};

#endif // tthAnalysis_HiggsToTauTau_cutFlowTable_h
