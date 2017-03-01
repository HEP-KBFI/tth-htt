#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TH1D.h>
#include <TH2F.h>
#include <iostream>
#include <TLegend.h>
#include <TBranch.h>
#include <TClonesArray.h>
#include <TChain.h>
#include <TMath.h>

#include <TSystem.h>

using namespace std;

//gSystem->Load("/home/llr/cms/strebler/MG5_aMC_v2_2_1/ExRootAnalysis/libExRootAnalysis.so") before compilation in Root

float binning(TH1F* h){

  float max=h->GetBinLowEdge(h->GetNbinsX()+1);
  float min=h->GetBinLowEdge(1);
  float bin=(max-min)/h->GetNbinsX();
  return bin;
}


TH1F* single_plot(TString file, TString tree_name, TString var, TString cut, int nbin, float min, float max){

  TChain * tree = new TChain(tree_name);
  tree->Add(file);

  TH1F* g=new TH1F("g","g",nbin,min,max);
  g->Sumw2();

  tree->Draw(var+">>g",cut,"goff");

  return g;

}



TH1F* single_plot(vector<TString> files, TString tree_name, TString var, TString cut, int nbin, float min, float max){

  TChain * tree = new TChain(tree_name);
  for(unsigned int i=0; i<files.size(); i++)
    tree->Add(files[i]);

  TH1F* g=new TH1F("g","g",nbin,min,max);
  g->Sumw2();

  tree->Draw(var+">>g",cut,"goff");

  return g;

}




TH1F* single_plot(vector<TString> files, TString tree_name, TString var, vector<TString> cut, int nbin, float min, float max){


  TH1F* g=new TH1F("g","g",nbin,min,max);
  g->Sumw2();

  for(unsigned int i=0; i<files.size(); i++){
    g->Add(single_plot(files[i],tree_name,var,cut[i],nbin,min,max));
  }

  return g;

}



TH1D* single_plot_d(vector<TString> files, TString tree_name, TString var, TString cut, int nbin, float min, float max){

  TChain * tree = new TChain(tree_name);
  for(unsigned int i=0; i<files.size(); i++)
    tree->Add(files[i]);

  TH1D* g=new TH1D("g","g",nbin,min,max);
  g->Sumw2();

  tree->Draw(var+">>g",cut,"goff");

  return g;

}




TH1F* single_plot(TString file, TString tree_name, TString var, TString cut, int nbin, double* x){

  TChain * tree = new TChain(tree_name);
  tree->Add(file);

  TH1F* g=new TH1F("g","g",nbin,x);
  g->Sumw2();

  tree->Draw(var+">>g",cut,"goff");

  return g;

}





TH1F* single_plot(vector<TString> files, TString tree_name, TString var, TString cut, int nbin, double* x){

  TChain * tree = new TChain(tree_name);
  for(unsigned int i=0;i<files.size();i++)
    tree->Add(files[i]);

  TH1F* g=new TH1F("g","g",nbin,x);
  g->Sumw2();

  tree->Draw(var+">>g",cut,"goff");

  return g;

}







TH2F* single_plot2D(TString file, TString tree_name, TString var1, TString var2, TString cut, int nbin1, float min1, float max1, int nbin2, float min2, float max2){

  TChain * tree = new TChain(tree_name);
  tree->Add(file);

  tree->Draw(var2+":"+var1+Form(">>h(%i,%f,%f,%i,%f,%f)",nbin1,min1,max1,nbin2,min2,max2),cut,"goff");
  TH2F* g=(TH2F*) ((TH2F*)gDirectory->Get("h"))->Clone();
  return g;
}





TH2F* single_plot2D(vector<TString> files, TString tree_name, TString var1, TString var2, TString cut, int nbin1, float min1, float max1, int nbin2, float min2, float max2){

  TChain * tree = new TChain(tree_name);
  for(unsigned int i=0; i<files.size(); i++){
    tree->Add(files[i]);
  }

  tree->Draw(var2+":"+var1+Form(">>h(%i,%f,%f,%i,%f,%f)",nbin1,min1,max1,nbin2,min2,max2),cut,"goff");
  TH2F* g=(TH2F*) ((TH2F*)gDirectory->Get("h"))->Clone();
  return g;
}






TH2F* single_plot2D(TString file, TString tree_name, TString var1, TString var2, TString cut, int nbinx, double* x, int nbiny, double* y){

  TChain * tree = new TChain(tree_name);
  tree->Add(file);

  TH2F* g=new TH2F("g","g",nbinx,x,nbiny,y);
  g->Sumw2();

  tree->Draw(var2+":"+var1+">>g",cut,"goff");

  return g;

}




std::vector<TH1F*> sort_histo(std::vector<TH1F*> h){
  
  float max=0;
  unsigned int imax=0;
  for(unsigned int i=0;i<h.size();i++){
    float m=h[i]->GetMaximum();
    if(m>max){
      max=m;
      imax=i;
    }
  }
  vector<TH1F*> new_h;
  new_h.push_back(h[imax]);
  for(unsigned int i=0;i<h.size();i++){
    if(i!=imax)
      new_h.push_back(h[i]);
  }

  return new_h;
}


