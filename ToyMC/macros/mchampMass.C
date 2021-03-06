/// .L massPlot.C+
// lifetimePlot("limit_summary.txt", "time_profile_summary.txt")

// ***********************************************
// The following parameters (LUMI, MAXLUMI) need to be set by hand:
// LUMI is a double
#define LUMI 877.
// MAXINSTLUMI is a double
// Get MAXINSTLUMI directly from https://cmswbm.web.cern.ch/cmswbm/cmsdb/servlet/FillReport 
// (PeakInstLumi).  
// Units are 10^30 cm^-2 s^-1
#define MAXINSTLUMI 1300.
// ENERGY is a double
#define ENERGY 8.
// ***********************************************


#include <cstdlib>
#include <fstream>
#include <iostream> 
#include <sstream>

#include "TGraph.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TH1.h"
#include "TH1F.h"
#include "TLegend.h"
#include "TPaveText.h"
#include "TBox.h"
#include "TLatex.h"

#include "LimitPlots.h"

// .L massPlot.C+
// massPlot("limit_summary.txt", "time_profile_summary.txt");

void mchampMass(double lumi=-1., double maxInstLumi=-1.) {
	
  if (lumi<0)
    lumi=877.;
  if (maxInstLumi<0)
    maxInstLumi=1300.;
  LimitPlots plots(lumi);
  
  //mchamp index 0 is used, corresponds to 0th mass point = 100 GeV
  plots.calculateCrossSections(7,4,0,39,9);
	
  // expected limit (1 and 2 sigma bands)
  TGraph* m_exp = plots.getExpMassLimitMchamp();
  TGraphAsymmErrors* m_exp1 = plots.getExpMassLimitMchamp1Sig();
  TGraphAsymmErrors* m_exp2 = plots.getExpMassLimitMchamp2Sig();
  
  // three points on counting expt curve
  TGraph* m_mchamp = plots.getMassLimitMchamp();
  TGraph* m_stop = plots.getMassLimitStop();
  
  // one point from lifetime fit
  TGraph* m_tp = plots.getMassLimitMchampTP();
  
  // theory prediction
  TGraph* m_thMchamp = plots.getMchampTheory();
  TGraph* m_thStop = plots.getStopTheory();
  
  TCanvas* canvas = new TCanvas("canvas");
  
  //canvas->SetGrid();
  canvas->SetLogy();
  
  TH1 * h;
  h = canvas->DrawFrame(300., .02, 1000., 1e2);
  //h->SetTitle("Beamgap Expt;m_{#tilde{g}} [GeV/c^{2}]; Stopped HSCP Cross Section #times BR [pb]");
  h->SetTitle("Beamgap Expt;m_{#tilde{g}} [GeV/c^{2}]; #sigma(pp #rightarrow #tilde{g}#tilde{g}) #times BR(#tilde{g} #rightarrow g#tilde{#chi}^{0}) [pb]");
  
  // not covered region
  TBox* nc = new TBox(100., .1, 150., 5e2);
  nc->SetFillStyle(3354);
  nc->SetFillColor(kRed-4);
  //nc->Draw();
  
  // details
  TPaveText* blurb = new TPaveText(300., 2, 550., 1e2);
  blurb->AddText("CMS Preliminary 2012");

  std::stringstream label;
  label<<"#int L dt = "<<lumi<<" fb^{-1}";
  blurb->AddText(label.str().c_str());
  label.str("");
  double peakInstLumi=maxInstLumi;
  int exponent=30;
  while (peakInstLumi>10) {
    peakInstLumi/=10.;
    ++exponent;
  }
  label<<"L^{max}_{inst} = "<<peakInstLumi<<" x 10^{"<<exponent<<"} cm^{-2}s^{-1}";
  blurb->AddText(label.str().c_str());
  label.str("");
  label << "#sqrt{s} = " << ENERGY << " TeV";
  blurb->AddText(label.str().c_str());
  blurb->AddText("m_{#tilde{g}} - m_{#tilde{#chi}^{0}} = 100 GeV/c^{2}");
  //blurb->AddText("m_{#tilde{t}} - m_{#tilde{#chi}^{0}} = 200 GeV/c^{2}");	
  blurb->SetTextFont(42);
  blurb->SetBorderSize(0);
  blurb->SetFillColor(0);
  blurb->SetShadowColor(0);
  blurb->SetTextAlign(12);
  blurb->SetTextSize(0.032);

  
  // legend
  TBox *legbg = new TBox(600., 2., 900., 1e2);
  legbg->Draw();
  TLegend *leg = new TLegend(600., 2., 900., 1e2,"95% C.L. Limits","");
  leg->SetTextSize(0.028);
  leg->SetBorderSize(0);
  leg->SetTextFont(42);
  leg->SetFillColor(0);
  leg->AddEntry(m_exp, "Expected: 10 #mus - 1000 s Counting Exp. ", "l");
  leg->AddEntry(m_exp1, "Expected #pm1#sigma: 10 #mus - 1000 s Counting Exp. ", "f");
  leg->AddEntry(m_exp2, "Expected #pm2#sigma: 10 #mus - 1000 s Counting Exp. ", "f");
  //	  leg->AddEntry(graph3, "Obs.: 10^{6} s Counting Exp.", "l");
  leg->AddEntry(m_mchamp, "Obs.: 10 #mus - 1000 s Counting Exp. ", "l");
  leg->AddEntry(m_tp, "Obs.: 10 #mus Timing Profile ", "l");
  //leg->AddEntry(m_stop, "Obs.: 10 #mus - 1000 s Counting Exp. (#tilde{t})", "l");
  //leg->AddEntry(graph_em, "Obs.: 10 #mus - 1000 s Counting Exp. (EM only)", "l");
  //  leg->AddEntry(graph1, "Obs.: 570 ns Counting Exp.", "l");
  leg->Draw();
  
  
  
  // 2 sigma expected band
  m_exp2->SetLineColor(0);
  m_exp2->SetLineStyle(0);
  m_exp2->SetLineWidth(0);
  m_exp2->SetFillColor(5);
  m_exp2->SetFillStyle(1001);
  m_exp2->Draw("3");
  
  // 1 sigma expected band
  m_exp1->SetLineColor(0);
  m_exp1->SetLineStyle(0);
  m_exp1->SetLineWidth(0);
  m_exp1->SetFillColor(3);
  m_exp1->SetFillStyle(1001);
  m_exp1->Draw("3");  
  
  // expected line
  m_exp->SetLineStyle(2);
  m_exp->SetLineWidth(1);
  m_exp->Draw("l");
  
 
  // plateau limit - 1 ms
  m_mchamp->SetLineColor(1);
  m_mchamp->SetLineStyle(1);
  m_mchamp->SetLineWidth(2);
  m_mchamp->Draw("l");
  
  // stop curve
  m_stop->SetLineColor(1);
  m_stop->SetLineStyle(5);
  m_stop->SetLineWidth(2);
  //m_stop->Draw("l");
 

  // 1 mus lifetime fit limit
  m_tp->SetLineColor(kRed);
  m_tp->SetLineStyle(1);
  m_tp->SetLineWidth(2);
  m_tp->Draw("l");
  
  // theory line
  m_thMchamp->SetLineColor(kBlue);
  m_thMchamp->SetLineStyle(1);
  m_thMchamp->SetLineWidth(2);
  m_thMchamp->SetFillStyle(3001);
  m_thMchamp->SetFillColor(kBlue-4);
  m_thMchamp->Draw("l3");
  
  m_thStop->SetLineColor(kRed);
  m_thStop->SetLineStyle(1);
  m_thStop->SetLineWidth(2);
  m_thStop->SetFillStyle(3001);
  m_thStop->SetFillColor(kRed-4);
  //m_thStop->Draw("l3");


  // theory line label
  TLatex* th = new TLatex(600., .3, "NLO+NLL #tilde{g}");
  th->SetTextColor(kBlue);
  th->SetTextFont(42);
  th->SetTextSize(0.035);
  th->Draw();

  TLatex* ths = new TLatex(330., 2., "NLO+NLL #tilde{t}");
  ths->SetTextColor(kRed);
  ths->SetTextFont(42);
  ths->SetTextSize(0.035);
  //ths->Draw();

  // not explored label
  TText* ne = new TText(125., .2, "Not Sensitive");
  ne->SetTextColor(kRed+1);
  ne->SetTextFont(42);
  ne->SetTextAngle(90);
  ne->SetTextSize(0.035);
  //ne->Draw();

  blurb->Draw();

  canvas->RedrawAxis();

  canvas->Print("mchampMassLimit.pdf");
  canvas->Print("mchampMassLimit.C");

  plots.calculateIntercepts();
  
}

