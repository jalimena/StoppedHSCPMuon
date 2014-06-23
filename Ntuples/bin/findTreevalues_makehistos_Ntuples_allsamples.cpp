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
    doTriggerCut = false;
    doPtCut = false;
    doChaCut = false;
    doEtaCut = false;
    doUpperCut = false;
    doRpcCut = false;
    doDisStCut = false;
    doRpcBxCut = false;
    doDtHitsCut = false;
    doCscHitsCut = false;
    doDtInvBetaCut = false;
    doTimeInOutCut = false;
    doOppEtaCut = false;
    doOppPhiCut = false;
    doTightPhi = false;
    doCosEnrich = false;
    doPrintout = false;

    BxCutValue_ = 2;
    ChaCutValue_ = 1;
    RpcCutValue_ = 2;
    DisStCutValue_ = 2;
    DtHitsCutValue_ = 8;
    CscHitsCutValue_ = 0;
    PtCutValue_ = 30.;
    Pt0CutValue_ = 30.;
    Pt1CutValue_ = 20.;
    EtaCutValue_ = 1.0;
    DtInvBetaCutValue_ = 0.7;
    TimeInOutCutValue_ = 0.;
    OppEtaCutValue_ = 0.1;
    OppPhiCutValue_ = 0.1;

    tracker_count_ = 0;
    eb_count_ = 0;
    ee_count_ = 0;
    hb_count_ = 0;
    he_count_ = 0;
    mb_count_ = 0;
    me_count_ = 0;
    other_detector_count_ = 0;
    cavern_count_ = 0;
    detector_count_ = 0;
    tracker_AccCount_ = 0;
    eb_AccCount_ = 0;
    ee_AccCount_ = 0;
    hb_AccCount_ = 0;
    he_AccCount_ = 0;
    mb_AccCount_ = 0;
    me_AccCount_ = 0;
    other_detector_AccCount_ = 0;
    cavern_AccCount_ = 0;
    detector_AccCount_ = 0;

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
    pass_trigger_cut = 0;
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
    pass_OppEta_cut = 0;
    pass_OppPhi_cut = 0;
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
    pass_OppEta_2_cut = 0;
    pass_OppPhi_2_cut = 0;

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
    run_hist = new TH1D("run_hist","Run Number",8000,192000,200000);
    bx_hist = new TH1D("bx_hist","BX",8000,0,4000);
    bxWrtCollision_hist = new TH1D("bxWrtCollision_hist","BX w.r.t. Collision",4000,-1000,1000);
    bxWrtBunch_hist = new TH1D("bxWrtBunch_hist","BX w.r.t. Bunch",4000,-1000,1000);
    
    mcStoppedParticle_N_hist = new TH1D("mcStoppedParticle_N_hist","Number of Stopped Particles",10,0,10);
    mcStoppedParticleX_hist = new TH1D("mcStoppedParticleX_hist","Stopped Particle X",300,-1500,1500);
    mcStoppedParticleY_hist = new TH1D("mcStoppedParticleY_hist","Stopped Particle Y",300,-1500,1500);
    mcStoppedParticleZ_hist = new TH1D("mcStoppedParticleZ_hist","Stopped Particle Z",300,-1500,1500);
    mcStoppedParticleR_hist = new TH1D("mcStoppedParticleR_hist","Stopped Particle R",300,0,1500);
    mcStoppedParticlePhi_hist = new TH1D("mcStoppedParticlePhi_hist","StoppedParticle #phi",64,-3.2,3.2);
    mcStoppedParticleXY_hist = new TH2D("mcStoppedParticleXY_hist","Stopped Particle X vs Y",300,-1500,1500,300,-1500,1500);
    mcStoppedParticleR_muStandAloneEta_hist = new TH2D("mcStoppedParticleR_muStandAloneEta_hist","Stopped Particle R vs SA #eta",300,0,1500,120,-6,6);
    
    mcLL_N_hist = new TH1D("mcLL_N_hist","Number of Gen LL Particles",10,0,10);
    mcLLStatus_hist = new TH1D("mcLLStatus_hist","Gen LL Particle Status",10,0,10);
    mcLLPt_hist = new TH1D("mcLLPt_hist","Gen LL Particle p_{T}",200,0,200);
    mcLLEta_hist = new TH1D("mcLLEta_hist","Gen LL Particle #eta",120,-6,6);
    mcLLPhi_hist = new TH1D("mcLLPhi_hist","Gen LL Particle #phi",64,-3.2,3.2);
    mcLLCharge_hist = new TH1D("mcLLCharge_hist","Gen LL Particle Charge",6,-3,3);
    mcLLMass_hist = new TH1D("mcLLMass_hist","Gen LL Particle Mass",40,0,0.2);
    mcLLNDaughters_hist = new TH1D("mcLLNDaughters_hist","Number of Daughters of Gen LL Particles",10,0,10);
    mcLLDaughterId_hist = new TH1D("mcLLDaughterId_hist","Daughter Id of Gen LL Particles",50,-25,25);
    
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
    mcMuonPt_hist = new TH1D("mcMuonPt_hist","Gen Muon p_{T}",1000,0,1000);
    mcMuonEta_hist = new TH1D("mcMuonEta_hist","Gen Muon #eta",120,-6,6);
    mcMuonPhi_hist = new TH1D("mcMuonPhi_hist","Gen Muon #phi",64,-3.2,3.2);
    mcMuonCharge_hist = new TH1D("mcMuonCharge_hist","Gen Muon Charge",6,-3,3);
    mcMuonMass_hist = new TH1D("mcMuonMass_hist","Gen Muon Mass",40,0,0.2);
    mcMuonMotherId_hist = new TH1D("mcMuonMotherId_hist","Mother Id of Gen Muons",20000,-10000,10000);
    
    mcMuonPt_l1MuonPt_hist = new TH2D("mcMuonPt_l1MuonPt_hist","Gen Muon p_{T} vs. L1 Muon p_{T}",100,0,1000,100,0,1000);
    mcMuonPt_hlt20Cha2MuonPt_hist = new TH2D("mcMuonPt_hlt20Cha2MuonPt_hist","Gen Muon p_{T} vs. L2 Muon p_{T}",100,0,1000,100,0,1000);

    mcMuonEta_l1MuonEta_hist = new TH2D("mcMuonEta_l1MuonEta_hist","Gen Muon #eta vs. L1 Muon #eta",120,-6,6,120,-6,6);
    mcMuonPhi_l1MuonPhi_hist = new TH2D("mcMuonPhi_l1MuonPhi_hist","Gen Muon #phi vs. L1 Muon #phi",64,-3.2,3.2,64,-3.2,3.2);

    mcMuonEta_hlt20Cha2MuonEta_hist = new TH2D("mcMuonEta_hlt20Cha2MuonEta_hist","Gen Muon #eta vs. L2 Muon #eta",120,-6,6,120,-6,6);
    mcMuonPhi_hlt20Cha2MuonPhi_hist = new TH2D("mcMuonPhi_hlt20Cha2MuonPhi_hist","Gen Muon #phi vs. L2 Muon #phi",64,-3.2,3.2,64,-3.2,3.2);

    mcMuonPt_muStandAlonePt_hist = new TH2D("mcMuonPt_muStandAlonePt_hist","Gen Muon p_{T} vs. SA Muon p_{T}",100,0,1000,100,0,1000);
    mcMuonPt_muRefittedStandAlonePt_hist = new TH2D("mcMuonPt_muRefittedStandAlonePt_hist","Gen Muon p_{T} vs. Refitted SA Muon p_{T}",100,0,1000,100,0,1000);
    //mcMuonPt_muRefittedStandAlonePt_hist = new TH2D("mcMuonPt_muRefittedStandAlonePt_hist","Gen Muon p_{T} vs. Refitted SA Muon p_{T}",100,0,100,100,0,100);
    mcMuonPt_muCosmicPt_hist = new TH2D("mcMuonPt_muCosmicPt_hist","Gen Muon p_{T} vs. Cosmic Muon p_{T}",100,0,1000,100,0,1000);
    mcMuonPt_muCosmicTrackPt_hist = new TH2D("mcMuonPt_muCosmicTrackPt_hist","Gen Muon p_{T} vs. Cosmic Track p_{T}",100,0,1000,100,0,1000);

    muStandAlonePtResolution_hist = new TH1D("muStandAlonePtResolution_hist","SA Muon p_{T} Resolution",110,-10,1);
    muRefittedStandAlonePtResolution_hist = new TH1D("muRefittedStandAlonePtResolution_hist","RSA Muon p_{T} Resolution",110,-10,1);
    muCosmicPtResolution_hist = new TH1D("muCosmicPtResolution_hist","Cosmic Muon p_{T} Resolution",110,-10,1);

    muRefittedStandAlonePtResolution_muCosmicPtResolution_hist = new TH2D("muRefittedStandAlonePtResolution_muCosmicPtResolution_hist","RSA p_{T} Resolution vs Cosmic Muon p_{T} Resolution",110,-10,1,110,-10,1);

    muStandAloneNChambersDt_PtResolution_hist = new TH2D("muStandAloneNChambersDt_PtResolution_hist","SA Muon # of DT Chambers vs p_{T} Resolution",10,0,10,110,-10,1);
    muRefittedStandAloneNChambersDt_PtResolution_hist = new TH2D("muRefittedStandAloneNChambersDt_PtResolution_hist","Refitted SA Muon # of DT Chambers vs p_{T} Resolution",10,0,10,110,-10,1);
    muCosmicNChambersDt_PtResolution_hist = new TH2D("muCosmicNChambersDt_PtResolution_hist","Cosmic Muon # of DT Chambers vs p_{T} Resolution",10,0,10,110,-10,1);
    muStandAloneNChambersRpc_PtResolution_hist = new TH2D("muStandAloneNChambersRpc_PtResolution_hist","SA Muon # of RPC Chambers vs p_{T} Resolution",10,0,10,110,-10,1);
    muRefittedStandAloneNChambersRpc_PtResolution_hist = new TH2D("muRefittedStandAloneNChambersRpc_PtResolution_hist","Refitted SA Muon # of RPC Chambers vs p_{T} Resolution",10,0,10,110,-10,1);
    muCosmicNChambersRpc_PtResolution_hist = new TH2D("muCosmicNChambersRpc_PtResolution_hist","Cosmic Muon # of RPC Chambers vs p_{T} Resolution",10,0,10,110,-10,1);

    muStandAloneNChambersDt_Pt_hist = new TH2D("muStandAloneNChambersDt_Pt_hist","SA Muon # of DT Chambers vs p_{T} ",10,0,10,100,0,1000);
    muRefittedStandAloneNChambersDt_Pt_hist = new TH2D("muRefittedStandAloneNChambersDt_Pt_hist","Refitted SA Muon # of DT Chambers vs p_{T} ",10,0,10,100,0,1000);
    muCosmicNChambersDt_Pt_hist = new TH2D("muCosmicNChambersDt_Pt_hist","Cosmic Muon # of DT Chambers vs p_{T} ",10,0,10,100,0,1000);
    muStandAloneNChambersRpc_Pt_hist = new TH2D("muStandAloneNChambersRpc_Pt_hist","SA Muon # of RPC Chambers vs p_{T} ",10,0,10,100,0,1000);
    muRefittedStandAloneNChambersRpc_Pt_hist = new TH2D("muRefittedStandAloneNChambersRpc_Pt_hist","Refitted SA Muon # of RPC Chambers vs p_{T} ",10,0,10,100,0,1000);
    muCosmicNChambersRpc_Pt_hist = new TH2D("muCosmicNChambersRpc_Pt_hist","Cosmic Muon # of RPC Chambers vs p_{T} ",10,0,10,100,0,1000);

    muStandAlonePt_muCosmicTrackPt_hist = new TH2D("muStandAlonePt_muCosmicTrackPt_hist","SA Muon p_{T} vs. Cosmic Track p_{T}",100,0,1000,100,0,1000);
    //mcMuonPt_muStandAlonePt_hist = new TH2D("mcMuonPt_muStandAlonePt_hist","Gen Muon p_{T} vs. SA Muon p_{T}",100,0,100,100,0,100);
    mcMuonPt_muStandAlonePt_hist->SetTitle(";Generator Muon p_{T} [GeV];SA Muon p_{T} [GeV]");
    mcMuonPt_muRefittedStandAlonePt_hist->SetTitle(";Generator Muon p_{T} [GeV];Refitted SA Muon p_{T} [GeV]");
    mcMuonPt_muCosmicPt_hist->SetTitle(";Generator Muon p_{T} [GeV];Cosmic Muon p_{T} [GeV]");
    mcMuonPt_muCosmicTrackPt_hist->SetTitle(";Generator Muon p_{T} [GeV];Cosmic Track p_{T} [GeV]");
    mcMuonEta_muStandAloneEta_hist = new TH2D("mcMuonEta_muStandAloneEta_hist","Gen Muon #eta vs. SA Muon #eta",120,-6,6,120,-6,6);
    mcMuonPhi_muStandAlonePhi_hist = new TH2D("mcMuonPhi_muStandAlonePhi_hist","Gen Muon #phi vs. SA Muon #phi",64,-3.2,3.2,64,-3.2,3.2);

    muRefittedStandAloneNHitsDt_Pt_hist = new TH2D("muRefittedStandAloneNHitsDt_Pt_hist","",50,0,50,100,0,1000);
    //muRefittedStandAloneNChambersDt_Pt_hist = new TH2D("muRefittedStandAloneNChambersDt_Pt_hist","",5,0,5,100,0,1000);
    mcStoppedParticleR_muRefittedStandAlonePt_hist = new TH2D("mcStoppedParticleR_muRefittedStandAlonePt_hist","",80,0,800,100,0,1000);
    mcStoppedParticleR_mcMuonPt_hist = new TH2D("mcStoppedParticleR_mcMuonPt_hist","",80,0,800,100,0,1000);
    muStandAloneTrackDistanceStations_Pt_hist = new TH2D("muStandAloneTrackDistanceStations_Pt_hist","Distance between first and last Stations vs Pt",5,-1,4,100,0,1000);
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
    muPt_hist = new TH1D("muPt_hist","Reco Muon p_{T}",200,0,200);
    muEta_hist = new TH1D("muEta_hist","Reco Muon #eta",120,-6,6);
    muPhi_hist = new TH1D("muPhi_hist","Reco Muon #phi",64,-3.2,3.2);
    muType_hist = new TH1D("muType_hist","Reco Muon Type",4000,0,4000);
    muIso_hist = new TH1D("muIso_hist","Reco Muon Isolation",1000,0,1000);
    muEta_muPhi_hist = new TH2D("muEta_muPhi_hist","Reco Muon #eta vs #phi",120,-6,6,64,-3.2,3.2);
    
    diMu_N_hist = new TH1D("diMu_N_hist","Number of DiMuons",100,0,100);
    diMuMass_hist = new TH1D("diMuMass_hist","Reco Muon Invaraint Mass",1000,0,1000);
    
    muCosmic_N_hist = new TH1D("muCosmic_N_hist","Number of Cosmic Muons",100,0,100);
    muCosmicPt_hist = new TH1D("muCosmicPt_hist","Cosmic Muon p_{T}",1000,0,1000);
    muCosmicEta_hist = new TH1D("muCosmicEta_hist","Cosmic Muon #eta",120,-6,6);
    muCosmicPhi_hist = new TH1D("muCosmicPhi_hist","Cosmic Muon #phi",64,-3.2,3.2);
    muCosmicType_hist = new TH1D("muCosmicType_hist","Cosmic Muon Type",4000,0,4000);
    muCosmicEta_muCosmicPhi_hist = new TH2D("muCosmicEta_muCosmicPhi_hist","Cosmic Muon #eta vs #phi",120,-6,6,64,-3.2,3.2);
    
    muCosmicTrackInnerPt_hist = new TH1D("muCosmicTrackInnerPt_hist","Cosmic Track Muon Inner p_{T}",100,0,1000);

    muStandAlone_N_other_cut_hist = new TH1D("muStandAlone_N_other_cut_hist","Number of StandAlone Muons with #phi>0 and >1 stations",100,0,100);
    
    muStandAlone_N_hist = new TH1D("muStandAlone_N_hist","Number of StandAlone Muons",100,0,100);
    //muStandAlonePt_hist = new TH1D("muStandAlonePt_hist","StandAlone Muon p_{T}",200,0,200);
    muStandAlonePt_hist = new TH1D("muStandAlonePt_hist","StandAlone Muon p_{T}",1000,0,1000);
    muStandAloneEta_hist = new TH1D("muStandAloneEta_hist","StandAlone Muon #eta",120,-6,6);
    muStandAlonePhi_hist = new TH1D("muStandAlonePhi_hist","StandAlone Muon #phi",64,-3.2,3.2);
    muStandAloneTrackNormalizedChi2_hist = new TH1D("muStandAloneTrackNormalizedChi2_hist","StandAlone Muon Track #chi^{2}/dof",1000,0,100);
    muStandAloneTrackDxy_hist = new TH1D("muStandAloneTrackDxy_hist","StandAlone Muon Dxy",200,-100,100);
    muStandAloneTrackDz_hist = new TH1D("muStandAloneTrackDz_hist","StandAlone Muon Dz",200,-100,100);
    muStandAloneTrackNHitsMuon_hist = new TH1D("muStandAloneTrackNHitsMuon_hist","Hits in StandAlone Muon Track",100,0,100);
    muStandAloneTrackNHitsCsc_hist = new TH1D("muStandAloneTrackNHitsCsc_hist","CSC Hits in StandAlone Muon Track",100,0,100);
    muStandAloneTrackNHitsDt_hist = new TH1D("muStandAloneTrackNHitsDt_hist","DT Hits in StandAlone Muon Track",100,0,100);
    muStandAloneTrackNHitsRpc_hist = new TH1D("muStandAloneTrackNHitsRpc_hist","RPC Hits in StandAlone Muon Track",10,0,10);
    muStandAloneTrackNStations_hist = new TH1D("muStandAloneTrackNStations_hist","Muon Stations in StandAlone Muon Track",10,0,10);
    muStandAloneTrackNChambersCsc_hist = new TH1D("muStandAloneTrackNChambersCsc_hist","CSC Chambers in StandAlone Muon Track",10,0,10);
    muStandAloneTrackNChambersDt_hist = new TH1D("muStandAloneTrackNChambersDt_hist","DT Chambers in StandAlone Muon Track",10,0,10);
    muStandAloneTrackNChambersRpc_hist = new TH1D("muStandAloneTrackNChambersRpc_hist","RPC Chambers in StandAlone Muon Track",10,0,10);
    muStandAloneTrackDistanceStations_hist = new TH1D("muStandAloneTrackDistanceStations_hist","Distance between first and last Stations in StandAlone Muon Track",5,-1,4);
    muStandAloneTrackInnerPt_hist = new TH1D("muStandAloneTrackInnerPt_hist","StandAlone Track Muon Inner p_{T}",100,0,1000);
    muStandAloneTrackDtTofNDof_hist = new TH1D("muStandAloneTrackDtTofNDof_hist","StandAlone Muons TOF Number of Degrees of Freedom",40,0,40);
    muStandAloneTrackDtTofInverseBetaLS_hist = new TH1D("muStandAloneTrackDtTofInverseBetaLS_hist","LS #beta^{-1} of StandAlone Muons",10000,-10,10);
    muStandAloneTrackDtTofInverseBetaLSErr_hist = new TH1D("muStandAloneTrackDtTofInverseBetaLSErr_hist","Error of LS #beta^{-1} of StandAlone Muons",100,0,5);
    muStandAloneTrackDtTofYIntercept_hist = new TH1D("muStandAloneTrackDtTofYIntercept_hist","Y-Intercept of StandAlone Muons",200,-100,100);
    muStandAloneTrackDtTofYInterceptErr_hist = new TH1D("muStandAloneTrackDtTofYInterceptErr_hist","Y-Intercept Error of StandAlone Muons",100,0,100);
    muStandAloneTrackDtTofChi2Dof_hist = new TH1D("muStandAloneTrackDtTofChi2Dof_hist","chi2/dof of StandAlone Muons",500,0,500);
    muStandAloneBxPattern_hist = new TH1D("muStandAloneBxPattern_hist","StandAlone Muon RPC BX Pattern",9,0,9);
    muStandAloneNHitsRpcBxPattern0_hist = new TH1D("muStandAloneNHitsRpcBxPattern0_hist","Number of RPC Hits for BXs==0",10,0,10);

    muStandAloneOppositeSegDR_hist = new TH1D("muStandAloneOppositeSegDR_hist","dR to opp side seg",500,0,5);
    muStandAloneOppositeSegDEta_hist = new TH1D("muStandAloneOppositeSegDEta_hist","dEta to opp side seg",100,-2,2);
    muStandAloneOppositeSegDPhi_hist = new TH1D("muStandAloneOppositeSegDPhi_hist","dPhi to opp side seg",100,-5,5);

    muStandAloneTrackShowerSize_station0_hist = new TH1D("muStandAloneTrackShowerSize_station0_hist","Shower Size",100,0,50);
    muStandAloneTrackShowerSize_station1_hist = new TH1D("muStandAloneTrackShowerSize_station1_hist","Shower Size",100,0,50);
    muStandAloneTrackShowerSize_station2_hist = new TH1D("muStandAloneTrackShowerSize_station2_hist","Shower Size",100,0,50);
    muStandAloneTrackShowerSize_station3_hist = new TH1D("muStandAloneTrackShowerSize_station3_hist","Shower Size",100,0,50);
    muStandAloneTrackShowerDeltaR_station0_hist = new TH1D("muStandAloneTrackShowerDeltaR_station0_hist","Shower DeltaR",100,0,0.5);
    muStandAloneTrackShowerDeltaR_station1_hist = new TH1D("muStandAloneTrackShowerDeltaR_station1_hist","Shower DeltaR",100,0,0.5);
    muStandAloneTrackShowerDeltaR_station2_hist = new TH1D("muStandAloneTrackShowerDeltaR_station2_hist","Shower DeltaR",100,0,0.5);
    muStandAloneTrackShowerDeltaR_station3_hist = new TH1D("muStandAloneTrackShowerDeltaR_station3_hist","Shower DeltaR",100,0,0.5);
    muStandAloneTrackShowerNHits_station0_hist = new TH1D("muStandAloneTrackShowerNHits_station0_hist","N Hits",200,0,200);
    muStandAloneTrackShowerNHits_station1_hist = new TH1D("muStandAloneTrackShowerNHits_station1_hist","N Hits",200,0,200);
    muStandAloneTrackShowerNHits_station2_hist = new TH1D("muStandAloneTrackShowerNHits_station2_hist","N Hits",200,0,200);
    muStandAloneTrackShowerNHits_station3_hist = new TH1D("muStandAloneTrackShowerNHits_station3_hist","N Hits",200,0,200);
    muStandAloneTrackShowerNCorrelatedHits_station0_hist = new TH1D("muStandAloneTrackShowerNCorrelatedHits_station0_hist","N Correlated Hits",50,0,50);
    muStandAloneTrackShowerNCorrelatedHits_station1_hist = new TH1D("muStandAloneTrackShowerNCorrelatedHits_station1_hist","N Correlated Hits",50,0,50);
    muStandAloneTrackShowerNCorrelatedHits_station2_hist = new TH1D("muStandAloneTrackShowerNCorrelatedHits_station2_hist","N Correlated Hits",50,0,50);
    muStandAloneTrackShowerNCorrelatedHits_station3_hist = new TH1D("muStandAloneTrackShowerNCorrelatedHits_station3_hist","N Correlated Hits",50,0,50);
    muStandAloneTrackShowerNUncorrelatedHits_station0_hist = new TH1D("muStandAloneTrackShowerNUncorrelatedHits_station0_hist","N Uncorrelated Hits",200,0,200);
    muStandAloneTrackShowerNUncorrelatedHits_station1_hist = new TH1D("muStandAloneTrackShowerNUncorrelatedHits_station1_hist","N Uncorrelated Hits",200,0,200);
    muStandAloneTrackShowerNUncorrelatedHits_station2_hist = new TH1D("muStandAloneTrackShowerNUncorrelatedHits_station2_hist","N Uncorrelated Hits",200,0,200);
    muStandAloneTrackShowerNUncorrelatedHits_station3_hist = new TH1D("muStandAloneTrackShowerNUncorrelatedHits_station3_hist","N Uncorrelated Hits",200,0,200);

    muStandAloneUpperOnlyDEta_hist = new TH1D("muStandAloneUpperOnlyDEta_hist","dEta between Upper SAs",100,0,10);
    muStandAloneUpperOnlyDPhi_hist = new TH1D("muStandAloneUpperOnlyDPhi_hist","dPhi between Upper SAs",100,0,5);
    muStandAloneLowerOnlyDEta_hist = new TH1D("muStandAloneLowerOnlyDEta_hist","dEta between Lower SAs",100,0,10);
    muStandAloneLowerOnlyDPhi_hist = new TH1D("muStandAloneLowerOnlyDPhi_hist","dPhi between Lower SAs",100,0,5);
    
    muStandAloneNCscSegments_hist = new TH1D("muStandAloneNCscSegments_hist","",10,0,10);

    muStandAloneEta_muStandAlonePhi_hist = new TH2D("muStandAloneEta_muStandAlonePhi_hist","StandAlone Muon #eta vs #phi",120,-6,6,64,-3.2,3.2);
    muStandAloneTrackNHitsRpc_muStandAloneTrackNormalizedChi2_hist = new TH2D("muStandAloneTrackNHitsRpc_muStandAloneTrackNormalizedChi2_hist","RPC Hits vs Track #chi^{2}/dof",10,0,10,100,0,100);
    muStandAloneTrackNHitsRpc_muStandAloneTrackNHitsDt_hist = new TH2D("muStandAloneTrackNHitsRpc_muStandAloneTrackNHitsDt_hist","RPC Hits vs DT Hits",10,0,10,100,0,100);
    muStandAlonePt_muStandAloneTrackNChambersDt_hist = new TH2D("muStandAlonePt_muStandAloneTrackNChambersDt_hist","",200,0,200,5,0,5);


    //vector< vector<Int_t> > muStandAloneTrackCscSegEndcap;
    //vector< vector<Int_t> > muStandAloneTrackCscSegRing;
    //vector< vector<Int_t> > muStandAloneTrackCscSegStation;
    //vector< vector<Int_t> > muStandAloneTrackCscSegChamber;
    //vector< vector<Int_t> > muStandAloneTrackCscSegNHits;
    //vector< vector<Double_t> > muStandAloneTrackCscSegPhi;
    //vector< vector<Double_t> > muStandAloneTrackCscSegZ;
    //vector< vector<Double_t> > muStandAloneTrackCscSegR;
    //vector< vector<Double_t> > muStandAloneTrackCscSegDirPhi;
    //vector< vector<Double_t> > muStandAloneTrackCscSegDirTheta;
    //vector< vector<Int_t> > muStandAloneTrackCscSegNHits;
    //vector< vector<Double_t> > muStandAloneTrackCscSegPhi;
    //vector< vector<Double_t> > muStandAloneTrackCscSegZ;
    //vector< vector<Double_t> > muStandAloneTrackCscSegR;
    //vector< vector<Double_t> > muStandAloneTrackCscSegDirPhi;
    //vector< vector<Double_t> > muStandAloneTrackCscSegDirTheta;
    //vector< vector<Double_t> > muStandAloneTrackCscSegTime;
    //vector< vector<Double_t> > muStandAloneTrackRpcHitZ;
    //vector< vector<Double_t> > muStandAloneTrackRpcHitRho;
    //vector< vector<Double_t> > muStandAloneTrackRpcHitPhi;
    //vector< vector<Int_t> > muStandAloneTrackRpcHitRegion;
    //vector< vector<Int_t> > muStandAloneTrackRpcHitBx;

    Upper_StandAlone_N_hist = new TH1D("Upper_StandAlone_N_hist","Number of StandAlone Muons",100,0,100);
    Upper_StandAlonePt_hist = new TH1D("Upper_StandAlonePt_hist","StandAlone Muon p_{T}",200,0,200);
    Upper_StandAloneEta_hist = new TH1D("Upper_StandAloneEta_hist","StandAlone Muon #eta",120,-6,6);
    Upper_StandAlonePhi_hist = new TH1D("Upper_StandAlonePhi_hist","StandAlone Muon #phi",64,-3.2,3.2);
    Upper_StandAloneTrackNormalizedChi2_hist = new TH1D("Upper_StandAloneTrackNormalizedChi2_hist","StandAlone Muon Track #chi^{2}/dof",1000,0,100);
    Upper_StandAloneTrackDxy_hist = new TH1D("Upper_StandAloneTrackDxy_hist","StandAlone Muon Dxy",200,-100,100);
    Upper_StandAloneTrackDz_hist = new TH1D("Upper_StandAloneTrackDz_hist","StandAlone Muon Dz",200,-100,100);
    Upper_StandAloneTrackNHitsMuon_hist = new TH1D("Upper_StandAloneTrackNHitsMuon_hist","Hits in StandAlone Muon Track",100,0,100);
    Upper_StandAloneTrackNHitsCsc_hist = new TH1D("Upper_StandAloneTrackNHitsCsc_hist","CSC Hits in StandAlone Muon Track",100,0,100);
    Upper_StandAloneTrackNHitsDt_hist = new TH1D("Upper_StandAloneTrackNHitsDt_hist","DT Hits in StandAlone Muon Track",100,0,100);
    Upper_StandAloneTrackNHitsRpc_hist = new TH1D("Upper_StandAloneTrackNHitsRpc_hist","RPC Hits in StandAlone Muon Track",10,0,10);
    Upper_StandAloneTrackNStations_hist = new TH1D("Upper_StandAloneTrackNStations_hist","Muon Stations in StandAlone Muon Track",10,0,10);
    Upper_StandAloneTrackNChambersCsc_hist = new TH1D("Upper_StandAloneTrackNChambersCsc_hist","CSC Chambers in StandAlone Muon Track",10,0,10);
    Upper_StandAloneTrackNChambersDt_hist = new TH1D("Upper_StandAloneTrackNChambersDt_hist","DT Chambers in StandAlone Muon Track",10,0,10);
    Upper_StandAloneTrackNChambersRpc_hist = new TH1D("Upper_StandAloneTrackNChambersRpc_hist","RPC Chambers in StandAlone Muon Track",10,0,10);
    Upper_StandAloneTrackNHitsRpc_Upper_StandAloneTrackNormalizedChi2_hist = new TH2D("Upper_StandAloneTrackNHitsRpc_Upper_StandAloneTrackNormalizedChi2_hist","RPC Hits vs Track #chi^{2}/dof",10,0,10,100,0,100);
    Upper_StandAloneTrackNHitsRpc_Upper_StandAloneTrackNHitsDt_hist = new TH2D("Upper_StandAloneTrackNHitsRpc_Upper_StandAloneTrackNHitsDt_hist","RPC Hits vs DT Hits",10,0,10,100,0,100);
    Upper_StandAloneTrackDtTofNDof_hist = new TH1D("Upper_StandAloneTrackDtTofNDof_hist","StandAlone Muons TOF Number of Degrees of Freedom",40,0,40);
    Upper_StandAloneTrackDtTofInverseBetaLS_hist = new TH1D("Upper_StandAloneTrackDtTofInverseBetaLS_hist","LS #beta^{-1} of StandAlone Muons",10000,-10,10);
    Upper_StandAloneTrackDtTofInverseBetaLSErr_hist = new TH1D("Upper_StandAloneTrackDtTofInverseBetaLSErr_hist","Error of LS #beta^{-1} of StandAlone Muons",100,0,5);
    Upper_StandAloneTrackDtTofYIntercept_hist = new TH1D("Upper_StandAloneTrackDtTofYIntercept_hist","Y-Intercept of StandAlone Muons",200,-100,100);
    Upper_StandAloneTrackDtTofYInterceptErr_hist = new TH1D("Upper_StandAloneTrackDtTofYInterceptErr_hist","Y-Intercept Error of StandAlone Muons",100,0,100);
    Upper_StandAloneTrackDtTofChi2Dof_hist = new TH1D("Upper_StandAloneTrackDtTofChi2Dof_hist","chi2/dof of StandAlone Muons",500,0,500);
    Upper_muStandAloneBxPattern_hist = new TH1D("Upper_muStandAloneBxPattern_hist","Upper StandAlone Muon RPC BX Pattern",9,0,9);
    Upper_muStandAloneNHitsRpcBxPattern0_hist = new TH1D("Upper_muStandAloneNHitsRpcBxPattern0_hist","Number of RPC Hits for BXs==0 and Upper",10,0,10);    
        
    Lower_StandAlone_N_hist = new TH1D("Lower_StandAlone_N_hist","Number of StandAlone Muons",100,0,100);
    Lower_StandAlonePt_hist = new TH1D("Lower_StandAlonePt_hist","StandAlone Muon p_{T}",200,0,200);
    Lower_StandAloneEta_hist = new TH1D("Lower_StandAloneEta_hist","StandAlone Muon #eta",120,-6,6);
    Lower_StandAlonePhi_hist = new TH1D("Lower_StandAlonePhi_hist","StandAlone Muon #phi",64,-3.2,3.2);
    Lower_StandAloneTrackNormalizedChi2_hist = new TH1D("Lower_StandAloneTrackNormalizedChi2_hist","StandAlone Muon Track #chi^{2}/dof",1000,0,100);
    Lower_StandAloneTrackDxy_hist = new TH1D("Lower_StandAloneTrackDxy_hist","StandAlone Muon Dxy",200,-100,100);
    Lower_StandAloneTrackDz_hist = new TH1D("Lower_StandAloneTrackDz_hist","StandAlone Muon Dz",200,-100,100);
    Lower_StandAloneTrackNHitsMuon_hist = new TH1D("Lower_StandAloneTrackNHitsMuon_hist","Hits in StandAlone Muon Track",100,0,100);
    Lower_StandAloneTrackNHitsCsc_hist = new TH1D("Lower_StandAloneTrackNHitsCsc_hist","CSC Hits in StandAlone Muon Track",100,0,100);
    Lower_StandAloneTrackNHitsDt_hist = new TH1D("Lower_StandAloneTrackNHitsDt_hist","DT Hits in StandAlone Muon Track",100,0,100);
    Lower_StandAloneTrackNHitsRpc_hist = new TH1D("Lower_StandAloneTrackNHitsRpc_hist","RPC Hits in StandAlone Muon Track",10,0,10);
    Lower_StandAloneTrackNStations_hist = new TH1D("Lower_StandAloneTrackNStations_hist","Muon Stations in StandAlone Muon Track",10,0,10);
    Lower_StandAloneTrackNChambersCsc_hist = new TH1D("Lower_StandAloneTrackNChambersCsc_hist","CSC Chambers in StandAlone Muon Track",10,0,10);
    Lower_StandAloneTrackNChambersDt_hist = new TH1D("Lower_StandAloneTrackNChambersDt_hist","DT Chambers in StandAlone Muon Track",10,0,10);
    Lower_StandAloneTrackNChambersRpc_hist = new TH1D("Lower_StandAloneTrackNChambersRpc_hist","RPC Chambers in StandAlone Muon Track",10,0,10);
    Lower_StandAloneTrackNHitsRpc_Lower_StandAloneTrackNormalizedChi2_hist = new TH2D("Lower_StandAloneTrackNHitsRpc_Lower_StandAloneTrackNormalizedChi2_hist","RPC Hits vs Track #chi^{2}/dof",10,0,10,100,0,100);
    Lower_StandAloneTrackNHitsRpc_Lower_StandAloneTrackNHitsDt_hist = new TH2D("Lower_StandAloneTrackNHitsRpc_Lower_StandAloneTrackNHitsDt_hist","RPC Hits vs DT Hits",10,0,10,100,0,100);
    Lower_StandAloneTrackDtTofNDof_hist = new TH1D("Lower_StandAloneTrackDtTofNDof_hist","StandAlone Muons TOF Number of Degrees of Freedom",40,0,40);
    Lower_StandAloneTrackDtTofInverseBetaLS_hist = new TH1D("Lower_StandAloneTrackDtTofInverseBetaLS_hist","LS #beta^{-1} of StandAlone Muons",10000,-10,10);
    Lower_StandAloneTrackDtTofInverseBetaLSErr_hist = new TH1D("Lower_StandAloneTrackDtTofInverseBetaLSErr_hist","Error of LS #beta^{-1} of StandAlone Muons",100,0,5);
    Lower_StandAloneTrackDtTofYIntercept_hist = new TH1D("Lower_StandAloneTrackDtTofYIntercept_hist","Y-Intercept of StandAlone Muons",200,-100,100);
    Lower_StandAloneTrackDtTofYInterceptErr_hist = new TH1D("Lower_StandAloneTrackDtTofYInterceptErr_hist","Y-Intercept Error of StandAlone Muons",100,0,100);
    Lower_StandAloneTrackDtTofChi2Dof_hist = new TH1D("Lower_StandAloneTrackDtTofChi2Dof_hist","chi2/dof of StandAlone Muons",500,0,500);
    Lower_muStandAloneBxPattern_hist = new TH1D("Lower_muStandAloneBxPattern_hist","Lower StandAlone Muon RPC BX Pattern",9,0,9);
    Lower_muStandAloneNHitsRpcBxPattern0_hist = new TH1D("Lower_muStandAloneNHitsRpcBxPattern0_hist","Number of RPC Hits for BXs==0 and Lower",10,0,10);

    Upper_StandAloneTofTimeAtIpInOut_hist = new TH1D("Upper_StandAloneTofTimeAtIpInOut_hist","Time at IP InOut of First StandAlone Muon",300,-50,100);
    Upper_StandAloneTofTimeAtIpOutIn_hist = new TH1D("Upper_StandAloneTofTimeAtIpOutIn_hist","Time at IP OutIn of First StandAlone Muon",300,0,150);
    Lower_StandAloneTofTimeAtIpInOut_hist = new TH1D("Lower_StandAloneTofTimeAtIpInOut_hist","Time at IP InOut of Second StandAlone Muon",300,-50,100);
    Lower_StandAloneTofTimeAtIpOutIn_hist = new TH1D("Lower_StandAloneTofTimeAtIpOutIn_hist","Time at IP OutIn of Second StandAlone Muon",300,0,150);
    mudiff_StandAloneTofTimeAtIpInOut_hist = new TH1D("mudiff_StandAloneTofTimeAtIpInOut_hist","Time at IP InOut of First minus Second StandAlone Muon",300,-50,100);
    mudiff_StandAloneTofTimeAtIpOutIn_hist = new TH1D("mudiff_StandAloneTofTimeAtIpOutIn_hist","Time at IP OutIn of First minus Second StandAlone Muon",300,0,150);
    Upper_Lower_StandAloneTofTimeAtIpInOut_hist = new TH2D("Upper_Lower_StandAloneTofTimeAtIpInOut_hist","Time at IP InOut of First vs Second StandAlone Muon",300,-50,100,300,-50,100);
    Upper_Lower_StandAloneTofTimeAtIpOutIn_hist = new TH2D("Upper_Lower_StandAloneTofTimeAtIpOutIn_hist","Time at IP OutIn of First vs Second StandAlone Muon",300,0,150,300,0,150);
    
    muRefittedStandAlone_N_hist = new TH1D("muRefittedStandAlone_N_hist","Number of Refitted StandAlone Muons",100,0,100);
    //muRefittedStandAlonePt_hist = new TH1D("muRefittedStandAlonePt_hist","Refitted StandAlone Muon p_{T}",200,0,200);
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
    muStandAloneTofTimeAtIpInOut_hist = new TH1D("muStandAloneTofTimeAtIpInOut_hist","Time at IP InOut of StandAlone Muons",300,-50,100);
    muStandAloneTofTimeAtIpInOutErr_hist = new TH1D("muStandAloneTofTimeAtIpInOutErr_hist","Error of Time at IP InOut of StandAlone Muons",100,0,20);
    muStandAloneTofTimeAtIpOutIn_hist = new TH1D("muStandAloneTofTimeAtIpOutIn_hist","Time at IP OutIn of StandAlone Muons",300,0,150);
    muStandAloneTofTimeAtIpOutInErr_hist = new TH1D("muStandAloneTofTimeAtIpOutInErr_hist","Error of Time at IP OutIn of StandAlone Muons",100,0,20);
    
    muStandAloneDTTof_N_hist = new TH1D("muStandAloneDTTof_N_hist","Number of StandAlone Muons in TOF Calculation",100,0,100);
    muStandAloneDTTofDirection_hist = new TH1D("muStandAloneDTTofDirection_hist","Direction of StandAlone Muons",3,-1,2);
    muStandAloneDTTofNDof_hist = new TH1D("muStandAloneDTTofNDof_hist","StandAlone Muons TOF Number of Degrees of Freedom",200,0,200);
    muStandAloneDTTofInverseBeta_hist = new TH1D("muStandAloneDTTofInverseBeta_hist","#beta^{-1} of StandAlone Muons",1000,-5,5);
    muStandAloneDTTofInverseBetaErr_hist = new TH1D("muStandAloneDTTofInverseBetaErr_hist","Error of #beta^{-1} of StandAlone Muons",10000,0,1000);
    muStandAloneDTTofFreeInverseBeta_hist = new TH1D("muStandAloneDTTofFreeInverseBeta_hist","Free #beta^{-1} of StandAlone Muons",1000,-50,50);
    muStandAloneDTTofFreeInverseBetaErr_hist = new TH1D("muStandAloneDTTofFreeInverseBetaErr_hist","Error of Free #beta^{-1} of StandAlone Muons",10000,0,1000);
    muStandAloneDTTofTimeAtIpInOut_hist = new TH1D("muStandAloneDTTofTimeAtIpInOut_hist","Time at IP InOut of StandAlone Muons",300,-50,100);
    muStandAloneDTTofTimeAtIpInOutErr_hist = new TH1D("muStandAloneDTTofTimeAtIpInOutErr_hist","Error of Time at IP InOut of StandAlone Muons",100,0,20);
    muStandAloneDTTofTimeAtIpOutIn_hist = new TH1D("muStandAloneDTTofTimeAtIpOutIn_hist","Time at IP OutIn of StandAlone Muons",300,0,150);
    muStandAloneDTTofTimeAtIpOutInErr_hist = new TH1D("muStandAloneDTTofTimeAtIpOutInErr_hist","Error of Time at IP OutIn of StandAlone Muons",100,0,20);
    
    muStandAloneCSCTof_N_hist = new TH1D("muStandAloneCSCTof_N_hist","Number of StandAlone Muons in TOF Calculation",100,0,100);
    muStandAloneCSCTofDirection_hist = new TH1D("muStandAloneCSCTofDirection_hist","Direction of StandAlone Muons",3,-1,2);
    muStandAloneCSCTofNDof_hist = new TH1D("muStandAloneCSCTofNDof_hist","StandAlone Muons TOF Number of Degrees of Freedom",200,0,200);
    muStandAloneCSCTofInverseBeta_hist = new TH1D("muStandAloneCSCTofInverseBeta_hist","#beta^{-1} of StandAlone Muons",1000,-5,5);
    muStandAloneCSCTofInverseBetaErr_hist = new TH1D("muStandAloneCSCTofInverseBetaErr_hist","Error of #beta^{-1} of StandAlone Muons",10000,0,1000);
    muStandAloneCSCTofFreeInverseBeta_hist = new TH1D("muStandAloneCSCTofFreeInverseBeta_hist","Free #beta^{-1} of StandAlone Muons",1000,-50,50);
    muStandAloneCSCTofFreeInverseBetaErr_hist = new TH1D("muStandAloneCSCTofFreeInverseBetaErr_hist","Error of Free #beta^{-1} of StandAlone Muons",10000,0,1000);
    muStandAloneCSCTofTimeAtIpInOut_hist = new TH1D("muStandAloneCSCTofTimeAtIpInOut_hist","Time at IP InOut of StandAlone Muons",300,-50,100);
    muStandAloneCSCTofTimeAtIpInOutErr_hist = new TH1D("muStandAloneCSCTofTimeAtIpInOutErr_hist","Error of Time at IP InOut of StandAlone Muons",100,0,20);
    muStandAloneCSCTofTimeAtIpOutIn_hist = new TH1D("muStandAloneCSCTofTimeAtIpOutIn_hist","Time at IP OutIn of StandAlone Muons",300,0,150);
    muStandAloneCSCTofTimeAtIpOutInErr_hist = new TH1D("muStandAloneCSCTofTimeAtIpOutInErr_hist","Error of Time at IP OutIn of StandAlone Muons",100,0,20);
    
    refitMuStandAloneTof_N_hist = new TH1D("refitMuStandAloneTof_N_hist","Number of StandAlone Muons in TOF Calculation with recoed DTs",100,0,100);
    refitMuStandAloneTofDirection_hist = new TH1D("refitMuStandAloneTofDirection_hist","Direction of StandAlone Muons with recoed DTs",3,-1,2);
    refitMuStandAloneTofNDof_hist = new TH1D("refitMuStandAloneTofNDof_hist","StandAlone Muons TOF Number of Degrees of Freedom with recoed DTs",200,0,200);
    refitMuStandAloneTofInverseBeta_hist = new TH1D("refitMuStandAloneTofInverseBeta_hist","#beta^{-1} of StandAlone Muons with recoed DTs",1000,-5,5);
    refitMuStandAloneTofInverseBetaErr_hist = new TH1D("refitMuStandAloneTofInverseBetaErr_hist","Error of #beta^{-1} of StandAlone Muons with recoed DTs",10000,0,1000);
    refitMuStandAloneTofFreeInverseBeta_hist = new TH1D("refitMuStandAloneTofFreeInverseBeta_hist","Free #beta^{-1} of StandAlone Muons with recoed DTs",1000,-50,50);
    refitMuStandAloneTofFreeInverseBetaErr_hist = new TH1D("refitMuStandAloneTofFreeInverseBetaErr_hist","Error of Free #beta^{-1} of StandAlone Muons with recoed DTs",10000,0,1000);
    refitMuStandAloneTofTimeAtIpInOut_hist = new TH1D("refitMuStandAloneTofTimeAtIpInOut_hist","Time at IP InOut of StandAlone Muons with recoed DTs",300,-50,100);
    refitMuStandAloneTofTimeAtIpInOutErr_hist = new TH1D("refitMuStandAloneTofTimeAtIpInOutErr_hist","Error of Time at IP InOut of StandAlone Muons with recoed DTs",100,0,20);
    refitMuStandAloneTofTimeAtIpOutIn_hist = new TH1D("refitMuStandAloneTofTimeAtIpOutIn_hist","Time at IP OutIn of StandAlone Muons with recoed DTs",300,0,150);
    refitMuStandAloneTofTimeAtIpOutInErr_hist = new TH1D("refitMuStandAloneTofTimeAtIpOutInErr_hist","Error of Time at IP OutIn of StandAlone Muons with recoed DTs",100,0,20);
    
    refitMuStandAloneDTTof_N_hist = new TH1D("refitMuStandAloneDTTof_N_hist","Number of StandAlone Muons in TOF Calculation with recoed DTs",100,0,100);
    refitMuStandAloneDTTofDirection_hist = new TH1D("refitMuStandAloneDTTofDirection_hist","Direction of StandAlone Muons with recoed DTs",3,-1,2);
    refitMuStandAloneDTTofNDof_hist = new TH1D("refitMuStandAloneDTTofNDof_hist","StandAlone Muons TOF Number of Degrees of Freedom with recoed DTs",200,0,200);
    refitMuStandAloneDTTofInverseBeta_hist = new TH1D("refitMuStandAloneDTTofInverseBeta_hist","#beta^{-1} of StandAlone Muons with recoed DTs",1000,-5,5);
    refitMuStandAloneDTTofInverseBetaErr_hist = new TH1D("refitMuStandAloneDTTofInverseBetaErr_hist","Error of #beta^{-1} of StandAlone Muons with recoed DTs",10000,0,1000);
    refitMuStandAloneDTTofFreeInverseBeta_hist = new TH1D("refitMuStandAloneDTTofFreeInverseBeta_hist","Free #beta^{-1} of StandAlone Muons with recoed DTs",1000,-50,50);
    refitMuStandAloneDTTofFreeInverseBetaErr_hist = new TH1D("refitMuStandAloneDTTofFreeInverseBetaErr_hist","Error of Free #beta^{-1} of StandAlone Muons with recoed DTs",10000,0,1000);
    refitMuStandAloneDTTofTimeAtIpInOut_hist = new TH1D("refitMuStandAloneDTTofTimeAtIpInOut_hist","Time at IP InOut of StandAlone Muons with recoed DTs",300,-50,100);
    refitMuStandAloneDTTofTimeAtIpInOutErr_hist = new TH1D("refitMuStandAloneDTTofTimeAtIpInOutErr_hist","Error of Time at IP InOut of StandAlone Muons with recoed DTs",100,0,20);
    refitMuStandAloneDTTofTimeAtIpOutIn_hist = new TH1D("refitMuStandAloneDTTofTimeAtIpOutIn_hist","Time at IP OutIn of StandAlone Muons with recoed DTs",300,0,150);
    refitMuStandAloneDTTofTimeAtIpOutInErr_hist = new TH1D("refitMuStandAloneDTTofTimeAtIpOutInErr_hist","Error of Time at IP OutIn of StandAlone Muons with recoed DTs",100,0,20);
    
    refitMuStandAloneCSCTof_N_hist = new TH1D("refitMuStandAloneCSCTof_N_hist","Number of StandAlone Muons in TOF Calculation with recoed DTs",100,0,100);
    refitMuStandAloneCSCTofDirection_hist = new TH1D("refitMuStandAloneCSCTofDirection_hist","Direction of StandAlone Muons with recoed DTs",3,-1,2);
    refitMuStandAloneCSCTofNDof_hist = new TH1D("refitMuStandAloneCSCTofNDof_hist","StandAlone Muons TOF Number of Degrees of Freedom with recoed DTs",200,0,200);
    refitMuStandAloneCSCTofInverseBeta_hist = new TH1D("refitMuStandAloneCSCTofInverseBeta_hist","#beta^{-1} of StandAlone Muons with recoed DTs",1000,-5,5);
    refitMuStandAloneCSCTofInverseBetaErr_hist = new TH1D("refitMuStandAloneCSCTofInverseBetaErr_hist","Error of #beta^{-1} of StandAlone Muons with recoed DTs",10000,0,1000);
    refitMuStandAloneCSCTofFreeInverseBeta_hist = new TH1D("refitMuStandAloneCSCTofFreeInverseBeta_hist","Free #beta^{-1} of StandAlone Muons with recoed DTs",1000,-50,50);
    refitMuStandAloneCSCTofFreeInverseBetaErr_hist = new TH1D("refitMuStandAloneCSCTofFreeInverseBetaErr_hist","Error of Free #beta^{-1} of StandAlone Muons with recoed DTs",10000,0,1000);
    refitMuStandAloneCSCTofTimeAtIpInOut_hist = new TH1D("refitMuStandAloneCSCTofTimeAtIpInOut_hist","Time at IP InOut of StandAlone Muons with recoed DTs",300,-50,100);
    refitMuStandAloneCSCTofTimeAtIpInOutErr_hist = new TH1D("refitMuStandAloneCSCTofTimeAtIpInOutErr_hist","Error of Time at IP InOut of StandAlone Muons with recoed DTs",100,0,20);
    refitMuStandAloneCSCTofTimeAtIpOutIn_hist = new TH1D("refitMuStandAloneCSCTofTimeAtIpOutIn_hist","Time at IP OutIn of StandAlone Muons with recoed DTs",300,0,150);
    refitMuStandAloneCSCTofTimeAtIpOutInErr_hist = new TH1D("refitMuStandAloneCSCTofTimeAtIpOutInErr_hist","Error of Time at IP OutIn of StandAlone Muons with recoed DTs",100,0,20);
    
    DTSegment_N_hist = new TH1D("DTSegment_N_hist","Number of DT Segments",100,0,100);
        
  }
  
  ~findTreevalues_makehistos_Ntuples_allsamples() {};
  
  virtual void loop(string& file_dataset, string& BxCut, string& CavCut, string& GenMuCut, string& SACut, string& GenMuMatchedCut, string& TriggerCut, string& PtCut, string& ChaCut, string& EtaCut, string& UpperCut, string& RpcCut, string& DisStCut, string& RpcBxCut, string& DtHitsCut, string& CscHitsCut, string& DtInvBetaCut, string& TimeInOutCut, string& OppEtaCut, string& OppPhiCut, string& TightPhi, string& CosEnrich, string& resT3, string& Printout, TString& BxCutValue, TString& PtCutValue, TString& Pt0CutValue, TString& Pt1CutValue, TString& ChaCutValue, TString& EtaCutValue, TString& RpcCutValue, TString& DisStCutValue, TString& DtHitsCutValue, TString& CscHitsCutValue, TString& DtInvBetaCutValue, TString& TimeInOutCutValue, TString& OppEtaCutValue, TString& OppPhiCutValue);

