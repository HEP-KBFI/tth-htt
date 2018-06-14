#include "tthAnalysis/HiggsToTauTau/interface/mvaAuxFunctions_Hj_and_Hjj_taggers.h"

#include "tthAnalysis/HiggsToTauTau/interface/mvaAuxFunctions.h" // check_mvaInputs
#include "DataFormats/Math/interface/deltaR.h" // deltaR

double comp_mvaOutput_Hj_tagger(const RecoJet* jet,
                                const std::vector<const RecoLepton*>& leptons,
                                std::map<std::string, double>& mvaInputs_Hj_tagger,
                                TMVAInterface& mva_Hj_tagger,
                                const EventInfo & eventInfo)
{
  //-----------------------------------------------------------------------------
  // CV: updated version of Hj-tagger for analysis of 2017 data,
  //     as presented by Francesco Romeo in ttH multilepton+tau working meeting on June 3rd 2018
  //    (https://indico.cern.ch/event/718592/contributions/3038714/attachments/1666644/2672104/Hj_tagger_03_05_017_BLFR-1.pdf)
  //-----------------------------------------------------------------------------

  double dRmin_lepton = -1.;
  double dRmax_lepton = -1.;
  for ( std::vector<const RecoLepton*>::const_iterator lepton = leptons.begin();
	lepton != leptons.end(); ++lepton ) {
    double dR = deltaR(jet->eta(), jet->phi(), (*lepton)->eta(), (*lepton)->phi());
    if ( dRmin_lepton == -1. || dR < dRmin_lepton ) dRmin_lepton = dR;
    if ( dRmax_lepton == -1. || dR > dRmax_lepton ) dRmax_lepton = dR;
  }

  mvaInputs_Hj_tagger["Jet25_lepdrmin"] = dRmin_lepton;
  mvaInputs_Hj_tagger["max(Jet25_bDiscriminator,0.)"] = std::max(0., jet->BtagCSV());
  mvaInputs_Hj_tagger["max(Jet25_qg,0.)"] = std::max(0., jet->QGDiscr());
  mvaInputs_Hj_tagger["Jet25_lepdrmax"] = dRmax_lepton;
  mvaInputs_Hj_tagger["Jet25_pt"] = jet->pt();

  check_mvaInputs(mvaInputs_Hj_tagger, eventInfo);

  double mvaOutput_Hj_tagger = mva_Hj_tagger(mvaInputs_Hj_tagger);
  return mvaOutput_Hj_tagger;
}

double comp_mvaOutput_Hjj_tagger(const RecoJet* jet1, const RecoJet* jet2, const std::vector<const RecoJet*>& jets,
				 const std::vector<const RecoLepton*>& leptons,
				 std::map<std::string, double>& mvaInputs_Hjj_tagger, TMVAInterface& mva_Hjj_tagger,
				 std::map<std::string, double>& mvaInputs_Hj_tagger, TMVAInterface& mva_Hj_tagger,
				 const EventInfo & eventInfo)
{
  double jet1_mvaOutput_Hj_tagger = comp_mvaOutput_Hj_tagger(
    jet1, leptons,
    mvaInputs_Hj_tagger, mva_Hj_tagger,
    eventInfo);
  double jet2_mvaOutput_Hj_tagger = comp_mvaOutput_Hj_tagger(
    jet2, leptons,
    mvaInputs_Hj_tagger, mva_Hj_tagger,
    eventInfo);
  Particle::LorentzVector dijetP4 = jet1->p4() + jet2->p4();
  const RecoLepton* lepton_nearest = 0;
  double dRmin_lepton = -1.;
  for ( std::vector<const RecoLepton*>::const_iterator lepton = leptons.begin();
	lepton != leptons.end(); ++lepton ) {
    double dR = deltaR(dijetP4.eta(), dijetP4.phi(), (*lepton)->eta(), (*lepton)->phi());
    if ( dRmin_lepton == -1. || dR < dRmin_lepton ) {
      lepton_nearest = (*lepton);
      dRmin_lepton = dR;
    }
  }
  double dRmin_jet_other = -1.;
  double dRmax_jet_other = -1.;
  for ( std::vector<const RecoJet*>::const_iterator jet_other = jets.begin();
	jet_other != jets.end(); ++jet_other ) {
    if ( (*jet_other) == jet1 || (*jet_other) == jet2 ) continue;
    double dR = deltaR(dijetP4.eta(), dijetP4.phi(), (*jet_other)->eta(), (*jet_other)->phi());
    if ( dRmin_jet_other == -1. || dR < dRmin_jet_other ) dRmin_jet_other = dR;
    if ( dRmax_jet_other == -1. || dR > dRmax_jet_other ) dRmax_jet_other = dR;
  }
  mvaInputs_Hjj_tagger["bdtJetPair_minlepmass"] = ( lepton_nearest ) ? (dijetP4 + lepton_nearest->p4()).mass() : 0.;
  mvaInputs_Hjj_tagger["bdtJetPair_sumbdt"] = jet1_mvaOutput_Hj_tagger + jet2_mvaOutput_Hj_tagger;
  mvaInputs_Hjj_tagger["bdtJetPair_dr"] = deltaR(jet1->eta(), jet1->phi(), jet2->eta(), jet2->phi());
  mvaInputs_Hjj_tagger["bdtJetPair_minjdr"] = dRmin_jet_other;
  mvaInputs_Hjj_tagger["bdtJetPair_mass"] = dijetP4.mass();
  mvaInputs_Hjj_tagger["bdtJetPair_minjOvermaxjdr"] = ( dRmax_jet_other > 0. ) ? dRmin_jet_other/dRmax_jet_other : 1.;

  check_mvaInputs(mvaInputs_Hjj_tagger, eventInfo);

  double mvaOutput_Hjj_tagger = mva_Hjj_tagger(mvaInputs_Hjj_tagger);
  return mvaOutput_Hjj_tagger;
}
