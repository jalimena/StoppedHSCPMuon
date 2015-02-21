#ifndef StoppedHSCPMuonEvent_h
#define StoppedHSCPMuonEvent_h

// -*- C++ -*-
//
// Package:    StoppedHSCPMuon/Analysis
// Class:      StoppedHSCPMuonEvent
// 
/**\class StoppedHSCPMuonEvent StoppedHSCPMuonEvent.h StoppedHSCPMuon/Analysis/interface/StoppedHSCPMuonEvent.h

 Description: Defines the Stopped HSCPMuon TTree

 Implementation:

*/
//
// Original Author:  Jim Brooke
// $Id: StoppedHSCPMuonEvent.h,v 1.31 2013/10/01 17:50:06 jalimena Exp $
//
//

#include "TObject.h"
#include "TString.h"
#include <vector>
#include <functional>

#include "boost/cstdint.hpp"

namespace shscp {

  // structs are not part of persistency layer
  // just maintained for interface with other code
    
  struct MCDecay {
  MCDecay() : pdgId(0),vtxX(0.),vtxY(0.),vtxZ(0.),vtxT(0.),e(0.),px(0.),py(0.),pz(0.),pt(0.) { }
    unsigned pdgId;
    double vtxX;
    double vtxY;
    double vtxZ;
    double vtxR;
    double vtxT;
    double e;
    double px;
    double py;
    double pz;
    double pt;
  };
  
  struct TrigJet {
  TrigJet() : type(0), e(0.), et(0.), eta(0.), phi(0.) { }
    unsigned type;   // 0 - L1 jet, 1 - L1 tau, 2, HLT jet
    double e;
    double et;
    double eta;
    double phi;
  };

  struct TrigMuon {
  TrigMuon() : pt(0.), eta(0.), phi(0.) { }
    double pt;
    double eta;
    double phi;
  };

  struct Jet {
  Jet() : e(0.),et(0.),eta(0.),phi(0.),eHad(0.),eEm(0.),eMaxEcalTow(0.),eMaxHcalTow(0.),n60(0),n90(0),n90Hits(0),fHPD(0.),r1(0.),r2(0.),rp(0.),ro(0.),r1_top5(0.),r2_top5(0.),rp_top5(0.),ro_top5(0.) { }
    double e;
    double e_corr;
    double et;
    double et_corr;
    double eta;
    double phi;
    double eHad;
    double eEm;
    double eMaxEcalTow;
    double eMaxHcalTow;
    unsigned n60;
    unsigned n90;
    unsigned n90Hits;
    double fHPD;
    double r1;
    double r2;
    double rp;
    double ro;
    double r1_top5;
    double r2_top5;
    double rp_top5;
    double ro_top5;
  };
  
  struct Muon {
  Muon() : px(0.),py(0.),pz(0.),pt(0.),p(0.),eta(0.),phi(0.),hcalEta(0.),hcalPhi(0.),sumChargedHadronPt(0.),sumChargedParticlePt(0.),sumNeutralHadronEt(0.),sumPhotonEt(0.),sumNeutralHadronEtHighThreshold(0.),sumPhotonEtHighThreshold(0.),sumPUPt(0.),iso(0.) { }
    unsigned type;        // type of muon (standalone/global/cosmic/regular)
    double px;
    double py;
    double pz;
    double pt;
    double p;
    double eta;
    double phi;
    double hcalEta;     // track intersection with HCAL front-face (?)
    double hcalPhi;
    double sumChargedHadronPt;
    double sumChargedParticlePt;
    double sumNeutralHadronEt;
    double sumPhotonEt;
    double sumNeutralHadronEtHighThreshold;
    double sumPhotonEtHighThreshold;
    double sumPUPt;
    double iso;
  };

  struct DiMuon {
  DiMuon() : mass(0.) { }
    double mass;
  };

  struct HPD {
  HPD() : id(0),eta(0),phi(0),totalZeros(0),maxZeros(0),nJet(0),fc0(0.), fc1(0.), fc2(0.), fc3(0.), fc4(0.), fc5(0.), fc6(0.), fc7(0.), fc8(0.), fc9(0.),fc5_0(0.), fc5_1(0.), fc5_2(0.), fc5_3(0.), fc5_4(0.), fc5_5(0.), fc5_6(0.), fc5_7(0.), fc5_8(0.), fc5_9(0.) { }
    unsigned id;
    double eta;
    double phi;
    unsigned totalZeros;
    unsigned maxZeros;
    unsigned nJet;
    double fc0, fc1, fc2, fc3, fc4, fc5, fc6, fc7, fc8, fc9;  // ROOT screws up an array :-(
    double fc5_0, fc5_1, fc5_2, fc5_3, fc5_4, fc5_5, fc5_6, fc5_7, fc5_8, fc5_9;
  };

  struct Tower {
  Tower() : e(0.),et(0.),eta(0.),phi(0.),ieta(0),iphi(0),nJet(0),eHad(0.),etHad(0.),eEm(0.),etEm(0.) { }
    double e;
    double et;
    double eta;
    double phi;
    int ieta;
    int iphi;
    unsigned nJet;
    double eHad;
    double etHad;
    double eEm;
    double etEm;
  };
  
  struct RecHit {
  RecHit() : e(0.),time(0.), flags(0), aux(0), eta(0.),phi(0.),ieta(0),iphi(0),depth(0), RBXindex(0), RMindex(0) { }
    double e;
    double time;
    unsigned flags;
    unsigned aux;
    double eta;
    double phi;
    int ieta;
    int iphi;
    int depth;
    int RBXindex;
    int RMindex;
  };

  struct CscSegment {
  CscSegment() : endcap(0), ring(0), station(0), chamber(0), nHits(0), phi(0.), eta(0.), z(0.), r(0.), dirPhi(0.), dirTheta(0.), time(0) { }
    int endcap;
    int ring;
    int station;
    int chamber;
    int nHits;
    double phi;
    double eta;
    double z;
    double r;
    double dirPhi;
    double dirTheta;
    double time;
  };


  struct CscHit {
  CscHit() : z(0), rho(0), phi(0) {}
    double z;
    double rho;
    double phi;
    double time;
  }; 

  struct DTD1RecHitCollection {
  DTD1RecHitCollection() : timeCollection(0), etaCollection(0), phiCollection(0) {}
    std::vector<double> timeCollection;
    std::vector<double> etaCollection;
    std::vector<double> phiCollection;

  }; 

  struct DTSegment{
  DTSegment(): wheel(0),station(0),sector(0),localX(0.),localY(0.),z(0.),rho(0.),phi(0.), eta(0.){}
    int wheel;
    int station;
    int sector;
    double localX; 
    double localY;
    double z;
    double rho;
    double phi;
    double eta;
  }; // DTSegment
  
  
  struct RpcHit {
  RpcHit(): z(0), rho(0), phi(0), region(0){}
    double z;
    double rho; 
    double phi;
    int region;
  };

  
  struct Track {
  Track() : charge(0), px(0.),py(0.),pz(0.0),pt(0.),p(0.),eta(0.),phi(0.),hcalEta(0.),hcalPhi(0.), chi2(0.), ndof(0.), normalizedChi2(0.), vx(0.), vy(0.), vz(0.), dxy(0.), dz(0.), nHits(0), nLost(0), nStationsWithAnyHits(0),nCscChambersWithAnyHits(0),nDtChambersWithAnyHits(0),nRpcChambersWithAnyHits(0),innermostStationWithAnyHits(0),outermostStationWithAnyHits(0),nValidMuonHits(0),nValidCscHits(0),nValidDtHits(0),nValidRpcHits(0),nStationsWithValidHits(0),nCscChambersWithValidHits(0),nDtChambersWithValidHits(0),nRpcChambersWithValidHits(0),innermostStationWithValidHits(0),outermostStationWithValidHits(0),quality(0),  innerPx(0), innerPy(0), innerPz(0), innerOk(0), innerX(0), innerY(0), innerZ(0), genParticleIndex(0), triggerParticle20Index(0), triggerParticle20Cha2Index(0),  dtTofDirection(0), dtTofNDof(0),dtTofInverseBeta(0),dtTofInverseBetaErr(0),dtTofFreeInverseBeta(0),dtTofFreeInverseBetaErr(0),dtTofTimeAtIpInOut(0),dtTofTimeAtIpInOutErr(0),dtTofTimeAtIpOutIn(0),dtTofTimeAtIpOutInErr(0),dtTofInverseBetaLS(0),dtTofInverseBetaLSErr(0),dtTofYIntercept(0),dtTofYInterceptErr(0),dtTofChi2Dof(0),dtTofAveHitTimeErr(0), showerSize_station0(0), showerSize_station1(0), showerSize_station2(0), showerSize_station3(0), showerDeltaR_station0(0), showerDeltaR_station1(0), showerDeltaR_station2(0), showerDeltaR_station3(0), showerNHits_station0(0), showerNHits_station1(0), showerNHits_station2(0), showerNHits_station3(0), showerNCorrelatedHits_station0(0), showerNCorrelatedHits_station1(0), showerNCorrelatedHits_station2(0), showerNCorrelatedHits_station3(0), showerNUncorrelatedHits_station0(0), showerNUncorrelatedHits_station1(0), showerNUncorrelatedHits_station2(0), showerNUncorrelatedHits_station3(0), cscSegEndcap(0), cscSegRing(0), cscSegStation(0), cscSegChamber(0), cscSegNHits(0), cscSegPhi(0.), cscSegZ(0.), cscSegR(0.), cscSegDirPhi(0.), cscSegDirTheta(0.), cscSegTime(0.), rpcHitZ(0.), rpcHitRho(0.), rpcHitPhi(0.), rpcHitRegion(0), rpcHitBx(0) {}
    int charge;
    double px;
    double py;
    double pz;
    double pt;
    double p;
    double eta;
    double phi;
    double hcalEta;     // track intersection with HCAL front-face (?)
    double hcalPhi;
    double chi2;
    double ndof;
    double normalizedChi2;
    double vx;
    double vy;
    double vz;
    double dxy;
    double dz;
    int nHits;
    int nLost;
    int nStationsWithAnyHits;
    int nCscChambersWithAnyHits;
    int nDtChambersWithAnyHits;
    int nRpcChambersWithAnyHits;
    int innermostStationWithAnyHits;
    int outermostStationWithAnyHits;
    int nValidMuonHits;
    int nValidCscHits;
    int nValidDtHits;
    int nValidRpcHits;
    int nStationsWithValidHits;
    int nCscChambersWithValidHits;
    int nDtChambersWithValidHits;
    int nRpcChambersWithValidHits;
    int innermostStationWithValidHits;
    int outermostStationWithValidHits;
    int quality;
    double innerPx;
    double innerPy;
    double innerPz;
    bool innerOk;
    double innerX; 
    double innerY; 
    double innerZ;
    int genParticleIndex;
    int triggerParticle20Index;
    int triggerParticle20Cha2Index;
    int dtTofDirection;
    int dtTofNDof;
    double dtTofInverseBeta;
    double dtTofInverseBetaErr;
    double dtTofFreeInverseBeta;
    double dtTofFreeInverseBetaErr;
    double dtTofTimeAtIpInOut;
    double dtTofTimeAtIpInOutErr;
    double dtTofTimeAtIpOutIn;
    double dtTofTimeAtIpOutInErr;
    double dtTofInverseBetaLS;
    double dtTofInverseBetaLSErr;
    double dtTofYIntercept;
    double dtTofYInterceptErr;
    double dtTofChi2Dof;
    double dtTofAveHitTimeErr;
    double showerSize_station0;
    double showerSize_station1;
    double showerSize_station2;
    double showerSize_station3;
    double showerDeltaR_station0;
    double showerDeltaR_station1;
    double showerDeltaR_station2;
    double showerDeltaR_station3;
    int showerNHits_station0;
    int showerNHits_station1;
    int showerNHits_station2;
    int showerNHits_station3;
    int showerNCorrelatedHits_station0;
    int showerNCorrelatedHits_station1;
    int showerNCorrelatedHits_station2;
    int showerNCorrelatedHits_station3;
    int showerNUncorrelatedHits_station0;
    int showerNUncorrelatedHits_station1;
    int showerNUncorrelatedHits_station2;
    int showerNUncorrelatedHits_station3;
    std::vector<int> cscSegEndcap;
    std::vector<int> cscSegRing;
    std::vector<int> cscSegStation;
    std::vector<int> cscSegChamber;
    std::vector<int> cscSegNHits;
    std::vector<double> cscSegPhi;
    std::vector<double> cscSegZ;
    std::vector<double> cscSegR;
    std::vector<double> cscSegDirPhi;
    std::vector<double> cscSegDirTheta;
    std::vector<double> cscSegTime;
    std::vector<double> rpcHitZ;
    std::vector<double> rpcHitRho;
    std::vector<double> rpcHitPhi;
    std::vector<int> rpcHitRegion;
    std::vector<int> rpcHitBx;
  };
  
