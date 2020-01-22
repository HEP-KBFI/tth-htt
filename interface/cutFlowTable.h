#ifndef tthAnalysis_HiggsToTauTau_cutFlowTable_h
#define tthAnalysis_HiggsToTauTau_cutFlowTable_h

#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

#include <string> // std::string
#include <vector> // std::vector<>
#include <map> // std::map<>
#include <iostream> // std::cout, std::endl
#include <ostream> // ostream
#include <cassert> // assert()

/**
 * @brief Auxiliary data structure for printing cut-flow tables at the end of analysis jobs
 */
namespace cutFlowTable_namespace
{
  struct rowType
  {
    rowType(const std::string & cut,
            int idx,
            const std::vector<std::string> & columns = {},
            int selEvents = 0,
            double selEvents_weighted = 0.)
      : idxRow_(idx)
      , selEvents_(selEvents)
      , selEvents_weighted_(selEvents_weighted)
      , cut_(cut)
    {
      for ( size_t idxColumn = 0; idxColumn < columns.size(); ++idxColumn )
      {
        columns_[columns[idxColumn]] = idxColumn;
      }
      assert(columns_.size() >= 1);
      selEvents_.resize(columns_.size());
      selEvents_weighted_.resize(columns_.size());
    }
    ~rowType() {}

    void
    update(const std::string & column, double evtWeight)
    {
      std::map<std::string, size_t>::iterator column_iter = columns_.find(column);
      if ( column_iter != columns_.end() ) 
      {
        size_t idxColumn = column_iter->second;
        assert(idxColumn < selEvents_.size() && idxColumn < selEvents_weighted_.size());
        selEvents_[idxColumn] += 1;
        selEvents_weighted_[idxColumn] += evtWeight; 
      } 
      else 
      {
        throw cmsException(this, __func__, __LINE__)
          << "Invalid column = '" << column << "' !!\n";
      }
    }

    int idxRow_;
    std::map<std::string, size_t> columns_;
    std::vector<int> selEvents_;
    std::vector<double> selEvents_weighted_;
    std::string cut_;
  };

  bool constexpr
  isLowerIdx(const rowType * row1,
             const rowType * row2)
  {
    return row1->idxRow_ < row2->idxRow_;
  }
}

class cutFlowTableType
{
public:
  cutFlowTableType(const std::vector<std::string> & columns = {}, bool isDEBUG = false);
  ~cutFlowTableType();

  void
  update(const std::string & cut,
         double evtWeight = 1.);
  void
  update(const std::string & cut, const std::string & column,
         double evtWeight = 1.);

  void
  print(std::ostream & stream) const;

  friend std::ostream &
  operator<<(std::ostream & os,
             const cutFlowTableType & cutFlowTable);

protected:
  std::vector<std::string> columns_;
  bool isDEBUG_;
  int row_idx_;
  std::map<std::string, cutFlowTable_namespace::rowType *> rows_;
};

#endif // tthAnalysis_HiggsToTauTau_cutFlowTable_h
