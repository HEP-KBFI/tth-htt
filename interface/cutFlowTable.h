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
    std::string cut_;
    int selEvents_;
    double selEvents_weighted_;
    int idx_;
  };

  bool isLowerIdx(const rowType* row1, const rowType* row2)
  {
    return (row1->idx_ < row2->idx_);
  }
}

class cutFlowTableType
{
 public:
  cutFlowTableType();
  ~cutFlowTableType();

  void update(const std::string& cut, double evtWeight = 1.);

  void print(std::ostream& stream) const;

  friend std::ostream &
  operator<<(std::ostream & os,
             const cutFlowTableType & cutFlowTable);

 protected:
  std::map<std::string, cutFlowTable_namespace::rowType*> rows_;
  int row_idx_;
};

#endif // tthAnalysis_HiggsToTauTau_cutFlowTable_h