  // functor for ordering towers
  struct tow_gt : public std::binary_function<shscp::Tower, shscp::Tower, bool> {
    bool operator()(const shscp::Tower& x, const shscp::Tower& y) {
      return x.e > y.e;
    }
  };


  struct MuonTOFMap {
  MuonTOFMap() : direction(0),nDof(0),inverseBeta(0.),inverseBetaErr(0.),freeInverseBeta(0.),freeInverseBetaErr(0.),timeAtIpInOut(0.),timeAtIpInOutErr(0.),timeAtIpOutIn(0.),timeAtIpOutInErr(0.) {}
    int direction;
    int nDof;
    double inverseBeta;
    double inverseBetaErr;
    double freeInverseBeta;
    double freeInverseBetaErr;
    double timeAtIpInOut;
    double timeAtIpInOutErr;
    double timeAtIpOutIn;
    double timeAtIpOutInErr;
   };

}


class StoppedHSCPMuonEvent : public TObject {
 public:
  
  enum { MAX_N_JETS=20 };
  enum { MAX_N_TOWERS=100 };
  enum { MAX_N_HPDS=10 };
  //  enum { MAX_N_DIGIS=100 };

 public:

  StoppedHSCPMuonEvent();
  ~StoppedHSCPMuonEvent();

  void addMCDecay(shscp::MCDecay d);
  void addL1Jet(shscp::TrigJet j);
  void addL1Muon(shscp::TrigMuon m);
  void addHlt20Muon(shscp::TrigMuon m);
  void addHlt20Cha2Muon(shscp::TrigMuon m);
  void addJet(shscp::Jet j);
  void addStudyJet(shscp::Jet j);
  void addAK5Jet(shscp::Jet j);
  void addAK5StudyJet(shscp::Jet j);
  void addMuon(shscp::Muon m);
  void addDiMuon(shscp::DiMuon diMu);
  void addCosmicMuon(shscp::Muon m);
  void addCosmicMuonTrack(shscp::Track track);
  void addStandAloneMuon(shscp::Track track);
  void addRefittedStandAloneMuon(shscp::Track track);
  void addDisplacedStandAloneMuon(shscp::Track track);
  void addHPD(shscp::HPD h);
  void addTower(shscp::Tower t);
  void removeTowers();
  void addStudyTower(shscp::Tower t);
  void addRecHit(shscp::RecHit r);
  void addHFRecHit(shscp::RecHit r);
  void addCscSegment(shscp::CscSegment s);
  void addCscHit(shscp::CscHit h);
  void addDTSegment(shscp::DTSegment dt);
  void addRpcHit(shscp::RpcHit h);
  void addHePlus(double energy, double antienergy, double phi);
  void addTrack(shscp::Track track);
  void addMuonTOFMap(shscp::MuonTOFMap muontof);
  void addMuonTOFDTMap(shscp::MuonTOFMap muontofdt);
  void addMuonTOFCSCMap(shscp::MuonTOFMap muontofcsc);
  void addREFITTOFMap(shscp::MuonTOFMap refittof);
  void addREFITTOFDTMap(shscp::MuonTOFMap refittofdt);
  void addREFITTOFCSCMap(shscp::MuonTOFMap refittofcsc);
  void addHeMinus(double energy, double antienergy, double phi);
  void addHe(double energy, double antienergy, double phi); 
  void addDTD1PhiRecHitCollection(shscp::DTD1RecHitCollection dtD1PhiRecHitCollection);
  void addDTD1ZedRecHitCollection(shscp::DTD1RecHitCollection dtD1ZedRecHitCollection);
  
  // utils
  void Dump();
  
  // jet leading iphi fraction
  double leadingIPhiFraction() const;
  
  // 
  unsigned jetCaloTowers() const;
    
  
 public:  // data
  
  //MC
  unsigned rHadPdgId;
  double rHadVtxX;
  double rHadVtxY;
  double rHadVtxZ;
  double rHadVtxR;
  double rHadVtxT;
  double rHadE;
  double rHadPx;
  double rHadPy;
  double rHadPz;
  double rHadPt;

  // MC decay products
  unsigned mc_N;
  std::vector<UInt_t> mcPDGid;
  std::vector<Double_t> mcVtxX;
  std::vector<Double_t> mcVtxY;
  std::vector<Double_t> mcVtxZ;
  std::vector<Double_t> mcVtxR;
  std::vector<Double_t> mcVtxT;
  std::vector<Double_t> mcE;
  std::vector<Double_t> mcPx;
  std::vector<Double_t> mcPy;
  std::vector<Double_t> mcPz;
  std::vector<Double_t> mcPt;

  // MC result of hard scatter (gluino, stop, stau)
  unsigned mcGenParticle_N;
  std::vector<Int_t> mcGenParticleId;
  std::vector<Double_t> mcGenParticleMass;
  std::vector<Double_t> mcGenParticleCharge;
  std::vector<Double_t> mcGenParticlePx;
  std::vector<Double_t> mcGenParticlePy;
  std::vector<Double_t> mcGenParticlePz;
  std::vector<Double_t> mcGenParticlePt;
  std::vector<Double_t> mcGenParticleP;
  std::vector<Double_t> mcGenParticleE;
  std::vector<Double_t> mcGenParticlePhi;
  std::vector<Double_t> mcGenParticleEta;
  std::vector<Int_t> mcGenParticleStatus;
  std::vector<Int_t> mcGenParticleNMothers;
  std::vector<Int_t> mcGenParticleMotherId;
  std::vector<Int_t> mcGenParticleNDaughters;
  std::vector< std::vector<Int_t> > mcGenParticleDaughterId;
  std::vector< std::vector<Int_t> > mcGenParticleDaughterStatus;
  std::vector<Int_t> mcGenParticleGenIndex;

  // MC result of hard scatter (gluino, stop, stau)
  unsigned mcSparticle_N;
  std::vector<UInt_t> mcSparticleId;
  std::vector<Double_t> mcSparticleMass;
  std::vector<Double_t> mcSparticleCharge;
  std::vector<Double_t> mcSparticlePx;
  std::vector<Double_t> mcSparticlePy;
  std::vector<Double_t> mcSparticlePz;
  std::vector<Double_t> mcSparticlePt;
  std::vector<Double_t> mcSparticleE;
  std::vector<Double_t> mcSparticlePhi;
  std::vector<Double_t> mcSparticleEta;

  // MC initial r-hadron (for gluino & stop)
  unsigned mcRhadron_N;
  std::vector<UInt_t> mcRhadronId;
  std::vector<Double_t> mcRhadronMass;
  std::vector<Double_t> mcRhadronCharge; // Not currently filled
  std::vector<Double_t> mcRhadronPx;
  std::vector<Double_t> mcRhadronPy;
  std::vector<Double_t> mcRhadronPz;
  std::vector<Double_t> mcRhadronPt;
  std::vector<Double_t> mcRhadronE;
  std::vector<Double_t> mcRhadronPhi;
  std::vector<Double_t> mcRhadronEta;

  // MC stop
  unsigned mcStop_N;
  std::vector<Int_t> mcStopId;
  std::vector<Double_t> mcStopMass;
  std::vector<Double_t> mcStopCharge; // Not currently filled
  std::vector<Double_t> mcStopPx;
  std::vector<Double_t> mcStopPy;
  std::vector<Double_t> mcStopPz;
  std::vector<Double_t> mcStopPt;
  std::vector<Double_t> mcStopP;
  std::vector<Double_t> mcStopE;
  std::vector<Double_t> mcStopPhi;
  std::vector<Double_t> mcStopEta;
  std::vector<Int_t> mcStopStatus;
  std::vector<Int_t> mcStopNMothers;
  std::vector<Int_t> mcStopMotherId;
  std::vector<Int_t> mcStopNDaughters;
  std::vector< std::vector<Int_t> > mcStopDaughterId;
  std::vector< std::vector<Int_t> > mcStopDaughterStatus;
  std::vector<Int_t> mcStopGenIndex;

  // MC stau
  unsigned mcStau_N;
  std::vector<Int_t> mcStauId;
  std::vector<Double_t> mcStauMass;
  std::vector<Double_t> mcStauCharge; // Not currently filled
  std::vector<Double_t> mcStauPx;
  std::vector<Double_t> mcStauPy;
  std::vector<Double_t> mcStauPz;
  std::vector<Double_t> mcStauPt;
  std::vector<Double_t> mcStauP;
  std::vector<Double_t> mcStauE;
  std::vector<Double_t> mcStauPhi;
  std::vector<Double_t> mcStauEta;
  std::vector<Int_t> mcStauStatus;
  std::vector<Int_t> mcStauNMothers;
  std::vector<Int_t> mcStauMotherId;
  std::vector<Int_t> mcStauNDaughters;
  std::vector< std::vector<Int_t> > mcStauDaughterId;
  std::vector< std::vector<Int_t> > mcStauDaughterStatus;
  std::vector<Int_t> mcStauGenIndex;

