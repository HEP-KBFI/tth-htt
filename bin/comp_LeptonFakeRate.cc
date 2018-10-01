/** \executable comp_LeptonFakeRate
 *
 * Determine probability for jets to get misidentified as hadronic tau candidates,
 * measured in tt+jets events selected by requiring the presence of two b-jets, plus an electron and muon pair of opposite charge.
 *
 * \authors Ram Krishna Dewanjee, Christian Veelken; Tallinn
 *
 */

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/PythonParameterSet/interface/MakeParameterSets.h"

#include "FWCore/Utilities/interface/Exception.h"

#include "PhysicsTools/FWLite/interface/TFileService.h"
#include "DataFormats/FWLite/interface/InputSource.h"
#include "DataFormats/FWLite/interface/OutputFiles.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h"
#include "tthAnalysis/HiggsToTauTau/interface/jetToTauFakeRateAuxFunctions.h" // getEtaBin, getPtBin
#include "tthAnalysis/HiggsToTauTau/interface/compFakeRateAuxFunctions.h" // compFakeRate

#include <TArrayD.h>
#include <TAxis.h>
#include <TBenchmark.h>
#include <TCanvas.h>
#include <TError.h> // gErrorAbortLevel, kError
#include <TFile.h>
#include <TGraphAsymmErrors.h>
#include <TH1.h>
#include <TLegend.h>
#include <TMath.h>
#include <TPaveText.h>
#include <TObjArray.h>
#include <TObjString.h>
#include <TRandom3.h>
#include <TString.h>
#include <TH2.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <assert.h>

typedef std::vector<double> vdouble;
typedef std::vector<std::string> vstring;

enum { kPrefit, kPostfit };

std::string readString(TObject* item_tobject, bool& parseError)
{
  TObjString* item_tstring = dynamic_cast<TObjString*>(item_tobject);
  assert(item_tstring);
  return item_tstring->GetString().Data();
}
double readFloat(TObject* item_tobject, bool& parseError)
{
  TObjString* item_tstring = dynamic_cast<TObjString*>(item_tobject);
  assert(item_tstring);
  if ( item_tstring->GetString().IsFloat() ) {
    return item_tstring->GetString().Atof();
  } else {
    parseError = true;
    return -1.;
  }
}

struct fitResultType
{
  fitResultType(const std::string& line)
    : norm_prefit_(-1.)
    , normErr_prefit_(-1.)
    , Conv_corr_e_(1.)     // NEWLY ADDED FOR ELECTRONS
    , Err_Conv_corr_e_(0.) // NEWLY ADDED FOR ELECTRONS
  {
    TString line_tstring(line.data());
    bool parseError = false;
    TObjArray* items = line_tstring.Tokenize(" ");
    if ( items->GetEntries() == 12 ) {
      std::string lepton_type_string = readString(items->At(0), parseError);
      if      ( lepton_type_string == "e"  ) lepton_type_ = kElectron;
      else if ( lepton_type_string == "mu" ) lepton_type_ = kMuon;
      else parseError = true;
      std::string pass_or_fail_string = readString(items->At(1), parseError);
      if      ( pass_or_fail_string == "num" ) pass_or_fail_ = kPass;
      else if ( pass_or_fail_string == "den" ) pass_or_fail_ = kFail;
      else parseError = true;
      minAbsEta_ = readFloat(items->At(4), parseError);
      maxAbsEta_ = readFloat(items->At(5), parseError);
      minPt_ = readFloat(items->At(6), parseError);
      maxPt_ = readFloat(items->At(7), parseError);      
      key_ = Form("%s_%s", getPtBin(minPt_, maxPt_).data(), getEtaBin(minAbsEta_, maxAbsEta_).data());
      norm_postfit_ = readFloat(items->At(10), parseError);
      std::string normErr_string = readString(items->At(11), parseError);
      if ( normErr_string != "nan" ) {
	normErr_postfit_ = readFloat(items->At(11), parseError);
      } else {
	normErr_postfit_ = norm_postfit_;
      }
    } else parseError = true;
    if ( parseError ) {
      throw cms::Exception("fitResultType") 
	<< "Failed to parse line = '" << line << "' !!\n";
    }
  }
  ~fitResultType() {}
  enum { kElectron, kMuon };
  int lepton_type_;
  enum { kPass, kFail }; // kPass (numerator) => Tight; kFail (denominator) => (Fakeable - Tight) in Tallinn definiton of numerator and denomintor histograms 
  int pass_or_fail_;
  double minAbsEta_;
  double maxAbsEta_;
  double minPt_;
  double maxPt_;
  std::string key_;
  double norm_prefit_;
  double normErr_prefit_;
  double norm_postfit_;
  double normErr_postfit_;
  double Conv_corr_e_;        // NEWLY ADDED FOR ELECTRONS
  double Err_Conv_corr_e_;    // NEWLY ADDED FOR ELECTRONS

  void SetConv_corr(double corr, double corr_err){ // NEWLY ADDED FOR ELECTRONS
    double default_Conv_corr_e_ = Conv_corr_e_; // set to 1.
    double default_Err_Conv_corr_e_ = Err_Conv_corr_e_; // set to 0.
    if(lepton_type_ == kElectron){
      Conv_corr_e_ = corr;
      Err_Conv_corr_e_ = corr_err; 
    }else if(lepton_type_ == kMuon){
      Conv_corr_e_ = default_Conv_corr_e_;
      Err_Conv_corr_e_ = default_Err_Conv_corr_e_; 
    }
  }

