//makes histograms from ntuples
//file_dataset, bx_cut, cavern_cut, generatorMuon_cut, SA_cut, genMuonMatched_cut, trigger_cut, pt_cut, cha_cut, eta_cut, Upper_cut, RPC_cut, Rpx_Bx_cut

#include "iostream"
#include "string"
#include "sstream"
#include "cmath"
#include "vector"
#include "math.h"
#include "stdlib.h"
#include "TROOT.h"
#include "TRint.h"
#include "TSystem.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TH2F.h"
#include "TClass.h"
#include "TFile.h"
#include "TTree.h"
#include "TMath.h"
#include "TObject.h"
#include "TString.h"
#include "TLorentzVector.h"
#include "Riostream.h"
#include "Cintex/Cintex.h"
#include "StoppedHSCPMuon/Ntuples/interface/StoppedHSCPMuonEvent.h"
#include "DataFormats/Math/interface/deltaR.h"

using namespace std;

double eta(double x, double y, double z, double time) {
  TLorentzVector v = TLorentzVector(x, y, z, time);
  return v.PseudoRapidity();
}

class findTreevalues_makehistos_Ntuples_allsamples{
public:
  findTreevalues_makehistos_Ntuples_allsamples(int argc, char* argv[]) {   
    doBxCut = false;
    doCavCut = false;
    doGenMuCut = false;
    doSACut = false;
    doGenMuMatchedCut = false;
    doTriggerTurnOn = false;
    doTriggerCut = false;
    doNdsaCut = false;
    doPtCut = false;
    doChaCut = false;
    doEtaCut = false;
    doUpperCut = false;
    doRpcCut = false;
    doDisStCut = false;
    doRpcBxCut = false;
    doDtHitsCut = false;
    doInvBetaErrCut = false;
    doCscHitsCut = false;
    doDtInvBetaCut = false;
    doTimeInOutCut = false;
    doTimeInOutErrCut = false;
    doDeltaTimeInOutCut = false;
    doDeltaDtInvBetaCut = false;
    doTofDirCut = false;
    doOppEtaCut = false;
    doOppPhiCut = false;
    doChargeCut = false;
    doDxyCut = false;
    doTightPhi = false;
    doCosEnrich = false;
    doPrintout = false;

    BxCutValue_ = 2;
    PreNdsaCutValue_ = 6;
    PrePtCutValue_ = 30.;
    PreChaCutValue_ = 1;
    PreRpcCutValue_ = 2;
    PreDtHitsCutValue_ = 8;
    PreInvBetaErrCutValue_ = 10.;
    PreCscHitsCutValue_ = 0;
    PreEtaCutValue_ = 1.0;

    ChaCutValue_ = 1;
    RpcCutValue_ = 2;
    DisStCutValue_ = 2;
    DtHitsCutValue_ = 8;
    CscHitsCutValue_ = 0;
    PtCutValue_ = 30.;
    EtaCutValue_ = 1.0;
    DtInvBetaCutValue_ = 0.7;
    TimeInOutCutValue_ = 0.;
    TimeInOutErrCutValue_ = 2.;
    DeltaTimeInOutCutValue_ = -20.;
    DeltaDtInvBetaCutValue_ = -1.;
    OppEtaCutValue_ = 0.1;
    OppPhiCutValue_ = 0.1;
    DxyCutValue_ = 50;

    abcdInvBetaCutValue_ = 0.0;
    abcdPtCutValue_ = 100.;

    abInvBetaCutValue_ = 0.0;
    cInvBetaCutValue_ = 0.0;
    acPtCutValue_ = 100.;
    bPtCutValue_ = 100.;

    tracker_count_ = 0.;
    eb_count_ = 0.;
    ee_count_ = 0.;
    hb_count_ = 0.;
    he_count_ = 0.;
    mb_count_ = 0.;
    me_count_ = 0.;
    other_detector_count_ = 0.;
    cavern_count_ = 0.;
    detector_count_ = 0.;
    total_count_ = 0.;

    tracker_AccCount_ = 0.;
    eb_AccCount_ = 0.;
    ee_AccCount_ = 0.;
    hb_AccCount_ = 0.;
    he_AccCount_ = 0.;
    mb_AccCount_ = 0.;
    me_AccCount_ = 0.;
    other_detector_AccCount_ = 0.;
    cavern_AccCount_ = 0.;
    detector_AccCount_ = 0.;

    pass_bx_cut = 0;
    pass_cavern_cut = 0;
    pass_Ntops_cut = 0;
    pass_Nstops_cut = 0;
    pass_Ngluinos_cut = 0;
    pass_Nmchamps_cut = 0;
    pass_Nstaus_cut = 0;
    pass_tauFromStau_cut = 0;
    pass_WFromTop_cut = 0;
    pass_muon_cut = 0;
    pass_status1muon_cut = 0;
    pass_status1muonFromW_cut = 0;
    pass_status1muonFromTau_cut = 0;
    pass_status1muonFromMuon_cut = 0;
    pass_status1muonFromBbaryon_cut = 0;
    pass_status1muonFromCbaryon_cut = 0;
    pass_status1muonFromSbaryon_cut = 0;
    pass_status1muonFromBmeson_cut = 0;
    pass_status1muonFromCmeson_cut = 0;
    pass_status1muonFromJPsi_cut = 0;
    pass_status1muonFromLightMeson_cut = 0;
    pass_generatorMuon_cut = 0;
    pass_standaloneMuon_cut = 0;
    pass_genMuonMatched_cut = 0;
    pass_10trigger_cut = 0;
    pass_trigger_cut = 0;
    pass_PreNdsa_cut = 0;
    pass_Prept_cut = 0;
    pass_Precha_cut = 0;
    pass_Preeta_cut = 0;
    pass_PreRPC_cut = 0;
    pass_PreDtHits_cut = 0;
    pass_PreInvBetaErr_cut = 0;
    pass_PreCscHits_cut = 0;
    pass_pt_cut = 0;
    pass_cha_cut = 0;
    pass_eta_cut = 0;
    pass_Upper_cut = 0;
    pass_RPC_cut = 0;
    pass_DisSt_cut = 0;
    pass_Rpc_Bx_cut = 0;
    pass_DtHits_cut = 0;
    pass_CscHits_cut = 0;
    pass_DtInvBeta_cut = 0;
    pass_TimeInOut_cut = 0;
    pass_TimeInOutErr_cut = 0;
    pass_TofDir_cut = 0;
    pass_OppEta_cut = 0;
    pass_OppPhi_cut = 0;
    pass_Dxy_cut = 0;
    pass_SA_2_cut = 0;
    pass_UpperAndLower_cut = 0;
    pass_UpperOnly_cut = 0;
    pass_LowerOnly_cut = 0;
    pass_pt_2_cut = 0;
    pass_UpperAndLower_pt30_cut = 0;
    pass_cha_2_cut = 0;
    pass_eta_2_cut = 0;
    pass_RPC_2_cut = 0;
    pass_DisSt_2_cut = 0;
    pass_Rpc_Bx_2_cut = 0;
    pass_DtHits_2_cut = 0;
    pass_DtInvBeta_2_cut = 0;
    pass_TimeInOut_2_cut = 0;
    pass_TimeInOutErr_2_cut = 0;
    pass_DeltaTimeInOut_2_cut = 0;
    pass_DeltaDtInvBeta_2_cut = 0;
    pass_TofDir_2_cut = 0;
    pass_OppEta_2_cut = 0;
    pass_OppPhi_2_cut = 0;
    pass_charge_2_cut = 0;

    nPrintedOutEvents = 0;

    nAregionHighestP_ = 0;
    nBregionHighestP_ = 0;
    nCregionHighestP_ = 0;
    nDregionHighestP_ = 0;
    nAregionRpc_ = 0;
    nBregionRpc_ = 0;
    nCregionRpc_ = 0;
    nDregionRpc_ = 0;
    nAregion = 0;
    nBregion = 0;
    nCregion = 0;
    nDregion = 0;
    nAregionDir = 0;
    nBregionDir = 0;
    nCregionDir = 0;
    nDregionDir = 0;
    nAprimeRegion = 0;
    nBprimeRegion = 0;
    nA1region = 0;
    nA2region = 0;
    nA3region = 0;
    nA4region = 0;
    nB1region = 0;
    nB2region = 0;
    nB3region = 0;
    nB4region = 0;
    nC1region = 0;
    nC2region = 0;
    nC3region = 0;
    nC4region = 0;

    for(int a=0; a<=50; a++){
      nUpperPLargerThanCut[a] = 0.;
      nLowerPLargerThanCut[a] = 0.;
      nHighestPLargerThanCut[a] = 0.;
      nDifferencePLargerThanCut[a] = 0.;
      nAvePLargerThanCut[a] = 0.;

      nUpperPtLargerThanCut[a] = 0.;
      nLowerPtLargerThanCut[a] = 0.;
      nHighestPtLargerThanCut[a] = 0.;
      nDifferencePtLargerThanCut[a] = 0.;
      nAvePtLargerThanCut[a] = 0.;
      nProductPtLargerThanCut[a] = 0.;

      nAregionUpperP[a] = 0.;
      nBregionUpperP[a] = 0.;
      nCregionUpperP[a] = 0.;
      nDregionUpperP[a] = 0.; 
      nAregionLowerP[a] = 0.;
      nBregionLowerP[a] = 0.;
      nCregionLowerP[a] = 0.;
      nDregionLowerP[a] = 0.; 
      nAregionHighestP[a] = 0.;
      nBregionHighestP[a] = 0.;
      nCregionHighestP[a] = 0.;
      nDregionHighestP[a] = 0.; 
      nAregionDifferenceP[a] = 0.;
      nBregionDifferenceP[a] = 0.;
      nCregionDifferenceP[a] = 0.;
      nDregionDifferenceP[a] = 0.; 
      nAregionAveP[a] = 0.;
      nBregionAveP[a] = 0.;
      nCregionAveP[a] = 0.;
      nDregionAveP[a] = 0.; 

      nAregionUpperPt[a] = 0.;
      nBregionUpperPt[a] = 0.;
      nCregionUpperPt[a] = 0.;
      nDregionUpperPt[a] = 0.; 
      nAregionLowerPt[a] = 0.;
      nBregionLowerPt[a] = 0.;
      nCregionLowerPt[a] = 0.;
      nDregionLowerPt[a] = 0.; 
      nAregionHighestPt[a] = 0.;
      nBregionHighestPt[a] = 0.;
      nCregionHighestPt[a] = 0.;
      nDregionHighestPt[a] = 0.; 
      nAregionDifferencePt[a] = 0.;
      nBregionDifferencePt[a] = 0.;
      nCregionDifferencePt[a] = 0.;
      nDregionDifferencePt[a] = 0.; 
      nAregionAvePt[a] = 0.;
      nBregionAvePt[a] = 0.;
      nCregionAvePt[a] = 0.;
      nDregionAvePt[a] = 0.; 
      nAregionProductPt[a] = 0.;
      nBregionProductPt[a] = 0.;
      nCregionProductPt[a] = 0.;
      nDregionProductPt[a] = 0.;
    }

    for(int a=0; a<=10; a++){
      nAregionInverseBeta[a] = 0.;
      nBregionInverseBeta[a] = 0.;
      nCregionInverseBeta[a] = 0.;
      nDregionInverseBeta[a] = 0.; 
      nAregionTimeInOut[a] = 0.;
      nBregionTimeInOut[a] = 0.;
      nCregionTimeInOut[a] = 0.;
      nDregionTimeInOut[a] = 0.; 
      nAregionDifferenceInverseBeta[a] = 0.;
      nBregionDifferenceInverseBeta[a] = 0.;
      nCregionDifferenceInverseBeta[a] = 0.;
      nDregionDifferenceInverseBeta[a] = 0.; 
      nAregionDifferenceTimeInOut[a] = 0.;
      nBregionDifferenceTimeInOut[a] = 0.;
      nCregionDifferenceTimeInOut[a] = 0.;
      nDregionDifferenceTimeInOut[a] = 0.; 
    }

    // for printouts
    PtPrecision = 1;
    EtaPrecision = 1;
    PhiPrecision = 1;
    ChargePrecision = 0;
    X2DOFPrecision = 1;
    TimeAtIpInOutPrecision = 2;    
    line = 2;

    //define histograms
    id_hist = new TH1D("id_hist","Event Number",100000,0,100000);
    run_hist = new TH1D("run_hist","Run Number",10000,190000,210000);
    bx_hist = new TH1D("bx_hist","BX",8000,0,4000);
    bxWrtCollision_hist = new TH1D("bxWrtCollision_hist","BX w.r.t. Collision",4000,-1000,1000);
    bxWrtBunch_hist = new TH1D("bxWrtBunch_hist","BX w.r.t. Bunch",4000,-1000,1000);
    
    mcStoppedParticle_N_hist = new TH1D("mcStoppedParticle_N_hist","Number of Stopped Particles",5,0,5);
    mcStoppedParticleX_hist = new TH1D("mcStoppedParticleX_hist","Stopped Particle X",300,-1500,1500);
    mcStoppedParticleY_hist = new TH1D("mcStoppedParticleY_hist","Stopped Particle Y",300,-1500,1500);
    mcStoppedParticleZ_hist = new TH1D("mcStoppedParticleZ_hist","Stopped Particle Z",300,-1500,1500);
    mcStoppedParticleR_hist = new TH1D("mcStoppedParticleR_hist","Stopped Particle R",300,0,1500);
    mcStoppedParticleEta_hist = new TH1D("mcStoppedParticleEta_hist","StoppedParticle #eta",120,-6,6);
    mcStoppedParticlePhi_hist = new TH1D("mcStoppedParticlePhi_hist","StoppedParticle #phi",64,-3.2,3.2);
    mcStoppedParticleTime_hist = new TH1D("mcStoppedParticleTime_hist","StoppedParticle Time",100,0,500);
    mcStoppedParticleXY_hist = new TH2D("mcStoppedParticleXY_hist","Stopped Particle X vs Y",300,-1500,1500,300,-1500,1500);
    mcStoppedParticleR_muDisplacedStandAloneEta_hist = new TH2D("mcStoppedParticleR_muDisplacedStandAloneEta_hist","Stopped Particle R vs SA #eta",300,0,1500,120,-6,6);
    mcStoppedParticleMass_hist = new TH1D("mcStoppedParticleMass_hist","Stopped Particle Mass",100,0,2000);
    mcStoppedParticleId_hist = new TH1D("mcStoppedParticleId_hist","Stopped Particle Id",100,0,2000);
    mcStoppedParticleCharge_hist = new TH1D("mcStoppedParticleCharge_hist","Stopped Particle Charge",6,-3,3);

    mcStoppedParticleX_StoppedParticleN_hist = new TH2D("mcStoppedParticleX_mcStoppedParticleN_hist","Stopped Particle X vs Number of Stopped Particles",300,-1500,1500,5,0,5);
    mcStoppedParticleY_StoppedParticleN_hist = new TH2D("mcStoppedParticleY_mcStoppedParticleN_hist","Stopped Particle X vs Number of Stopped Particles",300,-1500,1500,5,0,5);
    mcStoppedParticleZ_StoppedParticleN_hist = new TH2D("mcStoppedParticleZ_mcStoppedParticleN_hist","Stopped Particle X vs Number of Stopped Particles",300,-1500,1500,5,0,5);
    mcStoppedParticleId_StoppedParticleN_hist = new TH2D("mcStoppedParticleId_mcStoppedParticleN_hist","Stopped Particle PdgId vs Number of Stopped Particles",100,0,2000,5,0,5);
    mcStoppedParticleCharge_StoppedParticleN_hist = new TH2D("mcStoppedParticleCharge_mcStoppedParticleN_hist","Stopped Particle Charge vs Number of Stopped Particles",6,-3,3,5,0,5);
    mcStoppedParticleTime_mcStoppedParticleCharge_hist = new TH2D("mcStoppedParticleTime_mcStoppedParticleCharge_hist","Stopped Particle Time vs Charge",100,0,500,6,-3,3);

    mcStoppedParticleCharge_StoppedParticleN_hist->SetTitle(";Stopped Particle Charge;Number of Stopped Particles");
    mcStoppedParticleTime_mcStoppedParticleCharge_hist->SetTitle(";Stopped Particle Time [ns];Stopped Particle Charge");
    
    
    mcStoppedParticleXPos2Stopped_hist = new TH1D("mcStoppedParticleXPos2Stopped_hist","Stopped Particle X for pos when 2 stopped",300,-1500,1500);
    mcStoppedParticleYPos2Stopped_hist = new TH1D("mcStoppedParticleYPos2Stopped_hist","Stopped Particle Y for pos when 2 stopped",300,-1500,1500);
    mcStoppedParticleZPos2Stopped_hist = new TH1D("mcStoppedParticleZPos2Stopped_hist","Stopped Particle Z for pos when 2 stopped",300,-1500,1500);
    mcStoppedParticleRPos2Stopped_hist = new TH1D("mcStoppedParticleRPos2Stopped_hist","Stopped Particle R for pos when 2 stopped",300,0,1500);
    mcStoppedParticleXNeg2Stopped_hist = new TH1D("mcStoppedParticleXNeg2Stopped_hist","Stopped Particle X for neg when 2 stopped",300,-1500,1500);
    mcStoppedParticleYNeg2Stopped_hist = new TH1D("mcStoppedParticleYNeg2Stopped_hist","Stopped Particle Y for neg when 2 stopped",300,-1500,1500);
    mcStoppedParticleZNeg2Stopped_hist = new TH1D("mcStoppedParticleZNeg2Stopped_hist","Stopped Particle Z for neg when 2 stopped",300,-1500,1500);
    mcStoppedParticleRNeg2Stopped_hist = new TH1D("mcStoppedParticleRNeg2Stopped_hist","Stopped Particle R for neg when 2 stopped",300,0,1500);
    mcStoppedParticleDeltaTime_hist = new TH1D("mcStoppedParticleDeltaTime_hist","StoppedParticle #Delta Time",100,0,100);

    mcStoppedParticleXPos_hist = new TH1D("mcStoppedParticleXPos_hist","Stopped Particle X for pos when 1 stopped",300,-1500,1500);
    mcStoppedParticleYPos_hist = new TH1D("mcStoppedParticleYPos_hist","Stopped Particle Y for pos when 1 stopped",300,-1500,1500);
    mcStoppedParticleZPos_hist = new TH1D("mcStoppedParticleZPos_hist","Stopped Particle Z for pos when 1 stopped",300,-1500,1500);
    mcStoppedParticleRPos_hist = new TH1D("mcStoppedParticleRPos_hist","Stopped Particle R for pos when 1 stopped",300, 0,1500);
    mcStoppedParticleXNeg_hist = new TH1D("mcStoppedParticleXNeg_hist","Stopped Particle X for neg when 1 stopped",300,-1500,1500);
    mcStoppedParticleYNeg_hist = new TH1D("mcStoppedParticleYNeg_hist","Stopped Particle Y for neg when 1 stopped",300,-1500,1500);
    mcStoppedParticleZNeg_hist = new TH1D("mcStoppedParticleZNeg_hist","Stopped Particle Z for neg when 1 stopped",300,-1500,1500);
    mcStoppedParticleRNeg_hist = new TH1D("mcStoppedParticleRNeg_hist","Stopped Particle R for neg when 1 stopped",300, 0,1500);

    mcStoppedParticle0Charge_hist = new TH1D("mcStoppedParticle0Charge_hist","1st of 2 Stopped Particle Charge",6,-3,3);
    mcStoppedParticle1Charge_hist = new TH1D("mcStoppedParticle1Charge_hist","2nd of 2 Stopped Particle Charge",6,-3,3);
    mcStoppedParticle0Time_hist = new TH1D("mcStoppedParticle0Time_hist","1st of 2 Stopped Particle Time",100,0,500);
    mcStoppedParticle1Time_hist = new TH1D("mcStoppedParticle1Time_hist","2nd of 2 Stopped Particle Time",100,0,500);

    mcLL_N_hist = new TH1D("mcLL_N_hist","Number of Gen LL Particles",10,0,10);
    mcLLStatus_hist = new TH1D("mcLLStatus_hist","Gen LL Particle Status",10,0,10);
    mcLLPt_hist = new TH1D("mcLLPt_hist","Gen LL Particle p_{T}",200,0,200);
    mcLLEta_hist = new TH1D("mcLLEta_hist","Gen LL Particle #eta",120,-6,6);
    mcLLPhi_hist = new TH1D("mcLLPhi_hist","Gen LL Particle #phi",64,-3.2,3.2);
    mcLLCharge_hist = new TH1D("mcLLCharge_hist","Gen LL Particle Charge",6,-3,3);
    mcLLMass_hist = new TH1D("mcLLMass_hist","Gen LL Particle Mass",40,0,0.2);
    mcLLNDaughters_hist = new TH1D("mcLLNDaughters_hist","Number of Daughters of Gen LL Particles",10,0,10);
    mcLLDaughterId_hist = new TH1D("mcLLDaughterId_hist","Daughter Id of Gen LL Particles",50,-25,25);

    mcRhadron_N_hist = new TH1D("mcRhadron_N_hist","Number of Gen Rhadron Particles",10,0,10);
    mcRhadronPt_hist = new TH1D("mcRhadronPt_hist","Gen Rhadron Particle p_{T}",200,0,200);
    mcRhadronEta_hist = new TH1D("mcRhadronEta_hist","Gen Rhadron Particle #eta",120,-6,6);
    mcRhadronPhi_hist = new TH1D("mcRhadronPhi_hist","Gen Rhadron Particle #phi",64,-3.2,3.2);
    mcRhadronCharge_hist = new TH1D("mcRhadronCharge_hist","Gen Rhadron Particle Charge",6,-3,3);

    mcStop_N_hist = new TH1D("mcStop_N_hist","Number of Gen Stops",10,0,10);
    mcStop0Charge_hist = new TH1D("mcStop0Charge_hist","1st Gen stop Particle Charge",6,-3,3);
    mcStop1Charge_hist = new TH1D("mcStop1Charge_hist","2nd Gen stop Particle Charge",6,-3,3);
    mcStopP_hist = new TH1D("mcStopP_hist","Gen Stop p",5000,0,5000);
    mcStopPx_hist = new TH1D("mcStopPx_hist","Gen Stop p_{x}",5000,-5000,5000);
    mcStopPy_hist = new TH1D("mcStopPy_hist","Gen Stop p_{y}",5000,-5000,5000);
    mcStopPz_hist = new TH1D("mcStopPz_hist","Gen Stop p_{z}",5000,-5000,5000);
    mcStopPt_hist = new TH1D("mcStopPt_hist","Gen Stop p_{T}",5000,0,5000);
    mcStopEta_hist = new TH1D("mcStopEta_hist","Gen Stop #eta",160,-8,8);   
    mcStopPhi_hist = new TH1D("mcStopPhi_hist","Gen Stop #phi",64,-3.2,3.2);
    mcStopBeta_hist = new TH1D("mcStopBeta_hist","Gen Stop #beta",100,0,1);   

    stopped_mcStopP_hist = new TH1D("stopped_mcStopP_hist","Gen Stop initial p of stopped particle",5000,0,5000);
    stopped_mcStopPt_hist = new TH1D("stopped_mcStopPt_hist","Gen Stop initial pt of stopped particle",5000,0,5000);
    stopped_mcStopEta_hist = new TH1D("stopped_mcStopEta_hist","Gen Stop #eta of stopped particle",160,-8,8);   
    stopped_mcStopPhi_hist = new TH1D("stopped_mcStopPhi_hist","Gen Stop #phi of stopped particle",64,-3.2,3.2);
    stopped_mcStopBeta_hist = new TH1D("stopped_mcStopBeta_hist","Gen Stop initial beta of stopped particle",100,0,1);
    notStopped_mcStopP_hist = new TH1D("notStopped_mcStopP_hist","Gen Stop initial p of NOT stopped particle",5000,0,5000);
    notStopped_mcStopPt_hist = new TH1D("notStopped_mcStopPt_hist","Gen Stop initial pt of NOT stopped particle",5000,0,5000);
    notStopped_mcStopEta_hist = new TH1D("notStopped_mcStopEta_hist","Gen Stop #eta of stopped particle",160,-8,8);   
    notStopped_mcStopPhi_hist = new TH1D("notStopped_mcStopPhi_hist","Gen Stop #phi of stopped particle",64,-3.2,3.2);
    notStopped_mcStopBeta_hist = new TH1D("notStopped_mcStopBeta_hist","Gen Stop initial beta of NOT stopped particle",100,0,1);

    mcGluino_N_hist = new TH1D("mcGluino_N_hist","Number of Gen Gluinos",10,0,10);
    mcGluino0Charge_hist = new TH1D("mcGluino0Charge_hist","1st Gen gluino Particle Charge",6,-3,3);
    mcGluino1Charge_hist = new TH1D("mcGluino1Charge_hist","2nd Gen gluino Particle Charge",6,-3,3);
    mcGluinoP_hist = new TH1D("mcGluinoP_hist","Gen Gluino p",5000,0,5000);
    mcGluinoPx_hist = new TH1D("mcGluinoPx_hist","Gen Gluino p_{x}",5000,-5000,5000);
    mcGluinoPy_hist = new TH1D("mcGluinoPy_hist","Gen Gluino p_{y}",5000,-5000,5000);
    mcGluinoPz_hist = new TH1D("mcGluinoPz_hist","Gen Gluino p_{z}",5000,-5000,5000);
    mcGluinoPt_hist = new TH1D("mcGluinoPt_hist","Gen Gluino p_{T}",5000,0,5000);
    mcGluinoEta_hist = new TH1D("mcGluinoEta_hist","Gen Gluino #eta",160,-8,8);   
    mcGluinoPhi_hist = new TH1D("mcGluinoPhi_hist","Gen Gluino #phi",64,-3.2,3.2);
    mcGluinoBeta_hist = new TH1D("mcGluinoBeta_hist","Gen Gluino #beta",100,0,1);   

    stopped_mcGluinoP_hist = new TH1D("stopped_mcGluinoP_hist","Gen Gluino initial p of stopped particle",5000,0,5000);
    stopped_mcGluinoPt_hist = new TH1D("stopped_mcGluinoPt_hist","Gen Gluino initial pt of stopped particle",5000,0,5000);
    stopped_mcGluinoEta_hist = new TH1D("stopped_mcGluinoEta_hist","Gen Gluino #eta of stopped particle",160,-8,8);   
    stopped_mcGluinoPhi_hist = new TH1D("stopped_mcGluinoPhi_hist","Gen Gluino #phi of stopped particle",64,-3.2,3.2);
    stopped_mcGluinoBeta_hist = new TH1D("stopped_mcGluinoBeta_hist","Gen Gluino initial beta of stopped particle",100,0,1);
    notStopped_mcGluinoP_hist = new TH1D("notStopped_mcGluinoP_hist","Gen Gluino initial p of NOT stopped particle",5000,0,5000);
    notStopped_mcGluinoPt_hist = new TH1D("notStopped_mcGluinoPt_hist","Gen Gluino initial pt of NOT stopped particle",5000,0,5000);
    notStopped_mcGluinoEta_hist = new TH1D("notStopped_mcGluinoEta_hist","Gen Gluino #eta of stopped particle",160,-8,8);   
    notStopped_mcGluinoPhi_hist = new TH1D("notStopped_mcGluinoPhi_hist","Gen Gluino #phi of stopped particle",64,-3.2,3.2);
    notStopped_mcGluinoBeta_hist = new TH1D("notStopped_mcGluinoBeta_hist","Gen Gluino initial beta of NOT stopped particle",100,0,1);

    mcStau_N_hist = new TH1D("mcStau_N_hist","Number of Gen Staus",10,0,10);
    mcStau0Charge_hist = new TH1D("mcStau0Charge_hist","1st Gen stau Particle Charge",6,-3,3);
    mcStau1Charge_hist = new TH1D("mcStau1Charge_hist","2nd Gen stau Particle Charge",6,-3,3);
    mcStauP_hist = new TH1D("mcStauP_hist","Gen Stau p",5000,0,5000);
    mcStauPx_hist = new TH1D("mcStauPx_hist","Gen Stau p_{x}",5000,-5000,5000);
    mcStauPy_hist = new TH1D("mcStauPy_hist","Gen Stau p_{y}",5000,-5000,5000);
    mcStauPz_hist = new TH1D("mcStauPz_hist","Gen Stau p_{z}",5000,-5000,5000);
    mcStauPt_hist = new TH1D("mcStauPt_hist","Gen Stau p_{T}",5000,0,5000);
    mcStauEta_hist = new TH1D("mcStauEta_hist","Gen Stau #eta",160,-8,8);   
    mcStauPhi_hist = new TH1D("mcStauPhi_hist","Gen Stau #phi",64,-3.2,3.2);
    mcStauBeta_hist = new TH1D("mcStauBeta_hist","Gen Stau #beta",100,0,1);   

    stopped_mcStauP_hist = new TH1D("stopped_mcStauP_hist","Gen Stau initial p of stopped particle",5000,0,5000);
    stopped_mcStauPt_hist = new TH1D("stopped_mcStauPt_hist","Gen Stau initial pt of stopped particle",5000,0,5000);
    stopped_mcStauEta_hist = new TH1D("stopped_mcStauEta_hist","Gen Stau #eta of stopped particle",160,-8,8);   
    stopped_mcStauPhi_hist = new TH1D("stopped_mcStauPhi_hist","Gen Stau #phi of stopped particle",64,-3.2,3.2);
    stopped_mcStauBeta_hist = new TH1D("stopped_mcStauBeta_hist","Gen Stau initial beta of stopped particle",100,0,1);
    notStopped_mcStauP_hist = new TH1D("notStopped_mcStauP_hist","Gen Stau initial p of NOT stopped particle",5000,0,5000);
    notStopped_mcStauPt_hist = new TH1D("notStopped_mcStauPt_hist","Gen Stau initial pt of NOT stopped particle",5000,0,5000);
    notStopped_mcStauEta_hist = new TH1D("notStopped_mcStauEta_hist","Gen Stau #eta of stopped particle",160,-8,8);   
    notStopped_mcStauPhi_hist = new TH1D("notStopped_mcStauPhi_hist","Gen Stau #phi of stopped particle",64,-3.2,3.2);
    notStopped_mcStauBeta_hist = new TH1D("notStopped_mcStauBeta_hist","Gen Stau initial beta of NOT stopped particle",100,0,1);
    
    mcH0Charge_hist = new TH1D("mcH0Charge_hist","1st Gen H++/mchamp Particle Charge",6,-3,3);
    mcH1Charge_hist = new TH1D("mcH1Charge_hist","2nd Gen H++/mchamp Particle Charge",6,-3,3);

    mcHPlusPlusP_hist = new TH1D("mcHPlusPlusP_hist","Gen H++ p",5000,0,5000);
    mcHPlusPlusPx_hist = new TH1D("mcHPlusPlusPx_hist","Gen H++ p_{x}",5000,-5000,5000);
    mcHPlusPlusPy_hist = new TH1D("mcHPlusPlusPy_hist","Gen H++ p_{y}",5000,-5000,5000);
    mcHPlusPlusPz_hist = new TH1D("mcHPlusPlusPz_hist","Gen H++ p_{z}",5000,-5000,5000);
    mcHPlusPlusPt_hist = new TH1D("mcHPlusPlusPt_hist","Gen H++ p_{T}",5000,0,5000);
    mcHPlusPlusEta_hist = new TH1D("mcHPlusPlusEta_hist","Gen H++ #eta",160,-8,8);   
    mcHPlusPlusPhi_hist = new TH1D("mcHPlusPlusPhi_hist","Gen H++ #phi",64,-3.2,3.2);
    mcHMinusMinusP_hist = new TH1D("mcHMinusMinusP_hist","Gen H-- p",5000,0,5000);
    mcHMinusMinusPx_hist = new TH1D("mcHMinusMinusPx_hist","Gen H-- p_{x}",5000,-5000,5000);
    mcHMinusMinusPy_hist = new TH1D("mcHMinusMinusPy_hist","Gen H-- p_{y}",5000,-5000,5000);
    mcHMinusMinusPz_hist = new TH1D("mcHMinusMinusPz_hist","Gen H-- p_{z}",5000,-5000,5000);
    mcHMinusMinusPt_hist = new TH1D("mcHMinusMinusPt_hist","Gen H-- p_{T}",5000,0,5000);
    mcHMinusMinusEta_hist = new TH1D("mcHMinusMinusEta_hist","Gen H-- #eta",160,-8,8);
    mcHMinusMinusPhi_hist = new TH1D("mcHMinusMinusPhi_hist","Gen H-- #phi",64,-3.2,3.2);
    
    mcHPlusPlusP_HMinusMinusP_hist = new TH2D("mcHPlusPlusP_HMinusMinusP_hist","Gen H++ p vs H-- p",5000,0,5000,5000,0,5000);
    mcHPlusPlusPt_HMinusMinusPt_hist = new TH2D("mcHPlusPlusPt_HMinusMinusPt_hist","Gen H++ pt vs H-- pt",5000,0,5000,5000,0,5000);
    mcHPlusPlusEta_HMinusMinusEta_hist = new TH2D("mcHPlusPlusEta_HMinusMinusEta_hist","Gen H++ #eta vs H-- #eta",160,-8,8,160,-8,8);
    mcHPlusPlusPhi_HMinusMinusPhi_hist = new TH2D("mcHPlusPlusPhi_HMinusMinusPhi_hist","Gen H++ #phi vs H-- #eta",64,-3.2,3.2,64,-3.2,3.2);

    mcTauPrime_N_hist = new TH1D("mcTauPrime_N_hist","Number of Gen TauPrimes",10,0,10);
    mcTauPrime0Charge_hist = new TH1D("mcTauPrime0Charge_hist","1st Gen stau Particle Charge",6,-3,3);
    mcTauPrime1Charge_hist = new TH1D("mcTauPrime1Charge_hist","2nd Gen stau Particle Charge",6,-3,3);
    mcTauPrimeP_hist = new TH1D("mcTauPrimeP_hist","Gen TauPrime p",5000,0,5000);
    mcTauPrimePx_hist = new TH1D("mcTauPrimePx_hist","Gen TauPrime p_{x}",5000,-5000,5000);
    mcTauPrimePy_hist = new TH1D("mcTauPrimePy_hist","Gen TauPrime p_{y}",5000,-5000,5000);
    mcTauPrimePz_hist = new TH1D("mcTauPrimePz_hist","Gen TauPrime p_{z}",5000,-5000,5000);
    mcTauPrimePt_hist = new TH1D("mcTauPrimePt_hist","Gen TauPrime p_{T}",5000,0,5000);
    mcTauPrimeEta_hist = new TH1D("mcTauPrimeEta_hist","Gen TauPrime #eta",160,-8,8);   
    mcTauPrimePhi_hist = new TH1D("mcTauPrimePhi_hist","Gen TauPrime #phi",64,-3.2,3.2);
    mcTauPrimeBeta_hist = new TH1D("mcTauPrimeBeta_hist","Gen TauPrime #beta",100,0,1);   

    stopped_mcTauPrimeP_hist = new TH1D("stopped_mcTauPrimeP_hist","Gen TauPrime initial p of stopped particle",5000,0,5000);
    stopped_mcTauPrimePt_hist = new TH1D("stopped_mcTauPrimePt_hist","Gen TauPrime initial pt of stopped particle",5000,0,5000);
    stopped_mcTauPrimeEta_hist = new TH1D("stopped_mcTauPrimeEta_hist","Gen TauPrime #eta of stopped particle",160,-8,8);   
    stopped_mcTauPrimePhi_hist = new TH1D("stopped_mcTauPrimePhi_hist","Gen TauPrime #phi of stopped particle",64,-3.2,3.2);
    stopped_mcTauPrimeBeta_hist = new TH1D("stopped_mcTauPrimeBeta_hist","Gen TauPrime initial beta of stopped particle",100,0,1);
    notStopped_mcTauPrimeP_hist = new TH1D("notStopped_mcTauPrimeP_hist","Gen TauPrime initial p of NOT stopped particle",5000,0,5000);
    notStopped_mcTauPrimePt_hist = new TH1D("notStopped_mcTauPrimePt_hist","Gen TauPrime initial pt of NOT stopped particle",5000,0,5000);
    notStopped_mcTauPrimeEta_hist = new TH1D("notStopped_mcTauPrimeEta_hist","Gen TauPrime #eta of stopped particle",160,-8,8);   
    notStopped_mcTauPrimePhi_hist = new TH1D("notStopped_mcTauPrimePhi_hist","Gen TauPrime #phi of stopped particle",64,-3.2,3.2);
    notStopped_mcTauPrimeBeta_hist = new TH1D("notStopped_mcTauPrimeBeta_hist","Gen TauPrime initial beta of NOT stopped particle",100,0,1);

    mcTop_N_hist = new TH1D("mcTop_N_hist","Number of Generated Tops",10,0,10);
    mcTopStatus_hist = new TH1D("mcTopStatus_hist","Gen Top Status",10,0,10);
    mcTopPt_hist = new TH1D("mcTopPt_hist","Gen Top p_{T}",200,0,200);
    mcTopEta_hist = new TH1D("mcTopEta_hist","Gen Top #eta",120,-6,6);
    mcTopPhi_hist = new TH1D("mcTopPhi_hist","Gen Top #phi",64,-3.2,3.2);
    mcTopCharge_hist = new TH1D("mcTopCharge_hist","Gen Top Charge",6,-3,3);
    mcTopMass_hist = new TH1D("mcTopMass_hist","Gen Top Mass",40,0,0.2);
    mcTopNDaughters_hist = new TH1D("mcTopNDaughters_hist","Number of Daughters of Gen Tops",10,0,10);
    mcTopDaughterId_hist = new TH1D("mcTopDaughterId_hist","Daughter Id of Gen Tops",50,-25,25);
    
    mcW_N_hist = new TH1D("mcW_N_hist","Number of Generated Ws",10,0,10);
    mcWStatus_hist = new TH1D("mcWStatus_hist","Gen W Status",10,0,10);
    mcWPt_hist = new TH1D("mcWPt_hist","Gen W p_{T}",200,0,200);
    mcWEta_hist = new TH1D("mcWEta_hist","Gen W #eta",120,-6,6);
    mcWPhi_hist = new TH1D("mcWPhi_hist","Gen W #phi",64,-3.2,3.2);
    mcWCharge_hist = new TH1D("mcWCharge_hist","Gen W Charge",6,-3,3);
    mcWMass_hist = new TH1D("mcWMass_hist","Gen W Mass",40,0,0.2);
    mcWNDaughters_hist = new TH1D("mcWNDaughters_hist","Number of Daughters of Gen Ws",10,0,10);
    mcWDaughterId_hist = new TH1D("mcWDaughterId_hist","Daughter Id of Gen Tops",200,-100,100);
    
    mcMuon_N_hist = new TH1D("mcMuon_N_hist","Number of Generated Muons",10,0,10);
    mcMuonP_hist = new TH1D("mcMuonP_hist","Gen Muon p",1000,0,1000);
    mcMuonPt_hist = new TH1D("mcMuonPt_hist","Gen Muon p_{T}",1000,0,1000);
    mcMuonEta_hist = new TH1D("mcMuonEta_hist","Gen Muon #eta",120,-6,6);
    mcMuonPhi_hist = new TH1D("mcMuonPhi_hist","Gen Muon #phi",64,-3.2,3.2);
    mcMuonCharge_hist = new TH1D("mcMuonCharge_hist","Gen Muon Charge",6,-3,3);
    mcMuonStatus_hist = new TH1D("mcMuonStatus_hist","Gen Muon Status",5,0,5);
    mcMuonMass_hist = new TH1D("mcMuonMass_hist","Gen Muon Mass",40,0,0.2);
    mcMuonMotherId_hist = new TH1D("mcMuonMotherId_hist","Mother Id of Gen Muons",20000,-10000,10000);
    mcMuonVx_hist = new TH1D("mcMuonVx_hist","Gen Muon v_{x}",5000,-30000,30000);
    mcMuonVy_hist = new TH1D("mcMuonVy_hist","Gen Muon v_{y}",5000,-30000,30000);
    mcMuonVz_hist = new TH1D("mcMuonVz_hist","Gen Muon v_{z}",5000,-30000,30000);
    mcMuonLxy_hist = new TH1D("mcMuonLxy_hist","Gen Muon L_{xy}",100,0,1000);
    mcMuonDxy_hist = new TH1D("mcMuonDxy_hist","Gen Muon d_{xy}",2000,-1000,1000);
    mcMuon3Dangle_hist = new TH1D("mcMuon3Dangle_hist","3D Angle between 2 Gen Muons",500,0,5);
    mcMuonDeltaPhi_hist = new TH1D("mcMuonDeltaPhi_hist","Delta Phi between 2 Gen Muons",500,0,5);
    mcMuonInverseBeta_hist = new TH1D("mcMuonInverseBeta_hist","Gen Muon Inverse Beta",1000,-50,50);

    mcMuonPt_l1MuonPt_hist = new TH2D("mcMuonPt_l1MuonPt_hist","Gen Muon p_{T} vs. L1 Muon p_{T}",100,0,1000,100,0,1000);
    mcMuonPt_hlt20Cha2MuonPt_hist = new TH2D("mcMuonPt_hlt20Cha2MuonPt_hist","Gen Muon p_{T} vs. L2 Muon p_{T}",100,0,1000,100,0,1000);

    mcMuonEta_l1MuonEta_hist = new TH2D("mcMuonEta_l1MuonEta_hist","Gen Muon #eta vs. L1 Muon #eta",120,-6,6,120,-6,6);
    mcMuonPhi_l1MuonPhi_hist = new TH2D("mcMuonPhi_l1MuonPhi_hist","Gen Muon #phi vs. L1 Muon #phi",64,-3.2,3.2,64,-3.2,3.2);

    mcMuonEta_hlt20Cha2MuonEta_hist = new TH2D("mcMuonEta_hlt20Cha2MuonEta_hist","Gen Muon #eta vs. L2 Muon #eta",120,-6,6,120,-6,6);
    mcMuonPhi_hlt20Cha2MuonPhi_hist = new TH2D("mcMuonPhi_hlt20Cha2MuonPhi_hist","Gen Muon #phi vs. L2 Muon #phi",64,-3.2,3.2,64,-3.2,3.2);

    mcMuonPt_muDisplacedStandAlonePt_hist = new TH2D("mcMuonPt_muDisplacedStandAlonePt_hist","Gen Muon p_{T} vs. SA Muon p_{T}",100,0,1000,100,0,1000);
    mcMuonPt_muRefittedStandAlonePt_hist = new TH2D("mcMuonPt_muRefittedStandAlonePt_hist","Gen Muon p_{T} vs. Refitted SA Muon p_{T}",100,0,1000,100,0,1000);
    //mcMuonPt_muRefittedStandAlonePt_hist = new TH2D("mcMuonPt_muRefittedStandAlonePt_hist","Gen Muon p_{T} vs. Refitted SA Muon p_{T}",100,0,100,100,0,100);
    mcMuonPt_muCosmicPt_hist = new TH2D("mcMuonPt_muCosmicPt_hist","Gen Muon p_{T} vs. Cosmic Muon p_{T}",100,0,1000,100,0,1000);
    mcMuonPt_muCosmicTrackPt_hist = new TH2D("mcMuonPt_muCosmicTrackPt_hist","Gen Muon p_{T} vs. Cosmic Track p_{T}",100,0,1000,100,0,1000);

    simTrackN_hist = new TH1D("simTrack_N_hist","Number of Simulated Tracks",100,0,100);  
    simTrackPt_hist = new TH1D("simTrackPt_hist","Muon Sim Track p_{T}",1000,0,1000);	    
    simTrackEta_hist = new TH1D("simTrackEta_hist","Muon Sim Track #eta",120,-6,6);	    
    simTrackPhi_hist = new TH1D("simTrackPhi_hist","Muon Sim Track #phi",64,-3.2,3.2);	    
    simTrackCharge_hist = new TH1D("simTrackCharge_hist","Muon Sim Track Charge",6,-3,3);     
    simTrackVx_hist = new TH1D("simTrackVx_hist","Muon Sim Track v_{x}",5000,-30000,30000);
    simTrackVy_hist = new TH1D("simTrackVy_hist","Muon Sim Track v_{y}",5000,-30000,30000);
    simTrackVz_hist = new TH1D("simTrackVz_hist","Muon Sim Track v_{z}",5000,-30000,30000);

    muStandAloneP_hist = new TH1D("muStandAloneP_hist","SA Muon p",1000,0,1000);
    muStandAloneUpdatedAtVtxP_hist = new TH1D("muStandAloneUpdatedAtVtxP_hist","SA Muon Updated At Vtx p",1000,0,1000);

    muStandAlonePt_hist = new TH1D("muStandAlonePt_hist","SA Muon p_{T} ",1000,0,1000);
    muStandAloneUpdatedAtVtxPt_hist = new TH1D("muStandAloneUpdatedAtVtxPt_hist","SA Muon Updated At Vtx p_{T} ",1000,0,1000);
    
    muDisplacedStandAloneGenDR_hist = new TH1D("muDisplacedStandAloneGenDR_hist","dR to matched gen particle",500,0,5);
    muGenDR_hist = new TH1D("muGenDR_hist","dR to matched gen particle",500,0,5);
    muStandAloneTrackGenDR_hist = new TH1D("muStandAloneTrackGenDR_hist","dR to matched gen particle",500,0,5);
    muStandAloneTrackUpdatedAtVtxGenDR_hist = new TH1D("muStandAloneTrackUpdatedAtVtxGenDR_hist","dR to matched gen particle",500,0,5);
    muRefittedStandAloneTrackGenDR_hist = new TH1D("muRefittedStandAloneTrackGenDR_hist","dR to matched gen particle",500,0,5);
    muCosmicTrackGenDR_hist = new TH1D("muCosmicTrackGenDR_hist","dR to matched gen particle",500,0,5);

    mcStoppedParticleR_muDisplacedStandAloneGenDR_hist = new TH2D("mcStoppedParticleR_muDisplacedStandAloneGenDR_hist","",80,0,800,500,0,5);

    muDisplacedStandAlonePtResolution_hist = new TH1D("muDisplacedStandAlonePtResolution_hist","DSA Muon p_{T} Resolution",2000,-10,10);
    muPtResolution_hist = new TH1D("muPtResolution_hist","Reco Muon p_{T} Resolution",2000,-10,10);
    muStandAlonePtResolution_hist = new TH1D("muStandAlonePtResolution_hist","SA Muon p_{T} Resolution",2000,-10,10);
    muStandAloneUpdatedAtVtxPtResolution_hist = new TH1D("muStandAloneUpdatedAtVtxPtResolution_hist","SA Muon Updated At Vtx p_{T} Resolution",2000,-10,10);
    muRefittedStandAlonePtResolution_hist = new TH1D("muRefittedStandAlonePtResolution_hist","RSA Muon p_{T} Resolution",2000,-10,10);
    muCosmicPtResolution_hist = new TH1D("muCosmicPtResolution_hist","Cosmic Muon p_{T} Resolution",2000,-10,10);

    muDisplacedStandAloneQoverPtResolution_hist = new TH1D("muDisplacedStandAloneQoverPtResolution_hist","DSA Muon q/p_{T} Resolution",2000,-10,10);
    muQoverPtResolution_hist = new TH1D("muQoverPtResolution_hist","Reco Muon q/p_{T} Resolution",2000,-10,10);
    muStandAloneQoverPtResolution_hist = new TH1D("muStandAloneQoverPtResolution_hist","SA Muon q/p_{T} Resolution",2000,-10,10);
    muStandAloneUpdatedAtVtxQoverPtResolution_hist = new TH1D("muStandAloneUpdatedAtVtxQoverPtResolution_hist","SA Muon Updated At Vtx q/p_{T} Resolution",2000,-10,10);
    muRefittedStandAloneQoverPtResolution_hist = new TH1D("muRefittedStandAloneQoverPtResolution_hist","RSA Muon q/p_{T} Resolution",2000,-10,10);
    muCosmicQoverPtResolution_hist = new TH1D("muCosmicQoverPtResolution_hist","Cosmic Muon q/p_{T} Resolution",2000,-10,10);

    muRefittedStandAlonePtResolution_muCosmicPtResolution_hist = new TH2D("muRefittedStandAlonePtResolution_muCosmicPtResolution_hist","RSA p_{T} Resolution vs Cosmic Muon p_{T} Resolution",110,-10,1,110,-10,1);

    muDisplacedStandAloneNChambersDt_PtResolution_hist = new TH2D("muDisplacedStandAloneNChambersDt_PtResolution_hist","SA Muon # of DT Chambers vs p_{T} Resolution",10,0,10,110,-10,1);
    muRefittedStandAloneNChambersDt_PtResolution_hist = new TH2D("muRefittedStandAloneNChambersDt_PtResolution_hist","Refitted SA Muon # of DT Chambers vs p_{T} Resolution",10,0,10,110,-10,1);
    muCosmicNChambersDt_PtResolution_hist = new TH2D("muCosmicNChambersDt_PtResolution_hist","Cosmic Muon # of DT Chambers vs p_{T} Resolution",10,0,10,110,-10,1);
    muDisplacedStandAloneNChambersRpc_PtResolution_hist = new TH2D("muDisplacedStandAloneNChambersRpc_PtResolution_hist","SA Muon # of RPC Chambers vs p_{T} Resolution",10,0,10,110,-10,1);
    muRefittedStandAloneNChambersRpc_PtResolution_hist = new TH2D("muRefittedStandAloneNChambersRpc_PtResolution_hist","Refitted SA Muon # of RPC Chambers vs p_{T} Resolution",10,0,10,110,-10,1);
    muCosmicNChambersRpc_PtResolution_hist = new TH2D("muCosmicNChambersRpc_PtResolution_hist","Cosmic Muon # of RPC Chambers vs p_{T} Resolution",10,0,10,110,-10,1);

    muDisplacedStandAloneNChambersDt_Pt_hist = new TH2D("muDisplacedStandAloneNChambersDt_Pt_hist","SA Muon # of DT Chambers vs p_{T} ",10,0,10,100,0,1000);
    muRefittedStandAloneNChambersDt_Pt_hist = new TH2D("muRefittedStandAloneNChambersDt_Pt_hist","Refitted SA Muon # of DT Chambers vs p_{T} ",10,0,10,100,0,1000);
    muCosmicNChambersDt_Pt_hist = new TH2D("muCosmicNChambersDt_Pt_hist","Cosmic Muon # of DT Chambers vs p_{T} ",10,0,10,100,0,1000);
    muDisplacedStandAloneNChambersRpc_Pt_hist = new TH2D("muDisplacedStandAloneNChambersRpc_Pt_hist","SA Muon # of RPC Chambers vs p_{T} ",10,0,10,100,0,1000);
    muRefittedStandAloneNChambersRpc_Pt_hist = new TH2D("muRefittedStandAloneNChambersRpc_Pt_hist","Refitted SA Muon # of RPC Chambers vs p_{T} ",10,0,10,100,0,1000);
    muCosmicNChambersRpc_Pt_hist = new TH2D("muCosmicNChambersRpc_Pt_hist","Cosmic Muon # of RPC Chambers vs p_{T} ",10,0,10,100,0,1000);

    muDisplacedStandAlonePt_muCosmicTrackPt_hist = new TH2D("muDisplacedStandAlonePt_muCosmicTrackPt_hist","SA Muon p_{T} vs. Cosmic Track p_{T}",100,0,1000,100,0,1000);
    //mcMuonPt_muDisplacedStandAlonePt_hist = new TH2D("mcMuonPt_muDisplacedStandAlonePt_hist","Gen Muon p_{T} vs. SA Muon p_{T}",100,0,100,100,0,100);
    mcMuonPt_muDisplacedStandAlonePt_hist->SetTitle(";Generator Muon p_{T} [GeV];SA Muon p_{T} [GeV]");
    mcMuonPt_muRefittedStandAlonePt_hist->SetTitle(";Generator Muon p_{T} [GeV];Refitted SA Muon p_{T} [GeV]");
    mcMuonPt_muCosmicPt_hist->SetTitle(";Generator Muon p_{T} [GeV];Cosmic Muon p_{T} [GeV]");
    mcMuonPt_muCosmicTrackPt_hist->SetTitle(";Generator Muon p_{T} [GeV];Cosmic Track p_{T} [GeV]");

    mcMuonN_muDisplacedStandAloneN_hist = new TH2D("mcMuonN_muDisplacedStandAloneN_hist","N Gen Muons vs. N SA Muons",10,0,10,10,0,10);
    mcMuonEta_muDisplacedStandAloneEta_hist = new TH2D("mcMuonEta_muDisplacedStandAloneEta_hist","Gen Muon #eta vs. SA Muon #eta",120,-6,6,120,-6,6);
    mcMuonPhi_muDisplacedStandAlonePhi_hist = new TH2D("mcMuonPhi_muDisplacedStandAlonePhi_hist","Gen Muon #phi vs. SA Muon #phi",64,-3.2,3.2,64,-3.2,3.2);
    mcMuonCharge_muDisplacedStandAloneCharge_hist = new TH2D("mcMuonCharge_muDisplacedStandAloneCharge_hist","Gen Muon Charge vs. SA Muon Charge",3,-1,2,3,-1,2);
    mcMuonLxy_muDisplacedStandAloneLxy_hist = new TH2D("mcMuonLxy_muDisplacedStandAloneLxy_hist","Gen Muon Lxy vs. SA Muon Lxy",100,0,1000,100,0,1000);
    mcMuonDxy_muDisplacedStandAloneDxy_hist = new TH2D("mcMuonDxy_muDisplacedStandAloneDxy_hist","Gen Muon Dxy vs. SA Muon Dxy",2000,-1000,1000,2000,-1000,1000);
    mcMuonInverseBeta_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist = new TH2D("mcMuonInverseBetaa_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist","Gen Muon Inverse Beta vs SA Muon DT Free Inverse Beta",1000,-50,50,1000,-50,50);

    muRefittedStandAloneNHitsDt_Pt_hist = new TH2D("muRefittedStandAloneNHitsDt_Pt_hist","",50,0,50,100,0,1000);
    //muRefittedStandAloneNChambersDt_Pt_hist = new TH2D("muRefittedStandAloneNChambersDt_Pt_hist","",5,0,5,100,0,1000);
    mcStoppedParticleR_muRefittedStandAlonePt_hist = new TH2D("mcStoppedParticleR_muRefittedStandAlonePt_hist","",80,0,800,100,0,1000);
    mcStoppedParticleR_mcMuonPt_hist = new TH2D("mcStoppedParticleR_mcMuonPt_hist","",80,0,800,100,0,1000);
    muDisplacedStandAloneTrackDistanceStations_Pt_hist = new TH2D("muDisplacedStandAloneTrackDistanceStations_Pt_hist","Distance between first and last Stations vs Pt",5,-1,4,100,0,1000);
    muRefittedStandAloneTrackDistanceStations_Pt_hist = new TH2D("muRefittedStandAloneTrackDistanceStations_Pt_hist","Distance between first and last Stations vs Pt",5,-1,4,100,0,1000);

    l1Muon_N_hist = new TH1D("l1Muon_N_hist","Number of L1 Muons",10,0,10);
    l1MuonPt_hist = new TH1D("l1MuonPt_hist","L1 Muon p_{T}",100,0,500);
    l1MuonEta_hist = new TH1D("l1MuonEta_hist","L1 Muon #eta",120,-6,6);
    l1MuonPhi_hist = new TH1D("l1MuonPhi_hist","L1 Muon #phi",64,-3.2,3.2);

    hlt20Cha2Muon_N_hist = new TH1D("hlt20Cha2Muon_N_hist","Number of L2 Muons",10,0,10);
    hlt20Cha2MuonPt_hist = new TH1D("hlt20Cha2MuonPt_hist","L2 Muon p_{T}",100,0,1000);
    hlt20Cha2MuonEta_hist = new TH1D("hlt20Cha2MuonEta_hist","L2 Muon #eta",120,-6,6);
    hlt20Cha2MuonPhi_hist = new TH1D("hlt20Cha2MuonPhi_hist","L2 Muon #phi",64,-3.2,3.2);
    
    mu_N_hist = new TH1D("mu_N_hist","Number of Muons",100,0,100);
    muP_hist = new TH1D("muP_hist","Reco Muon p",1000,0,1000);
    muPt_hist = new TH1D("muPt_hist","Reco Muon p_{T}",1000,0,1000);
    muEta_hist = new TH1D("muEta_hist","Reco Muon #eta",120,-6,6);
    muPhi_hist = new TH1D("muPhi_hist","Reco Muon #phi",64,-3.2,3.2);
    muType_hist = new TH1D("muType_hist","Reco Muon Type",4000,0,4000);
    muIso_hist = new TH1D("muIso_hist","Reco Muon Isolation",1000,0,1000);
    muEta_muPhi_hist = new TH2D("muEta_muPhi_hist","Reco Muon #eta vs #phi",120,-6,6,64,-3.2,3.2);
    
    diMu_N_hist = new TH1D("diMu_N_hist","Number of DiMuons",100,0,100);
    diMuMass_hist = new TH1D("diMuMass_hist","Reco Muon Invaraint Mass",1000,0,1000);
    
    muCosmic_N_hist = new TH1D("muCosmic_N_hist","Number of Cosmic Muons",100,0,100);
    muCosmicP_hist = new TH1D("muCosmicP_hist","Cosmic Muon p",1000,0,1000);
    muCosmicPt_hist = new TH1D("muCosmicPt_hist","Cosmic Muon p_{T}",1000,0,1000);
    muCosmicEta_hist = new TH1D("muCosmicEta_hist","Cosmic Muon #eta",120,-6,6);
    muCosmicPhi_hist = new TH1D("muCosmicPhi_hist","Cosmic Muon #phi",64,-3.2,3.2);
    muCosmicType_hist = new TH1D("muCosmicType_hist","Cosmic Muon Type",4000,0,4000);
    muCosmicEta_muCosmicPhi_hist = new TH2D("muCosmicEta_muCosmicPhi_hist","Cosmic Muon #eta vs #phi",120,-6,6,64,-3.2,3.2);
    
    muCosmicTrackNChambersDt_hist = new TH1D("muCosmicTrackNChambersDt_hist","DT Chambers in Cosmic Muon Track",10,0,10);

    muCosmicTrackInnerPt_hist = new TH1D("muCosmicTrackInnerPt_hist","Cosmic Track Muon Inner p_{T}",100,0,1000);

    muDisplacedStandAlone_N_other_cut_hist = new TH1D("muDisplacedStandAlone_N_other_cut_hist","Number of StandAlone Muons with #phi>0 and >1 stations",100,0,100);
    
    muDisplacedStandAlone_N_hist = new TH1D("muDisplacedStandAlone_N_hist","Number of StandAlone Muons",100,0,100);
    muDisplacedStandAloneP_hist = new TH1D("muDisplacedStandAloneP_hist","StandAlone Muon p",1000,0,1000);
    muDisplacedStandAlonePt_hist = new TH1D("muDisplacedStandAlonePt_hist","StandAlone Muon p_{T}",1000,0,1000);
    muDisplacedStandAlonePt0_hist = new TH1D("muDisplacedStandAlonePt0_hist","1st StandAlone Muon p_{T}",1000,0,1000);
    muDisplacedStandAlonePt1_hist = new TH1D("muDisplacedStandAlonePt1_hist","2nd StandAlone Muon p_{T}",1000,0,1000);
    muDisplacedStandAlonePt2_hist = new TH1D("muDisplacedStandAlonePt2_hist","3rd StandAlone Muon p_{T}",1000,0,1000);
    muDisplacedStandAloneEta_hist = new TH1D("muDisplacedStandAloneEta_hist","StandAlone Muon #eta",120,-6,6);
    muDisplacedStandAlonePhi_hist = new TH1D("muDisplacedStandAlonePhi_hist","StandAlone Muon #phi",64,-3.2,3.2);
    muDisplacedStandAloneCharge_hist = new TH1D("muDisplacedStandAloneCharge_hist","StandAlone Muon Track Charge",10,-5,5);
    muDisplacedStandAloneTrackNormalizedChi2_hist = new TH1D("muDisplacedStandAloneTrackNormalizedChi2_hist","StandAlone Muon Track #chi^{2}/dof",1000,0,100);
    muDisplacedStandAloneTrackDxy_hist = new TH1D("muDisplacedStandAloneTrackDxy_hist","StandAlone Muon Dxy",2000,-1000,1000);
    muDisplacedStandAloneTrackDz_hist = new TH1D("muDisplacedStandAloneTrackDz_hist","StandAlone Muon Dz",2000,-1000,1000);
    muDisplacedStandAloneTrackNHitsMuon_hist = new TH1D("muDisplacedStandAloneTrackNHitsMuon_hist","Hits in StandAlone Muon Track",100,0,100);
    muDisplacedStandAloneTrackNHitsCsc_hist = new TH1D("muDisplacedStandAloneTrackNHitsCsc_hist","CSC Hits in StandAlone Muon Track",100,0,100);
    muDisplacedStandAloneTrackNHitsDt_hist = new TH1D("muDisplacedStandAloneTrackNHitsDt_hist","DT Hits in StandAlone Muon Track",100,0,100);
    muDisplacedStandAloneTrackNHitsRpc_hist = new TH1D("muDisplacedStandAloneTrackNHitsRpc_hist","RPC Hits in StandAlone Muon Track",10,0,10);
    muDisplacedStandAloneTrackNRpcDof_hist = new TH1D("muDisplacedStandAloneTrackNRpcDof_hist","RPC BX Measurements in StandAlone Muon Track",10,0,10);
    muDisplacedStandAloneTrackNStations_hist = new TH1D("muDisplacedStandAloneTrackNStations_hist","Muon Stations in StandAlone Muon Track",10,0,10);
    muDisplacedStandAloneTrackNChambersCsc_hist = new TH1D("muDisplacedStandAloneTrackNChambersCsc_hist","CSC Chambers in StandAlone Muon Track",10,0,10);
    muDisplacedStandAloneTrackNChambersDt_hist = new TH1D("muDisplacedStandAloneTrackNChambersDt_hist","DT Chambers in StandAlone Muon Track",10,0,10);
    muDisplacedStandAloneTrackNChambersRpc_hist = new TH1D("muDisplacedStandAloneTrackNChambersRpc_hist","RPC Chambers in StandAlone Muon Track",10,0,10);
    muDisplacedStandAloneTrackDistanceStations_hist = new TH1D("muDisplacedStandAloneTrackDistanceStations_hist","Distance between first and last Stations in StandAlone Muon Track",5,-1,4);
    muDisplacedStandAloneTrackInnerPt_hist = new TH1D("muDisplacedStandAloneTrackInnerPt_hist","StandAlone Track Muon Inner p_{T}",100,0,1000);
    muDisplacedStandAloneTrackDtTofNDof_hist = new TH1D("muDisplacedStandAloneTrackDtTofNDof_hist","StandAlone Muons TOF Number of Degrees of Freedom",40,0,40);
    muDisplacedStandAloneBxPattern_hist = new TH1D("muDisplacedStandAloneBxPattern_hist","StandAlone Muon RPC BX Pattern",9,0,9);
    muDisplacedStandAloneNHitsRpcBxPattern0_hist = new TH1D("muDisplacedStandAloneNHitsRpcBxPattern0_hist","Number of RPC Hits for BXs==0",10,0,10);
    muDisplacedStandAloneBxAverage_hist = new TH1D("muDisplacedStandAloneBxAverage_hist","RPC BX Average",100,-5,5);

    muDisplacedStandAloneOppositeSegDR_hist = new TH1D("muDisplacedStandAloneOppositeSegDR_hist","dR to opp side seg",500,0,5);
    muDisplacedStandAloneOppositeSegDEta_hist = new TH1D("muDisplacedStandAloneOppositeSegDEta_hist","dEta to opp side seg",100,-2,2);
    muDisplacedStandAloneOppositeSegDPhi_hist = new TH1D("muDisplacedStandAloneOppositeSegDPhi_hist","dPhi to opp side seg",100,-5,5);

    muDisplacedStandAlonePt_denominator_hist = new TH1D("muDisplacedStandAlonePt_denominator_hist","StandAlone Muon p_{T}",1000,0,1000);
    muDisplacedStandAlonePt_L1numerator_hist = new TH1D("muDisplacedStandAlonePt_L1numerator_hist","StandAlone Muon p_{T}",1000,0,1000);
    muDisplacedStandAlonePt_HLTnumerator_hist = new TH1D("muDisplacedStandAlonePt_HLTnumerator_hist","StandAlone Muon p_{T}",1000,0,1000);

    muRefittedStandAlonePt_denominator_hist = new TH1D("muRefittedStandAlonePt_denominator_hist","StandAlone Muon p_{T}",1000,0,1000);
    muRefittedStandAlonePt_L1numerator_hist = new TH1D("muRefittedStandAlonePt_L1numerator_hist","StandAlone Muon p_{T}",1000,0,1000);
    muRefittedStandAlonePt_HLTnumerator_hist = new TH1D("muRefittedStandAlonePt_HLTnumerator_hist","StandAlone Muon p_{T}",1000,0,1000);

    muDisplacedStandAlonePt_GlSAdenominator_hist = new TH1D("muDisplacedStandAlonePt_GlSAdenominator_hist","StandAlone Muon p_{T}",1000,0,1000);
    muDisplacedStandAlonePt_GlSAnumerator_hist = new TH1D("muDisplacedStandAlonePt_GlSAnumerator_hist","StandAlone Muon p_{T}",1000,0,1000);

    muDisplacedStandAloneTrackShowerSize_station0_hist = new TH1D("muDisplacedStandAloneTrackShowerSize_station0_hist","Shower Size",100,0,50);
    muDisplacedStandAloneTrackShowerSize_station1_hist = new TH1D("muDisplacedStandAloneTrackShowerSize_station1_hist","Shower Size",100,0,50);
    muDisplacedStandAloneTrackShowerSize_station2_hist = new TH1D("muDisplacedStandAloneTrackShowerSize_station2_hist","Shower Size",100,0,50);
    muDisplacedStandAloneTrackShowerSize_station3_hist = new TH1D("muDisplacedStandAloneTrackShowerSize_station3_hist","Shower Size",100,0,50);
    muDisplacedStandAloneTrackShowerDeltaR_station0_hist = new TH1D("muDisplacedStandAloneTrackShowerDeltaR_station0_hist","Shower DeltaR",100,0,0.5);
    muDisplacedStandAloneTrackShowerDeltaR_station1_hist = new TH1D("muDisplacedStandAloneTrackShowerDeltaR_station1_hist","Shower DeltaR",100,0,0.5);
    muDisplacedStandAloneTrackShowerDeltaR_station2_hist = new TH1D("muDisplacedStandAloneTrackShowerDeltaR_station2_hist","Shower DeltaR",100,0,0.5);
    muDisplacedStandAloneTrackShowerDeltaR_station3_hist = new TH1D("muDisplacedStandAloneTrackShowerDeltaR_station3_hist","Shower DeltaR",100,0,0.5);
    muDisplacedStandAloneTrackShowerNHits_station0_hist = new TH1D("muDisplacedStandAloneTrackShowerNHits_station0_hist","N Hits",200,0,200);
    muDisplacedStandAloneTrackShowerNHits_station1_hist = new TH1D("muDisplacedStandAloneTrackShowerNHits_station1_hist","N Hits",200,0,200);
    muDisplacedStandAloneTrackShowerNHits_station2_hist = new TH1D("muDisplacedStandAloneTrackShowerNHits_station2_hist","N Hits",200,0,200);
    muDisplacedStandAloneTrackShowerNHits_station3_hist = new TH1D("muDisplacedStandAloneTrackShowerNHits_station3_hist","N Hits",200,0,200);
    muDisplacedStandAloneTrackShowerNCorrelatedHits_station0_hist = new TH1D("muDisplacedStandAloneTrackShowerNCorrelatedHits_station0_hist","N Correlated Hits",50,0,50);
    muDisplacedStandAloneTrackShowerNCorrelatedHits_station1_hist = new TH1D("muDisplacedStandAloneTrackShowerNCorrelatedHits_station1_hist","N Correlated Hits",50,0,50);
    muDisplacedStandAloneTrackShowerNCorrelatedHits_station2_hist = new TH1D("muDisplacedStandAloneTrackShowerNCorrelatedHits_station2_hist","N Correlated Hits",50,0,50);
    muDisplacedStandAloneTrackShowerNCorrelatedHits_station3_hist = new TH1D("muDisplacedStandAloneTrackShowerNCorrelatedHits_station3_hist","N Correlated Hits",50,0,50);
    muDisplacedStandAloneTrackShowerNUncorrelatedHits_station0_hist = new TH1D("muDisplacedStandAloneTrackShowerNUncorrelatedHits_station0_hist","N Uncorrelated Hits",200,0,200);
    muDisplacedStandAloneTrackShowerNUncorrelatedHits_station1_hist = new TH1D("muDisplacedStandAloneTrackShowerNUncorrelatedHits_station1_hist","N Uncorrelated Hits",200,0,200);
    muDisplacedStandAloneTrackShowerNUncorrelatedHits_station2_hist = new TH1D("muDisplacedStandAloneTrackShowerNUncorrelatedHits_station2_hist","N Uncorrelated Hits",200,0,200);
    muDisplacedStandAloneTrackShowerNUncorrelatedHits_station3_hist = new TH1D("muDisplacedStandAloneTrackShowerNUncorrelatedHits_station3_hist","N Uncorrelated Hits",200,0,200);

    muDisplacedStandAloneUpperOnlyDEta_hist = new TH1D("muDisplacedStandAloneUpperOnlyDEta_hist","dEta between Upper SAs",100,0,10);
    muDisplacedStandAloneUpperOnlyDPhi_hist = new TH1D("muDisplacedStandAloneUpperOnlyDPhi_hist","dPhi between Upper SAs",100,0,5);
    muDisplacedStandAloneLowerOnlyDEta_hist = new TH1D("muDisplacedStandAloneLowerOnlyDEta_hist","dEta between Lower SAs",100,0,10);
    muDisplacedStandAloneLowerOnlyDPhi_hist = new TH1D("muDisplacedStandAloneLowerOnlyDPhi_hist","dPhi between Lower SAs",100,0,5);
    
    muDisplacedStandAloneNCscSegments_hist = new TH1D("muDisplacedStandAloneNCscSegments_hist","",10,0,10);

    muDisplacedStandAlonePhi_muDisplacedStandAloneDTTofFreeInverseBeta_hist = new TH2D("muDisplacedStandAlonePhi_muDisplacedStandAloneDTTofFreeInverseBeta_hist","StandAlone Muon #phi vs Free #beta^{-1}",64,-3.2,3.2,1000,-50,50);
    muDisplacedStandAloneEta_muDisplacedStandAlonePhi_hist = new TH2D("muDisplacedStandAloneEta_muDisplacedStandAlonePhi_hist","StandAlone Muon #eta vs #phi",120,-6,6,64,-3.2,3.2);
    muDisplacedStandAloneTrackNHitsRpc_muDisplacedStandAloneTrackNormalizedChi2_hist = new TH2D("muDisplacedStandAloneTrackNHitsRpc_muDisplacedStandAloneTrackNormalizedChi2_hist","RPC Hits vs Track #chi^{2}/dof",10,0,10,100,0,100);
    muDisplacedStandAloneTrackNHitsRpc_muDisplacedStandAloneTrackNHitsDt_hist = new TH2D("muDisplacedStandAloneTrackNHitsRpc_muDisplacedStandAloneTrackNHitsDt_hist","RPC Hits vs DT Hits",10,0,10,100,0,100);
    muDisplacedStandAlonePt_muDisplacedStandAloneTrackNChambersDt_hist = new TH2D("muDisplacedStandAlonePt_muDisplacedStandAloneTrackNChambersDt_hist","",1000,0,1000,5,0,5);
    muDisplacedStandAlonePt_DtTofFreeInverseBeta_hist = new TH2D("muDisplacedStandAlonePt_DtTofFreeInverseBeta_hist","",1000,0,1000,1000,-50,50);
    muDisplacedStandAloneP_DtTofFreeInverseBeta_hist = new TH2D("muDisplacedStandAloneP_DtTofFreeInverseBeta_hist","",1000,0,1000,1000,-50,50);
    muDisplacedStandAloneP_BxPattern_hist = new TH2D("muDisplacedStandAloneP_BxPattern_hist","",1000,0,1000,9,0,9);
    muDisplacedStandAlonePt_BxPattern_hist = new TH2D("muDisplacedStandAlonePt_BxPattern_hist","",1000,0,1000,9,0,9);
    muDisplacedStandAloneDtTofFreeInverseBeta_DtTofDirection_hist = new TH2D("muDisplacedStandAloneDtTofFreeInverseBeta_DtTofDirection_hist","",1000,-50,50,3,-1,2);
    muDisplacedStandAloneDtTofFreeInverseBetaErr_DtTofNDof_hist = new TH2D("muDisplacedStandAloneDtTofFreeInverseBetaErr_DtTofNDof_hist","Error of Free #beta^{-1} vs TOF nDOF of StandAlone Muons",10000,0,1000,200,0,200);

    runNumber_muDisplacedStandAloneDtTofFreeInverseBeta_hist = new TH2D("runNumber_muDisplacedStandAloneDtTofFreeInverseBeta_hist","",10000,190000,210000,1000,-50,50);
    runNumber_muDisplacedStandAloneDtTofInverseBeta_hist = new TH2D("runNumber_muDisplacedStandAloneDtTofInverseBeta_hist","",10000,190000,210000,1000,-50,50);
    runNumber_muDisplacedStandAlonePt_hist = new TH2D("runNumber_muDisplacedStandAlonePt_hist","",10000,190000,210000,1000,0,1000);
    runNumber_muDisplacedStandAlonePhi_hist = new TH2D("runNumber_muDisplacedStandAlonePhi_hist","",10000,190000,210000,64,-3.2,3.2);
    runNumber_muDisplacedStandAloneN_hist = new TH2D("runNumber_muDisplacedStandAloneN_hist","",10000,190000,210000,10,0,10);
    muDisplacedStandAloneEta_Phi_hist = new TH2D("muDisplacedStandAloneEta_Phi_hist","",120,-6,6,64,-3.2,3.2);

    Upper_muDisplacedStandAlonePt_hist = new TH1D("Upper_muDisplacedStandAlonePt_hist","StandAlone Muon p_{T}",1000,0,1000);
    Upper_muDisplacedStandAloneEta_hist = new TH1D("Upper_muDisplacedStandAloneEta_hist","StandAlone Muon #eta",120,-6,6);
    Upper_muDisplacedStandAlonePhi_hist = new TH1D("Upper_muDisplacedStandAlonePhi_hist","StandAlone Muon #phi",64,-3.2,3.2);
    Upper_muDisplacedStandAloneTrackCharge_hist = new TH1D("Upper_muDisplacedStandAloneTrackCharge_hist","StandAlone Muon Track Charge",10,-5,5);
    Upper_muDisplacedStandAloneTrackNormalizedChi2_hist = new TH1D("Upper_muDisplacedStandAloneTrackNormalizedChi2_hist","StandAlone Muon Track #chi^{2}/dof",1000,0,100);
    Upper_muDisplacedStandAloneTrackDxy_hist = new TH1D("Upper_muDisplacedStandAloneTrackDxy_hist","StandAlone Muon Dxy",2000,-1000,1000);
    Upper_muDisplacedStandAloneTrackDz_hist = new TH1D("Upper_muDisplacedStandAloneTrackDz_hist","StandAlone Muon Dz",2000,-1000,1000);
    Upper_muDisplacedStandAloneTrackNHitsMuon_hist = new TH1D("Upper_muDisplacedStandAloneTrackNHitsMuon_hist","Hits in StandAlone Muon Track",100,0,100);
    Upper_muDisplacedStandAloneTrackNHitsCsc_hist = new TH1D("Upper_muDisplacedStandAloneTrackNHitsCsc_hist","CSC Hits in StandAlone Muon Track",100,0,100);
    Upper_muDisplacedStandAloneTrackNHitsDt_hist = new TH1D("Upper_muDisplacedStandAloneTrackNHitsDt_hist","DT Hits in StandAlone Muon Track",100,0,100);
    Upper_muDisplacedStandAloneTrackNHitsRpc_hist = new TH1D("Upper_muDisplacedStandAloneTrackNHitsRpc_hist","RPC Hits in StandAlone Muon Track",10,0,10);
    Upper_muDisplacedStandAloneTrackNRpcDof_hist = new TH1D("Upper_muDisplacedStandAloneTrackNRpcDof_hist","RPC BX Measurements in StandAlone Muon Track",10,0,10);
    Upper_muDisplacedStandAloneTrackNStations_hist = new TH1D("Upper_muDisplacedStandAloneTrackNStations_hist","Muon Stations in StandAlone Muon Track",10,0,10);
    Upper_muDisplacedStandAloneTrackNChambersCsc_hist = new TH1D("Upper_muDisplacedStandAloneTrackNChambersCsc_hist","CSC Chambers in StandAlone Muon Track",10,0,10);
    Upper_muDisplacedStandAloneTrackNChambersDt_hist = new TH1D("Upper_muDisplacedStandAloneTrackNChambersDt_hist","DT Chambers in StandAlone Muon Track",10,0,10);
    Upper_muDisplacedStandAloneTrackNChambersRpc_hist = new TH1D("Upper_muDisplacedStandAloneTrackNChambersRpc_hist","RPC Chambers in StandAlone Muon Track",10,0,10);
    Upper_muDisplacedStandAloneTrackDtTofNDof_hist = new TH1D("Upper_muDisplacedStandAloneTrackDtTofNDof_hist","StandAlone Muons TOF Number of Degrees of Freedom",40,0,40);
    Upper_muDisplacedStandAloneTrackDtTofInverseBeta_hist = new TH1D("Upper_muDisplacedStandAloneTrackDtTofInverseBeta_hist","#beta^{-1} of StandAlone Muons",1000,-5,5);
    Upper_muDisplacedStandAloneTrackDtTofInverseBetaErr_hist = new TH1D("Upper_muDisplacedStandAloneTrackDtTofInverseBetaErr_hist","Error of #beta^{-1} of StandAlone Muons",10000,0,1000);
    Upper_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist = new TH1D("Upper_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist","Free #beta^{-1} of StandAlone Muons",1000,-50,50);
    Upper_muDisplacedStandAloneTrackDtTofFreeInverseBetaErr_hist = new TH1D("Upper_muDisplacedStandAloneTrackDtTofFreeInverseBetaErr_hist","Error of Free #beta^{-1} of StandAlone Muons",10000,0,1000);
    Upper_muDisplacedStandAloneTrackDtTofTimeAtIpInOut_hist = new TH1D("Upper_muDisplacedStandAloneTrackDtTofTimeAtIpInOut_hist","Time at IP InOut of StandAlone Muons",400,-100,100);
    Upper_muDisplacedStandAloneTrackDtTofTimeAtIpOutIn_hist = new TH1D("Upper_muDisplacedStandAloneTrackDtTofTimeAtIpOutIn_hist","Time at IP OutIn of StandAlone Muons",400,-50,150);
    Upper_muDisplacedStandAloneTrackDtTofTimeAtIpInOutErr_hist = new TH1D("Upper_muDisplacedStandAloneTrackDtTofTimeAtIpInOutErr_hist","Error of Time at IP InOut of StandAlone Muons",1000,-50,50);
    Upper_muDisplacedStandAloneTrackDtTofTimeAtIpOutInErr_hist = new TH1D("Upper_muDisplacedStandAloneTrackDtTofTimeAtIpOutInErr_hist","Error of Time at IP OutIn of StandAlone Muons",1000,-50,50);
    Upper_muDisplacedStandAloneTrackDtTofDirection_hist = new TH1D("Upper_muDisplacedStandAloneTrackDtTofDirection_hist","Direction of StandAlone Muons",3,-1,2);
    Upper_muDisplacedStandAloneTrackDtTofErrDiff_hist = new TH1D("Upper_muDisplacedStandAloneTrackDtTofErrDiff_hist","TimeInOut Error - TimeOutInError",400,-100,100);
    Upper_muDisplacedStandAloneBxPattern_hist = new TH1D("Upper_muDisplacedStandAloneBxPattern_hist","Upper StandAlone Muon RPC BX Pattern",9,0,9);
    Upper_muDisplacedStandAloneBxAverage_hist = new TH1D("Upper_muDisplacedStandAloneBxAverage_hist","Upper StandAlone Muon RPC BX Average",200,-10,10);

    Upper_muDisplacedStandAloneTrackNHitsRpc_Upper_muDisplacedStandAloneTrackNormalizedChi2_hist = new TH2D("Upper_muDisplacedStandAloneTrackNHitsRpc_Upper_muDisplacedStandAloneTrackNormalizedChi2_hist","RPC Hits vs Track #chi^{2}/dof",10,0,10,100,0,100);
    Upper_muDisplacedStandAloneTrackNHitsRpc_Upper_muDisplacedStandAloneTrackNHitsDt_hist = new TH2D("Upper_muDisplacedStandAloneTrackNHitsRpc_Upper_muDisplacedStandAloneTrackNHitsDt_hist","RPC Hits vs DT Hits",10,0,10,100,0,100);
    Upper_muDisplacedStandAloneBxPattern_Upper_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist = new TH2D("Upper_muDisplacedStandAloneBxPattern_Upper_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist","Rpc BX Pattern vs DT Free Inverse Beta",9,0,9,1000,-50,50);
    Upper_muDisplacedStandAloneBxPattern_Upper_muDisplacedStandAloneTrackDtTofNDof_hist = new TH2D("Upper_muDisplacedStandAloneBxPattern_Upper_muDisplacedStandAloneTrackDtTofNDof_hist","Rpc BX Pattern vs DT Free Inverse Beta",9,0,9,40,0,40);
    Upper_muDisplacedStandAloneBxPattern_mudiff_muDisplacedStandAloneTofTimeAtIpInOut_hist = new TH2D("Upper_muDisplacedStandAloneBxPattern_mudiff_muDisplacedStandAloneTofTimeAtIpInOut_hist","Rpc BX Pattern vs delta timeInOut",9,0,9,400,-100,100);
    Upper_muDisplacedStandAlonePt_Upper_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist = new TH2D("Upper_muDisplacedStandAlonePt_Upper_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist","Pt vs DT Free Inverse Beta",1000,0,1000,1000,-50,50);
    Upper_muDisplacedStandAloneP_Upper_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist = new TH2D("Upper_muDisplacedStandAloneP_Upper_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist","P vs DT Free Inverse Beta",1000,0,1000,1000,-50,50);
    Upper_muDisplacedStandAlonePt_Upper_muDisplacedStandAloneBxPattern_hist = new TH2D("Upper_muDisplacedStandAlonePt_Upper_muDisplacedStandAloneBxPattern_hist","Pt vs RPC BX Pattern",100,0,1000,9,0,9);
    Upper_muDisplacedStandAloneP_Upper_muDisplacedStandAloneBxPattern_hist = new TH2D("Upper_muDisplacedStandAloneP_Upper_muDisplacedStandAloneBxPattern_hist","P vs RPC BX Pattern",100,0,1000,9,0,9);
    Upper_muDisplacedStandAloneTimeAtIpInOut_Upper_muDisplacedStandAloneFreeInverseBeta_hist = new TH2D("Upper_muDisplacedStandAloneTimeAtIpInOut_Upper_muDisplacedStandAloneFreeInverseBeta_hist","DT Time InOut vs Free Inverse Beta",400,-100,100,1000,-50,50);
    Upper_muDisplacedStandAloneTimeAtIpInOut_Upper_muDisplacedStandAloneDirection_hist = new TH2D("Upper_muDisplacedStandAloneTimeAtIpInOut_Upper_muDisplacedStandAloneDirection_hist","DT Time InOut vs Direction",400,-100,100,3,-1,2);
    Upper_muDisplacedStandAloneFreeInverseBeta_Upper_muDisplacedStandAloneFreeInverseBetaErr_hist = new TH2D("Upper_muDisplacedStandAloneFreeInverseBeta_Upper_muDisplacedStandAloneFreeInverseBetaErr_hist","DT Free Inverse Beta vs Free Inverse Beta Error",1000,-50,50,10000,0,1000);

    Highest_muDisplacedStandAloneP_Upper_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist = new TH2D("Highest_muDisplacedStandAloneP_Upper_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist","Highest P vs DT Free Inverse Beta",100,0,1000,100,-50,50);

    Upper_runNumber_muDisplacedStandAloneDtTofFreeInverseBeta_hist = new TH2D("Upper_runNumber_muDisplacedStandAloneDtTofFreeInverseBeta_hist","run number vs free #beta^{-1} of StandAlone Muons",10000,190000,210000,1000,-50,50);
    Upper_runNumber_muDisplacedStandAloneDtTofInverseBeta_hist = new TH2D("Upper_runNumber_muDisplacedStandAloneDtTofInverseBeta_hist","run number vs #beta^{-1} of StandAlone Muons",10000,190000,210000,1000,-5,5);
    Upper_runNumber_muDisplacedStandAlonePt_hist = new TH2D("Upper_runNumber_muDisplacedStandAlonePt_hist","run number vs p_T of StandAlone Muons",10000,190000,210000,1000,0,1000);
    Upper_runNumber_muDisplacedStandAlonePhi_hist = new TH2D("Upper_runNumber_muDisplacedStandAlonePhi_hist","",10000,190000,210000,64,-3.2,3.2);
    Upper_runNumber_muDisplacedStandAloneN_hist = new TH2D("Upper_runNumber_muDisplacedStandAloneN_hist","",10000,190000,210000,10,0,10);
    Upper_muDisplacedStandAloneEta_Phi_hist = new TH2D("Upper_muDisplacedStandAloneEta_Phi_hist","",120,-6,6,64,-3.2,3.2);

    Lower_muDisplacedStandAlonePt_hist = new TH1D("Lower_muDisplacedStandAlonePt_hist","StandAlone Muon p_{T}",1000,0,1000);
    Lower_muDisplacedStandAloneEta_hist = new TH1D("Lower_muDisplacedStandAloneEta_hist","StandAlone Muon #eta",120,-6,6);
    Lower_muDisplacedStandAlonePhi_hist = new TH1D("Lower_muDisplacedStandAlonePhi_hist","StandAlone Muon #phi",64,-3.2,3.2);
    Lower_muDisplacedStandAloneTrackCharge_hist = new TH1D("Lower_muDisplacedStandAloneTrackCharge_hist","StandAlone Muon Track Charge",10,-5,5);
    Lower_muDisplacedStandAloneTrackNormalizedChi2_hist = new TH1D("Lower_muDisplacedStandAloneTrackNormalizedChi2_hist","StandAlone Muon Track #chi^{2}/dof",1000,0,100);
    Lower_muDisplacedStandAloneTrackDxy_hist = new TH1D("Lower_muDisplacedStandAloneTrackDxy_hist","StandAlone Muon Dxy",2000,-1000,1000);
    Lower_muDisplacedStandAloneTrackDz_hist = new TH1D("Lower_muDisplacedStandAloneTrackDz_hist","StandAlone Muon Dz",2000,-1000,1000);
    Lower_muDisplacedStandAloneTrackNHitsMuon_hist = new TH1D("Lower_muDisplacedStandAloneTrackNHitsMuon_hist","Hits in StandAlone Muon Track",100,0,100);
    Lower_muDisplacedStandAloneTrackNHitsCsc_hist = new TH1D("Lower_muDisplacedStandAloneTrackNHitsCsc_hist","CSC Hits in StandAlone Muon Track",100,0,100);
    Lower_muDisplacedStandAloneTrackNHitsDt_hist = new TH1D("Lower_muDisplacedStandAloneTrackNHitsDt_hist","DT Hits in StandAlone Muon Track",100,0,100);
    Lower_muDisplacedStandAloneTrackNHitsRpc_hist = new TH1D("Lower_muDisplacedStandAloneTrackNHitsRpc_hist","RPC Hits in StandAlone Muon Track",10,0,10);
    Lower_muDisplacedStandAloneTrackNRpcDof_hist = new TH1D("Lower_muDisplacedStandAloneTrackNRpcDof_hist","RPC BX Measurements in StandAlone Muon Track",10,0,10);
    Lower_muDisplacedStandAloneTrackNStations_hist = new TH1D("Lower_muDisplacedStandAloneTrackNStations_hist","Muon Stations in StandAlone Muon Track",10,0,10);
    Lower_muDisplacedStandAloneTrackNChambersCsc_hist = new TH1D("Lower_muDisplacedStandAloneTrackNChambersCsc_hist","CSC Chambers in StandAlone Muon Track",10,0,10);
    Lower_muDisplacedStandAloneTrackNChambersDt_hist = new TH1D("Lower_muDisplacedStandAloneTrackNChambersDt_hist","DT Chambers in StandAlone Muon Track",10,0,10);
    Lower_muDisplacedStandAloneTrackNChambersRpc_hist = new TH1D("Lower_muDisplacedStandAloneTrackNChambersRpc_hist","RPC Chambers in StandAlone Muon Track",10,0,10);
    Lower_muDisplacedStandAloneTrackDtTofNDof_hist = new TH1D("Lower_muDisplacedStandAloneTrackDtTofNDof_hist","StandAlone Muons TOF Number of Degrees of Freedom",40,0,40);
    Lower_muDisplacedStandAloneTrackDtTofInverseBeta_hist = new TH1D("Lower_muDisplacedStandAloneTrackDtTofInverseBeta_hist","#beta^{-1} of StandAlone Muons",1000,-5,5);
    Lower_muDisplacedStandAloneTrackDtTofInverseBetaErr_hist = new TH1D("Lower_muDisplacedStandAloneTrackDtTofInverseBetaErr_hist","Error of #beta^{-1} of StandAlone Muons",10000,0,1000);
    Lower_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist = new TH1D("Lower_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist","Free #beta^{-1} of StandAlone Muons",1000,-50,50);
    Lower_muDisplacedStandAloneTrackDtTofFreeInverseBetaErr_hist = new TH1D("Lower_muDisplacedStandAloneTrackDtTofFreeInverseBetaErr_hist","Error of Free #beta^{-1} of StandAlone Muons",10000,0,1000);
    Lower_muDisplacedStandAloneTrackDtTofTimeAtIpInOut_hist = new TH1D("Lower_muDisplacedStandAloneTrackDtTofTimeAtIpInOut_hist","Time at IP InOut of StandAlone Muons",400,-100,100);
    Lower_muDisplacedStandAloneTrackDtTofTimeAtIpOutIn_hist = new TH1D("Lower_muDisplacedStandAloneTrackDtTofTimeAtIpOutIn_hist","Time at IP OutIn of StandAlone Muons",400,-50,150);
    Lower_muDisplacedStandAloneTrackDtTofTimeAtIpInOutErr_hist = new TH1D("Lower_muDisplacedStandAloneTrackDtTofTimeAtIpInOutErr_hist","Error of Time at IP InOut of StandAlone Muons",1000,-50,50);
    Lower_muDisplacedStandAloneTrackDtTofTimeAtIpOutInErr_hist = new TH1D("Lower_muDisplacedStandAloneTrackDtTofTimeAtIpOutInErr_hist","Error of Time at IP OutIn of StandAlone Muons",1000,-50,50);
    Lower_muDisplacedStandAloneTrackDtTofDirection_hist = new TH1D("Lower_muDisplacedStandAloneTrackDtTofDirection_hist","Direction of StandAlone Muons",3,-1,2);
    Lower_muDisplacedStandAloneTrackDtTofErrDiff_hist = new TH1D("Lower_muDisplacedStandAloneTrackDtTofErrDiff_hist","TimeInOut Error - TimeOutInError",400,-100,100);
    Lower_muDisplacedStandAloneBxPattern_hist = new TH1D("Lower_muDisplacedStandAloneBxPattern_hist","Lower StandAlone Muon RPC BX Pattern",9,0,9);
    Lower_muDisplacedStandAloneBxAverage_hist = new TH1D("Lower_muDisplacedStandAloneBxAverage_hist","Lower StandAlone Muon RPC BX Average",200,-10,10);

    Lower_muDisplacedStandAloneTrackNHitsRpc_Lower_muDisplacedStandAloneTrackNormalizedChi2_hist = new TH2D("Lower_muDisplacedStandAloneTrackNHitsRpc_Lower_muDisplacedStandAloneTrackNormalizedChi2_hist","RPC Hits vs Track #chi^{2}/dof",10,0,10,100,0,100);
    Lower_muDisplacedStandAloneTrackNHitsRpc_Lower_muDisplacedStandAloneTrackNHitsDt_hist = new TH2D("Lower_muDisplacedStandAloneTrackNHitsRpc_Lower_muDisplacedStandAloneTrackNHitsDt_hist","RPC Hits vs DT Hits",10,0,10,100,0,100);
    Lower_muDisplacedStandAloneBxPattern_Lower_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist = new TH2D("Lower_muDisplacedStandAloneBxPattern_Lower_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist","Rpc BX Pattern vs DT Free Inverse Beta",9,0,9,1000,-50,50);
    Lower_muDisplacedStandAlonePt_Lower_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist = new TH2D("Lower_muDisplacedStandAlonePt_Lower_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist","Pt vs DT Free Inverse Beta",1000,0,1000,1000,-50,50);
    Lower_muDisplacedStandAlonePt_Lower_muDisplacedStandAloneBxPattern_hist = new TH2D("Lower_muDisplacedStandAlonePt_Lower_muDisplacedStandAloneBxPattern_hist","Pt vs RPC BX Pattern",100,0,1000,9,0,9);
    Lower_muDisplacedStandAloneP_Lower_muDisplacedStandAloneBxPattern_hist = new TH2D("Lower_muDisplacedStandAloneP_Lower_muDisplacedStandAloneBxPattern_hist","P vs RPC BX Pattern",100,0,1000,9,0,9);
    Lower_muDisplacedStandAloneTimeAtIpInOut_Lower_muDisplacedStandAloneFreeInverseBeta_hist = new TH2D("Lower_muDisplacedStandAloneTimeAtIpInOut_Lower_muDisplacedStandAloneFreeInverseBeta_hist","DT Time InOut vs Free Inverse Beta",400,-100,100,1000,-50,50);
    Lower_muDisplacedStandAloneTimeAtIpInOut_Lower_muDisplacedStandAloneDirection_hist = new TH2D("Lower_muDisplacedStandAloneTimeAtIpInOut_Lower_muDisplacedStandAloneDirection_hist","DT Time InOut vs Direction",400,-100,100,3,-1,2);
    Lower_muDisplacedStandAloneFreeInverseBeta_Lower_muDisplacedStandAloneFreeInverseBetaErr_hist = new TH2D("Lower_muDisplacedStandAloneFreeInverseBeta_Lower_muDisplacedStandAloneFreeInverseBetaErr_hist","DT Free Inverse Beta vs Free Inverse Beta Error",1000,-50,50,10000,0,1000);

    Lower_runNumber_muDisplacedStandAloneDtTofFreeInverseBeta_hist = new TH2D("Lower_runNumber_muDisplacedStandAloneDtTofFreeInverseBeta_hist","run number vs free #beta^{-1} of StandAlone Muons",10000,190000,210000,1000,-50,50);
    Lower_runNumber_muDisplacedStandAloneDtTofInverseBeta_hist = new TH2D("Lower_runNumber_muDisplacedStandAloneDtTofInverseBeta_hist","run number vs #beta^{-1} of StandAlone Muons",10000,190000,210000,1000,-5,5);
    Lower_runNumber_muDisplacedStandAlonePt_hist = new TH2D("Lower_runNumber_muDisplacedStandAlonePt_hist","run number vs p_T of StandAlone Muons",10000,190000,210000,1000,0,1000);
    Lower_runNumber_muDisplacedStandAlonePhi_hist = new TH2D("Lower_runNumber_muDisplacedStandAlonePhi_hist","",10000,190000,210000,64,-3.2,3.2);
    Lower_runNumber_muDisplacedStandAloneN_hist = new TH2D("Lower_runNumber_muDisplacedStandAloneN_hist","",10000,190000,210000,10,0,10);
    Lower_muDisplacedStandAloneEta_Phi_hist = new TH2D("Lower_muDisplacedStandAloneEta_Phi_hist","",120,-6,6,64,-3.2,3.2);
        
    Upper_Lower_muDisplacedStandAlone_deltaPhi_hist = new TH1D("Upper_Lower_muDisplacedStandAlone_deltaPhi_hist","Delta Phi",500,0,5);
    mudiff_muDisplacedStandAloneTofTimeAtIpInOut_hist = new TH1D("mudiff_muDisplacedStandAloneTofTimeAtIpInOut_hist","Time at IP InOut of First minus Second StandAlone Muon",400,-100,100);
    mudiff_muDisplacedStandAloneTofTimeAtIpOutIn_hist = new TH1D("mudiff_muDisplacedStandAloneTofTimeAtIpOutIn_hist","Time at IP OutIn of First minus Second StandAlone Muon",400,-100,100);
    mudiff_muDisplacedStandAloneTofFreeInverseBeta_hist = new TH1D("mudiff_muDisplacedStandAloneTofFreeInverseBeta_hist","Free Inverse Beta of First minus Second StandAlone Muon",400,-20,20);
    mudiff_muDisplacedStandAloneTofDirection_hist = new TH1D("mudiff_muDisplacedStandAloneTofDirection_hist","TOF Direction of First minus Second StandAlone Muon",5,-2,3);
    mudiff_muDisplacedStandAloneTrackDtTofErrDiff_hist = new TH1D("mudiff_muDisplacedStandAloneTrackDtTofErrDiff_hist","TimeInOut Error - TimeOutInError of first minus that of 2nd",400,-100,100);
    Upper_Lower_muDisplacedStandAlone_chargeMultiply_hist = new TH1D("Upper_Lower_muDisplacedStandAlone_chargeMultiply_hist","Charge0*Charge1",3,-1,2);
    Upper_Lower_muDisplacedStandAlone_directionMultiply_hist = new TH1D("Upper_Lower_muDisplacedStandAlone_directionMultiply_hist","Direction0*Direction1",3,-1,2);
    Upper_Lower_muDisplacedStandAloneBxAverage_hist = new TH1D("Upper_Lower_muDisplacedStandAloneBxAverage_hist","Upper and Lower StandAlone Muon RPC BX Average",100,-5,5);
    mudiff_muDisplacedStandAloneBxAverage_hist = new TH1D("mudiff_muDisplacedStandAloneBxAverage_hist","BX Average of First minus Second StandAlone Muon",200,-10,10);

    Upper_Lower_muDisplacedStandAloneTofTimeAtIpInOut_hist = new TH2D("Upper_Lower_muDisplacedStandAloneTofTimeAtIpInOut_hist","Time at IP InOut of First vs Second StandAlone Muon",400,-100,100,400,-100,100);
    Upper_Lower_muDisplacedStandAloneTofTimeAtIpOutIn_hist = new TH2D("Upper_Lower_muDisplacedStandAloneTofTimeAtIpOutIn_hist","Time at IP OutIn of First vs Second StandAlone Muon",500,-50,150,400,-50,150);
    Upper_Lower_muDisplacedStandAloneTrackCharge_hist = new TH2D("Upper_Lower_muDisplacedStandAloneTrackCharge_hist","Charge0 vs Charge1",3,-1,2,3,-1,2);
    Upper_Lower_muDisplacedStandAloneTrackDtTofDirection_hist = new TH2D("Upper_Lower_muDisplacedStandAloneTrackDtTofDirection_hist","Direction0 vs Direction1",3,-1,2,3,-1,2);
    Upper_Lower_muDisplacedStandAlonePt_hist = new TH2D("Upper_Lower_muDisplacedStandAlonePt_hist","Upper Pt vs Lower Pt",100,0,1000,100,0,1000);
    Upper_Lower_muDisplacedStandAloneDtTofFreeInverseBeta_hist = new TH2D("Upper_Lower_muDisplacedStandAloneDtTofFreeInverseBeta_hist","Inverse beta0 vs inverse beta1",1000,-50,50,1000,-50,50);
    Upper_Lower_muDisplacedStandAloneRpcBxPattern_hist = new TH2D("Upper_Lower_muDisplacedStandAloneRpcBxPattern_hist","Upper vs Lower StandAlone Muon RPC BX Pattern",9,0,9,9,0,9);
    mudiff_muDisplacedStandAloneTofTimeAtIpInOut_muDisplacedStandAloneTofFreeInverseBeta_hist = new TH2D("mudiff_muDisplacedStandAloneTofTimeAtIpInOut_muDisplacedStandAloneTofFreeInverseBeta_hist","Time at IP InOut of First minus Second StandAlone Muon vs diff free inverse beta",400,-100,100,400,-20,20);

    Upper_muDisplacedStandAloneP_mudiff_muDisplacedStandAloneBxAverage_hist = new TH2D("Upper_muDisplacedStandAloneP_mudiff_muDisplacedStandAloneBxAverage_hist","Upper DSA p vs BX Average of First minus Second StandAlone Muon",100,0,1000,200,-5,5);
    Lower_muDisplacedStandAloneP_mudiff_muDisplacedStandAloneBxAverage_hist = new TH2D("Lower_muDisplacedStandAloneP_mudiff_muDisplacedStandAloneBxAverage_hist","Lower DSA p vs BX Average of First minus Second StandAlone Muon",100,0,1000,200,-5,5);
    
    Both_muDisplacedStandAlonePt_hist = new TH1D("Both_muDisplacedStandAlonePt_hist","StandAlone Muon p_{T}",1000,0,1000);
    Both_muDisplacedStandAloneEta_hist = new TH1D("Both_muDisplacedStandAloneEta_hist","StandAlone Muon #eta",120,-6,6);
    Both_muDisplacedStandAlonePhi_hist = new TH1D("Both_muDisplacedStandAlonePhi_hist","StandAlone Muon #phi",64,-3.2,3.2);
    Both_muDisplacedStandAloneTrackCharge_hist = new TH1D("Both_muDisplacedStandAloneTrackCharge_hist","StandAlone Muon Track Charge",10,-5,5);
    Both_muDisplacedStandAloneTrackNormalizedChi2_hist = new TH1D("Both_muDisplacedStandAloneTrackNormalizedChi2_hist","StandAlone Muon Track #chi^{2}/dof",1000,0,100);
    Both_muDisplacedStandAloneTrackDxy_hist = new TH1D("Both_muDisplacedStandAloneTrackDxy_hist","StandAlone Muon Dxy",2000,-1000,1000);
    Both_muDisplacedStandAloneTrackDz_hist = new TH1D("Both_muDisplacedStandAloneTrackDz_hist","StandAlone Muon Dz",2000,-1000,1000);
    Both_muDisplacedStandAloneTrackNHitsMuon_hist = new TH1D("Both_muDisplacedStandAloneTrackNHitsMuon_hist","Hits in StandAlone Muon Track",100,0,100);
    Both_muDisplacedStandAloneTrackNHitsCsc_hist = new TH1D("Both_muDisplacedStandAloneTrackNHitsCsc_hist","CSC Hits in StandAlone Muon Track",100,0,100);
    Both_muDisplacedStandAloneTrackNHitsDt_hist = new TH1D("Both_muDisplacedStandAloneTrackNHitsDt_hist","DT Hits in StandAlone Muon Track",100,0,100);
    Both_muDisplacedStandAloneTrackNHitsRpc_hist = new TH1D("Both_muDisplacedStandAloneTrackNHitsRpc_hist","RPC Hits in StandAlone Muon Track",10,0,10);
    Both_muDisplacedStandAloneTrackNRpcDof_hist = new TH1D("Both_muDisplacedStandAloneTrackNRpcDof_hist","RPC BX Measurements in StandAlone Muon Track",10,0,10);
    Both_muDisplacedStandAloneTrackNStations_hist = new TH1D("Both_muDisplacedStandAloneTrackNStations_hist","Muon Stations in StandAlone Muon Track",10,0,10);
    Both_muDisplacedStandAloneTrackNChambersCsc_hist = new TH1D("Both_muDisplacedStandAloneTrackNChambersCsc_hist","CSC Chambers in StandAlone Muon Track",10,0,10);
    Both_muDisplacedStandAloneTrackNChambersDt_hist = new TH1D("Both_muDisplacedStandAloneTrackNChambersDt_hist","DT Chambers in StandAlone Muon Track",10,0,10);
    Both_muDisplacedStandAloneTrackNChambersRpc_hist = new TH1D("Both_muDisplacedStandAloneTrackNChambersRpc_hist","RPC Chambers in StandAlone Muon Track",10,0,10);
    Both_muDisplacedStandAloneTrackDtTofNDof_hist = new TH1D("Both_muDisplacedStandAloneTrackDtTofNDof_hist","StandAlone Muons TOF Number of Degrees of Freedom",40,0,40);
    Both_muDisplacedStandAloneTrackDtTofInverseBeta_hist = new TH1D("Both_muDisplacedStandAloneTrackDtTofInverseBeta_hist","#beta^{-1} of StandAlone Muons",1000,-5,5);
    Both_muDisplacedStandAloneTrackDtTofInverseBetaErr_hist = new TH1D("Both_muDisplacedStandAloneTrackDtTofInverseBetaErr_hist","Error of #beta^{-1} of StandAlone Muons",10000,0,1000);
    Both_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist = new TH1D("Both_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist","Free #beta^{-1} of StandAlone Muons",1000,-50,50);
    Both_muDisplacedStandAloneTrackDtTofFreeInverseBetaErr_hist = new TH1D("Both_muDisplacedStandAloneTrackDtTofFreeInverseBetaErr_hist","Error of Free #beta^{-1} of StandAlone Muons",10000,0,1000);
    Both_muDisplacedStandAloneTrackDtTofTimeAtIpInOut_hist = new TH1D("Both_muDisplacedStandAloneTrackDtTofTimeAtIpInOut_hist","Time at IP InOut of StandAlone Muons",400,-100,100);
    Both_muDisplacedStandAloneTrackDtTofTimeAtIpOutIn_hist = new TH1D("Both_muDisplacedStandAloneTrackDtTofTimeAtIpOutIn_hist","Time at IP OutIn of StandAlone Muons",400,-50,150);
    Both_muDisplacedStandAloneTrackDtTofTimeAtIpInOutErr_hist = new TH1D("Both_muDisplacedStandAloneTrackDtTofTimeAtIpInOutErr_hist","Error of Time at IP InOut of StandAlone Muons",1000,-50,50);
    Both_muDisplacedStandAloneTrackDtTofTimeAtIpOutInErr_hist = new TH1D("Both_muDisplacedStandAloneTrackDtTofTimeAtIpOutInErr_hist","Error of Time at IP OutIn of StandAlone Muons",1000,-50,50);
    Both_muDisplacedStandAloneTrackDtTofDirection_hist = new TH1D("Both_muDisplacedStandAloneTrackDtTofDirection_hist","Direction of StandAlone Muons",3,-1,2);
    Both_muDisplacedStandAloneTrackDtTofErrDiff_hist = new TH1D("Both_muDisplacedStandAloneTrackDtTofErrDiff_hist","TimeInOut Error - TimeOutInError",400,-100,100);
    Both_muDisplacedStandAloneBxPattern_hist = new TH1D("Both_muDisplacedStandAloneBxPattern_hist","Both StandAlone Muon RPC BX Pattern",9,0,9);
    Both_muDisplacedStandAloneBxAverage_hist = new TH1D("Both_muDisplacedStandAloneBxAverage_hist","Both StandAlone Muon RPC BX Average",200,-10,10);

    Upper_muDisplacedStandAloneP_mudiff_muDisplacedStandAloneTofFreeInverseBeta_hist = new TH2D("Upper_muDisplacedStandAloneP_mudiff_muDisplacedStandAloneTofFreeInverseBeta_hist","upper p vs mudiff free inv beta",1000,0,1000,400,-20,20);

    Ave_muDisplacedStandAlonePt_hist = new TH1D("Ave_muDisplacedStandAlonePt_hist","StandAlone Muon p_{T}",1000,0,1000);
    Diff_muDisplacedStandAlonePt_hist = new TH1D("Diff_muDisplacedStandAlonePt_hist","StandAlone Muon p_{T}",1000,-500,500);

    mcMuon_muDisplacedStandAlone_3Dangle_hist = new TH2D("mcMuon_muDisplacedStandAlone_3Dangle_hist","3D Angle between 2 Gen Muons vs between 2 reco muons",500,0,5,500,0,5);
    mcMuon_muDisplacedStandAlone_deltaPhi_hist = new TH2D("mcMuon_muDisplacedStandAlone_deltaPhi_hist","Delta Phi between 2 Gen Muons vs between 2 reco muons",500,0,5,500,0,5);

    /*
    muRefittedStandAlone_N_hist = new TH1D("muRefittedStandAlone_N_hist","Number of Refitted StandAlone Muons",100,0,100);
    muRefittedStandAloneP_hist = new TH1D("muRefittedStandAloneP_hist","Refitted StandAlone Muon p",1000,0,1000);
    muRefittedStandAlonePt_hist = new TH1D("muRefittedStandAlonePt_hist","Refitted StandAlone Muon p_{T}",1000,0,1000);
    muRefittedStandAloneEta_hist = new TH1D("muRefittedStandAloneEta_hist","Refitted StandAlone Muon #eta",120,-6,6);
    muRefittedStandAlonePhi_hist = new TH1D("muRefittedStandAlonePhi_hist","Refitted StandAlone Muon #phi",64,-3.2,3.2);
    muRefittedStandAloneTrackDistanceStations_hist = new TH1D("muRefittedStandAloneTrackDistanceStations_hist","Distance between first and last Stations in StandAlone Muon Track",5,-1,4);
    muRefittedStandAloneEta_muRefittedStandAlonePhi_hist = new TH2D("muRefittedStandAloneEta_muRefittedStandAlonePhi_hist","Refitted StandAlone Muon #eta vs #phi",120,-6,6,64,-3.2,3.2);
    
    muStandAloneTof_N_hist = new TH1D("muStandAloneTof_N_hist","Number of StandAlone Muons in TOF Calculation",100,0,100);
    muStandAloneTofDirection_hist = new TH1D("muStandAloneTofDirection_hist","Direction of StandAlone Muons",3,-1,2);
    muStandAloneTofNDof_hist = new TH1D("muStandAloneTofNDof_hist","StandAlone Muons TOF Number of Degrees of Freedom",200,0,200);
    muStandAloneTofInverseBeta_hist = new TH1D("muStandAloneTofInverseBeta_hist","#beta^{-1} of StandAlone Muons",1000,-5,5);
    muStandAloneTofInverseBetaErr_hist = new TH1D("muStandAloneTofInverseBetaErr_hist","Error of #beta^{-1} of StandAlone Muons",10000,0,1000);
    muStandAloneTofFreeInverseBeta_hist = new TH1D("muStandAloneTofFreeInverseBeta_hist","Free #beta^{-1} of StandAlone Muons",1000,-50,50);
    muStandAloneTofFreeInverseBetaErr_hist = new TH1D("muStandAloneTofFreeInverseBetaErr_hist","Error of Free #beta^{-1} of StandAlone Muons",10000,0,1000);
    muStandAloneTofTimeAtIpInOut_hist = new TH1D("muStandAloneTofTimeAtIpInOut_hist","Time at IP InOut of StandAlone Muons",400,-100,100);
    muStandAloneTofTimeAtIpInOutErr_hist = new TH1D("muStandAloneTofTimeAtIpInOutErr_hist","Error of Time at IP InOut of StandAlone Muons",1000,-50,50);
    muStandAloneTofTimeAtIpOutIn_hist = new TH1D("muStandAloneTofTimeAtIpOutIn_hist","Time at IP OutIn of StandAlone Muons",300,0,150);
    muStandAloneTofTimeAtIpOutInErr_hist = new TH1D("muStandAloneTofTimeAtIpOutInErr_hist","Error of Time at IP OutIn of StandAlone Muons",100,0,20);

    muDisplacedStandAloneDTTof_N_hist = new TH1D("muDisplacedStandAloneDTTof_N_hist","Number of StandAlone Muons in TOF Calculation",100,0,100);
    muDisplacedStandAloneDTTofDirection_hist = new TH1D("muDisplacedStandAloneDTTofDirection_hist","Direction of StandAlone Muons",3,-1,2);
    muDisplacedStandAloneDTTofNDof_hist = new TH1D("muDisplacedStandAloneDTTofNDof_hist","StandAlone Muons TOF Number of Degrees of Freedom",200,0,200);
    muDisplacedStandAloneDTTofInverseBeta_hist = new TH1D("muDisplacedStandAloneDTTofInverseBeta_hist","#beta^{-1} of StandAlone Muons",1000,-5,5);
    muDisplacedStandAloneDTTofInverseBetaErr_hist = new TH1D("muDisplacedStandAloneDTTofInverseBetaErr_hist","Error of #beta^{-1} of StandAlone Muons",10000,0,1000);
    muDisplacedStandAloneDTTofFreeInverseBeta_hist = new TH1D("muDisplacedStandAloneDTTofFreeInverseBeta_hist","Free #beta^{-1} of StandAlone Muons",1000,-50,50);
    muDisplacedStandAloneDTTofFreeInverseBetaErr_hist = new TH1D("muDisplacedStandAloneDTTofFreeInverseBetaErr_hist","Error of Free #beta^{-1} of StandAlone Muons",10000,0,1000);
    muDisplacedStandAloneDTTofTimeAtIpInOut_hist = new TH1D("muDisplacedStandAloneDTTofTimeAtIpInOut_hist","Time at IP InOut of StandAlone Muons",400,-100,100);
    muDisplacedStandAloneDTTofTimeAtIpInOutErr_hist = new TH1D("muDisplacedStandAloneDTTofTimeAtIpInOutErr_hist","Error of Time at IP InOut of StandAlone Muons",1000,-50,50);
    muDisplacedStandAloneDTTofTimeAtIpOutIn_hist = new TH1D("muDisplacedStandAloneDTTofTimeAtIpOutIn_hist","Time at IP OutIn of StandAlone Muons",400,-50,150);
    muDisplacedStandAloneDTTofTimeAtIpOutInErr_hist = new TH1D("muDisplacedStandAloneDTTofTimeAtIpOutInErr_hist","Error of Time at IP OutIn of StandAlone Muons",1000,-50,50);
    
    muDisplacedStandAloneCSCTof_N_hist = new TH1D("muDisplacedStandAloneCSCTof_N_hist","Number of StandAlone Muons in TOF Calculation",100,0,100);
    muDisplacedStandAloneCSCTofDirection_hist = new TH1D("muDisplacedStandAloneCSCTofDirection_hist","Direction of StandAlone Muons",3,-1,2);
    muDisplacedStandAloneCSCTofNDof_hist = new TH1D("muDisplacedStandAloneCSCTofNDof_hist","StandAlone Muons TOF Number of Degrees of Freedom",200,0,200);
    muDisplacedStandAloneCSCTofInverseBeta_hist = new TH1D("muDisplacedStandAloneCSCTofInverseBeta_hist","#beta^{-1} of StandAlone Muons",1000,-5,5);
    muDisplacedStandAloneCSCTofInverseBetaErr_hist = new TH1D("muDisplacedStandAloneCSCTofInverseBetaErr_hist","Error of #beta^{-1} of StandAlone Muons",10000,0,1000);
    muDisplacedStandAloneCSCTofFreeInverseBeta_hist = new TH1D("muDisplacedStandAloneCSCTofFreeInverseBeta_hist","Free #beta^{-1} of StandAlone Muons",1000,-50,50);
    muDisplacedStandAloneCSCTofFreeInverseBetaErr_hist = new TH1D("muDisplacedStandAloneCSCTofFreeInverseBetaErr_hist","Error of Free #beta^{-1} of StandAlone Muons",10000,0,1000);
    muDisplacedStandAloneCSCTofTimeAtIpInOut_hist = new TH1D("muDisplacedStandAloneCSCTofTimeAtIpInOut_hist","Time at IP InOut of StandAlone Muons",400,-100,100);
    muDisplacedStandAloneCSCTofTimeAtIpInOutErr_hist = new TH1D("muDisplacedStandAloneCSCTofTimeAtIpInOutErr_hist","Error of Time at IP InOut of StandAlone Muons",1000,-50,50);
    muDisplacedStandAloneCSCTofTimeAtIpOutIn_hist = new TH1D("muDisplacedStandAloneCSCTofTimeAtIpOutIn_hist","Time at IP OutIn of StandAlone Muons",300,0,150);
    muDisplacedStandAloneCSCTofTimeAtIpOutInErr_hist = new TH1D("muDisplacedStandAloneCSCTofTimeAtIpOutInErr_hist","Error of Time at IP OutIn of StandAlone Muons",100,0,20);    
    */

    regionD_muDisplacedStandAlone_N_hist = new TH1D("regionD_muDisplacedStandAlone_N_hist","Number of StandAlone Muons",100,0,100);
    regionD_muDisplacedStandAloneP_hist = new TH1D("regionD_muDisplacedStandAloneP_hist","StandAlone Muon p",1000,0,1000);
    regionD_muDisplacedStandAlonePt_hist = new TH1D("regionD_muDisplacedStandAlonePt_hist","StandAlone Muon p_{T}",1000,0,1000);
    regionD_muDisplacedStandAloneEta_hist = new TH1D("regionD_muDisplacedStandAloneEta_hist","StandAlone Muon #eta",120,-6,6);
    regionD_muDisplacedStandAlonePhi_hist = new TH1D("regionD_muDisplacedStandAlonePhi_hist","StandAlone Muon #phi",64,-3.2,3.2);
    regionD_muDisplacedStandAloneCharge_hist = new TH1D("regionD_muDisplacedStandAloneCharge_hist","StandAlone Muon Track Charge",10,-5,5);
    regionD_muDisplacedStandAloneTrackNormalizedChi2_hist = new TH1D("regionD_muDisplacedStandAloneTrackNormalizedChi2_hist","StandAlone Muon Track #chi^{2}/dof",1000,0,100);
    regionD_muDisplacedStandAloneTrackDxy_hist = new TH1D("regionD_muDisplacedStandAloneTrackDxy_hist","StandAlone Muon Dxy",2000,-1000,1000);
    regionD_muDisplacedStandAloneTrackDz_hist = new TH1D("regionD_muDisplacedStandAloneTrackDz_hist","StandAlone Muon Dz",2000,-1000,1000);
    regionD_muDisplacedStandAloneTrackNHitsMuon_hist = new TH1D("regionD_muDisplacedStandAloneTrackNHitsMuon_hist","Hits in StandAlone Muon Track",100,0,100);
    regionD_muDisplacedStandAloneTrackNHitsCsc_hist = new TH1D("regionD_muDisplacedStandAloneTrackNHitsCsc_hist","CSC Hits in StandAlone Muon Track",100,0,100);
    regionD_muDisplacedStandAloneTrackNHitsDt_hist = new TH1D("regionD_muDisplacedStandAloneTrackNHitsDt_hist","DT Hits in StandAlone Muon Track",100,0,100);
    regionD_muDisplacedStandAloneTrackNHitsRpc_hist = new TH1D("regionD_muDisplacedStandAloneTrackNHitsRpc_hist","RPC Hits in StandAlone Muon Track",10,0,10);
    regionD_muDisplacedStandAloneTrackNRpcDof_hist = new TH1D("regionD_muDisplacedStandAloneTrackNRpcDof_hist","RPC BX Measurements in StandAlone Muon Track",10,0,10);
    regionD_muDisplacedStandAloneTrackNStations_hist = new TH1D("regionD_muDisplacedStandAloneTrackNStations_hist","Muon Stations in StandAlone Muon Track",10,0,10);
    regionD_muDisplacedStandAloneTrackNChambersCsc_hist = new TH1D("regionD_muDisplacedStandAloneTrackNChambersCsc_hist","CSC Chambers in StandAlone Muon Track",10,0,10);
    regionD_muDisplacedStandAloneTrackNChambersDt_hist = new TH1D("regionD_muDisplacedStandAloneTrackNChambersDt_hist","DT Chambers in StandAlone Muon Track",10,0,10);
    regionD_muDisplacedStandAloneTrackNChambersRpc_hist = new TH1D("regionD_muDisplacedStandAloneTrackNChambersRpc_hist","RPC Chambers in StandAlone Muon Track",10,0,10);
    regionD_muDisplacedStandAloneTrackDtTofNDof_hist = new TH1D("regionD_muDisplacedStandAloneTrackDtTofNDof_hist","StandAlone Muons TOF Number of Degrees of Freedom",40,0,40);
    regionD_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist = new TH1D("regionD_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist","Free #beta^{-1} of StandAlone Muons",1000,-50,50);
    regionD_muDisplacedStandAloneTrackDtTofFreeInverseBetaErr_hist = new TH1D("regionD_muDisplacedStandAloneTrackDtTofFreeInverseBetaErr_hist","Error of Free #beta^{-1} of StandAlone Muons",10000,0,1000);
    regionD_muDisplacedStandAloneTrackDtTofTimeAtIpInOut_hist = new TH1D("regionD_muDisplacedStandAloneTrackDtTofTimeAtIpInOut_hist","Time at IP InOut of StandAlone Muons",400,-100,100);
    regionD_muDisplacedStandAloneTrackDtTofTimeAtIpInOutErr_hist = new TH1D("regionD_muDisplacedStandAloneTrackDtTofTimeAtIpInOutErr_hist","Error of Time at IP InOut of StandAlone Muons",1000,-50,50);
    regionD_muDisplacedStandAloneBxPattern_hist = new TH1D("regionD_muDisplacedStandAloneBxPattern_hist","StandAlone Muon RPC BX Pattern",9,0,9);
    regionD_CSCSegment_N_hist = new TH1D("regionD_CSCSegment_N_hist","Number of CSC Segments",100,0,100);


    regionAB_Upper_muDisplacedStandAloneP_Upper_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist = new TH2D("regionAB_Upper_muDisplacedStandAloneP_Upper_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist","P vs DT Free Inverse Beta",1000,0,1000,1000,-50,50);
    regionAC_Upper_muDisplacedStandAloneP_Upper_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist = new TH2D("regionAC_Upper_muDisplacedStandAloneP_Upper_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist","P vs DT Free Inverse Beta",1000,0,1000,1000,-50,50);

    regionB_muDisplacedStandAloneP_hist = new TH1D("regionB_muDisplacedStandAloneP_hist","StandAlone Muon p",1000,0,1000);
    regionC_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist = new TH1D("regionC_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist","Free #beta^{-1} of StandAlone Muons",1000,-50,50);
    regionC_muDisplacedStandAloneTrackBxPattern_hist = new TH1D("regionC_muDisplacedStandAloneTrackBxPattern_hist","RPC BX Pattern of StandAlone Muons",9,0,9);

    DTSegment_N_hist = new TH1D("DTSegment_N_hist","Number of DT Segments",100,0,100);
    CSCSegment_N_hist = new TH1D("CSCSegment_N_hist","Number of CSC Segments",100,0,100);
  }
  
  ~findTreevalues_makehistos_Ntuples_allsamples() {};
  
  virtual void loop(string& file_dataset, string& BxCut, string& CavCut, string& GenMuCut, string& SACut, string& GenMuMatchedCut, string& TriggerCut, string& TriggerTurnOn_, string& NdsaCut, string& PtCut, string& ChaCut, string& EtaCut, string& UpperCut, string& RpcCut, string& DisStCut, string& RpcBxCut, string& DtHitsCut, string& InvBetaErrCut, string& CscHitsCut, string& DtInvBetaCut, string& TimeInOutCut, string& TimeInOutErrCut, string& DeltaTimeInOutCut, string& DeltaDtInvBetaCut, string& TofDirCut, string& OppEtaCut, string& OppPhiCut, string& DxyCut, string& ChargeCut, string& TightPhi, string& CosEnrich, string& resT3, string& Printout, TString& BxCutValue, TString& PreNdsaCutValue, TString& PrePtCutValue, TString& PreChaCutValue, TString& PreEtaCutValue, TString& PreRpcCutValue, TString& PreDtHitsCutValue, TString& PreInvBetaErrCutValue, TString& PreCscHitsCutValue, TString& PtCutValue, TString& ChaCutValue, TString& EtaCutValue, TString& RpcCutValue, TString& DisStCutValue, TString& DtHitsCutValue, TString& CscHitsCutValue, TString& DtInvBetaCutValue, TString& TimeInOutCutValue, TString& TimeInOutErrCutValue, TString& DeltaTimeInOutCutValue, TString& DeltaDtInvBetaCutValue, TString& OppEtaCutValue, TString& OppPhiCutValue, TString& DxyCutValue, TString& abcdInvBetaCutValue, TString& abcdPtCutValue, TString& abInvBetaCutValue, TString& cInvBetaCutValue, TString& acPtCutValue, TString& bPtCutValue);

private:
  void stops( StoppedHSCPMuonEvent*, int&, UInt_t&, bool&, bool&, bool&, bool&, int& nRhadron, int& pdgid1, int& pdgid2, int& charge1, int& charge2, double& pt1, double& pt2, double& eta1, double& eta2, double& phi1, double& phi2, int& good_genStop, UInt_t& genStop0_index, UInt_t& genStop1_index, UInt_t& genStop2_index);
  void gluinos( StoppedHSCPMuonEvent*, int&, UInt_t&, bool&, bool&, bool&, bool&, bool&, bool&, bool&, bool&, bool&, bool&, bool&, int& good_genGluino, UInt_t& genGluino0_index, UInt_t& genGluino1_index, UInt_t& genGluino2_index);
  void mchamps( StoppedHSCPMuonEvent* events,
		bool& muonFromMchamp, bool (&status1muon_)[15], bool (&status1muonFromMchamp_)[15], 
		bool (&status1muonFromMuon_)[15], int& good_genMuons, int& good_genPosMuons, int& good_genNegMuons, 
		UInt_t& genMu0_index,
		UInt_t& genPosMu0_index, UInt_t& genPosMu1_index, UInt_t& genPosMuUpper_index, UInt_t& genPosMuLower_index,
		UInt_t& genNegMu0_index, UInt_t& genNegMu1_index, UInt_t& genNegMuUpper_index, UInt_t& genNegMuLower_index,
		Double_t& anglePos, Double_t& angleNeg,
		int& good_genTauPrime, UInt_t& genTauPrime0_index, UInt_t& genTauPrime1_index, UInt_t& genTauPrime2_index);
  void staus( StoppedHSCPMuonEvent*, int&, UInt_t&, bool&, bool&, bool&, bool&, bool&, int&, UInt_t&, UInt_t&, UInt_t&);
  void cosmicMC( StoppedHSCPMuonEvent*, int&, UInt_t&, bool&);
  void genMuMatch( StoppedHSCPMuonEvent* events, UInt_t (&genMuMatched_DSA_index)[15], UInt_t (&genMuMatched_mu_index)[15], UInt_t (&genMuMatched_SA_index)[15], UInt_t (&genMuMatched_SAUpdatedAtVtx_index)[15], UInt_t (&genMuMatched_RSA_index)[15], UInt_t (&genMuMatched_cosmic_index)[15]);
  void simTracks( StoppedHSCPMuonEvent* events, UInt_t& simTrack0_index);
  void doublyChargedHiggs( StoppedHSCPMuonEvent* events, bool (&status2H_)[15], int& good_genH, UInt_t& genH0_index, UInt_t& genH1_index, UInt_t& genHpos_index, UInt_t& genHneg_index, Double_t& angle );
  void tauPrime( StoppedHSCPMuonEvent* events, bool (&status2H_)[15], int& good_genH, UInt_t& genH0_index, UInt_t& genH1_index, UInt_t& genHpos_index, UInt_t& genHneg_index, Double_t& angle );

  double eventWeightTauPrime( StoppedHSCPMuonEvent* events, UInt_t& genHpos_index, UInt_t& genHneg_index, double (&eventweightPt)[500][500]);
  //double eventWeightTauPrime( StoppedHSCPMuonEvent* events, UInt_t& genHpos_index, UInt_t& genHneg_index, double (&eventweightPt)[160][160]);

  void stop_counts( StoppedHSCPMuonEvent*, bool&, bool&, bool&, bool&);
  void gluino_counts( StoppedHSCPMuonEvent*, bool&, bool&, bool&, bool&, bool&, bool&, bool&, bool&, bool&, bool&, bool&);
  void mchamp_counts( StoppedHSCPMuonEvent*, int&, int&, UInt_t&, UInt_t&, UInt_t&, UInt_t&);
  void stau_counts( StoppedHSCPMuonEvent*, bool&, bool&, bool&);
  void cosmicMC_counts( StoppedHSCPMuonEvent*, bool&);

  bool stopStoppedParticleMatched(StoppedHSCPMuonEvent* events, UInt_t& genStop_index);
  bool gluinoStoppedParticleMatched(StoppedHSCPMuonEvent* events, UInt_t& genGluino_index);
  bool tauprimeStoppedParticleMatched(StoppedHSCPMuonEvent* events, UInt_t& genTauPrime_index);
  bool stauStoppedParticleMatched(StoppedHSCPMuonEvent* events, UInt_t& genStau_index);

  void pickStoppedParticle( StoppedHSCPMuonEvent* events, UInt_t& stopped_index);
  void StoppedParticles( StoppedHSCPMuonEvent* events, double& eventweightTauPrime, UInt_t& stoppedPos_index, UInt_t& stoppedNeg_index, UInt_t& stopped_index, int& n_stoppedInDetector);
  void StoppingRegionAcceptance( StoppedHSCPMuonEvent*, double&, UInt_t&);

  bool genMuonMatched( StoppedHSCPMuonEvent*);
  bool multipleMuons_PtCut( StoppedHSCPMuonEvent* );
  bool diMuMass_Cut( StoppedHSCPMuonEvent* );

  int Rpc_Bx_Pattern( StoppedHSCPMuonEvent*, UInt_t&);
  double Rpc_Bx_Average( StoppedHSCPMuonEvent*, UInt_t&, UInt_t&); //upper and lower
  double Rpc_Bx_Average( StoppedHSCPMuonEvent*, UInt_t&); //highest pt
  double dR_OppositeSeg( StoppedHSCPMuonEvent*, UInt_t&, double&, double& );
  int distanceBetweenStations( StoppedHSCPMuonEvent*, UInt_t&, bool&);

  void PreselectionSA( StoppedHSCPMuonEvent* , int&, UInt_t&, UInt_t&, UInt_t&, UInt_t&, UInt_t&, float&, Int_t&, float&, Int_t&, Int_t&, float&, Int_t&, bool&, bool&, bool&, bool&, bool&, bool&, bool&, bool&);
  //void PreselectionSA( StoppedHSCPMuonEvent* , int&, UInt_t&, UInt_t&, UInt_t&, UInt_t&, float&, Int_t&, float&, UInt_t&, Int_t&, float&, Int_t&, bool&, bool&, bool&, bool&, bool&, bool&, bool&);
  void PreselectionSA_counts(bool&, bool&, bool&, bool&, bool&, bool&, bool&, bool&);
  void HighestPtSA( StoppedHSCPMuonEvent* events, string& file_dataset, UInt_t& presel0_index, UInt_t& presel1_index, UInt_t& presel2_index, UInt_t& presel3_index, UInt_t& highestPt_index, float& PtCutValue_, Int_t& ChaCutValue_, float& EtaCutValue_, Int_t& RpcCutValue_, Int_t& DisStCutValue_, Int_t& DtHitsCutValue_, Int_t& CscHitsCutValue_, float& DtInvBetaCutValue_, float& TimeInOutCutValue_, float& TimeInOutErrCutValue_, float& OppEtaCutValue_, float& OppPhiCutValue_, float& DxyCutValue_, bool& pass_Upper, bool& pass_pt, bool& pass_cha, bool& pass_eta, bool& pass_RPC, bool& pass_DisSt, bool& pass_DtHits, bool& pass_CscHits, bool& pass_DtInvBeta, bool& pass_TimeInOut, bool& pass_TimeInOutErr, bool& pass_TofDir, bool& pass_Rpc_Bx, bool& pass_OppEta, bool& pass_OppPhi, bool& pass_Dxy);
  void HighestPtSA_counts( bool& pass_Upper, bool& pass_pt, bool& pass_cha, bool& pass_eta, bool& pass_RPC, bool& pass_DisSt, bool& pass_DtHits, bool& pass_CscHits, bool& pass_DtInvBeta, bool& pass_TimeInOut, bool& pass_TimeInOutErr, bool& pass_TofDir,  bool& pass_Rpc_Bx, bool& pass_OppEta, bool& pass_OppPhi, bool& pass_Dxy);
  void pick_UpperAndLowerSA( StoppedHSCPMuonEvent*, int&,int&,int&, UInt_t&, UInt_t&, UInt_t&, UInt_t&, UInt_t&, UInt_t&, UInt_t&, UInt_t&, UInt_t&, UInt_t&);
  void UpperAndLowerSA( StoppedHSCPMuonEvent* events, string& file_dataset, UInt_t& upper0_index, UInt_t& lower0_index, UInt_t& upper1_index, UInt_t& lower1_index, UInt_t& upper2_index, UInt_t& lower2_index, UInt_t& upper_index, UInt_t& lower_index, float& PtCutValue_, Int_t& ChaCutValue_, float& EtaCutValue_, Int_t& RpcCutValue_,  Int_t& DisStCutValue_, Int_t& DtHitsCutValue_, float& DtInvBetaCutValue_, float& TimeInOutCutValue_, float& TimeInOutErrCutValue_, float& DeltaTimeInOutCutValue_, float& DeltaDtInvBetaCutValue_, bool& pass_UpperAndLower, bool& pass_pt_2, bool& pass_cha_2, bool& pass_eta_2, bool& pass_RPC_2,  bool& pass_DisSt_2, bool& pass_DtHits_2, bool& pass_OppEta_2, bool& pass_OppPhi_2, bool& pass_Rpc_Bx_2, bool& pass_DtInvBeta_2, bool& pass_TimeInOut_2, bool& pass_TimeInOutErr_2, bool& pass_DeltaTimeInOut_2, bool& pass_DeltaDtInvBeta_2, bool& pass_TofDir_2, bool& pass_charge_2);
  void UpperAndLowerSA_counts(bool& pass_UpperAndLower, bool& pass_pt_2, bool& pass_cha_2, bool& pass_eta_2, bool& pass_RPC_2,  bool& pass_DisSt_2, bool& pass_DtHits_2, bool& pass_OppEta_2, bool& pass_OppPhi_2, bool& pass_Rpc_Bx_2, bool& pass_DtInvBeta_2, bool& pass_TimeInOut_2, bool& pass_TimeInOutErr_2, bool& pass_DeltaTimeInOut_2, bool& pass_DeltaDtInvBeta_2, bool& pass_TofDir_2, bool& pass_charge_2);
  void TriggerTurnOn( StoppedHSCPMuonEvent*, string&, UInt_t&);
  void GlobalSATagAndProbe( StoppedHSCPMuonEvent* events, UInt_t& presel0_index);


  void printout_setup(StoppedHSCPMuonEvent*, bool& is_data);
  void printout_gen(StoppedHSCPMuonEvent*);
  void printout_DSA(StoppedHSCPMuonEvent*);
  void printout_SA(StoppedHSCPMuonEvent*);
  void printout_SA_UpdatedAtVtx(StoppedHSCPMuonEvent*);
  void printout_RSA(StoppedHSCPMuonEvent*);
  void printout_cosmic(StoppedHSCPMuonEvent*);
  void printout_tuneP_global(StoppedHSCPMuonEvent*);
  void printout_L2(StoppedHSCPMuonEvent*);
  void printout_L1(StoppedHSCPMuonEvent*);

  bool doBxCut, doCavCut, doGenMuCut, doSACut, doGenMuMatchedCut, doTriggerCut, doTriggerTurnOn, doNdsaCut, doPtCut, doChaCut, doEtaCut, doUpperCut, doRpcCut, doDisStCut, doRpcBxCut, doDtHitsCut, doInvBetaErrCut, doCscHitsCut, doDtInvBetaCut, doTimeInOutCut, doTimeInOutErrCut, doDeltaTimeInOutCut, doDeltaDtInvBetaCut, doTofDirCut, doOppEtaCut, doOppPhiCut, doChargeCut, doDxyCut, doTightPhi, doCosEnrich, doPrintout;
  UInt_t PreNdsaCutValue_;
  Int_t PreRpcCutValue_, PreChaCutValue_, PreDtHitsCutValue_, PreCscHitsCutValue_;
  //Int_t PreChaCutValue_, PreDtHitsCutValue_, PreCscHitsCutValue_;
  //UInt_t PreRpcCutValue_;
  float PrePtCutValue_, PreEtaCutValue_, PreInvBetaErrCutValue_;
  Int_t RpcCutValue_, DisStCutValue_, BxCutValue_, ChaCutValue_, DtHitsCutValue_, CscHitsCutValue_;
  float PtCutValue_, EtaCutValue_, DtInvBetaCutValue_, TimeInOutCutValue_, TimeInOutErrCutValue_, DeltaTimeInOutCutValue_, DeltaDtInvBetaCutValue_, OppEtaCutValue_, OppPhiCutValue_, DxyCutValue_;
  float abcdInvBetaCutValue_, abcdPtCutValue_, abInvBetaCutValue_, cInvBetaCutValue_, acPtCutValue_, bPtCutValue_;
  
  double tracker_count_, eb_count_, ee_count_, hb_count_, he_count_, mb_count_, me_count_, other_detector_count_, cavern_count_, detector_count_, total_count_;
  double tracker_AccCount_, eb_AccCount_, ee_AccCount_, hb_AccCount_, he_AccCount_, mb_AccCount_, me_AccCount_, other_detector_AccCount_, cavern_AccCount_, detector_AccCount_;
  int pass_bx_cut, pass_cavern_cut,
    pass_Ntops_cut, pass_Nstops_cut, pass_Ngluinos_cut, pass_Nmchamps_cut, pass_Nstaus_cut, pass_tauFromStau_cut, pass_WFromTop_cut, pass_muon_cut, pass_status1muon_cut, pass_status1muonFromW_cut, pass_status1muonFromTau_cut, pass_status1muonFromMuon_cut, pass_status1muonFromBbaryon_cut, pass_status1muonFromCbaryon_cut, pass_status1muonFromSbaryon_cut, pass_status1muonFromBmeson_cut, pass_status1muonFromCmeson_cut, pass_status1muonFromJPsi_cut, pass_status1muonFromLightMeson_cut, 
    pass_generatorMuon_cut, pass_standaloneMuon_cut, pass_genMuonMatched_cut, pass_trigger_cut, pass_10trigger_cut,
    pass_PreNdsa_cut, pass_Prept_cut, pass_Precha_cut, pass_Preeta_cut,  pass_PreRPC_cut, pass_PreDtHits_cut, pass_PreInvBetaErr_cut, pass_PreCscHits_cut, 
    pass_pt_cut, pass_cha_cut, pass_eta_cut, pass_Upper_cut, pass_RPC_cut, pass_DisSt_cut, pass_Rpc_Bx_cut, pass_DtHits_cut, pass_CscHits_cut, pass_DtInvBeta_cut, pass_TimeInOut_cut, pass_TimeInOutErr_cut, pass_TofDir_cut, pass_OppEta_cut, pass_OppPhi_cut, pass_Dxy_cut,
    pass_SA_2_cut, pass_UpperAndLower_cut, pass_UpperOnly_cut, pass_LowerOnly_cut, pass_pt_2_cut, pass_UpperAndLower_pt30_cut, pass_cha_2_cut, pass_eta_2_cut, pass_RPC_2_cut, pass_DisSt_2_cut, pass_Rpc_Bx_2_cut, pass_DtHits_2_cut, pass_DtInvBeta_2_cut, pass_TimeInOut_2_cut, pass_TimeInOutErr_2_cut, pass_DeltaTimeInOut_2_cut, pass_DeltaDtInvBeta_2_cut, pass_TofDir_2_cut, pass_OppEta_2_cut, pass_OppPhi_2_cut, pass_charge_2_cut;
  int PtPrecision, EtaPrecision, PhiPrecision, ChargePrecision, X2DOFPrecision, TimeAtIpInOutPrecision, line;
  int nPrintedOutEvents, nAregion, nBregion, nCregion, nDregion, nAregionDir, nBregionDir, nCregionDir, nDregionDir, nAprimeRegion, nBprimeRegion;
  int nA1region, nA2region, nA3region, nA4region, nB1region, nB2region, nB3region, nB4region, nC1region, nC2region, nC3region, nC4region;

  int nAregionHighestP_, nBregionHighestP_, nCregionHighestP_, nDregionHighestP_, nAregionRpc_, nBregionRpc_, nCregionRpc_, nDregionRpc_;
  double nUpperPLargerThanCut[51], nLowerPLargerThanCut[51], nHighestPLargerThanCut[51], nDifferencePLargerThanCut[51], nAvePLargerThanCut[51], nUpperPtLargerThanCut[51], nLowerPtLargerThanCut[51], nHighestPtLargerThanCut[51], nDifferencePtLargerThanCut[51], nAvePtLargerThanCut[51], nProductPtLargerThanCut[51];
  double nAregionUpperP[51], nBregionUpperP[51], nCregionUpperP[51], nDregionUpperP[51], 
    nAregionLowerP[51], nBregionLowerP[51], nCregionLowerP[51], nDregionLowerP[51], 
    nAregionHighestP[51], nBregionHighestP[51], nCregionHighestP[51], nDregionHighestP[51], 
    nAregionDifferenceP[51], nBregionDifferenceP[51], nCregionDifferenceP[51], nDregionDifferenceP[51], 
    nAregionAveP[51], nBregionAveP[51], nCregionAveP[51], nDregionAveP[51], 
    nAregionUpperPt[51], nBregionUpperPt[51], nCregionUpperPt[51], nDregionUpperPt[51], 
    nAregionLowerPt[51], nBregionLowerPt[51], nCregionLowerPt[51], nDregionLowerPt[51], 
    nAregionHighestPt[51], nBregionHighestPt[51], nCregionHighestPt[51], nDregionHighestPt[51], 
    nAregionDifferencePt[51], nBregionDifferencePt[51], nCregionDifferencePt[51], nDregionDifferencePt[51], 
    nAregionAvePt[51], nBregionAvePt[51], nCregionAvePt[51], nDregionAvePt[51], 
    nAregionProductPt[51], nBregionProductPt[51], nCregionProductPt[51], nDregionProductPt[51];
  double nAregionInverseBeta[11], nBregionInverseBeta[11], nCregionInverseBeta[11], nDregionInverseBeta[11],
    nAregionTimeInOut[11], nBregionTimeInOut[11], nCregionTimeInOut[11], nDregionTimeInOut[11],
    nAregionDifferenceInverseBeta[11], nBregionDifferenceInverseBeta[11], nCregionDifferenceInverseBeta[11], nDregionDifferenceInverseBeta[11],
    nAregionDifferenceTimeInOut[11], nBregionDifferenceTimeInOut[11], nCregionDifferenceTimeInOut[11], nDregionDifferenceTimeInOut[11];

  //define histograms
  TH1D* id_hist;
  TH1D* run_hist;
  TH1D* bx_hist; 
  TH1D* bxWrtCollision_hist;
  TH1D* bxWrtBunch_hist;

  TH1D* mcStoppedParticle_N_hist;
  TH1D* mcStoppedParticleX_hist; 
  TH1D* mcStoppedParticleY_hist; 
  TH1D* mcStoppedParticleZ_hist; 
  TH1D* mcStoppedParticleR_hist; 
  TH1D* mcStoppedParticleEta_hist;
  TH1D* mcStoppedParticlePhi_hist;
  TH1D* mcStoppedParticleTime_hist;
  TH2D* mcStoppedParticleXY_hist; 
  TH2D* mcStoppedParticleR_muDisplacedStandAloneEta_hist;

  TH1D* mcStoppedParticleMass_hist;
  TH1D* mcStoppedParticleId_hist;
  TH1D* mcStoppedParticleCharge_hist;

  TH2D* mcStoppedParticleX_StoppedParticleN_hist;
  TH2D* mcStoppedParticleY_StoppedParticleN_hist;
  TH2D* mcStoppedParticleZ_StoppedParticleN_hist;
  TH2D* mcStoppedParticleId_StoppedParticleN_hist;
  TH2D* mcStoppedParticleCharge_StoppedParticleN_hist;
  TH2D* mcStoppedParticleTime_mcStoppedParticleCharge_hist;

  TH1D* mcStoppedParticleXPos2Stopped_hist;
  TH1D* mcStoppedParticleYPos2Stopped_hist;
  TH1D* mcStoppedParticleZPos2Stopped_hist;
  TH1D* mcStoppedParticleRPos2Stopped_hist;
  TH1D* mcStoppedParticleXNeg2Stopped_hist;
  TH1D* mcStoppedParticleYNeg2Stopped_hist;
  TH1D* mcStoppedParticleZNeg2Stopped_hist;
  TH1D* mcStoppedParticleRNeg2Stopped_hist;
  TH1D* mcStoppedParticleDeltaTime_hist;
  TH1D* mcStoppedParticleXPos_hist;
  TH1D* mcStoppedParticleYPos_hist;
  TH1D* mcStoppedParticleZPos_hist;
  TH1D* mcStoppedParticleRPos_hist;
  TH1D* mcStoppedParticleXNeg_hist;
  TH1D* mcStoppedParticleYNeg_hist;
  TH1D* mcStoppedParticleZNeg_hist;
  TH1D* mcStoppedParticleRNeg_hist;

  TH1D* mcStoppedParticle0Charge_hist;
  TH1D* mcStoppedParticle1Charge_hist;
  TH1D* mcStoppedParticle0Time_hist;
  TH1D* mcStoppedParticle1Time_hist;

  TH1D* mcLL_N_hist;
  TH1D* mcLLStatus_hist;
  TH1D* mcLLPt_hist; 
  TH1D* mcLLEta_hist;
  TH1D* mcLLPhi_hist;
  TH1D* mcLLCharge_hist;
  TH1D* mcLLMass_hist;
  TH1D* mcLLNDaughters_hist;
  TH1D* mcLLDaughterId_hist;

  TH1D* mcRhadron_N_hist;
  TH1D* mcRhadronPt_hist;
  TH1D* mcRhadronEta_hist;
  TH1D* mcRhadronPhi_hist;
  TH1D* mcRhadronCharge_hist;

  TH1D* mcStop_N_hist;
  TH1D* mcStop0Charge_hist;
  TH1D* mcStop1Charge_hist;
  TH1D* mcStopP_hist;
  TH1D* mcStopPx_hist;
  TH1D* mcStopPy_hist;
  TH1D* mcStopPz_hist;
  TH1D* mcStopPt_hist;
  TH1D* mcStopEta_hist;
  TH1D* mcStopPhi_hist;
  TH1D* mcStopBeta_hist;

  TH1D* stopped_mcStopP_hist;
  TH1D* stopped_mcStopPt_hist;
  TH1D* stopped_mcStopEta_hist;
  TH1D* stopped_mcStopPhi_hist;
  TH1D* stopped_mcStopBeta_hist;
  TH1D* notStopped_mcStopP_hist;
  TH1D* notStopped_mcStopPt_hist;
  TH1D* notStopped_mcStopEta_hist;
  TH1D* notStopped_mcStopPhi_hist;
  TH1D* notStopped_mcStopBeta_hist;

  TH1D* mcGluino_N_hist;
  TH1D* mcGluino0Charge_hist;
  TH1D* mcGluino1Charge_hist;
  TH1D* mcGluinoP_hist;
  TH1D* mcGluinoPx_hist;
  TH1D* mcGluinoPy_hist;
  TH1D* mcGluinoPz_hist;
  TH1D* mcGluinoPt_hist;
  TH1D* mcGluinoEta_hist;
  TH1D* mcGluinoPhi_hist;
  TH1D* mcGluinoBeta_hist;

  TH1D* stopped_mcGluinoP_hist;
  TH1D* stopped_mcGluinoPt_hist;
  TH1D* stopped_mcGluinoEta_hist;
  TH1D* stopped_mcGluinoPhi_hist;
  TH1D* stopped_mcGluinoBeta_hist;
  TH1D* notStopped_mcGluinoP_hist;
  TH1D* notStopped_mcGluinoPt_hist;
  TH1D* notStopped_mcGluinoEta_hist;
  TH1D* notStopped_mcGluinoPhi_hist;
  TH1D* notStopped_mcGluinoBeta_hist;

  TH1D* mcStau_N_hist;
  TH1D* mcStau0Charge_hist;
  TH1D* mcStau1Charge_hist;
  TH1D* mcStauP_hist;
  TH1D* mcStauPx_hist;
  TH1D* mcStauPy_hist;
  TH1D* mcStauPz_hist;
  TH1D* mcStauPt_hist;
  TH1D* mcStauEta_hist;
  TH1D* mcStauPhi_hist;
  TH1D* mcStauBeta_hist;

  TH1D* stopped_mcStauP_hist;
  TH1D* stopped_mcStauPt_hist;
  TH1D* stopped_mcStauEta_hist;
  TH1D* stopped_mcStauPhi_hist;
  TH1D* stopped_mcStauBeta_hist;
  TH1D* notStopped_mcStauP_hist;
  TH1D* notStopped_mcStauPt_hist;
  TH1D* notStopped_mcStauEta_hist;
  TH1D* notStopped_mcStauPhi_hist;
  TH1D* notStopped_mcStauBeta_hist;

  TH1D* mcH0Charge_hist;
  TH1D* mcH1Charge_hist;

  TH1D* mcHPlusPlusP_hist;
  TH1D* mcHPlusPlusPx_hist;
  TH1D* mcHPlusPlusPy_hist;
  TH1D* mcHPlusPlusPz_hist;
  TH1D* mcHPlusPlusPt_hist;
  TH1D* mcHPlusPlusEta_hist;
  TH1D* mcHPlusPlusPhi_hist;
  TH1D* mcHMinusMinusP_hist;
  TH1D* mcHMinusMinusPx_hist;
  TH1D* mcHMinusMinusPy_hist;
  TH1D* mcHMinusMinusPz_hist;
  TH1D* mcHMinusMinusPt_hist;
  TH1D* mcHMinusMinusEta_hist;
  TH1D* mcHMinusMinusPhi_hist;

  TH2D* mcHPlusPlusP_HMinusMinusP_hist;
  TH2D* mcHPlusPlusPt_HMinusMinusPt_hist;
  TH2D* mcHPlusPlusEta_HMinusMinusEta_hist;
  TH2D* mcHPlusPlusPhi_HMinusMinusPhi_hist;

  TH1D* mcTauPrime_N_hist;
  TH1D* mcTauPrime0Charge_hist;
  TH1D* mcTauPrime1Charge_hist;
  TH1D* mcTauPrimeP_hist;
  TH1D* mcTauPrimePx_hist;
  TH1D* mcTauPrimePy_hist;
  TH1D* mcTauPrimePz_hist;
  TH1D* mcTauPrimePt_hist;
  TH1D* mcTauPrimeEta_hist;
  TH1D* mcTauPrimePhi_hist;
  TH1D* mcTauPrimeBeta_hist;

  TH1D* stopped_mcTauPrimeP_hist;
  TH1D* stopped_mcTauPrimePt_hist;
  TH1D* stopped_mcTauPrimeEta_hist;
  TH1D* stopped_mcTauPrimePhi_hist;
  TH1D* stopped_mcTauPrimeBeta_hist;
  TH1D* notStopped_mcTauPrimeP_hist;
  TH1D* notStopped_mcTauPrimePt_hist;
  TH1D* notStopped_mcTauPrimeEta_hist;
  TH1D* notStopped_mcTauPrimePhi_hist;
  TH1D* notStopped_mcTauPrimeBeta_hist;

  TH1D* mcTop_N_hist;
  TH1D* mcTopStatus_hist;
  TH1D* mcTopPt_hist;
  TH1D* mcTopEta_hist;
  TH1D* mcTopPhi_hist;
  TH1D* mcTopCharge_hist;
  TH1D* mcTopMass_hist;
  TH1D* mcTopNDaughters_hist;
  TH1D* mcTopDaughterId_hist;

  TH1D* mcW_N_hist;
  TH1D* mcWStatus_hist;
  TH1D* mcWPt_hist;
  TH1D* mcWEta_hist;
  TH1D* mcWPhi_hist;
  TH1D* mcWCharge_hist;
  TH1D* mcWMass_hist;
  TH1D* mcWNDaughters_hist;
  TH1D* mcWDaughterId_hist;

  TH1D* mcMuon_N_hist;
  TH1D* mcMuonP_hist;
  TH1D* mcMuonPt_hist;
  TH1D* mcMuonEta_hist;
  TH1D* mcMuonPhi_hist;
  TH1D* mcMuonCharge_hist;
  TH1D* mcMuonStatus_hist;
  TH1D* mcMuonMass_hist;
  TH1D* mcMuonMotherId_hist;
  TH1D* mcMuonVx_hist;
  TH1D* mcMuonVy_hist;
  TH1D* mcMuonVz_hist;
  TH1D* mcMuonLxy_hist;
  TH1D* mcMuonDxy_hist;
  TH1D* mcMuon3Dangle_hist;
  TH1D* mcMuonDeltaPhi_hist;
  TH1D* mcMuonInverseBeta_hist;

  TH2D* mcMuonPt_muRefittedStandAlonePt_hist;
  TH2D* mcMuonPt_muCosmicPt_hist;
  TH2D* mcMuonPt_muCosmicTrackPt_hist;
  TH2D* muDisplacedStandAlonePt_muCosmicTrackPt_hist;

  TH2D* mcMuonN_muDisplacedStandAloneN_hist;
  TH2D* mcMuonPt_muDisplacedStandAlonePt_hist;
  TH2D* mcMuonEta_muDisplacedStandAloneEta_hist;
  TH2D* mcMuonPhi_muDisplacedStandAlonePhi_hist;
  TH2D* mcMuonCharge_muDisplacedStandAloneCharge_hist;
  TH2D* mcMuonLxy_muDisplacedStandAloneLxy_hist;
  TH2D* mcMuonDxy_muDisplacedStandAloneDxy_hist;
  TH2D* mcMuonInverseBeta_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist;

  TH2D* mcMuonPt_l1MuonPt_hist;
  TH2D* mcMuonPt_hlt20Cha2MuonPt_hist;
  TH2D* mcMuonEta_l1MuonEta_hist;
  TH2D* mcMuonPhi_l1MuonPhi_hist;
  TH2D* mcMuonEta_hlt20Cha2MuonEta_hist;
  TH2D* mcMuonPhi_hlt20Cha2MuonPhi_hist;

  TH1D* simTrackN_hist;  
  TH1D* simTrackPt_hist;
  TH1D* simTrackEta_hist;
  TH1D* simTrackPhi_hist;
  TH1D* simTrackCharge_hist;
  TH1D* simTrackVx_hist;
  TH1D* simTrackVy_hist;
  TH1D* simTrackVz_hist;

  TH1D* muStandAloneP_hist;
  TH1D* muStandAloneUpdatedAtVtxP_hist;

  TH1D* muStandAlonePt_hist;
  TH1D* muStandAloneUpdatedAtVtxPt_hist;

  TH1D* muDisplacedStandAloneGenDR_hist;
  TH1D* muGenDR_hist;
  TH1D* muStandAloneTrackGenDR_hist;
  TH1D* muStandAloneTrackUpdatedAtVtxGenDR_hist;
  TH1D* muRefittedStandAloneTrackGenDR_hist;
  TH1D* muCosmicTrackGenDR_hist;

  TH2D* mcStoppedParticleR_muDisplacedStandAloneGenDR_hist;

  TH1D* muDisplacedStandAlonePtResolution_hist;
  TH1D* muPtResolution_hist;
  TH1D* muStandAlonePtResolution_hist;
  TH1D* muStandAloneUpdatedAtVtxPtResolution_hist;
  TH1D* muRefittedStandAlonePtResolution_hist;
  TH1D* muCosmicPtResolution_hist;

  TH1D* muDisplacedStandAloneQoverPtResolution_hist;
  TH1D* muQoverPtResolution_hist;
  TH1D* muStandAloneQoverPtResolution_hist;
  TH1D* muStandAloneUpdatedAtVtxQoverPtResolution_hist;
  TH1D* muRefittedStandAloneQoverPtResolution_hist;
  TH1D* muCosmicQoverPtResolution_hist;

  TH2D* muRefittedStandAlonePtResolution_muCosmicPtResolution_hist;

  TH2D* muDisplacedStandAloneNChambersDt_PtResolution_hist;
  TH2D* muRefittedStandAloneNChambersDt_PtResolution_hist;
  TH2D* muCosmicNChambersDt_PtResolution_hist;
  TH2D* muDisplacedStandAloneNChambersRpc_PtResolution_hist;
  TH2D* muRefittedStandAloneNChambersRpc_PtResolution_hist;
  TH2D* muCosmicNChambersRpc_PtResolution_hist;

  TH2D* muDisplacedStandAloneNChambersDt_Pt_hist;
  TH2D* muRefittedStandAloneNChambersDt_Pt_hist;
  TH2D* muCosmicNChambersDt_Pt_hist;
  TH2D* muDisplacedStandAloneNChambersRpc_Pt_hist;
  TH2D* muRefittedStandAloneNChambersRpc_Pt_hist;
  TH2D* muCosmicNChambersRpc_Pt_hist;
  
  TH2D* muRefittedStandAloneNHitsDt_Pt_hist;
  //TH2D* muRefittedStandAloneNChambersDt_Pt_hist;
  TH2D* mcStoppedParticleR_muRefittedStandAlonePt_hist;
  TH2D* mcStoppedParticleR_mcMuonPt_hist;
  TH2D* muDisplacedStandAloneTrackDistanceStations_Pt_hist;
  TH2D* muRefittedStandAloneTrackDistanceStations_Pt_hist;

  TH1D* l1Muon_N_hist;
  TH1D* l1MuonPt_hist;
  TH1D* l1MuonEta_hist;
  TH1D* l1MuonPhi_hist;

  TH1D* hlt20Cha2Muon_N_hist;
  TH1D* hlt20Cha2MuonPt_hist;
  TH1D* hlt20Cha2MuonEta_hist;
  TH1D* hlt20Cha2MuonPhi_hist;

  TH1D* mu_N_hist ;
  TH1D* muP_hist ;
  TH1D* muPt_hist ;
  TH1D* muEta_hist;
  TH1D* muPhi_hist;
  TH1D* muType_hist; 
  TH1D* muIso_hist;
  TH2D* muEta_muPhi_hist;

  TH1D* diMu_N_hist;
  TH1D* diMuMass_hist;

  TH1D* muCosmic_N_hist;
  TH1D* muCosmicP_hist;
  TH1D* muCosmicPt_hist;
  TH1D* muCosmicEta_hist;
  TH1D* muCosmicPhi_hist;
  TH1D* muCosmicType_hist;
  TH2D* muCosmicEta_muCosmicPhi_hist;

  TH1D* muCosmicTrackInnerPt_hist;

  TH1D* muCosmicTrackNChambersDt_hist;

  TH1D* muDisplacedStandAlone_N_other_cut_hist;

  TH1D* muDisplacedStandAlone_N_hist;
  TH1D* muDisplacedStandAloneP_hist;
  TH1D* muDisplacedStandAlonePt_hist;
  TH1D* muDisplacedStandAlonePt0_hist;
  TH1D* muDisplacedStandAlonePt1_hist;
  TH1D* muDisplacedStandAlonePt2_hist;
  TH1D* muDisplacedStandAloneEta_hist;
  TH1D* muDisplacedStandAlonePhi_hist;
  TH1D* muDisplacedStandAloneCharge_hist;
  TH1D* muDisplacedStandAloneTrackNormalizedChi2_hist;
  TH1D* muDisplacedStandAloneTrackDxy_hist;
  TH1D* muDisplacedStandAloneTrackDz_hist; 
  TH1D* muDisplacedStandAloneTrackNHitsMuon_hist;
  TH1D* muDisplacedStandAloneTrackNHitsCsc_hist; 
  TH1D* muDisplacedStandAloneTrackNHitsDt_hist;
  TH1D* muDisplacedStandAloneTrackNHitsRpc_hist; 
  TH1D* muDisplacedStandAloneTrackNRpcDof_hist;
  TH1D* muDisplacedStandAloneTrackNStations_hist;
  TH1D* muDisplacedStandAloneTrackNChambersCsc_hist;
  TH1D* muDisplacedStandAloneTrackNChambersDt_hist; 
  TH1D* muDisplacedStandAloneTrackNChambersRpc_hist;
  TH1D* muDisplacedStandAloneTrackDistanceStations_hist;
  TH1D* muDisplacedStandAloneTrackInnerPt_hist;
  TH1D* muDisplacedStandAloneTrackDtTofNDof_hist;
  TH1D* muDisplacedStandAloneBxPattern_hist;
  TH1D* muDisplacedStandAloneNHitsRpcBxPattern0_hist;
  TH1D* muDisplacedStandAloneBxAverage_hist;

  TH1D* muDisplacedStandAloneOppositeSegDR_hist;
  TH1D* muDisplacedStandAloneOppositeSegDEta_hist;
  TH1D* muDisplacedStandAloneOppositeSegDPhi_hist;
  
  TH1D* muDisplacedStandAlonePt_denominator_hist;
  TH1D* muDisplacedStandAlonePt_L1numerator_hist;
  TH1D* muDisplacedStandAlonePt_HLTnumerator_hist;

  TH1D* muRefittedStandAlonePt_denominator_hist;
  TH1D* muRefittedStandAlonePt_L1numerator_hist;
  TH1D* muRefittedStandAlonePt_HLTnumerator_hist;

  TH1D* muDisplacedStandAlonePt_GlSAdenominator_hist;
  TH1D* muDisplacedStandAlonePt_GlSAnumerator_hist;

  TH1D* muDisplacedStandAloneTrackShowerSize_station0_hist;
  TH1D* muDisplacedStandAloneTrackShowerSize_station1_hist;
  TH1D* muDisplacedStandAloneTrackShowerSize_station2_hist;
  TH1D* muDisplacedStandAloneTrackShowerSize_station3_hist;
  TH1D* muDisplacedStandAloneTrackShowerDeltaR_station0_hist;
  TH1D* muDisplacedStandAloneTrackShowerDeltaR_station1_hist;
  TH1D* muDisplacedStandAloneTrackShowerDeltaR_station2_hist;
  TH1D* muDisplacedStandAloneTrackShowerDeltaR_station3_hist;
  TH1D* muDisplacedStandAloneTrackShowerNHits_station0_hist;
  TH1D* muDisplacedStandAloneTrackShowerNHits_station1_hist;
  TH1D* muDisplacedStandAloneTrackShowerNHits_station2_hist;
  TH1D* muDisplacedStandAloneTrackShowerNHits_station3_hist;
  TH1D* muDisplacedStandAloneTrackShowerNCorrelatedHits_station0_hist;
  TH1D* muDisplacedStandAloneTrackShowerNCorrelatedHits_station1_hist;
  TH1D* muDisplacedStandAloneTrackShowerNCorrelatedHits_station2_hist;
  TH1D* muDisplacedStandAloneTrackShowerNCorrelatedHits_station3_hist;
  TH1D* muDisplacedStandAloneTrackShowerNUncorrelatedHits_station0_hist;
  TH1D* muDisplacedStandAloneTrackShowerNUncorrelatedHits_station1_hist;
  TH1D* muDisplacedStandAloneTrackShowerNUncorrelatedHits_station2_hist;
  TH1D* muDisplacedStandAloneTrackShowerNUncorrelatedHits_station3_hist;

  TH1D* muDisplacedStandAloneUpperOnlyDEta_hist;
  TH1D* muDisplacedStandAloneUpperOnlyDPhi_hist;
  TH1D* muDisplacedStandAloneLowerOnlyDEta_hist;
  TH1D* muDisplacedStandAloneLowerOnlyDPhi_hist;

  TH1D* muDisplacedStandAloneNCscSegments_hist;

  TH2D* muDisplacedStandAlonePhi_muDisplacedStandAloneDTTofFreeInverseBeta_hist;
  TH2D* muDisplacedStandAloneEta_muDisplacedStandAlonePhi_hist;
  TH2D* muDisplacedStandAloneTrackNHitsRpc_muDisplacedStandAloneTrackNormalizedChi2_hist;
  TH2D* muDisplacedStandAloneTrackNHitsRpc_muDisplacedStandAloneTrackNHitsDt_hist;
  TH2D* muDisplacedStandAlonePt_muDisplacedStandAloneTrackNChambersDt_hist;
  TH2D* muDisplacedStandAlonePt_DtTofFreeInverseBeta_hist;
  TH2D* muDisplacedStandAloneP_DtTofFreeInverseBeta_hist;
  TH2D* muDisplacedStandAloneP_BxPattern_hist;
  TH2D* muDisplacedStandAlonePt_BxPattern_hist;
  TH2D* muDisplacedStandAloneDtTofFreeInverseBeta_DtTofDirection_hist;
  TH2D* muDisplacedStandAloneDtTofFreeInverseBetaErr_DtTofNDof_hist;
  
  TH2D* runNumber_muDisplacedStandAloneDtTofFreeInverseBeta_hist;
  TH2D* runNumber_muDisplacedStandAloneDtTofInverseBeta_hist;
  TH2D* runNumber_muDisplacedStandAlonePt_hist;
  TH2D* runNumber_muDisplacedStandAlonePhi_hist;
  TH2D* runNumber_muDisplacedStandAloneN_hist;
  TH2D* muDisplacedStandAloneEta_Phi_hist;
  
  TH1D* Upper_muDisplacedStandAlonePt_hist;
  TH1D* Upper_muDisplacedStandAloneEta_hist;
  TH1D* Upper_muDisplacedStandAlonePhi_hist;
  TH1D* Upper_muDisplacedStandAloneTrackCharge_hist;
  TH1D* Upper_muDisplacedStandAloneTrackNormalizedChi2_hist;
  TH1D* Upper_muDisplacedStandAloneTrackDxy_hist;
  TH1D* Upper_muDisplacedStandAloneTrackDz_hist;
  TH1D* Upper_muDisplacedStandAloneTrackNHitsMuon_hist;
  TH1D* Upper_muDisplacedStandAloneTrackNHitsCsc_hist;
  TH1D* Upper_muDisplacedStandAloneTrackNHitsDt_hist;
  TH1D* Upper_muDisplacedStandAloneTrackNHitsRpc_hist;
  TH1D* Upper_muDisplacedStandAloneTrackNRpcDof_hist;
  TH1D* Upper_muDisplacedStandAloneTrackNStations_hist;
  TH1D* Upper_muDisplacedStandAloneTrackNChambersCsc_hist;
  TH1D* Upper_muDisplacedStandAloneTrackNChambersDt_hist;
  TH1D* Upper_muDisplacedStandAloneTrackNChambersRpc_hist;
  TH1D* Upper_muDisplacedStandAloneTrackDtTofNDof_hist;
  TH1D* Upper_muDisplacedStandAloneTrackDtTofInverseBeta_hist;
  TH1D* Upper_muDisplacedStandAloneTrackDtTofInverseBetaErr_hist;
  TH1D* Upper_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist;
  TH1D* Upper_muDisplacedStandAloneTrackDtTofFreeInverseBetaErr_hist;
  TH1D* Upper_muDisplacedStandAloneTrackDtTofTimeAtIpInOut_hist;
  TH1D* Upper_muDisplacedStandAloneTrackDtTofTimeAtIpOutIn_hist;
  TH1D* Upper_muDisplacedStandAloneTrackDtTofTimeAtIpInOutErr_hist;
  TH1D* Upper_muDisplacedStandAloneTrackDtTofTimeAtIpOutInErr_hist;
  TH1D* Upper_muDisplacedStandAloneTrackDtTofDirection_hist;
  TH1D* Upper_muDisplacedStandAloneTrackDtTofErrDiff_hist;
  TH1D* Upper_muDisplacedStandAloneBxPattern_hist;
  TH1D* Upper_muDisplacedStandAloneBxAverage_hist;

  TH2D* Upper_muDisplacedStandAloneTrackNHitsRpc_Upper_muDisplacedStandAloneTrackNormalizedChi2_hist;
  TH2D* Upper_muDisplacedStandAloneTrackNHitsRpc_Upper_muDisplacedStandAloneTrackNHitsDt_hist;
  TH2D* Upper_muDisplacedStandAloneBxPattern_Upper_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist;
  TH2D* Upper_muDisplacedStandAloneBxPattern_Upper_muDisplacedStandAloneTrackDtTofNDof_hist;
  TH2D* Upper_muDisplacedStandAloneBxPattern_mudiff_muDisplacedStandAloneTofTimeAtIpInOut_hist;
  TH2D* Upper_muDisplacedStandAlonePt_Upper_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist;
  TH2D* Upper_muDisplacedStandAloneP_Upper_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist;
  TH2D* Upper_muDisplacedStandAlonePt_Upper_muDisplacedStandAloneBxPattern_hist;
  TH2D* Upper_muDisplacedStandAloneP_Upper_muDisplacedStandAloneBxPattern_hist;
  TH2D* Upper_muDisplacedStandAloneTimeAtIpInOut_Upper_muDisplacedStandAloneFreeInverseBeta_hist;
  TH2D* Upper_muDisplacedStandAloneTimeAtIpInOut_Upper_muDisplacedStandAloneDirection_hist;
  TH2D* Upper_muDisplacedStandAloneFreeInverseBeta_Upper_muDisplacedStandAloneFreeInverseBetaErr_hist;

  TH2D* Highest_muDisplacedStandAloneP_Upper_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist;

  TH2D* Upper_runNumber_muDisplacedStandAloneDtTofFreeInverseBeta_hist;
  TH2D* Upper_runNumber_muDisplacedStandAloneDtTofInverseBeta_hist;
  TH2D* Upper_runNumber_muDisplacedStandAlonePt_hist;
  TH2D* Upper_runNumber_muDisplacedStandAlonePhi_hist;
  TH2D* Upper_runNumber_muDisplacedStandAloneN_hist;
  TH2D* Upper_muDisplacedStandAloneEta_Phi_hist;

  TH1D* Lower_muDisplacedStandAlonePt_hist;
  TH1D* Lower_muDisplacedStandAloneEta_hist;
  TH1D* Lower_muDisplacedStandAlonePhi_hist;
  TH1D* Lower_muDisplacedStandAloneTrackCharge_hist;
  TH1D* Lower_muDisplacedStandAloneTrackNormalizedChi2_hist;
  TH1D* Lower_muDisplacedStandAloneTrackDxy_hist;
  TH1D* Lower_muDisplacedStandAloneTrackDz_hist;
  TH1D* Lower_muDisplacedStandAloneTrackNHitsMuon_hist;
  TH1D* Lower_muDisplacedStandAloneTrackNHitsCsc_hist;
  TH1D* Lower_muDisplacedStandAloneTrackNHitsDt_hist;
  TH1D* Lower_muDisplacedStandAloneTrackNHitsRpc_hist;
  TH1D* Lower_muDisplacedStandAloneTrackNRpcDof_hist;
  TH1D* Lower_muDisplacedStandAloneTrackNStations_hist;
  TH1D* Lower_muDisplacedStandAloneTrackNChambersCsc_hist;
  TH1D* Lower_muDisplacedStandAloneTrackNChambersDt_hist;
  TH1D* Lower_muDisplacedStandAloneTrackNChambersRpc_hist;
  TH1D* Lower_muDisplacedStandAloneTrackDtTofNDof_hist;
  TH1D* Lower_muDisplacedStandAloneTrackDtTofInverseBeta_hist;
  TH1D* Lower_muDisplacedStandAloneTrackDtTofInverseBetaErr_hist;
  TH1D* Lower_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist;
  TH1D* Lower_muDisplacedStandAloneTrackDtTofFreeInverseBetaErr_hist;
  TH1D* Lower_muDisplacedStandAloneTrackDtTofTimeAtIpInOut_hist;
  TH1D* Lower_muDisplacedStandAloneTrackDtTofTimeAtIpOutIn_hist;
  TH1D* Lower_muDisplacedStandAloneTrackDtTofTimeAtIpInOutErr_hist;
  TH1D* Lower_muDisplacedStandAloneTrackDtTofTimeAtIpOutInErr_hist;
  TH1D* Lower_muDisplacedStandAloneTrackDtTofDirection_hist;
  TH1D* Lower_muDisplacedStandAloneTrackDtTofErrDiff_hist;
  TH1D* Lower_muDisplacedStandAloneBxPattern_hist;
  TH1D* Lower_muDisplacedStandAloneBxAverage_hist;

  TH2D* Lower_muDisplacedStandAloneTrackNHitsRpc_Lower_muDisplacedStandAloneTrackNormalizedChi2_hist;
  TH2D* Lower_muDisplacedStandAloneTrackNHitsRpc_Lower_muDisplacedStandAloneTrackNHitsDt_hist;
  TH2D* Lower_muDisplacedStandAloneBxPattern_Lower_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist;
  TH2D* Lower_muDisplacedStandAlonePt_Lower_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist;
  TH2D* Lower_muDisplacedStandAlonePt_Lower_muDisplacedStandAloneBxPattern_hist;
  TH2D* Lower_muDisplacedStandAloneP_Lower_muDisplacedStandAloneBxPattern_hist;
  TH2D* Lower_muDisplacedStandAloneTimeAtIpInOut_Lower_muDisplacedStandAloneFreeInverseBeta_hist;
  TH2D* Lower_muDisplacedStandAloneTimeAtIpInOut_Lower_muDisplacedStandAloneDirection_hist;
  TH2D* Lower_muDisplacedStandAloneFreeInverseBeta_Lower_muDisplacedStandAloneFreeInverseBetaErr_hist;

  TH2D* Lower_runNumber_muDisplacedStandAloneDtTofFreeInverseBeta_hist;
  TH2D* Lower_runNumber_muDisplacedStandAloneDtTofInverseBeta_hist;
  TH2D* Lower_runNumber_muDisplacedStandAlonePt_hist;
  TH2D* Lower_runNumber_muDisplacedStandAlonePhi_hist;
  TH2D* Lower_runNumber_muDisplacedStandAloneN_hist;
  TH2D* Lower_muDisplacedStandAloneEta_Phi_hist;

  TH1D* Upper_Lower_muDisplacedStandAlone_deltaPhi_hist;
  TH1D* mudiff_muDisplacedStandAloneTofTimeAtIpInOut_hist;
  TH1D* mudiff_muDisplacedStandAloneTofTimeAtIpOutIn_hist;
  TH1D* mudiff_muDisplacedStandAloneTofFreeInverseBeta_hist;
  TH1D* mudiff_muDisplacedStandAloneTofDirection_hist;
  TH1D* mudiff_muDisplacedStandAloneTrackDtTofErrDiff_hist;
  TH1D* Upper_Lower_muDisplacedStandAlone_chargeMultiply_hist;
  TH1D* Upper_Lower_muDisplacedStandAlone_directionMultiply_hist;
  TH1D* Upper_Lower_muDisplacedStandAloneBxAverage_hist;
  TH1D* mudiff_muDisplacedStandAloneBxAverage_hist;

  TH2D* Upper_Lower_muDisplacedStandAloneTofTimeAtIpInOut_hist;
  TH2D* Upper_Lower_muDisplacedStandAloneTofTimeAtIpOutIn_hist;
  TH2D* Upper_Lower_muDisplacedStandAloneTrackCharge_hist;
  TH2D* Upper_Lower_muDisplacedStandAloneTrackDtTofDirection_hist;
  TH2D* Upper_Lower_muDisplacedStandAlonePt_hist;
  TH2D* Upper_Lower_muDisplacedStandAloneDtTofFreeInverseBeta_hist;
  TH2D* Upper_Lower_muDisplacedStandAloneRpcBxPattern_hist;
  TH2D* mudiff_muDisplacedStandAloneTofTimeAtIpInOut_muDisplacedStandAloneTofFreeInverseBeta_hist;

  TH2D* Upper_muDisplacedStandAloneP_mudiff_muDisplacedStandAloneBxAverage_hist;
  TH2D* Lower_muDisplacedStandAloneP_mudiff_muDisplacedStandAloneBxAverage_hist;

  TH1D* Both_muDisplacedStandAlonePt_hist;
  TH1D* Both_muDisplacedStandAloneEta_hist;
  TH1D* Both_muDisplacedStandAlonePhi_hist;
  TH1D* Both_muDisplacedStandAloneTrackCharge_hist;
  TH1D* Both_muDisplacedStandAloneTrackNormalizedChi2_hist;
  TH1D* Both_muDisplacedStandAloneTrackDxy_hist;
  TH1D* Both_muDisplacedStandAloneTrackDz_hist;
  TH1D* Both_muDisplacedStandAloneTrackNHitsMuon_hist;
  TH1D* Both_muDisplacedStandAloneTrackNHitsCsc_hist;
  TH1D* Both_muDisplacedStandAloneTrackNHitsDt_hist;
  TH1D* Both_muDisplacedStandAloneTrackNHitsRpc_hist;
  TH1D* Both_muDisplacedStandAloneTrackNRpcDof_hist;
  TH1D* Both_muDisplacedStandAloneTrackNStations_hist;
  TH1D* Both_muDisplacedStandAloneTrackNChambersCsc_hist;
  TH1D* Both_muDisplacedStandAloneTrackNChambersDt_hist;
  TH1D* Both_muDisplacedStandAloneTrackNChambersRpc_hist;
  TH1D* Both_muDisplacedStandAloneTrackDtTofNDof_hist;
  TH1D* Both_muDisplacedStandAloneTrackDtTofInverseBeta_hist;
  TH1D* Both_muDisplacedStandAloneTrackDtTofInverseBetaErr_hist;
  TH1D* Both_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist;
  TH1D* Both_muDisplacedStandAloneTrackDtTofFreeInverseBetaErr_hist;
  TH1D* Both_muDisplacedStandAloneTrackDtTofTimeAtIpInOut_hist;
  TH1D* Both_muDisplacedStandAloneTrackDtTofTimeAtIpOutIn_hist;
  TH1D* Both_muDisplacedStandAloneTrackDtTofTimeAtIpInOutErr_hist;
  TH1D* Both_muDisplacedStandAloneTrackDtTofTimeAtIpOutInErr_hist;
  TH1D* Both_muDisplacedStandAloneTrackDtTofDirection_hist;
  TH1D* Both_muDisplacedStandAloneTrackDtTofErrDiff_hist;
  TH1D* Both_muDisplacedStandAloneBxPattern_hist;
  TH1D* Both_muDisplacedStandAloneBxAverage_hist;

  TH2D* Upper_muDisplacedStandAloneP_mudiff_muDisplacedStandAloneTofFreeInverseBeta_hist;

  TH1D* Ave_muDisplacedStandAlonePt_hist;
  TH1D* Diff_muDisplacedStandAlonePt_hist;

  TH2D* mcMuon_muDisplacedStandAlone_3Dangle_hist;
  TH2D* mcMuon_muDisplacedStandAlone_deltaPhi_hist;
  
  /*
  TH1D* muRefittedStandAlone_N_hist;
  TH1D* muRefittedStandAloneP_hist;
  TH1D* muRefittedStandAlonePt_hist;
  TH1D* muRefittedStandAloneEta_hist;
  TH1D* muRefittedStandAlonePhi_hist;
  TH1D* muRefittedStandAloneTrackDistanceStations_hist;
  TH2D* muRefittedStandAloneEta_muRefittedStandAlonePhi_hist;

  TH1D* muStandAloneTof_N_hist;
  TH1D* muStandAloneTofDirection_hist;
  TH1D* muStandAloneTofNDof_hist;
  TH1D* muStandAloneTofInverseBeta_hist;
  TH1D* muStandAloneTofInverseBetaErr_hist;
  TH1D* muStandAloneTofFreeInverseBeta_hist;
  TH1D* muStandAloneTofFreeInverseBetaErr_hist;
  TH1D* muStandAloneTofTimeAtIpInOut_hist;
  TH1D* muStandAloneTofTimeAtIpInOutErr_hist;
  TH1D* muStandAloneTofTimeAtIpOutIn_hist;
  TH1D* muStandAloneTofTimeAtIpOutInErr_hist;

  TH1D* muDisplacedStandAloneDTTof_N_hist;
  TH1D* muDisplacedStandAloneDTTofDirection_hist;
  TH1D* muDisplacedStandAloneDTTofNDof_hist;
  TH1D* muDisplacedStandAloneDTTofInverseBeta_hist;
  TH1D* muDisplacedStandAloneDTTofInverseBetaErr_hist;
  TH1D* muDisplacedStandAloneDTTofFreeInverseBeta_hist;
  TH1D* muDisplacedStandAloneDTTofFreeInverseBetaErr_hist;
  TH1D* muDisplacedStandAloneDTTofTimeAtIpInOut_hist;
  TH1D* muDisplacedStandAloneDTTofTimeAtIpInOutErr_hist;
  TH1D* muDisplacedStandAloneDTTofTimeAtIpOutIn_hist;
  TH1D* muDisplacedStandAloneDTTofTimeAtIpOutInErr_hist;

  TH1D* muDisplacedStandAloneCSCTof_N_hist;
  TH1D* muDisplacedStandAloneCSCTofDirection_hist;
  TH1D* muDisplacedStandAloneCSCTofNDof_hist;
  TH1D* muDisplacedStandAloneCSCTofInverseBeta_hist;
  TH1D* muDisplacedStandAloneCSCTofInverseBetaErr_hist;
  TH1D* muDisplacedStandAloneCSCTofFreeInverseBeta_hist;
  TH1D* muDisplacedStandAloneCSCTofFreeInverseBetaErr_hist;
  TH1D* muDisplacedStandAloneCSCTofTimeAtIpInOut_hist;
  TH1D* muDisplacedStandAloneCSCTofTimeAtIpInOutErr_hist;
  TH1D* muDisplacedStandAloneCSCTofTimeAtIpOutIn_hist;
  TH1D* muDisplacedStandAloneCSCTofTimeAtIpOutInErr_hist;
  */

  TH1D* regionD_muDisplacedStandAlone_N_hist;
  TH1D* regionD_muDisplacedStandAloneP_hist;
  TH1D* regionD_muDisplacedStandAlonePt_hist;
  TH1D* regionD_muDisplacedStandAloneEta_hist;
  TH1D* regionD_muDisplacedStandAlonePhi_hist;
  TH1D* regionD_muDisplacedStandAloneCharge_hist;
  TH1D* regionD_muDisplacedStandAloneTrackNormalizedChi2_hist;
  TH1D* regionD_muDisplacedStandAloneTrackDxy_hist;
  TH1D* regionD_muDisplacedStandAloneTrackDz_hist;
  TH1D* regionD_muDisplacedStandAloneTrackNHitsMuon_hist;
  TH1D* regionD_muDisplacedStandAloneTrackNHitsCsc_hist;
  TH1D* regionD_muDisplacedStandAloneTrackNHitsDt_hist;
  TH1D* regionD_muDisplacedStandAloneTrackNHitsRpc_hist;
  TH1D* regionD_muDisplacedStandAloneTrackNRpcDof_hist;
  TH1D* regionD_muDisplacedStandAloneTrackNStations_hist;
  TH1D* regionD_muDisplacedStandAloneTrackNChambersCsc_hist;
  TH1D* regionD_muDisplacedStandAloneTrackNChambersDt_hist;
  TH1D* regionD_muDisplacedStandAloneTrackNChambersRpc_hist;
  TH1D* regionD_muDisplacedStandAloneTrackDtTofNDof_hist;
  TH1D* regionD_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist;
  TH1D* regionD_muDisplacedStandAloneTrackDtTofFreeInverseBetaErr_hist;
  TH1D* regionD_muDisplacedStandAloneTrackDtTofTimeAtIpInOut_hist;
  TH1D* regionD_muDisplacedStandAloneTrackDtTofTimeAtIpInOutErr_hist;
  TH1D* regionD_muDisplacedStandAloneBxPattern_hist;
  TH1D* regionD_CSCSegment_N_hist;

  TH2D* regionAB_Upper_muDisplacedStandAloneP_Upper_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist;
  TH2D* regionAC_Upper_muDisplacedStandAloneP_Upper_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist;

  TH1D* regionB_muDisplacedStandAloneP_hist;
  TH1D* regionC_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist;
  TH1D* regionC_muDisplacedStandAloneTrackBxPattern_hist;

  TH1D* DTSegment_N_hist;
  TH1D* CSCSegment_N_hist;

};

void findTreevalues_makehistos_Ntuples_allsamples::stops( StoppedHSCPMuonEvent* events, int& good_genMuons, UInt_t& genMu0_index, bool& WFromTop, bool& status1muon, bool& status1muonFromW, bool& status1muonFromMuon, int& nRhadron, int& pdgid1, int& pdgid2, int& charge1, int& charge2, double& pt1, double& pt2, double& eta1, double& eta2, double& phi1, double& phi2, int& good_genStop, UInt_t& genStop0_index, UInt_t& genStop1_index, UInt_t& genStop2_index){

  for (UInt_t j=0; j<events->mcStop_N; j++) {
    if(events->mcStopStatus[j]==23){
      //cout<<"stop index "<<j<<" with status ==1"<<endl;
      good_genStop++;
      if(good_genStop==1) genStop0_index = j;
      if(good_genStop==2) genStop1_index = j;
      if(good_genStop==3) genStop2_index = j;
    }
  }

  //each event must contain at least one top
  //don't check that top came directly from stop, but check that there is at least one top and one stop in the event
  //cout<<"number of tops is: "<<events->mcTop_N<<endl;
  //check to see if at least one top from stop decays to W                                                                                                                                                                       
  for (UInt_t j=0; j<events->mcTop_N; j++) {
    for (UInt_t k=0; k<events->mcTopDaughterId.at(j).size(); k++) {
      if(TMath::Abs(events->mcTopDaughterId.at(j).at(k))==24){
	WFromTop = true;
	//cout<<"for event "<<events->id<<", WFromTop is: "<<WFromTop<<endl; 
      }
    }
  }

  //check first to see if there is a status 1 muon in the event
  for (UInt_t j=0; j<events->mcMuon_N; j++) {
    if(events->mcMuonStatus[j]==1){
      status1muon = true;

      //did status1 muon come from W? 
      //not checking if the mother of this W was a top, because could have the CMshower in between: it is enough that at least one top decays to a W 
      if(TMath::Abs(events->mcMuonMotherId[j])==24){
	status1muonFromW = true;
	genMu0_index = j;
	//cout<<"status1muonFromW and genMu0_index is: "<<genMu0_index<<endl;
      }

      //did status1 muon come from another muon? 
      if(TMath::Abs(events->mcMuonMotherId[j])==13){
	//check that at least one muon came from W, or from CMshower from W 
	for (UInt_t k=0; k<events->mcMuon_N; k++) {
	  if(TMath::Abs(events->mcMuonMotherId[k])==24){
	    status1muonFromMuon = true;
	    genMu0_index = j;
	    //cout<<"status1muonFromMuon and genMu0_index is: "<<genMu0_index<<endl;
	  }
	  if(TMath::Abs(events->mcMuonMotherId[k])==94) {
	    for (UInt_t l=0; l<events->mcCMshower_N; l++) {
	      if(TMath::Abs(events->mcCMshowerMotherId[l])==24){
		status1muonFromMuon = true;
		genMu0_index = j;
		//cout<<"status1muonFromMuon and genMu0_index is: "<<genMu0_index<<endl;
	      }
	    }
	  }
	}
      }

      if(TMath::Abs(events->mcMuonMotherId[j])==13 && !status1muonFromMuon) cout<<"mother of stable muon is muon but didn't work for event "<<events->id<<endl;
      if(TMath::Abs(events->mcMuonMotherId[j])==24 && !status1muonFromW) cout<<"mother of stable muon is W but didn't work for event "<<events->id<<endl;
    } //end of muon status is 1 
  } //end of loop over mc muons

  if(genMu0_index!=999) good_genMuons = 1;

  for (UInt_t j=0; j<events->mcGenParticle_N; j++) {
    if(TMath::Abs(events->mcGenParticleId[j]) > 1000100 && TMath::Abs(events->mcGenParticleId[j]) < 2000000){      
      //cout<<"possible rhadrons are: "<<events->mcGenParticleId[j]<<endl;
      if(pdgid1==0){
	pdgid1 = events->mcGenParticleId[j];
	pt1 = events->mcGenParticlePt[j];
	eta1 = events->mcGenParticleEta[j];
	phi1 = events->mcGenParticlePhi[j];
	nRhadron++;      
      }
      if(pdgid2==0 && pdgid1!=events->mcGenParticleId[j]){
	pdgid2 = events->mcGenParticleId[j];
	pt2 = events->mcGenParticlePt[j];
	eta2 = events->mcGenParticleEta[j];
	phi2 = events->mcGenParticlePhi[j];
	nRhadron++;      
      }
    }
  }
  
  if(TMath::Abs(pdgid1)==1000622 || TMath::Abs(pdgid1)==1000642 || TMath::Abs(pdgid1)==1006113 || TMath::Abs(pdgid1)==1006311 || TMath::Abs(pdgid1)==1006313 || TMath::Abs(pdgid1)==1006333) charge1 = 0;
  if(TMath::Abs(pdgid2)==1000622 || TMath::Abs(pdgid2)==1000642 || TMath::Abs(pdgid2)==1006113 || TMath::Abs(pdgid2)==1006311 || TMath::Abs(pdgid2)==1006313 || TMath::Abs(pdgid2)==1006333) charge2 = 0;
  if(pdgid1==-1000612 || pdgid1==-1000632 || pdgid1==-1000652 || pdgid1==-1006211 || pdgid1==-1006213 || pdgid1==-1006321 || pdgid1==-1006323) charge1 = -1;
  if(pdgid2==-1000612 || pdgid2==-1000632 || pdgid2==-1000652 || pdgid2==-1006211 || pdgid2==-1006213 || pdgid2==-1006321 || pdgid2==-1006323) charge2 = -1;
  if(pdgid1==-1006223) charge1 = -2;
  if(pdgid2==-1006223) charge2 = -2;
  if(pdgid1==1000612 || pdgid1==1000632 || pdgid1==1000652 || pdgid1==1006211 || pdgid1==1006213 || pdgid1==1006321 || pdgid1==1006323) charge1 = 1;
  if(pdgid2==1000612 || pdgid2==1000632 || pdgid2==1000652 || pdgid2==1006211 || pdgid2==1006213 || pdgid2==1006321 || pdgid2==1006323) charge2 = 1;
  if(pdgid1==1006223) charge1 = 2;
  if(pdgid2==1006223) charge2 = 2;
  //cout<<"R-hadron from gen particles ID is: "<<pdgid1<<", charge is: "<<charge1<<", pt is: "<<pt1<<", eta is: "<<eta1<<", phi is: "<<phi1<<endl;
  //cout<<"R-hadron from gen particles ID is: "<<pdgid2<<", charge is: "<<charge2<<", pt is: "<<pt2<<", eta is: "<<eta2<<", phi is: "<<phi2<<endl;

  for (UInt_t j=0; j<events->mcRhadron_N; j++) {
    //cout<<"R-hadron from Rhadrons is: "<<events->mcRhadronId[j]<<endl;
  }

}//end of stops

void findTreevalues_makehistos_Ntuples_allsamples::gluinos( StoppedHSCPMuonEvent* events, int& good_genMuons, UInt_t& genMu0_index, bool& status1muon, bool& status1muonFromW, bool& status1muonFromTau, bool& status1muonFromMuon, bool& status1muonFromBbaryon, bool& status1muonFromCbaryon, bool& status1muonFromSbaryon, bool& status1muonFromBmeson, bool& status1muonFromCmeson, bool& status1muonFromJPsi, bool& status1muonFromLightMeson, int& good_genGluino, UInt_t& genGluino0_index, UInt_t& genGluino1_index, UInt_t& genGluino2_index){

  for (UInt_t j=0; j<events->mcGluino_N; j++) {
    if(events->mcGluinoStatus[j]==23){
      //cout<<"gluino index "<<j<<" with status ==1"<<endl;
      good_genGluino++;
      if(good_genGluino==1) genGluino0_index = j;
      if(good_genGluino==2) genGluino1_index = j;
      if(good_genGluino==3) genGluino2_index = j;
    }
  }

  //check first to see if there is a status 1 muon in the event
  for (UInt_t j=0; j<events->mcMuon_N; j++) {
    if(events->mcMuonStatus[j]==1){
      status1muon = true;
      //cout<<"mother of status 1 muon is: "<<events->mcMuonMotherId[j]<<endl; 
      if(TMath::Abs(events->mcMuonMotherId[j])==24){
	status1muonFromW = true;
	genMu0_index = j;
      }
      if(TMath::Abs(events->mcMuonMotherId[j])==15){
	status1muonFromTau = true;
	genMu0_index = j;
      }
      if(TMath::Abs(events->mcMuonMotherId[j])==13){
	status1muonFromMuon = true;
	genMu0_index = j;
      }

      //did status1 muon come from some B or D meson, j/psi,
      if(TMath::Abs(events->mcMuonMotherId[j])==5332 || TMath::Abs(events->mcMuonMotherId[j])==5232 || TMath::Abs(events->mcMuonMotherId[j])==5132 || TMath::Abs(events->mcMuonMotherId[j])==5122){
	status1muonFromBbaryon = true;
	genMu0_index = j;
      }
      if(TMath::Abs(events->mcMuonMotherId[j])==4332 || TMath::Abs(events->mcMuonMotherId[j])==4232 || TMath::Abs(events->mcMuonMotherId[j])==4132 || TMath::Abs(events->mcMuonMotherId[j])==4122){
	status1muonFromCbaryon = true;
	genMu0_index = j;
      }
      if(TMath::Abs(events->mcMuonMotherId[j])==3312){
	status1muonFromSbaryon = true;
	genMu0_index = j;
      }
      if(TMath::Abs(events->mcMuonMotherId[j])==541 || TMath::Abs(events->mcMuonMotherId[j])==531 || TMath::Abs(events->mcMuonMotherId[j])==521 || TMath::Abs(events->mcMuonMotherId[j])==511){
	status1muonFromBmeson = true;
	genMu0_index = j;
      }
      if(TMath::Abs(events->mcMuonMotherId[j])==443){
	status1muonFromJPsi = true;
	genMu0_index = j;
      }
      if(TMath::Abs(events->mcMuonMotherId[j])==431 || TMath::Abs(events->mcMuonMotherId[j])==421 || TMath::Abs(events->mcMuonMotherId[j])==411){
	status1muonFromCmeson = true;
	genMu0_index = j;
      }
      if(TMath::Abs(events->mcMuonMotherId[j])==333 || TMath::Abs(events->mcMuonMotherId[j])==221 || TMath::Abs(events->mcMuonMotherId[j])==113){
	status1muonFromLightMeson = true;
	genMu0_index = j;
      }

      //did status1 muon come from anything else? 
      if(TMath::Abs(events->mcMuonMotherId[j])!=13 && TMath::Abs(events->mcMuonMotherId[j])!=15 && TMath::Abs(events->mcMuonMotherId[j])!=24){
	if(TMath::Abs(events->mcMuonMotherId[j])!=5332 && TMath::Abs(events->mcMuonMotherId[j])!=5232 && TMath::Abs(events->mcMuonMotherId[j])!=5132 && TMath::Abs(events->mcMuonMotherId[j])!=5122
	   && TMath::Abs(events->mcMuonMotherId[j])!=4332 && TMath::Abs(events->mcMuonMotherId[j])!=4232 && TMath::Abs(events->mcMuonMotherId[j])!=4132 && TMath::Abs(events->mcMuonMotherId[j])!=4122 && TMath::Abs(events->mcMuonMotherId[j])!=3312 
	   && TMath::Abs(events->mcMuonMotherId[j])!=541 && TMath::Abs(events->mcMuonMotherId[j])!=531 && TMath::Abs(events->mcMuonMotherId[j])!=521 && TMath::Abs(events->mcMuonMotherId[j])!=511
	   && TMath::Abs(events->mcMuonMotherId[j])!=443 && TMath::Abs(events->mcMuonMotherId[j])!=431 && TMath::Abs(events->mcMuonMotherId[j])!=421 && TMath::Abs(events->mcMuonMotherId[j])!=411
	   && TMath::Abs(events->mcMuonMotherId[j])!=333 && TMath::Abs(events->mcMuonMotherId[j])!=221 && TMath::Abs(events->mcMuonMotherId[j])!=113)
	  {
	    //cout<<"for event "<<events->id<<", mother of status1 muon is: "<<events->mcMuonMotherId[j]<<endl;
	  }
      }
      
    } //end of muon status is 1 
  } //end of loop over mc muons 

  if(genMu0_index!=999) good_genMuons = 1;
  //cout<<"genMu0_index is: "<<genMu0_index<<endl;

}//end of gluinos

void findTreevalues_makehistos_Ntuples_allsamples::mchamps( StoppedHSCPMuonEvent* events,
							    bool& muonFromMchamp, bool (&status1muon_)[15], bool (&status1muonFromMchamp_)[15], 
							    bool (&status1muonFromMuon_)[15], int& good_genMuons, int& good_genPosMuons, int& good_genNegMuons, 
							    UInt_t& genMu0_index,
							    UInt_t& genPosMu0_index, UInt_t& genPosMu1_index, UInt_t& genPosMuUpper_index, UInt_t& genPosMuLower_index,
							    UInt_t& genNegMu0_index, UInt_t& genNegMu1_index, UInt_t& genNegMuUpper_index, UInt_t& genNegMuLower_index,
							    Double_t& anglePos, Double_t& angleNeg,
							    int& good_genTauPrime, UInt_t& genTauPrime0_index, UInt_t& genTauPrime1_index, UInt_t& genTauPrime2_index){


  //each event must contain at least one top 
  //don't check that top came directly from stop, but check that there is at least one top and one stop in the event 
  //cout<<"number of tops is: "<<events->mcTop_N<<endl; 
  //check to see if at least one top from stop decays to W
  for (UInt_t j=0; j<events->mcTauPrime_N; j++) {
    if(events->mcTauPrimeStatus[j]==1){
      //cout<<"stop index "<<j<<" with status ==1"<<endl;
      good_genTauPrime++;
      if(good_genTauPrime==1) genTauPrime0_index = j;
      if(good_genTauPrime==2) genTauPrime1_index = j;
      if(good_genTauPrime==3) genTauPrime2_index = j;
    }
    for (UInt_t k=0; k<events->mcTauPrimeDaughterId.at(j).size(); k++) {
      if(TMath::Abs(events->mcTauPrimeDaughterId.at(j).at(k))==13){
	muonFromMchamp = true;
	//cout<<"for event "<<events->id<<", muonFromMchamp"<<endl; 
      }
    }
  }

  //check first to see if there is a status 1 muon in the event 
  for (UInt_t j=0; j<events->mcMuon_N; j++) {
    if(events->mcMuonStatus[j]==1){
      status1muon_[j] = true;

      if(TMath::Abs(events->mcMuonMotherId[j])==17) status1muonFromMchamp_[j] = true;

      //did status1 muon come from another muon?                                                                                                                                 
      if(TMath::Abs(events->mcMuonMotherId[j])==13){
	//check that at least one muon came from W, or from CMshower from W                                                                                                      
	for (UInt_t k=0; k<events->mcMuon_N; k++) {
	  if(TMath::Abs(events->mcMuonMotherId[k])==13) status1muonFromMuon_[j] = true;
	  if(TMath::Abs(events->mcMuonMotherId[k])==94) {
	    for (UInt_t l=0; l<events->mcCMshower_N; l++) {
	      if(TMath::Abs(events->mcCMshowerMotherId[l])==13)	status1muonFromMuon_[j] = true;
	    }
	  }
	}
      }

      //did status1 muon come from a CM shower from another muon?                                                                                                                
      if(TMath::Abs(events->mcMuonMotherId[j])==94){
	for (UInt_t l=0; l<events->mcCMshower_N; l++) {
	  if(TMath::Abs(events->mcCMshowerMotherId[l])==13) status1muonFromMuon_[j] = true;
	}
      }

      //did status1 muon come from anything else?                                                                                                                                
      if(TMath::Abs(events->mcMuonMotherId[j])!=13 && TMath::Abs(events->mcMuonMotherId[j])!=17 && TMath::Abs(events->mcMuonMotherId[j])!=94){
	//cout<<"for event "<<events->id<<", mother of status1 muon is: "<<events->mcMuonMotherId[j]<<endl;
      }
      if(TMath::Abs(events->mcMuonMotherId[j])==13 && !status1muonFromMuon_[j]) cout<<"mother of stable muon is muon but didn't work for event "<<events->id<<endl;
    } //end of muon status is 1                                                                                                                                                  
  } //end of loop over mc muons

  for (UInt_t j=0; j<events->mcMuon_N; j++) {
    if(status1muonFromMchamp_[j] || status1muonFromMuon_[j]){
      if(events->mcMuonCharge[j]==1){
	good_genPosMuons++;
	if(good_genPosMuons==1) genPosMu0_index = j;
	if(good_genPosMuons==2) genPosMu1_index = j;
      }
      if(events->mcMuonCharge[j]==-1){
	good_genNegMuons++;
	if(good_genNegMuons==1) genNegMu0_index = j;
	if(good_genNegMuons==2) genNegMu1_index = j;
      }
    }
  }
  good_genMuons = good_genPosMuons + good_genNegMuons;

  //if(good_genPosMuons!=2 && good_genNegMuons!=2) cout<<"for event "<<events->id<<", have "<<good_genPosMuons<<" good positive generator muons, and have "<<good_genNegMuons<<" good negative generator mouons"<<endl;
  //if(good_genPosMuons==2 && good_genNegMuons==2) cout<<"for event "<<events->id<<", have "<<good_genPosMuons<<" good positive generator muons, and have "<<good_genNegMuons<<" good negative generator mouons"<<endl;

  if(good_genPosMuons==2) genMu0_index = genPosMu0_index;
  else if(good_genNegMuons==2) genMu0_index = genNegMu0_index;

  // 3D angle between generator muons
  if(good_genPosMuons==2 && events->mcMuonP[genPosMu0_index]!=0. && events->mcMuonP[genPosMu1_index]!=0.){
    anglePos = TMath::ACos(( (events->mcMuonPx[genPosMu0_index])*(events->mcMuonPx[genPosMu1_index]) + (events->mcMuonPy[genPosMu0_index])*(events->mcMuonPy[genPosMu1_index]) + (events->mcMuonPz[genPosMu0_index])*(events->mcMuonPz[genPosMu1_index]))/((events->mcMuonP[genPosMu0_index])*(events->mcMuonP[genPosMu1_index])));
  }
  if(good_genNegMuons==2 && events->mcMuonP[genNegMu0_index]!=0. && events->mcMuonP[genNegMu1_index]!=0.){
    angleNeg = TMath::ACos(( (events->mcMuonPx[genNegMu0_index])*(events->mcMuonPx[genNegMu1_index]) + (events->mcMuonPy[genNegMu0_index])*(events->mcMuonPy[genNegMu1_index]) + (events->mcMuonPz[genNegMu0_index])*(events->mcMuonPz[genNegMu1_index]))/((events->mcMuonP[genNegMu0_index])*(events->mcMuonP[genNegMu1_index])));
  }

  //one in upper, one in lower?
  if(good_genPosMuons==2){
    if(events->mcMuonPhi[genPosMu0_index] > events->mcMuonPhi[genPosMu1_index]){
      genPosMuUpper_index = genPosMu0_index;
      genPosMuLower_index = genPosMu1_index;
    }
    if(events->mcMuonPhi[genPosMu1_index] > events->mcMuonPhi[genPosMu0_index]){
      genPosMuUpper_index = genPosMu1_index;
      genPosMuLower_index = genPosMu0_index;
    }
  }
  if(good_genNegMuons==2){
    if(events->mcMuonPhi[genNegMu0_index] > events->mcMuonPhi[genNegMu1_index]){
      genNegMuUpper_index = genNegMu0_index;
      genNegMuLower_index = genNegMu1_index;
    }
    if(events->mcMuonPhi[genNegMu1_index] > events->mcMuonPhi[genNegMu0_index]){
      genNegMuUpper_index = genNegMu1_index;
      genNegMuLower_index = genNegMu0_index;
    }
  }

}//end of mchamps

void findTreevalues_makehistos_Ntuples_allsamples::staus( StoppedHSCPMuonEvent* events, int& good_genMuons, UInt_t& genMu0_index, bool& tauFromStau, bool& status1muon, bool& status1muonFromTau, bool& status1muonFromMuon, bool& status1muonFromNeutralino, int& good_genStau, UInt_t& genStau0_index, UInt_t& genStau1_index, UInt_t& genStau2_index){
  
  //cout<<"starting staus()"<<endl;

  for (UInt_t j=0; j<events->mcStau_N; j++) {
    if(events->mcStauStatus[j]==1){
      //cout<<"stau index "<<j<<" with status ==1"<<endl;
      good_genStau++;
      if(good_genStau==1) genStau0_index = j;
      if(good_genStau==2) genStau1_index = j;
      if(good_genStau==3) genStau2_index = j;
    }
    for (UInt_t k=0; k<events->mcStauDaughterId.at(j).size(); k++) {
      if(TMath::Abs(events->mcStauDaughterId.at(j).at(k))==15){
	tauFromStau = true;
      }
    }
  }
  
  //if(good_genStau!=2) cout<<"for event "<<events->id<<", have "<<good_genStau<<" good generator staus"<<endl;

  //check first to see if there is a status 1 muon in the event
  for (UInt_t j=0; j<events->mcMuon_N; j++) {
    if(events->mcMuonStatus[j]==1){
      status1muon = true;
      
      //did status1 muon come from tau? 
      if(TMath::Abs(events->mcMuonMotherId[j])==15){
	status1muonFromTau = true;
	genMu0_index = j;
      }
      //did status1 muon come from another muon? 
      if(TMath::Abs(events->mcMuonMotherId[j])==13){
	status1muonFromMuon = true;
	genMu0_index = j;
      }
      //did status1 muon come from a CMshower, from a neutralino? 
      if(TMath::Abs(events->mcMuonMotherId[j])==94){
	for (UInt_t k=0; k<events->mcCMshower_N; k++) {
	  if(TMath::Abs(events->mcCMshowerMotherId[k])==1000022){ 
	    status1muonFromNeutralino = true;
	    genMu0_index = j;
	  }
	}
      }

      //did status1 muon come from anything else? 
      if(TMath::Abs(events->mcMuonMotherId[j])!=15){
	//if(TMath::Abs(events->mcMuonMotherId[j])!=13 && TMath::Abs(events->mcMuonMotherId[j])!=94 && TMath::Abs(events->mcMuonMotherId[j])!=15){ 
	//if(TMath::Abs(events->mcMuonMotherId[j])!=5232 && TMath::Abs(events->mcMuonMotherId[j])!=5132 && TMath::Abs(events->mcMuonMotherId[j])!=5122 && TMath::Abs(events->mcMuonMotherId[j])!=4332 && TMath::Abs(events->mcMuonMotherId[j])!=4232 && TMath::Abs(events->mcMuonMotherId[j])!=4132 && TMath::Abs(events->mcMuonMotherId[j])!=4122 && TMath::Abs(events->mcMuonMotherId[j])!=531 && TMath::Abs(events->mcMuonMotherId[j])!=521 && TMath::Abs(events->mcMuonMotherId[j])!=511 && TMath::Abs(events->mcMuonMotherId[j])!=443 && TMath::Abs(events->mcMuonMotherId[j]!=431 && TMath::Abs(events->mcMuonMotherId[j])!=421 && TMath::Abs(events->mcMuonMotherId[j])!=411 && TMath::Abs(events->mcMuonMotherId[j])!=221 && TMath::Abs(events->mcMuonMotherId[j])!=113){
	//cout<<"for event "<<events->id<<", mother of status1 muon is: "<<events->mcMuonMotherId[j]<<endl;
	//}
      }
      if(TMath::Abs(events->mcMuonMotherId[j])==13 && !status1muonFromMuon) cout<<"mother of stable muon is muon but didn't work for event "<<events->id<<endl;
      if(TMath::Abs(events->mcMuonMotherId[j])==94 && !status1muonFromNeutralino) cout<<"mother of stable muon is neutralino but didn't work for event "<<events->id<<endl;
      if(TMath::Abs(events->mcMuonMotherId[j])==15 && !status1muonFromTau) cout<<"mother of stable muon is stau but didn't work for event "<<events->id<<endl;
    } //end of muon status is 1                                                                                                                                                            
  } //end of loop over mc muons  

  if(genMu0_index!=999) good_genMuons = 1;
  //cout<<"genMu0_index is: "<<genMu0_index<<endl;

}//end of staus

void findTreevalues_makehistos_Ntuples_allsamples::cosmicMC( StoppedHSCPMuonEvent* events, int& good_genMuons, UInt_t& genMu0_index, bool& status1muon){

  //check first to see if there is a status 1 muon in the event
  for (UInt_t j=0; j<events->mcMuon_N; j++) {
    //cout<<"looping over cosmic mcMuons: "<<j<<endl;
    if(events->mcMuonStatus[j]==1){
      //cout<<"cosmic mcMuon has status 1"<<endl;
      status1muon = true;
      genMu0_index = j; //in cosmic MC, only one status 1 muon generated in upper hemisphere
    }
  }

  if(genMu0_index!=999) good_genMuons = 1;
}//end of cosmicMC

void findTreevalues_makehistos_Ntuples_allsamples::genMuMatch(StoppedHSCPMuonEvent* events, UInt_t (&genMuMatched_DSA_index)[15], UInt_t (&genMuMatched_mu_index)[15], UInt_t (&genMuMatched_SA_index)[15], UInt_t (&genMuMatched_SAUpdatedAtVtx_index)[15], UInt_t (&genMuMatched_RSA_index)[15], UInt_t (&genMuMatched_cosmic_index)[15]){

  for (UInt_t j=0; j<events->mcMuon_N; j++) {
    for (UInt_t k=0; k<events->mu_DisplacedStandAlone_N; k++) {
      if(events->mcMuonGenIndex[j] == events->muDisplacedStandAloneTrackGenParticleIndex[k]) genMuMatched_DSA_index[k] = j;
    }
    for (UInt_t k=0; k<events->mu_N; k++) {
      if(events->mcMuonGenIndex[j] == events->muSAgenParticleIndex[k]) genMuMatched_mu_index[k] = j;
    }
    for (UInt_t k=0; k<events->mu_StandAlone_N; k++) {
      if(events->mcMuonGenIndex[j] == events->muStandAloneTrackGenParticleIndex[k]) genMuMatched_SA_index[k] = j;
    }
    for (UInt_t k=0; k<events->mu_StandAloneUpdatedAtVtx_N; k++) {
      if(events->mcMuonGenIndex[j] == events->muStandAloneTrackUpdatedAtVtxGenParticleIndex[k]) genMuMatched_SAUpdatedAtVtx_index[k] = j;
    }
    for (UInt_t k=0; k<events->mu_RefittedStandAlone_N; k++) {
      if(events->mcMuonGenIndex[j] == events->muRefittedStandAloneTrackGenParticleIndex[k]) genMuMatched_RSA_index[k] = j;
    }
    for (UInt_t k=0; k<events->mu_CosmicTrack_N; k++) {
      if(events->mcMuonGenIndex[j] == events->muCosmicTrackGenParticleIndex[k]) genMuMatched_cosmic_index[k] = j;
    }
  }

}

void findTreevalues_makehistos_Ntuples_allsamples::simTracks( StoppedHSCPMuonEvent* events, UInt_t& simTrack0_index){
  for (UInt_t j=0; j<events->simTrack_N; j++) {
    if(TMath::Abs(events->simTrackPdgId[j])==13){
      simTrack0_index = j;
      break;
    }//end of if sim tracks correspond to gen muon
  }//end of loop over sim tracks
}//end of simTracks

void findTreevalues_makehistos_Ntuples_allsamples::doublyChargedHiggs( StoppedHSCPMuonEvent* events,
								       bool (&status2H_)[15], int& good_genH, 
								       UInt_t& genH0_index, UInt_t& genH1_index, UInt_t& genHpos_index, UInt_t& genHneg_index,
								       Double_t& angle ){

  //check first to see if there is a status 1 muon in the event 
  for (UInt_t j=0; j<events->mcDoublyChargedHiggs_N; j++) {
    if(events->mcDoublyChargedHiggsStatus[j]==2){
      status2H_[j] = true;
      good_genH++;
      if(good_genH==1) genH0_index = j;
      if(good_genH==2) genH1_index = j;
    }
  }

  //if(good_genH!=2) cout<<"for event "<<events->id<<", have "<<good_genH<<" good generator doubly charged higgs"<<endl;

  // 3D angle between doubly charged higgs
  if(good_genH==2 && events->mcDoublyChargedHiggsP[genH0_index]!=0. && events->mcDoublyChargedHiggsP[genH1_index]!=0.){
    angle = TMath::ACos(( (events->mcDoublyChargedHiggsPx[genH0_index])*(events->mcDoublyChargedHiggsPx[genH1_index]) + (events->mcDoublyChargedHiggsPy[genH0_index])*(events->mcDoublyChargedHiggsPy[genH1_index]) + (events->mcDoublyChargedHiggsPz[genH0_index])*(events->mcDoublyChargedHiggsPz[genH1_index]))/((events->mcDoublyChargedHiggsP[genH0_index])*(events->mcDoublyChargedHiggsP[genH1_index])));
  }

  //one in positive, one negative?
  if(events->mcDoublyChargedHiggsCharge[genH0_index] == -2 && events->mcDoublyChargedHiggsCharge[genH1_index] == 2){
    genHpos_index = genH1_index;
    genHneg_index = genH0_index;
  }
  if(events->mcDoublyChargedHiggsCharge[genH1_index] == -2 && events->mcDoublyChargedHiggsCharge[genH0_index] == 2){
    genHpos_index = genH0_index;
    genHneg_index = genH1_index;
  }

}//end of doublyChargedHiggs

void findTreevalues_makehistos_Ntuples_allsamples::tauPrime( StoppedHSCPMuonEvent* events,
								       bool (&status2H_)[15], int& good_genH, 
								       UInt_t& genH0_index, UInt_t& genH1_index, UInt_t& genHpos_index, UInt_t& genHneg_index,
								       Double_t& angle ){

  //check first to see if there is a status 1 muon in the event 
  for (UInt_t j=0; j<events->mcTauPrime_N; j++) {
    if(events->mcTauPrimeStatus[j]==1){
      status2H_[j] = true;
      good_genH++;
      if(good_genH==1) genH0_index = j;
      if(good_genH==2) genH1_index = j;
      //cout<<"genH0 index is: "<<genH0_index<<", genH1_index is: "<<genH1_index<<endl;
    }
  }

  //if(good_genH!=2) cout<<"for event "<<events->id<<", have "<<good_genH<<" good generator tauPrimes"<<endl;

  // 3D angle between doubly charged higgs
  if(good_genH==2 && events->mcTauPrimeP[genH0_index]!=0. && events->mcTauPrimeP[genH1_index]!=0.){
    angle = TMath::ACos(( (events->mcTauPrimePx[genH0_index])*(events->mcTauPrimePx[genH1_index]) + (events->mcTauPrimePy[genH0_index])*(events->mcTauPrimePy[genH1_index]) + (events->mcTauPrimePz[genH0_index])*(events->mcTauPrimePz[genH1_index]))/((events->mcTauPrimeP[genH0_index])*(events->mcTauPrimeP[genH1_index])));
  }

  //one in positive, one negative?
  if(events->mcTauPrimeCharge[genH0_index] == -1 && events->mcTauPrimeCharge[genH1_index] == 1){
    genHpos_index = genH1_index;
    genHneg_index = genH0_index;
    //cout<<"genHpos index is: "<<genHpos_index<<", genHneg_index is: "<<genHneg_index<<endl;
  }
  if(events->mcTauPrimeCharge[genH1_index] == -1 && events->mcTauPrimeCharge[genH0_index] == 1){
    genHpos_index = genH0_index;
    genHneg_index = genH1_index;
    //cout<<"genHpos index is: "<<genHpos_index<<", genHneg_index is: "<<genHneg_index<<endl;
  }

}//end of tauPrime()

double findTreevalues_makehistos_Ntuples_allsamples::eventWeightTauPrime( StoppedHSCPMuonEvent* events, UInt_t& genHpos_index,  UInt_t& genHneg_index, double(&eventweightPt)[500][500]){
//double findTreevalues_makehistos_Ntuples_allsamples::eventWeightTauPrime( StoppedHSCPMuonEvent* events, UInt_t& genHpos_index,  UInt_t& genHneg_index, double(&eventweightPt)[160][160]){
  double eventWeight = 1.0;
  const int NumBins = 500;
  //const int NumBins = 160;
  double binWidth = 10;
  //double binWidth = 0.1;

  for(int i=0;i<NumBins; i++){
    for(int j=0;j<NumBins; j++){
      if(events->mcTauPrimePt[genHpos_index] > (binWidth*i) && events->mcTauPrimePt[genHpos_index] < (binWidth*(i+1)) ){
	if(events->mcTauPrimePt[genHneg_index] > (binWidth*j) && events->mcTauPrimePt[genHneg_index] < (binWidth*(j+1)) ){
	  //if(events->mcTauPrimeEta[genHpos_index] > (-8+binWidth*i) && events->mcTauPrimeEta[genHpos_index] < (-8+binWidth*(i+1)) ){
	  //if(events->mcTauPrimeEta[genHneg_index] > (-8+binWidth*j) && events->mcTauPrimeEta[genHneg_index] < (-8+binWidth*(j+1)) ){
	  eventWeight = eventweightPt[i][j];
	  //cout<<"event weight of "<<eventWeight<<" is being set"<<endl;
	}
      }
      //cout<<"eventweight["<<i<<"] is: "<<eventweightPt[i]<<endl;
    }
  }

  //cout<<"TauPrimePt is: "<<events->mcTauPrimePt[genHpos_index]<<", eventWeight is: "<<eventWeight<<endl;

  return eventWeight;
}//end of eventWeightTauPrime

void findTreevalues_makehistos_Ntuples_allsamples::stop_counts( StoppedHSCPMuonEvent* events, bool& WFromTop, bool& status1muon, bool& status1muonFromMuon, bool& status1muonFromW ){
  if( (doGenMuCut && events->mcTop_N>0) || (!doGenMuCut)){
    pass_Ntops_cut++;
    if( (doGenMuCut && events->mcStop_N>0) || (!doGenMuCut)){
      pass_Nstops_cut++;
      if( (doGenMuCut && WFromTop)  || (!doGenMuCut)){
	pass_WFromTop_cut++;
	if( (doGenMuCut && events->mcMuon_N>0) || (!doGenMuCut)){
	  pass_muon_cut++;
	  if( (doGenMuCut && status1muon) || (!doGenMuCut)){
	    pass_status1muon_cut++;
	    if( (doGenMuCut && (status1muonFromMuon || status1muonFromW)) || (!doGenMuCut)){
	      pass_generatorMuon_cut++;
	    }
	  }
	}
      }
    }
  }
}//end of stop_counts

 void findTreevalues_makehistos_Ntuples_allsamples::gluino_counts( StoppedHSCPMuonEvent* events, bool& status1muon, bool& status1muonFromW, bool& status1muonFromTau, bool& status1muonFromMuon, bool& status1muonFromBbaryon, bool& status1muonFromCbaryon, bool& status1muonFromSbaryon, bool& status1muonFromBmeson, bool& status1muonFromCmeson, bool& status1muonFromJPsi, bool& status1muonFromLightMeson ){
  if( (doGenMuCut && events->mcGluino_N>0) || (!doGenMuCut)){
    pass_Ngluinos_cut++;
    if( (doGenMuCut && events->mcMuon_N>0) || (!doGenMuCut)){
      pass_muon_cut++;
      if( (doGenMuCut && status1muon) || (!doGenMuCut)){
	pass_status1muon_cut++;

	if( (doGenMuCut && status1muonFromW) || (!doGenMuCut)) pass_status1muonFromW_cut++;
	else if( (doGenMuCut && status1muonFromTau) || (!doGenMuCut)) pass_status1muonFromTau_cut++;
	else if( (doGenMuCut && status1muonFromMuon) || (!doGenMuCut)) pass_status1muonFromMuon_cut++;
	else if( (doGenMuCut && status1muonFromBbaryon) || (!doGenMuCut)) pass_status1muonFromBbaryon_cut++;
	else if( (doGenMuCut && status1muonFromCbaryon) || (!doGenMuCut)) pass_status1muonFromCbaryon_cut++;
	else if( (doGenMuCut && status1muonFromSbaryon) || (!doGenMuCut)) pass_status1muonFromSbaryon_cut++;
	else if( (doGenMuCut && status1muonFromBmeson) || (!doGenMuCut)) pass_status1muonFromBmeson_cut++;
	else if( (doGenMuCut && status1muonFromJPsi) || (!doGenMuCut)) pass_status1muonFromJPsi_cut++;
	else if( (doGenMuCut && status1muonFromCmeson) || (!doGenMuCut)) pass_status1muonFromCmeson_cut++;
	else if( (doGenMuCut && status1muonFromLightMeson) || (!doGenMuCut)) pass_status1muonFromLightMeson_cut++;

      }
    }
  }
}//end of gluino_counts

void findTreevalues_makehistos_Ntuples_allsamples::mchamp_counts( StoppedHSCPMuonEvent* events, int& good_genPosMuons, int& good_genNegMuons, UInt_t& genPosMu0_index,  UInt_t& genPosMu1_index, UInt_t& genNegMu0_index,  UInt_t& genNegMu1_index){
  if( (doGenMuCut && events->mcTauPrime_N>0) || (!doGenMuCut)){
    pass_Nmchamps_cut++;
    if( (doGenMuCut && events->mcMuon_N>0) || (!doGenMuCut)){
      //if( (doGenMuCut && events->mcMuon_N>1) || (!doGenMuCut)){                                                                                    
      pass_muon_cut++;
      //if( (doGenMuCut && status1muon) || (!doGenMuCut)){                                                                                           
      pass_status1muon_cut++;
      if( (doGenMuCut && (good_genPosMuons==2 || good_genNegMuons==2)) || (!doGenMuCut)){
	if( (doGenMuCut && ( (good_genPosMuons==2 && events->mcMuonCharge[genPosMu0_index]==events->mcMuonCharge[genPosMu1_index]) || (good_genNegMuons==2 && events->mcMuonCharge[genNegMu0_index]==events->mcMuonCharge[genNegMu1_index]) )) || (!doGenMuCut)){
	  pass_generatorMuon_cut++;
	}
      }
    }
  }
}//end of mchamp_counts

void findTreevalues_makehistos_Ntuples_allsamples::stau_counts( StoppedHSCPMuonEvent* events, bool& tauFromStau, bool& status1muon, bool& status1muonFromTau ){
  if( (doGenMuCut && events->mcStau_N>0) || (!doGenMuCut)){
    pass_Nstaus_cut++;
    if( (doGenMuCut && tauFromStau) || (!doGenMuCut)){
      pass_tauFromStau_cut++;
      if( (doGenMuCut && events->mcMuon_N>0) || (!doGenMuCut)){
	pass_muon_cut++;
	if( (doGenMuCut && status1muon) || (!doGenMuCut)){
	  pass_status1muon_cut++;
	  if( (doGenMuCut && status1muonFromTau) || (!doGenMuCut)){
	    pass_generatorMuon_cut++;
	  }
	}
      }
    }
  }
}//end of stau_counts

void findTreevalues_makehistos_Ntuples_allsamples::cosmicMC_counts( StoppedHSCPMuonEvent* events, bool& status1muon ){
  if( (doGenMuCut && events->mcMuon_N>0) || (!doGenMuCut)){
    pass_muon_cut++;
    if( (doGenMuCut && status1muon) || (!doGenMuCut)){
      pass_status1muon_cut++;
      pass_generatorMuon_cut++;
    }
  }
}//end of cosmicMC_counts

//match stage 1 stops to stopped particles
bool findTreevalues_makehistos_Ntuples_allsamples::stopStoppedParticleMatched(StoppedHSCPMuonEvent* events, UInt_t& genStop_index) {
  double minDeltaR=999;

  //loop over stopped particles
  for (UInt_t j=0; j<events->mcStoppedParticle_N; j++) {
    double stoppedParticle_eta = eta(events->mcStoppedParticleX[j],events->mcStoppedParticleY[j],
				     events->mcStoppedParticleZ[j],events->mcStoppedParticleTime[j]);
    
    // Calculate deltaR between this stopped particle and the stop
    double dR=deltaR(events->mcStopEta[genStop_index],events->mcStopPhi[genStop_index],stoppedParticle_eta,events->mcStoppedParticlePhi[j]);
    //std::cout<<"stop eta is: "<<events->mcStopEta[genStop_index]<<", stop phi is: "<<events->mcStopPhi[genStop_index]<<std::endl;
    //std::cout<<"stopped particle eta is: "<<stoppedParticle_eta<<", stopped particle phi is: "<<events->mcStoppedParticlePhi[j]<<", stopped particle index is: "<<j<<std::endl;
    //std::cout<<"dR is: "<<dR<<std::endl;
    
    if (dR<minDeltaR) {
      minDeltaR = dR;
      //std::cout<<"new min dR is: "<<minDeltaR<<std::endl;
    }    
  }//end of loop over stopped particles

  if (minDeltaR<1.0) return true;
  else return false;

}

//match stage 1 gluinos to stopped particles
bool findTreevalues_makehistos_Ntuples_allsamples::gluinoStoppedParticleMatched(StoppedHSCPMuonEvent* events, UInt_t& genGluino_index) {
  double minDeltaR=999;

  //loop over stopped particles
  for (UInt_t j=0; j<events->mcStoppedParticle_N; j++) {
    double stoppedParticle_eta = eta(events->mcStoppedParticleX[j],events->mcStoppedParticleY[j],
				     events->mcStoppedParticleZ[j],events->mcStoppedParticleTime[j]);
    
    // Calculate deltaR between this stopped particle and the gluino
    double dR=deltaR(events->mcGluinoEta[genGluino_index],events->mcGluinoPhi[genGluino_index],stoppedParticle_eta,events->mcStoppedParticlePhi[j]);
    std::cout<<"gluino eta is: "<<events->mcGluinoEta[genGluino_index]<<", gluino phi is: "<<events->mcGluinoPhi[genGluino_index]<<std::endl;
    std::cout<<"stopped particle eta is: "<<stoppedParticle_eta<<", stopped particle phi is: "<<events->mcStoppedParticlePhi[j]<<", stopped particle index is: "<<j<<std::endl;
    std::cout<<"dR is: "<<dR<<std::endl;
    
    if (dR<minDeltaR) {
      minDeltaR = dR;
      std::cout<<"new min dR is: "<<minDeltaR<<std::endl;
    }    
  }//end of loop over stopped particles

  if (minDeltaR<1.0) return true;
  else return false;

}

//match stage 1 mchamps to stopped particles
bool findTreevalues_makehistos_Ntuples_allsamples::tauprimeStoppedParticleMatched(StoppedHSCPMuonEvent* events, UInt_t& genTauPrime_index) {
  double minDeltaR=999;

  //loop over stopped particles
  for (UInt_t j=0; j<events->mcStoppedParticle_N; j++) {
    double stoppedParticle_eta = eta(events->mcStoppedParticleX[j],events->mcStoppedParticleY[j],
				     events->mcStoppedParticleZ[j],events->mcStoppedParticleTime[j]);
    
    // Calculate deltaR between this stopped particle and the tau prime
    double dR=deltaR(events->mcTauPrimeEta[genTauPrime_index],events->mcTauPrimePhi[genTauPrime_index],stoppedParticle_eta,events->mcStoppedParticlePhi[j]);
    std::cout<<"mchamp eta is: "<<events->mcTauPrimeEta[genTauPrime_index]<<", mchamp phi is: "<<events->mcTauPrimePhi[genTauPrime_index]<<std::endl;
    std::cout<<"stopped particle eta is: "<<stoppedParticle_eta<<", stopped particle phi is: "<<events->mcStoppedParticlePhi[j]<<", stopped particle index is: "<<j<<std::endl;
    std::cout<<"dR is: "<<dR<<std::endl;
    
    if (dR<minDeltaR) {
      minDeltaR = dR;
      std::cout<<"new min dR is: "<<minDeltaR<<std::endl;
    }    
  }//end of loop over stopped particles

  if (minDeltaR<0.1) return true;
  else return false;

}

//match stage 1 staus to stopped particles
bool findTreevalues_makehistos_Ntuples_allsamples::stauStoppedParticleMatched(StoppedHSCPMuonEvent* events, UInt_t& genStau_index) {
  double minDeltaR=999;

  //loop over stopped particles
  for (UInt_t j=0; j<events->mcStoppedParticle_N; j++) {
    double stoppedParticle_eta = eta(events->mcStoppedParticleX[j],events->mcStoppedParticleY[j],
				     events->mcStoppedParticleZ[j],events->mcStoppedParticleTime[j]);
    
    // Calculate deltaR between this stopped particle and the stau
    double dR=deltaR(events->mcStauEta[genStau_index],events->mcStauPhi[genStau_index],stoppedParticle_eta,events->mcStoppedParticlePhi[j]);
    //std::cout<<"stau eta is: "<<events->mcStauEta[genStau_index]<<", stau phi is: "<<events->mcStauPhi[genStau_index]<<std::endl;
    //std::cout<<"stopped particle eta is: "<<stoppedParticle_eta<<", stopped particle phi is: "<<events->mcStoppedParticlePhi[j]<<", stopped particle index is: "<<j<<std::endl;
    //std::cout<<"dR is: "<<dR<<std::endl;
    
    if (dR<minDeltaR) {
      minDeltaR = dR;
      //std::cout<<"new min dR is: "<<minDeltaR<<std::endl;
    }    
  }//end of loop over stopped particles

  if (minDeltaR<0.1) return true;
  else return false;

}

void findTreevalues_makehistos_Ntuples_allsamples::pickStoppedParticle( StoppedHSCPMuonEvent* events, UInt_t& stopped_index){  
  if(events->mcStoppedParticle_N==0){
    stopped_index = 999;
  }//end of if 0 stopped particles
  else if(events->mcStoppedParticle_N==1){
    stopped_index = 0;
  }//end of if 1 stopped particle
  else if(events->mcStoppedParticle_N==2){
    for (UInt_t j=0; j<events->mcStoppedParticle_N; j++) {
      //sufficient for mchamps to match pdgids, but not the case for stops or gluinos - should match vertex to r-hadron
      //double x = events->mcStoppedParticleX[j]/10.;
      //double y = events->mcStoppedParticleY[j]/10.;
      //double z = events->mcStoppedParticleZ[j]/10;
      if(events->mcTauPrime_N==1){
	if(events->mcStoppedParticleId[j] == events->mcTauPrimeId[0]){
	  stopped_index = j;
	}
      }
      else cout<<"There are "<<events->mcTauPrime_N<<" mchamps in the event!!!"<<endl;
    }
  }//end of if 2 stopped particles
  else{
    cout<<events->mcStoppedParticle_N<<" stopped particles!!!"<<endl;
  }//end of if 3 or more stopped particles
  //cout<<"stopped index is: "<<stopped_index<<endl;
}//end of pickStoppedParticle()

void findTreevalues_makehistos_Ntuples_allsamples::StoppedParticles( StoppedHSCPMuonEvent* events, double& eventweightTauPrime, UInt_t& stoppedPos_index, UInt_t& stoppedNeg_index, UInt_t& stopped_index, int& n_stoppedInDetector){  
  // Identify which detector region the particles stopped in. For ME and MB, this definition includes                                                                            
  // the entire muon system, not just the yokes.                                                                                                                                 

  if(events->mcStoppedParticle_N==2){
    if (TMath::Abs(events->mcStoppedParticleCharge[0])==TMath::Abs(events->mcStoppedParticleCharge[1])){
      if (events->mcStoppedParticleCharge[0]!=events->mcStoppedParticleCharge[1]){
	for (UInt_t j=0; j<events->mcStoppedParticle_N; j++) {
	  if(events->mcStoppedParticleCharge[j]>0) stoppedPos_index = j;
	  if(events->mcStoppedParticleCharge[j]<0) stoppedNeg_index = j;
	}//end of loop over stopped particles
      }//end of if 2 charges are not the same (mchamps, ppstaus, could be for gmstaus)
    }//end of if abs of 2 charges are the same
    
    else {       //what about stops, with charge of 1 and 2?
      //cout<<"charge of stopped particle 0 is: "<<events->mcStoppedParticleCharge[0]<<", charge of stopped particle 1 is: "<<events->mcStoppedParticleCharge[1]<<endl;
    }    
  }//end of if 2 stopped particles

  //if(stopped_index!=999){
  for (UInt_t j=0; j<events->mcStoppedParticle_N; j++) {
    //cout<<"stopped particle is: "<<events->mcStoppedParticleId[stopped_index]<<endl;
    //double r = events->mcStoppedParticleR[stopped_index]/10.0;
    //double z = events->mcStoppedParticleZ[stopped_index]/10.0;
    //double particle_eta = eta(events->mcStoppedParticleX[stopped_index],events->mcStoppedParticleY[stopped_index],
    //			      events->mcStoppedParticleZ[stopped_index],events->mcStoppedParticleTime[stopped_index]);

    double r = events->mcStoppedParticleR[j]/10.0;
    double z = events->mcStoppedParticleZ[j]/10.0;
    double particle_eta = eta(events->mcStoppedParticleX[j],events->mcStoppedParticleY[j],
    			      events->mcStoppedParticleZ[j],events->mcStoppedParticleTime[j]);
    
    if (r < 131.0 && fabs(particle_eta) <= 2.5 && fabs(z) < 300.0) tracker_count_+=eventweightTauPrime;
    else if (r>=131.0 && r<184.0 && fabs(z)<376.0 && fabs(particle_eta)<1.479) eb_count_+=eventweightTauPrime;
    else if (fabs(z)<376.0 && fabs(z) >= 300.0 && fabs(particle_eta)>=1.479 && fabs(particle_eta)<3.0) ee_count_+=eventweightTauPrime;
    else if (r>=184.0 && r<295.0 && fabs(particle_eta)<1.3 && fabs(z)<500.0) hb_count_+=eventweightTauPrime;
    else if (fabs(z)<560.0 && fabs(z)>=376.0 && fabs(particle_eta)>=1.3 && fabs(particle_eta)<3.0) he_count_+=eventweightTauPrime;
    else if (r>=295.0 && r<728.5 && fabs(z)<675.0)  mb_count_+=eventweightTauPrime;
    else if (r>=517.3 && r<728.5 && fabs(z)>=675.0 && fabs(z)<1080.0) me_count_+=eventweightTauPrime; // ME-top                                                                                     
    else if (r<517.3 && fabs(particle_eta)<3.0 && fabs(z)>=560.0 && fabs(z)<1080.0) me_count_+=eventweightTauPrime; // ME-bottom                                                                    
    else if (r<728.5 && fabs(z)<1080.0) { // other regions?                                                                                                                      
      other_detector_count_+=eventweightTauPrime;
      //dumpFile_ << r << "\t" << z << "\t" << particle_eta << std::endl;                                                                                                        
    }
    
    if (r >= 728.5 || fabs(z) > 1080) cavern_count_+=eventweightTauPrime;
    else{
      detector_count_+=eventweightTauPrime;
      n_stoppedInDetector++;
    }
  }//end of stopped_index!=999
}//end of StoppedParticles()

void findTreevalues_makehistos_Ntuples_allsamples::StoppingRegionAcceptance( StoppedHSCPMuonEvent* events, double& eventweightTauPrime, UInt_t& stopped_index ){
  // Identify which detector region the particles stopped in. For ME and MB, this definition includes                                                                            
  // the entire muon system, not just the yokes. 
  //if they also pass some preselection

  if(stopped_index!=999){
    double r = events->mcStoppedParticleR[stopped_index]/10.0;
    double z = events->mcStoppedParticleZ[stopped_index]/10.0;
    double particle_eta = eta(events->mcStoppedParticleX[stopped_index],events->mcStoppedParticleY[stopped_index],
			      events->mcStoppedParticleZ[stopped_index],events->mcStoppedParticleTime[stopped_index]);
      
    if (r < 131.0 && fabs(particle_eta) <= 2.5 && fabs(z) < 300.0) tracker_AccCount_+=eventweightTauPrime;
    else if (r>=131.0 && r<184.0 && fabs(z)<376.0 && fabs(particle_eta)<1.479) eb_AccCount_+=eventweightTauPrime;
    else if (fabs(z)<376.0 && fabs(z) >= 300.0 && fabs(particle_eta)>=1.479 && fabs(particle_eta)<3.0) ee_AccCount_+=eventweightTauPrime;
    else if (r>=184.0 && r<295.0 && fabs(particle_eta)<1.3 && fabs(z)<500.0) hb_AccCount_+=eventweightTauPrime;
    else if (fabs(z)<560.0 && fabs(z)>=376.0 && fabs(particle_eta)>=1.3 && fabs(particle_eta)<3.0) he_AccCount_+=eventweightTauPrime;
    else if (r>=295.0 && r<728.5 && fabs(z)<675.0) mb_AccCount_+=eventweightTauPrime;
    else if (r>=517.3 && r<728.5 && fabs(z)>=675.0 && fabs(z)<1080.0) me_AccCount_+=eventweightTauPrime; // ME-top                                                                                     
    else if (r<517.3 && fabs(particle_eta)<3.0 && fabs(z)>=560.0 && fabs(z)<1080.0) me_AccCount_+=eventweightTauPrime; // ME-bottom                                                                    
    else if (r<728.5 && fabs(z)<1080.0) { // other regions?                                                                                                                      
      other_detector_AccCount_+=eventweightTauPrime;
      //dumpFile_ << r << "\t" << z << "\t" << particle_eta << std::endl;                                                                                                        
    }
    
    if (r >= 728.5 || fabs(z) > 1080) cavern_AccCount_+=eventweightTauPrime;
    else detector_AccCount_+=eventweightTauPrime;
  }//end stopped_index!=999
}//end of StoppingRegionAcceptance()


bool findTreevalues_makehistos_Ntuples_allsamples::genMuonMatched( StoppedHSCPMuonEvent* events ){
  //for (UInt_t j=0; j<events->mu_DisplacedStandAlone_N; j++) {
  //if(events->muDisplacedStandAloneTrackGenParticleIndex[j] >= 0) return(true);
  //}
  if(events->muDisplacedStandAloneTrackGenParticleIndex[0] >= 0) return(true);
  return(false);
}//end of genMuonMatched()

bool findTreevalues_makehistos_Ntuples_allsamples::multipleMuons_PtCut( StoppedHSCPMuonEvent* events ){
  if(events->mu_DisplacedStandAlone_N>=2){
    if( events->muDisplacedStandAlonePt[0]>30. && events->muDisplacedStandAlonePt[1]>20. ) return(true);
  }// end of at least 2 standalone muons
  return(false);
}//end of multipleMuons_PtCut()

bool findTreevalues_makehistos_Ntuples_allsamples::diMuMass_Cut( StoppedHSCPMuonEvent* events ){
  for (UInt_t j=0; j<events->diMuMass.size(); j++) {
    if(events->diMuMass[j] >70. && events->diMuMass[j]<110.) return(true);
  }
  return(false);
}//end of diMuMass_Cut()

int findTreevalues_makehistos_Ntuples_allsamples::Rpc_Bx_Pattern( StoppedHSCPMuonEvent* events, UInt_t& j){

  bool all_bx_0 = true;
  bool all_bx_positive = true;
  bool all_bx_negative = true;
  bool all_bx_positiveOr0 = true;
  bool all_bx_negativeOr0 = true;
  bool all_bx_constant = true;
  bool all_bx_increasing = true;
  bool all_bx_decreasing = true;
  if(events->muDisplacedStandAloneTrackRpcHitZ.at(j).size()==0){
    all_bx_0 = false;
    all_bx_positive = false;
    all_bx_negative = false;
    all_bx_positiveOr0 = false;
    all_bx_negativeOr0 = false;
    all_bx_constant = false;
    all_bx_increasing = false;
    all_bx_decreasing = false;
  }

  //if(events->muDisplacedStandAloneTrackRpcHitZ.at(j).size()>0) events_1muon_pass_other_cut_with_rpcs++;
  //loop over Rpc hits
  for (UInt_t k=0; k<events->muDisplacedStandAloneTrackRpcHitZ.at(j).size(); k++) {
    //cout<<"  , for Rpc hit number "<<k<<", Z is: "<<events->muDisplacedStandAloneTrackRpcHitZ.at(j).at(k)<<", Rho is: "<<events->muDisplacedStandAloneTrackRpcHitRho.at(j).at(k)<<", phi is: "<<events->muDisplacedStandAloneTrackRpcHitPhi.at(j).at(k)<<", region is: "<<events->muDisplacedStandAloneTrackRpcHitRegion.at(j).at(k)<<", Bx is: "<<events->muDisplacedStandAloneTrackRpcHitBx.at(j).at(k)<<endl;
    if(events->muDisplacedStandAloneTrackRpcHitBx.at(j).at(k) != 0) all_bx_0 = false;
    if(events->muDisplacedStandAloneTrackRpcHitBx.at(j).at(k) <= 0) all_bx_positive = false;
    if(events->muDisplacedStandAloneTrackRpcHitBx.at(j).at(k) >= 0) all_bx_negative = false;
    if(events->muDisplacedStandAloneTrackRpcHitBx.at(j).at(k) < 0) all_bx_positiveOr0 = false;
    if(events->muDisplacedStandAloneTrackRpcHitBx.at(j).at(k) > 0) all_bx_negativeOr0 = false;
    UInt_t l=k+1;
    if(l<events->muDisplacedStandAloneTrackRpcHitZ.at(j).size()){
      if(events->muDisplacedStandAloneTrackRpcHitBx.at(j).at(l) != events->muDisplacedStandAloneTrackRpcHitBx.at(j).at(k)) all_bx_constant = false;
      if(events->muDisplacedStandAloneTrackRpcHitBx.at(j).at(l) < events->muDisplacedStandAloneTrackRpcHitBx.at(j).at(k)) all_bx_increasing = false;
      if(events->muDisplacedStandAloneTrackRpcHitBx.at(j).at(l) > events->muDisplacedStandAloneTrackRpcHitBx.at(j).at(k)) all_bx_decreasing = false;
      //cout<<"events->muDisplacedStandAloneTrackRpcHitBx.at(j).at(l) is: "<<events->muDisplacedStandAloneTrackRpcHitBx.at(j).at(l)<<", events->muDisplacedStandAloneTrackRpcHitBx.at(j).at(k) is: "<<events->muDisplacedStandAloneTrackRpcHitBx.at(j).at(k)<<", all_bx_increasing is: "<<all_bx_increasing<<", all_bx_decreasing is: "<<all_bx_decreasing<<endl;
    }
  }
  if(all_bx_constant) {
    all_bx_increasing = false;
    all_bx_decreasing = false;
  }

  //cout<<"all_bx_0 is: "<<all_bx_0<<endl;
  //cout<<"all_bx_positive is: "<<all_bx_positive<<endl;
  //cout<<"all_bx_negative is: "<<all_bx_negative<<endl;
  //cout<<"all_bx_positiveOr0 is: "<<all_bx_positiveOr0<<endl;
  //cout<<"all_bx_negativeOr0 is: "<<all_bx_negativeOr0<<endl;
  //cout<<"all_bx_constant is: "<<all_bx_constant<<endl;
  //cout<<"all_bx_increasing is: "<<all_bx_increasing<<endl;
  //cout<<"all_bx_decreasing is: "<<all_bx_decreasing<<endl;

  if(events->muDisplacedStandAloneTrackRpcHitZ.at(j).size()<=0) return(-1);
  if(all_bx_0 && all_bx_constant){
    return(0);
    //cout<<"0BX"<<endl;
  }
  if(all_bx_positive && all_bx_constant){
    return(1);
    //cout<<"positiveConstantBX"<<endl;
  }
  if(all_bx_positiveOr0 && all_bx_increasing){
    return(2);
    //cout<<"positiveOr0IncreasingBX"<<endl;
  }
  if(all_bx_positiveOr0 && all_bx_decreasing){
    return(3);
    //cout<<"positiveOr0DecreasingBX"<<endl;
  }
  if(all_bx_positiveOr0 && !all_bx_decreasing && !all_bx_increasing && !all_bx_constant){
    return(4);
    //cout<<"positiveOr0StrangeBX"<<endl;
  }
  if(all_bx_negative && all_bx_constant){
    return(5);
    //cout<<"negativeConstantBX"<<endl;
  }
  if(all_bx_negativeOr0 && all_bx_increasing){
    return(6);
    //cout<<"negativeOr0IncreasingBX"<<endl;
  }
  if(all_bx_negativeOr0 && all_bx_decreasing){
    return(7);
      //cout<<"negativeOr0DecreasingBX"<<endl;
  }
  if(all_bx_negativeOr0 && !all_bx_decreasing && !all_bx_increasing && !all_bx_constant){
    return(8);
    //cout<<"negativeOr0StrangeBX"<<endl;
  }
  return(-1);
}//end of Rpc_Bx_Pattern()

double findTreevalues_makehistos_Ntuples_allsamples::Rpc_Bx_Average( StoppedHSCPMuonEvent* events, UInt_t& upper_index, UInt_t& lower_index){

  double rpc_bx_average = 0.;

  //loop over Rpc hits for upper
  for (UInt_t k=0; k<events->muDisplacedStandAloneTrackRpcHitZ.at(upper_index).size(); k++) {
    //cout<<"  upper index: for Rpc hit number "<<k<<", Z is: "<<events->muDisplacedStandAloneTrackRpcHitZ.at(upper_index).at(k)<<", Rho is: "<<events->muDisplacedStandAloneTrackRpcHitRho.at(upper_index).at(k)<<", phi is: "<<events->muDisplacedStandAloneTrackRpcHitPhi.at(upper_index).at(k)<<", region is: "<<events->muDisplacedStandAloneTrackRpcHitRegion.at(upper_index).at(k)<<", Bx is: "<<events->muDisplacedStandAloneTrackRpcHitBx.at(upper_index).at(k)<<endl;
    rpc_bx_average += events->muDisplacedStandAloneTrackRpcHitBx.at(upper_index).at(k);
  }

  //loop over Rpc hits for lower
  for (UInt_t k=0; k<events->muDisplacedStandAloneTrackRpcHitZ.at(lower_index).size(); k++) {
    //cout<<"  lower index: for Rpc hit number "<<k<<", Z is: "<<events->muDisplacedStandAloneTrackRpcHitZ.at(lower_index).at(k)<<", Rho is: "<<events->muDisplacedStandAloneTrackRpcHitRho.at(lower_index).at(k)<<", phi is: "<<events->muDisplacedStandAloneTrackRpcHitPhi.at(lower_index).at(k)<<", region is: "<<events->muDisplacedStandAloneTrackRpcHitRegion.at(lower_index).at(k)<<", Bx is: "<<events->muDisplacedStandAloneTrackRpcHitBx.at(lower_index).at(k)<<endl;
    rpc_bx_average += events->muDisplacedStandAloneTrackRpcHitBx.at(lower_index).at(k);
  }

  int tot_num_rpc_hits = events->muDisplacedStandAloneTrackRpcHitZ.at(upper_index).size()+events->muDisplacedStandAloneTrackRpcHitZ.at(lower_index).size();
  if(tot_num_rpc_hits!=0) rpc_bx_average = 1.0*rpc_bx_average/tot_num_rpc_hits;
  else rpc_bx_average = -999;

  //cout<<"rpc_bx_average is: "<<rpc_bx_average<<endl;
  return rpc_bx_average;
}//end of Rpc_Bx_Average

double findTreevalues_makehistos_Ntuples_allsamples::Rpc_Bx_Average( StoppedHSCPMuonEvent* events, UInt_t& index){

  double rpc_bx_average = 0.;

  //loop over Rpc hits
  for (UInt_t k=0; k<events->muDisplacedStandAloneTrackRpcHitZ.at(index).size(); k++) {
    //cout<<"  , for Rpc hit number "<<k<<", Z is: "<<events->muDisplacedStandAloneTrackRpcHitZ.at(index).at(k)<<", Rho is: "<<events->muDisplacedStandAloneTrackRpcHitRho.at(index).at(k)<<", phi is: "<<events->muDisplacedStandAloneTrackRpcHitPhi.at(index).at(k)<<", region is: "<<events->muDisplacedStandAloneTrackRpcHitRegion.at(index).at(k)<<", Bx is: "<<events->muDisplacedStandAloneTrackRpcHitBx.at(index).at(k)<<endl;
    rpc_bx_average += events->muDisplacedStandAloneTrackRpcHitBx.at(index).at(k);
  }

  if(events->muDisplacedStandAloneTrackRpcHitZ.at(index).size()!=0) rpc_bx_average = 1.0*rpc_bx_average/events->muDisplacedStandAloneTrackRpcHitZ.at(index).size();
  else rpc_bx_average = -999;

  //cout<<"rpc_bx_average is: "<<rpc_bx_average<<endl;
  return rpc_bx_average;
}//end of Rpc_Bx_Average

double findTreevalues_makehistos_Ntuples_allsamples::dR_OppositeSeg( StoppedHSCPMuonEvent* events, UInt_t& mu_index, double& minPhi, double& minEta){
  // returns minimum dR segment (min dEta seg, min dPhi seg) - could be 3 different segments
  // if not matched to an opposite segment, returns 10
  double minDr=10;
  minPhi=10;
  minEta=10;

  double opposite_mu_eta = -1.*(events->muDisplacedStandAloneEta[mu_index]);
  double opposite_mu_phi = events->muDisplacedStandAlonePhi[mu_index] + TMath::Pi();

  //cout<<"there are "<<events->DTSegment_N<<" DT segments"<<endl;
  for (UInt_t j=0; j<events->DTSegment_N; j++) {
    //cout<<"  for segment "<<j<<", eta is: "<<events->DTSegEta[j]<<", phi is: "<<events->DTSegPhi[j]<<endl;
    double dEta = events->DTSegEta[j] - opposite_mu_eta;
    double dPhi = events->DTSegPhi[j] - opposite_mu_phi;
    while (dPhi > TMath::Pi()) dPhi -= 2*TMath::Pi();
    while (dPhi <= -TMath::Pi()) dPhi += 2*TMath::Pi();
    //cout<<"  dEta is: "<<dEta<<", dPhi is: "<<dPhi<<endl;

    //Find segment most opposite in eta
    //Require phi difference of 0.5 so it doesn't match to own segment
    if(fabs(dEta)<fabs(minEta) && fabs(dPhi)<(TMath::Pi()-0.5)) {
      minEta=dEta;
    }
    //Find segment most opposite in phi
    if(fabs(dPhi)<fabs(minPhi)) {
      minPhi=dPhi;
    }
    //Find segment most opposite in Eta-Phi
    double dR=sqrt(dEta*dEta+dPhi*dPhi);
    if(dR<minDr) minDr=dR;
  }//end of loop over DT segments

  //cout<<"there are "<<events->cscSeg_N<<" CSC segments"<<endl;
  for (UInt_t j=0; j<events->cscSeg_N; j++) {
    //cout<<"  for segment "<<j<<", eta is: "<<events->cscSegEta[j]<<", phi is: "<<events->cscSegPhi[j]<<endl;
    double dEta = events->cscSegEta[j] - opposite_mu_eta;
    double dPhi = events->cscSegPhi[j] - opposite_mu_phi;
    while (dPhi > TMath::Pi()) dPhi -= 2*TMath::Pi();
    while (dPhi <= -TMath::Pi()) dPhi += 2*TMath::Pi();
    //cout<<"  dEta is: "<<dEta<<", dPhi is: "<<dPhi<<endl;

    //Find segment most opposite in eta
    //Require phi difference of 0.5 so it doesn't match to own segment
    if(fabs(dEta)<fabs(minEta) && fabs(dPhi)<(TMath::Pi()-0.5)) {
      minEta=dEta;
    }
    //Find segment most opposite in phi
    if(fabs(dPhi)<fabs(minPhi)) {
      minPhi=dPhi;
    }
    //Find segment most opposite in Eta-Phi
    double dR=sqrt(dEta*dEta+dPhi*dPhi);
    if(dR<minDr) minDr=dR;
  }//end of loop over CSC segments

  return minDr;

}//end of dR_OppositeSeg


int findTreevalues_makehistos_Ntuples_allsamples::distanceBetweenStations( StoppedHSCPMuonEvent* events, UInt_t& mu_index, bool& refitted){
  //the "distance" between the outermost and innermost station with valid hits
  //stations are 1,2,3,and 4 
  //if station was 0, means that there were no valid hits for the track

  int distance_bet_stations = -1;

  if(refitted){
    if(events->muRefittedStandAloneTrackOutermostStationWithValidHits[mu_index]>0 && events->muRefittedStandAloneTrackInnermostStationWithValidHits[mu_index] >0) 
      distance_bet_stations = events->muRefittedStandAloneTrackOutermostStationWithValidHits[mu_index] - events->muRefittedStandAloneTrackInnermostStationWithValidHits[mu_index];
  }
  else{
    if(events->muDisplacedStandAloneTrackOutermostStationWithValidHits[mu_index]>0 && events->muDisplacedStandAloneTrackInnermostStationWithValidHits[mu_index] >0) 
      distance_bet_stations = events->muDisplacedStandAloneTrackOutermostStationWithValidHits[mu_index] - events->muDisplacedStandAloneTrackInnermostStationWithValidHits[mu_index];
  }

  return distance_bet_stations;

}//end of distanceBetweenStations

void findTreevalues_makehistos_Ntuples_allsamples::PreselectionSA( StoppedHSCPMuonEvent* events, int& n_passPreselection, UInt_t& presel0_index, UInt_t& presel1_index, UInt_t& presel2_index, UInt_t& presel3_index, UInt_t& PreNdsaCutValue_, float& PrePtCutValue_, Int_t& PreChaCutValue_, float& PreEtaCutValue_, Int_t& PreRpcCutValue_, Int_t& PreDtHitsCutValue_, float& PreInvBetaErrCutValue_, Int_t& PreCscHitsCutValue_, bool& pass_PreNdsa, bool& pass_Prept, bool& pass_Precha, bool& pass_Preeta, bool& pass_PreRPC, bool& pass_PreDtHits, bool& pass_PreInvBetaErr, bool& pass_PreCscHits){

  //cout<<"starting PreselectionSA"<<endl;

  //UInt_t a=0;
  n_passPreselection = 0;

  if( (doNdsaCut && events->mu_DisplacedStandAlone_N<PreNdsaCutValue_) || (!doNdsaCut) ){
    pass_PreNdsa = true;

    for (UInt_t j=0; j<events->mu_DisplacedStandAlone_N; j++) {
      
      //pt cut
      if ( (doPtCut && events->muDisplacedStandAlonePt[j]>PrePtCutValue_) || (!doPtCut) ){
	//if ( (doPtCut && events->muRefittedStandAlonePt[j]<PrePtCutValue_) || (!doPtCut) ){
	//if ( (doPtCut && events->muCosmicTrackPt[j]<PrePtCutValue_) || (!doPtCut) ){
	pass_Prept = true;
	//cout<<"passed pt cut"<<endl;
	
	//2 chamber cut
	//if( (doChaCut && (events->muDisplacedStandAloneTrackNDtChambersWithValidHits[j] + events->muDisplacedStandAloneTrackNCscChambersWithValidHits[j])>ChaCutValue_) || (!doChaCut)) {
	if( (doChaCut && events->muDisplacedStandAloneTrackNDtChambersWithValidHits[j]>PreChaCutValue_) || (!doChaCut)) {
	  pass_Precha = true;
	  //cout<<"passed chamber cut"<<endl;
	  
	  //eta cut
	  if ( (doEtaCut && TMath::Abs(events->muDisplacedStandAloneEta[j])<PreEtaCutValue_ ) || (!doEtaCut) ){
	    pass_Preeta = true;
	    //cout<<"passed eta cut"<<endl;
	    
	    //number of RPC hits cut
	    if( (doRpcCut && events->muDisplacedStandAloneTrackNValidRpcHits[j]>PreRpcCutValue_) || (!doRpcCut)){
	      //if( (doRpcCut && events->muDisplacedStandAloneTrackRpcHitZ.at(j).size()>PreRpcCutValue_) || (!doRpcCut)){
	      pass_PreRPC = true;
	      //cout<<"passed rpc cut"<<endl;
	      
	      //distance btw stations cut
	      //bool refitted = false;	    
	      //if( (doDisStCut && distanceBetweenStations(events, a, refitted)>PreDisStCutValue_) || (!doDisStCut)){
	      //pass_DisSt = true;
	      
	      //number of DT hits cut
	      if( (doDtHitsCut && events->muDisplacedStandAloneTrackDtTofNDof[j]>PreDtHitsCutValue_) || (!doDtHitsCut)){
		pass_PreDtHits = true;
		
		//inv beta error cut
		if( (doInvBetaErrCut && events->muDisplacedStandAloneTrackDtTofFreeInverseBetaErr[j]<PreInvBetaErrCutValue_) || (!doInvBetaErrCut)){
		  pass_PreInvBetaErr = true;
		  
		  //number of CSC hits cut
		  if( (doCscHitsCut && events->muDisplacedStandAloneTrackNValidCscHits[j]==PreCscHitsCutValue_) || (!doCscHitsCut)){
		    pass_PreCscHits = true;
		    
		    n_passPreselection++;
		    if(n_passPreselection == 1) presel0_index = j;
		    if(n_passPreselection == 2) presel1_index = j;
		    if(n_passPreselection == 3) presel2_index = j;
		    if(n_passPreselection == 4) presel3_index = j;
		    
		  }// end of csc hits
		}//end of inv beta err cut
	      }//end of dt hits
	      //} //end of dist btw stations
	    }//end of at least 1 RPC hit
	  }//end of eta[j]<1.0
	} //end of at least 2 DT/CSC chambers
      } //end of pt[j]>30
    }//end of loop over displaced SAs
  }//end of if <6 DSA tracks

  //cout<<"There are "<<n_passPreselection<<" displaced SA muons that pass the preselection"<<endl;
  //if(n_passPreselection>2) cout<<"There are "<<n_passPreselection<<" displaced SA muons that pass the preselection"<<endl;

}//end of PreselectionSA()

void findTreevalues_makehistos_Ntuples_allsamples::PreselectionSA_counts(bool& pass_PreNdsa, bool& pass_Prept, bool& pass_Precha, bool& pass_Preeta, bool& pass_PreRPC, bool& pass_PreDtHits, bool& pass_PreInvBetaErr, bool& pass_PreCscHits){

  //cout<<"starting PreselectionSA_counts"<<endl;

  //nDSA cut
  if(pass_PreNdsa){
    pass_PreNdsa_cut++;

    //pt cut
    if (pass_Prept){
      pass_Prept_cut++;
      //cout<<"passed pt cut"<<endl;
      
      //2 chamber cut
      if(pass_Precha){
	pass_Precha_cut++;
	//cout<<"passed chamber cut"<<endl;
	
	//eta cut
	if (pass_Preeta){
	  pass_Preeta_cut++;
	  //cout<<"passed eta cut"<<endl;
	  
	  //number of RPC hits cut
	  if( pass_PreRPC){
	    pass_PreRPC_cut++;
	    //cout<<"passed rpc cut"<<endl;
	    
	    //distance btw stations cut
	    //bool refitted = false;	    
	    //if(pass_DisSt){
	    //pass_DisSt_cut++;
	    
	    //number of DT hits cut
	    if(pass_PreDtHits){
	      pass_PreDtHits_cut++;
	      
	      //inverse beta error cut
	      if(pass_PreInvBetaErr){
		pass_PreInvBetaErr_cut++;
		
		//number of CSC hits cut
		if(pass_PreCscHits){
		  pass_PreCscHits_cut++;
		  
		}// end of csc hits
	      }// end of inv beta error cut
	    }//end of dt hits
	    //} //end of dist btw stations
	  }//end of at least 1 RPC hit
	}//end of eta[j]<1.0
      } //end of at least 2 DT/CSC chambers
    } //end of pt[j]>30
  }// end of dDSA< 6
}//end of PreselectionSA_counts()


void findTreevalues_makehistos_Ntuples_allsamples::HighestPtSA( StoppedHSCPMuonEvent* events, string& file_dataset, UInt_t& presel0_index, UInt_t& presel1_index, UInt_t& presel2_index, UInt_t& presel3_index, UInt_t& highestPt_index, float& PtCutValue_, Int_t& ChaCutValue_, float& EtaCutValue_, Int_t& RpcCutValue_, Int_t& DisStCutValue_, Int_t& DtHitsCutValue_, Int_t& CscHitsCutValue_, float& DtInvBetaCutValue_, float& TimeInOutCutValue_, float& TimeInOutErrCutValue_, float& OppEtaCutValue_, float& OppPhiCutValue_, float& DxyCutValue_, bool& pass_Upper, bool& pass_pt, bool& pass_cha, bool& pass_eta, bool& pass_RPC, bool& pass_DisSt, bool& pass_DtHits, bool& pass_CscHits, bool& pass_DtInvBeta, bool& pass_TimeInOut, bool& pass_TimeInOutErr, bool& pass_TofDir, bool& pass_Rpc_Bx, bool& pass_OppEta, bool& pass_OppPhi, bool& pass_Dxy){

  string file_dataset_=file_dataset.substr(0,4);
  //cout<<"file_dataset_ is: "<<file_dataset_<<endl;

  //cout<<"starting HighestPtSA"<<endl;
  double segment_dPhi = -999;
  double segment_dEta = -999;
  UInt_t a=0;
  //double segment_dR = dR_OppositeSeg(events, a, segment_dPhi, segment_dEta);

  UInt_t presel_index[4] = {presel0_index, presel1_index, presel2_index, presel3_index};

  int n_passHighestPt = 0;

  for (int i=0; i<4; i++) {
    if (presel_index[i]!=999){

      //upper hemisphere cut
      if( (doUpperCut && events->muDisplacedStandAlonePhi[presel_index[i]]>0.) || (!doUpperCut)){
	pass_Upper = true;
	//cout<<"passed upper cut"<<endl;
	
	//pt cut
	if ( (doPtCut && events->muDisplacedStandAlonePt[presel_index[i]]>PtCutValue_) || (!doPtCut) ){
	  //if ( (doPtCut && events->muRefittedStandAlonePt[presel_index[i]]<PtCutValue_) || (!doPtCut) ){
	  //if ( (doPtCut && events->muCosmicTrackPt[presel_index[i]]<PtCutValue_) || (!doPtCut) ){
	  pass_pt = true;
	  //cout<<"passed pt cut"<<endl;
	  
	  //2 chamber cut
	  //if( (doChaCut && (events->muDisplacedStandAloneTrackNDtChambersWithValidHits[presel_index[i]] + events->muDisplacedStandAloneTrackNCscChambersWithValidHits[presel_index[i]])>ChaCutValue_) || (!doChaCut)) {
	  if( (doChaCut && events->muDisplacedStandAloneTrackNDtChambersWithValidHits[presel_index[i]]>ChaCutValue_) || (!doChaCut)) {
	    pass_cha = true;
	    //cout<<"passed chamber cut"<<endl;
	    
	    //eta cut
	    if ( (doEtaCut && TMath::Abs(events->muDisplacedStandAloneEta[presel_index[i]])<EtaCutValue_ ) || (!doEtaCut) ){
	      pass_eta = true;
	      //cout<<"passed eta cut"<<endl;
	      
	      //number of RPC hits cut
	      if( (doRpcCut && events->muDisplacedStandAloneTrackNValidRpcHits[presel_index[i]]>RpcCutValue_) || (!doRpcCut)){
		pass_RPC = true;
		//cout<<"passed rpc cut"<<endl;
		
		//distance btw stations cut
		bool refitted = false;	    
		if( (doDisStCut && distanceBetweenStations(events, a, refitted)>DisStCutValue_) || (!doDisStCut)){
		  pass_DisSt = true;
		  
		  //number of DT hits cut
		  if( (doDtHitsCut && events->muDisplacedStandAloneTrackDtTofNDof[presel_index[i]]>DtHitsCutValue_) || (!doDtHitsCut)){
		    pass_DtHits = true;
		    
		    //number of CSC hits cut
		    if( (doCscHitsCut && events->muDisplacedStandAloneTrackNValidCscHits[presel_index[i]]==CscHitsCutValue_) || (!doCscHitsCut)){
		      pass_CscHits = true;
		      
		      //OppEta cut
		      if( (doOppEtaCut && !doCosEnrich && TMath::Abs(segment_dEta)>OppEtaCutValue_) ||
			  (doOppEtaCut && doCosEnrich && TMath::Abs(segment_dEta)<OppEtaCutValue_) ||
			  (!doOppEtaCut) ){
			pass_OppEta = true;
			
			//OppPhi cut
			if( (doOppPhiCut && !doCosEnrich && TMath::Abs(segment_dPhi)>OppPhiCutValue_) ||
			    (doOppPhiCut && doCosEnrich && TMath::Abs(segment_dPhi)<OppPhiCutValue_) ||
			    (!doOppPhiCut)){
			  pass_OppPhi = true;
			  
			  //RPC Bx pattern cut
			  //if( (doRpcBxCut && !doCosEnrich && (Rpc_Bx_Pattern(events, presel_index[i])==0 || Rpc_Bx_Pattern(events, presel_index[i])==1)) || 
			  //(doRpcBxCut && doCosEnrich && !(Rpc_Bx_Pattern(events, presel_index[i])==0 || Rpc_Bx_Pattern(events, presel_index[i])==1)) ||
			  if( (doRpcBxCut && !doCosEnrich && (Rpc_Bx_Pattern(events, presel_index[i])==0)) || 
			      (doRpcBxCut && doCosEnrich && !(Rpc_Bx_Pattern(events, presel_index[i])==0)) ||
			      (!doRpcBxCut)){
			    pass_Rpc_Bx = true;
			    
			    //timeInOut cut
			    if( (doTimeInOutCut && !doCosEnrich && events->muDisplacedStandAloneTrackDtTofTimeAtIpInOut[presel_index[i]]>TimeInOutCutValue_) ||
				(doTimeInOutCut && doCosEnrich && events->muDisplacedStandAloneTrackDtTofTimeAtIpInOut[presel_index[i]]<TimeInOutCutValue_) ||
				(!doTimeInOutCut)){
			      pass_TimeInOut = true;

			      //timeInOut error cut
			      if( (doTimeInOutErrCut && events->muDisplacedStandAloneTrackDtTofTimeAtIpInOutErr[presel_index[i]]<TimeInOutErrCutValue_) ||
				  //(doTimeInOutErrCut && doCosEnrich && events->muDisplacedStandAloneTrackDtTofTimeAtIpInOutErr[presel_index[i]]<TimeInOutErrCutValue_) ||
				  (!doTimeInOutErrCut)){
				pass_TimeInOutErr = true;
				
				//TOF dir cut
				if( (doTofDirCut && events->muDisplacedStandAloneTrackDtTofDirection[presel_index[i]]==1) ||
				    //(doTofDirCut && doCosEnrich && events->muDisplacedStandAloneTrackDtTofDirection[presel_index[i]]==1) ||
				    (!doTofDirCut)){
				  pass_TofDir = true;
				  
				  //DT inverse beta cut
				  if( (doDtInvBetaCut && !doCosEnrich && events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[presel_index[i]]>DtInvBetaCutValue_) || 
				      (doDtInvBetaCut && doCosEnrich && events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[presel_index[i]]<DtInvBetaCutValue_) || 
				      (!doDtInvBetaCut)){
				    pass_DtInvBeta = true;

				    //dxy cut
				    if( (doDxyCut && doCosEnrich && events->muDisplacedStandAloneTrackDxy[presel_index[i]]<DxyCutValue_) || 
					(!doDxyCut) || (!doCosEnrich)){
				      pass_Dxy = true;
				      
				      n_passHighestPt++;
				      if (n_passHighestPt==1) highestPt_index = presel_index[i];
				    
				    }//end of dxy cut for leading SA
				  }//end of dt inverse beta for leading SA
				}//end of tof dir cut of leading SA
			      }//end of timeInOut Error for leading SA
			    }//end of timeInOut for leading SA
			  }//end of rpc bx pattern is 0 or 1 for leading SA
			}//end of OppPhi cut for leading SA
		      }//end of OppEta cut for leading SA
		    }// end of csc hits for leading SA
		  }//end of dt hits for leading SA
		} //end of dist btw stations for leading SA
	      }//end of at least 1 RPC hit for leading SA
	    }//end of eta[0]<1.0
	  } //end of at least 2 DT/CSC chambers for leading SA
	} //end of pt[0]>30
      }//end of leading SA in upper hemisphere
    }//end of if presel_index is not 999
  }//end of loop over presel_indexes
  //cout<<"There are "<<n_passHighestPt<<" displaced SA muons that pass the highestPt criteria"<<endl;

}//end of HighestPtSA()

void findTreevalues_makehistos_Ntuples_allsamples::HighestPtSA_counts( bool& pass_Upper, bool& pass_pt, bool& pass_cha, bool& pass_eta, bool& pass_RPC, bool& pass_DisSt, bool& pass_DtHits, bool& pass_CscHits, bool& pass_DtInvBeta, bool& pass_TimeInOut, bool& pass_TimeInOutErr, bool& pass_TofDir, bool& pass_Rpc_Bx, bool& pass_OppEta, bool& pass_OppPhi, bool& pass_Dxy){

  //cout<<"starting HighestPtSA_counts"<<endl;

  //upper hemisphere cut
  if( pass_Upper){
    pass_Upper_cut++;
    //cout<<"passed upper cut"<<endl;
    
    //pt cut
    if ( pass_pt){
      pass_pt_cut++;
      //cout<<"passed pt cut"<<endl;
      
      //2 chamber cut
      if(pass_cha){
	pass_cha_cut++;
	//cout<<"passed chamber cut"<<endl;
	
	//eta cut
	if (pass_eta){
	  pass_eta_cut++;
	  //cout<<"passed eta cut"<<endl;
	  
	  //number of RPC hits cut
	  if(pass_RPC){
	    pass_RPC_cut++;
	    //cout<<"passed rpc cut"<<endl;
	    
	    //distance btw stations cut
	    if(pass_DisSt){
	      pass_DisSt_cut++;
	      
	      //number of DT hits cut
	      if(pass_DtHits){
		pass_DtHits_cut++;
		
		//number of CSC hits cut
		if(pass_CscHits){
		  pass_CscHits_cut++;
		  
		  //OppEta cut
		  if(pass_OppEta){
		    pass_OppEta_cut++;
		    
		    //OppPhi cut
		    if(pass_OppPhi){
		      pass_OppPhi_cut++;
		      
		      //RPC Bx pattern cut
		      if(pass_Rpc_Bx){
			pass_Rpc_Bx_cut++;
			
			//timeInOut cut
			if(pass_TimeInOut){
			  pass_TimeInOut_cut++;

			  //timeInOut error cut
			  if(pass_TimeInOutErr){
			    pass_TimeInOutErr_cut++;
			  
			    //tof dir cut
			    if(pass_TofDir){
			      pass_TofDir_cut++;
			      
			      //DT inverse beta cut
			      if(pass_DtInvBeta){
				pass_DtInvBeta_cut++;

				//dxy cut
				if(pass_Dxy){
				  pass_Dxy_cut++;
				
				}//end of dxy cut for leading SA
			      }//end of dt inverse beta for leading SA
			    } //end of tof dir cut for leading SA
			  }//end of timeInOut error for leading SA
			}//end of timeInOut for leading SA
		      }//end of rpc bx pattern is 0 or 1 for leading SA
		    }//end of OppPhi cut for leading SA
		  }//end of OppEta cut for leading SA
		}// end of csc hits for leading SA
	      }//end of dt hits for leading SA
	    } //end of dist btw stations for leading SA
	  }//end of at least 1 RPC hit for leading SA
	}//end of eta[0]<1.0
      } //end of at least 2 DT/CSC chambers for leading SA
    } //end of pt[0]>30
  }//end of leading SA in upper hemisphere
}//end of HighestPtSA_counts()

void findTreevalues_makehistos_Ntuples_allsamples::pick_UpperAndLowerSA( StoppedHSCPMuonEvent* events, int& n_passPreselection, int& n_Upper, int& n_Lower, UInt_t& presel0_index, UInt_t& presel1_index, UInt_t& presel2_index, UInt_t& presel3_index, UInt_t& upper0_index, UInt_t& lower0_index, UInt_t& upper1_index, UInt_t& lower1_index, UInt_t& upper2_index, UInt_t& lower2_index){

  //cout<<endl;
  UInt_t presel_index[4] = {presel0_index, presel1_index, presel2_index, presel3_index};

  n_Upper = 0;
  n_Lower = 0;

  if((doCosEnrich && n_passPreselection==2) || (!doCosEnrich)){
    pass_SA_2_cut++;
    //for (UInt_t j=0; j<events->mu_DisplacedStandAlone_N; j++) {
    //cout<<"for index "<<j<<", pt is: "<<events->muDisplacedStandAlonePt[j]<<", phi is: "<<events->muDisplacedStandAlonePhi[j]<<endl;
    //}
    
    for (int i=0; i<4; i++) {
      if (presel_index[i]!=999){
	
	//upper
	if( (!doTightPhi && events->muDisplacedStandAlonePhi[presel_index[i]]>0.) || (doTightPhi && (events->muDisplacedStandAlonePhi[presel_index[i]]>0.5 && events->muDisplacedStandAlonePhi[presel_index[i]]<(TMath::Pi()-0.5))) ){
	  n_Upper++;
	  if(n_Upper==1) upper0_index=presel_index[i];
	  if(n_Upper==2) upper1_index=presel_index[i];
	  if(n_Upper==3) upper2_index=presel_index[i];
	}//end of upper

	//lower
	if( (!doTightPhi && events->muDisplacedStandAlonePhi[presel_index[i]]<0.) || (doTightPhi && (events->muDisplacedStandAlonePhi[presel_index[i]] < (-0.5) && events->muDisplacedStandAlonePhi[presel_index[i]]>(-1.0*TMath::Pi()+0.5) ))){
	  n_Lower++;
	  if(n_Lower==1) lower0_index=presel_index[i];
	  if(n_Lower==2) lower1_index=presel_index[i];
	  if(n_Lower==3) lower2_index=presel_index[i];
	}//end of lower

      }//end of not presel index is 999
    }//end of loop over preselected muons

    /*
    if(x!=999 && y==999){
      pass_UpperOnly_cut++;
      double dEta = TMath::Abs(events->muDisplacedStandAloneEta[0] - events->muDisplacedStandAloneEta[1]);
      double dPhi = TMath::Abs(events->muDisplacedStandAlonePhi[0] - events->muDisplacedStandAlonePhi[1]);
      while (dPhi > TMath::Pi()) dPhi -= 2*TMath::Pi();
      while (dPhi <= -TMath::Pi()) dPhi += 2*TMath::Pi();
      muDisplacedStandAloneUpperOnlyDEta_hist->Fill(dEta);
      muDisplacedStandAloneUpperOnlyDPhi_hist->Fill(dPhi);
    }
    if(x==999 && y!=999){
      pass_LowerOnly_cut++;
      double dEta = TMath::Abs(events->muDisplacedStandAloneEta[0] - events->muDisplacedStandAloneEta[1]);
      double dPhi = TMath::Abs(events->muDisplacedStandAlonePhi[0] - events->muDisplacedStandAlonePhi[1]);
      while (dPhi > TMath::Pi()) dPhi -= 2*TMath::Pi();
      while (dPhi <= -TMath::Pi()) dPhi += 2*TMath::Pi();
      muDisplacedStandAloneLowerOnlyDEta_hist->Fill(dEta);
      muDisplacedStandAloneLowerOnlyDPhi_hist->Fill(dPhi);
    }
    */
  }//end of exactly 2 preselected muons for cosmic enriched sample

  //cout<<"number of upper preselected muons is: "<<n_Upper<<"; number of lower preselected muons is: "<<n_Lower<<endl;
  //cout<<"upper0_index is: "<<upper0_index<<", lower0_index is: "<<lower0_index<<endl;
  //cout<<"upper1_index is: "<<upper1_index<<", lower1_index is: "<<lower1_index<<endl;
  //cout<<"upper2_index is: "<<upper2_index<<", lower2_index is: "<<lower2_index<<endl;
  
}//end of pick_UpperAndLowerSA

void findTreevalues_makehistos_Ntuples_allsamples::UpperAndLowerSA( StoppedHSCPMuonEvent* events, string& file_dataset_, UInt_t& upper0_index, UInt_t& lower0_index, UInt_t& upper1_index, UInt_t& lower1_index, UInt_t& upper2_index, UInt_t& lower2_index, UInt_t& upper_index, UInt_t& lower_index, float& PtCutValue_, Int_t& ChaCutValue_, float& EtaCutValue_, Int_t& RpcCutValue_,  Int_t& DisStCutValue_, Int_t& DtHitsCutValue_, float& DtInvBetaCutValue_, float& TimeInOutCutValue_, float& TimeInOutErrCutValue_, float& DeltaTimeInOutCutValue_, float& DeltaDtInvBetaCutValue_, bool& pass_UpperAndLower, bool& pass_pt_2, bool& pass_cha_2, bool& pass_eta_2, bool& pass_RPC_2,  bool& pass_DisSt_2, bool& pass_DtHits_2, bool& pass_OppEta_2, bool& pass_OppPhi_2, bool& pass_Rpc_Bx_2, bool& pass_DtInvBeta_2, bool& pass_TimeInOut_2, bool& pass_TimeInOutErr_2, bool& pass_DeltaTimeInOut_2, bool& pass_DeltaDtInvBeta_2, bool& pass_TofDir_2, bool& pass_charge_2){

  UInt_t upper_Index[3] = {upper0_index, upper1_index, upper2_index};
  UInt_t lower_Index[3] = {lower0_index, lower1_index, lower2_index};

  int n_passUpperAndLower = 0;

  for (int i=0; i<3; i++) {
    for (int j=0; j<3; j++) {
      if(upper_Index[i]!=999 && lower_Index[j]!=999){
	pass_UpperAndLower = true;
	//pass_UpperAndLower_pt30 = true;

	//double UpperSegment_dPhi, UpperSegment_dEta;
	//double LowerSegment_dPhi, LowerSegment_dEta;
	//double UpperSegment_dR = dR_OppositeSeg(events, upper_index, UpperSegment_dPhi, UpperSegment_dEta);
	//double LowerSegment_dR = dR_OppositeSeg(events, lower_index, LowerSegment_dPhi, LowerSegment_dEta);
	
	//cout<<"run is: "<<events->run<<", event is: "<<events->id<<endl;
	//cout<<"upper track_dPhi is: "<<events->muDisplacedStandAlonePhi[upper_index]<<", upper track_dEta is: "<<events->muDisplacedStandAloneEta[upper_index]<<endl;
	//cout<<"UpperSegment_dR is: "<<UpperSegment_dR<<",  UpperSegment_dPhi is: "<<UpperSegment_dPhi<<",  UpperSegment_dEta is: "<<UpperSegment_dEta<<endl<<endl;
	//cout<<"lower track_dPhi is: "<<events->muDisplacedStandAlonePhi[lower_index]<<", lower track_dEta is: "<<events->muDisplacedStandAloneEta[lower_index]<<endl;
	//cout<<"LowerSegment_dR is: "<<LowerSegment_dR<<",  LowerSegment_dPhi is: "<<LowerSegment_dPhi<<",  LowerSegment_dEta is: "<<LowerSegment_dEta<<endl<<endl;
	
	if((file_dataset_=="Zmum" && diMuMass_Cut(events)) || (file_dataset_!="Zmum")){             	
	  
	  if( (doPtCut && (events->muDisplacedStandAlonePt[upper_Index[i]]>PtCutValue_ && events->muDisplacedStandAlonePt[lower_Index[j]]>PtCutValue_)) || (!doPtCut)){
	  //if( (doPtCut && (events->muDisplacedStandAlonePt[upper_Index[i]]>PtCutValue_ && events->muDisplacedStandAlonePt[lower_Index[j]]>abcdPtCutValue_)) || (!doPtCut)){
	    pass_pt_2 = true;
      
	    //2 chamber cut
	    //if( (doChaCut && (events->muDisplacedStandAloneTrackNDtChambersWithValidHits[upper_Index[i]] + events->muDisplacedStandAloneTrackNCscChambersWithValidHits[upper_Index[i]])>ChaCutValue_ && (events->muDisplacedStandAloneTrackNDtChambersWithValidHits[lower_Index[j]] + events->muDisplacedStandAloneTrackNCscChambersWithValidHits[lower_Index[j]])>ChaCutValue_) || (!doChaCut)) {
	    if( (doChaCut && (events->muDisplacedStandAloneTrackNDtChambersWithValidHits[upper_Index[i]])>ChaCutValue_ && (events->muDisplacedStandAloneTrackNDtChambersWithValidHits[lower_Index[j]])>ChaCutValue_) || (!doChaCut)) {
	      pass_cha_2 = true;
	      
	      //eta cut
	      if ( (doEtaCut && TMath::Abs(events->muDisplacedStandAloneEta[upper_Index[i]])<EtaCutValue_ && TMath::Abs(events->muDisplacedStandAloneEta[lower_Index[j]])<EtaCutValue_) || (!doEtaCut) ){
		pass_eta_2 = true;
		
		//RPC hits cut
		if( (doRpcCut && events->muDisplacedStandAloneTrackNValidRpcHits[upper_Index[i]]>RpcCutValue_ && events->muDisplacedStandAloneTrackNValidRpcHits[lower_Index[j]]>RpcCutValue_) || (!doRpcCut)){
		  pass_RPC_2 = true;			  
		  
		  //distance btw stations cut
		  bool refitted = false;	    
		  if( (doDisStCut && distanceBetweenStations(events, upper_Index[i], refitted)>DisStCutValue_ && distanceBetweenStations(events, lower_Index[j], refitted)>DisStCutValue_ ) || (!doDisStCut)){
		    pass_DisSt_2 = true;
		    
		    //number of DT hits cut
		    if( (doDtHitsCut && events->muDisplacedStandAloneTrackDtTofNDof[upper_Index[i]]>DtHitsCutValue_ && events->muDisplacedStandAloneTrackDtTofNDof[lower_Index[j]]>DtHitsCutValue_) || (!doDtHitsCut)){
		      pass_DtHits_2 = true;	      
		    
		      /*
		      double dEta = events->muDisplacedStandAloneEta[upper_Index[i]] + events->muDisplacedStandAloneEta[lower_Index[j]];
		      double dPhi = events->muDisplacedStandAlonePhi[upper_Index[i]] - (events->muDisplacedStandAlonePhi[lower_Index[j]] + TMath::Pi());
		      while (dPhi > TMath::Pi()) dPhi -= 2*TMath::Pi();
		      while (dPhi <= -TMath::Pi()) dPhi += 2*TMath::Pi();
		      */

		      //OppEta cut (cosmic enriched)
		      //if((doCosEnrich && TMath::Abs(dEta)<OppEtaCutValue_) || (!doCosEnrich)){
		      if((doCosEnrich ) || (!doCosEnrich)){
			pass_OppEta_2 = true;
			
			//OppPhi cut (cosmic enriched)
			//if((doCosEnrich && TMath::Abs(dPhi)<OppPhiCutValue_) || (!doCosEnrich)){
			if((doCosEnrich ) || (!doCosEnrich)){
			  pass_OppPhi_2 = true;
			  
			  //RPC Bx pattern cut
			  //if( (doRpcBxCut && !doCosEnrich && (Rpc_Bx_Pattern(events, upper_Index[i])==0 || Rpc_Bx_Pattern(events, upper_Index[i])==1) && (Rpc_Bx_Pattern(events, lower_Index[j])==0 || Rpc_Bx_Pattern(events, lower_Index[j])==1)) || 
			  //(doRpcBxCut && doCosEnrich && !(Rpc_Bx_Pattern(events, upper_Index[i])==0 || Rpc_Bx_Pattern(events, upper_Index[i])==1) && !(Rpc_Bx_Pattern(events, lower_Index[j])==0 || Rpc_Bx_Pattern(events, lower_Index[j])==1)) || 
			  //if( (doRpcBxCut && !doCosEnrich && (Rpc_Bx_Pattern(events, upper_Index[i])==0) && (Rpc_Bx_Pattern(events, lower_Index[j])==0)) || 
			  //(doRpcBxCut && doCosEnrich && !(Rpc_Bx_Pattern(events, upper_Index[i])==0) && !(Rpc_Bx_Pattern(events, lower_Index[j])==0)) || 
			  //(!doRpcBxCut)){
			    
			  if( (doRpcBxCut && !doCosEnrich && (Rpc_Bx_Pattern(events, lower_Index[j])==0)) || 
			      (doRpcBxCut && doCosEnrich && !(Rpc_Bx_Pattern(events, lower_Index[j])==0)) || 
			      (!doRpcBxCut)){
			    pass_Rpc_Bx_2 = true;
			    
			    //timeInOut cut
			    if( (doTimeInOutCut && !doCosEnrich && events->muDisplacedStandAloneTrackDtTofTimeAtIpInOut[upper_Index[i]]>TimeInOutCutValue_ && events->muDisplacedStandAloneTrackDtTofTimeAtIpInOut[lower_Index[j]]>TimeInOutCutValue_) || 
				(doTimeInOutCut && doCosEnrich && events->muDisplacedStandAloneTrackDtTofTimeAtIpInOut[upper_Index[i]]<TimeInOutCutValue_ && events->muDisplacedStandAloneTrackDtTofTimeAtIpInOut[lower_Index[j]]<TimeInOutCutValue_) || 
				(!doTimeInOutCut)){
			      pass_TimeInOut_2 = true;

			      //timeInOut error cut
			      if( (doTimeInOutErrCut && events->muDisplacedStandAloneTrackDtTofTimeAtIpInOutErr[upper_Index[i]]<TimeInOutErrCutValue_ && events->muDisplacedStandAloneTrackDtTofTimeAtIpInOutErr[lower_Index[j]]<TimeInOutErrCutValue_) || 
				  //(doTimeInOutErrCut && doCosEnrich && events->muDisplacedStandAloneTrackDtTofTimeAtIpInOutErr[upper_Index[i]]<TimeInOutErrCutValue_ && events->muDisplacedStandAloneTrackDtTofTimeAtIpInOutErr[lower_Index[j]]<TimeInOutErrCutValue_) || 
				  (!doTimeInOutErrCut)){
				pass_TimeInOutErr_2 = true;
				
				//delta timeInOut cut
				if( (doDeltaTimeInOutCut && !doCosEnrich && (events->muDisplacedStandAloneTrackDtTofTimeAtIpInOut[upper_Index[i]]-events->muDisplacedStandAloneTrackDtTofTimeAtIpInOut[lower_Index[j]])>DeltaTimeInOutCutValue_) || 
				    (doDeltaTimeInOutCut && doCosEnrich && (events->muDisplacedStandAloneTrackDtTofTimeAtIpInOut[upper_Index[i]]-events->muDisplacedStandAloneTrackDtTofTimeAtIpInOut[lower_Index[j]])<DeltaTimeInOutCutValue_) || 
				    (!doDeltaTimeInOutCut)){
				  pass_DeltaTimeInOut_2 = true;

				  //delta inverse beta cut
				  if( (doDeltaDtInvBetaCut && !doCosEnrich && (events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[upper_Index[i]]-events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[lower_Index[j]])>DeltaDtInvBetaCutValue_) || 
				      (doDeltaDtInvBetaCut && doCosEnrich && (events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[upper_Index[i]]-events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[lower_Index[j]])<DeltaDtInvBetaCutValue_) || 
				      (!doDeltaDtInvBetaCut)){
				    pass_DeltaDtInvBeta_2 = true;
				  
				    //charge cut
				    if( (doChargeCut && events->muDisplacedStandAloneCharge[upper_Index[i]] == events->muDisplacedStandAloneCharge[lower_Index[j]]) || 
					//(doChargeCut && doCosEnrich && events->muDisplacedStandAloneCharge[upper_Index[i]] == events->muDisplacedStandAloneCharge[lower_Index[j]]) || 
					(!doChargeCut)){
				      pass_charge_2 = true;
				      
				      //tof dir cut
				      if( (doTofDirCut && !doCosEnrich && events->muDisplacedStandAloneTrackDtTofDirection[upper_Index[i]]==1 && events->muDisplacedStandAloneTrackDtTofDirection[lower_Index[j]]==1) || 
					  //(doTofDirCut && doCosEnrich && events->muDisplacedStandAloneTrackDtTofDirection[upper_Index[i]]==1 && events->muDisplacedStandAloneTrackDtTofDirection[lower_Index[j]]==1) || 
					  //(!doTofDirCut)){
					  //if( (doTofDirCut && events->muDisplacedStandAloneTrackDtTofDirection[lower_Index[j]]==1) || 
					  //(doTofDirCut && doCosEnrich && events->muDisplacedStandAloneTrackDtTofDirection[lower_Index[j]]==1) || 
					  (!doTofDirCut)){
					pass_TofDir_2 = true;
					
					//DT inverse beta cut
					if( (doDtInvBetaCut && !doCosEnrich && events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[upper_Index[i]]>DtInvBetaCutValue_ && events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[lower_Index[j]]>DtInvBetaCutValue_) || 
					    (doDtInvBetaCut && doCosEnrich && events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[upper_Index[i]]<DtInvBetaCutValue_ && events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[lower_Index[j]]<DtInvBetaCutValue_) || 
					//(!doDtInvBetaCut)){
					//if( (doDtInvBetaCut && !doCosEnrich && events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[lower_Index[j]]>DtInvBetaCutValue_) || 
					//(doDtInvBetaCut && doCosEnrich && events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[lower_Index[j]]<DtInvBetaCutValue_) || 
					    (!doDtInvBetaCut)){
					  pass_DtInvBeta_2 = true;
					  
					  //if(doPrintout) printout_SA(events);
					  n_passUpperAndLower++;
					  if(n_passUpperAndLower==1){
					    upper_index = upper_Index[i];
					    lower_index = lower_Index[j];
					  }
					  
					}//end of dt inv beta cut for 2 muons
				      }//end of charge cut for 2 muons
				    }//end of tof dir cut for 2 muons
				  } //end of delta inverse beta cut
				}//end of delta timeInOut cut 
			      }////end of timeInOut error cut for 2 muons
			    }//end of timeInOut cut for 2 muons
			  }//end of rpc bx pattern cut for 2 muons
			}//end of opp phi cut for cosmic enriched 2 muons
		      }//end of opp eta cut for cosmic enriched 2 muons
		    }//end of number of dt hits cut for 2 muons
		  } //end of dist btw stations for 2 muons
		}//end of if at least 1 RPC hit for 2 muons
	      }//end of eta cut for 2 muons
	    } //end of 2 cha cut for 2 muons
	  }//end of OR pt cut for 2 muons
	}// end of Zmumu z-mass cut
      }//end of if index not 999 
    }//end of loop over j
  }//end of loop over i
}//end of UpperAndLowerSA

void findTreevalues_makehistos_Ntuples_allsamples::UpperAndLowerSA_counts(bool& pass_UpperAndLower, bool& pass_pt_2, bool& pass_cha_2, bool& pass_eta_2, bool& pass_RPC_2,  bool& pass_DisSt_2, bool& pass_DtHits_2, bool& pass_OppEta_2, bool& pass_OppPhi_2, bool& pass_Rpc_Bx_2, bool& pass_DtInvBeta_2, bool& pass_TimeInOut_2, bool& pass_TimeInOutErr_2, bool& pass_DeltaTimeInOut_2, bool& pass_DeltaDtInvBeta_2, bool& pass_TofDir_2, bool& pass_charge_2){

  if(pass_UpperAndLower){
    pass_UpperAndLower_cut++;
    //pass_UpperAndLower_pt30_cut++;
    
    if(pass_pt_2){
      pass_pt_2_cut++;
      
      //2 chamber cut
      if(pass_cha_2){
	pass_cha_2_cut++;
	
	//eta cut
	if (pass_eta_2){
	  pass_eta_2_cut++;
	  
	  //RPC hits cut
	  if(pass_RPC_2){
	    pass_RPC_2_cut++;			  
	    
	    //distance btw stations cut
	    if(pass_DisSt_2){
	      pass_DisSt_2_cut++;
	      
	      //number of DT hits cut
	      if(pass_DtHits_2){
		pass_DtHits_2_cut++;	      
		
		//OppEta cut (cosmic enriched)
		if(pass_OppEta_2){
		  pass_OppEta_2_cut++;
			
		  //OppPhi cut (cosmic enriched)
		  if(pass_OppPhi_2){
		    pass_OppPhi_2_cut++;
		    
		    //RPC Bx pattern cut
		    if(pass_Rpc_Bx_2){
		      pass_Rpc_Bx_2_cut++;
		      			      
		      //timeInOut cut
		      if(pass_TimeInOut_2){
			pass_TimeInOut_2_cut++;

			//timeInOut error cut
			if(pass_TimeInOutErr_2){
			  pass_TimeInOutErr_2_cut++;
			  
			  //delta timeInOut cut
			  if(pass_DeltaTimeInOut_2){
			    pass_DeltaTimeInOut_2_cut++;
			    
			    //delta inverse beta cut
			    if(pass_DeltaDtInvBeta_2){
			      pass_DeltaDtInvBeta_2_cut++;
			      
			      //charge cut
			      if(pass_charge_2){
				pass_charge_2_cut++;
				
				//tof dir cut
				if(pass_TofDir_2){
				  pass_TofDir_2_cut++;
				  
				  //DT inverse beta cut
				  if(pass_DtInvBeta_2){
				    pass_DtInvBeta_2_cut++;
				    
				  }//end of dt inv beta cut for 2 muons
				}//end of pass charge cut for 2 muons
			      }//end of pass tof dir cut for 2 muons
			    }//end of delta inverse beta cut
			  } //end of delta timeinout cut 			  
			}//end of timeInOut error cut for 2 muons
		      }//end of timeInOut cut for 2 muons
		    }//end of rpc bx pattern cut for 2 muons
		  }//end of opp phi cut for cosmic enriched 2 muons
		}//end of opp eta cut for cosmic enriched 2 muons
	      }//end of number of dt hits cut for 2 muons
	    } //end of dist btw stations for 2 muons
	  }//end of if at least 1 RPC hit for 2 muons
	}//end of eta cut for 2 muons
      } //end of 2 cha cut for 2 muons
    }//end of OR pt cut for 2 muons
  }//end of if pass Upper and Lower
}//end of UpperAndLowerSA_counts()

void findTreevalues_makehistos_Ntuples_allsamples::TriggerTurnOn( StoppedHSCPMuonEvent* events, string& file_dataset, UInt_t& presel0_index){

  //cout<<"starting TriggerTurnOn"<<endl;
  if(events->hltL2Mu10NoVertexNoBptx3BX || events->hltL2Mu10NoVertexNoBptx3BXNoHalo ){
    muDisplacedStandAlonePt_denominator_hist->Fill(events->muDisplacedStandAlonePt[presel0_index],1.0);
    //cout<<"filled denominator hist"<<endl;
    
    //pass HLT                                                                                                                                                                                                     
    if(file_dataset != "Zmum" && (events->hltL2Mu20NoVertexNoBptx3BX || events->hltL2Mu30NoVertexNoBptx3BX || events->hltL2Mu20NoVertexNoBptx3BXNoHalo || events->hltL2Mu30NoVertexNoBptx3BXNoHalo || events->hltL2Mu20NoVertex2ChaNoBptx3BXNoHalo || events->hltL2Mu30NoVertex2ChaNoBptx3BXNoHalo) ){ 
      //if(file_dataset != "Zmum" && (events->hltL2Mu20NoVertexNoBptx3BX || events->hltL2Mu20NoVertexNoBptx3BXNoHalo || events->hltL2Mu20NoVertex2ChaNoBptx3BXNoHalo) ){ 
      //if(file_dataset != "Zmum" && ( events->hltL2Mu30NoVertexNoBptx3BX || events->hltL2Mu30NoVertexNoBptx3BXNoHalo || events->hltL2Mu30NoVertex2ChaNoBptx3BXNoHalo) ){ 
      //cout<<"passed HLT"<<endl;
      muDisplacedStandAlonePt_HLTnumerator_hist->Fill(events->muDisplacedStandAlonePt[presel0_index],1.0);
    }//end of pass hlt
    
    //pass L1
    //[2] is main BX
    if (events->l1SingleMu6NoBptx[2]){
      //cout<<"passed L1"<<endl;
      muDisplacedStandAlonePt_L1numerator_hist->Fill(events->muDisplacedStandAlonePt[presel0_index],1.0);
    }//end of pass L1
  }//pass 10 GeV control trigger  
}//end of TriggerTurnOn
  

void findTreevalues_makehistos_Ntuples_allsamples::GlobalSATagAndProbe( StoppedHSCPMuonEvent* events, UInt_t& highestPt_index){
  //plots probe info
  //cout<<"starting GlobalSATagAndProbe"<<endl;
  
  //probe denominator
  muDisplacedStandAlonePt_GlSAdenominator_hist->Fill(events->muDisplacedStandAlonePt[highestPt_index],1.0);
  //cout<<"filled probe denominator hist"<<endl;
  /*
  //probe matched to good tag?
  if(events->muDisplacedStandAloneTrackGlobalMuonIndex[highestPt_index]>=0){
    cout<<"probe matched to global muon"<<endl;
    int GlMuIndex = events->muDisplacedStandAloneTrackGlobalMuonIndex[highestPt_index];
    //if(events->muIsStandAloneMuon[GlMuIndex] && events->muIsGlobalMuon[GlMuIndex] && events->muIsTrackerMuon[GlMuIndex] && events->muSAnDtChambersWithValidHits[GlMuIndex]>1){
    if(events->muIsStandAloneMuon[GlMuIndex] && events->muIsGlobalMuon[GlMuIndex]){
      //probe numerator
      muDisplacedStandAlonePt_GlSAnumerator_hist->Fill(events->muDisplacedStandAlonePt[highestPt_index],1.0);


      double pt_resolution = 1.0*(events->muDisplacedStandAlonePt[highestPt_index] - events->muTunePpt[GlMuIndex])/(events->muTunePpt[GlMuIndex]); 
      //double qOverPt_resolution = 1.0*(1.0*events->muDisplacedStandAloneCharge[j]/events->muDisplacedStandAlonePt[j] - 1.0*events->mcMuonCharge[genMuMatched_DSA_index[j]]/events->mcMuonPt[genMuMatched_DSA_index[j]])/(1.0*events->mcMuonCharge[genMuMatched_DSA_index[j]]/events->mcMuonPt[genMuMatched_DSA_index[j]]); 
      muDisplacedStandAlonePtResolution_hist->Fill(pt_resolution,1.0);

      cout<<"filled probe numerator hist"<<endl;
    } //end of if muon is global, SA w/>1 DT chambers, tracker
  }//end of pass probe
  */
}//end of globalSAtagandprobe

void findTreevalues_makehistos_Ntuples_allsamples::printout_setup( StoppedHSCPMuonEvent* events, bool& is_data){
  
  if(events->mu_DisplacedStandAlone_N>0 || events->mcMuon_N>0 || events->mcTop_N>0 || events->mcW_N>0 || events->mcCMshower_N>0 || events->mcTau_N>0){
    cout<<"__________________________________________________________________________________________________________________________________________________________"<<endl;
    line++;
  }
  
  if (line==3 || line % 15 == 0) {
    //cout  << "                                                                                 Hits             Chambers" << endl;
    //cout  << "                                                      M_ID       M_W_ID          Hits             Chambers" << endl;
    cout  << "                                                      Status   Daughters  Moth  Moth_of_W  v_{x} v_{y} y_{z}" << endl;
    cout  << "                                                                             Hits                Chambers                           DT time" << endl;
    cout  << setw(6) << "Run";
    cout  << setw(6) << "Lumi";
    cout  << setw(10) << "Event";
    cout  << setw(8) << "SA/Gen";
    cout  << setw(8) << "pT";
    cout  << setw(7) << "eta";
    cout  << setw(7) << "phi";
    cout  << setw(7) << "charge";
    cout  << setw(7) << "chi2";
    cout  << setw(14) << "RPC BXs";
    cout  << setw(5) << "All";
    cout  << setw(5) << "CSC";
    cout  << setw(5) << "DT";
    cout  << setw(5) << "RPC";
    cout  << setw(5) << "Sts";
    cout  << setw(5) << "CSC";
    cout  << setw(5) << "DT";
    cout  << setw(5) << "RPC";
    cout  << setw(5) << "Dir";
    cout  << setw(7) << "tInOut";
    cout  << setw(7) << "tInOut err";
    cout  << setw(7) << "1/beta";
    cout  << setw(11) << "1/beta err";
    cout  << setw(5) << "nDOF"<<endl;
    line = line + 2;
  }
  
  if(is_data){
    /*
    cout  << setw(6) << "Run";
    cout  << setw(6) << "Lumi";
    cout  << setw(10) << "Orbit";
    cout  << setw(8) << "Bx";
    cout  << setw(8) << "";
    cout  << setw(7) << "Event"<<endl;
    cout  << setw(6) << events->run;
    cout  << setw(6) << events->lb;
    cout  << setw(10) << events->orbit;
    cout  << setw(8) << events->bx;
    cout  << setw(8) << " ";
    cout  << setw(7) << events->id<<endl;
    */
    //cout  << events->run<<"," << events->lb<<","<< events->orbit<<"," << events->bx<<","<< events->id<<endl;
  //line=line+2;
  }
}//end of printout_setup()

void findTreevalues_makehistos_Ntuples_allsamples::printout_gen( StoppedHSCPMuonEvent* events){
  for (UInt_t j=0; j<events->mcStoppedParticle_N; j++) {
    cout  << setw(6) << events->run;
    cout  << setw(6) << events->lb;
    cout  << setw(10) << events->id;
    cout  << setw(8) << "SPart"<<j;
    //cout  << fixed << setprecision(PtPrecision)  << setw(8) << events->mcStoppedParticleX[j]/10.;
    //cout  << fixed << setprecision(EtaPrecision) << setw(7) << events->mcStoppedParticleY[j]/10.;
    //cout  << fixed << setprecision(PhiPrecision) << setw(7) << events->mcStoppedParticleZ[j]/10;
    cout  << fixed << setprecision(PtPrecision)  << setw(8) << " ";
    double particle_eta = eta(events->mcStoppedParticleX[j],events->mcStoppedParticleY[j],
			      events->mcStoppedParticleZ[j],events->mcStoppedParticleTime[j]);
    cout  << fixed << setprecision(EtaPrecision) << setw(7) << particle_eta;
    cout  << fixed << setprecision(PhiPrecision) << setw(7) << events->mcStoppedParticlePhi[j];
    cout  << fixed << setw(7) << events->mcStoppedParticleCharge[j];
    cout  << fixed << setw(7) << events->mcStoppedParticleId[j];
    cout  << fixed << setw(7) << events->mcStoppedParticleMass[j];
    //cout  << fixed << setw(7) << " ";
    //cout  << fixed << setw(7) << " ";
    cout  << fixed << setw(7) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(7) << " " << endl;
    line++;
  }

  for (UInt_t j=0; j<events->mcStop_N; j++) {
    TString Daughters = " ";
    for (UInt_t k=0; k<events->mcStopDaughterId.at(j).size(); k++) {
      //cout<<"bx for hit "<<k<<" is: "<<events->muDisplacedStandAloneTrackRpcHitBx.at(j).at(k)<<endl;                                                                                                    
      string each_daughter;
      ostringstream convert;
      convert<<events->mcStopDaughterId.at(j).at(k);
      each_daughter = convert.str();
      Daughters = Daughters + each_daughter + " ";
    }
    
    cout  << setw(6) << events->run;
    cout  << setw(6) << events->lb;
    cout  << setw(10) << events->id;
    cout  << setw(8) << "GenStop"<<j;
    cout  << fixed << setprecision(PtPrecision)  << setw(8) << events->mcStopPt[j];
    cout  << fixed << setprecision(EtaPrecision) << setw(7) << events->mcStopEta[j];
    cout  << fixed << setprecision(PhiPrecision) << setw(7) << events->mcStopPhi[j];
    cout  << fixed << setprecision(ChargePrecision) << setw(7) << events->mcStopCharge[j];
    cout  << fixed << setw(7) << events->mcStopStatus[j];
    cout  << fixed << setw(14) << Daughters;
    cout  << fixed << setw(5) << events->mcStopMotherId[j];
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(7) << " ";
    cout  << fixed << setw(7) << " " << endl;
    line++;
    }//end of loop over tops
  
  for (UInt_t j=0; j<events->mcTop_N; j++) {
    TString Daughters = " ";
    for (UInt_t k=0; k<events->mcTopDaughterId.at(j).size(); k++) {
      //cout<<"bx for hit "<<k<<" is: "<<events->muDisplacedStandAloneTrackRpcHitBx.at(j).at(k)<<endl;                                                                                                    
      string each_daughter;
      ostringstream convert;
      convert<<events->mcTopDaughterId.at(j).at(k);
      each_daughter = convert.str();
      Daughters = Daughters + each_daughter + " ";
    }
    
    cout  << setw(6) << events->run;
    cout  << setw(6) << events->lb;
    cout  << setw(10) << events->id;
    cout  << setw(8) << "GenTop"<<j;
    cout  << fixed << setprecision(PtPrecision)  << setw(8) << events->mcTopPt[j];
    cout  << fixed << setprecision(EtaPrecision) << setw(7) << events->mcTopEta[j];
    cout  << fixed << setprecision(PhiPrecision) << setw(7) << events->mcTopPhi[j];
    cout  << fixed << setprecision(ChargePrecision) << setw(7) << events->mcTopCharge[j];
    cout  << fixed << setw(7) << events->mcTopStatus[j];
    cout  << fixed << setw(14) << Daughters;
    cout  << fixed << setw(5) << events->mcTopMotherId[j];
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(7) << " ";
    cout  << fixed << setw(7) << " " << endl;
    line++;
    }//end of loop over tops
  
  for (UInt_t j=0; j<events->mcStau_N; j++) {
    TString Daughters = " ";
    for (UInt_t k=0; k<events->mcStauDaughterId.at(j).size(); k++) {
      //cout<<"bx for hit "<<k<<" is: "<<events->muDisplacedStandAloneTrackRpcHitBx.at(j).at(k)<<endl;                                                                                                    
      string each_daughter;
      ostringstream convert;
      convert<<events->mcStauDaughterId.at(j).at(k);
      each_daughter = convert.str();
      Daughters = Daughters + each_daughter + " ";
    }
    
    cout  << setw(6) << events->run;
    cout  << setw(6) << events->lb;
    cout  << setw(10) << events->id;
    cout  << setw(8) << "GenStau"<<j;
    cout  << fixed << setprecision(PtPrecision)  << setw(8) << events->mcStauPt[j];
    cout  << fixed << setprecision(EtaPrecision) << setw(7) << events->mcStauEta[j];
    cout  << fixed << setprecision(PhiPrecision) << setw(7) << events->mcStauPhi[j];
    cout  << fixed << setprecision(ChargePrecision) << setw(7) << events->mcStauCharge[j];
    cout  << fixed << setw(7) << events->mcStauStatus[j];
    cout  << fixed << setw(14) << Daughters;
    cout  << fixed << setw(5) << events->mcStauMotherId[j];
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(7) << " ";
    cout  << fixed << setw(7) << " " << endl;
    line++;
  }//end of loop over staus
  
  for (UInt_t j=0; j<events->mcGluino_N; j++) {
    TString Daughters = " ";
    for (UInt_t k=0; k<events->mcGluinoDaughterId.at(j).size(); k++) {
      //cout<<"bx for hit "<<k<<" is: "<<events->muDisplacedStandAloneTrackRpcHitBx.at(j).at(k)<<endl;                                                                                                    
      string each_daughter;
      ostringstream convert;
      convert<<events->mcGluinoDaughterId.at(j).at(k);
      each_daughter = convert.str();
      Daughters = Daughters + each_daughter + " ";
    }
    
    cout  << setw(6) << events->run;
    cout  << setw(6) << events->lb;
    cout  << setw(10) << events->id;
    cout  << setw(8) << "GenGluino"<<j;
    cout  << fixed << setprecision(PtPrecision)  << setw(8) << events->mcGluinoPt[j];
    cout  << fixed << setprecision(EtaPrecision) << setw(7) << events->mcGluinoEta[j];
    cout  << fixed << setprecision(PhiPrecision) << setw(7) << events->mcGluinoPhi[j];
    cout  << fixed << setprecision(ChargePrecision) << setw(7) << events->mcGluinoCharge[j];
    cout  << fixed << setw(7) << events->mcGluinoStatus[j];
    cout  << fixed << setw(14) << Daughters;
    cout  << fixed << setw(5) << events->mcGluinoMotherId[j];
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(7) << " ";
    cout  << fixed << setw(7) << " " << endl;
    line++;
  }//end of loop over gluinos
  
  for (UInt_t j=0; j<events->mcTauPrime_N; j++) {
    TString Daughters = " ";
    for (UInt_t k=0; k<events->mcTauPrimeDaughterId.at(j).size(); k++) {
      //cout<<"bx for hit "<<k<<" is: "<<events->muDisplacedStandAloneTrackRpcHitBx.at(j).at(k)<<endl;                                                                                                    
      string each_daughter;
      ostringstream convert;
      convert<<events->mcTauPrimeDaughterId.at(j).at(k);
      each_daughter = convert.str();
      Daughters = Daughters + each_daughter + " ";
    }
    
    cout  << setw(6) << events->run;
    cout  << setw(6) << events->lb;
    cout  << setw(10) << events->id;
    cout  << setw(8) << "GenMcha"<<j;
    cout  << fixed << setprecision(PtPrecision)  << setw(8) << events->mcTauPrimePt[j];
    cout  << fixed << setprecision(EtaPrecision) << setw(7) << events->mcTauPrimeEta[j];
    cout  << fixed << setprecision(PhiPrecision) << setw(7) << events->mcTauPrimePhi[j];
    cout  << fixed << setprecision(ChargePrecision) << setw(7) << 2.*events->mcTauPrimeCharge[j];
    cout  << fixed << setw(7) << events->mcTauPrimeStatus[j];
    cout  << fixed << setw(14) << Daughters;
    cout  << fixed << setw(5) << events->mcTauPrimeMotherId[j];
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(7) << " ";
    cout  << fixed << setw(7) << " " << endl;
    line++;
  }//end of loop over gluinos
  
  for (UInt_t j=0; j<events->mcNeutralino_N; j++) {
    TString Daughters = " ";
    for (UInt_t k=0; k<events->mcNeutralinoDaughterId.at(j).size(); k++) {
      //cout<<"bx for hit "<<k<<" is: "<<events->muDisplacedStandAloneTrackRpcHitBx.at(j).at(k)<<endl;                                                                                                    
      string each_daughter;
      ostringstream convert;
      convert<<events->mcNeutralinoDaughterId.at(j).at(k);
      each_daughter = convert.str();
      Daughters = Daughters + each_daughter + " ";
    }
    
    cout  << setw(6) << events->run;
    cout  << setw(6) << events->lb;
    cout  << setw(10) << events->id;
    cout  << setw(8) << "GenNeu"<<j;
    cout  << fixed << setprecision(PtPrecision)  << setw(8) << events->mcNeutralinoPt[j];
    cout  << fixed << setprecision(EtaPrecision) << setw(7) << events->mcNeutralinoEta[j];
    cout  << fixed << setprecision(PhiPrecision) << setw(7) << events->mcNeutralinoPhi[j];
    cout  << fixed << setprecision(ChargePrecision) << setw(7) << events->mcNeutralinoCharge[j];
    cout  << fixed << setw(7) << events->mcNeutralinoStatus[j];
    cout  << fixed << setw(14) << Daughters;
    cout  << fixed << setw(5) << events->mcNeutralinoMotherId[j];
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(7) << " ";
    cout  << fixed << setw(7) << " " << endl;
    line++;
  }//end of loop over neutralinos
  
  for (UInt_t j=0; j<events->mcGravitino_N; j++) {
    TString Daughters = " ";
    for (UInt_t k=0; k<events->mcGravitinoDaughterId.at(j).size(); k++) {
      //cout<<"bx for hit "<<k<<" is: "<<events->muDisplacedStandAloneTrackRpcHitBx.at(j).at(k)<<endl;                                                                                                    
      string each_daughter;
      ostringstream convert;
      convert<<events->mcGravitinoDaughterId.at(j).at(k);
      each_daughter = convert.str();
      Daughters = Daughters + each_daughter + " ";
    }
    
    cout  << setw(6) << events->run;
    cout  << setw(6) << events->lb;
    cout  << setw(10) << events->id;
    cout  << setw(8) << "GenGrav"<<j;
    cout  << fixed << setprecision(PtPrecision)  << setw(8) << events->mcGravitinoPt[j];
    cout  << fixed << setprecision(EtaPrecision) << setw(7) << events->mcGravitinoEta[j];
    cout  << fixed << setprecision(PhiPrecision) << setw(7) << events->mcGravitinoPhi[j];
    cout  << fixed << setprecision(ChargePrecision) << setw(7) << events->mcGravitinoCharge[j];
    cout  << fixed << setw(7) << events->mcGravitinoStatus[j];
    cout  << fixed << setw(14) << Daughters;
    cout  << fixed << setw(5) << events->mcGravitinoMotherId[j];
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(7) << " ";
    cout  << fixed << setw(7) << " " << endl;
    line++;
  }//end of loop over gravitinos
  
  for (UInt_t j=0; j<events->mcW_N; j++) {
    TString Daughters = " ";
    for (UInt_t k=0; k<events->mcWDaughterId.at(j).size(); k++) {
      //cout<<"bx for hit "<<k<<" is: "<<events->muDisplacedStandAloneTrackRpcHitBx.at(j).at(k)<<endl;                                                                                                    
      string each_daughter;
      ostringstream convert;
      convert<<events->mcWDaughterId.at(j).at(k);
      each_daughter = convert.str();
      Daughters = Daughters + each_daughter + " ";
    }
    
    cout  << setw(6) << events->run;
    cout  << setw(6) << events->lb;
    cout  << setw(10) << events->id;
    cout  << setw(8) << "GenW"<<j;
    cout  << fixed << setprecision(PtPrecision)  << setw(8) << events->mcWPt[j];
    cout  << fixed << setprecision(EtaPrecision) << setw(7) << events->mcWEta[j];
    cout  << fixed << setprecision(PhiPrecision) << setw(7) << events->mcWPhi[j];
    cout  << fixed << setprecision(ChargePrecision) << setw(7) << events->mcWCharge[j];
    cout  << fixed << setw(7) << events->mcWStatus[j];
    cout  << fixed << setw(14) << Daughters;
    cout  << fixed << setw(5) << events->mcWMotherId[j];
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(7) << " ";
    cout  << fixed << setw(7) << " " << endl;
    line++;
  }//end of loop over Ws
  
  for (UInt_t j=0; j<events->mcCMshower_N; j++) {
    TString Daughters = " ";
    for (UInt_t k=0; k<events->mcCMshowerDaughterId.at(j).size(); k++) {
      //cout<<"bx for hit "<<k<<" is: "<<events->muDisplacedStandAloneTrackRpcHitBx.at(j).at(k)<<endl;                                                                                                    
      string each_daughter;
      ostringstream convert;
      convert<<events->mcCMshowerDaughterId.at(j).at(k);
      each_daughter = convert.str();
      Daughters = Daughters + each_daughter + " ";
    }
    
    cout  << setw(6) << events->run;
    cout  << setw(6) << events->lb;
    cout  << setw(10) << events->id;
    cout  << setw(8) << "GenCMsh"<<j;
    cout  << fixed << setprecision(PtPrecision)  << setw(8) << events->mcCMshowerPt[j];
    cout  << fixed << setprecision(EtaPrecision) << setw(7) << events->mcCMshowerEta[j];
    cout  << fixed << setprecision(PhiPrecision) << setw(7) << events->mcCMshowerPhi[j];
    cout  << fixed << setprecision(ChargePrecision) << setw(7) << events->mcCMshowerCharge[j];
    cout  << fixed << setw(7) << events->mcCMshowerStatus[j];
    cout  << fixed << setw(14) << Daughters;
    cout  << fixed << setw(5) << events->mcCMshowerMotherId[j];
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(7) << " ";
    cout  << fixed << setw(7) << " " << endl;
    line++;
  }//end of loop over CMshowers
  
  for (UInt_t j=0; j<events->mcTau_N; j++) {
    TString Daughters = " ";
    for (UInt_t k=0; k<events->mcTauDaughterId.at(j).size(); k++) {
      //cout<<"bx for hit "<<k<<" is: "<<events->muDisplacedStandAloneTrackRpcHitBx.at(j).at(k)<<endl;                                                                                                    
      string each_daughter;
      ostringstream convert;
      convert<<events->mcTauDaughterId.at(j).at(k);
      each_daughter = convert.str();
      Daughters = Daughters + each_daughter + " ";
    }
    
    cout  << setw(6) << events->run;
    cout  << setw(6) << events->lb;
    cout  << setw(10) << events->id;
    cout  << setw(8) << "GenTau"<<j;
    cout  << fixed << setprecision(PtPrecision)  << setw(8) << events->mcTauPt[j];
    cout  << fixed << setprecision(EtaPrecision) << setw(7) << events->mcTauEta[j];
    cout  << fixed << setprecision(PhiPrecision) << setw(7) << events->mcTauPhi[j];
    cout  << fixed << setprecision(ChargePrecision) << setw(7) << events->mcTauCharge[j];
    cout  << fixed << setw(7) << events->mcTauStatus[j];
    cout  << fixed << setw(14) << Daughters;
    cout  << fixed << setw(5) << events->mcTauMotherId[j];
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(7) << " ";
    cout  << fixed << setw(7) << " " << endl;
    line++;
  }//end of loop over taus
  
  for (UInt_t j=0; j<events->mcMuon_N; j++) {
    TString Daughters = " ";
    for (UInt_t k=0; k<events->mcMuonDaughterId.at(j).size(); k++) {
      //cout<<"bx for hit "<<k<<" is: "<<events->muDisplacedStandAloneTrackRpcHitBx.at(j).at(k)<<endl;                                                                                                    
      string each_daughter;
      ostringstream convert;
      convert<<events->mcMuonDaughterId.at(j).at(k);
      each_daughter = convert.str();
      Daughters = Daughters + each_daughter + " ";
    }
    //if(events->mcMuonStatus[j]==1){                                                                                                                                                            
    //cout<<"For generated mu number "<<j<<",  pt is: "<<events->mcMuonPt[j]<<", eta is: "<<events->mcMuonEta[j]<<", phi is: "<<events->mcMuonPhi[j]<<", charge is: "<<events->mcMuonCharge[j]<<", mass is: "<<events->mcMuonMass[j]<<endl;                                                                                                                                                            
      
      cout  << setw(6) << events->run;
      cout  << setw(6) << events->lb;
      cout  << setw(10) << events->id;
      cout  << setw(8) << "GenMu"<<j;
      cout  << fixed << setprecision(PtPrecision)  << setw(8) << events->mcMuonPt[j];
      cout  << fixed << setprecision(EtaPrecision) << setw(7) << events->mcMuonEta[j];
      cout  << fixed << setprecision(PhiPrecision) << setw(7) << events->mcMuonPhi[j];
      cout  << fixed << setprecision(ChargePrecision) << setw(7) << events->mcMuonCharge[j];
      cout  << fixed << setw(7) << events->mcMuonStatus[j];
      cout  << fixed << setw(14) << Daughters;
      cout  << fixed << setw(5) << events->mcMuonMotherId[j];
      if(events->mcMuonMotherOfWId[j]==-999) cout  << fixed << setw(5) << " ";
      else cout  << fixed << setw(5) << events->mcMuonMotherOfWId[j];
      cout  << fixed << setw(5) << events->mcMuonVx[j];
      cout  << fixed << setw(5) << events->mcMuonVy[j];
      cout  << fixed << setw(5) << events->mcMuonVz[j];
      cout  << fixed << setw(5) << " ";
      cout  << fixed << setw(5) << " ";
      cout  << fixed << setw(7) << " ";
      cout  << fixed << setw(7) << " " << endl;
      line++;
  }//end of loop over mc muons

  for (UInt_t j=0; j<events->simTrack_N; j++) {
    if(TMath::Abs(events->simTrackPdgId[j])==13){
      //cout<<"For sim track number "<<j<<",  pt is: "<<events->simTrackPt[j]<<", eta is: "<<events->simTrackEta[j]<<", phi is: "<<events->simTrackPhi[j]<<", charge is: "<<events->simTrackCharge[j]<<", mass is: "<<events->simTrackMass[j]<<endl;                                                                                                                                                                  
      cout  << setw(6) << events->run;
      cout  << setw(6) << events->lb;
      cout  << setw(10) << events->id;
      cout  << setw(8) << "SimTrack"<<j;
      cout  << fixed << setprecision(PtPrecision)  << setw(8) << events->simTrackPt[j];
      cout  << fixed << setprecision(EtaPrecision) << setw(7) << events->simTrackEta[j];
      cout  << fixed << setprecision(PhiPrecision) << setw(7) << events->simTrackPhi[j];
      cout  << fixed << setprecision(ChargePrecision) << setw(7) << events->simTrackCharge[j];
      cout  << fixed << setw(7) << " ";
      cout  << fixed << setw(14) << " ";
      cout  << fixed << setw(5) << events->simTrackPdgId[j];
      cout  << fixed << setw(5) << " ";
      cout  << fixed << setw(5) << events->simTrackVx[j];
      cout  << fixed << setw(5) << events->simTrackVy[j];
      cout  << fixed << setw(5) << events->simTrackVz[j];
      cout  << fixed << setw(5) << " ";
      cout  << fixed << setw(5) << " ";
      cout  << fixed << setw(7) << " ";
      cout  << fixed << setw(7) << " " << endl;
      line++;
    }//end of if sim tracks correspond to gen muon
  }//end of loop over mc muons

}//end of printout_gen()

void findTreevalues_makehistos_Ntuples_allsamples::printout_DSA( StoppedHSCPMuonEvent* events){
  //cout<<"__________________________________________________________________________________________________________________________________________________________"<<endl;
  //line++;

  for (UInt_t j=0; j<events->mu_DisplacedStandAlone_N; j++) {
    TString BXs = " ";
    for (UInt_t k=0; k<events->muDisplacedStandAloneTrackRpcHitZ.at(j).size(); k++) {
      //cout<<"bx for hit "<<k<<" is: "<<events->muDisplacedStandAloneTrackRpcHitBx.at(j).at(k)<<endl;                                                                                                
      string each_bx;
      ostringstream convert;
      convert<<events->muDisplacedStandAloneTrackRpcHitBx.at(j).at(k);
      each_bx = convert.str();
      //cout<<"each_bx for hit "<<k<<" is: "<<each_bx<<endl;                                                                                                                                 
      BXs = BXs + each_bx + " ";
    }
    //cout<<"BXs is: "<<BXs<<endl;                                                                                                                                                           

    //double segment_dPhi, segment_dEta;
    //double segment_dR = dR_OppositeSeg(events, j, segment_dPhi, segment_dEta);

    cout  << setw(6) << events->run;
    cout  << setw(6) << events->lb;
    cout  << setw(10) << events->id;
    cout  << setw(8) << "DSA"<<j;
    cout  << fixed << setprecision(PtPrecision)  << setw(8) << events->muDisplacedStandAlonePt[j];
    cout  << fixed << setprecision(EtaPrecision) << setw(7) << events->muDisplacedStandAloneEta[j];
    cout  << fixed << setprecision(PhiPrecision) << setw(7) << events->muDisplacedStandAlonePhi[j];
    cout  << fixed << setprecision(ChargePrecision) << setw(7) << events->muDisplacedStandAloneCharge[j];
    cout  << fixed << setprecision(X2DOFPrecision) << setw(7) << events->muDisplacedStandAloneTrackNormalizedChi2[j];
    cout  << fixed << setw(14) << BXs;
    cout  << fixed << setw(5) << events->muDisplacedStandAloneTrackNValidMuonHits[j];
    cout  << fixed << setw(5) << events->muDisplacedStandAloneTrackNValidCscHits[j];
    cout  << fixed << setw(5) << events->muDisplacedStandAloneTrackNValidDtHits[j];
    cout  << fixed << setw(5) << events->muDisplacedStandAloneTrackRpcHitZ.at(j).size();
    cout  << fixed << setw(5) << events->muDisplacedStandAloneTrackNStationsWithValidHits[j];
    cout  << fixed << setw(5) << events->muDisplacedStandAloneTrackNCscChambersWithValidHits[j];
    cout  << fixed << setw(5) << events->muDisplacedStandAloneTrackNDtChambersWithValidHits[j];
    cout  << fixed << setw(5) << events->muDisplacedStandAloneTrackNRpcChambersWithValidHits[j];
    cout  << fixed << setw(5) << events->muDisplacedStandAloneTrackDtTofDirection[j];
    cout  << fixed << setprecision(TimeAtIpInOutPrecision) << setw(7) << events->muDisplacedStandAloneTrackDtTofTimeAtIpInOut[j];
    cout  << fixed << setw(11) << events->muDisplacedStandAloneTrackDtTofTimeAtIpInOutErr[j];
    cout  << fixed << setw(7) << events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[j];
    cout  << fixed << setw(11) << events->muDisplacedStandAloneTrackDtTofFreeInverseBetaErr[j];
    cout  << fixed << setw(5) << events->muDisplacedStandAloneTrackDtTofNDof[j]<<endl;
    //cout  << fixed << setw(5) << events->muDisplacedStandAloneTrackGlobalMuonIndex[j]<<endl;   
    line++;
  }//end of loop over DSA muons
}//end of printout_DSA()

void findTreevalues_makehistos_Ntuples_allsamples::printout_SA( StoppedHSCPMuonEvent* events){
  //cout<<"__________________________________________________________________________________________________________________________________________________________"<<endl;
  //line++;

  for (UInt_t j=0; j<events->mu_StandAlone_N; j++) {
    TString BXs = " ";
    for (UInt_t k=0; k<events->muStandAloneTrackRpcHitZ.at(j).size(); k++) {
      //cout<<"bx for hit "<<k<<" is: "<<events->muStandAloneTrackRpcHitBx.at(j).at(k)<<endl;                                                                                                
      string each_bx;
      ostringstream convert;
      convert<<events->muStandAloneTrackRpcHitBx.at(j).at(k);
      each_bx = convert.str();
      //cout<<"each_bx for hit "<<k<<" is: "<<each_bx<<endl;                                                                                                                                 
      BXs = BXs + each_bx + " ";
    }
    //cout<<"BXs is: "<<BXs<<endl;                                                                                                                                                           

    //double segment_dPhi, segment_dEta;
    //double segment_dR = dR_OppositeSeg(events, j, segment_dPhi, segment_dEta);

    cout  << setw(6) << events->run;
    cout  << setw(6) << events->lb;
    cout  << setw(10) << events->id;
    cout  << setw(8) << "SA"<<j;
    cout  << fixed << setprecision(PtPrecision)  << setw(8) << events->muStandAlonePt[j];
    cout  << fixed << setprecision(EtaPrecision) << setw(7) << events->muStandAloneEta[j];
    cout  << fixed << setprecision(PhiPrecision) << setw(7) << events->muStandAlonePhi[j];
    cout  << fixed << setprecision(ChargePrecision) << setw(7) << events->muStandAloneCharge[j];
    cout  << fixed << setprecision(X2DOFPrecision) << setw(7) << events->muStandAloneTrackNormalizedChi2[j];
    cout  << fixed << setw(14) << BXs;
    cout  << fixed << setw(5) << events->muStandAloneTrackNValidMuonHits[j];
    cout  << fixed << setw(5) << events->muStandAloneTrackNValidCscHits[j];
    cout  << fixed << setw(5) << events->muStandAloneTrackNValidDtHits[j];
    cout  << fixed << setw(5) << events->muStandAloneTrackRpcHitZ.at(j).size();
    cout  << fixed << setw(5) << events->muStandAloneTrackNStationsWithValidHits[j];
    cout  << fixed << setw(5) << events->muStandAloneTrackNCscChambersWithValidHits[j];
    cout  << fixed << setw(5) << events->muStandAloneTrackNDtChambersWithValidHits[j];
    cout  << fixed << setw(5) << events->muStandAloneTrackNRpcChambersWithValidHits[j];
    cout  << fixed << setw(5) << events->muStandAloneTrackDtTofDirection[j];
    cout  << fixed << setprecision(TimeAtIpInOutPrecision) << setw(7) << events->muStandAloneTrackDtTofTimeAtIpInOut[j];
    cout  << fixed << setw(11) << events->muStandAloneTrackDtTofTimeAtIpInOutErr[j];
    cout  << fixed << setw(7) << events->muStandAloneTrackDtTofFreeInverseBeta[j];
    cout  << fixed << setw(11) << events->muStandAloneTrackDtTofFreeInverseBetaErr[j];
    cout  << fixed << setw(5) << events->muStandAloneTrackDtTofNDof[j]<<endl;
    line++;
  }//end of loop over SA muons
}//end of printout_SA()

void findTreevalues_makehistos_Ntuples_allsamples::printout_SA_UpdatedAtVtx( StoppedHSCPMuonEvent* events){
  //cout<<"__________________________________________________________________________________________________________________________________________________________"<<endl;
  //line++;

  for (UInt_t j=0; j<events->mu_StandAloneUpdatedAtVtx_N; j++) {
    TString BXs = " ";
    for (UInt_t k=0; k<events->muStandAloneTrackUpdatedAtVtxRpcHitZ.at(j).size(); k++) {
      //cout<<"bx for hit "<<k<<" is: "<<events->muStandAloneTrackUpdatedAtVtxRpcHitBx.at(j).at(k)<<endl;                                                                                                
      string each_bx;
      ostringstream convert;
      convert<<events->muStandAloneTrackUpdatedAtVtxRpcHitBx.at(j).at(k);
      each_bx = convert.str();
      //cout<<"each_bx for hit "<<k<<" is: "<<each_bx<<endl;                                                                                                                                 
      BXs = BXs + each_bx + " ";
    }
    //cout<<"BXs is: "<<BXs<<endl;                                                                                                                                                           

    //double segment_dPhi, segment_dEta;
    //double segment_dR = dR_OppositeSeg(events, j, segment_dPhi, segment_dEta);

    cout  << setw(6) << events->run;
    cout  << setw(6) << events->lb;
    cout  << setw(10) << events->id;
    cout  << setw(8) << "SA_v"<<j;
    cout  << fixed << setprecision(PtPrecision)  << setw(8) << events->muStandAloneUpdatedAtVtxPt[j];
    cout  << fixed << setprecision(EtaPrecision) << setw(7) << events->muStandAloneUpdatedAtVtxEta[j];
    cout  << fixed << setprecision(PhiPrecision) << setw(7) << events->muStandAloneUpdatedAtVtxPhi[j];
    cout  << fixed << setprecision(ChargePrecision) << setw(7) << events->muStandAloneUpdatedAtVtxCharge[j];
    cout  << fixed << setprecision(X2DOFPrecision) << setw(7) << events->muStandAloneTrackUpdatedAtVtxNormalizedChi2[j];
    cout  << fixed << setw(14) << BXs;
    cout  << fixed << setw(5) << events->muStandAloneTrackUpdatedAtVtxNValidMuonHits[j];
    cout  << fixed << setw(5) << events->muStandAloneTrackUpdatedAtVtxNValidCscHits[j];
    cout  << fixed << setw(5) << events->muStandAloneTrackUpdatedAtVtxNValidDtHits[j];
    cout  << fixed << setw(5) << events->muStandAloneTrackUpdatedAtVtxRpcHitZ.at(j).size();
    cout  << fixed << setw(5) << events->muStandAloneTrackUpdatedAtVtxNStationsWithValidHits[j];
    cout  << fixed << setw(5) << events->muStandAloneTrackUpdatedAtVtxNCscChambersWithValidHits[j];
    cout  << fixed << setw(5) << events->muStandAloneTrackUpdatedAtVtxNDtChambersWithValidHits[j];
    cout  << fixed << setw(5) << events->muStandAloneTrackUpdatedAtVtxNRpcChambersWithValidHits[j];
    cout  << fixed << setw(5) << events->muStandAloneTrackUpdatedAtVtxDtTofDirection[j];
    cout  << fixed << setprecision(TimeAtIpInOutPrecision) << setw(7) << events->muStandAloneTrackUpdatedAtVtxDtTofTimeAtIpInOut[j];
    cout  << fixed << setw(11) << events->muStandAloneTrackUpdatedAtVtxDtTofTimeAtIpInOutErr[j];
    cout  << fixed << setw(7) << events->muStandAloneTrackUpdatedAtVtxDtTofFreeInverseBeta[j];
    cout  << fixed << setw(11) << events->muStandAloneTrackUpdatedAtVtxDtTofFreeInverseBetaErr[j];
    cout  << fixed << setw(5) << events->muStandAloneTrackUpdatedAtVtxDtTofNDof[j]<<endl;
    line++;
  }//end of loop over SA muons
}//end of printout_SA()


void findTreevalues_makehistos_Ntuples_allsamples::printout_RSA( StoppedHSCPMuonEvent* events){
  //cout<<"__________________________________________________________________________________________________________________________________________________________"<<endl; 
  //line++; 

  for (UInt_t j=0; j<events->mu_RefittedStandAlone_N; j++) {
    //TString BXs = " ";
    //for (UInt_t k=0; k<events->muRefittedStandAloneTrackRpcHitZ.at(j).size(); k++) {
      //cout<<"bx for hit "<<k<<" is: "<<events->muRefittedStandAloneTrackRpcHitBx.at(j).at(k)<<endl; 
      //string each_bx;
      //ostringstream convert;
      //convert<<events->muRefittedStandAloneTrackRpcHitBx.at(j).at(k);
      //each_bx = convert.str();
      //cout<<"each_bx for hit "<<k<<" is: "<<each_bx<<endl; 
      //BXs = BXs + each_bx + " ";
    //}
    //cout<<"BXs is: "<<BXs<<endl; 

    //double segment_dPhi, segment_dEta;
    //double segment_dR = dR_OppositeSeg(events, j, segment_dPhi, segment_dEta); 

    cout  << setw(6) << events->run;
    cout  << setw(6) << events->lb;
    cout  << setw(10) << events->id;
    cout  << setw(8) << "RSA"<<j;
    cout  << fixed << setprecision(PtPrecision)  << setw(8) << events->muRefittedStandAlonePt[j];
    cout  << fixed << setprecision(EtaPrecision) << setw(7) << events->muRefittedStandAloneEta[j];
    cout  << fixed << setprecision(PhiPrecision) << setw(7) << events->muRefittedStandAlonePhi[j];
    cout  << fixed << setprecision(ChargePrecision) << setw(7) << events->muRefittedStandAloneCharge[j];
    cout  << fixed << setprecision(X2DOFPrecision) << setw(7) << events->muRefittedStandAloneTrackNormalizedChi2[j];
    //cout  << fixed << setw(14) << BX;
    cout  << fixed << setw(14) << " ";
    cout  << fixed << setw(5) << events->muRefittedStandAloneTrackNValidMuonHits[j];
    cout  << fixed << setw(5) << events->muRefittedStandAloneTrackNValidCscHits[j];
    cout  << fixed << setw(5) << events->muRefittedStandAloneTrackNValidDtHits[j];
    //cout  << fixed << setw(5) << events->muRefittedStandAloneTrackRpcHitZ.at(j).size();
    cout  << fixed << setw(5) << events->muRefittedStandAloneTrackNValidRpcHits[j];
    cout  << fixed << setw(5) << events->muRefittedStandAloneTrackNStationsWithValidHits[j];
    cout  << fixed << setw(5) << events->muRefittedStandAloneTrackNCscChambersWithValidHits[j];
    cout  << fixed << setw(5) << events->muRefittedStandAloneTrackNDtChambersWithValidHits[j];
    cout  << fixed << setw(5) << events->muRefittedStandAloneTrackNRpcChambersWithValidHits[j];
    //cout  << fixed << setw(5) << events->muRefittedStandAloneTofDirection[j];
    cout  << fixed << setw(5) << " ";
    //cout  << fixed << setprecision(TimeAtIpInOutPrecision) << setw(7) << events->muRefittedStandAloneTofTimeAtIpInOut[j];
    cout  << fixed << setprecision(TimeAtIpInOutPrecision) << setw(7) << " ";
    cout  << fixed << setw(7) << " ";
    cout  << fixed << setw(7) << " ";
    cout  << fixed << setw(11) << " ";
    //cout  << fixed << setw(5) << segment_dEta << endl;
    //cout  << fixed << setw(5) << segment_dPhi << endl;
    cout  << fixed << setw(5) << " " << endl;
    line++;
  }//end of loop over RSA muons
}//end of printout_RSA()

void findTreevalues_makehistos_Ntuples_allsamples::printout_cosmic( StoppedHSCPMuonEvent* events){
  //cout<<"__________________________________________________________________________________________________________________________________________________________"<<endl; 
  //line++;

  for (UInt_t j=0; j<events->mu_Cosmic_N; j++) {
    //TString BXs = " ";
    //for (UInt_t k=0; k<events->muCosmicTrackRpcHitZ.at(j).size(); k++) {
      //cout<<"bx for hit "<<k<<" is: "<<events->muCosmicTrackRpcHitBx.at(j).at(k)<<endl; 
      //string each_bx;
      //ostringstream convert;
      //convert<<events->muCosmicTrackRpcHitBx.at(j).at(k);
      //each_bx = convert.str();
      //cout<<"each_bx for hit "<<k<<" is: "<<each_bx<<endl; 
      //BXs = BXs + each_bx + " ";
    //}
    //cout<<"BXs is: "<<BXs<<endl;

    //double segment_dPhi, segment_dEta;
    //double segment_dR = dR_OppositeSeg(events, j, segment_dPhi, segment_dEta); 

    cout  << setw(6) << events->run;
    cout  << setw(6) << events->lb;
    cout  << setw(10) << events->id;
    cout  << setw(8) << "Cos"<<j;
    cout  << fixed << setprecision(PtPrecision)  << setw(8) << events->muCosmicTrackPt[j];
    cout  << fixed << setprecision(EtaPrecision) << setw(7) << events->muCosmicTrackEta[j];
    cout  << fixed << setprecision(PhiPrecision) << setw(7) << events->muCosmicTrackPhi[j];
    cout  << fixed << setprecision(ChargePrecision) << setw(7) << events->muCosmicTrackCharge[j];
    cout  << fixed << setprecision(X2DOFPrecision) << setw(7) << events->muCosmicTrackNormalizedChi2[j];
    //cout  << fixed << setw(14) << BXs;
    cout  << fixed << setw(14) << " ";
    cout  << fixed << setw(5) << events->muCosmicTrackNValidMuonHits[j];
    cout  << fixed << setw(5) << events->muCosmicTrackNValidCscHits[j];
    cout  << fixed << setw(5) << events->muCosmicTrackNValidDtHits[j];
    //cout  << fixed << setw(5) << events->muCosmicTrackRpcHitZ.at(j).size();
    cout  << fixed << setw(5) << events->muCosmicTrackNValidRpcHits[j];
    cout  << fixed << setw(5) << events->muCosmicTrackNStationsWithValidHits[j];
    cout  << fixed << setw(5) << events->muCosmicTrackNCscChambersWithValidHits[j];
    cout  << fixed << setw(5) << events->muCosmicTrackNDtChambersWithValidHits[j];
    cout  << fixed << setw(5) << events->muCosmicTrackNRpcChambersWithValidHits[j];
    //cout  << fixed << setw(5) << events->muCosmicTofDirection[j];
    cout  << fixed << setw(5) << " ";
    //cout  << fixed << setprecision(TimeAtIpInOutPrecision) << setw(7) << events->muCosmicTofTimeAtIpInOut[j];
    cout  << fixed << setw(7) << " ";
    cout  << fixed << setw(7) << " ";
    cout  << fixed << setw(7) << " ";
    cout  << fixed << setw(11) << " ";
    //cout  << fixed << setw(5) << segment_dEta << endl;
    //cout  << fixed << setw(5) << segment_dPhi << endl;
    cout  << fixed << setw(5) << " " << endl;
    line++;
  }//end of loop over cosmic muons
}//end of printout_cosmic()

void findTreevalues_makehistos_Ntuples_allsamples::printout_tuneP_global( StoppedHSCPMuonEvent* events){
  //cout<<"__________________________________________________________________________________________________________________________________________________________"<<endl; 
  //line++;

  for (UInt_t j=0; j<events->mu_N; j++) {	    
    //TString BXs = " ";
    //for (UInt_t k=0; k<events->muTunePglobalTrackRpcHitZ.at(j).size(); k++) {
      //cout<<"bx for hit "<<k<<" is: "<<events->muTunePglobalTrackRpcHitBx.at(j).at(k)<<endl; 
      //string each_bx;
      //ostringstream convert;
      //convert<<events->muTunePglobalTrackRpcHitBx.at(j).at(k);
      //each_bx = convert.str();
      //cout<<"each_bx for hit "<<k<<" is: "<<each_bx<<endl; 
      //BXs = BXs + each_bx + " ";
    //}
    //cout<<"BXs is: "<<BXs<<endl;

    //double segment_dPhi, segment_dEta;
    //double segment_dR = dR_OppositeSeg(events, j, segment_dPhi, segment_dEta); 

    cout  << setw(6) << events->run;
    cout  << setw(6) << events->lb;
    cout  << setw(10) << events->id;
    cout  << setw(8) << "Glo"<<j;
    cout  << fixed << setprecision(PtPrecision)  << setw(8) << events->muTunePpt[j];
    cout  << fixed << setprecision(EtaPrecision) << setw(7) << events->muTunePeta[j];
    cout  << fixed << setprecision(PhiPrecision) << setw(7) << events->muTunePphi[j];
    cout  << fixed << setprecision(ChargePrecision) << setw(7) << events->muTunePcharge[j];
    cout  << fixed << setprecision(X2DOFPrecision) << setw(7) << events->muTunePnormalizedChi2[j];
    //cout  << fixed << setw(14) << BXs;
    cout  << fixed << setw(14) << " ";
    cout  << fixed << setw(5) << events->muIsTrackerMuon[j]; 
    cout  << fixed << setw(5) << events->muIsStandAloneMuon[j]; 
    cout  << fixed << setw(5) << events->muIsGlobalMuon[j];  
    //cout  << fixed << setw(5) << events->muTunePNValidMuonHits[j]; 
    //cout  << fixed << setw(5) << events->muTunePNValidCscHits[j];  
    //cout  << fixed << setw(5) << events->muTunePNValidDtHits[j];
    //cout  << fixed << setw(5) << events->muTunePRpcHitZ.at(j).size();
    //cout  << fixed << setw(5) << events->muTunePNValidRpcHits[j];
    //cout  << fixed << setw(5) << events->muTunePNStationsWithValidHits[j];
    //cout  << fixed << setw(5) << events->muTunePNCscChambersWithValidHits[j];
    if(events->muIsStandAloneMuon[j]) cout  << fixed << setw(5) << events->muSAnDtChambersWithValidHits[j];
    //cout  << fixed << setw(5) << events->muTunePNRpcChambersWithValidHits[j];
    //cout  << fixed << setw(5) << events->muTunePglobalTofDirection[j];
    cout  << fixed << setw(5) << " ";
    //cout  << fixed << setprecision(TimeAtIpInOutPrecision) << setw(7) << events->muTunePglobalTofTimeAtIpInOut[j];
    cout  << fixed << setw(7) << " ";
    cout  << fixed << setw(7) << " ";
    cout  << fixed << setw(7) << " ";
    cout  << fixed << setw(11) << " ";
    //cout  << fixed << setw(5) << segment_dEta << endl;
    //cout  << fixed << setw(5) << segment_dPhi << endl;
    cout  << fixed << setw(5) << " " << endl;
    line++;
  }//end of loop over tunePglobal muons
}//end of printout_tunePglobal()

void findTreevalues_makehistos_Ntuples_allsamples::printout_L2( StoppedHSCPMuonEvent* events){
  //cout<<"__________________________________________________________________________________________________________________________________________________________"<<endl;
  //line++;

  for (UInt_t j=0; j<events->hlt20Cha2Muon_N; j++) {
    cout  << setw(6) << events->run;
    cout  << setw(6) << events->lb;
    cout  << setw(10) << events->id;
    cout  << setw(8) << "L2 "<<j;
    cout  << fixed << setprecision(PtPrecision)  << setw(8) << events->hlt20Cha2MuonPt[j];
    cout  << fixed << setprecision(EtaPrecision) << setw(7) << events->hlt20Cha2MuonEta[j];
    cout  << fixed << setprecision(PhiPrecision) << setw(7) << events->hlt20Cha2MuonPhi[j]<<endl;
    line++;
  }//end of loop over L2 muons

  for (UInt_t j=0; j<events->hlt20Muon_N; j++) {
    cout  << setw(7) << events->run;
    cout  << setw(6) << events->lb;
    cout  << setw(9) << events->id;
    cout  << setw(8) << "L2 "<<j;
    cout  << fixed << setprecision(PtPrecision)  << setw(8) << events->hlt20MuonPt[j];
    cout  << fixed << setprecision(EtaPrecision) << setw(7) << events->hlt20MuonEta[j];
    cout  << fixed << setprecision(PhiPrecision) << setw(7) << events->hlt20MuonPhi[j]<<endl;
    line++;
  }//end of loop over L2 muons

}//end of printout_L2()

void findTreevalues_makehistos_Ntuples_allsamples::printout_L1( StoppedHSCPMuonEvent* events){
  //cout<<"__________________________________________________________________________________________________________________________________________________________"<<endl;
  //line++;

  for (UInt_t j=0; j<events->l1Muon_N; j++) {
    cout  << setw(6) << events->run;
    cout  << setw(6) << events->lb;
    cout  << setw(10) << events->id;
    cout  << setw(8) << "L1 "<<j;
    cout  << fixed << setprecision(PtPrecision)  << setw(8) << events->l1MuonPt[j];
    cout  << fixed << setprecision(EtaPrecision) << setw(7) << events->l1MuonEta[j];
    cout  << fixed << setprecision(PhiPrecision) << setw(7) << events->l1MuonPhi[j]<<endl;
    line++;
  }//end of loop over L1 muons
}//end of printout_L1()


int main(int argc, char* argv[]){
  if(argc!=64){
    cout<<"ERROR, need more arguments!"<<endl;
    cout<<"seeing "<<argc<<" arguments"<<endl;
    return 1;
  }

  string file_dataset, BxCut, CavCut, GenMuCut, SACut, GenMuMatchedCut, TriggerCut, TriggerTurnOn_, NdsaCut, PtCut, ChaCut, EtaCut, UpperCut, RpcCut, DisStCut, RpcBxCut, DtHitsCut, InvBetaErrCut, CscHitsCut, DtInvBetaCut, TimeInOutCut, TimeInOutErrCut, DeltaTimeInOutCut, DeltaDtInvBetaCut, TofDirCut, OppEtaCut, OppPhiCut, ChargeCut, DxyCut, TightPhi, CosEnrich, resT3, Printout;
  TString PreNdsaCutValue, PrePtCutValue, PreChaCutValue, PreEtaCutValue, PreRpcCutValue, PreRpcBxCutValue, PreDtHitsCutValue, PreInvBetaErrCutValue, PreCscHitsCutValue;
  TString BxCutValue, PtCutValue, ChaCutValue, EtaCutValue, RpcCutValue, DisStCutValue, RpcBxCutValue, DtHitsCutValue, CscHitsCutValue, DtInvBetaCutValue, TimeInOutCutValue, TimeInOutErrCutValue, DeltaTimeInOutCutValue, DeltaDtInvBetaCutValue, OppEtaCutValue, OppPhiCutValue, DxyCutValue;
  TString abcdInvBetaCutValue, abcdPtCutValue, abInvBetaCutValue, cInvBetaCutValue, acPtCutValue, bPtCutValue;

  file_dataset = "NoBPTX_Run2012B";
  BxCut = "wBxCut";
  CavCut = "wCavCut";
  GenMuCut = "wGenMuCut";
  SACut = "wSACut";
  GenMuMatchedCut = "wGenMuMatchedCut";
  TriggerCut = "wTriggerCut";
  TriggerTurnOn_ = "wTriggerTurnOn";
  NdsaCut = "wNdsaCut";
  PtCut = "wPtCut";
  ChaCut = "wChaCut";
  EtaCut = "wEtaCut";
  UpperCut = "wUpperCut";
  RpcCut = "wRpcCut";
  DisStCut = "wDisStCut";
  RpcBxCut = "wRpcBxCut";
  DtHitsCut = "wDtHitsCut";
  InvBetaErrCut = "wInvBetaErrCut";
  CscHitsCut = "wCscHitsCut";
  DtInvBetaCut = "wDtInvBetaCut";
  TimeInOutCut = "wTimeInOutCut";
  TimeInOutErrCut = "wTimeInOutErrCut";
  DeltaTimeInOutCut = "wDeltaTimeInOutCut";
  DeltaDtInvBetaCut = "wDeltaDtInvBetaCut";
  TofDirCut = "wTofDirCut";
  OppEtaCut = "wOppEtaCut";
  OppPhiCut = "wOppPhiCut";
  ChargeCut = "wChargeCut";
  DxyCut = "wDxyCut";
  TightPhi = "wTightPhi";
  CosEnrich = "wCosEnrich";
  resT3 = "T3";
  Printout = "wPrintout";

  BxCutValue = "2";
  PreNdsaCutValue = "6";
  PrePtCutValue = "30.";
  PreChaCutValue = "1";
  PreEtaCutValue = "1.0";
  PreRpcCutValue = "2";
  PreDtHitsCutValue = "8";
  PreInvBetaErrCutValue = "10";
  PreCscHitsCutValue = "0";

  PtCutValue = "30.";
  ChaCutValue = "1";
  EtaCutValue = "1.0";
  RpcCutValue = "2";
  DisStCutValue = "2";
  DtHitsCutValue = "8";
  CscHitsCutValue = "0";
  DtInvBetaCutValue = "0.7";
  TimeInOutCutValue = "0.";
  TimeInOutErrCutValue = "2.";
  DeltaTimeInOutCutValue = "-20.";
  DeltaDtInvBetaCutValue = "-1.";
  OppEtaCutValue = "0.1";
  OppPhiCutValue = "0.1";
  DxyCutValue = "50";

  abcdInvBetaCutValue = "0.0";
  abcdPtCutValue = "100.";
  abInvBetaCutValue = "0.0";
  cInvBetaCutValue = "0.0";
  acPtCutValue = "100.";
  bPtCutValue = "100.";

  if(argc==64){
    file_dataset = argv[1];
    BxCut = argv[2];
    CavCut = argv[3];
    GenMuCut = argv[4];
    SACut = argv[5];
    GenMuMatchedCut = argv[6];
    TriggerCut = argv[7];
    TriggerTurnOn_ = argv[8];
    NdsaCut = argv[9];
    PtCut = argv[10];
    ChaCut = argv[11];
    EtaCut = argv[12];
    UpperCut = argv[13];
    RpcCut = argv[14];
    DisStCut = argv[15];
    RpcBxCut = argv[16];
    DtHitsCut = argv[17];
    InvBetaErrCut = argv[18];
    CscHitsCut = argv[19];
    DtInvBetaCut = argv[20];
    TimeInOutCut = argv[21];
    TimeInOutErrCut = argv[22];
    DeltaTimeInOutCut = argv[23];
    DeltaDtInvBetaCut = argv[24];
    TofDirCut = argv[25];
    OppEtaCut = argv[26];
    OppPhiCut = argv[27];
    ChargeCut = argv[28];
    DxyCut = argv[29];
    TightPhi = argv[30];
    CosEnrich = argv[31];
    resT3 = argv[32];
    Printout = argv[33];

    BxCutValue = argv[34];

    PreNdsaCutValue = argv[35]; 
    PrePtCutValue = argv[36]; 
    PreChaCutValue = argv[37]; 
    PreEtaCutValue = argv[38]; 
    PreRpcCutValue = argv[39]; 
    PreDtHitsCutValue = argv[40]; 
    PreInvBetaErrCutValue = argv[41]; 
    PreCscHitsCutValue = argv[42]; 

    PtCutValue = argv[43];
    ChaCutValue = argv[44];
    EtaCutValue = argv[45];
    RpcCutValue = argv[46];
    DisStCutValue = argv[47];
    DtHitsCutValue = argv[48];
    CscHitsCutValue = argv[49];
    DtInvBetaCutValue = argv[50];
    TimeInOutCutValue = argv[51];
    TimeInOutErrCutValue = argv[52];
    DeltaTimeInOutCutValue = argv[53];
    DeltaDtInvBetaCutValue = argv[54];
    OppEtaCutValue = argv[55];
    OppPhiCutValue = argv[56];
    DxyCutValue = argv[57];

    abcdInvBetaCutValue = argv[58];
    abcdPtCutValue = argv[59];
    abInvBetaCutValue = argv[60];
    cInvBetaCutValue = argv[61];
    acPtCutValue = argv[62];
    bPtCutValue = argv[63];

    cout<<", file_dataset is: "<<file_dataset<<", BxCut is: "<<BxCut<<", CavCut is: "<<CavCut<<", GenMuCut is: "<<GenMuCut<<", SA cut is: "<<SACut<<", GenMuMatchedCut is; "<<GenMuMatchedCut<<", TriggerCut is: "<<TriggerCut<<", TriggerTurnOn_ is: "<<TriggerTurnOn_<<", PtCut is: "<<PtCut<<", ChaCut is: "<<ChaCut<<", EtaCut is: "<<EtaCut<<", UpperCut is: "<<UpperCut<<", RpcCut is: "<<RpcCut<<", DisStCut is: "<<DisStCut<<", RpcBxCut is: "<<RpcBxCut<<", DtHitsCut is: "<<DtHitsCut<<", CscHitsCut is: "<<CscHitsCut<<", DtInvBetaCut is: "<<DtInvBetaCut<<", TimeInOutCut is: "<<TimeInOutCut<<", TimeInOutErrCut is: "<<TimeInOutErrCut<<", DeltaTimeInOutCut is: "<<DeltaTimeInOutCut<<", DeltaDtInvBetaCut is: "<<DeltaDtInvBetaCut<<", OppEtaCut is: "<<OppEtaCut<<", OppPhiCut is: "<<OppPhiCut<<", ChargeCut is: "<<ChargeCut<<", OppPhiCutValue is: "<<OppPhiCutValue<<", TightPhi is: "<<TightPhi<<", CosEnrich is: "<<CosEnrich<<", resT3 is: "<<resT3<<", Printout is "<<Printout<<endl;
  }

  TH1D::SetDefaultSumw2();

  cout<<"set default sumw2"<<endl;
  findTreevalues_makehistos_Ntuples_allsamples analyzer(argc, argv);

  cout<<"just before analyzer.loop"<<endl;
  analyzer.loop(file_dataset, BxCut, CavCut, GenMuCut, SACut, GenMuMatchedCut, TriggerCut, TriggerTurnOn_, NdsaCut, PtCut, ChaCut, EtaCut, UpperCut, RpcCut, DisStCut, RpcBxCut, DtHitsCut, InvBetaErrCut, CscHitsCut, DtInvBetaCut, TimeInOutCut, TimeInOutErrCut, DeltaTimeInOutCut, DeltaDtInvBetaCut, TofDirCut, OppEtaCut, OppPhiCut, ChargeCut, DxyCut, TightPhi, CosEnrich, resT3, Printout, BxCutValue, PreNdsaCutValue, PrePtCutValue, PreChaCutValue, PreEtaCutValue, PreRpcCutValue, PreDtHitsCutValue, PreInvBetaErrCutValue, PreCscHitsCutValue, PtCutValue, ChaCutValue, EtaCutValue, RpcCutValue, DisStCutValue, DtHitsCutValue, CscHitsCutValue, DtInvBetaCutValue, TimeInOutCutValue, TimeInOutErrCutValue, DeltaTimeInOutCutValue, DeltaDtInvBetaCutValue, OppEtaCutValue, OppPhiCutValue, DxyCutValue, abcdInvBetaCutValue, abcdPtCutValue, abInvBetaCutValue, cInvBetaCutValue, acPtCutValue, bPtCutValue);
}

void findTreevalues_makehistos_Ntuples_allsamples::loop(string& file_dataset, string& BxCut, string& CavCut, string& GenMuCut, string& SACut, string& GenMuMatchedCut, string& TriggerCut, string& TriggerTurnOn_, string& NdsaCut, string& PtCut, string& ChaCut, string& EtaCut, string& UpperCut, string& RpcCut, string& DisStCut, string& RpcBxCut, string& DtHitsCut, string& InvBetaErrCut, string& CscHitsCut, string& DtInvBetaCut, string& TimeInOutCut, string& TimeInOutErrCut, string& DeltaTimeInOutCut, string& DeltaDtInvBetaCut, string& TofDirCut, string& OppEtaCut, string& OppPhiCut, string& ChargeCut, string& DxyCut, string& TightPhi, string& CosEnrich, string& resT3, string& Printout, TString& BxCutValue, TString& PreNdsaCutValue, TString& PrePtCutValue, TString& PreChaCutValue, TString& PreEtaCutValue, TString& PreRpcCutValue, TString& PreDtHitsCutValue, TString& PreInvBetaErrCutValue, TString& PreCscHitsCutValue, TString& PtCutValue, TString& ChaCutValue, TString& EtaCutValue, TString& RpcCutValue, TString& DisStCutValue, TString& DtHitsCutValue, TString& CscHitsCutValue, TString& DtInvBetaCutValue, TString& TimeInOutCutValue, TString& TimeInOutErrCutValue, TString& DeltaTimeInOutCutValue, TString& DeltaDtInvBetaCutValue, TString& OppEtaCutValue, TString& OppPhiCutValue, TString& DxyCutValue, TString& abcdInvBetaCutValue, TString& abcdPtCutValue,TString& abInvBetaCutValue, TString& cInvBetaCutValue, TString& acPtCutValue, TString& bPtCutValue){

  cout<<"just started loop"<<endl;

  id_hist->SetBinErrorOption(TH1::kPoisson);
  run_hist->SetBinErrorOption(TH1::kPoisson);
  bx_hist->SetBinErrorOption(TH1::kPoisson); 
  bxWrtCollision_hist->SetBinErrorOption(TH1::kPoisson);
  bxWrtBunch_hist->SetBinErrorOption(TH1::kPoisson);
  mcStoppedParticle_N_hist->SetBinErrorOption(TH1::kPoisson);
  mcStoppedParticleX_hist->SetBinErrorOption(TH1::kPoisson); 
  mcStoppedParticleY_hist->SetBinErrorOption(TH1::kPoisson); 
  mcStoppedParticleZ_hist->SetBinErrorOption(TH1::kPoisson); 
  mcStoppedParticleR_hist->SetBinErrorOption(TH1::kPoisson); 
  mcStoppedParticleEta_hist->SetBinErrorOption(TH1::kPoisson);
  mcStoppedParticlePhi_hist->SetBinErrorOption(TH1::kPoisson);
  mcStoppedParticleTime_hist->SetBinErrorOption(TH1::kPoisson);
  mcStoppedParticleXY_hist->SetBinErrorOption(TH1::kPoisson); 
  mcStoppedParticleR_muDisplacedStandAloneEta_hist->SetBinErrorOption(TH1::kPoisson);    
  mcStoppedParticleMass_hist->SetBinErrorOption(TH1::kPoisson);    
  mcStoppedParticleId_hist->SetBinErrorOption(TH1::kPoisson);    
  mcStoppedParticleCharge_hist->SetBinErrorOption(TH1::kPoisson);    
  mcStoppedParticleX_StoppedParticleN_hist->SetBinErrorOption(TH1::kPoisson);    
  mcStoppedParticleY_StoppedParticleN_hist->SetBinErrorOption(TH1::kPoisson);    
  mcStoppedParticleZ_StoppedParticleN_hist->SetBinErrorOption(TH1::kPoisson);    
  mcStoppedParticleId_StoppedParticleN_hist->SetBinErrorOption(TH1::kPoisson);    
  mcStoppedParticleCharge_StoppedParticleN_hist->SetBinErrorOption(TH1::kPoisson);    
  mcStoppedParticleTime_mcStoppedParticleCharge_hist->SetBinErrorOption(TH1::kPoisson);    
  mcStoppedParticleXPos2Stopped_hist->SetBinErrorOption(TH1::kPoisson);    
  mcStoppedParticleYPos2Stopped_hist->SetBinErrorOption(TH1::kPoisson);    
  mcStoppedParticleZPos2Stopped_hist->SetBinErrorOption(TH1::kPoisson);    
  mcStoppedParticleRPos2Stopped_hist->SetBinErrorOption(TH1::kPoisson);    
  mcStoppedParticleXNeg2Stopped_hist->SetBinErrorOption(TH1::kPoisson);    
  mcStoppedParticleYNeg2Stopped_hist->SetBinErrorOption(TH1::kPoisson);    
  mcStoppedParticleZNeg2Stopped_hist->SetBinErrorOption(TH1::kPoisson);    
  mcStoppedParticleRNeg2Stopped_hist->SetBinErrorOption(TH1::kPoisson);    
  mcStoppedParticleDeltaTime_hist->SetBinErrorOption(TH1::kPoisson);
  mcStoppedParticleXPos_hist->SetBinErrorOption(TH1::kPoisson);    
  mcStoppedParticleYPos_hist->SetBinErrorOption(TH1::kPoisson);    
  mcStoppedParticleZPos_hist->SetBinErrorOption(TH1::kPoisson);    
  mcStoppedParticleRPos_hist->SetBinErrorOption(TH1::kPoisson);    
  mcStoppedParticleXNeg_hist->SetBinErrorOption(TH1::kPoisson);    
  mcStoppedParticleYNeg_hist->SetBinErrorOption(TH1::kPoisson);    
  mcStoppedParticleZNeg_hist->SetBinErrorOption(TH1::kPoisson);    
  mcStoppedParticleRNeg_hist->SetBinErrorOption(TH1::kPoisson);    
  mcStoppedParticle0Charge_hist->SetBinErrorOption(TH1::kPoisson);
  mcStoppedParticle1Charge_hist->SetBinErrorOption(TH1::kPoisson);
  mcStoppedParticle0Time_hist->SetBinErrorOption(TH1::kPoisson);
  mcStoppedParticle1Time_hist->SetBinErrorOption(TH1::kPoisson);
  mcLL_N_hist->SetBinErrorOption(TH1::kPoisson);
  mcLLStatus_hist->SetBinErrorOption(TH1::kPoisson);
  mcLLPt_hist->SetBinErrorOption(TH1::kPoisson); 
  mcLLEta_hist->SetBinErrorOption(TH1::kPoisson);
  mcLLPhi_hist->SetBinErrorOption(TH1::kPoisson);
  mcLLCharge_hist->SetBinErrorOption(TH1::kPoisson);
  mcLLMass_hist->SetBinErrorOption(TH1::kPoisson);
  mcLLNDaughters_hist->SetBinErrorOption(TH1::kPoisson);
  mcLLDaughterId_hist->SetBinErrorOption(TH1::kPoisson);    
  mcRhadron_N_hist->SetBinErrorOption(TH1::kPoisson);    
  mcRhadronPt_hist->SetBinErrorOption(TH1::kPoisson);    
  mcRhadronEta_hist->SetBinErrorOption(TH1::kPoisson);    
  mcRhadronPhi_hist->SetBinErrorOption(TH1::kPoisson);    
  mcRhadronCharge_hist->SetBinErrorOption(TH1::kPoisson);    
  mcStau_N_hist->SetBinErrorOption(TH1::kPoisson);
  mcStau0Charge_hist->SetBinErrorOption(TH1::kPoisson);
  mcStau1Charge_hist->SetBinErrorOption(TH1::kPoisson);
  mcStauP_hist->SetBinErrorOption(TH1::kPoisson);
  mcStauPx_hist->SetBinErrorOption(TH1::kPoisson);
  mcStauPy_hist->SetBinErrorOption(TH1::kPoisson);
  mcStauPz_hist->SetBinErrorOption(TH1::kPoisson);
  mcStauPt_hist->SetBinErrorOption(TH1::kPoisson);
  mcStauEta_hist->SetBinErrorOption(TH1::kPoisson);
  mcStauPhi_hist->SetBinErrorOption(TH1::kPoisson);
  mcStauBeta_hist->SetBinErrorOption(TH1::kPoisson);
  mcH0Charge_hist->SetBinErrorOption(TH1::kPoisson);    
  mcH1Charge_hist->SetBinErrorOption(TH1::kPoisson);    
  mcHPlusPlusP_hist->SetBinErrorOption(TH1::kPoisson);    
  mcHPlusPlusPx_hist->SetBinErrorOption(TH1::kPoisson);    
  mcHPlusPlusPy_hist->SetBinErrorOption(TH1::kPoisson);    
  mcHPlusPlusPz_hist->SetBinErrorOption(TH1::kPoisson);    
  mcHPlusPlusPt_hist->SetBinErrorOption(TH1::kPoisson);    
  mcHPlusPlusEta_hist->SetBinErrorOption(TH1::kPoisson);    
  mcHPlusPlusPhi_hist->SetBinErrorOption(TH1::kPoisson);    
  mcHMinusMinusP_hist->SetBinErrorOption(TH1::kPoisson);    
  mcHMinusMinusPx_hist->SetBinErrorOption(TH1::kPoisson);    
  mcHMinusMinusPy_hist->SetBinErrorOption(TH1::kPoisson);    
  mcHMinusMinusPz_hist->SetBinErrorOption(TH1::kPoisson);    
  mcHMinusMinusPt_hist->SetBinErrorOption(TH1::kPoisson);    
  mcHMinusMinusEta_hist->SetBinErrorOption(TH1::kPoisson);    
  mcHMinusMinusPhi_hist->SetBinErrorOption(TH1::kPoisson);    
  mcHPlusPlusP_HMinusMinusP_hist->SetBinErrorOption(TH1::kPoisson);
  mcHPlusPlusPt_HMinusMinusPt_hist->SetBinErrorOption(TH1::kPoisson);
  mcHPlusPlusEta_HMinusMinusEta_hist->SetBinErrorOption(TH1::kPoisson);
  mcHPlusPlusPhi_HMinusMinusPhi_hist->SetBinErrorOption(TH1::kPoisson);
  mcTop_N_hist->SetBinErrorOption(TH1::kPoisson);
  mcTopStatus_hist->SetBinErrorOption(TH1::kPoisson);
  mcTopPt_hist->SetBinErrorOption(TH1::kPoisson);
  mcTopEta_hist->SetBinErrorOption(TH1::kPoisson);
  mcTopPhi_hist->SetBinErrorOption(TH1::kPoisson);
  mcTopCharge_hist->SetBinErrorOption(TH1::kPoisson);
  mcTopMass_hist->SetBinErrorOption(TH1::kPoisson);
  mcTopNDaughters_hist->SetBinErrorOption(TH1::kPoisson);
  mcTopDaughterId_hist->SetBinErrorOption(TH1::kPoisson);
  mcW_N_hist->SetBinErrorOption(TH1::kPoisson);
  mcWStatus_hist->SetBinErrorOption(TH1::kPoisson);
  mcWPt_hist->SetBinErrorOption(TH1::kPoisson);
  mcWEta_hist->SetBinErrorOption(TH1::kPoisson);
  mcWPhi_hist->SetBinErrorOption(TH1::kPoisson);
  mcWCharge_hist->SetBinErrorOption(TH1::kPoisson);
  mcWMass_hist->SetBinErrorOption(TH1::kPoisson);
  mcWNDaughters_hist->SetBinErrorOption(TH1::kPoisson);
  mcWDaughterId_hist->SetBinErrorOption(TH1::kPoisson);
  mcMuon_N_hist->SetBinErrorOption(TH1::kPoisson);
  mcMuonP_hist->SetBinErrorOption(TH1::kPoisson);
  mcMuonPt_hist->SetBinErrorOption(TH1::kPoisson);
  mcMuonEta_hist->SetBinErrorOption(TH1::kPoisson);
  mcMuonPhi_hist->SetBinErrorOption(TH1::kPoisson);
  mcMuonCharge_hist->SetBinErrorOption(TH1::kPoisson);
  mcMuonStatus_hist->SetBinErrorOption(TH1::kPoisson);
  mcMuonMass_hist->SetBinErrorOption(TH1::kPoisson);
  mcMuonMotherId_hist->SetBinErrorOption(TH1::kPoisson);
  mcMuonVx_hist->SetBinErrorOption(TH1::kPoisson);
  mcMuonVy_hist->SetBinErrorOption(TH1::kPoisson);
  mcMuonVz_hist->SetBinErrorOption(TH1::kPoisson);
  mcMuonLxy_hist->SetBinErrorOption(TH1::kPoisson);
  mcMuonDxy_hist->SetBinErrorOption(TH1::kPoisson);
  mcMuon3Dangle_hist->SetBinErrorOption(TH1::kPoisson);
  mcMuonDeltaPhi_hist->SetBinErrorOption(TH1::kPoisson);
  mcMuonInverseBeta_hist->SetBinErrorOption(TH1::kPoisson);
  mcMuonPt_muRefittedStandAlonePt_hist->SetBinErrorOption(TH1::kPoisson);
  mcMuonPt_muCosmicPt_hist->SetBinErrorOption(TH1::kPoisson);
  mcMuonPt_muCosmicTrackPt_hist->SetBinErrorOption(TH1::kPoisson);
  simTrackN_hist->SetBinErrorOption(TH1::kPoisson);
  simTrackPt_hist->SetBinErrorOption(TH1::kPoisson);
  simTrackEta_hist->SetBinErrorOption(TH1::kPoisson);
  simTrackPhi_hist->SetBinErrorOption(TH1::kPoisson);
  simTrackCharge_hist->SetBinErrorOption(TH1::kPoisson);
  simTrackVx_hist->SetBinErrorOption(TH1::kPoisson);
  simTrackVy_hist->SetBinErrorOption(TH1::kPoisson);
  simTrackVz_hist->SetBinErrorOption(TH1::kPoisson);
  muStandAloneP_hist->SetBinErrorOption(TH1::kPoisson);
  muStandAloneUpdatedAtVtxP_hist->SetBinErrorOption(TH1::kPoisson);
  muStandAlonePt_hist->SetBinErrorOption(TH1::kPoisson);
  muStandAloneUpdatedAtVtxPt_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneGenDR_hist->SetBinErrorOption(TH1::kPoisson);
  muGenDR_hist->SetBinErrorOption(TH1::kPoisson);
  muStandAloneTrackGenDR_hist->SetBinErrorOption(TH1::kPoisson);
  muStandAloneTrackUpdatedAtVtxGenDR_hist->SetBinErrorOption(TH1::kPoisson);
  muRefittedStandAloneTrackGenDR_hist->SetBinErrorOption(TH1::kPoisson);
  muCosmicTrackGenDR_hist->SetBinErrorOption(TH1::kPoisson);    
  mcStoppedParticleR_muDisplacedStandAloneGenDR_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAlonePtResolution_hist->SetBinErrorOption(TH1::kPoisson);
  muPtResolution_hist->SetBinErrorOption(TH1::kPoisson);
  muStandAlonePtResolution_hist->SetBinErrorOption(TH1::kPoisson);
  muStandAloneUpdatedAtVtxPtResolution_hist->SetBinErrorOption(TH1::kPoisson);
  muRefittedStandAlonePtResolution_hist->SetBinErrorOption(TH1::kPoisson);
  muCosmicPtResolution_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneQoverPtResolution_hist->SetBinErrorOption(TH1::kPoisson);
  muQoverPtResolution_hist->SetBinErrorOption(TH1::kPoisson);
  muStandAloneQoverPtResolution_hist->SetBinErrorOption(TH1::kPoisson);
  muStandAloneUpdatedAtVtxQoverPtResolution_hist->SetBinErrorOption(TH1::kPoisson);
  muRefittedStandAloneQoverPtResolution_hist->SetBinErrorOption(TH1::kPoisson);
  muCosmicQoverPtResolution_hist->SetBinErrorOption(TH1::kPoisson);
  muRefittedStandAlonePtResolution_muCosmicPtResolution_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneNChambersDt_PtResolution_hist->SetBinErrorOption(TH1::kPoisson);
  muRefittedStandAloneNChambersDt_PtResolution_hist->SetBinErrorOption(TH1::kPoisson);
  muCosmicNChambersDt_PtResolution_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneNChambersRpc_PtResolution_hist->SetBinErrorOption(TH1::kPoisson);
  muRefittedStandAloneNChambersRpc_PtResolution_hist->SetBinErrorOption(TH1::kPoisson);
  muCosmicNChambersRpc_PtResolution_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneNChambersDt_Pt_hist->SetBinErrorOption(TH1::kPoisson);
  muRefittedStandAloneNChambersDt_Pt_hist->SetBinErrorOption(TH1::kPoisson);
  muCosmicNChambersDt_Pt_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneNChambersRpc_Pt_hist->SetBinErrorOption(TH1::kPoisson);
  muRefittedStandAloneNChambersRpc_Pt_hist->SetBinErrorOption(TH1::kPoisson);
  muCosmicNChambersRpc_Pt_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAlonePt_muCosmicTrackPt_hist->SetBinErrorOption(TH1::kPoisson);
  mcMuonN_muDisplacedStandAloneN_hist->SetBinErrorOption(TH1::kPoisson);
  mcMuonPt_muDisplacedStandAlonePt_hist->SetBinErrorOption(TH1::kPoisson);
  mcMuonEta_muDisplacedStandAloneEta_hist->SetBinErrorOption(TH1::kPoisson);
  mcMuonPhi_muDisplacedStandAlonePhi_hist->SetBinErrorOption(TH1::kPoisson);
  mcMuonCharge_muDisplacedStandAloneCharge_hist->SetBinErrorOption(TH1::kPoisson);
  mcMuonLxy_muDisplacedStandAloneLxy_hist->SetBinErrorOption(TH1::kPoisson);
  mcMuonDxy_muDisplacedStandAloneDxy_hist->SetBinErrorOption(TH1::kPoisson);
  mcMuonInverseBeta_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist->SetBinErrorOption(TH1::kPoisson);    
  muRefittedStandAloneNHitsDt_Pt_hist->SetBinErrorOption(TH1::kPoisson);
  //muRefittedStandAloneNChambersDt_Pt_hist->SetBinErrorOption(TH1::kPoisson);
  mcStoppedParticleR_muRefittedStandAlonePt_hist->SetBinErrorOption(TH1::kPoisson);
  mcStoppedParticleR_mcMuonPt_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneTrackDistanceStations_Pt_hist->SetBinErrorOption(TH1::kPoisson);
  muRefittedStandAloneTrackDistanceStations_Pt_hist->SetBinErrorOption(TH1::kPoisson);
  mcMuonPt_l1MuonPt_hist->SetBinErrorOption(TH1::kPoisson);
  mcMuonPt_hlt20Cha2MuonPt_hist->SetBinErrorOption(TH1::kPoisson);
  mcMuonEta_l1MuonEta_hist->SetBinErrorOption(TH1::kPoisson);
  mcMuonPhi_l1MuonPhi_hist->SetBinErrorOption(TH1::kPoisson);
  mcMuonEta_hlt20Cha2MuonEta_hist->SetBinErrorOption(TH1::kPoisson);
  mcMuonPhi_hlt20Cha2MuonPhi_hist->SetBinErrorOption(TH1::kPoisson);
  l1Muon_N_hist->SetBinErrorOption(TH1::kPoisson);
  l1MuonPt_hist->SetBinErrorOption(TH1::kPoisson);
  l1MuonEta_hist->SetBinErrorOption(TH1::kPoisson);
  l1MuonPhi_hist->SetBinErrorOption(TH1::kPoisson);
  hlt20Cha2Muon_N_hist->SetBinErrorOption(TH1::kPoisson);
  hlt20Cha2MuonPt_hist->SetBinErrorOption(TH1::kPoisson);
  hlt20Cha2MuonEta_hist->SetBinErrorOption(TH1::kPoisson);
  hlt20Cha2MuonPhi_hist->SetBinErrorOption(TH1::kPoisson);
  mu_N_hist ->SetBinErrorOption(TH1::kPoisson);
  muP_hist ->SetBinErrorOption(TH1::kPoisson);
  muPt_hist ->SetBinErrorOption(TH1::kPoisson);
  muEta_hist->SetBinErrorOption(TH1::kPoisson);
  muPhi_hist->SetBinErrorOption(TH1::kPoisson);
  muType_hist->SetBinErrorOption(TH1::kPoisson); 
  muIso_hist->SetBinErrorOption(TH1::kPoisson);
  muEta_muPhi_hist->SetBinErrorOption(TH1::kPoisson);    
  diMu_N_hist->SetBinErrorOption(TH1::kPoisson);
  diMuMass_hist->SetBinErrorOption(TH1::kPoisson);    
  muCosmic_N_hist->SetBinErrorOption(TH1::kPoisson);
  muCosmicP_hist->SetBinErrorOption(TH1::kPoisson);
  muCosmicPt_hist->SetBinErrorOption(TH1::kPoisson);
  muCosmicEta_hist->SetBinErrorOption(TH1::kPoisson);
  muCosmicPhi_hist->SetBinErrorOption(TH1::kPoisson);
  muCosmicType_hist->SetBinErrorOption(TH1::kPoisson);
  muCosmicEta_muCosmicPhi_hist->SetBinErrorOption(TH1::kPoisson); 
  muCosmicTrackInnerPt_hist->SetBinErrorOption(TH1::kPoisson);   
  muCosmicTrackNChambersDt_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAlone_N_other_cut_hist->SetBinErrorOption(TH1::kPoisson);    
  muDisplacedStandAlone_N_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneP_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAlonePt_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAlonePt0_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAlonePt1_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAlonePt2_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneEta_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAlonePhi_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneCharge_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneTrackNormalizedChi2_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneTrackDxy_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneTrackDz_hist->SetBinErrorOption(TH1::kPoisson); 
  muDisplacedStandAloneTrackNHitsMuon_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneTrackNHitsCsc_hist->SetBinErrorOption(TH1::kPoisson); 
  muDisplacedStandAloneTrackNHitsDt_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneTrackNHitsRpc_hist->SetBinErrorOption(TH1::kPoisson); 
  muDisplacedStandAloneTrackNRpcDof_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneTrackNStations_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneTrackNChambersCsc_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneTrackNChambersDt_hist->SetBinErrorOption(TH1::kPoisson); 
  muDisplacedStandAloneTrackNChambersRpc_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneTrackDistanceStations_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneTrackInnerPt_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneTrackDtTofNDof_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneBxPattern_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneNHitsRpcBxPattern0_hist->SetBinErrorOption(TH1::kPoisson);    
  muDisplacedStandAloneOppositeSegDR_hist->SetBinErrorOption(TH1::kPoisson);    
  muDisplacedStandAloneOppositeSegDEta_hist->SetBinErrorOption(TH1::kPoisson);    
  muDisplacedStandAloneOppositeSegDPhi_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAlonePt_denominator_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAlonePt_L1numerator_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAlonePt_HLTnumerator_hist->SetBinErrorOption(TH1::kPoisson);
  muRefittedStandAlonePt_denominator_hist->SetBinErrorOption(TH1::kPoisson);
  muRefittedStandAlonePt_L1numerator_hist->SetBinErrorOption(TH1::kPoisson);
  muRefittedStandAlonePt_HLTnumerator_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAlonePt_GlSAdenominator_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAlonePt_GlSAnumerator_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneTrackShowerSize_station0_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneTrackShowerSize_station1_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneTrackShowerSize_station2_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneTrackShowerSize_station3_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneTrackShowerDeltaR_station0_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneTrackShowerDeltaR_station1_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneTrackShowerDeltaR_station2_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneTrackShowerDeltaR_station3_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneTrackShowerNHits_station0_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneTrackShowerNHits_station1_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneTrackShowerNHits_station2_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneTrackShowerNHits_station3_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneTrackShowerNCorrelatedHits_station0_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneTrackShowerNCorrelatedHits_station1_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneTrackShowerNCorrelatedHits_station2_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneTrackShowerNCorrelatedHits_station3_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneTrackShowerNUncorrelatedHits_station0_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneTrackShowerNUncorrelatedHits_station1_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneTrackShowerNUncorrelatedHits_station2_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneTrackShowerNUncorrelatedHits_station3_hist->SetBinErrorOption(TH1::kPoisson);    
  muDisplacedStandAloneUpperOnlyDEta_hist->SetBinErrorOption(TH1::kPoisson);    
  muDisplacedStandAloneUpperOnlyDPhi_hist->SetBinErrorOption(TH1::kPoisson);    
  muDisplacedStandAloneLowerOnlyDEta_hist->SetBinErrorOption(TH1::kPoisson);    
  muDisplacedStandAloneLowerOnlyDPhi_hist->SetBinErrorOption(TH1::kPoisson);    
  muDisplacedStandAloneNCscSegments_hist->SetBinErrorOption(TH1::kPoisson);    
  muDisplacedStandAlonePhi_muDisplacedStandAloneDTTofFreeInverseBeta_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneEta_muDisplacedStandAlonePhi_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneTrackNHitsRpc_muDisplacedStandAloneTrackNormalizedChi2_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneTrackNHitsRpc_muDisplacedStandAloneTrackNHitsDt_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAlonePt_muDisplacedStandAloneTrackNChambersDt_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAlonePt_DtTofFreeInverseBeta_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneP_DtTofFreeInverseBeta_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAlonePt_BxPattern_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneDtTofFreeInverseBeta_DtTofDirection_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneDtTofFreeInverseBetaErr_DtTofNDof_hist->SetBinErrorOption(TH1::kPoisson);
  runNumber_muDisplacedStandAloneDtTofFreeInverseBeta_hist->SetBinErrorOption(TH1::kPoisson);
  runNumber_muDisplacedStandAloneDtTofInverseBeta_hist->SetBinErrorOption(TH1::kPoisson);
  runNumber_muDisplacedStandAlonePt_hist->SetBinErrorOption(TH1::kPoisson);
  runNumber_muDisplacedStandAlonePhi_hist->SetBinErrorOption(TH1::kPoisson);
  runNumber_muDisplacedStandAloneN_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneEta_Phi_hist->SetBinErrorOption(TH1::kPoisson);
  Upper_muDisplacedStandAlonePt_hist->SetBinErrorOption(TH1::kPoisson);
  Upper_muDisplacedStandAloneEta_hist->SetBinErrorOption(TH1::kPoisson);
  Upper_muDisplacedStandAlonePhi_hist->SetBinErrorOption(TH1::kPoisson);
  Upper_muDisplacedStandAloneTrackCharge_hist->SetBinErrorOption(TH1::kPoisson);
  Upper_muDisplacedStandAloneTrackNormalizedChi2_hist->SetBinErrorOption(TH1::kPoisson);
  Upper_muDisplacedStandAloneTrackDxy_hist->SetBinErrorOption(TH1::kPoisson);
  Upper_muDisplacedStandAloneTrackDz_hist->SetBinErrorOption(TH1::kPoisson);
  Upper_muDisplacedStandAloneTrackNHitsMuon_hist->SetBinErrorOption(TH1::kPoisson);
  Upper_muDisplacedStandAloneTrackNHitsCsc_hist->SetBinErrorOption(TH1::kPoisson);
  Upper_muDisplacedStandAloneTrackNHitsDt_hist->SetBinErrorOption(TH1::kPoisson);
  Upper_muDisplacedStandAloneTrackNHitsRpc_hist->SetBinErrorOption(TH1::kPoisson);
  Upper_muDisplacedStandAloneTrackNRpcDof_hist->SetBinErrorOption(TH1::kPoisson);
  Upper_muDisplacedStandAloneTrackNStations_hist->SetBinErrorOption(TH1::kPoisson);
  Upper_muDisplacedStandAloneTrackNChambersCsc_hist->SetBinErrorOption(TH1::kPoisson);
  Upper_muDisplacedStandAloneTrackNChambersDt_hist->SetBinErrorOption(TH1::kPoisson);
  Upper_muDisplacedStandAloneTrackNChambersRpc_hist->SetBinErrorOption(TH1::kPoisson);
  Upper_muDisplacedStandAloneTrackDtTofNDof_hist->SetBinErrorOption(TH1::kPoisson);
  Upper_muDisplacedStandAloneTrackDtTofInverseBeta_hist->SetBinErrorOption(TH1::kPoisson);
  Upper_muDisplacedStandAloneTrackDtTofInverseBetaErr_hist->SetBinErrorOption(TH1::kPoisson);
  Upper_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist->SetBinErrorOption(TH1::kPoisson);
  Upper_muDisplacedStandAloneTrackDtTofFreeInverseBetaErr_hist->SetBinErrorOption(TH1::kPoisson);
  Upper_muDisplacedStandAloneTrackDtTofTimeAtIpInOut_hist->SetBinErrorOption(TH1::kPoisson);
  Upper_muDisplacedStandAloneTrackDtTofTimeAtIpOutIn_hist->SetBinErrorOption(TH1::kPoisson);
  Upper_muDisplacedStandAloneTrackDtTofDirection_hist->SetBinErrorOption(TH1::kPoisson);
  Upper_muDisplacedStandAloneBxPattern_hist->SetBinErrorOption(TH1::kPoisson);
  Upper_muDisplacedStandAloneTrackNHitsRpc_Upper_muDisplacedStandAloneTrackNormalizedChi2_hist->SetBinErrorOption(TH1::kPoisson);
  Upper_muDisplacedStandAloneTrackNHitsRpc_Upper_muDisplacedStandAloneTrackNHitsDt_hist->SetBinErrorOption(TH1::kPoisson);
  Upper_muDisplacedStandAloneBxPattern_Upper_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist->SetBinErrorOption(TH1::kPoisson);
  Upper_muDisplacedStandAlonePt_Upper_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist->SetBinErrorOption(TH1::kPoisson);
  Upper_muDisplacedStandAloneP_Upper_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist->SetBinErrorOption(TH1::kPoisson);
  Upper_muDisplacedStandAlonePt_Upper_muDisplacedStandAloneBxPattern_hist->SetBinErrorOption(TH1::kPoisson);
  Upper_muDisplacedStandAloneTimeAtIpInOut_Upper_muDisplacedStandAloneFreeInverseBeta_hist->SetBinErrorOption(TH1::kPoisson);
  Upper_muDisplacedStandAloneTimeAtIpInOut_Upper_muDisplacedStandAloneDirection_hist->SetBinErrorOption(TH1::kPoisson);
  Upper_muDisplacedStandAloneFreeInverseBeta_Upper_muDisplacedStandAloneFreeInverseBetaErr_hist->SetBinErrorOption(TH1::kPoisson);
  Highest_muDisplacedStandAloneP_Upper_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist->SetBinErrorOption(TH1::kPoisson);
  Upper_runNumber_muDisplacedStandAloneDtTofFreeInverseBeta_hist->SetBinErrorOption(TH1::kPoisson);
  Upper_runNumber_muDisplacedStandAloneDtTofInverseBeta_hist->SetBinErrorOption(TH1::kPoisson);
  Upper_runNumber_muDisplacedStandAlonePt_hist->SetBinErrorOption(TH1::kPoisson);    
  Upper_runNumber_muDisplacedStandAlonePhi_hist->SetBinErrorOption(TH1::kPoisson);
  Upper_runNumber_muDisplacedStandAloneN_hist->SetBinErrorOption(TH1::kPoisson);
  Upper_muDisplacedStandAloneEta_Phi_hist->SetBinErrorOption(TH1::kPoisson);
  Lower_muDisplacedStandAlonePt_hist->SetBinErrorOption(TH1::kPoisson);
  Lower_muDisplacedStandAloneEta_hist->SetBinErrorOption(TH1::kPoisson);
  Lower_muDisplacedStandAlonePhi_hist->SetBinErrorOption(TH1::kPoisson);
  Lower_muDisplacedStandAloneTrackCharge_hist->SetBinErrorOption(TH1::kPoisson);
  Lower_muDisplacedStandAloneTrackNormalizedChi2_hist->SetBinErrorOption(TH1::kPoisson);
  Lower_muDisplacedStandAloneTrackDxy_hist->SetBinErrorOption(TH1::kPoisson);
  Lower_muDisplacedStandAloneTrackDz_hist->SetBinErrorOption(TH1::kPoisson);
  Lower_muDisplacedStandAloneTrackNHitsMuon_hist->SetBinErrorOption(TH1::kPoisson);
  Lower_muDisplacedStandAloneTrackNHitsCsc_hist->SetBinErrorOption(TH1::kPoisson);
  Lower_muDisplacedStandAloneTrackNHitsDt_hist->SetBinErrorOption(TH1::kPoisson);
  Lower_muDisplacedStandAloneTrackNHitsRpc_hist->SetBinErrorOption(TH1::kPoisson);
  Lower_muDisplacedStandAloneTrackNRpcDof_hist->SetBinErrorOption(TH1::kPoisson);
  Lower_muDisplacedStandAloneTrackNStations_hist->SetBinErrorOption(TH1::kPoisson);
  Lower_muDisplacedStandAloneTrackNChambersCsc_hist->SetBinErrorOption(TH1::kPoisson);
  Lower_muDisplacedStandAloneTrackNChambersDt_hist->SetBinErrorOption(TH1::kPoisson);
  Lower_muDisplacedStandAloneTrackNChambersRpc_hist->SetBinErrorOption(TH1::kPoisson);
  Lower_muDisplacedStandAloneTrackDtTofNDof_hist->SetBinErrorOption(TH1::kPoisson);
  Lower_muDisplacedStandAloneTrackDtTofInverseBeta_hist->SetBinErrorOption(TH1::kPoisson);
  Lower_muDisplacedStandAloneTrackDtTofInverseBetaErr_hist->SetBinErrorOption(TH1::kPoisson);
  Lower_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist->SetBinErrorOption(TH1::kPoisson);
  Lower_muDisplacedStandAloneTrackDtTofFreeInverseBetaErr_hist->SetBinErrorOption(TH1::kPoisson);
  Lower_muDisplacedStandAloneTrackDtTofTimeAtIpInOut_hist->SetBinErrorOption(TH1::kPoisson);
  Lower_muDisplacedStandAloneTrackDtTofTimeAtIpOutIn_hist->SetBinErrorOption(TH1::kPoisson);
  Lower_muDisplacedStandAloneTrackDtTofDirection_hist->SetBinErrorOption(TH1::kPoisson);
  Lower_muDisplacedStandAloneBxPattern_hist->SetBinErrorOption(TH1::kPoisson);
  Lower_muDisplacedStandAloneTrackNHitsRpc_Lower_muDisplacedStandAloneTrackNormalizedChi2_hist->SetBinErrorOption(TH1::kPoisson);
  Lower_muDisplacedStandAloneTrackNHitsRpc_Lower_muDisplacedStandAloneTrackNHitsDt_hist->SetBinErrorOption(TH1::kPoisson);
  Lower_muDisplacedStandAloneBxPattern_Lower_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist->SetBinErrorOption(TH1::kPoisson);
  Lower_muDisplacedStandAlonePt_Lower_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist->SetBinErrorOption(TH1::kPoisson);
  Lower_muDisplacedStandAlonePt_Lower_muDisplacedStandAloneBxPattern_hist->SetBinErrorOption(TH1::kPoisson);
  Lower_muDisplacedStandAloneTimeAtIpInOut_Lower_muDisplacedStandAloneFreeInverseBeta_hist->SetBinErrorOption(TH1::kPoisson);
  Lower_muDisplacedStandAloneTimeAtIpInOut_Lower_muDisplacedStandAloneDirection_hist->SetBinErrorOption(TH1::kPoisson);
  Lower_muDisplacedStandAloneFreeInverseBeta_Lower_muDisplacedStandAloneFreeInverseBetaErr_hist->SetBinErrorOption(TH1::kPoisson);
  Lower_runNumber_muDisplacedStandAloneDtTofFreeInverseBeta_hist->SetBinErrorOption(TH1::kPoisson);
  Lower_runNumber_muDisplacedStandAloneDtTofInverseBeta_hist->SetBinErrorOption(TH1::kPoisson);
  Lower_runNumber_muDisplacedStandAlonePt_hist->SetBinErrorOption(TH1::kPoisson);    
  Lower_runNumber_muDisplacedStandAlonePhi_hist->SetBinErrorOption(TH1::kPoisson);
  Lower_runNumber_muDisplacedStandAloneN_hist->SetBinErrorOption(TH1::kPoisson);
  Lower_muDisplacedStandAloneEta_Phi_hist->SetBinErrorOption(TH1::kPoisson);
  Upper_Lower_muDisplacedStandAlone_deltaPhi_hist->SetBinErrorOption(TH1::kPoisson);
  mudiff_muDisplacedStandAloneTofTimeAtIpInOut_hist->SetBinErrorOption(TH1::kPoisson);
  mudiff_muDisplacedStandAloneTofTimeAtIpOutIn_hist->SetBinErrorOption(TH1::kPoisson);
  mudiff_muDisplacedStandAloneTofFreeInverseBeta_hist->SetBinErrorOption(TH1::kPoisson);
  Upper_Lower_muDisplacedStandAlone_chargeMultiply_hist->SetBinErrorOption(TH1::kPoisson);
  Upper_Lower_muDisplacedStandAlone_directionMultiply_hist->SetBinErrorOption(TH1::kPoisson);
  Upper_Lower_muDisplacedStandAloneTofTimeAtIpInOut_hist->SetBinErrorOption(TH1::kPoisson);
  Upper_Lower_muDisplacedStandAloneTofTimeAtIpOutIn_hist->SetBinErrorOption(TH1::kPoisson);
  Upper_Lower_muDisplacedStandAloneTrackCharge_hist->SetBinErrorOption(TH1::kPoisson);
  Upper_Lower_muDisplacedStandAloneTrackDtTofDirection_hist->SetBinErrorOption(TH1::kPoisson);
  Upper_Lower_muDisplacedStandAlonePt_hist->SetBinErrorOption(TH1::kPoisson);
  Upper_Lower_muDisplacedStandAloneDtTofFreeInverseBeta_hist->SetBinErrorOption(TH1::kPoisson);
  Both_muDisplacedStandAlonePt_hist->SetBinErrorOption(TH1::kPoisson);
  Both_muDisplacedStandAloneEta_hist->SetBinErrorOption(TH1::kPoisson);
  Both_muDisplacedStandAlonePhi_hist->SetBinErrorOption(TH1::kPoisson);
  Both_muDisplacedStandAloneTrackCharge_hist->SetBinErrorOption(TH1::kPoisson);
  Both_muDisplacedStandAloneTrackNormalizedChi2_hist->SetBinErrorOption(TH1::kPoisson);
  Both_muDisplacedStandAloneTrackDxy_hist->SetBinErrorOption(TH1::kPoisson);
  Both_muDisplacedStandAloneTrackDz_hist->SetBinErrorOption(TH1::kPoisson);
  Both_muDisplacedStandAloneTrackNHitsMuon_hist->SetBinErrorOption(TH1::kPoisson);
  Both_muDisplacedStandAloneTrackNHitsCsc_hist->SetBinErrorOption(TH1::kPoisson);
  Both_muDisplacedStandAloneTrackNHitsDt_hist->SetBinErrorOption(TH1::kPoisson);
  Both_muDisplacedStandAloneTrackNHitsRpc_hist->SetBinErrorOption(TH1::kPoisson);
  Both_muDisplacedStandAloneTrackNRpcDof_hist->SetBinErrorOption(TH1::kPoisson);
  Both_muDisplacedStandAloneTrackNStations_hist->SetBinErrorOption(TH1::kPoisson);
  Both_muDisplacedStandAloneTrackNChambersCsc_hist->SetBinErrorOption(TH1::kPoisson);
  Both_muDisplacedStandAloneTrackNChambersDt_hist->SetBinErrorOption(TH1::kPoisson);
  Both_muDisplacedStandAloneTrackNChambersRpc_hist->SetBinErrorOption(TH1::kPoisson);
  Both_muDisplacedStandAloneTrackDtTofNDof_hist->SetBinErrorOption(TH1::kPoisson);
  Both_muDisplacedStandAloneTrackDtTofInverseBeta_hist->SetBinErrorOption(TH1::kPoisson);
  Both_muDisplacedStandAloneTrackDtTofInverseBetaErr_hist->SetBinErrorOption(TH1::kPoisson);
  Both_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist->SetBinErrorOption(TH1::kPoisson);
  Both_muDisplacedStandAloneTrackDtTofFreeInverseBetaErr_hist->SetBinErrorOption(TH1::kPoisson);
  Both_muDisplacedStandAloneTrackDtTofTimeAtIpInOut_hist->SetBinErrorOption(TH1::kPoisson);
  Both_muDisplacedStandAloneTrackDtTofTimeAtIpOutIn_hist->SetBinErrorOption(TH1::kPoisson);
  Both_muDisplacedStandAloneTrackDtTofDirection_hist->SetBinErrorOption(TH1::kPoisson);
  Both_muDisplacedStandAloneBxPattern_hist->SetBinErrorOption(TH1::kPoisson);    
  Ave_muDisplacedStandAlonePt_hist->SetBinErrorOption(TH1::kPoisson);
  Diff_muDisplacedStandAlonePt_hist->SetBinErrorOption(TH1::kPoisson);
  mcMuon_muDisplacedStandAlone_3Dangle_hist->SetBinErrorOption(TH1::kPoisson);
  mcMuon_muDisplacedStandAlone_deltaPhi_hist->SetBinErrorOption(TH1::kPoisson);
  /*
  muRefittedStandAlone_N_hist->SetBinErrorOption(TH1::kPoisson);
  muRefittedStandAloneP_hist->SetBinErrorOption(TH1::kPoisson);
  muRefittedStandAlonePt_hist->SetBinErrorOption(TH1::kPoisson);
  muRefittedStandAloneEta_hist->SetBinErrorOption(TH1::kPoisson);
  muRefittedStandAlonePhi_hist->SetBinErrorOption(TH1::kPoisson);
  muRefittedStandAloneTrackDistanceStations_hist->SetBinErrorOption(TH1::kPoisson);
  muRefittedStandAloneEta_muRefittedStandAlonePhi_hist->SetBinErrorOption(TH1::kPoisson);    
  muStandAloneTof_N_hist->SetBinErrorOption(TH1::kPoisson);
  muStandAloneTofDirection_hist->SetBinErrorOption(TH1::kPoisson);
  muStandAloneTofNDof_hist->SetBinErrorOption(TH1::kPoisson);
  muStandAloneTofInverseBeta_hist->SetBinErrorOption(TH1::kPoisson);
  muStandAloneTofInverseBetaErr_hist->SetBinErrorOption(TH1::kPoisson);
  muStandAloneTofFreeInverseBeta_hist->SetBinErrorOption(TH1::kPoisson);
  muStandAloneTofFreeInverseBetaErr_hist->SetBinErrorOption(TH1::kPoisson);
  muStandAloneTofTimeAtIpInOut_hist->SetBinErrorOption(TH1::kPoisson);
  muStandAloneTofTimeAtIpInOutErr_hist->SetBinErrorOption(TH1::kPoisson);
  muStandAloneTofTimeAtIpOutIn_hist->SetBinErrorOption(TH1::kPoisson);
  muStandAloneTofTimeAtIpOutInErr_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneDTTof_N_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneDTTofDirection_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneDTTofNDof_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneDTTofInverseBeta_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneDTTofInverseBetaErr_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneDTTofFreeInverseBeta_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneDTTofFreeInverseBetaErr_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneDTTofTimeAtIpInOut_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneDTTofTimeAtIpInOutErr_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneDTTofTimeAtIpOutIn_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneDTTofTimeAtIpOutInErr_hist->SetBinErrorOption(TH1::kPoisson);    
  muDisplacedStandAloneCSCTof_N_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneCSCTofDirection_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneCSCTofNDof_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneCSCTofInverseBeta_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneCSCTofInverseBetaErr_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneCSCTofFreeInverseBeta_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneCSCTofFreeInverseBetaErr_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneCSCTofTimeAtIpInOut_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneCSCTofTimeAtIpInOutErr_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneCSCTofTimeAtIpOutIn_hist->SetBinErrorOption(TH1::kPoisson);
  muDisplacedStandAloneCSCTofTimeAtIpOutInErr_hist->SetBinErrorOption(TH1::kPoisson);    
  regionD_muDisplacedStandAlone_N_hist->SetBinErrorOption(TH1::kPoisson);
  regionD_muDisplacedStandAloneP_hist->SetBinErrorOption(TH1::kPoisson);
  regionD_muDisplacedStandAlonePt_hist->SetBinErrorOption(TH1::kPoisson);
  regionD_muDisplacedStandAloneEta_hist->SetBinErrorOption(TH1::kPoisson);
  regionD_muDisplacedStandAlonePhi_hist->SetBinErrorOption(TH1::kPoisson);
  regionD_muDisplacedStandAloneCharge_hist->SetBinErrorOption(TH1::kPoisson);
  regionD_muDisplacedStandAloneTrackNormalizedChi2_hist->SetBinErrorOption(TH1::kPoisson);
  regionD_muDisplacedStandAloneTrackDxy_hist->SetBinErrorOption(TH1::kPoisson);
  regionD_muDisplacedStandAloneTrackDz_hist->SetBinErrorOption(TH1::kPoisson);
  regionD_muDisplacedStandAloneTrackNHitsMuon_hist->SetBinErrorOption(TH1::kPoisson);
  regionD_muDisplacedStandAloneTrackNHitsCsc_hist->SetBinErrorOption(TH1::kPoisson);
  regionD_muDisplacedStandAloneTrackNHitsDt_hist->SetBinErrorOption(TH1::kPoisson);
  regionD_muDisplacedStandAloneTrackNHitsRpc_hist->SetBinErrorOption(TH1::kPoisson);
  regionD_muDisplacedStandAloneTrackNRpcDof_hist->SetBinErrorOption(TH1::kPoisson);
  regionD_muDisplacedStandAloneTrackNStations_hist->SetBinErrorOption(TH1::kPoisson);
  regionD_muDisplacedStandAloneTrackNChambersCsc_hist->SetBinErrorOption(TH1::kPoisson);
  regionD_muDisplacedStandAloneTrackNChambersDt_hist->SetBinErrorOption(TH1::kPoisson);
  regionD_muDisplacedStandAloneTrackNChambersRpc_hist->SetBinErrorOption(TH1::kPoisson);
  regionD_muDisplacedStandAloneTrackDtTofNDof_hist->SetBinErrorOption(TH1::kPoisson);
  regionD_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist->SetBinErrorOption(TH1::kPoisson);
  regionD_muDisplacedStandAloneTrackDtTofFreeInverseBetaErr_hist->SetBinErrorOption(TH1::kPoisson);
  regionD_muDisplacedStandAloneTrackDtTofTimeAtIpInOut_hist->SetBinErrorOption(TH1::kPoisson);
  regionD_muDisplacedStandAloneTrackDtTofTimeAtIpInOutErr_hist->SetBinErrorOption(TH1::kPoisson);
  regionD_muDisplacedStandAloneBxPattern_hist->SetBinErrorOption(TH1::kPoisson);    
  regionD_CSCSegment_N_hist->SetBinErrorOption(TH1::kPoisson);
  */
  regionAB_Upper_muDisplacedStandAloneP_Upper_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist->SetBinErrorOption(TH1::kPoisson);
  regionAC_Upper_muDisplacedStandAloneP_Upper_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist->SetBinErrorOption(TH1::kPoisson);
  regionB_muDisplacedStandAloneP_hist->SetBinErrorOption(TH1::kPoisson);
  regionC_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist->SetBinErrorOption(TH1::kPoisson);
  DTSegment_N_hist->SetBinErrorOption(TH1::kPoisson);
  CSCSegment_N_hist->SetBinErrorOption(TH1::kPoisson);

  string host=getenv("HOST");
  string host_=host.substr(0,4);
  cout<<"host is: "<<host_<<endl;
  cout<<"started function"<<endl;

  //make sure dictionaries can be used for reading
  //converts Reflex dictionary information to CINT data structures used by  ROOT
  ROOT::Cintex::Cintex::Enable();

  gSystem->Load("libStoppedHSCPMuonNtuples");
  cout<<"loaded library"<<endl;
  
  //stop, glui, mcha, gmst, ppst
  //NoBP, Sing, Zmum
  string file_dataset_=file_dataset.substr(0,4);
  bool is_data=false;
  bool is_otherMC=false;
  if(file_dataset_ == "NoBP" || file_dataset_ == "Sing" || file_dataset_ == "Zmum" || file_dataset_ == "ABCD" ) is_data=true;
  if(file_dataset_ == "tauP" || file_dataset_ == "doub" || file_dataset_=="mcha") is_otherMC=true;

  TString file = "blah";
  if(host_=="cmsl"){
    //if(resT3=="T3") file = "dcap:///pnfs/cms/WAX/11/store/user/alimena/Ntuples/" + file_dataset + "/stoppedHSCPMuonTree.root";
    //else if(resT3=="res") file = "dcap:///pnfs/cms/WAX/resilient/alimena/Ntuples/" + file_dataset + "/stoppedHSCPMuonTree.root";
    //else cout<<"problem with resT3!!!!!!"<<endl;
    file = "/uscms_data/d3/alimena/Ntuples/" + file_dataset + "/stoppedHSCPMuonTree.root";
  }
  if(host_=="brux") file = "/mnt/hadoop/store/user/jalimena/Ntuples/" + file_dataset + "/stoppedHSCPMuonTree.root";
  //if(host_=="brux") file = "/user_data/alimena/Ntuples/" + file_dataset + "/stoppedHSCPMuonTree.root";
  //if(host_=="brux") file = "../test/stoppedHSCPMuonTree.root";
  //if(host_=="brux") file="/home/alimena/histos/ABCDtree_2DSAdata_Run2012BCD.root";
  if(host_=="lxpl") file = "root://eoscms//eos/cms/store/user/jalimena/Ntuples/" + file_dataset + "/stoppedHSCPMuonTree.root";
  //if(host_=="lxpl") file = "/afs/cern.ch/work/j/jalimena/Ntuples/" + file_dataset + "/stoppedHSCPMuonTree.root";


  if (BxCut=="wBxCut") doBxCut = true;
  if (BxCut=="woBxCut") doBxCut = false;
  cout<<"doBxCut is: "<<doBxCut<<endl;

  if (CavCut=="wCavCut") doCavCut = true;
  if (CavCut=="woCavCut") doCavCut = false;
  cout<<"doCavCut is: "<<doCavCut<<endl;

  if (GenMuCut=="wGenMuCut") doGenMuCut = true;
  if (GenMuCut=="woGenMuCut") doGenMuCut = false;
  cout<<"doGenMuCut is: "<<doGenMuCut<<endl;

  if (SACut=="wSACut") doSACut = true;
  if (SACut=="woSACut") doSACut = false;
  cout<<"doSACut is: "<<doSACut<<endl;

  if (GenMuMatchedCut=="wGenMuMatchedCut") doGenMuMatchedCut = true;
  if (GenMuMatchedCut=="woGenMuMatched_cut") doGenMuMatchedCut = false;
  cout<<"doGenMuMatchedCut is: "<<doGenMuMatchedCut<<endl;

  if (TriggerCut=="wTriggerCut") doTriggerCut = true;
  if (TriggerCut=="woTriggerCut") doTriggerCut = false;
  cout<<"doTriggerCut is: "<<doTriggerCut<<endl;

  if (TriggerTurnOn_=="wTriggerTurnOn") doTriggerTurnOn = true;
  if (TriggerTurnOn_=="woTriggerTurnOn") doTriggerTurnOn = false;
  cout<<"doTriggerTurnOn_ is: "<<doTriggerTurnOn<<endl;

  if (NdsaCut=="wNdsaCut") doNdsaCut = true;
  if (NdsaCut=="woNdsaCut") doNdsaCut = false;
  cout<<"doNdsaCut is: "<<doNdsaCut<<endl;

  if (PtCut=="wPtCut") doPtCut = true;
  if (PtCut=="woPtCut") doPtCut = false;
  cout<<"doPtCut is: "<<doPtCut<<endl;

  if (ChaCut=="wChaCut") doChaCut = true;
  if (ChaCut=="woChaCut") doChaCut = false;
  cout<<"doChaCut is: "<<doChaCut<<endl;

  if (EtaCut=="wEtaCut") doEtaCut = true;
  if (EtaCut=="woEtaCut") doEtaCut = false;
  cout<<"doEtaCut is: "<<doEtaCut<<endl;

  if (UpperCut=="wUpperCut") doUpperCut = true;
  if (UpperCut=="woUpperCut") doUpperCut = false;
  cout<<"doUpperCut is: "<<doUpperCut<<endl;

  if (RpcCut=="wRpcCut") doRpcCut = true;
  if (RpcCut=="woRpcCut") doRpcCut = false;
  cout<<"doRpcCut is: "<<doRpcCut<<endl;

  if (DisStCut=="wDisStCut") doDisStCut = true;
  if (DisStCut=="woDisStCut") doDisStCut = false;
  cout<<"doDisStCut is: "<<doDisStCut<<endl;

  if (RpcBxCut=="wRpcBxCut") doRpcBxCut = true;
  if (RpcBxCut=="woRpcBxCut") doRpcBxCut = false;
  cout<<"doRpcBxCut is: "<<doRpcBxCut<<endl;

  if (DtHitsCut=="wDtHitsCut") doDtHitsCut = true;
  if (DtHitsCut=="woDtHitsCut") doDtHitsCut = false;
  cout<<"doDtHitsCut is: "<<doDtHitsCut<<endl;

  if (InvBetaErrCut=="wInvBetaErrCut") doInvBetaErrCut = true;
  if (InvBetaErrCut=="woInvBetaErrCut") doInvBetaErrCut = false;
  cout<<"doInvBetaErrCut is: "<<doInvBetaErrCut<<endl;

  if (CscHitsCut=="wCscHitsCut") doCscHitsCut = true;
  if (CscHitsCut=="woCscHitsCut") doCscHitsCut = false;
  cout<<"doCscHitsCut is: "<<doCscHitsCut<<endl;

  if (DtInvBetaCut=="wDtInvBetaCut") doDtInvBetaCut = true;
  if (DtInvBetaCut=="woDtInvBetaCut") doDtInvBetaCut = false;
  cout<<"doDtInvBetaCut is: "<<doDtInvBetaCut<<endl;

  if (TimeInOutCut=="wTimeInOutCut") doTimeInOutCut = true;
  if (TimeInOutCut=="woTimeInOutCut") doTimeInOutCut = false;
  cout<<"doTimeInOutCut is: "<<doTimeInOutCut<<endl;

  if (TimeInOutErrCut=="wTimeInOutErrCut") doTimeInOutErrCut = true;
  if (TimeInOutErrCut=="woTimeInOutErrCut") doTimeInOutErrCut = false;
  cout<<"doTimeInOutErrCut is: "<<doTimeInOutErrCut<<endl;

  if (DeltaTimeInOutCut=="wDeltaTimeInOutCut") doDeltaTimeInOutCut = true;
  if (DeltaTimeInOutCut=="woDeltaTimeInOutCut") doDeltaTimeInOutCut = false;
  cout<<"doDeltaTimeInOutCut is: "<<doDeltaTimeInOutCut<<endl;

  if (DeltaDtInvBetaCut=="wDeltaDtInvBetaCut") doDeltaDtInvBetaCut = true;
  if (DeltaDtInvBetaCut=="woDeltaDtInvBetaCut") doDeltaDtInvBetaCut = false;
  cout<<"doDeltaDtInvBetaCut is: "<<doDeltaDtInvBetaCut<<endl;

  if (TofDirCut=="wTofDirCut") doTofDirCut = true;
  if (TofDirCut=="woTofDirCut") doTofDirCut = false;
  cout<<"doTofDirCut is: "<<doTofDirCut<<endl;

  if (OppEtaCut=="wOppEtaCut") doOppEtaCut = true;
  if (OppEtaCut=="woOppEtaCut") doOppEtaCut = false;
  cout<<"doOppEtaCut is: "<<doOppEtaCut<<endl;

  if (OppPhiCut=="wOppPhiCut") doOppPhiCut = true;
  if (OppPhiCut=="woOppPhiCut") doOppPhiCut = false;
  cout<<"doOppPhiCut is: "<<doOppPhiCut<<endl;

  if (ChargeCut=="wChargeCut") doChargeCut = true;
  if (ChargeCut=="woChargeCut") doChargeCut = false;
  cout<<"doChargeCut is: "<<doChargeCut<<endl;

  if (DxyCut=="wDxyCut") doDxyCut = true;
  if (DxyCut=="woDxyCut") doDxyCut = false;
  cout<<"doDxyCut is: "<<doDxyCut<<endl;

  if (TightPhi=="wTightPhi") doTightPhi = true;
  if (TightPhi=="woTightPhi") doTightPhi = false;
  cout<<"doTightPhi is: "<<doTightPhi<<endl;

  if (CosEnrich=="wCosEnrich") doCosEnrich = true;
  if (CosEnrich=="woCosEnrich") doCosEnrich = false;
  cout<<"doCosEnrich is: "<<doCosEnrich<<endl;

  if (Printout=="wPrintout") doPrintout = true;
  if (Printout=="woPrintout") doPrintout = false;
  cout<<"doPrintout is: "<<doPrintout<<endl;

  sscanf(BxCutValue,"%d",&BxCutValue_);

  sscanf(PreNdsaCutValue,"%d",&PreNdsaCutValue_);
  sscanf(PrePtCutValue,"%f",&PrePtCutValue_);
  sscanf(PreChaCutValue,"%d",&PreChaCutValue_);
  sscanf(PreEtaCutValue,"%f",&PreEtaCutValue_);
  sscanf(PreRpcCutValue,"%d",&PreRpcCutValue_);
  sscanf(PreDtHitsCutValue,"%d",&PreDtHitsCutValue_);
  sscanf(PreInvBetaErrCutValue,"%f",&PreInvBetaErrCutValue_);
  sscanf(PreCscHitsCutValue,"%d",&PreCscHitsCutValue_);

  sscanf(PtCutValue,"%f",&PtCutValue_);
  sscanf(ChaCutValue,"%d",&ChaCutValue_);
  sscanf(EtaCutValue,"%f",&EtaCutValue_);
  sscanf(RpcCutValue,"%d",&RpcCutValue_);
  sscanf(DisStCutValue,"%d",&DisStCutValue_);
  sscanf(DtHitsCutValue,"%d",&DtHitsCutValue_);
  sscanf(CscHitsCutValue,"%d",&CscHitsCutValue_);
  sscanf(DtInvBetaCutValue,"%f",&DtInvBetaCutValue_);
  sscanf(TimeInOutCutValue,"%f",&TimeInOutCutValue_);
  sscanf(TimeInOutErrCutValue,"%f",&TimeInOutErrCutValue_);
  sscanf(DeltaTimeInOutCutValue,"%f",&DeltaTimeInOutCutValue_);
  sscanf(DeltaDtInvBetaCutValue,"%f",&DeltaDtInvBetaCutValue_);
  sscanf(OppEtaCutValue,"%f",&OppEtaCutValue_);
  sscanf(OppPhiCutValue,"%f",&OppPhiCutValue_);
  sscanf(DxyCutValue,"%f",&DxyCutValue_);

  sscanf(abcdInvBetaCutValue,"%f",&abcdInvBetaCutValue_);
  sscanf(abcdPtCutValue,"%f",&abcdPtCutValue_);
  sscanf(abInvBetaCutValue,"%f",&abInvBetaCutValue_);
  sscanf(cInvBetaCutValue,"%f",&cInvBetaCutValue_);
  sscanf(acPtCutValue,"%f",&acPtCutValue_);
  sscanf(bPtCutValue,"%f",&bPtCutValue_);

  cout<<"file is: "<<file<<endl;
  TFile* f1;
  if(host_=="brux") f1 = new TFile(file);
  else f1 = TFile::Open(file);

  if(!f1->IsZombie()) cout<<"opened input file"<<endl;
  else {
    cout<<"problem with input file?"<<endl;
    if(host_=="brux"){
      file = "/mnt/hadoop/store/user/jalimena/Ntuples/" + file_dataset + "/stoppedHSCPMuonTree.root";
      f1 = new TFile(file);
      if(!f1->IsZombie()) cout<<"opened input file on second attempt"<<endl;
      else{
	file = "/user_data/alimena/Ntuples/" + file_dataset + "/stoppedHSCPMuonTree.root";
	f1 = new TFile(file);
	if(!f1->IsZombie()) cout<<"opened input file on third attempt"<<endl;
      }
    }
  }

  TString new_file = "blah2";
  if ((BxCut=="wBxCut" || BxCut=="wBxCut") && (CavCut=="wCavCut" || CavCut=="woCavCut") && (GenMuCut=="wGenMuCut" || GenMuCut=="woGenMuCut") && (SACut=="wSACut" || SACut=="woSACut")  && (GenMuMatchedCut=="wGenMuMatchedCut" || GenMuMatchedCut=="woGenMuMatchedCut") && (TriggerCut=="wTriggerCut" || TriggerCut=="woTriggerCut") && (PtCut=="wPtCut" || PtCut=="woPtCut") && (ChaCut=="wChaCut" || ChaCut=="woChaCut")  && (EtaCut=="wEtaCut" || EtaCut=="woEtaCut")  && (UpperCut=="wUpperCut" || UpperCut=="woUpperCut") && (RpcCut=="wRpcCut" || RpcCut=="woRpcCut") && (DisStCut=="wDisStCut" || DisStCut=="woDisStCut") && (RpcBxCut=="wRpcBxCut" || RpcBxCut=="woRpcBxCut") && (DtHitsCut=="wDtHitsCut" || DtHitsCut=="woDtHitsCut") && (CscHitsCut=="wCscHitsCut" || CscHitsCut=="woCscHitsCut") && (DtInvBetaCut=="wDtInvBetaCut" || DtInvBetaCut=="woDtInvBetaCut") && (TimeInOutCut=="wTimeInOutCut" || TimeInOutCut=="woTimeInOutCut") && (TimeInOutErrCut=="wTimeInOutErrCut" || TimeInOutErrCut=="woTimeInOutErrCut") && (OppEtaCut=="wOppEtaCut" || OppEtaCut=="woOppEtaCut") && (OppPhiCut=="wOppPhiCut" || OppPhiCut=="woOppPhiCut") && (TightPhi=="wTightPhi" || TightPhi=="woTightPhi") && (CosEnrich=="wCosEnrich" || CosEnrich=="woCosEnrich")){
    if(host_=="cmsl") new_file = "/uscms/home/alimena/histos/" + file_dataset + "/" + BxCut + "_" + CavCut + "_" + GenMuCut + "_" + SACut  + "_" + GenMuMatchedCut  + "_" + TriggerCut  + "_" + PtCut  + "_" + ChaCut  + "_" + EtaCut + "_" + UpperCut + "_" + RpcCut  + "_" + DisStCut + "_" + RpcBxCut + "_" + DtHitsCut + "_" + CscHitsCut + "_" + DtInvBetaCut + "_" + TimeInOutCut + "_" + OppEtaCut + "_" + OppPhiCut + "_" + TightPhi + "_" + CosEnrich + ".root";
    if(host_=="brux") new_file = "/home/alimena/histos/" + file_dataset + "/" + BxCut + "_" + CavCut + "_" + GenMuCut + "_" + SACut  + "_" + GenMuMatchedCut  + "_" + TriggerCut  + "_" + PtCut  + "_" + ChaCut  + "_" + EtaCut  + "_" + UpperCut + "_" + RpcCut + "_" +  DisStCut + "_" + RpcBxCut + "_" + "_" + DtHitsCut + "_" + CscHitsCut + "_" + DtInvBetaCut + "_" + TimeInOutCut + "_" + OppEtaCut + "_" + OppPhiCut + "_" + TightPhi + "_" + CosEnrich + ".root";
    if(host_=="lxpl") new_file = "/afs/cern.ch/user/j/jalimena/public/histos/" + file_dataset + "/" + BxCut + "_" + CavCut + "_" + GenMuCut+ "_" + SACut  + "_" + GenMuMatchedCut  + "_" + TriggerCut  + "_" + PtCut  + "_" + ChaCut  + "_" + EtaCut  + "_" + UpperCut + "_" + RpcCut + "_" +  DisStCut + "_" + RpcBxCut + "_" + DtHitsCut + "_" + CscHitsCut + "_" + DtInvBetaCut + "_" + TimeInOutCut + "_" + OppEtaCut + "_" + OppPhiCut + "_" + TightPhi + "_" + CosEnrich + ".root";
  }
  if (BxCut!="wBxCut" && BxCut!="woBxCut") cout<<"problem w BxCut assignment!!!"<<endl;
  if (CavCut!="wCavCut" && CavCut!="woCavCut") cout<<"problem w CavCut assignment!!!"<<endl;
  if (GenMuCut!="wGenMuCut" && GenMuCut!="woGenMuCut") cout<<"problem w GenMuCut assignment!!!"<<endl;
  if (SACut!="wSACut" && SACut!="woSACut") cout<<"problem w SACut assignment!!!"<<endl;
  if (GenMuMatchedCut!="wGenMuMatchedCut" && GenMuMatchedCut!="woGenMuMatchedCut") cout<<"problem w GenMuMatchedCut assignment!!!"<<endl;
  if (TriggerCut!="wTriggerCut" && TriggerCut!="woTriggerCut") cout<<"problem w TriggerCut assignment!!!"<<endl;
  if (TriggerTurnOn_!="wTriggerTurnOn" && TriggerTurnOn_!="woTriggerTurnOn") cout<<"problem w TriggerTurnOn assignment!!!"<<endl;
  if (NdsaCut!="wNdsaCut" && NdsaCut!="woNdsaCut") cout<<"problem w NdsaCut assignment!!!"<<endl;
  if (PtCut!="wPtCut" && PtCut!="woPtCut") cout<<"problem w PtCut assignment!!!"<<endl;
  if (ChaCut!="wChaCut" && ChaCut!="woChaCut") cout<<"problem w ChaCut assignment!!!"<<endl;
  if (EtaCut!="wEtaCut" && EtaCut!="woEtaCut") cout<<"problem w EtaCut assignment!!!"<<endl;
  if (UpperCut!="wUpperCut" && UpperCut!="woUpperCut") cout<<"problem w UpperCut assignment!!!"<<endl;
  if (RpcCut!="wRpcCut" && RpcCut!="woRpcCut") cout<<"problem w RpcCut assignment!!!"<<endl;
  if (DisStCut!="wDisStCut" && DisStCut!="woDisStCut") cout<<"problem w DisStCut assignment!!!"<<endl;
  if (RpcBxCut!="wRpcBxCut" && RpcBxCut!="woRpcBxCut") cout<<"problem w RpcBxCut assignment!!!"<<endl;
  if (DtHitsCut!="wDtHitsCut" && DtHitsCut!="woDtHitsCut") cout<<"problem w DtHitsCut assignment!!!"<<endl;
  if (InvBetaErrCut!="wInvBetaErrCut" && InvBetaErrCut!="woInvBetaErrCut") cout<<"problem w InvBetaErrCut assignment!!!"<<endl;
  if (CscHitsCut!="wCscHitsCut" && CscHitsCut!="woCscHitsCut") cout<<"problem w CscHitsCut assignment!!!"<<endl;
  if (DtInvBetaCut!="wDtInvBetaCut" && DtInvBetaCut!="woDtInvBetaCut") cout<<"problem w DtInvBetaCut assignment!!!"<<endl;
  if (TimeInOutCut!="wTimeInOutCut" && TimeInOutCut!="woTimeInOutCut") cout<<"problem w TimeInOutCut assignment!!!"<<endl;
  if (TimeInOutErrCut!="wTimeInOutErrCut" && TimeInOutErrCut!="woTimeInOutErrCut") cout<<"problem w TimeInOutErrCut assignment!!!"<<endl;
  if (DeltaTimeInOutCut!="wDeltaTimeInOutCut" && DeltaTimeInOutCut!="woDeltaTimeInOutCut") cout<<"problem w DeltaTimeInOutCut assignment!!!"<<endl;
  if (DeltaDtInvBetaCut!="wDeltaDtInvBetaCut" && DeltaDtInvBetaCut!="woDeltaDtInvBetaCut") cout<<"problem w DeltaDtInvBetaCut assignment!!!"<<endl;
  if (TofDirCut!="wTofDirCut" && TofDirCut!="woTofDirCut") cout<<"problem w TofDirCut assignment!!!"<<endl;
  if (OppEtaCut!="wOppEtaCut" && OppEtaCut!="woOppEtaCut") cout<<"problem w OppEtaCut assignment!!!"<<endl;
  if (OppPhiCut!="wOppPhiCut" && OppPhiCut!="woOppPhiCut") cout<<"problem w OppPhiCut assignment!!!"<<endl;
  if (ChargeCut!="wChargeCut" && ChargeCut!="woChargeCut") cout<<"problem w ChargeCut assignment!!!"<<endl;
  if (DxyCut!="wDxyCut" && DxyCut!="woDxyCut") cout<<"problem w DxyCut assignment!!!"<<endl;
  if (TightPhi!="wTightPhi" && TightPhi!="woTightPhi") cout<<"problem w TightPhi assignment!!!"<<endl;
  if (CosEnrich!="wCosEnrich" && CosEnrich!="woCosEnrich") cout<<"problem w CosEnrich assignment!!!"<<endl;
  if (Printout!="wPrintout" && Printout!="woPrintout") cout<<"problem w Printout assignment!!!"<<endl;
  
  TFile* fnew = new TFile("blah","recreate");
  if(Printout=="woPrintout"){
    fnew = new TFile(new_file, "recreate");
    cout<<"opened output file"<<endl;
  }
  
  /*
  TString simpleTree_file = "/home/alimena/histos/" + file_dataset + "/simpleTree.root";
  TFile* f_simpleTree = new TFile(simpleTree_file,"recreate");
  */
  //get text files
  const int NumPtBins = 500;
  //const int NumPtBins = 160;
  double eventweightPt[NumPtBins][NumPtBins];
  ifstream inPt;
  TString weightFile = "/home/alimena/plots/txtfiles/DoublyChargedHiggsEventWeights/PtWeights_"+file_dataset+".txt";
  //TString weightFile = "/home/alimena/plots/txtfiles/DoublyChargedHiggsEventWeights/PtWeights_preselected_"+file_dataset+".txt";
  //TString weightFile = "/home/alimena/plots/txtfiles/DoublyChargedHiggsEventWeights/EtaWeights_preselected_"+file_dataset+".txt";
  inPt.open(weightFile, ios::in);
  cout<<"opened weight text file: "<<weightFile<<endl;

  for(int i=0;i<NumPtBins; i++){
    for(int j=0;j<NumPtBins; j++){
      inPt >> eventweightPt[i][j];
      cout<<"eventweightPt["<<i<<"]["<<j<<"] is: "<<eventweightPt[i][j]<<endl;
      if (!inPt.good()) break;
    }
  }


  ifstream inDuplicateEvents;
  TString duplicateEventsFile = "/home/alimena/Analysis/CMSSW_7_2_5/src/StoppedHSCPMuon/Ntuples/txtfiles/StoppedParticleDuplicateEvents/duplicateEvents_"+file_dataset+".txt";
  inDuplicateEvents.open(duplicateEventsFile, ios::in);
  cout<<"opened duplicateEvents text file: "<<duplicateEventsFile<<endl;    
  const int NumLines = count(istreambuf_iterator<char>(inDuplicateEvents), istreambuf_iterator<char>(), '\n');
  inDuplicateEvents.close();
  //const int NumLines = 50;
  cout<<"there are "<<NumLines<<" lines in the file"<<endl;
  int entryNumber[NumLines];
  ULong_t eventNumber[NumLines];
  //const int NumGoodEntries = NumLines/2;
  //int goodEntryNumber[NumGoodEntries];

  inDuplicateEvents.open(duplicateEventsFile, ios::in);
  for(int i=0;i<NumLines; i++){
    inDuplicateEvents >> entryNumber[i] >> eventNumber[i];
    //cout<<"entryNumber["<<i<<"]"<<" is: "<<entryNumber[i]<<", eventNumber is: "<<eventNumber[i]<<endl;
    if (!inDuplicateEvents.good()) break;
  }
  inDuplicateEvents.close();

  /*
  for(int i=0;i<NumLines; i++){
    for(int j=0;j<NumLines; j++){
      if(i<j){
	if(eventNumber[i]==eventNumber[j]){
	  cout<<"eventNumber is: "<<eventNumber[i]<<", 1st entry is: "<<entryNumber[i]<<"(i=="<<i<<"), 2nd entry is: "<<entryNumber[j]<<"(j=="<<j<<")"<<endl;
	  goodEntryNumber[i]=entryNumber[i];
	  cout<<"goodEntryNumber is: "<<goodEntryNumber[i]<<endl;
	}
      }
    }
  }
  */



  ifstream inPreselectedEvents;
  TString preselectedEventsFile = "/home/alimena/Analysis/CMSSW_7_2_5/src/StoppedHSCPMuon/Ntuples/bin/preselectedList.txt";
  inPreselectedEvents.open(preselectedEventsFile, ios::in);
  cout<<"opened preselectedEvents text file: "<<preselectedEventsFile<<endl;    
  const int NumLinesPre = count(istreambuf_iterator<char>(inPreselectedEvents), istreambuf_iterator<char>(), '\n');
  inPreselectedEvents.close();
  //const int NumLines = 50;
  cout<<"there are "<<NumLinesPre<<" lines in the file"<<endl;
  ULong_t eventNumberPre[NumLinesPre];
  //const int NumGoodEntries = NumLines/2;
  //int goodEntryNumber[NumGoodEntries];

  inPreselectedEvents.open(preselectedEventsFile, ios::in);
  for(int i=0;i<NumLinesPre; i++){
    inPreselectedEvents >> eventNumberPre[i];
    //cout<<"entryNumber["<<i<<"]"<<" is: "<<entryNumber[i]<<", eventNumber is: "<<eventNumber[i]<<endl;
    if (!inPreselectedEvents.good()) break;
  }
  inPreselectedEvents.close();

  //get tree
  TTree* tree = (TTree*)f1->Get("stoppedHSCPMuonTree/StoppedHSCPMuonTree");
  //TTree* tree = (TTree*)f1->Get("ABCDStoppedHSCPMuonTree");
  //tree->Print();
  //tree->Show(0);

  //StoppedHSCPMuonEvent* events = new StoppedHSCPMuonEvent();
  StoppedHSCPMuonEvent* events = 0;

  //set branch address
  tree->SetBranchAddress("events",&events);

  //get entries for data_tree (read in the old tree), set new variables, fill new tree
  Int_t nentries = tree->GetEntriesFast();
  //Int_t nentries = tree->GetEntries();
  cout<<"number of entries is: "<<nentries<<endl;


  //make new tree (write to same file as histograms)
  TTree* ABCDtree = new TTree("ABCDStoppedHSCPMuonTree","");
  StoppedHSCPMuonEvent* ABCDevent = new StoppedHSCPMuonEvent();
  ABCDtree->Branch("events", "StoppedHSCPMuonEvent", &ABCDevent, 64000, 1);
  cout<<"made new events branch"<<endl;

  /*
  //simple tree
  TTree* simpleTree = new TTree("tree","");

  // Declaration of new leaf types
  Bool_t l1SingleMu6NoBptx, hltL2Mu10NoVertexNoBptx3BX, hltL2Mu20NoVertexNoBptx3BX, hltL2Mu30NoVertexNoBptx3BX, hltL2Mu10NoVertexNoBptx3BXNoHalo, hltL2Mu20NoVertexNoBptx3BXNoHalo, hltL2Mu30NoVertexNoBptx3BXNoHalo,hltL2Mu20NoVertex2ChaNoBptx3BXNoHalo, hltL2Mu30NoVertex2ChaNoBptx3BXNoHalo;    

  Int_t runNumber, evtNumber, lumiSection, bxNumber, mcMuonId_upper, mcMuonCharge_upper, mcMuonStatus_upper, mcMuonMotherId_upper, mcMuonId_lower, mcMuonCharge_lower, mcMuonStatus_lower, mcMuonMotherId_lower, mcStoppedParticleId, mcStoppedParticleCharge, DTSegment_N, CSCSegment_N, nDSA, muDisplacedStandAloneCharge_upper, muDisplacedStandAloneNHitsMuon_upper,  muDisplacedStandAloneNHitsCsc_upper,  muDisplacedStandAloneNHitsDt_upper,  muDisplacedStandAloneNHitsRpc_upper,  muDisplacedStandAloneNRpcDof_upper, muDisplacedStandAloneNStations_upper, muDisplacedStandAloneNChambersCsc_upper, muDisplacedStandAloneNChambersDt_upper, muDisplacedStandAloneNChambersRpc_upper, muDisplacedStandAloneDtTofNDof_upper, muDisplacedStandAloneDtTofDirection_upper, muDisplacedStandAloneBxPattern_upper, muDisplacedStandAloneCharge_lower, muDisplacedStandAloneNHitsMuon_lower,  muDisplacedStandAloneNHitsCsc_lower,  muDisplacedStandAloneNHitsDt_lower,  muDisplacedStandAloneNHitsRpc_lower,  muDisplacedStandAloneNRpcDof_lower, muDisplacedStandAloneNStations_lower, muDisplacedStandAloneNChambersCsc_lower, muDisplacedStandAloneNChambersDt_lower, muDisplacedStandAloneNChambersRpc_lower, muDisplacedStandAloneDtTofNDof_lower, muDisplacedStandAloneDtTofDirection_lower, muDisplacedStandAloneBxPattern_lower;

  Double_t mcMuonMass_upper, mcMuonPx_upper, mcMuonPy_upper, mcMuonPz_upper, mcMuonPt_upper, mcMuonP_upper, mcMuonPhi_upper, mcMuonEta_upper, mcMuonVx_upper, mcMuonVy_upper, mcMuonVz_upper, mcMuonMass_lower, mcMuonPx_lower, mcMuonPy_lower, mcMuonPz_lower, mcMuonPt_lower, mcMuonP_lower, mcMuonPhi_lower, mcMuonEta_lower, mcMuonVx_lower, mcMuonVy_lower, mcMuonVz_lower, mcStoppedParticleMass, mcStoppedParticleX, mcStoppedParticleY, mcStoppedParticleZ, mcStoppedParticleR, mcStoppedParticleEta, mcStoppedParticlePhi, mcStoppedParticleTime, muDisplacedStandAloneP_upper, muDisplacedStandAlonePt_upper, muDisplacedStandAlonePx_upper, muDisplacedStandAlonePy_upper, muDisplacedStandAlonePz_upper, muDisplacedStandAloneEta_upper, muDisplacedStandAlonePhi_upper, muDisplacedStandAloneNormalizedChi2_upper,  muDisplacedStandAloneDxy_upper,  muDisplacedStandAloneDz_upper, muDisplacedStandAloneDtTofInverseBeta_upper, muDisplacedStandAloneDtTofInverseBetaErr_upper, muDisplacedStandAloneDtTofFreeInverseBeta_upper, muDisplacedStandAloneDtTofFreeInverseBetaErr_upper, muDisplacedStandAloneDtTofTimeAtIpInOut_upper, muDisplacedStandAloneDtTofTimeAtIpInOutErr_upper, muDisplacedStandAloneDtTofTimeAtIpOutIn_upper, muDisplacedStandAloneDtTofTimeAtIpOutInErr_upper, muDisplacedStandAloneP_lower, muDisplacedStandAlonePt_lower, muDisplacedStandAlonePx_lower, muDisplacedStandAlonePy_lower, muDisplacedStandAlonePz_lower, muDisplacedStandAloneEta_lower, muDisplacedStandAlonePhi_lower, muDisplacedStandAloneNormalizedChi2_lower,  muDisplacedStandAloneDxy_lower,  muDisplacedStandAloneDz_lower, muDisplacedStandAloneDtTofInverseBeta_lower, muDisplacedStandAloneDtTofInverseBetaErr_lower, muDisplacedStandAloneDtTofFreeInverseBeta_lower, muDisplacedStandAloneDtTofFreeInverseBetaErr_lower, muDisplacedStandAloneDtTofTimeAtIpInOut_lower, muDisplacedStandAloneDtTofTimeAtIpInOutErr_lower, muDisplacedStandAloneDtTofTimeAtIpOutIn_lower, muDisplacedStandAloneDtTofTimeAtIpOutInErr_lower;

  //set new branch addresses
  simpleTree->Branch("runNumber",&runNumber,"runNumber/I");
  simpleTree->Branch("eventNumber",&evtNumber,"eventNumber/I");
  simpleTree->Branch("lumiSection",&lumiSection,"lumiSection/I");
  simpleTree->Branch("bxNumber",&bxNumber,"bxNumber/I");

  simpleTree->Branch("mcMuonId_upper",&mcMuonId_upper,"mcMuonId_upper/I");	      
  simpleTree->Branch("mcMuonMass_upper",&mcMuonMass_upper,"mcMuonMass_upper/D");	      
  simpleTree->Branch("mcMuonCharge_upper",&mcMuonCharge_upper,"mcMuonCharge_upper/I");  
  simpleTree->Branch("mcMuonPx_upper",&mcMuonPx_upper,"mcMuonPx_upper/D");	      
  simpleTree->Branch("mcMuonPy_upper",&mcMuonPy_upper,"mcMuonPy_upper/D");	      
  simpleTree->Branch("mcMuonPz_upper",&mcMuonPz_upper,"mcMuonPz_upper/D");	      
  simpleTree->Branch("mcMuonPt_upper",&mcMuonPt_upper,"mcMuonPt_upper/D");	      
  simpleTree->Branch("mcMuonP_upper",&mcMuonP_upper,"mcMuonP_upper/D");	      
  simpleTree->Branch("mcMuonPhi_upper",&mcMuonPhi_upper,"mcMuonPhi_upper/D");	      
  simpleTree->Branch("mcMuonEta_upper",&mcMuonEta_upper,"mcMuonEta_upper/D");	      
  simpleTree->Branch("mcMuonVx_upper",&mcMuonVx_upper,"mcMuonVx_upper/D");	      
  simpleTree->Branch("mcMuonVy_upper",&mcMuonVy_upper,"mcMuonVy_upper/D");	      
  simpleTree->Branch("mcMuonVz_upper",&mcMuonVz_upper,"mcMuonVz_upper/D");	      
  simpleTree->Branch("mcMuonStatus_upper",&mcMuonStatus_upper,"mcMuonStatus_upper/I");  
  simpleTree->Branch("mcMuonMotherId_upper",&mcMuonMotherId_upper,"mcMuonMotherId_upper/I");

  simpleTree->Branch("mcMuonId_lower",&mcMuonId_lower,"mcMuonId_lower/I");
  simpleTree->Branch("mcMuonMass_lower",&mcMuonMass_lower,"mcMuonMass_lower/D");	      
  simpleTree->Branch("mcMuonCharge_lower",&mcMuonCharge_lower,"mcMuonCharge_lower/I");  
  simpleTree->Branch("mcMuonPx_lower",&mcMuonPx_lower,"mcMuonPx_lower/D");	      
  simpleTree->Branch("mcMuonPy_lower",&mcMuonPy_lower,"mcMuonPy_lower/D");	      
  simpleTree->Branch("mcMuonPz_lower",&mcMuonPz_lower,"mcMuonPz_lower/D");	      
  simpleTree->Branch("mcMuonPt_lower",&mcMuonPt_lower,"mcMuonPt_lower/D");	      
  simpleTree->Branch("mcMuonP_lower",&mcMuonP_lower,"mcMuonP_lower/D");	      
  simpleTree->Branch("mcMuonPhi_lower",&mcMuonPhi_lower,"mcMuonPhi_lower/D");	      
  simpleTree->Branch("mcMuonEta_lower",&mcMuonEta_lower,"mcMuonEta_lower/D");	      
  simpleTree->Branch("mcMuonVx_lower",&mcMuonVx_lower,"mcMuonVx_lower/D");	      
  simpleTree->Branch("mcMuonVy_lower",&mcMuonVy_lower,"mcMuonVy_lower/D");	      
  simpleTree->Branch("mcMuonVz_lower",&mcMuonVz_lower,"mcMuonVz_lower/D");	      
  simpleTree->Branch("mcMuonStatus_lower",&mcMuonStatus_lower,"mcMuonStatus_lower/I");  
  simpleTree->Branch("mcMuonMotherId_lower",&mcMuonMotherId_lower,"mcMuonMotherId_lower/I");

  simpleTree->Branch("mcStoppedParticleId",&mcStoppedParticleId,"mcStoppedParticleId/I");	  
  simpleTree->Branch("mcStoppedParticleMass",&mcStoppedParticleMass,"mcStoppedParticleMass/D");	  
  simpleTree->Branch("mcStoppedParticleCharge",&mcStoppedParticleCharge,"mcStoppedParticleCharge/I");  
  simpleTree->Branch("mcStoppedParticleX",&mcStoppedParticleX,"mcStoppedParticleX/D");	  
  simpleTree->Branch("mcStoppedParticleY",&mcStoppedParticleY,"mcStoppedParticleY/D");	  
  simpleTree->Branch("mcStoppedParticleZ",&mcStoppedParticleZ,"mcStoppedParticleZ/D");	  
  simpleTree->Branch("mcStoppedParticleR",&mcStoppedParticleR,"mcStoppedParticleR/D");	  
  simpleTree->Branch("mcStoppedParticleEta",&mcStoppedParticleEta,"mcStoppedParticleEta/D");	  
  simpleTree->Branch("mcStoppedParticlePhi",&mcStoppedParticlePhi,"mcStoppedParticlePhi/D");	  
  simpleTree->Branch("mcStoppedParticleTime",&mcStoppedParticleTime,"mcStoppedParticleTime/D");    
    
  simpleTree->Branch("l1SingleMu6NoBptx",&l1SingleMu6NoBptx,"l1SingleMu6NoBptx/B");		        
  simpleTree->Branch("hltL2Mu10NoVertexNoBptx3BX",&hltL2Mu10NoVertexNoBptx3BX,"hltL2Mu10NoVertexNoBptx3BX/B");	        
  simpleTree->Branch("hltL2Mu20NoVertexNoBptx3BX",&hltL2Mu20NoVertexNoBptx3BX,"hltL2Mu20NoVertexNoBptx3BX/B");	        
  simpleTree->Branch("hltL2Mu30NoVertexNoBptx3BX",&hltL2Mu30NoVertexNoBptx3BX,"hltL2Mu30NoVertexNoBptx3BX/B");	        
  simpleTree->Branch("hltL2Mu10NoVertexNoBptx3BXNoHalo",&hltL2Mu10NoVertexNoBptx3BXNoHalo,"hltL2Mu10NoVertexNoBptx3BXNoHalo/B");    
  simpleTree->Branch("hltL2Mu20NoVertexNoBptx3BXNoHalo",&hltL2Mu20NoVertexNoBptx3BXNoHalo,"hltL2Mu20NoVertexNoBptx3BXNoHalo/B");    
  simpleTree->Branch("hltL2Mu30NoVertexNoBptx3BXNoHalo",&hltL2Mu30NoVertexNoBptx3BXNoHalo,"hltL2Mu30NoVertexNoBptx3BXNoHalo/B");    
  simpleTree->Branch("hltL2Mu20NoVertex2ChaNoBptx3BXNoHalo",&hltL2Mu20NoVertex2ChaNoBptx3BXNoHalo,"hltL2Mu20NoVertex2ChaNoBptx3BXNoHalo/B");
  simpleTree->Branch("hltL2Mu30NoVertex2ChaNoBptx3BXNoHalo",&hltL2Mu30NoVertex2ChaNoBptx3BXNoHalo,"hltL2Mu30NoVertex2ChaNoBptx3BXNoHalo/B");
  
  simpleTree->Branch("DTSegment_N",&DTSegment_N,"DTSegment_N/I");
  simpleTree->Branch("CSCSegment_N",&CSCSegment_N,"CSCSegment_N/I");
  simpleTree->Branch("nDSA",&nDSA,"nDSA/I");
  simpleTree->Branch("muDisplacedStandAloneP_upper",&muDisplacedStandAloneP_upper,"muDisplacedStandAloneP_upper/D");
  simpleTree->Branch("muDisplacedStandAlonePt_upper",&muDisplacedStandAlonePt_upper,"muDisplacedStandAlonePt_upper/D");
  simpleTree->Branch("muDisplacedStandAlonePx_upper",&muDisplacedStandAlonePx_upper,"muDisplacedStandAlonePx_upper/D");
  simpleTree->Branch("muDisplacedStandAlonePy_upper",&muDisplacedStandAlonePy_upper,"muDisplacedStandAlonePy_upper/D");
  simpleTree->Branch("muDisplacedStandAlonePz_upper",&muDisplacedStandAlonePz_upper,"muDisplacedStandAlonePz_upper/D");
  simpleTree->Branch("muDisplacedStandAloneEta_upper",&muDisplacedStandAloneEta_upper,"muDisplacedStandAloneEta_upper/D");
  simpleTree->Branch("muDisplacedStandAlonePhi_upper",&muDisplacedStandAlonePhi_upper,"muDisplacedStandAlonePhi_upper/D");
  simpleTree->Branch("muDisplacedStandAloneCharge_upper",&muDisplacedStandAloneCharge_upper,"muDisplacedStandAloneCharge_upper/I");
  simpleTree->Branch("muDisplacedStandAloneTrackNormalizedChi2_upper",&muDisplacedStandAloneNormalizedChi2_upper,"muDisplacedStandAloneTrackNormalizedChi2_upper/D");
  simpleTree->Branch("muDisplacedStandAloneTrackDxy_upper",&muDisplacedStandAloneDxy_upper,"muDisplacedStandAloneTrackDxy_upper/D");
  simpleTree->Branch("muDisplacedStandAloneTrackDz_upper",&muDisplacedStandAloneDz_upper,"muDisplacedStandAloneTrackDz_upper/D");
  simpleTree->Branch("muDisplacedStandAloneTrackNHitsMuon_upper",&muDisplacedStandAloneNHitsMuon_upper,"muDisplacedStandAloneTrackNHitsMuon_upper/I");
  simpleTree->Branch("muDisplacedStandAloneTrackNHitsCsc_upper",&muDisplacedStandAloneNHitsCsc_upper,"muDisplacedStandAloneTrackNHitsCsc_upper/I");
  simpleTree->Branch("muDisplacedStandAloneTrackNHitsDt_upper",&muDisplacedStandAloneNHitsDt_upper,"muDisplacedStandAloneTrackNHitsDt_upper/I");
  simpleTree->Branch("muDisplacedStandAloneTrackNHitsRpc_upper",&muDisplacedStandAloneNHitsRpc_upper,"muDisplacedStandAloneTrackNHitsRpc_upper/I");
  simpleTree->Branch("muDisplacedStandAloneTrackNRpcDof_upper",&muDisplacedStandAloneNRpcDof_upper,"muDisplacedStandAloneTrackNRpcDof_upper/I");
  simpleTree->Branch("muDisplacedStandAloneTrackNStations_upper",&muDisplacedStandAloneNStations_upper,"muDisplacedStandAloneTrackNStations_upper/I");
  simpleTree->Branch("muDisplacedStandAloneTrackNChambersCsc_upper",&muDisplacedStandAloneNChambersCsc_upper,"muDisplacedStandAloneTrackNChambersCsc_upper/I");
  simpleTree->Branch("muDisplacedStandAloneTrackNChambersDt_upper",&muDisplacedStandAloneNChambersDt_upper,"muDisplacedStandAloneTrackNChambersDt_upper/I");
  simpleTree->Branch("muDisplacedStandAloneTrackNChambersRpc_upper",&muDisplacedStandAloneNChambersRpc_upper,"muDisplacedStandAloneTrackNChambersRpc_upper/I");
  simpleTree->Branch("muDisplacedStandAloneTrackDtTofNDof_upper",&muDisplacedStandAloneDtTofNDof_upper,"muDisplacedStandAloneTrackDtTofNDof_upper/I");
  simpleTree->Branch("muDisplacedStandAloneTrackDtTofInverseBeta_upper",&muDisplacedStandAloneDtTofInverseBeta_upper,"muDisplacedStandAloneTrackDtTofInverseBeta_upper/D");
  simpleTree->Branch("muDisplacedStandAloneTrackDtTofInverseBetaErr_upper",&muDisplacedStandAloneDtTofInverseBetaErr_upper,"muDisplacedStandAloneTrackDtTofInverseBetaErr_upper/D");
  simpleTree->Branch("muDisplacedStandAloneTrackDtTofFreeInverseBeta_upper",&muDisplacedStandAloneDtTofFreeInverseBeta_upper,"muDisplacedStandAloneTrackDtTofFreeInverseBeta_upper/D");
  simpleTree->Branch("muDisplacedStandAloneTrackDtTofFreeInverseBetaErr_upper",&muDisplacedStandAloneDtTofFreeInverseBetaErr_upper,"muDisplacedStandAloneTrackDtTofFreeInverseBetaErr_upper/D");
  simpleTree->Branch("muDisplacedStandAloneTrackDtTofTimeAtIpInOut_upper",&muDisplacedStandAloneDtTofTimeAtIpInOut_upper,"muDisplacedStandAloneTrackDtTofTimeAtIpInOut_upper/D");
  simpleTree->Branch("muDisplacedStandAloneTrackDtTofTimeAtIpInOutErr_upper",&muDisplacedStandAloneDtTofTimeAtIpInOutErr_upper,"muDisplacedStandAloneTrackDtTofTimeAtIpInOutErr_upper/D");
  simpleTree->Branch("muDisplacedStandAloneTrackDtTofTimeAtIpOutIn_upper",&muDisplacedStandAloneDtTofTimeAtIpOutIn_upper,"muDisplacedStandAloneTrackDtTofTimeAtIpOutIn_upper/D");
  simpleTree->Branch("muDisplacedStandAloneTrackDtTofTimeAtIpOutInErr_upper",&muDisplacedStandAloneDtTofTimeAtIpOutInErr_upper,"muDisplacedStandAloneTrackDtTofTimeAtIpOutInErr_upper/D");
  simpleTree->Branch("muDisplacedStandAloneTrackDtTofDirection_upper",&muDisplacedStandAloneDtTofDirection_upper,"muDisplacedStandAloneTrackDtTofDirection_upper/I");
  simpleTree->Branch("muDisplacedStandAloneBxPattern_upper",&muDisplacedStandAloneBxPattern_upper,"muDisplacedStandAloneBxPattern_upper/I");

  simpleTree->Branch("muDisplacedStandAloneP_lower",&muDisplacedStandAloneP_lower,"muDisplacedStandAloneP_lower/D");
  simpleTree->Branch("muDisplacedStandAlonePt_lower",&muDisplacedStandAlonePt_lower,"muDisplacedStandAlonePt_lower/D");
  simpleTree->Branch("muDisplacedStandAlonePx_lower",&muDisplacedStandAlonePx_lower,"muDisplacedStandAlonePx_lower/D");
  simpleTree->Branch("muDisplacedStandAlonePy_lower",&muDisplacedStandAlonePy_lower,"muDisplacedStandAlonePy_lower/D");
  simpleTree->Branch("muDisplacedStandAlonePz_lower",&muDisplacedStandAlonePz_lower,"muDisplacedStandAlonePz_lower/D");
  simpleTree->Branch("muDisplacedStandAloneEta_lower",&muDisplacedStandAloneEta_lower,"muDisplacedStandAloneEta_lower/D");
  simpleTree->Branch("muDisplacedStandAlonePhi_lower",&muDisplacedStandAlonePhi_lower,"muDisplacedStandAlonePhi_lower/D");
  simpleTree->Branch("muDisplacedStandAloneCharge_lower",&muDisplacedStandAloneCharge_lower,"muDisplacedStandAloneCharge_lower/I");
  simpleTree->Branch("muDisplacedStandAloneTrackNormalizedChi2_lower",&muDisplacedStandAloneNormalizedChi2_lower,"muDisplacedStandAloneTrackNormalizedChi2_lower/D");
  simpleTree->Branch("muDisplacedStandAloneTrackDxy_lower",&muDisplacedStandAloneDxy_lower,"muDisplacedStandAloneTrackDxy_lower/D");
  simpleTree->Branch("muDisplacedStandAloneTrackDz_lower",&muDisplacedStandAloneDz_lower,"muDisplacedStandAloneTrackDz_lower/D");
  simpleTree->Branch("muDisplacedStandAloneTrackNHitsMuon_lower",&muDisplacedStandAloneNHitsMuon_lower,"muDisplacedStandAloneTrackNHitsMuon_lower/I");
  simpleTree->Branch("muDisplacedStandAloneTrackNHitsCsc_lower",&muDisplacedStandAloneNHitsCsc_lower,"muDisplacedStandAloneTrackNHitsCsc_lower/I");
  simpleTree->Branch("muDisplacedStandAloneTrackNHitsDt_lower",&muDisplacedStandAloneNHitsDt_lower,"muDisplacedStandAloneTrackNHitsDt_lower/I");
  simpleTree->Branch("muDisplacedStandAloneTrackNHitsRpc_lower",&muDisplacedStandAloneNHitsRpc_lower,"muDisplacedStandAloneTrackNHitsRpc_lower/I");
  simpleTree->Branch("muDisplacedStandAloneTrackNRpcDof_lower",&muDisplacedStandAloneNRpcDof_lower,"muDisplacedStandAloneTrackNRpcDof_lower/I");
  simpleTree->Branch("muDisplacedStandAloneTrackNStations_lower",&muDisplacedStandAloneNStations_lower,"muDisplacedStandAloneTrackNStations_lower/I");
  simpleTree->Branch("muDisplacedStandAloneTrackNChambersCsc_lower",&muDisplacedStandAloneNChambersCsc_lower,"muDisplacedStandAloneTrackNChambersCsc_lower/I");
  simpleTree->Branch("muDisplacedStandAloneTrackNChambersDt_lower",&muDisplacedStandAloneNChambersDt_lower,"muDisplacedStandAloneTrackNChambersDt_lower/I");
  simpleTree->Branch("muDisplacedStandAloneTrackNChambersRpc_lower",&muDisplacedStandAloneNChambersRpc_lower,"muDisplacedStandAloneTrackNChambersRpc_lower/I");
  simpleTree->Branch("muDisplacedStandAloneTrackDtTofNDof_lower",&muDisplacedStandAloneDtTofNDof_lower,"muDisplacedStandAloneTrackDtTofNDof_lower/I");
  simpleTree->Branch("muDisplacedStandAloneTrackDtTofInverseBeta_lower",&muDisplacedStandAloneDtTofInverseBeta_lower,"muDisplacedStandAloneTrackDtTofInverseBeta_lower/D");
  simpleTree->Branch("muDisplacedStandAloneTrackDtTofInverseBetaErr_lower",&muDisplacedStandAloneDtTofInverseBetaErr_lower,"muDisplacedStandAloneTrackDtTofInverseBetaErr_lower/D");
  simpleTree->Branch("muDisplacedStandAloneTrackDtTofFreeInverseBeta_lower",&muDisplacedStandAloneDtTofFreeInverseBeta_lower,"muDisplacedStandAloneTrackDtTofFreeInverseBeta_lower/D");
  simpleTree->Branch("muDisplacedStandAloneTrackDtTofFreeInverseBetaErr_lower",&muDisplacedStandAloneDtTofFreeInverseBetaErr_lower,"muDisplacedStandAloneTrackDtTofFreeInverseBetaErr_lower/D");
  simpleTree->Branch("muDisplacedStandAloneTrackDtTofTimeAtIpInOut_lower",&muDisplacedStandAloneDtTofTimeAtIpInOut_lower,"muDisplacedStandAloneTrackDtTofTimeAtIpInOut_lower/D");
  simpleTree->Branch("muDisplacedStandAloneTrackDtTofTimeAtIpInOutErr_lower",&muDisplacedStandAloneDtTofTimeAtIpInOutErr_lower,"muDisplacedStandAloneTrackDtTofTimeAtIpInOutErr_lower/D");
  simpleTree->Branch("muDisplacedStandAloneTrackDtTofTimeAtIpOutIn_lower",&muDisplacedStandAloneDtTofTimeAtIpOutIn_lower,"muDisplacedStandAloneTrackDtTofTimeAtIpOutIn_lower/D");
  simpleTree->Branch("muDisplacedStandAloneTrackDtTofTimeAtIpOutInErr_lower",&muDisplacedStandAloneDtTofTimeAtIpOutInErr_lower,"muDisplacedStandAloneTrackDtTofTimeAtIpOutInErr_lower/D");
  simpleTree->Branch("muDisplacedStandAloneTrackDtTofDirection_lower",&muDisplacedStandAloneDtTofDirection_lower,"muDisplacedStandAloneTrackDtTofDirection_lower/I");
  simpleTree->Branch("muDisplacedStandAloneBxPattern_lower",&muDisplacedStandAloneBxPattern_lower,"muDisplacedStandAloneBxPattern_lower/I");
  */

  //for (Int_t i=0; i<100000; i++) {
    //for (Int_t i=0; i<500000; i++) {
  for (Int_t i=0; i<nentries; i++) {
  //for (Int_t i=0; i<2000; i++) {    
  //for (Int_t i=0; i<100; i++) {
    tree->GetEntry(i);
    //if(is_data && i%50000==0) cout<<"i is: "<<i<<endl;
    //if(!is_data && i%5000==0) cout<<"i is: "<<i<<endl;

    bool WFromTop = false;
    bool status1muon = false;
    bool tauFromStau = false;
    bool status1muonFromTau = false;
    bool status1muonFromMuon = false;
    bool status1muonFromNeutralino = false;
    bool status1muonFromW = false;
    bool status1muonFromBbaryon = false;
    bool status1muonFromCbaryon = false;
    bool status1muonFromSbaryon = false;
    bool status1muonFromBmeson = false;
    bool status1muonFromCmeson = false;
    bool status1muonFromJPsi = false;
    bool status1muonFromLightMeson = false;
    bool muonFromMchamp = false;
    bool status1muon_[15];
    bool status2H_[15];
    bool status1muonFromMchamp_[15];
    bool status1muonFromMuon_[15];
    for (UInt_t j=0; j<events->mcMuon_N; j++) {
      status1muon_[j]=false;
      status1muonFromMchamp_[j]=false;
      status1muonFromMuon_[j]=false;
    }
    int good_genMuons = 0;
    int good_genPosMuons = 0;
    int good_genNegMuons = 0;
    UInt_t genMu0_index = 999;
    //UInt_t genMu1_index = 999;
    //UInt_t genMuUpper_index = 999;
    //UInt_t genMuLower_index = 999;
    UInt_t genPosMu0_index = 999;
    UInt_t genPosMu1_index = 999;
    UInt_t genPosMuUpper_index = 999;
    UInt_t genPosMuLower_index = 999;
    UInt_t genNegMu0_index = 999;
    UInt_t genNegMu1_index = 999;
    UInt_t genNegMuUpper_index = 999;
    UInt_t genNegMuLower_index = 999;
    Double_t angle=-999.;
    Double_t anglePos=-999.;
    Double_t angleNeg=-999.;

    UInt_t simTrack0_index = 999;

    int nRhadron = 0;
    int rhadronId1 = 0;
    int rhadronId2 = 0;
    int rhadronCharge1 = -999;
    int rhadronCharge2 = -999;
    double rhadronPt1 = -999;
    double rhadronPt2 = -999;
    double rhadronEta1 = -999;
    double rhadronEta2 = -999;
    double rhadronPhi1 = -999;
    double rhadronPhi2 = -999;

    int good_genH = 0;
    UInt_t genH0_index = 999;
    UInt_t genH1_index = 999;
    UInt_t genHpos_index = 999;
    UInt_t genHneg_index = 999;

    int good_genStop = 0;
    UInt_t genStop0_index = 999;
    UInt_t genStop1_index = 999;
    UInt_t genStop2_index = 999;

    int good_genGluino = 0;
    UInt_t genGluino0_index = 999;
    UInt_t genGluino1_index = 999;
    UInt_t genGluino2_index = 999;

    int good_genTauPrime = 0;
    UInt_t genTauPrime0_index = 999;
    UInt_t genTauPrime1_index = 999;
    UInt_t genTauPrime2_index = 999;

    int good_genStau = 0;
    UInt_t genStau0_index = 999;
    UInt_t genStau1_index = 999;
    UInt_t genStau2_index = 999;

    int n_stoppedInDetector = 0;
    UInt_t stoppedPos_index = 999;
    UInt_t stoppedNeg_index = 999;
    UInt_t stopped_index = 999;
    UInt_t stoppedDetector0_index = 999;
    UInt_t stoppedDetector1_index = 999;

    bool pass_PreNdsa = false; 
    bool pass_Prept = false; 
    bool pass_Precha = false; 
    bool pass_Preeta = false; 
    bool pass_PreRPC = false; 
    bool pass_PreDtHits = false; 
    bool pass_PreInvBetaErr = false; 
    bool pass_PreCscHits = false;
    bool pass_Upper = false; 
    bool pass_pt = false; 
    bool pass_cha = false; 
    bool pass_eta = false; 
    bool pass_RPC = false; 
    bool pass_DisSt = false; 
    bool pass_DtHits = false; 
    bool pass_CscHits = false; 
    bool pass_DtInvBeta = false; 
    bool pass_TimeInOut = false; 
    bool pass_TimeInOutErr = false; 
    bool pass_TofDir = false; 
    bool pass_Rpc_Bx = false; 
    bool pass_OppEta = false; 
    bool pass_OppPhi = false;
    bool pass_Dxy = false;
    bool pass_UpperAndLower = false;
    bool pass_pt_2 = false;
    bool pass_cha_2 = false;
    bool pass_eta_2 = false;
    bool pass_RPC_2 = false;
    bool pass_DisSt_2 = false;
    bool pass_DtHits_2 = false;
    bool pass_OppEta_2 = false;
    bool pass_OppPhi_2 = false;
    bool pass_charge_2 = false;
    bool pass_Rpc_Bx_2 = false;
    bool pass_DtInvBeta_2 = false;
    bool pass_TimeInOut_2 = false;
    bool pass_TimeInOutErr_2 = false;
    bool pass_DeltaTimeInOut_2 = false;
    bool pass_DeltaDtInvBeta_2 = false;
    bool pass_TofDir_2 = false;

    int n_passPreselection, n_Upper, n_Lower;
    UInt_t upper_index = 999;
    UInt_t lower_index = 999;
    UInt_t presel0_index = 999;
    UInt_t presel1_index = 999;
    UInt_t presel2_index = 999;
    UInt_t presel3_index = 999;
    UInt_t highestPt_index = 999;
    UInt_t upper0_index = 999;
    UInt_t lower0_index = 999;
    UInt_t upper1_index = 999;
    UInt_t lower1_index = 999;
    UInt_t upper2_index = 999;
    UInt_t lower2_index = 999;

    UInt_t genMuMatched_DSA_index[15];
    UInt_t genMuMatched_mu_index[15];
    UInt_t genMuMatched_SA_index[15];
    UInt_t genMuMatched_SAUpdatedAtVtx_index[15];
    UInt_t genMuMatched_RSA_index[15];
    UInt_t genMuMatched_cosmic_index[15];

    for (UInt_t j=0; j<15; j++) {
      genMuMatched_DSA_index[j] = 999;
      genMuMatched_mu_index[j] = 999;
      genMuMatched_SA_index[j] = 999;
      genMuMatched_SAUpdatedAtVtx_index[j] = 999;
      genMuMatched_RSA_index[j] = 999;
      genMuMatched_cosmic_index[j] = 999;
    }

    double eventweightTauPrime = 1.0;

    //bool doHplusHistos = false;
    bool doHplusHistos = true;
    //for(int j=0;j<NumLinesPre; j++){
    //if(events->id==eventNumberPre[j]){
    //doHplusHistos = true;
	//cout<<"doPlusHistos, event number "<<events->id<<endl;
	//break;
    //}
    //}

    //find out what's happening at the gen level for signal MC
    if(file_dataset_ == "stop") stops(events, good_genMuons, genMu0_index, WFromTop, status1muon, status1muonFromW, status1muonFromMuon, nRhadron, rhadronId1, rhadronId2, rhadronCharge1, rhadronCharge2, rhadronPt1, rhadronPt2, rhadronEta1, rhadronEta2, rhadronPhi1, rhadronPhi2, good_genStop, genStop0_index, genStop1_index, genStop2_index);
    if(file_dataset_ == "glui") gluinos(events, good_genMuons, genMu0_index, status1muon, status1muonFromW, status1muonFromTau, status1muonFromMuon,
					status1muonFromBbaryon, status1muonFromCbaryon, status1muonFromSbaryon, status1muonFromBmeson, status1muonFromCmeson,
					status1muonFromJPsi, status1muonFromLightMeson, 
					good_genGluino, genGluino0_index, genGluino1_index, genGluino2_index);
    if(file_dataset_ == "mcha") mchamps(events, muonFromMchamp, status1muon_, status1muonFromMchamp_, status1muonFromMuon_, good_genMuons, good_genPosMuons, good_genNegMuons, 
					genMu0_index,
					genPosMu0_index, genPosMu1_index, genPosMuUpper_index, genPosMuLower_index,
					genNegMu0_index, genNegMu1_index, genNegMuUpper_index, genNegMuLower_index,
					anglePos, angleNeg,
					good_genTauPrime, genTauPrime0_index, genTauPrime1_index, genTauPrime2_index);
    if(file_dataset_ == "ppst" || file_dataset_ == "gmst" ) staus(events, good_genMuons, genMu0_index, tauFromStau, status1muon, status1muonFromTau, status1muonFromMuon, status1muonFromNeutralino, good_genStau, genStau0_index, genStau1_index, genStau2_index);
    if(file_dataset_ == "cosm" || file_dataset_ == "PGun") cosmicMC(events, good_genMuons, genMu0_index, status1muon);
    if(file_dataset_ == "tauP" || file_dataset_ == "mcha"){
      simTracks(events,simTrack0_index);
      tauPrime(events, status2H_, good_genH, genH0_index, genH1_index, genHpos_index, genHneg_index, angle);
      //eventweightTauPrime = 1.0*eventWeightTauPrime(events,genHpos_index,genHneg_index,eventweightPt);
      cout<<"eventweightTauPrime is: "<<eventweightTauPrime<<endl;
      total_count_+=eventweightTauPrime;
    }
    if(file_dataset_ == "PGun" || file_dataset_ == "mcha") genMuMatch(events, genMuMatched_DSA_index,  genMuMatched_mu_index,  genMuMatched_SA_index,  genMuMatched_SAUpdatedAtVtx_index,  genMuMatched_RSA_index,  genMuMatched_cosmic_index);
    if(file_dataset_ == "doub") doublyChargedHiggs(events, status2H_, good_genH, genH0_index, genH1_index, genHpos_index, genHneg_index, angle);
    //cout<<"finished intro MC stuff"<<endl;

    //bx cut
    if ( (doBxCut && file_dataset_ != "Zmum" && TMath::Abs(events->bxWrtCollision)>=BxCutValue_ && TMath::Abs(events->bxWrtBunch)>=BxCutValue_) || (!doBxCut) || (file_dataset_ == "Zmum") ){
      pass_bx_cut++;
      //cout<<"passed bx cut"<<endl;

      //bool doStoppedParticles = false;
      //bool doDuplicatePrintout = false;
      //if(file_dataset_ == "tauP") doStoppedParticles = true;
      //if(file_dataset_ == "mcha"){
	//if(events->mcStoppedParticle_N==2){
	//for(int j=0;j<NumGoodEntries; j++){
	//if(goodEntryNumber[j]==i) doStoppedParticles = true;
	//}
	//}
	//if(events->mcStoppedParticle_N!=2) doStoppedParticles = true;

	//for(int j=0;j<NumLines; j++){
      //if(events->id==eventNumber[j]) doDuplicatePrintout = true;
      //}
      //}
      //cout<<"just before pick stopped particles"<<endl;
      //if(doStoppedParticles) StoppedParticles(events, eventweightTauPrime, stoppedPos_index, stoppedNeg_index, n_stoppedInDetector, stoppedDetector0_index, stoppedDetector1_index);
      pickStoppedParticle(events, stopped_index);
      StoppedParticles(events, eventweightTauPrime, stoppedPos_index, stoppedNeg_index, stopped_index, n_stoppedInDetector);
      //cout<<"just after stopped particles"<<endl;

      //long-lived particle stopping in cavern walls? mcStoppedParticle variables are in mm 
      if( (!is_data && is_otherMC && doCavCut && events->mcStoppedParticle_N>0 && n_stoppedInDetector>0) || (!doCavCut) || (is_data) || (file_dataset_=="cosm") || (file_dataset_=="PGun")){
      //if( (!is_data && is_otherMC && doCavCut && events->mcStoppedParticle_N>0 && n_stoppedInDetector>1) || (!doCavCut) || (is_data) || (file_dataset_=="cosm") || (file_dataset_=="PGun")){
	//double r = events->mcStoppedParticleR[0]/10.0;
	//double z = events->mcStoppedParticleZ[0]/10.0;
	//double particle_eta = eta(events->mcStoppedParticleX[0],events->mcStoppedParticleY[0],
	//events->mcStoppedParticleZ[0],events->mcStoppedParticleTime[0]);
	
	//if (r < 131.0 && fabs(particle_eta) <= 2.5 && fabs(z) < 300.0){
	//if (r < 20.0 && fabs(particle_eta) <= 1.0 && fabs(z) < 20.0){
        pass_cavern_cut++;
	//cout<<"after cavern cut"<<endl;

	//does MC pass gen level criteria
	if(file_dataset_ == "stop") stop_counts(events, WFromTop, status1muon, status1muonFromMuon, status1muonFromW );
	if(file_dataset_ == "glui") gluino_counts(events, status1muon, status1muonFromW, status1muonFromTau, status1muonFromMuon, status1muonFromBbaryon, status1muonFromCbaryon, status1muonFromSbaryon, status1muonFromBmeson, status1muonFromCmeson, status1muonFromJPsi, status1muonFromLightMeson);
	if(file_dataset_ == "mcha") mchamp_counts(events, good_genPosMuons, good_genNegMuons, genPosMu0_index, genPosMu1_index, genNegMu0_index, genNegMu1_index );
	if(file_dataset_ == "ppst" || file_dataset_ == "gmst" ) stau_counts(events, tauFromStau, status1muon, status1muonFromTau );
	if(file_dataset_ == "cosm" || file_dataset_ == "PGun" ) cosmicMC_counts(events, status1muon);
	//cout<<"finished cosmicMC_counts"<<endl;

	if(doPrintout){
	  printout_setup(events,is_data);
	  printout_gen(events);
	}
	
	if( (!is_data && doGenMuCut && (status1muon || (file_dataset_ == "mcha" &&(events->mcMuonCharge[genPosMu0_index]==events->mcMuonCharge[genPosMu1_index] || events->mcMuonCharge[genNegMu0_index]==events->mcMuonCharge[genNegMu1_index])))) || (!doGenMuCut) || (is_data) || (is_otherMC)){
	  //cout<<"finished status1muon"<<endl;
	  //cout<<"after gen mu"<<endl;

	  //SA muon cut
	  if ((doSACut && events->mu_DisplacedStandAlone_N>0 ) || (!doSACut)){
	  //if ((doSACut && events->mu_StandAlone_N>0) || (!doSACut)){
	  //if ((doSACut && events->mu_RefittedStandAlone_N>0) || (!doSACut)){
	  //if ((doSACut && events->mu_Cosmic_N>0 ) || (!doSACut)){
	  //if ((doSACut && events->mu_DisplacedStandAlone_N==0) || (!doSACut)){
	  //if ((doSACut && events->mu_DisplacedStandAlone_N==0 && events->DTSegment_N>2) || (!doSACut)){
	    pass_standaloneMuon_cut++;
	    //cout<<"finished standalonemuon"<<endl;

	    //SA matched to gen muon?
	    if ((!is_data && doGenMuMatchedCut && genMuonMatched(events) && doSACut) || (!doGenMuMatchedCut) || (is_data) || (!doSACut)){
	      pass_genMuonMatched_cut++;
	      //cout<<"after gen mu matched"<<endl;

	      //if(doSACut){
		
	      //cout<<"right before turnon curve"<<endl;
		//do trigger turn on curve
		if(doTriggerTurnOn){		  
		  PreselectionSA(events, n_passPreselection, presel0_index, presel1_index, presel2_index, presel3_index, PreNdsaCutValue_, PrePtCutValue_, PreChaCutValue_, PreEtaCutValue_, PreRpcCutValue_, PreDtHitsCutValue_, PreInvBetaErrCutValue_, PreCscHitsCutValue_, pass_PreNdsa, pass_Prept, pass_Precha, pass_Preeta, pass_PreRPC, pass_PreDtHits, pass_PreInvBetaErr, pass_PreCscHits);		  
		  PreselectionSA_counts(pass_PreNdsa, pass_Prept, pass_Precha, pass_Preeta, pass_PreRPC, pass_PreDtHits, pass_PreInvBetaErr, pass_PreCscHits);
		  if(n_passPreselection>0) TriggerTurnOn(events, file_dataset_, presel0_index);
		  //cout<<"right after turnon curve"<<endl;
		}
		
		//don't do trigger turn on
		else {	     
		  //pass trigger
		  //if ( (doTriggerCut && file_dataset_ != "Zmum" && (events->hltL2Mu10NoVertexNoBptx3BXNoHalo ) ) || (!doTriggerCut) || (file_dataset_ == "Zmum") || (file_dataset_ == "ABCD")){
		  //if ( (doTriggerCut && file_dataset_ != "Zmum" && (events->l1SingleMu6NoBptx[2] ) ) || (!doTriggerCut) || (file_dataset_ == "Zmum")){
		  //pass_10trigger_cut++;
		  if ( (doTriggerCut && file_dataset_ != "Zmum" && (events->hltL2Mu20NoVertexNoBptx3BX || events->hltL2Mu30NoVertexNoBptx3BX || events->hltL2Mu20NoVertexNoBptx3BXNoHalo || events->hltL2Mu30NoVertexNoBptx3BXNoHalo || events->hltL2Mu20NoVertex2ChaNoBptx3BXNoHalo || events->hltL2Mu30NoVertex2ChaNoBptx3BXNoHalo ) ) || (!doTriggerCut) || (file_dataset_ == "Zmum")){
		  //if ( (doTriggerCut && file_dataset_ != "Zmum" && (events->l1SingleMu6NoBptx[2]) ) || (!doTriggerCut) || (file_dataset_ == "Zmum")){
		    pass_trigger_cut++;
		    //cout<<"finished trigger cut"<<endl;
		    //StoppingRegionAcceptance(events,eventweightTauPrime);

		    PreselectionSA(events, n_passPreselection, presel0_index, presel1_index, presel2_index, presel3_index, PreNdsaCutValue_, PrePtCutValue_, PreChaCutValue_, PreEtaCutValue_, PreRpcCutValue_, PreDtHitsCutValue_, PreInvBetaErrCutValue_, PreCscHitsCutValue_, pass_PreNdsa, pass_Prept, pass_Precha, pass_Preeta, pass_PreRPC, pass_PreDtHits, pass_PreInvBetaErr, pass_PreCscHits);
		    PreselectionSA_counts(pass_PreNdsa, pass_Prept, pass_Precha, pass_Preeta, pass_PreRPC, pass_PreDtHits, pass_PreInvBetaErr, pass_PreCscHits);

		    if(n_passPreselection>0){
		      //cout<<"preselection: "<<events->id<<endl;
		      StoppingRegionAcceptance(events,eventweightTauPrime, stopped_index);
		      HighestPtSA(events, file_dataset_, presel0_index, presel1_index, presel2_index, presel3_index, highestPt_index, PtCutValue_, ChaCutValue_, EtaCutValue_, RpcCutValue_, DisStCutValue_, DtHitsCutValue_, CscHitsCutValue_, DtInvBetaCutValue_, TimeInOutCutValue_, TimeInOutErrCutValue_, OppEtaCutValue_, OppPhiCutValue_, DxyCutValue_, pass_Upper,pass_pt,pass_cha,pass_eta,pass_RPC,pass_DisSt,pass_DtHits,pass_CscHits,pass_DtInvBeta,pass_TimeInOut,pass_TimeInOutErr,pass_TofDir,pass_Rpc_Bx,pass_OppEta,pass_OppPhi,pass_Dxy);
		      HighestPtSA_counts(pass_Upper,pass_pt,pass_cha,pass_eta,pass_RPC,pass_DisSt,pass_DtHits,pass_CscHits,pass_DtInvBeta,pass_TimeInOut,pass_TimeInOutErr,pass_TofDir,pass_Rpc_Bx,pass_OppEta,pass_OppPhi,pass_Dxy);		    
		    }
		    //cout<<"finished HighestPtSA_counts"<<endl;
		    if(n_passPreselection>1){
		      pick_UpperAndLowerSA(events, n_passPreselection, n_Upper, n_Lower, presel0_index, presel1_index, presel2_index, presel3_index, upper0_index, lower0_index, upper1_index, lower1_index, upper2_index, lower2_index);
		      if (n_Upper>0 && n_Lower>0){
			UpperAndLowerSA(events, file_dataset, upper0_index, lower0_index, upper1_index, lower1_index, upper2_index, lower2_index, upper_index, lower_index, PtCutValue_, ChaCutValue_, EtaCutValue_, RpcCutValue_,  DisStCutValue_, DtHitsCutValue_, DtInvBetaCutValue_, TimeInOutCutValue_, TimeInOutErrCutValue_, DeltaTimeInOutCutValue_, DeltaDtInvBetaCutValue_, pass_UpperAndLower, pass_pt_2, pass_cha_2, pass_eta_2, pass_RPC_2,  pass_DisSt_2, pass_DtHits_2, pass_OppEta_2, pass_OppPhi_2, pass_Rpc_Bx_2, pass_DtInvBeta_2, pass_TimeInOut_2, pass_TimeInOutErr_2, pass_DeltaTimeInOut_2, pass_DeltaDtInvBeta_2, pass_TofDir_2,pass_charge_2);
			UpperAndLowerSA_counts(pass_UpperAndLower, pass_pt_2, pass_cha_2, pass_eta_2, pass_RPC_2,  pass_DisSt_2, pass_DtHits_2, pass_OppEta_2, pass_OppPhi_2, pass_Rpc_Bx_2, pass_DtInvBeta_2, pass_TimeInOut_2, pass_TimeInOutErr_2, pass_DeltaTimeInOut_2, pass_DeltaDtInvBeta_2, pass_TofDir_2, pass_charge_2);
		      }
		    }
		    //cout<<"finished UpperAndLowerSA_counts"<<endl;
		  
		    
		    if(doPrintout){
		      //if(doDuplicatePrintout){
		      //if(n_passPreselection>0){
		      //if(events->muDisplacedStandAloneTrackDtTofFreeInverseBetaErr[presel0_index]>20){
		      //if(events->DTSegment_N>20){
		      //if(events->cscSeg_N>0){
		      //if(highestPt_index!=999 || (n_Upper>0 && n_Lower>0)){
		      //if(highestPt_index!=999){
		      //if((n_Upper>0 && n_Lower>0)){
		      //if(upper_index!=999 && lower_index!=999){
		      //if(events->muDisplacedStandAloneTrackDtTofTimeAtIpInOut[lower_index]!=-999. && events->muDisplacedStandAloneTrackDtTofTimeAtIpInOut[upper_index]!=-999.){
		      //if(events->muDisplacedStandAloneTrackDtTofTimeAtIpInOut[lower_index]<20.){
		      //if(pass_TofDir_2){
		      //if(pass_charge_2){
		      //if(!is_data) printout_gen(events);
		      //cout<<"event number is: "<<events->id<<endl;
		      
		      /*
		      bool trackerMu = false;
		      for (UInt_t j=0; j<events->mu_N; j++) {	    
			if(events->muIsTrackerMuon[j]){
			  trackerMu = true;
			  break;
			}
		      }
		      */
		      /*
		      if(n_passPreselection>0){
			if(highestPt_index!=999){
			  //if(highestPt_index!=999 || (n_Upper>0 && n_Lower>0)){
			  //if((n_Upper>0 && n_Lower>0)){
			  //if(upper_index!=999 && lower_index!=999){
			  //if(trackerMu){
			  if(events->cscSeg_N>2){
			    cout<<"highest pt index is: "<<highestPt_index<<endl;
			    printout_setup(events,is_data);
			    printout_gen(events);
			    printout_DSA(events);
			    printout_SA(events);
			    printout_RSA(events);
			    printout_cosmic(events);
			    //printout_tuneP_global(events);
			    printout_L2(events);
			    printout_L1(events);
			    
			    nPrintedOutEvents++;
			  }
			}
		      }
		      //}
		      */
		    }

		    //cout<<"finished printouts"<<endl;
		    //cout<<"starting histos"<<endl;

		    id_hist->Fill(events->id,1.0);
		    run_hist->Fill(events->run,1.0);
		    bx_hist->Fill(events->bx,1.0);
		    bxWrtCollision_hist->Fill(events->bxWrtCollision,1.0);
		    bxWrtBunch_hist->Fill(events->bxWrtBunch,1.0);

		    if(events->l1Muon_N>0){
		      l1MuonPt_hist->Fill(events->l1MuonPt[0],1.0);
		      l1MuonEta_hist->Fill(events->l1MuonEta[0],1.0);
		      l1MuonPhi_hist->Fill(events->l1MuonPhi[0],1.0);
		    }
		    
		    if(events->hlt20Cha2Muon_N>0){
		      hlt20Cha2MuonPt_hist->Fill(events->hlt20Cha2MuonPt[0],1.0);
		      hlt20Cha2MuonEta_hist->Fill(events->hlt20Cha2MuonEta[0],1.0);
		      hlt20Cha2MuonPhi_hist->Fill(events->hlt20Cha2MuonPhi[0],1.0);
		    }
		    //cout<<"trigger hists done"<<endl;
		    
		    if(events->mu_Cosmic_N>0){
		      //muCosmicPt_hist->Fill(events->muCosmicPt[0],1.0);
		      muCosmicEta_hist->Fill(events->muCosmicEta[0],1.0);
		      muCosmicPhi_hist->Fill(events->muCosmicPhi[0],1.0);
		    }
		    if(events->mu_CosmicTrack_N>0){
		      muCosmicTrackNChambersDt_hist->Fill(events->muCosmicTrackNDtChambersWithValidHits[0],1.0);
		    }

		    mu_N_hist->Fill(events->mu_N,1.0);
		    if (events->mu_N>0) {
		      //cout<<"mu number "<<j<<endl;
		      //muPt_hist->Fill(events->muPt[0],1.0);
		      muEta_hist->Fill(events->muEta[0],1.0);
		      muPhi_hist->Fill(events->muPhi[0],1.0);
		      muType_hist->Fill(events->muType[0],1.0);
		      muIso_hist->Fill(events->muIso[0],1.0);
		      muEta_muPhi_hist->Fill(events->muEta[0],events->muPhi[0],1.0);
		    }	      

		    //DTSegment_N_hist->Fill(events->DTSegment_N,1.0); //moved to after preselection
		    //CSCSegment_N_hist->Fill(events->cscSeg_N,1.0); //moved to after preselection
		    
		    //cout<<"number of dimuon candidates is: "<<events->diMuMass.size()<<endl;
		    diMu_N_hist->Fill(events->diMuMass.size(),1.0);
		    if(events->diMuMass.size()>0) diMuMass_hist->Fill(events->diMuMass[0],1.0);

		    runNumber_muDisplacedStandAloneN_hist->Fill(events->run,n_passPreselection,1.0);

		    if(!is_data){
		      if(file_dataset_!="cosm" && file_dataset_!="PGun"){
			if(doCavCut){
			  mcStoppedParticle_N_hist->Fill(n_stoppedInDetector,eventweightTauPrime);

			  if(n_stoppedInDetector>0){
			    mcStoppedParticleX_StoppedParticleN_hist->Fill(events->mcStoppedParticleX[stoppedDetector0_index]/10.0,n_stoppedInDetector,eventweightTauPrime);
			    mcStoppedParticleY_StoppedParticleN_hist->Fill(events->mcStoppedParticleY[stoppedDetector0_index]/10.0,n_stoppedInDetector,eventweightTauPrime);
			    mcStoppedParticleZ_StoppedParticleN_hist->Fill(events->mcStoppedParticleZ[stoppedDetector0_index]/10.0,n_stoppedInDetector,eventweightTauPrime);
			    mcStoppedParticleId_StoppedParticleN_hist->Fill(events->mcStoppedParticleId[stoppedDetector0_index],n_stoppedInDetector,eventweightTauPrime);
			    mcStoppedParticleCharge_StoppedParticleN_hist->Fill(events->mcStoppedParticleCharge[stoppedDetector0_index],n_stoppedInDetector,eventweightTauPrime);
			    mcStoppedParticleTime_mcStoppedParticleCharge_hist->Fill(events->mcStoppedParticleTime[stoppedDetector0_index],events->mcStoppedParticleCharge[stoppedDetector0_index],eventweightTauPrime);

			    mcStoppedParticleX_hist->Fill(events->mcStoppedParticleX[stoppedDetector0_index]/10.0,eventweightTauPrime);
			    mcStoppedParticleY_hist->Fill(events->mcStoppedParticleY[stoppedDetector0_index]/10.0,eventweightTauPrime);
			    mcStoppedParticleZ_hist->Fill(events->mcStoppedParticleZ[stoppedDetector0_index]/10.0,eventweightTauPrime);
			    mcStoppedParticleR_hist->Fill(events->mcStoppedParticleR[stoppedDetector0_index]/10.0,eventweightTauPrime);
			    double particle_eta = eta(events->mcStoppedParticleX[stoppedDetector0_index],events->mcStoppedParticleY[stoppedDetector0_index],
							events->mcStoppedParticleZ[stoppedDetector0_index],events->mcStoppedParticleTime[stoppedDetector0_index]);			
			    mcStoppedParticleEta_hist->Fill(particle_eta,eventweightTauPrime);
			    mcStoppedParticlePhi_hist->Fill(events->mcStoppedParticlePhi[stoppedDetector0_index],eventweightTauPrime);
			    mcStoppedParticleTime_hist->Fill(events->mcStoppedParticleTime[stoppedDetector0_index],eventweightTauPrime);
			    mcStoppedParticleXY_hist->Fill(events->mcStoppedParticleX[stoppedDetector0_index]/10.0,events->mcStoppedParticleY[stoppedDetector0_index]/10.0,eventweightTauPrime);
			    mcStoppedParticleMass_hist->Fill(events->mcStoppedParticleMass[stoppedDetector0_index],eventweightTauPrime);
			    mcStoppedParticleId_hist->Fill(events->mcStoppedParticleId[stoppedDetector0_index],eventweightTauPrime);
			    mcStoppedParticleCharge_hist->Fill(events->mcStoppedParticleCharge[stoppedDetector0_index],eventweightTauPrime);
			    
			    if(events->mcStoppedParticleCharge[stoppedDetector0_index]>0){
			      mcStoppedParticleXPos_hist->Fill(events->mcStoppedParticleX[stoppedDetector0_index]/10.0,eventweightTauPrime);
			      mcStoppedParticleYPos_hist->Fill(events->mcStoppedParticleY[stoppedDetector0_index]/10.0,eventweightTauPrime);
			      mcStoppedParticleZPos_hist->Fill(events->mcStoppedParticleZ[stoppedDetector0_index]/10.0,eventweightTauPrime);
			      mcStoppedParticleRPos_hist->Fill(events->mcStoppedParticleR[stoppedDetector0_index]/10.0,eventweightTauPrime);
			    }
			    if(events->mcStoppedParticleCharge[stoppedDetector0_index]<0){
			      mcStoppedParticleXNeg_hist->Fill(events->mcStoppedParticleX[stoppedDetector0_index]/10.0,eventweightTauPrime);
			      mcStoppedParticleYNeg_hist->Fill(events->mcStoppedParticleY[stoppedDetector0_index]/10.0,eventweightTauPrime);
			      mcStoppedParticleZNeg_hist->Fill(events->mcStoppedParticleZ[stoppedDetector0_index]/10.0,eventweightTauPrime);
			      mcStoppedParticleRNeg_hist->Fill(events->mcStoppedParticleR[stoppedDetector0_index]/10.0,eventweightTauPrime);
			    }

			    if(n_stoppedInDetector==2){
			      mcStoppedParticleX_StoppedParticleN_hist->Fill(events->mcStoppedParticleX[stoppedDetector1_index]/10.0,n_stoppedInDetector,eventweightTauPrime);
			      mcStoppedParticleY_StoppedParticleN_hist->Fill(events->mcStoppedParticleY[stoppedDetector1_index]/10.0,n_stoppedInDetector,eventweightTauPrime);
			      mcStoppedParticleZ_StoppedParticleN_hist->Fill(events->mcStoppedParticleZ[stoppedDetector1_index]/10.0,n_stoppedInDetector,eventweightTauPrime);
			      mcStoppedParticleId_StoppedParticleN_hist->Fill(events->mcStoppedParticleId[stoppedDetector1_index],n_stoppedInDetector,eventweightTauPrime);
			      mcStoppedParticleCharge_StoppedParticleN_hist->Fill(events->mcStoppedParticleCharge[stoppedDetector1_index],n_stoppedInDetector,eventweightTauPrime);
			      mcStoppedParticleTime_mcStoppedParticleCharge_hist->Fill(events->mcStoppedParticleTime[stoppedDetector1_index],events->mcStoppedParticleCharge[stoppedDetector1_index],eventweightTauPrime);

			      mcStoppedParticleX_hist->Fill(events->mcStoppedParticleX[stoppedDetector1_index]/10.0,eventweightTauPrime);
			      mcStoppedParticleY_hist->Fill(events->mcStoppedParticleY[stoppedDetector1_index]/10.0,eventweightTauPrime);
			      mcStoppedParticleZ_hist->Fill(events->mcStoppedParticleZ[stoppedDetector1_index]/10.0,eventweightTauPrime);
			      mcStoppedParticleR_hist->Fill(events->mcStoppedParticleR[stoppedDetector1_index]/10.0,eventweightTauPrime);
			      double particle_eta = eta(events->mcStoppedParticleX[stoppedDetector1_index],events->mcStoppedParticleY[stoppedDetector1_index],
						      events->mcStoppedParticleZ[stoppedDetector1_index],events->mcStoppedParticleTime[stoppedDetector1_index]);			
			      mcStoppedParticleEta_hist->Fill(particle_eta,eventweightTauPrime);
			      mcStoppedParticlePhi_hist->Fill(events->mcStoppedParticlePhi[stoppedDetector1_index],eventweightTauPrime);
			      mcStoppedParticleTime_hist->Fill(events->mcStoppedParticleTime[stoppedDetector1_index],eventweightTauPrime);
			      mcStoppedParticleXY_hist->Fill(events->mcStoppedParticleX[stoppedDetector1_index]/10.0,events->mcStoppedParticleY[stoppedDetector1_index]/10.0,eventweightTauPrime);
			      mcStoppedParticleMass_hist->Fill(events->mcStoppedParticleMass[stoppedDetector1_index],eventweightTauPrime);
			      mcStoppedParticleId_hist->Fill(events->mcStoppedParticleId[stoppedDetector1_index],eventweightTauPrime);
			      mcStoppedParticleCharge_hist->Fill(events->mcStoppedParticleCharge[stoppedDetector1_index],eventweightTauPrime);
			      
			      mcStoppedParticleXPos2Stopped_hist->Fill(events->mcStoppedParticleX[stoppedPos_index]/10.0,eventweightTauPrime);
			      mcStoppedParticleYPos2Stopped_hist->Fill(events->mcStoppedParticleY[stoppedPos_index]/10.0,eventweightTauPrime);
			      mcStoppedParticleZPos2Stopped_hist->Fill(events->mcStoppedParticleZ[stoppedPos_index]/10.0,eventweightTauPrime);
			      mcStoppedParticleRPos2Stopped_hist->Fill(events->mcStoppedParticleR[stoppedPos_index]/10.0,eventweightTauPrime);
			      mcStoppedParticleXNeg2Stopped_hist->Fill(events->mcStoppedParticleX[stoppedNeg_index]/10.0,eventweightTauPrime);
			      mcStoppedParticleYNeg2Stopped_hist->Fill(events->mcStoppedParticleY[stoppedNeg_index]/10.0,eventweightTauPrime);
			      mcStoppedParticleZNeg2Stopped_hist->Fill(events->mcStoppedParticleZ[stoppedNeg_index]/10.0,eventweightTauPrime);
			      mcStoppedParticleRNeg2Stopped_hist->Fill(events->mcStoppedParticleR[stoppedNeg_index]/10.0,eventweightTauPrime);

			      mcStoppedParticle0Charge_hist->Fill(events->mcStoppedParticleCharge[stoppedDetector0_index],eventweightTauPrime);
			      mcStoppedParticle1Charge_hist->Fill(events->mcStoppedParticleCharge[stoppedDetector1_index],eventweightTauPrime);
			      mcStoppedParticle0Time_hist->Fill(events->mcStoppedParticleTime[stoppedDetector0_index],eventweightTauPrime);
			      mcStoppedParticle1Time_hist->Fill(events->mcStoppedParticleTime[stoppedDetector1_index],eventweightTauPrime);

			      double deltaTime = TMath::Abs(events->mcStoppedParticleTime[stoppedDetector0_index]-events->mcStoppedParticleTime[stoppedDetector1_index]);
			      mcStoppedParticleDeltaTime_hist->Fill(deltaTime,eventweightTauPrime);
			    } //end of if exactly 2 stopped in the detector
			  }//end of if at least 1 stopped in the detector
			}//end of if doCavCut
			else{
			  //cout<<"starting stopped particle histos"<<endl;
			  mcStoppedParticle_N_hist->Fill(events->mcStoppedParticle_N,eventweightTauPrime);
			  //cout<<"plotted Stopped Particle N"<<endl;
			  if(stopped_index!=999){
			    //cout<<"stopped particle index is not 999"<<endl;
			    mcStoppedParticleX_hist->Fill(events->mcStoppedParticleX[stopped_index]/10.0,eventweightTauPrime);
			    mcStoppedParticleY_hist->Fill(events->mcStoppedParticleY[stopped_index]/10.0,eventweightTauPrime);
			    mcStoppedParticleZ_hist->Fill(events->mcStoppedParticleZ[stopped_index]/10.0,eventweightTauPrime);
			    mcStoppedParticleR_hist->Fill(events->mcStoppedParticleR[stopped_index]/10.0,eventweightTauPrime);
			    double particle_eta = eta(events->mcStoppedParticleX[stopped_index],events->mcStoppedParticleY[stopped_index],
						      events->mcStoppedParticleZ[stopped_index],events->mcStoppedParticleTime[stopped_index]);			
			    mcStoppedParticleEta_hist->Fill(particle_eta,eventweightTauPrime);
			    mcStoppedParticlePhi_hist->Fill(events->mcStoppedParticlePhi[stopped_index],eventweightTauPrime);
			    mcStoppedParticleTime_hist->Fill(events->mcStoppedParticleTime[stopped_index],eventweightTauPrime);
			    mcStoppedParticleXY_hist->Fill(events->mcStoppedParticleX[stopped_index]/10.0,events->mcStoppedParticleY[stopped_index]/10.0,eventweightTauPrime);
			    mcStoppedParticleMass_hist->Fill(events->mcStoppedParticleMass[stopped_index],eventweightTauPrime);
			    mcStoppedParticleId_hist->Fill(events->mcStoppedParticleId[stopped_index],eventweightTauPrime);
			    mcStoppedParticleCharge_hist->Fill(events->mcStoppedParticleCharge[stopped_index],eventweightTauPrime);

			    mcStoppedParticleX_StoppedParticleN_hist->Fill(events->mcStoppedParticleX[stopped_index]/10.0,events->mcStoppedParticle_N,eventweightTauPrime);
			    mcStoppedParticleY_StoppedParticleN_hist->Fill(events->mcStoppedParticleY[stopped_index]/10.0,events->mcStoppedParticle_N,eventweightTauPrime);
			    mcStoppedParticleZ_StoppedParticleN_hist->Fill(events->mcStoppedParticleZ[stopped_index]/10.0,events->mcStoppedParticle_N,eventweightTauPrime);
			    mcStoppedParticleId_StoppedParticleN_hist->Fill(events->mcStoppedParticleId[stopped_index],events->mcStoppedParticle_N,eventweightTauPrime);
			    mcStoppedParticleCharge_StoppedParticleN_hist->Fill(events->mcStoppedParticleCharge[stopped_index],events->mcStoppedParticle_N,eventweightTauPrime);
			    mcStoppedParticleTime_mcStoppedParticleCharge_hist->Fill(events->mcStoppedParticleTime[stopped_index],events->mcStoppedParticleCharge[stopped_index],eventweightTauPrime);
			    //cout<<"finished first bunch of stopped particle histos"<<endl;

			    /*
			    if(events->mcStoppedParticleCharge[stopped_index]>0){
			      cout<<"stopped particle charge >0"<<endl;
			      mcStoppedParticleXPos_hist->Fill(events->mcStoppedParticleX[stopped_index]/10.0,eventweightTauPrime);
			      mcStoppedParticleYPos_hist->Fill(events->mcStoppedParticleY[stopped_index]/10.0,eventweightTauPrime);
			      mcStoppedParticleZPos_hist->Fill(events->mcStoppedParticleZ[stopped_index]/10.0,eventweightTauPrime);
			      mcStoppedParticleRPos_hist->Fill(events->mcStoppedParticleR[stopped_index]/10.0,eventweightTauPrime);
			    }
			    else{
			      cout<<"stopped particle charge <0"<<endl;
			      mcStoppedParticleXNeg_hist->Fill(events->mcStoppedParticleX[stopped_index]/10.0,eventweightTauPrime);
			      mcStoppedParticleYNeg_hist->Fill(events->mcStoppedParticleY[stopped_index]/10.0,eventweightTauPrime);
			      mcStoppedParticleZNeg_hist->Fill(events->mcStoppedParticleZ[stopped_index]/10.0,eventweightTauPrime);
			      mcStoppedParticleRNeg_hist->Fill(events->mcStoppedParticleR[stopped_index]/10.0,eventweightTauPrime);
			    }
			    */
			  }//end of stopped particle index not 999

			  if(events->mcStoppedParticle_N==2){
			    //cout<<"2 stopped particles"<<endl;
			    //mcStoppedParticle0Charge_hist->Fill(events->mcStoppedParticleCharge[0],eventweightTauPrime);
			    //mcStoppedParticle1Charge_hist->Fill(events->mcStoppedParticleCharge[1],eventweightTauPrime);
			    mcStoppedParticle0Time_hist->Fill(events->mcStoppedParticleTime[0],eventweightTauPrime);
			    mcStoppedParticle1Time_hist->Fill(events->mcStoppedParticleTime[1],eventweightTauPrime);

			    double deltaTime = TMath::Abs(events->mcStoppedParticleTime[stoppedDetector0_index]-events->mcStoppedParticleTime[stoppedDetector1_index]);
			    mcStoppedParticleDeltaTime_hist->Fill(deltaTime,eventweightTauPrime);
			  }
			}//end if !doCavernCut
			//UInt_t stoppedPos_index = 999;
			//UInt_t stoppedNeg_index = 999;
		      }//end of if not cosmics

		      //cout<<"end of stopped particle histos"<<endl;

		      if(file_dataset_ == "stop" || file_dataset_ == "glui"){
			//cout<<"file dataset is stop or gluino"<<endl;
			mcRhadron_N_hist->Fill(nRhadron,1.0);

			mcRhadronPt_hist->Fill(rhadronPt1,1.0);    
			mcRhadronEta_hist->Fill(rhadronEta1,1.0);    
			mcRhadronPhi_hist->Fill(rhadronPhi1,1.0);    
			mcRhadronCharge_hist->Fill(rhadronCharge1,1.0);    

			mcRhadronPt_hist->Fill(rhadronPt2,1.0);    
			mcRhadronEta_hist->Fill(rhadronEta2,1.0);    
			mcRhadronPhi_hist->Fill(rhadronPhi2,1.0);    
			mcRhadronCharge_hist->Fill(rhadronCharge2,1.0);    

			if(file_dataset_ == "stop"){
			  //cout<<"starting to plot stop histos"<<endl;
			  mcStop_N_hist->Fill(good_genStop,1.0);
			  if(good_genStop>0){
			    
			    double beta0 = -999.;
			    if(events->mcStopP[genStop0_index]!=0.) beta0 = 1.0/(TMath::Sqrt((events->mcStopMass[genStop0_index]/events->mcStopP[genStop0_index])*(events->mcStopMass[genStop0_index]/events->mcStopP[genStop0_index])+1));
			    
			    mcStop0Charge_hist->Fill(events->mcStopCharge[genStop0_index],1.0);			  
			    mcStopP_hist->Fill(events->mcStopP[genStop0_index],1.0);
			    mcStopPx_hist->Fill(events->mcStopPx[genStop0_index],1.0);
			    mcStopPy_hist->Fill(events->mcStopPy[genStop0_index],1.0);
			    mcStopPz_hist->Fill(events->mcStopPz[genStop0_index],1.0);
			    mcStopPt_hist->Fill(events->mcStopPt[genStop0_index],1.0);
			    mcStopEta_hist->Fill(events->mcStopEta[genStop0_index],1.0);
			    mcStopPhi_hist->Fill(events->mcStopPhi[genStop0_index],1.0);			    
			    mcStopBeta_hist->Fill(beta0,1.0);
			    
			    if(stopStoppedParticleMatched(events, genStop0_index)){
			      stopped_mcStopP_hist->Fill(events->mcStopP[genStop0_index],1.0);
			      stopped_mcStopPt_hist->Fill(events->mcStopPt[genStop0_index],1.0);
			      stopped_mcStopEta_hist->Fill(events->mcStopEta[genStop0_index],1.0);
			      stopped_mcStopPhi_hist->Fill(events->mcStopPhi[genStop0_index],1.0);
			      stopped_mcStopBeta_hist->Fill(beta0,1.0);
			    }
			    else{
			      notStopped_mcStopP_hist->Fill(events->mcStopP[genStop0_index],1.0);
			      notStopped_mcStopPt_hist->Fill(events->mcStopPt[genStop0_index],1.0);
			      notStopped_mcStopEta_hist->Fill(events->mcStopEta[genStop0_index],1.0);
			      notStopped_mcStopPhi_hist->Fill(events->mcStopPhi[genStop0_index],1.0);
			      notStopped_mcStopBeta_hist->Fill(beta0,1.0);
			    }
			    
			    if(good_genStop>1){
			      double beta1 = -999.;
			      if(events->mcStopP[genStop1_index]!=0.) beta1 = 1.0/(TMath::Sqrt((events->mcStopMass[genStop1_index]/events->mcStopP[genStop1_index])*(events->mcStopMass[genStop1_index]/events->mcStopP[genStop1_index])+1));
			      
			      mcStop1Charge_hist->Fill(events->mcStopCharge[genStop1_index],1.0);
			      mcStopP_hist->Fill(events->mcStopP[genStop1_index],1.0);
			      mcStopPx_hist->Fill(events->mcStopPx[genStop1_index],1.0);
			      mcStopPy_hist->Fill(events->mcStopPy[genStop1_index],1.0);
			      mcStopPz_hist->Fill(events->mcStopPz[genStop1_index],1.0);
			      mcStopPt_hist->Fill(events->mcStopPt[genStop1_index],1.0);
			      mcStopEta_hist->Fill(events->mcStopEta[genStop1_index],1.0);
			      mcStopPhi_hist->Fill(events->mcStopPhi[genStop1_index],1.0);
			      mcStopBeta_hist->Fill(beta1,1.0);
			      
			      if(stopStoppedParticleMatched(events, genStop1_index)){
				stopped_mcStopP_hist->Fill(events->mcStopP[genStop1_index],1.0);
				stopped_mcStopPt_hist->Fill(events->mcStopPt[genStop1_index],1.0);
				stopped_mcStopEta_hist->Fill(events->mcStopEta[genStop1_index],1.0);
				stopped_mcStopPhi_hist->Fill(events->mcStopPhi[genStop1_index],1.0);
				stopped_mcStopBeta_hist->Fill(beta1,1.0);
			      }
			      else{
				notStopped_mcStopP_hist->Fill(events->mcStopP[genStop1_index],1.0);
				notStopped_mcStopPt_hist->Fill(events->mcStopPt[genStop1_index],1.0);
				notStopped_mcStopEta_hist->Fill(events->mcStopEta[genStop1_index],1.0);
				notStopped_mcStopPhi_hist->Fill(events->mcStopPhi[genStop1_index],1.0);
				notStopped_mcStopBeta_hist->Fill(beta1,1.0);
			      }//end of if stop not matched to a stopped particle
			      
			    }//end of if 2 or more good stops
			  }//end of if 1 or more good stops
			}//end of if file is stop
			
			if(file_dataset_ == "glui"){
			  cout<<"starting to plot gluino histos"<<endl;
			  mcGluino_N_hist->Fill(good_genGluino,1.0);
			  if(good_genGluino>0){
			    //cout<<"at least 1 good gluino"<<endl;
			    double beta0 = -999.;
			    if(events->mcGluinoP[genGluino0_index]!=0.) beta0 = 1.0/(TMath::Sqrt((events->mcGluinoMass[genGluino0_index]/events->mcGluinoP[genGluino0_index])*(events->mcGluinoMass[genGluino0_index]/events->mcGluinoP[genGluino0_index])+1));
			    
			    mcGluino0Charge_hist->Fill(events->mcGluinoCharge[genGluino0_index],1.0);			  
			    mcGluinoP_hist->Fill(events->mcGluinoP[genGluino0_index],1.0);
			    mcGluinoPx_hist->Fill(events->mcGluinoPx[genGluino0_index],1.0);
			    mcGluinoPy_hist->Fill(events->mcGluinoPy[genGluino0_index],1.0);
			    mcGluinoPz_hist->Fill(events->mcGluinoPz[genGluino0_index],1.0);
			    mcGluinoPt_hist->Fill(events->mcGluinoPt[genGluino0_index],1.0);
			    mcGluinoEta_hist->Fill(events->mcGluinoEta[genGluino0_index],1.0);
			    mcGluinoPhi_hist->Fill(events->mcGluinoPhi[genGluino0_index],1.0);			    
			    mcGluinoBeta_hist->Fill(beta0,1.0);
			    
			    if(gluinoStoppedParticleMatched(events, genGluino0_index)){
			      cout<<"matched!!! stopped gluino eta is: "<<events->mcGluinoEta[genGluino0_index]<<", phi is: "<<events->mcGluinoPhi[genGluino0_index]<<endl;
			      stopped_mcGluinoP_hist->Fill(events->mcGluinoP[genGluino0_index],1.0);
			      stopped_mcGluinoPt_hist->Fill(events->mcGluinoPt[genGluino0_index],1.0);
			      stopped_mcGluinoEta_hist->Fill(events->mcGluinoEta[genGluino0_index],1.0);
			      stopped_mcGluinoPhi_hist->Fill(events->mcGluinoPhi[genGluino0_index],1.0);
			      stopped_mcGluinoBeta_hist->Fill(beta0,1.0);
			    }
			    else{
			      cout<<"not matched: gluino eta is: "<<events->mcGluinoEta[genGluino0_index]<<", phi is: "<<events->mcGluinoPhi[genGluino0_index]<<endl;
			      notStopped_mcGluinoP_hist->Fill(events->mcGluinoP[genGluino0_index],1.0);
			      notStopped_mcGluinoPt_hist->Fill(events->mcGluinoPt[genGluino0_index],1.0);
			      notStopped_mcGluinoEta_hist->Fill(events->mcGluinoEta[genGluino0_index],1.0);
			      notStopped_mcGluinoPhi_hist->Fill(events->mcGluinoPhi[genGluino0_index],1.0);
			      notStopped_mcGluinoBeta_hist->Fill(beta0,1.0);
			    }
			    
			    if(good_genGluino>1){
			      //cout<<"at least 2 good gluino"<<endl;
			      double beta1 = -999.;
			      if(events->mcGluinoP[genGluino1_index]!=0.) beta1 = 1.0/(TMath::Sqrt((events->mcGluinoMass[genGluino1_index]/events->mcGluinoP[genGluino1_index])*(events->mcGluinoMass[genGluino1_index]/events->mcGluinoP[genGluino1_index])+1));
			      
			      mcGluino1Charge_hist->Fill(events->mcGluinoCharge[genGluino1_index],1.0);
			      mcGluinoP_hist->Fill(events->mcGluinoP[genGluino1_index],1.0);
			      mcGluinoPx_hist->Fill(events->mcGluinoPx[genGluino1_index],1.0);
			      mcGluinoPy_hist->Fill(events->mcGluinoPy[genGluino1_index],1.0);
			      mcGluinoPz_hist->Fill(events->mcGluinoPz[genGluino1_index],1.0);
			      mcGluinoPt_hist->Fill(events->mcGluinoPt[genGluino1_index],1.0);
			      mcGluinoEta_hist->Fill(events->mcGluinoEta[genGluino1_index],1.0);
			      mcGluinoPhi_hist->Fill(events->mcGluinoPhi[genGluino1_index],1.0);
			      mcGluinoBeta_hist->Fill(beta1,1.0);
			      
			      if(gluinoStoppedParticleMatched(events, genGluino1_index)){
				cout<<"matched!!! stopped gluino eta is: "<<events->mcGluinoEta[genGluino1_index]<<", phi is: "<<events->mcGluinoPhi[genGluino1_index]<<endl;
				stopped_mcGluinoP_hist->Fill(events->mcGluinoP[genGluino1_index],1.0);
				stopped_mcGluinoPt_hist->Fill(events->mcGluinoPt[genGluino1_index],1.0);
				stopped_mcGluinoEta_hist->Fill(events->mcGluinoEta[genGluino1_index],1.0);
				stopped_mcGluinoPhi_hist->Fill(events->mcGluinoPhi[genGluino1_index],1.0);
				stopped_mcGluinoBeta_hist->Fill(beta1,1.0);
			      }
			      else{
				cout<<"not matched: gluino eta is: "<<events->mcGluinoEta[genGluino1_index]<<", phi is: "<<events->mcGluinoPhi[genGluino1_index]<<endl;
				notStopped_mcGluinoP_hist->Fill(events->mcGluinoP[genGluino1_index],1.0);
				notStopped_mcGluinoPt_hist->Fill(events->mcGluinoPt[genGluino1_index],1.0);
				notStopped_mcGluinoEta_hist->Fill(events->mcGluinoEta[genGluino1_index],1.0);
				notStopped_mcGluinoPhi_hist->Fill(events->mcGluinoPhi[genGluino1_index],1.0);
				notStopped_mcGluinoBeta_hist->Fill(beta1,1.0);
			      }//end of if gluino not matched to a stopped particle
			      
			    }//end of if 2 or more good gluinos
			  }//end of if 1 or more good gluinos
			}//end of if file is gluino
			
		      }//end of if file is stop or gluino
		      if(file_dataset_ == "ppst" || file_dataset_ == "gmst"){
			//cout<<"starting to plot stau histos"<<endl;
			mcStau_N_hist->Fill(good_genStau,1.0);
			if(good_genStau>0){
			  
			  double beta0 = -999.;
			  if(events->mcStauP[genStau0_index]!=0.) beta0 = 1.0/(TMath::Sqrt((events->mcStauMass[genStau0_index]/events->mcStauP[genStau0_index])*(events->mcStauMass[genStau0_index]/events->mcStauP[genStau0_index])+1));
			  
			  mcStau0Charge_hist->Fill(events->mcStauCharge[genStau0_index],1.0);			  
			  mcStauP_hist->Fill(events->mcStauP[genStau0_index],1.0);
			  mcStauPx_hist->Fill(events->mcStauPx[genStau0_index],1.0);
			  mcStauPy_hist->Fill(events->mcStauPy[genStau0_index],1.0);
			  mcStauPz_hist->Fill(events->mcStauPz[genStau0_index],1.0);
			  mcStauPt_hist->Fill(events->mcStauPt[genStau0_index],1.0);
			  mcStauEta_hist->Fill(events->mcStauEta[genStau0_index],1.0);
			  mcStauPhi_hist->Fill(events->mcStauPhi[genStau0_index],1.0);			    
			  mcStauBeta_hist->Fill(beta0,1.0);

			  if(stauStoppedParticleMatched(events, genStau0_index)){
			    stopped_mcStauP_hist->Fill(events->mcStauP[genStau0_index],1.0);
			    stopped_mcStauPt_hist->Fill(events->mcStauPt[genStau0_index],1.0);
			    stopped_mcStauEta_hist->Fill(events->mcStauEta[genStau0_index],1.0);
			    stopped_mcStauPhi_hist->Fill(events->mcStauPhi[genStau0_index],1.0);
			    stopped_mcStauBeta_hist->Fill(beta0,1.0);
			  }
			  else{
			    notStopped_mcStauP_hist->Fill(events->mcStauP[genStau0_index],1.0);
			    notStopped_mcStauPt_hist->Fill(events->mcStauPt[genStau0_index],1.0);
			    notStopped_mcStauEta_hist->Fill(events->mcStauEta[genStau0_index],1.0);
			    notStopped_mcStauPhi_hist->Fill(events->mcStauPhi[genStau0_index],1.0);
			    notStopped_mcStauBeta_hist->Fill(beta0,1.0);
			  }

			  if(good_genStau>1){
			    double beta1 = -999.;
			    if(events->mcStauP[genStau1_index]!=0.) beta1 = 1.0/(TMath::Sqrt((events->mcStauMass[genStau1_index]/events->mcStauP[genStau1_index])*(events->mcStauMass[genStau1_index]/events->mcStauP[genStau1_index])+1));

			    mcStau1Charge_hist->Fill(events->mcStauCharge[genStau1_index],1.0);
			    mcStauP_hist->Fill(events->mcStauP[genStau1_index],1.0);
			    mcStauPx_hist->Fill(events->mcStauPx[genStau1_index],1.0);
			    mcStauPy_hist->Fill(events->mcStauPy[genStau1_index],1.0);
			    mcStauPz_hist->Fill(events->mcStauPz[genStau1_index],1.0);
			    mcStauPt_hist->Fill(events->mcStauPt[genStau1_index],1.0);
			    mcStauEta_hist->Fill(events->mcStauEta[genStau1_index],1.0);
			    mcStauPhi_hist->Fill(events->mcStauPhi[genStau1_index],1.0);
			    mcStauBeta_hist->Fill(beta1,1.0);

			    if(stauStoppedParticleMatched(events, genStau1_index)){
			      stopped_mcStauP_hist->Fill(events->mcStauP[genStau1_index],1.0);
			      stopped_mcStauPt_hist->Fill(events->mcStauPt[genStau1_index],1.0);
			      stopped_mcStauEta_hist->Fill(events->mcStauEta[genStau1_index],1.0);
			      stopped_mcStauPhi_hist->Fill(events->mcStauPhi[genStau1_index],1.0);
			      stopped_mcStauBeta_hist->Fill(beta1,1.0);
			    }
			    else{
			      notStopped_mcStauP_hist->Fill(events->mcStauP[genStau1_index],1.0);
			      notStopped_mcStauPt_hist->Fill(events->mcStauPt[genStau1_index],1.0);
			      notStopped_mcStauEta_hist->Fill(events->mcStauEta[genStau1_index],1.0);
			      notStopped_mcStauPhi_hist->Fill(events->mcStauPhi[genStau1_index],1.0);
			      notStopped_mcStauBeta_hist->Fill(beta1,1.0);
			    }//end of if stau not matched to a stopped particle

			  }//end of if 2 or more good staus
			}//end of if 1 or more good staus
		      }//end of if file is gmstau or ppstau
		      if(is_otherMC && file_dataset != "cosm"){
			if(good_genH==2){
			  //cout<<"2 good gen HPlusPlus"<<endl;
			  if(file_dataset_ == "doub"){

			    mcH0Charge_hist->Fill(events->mcDoublyChargedHiggsCharge[genH0_index],1.0);
			    mcH1Charge_hist->Fill(events->mcDoublyChargedHiggsCharge[genH1_index],1.0);

			    mcHPlusPlusP_hist->Fill(events->mcDoublyChargedHiggsP[genHpos_index],1.0);
			    mcHPlusPlusPx_hist->Fill(events->mcDoublyChargedHiggsPx[genHpos_index],1.0);
			    mcHPlusPlusPy_hist->Fill(events->mcDoublyChargedHiggsPy[genHpos_index],1.0);
			    mcHPlusPlusPz_hist->Fill(events->mcDoublyChargedHiggsPz[genHpos_index],1.0);
			    mcHPlusPlusPt_hist->Fill(events->mcDoublyChargedHiggsPt[genHpos_index],1.0);
			    mcHPlusPlusEta_hist->Fill(events->mcDoublyChargedHiggsEta[genHpos_index],1.0);
			    mcHPlusPlusPhi_hist->Fill(events->mcDoublyChargedHiggsPhi[genHpos_index],1.0);
			    mcHMinusMinusP_hist->Fill(events->mcDoublyChargedHiggsP[genHneg_index],1.0);
			    mcHMinusMinusPx_hist->Fill(events->mcDoublyChargedHiggsPx[genHneg_index],1.0);
			    mcHMinusMinusPy_hist->Fill(events->mcDoublyChargedHiggsPy[genHneg_index],1.0);
			    mcHMinusMinusPz_hist->Fill(events->mcDoublyChargedHiggsPz[genHneg_index],1.0);
			    mcHMinusMinusPt_hist->Fill(events->mcDoublyChargedHiggsPt[genHneg_index],1.0);
			    mcHMinusMinusEta_hist->Fill(events->mcDoublyChargedHiggsEta[genHneg_index],1.0);
			    mcHMinusMinusPhi_hist->Fill(events->mcDoublyChargedHiggsPhi[genHneg_index],1.0);

			    mcHPlusPlusP_HMinusMinusP_hist->Fill(events->mcDoublyChargedHiggsP[genHpos_index],events->mcDoublyChargedHiggsP[genHneg_index],1.0);
			    mcHPlusPlusPt_HMinusMinusPt_hist->Fill(events->mcDoublyChargedHiggsPt[genHpos_index],events->mcDoublyChargedHiggsPt[genHneg_index],1.0);
			    mcHPlusPlusEta_HMinusMinusEta_hist->Fill(events->mcDoublyChargedHiggsEta[genHpos_index],events->mcDoublyChargedHiggsEta[genHneg_index],1.0);
			    mcHPlusPlusPhi_HMinusMinusPhi_hist->Fill(events->mcDoublyChargedHiggsPhi[genHpos_index],events->mcDoublyChargedHiggsPhi[genHneg_index],1.0);
			  }
			  if((file_dataset_ == "tauP" || file_dataset_ == "mcha") && doHplusHistos){
			    //cout<<"file dataset is tauP"<<endl;

			    mcH0Charge_hist->Fill(events->mcTauPrimeCharge[genH0_index],eventweightTauPrime);
			    mcH1Charge_hist->Fill(events->mcTauPrimeCharge[genH1_index],eventweightTauPrime);

			    mcHPlusPlusP_hist->Fill(events->mcTauPrimeP[genHpos_index],eventweightTauPrime);
			    mcHPlusPlusPx_hist->Fill(events->mcTauPrimePx[genHpos_index],eventweightTauPrime);
			    mcHPlusPlusPy_hist->Fill(events->mcTauPrimePy[genHpos_index],eventweightTauPrime);
			    mcHPlusPlusPz_hist->Fill(events->mcTauPrimePz[genHpos_index],eventweightTauPrime);
			    mcHPlusPlusPt_hist->Fill(events->mcTauPrimePt[genHpos_index],eventweightTauPrime);
			    mcHPlusPlusEta_hist->Fill(events->mcTauPrimeEta[genHpos_index],eventweightTauPrime);
			    mcHPlusPlusPhi_hist->Fill(events->mcTauPrimePhi[genHpos_index],eventweightTauPrime);
			    mcHMinusMinusP_hist->Fill(events->mcTauPrimeP[genHneg_index],eventweightTauPrime);
			    mcHMinusMinusPx_hist->Fill(events->mcTauPrimePx[genHneg_index],eventweightTauPrime);
			    mcHMinusMinusPy_hist->Fill(events->mcTauPrimePy[genHneg_index],eventweightTauPrime);
			    mcHMinusMinusPz_hist->Fill(events->mcTauPrimePz[genHneg_index],eventweightTauPrime);
			    mcHMinusMinusPt_hist->Fill(events->mcTauPrimePt[genHneg_index],eventweightTauPrime);
			    mcHMinusMinusEta_hist->Fill(events->mcTauPrimeEta[genHneg_index],eventweightTauPrime);
			    mcHMinusMinusPhi_hist->Fill(events->mcTauPrimePhi[genHneg_index],eventweightTauPrime);
			    
			    mcHPlusPlusP_HMinusMinusP_hist->Fill(events->mcTauPrimeP[genHpos_index],events->mcTauPrimeP[genHneg_index],eventweightTauPrime);
			    mcHPlusPlusPt_HMinusMinusPt_hist->Fill(events->mcTauPrimePt[genHpos_index],events->mcTauPrimePt[genHneg_index],eventweightTauPrime);
			    mcHPlusPlusEta_HMinusMinusEta_hist->Fill(events->mcTauPrimeEta[genHpos_index],events->mcTauPrimeEta[genHneg_index],eventweightTauPrime);
			    mcHPlusPlusPhi_HMinusMinusPhi_hist->Fill(events->mcTauPrimePhi[genHpos_index],events->mcTauPrimePhi[genHneg_index],eventweightTauPrime);

			    //cout<<"plotted H histos"<<endl;

			    mcTauPrime_N_hist->Fill(good_genTauPrime,1.0);
			    if(good_genTauPrime>0){
			      //cout<<"at least 1 good Tau Prime"<<endl;
			      double beta0 = -999.;
			      if(events->mcTauPrimeP[genTauPrime0_index]!=0.) beta0 = 1.0/(TMath::Sqrt((events->mcTauPrimeMass[genTauPrime0_index]/events->mcTauPrimeP[genTauPrime0_index])*(events->mcTauPrimeMass[genTauPrime0_index]/events->mcTauPrimeP[genTauPrime0_index])+1));
			      
			      mcTauPrime0Charge_hist->Fill(events->mcTauPrimeCharge[genTauPrime0_index],1.0);			  
			      mcTauPrimeP_hist->Fill(events->mcTauPrimeP[genTauPrime0_index],1.0);
			      mcTauPrimePx_hist->Fill(events->mcTauPrimePx[genTauPrime0_index],1.0);
			      mcTauPrimePy_hist->Fill(events->mcTauPrimePy[genTauPrime0_index],1.0);
			      mcTauPrimePz_hist->Fill(events->mcTauPrimePz[genTauPrime0_index],1.0);
			      mcTauPrimePt_hist->Fill(events->mcTauPrimePt[genTauPrime0_index],1.0);
			      mcTauPrimeEta_hist->Fill(events->mcTauPrimeEta[genTauPrime0_index],1.0);
			      mcTauPrimePhi_hist->Fill(events->mcTauPrimePhi[genTauPrime0_index],1.0);			    
			      mcTauPrimeBeta_hist->Fill(beta0,1.0);
			      
			      if(tauprimeStoppedParticleMatched(events, genTauPrime0_index)){
				cout<<"matched!!! stopped tau prime eta is: "<<events->mcTauPrimeEta[genTauPrime0_index]<<", phi is: "<<events->mcTauPrimePhi[genTauPrime0_index]<<endl;
				stopped_mcTauPrimeP_hist->Fill(events->mcTauPrimeP[genTauPrime0_index],1.0);
				stopped_mcTauPrimePt_hist->Fill(events->mcTauPrimePt[genTauPrime0_index],1.0);
				stopped_mcTauPrimeEta_hist->Fill(events->mcTauPrimeEta[genTauPrime0_index],1.0);
				stopped_mcTauPrimePhi_hist->Fill(events->mcTauPrimePhi[genTauPrime0_index],1.0);			    
				stopped_mcTauPrimeBeta_hist->Fill(beta0,1.0);
			      }
			      else{
				cout<<"not matched: tau prime eta is: "<<events->mcTauPrimeEta[genTauPrime0_index]<<", phi is: "<<events->mcTauPrimePhi[genTauPrime0_index]<<endl;
				notStopped_mcTauPrimeP_hist->Fill(events->mcTauPrimeP[genTauPrime0_index],1.0);
				notStopped_mcTauPrimePt_hist->Fill(events->mcTauPrimePt[genTauPrime0_index],1.0);
				notStopped_mcTauPrimeEta_hist->Fill(events->mcTauPrimeEta[genTauPrime0_index],1.0);
				notStopped_mcTauPrimePhi_hist->Fill(events->mcTauPrimePhi[genTauPrime0_index],1.0);			    
				notStopped_mcTauPrimeBeta_hist->Fill(beta0,1.0);
			      }
			      
			      if(good_genTauPrime>1){
				//cout<<"at least 2 good Tau Prime"<<endl;
				double beta1 = -999.;
				if(events->mcTauPrimeP[genTauPrime1_index]!=0.) beta1 = 1.0/(TMath::Sqrt((events->mcTauPrimeMass[genTauPrime1_index]/events->mcTauPrimeP[genTauPrime1_index])*(events->mcTauPrimeMass[genTauPrime1_index]/events->mcTauPrimeP[genTauPrime1_index])+1));
				
				mcTauPrime1Charge_hist->Fill(events->mcTauPrimeCharge[genTauPrime1_index],1.0);
				mcTauPrimeP_hist->Fill(events->mcTauPrimeP[genTauPrime1_index],1.0);
				mcTauPrimePx_hist->Fill(events->mcTauPrimePx[genTauPrime1_index],1.0);
				mcTauPrimePy_hist->Fill(events->mcTauPrimePy[genTauPrime1_index],1.0);
				mcTauPrimePz_hist->Fill(events->mcTauPrimePz[genTauPrime1_index],1.0);
				mcTauPrimePt_hist->Fill(events->mcTauPrimePt[genTauPrime1_index],1.0);
				mcTauPrimeEta_hist->Fill(events->mcTauPrimeEta[genTauPrime1_index],1.0);
				mcTauPrimePhi_hist->Fill(events->mcTauPrimePhi[genTauPrime1_index],1.0);
				mcTauPrimeBeta_hist->Fill(beta1,1.0);
				
				if(tauprimeStoppedParticleMatched(events, genTauPrime1_index)){
				  cout<<"matched!!! stopped tau prime eta is: "<<events->mcTauPrimeEta[genTauPrime1_index]<<", phi is: "<<events->mcTauPrimePhi[genTauPrime1_index]<<endl;
				  stopped_mcTauPrimeP_hist->Fill(events->mcTauPrimeP[genTauPrime1_index],1.0);
				  stopped_mcTauPrimePt_hist->Fill(events->mcTauPrimePt[genTauPrime1_index],1.0);
				  stopped_mcTauPrimeEta_hist->Fill(events->mcTauPrimeEta[genTauPrime1_index],1.0);
				  stopped_mcTauPrimePhi_hist->Fill(events->mcTauPrimePhi[genTauPrime1_index],1.0);			    
				  stopped_mcTauPrimeBeta_hist->Fill(beta1,1.0);
				}
				else{
				  cout<<"not matched: tau prime eta is: "<<events->mcTauPrimeEta[genTauPrime1_index]<<", phi is: "<<events->mcTauPrimePhi[genTauPrime1_index]<<endl;
				  notStopped_mcTauPrimeP_hist->Fill(events->mcTauPrimeP[genTauPrime1_index],1.0);
				  notStopped_mcTauPrimePt_hist->Fill(events->mcTauPrimePt[genTauPrime1_index],1.0);
				  notStopped_mcTauPrimeEta_hist->Fill(events->mcTauPrimeEta[genTauPrime1_index],1.0);
				  notStopped_mcTauPrimePhi_hist->Fill(events->mcTauPrimePhi[genTauPrime1_index],1.0);			    
				  notStopped_mcTauPrimeBeta_hist->Fill(beta1,1.0);
				}//end of if stau not matched to a stopped particle
				
			      }//end of if 2 or more good staus
			    }//end of if 1 or more good staus
			    
			  }//end of if file is tauPrime or mchamps
			}//end of if 2 good H++
		      }//end of if other mc

		      //cout<<"about to plot mcMuon histos"<<endl;
		      mcMuon_N_hist->Fill(good_genMuons,1.0); //only status 1 good muons
		      if(genMu0_index!= 999){
			mcMuonP_hist->Fill(events->mcMuonP[genMu0_index],1.0);
			mcMuonPt_hist->Fill(events->mcMuonPt[genMu0_index],1.0);
			mcMuonEta_hist->Fill(events->mcMuonEta[genMu0_index],1.0);
			mcMuonPhi_hist->Fill(events->mcMuonPhi[genMu0_index],1.0);
			mcMuonStatus_hist->Fill(events->mcMuonStatus[genMu0_index],1.0);
			mcMuonCharge_hist->Fill(events->mcMuonCharge[genMu0_index],1.0);
			mcMuonMass_hist->Fill(events->mcMuonMass[genMu0_index],1.0);
			mcMuonVx_hist->Fill(events->mcMuonVx[genMu0_index],1.0);
			mcMuonVy_hist->Fill(events->mcMuonVy[genMu0_index],1.0);
			mcMuonVz_hist->Fill(events->mcMuonVz[genMu0_index],1.0);
			
			double lxy = (events->mcMuonVx[genMu0_index])*(events->mcMuonVx[genMu0_index])+(events->mcMuonVy[genMu0_index])*(events->mcMuonVy[genMu0_index]);
			lxy = TMath::Sqrt(lxy);
			mcMuonLxy_hist->Fill(lxy,1.0);
			
			double dxy = -999.;
			if(events->mcMuonPt[genMu0_index]!=0.){
			  dxy = (events->mcMuonVx[genMu0_index]*events->mcMuonPy[genMu0_index] - events->mcMuonVy[genMu0_index]*events->mcMuonPx[genMu0_index])/(events->mcMuonPt[genMu0_index]);
			}
			mcMuonDxy_hist->Fill(dxy,1.0);
			
			double invBeta = -999.;
			if(events->mcMuonP[genMu0_index]!=0.){
			  invBeta = (events->mcMuonMass[genMu0_index]*events->mcMuonMass[genMu0_index])/(events->mcMuonP[genMu0_index]*events->mcMuonP[genMu0_index])+1;
			  invBeta = TMath::Sqrt(invBeta);
			}
			mcMuonInverseBeta_hist->Fill(invBeta,1.0);
			
			if(good_genMuons==2 || good_genMuons==4){
			  if(good_genPosMuons==2){
			    mcMuon3Dangle_hist->Fill(anglePos,1.0);
			    mcMuonDeltaPhi_hist->Fill(events->mcMuonPhi[genPosMuUpper_index] - events->mcMuonPhi[genPosMuLower_index],1.0);
			  }
			  else if(good_genNegMuons==2){
			    mcMuon3Dangle_hist->Fill(angleNeg,1.0);
			    mcMuonDeltaPhi_hist->Fill(events->mcMuonPhi[genNegMuUpper_index] - events->mcMuonPhi[genNegMuLower_index],1.0);
			  }
			}			
			//cout<<"finished genMu histos"<<endl;
			
			//sim histos
			simTrackN_hist->Fill(events->simTrack_N,1.0);
			if(simTrack0_index!=999){
			  simTrackPt_hist->Fill(events->simTrackPt[simTrack0_index],1.0);
			  simTrackEta_hist->Fill(events->simTrackEta[simTrack0_index],1.0);
			  simTrackPhi_hist->Fill(events->simTrackPhi[simTrack0_index],1.0);
			  simTrackCharge_hist->Fill(events->simTrackCharge[simTrack0_index],1.0);
			  simTrackVx_hist->Fill(events->simTrackVx[simTrack0_index],1.0);
			  simTrackVy_hist->Fill(events->simTrackVy[simTrack0_index],1.0);
			  simTrackVz_hist->Fill(events->simTrackVz[simTrack0_index],1.0);
			}
			//cout<<"finished sim histos"<<endl;
			
			if(events->l1Muon_N>0){
			  mcMuonPt_l1MuonPt_hist->Fill(events->mcMuonPt[genMu0_index],events->l1MuonPt[0],1.0);		      
			  mcMuonEta_l1MuonEta_hist->Fill(events->mcMuonEta[genMu0_index],events->l1MuonEta[0],1.0);
			  mcMuonPhi_l1MuonPhi_hist->Fill(events->mcMuonPhi[genMu0_index],events->l1MuonPhi[0],1.0);
			}
			
			if(events->hlt20Cha2Muon_N>0){
			  mcMuonPt_hlt20Cha2MuonPt_hist->Fill(events->mcMuonPt[genMu0_index],events->hlt20Cha2MuonPt[0],1.0);
			  mcMuonEta_hlt20Cha2MuonEta_hist->Fill(events->mcMuonEta[genMu0_index],events->hlt20Cha2MuonEta[0],1.0);
			  mcMuonPhi_hlt20Cha2MuonPhi_hist->Fill(events->mcMuonPhi[genMu0_index],events->hlt20Cha2MuonPhi[0],1.0);
			}
			//cout<<"finished trigger histos"<<endl;
		      }
		    }//end of if MC

		    //muDisplacedStandAlone_N_hist->Fill(events->mu_DisplacedStandAlone_N,1.0);

		    //cout<<"starting to look at preselection"<<endl;
		    if(n_passPreselection>0){
		      if(highestPt_index!=999){
			//ABCDevent = events; 
			//ABCDtree->Fill();   
			//StoppingRegionAcceptance(events);
			//cout<<"starting highestPt plots"<<endl;		      		      
			
			GlobalSATagAndProbe(events, highestPt_index);

			//1D n tracks and total n segments histos
			muDisplacedStandAlone_N_hist->Fill(events->mu_DisplacedStandAlone_N,1.0);
			//muDisplacedStandAlone_N_hist->Fill(n_passPreselection,1.0);
			//muRefittedStandAlone_N_hist->Fill(events->mu_RefittedStandAlone_N,1.0);
			//muStandAloneTof_N_hist->Fill(events->muStandAloneTof_N,1.0);
			
			//cout<<"number of displaced SA muon tracks is: "<<events->mu_DisplacedStandAlone_N<<endl;

			DTSegment_N_hist->Fill(events->DTSegment_N,1.0);
			CSCSegment_N_hist->Fill(events->cscSeg_N,1.0);
			
			//1D displaced SA highest pt histos
			muDisplacedStandAloneP_hist->Fill(events->muDisplacedStandAloneP[highestPt_index],1.0);					    
			muDisplacedStandAlonePt_hist->Fill(events->muDisplacedStandAlonePt[highestPt_index],1.0);					    
			muDisplacedStandAloneEta_hist->Fill(events->muDisplacedStandAloneEta[highestPt_index],1.0);					    
			muDisplacedStandAlonePhi_hist->Fill(events->muDisplacedStandAlonePhi[highestPt_index],1.0);					    
			muDisplacedStandAloneCharge_hist->Fill(events->muDisplacedStandAloneCharge[highestPt_index],1.0);				    
			muDisplacedStandAloneTrackNormalizedChi2_hist->Fill(events->muDisplacedStandAloneTrackNormalizedChi2[highestPt_index],1.0);	    
			muDisplacedStandAloneTrackDxy_hist->Fill(events->muDisplacedStandAloneTrackDxy[highestPt_index],1.0);				    
			muDisplacedStandAloneTrackDz_hist->Fill(events->muDisplacedStandAloneTrackDz[highestPt_index],1.0);				    
			muDisplacedStandAloneTrackNHitsMuon_hist->Fill(events->muDisplacedStandAloneTrackNValidMuonHits[highestPt_index],1.0);		    
			muDisplacedStandAloneTrackNHitsCsc_hist->Fill(events->muDisplacedStandAloneTrackNValidCscHits[highestPt_index],1.0);		    
			muDisplacedStandAloneTrackNHitsDt_hist->Fill(events->muDisplacedStandAloneTrackNValidDtHits[highestPt_index],1.0);		    
			muDisplacedStandAloneTrackNHitsRpc_hist->Fill(events->muDisplacedStandAloneTrackNValidRpcHits[highestPt_index],1.0);		    
			muDisplacedStandAloneTrackNRpcDof_hist->Fill(events->muDisplacedStandAloneTrackRpcHitZ.at(highestPt_index).size(),1.0);		    
			muDisplacedStandAloneTrackNStations_hist->Fill(events->muDisplacedStandAloneTrackNStationsWithValidHits[highestPt_index],1.0);	    
			muDisplacedStandAloneTrackNChambersCsc_hist->Fill(events->muDisplacedStandAloneTrackNCscChambersWithValidHits[highestPt_index],1.0);
			muDisplacedStandAloneTrackNChambersDt_hist->Fill(events->muDisplacedStandAloneTrackNDtChambersWithValidHits[highestPt_index],1.0);  
			muDisplacedStandAloneTrackNChambersRpc_hist->Fill(events->muDisplacedStandAloneTrackNRpcChambersWithValidHits[highestPt_index],1.0);
			muDisplacedStandAloneTrackInnerPt_hist->Fill(TMath::Sqrt((events->muDisplacedStandAloneTrackInnerPx[highestPt_index])*(events->muDisplacedStandAloneTrackInnerPx[highestPt_index])+(events->muDisplacedStandAloneTrackInnerPy[highestPt_index])*(events->muDisplacedStandAloneTrackInnerPy[highestPt_index])),1.0);
			muDisplacedStandAloneTrackDtTofNDof_hist->Fill(events->muDisplacedStandAloneTrackDtTofNDof[highestPt_index],1.0);
			muDisplacedStandAloneEta_muDisplacedStandAlonePhi_hist->Fill(events->muDisplacedStandAloneEta[highestPt_index],events->muDisplacedStandAlonePhi[highestPt_index],1.0);
			muDisplacedStandAloneTrackNHitsRpc_muDisplacedStandAloneTrackNormalizedChi2_hist->Fill(events->muDisplacedStandAloneTrackNValidRpcHits[highestPt_index],events->muDisplacedStandAloneTrackNormalizedChi2[highestPt_index],1.0);
			muDisplacedStandAloneTrackNHitsRpc_muDisplacedStandAloneTrackNHitsDt_hist->Fill(events->muDisplacedStandAloneTrackNValidRpcHits[highestPt_index],events->muDisplacedStandAloneTrackNValidDtHits[highestPt_index],1.0);
			muDisplacedStandAloneBxPattern_hist->Fill(Rpc_Bx_Pattern(events,highestPt_index)); //for highest pt muon
			if(Rpc_Bx_Pattern(events, highestPt_index)==0) muDisplacedStandAloneNHitsRpcBxPattern0_hist->Fill(events->muDisplacedStandAloneTrackRpcHitZ.at(highestPt_index).size());
			muDisplacedStandAloneBxAverage_hist->Fill(Rpc_Bx_Average(events,highestPt_index)); //for highest pt muon
			//muDisplacedStandAloneOppositeSegDR_hist->Fill(segment_dR,1.0);
			//muDisplacedStandAloneOppositeSegDEta_hist->Fill(segment_dEta,1.0);
			//muDisplacedStandAloneOppositeSegDPhi_hist->Fill(segment_dPhi,1.0);
			
			/*
			muDisplacedStandAloneDTTofDirection_hist->Fill(events->muDisplacedStandAloneTrackDtTofDirection[highestPt_index],1.0);
			muDisplacedStandAloneDTTofNDof_hist->Fill(events->muDisplacedStandAloneTrackDtTofNDof[highestPt_index],1.0);
			muDisplacedStandAloneDTTofInverseBeta_hist->Fill(events->muDisplacedStandAloneTrackDtTofInverseBeta[highestPt_index],1.0);
			muDisplacedStandAloneDTTofInverseBetaErr_hist->Fill(events->muDisplacedStandAloneTrackDtTofInverseBetaErr[highestPt_index],1.0);
			muDisplacedStandAloneDTTofFreeInverseBeta_hist->Fill(events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[highestPt_index],1.0);  
			muDisplacedStandAloneDTTofFreeInverseBetaErr_hist->Fill(events->muDisplacedStandAloneTrackDtTofFreeInverseBetaErr[highestPt_index],1.0);
			muDisplacedStandAloneDTTofTimeAtIpInOut_hist->Fill(events->muDisplacedStandAloneTrackDtTofTimeAtIpInOut[highestPt_index],1.0);	    
			muDisplacedStandAloneDTTofTimeAtIpInOutErr_hist->Fill(events->muDisplacedStandAloneTrackDtTofTimeAtIpInOutErr[highestPt_index],1.0);
			muDisplacedStandAloneDTTofTimeAtIpOutIn_hist->Fill(events->muDisplacedStandAloneTrackDtTofTimeAtIpOutIn[highestPt_index],1.0);
			muDisplacedStandAloneDTTofTimeAtIpOutInErr_hist->Fill(events->muDisplacedStandAloneTrackDtTofTimeAtIpOutInErr[highestPt_index],1.0);
			*/

			muDisplacedStandAloneTrackShowerSize_station0_hist->Fill(events->muDisplacedStandAloneTrackShowerSize_station0[highestPt_index],1.0);
			muDisplacedStandAloneTrackShowerSize_station1_hist->Fill(events->muDisplacedStandAloneTrackShowerSize_station1[highestPt_index],1.0);
			muDisplacedStandAloneTrackShowerSize_station2_hist->Fill(events->muDisplacedStandAloneTrackShowerSize_station2[highestPt_index],1.0);
			muDisplacedStandAloneTrackShowerSize_station3_hist->Fill(events->muDisplacedStandAloneTrackShowerSize_station3[highestPt_index],1.0);
			muDisplacedStandAloneTrackShowerDeltaR_station0_hist->Fill(events->muDisplacedStandAloneTrackShowerDeltaR_station0[highestPt_index],1.0);
			muDisplacedStandAloneTrackShowerDeltaR_station1_hist->Fill(events->muDisplacedStandAloneTrackShowerDeltaR_station1[highestPt_index],1.0);
			muDisplacedStandAloneTrackShowerDeltaR_station2_hist->Fill(events->muDisplacedStandAloneTrackShowerDeltaR_station2[highestPt_index],1.0);
			muDisplacedStandAloneTrackShowerDeltaR_station3_hist->Fill(events->muDisplacedStandAloneTrackShowerDeltaR_station3[highestPt_index],1.0);
			muDisplacedStandAloneTrackShowerNHits_station0_hist->Fill(events->muDisplacedStandAloneTrackShowerNHits_station0[highestPt_index],1.0);
			muDisplacedStandAloneTrackShowerNHits_station1_hist->Fill(events->muDisplacedStandAloneTrackShowerNHits_station1[highestPt_index],1.0);
			muDisplacedStandAloneTrackShowerNHits_station2_hist->Fill(events->muDisplacedStandAloneTrackShowerNHits_station2[highestPt_index],1.0);
			muDisplacedStandAloneTrackShowerNHits_station3_hist->Fill(events->muDisplacedStandAloneTrackShowerNHits_station3[highestPt_index],1.0);
			muDisplacedStandAloneTrackShowerNCorrelatedHits_station0_hist->Fill(events->muDisplacedStandAloneTrackShowerNCorrelatedHits_station0[highestPt_index],1.0);
			muDisplacedStandAloneTrackShowerNCorrelatedHits_station1_hist->Fill(events->muDisplacedStandAloneTrackShowerNCorrelatedHits_station1[highestPt_index],1.0);
			muDisplacedStandAloneTrackShowerNCorrelatedHits_station2_hist->Fill(events->muDisplacedStandAloneTrackShowerNCorrelatedHits_station2[highestPt_index],1.0);
			muDisplacedStandAloneTrackShowerNCorrelatedHits_station3_hist->Fill(events->muDisplacedStandAloneTrackShowerNCorrelatedHits_station3[highestPt_index],1.0);
			muDisplacedStandAloneTrackShowerNUncorrelatedHits_station0_hist->Fill(events->muDisplacedStandAloneTrackShowerNUncorrelatedHits_station0[highestPt_index],1.0);
			muDisplacedStandAloneTrackShowerNUncorrelatedHits_station1_hist->Fill(events->muDisplacedStandAloneTrackShowerNUncorrelatedHits_station1[highestPt_index],1.0);
			muDisplacedStandAloneTrackShowerNUncorrelatedHits_station2_hist->Fill(events->muDisplacedStandAloneTrackShowerNUncorrelatedHits_station2[highestPt_index],1.0);
			muDisplacedStandAloneTrackShowerNUncorrelatedHits_station3_hist->Fill(events->muDisplacedStandAloneTrackShowerNUncorrelatedHits_station3[highestPt_index],1.0);
			
			//2D displaced tracks histos
			muDisplacedStandAlonePhi_muDisplacedStandAloneDTTofFreeInverseBeta_hist->Fill(events->muDisplacedStandAlonePhi[highestPt_index],events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[highestPt_index],1.0);
			muDisplacedStandAloneNChambersDt_Pt_hist->Fill(events->muDisplacedStandAloneTrackNDtChambersWithValidHits[highestPt_index], events->muDisplacedStandAlonePt[highestPt_index],1.0);
			muDisplacedStandAloneNChambersRpc_Pt_hist->Fill(events->muDisplacedStandAloneTrackNRpcChambersWithValidHits[highestPt_index], events->muDisplacedStandAlonePt[highestPt_index],1.0);
			muDisplacedStandAlonePt_DtTofFreeInverseBeta_hist->Fill(events->muDisplacedStandAlonePt[highestPt_index],events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[highestPt_index],1.0);
			muDisplacedStandAloneP_DtTofFreeInverseBeta_hist->Fill(events->muDisplacedStandAloneP[highestPt_index],events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[highestPt_index],1.0);
			muDisplacedStandAloneP_BxPattern_hist->Fill(events->muDisplacedStandAloneP[highestPt_index],Rpc_Bx_Pattern(events,highestPt_index),1.0);
			muDisplacedStandAlonePt_BxPattern_hist->Fill(events->muDisplacedStandAlonePt[highestPt_index],Rpc_Bx_Pattern(events,highestPt_index),1.0);
			muDisplacedStandAloneDtTofFreeInverseBeta_DtTofDirection_hist->Fill(events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[highestPt_index],events->muDisplacedStandAloneTrackDtTofDirection[highestPt_index],1.0);
			muDisplacedStandAloneDtTofFreeInverseBetaErr_DtTofNDof_hist->Fill(events->muDisplacedStandAloneTrackDtTofFreeInverseBetaErr[highestPt_index],events->muDisplacedStandAloneTrackDtTofNDof[highestPt_index],1.0);
			
			runNumber_muDisplacedStandAloneDtTofFreeInverseBeta_hist->Fill(events->run,events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[highestPt_index],1.0);
			runNumber_muDisplacedStandAloneDtTofInverseBeta_hist->Fill(events->run,events->muDisplacedStandAloneTrackDtTofInverseBeta[highestPt_index],1.0);
			runNumber_muDisplacedStandAlonePt_hist->Fill(events->run,events->muDisplacedStandAlonePt[highestPt_index],1.0);		      
			runNumber_muDisplacedStandAlonePhi_hist->Fill(events->run,events->muDisplacedStandAlonePhi[highestPt_index],1.0);
			muDisplacedStandAloneEta_Phi_hist->Fill(events->muDisplacedStandAloneEta[highestPt_index],events->muDisplacedStandAlonePhi[highestPt_index],1.0);

			//cout<<"finished DSA histos"<<endl;
			/*
			//RPC BX pattern ABCD
			//if(Rpc_Bx_Pattern(events,highestPt_index)==0 || Rpc_Bx_Pattern(events,highestPt_index)==1){
			if(Rpc_Bx_Pattern(events,highestPt_index)==0){
			  if(events->muDisplacedStandAloneP[highestPt_index]>abcdPtCutValue_){
			    nDregionRpc_++;
			    regionD_muDisplacedStandAloneP_hist->Fill(events->muDisplacedStandAloneP[highestPt_index],1.0);					    
			    regionD_muDisplacedStandAloneBxPattern_hist->Fill(Rpc_Bx_Pattern(events,highestPt_index)); //for highest pt muon	
			    if(doPrintout){
			      printout_setup(events,is_data);
			      
			      //printout_gen(events);
			      //printout_DSA(events);
			      //printout_SA(events);
			      //printout_RSA(events);
			      //printout_cosmic(events);
			      //printout_L2(events);
			      //printout_L1(events);
			      
			    }
			  }
			  else{
			    nCregionRpc_++;
			    regionC_muDisplacedStandAloneTrackBxPattern_hist->Fill(Rpc_Bx_Pattern(events,highestPt_index),1.0);
			    if(events->muDisplacedStandAloneP[highestPt_index] > acPtCutValue_)  nC2region++;
			    else nC1region++;			    
			  }
			}
			else{
			  if(events->muDisplacedStandAloneP[highestPt_index]>abcdPtCutValue_){
			    nBregionRpc_++;
			    regionB_muDisplacedStandAloneP_hist->Fill(events->muDisplacedStandAloneP[highestPt_index],1.0);
			    //if(Rpc_Bx_Pattern(events,highestPt_index)==1) nB1region++;
			    //else nB2region++;
			  }
			  else{
			    nAregionRpc_++;
			    if(events->muDisplacedStandAloneP[highestPt_index] > acPtCutValue_)  nA2region++;
			    else nA1region++;
			    //if(Rpc_Bx_Pattern(events,highestPt_index)==1) nA1region++;
			    //else nA2region++;			  
			  }
			}
			*/
			/*
			//abcd with free inverse beta and p
			if(events->muDisplacedStandAloneP[highestPt_index] > abcdPtCutValue_){
			  if(events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[highestPt_index] > abcdInvBetaCutValue_){
			    nDregion++;

			    regionD_muDisplacedStandAlone_N_hist->Fill(events->mu_DisplacedStandAlone_N,1.0);
			    regionD_muDisplacedStandAloneP_hist->Fill(events->muDisplacedStandAloneP[highestPt_index],1.0);					    
			    regionD_muDisplacedStandAlonePt_hist->Fill(events->muDisplacedStandAlonePt[highestPt_index],1.0);					    
			    regionD_muDisplacedStandAloneEta_hist->Fill(events->muDisplacedStandAloneEta[highestPt_index],1.0);					   
			    regionD_muDisplacedStandAlonePhi_hist->Fill(events->muDisplacedStandAlonePhi[highestPt_index],1.0);					   
			    regionD_muDisplacedStandAloneCharge_hist->Fill(events->muDisplacedStandAloneCharge[highestPt_index],1.0);				    
			    regionD_muDisplacedStandAloneTrackNormalizedChi2_hist->Fill(events->muDisplacedStandAloneTrackNormalizedChi2[highestPt_index],1.0);	
			    regionD_muDisplacedStandAloneTrackDxy_hist->Fill(events->muDisplacedStandAloneTrackDxy[highestPt_index],1.0);			
			    regionD_muDisplacedStandAloneTrackDz_hist->Fill(events->muDisplacedStandAloneTrackDz[highestPt_index],1.0);				   
			    regionD_muDisplacedStandAloneTrackNHitsMuon_hist->Fill(events->muDisplacedStandAloneTrackNValidMuonHits[highestPt_index],1.0);	
			    regionD_muDisplacedStandAloneTrackNHitsCsc_hist->Fill(events->muDisplacedStandAloneTrackNValidCscHits[highestPt_index],1.0);	
			    regionD_muDisplacedStandAloneTrackNHitsDt_hist->Fill(events->muDisplacedStandAloneTrackNValidDtHits[highestPt_index],1.0);		
			    regionD_muDisplacedStandAloneTrackNHitsRpc_hist->Fill(events->muDisplacedStandAloneTrackNValidRpcHits[highestPt_index],1.0);	
			    regionD_muDisplacedStandAloneTrackNRpcDof_hist->Fill(events->muDisplacedStandAloneTrackRpcHitZ.at(highestPt_index).size(),1.0);	
			    regionD_muDisplacedStandAloneTrackNStations_hist->Fill(events->muDisplacedStandAloneTrackNStationsWithValidHits[highestPt_index],1.0);	
			    regionD_muDisplacedStandAloneTrackNChambersCsc_hist->Fill(events->muDisplacedStandAloneTrackNCscChambersWithValidHits[highestPt_index],1.0);
			    regionD_muDisplacedStandAloneTrackNChambersDt_hist->Fill(events->muDisplacedStandAloneTrackNDtChambersWithValidHits[highestPt_index],1.0);  
			    regionD_muDisplacedStandAloneTrackNChambersRpc_hist->Fill(events->muDisplacedStandAloneTrackNRpcChambersWithValidHits[highestPt_index],1.0);
			    regionD_muDisplacedStandAloneTrackDtTofNDof_hist->Fill(events->muDisplacedStandAloneTrackDtTofNDof[highestPt_index],1.0);
			    regionD_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist->Fill(events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[highestPt_index],1.0);  
			    regionD_muDisplacedStandAloneTrackDtTofFreeInverseBetaErr_hist->Fill(events->muDisplacedStandAloneTrackDtTofFreeInverseBetaErr[highestPt_index],1.0);
			    regionD_muDisplacedStandAloneTrackDtTofTimeAtIpInOut_hist->Fill(events->muDisplacedStandAloneTrackDtTofTimeAtIpInOut[highestPt_index],1.0);	    
			    regionD_muDisplacedStandAloneTrackDtTofTimeAtIpInOutErr_hist->Fill(events->muDisplacedStandAloneTrackDtTofTimeAtIpInOutErr[highestPt_index],1.0);
			    regionD_muDisplacedStandAloneBxPattern_hist->Fill(Rpc_Bx_Pattern(events,highestPt_index)); //for highest pt muon

			    if(doPrintout){
			      printout_setup(events,is_data);
			      //printout_gen(events);
			      //printout_SA(events);
			      //printout_L2(events);
			      //printout_L1(events);
			    }
			  }
			  else{
			    nBregion++;
			    regionB_muDisplacedStandAloneP_hist->Fill(events->muDisplacedStandAloneP[highestPt_index],1.0);
			  }
			}
			else{
			  if(events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[highestPt_index] > abcdInvBetaCutValue_){
			    nCregion++;
			    regionC_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist->Fill(events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[highestPt_index],1.0);
			  }
			  else nAregion++;
			}


			//abcd with free inverse beta and direction, and pt
			if(events->muDisplacedStandAlonePt[highestPt_index] > abcdPtCutValue_){
			  if(events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[highestPt_index] > abcdInvBetaCutValue_ && events->muDisplacedStandAloneTrackDtTofDirection[highestPt_index]==1) nDregionDir++;
			  else if(events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[highestPt_index] <= abcdInvBetaCutValue_ && events->muDisplacedStandAloneTrackDtTofDirection[highestPt_index]==-1) nBregionDir++;
			}
			else{
			  if(events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[highestPt_index] > abcdInvBetaCutValue_ && events->muDisplacedStandAloneTrackDtTofDirection[highestPt_index]==1) nCregionDir++;
			  else if(events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[highestPt_index] <= abcdInvBetaCutValue_ && events->muDisplacedStandAloneTrackDtTofDirection[highestPt_index]==-1) nAregionDir++;
			}
			
			*/
			//cout<<"finished A and B region calculation"<<endl;

			//2D genMu0 vs displaced SA histos, 1D MC resolution histos
			if(!is_data){
			  //cout<<"not data"<<endl;

			  if(file_dataset_!="cosm" && file_dataset_!="PGun") mcStoppedParticleR_mcMuonPt_hist->Fill(events->mcStoppedParticleR[stopped_index]/10.,events->mcMuonPt[highestPt_index],1.0);

			  //cout<<"starting pt hists"<<endl;
			 
			  /*
			  if(doPrintout){
			    printout_setup(events,is_data);
			    printout_gen(events);
			    printout_DSA(events);
			    printout_SA(events);
			    printout_SA_UpdatedAtVtx(events);
			    printout_RSA(events);
			    printout_cosmic(events);
			    printout_L2(events);
			    printout_L1(events);
			  }
			  */

			  //cout<<"starting muon POG resolution hists"<<endl;
			  /*
			  for (UInt_t j=0; j<events->mu_DisplacedStandAlone_N; j++) {
			    if(events->muDisplacedStandAloneTrackNDtChambersWithValidHits[j]>1){
			      if(events->muDisplacedStandAloneTrackGenParticleIndex[j] >= 0){// matched_DSA
				double dR = deltaR(events->muDisplacedStandAloneEta[j],events->muDisplacedStandAlonePhi[j],events->mcMuonEta[genMuMatched_DSA_index[j]],events->mcMuonPhi[genMuMatched_DSA_index[j]]);
				muDisplacedStandAloneGenDR_hist->Fill(dR);
				if(file_dataset_!="cosm" && file_dataset_!="PGun") mcStoppedParticleR_muDisplacedStandAloneGenDR_hist->Fill(events->mcStoppedParticleR[stopped_index]/10.,dR,1.0);
				if(dR<0.5){
				  if(events->mcMuonPt[genMuMatched_DSA_index[j]]>0. && events->muDisplacedStandAlonePt[j]>0.){
				    //if(file_dataset_!="cosm" && file_dataset_!="PGun" && events->mcStoppedParticleR[stopped_index]/10.<400){
				    //if(events->muDisplacedStandAloneCharge[j]!=events->mcMuonCharge[genMuMatched_DSA_index[j]]){
				      double pt_resolution = 1.0*(events->muDisplacedStandAlonePt[j] - events->mcMuonPt[genMuMatched_DSA_index[j]])/(events->mcMuonPt[genMuMatched_DSA_index[j]]); 
				      double qOverPt_resolution = 1.0*(1.0*events->muDisplacedStandAloneCharge[j]/events->muDisplacedStandAlonePt[j] - 1.0*events->mcMuonCharge[genMuMatched_DSA_index[j]]/events->mcMuonPt[genMuMatched_DSA_index[j]])/(1.0*events->mcMuonCharge[genMuMatched_DSA_index[j]]/events->mcMuonPt[genMuMatched_DSA_index[j]]); 
				      //muDisplacedStandAloneP_hist->Fill(events->muDisplacedStandAloneP[j],1.0);
				      //muDisplacedStandAlonePt_hist->Fill(events->muDisplacedStandAlonePt[j],1.0);
				      if(j==0) muDisplacedStandAlonePt0_hist->Fill(events->muDisplacedStandAlonePt[0],1.0);
				      if(j==1) muDisplacedStandAlonePt1_hist->Fill(events->muDisplacedStandAlonePt[1],1.0);
				      if(j==2) muDisplacedStandAlonePt2_hist->Fill(events->muDisplacedStandAlonePt[2],1.0);
				      muDisplacedStandAlonePtResolution_hist->Fill(pt_resolution,1.0);
				      muDisplacedStandAloneQoverPtResolution_hist->Fill(qOverPt_resolution,1.0);
				      //cout<<"muDisplacedPt is: "<<events->muDisplacedStandAlonePt[j]<<", genMuMatched_DSA_index is: "<<genMuMatched_DSA_index[j]<<", dR is: "<<dR<<endl;
				      //}
				  }
				}
			      }
			    }
			  }
			  
			  for (UInt_t j=0; j<events->mu_N; j++) {	    
			    if(events->muIsStandAloneMuon[j] && events->muIsGlobalMuon[j] && events->muSAnDtChambersWithValidHits[j]>1){
			      if(events->muSAgenParticleIndex[j] >= 0){// matched_mu
				double dR = deltaR(events->muEta[j],events->muPhi[j],events->mcMuonEta[genMuMatched_mu_index[j]],events->mcMuonPhi[genMuMatched_mu_index[j]]);
				muGenDR_hist->Fill(dR);
				if(dR<0.5){
				  if(events->mcMuonPt[genMuMatched_mu_index[j]]>0. && events->muTunePpt[j]>0.){
				    double pt_resolution = 1.0*(events->muTunePpt[j] - events->mcMuonPt[genMuMatched_mu_index[j]])/(events->mcMuonPt[genMuMatched_mu_index[j]]); 
				    double qOverPt_resolution = 1.0*(1.0*events->muTunePcharge[j]/events->muTunePpt[j] - 1.0*events->mcMuonCharge[genMuMatched_mu_index[j]]/events->mcMuonPt[genMuMatched_mu_index[j]])/(1.0*events->mcMuonCharge[genMuMatched_mu_index[j]]/events->mcMuonPt[genMuMatched_mu_index[j]]); 
				    muP_hist->Fill(events->muTunePp[j],1.0);
				    muPt_hist->Fill(events->muTunePpt[j],1.0);
				    muPtResolution_hist->Fill(pt_resolution,1.0);
				    muQoverPtResolution_hist->Fill(qOverPt_resolution,1.0);
				    //cout<<"muTunePpt is: "<<events->muTunePpt[j]<<", muSAcharge is: "<<events->muSAcharge[j]<<", genMuMatched_mu_index is: "<<genMuMatched_mu_index[j]<<", dR is: "<<dR<<", genMuCharge is: "<<events->mcMuonCharge[genMuMatched_mu_index[j]]<<", genMuPt is: "<<events->mcMuonPt[genMuMatched_mu_index[j]]<<endl;
				  }
				}
			      }
			    }
			  }
			  
			  for (UInt_t j=0; j<events->mu_StandAlone_N; j++) {
			    if(events->muStandAloneTrackNDtChambersWithValidHits[j]>1){
			      if(events->muStandAloneTrackGenParticleIndex[j] >= 0){// matched_SA
				double dR = deltaR(events->muStandAloneEta[j],events->muStandAlonePhi[j],events->mcMuonEta[genMuMatched_SA_index[j]],events->mcMuonPhi[genMuMatched_SA_index[j]]);
				muStandAloneTrackGenDR_hist->Fill(dR);
				if(dR<0.5){
				  if(events->mcMuonPt[genMuMatched_SA_index[j]]>0. && events->muStandAlonePt[j]>0.){			  
				    //if(file_dataset_!="cosm" && file_dataset_!="PGun" && events->mcStoppedParticleR[stopped_index]/10.<400){
				    //if(events->muStandAloneCharge[j]!=events->mcMuonCharge[genMuMatched_SA_index[j]]){
				      double pt_resolution = 1.0*(events->muStandAlonePt[j] - events->mcMuonPt[genMuMatched_SA_index[j]])/(events->mcMuonPt[genMuMatched_SA_index[j]]); 
				      double qOverPt_resolution = 1.0*(1.0*events->muStandAloneCharge[j]/events->muStandAlonePt[j] - 1.0*events->mcMuonCharge[genMuMatched_SA_index[j]]/events->mcMuonPt[genMuMatched_SA_index[j]])/(1.0*events->mcMuonCharge[genMuMatched_SA_index[j]]/events->mcMuonPt[genMuMatched_SA_index[j]]); 
				      muStandAloneP_hist->Fill(events->muStandAloneP[j],1.0);
				      muStandAlonePt_hist->Fill(events->muStandAlonePt[j],1.0);
				      muStandAlonePtResolution_hist->Fill(pt_resolution,1.0);
				      muStandAloneQoverPtResolution_hist->Fill(qOverPt_resolution,1.0);
				      //}
				  }
				}
			      }
			    }
			  }

			  for (UInt_t j=0; j<events->mu_StandAloneUpdatedAtVtx_N; j++) {
			    if(events->muStandAloneTrackUpdatedAtVtxNDtChambersWithValidHits[j]>1){
			      if(events->muStandAloneTrackUpdatedAtVtxGenParticleIndex[j] >= 0){// matched_SAUpdatedAtVtx
				double dR = deltaR(events->muStandAloneUpdatedAtVtxEta[j],events->muStandAloneUpdatedAtVtxPhi[j],events->mcMuonEta[genMuMatched_SAUpdatedAtVtx_index[j]],events->mcMuonPhi[genMuMatched_SAUpdatedAtVtx_index[j]]);
				muStandAloneTrackUpdatedAtVtxGenDR_hist->Fill(dR);
				if(dR<0.5){
				  if(events->mcMuonPt[genMuMatched_SAUpdatedAtVtx_index[j]]>0. && events->muStandAloneUpdatedAtVtxPt[j]>0.){			  
				    double pt_resolution = 1.0*(events->muStandAloneUpdatedAtVtxPt[j] - events->mcMuonPt[genMuMatched_SAUpdatedAtVtx_index[j]])/(events->mcMuonPt[genMuMatched_SAUpdatedAtVtx_index[j]]); 
				    double qOverPt_resolution = 1.0*(1.0*events->muStandAloneUpdatedAtVtxCharge[j]/events->muStandAloneUpdatedAtVtxPt[j] - 1.0*events->mcMuonCharge[genMuMatched_SAUpdatedAtVtx_index[j]]/events->mcMuonPt[genMuMatched_SAUpdatedAtVtx_index[j]])/(1.0*events->mcMuonCharge[genMuMatched_SAUpdatedAtVtx_index[j]]/events->mcMuonPt[genMuMatched_SAUpdatedAtVtx_index[j]]); 
				    muStandAloneUpdatedAtVtxP_hist->Fill(events->muStandAloneUpdatedAtVtxP[j],1.0);
				    muStandAloneUpdatedAtVtxPt_hist->Fill(events->muStandAloneUpdatedAtVtxPt[j],1.0);
				    muStandAloneUpdatedAtVtxPtResolution_hist->Fill(pt_resolution,1.0);
				    muStandAloneUpdatedAtVtxQoverPtResolution_hist->Fill(qOverPt_resolution,1.0);
				  }
				}
			      }
			    }
			  }

			  for (UInt_t j=0; j<events->mu_RefittedStandAlone_N; j++) {
			    if(events->muRefittedStandAloneTrackNDtChambersWithValidHits[j]>1){
			      if(events->muRefittedStandAloneTrackGenParticleIndex[j] >= 0){// matched_RSA
				double dR = deltaR(events->muRefittedStandAloneEta[j],events->muRefittedStandAlonePhi[j],events->mcMuonEta[genMuMatched_RSA_index[j]],events->mcMuonPhi[genMuMatched_RSA_index[j]]);
				muRefittedStandAloneTrackGenDR_hist->Fill(dR);
				if(dR<0.5){
				  if(events->mcMuonPt[genMuMatched_RSA_index[j]]>0. && events->muRefittedStandAlonePt[j]>0.){			  
				    double pt_resolution = 1.0*(events->muRefittedStandAlonePt[j] - events->mcMuonPt[genMuMatched_RSA_index[j]])/(events->mcMuonPt[genMuMatched_RSA_index[j]]); 
				    double qOverPt_resolution = 1.0*(1.0*events->muRefittedStandAloneCharge[j]/events->muRefittedStandAlonePt[j] - 1.0*events->mcMuonCharge[genMuMatched_RSA_index[j]]/events->mcMuonPt[genMuMatched_RSA_index[j]])/(1.0*events->mcMuonCharge[genMuMatched_RSA_index[j]]/events->mcMuonPt[genMuMatched_RSA_index[j]]); 
				    muRefittedStandAloneP_hist->Fill(events->muRefittedStandAloneP[j],1.0);
				    muRefittedStandAlonePt_hist->Fill(events->muRefittedStandAlonePt[j],1.0);
				    muRefittedStandAlonePtResolution_hist->Fill(pt_resolution,1.0);
				    muRefittedStandAloneQoverPtResolution_hist->Fill(qOverPt_resolution,1.0);
				  }
				}
			      }
			    }
			  }

			  for (UInt_t j=0; j<events->mu_CosmicTrack_N; j++) {	    
			    if(events->muCosmicTrackNDtChambersWithValidHits[j]>1){
			      if(events->muCosmicTrackGenParticleIndex[j] >= 0){// matched_cosmic
				double dR = deltaR(events->muCosmicTrackEta[j],events->muCosmicTrackPhi[j],events->mcMuonEta[genMuMatched_cosmic_index[j]],events->mcMuonPhi[genMuMatched_cosmic_index[j]]);
				muCosmicTrackGenDR_hist->Fill(dR);
				if(dR<0.5){
				  if(events->mcMuonPt[genMuMatched_cosmic_index[j]]>0. && events->muCosmicTrackPt[j]>0.){			  
				    double pt_resolution = 1.0*(events->muCosmicTrackPt[j] - events->mcMuonPt[genMuMatched_cosmic_index[j]])/(events->mcMuonPt[genMuMatched_cosmic_index[j]]); 
				    double qOverPt_resolution = 1.0*(1.0*events->muCosmicTrackCharge[j]/events->muCosmicTrackPt[j] - 1.0*events->mcMuonCharge[genMuMatched_cosmic_index[j]]/events->mcMuonPt[genMuMatched_cosmic_index[j]])/(1.0*events->mcMuonCharge[genMuMatched_cosmic_index[j]]/events->mcMuonPt[genMuMatched_cosmic_index[j]]); 
				    muCosmicP_hist->Fill(events->muCosmicTrackP[j],1.0);
				    muCosmicPt_hist->Fill(events->muCosmicTrackPt[j],1.0);
				    muCosmicPtResolution_hist->Fill(pt_resolution,1.0);
				    muCosmicQoverPtResolution_hist->Fill(qOverPt_resolution,1.0);
				  }
				}
			      }
			    }
			  }
			  */
			  //cout<<"pass muon pog event selection"<<endl;

			  /*
			  if(events->mu_RefittedStandAlone_N>0 && events->mu_CosmicTrack_N>0){
			    muDisplacedStandAloneNChambersDt_PtResolution_hist->Fill(events->muDisplacedStandAloneTrackNDtChambersWithValidHits[highestPt_index], muDisplacedStandAlone_pt_resolution,1.0);
			    muRefittedStandAloneNChambersDt_PtResolution_hist->Fill(events->muRefittedStandAloneTrackNDtChambersWithValidHits[highestPt_index], muRefittedStandAlone_pt_resolution,1.0);
			    muCosmicNChambersDt_PtResolution_hist->Fill(events->muCosmicTrackNDtChambersWithValidHits[highestPt_index], muCosmic_pt_resolution,1.0);
			    muDisplacedStandAloneNChambersRpc_PtResolution_hist->Fill(events->muDisplacedStandAloneTrackNRpcChambersWithValidHits[highestPt_index], muDisplacedStandAlone_pt_resolution,1.0);
			    muRefittedStandAloneNChambersRpc_PtResolution_hist->Fill(events->muRefittedStandAloneTrackNRpcChambersWithValidHits[highestPt_index], muRefittedStandAlone_pt_resolution,1.0);
			    muCosmicNChambersRpc_PtResolution_hist->Fill(events->muCosmicTrackNRpcChambersWithValidHits[highestPt_index], muCosmic_pt_resolution,1.0);
			  }
			  */

			  mcMuonN_muDisplacedStandAloneN_hist->Fill(good_genMuons,n_passPreselection,1.0);
			  if(genMu0_index!=999){
			    mcMuonPt_muDisplacedStandAlonePt_hist->Fill(events->mcMuonPt[genMu0_index],events->muDisplacedStandAlonePt[highestPt_index],1.0);
			    mcMuonEta_muDisplacedStandAloneEta_hist->Fill(events->mcMuonEta[genMu0_index],events->muDisplacedStandAloneEta[highestPt_index],1.0);
			    mcMuonPhi_muDisplacedStandAlonePhi_hist->Fill(events->mcMuonPhi[genMu0_index],events->muDisplacedStandAlonePhi[highestPt_index],1.0);
			    mcMuonCharge_muDisplacedStandAloneCharge_hist->Fill(events->mcMuonCharge[genMu0_index],events->muDisplacedStandAloneCharge[highestPt_index],1.0);
			  
			    double genMu0Lxy = (events->mcMuonVx[genMu0_index])*(events->mcMuonVx[genMu0_index])+(events->mcMuonVy[genMu0_index])*(events->mcMuonVy[genMu0_index]);
			    genMu0Lxy = TMath::Sqrt(genMu0Lxy);
			    double SAlxy = (events->muDisplacedStandAloneTrackVx[highestPt_index])*(events->muDisplacedStandAloneTrackVx[highestPt_index])+(events->muDisplacedStandAloneTrackVy[highestPt_index])*(events->muDisplacedStandAloneTrackVy[highestPt_index]);
			    mcMuonLxy_muDisplacedStandAloneLxy_hist->Fill(genMu0Lxy,SAlxy,1.0);
			    
			    double genMu0Dxy = -999.;
			    if(events->mcMuonPt[genMu0_index]!=0.){
			      genMu0Dxy = (events->mcMuonVx[genMu0_index]*events->mcMuonPy[genMu0_index] - events->mcMuonVy[genMu0_index]*events->mcMuonPx[genMu0_index])/(events->mcMuonPt[genMu0_index]);
			    }
			    mcMuonDxy_muDisplacedStandAloneDxy_hist->Fill(genMu0Dxy,events->muDisplacedStandAloneTrackDxy[highestPt_index],1.0);
			    
			    double invBeta = -999.;
			    if(events->mcMuonP[genMu0_index]!=0.){
			      invBeta = (events->mcMuonMass[genMu0_index]*events->mcMuonMass[genMu0_index])/(events->mcMuonP[genMu0_index]*events->mcMuonP[genMu0_index])+1;
			      invBeta = TMath::Sqrt(invBeta);
			    }
			    mcMuonInverseBeta_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist->Fill(invBeta,events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[highestPt_index],1.0);
			  }
			  //cout<<"finished 2D genMu0 vs displaced SA histos, 1D MC resolution histos"<<endl;
			  
			  //if(events->muDisplacedStandAloneTrackGenParticleIndex[presel_index[i]] >= 0) {
			  //mcMuonPt_muDisplacedStandAlonePt_hist->Fill(events->mcMuonPt[events->muDisplacedStandAloneTrackGenParticleIndex[presel_index[i]]],events->muDisplacedStandAlonePt[presel_index[i]],1.0);
			  //mcMuonEta_muDisplacedStandAloneEta_hist->Fill(events->mcMuonEta[events->muDisplacedStandAloneTrackGenParticleIndex[presel_index[i]]],events->muDisplacedStandAloneEta[presel_index[i]],1.0);
			  //mcMuonPhi_muDisplacedStandAlonePhi_hist->Fill(events->mcMuonPhi[events->muDisplacedStandAloneTrackGenParticleIndex[presel_index[i]]],events->muDisplacedStandAlonePhi[presel_index[i]],1.0);
			  //}			
			  
			}//end of if MC
			
			//other displaced SA muon hists can go here
			
			//bool refitted = false;
			//muDisplacedStandAloneTrackDistanceStations_hist->Fill(distanceBetweenStations(events, a, refitted) ,1.0);
			//muDisplacedStandAloneTrackDistanceStations_Pt_hist->Fill(distanceBetweenStations(events, a, refitted), events->muDisplacedStandAlonePt[highestPt_index],1.0);

		      }//end of highest pt index not 999			
		    }//end of if at least 1 passes preselection		      		      

		    //cout<<"starting upper and lower"<<endl;
		    if(upper_index!=999 && lower_index!=999){
		      ABCDevent = events; 
		      ABCDtree->Fill();   
		      
		      /*
		      //cout<<"starting to fill simple tree"<<endl;
		      runNumber = events->run;
		      evtNumber = events->id;
		      lumiSection = events->lb;
		      bxNumber = events->bx;

		      //cout<<"starting to fill stopped particles in simple tree"<<endl;
		      if(stopped_index!=999){
			mcStoppedParticleId = events->mcStoppedParticleId[stopped_index];
			mcStoppedParticleMass = events->mcStoppedParticleMass[stopped_index];
			mcStoppedParticleCharge = events->mcStoppedParticleCharge[stopped_index];
			mcStoppedParticleX = events->mcStoppedParticleX[stopped_index]/10.0;
			mcStoppedParticleY = events->mcStoppedParticleY[stopped_index]/10.0;
			mcStoppedParticleZ = events->mcStoppedParticleZ[stopped_index]/10.0;
			mcStoppedParticleR = events->mcStoppedParticleR[stopped_index]/10.0;
			mcStoppedParticleEta = eta(events->mcStoppedParticleX[stopped_index],events->mcStoppedParticleY[stopped_index],
						  events->mcStoppedParticleZ[stopped_index],events->mcStoppedParticleTime[stopped_index]);
			mcStoppedParticlePhi = events->mcStoppedParticlePhi[stopped_index];
			mcStoppedParticleTime = events->mcStoppedParticleTime[stopped_index];
		      }

		      //cout<<"starting to fill mcMuons in simple tree"<<endl;
		      if(good_genMuons==2 || good_genMuons==4){
			//cout<<"2 or 4 good gen muons"<<endl;
			if(good_genPosMuons==2){
			  //cout<<"2 or good gen Positive muons"<<endl;
			  if(genPosMuUpper_index!=999){
			    //cout<<"good gen Positive Upper muon"<<endl;
			    mcMuonId_upper = events->mcMuonId[genPosMuUpper_index];
			    mcMuonMass_upper = events->mcMuonMass[genPosMuUpper_index];
			    mcMuonCharge_upper = events->mcMuonCharge[genPosMuUpper_index];
			    mcMuonPx_upper = events->mcMuonPx[genPosMuUpper_index];
			    mcMuonPy_upper = events->mcMuonPy[genPosMuUpper_index];
			    mcMuonPz_upper = events->mcMuonPz[genPosMuUpper_index];
			    mcMuonPt_upper = events->mcMuonPt[genPosMuUpper_index];
			    mcMuonP_upper = events->mcMuonP[genPosMuUpper_index];
			    mcMuonPhi_upper = events->mcMuonPhi[genPosMuUpper_index];
			    mcMuonEta_upper = events->mcMuonEta[genPosMuUpper_index];
			    mcMuonVx_upper = events->mcMuonVx[genPosMuUpper_index];
			    mcMuonVy_upper = events->mcMuonVy[genPosMuUpper_index];
			    mcMuonVz_upper = events->mcMuonVz[genPosMuUpper_index];
			    mcMuonStatus_upper = events->mcMuonStatus[genPosMuUpper_index];
			    mcMuonMotherId_upper = events->mcMuonMotherId[genPosMuUpper_index];
			  }
			  if(genPosMuLower_index!=999){
			    //cout<<"good gen Positive Lower muon"<<endl;
			    mcMuonId_lower = events->mcMuonId[genPosMuLower_index];
			    mcMuonMass_lower = events->mcMuonMass[genPosMuLower_index];
			    mcMuonCharge_lower = events->mcMuonCharge[genPosMuLower_index];
			    mcMuonPx_lower = events->mcMuonPx[genPosMuLower_index];
			    mcMuonPy_lower = events->mcMuonPy[genPosMuLower_index];
			    mcMuonPz_lower = events->mcMuonPz[genPosMuLower_index];
			    mcMuonPt_lower = events->mcMuonPt[genPosMuLower_index];
			    mcMuonP_lower = events->mcMuonP[genPosMuLower_index];
			    mcMuonPhi_lower = events->mcMuonPhi[genPosMuLower_index];
			    mcMuonEta_lower = events->mcMuonEta[genPosMuLower_index];
			    mcMuonVx_lower = events->mcMuonVx[genPosMuLower_index];
			    mcMuonVy_lower = events->mcMuonVy[genPosMuLower_index];
			    mcMuonVz_lower = events->mcMuonVz[genPosMuLower_index];
			    mcMuonStatus_lower = events->mcMuonStatus[genPosMuLower_index];
			    mcMuonMotherId_lower = events->mcMuonMotherId[genPosMuLower_index];
			  }
			}
			if(good_genNegMuons==2){
			  //cout<<"2 or good gen Negative muons"<<endl;
			  if(genNegMuUpper_index!=999){
			    //cout<<"good gen Negative Upper muon"<<endl;
			    mcMuonId_upper = events->mcMuonId[genNegMuUpper_index];
			    mcMuonMass_upper = events->mcMuonMass[genNegMuUpper_index];
			    mcMuonCharge_upper = events->mcMuonCharge[genNegMuUpper_index];
			    mcMuonPx_upper = events->mcMuonPx[genNegMuUpper_index];
			    mcMuonPy_upper = events->mcMuonPy[genNegMuUpper_index];
			    mcMuonPz_upper = events->mcMuonPz[genNegMuUpper_index];
			    mcMuonPt_upper = events->mcMuonPt[genNegMuUpper_index];
			    mcMuonP_upper = events->mcMuonP[genNegMuUpper_index];
			    mcMuonPhi_upper = events->mcMuonPhi[genNegMuUpper_index];
			    mcMuonEta_upper = events->mcMuonEta[genNegMuUpper_index];
			    mcMuonVx_upper = events->mcMuonVx[genNegMuUpper_index];
			    mcMuonVy_upper = events->mcMuonVy[genNegMuUpper_index];
			    mcMuonVz_upper = events->mcMuonVz[genNegMuUpper_index];
			    mcMuonStatus_upper = events->mcMuonStatus[genNegMuUpper_index];
			    mcMuonMotherId_upper = events->mcMuonMotherId[genNegMuUpper_index];
			  }
			  if(genNegMuLower_index!=999){
			    //cout<<"good gen Negative Lower muon"<<endl;
			    mcMuonId_lower = events->mcMuonId[genNegMuLower_index];
			    mcMuonMass_lower = events->mcMuonMass[genNegMuLower_index];
			    mcMuonCharge_lower = events->mcMuonCharge[genNegMuLower_index];
			    mcMuonPx_lower = events->mcMuonPx[genNegMuLower_index];
			    mcMuonPy_lower = events->mcMuonPy[genNegMuLower_index];
			    mcMuonPz_lower = events->mcMuonPz[genNegMuLower_index];
			    mcMuonPt_lower = events->mcMuonPt[genNegMuLower_index];
			    mcMuonP_lower = events->mcMuonP[genNegMuLower_index];
			    mcMuonPhi_lower = events->mcMuonPhi[genNegMuLower_index];
			    mcMuonEta_lower = events->mcMuonEta[genNegMuLower_index];
			    mcMuonVx_lower = events->mcMuonVx[genNegMuLower_index];
			    mcMuonVy_lower = events->mcMuonVy[genNegMuLower_index];
			    mcMuonVz_lower = events->mcMuonVz[genNegMuLower_index];
			    mcMuonStatus_lower = events->mcMuonStatus[genNegMuLower_index];
			    mcMuonMotherId_lower = events->mcMuonMotherId[genNegMuLower_index];
			  }
			}
		      }//end of if 2 good gen muons

		      //cout<<"starting to fill L1 and HLT bools in simple tree"<<endl;
		      l1SingleMu6NoBptx = events->l1SingleMu6NoBptx[2];
		      hltL2Mu10NoVertexNoBptx3BX = events->hltL2Mu10NoVertexNoBptx3BX;
		      hltL2Mu20NoVertexNoBptx3BX = events->hltL2Mu20NoVertexNoBptx3BX;
		      hltL2Mu30NoVertexNoBptx3BX = events->hltL2Mu30NoVertexNoBptx3BX;
		      hltL2Mu10NoVertexNoBptx3BXNoHalo = events->hltL2Mu10NoVertexNoBptx3BXNoHalo;
		      hltL2Mu20NoVertexNoBptx3BXNoHalo = events->hltL2Mu20NoVertexNoBptx3BXNoHalo;
		      hltL2Mu30NoVertexNoBptx3BXNoHalo = events->hltL2Mu30NoVertexNoBptx3BXNoHalo;
		      hltL2Mu20NoVertex2ChaNoBptx3BXNoHalo = events->hltL2Mu20NoVertex2ChaNoBptx3BXNoHalo;
		      hltL2Mu30NoVertex2ChaNoBptx3BXNoHalo = events->hltL2Mu30NoVertex2ChaNoBptx3BXNoHalo;

		      //cout<<"starting to fill reco DSAs in simple tree"<<endl;
		      DTSegment_N = events->DTSegment_N;
		      CSCSegment_N = events->cscSeg_N;
		      nDSA = events->mu_DisplacedStandAlone_N;
		      muDisplacedStandAloneP_upper = events->muDisplacedStandAloneP[upper_index];
		      muDisplacedStandAlonePt_upper = events->muDisplacedStandAlonePt[upper_index];
		      muDisplacedStandAlonePx_upper = events->muDisplacedStandAlonePx[upper_index];
		      muDisplacedStandAlonePy_upper = events->muDisplacedStandAlonePy[upper_index];
		      muDisplacedStandAlonePz_upper = events->muDisplacedStandAlonePz[upper_index];
		      muDisplacedStandAloneEta_upper = events->muDisplacedStandAloneEta[upper_index];
		      muDisplacedStandAlonePhi_upper = events->muDisplacedStandAlonePhi[upper_index];
		      muDisplacedStandAloneCharge_upper = events->muDisplacedStandAloneCharge[upper_index];
		      muDisplacedStandAloneNormalizedChi2_upper = events->muDisplacedStandAloneTrackNormalizedChi2[upper_index];
		      muDisplacedStandAloneDxy_upper = events->muDisplacedStandAloneTrackDxy[upper_index];
		      muDisplacedStandAloneDz_upper = events->muDisplacedStandAloneTrackDz[upper_index];
		      muDisplacedStandAloneNHitsMuon_upper = events->muDisplacedStandAloneTrackNValidMuonHits[upper_index];
		      muDisplacedStandAloneNHitsCsc_upper = events->muDisplacedStandAloneTrackNValidCscHits[upper_index];
		      muDisplacedStandAloneNHitsDt_upper = events->muDisplacedStandAloneTrackNValidDtHits[upper_index];
		      muDisplacedStandAloneNHitsRpc_upper = events->muDisplacedStandAloneTrackNValidRpcHits[upper_index];
		      muDisplacedStandAloneNRpcDof_upper = events->muDisplacedStandAloneTrackRpcHitZ.at(upper_index).size();
		      muDisplacedStandAloneNStations_upper = events->muDisplacedStandAloneTrackNStationsWithValidHits[upper_index];
		      muDisplacedStandAloneNChambersCsc_upper = events->muDisplacedStandAloneTrackNCscChambersWithValidHits[upper_index];
		      muDisplacedStandAloneNChambersDt_upper = events->muDisplacedStandAloneTrackNDtChambersWithValidHits[upper_index];
		      muDisplacedStandAloneNChambersRpc_upper = events->muDisplacedStandAloneTrackNRpcChambersWithValidHits[upper_index];
		      muDisplacedStandAloneDtTofNDof_upper = events->muDisplacedStandAloneTrackDtTofNDof[upper_index];
		      muDisplacedStandAloneDtTofInverseBeta_upper = events->muDisplacedStandAloneTrackDtTofInverseBeta[upper_index];
		      muDisplacedStandAloneDtTofInverseBetaErr_upper = events->muDisplacedStandAloneTrackDtTofInverseBetaErr[upper_index];
		      muDisplacedStandAloneDtTofFreeInverseBeta_upper = events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[upper_index];
		      muDisplacedStandAloneDtTofFreeInverseBetaErr_upper = events->muDisplacedStandAloneTrackDtTofFreeInverseBetaErr[upper_index];
		      muDisplacedStandAloneDtTofTimeAtIpInOut_upper = events->muDisplacedStandAloneTrackDtTofTimeAtIpInOut[upper_index];
		      muDisplacedStandAloneDtTofTimeAtIpInOutErr_upper = events->muDisplacedStandAloneTrackDtTofTimeAtIpInOutErr[upper_index];
		      muDisplacedStandAloneDtTofTimeAtIpOutIn_upper = events->muDisplacedStandAloneTrackDtTofTimeAtIpOutIn[upper_index];
		      muDisplacedStandAloneDtTofTimeAtIpOutInErr_upper = events->muDisplacedStandAloneTrackDtTofTimeAtIpOutInErr[upper_index];
		      muDisplacedStandAloneDtTofDirection_upper = events->muDisplacedStandAloneTrackDtTofDirection[upper_index];
		      muDisplacedStandAloneBxPattern_upper = Rpc_Bx_Pattern(events,upper_index); //for highest pt muon	

		      muDisplacedStandAloneP_lower = events->muDisplacedStandAloneP[lower_index];
		      muDisplacedStandAlonePt_lower = events->muDisplacedStandAlonePt[lower_index];
		      muDisplacedStandAlonePx_lower = events->muDisplacedStandAlonePx[lower_index];
		      muDisplacedStandAlonePy_lower = events->muDisplacedStandAlonePy[lower_index];
		      muDisplacedStandAlonePz_lower = events->muDisplacedStandAlonePz[lower_index];
		      muDisplacedStandAloneEta_lower = events->muDisplacedStandAloneEta[lower_index];
		      muDisplacedStandAlonePhi_lower = events->muDisplacedStandAlonePhi[lower_index];
		      muDisplacedStandAloneCharge_lower = events->muDisplacedStandAloneCharge[lower_index];
		      muDisplacedStandAloneNormalizedChi2_lower = events->muDisplacedStandAloneTrackNormalizedChi2[lower_index];
		      muDisplacedStandAloneDxy_lower = events->muDisplacedStandAloneTrackDxy[lower_index];
		      muDisplacedStandAloneDz_lower = events->muDisplacedStandAloneTrackDz[lower_index];
		      muDisplacedStandAloneNHitsMuon_lower = events->muDisplacedStandAloneTrackNValidMuonHits[lower_index];
		      muDisplacedStandAloneNHitsCsc_lower = events->muDisplacedStandAloneTrackNValidCscHits[lower_index];
		      muDisplacedStandAloneNHitsDt_lower = events->muDisplacedStandAloneTrackNValidDtHits[lower_index];
		      muDisplacedStandAloneNHitsRpc_lower = events->muDisplacedStandAloneTrackNValidRpcHits[lower_index];
		      muDisplacedStandAloneNRpcDof_lower = events->muDisplacedStandAloneTrackRpcHitZ.at(lower_index).size();
		      muDisplacedStandAloneNStations_lower = events->muDisplacedStandAloneTrackNStationsWithValidHits[lower_index];
		      muDisplacedStandAloneNChambersCsc_lower = events->muDisplacedStandAloneTrackNCscChambersWithValidHits[lower_index];
		      muDisplacedStandAloneNChambersDt_lower = events->muDisplacedStandAloneTrackNDtChambersWithValidHits[lower_index];
		      muDisplacedStandAloneNChambersRpc_lower = events->muDisplacedStandAloneTrackNRpcChambersWithValidHits[lower_index];
		      muDisplacedStandAloneDtTofNDof_lower = events->muDisplacedStandAloneTrackDtTofNDof[lower_index];
		      muDisplacedStandAloneDtTofInverseBeta_lower = events->muDisplacedStandAloneTrackDtTofInverseBeta[lower_index];
		      muDisplacedStandAloneDtTofInverseBetaErr_lower = events->muDisplacedStandAloneTrackDtTofInverseBetaErr[lower_index];
		      muDisplacedStandAloneDtTofFreeInverseBeta_lower = events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[lower_index];
		      muDisplacedStandAloneDtTofFreeInverseBetaErr_lower = events->muDisplacedStandAloneTrackDtTofFreeInverseBetaErr[lower_index];
		      muDisplacedStandAloneDtTofTimeAtIpInOut_lower = events->muDisplacedStandAloneTrackDtTofTimeAtIpInOut[lower_index];
		      muDisplacedStandAloneDtTofTimeAtIpInOutErr_lower = events->muDisplacedStandAloneTrackDtTofTimeAtIpInOutErr[lower_index];
		      muDisplacedStandAloneDtTofTimeAtIpOutIn_lower = events->muDisplacedStandAloneTrackDtTofTimeAtIpOutIn[lower_index];
		      muDisplacedStandAloneDtTofTimeAtIpOutInErr_lower = events->muDisplacedStandAloneTrackDtTofTimeAtIpOutInErr[lower_index];
		      muDisplacedStandAloneDtTofDirection_lower = events->muDisplacedStandAloneTrackDtTofDirection[lower_index];
		      muDisplacedStandAloneBxPattern_lower = Rpc_Bx_Pattern(events,lower_index); //for highest pt muon	
		      
		      simpleTree->Fill();   
		      */

		      //if(doPrintout){
		      //printout_setup(events,is_data);
			//printout_gen(events);
			//printout_DSA(events);
			//printout_SA(events);
			//printout_RSA(events);
			//printout_cosmic(events);
			//printout_L2(events);
			//printout_L1(events);
		      //}
		      
		      //if(events->muDisplacedStandAloneTrackDtTofTimeAtIpInOut[upper_index]<-30){
		      //if(events->muDisplacedStandAloneTrackDtTofTimeAtIpInOut[lower_index]<15){
		      //cout<<"starting upper and lower hists"<<endl;

		      double highestP = events->muDisplacedStandAloneP[upper_index];
		      if (events->muDisplacedStandAloneP[lower_index]> events->muDisplacedStandAloneP[upper_index]) highestP=events->muDisplacedStandAloneP[lower_index];
		      double differenceP = TMath::Abs(events->muDisplacedStandAloneP[upper_index]-events->muDisplacedStandAloneP[lower_index]);
		      double aveP = 1.0*(events->muDisplacedStandAloneP[upper_index] + events->muDisplacedStandAloneP[lower_index])/2;

		      double highestPt = events->muDisplacedStandAlonePt[upper_index];
		      if (events->muDisplacedStandAlonePt[lower_index]> events->muDisplacedStandAlonePt[upper_index]) highestPt=events->muDisplacedStandAlonePt[lower_index];
		      double differencePt = TMath::Abs(events->muDisplacedStandAlonePt[upper_index]-events->muDisplacedStandAlonePt[lower_index]);
		      double avePt = 1.0*(events->muDisplacedStandAlonePt[upper_index] + events->muDisplacedStandAlonePt[lower_index])/2;
		      double productPt = 1.0*(events->muDisplacedStandAlonePt[upper_index]*events->muDisplacedStandAlonePt[lower_index]);
		      //cout<<"upper pt is: "<<events->muDisplacedStandAlonePt[upper_index]<<", lower pt is: "<<events->muDisplacedStandAlonePt[lower_index]<<", ave pt is: "<<avePt<<endl;
		      double upper_timeErrorDiff = events->muDisplacedStandAloneTrackDtTofTimeAtIpInOutErr[upper_index]-events->muDisplacedStandAloneTrackDtTofTimeAtIpOutInErr[upper_index];
		      double lower_timeErrorDiff = events->muDisplacedStandAloneTrackDtTofTimeAtIpInOutErr[lower_index]-events->muDisplacedStandAloneTrackDtTofTimeAtIpOutInErr[lower_index];
		      double upperLower_timeErrorDiff = upper_timeErrorDiff - lower_timeErrorDiff;

		      Ave_muDisplacedStandAlonePt_hist->Fill(avePt,1.0);
		      Diff_muDisplacedStandAlonePt_hist->Fill(differencePt,1.0);

		      //upper, 1D
		      Upper_muDisplacedStandAlonePt_hist->Fill(events->muDisplacedStandAlonePt[upper_index],1.0);
		      Upper_muDisplacedStandAloneEta_hist->Fill(events->muDisplacedStandAloneEta[upper_index],1.0);
		      Upper_muDisplacedStandAlonePhi_hist->Fill(events->muDisplacedStandAlonePhi[upper_index],1.0);
		      Upper_muDisplacedStandAloneTrackCharge_hist->Fill(events->muDisplacedStandAloneCharge[upper_index],1.0);
		      Upper_muDisplacedStandAloneTrackNormalizedChi2_hist->Fill(events->muDisplacedStandAloneTrackNormalizedChi2[upper_index],1.0);
		      Upper_muDisplacedStandAloneTrackDxy_hist->Fill(events->muDisplacedStandAloneTrackDxy[upper_index],1.0);
		      Upper_muDisplacedStandAloneTrackDz_hist->Fill(events->muDisplacedStandAloneTrackDz[upper_index],1.0);
		      Upper_muDisplacedStandAloneTrackNHitsMuon_hist->Fill(events->muDisplacedStandAloneTrackNValidMuonHits[upper_index],1.0);
		      Upper_muDisplacedStandAloneTrackNHitsCsc_hist->Fill(events->muDisplacedStandAloneTrackNValidCscHits[upper_index],1.0);
		      Upper_muDisplacedStandAloneTrackNHitsDt_hist->Fill(events->muDisplacedStandAloneTrackNValidDtHits[upper_index],1.0);
		      Upper_muDisplacedStandAloneTrackNHitsRpc_hist->Fill(events->muDisplacedStandAloneTrackNValidRpcHits[upper_index],1.0);
		      Upper_muDisplacedStandAloneTrackNRpcDof_hist->Fill(events->muDisplacedStandAloneTrackRpcHitZ.at(upper_index).size(),1.0);
		      Upper_muDisplacedStandAloneTrackNStations_hist->Fill(events->muDisplacedStandAloneTrackNStationsWithValidHits[upper_index],1.0);
		      Upper_muDisplacedStandAloneTrackNChambersCsc_hist->Fill(events->muDisplacedStandAloneTrackNCscChambersWithValidHits[upper_index],1.0);
		      Upper_muDisplacedStandAloneTrackNChambersDt_hist->Fill(events->muDisplacedStandAloneTrackNDtChambersWithValidHits[upper_index],1.0);
		      Upper_muDisplacedStandAloneTrackNChambersRpc_hist->Fill(events->muDisplacedStandAloneTrackNRpcChambersWithValidHits[upper_index],1.0);
		      Upper_muDisplacedStandAloneTrackDtTofNDof_hist->Fill(events->muDisplacedStandAloneTrackDtTofNDof[upper_index],1.0);
		      Upper_muDisplacedStandAloneTrackDtTofInverseBeta_hist->Fill(events->muDisplacedStandAloneTrackDtTofInverseBeta[upper_index],1.0);
		      Upper_muDisplacedStandAloneTrackDtTofInverseBetaErr_hist->Fill(events->muDisplacedStandAloneTrackDtTofInverseBetaErr[upper_index],1.0);
		      Upper_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist->Fill(events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[upper_index],1.0);
		      Upper_muDisplacedStandAloneTrackDtTofFreeInverseBetaErr_hist->Fill(events->muDisplacedStandAloneTrackDtTofFreeInverseBetaErr[upper_index],1.0);
		      Upper_muDisplacedStandAloneTrackDtTofTimeAtIpInOut_hist->Fill(events->muDisplacedStandAloneTrackDtTofTimeAtIpInOut[upper_index],1.0);
		      Upper_muDisplacedStandAloneTrackDtTofTimeAtIpOutIn_hist->Fill(events->muDisplacedStandAloneTrackDtTofTimeAtIpOutIn[upper_index],1.0);
		      Upper_muDisplacedStandAloneTrackDtTofTimeAtIpInOutErr_hist->Fill(events->muDisplacedStandAloneTrackDtTofTimeAtIpInOutErr[upper_index],1.0);
		      Upper_muDisplacedStandAloneTrackDtTofTimeAtIpOutInErr_hist->Fill(events->muDisplacedStandAloneTrackDtTofTimeAtIpOutInErr[upper_index],1.0);
		      Upper_muDisplacedStandAloneTrackDtTofErrDiff_hist->Fill(upper_timeErrorDiff,1.0);
		      Upper_muDisplacedStandAloneTrackDtTofDirection_hist->Fill(events->muDisplacedStandAloneTrackDtTofDirection[upper_index],1.0);
		      Upper_muDisplacedStandAloneBxPattern_hist->Fill(Rpc_Bx_Pattern(events,upper_index),1.0);
		      //cout<<"For UPPER index: "<<endl;
		      Upper_muDisplacedStandAloneBxAverage_hist->Fill(Rpc_Bx_Average(events,upper_index),1.0);

		      //upper vs upper, 2D
		      Upper_muDisplacedStandAloneTrackNHitsRpc_Upper_muDisplacedStandAloneTrackNormalizedChi2_hist->Fill(events->muDisplacedStandAloneTrackNValidRpcHits[upper_index],events->muDisplacedStandAloneTrackNormalizedChi2[upper_index],1.0);
		      Upper_muDisplacedStandAloneTrackNHitsRpc_Upper_muDisplacedStandAloneTrackNHitsDt_hist->Fill(events->muDisplacedStandAloneTrackNValidRpcHits[upper_index],events->muDisplacedStandAloneTrackNValidDtHits[upper_index],1.0);
		      Upper_muDisplacedStandAloneBxPattern_Upper_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist->Fill(Rpc_Bx_Pattern(events,upper_index),events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[upper_index],1.0);
		      Upper_muDisplacedStandAloneBxPattern_Upper_muDisplacedStandAloneTrackDtTofNDof_hist->Fill(Rpc_Bx_Pattern(events,upper_index),events->muDisplacedStandAloneTrackDtTofNDof[upper_index],1.0);
		      Upper_muDisplacedStandAloneBxPattern_mudiff_muDisplacedStandAloneTofTimeAtIpInOut_hist->Fill(Rpc_Bx_Pattern(events,upper_index),(events->muDisplacedStandAloneTrackDtTofTimeAtIpInOut[upper_index]-events->muDisplacedStandAloneTrackDtTofTimeAtIpInOut[lower_index]),1.0);
		      Upper_muDisplacedStandAlonePt_Upper_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist->Fill(events->muDisplacedStandAlonePt[upper_index],events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[upper_index],1.0);
		      Upper_muDisplacedStandAloneP_Upper_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist->Fill(events->muDisplacedStandAloneP[upper_index],events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[upper_index],1.0);
		      Upper_muDisplacedStandAlonePt_Upper_muDisplacedStandAloneBxPattern_hist->Fill(events->muDisplacedStandAlonePt[upper_index],Rpc_Bx_Pattern(events,upper_index),1.0);
		      Upper_muDisplacedStandAloneP_Upper_muDisplacedStandAloneBxPattern_hist->Fill(events->muDisplacedStandAloneP[upper_index],Rpc_Bx_Pattern(events,upper_index),1.0);
		      Upper_muDisplacedStandAloneTimeAtIpInOut_Upper_muDisplacedStandAloneFreeInverseBeta_hist->Fill(events->muDisplacedStandAloneTrackDtTofTimeAtIpInOut[upper_index],events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[upper_index],1.0);
		      Upper_muDisplacedStandAloneTimeAtIpInOut_Upper_muDisplacedStandAloneDirection_hist->Fill(events->muDisplacedStandAloneTrackDtTofTimeAtIpInOut[upper_index],events->muDisplacedStandAloneTrackDtTofDirection[upper_index],1.0);
		      Upper_muDisplacedStandAloneFreeInverseBeta_Upper_muDisplacedStandAloneFreeInverseBetaErr_hist->Fill(events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[upper_index],events->muDisplacedStandAloneTrackDtTofFreeInverseBetaErr[upper_index],1.0);

		      Highest_muDisplacedStandAloneP_Upper_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist->Fill(highestP,events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[upper_index],1.0);

		      //upper vs run number, 2D
		      Upper_runNumber_muDisplacedStandAloneDtTofFreeInverseBeta_hist->Fill(events->run,events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[upper_index],1.0);
		      Upper_runNumber_muDisplacedStandAloneDtTofInverseBeta_hist->Fill(events->run,events->muDisplacedStandAloneTrackDtTofInverseBeta[upper_index],1.0);
		      Upper_runNumber_muDisplacedStandAlonePt_hist->Fill(events->run,events->muDisplacedStandAlonePt[upper_index],1.0);		     
		      Upper_runNumber_muDisplacedStandAlonePhi_hist->Fill(events->run,events->muDisplacedStandAlonePhi[upper_index],1.0);		     
		      Upper_runNumber_muDisplacedStandAloneN_hist->Fill(events->run,n_Upper,1.0);
		      Upper_muDisplacedStandAloneEta_Phi_hist->Fill(events->muDisplacedStandAloneEta[upper_index],events->muDisplacedStandAlonePhi[upper_index],1.0);

		      //lower, 1D
		      Lower_muDisplacedStandAlonePt_hist->Fill(events->muDisplacedStandAlonePt[lower_index],1.0);
		      Lower_muDisplacedStandAloneEta_hist->Fill(events->muDisplacedStandAloneEta[lower_index],1.0);
		      Lower_muDisplacedStandAlonePhi_hist->Fill(events->muDisplacedStandAlonePhi[lower_index],1.0);
		      Lower_muDisplacedStandAloneTrackCharge_hist->Fill(events->muDisplacedStandAloneCharge[lower_index],1.0);
		      Lower_muDisplacedStandAloneTrackNormalizedChi2_hist->Fill(events->muDisplacedStandAloneTrackNormalizedChi2[lower_index],1.0);
		      Lower_muDisplacedStandAloneTrackDxy_hist->Fill(events->muDisplacedStandAloneTrackDxy[lower_index],1.0);
		      Lower_muDisplacedStandAloneTrackDz_hist->Fill(events->muDisplacedStandAloneTrackDz[lower_index],1.0);
		      Lower_muDisplacedStandAloneTrackNHitsMuon_hist->Fill(events->muDisplacedStandAloneTrackNValidMuonHits[lower_index],1.0);
		      Lower_muDisplacedStandAloneTrackNHitsCsc_hist->Fill(events->muDisplacedStandAloneTrackNValidCscHits[lower_index],1.0);
		      Lower_muDisplacedStandAloneTrackNHitsDt_hist->Fill(events->muDisplacedStandAloneTrackNValidDtHits[lower_index],1.0);
		      Lower_muDisplacedStandAloneTrackNHitsRpc_hist->Fill(events->muDisplacedStandAloneTrackNValidRpcHits[lower_index],1.0);
		      Lower_muDisplacedStandAloneTrackNRpcDof_hist->Fill(events->muDisplacedStandAloneTrackRpcHitZ.at(lower_index).size(),1.0);
		      Lower_muDisplacedStandAloneTrackNStations_hist->Fill(events->muDisplacedStandAloneTrackNStationsWithValidHits[lower_index],1.0);
		      Lower_muDisplacedStandAloneTrackNChambersCsc_hist->Fill(events->muDisplacedStandAloneTrackNCscChambersWithValidHits[lower_index],1.0);
		      Lower_muDisplacedStandAloneTrackNChambersDt_hist->Fill(events->muDisplacedStandAloneTrackNDtChambersWithValidHits[lower_index],1.0);
		      Lower_muDisplacedStandAloneTrackNChambersRpc_hist->Fill(events->muDisplacedStandAloneTrackNRpcChambersWithValidHits[lower_index],1.0);
		      Lower_muDisplacedStandAloneTrackDtTofNDof_hist->Fill(events->muDisplacedStandAloneTrackDtTofNDof[lower_index],1.0);
		      Lower_muDisplacedStandAloneTrackDtTofInverseBeta_hist->Fill(events->muDisplacedStandAloneTrackDtTofInverseBeta[lower_index],1.0);
		      Lower_muDisplacedStandAloneTrackDtTofInverseBetaErr_hist->Fill(events->muDisplacedStandAloneTrackDtTofInverseBetaErr[lower_index],1.0);
		      Lower_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist->Fill(events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[lower_index],1.0);
		      Lower_muDisplacedStandAloneTrackDtTofFreeInverseBetaErr_hist->Fill(events->muDisplacedStandAloneTrackDtTofFreeInverseBetaErr[lower_index],1.0);
		      Lower_muDisplacedStandAloneTrackDtTofTimeAtIpInOut_hist->Fill(events->muDisplacedStandAloneTrackDtTofTimeAtIpInOut[lower_index],1.0);
		      Lower_muDisplacedStandAloneTrackDtTofTimeAtIpOutIn_hist->Fill(events->muDisplacedStandAloneTrackDtTofTimeAtIpOutIn[lower_index],1.0);
		      Lower_muDisplacedStandAloneTrackDtTofTimeAtIpInOutErr_hist->Fill(events->muDisplacedStandAloneTrackDtTofTimeAtIpInOutErr[lower_index],1.0);
		      Lower_muDisplacedStandAloneTrackDtTofTimeAtIpOutInErr_hist->Fill(events->muDisplacedStandAloneTrackDtTofTimeAtIpOutInErr[lower_index],1.0);
		      Lower_muDisplacedStandAloneTrackDtTofDirection_hist->Fill(events->muDisplacedStandAloneTrackDtTofDirection[lower_index],1.0);
		      Lower_muDisplacedStandAloneTrackDtTofErrDiff_hist->Fill(lower_timeErrorDiff,1.0);
		      Lower_muDisplacedStandAloneBxPattern_hist->Fill(Rpc_Bx_Pattern(events,lower_index),1.0);
		      //cout<<"For LOWER index: "<<endl;
		      Lower_muDisplacedStandAloneBxAverage_hist->Fill(Rpc_Bx_Average(events,lower_index),1.0);

			//lower vs lower, 2D
		      Lower_muDisplacedStandAloneTrackNHitsRpc_Lower_muDisplacedStandAloneTrackNormalizedChi2_hist->Fill(events->muDisplacedStandAloneTrackNValidRpcHits[lower_index],events->muDisplacedStandAloneTrackNormalizedChi2[lower_index],1.0);
		      Lower_muDisplacedStandAloneTrackNHitsRpc_Lower_muDisplacedStandAloneTrackNHitsDt_hist->Fill(events->muDisplacedStandAloneTrackNValidRpcHits[lower_index],events->muDisplacedStandAloneTrackNValidDtHits[lower_index],1.0);
		      Lower_muDisplacedStandAloneBxPattern_Lower_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist->Fill(Rpc_Bx_Pattern(events,lower_index),events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[lower_index],1.0);
		      Lower_muDisplacedStandAlonePt_Lower_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist->Fill(events->muDisplacedStandAlonePt[lower_index],events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[lower_index],1.0);
		      Lower_muDisplacedStandAlonePt_Lower_muDisplacedStandAloneBxPattern_hist->Fill(events->muDisplacedStandAlonePt[lower_index],Rpc_Bx_Pattern(events,lower_index),1.0);
		      Lower_muDisplacedStandAloneP_Lower_muDisplacedStandAloneBxPattern_hist->Fill(events->muDisplacedStandAloneP[lower_index],Rpc_Bx_Pattern(events,lower_index),1.0);
		      Lower_muDisplacedStandAloneTimeAtIpInOut_Lower_muDisplacedStandAloneFreeInverseBeta_hist->Fill(events->muDisplacedStandAloneTrackDtTofTimeAtIpInOut[lower_index],events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[lower_index],1.0);
		      Lower_muDisplacedStandAloneTimeAtIpInOut_Lower_muDisplacedStandAloneDirection_hist->Fill(events->muDisplacedStandAloneTrackDtTofTimeAtIpInOut[lower_index],events->muDisplacedStandAloneTrackDtTofDirection[lower_index],1.0);
		      Lower_muDisplacedStandAloneFreeInverseBeta_Lower_muDisplacedStandAloneFreeInverseBetaErr_hist->Fill(events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[lower_index],events->muDisplacedStandAloneTrackDtTofFreeInverseBetaErr[lower_index],1.0);

		      //lower vs run number, 2D
		      Lower_runNumber_muDisplacedStandAloneDtTofFreeInverseBeta_hist->Fill(events->run,events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[lower_index],1.0);
		      Lower_runNumber_muDisplacedStandAloneDtTofInverseBeta_hist->Fill(events->run,events->muDisplacedStandAloneTrackDtTofInverseBeta[lower_index],1.0);
		      Lower_runNumber_muDisplacedStandAlonePt_hist->Fill(events->run,events->muDisplacedStandAlonePt[lower_index],1.0);		     
		      Lower_runNumber_muDisplacedStandAlonePhi_hist->Fill(events->run,events->muDisplacedStandAlonePhi[lower_index],1.0);		     
		      Lower_runNumber_muDisplacedStandAloneN_hist->Fill(events->run,n_Lower,1.0);
		      Lower_muDisplacedStandAloneEta_Phi_hist->Fill(events->muDisplacedStandAloneEta[lower_index],events->muDisplacedStandAlonePhi[lower_index],1.0);

		      //upper and lower (diff, delta, multiply), 1D
		      Upper_Lower_muDisplacedStandAlone_deltaPhi_hist->Fill(events->muDisplacedStandAlonePhi[upper_index] - events->muDisplacedStandAlonePhi[lower_index],1.0);
		      mudiff_muDisplacedStandAloneTofTimeAtIpInOut_hist->Fill(events->muDisplacedStandAloneTrackDtTofTimeAtIpInOut[upper_index] - events->muDisplacedStandAloneTrackDtTofTimeAtIpInOut[lower_index],1.0);
		      mudiff_muDisplacedStandAloneTofTimeAtIpOutIn_hist->Fill(events->muDisplacedStandAloneTrackDtTofTimeAtIpOutIn[upper_index] - events->muDisplacedStandAloneTrackDtTofTimeAtIpOutIn[lower_index],1.0);
		      mudiff_muDisplacedStandAloneTofFreeInverseBeta_hist->Fill(events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[upper_index] - events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[lower_index],1.0);
		      mudiff_muDisplacedStandAloneTofDirection_hist->Fill(events->muDisplacedStandAloneTrackDtTofDirection[upper_index] - events->muDisplacedStandAloneTrackDtTofDirection[lower_index],1.0);
		      mudiff_muDisplacedStandAloneTrackDtTofErrDiff_hist->Fill(upperLower_timeErrorDiff,1.0);
		      Upper_Lower_muDisplacedStandAlone_chargeMultiply_hist->Fill((events->muDisplacedStandAloneCharge[upper_index])*(events->muDisplacedStandAloneCharge[lower_index]),1.0);
		      Upper_Lower_muDisplacedStandAlone_directionMultiply_hist->Fill((events->muDisplacedStandAloneTrackDtTofDirection[upper_index])*(events->muDisplacedStandAloneTrackDtTofDirection[lower_index]),1.0);
		      Upper_Lower_muDisplacedStandAloneBxAverage_hist->Fill(Rpc_Bx_Average(events,upper_index,lower_index),1.0);
		      mudiff_muDisplacedStandAloneBxAverage_hist->Fill(Rpc_Bx_Average(events,upper_index)-Rpc_Bx_Average(events,lower_index),1.0);

		      //upper vs lower, 2D
		      Upper_Lower_muDisplacedStandAloneTofTimeAtIpInOut_hist->Fill(events->muDisplacedStandAloneTrackDtTofTimeAtIpInOut[upper_index],events->muDisplacedStandAloneTrackDtTofTimeAtIpInOut[lower_index],1.0);
		      Upper_Lower_muDisplacedStandAloneTofTimeAtIpOutIn_hist->Fill(events->muDisplacedStandAloneTrackDtTofTimeAtIpOutIn[upper_index],events->muDisplacedStandAloneTrackDtTofTimeAtIpOutIn[lower_index],1.0);
		      Upper_Lower_muDisplacedStandAloneTrackCharge_hist->Fill((events->muDisplacedStandAloneCharge[upper_index]),(events->muDisplacedStandAloneCharge[lower_index]),1.0);
		      Upper_Lower_muDisplacedStandAloneTrackDtTofDirection_hist->Fill((events->muDisplacedStandAloneTrackDtTofDirection[upper_index]),(events->muDisplacedStandAloneTrackDtTofDirection[lower_index]),1.0);
		      Upper_Lower_muDisplacedStandAlonePt_hist->Fill(events->muDisplacedStandAlonePt[upper_index],events->muDisplacedStandAlonePt[lower_index],1.0);
		      Upper_Lower_muDisplacedStandAloneDtTofFreeInverseBeta_hist->Fill(events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[upper_index],events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[lower_index],1.0);
		      Upper_Lower_muDisplacedStandAloneRpcBxPattern_hist->Fill(Rpc_Bx_Pattern(events,upper_index),Rpc_Bx_Pattern(events,lower_index),1.0);
		      mudiff_muDisplacedStandAloneTofTimeAtIpInOut_muDisplacedStandAloneTofFreeInverseBeta_hist->Fill(events->muDisplacedStandAloneTrackDtTofTimeAtIpInOut[upper_index] - events->muDisplacedStandAloneTrackDtTofTimeAtIpInOut[lower_index],events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[upper_index] - events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[lower_index],1.0);

		      Upper_muDisplacedStandAloneP_mudiff_muDisplacedStandAloneBxAverage_hist->Fill(events->muDisplacedStandAloneP[upper_index],Rpc_Bx_Average(events,upper_index)-Rpc_Bx_Average(events,lower_index),1.0);
		      Lower_muDisplacedStandAloneP_mudiff_muDisplacedStandAloneBxAverage_hist->Fill(events->muDisplacedStandAloneP[lower_index],Rpc_Bx_Average(events,upper_index)-Rpc_Bx_Average(events,lower_index),1.0);


		      //both upper and lower, 1D
		      Both_muDisplacedStandAlonePt_hist->Fill(events->muDisplacedStandAlonePt[upper_index],1.0);
		      Both_muDisplacedStandAloneEta_hist->Fill(events->muDisplacedStandAloneEta[upper_index],1.0);
		      Both_muDisplacedStandAlonePhi_hist->Fill(events->muDisplacedStandAlonePhi[upper_index],1.0);
		      Both_muDisplacedStandAloneTrackCharge_hist->Fill(events->muDisplacedStandAloneCharge[upper_index],1.0);
		      Both_muDisplacedStandAloneTrackNormalizedChi2_hist->Fill(events->muDisplacedStandAloneTrackNormalizedChi2[upper_index],1.0);
		      Both_muDisplacedStandAloneTrackDxy_hist->Fill(events->muDisplacedStandAloneTrackDxy[upper_index],1.0);
		      Both_muDisplacedStandAloneTrackDz_hist->Fill(events->muDisplacedStandAloneTrackDz[upper_index],1.0);
		      Both_muDisplacedStandAloneTrackNHitsMuon_hist->Fill(events->muDisplacedStandAloneTrackNValidMuonHits[upper_index],1.0);
		      Both_muDisplacedStandAloneTrackNHitsCsc_hist->Fill(events->muDisplacedStandAloneTrackNValidCscHits[upper_index],1.0);
		      Both_muDisplacedStandAloneTrackNHitsDt_hist->Fill(events->muDisplacedStandAloneTrackNValidDtHits[upper_index],1.0);
		      Both_muDisplacedStandAloneTrackNHitsRpc_hist->Fill(events->muDisplacedStandAloneTrackNValidRpcHits[upper_index],1.0);
		      Both_muDisplacedStandAloneTrackNRpcDof_hist->Fill(events->muDisplacedStandAloneTrackRpcHitZ.at(upper_index).size(),1.0);
		      Both_muDisplacedStandAloneTrackNStations_hist->Fill(events->muDisplacedStandAloneTrackNStationsWithValidHits[upper_index],1.0);
		      Both_muDisplacedStandAloneTrackNChambersCsc_hist->Fill(events->muDisplacedStandAloneTrackNCscChambersWithValidHits[upper_index],1.0);
		      Both_muDisplacedStandAloneTrackNChambersDt_hist->Fill(events->muDisplacedStandAloneTrackNDtChambersWithValidHits[upper_index],1.0);
		      Both_muDisplacedStandAloneTrackNChambersRpc_hist->Fill(events->muDisplacedStandAloneTrackNRpcChambersWithValidHits[upper_index],1.0);
		      Both_muDisplacedStandAloneTrackDtTofNDof_hist->Fill(events->muDisplacedStandAloneTrackDtTofNDof[upper_index],1.0);
		      Both_muDisplacedStandAloneTrackDtTofInverseBeta_hist->Fill(events->muDisplacedStandAloneTrackDtTofInverseBeta[upper_index],1.0);
		      Both_muDisplacedStandAloneTrackDtTofInverseBetaErr_hist->Fill(events->muDisplacedStandAloneTrackDtTofInverseBetaErr[upper_index],1.0);
		      Both_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist->Fill(events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[upper_index],1.0);
		      Both_muDisplacedStandAloneTrackDtTofFreeInverseBetaErr_hist->Fill(events->muDisplacedStandAloneTrackDtTofFreeInverseBetaErr[upper_index],1.0);
		      Both_muDisplacedStandAloneTrackDtTofTimeAtIpInOut_hist->Fill(events->muDisplacedStandAloneTrackDtTofTimeAtIpInOut[upper_index],1.0);
		      Both_muDisplacedStandAloneTrackDtTofTimeAtIpOutIn_hist->Fill(events->muDisplacedStandAloneTrackDtTofTimeAtIpOutIn[upper_index],1.0);
		      Both_muDisplacedStandAloneTrackDtTofTimeAtIpInOutErr_hist->Fill(events->muDisplacedStandAloneTrackDtTofTimeAtIpInOutErr[upper_index],1.0);
		      Both_muDisplacedStandAloneTrackDtTofTimeAtIpOutInErr_hist->Fill(events->muDisplacedStandAloneTrackDtTofTimeAtIpOutInErr[upper_index],1.0);
		      Both_muDisplacedStandAloneTrackDtTofDirection_hist->Fill(events->muDisplacedStandAloneTrackDtTofDirection[upper_index],1.0);
		      Both_muDisplacedStandAloneTrackDtTofErrDiff_hist->Fill(upper_timeErrorDiff,1.0);
		      Both_muDisplacedStandAloneBxPattern_hist->Fill(Rpc_Bx_Pattern(events,upper_index));
		      Both_muDisplacedStandAloneBxAverage_hist->Fill(Rpc_Bx_Average(events,upper_index));

		      Both_muDisplacedStandAlonePt_hist->Fill(events->muDisplacedStandAlonePt[lower_index],1.0);
		      Both_muDisplacedStandAloneEta_hist->Fill(events->muDisplacedStandAloneEta[lower_index],1.0);
		      Both_muDisplacedStandAlonePhi_hist->Fill(events->muDisplacedStandAlonePhi[lower_index],1.0);
		      Both_muDisplacedStandAloneTrackCharge_hist->Fill(events->muDisplacedStandAloneCharge[lower_index],1.0);
		      Both_muDisplacedStandAloneTrackNormalizedChi2_hist->Fill(events->muDisplacedStandAloneTrackNormalizedChi2[lower_index],1.0);
		      Both_muDisplacedStandAloneTrackDxy_hist->Fill(events->muDisplacedStandAloneTrackDxy[lower_index],1.0);
		      Both_muDisplacedStandAloneTrackDz_hist->Fill(events->muDisplacedStandAloneTrackDz[lower_index],1.0);
		      Both_muDisplacedStandAloneTrackNHitsMuon_hist->Fill(events->muDisplacedStandAloneTrackNValidMuonHits[lower_index],1.0);
		      Both_muDisplacedStandAloneTrackNHitsCsc_hist->Fill(events->muDisplacedStandAloneTrackNValidCscHits[lower_index],1.0);
		      Both_muDisplacedStandAloneTrackNHitsDt_hist->Fill(events->muDisplacedStandAloneTrackNValidDtHits[lower_index],1.0);
		      Both_muDisplacedStandAloneTrackNHitsRpc_hist->Fill(events->muDisplacedStandAloneTrackNValidRpcHits[lower_index],1.0);
		      Both_muDisplacedStandAloneTrackNRpcDof_hist->Fill(events->muDisplacedStandAloneTrackRpcHitZ.at(lower_index).size(),1.0);
		      Both_muDisplacedStandAloneTrackNStations_hist->Fill(events->muDisplacedStandAloneTrackNStationsWithValidHits[lower_index],1.0);
		      Both_muDisplacedStandAloneTrackNChambersCsc_hist->Fill(events->muDisplacedStandAloneTrackNCscChambersWithValidHits[lower_index],1.0);
		      Both_muDisplacedStandAloneTrackNChambersDt_hist->Fill(events->muDisplacedStandAloneTrackNDtChambersWithValidHits[lower_index],1.0);
		      Both_muDisplacedStandAloneTrackNChambersRpc_hist->Fill(events->muDisplacedStandAloneTrackNRpcChambersWithValidHits[lower_index],1.0);
		      Both_muDisplacedStandAloneTrackDtTofNDof_hist->Fill(events->muDisplacedStandAloneTrackDtTofNDof[lower_index],1.0);
		      Both_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist->Fill(events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[lower_index],1.0);
		      Both_muDisplacedStandAloneTrackDtTofFreeInverseBetaErr_hist->Fill(events->muDisplacedStandAloneTrackDtTofFreeInverseBetaErr[lower_index],1.0);
		      Both_muDisplacedStandAloneTrackDtTofTimeAtIpInOut_hist->Fill(events->muDisplacedStandAloneTrackDtTofTimeAtIpInOut[lower_index],1.0);
		      Both_muDisplacedStandAloneTrackDtTofTimeAtIpOutIn_hist->Fill(events->muDisplacedStandAloneTrackDtTofTimeAtIpOutIn[lower_index],1.0);
		      Both_muDisplacedStandAloneTrackDtTofDirection_hist->Fill(events->muDisplacedStandAloneTrackDtTofDirection[lower_index],1.0);
		      Both_muDisplacedStandAloneTrackDtTofTimeAtIpInOutErr_hist->Fill(events->muDisplacedStandAloneTrackDtTofTimeAtIpInOutErr[lower_index],1.0);
		      Both_muDisplacedStandAloneTrackDtTofTimeAtIpOutInErr_hist->Fill(events->muDisplacedStandAloneTrackDtTofTimeAtIpOutInErr[lower_index],1.0);
		      Both_muDisplacedStandAloneTrackDtTofErrDiff_hist->Fill(lower_timeErrorDiff,1.0);
		      Both_muDisplacedStandAloneBxPattern_hist->Fill(Rpc_Bx_Pattern(events,lower_index));
		      Both_muDisplacedStandAloneBxAverage_hist->Fill(Rpc_Bx_Average(events,lower_index));

		      //2D: upper p, mudiff free inverse beta
		      Upper_muDisplacedStandAloneP_mudiff_muDisplacedStandAloneTofFreeInverseBeta_hist->Fill(events->muDisplacedStandAlonePt[upper_index],(events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[upper_index] - events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[lower_index]),1.0);
		      //cout<<"finished Both histos"<<endl;

		      //abcd with upper hemisphere inverse beta and average pt (upper and lower)

		      //fraction of events greater than pt cut value with RPC BX pattern cut
		      for(int a=0; a<=50; a++){
			double cutValue=a*5.;
			if(Rpc_Bx_Pattern(events,lower_index)==0){
			  if(events->muDisplacedStandAloneP[lower_index]>cutValue) nDregionLowerP[a]++;
			  else nCregionLowerP[a]++;
			}
			else{
			  if(events->muDisplacedStandAloneP[lower_index]>cutValue) nBregionLowerP[a]++;
			  else nAregionLowerP[a]++;
			}
		      }



		      //fraction of events greater than pt cut value
		      for(int a=0; a<=50; a++){
			double cutValue=a*5.;
			if(events->muDisplacedStandAloneP[upper_index]>cutValue){
			  nUpperPLargerThanCut[a]++;
			  if(events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[upper_index] > abcdInvBetaCutValue_) nDregionUpperP[a]++;
			  else nBregionUpperP[a]++;
			}
			else{
			  if(events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[upper_index] > abcdInvBetaCutValue_) nCregionUpperP[a]++;
			  else nAregionUpperP[a]++;
			}
			if(highestP>cutValue) {
			  nHighestPLargerThanCut[a]++;
			  if(events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[upper_index] > abcdInvBetaCutValue_) nDregionHighestP[a]++;
			  else nBregionHighestP[a]++;
			}
			else{
			  if(events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[upper_index] > abcdInvBetaCutValue_) nCregionHighestP[a]++;
			  else nAregionHighestP[a]++;
			}

			if(differenceP>cutValue){
			  nDifferencePLargerThanCut[a]++;
			  if(events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[upper_index] > abcdInvBetaCutValue_) nDregionDifferenceP[a]++;
			  else nBregionDifferenceP[a]++;
			}
			else{
			  if(events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[upper_index] > abcdInvBetaCutValue_) nCregionDifferenceP[a]++;
			  else nAregionDifferenceP[a]++;
			}

			if(aveP>cutValue){
			  nAvePLargerThanCut[a]++;
			  if(events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[upper_index] > abcdInvBetaCutValue_) nDregionAveP[a]++;
			  else nBregionAveP[a]++;
			}
			else{
			  if(events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[upper_index] > abcdInvBetaCutValue_) nCregionAveP[a]++;
			  else nAregionAveP[a]++;
			}


			if(events->muDisplacedStandAlonePt[upper_index]>cutValue){
			  nUpperPtLargerThanCut[a]++;
			  if(events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[upper_index] > abcdInvBetaCutValue_) nDregionUpperPt[a]++;
			  else nBregionUpperPt[a]++;
			}
			else{
			  if(events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[upper_index] > abcdInvBetaCutValue_) nCregionUpperPt[a]++;
			  else nAregionUpperPt[a]++;
			}
			
			if(highestPt>cutValue) {
			  nHighestPtLargerThanCut[a]++;
			  if(events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[upper_index] > abcdInvBetaCutValue_) nDregionHighestPt[a]++;
			  else nBregionHighestPt[a]++;
			}
			else{
			  if(events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[upper_index] > abcdInvBetaCutValue_) nCregionHighestPt[a]++;
			  else nAregionHighestPt[a]++;
			}

			if(differencePt>cutValue){
			  nDifferencePtLargerThanCut[a]++;
			  if(events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[upper_index] > abcdInvBetaCutValue_) nDregionDifferencePt[a]++;
			  else nBregionDifferencePt[a]++;
			}
			else{
			  if(events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[upper_index] > abcdInvBetaCutValue_) nCregionDifferencePt[a]++;
			  else nAregionDifferencePt[a]++;
			}

			if(avePt>cutValue){
			  nAvePtLargerThanCut[a]++;
			  if(events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[upper_index] > abcdInvBetaCutValue_) nDregionAvePt[a]++;
			  else nBregionAvePt[a]++;
			}
			else{
			  if(events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[upper_index] > abcdInvBetaCutValue_) nCregionAvePt[a]++;
			  else nAregionAvePt[a]++;
			}
			
			if(productPt>cutValue){
			  nProductPtLargerThanCut[a]++;
			  if(events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[upper_index] > abcdInvBetaCutValue_) nDregionProductPt[a]++;
			  else nBregionProductPt[a]++;
			}
			else{
			  if(events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[upper_index] > abcdInvBetaCutValue_) nCregionProductPt[a]++;
			  else nAregionProductPt[a]++;
			}			
		      }//end of loop over 25 entries

		      //fraction of events greater than inverse beta cut value
		      for(int a=0; a<=10; a++){
			double cutValue=a*0.1;
			double cutValueTimeInOut=a*5-20;
			double cutValueDifferenceInverseBeta=a*0.2-2;
			double cutValueDifferenceTimeInOut=a*4-40;
			if(events->muDisplacedStandAloneP[upper_index]>abcdPtCutValue_){
			  if(events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[upper_index] > cutValue) nDregionInverseBeta[a]++;
			  else nBregionInverseBeta[a]++;
			  if(events->muDisplacedStandAloneTrackDtTofTimeAtIpInOut[upper_index] > cutValueTimeInOut) nDregionTimeInOut[a]++;
			  else nBregionTimeInOut[a]++;
			  if((events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[upper_index]-events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[lower_index]) > cutValueDifferenceInverseBeta) nDregionDifferenceInverseBeta[a]++;
			  else nBregionDifferenceInverseBeta[a]++;
			  if((events->muDisplacedStandAloneTrackDtTofTimeAtIpInOut[upper_index]-events->muDisplacedStandAloneTrackDtTofTimeAtIpInOut[lower_index]) > cutValueDifferenceTimeInOut) nDregionDifferenceTimeInOut[a]++;
			  else nBregionDifferenceTimeInOut[a]++;

			}
			else{
			  if(events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[upper_index] > cutValue) nCregionInverseBeta[a]++;
			  else nAregionInverseBeta[a]++;
			  if(events->muDisplacedStandAloneTrackDtTofTimeAtIpInOut[upper_index] > cutValueTimeInOut) nCregionTimeInOut[a]++;
			  else nAregionTimeInOut[a]++;
			  if((events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[upper_index]-events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[lower_index]) > cutValueDifferenceInverseBeta) nCregionDifferenceInverseBeta[a]++;
			  else nAregionDifferenceInverseBeta[a]++;
			  if((events->muDisplacedStandAloneTrackDtTofTimeAtIpInOut[upper_index]-events->muDisplacedStandAloneTrackDtTofTimeAtIpInOut[lower_index]) > cutValueDifferenceTimeInOut) nCregionDifferenceTimeInOut[a]++;
			  else nAregionDifferenceTimeInOut[a]++;

			}
		      }

		      
		      //highestP regular ABCD
		      if(highestP > abcdPtCutValue_){
			if(events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[upper_index] > abcdInvBetaCutValue_) nDregionHighestP_++;
			else nBregionHighestP_++;
		      }
		      else{
			if(events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[upper_index] > abcdInvBetaCutValue_) nCregionHighestP_++;
			else nAregionHighestP_++;
		      }
		      
		      
		      //RPC BX pattern ABCD
		      //if(Rpc_Bx_Pattern(events,lower_index)==0 || Rpc_Bx_Pattern(events,lower_index)==1){
		      //if(Rpc_Bx_Pattern(events,lower_index)==0){
		      if((Rpc_Bx_Average(events,upper_index)-Rpc_Bx_Average(events,lower_index))>abcdInvBetaCutValue_){
			if(events->muDisplacedStandAloneP[lower_index]>abcdPtCutValue_){
			  nDregionRpc_++;
			  regionD_muDisplacedStandAloneP_hist->Fill(events->muDisplacedStandAloneP[lower_index],1.0);					    
			  regionD_muDisplacedStandAloneBxPattern_hist->Fill(Rpc_Bx_Pattern(events,lower_index)); //for highest pt muon	
			  /*
			  if(doPrintout){
			    printout_setup(events,is_data);
			    printout_gen(events);
			    printout_DSA(events);
			    printout_SA(events);
			    printout_RSA(events);
			    printout_cosmic(events);
			    printout_L2(events);
			    printout_L1(events);
			  }
			  */
			}
			else{
			  //cout<<"p is: "<<events->muDisplacedStandAloneP[lower_index]<<", delta ave rpc bx is: "<<Rpc_Bx_Average(events,upper_index)-Rpc_Bx_Average(events,lower_index)<<endl;
			  nCregionRpc_++;
			  regionC_muDisplacedStandAloneTrackBxPattern_hist->Fill(Rpc_Bx_Pattern(events,lower_index),1.0);
			  if(events->muDisplacedStandAloneP[lower_index] > acPtCutValue_)  nC2region++;
			  else nC1region++;			    
			}
		      }
		      else{
			if(events->muDisplacedStandAloneP[lower_index]>abcdPtCutValue_){
			  nBregionRpc_++;
			  regionB_muDisplacedStandAloneP_hist->Fill(events->muDisplacedStandAloneP[lower_index],1.0);
			  //if(Rpc_Bx_Pattern(events,lower_index)==1) nB1region++;
			  //else nB2region++;
			}
			else{
			  nAregionRpc_++;
			  if(events->muDisplacedStandAloneP[lower_index] > acPtCutValue_)  nA2region++;
			  else nA1region++;
			  //if(Rpc_Bx_Pattern(events,lower_index)==1) nA1region++;
			  //else nA2region++;			  
			}
		      }
		      

		      //abcd with free inverse beta and upper p
		      if(events->muDisplacedStandAloneP[upper_index] > abcdPtCutValue_){
			if(events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[upper_index] > abcdInvBetaCutValue_){
			//if(0.95*events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[upper_index] > abcdInvBetaCutValue_){ //systematic uncertainty on free inverse beta between MC and data
			//if(events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[upper_index]-0.05 > abcdInvBetaCutValue_){ //systematic uncertainty on free inverse beta between MC and data
			//if((events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[upper_index]-events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[lower_index]) > abcdInvBetaCutValue_){
			  nDregion++;
			 
			  /*
			  regionD_muDisplacedStandAlone_N_hist->Fill(events->mu_DisplacedStandAlone_N,1.0);
			  regionD_muDisplacedStandAloneP_hist->Fill(events->muDisplacedStandAloneP[upper_index],1.0);					    
			  regionD_muDisplacedStandAlonePt_hist->Fill(events->muDisplacedStandAlonePt[upper_index],1.0);					    
			  regionD_muDisplacedStandAloneEta_hist->Fill(events->muDisplacedStandAloneEta[upper_index],1.0);					   
			  regionD_muDisplacedStandAlonePhi_hist->Fill(events->muDisplacedStandAlonePhi[upper_index],1.0);					   
			  regionD_muDisplacedStandAloneCharge_hist->Fill(events->muDisplacedStandAloneCharge[upper_index],1.0);				    
			  regionD_muDisplacedStandAloneTrackNormalizedChi2_hist->Fill(events->muDisplacedStandAloneTrackNormalizedChi2[upper_index],1.0);	
			  regionD_muDisplacedStandAloneTrackDxy_hist->Fill(events->muDisplacedStandAloneTrackDxy[upper_index],1.0);			
			  regionD_muDisplacedStandAloneTrackDz_hist->Fill(events->muDisplacedStandAloneTrackDz[upper_index],1.0);				   
			  regionD_muDisplacedStandAloneTrackNHitsMuon_hist->Fill(events->muDisplacedStandAloneTrackNValidMuonHits[upper_index],1.0);	
			  regionD_muDisplacedStandAloneTrackNHitsCsc_hist->Fill(events->muDisplacedStandAloneTrackNValidCscHits[upper_index],1.0);	
			  regionD_muDisplacedStandAloneTrackNHitsDt_hist->Fill(events->muDisplacedStandAloneTrackNValidDtHits[upper_index],1.0);		
			  regionD_muDisplacedStandAloneTrackNHitsRpc_hist->Fill(events->muDisplacedStandAloneTrackNValidRpcHits[upper_index],1.0);	
			  regionD_muDisplacedStandAloneTrackNRpcDof_hist->Fill(events->muDisplacedStandAloneTrackRpcHitZ.at(upper_index).size(),1.0);	
			  regionD_muDisplacedStandAloneTrackNStations_hist->Fill(events->muDisplacedStandAloneTrackNStationsWithValidHits[upper_index],1.0);	
			  regionD_muDisplacedStandAloneTrackNChambersCsc_hist->Fill(events->muDisplacedStandAloneTrackNCscChambersWithValidHits[upper_index],1.0);
			  regionD_muDisplacedStandAloneTrackNChambersDt_hist->Fill(events->muDisplacedStandAloneTrackNDtChambersWithValidHits[upper_index],1.0);  
			  regionD_muDisplacedStandAloneTrackNChambersRpc_hist->Fill(events->muDisplacedStandAloneTrackNRpcChambersWithValidHits[upper_index],1.0);
			  regionD_muDisplacedStandAloneTrackDtTofNDof_hist->Fill(events->muDisplacedStandAloneTrackDtTofNDof[upper_index],1.0);
			  regionD_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist->Fill(events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[upper_index],1.0);  
			  regionD_muDisplacedStandAloneTrackDtTofFreeInverseBetaErr_hist->Fill(events->muDisplacedStandAloneTrackDtTofFreeInverseBetaErr[upper_index],1.0);
			  regionD_muDisplacedStandAloneTrackDtTofTimeAtIpInOut_hist->Fill(events->muDisplacedStandAloneTrackDtTofTimeAtIpInOut[upper_index],1.0);	    
			  regionD_muDisplacedStandAloneTrackDtTofTimeAtIpInOutErr_hist->Fill(events->muDisplacedStandAloneTrackDtTofTimeAtIpInOutErr[upper_index],1.0);
			  regionD_muDisplacedStandAloneBxPattern_hist->Fill(Rpc_Bx_Pattern(events,upper_index)); //for highest pt muon	
			  regionD_CSCSegment_N_hist->Fill(events->cscSeg_N,1.0);
			  */

			  if(doPrintout){
			    //if(events->mu_DisplacedStandAlone_N>2){
			    //printout_setup(events,is_data);
			    /*
			    printout_gen(events);
			    printout_DSA(events);
			    printout_SA(events);
			    printout_RSA(events);
			    printout_cosmic(events);
			    printout_L2(events);
			    printout_L1(events);
			    */
			    //}
			  }
			}//end of D region
			else{
			  nBregion++;
			  //regionAB_Upper_muDisplacedStandAloneP_Upper_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist->Fill(events->muDisplacedStandAloneP[upper_index],events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[upper_index],1.0);
			  //regionB_muDisplacedStandAloneP_hist->Fill(events->muDisplacedStandAloneP[upper_index],1.0);

			  if(events->muDisplacedStandAloneP[upper_index] > bPtCutValue_){
			    //if(events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[upper_index] > abInvBetaCutValue_) nB2region++;
			    //else nB1region++;			    
			  }//end of B1 and B2 regions
			  else{
			    //if(events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[upper_index] > abInvBetaCutValue_) nB4region++;
			    //else nB3region++;
			  }//end of B3 and B4 regions
			}//end of B region
		      }//end of B and D region

		      else{
			if(events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[upper_index] > abcdInvBetaCutValue_){
			//if((events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[upper_index]-events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[lower_index]) > abcdInvBetaCutValue_){
			  nCregion++;
			  //regionAC_Upper_muDisplacedStandAloneP_Upper_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist->Fill(events->muDisplacedStandAloneP[upper_index],events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[upper_index],1.0);
			  //regionC_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist->Fill(events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[upper_index],1.0);

			  if(events->muDisplacedStandAloneP[upper_index] > acPtCutValue_){
			    //if(events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[upper_index] > cInvBetaCutValue_) nC2region++;
			    //else nC1region++;			    
			  }//end of C1 and C2 regions
			  else{
			    //if(events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[upper_index] > cInvBetaCutValue_) nC4region++;
			    //else nC3region++;
			  }//end of C3 and C4 regions
			}//end of C region
			else{
			  nAregion++;
			  //regionAB_Upper_muDisplacedStandAloneP_Upper_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist->Fill(events->muDisplacedStandAloneP[upper_index],events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[upper_index],1.0);
			  //regionAC_Upper_muDisplacedStandAloneP_Upper_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist->Fill(events->muDisplacedStandAloneP[upper_index],events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[upper_index],1.0);

			  if(events->muDisplacedStandAloneP[upper_index] > acPtCutValue_){
			    //if(events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[upper_index] > abInvBetaCutValue_) nA2region++;
			    //else nA1region++;			    
			  }//end of A1 and A2 regions
			  else{
			    //if(events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[upper_index] > abInvBetaCutValue_) nA4region++;
			    //else nA3region++;
			  }//end of A3 and A4 regions

			}//end of A region
		      }//end of A and C region

		      //abcd with free inverse beta and direction, and pt
		      if(events->muDisplacedStandAlonePt[upper_index] > abcdPtCutValue_){
			if(events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[upper_index] > abcdInvBetaCutValue_ && events->muDisplacedStandAloneTrackDtTofDirection[upper_index]==1) nDregionDir++;
			else if(events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[upper_index] <= abcdInvBetaCutValue_ && events->muDisplacedStandAloneTrackDtTofDirection[upper_index]==-1) nBregionDir++;
		      }
		      else{
			if(events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[upper_index] > abcdInvBetaCutValue_ && events->muDisplacedStandAloneTrackDtTofDirection[upper_index]==1) nCregionDir++;
			else if(events->muDisplacedStandAloneTrackDtTofFreeInverseBeta[upper_index] <= abcdInvBetaCutValue_ && events->muDisplacedStandAloneTrackDtTofDirection[upper_index]==-1) nAregionDir++;
		      }

		      //a'b': pt cut on lower muon
		      if(events->muDisplacedStandAlonePt[lower_index] > abcdPtCutValue_) nBprimeRegion++;
		      else nAprimeRegion++;
		      
		      

		      //2D gen vs reco: both muons
		      if(!is_data){
			if(good_genMuons==2||good_genMuons==4){
			  if(events->muDisplacedStandAloneP[upper_index]!=0. && events->muDisplacedStandAloneP[lower_index]!=0.){
			    double SAangle = TMath::ACos(( (events->muDisplacedStandAlonePx[upper_index])*(events->muDisplacedStandAlonePx[lower_index]) + (events->muDisplacedStandAlonePy[upper_index])*(events->muDisplacedStandAlonePy[lower_index]) + (events->muDisplacedStandAlonePz[upper_index])*(events->muDisplacedStandAlonePz[lower_index]))/((events->muDisplacedStandAloneP[upper_index])*(events->muDisplacedStandAloneP[lower_index])));
			    if(good_genPosMuons==2) mcMuon_muDisplacedStandAlone_3Dangle_hist->Fill(anglePos,SAangle, 1.0);
			    else if(good_genNegMuons==2) mcMuon_muDisplacedStandAlone_3Dangle_hist->Fill(angleNeg,SAangle, 1.0);
			  }
			  double GenMuDeltaPhi = -999.;
			  if(good_genPosMuons==2) GenMuDeltaPhi = events->mcMuonPhi[genPosMuUpper_index] - events->mcMuonPhi[genPosMuLower_index];
			  else if(good_genNegMuons==2) GenMuDeltaPhi = events->mcMuonPhi[genNegMuUpper_index] - events->mcMuonPhi[genNegMuLower_index];
			  double SADeltaPhi = events->muDisplacedStandAlonePhi[upper_index] - events->muDisplacedStandAlonePhi[lower_index];
			  mcMuon_muDisplacedStandAlone_deltaPhi_hist->Fill(GenMuDeltaPhi,SADeltaPhi,1.0);
			}
		      }

		      //cout<<"finished upper and lower DSA histos"<<endl;

		      //}//end of select few cosmics with weird times
		    }//end of plot upper and lower
		    
		    //}
		  }//end of pass trigger
		}//end of if not doTriggerTurnOn
		//} //end doSACut
	    }//end of genMuonMatched cut
	  } //end of at least one SA
	}//end of status1muon
	//}//end of decay in tracker cut
      }//end of cavern cut
    }//end of bx_cut
  }//end of loop over entries
  
  //cout<<"end of loop over entries"<<endl;

  //set bin labels and normalize BxPattern hists
  const int nbins = muDisplacedStandAloneBxPattern_hist->GetNbinsX();
  string BxPatternLabel[] = {"BXs==0","BXs>0, constant","BXs>=0, increasing","BXs>=0, decreasing","BXs>=0, strange","BXs<0, constant","BXs<=0, increasing","BXs<=0, decreasing","BXs<=0, strange"};
  for (int x=0; x<nbins; x++) {
    muDisplacedStandAloneBxPattern_hist->GetXaxis()->SetBinLabel(x+1,BxPatternLabel[x].c_str());
    Upper_muDisplacedStandAloneBxPattern_hist->GetXaxis()->SetBinLabel(x+1,BxPatternLabel[x].c_str());
    Lower_muDisplacedStandAloneBxPattern_hist->GetXaxis()->SetBinLabel(x+1,BxPatternLabel[x].c_str());
    Both_muDisplacedStandAloneBxPattern_hist->GetXaxis()->SetBinLabel(x+1,BxPatternLabel[x].c_str());
    Upper_Lower_muDisplacedStandAloneRpcBxPattern_hist->GetXaxis()->SetBinLabel(x+1,BxPatternLabel[x].c_str());
    Upper_Lower_muDisplacedStandAloneRpcBxPattern_hist->GetYaxis()->SetBinLabel(x+1,BxPatternLabel[x].c_str());
    Upper_muDisplacedStandAlonePt_Upper_muDisplacedStandAloneBxPattern_hist->GetYaxis()->SetBinLabel(x+1,BxPatternLabel[x].c_str());
    Upper_muDisplacedStandAloneP_Upper_muDisplacedStandAloneBxPattern_hist->GetYaxis()->SetBinLabel(x+1,BxPatternLabel[x].c_str());
    Lower_muDisplacedStandAlonePt_Lower_muDisplacedStandAloneBxPattern_hist->GetYaxis()->SetBinLabel(x+1,BxPatternLabel[x].c_str());
    Lower_muDisplacedStandAloneP_Lower_muDisplacedStandAloneBxPattern_hist->GetYaxis()->SetBinLabel(x+1,BxPatternLabel[x].c_str());
    regionC_muDisplacedStandAloneTrackBxPattern_hist->GetXaxis()->SetBinLabel(x+1,BxPatternLabel[x].c_str());
  }

  //print out cut flow
  if(!is_data){
    cout<<endl;

    cout<<"out of those stopped IN THE DETECTOR:"<<endl;
    cout<<"percentage of stopped particles in tracker is: "<<1.*tracker_count_/detector_count_*100.<<endl;
    cout<<"percentage of stopped particles in EB is: "<<1.*eb_count_/detector_count_*100.<<endl;
    cout<<"percentage of stopped particles in EE is: "<<1.*ee_count_/detector_count_*100.<<endl;
    cout<<"percentage of stopped particles in HB is: "<<1.*hb_count_/detector_count_*100.<<endl;
    cout<<"percentage of stopped particles in HE is: "<<1.*he_count_/detector_count_*100.<<endl;
    cout<<"percentage of stopped particles in MB is: "<<1.*mb_count_/detector_count_*100.<<endl;
    cout<<"percentage of stopped particles in ME is: "<<1.*me_count_/detector_count_*100.<<endl;
    cout<<"percentage of stopped particles in other parts of the detector is: "<<1.*other_detector_count_/detector_count_*100.<<endl;
    
    cout<<endl;
    cout<<"out of ALL those stopped:"<<endl;
    cout<<"percentage of stopped particles in cavern walls is: "<<1.*cavern_count_/pass_bx_cut*100.<<endl;
    cout<<"percentage of stopped particles in tracker is: "<<1.*tracker_count_/pass_bx_cut*100.<<endl;
    cout<<"percentage of stopped particles in EB is: "<<1.*eb_count_/pass_bx_cut*100.<<endl;
    cout<<"percentage of stopped particles in EE is: "<<1.*ee_count_/pass_bx_cut*100.<<endl;
    cout<<"percentage of stopped particles in HB is: "<<1.*hb_count_/pass_bx_cut*100.<<endl;
    cout<<"percentage of stopped particles in HE is: "<<1.*he_count_/pass_bx_cut*100.<<endl;
    cout<<"percentage of stopped particles in MB is: "<<1.*mb_count_/pass_bx_cut*100.<<endl;
    cout<<"percentage of stopped particles in ME is: "<<1.*me_count_/pass_bx_cut*100.<<endl;
    cout<<"percentage of stopped particles in other parts of the detector is: "<<1.*other_detector_count_/pass_bx_cut*100.<<endl;

    cout<<endl;
    cout<<"out of ALL those stopped:"<<endl;
    cout<<"number of stopped particles in cavern walls is: "<<cavern_count_<<endl;
    cout<<"number of stopped particles in tracker is: "<<tracker_count_<<endl;
    cout<<"number of stopped particles in EB is: "<<eb_count_<<endl;
    cout<<"number of stopped particles in EE is: "<<ee_count_<<endl;
    cout<<"number of stopped particles in HB is: "<<hb_count_<<endl;
    cout<<"number of stopped particles in HE is: "<<he_count_<<endl;
    cout<<"number of stopped particles in MB is: "<<mb_count_<<endl;
    cout<<"number of stopped particles in ME is: "<<me_count_<<endl;
    cout<<"number of stopped particles in other parts of the detector is: "<<other_detector_count_<<endl;
    cout<<"number of stopped particles in all parts of the detector (not cavern walls) is: "<<detector_count_<<endl;

    cout<<endl;
    cout<<"out of ALL those stopped:"<<endl;
    cout<<"number of events passing preselection and stopped particles in cavern walls is: "<<cavern_AccCount_<<endl;
    cout<<"number of events passing preselection and stopped particles in tracker is: "<<tracker_AccCount_<<endl;
    cout<<"number of events passing preselection and stopped particles in EB is: "<<eb_AccCount_<<endl;
    cout<<"number of events passing preselection and stopped particles in EE is: "<<ee_AccCount_<<endl;
    cout<<"number of events passing preselection and stopped particles in HB is: "<<hb_AccCount_<<endl;
    cout<<"number of events passing preselection and stopped particles in HE is: "<<he_AccCount_<<endl;
    cout<<"number of events passing preselection and stopped particles in MB is: "<<mb_AccCount_<<endl;
    cout<<"number of events passing preselection and stopped particles in ME is: "<<me_AccCount_<<endl;
    cout<<"number of events passing preselection and stopped particles in other parts of the detector is: "<<other_detector_AccCount_<<endl;
  }

  cout<<endl;
  cout<<"total sum of event weights is: "<<total_count_<<endl;

  if(doBxCut && file_dataset_!="Zmum") cout<<"number of events passing bx cut is: "<<pass_bx_cut<<endl;
  if(doCavCut && !is_data) cout<<"number of events passing cavern cut is: "<<pass_cavern_cut<<endl;

  if(file_dataset_ == "stop") {
    cout<<"number of events passing number of tops cut is: "<<pass_Ntops_cut<<endl;
    cout<<"number of events passing number of stops cut is: "<<pass_Nstops_cut<<endl;
    cout<<"number of events passing W from top cut is: "<<pass_WFromTop_cut<<endl;
  }
  if(file_dataset_ == "glui") cout<<"number of events passing number of gluinos cut is: "<<pass_Ngluinos_cut<<endl;
  if(file_dataset_ == "mcha") {
  }
  if(file_dataset_ == "ppst" || file_dataset_ == "gmst" ){
  }

  if(!is_data){
    cout<<"number of events passing muon cut is: "<<pass_muon_cut<<endl;
    cout<<"number of events passing status1 muon cut is: "<<pass_status1muon_cut<<endl;
    if(file_dataset_ != "glui") cout<<"number of events passing status1 muon from W (generator muon) cut is: "<<pass_generatorMuon_cut<<endl;
  }


  if(file_dataset_ == "glui"){
    cout<<"number of events passing status1 muon from W cut is: "<<pass_status1muonFromW_cut<<endl;
    cout<<"number of events passing status1 muon from Tau cut is: "<<pass_status1muonFromTau_cut<<endl;
    cout<<"number of events passing status1 muon from Muon cut is: "<<pass_status1muonFromMuon_cut<<endl;
    cout<<"number of events passing status1 muon from bottom baryon cut is: "<<pass_status1muonFromBbaryon_cut<<endl;
    cout<<"number of events passing status1 muon from charmed baryon cut is: "<<pass_status1muonFromCbaryon_cut<<endl;
    cout<<"number of events passing status1 muon from strange baryon cut is: "<<pass_status1muonFromSbaryon_cut<<endl;
    cout<<"number of events passing status1 muon from bottom meson cut is: "<<pass_status1muonFromBmeson_cut<<endl;
    cout<<"number of events passing status1 muon from charmed meson cut is: "<<pass_status1muonFromCmeson_cut<<endl;
    cout<<"number of events passing status1 muon from JPsi cut is: "<<pass_status1muonFromJPsi_cut<<endl;
    cout<<"number of events passing status1 muon from light meson cut is: "<<pass_status1muonFromLightMeson_cut<<endl;
  }

  cout<<endl;
  if(doSACut)                                     cout<<"number of events passing standalone muon cut is: "<<pass_standaloneMuon_cut<<endl;
  if(!is_data && doGenMuMatchedCut)               cout<<"number of events passing gen muon match cut is: "<<pass_genMuonMatched_cut<<endl;
  //if(doTriggerCut && file_dataset_!="Zmum")       cout<<"number of events passing 10 GeV trigger cut is: "<<pass_10trigger_cut<<endl;
  if(doTriggerCut && file_dataset_!="Zmum")       cout<<"number of events passing trigger cut is: "<<pass_trigger_cut<<endl;
  if(doNdsaCut)                                     cout<<"number of events passing n DSA tracks<"<<PreNdsaCutValue_<<" cut is: "<<pass_PreNdsa_cut<<endl;
  if(doPtCut)                                     cout<<"number of events passing pt[0]>"<<PrePtCutValue_<<" cut is: "<<pass_Prept_cut<<endl;
  if(doChaCut)                                    cout<<"number of events passing >"<<PreChaCutValue_<<" DT/CSC chambers cut is: "<<pass_Precha_cut<<endl;
  if(doEtaCut)                                    cout<<"number of events passing |eta[0]|<"<<PreEtaCutValue_<<" cut is: "<<pass_Preeta_cut<<endl;
  if(doRpcCut)                                    cout<<"number of events passing >"<<PreRpcCutValue_<<" RPC hit cut is: "<<pass_PreRPC_cut<<endl;
  if(doDtHitsCut)                                 cout<<"number of events passing >"<<PreDtHitsCutValue_<<" DT hits cut is: "<<pass_PreDtHits_cut<<endl;
  if(doInvBetaErrCut)                             cout<<"number of events passing <"<<PreInvBetaErrCutValue_<<" Free inverse beta error cut is: "<<pass_PreInvBetaErr_cut<<endl;
  if(doCscHitsCut)                                cout<<"number of events passing =="<<PreCscHitsCutValue_<<" CSC hits cut is: "<<pass_PreCscHits_cut<<endl;

  cout<<endl;
  if(doUpperCut)                                  cout<<"number of events passing upper hemisphere cut is: "<<pass_Upper_cut<<endl;
  if(doPtCut)                                     cout<<"number of events passing pt[0]>"<<PtCutValue_<<" cut is: "<<pass_pt_cut<<endl;
  if(doChaCut)                                    cout<<"number of events passing >"<<ChaCutValue_<<" DT/CSC chambers cut is: "<<pass_cha_cut<<endl;
  if(doEtaCut)                                    cout<<"number of events passing |eta[0]|<"<<EtaCutValue_<<" cut is: "<<pass_eta_cut<<endl;
  if(doRpcCut)                                    cout<<"number of events passing >"<<RpcCutValue_<<" RPC hit cut is: "<<pass_RPC_cut<<endl;
  if(doDtHitsCut)                                 cout<<"number of events passing >"<<DtHitsCutValue_<<" DT hits cut is: "<<pass_DtHits_cut<<endl;
  if(doCscHitsCut)                                cout<<"number of events passing =="<<CscHitsCutValue_<<" CSC hits cut is: "<<pass_CscHits_cut<<endl;
  if(!doCosEnrich && doOppEtaCut)            cout<<"number of events passing OppEta >"<<OppEtaCutValue_<<" cut is: "<<pass_OppEta_cut<<endl;
  if(doCosEnrich && doOppEtaCut)             cout<<"number of events passing OppEta <"<<OppEtaCutValue_<<" cut is: "<<pass_OppEta_cut<<endl;
  if(!doCosEnrich && doOppPhiCut)            cout<<"number of events passing OppPhi >"<<OppPhiCutValue_<<" cut is: "<<pass_OppPhi_cut<<endl;
  if(doCosEnrich && doOppPhiCut)             cout<<"number of events passing OppPhi <"<<OppPhiCutValue_<<" cut is: "<<pass_OppPhi_cut<<endl;
  if(doRpcBxCut)                                  cout<<"number of events passing at RPC bx pattern cut is: "<<pass_Rpc_Bx_cut<<endl;
  if(!doCosEnrich && doTimeInOutCut)         cout<<"number of events passing TimeInOut >"<<TimeInOutCutValue_<<" cut is: "<<pass_TimeInOut_cut<<endl;
  if(doCosEnrich && doTimeInOutCut)          cout<<"number of events passing TimeInOut <"<<TimeInOutCutValue_<<" cut is: "<<pass_TimeInOut_cut<<endl;
  if(!doCosEnrich && doTimeInOutErrCut)         cout<<"number of events passing TimeInOutErr <"<<TimeInOutErrCutValue_<<" cut is: "<<pass_TimeInOutErr_cut<<endl;
  if(doCosEnrich && doTimeInOutErrCut)          cout<<"number of events passing TimeInOutErr <"<<TimeInOutErrCutValue_<<" cut is: "<<pass_TimeInOutErr_cut<<endl;
  if(!doCosEnrich && doTofDirCut)         cout<<"number of events passing TofDir cut is: "<<pass_TofDir_cut<<endl;
  if(doCosEnrich && doTofDirCut)          cout<<"number of events passing TofDir cut is: "<<pass_TofDir_cut<<endl;
  if(!doCosEnrich && doDtInvBetaCut)         cout<<"number of events passing Dt inverse beta >"<<DtInvBetaCutValue_<<" cut is: "<<pass_DtInvBeta_cut<<endl;
  if(doCosEnrich && doDtInvBetaCut)          cout<<"number of events passing Dt inverse beta <"<<DtInvBetaCutValue_<<" cut is: "<<pass_DtInvBeta_cut<<endl;
  if(doCosEnrich && doDxyCut)          cout<<"number of events passing Dxy <"<<DxyCutValue_<<" cut is: "<<pass_Dxy_cut<<endl;

  cout<<endl;
  if(doSACut)                                     cout<<"number of events passing at least two SA muons cut is: "<<pass_SA_2_cut<<endl;
  if(doSACut)                                     cout<<"number of events passing upper and lower cut is: "<<pass_UpperAndLower_cut<<endl;
  //if(doSACut)                                     cout<<"number of events passing upper only cut is: "<<pass_UpperOnly_cut<<endl;
  //if(doSACut)                                     cout<<"number of events passing lower only cut is: "<<pass_LowerOnly_cut<<endl;
  if(doPtCut)                                     cout<<"number of events passing pt of 2 muons cut is: "<<pass_pt_2_cut<<endl;
  if(doPtCut)                                     cout<<"number of events passing pt of 2 muons take 2 cut is: "<<pass_UpperAndLower_pt30_cut<<endl;
  if(doChaCut)                                    cout<<"number of events passing >"<<ChaCutValue_<<" DT/CSC chambers for 2 muons cut is: "<<pass_cha_2_cut<<endl;
  if(doEtaCut)                                    cout<<"number of events passing eta<"<<EtaCutValue_<<" for 2 muons cut is: "<<pass_eta_2_cut<<endl;
  if(doRpcCut)                                    cout<<"number of events passing >"<<RpcCutValue_<<" RPC hit for 2 muons cut is: "<<pass_RPC_2_cut<<endl;
  if(doDtHitsCut)                                 cout<<"number of events passing >"<<DtHitsCutValue_<<" DT hits cut for 2 muons is: "<<pass_DtHits_2_cut<<endl;
  if(doCosEnrich && doOppEtaCut)             cout<<"number of events passing OppEta <"<<OppEtaCutValue_<<" cut is: "<<pass_OppEta_2_cut<<endl;
  if(doCosEnrich && doOppPhiCut)             cout<<"number of events passing OppPhi <"<<OppPhiCutValue_<<" cut is: "<<pass_OppPhi_2_cut<<endl;
  if(doRpcBxCut)                                  cout<<"number of events passing at RPC bx pattern cut for 2 muons cut is: "<<pass_Rpc_Bx_2_cut<<endl;
  if(!doCosEnrich && doTimeInOutCut)         cout<<"number of events passing TimeInOut >"<<TimeInOutCutValue_<<" cut for 2 muons is: "<<pass_TimeInOut_2_cut<<endl;
  if(doCosEnrich && doTimeInOutCut)          cout<<"number of events passing TimeInOut <"<<TimeInOutCutValue_<<" cut for 2 muons is: "<<pass_TimeInOut_2_cut<<endl;
  if(!doCosEnrich && doTimeInOutErrCut)         cout<<"number of events passing TimeInOutErr <"<<TimeInOutErrCutValue_<<" cut for 2 muons is: "<<pass_TimeInOutErr_2_cut<<endl;
  if(doCosEnrich && doTimeInOutErrCut)          cout<<"number of events passing TimeInOutErr <"<<TimeInOutErrCutValue_<<" cut for 2 muons is: "<<pass_TimeInOutErr_2_cut<<endl;
  if(!doCosEnrich && doDeltaTimeInOutCut)         cout<<"number of events passing DeltaTimeInOut >"<<DeltaTimeInOutCutValue_<<" cut for 2 muons is: "<<pass_DeltaTimeInOut_2_cut<<endl;
  if(doCosEnrich && doDeltaTimeInOutCut)          cout<<"number of events passing DeltaTimeInOut <"<<DeltaTimeInOutCutValue_<<" cut for 2 muons is: "<<pass_DeltaTimeInOut_2_cut<<endl;
  if(!doCosEnrich && doDeltaDtInvBetaCut)         cout<<"number of events passing DeltaDtInvBeta >"<<DeltaDtInvBetaCutValue_<<" cut for 2 muons is: "<<pass_DeltaDtInvBeta_2_cut<<endl;
  if(doCosEnrich && doDeltaDtInvBetaCut)          cout<<"number of events passing DeltaDtInvBeta <"<<DeltaDtInvBetaCutValue_<<" cut for 2 muons is: "<<pass_DeltaDtInvBeta_2_cut<<endl;
  if(!doCosEnrich && doChargeCut)         cout<<"number of events passing Charge cut for 2 muons is: "<<pass_charge_2_cut<<endl;
  if(doCosEnrich && doChargeCut)          cout<<"number of events passing Charge cut for 2 muons is: "<<pass_charge_2_cut<<endl;
  if(!doCosEnrich && doTofDirCut)         cout<<"number of events passing TofDir cut for 2 muons is: "<<pass_TofDir_2_cut<<endl;
  if(doCosEnrich && doTofDirCut)          cout<<"number of events passing TofDir cut for 2 muons is: "<<pass_TofDir_2_cut<<endl;
  if(!doCosEnrich && doDtInvBetaCut)         cout<<"number of events passing Dt inverse beta >"<<DtInvBetaCutValue_<<" cut for 2 muons is: "<<pass_DtInvBeta_2_cut<<endl;
  if(doCosEnrich && doDtInvBetaCut)          cout<<"number of events passing Dt inverse beta <"<<DtInvBetaCutValue_<<" cut for 2 muons is: "<<pass_DtInvBeta_2_cut<<endl;


  cout<<endl;
  /*
  cout<<"abcd regions defined by inverse beta cut of "<<abcdInvBetaCutValue_<<" and upper P cut of "<<abcdPtCutValue_<<endl;
  cout<<"number of events in A region is: "<<nAregion<<" +/- "<<TMath::Sqrt(nAregion)<<endl;
  cout<<"number of events in B region is: "<<nBregion<<" +/- "<<TMath::Sqrt(nBregion)<<endl;
  cout<<"number of events in C region is: "<<nCregion<<" +/- "<<TMath::Sqrt(nCregion)<<endl;
  cout<<"number of events in D region is: "<<nDregion<<" +/- "<<TMath::Sqrt(nDregion)<<endl;
  cout<<"B*C/A is: "<<1.0*nBregion*nCregion/nAregion<<" +/- "<<endl<<endl;
  */

  cout<<"abcd regions defined by delta RPC BX average cut of "<<abcdInvBetaCutValue_<<" and upper P cut of "<<abcdPtCutValue_<<endl;
  //cout<<"abcd regions defined by RPC BX pattern cut and upper P cut of "<<abcdPtCutValue_<<endl;
  cout<<"number of events in A region is: "<<nAregionRpc_<<" +/- "<<TMath::Sqrt(nAregionRpc_)<<endl;
  cout<<"number of events in B region is: "<<nBregionRpc_<<" +/- "<<TMath::Sqrt(nBregionRpc_)<<endl;
  cout<<"number of events in C region is: "<<nCregionRpc_<<" +/- "<<TMath::Sqrt(nCregionRpc_)<<endl;
  cout<<"number of events in D region is: "<<nDregionRpc_<<" +/- "<<TMath::Sqrt(nDregionRpc_)<<endl;
  cout<<"B*C/A is: "<<1.0*nBregionRpc_*nCregionRpc_/nAregionRpc_<<" +/- "<<endl<<endl;

  /*
  cout<<"abcd regions defined by inverse beta cut of "<<abcdInvBetaCutValue_<<", TOF Direction cut, and pt cut of "<<abcdPtCutValue_<<endl;
  cout<<"number of events in A region is: "<<nAregionDir<<" +/- "<<TMath::Sqrt(nAregionDir)<<endl;
  cout<<"number of events in B region is: "<<nBregionDir<<" +/- "<<TMath::Sqrt(nBregionDir)<<endl;
  cout<<"number of events in C region is: "<<nCregionDir<<" +/- "<<TMath::Sqrt(nCregionDir)<<endl;
  cout<<"number of events in D region is: "<<nDregionDir<<" +/- "<<TMath::Sqrt(nDregionDir)<<endl;
  cout<<"B*C/A is: "<<1.0*nBregionDir*nCregionDir/nAregionDir<<" +/- "<<endl<<endl;

  cout<<"a'b' regions defined by pt cut of "<<abcdPtCutValue_<<endl;
  cout<<"number of events in A' region is: "<<nAprimeRegion<<" +/- "<<TMath::Sqrt(nAprimeRegion)<<endl;
  cout<<"number of events in B' region is: "<<nBprimeRegion<<" +/- "<<TMath::Sqrt(nBprimeRegion)<<endl;
  cout<<"Aprime*B/A is: "<<1.0*nAprimeRegion*nBregion/nAregion<<" +/- "<<endl;
  */

  /*
  cout<<"1,2,3,4 regions defined by inverse beta cut of "<<abInvBetaCutValue_<<", "<<cInvBetaCutValue_<<", and upper P cut of "<<acPtCutValue_<<", "<<bPtCutValue_<<endl;

  cout<<"number of events in A1+A2 region is: "<<nA1region+nA2region<<" +/- "<<TMath::Sqrt(nA1region+nA2region)<<endl;
  cout<<"number of events in B region is: "<<nBregion<<" +/- "<<TMath::Sqrt(nBregion)<<endl;
  cout<<"number of events in C1+C2 region is: "<<nC1region+nC2region<<" +/- "<<TMath::Sqrt(nC1region+nC2region)<<endl;
  cout<<"number of events in D region is: "<<nDregion<<" +/- "<<TMath::Sqrt(nDregion)<<endl;
  cout<<"B*(C1+C2)/(A1+A2) is: "<<1.0*nBregion*(nC1region+nC2region)/(nA1region+nA2region)<<" +/- "<<endl<<endl;

  cout<<"number of events in A3+A4 region is: "<<nA3region+nA4region<<" +/- "<<TMath::Sqrt(nA3region+nA4region)<<endl;
  cout<<"number of events in B region is: "<<nBregion<<" +/- "<<TMath::Sqrt(nBregion)<<endl;
  cout<<"number of events in C3+C4 region is: "<<nC3region+nC4region<<" +/- "<<TMath::Sqrt(nC3region+nC4region)<<endl;
  cout<<"number of events in D region is: "<<nDregion<<" +/- "<<TMath::Sqrt(nDregion)<<endl;
  cout<<"B*(C3+C4)/(A3+A4) is: "<<1.0*nBregion*(nC3region+nC4region)/(nA3region+nA4region)<<" +/- "<<endl<<endl;

  cout<<"number of events in A1+A3 region is: "<<nA1region+nA3region<<" +/- "<<TMath::Sqrt(nA1region+nA3region)<<endl;
  cout<<"number of events in B1+B3 region is: "<<nB1region+nB3region<<" +/- "<<TMath::Sqrt(nB1region+nB3region)<<endl;
  cout<<"number of events in C region is: "<<nCregion<<" +/- "<<TMath::Sqrt(nCregion)<<endl;
  cout<<"number of events in D region is: "<<nDregion<<" +/- "<<TMath::Sqrt(nDregion)<<endl;
  cout<<"(B1+B3)*C/(A1+A3) is: "<<1.0*(nB1region+nB3region)*nCregion/(nA1region+nA3region)<<" +/- "<<endl<<endl;

  cout<<"number of events in A2+A4 region is: "<<nA2region+nA4region<<" +/- "<<TMath::Sqrt(nA2region+nA4region)<<endl;
  cout<<"number of events in B2+B4 region is: "<<nB2region+nB4region<<" +/- "<<TMath::Sqrt(nB2region+nB4region)<<endl;
  cout<<"number of events in C region is: "<<nCregion<<" +/- "<<TMath::Sqrt(nCregion)<<endl;
  cout<<"number of events in D region is: "<<nDregion<<" +/- "<<TMath::Sqrt(nDregion)<<endl;
  cout<<"(B2+B4)*C/(A2+A4) is: "<<1.0*(nB2region+nB4region)*nCregion/(nA2region+nA4region)<<" +/- "<<endl<<endl;
  */


  cout<<"number of events in A1 region is: "<<nA1region<<" +/- "<<TMath::Sqrt(nA1region)<<endl;
  cout<<"number of events in B region is: "<<nBregionRpc_<<" +/- "<<TMath::Sqrt(nBregionRpc_)<<endl;
  cout<<"number of events in C1 region is: "<<nC1region<<" +/- "<<TMath::Sqrt(nC1region)<<endl;
  cout<<"number of events in D region is: "<<nDregionRpc_<<" +/- "<<TMath::Sqrt(nDregionRpc_)<<endl;
  cout<<"B*(C1)/(A1) is: "<<1.0*nBregionRpc_*(nC1region)/(nA1region)<<" +/- "<<endl<<endl;

  cout<<"number of events in A2 region is: "<<nA2region<<" +/- "<<TMath::Sqrt(nA2region)<<endl;
  cout<<"number of events in B region is: "<<nBregionRpc_<<" +/- "<<TMath::Sqrt(nBregionRpc_)<<endl;
  cout<<"number of events in C2 region is: "<<nC2region<<" +/- "<<TMath::Sqrt(nC2region)<<endl;
  cout<<"number of events in D region is: "<<nDregionRpc_<<" +/- "<<TMath::Sqrt(nDregionRpc_)<<endl;
  cout<<"B*(C2)/(A2) is: "<<1.0*nBregionRpc_*(nC2region)/(nA2region)<<" +/- "<<endl<<endl;

  /*
  cout<<"number of events in A1 region is: "<<nA1region<<" +/- "<<TMath::Sqrt(nA1region)<<endl;
  cout<<"number of events in B1 region is: "<<nB1region<<" +/- "<<TMath::Sqrt(nB1region)<<endl;
  cout<<"number of events in C region is: "<<nCregionRpc_<<" +/- "<<TMath::Sqrt(nCregionRpc_)<<endl;
  cout<<"number of events in D region is: "<<nDregionRpc_<<" +/- "<<TMath::Sqrt(nDregionRpc_)<<endl;
  cout<<"B1*(C)/(A1) is: "<<1.0*nB1region*(nCregionRpc_)/(nA1region)<<" +/- "<<endl<<endl;

  cout<<"number of events in A2 region is: "<<nA2region<<" +/- "<<TMath::Sqrt(nA2region)<<endl;
  cout<<"number of events in B2 region is: "<<nB2region<<" +/- "<<TMath::Sqrt(nB2region)<<endl;
  cout<<"number of events in C region is: "<<nCregionRpc_<<" +/- "<<TMath::Sqrt(nCregionRpc_)<<endl;
  cout<<"number of events in D region is: "<<nDregionRpc_<<" +/- "<<TMath::Sqrt(nDregionRpc_)<<endl;
  cout<<"B2*(C)/(A2) is: "<<1.0*nB2region*(nCregionRpc_)/(nA2region)<<" +/- "<<endl<<endl;
  */
  cout<<endl;
  if(doPrintout) cout<<"number of printed out events is: "<<nPrintedOutEvents<<endl;

  TString outfileUpperP_path = "../txtfiles/FractionEvents_PtCuts/FractionEventsUpperP_"+file_dataset+".txt";
  TString outfileLowerP_path = "../txtfiles/FractionEvents_PtCuts/FractionEventsLowerP_"+file_dataset+".txt";
  TString outfileHighestP_path = "../txtfiles/FractionEvents_PtCuts/FractionEventsHighestP_"+file_dataset+".txt";
  TString outfileDifferenceP_path = "../txtfiles/FractionEvents_PtCuts/FractionEventsDifferenceP_"+file_dataset+".txt";
  TString outfileAveP_path = "../txtfiles/FractionEvents_PtCuts/FractionEventsAveP_"+file_dataset+".txt";
  TString outfileUpperPt_path = "../txtfiles/FractionEvents_PtCuts/FractionEventsUpperPt_"+file_dataset+".txt";
  TString outfileLowerPt_path = "../txtfiles/FractionEvents_PtCuts/FractionEventsLowerPt_"+file_dataset+".txt";
  TString outfileHighestPt_path = "../txtfiles/FractionEvents_PtCuts/FractionEventsHighestPt_"+file_dataset+".txt";
  TString outfileDifferencePt_path = "../txtfiles/FractionEvents_PtCuts/FractionEventsDifferencePt_"+file_dataset+".txt";
  TString outfileAvePt_path = "../txtfiles/FractionEvents_PtCuts/FractionEventsAvePt_"+file_dataset+".txt";
  TString outfileProductPt_path = "../txtfiles/FractionEvents_PtCuts/FractionEventsProductPt_"+file_dataset+".txt";

  ofstream outfileUpperP(outfileUpperP_path);
  ofstream outfileLowerP(outfileLowerP_path);
  ofstream outfileHighestP(outfileHighestP_path);
  ofstream outfileDifferenceP(outfileDifferenceP_path);
  ofstream outfileAveP(outfileAveP_path);
  ofstream outfileUpperPt(outfileUpperPt_path);
  ofstream outfileLowerPt(outfileLowerPt_path);
  ofstream outfileHighestPt(outfileHighestPt_path);
  ofstream outfileDifferencePt(outfileDifferencePt_path);
  ofstream outfileAvePt(outfileAvePt_path);
  ofstream outfileProductPt(outfileProductPt_path);

  for(int a=0; a<=50; a++){            
    outfileUpperP<<1.0*nUpperPLargerThanCut[a]/pass_DtInvBeta_2_cut<<endl;
    outfileLowerP<<1.0*nLowerPLargerThanCut[a]/pass_DtInvBeta_2_cut<<endl;
    outfileHighestP<<1.0*nHighestPLargerThanCut[a]/pass_DtInvBeta_2_cut<<endl;
    outfileDifferenceP<<1.0*nDifferencePLargerThanCut[a]/pass_DtInvBeta_2_cut<<endl;
    outfileAveP<<1.0*nAvePLargerThanCut[a]/pass_DtInvBeta_2_cut<<endl;

    outfileUpperPt<<1.0*nUpperPtLargerThanCut[a]/pass_DtInvBeta_2_cut<<endl;
    outfileLowerPt<<1.0*nLowerPtLargerThanCut[a]/pass_DtInvBeta_2_cut<<endl;
    outfileHighestPt<<1.0*nHighestPtLargerThanCut[a]/pass_DtInvBeta_2_cut<<endl;
    outfileDifferencePt<<1.0*nDifferencePtLargerThanCut[a]/pass_DtInvBeta_2_cut<<endl;
    outfileAvePt<<1.0*nAvePtLargerThanCut[a]/pass_DtInvBeta_2_cut<<endl;
    outfileProductPt<<1.0*nProductPtLargerThanCut[a]/pass_DtInvBeta_2_cut<<endl;
  }

  TString outfileBCAUpperP_path = "../txtfiles/FractionEvents_PtCuts/BCAUpperP_"+file_dataset+".txt";
  TString outfileBCALowerP_path = "../txtfiles/FractionEvents_PtCuts/BCALowerP_"+file_dataset+".txt";
  TString outfileBCAHighestP_path = "../txtfiles/FractionEvents_PtCuts/BCAHighestP_"+file_dataset+".txt";
  TString outfileBCADifferenceP_path = "../txtfiles/FractionEvents_PtCuts/BCADifferenceP_"+file_dataset+".txt";
  TString outfileBCAAveP_path = "../txtfiles/FractionEvents_PtCuts/BCAAveP_"+file_dataset+".txt";
  TString outfileBCAUpperPt_path = "../txtfiles/FractionEvents_PtCuts/BCAUpperPt_"+file_dataset+".txt";
  TString outfileBCALowerPt_path = "../txtfiles/FractionEvents_PtCuts/BCALowerPt_"+file_dataset+".txt";
  TString outfileBCAHighestPt_path = "../txtfiles/FractionEvents_PtCuts/BCAHighestPt_"+file_dataset+".txt";
  TString outfileBCADifferencePt_path = "../txtfiles/FractionEvents_PtCuts/BCADifferencePt_"+file_dataset+".txt";
  TString outfileBCAAvePt_path = "../txtfiles/FractionEvents_PtCuts/BCAAvePt_"+file_dataset+".txt";
  TString outfileBCAProductPt_path = "../txtfiles/FractionEvents_PtCuts/BCAProductPt_"+file_dataset+".txt";

  ofstream outfileBCAUpperP(outfileBCAUpperP_path);
  ofstream outfileBCALowerP(outfileBCALowerP_path);
  ofstream outfileBCAHighestP(outfileBCAHighestP_path);
  ofstream outfileBCADifferenceP(outfileBCADifferenceP_path);
  ofstream outfileBCAAveP(outfileBCAAveP_path);
  ofstream outfileBCAUpperPt(outfileBCAUpperPt_path);
  ofstream outfileBCALowerPt(outfileBCALowerPt_path);
  ofstream outfileBCAHighestPt(outfileBCAHighestPt_path);
  ofstream outfileBCADifferencePt(outfileBCADifferencePt_path);
  ofstream outfileBCAAvePt(outfileBCAAvePt_path);
  ofstream outfileBCAProductPt(outfileBCAProductPt_path);

  for(int a=0; a<=50; a++){            
    outfileBCAUpperP<<1.0*nBregionUpperP[a]*nCregionUpperP[a]/nAregionUpperP[a]<<endl;
    outfileBCALowerP<<1.0*nBregionLowerP[a]*nCregionLowerP[a]/nAregionLowerP[a]<<endl;
    outfileBCAHighestP<<1.0*nBregionHighestP[a]*nCregionHighestP[a]/nAregionHighestP[a]<<endl;
    outfileBCADifferenceP<<1.0*nBregionDifferenceP[a]*nCregionDifferenceP[a]/nAregionDifferenceP[a]<<endl;
    outfileBCAAveP<<1.0*nBregionAveP[a]*nCregionAveP[a]/nAregionAveP[a]<<endl;
    outfileBCAUpperPt<<1.0*nBregionUpperPt[a]*nCregionUpperPt[a]/nAregionUpperPt[a]<<endl;
    outfileBCALowerPt<<1.0*nBregionLowerPt[a]*nCregionLowerPt[a]/nAregionLowerPt[a]<<endl;
    outfileBCAHighestPt<<1.0*nBregionHighestPt[a]*nCregionHighestPt[a]/nAregionHighestPt[a]<<endl;
    outfileBCADifferencePt<<1.0*nBregionDifferencePt[a]*nCregionDifferencePt[a]/nAregionDifferencePt[a]<<endl;
    outfileBCAAvePt<<1.0*nBregionAvePt[a]*nCregionAvePt[a]/nAregionAvePt[a]<<endl;
    outfileBCAProductPt<<1.0*nBregionProductPt[a]*nCregionProductPt[a]/nAregionProductPt[a]<<endl;
  }

  TString outfileDUpperP_path = "../txtfiles/FractionEvents_PtCuts/DUpperP_"+file_dataset+".txt";
  TString outfileDLowerP_path = "../txtfiles/FractionEvents_PtCuts/DLowerP_"+file_dataset+".txt";
  TString outfileDHighestP_path = "../txtfiles/FractionEvents_PtCuts/DHighestP_"+file_dataset+".txt";
  TString outfileDDifferenceP_path = "../txtfiles/FractionEvents_PtCuts/DDifferenceP_"+file_dataset+".txt";
  TString outfileDAveP_path = "../txtfiles/FractionEvents_PtCuts/DAveP_"+file_dataset+".txt";
  TString outfileDUpperPt_path = "../txtfiles/FractionEvents_PtCuts/DUpperPt_"+file_dataset+".txt";
  TString outfileDLowerPt_path = "../txtfiles/FractionEvents_PtCuts/DLowerPt_"+file_dataset+".txt";
  TString outfileDHighestPt_path = "../txtfiles/FractionEvents_PtCuts/DHighestPt_"+file_dataset+".txt";
  TString outfileDDifferencePt_path = "../txtfiles/FractionEvents_PtCuts/DDifferencePt_"+file_dataset+".txt";
  TString outfileDAvePt_path = "../txtfiles/FractionEvents_PtCuts/DAvePt_"+file_dataset+".txt";
  TString outfileDProductPt_path = "../txtfiles/FractionEvents_PtCuts/DProductPt_"+file_dataset+".txt";

  ofstream outfileDUpperP(outfileDUpperP_path);
  ofstream outfileDLowerP(outfileDLowerP_path);
  ofstream outfileDHighestP(outfileDHighestP_path);
  ofstream outfileDDifferenceP(outfileDDifferenceP_path);
  ofstream outfileDAveP(outfileDAveP_path);
  ofstream outfileDUpperPt(outfileDUpperPt_path);
  ofstream outfileDLowerPt(outfileDLowerPt_path);
  ofstream outfileDHighestPt(outfileDHighestPt_path);
  ofstream outfileDDifferencePt(outfileDDifferencePt_path);
  ofstream outfileDAvePt(outfileDAvePt_path);
  ofstream outfileDProductPt(outfileDProductPt_path);

  for(int a=0; a<=50; a++){            
    outfileDUpperP<<1.0*nDregionUpperP[a]<<endl;
    outfileDLowerP<<1.0*nDregionLowerP[a]<<endl;
    outfileDHighestP<<1.0*nDregionHighestP[a]<<endl;
    outfileDDifferenceP<<1.0*nDregionDifferenceP[a]<<endl;
    outfileDAveP<<1.0*nDregionAveP[a]<<endl;
    outfileDUpperPt<<1.0*nDregionUpperPt[a]<<endl;
    outfileDLowerPt<<1.0*nDregionLowerPt[a]<<endl;
    outfileDHighestPt<<1.0*nDregionHighestPt[a]<<endl;
    outfileDDifferencePt<<1.0*nDregionDifferencePt[a]<<endl;
    outfileDAvePt<<1.0*nDregionAvePt[a]<<endl;
    outfileDProductPt<<1.0*nDregionProductPt[a]<<endl;
  }






  TString outfileBCAInverseBeta_path = "../txtfiles/FractionEvents_InverseBetaCuts/BCAInverseBeta_"+file_dataset+".txt";
  TString outfileBCATimeInOut_path = "../txtfiles/FractionEvents_InverseBetaCuts/BCATimeInOut_"+file_dataset+".txt";
  TString outfileBCADifferenceInverseBeta_path = "../txtfiles/FractionEvents_InverseBetaCuts/BCADifferenceInverseBeta_"+file_dataset+".txt";
  TString outfileBCADifferenceTimeInOut_path = "../txtfiles/FractionEvents_InverseBetaCuts/BCADifferenceTimeInOut_"+file_dataset+".txt";
  ofstream outfileBCAInverseBeta(outfileBCAInverseBeta_path);
  ofstream outfileBCATimeInOut(outfileBCATimeInOut_path);
  ofstream outfileBCADifferenceInverseBeta(outfileBCADifferenceInverseBeta_path);
  ofstream outfileBCADifferenceTimeInOut(outfileBCADifferenceTimeInOut_path);
  for(int a=0; a<=10; a++){            
    cout<<"nAregionDiffernceTimeInOut["<<a<<"] is: "<<nAregionDifferenceTimeInOut[a]<<", nBregionDifferenceTimeInOut["<<a<<"] is: "<<nBregionDifferenceTimeInOut[a]<<", nCregionDifferenceTimeInOut["<<a<<"] is: "<<nCregionDifferenceTimeInOut[a]<<", nDregionDifferenceTimeInOut["<<a<<"] is: "<<nDregionDifferenceTimeInOut[a]<<endl;
    outfileBCAInverseBeta<<1.0*nBregionInverseBeta[a]*nCregionInverseBeta[a]/nAregionInverseBeta[a]<<endl;
    outfileBCATimeInOut<<1.0*nBregionTimeInOut[a]*nCregionTimeInOut[a]/nAregionTimeInOut[a]<<endl;
    outfileBCADifferenceInverseBeta<<1.0*nBregionDifferenceInverseBeta[a]*nCregionDifferenceInverseBeta[a]/nAregionDifferenceInverseBeta[a]<<endl;
    outfileBCADifferenceTimeInOut<<1.0*nBregionDifferenceTimeInOut[a]*nCregionDifferenceTimeInOut[a]/nAregionDifferenceTimeInOut[a]<<endl;
  }

  TString outfileDInverseBeta_path = "../txtfiles/FractionEvents_InverseBetaCuts/DInverseBeta_"+file_dataset+".txt";
  TString outfileDTimeInOut_path = "../txtfiles/FractionEvents_InverseBetaCuts/DTimeInOut_"+file_dataset+".txt";
  TString outfileDDifferenceInverseBeta_path = "../txtfiles/FractionEvents_InverseBetaCuts/DDifferenceInverseBeta_"+file_dataset+".txt";
  TString outfileDDifferenceTimeInOut_path = "../txtfiles/FractionEvents_InverseBetaCuts/DDifferenceTimeInOut_"+file_dataset+".txt";
  ofstream outfileDInverseBeta(outfileDInverseBeta_path);
  ofstream outfileDTimeInOut(outfileDTimeInOut_path);
  ofstream outfileDDifferenceInverseBeta(outfileDDifferenceInverseBeta_path);
  ofstream outfileDDifferenceTimeInOut(outfileDDifferenceTimeInOut_path);
  for(int a=0; a<=10; a++){            
    outfileDInverseBeta<<1.0*nDregionInverseBeta[a]<<endl;
    outfileDTimeInOut<<1.0*nDregionTimeInOut[a]<<endl;
    outfileDDifferenceInverseBeta<<1.0*nDregionDifferenceInverseBeta[a]<<endl;
    outfileDDifferenceTimeInOut<<1.0*nDregionDifferenceTimeInOut[a]<<endl;
  }


  if(!doPrintout) {
    fnew->cd();
    ABCDtree->Write();
    id_hist->Write();
    run_hist->Write();
    bx_hist->Write(); 
    bxWrtCollision_hist->Write();
    bxWrtBunch_hist->Write();
    mcStoppedParticle_N_hist->Write();
    mcStoppedParticleX_hist->Write(); 
    mcStoppedParticleY_hist->Write(); 
    mcStoppedParticleZ_hist->Write(); 
    mcStoppedParticleR_hist->Write(); 
    mcStoppedParticleEta_hist->Write();
    mcStoppedParticlePhi_hist->Write();
    mcStoppedParticleTime_hist->Write();
    mcStoppedParticleXY_hist->Write(); 
    mcStoppedParticleR_muDisplacedStandAloneEta_hist->Write();    
    mcStoppedParticleMass_hist->Write();    
    mcStoppedParticleId_hist->Write();    
    mcStoppedParticleCharge_hist->Write();    
    mcStoppedParticleX_StoppedParticleN_hist->Write();    
    mcStoppedParticleY_StoppedParticleN_hist->Write();    
    mcStoppedParticleZ_StoppedParticleN_hist->Write();    
    mcStoppedParticleId_StoppedParticleN_hist->Write();    
    mcStoppedParticleCharge_StoppedParticleN_hist->Write();    
    mcStoppedParticleTime_mcStoppedParticleCharge_hist->Write();    
    mcStoppedParticleXPos2Stopped_hist->Write();    
    mcStoppedParticleYPos2Stopped_hist->Write();    
    mcStoppedParticleZPos2Stopped_hist->Write();    
    mcStoppedParticleRPos2Stopped_hist->Write();    
    mcStoppedParticleXNeg2Stopped_hist->Write();    
    mcStoppedParticleYNeg2Stopped_hist->Write();    
    mcStoppedParticleZNeg2Stopped_hist->Write();    
    mcStoppedParticleRNeg2Stopped_hist->Write();    
    mcStoppedParticleDeltaTime_hist->Write();
    mcStoppedParticleXPos_hist->Write();    
    mcStoppedParticleYPos_hist->Write();    
    mcStoppedParticleZPos_hist->Write();    
    mcStoppedParticleRPos_hist->Write();    
    mcStoppedParticleXNeg_hist->Write();    
    mcStoppedParticleYNeg_hist->Write();    
    mcStoppedParticleZNeg_hist->Write();    
    mcStoppedParticleRNeg_hist->Write();    
    mcStoppedParticle0Charge_hist->Write();
    mcStoppedParticle1Charge_hist->Write();
    mcStoppedParticle0Time_hist->Write();
    mcStoppedParticle1Time_hist->Write();
    mcLL_N_hist->Write();
    mcLLStatus_hist->Write();
    mcLLPt_hist->Write(); 
    mcLLEta_hist->Write();
    mcLLPhi_hist->Write();
    mcLLCharge_hist->Write();
    mcLLMass_hist->Write();
    mcLLNDaughters_hist->Write();
    mcLLDaughterId_hist->Write();    
    mcRhadron_N_hist->Write();    
    mcRhadronPt_hist->Write();    
    mcRhadronEta_hist->Write();    
    mcRhadronPhi_hist->Write();    
    mcRhadronCharge_hist->Write();    
    mcStop_N_hist->Write();
    mcStop0Charge_hist->Write();
    mcStop1Charge_hist->Write();
    mcStopP_hist->Write();
    mcStopPx_hist->Write();
    mcStopPy_hist->Write();
    mcStopPz_hist->Write();
    mcStopPt_hist->Write();
    mcStopEta_hist->Write();
    mcStopPhi_hist->Write();
    mcStopBeta_hist->Write();
    stopped_mcStopP_hist->Write();
    stopped_mcStopPt_hist->Write();
    stopped_mcStopEta_hist->Write();
    stopped_mcStopPhi_hist->Write();
    stopped_mcStopBeta_hist->Write();
    notStopped_mcStopP_hist->Write();
    notStopped_mcStopPt_hist->Write();
    notStopped_mcStopEta_hist->Write();
    notStopped_mcStopPhi_hist->Write();
    notStopped_mcStopBeta_hist->Write();
    mcGluino_N_hist->Write();
    mcGluino0Charge_hist->Write();
    mcGluino1Charge_hist->Write();
    mcGluinoP_hist->Write();
    mcGluinoPx_hist->Write();
    mcGluinoPy_hist->Write();
    mcGluinoPz_hist->Write();
    mcGluinoPt_hist->Write();
    mcGluinoEta_hist->Write();
    mcGluinoPhi_hist->Write();
    mcGluinoBeta_hist->Write();
    stopped_mcGluinoP_hist->Write();
    stopped_mcGluinoPt_hist->Write();
    stopped_mcGluinoEta_hist->Write();
    stopped_mcGluinoPhi_hist->Write();
    stopped_mcGluinoBeta_hist->Write();
    notStopped_mcGluinoP_hist->Write();
    notStopped_mcGluinoPt_hist->Write();
    notStopped_mcGluinoEta_hist->Write();
    notStopped_mcGluinoPhi_hist->Write();
    notStopped_mcGluinoBeta_hist->Write();
    mcStau_N_hist->Write();
    mcStau0Charge_hist->Write();
    mcStau1Charge_hist->Write();
    mcStauP_hist->Write();
    mcStauPx_hist->Write();
    mcStauPy_hist->Write();
    mcStauPz_hist->Write();
    mcStauPt_hist->Write();
    mcStauEta_hist->Write();
    mcStauPhi_hist->Write();
    mcStauBeta_hist->Write();
    stopped_mcStauP_hist->Write();
    stopped_mcStauPt_hist->Write();
    stopped_mcStauEta_hist->Write();
    stopped_mcStauPhi_hist->Write();
    stopped_mcStauBeta_hist->Write();
    notStopped_mcStauP_hist->Write();
    notStopped_mcStauPt_hist->Write();
    notStopped_mcStauEta_hist->Write();
    notStopped_mcStauPhi_hist->Write();
    notStopped_mcStauBeta_hist->Write();
    mcH0Charge_hist->Write();    
    mcH1Charge_hist->Write();    
    mcHPlusPlusP_hist->Write();    
    mcHPlusPlusPx_hist->Write();    
    mcHPlusPlusPy_hist->Write();    
    mcHPlusPlusPz_hist->Write();    
    mcHPlusPlusPt_hist->Write();    
    mcHPlusPlusEta_hist->Write();    
    mcHPlusPlusPhi_hist->Write();    
    mcHMinusMinusP_hist->Write();    
    mcHMinusMinusPx_hist->Write();    
    mcHMinusMinusPy_hist->Write();    
    mcHMinusMinusPz_hist->Write();    
    mcHMinusMinusPt_hist->Write();    
    mcHMinusMinusEta_hist->Write();    
    mcHMinusMinusPhi_hist->Write();    
    mcHPlusPlusP_HMinusMinusP_hist->Write();
    mcHPlusPlusPt_HMinusMinusPt_hist->Write();
    mcHPlusPlusEta_HMinusMinusEta_hist->Write();
    mcHPlusPlusPhi_HMinusMinusPhi_hist->Write();
    mcTauPrime_N_hist->Write();
    mcTauPrime0Charge_hist->Write();
    mcTauPrime1Charge_hist->Write();
    mcTauPrimeP_hist->Write();
    mcTauPrimePx_hist->Write();
    mcTauPrimePy_hist->Write();
    mcTauPrimePz_hist->Write();
    mcTauPrimePt_hist->Write();
    mcTauPrimeEta_hist->Write();
    mcTauPrimePhi_hist->Write();
    mcTauPrimeBeta_hist->Write();
    stopped_mcTauPrimeP_hist->Write();
    stopped_mcTauPrimePt_hist->Write();
    stopped_mcTauPrimeEta_hist->Write();
    stopped_mcTauPrimePhi_hist->Write();
    stopped_mcTauPrimeBeta_hist->Write();
    notStopped_mcTauPrimeP_hist->Write();
    notStopped_mcTauPrimePt_hist->Write();
    notStopped_mcTauPrimeEta_hist->Write();
    notStopped_mcTauPrimePhi_hist->Write();
    notStopped_mcTauPrimeBeta_hist->Write();
    mcTop_N_hist->Write();
    mcTopStatus_hist->Write();
    mcTopPt_hist->Write();
    mcTopEta_hist->Write();
    mcTopPhi_hist->Write();
    mcTopCharge_hist->Write();
    mcTopMass_hist->Write();
    mcTopNDaughters_hist->Write();
    mcTopDaughterId_hist->Write();
    mcW_N_hist->Write();
    mcWStatus_hist->Write();
    mcWPt_hist->Write();
    mcWEta_hist->Write();
    mcWPhi_hist->Write();
    mcWCharge_hist->Write();
    mcWMass_hist->Write();
    mcWNDaughters_hist->Write();
    mcWDaughterId_hist->Write();
    mcMuon_N_hist->Write();
    mcMuonP_hist->Write();
    mcMuonPt_hist->Write();
    mcMuonEta_hist->Write();
    mcMuonPhi_hist->Write();
    mcMuonCharge_hist->Write();
    mcMuonStatus_hist->Write();
    mcMuonMass_hist->Write();
    mcMuonMotherId_hist->Write();
    mcMuonVx_hist->Write();
    mcMuonVy_hist->Write();
    mcMuonVz_hist->Write();
    mcMuonLxy_hist->Write();
    mcMuonDxy_hist->Write();
    mcMuon3Dangle_hist->Write();
    mcMuonDeltaPhi_hist->Write();
    mcMuonInverseBeta_hist->Write();
    mcMuonPt_muRefittedStandAlonePt_hist->Write();
    mcMuonPt_muCosmicPt_hist->Write();
    mcMuonPt_muCosmicTrackPt_hist->Write();
    simTrackN_hist->Write();
    simTrackPt_hist->Write();
    simTrackEta_hist->Write();
    simTrackPhi_hist->Write();
    simTrackCharge_hist->Write();
    simTrackVx_hist->Write();
    simTrackVy_hist->Write();
    simTrackVz_hist->Write();
    muStandAloneP_hist->Write();
    muStandAloneUpdatedAtVtxP_hist->Write();
    muStandAlonePt_hist->Write();
    muStandAloneUpdatedAtVtxPt_hist->Write();
    muDisplacedStandAloneGenDR_hist->Write();
    muGenDR_hist->Write();
    muStandAloneTrackGenDR_hist->Write();
    muStandAloneTrackUpdatedAtVtxGenDR_hist->Write();
    muRefittedStandAloneTrackGenDR_hist->Write();
    muCosmicTrackGenDR_hist->Write();    
    mcStoppedParticleR_muDisplacedStandAloneGenDR_hist->Write();
    muDisplacedStandAlonePtResolution_hist->Write();
    muPtResolution_hist->Write();
    muStandAlonePtResolution_hist->Write();
    muStandAloneUpdatedAtVtxPtResolution_hist->Write();
    muRefittedStandAlonePtResolution_hist->Write();
    muCosmicPtResolution_hist->Write();
    muDisplacedStandAloneQoverPtResolution_hist->Write();
    muQoverPtResolution_hist->Write();
    muStandAloneQoverPtResolution_hist->Write();
    muStandAloneUpdatedAtVtxQoverPtResolution_hist->Write();
    muRefittedStandAloneQoverPtResolution_hist->Write();
    muCosmicQoverPtResolution_hist->Write();
    muRefittedStandAlonePtResolution_muCosmicPtResolution_hist->Write();
    muDisplacedStandAloneNChambersDt_PtResolution_hist->Write();
    muRefittedStandAloneNChambersDt_PtResolution_hist->Write();
    muCosmicNChambersDt_PtResolution_hist->Write();
    muDisplacedStandAloneNChambersRpc_PtResolution_hist->Write();
    muRefittedStandAloneNChambersRpc_PtResolution_hist->Write();
    muCosmicNChambersRpc_PtResolution_hist->Write();
    muDisplacedStandAloneNChambersDt_Pt_hist->Write();
    muRefittedStandAloneNChambersDt_Pt_hist->Write();
    muCosmicNChambersDt_Pt_hist->Write();
    muDisplacedStandAloneNChambersRpc_Pt_hist->Write();
    muRefittedStandAloneNChambersRpc_Pt_hist->Write();
    muCosmicNChambersRpc_Pt_hist->Write();
    muDisplacedStandAlonePt_muCosmicTrackPt_hist->Write();
    mcMuonN_muDisplacedStandAloneN_hist->Write();
    mcMuonPt_muDisplacedStandAlonePt_hist->Write();
    mcMuonEta_muDisplacedStandAloneEta_hist->Write();
    mcMuonPhi_muDisplacedStandAlonePhi_hist->Write();
    mcMuonCharge_muDisplacedStandAloneCharge_hist->Write();
    mcMuonLxy_muDisplacedStandAloneLxy_hist->Write();
    mcMuonDxy_muDisplacedStandAloneDxy_hist->Write();
    mcMuonInverseBeta_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist->Write();    
    muRefittedStandAloneNHitsDt_Pt_hist->Write();
    //muRefittedStandAloneNChambersDt_Pt_hist->Write();
    mcStoppedParticleR_muRefittedStandAlonePt_hist->Write();
    mcStoppedParticleR_mcMuonPt_hist->Write();
    muDisplacedStandAloneTrackDistanceStations_Pt_hist->Write();
    muRefittedStandAloneTrackDistanceStations_Pt_hist->Write();
    mcMuonPt_l1MuonPt_hist->Write();
    mcMuonPt_hlt20Cha2MuonPt_hist->Write();
    mcMuonEta_l1MuonEta_hist->Write();
    mcMuonPhi_l1MuonPhi_hist->Write();
    mcMuonEta_hlt20Cha2MuonEta_hist->Write();
    mcMuonPhi_hlt20Cha2MuonPhi_hist->Write();
    l1Muon_N_hist->Write();
    l1MuonPt_hist->Write();
    l1MuonEta_hist->Write();
    l1MuonPhi_hist->Write();
    hlt20Cha2Muon_N_hist->Write();
    hlt20Cha2MuonPt_hist->Write();
    hlt20Cha2MuonEta_hist->Write();
    hlt20Cha2MuonPhi_hist->Write();
    mu_N_hist ->Write();
    muP_hist ->Write();
    muPt_hist ->Write();
    muEta_hist->Write();
    muPhi_hist->Write();
    muType_hist->Write(); 
    muIso_hist->Write();
    muEta_muPhi_hist->Write();    
    diMu_N_hist->Write();
    diMuMass_hist->Write();    
    muCosmic_N_hist->Write();
    muCosmicP_hist->Write();
    muCosmicPt_hist->Write();
    muCosmicEta_hist->Write();
    muCosmicPhi_hist->Write();
    muCosmicType_hist->Write();
    muCosmicEta_muCosmicPhi_hist->Write(); 
    muCosmicTrackInnerPt_hist->Write();   
    muCosmicTrackNChambersDt_hist->Write();
    muDisplacedStandAlone_N_other_cut_hist->Write();    
    muDisplacedStandAlone_N_hist->Write();
    muDisplacedStandAloneP_hist->Write();
    muDisplacedStandAlonePt_hist->Write();
    muDisplacedStandAlonePt0_hist->Write();
    muDisplacedStandAlonePt1_hist->Write();
    muDisplacedStandAlonePt2_hist->Write();
    muDisplacedStandAloneEta_hist->Write();
    muDisplacedStandAlonePhi_hist->Write();
    muDisplacedStandAloneCharge_hist->Write();
    muDisplacedStandAloneTrackNormalizedChi2_hist->Write();
    muDisplacedStandAloneTrackDxy_hist->Write();
    muDisplacedStandAloneTrackDz_hist->Write(); 
    muDisplacedStandAloneTrackNHitsMuon_hist->Write();
    muDisplacedStandAloneTrackNHitsCsc_hist->Write(); 
    muDisplacedStandAloneTrackNHitsDt_hist->Write();
    muDisplacedStandAloneTrackNHitsRpc_hist->Write(); 
    muDisplacedStandAloneTrackNRpcDof_hist->Write();
    muDisplacedStandAloneTrackNStations_hist->Write();
    muDisplacedStandAloneTrackNChambersCsc_hist->Write();
    muDisplacedStandAloneTrackNChambersDt_hist->Write(); 
    muDisplacedStandAloneTrackNChambersRpc_hist->Write();
    muDisplacedStandAloneTrackDistanceStations_hist->Write();
    muDisplacedStandAloneTrackInnerPt_hist->Write();
    muDisplacedStandAloneTrackDtTofNDof_hist->Write();
    muDisplacedStandAloneBxPattern_hist->Write();
    muDisplacedStandAloneNHitsRpcBxPattern0_hist->Write();    
    muDisplacedStandAloneBxAverage_hist->Write();
    muDisplacedStandAloneOppositeSegDR_hist->Write();    
    muDisplacedStandAloneOppositeSegDEta_hist->Write();    
    muDisplacedStandAloneOppositeSegDPhi_hist->Write();
    muDisplacedStandAlonePt_denominator_hist->Write();
    muDisplacedStandAlonePt_L1numerator_hist->Write();
    muDisplacedStandAlonePt_HLTnumerator_hist->Write();
    muRefittedStandAlonePt_denominator_hist->Write();
    muRefittedStandAlonePt_L1numerator_hist->Write();
    muRefittedStandAlonePt_HLTnumerator_hist->Write();
    muDisplacedStandAlonePt_GlSAdenominator_hist->Write();
    muDisplacedStandAlonePt_GlSAnumerator_hist->Write();
    muDisplacedStandAloneTrackShowerSize_station0_hist->Write();
    muDisplacedStandAloneTrackShowerSize_station1_hist->Write();
    muDisplacedStandAloneTrackShowerSize_station2_hist->Write();
    muDisplacedStandAloneTrackShowerSize_station3_hist->Write();
    muDisplacedStandAloneTrackShowerDeltaR_station0_hist->Write();
    muDisplacedStandAloneTrackShowerDeltaR_station1_hist->Write();
    muDisplacedStandAloneTrackShowerDeltaR_station2_hist->Write();
    muDisplacedStandAloneTrackShowerDeltaR_station3_hist->Write();
    muDisplacedStandAloneTrackShowerNHits_station0_hist->Write();
    muDisplacedStandAloneTrackShowerNHits_station1_hist->Write();
    muDisplacedStandAloneTrackShowerNHits_station2_hist->Write();
    muDisplacedStandAloneTrackShowerNHits_station3_hist->Write();
    muDisplacedStandAloneTrackShowerNCorrelatedHits_station0_hist->Write();
    muDisplacedStandAloneTrackShowerNCorrelatedHits_station1_hist->Write();
    muDisplacedStandAloneTrackShowerNCorrelatedHits_station2_hist->Write();
    muDisplacedStandAloneTrackShowerNCorrelatedHits_station3_hist->Write();
    muDisplacedStandAloneTrackShowerNUncorrelatedHits_station0_hist->Write();
    muDisplacedStandAloneTrackShowerNUncorrelatedHits_station1_hist->Write();
    muDisplacedStandAloneTrackShowerNUncorrelatedHits_station2_hist->Write();
    muDisplacedStandAloneTrackShowerNUncorrelatedHits_station3_hist->Write();    
    muDisplacedStandAloneUpperOnlyDEta_hist->Write();    
    muDisplacedStandAloneUpperOnlyDPhi_hist->Write();    
    muDisplacedStandAloneLowerOnlyDEta_hist->Write();    
    muDisplacedStandAloneLowerOnlyDPhi_hist->Write();    
    muDisplacedStandAloneNCscSegments_hist->Write();    
    muDisplacedStandAlonePhi_muDisplacedStandAloneDTTofFreeInverseBeta_hist->Write();
    muDisplacedStandAloneEta_muDisplacedStandAlonePhi_hist->Write();
    muDisplacedStandAloneTrackNHitsRpc_muDisplacedStandAloneTrackNormalizedChi2_hist->Write();
    muDisplacedStandAloneTrackNHitsRpc_muDisplacedStandAloneTrackNHitsDt_hist->Write();
    muDisplacedStandAlonePt_muDisplacedStandAloneTrackNChambersDt_hist->Write();
    muDisplacedStandAlonePt_DtTofFreeInverseBeta_hist->Write();
    muDisplacedStandAloneP_DtTofFreeInverseBeta_hist->Write();
    muDisplacedStandAloneP_BxPattern_hist->Write();
    muDisplacedStandAlonePt_BxPattern_hist->Write();
    muDisplacedStandAloneDtTofFreeInverseBeta_DtTofDirection_hist->Write();
    muDisplacedStandAloneDtTofFreeInverseBetaErr_DtTofNDof_hist->Write();
    runNumber_muDisplacedStandAloneDtTofFreeInverseBeta_hist->Write();
    runNumber_muDisplacedStandAloneDtTofInverseBeta_hist->Write();
    runNumber_muDisplacedStandAlonePt_hist->Write();
    runNumber_muDisplacedStandAlonePhi_hist->Write();
    runNumber_muDisplacedStandAloneN_hist->Write();
    muDisplacedStandAloneEta_Phi_hist->Write();
    Upper_muDisplacedStandAlonePt_hist->Write();
    Upper_muDisplacedStandAloneEta_hist->Write();
    Upper_muDisplacedStandAlonePhi_hist->Write();
    Upper_muDisplacedStandAloneTrackCharge_hist->Write();
    Upper_muDisplacedStandAloneTrackNormalizedChi2_hist->Write();
    Upper_muDisplacedStandAloneTrackDxy_hist->Write();
    Upper_muDisplacedStandAloneTrackDz_hist->Write();
    Upper_muDisplacedStandAloneTrackNHitsMuon_hist->Write();
    Upper_muDisplacedStandAloneTrackNHitsCsc_hist->Write();
    Upper_muDisplacedStandAloneTrackNHitsDt_hist->Write();
    Upper_muDisplacedStandAloneTrackNHitsRpc_hist->Write();
    Upper_muDisplacedStandAloneTrackNRpcDof_hist->Write();
    Upper_muDisplacedStandAloneTrackNStations_hist->Write();
    Upper_muDisplacedStandAloneTrackNChambersCsc_hist->Write();
    Upper_muDisplacedStandAloneTrackNChambersDt_hist->Write();
    Upper_muDisplacedStandAloneTrackNChambersRpc_hist->Write();
    Upper_muDisplacedStandAloneTrackDtTofNDof_hist->Write();
    Upper_muDisplacedStandAloneTrackDtTofInverseBeta_hist->Write();
    Upper_muDisplacedStandAloneTrackDtTofInverseBetaErr_hist->Write();
    Upper_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist->Write();
    Upper_muDisplacedStandAloneTrackDtTofFreeInverseBetaErr_hist->Write();
    Upper_muDisplacedStandAloneTrackDtTofTimeAtIpInOut_hist->Write();
    Upper_muDisplacedStandAloneTrackDtTofTimeAtIpOutIn_hist->Write();
    Upper_muDisplacedStandAloneTrackDtTofTimeAtIpInOutErr_hist->Write();
    Upper_muDisplacedStandAloneTrackDtTofTimeAtIpOutInErr_hist->Write();
    Upper_muDisplacedStandAloneTrackDtTofDirection_hist->Write();
    Upper_muDisplacedStandAloneTrackDtTofErrDiff_hist->Write();
    Upper_muDisplacedStandAloneBxPattern_hist->Write();
    Upper_muDisplacedStandAloneBxAverage_hist->Write();
    Upper_muDisplacedStandAloneTrackNHitsRpc_Upper_muDisplacedStandAloneTrackNormalizedChi2_hist->Write();
    Upper_muDisplacedStandAloneTrackNHitsRpc_Upper_muDisplacedStandAloneTrackNHitsDt_hist->Write();
    Upper_muDisplacedStandAloneBxPattern_Upper_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist->Write();
    Upper_muDisplacedStandAloneBxPattern_Upper_muDisplacedStandAloneTrackDtTofNDof_hist->Write();
    Upper_muDisplacedStandAloneBxPattern_mudiff_muDisplacedStandAloneTofTimeAtIpInOut_hist->Write();
    Upper_muDisplacedStandAlonePt_Upper_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist->Write();
    Upper_muDisplacedStandAloneP_Upper_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist->Write();
    Upper_muDisplacedStandAlonePt_Upper_muDisplacedStandAloneBxPattern_hist->Write();
    Upper_muDisplacedStandAloneP_Upper_muDisplacedStandAloneBxPattern_hist->Write();
    Upper_muDisplacedStandAloneTimeAtIpInOut_Upper_muDisplacedStandAloneFreeInverseBeta_hist->Write();
    Upper_muDisplacedStandAloneTimeAtIpInOut_Upper_muDisplacedStandAloneDirection_hist->Write();
    Upper_muDisplacedStandAloneFreeInverseBeta_Upper_muDisplacedStandAloneFreeInverseBetaErr_hist->Write();
    Highest_muDisplacedStandAloneP_Upper_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist->Write();
    Upper_runNumber_muDisplacedStandAloneDtTofFreeInverseBeta_hist->Write();
    Upper_runNumber_muDisplacedStandAloneDtTofInverseBeta_hist->Write();
    Upper_runNumber_muDisplacedStandAlonePt_hist->Write();    
    Upper_runNumber_muDisplacedStandAlonePhi_hist->Write();
    Upper_runNumber_muDisplacedStandAloneN_hist->Write();
    Upper_muDisplacedStandAloneEta_Phi_hist->Write();
    Lower_muDisplacedStandAlonePt_hist->Write();
    Lower_muDisplacedStandAloneEta_hist->Write();
    Lower_muDisplacedStandAlonePhi_hist->Write();
    Lower_muDisplacedStandAloneTrackCharge_hist->Write();
    Lower_muDisplacedStandAloneTrackNormalizedChi2_hist->Write();
    Lower_muDisplacedStandAloneTrackDxy_hist->Write();
    Lower_muDisplacedStandAloneTrackDz_hist->Write();
    Lower_muDisplacedStandAloneTrackNHitsMuon_hist->Write();
    Lower_muDisplacedStandAloneTrackNHitsCsc_hist->Write();
    Lower_muDisplacedStandAloneTrackNHitsDt_hist->Write();
    Lower_muDisplacedStandAloneTrackNHitsRpc_hist->Write();
    Lower_muDisplacedStandAloneTrackNRpcDof_hist->Write();
    Lower_muDisplacedStandAloneTrackNStations_hist->Write();
    Lower_muDisplacedStandAloneTrackNChambersCsc_hist->Write();
    Lower_muDisplacedStandAloneTrackNChambersDt_hist->Write();
    Lower_muDisplacedStandAloneTrackNChambersRpc_hist->Write();
    Lower_muDisplacedStandAloneTrackDtTofNDof_hist->Write();
    Lower_muDisplacedStandAloneTrackDtTofInverseBeta_hist->Write();
    Lower_muDisplacedStandAloneTrackDtTofInverseBetaErr_hist->Write();
    Lower_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist->Write();
    Lower_muDisplacedStandAloneTrackDtTofFreeInverseBetaErr_hist->Write();
    Lower_muDisplacedStandAloneTrackDtTofTimeAtIpInOut_hist->Write();
    Lower_muDisplacedStandAloneTrackDtTofTimeAtIpOutIn_hist->Write();
    Lower_muDisplacedStandAloneTrackDtTofTimeAtIpInOutErr_hist->Write();
    Lower_muDisplacedStandAloneTrackDtTofTimeAtIpOutInErr_hist->Write();
    Lower_muDisplacedStandAloneTrackDtTofDirection_hist->Write();
    Lower_muDisplacedStandAloneTrackDtTofErrDiff_hist->Write();
    Lower_muDisplacedStandAloneBxPattern_hist->Write();
    Lower_muDisplacedStandAloneBxAverage_hist->Write();
    Lower_muDisplacedStandAloneTrackNHitsRpc_Lower_muDisplacedStandAloneTrackNormalizedChi2_hist->Write();
    Lower_muDisplacedStandAloneTrackNHitsRpc_Lower_muDisplacedStandAloneTrackNHitsDt_hist->Write();
    Lower_muDisplacedStandAloneBxPattern_Lower_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist->Write();
    Lower_muDisplacedStandAlonePt_Lower_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist->Write();
    Lower_muDisplacedStandAlonePt_Lower_muDisplacedStandAloneBxPattern_hist->Write();
    Lower_muDisplacedStandAloneP_Lower_muDisplacedStandAloneBxPattern_hist->Write();
    Lower_muDisplacedStandAloneTimeAtIpInOut_Lower_muDisplacedStandAloneFreeInverseBeta_hist->Write();
    Lower_muDisplacedStandAloneTimeAtIpInOut_Lower_muDisplacedStandAloneDirection_hist->Write();
    Lower_muDisplacedStandAloneFreeInverseBeta_Lower_muDisplacedStandAloneFreeInverseBetaErr_hist->Write();
    Lower_runNumber_muDisplacedStandAloneDtTofFreeInverseBeta_hist->Write();
    Lower_runNumber_muDisplacedStandAloneDtTofInverseBeta_hist->Write();
    Lower_runNumber_muDisplacedStandAlonePt_hist->Write();    
    Lower_runNumber_muDisplacedStandAlonePhi_hist->Write();
    Lower_runNumber_muDisplacedStandAloneN_hist->Write();
    Lower_muDisplacedStandAloneEta_Phi_hist->Write();
    Upper_Lower_muDisplacedStandAlone_deltaPhi_hist->Write();
    mudiff_muDisplacedStandAloneTofTimeAtIpInOut_hist->Write();
    mudiff_muDisplacedStandAloneTofTimeAtIpOutIn_hist->Write();
    mudiff_muDisplacedStandAloneTofFreeInverseBeta_hist->Write();
    mudiff_muDisplacedStandAloneTofDirection_hist->Write();
    mudiff_muDisplacedStandAloneTrackDtTofErrDiff_hist->Write();
    Upper_Lower_muDisplacedStandAlone_chargeMultiply_hist->Write();
    Upper_Lower_muDisplacedStandAlone_directionMultiply_hist->Write();
    Upper_Lower_muDisplacedStandAloneBxAverage_hist->Write();
    mudiff_muDisplacedStandAloneBxAverage_hist->Write();
    Upper_Lower_muDisplacedStandAloneTofTimeAtIpInOut_hist->Write();
    Upper_Lower_muDisplacedStandAloneTofTimeAtIpOutIn_hist->Write();
    Upper_Lower_muDisplacedStandAloneTrackCharge_hist->Write();
    Upper_Lower_muDisplacedStandAloneTrackDtTofDirection_hist->Write();
    Upper_Lower_muDisplacedStandAlonePt_hist->Write();
    Upper_Lower_muDisplacedStandAloneDtTofFreeInverseBeta_hist->Write();
    Upper_Lower_muDisplacedStandAloneRpcBxPattern_hist->Write();
    mudiff_muDisplacedStandAloneTofTimeAtIpInOut_muDisplacedStandAloneTofFreeInverseBeta_hist->Write();
    Upper_muDisplacedStandAloneP_mudiff_muDisplacedStandAloneBxAverage_hist->Write();
    Lower_muDisplacedStandAloneP_mudiff_muDisplacedStandAloneBxAverage_hist->Write();    
    Both_muDisplacedStandAlonePt_hist->Write();
    Both_muDisplacedStandAloneEta_hist->Write();
    Both_muDisplacedStandAlonePhi_hist->Write();
    Both_muDisplacedStandAloneTrackCharge_hist->Write();
    Both_muDisplacedStandAloneTrackNormalizedChi2_hist->Write();
    Both_muDisplacedStandAloneTrackDxy_hist->Write();
    Both_muDisplacedStandAloneTrackDz_hist->Write();
    Both_muDisplacedStandAloneTrackNHitsMuon_hist->Write();
    Both_muDisplacedStandAloneTrackNHitsCsc_hist->Write();
    Both_muDisplacedStandAloneTrackNHitsDt_hist->Write();
    Both_muDisplacedStandAloneTrackNHitsRpc_hist->Write();
    Both_muDisplacedStandAloneTrackNRpcDof_hist->Write();
    Both_muDisplacedStandAloneTrackNStations_hist->Write();
    Both_muDisplacedStandAloneTrackNChambersCsc_hist->Write();
    Both_muDisplacedStandAloneTrackNChambersDt_hist->Write();
    Both_muDisplacedStandAloneTrackNChambersRpc_hist->Write();
    Both_muDisplacedStandAloneTrackDtTofNDof_hist->Write();
    Both_muDisplacedStandAloneTrackDtTofInverseBeta_hist->Write();
    Both_muDisplacedStandAloneTrackDtTofInverseBetaErr_hist->Write();
    Both_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist->Write();
    Both_muDisplacedStandAloneTrackDtTofFreeInverseBetaErr_hist->Write();
    Both_muDisplacedStandAloneTrackDtTofTimeAtIpInOut_hist->Write();
    Both_muDisplacedStandAloneTrackDtTofTimeAtIpOutIn_hist->Write();
    Both_muDisplacedStandAloneTrackDtTofTimeAtIpInOutErr_hist->Write();
    Both_muDisplacedStandAloneTrackDtTofTimeAtIpOutInErr_hist->Write();
    Both_muDisplacedStandAloneTrackDtTofDirection_hist->Write();
    Both_muDisplacedStandAloneTrackDtTofErrDiff_hist->Write();
    Both_muDisplacedStandAloneBxPattern_hist->Write();    
    Both_muDisplacedStandAloneBxAverage_hist->Write();
    Upper_muDisplacedStandAloneP_mudiff_muDisplacedStandAloneTofFreeInverseBeta_hist->Write();
    Ave_muDisplacedStandAlonePt_hist->Write();
    Diff_muDisplacedStandAlonePt_hist->Write();
    mcMuon_muDisplacedStandAlone_3Dangle_hist->Write();
    mcMuon_muDisplacedStandAlone_deltaPhi_hist->Write();
    /*
    muRefittedStandAlone_N_hist->Write();
    muRefittedStandAloneP_hist->Write();
    muRefittedStandAlonePt_hist->Write();
    muRefittedStandAloneEta_hist->Write();
    muRefittedStandAlonePhi_hist->Write();
    muRefittedStandAloneTrackDistanceStations_hist->Write();
    muRefittedStandAloneEta_muRefittedStandAlonePhi_hist->Write();    
    muStandAloneTof_N_hist->Write();
    muStandAloneTofDirection_hist->Write();
    muStandAloneTofNDof_hist->Write();
    muStandAloneTofInverseBeta_hist->Write();
    muStandAloneTofInverseBetaErr_hist->Write();
    muStandAloneTofFreeInverseBeta_hist->Write();
    muStandAloneTofFreeInverseBetaErr_hist->Write();
    muStandAloneTofTimeAtIpInOut_hist->Write();
    muStandAloneTofTimeAtIpInOutErr_hist->Write();
    muStandAloneTofTimeAtIpOutIn_hist->Write();
    muStandAloneTofTimeAtIpOutInErr_hist->Write();
    muDisplacedStandAloneDTTof_N_hist->Write();
    muDisplacedStandAloneDTTofDirection_hist->Write();
    muDisplacedStandAloneDTTofNDof_hist->Write();
    muDisplacedStandAloneDTTofInverseBeta_hist->Write();
    muDisplacedStandAloneDTTofInverseBetaErr_hist->Write();
    muDisplacedStandAloneDTTofFreeInverseBeta_hist->Write();
    muDisplacedStandAloneDTTofFreeInverseBetaErr_hist->Write();
    muDisplacedStandAloneDTTofTimeAtIpInOut_hist->Write();
    muDisplacedStandAloneDTTofTimeAtIpInOutErr_hist->Write();
    muDisplacedStandAloneDTTofTimeAtIpOutIn_hist->Write();
    muDisplacedStandAloneDTTofTimeAtIpOutInErr_hist->Write();    
    muDisplacedStandAloneCSCTof_N_hist->Write();
    muDisplacedStandAloneCSCTofDirection_hist->Write();
    muDisplacedStandAloneCSCTofNDof_hist->Write();
    muDisplacedStandAloneCSCTofInverseBeta_hist->Write();
    muDisplacedStandAloneCSCTofInverseBetaErr_hist->Write();
    muDisplacedStandAloneCSCTofFreeInverseBeta_hist->Write();
    muDisplacedStandAloneCSCTofFreeInverseBetaErr_hist->Write();
    muDisplacedStandAloneCSCTofTimeAtIpInOut_hist->Write();
    muDisplacedStandAloneCSCTofTimeAtIpInOutErr_hist->Write();
    muDisplacedStandAloneCSCTofTimeAtIpOutIn_hist->Write();
    muDisplacedStandAloneCSCTofTimeAtIpOutInErr_hist->Write();    
    */
    regionD_muDisplacedStandAlone_N_hist->Write();
    regionD_muDisplacedStandAloneP_hist->Write();
    regionD_muDisplacedStandAlonePt_hist->Write();
    regionD_muDisplacedStandAloneEta_hist->Write();
    regionD_muDisplacedStandAlonePhi_hist->Write();
    regionD_muDisplacedStandAloneCharge_hist->Write();
    regionD_muDisplacedStandAloneTrackNormalizedChi2_hist->Write();
    regionD_muDisplacedStandAloneTrackDxy_hist->Write();
    regionD_muDisplacedStandAloneTrackDz_hist->Write();
    regionD_muDisplacedStandAloneTrackNHitsMuon_hist->Write();
    regionD_muDisplacedStandAloneTrackNHitsCsc_hist->Write();
    regionD_muDisplacedStandAloneTrackNHitsDt_hist->Write();
    regionD_muDisplacedStandAloneTrackNHitsRpc_hist->Write();
    regionD_muDisplacedStandAloneTrackNRpcDof_hist->Write();
    regionD_muDisplacedStandAloneTrackNStations_hist->Write();
    regionD_muDisplacedStandAloneTrackNChambersCsc_hist->Write();
    regionD_muDisplacedStandAloneTrackNChambersDt_hist->Write();
    regionD_muDisplacedStandAloneTrackNChambersRpc_hist->Write();
    regionD_muDisplacedStandAloneTrackDtTofNDof_hist->Write();
    regionD_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist->Write();
    regionD_muDisplacedStandAloneTrackDtTofFreeInverseBetaErr_hist->Write();
    regionD_muDisplacedStandAloneTrackDtTofTimeAtIpInOut_hist->Write();
    regionD_muDisplacedStandAloneTrackDtTofTimeAtIpInOutErr_hist->Write();
    regionD_muDisplacedStandAloneBxPattern_hist->Write();    
    regionD_CSCSegment_N_hist->Write();
    regionAB_Upper_muDisplacedStandAloneP_Upper_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist->Write();
    regionAC_Upper_muDisplacedStandAloneP_Upper_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist->Write();
    regionB_muDisplacedStandAloneP_hist->Write();
    regionC_muDisplacedStandAloneTrackDtTofFreeInverseBeta_hist->Write();
    regionC_muDisplacedStandAloneTrackBxPattern_hist->Write();
    DTSegment_N_hist->Write();
    CSCSegment_N_hist->Write();

    //fnew->Close();
  }

  /*
  f_simpleTree->cd();
  simpleTree->Write();
  //f_simpleTree->Close();
  */

  //return(0);
}