  // MC gluino
  unsigned mcGluino_N;
  std::vector<Int_t> mcGluinoId;
  std::vector<Double_t> mcGluinoMass;
  std::vector<Double_t> mcGluinoCharge; // Not currently filled
  std::vector<Double_t> mcGluinoPx;
  std::vector<Double_t> mcGluinoPy;
  std::vector<Double_t> mcGluinoPz;
  std::vector<Double_t> mcGluinoPt;
  std::vector<Double_t> mcGluinoP;
  std::vector<Double_t> mcGluinoE;
  std::vector<Double_t> mcGluinoPhi;
  std::vector<Double_t> mcGluinoEta;
  std::vector<Int_t> mcGluinoStatus;
  std::vector<Int_t> mcGluinoNMothers;
  std::vector<Int_t> mcGluinoMotherId;
  std::vector<Int_t> mcGluinoNDaughters;
  std::vector< std::vector<Int_t> > mcGluinoDaughterId;
  std::vector< std::vector<Int_t> > mcGluinoDaughterStatus;
  std::vector<Int_t> mcGluinoGenIndex;

  // MC tauPrime
  unsigned mcTauPrime_N;
  std::vector<Int_t> mcTauPrimeId;
  std::vector<Double_t> mcTauPrimeMass;
  std::vector<Double_t> mcTauPrimeCharge; // Not currently filled
  std::vector<Double_t> mcTauPrimePx;
  std::vector<Double_t> mcTauPrimePy;
  std::vector<Double_t> mcTauPrimePz;
  std::vector<Double_t> mcTauPrimePt;
  std::vector<Double_t> mcTauPrimeP;
  std::vector<Double_t> mcTauPrimeE;
  std::vector<Double_t> mcTauPrimePhi;
  std::vector<Double_t> mcTauPrimeEta;
  std::vector<Int_t> mcTauPrimeStatus;
  std::vector<Int_t> mcTauPrimeNMothers;
  std::vector<Int_t> mcTauPrimeMotherId;
  std::vector<Int_t> mcTauPrimeNDaughters;
  std::vector< std::vector<Int_t> > mcTauPrimeDaughterId;
  std::vector< std::vector<Int_t> > mcTauPrimeDaughterStatus;
  std::vector<Int_t> mcTauPrimeGenIndex;

  // MC doubly charged Higgs
  unsigned mcDoublyChargedHiggs_N;
  std::vector<Int_t> mcDoublyChargedHiggsId;
  std::vector<Double_t> mcDoublyChargedHiggsMass;
  std::vector<Double_t> mcDoublyChargedHiggsCharge; // Not currently filled
  std::vector<Double_t> mcDoublyChargedHiggsPx;
  std::vector<Double_t> mcDoublyChargedHiggsPy;
  std::vector<Double_t> mcDoublyChargedHiggsPz;
  std::vector<Double_t> mcDoublyChargedHiggsPt;
  std::vector<Double_t> mcDoublyChargedHiggsP;
  std::vector<Double_t> mcDoublyChargedHiggsE;
  std::vector<Double_t> mcDoublyChargedHiggsPhi;
  std::vector<Double_t> mcDoublyChargedHiggsEta;
  std::vector<Int_t> mcDoublyChargedHiggsStatus;
  std::vector<Int_t> mcDoublyChargedHiggsNMothers;
  std::vector<Int_t> mcDoublyChargedHiggsMotherId;
  std::vector<Int_t> mcDoublyChargedHiggsNDaughters;
  std::vector< std::vector<Int_t> > mcDoublyChargedHiggsDaughterId;
  std::vector< std::vector<Int_t> > mcDoublyChargedHiggsDaughterStatus;
  std::vector<Int_t> mcDoublyChargedHiggsGenIndex;

  // MC chargino
  unsigned mcChargino_N;
  std::vector<Int_t> mcCharginoId;
  std::vector<Double_t> mcCharginoMass;
  std::vector<Double_t> mcCharginoCharge; // Not currently filled
  std::vector<Double_t> mcCharginoPx;
  std::vector<Double_t> mcCharginoPy;
  std::vector<Double_t> mcCharginoPz;
  std::vector<Double_t> mcCharginoPt;
  std::vector<Double_t> mcCharginoP;
  std::vector<Double_t> mcCharginoE;
  std::vector<Double_t> mcCharginoPhi;
  std::vector<Double_t> mcCharginoEta;
  std::vector<Int_t> mcCharginoStatus;
  std::vector<Int_t> mcCharginoNMothers;
  std::vector<Int_t> mcCharginoMotherId;
  std::vector<Int_t> mcCharginoNDaughters;
  std::vector< std::vector<Int_t> > mcCharginoDaughterId;
  std::vector< std::vector<Int_t> > mcCharginoDaughterStatus;
  std::vector<Int_t> mcCharginoGenIndex;

  // MC neutralino
  unsigned mcNeutralino_N;
  std::vector<Int_t> mcNeutralinoId;
  std::vector<Double_t> mcNeutralinoMass;
  std::vector<Double_t> mcNeutralinoCharge; // Not currently filled
  std::vector<Double_t> mcNeutralinoPx;
  std::vector<Double_t> mcNeutralinoPy;
  std::vector<Double_t> mcNeutralinoPz;
  std::vector<Double_t> mcNeutralinoPt;
  std::vector<Double_t> mcNeutralinoP;
  std::vector<Double_t> mcNeutralinoE;
  std::vector<Double_t> mcNeutralinoPhi;
  std::vector<Double_t> mcNeutralinoEta;
  std::vector<Int_t> mcNeutralinoStatus;
  std::vector<Int_t> mcNeutralinoNMothers;
  std::vector<Int_t> mcNeutralinoMotherId;
  std::vector<Int_t> mcNeutralinoNDaughters;
  std::vector< std::vector<Int_t> > mcNeutralinoDaughterId;
  std::vector< std::vector<Int_t> > mcNeutralinoDaughterStatus;
  std::vector<Int_t> mcNeutralinoGenIndex;

  // MC gravitino
  unsigned mcGravitino_N;
  std::vector<Int_t> mcGravitinoId;
  std::vector<Double_t> mcGravitinoMass;
  std::vector<Double_t> mcGravitinoCharge; // Not currently filled
  std::vector<Double_t> mcGravitinoPx;
  std::vector<Double_t> mcGravitinoPy;
  std::vector<Double_t> mcGravitinoPz;
  std::vector<Double_t> mcGravitinoPt;
  std::vector<Double_t> mcGravitinoP;
  std::vector<Double_t> mcGravitinoE;
  std::vector<Double_t> mcGravitinoPhi;
  std::vector<Double_t> mcGravitinoEta;
  std::vector<Int_t> mcGravitinoStatus;
  std::vector<Int_t> mcGravitinoNMothers;
  std::vector<Int_t> mcGravitinoMotherId;
  std::vector<Int_t> mcGravitinoNDaughters;
  std::vector< std::vector<Int_t> > mcGravitinoDaughterId;
  std::vector< std::vector<Int_t> > mcGravitinoDaughterStatus;
  std::vector<Int_t> mcGravitinoGenIndex;

  // MC neutrino
  unsigned mcNeutrino_N;
  std::vector<Int_t> mcNeutrinoId;
  std::vector<Double_t> mcNeutrinoMass;
  std::vector<Double_t> mcNeutrinoCharge; // Not currently filled
  std::vector<Double_t> mcNeutrinoPx;
  std::vector<Double_t> mcNeutrinoPy;
  std::vector<Double_t> mcNeutrinoPz;
  std::vector<Double_t> mcNeutrinoPt;
  std::vector<Double_t> mcNeutrinoP;
  std::vector<Double_t> mcNeutrinoE;
  std::vector<Double_t> mcNeutrinoPhi;
  std::vector<Double_t> mcNeutrinoEta;
  std::vector<Int_t> mcNeutrinoStatus;
  std::vector<Int_t> mcNeutrinoNMothers;
  std::vector<Int_t> mcNeutrinoMotherId;
  std::vector<Int_t> mcNeutrinoNDaughters;
  std::vector< std::vector<Int_t> > mcNeutrinoDaughterId;
  std::vector< std::vector<Int_t> > mcNeutrinoDaughterStatus;
  std::vector<Int_t> mcNeutrinoGenIndex;

  // MC top
  unsigned mcTop_N;
  std::vector<Int_t> mcTopId;
  std::vector<Double_t> mcTopMass;
  std::vector<Double_t> mcTopCharge; // Not currently filled
  std::vector<Double_t> mcTopPx;
  std::vector<Double_t> mcTopPy;
  std::vector<Double_t> mcTopPz;
  std::vector<Double_t> mcTopPt;
  std::vector<Double_t> mcTopP;
  std::vector<Double_t> mcTopE;
  std::vector<Double_t> mcTopPhi;
  std::vector<Double_t> mcTopEta;
  std::vector<Int_t> mcTopStatus;
  std::vector<Int_t> mcTopNMothers;
  std::vector<Int_t> mcTopMotherId;
  std::vector<Int_t> mcTopNDaughters;
  std::vector< std::vector<Int_t> > mcTopDaughterId;
  std::vector< std::vector<Int_t> > mcTopDaughterStatus;
  std::vector<Int_t> mcTopGenIndex;

  // MC W
  unsigned mcW_N;
  std::vector<Int_t> mcWId;
  std::vector<Double_t> mcWMass;
  std::vector<Double_t> mcWCharge; // Not currently filled
  std::vector<Double_t> mcWPx;
  std::vector<Double_t> mcWPy;
  std::vector<Double_t> mcWPz;
  std::vector<Double_t> mcWPt;
  std::vector<Double_t> mcWP;
  std::vector<Double_t> mcWE;
  std::vector<Double_t> mcWPhi;
  std::vector<Double_t> mcWEta;
  std::vector<Int_t> mcWStatus;
  std::vector<Int_t> mcWNMothers;
  std::vector<Int_t> mcWMotherId;
  std::vector<Int_t> mcWNDaughters;
  std::vector< std::vector<Int_t> > mcWDaughterId;
  std::vector< std::vector<Int_t> > mcWDaughterStatus;
  std::vector<Int_t> mcWGenIndex;

  // MC CMshower
  unsigned mcCMshower_N;
  std::vector<Int_t> mcCMshowerId;
  std::vector<Double_t> mcCMshowerMass;
  std::vector<Double_t> mcCMshowerCharge; // Not currently filled
  std::vector<Double_t> mcCMshowerPx;
  std::vector<Double_t> mcCMshowerPy;
  std::vector<Double_t> mcCMshowerPz;
  std::vector<Double_t> mcCMshowerPt;
  std::vector<Double_t> mcCMshowerP;
  std::vector<Double_t> mcCMshowerE;
  std::vector<Double_t> mcCMshowerPhi;
  std::vector<Double_t> mcCMshowerEta;
  std::vector<Int_t> mcCMshowerStatus;
  std::vector<Int_t> mcCMshowerNMothers;
  std::vector<Int_t> mcCMshowerMotherId;
  std::vector<Int_t> mcCMshowerNDaughters;
  std::vector< std::vector<Int_t> > mcCMshowerDaughterId;
  std::vector< std::vector<Int_t> > mcCMshowerDaughterStatus;
  std::vector<Int_t> mcCMshowerGenIndex;

