#include "tthAnalysis/HiggsToTauTau/interface/RecoVertexReader.h"

#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h"             // cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/BranchAddressInitializer.h" // BranchAddressInitializer, TTree, Form()

std::map<std::string, int> RecoVertexReader::numInstances_;
std::map<std::string, RecoVertexReader *> RecoVertexReader::instances_;

RecoVertexReader::RecoVertexReader()
  : RecoVertexReader("PV")
{}

RecoVertexReader::RecoVertexReader(const std::string & branchName)
  : branchName_(branchName)
{
  setBranchNames();
}

RecoVertexReader::~RecoVertexReader()
{
  --numInstances_[branchName_];
  assert(numInstances_[branchName_] >= 0);
  if(numInstances_[branchName_] == 0)
  {
    RecoVertexReader * const gInstance = instances_[branchName_];
    assert(gInstance);
    instances_[branchName_] = nullptr;
  }
}

void
RecoVertexReader::setBranchNames()
{
  if(numInstances_[branchName_] == 0)
  {
    branchName_x_ = Form("%s_%s", branchName_.data(), "x");
    branchName_y_ = Form("%s_%s", branchName_.data(), "y");
    branchName_z_ = Form("%s_%s", branchName_.data(), "z");
    branchName_ndof_ = Form("%s_%s", branchName_.data(), "ndof");
    branchName_chi2_ = Form("%s_%s", branchName_.data(), "chi2");
    branchName_score_ = Form("%s_%s", branchName_.data(), "score");
    branchName_npvs_ = Form("%s_%s", branchName_.data(), "npvs");
    branchName_npvsGood_ = Form("%s_%s", branchName_.data(), "npvsGood");
    instances_[branchName_] = this;
  }
  ++numInstances_[branchName_];
}

void
RecoVertexReader::setBranchAddresses(TTree * tree)
{
  if(instances_[branchName_] == this)
  {
    BranchAddressInitializer bai(tree);
    bai.setBranchAddress(vertex_x_, branchName_x_);
    bai.setBranchAddress(vertex_y_, branchName_y_);
    bai.setBranchAddress(vertex_z_, branchName_z_);
    bai.setBranchAddress(vertex_ndof_, branchName_ndof_);
    bai.setBranchAddress(vertex_chi2_, branchName_chi2_);
    bai.setBranchAddress(vertex_score_, branchName_score_);
    bai.setBranchAddress(vertex_npvs_, branchName_npvs_);
    bai.setBranchAddress(vertex_npvsGood_, branchName_npvsGood_);
  }
}

RecoVertex
RecoVertexReader::read() const
{
  const RecoVertexReader * const gInstance = instances_[branchName_];
  assert(gInstance);

  RecoVertex vertex(gInstance->vertex_x_,
                    gInstance->vertex_y_,
                    gInstance->vertex_z_,
                    gInstance->vertex_ndof_,
                    gInstance->vertex_chi2_,
                    gInstance->vertex_score_,
                    gInstance->vertex_npvs_,
                    gInstance->vertex_npvsGood_);
  return vertex;
}