private:
  void stops( StoppedHSCPMuonEvent*, bool&, bool&, bool&, bool&);
  void gluinos( StoppedHSCPMuonEvent*, bool&, bool&, bool&, bool&, bool&, bool&, bool&, bool&, bool&, bool&, bool&);
  void mchamps( StoppedHSCPMuonEvent*, bool&, bool (&)[15], bool (&)[15], bool (&)[15], int&, double&, double&, double&, double&, double&, double&, double&, double&, double&, double&, double&, double&, double&, double&, double&, double&, Double_t&, double&, double&, double&, double&, double&, double&, double&, double&, double&, double&, double&, double&, double&, double&, double&, double&);
  void staus( StoppedHSCPMuonEvent*, bool&, bool&, bool&, bool&, bool&);
  void stop_counts( StoppedHSCPMuonEvent*, bool&, bool&, bool&, bool&);
  void gluino_counts( StoppedHSCPMuonEvent*, bool&, bool&, bool&, bool&, bool&, bool&, bool&, bool&, bool&, bool&, bool&);
  void mchamp_counts( StoppedHSCPMuonEvent*, int&, double&, double&);
  void stau_counts( StoppedHSCPMuonEvent*, bool&, bool&, bool&);

  void StoppedParticles( StoppedHSCPMuonEvent*);
  void StoppingRegionAcceptance( StoppedHSCPMuonEvent*);

  bool genMuonMatched( StoppedHSCPMuonEvent*);
  bool multipleMuons_PtCut( StoppedHSCPMuonEvent* );
  bool diMuMass_Cut( StoppedHSCPMuonEvent* );

  int Rpc_Bx_Pattern( StoppedHSCPMuonEvent*, UInt_t&);
  double dR_OppositeSeg( StoppedHSCPMuonEvent*, UInt_t&, double&, double& );
  int distanceBetweenStations( StoppedHSCPMuonEvent*, UInt_t&, bool&);

  void HighestPtSA_counts( StoppedHSCPMuonEvent*, float&, Int_t&, float&, UInt_t&, Int_t&, Int_t&, Int_t&, float&, float&, float&, float&);
  void pick_UpperAndLowerSA( StoppedHSCPMuonEvent*, UInt_t&, UInt_t&, float&, float&);
  void UpperAndLowerSA_counts( StoppedHSCPMuonEvent*, string&, float&, float&, Int_t&, float&, UInt_t&,  Int_t&, Int_t&, float&, float&);

  void printout_setup(StoppedHSCPMuonEvent*);
  void printout_gen(StoppedHSCPMuonEvent*);
  void printout_SA(StoppedHSCPMuonEvent*);
  void printout_RSA(StoppedHSCPMuonEvent*);
  void printout_cosmic(StoppedHSCPMuonEvent*);
  void printout_L2(StoppedHSCPMuonEvent*);
  void printout_L1(StoppedHSCPMuonEvent*);

  bool doBxCut, doCavCut, doGenMuCut, doSACut, doGenMuMatchedCut, doTriggerCut, doPtCut, doChaCut, doEtaCut, doUpperCut, doRpcCut, doDisStCut, doRpcBxCut, doDtHitsCut, doCscHitsCut, doDtInvBetaCut, doTimeInOutCut, doOppEtaCut, doOppPhiCut, doTightPhi, doCosEnrich, doPrintout;
  UInt_t RpcCutValue_;
  Int_t DisStCutValue_, BxCutValue_, ChaCutValue_, DtHitsCutValue_, CscHitsCutValue_;
  float PtCutValue_, Pt0CutValue_, Pt1CutValue_, EtaCutValue_, DtInvBetaCutValue_, TimeInOutCutValue_, OppEtaCutValue_, OppPhiCutValue_;

  int tracker_count_, eb_count_, ee_count_, hb_count_, he_count_, mb_count_, me_count_, other_detector_count_, cavern_count_, detector_count_;
  int tracker_AccCount_, eb_AccCount_, ee_AccCount_, hb_AccCount_, he_AccCount_, mb_AccCount_, me_AccCount_, other_detector_AccCount_, cavern_AccCount_, detector_AccCount_;
  int pass_bx_cut, pass_cavern_cut,
    pass_Ntops_cut, pass_Nstops_cut, pass_Ngluinos_cut, pass_Nmchamps_cut, pass_Nstaus_cut, pass_tauFromStau_cut, pass_WFromTop_cut, pass_muon_cut, pass_status1muon_cut, pass_status1muonFromW_cut, pass_status1muonFromTau_cut, pass_status1muonFromMuon_cut, pass_status1muonFromBbaryon_cut, pass_status1muonFromCbaryon_cut, pass_status1muonFromSbaryon_cut, pass_status1muonFromBmeson_cut, pass_status1muonFromCmeson_cut, pass_status1muonFromJPsi_cut, pass_status1muonFromLightMeson_cut, 
    pass_generatorMuon_cut, pass_standaloneMuon_cut, pass_genMuonMatched_cut, pass_trigger_cut, 
    pass_pt_cut, pass_cha_cut, pass_eta_cut, pass_Upper_cut, pass_RPC_cut, pass_DisSt_cut, pass_Rpc_Bx_cut, pass_DtHits_cut, pass_CscHits_cut, pass_DtInvBeta_cut, pass_TimeInOut_cut, pass_OppEta_cut, pass_OppPhi_cut,
    pass_SA_2_cut, pass_UpperAndLower_cut, pass_UpperOnly_cut, pass_LowerOnly_cut, pass_pt_2_cut, pass_UpperAndLower_pt30_cut, pass_cha_2_cut, pass_eta_2_cut, pass_RPC_2_cut, pass_DisSt_2_cut, pass_Rpc_Bx_2_cut, pass_DtHits_2_cut, pass_DtInvBeta_2_cut, pass_TimeInOut_2_cut, pass_OppEta_2_cut, pass_OppPhi_2_cut;
  int PtPrecision, EtaPrecision, PhiPrecision, ChargePrecision, X2DOFPrecision, TimeAtIpInOutPrecision, line;

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
  TH1D* mcStoppedParticlePhi_hist;
  TH2D* mcStoppedParticleXY_hist; 
  TH2D* mcStoppedParticleR_muStandAloneEta_hist;

  TH1D* mcLL_N_hist;
  TH1D* mcLLStatus_hist;
  TH1D* mcLLPt_hist; 
  TH1D* mcLLEta_hist;
  TH1D* mcLLPhi_hist;
  TH1D* mcLLCharge_hist;
  TH1D* mcLLMass_hist;
  TH1D* mcLLNDaughters_hist;
  TH1D* mcLLDaughterId_hist;

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
  TH1D* mcMuonPt_hist;
  TH1D* mcMuonEta_hist;
  TH1D* mcMuonPhi_hist;
  TH1D* mcMuonCharge_hist;
  TH1D* mcMuonMass_hist;
  TH1D* mcMuonMotherId_hist;

  TH2D* mcMuonPt_muStandAlonePt_hist;
  TH2D* mcMuonPt_muRefittedStandAlonePt_hist;
  TH2D* mcMuonPt_muCosmicPt_hist;
  TH2D* mcMuonPt_muCosmicTrackPt_hist;
  TH2D* muStandAlonePt_muCosmicTrackPt_hist;
  TH2D* mcMuonEta_muStandAloneEta_hist;
  TH2D* mcMuonPhi_muStandAlonePhi_hist;

  TH2D* mcMuonPt_l1MuonPt_hist;
  TH2D* mcMuonPt_hlt20Cha2MuonPt_hist;
  TH2D* mcMuonEta_l1MuonEta_hist;
  TH2D* mcMuonPhi_l1MuonPhi_hist;
  TH2D* mcMuonEta_hlt20Cha2MuonEta_hist;
  TH2D* mcMuonPhi_hlt20Cha2MuonPhi_hist;

  TH1D* muStandAlonePtResolution_hist;
  TH1D* muRefittedStandAlonePtResolution_hist;
  TH1D* muCosmicPtResolution_hist;

  TH2D* muRefittedStandAlonePtResolution_muCosmicPtResolution_hist;

  TH2D* muStandAloneNChambersDt_PtResolution_hist;
  TH2D* muRefittedStandAloneNChambersDt_PtResolution_hist;
  TH2D* muCosmicNChambersDt_PtResolution_hist;
  TH2D* muStandAloneNChambersRpc_PtResolution_hist;
  TH2D* muRefittedStandAloneNChambersRpc_PtResolution_hist;
  TH2D* muCosmicNChambersRpc_PtResolution_hist;

  TH2D* muStandAloneNChambersDt_Pt_hist;
  TH2D* muRefittedStandAloneNChambersDt_Pt_hist;
  TH2D* muCosmicNChambersDt_Pt_hist;
  TH2D* muStandAloneNChambersRpc_Pt_hist;
  TH2D* muRefittedStandAloneNChambersRpc_Pt_hist;
  TH2D* muCosmicNChambersRpc_Pt_hist;
  
  TH2D* muRefittedStandAloneNHitsDt_Pt_hist;
  //TH2D* muRefittedStandAloneNChambersDt_Pt_hist;
  TH2D* mcStoppedParticleR_muRefittedStandAlonePt_hist;
  TH2D* mcStoppedParticleR_mcMuonPt_hist;
  TH2D* muStandAloneTrackDistanceStations_Pt_hist;
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
  TH1D* muPt_hist ;
  TH1D* muEta_hist;
  TH1D* muPhi_hist;
  TH1D* muType_hist; 
  TH1D* muIso_hist;
  TH2D* muEta_muPhi_hist;

  TH1D* diMu_N_hist;
  TH1D* diMuMass_hist;

  TH1D* muCosmic_N_hist;
  TH1D* muCosmicPt_hist;
  TH1D* muCosmicEta_hist;
  TH1D* muCosmicPhi_hist;
  TH1D* muCosmicType_hist;
  TH2D* muCosmicEta_muCosmicPhi_hist;

  TH1D* muCosmicTrackInnerPt_hist;

  TH1D* muStandAlone_N_other_cut_hist;

  TH1D* muStandAlone_N_hist;
  TH1D* muStandAlonePt_hist;
  TH1D* muStandAloneEta_hist;
  TH1D* muStandAlonePhi_hist;
  TH1D* muStandAloneTrackNormalizedChi2_hist;
  TH1D* muStandAloneTrackDxy_hist;
  TH1D* muStandAloneTrackDz_hist; 
  TH1D* muStandAloneTrackNHitsMuon_hist;
  TH1D* muStandAloneTrackNHitsCsc_hist; 
  TH1D* muStandAloneTrackNHitsDt_hist;
  TH1D* muStandAloneTrackNHitsRpc_hist; 
  TH1D* muStandAloneTrackNStations_hist;
  TH1D* muStandAloneTrackNChambersCsc_hist;
  TH1D* muStandAloneTrackNChambersDt_hist; 
  TH1D* muStandAloneTrackNChambersRpc_hist;
  TH1D* muStandAloneTrackDistanceStations_hist;
  TH1D* muStandAloneTrackInnerPt_hist;
  TH1D* muStandAloneTrackDtTofNDof_hist;
  TH1D* muStandAloneTrackDtTofInverseBetaLS_hist;
  TH1D* muStandAloneTrackDtTofInverseBetaLSErr_hist;
  TH1D* muStandAloneTrackDtTofYIntercept_hist;
  TH1D* muStandAloneTrackDtTofYInterceptErr_hist;
  TH1D* muStandAloneTrackDtTofChi2Dof_hist;
  TH1D* muStandAloneBxPattern_hist;
  TH1D* muStandAloneNHitsRpcBxPattern0_hist;

  TH1D* muStandAloneOppositeSegDR_hist;
  TH1D* muStandAloneOppositeSegDEta_hist;
  TH1D* muStandAloneOppositeSegDPhi_hist;
  
  TH1D* muStandAloneTrackShowerSize_station0_hist;
  TH1D* muStandAloneTrackShowerSize_station1_hist;
  TH1D* muStandAloneTrackShowerSize_station2_hist;
  TH1D* muStandAloneTrackShowerSize_station3_hist;
  TH1D* muStandAloneTrackShowerDeltaR_station0_hist;
  TH1D* muStandAloneTrackShowerDeltaR_station1_hist;
  TH1D* muStandAloneTrackShowerDeltaR_station2_hist;
  TH1D* muStandAloneTrackShowerDeltaR_station3_hist;
  TH1D* muStandAloneTrackShowerNHits_station0_hist;
  TH1D* muStandAloneTrackShowerNHits_station1_hist;
  TH1D* muStandAloneTrackShowerNHits_station2_hist;
  TH1D* muStandAloneTrackShowerNHits_station3_hist;
  TH1D* muStandAloneTrackShowerNCorrelatedHits_station0_hist;
  TH1D* muStandAloneTrackShowerNCorrelatedHits_station1_hist;
  TH1D* muStandAloneTrackShowerNCorrelatedHits_station2_hist;
  TH1D* muStandAloneTrackShowerNCorrelatedHits_station3_hist;
  TH1D* muStandAloneTrackShowerNUncorrelatedHits_station0_hist;
  TH1D* muStandAloneTrackShowerNUncorrelatedHits_station1_hist;
  TH1D* muStandAloneTrackShowerNUncorrelatedHits_station2_hist;
  TH1D* muStandAloneTrackShowerNUncorrelatedHits_station3_hist;

  TH1D* muStandAloneUpperOnlyDEta_hist;
  TH1D* muStandAloneUpperOnlyDPhi_hist;
  TH1D* muStandAloneLowerOnlyDEta_hist;
  TH1D* muStandAloneLowerOnlyDPhi_hist;

  TH1D* muStandAloneNCscSegments_hist;

  TH2D* muStandAloneEta_muStandAlonePhi_hist;
  TH2D* muStandAloneTrackNHitsRpc_muStandAloneTrackNormalizedChi2_hist;
  TH2D* muStandAloneTrackNHitsRpc_muStandAloneTrackNHitsDt_hist;
  TH2D* muStandAlonePt_muStandAloneTrackNChambersDt_hist;

  TH1D* Upper_StandAlone_N_hist;
  TH1D* Upper_StandAlonePt_hist;
  TH1D* Upper_StandAloneEta_hist;
  TH1D* Upper_StandAlonePhi_hist;
  TH1D* Upper_StandAloneTrackNormalizedChi2_hist;
  TH1D* Upper_StandAloneTrackDxy_hist;
  TH1D* Upper_StandAloneTrackDz_hist;
  TH1D* Upper_StandAloneTrackNHitsMuon_hist;
  TH1D* Upper_StandAloneTrackNHitsCsc_hist;
  TH1D* Upper_StandAloneTrackNHitsDt_hist;
  TH1D* Upper_StandAloneTrackNHitsRpc_hist;
  TH1D* Upper_StandAloneTrackNStations_hist;
  TH1D* Upper_StandAloneTrackNChambersCsc_hist;
  TH1D* Upper_StandAloneTrackNChambersDt_hist;
  TH1D* Upper_StandAloneTrackNChambersRpc_hist;
  TH1D* Upper_StandAloneTrackDtTofNDof_hist;
  TH1D* Upper_StandAloneTrackDtTofInverseBetaLS_hist;
  TH1D* Upper_StandAloneTrackDtTofInverseBetaLSErr_hist;
  TH1D* Upper_StandAloneTrackDtTofYIntercept_hist;
  TH1D* Upper_StandAloneTrackDtTofYInterceptErr_hist;
  TH1D* Upper_StandAloneTrackDtTofChi2Dof_hist;
  TH2D* Upper_StandAloneTrackNHitsRpc_Upper_StandAloneTrackNormalizedChi2_hist;
  TH2D* Upper_StandAloneTrackNHitsRpc_Upper_StandAloneTrackNHitsDt_hist;
  TH1D* Upper_muStandAloneBxPattern_hist;
  TH1D* Upper_muStandAloneNHitsRpcBxPattern0_hist;

  TH1D* Lower_StandAlone_N_hist;
  TH1D* Lower_StandAlonePt_hist;
  TH1D* Lower_StandAloneEta_hist;
  TH1D* Lower_StandAlonePhi_hist;
  TH1D* Lower_StandAloneTrackNormalizedChi2_hist;
  TH1D* Lower_StandAloneTrackDxy_hist;
  TH1D* Lower_StandAloneTrackDz_hist; 
  TH1D* Lower_StandAloneTrackNHitsMuon_hist;
  TH1D* Lower_StandAloneTrackNHitsCsc_hist;
  TH1D* Lower_StandAloneTrackNHitsDt_hist;
  TH1D* Lower_StandAloneTrackNHitsRpc_hist;
  TH1D* Lower_StandAloneTrackNStations_hist;
  TH1D* Lower_StandAloneTrackNChambersCsc_hist;
  TH1D* Lower_StandAloneTrackNChambersDt_hist; 
  TH1D* Lower_StandAloneTrackNChambersRpc_hist;
  TH1D* Lower_StandAloneTrackDtTofNDof_hist;
  TH1D* Lower_StandAloneTrackDtTofInverseBetaLS_hist;
  TH1D* Lower_StandAloneTrackDtTofInverseBetaLSErr_hist;
  TH1D* Lower_StandAloneTrackDtTofYIntercept_hist;
  TH1D* Lower_StandAloneTrackDtTofYInterceptErr_hist;
  TH1D* Lower_StandAloneTrackDtTofChi2Dof_hist;
  TH2D* Lower_StandAloneTrackNHitsRpc_Lower_StandAloneTrackNormalizedChi2_hist;
  TH2D* Lower_StandAloneTrackNHitsRpc_Lower_StandAloneTrackNHitsDt_hist;
  TH1D* Lower_muStandAloneBxPattern_hist;
  TH1D* Lower_muStandAloneNHitsRpcBxPattern0_hist;

  TH1D* Upper_StandAloneTofTimeAtIpInOut_hist;
  TH1D* Upper_StandAloneTofTimeAtIpOutIn_hist;
  TH1D* Lower_StandAloneTofTimeAtIpInOut_hist;
  TH1D* Lower_StandAloneTofTimeAtIpOutIn_hist;
  TH1D* mudiff_StandAloneTofTimeAtIpInOut_hist;
  TH1D* mudiff_StandAloneTofTimeAtIpOutIn_hist;
  TH2D* Upper_Lower_StandAloneTofTimeAtIpInOut_hist;
  TH2D* Upper_Lower_StandAloneTofTimeAtIpOutIn_hist;
  
  TH1D* muRefittedStandAlone_N_hist;
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

  TH1D* muStandAloneDTTof_N_hist;
  TH1D* muStandAloneDTTofDirection_hist;
  TH1D* muStandAloneDTTofNDof_hist;
  TH1D* muStandAloneDTTofInverseBeta_hist;
  TH1D* muStandAloneDTTofInverseBetaErr_hist;
  TH1D* muStandAloneDTTofFreeInverseBeta_hist;
  TH1D* muStandAloneDTTofFreeInverseBetaErr_hist;
  TH1D* muStandAloneDTTofTimeAtIpInOut_hist;
  TH1D* muStandAloneDTTofTimeAtIpInOutErr_hist;
  TH1D* muStandAloneDTTofTimeAtIpOutIn_hist;
  TH1D* muStandAloneDTTofTimeAtIpOutInErr_hist;

  TH1D* muStandAloneCSCTof_N_hist;
  TH1D* muStandAloneCSCTofDirection_hist;
  TH1D* muStandAloneCSCTofNDof_hist;
  TH1D* muStandAloneCSCTofInverseBeta_hist;
  TH1D* muStandAloneCSCTofInverseBetaErr_hist;
  TH1D* muStandAloneCSCTofFreeInverseBeta_hist;
  TH1D* muStandAloneCSCTofFreeInverseBetaErr_hist;
  TH1D* muStandAloneCSCTofTimeAtIpInOut_hist;
  TH1D* muStandAloneCSCTofTimeAtIpInOutErr_hist;
  TH1D* muStandAloneCSCTofTimeAtIpOutIn_hist;
  TH1D* muStandAloneCSCTofTimeAtIpOutInErr_hist;

  TH1D* refitMuStandAloneTof_N_hist;
  TH1D* refitMuStandAloneTofDirection_hist;
  TH1D* refitMuStandAloneTofNDof_hist;
  TH1D* refitMuStandAloneTofInverseBeta_hist;
  TH1D* refitMuStandAloneTofInverseBetaErr_hist;
  TH1D* refitMuStandAloneTofFreeInverseBeta_hist;
  TH1D* refitMuStandAloneTofFreeInverseBetaErr_hist;
  TH1D* refitMuStandAloneTofTimeAtIpInOut_hist;
  TH1D* refitMuStandAloneTofTimeAtIpInOutErr_hist;
  TH1D* refitMuStandAloneTofTimeAtIpOutIn_hist;
  TH1D* refitMuStandAloneTofTimeAtIpOutInErr_hist;

  TH1D* refitMuStandAloneDTTof_N_hist;
  TH1D* refitMuStandAloneDTTofDirection_hist;
  TH1D* refitMuStandAloneDTTofNDof_hist;
  TH1D* refitMuStandAloneDTTofInverseBeta_hist;
  TH1D* refitMuStandAloneDTTofInverseBetaErr_hist;
  TH1D* refitMuStandAloneDTTofFreeInverseBeta_hist;
  TH1D* refitMuStandAloneDTTofFreeInverseBetaErr_hist;
  TH1D* refitMuStandAloneDTTofTimeAtIpInOut_hist;
  TH1D* refitMuStandAloneDTTofTimeAtIpInOutErr_hist;
  TH1D* refitMuStandAloneDTTofTimeAtIpOutIn_hist;
  TH1D* refitMuStandAloneDTTofTimeAtIpOutInErr_hist;

  TH1D* refitMuStandAloneCSCTof_N_hist;
  TH1D* refitMuStandAloneCSCTofDirection_hist;
  TH1D* refitMuStandAloneCSCTofNDof_hist;
  TH1D* refitMuStandAloneCSCTofInverseBeta_hist;
  TH1D* refitMuStandAloneCSCTofInverseBetaErr_hist;
  TH1D* refitMuStandAloneCSCTofFreeInverseBeta_hist;
  TH1D* refitMuStandAloneCSCTofFreeInverseBetaErr_hist;
  TH1D* refitMuStandAloneCSCTofTimeAtIpInOut_hist;
  TH1D* refitMuStandAloneCSCTofTimeAtIpInOutErr_hist;
  TH1D* refitMuStandAloneCSCTofTimeAtIpOutIn_hist;
  TH1D* refitMuStandAloneCSCTofTimeAtIpOutInErr_hist;

  TH1D* DTSegment_N_hist;

};