  void ApplyConv_corr(){  // NEWLY ADDED FOR ELECTRONS
    double uncorr_norm_prefit = norm_prefit_;
    double uncorr_norm_postfit = norm_postfit_;
    double uncorr_err_prefit = normErr_prefit_;
    double uncorr_err_postfit = normErr_postfit_;
    if(lepton_type_ == kElectron){
      norm_prefit_ *= Conv_corr_e_;
      normErr_prefit_ = (uncorr_err_prefit * Conv_corr_e_) + (uncorr_norm_prefit * Err_Conv_corr_e_);
      norm_postfit_ *= Conv_corr_e_;
      normErr_postfit_ = (uncorr_err_postfit * Conv_corr_e_) + (uncorr_norm_postfit * Err_Conv_corr_e_);
    }else if(lepton_type_ == kMuon){
      norm_prefit_ = uncorr_norm_prefit;
      norm_postfit_ = uncorr_norm_postfit;
      normErr_prefit_ = uncorr_err_prefit ;
      normErr_postfit_ = uncorr_err_postfit ;
    }
  }

};


void compFakeRateFromHistos(const TH1* histogram_QCD_Pass, const TH1* histogram_QCD_Fail, std::map<std::string, fitResultType*>::iterator fitResult, 
                            double avFakeRate_QCD, double avFakeRateErrUp_QCD, double avFakeRateErrDown_QCD, double avFakeRateErr_QCD)
{

  // Fake Rate computation (QCD e)                                                                                                                                                                                                          
  double nPass_QCD = compIntegral(histogram_QCD_Pass, true, true);
  double nPassErr_QCD = compIntegralErr(histogram_QCD_Pass, true, true);
  double nFail_QCD = compIntegral(histogram_QCD_Fail, true, true);
  double nFailErr_QCD = compIntegralErr(histogram_QCD_Fail, true, true);
  bool errorFlag;

  compFakeRate(nPass_QCD, nPassErr_QCD, nFail_QCD, nFailErr_QCD, avFakeRate_QCD, avFakeRateErrUp_QCD, avFakeRateErrDown_QCD, errorFlag);

  if ( !errorFlag) {
    avFakeRateErr_QCD = TMath::Sqrt(0.5*(avFakeRateErrUp_QCD*avFakeRateErrUp_QCD + avFakeRateErrDown_QCD*avFakeRateErrDown_QCD));                                                                                 
  } else {
    throw cms::Exception("compFakeRateFromHistos")
      << "Failed to compute fake rate for " << fitResult->second->minPt_ << " < pT < " << fitResult->second->maxPt_ << " && " << fitResult->second->minAbsEta_ << " < abs(eta) < " << fitResult->second->maxAbsEta_
      << " (nPass = " << nPass_QCD << " +/- " << nPassErr_QCD<< ", nFail = " << nFail_QCD << " +/- " << nFailErr_QCD << ") !!\n";
  }


}