  // MC Tau
  unsigned mcTau_N;
  std::vector<Int_t> mcTauId;
  std::vector<Double_t> mcTauMass;
  std::vector<Double_t> mcTauCharge; // Not currently filled
  std::vector<Double_t> mcTauPx;
  std::vector<Double_t> mcTauPy;
  std::vector<Double_t> mcTauPz;
  std::vector<Double_t> mcTauPt;
  std::vector<Double_t> mcTauP;
  std::vector<Double_t> mcTauE;
  std::vector<Double_t> mcTauPhi;
  std::vector<Double_t> mcTauEta;
  std::vector<Int_t> mcTauStatus;
  std::vector<Int_t> mcTauNMothers;
  std::vector<Int_t> mcTauMotherId;
  std::vector<Int_t> mcTauNDaughters;
  std::vector< std::vector<Int_t> > mcTauDaughterId;
  std::vector< std::vector<Int_t> > mcTauDaughterStatus;
  std::vector<Int_t> mcTauGenIndex;

  // MC muon
  unsigned mcMuon_N;
  std::vector<Int_t> mcMuonId;
  std::vector<Double_t> mcMuonMass;
  std::vector<Double_t> mcMuonCharge; // Not currently filled
  std::vector<Double_t> mcMuonPx;
  std::vector<Double_t> mcMuonPy;
  std::vector<Double_t> mcMuonPz;
  std::vector<Double_t> mcMuonPt;
  std::vector<Double_t> mcMuonP;
  std::vector<Double_t> mcMuonE;
  std::vector<Double_t> mcMuonPhi;
  std::vector<Double_t> mcMuonEta;
  std::vector<Double_t> mcMuonVx;
  std::vector<Double_t> mcMuonVy;
  std::vector<Double_t> mcMuonVz;
  //std::vector<Double_t> mcMuonDxy;
  //std::vector<Double_t> mcMuonDz;
  std::vector<Int_t> mcMuonStatus;
  std::vector<Int_t> mcMuonNMothers;
  std::vector<Int_t> mcMuonMotherId;
  std::vector<Int_t> mcMuonMotherOfWId;
  std::vector<Int_t> mcMuonMotherOfZId;
  std::vector<Int_t> mcMuonNDaughters;
  std::vector< std::vector<Int_t> > mcMuonDaughterId;
  std::vector< std::vector<Int_t> > mcMuonDaughterStatus;
  std::vector<Int_t> mcMuonGenIndex;

  // MC stopped points
  unsigned mcStoppedParticle_N;
  std::vector<TString> mcStoppedParticleName;
  std::vector<UInt_t> mcStoppedParticleId;    // Not currently filled
  std::vector<Double_t> mcStoppedParticleX;
  std::vector<Double_t> mcStoppedParticleY;
  std::vector<Double_t> mcStoppedParticleZ;
  std::vector<Double_t> mcStoppedParticleR;
  std::vector<Double_t> mcStoppedParticlePhi;
  std::vector<Double_t> mcStoppedParticleTime;

  // event
  ULong_t id;
  ULong_t bx;
  ULong_t orbit;
  ULong_t lb;
  ULong_t run;
  ULong_t fill;
  ULong_t fillFromL1;
  ULong64_t time;   // timestamp from EvF
  ULong64_t time2;  // calculated from run start + L1 counters for LS, orbit, BX
  ULong64_t time3;  // timestamp from LHC info in L1 data
  Long_t bxAfterCollision;
  Long_t bxBeforeCollision;
  Long_t bxWrtCollision;
  Long_t bxAfterBunch;
  Long_t bxBeforeBunch;
  Long_t bxWrtBunch;

  // lumi details (for this bx +/- 2)
  // All are set to -1 if LumiDetails collection is unavailable
  std::vector<Double_t> beam1Intensity; // in #protons
  std::vector<Double_t> beam2Intensity; // in #protons
  std::vector<Double_t> lumiByBx;       // in ub^-1 s^-1
  
  // trigger
  ULong64_t gtAlgoWord0;
  ULong64_t gtAlgoWord1;
  ULong64_t gtTechWord;
  std::vector<UInt_t> l1JetNoBptx;
  std::vector<UInt_t> l1JetNoBptxNoHalo;
  std::vector<UInt_t> l1Jet32NoBptxNoHalo;
  std::vector<UInt_t> l1SingleMu16er;
  std::vector<UInt_t> l1SingleMu6NoBptx;

  std::vector<UInt_t> l1Bptx;
  std::vector<UInt_t> l1MuBeamHalo;

  bool hltJetNoBptx;
  bool hltJetNoBptxNoHalo;
  bool hltJetNoBptx3BXNoHalo;
  bool hltJetE50NoBptx3BXNoHalo;
  bool hltL2Mu20eta2p1NoVertex;
  bool hltL2Mu10NoVertexNoBptx3BX;
  bool hltL2Mu20NoVertexNoBptx3BX;
  bool hltL2Mu30NoVertexNoBptx3BX;
  bool hltL2Mu10NoVertexNoBptx3BXNoHalo;
  bool hltL2Mu20NoVertexNoBptx3BXNoHalo;
  bool hltL2Mu30NoVertexNoBptx3BXNoHalo;
  bool hltL2Mu20NoVertex2ChaNoBptx3BXNoHalo;
  bool hltL2Mu30NoVertex2ChaNoBptx3BXNoHalo;

  // Add prescales
  Int_t algoTriggerPrescaleIndex;
  Int_t techTriggerPrescaleIndex;
  Int_t hltPrescaleIndex;

  Int_t l1JetNoBptxPrescale;
  Int_t l1JetNoBptxNoHaloPrescale;
  Int_t l1Jet32NoBptxNoHaloPrescale;
  Int_t l1SingleMu16erPrescale;
  Int_t l1SingleMu6NoBptxPrescale;

  Int_t hltJetNoBptxPrescale;
  Int_t hltJetNoBptxNoHaloPrescale;
  Int_t hltJetNoBptx3BXNoHaloPrescale;
  Int_t hltJetE50NoBptx3BXNoHaloPrescale;
  Int_t hltL2Mu20eta2p1NoVertexPrescale;
  Int_t hltL2Mu10NoVertexNoBptx3BXPrescale;
  Int_t hltL2Mu20NoVertexNoBptx3BXPrescale;
  Int_t hltL2Mu30NoVertexNoBptx3BXPrescale;
  Int_t hltL2Mu10NoVertexNoBptx3BXNoHaloPrescale;
  Int_t hltL2Mu20NoVertexNoBptx3BXNoHaloPrescale;
  Int_t hltL2Mu30NoVertexNoBptx3BXNoHaloPrescale;
  Int_t hltL2Mu20NoVertex2ChaNoBptx3BXNoHaloPrescale;
  Int_t hltL2Mu30NoVertex2ChaNoBptx3BXNoHaloPrescale;

  // trigger jets
  unsigned l1Jet_N;
  std::vector<UInt_t> l1JetType;
  std::vector<Double_t> l1JetE;
  std::vector<Double_t> l1JetEt;
  std::vector<Double_t> l1JetEta;
  std::vector<Double_t> l1JetPhi;

  unsigned l1Muon_N;
  std::vector<Double_t> l1MuonPt;
  std::vector<Double_t> l1MuonEta;
  std::vector<Double_t> l1MuonPhi;

  unsigned hlt20Muon_N;
  std::vector<Double_t> hlt20MuonPt;
  std::vector<Double_t> hlt20MuonEta;
  std::vector<Double_t> hlt20MuonPhi;

  unsigned hlt20Cha2Muon_N;
  std::vector<Double_t> hlt20Cha2MuonPt;
  std::vector<Double_t> hlt20Cha2MuonEta;
  std::vector<Double_t> hlt20Cha2MuonPhi;

  // reco jets
  unsigned jet_N;
  std::vector<Double_t> jetE;
  std::vector<Double_t> jetECorr;
  std::vector<Double_t> jetEt;
  std::vector<Double_t> jetEtCorr;
  std::vector<Double_t> jetEta;
  std::vector<Double_t> jetPhi;
  std::vector<Double_t> jetEHad;
  std::vector<Double_t> jetEEm;
  std::vector<Double_t> jetEMaxEcalTow;
  std::vector<Double_t> jetEMaxHcalTow;
  std::vector<UInt_t> jetN60;
  std::vector<UInt_t> jetN90;
  std::vector<Double_t> jetFHPD;
  std::vector<UInt_t> jetN90Hits;

  // reco jets used for studies only
  unsigned studyJet_N;
  std::vector<Double_t> studyJetE;
  std::vector<Double_t> studyJetECorr;
  std::vector<Double_t> studyJetEt;
  std::vector<Double_t> studyJetEtCorr;
  std::vector<Double_t> studyJetEta;
  std::vector<Double_t> studyJetPhi;
  std::vector<Double_t> studyJetEHad;
  std::vector<Double_t> studyJetEEm;
  std::vector<Double_t> studyJetEMaxEcalTow;
  std::vector<Double_t> studyJetEMaxHcalTow;
  std::vector<UInt_t> studyJetN60;
  std::vector<UInt_t> studyJetN90;
  std::vector<Double_t> studyJetFHPD;
  std::vector<UInt_t> studyJetN90Hits;


  // AK5 jets
  unsigned jetAK5_N;
  std::vector<Double_t> jetAK5E;
  std::vector<Double_t> jetAK5ECorr;
  std::vector<Double_t> jetAK5Et;
  std::vector<Double_t> jetAK5EtCorr;
  std::vector<Double_t> jetAK5Eta;
  std::vector<Double_t> jetAK5Phi;
  std::vector<Double_t> jetAK5EHad;
  std::vector<Double_t> jetAK5EEm;
  std::vector<Double_t> jetAK5EMaxEcalTow;
  std::vector<Double_t> jetAK5EMaxHcalTow;
  std::vector<UInt_t> jetAK5N60;
  std::vector<UInt_t> jetAK5N90;
  std::vector<Double_t> jetAK5FHPD;
  std::vector<UInt_t> jetAK5N90Hits;

