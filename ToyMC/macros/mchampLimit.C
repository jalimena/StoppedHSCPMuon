// .L lifetimePlot.C+
// lifetimePlot("limit_summary.txt")


// *********************************
// The following parameters (LUMI, MAXLUMI) need to be set by hand:
// LUMI is a double
#define LUMI 877.
// MAXINSTLUMI is a double
// Get MAXINSTLUMI directly from https://cmswbm.web.cern.ch/cmswbm/cmsdb/servlet/FillReport  
// (PeakInstLumi). 
// Units are 10^30 cm^-2 s^-1
#define MAXINSTLUMI 1300
// ENERGY is a string
#define ENERGY "8"
// *********************************

#include <sstream>

#include "TGraph.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TH1.h"
#include "TH1F.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TPaveText.h"

#include "LimitPlots.h"

void mchampLimit(double lumi=-1., double maxInstLumi=-1.) {


  if (lumi<0)
    lumi=LUMI;
  if (maxInstLumi<0)
    maxInstLumi=MAXINSTLUMI;
  LimitPlots plots(lumi);

  //mchamp index 0 is used, corresponds to 0th mass point = 100 GeV
  plots.calculateCrossSections(7,4,0,39,9);
  
  // graphs - observed
  TGraph* m_obs     = plots.getLimitMchamp();
  TGraph* m_obs_em  = plots.getLimitMchampEM();
  //  	TGraph* m_obs_nb = plots.getLimitMchampNB();
  TGraph* m_obs_tp  = plots.getLimitMchampTP();
  TGraph* m_exp      = plots.getExpLimitMchamp();
  TGraphAsymmErrors* m_exp_1sig = plots.getExpLimitMchamp1Sig();
  TGraphAsymmErrors* m_exp_2sig = plots.getExpLimitMchamp2Sig();
  
  TCanvas *canvas;
  canvas = new TCanvas("lifetimeLimit");
  
  canvas->SetLogx();
  canvas->SetLogy();
  
  TH1 * h;
  TPaveText *blurb;
  
  h = canvas->DrawFrame(7.5e-8, .03, 1e6, 1e2);
  // h->SetTitle("Beamgap Expt;#tau_{#tilde{g}} [s]; #sigma(pp #rightarrow #tilde{g}#tilde{g}) [cm^{2}]");
  h->SetTitle("Beamgap Expt;#tau_{#tilde{g}} [s]; #sigma(pp #rightarrow #tilde{g}#tilde{g}) #times BR(#tilde{g} #rightarrow g#tilde{#chi}^{0}) [pb]");
  
  blurb = new TPaveText(2e-7, 3, 4e-3, 80);
  blurb->AddText("CMS Preliminary 2012");
  std::stringstream label;
  label<<"#int L dt = "<<lumi<<" fb^{-1}";
  blurb->AddText(label.str().c_str());
  label.str("");
  double peakInstLumi=maxInstLumi;
  int exponent=30;
  while (peakInstLumi>10) {
    peakInstLumi/=10;
    ++exponent;
  }
  label<<"L^{max}_{inst} = "<<peakInstLumi<<" x 10^{"<<exponent<<"} cm^{-2}s^{-1}";
  blurb->AddText(label.str().c_str());
  label.str("");
  label << "#sqrt{s} = " << ENERGY << " TeV";
  blurb->AddText(label.str().c_str());
  blurb->AddText("m_{#tilde{g}} - m_{#tilde{#chi}^{0}} = 100 GeV/c^{2}");
  //blurb->AddText("m_{#tilde{g}} = 300 GeV/c^{2}");
  //blurb->AddText("m_{#tilde{#chi}^{0}} = 200 GeV/c^{2}");
  blurb->SetTextFont(42);
  blurb->SetBorderSize(0);
  blurb->SetFillColor(0);
  blurb->SetShadowColor(0);
  blurb->SetTextAlign(12);
  blurb->SetTextSize(0.033);
  blurb->Draw();
  
  TLegend *leg = new TLegend(2e-2, 3, 1e1, 80,"95% C.L. Limits:","");
  leg->SetTextSize(0.033);
  leg->SetBorderSize(0);
  leg->SetTextFont(42);
  leg->SetFillColor(0);
  leg->AddEntry(m_exp, "Expected: Counting Exp.", "l");
  leg->AddEntry(m_exp_1sig, "Expected #pm1#sigma: Counting Exp.", "f");
  leg->AddEntry(m_exp_2sig, "Expected #pm2#sigma: Counting Exp.", "f");
  leg->AddEntry(m_obs, "Observed: Counting Exp.", "l");
  //leg->AddEntry(m_obs_stop,"Obs.: Counting Exp. (#tilde{t})", "l");
  //leg->AddEntry(m_obs_nb, "Obs.: Counting Exp. (Neutral R-Baryon)", "l");
  leg->AddEntry(m_obs_em, "Observed: Counting Exp. (EM only)", "l");
  leg->AddEntry(m_obs_tp, "Observed: Timing Profile", "l");
  leg->Draw();
  
  // 2 sigma band
  if (m_exp_2sig) {
    m_exp_2sig->SetLineColor(0);
    m_exp_2sig->SetLineStyle(0);
    m_exp_2sig->SetLineWidth(0);
    m_exp_2sig->SetFillColor(kYellow);
    m_exp_2sig->SetFillStyle(1001);
    m_exp_2sig->Draw("3");
  }
  
  // 1 sigma band
  if (m_exp_1sig) {
    // m_exp_1sig->SetLineColor(8);
    m_exp_1sig->SetLineColor(0);
    m_exp_1sig->SetLineStyle(0);
    m_exp_1sig->SetLineWidth(0);
    // m_exp_1sig->SetFillColor(8);
    m_exp_1sig->SetFillColor(kGreen);
    m_exp_1sig->SetFillStyle(1001);
    // m_exp_1sig->SetFillStyle(3005);
    m_exp_1sig->Draw("3");
    // m_exp_1sig->Draw("lX");
  }
  
  //lifetime fit
  if (m_obs_tp) {
    m_obs_tp->SetLineColor(kRed);
    m_obs_tp->SetLineStyle(1);
    m_obs_tp->SetLineWidth(2);
    m_obs_tp->Draw("l3");
  }
  
  // epxected limit
  if (m_exp) {
    m_exp->SetLineColor(1);
    m_exp->SetLineStyle(2);
    m_exp->SetLineWidth(2);
    m_exp->Draw("l3");
  }
  
  TLine *l;
  l = new TLine(7.5e-8, 1.3, 1e6, 1.3); //600 GeV
  //l = new TLine(7.5e-8, 1.87, 1e6, 1.87); //500 GeV
  //l = new TLine(7.5e-8, 8.98, 1e6, 8.98); //400 GeV
  //l = new TLine(7.5e-8, 57.2, 1e6, 57.2); //300 GeV
  //l = new TLine(7.5e-8, 606, 1e6, 606); //200 GeV
  // l = new TLine(1e-8, 3.75e-34, 1e7, 3.75e-34);
  l->SetLineColor(kBlue);
  l->SetLineWidth(2);
  l->Draw();
  
  //uncertainty band
  // TBox *syst = new TBox(1e-8, 515, 1e7, 697);
  // syst->SetFillStyle(3001);
  // syst->SetFillColor(kBlue-4);
  // syst->Draw();
  
  TLatex *t1;
  //t1 = new TLatex(1.e2, 70., "NLO+NLL");
  t1 = new TLatex(0.1, 1.6, "NLO+NLL (m_{#tilde{g}} = 600 GeV/c^{2})");
  t1->SetTextColor(kBlue);
  t1->SetTextFont(42);
  t1->SetTextSize(0.035);
  t1->Draw();
  
  // observed limit
  if (m_obs) {
    m_obs->SetLineColor(1);
    m_obs->SetLineStyle(1);
    m_obs->SetLineWidth(2);
    m_obs->Draw("l");
  }
  
  // EM model
  if (m_obs_em) {
    m_obs_em->SetLineColor(kGray+2);
    m_obs_em->SetLineWidth(2);
    m_obs_em->SetLineStyle(5);
    m_obs_em->Draw("l");
  }
  
  // NB model
  //	if (m_obs_nb) {
  //		m_obs_nb->SetLineColor(kGray+1);
  //		m_obs_nb->SetLineWidth(2);
  //		m_obs_nb->SetLineStyle(5);
  //m_obs_nb->Draw("l");
  //	}
  
  canvas->RedrawAxis();
  
  canvas->Print("lifetimeLimit.png");
  canvas->Print("lifetimeLimit.pdf");
  canvas->Print("lifetimeLimit.C");
  
}