void findTreevalues_makehistos_Ntuples_allsamples::stops( StoppedHSCPMuonEvent* events, bool& WFromTop, bool& status1muon, bool& status1muonFromW, bool& status1muonFromMuon){

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
      if(TMath::Abs(events->mcMuonMotherId[j])==24) status1muonFromW = true;

      //did status1 muon come from another muon? 
      if(TMath::Abs(events->mcMuonMotherId[j])==13){
	//check that at least one muon came from W, or from CMshower from W 
	for (UInt_t k=0; k<events->mcMuon_N; k++) {
	  if(TMath::Abs(events->mcMuonMotherId[k])==24) status1muonFromMuon = true;
	  if(TMath::Abs(events->mcMuonMotherId[k])==94) {
	    for (UInt_t l=0; l<events->mcCMshower_N; l++) {
	      if(TMath::Abs(events->mcCMshowerMotherId[l])==24) status1muonFromMuon = true;
	    }
	  }
	}
      }

      if(TMath::Abs(events->mcMuonMotherId[j])==13 && !status1muonFromMuon) cout<<"mother of stable muon is muon but didn't work for event "<<events->id<<endl;
      if(TMath::Abs(events->mcMuonMotherId[j])==24 && !status1muonFromW) cout<<"mother of stable muon is W but didn't work for event "<<events->id<<endl;
    } //end of muon status is 1 
  } //end of loop over mc muons      
}//end of stops

void findTreevalues_makehistos_Ntuples_allsamples::gluinos( StoppedHSCPMuonEvent* events, bool& status1muon, bool& status1muonFromW, bool& status1muonFromTau, bool& status1muonFromMuon, bool& status1muonFromBbaryon, bool& status1muonFromCbaryon, bool& status1muonFromSbaryon, bool& status1muonFromBmeson, bool& status1muonFromCmeson, bool& status1muonFromJPsi, bool& status1muonFromLightMeson ){

  //check first to see if there is a status 1 muon in the event
  for (UInt_t j=0; j<events->mcMuon_N; j++) {
    if(events->mcMuonStatus[j]==1){
      status1muon = true;
      //cout<<"mother of status 1 muon is: "<<events->mcMuonMotherId[j]<<endl; 
      if(TMath::Abs(events->mcMuonMotherId[j])==24){
	status1muonFromW = true;
      }
      if(TMath::Abs(events->mcMuonMotherId[j])==15){
	status1muonFromTau = true;
      }
      if(TMath::Abs(events->mcMuonMotherId[j])==13){
	status1muonFromMuon = true;
      }

      //did status1 muon come from some B or D meson, j/psi,
      if(TMath::Abs(events->mcMuonMotherId[j])==5332 || TMath::Abs(events->mcMuonMotherId[j])==5232 || TMath::Abs(events->mcMuonMotherId[j])==5132 || TMath::Abs(events->mcMuonMotherId[j])==5122){
	status1muonFromBbaryon = true;
      }
      if(TMath::Abs(events->mcMuonMotherId[j])==4332 || TMath::Abs(events->mcMuonMotherId[j])==4232 || TMath::Abs(events->mcMuonMotherId[j])==4132 || TMath::Abs(events->mcMuonMotherId[j])==4122){
	status1muonFromCbaryon = true;
      }
      if(TMath::Abs(events->mcMuonMotherId[j])==3312){
	status1muonFromSbaryon = true;
      }
      if(TMath::Abs(events->mcMuonMotherId[j])==541 || TMath::Abs(events->mcMuonMotherId[j])==531 || TMath::Abs(events->mcMuonMotherId[j])==521 || TMath::Abs(events->mcMuonMotherId[j])==511){
	status1muonFromBmeson = true;
      }
      if(TMath::Abs(events->mcMuonMotherId[j])==443){
	status1muonFromJPsi = true;
      }
      if(TMath::Abs(events->mcMuonMotherId[j])==431 || TMath::Abs(events->mcMuonMotherId[j])==421 || TMath::Abs(events->mcMuonMotherId[j])==411){
	status1muonFromCmeson = true;
      }
      if(TMath::Abs(events->mcMuonMotherId[j])==333 || TMath::Abs(events->mcMuonMotherId[j])==221 || TMath::Abs(events->mcMuonMotherId[j])==113){
	status1muonFromLightMeson = true;
      }

      //did status1 muon come from anything else? 
      if(TMath::Abs(events->mcMuonMotherId[j])!=13 && TMath::Abs(events->mcMuonMotherId[j])!=15 && TMath::Abs(events->mcMuonMotherId[j])!=24){
	if(TMath::Abs(events->mcMuonMotherId[j])!=5332 && TMath::Abs(events->mcMuonMotherId[j])!=5232 && TMath::Abs(events->mcMuonMotherId[j])!=5132 && TMath::Abs(events->mcMuonMotherId[j])!=5122
	   && TMath::Abs(events->mcMuonMotherId[j])!=4332 && TMath::Abs(events->mcMuonMotherId[j])!=4232 && TMath::Abs(events->mcMuonMotherId[j])!=4132 && TMath::Abs(events->mcMuonMotherId[j])!=4122 && TMath::Abs(events->mcMuonMotherId[j])!=3312 
	   && TMath::Abs(events->mcMuonMotherId[j])!=541 && TMath::Abs(events->mcMuonMotherId[j])!=531 && TMath::Abs(events->mcMuonMotherId[j])!=521 && TMath::Abs(events->mcMuonMotherId[j])!=511
	   && TMath::Abs(events->mcMuonMotherId[j])!=443 && TMath::Abs(events->mcMuonMotherId[j])!=431 && TMath::Abs(events->mcMuonMotherId[j])!=421 && TMath::Abs(events->mcMuonMotherId[j])!=411
	   && TMath::Abs(events->mcMuonMotherId[j])!=333 && TMath::Abs(events->mcMuonMotherId[j])!=221 && TMath::Abs(events->mcMuonMotherId[j])!=113)
	  {
	    cout<<"for event "<<events->id<<", mother of status1 muon is: "<<events->mcMuonMotherId[j]<<endl;
	  }
      }
      
    } //end of muon status is 1 
  } //end of loop over mc muons 
}//end of gluinos

void findTreevalues_makehistos_Ntuples_allsamples::mchamps( StoppedHSCPMuonEvent* events,
							    bool& muonFromMchamp, bool (&status1muon_)[15], bool (&status1muonFromMchamp_)[15], 
							    bool (&status1muonFromMuon_)[15], int& good_genMuons, 
							    double& genMu0_px, double& genMu0_py, double& genMu0_pz, double& genMu0_pt, double& genMu0_p,
							    double& genMu0_eta, double& genMu0_phi, double& genMu0_charge,
							    double& genMu1_px, double& genMu1_py, double& genMu1_pz, double& genMu1_pt, double& genMu1_p, 
							    double& genMu1_eta, double& genMu1_phi, double& genMu1_charge,
							    Double_t& angle,
							    double& genMuUpper_px, double& genMuUpper_py, double& genMuUpper_pz, double& genMuUpper_pt, double& genMuUpper_p,
							    double& genMuUpper_eta, double& genMuUpper_phi, double& genMuUpper_charge, 
							    double& genMuLower_px, double& genMuLower_py, double& genMuLower_pz, double& genMuLower_pt, double& genMuLower_p, 
							    double& genMuLower_eta, double& genMuLower_phi, double& genMuLower_charge){

  //each event must contain at least one top 
  //don't check that top came directly from stop, but check that there is at least one top and one stop in the event 
  //cout<<"number of tops is: "<<events->mcTop_N<<endl; 
  //check to see if at least one top from stop decays to W
  for (UInt_t j=0; j<events->mcTauPrime_N; j++) {
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
	cout<<"for event "<<events->id<<", mother of status1 muon is: "<<events->mcMuonMotherId[j]<<endl;
      }
      if(TMath::Abs(events->mcMuonMotherId[j])==13 && !status1muonFromMuon_[j]) cout<<"mother of stable muon is muon but didn't work for event "<<events->id<<endl;
    } //end of muon status is 1                                                                                                                                                  
  } //end of loop over mc muons

  for (UInt_t j=0; j<events->mcMuon_N; j++) {
    if(status1muonFromMchamp_[j] || status1muonFromMuon_[j]){
      good_genMuons++;
      if(good_genMuons==1){
	genMu0_px=events->mcMuonPx[j];
	genMu0_py=events->mcMuonPy[j];
	genMu0_pz=events->mcMuonPz[j];
	genMu0_pt=events->mcMuonPt[j];
	genMu0_p=events->mcMuonP[j];
	genMu0_eta=events->mcMuonEta[j];
	genMu0_phi=events->mcMuonPhi[j];
	genMu0_charge=events->mcMuonCharge[j];
      }
      if(good_genMuons==2){
	genMu1_px=events->mcMuonPx[j];
	genMu1_py=events->mcMuonPy[j];
	genMu1_pz=events->mcMuonPz[j];
	genMu1_pt=events->mcMuonPt[j];
	genMu1_p=events->mcMuonP[j];
	genMu1_eta=events->mcMuonEta[j];
	genMu1_phi=events->mcMuonPhi[j];
	genMu1_charge=events->mcMuonCharge[j];
      }
    }
  }

  if(good_genMuons!=2) cout<<"for event "<<events->id<<", have "<<good_genMuons<<" good generator muons"<<endl;

  // 3D angle between generator muons
  if(good_genMuons==2 && genMu0_p!=0. && genMu1_p!=0.){
    angle = TMath::ACos((genMu0_px*genMu1_px + genMu0_py*genMu1_py + genMu0_pz*genMu1_pz)/(genMu0_p*genMu1_p));
  }

  //one in upper, one in lower?
  if(genMu0_phi>genMu1_phi){
    genMuUpper_px=genMu0_px;
    genMuUpper_py=genMu0_py;
    genMuUpper_pz=genMu0_pz;
    genMuUpper_pt=genMu0_pt;
    genMuUpper_p=genMu0_p;
    genMuUpper_eta=genMu0_eta;
    genMuUpper_phi=genMu0_phi;
    genMuUpper_charge=genMu0_charge;
    genMuLower_px=genMu1_px;
    genMuLower_py=genMu1_py;
    genMuLower_pz=genMu1_pz;
    genMuLower_pt=genMu1_pt;
    genMuLower_p=genMu1_p;
    genMuLower_eta=genMu1_eta;
    genMuLower_phi=genMu1_phi;
    genMuLower_charge=genMu1_charge;
  }
  if(genMu1_phi>genMu0_phi){
    genMuUpper_px=genMu1_px;
    genMuUpper_py=genMu1_py;
    genMuUpper_pz=genMu1_pz;
    genMuUpper_pt=genMu1_pt;
    genMuUpper_p=genMu1_p;
    genMuUpper_eta=genMu1_eta;
    genMuUpper_phi=genMu1_phi;
    genMuUpper_charge=genMu1_charge;
    genMuLower_px=genMu0_px;
    genMuLower_py=genMu0_py;
    genMuLower_pz=genMu0_pz;
    genMuLower_pt=genMu0_pt;
    genMuLower_p=genMu0_p;
    genMuLower_eta=genMu0_eta;
    genMuLower_phi=genMu0_phi;
    genMuLower_charge=genMu0_charge;
  }
}//end of mchamps

