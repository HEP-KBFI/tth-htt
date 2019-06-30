#include "tthAnalysis/HiggsToTauTau/interface/fitAuxFunctions.h"

#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

#include <TCanvas.h>
#include <TPad.h>
#include <TH1.h> // TH1D
#include <TLegend.h>
#include <TF1.h>
#include <TGraphAsymmErrors.h>

#include <assert.h> // assert

EigenVector_and_Value::EigenVector_and_Value(const TVectorD & eigenVector,
                                             double eigenValue)
  : eigenVector_(eigenVector),
    eigenValue_(eigenValue)
{}

fitFunction_and_legendEntry::fitFunction_and_legendEntry(TF1 * fitFunction,
                                                         const std::string & legendEntry)
  : fitFunction_(fitFunction),
    legendEntry_(legendEntry)
{}

std::vector<EigenVector_and_Value>
compEigenVectors_and_Values(const TMatrixD& cov)
{
  std::cout << __func__ << ":\n cov:\n";
  cov.Print();

  if(cov.GetNcols() != cov.GetNrows())
  {
    throw cmsException(__func__, __LINE__)
      << "Matrix given as function argument is not symmetric"
    ;
  }

  const int dimension = cov.GetNrows();
  TVectorD eigenValues(dimension);
  const TMatrixD eigenVectors = cov.EigenVectors(eigenValues);
  assert(eigenVectors.GetNrows() == dimension);
  assert(eigenVectors.GetNcols() == dimension);

  std::vector<EigenVector_and_Value> eigenVectors_and_Values;
  for(int iEigenVector = 0; iEigenVector < dimension; ++iEigenVector)
  {
    TVectorD eigenVector(dimension);
    for(int iComponent = 0; iComponent < dimension; ++iComponent)
    {
      eigenVector(iComponent) = eigenVectors(iComponent, iEigenVector);
    }

    const double eigenValue = eigenValues(iEigenVector);
    const TVectorD vec1 = cov * eigenVector;
    std::cout << "vec1:\n";
    vec1.Print();

    const TVectorD vec2 = eigenValue * eigenVector;
    std::cout << "vec2:\n";
    vec2.Print();

    // CV: check that EigenVector is indeed an EigenVector,
    //     i.e. that we interpreted the ordering of columns and rows of the eigenVectors matrix correctly
    for(int iComponent = 0; iComponent < dimension; ++iComponent)
    {
      std::cout << "component #" << iComponent << ": vec1 = " << vec1(iComponent) << ", vec2 = " << vec2(iComponent) << '\n';
      const double diff = vec1(iComponent) - vec2(iComponent);
      const double sum = std::fabs(std::max(1.e-6, vec1(iComponent))) + std::fabs(std::max(1.e-6, vec2(iComponent)));

      std::cout << "assert(" << diff << " < " << std::max(1.e-6, 1.e-3 * sum) << ")\n";
      assert(diff < std::max(1.e-6, 1.e-3 * sum));
    }
    eigenVectors_and_Values.push_back({ eigenVector, eigenValue });
  }
  return eigenVectors_and_Values;
}

