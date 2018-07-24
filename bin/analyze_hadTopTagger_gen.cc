
// version preprocessor if condition used to comment out 2lss-1tau selection


#include "FWCore/ParameterSet/interface/ParameterSet.h" // edm::ParameterSet
#include "FWCore/PythonParameterSet/interface/MakeParameterSets.h" // edm::readPSetsFrom()
#include "FWCore/Utilities/interface/Exception.h" // cms::Exception
#include "PhysicsTools/FWLite/interface/TFileService.h" // fwlite::TFileService
#include "DataFormats/FWLite/interface/InputSource.h" // fwlite::InputSource
#include "DataFormats/FWLite/interface/OutputFiles.h" // fwlite::OutputFiles
#include "DataFormats/Math/interface/LorentzVector.h" // math::PtEtaPhiMLorentzVector
#include "DataFormats/Math/interface/deltaR.h" // deltaR

#include <TBenchmark.h> // TBenchmark
#include <TString.h> // TString, Form
#include <TMatrixD.h> // TMatrixD
#include <TError.h> // gErrorAbortLevel, kError
#include <TMath.h> // TMath::Pi()
#include <TH2.h>

#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h" // RecoLepton
#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetHTTv2.h" // RecoJetHTTv2
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetAK12.h" // RecoJetAK12
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h" // RecoHadTau
#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h" // GenLepton
#include "tthAnalysis/HiggsToTauTau/interface/GenJet.h" // GenJet
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTau.h" // GenHadTau
#include "tthAnalysis/HiggsToTauTau/interface/RecoMEt.h" // RecoMEt
#include "tthAnalysis/HiggsToTauTau/interface/MEMOutput_2lss_1tau.h" // MEMOutput_2lss_1tau
#include "tthAnalysis/HiggsToTauTau/interface/TMVAInterface.h" // TMVAInterface
#include "tthAnalysis/HiggsToTauTau/interface/mvaAuxFunctions.h" // check_mvaInputs, get_mvaInputVariables
#include "tthAnalysis/HiggsToTauTau/interface/mvaInputVariables.h" // auxiliary functions for computing input variables of the MVA used for signal extraction in the 2lss_1tau category
#include "tthAnalysis/HiggsToTauTau/interface/LeptonFakeRateInterface.h" // LeptonFakeRateInterface
#include "tthAnalysis/HiggsToTauTau/interface/JetToTauFakeRateInterface.h" // JetToTauFakeRateInterface
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronReader.h" // RecoElectronReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonReader.h" // RecoMuonReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauReader.h" // RecoHadTauReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetReader.h" // RecoJetReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetReaderHTTv2.h" // RecoJetReaderHTTv2
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelectorHTTv2.h" // RecoJetSelectorHTTv2
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetReaderAK12.h" // RecoJetReaderAK12
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelectorAK12.h" // RecoJetSelectorAK12
#include "tthAnalysis/HiggsToTauTau/interface/RecoMEtReader.h" // RecoMEtReader
#include "tthAnalysis/HiggsToTauTau/interface/MEMOutputReader_2lss_1tau.h" // MEMOutputReader_2lss_1tau
#include "tthAnalysis/HiggsToTauTau/interface/GenLeptonReader.h" // GenLeptonReader
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTauReader.h" // GenHadTauReader
#include "tthAnalysis/HiggsToTauTau/interface/GenJetReader.h" // GenJetReader
#include "tthAnalysis/HiggsToTauTau/interface/GenParticleReader.h" // GenParticleReader
#include "tthAnalysis/HiggsToTauTau/interface/LHEInfoReader.h" // LHEInfoReader
#include "tthAnalysis/HiggsToTauTau/interface/EventInfoReader.h" // EventInfoReader, EventInfo
#include "tthAnalysis/HiggsToTauTau/interface/convert_to_ptrs.h" // convert_to_ptrs
#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionCleaner.h" // RecoElectronCollectionCleaner, RecoMuonCollectionCleaner, RecoHadTauCollectionCleaner, RecoJetCollectionCleaner
#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionGenMatcher.h" // RecoElectronCollectionGenMatcher, RecoMuonCollectionGenMatcher, RecoHadTauCollectionGenMatcher, RecoJetCollectionGenMatcher
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorLoose.h" // RecoElectronCollectionSelectorLoose
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorFakeable.h" // RecoElectronCollectionSelectorFakeable
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorTight.h" // RecoElectronCollectionSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorLoose.h" // RecoMuonCollectionSelectorLoose
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorFakeable.h" // RecoMuonCollectionSelectorFakeable
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorTight.h" // RecoMuonCollectionSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauCollectionSelectorLoose.h" // RecoHadTauCollectionSelectorLoose
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauCollectionSelectorFakeable.h" // RecoHadTauCollectionSelectorFakeable
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauCollectionSelectorTight.h" // RecoHadTauCollectionSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelector.h" // RecoJetCollectionSelector
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelectorBtag.h" // RecoJetCollectionSelectorBtagLoose, RecoJetCollectionSelectorBtagMedium
#include "tthAnalysis/HiggsToTauTau/interface/RunLumiEventSelector.h" // RunLumiEventSelector
#include "tthAnalysis/HiggsToTauTau/interface/ElectronHistManager.h" // ElectronHistManager
#include "tthAnalysis/HiggsToTauTau/interface/MuonHistManager.h" // MuonHistManager
#include "tthAnalysis/HiggsToTauTau/interface/HadTauHistManager.h" // HadTauHistManager
#include "tthAnalysis/HiggsToTauTau/interface/JetHistManager.h" // JetHistManager
#include "tthAnalysis/HiggsToTauTau/interface/JetHistManagerHTTv2.h" // JetHistManagerHTTv2
#include "tthAnalysis/HiggsToTauTau/interface/JetHistManagerAK12.h" // JetHistManagerAK12
#include "tthAnalysis/HiggsToTauTau/interface/MEtHistManager.h" // MEtHistManager
#include "tthAnalysis/HiggsToTauTau/interface/MVAInputVarHistManager.h" // MVAInputVarHistManager
#include "tthAnalysis/HiggsToTauTau/interface/EvtHistManager_2lss_1tau.h" // EvtHistManager_2lss_1tau
#include "tthAnalysis/HiggsToTauTau/interface/WeightHistManager.h" // WeightHistManager
#include "tthAnalysis/HiggsToTauTau/interface/GenEvtHistManager.h" // GenEvtHistManager
#include "tthAnalysis/HiggsToTauTau/interface/LHEInfoHistManager.h" // LHEInfoHistManager
#include "tthAnalysis/HiggsToTauTau/interface/leptonTypes.h" // getLeptonType, kElectron, kMuon
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // getBTagWeight_option, getHadTau_genPdgId, isHigherPt, isMatched
#include "tthAnalysis/HiggsToTauTau/interface/HistManagerBase.h" // HistManagerBase
#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // fillWithOverFlow2d
#include "tthAnalysis/HiggsToTauTau/interface/hadTopTaggerAuxFunctions.h" // isGenMatchedJetTriplet
#include "tthAnalysis/HiggsToTauTau/interface/leptonGenMatchingAuxFunctions.h" // getLeptonGenMatch_definitions_1lepton, getLeptonGenMatch_string, getLeptonGenMatch_int
#include "tthAnalysis/HiggsToTauTau/interface/hadTauGenMatchingAuxFunctions.h" // getHadTauGenMatch_definitions_1tau, getHadTauGenMatch_string, getHadTauGenMatch_int
#include "tthAnalysis/HiggsToTauTau/interface/fakeBackgroundAuxFunctions.h" // getWeight_2L, getWeight_3L
#include "tthAnalysis/HiggsToTauTau/interface/backgroundEstimation.h" // prob_chargeMisId
#include "tthAnalysis/HiggsToTauTau/interface/hltPath.h" // hltPath, create_hltPaths, hltPaths_isTriggered, hltPaths_delete
#include "tthAnalysis/HiggsToTauTau/interface/hltPathReader.h" // hltPathReader
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_2016.h"
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_2017.h"
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_2018.h"
#include "tthAnalysis/HiggsToTauTau/interface/lutAuxFunctions.h" // loadTH2, getSF_from_TH2
#include "tthAnalysis/HiggsToTauTau/interface/cutFlowTable.h" // cutFlowTableType
#include "tthAnalysis/HiggsToTauTau/interface/NtupleFillerBDT.h" // NtupleFillerBDT
#include "tthAnalysis/HiggsToTauTau/interface/HadTopTagger.h" // HadTopTagger
#include "tthAnalysis/HiggsToTauTau/interface/TTreeWrapper.h" // TTreeWrapper
#include "tthAnalysis/HiggsToTauTau/interface/EvtWeightManager.h" // EvtWeightManager

#include <boost/math/special_functions/sign.hpp> // boost::math::sign()

#include <iostream> // std::cerr, std::fixed
#include <iomanip> // std::setprecision(), std::setw()
#include <string> // std::string
#include <vector> // std::vector<>
#include <cstdlib> // EXIT_SUCCESS, EXIT_FAILURE
#include <algorithm> // std::sort
#include <math.h> // acos, sqrt
#include <fstream> // std::ofstream
#include <assert.h> // assert

#define DoNotUse2lss_1tauConditions // uncomment this if 2lss_1tau rec-level selection conditions are not required


typedef math::PtEtaPhiMLorentzVector LV;
typedef std::vector<std::string> vstring;

//const int hadTauSelection_antiElectron = 1; // vLoose
//const int hadTauSelection_antiMuon = 1; // Loose
const int hadTauSelection_antiElectron = -1; // not applied
const int hadTauSelection_antiMuon = -1; // not applied


// Global variables::
bool isHTTv2FromTop;
bool isHTTv2FromTop_fatjetPtGt200 = false;
bool isHTTv2FromTop_fatjetPtGt200_and_subjetPtGt30 = false;
bool isHTTv2FromTop_selected = false;
bool isHTTv2FromAntiTop = false;
bool isHTTv2FromAntiTop_fatjetPtGt200 = false;
bool isHTTv2FromAntiTop_fatjetPtGt200_and_subjetPtGt30 = false;
bool isHTTv2FromAntiTop_selected = false;

bool isbCandiFromTop = false;
bool isW1CandiFromTop = false;
bool isW2CandiFromTop = false;
bool isJetTripletFromTop = false;
bool isbCandiFromAntiTop = false;
bool isW1CandiFromAntiTop = false;
bool isW2CandiFromAntiTop = false;
bool isJetTripletFromAntiTop = false;

bool isbCandiFromTopPtGt30 = false;
bool isW1CandiFromTopPtGt30 = false;
bool isW2CandiFromTopPtGt30 = false;
bool isJetTripletFromTopPtGt30 = false;
bool isbCandiFromAntiTopPtGt30 = false;
bool isW1CandiFromAntiTopPtGt30 = false;
bool isW2CandiFromAntiTopPtGt30 = false;
bool isJetTripletFromAntiTopPtGt30 = false;

int isCat1_Gen = 0;

TString sPrint;

cutFlowTableType cutFlowTable_2lss_1tau;
cutFlowTableType cutFlowTable_2lss_1tau_HTTv2;
cutFlowTableType cutFlowTable_2lss_1tau_AK12;
cutFlowTableType cutFlowTable_2lss_1tau_resolved;

double evtWeight;

JetHistManagerHTTv2* histManager_jetsHTTv2;
TH1* histogram_HTTv2_W_ptRec_div_ptGen;
TH1* histogram_HTTv2_mW;
TH1* histogram_HTTv2_Top_ptRec_div_ptGen;
TH1* histogram_HTTv2_mTop;
TH1* histogram_HTTv2_WJet1_ptRec_div_ptGen;
TH1* histogram_HTTv2_WJet1_dRmatch;
TH1* histogram_HTTv2_WJet1_cosThetaStar;
TH1* histogram_HTTv2_WJet2_ptRec_div_ptGen;
TH1* histogram_HTTv2_WJet2_dRmatch;
TH1* histogram_HTTv2_BJet_ptRec_div_ptGen;
TH1* histogram_HTTv2_BJet_dRmatch;
TH1* histogram_HTTv2_BJet_cosThetaStar;
TH1* histogram_HTTv2_GenTop_dRmin;
TH1* histogram_HTTv2Pt_div_GenTopPt_dRmin;
TH2* histogram_HTTv2_GenTop_dRmin_vs_HTTv2Pt_div_GenTopPt;

std::vector<GenParticle> genTopQuarks;
std::vector<GenParticle> genBJets;
std::vector<GenParticle> genWBosons;
std::vector<GenParticle> genWJets;
std::vector<GenParticle> genQuarkFromTop;


void dumpGenParticles(const std::string& label, const std::vector<GenParticle>& particles)
{
  for ( size_t idxParticle = 0; idxParticle < particles.size(); ++idxParticle ) {
    std::cout << label << " #" << idxParticle << ":" << " ";
    std::cout << particles[idxParticle];
    std::cout << std::endl;
  }
}

double square(double x)
{
  return x*x;
}

double comp_theta_t(const Particle::LorentzVector& jet1_p4, double jet1_pullEta, double jet1_pullPhi, const Particle::LorentzVector& jet2_p4)
{
  double dEta1 = jet1_pullEta - jet1_p4.eta();
  double dPhi1 = jet1_pullPhi - jet1_p4.phi();
  double dEta2 = jet2_p4.eta() - jet1_p4.eta();
  double dPhi2 = jet2_p4.phi() - jet1_p4.phi();
  double dR1 = sqrt(square(dEta1) + square(dPhi1));
  double dR2 = sqrt(square(dEta2) + square(dPhi2));
  if ( dR1*dR2 > 0. ) {
    double cos_theta_t = (dEta1*dEta2 + dPhi1*dPhi2)/(dR1*dR2);
    assert(cos_theta_t >= -1. && cos_theta_t <= +1.);
    return acos(cos_theta_t);
  } else {
    return -1.;
  }
}

enum {
  kTLVGenTop, kTLVGenBJet, kTLVGenWJet1, kTLVGenWJet2
};

