#include "tthAnalysis/HiggsToTauTau/interface/cutFlowTable.h"

#include <iostream> // std::cerr, std::fixed
#include <iomanip> // std::setprecision(), std::setw()
#include <sstream> // std::ostringstream
#include <vector> // std::vector<>
#include <algorithm> // std::sort

using namespace cutFlowTable_namespace;

cutFlowTableType::cutFlowTableType(const std::vector<std::string> & columns, bool isDEBUG)
  : columns_(columns)
  , isDEBUG_(isDEBUG)
  , row_idx_(0)
{
  if (columns_.size() == 0)
  { 
    columns_.push_back("");
  }
}
 
cutFlowTableType::~cutFlowTableType()
{
  for(auto & kv: rows_)
  {
    delete kv.second;
  }
}

void
cutFlowTableType::update(const std::string & cut,
                         double evtWeight)
{
  this->update(cut, "", evtWeight);
}

void
cutFlowTableType::update(const std::string & cut, const std::string & column,
                         double evtWeight)
{
  if(! rows_.count(cut))
  {
    rows_[cut] = new rowType(cut, row_idx_, columns_);
    ++row_idx_;
  }
  rowType * const row = rows_[cut];

  if(isDEBUG_)
  {
    std::cout << "<cutFlowTableType::update>: cut = " << cut << ",";
    if ( column != "" ) std::cout << " (column = " << column << ")";
    std::cout << " evtWeight = " << evtWeight << '\n';
  }
  if(evtWeight != -1.)
  {
    row->update(column, evtWeight);
  }
}

void
cutFlowTableType::print(std::ostream & stream) const
{
  std::vector<const rowType*> row_ptrs;
  for(const auto & row: rows_)
  {
    row_ptrs.push_back(row.second);
  }
  std::sort(row_ptrs.begin(), row_ptrs.end(), cutFlowTable_namespace::isLowerIdx);

  size_t max_cut_length = 0;
  for(const rowType * row_ptr: row_ptrs)
  {
    if ( row_ptr->cut_.length() > max_cut_length ) max_cut_length = row_ptr->cut_.length();
  }

  if (columns_.size() > 0 && columns_[0] != "")
  {
    stream << " " << std::left << std::setw(max_cut_length + 1) << " ";
    for(auto column : columns_)
    {
      stream << std::left << std::setw(8) << "" << std::left << std::setw(24) << column;
    }
    stream << "\n";
  }
  for(const rowType * row_ptr: row_ptrs)
  {
    stream << " " << std::left << std::setw(max_cut_length + 1) << row_ptr->cut_;
    for(auto column : columns_)
    {
      std::map<std::string, size_t>::const_iterator idxColumn_iter = row_ptr->columns_.find(column);
      assert(idxColumn_iter != row_ptr->columns_.end());
      size_t idxColumn = idxColumn_iter->second;
      std::ostringstream evtYield;
      evtYield << std::right << std::setw(10) << row_ptr->selEvents_[idxColumn];
      evtYield << std::left << " (weighted = " << row_ptr->selEvents_weighted_[idxColumn] << ")";
      stream << std::left << std::setw(32) << evtYield.str();
    }
    stream << "\n";
  }
}

std::ostream &
operator<<(std::ostream & os,
           const cutFlowTableType & cutFlowTable)
{
  cutFlowTable.print(os);
  return os;
}
