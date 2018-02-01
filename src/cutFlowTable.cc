#include "tthAnalysis/HiggsToTauTau/interface/cutFlowTable.h"

#include <iostream> // std::cerr, std::fixed
#include <iomanip> // std::setprecision(), std::setw()
#include <vector> // std::vector<>
#include <algorithm> // std::sort
#include <cassert> // assert()

using namespace cutFlowTable_namespace;

cutFlowTableType::cutFlowTableType(bool isDEBUG)
  : isDEBUG_(isDEBUG)
  , row_idx_(0)
{}
 
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
  if(! rows_.count(cut))
  {
    rows_[cut] = new rowType(cut, row_idx_);
    ++row_idx_;
  }
  rowType * const row = rows_[cut];

  if(isDEBUG_)
  {
    std::cout << "<cutFlowTableType::update>: cut = " << cut << ", evtWeight = " << evtWeight << '\n';
  }
  if(evtWeight != -1.)
  {
    ++row->selEvents_;
    row->selEvents_weighted_ += evtWeight;
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

  for(const rowType * row_ptr: row_ptrs)
  {
    stream << ' ' << row_ptr->cut_ << " = " << row_ptr->selEvents_
           << " (weighted = " << row_ptr->selEvents_weighted_ << ")\n";
  }
}

std::ostream &
operator<<(std::ostream & os,
           const cutFlowTableType & cutFlowTable)
{
  cutFlowTable.print(os);
  return os;
}
