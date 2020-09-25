#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronReader.h" // RecoElectronReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonReader.h" // RecoMuonReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetReader.h" // RecoJetReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoMEtReader.h" // RecoMEtReader
#include "tthAnalysis/HiggsToTauTau/interface/GenMEtReader.h" // GenMEtReader
#include "tthAnalysis/HiggsToTauTau/interface/GenLeptonReader.h" // GenLeptonReader
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTauReader.h" // GenHadTauReader
#include "tthAnalysis/HiggsToTauTau/interface/GenPhotonReader.h" // GenPhotonReader
#include "tthAnalysis/HiggsToTauTau/interface/GenJetReader.h" // GenJetReader
#include "tthAnalysis/HiggsToTauTau/interface/GenParticleReader.h" // GenParticleReader
#include "tthAnalysis/HiggsToTauTau/interface/LHEInfoReader.h" // LHEInfoReader
#include "tthAnalysis/HiggsToTauTau/interface/EventInfoReader.h" // EventInfoReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoVertexReader.h" // RecoVertexReader
#include "tthAnalysis/HiggsToTauTau/interface/MEtFilterReader.h" // MEtFilterReader
#include "tthAnalysis/HiggsToTauTau/interface/ObjectMultiplicity.h" // ObjectMultiplicity
#include "tthAnalysis/HiggsToTauTau/interface/ObjectMultiplicityReader.h" // ObjectMultiplicityReader

#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorLoose.h" // RecoElectronCollectionSelectorLoose
#include "hhAnalysis/multilepton/interface/RecoElectronCollectionSelectorFakeable_hh_multilepton.h" // RecoElectronCollectionSelectorFakeable_hh_multilepton
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorFakeable.h" // RecoElectronCollectionSelectorFakeable
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorTight.h" // RecoElectronCollectionSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorLoose.h" // RecoMuonCollectionSelectorLoose
#include "hhAnalysis/multilepton/interface/RecoMuonCollectionSelectorFakeable_hh_multilepton.h" // RecoMuonCollectionSelectorFakeable_hh_multilepton
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorFakeable.h" // RecoMuonCollectionSelectorFakeable
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorTight.h" // RecoMuonCollectionSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelector.h" // RecoJetCollectionSelector
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelectorBtag.h" // RecoJetSelectorBtag/Loose
#include "tthAnalysis/HiggsToTauTau/interface/MEtFilterSelector.h" // MEtFilterSelector

#include "tthAnalysis/HiggsToTauTau/interface/GenEvtHistManager.h" // GenEvtHistManager
#include "tthAnalysis/HiggsToTauTau/interface/LHEInfoHistManager.h" // LHEInfoHistManager
#include "tthAnalysis/HiggsToTauTau/interface/L1PreFiringWeightReader.h" // L1PreFiringWeightReader
#include "tthAnalysis/HiggsToTauTau/interface/MEtFilterHistManager.h" // MEtFilterHistManager
#include "tthAnalysis/HiggsToTauTau/interface/DYMCReweighting.h" // DYMCReweighting
#include "tthAnalysis/HiggsToTauTau/interface/DYMCNormScaleFactors.h" // DYMCNormScaleFactors

#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionGenMatcher.h" // Reco*CollectionGenMatcher
#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionCleaner.h" // Reco*CollectionCleaner

#include "tthAnalysis/HiggsToTauTau/interface/EventInfo.h" // EventInfo
#include "tthAnalysis/HiggsToTauTau/interface/cutFlowTable.h" // cutFlowTableType
#include "tthAnalysis/HiggsToTauTau/interface/NtupleFillerBDT.h" // NtupleFillerBDT
#include "tthAnalysis/HiggsToTauTau/interface/TTreeWrapper.h" // TTreeWrapper
#include "tthAnalysis/HiggsToTauTau/interface/RunLumiEventSelector.h" // RunLumiEventSelector
#include "tthAnalysis/HiggsToTauTau/interface/EvtWeightManager.h" // EvtWeightManager
#include "tthAnalysis/HiggsToTauTau/interface/EvtWeightRecorder.h" // EvtWeightRecorder
#include "tthAnalysis/HiggsToTauTau/interface/BtagSFRatioFacility.h" // BtagSFRatioFacility

#include "tthAnalysis/HiggsToTauTau/interface/convert_to_ptrs.h" // convert_to_ptrs()
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // Era::k2017, getBTagWeight_option()
#include "tthAnalysis/HiggsToTauTau/interface/sysUncertOptions.h" // get*_option()
#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // fillWithOverflow
#include "tthAnalysis/HiggsToTauTau/interface/leptonFakeRateAuxFunctions.h"
#include "tthAnalysis/HiggsToTauTau/interface/hltPath_LeptonFakeRate.h" // hltPath_LeptonFakeRate, create_hltPaths_LeptonFakeRate(), hltPaths_LeptonFakeRate_delete()
#include "tthAnalysis/HiggsToTauTau/interface/hltPathReader.h" // hltPathReader
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_2016.h" // Taken from HH 3l
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_2017.h" // Taken from HH 3l
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_2018.h" // Taken from HH 3l
#include "tthAnalysis/HiggsToTauTau/interface/jetToTauFakeRateAuxFunctions.h" // getEtaBin(), getPtBin()
#include "tthAnalysis/HiggsToTauTau/interface/leptonTypes.h" // kElectron, kMuon, getLeptonType

#if __has_include (<FWCore/ParameterSetReader/interface/ParameterSetReader.h>)
#  include <FWCore/ParameterSetReader/interface/ParameterSetReader.h> // edm::readPSetsFrom()
#else
#  include <FWCore/PythonParameterSet/interface/MakeParameterSets.h> // edm::readPSetsFrom()
#endif

#include <PhysicsTools/FWLite/interface/TFileService.h> // fwlite::TFileService
#include <DataFormats/FWLite/interface/InputSource.h> // fwlite::InputSource
#include <DataFormats/FWLite/interface/OutputFiles.h> // fwlite::OutputFiles
#include <DataFormats/Math/interface/deltaR.h>

#include <TRandom3.h> // TRandom3
#include <TBenchmark.h> // TBenchmark
#include <TH1.h> // TH1, TH1D
#include <TMath.h> // TMath::Pi()
#include <TROOT.h> // TROOT
#include <Math/Vector3D.h> // Needed for ROOT::Math::XYZVector

#include <boost/math/special_functions/sign.hpp> // boost::math::sign()
#include <boost/algorithm/string/predicate.hpp> // boost::starts_with(), boost::ends_with()

#include <fstream> // std::ofstream

typedef std::vector<std::string> vstring;
typedef std::vector<double> vdouble;

int printLevel = 0; // set to 1 to add eventWeight recorder

void CheckPhotonMatch(const RecoElectron & preselElectron, std::vector<GenPhoton> genPhotons, double dR = 0.5)
{

  int photon_counter = 0;
  for(std::vector<GenPhoton>::iterator genPhoton = genPhotons.begin(); genPhoton != genPhotons.end(); genPhoton++) {
    //Particle::LorentzVector electron_4_vector =  preselElectron.p4();
    //Particle::LorentzVector genPhoton_4_vector = (*genPhoton).p4();
    double dR_lep_Genphoton = deltaR(preselElectron.eta(), preselElectron.phi(), (*genPhoton).eta(), (*genPhoton).phi());
    if(dR_lep_Genphoton <= dR){
      photon_counter++;
      std::cout<< " genPhoton # " << photon_counter << std::endl;
      std::cout<< " This genPhoton is within dR <= "  << dR << " from the selected RecoElectron " << std::endl;
      std::cout<< " genPhoton: " << (*genPhoton) << std::endl; 
    }
  }
  std::cout << "There are " << photon_counter << " genphotons matched to this RecoElectron"<< std::endl;
 
}

void CheckLeptonMatch(const RecoElectron & preselElectron, std::vector<GenLepton> genLeptons, double dR = 0.5)
{

  int genLepton_counter = 0;
  for(std::vector<GenLepton>::iterator genLepton = genLeptons.begin(); genLepton != genLeptons.end(); genLepton++) {
    //Particle::LorentzVector electron_4_vector =  preselElectron.p4();
    //Particle::LorentzVector genLepton_4_vector = (*genLepton).p4();
    double dR_lep_GenLepton = deltaR(preselElectron.eta(), preselElectron.phi(), (*genLepton).eta(), (*genLepton).phi());
    if(dR_lep_GenLepton <= dR){
      genLepton_counter++;
      std::cout<< " genLepton # " << genLepton_counter << std::endl;
      std::cout<< " This genLepton is within dR <= "  << dR << " from the selected RecoElectron " << std::endl;
      std::cout<< " genLepton: " << (*genLepton) << std::endl; 
    }
  }
  std::cout << "There are " << genLepton_counter << " genLeptons matched to this RecoElectron"<< std::endl;
 
}

void CheckGenParticleMatch(const RecoElectron & preselElectron, std::vector<GenParticle> genParticles, double dR = 0.5, std::string label = "genParticle")
{
  int genParticle_counter = 0;
  for(std::vector<GenParticle>::iterator genParticle = genParticles.begin(); genParticle != genParticles.end(); genParticle++) {
    //Particle::LorentzVector electron_4_vector =  preselElectron.p4();
    //Particle::LorentzVector genParticle_4_vector = (*genParticle).p4();
    double dR_lep_GenParticle = deltaR(preselElectron.eta(), preselElectron.phi(), (*genParticle).eta(), (*genParticle).phi());
    if(dR_lep_GenParticle <= dR){
      genParticle_counter++;
      std::cout<< " genParticle # " << genParticle_counter << std::endl;
      std::cout<< " This genParticle is within dR <= "  << dR << " from the selected RecoElectron " << std::endl;
      std::cout<< " genParticle: " << (*genParticle) << std::endl; 
    }
  }
  std::cout << "There are " << genParticle_counter << " " << label << "s matched to this RecoElectron"<< std::endl;
 
}


struct JetAndTrigPrescaleCollector
{
  JetAndTrigPrescaleCollector(const std::vector<const RecoJet *>& selJets,
			      const std::vector<const RecoJet *>& selBJets_loose,
			      const std::vector<const RecoJet*>& selBJets_medium,
			      const double prescaleWeight,
			      const bool isTrigFired)
    : selJets_(selJets)
    , selBJets_loose_(selBJets_loose)
    , selBJets_medium_(selBJets_medium)
    , prescaleWeight_(prescaleWeight)
    , isTrigFired_(isTrigFired)  
  {
    selJets_size_ = selJets_.size();
    selBJets_loose_size_ = selBJets_loose_.size();
    selBJets_medium_size_ = selBJets_medium_.size();
  }

  ~JetAndTrigPrescaleCollector() {}
  const std::vector<const RecoJet *>& selJets_;
  const std::vector<const RecoJet *>& selBJets_loose_;
  const std::vector<const RecoJet *>& selBJets_medium_;
  const double prescaleWeight_;
  const bool isTrigFired_;
  int selJets_size_;
  int selBJets_loose_size_;
  int selBJets_medium_size_;

  double Get_prescaleWeight() const
  {
    return prescaleWeight_;
  }

  int Get_selJets_size() const
  {
    return selJets_size_;
  }

  int Get_selBJets_loose_size() const
  {
    return selBJets_loose_size_;
  }

  int Get_selBJets_medium_size() const
  {
    return selBJets_medium_size_;
  }

  bool Get_TrigDecision() const
  {
    return isTrigFired_;
  }

  std::vector<const RecoJet *> Get_selJets()
  {
    return selJets_;
  }


};

JetAndTrigPrescaleCollector* 
PrescaleAndJetExtractor(std::vector<const RecoLepton*> preselLeptonsFull, 
			std::vector<const RecoJet*> jet_ptrs,
			std::vector<hltPath_LeptonFakeRate *> triggers_mu,
			std::vector<hltPath_LeptonFakeRate *> triggers_e,
			const std::string era_string,
			const double minConePt_global_e,
			const double minRecoPt_global_e,
			const double minConePt_global_mu,
			const double minRecoPt_global_mu,
			const bool use_triggers_1e,
			const bool use_triggers_2e,
			const bool use_triggers_1mu,
			const bool use_triggers_2mu,
			const bool isMC,
			bool isDEBUG = false)
{
  JetAndTrigPrescaleCollector* JetAndTrigPrescaleCollector_ptr = 0;
  //----Splitting preseLeptons into preselMuons and preselElectrons
  std::vector<const RecoElectron *> preselElectrons;
  std::vector<const RecoMuon *> preselMuons;
  for(unsigned int i = 0; i < preselLeptonsFull.size(); i++)
    { // loop over preselleptons  
      if(preselLeptonsFull[i]->is_muon()){
	const RecoMuon* preselMuon_ptr  = dynamic_cast<const RecoMuon*>(preselLeptonsFull[i]);
	preselMuons.push_back(preselMuon_ptr);
      }

      if(preselLeptonsFull[i]->is_electron()){
	const RecoElectron* preselElectron_ptr  = dynamic_cast<const RecoElectron*>(preselLeptonsFull[i]);
	preselElectrons.push_back(preselElectron_ptr);
      }
    }// preselleptons loop ends
  //------------------

  //-------TRIGGER CUTS -----
  RecoJetCollectionCleaner jetCleaner_dR07(0.7, isDEBUG);
  const Era era = get_era(era_string);
  RecoJetCollectionSelector jetSelector(era);
  RecoJetCollectionSelectorBtagLoose jetSelectorBtagLoose(era);
  RecoJetCollectionSelectorBtagMedium jetSelectorBtagMedium(era);
  std::vector<const RecoJet *> cleanedJets;
  std::vector<const RecoJet *> selJets;
  std::vector<const RecoJet*> selBJets_loose;
  std::vector<const RecoJet*> selBJets_medium;

  bool isTriggered_1mu = false;
  bool isTriggered_2mu = false;
  for(const hltPath_LeptonFakeRate * const hltPath_iter: triggers_mu)
    {//loop over mu triggers
      hltPath_iter->setIsTriggered(false); // resetting the bool to false

      if(! (hltPath_iter->getValue() >= 1))
	{
	  continue; // require trigger to fire
	}

      for(const RecoMuon * const preselMuon_ptr: preselMuons)
	{// loop over muons
	  const RecoMuon & preselMuon = *preselMuon_ptr;

	  // Giovanni's selection for global lepton reco and cone pt cuts
	  if(!(preselMuon.cone_pt() > minConePt_global_mu && preselMuon.pt() > minRecoPt_global_mu))
	    {
	      continue;
	    }

	  const std::vector<const RecoMuon*> tmp_leptons = { preselMuon_ptr };
	  cleanedJets = jetCleaner_dR07(jet_ptrs, tmp_leptons);
	  selJets = jetSelector(cleanedJets);
	  selBJets_loose = jetSelectorBtagLoose(cleanedJets);
	  selBJets_medium = jetSelectorBtagMedium(cleanedJets);

	  for(const RecoJet * const selJet: selJets)
	    {// loop over jets
	      if(deltaR(preselMuon.p4(), selJet->p4()) <= 0.7)
		{
		  continue;
		}

	      if(!( preselMuon.cone_pt() >= hltPath_iter->getMinPt()    &&
		    preselMuon.cone_pt() <  hltPath_iter->getMaxPt()    &&
		    selJet->pt()         >  hltPath_iter->getMinJetPt() &&
		    preselMuon.pt()      >  hltPath_iter->getMinRecoPt()))
		{
		  continue;
		}else{
		hltPath_iter->setIsTriggered(true);
		break;
	      }
	    }// jet loop ends
	}//muon loop ends
      if(hltPath_iter->isTriggered())
	{
	  isTriggered_2mu |= hltPath_iter->is_trigger_2mu();
	  isTriggered_1mu |= hltPath_iter->is_trigger_1mu();
	}
    }//mu trigger loop ends


  bool isTriggered_1e = false;
  bool isTriggered_2e = false;
  for(const hltPath_LeptonFakeRate * const hltPath_iter: triggers_e)
    {//loop over e triggers
      hltPath_iter->setIsTriggered(false); // resetting the bool to false

      if(! (hltPath_iter->getValue() >= 1))
	{
	  continue; // require trigger to fire
	}

      for(const RecoElectron * const preselElectron_ptr: preselElectrons)
	{// loop over e
	  const RecoElectron & preselElectron = *preselElectron_ptr;

	  if(!(preselElectron.cone_pt() > minConePt_global_e && preselElectron.pt() > minRecoPt_global_e))
	    {
	      continue;
	    }
	  const std::vector<const RecoElectron *> tmp_leptons = { preselElectron_ptr };
	  cleanedJets = jetCleaner_dR07(jet_ptrs, tmp_leptons);
	  selJets = jetSelector(cleanedJets);
	  selBJets_loose = jetSelectorBtagLoose(cleanedJets);
	  selBJets_medium = jetSelectorBtagMedium(cleanedJets);
	  for(const RecoJet * const selJet: selJets)
	    {// loop over jets
	      if(deltaR(preselElectron.p4(), selJet->p4()) <= 0.7)
		{
		  continue;
		}

	      if(!(preselElectron.cone_pt() >= hltPath_iter->getMinPt()    &&
		   preselElectron.cone_pt() <  hltPath_iter->getMaxPt()    &&
		   selJet->pt()             >  hltPath_iter->getMinJetPt() &&
		   preselElectron.pt()      > hltPath_iter->getMinRecoPt() ))
		{
		  continue;
		}else{
		hltPath_iter->setIsTriggered(true);
                break;
	      }
	    }// jet loop ends
	}// e loop ends
      if(hltPath_iter->isTriggered())
	{
	  isTriggered_2e |= hltPath_iter->is_trigger_2e();
	  isTriggered_1e |= hltPath_iter->is_trigger_1e();
	}
    }//e trigger loop ends

  const bool selTrigger_1e = use_triggers_1e && isTriggered_1e;
  const bool selTrigger_2e = use_triggers_2e && isTriggered_2e;
  const bool selTrigger_1mu = use_triggers_1mu && isTriggered_1mu;
  const bool selTrigger_2mu = use_triggers_2mu && isTriggered_2mu;
  //------------------------

  bool isTrigFired = (selTrigger_1e || selTrigger_2e || selTrigger_1mu || selTrigger_2mu) ? true : false;

  std::vector<hltPath_LeptonFakeRate *> triggers_all_current;
  triggers_all_current.insert(triggers_all_current.end(), triggers_e.begin(), triggers_e.end());
  triggers_all_current.insert(triggers_all_current.end(), triggers_mu.begin(), triggers_mu.end());  

  
  // prescale weight
  double prob_all_trigger_fail = 1.0;
  if(isMC)
    {

      for(const hltPath_LeptonFakeRate * const hltPath_iter: triggers_all_current)
	{
	  if(hltPath_iter->isTriggered())
	    {
	      prob_all_trigger_fail *= (1. - (1. / hltPath_iter->getPrescale()));
	    }
	}
    }
  //JetAndTrigPrescaleCollector_ptr = new JetAndTrigPrescaleCollector(selJets, selBJets_loose, selBJets_medium, prob_all_trigger_fail, isTrigFired);
  double prescale_weight = 1 - prob_all_trigger_fail;  
  //std::cout<< "Function prescale_weight " << prescale_weight << std::endl;
  JetAndTrigPrescaleCollector_ptr = new JetAndTrigPrescaleCollector(selJets, selBJets_loose, selBJets_medium, prescale_weight, isTrigFired);
  //printf("PrescaleAndJetExtractor():: prescale_weight %e,  prob_all_trigger_fail %e \n",prescale_weight,prob_all_trigger_fail);
  return JetAndTrigPrescaleCollector_ptr;
}

void ApplyDYNormSF2(JetAndTrigPrescaleCollector* JetAndTrigPrescaleCollector_ptr,
		    EvtWeightRecorder &evtWeightRecorder,
		    const bool isMC,
		    const bool apply_DYMCNormScaleFactors,
		    DYMCNormScaleFactors* dyNormScaleFactors,
		    std::vector<GenParticle> genTauLeptons)
{
  assert(JetAndTrigPrescaleCollector_ptr != 0);
  if(isMC)
    {
      // DY Norm Scale factor weight
      if(apply_DYMCNormScaleFactors)
	{
	  evtWeightRecorder.record_dy_norm(dyNormScaleFactors, 
					   genTauLeptons, 
					   JetAndTrigPrescaleCollector_ptr->Get_selJets_size(), 
					   JetAndTrigPrescaleCollector_ptr->Get_selBJets_loose_size(), 
					   JetAndTrigPrescaleCollector_ptr->Get_selBJets_medium_size());
	}
      
    }
}

void ApplyBTagSF2(const std::vector<const RecoJet*> selJets,
		 EvtWeightRecorder &evtWeightRecorder,
		 const bool isMC,
		 BtagSFRatioFacility* btagSFRatioFacility)
{
  //std::cout<< "selJets.size(): "<< selJets.size() << std::endl;
  if(isMC)
    {
      //--- compute event-level weight for data/MC correction of b-tagging efficiency and mistag rate
      evtWeightRecorder.record_btagWeight(selJets);
      if(btagSFRatioFacility)
	{
	  evtWeightRecorder.record_btagSFRatio(btagSFRatioFacility, selJets.size());
	  //std::cout << "ApplyBTagSF2():: evtWeightRecorder: " << evtWeightRecorder << std::endl;
	}

    }
}

void 
ApplyDataToMCCorrection(const RecoLepton* preselLepton,
			Data_to_MC_CorrectionInterface_Base * dataToMCcorrectionInterface,
			EvtWeightRecorder &evtWeightRecorder)
{
  //std::cout << "preselLepton " << " pdgId: "<< preselLepton->pdgId() << " eta: " << preselLepton->eta() << " pt: " << preselLepton->pt() << " cone_pt: " << preselLepton->cone_pt() << std::endl;
  dataToMCcorrectionInterface->setLeptons({ preselLepton }); // requireChargeGenMatch set to false for preselLepton by default
  
  //--- apply data/MC corrections for efficiencies for lepton to pass loose identification and isolation criteria                                                                               
  evtWeightRecorder.record_leptonIDSF_recoToLoose(dataToMCcorrectionInterface);

  //--- apply data/MC corrections for efficiencies of leptons passing the loose identification and isolation criteria                                                                           
  //    to also pass the tight identification and isolation criteria                                                                                                                            
  if(preselLepton->isTight()){ // Signal region
    evtWeightRecorder.record_leptonIDSF_looseToTight(dataToMCcorrectionInterface);    
  }else if(preselLepton->isFakeable()){ // Fakeable region
    evtWeightRecorder.record_leptonSF(dataToMCcorrectionInterface->getSF_leptonID_and_Iso_looseToFakeable());
  }
  //std::cout<<" evtWeightRecorder.get(central): " << evtWeightRecorder.get("central") << std::endl;

}


bool METFilterDecision(const bool isMC,
		       const bool apply_met_filters,
		       MEtFilter metFilter,
		       const edm::ParameterSet cfgMEtFilter)
{
    bool passesMETFilter = false;
    const MEtFilterSelector metFilterSelector(cfgMEtFilter, isMC);
    if(apply_met_filters)
      {
	if(metFilterSelector(metFilter))
	  {
	    passesMETFilter = true;
	  }
      }
    return passesMETFilter;
}