void
makeControlPlot_graphs(TGraphAsymmErrors * graph_data,
                       const std::string & legendEntry_data,
                       TGraphAsymmErrors * graph_mc,
                       const std::string & legendEntry_mc,
                       TGraphAsymmErrors * graph_data_div_mc,
                       double xMin,
                       double xMax,
                       const std::string & xAxisTitle,
                       bool useLogScale,
                       double yMin,
                       double yMax,
                       const std::string & yAxisTitle,
                       double yMin_ratio,
                       double yMax_ratio,
                       const std::string & yAxisTitle_ratio,
                       const std::string & outputFileName)
{
  std::cout << __func__ << ":\n outputFileName = " << outputFileName << '\n';

  TCanvas * const canvas = new TCanvas("canvas", "canvas", 800, 900);
  canvas->SetFillColor(10);
  canvas->SetBorderSize(2);
  canvas->SetTopMargin(0.12);
  canvas->SetLeftMargin(0.12);
  canvas->SetBottomMargin(0.12);

  TPad * const topPad = new TPad("topPad", "topPad", 0.00, 0.35, 1.00, 1.00);
  topPad->SetFillColor(10);
  topPad->SetTopMargin(0.04);
  topPad->SetLeftMargin(0.15);
  topPad->SetBottomMargin(0.03);
  topPad->SetRightMargin(0.05);
  topPad->SetGridx();
  topPad->SetGridy();
  topPad->SetLogy(useLogScale);

  canvas->cd();
  topPad->Draw();
  topPad->cd();

  TH1 * const dummyHistogram_top = new TH1D("dummyHistogram_top", "dummyHistogram_top", 10, xMin, xMax);
  dummyHistogram_top->SetTitle("");
  dummyHistogram_top->SetStats(false);
  dummyHistogram_top->SetMaximum(yMax);
  dummyHistogram_top->SetMinimum(yMin);
  
  TAxis * const xAxis_top = dummyHistogram_top->GetXaxis();
  xAxis_top->SetTitle(xAxisTitle.data());
  xAxis_top->SetTitleOffset(1.2);
  xAxis_top->SetLabelColor(10);
  xAxis_top->SetTitleColor(10);

  TAxis * const yAxis_top = dummyHistogram_top->GetYaxis();
  yAxis_top->SetTitle(yAxisTitle.data());
  yAxis_top->SetTitleSize(0.050);
  yAxis_top->SetTitleOffset(1.15);

  dummyHistogram_top->Draw();

  TLegend * const legend = new TLegend(0.74, 0.785, 0.94, 0.935, "", "brNDC");
  legend->SetBorderSize(0);
  legend->SetFillColor(0);
  legend->AddEntry(graph_data, legendEntry_data.data(), "p");
  legend->AddEntry(graph_mc, legendEntry_mc.data(), "p");

  graph_mc->SetMarkerStyle(24);
  graph_mc->SetMarkerColor(1);
  graph_mc->Draw("p");

  graph_data->SetMarkerStyle(20);
  graph_data->SetMarkerColor(1);
  graph_data->Draw("p");

  legend->Draw();

  TPad * const bottomPad = new TPad("bottomPad", "bottomPad", 0.00, 0.00, 1.00, 0.35);
  bottomPad->SetFillColor(10);
  bottomPad->SetTopMargin(0.02);
  bottomPad->SetLeftMargin(0.15);
  bottomPad->SetBottomMargin(0.24);
  bottomPad->SetRightMargin(0.05);
  bottomPad->SetGridx();
  bottomPad->SetGridy();

  canvas->cd();
  bottomPad->Draw();
  bottomPad->cd();

  TH1 * const dummyHistogram_bottom = new TH1D("dummyHistogram_bottom", "dummyHistogram_bottom", 10, xMin, xMax);
  
  dummyHistogram_bottom->SetMinimum(yMin_ratio);
  dummyHistogram_bottom->SetMaximum(yMax_ratio);

  TAxis* xAxis_bottom = dummyHistogram_bottom->GetXaxis();
  xAxis_bottom->SetTitle(xAxisTitle.data());
  xAxis_bottom->SetTitleOffset(1.20);
  xAxis_bottom->SetLabelColor(1);
  xAxis_bottom->SetTitleColor(1);
  xAxis_bottom->SetTitleSize(0.08);
  xAxis_bottom->SetLabelOffset(0.02);
  xAxis_bottom->SetLabelSize(0.08);
  xAxis_bottom->SetTickLength(0.055);

  TAxis* yAxis_bottom = dummyHistogram_bottom->GetYaxis();
  yAxis_bottom->SetTitle(yAxisTitle_ratio.data());
  yAxis_bottom->SetTitleOffset(0.75);
  yAxis_bottom->SetNdivisions(505);
  yAxis_bottom->CenterTitle();
  yAxis_bottom->SetTitleSize(0.08);
  yAxis_bottom->SetLabelSize(0.08);
  yAxis_bottom->SetTickLength(0.04);

  dummyHistogram_bottom->SetTitle("");
  dummyHistogram_bottom->SetStats(false);
  dummyHistogram_bottom->Draw();
  
  const std::string graphName_data_div_mc_cloned = Form("%s_cloned", graph_data_div_mc->GetName());
  TGraphAsymmErrors * const graph_data_div_mc_cloned = static_cast<TGraphAsymmErrors *>(
    graph_data_div_mc->Clone(graphName_data_div_mc_cloned.data())
  );
  const int numPoints = graph_data_div_mc_cloned->GetN();
  for(int idxPoint = 0; idxPoint < numPoints; ++idxPoint)
  {
    double x, y;
    graph_data_div_mc->GetPoint(idxPoint, x, y);
    graph_data_div_mc_cloned->SetPoint(idxPoint, x, y - 1.);
  }
  graph_data_div_mc_cloned->SetMarkerStyle(20);
  graph_data_div_mc_cloned->SetMarkerColor(1);
  graph_data_div_mc_cloned->Draw("p");
  
  canvas->Update();
  const std::size_t idx = outputFileName.find_last_of('.');
  std::string outputFileName_plot = std::string(outputFileName, 0, idx);
  if(useLogScale)
  {
    outputFileName_plot.append("_log");
  }
  else
  {
    outputFileName_plot.append("_linear");
  }
  if(idx != std::string::npos)
  {
    canvas->Print(outputFileName_plot.append(std::string(outputFileName, idx)).data());
  }
  canvas->Print(std::string(outputFileName_plot).append(".png").data());
  canvas->Print(std::string(outputFileName_plot).append(".pdf").data());
  canvas->Print(std::string(outputFileName_plot).append(".root").data());

  delete legend;
  delete dummyHistogram_top;
  delete topPad;
  delete dummyHistogram_bottom;
  delete graph_data_div_mc_cloned;
  delete canvas;
}

