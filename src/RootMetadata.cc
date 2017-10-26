#include "tthAnalysis/HiggsToTauTau/interface/RootMetadata.h" // RecoElectron, RecoLepton, GenLepton

#include <iostream>
#include <fstream>
#include <string>
using namespace std;


std::string RootMetadata::toString() {
  return std::string("selectedEntries: ") + std::to_string(this->selectedEntries) + std::string("\n");
}

bool RootMetadata::save(std::string fileName)
{
  ofstream f;
  f.open(fileName);
  f << this->toString();
  f.close();
  return true;
}