void readConversionCorr(TFile* inputFile, std::map<std::string, fitResultType*>& fitResults, const std::string& process, const std::string& variable, const double& conv_unc ){

  // std::string histogramName_QCD_num_e = "LeptonFakeRate/numerator/electrons/tight";    
  // std::string histogramName_QCD_den_e = "LeptonFakeRate/numerator/electrons/fakeable"; // QCD (fakeable - tight)

  std::string histogramName_QCD_num_el = "";
  std::string histogramName_QCD_den_el = "";
  std::string histogramName_QCD_num_g_el = "";
  std::string histogramName_QCD_den_g_el = "";


  for ( std::map<std::string, fitResultType*>::iterator fitResult = fitResults.begin();
        fitResult != fitResults.end(); ++fitResult ) {
        std::cout << "pT: min = " << fitResult->second->minPt_ << ", max = " << fitResult->second->maxPt_ << std::endl;
        std::cout << "abs(eta): min = " << fitResult->second->minAbsEta_ << ", max = " << fitResult->second->maxAbsEta_ << std::endl;


	if( fitResult->second->lepton_type_ == fitResultType::kMuon){ // SINCE VALID ONLY FOR ELECTRONS                                                                                                               
	  std::cout << "Skipping since muon" << std::endl;
	  continue; 
	}

        if((fitResult->second->minPt_ == -1.) && (fitResult->second->maxPt_ == -1.) && (fitResult->second->minAbsEta_ == -1.) && (fitResult->second->maxAbsEta_ == -1.)){ // INCLUSIVE
	  histogramName_QCD_num_el = Form("LeptonFakeRate/numerator/electrons_tight/incl/%s/%s", process.data(), variable.data()); // QCD tight
	  histogramName_QCD_den_el = Form("LeptonFakeRate/denominator/electrons_fakeable/incl/%s/%s", process.data(), variable.data()); // QCD (fakeable - tight)
	  histogramName_QCD_num_g_el = Form("LeptonFakeRate/numerator/electrons_tight/incl/%s%s/%s", process.data(), "g", variable.data()); // QCD tight (gen photon matched)
	  histogramName_QCD_den_g_el = Form("LeptonFakeRate/denominator/electrons_fakeable/incl/%s%s/%s", process.data(), "g", variable.data()); // QCD (fakeable - tight) (gen photon matched)
	}else{ // PT AND ETA BINNED
 	  histogramName_QCD_num_el = Form("LeptonFakeRate/numerator/electrons_tight/%s/%s/%s/%s", (getEtaBin(fitResult->second->minAbsEta_, fitResult->second->maxAbsEta_)).data(),
						   (getPtBin(fitResult->second->minPt_, fitResult->second->maxPt_)).data(), process.data(), variable.data()); // QCD tight
	  histogramName_QCD_den_el = Form("LeptonFakeRate/denominator/electrons_fakeable/%s/%s/%s/%s", (getEtaBin(fitResult->second->minAbsEta_, fitResult->second->maxAbsEta_)).data(),
						   (getPtBin(fitResult->second->minPt_, fitResult->second->maxPt_)).data(), process.data(), variable.data()); // QCD (fakeable - tight)
 	  histogramName_QCD_num_g_el = Form("LeptonFakeRate/numerator/electrons_tight/%s/%s/%s%s/%s", (getEtaBin(fitResult->second->minAbsEta_, fitResult->second->maxAbsEta_)).data(),
						   (getPtBin(fitResult->second->minPt_, fitResult->second->maxPt_)).data(), process.data(), "g", variable.data()); // QCD tight (gen photon matched)
	  histogramName_QCD_den_g_el = Form("LeptonFakeRate/denominator/electrons_fakeable/%s/%s/%s%s/%s", (getEtaBin(fitResult->second->minAbsEta_, fitResult->second->maxAbsEta_)).data(),
						   (getPtBin(fitResult->second->minPt_, fitResult->second->maxPt_)).data(), process.data(), "g", variable.data()); // QCD (fakeable - tight) (gen photon matched)
	}



	TH1* histogram_QCD_num_el = dynamic_cast<TH1*>(inputFile->Get(histogramName_QCD_num_el.data())); // QCD e num [= Pass]
	TH1* histogram_QCD_den_el = dynamic_cast<TH1*>(inputFile->Get(histogramName_QCD_den_el.data())); // QCD e den [= (Fail - Pass)]
	TH1* histogram_QCD_num_g_el = dynamic_cast<TH1*>(inputFile->Get(histogramName_QCD_num_g_el.data())); // QCD Converted e num [= Pass_Converted]
	TH1* histogram_QCD_den_g_el = dynamic_cast<TH1*>(inputFile->Get(histogramName_QCD_den_g_el.data())); // QCD Converted e den [= (Fail_Converted - Pass_Converted)]
        TH1* histogram_QCD_num_el_NC = subtractHistograms("histogram_QCD_num_el_NC", histogram_QCD_num_el, histogram_QCD_num_g_el, 1); // QCD Non Converted e num [= Pass_NonConverted]
        TH1* histogram_QCD_den_el_NC = subtractHistograms("histogram_QCD_den_el_NC", histogram_QCD_den_el, histogram_QCD_den_g_el, 1); // QCD Non Converted e den [= (Fail_NonConverted - Pass_NonConverted)]

        
	TH1* histogram_QCD_Pass = histogram_QCD_num_el; // QCD e Pass 
        TH1* histogram_QCD_Pass_twice = addHistograms("histogram_QCD_Pass_twice", histogram_QCD_Pass, histogram_QCD_Pass, 1); // 2 x (QCD e Pass)
	TH1* histogram_QCD_Fail = addHistograms("histogram_QCD_Fail", histogram_QCD_den_el, histogram_QCD_Pass_twice, 1); // QCD e Fail


	TH1* histogram_QCD_Pass_NC = histogram_QCD_num_el_NC; // QCD Non Converted e Pass 
        TH1* histogram_QCD_Pass_NC_twice = addHistograms("histogram_QCD_Pass_NC_twice", histogram_QCD_Pass_NC, histogram_QCD_Pass_NC, 1); // 2 x (QCD Non Converted e Pass) 
	TH1* histogram_QCD_Fail_NC = addHistograms("histogram_QCD_Fakeable", histogram_QCD_den_el_NC, histogram_QCD_Pass_NC_twice, 1); // QCD Non Converted e Fail

        // Fake Rate computation (QCD e)
	double avFakeRate_QCD = 0.;
        double avFakeRateErrUp_QCD = 0.;
        double avFakeRateErrDown_QCD = 0.;
        double avFakeRateErr_QCD = 0.;
        compFakeRateFromHistos(histogram_QCD_Pass, histogram_QCD_Fail, fitResult, avFakeRate_QCD, avFakeRateErrUp_QCD, avFakeRateErrDown_QCD, avFakeRateErr_QCD);

        // Fake Rate computation (QCD Non Converted e)
	double avFakeRate_QCD_NC = 0.;
        double avFakeRateErrUp_QCD_NC = 0.;
        double avFakeRateErrDown_QCD_NC = 0.;
        double avFakeRateErr_QCD_NC = 0.;
        compFakeRateFromHistos(histogram_QCD_Pass_NC, histogram_QCD_Fail_NC, fitResult, avFakeRate_QCD_NC, avFakeRateErrUp_QCD_NC, avFakeRateErrDown_QCD_NC, avFakeRateErr_QCD_NC);


        double FR_Conv_Corr = 1.;
	double Err_FR_Conv_Corr = 0.;
        if(avFakeRate_QCD != 0.){
	  FR_Conv_Corr = avFakeRate_QCD_NC/avFakeRate_QCD; // central value computed here
          Err_FR_Conv_Corr = TMath::Abs( ((avFakeRate_QCD * avFakeRateErr_QCD_NC) - (avFakeRate_QCD_NC * avFakeRateErr_QCD))/(TMath::Power(avFakeRate_QCD, 2.0)) );
	}
	std::cout << " FR_Conv_Corr " << FR_Conv_Corr << " +/- " << Err_FR_Conv_Corr << std::endl;
        fitResult->second->SetConv_corr(FR_Conv_Corr, Err_FR_Conv_Corr);   




	/*
        double FakeRate_QCD_NC_num = ( histogram_QCD_num_el->Integral() - histogram_QCD_num_g_el->Integral() );     // = pass (QCD Conv. Rejected)
        double FakeRate_QCD_NC_den = ( histogram_QCD_num_el->Integral() + histogram_QCD_den_el->Integral()) 
	                               - (histogram_QCD_num_g_el->Integral() + histogram_QCD_den_g_el->Integral()) 
	                               + (histogram_QCD_num_el->Integral() - histogram_QCD_num_g_el->Integral()); // = pass + fail (QCD Conv. Rejected)
        double FakeRate_QCD_NC = 0.; 
        if(FakeRate_QCD_NC_den != 0.){ 
	  FakeRate_QCD_NC = FakeRate_QCD_NC_num/FakeRate_QCD_NC_den;
	}else{
          FakeRate_QCD_NC = 1.0;
	}  

	double FakeRate_QCD_num = histogram_QCD_num_el->Integral(); // pass (QCD all)  
	double FakeRate_QCD_den = histogram_QCD_den_el->Integral() + (2 * histogram_QCD_num_el->Integral()); // pass + fail (QCD all)
        double FakeRate_QCD     = 0.; 
	if(FakeRate_QCD_den != 0.){ 
	  FakeRate_QCD = FakeRate_QCD_num/FakeRate_QCD_den;
	}else{
          FakeRate_QCD = 1.0;
	}  
	std::cout << " FakeRate_QCD " << FakeRate_QCD << std::endl;

        double FR_Conv_Corr = 1.;
        if(FakeRate_QCD != 0.){
	  FR_Conv_Corr = FakeRate_QCD_NC/FakeRate_QCD; // central value computed here
	}
	std::cout << " FR_Conv_Corr " << FR_Conv_Corr << std::endl;

	std::cout<< " histogram_QCD_num_el->Integral() " << histogram_QCD_num_el->Integral() << " histogram_QCD_den_el->Integral() " << histogram_QCD_den_el->Integral() << std::endl;
 
        // ERROR PROP. ON FAKE RATE CORR.
        assert( ((histogram_QCD_num_el->Integral() != 0.) && (histogram_QCD_den_el->Integral() != 0.)) );

        double alpha_pass = histogram_QCD_num_g_el->Integral()/histogram_QCD_num_el->Integral();
        double alpha_fail = histogram_QCD_den_g_el->Integral()/histogram_QCD_den_el->Integral();
        double del_A = (conv_unc*((2*histogram_QCD_num_el->Integral()) + histogram_QCD_den_el->Integral()) ) + ((1. - alpha_pass) * ((2*compIntegralErr(histogram_QCD_num_el, true,true)) + compIntegralErr(histogram_QCD_den_el, true,true)));
        double B = (2*histogram_QCD_num_el->Integral()*(1. - alpha_pass)) + (histogram_QCD_den_el->Integral()*(1.- alpha_fail));
        double del_B = ((2*compIntegralErr(histogram_QCD_num_el, true,true)*(1. - alpha_pass)) + ((2*histogram_QCD_num_el->Integral())*conv_unc)) 
	               + ( (compIntegralErr(histogram_QCD_den_el, true,true)*(1. - alpha_fail)) + (histogram_QCD_den_el->Integral()*conv_unc));
	double Err_FR_Conv_Corr = 0.;
        if(B != 0.) Err_FR_Conv_Corr = (del_A + (FR_Conv_Corr * del_B))/B;

        fitResult->second->SetConv_corr(FR_Conv_Corr, Err_FR_Conv_Corr); 
	// fitResult->second->ApplyConv_corr(); // NOT NEEDED
	*/


  }
}



