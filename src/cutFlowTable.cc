#include "tthAnalysis/HiggsToTauTau/interface/cutFlowTable.h"

#include <iostream> // std::cerr, std::fixed
#include <iomanip> // std::setprecision(), std::setw()
#include <vector> // std::vector<>
#include <algorithm> // std::sort
#include <assert.h> // assert

using namespace cutFlowTable_namespace;

cutFlowTableType::cutFlowTableType(bool isDEBUG)
  : isDEBUG_(isDEBUG)
  , row_idx_(0)
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
  rowType* row = 0;
  if ( row_iter != rows_.end() ) {
    row = row_iter->second;
  } else {
    row = new rowType();
    row->cut_ = cut;
    row->selEvents_ = 0;
    row->selEvents_weighted_ = 0.;
    row->idx_ = row_idx_;
    rows_[cut] = row;
    ++row_idx_;
  }
  assert(row);
  if ( isDEBUG_ ) {
    std::cout << "<cutFlowTableType::update>: cut = " << cut << ", evtWeight = " << evtWeight << std::endl;
  }
  if ( evtWeight != -1. ) {
    ++row->selEvents_;
    row->selEvents_weighted_ += evtWeight;
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