void findTreevalues_makehistos_Ntuples_allsamples::staus( StoppedHSCPMuonEvent* events, bool& tauFromStau, bool& status1muon, bool& status1muonFromTau, bool& status1muonFromMuon, bool& status1muonFromNeutralino){
  
  for (UInt_t j=0; j<events->mcStau_N; j++) {
    for (UInt_t k=0; k<events->mcStauDaughterId.at(j).size(); k++) {
      if(TMath::Abs(events->mcStauDaughterId.at(j).at(k))==15){
	tauFromStau = true;
      }
    }
  }
  
  //check first to see if there is a status 1 muon in the event
  for (UInt_t j=0; j<events->mcMuon_N; j++) {
    if(events->mcMuonStatus[j]==1){
      status1muon = true;
      
      //did status1 muon come from tau? 
      if(TMath::Abs(events->mcMuonMotherId[j])==15) status1muonFromTau = true;
      //did status1 muon come from another muon? 
      if(TMath::Abs(events->mcMuonMotherId[j])==13) status1muonFromMuon = true;
      //did status1 muon come from a CMshower, from a neutralino? 
      if(TMath::Abs(events->mcMuonMotherId[j])==94){
	for (UInt_t k=0; k<events->mcCMshower_N; k++) {
	  if(TMath::Abs(events->mcCMshowerMotherId[k])==1000022) status1muonFromNeutralino = true;
	}
      }

      //did status1 muon come from anything else? 
      if(TMath::Abs(events->mcMuonMotherId[j])!=15){
	//if(TMath::Abs(events->mcMuonMotherId[j])!=13 && TMath::Abs(events->mcMuonMotherId[j])!=94 && TMath::Abs(events->mcMuonMotherId[j])!=15){ 
	//if(TMath::Abs(events->mcMuonMotherId[j])!=5232 && TMath::Abs(events->mcMuonMotherId[j])!=5132 && TMath::Abs(events->mcMuonMotherId[j])!=5122 && TMath::Abs(events->mcMuonMotherId[j])!=4332 && TMath::Abs(events->mcMuonMotherId[j])!=4232 && TMath::Abs(events->mcMuonMotherId[j])!=4132 && TMath::Abs(events->mcMuonMotherId[j])!=4122 && TMath::Abs(events->mcMuonMotherId[j])!=531 && TMath::Abs(events->mcMuonMotherId[j])!=521 && TMath::Abs(events->mcMuonMotherId[j])!=511 && TMath::Abs(events->mcMuonMotherId[j])!=443 && TMath::Abs(events->mcMuonMotherId[j]!=431 && TMath::Abs(events->mcMuonMotherId[j])!=421 && TMath::Abs(events->mcMuonMotherId[j])!=411 && TMath::Abs(events->mcMuonMotherId[j])!=221 && TMath::Abs(events->mcMuonMotherId[j])!=113){
	cout<<"for event "<<events->id<<", mother of status1 muon is: "<<events->mcMuonMotherId[j]<<endl;
	//}
      }
      if(TMath::Abs(events->mcMuonMotherId[j])==13 && !status1muonFromMuon) cout<<"mother of stable muon is muon but didn't work for event "<<events->id<<endl;
      if(TMath::Abs(events->mcMuonMotherId[j])==94 && !status1muonFromNeutralino) cout<<"mother of stable muon is neutralino but didn't work for event "<<events->id<<endl;
      if(TMath::Abs(events->mcMuonMotherId[j])==15 && !status1muonFromTau) cout<<"mother of stable muon is stau but didn't work for event "<<events->id<<endl;
    } //end of muon status is 1                                                                                                                                                            
  } //end of loop over mc muons  
}//end of staus

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