void readPrefit(TFile* inputFile, std::map<std::string, fitResultType*>& fitResults, const std::string& variable_den)
{
  for ( std::map<std::string, fitResultType*>::iterator fitResult = fitResults.begin();
	fitResult != fitResults.end(); ++fitResult ) {
    std::cout << "pT: min = " << fitResult->second->minPt_ << ", max = " << fitResult->second->maxPt_ << std::endl;
    std::cout << "abs(eta): min = " << fitResult->second->minAbsEta_ << ", max = " << fitResult->second->maxAbsEta_ << std::endl;
    // CV: skip inclusive pT and abs(eta) selection
    if ( fitResult->second->minPt_ == -1. && fitResult->second->maxPt_ == -1. ) continue;
    if ( fitResult->second->minAbsEta_ == -1. && fitResult->second->maxAbsEta_ == -1. ) continue;
    std::string histogramName = "LeptonFakeRate";
    histogramName.append("/");
    if      ( fitResult->second->pass_or_fail_ == fitResultType::kPass ) histogramName.append("numerator");
    else if ( fitResult->second->pass_or_fail_ == fitResultType::kFail ) histogramName.append("denominator"); 
    else assert(0);
    histogramName.append("/");
    if      ( fitResult->second->lepton_type_ == fitResultType::kElectron ) histogramName.append("electrons");
    else if ( fitResult->second->lepton_type_ == fitResultType::kMuon     ) histogramName.append("muons"); 
    else assert(0);
    histogramName.append("_");
    if      ( fitResult->second->pass_or_fail_ == fitResultType::kPass ) histogramName.append("tight");
    else if ( fitResult->second->pass_or_fail_ == fitResultType::kFail ) histogramName.append("fakeable"); 
    else assert(0);
    histogramName.append("/");
    histogramName.append(getEtaBin(fitResult->second->minAbsEta_, fitResult->second->maxAbsEta_));
    histogramName.append("/");
    histogramName.append(getPtBin(fitResult->second->minPt_, fitResult->second->maxPt_));
    histogramName.append("/");
    histogramName.append("fakes_mc"); // old line in def code
    // histogramName.append("fakes_data");
    histogramName.append("/");
    // histogramName.append("EventCounter"); // DEF LINE
    // histogramName.append("mT_fix_L_den");
    histogramName.append(variable_den);
    std::cout << "loading histogram = '" << histogramName << "'" << std::endl;
    TH1* histogram = dynamic_cast<TH1*>(inputFile->Get(histogramName.data()));
    if ( !histogram ) throw cms::Exception("fillHistogram") 
      << "Failed to load histogram = '" << histogramName << "' from file = '" << inputFile->GetName() << "' !!\n";
    double integral = 0.;
    double integralErr2 = 0.;
    int numBins = histogram->GetNbinsX();
    for ( int idxBin = 0; idxBin <= (numBins + 1); ++idxBin ) { // CV: include underflow and overflow bins
      double binContent = histogram->GetBinContent(idxBin);
      double binError = histogram->GetBinError(idxBin);
      integral += binContent;
      integralErr2 += (binError*binError);
    }
    double integralErr = TMath::Sqrt(integralErr2);
    fitResult->second->norm_prefit_ = integral;
    fitResult->second->normErr_prefit_ = integralErr;
  }
}

