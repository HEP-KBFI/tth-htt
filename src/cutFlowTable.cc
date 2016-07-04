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

void cutFlowTableType::print(std::ostream& stream)
{
  std::vector<const rowType*> row_ptrs;
  for ( std::map<std::string, rowType*>::const_iterator row = rows_.begin();
	row != rows_.end(); ++row ) {
    row_ptrs.push_back(row->second);
  }
  std::sort(row_ptrs.begin(), row_ptrs.end(), isLowerIdx);

  for ( std::vector<const rowType*>::const_iterator row_ptr = row_ptrs.begin();
	row_ptr != row_ptrs.end(); ++row_ptr ) {
    stream << " " << (*row_ptr)->cut_ << " = " << (*row_ptr)->selEvents_ << " (weighted = " << (*row_ptr)->selEvents_weighted_ << ")" << std::endl;
  }
}
