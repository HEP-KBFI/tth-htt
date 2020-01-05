/** \executable comp_LeptonFakeRate                                                                                                                                                                                                     
 *                                                                                                                                                                                                                                      
 * Determine probability for fakeable leptons of the ttH legacy analysis to get misidentified as prompt lepton candididates,                                                                                                            
 * measured in a region of phase space comprising exactly one fakeable lepton and atleast one jet separated by dr > 0.7                                                                                                                 
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
    : norm_data_fakes_prefit_(-1.)
    , normErr_data_fakes_prefit_(-1.)
    , Conv_corr_e_(1.)
    , Err_Conv_corr_e_(0.)
    , norm_TT_fakes_(-1.)  
    , normErr_TT_fakes_(-1.)  
    , norm_QCD_fakes_(-1.)  
    , normErr_QCD_fakes_(-1.)  
    , norm_QCD_fakes_Conv_Corrected_(-1.)  
    , normErr_QCD_fakes_Conv_Corrected_(-1.)  
    , norm_TTj_minus_TTg_(-1.)
    , normErr_TTj_minus_TTg_(-1.)  
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
      norm_data_fakes_postfit_ = readFloat(items->At(10), parseError);
      std::string normErr_data_fakes_string = readString(items->At(11), parseError);
      if ( normErr_data_fakes_string != "nan" ) {
        normErr_data_fakes_postfit_ = readFloat(items->At(11), parseError);
      } else {
        normErr_data_fakes_postfit_ = norm_data_fakes_postfit_;
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
  double norm_data_fakes_prefit_;
  double normErr_data_fakes_prefit_;
  double norm_data_fakes_postfit_;
  double normErr_data_fakes_postfit_;
  double Conv_corr_e_;
  double Err_Conv_corr_e_;
  double norm_TT_fakes_;
  double normErr_TT_fakes_;
  double norm_QCD_fakes_;
  double normErr_QCD_fakes_;
  double norm_QCD_fakes_Conv_Corrected_;
  double normErr_QCD_fakes_Conv_Corrected_;
  double norm_TTj_minus_TTg_;
  double normErr_TTj_minus_TTg_;

  void SetConv_corr(double corr, double corr_err){
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


  void ApplyConv_corr(){
    double uncorr_norm_data_fakes_prefit = norm_data_fakes_prefit_;
    double uncorr_norm_data_fakes_postfit = norm_data_fakes_postfit_;
    double uncorr_err_data_fakes_prefit = normErr_data_fakes_prefit_;
    double uncorr_err_data_fakes_postfit = normErr_data_fakes_postfit_;
    if(lepton_type_ == kElectron){
      norm_data_fakes_prefit_ *= Conv_corr_e_;
      normErr_data_fakes_prefit_ = (uncorr_err_data_fakes_prefit * Conv_corr_e_) + (uncorr_norm_data_fakes_prefit * Err_Conv_corr_e_);
      norm_data_fakes_postfit_ *= Conv_corr_e_;
      normErr_data_fakes_postfit_ = (uncorr_err_data_fakes_postfit * Conv_corr_e_) + (uncorr_norm_data_fakes_postfit * Err_Conv_corr_e_);
    }else if(lepton_type_ == kMuon){
      norm_data_fakes_prefit_ = uncorr_norm_data_fakes_prefit;
      norm_data_fakes_postfit_ = uncorr_norm_data_fakes_postfit;
      normErr_data_fakes_prefit_ = uncorr_err_data_fakes_prefit ;
      normErr_data_fakes_postfit_ = uncorr_err_data_fakes_postfit ;
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

void readConversionCorr(TFile* inputFile, std::map<std::string, fitResultType*>& fitResults, const std::string& process, const std::string& variable){

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



  }
}


void ComputeHistBinIntegral(TH1* histogram, std::map<std::string, fitResultType*>::iterator fitResult){
  double integral = 0.;
  double integralErr2 = 0.;
  int numBins = histogram->GetNbinsX();
  for ( int idxBin = 0; idxBin <= (numBins + 1); ++idxBin ) { // CV: include underflow and overflow bins                                                                                                                                                             
    double binContent = histogram->GetBinContent(idxBin);
    double binError = histogram->GetBinError(idxBin);
    integral += binContent;
    integralErr2 += (binError*binError);
  }
  std::cout << " ComputeHistBinIntegral(): integral " << integral << " integralErr2 " << integralErr2 << std::endl;
  double integralErr = TMath::Sqrt(integralErr2);
  fitResult->second->norm_TTj_minus_TTg_ = integral;
  fitResult->second->normErr_TTj_minus_TTg_ = integralErr;      
}


void FixHistBinIntegral(std::string& histogramName, TFile* inputFile, const std::string& ProcessName, const std::string& variable_den, double& integral, double& integralErr2)
{
    //double integral_temp = 0.;
    //double integralErr2_temp = 0.;
    histogramName.append(ProcessName);
    histogramName.append("/");
    histogramName.append(variable_den);
    std::cout << "loading histogram = '" << histogramName << "'" << std::endl;
    TH1* histogram = dynamic_cast<TH1*>(inputFile->Get(histogramName.data()));
    if ( !histogram ) throw cms::Exception("fillHistogram")
    << "Failed to load histogram = '" << histogramName << "' from file = '" << inputFile->GetName() << "' !!\n";

    int numBins = histogram->GetNbinsX();
    for ( int idxBin = 0; idxBin <= (numBins + 1); ++idxBin ) { // CV: include underflow and overflow bins
      double binContent = histogram->GetBinContent(idxBin);
      double binError = histogram->GetBinError(idxBin);
      //std::cout<< "binContent " << binContent << " +/- " << binError << std::endl;
      integral += binContent;
      integralErr2 += (binError*binError);
    }
}


void readPrefit(TFile* inputFile_stage2, TFile* inputFile_stage1_5, std::map<std::string, fitResultType*>& fitResults, const std::string& variable_den)
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
    std::string histogramName_TT_fakes = histogramName;  // Copying path for TTbar fakes 
    std::string histogramName_QCD_fakes = histogramName; // Copying path for QCD fakes 
    std::string histogramName_QCD_fakes_Conv_Corrected = histogramName; // Copying path for QCD fakes (Conv Corr.)

    std::string histogramName_TT_fakes_copy = histogramName;
    std::string histogramName_TTg = histogramName;
    histogramName_TT_fakes_copy.append("TTj");                                                                                                                                                                                                                       
     
    histogramName_TTg.append("TTg"); 
    histogramName_TT_fakes_copy.append("/");
    histogramName_TTg.append("/");   
    histogramName_TT_fakes_copy.append(variable_den);
    histogramName_TTg.append(variable_den); 
    std::cout << "loading histogram_TT_fakes_copy = '" << histogramName_TT_fakes_copy << "'" << std::endl;
    TH1* histogram_TT_fakes_copy = dynamic_cast<TH1*>(inputFile_stage1_5->Get(histogramName_TT_fakes_copy.data())->Clone());
    if ( !histogram_TT_fakes_copy ) throw cms::Exception("fillHistogram")
				 << "Failed to load histogram = '" << histogramName_TT_fakes_copy << "' from file = '" << inputFile_stage1_5->GetName() << "' !!\n";
    TH1* histogram_TTg = dynamic_cast<TH1*>(inputFile_stage1_5->Get(histogramName_TTg.data()));
    if ( !histogram_TTg ) throw cms::Exception("fillHistogram")
				 << "Failed to load histogram = '" << histogramName_TTg << "' from file = '" << inputFile_stage1_5->GetName() << "' !!\n";
    std::cout<< " histogram_TT_fakes_copy->GetEntries() " << histogram_TT_fakes_copy->GetEntries() << " histogram_TT_fakes_copy->Integral() " << histogram_TT_fakes_copy->Integral() << std::endl; 
    std::cout<< " histogram_TTg->GetEntries() " << histogram_TTg->GetEntries() << " histogram_TTg->Integral() " << histogram_TTg->Integral() << std::endl; 

    histogram_TT_fakes_copy->Add(histogram_TTg, -1.0); // TTj - TTg 

    std::cout<< "After Subtraction: histogram_TT_fakes_copy->GetEntries() " << histogram_TT_fakes_copy->GetEntries() << " histogram_TT_fakes_copy->Integral() " << histogram_TT_fakes_copy->Integral() << std::endl; 

    //double integral_TTj_minus_TTg = 0.;
    //double integralErr2_TTj_minus_TTg = 0.;
    ComputeHistBinIntegral(histogram_TT_fakes_copy, fitResult);
    //std::cout<< " integral_TTj_minus_TTg " << integral_TTj_minus_TTg << " integralErr_TTj_minus_TTg " << integralErr_TTj_minus_TTg << std::endl;      
    




    double integral_data_fakes_prefit = 0.;
    double integralErr2_data_fakes_prefit = 0.; 
    FixHistBinIntegral(histogramName, inputFile_stage2, "data_fakes", variable_den, integral_data_fakes_prefit, integralErr2_data_fakes_prefit);
    std::cout << " integral_data_fakes_prefit " << integral_data_fakes_prefit << " integralErr2_data_fakes_prefit " << integralErr2_data_fakes_prefit << std::endl;
    double integralErr_data_fakes_prefit = TMath::Sqrt(integralErr2_data_fakes_prefit);
    fitResult->second->norm_data_fakes_prefit_ = integral_data_fakes_prefit;
    fitResult->second->normErr_data_fakes_prefit_ = integralErr_data_fakes_prefit;
    std::cout<< " fitResult->second->norm_data_fakes_prefit_ " << fitResult->second->norm_data_fakes_prefit_ << " fitResult->second->normErr_data_fakes_prefit_ " << fitResult->second->normErr_data_fakes_prefit_ << std::endl;


    double integral_TT_fakes = 0.;
    double integralErr2_TT_fakes = 0.; 
    FixHistBinIntegral(histogramName_TT_fakes, inputFile_stage1_5, "TTj", variable_den, integral_TT_fakes, integralErr2_TT_fakes);
    double integralErr_TT_fakes = TMath::Sqrt(integralErr2_TT_fakes);
    fitResult->second->norm_TT_fakes_ = integral_TT_fakes;
    fitResult->second->normErr_TT_fakes_ = integralErr_TT_fakes;

    double integral_QCD_fakes = 0.;
    double integralErr2_QCD_fakes = 0.; 
    FixHistBinIntegral(histogramName_QCD_fakes, inputFile_stage1_5, "QCDj", variable_den, integral_QCD_fakes, integralErr2_QCD_fakes);
    double integralErr_QCD_fakes = TMath::Sqrt(integralErr2_QCD_fakes);
    fitResult->second->norm_QCD_fakes_ = integral_QCD_fakes;
    fitResult->second->normErr_QCD_fakes_ = integralErr_QCD_fakes;

    double integral_QCD_fakes_Conv_Corrected = 0.;
    double integralErr2_QCD_fakes_Conv_Corrected = 0.; 
    FixHistBinIntegral(histogramName_QCD_fakes_Conv_Corrected, inputFile_stage2, "QCD", variable_den, integral_QCD_fakes_Conv_Corrected, integralErr2_QCD_fakes_Conv_Corrected);
    double integralErr_QCD_fakes_Conv_Corrected = TMath::Sqrt(integralErr2_QCD_fakes_Conv_Corrected);
    fitResult->second->norm_QCD_fakes_Conv_Corrected_ = integral_QCD_fakes_Conv_Corrected;
    fitResult->second->normErr_QCD_fakes_Conv_Corrected_ = integralErr_QCD_fakes_Conv_Corrected;

    /*

    histogramName.append("data_fakes");
    histogramName.append("/");
    histogramName.append(variable_den);
 

    std::cout << "loading histogram = '" << histogramName << "'" << std::endl;
    TH1* histogram = dynamic_cast<TH1*>(inputFile_stage2->Get(histogramName.data()));
    if ( !histogram ) throw cms::Exception("fillHistogram")
    << "Failed to load histogram = '" << histogramName << "' from file = '" << inputFile_stage2->GetName() << "' !!\n";
    ComputeHistBinIntegral(histogram, integral_data_fakes, integralErr2_data_fakes);

    double integralErr_data_fakes = TMath::Sqrt(integralErr2_data_fakes);
    fitResult->second->norm_data_fakes_prefit_ = integral_data_fakes;
    fitResult->second->normErr_data_fakes_prefit_ = integralErr_data_fakes;
    */
  }
}


