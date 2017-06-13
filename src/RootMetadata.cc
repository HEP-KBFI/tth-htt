#include "tthAnalysis/HiggsToTauTau/interface/RecoElectron.h" // RecoElectron, RecoLepton, GenLepton

#include <iostream>
#include <fstream>
#include <string>
using namespace std;


RootMetadata::RootMetadata()
{

}

string RootMetadata::toString() {
  return std::to_string("selectedEntries: ") + std::to_string(this.selectedEntries) + "\n";
}

bool RootMetadata::save(std::string fileName)
{
  ofstream f;
  f.open(fileName);
  f << this.toString();
  f.close();
  return true;
}
