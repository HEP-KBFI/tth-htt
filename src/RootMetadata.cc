#include "tthAnalysis/HiggsToTauTau/interface/RecoElectron.h" // RecoElectron, RecoLepton, GenLepton

#include <iostream>
#include <fstream>
using namespace std;


RootMetadata::RootMetadata()
{

}

string RootMetadata::toString() {
  return "selectedEntries: " + to_string(this.selectedEntries) + "\n";
}

bool RootMetadata::save(std::string fileName)
{
  ofstream f;
  f.open(fileName);
  f << this.toString();
  f.close();
  return true;
}
