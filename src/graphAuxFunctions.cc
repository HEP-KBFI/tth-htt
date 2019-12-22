#include "tthAnalysis/HiggsToTauTau/interface/graphAuxFunctions.h"

#include <TGraphErrors.h> 

#include <TGraph.h>
#include <TGraphAsymmErrors.h>

#include <iostream> // std::cout
#include <cassert> // assert()

double
square(double x)
{
  return x * x;
}

TGraphAsymmErrors *
compRatioGraph(const std::string & ratioGraphName,
               const TGraph * numerator,
               const TGraph * denominator)
{
  assert(numerator->GetN() == denominator->GetN());
  const int nPoints = numerator->GetN();

  TGraphAsymmErrors * const graphRatio = new TGraphAsymmErrors(nPoints);
  graphRatio->SetName(ratioGraphName.data());

  for( int idxPoint = 0; idxPoint < nPoints; ++idxPoint)
  {
    double x_numerator, y_numerator;
    numerator->GetPoint(idxPoint, x_numerator, y_numerator);

    double xErrUp_numerator = 0.;
    double xErrDown_numerator = 0.;
    double yErrUp_numerator = 0.;
    double yErrDown_numerator = 0.;
    if(dynamic_cast<const TGraphAsymmErrors *>(numerator))
    {
      const TGraphAsymmErrors * const numerator_asymmerrors = dynamic_cast<const TGraphAsymmErrors *>(numerator);
      xErrUp_numerator = numerator_asymmerrors->GetErrorXhigh(idxPoint);
      xErrDown_numerator = numerator_asymmerrors->GetErrorXlow(idxPoint);
      yErrUp_numerator = numerator_asymmerrors->GetErrorYhigh(idxPoint);
      yErrDown_numerator = numerator_asymmerrors->GetErrorYlow(idxPoint);
    }
    else if(dynamic_cast<const TGraphErrors *>(numerator))
    {
      const TGraphErrors * const numerator_errors = dynamic_cast<const TGraphErrors *>(numerator);
      xErrUp_numerator = numerator_errors->GetErrorX(idxPoint);
      xErrDown_numerator = xErrUp_numerator;
      yErrUp_numerator = numerator_errors->GetErrorY(idxPoint);
      yErrDown_numerator = yErrUp_numerator;
    }

    double x_denominator, y_denominator;
    denominator->GetPoint(idxPoint, x_denominator, y_denominator);
    assert(std::fabs(x_denominator - x_numerator) < 1.e-5);

    double xErrUp_denominator = 0.;
    double xErrDown_denominator = 0.;
    double yErrUp_denominator = 0.;
    double yErrDown_denominator = 0.;
    if(dynamic_cast<const TGraphAsymmErrors *>(denominator))
    {
      const TGraphAsymmErrors * const denominator_asymmerrors = dynamic_cast<const TGraphAsymmErrors *>(denominator);
      xErrUp_denominator = denominator_asymmerrors->GetErrorXhigh(idxPoint);
      xErrDown_denominator = denominator_asymmerrors->GetErrorXlow(idxPoint);
      yErrUp_denominator = denominator_asymmerrors->GetErrorYhigh(idxPoint);
      yErrDown_denominator = denominator_asymmerrors->GetErrorYlow(idxPoint);
    }
    else if( dynamic_cast<const TGraphErrors *>(denominator))
    {
      const TGraphErrors * const denominator_errors = dynamic_cast<const TGraphErrors *>(denominator);
      xErrUp_denominator = denominator_errors->GetErrorX(idxPoint);
      xErrDown_denominator = xErrUp_denominator;
      yErrUp_denominator = denominator_errors->GetErrorY(idxPoint);
      yErrDown_denominator = yErrUp_denominator;
    }

    const double x_ratio = x_numerator;
    const double y_ratio = y_denominator > 0. ? y_numerator / y_denominator : 0.;

    const double xErrUp_ratio = std::max(xErrUp_numerator, xErrUp_denominator);
    const double xErrDown_ratio = std::max(xErrDown_numerator, xErrDown_denominator);
    double yErr2Up_ratio =
      square(yErrUp_numerator     / (y_numerator   != 0. ? y_numerator   : 1.)) +
      square(yErrDown_denominator / (y_denominator != 0. ? y_denominator : 1.))
    ;

    double yErrUp_ratio = std::sqrt(yErr2Up_ratio) * (y_ratio != 0. ? std::fabs(y_ratio) : 1.);
    double yErr2Down_ratio =
      square(yErrDown_numerator / (y_numerator   != 0. ? y_numerator   : 1.)) +
      square(yErrUp_denominator / (y_denominator != 0. ? y_denominator : 1.))
    ;
    double yErrDown_ratio = std::sqrt(yErr2Down_ratio) * (y_ratio != 0. ? std::fabs(y_ratio) : 1.);

    graphRatio->SetPoint(idxPoint, x_ratio, y_ratio);
    graphRatio->SetPointError(idxPoint, xErrDown_ratio, xErrUp_ratio, yErrDown_ratio, yErrUp_ratio);
  }
  
  graphRatio->SetLineColor(numerator->GetLineColor());
  graphRatio->SetLineWidth(numerator->GetLineWidth());
  graphRatio->SetMarkerColor(numerator->GetMarkerColor());
  graphRatio->SetMarkerStyle(numerator->GetMarkerStyle());
  graphRatio->SetMarkerSize(numerator->GetMarkerSize());

  return graphRatio;
}

void
dumpGraph(const TGraph * graph)
{
  std::cout << __func__ << ":\ngraph = " << graph->GetName() << '\n';

  const int nPoints = graph->GetN();
  for(int idxPoint = 0; idxPoint < nPoints; ++idxPoint)
  {
    double x, y;
    graph->GetPoint(idxPoint, x, y);

    double yErrUp = 0.;
    double yErrDown = 0.;
    if(dynamic_cast<const TGraphAsymmErrors *>(graph))
    {
      const TGraphAsymmErrors * const graph_asymmerrors = dynamic_cast<const TGraphAsymmErrors *>(graph);
      yErrUp = graph_asymmerrors->GetErrorYhigh(idxPoint);
      yErrDown = graph_asymmerrors->GetErrorYlow(idxPoint);
    }
    else if(dynamic_cast<const TGraphErrors *>(graph))
    {
      const TGraphErrors * const graph_errors = dynamic_cast<const TGraphErrors *>(graph);
      yErrUp = graph_errors->GetErrorY(idxPoint);
      yErrDown = yErrUp;
    }
    std::cout << "point #" << idxPoint << " (x = " << x << "):"
              << " y = " << y << " + " << yErrUp << " - " << yErrDown << '\n';
  }
}