 // AK5 jets used for studies only
  unsigned studyJetAK5_N;
  std::vector<Double_t> studyJetAK5E;
  std::vector<Double_t> studyJetAK5ECorr;
  std::vector<Double_t> studyJetAK5Et;
  std::vector<Double_t> studyJetAK5EtCorr;
  std::vector<Double_t> studyJetAK5Eta;
  std::vector<Double_t> studyJetAK5Phi;
  std::vector<Double_t> studyJetAK5EHad;
  std::vector<Double_t> studyJetAK5EEm;
  std::vector<Double_t> studyJetAK5EMaxEcalTow;
  std::vector<Double_t> studyJetAK5EMaxHcalTow;
  std::vector<UInt_t> studyJetAK5N60;
  std::vector<UInt_t> studyJetAK5N90;
  std::vector<Double_t> studyJetAK5FHPD;
  std::vector<UInt_t> studyJetAK5N90Hits;


  // reco muons
  unsigned mu_N;
  std::vector<UInt_t> muType;        // type of muon (standalone/global/cosmic/regular)
  std::vector<Double_t> muPx;
  std::vector<Double_t> muPy;
  std::vector<Double_t> muPz;
  std::vector<Double_t> muPt;
  std::vector<Double_t> muP;
  std::vector<Double_t> muEta;
  std::vector<Double_t> muPhi;
  std::vector<Double_t> muHcalEta;     // track intersection with HCAL front-face (?)
  std::vector<Double_t> muHcalPhi;
  std::vector<Double_t> muSumChargedHadronPt;
  std::vector<Double_t> muSumChargedParticlePt;
  std::vector<Double_t> muSumNeutralHadronEt;
  std::vector<Double_t> muSumPhotonEt;
  std::vector<Double_t> muSumNeutralHadronEtHighThreshold;
  std::vector<Double_t> muSumPhotonEtHighThreshold;
  std::vector<Double_t> muSumPUPt;
  std::vector<Double_t> muIso;

  //dimuons
  unsigned diMu_N;
  std::vector<Double_t> diMuMass;

  // reco cosmic muons
  unsigned mu_Cosmic_N;
  std::vector<UInt_t> muCosmicType;        // type of muon (standalone/global/cosmic/regular)
  std::vector<Double_t> muCosmicPx;
  std::vector<Double_t> muCosmicPy;
  std::vector<Double_t> muCosmicPz;
  std::vector<Double_t> muCosmicPt;
  std::vector<Double_t> muCosmicP;
  std::vector<Double_t> muCosmicEta;
  std::vector<Double_t> muCosmicPhi;
  std::vector<Double_t> muCosmicHcalEta;     // track intersection with HCAL front-face (?)
  std::vector<Double_t> muCosmicHcalPhi;
  std::vector<Double_t> muCosmicSumChargedHadronPt;
  std::vector<Double_t> muCosmicSumChargedParticlePt;
  std::vector<Double_t> muCosmicSumNeutralHadronEt;
  std::vector<Double_t> muCosmicSumPhotonEt;
  std::vector<Double_t> muCosmicSumNeutralHadronEtHighThreshold;
  std::vector<Double_t> muCosmicSumPhotonEtHighThreshold;
  std::vector<Double_t> muCosmicSumPUPt;
  std::vector<Double_t> muCosmicIso;

  unsigned mu_CosmicTrack_N;
  std::vector<Int_t> muCosmicTrackCharge;
  std::vector<Double_t> muCosmicTrackPx;
  std::vector<Double_t> muCosmicTrackPy;
  std::vector<Double_t> muCosmicTrackPz;
  std::vector<Double_t> muCosmicTrackPt;
  std::vector<Double_t> muCosmicTrackP;
  std::vector<Double_t> muCosmicTrackEta;
  std::vector<Double_t> muCosmicTrackPhi;
  std::vector<Double_t> muCosmicTrackHcalEta;
  std::vector<Double_t> muCosmicTrackHcalPhi;
  std::vector<Double_t> muCosmicTrackChi2;
  std::vector<Double_t> muCosmicTrackNdof;
  std::vector<Double_t> muCosmicTrackNormalizedChi2;
  std::vector<Double_t> muCosmicTrackVx;
  std::vector<Double_t> muCosmicTrackVy;
  std::vector<Double_t> muCosmicTrackVz;
  std::vector<Double_t> muCosmicTrackDxy;
  std::vector<Double_t> muCosmicTrackDz;
  std::vector<Int_t> muCosmicTrackNHits;
  std::vector<Int_t> muCosmicTrackNLost;
  std::vector<Int_t> muCosmicTrackNStationsWithAnyHits;
  std::vector<Int_t> muCosmicTrackNCscChambersWithAnyHits;
  std::vector<Int_t> muCosmicTrackNDtChambersWithAnyHits;
  std::vector<Int_t> muCosmicTrackNRpcChambersWithAnyHits;
  std::vector<Int_t> muCosmicTrackInnermostStationWithAnyHits;
  std::vector<Int_t> muCosmicTrackOutermostStationWithAnyHits;
  std::vector<Int_t> muCosmicTrackNValidMuonHits;
  std::vector<Int_t> muCosmicTrackNValidCscHits;
  std::vector<Int_t> muCosmicTrackNValidDtHits;
  std::vector<Int_t> muCosmicTrackNValidRpcHits;
  std::vector<Int_t> muCosmicTrackNStationsWithValidHits;
  std::vector<Int_t> muCosmicTrackNCscChambersWithValidHits;
  std::vector<Int_t> muCosmicTrackNDtChambersWithValidHits;
  std::vector<Int_t> muCosmicTrackNRpcChambersWithValidHits;
  std::vector<Int_t> muCosmicTrackInnermostStationWithValidHits;
  std::vector<Int_t> muCosmicTrackOutermostStationWithValidHits;
  std::vector<Int_t> muCosmicTrackQuality;
  std::vector<Double_t> muCosmicTrackInnerPx;
  std::vector<Double_t> muCosmicTrackInnerPy;
  std::vector<Double_t> muCosmicTrackInnerPz;
  std::vector<Bool_t> muCosmicTrackInnerOk;
  std::vector<Double_t> muCosmicTrackInnerX; 
  std::vector<Double_t> muCosmicTrackInnerY; 
  std::vector<Double_t> muCosmicTrackInnerZ; 
  std::vector<Int_t> muCosmicTrackGenParticleIndex;
  std::vector<Int_t> muCosmicTrackTriggerParticle20Index;
  std::vector<Int_t> muCosmicTrackTriggerParticle20Cha2Index;
  std::vector< std::vector<Double_t> > muCosmicTrackRpcHitZ;
  std::vector< std::vector<Double_t> > muCosmicTrackRpcHitRho;
  std::vector< std::vector<Double_t> > muCosmicTrackRpcHitPhi;
  std::vector< std::vector<Int_t> > muCosmicTrackRpcHitRegion;
  std::vector< std::vector<Int_t> > muCosmicTrackRpcHitBx;


  // reco standalone muon tracks
  unsigned mu_StandAlone_N;
  std::vector<Int_t> muStandAloneCharge;
  std::vector<Double_t> muStandAlonePx;
  std::vector<Double_t> muStandAlonePy;
  std::vector<Double_t> muStandAlonePz;
  std::vector<Double_t> muStandAlonePt;
  std::vector<Double_t> muStandAloneP;
  std::vector<Double_t> muStandAloneEta;
  std::vector<Double_t> muStandAlonePhi;
  std::vector<Double_t> muStandAloneHcalEta;     // track intersection with HCAL front-face (?)
  std::vector<Double_t> muStandAloneHcalPhi;
  std::vector<Double_t> muStandAloneTrackChi2;
  std::vector<Double_t> muStandAloneTrackNdof;
  std::vector<Double_t> muStandAloneTrackNormalizedChi2;
  std::vector<Double_t> muStandAloneTrackVx;
  std::vector<Double_t> muStandAloneTrackVy;
  std::vector<Double_t> muStandAloneTrackVz;
  std::vector<Double_t> muStandAloneTrackDxy;
  std::vector<Double_t> muStandAloneTrackDz;
  std::vector<Int_t> muStandAloneTrackNHits;
  std::vector<Int_t> muStandAloneTrackNLost;
  std::vector<Int_t> muStandAloneTrackNStationsWithAnyHits;
  std::vector<Int_t> muStandAloneTrackNCscChambersWithAnyHits;
  std::vector<Int_t> muStandAloneTrackNDtChambersWithAnyHits;
  std::vector<Int_t> muStandAloneTrackNRpcChambersWithAnyHits;
  std::vector<Int_t> muStandAloneTrackInnermostStationWithAnyHits;
  std::vector<Int_t> muStandAloneTrackOutermostStationWithAnyHits;
  std::vector<Int_t> muStandAloneTrackNValidMuonHits;
  std::vector<Int_t> muStandAloneTrackNValidCscHits;
  std::vector<Int_t> muStandAloneTrackNValidDtHits;
  std::vector<Int_t> muStandAloneTrackNValidRpcHits;
  std::vector<Int_t> muStandAloneTrackNStationsWithValidHits;
  std::vector<Int_t> muStandAloneTrackNCscChambersWithValidHits;
  std::vector<Int_t> muStandAloneTrackNDtChambersWithValidHits;
  std::vector<Int_t> muStandAloneTrackNRpcChambersWithValidHits;
  std::vector<Int_t> muStandAloneTrackInnermostStationWithValidHits;
  std::vector<Int_t> muStandAloneTrackOutermostStationWithValidHits;
  std::vector<Int_t> muStandAloneTrackQuality;
  std::vector<Double_t> muStandAloneTrackInnerPx;
  std::vector<Double_t> muStandAloneTrackInnerPy;
  std::vector<Double_t> muStandAloneTrackInnerPz;
  std::vector<Bool_t> muStandAloneTrackInnerOk;
  std::vector<Double_t> muStandAloneTrackInnerX; 
  std::vector<Double_t> muStandAloneTrackInnerY; 
  std::vector<Double_t> muStandAloneTrackInnerZ; 
  std::vector<Int_t> muStandAloneTrackGenParticleIndex;
  std::vector<Int_t> muStandAloneTrackTriggerParticle20Index;
  std::vector<Int_t> muStandAloneTrackTriggerParticle20Cha2Index;
  std::vector<Int_t> muStandAloneTrackDtTofDirection;
  std::vector<Int_t> muStandAloneTrackDtTofNDof; 
  std::vector<Double_t> muStandAloneTrackDtTofInverseBeta;
  std::vector<Double_t> muStandAloneTrackDtTofInverseBetaErr;
  std::vector<Double_t> muStandAloneTrackDtTofFreeInverseBeta;
  std::vector<Double_t> muStandAloneTrackDtTofFreeInverseBetaErr;
  std::vector<Double_t> muStandAloneTrackDtTofTimeAtIpInOut;
  std::vector<Double_t> muStandAloneTrackDtTofTimeAtIpInOutErr;
  std::vector<Double_t> muStandAloneTrackDtTofTimeAtIpOutIn;
  std::vector<Double_t> muStandAloneTrackDtTofTimeAtIpOutInErr;
  std::vector<Double_t> muStandAloneTrackDtTofInverseBetaLS;
  std::vector<Double_t> muStandAloneTrackDtTofInverseBetaLSErr;
  std::vector<Double_t> muStandAloneTrackDtTofYIntercept; 
  std::vector<Double_t> muStandAloneTrackDtTofYInterceptErr;
  std::vector<Double_t> muStandAloneTrackDtTofChi2Dof;
  std::vector<Double_t> muStandAloneTrackDtTofAveHitTimeErr;
  std::vector<Double_t> muStandAloneTrackShowerSize_station0;
  std::vector<Double_t> muStandAloneTrackShowerSize_station1;
  std::vector<Double_t> muStandAloneTrackShowerSize_station2;
  std::vector<Double_t> muStandAloneTrackShowerSize_station3;
  std::vector<Double_t> muStandAloneTrackShowerDeltaR_station0;
  std::vector<Double_t> muStandAloneTrackShowerDeltaR_station1;
  std::vector<Double_t> muStandAloneTrackShowerDeltaR_station2;
  std::vector<Double_t> muStandAloneTrackShowerDeltaR_station3;
  std::vector<Int_t> muStandAloneTrackShowerNHits_station0;
  std::vector<Int_t> muStandAloneTrackShowerNHits_station1;
  std::vector<Int_t> muStandAloneTrackShowerNHits_station2;
  std::vector<Int_t> muStandAloneTrackShowerNHits_station3;
  std::vector<Int_t> muStandAloneTrackShowerNCorrelatedHits_station0;
  std::vector<Int_t> muStandAloneTrackShowerNCorrelatedHits_station1;
  std::vector<Int_t> muStandAloneTrackShowerNCorrelatedHits_station2;
  std::vector<Int_t> muStandAloneTrackShowerNCorrelatedHits_station3;
  std::vector<Int_t> muStandAloneTrackShowerNUncorrelatedHits_station0;
  std::vector<Int_t> muStandAloneTrackShowerNUncorrelatedHits_station1;
  std::vector<Int_t> muStandAloneTrackShowerNUncorrelatedHits_station2;
  std::vector<Int_t> muStandAloneTrackShowerNUncorrelatedHits_station3;
  std::vector< std::vector<Int_t> > muStandAloneTrackCscSegEndcap;
  std::vector< std::vector<Int_t> > muStandAloneTrackCscSegRing;
  std::vector< std::vector<Int_t> > muStandAloneTrackCscSegStation;
  std::vector< std::vector<Int_t> > muStandAloneTrackCscSegChamber;
  std::vector< std::vector<Int_t> > muStandAloneTrackCscSegNHits;
  std::vector< std::vector<Double_t> > muStandAloneTrackCscSegPhi;
  std::vector< std::vector<Double_t> > muStandAloneTrackCscSegZ;
  std::vector< std::vector<Double_t> > muStandAloneTrackCscSegR;
  std::vector< std::vector<Double_t> > muStandAloneTrackCscSegDirPhi;
  std::vector< std::vector<Double_t> > muStandAloneTrackCscSegDirTheta;
  std::vector< std::vector<Double_t> > muStandAloneTrackCscSegTime;
  std::vector< std::vector<Double_t> > muStandAloneTrackRpcHitZ;
  std::vector< std::vector<Double_t> > muStandAloneTrackRpcHitRho;
  std::vector< std::vector<Double_t> > muStandAloneTrackRpcHitPhi;
  std::vector< std::vector<Int_t> > muStandAloneTrackRpcHitRegion;
  std::vector< std::vector<Int_t> > muStandAloneTrackRpcHitBx;