void
makeControlPlot_fit(TGraphAsymmErrors * graph,
                    TF1 * fitFunction_central,
                    std::vector<fitFunction_and_legendEntry> & fitFunctions_sysShifts,
                    double xMin,
                    double xMax,
                    const std::string & xAxisTitle,
                    bool useLogScale,
                    double yMin,
                    double yMax,
                    const std::string & yAxisTitle,
                    const std::string & outputFileName)
{
  std::cout << __func__ << ":\n outputFileName = " << outputFileName << '\n';

  if(fitFunctions_sysShifts.size() > 6)
  {
    throw cmsException(__func__, __LINE__)
      << "Fit functions with more than 3 parameters are not supported yet"
    ;
  }

  TCanvas * const canvas = new TCanvas("canvas", "canvas", 800, 900);
  canvas->SetFillColor(10);
  canvas->SetBorderSize(2);
  canvas->SetTopMargin(0.12);
  canvas->SetLeftMargin(0.12);
  canvas->SetBottomMargin(0.12);
  
  TPad * const topPad = new TPad("topPad", "topPad", 0.00, 0.35, 1.00, 1.00);
  topPad->SetFillColor(10);
  topPad->SetTopMargin(0.04);
  topPad->SetLeftMargin(0.15);
  topPad->SetBottomMargin(0.03);
  topPad->SetRightMargin(0.05);
  topPad->SetGridx();
  topPad->SetGridy();
  topPad->SetLogy(useLogScale);

  canvas->cd();
  topPad->Draw();
  topPad->cd();

  TH1 * const dummyHistogram_top = new TH1D("dummyHistogram_top", "dummyHistogram_top", 10, xMin, xMax);
  dummyHistogram_top->SetTitle("");
  dummyHistogram_top->SetStats(false);
  dummyHistogram_top->SetMaximum(yMax);
  dummyHistogram_top->SetMinimum(yMin);
  
  TAxis * const xAxis_top = dummyHistogram_top->GetXaxis();
  xAxis_top->SetTitle(xAxisTitle.data());
  xAxis_top->SetTitleOffset(1.2);
  xAxis_top->SetLabelColor(10);
  xAxis_top->SetTitleColor(10);

  TAxis * const yAxis_top = dummyHistogram_top->GetYaxis();
  yAxis_top->SetTitle(yAxisTitle.data());
  yAxis_top->SetTitleSize(0.050);
  yAxis_top->SetTitleOffset(1.15);

  dummyHistogram_top->Draw();

  TLegend * const legend = new TLegend(0.69, 0.935 - 0.055 * (1 + fitFunctions_sysShifts.size()/2), 0.94, 0.935, "", "brNDC");
  legend->SetBorderSize(0);
  legend->SetFillColor(0);

  fitFunction_central->SetLineColor(2);
  fitFunction_central->Draw("Lsame");
  legend->AddEntry(fitFunction_central, "Best Fit", "L");    

  const int colors[3] = { 4, 6, 7 };

  int idx_top = 0;
  for(fitFunction_and_legendEntry & fitFunction_sysShift: fitFunctions_sysShifts)
  {
    const int iColor = idx_top / 2;
    assert(iColor <= 2);
    fitFunction_sysShift.fitFunction_->SetLineColor(colors[iColor]);
    fitFunction_sysShift.fitFunction_->SetLineStyle(8);
    fitFunction_sysShift.fitFunction_->Draw("Lsame");
    if(idx_top % 2 == 0)
    {
      legend->AddEntry(fitFunction_sysShift.fitFunction_, fitFunction_sysShift.legendEntry_.data(), "L");
    }
    ++idx_top;
  }

  graph->SetMarkerStyle(8);
  graph->SetMarkerColor(1);
  graph->Draw("p");

  legend->Draw();

  TPad * const bottomPad = new TPad("bottomPad", "bottomPad", 0.00, 0.00, 1.00, 0.35);
  bottomPad->SetFillColor(10);
  bottomPad->SetTopMargin(0.02);
  bottomPad->SetLeftMargin(0.15);
  bottomPad->SetBottomMargin(0.24);
  bottomPad->SetRightMargin(0.05);
  bottomPad->SetGridx();
  bottomPad->SetGridy();

  canvas->cd();
  bottomPad->Draw();
  bottomPad->cd();

  TH1 * const dummyHistogram_bottom = new TH1D("dummyHistogram_bottom", "dummyHistogram_bottom", 10, xMin, xMax);
  
  dummyHistogram_bottom->SetMinimum(-1.50);
  dummyHistogram_bottom->SetMaximum(+1.50);

  TAxis * const xAxis_bottom = dummyHistogram_bottom->GetXaxis();
  xAxis_bottom->SetTitle(xAxisTitle.data());
  xAxis_bottom->SetTitleOffset(1.20);
  xAxis_bottom->SetLabelColor(1);
  xAxis_bottom->SetTitleColor(1);
  xAxis_bottom->SetTitleSize(0.08);
  xAxis_bottom->SetLabelOffset(0.02);
  xAxis_bottom->SetLabelSize(0.08);
  xAxis_bottom->SetTickLength(0.055);

  TAxis * const yAxis_bottom = dummyHistogram_bottom->GetYaxis();
  yAxis_bottom->SetTitle(Form("%s - Fit", yAxisTitle.data()));
  yAxis_bottom->SetTitleOffset(0.75);
  yAxis_bottom->SetNdivisions(505);
  yAxis_bottom->CenterTitle();
  yAxis_bottom->SetTitleSize(0.08);
  yAxis_bottom->SetLabelSize(0.08);
  yAxis_bottom->SetTickLength(0.04);

  dummyHistogram_bottom->SetTitle("");
  dummyHistogram_bottom->SetStats(false);
  dummyHistogram_bottom->Draw();

  std::vector<TF1 *> fitFunctionsToDelete;

  int idx_bottom = 0;
  for(fitFunction_and_legendEntry & fitFunction_sysShift: fitFunctions_sysShifts)
  {
    TF1 * const fitFunction_pass = fitFunction_sysShift.fitFunction_;
    TString fitFunction_formula_pass = fitFunction_pass->GetTitle();
    const int numPar_pass = fitFunction_pass->GetNpar();

    TF1 * const fitFunction_fail = fitFunction_central;
    TString fitFunction_formula_fail = fitFunction_fail->GetTitle();
    const int numPar_fail = fitFunction_fail->GetNpar();

    for(int iPar = 0; iPar < numPar_fail; ++iPar)
    {
      fitFunction_formula_fail.ReplaceAll(Form("[%i]", iPar), Form("[%i]", iPar + numPar_pass));      
    }

    const std::string fitFunctionName_sysShift_div_central = Form("%s_div_central", fitFunction_pass->GetName());
    const std::string fitFunction_formula_sysShift_div_central = Form(
      "(%s)/(%s) - 1.0", fitFunction_formula_pass.Data(), fitFunction_formula_fail.Data()
    );

    TF1 * const fitFunction_sysShift_div_central = new TF1(
      fitFunctionName_sysShift_div_central.data(), fitFunction_formula_sysShift_div_central.data(), xMin, xMax
    );
    for(int iPar_pass = 0; iPar_pass < numPar_fail; ++iPar_pass)
    {
      fitFunction_sysShift_div_central->SetParameter(iPar_pass, fitFunction_fail->GetParameter(iPar_pass));
    }
    for(int iPar_fail = 0; iPar_fail < numPar_fail; ++iPar_fail)
    {
      fitFunction_sysShift_div_central->SetParameter(iPar_fail + numPar_pass, fitFunction_fail->GetParameter(iPar_fail));
    }

    const int iColor = idx_bottom / 2;
    assert(iColor <= 2);
    fitFunction_sysShift_div_central->SetLineColor(colors[iColor]);
    fitFunction_sysShift_div_central->Draw("Lsame");
    fitFunctionsToDelete.push_back(fitFunction_sysShift_div_central);
    ++idx_bottom;
  }

  const int numPoints = graph->GetN();
  TGraphAsymmErrors * const graph_div_fit = new TGraphAsymmErrors(numPoints);
  for(int iPoint = 0; iPoint < numPoints; ++iPoint)
  {
    double x, y;
    graph->GetPoint(iPoint, x, y);

    const double fitFunctionValue = fitFunction_central->Eval(x);
    graph_div_fit->SetPoint(iPoint, x, y - fitFunctionValue);

    const double xErrUp = graph->GetErrorXhigh(iPoint);
    const double xErrDown = graph->GetErrorXlow(iPoint);
    const double yErrUp = graph->GetErrorYhigh(iPoint);
    const double yErrDown = graph->GetErrorYlow(iPoint);
    graph_div_fit->SetPointError(iPoint, xErrDown, xErrUp, yErrDown, yErrUp);
  }
  graph_div_fit->SetMarkerStyle(8);
  graph_div_fit->SetMarkerColor(1);
  graph_div_fit->Draw("p");
  
  canvas->Update();
  const std::size_t idx = outputFileName.find_last_of('.');
  std::string outputFileName_plot = std::string(outputFileName, 0, idx);
  if(useLogScale)
  {
    outputFileName_plot.append("_log");
  }
  else
  {
    outputFileName_plot.append("_linear");
  }
  if(idx != std::string::npos)
  {
    canvas->Print(std::string(outputFileName_plot).append(std::string(outputFileName, idx)).data());
  }
  canvas->Print(std::string(outputFileName_plot).append(".png").data());
  canvas->Print(std::string(outputFileName_plot).append(".pdf").data());
  canvas->Print(std::string(outputFileName_plot).append(".root").data());
  
  delete legend;
  delete dummyHistogram_top;
  delete topPad;
  delete dummyHistogram_bottom;
  for(TF1 * it: fitFunctionsToDelete)
  {
    delete it;
  }
  delete graph_div_fit;
  delete canvas;
}