TH2* bookHistogram(fwlite::TFileService& fs, const std::string& histogramName, const TArrayD& ptBins, const TArrayD& absEtaBins)
{
  int numBinsX = ptBins.GetSize() - 1;
  int numBinsY = absEtaBins.GetSize() - 1;
  TH2* histogram = fs.make<TH2D>(histogramName.data(), histogramName.data(), numBinsX, ptBins.GetArray(), numBinsY, absEtaBins.GetArray());
  return histogram;
}   

void fillHistogram(TH2* histogram, const std::map<std::string, fitResultType*>& fitResults_pass, const std::map<std::string, fitResultType*>& fitResults_fail, int prefit_or_postfit)
{
  const TAxis* xAxis = histogram->GetXaxis();
  const TAxis* yAxis = histogram->GetYaxis();
  for ( int idxBinX = 1; idxBinX <= xAxis->GetNbins(); ++idxBinX ) {
    double minPt = xAxis->GetBinLowEdge(idxBinX);
    double maxPt = xAxis->GetBinUpEdge(idxBinX);
    for ( int idxBinY = 1; idxBinY <= yAxis->GetNbins(); ++idxBinY ) {
      double minAbsEta = yAxis->GetBinLowEdge(idxBinY);
      double maxAbsEta = yAxis->GetBinUpEdge(idxBinY);
      
      std::string key = Form("%s_%s", getPtBin(minPt, maxPt).data(), getEtaBin(minAbsEta, maxAbsEta).data());
      std::map<std::string, fitResultType*>::const_iterator fitResult_pass = fitResults_pass.find(key);
      std::map<std::string, fitResultType*>::const_iterator fitResult_fail = fitResults_fail.find(key);
      if ( fitResult_pass != fitResults_pass.end() && fitResult_fail != fitResults_fail.end() ) {
	double nPass, nPassErr, nFail, nFailErr;
	if ( prefit_or_postfit == kPrefit ) { // APPLY CONV.CORR FOR ELECTRONS CASE TO BOTH PRE AND POSTFIT
	  nPass = fitResult_pass->second->norm_prefit_;
	  nPassErr = fitResult_pass->second->normErr_prefit_;
	  nFail = fitResult_fail->second->norm_prefit_;
	  nFailErr = fitResult_fail->second->normErr_prefit_;
	} else if ( prefit_or_postfit == kPostfit ) {
	  nPass = fitResult_pass->second->norm_postfit_;
	  nPassErr = fitResult_pass->second->normErr_postfit_;
	  nFail = fitResult_fail->second->norm_postfit_;
	  nFailErr = fitResult_fail->second->normErr_postfit_;
	} else assert(0);
	double avFakeRate, avFakeRateErrUp, avFakeRateErrDown;
	bool errorFlag;
	compFakeRate(nPass, nPassErr, nFail, nFailErr, avFakeRate, avFakeRateErrUp, avFakeRateErrDown, errorFlag);

        if(fitResult_pass->second->lepton_type_ == fitResultType::kElectron ){
          avFakeRate *= fitResult_pass->second->Conv_corr_e_ ; // apply the correction 
          double def_avFakeRateErrUp = avFakeRateErrUp;  
	  double def_avFakeRateErrDown = avFakeRateErrDown;   
          avFakeRateErrUp = TMath::Sqrt(TMath::Power(def_avFakeRateErrUp, 2.0) + TMath::Power((fitResult_pass->second->Err_Conv_corr_e_), 2.0));
          avFakeRateErrDown = TMath::Sqrt(TMath::Power(def_avFakeRateErrDown, 2.0) + TMath::Power((fitResult_pass->second->Err_Conv_corr_e_), 2.0));
	}
        

	if ( !errorFlag ) {
	  double avFakeRateErr = TMath::Sqrt(0.5*(avFakeRateErrUp*avFakeRateErrUp + avFakeRateErrDown*avFakeRateErrDown));
	  histogram->SetBinContent(idxBinX, idxBinY, avFakeRate);  // 2D HISTOGRAM FILED HERE
	  histogram->SetBinError(idxBinX, idxBinY, avFakeRateErr); // 2D HISTOGRAM FILED HERE
	} else {
	  throw cms::Exception("fillHistogram") 
	    << "Failed to compute fake rate for " << minPt << " < pT < " << maxPt << " && " << minAbsEta << " < abs(eta) < " << maxAbsEta 
	    << " (nPass = " << nPass << " +/- " << nPassErr << ", nFail = " << nFail << " +/- " << nFailErr << ") !!\n";
	}
      } else {
	throw cms::Exception("fillHistogram") 
	  << "Failed to find fitResult for " << minPt << " < pT < " << maxPt << " && " << minAbsEta << " < abs(eta) < " << maxAbsEta << " !!\n";
      }
    }
  }
}

TGraphAsymmErrors* bookGraph(fwlite::TFileService& fs, const std::string& graphName, const TArrayD& ptBins)
{
  int numPoints = ptBins.GetSize() - 1;
  assert(numPoints >= 1);
  TGraphAsymmErrors* graph = new TGraphAsymmErrors(numPoints);
  return graph;
}

void fillGraph(TGraphAsymmErrors* graph, TH2* histogram, double absEta)
{
  const TAxis* xAxis = histogram->GetXaxis();
  int numPoints = xAxis->GetNbins();
  const TAxis* yAxis = histogram->GetYaxis();
  int idxBinY = yAxis->FindBin(absEta);
  if ( !(idxBinY >= 1 && idxBinY <= yAxis->GetNbins()) ) {
    throw cms::Exception("fillGraph") 
      << "Failed to find fitResult for abs(eta) = " << absEta << " !!\n";
  }
  for ( int idxBinX = 1; idxBinX <= xAxis->GetNbins(); ++idxBinX ) {
    double minPt = xAxis->GetBinLowEdge(idxBinX);
    double maxPt = xAxis->GetBinUpEdge(idxBinX);
    if ( maxPt > 100. ) maxPt = 100.;
    double pt = 0.5*(minPt + maxPt);
    
    double binContent = histogram->GetBinContent(idxBinX, idxBinY);
    double binError = histogram->GetBinError(idxBinX, idxBinY);
    
    int idxPoint = idxBinX - 1;
    assert(idxPoint >= 0 && idxPoint < numPoints);
    graph->SetPoint(idxPoint, pt, binContent);
    graph->SetPointError(idxPoint, pt - minPt, maxPt - pt, binError, binError);
  }
}

