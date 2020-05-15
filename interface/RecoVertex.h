#ifndef tthAnalysis_HiggsToTauTau_RecoVertex_h
#define tthAnalysis_HiggsToTauTau_RecoVertex_h

/** \class RecoVertex
 *
 * Class to access information for reconstructed primary event vertex
 *
 * \author Christian Veelken, Tallinn
 *
 */

#include "FWCore/ParameterSet/interface/ParameterSet.h" // edm::ParameterSet

#include <Rtypes.h> // Int_t, Double_t

#include <iostream> // std::ostream
#include <string> // std::string
#include <map> // std::map<,>

class RecoVertex
{
public:
  RecoVertex();
  RecoVertex(Double_t x, 
             Double_t y, 
             Double_t z, 
             Double_t ndof,
             Double_t chi2,
             Double_t score,
             Int_t npvs,
             Int_t npvsGood);
  ~RecoVertex();

  Double_t x() const;
  Double_t y() const;
  Double_t z() const; 
  Double_t ndof() const;
  Double_t chi2() const;
  Double_t score() const;
  Int_t npvs() const;
  Int_t npvsGood() const;

private:
  Double_t x_;        ///< x-coordinate of vertex position (in units of cm)
  Double_t y_;        ///< y-coordinate of vertex position (in units of cm)
  Double_t z_;        ///< z-coordinate of vertex position (in units of cm)
  Double_t ndof_;     ///< number of degrees of freedom in vertex fit
  Double_t chi2_;     ///< chi^2 per degree of freedom
  Double_t score_;    ///< vertex score, i.e. sum pT^2 of clustered objects
  Int_t    npvs_;     ///< total number of reconstructed primary vertices 
  Int_t    npvsGood_; ///< number of good reconstructed primary vertices
                      ///< (selection = !isFake && ndof > 4 && abs(z) <= 24 && position.Rho <= 2)
};

std::ostream &
operator<<(std::ostream & stream,
           const RecoVertex & vertex);

#endif // tthAnalysis_HiggsToTauTau_RecoJet_h


