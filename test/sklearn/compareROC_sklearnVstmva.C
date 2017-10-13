#include <TFile.h>
#include <TTree.h>
#include <TTreeFormula.h>
#include <TH1F.h>
#include <TGraph.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TMath.h>
#include <TROOT.h>
#include <TSystem.h>
#include <TCut.h>
#include <vector>

void LegendSettings(TLegend *leg, int ncolumn){
  leg->SetNColumns(ncolumn);
  leg->SetBorderSize(0);
  leg->SetFillColor(10);
  leg->SetLineColor(0);
  leg->SetFillStyle(0);
  leg->SetTextSize(0.035);
  leg->SetTextFont(42);
}
void compareROC(std::vector<TString> filenames, std::vector<TString> histDirs, std::vector<TString> mvatype, std::vector<TString> legends, TString outfileDir, TString outfile)
{
  
  gROOT->SetBatch(true);
  
  std::vector<TH1F*> h_ROCs;
  //h_ROCs.resize(filenames.size());
  std::vector<TH1F*> h_ROCs_training; 
  //h_ROCs_training.resize(filenames.size());
  std::vector<TGraph*> h_ROCs_skl;
  std::vector<TGraph*> h_ROCs_training_skl;
  std::vector<TFile*> inFiles;
  inFiles.resize(filenames.size());
  for(size_t ifile = 0; ifile < filenames.size(); ifile++){
    inFiles[ifile] = new TFile(filenames[ifile]);
    if(mvatype[ifile].Contains("TMVA")){
      h_ROCs.push_back((TH1F*) inFiles[ifile]->Get(histDirs[ifile]+"/MVA_BDTG_effBvsS"));
      h_ROCs_training.push_back((TH1F*) inFiles[ifile]->Get(histDirs[ifile]+"/MVA_BDTG_trainingEffBvsS"));
    }
    else if(mvatype[ifile].Contains("SKLEARN")){
      h_ROCs_skl.push_back((TGraph*) inFiles[ifile]->Get(histDirs[ifile]+"roc_test"));
      h_ROCs_training_skl.push_back((TGraph*) inFiles[ifile]->Get(histDirs[ifile]+"roc_train"));
    }
    else{std::cout<<" No valid MVA type found "<<std::endl;}
  }

  int colors[] = { 1, 2, 4, 6, 7, 9};

  for(size_t ih = 0; ih < h_ROCs.size(); ih++){
    h_ROCs[ih]->SetLineColor(colors[ih]);
    h_ROCs_training[ih]->SetLineColor(colors[ih]);
    h_ROCs_training[ih]->SetLineStyle(2);
  }
  for(size_t ih = 0; ih < h_ROCs_skl.size(); ih++){ 
    h_ROCs_skl[ih]->SetLineColor(colors[ih+h_ROCs.size()]); 
    h_ROCs_training_skl[ih]->SetLineColor(colors[ih+h_ROCs.size()]); 
    h_ROCs_training_skl[ih]->SetLineStyle(2);
  }

  TCanvas* canvas = new TCanvas("canvas", "canvas", 800, 900);
  canvas->SetFillColor(10);
  canvas->SetBorderSize(2);
  canvas->SetLeftMargin(0.12);
  canvas->SetBottomMargin(0.12);
  canvas->SetRightMargin(0.05);
  canvas->SetLogy();
  canvas->cd();

  TH1F* histogram_base = new TH1F("histogram_base", "", 100, 0., 1.);
  histogram_base->SetTitle("");
  histogram_base->SetStats(false);
  histogram_base->SetMinimum(0.001);
  histogram_base->SetMaximum(10.);
  histogram_base->GetXaxis()->SetTitle("Signal Eff.");
  histogram_base->GetYaxis()->SetTitle("Background Eff.");
  histogram_base->Draw("hist");

  for(size_t ih = 0; ih < h_ROCs.size(); ih++){ 
    h_ROCs[ih]->Draw("same");
    h_ROCs_training[ih]->Draw("same"); 
  }
  for(size_t ih = 0; ih < h_ROCs_skl.size(); ih++){ 
    h_ROCs_skl[ih]->Draw("Lsame");
    h_ROCs_training_skl[ih]->Draw("Lsame");
  }

  TLegend *leg1 = new TLegend(0.15,0.6,0.5,(0.6+0.1*(h_ROCs.size()+h_ROCs_skl.size())));
  LegendSettings(leg1, 1);
  for(size_t ih = 0; ih < h_ROCs.size(); ih++){ 
    leg1->AddEntry(h_ROCs[ih], legends[ih]+" (test)", "l");
    leg1->AddEntry(h_ROCs_training[ih], legends[ih]+" (train)", "l");
  }
  for(size_t ih = 0; ih < h_ROCs_skl.size(); ih++){ 
    leg1->AddEntry(h_ROCs_skl[ih], legends[ih+h_ROCs.size()]+" (test)", "l"); 
    leg1->AddEntry(h_ROCs_training_skl[ih], legends[ih+h_ROCs.size()]+" (train)", "l"); 
  }
  leg1->Draw();
  
  canvas->Update();
  //canvas->SaveAs(outfileDir+"/comparison_roc_sklearn_maxDepthN_9Var_1l2tau.png");
  //canvas->SaveAs(outfileDir+"/comparison_roc_sklearn_maxDepthN_20Var_2lss1tau.png");
  //canvas->SaveAs(outfileDir+"/comparison_roc_sklearn_maxDepth4_NVar_2lss1tau.png");
  //canvas->SaveAs(outfileDir+"/comparison_roc_tmva_vs_sklearn_2lss1tau_multilep.png");
  //canvas->SaveAs(outfileDir+"/comparison_roc_sklearn_maxDepthN_2lss1tau_multilep.png");
  //canvas->SaveAs(outfileDir+"/comparison_roc_sklearn_2lss1tau_vs_2lss1tau_ttV_multilep.png");
  //canvas->SaveAs(outfileDir+"/comparison_roc_sklearn_2lss1tau_vs_2lss1tau_ttV_10Var_mem.png");
  //canvas->SaveAs(outfileDir+"/comparison_roc_sklearn_2lss1tau_vs_2lss1tau_tt_11Var_mem.png");
  //canvas->SaveAs(outfileDir+"/comparison_roc_sklearn_2lss1tau_vs_2lss1tau_ttV_10Var_5memVar.png");
  //canvas->SaveAs(outfileDir+"/comparison_roc_sklearn_2lss1tau_vs_2lss1tau_tt_11Var_5memVar.png"); 

  //canvas->SaveAs(outfileDir+"/comparison_roc_sklearn_3l1tau_tt.png");
  //canvas->SaveAs(outfileDir+"/comparison_roc_sklearn_3l1tau_ttV.png"); 
  canvas->SaveAs(outfileDir+"/"+outfile);
}

