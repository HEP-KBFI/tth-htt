#include "tthAnalysis/HiggsToTauTau/interface/cutFlowTable.h"

#include <vector> // std::vector<>
#include <algorithm> // std::sort

using namespace cutFlowTable_namespace;

cutFlowTableType::cutFlowTableType()
  : row_idx_(0)
{}
 
cutFlowTableType::~cutFlowTableType()
{
  for ( std::map<std::string, rowType*>::iterator it = rows_.begin();
	it != rows_.end(); ++it ) {
    delete it->second;
  }
}

void cutFlowTableType::update(const std::string& cut, double evtWeight)
{
  std::map<std::string, rowType*>::iterator row_iter = rows_.find(cut);
  if ( row_iter != rows_.end() ) {
    rowType* row = row_iter->second;
    ++row->selEvents_;
    row->selEvents_weighted_ += evtWeight;
  } else {
    rowType* row = new rowType();
    row->cut_ = cut;
    row->selEvents_ = 1;
    row->selEvents_weighted_ = evtWeight;
    row->idx_ = row_idx_;
    rows_[cut] = row;
    ++row_idx_;
  }
}

void cutFlowTableType::print(std::ostream& stream) const
{
  std::vector<const rowType*> row_ptrs;
  for(const auto & row: rows_)
  {
    row_ptrs.push_back(row.second);
  }
  std::sort(row_ptrs.begin(), row_ptrs.end(), isLowerIdx);

  for(const rowType* row_ptr: row_ptrs)
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
