#include "TGraph.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TH1.h"
#include "TH1F.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TPaveText.h"

#include <cstdlib>
#include <fstream>
#include <iostream> 

#include <vector>
#include <string>

class DifferentXSLimitPlots {
	public:

  DifferentXSLimitPlots(double tpLumi);
  ~DifferentXSLimitPlots();
  
  void readToyFile(std::string filename);
  void readTimeProfileFile(std::string filename);
  //void readGluinoData(std::string filename);
  //void readStopData(std::string filename);
  void readLimitGluinoData(std::string filename);
  void readLimitStopData(std::string filename);
  void readLimitMchampData(std::string filename);
  void readStauData(std::string filename);
  
  void calculateCrossSections(unsigned gluinoIndex,
			      unsigned stopIndex,
			      unsigned mchampIndex,
			      unsigned toyIndex,     // toyIndex resets to index of 1 sec data point
			      unsigned tpIndex);
  
  void calculateIntercepts();
  double calculateMassLimits(TGraph* gTheory, TGraph* gData);
  std::vector<double> calculateMassLimitsWithErrors(TGraph* gTheory, TGraphAsymmErrors* gData);
  
  TGraph* getLimitGluinoBasic();
  TGraph* getLimitGluino();
  TGraph* getLimitGluinoNB();
  TGraph* getLimitGluinoEM();
  TGraph* getLimitGluinoTP();
  
  TGraph* getExpLimitGluino();
  TGraphAsymmErrors* getExpLimitGluino1Sig();
  TGraphAsymmErrors* getExpLimitGluino2Sig();
  
  TGraph* getLimitStopBasic();
  TGraph* getLimitStop();
  TGraph* getLimitStopNB();
  TGraph* getLimitStopEM();
  TGraph* getLimitStopTP();
  
  TGraph* getExpLimitStop();
  TGraphAsymmErrors* getExpLimitStop1Sig();
  TGraphAsymmErrors* getExpLimitStop2Sig();

  TGraph* getLimitMchampBasic();
  TGraph* getLimitMchamp();
  TGraph* getLimitMchampTP();
  
  TGraph* getExpLimitMchamp();
  TGraphAsymmErrors* getExpLimitMchamp1Sig();
  TGraphAsymmErrors* getExpLimitMchamp2Sig();
  
  TGraph* getMassLimitGluino();
  TGraph* getMassLimitGluinoTP();
  
  TGraph* getExpMassLimitGluino();
  TGraphAsymmErrors* getExpMassLimitGluino1Sig();
  TGraphAsymmErrors* getExpMassLimitGluino2Sig();
  
  TGraph* getMassLimitStop();
  TGraph* getMassLimitStopTP();
  
  TGraph* getExpMassLimitStop();
  TGraphAsymmErrors* getExpMassLimitStop1Sig();
  TGraphAsymmErrors* getExpMassLimitStop2Sig();

  TGraph* getMassLimitMchamp();
  TGraph* getMassLimitMchampTP();
  
  TGraph* getExpMassLimitMchamp();
  TGraphAsymmErrors* getExpMassLimitMchamp1Sig();
  TGraphAsymmErrors* getExpMassLimitMchamp2Sig();
  
  TGraph* getGluinoTheory();
  TGraph* getStopTheory();
  TGraph* getMchampTheory();
  
 private:
  
  // lumi for TP XS
  double tpLumi_;
  
  // toy MC results
  int nToyLifetime;
  std::vector<double> toyLifetime;
  std::vector<double> toyEffLumi;
  std::vector<double> toyExpBG;
  std::vector<double> toyExpBGErr;
  std::vector<double> toyObs;
  std::vector<double> toyObsLimit;
  std::vector<double> toyExpLimit;
  std::vector<double> toyExpLimitLo1Sig;
  std::vector<double> toyExpLimitHi1Sig;
  std::vector<double> toyExpLimitLo2Sig;
  std::vector<double> toyExpLimitHi2Sig;
  
  // time profile results
  int nTPLifetime;
  std::vector<double> tpLifetime;
  std::vector<double> tpObsLimit;
  
  // gluino info
  std::vector<double> gluinoMass;
  std::vector<double> gluinoChi0Mass;
  std::vector<double> gluinoEffStopCM;
  std::vector<double> gluinoEffStopNB;
  std::vector<double> gluinoEffStopEM;
  std::vector<double> gluinoEffReco;
  std::vector<double> gluinoEffLumi;
  std::vector<double> gluinoExpBG;
  std::vector<double> gluinoExpBGErr;
  std::vector<double> gluinoObs;
  std::vector<double> gluinoObsLimit;
  std::vector<double> gluinoExpLimit;
  std::vector<double> gluinoExpLimitLo1Sig;
  std::vector<double> gluinoExpLimitHi1Sig;
  std::vector<double> gluinoExpLimitLo2Sig;
  std::vector<double> gluinoExpLimitHi2Sig;
  
  // gluino theory info
  std::vector<double> gluinoTheoryMass;
  std::vector<double> gluinoTheoryXS;
  