  // reco refitted standalone muon tracks
  unsigned mu_RefittedStandAlone_N;
  std::vector<Int_t> muRefittedStandAloneCharge;
  std::vector<Double_t> muRefittedStandAlonePx;
  std::vector<Double_t> muRefittedStandAlonePy;
  std::vector<Double_t> muRefittedStandAlonePz;
  std::vector<Double_t> muRefittedStandAlonePt;
  std::vector<Double_t> muRefittedStandAloneP;
  std::vector<Double_t> muRefittedStandAloneEta;
  std::vector<Double_t> muRefittedStandAlonePhi;
  std::vector<Double_t> muRefittedStandAloneHcalEta;     // track intersection with HCAL front-face (?)
  std::vector<Double_t> muRefittedStandAloneHcalPhi;
  std::vector<Double_t> muRefittedStandAloneTrackChi2;
  std::vector<Double_t> muRefittedStandAloneTrackNdof;
  std::vector<Double_t> muRefittedStandAloneTrackNormalizedChi2;
  std::vector<Double_t> muRefittedStandAloneTrackVx;
  std::vector<Double_t> muRefittedStandAloneTrackVy;
  std::vector<Double_t> muRefittedStandAloneTrackVz;
  std::vector<Double_t> muRefittedStandAloneTrackDxy;
  std::vector<Double_t> muRefittedStandAloneTrackDz;
  std::vector<Int_t> muRefittedStandAloneTrackNHits;
  std::vector<Int_t> muRefittedStandAloneTrackNLost;
  std::vector<Int_t> muRefittedStandAloneTrackNStationsWithAnyHits;
  std::vector<Int_t> muRefittedStandAloneTrackNCscChambersWithAnyHits;
  std::vector<Int_t> muRefittedStandAloneTrackNDtChambersWithAnyHits;
  std::vector<Int_t> muRefittedStandAloneTrackNRpcChambersWithAnyHits;
  std::vector<Int_t> muRefittedStandAloneTrackInnermostStationWithAnyHits;
  std::vector<Int_t> muRefittedStandAloneTrackOutermostStationWithAnyHits;
  std::vector<Int_t> muRefittedStandAloneTrackNValidMuonHits;
  std::vector<Int_t> muRefittedStandAloneTrackNValidCscHits;
  std::vector<Int_t> muRefittedStandAloneTrackNValidDtHits;
  std::vector<Int_t> muRefittedStandAloneTrackNValidRpcHits;
  std::vector<Int_t> muRefittedStandAloneTrackNStationsWithValidHits;
  std::vector<Int_t> muRefittedStandAloneTrackNCscChambersWithValidHits;
  std::vector<Int_t> muRefittedStandAloneTrackNDtChambersWithValidHits;
  std::vector<Int_t> muRefittedStandAloneTrackNRpcChambersWithValidHits;
  std::vector<Int_t> muRefittedStandAloneTrackInnermostStationWithValidHits;
  std::vector<Int_t> muRefittedStandAloneTrackOutermostStationWithValidHits;
  std::vector<Int_t> muRefittedStandAloneTrackQuality;
  std::vector<Double_t> muRefittedStandAloneTrackInnerPx;
  std::vector<Double_t> muRefittedStandAloneTrackInnerPy;
  std::vector<Double_t> muRefittedStandAloneTrackInnerPz;
  std::vector<Bool_t> muRefittedStandAloneTrackInnerOk;
  std::vector<Double_t> muRefittedStandAloneTrackInnerX; 
  std::vector<Double_t> muRefittedStandAloneTrackInnerY; 
  std::vector<Double_t> muRefittedStandAloneTrackInnerZ; 
  std::vector<Int_t> muRefittedStandAloneTrackGenParticleIndex;
  std::vector<Int_t> muRefittedStandAloneTrackTriggerParticle20Index;
  std::vector<Int_t> muRefittedStandAloneTrackTriggerParticle20Cha2Index;
  std::vector<Int_t> muRefittedStandAloneTrackDtTofDirection;
  std::vector<Int_t> muRefittedStandAloneTrackDtTofNDof; 
  std::vector<Double_t> muRefittedStandAloneTrackDtTofInverseBeta;
  std::vector<Double_t> muRefittedStandAloneTrackDtTofInverseBetaErr;
  std::vector<Double_t> muRefittedStandAloneTrackDtTofFreeInverseBeta;
  std::vector<Double_t> muRefittedStandAloneTrackDtTofFreeInverseBetaErr;
  std::vector<Double_t> muRefittedStandAloneTrackDtTofTimeAtIpInOut;
  std::vector<Double_t> muRefittedStandAloneTrackDtTofTimeAtIpInOutErr;
  std::vector<Double_t> muRefittedStandAloneTrackDtTofTimeAtIpOutIn;
  std::vector<Double_t> muRefittedStandAloneTrackDtTofTimeAtIpOutInErr;
  std::vector<Double_t> muRefittedStandAloneTrackDtTofInverseBetaLS;
  std::vector<Double_t> muRefittedStandAloneTrackDtTofInverseBetaLSErr;
  std::vector<Double_t> muRefittedStandAloneTrackDtTofYIntercept; 
  std::vector<Double_t> muRefittedStandAloneTrackDtTofYInterceptErr;
  std::vector<Double_t> muRefittedStandAloneTrackDtTofChi2Dof;
  std::vector<Double_t> muRefittedStandAloneTrackDtTofAveHitTimeErr;
  std::vector<Double_t> muRefittedStandAloneTrackShowerSize_station0;
  std::vector<Double_t> muRefittedStandAloneTrackShowerSize_station1;
  std::vector<Double_t> muRefittedStandAloneTrackShowerSize_station2;
  std::vector<Double_t> muRefittedStandAloneTrackShowerSize_station3;
  std::vector<Double_t> muRefittedStandAloneTrackShowerDeltaR_station0;
  std::vector<Double_t> muRefittedStandAloneTrackShowerDeltaR_station1;
  std::vector<Double_t> muRefittedStandAloneTrackShowerDeltaR_station2;
  std::vector<Double_t> muRefittedStandAloneTrackShowerDeltaR_station3;
  std::vector<Int_t> muRefittedStandAloneTrackShowerNHits_station0;
  std::vector<Int_t> muRefittedStandAloneTrackShowerNHits_station1;
  std::vector<Int_t> muRefittedStandAloneTrackShowerNHits_station2;
  std::vector<Int_t> muRefittedStandAloneTrackShowerNHits_station3;
  std::vector<Int_t> muRefittedStandAloneTrackShowerNCorrelatedHits_station0;
  std::vector<Int_t> muRefittedStandAloneTrackShowerNCorrelatedHits_station1;
  std::vector<Int_t> muRefittedStandAloneTrackShowerNCorrelatedHits_station2;
  std::vector<Int_t> muRefittedStandAloneTrackShowerNCorrelatedHits_station3;
  std::vector<Int_t> muRefittedStandAloneTrackShowerNUncorrelatedHits_station0;
  std::vector<Int_t> muRefittedStandAloneTrackShowerNUncorrelatedHits_station1;
  std::vector<Int_t> muRefittedStandAloneTrackShowerNUncorrelatedHits_station2;
  std::vector<Int_t> muRefittedStandAloneTrackShowerNUncorrelatedHits_station3;
  std::vector< std::vector<Double_t> > muRefittedStandAloneTrackRpcHitZ;
  std::vector< std::vector<Double_t> > muRefittedStandAloneTrackRpcHitRho;
  std::vector< std::vector<Double_t> > muRefittedStandAloneTrackRpcHitPhi;
  std::vector< std::vector<Int_t> > muRefittedStandAloneTrackRpcHitRegion;
  std::vector< std::vector<Int_t> > muRefittedStandAloneTrackRpcHitBx;

