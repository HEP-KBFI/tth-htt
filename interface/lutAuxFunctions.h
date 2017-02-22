#ifndef tthAnalysis_HiggsToTauTau_lutAuxFunctions_h
#define tthAnalysis_HiggsToTauTau_lutAuxFunctions_h

#include "tthAnalysis/HiggsToTauTau/interface/LocalFileInPath.h" // LocalFileInPath

#include <TFile.h> // TFile
#include <TH1.h> // TH1
#include <TH2.h> // TH2
#include <TGraph.h> // TH2

#include <string>
#include <vector>
#include <map>

namespace lut
{
  enum { kXpt, kXeta, kXabsEta, kXptYpt, kXptYeta, kXptYabsEta, kXetaYpt, kXabsEtaYpt };
}

// define auxiliary functions
TFile* openFile(const LocalFileInPath& fileName);

TH1* loadTH1(TFile* inputFile, const std::string& histogramName);
TH2* loadTH2(TFile* inputFile, const std::string& histogramName);

TGraph* loadTGraph(TFile* inputFile, const std::string& graphName);

double getSF_from_TH1(TH1* lut, double x);
double getSF_from_TH2(TH2* lut, double x, double y);
double getSF_from_TH2Poly(TH2* lut, double x, double y);
double getSF_from_TGraph(TGraph* lut, double x);

class lutWrapperBase
{
 public:
  lutWrapperBase();
  lutWrapperBase(std::map<std::string, TFile*>& inputFiles, const std::string& inputFileName, const std::string& lutName, int lutType,
                 double xMin = -1., double xMax = -1., double yMin = -1., double yMax = -1.);
  virtual ~lutWrapperBase() {}
  double getSF(double pt, double eta);
 protected:
  enum { kUndefined, kPt, kEta, kAbsEta };
  std::string inputFileName_;
  TFile* inputFile_;
  std::string lutName_;
  int lutTypeX_;
  int lutTypeY_;
  double xMin_;
  double xMax_;
  double yMin_;
  double yMax_;
 private:
  virtual double getSF_private(double x, double y) = 0;
};

typedef std::vector<lutWrapperBase*> vLutWrapperBase;
double get_from_lut(const vLutWrapperBase& corrections, double pt, double eta);

class lutWrapperTH1 : public lutWrapperBase
{
 public:
  lutWrapperTH1(std::map<std::string, TFile*>& inputFiles, const std::string& inputFileName, const std::string& lutName, int lutType, 
		double xMin = -1., double xMax = -1., double yMin = -1., double yMax = -1.);
 private:
  double getSF_private(double x, double y);
  TH1* lut_;
};

class lutWrapperTH2 : public lutWrapperBase
{
 public:
  lutWrapperTH2(std::map<std::string, TFile*>& inputFiles, const std::string& inputFileName, const std::string& lutName, int lutType, 
		double xMin = -1., double xMax = -1., double yMin = -1., double yMax = -1.);
 private:
  double getSF_private(double x, double y);
  TH2* lut_;
};
class lutWrapperTH2Poly : public lutWrapperBase
{
 public:
  lutWrapperTH2Poly(std::map<std::string, TFile*>& inputFiles, const std::string& inputFileName, const std::string& lutName, int lutType, 
		    double xMin = -1., double xMax = -1., double yMin = -1., double yMax = -1.);
 private:
  double getSF_private(double x, double y);
  TH2* lut_;
};

class lutWrapperTGraph : public lutWrapperBase
{
 public:
  lutWrapperTGraph(std::map<std::string, TFile*>& inputFiles, const std::string& inputFileName, const std::string& lutName, int lutType, 
		   double xMin = -1., double xMax = -1., double yMin = -1., double yMax = -1.);
 private:
  double getSF_private(double x, double y);
  TGraph* lut_;
};

class lutWrapperData_to_MC : public lutWrapperBase
{
 public:
  lutWrapperData_to_MC(lutWrapperBase* lutData, lutWrapperBase* lutMC);
  ~lutWrapperData_to_MC();
 private:
  double getSF_private(double x, double y);
  lutWrapperBase* lutData_;
  lutWrapperBase* lutMC_;
};

#endif // tthAnalysis_HiggsToTauTau_lutAuxFunctions_h