  // stop info
  std::vector<double> stopMass;
  std::vector<double> stopChi0Mass;
  std::vector<double> stopEffStopCM;
  std::vector<double> stopEffStopNB;
  std::vector<double> stopEffStopEM;
  std::vector<double> stopEffReco;
  std::vector<double> stopEffLumi;
  std::vector<double> stopExpBG;
  std::vector<double> stopExpBGErr;
  std::vector<double> stopObs;
  std::vector<double> stopObsLimit;
  std::vector<double> stopExpLimit;
  std::vector<double> stopExpLimitLo1Sig;
  std::vector<double> stopExpLimitHi1Sig;
  std::vector<double> stopExpLimitLo2Sig;
  std::vector<double> stopExpLimitHi2Sig;
  
  //stop theory
  std::vector<double> stopTheoryMass;
  std::vector<double> stopTheoryXS;

  // mchamp info
  std::vector<double> mchampMass;
  std::vector<double> mchampEffReco;
  std::vector<double> mchampEffLumi;
  std::vector<double> mchampExpBG;
  std::vector<double> mchampExpBGErr;
  std::vector<double> mchampObs;
  std::vector<double> mchampObsLimit;
  std::vector<double> mchampExpLimit;
  std::vector<double> mchampExpLimitLo1Sig;
  std::vector<double> mchampExpLimitHi1Sig;
  std::vector<double> mchampExpLimitLo2Sig;
  std::vector<double> mchampExpLimitHi2Sig;

  
  // mchamp theory info
  std::vector<double> mchampTheoryMass;
  std::vector<double> mchampTheoryXS;
  
  // observed limits on gluino	
  std::vector<double> xsLimitToyGluino;
  std::vector<double> xsProdLimitToyGluino;
  std::vector<double> xsProdLimitToyGluinoNB;
  std::vector<double> xsProdLimitToyGluinoEM;
  std::vector<double> xsProdLimitTPGluino;
  
  // observed limits on stop
  std::vector<double> xsLimitToyStop;
  std::vector<double> xsProdLimitToyStop;
  std::vector<double> xsProdLimitToyStopNB;
  std::vector<double> xsProdLimitToyStopEM;
  std::vector<double> xsProdLimitTPStop;

  // observed limits on mchamp	
  std::vector<double> xsLimitToyMchamp;
  std::vector<double> xsProdLimitToyMchamp;
  std::vector<double> xsProdLimitToyMchampNB;
  std::vector<double> xsProdLimitToyMchampEM;
  std::vector<double> xsProdLimitTPMchamp;
  
  // observed limits on stau
  std::vector<double> xsLimitToyStau;
  
  // expected limits on gluino
  std::vector<double> xsProdExpLimitToyGluino;
  std::vector<double> xsProdExpLimitLo1SigToyGluino;
  std::vector<double> xsProdExpLimitHi1SigToyGluino;
  std::vector<double> xsProdExpLimitLo2SigToyGluino;
  std::vector<double> xsProdExpLimitHi2SigToyGluino;
  
  // expected limits on stop
  std::vector<double> xsProdExpLimitToyStop;
  std::vector<double> xsProdExpLimitLo1SigToyStop;
  std::vector<double> xsProdExpLimitHi1SigToyStop;
  std::vector<double> xsProdExpLimitLo2SigToyStop;
  std::vector<double> xsProdExpLimitHi2SigToyStop;

  // expected limits on mchamp
  std::vector<double> xsProdExpLimitToyMchamp;
  std::vector<double> xsProdExpLimitLo1SigToyMchamp;
  std::vector<double> xsProdExpLimitHi1SigToyMchamp;
  std::vector<double> xsProdExpLimitLo2SigToyMchamp;
  std::vector<double> xsProdExpLimitHi2SigToyMchamp;
  
  // observed mass limit gluino
  std::vector<double> massGluino;
  std::vector<double> xsProdMassGluino;
  std::vector<double> xsProdMassTPGluino;
  
  std::vector<double> xsProdExpMassGluino;
  std::vector<double> xsProdExpLo1SigMassGluino;
  std::vector<double> xsProdExpHi1SigMassGluino;
  std::vector<double> xsProdExpLo2SigMassGluino;
  std::vector<double> xsProdExpHi2SigMassGluino;
  
  // observed stop
  std::vector<double> massStop;
  std::vector<double> xsProdMassStop;
  std::vector<double> xsProdMassTPStop;	
  
  // expected stop
  std::vector<double> xsProdExpMassStop;
  std::vector<double> xsProdExpLo1SigMassStop;
  std::vector<double> xsProdExpHi1SigMassStop;
  std::vector<double> xsProdExpLo2SigMassStop;
  std::vector<double> xsProdExpHi2SigMassStop;

  // observed mass limit mchamp
  std::vector<double> massMchamp;
  std::vector<double> xsProdMassMchamp;
  std::vector<double> xsProdMassTPMchamp;
  
  std::vector<double> xsProdExpMassMchamp;
  std::vector<double> xsProdExpLo1SigMassMchamp;
  std::vector<double> xsProdExpHi1SigMassMchamp;
  std::vector<double> xsProdExpLo2SigMassMchamp;
  std::vector<double> xsProdExpHi2SigMassMchamp;
		
};