void findTreevalues_makehistos_Ntuples_allsamples::mchamp_counts( StoppedHSCPMuonEvent* events, int& good_genMuons, double& genMu0_charge, double& genMu1_charge ){
  if( (doGenMuCut && events->mcTauPrime_N>0) || (!doGenMuCut)){
    pass_Nmchamps_cut++;
    if( (doGenMuCut && events->mcMuon_N>0) || (!doGenMuCut)){
      //if( (doGenMuCut && events->mcMuon_N>1) || (!doGenMuCut)){                                                                                    
      pass_muon_cut++;
      //if( (doGenMuCut && status1muon) || (!doGenMuCut)){                                                                                           
      pass_status1muon_cut++;
      if( (doGenMuCut && good_genMuons>1) || (!doGenMuCut)){
	if( (doGenMuCut && genMu0_charge==genMu1_charge) || (!doGenMuCut)){
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

void findTreevalues_makehistos_Ntuples_allsamples::StoppedParticles( StoppedHSCPMuonEvent* events ){
  // Identify which detector region the particles stopped in. For ME and MB, this definition includes                                                                            
  // the entire muon system, not just the yokes.                                                                                                                                 
  if( events->mcStoppedParticle_N>0 ){
    double r = events->mcStoppedParticleR[0]/10.0;
    double z = events->mcStoppedParticleZ[0]/10.0;
    double particle_eta = eta(events->mcStoppedParticleX[0],events->mcStoppedParticleY[0],
			      events->mcStoppedParticleZ[0],events->mcStoppedParticleTime[0]);
      
    if (r < 131.0 && fabs(particle_eta) <= 2.5 && fabs(z) < 300.0) tracker_count_++;
    else if (r>=131.0 && r<184.0 && fabs(z)<376.0 && fabs(particle_eta)<1.479) eb_count_++;
    else if (fabs(z)<376.0 && fabs(z) >= 300.0 && fabs(particle_eta)>=1.479 && fabs(particle_eta)<3.0) ee_count_++;
    else if (r>=184.0 && r<295.0 && fabs(particle_eta)<1.3 && fabs(z)<500.0) hb_count_++;
    else if (fabs(z)<560.0 && fabs(z)>=376.0 && fabs(particle_eta)>=1.3 && fabs(particle_eta)<3.0) he_count_++;
    else if (r>=295.0 && r<728.5 && fabs(z)<675.0)  mb_count_++;
    else if (r>=267.3 && r<728.5 && fabs(z)>=675.0 && fabs(z)<1080.0) me_count_++; // ME-top                                                                                     
    else if (r<267.3 && fabs(particle_eta)<3.0 && fabs(z)>=560.0 && fabs(z)<1080.0) me_count_++; // ME-bottom                                                                    
    else if (r<728.5 && fabs(z)<1080.0) { // other regions?                                                                                                                      
      other_detector_count_++;
      //dumpFile_ << r << "\t" << z << "\t" << particle_eta << std::endl;                                                                                                        
    }
    
    if (r >= 728.5 || fabs(z) > 1080) cavern_count_++;
    else detector_count_++;
  }//end of if >0 stopped particles
}//end of StoppedParticles()

void findTreevalues_makehistos_Ntuples_allsamples::StoppingRegionAcceptance( StoppedHSCPMuonEvent* events ){
  // Identify which detector region the particles stopped in. For ME and MB, this definition includes                                                                            
  // the entire muon system, not just the yokes. 
  //if they also pass some preselection
  if( events->mcStoppedParticle_N>0 ){
    double r = events->mcStoppedParticleR[0]/10.0;
    double z = events->mcStoppedParticleZ[0]/10.0;
    double particle_eta = eta(events->mcStoppedParticleX[0],events->mcStoppedParticleY[0],
			      events->mcStoppedParticleZ[0],events->mcStoppedParticleTime[0]);
      
    if (r < 131.0 && fabs(particle_eta) <= 2.5 && fabs(z) < 300.0) tracker_AccCount_++;
    else if (r>=131.0 && r<184.0 && fabs(z)<376.0 && fabs(particle_eta)<1.479) eb_AccCount_++;
    else if (fabs(z)<376.0 && fabs(z) >= 300.0 && fabs(particle_eta)>=1.479 && fabs(particle_eta)<3.0) ee_AccCount_++;
    else if (r>=184.0 && r<295.0 && fabs(particle_eta)<1.3 && fabs(z)<500.0) hb_AccCount_++;
    else if (fabs(z)<560.0 && fabs(z)>=376.0 && fabs(particle_eta)>=1.3 && fabs(particle_eta)<3.0) he_AccCount_++;
    else if (r>=295.0 && r<728.5 && fabs(z)<675.0)  mb_AccCount_++;
    else if (r>=267.3 && r<728.5 && fabs(z)>=675.0 && fabs(z)<1080.0) me_AccCount_++; // ME-top                                                                                     
    else if (r<267.3 && fabs(particle_eta)<3.0 && fabs(z)>=560.0 && fabs(z)<1080.0) me_AccCount_++; // ME-bottom                                                                    
    else if (r<728.5 && fabs(z)<1080.0) { // other regions?                                                                                                                      
      other_detector_AccCount_++;
      //dumpFile_ << r << "\t" << z << "\t" << particle_eta << std::endl;                                                                                                        
    }
    
    if (r >= 728.5 || fabs(z) > 1080) cavern_AccCount_++;
    else detector_AccCount_++;
  }//end of if >0 stopped particles
}//end of StoppingRegionAcceptance()

bool findTreevalues_makehistos_Ntuples_allsamples::genMuonMatched( StoppedHSCPMuonEvent* events ){
  //for (UInt_t j=0; j<events->mu_StandAlone_N; j++) {
  //if(events->muStandAloneTrackGenParticleIndex[j] >= 0) return(true);
  //}
  if(events->muStandAloneTrackGenParticleIndex[0] >= 0) return(true);
  return(false);
}//end of genMuonMatched()

bool findTreevalues_makehistos_Ntuples_allsamples::multipleMuons_PtCut( StoppedHSCPMuonEvent* events ){
  if(events->mu_StandAlone_N>=2){
    if( events->muStandAlonePt[0]>30. && events->muStandAlonePt[1]>20. ) return(true);
  }// end of at least 2 standalone muons
  return(false);
}//end of multipleMuons_PtCut()

bool findTreevalues_makehistos_Ntuples_allsamples::diMuMass_Cut( StoppedHSCPMuonEvent* events ){
  for (UInt_t j=0; j<events->diMuMass.size(); j++) {
    if(events->diMuMass[j] >80. && events->diMuMass[j]<100.) return(true);
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
  if(events->muStandAloneTrackRpcHitZ.at(j).size()==0){
    all_bx_0 = false;
    all_bx_positive = false;
    all_bx_negative = false;
    all_bx_positiveOr0 = false;
    all_bx_negativeOr0 = false;
    all_bx_constant = false;
    all_bx_increasing = false;
    all_bx_decreasing = false;
  }

  //if(events->muStandAloneTrackRpcHitZ.at(j).size()>0) events_1muon_pass_other_cut_with_rpcs++;
  //loop over Rpc hits
  for (UInt_t k=0; k<events->muStandAloneTrackRpcHitZ.at(j).size(); k++) {
    //cout<<"  , for Rpc hit number "<<k<<", Z is: "<<events->muStandAloneTrackRpcHitZ.at(j).at(k)<<", Rho is: "<<events->muStandAloneTrackRpcHitRho.at(j).at(k)<<", phi is: "<<events->muStandAloneTrackRpcHitPhi.at(j).at(k)<<", region is: "<<events->muStandAloneTrackRpcHitRegion.at(j).at(k)<<", Bx is: "<<events->muStandAloneTrackRpcHitBx.at(j).at(k)<<endl;
    if(events->muStandAloneTrackRpcHitBx.at(j).at(k) != 0) all_bx_0 = false;
    if(events->muStandAloneTrackRpcHitBx.at(j).at(k) <= 0) all_bx_positive = false;
    if(events->muStandAloneTrackRpcHitBx.at(j).at(k) >= 0) all_bx_negative = false;
    if(events->muStandAloneTrackRpcHitBx.at(j).at(k) < 0) all_bx_positiveOr0 = false;
    if(events->muStandAloneTrackRpcHitBx.at(j).at(k) > 0) all_bx_negativeOr0 = false;
    UInt_t l=k+1;
    if(l<events->muStandAloneTrackRpcHitZ.at(j).size()){
      if(events->muStandAloneTrackRpcHitBx.at(j).at(l) != events->muStandAloneTrackRpcHitBx.at(j).at(k)) all_bx_constant = false;
      if(events->muStandAloneTrackRpcHitBx.at(j).at(l) < events->muStandAloneTrackRpcHitBx.at(j).at(k)) all_bx_increasing = false;
      if(events->muStandAloneTrackRpcHitBx.at(j).at(l) > events->muStandAloneTrackRpcHitBx.at(j).at(k)) all_bx_decreasing = false;
      //cout<<"events->muStandAloneTrackRpcHitBx.at(j).at(l) is: "<<events->muStandAloneTrackRpcHitBx.at(j).at(l)<<", events->muStandAloneTrackRpcHitBx.at(j).at(k) is: "<<events->muStandAloneTrackRpcHitBx.at(j).at(k)<<", all_bx_increasing is: "<<all_bx_increasing<<", all_bx_decreasing is: "<<all_bx_decreasing<<endl;
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

  if(events->muStandAloneTrackRpcHitZ.at(j).size()<=0) return(-1);
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

double findTreevalues_makehistos_Ntuples_allsamples::dR_OppositeSeg( StoppedHSCPMuonEvent* events, UInt_t& mu_index, double& minPhi, double& minEta){
  // returns minimum dR segment (min dEta seg, min dPhi seg) - could be 3 different segments
  // if not matched to an opposite segment, returns 10
  double minDr=10;
  minPhi=10;
  minEta=10;

  double opposite_mu_eta = -1.*(events->muStandAloneEta[mu_index]);
  double opposite_mu_phi = events->muStandAlonePhi[mu_index] + TMath::Pi();

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
    if(events->muRefittedStandAloneTrackOutermostStation[mu_index]>0 && events->muRefittedStandAloneTrackInnermostStation[mu_index] >0) 
      distance_bet_stations = events->muRefittedStandAloneTrackOutermostStation[mu_index] - events->muRefittedStandAloneTrackInnermostStation[mu_index];
  }
  else{
    if(events->muStandAloneTrackOutermostStation[mu_index]>0 && events->muStandAloneTrackInnermostStation[mu_index] >0) 
      distance_bet_stations = events->muStandAloneTrackOutermostStation[mu_index] - events->muStandAloneTrackInnermostStation[mu_index];
  }

  return distance_bet_stations;

}//end of distanceBetweenStations


void findTreevalues_makehistos_Ntuples_allsamples::HighestPtSA_counts( StoppedHSCPMuonEvent* events, float& PtCutValue_, Int_t& ChaCutValue_, float& EtaCutValue_, UInt_t& RpcCutValue_, Int_t& DisStCutValue_, Int_t& DtHitsCutValue_, Int_t& CscHitsCutValue_, float& DtInvBetaCutValue_, float& TimeInOutCutValue_, float& OppEtaCutValue_, float& OppPhiCutValue_){

  double segment_dPhi, segment_dEta;
  UInt_t a=0;
  double segment_dR = dR_OppositeSeg(events, a, segment_dPhi, segment_dEta);

  //upper hemisphere cut
  if( (doUpperCut && events->muStandAlonePhi[0]>0.) || (!doUpperCut)){
    pass_Upper_cut++;
    
    //pt cut
    //if ( (doPtCut && events->muStandAlonePt[0]>PtCutValue_) || (!doPtCut) ){
    if ( (doPtCut && events->muRefittedStandAlonePt[0]<PtCutValue_) || (!doPtCut) ){
    //if ( (doPtCut && events->muCosmicTrackPt[0]<PtCutValue_) || (!doPtCut) ){
      pass_pt_cut++;
      StoppingRegionAcceptance(events);

      //2 chamber cut
      if( (doChaCut && (events->muStandAloneTrackNChambersDt[0] + events->muStandAloneTrackNChambersCsc[0])>ChaCutValue_) || (!doChaCut)) {
	pass_cha_cut++;
	
	//eta cut
	if ( (doEtaCut && TMath::Abs(events->muStandAloneEta[0])<EtaCutValue_ ) || (!doEtaCut) ){
	  pass_eta_cut++;
	  
	  //number of RPC hits cut
	  if( (doRpcCut && events->muStandAloneTrackRpcHitZ.at(0).size()>RpcCutValue_) || (!doRpcCut)){
	    pass_RPC_cut++;

	    //distance btw stations cut
	    bool refitted = false;	    
	    if( (doDisStCut && distanceBetweenStations(events, a, refitted)>DisStCutValue_) || (!doDisStCut)){
	      pass_DisSt_cut++;
	    
	      //number of DT hits cut
	      if( (doDtHitsCut && events->muStandAloneTrackDtTofNDof[0]>DtHitsCutValue_) || (!doDtHitsCut)){
		pass_DtHits_cut++;
		
		//number of CSC hits cut
		if( (doCscHitsCut && events->muStandAloneTrackNHitsCsc[0]==CscHitsCutValue_) || (!doCscHitsCut)){
		  pass_CscHits_cut++;
		  
		  //OppEta cut
		  if( (doOppEtaCut && !doCosEnrich && TMath::Abs(segment_dEta)>OppEtaCutValue_) ||
		      (doOppEtaCut && doCosEnrich && TMath::Abs(segment_dEta)<OppEtaCutValue_) ||
		      (!doOppEtaCut) ){
		    pass_OppEta_cut++;
		    
		    //OppPhi cut
		    if( (doOppPhiCut && !doCosEnrich && TMath::Abs(segment_dPhi)>OppPhiCutValue_) ||
			(doOppPhiCut && doCosEnrich && TMath::Abs(segment_dPhi)<OppPhiCutValue_) ||
			(!doOppPhiCut)){
		      pass_OppPhi_cut++;
		      
		      UInt_t muon_number = 0;
		      //RPC Bx pattern cut
		      if( (doRpcBxCut && !doCosEnrich && (Rpc_Bx_Pattern(events, muon_number)==0 || Rpc_Bx_Pattern(events, muon_number)==1)) || 
			  (doRpcBxCut && doCosEnrich && !(Rpc_Bx_Pattern(events, muon_number)==0 || Rpc_Bx_Pattern(events, muon_number)==1)) ||
			  (!doRpcBxCut)){
			pass_Rpc_Bx_cut++;
			
			//DT inverse beta cut
			if( (doDtInvBetaCut && !doCosEnrich && events->muStandAloneTrackDtTofInverseBetaLS[0]>DtInvBetaCutValue_) || 
			    (doDtInvBetaCut && doCosEnrich && events->muStandAloneTrackDtTofInverseBetaLS[0]<DtInvBetaCutValue_) || 
			    (!doDtInvBetaCut)){
			  pass_DtInvBeta_cut++;
			  
			  //timeInOut cut
			  if( (doTimeInOutCut && !doCosEnrich && events->muStandAloneTofTimeAtIpInOut[0]>TimeInOutCutValue_) ||
			      (doTimeInOutCut && doCosEnrich && events->muStandAloneTofTimeAtIpInOut[0]<TimeInOutCutValue_) ||
			      (!doTimeInOutCut)){
			    pass_TimeInOut_cut++;
			    
			    if(doPrintout){
			      printout_gen(events);
			      printout_SA(events);
			      printout_RSA(events);
			      printout_cosmic(events);
			      printout_L2(events);
			      printout_L1(events);
			    }
			    
			    //cout<<"run is: "<<events->run<<", event is: "<<events->id<<endl;
			    //cout<<"track_phi is: "<<events->muStandAlonePhi[0]<<", track_eta is: "<<events->muStandAloneEta[0]<<endl;
			    //cout<<"segment_dR is: "<<segment_dR<<", segment_dPhi is: "<<segment_dPhi<<", segment_dEta is: "<<segment_dEta<<endl<<endl;;
			    
			    //if(events->muStandAloneTrackGenParticleIndex[0] >= 0) {
			    //mcMuonPt_muStandAlonePt_hist->Fill(events->mcMuonPt[events->muStandAloneTrackGenParticleIndex[0]],events->muStandAlonePt[0],1.0);
			    //mcMuonEta_muStandAloneEta_hist->Fill(events->mcMuonEta[events->muStandAloneTrackGenParticleIndex[0]],events->muStandAloneEta[0],1.0);
			    //mcMuonPhi_muStandAlonePhi_hist->Fill(events->mcMuonPhi[events->muStandAloneTrackGenParticleIndex[0]],events->muStandAlonePhi[0],1.0);
			    //}
			    
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

			  double muStandAlone_pt_resolution = -99.;
			  double muRefittedStandAlone_pt_resolution = -99.;
			  double muCosmic_pt_resolution = -99.;

			  if(events->mcMuonPt[0]>0.){
			    muStandAlone_pt_resolution = 1.0*(events->mcMuonPt[0] - events->muStandAlonePt[0])/(events->mcMuonPt[0]); 
			    muRefittedStandAlone_pt_resolution = 1.0*(events->mcMuonPt[0] - events->muRefittedStandAlonePt[0])/(events->mcMuonPt[0]);
			    muCosmic_pt_resolution = 1.0*(events->mcMuonPt[0] - events->muCosmicTrackPt[0])/(events->mcMuonPt[0]);
			  }

			  muStandAlonePtResolution_hist->Fill(muStandAlone_pt_resolution,1.0);
			  muRefittedStandAlonePtResolution_hist->Fill(muRefittedStandAlone_pt_resolution,1.0);
			  muCosmicPtResolution_hist->Fill(muCosmic_pt_resolution,1.0);

			  muRefittedStandAlonePtResolution_muCosmicPtResolution_hist->Fill(muRefittedStandAlone_pt_resolution,muCosmic_pt_resolution,1.0);

			  muStandAloneNChambersDt_PtResolution_hist->Fill(events->muStandAloneTrackNChambersDt[0], muStandAlone_pt_resolution,1.0);
			  muRefittedStandAloneNChambersDt_PtResolution_hist->Fill(events->muRefittedStandAloneTrackNChambersDt[0], muRefittedStandAlone_pt_resolution,1.0);
			  muCosmicNChambersDt_PtResolution_hist->Fill(events->muCosmicTrackNChambersDt[0], muCosmic_pt_resolution,1.0);
			  muStandAloneNChambersRpc_PtResolution_hist->Fill(events->muStandAloneTrackNChambersRpc[0], muStandAlone_pt_resolution,1.0);
			  muRefittedStandAloneNChambersRpc_PtResolution_hist->Fill(events->muRefittedStandAloneTrackNChambersRpc[0], muRefittedStandAlone_pt_resolution,1.0);
			  muCosmicNChambersRpc_PtResolution_hist->Fill(events->muCosmicTrackNChambersRpc[0], muCosmic_pt_resolution,1.0);

			  //cout<<"resolution hists done"<<endl;

			  muStandAloneNChambersDt_Pt_hist->Fill(events->muStandAloneTrackNChambersDt[0], events->muStandAlonePt[0],1.0);
			  muRefittedStandAloneNChambersDt_Pt_hist->Fill(events->muRefittedStandAloneTrackNChambersDt[0], events->muRefittedStandAlonePt[0],1.0);
			  muCosmicNChambersDt_Pt_hist->Fill(events->muCosmicTrackNChambersDt[0], events->muCosmicTrackPt[0],1.0);
			  muStandAloneNChambersRpc_Pt_hist->Fill(events->muStandAloneTrackNChambersRpc[0], events->muStandAlonePt[0],1.0);
			  muRefittedStandAloneNChambersRpc_Pt_hist->Fill(events->muRefittedStandAloneTrackNChambersRpc[0], events->muRefittedStandAlonePt[0],1.0);
			  muCosmicNChambersRpc_Pt_hist->Fill(events->muCosmicTrackNChambersRpc[0], events->muCosmicTrackPt[0],1.0);

			  //cout<<"2D pt hists done"<<endl;

			  if(events->l1Muon_N>0) mcMuonPt_l1MuonPt_hist->Fill(events->mcMuonPt[0],events->l1MuonPt[0],1.0);
			  if(events->hlt20Cha2Muon_N>0) mcMuonPt_hlt20Cha2MuonPt_hist->Fill(events->mcMuonPt[0],events->hlt20Cha2MuonPt[0],1.0);

			  //cout<<"trigger hists done"<<endl;
			  mcMuonPt_hist->Fill(events->mcMuonPt[0],1.0);

			  mcMuonPt_muStandAlonePt_hist->Fill(events->mcMuonPt[0],events->muStandAlonePt[0],1.0);
			  mcMuonPt_muRefittedStandAlonePt_hist->Fill(events->mcMuonPt[0],events->muRefittedStandAlonePt[0],1.0);
			  mcMuonPt_muCosmicPt_hist->Fill(events->mcMuonPt[0],events->muCosmicPt[0],1.0);
			  mcMuonPt_muCosmicTrackPt_hist->Fill(events->mcMuonPt[0],events->muCosmicTrackPt[0],1.0);
			  muStandAlonePt_muCosmicTrackPt_hist->Fill(events->muStandAlonePt[0],events->muCosmicTrackPt[0],1.0);
			  
			  //cout<<"other 2d hists done"<<endl;

			  if(events->l1Muon_N>0){
			    mcMuonEta_l1MuonEta_hist->Fill(events->mcMuonEta[0],events->l1MuonEta[0],1.0);
			    mcMuonPhi_l1MuonPhi_hist->Fill(events->mcMuonPhi[0],events->l1MuonPhi[0],1.0);
			  }

			  if(events->hlt20Cha2Muon_N>0){
			    mcMuonEta_hlt20Cha2MuonEta_hist->Fill(events->mcMuonEta[0],events->hlt20Cha2MuonEta[0],1.0);
			    mcMuonPhi_hlt20Cha2MuonPhi_hist->Fill(events->mcMuonPhi[0],events->hlt20Cha2MuonPhi[0],1.0);
			  }

			  mcMuonEta_muStandAloneEta_hist->Fill(events->mcMuonEta[0],events->muStandAloneEta[0],1.0);
			  mcMuonPhi_muStandAlonePhi_hist->Fill(events->mcMuonPhi[0],events->muStandAlonePhi[0],1.0);
			  //muPt_hist->Fill(events->muPt[0],1.0);			
			  
			  //cout<<"mcMuon hists done"<<endl;
			  

			  muRefittedStandAloneNHitsDt_Pt_hist->Fill(events->muRefittedStandAloneTrackNHitsDt[0],events->muRefittedStandAlonePt[0],1.0);
			  //muRefittedStandAloneNChambersDt_Pt_hist->Fill(events->muRefittedStandAloneTrackNChambersDt[0],events->muRefittedStandAlonePt[0],1.0);
			  mcStoppedParticleR_muRefittedStandAlonePt_hist->Fill(events->mcStoppedParticleR[0]/10.,events->muRefittedStandAlonePt[0],1.0);
			  mcStoppedParticleR_mcMuonPt_hist->Fill(events->mcStoppedParticleR[0]/10.,events->mcMuonPt[0],1.0);

			  //cout<<"blah"<<endl;

			  //bool refitted = false;
			    muStandAloneTrackDistanceStations_hist->Fill(distanceBetweenStations(events, a, refitted) ,1.0);
			    muStandAloneTrackDistanceStations_Pt_hist->Fill(distanceBetweenStations(events, a, refitted), events->muStandAlonePt[0],1.0);

			    refitted = true;
			    muRefittedStandAloneTrackDistanceStations_hist->Fill(distanceBetweenStations(events, a, refitted) ,1.0);
			    muRefittedStandAloneTrackDistanceStations_Pt_hist->Fill(distanceBetweenStations(events, a, refitted), events->muRefittedStandAlonePt[0],1.0);

			    
			    muCosmicTrackInnerPt_hist->Fill(TMath::Sqrt((events->muCosmicTrackInnerPx[0])*(events->muCosmicTrackInnerPx[0])+(events->muCosmicTrackInnerPy[0])*(events->muCosmicTrackInnerPy[0])),1.0);
			  
			  
			  muStandAlonePt_hist->Fill(events->muStandAlonePt[0],1.0);
			  muStandAloneEta_hist->Fill(events->muStandAloneEta[0],1.0);
			  muStandAlonePhi_hist->Fill(events->muStandAlonePhi[0],1.0);
			  muStandAloneTrackNormalizedChi2_hist->Fill(events->muStandAloneTrackNormalizedChi2[0],1.0);
			  muStandAloneTrackDxy_hist->Fill(events->muStandAloneTrackDxy[0],1.0);
			  muStandAloneTrackDz_hist->Fill(events->muStandAloneTrackDz[0],1.0);
			  muStandAloneTrackNHitsMuon_hist->Fill(events->muStandAloneTrackNHitsMuon[0],1.0);
			  muStandAloneTrackNHitsCsc_hist->Fill(events->muStandAloneTrackNHitsCsc[0],1.0);
			  muStandAloneTrackNHitsDt_hist->Fill(events->muStandAloneTrackNHitsDt[0],1.0);
			  //muStandAloneTrackNHitsRpc_hist->Fill(events->muStandAloneTrackNHitsRpc[0],1.0);
			  muStandAloneTrackNHitsRpc_hist->Fill(events->muStandAloneTrackRpcHitZ.at(muon_number).size(),1.0);
			  muStandAloneTrackNStations_hist->Fill(events->muStandAloneTrackNStations[0],1.0);
			  muStandAloneTrackNChambersCsc_hist->Fill(events->muStandAloneTrackNChambersCsc[0],1.0);
			  muStandAloneTrackNChambersDt_hist->Fill(events->muStandAloneTrackNChambersDt[0],1.0);
			  muStandAloneTrackNChambersRpc_hist->Fill(events->muStandAloneTrackNChambersRpc[0],1.0);
			  muStandAloneTrackInnerPt_hist->Fill(TMath::Sqrt((events->muStandAloneTrackInnerPx[0])*(events->muStandAloneTrackInnerPx[0])+(events->muStandAloneTrackInnerPy[0])*(events->muStandAloneTrackInnerPy[0])),1.0);
			  muStandAloneTrackDtTofNDof_hist->Fill(events->muStandAloneTrackDtTofNDof[0],1.0);
			  muStandAloneTrackDtTofInverseBetaLS_hist->Fill(events->muStandAloneTrackDtTofInverseBetaLS[0],1.0);
			  muStandAloneTrackDtTofInverseBetaLSErr_hist->Fill(events->muStandAloneTrackDtTofInverseBetaLSErr[0],1.0);
			  muStandAloneTrackDtTofYIntercept_hist->Fill(events->muStandAloneTrackDtTofYIntercept[0],1.0);
			  muStandAloneTrackDtTofYInterceptErr_hist->Fill(events->muStandAloneTrackDtTofYInterceptErr[0],1.0);
			  muStandAloneTrackDtTofChi2Dof_hist->Fill(events->muStandAloneTrackDtTofChi2Dof[0],1.0);
			  muStandAloneEta_muStandAlonePhi_hist->Fill(events->muStandAloneEta[0],events->muStandAlonePhi[0],1.0);
			  muStandAloneTrackNHitsRpc_muStandAloneTrackNormalizedChi2_hist->Fill(events->muStandAloneTrackNHitsRpc[0],events->muStandAloneTrackNormalizedChi2[0],1.0);
			  muStandAloneTrackNHitsRpc_muStandAloneTrackNHitsDt_hist->Fill(events->muStandAloneTrackNHitsRpc[0],events->muStandAloneTrackNHitsDt[0],1.0);
			  muStandAloneBxPattern_hist->Fill(Rpc_Bx_Pattern(events,muon_number)); //for highest pt muon
			  if(Rpc_Bx_Pattern(events, muon_number)==0) muStandAloneNHitsRpcBxPattern0_hist->Fill(events->muStandAloneTrackRpcHitZ.at(muon_number).size());
			  muStandAloneOppositeSegDR_hist->Fill(segment_dR,1.0);
			  muStandAloneOppositeSegDEta_hist->Fill(segment_dEta,1.0);
			  muStandAloneOppositeSegDPhi_hist->Fill(segment_dPhi,1.0);

			  muStandAloneTrackShowerSize_station0_hist->Fill(events->muStandAloneTrackShowerSize_station0[0],1.0);
			  muStandAloneTrackShowerSize_station1_hist->Fill(events->muStandAloneTrackShowerSize_station1[0],1.0);
			  muStandAloneTrackShowerSize_station2_hist->Fill(events->muStandAloneTrackShowerSize_station2[0],1.0);
			  muStandAloneTrackShowerSize_station3_hist->Fill(events->muStandAloneTrackShowerSize_station3[0],1.0);
			  muStandAloneTrackShowerDeltaR_station0_hist->Fill(events->muStandAloneTrackShowerDeltaR_station0[0],1.0);
			  muStandAloneTrackShowerDeltaR_station1_hist->Fill(events->muStandAloneTrackShowerDeltaR_station1[0],1.0);
			  muStandAloneTrackShowerDeltaR_station2_hist->Fill(events->muStandAloneTrackShowerDeltaR_station2[0],1.0);
			  muStandAloneTrackShowerDeltaR_station3_hist->Fill(events->muStandAloneTrackShowerDeltaR_station3[0],1.0);
			  muStandAloneTrackShowerNHits_station0_hist->Fill(events->muStandAloneTrackShowerNHits_station0[0],1.0);
			  muStandAloneTrackShowerNHits_station1_hist->Fill(events->muStandAloneTrackShowerNHits_station1[0],1.0);
			  muStandAloneTrackShowerNHits_station2_hist->Fill(events->muStandAloneTrackShowerNHits_station2[0],1.0);
			  muStandAloneTrackShowerNHits_station3_hist->Fill(events->muStandAloneTrackShowerNHits_station3[0],1.0);
			  muStandAloneTrackShowerNCorrelatedHits_station0_hist->Fill(events->muStandAloneTrackShowerNCorrelatedHits_station0[0],1.0);
			  muStandAloneTrackShowerNCorrelatedHits_station1_hist->Fill(events->muStandAloneTrackShowerNCorrelatedHits_station1[0],1.0);
			  muStandAloneTrackShowerNCorrelatedHits_station2_hist->Fill(events->muStandAloneTrackShowerNCorrelatedHits_station2[0],1.0);
			  muStandAloneTrackShowerNCorrelatedHits_station3_hist->Fill(events->muStandAloneTrackShowerNCorrelatedHits_station3[0],1.0);
			  muStandAloneTrackShowerNUncorrelatedHits_station0_hist->Fill(events->muStandAloneTrackShowerNUncorrelatedHits_station0[0],1.0);
			  muStandAloneTrackShowerNUncorrelatedHits_station1_hist->Fill(events->muStandAloneTrackShowerNUncorrelatedHits_station1[0],1.0);
			  muStandAloneTrackShowerNUncorrelatedHits_station2_hist->Fill(events->muStandAloneTrackShowerNUncorrelatedHits_station2[0],1.0);
			  muStandAloneTrackShowerNUncorrelatedHits_station3_hist->Fill(events->muStandAloneTrackShowerNUncorrelatedHits_station3[0],1.0);
			  
			  
			  //cout<<"______________________"<<endl;
			  //cout<<endl<<"For event "<<i<<", event # is: "<<events->id<<", run # is: "<<events->run<<", mu_StandAlone_N is: "<<events->mu_StandAlone_N<<", mu_RefittedStandAlone_N is: "<<events->mu_RefittedStandAlone_N<<", muStandAloneTof_N is: "<<events->muStandAloneTof_N<<", refitMuStandAloneTof_N is: "<<events->refitMuStandAloneTof_N<<endl;	
			  //cout<<"For event "<<i<<", event # is: "<<events->id<<", run # is: "<<events->run<<", bx is: "<<events->bx<<", mu_N is: "<<events->mu_N<<", mu_Cosmic_N is: "<<events->mu_Cosmic_N<<", mu_StandAlone_N is: "<<events->mu_StandAlone_N<<", mu_RefittedStandAlone_N is: "<<events->mu_RefittedStandAlone_N<<endl;
			  
			  //for (UInt_t j=0; j<events->mu_StandAlone_N; j++) {
			  //cout<<"For standalone mu number "<<j<<", before the cuts pt is: "<<events->muStandAlonePt[j]<<", eta is: "<<events->muStandAloneEta[j]<<", phi is: "<<events->muStandAlonePhi[j]<<", direction is: "<<events->muStandAloneTofDirection[j]<<", ndof is: "<<events->muStandAloneTofNDof[j]<<", number of DT segments is: "<<events->DTSegment_N<<endl;			
			  //cout<<endl<<"For event "<<i<<", event # is: "<<events->id<<", run # is: "<<events->run<<", mu_StandAlone_N is: "<<events->mu_StandAlone_N<<", mu_RefittedStandAlone_N is: "<<events->mu_RefittedStandAlone_N<<", muStandAloneTof_N is: "<<events->muStandAloneTof_N<<", refitMuStandAloneTof_N is: "<<events->refitMuStandAloneTof_N<<endl;
			  //cout<<"For standalone mu number "<<j<<", after the cuts pt is: "<<events->muStandAlonePt[j]<<", eta is: "<<events->muStandAloneEta[j]<<", phi is: "<<events->muStandAlonePhi[j]<<", track chi2/dof is: "<<events->muStandAloneTrackNormalizedChi2[j]<<", dxy is: "<<events->muStandAloneTrackDxy[j]<<", dz is: "<<events->muStandAloneTrackDz[j]<<endl;
			  //cout<<"  , number of overall muon hits is: "<<events->muStandAloneTrackNHitsMuon[j]<<", number of Csc hits is: "<<events->muStandAloneTrackNHitsCsc[j]<<", number of Dt hits is: "<<events->muStandAloneTrackNHitsDt[j]<<", number of Rpc hits is: "<<events->muStandAloneTrackNHitsRpc[j]<<endl;
			  //cout<<"  , number of overall muon stations is: "<<events->muStandAloneTrackNStations[j]<<", number of Csc chambers is: "<<events->muStandAloneTrackNChambersCsc[j]<<", number of Dt chambers is: "<<events->muStandAloneTrackNChambersDt[j]<<", number of Rpc Chambers is: "<<events->muStandAloneTrackNChambersRpc[j]<<endl;
			  //cout<<"  , TOF direction is: "<<events->muStandAloneTofDirection[j]<<", TOF ndof is: "<<events->muStandAloneTofNDof[j]<<", TimeAtIpInOut is: "<<events->muStandAloneTofTimeAtIpInOut[j]<<endl;
			  //}
			  //cout<<"blah2"<<endl;
			  
			  mu_N_hist->Fill(events->mu_N,1.0);
			  //for (UInt_t j=0; j<events->mu_N; j++) {
			    //cout<<"mu number "<<j<<endl;
			    muPt_hist->Fill(events->muPt[0],1.0);
			    muEta_hist->Fill(events->muEta[0],1.0);
			    muPhi_hist->Fill(events->muPhi[0],1.0);
			    muType_hist->Fill(events->muType[0],1.0);
			    muIso_hist->Fill(events->muIso[0],1.0);
			    muEta_muPhi_hist->Fill(events->muEta[0],events->muPhi[0],1.0);
			    //}	      
			  
			  muCosmic_N_hist->Fill(events->mu_Cosmic_N,1.0);
			  //for (UInt_t j=0; j<events->mu_Cosmic_N; j++) {
			    //cout<<"cosmic mu number "<<j<<endl;
			    muCosmicPt_hist->Fill(events->muCosmicTrackPt[0],1.0);
			    muCosmicEta_hist->Fill(events->muCosmicTrackEta[0],1.0);
			    muCosmicPhi_hist->Fill(events->muCosmicTrackPhi[0],1.0);
			    muCosmicType_hist->Fill(events->muCosmicType[0],1.0);
			    muCosmicEta_muCosmicPhi_hist->Fill(events->muCosmicEta[0],events->muCosmicPhi[0],1.0);
			    //}
			  
			  muStandAlone_N_hist->Fill(events->mu_StandAlone_N,1.0);
			  muRefittedStandAlone_N_hist->Fill(events->mu_RefittedStandAlone_N,1.0);
			  muStandAloneTof_N_hist->Fill(events->muStandAloneTof_N,1.0);
			  refitMuStandAloneTof_N_hist->Fill(events->refitMuStandAloneTof_N,1.0);						
			  
			  //cout<<"blah3"<<endl;
			  //if ( (do_other_cut && TMath::Abs(events->muStandAloneEta[j])<1.0 && events->muStandAlonePhi[j]>0.5 && events->muStandAlonePhi[j]<(TMath::Pi()-0.5) && events->muStandAloneTofDirection[j]!=0 && (events->muStandAloneTrackNChambersDt[j] + events->muStandAloneTrackNChambersCsc[j])>1 && pass_pt_cut[j] && TMath::Abs(events->muStandAloneTofTimeAtIpInOut[j])<50.) || (!do_other_cut) ){
			  //if ( (do_other_cut && TMath::Abs(events->muStandAloneEta[j])<1.0 && events->muStandAlonePhi[j]<-0.5 && events->muStandAlonePhi[j]>(-(TMath::Pi()-0.5)) && events->muStandAloneTofDirection[j]!=0 && (events->muStandAloneTrackNChambersDt[j] + events->muStandAloneTrackNChambersCsc[j])>1 && pass_pt_cut[j] && TMath::Abs(events->muStandAloneTofTimeAtIpInOut[j])<50.) || (!do_other_cut) ){									
			  
			  
			  //cout<<endl<<"number of rpc hits is: "<<events->muStandAloneTrackRpcHitZ.at(j).size()<<endl;
			  
			  //for (UInt_t j=0; j<events->mu_RefittedStandAlone_N; j++) {
			    //cout<<"refitted standalone mu number "<<j<<endl;
			    muRefittedStandAlonePt_hist->Fill(events->muRefittedStandAlonePt[0],1.0);
			    muRefittedStandAloneEta_hist->Fill(events->muRefittedStandAloneEta[0],1.0);
			    muRefittedStandAlonePhi_hist->Fill(events->muRefittedStandAlonePhi[0],1.0);
			    muRefittedStandAloneEta_muRefittedStandAlonePhi_hist->Fill(events->muRefittedStandAloneEta[0],events->muRefittedStandAlonePhi[0],1.0);
			    //}

			    //cout<<"blah4"<<endl;			  
			    //for (UInt_t j=0; j<events->muStandAloneTof_N; j++) {
			    //cout<<"TOF mu number "<<j<<endl;
			    //muStandAloneTofDirection_hist->Fill(events->muStandAloneTofDirection[0],1.0);
			    //muStandAloneTofNDof_hist->Fill(events->muStandAloneTofNDof[0],1.0);
			    //muStandAloneTofInverseBeta_hist->Fill(events->muStandAloneTofInverseBeta[0],1.0);
			    //muStandAloneTofInverseBetaErr_hist->Fill(events->muStandAloneTofInverseBetaErr[0],1.0);
			    //muStandAloneTofFreeInverseBeta_hist->Fill(events->muStandAloneTofFreeInverseBeta[0],1.0);
			    //muStandAloneTofFreeInverseBetaErr_hist->Fill(events->muStandAloneTofFreeInverseBetaErr[0],1.0);
			  // muStandAloneTofTimeAtIpInOut_hist->Fill(events->muStandAloneTofTimeAtIpInOut[0],1.0);
			  //muStandAloneTofTimeAtIpInOutErr_hist->Fill(events->muStandAloneTofTimeAtIpInOutErr[0],1.0);
			  //muStandAloneTofTimeAtIpOutIn_hist->Fill(events->muStandAloneTofTimeAtIpOutIn[0],1.0);
			  //muStandAloneTofTimeAtIpOutInErr_hist->Fill(events->muStandAloneTofTimeAtIpOutInErr[0],1.0);
			    //}
			  
			    //for (UInt_t j=0; j<events->refitMuStandAloneTof_N; j++) {
			    //cout<<"DT re-reco TOF mu number "<<j<<endl;
			    //refitMuStandAloneTofDirection_hist->Fill(events->refitMuStandAloneTofDirection[0],1.0);
			    //refitMuStandAloneTofNDof_hist->Fill(events->refitMuStandAloneTofNDof[0],1.0);
			    //refitMuStandAloneTofInverseBeta_hist->Fill(events->refitMuStandAloneTofInverseBeta[0],1.0);
			    //refitMuStandAloneTofInverseBetaErr_hist->Fill(events->refitMuStandAloneTofInverseBetaErr[0],1.0);
			    //refitMuStandAloneTofFreeInverseBeta_hist->Fill(events->refitMuStandAloneTofFreeInverseBeta[0],1.0);
			  //refitMuStandAloneTofFreeInverseBetaErr_hist->Fill(events->refitMuStandAloneTofFreeInverseBetaErr[0],1.0);
			  //refitMuStandAloneTofTimeAtIpInOut_hist->Fill(events->refitMuStandAloneTofTimeAtIpInOut[0],1.0);
			  //refitMuStandAloneTofTimeAtIpInOutErr_hist->Fill(events->refitMuStandAloneTofTimeAtIpInOutErr[0],1.0);
			  //refitMuStandAloneTofTimeAtIpOutIn_hist->Fill(events->refitMuStandAloneTofTimeAtIpOutIn[0],1.0);
			  //refitMuStandAloneTofTimeAtIpOutInErr_hist->Fill(events->refitMuStandAloneTofTimeAtIpOutInErr[0],1.0);
			    //}
			  
			    //cout<<"blah5"<<endl;
			  //muStandAloneDTTof_N_hist->Fill(events->muStandAloneDTTof_N,1.0);
			  //for (UInt_t j=0; j<events->muStandAloneDTTof_N; j++) {
			    //cout<<"TOF DT mu number "<<j<<endl;
			    //muStandAloneDTTofDirection_hist->Fill(events->muStandAloneDTTofDirection[0],1.0);
			    //muStandAloneDTTofNDof_hist->Fill(events->muStandAloneDTTofNDof[0],1.0);
			    //muStandAloneDTTofInverseBeta_hist->Fill(events->muStandAloneDTTofInverseBeta[0],1.0);
			    //muStandAloneDTTofInverseBetaErr_hist->Fill(events->muStandAloneDTTofInverseBetaErr[0],1.0);
			  // muStandAloneDTTofFreeInverseBeta_hist->Fill(events->muStandAloneDTTofFreeInverseBeta[0],1.0);
			  //muStandAloneDTTofFreeInverseBetaErr_hist->Fill(events->muStandAloneDTTofFreeInverseBetaErr[0],1.0);
			  //muStandAloneDTTofTimeAtIpInOut_hist->Fill(events->muStandAloneDTTofTimeAtIpInOut[0],1.0);
			  //muStandAloneDTTofTimeAtIpInOutErr_hist->Fill(events->muStandAloneDTTofTimeAtIpInOutErr[0],1.0);
			  //muStandAloneDTTofTimeAtIpOutIn_hist->Fill(events->muStandAloneDTTofTimeAtIpOutIn[0],1.0);
			  //muStandAloneDTTofTimeAtIpOutInErr_hist->Fill(events->muStandAloneDTTofTimeAtIpOutInErr[0],1.0);
			    //}
			  
			  //muStandAloneCSCTof_N_hist->Fill(events->muStandAloneCSCTof_N,1.0);
			  //for (UInt_t j=0; j<events->muStandAloneCSCTof_N; j++) {
			    //cout<<"TOF CSC mu number "<<j<<endl;
			    //muStandAloneCSCTofDirection_hist->Fill(events->muStandAloneCSCTofDirection[0],1.0);
			    //muStandAloneCSCTofNDof_hist->Fill(events->muStandAloneCSCTofNDof[0],1.0);
			    //muStandAloneCSCTofInverseBeta_hist->Fill(events->muStandAloneCSCTofInverseBeta[0],1.0);
			    //muStandAloneCSCTofInverseBetaErr_hist->Fill(events->muStandAloneCSCTofInverseBetaErr[0],1.0);
			    //muStandAloneCSCTofFreeInverseBeta_hist->Fill(events->muStandAloneCSCTofFreeInverseBeta[0],1.0);
			    //muStandAloneCSCTofFreeInverseBetaErr_hist->Fill(events->muStandAloneCSCTofFreeInverseBetaErr[0],1.0);
			    //muStandAloneCSCTofTimeAtIpInOut_hist->Fill(events->muStandAloneCSCTofTimeAtIpInOut[0],1.0);
			    //muStandAloneCSCTofTimeAtIpInOutErr_hist->Fill(events->muStandAloneCSCTofTimeAtIpInOutErr[0],1.0);
			    //muStandAloneCSCTofTimeAtIpOutIn_hist->Fill(events->muStandAloneCSCTofTimeAtIpOutIn[0],1.0);
			    //muStandAloneCSCTofTimeAtIpOutInErr_hist->Fill(events->muStandAloneCSCTofTimeAtIpOutInErr[0],1.0);
			    //}
			  
			  //refitMuStandAloneDTTof_N_hist->Fill(events->refitMuStandAloneDTTof_N,1.0);
			  //for (UInt_t j=0; j<events->refitMuStandAloneDTTof_N; j++) {
			    //cout<<"DT re-reco TOF DT mu number "<<j<<endl;
			    //refitMuStandAloneDTTofDirection_hist->Fill(events->refitMuStandAloneDTTofDirection[0],1.0);
			    //refitMuStandAloneDTTofNDof_hist->Fill(events->refitMuStandAloneDTTofNDof[0],1.0);
			    //refitMuStandAloneDTTofInverseBeta_hist->Fill(events->refitMuStandAloneDTTofInverseBeta[0],1.0);
			    //refitMuStandAloneDTTofInverseBetaErr_hist->Fill(events->refitMuStandAloneDTTofInverseBetaErr[0],1.0);
			    ///refitMuStandAloneDTTofFreeInverseBeta_hist->Fill(events->refitMuStandAloneDTTofFreeInverseBeta[0],1.0);
			    //refitMuStandAloneDTTofFreeInverseBetaErr_hist->Fill(events->refitMuStandAloneDTTofFreeInverseBetaErr[0],1.0);
			  //refitMuStandAloneDTTofTimeAtIpInOut_hist->Fill(events->refitMuStandAloneDTTofTimeAtIpInOut[0],1.0);
			    //refitMuStandAloneDTTofTimeAtIpInOutErr_hist->Fill(events->refitMuStandAloneDTTofTimeAtIpInOutErr[0],1.0);
			    //refitMuStandAloneDTTofTimeAtIpOutIn_hist->Fill(events->refitMuStandAloneDTTofTimeAtIpOutIn[0],1.0);
			    //refitMuStandAloneDTTofTimeAtIpOutInErr_hist->Fill(events->refitMuStandAloneDTTofTimeAtIpOutInErr[0],1.0);
			    //}
			    //cout<<"blah6"<<endl;
			    //refitMuStandAloneCSCTof_N_hist->Fill(events->refitMuStandAloneCSCTof_N,1.0);
			  //for (UInt_t j=0; j<events->refitMuStandAloneCSCTof_N; j++) {
			    //cout<<"DT re-reco TOF CSC mu number "<<j<<endl;
			    //refitMuStandAloneCSCTofDirection_hist->Fill(events->refitMuStandAloneCSCTofDirection[0],1.0);
			    //refitMuStandAloneCSCTofNDof_hist->Fill(events->refitMuStandAloneCSCTofNDof[0],1.0);
			    //refitMuStandAloneCSCTofInverseBeta_hist->Fill(events->refitMuStandAloneCSCTofInverseBeta[0],1.0);
			    //refitMuStandAloneCSCTofInverseBetaErr_hist->Fill(events->refitMuStandAloneCSCTofInverseBetaErr[0],1.0);
			    //refitMuStandAloneCSCTofFreeInverseBeta_hist->Fill(events->refitMuStandAloneCSCTofFreeInverseBeta[0],1.0);
			    //refitMuStandAloneCSCTofFreeInverseBetaErr_hist->Fill(events->refitMuStandAloneCSCTofFreeInverseBetaErr[0],1.0);
			    //refitMuStandAloneCSCTofTimeAtIpInOut_hist->Fill(events->refitMuStandAloneCSCTofTimeAtIpInOut[0],1.0);
			    //refitMuStandAloneCSCTofTimeAtIpInOutErr_hist->Fill(events->refitMuStandAloneCSCTofTimeAtIpInOutErr[0],1.0);
			    //refitMuStandAloneCSCTofTimeAtIpOutIn_hist->Fill(events->refitMuStandAloneCSCTofTimeAtIpOutIn[0],1.0);
			    //refitMuStandAloneCSCTofTimeAtIpOutInErr_hist->Fill(events->refitMuStandAloneCSCTofTimeAtIpOutInErr[0],1.0);
			    //cout<<"blah7"<<endl;
			    //}
			  
			  }//end of timeInOut for leading SA
			}//end of dt inverse beta for leading SA
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

void findTreevalues_makehistos_Ntuples_allsamples::pick_UpperAndLowerSA( StoppedHSCPMuonEvent* events, UInt_t& upper_index, UInt_t& lower_index, float& Pt0CutValue_, float& Pt1CutValue_){
  upper_index = 999;
  lower_index = 999;
  UInt_t x=999;
  UInt_t y=999;
  //cout<<endl;

  if(events->mu_StandAlone_N>=2){
    if((doCosEnrich && events->mu_StandAlone_N==2) || (!doCosEnrich)){
      pass_SA_2_cut++;
      //for (UInt_t j=0; j<events->mu_StandAlone_N; j++) {
      //cout<<"for index "<<j<<", pt is: "<<events->muStandAlonePt[j]<<", phi is: "<<events->muStandAlonePhi[j]<<endl;
      //}
      
      for (UInt_t j=0; j<events->mu_StandAlone_N; j++) {
	//upper
	if( (!doTightPhi && events->muStandAlonePhi[j]>0.) || (doTightPhi && (events->muStandAlonePhi[j]>0.5 && events->muStandAlonePhi[j]<(TMath::Pi()-0.5))) ){
	  if ( (doPtCut && events->muStandAlonePt[j]>Pt1CutValue_) || (!doPtCut) ){
	    x=j;
	    break;
	  }//end of pt 20 cut
	}//end of upper
      }//end of loop over SA muons
      
      for (UInt_t j=0; j<events->mu_StandAlone_N; j++) {
	//lower
	if( (!doTightPhi && events->muStandAlonePhi[j]<0.) || (doTightPhi && (events->muStandAlonePhi[j] < (-0.5) && events->muStandAlonePhi[j]>(-1.0*TMath::Pi()+0.5) ))){
	  if ( (doPtCut && events->muStandAlonePt[j]>Pt1CutValue_) || (!doPtCut) ){
	    y=j;
	    break;
	  }//end of pt 20 cut
	}//end of lower
      }//end of loop over SA muons
      
      if(x!=999 && y!=999){
	pass_UpperAndLower_cut++;
	if( (doPtCut && (events->muStandAlonePt[x]>Pt0CutValue_ || events->muStandAlonePt[y]>Pt0CutValue_)) || (!doPtCut)){
	  pass_pt_2_cut++;
	  upper_index = x;
	  lower_index = y;
	}//end of at least one candidate having pt>30
      }//end of if have candidate upper and lower muons
      else if(x!=999 && y==999){
	pass_UpperOnly_cut++;
	double dEta = TMath::Abs(events->muStandAloneEta[0] - events->muStandAloneEta[1]);
	double dPhi = TMath::Abs(events->muStandAlonePhi[0] - events->muStandAlonePhi[1]);
	while (dPhi > TMath::Pi()) dPhi -= 2*TMath::Pi();
	while (dPhi <= -TMath::Pi()) dPhi += 2*TMath::Pi();
	muStandAloneUpperOnlyDEta_hist->Fill(dEta);
	muStandAloneUpperOnlyDPhi_hist->Fill(dPhi);
      }
      else if(x==999 && y!=999){
	pass_LowerOnly_cut++;
	double dEta = TMath::Abs(events->muStandAloneEta[0] - events->muStandAloneEta[1]);
	double dPhi = TMath::Abs(events->muStandAlonePhi[0] - events->muStandAlonePhi[1]);
	while (dPhi > TMath::Pi()) dPhi -= 2*TMath::Pi();
	while (dPhi <= -TMath::Pi()) dPhi += 2*TMath::Pi();
	muStandAloneLowerOnlyDEta_hist->Fill(dEta);
	muStandAloneLowerOnlyDPhi_hist->Fill(dPhi);
      }
      
    }//end of exactly 2 SA muons for cosmic enriched sample
  }//end of at least 2 SA muons in event

  //cout<<"upper_index is: "<<upper_index<<", lower_index is: "<<lower_index<<endl;

}//end of pick_UpperAndLowerSA

void findTreevalues_makehistos_Ntuples_allsamples::UpperAndLowerSA_counts( StoppedHSCPMuonEvent* events, string& file_dataset, float& Pt0CutValue_, float& Pt1CutValue_, Int_t& ChaCutValue_, float& EtaCutValue_, UInt_t& RpcCutValue_,  Int_t& DisStCutValue_, Int_t& DtHitsCutValue_, float& DtInvBetaCutValue_, float& TimeInOutCutValue_){

  UInt_t upper_index=999;
  UInt_t lower_index=999;
  pick_UpperAndLowerSA(events,upper_index,lower_index,Pt0CutValue_,Pt1CutValue_);

  if(upper_index!=999 && lower_index!=999){
    pass_UpperAndLower_pt30_cut++;

    //double UpperSegment_dPhi, UpperSegment_dEta;
    //double LowerSegment_dPhi, LowerSegment_dEta;
    //double UpperSegment_dR = dR_OppositeSeg(events, upper_index, UpperSegment_dPhi, UpperSegment_dEta);
    //double LowerSegment_dR = dR_OppositeSeg(events, lower_index, LowerSegment_dPhi, LowerSegment_dEta);

    //cout<<"run is: "<<events->run<<", event is: "<<events->id<<endl;
    //cout<<"upper track_dPhi is: "<<events->muStandAlonePhi[upper_index]<<", upper track_dEta is: "<<events->muStandAloneEta[upper_index]<<endl;
    //cout<<"UpperSegment_dR is: "<<UpperSegment_dR<<",  UpperSegment_dPhi is: "<<UpperSegment_dPhi<<",  UpperSegment_dEta is: "<<UpperSegment_dEta<<endl<<endl;
    //cout<<"lower track_dPhi is: "<<events->muStandAlonePhi[lower_index]<<", lower track_dEta is: "<<events->muStandAloneEta[lower_index]<<endl;
    //cout<<"LowerSegment_dR is: "<<LowerSegment_dR<<",  LowerSegment_dPhi is: "<<LowerSegment_dPhi<<",  LowerSegment_dEta is: "<<LowerSegment_dEta<<endl<<endl;

    if((file_dataset=="Zmumu_Run2012B" && diMuMass_Cut(events)) || (file_dataset!="Zmumu_Run2012B")){             	
      
      //2 chamber cut
      if( (doChaCut && (events->muStandAloneTrackNChambersDt[upper_index] + events->muStandAloneTrackNChambersCsc[upper_index])>ChaCutValue_ && (events->muStandAloneTrackNChambersDt[lower_index] + events->muStandAloneTrackNChambersCsc[lower_index])>ChaCutValue_) || (!doChaCut)) {
	pass_cha_2_cut++;
	
	//eta cut
	if ( (doEtaCut && TMath::Abs(events->muStandAloneEta[upper_index])<EtaCutValue_ && TMath::Abs(events->muStandAloneEta[lower_index])<EtaCutValue_) || (!doEtaCut) ){
	  pass_eta_2_cut++;
	  
	  //RPC hits cut
	  if( (doRpcCut && events->muStandAloneTrackRpcHitZ.at(upper_index).size()>RpcCutValue_ && events->muStandAloneTrackRpcHitZ.at(lower_index).size()>RpcCutValue_) || (!doRpcCut)){
	    pass_RPC_2_cut++;			  
	    
	    Upper_muStandAloneBxPattern_hist->Fill(Rpc_Bx_Pattern(events,upper_index));
	    if(Rpc_Bx_Pattern(events, upper_index)==0) Upper_muStandAloneNHitsRpcBxPattern0_hist->Fill(events->muStandAloneTrackRpcHitZ.at(upper_index).size());
	    Lower_muStandAloneBxPattern_hist->Fill(Rpc_Bx_Pattern(events,lower_index));
	    if(Rpc_Bx_Pattern(events, lower_index)==0) Lower_muStandAloneNHitsRpcBxPattern0_hist->Fill(events->muStandAloneTrackRpcHitZ.at(lower_index).size());

	    //distance btw stations cut
	    bool refitted = false;	    
	    if( (doDisStCut && distanceBetweenStations(events, upper_index, refitted)>DisStCutValue_ && distanceBetweenStations(events, lower_index, refitted)>DisStCutValue_ ) || (!doDisStCut)){
	      pass_DisSt_2_cut++;

	      //number of DT hits cut
	      if( (doDtHitsCut && events->muStandAloneTrackDtTofNDof[upper_index]>DtHitsCutValue_ && events->muStandAloneTrackDtTofNDof[lower_index]>DtHitsCutValue_) || (!doDtHitsCut)){
		pass_DtHits_2_cut++;	      
		
		double dEta = events->muStandAloneEta[upper_index] + events->muStandAloneEta[lower_index];
		double dPhi = events->muStandAlonePhi[upper_index] - (events->muStandAlonePhi[lower_index] + TMath::Pi());
		while (dPhi > TMath::Pi()) dPhi -= 2*TMath::Pi();
		while (dPhi <= -TMath::Pi()) dPhi += 2*TMath::Pi();
		
		//OppEta cut (cosmic enriched)
		if((doCosEnrich && TMath::Abs(dEta)<OppEtaCutValue_) || (!doCosEnrich)){
		  pass_OppEta_2_cut++;
		  
		  //OppPhi cut (cosmic enriched)
		  if((doCosEnrich && TMath::Abs(dPhi)<OppPhiCutValue_) || (!doCosEnrich)){
		    pass_OppPhi_2_cut++;
		    
		    //RPC Bx pattern cut
		    if( (doRpcBxCut && !doCosEnrich && (Rpc_Bx_Pattern(events, upper_index)==0 || Rpc_Bx_Pattern(events, upper_index)==1) && (Rpc_Bx_Pattern(events, lower_index)==0 || Rpc_Bx_Pattern(events, lower_index)==1)) || 
			(doRpcBxCut && doCosEnrich && !(Rpc_Bx_Pattern(events, upper_index)==0 || Rpc_Bx_Pattern(events, upper_index)==1) && !(Rpc_Bx_Pattern(events, lower_index)==0 || Rpc_Bx_Pattern(events, lower_index)==1)) || 
			(!doRpcBxCut)){
		      pass_Rpc_Bx_2_cut++;
		      
		      //DT inverse beta cut
		      if( (doDtInvBetaCut && !doCosEnrich && events->muStandAloneTrackDtTofInverseBetaLS[upper_index]>DtInvBetaCutValue_ && events->muStandAloneTrackDtTofInverseBetaLS[lower_index]>DtInvBetaCutValue_) || 
			  (doDtInvBetaCut && doCosEnrich && events->muStandAloneTrackDtTofInverseBetaLS[upper_index]<DtInvBetaCutValue_ && events->muStandAloneTrackDtTofInverseBetaLS[lower_index]<DtInvBetaCutValue_) || 
			  (!doDtInvBetaCut)){
			pass_DtInvBeta_2_cut++;
			
			//timeInOut cut
			if( (doTimeInOutCut && !doCosEnrich && events->muStandAloneTofTimeAtIpInOut[upper_index]>TimeInOutCutValue_ && events->muStandAloneTofTimeAtIpInOut[lower_index]>TimeInOutCutValue_) || 
			    (doTimeInOutCut && doCosEnrich && events->muStandAloneTofTimeAtIpInOut[upper_index]<TimeInOutCutValue_ && events->muStandAloneTofTimeAtIpInOut[lower_index]<TimeInOutCutValue_) || 
			    (!doTimeInOutCut)){
			  pass_TimeInOut_2_cut++;
			  
			  //if(doPrintout) printout_SA(events);
			  
			  //cout<<"number of dimuon candidates is: "<<events->diMuMass.size()<<endl;
			  diMu_N_hist->Fill(events->diMuMass.size(),1.0);
			  for (UInt_t j=0; j<events->diMuMass.size(); j++) {
			    //cout<<"diMuMass is: "<<events->diMuMass[j]<<endl;
			    diMuMass_hist->Fill(events->diMuMass[j],1.0);
			  }
			  
			  Upper_StandAloneTofTimeAtIpInOut_hist->Fill(events->muStandAloneTofTimeAtIpInOut[upper_index],1.0);
			  Upper_StandAloneTofTimeAtIpOutIn_hist->Fill(events->muStandAloneTofTimeAtIpOutIn[upper_index],1.0);
			  Lower_StandAloneTofTimeAtIpInOut_hist->Fill(events->muStandAloneTofTimeAtIpInOut[lower_index],1.0);
			  Lower_StandAloneTofTimeAtIpOutIn_hist->Fill(events->muStandAloneTofTimeAtIpOutIn[lower_index],1.0);
			  mudiff_StandAloneTofTimeAtIpInOut_hist->Fill(events->muStandAloneTofTimeAtIpInOut[upper_index] - events->muStandAloneTofTimeAtIpInOut[lower_index],1.0);
			  mudiff_StandAloneTofTimeAtIpOutIn_hist->Fill(events->muStandAloneTofTimeAtIpOutIn[upper_index] - events->muStandAloneTofTimeAtIpOutIn[lower_index],1.0);
			  Upper_Lower_StandAloneTofTimeAtIpInOut_hist->Fill(events->muStandAloneTofTimeAtIpInOut[upper_index],events->muStandAloneTofTimeAtIpInOut[lower_index],1.0);
			  Upper_Lower_StandAloneTofTimeAtIpOutIn_hist->Fill(events->muStandAloneTofTimeAtIpOutIn[upper_index],events->muStandAloneTofTimeAtIpOutIn[lower_index],1.0);
			  
			Upper_StandAlonePt_hist->Fill(events->muStandAlonePt[upper_index],1.0);
			Upper_StandAloneEta_hist->Fill(events->muStandAloneEta[upper_index],1.0);
			Upper_StandAlonePhi_hist->Fill(events->muStandAlonePhi[upper_index],1.0);
			Upper_StandAloneTrackNormalizedChi2_hist->Fill(events->muStandAloneTrackNormalizedChi2[upper_index],1.0);
			Upper_StandAloneTrackDxy_hist->Fill(events->muStandAloneTrackDxy[upper_index],1.0);
			Upper_StandAloneTrackDz_hist->Fill(events->muStandAloneTrackDz[upper_index],1.0);
			Upper_StandAloneTrackNHitsMuon_hist->Fill(events->muStandAloneTrackNHitsMuon[upper_index],1.0);
			Upper_StandAloneTrackNHitsCsc_hist->Fill(events->muStandAloneTrackNHitsCsc[upper_index],1.0);
			Upper_StandAloneTrackNHitsDt_hist->Fill(events->muStandAloneTrackNHitsDt[upper_index],1.0);
			Upper_StandAloneTrackNHitsRpc_hist->Fill(events->muStandAloneTrackNHitsRpc[upper_index],1.0);
			Upper_StandAloneTrackNStations_hist->Fill(events->muStandAloneTrackNStations[upper_index],1.0);
			Upper_StandAloneTrackNChambersCsc_hist->Fill(events->muStandAloneTrackNChambersCsc[upper_index],1.0);
			Upper_StandAloneTrackNChambersDt_hist->Fill(events->muStandAloneTrackNChambersDt[upper_index],1.0);
			Upper_StandAloneTrackNChambersRpc_hist->Fill(events->muStandAloneTrackNChambersRpc[upper_index],1.0);
			Upper_StandAloneTrackDtTofNDof_hist->Fill(events->muStandAloneTrackDtTofNDof[upper_index],1.0);
			Upper_StandAloneTrackDtTofInverseBetaLS_hist->Fill(events->muStandAloneTrackDtTofInverseBetaLS[upper_index],1.0);
			Upper_StandAloneTrackDtTofInverseBetaLSErr_hist->Fill(events->muStandAloneTrackDtTofInverseBetaLSErr[upper_index],1.0);
			Upper_StandAloneTrackDtTofYIntercept_hist->Fill(events->muStandAloneTrackDtTofYIntercept[upper_index],1.0);
			Upper_StandAloneTrackDtTofYInterceptErr_hist->Fill(events->muStandAloneTrackDtTofYInterceptErr[upper_index],1.0);
			Upper_StandAloneTrackDtTofChi2Dof_hist->Fill(events->muStandAloneTrackDtTofChi2Dof[upper_index],1.0);
			Upper_StandAloneTrackNHitsRpc_Upper_StandAloneTrackNormalizedChi2_hist->Fill(events->muStandAloneTrackNHitsRpc[upper_index],events->muStandAloneTrackNormalizedChi2[upper_index],1.0);
			Upper_StandAloneTrackNHitsRpc_Upper_StandAloneTrackNHitsDt_hist->Fill(events->muStandAloneTrackNHitsRpc[upper_index],events->muStandAloneTrackNHitsDt[upper_index],1.0);
			
			Lower_StandAlonePt_hist->Fill(events->muStandAlonePt[lower_index],1.0);
			Lower_StandAloneEta_hist->Fill(events->muStandAloneEta[lower_index],1.0);
			Lower_StandAlonePhi_hist->Fill(events->muStandAlonePhi[lower_index],1.0);
			Lower_StandAloneTrackNormalizedChi2_hist->Fill(events->muStandAloneTrackNormalizedChi2[lower_index],1.0);
			Lower_StandAloneTrackDxy_hist->Fill(events->muStandAloneTrackDxy[lower_index],1.0);
			Lower_StandAloneTrackDz_hist->Fill(events->muStandAloneTrackDz[lower_index],1.0);
			Lower_StandAloneTrackNHitsMuon_hist->Fill(events->muStandAloneTrackNHitsMuon[lower_index],1.0);
			Lower_StandAloneTrackNHitsCsc_hist->Fill(events->muStandAloneTrackNHitsCsc[lower_index],1.0);
			Lower_StandAloneTrackNHitsDt_hist->Fill(events->muStandAloneTrackNHitsDt[lower_index],1.0);
			Lower_StandAloneTrackNHitsRpc_hist->Fill(events->muStandAloneTrackNHitsRpc[lower_index],1.0);
			Lower_StandAloneTrackNStations_hist->Fill(events->muStandAloneTrackNStations[lower_index],1.0);
			Lower_StandAloneTrackNChambersCsc_hist->Fill(events->muStandAloneTrackNChambersCsc[lower_index],1.0);
			Lower_StandAloneTrackNChambersDt_hist->Fill(events->muStandAloneTrackNChambersDt[lower_index],1.0);
			Lower_StandAloneTrackNChambersRpc_hist->Fill(events->muStandAloneTrackNChambersRpc[lower_index],1.0);
			Lower_StandAloneTrackDtTofNDof_hist->Fill(events->muStandAloneTrackDtTofNDof[lower_index],1.0);
			Lower_StandAloneTrackDtTofInverseBetaLS_hist->Fill(events->muStandAloneTrackDtTofInverseBetaLS[lower_index],1.0);
			Lower_StandAloneTrackDtTofInverseBetaLSErr_hist->Fill(events->muStandAloneTrackDtTofInverseBetaLSErr[lower_index],1.0);
			Lower_StandAloneTrackDtTofYIntercept_hist->Fill(events->muStandAloneTrackDtTofYIntercept[lower_index],1.0);
			Lower_StandAloneTrackDtTofYInterceptErr_hist->Fill(events->muStandAloneTrackDtTofYInterceptErr[lower_index],1.0);
			Lower_StandAloneTrackDtTofChi2Dof_hist->Fill(events->muStandAloneTrackDtTofChi2Dof[lower_index],1.0);
			Lower_StandAloneTrackNHitsRpc_Lower_StandAloneTrackNormalizedChi2_hist->Fill(events->muStandAloneTrackNHitsRpc[lower_index],events->muStandAloneTrackNormalizedChi2[lower_index],1.0);
			Lower_StandAloneTrackNHitsRpc_Lower_StandAloneTrackNHitsDt_hist->Fill(events->muStandAloneTrackNHitsRpc[lower_index],events->muStandAloneTrackNHitsDt[lower_index],1.0);
			
			}//end of timeInOut cut for 2 muons
		      }//end of dt inv beta cut for 2 muons
		    }//end of rpc bx pattern cut for 2 muons
		  }//end of opp phi cut for cosmic enriched 2 muons
		}//end of opp eta cut for cosmic enriched 2 muons
	      }//end of number of dt hits cut for 2 muons
	    } //end of dist btw stations for 2 muons
	  }//end of if at least 1 RPC hit for 2 muons
	}//end of eta cut for 2 muons
      } //end of 2 cha cut for 2 muons
    }// end of Zmumu z-mass cut
  }//end of if 2 standalone muons in upper and lower with pt>30, 20
}//end of UpperAndLowerSA_counts()

void findTreevalues_makehistos_Ntuples_allsamples::printout_setup( StoppedHSCPMuonEvent* events){
  
  if(events->mu_StandAlone_N>0 || events->mcMuon_N>0 || events->mcTop_N>0 || events->mcW_N>0 || events->mcCMshower_N>0 || events->mcTau_N>0){
    cout<<"__________________________________________________________________________________________________________________________________________________________"<<endl;
    line++;
  }

  if (line==3 || line % 15 == 0) {
    //cout  << "                                                                                 Hits             Chambers" << endl;
    //cout  << "                                                      M_ID       M_W_ID          Hits             Chambers" << endl;
    cout  << "                                                      Status   Daughters  Moth  Moth_of_W " << endl;
    cout  << "                                                                             Hits                Chambers                           DT time" << endl;
    cout  << setw(7) << "Run Num ";
    cout  << setw(9) << "Event Num ";
    cout  << setw(8) << "SA/Gen ";
    cout  << setw(8) << "pT ";
    cout  << setw(7) << "eta ";
    cout  << setw(7) << "phi ";
    cout  << setw(7) << "charge ";
    cout  << setw(10) << "chi2 ";
    cout  << setw(14) << "RPC BXs ";
    cout  << setw(5) << "All ";
    cout  << setw(5) << "CSC ";
    cout  << setw(5) << "DT ";
    cout  << setw(5) << "RPC ";
    cout  << setw(5) << "Sts ";
    cout  << setw(5) << "CSC ";
    cout  << setw(5) << "DT ";
    cout  << setw(5) << "RPC ";
    cout  << setw(5) << "Dir ";
    cout  << setw(7) << "tInOut ";
    cout  << setw(7) << "1/beta ";
    cout  << setw(11) << "1/beta err  ";
    cout  << setw(5) << "chi2 ";
    cout  << setw(5) << "dEta " << endl;
    cout  << setw(5) << "dPhi " << endl;
    line = line + 2;
  }
}//end of printout_setup()

void findTreevalues_makehistos_Ntuples_allsamples::printout_gen( StoppedHSCPMuonEvent* events){
  cout  << setw(7) << events->run;
  cout  << setw(9) << events->id;
  cout  << setw(8) << "SPart"<<" ";
  cout  << fixed << setprecision(PtPrecision)  << setw(8) << events->mcStoppedParticleZ[0]/10.;
  cout  << fixed << setprecision(EtaPrecision) << setw(7) << events->mcStoppedParticleR[0]/10.;
  cout  << fixed << setprecision(PhiPrecision) << setw(7) << events->mcStoppedParticlePhi[0];
  cout  << fixed << setw(7) << " ";
  cout  << fixed << setw(7) << " ";
  cout  << fixed << setw(14) << " ";
  cout  << fixed << setw(5) << " ";
  cout  << fixed << setw(5) << " ";
  cout  << fixed << setw(5) << " ";
  cout  << fixed << setw(5) << " ";
  cout  << fixed << setw(5) << " ";
  cout  << fixed << setw(5) << " ";
  cout  << fixed << setw(5) << " ";
  cout  << fixed << setw(5) << " ";
  cout  << fixed << setw(5) << " ";
  cout  << fixed << setw(7) << " " << endl;
  line++;
  
  for (UInt_t j=0; j<events->mcTop_N; j++) {
    TString Daughters = " ";
    for (UInt_t k=0; k<events->mcTopDaughterId.at(j).size(); k++) {
      //cout<<"bx for hit "<<k<<" is: "<<events->muStandAloneTrackRpcHitBx.at(j).at(k)<<endl;                                                                                                    
      string each_daughter;
      ostringstream convert;
      convert<<events->mcTopDaughterId.at(j).at(k);
      each_daughter = convert.str();
      Daughters = Daughters + each_daughter + " ";
    }
    
    cout  << setw(7) << events->run;
    cout  << setw(9) << events->id;
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
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(7) << " " << endl;
    line++;
    }//end of loop over tops
  
  for (UInt_t j=0; j<events->mcStau_N; j++) {
    TString Daughters = " ";
    for (UInt_t k=0; k<events->mcStauDaughterId.at(j).size(); k++) {
      //cout<<"bx for hit "<<k<<" is: "<<events->muStandAloneTrackRpcHitBx.at(j).at(k)<<endl;                                                                                                    
      string each_daughter;
      ostringstream convert;
      convert<<events->mcStauDaughterId.at(j).at(k);
      each_daughter = convert.str();
      Daughters = Daughters + each_daughter + " ";
    }
    
    cout  << setw(7) << events->run;
    cout  << setw(9) << events->id;
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
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(7) << " " << endl;
    line++;
  }//end of loop over staus
  
  for (UInt_t j=0; j<events->mcGluino_N; j++) {
    TString Daughters = " ";
    for (UInt_t k=0; k<events->mcGluinoDaughterId.at(j).size(); k++) {
      //cout<<"bx for hit "<<k<<" is: "<<events->muStandAloneTrackRpcHitBx.at(j).at(k)<<endl;                                                                                                    
      string each_daughter;
      ostringstream convert;
      convert<<events->mcGluinoDaughterId.at(j).at(k);
      each_daughter = convert.str();
      Daughters = Daughters + each_daughter + " ";
    }
    
    cout  << setw(7) << events->run;
    cout  << setw(9) << events->id;
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
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(7) << " " << endl;
    line++;
  }//end of loop over gluinos
  
  for (UInt_t j=0; j<events->mcTauPrime_N; j++) {
    TString Daughters = " ";
    for (UInt_t k=0; k<events->mcTauPrimeDaughterId.at(j).size(); k++) {
      //cout<<"bx for hit "<<k<<" is: "<<events->muStandAloneTrackRpcHitBx.at(j).at(k)<<endl;                                                                                                    
      string each_daughter;
      ostringstream convert;
      convert<<events->mcTauPrimeDaughterId.at(j).at(k);
      each_daughter = convert.str();
      Daughters = Daughters + each_daughter + " ";
    }
    
    cout  << setw(7) << events->run;
    cout  << setw(9) << events->id;
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
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(7) << " " << endl;
    line++;
  }//end of loop over gluinos
  
  for (UInt_t j=0; j<events->mcNeutralino_N; j++) {
    TString Daughters = " ";
    for (UInt_t k=0; k<events->mcNeutralinoDaughterId.at(j).size(); k++) {
      //cout<<"bx for hit "<<k<<" is: "<<events->muStandAloneTrackRpcHitBx.at(j).at(k)<<endl;                                                                                                    
      string each_daughter;
      ostringstream convert;
      convert<<events->mcNeutralinoDaughterId.at(j).at(k);
      each_daughter = convert.str();
      Daughters = Daughters + each_daughter + " ";
    }
    
    cout  << setw(7) << events->run;
    cout  << setw(9) << events->id;
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
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(7) << " " << endl;
    line++;
  }//end of loop over neutralinos
  
  for (UInt_t j=0; j<events->mcGravitino_N; j++) {
    TString Daughters = " ";
    for (UInt_t k=0; k<events->mcGravitinoDaughterId.at(j).size(); k++) {
      //cout<<"bx for hit "<<k<<" is: "<<events->muStandAloneTrackRpcHitBx.at(j).at(k)<<endl;                                                                                                    
      string each_daughter;
      ostringstream convert;
      convert<<events->mcGravitinoDaughterId.at(j).at(k);
      each_daughter = convert.str();
      Daughters = Daughters + each_daughter + " ";
    }
    
    cout  << setw(7) << events->run;
    cout  << setw(9) << events->id;
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
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(7) << " " << endl;
    line++;
  }//end of loop over gravitinos
  
  for (UInt_t j=0; j<events->mcW_N; j++) {
    TString Daughters = " ";
    for (UInt_t k=0; k<events->mcWDaughterId.at(j).size(); k++) {
      //cout<<"bx for hit "<<k<<" is: "<<events->muStandAloneTrackRpcHitBx.at(j).at(k)<<endl;                                                                                                    
      string each_daughter;
      ostringstream convert;
      convert<<events->mcWDaughterId.at(j).at(k);
      each_daughter = convert.str();
      Daughters = Daughters + each_daughter + " ";
    }
    
    cout  << setw(7) << events->run;
    cout  << setw(9) << events->id;
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
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(7) << " " << endl;
    line++;
  }//end of loop over Ws
  
  for (UInt_t j=0; j<events->mcCMshower_N; j++) {
    TString Daughters = " ";
    for (UInt_t k=0; k<events->mcCMshowerDaughterId.at(j).size(); k++) {
      //cout<<"bx for hit "<<k<<" is: "<<events->muStandAloneTrackRpcHitBx.at(j).at(k)<<endl;                                                                                                    
      string each_daughter;
      ostringstream convert;
      convert<<events->mcCMshowerDaughterId.at(j).at(k);
      each_daughter = convert.str();
      Daughters = Daughters + each_daughter + " ";
    }
    
    cout  << setw(7) << events->run;
    cout  << setw(9) << events->id;
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
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(7) << " " << endl;
    line++;
  }//end of loop over CMshowers
  
  for (UInt_t j=0; j<events->mcTau_N; j++) {
    TString Daughters = " ";
    for (UInt_t k=0; k<events->mcTauDaughterId.at(j).size(); k++) {
      //cout<<"bx for hit "<<k<<" is: "<<events->muStandAloneTrackRpcHitBx.at(j).at(k)<<endl;                                                                                                    
      string each_daughter;
      ostringstream convert;
      convert<<events->mcTauDaughterId.at(j).at(k);
      each_daughter = convert.str();
      Daughters = Daughters + each_daughter + " ";
    }
    
    cout  << setw(7) << events->run;
    cout  << setw(9) << events->id;
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
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(5) << " ";
    cout  << fixed << setw(7) << " " << endl;
    line++;
  }//end of loop over taus
  
  for (UInt_t j=0; j<events->mcMuon_N; j++) {
    TString Daughters = " ";
    for (UInt_t k=0; k<events->mcMuonDaughterId.at(j).size(); k++) {
      //cout<<"bx for hit "<<k<<" is: "<<events->muStandAloneTrackRpcHitBx.at(j).at(k)<<endl;                                                                                                    
      string each_daughter;
      ostringstream convert;
      convert<<events->mcMuonDaughterId.at(j).at(k);
      each_daughter = convert.str();
      Daughters = Daughters + each_daughter + " ";
    }
    //if(events->mcMuonStatus[j]==1){                                                                                                                                                            
    //cout<<"For generated mu number "<<j<<",  pt is: "<<events->mcMuonPt[j]<<", eta is: "<<events->mcMuonEta[j]<<", phi is: "<<events->mcMuonPhi[j]<<", charge is: "<<events->mcMuonCharge[j]<<", mass is: "<<events->mcMuonMass[j]<<endl;                                                                                                                                                            
      
      cout  << setw(7) << events->run;
      cout  << setw(9) << events->id;
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
      cout  << fixed << setw(5) << " ";
      cout  << fixed << setw(5) << " ";
      cout  << fixed << setw(5) << " ";
      cout  << fixed << setw(5) << " ";
      cout  << fixed << setw(5) << " ";
      cout  << fixed << setw(5) << " ";
      cout  << fixed << setw(5) << " ";
      cout  << fixed << setw(7) << " " << endl;
      line++;
  }//end of loop over mc muons
}//end of printout_gen()

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

    double segment_dPhi, segment_dEta;
    //double segment_dR = dR_OppositeSeg(events, j, segment_dPhi, segment_dEta);

    cout  << setw(7) << events->run;
    cout  << setw(9) << events->id;
    cout  << setw(8) << "SA"<<j;
    cout  << fixed << setprecision(PtPrecision)  << setw(8) << events->muStandAlonePt[j];
    cout  << fixed << setprecision(EtaPrecision) << setw(7) << events->muStandAloneEta[j];
    cout  << fixed << setprecision(PhiPrecision) << setw(7) << events->muStandAlonePhi[j];
    cout  << fixed << setprecision(ChargePrecision) << setw(7) << events->muStandAloneCharge[j];
    cout  << fixed << setprecision(X2DOFPrecision) << setw(10) << events->muStandAloneTrackNormalizedChi2[j];
    cout  << fixed << setw(14) << BXs;
    cout  << fixed << setw(5) << events->muStandAloneTrackNHitsMuon[j];
    cout  << fixed << setw(5) << events->muStandAloneTrackNHitsCsc[j];
    cout  << fixed << setw(5) << events->muStandAloneTrackNHitsDt[j];
    cout  << fixed << setw(5) << events->muStandAloneTrackRpcHitZ.at(j).size();
    cout  << fixed << setw(5) << events->muStandAloneTrackNStations[j];
    cout  << fixed << setw(5) << events->muStandAloneTrackNChambersCsc[j];
    cout  << fixed << setw(5) << events->muStandAloneTrackNChambersDt[j];
    cout  << fixed << setw(5) << events->muStandAloneTrackNChambersRpc[j];
    cout  << fixed << setw(5) << events->muStandAloneTofDirection[j];
    cout  << fixed << setprecision(TimeAtIpInOutPrecision) << setw(7) << events->muStandAloneTofTimeAtIpInOut[j];
    cout  << fixed << setw(7) << events->muStandAloneTrackDtTofInverseBetaLS[j];
    cout  << fixed << setw(11) << events->muStandAloneTrackDtTofInverseBetaLSErr[j];
    cout  << fixed << setw(5) << events->muStandAloneTrackDtTofChi2Dof[j];
    cout  << fixed << setw(5) << segment_dEta;
    cout  << fixed << setw(5) << segment_dPhi << endl;
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

    cout  << setw(7) << events->run;
    cout  << setw(9) << events->id;
    cout  << setw(8) << "RSA"<<j;
    cout  << fixed << setprecision(PtPrecision)  << setw(8) << events->muRefittedStandAlonePt[j];
    cout  << fixed << setprecision(EtaPrecision) << setw(7) << events->muRefittedStandAloneEta[j];
    cout  << fixed << setprecision(PhiPrecision) << setw(7) << events->muRefittedStandAlonePhi[j];
    cout  << fixed << setprecision(ChargePrecision) << setw(7) << events->muRefittedStandAloneCharge[j];
    cout  << fixed << setprecision(X2DOFPrecision) << setw(10) << events->muRefittedStandAloneTrackNormalizedChi2[j];
    //cout  << fixed << setw(14) << BX;
    cout  << fixed << setw(14) << " ";
    cout  << fixed << setw(5) << events->muRefittedStandAloneTrackNHitsMuon[j];
    cout  << fixed << setw(5) << events->muRefittedStandAloneTrackNHitsCsc[j];
    cout  << fixed << setw(5) << events->muRefittedStandAloneTrackNHitsDt[j];
    //cout  << fixed << setw(5) << events->muRefittedStandAloneTrackRpcHitZ.at(j).size();
    cout  << fixed << setw(5) << events->muRefittedStandAloneTrackNHitsRpc[j];
    cout  << fixed << setw(5) << events->muRefittedStandAloneTrackNStations[j];
    cout  << fixed << setw(5) << events->muRefittedStandAloneTrackNChambersCsc[j];
    cout  << fixed << setw(5) << events->muRefittedStandAloneTrackNChambersDt[j];
    cout  << fixed << setw(5) << events->muRefittedStandAloneTrackNChambersRpc[j];
    //cout  << fixed << setw(5) << events->muRefittedStandAloneTofDirection[j];
    cout  << fixed << setw(5) << " ";
    //cout  << fixed << setprecision(TimeAtIpInOutPrecision) << setw(7) << events->muRefittedStandAloneTofTimeAtIpInOut[j];
    cout  << fixed << setprecision(TimeAtIpInOutPrecision) << setw(7) << " ";
    //cout  << fixed << setw(7) << events->muRefittedStandAloneTrackDtTofInverseBetaLS[j];
    cout  << fixed << setw(7) << " ";
    //cout  << fixed << setw(11) << events->muRefittedStandAloneTrackDtTofInverseBetaLSErr[j];
    cout  << fixed << setw(11) << " ";
    //cout  << fixed << setw(5) << events->muRefittedStandAloneTrackDtTofChi2Dof[j];
    cout  << fixed << setw(5) << " ";
    //cout  << fixed << setw(5) << segment_dEta << endl;
    cout  << fixed << setw(5) << " ";
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

    cout  << setw(7) << events->run;
    cout  << setw(9) << events->id;
    cout  << setw(8) << "Cos"<<j;
    cout  << fixed << setprecision(PtPrecision)  << setw(8) << events->muCosmicTrackPt[j];
    cout  << fixed << setprecision(EtaPrecision) << setw(7) << events->muCosmicTrackEta[j];
    cout  << fixed << setprecision(PhiPrecision) << setw(7) << events->muCosmicTrackPhi[j];
    cout  << fixed << setprecision(ChargePrecision) << setw(7) << events->muCosmicTrackCharge[j];
    cout  << fixed << setprecision(X2DOFPrecision) << setw(10) << events->muCosmicTrackNormalizedChi2[j];
    //cout  << fixed << setw(14) << BXs;
    cout  << fixed << setw(14) << " ";
    cout  << fixed << setw(5) << events->muCosmicTrackNHitsMuon[j];
    cout  << fixed << setw(5) << events->muCosmicTrackNHitsCsc[j];
    cout  << fixed << setw(5) << events->muCosmicTrackNHitsDt[j];
    //cout  << fixed << setw(5) << events->muCosmicTrackRpcHitZ.at(j).size();
    cout  << fixed << setw(5) << events->muCosmicTrackNHitsRpc[j];
    cout  << fixed << setw(5) << events->muCosmicTrackNStations[j];
    cout  << fixed << setw(5) << events->muCosmicTrackNChambersCsc[j];
    cout  << fixed << setw(5) << events->muCosmicTrackNChambersDt[j];
    cout  << fixed << setw(5) << events->muCosmicTrackNChambersRpc[j];
    //cout  << fixed << setw(5) << events->muCosmicTofDirection[j];
    cout  << fixed << setw(5) << " ";
    //cout  << fixed << setprecision(TimeAtIpInOutPrecision) << setw(7) << events->muCosmicTofTimeAtIpInOut[j];
    cout  << fixed << setw(7) << " ";
    //cout  << fixed << setw(7) << events->muCosmicTrackDtTofInverseBetaLS[j];
    cout  << fixed << setw(7) << " ";
    //cout  << fixed << setw(11) << events->muCosmicTrackDtTofInverseBetaLSErr[j];
    cout  << fixed << setw(11) << " ";
    //cout  << fixed << setw(5) << events->muCosmicTrackDtTofChi2Dof[j];
    cout  << fixed << setw(5) << " ";
    //cout  << fixed << setw(5) << segment_dEta << endl;
    cout  << fixed << setw(5) << " ";
    //cout  << fixed << setw(5) << segment_dPhi << endl;
    cout  << fixed << setw(5) << " " << endl;
    line++;
  }//end of loop over cosmic muons
}//end of printout_cosmic()

void findTreevalues_makehistos_Ntuples_allsamples::printout_L2( StoppedHSCPMuonEvent* events){
  //cout<<"__________________________________________________________________________________________________________________________________________________________"<<endl;
  //line++;

  for (UInt_t j=0; j<events->hlt20Cha2Muon_N; j++) {
    cout  << setw(7) << events->run;
    cout  << setw(9) << events->id;
    cout  << setw(8) << "L2 "<<j;
    cout  << fixed << setprecision(PtPrecision)  << setw(8) << events->hlt20Cha2MuonPt[j];
    cout  << fixed << setprecision(EtaPrecision) << setw(7) << events->hlt20Cha2MuonEta[j];
    cout  << fixed << setprecision(PhiPrecision) << setw(7) << events->hlt20Cha2MuonPhi[j]<<endl;
    line++;
  }//end of loop over L2 muons
}//end of printout_L2()

void findTreevalues_makehistos_Ntuples_allsamples::printout_L1( StoppedHSCPMuonEvent* events){
  //cout<<"__________________________________________________________________________________________________________________________________________________________"<<endl;
  //line++;

  for (UInt_t j=0; j<events->l1Muon_N; j++) {
    cout  << setw(7) << events->run;
    cout  << setw(9) << events->id;
    cout  << setw(8) << "L1 "<<j;
    cout  << fixed << setprecision(PtPrecision)  << setw(8) << events->l1MuonPt[j];
    cout  << fixed << setprecision(EtaPrecision) << setw(7) << events->l1MuonEta[j];
    cout  << fixed << setprecision(PhiPrecision) << setw(7) << events->l1MuonPhi[j]<<endl;
    line++;
  }//end of loop over L1 muons
}//end of printout_L1()

int main(int argc, char* argv[]){
  if(argc!=39){
    cout<<"ERROR, need more arguments!"<<endl;
    cout<<"seeing "<<argc<<" arguments"<<endl;
    return 1;
  }

  string file_dataset, BxCut, CavCut, GenMuCut, SACut, GenMuMatchedCut, TriggerCut, PtCut, ChaCut, EtaCut, UpperCut, RpcCut, DisStCut, RpcBxCut, DtHitsCut, CscHitsCut, DtInvBetaCut, TimeInOutCut, OppEtaCut, OppPhiCut, TightPhi, CosEnrich, resT3, Printout;
  TString BxCutValue, PtCutValue, Pt0CutValue, Pt1CutValue, ChaCutValue, EtaCutValue, RpcCutValue, DisStCutValue, RpcBxCutValue, DtHitsCutValue, CscHitsCutValue, DtInvBetaCutValue, TimeInOutCutValue, OppEtaCutValue, OppPhiCutValue;

  file_dataset = "NoBPTX_Run2012B";
  BxCut = "wBxCut";
  CavCut = "wCavCut";
  GenMuCut = "wGenMuCut";
  SACut = "wSACut";
  GenMuMatchedCut = "wGenMuMatchedCut";
  TriggerCut = "wTriggerCut";
  PtCut = "wPtCut";
  ChaCut = "wChaCut";
  EtaCut = "wEtaCut";
  UpperCut = "wUpperCut";
  RpcCut = "wRpcCut";
  DisStCut = "wDisStCut";
  RpcBxCut = "wRpcBxCut";
  DtHitsCut = "wDtHitsCut";
  CscHitsCut = "wCscHitsCut";
  DtInvBetaCut = "wDtInvBetaCut";
  TimeInOutCut = "wTimeInOutCut";
  OppEtaCut = "wOppEtaCut";
  OppPhiCut = "wOppPhiCut";
  TightPhi = "wTightPhi";
  CosEnrich = "wCosEnrich";
  resT3 = "T3";
  Printout = "wPrintout";

  BxCutValue = "2";
  PtCutValue = "30.";
  Pt0CutValue = "30.";
  Pt1CutValue = "20.";
  ChaCutValue = "1";
  EtaCutValue = "1.0";
  RpcCutValue = "2";
  DisStCutValue = "2";
  DtHitsCutValue = "8";
  CscHitsCutValue = "0";
  DtInvBetaCutValue = "0.7";
  TimeInOutCutValue = "0.";
  OppEtaCutValue = "0.1";
  OppPhiCutValue = "0.1";
  
  if(argc==39){
    file_dataset = argv[1];
    BxCut = argv[2];
    CavCut = argv[3];
    GenMuCut = argv[4];
    SACut = argv[5];
    GenMuMatchedCut = argv[6];
    TriggerCut = argv[7];
    PtCut = argv[8];
    ChaCut = argv[9];
    EtaCut = argv[10];
    UpperCut = argv[11];
    RpcCut = argv[12];
    DisStCut = argv[13];
    RpcBxCut = argv[14];
    DtHitsCut = argv[15];
    CscHitsCut = argv[16];
    DtInvBetaCut = argv[17];
    TimeInOutCut = argv[18];
    OppEtaCut = argv[19];
    OppPhiCut = argv[20];
    TightPhi = argv[21];
    CosEnrich = argv[22];
    resT3 = argv[23];
    Printout = argv[24];

    BxCutValue = argv[25];
    PtCutValue = argv[26];
    Pt0CutValue = argv[27];
    Pt1CutValue = argv[28];
    ChaCutValue = argv[29];
    EtaCutValue = argv[30];
    RpcCutValue = argv[31];
    DisStCutValue = argv[32];
    DtHitsCutValue = argv[33];
    CscHitsCutValue = argv[34];
    DtInvBetaCutValue = argv[35];
    TimeInOutCutValue = argv[36];
    OppEtaCutValue = argv[37];
    OppPhiCutValue = argv[38];

    cout<<", file_dataset is: "<<file_dataset<<", BxCut is: "<<BxCut<<", CavCut is: "<<CavCut<<", GenMuCut is: "<<GenMuCut<<", SA cut is: "<<SACut<<", GenMuMatchedCut is; "<<GenMuMatchedCut<<", TriggerCut is: "<<TriggerCut<<", PtCut is: "<<PtCut<<", ChaCut is: "<<ChaCut<<", EtaCut is: "<<EtaCut<<", UpperCut is: "<<UpperCut<<", RpcCut is: "<<RpcCut<<", DisStCut is: "<<DisStCut<<", RpcBxCut is: "<<RpcBxCut<<", DtHitsCut is: "<<DtHitsCut<<", CscHitsCut is: "<<CscHitsCut<<", DtInvBetaCut is: "<<DtInvBetaCut<<", TimeInOutCut is: "<<TimeInOutCut<<", OppEtaCut is: "<<OppEtaCut<<", OppPhiCut is: "<<OppPhiCut<<", TightPhi is: "<<TightPhi<<", CosEnrich is: "<<CosEnrich<<", resT3 is: "<<resT3<<", Printout is "<<Printout<<endl;
  }

  TH1D::SetDefaultSumw2();

  findTreevalues_makehistos_Ntuples_allsamples analyzer(argc, argv);

  analyzer.loop(file_dataset, BxCut, CavCut, GenMuCut, SACut, GenMuMatchedCut, TriggerCut, PtCut, ChaCut, EtaCut, UpperCut, RpcCut, DisStCut, RpcBxCut, DtHitsCut, CscHitsCut, DtInvBetaCut, TimeInOutCut, OppEtaCut, OppPhiCut, TightPhi, CosEnrich, resT3, Printout, BxCutValue, PtCutValue, Pt0CutValue, Pt1CutValue, ChaCutValue, EtaCutValue, RpcCutValue, DisStCutValue, DtHitsCutValue, CscHitsCutValue, DtInvBetaCutValue, TimeInOutCutValue, OppEtaCutValue, OppPhiCutValue);
}

void findTreevalues_makehistos_Ntuples_allsamples::loop(string& file_dataset, string& BxCut, string& CavCut, string& GenMuCut, string& SACut, string& GenMuMatchedCut, string& TriggerCut, string& PtCut, string& ChaCut, string& EtaCut, string& UpperCut, string& RpcCut, string& DisStCut, string& RpcBxCut, string& DtHitsCut, string& CscHitsCut, string& DtInvBetaCut, string& TimeInOutCut, string& OppEtaCut, string& OppPhiCut, string& TightPhi, string& CosEnrich, string& resT3, string& Printout, TString& BxCutValue, TString& PtCutValue, TString& Pt0CutValue, TString& Pt1CutValue, TString& ChaCutValue, TString& EtaCutValue, TString& RpcCutValue, TString& DisStCutValue, TString& DtHitsCutValue, TString& CscHitsCutValue, TString& DtInvBetaCutValue, TString& TimeInOutCutValue, TString& OppEtaCutValue, TString& OppPhiCutValue){

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
  if(file_dataset_ == "NoBP" || file_dataset_ == "Sing" || file_dataset_ == "Zmum") is_data=true;

  TString file = "blah";
  if(host_=="cmsl"){
    //if(resT3=="T3") file = "dcap:///pnfs/cms/WAX/11/store/user/alimena/Ntuples/" + file_dataset + "/stoppedHSCPMuonTree.root";
    //else if(resT3=="res") file = "dcap:///pnfs/cms/WAX/resilient/alimena/Ntuples/" + file_dataset + "/stoppedHSCPMuonTree.root";
    //else cout<<"problem with resT3!!!!!!"<<endl;
    file = "/uscms_data/d3/alimena/Ntuples/" + file_dataset + "/stoppedHSCPMuonTree.root";
  }
  if(host_=="brux") file = "/mnt/hadoop/users/alimena/CMS/Ntuples/" + file_dataset + "/stoppedHSCPMuonTree.root";
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

  if (CscHitsCut=="wCscHitsCut") doCscHitsCut = true;
  if (CscHitsCut=="woCscHitsCut") doCscHitsCut = false;
  cout<<"doCscHitsCut is: "<<doCscHitsCut<<endl;

  if (DtInvBetaCut=="wDtInvBetaCut") doDtInvBetaCut = true;
  if (DtInvBetaCut=="woDtInvBetaCut") doDtInvBetaCut = false;
  cout<<"doDtInvBetaCut is: "<<doDtInvBetaCut<<endl;

  if (TimeInOutCut=="wTimeInOutCut") doTimeInOutCut = true;
  if (TimeInOutCut=="woTimeInOutCut") doTimeInOutCut = false;
  cout<<"doTimeInOutCut is: "<<doTimeInOutCut<<endl;

  if (OppEtaCut=="wOppEtaCut") doOppEtaCut = true;
  if (OppEtaCut=="woOppEtaCut") doOppEtaCut = false;
  cout<<"doOppEtaCut is: "<<doOppEtaCut<<endl;

  if (OppPhiCut=="wOppPhiCut") doOppPhiCut = true;
  if (OppPhiCut=="woOppPhiCut") doOppPhiCut = false;
  cout<<"doOppPhiCut is: "<<doOppPhiCut<<endl;

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
  sscanf(PtCutValue,"%f",&PtCutValue_);
  sscanf(Pt0CutValue,"%f",&Pt0CutValue_);
  sscanf(Pt1CutValue,"%f",&Pt1CutValue_);
  sscanf(ChaCutValue,"%d",&ChaCutValue_);
  sscanf(EtaCutValue,"%f",&EtaCutValue_);
  sscanf(RpcCutValue,"%d",&RpcCutValue_);
  sscanf(DisStCutValue,"%d",&DisStCutValue_);
  sscanf(DtHitsCutValue,"%d",&DtHitsCutValue_);
  sscanf(CscHitsCutValue,"%d",&CscHitsCutValue_);
  sscanf(DtInvBetaCutValue,"%f",&DtInvBetaCutValue_);
  sscanf(TimeInOutCutValue,"%f",&TimeInOutCutValue_);
  sscanf(OppEtaCutValue,"%f",&OppEtaCutValue_);
  sscanf(OppPhiCutValue,"%f",&OppPhiCutValue_);

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
    }
  }

  TString new_file = "blah2";
  if ((BxCut=="wBxCut" || BxCut=="wBxCut") && (CavCut=="wCavCut" || CavCut=="woCavCut") && (GenMuCut=="wGenMuCut" || GenMuCut=="woGenMuCut") && (SACut=="wSACut" || SACut=="woSACut")  && (GenMuMatchedCut=="wGenMuMatchedCut" || GenMuMatchedCut=="woGenMuMatchedCut") && (TriggerCut=="wTriggerCut" || TriggerCut=="woTriggerCut") && (PtCut=="wPtCut" || PtCut=="woPtCut") && (ChaCut=="wChaCut" || ChaCut=="woChaCut")  && (EtaCut=="wEtaCut" || EtaCut=="woEtaCut")  && (UpperCut=="wUpperCut" || UpperCut=="woUpperCut") && (RpcCut=="wRpcCut" || RpcCut=="woRpcCut") && (DisStCut=="wDisStCut" || DisStCut=="woDisStCut") && (RpcBxCut=="wRpcBxCut" || RpcBxCut=="woRpcBxCut") && (DtHitsCut=="wDtHitsCut" || DtHitsCut=="woDtHitsCut") && (CscHitsCut=="wCscHitsCut" || CscHitsCut=="woCscHitsCut") && (DtInvBetaCut=="wDtInvBetaCut" || DtInvBetaCut=="woDtInvBetaCut") && (TimeInOutCut=="wTimeInOutCut" || TimeInOutCut=="woTimeInOutCut") && (OppEtaCut=="wOppEtaCut" || OppEtaCut=="woOppEtaCut") && (OppPhiCut=="wOppPhiCut" || OppPhiCut=="woOppPhiCut") && (TightPhi=="wTightPhi" || TightPhi=="woTightPhi") && (CosEnrich=="wCosEnrich" || CosEnrich=="woCosEnrich")){
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
  if (PtCut!="wPtCut" && PtCut!="woPtCut") cout<<"problem w PtCut assignment!!!"<<endl;
  if (ChaCut!="wChaCut" && ChaCut!="woChaCut") cout<<"problem w ChaCut assignment!!!"<<endl;
  if (EtaCut!="wEtaCut" && EtaCut!="woEtaCut") cout<<"problem w EtaCut assignment!!!"<<endl;
  if (UpperCut!="wUpperCut" && UpperCut!="woUpperCut") cout<<"problem w UpperCut assignment!!!"<<endl;
  if (RpcCut!="wRpcCut" && RpcCut!="woRpcCut") cout<<"problem w RpcCut assignment!!!"<<endl;
  if (DisStCut!="wDisStCut" && DisStCut!="woDisStCut") cout<<"problem w DisStCut assignment!!!"<<endl;
  if (RpcBxCut!="wRpcBxCut" && RpcBxCut!="woRpcBxCut") cout<<"problem w RpcBxCut assignment!!!"<<endl;
  if (DtHitsCut!="wDtHitsCut" && DtHitsCut!="woDtHitsCut") cout<<"problem w DtHitsCut assignment!!!"<<endl;
  if (CscHitsCut!="wCscHitsCut" && CscHitsCut!="woCscHitsCut") cout<<"problem w CscHitsCut assignment!!!"<<endl;
  if (DtInvBetaCut!="wDtInvBetaCut" && DtInvBetaCut!="woDtInvBetaCut") cout<<"problem w DtInvBetaCut assignment!!!"<<endl;
  if (TimeInOutCut!="wTimeInOutCut" && TimeInOutCut!="woTimeInOutCut") cout<<"problem w TimeInOutCut assignment!!!"<<endl;
  if (OppEtaCut!="wOppEtaCut" && OppEtaCut!="woOppEtaCut") cout<<"problem w OppEtaCut assignment!!!"<<endl;
  if (OppPhiCut!="wOppPhiCut" && OppPhiCut!="woOppPhiCut") cout<<"problem w OppPhiCut assignment!!!"<<endl;
  if (TightPhi!="wTightPhi" && TightPhi!="woTightPhi") cout<<"problem w TightPhi assignment!!!"<<endl;
  if (CosEnrich!="wCosEnrich" && CosEnrich!="woCosEnrich") cout<<"problem w CosEnrich assignment!!!"<<endl;
  if (Printout!="wPrintout" && Printout!="woPrintout") cout<<"problem w Printout assignment!!!"<<endl;

  TFile* fnew = new TFile("blah","recreate");
  if(Printout=="woPrintout"){
    fnew = new TFile(new_file, "recreate");
    cout<<"opened output file"<<endl;
  }


  //get tree
  TTree* tree = (TTree*)f1->Get("stoppedHSCPMuonTree/StoppedHSCPMuonTree");
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
  
  for (Int_t i=0; i<nentries; i++) {
  //for (Int_t i=0; i<2000; i++) {    
  //for (Int_t i=0; i<100; i++) {
    tree->GetEntry(i);
    if(is_data && i%50000==0) cout<<"i is: "<<i<<endl;
    if(!is_data && i%5000==0) cout<<"i is: "<<i<<endl;

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
    bool status1muonFromMchamp_[15];
    bool status1muonFromMuon_[15];
    for (UInt_t j=0; j<events->mcMuon_N; j++) {
      status1muon_[j]=false;
      status1muonFromMchamp_[j]=false;
      status1muonFromMuon_[j]=false;
    }
    int good_genMuons = 0;
    double genMu0_px, genMu0_py, genMu0_pz, genMu0_pt, genMu0_p, genMu0_eta, genMu0_phi, genMu0_charge;
    double genMu1_px, genMu1_py, genMu1_pz, genMu1_pt, genMu1_p, genMu1_eta, genMu1_phi, genMu1_charge;
    Double_t angle=-999.;
    double genMuUpper_px, genMuUpper_py, genMuUpper_pz, genMuUpper_pt, genMuUpper_p, genMuUpper_eta, genMuUpper_phi, genMuUpper_charge;
    double genMuLower_px, genMuLower_py, genMuLower_pz, genMuLower_pt, genMuLower_p, genMuLower_eta, genMuLower_phi, genMuLower_charge;

    //find out what's happening at the gen level for signal MC
    if(file_dataset_ == "stop") stops(events, WFromTop, status1muon, status1muonFromW, status1muonFromMuon);
    if(file_dataset_ == "glui") gluinos(events, status1muon, status1muonFromW, status1muonFromTau, status1muonFromMuon,
					status1muonFromBbaryon, status1muonFromCbaryon, status1muonFromSbaryon, status1muonFromBmeson, status1muonFromCmeson,
					status1muonFromJPsi, status1muonFromLightMeson);
    if(file_dataset_ == "mcha") mchamps(events, muonFromMchamp, status1muon_, status1muonFromMchamp_, status1muonFromMuon_, good_genMuons, 
					genMu0_px,  genMu0_py,  genMu0_pz,  genMu0_pt,  genMu0_p,  genMu0_eta,  genMu0_phi,  genMu0_charge,
					genMu1_px,  genMu1_py,  genMu1_pz,  genMu1_pt,  genMu1_p,  genMu1_eta,  genMu1_phi,  genMu1_charge, angle,
					genMuUpper_px, genMuUpper_py, genMuUpper_pz, genMuUpper_pt, genMuUpper_p, genMuUpper_eta, genMuUpper_phi, genMuUpper_charge,
					genMuLower_px, genMuLower_py, genMuLower_pz, genMuLower_pt, genMuLower_p, genMuLower_eta, genMuLower_phi, genMuLower_charge);
    if(file_dataset_ == "ppst" || file_dataset_ == "gmst" ) staus(events, tauFromStau, status1muon, status1muonFromTau, status1muonFromMuon, status1muonFromNeutralino);

    //bx cut
    if ( (doBxCut && file_dataset_ != "Zmum" && TMath::Abs(events->bxWrtCollision)>=BxCutValue_ && TMath::Abs(events->bxWrtBunch)>=BxCutValue_) || (!doBxCut) || (file_dataset_ == "Zmum") ){
      pass_bx_cut++;
      
      StoppedParticles(events);

      //long-lived particle stopping in cavern walls? mcStoppedParticle variables are in mm 
      if( (!is_data && doCavCut && events->mcStoppedParticle_N>0 && events->mcStoppedParticleR[0]<7285. && TMath::Abs(events->mcStoppedParticleZ[0]<10800)) || (!doCavCut) || (is_data) ){
	//double r = events->mcStoppedParticleR[0]/10.0;
	//double z = events->mcStoppedParticleZ[0]/10.0;
	//double particle_eta = eta(events->mcStoppedParticleX[0],events->mcStoppedParticleY[0],
	//events->mcStoppedParticleZ[0],events->mcStoppedParticleTime[0]);
	
	//if (r < 131.0 && fabs(particle_eta) <= 2.5 && fabs(z) < 300.0){
	//if (r < 20.0 && fabs(particle_eta) <= 1.0 && fabs(z) < 20.0){
        pass_cavern_cut++;

	//does signal MC pass gen level criteria
	if(file_dataset_ == "stop") stop_counts(events, WFromTop, status1muon, status1muonFromMuon, status1muonFromW );
	if(file_dataset_ == "glui") gluino_counts(events, status1muon, status1muonFromW, status1muonFromTau, status1muonFromMuon, status1muonFromBbaryon, status1muonFromCbaryon, status1muonFromSbaryon, status1muonFromBmeson, status1muonFromCmeson, status1muonFromJPsi, status1muonFromLightMeson);
	if(file_dataset_ == "mcha") mchamp_counts(events, good_genMuons, genMu0_charge, genMu1_charge );
	if(file_dataset_ == "ppst" || file_dataset_ == "gmst" ) stau_counts(events, tauFromStau, status1muon, status1muonFromTau );

	if( (!is_data && doGenMuCut && (status1muon || (file_dataset_ == "mcha" && genMu0_charge==genMu1_charge))) || (!doGenMuCut) || (is_data)){
	  
	  if(doPrintout){
	    printout_setup(events);
	    //if(!is_data) printout_gen(events);
	  }

	  //SA muon cut
	  if ((doSACut && events->mu_StandAlone_N>0 && events->mu_RefittedStandAlone_N>0) || (!doSACut)){
	    pass_standaloneMuon_cut++;
	    
	    //SA matched to gen muon?
	    if ((!is_data && doGenMuMatchedCut && genMuonMatched(events)) || (!doGenMuMatchedCut) || (is_data)){
	      pass_genMuonMatched_cut++;
	      
	      //pass trigger
	      if ( (doTriggerCut && file_dataset_ != "Zmum" && (events->hltL2Mu20NoVertexNoBptx3BX || events->hltL2Mu30NoVertexNoBptx3BX || events->hltL2Mu20NoVertexNoBptx3BXNoHalo || events->hltL2Mu30NoVertexNoBptx3BXNoHalo || events->hltL2Mu20NoVertex2ChaNoBptx3BXNoHalo || events->hltL2Mu30NoVertex2ChaNoBptx3BXNoHalo ) ) || (!doTriggerCut) || (file_dataset_ == "Zmum")){
		pass_trigger_cut++;

		HighestPtSA_counts(events, PtCutValue_, ChaCutValue_, EtaCutValue_, RpcCutValue_, DisStCutValue_, DtHitsCutValue_, CscHitsCutValue_, DtInvBetaCutValue_, TimeInOutCutValue_, OppEtaCutValue_, OppPhiCutValue_);
		//cout<<"finished HighestPtSA_counts"<<endl;
		UpperAndLowerSA_counts(events, file_dataset, Pt0CutValue_, Pt1CutValue_, ChaCutValue_, EtaCutValue_, RpcCutValue_, DisStCutValue_, DtHitsCutValue_, DtInvBetaCutValue_, TimeInOutCutValue_);
		//cout<<"finished UpperAndLowerSA_counts"<<endl;

		id_hist->Fill(events->id,1.0);
		run_hist->Fill(events->run,1.0);
		bx_hist->Fill(events->bx,1.0);
		bxWrtCollision_hist->Fill(events->bxWrtCollision,1.0);
		bxWrtBunch_hist->Fill(events->bxWrtBunch,1.0);
			    
		//for (UInt_t j=0; j<events->mu_StandAlone_N; j++) {
		//cout<<endl<<"number of Csc segments is: "<<events->muStandAloneTrackCscSegEndcap.at(j).size()<<endl;
		//loop over Csc segments
		//for (UInt_t k=0; k<events->muStandAloneTrackCscSegEndcap.at(j).size(); k++) {
		//cout<<"  , for Csc segment number "<<k<<", endcap is: "<<events->muStandAloneTrackCscSegEndcap.at(j).at(k)<<", ring is: "<<events->muStandAloneTrackCscSegRing.at(j).at(k)<<", station is: "<<events->muStandAloneTrackCscSegStation.at(j).at(k)<<", chamber is: "<<events->muStandAloneTrackCscSegChamber.at(j).at(k)<<", number of hits is: "<<events->muStandAloneTrackCscSegNHits.at(j).at(k)<<", phi is: "<<events->muStandAloneTrackCscSegPhi.at(j).at(k)<<", z is: "<<events->muStandAloneTrackCscSegZ.at(j).at(k)<<", R is: "<<events->muStandAloneTrackCscSegR.at(j).at(k)<<", dir phi is: "<<events->muStandAloneTrackCscSegDirPhi.at(j).at(k)<<", dir theta is: "<<events->muStandAloneTrackCscSegDirTheta.at(j).at(k)<<", segment time is: "<<events->muStandAloneTrackCscSegTime.at(j).at(k)<<endl;
		//}
		//}		
		
		
		//if ( (do_other_cut && TMath::Abs(events->muStandAloneEta[0])<1.0 && TMath::Abs(events->muStandAloneEta[1])<1.0 && events->muStandAloneTofDirection[0]!=0 && events->muStandAloneTofDirection[1]!=0 && (events->muStandAloneTrackNChambersDt[0] + events->muStandAloneTrackNChambersCsc[0])>1 && (events->muStandAloneTrackNChambersDt[1] + events->muStandAloneTrackNChambersCsc[1])>1 && pass_pt_cut[0] && pass_pt_cut[1] && TMath::Abs(events->muStandAloneTofTimeAtIpInOut[0])<50. && TMath::Abs(events->muStandAloneTofTimeAtIpInOut[1])<50.) || (!do_other_cut) ){
		
		//cout<<"______________________"<<endl;
		//cout<<endl<<"For event "<<i<<", event # is: "<<events->id<<", run # is: "<<events->run<<", mu_StandAlone_N is: "<<events->mu_StandAlone_N<<", mu_RefittedStandAlone_N is: "<<events->mu_RefittedStandAlone_N<<", muStandAloneTof_N is: "<<events->muStandAloneTof_N<<", refitMuStandAloneTof_N is: "<<events->refitMuStandAloneTof_N<<endl;
		//cout<<"number of dimuon candidates is: "<<events->diMuMass.size()<<endl;
		//for (UInt_t j=0; j<events->diMuMass.size(); j++) {
		//cout<<"diMuMass for candidate "<<j<<" is: "<<events->diMuMass[j]<<endl;
		//}
		
		
		/*
		  cout<<"For standalone mu number "<<0<<", after the cuts pt is: "<<events->muStandAlonePt[0]<<", eta is: "<<events->muStandAloneEta[0]<<", phi is: "<<events->muStandAlonePhi[0]<<", track chi2/dof is: "<<events->muStandAloneTrackNormalizedChi2[0]<<", dxy is: "<<events->muStandAloneTrackDxy[0]<<", dz is: "<<events->muStandAloneTrackDz[0]<<endl;
		  cout<<"  , number of overall muon hits is: "<<events->muStandAloneTrackNHitsMuon[0]<<", number of Csc hits is: "<<events->muStandAloneTrackNHitsCsc[0]<<", number of Dt hits is: "<<events->muStandAloneTrackNHitsDt[0]<<", number of Rpc hits is: "<<events->muStandAloneTrackNHitsRpc[0]<<endl;
		  cout<<"  , number of overall muon stations is: "<<events->muStandAloneTrackNStations[0]<<", number of Csc chambers is: "<<events->muStandAloneTrackNChambersCsc[0]<<", number of Dt chambers is: "<<events->muStandAloneTrackNChambersDt[0]<<", number of Rpc Chambers is: "<<events->muStandAloneTrackNChambersRpc[0]<<endl;
		  cout<<"  , TOF direction is: "<<events->muStandAloneTofDirection[0]<<", TOF ndof is: "<<events->muStandAloneTofNDof[0]<<", TimeAtIpInOut is: "<<events->muStandAloneTofTimeAtIpInOut[0]<<endl;
		  cout<<endl<<"number of Csc segments is: "<<events->muStandAloneTrackCscSegEndcap.at(0).size()<<endl;
		  //loop over Csc segments
		  for (UInt_t k=0; k<events->muStandAloneTrackCscSegEndcap.at(0).size(); k++) {
		  cout<<"  , for Csc segment number "<<k<<", endcap is: "<<events->muStandAloneTrackCscSegEndcap.at(0).at(k)<<", ring is: "<<events->muStandAloneTrackCscSegRing.at(0).at(k)<<", station is: "<<events->muStandAloneTrackCscSegStation.at(0).at(k)<<", chamber is: "<<events->muStandAloneTrackCscSegChamber.at(0).at(k)<<", number of hits is: "<<events->muStandAloneTrackCscSegNHits.at(0).at(k)<<", phi is: "<<events->muStandAloneTrackCscSegPhi.at(0).at(k)<<", z is: "<<events->muStandAloneTrackCscSegZ.at(0).at(k)<<", R is: "<<events->muStandAloneTrackCscSegR.at(0).at(k)<<", dir phi is: "<<events->muStandAloneTrackCscSegDirPhi.at(0).at(k)<<", dir theta is: "<<events->muStandAloneTrackCscSegDirTheta.at(0).at(k)<<", segment time is: "<<events->muStandAloneTrackCscSegTime.at(0).at(k)<<endl;
		  }
		*/					    				
		
	      } //end of pass trigger
	    }//end of genMuonMatched cut
	  } //end of at least one SA
	}//end of status1muon
	//}//end of decay in tracker cut
      }//end of cavern cut
    }//end of bx_cut
  }//end of loop over entries

  //set bin labels and normalize BxPattern hists
  const int nbins = muStandAloneBxPattern_hist->GetNbinsX();
  string BxPatternLabel[] = {"BXs==0","BXs>0, constant","BXs>=0, increasing","BXs>=0, decreasing","BXs>=0, strange","BXs<0, constant","BXs<=0, increasing","BXs<=0, decreasing","BXs<=0, strange"};
  for (int x=0; x<nbins; x++) {
    muStandAloneBxPattern_hist->GetXaxis()->SetBinLabel(x+1,BxPatternLabel[x].c_str());
    Upper_muStandAloneBxPattern_hist->GetXaxis()->SetBinLabel(x+1,BxPatternLabel[x].c_str());
    Lower_muStandAloneBxPattern_hist->GetXaxis()->SetBinLabel(x+1,BxPatternLabel[x].c_str());
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
  if(doTriggerCut && file_dataset_!="Zmum")       cout<<"number of events passing trigger cut is: "<<pass_trigger_cut<<endl;
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
  if(!doCosEnrich && doDtInvBetaCut)         cout<<"number of events passing Dt inverse beta >"<<DtInvBetaCutValue_<<" cut is: "<<pass_DtInvBeta_cut<<endl;
  if(doCosEnrich && doDtInvBetaCut)          cout<<"number of events passing Dt inverse beta <"<<DtInvBetaCutValue_<<" cut is: "<<pass_DtInvBeta_cut<<endl;
  if(!doCosEnrich && doTimeInOutCut)         cout<<"number of events passing TimeInOut >"<<TimeInOutCutValue_<<" cut is: "<<pass_TimeInOut_cut<<endl;
  if(doCosEnrich && doTimeInOutCut)          cout<<"number of events passing TimeInOut <"<<TimeInOutCutValue_<<" cut is: "<<pass_TimeInOut_cut<<endl;

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
  if(!doCosEnrich && doDtInvBetaCut)         cout<<"number of events passing Dt inverse beta >"<<DtInvBetaCutValue_<<" cut for 2 muons is: "<<pass_DtInvBeta_2_cut<<endl;
  if(doCosEnrich && doDtInvBetaCut)          cout<<"number of events passing Dt inverse beta <"<<DtInvBetaCutValue_<<" cut for 2 muons is: "<<pass_DtInvBeta_2_cut<<endl;
  if(!doCosEnrich && doTimeInOutCut)         cout<<"number of events passing TimeInOut >"<<TimeInOutCutValue_<<" cut for 2 muons is: "<<pass_TimeInOut_2_cut<<endl;
  if(doCosEnrich && doTimeInOutCut)          cout<<"number of events passing TimeInOut <"<<TimeInOutCutValue_<<" cut for 2 muons is: "<<pass_TimeInOut_2_cut<<endl;

  if(!doPrintout) {
    fnew->cd();
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
    mcStoppedParticlePhi_hist->Write();
    mcStoppedParticleXY_hist->Write(); 
    mcStoppedParticleR_muStandAloneEta_hist->Write();    
    mcLL_N_hist->Write();
    mcLLStatus_hist->Write();
    mcLLPt_hist->Write(); 
    mcLLEta_hist->Write();
    mcLLPhi_hist->Write();
    mcLLCharge_hist->Write();
    mcLLMass_hist->Write();
    mcLLNDaughters_hist->Write();
    mcLLDaughterId_hist->Write();    
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
    mcMuonPt_hist->Write();
    mcMuonEta_hist->Write();
    mcMuonPhi_hist->Write();
    mcMuonCharge_hist->Write();
    mcMuonMass_hist->Write();
    mcMuonMotherId_hist->Write();
    mcMuonPt_muStandAlonePt_hist->Write();
    mcMuonPt_muRefittedStandAlonePt_hist->Write();
    mcMuonPt_muCosmicPt_hist->Write();
    mcMuonPt_muCosmicTrackPt_hist->Write();
    muStandAlonePtResolution_hist->Write();
    muRefittedStandAlonePtResolution_hist->Write();
    muCosmicPtResolution_hist->Write();
    muRefittedStandAlonePtResolution_muCosmicPtResolution_hist->Write();
    muStandAloneNChambersDt_PtResolution_hist->Write();
    muRefittedStandAloneNChambersDt_PtResolution_hist->Write();
    muCosmicNChambersDt_PtResolution_hist->Write();
    muStandAloneNChambersRpc_PtResolution_hist->Write();
    muRefittedStandAloneNChambersRpc_PtResolution_hist->Write();
    muCosmicNChambersRpc_PtResolution_hist->Write();
    muStandAloneNChambersDt_Pt_hist->Write();
    muRefittedStandAloneNChambersDt_Pt_hist->Write();
    muCosmicNChambersDt_Pt_hist->Write();
    muStandAloneNChambersRpc_Pt_hist->Write();
    muRefittedStandAloneNChambersRpc_Pt_hist->Write();
    muCosmicNChambersRpc_Pt_hist->Write();
    muStandAlonePt_muCosmicTrackPt_hist->Write();
    mcMuonEta_muStandAloneEta_hist->Write();
    mcMuonPhi_muStandAlonePhi_hist->Write();
    muRefittedStandAloneNHitsDt_Pt_hist->Write();
    //muRefittedStandAloneNChambersDt_Pt_hist->Write();
    mcStoppedParticleR_muRefittedStandAlonePt_hist->Write();
    mcStoppedParticleR_mcMuonPt_hist->Write();
    muStandAloneTrackDistanceStations_Pt_hist->Write();
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
    muPt_hist ->Write();
    muEta_hist->Write();
    muPhi_hist->Write();
    muType_hist->Write(); 
    muIso_hist->Write();
    muEta_muPhi_hist->Write();    
    diMu_N_hist->Write();
    diMuMass_hist->Write();    
    muCosmic_N_hist->Write();
    muCosmicPt_hist->Write();
    muCosmicEta_hist->Write();
    muCosmicPhi_hist->Write();
    muCosmicType_hist->Write();
    muCosmicEta_muCosmicPhi_hist->Write(); 
    muCosmicTrackInnerPt_hist->Write();   
    muStandAlone_N_other_cut_hist->Write();    
    muStandAlone_N_hist->Write();
    muStandAlonePt_hist->Write();
    muStandAloneEta_hist->Write();
    muStandAlonePhi_hist->Write();
    muStandAloneTrackNormalizedChi2_hist->Write();
    muStandAloneTrackDxy_hist->Write();
    muStandAloneTrackDz_hist->Write(); 
    muStandAloneTrackNHitsMuon_hist->Write();
    muStandAloneTrackNHitsCsc_hist->Write(); 
    muStandAloneTrackNHitsDt_hist->Write();
    muStandAloneTrackNHitsRpc_hist->Write(); 
    muStandAloneTrackNStations_hist->Write();
    muStandAloneTrackNChambersCsc_hist->Write();
    muStandAloneTrackNChambersDt_hist->Write(); 
    muStandAloneTrackNChambersRpc_hist->Write();
    muStandAloneTrackDistanceStations_hist->Write();
    muStandAloneTrackInnerPt_hist->Write();
    muStandAloneTrackDtTofNDof_hist->Write();
    muStandAloneTrackDtTofInverseBetaLS_hist->Write();
    muStandAloneTrackDtTofInverseBetaLSErr_hist->Write();
    muStandAloneTrackDtTofYIntercept_hist->Write();
    muStandAloneTrackDtTofYInterceptErr_hist->Write();
    muStandAloneTrackDtTofChi2Dof_hist->Write();
    muStandAloneBxPattern_hist->Write();
    muStandAloneNHitsRpcBxPattern0_hist->Write();    
    muStandAloneOppositeSegDR_hist->Write();    
    muStandAloneOppositeSegDEta_hist->Write();    
    muStandAloneOppositeSegDPhi_hist->Write();
    muStandAloneTrackShowerSize_station0_hist->Write();
    muStandAloneTrackShowerSize_station1_hist->Write();
    muStandAloneTrackShowerSize_station2_hist->Write();
    muStandAloneTrackShowerSize_station3_hist->Write();
    muStandAloneTrackShowerDeltaR_station0_hist->Write();
    muStandAloneTrackShowerDeltaR_station1_hist->Write();
    muStandAloneTrackShowerDeltaR_station2_hist->Write();
    muStandAloneTrackShowerDeltaR_station3_hist->Write();
    muStandAloneTrackShowerNHits_station0_hist->Write();
    muStandAloneTrackShowerNHits_station1_hist->Write();
    muStandAloneTrackShowerNHits_station2_hist->Write();
    muStandAloneTrackShowerNHits_station3_hist->Write();
    muStandAloneTrackShowerNCorrelatedHits_station0_hist->Write();
    muStandAloneTrackShowerNCorrelatedHits_station1_hist->Write();
    muStandAloneTrackShowerNCorrelatedHits_station2_hist->Write();
    muStandAloneTrackShowerNCorrelatedHits_station3_hist->Write();
    muStandAloneTrackShowerNUncorrelatedHits_station0_hist->Write();
    muStandAloneTrackShowerNUncorrelatedHits_station1_hist->Write();
    muStandAloneTrackShowerNUncorrelatedHits_station2_hist->Write();
    muStandAloneTrackShowerNUncorrelatedHits_station3_hist->Write();    
    muStandAloneUpperOnlyDEta_hist->Write();    
    muStandAloneUpperOnlyDPhi_hist->Write();    
    muStandAloneLowerOnlyDEta_hist->Write();    
    muStandAloneLowerOnlyDPhi_hist->Write();    
    muStandAloneNCscSegments_hist->Write();    
    muStandAloneEta_muStandAlonePhi_hist->Write();
    muStandAloneTrackNHitsRpc_muStandAloneTrackNormalizedChi2_hist->Write();
    muStandAloneTrackNHitsRpc_muStandAloneTrackNHitsDt_hist->Write();
    muStandAlonePt_muStandAloneTrackNChambersDt_hist->Write();
    Upper_StandAlone_N_hist->Write();
    Upper_StandAlonePt_hist->Write();
    Upper_StandAloneEta_hist->Write();
    Upper_StandAlonePhi_hist->Write();
    Upper_StandAloneTrackNormalizedChi2_hist->Write();
    Upper_StandAloneTrackDxy_hist->Write();
    Upper_StandAloneTrackDz_hist->Write();
    Upper_StandAloneTrackNHitsMuon_hist->Write();
    Upper_StandAloneTrackNHitsCsc_hist->Write();
    Upper_StandAloneTrackNHitsDt_hist->Write();
    Upper_StandAloneTrackNHitsRpc_hist->Write();
    Upper_StandAloneTrackNStations_hist->Write();
    Upper_StandAloneTrackNChambersCsc_hist->Write();
    Upper_StandAloneTrackNChambersDt_hist->Write();
    Upper_StandAloneTrackNChambersRpc_hist->Write();
    Upper_StandAloneTrackDtTofNDof_hist->Write();
    Upper_StandAloneTrackDtTofInverseBetaLS_hist->Write();
    Upper_StandAloneTrackDtTofInverseBetaLSErr_hist->Write();
    Upper_StandAloneTrackDtTofYIntercept_hist->Write();
    Upper_StandAloneTrackDtTofYInterceptErr_hist->Write();
    Upper_StandAloneTrackDtTofChi2Dof_hist->Write();
    Upper_StandAloneTrackNHitsRpc_Upper_StandAloneTrackNormalizedChi2_hist->Write();
    Upper_StandAloneTrackNHitsRpc_Upper_StandAloneTrackNHitsDt_hist->Write();
    Upper_muStandAloneBxPattern_hist->Write();
    Upper_muStandAloneNHitsRpcBxPattern0_hist->Write();
    Lower_StandAlone_N_hist->Write();
    Lower_StandAlonePt_hist->Write();
    Lower_StandAloneEta_hist->Write();
    Lower_StandAlonePhi_hist->Write();
    Lower_StandAloneTrackNormalizedChi2_hist->Write();
    Lower_StandAloneTrackDxy_hist->Write();
    Lower_StandAloneTrackDz_hist->Write(); 
    Lower_StandAloneTrackNHitsMuon_hist->Write();
    Lower_StandAloneTrackNHitsCsc_hist->Write();
    Lower_StandAloneTrackNHitsDt_hist->Write();
    Lower_StandAloneTrackNHitsRpc_hist->Write();
    Lower_StandAloneTrackNStations_hist->Write();
    Lower_StandAloneTrackNChambersCsc_hist->Write();
    Lower_StandAloneTrackNChambersDt_hist->Write(); 
    Lower_StandAloneTrackNChambersRpc_hist->Write();
    Lower_StandAloneTrackDtTofNDof_hist->Write();
    Lower_StandAloneTrackDtTofInverseBetaLS_hist->Write();
    Lower_StandAloneTrackDtTofInverseBetaLSErr_hist->Write();
    Lower_StandAloneTrackDtTofYIntercept_hist->Write();
    Lower_StandAloneTrackDtTofYInterceptErr_hist->Write();
    Lower_StandAloneTrackDtTofChi2Dof_hist->Write();
    Lower_StandAloneTrackNHitsRpc_Lower_StandAloneTrackNormalizedChi2_hist->Write();
    Lower_StandAloneTrackNHitsRpc_Lower_StandAloneTrackNHitsDt_hist->Write();
    Lower_muStandAloneBxPattern_hist->Write();
    Lower_muStandAloneNHitsRpcBxPattern0_hist->Write();
    Upper_StandAloneTofTimeAtIpInOut_hist->Write();
    Upper_StandAloneTofTimeAtIpOutIn_hist->Write();
    Lower_StandAloneTofTimeAtIpInOut_hist->Write();
    Lower_StandAloneTofTimeAtIpOutIn_hist->Write();
    mudiff_StandAloneTofTimeAtIpInOut_hist->Write();
    mudiff_StandAloneTofTimeAtIpOutIn_hist->Write();
    Upper_Lower_StandAloneTofTimeAtIpInOut_hist->Write();
    Upper_Lower_StandAloneTofTimeAtIpOutIn_hist->Write();    
    muRefittedStandAlone_N_hist->Write();
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
    muStandAloneDTTof_N_hist->Write();
    muStandAloneDTTofDirection_hist->Write();
    muStandAloneDTTofNDof_hist->Write();
    muStandAloneDTTofInverseBeta_hist->Write();
    muStandAloneDTTofInverseBetaErr_hist->Write();
    muStandAloneDTTofFreeInverseBeta_hist->Write();
    muStandAloneDTTofFreeInverseBetaErr_hist->Write();
    muStandAloneDTTofTimeAtIpInOut_hist->Write();
    muStandAloneDTTofTimeAtIpInOutErr_hist->Write();
    muStandAloneDTTofTimeAtIpOutIn_hist->Write();
    muStandAloneDTTofTimeAtIpOutInErr_hist->Write();    
    muStandAloneCSCTof_N_hist->Write();
    muStandAloneCSCTofDirection_hist->Write();
    muStandAloneCSCTofNDof_hist->Write();
    muStandAloneCSCTofInverseBeta_hist->Write();
    muStandAloneCSCTofInverseBetaErr_hist->Write();
    muStandAloneCSCTofFreeInverseBeta_hist->Write();
    muStandAloneCSCTofFreeInverseBetaErr_hist->Write();
    muStandAloneCSCTofTimeAtIpInOut_hist->Write();
    muStandAloneCSCTofTimeAtIpInOutErr_hist->Write();
    muStandAloneCSCTofTimeAtIpOutIn_hist->Write();
    muStandAloneCSCTofTimeAtIpOutInErr_hist->Write();    
    refitMuStandAloneTof_N_hist->Write();
    refitMuStandAloneTofDirection_hist->Write();
    refitMuStandAloneTofNDof_hist->Write();
    refitMuStandAloneTofInverseBeta_hist->Write();
    refitMuStandAloneTofInverseBetaErr_hist->Write();
    refitMuStandAloneTofFreeInverseBeta_hist->Write();
    refitMuStandAloneTofFreeInverseBetaErr_hist->Write();
    refitMuStandAloneTofTimeAtIpInOut_hist->Write();
    refitMuStandAloneTofTimeAtIpInOutErr_hist->Write();
    refitMuStandAloneTofTimeAtIpOutIn_hist->Write();
    refitMuStandAloneTofTimeAtIpOutInErr_hist->Write();    
    refitMuStandAloneDTTof_N_hist->Write();
    refitMuStandAloneDTTofDirection_hist->Write();
    refitMuStandAloneDTTofNDof_hist->Write();
    refitMuStandAloneDTTofInverseBeta_hist->Write();
    refitMuStandAloneDTTofInverseBetaErr_hist->Write();
    refitMuStandAloneDTTofFreeInverseBeta_hist->Write();
    refitMuStandAloneDTTofFreeInverseBetaErr_hist->Write();
    refitMuStandAloneDTTofTimeAtIpInOut_hist->Write();
    refitMuStandAloneDTTofTimeAtIpInOutErr_hist->Write();
    refitMuStandAloneDTTofTimeAtIpOutIn_hist->Write();
    refitMuStandAloneDTTofTimeAtIpOutInErr_hist->Write();
    refitMuStandAloneCSCTof_N_hist->Write();
    refitMuStandAloneCSCTofDirection_hist->Write();
    refitMuStandAloneCSCTofNDof_hist->Write();
    refitMuStandAloneCSCTofInverseBeta_hist->Write();
    refitMuStandAloneCSCTofInverseBetaErr_hist->Write();
    refitMuStandAloneCSCTofFreeInverseBeta_hist->Write();
    refitMuStandAloneCSCTofFreeInverseBetaErr_hist->Write();
    refitMuStandAloneCSCTofTimeAtIpInOut_hist->Write();
    refitMuStandAloneCSCTofTimeAtIpInOutErr_hist->Write();
    refitMuStandAloneCSCTofTimeAtIpOutIn_hist->Write();
    refitMuStandAloneCSCTofTimeAtIpOutInErr_hist->Write();
    DTSegment_N_hist->Write();

  }
  
  //return(0);
}