void
CheckGenHTTv2JetMatching(int kGenMode, const GenParticle **genParticle, //Particle::LorentzVector *genParticle,
			 std::vector<const RecoJetHTTv2*> jet_ptrsHTTv2,
			 std::vector<const RecoJet*> selJets,
			 std::vector<const RecoHadTau*> selHadTaus,
			 std::vector<const RecoLepton*> selLeptons,
			 std::vector<const RecoElectron*> fakeableElectrons,
			 std::vector<const RecoMuon*> fakeableMuons,
			 std::vector<const RecoHadTau*> fakeableHadTaus,
			 RecoJetSelectorHTTv2 jetSelectorHTTv2) {

  const GenParticle *genTopQuark = genParticle[kTLVGenTop];
  const GenParticle *genBJetFromTop = genParticle[kTLVGenBJet];
  const GenParticle *genWJetFromTop_lead = genParticle[kTLVGenWJet1];
  const GenParticle *genWJetFromTop_sublead = genParticle[kTLVGenWJet2];

  Particle::LorentzVector genTopP4 = genTopQuark->p4();
  Particle::LorentzVector genWBosonFromTopP4 = genWJetFromTop_lead->p4() + genWJetFromTop_sublead->p4();

  if      ( kGenMode == kGenTop     ) sPrint += Form("\nTop\n");
  else if ( kGenMode == kGenAntiTop ) sPrint += Form("\nAntiTop\n");
  else assert(0);
  /*sPrint += Form(" Top:     (%f, %f, %f, %f); \n b:       (%f, %f, %f, %f); \n W1:      (%f, %f, %f, %f); \n W2:      (%f, %f, %f, %f)\n",
		 genTopP4.pt(),genTopP4.eta(),genTopP4.phi(),genTopP4.mass(),
		 genBJetFromTop->pt(),genBJetFromTop->eta(),genBJetFromTop->phi(),genBJetFromTop->mass(),
		 genWJetFromTop_lead->pt(),genWJetFromTop_lead->eta(),genWJetFromTop_lead->phi(),genWJetFromTop_lead->mass(),
		 genWJetFromTop_sublead->pt(),genWJetFromTop_sublead->eta(),genWJetFromTop_sublead->phi(),genWJetFromTop_sublead->mass()); */
  

  if ( (genBJetFromTop     && genWJetFromTop_lead     && genWJetFromTop_sublead     && genTopP4.pt()     > 200.) ) {
    cutFlowTable_2lss_1tau_HTTv2.update("genTop passes pT > 200 GeV");

    if ( (genBJetFromTop             && genBJetFromTop->absEta()          < 5.0 &&
	  genWJetFromTop_lead        && genWJetFromTop_lead->absEta()     < 5.0 &&
	  genWJetFromTop_sublead     && genWJetFromTop_sublead->absEta()     < 5.0) ) {
      cutFlowTable_2lss_1tau_HTTv2.update("genJet triplet passes abs(eta) < 5.0");

      if ( (genBJetFromTop             && genBJetFromTop->absEta()      < 2.4) ) {
	cutFlowTable_2lss_1tau_HTTv2.update("genBJet passes abs(eta) < 2.4");

	if ( (genBJetFromTop             && genBJetFromTop->absEta()          < 2.4 &&
	      genWJetFromTop_lead        && genWJetFromTop_lead->absEta()     < 2.4 &&
	      genWJetFromTop_sublead     && genWJetFromTop_sublead->absEta()     < 2.4) ) {
	  cutFlowTable_2lss_1tau_HTTv2.update("genJet triplet passes abs(eta) < 2.4");

	  if ( (genBJetFromTop             && genBJetFromTop->pt()          > 30  &&
		genWJetFromTop_lead        && genWJetFromTop_lead->pt()     > 30 &&
		genWJetFromTop_sublead     && genWJetFromTop_sublead->pt()     > 30 ) ) {
	    cutFlowTable_2lss_1tau_HTTv2.update("genJet triplet passes pt > 30");


	    if ( (genBJetFromTop && genWJetFromTop_lead && genWJetFromTop_sublead             &&
		  deltaR(genTopP4, genBJetFromTop->p4())                                < 1.5 &&
		  deltaR(genTopP4, genWJetFromTop_lead->p4())                           < 1.5 &&
		  deltaR(genTopP4, genWJetFromTop_sublead->p4())                        < 1.5) ) {
	      cutFlowTable_2lss_1tau_HTTv2.update("dR(genBJet, genWJet1, genWJet2) < 1.5");
	      isCat1_Gen++;


	      if (jet_ptrsHTTv2.size() >= 1) {
		cutFlowTable_2lss_1tau_HTTv2.update("HTTv2: jet_ptrsHTTv2.size() >= 1");
	      }


	      sPrint += "genInfo::\n";
	      if (genBJetFromTop     && genWJetFromTop_lead     && genWJetFromTop_sublead) {
		/*sPrint += Form(" Top:     (%6.1f, %5.2f, %5.2f, %g); \n b:       (%6.1f, %5.2f, %5.2f, %g); \n W1:      (%6.1f, %5.2f, %5.2f, %g); \n W2:      (%6.1f, %5.2f, %5.2f, %g)\n",
			       genTopP4.pt(),genTopP4.eta(),genTopP4.phi(),genTopP4.mass(),
			       genBJetFromTop->pt(),genBJetFromTop->eta(),genBJetFromTop->phi(),genBJetFromTop->mass(),
			       genWJetFromTop_lead->pt(),genWJetFromTop_lead->eta(),genWJetFromTop_lead->phi(),genWJetFromTop_lead->mass(),
			       genWJetFromTop_sublead->pt(),genWJetFromTop_sublead->eta(),genWJetFromTop_sublead->phi(),genWJetFromTop_sublead->mass()); */

		sPrint += Form("gen_Top: \t pt: %6.1f,  eta: %5.2f, phi: %5.2f, m: %g\n",
			       genTopP4.pt(),genTopP4.eta(),genTopP4.phi(),genTopP4.mass());
		sPrint += Form("gen_b:\t \t pt: %6.1f,  eta: %5.2f, phi: %5.2f, m: %g\n",
			       genBJetFromTop->pt(),genBJetFromTop->eta(),genBJetFromTop->phi(),genBJetFromTop->mass());
		sPrint += Form("gen_W1: \t pt: %6.1f,  eta: %5.2f, phi: %5.2f, m: %g\n",
			       genWJetFromTop_lead->pt(),genWJetFromTop_lead->eta(),genWJetFromTop_lead->phi(),genWJetFromTop_lead->mass());
		sPrint += Form("gen_W2: \t pt: %6.1f,  eta: %5.2f, phi: %5.2f, m: %g\n",
			       genWJetFromTop_sublead->pt(),genWJetFromTop_sublead->eta(),genWJetFromTop_sublead->phi(),genWJetFromTop_sublead->mass());

	      }


	      int nGenTopMatch = 0;
	      int nGenBMatch = 0;
	      int nGenW1Match = 0;
	      int nGenW2Match = 0;
	      int nGenTripletMatch = 0;
	      int nGenTripletAndFatJetMatch = 0;
	      int nGenTopMatch_1 = 0;
	      int nGenBMatch_1 = 0;
	      int nGenW1Match_1 = 0;
	      int nGenW2Match_1 = 0;
	      //int nGenTripletMatch_1 = 0;


	      double dRGenRecTopMin = 1.e+3;
	      double HTTv2JetPt_dRGenRecTopMin = -1;
	      double GenTopPt_dRGenRecTopMin = -1;

	      int kHTTv2JetPassedConditions = 0;
	      const RecoJetHTTv2* recTop = 0;
	      const RecoSubjetHTTv2* recBJetFromTop = 0;
	      const RecoSubjetHTTv2* recWJetFromTop_lead = 0;
	      const RecoSubjetHTTv2* recWJetFromTop_sublead = 0;
	      for ( std::vector<const RecoJetHTTv2*>::const_iterator jetHTTv2 = jet_ptrsHTTv2.begin();
		    jetHTTv2 != jet_ptrsHTTv2.end(); ++jetHTTv2 ) {
		//kHTTv2Jet++;

		if ( genBJetFromTop && genWJetFromTop_lead && genWJetFromTop_sublead && deltaR((*jetHTTv2)->p4(), genTopP4) < 1.5 ) {
		  nGenTopMatch++;

		  if ((*jetHTTv2)->pt() > 200 && (*jetHTTv2)->eta() < 2.4) {
		    double dR_1 = deltaR((*jetHTTv2)->p4(), genTopP4);
		    if (dR_1 < dRGenRecTopMin) {
		      dRGenRecTopMin = dR_1;
		      //HTTv2JetPt_dRGenRecTopMin = (*jetHTTv2)->pt();
		      //GenTopPt_dRGenRecTopMin = genTopP4.pt();
		    }
		  }
		}

		if ( genBJetFromTop && genWJetFromTop_lead && genWJetFromTop_sublead && deltaR((*jetHTTv2)->p4(), genTopP4) < 0.75 ) {
		  recTop = (*jetHTTv2);
		  histManager_jetsHTTv2->fillHistograms({ recTop }, evtWeight);
		  sPrint += " Top matched; \n";
		} else {
		  continue;
		}
		cutFlowTable_2lss_1tau_HTTv2.update("dR(HTTv2, genTop) < 0.75");

		kHTTv2JetPassedConditions++;

		int typeTop = 1;
		Particle::LorentzVector unfittedHadTopP4, selBJet, selWJet1, selWJet2, selTmp ;
		double genTopPtProbeTop = -1.;
		double genTopPtProbeAntiTop = -1.;
		bool b_isGenMatched        = false;
		bool Wlead_isGenMatched    = false;
		bool Wsublead_isGenMatched = false;;
		bool isGenMatched          = false;
		//bool fatjet_isGenMatched = false;
		double dR_tot_min = 1.e+3;
		int    kGenMatchingScoreMax = 0;

		unfittedHadTopP4 = (*jetHTTv2)->p4();
		const RecoSubjetHTTv2* recSubJet[3];
		recSubJet[0] = (*jetHTTv2)->subJet1();
		recSubJet[1] = (*jetHTTv2)->subJet2();
		recSubJet[2] = (*jetHTTv2)->subJet3();
		//int perm [5] = { 0, 1, 2, 0, 1 }; // I do not care about the ordering of wj1/2 so no fancy permutation solution is required

		sPrint += Form("\nHTTv2 jet #%i with dR(HTTv2, genTop) < 0.75\n",kHTTv2JetPassedConditions);
		sPrint += Form("HTTv2_Top: \t pt: %6.1f,  eta: %5.2f, phi: %5.2f, m: %g\n",
			       recTop->pt(), recTop->eta(), recTop->phi(), recTop->mass());
		sPrint += Form("HTTv2_subjet1: \t pt: %6.1f,  eta: %5.2f, phi: %5.2f, m: %g, \t bCSV: %f\n",
			       recSubJet[0]->pt(), recSubJet[0]->eta(), recSubJet[0]->phi(), recSubJet[0]->mass(), recSubJet[0]->BtagCSV());
		sPrint += Form("HTTv2_subjet2: \t pt: %6.1f,  eta: %5.2f, phi: %5.2f, m: %g, \t bCSV: %f\n",
			       recSubJet[1]->pt(), recSubJet[1]->eta(), recSubJet[1]->phi(), recSubJet[1]->mass(), recSubJet[1]->BtagCSV());
		sPrint += Form("HTTv2_subjet3: \t pt: %6.1f,  eta: %5.2f, phi: %5.2f, m: %g, \t bCSV: %f\n",
			       recSubJet[2]->pt(), recSubJet[2]->eta(), recSubJet[2]->phi(), recSubJet[2]->mass(), recSubJet[2]->BtagCSV());

		// it returns the gen-triplets organized in top/anti-top
		std::map<int, Particle::LorentzVector> genVar = isGenMatchedJetTripletVar(genTopQuarks, genBJets, genWBosons, genWJets, kGenMode);
		// using genWJets or genQuarkFromTop does not make any difference
		bool isAnalysisModeGenStudy = true;

		/*
		sPrint += "\ngenTopInfo from isGenMatchedJetTripletVar()::\n";
		sPrint += Form("gen_Top: \t pt: %6.1f,  eta: %5.2f, phi: %5.2f, m: %g\n",
			       genVar[kGenTopVar].pt(),genVar[kGenTopVar].eta(),genVar[kGenTopVar].phi(),genVar[kGenTopVar].mass());
		sPrint += Form("gen_b:\t \t pt: %6.1f,  eta: %5.2f, phi: %5.2f, m: %g\n",
			       genVar[kGenTopB].pt(),genVar[kGenTopB].eta(),genVar[kGenTopB].phi(),genVar[kGenTopB].mass());
		sPrint += Form("gen_W1: \t pt: %6.1f,  eta: %5.2f, phi: %5.2f, m: %g\n",
			       genVar[kGenTopWj1].pt(),genVar[kGenTopWj1].eta(),genVar[kGenTopWj1].phi(),genVar[kGenTopWj1].mass());
		sPrint += Form("gen_W2: \t pt: %6.1f,  eta: %5.2f, phi: %5.2f, m: %g\n",
			       genVar[kGenTopWj2].pt(),genVar[kGenTopWj2].eta(),genVar[kGenTopWj2].phi(),genVar[kGenTopWj2].mass());
		*/
      
		
		for (int i1=0; i1 < 3; i1++) {
		  for (int i2=0; i2 < 3; i2++) {
		    if (i2==i1) continue;
		    for (int i3=0; i3 < 3; i3++) {
		      if (i2==i3) continue;
		      if (i1==i3) continue;

		      selBJet = recSubJet[i1]->p4();
		      selWJet1 = recSubJet[i2]->p4();
		      selWJet2 = recSubJet[i3]->p4();

		//for (int ii = 0; ii < 3; ii++) {
		      /*selBJet = recSubJet[perm[ii]]->p4();
		  selWJet1 = recSubJet[perm[ii+1]]->p4();
		  selWJet2 = recSubJet[perm[ii+2]]->p4();*/
		  /*if (selWJet1.pt() < selWJet2.pt()) { // if selWJet1 is not lead then make it
		    selTmp = selWJet1;
		    selWJet1 = selWJet2;
		    selWJet2 = selTmp;
		    }*/


		      std::map<int, bool> genMatchingTop     = isGenMatchedJetTriplet(
				      selBJet, selWJet1, selWJet2,
				      genVar[kGenTop], genVar[kGenTopB], genVar[kGenTopW], genVar[kGenTopWj1], genVar[kGenTopWj2],
				      kGenMode, typeTop, unfittedHadTopP4,
				      isAnalysisModeGenStudy);
		      //std::map<int, bool> genMatchingTop     = isGenMatchedJetTriplet_Method2(selBJet, selWJet1, selWJet2, genTopQuarks, genBJets, genWBosons, genWJets, kGenMode, genTopPtProbeTop, typeTop, unfittedHadTopP4, sPrint);
		      //std::map<int, bool> genMatchingTop     = isGenMatchedJetTriplet_Method3(selBJet, selWJet1, selWJet2, genTopQuarks, genBJets, genWBosons, genWJets, kGenMode, genTopPtProbeTop, typeTop, unfittedHadTopP4, sPrint);

		      double dR_1 = deltaR(selBJet,  genBJetFromTop->p4());
		      double dR_2 = deltaR(selWJet1, genWJetFromTop_lead->p4());
		      double dR_3 = deltaR(selWJet2, genWJetFromTop_sublead->p4());
		      double dR_tot = dR_1*dR_1 + dR_2*dR_2 + dR_3*dR_3;
		      int    kGenMatchingScore = 0;
		      if (genMatchingTop[kGenMatchedBJet])  kGenMatchingScore++;
		      if (genMatchingTop[kGenMatchedWJet1]) kGenMatchingScore++;
		      if (genMatchingTop[kGenMatchedWJet2]) kGenMatchingScore++;

		      sPrint += Form("  combination: gen_b=subjet%i & gen_W1=subjet%i & gen_W2=subjet%i, \t dR: %f, %f, %f, tot %f, \t isGenMatched: %i, %i, %i (totalScore %i)\n",
				     i1+1,i2+1,i3+1, dR_1,dR_2,dR_3, dR_tot,
				     genMatchingTop[kGenMatchedBJet],genMatchingTop[kGenMatchedWJet1],genMatchingTop[kGenMatchedWJet2], 
				     kGenMatchingScore);
		      if ( (kGenMatchingScore > 0) &&
			   ( (kGenMatchingScore > kGenMatchingScoreMax) ||
			     (kGenMatchingScore == kGenMatchingScoreMax && dR_tot < dR_tot_min) ) ) {
			if (dR_tot < dR_tot_min) {
			  dR_tot_min = dR_tot;
			}
			kGenMatchingScoreMax  = kGenMatchingScore;
			b_isGenMatched        = genMatchingTop[kGenMatchedBJet];
			Wlead_isGenMatched    = genMatchingTop[kGenMatchedWJet1];
			Wsublead_isGenMatched = genMatchingTop[kGenMatchedWJet2];
			isGenMatched          = genMatchingTop[kGenMatchedTriplet];

			sPrint += Form(" *** MININUM ***\n");

			if (isGenMatched) {
			  recTop = (*jetHTTv2); // just to make sure jet and it's subjet are related
			  // recTop is not the last one fulfilling dR(recTop and genTop) < 0.75 condition

			  recBJetFromTop         = recSubJet[i1];
			  recWJetFromTop_lead    = recSubJet[i2];
			  recWJetFromTop_sublead = recSubJet[i3];
			}
		      }

		      /*
		      if (dR_tot < dR_tot_min) {
			dR_tot_min = dR_tot;
			b_isGenMatched        = genMatchingTop[kGenMatchedBJet];
			Wlead_isGenMatched    = genMatchingTop[kGenMatchedWJet1];
			Wsublead_isGenMatched = genMatchingTop[kGenMatchedWJet2];
			isGenMatched          = genMatchingTop[kGenMatchedTriplet];
			//fatjet_isGenMatched   = genMatchingTop[kGenMatchedFatJet];

			sPrint += Form(" subjet combination %i %i %i, \t dR: %f, %f, %f, tot %f, \t isGenMatched: %i, %i, %i *** MININUM **\n",
				       i1,i2,i3, dR_1,dR_2,dR_3, dR_tot,
				       b_isGenMatched,Wlead_isGenMatched,Wsublead_isGenMatched);

			if (isGenMatched) {
			  recTop = (*jetHTTv2); // just to make sure jet and it's subjet are related
			  // recTop is not the last one fulfilling dR(recTop and genTop) < 0.75 condition

			  recBJetFromTop         = recSubJet[i1];
			  recWJetFromTop_lead    = recSubJet[i2];
			  recWJetFromTop_sublead = recSubJet[i3];
			}
			}*/

		      if (genMatchingTop[kGenMatchedBJet]) {
			nGenBMatch++;
			if (selBJet.pt() > 30) nGenBMatch_1++;
		      }
		      if (genMatchingTop[kGenMatchedWJet1]) {
			nGenW1Match++;
			if (selWJet1.pt() > 30) nGenW1Match_1++;
		      }
		      if (genMatchingTop[kGenMatchedWJet2]) {
			nGenW2Match++;
			if (selWJet2.pt() > 30) nGenW2Match_1++;
		      }

		      if (genMatchingTop[kGenMatchedTriplet]) nGenTripletMatch++;

		      if (genMatchingTop[kGenMatchedTriplet] && genMatchingTop[kGenMatchedFatJet]) nGenTripletAndFatJetMatch++;
		      if (genMatchingTop[kGenMatchedTriplet]) sPrint += Form("\t HTTv2 subjet combination matched to all 3 genJets: %i_%i_%i;\n",i1,i2,i3);
		    }
		  }
		}


		sPrint += Form(" HTTv2 jet matching status:: isGenMatched: %i, %i, %i \n",
			       b_isGenMatched,Wlead_isGenMatched,Wsublead_isGenMatched);
		if (isGenMatched) cutFlowTable_2lss_1tau_HTTv2.update("HTTv2: gen matched");

		if ( !isGenMatched ) { // dR(HTTv2, genTop) < 0.75,  but  subjet gen matching failed
		  sPrint += "\ndR(HTTv2, genTop) < 0.75,  but  subjet gen matching failed\n";
		  sPrint += Form("genTop: \t pt: %6.1f,  eta: %5.2f, phi: %5.2f, m: %g \n",
				  genTopQuark->pt(), genTopQuark->eta(), genTopQuark->phi(), genTopQuark->mass());
		  sPrint += Form("genB: \t\t pt: %6.1f,  eta: %5.2f, phi: %5.2f, m: %g, \t isMatchFound: %i \n",
				 genBJetFromTop->pt(),genBJetFromTop->eta(),genBJetFromTop->phi(),genBJetFromTop->mass(), b_isGenMatched);
		  sPrint += Form("genW1: \t\t pt: %6.1f,  eta: %5.2f, phi: %5.2f, m: %g, \t isMatchFound: %i \n",
				 genWJetFromTop_lead->pt(),genWJetFromTop_lead->eta(),genWJetFromTop_lead->phi(),genWJetFromTop_lead->mass(), Wlead_isGenMatched);
		  sPrint += Form("genW2: \t\t pt: %6.1f,  eta: %5.2f, phi: %5.2f, m: %g, \t isMatchFound: %i \n",
				 genWJetFromTop_sublead->pt(),genWJetFromTop_sublead->eta(),genWJetFromTop_sublead->phi(),genWJetFromTop_sublead->mass(), Wsublead_isGenMatched);

		  sPrint += Form("\nHTTv2_Top: \t pt: %6.1f,  eta: %5.2f, phi: %5.2f, m: %g\n",
				  recTop->pt(), recTop->eta(), recTop->phi(), recTop->mass());
		  sPrint += Form("HTTv2_subjet1: \t pt: %6.1f,  eta: %5.2f, phi: %5.2f, m: %g\n",
				  recSubJet[0]->pt(), recSubJet[0]->eta(), recSubJet[0]->phi(), recSubJet[0]->mass());
		  sPrint += Form("HTTv2_subjet2: \t pt: %6.1f,  eta: %5.2f, phi: %5.2f, m: %g\n",
				  recSubJet[1]->pt(), recSubJet[1]->eta(), recSubJet[1]->phi(), recSubJet[1]->mass());
		  sPrint += Form("HTTv2_subjet3: \t pt: %6.1f,  eta: %5.2f, phi: %5.2f, m: %g\n",
				  recSubJet[2]->pt(), recSubJet[2]->eta(), recSubJet[2]->phi(), recSubJet[2]->mass());

		  cutFlowTable_2lss_1tau_HTTv2.update("HTTv2: gen match failed");
		  if (!b_isGenMatched)        cutFlowTable_2lss_1tau_HTTv2.update("HTTv2: genB match failed");
		  if (!Wlead_isGenMatched)    cutFlowTable_2lss_1tau_HTTv2.update("HTTv2: genWlead match failed");
		  if (!Wsublead_isGenMatched) cutFlowTable_2lss_1tau_HTTv2.update("HTTv2: genWsublead match failed");


		  sPrint += "\nLooking at AK4 jets within dR < 2.0 of genTop::\n";
		  bool isAK4JetAroundGenTop = false;
		  for ( std::vector<const RecoJet*>::const_iterator selJet = selJets.begin(); selJet != selJets.end(); ++selJet ) {
		    if ( deltaR((*selJet)->p4(), genTopQuark->p4()) < 2.0 ) {
		      isAK4JetAroundGenTop = true;
		    }
		  }

		  if (isAK4JetAroundGenTop) {
		    sPrint += "Found AK4 jet within dR < 2.0 of genTop::\n";
		    cutFlowTable_2lss_1tau_HTTv2.update("HTTv2: AK4 jet near genTop dR<2.0");

		    for (int iGenJet=0; iGenJet<3; iGenJet++) {
		      bool isGenJetMatched;
		      TString sGen;
		      // check only those genParticles for which recJet is not found
		      switch (iGenJet) {
		      case 0:
			//if (b_isGenMatched) continue;
			sGen = "B";
			isGenJetMatched = b_isGenMatched;
			break;

		      case 1:
			//if (Wlead_isGenMatched) continue;
			sGen = "W1";
			isGenJetMatched = Wlead_isGenMatched;
			break;

		      case 2:
			//if (Wsublead_isGenMatched) continue;
			sGen = "W2";
			isGenJetMatched = Wsublead_isGenMatched;
			break;
		      }

		      sPrint += Form("\n\tgen%s:  pt: %6.1f,  eta: %5.2f, phi: %5.2f, m: %g, \t Matched found: %i\n",
				     sGen.Data(),
				     genParticle[kTLVGenBJet+iGenJet]->pt(),genParticle[kTLVGenBJet+iGenJet]->eta(),genParticle[kTLVGenBJet+iGenJet]->phi(),genParticle[kTLVGenBJet+iGenJet]->mass(), isGenJetMatched);

		      //bool isHTTv2SubjetMatched = false;
		      /*for (int iRecJet=0; iRecJet<3; iRecJet++) {
			if (deltaR(recSubJet[iRecJet]->p4(), genParticle[kTLVGenBJet+iGenJet]->p4()) < 0.25) {
			  sPrint += Form("\t\t\tMATCHES HTTv2 SUBJET (dR<0.25):  pt: %6.1f,  eta: %5.2f, phi: %5.2f, m: %g\n",
					 recSubJet[iRecJet]->pt(), recSubJet[iRecJet]->eta(), recSubJet[iRecJet]->phi(), recSubJet[iRecJet]->mass());
			  isHTTv2SubjetMatched = true;
			}
		      }

		      if (isHTTv2SubjetMatched) {
			cutFlowTable_2lss_1tau_HTTv2.update(Form("HTTv2: gen%i MATCHES HTTv2 SUBJET",iGenJet));
			continue;
			}*/

		      sPrint += Form("\t    AK4 size %zu\n",selJets.size());
		      bool isAK4JetMatched = false;
		      for ( std::vector<const RecoJet*>::const_iterator selJet = selJets.begin(); selJet != selJets.end(); ++selJet ) {
			sPrint += Form("\t\tAK4 jet:  pt: %6.1f,  eta: %5.2f, phi: %5.2f, m: %g, bCSV: %5.2f,",
				       (*selJet)->pt(), (*selJet)->eta(), (*selJet)->phi(), (*selJet)->mass(), (*selJet)->BtagCSV());

			if (deltaR((*selJet)->p4(), genParticle[kTLVGenBJet+iGenJet]->p4()) < 0.3) {
			  sPrint += Form("\t MATCHES with gen%s (dR<0.3)",sGen.Data());
			  isAK4JetMatched = true;
			}
			sPrint += "\n";
		      }

		      if ( isAK4JetMatched ) {
			if ( !isGenJetMatched ) {
			  cutFlowTable_2lss_1tau_HTTv2.update(Form("HTTv2: HTTv2 unmatched gen%s MATCHES AK4 ",sGen.Data()));
			}
		      } else {
			sPrint += "\t       UNMATCHED AK4 \n";
			if ( !isGenJetMatched ) {
			  cutFlowTable_2lss_1tau_HTTv2.update(Form("HTTv2: HTTv2 unmatched gen%s UNMATCHED AK4",sGen.Data()));
			}
		      }

		      sPrint += Form("\t    selHadTau size %zu\n",selHadTaus.size());
		      bool isHadTauJetMatched = false;
		      for ( std::vector<const RecoHadTau*>::const_iterator selHadTau = selHadTaus.begin(); selHadTau != selHadTaus.end(); ++selHadTau ) {
			sPrint += Form("\t\tselHadTau jet:  pt: %6.1f,  eta: %5.2f, phi: %5.2f, m: %g,",
				       (*selHadTau)->pt(), (*selHadTau)->eta(), (*selHadTau)->phi(), (*selHadTau)->mass());

			if (deltaR((*selHadTau)->p4(), genParticle[kTLVGenBJet+iGenJet]->p4()) < 0.3) {
			  sPrint += Form("\t MATCHES with gen%s (dR<0.3)",sGen.Data());
			  isHadTauJetMatched = true;
			}
			sPrint += "\n";
		      }

		      if ( isHadTauJetMatched ) {
			if ( !isGenJetMatched ) {
			  cutFlowTable_2lss_1tau_HTTv2.update(Form("HTTv2: HTTv2 unmatched gen%s MATCHES HadTau ",sGen.Data()));
			}
		      } else {
			sPrint += "\t       UNMATCHED HadTau \n";
			if ( !isGenJetMatched ) {
			  cutFlowTable_2lss_1tau_HTTv2.update(Form("HTTv2: HTTv2 unmatched gen%s UNMATCHED HadTau",sGen.Data()));
			}
		      }

		      sPrint += Form("\t    selLeptons size %zu\n",selLeptons.size());
		      bool isLeptonMatched = false;
		      for ( std::vector<const RecoLepton*>::const_iterator selLepton = selLeptons.begin(); selLepton != selLeptons.end(); ++selLepton ) {
			sPrint += Form("\t\tselLepton:      pt: %6.1f,  eta: %5.2f, phi: %5.2f, m: %g,",
				       (*selLepton)->pt(), (*selLepton)->eta(), (*selLepton)->phi(), (*selLepton)->mass());

			if (deltaR((*selLepton)->p4(), genParticle[kTLVGenBJet+iGenJet]->p4()) < 0.3) {
			  sPrint += Form("\t MATCHES with gen%s (dR<0.3)",sGen.Data());
			  isLeptonMatched = true;
			}
			sPrint += "\n";
		      }

		      if ( isLeptonMatched ) {
			if ( !isGenJetMatched ) {
			  cutFlowTable_2lss_1tau_HTTv2.update(Form("HTTv2: HTTv2 unmatched gen%s MATCHES selLepton ",sGen.Data()));
			}
		      } else {
			sPrint += "\t       UNMATCHED selLepton \n";
			if ( !isGenJetMatched ) {
			  cutFlowTable_2lss_1tau_HTTv2.update(Form("HTTv2: HTTv2 unmatched gen%s UNMATCHED selLepton",sGen.Data()));
			}
		      }


		      sPrint += Form("\t    fakeableElectrons size %zu\n",fakeableElectrons.size());
		      bool isfakeableElectronMatched = false;
		      for ( std::vector<const RecoElectron*>::const_iterator fakeableElectron = fakeableElectrons.begin(); fakeableElectron != fakeableElectrons.end(); ++fakeableElectron ) {
			sPrint += Form("\t\tfakeableElectrons:      pt: %6.1f,  eta: %5.2f, phi: %5.2f, m: %g,",
				       (*fakeableElectron)->pt(), (*fakeableElectron)->eta(), (*fakeableElectron)->phi(), (*fakeableElectron)->mass());

			if (deltaR((*fakeableElectron)->p4(), genParticle[kTLVGenBJet+iGenJet]->p4()) < 0.3) {
			  sPrint += Form("\t MATCHES with gen%s (dR<0.3)",sGen.Data());
			  isfakeableElectronMatched = true;
			}
			sPrint += "\n";
		      }

		      if ( isfakeableElectronMatched ) {
			if ( !isGenJetMatched ) {
			  cutFlowTable_2lss_1tau_HTTv2.update(Form("HTTv2: HTTv2 unmatched gen%s MATCHES fakeableElectron ",sGen.Data()));
			}
		      } else {
			sPrint += "\t       UNMATCHED fakeableElectron \n";
			if ( !isGenJetMatched ) {
			  cutFlowTable_2lss_1tau_HTTv2.update(Form("HTTv2: HTTv2 unmatched gen%s UNMATCHED fakeableElectron",sGen.Data()));
			}
		      }


		      sPrint += Form("\t    fakeableMuons size %zu\n",fakeableMuons.size());
		      bool isfakeableMuonMatched = false;
		      for ( std::vector<const RecoMuon*>::const_iterator fakeableMuon = fakeableMuons.begin(); fakeableMuon != fakeableMuons.end(); ++fakeableMuon ) {
			sPrint += Form("\t\tfakeableMuons:      pt: %6.1f,  eta: %5.2f, phi: %5.2f, m: %g,",
				       (*fakeableMuon)->pt(), (*fakeableMuon)->eta(), (*fakeableMuon)->phi(), (*fakeableMuon)->mass());

			if (deltaR((*fakeableMuon)->p4(), genParticle[kTLVGenBJet+iGenJet]->p4()) < 0.3) {
			  sPrint += Form("\t MATCHES with gen%s (dR<0.3)",sGen.Data());
			  isfakeableMuonMatched = true;
			}
			sPrint += "\n";
		      }

		      if ( isfakeableMuonMatched ) {
			if ( !isGenJetMatched ) {
			  cutFlowTable_2lss_1tau_HTTv2.update(Form("HTTv2: HTTv2 unmatched gen%s MATCHES fakeableMuon ",sGen.Data()));
			}
		      } else {
			sPrint += "\t       UNMATCHED fakeableMuon \n";
			if ( !isGenJetMatched ) {
			  cutFlowTable_2lss_1tau_HTTv2.update(Form("HTTv2: HTTv2 unmatched gen%s UNMATCHED fakeableMuon",sGen.Data()));
			}
		      }

		      sPrint += Form("\t    fakeableHadTaus size %zu\n",fakeableHadTaus.size());
		      bool isfakeableHadTauMatched = false;
		      for ( std::vector<const RecoHadTau*>::const_iterator fakeableHadTau = fakeableHadTaus.begin(); fakeableHadTau != fakeableHadTaus.end(); ++fakeableHadTau ) {
			sPrint += Form("\t\tfakeableHadTaus:      pt: %6.1f,  eta: %5.2f, phi: %5.2f, m: %g,",
				       (*fakeableHadTau)->pt(), (*fakeableHadTau)->eta(), (*fakeableHadTau)->phi(), (*fakeableHadTau)->mass());

			if (deltaR((*fakeableHadTau)->p4(), genParticle[kTLVGenBJet+iGenJet]->p4()) < 0.3) {
			  sPrint += Form("\t MATCHES with gen%s (dR<0.3)",sGen.Data());
			  isfakeableHadTauMatched = true;
			}
			sPrint += "\n";
		      }

		      if ( isfakeableHadTauMatched ) {
			if ( !isGenJetMatched ) {
			  cutFlowTable_2lss_1tau_HTTv2.update(Form("HTTv2: HTTv2 unmatched gen%s MATCHES fakeableHadTau ",sGen.Data()));
			}
		      } else {
			sPrint += "\t       UNMATCHED fakeableHadTau \n";
			if ( !isGenJetMatched ) {
			  cutFlowTable_2lss_1tau_HTTv2.update(Form("HTTv2: HTTv2 unmatched gen%s UNMATCHED fakeableHadTau",sGen.Data()));
			}
		      }

		    }
		  } else {
		    sPrint += "\t No AK4 jet around genTop dR<2.0\n";
		  }

		}


		//~~~~
	      }

	      sPrint += Form("HTTv2: n HTTv2 jets within dR<0.75 genTop per Top/Antitop: %i\n",kHTTv2JetPassedConditions);

	      if (nGenTopMatch >= 1) cutFlowTable_2lss_1tau_HTTv2.update("HTTv2: GenTop matched (dR < 1.5)");
	      if (recTop) {
		cutFlowTable_2lss_1tau_HTTv2.update("HTTv2: GenTop matched (dR < 0.75)");
		if ((recTop && recTop->pt() > 200)){
		  cutFlowTable_2lss_1tau_HTTv2.update("HTTv2: GenTop matched (dR < 0.75 && rectop.pt > 200)");
		}


		if (nGenBMatch >= 1) cutFlowTable_2lss_1tau_HTTv2.update("HTTv2**: GenBJet matched)");
		if (nGenBMatch_1 >= 1) cutFlowTable_2lss_1tau_HTTv2.update("HTTv2**: GenBJet matched selBJet.pt > 30)");
		if (nGenW1Match >= 1) cutFlowTable_2lss_1tau_HTTv2.update("HTTv2**: GenWJet1 matched)");
		if (nGenW1Match_1 >= 1) cutFlowTable_2lss_1tau_HTTv2.update("HTTv2**: GenWJet1 matched selWJet1.pt > 30)");
		if (nGenW2Match >= 1) cutFlowTable_2lss_1tau_HTTv2.update("HTTv2**: GenWJet2 matched)");
		if (nGenW2Match_1 >= 1) cutFlowTable_2lss_1tau_HTTv2.update("HTTv2**: GenWJet2 matched selWJet2.pt > 30)");

		if (nGenTripletMatch >= 1) cutFlowTable_2lss_1tau_HTTv2.update("HTTv2**: GenTripletJet matched)");
		if (nGenTripletAndFatJetMatch >= 1) cutFlowTable_2lss_1tau_HTTv2.update("HTTv2**: GenTripletJet and FatJet matched)");

	      }

	      if (dRGenRecTopMin < 1.e+3) {
		histogram_HTTv2_GenTop_dRmin->Fill(dRGenRecTopMin);
		histogram_HTTv2_GenTop_dRmin_vs_HTTv2Pt_div_GenTopPt->Fill(HTTv2JetPt_dRGenRecTopMin/GenTopPt_dRGenRecTopMin, dRGenRecTopMin);
		if (dRGenRecTopMin < 0.5) {
		  histogram_HTTv2Pt_div_GenTopPt_dRmin->Fill(HTTv2JetPt_dRGenRecTopMin/GenTopPt_dRGenRecTopMin);
		}
	      }


	      if ( recBJetFromTop && recWJetFromTop_lead && recWJetFromTop_sublead ) {
		Particle::LorentzVector recWBosonFromTopP4 = recWJetFromTop_lead->p4() + recWJetFromTop_sublead->p4();
		if ( genWBosonFromTopP4.pt() > 100. ) {
		  fillWithOverFlow(histogram_HTTv2_W_ptRec_div_ptGen, recWBosonFromTopP4.pt()/genWBosonFromTopP4.pt(), evtWeight);
		}
		fillWithOverFlow(histogram_HTTv2_mW, recWBosonFromTopP4.mass(), evtWeight);
		Particle::LorentzVector recTopP4 = recBJetFromTop->p4() + recWBosonFromTopP4;
		if ( genTopP4.pt() > 200. ) {
		  fillWithOverFlow(histogram_HTTv2_Top_ptRec_div_ptGen, recTopP4.pt()/genTopP4.pt(), evtWeight);
		}
		fillWithOverFlow(histogram_HTTv2_mTop, recTopP4.mass(), evtWeight);
		if ( genWJetFromTop_lead->pt() > 20. ) {
		  fillWithOverFlow(histogram_HTTv2_WJet1_ptRec_div_ptGen, recWJetFromTop_lead->pt()/genWJetFromTop_lead->pt(), evtWeight);
		  fillWithOverFlow(histogram_HTTv2_WJet1_dRmatch, deltaR(recWJetFromTop_lead->p4(), genWJetFromTop_lead->p4()), evtWeight);
		  double cosThetaStar_WJet1 = comp_cosThetaStar(recWJetFromTop_lead->p4(), recWBosonFromTopP4);
		  fillWithOverFlow(histogram_HTTv2_WJet1_cosThetaStar, cosThetaStar_WJet1, evtWeight);
		}
		if ( genWJetFromTop_sublead->pt() > 20. ) {
		  fillWithOverFlow(histogram_HTTv2_WJet2_ptRec_div_ptGen, recWJetFromTop_sublead->pt()/genWJetFromTop_sublead->pt(), evtWeight);
		  fillWithOverFlow(histogram_HTTv2_WJet2_dRmatch, deltaR(recWJetFromTop_sublead->p4(), genWJetFromTop_sublead->p4()), evtWeight);
		}
		if ( genBJetFromTop->pt() > 20. ) {
		  fillWithOverFlow(histogram_HTTv2_BJet_ptRec_div_ptGen, recBJetFromTop->pt()/genBJetFromTop->pt(), evtWeight);
		  fillWithOverFlow(histogram_HTTv2_BJet_dRmatch, deltaR(recBJetFromTop->p4(), genBJetFromTop->p4()), evtWeight);
		  double cosThetaStar_BJet = comp_cosThetaStar(recBJetFromTop->p4(), recTopP4);
		  fillWithOverFlow(histogram_HTTv2_BJet_cosThetaStar, cosThetaStar_BJet, evtWeight);
		}
		isHTTv2FromTop = true;
		if ( recTop->pt() > 200 ) {
		  isHTTv2FromTop_fatjetPtGt200 = true;
		  if ( recTop->subJet1()->pt() > 30 && recTop->subJet2()->pt() > 30 && recTop->subJet3()->pt() > 30 ) {
		    isHTTv2FromTop_fatjetPtGt200_and_subjetPtGt30 = true;
		    if ( jetSelectorHTTv2(*recTop) ) {
		      /*std::cout << "found boosted hadronic top:"
			<< " run = " << eventInfo.run << ", ls = " << eventInfo.lumi << ", event = " << eventInfo.event << std::endl;
			std::cout << "HTTv2 jet:" << std::endl;
			std::cout << (*recTop);*/
		      isHTTv2FromTop_selected = true;
		    }
		  }
		}
	      }

	    }
	  }
	}
      }
    }
  }

}




