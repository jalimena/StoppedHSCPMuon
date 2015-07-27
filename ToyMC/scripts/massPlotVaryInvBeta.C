/// .L massPlot.C+
// lifetimePlot("limit_summary.txt", "time_profile_summary.txt")

// ***********************************************
// The following parameters (LUMI, MAXLUMI) need to be set by hand:
// LUMI is a double
#define LUMI 4560.
// MAXINSTLUMI is a double
// Get MAXINSTLUMI directly from https://cmswbm.web.cern.ch/cmswbm/cmsdb/servlet/FillReport 
// (PeakInstLumi).  
// Units are 10^30 cm^-2 s^-1
#define MAXINSTLUMI 3300.
// ENERGY is a string
#define ENERGY "8"
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

//#include "DifferentXSLimitPlots.h"

// .L massPlot.C+
// massPlot("limit_summary.txt", "time_profile_summary.txt");

void massPlotVaryInvBeta(double lumi=-1., double maxInstLumi=-1.) {
	
  if (lumi<0)
    lumi=LUMI;
  if (maxInstLumi<0)
    maxInstLumi=MAXINSTLUMI;

  //mchamp index 0 is used, corresponds to 0th mass point = 100 GeV
  //plots.calculateCrossSections(7,4,0,39,9);
    

  const int NumFiles = 4;
  //pt=35
  TFile f_invbetaP3("mchampAllMass_invbetaP3/histos.root");
  TFile f_invbetaP5("mchampAllMass_pt35/histos.root");
  TFile f_invbetaP7("mchampAllMass_invbetaP7/histos.root");
  //TFile f_invbetaP8("mchampAllMass_invbetaP8/histos.root");
  //TFile f_invbetaP9("mchampAllMass_invbetaP9/histos.root");
  TFile f_invbeta1("mchampAllMass_invbeta1/histos.root");
  //TFile f_invbeta1P3("mchampAllMass_invbeta1P3/histos.root");
  //TFile f_invbeta1P6("mchampAllMass_invbeta1P6/histos.root");

  
  //Graph0 is expected limit
  TGraph* m_exp_graph[NumFiles];
  m_exp_graph[0] = (TGraph*) f_invbetaP3.Get("Graph0");
  m_exp_graph[1] = (TGraph*) f_invbetaP5.Get("Graph0");
  m_exp_graph[2] = (TGraph*) f_invbetaP7.Get("Graph0");
  m_exp_graph[3] = (TGraph*) f_invbeta1.Get("Graph0");
  //m_exp_graph[4] = (TGraph*) f_invbetaP9.Get("Graph0");
  //m_exp_graph[5] = (TGraph*) f_invbeta1.Get("Graph0");

  //Graph1 is theory curve
  TGraph* m_theory_graph = f_invbetaP5.Get("Graph1");

  TCanvas* canvas = new TCanvas("canvas");
  //canvas->SetGrid();
  canvas->SetLogy();
  
  TH1 * h;
  h = canvas->DrawFrame(100., 1e-5, 1000., 1e4);
  h->SetTitle(";m_{mchamp} [GeV];#sigma(pp #rightarrow mch mch) #times BF(mch #rightarrow #mu#mu)  [pb]");
  //h->SetTitle("Beamgap Expt;m_{#tilde{g}} [GeV/c^{2}]; #sigma(pp #rightarrow #tilde{g}#tilde{g}) #times BR(#tilde{g} #rightarrow g#tilde{#chi}^{0}) [pb]");
  
  // not covered region
  TBox* nc = new TBox(100., .1, 150., 5e2);
  nc->SetFillStyle(3354);
  nc->SetFillColor(kRed-4);
  //nc->Draw();
  
  // details
  //TPaveText* blurb = new TPaveText(305., 1.e1, 550., 4.5e2);
  TPaveText* blurb = new TPaveText(0.25, 0.70, 0.50, 0.92, "NDC");
  blurb->AddText("CMS Preliminary 2012");
  
  std::stringstream label;
  label<<"#int L dt = 19.7 fb^{-1}";
  blurb->AddText(label.str().c_str());
  label.str("");
  double peakInstLumi=maxInstLumi;
  int exponent=30;
  while (peakInstLumi>10) {
    peakInstLumi/=10.;
    ++exponent;
  }
  //label<<"L^{max}_{inst} = "<<peakInstLumi<<" x 10^{"<<exponent<<"} cm^{-2}s^{-1}";
  //blurb->AddText(label.str().c_str());
  //label.str("");
  label << "#sqrt{s} = " << ENERGY << " TeV";
  blurb->AddText(label.str().c_str());
  //blurb->AddText("m_{#tilde{g}} - m_{#tilde{#chi}^{0}} = 100 GeV/c^{2}");
  //blurb->AddText("m_{#tilde{t}} - m_{#tilde{#chi}^{0}} = 180 GeV/c^{2}");	
  blurb->SetTextFont(42);
  blurb->SetBorderSize(0);
  blurb->SetFillColor(0);
  blurb->SetShadowColor(0);
  blurb->SetTextAlign(12);
  blurb->SetTextSize(0.033);
  
  
  // legend
  TBox *legbg = new TBox(600., 1.e1, 900., 4e2);
  //legbg->Draw();
  
   
  //int color[NumFiles] = {12,13,14,1,2,4,11,6,8,15,16,17}; 
  int color[NumFiles] = {1,2,4,11};//,6,8};//,15,16,17}; 
  int marker[NumFiles] = {20,21,22,23};//,24,25};//,26,27,28,29,30,31};
  for(int a=0; a<NumFiles; a++){
    m_exp_graph[a]->SetLineColor(color[a]);
    m_exp_graph[a]->SetMarkerStyle(marker[a]);
  }


  char* LegFile[NumFiles] = {"InvBeta=0.3","InvBeta=0.5","InvBeta=0.7","InvBeta=1.0"};
  char LegEntry[100];

  //TLegend *leg = new TLegend(600., 1.e1, 900., 4e2,"95% C.L. Limits","");
  TLegend* leg = new TLegend(0.67, 0.70, 0.82, 0.92,"95% CL Limits:","NDC");
  leg->SetTextSize(0.033);
  leg->SetBorderSize(0);
  leg->SetTextFont(42);
  leg->SetFillColor(0);
  //leg->AddEntry(g_obs_mchamp, "Obs.: 10 #mus - 1000 s", "p");
  //leg->AddEntry(g_mchamp, "Exp.: 10 #mus - 1000 s", "l");
  for(int a=0; a<NumFiles; a++){
    sprintf(LegEntry,"%s",LegFile[a]);
    leg->AddEntry(m_exp_graph[a], LegEntry, "lp");
  }
  leg->AddEntry(m_theory_graph, "NLO+NLL Prediction", "l");

  //leg->AddEntry(g_thGluino, "NLO+NLL #tilde{g}", "l");
  //leg->AddEntry(g_gluino, "Obs.: 10 #mus - 1000 s Counting Exp. (#tilde{g})", "l");
  //leg->AddEntry(g_tpg, "Obs.: 10 #mus Timing Profile (#tilde{g})", "l");
  //leg->AddEntry(g_thStop, "NLO+NLL #tilde{t}", "l");
  //leg->AddEntry(g_stop, "Obs.: 10 #mus - 1000 s Counting Exp. (#tilde{t})", "l");
  //leg->AddEntry(g_tps, "Obs.: 10 #mus Timing Profile (#tilde{t})", "l");
  //leg->AddEntry(graph_em, "Obs.: 10 #mus - 1000 s Counting Exp. (EM only)", "l");
  //  leg->AddEntry(graph1, "Obs.: 570 ns Counting Exp.", "l");
  leg->Draw();


  m_theory_graph->Draw("l3");
  for(int a=0; a<NumFiles; a++){
    m_exp_graph[a]->Draw("lp");
  }

  // theory line label
  TLatex* th = new TLatex(480., 4., "NLO+NLL #tilde{g}");
  th->SetTextColor(kBlue);
  th->SetTextFont(42);
  th->SetTextSize(0.035);
  //th->Draw();

  TLatex* ths = new TLatex(330., 2., "NLO+NLL #tilde{t}");
  ths->SetTextColor(kRed);
  ths->SetTextFont(42);
  ths->SetTextSize(0.035);
  //ths->Draw();

  TLatex* thm = new TLatex(480., 4., "NLO+NLL mchamp");
  //thm->SetTextColor(kBlue);
  thm->SetTextFont(42);
  thm->SetTextSize(0.035);
  //thm->Draw();

  // not explored label
  TText* ne = new TText(125., .2, "Not Sensitive");
  ne->SetTextColor(kRed+1);
  ne->SetTextFont(42);
  ne->SetTextAngle(90);
  ne->SetTextSize(0.035);
  //ne->Draw();

  blurb->Draw();

  canvas->RedrawAxis();

  canvas->Print("massLimit_VaryInvBeta.pdf");
  canvas->Print("massLimit_VaryInvBeta.png");
  //canvas->Print("massLimit.C");

  //plots.calculateIntercepts();

}