void compareAll()
{
  /*
  vector<TString> filenames_2lss_1tau_multilep;         
  filenames_2lss_1tau_multilep.push_back("results/2lss1tau/2lss_1tau_performance_maxDepth3_multilep.root");   
  filenames_2lss_1tau_multilep.push_back("results/2lss1tau/2lss_1tau_performance_maxDepth3_8Var.root");          
  filenames_2lss_1tau_multilep.push_back("results/2lss1tau/2lss_1tau_performance_maxDepth3_13Var.root");
  filenames_2lss_1tau_multilep.push_back("results/2lss1tau/2lss_1tau_performance_maxDepth3_23Var.root");
  vector<TString>histDirs_2lss_1tau_multilep;         
  histDirs_2lss_1tau_multilep.push_back("");       
  histDirs_2lss_1tau_multilep.push_back("");
  histDirs_2lss_1tau_multilep.push_back("");
  histDirs_2lss_1tau_multilep.push_back("");
  vector<TString>mvatype;   
  mvatype.push_back("SKLEARN");
  mvatype.push_back("SKLEARN");   
  mvatype.push_back("SKLEARN");
  mvatype.push_back("SKLEARN");
  vector<TString>legends_2lss_1tau_multilep;         
  legends_2lss_1tau_multilep.push_back("sklearn-multilep");
  legends_2lss_1tau_multilep.push_back("sklearn-8Var");
  legends_2lss_1tau_multilep.push_back("sklearn-13Var");
  legends_2lss_1tau_multilep.push_back("sklearn-23Var");
  compareROC(filenames_2lss_1tau_multilep, histDirs_2lss_1tau_multilep, mvatype, legends_2lss_1tau_multilep, "plots");
  */
  /*
  vector<TString> filenames_2lss_1tau_ttV_multilep;
  filenames_2lss_1tau_ttV_multilep.push_back("results/2lss1tau/2lss_1tau_ttV_performance_maxDepth3_multilep.root");
  filenames_2lss_1tau_ttV_multilep.push_back("results/2lss1tau/2lss_1tau_ttV_performance_maxDepth3_8Var.root");
  filenames_2lss_1tau_ttV_multilep.push_back("results/2lss1tau/2lss_1tau_ttV_performance_maxDepth3_13Var.root");
  filenames_2lss_1tau_ttV_multilep.push_back("results/2lss1tau/2lss_1tau_ttV_performance_maxDepth3_23Var.root");
  vector<TString>histDirs_2lss_1tau_ttV_multilep;
  histDirs_2lss_1tau_ttV_multilep.push_back("");
  histDirs_2lss_1tau_ttV_multilep.push_back("");
  histDirs_2lss_1tau_ttV_multilep.push_back("");
  histDirs_2lss_1tau_ttV_multilep.push_back("");
  vector<TString>mvatype;
  mvatype.push_back("SKLEARN");
  mvatype.push_back("SKLEARN");
  mvatype.push_back("SKLEARN");
  mvatype.push_back("SKLEARN");
  vector<TString>legends_2lss_1tau_ttV_multilep;
  legends_2lss_1tau_ttV_multilep.push_back("sklearn-multilep");
  legends_2lss_1tau_ttV_multilep.push_back("sklearn-8Var");
  legends_2lss_1tau_ttV_multilep.push_back("sklearn-13Var");
  legends_2lss_1tau_ttV_multilep.push_back("sklearn-23Var");
  compareROC(filenames_2lss_1tau_ttV_multilep, histDirs_2lss_1tau_ttV_multilep, mvatype, legends_2lss_1tau_ttV_multilep, "plots");
  */
  /*
  vector<TString> filenames_2lss_1tau_tt_mem;
  filenames_2lss_1tau_tt_mem.push_back("training_v6_09Feb17/results/2lss1tau/2lss_1tau_performance_maxDepth3_onlyMEM.root");
  filenames_2lss_1tau_tt_mem.push_back("training_v6_09Feb17/results/2lss1tau/2lss_1tau_performance_maxDepth3_11Var_mem.root");
  filenames_2lss_1tau_tt_mem.push_back("training_v6_09Feb17/results/2lss1tau/2lss_1tau_performance_maxDepth3_11Var.root");
  vector<TString>histDirs_2lss_1tau_tt_mem;
  histDirs_2lss_1tau_tt_mem.push_back("");
  histDirs_2lss_1tau_tt_mem.push_back("");
  histDirs_2lss_1tau_tt_mem.push_back("");
  vector<TString>mvatype;
  mvatype.push_back("SKLEARN");
  mvatype.push_back("SKLEARN");
  mvatype.push_back("SKLEARN");
  vector<TString>legends_2lss_1tau_tt_mem;
  legends_2lss_1tau_tt_mem.push_back("MEM");
  legends_2lss_1tau_tt_mem.push_back("sklearn-11Var-mem");
  legends_2lss_1tau_tt_mem.push_back("sklearn-11Var");
  compareROC(filenames_2lss_1tau_tt_mem, histDirs_2lss_1tau_tt_mem, mvatype, legends_2lss_1tau_tt_mem, "plots");
  */
  /*  
  vector<TString> filenames_2lss_1tau_ttV_mem;
  filenames_2lss_1tau_ttV_mem.push_back("results/2lss1tau/2lss_1tau_ttV_performance_maxDepth3_13Var_mem.root");
  filenames_2lss_1tau_ttV_mem.push_back("results/2lss1tau/2lss_1tau_ttV_performance_maxDepth3_13Var.root");
  vector<TString>histDirs_2lss_1tau_ttV_mem;
  histDirs_2lss_1tau_ttV_mem.push_back("");
  histDirs_2lss_1tau_ttV_mem.push_back("");
  vector<TString>mvatype;
  mvatype.push_back("SKLEARN");
  mvatype.push_back("SKLEARN");
  vector<TString>legends_2lss_1tau_ttV_mem;
  legends_2lss_1tau_ttV_mem.push_back("sklearn-13Var-mem");
  legends_2lss_1tau_ttV_mem.push_back("sklearn-13Var");
  compareROC(filenames_2lss_1tau_ttV_mem, histDirs_2lss_1tau_ttV_mem, mvatype, legends_2lss_1tau_ttV_mem, "plots");
  */
  /*  
  vector<TString> filenames_2lss_1tau_ttV_mem;
  filenames_2lss_1tau_ttV_mem.push_back("training_v5_03Feb17/results/2lss1tau/2lss_1tau_ttV_performance_maxDepth3_onlyMEM.root");
  filenames_2lss_1tau_ttV_mem.push_back("training_v6_09Feb17/results/2lss1tau/2lss_1tau_ttV_performance_maxDepth3_10Var_mem.root");
  filenames_2lss_1tau_ttV_mem.push_back("training_v6_09Feb17/results/2lss1tau/2lss_1tau_ttV_performance_maxDepth3_10Var.root");
  vector<TString>histDirs_2lss_1tau_ttV_mem;
  histDirs_2lss_1tau_ttV_mem.push_back("");
  histDirs_2lss_1tau_ttV_mem.push_back("");
  histDirs_2lss_1tau_ttV_mem.push_back("");
  vector<TString>mvatype;
  mvatype.push_back("SKLEARN");
  mvatype.push_back("SKLEARN");
  mvatype.push_back("SKLEARN");
  vector<TString>legends_2lss_1tau_ttV_mem;
  legends_2lss_1tau_ttV_mem.push_back("MEM");
  legends_2lss_1tau_ttV_mem.push_back("sklearn-10Var-mem");
  legends_2lss_1tau_ttV_mem.push_back("sklearn-10Var");
  compareROC(filenames_2lss_1tau_ttV_mem, histDirs_2lss_1tau_ttV_mem, mvatype, legends_2lss_1tau_ttV_mem, "plots");
  */
  /*
  vector<TString> filenames_2lss_1tau_ttV_mem;
  filenames_2lss_1tau_ttV_mem.push_back("results/2lss1tau/2lss_1tau_ttV_performance_maxDepth3_memVars.root");
  filenames_2lss_1tau_ttV_mem.push_back("results/2lss1tau/2lss_1tau_ttV_performance_maxDepth3_10Var_memVars.root");
  filenames_2lss_1tau_ttV_mem.push_back("results/2lss1tau/2lss_1tau_ttV_performance_maxDepth3_10Var.root");
  vector<TString>histDirs_2lss_1tau_ttV_mem;
  histDirs_2lss_1tau_ttV_mem.push_back("");
  histDirs_2lss_1tau_ttV_mem.push_back("");
  histDirs_2lss_1tau_ttV_mem.push_back("");
  vector<TString>mvatype;
  mvatype.push_back("SKLEARN");
  mvatype.push_back("SKLEARN");
  mvatype.push_back("SKLEARN");
  vector<TString>legends_2lss_1tau_ttV_mem;
  legends_2lss_1tau_ttV_mem.push_back("5memVar");
  legends_2lss_1tau_ttV_mem.push_back("10Var-5memVar");
  legends_2lss_1tau_ttV_mem.push_back("10Var");
  compareROC(filenames_2lss_1tau_ttV_mem, histDirs_2lss_1tau_ttV_mem, mvatype, legends_2lss_1tau_ttV_mem, "plots");
  */
  /*
  vector<TString> filenames_2lss_1tau_tt_mem;
  filenames_2lss_1tau_tt_mem.push_back("results/2lss1tau/2lss_1tau_performance_maxDepth3_memVars.root");
  filenames_2lss_1tau_tt_mem.push_back("results/2lss1tau/2lss_1tau_performance_maxDepth3_11Var_memVars.root");
  filenames_2lss_1tau_tt_mem.push_back("results/2lss1tau/2lss_1tau_performance_maxDepth3_11Var.root");
  vector<TString>histDirs_2lss_1tau_tt_mem;
  histDirs_2lss_1tau_tt_mem.push_back("");
  histDirs_2lss_1tau_tt_mem.push_back("");
  histDirs_2lss_1tau_tt_mem.push_back("");
  vector<TString>mvatype;
  mvatype.push_back("SKLEARN");
  mvatype.push_back("SKLEARN");
  mvatype.push_back("SKLEARN");
  vector<TString>legends_2lss_1tau_tt_mem;
  legends_2lss_1tau_tt_mem.push_back("5memVar");
  legends_2lss_1tau_tt_mem.push_back("11Var-5memVar");
  legends_2lss_1tau_tt_mem.push_back("11Var");
  compareROC(filenames_2lss_1tau_tt_mem, histDirs_2lss_1tau_tt_mem, mvatype, legends_2lss_1tau_tt_mem, "plots");
  */
  /*
  vector<TString> filenames_3l_1tau_tt;
  filenames_3l_1tau_tt.push_back("training_3l1t/3l_1tau_performance_maxDepth3_multilep_mva.root");
  filenames_3l_1tau_tt.push_back("training_3l1t/3l_1tau_performance_maxDepth3_12Var.root");
  filenames_3l_1tau_tt.push_back("training_3l1t/3l_1tau_performance_maxDepth3_9Var.root");
  vector<TString>histDirs_3l_1tau_tt;
  histDirs_3l_1tau_tt.push_back("");
  histDirs_3l_1tau_tt.push_back("");
  histDirs_3l_1tau_tt.push_back("");
  vector<TString>mvatype;
  mvatype.push_back("SKLEARN");
  mvatype.push_back("SKLEARN");
  mvatype.push_back("SKLEARN");
  vector<TString>legends_3l_1tau_tt;
  legends_3l_1tau_tt.push_back("tth-multilep-mva");
  legends_3l_1tau_tt.push_back("sklearn-12Var");
  legends_3l_1tau_tt.push_back("sklearn-9Var");
  compareROC(filenames_3l_1tau_tt, histDirs_3l_1tau_tt, mvatype, legends_3l_1tau_tt, "plots");
  */
  /*
  vector<TString> filenames_3l_1tau_ttV;
  filenames_3l_1tau_ttV.push_back("training_3l1t/3l_1tau_ttV_performance_maxDepth3_multilep_mva.root");
  filenames_3l_1tau_ttV.push_back("training_3l1t/3l_1tau_ttV_performance_maxDepth3_16Var.root");
  filenames_3l_1tau_ttV.push_back("training_3l1t/3l_1tau_ttV_performance_maxDepth3_9Var.root");
  vector<TString>histDirs_3l_1tau_ttV;
  histDirs_3l_1tau_ttV.push_back("");
  histDirs_3l_1tau_ttV.push_back("");
  histDirs_3l_1tau_ttV.push_back("");
  vector<TString>mvatype;
  mvatype.push_back("SKLEARN");
  mvatype.push_back("SKLEARN");
  mvatype.push_back("SKLEARN");
  vector<TString>legends_3l_1tau_ttV;
  legends_3l_1tau_ttV.push_back("tth-multilep-mva");
  legends_3l_1tau_ttV.push_back("sklearn-16Var");
  legends_3l_1tau_ttV.push_back("sklearn-9Var");
  compareROC(filenames_3l_1tau_ttV, histDirs_3l_1tau_ttV, mvatype, legends_3l_1tau_ttV, "plots");
  */  
  /*
  vector<TString> filenames_2lss_1tau_wCuts_frWt;
  filenames_2lss_1tau_wCuts_frWt.push_back("training_fastsim_v2_03Mar2017_wCuts_frWt/2lss_1tau_performance_maxDepth3_8Var_oldset_frWt.root");
  filenames_2lss_1tau_wCuts_frWt.push_back("training_fastsim_v2_03Mar2017_wCuts_frWt/2lss_1tau_performance_maxDepth3_allVar_frWt.root");
  filenames_2lss_1tau_wCuts_frWt.push_back("training_fastsim_v2_03Mar2017_wCuts_frWt/2lss_1tau_performance_maxDepth3_8Var_frWt.root");
  vector<TString> histDirs_2lss_1tau_wCuts_frWt;
  histDirs_2lss_1tau_wCuts_frWt.push_back("");
  histDirs_2lss_1tau_wCuts_frWt.push_back("");
  histDirs_2lss_1tau_wCuts_frWt.push_back("");
  vector<TString> mvatype;
  mvatype.push_back("SKLEARN");
  mvatype.push_back("SKLEARN");
  mvatype.push_back("SKLEARN");
  vector<TString> legends_2lss_1tau_wCuts_frWt;
  legends_2lss_1tau_wCuts_frWt.push_back("8Var-old-wCuts-wFrWt");
  legends_2lss_1tau_wCuts_frWt.push_back("allVar-wCuts-wFrWt");
  legends_2lss_1tau_wCuts_frWt.push_back("8Var-wCuts-wFrWt");
  compareROC(filenames_2lss_1tau_wCuts_frWt,histDirs_2lss_1tau_wCuts_frWt,mvatype,legends_2lss_1tau_wCuts_frWt,"plots", "comparison_roc_sklearn_2lss1tau_wCuts_wFrWt.png");
  */
  /*  
  vector<TString> filenames_2lss_1tau_wCuts_frWt;
  filenames_2lss_1tau_wCuts_frWt.push_back("/home/arun/VHbbNtuples_7_6_x/CMSSW_7_6_3_for8X/src/tthAnalysis/HiggsToTauTau/test/weights_2lss_1tau_wCuts_allVar_07Mar2017/trainTTHMVA_2lss_1tau_07Mar17_allVar_wfrWt.root");
  filenames_2lss_1tau_wCuts_frWt.push_back("training_fastsim_v2_03Mar2017_wCuts_frWt/2lss_1tau_performance_maxDepth3_allVar_frWt.root");
  vector<TString> histDirs_2lss_1tau_wCuts_frWt;
  histDirs_2lss_1tau_wCuts_frWt.push_back("Method_BDT/BDTG/");
  histDirs_2lss_1tau_wCuts_frWt.push_back("");
  vector<TString> mvatype;
  mvatype.push_back("TMVA");
  mvatype.push_back("SKLEARN");
  vector<TString> legends_2lss_1tau_wCuts_frWt;
  legends_2lss_1tau_wCuts_frWt.push_back("tmva-allVar-wCuts-wFrWt");
  legends_2lss_1tau_wCuts_frWt.push_back("sklearn-allVar-wCuts-wFrWt");
  compareROC(filenames_2lss_1tau_wCuts_frWt,histDirs_2lss_1tau_wCuts_frWt,mvatype,legends_2lss_1tau_wCuts_frWt,"plots","comparison_roc_sklearn_vs_tmva_2lss1tau_allVar_wCuts_wFrWt.png");

  vector<TString> filenames_2lss_1tau_wCuts_frWt;
  filenames_2lss_1tau_wCuts_frWt.push_back("/home/arun/VHbbNtuples_7_6_x/CMSSW_7_6_3_for8X/src/tthAnalysis/HiggsToTauTau/test/weights_2lss_1tau_wCuts_8Var_07Mar2017/trainTTHMVA_2lss_1tau_07Mar17_8Var_wfrWt.root");
  filenames_2lss_1tau_wCuts_frWt.push_back("training_fastsim_v2_03Mar2017_wCuts_frWt/2lss_1tau_performance_maxDepth3_8Var_frWt.root");
  vector<TString> histDirs_2lss_1tau_wCuts_frWt;
  histDirs_2lss_1tau_wCuts_frWt.push_back("Method_BDT/BDTG/");
  histDirs_2lss_1tau_wCuts_frWt.push_back("");
  vector<TString> mvatype;
  mvatype.push_back("TMVA");
  mvatype.push_back("SKLEARN");
  vector<TString> legends_2lss_1tau_wCuts_frWt;
  legends_2lss_1tau_wCuts_frWt.push_back("tmva-8Var-wCuts-wFrWt");
  legends_2lss_1tau_wCuts_frWt.push_back("sklearn-8Var-wCuts-wFrWt");
  compareROC(filenames_2lss_1tau_wCuts_frWt,histDirs_2lss_1tau_wCuts_frWt,mvatype,legends_2lss_1tau_wCuts_frWt,"plots","comparison_roc_sklearn_vs_tmva_2lss1tau_8Var_wCuts_wFrWt.png");

  vector<TString> filenames_2lss_1tau_wCuts_frWt;
  filenames_2lss_1tau_wCuts_frWt.push_back("/home/arun/VHbbNtuples_7_6_x/CMSSW_7_6_3_for8X/src/tthAnalysis/HiggsToTauTau/test/weights_2lss_1tau_wCuts_8Var_oldset_03Mar2017/trainTTHMVA_2lss_1tau_03Mar17.root");
  filenames_2lss_1tau_wCuts_frWt.push_back("training_fastsim_v2_03Mar2017_wCuts_frWt/2lss_1tau_performance_maxDepth3_8Var_oldset_frWt.root");
  vector<TString> histDirs_2lss_1tau_wCuts_frWt;
  histDirs_2lss_1tau_wCuts_frWt.push_back("Method_BDT/BDTG/");
  histDirs_2lss_1tau_wCuts_frWt.push_back("");
  vector<TString> mvatype;
  mvatype.push_back("TMVA");
  mvatype.push_back("SKLEARN");
  vector<TString> legends_2lss_1tau_wCuts_frWt;
  legends_2lss_1tau_wCuts_frWt.push_back("tmva-8Var-wCuts-wFrWt");
  legends_2lss_1tau_wCuts_frWt.push_back("sklearn-8Var-wCuts-wFrWt");
  compareROC(filenames_2lss_1tau_wCuts_frWt,histDirs_2lss_1tau_wCuts_frWt,mvatype,legends_2lss_1tau_wCuts_frWt,"plots","comparison_roc_sklearn_vs_tmva_2lss1tau_8Var_oldset_wCuts_wFrWt.png");
  */
  /*
  vector<TString> filenames_2lss_1tau_wCuts_frWt;
  filenames_2lss_1tau_wCuts_frWt.push_back("/home/arun/VHbbNtuples_7_6_x/CMSSW_7_6_3_for8X/src/tthAnalysis/HiggsToTauTau/test/training_2lss_1tau_TTV/weights_2lss_1tau_TTV_wCuts_10Var_15Mar2017/trainTTHMVA_2lss_1tau_TTV_07Mar17_10Var_wfrWt.root");
  filenames_2lss_1tau_wCuts_frWt.push_back("training_fastsim_v2_03Mar2017_wCuts_frWt/2lss_1tau_ttV_performance_maxDepth3_10Var_frWt.root");
  filenames_2lss_1tau_wCuts_frWt.push_back("training_fastsim_v1_22Feb17_frWt/results/2lss_1tau_ttV_performance_maxDepth3_10Var_frWt.root");
  vector<TString> histDirs_2lss_1tau_wCuts_frWt;
  histDirs_2lss_1tau_wCuts_frWt.push_back("Method_BDT/BDTG/");
  histDirs_2lss_1tau_wCuts_frWt.push_back("");
  histDirs_2lss_1tau_wCuts_frWt.push_back("");
  vector<TString> mvatype;
  mvatype.push_back("TMVA");
  mvatype.push_back("SKLEARN");
  mvatype.push_back("SKLEARN");
  vector<TString> legends_2lss_1tau_wCuts_frWt;
  legends_2lss_1tau_wCuts_frWt.push_back("tmva-10Var-wCuts-wFrWt");
  legends_2lss_1tau_wCuts_frWt.push_back("sklearn-10Var-wCuts-wFrWt");
  legends_2lss_1tau_wCuts_frWt.push_back("sklearn-10Var-woCuts-wFrWt");
  compareROC(filenames_2lss_1tau_wCuts_frWt,histDirs_2lss_1tau_wCuts_frWt,mvatype,legends_2lss_1tau_wCuts_frWt,"plots","comparison_roc_sklearn_vs_tmva_2lss1tau_ttV_10Var_wCuts_wFrWt.png");
  */
  /*
  vector<TString> filenames_2lss_1tau_wCuts_frWt;
  filenames_2lss_1tau_wCuts_frWt.push_back("training_fastsim_v2_28Mar2017_wCuts_frWt_mem/2lss_1tau_performance_maxDepth3_allVar_frWt_woMEM.root");
  filenames_2lss_1tau_wCuts_frWt.push_back("training_fastsim_v2_28Mar2017_wCuts_frWt_mem/2lss_1tau_performance_maxDepth3_8Var_frWt_woMEM.root");
  filenames_2lss_1tau_wCuts_frWt.push_back("training_fastsim_v2_28Mar2017_wCuts_frWt_mem/2lss_1tau_performance_maxDepth3_8Var_frWt_wMEM.root");
  filenames_2lss_1tau_wCuts_frWt.push_back("training_fastsim_v2_28Mar2017_wCuts_frWt_mem/2lss_1tau_performance_maxDepth3_8Var_frWt_wMEMall.root");
  vector<TString> histDirs_2lss_1tau_wCuts_frWt;
  histDirs_2lss_1tau_wCuts_frWt.push_back("");
  histDirs_2lss_1tau_wCuts_frWt.push_back("");
  histDirs_2lss_1tau_wCuts_frWt.push_back("");
  histDirs_2lss_1tau_wCuts_frWt.push_back("");
  vector<TString> mvatype;
  mvatype.push_back("SKLEARN");
  mvatype.push_back("SKLEARN");
  mvatype.push_back("SKLEARN");
  mvatype.push_back("SKLEARN");
  vector<TString> legends_2lss_1tau_wCuts_frWt;
  legends_2lss_1tau_wCuts_frWt.push_back("allVar-wCuts-wFrWt");
  legends_2lss_1tau_wCuts_frWt.push_back("8Var-wCuts-wFrWt");
  legends_2lss_1tau_wCuts_frWt.push_back("8Var-wCuts-wFrWt_wMEM");
  legends_2lss_1tau_wCuts_frWt.push_back("8Var-wCuts-wFrWt_wMEMLR");
  compareROC(filenames_2lss_1tau_wCuts_frWt,histDirs_2lss_1tau_wCuts_frWt,mvatype,legends_2lss_1tau_wCuts_frWt,"plots", "comparison_roc_sklearn_2lss1tau_wCuts_wFrWt_wMEM.png");
  */
  /*
  vector<TString> filenames_2lss_1tau_wCuts_frWt;
  filenames_2lss_1tau_wCuts_frWt.push_back("training_fastsim_v2_28Mar2017_wCuts_frWt_mem/2lss_1tau_performance_maxDepth3_allVar_frWt_woMEM.root");
  filenames_2lss_1tau_wCuts_frWt.push_back("training_fastsim_v2_28Mar2017_wCuts_frWt_mem/2lss_1tau_performance_maxDepth3_8Var_frWt_woMEM.root");
  filenames_2lss_1tau_wCuts_frWt.push_back("training_fastsim_v2_03Mar2017_wCuts_frWt/2lss_1tau_performance_maxDepth3_allVar_frWt.root");
  filenames_2lss_1tau_wCuts_frWt.push_back("training_fastsim_v2_03Mar2017_wCuts_frWt/2lss_1tau_performance_maxDepth3_8Var_frWt.root");  
  vector<TString> histDirs_2lss_1tau_wCuts_frWt;
  histDirs_2lss_1tau_wCuts_frWt.push_back("");
  histDirs_2lss_1tau_wCuts_frWt.push_back("");
  histDirs_2lss_1tau_wCuts_frWt.push_back("");
  histDirs_2lss_1tau_wCuts_frWt.push_back("");
  vector<TString> mvatype;
  mvatype.push_back("SKLEARN");
  mvatype.push_back("SKLEARN");
  mvatype.push_back("SKLEARN");
  mvatype.push_back("SKLEARN");
  vector<TString> legends_2lss_1tau_wCuts_frWt;
  legends_2lss_1tau_wCuts_frWt.push_back("allVar-wCuts-wFrWt");
  legends_2lss_1tau_wCuts_frWt.push_back("8Var-wCuts-wFrWt");
  legends_2lss_1tau_wCuts_frWt.push_back("allVar-wCuts-wFrWt_old");
  legends_2lss_1tau_wCuts_frWt.push_back("8Var-wCuts-wFrWt_old");
  compareROC(filenames_2lss_1tau_wCuts_frWt,histDirs_2lss_1tau_wCuts_frWt,mvatype,legends_2lss_1tau_wCuts_frWt,"plots", "comparison_roc_sklearn_2lss1tau_wCuts_wFrWt_oldVsnew.png");
  */
  /*
  vector<TString> filenames_2lss_1tau_wCuts_frWt;
  filenames_2lss_1tau_wCuts_frWt.push_back("/home/arun/VHbbNtuples_8_0_x/CMSSW_8_0_21/src/tthAnalysis/HiggsToTauTau/test/training_2lss_1tau_TT/weights_2lss_1tau_wCuts_allVar_woMEM_28Mar2017/trainTTHMVA_2lss_1tau_28Mar17_allVar_wfrWt_woMEM.root");
  filenames_2lss_1tau_wCuts_frWt.push_back("/home/arun/VHbbNtuples_8_0_x/CMSSW_8_0_21/src/tthAnalysis/HiggsToTauTau/test/training_2lss_1tau_TT/weights_2lss_1tau_wCuts_8Var_woMEM_28Mar2017/trainTTHMVA_2lss_1tau_28Mar17_8Var_wfrWt.root");
  filenames_2lss_1tau_wCuts_frWt.push_back("/home/arun/VHbbNtuples_8_0_x/CMSSW_8_0_21/src/tthAnalysis/HiggsToTauTau/test/training_2lss_1tau_TT/weights_2lss_1tau_wCuts_8Var_wMEM_28Mar2017/trainTTHMVA_2lss_1tau_28Mar17_8Var_wfrWt_wMEM.root");
  filenames_2lss_1tau_wCuts_frWt.push_back("/home/arun/VHbbNtuples_8_0_x/CMSSW_8_0_21/src/tthAnalysis/HiggsToTauTau/test/training_2lss_1tau_TT/weights_2lss_1tau_wCuts_8Var_wMEMall_28Mar2017/trainTTHMVA_2lss_1tau_28Mar17_8Var_wfrWt_wMEMall.root");
  vector<TString> histDirs_2lss_1tau_wCuts_frWt;
  histDirs_2lss_1tau_wCuts_frWt.push_back("Method_BDT/BDTG/");
  histDirs_2lss_1tau_wCuts_frWt.push_back("Method_BDT/BDTG/");
  histDirs_2lss_1tau_wCuts_frWt.push_back("Method_BDT/BDTG/");
  histDirs_2lss_1tau_wCuts_frWt.push_back("Method_BDT/BDTG/");
  vector<TString> mvatype;
  mvatype.push_back("TMVA");
  mvatype.push_back("TMVA");
  mvatype.push_back("TMVA");
  mvatype.push_back("TMVA");
  vector<TString> legends_2lss_1tau_wCuts_frWt;
  legends_2lss_1tau_wCuts_frWt.push_back("allVar-wCuts-wFrWt");
  legends_2lss_1tau_wCuts_frWt.push_back("8Var-wCuts-wFrWt");
  legends_2lss_1tau_wCuts_frWt.push_back("8Var-wCuts-wFrWt_wMEM");
  legends_2lss_1tau_wCuts_frWt.push_back("8Var-wCuts-wFrWt_wMEMLR");
  compareROC(filenames_2lss_1tau_wCuts_frWt,histDirs_2lss_1tau_wCuts_frWt,mvatype,legends_2lss_1tau_wCuts_frWt,"plots", "comparison_roc_tmva_2lss1tau_wCuts_wFrWt_wMEM.png");
  */
  /*
  vector<TString> filenames_2lss_1tau_wCuts_frWt;
  filenames_2lss_1tau_wCuts_frWt.push_back("/home/arun/VHbbNtuples_8_0_x/CMSSW_8_0_21/src/tthAnalysis/HiggsToTauTau/test/training_2lss_1tau_TT/weights_2lss_1tau_wCuts_allVar_woMEM_28Mar2017/trainTTHMVA_2lss_1tau_28Mar17_allVar_wfrWt_woMEM.root");
  filenames_2lss_1tau_wCuts_frWt.push_back("/home/arun/VHbbNtuples_8_0_x/CMSSW_8_0_21/src/tthAnalysis/HiggsToTauTau/test/training_2lss_1tau_TT/weights_2lss_1tau_wCuts_8Var_woMEM_28Mar2017/trainTTHMVA_2lss_1tau_28Mar17_8Var_wfrWt.root");
  filenames_2lss_1tau_wCuts_frWt.push_back("/home/arun/VHbbNtuples_7_6_x/CMSSW_7_6_3_for8X/src/tthAnalysis/HiggsToTauTau/test/training_2lss_1tau_TT/weights_2lss_1tau_wCuts_allVar_07Mar2017/trainTTHMVA_2lss_1tau_07Mar17_allVar_wfrWt.root");
  filenames_2lss_1tau_wCuts_frWt.push_back("/home/arun/VHbbNtuples_7_6_x/CMSSW_7_6_3_for8X/src/tthAnalysis/HiggsToTauTau/test/training_2lss_1tau_TT/weights_2lss_1tau_wCuts_8Var_07Mar2017/trainTTHMVA_2lss_1tau_07Mar17_8Var_wfrWt.root");
  vector<TString> histDirs_2lss_1tau_wCuts_frWt;
  histDirs_2lss_1tau_wCuts_frWt.push_back("Method_BDT/BDTG/");
  histDirs_2lss_1tau_wCuts_frWt.push_back("Method_BDT/BDTG/");
  histDirs_2lss_1tau_wCuts_frWt.push_back("Method_BDT/BDTG/");
  histDirs_2lss_1tau_wCuts_frWt.push_back("Method_BDT/BDTG/");
  vector<TString> mvatype;
  mvatype.push_back("TMVA");
  mvatype.push_back("TMVA");
  mvatype.push_back("TMVA");
  mvatype.push_back("TMVA");
  vector<TString> legends_2lss_1tau_wCuts_frWt;
  legends_2lss_1tau_wCuts_frWt.push_back("allVar-wCuts-wFrWt");
  legends_2lss_1tau_wCuts_frWt.push_back("8Var-wCuts-wFrWt");
  legends_2lss_1tau_wCuts_frWt.push_back("allVar-wCuts-wFrWt-old");
  legends_2lss_1tau_wCuts_frWt.push_back("8Var-wCuts-wFrWt-old");
  compareROC(filenames_2lss_1tau_wCuts_frWt,histDirs_2lss_1tau_wCuts_frWt,mvatype,legends_2lss_1tau_wCuts_frWt,"plots", "comparison_roc_tmva_2lss1tau_wCuts_wFrWt_oldVsnew.png");
  */
  /*
  vector<TString> filenames_2lss_1tau_wCuts_frWt;
  filenames_2lss_1tau_wCuts_frWt.push_back("training_fastsim_v2_28Mar2017_wCuts_frWt_mem/2lss_1tau_ttV_performance_maxDepth3_10Var_frWt_woMEM.root");
  filenames_2lss_1tau_wCuts_frWt.push_back("training_fastsim_v2_28Mar2017_wCuts_frWt_mem/2lss_1tau_ttV_performance_maxDepth3_10Var_frWt_wMEM.root");
  filenames_2lss_1tau_wCuts_frWt.push_back("training_fastsim_v2_28Mar2017_wCuts_frWt_mem/2lss_1tau_ttV_performance_maxDepth3_10Var_frWt_wMEMall.root");
  vector<TString> histDirs_2lss_1tau_wCuts_frWt;
  histDirs_2lss_1tau_wCuts_frWt.push_back("");
  histDirs_2lss_1tau_wCuts_frWt.push_back("");
  histDirs_2lss_1tau_wCuts_frWt.push_back("");
  vector<TString> mvatype;
  mvatype.push_back("SKLEARN");
  mvatype.push_back("SKLEARN");
  mvatype.push_back("SKLEARN");
  vector<TString> legends_2lss_1tau_wCuts_frWt;
  legends_2lss_1tau_wCuts_frWt.push_back("sklearn-10Var-wCuts-wFrWt_woMEM");
  legends_2lss_1tau_wCuts_frWt.push_back("sklearn-10Var-wCuts-wFrWt_wMEM");
  legends_2lss_1tau_wCuts_frWt.push_back("sklearn-10Var-wCuts-wFrWt_wMEMLR");
  compareROC(filenames_2lss_1tau_wCuts_frWt,histDirs_2lss_1tau_wCuts_frWt,mvatype,legends_2lss_1tau_wCuts_frWt,"plots","comparison_roc_sklearn_2lss1tau_ttV_10Var_wCuts_wFrWt_wMEM.png");
  */
  /*
  vector<TString> filenames_2lss_1tau_wCuts_frWt;
  filenames_2lss_1tau_wCuts_frWt.push_back("/home/arun/VHbbNtuples_8_0_x/CMSSW_8_0_21/src/tthAnalysis/HiggsToTauTau/test/training_2lss_1tau_TTV/weights_2lss_1tau_TTV_wCuts_10Var_wfrWt_woMEM_28Mar2017/trainTTHMVA_2lss_1tau_TTV_28Mar17_10Var_wfrWt_woMEM.root");
  filenames_2lss_1tau_wCuts_frWt.push_back("/home/arun/VHbbNtuples_8_0_x/CMSSW_8_0_21/src/tthAnalysis/HiggsToTauTau/test/training_2lss_1tau_TTV/weights_2lss_1tau_TTV_wCuts_10Var_wfrWt_wMEM_28Mar2017/trainTTHMVA_2lss_1tau_TTV_28Mar17_10Var_wfrWt_wMEM.root");
  filenames_2lss_1tau_wCuts_frWt.push_back("/home/arun/VHbbNtuples_8_0_x/CMSSW_8_0_21/src/tthAnalysis/HiggsToTauTau/test/training_2lss_1tau_TTV/weights_2lss_1tau_TTV_wCuts_10Var_wfrWt_wMEMall_28Mar2017/trainTTHMVA_2lss_1tau_TTV_28Mar17_10Var_wfrWt_wMEMall.root");
  vector<TString> histDirs_2lss_1tau_wCuts_frWt;
  histDirs_2lss_1tau_wCuts_frWt.push_back("Method_BDT/BDTG/");
  histDirs_2lss_1tau_wCuts_frWt.push_back("Method_BDT/BDTG/");
  histDirs_2lss_1tau_wCuts_frWt.push_back("Method_BDT/BDTG/");
  vector<TString> mvatype;
  mvatype.push_back("TMVA");
  mvatype.push_back("TMVA");
  mvatype.push_back("TMVA");
  vector<TString> legends_2lss_1tau_wCuts_frWt;
  legends_2lss_1tau_wCuts_frWt.push_back("tmva-10Var-wCuts-wFrWt_woMEM");
  legends_2lss_1tau_wCuts_frWt.push_back("tmva-10Var-wCuts-wFrWt_wMEM");
  legends_2lss_1tau_wCuts_frWt.push_back("tmva-10Var-wCuts-wFrWt_wMEMLR");

  compareROC(filenames_2lss_1tau_wCuts_frWt,histDirs_2lss_1tau_wCuts_frWt,mvatype,legends_2lss_1tau_wCuts_frWt,"plots","comparison_roc_tmva_2lss1tau_ttV_10Var_wCuts_wFrWt_wMEM.png");
  */
  /*
  vector<TString> filenames_3l_1tau_tt;
  filenames_3l_1tau_tt.push_back("training_3l1t_fastsim_30Mar2017_frWt/3l_1tau_performance_maxDepth3_allVar_frWt.root");
  filenames_3l_1tau_tt.push_back("training_3l1t_fastsim_30Mar2017_frWt/3l_1tau_performance_maxDepth3_15Var_frWt.root");
  filenames_3l_1tau_tt.push_back("training_3l1t_fastsim_30Mar2017_frWt/3l_1tau_performance_maxDepth3_8Var_frWt.root");
  vector<TString>histDirs_3l_1tau_tt;
  histDirs_3l_1tau_tt.push_back("");
  histDirs_3l_1tau_tt.push_back("");
  histDirs_3l_1tau_tt.push_back("");
  vector<TString>mvatype;
  mvatype.push_back("SKLEARN");
  mvatype.push_back("SKLEARN");
  mvatype.push_back("SKLEARN");
  vector<TString>legends_3l_1tau_tt;
  legends_3l_1tau_tt.push_back("sklearn-25Var-wFrWt");
  legends_3l_1tau_tt.push_back("sklearn-15Var-wFrWt");
  legends_3l_1tau_tt.push_back("sklearn-8Var-wFrWt");
  compareROC(filenames_3l_1tau_tt, histDirs_3l_1tau_tt, mvatype, legends_3l_1tau_tt, "plots", "comparison_roc_sklearn_3l1tau_wFrWt.png");
  */
  /*
  vector<TString> filenames_3l_1tau_tt;
  filenames_3l_1tau_tt.push_back("/home/arun/VHbbNtuples_8_0_x/CMSSW_8_0_21/src/tthAnalysis/HiggsToTauTau/test/training_3l_1tau_TT/weight_fastsim_30Mar2017_allVar_frWt/trainTTHMVA_3l_1tau_01Apr17_allVar_wfrWt.root");
  filenames_3l_1tau_tt.push_back("/home/arun/VHbbNtuples_8_0_x/CMSSW_8_0_21/src/tthAnalysis/HiggsToTauTau/test/training_3l_1tau_TT/weight_fastsim_30Mar2017_15Var_frWt/trainTTHMVA_3l_1tau_01Apr17_15Var_wfrWt.root");
  filenames_3l_1tau_tt.push_back("/home/arun/VHbbNtuples_8_0_x/CMSSW_8_0_21/src/tthAnalysis/HiggsToTauTau/test/training_3l_1tau_TT/weight_fastsim_30Mar2017_10Var_frWt/trainTTHMVA_3l_1tau_01Apr17_10Var_wfrWt.root");
  vector<TString>histDirs_3l_1tau_tt;
  histDirs_3l_1tau_tt.push_back("Method_BDT/BDTG/");
  histDirs_3l_1tau_tt.push_back("Method_BDT/BDTG/");
  histDirs_3l_1tau_tt.push_back("Method_BDT/BDTG/");
  vector<TString>mvatype;
  mvatype.push_back("TMVA");
  mvatype.push_back("TMVA");
  mvatype.push_back("TMVA");
  vector<TString>legends_3l_1tau_tt;
  legends_3l_1tau_tt.push_back("tmva-25Var-wFrWt");
  legends_3l_1tau_tt.push_back("tmva-15Var-wFrWt");
  legends_3l_1tau_tt.push_back("tmva-10Var-wFrWt");
  compareROC(filenames_3l_1tau_tt, histDirs_3l_1tau_tt, mvatype, legends_3l_1tau_tt, "plots", "comparison_roc_tmva_3l1tau_wFrWt.png");
  */
  /*
  vector<TString> filenames_3l_1tau_tt;
  filenames_3l_1tau_tt.push_back("/home/arun/VHbbNtuples_8_0_x/CMSSW_8_0_21/src/tthAnalysis/HiggsToTauTau/test/training_3l_1tau_TT/weight_fastsim_30Mar2017_10Var_frWt/trainTTHMVA_3l_1tau_01Apr17_10Var_wfrWt.root");
  filenames_3l_1tau_tt.push_back("training_3l1t_fastsim_30Mar2017_frWt/3l_1tau_performance_maxDepth3_8Var_frWt.root");
  vector<TString>histDirs_3l_1tau_tt;
  histDirs_3l_1tau_tt.push_back("Method_BDT/BDTG/");
  histDirs_3l_1tau_tt.push_back("");
  vector<TString>mvatype;
  mvatype.push_back("TMVA");
  mvatype.push_back("SKLEARN");
  vector<TString>legends_3l_1tau_tt;
  legends_3l_1tau_tt.push_back("tmva-10Var-wFrWt");
  legends_3l_1tau_tt.push_back("sklearn-8Var-wFrWt");
  compareROC(filenames_3l_1tau_tt, histDirs_3l_1tau_tt, mvatype, legends_3l_1tau_tt, "plots", "comparison_roc_sklearn_vs_tmva_3l1tau_10Var_wFrWt.png");
  */
  /*
  vector<TString> filenames_3l_1tau_ttV;
  filenames_3l_1tau_ttV.push_back("training_3l1t_fastsim_30Mar2017_frWt/3l_1tau_ttV_performance_maxDepth3_allVar_frWt.root");
  filenames_3l_1tau_ttV.push_back("training_3l1t_fastsim_30Mar2017_frWt/3l_1tau_ttV_performance_maxDepth3_21Var_frWt.root");
  filenames_3l_1tau_ttV.push_back("training_3l1t_fastsim_30Mar2017_frWt/3l_1tau_ttV_performance_maxDepth3_12Var_frWt.root");
  vector<TString>histDirs_3l_1tau_ttV;
  histDirs_3l_1tau_ttV.push_back("");
  histDirs_3l_1tau_ttV.push_back("");
  histDirs_3l_1tau_ttV.push_back("");
  vector<TString>mvatype;
  mvatype.push_back("SKLEARN");
  mvatype.push_back("SKLEARN");
  mvatype.push_back("SKLEARN");
  vector<TString>legends_3l_1tau_ttV;
  legends_3l_1tau_ttV.push_back("sklearn-25Var-wFrWt");
  legends_3l_1tau_ttV.push_back("sklearn-21Var-wFrWt");
  legends_3l_1tau_ttV.push_back("sklearn-12Var-wFrWt");
  compareROC(filenames_3l_1tau_ttV, histDirs_3l_1tau_ttV, mvatype, legends_3l_1tau_ttV, "plots", "comparison_roc_sklearn_3l1tau_ttV_wFrWt.png");
  */
  /*
  vector<TString> filenames_3l_1tau_ttV;
  filenames_3l_1tau_ttV.push_back("/home/arun/VHbbNtuples_8_0_x/CMSSW_8_0_21/src/tthAnalysis/HiggsToTauTau/test/training_3l_1tau_TTV/weight_fastsim_ttV_01Apr2017_allVar_frWt/trainTTHMVA_3l_1tau_ttV_01Apr17_allVar_wfrWt.root");
  filenames_3l_1tau_ttV.push_back("/home/arun/VHbbNtuples_8_0_x/CMSSW_8_0_21/src/tthAnalysis/HiggsToTauTau/test/training_3l_1tau_TTV/weight_fastsim_ttV_01Apr2017_12Var_frWt/trainTTHMVA_3l_1tau_ttV_01Apr17_12Var_wfrWt.root");
  vector<TString>histDirs_3l_1tau_ttV;
  histDirs_3l_1tau_ttV.push_back("Method_BDT/BDTG/");
  histDirs_3l_1tau_ttV.push_back("Method_BDT/BDTG/");
  vector<TString>mvatype;
  mvatype.push_back("TMVA");
  mvatype.push_back("TMVA");
  vector<TString>legends_3l_1tau_ttV;
  legends_3l_1tau_ttV.push_back("tmva-25Var-wFrWt");
  legends_3l_1tau_ttV.push_back("tmva-12Var-wFrWt");
  compareROC(filenames_3l_1tau_ttV, histDirs_3l_1tau_ttV, mvatype, legends_3l_1tau_ttV, "plots", "comparison_roc_tmva_3l1tau_ttV_wFrWt.png");
  */
  /*
  vector<TString> filenames_3l_1tau_ttV;
  filenames_3l_1tau_ttV.push_back("/home/arun/VHbbNtuples_8_0_x/CMSSW_8_0_21/src/tthAnalysis/HiggsToTauTau/test/training_3l_1tau_TTV/weight_fastsim_ttV_01Apr2017_12Var_frWt/trainTTHMVA_3l_1tau_ttV_01Apr17_12Var_wfrWt.root");
  filenames_3l_1tau_ttV.push_back("training_3l1t_fastsim_30Mar2017_frWt/3l_1tau_ttV_performance_maxDepth3_12Var_frWt.root");
  vector<TString>histDirs_3l_1tau_ttV;
  histDirs_3l_1tau_ttV.push_back("Method_BDT/BDTG/");
  histDirs_3l_1tau_ttV.push_back("");
  vector<TString>mvatype;
  mvatype.push_back("TMVA");
  mvatype.push_back("SKLEARN");
  vector<TString>legends_3l_1tau_ttV;
  legends_3l_1tau_ttV.push_back("tmva-12Var-wFrWt");
  legends_3l_1tau_ttV.push_back("sklearn-12Var-wFrWt");
  compareROC(filenames_3l_1tau_ttV, histDirs_3l_1tau_ttV, mvatype, legends_3l_1tau_ttV, "plots", "comparison_roc_sklearn_vs_tmva_3l1tau_ttV_12Var_wFrWt.png");
  */
  /*
  vector<TString> filenames_3l_1tau_tt;
  filenames_3l_1tau_tt.push_back("/home/arun/VHbbNtuples_8_0_x/CMSSW_8_0_21/src/tthAnalysis/HiggsToTauTau/test/training_3l_1tau_TT/weight_fastsim_30Mar2017_10Var_frWt/trainTTHMVA_3l_1tau_01Apr17_10Var_wfrWt.root");
  filenames_3l_1tau_tt.push_back("/home/arun/VHbbNtuples_8_0_x/CMSSW_8_0_21/src/tthAnalysis/HiggsToTauTau/test/training_3l_1tau_TT/weight_fastsim_04Apr17_10Var_wfrWt_sigTauTight/trainTTHMVA_3l_1tau_04Apr17_10Var_wfrWt_sigTauTight.root");
  filenames_3l_1tau_tt.push_back("/home/arun/VHbbNtuples_8_0_x/CMSSW_8_0_21/src/tthAnalysis/HiggsToTauTau/test/training_3l_1tau_TT/weight_fastsim_04Apr17_10VarNew_wfrWt_sigTauTight/trainTTHMVA_3l_1tau_04Apr17_10Var_wfrWt_sigTauTight.root");
  vector<TString>histDirs_3l_1tau_tt;
  histDirs_3l_1tau_tt.push_back("Method_BDT/BDTG/");
  histDirs_3l_1tau_tt.push_back("Method_BDT/BDTG/");
  histDirs_3l_1tau_tt.push_back("Method_BDT/BDTG/");
  vector<TString>mvatype;
  mvatype.push_back("TMVA");
  mvatype.push_back("TMVA");
  mvatype.push_back("TMVA");
  vector<TString>legends_3l_1tau_tt;
  legends_3l_1tau_tt.push_back("tmva-10Var-wFrWt-mvaVVLoose");
  legends_3l_1tau_tt.push_back("tmva-10Var-wFrWt-mvaMedium");
  legends_3l_1tau_tt.push_back("tmva-10VarNew-wFrWt-mvaMedium");
  compareROC(filenames_3l_1tau_tt, histDirs_3l_1tau_tt, mvatype, legends_3l_1tau_tt, "plots", "comparison_roc_tmva_3l1tau_wFrWt_tauMvaMedium.png");
  */
  /*
  vector<TString> filenames_3l_1tau_ttV;
  filenames_3l_1tau_ttV.push_back("/home/arun/VHbbNtuples_8_0_x/CMSSW_8_0_21/src/tthAnalysis/HiggsToTauTau/test/training_3l_1tau_TTV/weight_fastsim_ttV_01Apr2017_12Var_frWt/trainTTHMVA_3l_1tau_ttV_01Apr17_12Var_wfrWt.root");
  filenames_3l_1tau_ttV.push_back("/home/arun/VHbbNtuples_8_0_x/CMSSW_8_0_21/src/tthAnalysis/HiggsToTauTau/test/training_3l_1tau_TTV/weight_fastsim_ttV_04Apr2017_12Var_frWt_sigTauTight/trainTTHMVA_3l_1tau_ttV_04Apr17_12Var_wfrWt_tauMvaTight.root");
  filenames_3l_1tau_ttV.push_back("/home/arun/VHbbNtuples_8_0_x/CMSSW_8_0_21/src/tthAnalysis/HiggsToTauTau/test/training_3l_1tau_TTV/weight_fastsim_ttV_04Apr2017_12VarNew_frWt_sigTauTight/trainTTHMVA_3l_1tau_ttV_04Apr17_12VarNew_wfrWt_tauMvaTight.root");
  vector<TString>histDirs_3l_1tau_ttV;
  histDirs_3l_1tau_ttV.push_back("Method_BDT/BDTG/");
  histDirs_3l_1tau_ttV.push_back("Method_BDT/BDTG/");
  histDirs_3l_1tau_ttV.push_back("Method_BDT/BDTG/");
  vector<TString>mvatype;
  mvatype.push_back("TMVA");
  mvatype.push_back("TMVA");
  mvatype.push_back("TMVA");
  vector<TString>legends_3l_1tau_ttV;
  legends_3l_1tau_ttV.push_back("tmva-12Var-wFrWt-mvaVVLoose");
  legends_3l_1tau_ttV.push_back("tmva-12Var-wFrWt-mvaMedium");
  legends_3l_1tau_ttV.push_back("tmva-12VarNew-wFrWt-mvaMedium");
  compareROC(filenames_3l_1tau_ttV, histDirs_3l_1tau_ttV, mvatype, legends_3l_1tau_ttV, "plots", "comparison_roc_tmva_3l1tau_ttV_wFrWt_tauMvaMedium.png");
  */
  /*
  vector<TString> filenames_2lss_1tau_wCuts_frWt;
  filenames_2lss_1tau_wCuts_frWt.push_back("/home/arun/VHbbNtuples_8_0_x/CMSSW_8_0_21/src/tthAnalysis/HiggsToTauTau/test/training_2lss_1tau_TT/weights_2lss_1tau_wCuts_8Var_woMEM_07Apr2017/trainTTHMVA_2lss_1tau_07Apr17_8Var_wfrWt_woMEM.root");
  filenames_2lss_1tau_wCuts_frWt.push_back("/home/arun/VHbbNtuples_8_0_x/CMSSW_8_0_21/src/tthAnalysis/HiggsToTauTau/test/training_2lss_1tau_TT/weights_2lss_1tau_wCuts_8Var_wMEMLR_07Apr2017/trainTTHMVA_2lss_1tau_07Apr17_8Var_wfrWt_wMEMLR.root");
  filenames_2lss_1tau_wCuts_frWt.push_back("/home/arun/VHbbNtuples_8_0_x/CMSSW_8_0_21/src/tthAnalysis/HiggsToTauTau/test/training_2lss_1tau_TT/weights_2lss_1tau_wCuts_8Var_wMEMttLR_07Apr2017/trainTTHMVA_2lss_1tau_07Apr17_8Var_wfrWt_wMEMttLR.root");
  vector<TString> histDirs_2lss_1tau_wCuts_frWt;
  histDirs_2lss_1tau_wCuts_frWt.push_back("Method_BDT/BDTG/");
  histDirs_2lss_1tau_wCuts_frWt.push_back("Method_BDT/BDTG/");
  histDirs_2lss_1tau_wCuts_frWt.push_back("Method_BDT/BDTG/");
  vector<TString> mvatype;
  mvatype.push_back("TMVA");
  mvatype.push_back("TMVA");
  mvatype.push_back("TMVA");
  vector<TString> legends_2lss_1tau_wCuts_frWt;
  legends_2lss_1tau_wCuts_frWt.push_back("8Var-wCuts-wFrWt");
  legends_2lss_1tau_wCuts_frWt.push_back("8Var-wCuts-wFrWt_wMEM_LR");
  legends_2lss_1tau_wCuts_frWt.push_back("8Var-wCuts-wFrWt_wMEM_ttLR");
  compareROC(filenames_2lss_1tau_wCuts_frWt,histDirs_2lss_1tau_wCuts_frWt,mvatype,legends_2lss_1tau_wCuts_frWt,"plots", "comparison_roc_tmva_2lss1tau_wCuts_wFrWt_wMEM_ttLR_07Apr.png");
  */
  /*
  vector<TString> filenames_2lss_1tau_wCuts_frWt;
  filenames_2lss_1tau_wCuts_frWt.push_back("/home/arun/VHbbNtuples_8_0_x/CMSSW_8_0_21/src/tthAnalysis/HiggsToTauTau/test/training_2lss_1tau_TTV/weights_2lss_1tau_TTV_wCuts_10Var_wfrWt_woMEM_07Apr2017/trainTTHMVA_2lss_1tau_TTV_07Apr17_10Var_wfrWt_woMEM.root");
  filenames_2lss_1tau_wCuts_frWt.push_back("/home/arun/VHbbNtuples_8_0_x/CMSSW_8_0_21/src/tthAnalysis/HiggsToTauTau/test/training_2lss_1tau_TTV/weights_2lss_1tau_TTV_wCuts_10Var_wfrWt_wMEMLR_07Apr2017/trainTTHMVA_2lss_1tau_TTV_07Apr17_10Var_wfrWt_wMEMLR.root");
  filenames_2lss_1tau_wCuts_frWt.push_back("/home/arun/VHbbNtuples_8_0_x/CMSSW_8_0_21/src/tthAnalysis/HiggsToTauTau/test/training_2lss_1tau_TTV/weights_2lss_1tau_TTV_wCuts_10Var_wfrWt_wMEMttZLR_07Apr2017/trainTTHMVA_2lss_1tau_TTV_07Apr17_10Var_wfrWt_wMEMttZLR.root");
  vector<TString> histDirs_2lss_1tau_wCuts_frWt;
  histDirs_2lss_1tau_wCuts_frWt.push_back("Method_BDT/BDTG/");
  histDirs_2lss_1tau_wCuts_frWt.push_back("Method_BDT/BDTG/");
  histDirs_2lss_1tau_wCuts_frWt.push_back("Method_BDT/BDTG/");
  vector<TString> mvatype;
  mvatype.push_back("TMVA");
  mvatype.push_back("TMVA");
  mvatype.push_back("TMVA");
  vector<TString> legends_2lss_1tau_wCuts_frWt;
  legends_2lss_1tau_wCuts_frWt.push_back("tmva-10Var-wCuts-wFrWt_woMEM");
  legends_2lss_1tau_wCuts_frWt.push_back("tmva-10Var-wCuts-wFrWt_wMEM_LR");
  legends_2lss_1tau_wCuts_frWt.push_back("tmva-10Var-wCuts-wFrWt_wMEM_ttZLR");
  compareROC(filenames_2lss_1tau_wCuts_frWt,histDirs_2lss_1tau_wCuts_frWt,mvatype,legends_2lss_1tau_wCuts_frWt,"plots","comparison_roc_tmva_2lss1tau_ttV_10Var_wCuts_wFrWt_wMEM_ttZLR_07Apr.png");
  */
  /*
  vector<TString> filenames_3l_1tau_tt;
  filenames_3l_1tau_tt.push_back("/home/arun/VHbbNtuples_8_0_x/CMSSW_8_0_21/src/tthAnalysis/HiggsToTauTau/test/training_3l_1tau_TT/weight_fastsim_06Apr17_allVar_wfrWt_sigTauTight_njet1/trainTTHMVA_3l_1tau_06Apr17_allVar_wfrWt_sigTauTight_njet1.root");
  filenames_3l_1tau_tt.push_back("/home/arun/VHbbNtuples_8_0_x/CMSSW_8_0_21/src/tthAnalysis/HiggsToTauTau/test/training_3l_1tau_TT/weight_fastsim_06Apr17_12Var_wfrWt_sigTauTight_njet1/trainTTHMVA_3l_1tau_06Apr17_12Var_wfrWt_sigTauTight_njet1.root");
  vector<TString>histDirs_3l_1tau_tt;
  histDirs_3l_1tau_tt.push_back("Method_BDT/BDTG/");
  histDirs_3l_1tau_tt.push_back("Method_BDT/BDTG/");
  vector<TString>mvatype;
  mvatype.push_back("TMVA");
  mvatype.push_back("TMVA");
  vector<TString>legends_3l_1tau_tt;
  legends_3l_1tau_tt.push_back("tmva-allVar-wFrWt-mvaMedium-njet1");
  legends_3l_1tau_tt.push_back("tmva-12Var-wFrWt-mvaMedium-njet1");
  compareROC(filenames_3l_1tau_tt, histDirs_3l_1tau_tt, mvatype, legends_3l_1tau_tt, "plots", "comparison_roc_tmva_3l1tau_wFrWt_tauMvaMedium_njet1.png");
  */
  /*
  vector<TString> filenames_3l_1tau_ttV;
  filenames_3l_1tau_ttV.push_back("/home/arun/VHbbNtuples_8_0_x/CMSSW_8_0_21/src/tthAnalysis/HiggsToTauTau/test/training_3l_1tau_TTV/weight_fastsim_ttV_06Apr2017_allVar_frWt_sigTauTight_njet1/trainTTHMVA_3l_1tau_ttV_06Apr17_allVar_wfrWt_tauMvaTight_njet1.root");
  filenames_3l_1tau_ttV.push_back("/home/arun/VHbbNtuples_8_0_x/CMSSW_8_0_21/src/tthAnalysis/HiggsToTauTau/test/training_3l_1tau_TTV/weight_fastsim_ttV_06Apr2017_12Var_frWt_sigTauTight_njet1/trainTTHMVA_3l_1tau_ttV_06Apr17_12Var_wfrWt_tauMvaTight_njet1.root");
  vector<TString>histDirs_3l_1tau_ttV;
  histDirs_3l_1tau_ttV.push_back("Method_BDT/BDTG/");
  histDirs_3l_1tau_ttV.push_back("Method_BDT/BDTG/");
  vector<TString>mvatype;
  mvatype.push_back("TMVA");
  mvatype.push_back("TMVA");
  vector<TString>legends_3l_1tau_ttV;
  legends_3l_1tau_ttV.push_back("tmva-allVar-wFrWt-mvaMedium-njet1");
  legends_3l_1tau_ttV.push_back("tmva-12Var-wFrWt-mvaMedium-njet1");
  compareROC(filenames_3l_1tau_ttV, histDirs_3l_1tau_ttV, mvatype, legends_3l_1tau_ttV, "plots", "comparison_roc_tmva_3l1tau_ttV_wFrWt_tauMvaMedium_njet1.png");
  */
  /*
  vector<TString> filenames_3l_1tau_ttV;
  filenames_3l_1tau_ttV.push_back("/home/arun/VHbbNtuples_8_0_x/CMSSW_8_0_21/src/tthAnalysis/HiggsToTauTau/test/training_3l_1tau_TTV/weight_fastsim_ttV_06Apr2017_12Var_frWt_sigTauTight_njet1/trainTTHMVA_3l_1tau_ttV_06Apr17_12Var_wfrWt_tauMvaTight_njet1.root");
  filenames_3l_1tau_ttV.push_back("/home/arun/VHbbNtuples_8_0_x/CMSSW_8_0_21/src/tthAnalysis/HiggsToTauTau/test/training_3l_1tau_TTV/weight_fastsim_ttV_25Apr2017_12Var_frWt_tauTight_njet1/trainTTHMVA_3l_1tau_ttV_25Apr17_12Var_wfrWt_tauTight_njet1.root");
  vector<TString>histDirs_3l_1tau_ttV;
  histDirs_3l_1tau_ttV.push_back("Method_BDT/BDTG/");
  histDirs_3l_1tau_ttV.push_back("Method_BDT/BDTG/");
  vector<TString>mvatype;
  mvatype.push_back("TMVA");
  mvatype.push_back("TMVA");
  vector<TString>legends_3l_1tau_ttV;
  legends_3l_1tau_ttV.push_back("tmva-12Var-wFrWt-mvaMedium(signal)-njet1");
  legends_3l_1tau_ttV.push_back("tmva-12Var-wFrWt-mvaMedium(all)-njet1");
  compareROC(filenames_3l_1tau_ttV, histDirs_3l_1tau_ttV, mvatype, legends_3l_1tau_ttV, "plots", "comparison_roc_tmva_3l1tau_ttV_wFrWt_tauMvaMediumAll_njet1.png");
  */
  vector<TString> filenames_3l_1tau_ttV;
  filenames_3l_1tau_ttV.push_back("/home/arun/VHbbNtuples_8_0_x/CMSSW_8_0_21/src/tthAnalysis/HiggsToTauTau/test/training_3l_1tau_TTV/weight_fastsim_ttV_28Apr2017_allVar_frWt_tauTight_njet1/trainTTHMVA_3l_1tau_ttV_28Apr17_allVar_wfrWt_tauTight_njet1.root");
  filenames_3l_1tau_ttV.push_back("/home/arun/VHbbNtuples_8_0_x/CMSSW_8_0_21/src/tthAnalysis/HiggsToTauTau/test/training_3l_1tau_TTV/weight_fastsim_ttV_28Apr2017_13Var_frWt_tauTight_njet1/trainTTHMVA_3l_1tau_ttV_28Apr17_13Var_wfrWt_tauTight_njet1.root");
  vector<TString>histDirs_3l_1tau_ttV;
  histDirs_3l_1tau_ttV.push_back("Method_BDT/BDTG/");
  histDirs_3l_1tau_ttV.push_back("Method_BDT/BDTG/");
  vector<TString>mvatype;
  mvatype.push_back("TMVA");
  mvatype.push_back("TMVA");
  vector<TString>legends_3l_1tau_ttV;
  legends_3l_1tau_ttV.push_back("tmva-allVar-wFrWt-mvaMedium(all)-njet1");
  legends_3l_1tau_ttV.push_back("tmva-13Var-wFrWt-mvaMedium(all)-njet1");
  compareROC(filenames_3l_1tau_ttV, histDirs_3l_1tau_ttV, mvatype, legends_3l_1tau_ttV, "plots", "comparison_roc_tmva_3l1tau_ttV_wFrWt_tauMvaMediumAll_njet1_V2.png");
}