TH2* bookHistogram(fwlite::TFileService& fs, const std::string& histogramName, const TArrayD& ptBins, const TArrayD& absEtaBins)
{
  int numBinsX = ptBins.GetSize() - 1;
  int numBinsY = absEtaBins.GetSize() - 1;
  TH2* histogram = fs.make<TH2D>(histogramName.data(), histogramName.data(), numBinsX, ptBins.GetArray(), numBinsY, absEtaBins.GetArray());
  return histogram;
}


void fillHistogram(TH2* histogram, const std::map<std::string, fitResultType*>& fitResults_pass, const std::map<std::string, fitResultType*>& fitResults_fail, int prefit_or_postfit, 
		   bool is_data_fakes = true, bool is_TT_fakes = false, bool is_QCD_fakes = false, bool use_Conv_Corrected_QCD = false, bool is_TTj_minus_TTg = false)
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
      if((fitResult_pass->second->lepton_type_ == fitResultType::kElectron)){
	std::cout<< " Electron " << std::endl;
      }else{
	std::cout<< " Muon " << std::endl;
      }

      if ( fitResult_pass != fitResults_pass.end() && fitResult_fail != fitResults_fail.end() ) {
	double nPass, nPassErr, nFail, nFailErr;
	if(is_data_fakes && !is_TT_fakes && !is_QCD_fakes && !is_TTj_minus_TTg){ // For data driven fakes
	  if ( prefit_or_postfit == kPrefit ) {
	    std::cout<< "Pre-fit data fakes" << std::endl;
	    nPass = fitResult_pass->second->norm_data_fakes_prefit_;
	    nPassErr = fitResult_pass->second->normErr_data_fakes_prefit_;
	    nFail = fitResult_fail->second->norm_data_fakes_prefit_;
	    nFailErr = fitResult_fail->second->normErr_data_fakes_prefit_;
	    std::cout << " Prefit nPass " << nPass << " +/- " << nPassErr << " Prefit nFail " <<  nFail  << " +/- " << nFailErr << std::endl;
	  } else if ( prefit_or_postfit == kPostfit ) {
	    std::cout<< "Post-fit data fakes" << std::endl;
	    nPass = fitResult_pass->second->norm_data_fakes_postfit_;
	    nPassErr = fitResult_pass->second->normErr_data_fakes_postfit_;
	    nFail = fitResult_fail->second->norm_data_fakes_postfit_;
	    nFailErr = fitResult_fail->second->normErr_data_fakes_postfit_;
	  } else assert(0);
	}else if(!is_data_fakes && is_TT_fakes && !is_QCD_fakes && !is_TTj_minus_TTg){ // For TTBar MC driven fakes
	    std::cout<< "TTbar MC driven fakes" << std::endl;
	    nPass = fitResult_pass->second->norm_TT_fakes_;
	    nPassErr = fitResult_pass->second->normErr_TT_fakes_;
	    nFail = fitResult_fail->second->norm_TT_fakes_;
	    nFailErr = fitResult_fail->second->normErr_TT_fakes_;
	}else if(!is_data_fakes && !is_TT_fakes && is_QCD_fakes && !is_TTj_minus_TTg ){ // For QCD MC driven fakes
	  if(use_Conv_Corrected_QCD){
	    std::cout<< "QCD MC driven fakes (Corrected for Conversions)" << std::endl;
	    nPass = fitResult_pass->second->norm_QCD_fakes_Conv_Corrected_;
	    nPassErr = fitResult_pass->second->normErr_QCD_fakes_Conv_Corrected_;
	    nFail = fitResult_fail->second->norm_QCD_fakes_Conv_Corrected_;
	    nFailErr = fitResult_fail->second->normErr_QCD_fakes_Conv_Corrected_;
	  }else {
	    std::cout<< "QCD MC driven fakes (Un-corrected for Conversions)" << std::endl;
	    nPass = fitResult_pass->second->norm_QCD_fakes_;
	    nPassErr = fitResult_pass->second->normErr_QCD_fakes_;
	    nFail = fitResult_fail->second->norm_QCD_fakes_;
	    nFailErr = fitResult_fail->second->normErr_QCD_fakes_;
	  }
	}else if(!is_data_fakes && !is_TT_fakes && !is_QCD_fakes && is_TTj_minus_TTg ){ // For TTj - TTg
	    std::cout<< "(TTj - TTg) MC driven fakes " << std::endl;
	    nPass = fitResult_pass->second->norm_TTj_minus_TTg_;
	    nPassErr = fitResult_pass->second->normErr_TTj_minus_TTg_;
	    nFail = fitResult_fail->second->norm_TTj_minus_TTg_;
	    nFailErr = fitResult_fail->second->normErr_TTj_minus_TTg_;
	}else assert(0);
	double avFakeRate, avFakeRateErrUp, avFakeRateErrDown;
        bool errorFlag;
	std::cout << " nPass2 " << nPass << " +/- " << nPassErr << " nFail2 " <<  nFail  << " +/- " << nFailErr << std::endl;
        compFakeRate(nPass, nPassErr, nFail, nFailErr, avFakeRate, avFakeRateErrUp, avFakeRateErrDown, errorFlag);


	if((fitResult_pass->second->lepton_type_ == fitResultType::kElectron) && is_data_fakes){ // Applying Conv corrections to electrons in case of data fakes (numerator) only                                               
          avFakeRate *= fitResult_pass->second->Conv_corr_e_ ; // apply the correction                                                                                                                                                  
          double def_avFakeRateErrUp = avFakeRateErrUp;
          double def_avFakeRateErrDown = avFakeRateErrDown;
          avFakeRateErrUp = TMath::Sqrt(TMath::Power(def_avFakeRateErrUp, 2.0) + TMath::Power((fitResult_pass->second->Err_Conv_corr_e_), 2.0));
          avFakeRateErrDown = TMath::Sqrt(TMath::Power(def_avFakeRateErrDown, 2.0) + TMath::Power((fitResult_pass->second->Err_Conv_corr_e_), 2.0));
        }else{
	  std::cout << "Not applying Conversion corrections (since it is applicable only to elctrons in data fakes)" << std::endl;
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


void makeControlPlot(TGraphAsymmErrors* graph_data, TGraphAsymmErrors* graph_mc_QCD_fakes,  TGraphAsymmErrors* graph_mc_QCD_fakes_Conv_Corr, TGraphAsymmErrors* graph_mc_TT_fakes, TGraphAsymmErrors* graph_mc_TTj_minus_TTg_fakes, const TArrayD& ptBins, double minAbsEta, double maxAbsEta, bool useLogScale, const std::string& outputFileName)
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
    yMax = 0.50;
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


  if ( graph_mc_QCD_fakes ) {
    graph_mc_QCD_fakes->SetMarkerStyle(24);
    graph_mc_QCD_fakes->SetMarkerSize(2);
    graph_mc_QCD_fakes->SetMarkerColor(1);
    graph_mc_QCD_fakes->SetLineStyle(1);
    graph_mc_QCD_fakes->SetLineWidth(1);
    graph_mc_QCD_fakes->SetLineColor(1);
    graph_mc_QCD_fakes->Draw("psame");
  }

  if ( graph_mc_TT_fakes ) {
    graph_mc_TT_fakes->SetMarkerStyle(25);
    graph_mc_TT_fakes->SetMarkerSize(2);
    graph_mc_TT_fakes->SetMarkerColor(1);
    graph_mc_TT_fakes->SetLineStyle(1);
    graph_mc_TT_fakes->SetLineWidth(1);
    graph_mc_TT_fakes->SetLineColor(1);
    graph_mc_TT_fakes->Draw("psame");
  }

  if ( graph_mc_QCD_fakes_Conv_Corr ) {
    graph_mc_QCD_fakes_Conv_Corr->SetMarkerStyle(26);
    graph_mc_QCD_fakes_Conv_Corr->SetMarkerSize(2);
    graph_mc_QCD_fakes_Conv_Corr->SetMarkerColor(1);
    graph_mc_QCD_fakes_Conv_Corr->SetLineStyle(1);
    graph_mc_QCD_fakes_Conv_Corr->SetLineWidth(1);
    graph_mc_QCD_fakes_Conv_Corr->SetLineColor(1);
    graph_mc_QCD_fakes_Conv_Corr->Draw("psame");
  }

  if ( graph_mc_TTj_minus_TTg_fakes ) {
    graph_mc_TTj_minus_TTg_fakes->SetMarkerStyle(32);
    graph_mc_TTj_minus_TTg_fakes->SetMarkerSize(2);
    graph_mc_TTj_minus_TTg_fakes->SetMarkerColor(1);
    graph_mc_TTj_minus_TTg_fakes->SetLineStyle(1);
    graph_mc_TTj_minus_TTg_fakes->SetLineWidth(1);
    graph_mc_TTj_minus_TTg_fakes->SetLineColor(1);
    graph_mc_TTj_minus_TTg_fakes->Draw("psame");
  }



  TLegend* legend = 0;
    legend = new TLegend(0.73, 0.76, 0.88, 0.91, NULL, "brNDC");
    legend->SetFillStyle(0);
    legend->SetBorderSize(0);
    legend->SetFillColor(10);
    legend->SetTextFont(42);
    legend->SetTextSize(0.040);
    legend->SetMargin(0.24);
    if ( graph_data ) legend->AddEntry(graph_data, "Data",       "p");
    if ( graph_mc_QCD_fakes ) legend->AddEntry(graph_mc_QCD_fakes,   "Fakes (QCD)", "p");
    if ( graph_mc_QCD_fakes_Conv_Corr ) legend->AddEntry(graph_mc_QCD_fakes_Conv_Corr,   "Fakes (QCD#gamma)", "p");
    if ( graph_mc_TT_fakes ) legend->AddEntry(graph_mc_TT_fakes,   "Fakes (t#bar{t})", "p");
    if ( graph_mc_TTj_minus_TTg_fakes ) legend->AddEntry(graph_mc_TTj_minus_TTg_fakes,   "Fakes (t#bar{t}_{j} - t#bar{t}_{#gamma})", "p");
    legend->Draw();


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
  //double conv_unc = cfg_comp.getParameter<double>("Conversion_uncert");    // ADDED FOR CONV. CORR.S [Not needed anymore]


  fwlite::InputSource inputFiles(cfg);
  if ( !(inputFiles.files().size() == 2) )
    throw cms::Exception("comp_LeptonFakeRate")
      << "Exactly two input files expected !!\n";
  vstring inputFileNames = inputFiles.files();
  std::string inputFileName_data;
  std::string inputFileName_mc_stage2; // stage2 root file
  std::string inputFileName_mc_stage1_5; // stage1_5 root file

  for ( vstring::const_iterator inputFileName = inputFileNames.begin();
        inputFileName != inputFileNames.end(); ++inputFileName ) {
    if      ( inputFileName->find(".txt")  != std::string::npos ) inputFileName_data = (*inputFileName);
    else if ( inputFileName->find(".root") != std::string::npos ){
      inputFileName_mc_stage2   = (*inputFileName);
      inputFileName_mc_stage1_5 = (*inputFileName);
      std::string temp = "stage2";
      inputFileName_mc_stage1_5.replace(inputFileName_mc_stage1_5.find(temp), temp.length(), "stage1_5");
      std::cout<< " inputFileName_mc_stage1_5 " << inputFileName_mc_stage1_5 << std::endl;
    }
  }
  if ( !(inputFileName_data != "" && inputFileName_mc_stage2 != "") ) {
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
  std::cout << "opening stage 2 inputFile = '" << inputFileName_mc_stage2 << "'" << std::endl;
  TFile* inputFile_mc_stage2 = new TFile(inputFileName_mc_stage2.data());
  if ( !inputFile_mc_stage2 ) throw cms::Exception("comp_LeptonFakeRate")
			 << "Failed to open stage 2 input file = '" << inputFileName_mc_stage2 << "' !!\n";
  std::cout << "opening stage 1_5 inputFile = '" << inputFileName_mc_stage1_5 << "'" << std::endl;
  TFile* inputFile_mc_stage1_5 = new TFile(inputFileName_mc_stage1_5.data());
  if ( !inputFile_mc_stage1_5 ) throw cms::Exception("comp_LeptonFakeRate")
			 << "Failed to open stage 1_5 input file = '" << inputFileName_mc_stage1_5 << "' !!\n";

     //void readPrefit(TFile* inputFile_stage2, TFile* inputFile_stage1_5, std::map<std::string, fitResultType*>& fitResults, const std::string& variable_den)
  readPrefit(inputFile_mc_stage2, inputFile_mc_stage1_5, fitResults_e_pass, variable_den);
  readPrefit(inputFile_mc_stage2, inputFile_mc_stage1_5, fitResults_e_fail, variable_den);
  readPrefit(inputFile_mc_stage2, inputFile_mc_stage1_5, fitResults_mu_pass, variable_den);
  readPrefit(inputFile_mc_stage2, inputFile_mc_stage1_5, fitResults_mu_fail, variable_den);

  readConversionCorr(inputFile_mc_stage2, fitResults_e_pass, process, variable); // ADDED FOR ELECTRON CONV. CORRECTIONS

  std::cout << "closing inputFile_mc_stage2 = '" << inputFileName_mc_stage2 << "'" << std::endl;
  delete inputFile_mc_stage2;
  std::cout << "closing inputFile_mc_stage1_5 = '" << inputFileName_mc_stage1_5 << "'" << std::endl;
  delete inputFile_mc_stage1_5;

  fwlite::OutputFiles outputFile(cfg);
  fwlite::TFileService fs = fwlite::TFileService(outputFile.file().data());


  TH2* histogram_e_data_fakes_postfit = bookHistogram(fs, histogramName_e, ptBins_e_array, absEtaBins_e_array);
  fillHistogram(histogram_e_data_fakes_postfit, fitResults_e_pass, fitResults_e_fail, kPostfit);
  TH2* histogram_e_data_fakes_prefit = bookHistogram(fs, Form("%s_prefit", histogramName_e.data()), ptBins_e_array, absEtaBins_e_array);
  fillHistogram(histogram_e_data_fakes_prefit, fitResults_e_pass, fitResults_e_fail, kPrefit);
  TH2* histogram_e_mc_TT_fakes = bookHistogram(fs, Form("%s_TT_fakes", histogramName_e.data()), ptBins_e_array, absEtaBins_e_array);
  fillHistogram(histogram_e_mc_TT_fakes, fitResults_e_pass, fitResults_e_fail, kPrefit, false, true, false, false, false);
  TH2* histogram_e_mc_QCD_fakes = bookHistogram(fs, Form("%s_QCD_fakes", histogramName_e.data()), ptBins_e_array, absEtaBins_e_array);
  fillHistogram(histogram_e_mc_QCD_fakes, fitResults_e_pass, fitResults_e_fail, kPrefit, false, false, true, false, false); // Using Uncorrected QCD MC  
  TH2* histogram_e_mc_QCD_fakes_Conv_Corrected = bookHistogram(fs, Form("%s_QCD_fakes_Conv_Corr", histogramName_e.data()), ptBins_e_array, absEtaBins_e_array);
  fillHistogram(histogram_e_mc_QCD_fakes_Conv_Corrected, fitResults_e_pass, fitResults_e_fail, kPrefit, false, false, true, true, false); // Using Conv. Corrected QCD MC  
  
  TH2* histogram_e_mc_TTj_minus_TTg_fakes = bookHistogram(fs, Form("%s_TTj_minus_TTg_fakes", histogramName_e.data()), ptBins_e_array, absEtaBins_e_array);
  fillHistogram(histogram_e_mc_TTj_minus_TTg_fakes, fitResults_e_pass, fitResults_e_fail, kPrefit, false, false, false, false, true);



  TAxis* yAxis_e = histogram_e_data_fakes_postfit->GetYaxis();
  for ( int idxBinY = 1; idxBinY <= yAxis_e->GetNbins(); ++idxBinY ) {
    double minAbsEta = yAxis_e->GetBinLowEdge(idxBinY);
    double maxAbsEta = yAxis_e->GetBinUpEdge(idxBinY);
    double absEta = 0.5*(minAbsEta + maxAbsEta);
    std::string graphName_data = TString(Form("graph_e_absEta%1.2fto%1.2f_data", minAbsEta, maxAbsEta)).ReplaceAll(".", "_").Data();
    TGraphAsymmErrors* graph_data = bookGraph(fs, graphName_data, ptBins_e_array);
    fillGraph(graph_data, histogram_e_data_fakes_postfit, absEta);

    std::string graphName_mc_TT_fakes = TString(Form("graph_e_absEta%1.2fto%1.2f_mc_TT_fakes", minAbsEta, maxAbsEta)).ReplaceAll(".", "_").Data();
    TGraphAsymmErrors* graph_mc_TT_fakes = bookGraph(fs, graphName_mc_TT_fakes, ptBins_e_array);
    fillGraph(graph_mc_TT_fakes, histogram_e_mc_TT_fakes, absEta);

    std::string graphName_mc_QCD_fakes = TString(Form("graph_e_absEta%1.2fto%1.2f_mc_QCD_fakes", minAbsEta, maxAbsEta)).ReplaceAll(".", "_").Data();
    TGraphAsymmErrors* graph_mc_QCD_fakes = bookGraph(fs, graphName_mc_QCD_fakes, ptBins_e_array);
    fillGraph(graph_mc_QCD_fakes, histogram_e_mc_QCD_fakes, absEta);

    std::string graphName_mc_QCD_fakes_Conv_Corr = TString(Form("graph_e_absEta%1.2fto%1.2f_mc_QCD_fakes_Conv_Corr", minAbsEta, maxAbsEta)).ReplaceAll(".", "_").Data();
    TGraphAsymmErrors* graph_mc_QCD_fakes_Conv_Corr = bookGraph(fs, graphName_mc_QCD_fakes_Conv_Corr, ptBins_e_array);
    fillGraph(graph_mc_QCD_fakes_Conv_Corr, histogram_e_mc_QCD_fakes_Conv_Corrected, absEta);
    
    std::string graphName_mc_TTj_minus_TTg_fakes = TString(Form("graph_e_absEta%1.2fto%1.2f_mc_TTj_minus_TTg_fakes", minAbsEta, maxAbsEta)).ReplaceAll(".", "_").Data();
    TGraphAsymmErrors* graph_mc_TTj_minus_TTg_fakes = bookGraph(fs, graphName_mc_TTj_minus_TTg_fakes, ptBins_e_array);
    fillGraph(graph_mc_TTj_minus_TTg_fakes, histogram_e_mc_TTj_minus_TTg_fakes, absEta);


    std::string outputFileName_plot = std::string(outputFileName, 0, outputFileName.find_last_of('.'));
    outputFileName_plot.append(Form("_e_%s.png", getEtaBin(minAbsEta, maxAbsEta).data()));


    makeControlPlot(graph_data, graph_mc_QCD_fakes, graph_mc_QCD_fakes_Conv_Corr,  graph_mc_TT_fakes, graph_mc_TTj_minus_TTg_fakes, ptBins_e_array, minAbsEta, maxAbsEta, true, outputFileName_plot);
    makeControlPlot(graph_data, graph_mc_QCD_fakes, graph_mc_QCD_fakes_Conv_Corr,  graph_mc_TT_fakes, graph_mc_TTj_minus_TTg_fakes, ptBins_e_array, minAbsEta, maxAbsEta, false, outputFileName_plot);
  }  


  TH2* histogram_mu_data_fakes_postfit = bookHistogram(fs, histogramName_mu, ptBins_mu_array, absEtaBins_mu_array);
  fillHistogram(histogram_mu_data_fakes_postfit, fitResults_mu_pass, fitResults_mu_fail, kPostfit);
  TH2* histogram_mu_data_fakes_prefit = bookHistogram(fs, Form("%s_prefit", histogramName_mu.data()), ptBins_mu_array, absEtaBins_mu_array);
  fillHistogram(histogram_mu_data_fakes_prefit, fitResults_mu_pass, fitResults_mu_fail, kPrefit);
  TH2* histogram_mu_mc_TT_fakes = bookHistogram(fs, Form("%s_TT_fakes_prefit", histogramName_mu.data()), ptBins_mu_array, absEtaBins_mu_array);
  fillHistogram(histogram_mu_mc_TT_fakes, fitResults_mu_pass, fitResults_mu_fail, kPrefit, false, true, false, false);
  TH2* histogram_mu_mc_QCD_fakes = bookHistogram(fs, Form("%s_QCD_fakes", histogramName_mu.data()), ptBins_mu_array, absEtaBins_mu_array);
  fillHistogram(histogram_mu_mc_QCD_fakes, fitResults_mu_pass, fitResults_mu_fail, kPrefit, false, false, true, false); // Using Uncorrected QCD MC (Since photon conv.s important only for electrons) 

  TAxis* yAxis_mu = histogram_mu_data_fakes_postfit->GetYaxis();
  for ( int idxBinY = 1; idxBinY <= yAxis_mu->GetNbins(); ++idxBinY ) {
    double minAbsEta = yAxis_mu->GetBinLowEdge(idxBinY);
    double maxAbsEta = yAxis_mu->GetBinUpEdge(idxBinY);
    double absEta = 0.5*(minAbsEta + maxAbsEta);
    std::string graphName_data = TString(Form("graph_mu_absEta%1.2fto%1.2f_data", minAbsEta, maxAbsEta)).ReplaceAll(".", "_").Data();
    TGraphAsymmErrors* graph_data = bookGraph(fs, graphName_data, ptBins_mu_array);
    fillGraph(graph_data, histogram_mu_data_fakes_postfit, absEta);

    std::string graphName_mc_TT_fakes = TString(Form("graph_mu_absEta%1.2fto%1.2f_mc_TT_fakes", minAbsEta, maxAbsEta)).ReplaceAll(".", "_").Data();
    TGraphAsymmErrors* graph_mc_TT_fakes = bookGraph(fs, graphName_mc_TT_fakes, ptBins_mu_array);
    fillGraph(graph_mc_TT_fakes, histogram_mu_mc_TT_fakes, absEta);

    std::string graphName_mc_QCD_fakes = TString(Form("graph_mu_absEta%1.2fto%1.2f_mc_QCD_fakes", minAbsEta, maxAbsEta)).ReplaceAll(".", "_").Data();
    TGraphAsymmErrors* graph_mc_QCD_fakes = bookGraph(fs, graphName_mc_QCD_fakes, ptBins_mu_array);
    fillGraph(graph_mc_QCD_fakes, histogram_mu_mc_QCD_fakes, absEta);


    TGraphAsymmErrors* graph_mc_QCD_fakes_Conv_Corr = 0;
    TGraphAsymmErrors* graph_mc_TTj_minus_TTg_fakes = 0;


    std::string outputFileName_plot = std::string(outputFileName, 0, outputFileName.find_last_of('.'));
    outputFileName_plot.append(Form("_mu_%s.png", getEtaBin(minAbsEta, maxAbsEta).data()));


    makeControlPlot(graph_data, graph_mc_QCD_fakes, graph_mc_QCD_fakes_Conv_Corr,  graph_mc_TT_fakes, graph_mc_TTj_minus_TTg_fakes, ptBins_mu_array, minAbsEta, maxAbsEta, true, outputFileName_plot);
    makeControlPlot(graph_data, graph_mc_QCD_fakes, graph_mc_QCD_fakes_Conv_Corr,  graph_mc_TT_fakes, graph_mc_TTj_minus_TTg_fakes, ptBins_mu_array, minAbsEta, maxAbsEta, false, outputFileName_plot);


  }




}
