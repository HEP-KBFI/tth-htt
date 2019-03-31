#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // get_human_line()

class RecoJetCollectionCleanerByIndex
{
public:
  RecoJetCollectionCleanerByIndex(bool debug = false)
    : debug_(debug)
  {}

  template <typename Toverlap>
  std::vector<const RecoJet *>
  operator()(const std::vector<const RecoJet *> & jets,
             const std::vector<const Toverlap *> & overlaps) const
  {
    if(debug_)
    {
      std::cout << get_human_line(this, __func__, __LINE__) << '\n';
    }

    std::vector<const RecoJet *> cleanedJets;
    for(const RecoJet * jet: jets)
    {
      const int jet_idx = jet->idx();
      bool isOverlap = false;
      for(const Toverlap * overlap: overlaps)
      {
        if(overlap->jetIdx() == jet_idx)
        {
          isOverlap = true;
          if(debug_)
          {
            std::cout << "Removed:\n"                    << *jet
                      << "because it overlapped with:\n" << *overlap
                      << " at index "                    << jet_idx
                      << '\n'
            ;
          }
          break;
        }
      }
      if(! isOverlap)
      {
        cleanedJets.push_back(jet);
      }
    }
    return cleanedJets;
  }

  template <typename Toverlap,
            typename... Args>
  std::vector<const RecoJet *>
  operator()(const std::vector<const RecoJet *> & jets,
             const std::vector<const Toverlap *> & overlaps,
             Args... args) const
  {
    std::vector<const RecoJet *> cleanedJets = (*this)(jets, overlaps);
    return (*this)(cleanedJets, args...);
  }

protected:
  bool debug_;
};