void
FillNtuples(const RecoLepton* preselLepton, 
	    EventInfo eventInfo,
	    double evtWeight,
	    double evtWeight_wo_TrigPrescale,
	    const double mT, 
	    const double mT_fix,
	    const int passesTrigger,
	    NtupleFillerBDT<float, int>* bdt_filler = 0)
{
  if(preselLepton->is_electron())
    {
      const RecoElectron* preselElectron_ptr  = dynamic_cast<const RecoElectron*>(preselLepton);
      const RecoElectron & preselElectron = *preselElectron_ptr;

      int EGamma_MVA_WP = 0;
      if(preselElectron.mvaID_POG(EGammaWP::WPL)){
        EGamma_MVA_WP = 1;
      }

      if(preselElectron.mvaID_POG(EGammaWP::WP90)){
        EGamma_MVA_WP = 2;
      }

      if(preselElectron.mvaID_POG(EGammaWP::WP80)){
        EGamma_MVA_WP = 3;
      }

      //----Fill the Ntuples for preselElectron
      if(bdt_filler)
	{
	  // FILL THE ELECTRON BRANCHES
	  bdt_filler->operator()({eventInfo.run, eventInfo.lumi, eventInfo.event})
	    ("passesTrigger", passesTrigger)
	    ("mT_fix", mT_fix)
	    ("mT", mT)
	    ("cone_pt", preselElectron.cone_pt())
	    ("pt", preselElectron.pt())
	    ("eta", preselElectron.eta())
	    ("dxy", preselElectron.dxy())
	    ("dz", preselElectron.dz())
	    ("sip3d", preselElectron.sip3d())
	    ("iso", preselElectron.relIso())
	    ("sigma_ieie", preselElectron.sigmaEtaEta())
	    ("HbyE", preselElectron.HoE())
	    ("OnebyEminusOnebyP", preselElectron.OoEminusOoP())
	    ("JetRelIso", preselElectron.jetRelIso())
	    ("tth_mva", preselElectron.mvaRawTTH())
	    ("Conv_reject", preselElectron.passesConversionVeto() ? 1 : 0)
	    ("miss_hits", preselElectron.nLostHits())
	    ("EGamma_MVA_WP", EGamma_MVA_WP)
	    ("DeepJet_WP", preselElectron.jetBtagCSV(false))
	    ("assocJet_pt", preselElectron.assocJet_pt())
	    ("evtWeight", evtWeight)
	    ("evtWeight_wo_TrigPrescale", evtWeight_wo_TrigPrescale)
	    ("isTight", preselElectron.isTight() ? 1 : 0)
	    ("isFakeable", preselElectron.isFakeable() ? 1 : 0)
	    ("lep_isgenMatchedFake", (!(preselElectron.genLepton() || preselElectron.genHadTau() || preselElectron.genPhoton())) ? 1 : 0)
	    ("lep_isgenMatchedToLepton", preselElectron.genLepton() ? 1 : 0)
	    ("lep_isgenMatchedToTau", preselElectron.genHadTau() ? 1 : 0)
	    ("lep_isgenMatchedToPhoton", preselElectron.genPhoton() ? 1 : 0)
	    .fill();
      }
    }

  if(preselLepton->is_muon())
    {
      const RecoMuon* preselMuon_ptr  = dynamic_cast<const RecoMuon*>(preselLepton);
      const RecoMuon & preselMuon = *preselMuon_ptr;

      int PFMuon_WP = 0;
      if(preselMuon.passesLooseIdPOG()){
        PFMuon_WP = 1;
      }
      if(preselMuon.passesMediumIdPOG()){
        PFMuon_WP = 2;
      }

      if(bdt_filler){
        // FILL THE MUON BRANCHES
	bdt_filler->operator()({eventInfo.run, eventInfo.lumi, eventInfo.event})
	  ("passesTrigger", passesTrigger)
          ("mT_fix", mT_fix)
          ("mT", mT)
          ("cone_pt", preselMuon.cone_pt())
          ("pt", preselMuon.pt())
          ("eta", preselMuon.eta())
          ("dxy", preselMuon.dxy())
          ("dz", preselMuon.dz())
          ("sip3d", preselMuon.sip3d())
          ("iso", preselMuon.relIso())
          ("JetRelIso", preselMuon.jetRelIso())
          ("tth_mva", preselMuon.mvaRawTTH())
          ("PFMuon_WP", PFMuon_WP)
          ("assocJet_pt", preselMuon.assocJet_pt())
          ("DeepJet_WP", preselMuon.jetBtagCSV(false))
          ("evtWeight", evtWeight)
	  ("evtWeight_wo_TrigPrescale", evtWeight_wo_TrigPrescale)
          ("isTight", preselMuon.isTight() ? 1 : 0)
          ("isFakeable", preselMuon.isFakeable() ? 1 : 0)
          ("lep_isgenMatchedFake", (!(preselMuon.genLepton() || preselMuon.genHadTau())) ? 1 : 0)
          ("lep_isgenMatchedToLepton", preselMuon.genLepton() ? 1 : 0)
          ("lep_isgenMatchedToTau", preselMuon.genHadTau() ? 1 : 0)
          .fill();
      }
    }
  
}

int
LeptonPlusJet(Data_to_MC_CorrectionInterface_Base * dataToMCcorrectionInterface_ntuple,
	      std::vector<const RecoLepton*> preselLeptonsFull, 
              std::vector<const RecoJet*> jet_ptrs,
	      const std::string era_string,
	      const bool apply_met_filters,
	      MEtFilter metFilter,
	      const edm::ParameterSet cfgMEtFilter,
	      const GenMEt genmet, 
	      const RecoMEt met, 
	      const double METScaleSyst, 
	      const METSyst metSyst_option,
	      numerator_and_denominatorHistManagers * histograms_e_numerator_incl_LeptonPlusJet,
	      std::vector<numerator_and_denominatorHistManagers *> histograms_e_numerator_binned_LeptonPlusJet,
	      numerator_and_denominatorHistManagers * histograms_e_denominator_incl_LeptonPlusJet,
	      std::vector<numerator_and_denominatorHistManagers *> histograms_e_denominator_binned_LeptonPlusJet,
	      numerator_and_denominatorHistManagers * histograms_mu_numerator_incl_LeptonPlusJet,
	      std::vector<numerator_and_denominatorHistManagers *> histograms_mu_numerator_binned_LeptonPlusJet,
	      numerator_and_denominatorHistManagers * histograms_mu_denominator_incl_LeptonPlusJet,
	      std::vector<numerator_and_denominatorHistManagers *> histograms_mu_denominator_binned_LeptonPlusJet,
	      numerator_and_denominatorHistManagers * histograms_e_numerator_incl_LeptonPlusJet_woTrigger,
	      std::vector<numerator_and_denominatorHistManagers *> histograms_e_numerator_binned_LeptonPlusJet_woTrigger,
	      numerator_and_denominatorHistManagers * histograms_e_denominator_incl_LeptonPlusJet_woTrigger,
	      std::vector<numerator_and_denominatorHistManagers *> histograms_e_denominator_binned_LeptonPlusJet_woTrigger,
	      numerator_and_denominatorHistManagers * histograms_mu_numerator_incl_LeptonPlusJet_woTrigger,
	      std::vector<numerator_and_denominatorHistManagers *> histograms_mu_numerator_binned_LeptonPlusJet_woTrigger,
	      numerator_and_denominatorHistManagers * histograms_mu_denominator_incl_LeptonPlusJet_woTrigger,
	      std::vector<numerator_and_denominatorHistManagers *> histograms_mu_denominator_binned_LeptonPlusJet_woTrigger,
	      EvtWeightRecorder evtWeightRecorder_copy,
	      const std::string central_or_shift,
	      EventInfo eventInfo,
	      std::vector<hltPath_LeptonFakeRate *> triggers_mu,
	      std::vector<hltPath_LeptonFakeRate *> triggers_e,
	      const double minConePt_global_e,
	      const double minRecoPt_global_e,
	      const double minConePt_global_mu,
	      const double minRecoPt_global_mu,
	      const bool use_triggers_1e,
	      const bool use_triggers_2e,
	      const bool use_triggers_1mu,
	      const bool use_triggers_2mu,
	      const bool isMC,
	      const bool apply_DYMCNormScaleFactors,
	      //const bool apply_DYMCReweighting,
	      std::vector<GenParticle> genTauLeptons,
	      DYMCNormScaleFactors * dyNormScaleFactors = 0,
	      BtagSFRatioFacility * btagSFRatioFacility = 0,
	      NtupleFillerBDT<float, int>* bdt_filler_e_LeptonPlusJet = 0,
	      NtupleFillerBDT<float, int>* bdt_filler_mu_LeptonPlusJet = 0,
	      bool isDEBUG = false,
	      cutFlowTableType* cutFlowTable_e = 0,
	      cutFlowTableType* cutFlowTable_mu = 0,
	      cutFlowTableType* cutFlowTable_e_woTrigger = 0,
	      cutFlowTableType* cutFlowTable_mu_woTrigger = 0)

{
  bool passMETFilter = false;
  passMETFilter = METFilterDecision(isMC, apply_met_filters,
				      metFilter, cfgMEtFilter);


  // Original Event weight (w/o Trigger prescale/BTagSF/DY Corr.s/METFilters) defined below
  double evtWeight_wo_TrigPrescale_BTag_DY_SFs = evtWeightRecorder_copy.get(central_or_shift);
  
  RecoJetCollectionCleaner jetCleaner_dR07(0.7, isDEBUG); 
  const Era era = get_era(era_string);
  RecoJetCollectionSelector jetSelector(era);
  RecoJetCollectionSelectorBtagLoose jetSelectorBtagLoose(era);
  RecoJetCollectionSelectorBtagMedium jetSelectorBtagMedium(era);
  std::vector<const RecoJet *> cleanedJets;
  std::vector<const RecoJet *> selJets;
  //std::vector<const RecoJet*> selBJets_loose;
  //std::vector<const RecoJet*> selBJets_medium;
  double prescale_weight = 1.0;
  bool passTrigger = false;

  if(preselLeptonsFull.size() == 1)
    { // 1 Loose/Presel Leptons cond.
      if(preselLeptonsFull[0]->is_electron())
	{// electron block
	  cutFlowTable_e->update("= 1 presel/Loose electron", evtWeight_wo_TrigPrescale_BTag_DY_SFs);
	  cutFlowTable_e_woTrigger->update("= 1 presel/Loose electron", evtWeight_wo_TrigPrescale_BTag_DY_SFs);
	  const RecoElectron* preselElectron_ptr  = dynamic_cast<const RecoElectron*>(preselLeptonsFull[0]);
	  const std::vector<const RecoElectron *> tmp_leptons = { preselElectron_ptr };
	  cleanedJets = jetCleaner_dR07(jet_ptrs, tmp_leptons);
	  selJets = jetSelector(cleanedJets);
	  //selBJets_loose = jetSelectorBtagLoose(cleanedJets);
	  //selBJets_medium = jetSelectorBtagMedium(cleanedJets);

	  int jetindex  = -1;
	  for(unsigned int i = 0; i < selJets.size(); i++)
	    {// loop over jets
	      if(deltaR(preselLeptonsFull[0]->p4(), selJets[i]->p4()) <= 0.7)
		{
		  continue;
		}else{
		jetindex = i;   
		break; 
	      }
	    }// loop over jets ends

	      if(jetindex != -1){// Jet is found
		//std::cout<<" Jet is found dR=0.7 away from electron "<<std::endl;
		cutFlowTable_e->update("Jet found at a dist. dR=0.7 from electron", evtWeight_wo_TrigPrescale_BTag_DY_SFs);
		cutFlowTable_e_woTrigger->update("Jet found at a dist. dR=0.7 from electron", evtWeight_wo_TrigPrescale_BTag_DY_SFs);
		// Fill the electron histograms
		const RecoLepton & preselElectron = *(preselLeptonsFull[0]);
		const RecoMEt met_mod = METSystComp_LeptonFakeRate(preselLeptonsFull[0], genmet, met, METScaleSyst, metSyst_option, isDEBUG);
		const double mT     = comp_mT(preselElectron, met_mod.pt(), met_mod.phi());
		const double mT_fix = comp_mT_fix(preselElectron, met_mod.pt(), met_mod.phi());

		std::vector<const RecoLepton*> probe_lepton_vec = { preselLeptonsFull[0] };
		JetAndTrigPrescaleCollector* JetAndTrigPrescaleCollector_ptr = 0;
		JetAndTrigPrescaleCollector_ptr = PrescaleAndJetExtractor(probe_lepton_vec,
									  jet_ptrs,
									  triggers_mu,
									  triggers_e,
									  era_string,
									  minConePt_global_e,
									  minRecoPt_global_e,
									  minConePt_global_mu,
									  minRecoPt_global_mu,
									  use_triggers_1e,
									  use_triggers_2e,
									  use_triggers_1mu,
									  use_triggers_2mu,
									  isMC,
									  isDEBUG);

		if(JetAndTrigPrescaleCollector_ptr)
		  { // All Trigger cond.s applied
		    ApplyBTagSF2(selJets,
				 evtWeightRecorder_copy,
				 isMC,
				 btagSFRatioFacility);
		    ApplyDYNormSF2(JetAndTrigPrescaleCollector_ptr,
				   evtWeightRecorder_copy,
				   isMC,
				   apply_DYMCNormScaleFactors,
				   dyNormScaleFactors,
				   genTauLeptons);
		    prescale_weight = JetAndTrigPrescaleCollector_ptr->Get_prescaleWeight();
		    passTrigger = JetAndTrigPrescaleCollector_ptr->Get_TrigDecision();
		    //std::cout<< "LeptonPlusJet():: prescale_weight " << prescale_weight << std::endl;
		    //std::cout<< "LeptonPlusJet():: passTrigger " << passTrigger << std::endl;
		  }
		double evtWeight_wo_TrigPrescale = 1.0; // Electron Event weight (w/o Trigger prescale, BTag, DY SFs, Data/MC corr.s) defined here
		double evtWeight = 1.0;
		int passesMETandTrigger = (passMETFilter && passTrigger) ? 1 : 0;

		if(passMETFilter)
		  {
		    // ---- Apply Data-to-mc Corrections
		    ApplyDataToMCCorrection(preselLeptonsFull[0], dataToMCcorrectionInterface_ntuple, evtWeightRecorder_copy);
		    evtWeight_wo_TrigPrescale = evtWeightRecorder_copy.get(central_or_shift);
		    cutFlowTable_e_woTrigger->update("Event passes MET filters", evtWeight_wo_TrigPrescale);
		  }

		if(passesMETandTrigger)
		  {
		    evtWeightRecorder_copy.record_prescale(prescale_weight); //Applying prescale weight 
		    evtWeight = evtWeightRecorder_copy.get(central_or_shift); // Electron Event weight (w Trigger prescale and Data/MC corr.) defined here  
		    //std::cout<< "LeptonPlusJet():: (after corr.): evtWeightRecorder_copy: "<< evtWeightRecorder_copy << std::endl;		      
		    cutFlowTable_e->update("Event passes trigger and MET filters", evtWeight);
		  }

		  // Fill Ntuples for electron
		  FillNtuples(preselLeptonsFull[0], eventInfo, evtWeight, evtWeight_wo_TrigPrescale,  mT, mT_fix, passesMETandTrigger, bdt_filler_e_LeptonPlusJet);
		
		  // numerator histograms
		  numerator_and_denominatorHistManagers * histograms_incl_num = nullptr;
		  std::vector<numerator_and_denominatorHistManagers *> * histograms_binned_num = nullptr;
		  numerator_and_denominatorHistManagers * histograms_incl_num_woTrigger = nullptr;
		  std::vector<numerator_and_denominatorHistManagers *> * histograms_binned_num_woTrigger = nullptr;

		  // denominator histograms
		  numerator_and_denominatorHistManagers * histograms_incl_den = nullptr;
		  std::vector<numerator_and_denominatorHistManagers *> * histograms_binned_den = nullptr;
		  numerator_and_denominatorHistManagers * histograms_incl_den_woTrigger = nullptr;
		  std::vector<numerator_and_denominatorHistManagers *> * histograms_binned_den_woTrigger = nullptr;
		  
		  if(preselElectron.isTight())
		    {// numerator e histograms filled
		      if(passMETFilter){ // Passes MET Filters (no Trigger cond. applied)
			histograms_incl_num_woTrigger = histograms_e_numerator_incl_LeptonPlusJet_woTrigger;
			histograms_binned_num_woTrigger = &histograms_e_numerator_binned_LeptonPlusJet_woTrigger;
			if(histograms_incl_num_woTrigger != nullptr && histograms_binned_num_woTrigger != nullptr)
			  {
			    histograms_incl_num_woTrigger->fillHistograms(preselElectron, met.pt(), mT, mT_fix, evtWeight_wo_TrigPrescale); //(w/o trigger) 
			    fillHistograms(*histograms_binned_num_woTrigger, preselElectron, met.pt(), mT, mT_fix, evtWeight_wo_TrigPrescale, cutFlowTable_e_woTrigger); //(w/o trigger) 
			  }
		      }
 
		      if(passesMETandTrigger){ // Passes MET Filters (Trigger cond. applied)
			histograms_incl_num = histograms_e_numerator_incl_LeptonPlusJet;
			histograms_binned_num = &histograms_e_numerator_binned_LeptonPlusJet;
			if(histograms_incl_num != nullptr && histograms_binned_num != nullptr)
			  {
			    histograms_incl_num->fillHistograms(preselElectron, met.pt(), mT, mT_fix, evtWeight); //(w Trigger)
			    fillHistograms(*histograms_binned_num, preselElectron, met.pt(), mT, mT_fix, evtWeight, cutFlowTable_e); //(w Trigger) 
			  }
		      }

		    }

		  //if(preselElectron.isFakeable()) // CERN group logic
		  if(preselElectron.isFakeable() && !preselElectron.isTight()) // Tallinn Group logic
		    {// denominator e histograms filled
		      if(passMETFilter)
			{ // Passes MET Filters (no Trigger cond. applied)
			  histograms_incl_den_woTrigger = histograms_e_denominator_incl_LeptonPlusJet_woTrigger;
			  histograms_binned_den_woTrigger = &histograms_e_denominator_binned_LeptonPlusJet_woTrigger;
			  if(histograms_incl_den_woTrigger != nullptr && histograms_binned_den_woTrigger != nullptr)
			    {
			      histograms_incl_den_woTrigger->fillHistograms(preselElectron, met.pt(), mT, mT_fix, evtWeight_wo_TrigPrescale); //(w/o trigger) 
			      fillHistograms(*histograms_binned_den_woTrigger, preselElectron, met.pt(), mT, mT_fix, evtWeight_wo_TrigPrescale, cutFlowTable_e_woTrigger); //(w/o trigger) 
			    }
			}
		      if(passesMETandTrigger)
			{ // Passes MET Filters (Trigger cond. applied)
			  histograms_incl_den = histograms_e_denominator_incl_LeptonPlusJet;
			  histograms_binned_den = &histograms_e_denominator_binned_LeptonPlusJet;
			  if(histograms_incl_den != nullptr && histograms_binned_den != nullptr)
			    {
			      histograms_incl_den->fillHistograms(preselElectron, met.pt(), mT, mT_fix, evtWeight); //(w trigger) 
			      fillHistograms(*histograms_binned_den, preselElectron, met.pt(), mT, mT_fix, evtWeight, cutFlowTable_e); //(w trigger) 
			    }
			}
		    }

		  if (printLevel==1 && passesMETandTrigger) {
		    std::cout << "LeptonPlusJet():: FR LeptonPlusJet() electron:: " << evtWeightRecorder_copy << "\nevtWt: " << evtWeightRecorder_copy.get(central_or_shift)<< '\n';
		  }
		  return 2; 
	      }else{ // no jet is found dR=0.7 away from electron
		return 3;
	      } 
	}// electron block ends

      if(preselLeptonsFull[0]->is_muon())
	{// muon block
	  cutFlowTable_mu->update("= 1 presel/Loose muon", evtWeight_wo_TrigPrescale_BTag_DY_SFs);
	  cutFlowTable_mu_woTrigger->update("= 1 presel/Loose muon", evtWeight_wo_TrigPrescale_BTag_DY_SFs);
	  const RecoMuon* preselMuon_ptr  = dynamic_cast<const RecoMuon*>(preselLeptonsFull[0]);
	  const std::vector<const RecoMuon *> tmp_leptons = { preselMuon_ptr };
	  cleanedJets = jetCleaner_dR07(jet_ptrs, tmp_leptons);
	  selJets = jetSelector(cleanedJets);
	  //selBJets_loose = jetSelectorBtagLoose(cleanedJets);
	  //selBJets_medium = jetSelectorBtagMedium(cleanedJets);


	  int jetindex  = -1;
	  for(unsigned int i = 0; i < selJets.size(); i++)
	    {// loop over jets
	      if(deltaR(preselLeptonsFull[0]->p4(), selJets[i]->p4()) <= 0.7)
		{
		  continue;
		}else{
		jetindex = i;   
		break; 
	      }
	    }// loop over jets ends

	      if(jetindex != -1){// Jet is found
		//std::cout<<" Jet is found dR=0.7 away from muon "<<std::endl;
		cutFlowTable_mu->update("Jet found at a dist. dR=0.7 from muon", evtWeight_wo_TrigPrescale_BTag_DY_SFs);
		cutFlowTable_mu_woTrigger->update("Jet found at a dist. dR=0.7 from muon", evtWeight_wo_TrigPrescale_BTag_DY_SFs);
		const RecoLepton & preselMuon = *(preselLeptonsFull[0]);
		const RecoMEt met_mod = METSystComp_LeptonFakeRate(preselLeptonsFull[0], genmet, met, METScaleSyst, metSyst_option, isDEBUG);
		const double mT     = comp_mT(preselMuon, met_mod.pt(), met_mod.phi());
		const double mT_fix = comp_mT_fix(preselMuon, met_mod.pt(), met_mod.phi());

		std::vector<const RecoLepton*> probe_lepton_vec = { preselLeptonsFull[0] };
		JetAndTrigPrescaleCollector* JetAndTrigPrescaleCollector_ptr = 0;
		JetAndTrigPrescaleCollector_ptr = PrescaleAndJetExtractor(probe_lepton_vec, 
									  jet_ptrs,
									  triggers_mu,
									  triggers_e,
									  era_string,
									  minConePt_global_e,
									  minRecoPt_global_e,
									  minConePt_global_mu,
									  minRecoPt_global_mu,
									  use_triggers_1e,
									  use_triggers_2e,
									  use_triggers_1mu,
									  use_triggers_2mu,
									  isMC,
									  isDEBUG);
		
		if(JetAndTrigPrescaleCollector_ptr)
		  {// All Trigger cond.s applied
		    ApplyBTagSF2(selJets,
				 evtWeightRecorder_copy,
				 isMC,
				 btagSFRatioFacility);
		    ApplyDYNormSF2(JetAndTrigPrescaleCollector_ptr,
				   evtWeightRecorder_copy,
				   isMC,
				   apply_DYMCNormScaleFactors,
				   dyNormScaleFactors,
				   genTauLeptons);
		    prescale_weight = JetAndTrigPrescaleCollector_ptr->Get_prescaleWeight();
		    passTrigger = JetAndTrigPrescaleCollector_ptr->Get_TrigDecision();
		    //std::cout<< "LeptonPlusJet():: prescale_weight " << prescale_weight << std::endl;
		    //std::cout<< "LeptonPlusJet():: passTrigger " << passTrigger << std::endl;
		  }
		double evtWeight_wo_TrigPrescale = 1.0; // Muon Event weight (w/o Trigger prescale and Data/MC corr.) defined here
		double evtWeight = 1.0;
		int passesMETandTrigger = (passMETFilter && passTrigger) ? 1 : 0;

		if(passMETFilter)
		  {
		    // ---- Apply Data-to-mc Corrections
		    ApplyDataToMCCorrection(preselLeptonsFull[0], dataToMCcorrectionInterface_ntuple, evtWeightRecorder_copy);
		    evtWeight_wo_TrigPrescale = evtWeightRecorder_copy.get(central_or_shift);
		    cutFlowTable_mu_woTrigger->update("Event passes MET filters", evtWeight_wo_TrigPrescale);
		  }


		if(passesMETandTrigger)
		{

		  evtWeightRecorder_copy.record_prescale(prescale_weight); //Applying prescale weight
		  evtWeight = evtWeightRecorder_copy.get(central_or_shift); // Muon Event weight (w Trigger prescale and Data/MC corr.) defined here  
		  //std::cout<< "LeptonPlusJet():: (after corr.): evtWeightRecorder_copy: "<< evtWeightRecorder_copy << std::endl;		      
		  cutFlowTable_mu->update("Event passes trigger and MET filters", evtWeight);
		}

		// Fill Ntuples for muon
		FillNtuples(preselLeptonsFull[0], eventInfo, evtWeight, evtWeight_wo_TrigPrescale, mT, mT_fix, passesMETandTrigger, bdt_filler_mu_LeptonPlusJet);
	
		// numerator histograms
		numerator_and_denominatorHistManagers * histograms_incl_num = nullptr;
		std::vector<numerator_and_denominatorHistManagers *> * histograms_binned_num = nullptr;
		numerator_and_denominatorHistManagers * histograms_incl_num_woTrigger = nullptr;
		std::vector<numerator_and_denominatorHistManagers *> * histograms_binned_num_woTrigger = nullptr;
		// denominator histograms
		numerator_and_denominatorHistManagers * histograms_incl_den = nullptr;
		std::vector<numerator_and_denominatorHistManagers *> * histograms_binned_den = nullptr;
		numerator_and_denominatorHistManagers * histograms_incl_den_woTrigger = nullptr;
		std::vector<numerator_and_denominatorHistManagers *> * histograms_binned_den_woTrigger = nullptr;
		
		if(preselMuon.isTight())
		  {// numerator mu histograms filled

		    if(passMETFilter)
		      {// Passes MET Filters (no Trigger cond. applied) 
			histograms_incl_num_woTrigger = histograms_mu_numerator_incl_LeptonPlusJet_woTrigger;
			histograms_binned_num_woTrigger = &histograms_mu_numerator_binned_LeptonPlusJet_woTrigger;
			if(histograms_incl_num_woTrigger != nullptr && histograms_binned_num_woTrigger != nullptr)
			  {
			    histograms_incl_num_woTrigger->fillHistograms(preselMuon, met.pt(), mT, mT_fix, evtWeight_wo_TrigPrescale); //(w/o trigger) 
			    fillHistograms(*histograms_binned_num_woTrigger, preselMuon, met.pt(), mT, mT_fix, evtWeight_wo_TrigPrescale, cutFlowTable_mu_woTrigger); //(w/o trigger) 
			  }
		      }
		    if(passesMETandTrigger)
		      {// Passes MET Filters (Trigger cond. applied) 
			histograms_incl_num = histograms_mu_numerator_incl_LeptonPlusJet;
			histograms_binned_num = &histograms_mu_numerator_binned_LeptonPlusJet;
			if(histograms_incl_num != nullptr && histograms_binned_num != nullptr)
			  {
			    histograms_incl_num->fillHistograms(preselMuon, met.pt(), mT, mT_fix, evtWeight); //(w Trigger) 
			    fillHistograms(*histograms_binned_num, preselMuon, met.pt(), mT, mT_fix, evtWeight, cutFlowTable_mu); //(w Trigger)  
			  }
		      }
		  }
		
		//if(preselMuon.isFakeable()) // CERN group logic
		if(preselMuon.isFakeable() && !preselMuon.isTight()) // Tallinn Group logic
		  {// denominator mu histograms filled
		    if(passMETFilter)
                      {// Passes MET Filters (no Trigger cond. applied)  
			histograms_incl_den_woTrigger = histograms_mu_denominator_incl_LeptonPlusJet_woTrigger;
			histograms_binned_den_woTrigger = &histograms_mu_denominator_binned_LeptonPlusJet_woTrigger;
			if(histograms_incl_den_woTrigger != nullptr && histograms_binned_den_woTrigger != nullptr)
			  {
			    histograms_incl_den_woTrigger->fillHistograms(preselMuon, met.pt(), mT, mT_fix, evtWeight_wo_TrigPrescale); //(w/o trigger) 
			    fillHistograms(*histograms_binned_den_woTrigger, preselMuon, met.pt(), mT, mT_fix, evtWeight_wo_TrigPrescale, cutFlowTable_mu_woTrigger); //(w/o trigger) 
			  }
		      }
		    if(passesMETandTrigger)
		      { // Passes MET Filters (Trigger cond. applied)  
			histograms_incl_den = histograms_mu_denominator_incl_LeptonPlusJet;
			histograms_binned_den = &histograms_mu_denominator_binned_LeptonPlusJet;
			if(histograms_incl_den != nullptr && histograms_binned_den != nullptr)
			  {
			    histograms_incl_den->fillHistograms(preselMuon, met.pt(), mT, mT_fix, evtWeight); //(w Trigger)
			    fillHistograms(*histograms_binned_den, preselMuon, met.pt(), mT, mT_fix, evtWeight, cutFlowTable_mu); //(w Trigger)
			  }
		      }
		  }

		if (printLevel==1 && passesMETandTrigger) {
		  std::cout << "LeptonPlusJet():: FR LeptonPlusJet() muon:: " << evtWeightRecorder_copy << "\nevtWt: " << evtWeightRecorder_copy.get(central_or_shift) << '\n';
		}		
		return 4; 
	      }else{// no jet is found dR=0.7 away from muon
		return 5; 
	      }
	}// muon block ends
    }else{// 1 Loose/Presel Leptons cond. not satisfied
    return 1;
  }
  return 0;
}

  