  // reco displaced standalone muon tracks
  unsigned mu_DisplacedStandAlone_N;
  std::vector<Int_t> muDisplacedStandAloneCharge;
  std::vector<Double_t> muDisplacedStandAlonePx;
  std::vector<Double_t> muDisplacedStandAlonePy;
  std::vector<Double_t> muDisplacedStandAlonePz;
  std::vector<Double_t> muDisplacedStandAlonePt;
  std::vector<Double_t> muDisplacedStandAloneP;
  std::vector<Double_t> muDisplacedStandAloneEta;
  std::vector<Double_t> muDisplacedStandAlonePhi;
  std::vector<Double_t> muDisplacedStandAloneHcalEta;     // track intersection with HCAL front-face (?)
  std::vector<Double_t> muDisplacedStandAloneHcalPhi;
  std::vector<Double_t> muDisplacedStandAloneTrackChi2;
  std::vector<Double_t> muDisplacedStandAloneTrackNdof;
  std::vector<Double_t> muDisplacedStandAloneTrackNormalizedChi2;
  std::vector<Double_t> muDisplacedStandAloneTrackVx;
  std::vector<Double_t> muDisplacedStandAloneTrackVy;
  std::vector<Double_t> muDisplacedStandAloneTrackVz;
  std::vector<Double_t> muDisplacedStandAloneTrackDxy;
  std::vector<Double_t> muDisplacedStandAloneTrackDz;
  std::vector<Int_t> muDisplacedStandAloneTrackNHits;
  std::vector<Int_t> muDisplacedStandAloneTrackNLost;
  std::vector<Int_t> muDisplacedStandAloneTrackNStationsWithAnyHits;
  std::vector<Int_t> muDisplacedStandAloneTrackNCscChambersWithAnyHits;
  std::vector<Int_t> muDisplacedStandAloneTrackNDtChambersWithAnyHits;
  std::vector<Int_t> muDisplacedStandAloneTrackNRpcChambersWithAnyHits;
  std::vector<Int_t> muDisplacedStandAloneTrackInnermostStationWithAnyHits;
  std::vector<Int_t> muDisplacedStandAloneTrackOutermostStationWithAnyHits;
  std::vector<Int_t> muDisplacedStandAloneTrackNValidMuonHits;
  std::vector<Int_t> muDisplacedStandAloneTrackNValidCscHits;
  std::vector<Int_t> muDisplacedStandAloneTrackNValidDtHits;
  std::vector<Int_t> muDisplacedStandAloneTrackNValidRpcHits;
  std::vector<Int_t> muDisplacedStandAloneTrackNStationsWithValidHits;
  std::vector<Int_t> muDisplacedStandAloneTrackNCscChambersWithValidHits;
  std::vector<Int_t> muDisplacedStandAloneTrackNDtChambersWithValidHits;
  std::vector<Int_t> muDisplacedStandAloneTrackNRpcChambersWithValidHits;
  std::vector<Int_t> muDisplacedStandAloneTrackInnermostStationWithValidHits;
  std::vector<Int_t> muDisplacedStandAloneTrackOutermostStationWithValidHits;
  std::vector<Int_t> muDisplacedStandAloneTrackQuality;
  std::vector<Double_t> muDisplacedStandAloneTrackInnerPx;
  std::vector<Double_t> muDisplacedStandAloneTrackInnerPy;
  std::vector<Double_t> muDisplacedStandAloneTrackInnerPz;
  std::vector<Bool_t> muDisplacedStandAloneTrackInnerOk;
  std::vector<Double_t> muDisplacedStandAloneTrackInnerX; 
  std::vector<Double_t> muDisplacedStandAloneTrackInnerY; 
  std::vector<Double_t> muDisplacedStandAloneTrackInnerZ; 
  std::vector<Int_t> muDisplacedStandAloneTrackGenParticleIndex;
  std::vector<Int_t> muDisplacedStandAloneTrackTriggerParticle20Index;
  std::vector<Int_t> muDisplacedStandAloneTrackTriggerParticle20Cha2Index;
  std::vector<Int_t> muDisplacedStandAloneTrackDtTofDirection;
  std::vector<Int_t> muDisplacedStandAloneTrackDtTofNDof; 
  std::vector<Double_t> muDisplacedStandAloneTrackDtTofInverseBeta;
  std::vector<Double_t> muDisplacedStandAloneTrackDtTofInverseBetaErr;
  std::vector<Double_t> muDisplacedStandAloneTrackDtTofFreeInverseBeta;
  std::vector<Double_t> muDisplacedStandAloneTrackDtTofFreeInverseBetaErr;
  std::vector<Double_t> muDisplacedStandAloneTrackDtTofTimeAtIpInOut;
  std::vector<Double_t> muDisplacedStandAloneTrackDtTofTimeAtIpInOutErr;
  std::vector<Double_t> muDisplacedStandAloneTrackDtTofTimeAtIpOutIn;
  std::vector<Double_t> muDisplacedStandAloneTrackDtTofTimeAtIpOutInErr;
  std::vector<Double_t> muDisplacedStandAloneTrackDtTofInverseBetaLS;
  std::vector<Double_t> muDisplacedStandAloneTrackDtTofInverseBetaLSErr;
  std::vector<Double_t> muDisplacedStandAloneTrackDtTofYIntercept; 
  std::vector<Double_t> muDisplacedStandAloneTrackDtTofYInterceptErr;
  std::vector<Double_t> muDisplacedStandAloneTrackDtTofChi2Dof;
  std::vector<Double_t> muDisplacedStandAloneTrackDtTofAveHitTimeErr;
  std::vector<Double_t> muDisplacedStandAloneTrackShowerSize_station0;
  std::vector<Double_t> muDisplacedStandAloneTrackShowerSize_station1;
  std::vector<Double_t> muDisplacedStandAloneTrackShowerSize_station2;
  std::vector<Double_t> muDisplacedStandAloneTrackShowerSize_station3;
  std::vector<Double_t> muDisplacedStandAloneTrackShowerDeltaR_station0;
  std::vector<Double_t> muDisplacedStandAloneTrackShowerDeltaR_station1;
  std::vector<Double_t> muDisplacedStandAloneTrackShowerDeltaR_station2;
  std::vector<Double_t> muDisplacedStandAloneTrackShowerDeltaR_station3;
  std::vector<Int_t> muDisplacedStandAloneTrackShowerNHits_station0;
  std::vector<Int_t> muDisplacedStandAloneTrackShowerNHits_station1;
  std::vector<Int_t> muDisplacedStandAloneTrackShowerNHits_station2;
  std::vector<Int_t> muDisplacedStandAloneTrackShowerNHits_station3;
  std::vector<Int_t> muDisplacedStandAloneTrackShowerNCorrelatedHits_station0;
  std::vector<Int_t> muDisplacedStandAloneTrackShowerNCorrelatedHits_station1;
  std::vector<Int_t> muDisplacedStandAloneTrackShowerNCorrelatedHits_station2;
  std::vector<Int_t> muDisplacedStandAloneTrackShowerNCorrelatedHits_station3;
  std::vector<Int_t> muDisplacedStandAloneTrackShowerNUncorrelatedHits_station0;
  std::vector<Int_t> muDisplacedStandAloneTrackShowerNUncorrelatedHits_station1;
  std::vector<Int_t> muDisplacedStandAloneTrackShowerNUncorrelatedHits_station2;
  std::vector<Int_t> muDisplacedStandAloneTrackShowerNUncorrelatedHits_station3;
  std::vector< std::vector<Double_t> > muDisplacedStandAloneTrackRpcHitZ;
  std::vector< std::vector<Double_t> > muDisplacedStandAloneTrackRpcHitRho;
  std::vector< std::vector<Double_t> > muDisplacedStandAloneTrackRpcHitPhi;
  std::vector< std::vector<Int_t> > muDisplacedStandAloneTrackRpcHitRegion;
  std::vector< std::vector<Int_t> > muDisplacedStandAloneTrackRpcHitBx;

  // vertices
  unsigned nVtx;
  unsigned vtx_N;
  std::vector<UInt_t> vtxNDOF;
  std::vector<Double_t> vtxZ;
  std::vector<Double_t> vtxRho;

  // tracks
  unsigned track_N;
  std::vector<double> trackChi2;
  std::vector<double> trackNdof;
  std::vector<int> trackNHits;
  std::vector<int> trackNLost;
  std::vector<double> trackP;
  std::vector<int> trackQuality;
  std::vector<double> trackHcalEta;
  std::vector<double> trackHcalPhi;

  // muon TOF
  unsigned muStandAloneTof_N;
  std::vector<int>    muStandAloneTofDirection;
  std::vector<double> muStandAloneTofNDof;
  std::vector<double> muStandAloneTofInverseBeta;
  std::vector<double> muStandAloneTofInverseBetaErr;
  std::vector<double> muStandAloneTofFreeInverseBeta;
  std::vector<double> muStandAloneTofFreeInverseBetaErr;
  std::vector<double> muStandAloneTofTimeAtIpInOut;
  std::vector<double> muStandAloneTofTimeAtIpInOutErr;
  std::vector<double> muStandAloneTofTimeAtIpOutIn;
  std::vector<double> muStandAloneTofTimeAtIpOutInErr;

  // muon DT TOF
  unsigned muStandAloneDTTof_N;
  std::vector<int>    muStandAloneDTTofDirection;
  std::vector<double> muStandAloneDTTofNDof;
  std::vector<double> muStandAloneDTTofInverseBeta;
  std::vector<double> muStandAloneDTTofInverseBetaErr;
  std::vector<double> muStandAloneDTTofFreeInverseBeta;
  std::vector<double> muStandAloneDTTofFreeInverseBetaErr;
  std::vector<double> muStandAloneDTTofTimeAtIpInOut;
  std::vector<double> muStandAloneDTTofTimeAtIpInOutErr;
  std::vector<double> muStandAloneDTTofTimeAtIpOutIn;
  std::vector<double> muStandAloneDTTofTimeAtIpOutInErr;
 
  // muon CSC TOF
  unsigned muStandAloneCSCTof_N;
  std::vector<int>    muStandAloneCSCTofDirection;
  std::vector<double> muStandAloneCSCTofNDof;
  std::vector<double> muStandAloneCSCTofInverseBeta;
  std::vector<double> muStandAloneCSCTofInverseBetaErr;
  std::vector<double> muStandAloneCSCTofFreeInverseBeta;
  std::vector<double> muStandAloneCSCTofFreeInverseBetaErr;
  std::vector<double> muStandAloneCSCTofTimeAtIpInOut;
  std::vector<double> muStandAloneCSCTofTimeAtIpInOutErr;
  std::vector<double> muStandAloneCSCTofTimeAtIpOutIn;
  std::vector<double> muStandAloneCSCTofTimeAtIpOutInErr;