void makeControlPlot(TGraphAsymmErrors* graph_data, TGraphAsymmErrors* graph_mc, const TArrayD& ptBins, double minAbsEta, double maxAbsEta, bool useLogScale, const std::string& outputFileName)
{
  TCanvas* canvas = new TCanvas("canvas", "canvas", 1200, 900);
  canvas->SetFillColor(10);
  canvas->SetBorderSize(2);
  canvas->SetTopMargin(0.04);
  canvas->SetLeftMargin(0.19);
  canvas->SetBottomMargin(0.17);
  canvas->SetRightMargin(0.04);
  canvas->SetGridx();
  canvas->SetGridy();
  canvas->SetLogy(useLogScale);
  
  //TH1* dummyHistogram = new TH1D("dummyHistogram", "dummyHistogram", ptBins.GetSize() - 1, ptBins.GetArray());
  TH1* dummyHistogram = new TH1D("dummyHistogram", "dummyHistogram", 10, 0., 100.);
  dummyHistogram->SetTitle("");
  dummyHistogram->SetStats(false);
  double yMin, yMax;
  if ( useLogScale ) {
    yMin = 1.e-3;
    yMax = 1.e+1;
  } else {
    yMin = 0.;
    yMax = 0.20;
  }
  dummyHistogram->SetMinimum(yMin);
  dummyHistogram->SetMaximum(yMax);
  
  TAxis* xAxis = dummyHistogram->GetXaxis();
  xAxis->SetTitle("p_{T} [GeV]");
  xAxis->SetTitleOffset(1.3);
  xAxis->SetTitleSize(0.06);
  xAxis->SetLabelOffset(0.02);
  xAxis->SetLabelSize(0.06);
  xAxis->SetTickLength(0.04);
  xAxis->SetNdivisions(505);
  
  TAxis* yAxis = dummyHistogram->GetYaxis();
  yAxis->SetTitle("Fake rate");
  yAxis->SetTitleOffset(1.60);
  yAxis->SetTitleSize(0.06);
  yAxis->SetLabelOffset(0.02);
  yAxis->SetLabelSize(0.06);
  yAxis->SetTickLength(0.04);
  yAxis->SetNdivisions(505);
  
  dummyHistogram->Draw("axis");

  graph_data->SetMarkerStyle(20);
  graph_data->SetMarkerSize(2);
  graph_data->SetMarkerColor(1);
  graph_data->SetLineStyle(1);
  graph_data->SetLineWidth(1);
  graph_data->SetLineColor(1);  
  graph_data->Draw("psame");

  if ( graph_mc ) {
    graph_mc->SetMarkerStyle(24);
    graph_mc->SetMarkerSize(2);
    graph_mc->SetMarkerColor(1);
    graph_mc->SetLineStyle(1);
    graph_mc->SetLineWidth(1);
    graph_mc->SetLineColor(1);  
    graph_mc->Draw("psame");
  }

  TLegend* legend = 0;
  if ( graph_mc ) {
    legend = new TLegend(0.73, 0.76, 0.88, 0.91, NULL, "brNDC");
    legend->SetFillStyle(0);
    legend->SetBorderSize(0);
    legend->SetFillColor(10);
    legend->SetTextFont(42);
    legend->SetTextSize(0.050);
    legend->SetMargin(0.24);
    if ( graph_data ) legend->AddEntry(graph_data, "Data",       "p");
    if ( graph_mc   ) legend->AddEntry(graph_mc,   "Simulation", "p");
    legend->Draw();
  }

  TPaveText* label = 0;
  std::string label_text;
  if      ( minAbsEta > 0. && maxAbsEta < 5. ) label_text = Form("%1.1f < |#eta| < %1.1f", minAbsEta, maxAbsEta);
  else if ( minAbsEta > 0.                   ) label_text = Form("|#eta| > %1.1f", minAbsEta);
  else if (                   maxAbsEta < 5. ) label_text = Form("|#eta| < %1.1f", maxAbsEta);
  if ( label_text != "" ) {
    label = new TPaveText(0.23, 0.83, 0.33, 0.88, "brNDC");
    label->AddText(label_text.data());
    label->SetFillColor(10);
    label->SetBorderSize(0);
    label->SetTextColor(1);
    label->SetTextAlign(22);
    label->SetTextSize(0.050);
    label->Draw();
  }

  canvas->Update();
  size_t idx = outputFileName.find_last_of('.');
  std::string outputFileName_plot = std::string(outputFileName, 0, idx);
  if ( useLogScale ) outputFileName_plot.append("_log");
  else outputFileName_plot.append("_linear");
  if ( idx != std::string::npos ) canvas->Print(std::string(outputFileName_plot).append(std::string(outputFileName, idx)).data());
  canvas->Print(std::string(outputFileName_plot).append(".png").data());
  canvas->Print(std::string(outputFileName_plot).append(".pdf").data());
  canvas->Print(std::string(outputFileName_plot).append(".root").data());
  
  delete dummyHistogram;
  delete legend;
  delete label;
  delete canvas;
}