int 
DiLeptonSS(Data_to_MC_CorrectionInterface_Base * dataToMCcorrectionInterface_ntuple,
	   std::vector<const RecoLepton*> preselLeptonsFull,
	   std::vector<const RecoJet*> jet_ptrs,
	   const std::string era_string,
	   const bool apply_met_filters,
	   MEtFilter metFilter,
	   const edm::ParameterSet cfgMEtFilter,
	   const GenMEt genmet, 
	   const RecoMEt met, 
	   const double METScaleSyst, 
	   const METSyst metSyst_option,
	   numerator_and_denominatorHistManagers * histograms_e_numerator_incl_diLeptSS,
	   std::vector<numerator_and_denominatorHistManagers *> histograms_e_numerator_binned_diLeptSS,
	   numerator_and_denominatorHistManagers * histograms_e_denominator_incl_diLeptSS,
	   std::vector<numerator_and_denominatorHistManagers *> histograms_e_denominator_binned_diLeptSS,
	   numerator_and_denominatorHistManagers * histograms_mu_numerator_incl_diLeptSS,
	   std::vector<numerator_and_denominatorHistManagers *> histograms_mu_numerator_binned_diLeptSS,
	   numerator_and_denominatorHistManagers * histograms_mu_denominator_incl_diLeptSS,
	   std::vector<numerator_and_denominatorHistManagers *> histograms_mu_denominator_binned_diLeptSS,
	   numerator_and_denominatorHistManagers * histograms_e_numerator_incl_diLeptSS_woTrigger,
	   std::vector<numerator_and_denominatorHistManagers *> histograms_e_numerator_binned_diLeptSS_woTrigger,
	   numerator_and_denominatorHistManagers * histograms_e_denominator_incl_diLeptSS_woTrigger,
	   std::vector<numerator_and_denominatorHistManagers *> histograms_e_denominator_binned_diLeptSS_woTrigger,
	   numerator_and_denominatorHistManagers * histograms_mu_numerator_incl_diLeptSS_woTrigger,
	   std::vector<numerator_and_denominatorHistManagers *> histograms_mu_numerator_binned_diLeptSS_woTrigger,
	   numerator_and_denominatorHistManagers * histograms_mu_denominator_incl_diLeptSS_woTrigger,
	   std::vector<numerator_and_denominatorHistManagers *> histograms_mu_denominator_binned_diLeptSS_woTrigger,
	   EvtWeightRecorder evtWeightRecorder_copy,
	   const std::string central_or_shift,
	   EventInfo eventInfo,
	   std::vector<hltPath_LeptonFakeRate *> triggers_mu,
	   std::vector<hltPath_LeptonFakeRate *> triggers_e,
	   const double minConePt_global_e,
	   const double minRecoPt_global_e,
	   const double minConePt_global_mu,
	   const double minRecoPt_global_mu,
	   const bool use_triggers_1e,
	   const bool use_triggers_2e,
	   const bool use_triggers_1mu,
	   const bool use_triggers_2mu,
	   const bool isMC,
	   const bool apply_DYMCNormScaleFactors,
	   //const bool apply_DYMCReweighting,
	   std::vector<GenParticle> genTauLeptons,
	   DYMCNormScaleFactors* dyNormScaleFactors = 0,
	   BtagSFRatioFacility* btagSFRatioFacility = 0,
	   NtupleFillerBDT<float, int>* bdt_filler_e_diLeptSS = 0,
	   NtupleFillerBDT<float, int>* bdt_filler_mu_diLeptSS = 0,
	   bool isDEBUG = false,
	   cutFlowTableType* cutFlowTable_e = 0,
	   cutFlowTableType* cutFlowTable_mu = 0,
	   cutFlowTableType* cutFlowTable_e_woTrigger = 0,
	   cutFlowTableType* cutFlowTable_mu_woTrigger = 0)
	   
{ 
  bool passMETFilter = false;
  passMETFilter = METFilterDecision(isMC, apply_met_filters,
				      metFilter, cfgMEtFilter);
  // Original Event weight (w/o Trigger prescale/BTagSF/DY Corr.s/METFilters) defined below
  double evtWeight_wo_TrigPrescale_BTag_DY_SFs = evtWeightRecorder_copy.get(central_or_shift); 

  RecoJetCollectionCleaner jetCleaner_dR07(0.7, isDEBUG); 
  const Era era = get_era(era_string);
  RecoJetCollectionSelector jetSelector(era);
  RecoJetCollectionSelectorBtagLoose jetSelectorBtagLoose(era);
  RecoJetCollectionSelectorBtagMedium jetSelectorBtagMedium(era);
  std::vector<const RecoJet *> cleanedJets;
  std::vector<const RecoJet *> selJets;
  //std::vector<const RecoJet*> selBJets_loose;
  //std::vector<const RecoJet*> selBJets_medium;
  double prescale_weight = 1.0;
  bool passTrigger = false;


  int TagLeptonIndex = -1;
  int ProbeLeptonIndex = -1;
  bool TagLeptonExists = false;
  bool ProbeLeptonExists = false;
  if(preselLeptonsFull.size() == 2)
    { // 2 Loose/Presel Leptons cond.

      cutFlowTable_e->update("= 2 presel/Loose leptons", evtWeight_wo_TrigPrescale_BTag_DY_SFs);
      cutFlowTable_mu->update("= 2 presel/Loose leptons", evtWeight_wo_TrigPrescale_BTag_DY_SFs);
      cutFlowTable_e_woTrigger->update("= 2 presel/Loose leptons", evtWeight_wo_TrigPrescale_BTag_DY_SFs);
      cutFlowTable_mu_woTrigger->update("= 2 presel/Loose leptons", evtWeight_wo_TrigPrescale_BTag_DY_SFs);

      for(unsigned int i = 0; i < preselLeptonsFull.size(); i++)
	{ // loop over preselleptons
	  if( (preselLeptonsFull[i]->genLepton()) && (preselLeptonsFull[i]->isTight()) )
	    {
	      cutFlowTable_e->update("Gen-matched lepton (Tag) exists", evtWeight_wo_TrigPrescale_BTag_DY_SFs);
	      cutFlowTable_mu->update("Gen-matched lepton (Tag) exists", evtWeight_wo_TrigPrescale_BTag_DY_SFs);
	      cutFlowTable_e_woTrigger->update("Gen-matched lepton (Tag) exists", evtWeight_wo_TrigPrescale_BTag_DY_SFs);
	      cutFlowTable_mu_woTrigger->update("Gen-matched lepton (Tag) exists", evtWeight_wo_TrigPrescale_BTag_DY_SFs);
	      //std::cout << "Tag found " << std::endl;
	      TagLeptonExists = true;
	      TagLeptonIndex = i;
	    }
	  if((preselLeptonsFull[i]->is_electron()) 
	     && !((preselLeptonsFull[i]->genLepton())
		  || (preselLeptonsFull[i]->genHadTau())
		  || (preselLeptonsFull[i]->genPhoton())))
	    {
	      //std::cout << "Probe found and it is an electron " << std::endl;
	      ProbeLeptonExists = true;
	      ProbeLeptonIndex = i;
	    }
	  if((preselLeptonsFull[i]->is_muon()) 
	     && !((preselLeptonsFull[i]->genLepton())
		  || (preselLeptonsFull[i]->genHadTau())) )
	    {
	      //std::cout << "Probe found and it is a muon " << std::endl;
	      ProbeLeptonExists = true;
	      ProbeLeptonIndex = i;
	    }
	} // loop over preselleptons ends

      if(TagLeptonExists && ProbeLeptonExists)
	{// Both Tag and probe exists
	  if((preselLeptonsFull[TagLeptonIndex]->charge()*preselLeptonsFull[ProbeLeptonIndex]->charge()) > 0)
	    {// Same Sign cond.
	      //std::cout<< "Both presel/Loose leptons are Same Sign" << std::endl;
	      cutFlowTable_e->update("Both presel/Loose leptons are Same Sign", evtWeight_wo_TrigPrescale_BTag_DY_SFs);
	      cutFlowTable_mu->update("Both presel/Loose leptons are Same Sign", evtWeight_wo_TrigPrescale_BTag_DY_SFs);
	      cutFlowTable_e_woTrigger->update("Both presel/Loose leptons are Same Sign", evtWeight_wo_TrigPrescale_BTag_DY_SFs);
	      cutFlowTable_mu_woTrigger->update("Both presel/Loose leptons are Same Sign", evtWeight_wo_TrigPrescale_BTag_DY_SFs);
	      cleanedJets = jetCleaner_dR07(jet_ptrs, preselLeptonsFull); // Cleaning w.r.t both Tag and Probe leptons 
	      selJets = jetSelector(cleanedJets);
	      //selBJets_loose = jetSelectorBtagLoose(cleanedJets);
	      //selBJets_medium = jetSelectorBtagMedium(cleanedJets);
	      JetAndTrigPrescaleCollector* JetAndTrigPrescaleCollector_ptr = 0;
	      JetAndTrigPrescaleCollector_ptr = PrescaleAndJetExtractor(preselLeptonsFull, // Demanding trigger either Tag or probe
									jet_ptrs,
									triggers_mu,
									triggers_e,
									era_string,
									minConePt_global_e,
									minRecoPt_global_e,
									minConePt_global_mu,
									minRecoPt_global_mu,
									use_triggers_1e,
									use_triggers_2e,
									use_triggers_1mu,
									use_triggers_2mu,
									isMC,
									isDEBUG);

	      if(JetAndTrigPrescaleCollector_ptr)
		{	
		  ApplyBTagSF2(selJets,
			       evtWeightRecorder_copy,
			       isMC,
			       btagSFRatioFacility);
		  ApplyDYNormSF2(JetAndTrigPrescaleCollector_ptr,
				 evtWeightRecorder_copy,
				 isMC,
				 apply_DYMCNormScaleFactors,
				 dyNormScaleFactors,
				 genTauLeptons);
		  prescale_weight = JetAndTrigPrescaleCollector_ptr->Get_prescaleWeight();
		  passTrigger = JetAndTrigPrescaleCollector_ptr->Get_TrigDecision();
		  std::cout<< "DiLeptonSS()::prescale_weight " << prescale_weight << std::endl;
		  std::cout<< "DiLeptonSS()::passTrigger " << passTrigger << std::endl;
		}
	      	
	      double evtWeight_wo_TrigPrescale = 1.0; // Event weight (w/o Trigger prescale and Data/MC corr.) defined here
	      double evtWeight = 1.0;
	      int passesMETandTrigger = (passMETFilter && passTrigger) ? 1 : 0;
	      
	      if(passMETFilter)
		{
		  // ---- Apply Data-to-mc Corrections
		  ApplyDataToMCCorrection(preselLeptonsFull[ProbeLeptonIndex], dataToMCcorrectionInterface_ntuple, evtWeightRecorder_copy);
		  evtWeight_wo_TrigPrescale = evtWeightRecorder_copy.get(central_or_shift);
		  cutFlowTable_e_woTrigger->update ("Event passes MET filters", evtWeight_wo_TrigPrescale);
		  cutFlowTable_mu_woTrigger->update ("Event passes MET filters", evtWeight_wo_TrigPrescale);
		}
	      
	      if(passesMETandTrigger)
		{

		  evtWeightRecorder_copy.record_prescale(prescale_weight); //Applying prescale weight
		  evtWeight = evtWeightRecorder_copy.get(central_or_shift); // Event weight (w Trigger prescale and Data/MC corr.) defined here
		  //std::cout<< "DiLeptonSS():: (after corr.): evtWeightRecorder_copy: "<< evtWeightRecorder_copy << std::endl;
		  cutFlowTable_e->update ("Event passes trigger and MET filters", evtWeight);
		  cutFlowTable_mu->update ("Event passes trigger and MET filters", evtWeight);
		}
	
	      //electron block
    	      if(preselLeptonsFull[ProbeLeptonIndex]->is_electron())
    		{ // Fill electron histograms
		  cutFlowTable_e->update("Probe lepton exists and is an electron", evtWeight);
		  cutFlowTable_e_woTrigger->update("Probe lepton exists and is an electron", evtWeight_wo_TrigPrescale);

		  const RecoLepton & preselElectron = *(preselLeptonsFull[ProbeLeptonIndex]);
		  const RecoMEt met_mod = METSystComp_LeptonFakeRate(preselLeptonsFull[ProbeLeptonIndex], genmet, met, METScaleSyst, metSyst_option, isDEBUG);
		  const double mT     = comp_mT(preselElectron, met_mod.pt(), met_mod.phi());
		  const double mT_fix = comp_mT_fix(preselElectron, met_mod.pt(), met_mod.phi());

		  // Fill Ntuples for electron
		  FillNtuples(preselLeptonsFull[ProbeLeptonIndex], eventInfo, evtWeight, evtWeight_wo_TrigPrescale, mT, mT_fix, passesMETandTrigger, bdt_filler_e_diLeptSS);

		  // numerator histograms
    		  numerator_and_denominatorHistManagers * histograms_incl_num = nullptr;
    		  std::vector<numerator_and_denominatorHistManagers *> * histograms_binned_num = nullptr;
    		  numerator_and_denominatorHistManagers * histograms_incl_num_woTrigger = nullptr;
    		  std::vector<numerator_and_denominatorHistManagers *> * histograms_binned_num_woTrigger = nullptr;
		  // denominator histograms
    		  numerator_and_denominatorHistManagers * histograms_incl_den = nullptr;
    		  std::vector<numerator_and_denominatorHistManagers *> * histograms_binned_den = nullptr;
    		  numerator_and_denominatorHistManagers * histograms_incl_den_woTrigger = nullptr;
    		  std::vector<numerator_and_denominatorHistManagers *> * histograms_binned_den_woTrigger = nullptr;
		  if(preselElectron.isTight())
    		    {// numerator e histograms filled
		      if(passMETFilter)
			{// Passes MET Filter (w/o Trigger cond.)
			  histograms_incl_num_woTrigger = histograms_e_numerator_incl_diLeptSS_woTrigger;
			  histograms_binned_num_woTrigger = &histograms_e_numerator_binned_diLeptSS_woTrigger;
			  if(histograms_incl_num_woTrigger != nullptr && histograms_binned_num_woTrigger != nullptr)
			    {
			      histograms_incl_num_woTrigger->fillHistograms(preselElectron, met.pt(), mT, mT_fix, evtWeight_wo_TrigPrescale); //(w/o Trigger)
			      fillHistograms(*histograms_binned_num_woTrigger, preselElectron, met.pt(), mT, mT_fix, evtWeight_wo_TrigPrescale, cutFlowTable_e_woTrigger); //(w/o Trigger) 			    
			    }
			}
		      if(passesMETandTrigger)
			{// Passes MET Filter (w Trigger cond.)
			  histograms_incl_num = histograms_e_numerator_incl_diLeptSS;
			  histograms_binned_num = &histograms_e_numerator_binned_diLeptSS;
			  if(histograms_incl_num != nullptr && histograms_binned_num != nullptr)
			    {
			      histograms_incl_num->fillHistograms(preselElectron, met.pt(), mT, mT_fix, evtWeight); //(w Trigger)
			      fillHistograms(*histograms_binned_num, preselElectron, met.pt(), mT, mT_fix, evtWeight, cutFlowTable_e); //(w Trigger) 
			    }
			}
		    }

		  //if(preselElectron.isFakeable()) // CERN group logic
		  if(preselElectron.isFakeable() && !preselElectron.isTight()) // Tallinn Group logic
    		    {// denominator e histograms filled
		      if(passMETFilter)
			{// Passes MET Filter (w/o Trigger cond.)
			  histograms_incl_den_woTrigger = histograms_e_denominator_incl_diLeptSS_woTrigger;
			  histograms_binned_den_woTrigger = &histograms_e_denominator_binned_diLeptSS_woTrigger;
			  if(histograms_incl_den_woTrigger != nullptr && histograms_binned_den_woTrigger != nullptr)
			    {
			      histograms_incl_den_woTrigger->fillHistograms(preselElectron, met.pt(), mT, mT_fix, evtWeight_wo_TrigPrescale); //(w/o Trigger)
			      fillHistograms(*histograms_binned_den_woTrigger, preselElectron, met.pt(), mT, mT_fix, evtWeight_wo_TrigPrescale, cutFlowTable_e_woTrigger); //(w/o Trigger) 			    
			    }
			}
		      if(passesMETandTrigger)
			{// Passes MET Filter (w Trigger cond.)
			  histograms_incl_den = histograms_e_denominator_incl_diLeptSS;
			  histograms_binned_den = &histograms_e_denominator_binned_diLeptSS;
			  if(histograms_incl_den != nullptr && histograms_binned_den != nullptr)
			    {
			      histograms_incl_den->fillHistograms(preselElectron, met.pt(), mT, mT_fix, evtWeight); //(w Trigger)
			      fillHistograms(*histograms_binned_den, preselElectron, met.pt(), mT, mT_fix, evtWeight, cutFlowTable_e); //(w Trigger)
			    }
			}
    		    }	
		  return 4; 
		} // electron block ends
	      
	      // muon block
	      if(preselLeptonsFull[ProbeLeptonIndex]->is_muon())
		{ // Fill muon histograms
		  cutFlowTable_mu->update("Probe lepton exists and is a muon", evtWeight);
		  cutFlowTable_mu_woTrigger->update("Probe lepton exists and is a muon", evtWeight_wo_TrigPrescale);
		  const RecoLepton & preselMuon = *(preselLeptonsFull[ProbeLeptonIndex]);
		  const RecoMEt met_mod = METSystComp_LeptonFakeRate(preselLeptonsFull[ProbeLeptonIndex], genmet, met, METScaleSyst, metSyst_option, isDEBUG);
		  const double mT     = comp_mT(preselMuon, met_mod.pt(), met_mod.phi());
		  const double mT_fix = comp_mT_fix(preselMuon, met_mod.pt(), met_mod.phi());

		  // Fill Ntuples for muon
		  FillNtuples(preselLeptonsFull[ProbeLeptonIndex], eventInfo, evtWeight, evtWeight_wo_TrigPrescale, mT, mT_fix, passesMETandTrigger, bdt_filler_mu_diLeptSS);

		  // numerator histograms
		  numerator_and_denominatorHistManagers * histograms_incl_num = nullptr;
		  std::vector<numerator_and_denominatorHistManagers *> * histograms_binned_num = nullptr;
		  numerator_and_denominatorHistManagers * histograms_incl_num_woTrigger = nullptr;
		  std::vector<numerator_and_denominatorHistManagers *> * histograms_binned_num_woTrigger = nullptr;
		  // denominator histograms
		  numerator_and_denominatorHistManagers * histograms_incl_den = nullptr;
		  std::vector<numerator_and_denominatorHistManagers *> * histograms_binned_den = nullptr;
		  numerator_and_denominatorHistManagers * histograms_incl_den_woTrigger = nullptr;
		  std::vector<numerator_and_denominatorHistManagers *> * histograms_binned_den_woTrigger = nullptr;
		  if(preselMuon.isTight())
		    {// numerator mu histograms filled
		      if(passMETFilter)
			{// Passes MET Filter (w/o Trigger cond.) 
			  histograms_incl_num_woTrigger = histograms_mu_numerator_incl_diLeptSS_woTrigger;
			  histograms_binned_num_woTrigger = &histograms_mu_numerator_binned_diLeptSS_woTrigger;
			  if(histograms_incl_num_woTrigger != nullptr && histograms_binned_num_woTrigger != nullptr)
			    {
			      histograms_incl_num_woTrigger->fillHistograms(preselMuon, met.pt(), mT, mT_fix, evtWeight_wo_TrigPrescale); //(w/o Trigger)
			      fillHistograms(*histograms_binned_num_woTrigger, preselMuon, met.pt(), mT, mT_fix, evtWeight_wo_TrigPrescale, cutFlowTable_mu_woTrigger); //(w/o Trigger) 			      
			    }
			}
		      if(passesMETandTrigger)
			{// Passes MET Filter (w Trigger cond.)
			  histograms_incl_num = histograms_mu_numerator_incl_diLeptSS;
			  histograms_binned_num = &histograms_mu_numerator_binned_diLeptSS;
			  if(histograms_incl_num != nullptr && histograms_binned_num != nullptr)
			    {
			      histograms_incl_num->fillHistograms(preselMuon, met.pt(), mT, mT_fix, evtWeight); //(w Trigger)
			      fillHistograms(*histograms_binned_num, preselMuon, met.pt(), mT, mT_fix, evtWeight, cutFlowTable_mu); //(w Trigger) 
			    }
			}
		    }

		  //if(preselMuon.isFakeable())  // CERN group logic
		  if(preselMuon.isFakeable() && !preselMuon.isTight()) // Tallinn Group logic
		    {// denominator mu histograms filled
		      if(passMETFilter)
			{// Passes MET Filter (w/o Trigger cond.) 
			  histograms_incl_den_woTrigger = histograms_mu_denominator_incl_diLeptSS_woTrigger;
			  histograms_binned_den_woTrigger = &histograms_mu_denominator_binned_diLeptSS_woTrigger;
			  if(histograms_incl_den_woTrigger != nullptr && histograms_binned_den_woTrigger != nullptr)
			    {
			      histograms_incl_den_woTrigger->fillHistograms(preselMuon, met.pt(), mT, mT_fix, evtWeight_wo_TrigPrescale); //(w/o Trigger) 
			      fillHistograms(*histograms_binned_den_woTrigger, preselMuon, met.pt(), mT, mT_fix, evtWeight_wo_TrigPrescale, cutFlowTable_mu_woTrigger); //(w/o Trigger)
			      }
			}
		      if(passesMETandTrigger)
			{// Passes MET Filter (w Trigger cond.) 
			  histograms_incl_den = histograms_mu_denominator_incl_diLeptSS;
			  histograms_binned_den = &histograms_mu_denominator_binned_diLeptSS;
			  if(histograms_incl_den != nullptr && histograms_binned_den != nullptr)
			    {
			      histograms_incl_den->fillHistograms(preselMuon, met.pt(), mT, mT_fix, evtWeight); //(w Trigger)
				fillHistograms(*histograms_binned_den, preselMuon, met.pt(), mT, mT_fix, evtWeight, cutFlowTable_mu); //(w Trigger)
			      }
			}
		    }
		  return 5; 
		} // muon block ends	      
	      
	    }else{ // Same Sign cond. not satisfied
	    return 3; 
	  }
	}else{ // Both Tag and probe exists cond. not satisfied
	return 2; 
      }
    }else{// 2 Loose/Presel Leptons cond. not satisfied
    return 1; 
  }
  return 0;
}// func ends