  // refit TOF
  unsigned refitMuStandAloneTof_N;
  std::vector<int>    refitMuStandAloneTofDirection;
  std::vector<double> refitMuStandAloneTofNDof;
  std::vector<double> refitMuStandAloneTofInverseBeta;
  std::vector<double> refitMuStandAloneTofInverseBetaErr;
  std::vector<double> refitMuStandAloneTofFreeInverseBeta;
  std::vector<double> refitMuStandAloneTofFreeInverseBetaErr;
  std::vector<double> refitMuStandAloneTofTimeAtIpInOut;
  std::vector<double> refitMuStandAloneTofTimeAtIpInOutErr;
  std::vector<double> refitMuStandAloneTofTimeAtIpOutIn;
  std::vector<double> refitMuStandAloneTofTimeAtIpOutInErr;

  // refit DT TOF
  unsigned refitMuStandAloneDTTof_N;
  std::vector<int>    refitMuStandAloneDTTofDirection;
  std::vector<double> refitMuStandAloneDTTofNDof;
  std::vector<double> refitMuStandAloneDTTofInverseBeta;
  std::vector<double> refitMuStandAloneDTTofInverseBetaErr;
  std::vector<double> refitMuStandAloneDTTofFreeInverseBeta;
  std::vector<double> refitMuStandAloneDTTofFreeInverseBetaErr;
  std::vector<double> refitMuStandAloneDTTofTimeAtIpInOut;
  std::vector<double> refitMuStandAloneDTTofTimeAtIpInOutErr;
  std::vector<double> refitMuStandAloneDTTofTimeAtIpOutIn;
  std::vector<double> refitMuStandAloneDTTofTimeAtIpOutInErr;

  // refit CSC TOF
  unsigned refitMuStandAloneCSCTof_N;
  std::vector<int>    refitMuStandAloneCSCTofDirection;
  std::vector<double> refitMuStandAloneCSCTofNDof;
  std::vector<double> refitMuStandAloneCSCTofInverseBeta;
  std::vector<double> refitMuStandAloneCSCTofInverseBetaErr;
  std::vector<double> refitMuStandAloneCSCTofFreeInverseBeta;
  std::vector<double> refitMuStandAloneCSCTofFreeInverseBetaErr;
  std::vector<double> refitMuStandAloneCSCTofTimeAtIpInOut;
  std::vector<double> refitMuStandAloneCSCTofTimeAtIpInOutErr;
  std::vector<double> refitMuStandAloneCSCTofTimeAtIpOutIn;
  std::vector<double> refitMuStandAloneCSCTofTimeAtIpOutInErr;


  // Beam Halo data
  bool beamHalo_CSCTight;
  bool beamHalo_CSCLoose;
  bool beamHalo_HcalTight;
  bool beamHalo_HcalLoose;

  // global calo quantities
  unsigned nTowerSameiPhi;
  double leadingIPhiFractionValue;
  unsigned nTowerLeadingIPhi;
  double eHadLeadingIPhi;
  double hfPlusTotalE;
  double hfMinusTotalE;

  // noise summary data
  double noiseMinE2Over10TS;
  double noiseMaxE2Over10TS;
  int noiseMaxHPDHits;
  int noiseMaxRBXHits;
  int noiseMaxHPDNoOtherHits;
  int noiseMaxZeros;
  double noiseMin25GeVHitTime;
  double noiseMax25GeVHitTime;
  double noiseMinRBXEMF;
  bool noiseFilterResult;
  
  float noiseEventEMEnergy;
  float noiseEventHadEnergy;
  float noiseEventTrackEnergy;
  int noiseNumProblematicRBXs;

  // NoiseSummary pulse shape variables
  std::vector<double> topHPD5TimeSamples;
  unsigned topHPD5PeakSample;
  double   topHPD5Total;
  double   topHPD5R1;
  double   topHPD5R2;
  double   topHPD5RPeak;
  double   topHPD5ROuter;

  // HPDs identified by noise summary algos
  unsigned hpd_N;
  std::vector<UInt_t> hpdId;
  std::vector<Double_t> hpdEta;
  std::vector<Double_t> hpdPhi;
  std::vector<UInt_t> hpdTotalZeros;
  std::vector<UInt_t> hpdMaxZeros;
  std::vector<UInt_t> hpdNJet;
  std::vector<Double_t> hpdFc0, hpdFc1, hpdFc2, hpdFc3, hpdFc4, hpdFc5, hpdFc6, hpdFc7, hpdFc8, hpdFc9;
  std::vector<Double_t> hpdFc5_0, hpdFc5_1, hpdFc5_2, hpdFc5_3, hpdFc5_4, hpdFc5_5, hpdFc5_6, hpdFc5_7, hpdFc5_8, hpdFc5_9;

  // calo towers
  unsigned tower_N;
  std::vector<Double_t> towerE;
  std::vector<Double_t> towerEt;
  std::vector<Double_t> towerEta;
  std::vector<Double_t> towerPhi;
  std::vector<Int_t> towerIEta;
  std::vector<Int_t> towerIPhi;
  std::vector<UInt_t> towerNJet;
  std::vector<Double_t> towerEHad;
  std::vector<Double_t> towerEtHad;
  std::vector<Double_t> towerEEm;
  std::vector<Double_t> towerEtEm;

  // calo towers used only for study purposes
  unsigned studyTower_N;
  std::vector<Double_t> studyTowerE;
  std::vector<Double_t> studyTowerEt;
  std::vector<Double_t> studyTowerEta;
  std::vector<Double_t> studyTowerPhi;
  std::vector<Int_t> studyTowerIEta;
  std::vector<Int_t> studyTowerIPhi;
  std::vector<UInt_t> studyTowerNJet;
  std::vector<Double_t> studyTowerEHad;
  std::vector<Double_t> studyTowerEtHad;
  std::vector<Double_t> studyTowerEEm;
  std::vector<Double_t> studyTowerEtEm;

  // calo rechits
  unsigned recHit_N;
  std::vector<Double_t> recHitE;
  std::vector<Double_t> recHitTime;
  std::vector<UInt_t> recHitFlags;
  std::vector<UInt_t> recHitAux;
  std::vector<Double_t> recHitEta;
  std::vector<Double_t> recHitPhi;
  std::vector<Int_t> recHitIEta;
  std::vector<Int_t> recHitIPhi;
  std::vector<Int_t> recHitDepth;
  std::vector<Int_t> recHitRBXindex;
  std::vector<Int_t> recHitRMindex;

  // HF Rec Hits
  unsigned hfRecHit_N;
  std::vector<Double_t> hfRecHitE;
  std::vector<Double_t> hfRecHitTime;
  std::vector<Double_t> hfRecHitEta;
  std::vector<Double_t> hfRecHitPhi;
  std::vector<Int_t> hfRecHitIEta;
  std::vector<Int_t> hfRecHitIPhi;
  std::vector<Int_t> hfRecHitDepth;

  // CSC segments
  unsigned cscSeg_N;
  std::vector<Int_t> cscSegEndcap;
  std::vector<Int_t> cscSegRing;
  std::vector<Int_t> cscSegStation;
  std::vector<Int_t> cscSegChamber;
  std::vector<UInt_t> cscSegNHits;
  std::vector<Double_t> cscSegPhi;
  std::vector<Double_t> cscSegEta;
  std::vector<Double_t> cscSegZ;
  std::vector<Double_t> cscSegR;
  std::vector<Double_t> cscSegDirPhi;
  std::vector<Double_t> cscSegDirTheta;
  std::vector<Double_t> cscSegTime;

  // CSC hits
  unsigned cscHit_N;
  std::vector<Double_t> cscHitZ;
  std::vector<Double_t> cscHitRho;
  std::vector<Double_t> cscHitPhi;
  std::vector<Double_t> cscHitTime; 

  // DT segments
  unsigned DTSegment_N;
  std::vector<Int_t> DTSegWheel;
  std::vector<Int_t> DTSegStation;
  std::vector<Int_t> DTSegSector;
  std::vector<Double_t> DTSegLocalX;
  std::vector<Double_t> DTSegLocalY;
  std::vector<Double_t> DTSegZ;
  std::vector<Double_t> DTSegRho;
  std::vector<Double_t> DTSegPhi;
  std::vector<Double_t> DTSegEta;

  // DT Phi hits
  unsigned DTD1PhiRecHitCollection_N;
  std::vector< std::vector<Double_t> > DTD1PhiRecHitTimeCollection;
  std::vector< std::vector<Double_t> > DTD1PhiRecHitEtaCollection;
  std::vector< std::vector<Double_t> > DTD1PhiRecHitPhiCollection;

  // DT Zed hits
  unsigned DTD1ZedRecHitCollection_N;
  std::vector< std::vector<Double_t> > DTD1ZedRecHitTimeCollection;
  std::vector< std::vector<Double_t> > DTD1ZedRecHitEtaCollection;
  std::vector< std::vector<Double_t> > DTD1ZedRecHitPhiCollection;

  // RPC hits
  unsigned rpcHit_N;
  std::vector<Double_t> rpcHitZ;
  std::vector<Double_t> rpcHitRho;
  std::vector<Double_t> rpcHitPhi;
  std::vector<Int_t>    rpcHitRegion;

  // HE energy -- Fedor's HE variables
  Double_t hePlusEnergy;
  Double_t hePlusAntiEnergy;
  Double_t hePlusPhi;
  Double_t heMinusEnergy;
  Double_t heMinusAntiEnergy;
  Double_t heMinusPhi;
  Double_t heEnergy;
  Double_t heAntiEnergy;
  Double_t hePhi; 

  // digi pulse shape variables
  int leadingDigiIEta;
  int leadingDigiIPhi;
  std::vector<double> leadingDigiTimeSamples;
  unsigned leadingDigiPeakSample;
  double leadingDigiTotal;
  double leadingDigiR1;
  double leadingDigiR2;
  double leadingDigiRPeak;
  double leadingDigiROuter;
  std::vector<double> top5DigiTimeSamples;
  unsigned top5DigiPeakSample;
  double top5DigiTotal;
  double top5DigiR1;
  double top5DigiR2;
  double top5DigiRPeak;
  double top5DigiROuter;

  ClassDef(StoppedHSCPMuonEvent,31); // version 26: include Marco's code for IP of gen muon
  //version 27: updated to 710
  //version 28: add more RSA info
  //version 29: add Rpc info to cosmic track and any hits
  //version 30: add displacedStandAloneMuons collection
  //version 31: add doubly charged higgs
};

#endif

/*  LocalWords:  muRefittedStandAloneTrackNLost
 */