int main(int argc, char* argv[]) 
{
//--- throw an exception in case ROOT encounters an error
  gErrorAbortLevel = kError;

//--- parse command-line arguments
  if ( argc < 2 ) {
    std::cout << "Usage: " << argv[0] << " [parameters.py]" << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << "<comp_LeptonFakeRate>:" << std::endl;

//--- keep track of time it takes the macro to execute
  TBenchmark clock;
  clock.Start("comp_LeptonFakeRate");

//--- read python configuration parameters
  if ( !edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process") ) 
    throw cms::Exception("comp_LeptonFakeRate") 
      << "No ParameterSet 'process' found in configuration file = " << argv[1] << " !!\n";

  edm::ParameterSet cfg = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");

  edm::ParameterSet cfg_comp = cfg.getParameter<edm::ParameterSet>("comp_LeptonFakeRate");

  std::string histogramName_e = cfg_comp.getParameter<std::string>("histogramName_e");
  vdouble absEtaBins_e = cfg_comp.getParameter<vdouble>("absEtaBins_e");
  if ( absEtaBins_e.size() < 2 ) throw cms::Exception("comp_LeptonFakeRate") 
    << "Invalid Configuration parameter 'absEtaBins_e' !!\n";
  TArrayD absEtaBins_e_array = convertToTArrayD(absEtaBins_e);
  vdouble ptBins_e = cfg_comp.getParameter<vdouble>("ptBins_e");
  if ( ptBins_e.size() < 2 ) throw cms::Exception("comp_LeptonFakeRate") 
    << "Invalid Configuration parameter 'ptBins_e' !!\n";
  TArrayD ptBins_e_array = convertToTArrayD(ptBins_e);
  //if ( ptBins_e_array[ptBins_e_array.GetSize() - 1] > 100. ) ptBins_e_array[ptBins_e_array.GetSize() - 1] = 100.;
  
  std::string histogramName_mu = cfg_comp.getParameter<std::string>("histogramName_mu");
  vdouble absEtaBins_mu = cfg_comp.getParameter<vdouble>("absEtaBins_mu");
  if ( absEtaBins_mu.size() < 2 ) throw cms::Exception("comp_LeptonFakeRate") 
    << "Invalid Configuration parameter 'absEtaBins_mu' !!\n";
  TArrayD absEtaBins_mu_array = convertToTArrayD(absEtaBins_mu);
  vdouble ptBins_mu = cfg_comp.getParameter<vdouble>("ptBins_mu");
  if ( ptBins_mu.size() < 2 ) throw cms::Exception("comp_LeptonFakeRate") 
    << "Invalid Configuration parameter 'ptBins_mu' !!\n";
  TArrayD ptBins_mu_array = convertToTArrayD(ptBins_mu);
  //if ( ptBins_mu_array[ptBins_mu_array.GetSize() - 1] > 100. ) ptBins_mu_array[ptBins_mu_array.GetSize() - 1] = 100.;
  
  std::string outputFileName = cfg_comp.getParameter<std::string>("outputFileName"); // for control plots


  std::string process = cfg_comp.getParameter<std::string>("processName"); // ADDED FOR CONV. CORR.S
  std::string variable = cfg_comp.getParameter<std::string>("HistogramName_num");   // ADDED FOR CONV. CORR.S
  std::string variable_den = cfg_comp.getParameter<std::string>("HistogramName_den");
  double conv_unc = cfg_comp.getParameter<double>("Conversion_uncert");    // ADDED FOR CONV. CORR.S


  // process, variable, conv_unc

  /*
  bool use_fakes_from_MC = cfg_comp.getParameter<bool>("use_fakes_from_MC"); // handle for switching to MC based QCD computation
  if(use_fakes_from_MC){
    std::cout<< "Using Fakes from MC expectation " << std::endl;
  }else{
    std::cout<< "Using Fakes from data driven methods " << std::endl;
  } 
  */

  fwlite::InputSource inputFiles(cfg); 
  if ( !(inputFiles.files().size() == 2) )
    throw cms::Exception("comp_LeptonFakeRate") 
      << "Exactly two input files expected !!\n";
  vstring inputFileNames = inputFiles.files();
  std::string inputFileName_data;
  std::string inputFileName_mc;
  for ( vstring::const_iterator inputFileName = inputFileNames.begin();
	inputFileName != inputFileNames.end(); ++inputFileName ) {
    if      ( inputFileName->find(".txt")  != std::string::npos ) inputFileName_data = (*inputFileName);
    else if ( inputFileName->find(".root") != std::string::npos ) inputFileName_mc   = (*inputFileName);
  }
  if ( !(inputFileName_data != "" && inputFileName_mc != "") ) {
    throw cms::Exception("comp_LeptonFakeRate") 
      << "Invalid Configuration parameter 'fwliteInput.fileNames' !!\n";
  }
  
  std::map<std::string, fitResultType*> fitResults_e_pass;  // key = pT and eta bin
  std::map<std::string, fitResultType*> fitResults_e_fail;  // key = pT and eta bin
  std::map<std::string, fitResultType*> fitResults_mu_pass; // key = pT and eta bin
  std::map<std::string, fitResultType*> fitResults_mu_fail; // key = pT and eta bin

  // read fake-rates measured in data
  std::cout << "opening inputFile = '" << inputFileName_data << "'" << std::endl;
  std::ifstream* inputFile_data = new std::ifstream(inputFileName_data);
  if ( inputFile_data->is_open() ) {
    std::string line;
    while ( getline(*inputFile_data, line) ) {
      std::cout << "reading line = '" << line << "'" << std::endl;
      fitResultType* fitResult = new fitResultType(line);
      if        ( fitResult->lepton_type_ == fitResultType::kElectron && fitResult->pass_or_fail_ == fitResultType::kPass ) {
	fitResults_e_pass[fitResult->key_]  = fitResult;
      } else if ( fitResult->lepton_type_ == fitResultType::kElectron && fitResult->pass_or_fail_ == fitResultType::kFail ) {
	fitResults_e_fail[fitResult->key_]  = fitResult;
      } else if ( fitResult->lepton_type_ == fitResultType::kMuon     && fitResult->pass_or_fail_ == fitResultType::kPass ) {
	fitResults_mu_pass[fitResult->key_] = fitResult;
      } else if ( fitResult->lepton_type_ == fitResultType::kMuon     && fitResult->pass_or_fail_ == fitResultType::kFail ) {
	fitResults_mu_fail[fitResult->key_] = fitResult;
      } else assert(0);
    }
  } else throw cms::Exception("comp_LeptonFakeRate") 
      << "Failed to open input file = '" << inputFileName_data << "' !!\n";
  std::cout << "closing inputFile = '" << inputFileName_data << "'" << std::endl;
  delete inputFile_data;

  // read fake-rates expected from MC simulation
  std::cout << "opening inputFile = '" << inputFileName_mc << "'" << std::endl;
  TFile* inputFile_mc = new TFile(inputFileName_mc.data());
  if ( !inputFile_mc ) throw cms::Exception("comp_LeptonFakeRate") 
    << "Failed to open input file = '" << inputFileName_mc << "' !!\n";
  readPrefit(inputFile_mc, fitResults_e_pass, variable_den);
  readPrefit(inputFile_mc, fitResults_e_fail, variable_den);
  readPrefit(inputFile_mc, fitResults_mu_pass, variable_den);
  readPrefit(inputFile_mc, fitResults_mu_fail, variable_den);


  readConversionCorr(inputFile_mc, fitResults_e_pass, process, variable, conv_unc); // ADDED FOR ELECTRON CONV. CORRECTIONS

  std::cout << "closing inputFile = '" << inputFileName_mc << "'" << std::endl;
  delete inputFile_mc;
  
  fwlite::OutputFiles outputFile(cfg);
  fwlite::TFileService fs = fwlite::TFileService(outputFile.file().data());

  TH2* histogram_e_data = bookHistogram(fs, histogramName_e, ptBins_e_array, absEtaBins_e_array);
  fillHistogram(histogram_e_data, fitResults_e_pass, fitResults_e_fail, kPostfit);
  TH2* histogram_e_mc = bookHistogram(fs, Form("%s_prefit", histogramName_e.data()), ptBins_e_array, absEtaBins_e_array);
  fillHistogram(histogram_e_mc, fitResults_e_pass, fitResults_e_fail, kPrefit);
  TAxis* yAxis_e = histogram_e_data->GetYaxis();
  for ( int idxBinY = 1; idxBinY <= yAxis_e->GetNbins(); ++idxBinY ) {
    double minAbsEta = yAxis_e->GetBinLowEdge(idxBinY);
    double maxAbsEta = yAxis_e->GetBinUpEdge(idxBinY);
    double absEta = 0.5*(minAbsEta + maxAbsEta);
    std::string graphName_data = TString(Form("graph_e_absEta%1.2fto%1.2f_data", minAbsEta, maxAbsEta)).ReplaceAll(".", "_").Data();
    TGraphAsymmErrors* graph_data = bookGraph(fs, graphName_data, ptBins_e_array);
    fillGraph(graph_data, histogram_e_data, absEta);
    std::string graphName_mc = TString(Form("graph_e_absEta%1.2fto%1.2f_mc", minAbsEta, maxAbsEta)).ReplaceAll(".", "_").Data();
    TGraphAsymmErrors* graph_mc = bookGraph(fs, graphName_mc, ptBins_e_array);
    fillGraph(graph_mc, histogram_e_mc, absEta);
    std::string outputFileName_plot = std::string(outputFileName, 0, outputFileName.find_last_of('.'));
    outputFileName_plot.append(Form("_e_%s.png", getEtaBin(minAbsEta, maxAbsEta).data()));
    makeControlPlot(graph_data, graph_mc, ptBins_e_array, minAbsEta, maxAbsEta, true, outputFileName_plot);
    makeControlPlot(graph_data, graph_mc, ptBins_e_array, minAbsEta, maxAbsEta, false, outputFileName_plot);
  }

  TH2* histogram_mu_data = bookHistogram(fs, histogramName_mu, ptBins_mu_array, absEtaBins_mu_array);
  fillHistogram(histogram_mu_data, fitResults_mu_pass, fitResults_mu_fail, kPostfit);
  TH2* histogram_mu_mc = bookHistogram(fs, Form("%s_prefit", histogramName_mu.data()), ptBins_mu_array, absEtaBins_mu_array);
  fillHistogram(histogram_mu_mc, fitResults_mu_pass, fitResults_mu_fail, kPrefit);
  TAxis* yAxis_mu = histogram_mu_data->GetYaxis();
  for ( int idxBinY = 1; idxBinY <= yAxis_mu->GetNbins(); ++idxBinY ) {
    double minAbsEta = yAxis_mu->GetBinLowEdge(idxBinY);
    double maxAbsEta = yAxis_mu->GetBinUpEdge(idxBinY);
    double absEta = 0.5*(minAbsEta + maxAbsEta);
    std::string graphName_data = TString(Form("graph_mu_absEta%1.2fto%1.2f_data", minAbsEta, maxAbsEta)).ReplaceAll(".", "_").Data();
    TGraphAsymmErrors* graph_data = bookGraph(fs, graphName_data, ptBins_mu_array);
    fillGraph(graph_data, histogram_mu_data, absEta);
    std::string graphName_mc = TString(Form("graph_mu_absEta%1.2fto%1.2f_mc", minAbsEta, maxAbsEta)).ReplaceAll(".", "_").Data();
    TGraphAsymmErrors* graph_mc = bookGraph(fs, graphName_mc, ptBins_mu_array);
    fillGraph(graph_mc, histogram_mu_mc, absEta);
    std::string outputFileName_plot = std::string(outputFileName, 0, outputFileName.find_last_of('.'));
    outputFileName_plot.append(Form("_mu_%s.png", getEtaBin(minAbsEta, maxAbsEta).data()));
    makeControlPlot(graph_data, graph_mc, ptBins_mu_array, minAbsEta, maxAbsEta, true, outputFileName_plot);
    makeControlPlot(graph_data, graph_mc, ptBins_mu_array, minAbsEta, maxAbsEta, false, outputFileName_plot);
  }

  clock.Show("comp_LeptonFakeRate");

  return 0;
}