int
main(int argc,
     char ** argv)
{
//--- throw an exception in case ROOT encounters an error
  gErrorAbortLevel = kError;

//--- stop ROOT from keeping track of all histograms
  TH1::AddDirectory(false);

//--- parse command-line arguments
  if(argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " [parameters.py]\n";
    return EXIT_FAILURE;
  }

  std::cout << "<analyze_LeptonFakeRate>:\n";

//--- keep track of time it takes the macro to execute
  TBenchmark clock;
  clock.Start(argv[0]);

//--- initialize RNG
  TRandom3 rand(12345);

//--- read python configuration parameters
  if(! edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process"))
  {
    throw cmsException(argv[0])
      << "No ParameterSet 'process' found in configuration file = " << argv[1];
  }

  const edm::ParameterSet cfg = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");
  const edm::ParameterSet cfg_analyze = cfg.getParameter<edm::ParameterSet>("analyze_LeptonFakeRate");
  const std::string treeName = cfg_analyze.getParameter<std::string>("treeName");
  const std::string process_string = cfg_analyze.getParameter<std::string>("process");
  const bool isMC_tHq = process_string == "tHq";
  const bool isMC_tHW = process_string == "tHW";
  const bool isMC_tH = isMC_tHq || isMC_tHW;
  const bool isSignal = process_string == "ttH" || process_string == "ttH_ctcvcp";
  const bool isMC_QCD = process_string == "QCD";
  const bool isMC_EWK = process_string == "WZ" || process_string == "ZZ"; // Taken from HH 3l

  const std::string era_string = cfg_analyze.getParameter<std::string>("era");
  const Era era = get_era(era_string);
  const bool isMC    = cfg_analyze.getParameter<bool>("isMC");
  const bool hasLHE  = cfg_analyze.getParameter<bool>("hasLHE");
  const bool useObjectMultiplicity = cfg_analyze.getParameter<bool>("useObjectMultiplicity");

  const std::string apply_topPtReweighting_str = cfg_analyze.getParameter<std::string>("apply_topPtReweighting");
  const std::string central_or_shift = cfg_analyze.getParameter<std::string>("central_or_shift");
  edm::VParameterSet lumiScale = cfg_analyze.getParameter<edm::VParameterSet>("lumiScale");
  const bool apply_genWeight            = cfg_analyze.getParameter<bool>("apply_genWeight");
  const bool apply_topPtReweighting     = ! apply_topPtReweighting_str.empty();
  const bool apply_DYMCReweighting      = cfg_analyze.getParameter<bool>("apply_DYMCReweighting");
  const bool apply_DYMCNormScaleFactors = cfg_analyze.getParameter<bool>("apply_DYMCNormScaleFactors");
  const bool apply_l1PreFireWeight      = cfg_analyze.getParameter<bool>("apply_l1PreFireWeight");
  const bool apply_btagSFRatio          = cfg_analyze.getParameter<bool>("applyBtagSFRatio");
  const bool fillGenEvtHistograms       = cfg_analyze.getParameter<bool>("fillGenEvtHistograms");
  const bool jetCleaningByIndex         = cfg_analyze.getParameter<bool>("jetCleaningByIndex");
  const bool redoGenMatching            = cfg_analyze.getParameter<bool>("redoGenMatching");
  const bool genMatchingByIndex         = cfg_analyze.getParameter<bool>("genMatchingByIndex");
  const bool readGenObjects             = isMC && ! redoGenMatching;
  const bool isDEBUG                    = cfg_analyze.getParameter<bool>("isDEBUG");
  const bool apply_met_filters          = cfg_analyze.getParameter<bool>("apply_met_filters");
  const double min_PV_ndof              = cfg_analyze.getParameter<double>("min_PV_ndof");
  
  const vstring triggerNames_1e = cfg_analyze.getParameter<vstring>("triggers_1e");
  const vstring triggerNames_2e = cfg_analyze.getParameter<vstring>("triggers_2e");
  const vstring triggerNames_1mu = cfg_analyze.getParameter<vstring>("triggers_1mu");
  const vstring triggerNames_2mu = cfg_analyze.getParameter<vstring>("triggers_2mu");

  const bool use_triggers_1e  = cfg_analyze.getParameter<bool>("use_triggers_1e");
  const bool use_triggers_2e  = cfg_analyze.getParameter<bool>("use_triggers_2e");
  const bool use_triggers_1mu = cfg_analyze.getParameter<bool>("use_triggers_1mu");
  const bool use_triggers_2mu = cfg_analyze.getParameter<bool>("use_triggers_2mu");

  const bool fillNtuple = ( cfg_analyze.exists("fillNtuple") ) ? cfg_analyze.getParameter<bool>("fillNtuple") : false;

  edm::ParameterSet triggerWhiteList;
  if(! isMC)
  {
    triggerWhiteList = cfg_analyze.getParameter<edm::ParameterSet>("triggerWhiteList");
  }

  const edm::VParameterSet cfg_triggers_e = cfg_analyze.getParameter<edm::VParameterSet>("triggers_e_cfg");
  std::vector<hltPath_LeptonFakeRate *> triggers_e;
  if(use_triggers_1e || use_triggers_2e)
  {
    for(const edm::ParameterSet & cfg_trigger: cfg_triggers_e)
    {
      const std::string trigger_path = cfg_trigger.getParameter<std::string>("path");
      const bool is_trigger_1e = cfg_trigger.getParameter<bool>("is_trigger_1e");
      const bool is_trigger_2e = cfg_trigger.getParameter<bool>("is_trigger_2e");
      assert(is_trigger_1e || is_trigger_2e);

      if(! ((is_trigger_1e && use_triggers_1e) ||(is_trigger_2e && use_triggers_2e)))
      {
        std::cout << "Skipping electron HLT path = '" << trigger_path << "'\n";
        continue;
      }

      if((is_trigger_1e && std::find(triggerNames_1e.begin(), triggerNames_1e.end(), trigger_path) == triggerNames_1e.end()) ||
         (is_trigger_2e && std::find(triggerNames_2e.begin(), triggerNames_2e.end(), trigger_path) == triggerNames_2e.end())  )
      {
        std::cout << "HLT path '" << trigger_path << "' is not in the list of available electron HLT paths\n";
        continue;
      }

      std::cout << "Selecting electron HLT path = '" << trigger_path << "'\n";
      const std::vector<hltPath_LeptonFakeRate *> hltPaths = create_hltPaths_LeptonFakeRate({ trigger_path }, cfg_trigger);
      triggers_e.insert(triggers_e.end(), hltPaths.begin(), hltPaths.end());
    }
  }

  const edm::VParameterSet cfg_triggers_mu = cfg_analyze.getParameter<edm::VParameterSet>("triggers_mu_cfg");
  std::vector<hltPath_LeptonFakeRate *> triggers_mu;
  if(use_triggers_1mu || use_triggers_2mu)
  {
    for(const edm::ParameterSet & cfg_trigger: cfg_triggers_mu)
    {
      const std::string trigger_path = cfg_trigger.getParameter<std::string>("path");
      const bool is_trigger_1mu = cfg_trigger.getParameter<bool>("is_trigger_1mu");
      const bool is_trigger_2mu = cfg_trigger.getParameter<bool>("is_trigger_2mu");
      assert(is_trigger_1mu || is_trigger_2mu);

      if(!((is_trigger_1mu && use_triggers_1mu) ||(is_trigger_2mu && use_triggers_2mu)))
      {
        std::cout << "Skipping muon HLT path = '" << trigger_path << "'\n";
        continue;
      }

      if((is_trigger_1mu && std::find(triggerNames_1mu.begin(), triggerNames_1mu.end(), trigger_path) == triggerNames_1mu.end()) ||
         (is_trigger_2mu && std::find(triggerNames_2mu.begin(), triggerNames_2mu.end(), trigger_path) == triggerNames_2mu.end())  )
      {
        std::cout << "HLT path '" << trigger_path << "' is not in the list of available muon HLT paths\n";
        continue;
      }

      std::cout << "Selecting muon HLT path = '" << trigger_path << "'\n";
      const std::vector<hltPath_LeptonFakeRate *> hltPaths = create_hltPaths_LeptonFakeRate({ trigger_path }, cfg_trigger);
      triggers_mu.insert(triggers_mu.end(), hltPaths.begin(), hltPaths.end());
    }
  }

  // sort HLT paths by reco pT thresholds in descending order (from higher pT threshold to lowest)
  std::sort(triggers_e.begin(),  triggers_e.end(),  isHigherMinRecoPt);
  std::sort(triggers_mu.begin(), triggers_mu.end(), isHigherMinRecoPt);

  const vdouble etaBins_e  = cfg_analyze.getParameter<vdouble>("absEtaBins_e");
  const vdouble ptBins_e   = cfg_analyze.getParameter<vdouble>("ptBins_e");
  const vdouble etaBins_mu = cfg_analyze.getParameter<vdouble>("absEtaBins_mu");
  const vdouble ptBins_mu  = cfg_analyze.getParameter<vdouble>("ptBins_mu");

  const double minConePt_global_e  = cfg_analyze.getParameter<double>("minConePt_global_e");
  const double minConePt_global_mu = cfg_analyze.getParameter<double>("minConePt_global_mu");
  const double minRecoPt_global_e  = cfg_analyze.getParameter<double>("minRecoPt_global_e");
  const double minRecoPt_global_mu = cfg_analyze.getParameter<double>("minRecoPt_global_mu");

  const double lep_mva_cut_mu = cfg_analyze.getParameter<double>("lep_mva_cut_mu");
  const double lep_mva_cut_e  = cfg_analyze.getParameter<double>("lep_mva_cut_e");
  const double METScaleSyst   = cfg_analyze.getParameter<double>("METScaleSyst");

  
  const std::string branchName_electrons = cfg_analyze.getParameter<std::string>("branchName_electrons");
  const std::string branchName_muons     = cfg_analyze.getParameter<std::string>("branchName_muons");
  const std::string branchName_hadTaus   = cfg_analyze.getParameter<std::string>("branchName_hadTaus"); // Taken from HH 3l
  const std::string branchName_jets      = cfg_analyze.getParameter<std::string>("branchName_jets");
  const std::string branchName_met       = cfg_analyze.getParameter<std::string>("branchName_met");
  const std::string branchName_vertex    = cfg_analyze.getParameter<std::string>("branchName_vertex");
  const std::string branchName_genmet    = cfg_analyze.getParameter<std::string>("branchName_genmet");

  const std::string branchName_genTauLeptons = cfg_analyze.getParameter<std::string>("branchName_genTauLeptons");
  const std::string branchName_genLeptons    = cfg_analyze.getParameter<std::string>("branchName_genLeptons");
  const std::string branchName_genHadTaus    = cfg_analyze.getParameter<std::string>("branchName_genHadTaus");
  const std::string branchName_genPhotons    = cfg_analyze.getParameter<std::string>("branchName_genPhotons");
  const std::string branchName_genJets       = cfg_analyze.getParameter<std::string>("branchName_genJets");

  const std::string branchName_muonGenMatch     = cfg_analyze.getParameter<std::string>("branchName_muonGenMatch");
  const std::string branchName_electronGenMatch = cfg_analyze.getParameter<std::string>("branchName_electronGenMatch");
  const std::string branchName_jetGenMatch      = cfg_analyze.getParameter<std::string>("branchName_jetGenMatch");

  const edm::ParameterSet cfgMEtFilter = cfg_analyze.getParameter<edm::ParameterSet>("cfgMEtFilter");
  const MEtFilterSelector metFilterSelector(cfgMEtFilter, isMC);
  const bool useNonNominal = cfg_analyze.getParameter<bool>("useNonNominal"); // Added from HH 3l
  const bool useNonNominal_jetmet = useNonNominal || ! isMC;     // Added from HH 3l

  const std::string selEventsFileName_input = cfg_analyze.exists("selEventsFileName_input") ?
                                              cfg_analyze.getParameter<std::string>("selEventsFileName_input") : ""
  ;
  std::cout << "selEventsFileName_input = '" << selEventsFileName_input << "'\n";
  RunLumiEventSelector * run_lumi_eventSelector = nullptr;
  if(! selEventsFileName_input.empty())
  {
    edm::ParameterSet cfgRunLumiEventSelector;
    cfgRunLumiEventSelector.addParameter<std::string>("inputFileName", selEventsFileName_input);
    cfgRunLumiEventSelector.addParameter<std::string>("separator",     ":");
    run_lumi_eventSelector = new RunLumiEventSelector(cfgRunLumiEventSelector);
  }

  const std::string selEventsFileName_output = cfg_analyze.getParameter<std::string>("selEventsFileName_output");
  const bool writeTo_selEventsFileOut = ! selEventsFileName_output.empty();
  std::map<std::string, std::map<std::string, std::ofstream *>> outputFiles;
  for(const std::string & emu_str: { "e", "mu" })
  {
    for(const std::string & numden_str: { "num", "den" })
    {
      outputFiles[emu_str][numden_str] = writeTo_selEventsFileOut ?
        new std::ofstream(Form(selEventsFileName_output.data(), emu_str.data(), numden_str.data())) :
        nullptr
      ;
    }
  }

  const edm::ParameterSet additionalEvtWeight = cfg_analyze.getParameter<edm::ParameterSet>("evtWeight");
  const bool applyAdditionalEvtWeight = additionalEvtWeight.getParameter<bool>("apply");
  EvtWeightManager * eventWeightManager = nullptr;
  if(applyAdditionalEvtWeight)
  {
    eventWeightManager = new EvtWeightManager(additionalEvtWeight);
    eventWeightManager->set_central_or_shift(central_or_shift);
  }

  checkOptionValidity(central_or_shift, isMC);
  const int jetPt_option    = useNonNominal_jetmet ? kJetMET_central_nonNominal : getJet_option(central_or_shift, isMC); // Taken from HH 3l
  const int met_option      = useNonNominal_jetmet ? kJetMET_central_nonNominal : getMET_option(central_or_shift, isMC); // Taken from HH 3l
  const int hadTauPt_option = useNonNominal_jetmet ? kHadTauPt_uncorrected      : getHadTauPt_option(central_or_shift);  // Taken from HH 3l
  const METSyst metSyst_option = getMETsyst_option(central_or_shift); // DEFAULT

  std::cout
    << "central_or_shift = "    << central_or_shift           << "\n"
       " -> met_option      = " << met_option                 << "\n"
       " -> metSyst_option  = " << as_integer(metSyst_option) << "\n"
       " -> jetPt_option    = " << jetPt_option               << "\n"
       " -> hadTauPt_option = " << hadTauPt_option            << '\n'
  ;

  // ------ Taken from HH 3l ----------------
  edm::ParameterSet cfg_dataToMCcorrectionInterface; 
  cfg_dataToMCcorrectionInterface.addParameter<std::string>("era", era_string);
  cfg_dataToMCcorrectionInterface.addParameter<std::string>("hadTauSelection", "disabled");
  cfg_dataToMCcorrectionInterface.addParameter<int>("hadTauSelection_antiElectron", -1);
  cfg_dataToMCcorrectionInterface.addParameter<int>("hadTauSelection_antiMuon", -1);
  Data_to_MC_CorrectionInterface_Base * dataToMCcorrectionInterface = nullptr;
  switch(era)
    {
    case Era::k2016: dataToMCcorrectionInterface = new Data_to_MC_CorrectionInterface_2016(cfg_dataToMCcorrectionInterface); break;
    case Era::k2017: dataToMCcorrectionInterface = new Data_to_MC_CorrectionInterface_2017(cfg_dataToMCcorrectionInterface); break;
    case Era::k2018: dataToMCcorrectionInterface = new Data_to_MC_CorrectionInterface_2018(cfg_dataToMCcorrectionInterface); break;
    default: throw cmsException("analyze_LeptonFakeRate", __LINE__) << "Invalid era = " << static_cast<int>(era);
    }
  Data_to_MC_CorrectionInterface_Base * dataToMCcorrectionInterface_ntuple = nullptr;
  switch(era)
    {
    case Era::k2016: dataToMCcorrectionInterface_ntuple = new Data_to_MC_CorrectionInterface_2016(cfg_dataToMCcorrectionInterface); break;
    case Era::k2017: dataToMCcorrectionInterface_ntuple = new Data_to_MC_CorrectionInterface_2017(cfg_dataToMCcorrectionInterface); break;
    case Era::k2018: dataToMCcorrectionInterface_ntuple = new Data_to_MC_CorrectionInterface_2018(cfg_dataToMCcorrectionInterface); break;
    default: throw cmsException("analyze_LeptonFakeRate", __LINE__) << "Invalid era = " << static_cast<int>(era);
    }

  // ---------------------------------------

  DYMCReweighting * dyReweighting = nullptr;
  if(apply_DYMCReweighting)
  {
    dyReweighting = new DYMCReweighting(era);
  }
  DYMCNormScaleFactors * dyNormScaleFactors = nullptr;
  if(apply_DYMCNormScaleFactors)
  {
    dyNormScaleFactors = new DYMCNormScaleFactors(era);
  }

  fwlite::InputSource inputFiles(cfg);
  const int maxEvents        = inputFiles.maxEvents();
  const unsigned reportEvery = inputFiles.reportAfter();

  TTreeWrapper * inputTree = new TTreeWrapper(treeName, inputFiles.files(), maxEvents);
  std::cout << "Loaded " << inputTree->getFileCount() << " file(s).\n";

  fwlite::OutputFiles outputFile(cfg);
  fwlite::TFileService fs = fwlite::TFileService(outputFile.file().data());

  std::string OutputFileName = outputFile.file().data();
  std::cout<< "OutputFileName " << OutputFileName << std::endl;
  bool isMC_TT_SL = false;
  if(OutputFileName.find("TTToSemiLeptonic") != std::string::npos)
    {// handle for semileptonic TTbar MC samples
      isMC_TT_SL = true;
    }

  bool isMC_TT_HAD = false;
  if(OutputFileName.find("TTToHadronic") != std::string::npos)
    {// handle for hadronic TTbar MC samples
      isMC_TT_HAD = true;
    }

//--- declare event-level variables
  EventInfo eventInfo(isMC, false, false, apply_topPtReweighting);
  const std::vector<edm::ParameterSet> tHweights = cfg_analyze.getParameterSetVector("tHweights");
  if((isMC_tH || isSignal) && ! tHweights.empty())
  {
    eventInfo.set_central_or_shift(central_or_shift);
    eventInfo.loadWeight_tH(tHweights);
  }
  EventInfoReader eventInfoReader(&eventInfo);
  if(apply_topPtReweighting)
  {
    eventInfoReader.setTopPtRwgtBranchName(apply_topPtReweighting_str);
  }
  inputTree->registerReader(&eventInfoReader);

  RecoVertexReader vertexReader(branchName_vertex);
  inputTree -> registerReader(&vertexReader);

  ObjectMultiplicity objectMultiplicity;
  ObjectMultiplicityReader objectMultiplicityReader(&objectMultiplicity);
  if(useObjectMultiplicity)
  {
    inputTree -> registerReader(&objectMultiplicityReader);
  }

  std::vector<hltPath_LeptonFakeRate *> triggers_all;
  triggers_all.insert(triggers_all.end(), triggers_e.begin(), triggers_e.end());
  triggers_all.insert(triggers_all.end(), triggers_mu.begin(), triggers_mu.end());

  std::vector<hltPath *> triggers;
  triggers.insert(triggers.end(), triggers_e.begin(), triggers_e.end());
  triggers.insert(triggers.end(), triggers_mu.begin(), triggers_mu.end());
  hltPathReader hltPathReader_instance(triggers);
  inputTree -> registerReader(&hltPathReader_instance);

  if(eventWeightManager)
  {
    inputTree->registerReader(eventWeightManager);
  }

  L1PreFiringWeightReader * l1PreFiringWeightReader = nullptr;
  if(apply_l1PreFireWeight)
  {
    l1PreFiringWeightReader = new L1PreFiringWeightReader(era);
    inputTree->registerReader(l1PreFiringWeightReader);
  }

  BtagSFRatioFacility * btagSFRatioFacility = nullptr;
  if(apply_btagSFRatio)
  {
    const edm::ParameterSet btagSFRatio = cfg_analyze.getParameterSet("btagSFRatio");
    btagSFRatioFacility = new BtagSFRatioFacility(btagSFRatio);
  }

//--- declare particle collections
  RecoMuonReader * muonReader = new RecoMuonReader(era, branchName_muons, isMC, readGenObjects);
  inputTree->registerReader(muonReader);
  RecoMuonCollectionGenMatcher muonGenMatcher;
  RecoMuonCollectionSelectorLoose preselMuonSelector(era);
  //RecoMuonCollectionSelectorFakeable fakeableMuonSelector(era); // DEFAULT FAKE DEF. USED IN TTH ANALYSIS
  RecoMuonCollectionSelectorFakeable_hh_multilepton fakeableMuonSelector(era); // NEW HH OPTIMIZED FAKE DEFINITION
  RecoMuonCollectionSelectorTight tightMuonSelector(era);       
  muonReader->set_mvaTTH_wp(lep_mva_cut_mu);

  RecoElectronReader * electronReader = new RecoElectronReader(era, branchName_electrons, isMC, readGenObjects);
  inputTree->registerReader(electronReader);
  //RecoElectronCollectionGenMatcher electronGenMatcher(true);
  RecoElectronCollectionGenMatcher electronGenMatcher;
  RecoElectronCollectionCleaner electronCleaner(0.3);
  RecoElectronCollectionSelectorLoose preselElectronSelector(era);
  //RecoElectronCollectionSelectorFakeable fakeableElectronSelector(era); // DEFAULT FAKE DEF. USED IN TTH ANALYSIS
  RecoElectronCollectionSelectorFakeable_hh_multilepton fakeableElectronSelector(era); // NEW HH OPTIMIZED FAKE DEFINITION
  RecoElectronCollectionSelectorTight tightElectronSelector(era); 
  electronReader->set_mvaTTH_wp(lep_mva_cut_e);
  fakeableElectronSelector.enable_offline_e_trigger_cuts();
  tightElectronSelector.enable_offline_e_trigger_cuts();

  RecoJetReader * jetReader = new RecoJetReader(era, isMC, branchName_jets, readGenObjects);
  jetReader->setPtMass_central_or_shift(jetPt_option);
  jetReader->read_btag_systematics(central_or_shift != "central" && isMC);
  inputTree->registerReader(jetReader);
  RecoJetCollectionGenMatcher jetGenMatcher;
  RecoJetCollectionCleaner jetCleaner_dR04(0.4, isDEBUG);
  RecoJetCollectionCleanerByIndex jetCleanerByIndex(isDEBUG);
  RecoJetCollectionCleaner jetCleaner_dR07(0.7, isDEBUG); // Christian's suggestion
  RecoJetCollectionSelector jetSelector(era);
  jetSelector.getSelector().set_min_pt(30.);
  jetSelector.getSelector().set_max_absEta(2.4);
  RecoJetCollectionSelectorBtagLoose jetSelectorBtagLoose(era);
  RecoJetCollectionSelectorBtagMedium jetSelectorBtagMedium(era);

//--- declare missing transverse energy
  RecoMEtReader * metReader = new RecoMEtReader(era, isMC, branchName_met);
  metReader->setMEt_central_or_shift(met_option);
  inputTree->registerReader(metReader);

//--- declare MET filter
  MEtFilter metFilter;
  MEtFilterReader * metFilterReader = new MEtFilterReader(&metFilter, era);
  inputTree->registerReader(metFilterReader);

// --- Setting up the Met Filter Hist Manager ----
  const edm::ParameterSet metFilterHistManagerCfg = makeHistManager_cfg(process_string, "LeptonFakeRate/met_filters", era_string, central_or_shift);
  MEtFilterHistManager * metFilterHistManager = new MEtFilterHistManager(metFilterHistManagerCfg);
  metFilterHistManager->bookHistograms(fs);

//--- declare generator level information
  GenLeptonReader * genLeptonReader = nullptr;
  GenHadTauReader * genHadTauReader = nullptr;
  GenJetReader * genJetReader       = nullptr;
  GenPhotonReader * genPhotonReader = nullptr;
  LHEInfoReader * lheInfoReader     = nullptr;

  GenParticleReader * genMatchToMuonReader     = nullptr;
  GenParticleReader * genMatchToElectronReader = nullptr;
  GenParticleReader * genMatchToJetReader      = nullptr;
  GenMEtReader * genmetReader  = nullptr;

  if(isMC)
  {
    if(! readGenObjects)
    {
      genLeptonReader = new GenLeptonReader(branchName_genLeptons);
      inputTree->registerReader(genLeptonReader);
      genHadTauReader = new GenHadTauReader(branchName_genHadTaus);
      inputTree->registerReader(genHadTauReader);
      genJetReader = new GenJetReader(branchName_genJets);
      inputTree->registerReader(genJetReader);

      if(genMatchingByIndex)
      {
        genMatchToMuonReader = new GenParticleReader(branchName_muonGenMatch);
        genMatchToMuonReader -> readGenPartFlav(true);
        inputTree -> registerReader(genMatchToMuonReader);

        genMatchToElectronReader = new GenParticleReader(branchName_electronGenMatch);
        genMatchToElectronReader -> readGenPartFlav(true);
        inputTree -> registerReader(genMatchToElectronReader);

        genMatchToJetReader = new GenParticleReader(branchName_jetGenMatch);
        genMatchToJetReader -> readGenPartFlav(true);
        inputTree -> registerReader(genMatchToJetReader);
      }
      else
      {
        genPhotonReader = new GenPhotonReader(branchName_genPhotons);
        inputTree->registerReader(genPhotonReader);
      }
    }
    genmetReader = new GenMEtReader(era, isMC, branchName_genmet); 
    inputTree->registerReader(genmetReader);
    lheInfoReader = new LHEInfoReader(hasLHE);
    inputTree->registerReader(lheInfoReader);
  }

  GenParticleReader * genTauLeptonReader = nullptr;
  if(isMC && (apply_DYMCReweighting || apply_DYMCNormScaleFactors))
  {
    genTauLeptonReader = new GenParticleReader(branchName_genTauLeptons);
    inputTree->registerReader(genTauLeptonReader);
  }

  const auto get_num_den_hist_managers =
    [&process_string, isMC, &era_string, &central_or_shift](const std::string & dir,
                                                            int lepton_type,
                                                            double minAbsEta = -1.,
                                                            double maxAbsEta = -1.,
                                                            double minPt = -1.,
                                                            double maxPt = -1.,
                                                            const std::string & subdir_suffix = "")
    -> numerator_and_denominatorHistManagers * const
  {
    return new numerator_and_denominatorHistManagers(
      process_string, isMC, era_string, central_or_shift, Form("LeptonFakeRate/%s", dir.data()),
      lepton_type, minAbsEta, maxAbsEta, minPt, maxPt, subdir_suffix
    );
  };

//--- book histograms for electron numerator and denominator

  auto histograms_e_numerator_incl_LeptonPlusJet = get_num_den_hist_managers("numerator/LeptonPlusJet/electrons_tight", kElectron); // NEW !
  histograms_e_numerator_incl_LeptonPlusJet->bookHistograms(fs); // NEW !

  auto histograms_e_numerator_incl_LeptonPlusJet_woTrigger = get_num_den_hist_managers("numerator/LeptonPlusJet_woTrigger/electrons_tight", kElectron); // NEW !
  histograms_e_numerator_incl_LeptonPlusJet_woTrigger->bookHistograms(fs); // NEW !

  auto histograms_e_denominator_incl_LeptonPlusJet = get_num_den_hist_managers("denominator/LeptonPlusJet/electrons_fakeable", kElectron); // NEW !
  histograms_e_denominator_incl_LeptonPlusJet->bookHistograms(fs); // NEW !

  auto histograms_e_denominator_incl_LeptonPlusJet_woTrigger = get_num_den_hist_managers("denominator/LeptonPlusJet_woTrigger/electrons_fakeable", kElectron); // NEW !
  histograms_e_denominator_incl_LeptonPlusJet_woTrigger->bookHistograms(fs); // NEW !

  auto histograms_e_numerator_incl_diLeptSS = get_num_den_hist_managers("numerator/diLeptSS/electrons_tight", kElectron); // NEW !
  histograms_e_numerator_incl_diLeptSS->bookHistograms(fs); // NEW !

  auto histograms_e_numerator_incl_diLeptSS_woTrigger = get_num_den_hist_managers("numerator/diLeptSS_woTrigger/electrons_tight", kElectron); // NEW !
  histograms_e_numerator_incl_diLeptSS_woTrigger->bookHistograms(fs); // NEW !

  auto histograms_e_denominator_incl_diLeptSS = get_num_den_hist_managers("denominator/diLeptSS/electrons_fakeable", kElectron); // NEW !
  histograms_e_denominator_incl_diLeptSS->bookHistograms(fs); // NEW !

  auto histograms_e_denominator_incl_diLeptSS_woTrigger = get_num_den_hist_managers("denominator/diLeptSS_woTrigger/electrons_fakeable", kElectron); // NEW !
  histograms_e_denominator_incl_diLeptSS_woTrigger->bookHistograms(fs); // NEW !

  auto histograms_e_numerator_incl_beforeCuts = get_num_den_hist_managers("numerator/electrons_tight", kElectron);
  histograms_e_numerator_incl_beforeCuts->bookHistograms(fs);

  auto histograms_e_denominator_incl_beforeCuts = get_num_den_hist_managers("denominator/electrons_fakeable", kElectron);
  histograms_e_denominator_incl_beforeCuts->bookHistograms(fs);

  auto histograms_e_numerator_incl_afterCuts = get_num_den_hist_managers(
    "numerator/electrons_tight", kElectron, -1., -1., -1., -1., "aftercuts"
  );
  histograms_e_numerator_incl_afterCuts->bookHistograms(fs);

  auto histograms_e_denominator_incl_afterCuts = get_num_den_hist_managers(
    "denominator/electrons_fakeable", kElectron, -1., -1., -1., -1., "aftercuts"
  );
  histograms_e_denominator_incl_afterCuts->bookHistograms(fs);

  std::vector<numerator_and_denominatorHistManagers *> histograms_e_numerator_binned_LeptonPlusJet;   // NEW !
  std::vector<numerator_and_denominatorHistManagers *> histograms_e_numerator_binned_LeptonPlusJet_woTrigger;   // NEW !
  std::vector<numerator_and_denominatorHistManagers *> histograms_e_denominator_binned_LeptonPlusJet; // NEW !
  std::vector<numerator_and_denominatorHistManagers *> histograms_e_denominator_binned_LeptonPlusJet_woTrigger; // NEW !
  std::vector<numerator_and_denominatorHistManagers *> histograms_e_numerator_binned_diLeptSS;   // NEW !
  std::vector<numerator_and_denominatorHistManagers *> histograms_e_numerator_binned_diLeptSS_woTrigger;   // NEW !
  std::vector<numerator_and_denominatorHistManagers *> histograms_e_denominator_binned_diLeptSS; // NEW !
  std::vector<numerator_and_denominatorHistManagers *> histograms_e_denominator_binned_diLeptSS_woTrigger; // NEW !
  std::vector<numerator_and_denominatorHistManagers *> histograms_e_numerator_binned_beforeCuts;
  std::vector<numerator_and_denominatorHistManagers *> histograms_e_denominator_binned_beforeCuts;
  std::vector<numerator_and_denominatorHistManagers *> histograms_e_numerator_binned_afterCuts;
  std::vector<numerator_and_denominatorHistManagers *> histograms_e_denominator_binned_afterCuts;
  const int numEtaBins_e = etaBins_e.size() - 1;
  const int numPtBins_e  = ptBins_e.size()  - 1;

  for(int idxEtaBin_e = 0; idxEtaBin_e < numEtaBins_e; ++idxEtaBin_e)
  {
    const double minAbsEta_e = std::abs(etaBins_e[idxEtaBin_e]);
    const double maxAbsEta_e = std::abs(etaBins_e[idxEtaBin_e + 1]);

    for(int idxPtBin_e = 0; idxPtBin_e < numPtBins_e; ++idxPtBin_e)
    {
      const double minPt_e = ptBins_e[idxPtBin_e];
      const double maxPt_e = ptBins_e[idxPtBin_e + 1];

      auto histograms_numerator_LeptonPlusJet = get_num_den_hist_managers(
	"numerator/LeptonPlusJet/electrons_tight", kElectron, minAbsEta_e, maxAbsEta_e, minPt_e, maxPt_e
      ); // NEW !
      histograms_numerator_LeptonPlusJet->bookHistograms(fs); // NEW !
      histograms_e_numerator_binned_LeptonPlusJet.push_back(histograms_numerator_LeptonPlusJet); // NEW !

      auto histograms_numerator_LeptonPlusJet_woTrigger = get_num_den_hist_managers(
	"numerator/LeptonPlusJet_woTrigger/electrons_tight", kElectron, minAbsEta_e, maxAbsEta_e, minPt_e, maxPt_e
      ); // NEW !
      histograms_numerator_LeptonPlusJet_woTrigger->bookHistograms(fs); // NEW !
      histograms_e_numerator_binned_LeptonPlusJet_woTrigger.push_back(histograms_numerator_LeptonPlusJet_woTrigger); // NEW !

      auto histograms_denominator_LeptonPlusJet = get_num_den_hist_managers(
        "denominator/LeptonPlusJet/electrons_fakeable", kElectron, minAbsEta_e, maxAbsEta_e, minPt_e, maxPt_e
      ); // NEW !
      histograms_denominator_LeptonPlusJet->bookHistograms(fs); // NEW !
      histograms_e_denominator_binned_LeptonPlusJet.push_back(histograms_denominator_LeptonPlusJet); // NEW !

      auto histograms_denominator_LeptonPlusJet_woTrigger = get_num_den_hist_managers(
        "denominator/LeptonPlusJet_woTrigger/electrons_fakeable", kElectron, minAbsEta_e, maxAbsEta_e, minPt_e, maxPt_e
      ); // NEW !
      histograms_denominator_LeptonPlusJet_woTrigger->bookHistograms(fs); // NEW !
      histograms_e_denominator_binned_LeptonPlusJet_woTrigger.push_back(histograms_denominator_LeptonPlusJet_woTrigger); // NEW !

      auto histograms_numerator_diLeptSS = get_num_den_hist_managers(
	"numerator/diLeptSS/electrons_tight", kElectron, minAbsEta_e, maxAbsEta_e, minPt_e, maxPt_e
      ); // NEW !
      histograms_numerator_diLeptSS->bookHistograms(fs); // NEW !
      histograms_e_numerator_binned_diLeptSS.push_back(histograms_numerator_diLeptSS); // NEW !

      auto histograms_numerator_diLeptSS_woTrigger = get_num_den_hist_managers(
	"numerator/diLeptSS_woTrigger/electrons_tight", kElectron, minAbsEta_e, maxAbsEta_e, minPt_e, maxPt_e
      ); // NEW !
      histograms_numerator_diLeptSS_woTrigger->bookHistograms(fs); // NEW !
      histograms_e_numerator_binned_diLeptSS_woTrigger.push_back(histograms_numerator_diLeptSS_woTrigger); // NEW !

      auto histograms_denominator_diLeptSS = get_num_den_hist_managers(
        "denominator/diLeptSS/electrons_fakeable", kElectron, minAbsEta_e, maxAbsEta_e, minPt_e, maxPt_e
      ); // NEW !
      histograms_denominator_diLeptSS->bookHistograms(fs); // NEW !
      histograms_e_denominator_binned_diLeptSS.push_back(histograms_denominator_diLeptSS); // NEW !

      auto histograms_denominator_diLeptSS_woTrigger = get_num_den_hist_managers(
        "denominator/diLeptSS_woTrigger/electrons_fakeable", kElectron, minAbsEta_e, maxAbsEta_e, minPt_e, maxPt_e
      ); // NEW !
      histograms_denominator_diLeptSS_woTrigger->bookHistograms(fs); // NEW !
      histograms_e_denominator_binned_diLeptSS_woTrigger.push_back(histograms_denominator_diLeptSS_woTrigger); // NEW !

      auto histograms_numerator_beforeCuts = get_num_den_hist_managers(
        "numerator/electrons_tight", kElectron, minAbsEta_e, maxAbsEta_e, minPt_e, maxPt_e
      );
      histograms_numerator_beforeCuts->bookHistograms(fs);
      histograms_e_numerator_binned_beforeCuts.push_back(histograms_numerator_beforeCuts);

      auto histograms_denominator_beforeCuts = get_num_den_hist_managers(
        "denominator/electrons_fakeable", kElectron, minAbsEta_e, maxAbsEta_e, minPt_e, maxPt_e
      );
      histograms_denominator_beforeCuts->bookHistograms(fs);
      histograms_e_denominator_binned_beforeCuts.push_back(histograms_denominator_beforeCuts);

      auto histograms_numerator_afterCuts = get_num_den_hist_managers(
        "numerator/electrons_tight", kElectron, minAbsEta_e, maxAbsEta_e, minPt_e, maxPt_e, "aftercuts"
      );
      histograms_numerator_afterCuts->bookHistograms(fs);
      histograms_e_numerator_binned_afterCuts.push_back(histograms_numerator_afterCuts);

      auto histograms_denominator_afterCuts = get_num_den_hist_managers(
        "denominator/electrons_fakeable", kElectron, minAbsEta_e, maxAbsEta_e, minPt_e, maxPt_e, "aftercuts"
      );
      histograms_denominator_afterCuts->bookHistograms(fs);
      histograms_e_denominator_binned_afterCuts.push_back(histograms_denominator_afterCuts);
    }
  }

//--- book histograms for muon numerator and denominator
  auto histograms_mu_numerator_incl_LeptonPlusJet = get_num_den_hist_managers("numerator/LeptonPlusJet/muons_tight", kMuon);   // NEW !
  histograms_mu_numerator_incl_LeptonPlusJet->bookHistograms(fs); // NEW !

  auto histograms_mu_numerator_incl_LeptonPlusJet_woTrigger = get_num_den_hist_managers("numerator/LeptonPlusJet_woTrigger/muons_tight", kMuon);   // NEW !
  histograms_mu_numerator_incl_LeptonPlusJet_woTrigger->bookHistograms(fs); // NEW !

  auto histograms_mu_denominator_incl_LeptonPlusJet = get_num_den_hist_managers("denominator/LeptonPlusJet/muons_fakeable", kMuon); // NEW !
  histograms_mu_denominator_incl_LeptonPlusJet->bookHistograms(fs); // NEW !

  auto histograms_mu_denominator_incl_LeptonPlusJet_woTrigger = get_num_den_hist_managers("denominator/LeptonPlusJet_woTrigger/muons_fakeable", kMuon); // NEW !
  histograms_mu_denominator_incl_LeptonPlusJet_woTrigger->bookHistograms(fs); // NEW !

  auto histograms_mu_numerator_incl_diLeptSS = get_num_den_hist_managers("numerator/diLeptSS/muons_tight", kMuon);   // NEW !
  histograms_mu_numerator_incl_diLeptSS->bookHistograms(fs); // NEW !

  auto histograms_mu_numerator_incl_diLeptSS_woTrigger = get_num_den_hist_managers("numerator/diLeptSS_woTrigger/muons_tight", kMuon);   // NEW !
  histograms_mu_numerator_incl_diLeptSS_woTrigger->bookHistograms(fs); // NEW !

  auto histograms_mu_denominator_incl_diLeptSS = get_num_den_hist_managers("denominator/diLeptSS/muons_fakeable", kMuon); // NEW !
  histograms_mu_denominator_incl_diLeptSS->bookHistograms(fs); // NEW !

  auto histograms_mu_denominator_incl_diLeptSS_woTrigger = get_num_den_hist_managers("denominator/diLeptSS_woTrigger/muons_fakeable", kMuon); // NEW !
  histograms_mu_denominator_incl_diLeptSS_woTrigger->bookHistograms(fs); // NEW !

  auto histograms_mu_numerator_incl_beforeCuts = get_num_den_hist_managers("numerator/muons_tight", kMuon);
  histograms_mu_numerator_incl_beforeCuts->bookHistograms(fs);

  auto histograms_mu_denominator_incl_beforeCuts = get_num_den_hist_managers("denominator/muons_fakeable", kMuon);
  histograms_mu_denominator_incl_beforeCuts->bookHistograms(fs);

  auto histograms_mu_numerator_incl_afterCuts = get_num_den_hist_managers(
    "numerator/muons_tight", kMuon, -1., -1., -1., -1., "aftercuts"
  );
  histograms_mu_numerator_incl_afterCuts->bookHistograms(fs);

  auto histograms_mu_denominator_incl_afterCuts = get_num_den_hist_managers(
    "denominator/muons_fakeable", kMuon, -1., -1., -1., -1., "aftercuts"
  );
  histograms_mu_denominator_incl_afterCuts->bookHistograms(fs);

  std::vector<numerator_and_denominatorHistManagers *> histograms_mu_numerator_binned_LeptonPlusJet; // NEW !
  std::vector<numerator_and_denominatorHistManagers *> histograms_mu_numerator_binned_LeptonPlusJet_woTrigger; // NEW !
  std::vector<numerator_and_denominatorHistManagers *> histograms_mu_denominator_binned_LeptonPlusJet; // NEW !
  std::vector<numerator_and_denominatorHistManagers *> histograms_mu_denominator_binned_LeptonPlusJet_woTrigger; // NEW !
  std::vector<numerator_and_denominatorHistManagers *> histograms_mu_numerator_binned_diLeptSS; // NEW !
  std::vector<numerator_and_denominatorHistManagers *> histograms_mu_numerator_binned_diLeptSS_woTrigger; // NEW !
  std::vector<numerator_and_denominatorHistManagers *> histograms_mu_denominator_binned_diLeptSS; // NEW !
  std::vector<numerator_and_denominatorHistManagers *> histograms_mu_denominator_binned_diLeptSS_woTrigger; // NEW !
  std::vector<numerator_and_denominatorHistManagers *> histograms_mu_numerator_binned_beforeCuts;
  std::vector<numerator_and_denominatorHistManagers *> histograms_mu_denominator_binned_beforeCuts;
  std::vector<numerator_and_denominatorHistManagers *> histograms_mu_numerator_binned_afterCuts;
  std::vector<numerator_and_denominatorHistManagers *> histograms_mu_denominator_binned_afterCuts;
  const int numEtaBins_mu = etaBins_mu.size() - 1;
  const int numPtBins_mu  = ptBins_mu.size()  - 1;

  for(int idxEtaBin_mu = 0; idxEtaBin_mu < numEtaBins_mu; ++idxEtaBin_mu)
  {
    const double minAbsEta_mu = std::abs(etaBins_mu[idxEtaBin_mu]);
    const double maxAbsEta_mu = std::abs(etaBins_mu[idxEtaBin_mu + 1]);

    for(int idxPtBin_mu = 0; idxPtBin_mu < numPtBins_mu; ++idxPtBin_mu)
    {
      const double minPt_mu = ptBins_mu[idxPtBin_mu];
      const double maxPt_mu = ptBins_mu[idxPtBin_mu + 1];

      auto histograms_numerator_LeptonPlusJet = get_num_den_hist_managers(
        "numerator/LeptonPlusJet/muons_tight", kMuon, minAbsEta_mu, maxAbsEta_mu, minPt_mu, maxPt_mu
      ); // NEW !
      histograms_numerator_LeptonPlusJet->bookHistograms(fs); // NEW !
      histograms_mu_numerator_binned_LeptonPlusJet.push_back(histograms_numerator_LeptonPlusJet); // NEW !

      auto histograms_numerator_LeptonPlusJet_woTrigger = get_num_den_hist_managers(
        "numerator/LeptonPlusJet_woTrigger/muons_tight", kMuon, minAbsEta_mu, maxAbsEta_mu, minPt_mu, maxPt_mu
      ); // NEW !
      histograms_numerator_LeptonPlusJet_woTrigger->bookHistograms(fs); // NEW !
      histograms_mu_numerator_binned_LeptonPlusJet_woTrigger.push_back(histograms_numerator_LeptonPlusJet_woTrigger); // NEW !

      auto histograms_denominator_LeptonPlusJet = get_num_den_hist_managers(
        "denominator/LeptonPlusJet/muons_fakeable", kMuon, minAbsEta_mu, maxAbsEta_mu, minPt_mu, maxPt_mu
      ); // NEW !
      histograms_denominator_LeptonPlusJet->bookHistograms(fs); // NEW !
      histograms_mu_denominator_binned_LeptonPlusJet.push_back(histograms_denominator_LeptonPlusJet); // NEW !

      auto histograms_denominator_LeptonPlusJet_woTrigger = get_num_den_hist_managers(
        "denominator/LeptonPlusJet_woTrigger/muons_fakeable", kMuon, minAbsEta_mu, maxAbsEta_mu, minPt_mu, maxPt_mu
      ); // NEW !
      histograms_denominator_LeptonPlusJet_woTrigger->bookHistograms(fs); // NEW !
      histograms_mu_denominator_binned_LeptonPlusJet_woTrigger.push_back(histograms_denominator_LeptonPlusJet_woTrigger); // NEW !

      auto histograms_numerator_diLeptSS = get_num_den_hist_managers(
        "numerator/diLeptSS/muons_tight", kMuon, minAbsEta_mu, maxAbsEta_mu, minPt_mu, maxPt_mu
      ); // NEW !
      histograms_numerator_diLeptSS->bookHistograms(fs); // NEW !
      histograms_mu_numerator_binned_diLeptSS.push_back(histograms_numerator_diLeptSS); // NEW !

      auto histograms_numerator_diLeptSS_woTrigger = get_num_den_hist_managers(
        "numerator/diLeptSS_woTrigger/muons_tight", kMuon, minAbsEta_mu, maxAbsEta_mu, minPt_mu, maxPt_mu
      ); // NEW !
      histograms_numerator_diLeptSS_woTrigger->bookHistograms(fs); // NEW !
      histograms_mu_numerator_binned_diLeptSS_woTrigger.push_back(histograms_numerator_diLeptSS_woTrigger); // NEW !

      auto histograms_denominator_diLeptSS = get_num_den_hist_managers(
        "denominator/diLeptSS/muons_fakeable", kMuon, minAbsEta_mu, maxAbsEta_mu, minPt_mu, maxPt_mu
      ); // NEW !
      histograms_denominator_diLeptSS->bookHistograms(fs); // NEW !
      histograms_mu_denominator_binned_diLeptSS.push_back(histograms_denominator_diLeptSS); // NEW !

      auto histograms_denominator_diLeptSS_woTrigger = get_num_den_hist_managers(
        "denominator/diLeptSS_woTrigger/muons_fakeable", kMuon, minAbsEta_mu, maxAbsEta_mu, minPt_mu, maxPt_mu
      ); // NEW !
      histograms_denominator_diLeptSS_woTrigger->bookHistograms(fs); // NEW !
      histograms_mu_denominator_binned_diLeptSS_woTrigger.push_back(histograms_denominator_diLeptSS_woTrigger); // NEW !

      auto histograms_numerator_beforeCuts = get_num_den_hist_managers(
        "numerator/muons_tight", kMuon, minAbsEta_mu, maxAbsEta_mu, minPt_mu, maxPt_mu
      );
      histograms_numerator_beforeCuts->bookHistograms(fs);
      histograms_mu_numerator_binned_beforeCuts.push_back(histograms_numerator_beforeCuts);

      auto histograms_denominator_beforeCuts = get_num_den_hist_managers(
        "denominator/muons_fakeable", kMuon, minAbsEta_mu, maxAbsEta_mu, minPt_mu, maxPt_mu
      );
      histograms_denominator_beforeCuts->bookHistograms(fs);
      histograms_mu_denominator_binned_beforeCuts.push_back(histograms_denominator_beforeCuts);

      auto histograms_numerator_afterCuts = get_num_den_hist_managers(
        "numerator/muons_tight", kMuon, minAbsEta_mu, maxAbsEta_mu, minPt_mu, maxPt_mu, "aftercuts"
      );
      histograms_numerator_afterCuts->bookHistograms(fs);
      histograms_mu_numerator_binned_afterCuts.push_back(histograms_numerator_afterCuts);

      auto histograms_denominator_afterCuts = get_num_den_hist_managers(
        "denominator/muons_fakeable", kMuon, minAbsEta_mu, maxAbsEta_mu, minPt_mu, maxPt_mu, "aftercuts"
      );
      histograms_denominator_afterCuts->bookHistograms(fs);
      histograms_mu_denominator_binned_afterCuts.push_back(histograms_denominator_afterCuts);
    }
  }

//--- book generator-level histograms for MC
  GenEvtHistManager * genEvtHistManager_beforeCuts = nullptr;
  GenEvtHistManager * genEvtHistManager_afterCuts  = nullptr;
  LHEInfoHistManager * lheInfoHistManager          = nullptr;
  if(isMC)
  {
    const auto getHistManagerCfg = [&process_string, &era_string, &central_or_shift](const std::string & dir)
      -> edm::ParameterSet
    {
      return makeHistManager_cfg(process_string, Form("LeptonFakeRate/%s", dir.data()), era_string, central_or_shift);
    };
    genEvtHistManager_beforeCuts = new GenEvtHistManager(getHistManagerCfg("gen_unbiased/genEvt"));
    genEvtHistManager_beforeCuts->bookHistograms(fs);

    genEvtHistManager_afterCuts = new GenEvtHistManager(getHistManagerCfg("gen_sel/genEvt"));
    genEvtHistManager_afterCuts->bookHistograms(fs);

    lheInfoHistManager = new LHEInfoHistManager(getHistManagerCfg("gen_sel/lheInfo"));
    lheInfoHistManager->bookHistograms(fs);

    if(eventWeightManager)
    {
      genEvtHistManager_beforeCuts->bookHistograms(fs, eventWeightManager);
      genEvtHistManager_afterCuts->bookHistograms(fs, eventWeightManager);
    }
  }

//--- book additional event level histograms
  TH1 * histogram_met_pt  = fs.make<TH1D>("met_pt",  "met_pt",   40, 0., 200.);
  TH1 * histogram_met_phi = fs.make<TH1D>("met_phi", "met_phi",  36, -TMath::Pi(), +TMath::Pi());
  

//---fill Ntuple for fakeable tuning
  NtupleFillerBDT<float, int>* bdt_filler_e_LeptonPlusJet = nullptr;
  NtupleFillerBDT<float, int>* bdt_filler_mu_LeptonPlusJet = nullptr;
  NtupleFillerBDT<float, int>* bdt_filler_e_diLeptSS = nullptr;
  NtupleFillerBDT<float, int>* bdt_filler_mu_diLeptSS = nullptr;
  typedef std::remove_pointer<decltype(bdt_filler_e_LeptonPlusJet)>::type::float_type float_type_e;
  typedef std::remove_pointer<decltype(bdt_filler_e_LeptonPlusJet)>::type::int_type   int_type_e;
  typedef std::remove_pointer<decltype(bdt_filler_mu_LeptonPlusJet)>::type::float_type float_type_mu;
  typedef std::remove_pointer<decltype(bdt_filler_mu_LeptonPlusJet)>::type::int_type   int_type_mu;
  typedef std::remove_pointer<decltype(bdt_filler_e_diLeptSS)>::type::float_type float_type_e;
  typedef std::remove_pointer<decltype(bdt_filler_e_diLeptSS)>::type::int_type   int_type_e;
  typedef std::remove_pointer<decltype(bdt_filler_mu_diLeptSS)>::type::float_type float_type_mu;
  typedef std::remove_pointer<decltype(bdt_filler_mu_diLeptSS)>::type::int_type   int_type_mu;
  if( fillNtuple ) {
    bdt_filler_e_LeptonPlusJet = new std::remove_pointer<decltype(bdt_filler_e_LeptonPlusJet)>::type(
	    makeHistManager_cfg(process_string, Form("LeptonFakeRate_ntuple_LeptonPlusJet/%s", "electron"), era_string, central_or_shift)
    );
    bdt_filler_e_LeptonPlusJet->register_variable<float_type_e>(
						  "cone_pt", "pt",  "eta", "dxy", "dz", "sip3d", "iso", "sigma_ieie", "HbyE",
						  "OnebyEminusOnebyP", "JetRelIso", "tth_mva", "DeepJet_WP", "assocJet_pt", "mT", "mT_fix", 
						  "evtWeight", "evtWeight_wo_TrigPrescale"
    );
    bdt_filler_e_LeptonPlusJet->register_variable<int_type_e>(
						"EGamma_MVA_WP", "Conv_reject", "miss_hits", "isTight", "isFakeable", "lep_isgenMatchedFake",
						"lep_isgenMatchedToLepton", "lep_isgenMatchedToPhoton", "lep_isgenMatchedToTau", "passesTrigger"
    );

    bdt_filler_e_diLeptSS = new std::remove_pointer<decltype(bdt_filler_e_diLeptSS)>::type(
	    makeHistManager_cfg(process_string, Form("LeptonFakeRate_ntuple_diLeptSS/%s", "electron"), era_string, central_or_shift)
    );
    bdt_filler_e_diLeptSS->register_variable<float_type_e>(
						  "cone_pt", "pt",  "eta", "dxy", "dz", "sip3d", "iso", "sigma_ieie", "HbyE",
						  "OnebyEminusOnebyP", "JetRelIso", "tth_mva", "DeepJet_WP", "assocJet_pt", "mT", "mT_fix", 
						  "evtWeight", "evtWeight_wo_TrigPrescale"
    );
    bdt_filler_e_diLeptSS->register_variable<int_type_e>(
						"EGamma_MVA_WP", "Conv_reject", "miss_hits", "isTight", "isFakeable", "lep_isgenMatchedFake",
						"lep_isgenMatchedToLepton", "lep_isgenMatchedToPhoton", "lep_isgenMatchedToTau", "passesTrigger"
    );

    bdt_filler_mu_LeptonPlusJet = new std::remove_pointer<decltype(bdt_filler_mu_LeptonPlusJet)>::type(
	    makeHistManager_cfg(process_string, Form("LeptonFakeRate_ntuple_LeptonPlusJet/%s", "muon"), era_string, central_or_shift)
    );
    bdt_filler_mu_LeptonPlusJet->register_variable<float_type_mu>(
						    "cone_pt", "pt", "eta", "dxy", "dz", "sip3d", "iso", "JetRelIso", 
						    "tth_mva", "DeepJet_WP", "assocJet_pt", "mT", "mT_fix", "evtWeight", 
						    "evtWeight_wo_TrigPrescale"
    );
    bdt_filler_mu_LeptonPlusJet->register_variable<int_type_mu>(
						  "PFMuon_WP", "isTight", "isFakeable", "lep_isgenMatchedFake",
						  "lep_isgenMatchedToLepton", "lep_isgenMatchedToTau", "passesTrigger"
    );

    bdt_filler_mu_diLeptSS = new std::remove_pointer<decltype(bdt_filler_mu_diLeptSS)>::type(
	    makeHistManager_cfg(process_string, Form("LeptonFakeRate_ntuple_diLeptSS/%s", "muon"), era_string, central_or_shift)
    );
    bdt_filler_mu_diLeptSS->register_variable<float_type_mu>(
						    "cone_pt", "pt", "eta", "dxy", "dz", "sip3d", "iso", "JetRelIso", 
						    "tth_mva", "DeepJet_WP", "assocJet_pt", "mT", "mT_fix", "evtWeight",
						    "evtWeight_wo_TrigPrescale"
    );
    bdt_filler_mu_diLeptSS->register_variable<int_type_mu>(
						  "PFMuon_WP", "isTight", "isFakeable", "lep_isgenMatchedFake",
						  "lep_isgenMatchedToLepton", "lep_isgenMatchedToTau", "passesTrigger"
    );
    bdt_filler_e_LeptonPlusJet->bookTree(fs);
    bdt_filler_e_diLeptSS->bookTree(fs);
    bdt_filler_mu_LeptonPlusJet->bookTree(fs);
    bdt_filler_mu_diLeptSS->bookTree(fs);
  }
//----------------------------------------


  int analyzedEntries = 0;
  int selectedEntries = 0;
  double selectedEntries_weighted = 0.;
  TH1 * histogram_analyzedEntries = fs.make<TH1D>("analyzedEntries", "analyzedEntries", 1, -0.5, +0.5);
  TH1 * histogram_selectedEntries = fs.make<TH1D>("selectedEntries", "selectedEntries", 1, -0.5, +0.5);

  cutFlowTableType cutFlowTable_e_LeptonPlusJet({}, isDEBUG);
  initializeCutFlowTable(cutFlowTable_e_LeptonPlusJet, "= 1 presel/Loose electron");
  initializeCutFlowTable(cutFlowTable_e_LeptonPlusJet, "Jet found at a dist. dR=0.7 from electron");
  initializeCutFlowTable(cutFlowTable_e_LeptonPlusJet, "Event passes trigger and MET filters");
  initializeCutFlowTable(cutFlowTable_e_LeptonPlusJet, histograms_e_numerator_binned_LeptonPlusJet);
  initializeCutFlowTable(cutFlowTable_e_LeptonPlusJet, histograms_e_denominator_binned_LeptonPlusJet);

  cutFlowTableType cutFlowTable_e_LeptonPlusJet_woTrigger({}, isDEBUG);
  initializeCutFlowTable(cutFlowTable_e_LeptonPlusJet_woTrigger, "= 1 presel/Loose electron");
  initializeCutFlowTable(cutFlowTable_e_LeptonPlusJet_woTrigger, "Jet found at a dist. dR=0.7 from electron");
  initializeCutFlowTable(cutFlowTable_e_LeptonPlusJet_woTrigger, "Event passes MET filters");
  initializeCutFlowTable(cutFlowTable_e_LeptonPlusJet_woTrigger, histograms_e_numerator_binned_LeptonPlusJet_woTrigger);
  initializeCutFlowTable(cutFlowTable_e_LeptonPlusJet_woTrigger, histograms_e_denominator_binned_LeptonPlusJet_woTrigger);

  cutFlowTableType cutFlowTable_e_diLeptSS({}, isDEBUG);
  initializeCutFlowTable(cutFlowTable_e_diLeptSS, "= 2 presel/Loose leptons");
  initializeCutFlowTable(cutFlowTable_e_diLeptSS, "Gen-matched lepton (Tag) exists");
  initializeCutFlowTable(cutFlowTable_e_diLeptSS, "Both presel/Loose leptons are Same Sign");
  initializeCutFlowTable(cutFlowTable_e_diLeptSS, "Event passes trigger and MET filters");
  initializeCutFlowTable(cutFlowTable_e_diLeptSS, "Probe lepton exists and is an electron");
  initializeCutFlowTable(cutFlowTable_e_diLeptSS, histograms_e_numerator_binned_diLeptSS);
  initializeCutFlowTable(cutFlowTable_e_diLeptSS, histograms_e_denominator_binned_diLeptSS);

  cutFlowTableType cutFlowTable_e_diLeptSS_woTrigger({}, isDEBUG);
  initializeCutFlowTable(cutFlowTable_e_diLeptSS_woTrigger, "= 2 presel/Loose leptons");
  initializeCutFlowTable(cutFlowTable_e_diLeptSS_woTrigger, "Gen-matched lepton (Tag) exists");
  initializeCutFlowTable(cutFlowTable_e_diLeptSS_woTrigger, "Both presel/Loose leptons are Same Sign");
  initializeCutFlowTable(cutFlowTable_e_diLeptSS_woTrigger, "Event passes MET filters");
  initializeCutFlowTable(cutFlowTable_e_diLeptSS_woTrigger, "Probe lepton exists and is an electron");
  initializeCutFlowTable(cutFlowTable_e_diLeptSS_woTrigger, histograms_e_numerator_binned_diLeptSS_woTrigger);
  initializeCutFlowTable(cutFlowTable_e_diLeptSS_woTrigger, histograms_e_denominator_binned_diLeptSS_woTrigger);

  cutFlowTableType cutFlowTable_mu_LeptonPlusJet({}, isDEBUG);
  initializeCutFlowTable(cutFlowTable_mu_LeptonPlusJet, "= 1 presel/Loose muon");
  initializeCutFlowTable(cutFlowTable_mu_LeptonPlusJet, "Jet found at a dist. dR=0.7 from muon");
  initializeCutFlowTable(cutFlowTable_mu_LeptonPlusJet, "Event passes trigger and MET filters");
  initializeCutFlowTable(cutFlowTable_mu_LeptonPlusJet, histograms_mu_numerator_binned_LeptonPlusJet);
  initializeCutFlowTable(cutFlowTable_mu_LeptonPlusJet, histograms_mu_denominator_binned_LeptonPlusJet);

  cutFlowTableType cutFlowTable_mu_LeptonPlusJet_woTrigger({}, isDEBUG);
  initializeCutFlowTable(cutFlowTable_mu_LeptonPlusJet_woTrigger, "= 1 presel/Loose muon");
  initializeCutFlowTable(cutFlowTable_mu_LeptonPlusJet_woTrigger, "Jet found at a dist. dR=0.7 from muon");
  initializeCutFlowTable(cutFlowTable_mu_LeptonPlusJet_woTrigger, "Event passes MET filters");
  initializeCutFlowTable(cutFlowTable_mu_LeptonPlusJet_woTrigger, histograms_mu_numerator_binned_LeptonPlusJet_woTrigger);
  initializeCutFlowTable(cutFlowTable_mu_LeptonPlusJet_woTrigger, histograms_mu_denominator_binned_LeptonPlusJet_woTrigger);


  cutFlowTableType cutFlowTable_mu_diLeptSS({}, isDEBUG);
  initializeCutFlowTable(cutFlowTable_mu_diLeptSS, "= 2 presel/Loose leptons");
  initializeCutFlowTable(cutFlowTable_mu_diLeptSS, "Gen-matched lepton (Tag) exists");
  initializeCutFlowTable(cutFlowTable_mu_diLeptSS, "Both presel/Loose leptons are Same Sign");
  initializeCutFlowTable(cutFlowTable_mu_diLeptSS, "Event passes trigger and MET filters");
  initializeCutFlowTable(cutFlowTable_mu_diLeptSS, "Probe lepton exists and is a muon");
  initializeCutFlowTable(cutFlowTable_mu_diLeptSS, histograms_mu_numerator_binned_diLeptSS);
  initializeCutFlowTable(cutFlowTable_mu_diLeptSS, histograms_mu_denominator_binned_diLeptSS);


  cutFlowTableType cutFlowTable_mu_diLeptSS_woTrigger({}, isDEBUG);
  initializeCutFlowTable(cutFlowTable_mu_diLeptSS_woTrigger, "= 2 presel/Loose leptons");
  initializeCutFlowTable(cutFlowTable_mu_diLeptSS_woTrigger, "Gen-matched lepton (Tag) exists");
  initializeCutFlowTable(cutFlowTable_mu_diLeptSS_woTrigger, "Both presel/Loose leptons are Same Sign");
  initializeCutFlowTable(cutFlowTable_mu_diLeptSS_woTrigger, "Event passes MET filters");
  initializeCutFlowTable(cutFlowTable_mu_diLeptSS_woTrigger, "Probe lepton exists and is an muon");
  initializeCutFlowTable(cutFlowTable_mu_diLeptSS_woTrigger, histograms_mu_numerator_binned_diLeptSS_woTrigger);
  initializeCutFlowTable(cutFlowTable_mu_diLeptSS_woTrigger, histograms_mu_denominator_binned_diLeptSS_woTrigger);


  cutFlowTableType cutFlowTable_e({}, isDEBUG);
  initializeCutFlowTable(cutFlowTable_e, ">= 1 presel/Loose electron");
  if(apply_met_filters)
  {
    initializeCutFlowTable(cutFlowTable_e, "MEt filter");
  }
  initializeCutFlowTable(cutFlowTable_e, "electron+jet pair passing trigger bit");
  initializeCutFlowTable(cutFlowTable_e, "electron+jet pair passing trigger bit && prescale");
  initializeCutFlowTable(cutFlowTable_e, "GoodElectronJetPair passing trigger and MEt filter");
  initializeCutFlowTable(cutFlowTable_e, "mT_fix(electron, MET) < 15 GeV (before cut)");
  initializeCutFlowTable(cutFlowTable_e, histograms_e_numerator_binned_beforeCuts);
  initializeCutFlowTable(cutFlowTable_e, histograms_e_denominator_binned_beforeCuts);
  initializeCutFlowTable(cutFlowTable_e, "mT_fix(electron, MET) < 15 GeV (after cut)");
  initializeCutFlowTable(cutFlowTable_e, histograms_e_numerator_binned_afterCuts);
  initializeCutFlowTable(cutFlowTable_e, histograms_e_denominator_binned_afterCuts);

  cutFlowTableType cutFlowTable_mu({}, isDEBUG);
  initializeCutFlowTable(cutFlowTable_mu, ">= 1 presel/Loose muon");
  if(apply_met_filters)
  {
    initializeCutFlowTable(cutFlowTable_mu, "MEt filter");
  }
  initializeCutFlowTable(cutFlowTable_mu, "muon+jet pair passing trigger bit");
  initializeCutFlowTable(cutFlowTable_mu, "muon+jet pair passing trigger bit && prescale");
  initializeCutFlowTable(cutFlowTable_mu, "GoodElectronJetPair passing trigger and MEt filter");
  initializeCutFlowTable(cutFlowTable_mu, "mT_fix(muon, MET) < 15 GeV (before cut)");
  initializeCutFlowTable(cutFlowTable_mu, histograms_mu_numerator_binned_beforeCuts);
  initializeCutFlowTable(cutFlowTable_mu, histograms_mu_denominator_binned_beforeCuts);
  initializeCutFlowTable(cutFlowTable_mu, "mT_fix(muon, MET) < 15 GeV (after cut)");
  initializeCutFlowTable(cutFlowTable_mu, histograms_mu_numerator_binned_afterCuts);
  initializeCutFlowTable(cutFlowTable_mu, histograms_mu_denominator_binned_afterCuts);

  while(inputTree -> hasNextEvent() && (! run_lumi_eventSelector || (run_lumi_eventSelector && ! run_lumi_eventSelector -> areWeDone())))
  {
    if(inputTree -> canReport(reportEvery))
    {
      std::cout << "processing Entry " << inputTree -> getCurrentMaxEventIdx()
                << " or " << inputTree -> getCurrentEventIdx() << " entry in #"
                << (inputTree -> getProcessedFileCount() - 1) << " ("
                << eventInfo << ") file (" << selectedEntries << " Entries selected)\n";
    }
    ++analyzedEntries;
    histogram_analyzedEntries->Fill(0.);

    if(isDEBUG)
    {
      std::cout << "event #" << inputTree -> getCurrentMaxEventIdx() << ' ' << eventInfo << '\n';
    }

    if(run_lumi_eventSelector && !(*run_lumi_eventSelector)(eventInfo))
    {
      continue;
    }

    if(run_lumi_eventSelector)
    {
      std::cout << "processing Entry " << inputTree -> getCurrentMaxEventIdx() << ": " << eventInfo << '\n';
      if(inputTree -> isOpen())
      {
        std::cout << "input File = " << inputTree -> getCurrentFileName() << '\n';
      }
    }

    if(useObjectMultiplicity)
    {
      if(objectMultiplicity.getNRecoLepton(kLoose) != 1)
      {
        if(isDEBUG || run_lumi_eventSelector)
        {
          std::cout << "event " << eventInfo.str() << " FAILS preliminary object multiplicity cuts\n";
        }
        continue;
      }
    }

    const RecoVertex vertex = vertexReader.read();
    if(vertex.ndof() <= min_PV_ndof)
    {
      if(run_lumi_eventSelector)
      {
        std::cout << "event " << eventInfo.str() << " FAILS PV ndof > " << min_PV_ndof << "cut \n";
      }
      continue;
    }

//--- build collections of generator level particles (before any cuts are applied,
//    to check distributions in unbiased event samples)
    std::vector<GenLepton> genLeptons;
    std::vector<GenLepton> genElectrons;
    std::vector<GenLepton> genMuons;
    std::vector<GenHadTau> genHadTaus;
    std::vector<GenPhoton> genPhotons;
    std::vector<GenJet> genJets;

    std::vector<GenParticle> muonGenMatch;
    std::vector<GenParticle> electronGenMatch;
    std::vector<GenParticle> jetGenMatch;
    if(isMC && fillGenEvtHistograms)
    {
      if(genLeptonReader)
      {
        genLeptons = genLeptonReader->read();
        for(const GenLepton & genLepton: genLeptons)
        {
          const int abs_pdgId = std::abs(genLepton.pdgId());
          switch(abs_pdgId)
          {
            case 11: genElectrons.push_back(genLepton); break;
            case 13: genMuons.push_back(genLepton);     break;
            default: assert(0);
          }
        }
      }
      if(genHadTauReader) genHadTaus = genHadTauReader->read();
      if(genPhotonReader) genPhotons = genPhotonReader->read();
      if(genJetReader)    genJets = genJetReader->read();

      if(genMatchToMuonReader)     muonGenMatch = genMatchToMuonReader->read();
      if(genMatchToElectronReader) electronGenMatch = genMatchToElectronReader->read();
      if(genMatchToJetReader)      jetGenMatch = genMatchToJetReader->read();
    }
  
//--- fill generator level histograms (before cuts)
    EvtWeightRecorder evtWeightRecorder({central_or_shift}, central_or_shift, isMC);
    std::vector<GenParticle> genTauLeptons;
    if(isMC && (apply_DYMCReweighting || apply_DYMCNormScaleFactors))
    {
      genTauLeptons = genTauLeptonReader->read();
    }
    if(isMC)
    {
      if(apply_genWeight)         evtWeightRecorder.record_genWeight(boost::math::sign(eventInfo.genWeight));
      if(apply_DYMCReweighting)   evtWeightRecorder.record_dy_rwgt(dyReweighting, genTauLeptons);
      if(eventWeightManager)      evtWeightRecorder.record_auxWeight(eventWeightManager);
      if(l1PreFiringWeightReader) evtWeightRecorder.record_l1PrefireWeight(l1PreFiringWeightReader);
      if(apply_topPtReweighting)  evtWeightRecorder.record_toppt_rwgt(eventInfo.topPtRwgtSF);
      lheInfoReader->read();
      evtWeightRecorder.record_lheScaleWeight(lheInfoReader);
      evtWeightRecorder.record_puWeight(&eventInfo);
      evtWeightRecorder.record_nom_tH_weight(&eventInfo);
      evtWeightRecorder.record_lumiScale(lumiScale);

      genEvtHistManager_beforeCuts->fillHistograms(
        genElectrons, genMuons, genHadTaus, genPhotons, genJets, evtWeightRecorder.get_inclusive(central_or_shift)
      );
      if(eventWeightManager)
      {
        genEvtHistManager_beforeCuts->fillHistograms(
          eventWeightManager, evtWeightRecorder.get_inclusive(central_or_shift)
        );
      }
    }

//--- build reco level collections of electrons, muons and hadronic taus;
//    resolve overlaps in order of priority: muon, electron,
    std::vector<RecoMuon> muons = muonReader->read();
    std::vector<const RecoMuon *> muon_ptrs = convert_to_ptrs(muons);
    // CV: no cleaning needed for muons, as they have the highest priority in the overlap removal
    std::vector<const RecoMuon *> cleanedMuons = muon_ptrs;
    std::vector<const RecoMuon *> preselMuons = preselMuonSelector(cleanedMuons); // Loose muons
    std::vector<const RecoMuon *> fakeableMuons = fakeableMuonSelector(preselMuons);
    std::vector<const RecoMuon *> tightMuons = tightMuonSelector(preselMuons);

    std::vector<RecoElectron> electrons = electronReader->read();
    std::vector<const RecoElectron *> electron_ptrs = convert_to_ptrs(electrons);
    std::vector<const RecoElectron *> cleanedElectrons = electronCleaner(electron_ptrs, preselMuons);
    std::vector<const RecoElectron *> preselElectrons = preselElectronSelector(cleanedElectrons); // Loose electrons
    std::vector<const RecoElectron *> fakeableElectrons = fakeableElectronSelector(preselElectrons);
    std::vector<const RecoElectron *> tightElectrons = tightElectronSelector(preselElectrons);

//--- build collections of jets and select subset of jets passing b-tagging criteria
    std::vector<RecoJet> jets = jetReader->read();
    std::vector<const RecoJet *> jet_ptrs = convert_to_ptrs(jets);
    std::vector<const RecoJet *> cleanedJets_dR04 = jetCleaningByIndex ?
      jetCleanerByIndex(jet_ptrs, fakeableMuons, fakeableElectrons) :
      jetCleaner_dR04  (jet_ptrs, fakeableMuons, fakeableElectrons)
    ; // changed from presel to be in sync with the analysis channels
    std::vector<const RecoJet *> selBJets_loose_dR04 = jetSelectorBtagLoose(cleanedJets_dR04);
    std::vector<const RecoJet *> selJets_dR04 = jetSelector(cleanedJets_dR04);
    std::vector<const RecoJet *> cleanedJets_dR07 = jetCleaner_dR07(jet_ptrs, fakeableMuons, fakeableElectrons); // changed from presel to be in sync with the analysis channels
    std::vector<const RecoJet *> selJets_dR07 = jetSelector(cleanedJets_dR07);

    const RecoMEt met = metReader->read();
    GenMEt genmet_tmp = GenMEt(0.,0.); // There is no MET Covariance stored in Ntuples
    if(isMC && (genmetReader != nullptr)){
      genmet_tmp = genmetReader->read();
    }

    const GenMEt genmet = genmet_tmp;    

//--- build collections of generator level particles (after some cuts are applied, to safe computing time)
    if(isMC && redoGenMatching && ! fillGenEvtHistograms)
    {
      if(genLeptonReader)
      {
        genLeptons = genLeptonReader->read();
        for(const GenLepton & genLepton: genLeptons)
        {
          const int abs_pdgId = std::abs(genLepton.pdgId());
          switch(abs_pdgId)
          {
            case 11: genElectrons.push_back(genLepton); break;
            case 13: genMuons.push_back(genLepton);     break;
            default: assert(0);
          }
        }
      }
      if(genHadTauReader) genHadTaus = genHadTauReader->read();
      if(genPhotonReader) genPhotons = genPhotonReader->read();
      if(genJetReader)    genJets = genJetReader->read();

      if(genMatchToMuonReader)     muonGenMatch = genMatchToMuonReader->read();
      if(genMatchToElectronReader) electronGenMatch = genMatchToElectronReader->read();
      if(genMatchToJetReader)      jetGenMatch = genMatchToJetReader->read();
    }
  
//--- match reconstructed to generator level particles
    if(isMC && redoGenMatching)
    {
      if(genMatchingByIndex)
      {
        muonGenMatcher.addGenLeptonMatchByIndex(preselMuons, muonGenMatch, GenParticleType::kGenMuon);
        muonGenMatcher.addGenHadTauMatch       (preselMuons, genHadTaus);
        muonGenMatcher.addGenJetMatch          (preselMuons, genJets);

        electronGenMatcher.addGenLeptonMatchByIndex(preselElectrons, electronGenMatch, GenParticleType::kGenElectron);
        electronGenMatcher.addGenPhotonMatchByIndex(preselElectrons, electronGenMatch);
        electronGenMatcher.addGenHadTauMatch       (preselElectrons, genHadTaus);
        electronGenMatcher.addGenJetMatch          (preselElectrons, genJets);

        jetGenMatcher.addGenLeptonMatch    (selJets_dR07, genLeptons);
        jetGenMatcher.addGenHadTauMatch    (selJets_dR07, genHadTaus);
        jetGenMatcher.addGenJetMatchByIndex(selJets_dR07, jetGenMatch);
      }
      else
      {
        muonGenMatcher.addGenLeptonMatch(preselMuons, genMuons);
        muonGenMatcher.addGenHadTauMatch(preselMuons, genHadTaus);
        muonGenMatcher.addGenJetMatch   (preselMuons, genJets);

        electronGenMatcher.addGenLeptonMatch(preselElectrons, genElectrons);
        electronGenMatcher.addGenPhotonMatch(preselElectrons, genPhotons);
        electronGenMatcher.addGenHadTauMatch(preselElectrons, genHadTaus);
        electronGenMatcher.addGenJetMatch   (preselElectrons, genJets);

        jetGenMatcher.addGenLeptonMatch(selJets_dR07, genLeptons);
        jetGenMatcher.addGenHadTauMatch(selJets_dR07, genHadTaus);
        jetGenMatcher.addGenJetMatch   (selJets_dR07, genJets);
      }
    }

    if(run_lumi_eventSelector)
    {
      std::cout << "Event Particle Collection Info\n";
      printCollection("preselElectrons", preselElectrons);
      printCollection("preselMuons", preselMuons);
      printCollection("uncleaned jets", jet_ptrs);
      printCollection("selJets_dR07", selJets_dR07);
    }


    if (printLevel==1) {
      std::cout << "processing Entry " << inputTree -> getCurrentMaxEventIdx()
                << " or " << inputTree -> getCurrentEventIdx() << " entry in #"
                << (inputTree -> getProcessedFileCount() - 1) << " ("
                << eventInfo << ") file (" << selectedEntries << " Entries selected)\n";
    }

    //std::cout << "event: " << eventInfo.str() << std::endl;
    std::vector<const RecoLepton*> preselLeptonsFull = mergeLeptonCollections(preselElectrons, preselMuons, isHigherConePt); // For The Ntuples

//********* Ntuple filling occurs here
    // ---Making a copy of the evtweightRecorder of the original workflow 
    // ---for the evtWeight of the MC Ntuples
    EvtWeightRecorder evtWeightRecorder_copy = EvtWeightRecorder();
    evtWeightRecorder_copy = evtWeightRecorder; 


    if(isMC && isMC_TT_SL)
      {//Runs only for TT_SemiLeptonic MC
	int DileptSS_result = DiLeptonSS(dataToMCcorrectionInterface_ntuple,
				     preselLeptonsFull,
				     jet_ptrs,
				     era_string,
				     apply_met_filters,
				     metFilter,
				     cfgMEtFilter,
				     genmet, 
				     met, 
				     METScaleSyst, 
				     metSyst_option,
				     histograms_e_numerator_incl_diLeptSS,
				     histograms_e_numerator_binned_diLeptSS,
				     histograms_e_denominator_incl_diLeptSS,
				     histograms_e_denominator_binned_diLeptSS,
				     histograms_mu_numerator_incl_diLeptSS,
				     histograms_mu_numerator_binned_diLeptSS,
				     histograms_mu_denominator_incl_diLeptSS,
				     histograms_mu_denominator_binned_diLeptSS,
				     histograms_e_numerator_incl_diLeptSS_woTrigger,
				     histograms_e_numerator_binned_diLeptSS_woTrigger,
				     histograms_e_denominator_incl_diLeptSS_woTrigger,
				     histograms_e_denominator_binned_diLeptSS_woTrigger,
				     histograms_mu_numerator_incl_diLeptSS_woTrigger,
				     histograms_mu_numerator_binned_diLeptSS_woTrigger,
				     histograms_mu_denominator_incl_diLeptSS_woTrigger,
				     histograms_mu_denominator_binned_diLeptSS_woTrigger,
				     evtWeightRecorder_copy,
				     central_or_shift,
				     eventInfo,
				     triggers_mu,
				     triggers_e,
				     minConePt_global_e,
				     minRecoPt_global_e,
				     minConePt_global_mu,
				     minRecoPt_global_mu,
				     use_triggers_1e,
			             use_triggers_2e,
				     use_triggers_1mu,
				     use_triggers_2mu,
				     isMC,
				     apply_DYMCNormScaleFactors,
				     //apply_DYMCReweighting,
				     genTauLeptons,
				     dyNormScaleFactors,
				     btagSFRatioFacility,
				     bdt_filler_e_diLeptSS,
				     bdt_filler_mu_diLeptSS,
				     isDEBUG,
				     &cutFlowTable_e_diLeptSS,
				     &cutFlowTable_mu_diLeptSS,
				     &cutFlowTable_e_diLeptSS_woTrigger,
				     &cutFlowTable_mu_diLeptSS_woTrigger);

      }

    if(isMC && (isMC_TT_HAD || isMC_QCD))
      {// Runs only for QCD and TTToHadronic
	int LeptonPlusJet_result = LeptonPlusJet(dataToMCcorrectionInterface_ntuple,
					     preselLeptonsFull,
					     jet_ptrs,
					     era_string,
					     apply_met_filters,
					     metFilter,
					     cfgMEtFilter,
					     genmet,
					     met,
					     METScaleSyst,
					     metSyst_option,
					     histograms_e_numerator_incl_LeptonPlusJet,
					     histograms_e_numerator_binned_LeptonPlusJet,
					     histograms_e_denominator_incl_LeptonPlusJet,
					     histograms_e_denominator_binned_LeptonPlusJet,
					     histograms_mu_numerator_incl_LeptonPlusJet,
					     histograms_mu_numerator_binned_LeptonPlusJet,
					     histograms_mu_denominator_incl_LeptonPlusJet,
					     histograms_mu_denominator_binned_LeptonPlusJet,
					     histograms_e_numerator_incl_LeptonPlusJet_woTrigger,
					     histograms_e_numerator_binned_LeptonPlusJet_woTrigger,
					     histograms_e_denominator_incl_LeptonPlusJet_woTrigger,
					     histograms_e_denominator_binned_LeptonPlusJet_woTrigger,
					     histograms_mu_numerator_incl_LeptonPlusJet_woTrigger,
					     histograms_mu_numerator_binned_LeptonPlusJet_woTrigger,
					     histograms_mu_denominator_incl_LeptonPlusJet_woTrigger,
					     histograms_mu_denominator_binned_LeptonPlusJet_woTrigger,
					     evtWeightRecorder_copy,
					     central_or_shift,
					     eventInfo,
					     triggers_mu,
					     triggers_e,
					     minConePt_global_e,
					     minRecoPt_global_e,
					     minConePt_global_mu,
					     minRecoPt_global_mu,
					     use_triggers_1e,
					     use_triggers_2e,
					     use_triggers_1mu,
					     use_triggers_2mu,
					     isMC,
					     apply_DYMCNormScaleFactors,
					     //apply_DYMCReweighting,
					     genTauLeptons,
					     dyNormScaleFactors,
					     btagSFRatioFacility,
					     bdt_filler_e_LeptonPlusJet,
					     bdt_filler_mu_LeptonPlusJet,
					     isDEBUG,
					     &cutFlowTable_e_LeptonPlusJet,
					     &cutFlowTable_mu_LeptonPlusJet,
					     &cutFlowTable_e_LeptonPlusJet_woTrigger,
					     &cutFlowTable_mu_LeptonPlusJet_woTrigger);

      }
// *************************



//--- require exactly one Loose lepton
    //if((preselElectrons.size() + preselMuons.size()) != 1) // Giovanni's pre-selection
    if(preselLeptonsFull.size() != 1)  // Giovanni's pre-selection
    {
      if(run_lumi_eventSelector)
      {
        std::cout << "event " << eventInfo.str() << " FAILS (presel.e + presel.mu != 1) cut\n";
      }
      continue;
    }

    if(preselElectrons.size() >= 1) cutFlowTable_e.update (">= 1 presel/Loose electron", evtWeightRecorder.get(central_or_shift));
    if(preselMuons.size()     >= 1) cutFlowTable_mu.update(">= 1 presel/Loose muon",     evtWeightRecorder.get(central_or_shift));
  
    if(apply_met_filters)
      {
        metFilterHistManager->fillHistograms(metFilter, evtWeightRecorder.get(central_or_shift));
        if(! metFilterSelector(metFilter))
          {
            if(run_lumi_eventSelector)
              {
                std::cout << "event " << eventInfo.str() << " FAILS MEtFilter\n";
              }
            continue;
          }
        cutFlowTable_e.update ("MEt filter", evtWeightRecorder.get(central_or_shift));
        cutFlowTable_mu.update("MEt filter", evtWeightRecorder.get(central_or_shift));
	if(preselElectrons.size() >= 1) cutFlowTable_e.update ("MEt filter, for e", evtWeightRecorder.get(central_or_shift));
	if(preselMuons.size()     >= 1) cutFlowTable_mu.update("MEt filter, for mu",     evtWeightRecorder.get(central_or_shift));

      }

    bool isTriggered_1e = false;
    bool isTriggered_2e = false;
    bool isTriggered_1mu = false;
    bool isTriggered_2mu = false;

    bool isGoodLeptonJetPair = false; // set to true if at least one electron+jet or one muon+jet combination passes trigger requirements
    bool isGoodMuonJetPair = false;
    bool isGoodElectronJetPair = false;
    std::vector<const RecoJet *> cleanedJets;
    std::vector<const RecoJet *> selJets;
    std::vector<const RecoJet*> selBJets_loose;
    std::vector<const RecoJet*> selBJets_medium;

    // muon block
    // loop over triggers_mu (given in descendng order of thresholds in the config)
    for(const hltPath_LeptonFakeRate * const hltPath_iter: triggers_mu)
    {
      hltPath_iter->setIsTriggered(false); // resetting the bool to false

      if(! (hltPath_iter->getValue() >= 1))
      {
        if(run_lumi_eventSelector)
        {
          std::cout << "event " << eventInfo.str() << " FAILS this mu trigger " << *hltPath_iter << '\n';
        }
        continue; // require trigger to fire
      }

      for(const RecoMuon * const preselMuon_ptr: preselMuons)
      {
        const RecoMuon & preselMuon = *preselMuon_ptr;

        // Giovanni's selection for global lepton reco and cone pt cuts
        if(!(preselMuon.cone_pt() > minConePt_global_mu && preselMuon.pt() > minRecoPt_global_mu))
        {
          if(run_lumi_eventSelector)
          {
            std::cout << "event " << eventInfo.str() << " FAILS global muon cone and reco pt cuts\n";
          }
          continue;
        }

        const std::vector<const RecoMuon*> tmp_leptons = { preselMuon_ptr };
        cleanedJets = jetCleaner_dR07(jet_ptrs, tmp_leptons);
        selJets = jetSelector(cleanedJets);
        selBJets_loose = jetSelectorBtagLoose(cleanedJets);
        selBJets_medium = jetSelectorBtagMedium(cleanedJets);

        for(const RecoJet * const selJet: selJets)
        {
          if(deltaR(preselMuon.p4(), selJet->p4()) <= 0.7)
          {
            if(run_lumi_eventSelector)
            {
              std::cout << "jet FAILS deltaR(presel. mu, sel-jet) > 0.7 cut\n"
                           "deltaR(preselMuon.p4(), selJet->p4()) " << deltaR(preselMuon.p4(), selJet->p4())
                        << '\n';
            }
            continue;
          }

          if(!( preselMuon.cone_pt() >= hltPath_iter->getMinPt()    &&
                preselMuon.cone_pt() <  hltPath_iter->getMaxPt()    &&
                selJet->pt()         >  hltPath_iter->getMinJetPt() &&
                preselMuon.pt()      >  hltPath_iter->getMinRecoPt()))
          {
            if(run_lumi_eventSelector)
            {
              std::cout << "Muon + jet pair FAILS trigger dep. Pt cuts "                      << "\n"
                           "preselMuon.cone_pt() = "          << preselMuon.cone_pt()         << "\n"
                           "hltPath_iter->getMinPt() = "      << hltPath_iter->getMinPt()     << "\n"
                           "hltPath_iter->getMaxPt() = "      << hltPath_iter->getMaxPt()     << "\n"
                           "selJet->pt() = "                  << selJet->pt()                 << "\n"
                           "Trigger Min. Jet pT = "           << hltPath_iter->getMinJetPt()  << "\n"
                           "preselMuon.pt() = "               << preselMuon.pt()              << "\n"
                           "Trigger Min. Reco Muon pT cut = " << hltPath_iter->getMinRecoPt() << '\n'
              ;
            }
            continue;
          }
          else
          {
            hltPath_iter->setIsTriggered(true);
            isGoodMuonJetPair = true;
            isGoodLeptonJetPair = true;
            break;
          }
        }
      }

      if(hltPath_iter->isTriggered())
      {
        isTriggered_2mu |= hltPath_iter->is_trigger_2mu();
        isTriggered_1mu |= hltPath_iter->is_trigger_1mu();
      }
    }

    // electron block
    for(const hltPath_LeptonFakeRate * const hltPath_iter: triggers_e)
    {
      hltPath_iter->setIsTriggered(false); // resetting the bool to false 

      if(! (hltPath_iter->getValue() >= 1))
      {
        if(run_lumi_eventSelector)
        {
          std::cout << "event " << eventInfo.str() << " FAILS this e trigger " << *hltPath_iter << '\n';
        }
        continue; // require trigger to fire
      }

      for(const RecoElectron * const preselElectron_ptr: preselElectrons)
      {
        const RecoElectron & preselElectron = *preselElectron_ptr;

        // Giovanni's selection for global lepton reco and cone pt cuts
        if(!(preselElectron.cone_pt() > minConePt_global_e && preselElectron.pt() > minRecoPt_global_e))
        {
          if(run_lumi_eventSelector)
          {
            std::cout << "presel Electron FAILS global reco pt and cone pt cuts\n"
                         "minConePt_global_e " << minConePt_global_e << " "
                         "minRecoPt_global_e " << minRecoPt_global_e << '\n'
            ;
          }
          continue;
	   }

        const std::vector<const RecoElectron *> tmp_leptons = { preselElectron_ptr };
        cleanedJets = jetCleaner_dR07(jet_ptrs, tmp_leptons);
        selJets = jetSelector(cleanedJets);
	selBJets_loose = jetSelectorBtagLoose(cleanedJets);
        selBJets_medium = jetSelectorBtagMedium(cleanedJets);

        for(const RecoJet * const selJet: selJets)
        {
          if(deltaR(preselElectron.p4(), selJet->p4()) <= 0.7)
          {
            if(run_lumi_eventSelector)
            {
              std::cout << "jet FAILS deltaR(presel. e, sel-jet) > 0.7 cut\n"
                           "deltaR(preselElectron.p4(), selJet->p4()) " << deltaR(preselElectron.p4(), selJet->p4())
                        << '\n'
              ;
            }
            continue;
          }


          if(!(preselElectron.cone_pt() >= hltPath_iter->getMinPt()    &&
               preselElectron.cone_pt() <  hltPath_iter->getMaxPt()    &&
               selJet->pt()             >  hltPath_iter->getMinJetPt() &&
               preselElectron.pt()      > hltPath_iter->getMinRecoPt() ))
          {
            if(run_lumi_eventSelector)
            {
              std::cout << "electron + jet pair FAILS trigger dep. Pt cuts "                      << "\n"
                           "preselElectron.cone_pt() = "           << preselElectron.cone_pt()    << "\n"
                           "hltPath_iter->getMinPt() = "          << hltPath_iter->getMinPt()     << "\n"
                           "hltPath_iter->getMaxPt() = "          << hltPath_iter->getMaxPt()     << "\n"
                           "selJet->pt() = "                      << selJet->pt()                 << "\n"
                           "Trigger Min. Jet pT cut = "           << hltPath_iter->getMinJetPt()  << "\n"
                           "preselElectron.pt() = "               << preselElectron.pt()          << "\n"
                           "Trigger Min. Reco Electron pT cut = " << hltPath_iter->getMinRecoPt() << '\n'
              ;
            }
            continue;
          }
          else
          {
            hltPath_iter->setIsTriggered(true);
            isGoodElectronJetPair = true; // set to true as soon as we find a jet matching all the above criteria
            isGoodLeptonJetPair = true;
            break;
          }
        } // loop over selJets ends
      } // loop over preselElectrons ends

      if(hltPath_iter->isTriggered())
      {
        isTriggered_2e |= hltPath_iter->is_trigger_2e();
        isTriggered_1e |= hltPath_iter->is_trigger_1e();
      }
    }

    const bool selTrigger_1e = use_triggers_1e && isTriggered_1e;
    const bool selTrigger_2e = use_triggers_2e && isTriggered_2e;
    const bool selTrigger_1mu = use_triggers_1mu && isTriggered_1mu;
    const bool selTrigger_2mu = use_triggers_2mu && isTriggered_2mu;

    if(! (selTrigger_1e || selTrigger_2e || selTrigger_1mu || selTrigger_2mu))
    {
      if(run_lumi_eventSelector)
      {
        std::cout << "event " << eventInfo.str() << " FAILS trigger selection.\n ("
                     "selTrigger_1e = "  << selTrigger_1e  << ", "
                     "selTrigger_2e = "  << selTrigger_2e  << ", "
                     "selTrigger_1mu = " << selTrigger_1mu << ", "
                     "selTrigger_2mu = " << selTrigger_2mu << ")\n"
        ;
      }
      continue;
    }
    //--- rank triggers by priority and ignore triggers of lower priority if a trigger of higher priority has fired for given event;
    //    the ranking of the triggers is as follows: 2mu, 2e, 1mu, 1e
    // CV: this logic is necessary to avoid that the same event is selected multiple times when processing different primary datasets
    if(! isMC && ! isDEBUG)
    {
      if(selTrigger_1e && (isTriggered_1mu || isTriggered_2e || isTriggered_2mu))
      {
        if(run_lumi_eventSelector)
        {
          std::cout << "event " << eventInfo.str() << " FAILS trigger selection.\n( "
                       "selTrigger_1e = "   << selTrigger_1e   << ", "
                       "isTriggered_2e = "  << isTriggered_2e  << ", "
                       "isTriggered_1mu = " << isTriggered_1mu << ", "
                       "isTriggered_2mu = " << isTriggered_2mu << ")\n"
          ;
        }
        continue;
      }
      if(selTrigger_1mu && (isTriggered_2e || isTriggered_2mu))
      {
        if(run_lumi_eventSelector)
        {
          std::cout << "event " << eventInfo.str() << " FAILS trigger selection.\n( "
                       "selTrigger_1mu = "  << selTrigger_1mu  << ", "
                       "isTriggered_2e = "  << isTriggered_2e  << ", "
                       "isTriggered_2mu = " << isTriggered_2mu << ")\n"
          ;
        }
        continue;
      }
      if(selTrigger_2e && isTriggered_2mu)
      {
        if(run_lumi_eventSelector)
        {
          std::cout << "event " << eventInfo.str() << " FAILS trigger selection.\n( "
                       "selTrigger_2e = "   << selTrigger_2e   << ", "
                       "isTriggered_2mu = " << isTriggered_2mu << ")\n"
          ;
        }
        continue;
      }
    }


    if(isMC)
    {
      if(apply_DYMCNormScaleFactors)
      {
        evtWeightRecorder.record_dy_norm(
          dyNormScaleFactors, genTauLeptons, selJets.size(), selBJets_loose.size(), selBJets_medium.size()
        );
      }
//--- compute event-level weight for data/MC correction of b-tagging efficiency and mistag rate
//   (using the method "Event reweighting using scale factors calculated with a tag and probe method",
//    described on the BTV POG twiki https://twiki.cern.ch/twiki/bin/view/CMS/BTagShapeCalibration )
      evtWeightRecorder.record_btagWeight(selJets);
      if(btagSFRatioFacility)
      {
        evtWeightRecorder.record_btagSFRatio(btagSFRatioFacility, selJets.size());
      }

      if(isMC_EWK) // Taken from HH 3l
	{
	  evtWeightRecorder.record_ewk_jet(selJets);
	  evtWeightRecorder.record_ewk_bjet(selBJets_medium);
	}

//--- Data/MC scale factors ---------
      ApplyDataToMCCorrection(preselLeptonsFull[0], dataToMCcorrectionInterface, evtWeightRecorder);
      //std::cout<<"Main Workflow (after corr.): evtWeightRecorder.get(central_or_shift): "<< evtWeightRecorder.get(central_or_shift) << std::endl;

//--- prescale weight      
      double prob_all_trigger_fail = 1.0;
      for(const hltPath_LeptonFakeRate * const hltPath_iter: triggers_all)
      {
        if(hltPath_iter->isTriggered())
        {
          prob_all_trigger_fail *= (1. - (1. / hltPath_iter->getPrescale()));
        }
      }
      evtWeightRecorder.record_prescale(1.0 - prob_all_trigger_fail);
      //std::cout<< "Data:: prescale_weight " << (1.0 - prob_all_trigger_fail) << std::endl;
    }


    //std::cout<< "Main Workflow evtWeightRecorder: " << evtWeightRecorder << std::endl;



    if(preselElectrons.size() >= 1) cutFlowTable_e.update ("pass triggers for e", evtWeightRecorder.get(central_or_shift));
    if(preselMuons.size()     >= 1) cutFlowTable_mu.update("pass triggers for mu",     evtWeightRecorder.get(central_or_shift));
    if (isGoodElectronJetPair) cutFlowTable_e.update("GoodElectronJetPair passing trigger and MEt filter",     evtWeightRecorder.get(central_or_shift));
    if (isGoodMuonJetPair) cutFlowTable_mu.update("GoodElectronJetPair passing trigger and MEt filter",     evtWeightRecorder.get(central_or_shift));
    if (printLevel==1) {
      std::cout << "FR default: " << evtWeightRecorder << "\nevtWt: " << evtWeightRecorder.get(central_or_shift) << '\n';
      //std::cout << "And evtWeightRecorder_copy: " << evtWeightRecorder_copy << "\nevtWt: " << evtWeightRecorder_copy.get(central_or_shift) << '\n';
      std::cout << "evtWt: " << evtWeightRecorder.get(central_or_shift) << ",   prescale wt: " << evtWeightRecorder.get_prescaleWeight() << std::endl;
    }
    
    
    // fill histograms for muons
    for(const RecoMuon * const preselMuon_ptr: preselMuons) // loop over preselMuons
    {
      if(! isGoodMuonJetPair)
      {
        break;
      }
      const RecoMuon & preselMuon = *preselMuon_ptr; 
      const RecoMEt met_mod = METSystComp_LeptonFakeRate(preselMuon_ptr, genmet, met, METScaleSyst, metSyst_option, isDEBUG);
      const double mT     = comp_mT    (preselMuon, met_mod.pt(), met_mod.phi());
      const double mT_fix = comp_mT_fix(preselMuon, met_mod.pt(), met_mod.phi());
      if(isDEBUG) {
	std::cout<< "mT (nominal) " << comp_mT(preselMuon, met.pt(), met.phi()) << std::endl;
	std::cout<< "mT_fix (nominal) " << comp_mT_fix(preselMuon, met.pt(), met.phi()) << std::endl;
	std::cout<< "mT " << mT_fix << std::endl;
	std::cout<< "mT_fix " << mT_fix << std::endl;
      }
      
      // numerator histograms
      numerator_and_denominatorHistManagers * histograms_incl_beforeCuts_num = nullptr;
      numerator_and_denominatorHistManagers * histograms_incl_afterCuts_num  = nullptr;
      std::vector<numerator_and_denominatorHistManagers *> * histograms_binned_beforeCuts_num = nullptr;
      std::vector<numerator_and_denominatorHistManagers *> * histograms_binned_afterCuts_num  = nullptr;
      // denominator histograms
      numerator_and_denominatorHistManagers * histograms_incl_beforeCuts_den = nullptr;
      numerator_and_denominatorHistManagers * histograms_incl_afterCuts_den  = nullptr;
      std::vector<numerator_and_denominatorHistManagers *> * histograms_binned_beforeCuts_den = nullptr;
      std::vector<numerator_and_denominatorHistManagers *> * histograms_binned_afterCuts_den  = nullptr;

      if(preselMuon.isTight())
      {
        // muon enters the numerator
        if(isDEBUG || run_lumi_eventSelector)
        {
          std::cout << "numerator filled\n";
        }
        histograms_incl_beforeCuts_num = histograms_mu_numerator_incl_beforeCuts;
        histograms_incl_afterCuts_num  = histograms_mu_numerator_incl_afterCuts;
        histograms_binned_beforeCuts_num = &histograms_mu_numerator_binned_beforeCuts;
        histograms_binned_afterCuts_num  = &histograms_mu_numerator_binned_afterCuts;
        if(writeTo_selEventsFileOut)
        {
          *(outputFiles["mu"]["num"]) << eventInfo.str() << '\n' ;
        }
      }

      if(histograms_incl_beforeCuts_num != nullptr && histograms_incl_afterCuts_num != nullptr &&
         histograms_binned_beforeCuts_num != nullptr && histograms_binned_afterCuts_num != nullptr)
      {
	cutFlowTable_mu.update("mT_fix(muon, MET) < 15 GeV (before cut)", evtWeightRecorder.get(central_or_shift));
        histograms_incl_beforeCuts_num->fillHistograms(preselMuon, met.pt(), mT, mT_fix, evtWeightRecorder.get(central_or_shift));
        fillHistograms(*histograms_binned_beforeCuts_num, preselMuon, met.pt(), mT, mT_fix, evtWeightRecorder.get(central_or_shift), &cutFlowTable_mu);

        if(mT_fix < 15.)
        {
          cutFlowTable_mu.update("mT_fix(muon, MET) < 15 GeV (after cut)", evtWeightRecorder.get(central_or_shift));
          histograms_incl_afterCuts_num->fillHistograms(preselMuon, met.pt(), mT, mT_fix, evtWeightRecorder.get(central_or_shift));
          fillHistograms(*histograms_binned_afterCuts_num, preselMuon, met.pt(), mT, mT_fix, evtWeightRecorder.get(central_or_shift), &cutFlowTable_mu);
        }
      }

      //if(preselMuon.isFakeable())                          // applying (isFakeable) condition [GIOVANNI'S METHOD]
      if(preselMuon.isFakeable() && !(preselMuon.isTight())) // applyng (isFakeable && !(isTight)) condition [TALLINN METHOD]
	{
	  // muon enters denominator (fakeable)
	  if(isDEBUG || run_lumi_eventSelector)
	    {
	      std::cout << "denominator filled\n";
	    }
	  histograms_incl_beforeCuts_den = histograms_mu_denominator_incl_beforeCuts;
	  histograms_incl_afterCuts_den  = histograms_mu_denominator_incl_afterCuts;
	  histograms_binned_beforeCuts_den = &histograms_mu_denominator_binned_beforeCuts;
	  histograms_binned_afterCuts_den  = &histograms_mu_denominator_binned_afterCuts;
	  if(writeTo_selEventsFileOut)
	    {
	      *(outputFiles["mu"]["den"]) << eventInfo.str() << '\n';
	    }
      }

      if(histograms_incl_beforeCuts_den != nullptr && histograms_incl_afterCuts_den != nullptr &&
         histograms_binned_beforeCuts_den != nullptr && histograms_binned_afterCuts_den != nullptr)
      {
	cutFlowTable_mu.update("mT_fix(muon, MET) < 15 GeV (before cut)", evtWeightRecorder.get(central_or_shift));
        histograms_incl_beforeCuts_den->fillHistograms(preselMuon, met.pt(), mT, mT_fix, evtWeightRecorder.get(central_or_shift));
        fillHistograms(*histograms_binned_beforeCuts_den, preselMuon, met.pt(), mT, mT_fix, evtWeightRecorder.get(central_or_shift), &cutFlowTable_mu);

        if(mT_fix < 15.)
        {
          cutFlowTable_mu.update("mT_fix(muon, MET) < 15 GeV (after cut)", evtWeightRecorder.get(central_or_shift));
          histograms_incl_afterCuts_den->fillHistograms(preselMuon, met.pt(), mT, mT_fix, evtWeightRecorder.get(central_or_shift));
          fillHistograms(*histograms_binned_afterCuts_den, preselMuon, met.pt(), mT, mT_fix, evtWeightRecorder.get(central_or_shift), &cutFlowTable_mu);
        }
      }
    }
    
    // fill histograms for electrons
    for(const RecoElectron * const preselElectron_ptr: preselElectrons) // loop over preselElectrons
    {
      if(!isGoodElectronJetPair)
      {
        break;
      }
      const RecoElectron & preselElectron = *preselElectron_ptr; 
      const RecoMEt met_mod = METSystComp_LeptonFakeRate(preselElectron_ptr, genmet, met, METScaleSyst, metSyst_option, isDEBUG);
      const double mT     = comp_mT    (preselElectron, met_mod.pt(), met_mod.phi());
      const double mT_fix = comp_mT_fix(preselElectron, met_mod.pt(), met_mod.phi());
      if(isDEBUG) {
	std::cout<< "mT (nominal) " << comp_mT(preselElectron, met.pt(), met.phi()) << std::endl;
	std::cout<< "mT_fix (nominal) " << comp_mT_fix(preselElectron, met.pt(), met.phi()) << std::endl;
	std::cout<< "mT " << mT_fix << std::endl;
	std::cout<< "mT_fix " << mT_fix << std::endl;
      }

      numerator_and_denominatorHistManagers * histograms_incl_beforeCuts_num = nullptr;
      numerator_and_denominatorHistManagers * histograms_incl_afterCuts_num  = nullptr;
      std::vector<numerator_and_denominatorHistManagers *> * histograms_binned_beforeCuts_num = nullptr;
      std::vector<numerator_and_denominatorHistManagers *> * histograms_binned_afterCuts_num  = nullptr;
      numerator_and_denominatorHistManagers * histograms_incl_beforeCuts_den = nullptr;
      numerator_and_denominatorHistManagers * histograms_incl_afterCuts_den  = nullptr;
      std::vector<numerator_and_denominatorHistManagers *> * histograms_binned_beforeCuts_den = nullptr;
      std::vector<numerator_and_denominatorHistManagers *> * histograms_binned_afterCuts_den  = nullptr;


      if(preselElectron.isTight())
      {

        if(isDEBUG || run_lumi_eventSelector)
        {
          std::cout << "numerator filled\n";
	}

        // electron enters numerator
        histograms_incl_beforeCuts_num = histograms_e_numerator_incl_beforeCuts;
        histograms_incl_afterCuts_num  = histograms_e_numerator_incl_afterCuts;
        histograms_binned_beforeCuts_num = &histograms_e_numerator_binned_beforeCuts;
        histograms_binned_afterCuts_num  = &histograms_e_numerator_binned_afterCuts;
        if(writeTo_selEventsFileOut)
        {
          *(outputFiles["e"]["num"]) << eventInfo.str() <<  '\n';
        }
      }

      if(histograms_incl_beforeCuts_num != nullptr && histograms_incl_afterCuts_num != nullptr &&
         histograms_binned_beforeCuts_num != nullptr && histograms_binned_afterCuts_num != nullptr)
      {
	cutFlowTable_e.update("mT_fix(electron, MET) < 15 GeV (before cut)", evtWeightRecorder.get(central_or_shift));
        histograms_incl_beforeCuts_num->fillHistograms(preselElectron, met.pt(), mT, mT_fix, evtWeightRecorder.get(central_or_shift));
        fillHistograms(*histograms_binned_beforeCuts_num, preselElectron, met.pt(), mT, mT_fix, evtWeightRecorder.get(central_or_shift), &cutFlowTable_e);

        if(mT_fix < 15.)
        {
          cutFlowTable_e.update("mT_fix(electron, MET) < 15 GeV (after cut)", evtWeightRecorder.get(central_or_shift));
          histograms_incl_afterCuts_num->fillHistograms(preselElectron, met.pt(), mT, mT_fix, evtWeightRecorder.get(central_or_shift));
          fillHistograms(*histograms_binned_afterCuts_num, preselElectron, met.pt(), mT, mT_fix, evtWeightRecorder.get(central_or_shift), &cutFlowTable_e);
        }
      }


      //if(preselElectron.isFakeable())                              // applying (isFakeable) condition [GIOVANNI'S/CERN METHOD]
      if(preselElectron.isFakeable() && !(preselElectron.isTight())) // applying (isFakeable && !(isTight)) condition [TALLINN METHOD]
	{

	  if(isDEBUG || run_lumi_eventSelector)
	    {
	      std::cout << "denominator filled\n";
	    }
	  // electron enters denominator (fakeable but not tight)
	  histograms_incl_beforeCuts_den = histograms_e_denominator_incl_beforeCuts;
	  histograms_incl_afterCuts_den  = histograms_e_denominator_incl_afterCuts;
	  histograms_binned_beforeCuts_den = &histograms_e_denominator_binned_beforeCuts;
	  histograms_binned_afterCuts_den  = &histograms_e_denominator_binned_afterCuts;
	  if(writeTo_selEventsFileOut)
	    {
	      *(outputFiles["e"]["den"]) << eventInfo.str() << '\n';
	    }
	}

      if(histograms_incl_beforeCuts_den != nullptr && histograms_incl_afterCuts_den != nullptr &&
         histograms_binned_beforeCuts_den != nullptr && histograms_binned_afterCuts_den != nullptr)
      {
	cutFlowTable_e.update("mT_fix(electron, MET) < 15 GeV (before cut)", evtWeightRecorder.get(central_or_shift));
        histograms_incl_beforeCuts_den->fillHistograms(preselElectron, met.pt(), mT, mT_fix, evtWeightRecorder.get(central_or_shift));
        fillHistograms(*histograms_binned_beforeCuts_den, preselElectron, met.pt(), mT, mT_fix, evtWeightRecorder.get(central_or_shift), &cutFlowTable_e);

        if(mT_fix < 15.)
        {
          cutFlowTable_e.update("mT_fix(electron, MET) < 15 GeV (after cut)", evtWeightRecorder.get(central_or_shift));
          histograms_incl_afterCuts_den->fillHistograms(preselElectron, met.pt(), mT, mT_fix, evtWeightRecorder.get(central_or_shift));
          fillHistograms(*histograms_binned_afterCuts_den, preselElectron, met.pt(), mT, mT_fix, evtWeightRecorder.get(central_or_shift), &cutFlowTable_e);
        }
      }
    }

    if(! isGoodLeptonJetPair)
    {
      if(run_lumi_eventSelector)
      {
        std::cout << "event " << eventInfo.str() << " FAILS as "
                     "there is no preselected lepton+jet pair in the event satisfying all requirements\n"
        ;
      }
      continue;
    }

    fillWithOverFlow(histogram_met_pt,  met.pt(),  evtWeightRecorder.get(central_or_shift));
    fillWithOverFlow(histogram_met_phi, met.phi(), evtWeightRecorder.get(central_or_shift));

    
//--- fill generator level histograms (after cuts)
    if(isMC)
    {
      genEvtHistManager_afterCuts->fillHistograms(
        genElectrons, genMuons, genHadTaus, genPhotons, genJets, evtWeightRecorder.get_inclusive(central_or_shift)
      );
      lheInfoHistManager->fillHistograms(*lheInfoReader, evtWeightRecorder.get(central_or_shift));
      if(eventWeightManager)
      {
        genEvtHistManager_afterCuts->fillHistograms(eventWeightManager, evtWeightRecorder.get_inclusive(central_or_shift));
      }
    }
    ++selectedEntries;
    selectedEntries_weighted += evtWeightRecorder.get(central_or_shift);
    histogram_selectedEntries->Fill(0.);
    if(isDEBUG)
    {
      std::cout << evtWeightRecorder << '\n';
    }
  }

  std::cout << "max num. Entries = " << inputTree -> getCumulativeMaxEventCount()
            << " (limited by " << maxEvents << ") "
               "processed in " << inputTree -> getProcessedFileCount() << " file(s) "
               "(out of "      << inputTree -> getFileCount()          << ")\n"
               " analyzed = "  << analyzedEntries                      << "\n"
               " selected = "  << selectedEntries
            << " (weighted = " << selectedEntries_weighted << ")\n\n"
               "cut-flow table for electron events\n" << cutFlowTable_e  << "\n"
               "cut-flow table for muon events\n"     << cutFlowTable_mu << '\n';


  if(isMC && isMC_TT_SL)
    {// Runs only for TTJets_SemiLeptonic
      std::cout << "Di-Lepton SS sideband Info (w MET Filter & Trigger)" << std::endl;
      std::cout << "cut-flow table for electron events\n" << cutFlowTable_e_diLeptSS  << "\n"
	"cut-flow table for muon events\n"     << cutFlowTable_mu_diLeptSS << '\n';

      std::cout << "Di-Lepton SS sideband Info (w/o Trigger)" << std::endl;
      std::cout << "cut-flow table for electron events\n" << cutFlowTable_e_diLeptSS_woTrigger << "\n"
	"cut-flow table for muon events\n"     << cutFlowTable_mu_diLeptSS_woTrigger << '\n';
    }

  if(isMC && (isMC_TT_HAD || isMC_QCD))
    {// Runs only for QCD and TTToHadronic
      std::cout << "Lepton+Jet sideband Info (w MET Filter & Trigger)" << std::endl;
      std::cout << "cut-flow table for electron events\n" << cutFlowTable_e_LeptonPlusJet  << "\n"
	"cut-flow table for muon events\n"     << cutFlowTable_mu_LeptonPlusJet << '\n';

      std::cout << "Lepton+Jet sideband Info (w/o Trigger)" << std::endl;
      std::cout << "cut-flow table for electron events\n" << cutFlowTable_e_LeptonPlusJet_woTrigger  << "\n"
	"cut-flow table for muon events\n"     << cutFlowTable_mu_LeptonPlusJet_woTrigger << '\n';
    }



//--- manually write histograms to output file
  fs.file().cd();
  //histogram_analyzedEntries->Write();
  //histogram_selectedEntries->Write();
  HistManagerBase::writeHistograms();

//--- memory clean-up
  delete muonReader;
  delete electronReader;
  delete jetReader;
  delete metReader;
  delete genmetReader;
  delete genLeptonReader;
  delete genHadTauReader;
  delete genPhotonReader;
  delete genJetReader;
  delete lheInfoReader;
  delete metFilterReader;
  delete bdt_filler_e_LeptonPlusJet;
  delete bdt_filler_mu_LeptonPlusJet;
  delete bdt_filler_e_diLeptSS;
  delete bdt_filler_mu_diLeptSS;

  delete genEvtHistManager_beforeCuts;
  delete genEvtHistManager_afterCuts;
  delete lheInfoHistManager;
  delete metFilterHistManager;
  delete l1PreFiringWeightReader;
  delete eventWeightManager;

  hltPaths_LeptonFakeRate_delete(triggers_e);
  hltPaths_LeptonFakeRate_delete(triggers_mu);

  
  delete histograms_e_numerator_incl_LeptonPlusJet; 
  delete histograms_e_denominator_incl_LeptonPlusJet; 
  delete histograms_e_numerator_incl_LeptonPlusJet_woTrigger; 
  delete histograms_e_denominator_incl_LeptonPlusJet_woTrigger; 
  delete histograms_e_numerator_incl_diLeptSS; 
  delete histograms_e_denominator_incl_diLeptSS; 
  delete histograms_e_numerator_incl_diLeptSS_woTrigger; 
  delete histograms_e_denominator_incl_diLeptSS_woTrigger; 
  delete histograms_e_numerator_incl_beforeCuts;
  delete histograms_e_denominator_incl_beforeCuts;
  delete histograms_e_numerator_incl_afterCuts;
  delete histograms_e_denominator_incl_afterCuts;
  delete histograms_mu_numerator_incl_LeptonPlusJet; 
  delete histograms_mu_denominator_incl_LeptonPlusJet; 
  delete histograms_mu_numerator_incl_LeptonPlusJet_woTrigger; 
  delete histograms_mu_denominator_incl_LeptonPlusJet_woTrigger; 
  delete histograms_mu_numerator_incl_diLeptSS; 
  delete histograms_mu_denominator_incl_diLeptSS; 
  delete histograms_mu_numerator_incl_diLeptSS_woTrigger; 
  delete histograms_mu_denominator_incl_diLeptSS_woTrigger; 
  delete histograms_mu_numerator_incl_beforeCuts;
  delete histograms_mu_denominator_incl_beforeCuts;
  delete histograms_mu_numerator_incl_afterCuts;
  delete histograms_mu_denominator_incl_afterCuts;

  for(const std::vector<numerator_and_denominatorHistManagers *> & histVector:
      {
        histograms_e_numerator_binned_LeptonPlusJet, 
        histograms_e_denominator_binned_LeptonPlusJet, 
        histograms_e_numerator_binned_LeptonPlusJet_woTrigger, 
        histograms_e_denominator_binned_LeptonPlusJet_woTrigger, 
        histograms_e_numerator_binned_diLeptSS, 
        histograms_e_denominator_binned_diLeptSS, 
        histograms_e_numerator_binned_diLeptSS_woTrigger, 
        histograms_e_denominator_binned_diLeptSS_woTrigger, 
        histograms_e_numerator_binned_beforeCuts,
        histograms_e_denominator_binned_beforeCuts,
        histograms_e_numerator_binned_afterCuts,
        histograms_e_denominator_binned_afterCuts,
        histograms_mu_numerator_binned_LeptonPlusJet, 
        histograms_mu_denominator_binned_LeptonPlusJet, 
        histograms_mu_numerator_binned_LeptonPlusJet_woTrigger, 
        histograms_mu_denominator_binned_LeptonPlusJet_woTrigger, 
        histograms_mu_numerator_binned_diLeptSS, 
        histograms_mu_denominator_binned_diLeptSS, 
        histograms_mu_numerator_binned_diLeptSS_woTrigger, 
        histograms_mu_denominator_binned_diLeptSS_woTrigger, 
        histograms_mu_numerator_binned_beforeCuts,
        histograms_mu_denominator_binned_beforeCuts,
        histograms_mu_numerator_binned_afterCuts,
        histograms_mu_denominator_binned_afterCuts
      })
  {
    for(numerator_and_denominatorHistManagers * hist: histVector)
    {
      delete hist;
    }
  }

  delete inputTree;

  for(auto & kv: outputFiles)
  {
    for(auto & kv2: kv.second)
    {
      if(kv2.second)
      {
        *kv2.second << std::flush;
        delete kv2.second;
      }
    }
  }

  delete dataToMCcorrectionInterface;
  delete dataToMCcorrectionInterface_ntuple; 
  delete run_lumi_eventSelector;

  clock.Show(argv[0]);

  return EXIT_SUCCESS;
} // main func ends