/**
 * @brief Check why only 25% of ttH signal events selected in 2lss_1tau category
 *        contain a reconstructible hadronic top
 */
int main(int argc, char* argv[])
{
  //--- throw an exception in case ROOT encounters an error
  gErrorAbortLevel = kError;

  //--- parse command-line arguments
  if ( argc < 2 ) {
    std::cout << "Usage: " << argv[0] << " [parameters.py]" << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << "<analyze_hadTopTagger_gen>:" << std::endl;

//--- keep track of time it takes the macro to execute
  TBenchmark clock;
  clock.Start("analyze_hadTopTagger_gen");

//--- read python configuration parameters
  if ( !edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process") )
    throw cms::Exception("analyze_hadTopTagger_gen")
      << "No ParameterSet 'process' found in configuration file = " << argv[1] << " !!\n";

  edm::ParameterSet cfg = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");

  edm::ParameterSet cfg_analyze = cfg.getParameter<edm::ParameterSet>("analyze_hadTopTagger_gen");

  std::string treeName = cfg_analyze.getParameter<std::string>("treeName");

  std::string process_string = cfg_analyze.getParameter<std::string>("process");
  bool isSignal = ( process_string == "signal" ) ? true : false;

  std::string histogramDir = cfg_analyze.getParameter<std::string>("histogramDir");

  std::string era_string = cfg_analyze.getParameter<std::string>("era");
  const int era = get_era(era_string);

  vstring triggerNames_1e = cfg_analyze.getParameter<vstring>("triggers_1e");
  std::vector<hltPath*> triggers_1e = create_hltPaths(triggerNames_1e);
  bool use_triggers_1e = cfg_analyze.getParameter<bool>("use_triggers_1e");
  vstring triggerNames_2e = cfg_analyze.getParameter<vstring>("triggers_2e");
  std::vector<hltPath*> triggers_2e = create_hltPaths(triggerNames_2e);
  bool use_triggers_2e = cfg_analyze.getParameter<bool>("use_triggers_2e");
  vstring triggerNames_1mu = cfg_analyze.getParameter<vstring>("triggers_1mu");
  std::vector<hltPath*> triggers_1mu = create_hltPaths(triggerNames_1mu);
  bool use_triggers_1mu = cfg_analyze.getParameter<bool>("use_triggers_1mu");
  vstring triggerNames_2mu = cfg_analyze.getParameter<vstring>("triggers_2mu");
  std::vector<hltPath*> triggers_2mu = create_hltPaths(triggerNames_2mu);
  bool use_triggers_2mu = cfg_analyze.getParameter<bool>("use_triggers_2mu");
  vstring triggerNames_1e1mu = cfg_analyze.getParameter<vstring>("triggers_1e1mu");
  std::vector<hltPath*> triggers_1e1mu = create_hltPaths(triggerNames_1e1mu);
  bool use_triggers_1e1mu = cfg_analyze.getParameter<bool>("use_triggers_1e1mu");

  bool apply_offline_e_trigger_cuts_1e = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_1e");
  bool apply_offline_e_trigger_cuts_2e = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_2e");
  bool apply_offline_e_trigger_cuts_1mu = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_1mu");
  bool apply_offline_e_trigger_cuts_2mu = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_2mu");
  bool apply_offline_e_trigger_cuts_1e1mu = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_1e1mu");

  enum { kOS, kSS };
  std::string leptonChargeSelection_string = cfg_analyze.getParameter<std::string>("leptonChargeSelection");
  int leptonChargeSelection = -1;
  if      ( leptonChargeSelection_string == "OS" ) leptonChargeSelection = kOS;
  else if ( leptonChargeSelection_string == "SS" ) leptonChargeSelection = kSS;
  else throw cms::Exception("analyze_hadTopTagger_gen")
    << "Invalid Configuration parameter 'leptonChargeSelection' = " << leptonChargeSelection_string << " !!\n";
	std::cout<<"leptonChargeSelection:"<<leptonChargeSelection<<std::endl;

  std::string leptonSelection_string = cfg_analyze.getParameter<std::string>("leptonSelection").data();
  std::cout << "leptonSelection_string = " << leptonSelection_string << std::endl;
  int leptonSelection = -1;
  if      ( leptonSelection_string == "Loose"                                                      ) leptonSelection = kLoose;
  else if ( leptonSelection_string == "Fakeable" || leptonSelection_string == "Fakeable_mcClosure" ) leptonSelection = kFakeable;
  else if ( leptonSelection_string == "Tight"                                                      ) leptonSelection = kTight;
  else throw cms::Exception("analyze_hadTopTagger_gen")
    << "Invalid Configuration parameter 'leptonSelection' = " << leptonSelection_string << " !!\n";

  bool apply_leptonGenMatching = cfg_analyze.getParameter<bool>("apply_leptonGenMatching");
  std::vector<leptonGenMatchEntry> leptonGenMatch_definitions = getLeptonGenMatch_definitions_2lepton(apply_leptonGenMatching);
  std::cout << "leptonGenMatch_definitions:" << std::endl;
  std::cout << leptonGenMatch_definitions;

  TString hadTauSelection_string = cfg_analyze.getParameter<std::string>("hadTauSelection").data();
  TObjArray* hadTauSelection_parts = hadTauSelection_string.Tokenize("|");
  assert(hadTauSelection_parts->GetEntries() >= 1);
  const std::string hadTauSelection_part1 = (dynamic_cast<TObjString*>(hadTauSelection_parts->At(0)))->GetString().Data();
  const int hadTauSelection = get_selection(hadTauSelection_part1);
  std::string hadTauSelection_part2 = ( hadTauSelection_parts->GetEntries() == 2 ) ? (dynamic_cast<TObjString*>(hadTauSelection_parts->At(1)))->GetString().Data() : "";
  delete hadTauSelection_parts;

  bool apply_hadTauGenMatching = cfg_analyze.getParameter<bool>("apply_hadTauGenMatching");
  std::vector<hadTauGenMatchEntry> hadTauGenMatch_definitions = getHadTauGenMatch_definitions_1tau(apply_hadTauGenMatching);
  std::cout << "hadTauGenMatch_definitions:" << std::endl;
  std::cout << hadTauGenMatch_definitions;

  std::string chargeSumSelection_string = cfg_analyze.getParameter<std::string>("chargeSumSelection");
  int chargeSumSelection = -1;
  if      ( chargeSumSelection_string == "OS" ) chargeSumSelection = kOS;
  else if ( chargeSumSelection_string == "SS" ) chargeSumSelection = kSS;
  else throw cms::Exception("analyze_hadTopTagger_gen")
    << "Invalid Configuration parameter 'chargeSumSelection' = " << chargeSumSelection_string << " !!\n";
	std::cout<<"chargeSumSelection:"<<chargeSumSelection<<std::endl;

  bool apply_lepton_and_hadTauCharge_cut = cfg_analyze.getParameter<bool>("apply_lepton_and_hadTauCharge_cut");
  std::cout << "apply_lepton_and_hadTauCharge_cut = " << apply_lepton_and_hadTauCharge_cut << std::endl;

  bool isMC = cfg_analyze.getParameter<bool>("isMC");
  bool isMC_tH = ( process_string == "tHq" || process_string == "tHW" ) ? true : false;
  bool hasLHE = cfg_analyze.getParameter<bool>("hasLHE");
  std::string central_or_shift = cfg_analyze.getParameter<std::string>("central_or_shift");
  double lumiScale = ( process_string != "data_obs" ) ? cfg_analyze.getParameter<double>("lumiScale") : 1.;
  bool apply_genWeight = cfg_analyze.getParameter<bool>("apply_genWeight");
  bool apply_trigger_bits = cfg_analyze.getParameter<bool>("apply_trigger_bits");

  const edm::ParameterSet additionalEvtWeight = cfg_analyze.getParameter<edm::ParameterSet>("evtWeight");
  const bool applyAdditionalEvtWeight = additionalEvtWeight.getParameter<bool>("apply");
  EvtWeightManager * eventWeightManager = nullptr;
  if(applyAdditionalEvtWeight)
  {
    eventWeightManager = new EvtWeightManager(additionalEvtWeight);
  }

  bool isDEBUG = cfg_analyze.getParameter<bool>("isDEBUG");
  if ( isDEBUG ) std::cout << "Warning: DEBUG mode enabled -> trigger selection will not be applied for data !!" << std::endl;

  checkOptionValidity(central_or_shift, isMC);
  const int jetPt_option     = getJet_option       (central_or_shift, isMC);
  const int hadTauPt_option  = getHadTauPt_option  (central_or_shift);
  const int lheScale_option  = getLHEscale_option  (central_or_shift);
  const int jetBtagSF_option = getBTagWeight_option(central_or_shift);
  const int met_option       = getMET_option       (central_or_shift, isMC);

  std::cout
    << "central_or_shift = "               << central_or_shift           << "\n"
       " -> hadTauPt_option            = " << hadTauPt_option            << "\n"
       " -> lheScale_option            = " << lheScale_option            << "\n"
       " -> jetBtagSF_option           = " << jetBtagSF_option           << "\n"
       " -> met_option                 = " << met_option                 << "\n"
       " -> jetPt_option               = " << jetPt_option               << '\n'
  ;

  edm::ParameterSet cfg_dataToMCcorrectionInterface;
  cfg_dataToMCcorrectionInterface.addParameter<std::string>("era", era_string);
  cfg_dataToMCcorrectionInterface.addParameter<std::string>("hadTauSelection", hadTauSelection_part2);
  cfg_dataToMCcorrectionInterface.addParameter<int>("hadTauSelection_antiElectron", hadTauSelection_antiElectron);
  cfg_dataToMCcorrectionInterface.addParameter<int>("hadTauSelection_antiMuon", hadTauSelection_antiMuon);
  cfg_dataToMCcorrectionInterface.addParameter<std::string>("central_or_shift", central_or_shift);
  Data_to_MC_CorrectionInterface_Base * dataToMCcorrectionInterface = nullptr;
  switch(era)
  {
    case kEra_2016: dataToMCcorrectionInterface = new Data_to_MC_CorrectionInterface_2016(cfg_dataToMCcorrectionInterface); break;
    case kEra_2017: dataToMCcorrectionInterface = new Data_to_MC_CorrectionInterface_2017(cfg_dataToMCcorrectionInterface); break;
    case kEra_2018: dataToMCcorrectionInterface = new Data_to_MC_CorrectionInterface_2018(cfg_dataToMCcorrectionInterface); break;
    default: throw cmsException("analyze_hadTopTagger_gen", __LINE__) << "Invalid era = " << era;
  }

  std::string branchName_electrons = cfg_analyze.getParameter<std::string>("branchName_electrons");
  std::string branchName_muons = cfg_analyze.getParameter<std::string>("branchName_muons");
  std::string branchName_hadTaus = cfg_analyze.getParameter<std::string>("branchName_hadTaus");
  std::string branchName_jets = cfg_analyze.getParameter<std::string>("branchName_jets");
  std::string branchName_jetsHTTv2 = cfg_analyze.getParameter<std::string>("branchName_jetsHTTv2");
  std::string branchName_subjetsHTTv2 = cfg_analyze.getParameter<std::string>("branchName_subjetsHTTv2");
  std::string branchName_jetsAK12 = cfg_analyze.getParameter<std::string>("branchName_jetsAK12");
  std::string branchName_subjetsAK12 = cfg_analyze.getParameter<std::string>("branchName_subjetsAK12");
  std::string branchName_met = cfg_analyze.getParameter<std::string>("branchName_met");

  std::string branchName_genLeptons = cfg_analyze.getParameter<std::string>("branchName_genLeptons");
  std::string branchName_genHadTaus = cfg_analyze.getParameter<std::string>("branchName_genHadTaus");
  std::string branchName_genJets = cfg_analyze.getParameter<std::string>("branchName_genJets");

  std::string branchName_genTopQuarks = cfg_analyze.getParameter<std::string>("branchName_genTopQuarks");
  std::string branchName_genBJets = cfg_analyze.getParameter<std::string>("branchName_genBJets");
  std::string branchName_genWBosons = cfg_analyze.getParameter<std::string>("branchName_genWBosons");
  std::string branchName_genWJets = cfg_analyze.getParameter<std::string>("branchName_genWJets");
  std::string branchName_genQuarkFromTop = cfg_analyze.getParameter<std::string>("branchName_genQuarkFromTop");
 
  bool redoGenMatching = cfg_analyze.getParameter<bool>("redoGenMatching");

  std::string selEventsFileName_input = cfg_analyze.getParameter<std::string>("selEventsFileName_input");
  std::cout << "selEventsFileName_input = " << selEventsFileName_input << std::endl;
  RunLumiEventSelector* run_lumi_eventSelector = 0;
  if ( selEventsFileName_input != "" ) {
    edm::ParameterSet cfgRunLumiEventSelector;
    cfgRunLumiEventSelector.addParameter<std::string>("inputFileName", selEventsFileName_input);
    cfgRunLumiEventSelector.addParameter<std::string>("separator", ":");
    run_lumi_eventSelector = new RunLumiEventSelector(cfgRunLumiEventSelector);
  }

  std::string selEventsFileName_output = cfg_analyze.getParameter<std::string>("selEventsFileName_output");
  std::string selEventsFileName_output_boosted = cfg_analyze.getParameter<std::string>("selEventsFileName_output_boosted");
  std::string selEventsFileName_output_semiboosted = cfg_analyze.getParameter<std::string>("selEventsFileName_output_semiboosted");
  std::string selEventsFileName_output_resolved = cfg_analyze.getParameter<std::string>("selEventsFileName_output_resolved");

  fwlite::InputSource inputFiles(cfg);
  int maxEvents = inputFiles.maxEvents();
  std::cout << " maxEvents = " << maxEvents << std::endl;
  unsigned reportEvery = inputFiles.reportAfter();

  fwlite::OutputFiles outputFile(cfg);
  fwlite::TFileService fs = fwlite::TFileService(outputFile.file().data());

  TTreeWrapper * inputTree = new TTreeWrapper(treeName.data(), inputFiles.files(), maxEvents);

  std::cout << "Loaded " << inputTree -> getFileCount() << " file(s).\n";

//--- declare event-level variables
  EventInfo eventInfo(isSignal, isMC, isMC_tH);
  EventInfoReader eventInfoReader(&eventInfo);
  inputTree -> registerReader(&eventInfoReader);

  hltPathReader hltPathReader_instance({ triggers_1e, triggers_2e, triggers_1mu, triggers_2mu, triggers_1e1mu });
  inputTree -> registerReader(&hltPathReader_instance);

  if(eventWeightManager)
  {
    inputTree->registerReader(eventWeightManager);
  }

//--- declare particle collections
  const bool readGenObjects = isMC && !redoGenMatching;
  RecoMuonReader* muonReader = new RecoMuonReader(era, branchName_muons, readGenObjects);
  inputTree -> registerReader(muonReader);
  RecoMuonCollectionGenMatcher muonGenMatcher;
  RecoMuonCollectionSelectorLoose preselMuonSelector(era);
  RecoMuonCollectionSelectorFakeable fakeableMuonSelector(era);
  RecoMuonCollectionSelectorTight tightMuonSelector(era);

  RecoElectronReader* electronReader = new RecoElectronReader(era, branchName_electrons, readGenObjects);
  inputTree -> registerReader(electronReader);
  RecoElectronCollectionGenMatcher electronGenMatcher;
  RecoElectronCollectionCleaner electronCleaner(0.05);
  RecoElectronCollectionSelectorLoose preselElectronSelector(era);
  RecoElectronCollectionSelectorFakeable fakeableElectronSelector(era);
  RecoElectronCollectionSelectorTight tightElectronSelector(era);

  RecoHadTauReader* hadTauReader = new RecoHadTauReader(era, branchName_hadTaus, readGenObjects);
  hadTauReader->setHadTauPt_central_or_shift(hadTauPt_option);
  inputTree -> registerReader(hadTauReader);
  RecoHadTauCollectionGenMatcher hadTauGenMatcher;
  RecoHadTauCollectionCleaner hadTauCleaner(0.3);
  RecoHadTauCollectionSelectorLoose preselHadTauSelector(era);
  if ( hadTauSelection_part2 == "dR03mvaVLoose" || hadTauSelection_part2 == "dR03mvaVVLoose" ) preselHadTauSelector.set(hadTauSelection_part2);
  preselHadTauSelector.set_min_antiElectron(hadTauSelection_antiElectron);
  preselHadTauSelector.set_min_antiMuon(hadTauSelection_antiMuon);
  RecoHadTauCollectionSelectorFakeable fakeableHadTauSelector(era);
  if ( hadTauSelection_part2 == "dR03mvaVLoose" || hadTauSelection_part2 == "dR03mvaVVLoose" ) fakeableHadTauSelector.set(hadTauSelection_part2);
  fakeableHadTauSelector.set_min_antiElectron(hadTauSelection_antiElectron);
  fakeableHadTauSelector.set_min_antiMuon(hadTauSelection_antiMuon);
  RecoHadTauCollectionSelectorTight tightHadTauSelector(era);
  if ( hadTauSelection_part2 != "" ) tightHadTauSelector.set(hadTauSelection_part2);
  tightHadTauSelector.set_min_antiElectron(hadTauSelection_antiElectron);
  tightHadTauSelector.set_min_antiMuon(hadTauSelection_antiMuon);
  RecoHadTauSelectorTight tightHadTauFilter(era);
  tightHadTauFilter.set("dR03mvaMedium");
  tightHadTauFilter.set_min_antiElectron(hadTauSelection_antiElectron);
  tightHadTauFilter.set_min_antiMuon(hadTauSelection_antiMuon);

  RecoJetReader* jetReader = new RecoJetReader(era, isMC, branchName_jets, readGenObjects);
  jetReader->setPtMass_central_or_shift(jetPt_option);
  jetReader->setBranchName_BtagWeight(jetBtagSF_option);
  inputTree -> registerReader(jetReader);
  RecoJetCollectionGenMatcher jetGenMatcher;
  RecoJetCollectionCleaner jetCleaner(0.4);
  RecoJetCollectionSelector jetSelector(era);
  //-----------------------------------------------------------------------------
  // CV: only for testing
  jetSelector.getSelector().set_min_pt(-1.);
  jetSelector.getSelector().set_max_absEta(4.7);
  jetSelector.getSelector().set_min_jetId(-1);
  //-----------------------------------------------------------------------------
  RecoJetCollectionSelectorBtagLoose jetSelectorBtagLoose(era);
  RecoJetCollectionSelectorBtagMedium jetSelectorBtagMedium(era);

  RecoJetReaderHTTv2* jetReaderHTTv2 = new RecoJetReaderHTTv2(era, branchName_jetsHTTv2, branchName_subjetsHTTv2);
  inputTree -> registerReader(jetReaderHTTv2);
  RecoJetSelectorHTTv2 jetSelectorHTTv2(era);

  RecoJetReaderAK12* jetReaderAK12 = new RecoJetReaderAK12(era, branchName_jetsAK12, branchName_subjetsAK12);
  inputTree -> registerReader(jetReaderAK12);
  RecoJetSelectorAK12 jetSelectorAK12(era);

//--- declare missing transverse energy
  RecoMEtReader* metReader = new RecoMEtReader(era, isMC, branchName_met);
  metReader->setMEt_central_or_shift(met_option);
  inputTree -> registerReader(metReader);

//--- declare generator level information
  GenLeptonReader* genLeptonReader = 0;
  GenHadTauReader* genHadTauReader = 0;
  GenJetReader* genJetReader = 0;
  LHEInfoReader* lheInfoReader = 0;
  if ( isMC ) {
    if ( !readGenObjects ) {
      if ( branchName_genLeptons != "" ) {
        genLeptonReader = new GenLeptonReader(branchName_genLeptons);
        inputTree -> registerReader(genLeptonReader);
      }
      if ( branchName_genHadTaus != "" ) {
        genHadTauReader = new GenHadTauReader(branchName_genHadTaus);
        inputTree -> registerReader(genHadTauReader);
      }
      if ( branchName_genJets != "" ) {
        genJetReader = new GenJetReader(branchName_genJets);
        inputTree -> registerReader(genJetReader);
      }
    }
    lheInfoReader = new LHEInfoReader(hasLHE);
    inputTree -> registerReader(lheInfoReader);
  }

  GenParticleReader* genTopQuarkReader = new GenParticleReader(branchName_genTopQuarks);
  GenParticleReader* genBJetReader = new GenParticleReader(branchName_genBJets);
  GenParticleReader* genWBosonReader = new GenParticleReader(branchName_genWBosons);
  GenParticleReader* genWJetReader = new GenParticleReader(branchName_genWJets);
  GenParticleReader* genQuarkFromTopReader = new GenParticleReader(branchName_genQuarkFromTop);
  
  if ( isMC ) {
    inputTree->registerReader(genTopQuarkReader);
    inputTree->registerReader(genBJetReader);
    inputTree->registerReader(genWBosonReader);
    inputTree->registerReader(genWJetReader);
    inputTree->registerReader(genQuarkFromTopReader);
  }

  int analyzedEntries = 0;
  int selectedEntries = 0;
  double selectedEntries_weighted = 0.;
  TH1* histogram_analyzedEntries = fs.make<TH1D>("analyzedEntries", "analyzedEntries", 1, -0.5, +0.5);
  TH1* histogram_selectedEntries = fs.make<TH1D>("selectedEntries", "selectedEntries", 1, -0.5, +0.5);

  TH1* histogram_ptTop = fs.make<TH1D>("ptTop", "ptTop", 100, 0., 500.);
  TH1* histogram_etaTop = fs.make<TH1D>("etaTop", "etaTop", 100, -5.0, +5.0);
  TH1* histogram_dRmaxTop = fs.make<TH1D>("dRmaxTop", "dRmaxTop", 200, -0.01, 9.99);
  TH1* histogram_ptW = fs.make<TH1D>("ptW", "ptW", 100, 0., 500.);
  TH1* histogram_etaW = fs.make<TH1D>("etaW", "etaW", 100, -5.0, +5.0);
  TH1* histogram_dRmaxW = fs.make<TH1D>("dRmaxW", "dRmaxW", 200, -0.01, 9.99);
  TH1* histogram_dRmaxW_dRmaxTopGt1p2 = fs.make<TH1D>("dRmaxW_dRmaxTopGt1p2", "dRmaxW_dRmaxTopGt1p2", 200, -0.01, 9.99);
  TH1* histogram_dRmaxW_dRmaxTopGt1p5 = fs.make<TH1D>("dRmaxW_dRmaxTopGt1p5", "dRmaxW_dRmaxTopGt1p5", 200, -0.01, 9.99);
  TH1* histogram_ptB = fs.make<TH1D>("ptB", "ptB", 100, 0., 500.);
  TH1* histogram_etaB = fs.make<TH1D>("etaB", "etaB", 100, -5.0, +5.0);

  histManager_jetsHTTv2 = new JetHistManagerHTTv2(makeHistManager_cfg(process_string,
    Form("%s/sel/jetsHTTv2", histogramDir.data()), central_or_shift));
  histManager_jetsHTTv2->bookHistograms(fs);
  histogram_HTTv2_W_ptRec_div_ptGen = fs.make<TH1D>("HTTv2_W_ptRec_div_ptGen", "HTTv2_W_ptRec_div_ptGen", 200, 0., 2.);
  histogram_HTTv2_mW = fs.make<TH1D>("HTTv2_mW", "HTTv2_mW", 200, 0., 200.);
  histogram_HTTv2_Top_ptRec_div_ptGen = fs.make<TH1D>("HTTv2_Top_ptRec_div_ptGen", "HTTv2_Top_ptRec_div_ptGen", 200, 0., 2.);
  histogram_HTTv2_mTop = fs.make<TH1D>("HTTv2_mTop", "HTTv2_mTop", 300, 0., 300.);
  histogram_HTTv2_WJet1_ptRec_div_ptGen = fs.make<TH1D>("HTTv2_WJet1_ptRec_div_ptGen", "HTTv2_WJet1_ptRec_div_ptGen", 200, 0., 2.);
  histogram_HTTv2_WJet1_dRmatch = fs.make<TH1D>("HTTv2_WJet1_dRmatch", "HTTv2_WJet1_dRmatch", 100, 0., 1.);
  histogram_HTTv2_WJet1_cosThetaStar = fs.make<TH1D>("HTTv2_WJet1_cosThetaStar", "HTTv2_WJet1_cosThetaStar", 36, 0., TMath::Pi());
  histogram_HTTv2_WJet2_ptRec_div_ptGen = fs.make<TH1D>("HTTv2_WJet2_ptRec_div_ptGen", "HTTv2_WJet2_ptRec_div_ptGen", 200, 0., 2.);
  histogram_HTTv2_WJet2_dRmatch = fs.make<TH1D>("HTTv2_WJet2_dRmatch", "HTTv2_WJet2_dRmatch", 100, 0., 1.);
  histogram_HTTv2_BJet_ptRec_div_ptGen = fs.make<TH1D>("HTTv2_BJet_ptRec_div_ptGen", "HTTv2_BJet_ptRec_div_ptGen", 200, 0., 2.);
  histogram_HTTv2_BJet_dRmatch = fs.make<TH1D>("HTTv2_BJet_dRmatch", "HTTv2_BJet_dRmatch", 100, 0., 1.);
  histogram_HTTv2_BJet_cosThetaStar = fs.make<TH1D>("HTTv2_BJet_cosThetaStar", "HTTv2_BJet_cosThetaStar", 36, 0., TMath::Pi());

  histogram_HTTv2_GenTop_dRmin = fs.make<TH1D>("HTTv2_GenTop_dRmin", "dRMin(HTTv2 and GenTop)", 100, 0., 1.);
  histogram_HTTv2Pt_div_GenTopPt_dRmin = fs.make<TH1D>("HTTv2Pt_div_GenTopPt_dRminHTTv2_GenTop_dRmin", "", 200, 0., 2.);
  histogram_HTTv2_GenTop_dRmin_vs_HTTv2Pt_div_GenTopPt = fs.make<TH2D>("histogram_HTTv2_GenTop_dRmin_vs_HTTv2Pt_div_GenTopPt", "", 200, 0., 2., 100, 0., 1.);


  JetHistManagerAK12* histManager_jetsAK12 = new JetHistManagerAK12(makeHistManager_cfg(process_string,
    Form("%s/sel/jetsAK12", histogramDir.data()), central_or_shift));
  histManager_jetsAK12->bookHistograms(fs);
  JetHistManagerAK12* histManager_jetsAK12_notHTTv2 = new JetHistManagerAK12(makeHistManager_cfg(process_string,
    Form("%s/sel/jetsAK12_notHTTv2", histogramDir.data()), central_or_shift));
  histManager_jetsAK12_notHTTv2->bookHistograms(fs);
  TH1* histogram_AK12_W_ptRec_div_ptGen = fs.make<TH1D>("AK12_W_ptRec_div_ptGen", "AK12_W_ptRec_div_ptGen", 200, 0., 2.);
  TH1* histogram_AK12_mW = fs.make<TH1D>("AK12_mW", "AK12_mW", 200, 0., 200.);
  TH1* histogram_AK12_WJet1_ptRec_div_ptGen = fs.make<TH1D>("AK12_WJet1_ptRec_div_ptGen", "AK12_WJet1_ptRec_div_ptGen", 200, 0., 2.);
  TH1* histogram_AK12_WJet1_dRmatch = fs.make<TH1D>("AK12_WJet1_dRmatch", "AK12_WJet1_dRmatch", 100, 0., 1.);
  TH1* histogram_AK12_WJet1_cosThetaStar = fs.make<TH1D>("AK12_WJet1_cosThetaStar", "AK12_WJet1_cosThetaStar", 36, 0., TMath::Pi());
  TH1* histogram_AK12_WJet2_ptRec_div_ptGen = fs.make<TH1D>("AK12_WJet2_ptRec_div_ptGen", "AK12_WJet2_ptRec_div_ptGen", 200, 0., 2.);
  TH1* histogram_AK12_WJet2_dRmatch = fs.make<TH1D>("AK12_WJet2_dRmatch", "AK12_WJet2_dRmatch", 100, 0., 1.);
  TH1* histogram_AK12_BJet_cosThetaStar = fs.make<TH1D>("AK12_BJet_cosThetaStar", "AK12_BJet_cosThetaStar", 36, 0., TMath::Pi());
  TH1* histogram_AK12_theta_t_lead = fs.make<TH1D>("AK12_theta_t_lead", "AK12_theta_t_lead", 36, 0., TMath::Pi());
  TH1* histogram_AK12_theta_t_sublead = fs.make<TH1D>("AK12_theta_t_sublead", "AK12_theta_t_sublead", 36, 0., TMath::Pi());

  TH1* histogram_resolved_WJet1_cosThetaStar = fs.make<TH1D>("resolved_WJet1_cosThetaStar", "resolved_WJet1_cosThetaStar", 36, 0., TMath::Pi());
  TH1* histogram_resolved_BJet_cosThetaStar = fs.make<TH1D>("resolved_BJet_cosThetaStar", "resolved_BJet_cosThetaStar", 36, 0., TMath::Pi());
  TH1* histogram_resolved_theta_t_lead = fs.make<TH1D>("resolved_theta_t_lead", "resolved_theta_t_lead", 36, 0., TMath::Pi());
  TH1* histogram_resolved_theta_t_sublead = fs.make<TH1D>("resolved_theta_t_sublead", "resolved_theta_t_sublead", 36, 0., TMath::Pi());

//--- open output file containing run:lumi:event numbers of events passing final event selection criteria
  std::ostream* selEventsFile = ( selEventsFileName_output != "" ) ? new std::ofstream(selEventsFileName_output.data(), std::ios::out) : 0;
  std::cout << "selEventsFileName_output = " << selEventsFileName_output << std::endl;
  std::ostream* selEventsFile_boosted = ( selEventsFileName_output_boosted != "" ) ? new std::ofstream(selEventsFileName_output_boosted.data(), std::ios::out) : 0;
  std::cout << "selEventsFileName_output_boosted = " << selEventsFileName_output_boosted << std::endl;
  std::ostream* selEventsFile_semiboosted = ( selEventsFileName_output_semiboosted != "" ) ? new std::ofstream(selEventsFileName_output_semiboosted.data(), std::ios::out) : 0;
  std::cout << "selEventsFileName_output_semiboosted = " << selEventsFileName_output_semiboosted << std::endl;
  std::ostream* selEventsFile_resolved = ( selEventsFileName_output_resolved != "" ) ? new std::ofstream(selEventsFileName_output_resolved.data(), std::ios::out) : 0;
  std::cout << "selEventsFileName_output_resolved = " << selEventsFileName_output_resolved << std::endl;

  while(inputTree -> hasNextEvent() && (! run_lumi_eventSelector || (run_lumi_eventSelector && ! run_lumi_eventSelector -> areWeDone())))
  {
    if ( isDEBUG ) {
      std::cout << "processing run = " << eventInfo.run << ", ls = " << eventInfo.lumi << ", event = " << eventInfo.event << std::endl;
    }

    if(inputTree -> canReport(reportEvery) )
    {
      std::cout << "processing Entry " << inputTree -> getCurrentMaxEventIdx()
                << " or " << inputTree -> getCurrentEventIdx() << " entry in #"
                << (inputTree -> getProcessedFileCount() - 1)
                << " (" << eventInfo
                << ") file (" << selectedEntries << " Entries selected)"<<std::endl;
    }
    ++analyzedEntries;
    histogram_analyzedEntries->Fill(0.);

    if (run_lumi_eventSelector && !(*run_lumi_eventSelector)(eventInfo))
    {
      continue;
    }


//--- build collections of electrons, muons and hadronic taus;
//    resolve overlaps in order of priority: muon, electron,
    std::vector<RecoMuon> muons = muonReader->read();
    std::vector<const RecoMuon*> muon_ptrs = convert_to_ptrs(muons);
    std::vector<const RecoMuon*> cleanedMuons = muon_ptrs; // CV: no cleaning needed for muons, as they have the highest priority in the overlap removal
    std::vector<const RecoMuon*> preselMuons = preselMuonSelector(cleanedMuons);
    std::vector<const RecoMuon*> fakeableMuons = fakeableMuonSelector(preselMuons);
    std::vector<const RecoMuon*> tightMuons = tightMuonSelector(preselMuons);
    std::vector<const RecoMuon*> selMuons;
    if      ( leptonSelection == kLoose    ) selMuons = preselMuons;
    else if ( leptonSelection == kFakeable ) selMuons = fakeableMuons;
    else if ( leptonSelection == kTight    ) selMuons = tightMuons;
    else assert(0);
    //if ( isDEBUG ) {
    //  for ( size_t idxPreselMuon = 0; idxPreselMuon < preselMuons.size(); ++idxPreselMuon ) {
    //    std::cout << "preselMuon #" << idxPreselMuon << ":" << std::endl;
    //    std::cout << (*preselMuons[idxPreselMuon]);
    //  }
    //  for ( size_t idxSelMuon = 0; idxSelMuon < selMuons.size(); ++idxSelMuon ) {
    //    std::cout << "selMuon #" << idxSelMuon << ":" << std::endl;
    //    std::cout << (*selMuons[idxSelMuon]);
    //  }
    //}

    std::vector<RecoElectron> electrons = electronReader->read();
    std::vector<const RecoElectron*> electron_ptrs = convert_to_ptrs(electrons);
    std::vector<const RecoElectron*> cleanedElectrons = electronCleaner(electron_ptrs, selMuons);
    std::vector<const RecoElectron*> preselElectrons = preselElectronSelector(cleanedElectrons);
    std::vector<const RecoElectron*> fakeableElectrons = fakeableElectronSelector(preselElectrons);
    std::vector<const RecoElectron*> tightElectrons = tightElectronSelector(preselElectrons);
    std::vector<const RecoElectron*> selElectrons;
    if      ( leptonSelection == kLoose    ) selElectrons = preselElectrons;
    else if ( leptonSelection == kFakeable ) selElectrons = fakeableElectrons;
    else if ( leptonSelection == kTight    ) selElectrons = tightElectrons;
    else assert(0);
    //if ( isDEBUG ) {
    //  for ( size_t idxPreselElectron = 0; idxPreselElectron < preselElectrons.size(); ++idxPreselElectron ) {
    //    std::cout << "preselElectron #" << idxPreselElectron << ":" << std::endl;
    //    std::cout << (*preselElectrons[idxPreselElectron]);
    //  }
    //  for ( size_t idxSelElectron = 0; idxSelElectron < selElectrons.size(); ++idxSelElectron ) {
    //    std::cout << "selElectron #" << idxSelElectron << ":" << std::endl;
    //    std::cout << (*selElectrons[idxSelElectron]);
    //  }
    //}

    std::vector<const RecoLepton*> selLeptons = mergeLeptonCollections(selElectrons, selMuons, isHigherPt);
    std::vector<RecoHadTau> hadTaus = hadTauReader->read();
    std::vector<const RecoHadTau*> hadTau_ptrs = convert_to_ptrs(hadTaus);
    std::vector<const RecoHadTau*> cleanedHadTaus = hadTauCleaner(hadTau_ptrs, preselMuons, preselElectrons);
    std::vector<const RecoHadTau*> preselHadTaus = preselHadTauSelector(cleanedHadTaus);
    std::vector<const RecoHadTau*> fakeableHadTaus = fakeableHadTauSelector(cleanedHadTaus);
    std::vector<const RecoHadTau*> tightHadTaus = tightHadTauSelector(cleanedHadTaus);
    std::vector<const RecoHadTau*> selHadTaus;
    if      ( hadTauSelection == kLoose    ) selHadTaus = preselHadTaus;
    else if ( hadTauSelection == kFakeable ) selHadTaus = fakeableHadTaus;
    else if ( hadTauSelection == kTight    ) selHadTaus = tightHadTaus;
    else assert(0);
    //if ( isDEBUG ) {
    //  for ( size_t idxPreselHadTau = 0; idxPreselHadTau < preselHadTaus.size(); ++idxPreselHadTau ) {
    //    std::cout << "preselHadTau #" << idxPreselHadTau << ":" << std::endl;
    //    std::cout << (*preselHadTaus[idxPreselHadTau]);
    //  }
    //  for ( size_t idxSelHadTau = 0; idxSelHadTau < selHadTaus.size(); ++idxSelHadTau ) {
    //    std::cout << "selHadTau #" << idxSelHadTau << ":" << std::endl;
    //    std::cout << (*selHadTaus[idxSelHadTau]);
    //  }
    //}
    selHadTaus = pickFirstNobjects(selHadTaus, 1);



//--- build collections of jets and select subset of jets passing b-tagging criteria
    std::vector<RecoJet> jets = jetReader->read();
    std::vector<const RecoJet*> jet_ptrs = convert_to_ptrs(jets);
    std::vector<const RecoJet*> cleanedJets = jetCleaner(jet_ptrs, fakeableMuons, fakeableElectrons, fakeableHadTaus);
    // selLeptons for BDT training is loose, and loose>fakeable
    // this has no effect on datacards making as there selLeptons are tight and tight<fakeable
    std::vector<const RecoJet*> selJets = jetSelector(cleanedJets);
    std::vector<const RecoJet*> selBJets_loose = jetSelectorBtagLoose(cleanedJets);
    std::vector<const RecoJet*> selBJets_medium = jetSelectorBtagMedium(cleanedJets);

//--- build collections of jets reconstructed by hep-top-tagger (HTTv2) algorithm
    std::vector<RecoJetHTTv2> jetsHTTv2 = jetReaderHTTv2->read();
    std::vector<const RecoJetHTTv2*> jet_ptrsHTTv2 = convert_to_ptrs(jetsHTTv2);

//--- build collections of jets reconstructed by anti-kT algorithm with dR=1.2 (AK12)
    std::vector<RecoJetAK12> jetsAK12 = jetReaderAK12->read();
    std::vector<const RecoJetAK12*> jet_ptrsAK12 = convert_to_ptrs(jetsAK12);



//--- build collections of generator level particles (after some cuts are applied, to safe computing time)
    std::vector<GenLepton> genLeptons;
    std::vector<GenLepton> genElectrons;
    std::vector<GenLepton> genMuons;
    std::vector<GenHadTau> genHadTaus;
    std::vector<GenJet> genJets;
    if ( isMC && redoGenMatching ) {
      if ( genLeptonReader ) {
	genLeptons = genLeptonReader->read();
	for ( std::vector<GenLepton>::const_iterator genLepton = genLeptons.begin();
	      genLepton != genLeptons.end(); ++genLepton ) {
	  int abs_pdgId = std::abs(genLepton->pdgId());
	  if      ( abs_pdgId == 11 ) genElectrons.push_back(*genLepton);
	  else if ( abs_pdgId == 13 ) genMuons.push_back(*genLepton);
	}
      }
      if ( genHadTauReader ) {
	genHadTaus = genHadTauReader->read();
      }
      if ( genJetReader ) {
	genJets = genJetReader->read();
      }
    }

//--- match reconstructed to generator level particles
    if ( isMC && redoGenMatching ) {
      muonGenMatcher.addGenLeptonMatch(preselMuons, genLeptons, 0.2);
      muonGenMatcher.addGenHadTauMatch(preselMuons, genHadTaus, 0.2);
      muonGenMatcher.addGenJetMatch(preselMuons, genJets, 0.2);

      electronGenMatcher.addGenLeptonMatch(preselElectrons, genLeptons, 0.2);
      electronGenMatcher.addGenHadTauMatch(preselElectrons, genHadTaus, 0.2);
      electronGenMatcher.addGenJetMatch(preselElectrons, genJets, 0.2);

      hadTauGenMatcher.addGenLeptonMatch(selHadTaus, genLeptons, 0.2);
      hadTauGenMatcher.addGenHadTauMatch(selHadTaus, genHadTaus, 0.2);
      hadTauGenMatcher.addGenJetMatch(selHadTaus, genJets, 0.2);

      jetGenMatcher.addGenLeptonMatch(selJets, genLeptons, 0.2);
      jetGenMatcher.addGenHadTauMatch(selJets, genHadTaus, 0.2);
      jetGenMatcher.addGenJetMatch(selJets, genJets, 0.2);
    }


#ifndef DoNotUse2lss_1tauConditions
#pragma message ("Warning*** DoNotUse2lss_1tauConditions is not defined")

		bool isTriggered_1e = hltPaths_isTriggered(triggers_1e) || (isMC && !apply_trigger_bits);
    bool isTriggered_2e = hltPaths_isTriggered(triggers_2e) || (isMC && !apply_trigger_bits);
    bool isTriggered_1mu = hltPaths_isTriggered(triggers_1mu) || (isMC && !apply_trigger_bits);
    bool isTriggered_2mu = hltPaths_isTriggered(triggers_2mu) || (isMC && !apply_trigger_bits);
    bool isTriggered_1e1mu = hltPaths_isTriggered(triggers_1e1mu) || (isMC && !apply_trigger_bits);

    bool selTrigger_1e = use_triggers_1e && isTriggered_1e;
    bool selTrigger_2e = use_triggers_2e && isTriggered_2e;
    bool selTrigger_1mu = use_triggers_1mu && isTriggered_1mu;
    bool selTrigger_2mu = use_triggers_2mu && isTriggered_2mu;
    bool selTrigger_1e1mu = use_triggers_1e1mu && isTriggered_1e1mu;
    if ( !(selTrigger_1e || selTrigger_2e || selTrigger_1mu || selTrigger_2mu || selTrigger_1e1mu) ) {
      continue;
    }

//--- rank triggers by priority and ignore triggers of lower priority if a trigger of higher priority has fired for given event;
//    the ranking of the triggers is as follows: 2mu, 1e1mu, 2e, 1mu, 1e
// CV: this logic is necessary to avoid that the same event is selected multiple times when processing different primary datasets
    if ( !isMC && !isDEBUG ) {
      if ( selTrigger_1e && (isTriggered_2e || isTriggered_1mu || isTriggered_2mu || isTriggered_1e1mu) ) {
	continue;
      }
      if ( selTrigger_2e && (isTriggered_2mu || isTriggered_1e1mu) ) {
	continue;
      }
      if ( selTrigger_1mu && (isTriggered_2e || isTriggered_2mu || isTriggered_1e1mu) ) {
	continue;
      }
      if ( selTrigger_1e1mu && isTriggered_2mu ) {
	continue;
      }
    }
    cutFlowTable_2lss_1tau.update("trigger");

    if ( (selTrigger_2mu   && !apply_offline_e_trigger_cuts_2mu)   ||
	 (selTrigger_1mu   && !apply_offline_e_trigger_cuts_1mu)   ||
	 (selTrigger_2e    && !apply_offline_e_trigger_cuts_2e)    ||
	 (selTrigger_1e1mu && !apply_offline_e_trigger_cuts_1e1mu) ||
	 (selTrigger_1e    && !apply_offline_e_trigger_cuts_1e)    ) {
      fakeableElectronSelector.disable_offline_e_trigger_cuts();
      tightElectronSelector.disable_offline_e_trigger_cuts();
    } else {
      fakeableElectronSelector.enable_offline_e_trigger_cuts();
      tightElectronSelector.enable_offline_e_trigger_cuts();
    }


//--- apply preselection
    std::vector<const RecoLepton*> preselLeptons = mergeLeptonCollections(preselElectrons, preselMuons, isHigherConePt);
    // require at least two leptons passing loose preselection criteria
    if ( !(preselLeptons.size() >= 2) ) {
      continue;
    }
    cutFlowTable_2lss_1tau.update(">= 2 presel leptons");
    const RecoLepton* preselLepton_lead = preselLeptons[0];
    const RecoLepton* preselLepton_sublead = preselLeptons[1];
    const leptonGenMatchEntry& preselLepton_genMatch = getLeptonGenMatch(leptonGenMatch_definitions, preselLepton_lead, preselLepton_sublead);
    int idxPreselLepton_genMatch = preselLepton_genMatch.idx_;
    assert(idxPreselLepton_genMatch != kGen_LeptonUndefined2);

    // require that trigger paths match event category (with event category based on preselLeptons)
    if ( !((preselElectrons.size() >= 2 &&                            (selTrigger_2e    || selTrigger_1e                  )) ||
	   (preselElectrons.size() >= 1 && preselMuons.size() >= 1 && (selTrigger_1e1mu || selTrigger_1mu || selTrigger_1e)) ||
	   (                               preselMuons.size() >= 2 && (selTrigger_2mu   || selTrigger_1mu                 ))) ) {
      continue;
    }
    cutFlowTable_2lss_1tau.update("presel lepton trigger match");

    // apply requirement on jets (incl. b-tagged jets) and hadronic taus on preselection level
    if ( !(selJets.size() >= 2) ) {
      continue;
    }
    cutFlowTable_2lss_1tau.update(">= 2 jets");
    if ( !(selBJets_loose.size() >= 2 || selBJets_medium.size() >= 1) ) {
    }
    cutFlowTable_2lss_1tau.update(">= 2 loose b-jets || 1 medium b-jet (1)");

    if ( !(selHadTaus.size() >= 1) ) {
      continue;
    }
    cutFlowTable_2lss_1tau.update(">= 1 sel tau (1)");
    const RecoHadTau* selHadTau = selHadTaus[0];
    const hadTauGenMatchEntry& selHadTau_genMatch = getHadTauGenMatch(hadTauGenMatch_definitions, selHadTau);
    int idxSelHadTau_genMatch = selHadTau_genMatch.idx_;
    assert(idxSelHadTau_genMatch != kGen_HadTauUndefined1);

//--- compute MHT and linear MET discriminant (met_LD)
    RecoMEt met = metReader->read();
    std::vector<const RecoLepton*> fakeableLeptons = mergeLeptonCollections(fakeableElectrons, fakeableMuons);
    Particle::LorentzVector mht_p4 = compMHT(fakeableLeptons, selHadTaus, selJets);
    double met_LD = compMEt_LD(met.p4(), mht_p4);

//--- apply final event selection
    if ( !(selLeptons.size() >= 2) ) {
      continue;
    }
    cutFlowTable_2lss_1tau.update(">= 2 sel leptons", 1.);
    const RecoLepton* selLepton_lead = selLeptons[0];
    int selLepton_lead_type = getLeptonType(selLepton_lead->pdgId());
    const RecoLepton* selLepton_sublead = selLeptons[1];
    int selLepton_sublead_type = getLeptonType(selLepton_sublead->pdgId());
    const leptonGenMatchEntry& selLepton_genMatch = getLeptonGenMatch(leptonGenMatch_definitions, selLepton_lead, selLepton_sublead);
    int idxSelLepton_genMatch = selLepton_genMatch.idx_;
    assert(idxSelLepton_genMatch != kGen_LeptonUndefined2);

    if ( isMC ) {
      lheInfoReader->read();
    }


//--- compute event-level weight for data/MC correction of b-tagging efficiency and mistag rate
//   (using the method "Event reweighting using scale factors calculated with a tag and probe method",
//    described on the BTV POG twiki https://twiki.cern.ch/twiki/bin/view/CMS/BTagShapeCalibration )
    /*double*/ evtWeight = 1.;
    if ( isMC ) {
      evtWeight *= lumiScale;
      if ( apply_genWeight ) evtWeight *= boost::math::sign(eventInfo.genWeight);
      if ( isMC_tH ) evtWeight *= eventInfo.genWeight_tH;
      evtWeight *= eventInfo.pileupWeight;
      evtWeight *= lheInfoReader->getWeight_scale(lheScale_option);
      double btagWeight = 1.;
      for ( std::vector<const RecoJet*>::const_iterator jet = selJets.begin();
	    jet != selJets.end(); ++jet ) {
	btagWeight *= (*jet)->BtagWeight();
      }
      evtWeight *= btagWeight;
    }

    double weight_data_to_MC_correction = 1.;
    double triggerWeight = 1.;
    if ( isMC ) {
      dataToMCcorrectionInterface->setLeptons(
        selLepton_lead_type, selLepton_lead->pt(), selLepton_lead->eta(),
	selLepton_sublead_type, selLepton_sublead->pt(), selLepton_sublead->eta());

//--- apply trigger efficiency turn-on curves to Spring16 non-reHLT MC
      if ( !apply_trigger_bits ) {
	triggerWeight = dataToMCcorrectionInterface->getWeight_leptonTriggerEff();
	evtWeight *= triggerWeight;
      }

//--- apply data/MC corrections for trigger efficiency
      double sf_triggerEff = dataToMCcorrectionInterface->getSF_leptonTriggerEff();
      triggerWeight *= sf_triggerEff;
      weight_data_to_MC_correction *= sf_triggerEff;

//--- apply data/MC corrections for efficiencies for lepton to pass loose identification and isolation criteria
      weight_data_to_MC_correction *= dataToMCcorrectionInterface->getSF_leptonID_and_Iso_loose();

//--- apply data/MC corrections for efficiencies of leptons passing the loose identification and isolation criteria
//    to also pass the tight identification and isolation criteria
      if ( leptonSelection == kFakeable ) {
	weight_data_to_MC_correction = dataToMCcorrectionInterface->getSF_leptonID_and_Iso_fakeable_to_loose();
      } else if ( leptonSelection == kTight ) {
        weight_data_to_MC_correction = dataToMCcorrectionInterface->getSF_leptonID_and_Iso_tight_to_loose_wTightCharge();
      }

//--- apply data/MC corrections for hadronic tau identification efficiency
//    and for e->tau and mu->tau misidentification rates
      int selHadTau_genPdgId = getHadTau_genPdgId(selHadTau);
      dataToMCcorrectionInterface->setHadTaus(selHadTau_genPdgId, selHadTau->pt(), selHadTau->eta());
      weight_data_to_MC_correction *= dataToMCcorrectionInterface->getSF_hadTauID_and_Iso();
      weight_data_to_MC_correction *= dataToMCcorrectionInterface->getSF_eToTauFakeRate();
      weight_data_to_MC_correction *= dataToMCcorrectionInterface->getSF_muToTauFakeRate();

      evtWeight *= weight_data_to_MC_correction;
    }


    // require exactly two leptons passing tight selection criteria, to avoid overlap with other channels
    std::vector<const RecoLepton*> tightLeptons = mergeLeptonCollections(tightElectrons, tightMuons, isHigherPt);
    if ( !(tightLeptons.size() <= 2) ) {
      continue;
    }
    cutFlowTable_2lss_1tau.update("<= 2 tight leptons", evtWeight);

    // require that trigger paths match event category (with event category based on selLeptons)
    if ( !((selElectrons.size() >= 2 &&                         (selTrigger_2e    || selTrigger_1e                  )) ||
	   (selElectrons.size() >= 1 && selMuons.size() >= 1 && (selTrigger_1e1mu || selTrigger_1mu || selTrigger_1e)) ||
	   (                            selMuons.size() >= 2 && (selTrigger_2mu   || selTrigger_1mu                 ))) ) {
      continue;
    }
    cutFlowTable_2lss_1tau.update("sel lepton trigger match", evtWeight);

    // apply requirement on jets (incl. b-tagged jets) and hadronic taus on level of final event selection
    if ( !(selJets.size() >= 3) ) {
      continue;
    }
    cutFlowTable_2lss_1tau.update(">= 3 jets", evtWeight);

    if ( !(selBJets_loose.size() >= 2 || selBJets_medium.size() >= 1) ) {
      continue;
    }
    cutFlowTable_2lss_1tau.update(">= 2 loose b-jets || 1 medium b-jet (2)", evtWeight);

    if ( !(selHadTaus.size() >= 1) ) {
      continue;
    }
    cutFlowTable_2lss_1tau.update(">= 1 sel tau (2)", evtWeight);

    bool failsLowMassVeto = false;
    for ( std::vector<const RecoLepton*>::const_iterator lepton1 = preselLeptons.begin();
	  lepton1 != preselLeptons.end(); ++lepton1 ) {
      for ( std::vector<const RecoLepton*>::const_iterator lepton2 = lepton1 + 1;
	    lepton2 != preselLeptons.end(); ++lepton2 ) {
	double mass = ((*lepton1)->p4() + (*lepton2)->p4()).mass();
	if ( mass < 12. ) {
	  failsLowMassVeto = true;
	}
      }
    }
    if ( failsLowMassVeto ) {
      continue;
    }
    cutFlowTable_2lss_1tau.update("m(ll) > 12 GeV", evtWeight);

    const double minPt_lead = 25.;
    const double minPt_sublead = selLepton_sublead->is_electron() ? 15. : 10.;
    if ( !(selLepton_lead->pt() > minPt_lead && selLepton_sublead->pt() > minPt_sublead) ) {
      continue;
    }
    cutFlowTable_2lss_1tau.update("lead lepton pT > 25 GeV && sublead lepton pT > 15(e)/10(mu) GeV", evtWeight);

    bool failsTightChargeCut = false;
    for ( std::vector<const RecoLepton*>::const_iterator lepton = selLeptons.begin();
	  lepton != selLeptons.end(); ++lepton ) {
      if ( (*lepton)->is_electron() ) {
	const RecoElectron* electron = dynamic_cast<const RecoElectron*>(*lepton);
	assert(electron);
	if ( electron->tightCharge() < 2 ) failsTightChargeCut = true;
      }
      if ( (*lepton)->is_muon() ) {
	const RecoMuon* muon = dynamic_cast<const RecoMuon*>(*lepton);
	assert(muon);
	if ( muon->tightCharge() < 2 ) failsTightChargeCut = true;
      }
    }
    if ( failsTightChargeCut ) {
      continue;
    }
    cutFlowTable_2lss_1tau.update("tight lepton charge", evtWeight);

    bool isLeptonCharge_SS = selLepton_lead->charge()*selLepton_sublead->charge() > 0;
    bool isLeptonCharge_OS = selLepton_lead->charge()*selLepton_sublead->charge() < 0;
    if ( leptonChargeSelection == kOS && isLeptonCharge_SS ) {
      continue;
    }
    if ( leptonChargeSelection == kSS && isLeptonCharge_OS ) {
      continue;
    }
    cutFlowTable_2lss_1tau.update(Form("sel lepton-pair %s charge", leptonChargeSelection_string.data()), evtWeight);

    if ( apply_lepton_and_hadTauCharge_cut ) {
      if ( !((chargeSumSelection == kOS && std::abs(selLepton_lead->charge() + selLepton_sublead->charge() + selHadTau->charge()) == 1) ||
	     (chargeSumSelection == kSS && std::abs(selLepton_lead->charge() + selLepton_sublead->charge() + selHadTau->charge()) != 1)) ) {
	continue;
      }
      cutFlowTable_2lss_1tau.update(Form("sel lepton+tau %s charge", chargeSumSelection_string.data()), evtWeight);
    }

    bool failsZbosonMassVeto = false;
    for ( std::vector<const RecoLepton*>::const_iterator lepton1 = fakeableLeptons.begin();
	  lepton1 != fakeableLeptons.end(); ++lepton1 ) {
      for ( std::vector<const RecoLepton*>::const_iterator lepton2 = lepton1 + 1;
	    lepton2 != fakeableLeptons.end(); ++lepton2 ) {
	double mass = ((*lepton1)->p4() + (*lepton2)->p4()).mass();
	if ( (*lepton1)->is_electron() && (*lepton2)->is_electron() && std::fabs(mass - z_mass) < z_window ) {
	  failsZbosonMassVeto = true;
	}
      }
    }
    if ( failsZbosonMassVeto ) {
      continue;
    }
    cutFlowTable_2lss_1tau.update("Z-boson mass veto", evtWeight);

    if ( !(fakeableMuons.size() >= 1 || met_LD >= 0.2) ) {
      continue;
    }
    cutFlowTable_2lss_1tau.update("met LD > 0.2", evtWeight);

    if ( selEventsFile ) {
      (*selEventsFile) << eventInfo.run << ':' << eventInfo.lumi << ':' << eventInfo.event << '\n';
    }

#else
#pragma message ("Warning***   2lss_1tau selection conditions will not be executed ")

    /*double*/ evtWeight = 1.;
#endif



//--- build collections of generator level particles
    /*std::vector<GenParticle>*/ genTopQuarks = genTopQuarkReader->read();
    /*std::vector<GenParticle>*/ genBJets = genBJetReader->read();
    /*std::vector<GenParticle>*/ genWBosons = genWBosonReader->read();
    /*std::vector<GenParticle>*/ genWJets = genWJetReader->read();
    /*std::vector<GenParticle>*/ genQuarkFromTop = genQuarkFromTopReader->read();
    
    if ( isDEBUG ) {
      dumpGenParticles("genTopQuark", genTopQuarks);
      dumpGenParticles("genBJet", genBJets);
      dumpGenParticles("genWBoson", genWBosons);
      dumpGenParticles("genWJet", genWJets);
    }

    if ( !(genTopQuarks.size() == 2) ) {
      if ( isDEBUG ) std::cout << "FAILS '2 genTopQuarks' cut !!" << std::endl;
      continue;
    }
    cutFlowTable_2lss_1tau.update("2 genTopQuarks");
    if ( !(genBJets.size() == 2) ) {
      if ( isDEBUG ) std::cout << "FAILS '2 genBJets' cut !!" << std::endl;
      continue;
    }
    cutFlowTable_2lss_1tau.update("2 genBJets");
    if ( !(genWBosons.size() >= 2) ) { // CV: do not veto events in which Higgs boson decays into W bosons
      if ( isDEBUG ) std::cout << "FAILS '>= 2 genWBosons' cut !!" << std::endl;
      continue;
    }
    cutFlowTable_2lss_1tau.update(">= 2 genWBosons");
    //std::cout << "#genWJets = " << genWJets.size() << std::endl;
    if ( !(genWJets.size() >= 2) ) {
      if ( isDEBUG ) std::cout << "FAILS '>= 2 genWJets' cut !!" << std::endl;
      continue;
    }
    cutFlowTable_2lss_1tau.update(">= 2 genWJets");

    const GenParticle* genTopQuark = 0;
    const GenParticle* genAntiTopQuark = 0;
    for ( std::vector<GenParticle>::const_iterator it = genTopQuarks.begin();
	  it != genTopQuarks.end(); ++it ) {
      if ( it->pdgId() == +6 && !genTopQuark     ) genTopQuark = &(*it);
      if ( it->pdgId() == -6 && !genAntiTopQuark ) genAntiTopQuark = &(*it);
    }
    if ( !(genTopQuark && genAntiTopQuark) ) {
      if ( isDEBUG ) std::cout << "FAILS 'genTopQuark && genAntiTopQuark' cut !!" << std::endl;
      continue;
    }
    cutFlowTable_2lss_1tau.update("genTopQuark && genAntiTopQuark");

    std::vector<const GenParticle*> genBJetsFromTop;
    std::vector<const GenParticle*> genBJetsFromAntiTop;
    for ( std::vector<GenParticle>::const_iterator it = genBJets.begin();
	  it != genBJets.end(); ++it ) {
      if ( it->pdgId() == +5 ) genBJetsFromTop.push_back(&(*it));
      if ( it->pdgId() == -5 ) genBJetsFromAntiTop.push_back(&(*it));
    }
    if ( !(genBJetsFromTop.size() >= 1 && genBJetsFromAntiTop.size() >= 1) ) {
      if ( isDEBUG ) std::cout << "FAILS 'genBJetFromTop && genBJetFromAntiTop' cut !!" << std::endl;
      continue;
    }
    cutFlowTable_2lss_1tau.update("genBJetFromTop && genBJetFromAntiTop");

    std::vector<const GenParticle*> genWBosonsFromTop;
    std::vector<const GenParticle*> genWBosonsFromAntiTop;
    for ( std::vector<GenParticle>::const_iterator it = genWBosons.begin();
	  it != genWBosons.end(); ++it ) {
      if ( it->pdgId() == +24 ) genWBosonsFromTop.push_back(&(*it));
      if ( it->pdgId() == -24 ) genWBosonsFromAntiTop.push_back(&(*it));
    }
    if ( !(genWBosonsFromTop.size() >= 1 && genWBosonsFromAntiTop.size() >= 1) ) {
      if ( isDEBUG ) std::cout << "FAILS 'genWBosonFromTop && genWBosonFromAntiTop' cut !!" << std::endl;
      continue;
    }
    cutFlowTable_2lss_1tau.update("genWBosonFromTop && genWBosonFromAntiTop");

    const GenParticle* genBJetFromTop = 0;
    const GenParticle* genWBosonFromTop = 0;
    double genBJet_plus_WBosonMassFromTop = -1.;
    for ( std::vector<const GenParticle*>::const_iterator genBJet = genBJetsFromTop.begin();
	  genBJet != genBJetsFromTop.end(); ++genBJet ) {
      for ( std::vector<const GenParticle*>::const_iterator genWBoson = genWBosonsFromTop.begin();
	    genWBoson != genWBosonsFromTop.end(); ++genWBoson ) {
	double genBJet_plus_WBosonMass = ((*genBJet)->p4() + (*genWBoson)->p4()).mass();
	if ( std::fabs(genBJet_plus_WBosonMass - genTopQuark->mass()) < std::fabs(genBJet_plus_WBosonMassFromTop - genTopQuark->mass())  ||
	     !(genBJetFromTop && genWBosonFromTop) ) {
	  genBJetFromTop = (*genBJet);
	  genWBosonFromTop = (*genWBoson);
	  genBJet_plus_WBosonMassFromTop = genBJet_plus_WBosonMass;
	}
      }
    }
    if ( !(std::fabs((genBJetFromTop->p4() + genWBosonFromTop->p4()).mass() - genTopQuark->mass()) < 15.) ) {
      if ( isDEBUG ) {
	std::cout << "FAILS 'genTopQuark mass' cut !!" << std::endl;
	//std::cout << "genTopQuark: pT = " << genTopQuark->pt() << ", eta = " << genTopQuark->eta() << ","
	//	    << " phi = " << genTopQuark->phi() << ", mass = " << genTopQuark->mass() << std::endl;
	//std::cout << "genBJetFromTop: pT = " << genBJetFromTop->pt() << ", eta = " << genBJetFromTop->eta() << ","
	//	    << " phi = " << genBJetFromTop->phi() << ", mass = " << genBJetFromTop->mass() << std::endl;
	//std::cout << "genWBosonFromTop: pT = " << genWBosonFromTop->pt() << ", eta = " << genWBosonFromTop->eta() << ","
	//	    << " phi = " << genWBosonFromTop->phi() << ", mass = " << genWBosonFromTop->mass() << std::endl;
	//std::cout << "(mass of genBJetFromTop + genWBosonFromTop = " << (genBJetFromTop->p4() + genWBosonFromTop->p4()).mass() << ")" << std::endl;
      }
      continue;
    }
    cutFlowTable_2lss_1tau.update("genTopQuark mass");
    const GenParticle* genBJetFromAntiTop = 0;
    const GenParticle* genWBosonFromAntiTop = 0;
    double genBJet_plus_WBosonMassFromAntiTop = -1.;
    for ( std::vector<const GenParticle*>::const_iterator genBJet = genBJetsFromAntiTop.begin();
	  genBJet != genBJetsFromAntiTop.end(); ++genBJet ) {
      for ( std::vector<const GenParticle*>::const_iterator genWBoson = genWBosonsFromAntiTop.begin();
	    genWBoson != genWBosonsFromAntiTop.end(); ++genWBoson ) {
	double genBJet_plus_WBosonMass = ((*genBJet)->p4() + (*genWBoson)->p4()).mass();
	if ( std::fabs(genBJet_plus_WBosonMass - genAntiTopQuark->mass()) < std::fabs(genBJet_plus_WBosonMassFromAntiTop - genAntiTopQuark->mass())  ||
	     !(genBJetFromAntiTop && genWBosonFromAntiTop) ) {
	  genBJetFromAntiTop = (*genBJet);
	  genWBosonFromAntiTop = (*genWBoson);
	  genBJet_plus_WBosonMassFromAntiTop = genBJet_plus_WBosonMass;
	}
      }
    }
    if ( !(std::fabs((genBJetFromAntiTop->p4() + genWBosonFromAntiTop->p4()).mass() - genAntiTopQuark->mass()) < 15.) ) {
      if ( isDEBUG ) {
	std::cout << "FAILS 'genAntiTopQuark mass' cut !!" << std::endl;
	//std::cout << "genAntiTopQuark: pT = " << genAntiTopQuark->pt() << ", eta = " << genAntiTopQuark->eta() << ","
	//	    << " phi = " << genAntiTopQuark->phi() << ", mass = " << genAntiTopQuark->mass() << std::endl;
	//std::cout << "genBJetFromAntiTop: pT = " << genBJetFromAntiTop->pt() << ", eta = " << genBJetFromAntiTop->eta() << ","
	//	    << " phi = " << genBJetFromAntiTop->phi() << ", mass = " << genBJetFromAntiTop->mass() << std::endl;
	//std::cout << "genWBosonFromAntiTop: pT = " << genWBosonFromAntiTop->pt() << ", eta = " << genWBosonFromAntiTop->eta() << ","
	//	    << " phi = " << genWBosonFromAntiTop->phi() << ", mass = " << genWBosonFromAntiTop->mass() << std::endl;
	//std::cout << "(mass of genBJetFromAntiTop + genWBosonFromAntiTop = " << (genBJetFromAntiTop->p4() + genWBosonFromAntiTop->p4()).mass() << ")" << std::endl;
      }
      continue;
    }
    cutFlowTable_2lss_1tau.update("genAntiTopQuark mass");

    std::vector<const GenParticle*> genWJetsFromTop;
    double genWJetsFromTop_mass = -1.;
    std::vector<const GenParticle*> genWJetsFromAntiTop;
    double genWJetsFromAntiTop_mass = -1.;
    for ( std::vector<GenParticle>::const_iterator it1 = genWJets.begin(); it1 != genWJets.end(); ++it1 ) {
      for ( std::vector<GenParticle>::const_iterator it2 = it1 + 1;
      it2 != genWJets.end(); ++it2 ) {
    /*for ( std::vector<GenParticle>::const_iterator it1 = genQuarkFromTop.begin(); it1 != genQuarkFromTop.end(); ++it1 ) {
      for ( std::vector<GenParticle>::const_iterator it2 = it1 + 1;
      it2 != genQuarkFromTop.end(); ++it2 ) {*/
	
	double genDijetMass = (it1->p4() + it2->p4()).mass();
	// CV: Matching the generator-level charge of the two quarks to the generator-level charge of the W boson is a bit cumbersome,
	//     because charge of Particles is stored as integer in Ntuple,
	//     so only sign of charge is well defined for quarks (fractional charge is not supported!)
	//
	//     For W->jj decays, the sign of the charge of both jets is equal to the sign of the charge of the W boson,
	//     i.e. the W boson decays either via
	//       W+ -> up-type-quark (q = +2/3) + anti-down-type-quark (+1/3)
	//     or via
	//       W- -> anti-up-type-quark (q = -2/3) + down-type-quark (-1/3)
	if ( boost::math::sign(it1->charge()) == boost::math::sign(genWBosonFromTop->charge()) &&
	     boost::math::sign(it2->charge()) == boost::math::sign(genWBosonFromTop->charge()) ) {
	  if ( std::fabs(genDijetMass - genWBosonFromTop->mass()) < 15. &&
	       (genWJetsFromTop_mass == -1. ||
		std::fabs(genDijetMass - genWBosonFromTop->mass()) < std::fabs(genWJetsFromTop_mass - genWBosonFromTop->mass())) ) {
	    genWJetsFromTop.clear();
	    genWJetsFromTop.push_back(&(*it1));
	    genWJetsFromTop.push_back(&(*it2));
	    genWJetsFromTop_mass = genDijetMass;
	  }
	}
	if ( boost::math::sign(it1->charge()) == boost::math::sign(genWBosonFromAntiTop->charge()) &&
	     boost::math::sign(it2->charge()) == boost::math::sign(genWBosonFromAntiTop->charge()) ) {
	  if ( std::fabs(genDijetMass - genWBosonFromAntiTop->mass()) < 15. &&
	       (genWJetsFromAntiTop_mass == -1. ||
		std::fabs(genDijetMass - genWBosonFromAntiTop->mass()) < std::fabs(genWJetsFromAntiTop_mass - genWBosonFromAntiTop->mass())) ) {
	    genWJetsFromAntiTop.clear();
	    genWJetsFromAntiTop.push_back(&(*it1));
	    genWJetsFromAntiTop.push_back(&(*it2));
	    genWJetsFromAntiTop_mass = genDijetMass;
	  }
	}
      }
    }
    //std::cout << "#genWJetsFromTop = " << genWJetsFromTop.size() << " (mass = " << genWJetsFromTop_mass << ")" << std::endl;
    //std::cout << "#genWJetsFromAntiTop = " << genWJetsFromAntiTop.size() << " (mass = " << genWJetsFromAntiTop_mass << ")" << std::endl;
    if ( !(genWJetsFromTop.size() == 2 || genWJetsFromAntiTop.size() == 2) ) {
      if ( isDEBUG ) std::cout << "FAILS '2 genWJetsFromTop || 2 genWJetsFromAntiTop' cut !!" << std::endl;
      continue;
    }
    cutFlowTable_2lss_1tau.update("2 genWJetsFromTop || 2 genWJetsFromAntiTop");

    const GenParticle* genWJetFromTop_lead = 0;
    const GenParticle* genWJetFromTop_sublead = 0;
    bool failsWbosonMassVeto_top = false;
    if ( genWJetsFromTop.size() == 2 ) {
      std::sort(genWJetsFromTop.begin(), genWJetsFromTop.end(), isHigherPt);
      genWJetFromTop_lead = genWJetsFromTop[0];
      genWJetFromTop_sublead = genWJetsFromTop[1];
      if ( !(std::fabs((genWJetFromTop_lead->p4() + genWJetFromTop_sublead->p4()).mass() - genWBosonFromTop->mass()) < 15.) ) failsWbosonMassVeto_top = true;
    }
    //std::cout << "genWBosonFromTop: mass = " << genWBosonFromTop->mass();
    //if ( genWJetFromTop_lead && genWJetFromTop_sublead ) {
    //  std::cout << "," ;
    //  std::cout << " mass of genWJetsFromTop = " << (genWJetFromTop_lead->p4() + genWJetFromTop_sublead->p4()).mass();
    //}
    //std::cout << std::endl;
    if ( failsWbosonMassVeto_top ) {
      if ( isDEBUG ) std::cout << "FAILS 'genWBosonFromTop mass' cut !!" << std::endl;
      continue;
    }
    cutFlowTable_2lss_1tau.update("genWBosonFromTop mass");

    const GenParticle* genWJetFromAntiTop_lead = 0;
    const GenParticle* genWJetFromAntiTop_sublead = 0;
    bool failsWbosonMassVeto_antiTop = false;
    if ( genWJetsFromAntiTop.size() == 2 ) {
      std::sort(genWJetsFromAntiTop.begin(), genWJetsFromAntiTop.end(), isHigherPt);
      genWJetFromAntiTop_lead = genWJetsFromAntiTop[0];
      genWJetFromAntiTop_sublead = genWJetsFromAntiTop[1];
      if ( !(std::fabs((genWJetFromAntiTop_lead->p4() + genWJetFromAntiTop_sublead->p4()).mass() - genWBosonFromAntiTop->mass()) < 15.) ) failsWbosonMassVeto_antiTop = true;
    }
    //std::cout << "genWBosonFromAntiTop: mass = " << genWBosonFromAntiTop->mass();
    //if ( genWJetFromAntiTop_lead && genWJetFromAntiTop_sublead ) {
    //  std::cout << "," ;
    //  std::cout << " mass of genWJetsFromAntiTop = " << (genWJetFromAntiTop_lead->p4() + genWJetFromAntiTop_sublead->p4()).mass();
    //}
    //std::cout << std::endl;
    if ( failsWbosonMassVeto_antiTop ) {
      if ( isDEBUG ) std::cout << "FAILS 'genWBosonFromAntiTop mass' cut !!" << std::endl;
      continue;
    }
    cutFlowTable_2lss_1tau.update("genWBosonFromAntiTop mass");

    if ( isDEBUG ) {
      std::cout << "top:" << (*genTopQuark) << std::endl;
      std::cout << " b:" << (*genBJetFromTop) << std::endl;
      std::cout << " W:" << (*genWBosonFromTop) << std::endl;
      if ( genWJetFromTop_lead && genWJetFromTop_sublead ) {
	std::cout << " Wj1:" << (*genWJetFromTop_lead) << std::endl;
	std::cout << " Wj2:" << (*genWJetFromTop_sublead) << std::endl;
      } else {
	std::cout << "(leptonic W decay)" << std::endl;
      }
      std::cout << "anti-top:" << (*genAntiTopQuark) << std::endl;
      std::cout << " b:" << (*genBJetFromAntiTop) << std::endl;
      std::cout << " W:" << (*genWBosonFromAntiTop) << std::endl;
      if ( genWJetFromAntiTop_lead && genWJetFromAntiTop_sublead ) {
	std::cout << " Wj1:" << (*genWJetFromAntiTop_lead) << std::endl;
	std::cout << " Wj2:" << (*genWJetFromAntiTop_sublead) << std::endl;
      } else {
	std::cout << "(leptonic W decay)" << std::endl;
      }
      std::cout << std::endl;
    }

    if ( !((genBJetFromTop             &&
	    genWJetFromTop_lead        &&
	    genWJetFromTop_sublead    ) ||
	   (genBJetFromAntiTop         &&
	    genWJetFromAntiTop_lead    &&
	    genWJetFromAntiTop_sublead)) ) {
      if ( isDEBUG ) std::cout << "FAILS 'genJet triplet' cut !!" << std::endl;
      continue;
    }
    cutFlowTable_2lss_1tau.update("genJet triplet");

    Particle::LorentzVector genWBosonFromTopP4;
    if ( genWJetFromTop_lead && genWJetFromTop_sublead ) {
      genWBosonFromTopP4 = genWJetFromTop_lead->p4() + genWJetFromTop_sublead->p4();
    }
    Particle::LorentzVector genWBosonFromAntiTopP4;
    if ( genWJetFromAntiTop_lead && genWJetFromAntiTop_sublead ) {
      genWBosonFromAntiTopP4 = genWJetFromAntiTop_lead->p4() + genWJetFromAntiTop_sublead->p4();
    }

    Particle::LorentzVector genTopP4;
    if ( genBJetFromTop && genWJetFromTop_lead && genWJetFromTop_sublead ) {
      genTopP4 = genBJetFromTop->p4() + genWJetFromTop_lead->p4() + genWJetFromTop_sublead->p4();
    }
    Particle::LorentzVector genAntiTopP4;
    if ( genBJetFromAntiTop && genWJetFromAntiTop_lead && genWJetFromAntiTop_sublead ) {
      genAntiTopP4 = genBJetFromAntiTop->p4() + genWJetFromAntiTop_lead->p4() + genWJetFromAntiTop_sublead->p4();
    }


    //-------------------------------------------------------------------------------------------------------------------
    // case 1: all three jets contained within dR=1.5 "fat" jet,
    //         reconstructed by hep-top-tagger (HTTv2) algorithm

    cutFlowTable_2lss_1tau_HTTv2.update("genJet triplet");

    if ((genBJetFromTop         &&
	 genWJetFromTop_lead    &&
	 genWJetFromTop_sublead    )   &&
	(genBJetFromAntiTop      &&
	 genWJetFromAntiTop_lead &&
	    genWJetFromAntiTop_sublead))
      cutFlowTable_2lss_1tau_HTTv2.update("genJet triplet from both top and antitop");


    isHTTv2FromTop = false;
    isHTTv2FromTop_fatjetPtGt200 = false;
    isHTTv2FromTop_fatjetPtGt200_and_subjetPtGt30 = false;
    isHTTv2FromTop_selected = false;
    isHTTv2FromAntiTop = false;
    isHTTv2FromAntiTop_fatjetPtGt200 = false;
    isHTTv2FromAntiTop_fatjetPtGt200_and_subjetPtGt30 = false;
    isHTTv2FromAntiTop_selected = false;

    isbCandiFromTop = false;
    isW1CandiFromTop = false;
    isW2CandiFromTop = false;
    isJetTripletFromTop = false;
    isbCandiFromAntiTop = false;
    isW1CandiFromAntiTop = false;
    isW2CandiFromAntiTop = false;
    isJetTripletFromAntiTop = false;

    isbCandiFromTopPtGt30 = false;
    isW1CandiFromTopPtGt30 = false;
    isW2CandiFromTopPtGt30 = false;
    isJetTripletFromTopPtGt30 = false;
    isbCandiFromAntiTopPtGt30 = false;
    isW1CandiFromAntiTopPtGt30 = false;
    isW2CandiFromAntiTopPtGt30 = false;
    isJetTripletFromAntiTopPtGt30 = false;

    isCat1_Gen = 0;

    //TString sPrint = Form("\n\nEvent %lli:\n",inputTree -> getCurrentMaxEventIdx());
    sPrint = Form("\n\n\nEntry #%lli (run=%u,ls=%u,event=%lli):\n",inputTree -> getCurrentMaxEventIdx(),eventInfo.run,eventInfo.lumi,eventInfo.event);

    sPrint += Form("selJets.size:%zu\n",selJets.size());
    sPrint += Form("selHadTau.size:%zu\n",selHadTaus.size());
    sPrint += Form("selLeptons.size:%zu\n",selLeptons.size());
    sPrint += Form("fakeableElectrons.size:%zu\n",fakeableElectrons.size());
    sPrint += Form("fakeableMuons.size:%zu\n",fakeableMuons.size());
    sPrint += Form("fakeableHadTau.size:%zu\n",fakeableHadTaus.size());

    if (genBJetFromTop     && genWJetFromTop_lead     && genWJetFromTop_sublead && 0==1) {
      sPrint += "genTopInfo::\n";
      sPrint += Form("gen_Top: \t pt: %6.1f,  eta: %5.2f, phi: %5.2f, m: %g\n",
		     genTopP4.pt(),genTopP4.eta(),genTopP4.phi(),genTopP4.mass());
      sPrint += Form("gen_b:\t \t pt: %6.1f,  eta: %5.2f, phi: %5.2f, m: %g\n",
		     genBJetFromTop->pt(),genBJetFromTop->eta(),genBJetFromTop->phi(),genBJetFromTop->mass());
      sPrint += Form("gen_W1: \t pt: %6.1f,  eta: %5.2f, phi: %5.2f, m: %g\n",
		     genWJetFromTop_lead->pt(),genWJetFromTop_lead->eta(),genWJetFromTop_lead->phi(),genWJetFromTop_lead->mass());
      sPrint += Form("gen_W2: \t pt: %6.1f,  eta: %5.2f, phi: %5.2f, m: %g\n",
		     genWJetFromTop_sublead->pt(),genWJetFromTop_sublead->eta(),genWJetFromTop_sublead->phi(),genWJetFromTop_sublead->mass());

      
      std::map<int, Particle::LorentzVector> genVarsFromTop = isGenMatchedJetTripletVar(genTopQuarks, genBJets, genWBosons, genWJets, kGenTop); // genWJets -> genQuarkFromTop

      sPrint += "\n\ngenTopInfo from isGenMatchedJetTripletVar()::\n";
      sPrint += Form("gen_Top: \t pt: %6.1f,  eta: %5.2f, phi: %5.2f, m: %g\n",
		     genVarsFromTop[kGenTopVar].pt(),genVarsFromTop[kGenTopVar].eta(),genVarsFromTop[kGenTopVar].phi(),genVarsFromTop[kGenTopVar].mass());
      sPrint += Form("gen_b:\t \t pt: %6.1f,  eta: %5.2f, phi: %5.2f, m: %g\n",
		     genVarsFromTop[kGenTopB].pt(),genVarsFromTop[kGenTopB].eta(),genVarsFromTop[kGenTopB].phi(),genVarsFromTop[kGenTopB].mass());
      sPrint += Form("gen_W1: \t pt: %6.1f,  eta: %5.2f, phi: %5.2f, m: %g\n",
		     genVarsFromTop[kGenTopWj1].pt(),genVarsFromTop[kGenTopWj1].eta(),genVarsFromTop[kGenTopWj1].phi(),genVarsFromTop[kGenTopWj1].mass());
      sPrint += Form("gen_W2: \t pt: %6.1f,  eta: %5.2f, phi: %5.2f, m: %g\n",
		     genVarsFromTop[kGenTopWj2].pt(),genVarsFromTop[kGenTopWj2].eta(),genVarsFromTop[kGenTopWj2].phi(),genVarsFromTop[kGenTopWj2].mass());

      //if ((genVarsFromTop[kGenTopWj1]) != (genWJetFromTop_lead->p4())) sPrint += " ****** genWj1 different in two methos of fetching info *** \n";
      //if (genVarsFromTop[kGenTopWj2] != (genWJetFromTop_sublead->p4())) sPrint += " ****** genWj2 different in two methos of fetching info *** \n";
      


      std::map<int, Particle::LorentzVector> genVarsFromTop_1 = isGenMatchedJetTripletVar(genTopQuarks, genBJets, genWBosons, genQuarkFromTop, kGenTop); // genWJets -> genQuarkFromTop

      sPrint += "\n\ngenTopInfo from isGenMatchedJetTripletVar_1()::\n";
      sPrint += Form("gen_Top: \t pt: %6.1f,  eta: %5.2f, phi: %5.2f, m: %g\n",
		     genVarsFromTop_1[kGenTopVar].pt(),genVarsFromTop_1[kGenTopVar].eta(),genVarsFromTop_1[kGenTopVar].phi(),genVarsFromTop_1[kGenTopVar].mass());
      sPrint += Form("gen_b:\t \t pt: %6.1f,  eta: %5.2f, phi: %5.2f, m: %g\n",
		     genVarsFromTop_1[kGenTopB].pt(),genVarsFromTop_1[kGenTopB].eta(),genVarsFromTop_1[kGenTopB].phi(),genVarsFromTop_1[kGenTopB].mass());
      sPrint += Form("gen_W1: \t pt: %6.1f,  eta: %5.2f, phi: %5.2f, m: %g\n",
		     genVarsFromTop_1[kGenTopWj1].pt(),genVarsFromTop_1[kGenTopWj1].eta(),genVarsFromTop_1[kGenTopWj1].phi(),genVarsFromTop_1[kGenTopWj1].mass());
      sPrint += Form("gen_W2: \t pt: %6.1f,  eta: %5.2f, phi: %5.2f, m: %g\n",
		     genVarsFromTop_1[kGenTopWj2].pt(),genVarsFromTop_1[kGenTopWj2].eta(),genVarsFromTop_1[kGenTopWj2].phi(),genVarsFromTop_1[kGenTopWj2].mass());

      //if ((genVarsFromTop_1[kGenTopWj1]) != (genWJetFromTop_lead->p4())) sPrint += " ****** genWj1_1 different in two methos of fetching info *** \n";
      //if (genVarsFromTop_1[kGenTopWj2] != (genWJetFromTop_sublead->p4())) sPrint += " ****** genWj2_1 different in two methos of fetching info *** \n";

     
    }

    if (genBJetFromAntiTop     && genWJetFromAntiTop_lead     && genWJetFromAntiTop_sublead && 0==1) {
      sPrint += "\ngenAntiTopInfo::\n";
      sPrint += Form("gen_Top: \t pt: %6.1f,  eta: %5.2f, phi: %5.2f, m: %g\n",
		     genAntiTopP4.pt(),genAntiTopP4.eta(),genAntiTopP4.phi(),genAntiTopP4.mass());
      sPrint += Form("gen_b:\t \t pt: %6.1f,  eta: %5.2f, phi: %5.2f, m: %g\n",
		     genBJetFromAntiTop->pt(),genBJetFromAntiTop->eta(),genBJetFromAntiTop->phi(),genBJetFromAntiTop->mass());
      sPrint += Form("gen_W1: \t pt: %6.1f,  eta: %5.2f, phi: %5.2f, m: %g\n",
		     genWJetFromAntiTop_lead->pt(),genWJetFromAntiTop_lead->eta(),genWJetFromAntiTop_lead->phi(),genWJetFromAntiTop_lead->mass());
      sPrint += Form("gen_W2: \t pt: %6.1f,  eta: %5.2f, phi: %5.2f, m: %g\n",
		     genWJetFromAntiTop_sublead->pt(),genWJetFromAntiTop_sublead->eta(),genWJetFromAntiTop_sublead->phi(),genWJetFromAntiTop_sublead->mass());
      
      std::map<int, Particle::LorentzVector> genVarsFromAntiTop = isGenMatchedJetTripletVar(genTopQuarks, genBJets, genWBosons, genWJets, kGenAntiTop); // genWJets -> genQuarkFromTop
    
      sPrint += "\ngenAntiTopInfo from isGenMatchedJetTripletVar()::\n";
      sPrint += Form("gen_Top: \t pt: %6.1f,  eta: %5.2f, phi: %5.2f, m: %g\n",
		     genVarsFromAntiTop[kGenTopVar].pt(),genVarsFromAntiTop[kGenTopVar].eta(),genVarsFromAntiTop[kGenTopVar].phi(),genVarsFromAntiTop[kGenTopVar].mass());
      sPrint += Form("gen_b:\t \t pt: %6.1f,  eta: %5.2f, phi: %5.2f, m: %g\n",
		     genVarsFromAntiTop[kGenTopB].pt(),genVarsFromAntiTop[kGenTopB].eta(),genVarsFromAntiTop[kGenTopB].phi(),genVarsFromAntiTop[kGenTopB].mass());
      sPrint += Form("gen_W1: \t pt: %6.1f,  eta: %5.2f, phi: %5.2f, m: %g\n",
		     genVarsFromAntiTop[kGenTopWj1].pt(),genVarsFromAntiTop[kGenTopWj1].eta(),genVarsFromAntiTop[kGenTopWj1].phi(),genVarsFromAntiTop[kGenTopWj1].mass());
      sPrint += Form("gen_W2: \t pt: %6.1f,  eta: %5.2f, phi: %5.2f, m: %g\n",
		     genVarsFromAntiTop[kGenTopWj2].pt(),genVarsFromAntiTop[kGenTopWj2].eta(),genVarsFromAntiTop[kGenTopWj2].phi(),genVarsFromAntiTop[kGenTopWj2].mass());

      //if ((genVarsFromAntiTop[kGenTopWj1]) != (genWJetFromAntiTop_lead->p4())) sPrint += " ****** genWj1 (Anti) different in two methos of fetching info *** \n";
      //if (genVarsFromAntiTop[kGenTopWj2] != (genWJetFromAntiTop_sublead->p4())) sPrint += " ****** genWj2 (Anti) different in two methos of fetching info *** \n";
      

       std::map<int, Particle::LorentzVector> genVarsFromAntiTop_1 = isGenMatchedJetTripletVar(genTopQuarks, genBJets, genWBosons, genQuarkFromTop, kGenAntiTop); // genWJets -> genQuarkFromTop
    
      sPrint += "\ngenAntiTopInfo from isGenMatchedJetTripletVar_1()::\n";
      sPrint += Form("gen_Top: \t pt: %6.1f,  eta: %5.2f, phi: %5.2f, m: %g\n",
		     genVarsFromAntiTop_1[kGenTopVar].pt(),genVarsFromAntiTop_1[kGenTopVar].eta(),genVarsFromAntiTop_1[kGenTopVar].phi(),genVarsFromAntiTop_1[kGenTopVar].mass());
      sPrint += Form("gen_b:\t \t pt: %6.1f,  eta: %5.2f, phi: %5.2f, m: %g\n",
		     genVarsFromAntiTop_1[kGenTopB].pt(),genVarsFromAntiTop_1[kGenTopB].eta(),genVarsFromAntiTop_1[kGenTopB].phi(),genVarsFromAntiTop_1[kGenTopB].mass());
      sPrint += Form("gen_W1: \t pt: %6.1f,  eta: %5.2f, phi: %5.2f, m: %g\n",
		     genVarsFromAntiTop_1[kGenTopWj1].pt(),genVarsFromAntiTop_1[kGenTopWj1].eta(),genVarsFromAntiTop_1[kGenTopWj1].phi(),genVarsFromAntiTop_1[kGenTopWj1].mass());
      sPrint += Form("gen_W2: \t pt: %6.1f,  eta: %5.2f, phi: %5.2f, m: %g\n",
		     genVarsFromAntiTop_1[kGenTopWj2].pt(),genVarsFromAntiTop_1[kGenTopWj2].eta(),genVarsFromAntiTop_1[kGenTopWj2].phi(),genVarsFromAntiTop_1[kGenTopWj2].mass());

      //if ((genVarsFromAntiTop_1[kGenTopWj1]) != (genWJetFromAntiTop_lead->p4())) sPrint += " ****** genWj1 (Anti) different in two methos of fetching info *** \n";
      //if (genVarsFromAntiTop_1[kGenTopWj2] != (genWJetFromAntiTop_sublead->p4())) sPrint += " ****** genWj2 (Anti) different in two methos of fetching info *** \n";     
    }

 
    
   
    
    //Particle::LorentzVector *genParticle = new Particle::LorentzVector[4];
    const GenParticle **genParticle = new const GenParticle*[4];
    if (genBJetFromTop     && genWJetFromTop_lead     && genWJetFromTop_sublead) {
      genParticle[kTLVGenTop]   = genTopQuark;
      genParticle[kTLVGenBJet]  = genBJetFromTop;
      genParticle[kTLVGenWJet1] = genWJetFromTop_lead;
      genParticle[kTLVGenWJet2] = genWJetFromTop_sublead;

      CheckGenHTTv2JetMatching(kGenTop, genParticle, jet_ptrsHTTv2, selJets, selHadTaus, selLeptons, fakeableElectrons, fakeableMuons, fakeableHadTaus, jetSelectorHTTv2);
    }
    if (genBJetFromAntiTop     && genWJetFromAntiTop_lead     && genWJetFromAntiTop_sublead) {
      genParticle[kTLVGenTop]   = genAntiTopQuark;
      genParticle[kTLVGenBJet]  = genBJetFromAntiTop;
      genParticle[kTLVGenWJet1] = genWJetFromAntiTop_lead;
      genParticle[kTLVGenWJet2] = genWJetFromAntiTop_sublead;

      CheckGenHTTv2JetMatching(kGenAntiTop, genParticle, jet_ptrsHTTv2, selJets, selHadTaus, selLeptons, fakeableElectrons, fakeableMuons, fakeableHadTaus, jetSelectorHTTv2);
    }

    if (isCat1_Gen == 2) cutFlowTable_2lss_1tau_HTTv2.update("Both genTop and genAntiTop fall in CatI");

    if ( isHTTv2FromTop || isHTTv2FromAntiTop ) {
      cutFlowTable_2lss_1tau_HTTv2.update("rec HTTv2");
      sPrint += " rec HTTv2";
    }
    if ( isHTTv2FromTop_fatjetPtGt200 || isHTTv2FromAntiTop_fatjetPtGt200 ) {
      cutFlowTable_2lss_1tau_HTTv2.update("rec HTTv2 passes fat-jet pT > 200 GeV");
    }
    if ( isHTTv2FromTop_fatjetPtGt200_and_subjetPtGt30 || isHTTv2FromAntiTop_fatjetPtGt200_and_subjetPtGt30 ) {
      cutFlowTable_2lss_1tau_HTTv2.update("rec HTTv2 passes sub-jet pT > 30 GeV for all subjets");
    }
    if ( isHTTv2FromTop_selected || isHTTv2FromAntiTop_selected ) {
      cutFlowTable_2lss_1tau_HTTv2.update("rec HTTv2 passes all cuts");
      if ( selEventsFile_boosted ) {
	(*selEventsFile_boosted) << eventInfo.run << ':' << eventInfo.lumi << ':' << eventInfo.event << '\n';
      }
    }

    if (isbCandiFromTop || isbCandiFromAntiTop) {
      cutFlowTable_2lss_1tau_HTTv2.update("HTTv2_1: GenBJet matched)");
      if (isbCandiFromTopPtGt30 || isbCandiFromAntiTopPtGt30) {
	cutFlowTable_2lss_1tau_HTTv2.update("HTTv2_1: GenBJet pt > 30 matched)");
      }
    }
    if (isW1CandiFromTop || isW1CandiFromAntiTop) {
      cutFlowTable_2lss_1tau_HTTv2.update("HTTv2_1: GenWJet1 matched)");
      if (isW1CandiFromTopPtGt30 || isW1CandiFromAntiTopPtGt30) {
	cutFlowTable_2lss_1tau_HTTv2.update("HTTv2_1: GenWJet1 pt > 30 matched)");
      }
    }
    if (isW2CandiFromTop || isW2CandiFromAntiTop) {
      cutFlowTable_2lss_1tau_HTTv2.update("HTTv2_1: GenWJet2 matched)");
      if (isW2CandiFromTopPtGt30 || isW2CandiFromAntiTopPtGt30) {
	cutFlowTable_2lss_1tau_HTTv2.update("HTTv2_1: GenWJet2 pt > 30 matched)");
      }
    }
    if (isJetTripletFromTop || isJetTripletFromAntiTop) {
      cutFlowTable_2lss_1tau_HTTv2.update("HTTv2_1: GenTripletJet matched)");
    }

    if (isCat1_Gen) std::cout << sPrint << std::endl;
    //-------------------------------------------------------------------------------------------------------------------

    //-------------------------------------------------------------------------------------------------------------------
    // case 2: two jets from hadronic W boson decay contained within dR=1.2 "fat" jet,
    //         reconstructed by by anti-kT algorithm with dR=1.2 (AK12),
    //         while b-jet from top decay is resolved as separate jets,
    //         reconstructed by anti-kT algorithm with dR=0.4 (AK4)

    cutFlowTable_2lss_1tau_AK12.update("genJet triplet");

    bool isAK12FromTop = false;
    bool isAK12FromTop_fatjetPtGt130 = false;
    bool isAK12FromTop_fatjetPtGt130_and_subjetPtGt10 = false;
    bool isAK12FromTop_selected = false;
    bool isBJetFromTop = false;
    bool selBJetFromTop_passesLoose = false;
    bool isAK12FromAntiTop = false;
    bool isAK12FromAntiTop_fatjetPtGt130 = false;
    bool isAK12FromAntiTop_fatjetPtGt130_and_subjetPtGt10 = false;
    bool isAK12FromAntiTop_selected = false;
    bool isBJetFromAntiTop = false;
    bool selBJetFromAntiTop_passesLoose = false;

    if ( (genBJetFromTop                                        && genBJetFromTop->pt()         >  20. &&
	  genWJetFromTop_lead && genWJetFromTop_sublead         && genWBosonFromTopP4.pt()      > 100.) ||
	 (genBJetFromAntiTop                                    && genBJetFromAntiTop->pt()     >  20. &&
	  genWJetFromAntiTop_lead && genWJetFromAntiTop_sublead && genWBosonFromAntiTopP4.pt()  > 100.) ) {
      cutFlowTable_2lss_1tau_AK12.update("genBJet passes pT > 20 GeV && genW passes pT > 100 GeV");

      if ( (genBJetFromTop             && genBJetFromTop->absEta()          < 5.0 &&
	    genWJetFromTop_lead        && genWJetFromTop_lead->absEta()     < 5.0 &&
	    genWJetFromTop_sublead     && genWJetFromTop_lead->absEta()     < 5.0) ||
	   (genBJetFromAntiTop         && genBJetFromAntiTop->absEta()      < 5.0 &&
	    genWJetFromAntiTop_lead    && genWJetFromAntiTop_lead->absEta() < 5.0 &&
	    genWJetFromAntiTop_sublead && genWJetFromAntiTop_lead->absEta() < 5.0) ) {
	cutFlowTable_2lss_1tau_AK12.update("genJet triplet passes abs(eta) < 5.0");

	if ( (genBJetFromTop             && genBJetFromTop->absEta()      < 2.4) ||
	     (genBJetFromAntiTop         && genBJetFromAntiTop->absEta()  < 2.4) ) {
	  cutFlowTable_2lss_1tau_AK12.update("genBJet passes abs(eta) < 2.4");

	  if ( (genBJetFromTop             && genBJetFromTop->absEta()          < 2.4 &&
		genWJetFromTop_lead        && genWJetFromTop_lead->absEta()     < 2.4 &&
		genWJetFromTop_sublead     && genWJetFromTop_lead->absEta()     < 2.4) ||
	       (genBJetFromAntiTop         && genBJetFromAntiTop->absEta()      < 2.4 &&
		genWJetFromAntiTop_lead    && genWJetFromAntiTop_lead->absEta() < 2.4 &&
		genWJetFromAntiTop_sublead && genWJetFromAntiTop_lead->absEta() < 2.4) ) {
	    cutFlowTable_2lss_1tau_AK12.update("genJet triplet passes abs(eta) < 2.4");

	    if ( (genWJetFromTop_lead && genWJetFromTop_sublead                          &&
		  deltaR(genWBosonFromTopP4, genWJetFromTop_lead->p4())            < 1.2 &&
		  deltaR(genWBosonFromTopP4, genWJetFromTop_sublead->p4())         < 1.2) ||
		 (genWJetFromAntiTop_lead && genWJetFromAntiTop_sublead                  &&
		  deltaR(genWBosonFromAntiTopP4, genWJetFromAntiTop_lead->p4())    < 1.2 &&
		  deltaR(genWBosonFromAntiTopP4, genWJetFromAntiTop_sublead->p4()) < 1.2) ) {
	      cutFlowTable_2lss_1tau_AK12.update("dR(genWJet1, genWJet2) < 1.2");

	      const RecoJetAK12* recWBosonFromTop = 0;
	      const RecoJetAK12* recWBosonFromAntiTop = 0;
	      for ( std::vector<const RecoJetAK12*>::const_iterator jetAK12 = jet_ptrsAK12.begin();
		    jetAK12 != jet_ptrsAK12.end(); ++jetAK12 ) {
		if ( genWJetFromTop_lead && genWJetFromTop_sublead && deltaR((*jetAK12)->p4(), genWBosonFromTopP4) < 0.6 ) {
		  recWBosonFromTop = (*jetAK12);
		  histManager_jetsAK12->fillHistograms({ recWBosonFromTop }, evtWeight);
		  if ( !isHTTv2FromTop ) {
		    histManager_jetsAK12_notHTTv2->fillHistograms({ recWBosonFromTop }, evtWeight);
		  }
		}
		if ( genWJetFromAntiTop_lead && genWJetFromAntiTop_sublead && deltaR((*jetAK12)->p4(), genWBosonFromAntiTopP4) < 0.6 ) {
		  recWBosonFromAntiTop = (*jetAK12);
		  histManager_jetsAK12->fillHistograms({ recWBosonFromAntiTop }, evtWeight);
		  if ( !isHTTv2FromAntiTop ) {
		    histManager_jetsAK12_notHTTv2->fillHistograms({ recWBosonFromAntiTop }, evtWeight);
		  }
		}
	      }

	      const RecoJet* selBJetFromTop = 0;
	      double dRmin_selBJetFromTop = 1.e+3;
	      const RecoJet* selBJetFromAntiTop = 0;
	      double dRmin_selBJetFromAntiTop = 1.e+3;
	      for ( std::vector<const RecoJet*>::const_iterator selJet = selJets.begin(); selJet != selJets.end(); ++selJet ) {
		if ( genBJetFromTop ) {
		  double dR_selBJetFromTop = deltaR((*selJet)->p4(), genBJetFromTop->p4());
		  if ( dR_selBJetFromTop < 0.3 && dR_selBJetFromTop < dRmin_selBJetFromTop ) {
		    selBJetFromTop = (*selJet);
		    dRmin_selBJetFromTop = dR_selBJetFromTop;
		  }
		}
		if ( genBJetFromAntiTop ) {
		  double dR_selBJetFromAntiTop = deltaR((*selJet)->p4(), genBJetFromAntiTop->p4());
		  if ( dR_selBJetFromAntiTop < 0.3 && dR_selBJetFromAntiTop < dRmin_selBJetFromAntiTop ) {
		    selBJetFromAntiTop = (*selJet);
		    dRmin_selBJetFromAntiTop = dR_selBJetFromAntiTop;
		  }
		}
	      }

	      if ( selBJetFromTop ) {
		isBJetFromTop = true;
	      }
	      if ( selBJetFromAntiTop ) {
		isBJetFromAntiTop = true;
	      }

	      for ( std::vector<const RecoJet*>::const_iterator selBJet_loose = selBJets_loose.begin();
		    selBJet_loose != selBJets_loose.end(); ++selBJet_loose ) {
		if ( selBJetFromTop && deltaR(selBJetFromTop->p4(), (*selBJet_loose)->p4()) < 0.3 ) {
		  selBJetFromTop_passesLoose = true;
		}
		if ( selBJetFromAntiTop && deltaR(selBJetFromAntiTop->p4(), (*selBJet_loose)->p4()) < 0.3 ) {
		  selBJetFromAntiTop_passesLoose = true;
		}
	      }


	      if ( recWBosonFromTop && recWBosonFromTop->subJet1() && recWBosonFromTop->subJet2() ) {
		const RecoSubjetAK12* recWJetFromTop_lead = 0;
		const RecoSubjetAK12* recWJetFromTop_sublead = 0;
  		double dR_lead_1 = deltaR(genWJetFromTop_lead->p4(), recWBosonFromTop->subJet1()->p4());
		double dR_lead_2 = deltaR(genWJetFromTop_lead->p4(), recWBosonFromTop->subJet2()->p4());
		double dR_sublead_1 = deltaR(genWJetFromTop_sublead->p4(), recWBosonFromTop->subJet1()->p4());
		double dR_sublead_2 = deltaR(genWJetFromTop_sublead->p4(), recWBosonFromTop->subJet2()->p4());
		if ( (square(dR_lead_1) + square(dR_sublead_2)) < (square(dR_lead_2) + square(dR_sublead_1)) ) {
		  if ( dR_lead_1 < 0.2 && dR_sublead_2 < 0.2 ) {
		    recWJetFromTop_lead = recWBosonFromTop->subJet1();
		    recWJetFromTop_sublead = recWBosonFromTop->subJet2();
		  }
		} else {
		  if ( dR_lead_2 < 0.2 && dR_sublead_1 < 0.2 ) {
		    recWJetFromTop_lead = recWBosonFromTop->subJet2();
		    recWJetFromTop_sublead = recWBosonFromTop->subJet1();
		  }
		}
                if ( recWJetFromTop_lead && recWJetFromTop_sublead ) {
		  Particle::LorentzVector recWBosonFromTopP4 = recWJetFromTop_lead->p4() + recWJetFromTop_sublead->p4();
                  if ( genWBosonFromTopP4.pt() > 100. ) {
		    fillWithOverFlow(histogram_AK12_W_ptRec_div_ptGen, recWBosonFromTopP4.pt()/genWBosonFromTopP4.pt(), evtWeight);
		  }
		  fillWithOverFlow(histogram_AK12_mW, recWBosonFromTopP4.mass(), evtWeight);
		  if ( genWJetFromTop_lead->pt() > 20. ) {
		    fillWithOverFlow(histogram_AK12_WJet1_ptRec_div_ptGen, recWJetFromTop_lead->pt()/genWJetFromTop_lead->pt(), evtWeight);
		    fillWithOverFlow(histogram_AK12_WJet1_dRmatch, deltaR(recWJetFromTop_lead->p4(), genWJetFromTop_lead->p4()), evtWeight);
		    double cosThetaStar_WJet1 = comp_cosThetaStar(recWJetFromTop_lead->p4(), recWJetFromTop_lead->p4() + recWJetFromTop_sublead->p4());
		    fillWithOverFlow(histogram_AK12_WJet1_cosThetaStar, cosThetaStar_WJet1, evtWeight);
		  }
		  if ( genWJetFromTop_sublead->pt() > 20. ) {
		    fillWithOverFlow(histogram_AK12_WJet2_ptRec_div_ptGen, recWJetFromTop_sublead->pt()/genWJetFromTop_sublead->pt(), evtWeight);
		    fillWithOverFlow(histogram_AK12_WJet2_dRmatch, deltaR(recWJetFromTop_sublead->p4(), genWJetFromTop_sublead->p4()), evtWeight);
		  }
		  if ( selBJetFromTop ) {
		    double cosThetaStar_BJet = comp_cosThetaStar(selBJetFromTop->p4(), selBJetFromTop->p4() + recWJetFromTop_lead->p4() + recWJetFromTop_sublead->p4());
		    fillWithOverFlow(histogram_AK12_BJet_cosThetaStar, cosThetaStar_BJet, evtWeight);
		  }
		  double theta_t_lead = comp_theta_t(
                    recWJetFromTop_lead->p4(), recWBosonFromTop->pullEta(), recWBosonFromTop->pullPhi(),
		    recWJetFromTop_sublead->p4());
		  fillWithOverFlow(histogram_AK12_theta_t_lead, theta_t_lead, evtWeight);
		  double theta_t_sublead = comp_theta_t(
                    recWJetFromTop_sublead->p4(), recWBosonFromTop->pullEta(), recWBosonFromTop->pullPhi(),
		    recWJetFromTop_lead->p4());
		  fillWithOverFlow(histogram_AK12_theta_t_sublead, theta_t_sublead, evtWeight);
		  isAK12FromTop = true;
		  if ( recWBosonFromTop->pt() > 130 ) {
		    isAK12FromTop_fatjetPtGt130 = true;
		    if ( recWBosonFromTop->subJet1()->pt() > 10. && recWBosonFromTop->subJet2()->pt() > 10. ) {
		      isAK12FromTop_fatjetPtGt130_and_subjetPtGt10 = true;
		      if ( jetSelectorAK12(*recWBosonFromTop) ) {
			if ( selBJetFromTop ) {
			  /*std::cout << "found semi-boosted hadronic top:"
				    << " run = " << eventInfo.run << ", ls = " << eventInfo.lumi << ", event = " << eventInfo.event << std::endl;
			  std::cout << "AK12 jet:" << std::endl;
			  std::cout << (*recWBosonFromTop);
			  std::cout << "b-jet:" << std::endl;
			  std::cout << (*selBJetFromTop);*/
			}
			isAK12FromTop_selected = true;
		      }
		    }
		  }
		}
	      }

	      if ( recWBosonFromAntiTop && recWBosonFromAntiTop->subJet1() && recWBosonFromAntiTop->subJet2() ) {
		const RecoSubjetAK12* recWJetFromAntiTop_lead = 0;
		const RecoSubjetAK12* recWJetFromAntiTop_sublead = 0;
		double dR_lead_1 = deltaR(genWJetFromAntiTop_lead->p4(), recWBosonFromAntiTop->subJet1()->p4());
		double dR_lead_2 = deltaR(genWJetFromAntiTop_lead->p4(), recWBosonFromAntiTop->subJet2()->p4());
		double dR_sublead_1 = deltaR(genWJetFromAntiTop_sublead->p4(), recWBosonFromAntiTop->subJet1()->p4());
		double dR_sublead_2 = deltaR(genWJetFromAntiTop_sublead->p4(), recWBosonFromAntiTop->subJet2()->p4());
		if ( (square(dR_lead_1) + square(dR_sublead_2)) < (square(dR_lead_2) + square(dR_sublead_1)) ) {
		  if ( dR_lead_1 < 0.2 && dR_sublead_2 < 0.2 ) {
		    recWJetFromAntiTop_lead = recWBosonFromAntiTop->subJet1();
		    recWJetFromAntiTop_sublead = recWBosonFromAntiTop->subJet2();
		  }
		} else {
		  if ( dR_lead_2 < 0.2 && dR_sublead_1 < 0.2 ) {
		    recWJetFromAntiTop_lead = recWBosonFromAntiTop->subJet2();
		    recWJetFromAntiTop_sublead = recWBosonFromAntiTop->subJet1();
		  }
		}
		if ( recWJetFromAntiTop_lead && recWJetFromAntiTop_sublead ) {
		  Particle::LorentzVector recWBosonFromAntiTopP4 = recWJetFromAntiTop_lead->p4() + recWJetFromAntiTop_sublead->p4();
		  if ( genWBosonFromAntiTopP4.pt() > 100. ) {
		    fillWithOverFlow(histogram_AK12_W_ptRec_div_ptGen, recWBosonFromAntiTopP4.pt()/genWBosonFromAntiTopP4.pt(), evtWeight);
		  }
		  fillWithOverFlow(histogram_AK12_mW, recWBosonFromAntiTopP4.mass(), evtWeight);
		  if ( genWJetFromAntiTop_lead->pt() > 20. ) {
		    fillWithOverFlow(histogram_AK12_WJet1_ptRec_div_ptGen, recWJetFromAntiTop_lead->pt()/genWJetFromAntiTop_lead->pt(), evtWeight);
		    fillWithOverFlow(histogram_AK12_WJet1_dRmatch, deltaR(recWJetFromAntiTop_lead->p4(), genWJetFromAntiTop_lead->p4()), evtWeight);
		    double cosThetaStar_WJet1 = comp_cosThetaStar(recWJetFromAntiTop_lead->p4(), recWJetFromAntiTop_lead->p4() + recWJetFromAntiTop_sublead->p4());
		    fillWithOverFlow(histogram_AK12_WJet1_cosThetaStar, cosThetaStar_WJet1, evtWeight);
		  }
		  if ( genWJetFromAntiTop_sublead->pt() > 20. ) {
		    fillWithOverFlow(histogram_AK12_WJet2_ptRec_div_ptGen, recWJetFromAntiTop_sublead->pt()/genWJetFromAntiTop_sublead->pt(), evtWeight);
		    fillWithOverFlow(histogram_AK12_WJet2_dRmatch, deltaR(recWJetFromAntiTop_sublead->p4(), genWJetFromAntiTop_sublead->p4()), evtWeight);
		  }
		  if ( selBJetFromAntiTop ) {
		    double cosThetaStar_BJet = comp_cosThetaStar(selBJetFromAntiTop->p4(), selBJetFromAntiTop->p4() + recWJetFromAntiTop_lead->p4() + recWJetFromAntiTop_sublead->p4());
		    fillWithOverFlow(histogram_AK12_BJet_cosThetaStar, cosThetaStar_BJet, evtWeight);
		  }
		  double theta_t_lead = comp_theta_t(
                    recWJetFromAntiTop_lead->p4(), recWBosonFromAntiTop->pullEta(), recWBosonFromAntiTop->pullPhi(),
		    recWJetFromAntiTop_sublead->p4());
		  fillWithOverFlow(histogram_AK12_theta_t_lead, theta_t_lead, evtWeight);
		  double theta_t_sublead = comp_theta_t(
                    recWJetFromAntiTop_sublead->p4(), recWBosonFromAntiTop->pullEta(), recWBosonFromAntiTop->pullPhi(),
		    recWJetFromAntiTop_lead->p4());
		  fillWithOverFlow(histogram_AK12_theta_t_sublead, theta_t_sublead, evtWeight);
		  isAK12FromAntiTop = true;
		  if ( recWBosonFromAntiTop->pt() > 130 ) {
		    isAK12FromAntiTop_fatjetPtGt130 = true;
		    if ( recWBosonFromAntiTop->subJet1()->pt() > 10. && recWBosonFromAntiTop->subJet2()->pt() > 10. ) {
		      isAK12FromAntiTop_fatjetPtGt130_and_subjetPtGt10 = true;
		      if ( jetSelectorAK12(*recWBosonFromAntiTop) ) {
			if ( selBJetFromAntiTop ) {
			  /*std::cout << "found semi-boosted hadronic anti-top:"
				    << " run = " << eventInfo.run << ", ls = " << eventInfo.lumi << ", event = " << eventInfo.event << std::endl;
			  std::cout << "AK12 jet:" << std::endl;
			  std::cout << (*recWBosonFromAntiTop);
			  std::cout << "b-jet:" << std::endl;
			  std::cout << (*selBJetFromAntiTop);*/
			}
			isAK12FromAntiTop_selected = true;
		      }
		    }
		  }
		}
	      }
	    }
	  }
	}
      }
    }

    if ( isAK12FromTop || isAK12FromAntiTop ) {
      cutFlowTable_2lss_1tau_AK12.update("rec AK12");
      if ( isAK12FromTop_fatjetPtGt130 || isAK12FromAntiTop_fatjetPtGt130 ) {
	cutFlowTable_2lss_1tau_AK12.update("rec AK12 passes fat-jet pT > 130 GeV");
	if ( isAK12FromTop_fatjetPtGt130_and_subjetPtGt10 || isAK12FromAntiTop_fatjetPtGt130_and_subjetPtGt10 ) {
	  cutFlowTable_2lss_1tau_AK12.update("rec AK12 passes sub-jet pT > 10 GeV for all subjets");
	}
	if ( isAK12FromTop_selected || isAK12FromAntiTop_selected ) {
	  cutFlowTable_2lss_1tau_AK12.update("rec AK12 passes all cuts");
	  if ( isBJetFromTop || isBJetFromAntiTop ) {
	    cutFlowTable_2lss_1tau_AK12.update("rec AK12 + BJet pair");
	    if ( selBJetFromTop_passesLoose || selBJetFromAntiTop_passesLoose ) {
	      cutFlowTable_2lss_1tau_AK12.update("rec BJet passes loose b-tagging working-point");
	      if ( selEventsFile_semiboosted ) {
		(*selEventsFile_semiboosted) << eventInfo.run << ':' << eventInfo.lumi << ':' << eventInfo.event << '\n';
	      }
	      if ( !(isHTTv2FromTop_selected || isHTTv2FromAntiTop_selected) ) {
		cutFlowTable_2lss_1tau_AK12.update("!HTTv2");
	      }
	    }
	  }
	}
      }
    }
    //-------------------------------------------------------------------------------------------------------------------

    //-------------------------------------------------------------------------------------------------------------------
    // case 3: all three jets resolved as separate jets,
    //         reconstructed by anti-kT algorithm with dR=0.4 (AK4)

    cutFlowTable_2lss_1tau_resolved.update("genJet triplet");

    bool isResolved = false;

    if ( (genBJetFromTop             && genBJetFromTop->pt()          > 20. &&
	  genWJetFromTop_lead        && genWJetFromTop_lead->pt()     > 20. &&
	  genWJetFromTop_sublead     && genWJetFromTop_lead->pt()     > 20.) ||
	 (genBJetFromAntiTop         && genBJetFromAntiTop->pt()      > 20. &&
	  genWJetFromAntiTop_lead    && genWJetFromAntiTop_lead->pt() > 20. &&
	  genWJetFromAntiTop_sublead && genWJetFromAntiTop_lead->pt() > 20.) ) {
      cutFlowTable_2lss_1tau_resolved.update("genJet triplet passes pT > 20 GeV");

      if ( (genBJetFromTop             && genBJetFromTop->absEta()          < 5.0 &&
	    genWJetFromTop_lead        && genWJetFromTop_lead->absEta()     < 5.0 &&
	    genWJetFromTop_sublead     && genWJetFromTop_lead->absEta()     < 5.0) ||
	   (genBJetFromAntiTop         && genBJetFromAntiTop->absEta()      < 5.0 &&
	    genWJetFromAntiTop_lead    && genWJetFromAntiTop_lead->absEta() < 5.0 &&
	    genWJetFromAntiTop_sublead && genWJetFromAntiTop_lead->absEta() < 5.0) ) {
	cutFlowTable_2lss_1tau_resolved.update("genJet triplet passes abs(eta) < 5.0");

	if ( (genBJetFromTop             && genBJetFromTop->absEta()      < 2.4) ||
	     (genBJetFromAntiTop         && genBJetFromAntiTop->absEta()  < 2.4) ) {
	  cutFlowTable_2lss_1tau_resolved.update("genBJet passes abs(eta) < 2.4");

	  if ( (genBJetFromTop             && genBJetFromTop->pt()          > 25. &&
		genWJetFromTop_lead        && genWJetFromTop_lead->pt()     > 25. &&
		genWJetFromTop_sublead     && genWJetFromTop_lead->pt()     > 25.) ||
	       (genBJetFromAntiTop         && genBJetFromAntiTop->pt()      > 25. &&
		genWJetFromAntiTop_lead    && genWJetFromAntiTop_lead->pt() > 25. &&
		genWJetFromAntiTop_sublead && genWJetFromAntiTop_lead->pt() > 25.) ) {
	    cutFlowTable_2lss_1tau_resolved.update("genJet triplet passes pT > 25 GeV");

	    if ( (genBJetFromTop             && genBJetFromTop->absEta()          < 2.4 &&
		  genWJetFromTop_lead        && genWJetFromTop_lead->absEta()     < 2.4 &&
		  genWJetFromTop_sublead     && genWJetFromTop_lead->absEta()     < 2.4) ||
		 (genBJetFromAntiTop         && genBJetFromAntiTop->absEta()      < 2.4 &&
		  genWJetFromAntiTop_lead    && genWJetFromAntiTop_lead->absEta() < 2.4 &&
		  genWJetFromAntiTop_sublead && genWJetFromAntiTop_lead->absEta() < 2.4) ) {
	      cutFlowTable_2lss_1tau_resolved.update("genJet triplet passes abs(eta) < 2.4");


	      if ( genTopQuark && genWBosonFromTop && genBJetFromTop && genWJetFromTop_lead && genWJetFromTop_sublead ) {
		fillWithOverFlow(histogram_ptTop, genTopQuark->pt(), evtWeight);
		fillWithOverFlow(histogram_etaTop, genTopQuark->eta(), evtWeight);
		double dRmaxTop = -1.;
		dRmaxTop = TMath::Max(dRmaxTop, deltaR(genTopQuark->p4(), genBJetFromTop->p4()));
		dRmaxTop = TMath::Max(dRmaxTop, deltaR(genTopQuark->p4(), genWJetFromTop_lead->p4()));
		dRmaxTop = TMath::Max(dRmaxTop, deltaR(genTopQuark->p4(), genWJetFromTop_sublead->p4()));
		fillWithOverFlow(histogram_dRmaxTop, dRmaxTop, evtWeight);
		fillWithOverFlow(histogram_ptW, genWBosonFromTop->pt(), evtWeight);
		fillWithOverFlow(histogram_etaW, genWBosonFromTop->eta(), evtWeight);
		double dRmaxW = -1.;
		dRmaxW = TMath::Max(dRmaxW, deltaR(genWBosonFromTop->p4(), genWJetFromTop_lead->p4()));
		dRmaxW = TMath::Max(dRmaxW, deltaR(genWBosonFromTop->p4(), genWJetFromTop_sublead->p4()));
		fillWithOverFlow(histogram_dRmaxW, dRmaxW, evtWeight);
		if ( dRmaxTop > 1.2 ) fillWithOverFlow(histogram_dRmaxW_dRmaxTopGt1p2, dRmaxW, evtWeight);
		if ( dRmaxTop > 1.5 ) fillWithOverFlow(histogram_dRmaxW_dRmaxTopGt1p5, dRmaxW, evtWeight);
		fillWithOverFlow(histogram_ptB, genBJetFromTop->pt(), evtWeight);
		fillWithOverFlow(histogram_etaB, genBJetFromTop->eta(), evtWeight);
	      }
	      if ( genAntiTopQuark && genWBosonFromAntiTop && genBJetFromAntiTop && genWJetFromAntiTop_lead && genWJetFromAntiTop_sublead ) {
		fillWithOverFlow(histogram_ptTop, genAntiTopQuark->pt(), evtWeight);
		fillWithOverFlow(histogram_etaTop, genAntiTopQuark->eta(), evtWeight);
		double dRmaxAntiTop = -1.;
		dRmaxAntiTop = TMath::Max(dRmaxAntiTop, deltaR(genAntiTopQuark->p4(), genBJetFromAntiTop->p4()));
		dRmaxAntiTop = TMath::Max(dRmaxAntiTop, deltaR(genAntiTopQuark->p4(), genWJetFromAntiTop_lead->p4()));
		dRmaxAntiTop = TMath::Max(dRmaxAntiTop, deltaR(genAntiTopQuark->p4(), genWJetFromAntiTop_sublead->p4()));
		fillWithOverFlow(histogram_dRmaxTop, dRmaxAntiTop, evtWeight);
		fillWithOverFlow(histogram_ptW, genWBosonFromAntiTop->pt(), evtWeight);
		fillWithOverFlow(histogram_etaW, genWBosonFromAntiTop->eta(), evtWeight);
		double dRmaxW = -1.;
		dRmaxW = TMath::Max(dRmaxW, deltaR(genWBosonFromAntiTop->p4(), genWJetFromAntiTop_lead->p4()));
		dRmaxW = TMath::Max(dRmaxW, deltaR(genWBosonFromAntiTop->p4(), genWJetFromAntiTop_sublead->p4()));
		fillWithOverFlow(histogram_dRmaxW, dRmaxW, evtWeight);
		if ( dRmaxAntiTop > 1.2 ) fillWithOverFlow(histogram_dRmaxW_dRmaxTopGt1p2, dRmaxW, evtWeight);
		if ( dRmaxAntiTop > 1.5 ) fillWithOverFlow(histogram_dRmaxW_dRmaxTopGt1p5, dRmaxW, evtWeight);
		fillWithOverFlow(histogram_ptB, genBJetFromAntiTop->pt(), evtWeight);
		fillWithOverFlow(histogram_etaB, genBJetFromAntiTop->eta(), evtWeight);
	      }


	      if ( (genBJetFromTop                                                                &&
		    genWJetFromTop_lead                                                           &&
		    genWJetFromTop_sublead                                                        &&
		    deltaR(genBJetFromTop->p4(),          genWJetFromTop_lead->p4())        > 0.4 &&
		    deltaR(genBJetFromTop->p4(),          genWJetFromTop_sublead->p4())     > 0.4 &&
		    deltaR(genWJetFromTop_lead->p4(),     genWJetFromTop_sublead->p4())     > 0.4) ||
		   (genBJetFromAntiTop                                                            &&
		    genWJetFromAntiTop_lead                                                       &&
		    genWJetFromAntiTop_sublead                                                    &&
		    deltaR(genBJetFromAntiTop->p4(),      genWJetFromAntiTop_lead->p4())    > 0.4 &&
		    deltaR(genBJetFromAntiTop->p4(),      genWJetFromAntiTop_sublead->p4()) > 0.4 &&
		    deltaR(genWJetFromAntiTop_lead->p4(), genWJetFromAntiTop_sublead->p4()) > 0.4) ) {
		cutFlowTable_2lss_1tau_resolved.update("dR(jet1,jet2) > 0.4 for any pair of genJets in triplet");


		const RecoJet* selBJetFromTop = 0;
		double dRmin_selBJetFromTop = 1.e+3;
		const RecoJet* selWJetFromTop_lead = 0;
		double dRmin_selWJetFromTop_lead = 1.e+3;
		const RecoJet* selWJetFromTop_sublead = 0;
		double dRmin_selWJetFromTop_sublead = 1.e+3;
		const RecoJet* selBJetFromAntiTop = 0;
		double dRmin_selBJetFromAntiTop = 1.e+3;
		const RecoJet* selWJetFromAntiTop_lead = 0;
		double dRmin_selWJetFromAntiTop_lead = 1.e+3;
		const RecoJet* selWJetFromAntiTop_sublead = 0;
		double dRmin_selWJetFromAntiTop_sublead = 1.e+3;
		for ( std::vector<const RecoJet*>::const_iterator selJet = selJets.begin(); selJet != selJets.end(); ++selJet ) {
		  if ( genBJetFromTop ) {
		    double dR_selBJetFromTop = deltaR((*selJet)->p4(), genBJetFromTop->p4());
		    if ( dR_selBJetFromTop < 0.3 && dR_selBJetFromTop < dRmin_selBJetFromTop ) {
		      selBJetFromTop = (*selJet);
		      dRmin_selBJetFromTop = dR_selBJetFromTop;
		    }
		  }
		  if ( genWJetFromTop_lead ) {
		    double dR_selWJetFromTop_lead = deltaR((*selJet)->p4(), genWJetFromTop_lead->p4());
		    if ( dR_selWJetFromTop_lead < 0.3 && dR_selWJetFromTop_lead < dRmin_selWJetFromTop_lead ) {
		      selWJetFromTop_lead = (*selJet);
		      dRmin_selWJetFromTop_lead = dR_selWJetFromTop_lead;
		    }
		  }
		  if ( genWJetFromTop_sublead ) {
		    double dR_selWJetFromTop_sublead = deltaR((*selJet)->p4(), genWJetFromTop_sublead->p4());
		    if ( dR_selWJetFromTop_sublead < 0.3 && dR_selWJetFromTop_sublead < dRmin_selWJetFromTop_sublead ) {
		      selWJetFromTop_sublead = (*selJet);
		      dRmin_selWJetFromTop_sublead = dR_selWJetFromTop_sublead;
		    }
		  }
		  if ( genBJetFromAntiTop ) {
		    double dR_selBJetFromAntiTop = deltaR((*selJet)->p4(), genBJetFromAntiTop->p4());
		    if ( dR_selBJetFromAntiTop < 0.3 && dR_selBJetFromAntiTop < dRmin_selBJetFromAntiTop ) {
		      selBJetFromAntiTop = (*selJet);
		      dRmin_selBJetFromAntiTop = dR_selBJetFromAntiTop;
		    }
		  }
		  if ( genWJetFromAntiTop_lead ) {
		    double dR_selWJetFromAntiTop_lead = deltaR((*selJet)->p4(), genWJetFromAntiTop_lead->p4());
		    if ( dR_selWJetFromAntiTop_lead < 0.3 && dR_selWJetFromAntiTop_lead < dRmin_selWJetFromAntiTop_lead ) {
		      selWJetFromAntiTop_lead = (*selJet);
		      dRmin_selWJetFromAntiTop_lead = dR_selWJetFromAntiTop_lead;
		    }
		  }
		  if ( genWJetFromAntiTop_sublead ) {
		    double dR_selWJetFromAntiTop_sublead = deltaR((*selJet)->p4(), genWJetFromAntiTop_sublead->p4());
		    if ( dR_selWJetFromAntiTop_sublead < 0.3 && dR_selWJetFromAntiTop_sublead < dRmin_selWJetFromAntiTop_sublead ) {
		      selWJetFromAntiTop_sublead = (*selJet);
		      dRmin_selWJetFromAntiTop_sublead = dR_selWJetFromAntiTop_sublead;
		    }
		  }
		}


		if ( (selBJetFromTop             &&
		      selWJetFromTop_lead        &&
		      selWJetFromTop_sublead    ) ||
		     (selBJetFromAntiTop         &&
		      selWJetFromAntiTop_lead    &&
		      selWJetFromAntiTop_sublead) ) {
		  cutFlowTable_2lss_1tau_resolved.update("selJet triplet");

		  if ( (selBJetFromTop                                                                &&
			selWJetFromTop_lead                                                           &&
			selWJetFromTop_sublead                                                        &&
			deltaR(selBJetFromTop->p4(),          selWJetFromTop_lead->p4())        > 0.3 &&
			deltaR(selBJetFromTop->p4(),          selWJetFromTop_sublead->p4())     > 0.3 &&
			deltaR(selWJetFromTop_lead->p4(),     selWJetFromTop_sublead->p4())     > 0.3) ||
		       (selBJetFromAntiTop                                                            &&
			selWJetFromAntiTop_lead                                                       &&
			selWJetFromAntiTop_sublead                                                    &&
			deltaR(selBJetFromAntiTop->p4(),      selWJetFromAntiTop_lead->p4())    > 0.3 &&
			deltaR(selBJetFromAntiTop->p4(),      selWJetFromAntiTop_sublead->p4()) > 0.3 &&
			deltaR(selWJetFromAntiTop_lead->p4(), selWJetFromAntiTop_sublead->p4()) > 0.3) ) {
		    cutFlowTable_2lss_1tau_resolved.update("dR(jet1,jet2) > 0.3 for any pair of selJets in triplet");

		    if ( selWJetFromTop_lead && selWJetFromTop_sublead && 1==0) {
					std::cout<<"here75"<<std::endl;
		      double cosThetaStar_WJet1 = comp_cosThetaStar(selWJetFromTop_lead->p4(), selWJetFromTop_lead->p4() + selWJetFromTop_sublead->p4());
		      fillWithOverFlow(histogram_resolved_WJet1_cosThetaStar, cosThetaStar_WJet1, evtWeight);
		      double cosThetaStar_BJet = comp_cosThetaStar(selBJetFromTop->p4(), selBJetFromTop->p4() + selWJetFromTop_lead->p4() + selWJetFromTop_sublead->p4());
		      fillWithOverFlow(histogram_resolved_BJet_cosThetaStar, cosThetaStar_BJet, evtWeight);
		      double theta_t_lead = comp_theta_t(
                        selWJetFromTop_lead->p4(), selWJetFromTop_lead->pullEta(), selWJetFromTop_lead->pullPhi(),
			selWJetFromTop_sublead->p4());
		      fillWithOverFlow(histogram_resolved_theta_t_lead, theta_t_lead, evtWeight);
		      double theta_t_sublead = comp_theta_t(
                        selWJetFromTop_sublead->p4(), selWJetFromTop_sublead->pullEta(), selWJetFromTop_sublead->pullPhi(),
			selWJetFromTop_lead->p4());
		      fillWithOverFlow(histogram_resolved_theta_t_sublead, theta_t_sublead, evtWeight);
		    }
		    if ( selWJetFromAntiTop_lead && selWJetFromAntiTop_sublead && 1==0) {
		      double cosThetaStar_WJet1 = comp_cosThetaStar(selWJetFromAntiTop_lead->p4(), selWJetFromAntiTop_lead->p4() + selWJetFromAntiTop_sublead->p4());
		      fillWithOverFlow(histogram_resolved_WJet1_cosThetaStar, cosThetaStar_WJet1, evtWeight);
		      double cosThetaStar_BJet = comp_cosThetaStar(selBJetFromAntiTop->p4(), selBJetFromAntiTop->p4() + selWJetFromAntiTop_lead->p4() + selWJetFromAntiTop_sublead->p4());
		      fillWithOverFlow(histogram_resolved_BJet_cosThetaStar, cosThetaStar_BJet, evtWeight);
		      double theta_t_lead = comp_theta_t(
                        selWJetFromAntiTop_lead->p4(), selWJetFromAntiTop_lead->pullEta(), selWJetFromAntiTop_lead->pullPhi(),
			selWJetFromAntiTop_sublead->p4());
		      fillWithOverFlow(histogram_resolved_theta_t_lead, theta_t_lead, evtWeight);
		      double theta_t_sublead = comp_theta_t(
                        selWJetFromAntiTop_sublead->p4(), selWJetFromAntiTop_sublead->pullEta(), selWJetFromAntiTop_sublead->pullPhi(),
			selWJetFromAntiTop_lead->p4());
		      fillWithOverFlow(histogram_resolved_theta_t_sublead, theta_t_sublead, evtWeight);
		    }

		    bool selBJetFromTop_passesLoose = false;
		    bool selBJetFromAntiTop_passesLoose = false;
		    for ( std::vector<const RecoJet*>::const_iterator selBJet_loose = selBJets_loose.begin();
			  selBJet_loose != selBJets_loose.end(); ++selBJet_loose ) {
		      if ( selBJetFromTop && deltaR(selBJetFromTop->p4(), (*selBJet_loose)->p4()) < 0.3 ) {
			selBJetFromTop_passesLoose = true;
		      }
		      if ( selBJetFromAntiTop && deltaR(selBJetFromAntiTop->p4(), (*selBJet_loose)->p4()) < 0.3 ) {
			selBJetFromAntiTop_passesLoose = true;
		      }
		    }
		    if ( selBJetFromTop_passesLoose || selBJetFromAntiTop_passesLoose ) {
		      cutFlowTable_2lss_1tau_resolved.update(">= 1 selBJet passes loose b-tagging working-point");
		      /*if ( selWJetFromTop_lead && selWJetFromTop_sublead && selBJetFromTop_passesLoose ) {
			std::cout << "found resolved hadronic top:";
		      }
		      if ( selBJetFromAntiTop_passesLoose && selWJetFromAntiTop_lead && selWJetFromAntiTop_sublead ) {
			std::cout << "found resolved hadronic anti-top:";
		      }
		      std::cout << " run = " << eventInfo.run << ", ls = " << eventInfo.lumi << ", event = " << eventInfo.event << std::endl;
		      std::cout << "1st jet from W:" << std::endl;
		      if ( selWJetFromTop_lead     ) std::cout << (*selWJetFromTop_lead);
		      if ( selWJetFromAntiTop_lead ) std::cout << (*selWJetFromAntiTop_lead);
		      std::cout << "2nd jet from W:" << std::endl;
		      if ( selWJetFromTop_sublead     ) std::cout << (*selWJetFromTop_sublead);
		      if ( selWJetFromAntiTop_sublead ) std::cout << (*selWJetFromAntiTop_sublead);
		      std::cout << "b-jet:" << std::endl;
		      if ( selBJetFromTop     ) std::cout << (*selBJetFromTop);
		      if ( selBJetFromAntiTop ) std::cout << (*selBJetFromAntiTop);*/
		      isResolved = true;
		    }
		  }
		}
	      }
	    }
	  }
	}
      }
    }



    if ( isResolved ) {
      cutFlowTable_2lss_1tau_resolved.update("rec resolved");
      if ( selEventsFile_resolved ) {
	(*selEventsFile_resolved) << eventInfo.run << ':' << eventInfo.lumi << ':' << eventInfo.event << '\n';
      }
      if ( !(isHTTv2FromTop_selected || isHTTv2FromAntiTop_selected) ) {
	cutFlowTable_2lss_1tau_resolved.update("!HTTv2");
	if ( !((isAK12FromTop_selected && isBJetFromTop) || (isAK12FromAntiTop_selected && isBJetFromAntiTop)) ) {
	  cutFlowTable_2lss_1tau_resolved.update("!HTTv2 && !AK12");
	}
      }
			if ( !((isAK12FromTop_selected && isBJetFromTop) || (isAK12FromAntiTop_selected && isBJetFromAntiTop)) ) {
				cutFlowTable_2lss_1tau_resolved.update("!AK12");
			}
    }
    //-------------------------------------------------------------------------------------------------------------------

    ++selectedEntries;
    selectedEntries_weighted += evtWeight;
    histogram_selectedEntries->Fill(0.);
  }

  std::cout << "max num. Entries = " << inputTree -> getCumulativeMaxEventCount()
            << " (limited by " << maxEvents << ") processed in "
            << inputTree -> getProcessedFileCount() << " file(s) (out of "
            << inputTree -> getFileCount() << ")\n"
            << " analyzed = " << analyzedEntries << '\n'
            << " selected = " << selectedEntries << " (weighted = " << selectedEntries_weighted << ")\n\n"
            << "cut-flow table" << std::endl;
  cutFlowTable_2lss_1tau.print(std::cout);
  std::cout << "HTTv2:" << std::endl;
  cutFlowTable_2lss_1tau_HTTv2.print(std::cout);
  std::cout << "AK12:" << std::endl;
  cutFlowTable_2lss_1tau_AK12.print(std::cout);
  std::cout << "resolved:" << std::endl;
  cutFlowTable_2lss_1tau_resolved.print(std::cout);
  std::cout << std::endl;

  delete dataToMCcorrectionInterface;

  delete selEventsFile;
  delete selEventsFile_boosted;
  delete selEventsFile_semiboosted;
  delete selEventsFile_resolved;

  delete muonReader;
  delete electronReader;
  delete hadTauReader;
  delete jetReader;
  delete metReader;
  delete genLeptonReader;
  delete genHadTauReader;
  delete genJetReader;
  delete lheInfoReader;
  delete eventWeightManager;
/*
  delete hadTopTagger;
 */
  delete inputTree;

  clock.Show("analyze_hadTopTagger_gen");

  return EXIT_SUCCESS;
}
