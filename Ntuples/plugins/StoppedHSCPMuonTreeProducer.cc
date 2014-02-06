// -*- C++ -*-
//
// Package:    StoppedHSCPMuon/Analysis
// Class:      StoppedHSCPMuonTreeProducer
// 
/**\class StoppedHSCPMuonTreeProducer StoppedHSCPMuonTreeProducer.cc StoppedHSCPMuon/Analysis/src/StoppedHSCPMuonTreeProducer.cc

 Description: Produce Stopped HSCPMuon tree

 Implementation:
     
*/
//
// Original Author:  Jim Brooke
//         Created:  
// $Id: StoppedHSCPMuonTreeProducer.cc,v 1.48 2013/07/22 16:02:37 jalimena Exp $
//
//


// system include files
#include <memory>

// framework
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/ESHandle.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "DataFormats/Common/interface/ConditionsInEdm.h"
#include "DataFormats/Luminosity/interface/LumiDetails.h"

#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

// L1
#include "CondFormats/L1TObjects/interface/L1GtTriggerMenu.h"
#include "CondFormats/DataRecord/interface/L1GtTriggerMenuRcd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetupFwd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetup.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"

#include "DataFormats/L1Trigger/interface/L1JetParticleFwd.h"
#include "DataFormats/L1Trigger/interface/L1JetParticle.h"
#include "DataFormats/L1Trigger/interface/L1MuonParticleFwd.h"
#include "DataFormats/L1Trigger/interface/L1MuonParticle.h"

#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "L1Trigger/GlobalTriggerAnalyzer/interface/L1GtUtils.h"

// HLT
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/HLTReco/interface/TriggerTypeDefs.h"
#include "DataFormats/HLTReco/interface/TriggerObject.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"

// jets
#include "DataFormats/JetReco/interface/CaloJetCollection.h"

#include "JetMETCorrections/Objects/interface/JetCorrector.h"

// muons
#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "RecoMuon/TrackingTools/interface/MuonServiceProxy.h"
#include "RecoMuon/TrackingTools/interface/MuonSegmentMatcher.h"
#include "RecoMuon/MuonIdentification/interface/TimeMeasurementSequence.h"

#include "DataFormats/Candidate/interface/LeafCandidate.h"
#include "DataFormats/Candidate/interface/iterator_imp_specific.h"
#include "DataFormats/Candidate/interface/CompositeCandidate.h"
#include "DataFormats/Candidate/interface/CompositeCandidateFwd.h"

#include "Geometry/Records/interface/GlobalTrackingGeometryRecord.h"
#include "Geometry/CommonDetUnit/interface/GlobalTrackingGeometry.h"

// Vertices
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

// tracks
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/TrackReco/interface/Track.h"

#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"
#include "TrackingTools/TransientTrack/interface/TransientTrack.h"
#include "TrackingTools/Records/interface/TransientTrackRecord.h"
#include "TrackingTools/MaterialEffects/interface/PropagatorWithMaterial.h"
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"
#include "DataFormats/GeometrySurface/interface/BoundCylinder.h"
#include "DataFormats/GeometrySurface/interface/SimpleCylinderBounds.h"

// Beam Halo Summary
#include "DataFormats/METReco/interface/BeamHaloSummary.h"

// HCAL noise
#include "DataFormats/METReco/interface/HcalNoiseHPD.h"
#include "DataFormats/METReco/interface/HcalNoiseRBX.h"
#include "DataFormats/METReco/interface/HcalNoiseSummary.h"

// HCAL Channel Status
#include "CondFormats/HcalObjects/interface/HcalChannelStatus.h"
#include "CondFormats/HcalObjects/interface/HcalChannelQuality.h"
#include "CondFormats/HcalObjects/interface/HcalCondObjectContainer.h"
#include "CondFormats/DataRecord/interface/HcalChannelQualityRcd.h"

#include "CalibCalorimetry/HcalAlgos/interface/HcalDbASCIIIO.h"
#include "CalibFormats/HcalObjects/interface/HcalDbRecord.h"

// towers
#include "DataFormats/CaloTowers/interface/CaloTowerCollection.h"
#include "DataFormats/CaloTowers/interface/CaloTowerDetId.h"

// rechits
#include "Geometry/Records/interface/CaloGeometryRecord.h" 
#include "Geometry/CaloGeometry/interface/CaloGeometry.h" 
#include "DataFormats/GeometryVector/interface/GlobalPoint.h" 
#include "DataFormats/HcalRecHit/interface/HcalRecHitCollections.h"
#include "CalibCalorimetry/HcalAlgos/interface/HcalLogicalMapGenerator.h"
#include "CondFormats/HcalObjects/interface/HcalLogicalMap.h"

// CSC segments
#include "DataFormats/CSCRecHit/interface/CSCSegment.h"
#include "DataFormats/CSCRecHit/interface/CSCSegmentCollection.h"
#include "Geometry/Records/interface/MuonGeometryRecord.h"
#include "Geometry/CSCGeometry/interface/CSCGeometry.h"
#include "Geometry/CSCGeometry/interface/CSCChamber.h"
#include "Geometry/CSCGeometry/interface/CSCLayer.h"
#include "Geometry/CSCGeometry/interface/CSCLayerGeometry.h"

// DT segments
#include "DataFormats/DTRecHit/interface/DTRecHit1D.h"
#include "DataFormats/DTRecHit/interface/DTRecSegment4D.h"
#include "DataFormats/DTRecHit/interface/DTRecSegment2D.h"
#include "DataFormats/DTRecHit/interface/DTRecHitCollection.h"
#include "DataFormats/DTRecHit/interface/DTRecSegment2DCollection.h"
#include "DataFormats/DTRecHit/interface/DTRecSegment4DCollection.h"
#include "Geometry/DTGeometry/interface/DTChamber.h"
#include "Geometry/DTGeometry/interface/DTLayer.h"
#include "Geometry/DTGeometry/interface/DTGeometry.h"
#include "DataFormats/MuonDetId/interface/DTLayerId.h"
#include "DataFormats/MuonDetId/interface/DTWireId.h"

// RPC hits
#include "DataFormats/RPCRecHit/interface/RPCRecHit.h"
#include "DataFormats/RPCRecHit/interface/RPCRecHitCollection.h"
#include "Geometry/RPCGeometry/interface/RPCGeometry.h"
#include "Geometry/RPCGeometry/interface/RPCChamber.h"

// digis
#include "CalibFormats/HcalObjects/interface/HcalCoderDb.h"
#include "CalibFormats/HcalObjects/interface/HcalCalibrations.h"
#include "CalibFormats/HcalObjects/interface/HcalDbService.h"
#include "CalibFormats/HcalObjects/interface/HcalDbRecord.h"

#include "DataFormats/HcalDigi/interface/HBHEDataFrame.h"
#include "DataFormats/HcalDigi/interface/HcalDigiCollections.h"
#include "DataFormats/HcalDetId/interface/HcalDetId.h"
#include "DataFormats/HcalDetId/interface/HcalSubdetector.h"

// MC
#include "SimGeneral/HepPDTRecord/interface/ParticleDataTable.h"

// ROOT output stuff
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TH1.h"
#include "TTree.h"
#include "TF1.h"

// Helper classes
#include "StoppedHSCP/Ntuples/interface/LhcFills.h"


// TTree definition
#include "StoppedHSCPMuon/Ntuples/interface/StoppedHSCPMuonEvent.h"

// MuonTimeExtra
#include "DataFormats/MuonReco/interface/MuonTimeExtra.h"
#include "DataFormats/MuonReco/interface/MuonTimeExtraMap.h"




//
// class declaration
//

using namespace reco;

class MuonServiceProxy;

class StoppedHSCPMuonTreeProducer : public edm::EDAnalyzer {
public:
  explicit StoppedHSCPMuonTreeProducer(const edm::ParameterSet&);
  ~StoppedHSCPMuonTreeProducer();
  
  
private:
  virtual void beginJob() ;
  virtual void beginRun(const edm::Run&, const edm::EventSetup&);
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  
  void doEventInfo(const edm::Event&);

  /// write MC info
  void doMC(const edm::Event&);

  int getGenParticleMatch(const edm::Event&, reco::TrackRef);
  int getGenParticleMatch(const edm::Event&, std::vector<reco::Track>::const_iterator);
  int getTriggerObjectMatch20(const edm::Event&, reco::TrackRef);
  int getTriggerObjectMatch20(const edm::Event&, std::vector<reco::Track>::const_iterator);
  int getTriggerObjectMatch20Cha2(const edm::Event&, reco::TrackRef);
  int getTriggerObjectMatch20Cha2(const edm::Event&, std::vector<reco::Track>::const_iterator);

  /// write trigger info
  void doTrigger(const edm::Event&, const edm::EventSetup&);

  // write basic RECO objects
  void doJets(const edm::Event&, const edm::EventSetup&);
  //void doGlobalCalo(const edm::Event&);
  void doMuons(const edm::Event&, reco::CompositeCandidateCollection&);
  void doCosmicMuons(const edm::Event&);
  void doStandAloneMuons(const edm::Event&, const edm::EventSetup&);
  void doRefittedStandAloneMuons(const edm::Event&, const edm::EventSetup&);
  void doMuonDTs(const edm::Event&, const edm::EventSetup&, std::vector<DTRecHit1D>&);
  void doMuonRPCs(const edm::Event&, const edm::EventSetup&);
  void doVertices(const edm::Event&, const reco::Vertex::Point&);
  void doTracks(const edm::Event&, const edm::EventSetup&);
  void doBeamHalo(const edm::Event&);

  // write time of flight information
  void doTOF(const edm::Event&);
  void doTOFDT(const edm::Event&);
  void doTOFCSC(const edm::Event&);
  void doREFITTOF(const edm::Event&);
  void doREFITTOFDT(const edm::Event&);
  void doREFITTOFCSC(const edm::Event&);

  // write variables based on HCAL noise summary
  void doHcalNoise(const edm::Event&);
  void fillNoiseObjectTopDigiSamples(shscp::HPD& hpd, std::vector<double>& outvec);
  void fillNoiseObjectTop5DigiSamples(shscp::HPD& hpd, std::vector<double>& outvec);

  // write HCAL RecHits
  void doHcalRecHits(const edm::Event&);
  void doHFRecHits(const edm::Event&);

  // write CSC segments
  void doCscSegments(const edm::Event&, const edm::EventSetup&);
  void doCscHits(const edm::Event&, const edm::EventSetup&);
  //void doSlices (const edm::Event& iEvent, const edm::EventSetup& iSetup); 

  // write variables based on digis
  void doTimingFromDigis(const edm::Event&, const edm::EventSetup&);

  // method to calculate pulse shape variables from time samples
  void pulseShapeVariables(const std::vector<double>& samples,
			   unsigned& ipeak,
			   double& total,
			   double& r1,
			   double& r2,
			   double& rpeak,
			   double& router);



public:

  struct genParticle_pt : public std::binary_function<reco::GenParticle, reco::GenParticle, bool> {
    bool operator()(const reco::GenParticle& x, const reco::GenParticle& y) {
      return ( x.pt() > y.pt() ) ;
    }
  };

  struct l1jet_gt : public std::binary_function<l1extra::L1JetParticle, l1extra::L1JetParticle, bool> {
    bool operator()(const l1extra::L1JetParticle& x, const l1extra::L1JetParticle& y) {
      return ( x.et() > y.et() ) ;
    }
  };

  struct l1muon_pt : public std::binary_function<l1extra::L1MuonParticle, l1extra::L1MuonParticle, bool> {
    bool operator()(const l1extra::L1MuonParticle& x, const l1extra::L1MuonParticle& y) {
      return ( x.pt() > y.pt() ) ;
    }
  };

  struct jete_gt : public std::binary_function<reco::CaloJet, reco::CaloJet, bool> {
    bool operator()(const reco::CaloJet& x, const reco::CaloJet& y) {
      return ( x.energy() > y.energy() ) ;
    }
  };

  struct muon_pt : public std::binary_function<reco::Muon, reco::Muon, bool> {
    bool operator()(const reco::Muon& x, const reco::Muon& y) {
      return ( x.pt() > y.pt() ) ;
    }
  };

  struct ReverseMassSorter : public std::binary_function<reco::CompositeCandidate, reco::CompositeCandidate, bool> {
    bool operator()(const reco::CompositeCandidate& lhs, const reco::CompositeCandidate& rhs) {
      return (lhs.mass() > rhs.mass());
    }
  };

  struct track_pt : public std::binary_function<reco::Track, reco::Track, bool> {
    bool operator()(const reco::Track& x, const reco::Track& y) {
      return ( x.pt() > y.pt() ) ;
    }
  };
  
  struct calotower_gt : public std::binary_function<CaloTower, CaloTower, bool> {
    bool operator()(const CaloTower& x, const CaloTower& y) {
      return ( x.hadEnergy() > y.hadEnergy() ) ;
    }
  };

  struct rechit_gt : public std::binary_function<CaloRecHit, CaloRecHit, bool> {
    bool operator()(const CaloRecHit& x, const CaloRecHit& y) {
      return ( x.energy() > y.energy() ) ;
    }
  };
  
  struct digi_gt : public std::binary_function<HBHEDataFrame, HBHEDataFrame, bool> {
    bool operator()(const HBHEDataFrame& x, const HBHEDataFrame& y) {
      float TotalX=0;
      float TotalY=0;
      for(int i=0; i<HBHEDataFrame::MAXSAMPLES; i++)
	{
	  double samplex = x.sample(i).nominal_fC();
	  TotalX += samplex;
	  double sampley = y.sample(i).nominal_fC();
	  TotalY += sampley;
	}
      return ( TotalX > TotalY ) ;
    }
  };
  
  struct digiDetId_eq : public std::binary_function<HBHEDataFrame, DetId, bool> {
    bool operator()(const HBHEDataFrame& digi, const DetId& id) const {
      return ( digi.id() == id ) ;
    }
  };
  
private:
  
  // output file
  edm::Service<TFileService> fs_;
  
  // tree
  TTree * tree_;
  StoppedHSCPMuonEvent* event_;

  // job control
  bool isMC_;
  bool doAK5_;
  bool doCaloTowers_;
  bool doRecHits_;
  bool doHFRecHits_;
  bool doCscSegments_;
  bool doCscRecHits_;
  bool doDT_; // muon drift tubes
  bool doRpcRecHits_;

  bool doDigis_;
  bool doHltBit1_;
  bool doHltBit2_;
  bool doHltBit3_;
  bool doHltBit4_;
  bool doHltBit5_;
  bool doHltBit6_;
  bool doHltBit7_;
  bool doHltBit8_;
  bool doHltBit9_;
  bool doHltBit10_;
  bool doHltBit11_;
  bool doHltBit12_;
  bool doHltBit13_;
  bool writeHistos_;
  


  // EDM input tags
  edm::InputTag condInEdmTag_;
  std::string l1JetsTag_;
  std::string l1MuonsTag_;
  edm::InputTag l1BitsTag_;
  std::string l1JetNoBptxName_;
  std::string l1JetNoBptxNoHaloName_;
  std::string l1Jet32NoBptxNoHaloName_;
  std::string l1SingleMu16erName_;
  std::string l1SingleMu6NoBptxName_;
  std::string l1BptxName_;
  std::string l1MuBeamHaloName_;
  edm::InputTag hltResultsTag_;
  edm::InputTag hltEventTag_;
  std::string hltPathJetNoBptx_;
  std::string hltPathJetNoBptxNoHalo_;
  std::string hltPathJetNoBptx3BXNoHalo_;
  std::string hltPathJetE50NoBptx3BXNoHalo_;
  std::string hltPathL2Mu20eta2p1NoVertex_;
  std::string hltPathL2Mu10NoVertexNoBptx3BX_;
  std::string hltPathL2Mu20NoVertexNoBptx3BX_;
  std::string hltPathL2Mu30NoVertexNoBptx3BX_;
  std::string hltPathL2Mu10NoVertexNoBptx3BXNoHalo_;
  std::string hltPathL2Mu20NoVertexNoBptx3BXNoHalo_;
  std::string hltPathL2Mu30NoVertexNoBptx3BXNoHalo_;
  std::string hltPathL2Mu20NoVertex2ChaNoBptx3BXNoHalo_;
  std::string hltPathL2Mu30NoVertex2ChaNoBptx3BXNoHalo_;
  edm::InputTag hltFilterTag_20_;
  edm::InputTag hltFilterTag_20Cha2_;
  edm::InputTag mcTag_;
  std::string mcProducer_;
  edm::InputTag hepProducer_;
  edm::InputTag genParticlesTag_;
  std::string jetCorrectorServiceName_;
  edm::InputTag jetTag_;
  edm::InputTag jetAK5Tag_;
  edm::InputTag muonTag_;
  edm::InputTag cosmicMuonTag_;
  edm::InputTag standAloneMuonTag_;
  edm::InputTag refittedStandAloneMuonTag_;
  edm::InputTag verticesTag_;
  edm::InputTag tracksTag_;
  //edm::InputTag caloTowerTag_;
  edm::InputTag caloRecHitTag_;
  edm::InputTag hcalNoiseTag_;
  edm::InputTag hcalNoiseFilterResultTag_;
  edm::InputTag rbxTag_;
  edm::InputTag hpdTag_;
  edm::InputTag hcalRecHitTag_;
  edm::InputTag hfRecHitTag_;
  edm::InputTag hcalDigiTag_;
  edm::InputTag cscSegmentsTag_;
  edm::InputTag cscRecHitsTag_;
  edm::InputTag DTRecHitsTag_;
  edm::InputTag DT4DSegmentsTag_;
  edm::InputTag timeTag_;
  edm::InputTag rpcRecHitsTag_;

  // HLT config helper
  HLTConfigProvider hltConfig_;
  unsigned hltPathIndexJetNoBptx_;
  unsigned hltPathIndexJetNoBptxNoHalo_;
  unsigned hltPathIndexJetNoBptx3BXNoHalo_;
  unsigned hltPathIndexJetE50NoBptx3BXNoHalo_;
  unsigned hltPathIndexL2Mu20eta2p1NoVertex_;
  unsigned hltPathIndexL2Mu10NoVertexNoBptx3BX_;
  unsigned hltPathIndexL2Mu20NoVertexNoBptx3BX_;
  unsigned hltPathIndexL2Mu30NoVertexNoBptx3BX_;
  unsigned hltPathIndexL2Mu10NoVertexNoBptx3BXNoHalo_;
  unsigned hltPathIndexL2Mu20NoVertexNoBptx3BXNoHalo_;
  unsigned hltPathIndexL2Mu30NoVertexNoBptx3BXNoHalo_;
  unsigned hltPathIndexL2Mu20NoVertex2ChaNoBptx3BXNoHalo_;
  unsigned hltPathIndexL2Mu30NoVertex2ChaNoBptx3BXNoHalo_;

  // geometry
  const CaloGeometry* caloGeom_;

  // HepPDT table
  edm::ESHandle<HepPDT::ParticleDataTable> fPDGTable;

  // cuts
  double recoGenDeltaR_;
  double recoTriggerDeltaR_;
  double towerMinEnergy_;
  double towerMaxEta_;
  double jetMinEnergy_;
  double jetMaxEta_;
  double digiMinFc_;
  double rechitMinEnergy_;	

  // Muon TOF
  int GlobalMinNDOF_;
  double GlobalMinNDOFDT_;
  double GlobalMinNDOFCSC_;
  double GlobalMaxTOFErr_;
  double GlobalMinTOF_;

  // extra "study" jet tower info
  // (These objects are saved for study purposes, but are not used in the analysis)
  double studyJetMinEta_;
  double studyJetMaxEta_;
  double studyTowerMinEta_;
  double studyTowerMaxEta_;

  // Hcal Logical map (ieta-iphi->hardware) object
  HcalLogicalMap* logicalMap_;  
  
  // bad channel status to mask;
  HcalChannelQuality* chanquality_;
  int badchannelstatus_;
  std::set<HcalDetId> badChannels_;

  // boolean for making reduced ntuples
  bool makeReducedNtuples_;

  // LHC Fill structure (temporary until this is available through CMSSW)
  LhcFills fills_;
  unsigned currentFill_;
  unsigned currentFillL1_;
  std::vector<unsigned long> currentColls_;
  std::vector<unsigned long> currentBunches_;

  // debug stuff
  bool l1JetsMissing_;
  bool l1MuonsMissing_;
  bool hltMuonsMissing_;
  bool hltMissing_;
  bool mcMissing_;
  bool jetsMissing_;
  bool muonsMissing_;
  bool towersMissing_;
  bool rechitsMissing_;
  bool noiseSumMissing_;
  bool rbxsMissing_;
  bool hpdsMissing_;
  bool digisMissing_;
  bool verticesMissing_;
  bool tracksMissing_;
  bool cscSegsMissing_;

  std::vector<CaloTowerPtr> jetTowers_;
  std::vector<unsigned> towerJets_;

  std::vector<HcalDetId> hcalDetIds_;
  std::vector<unsigned> hcalDetJets_;

  std::vector<HBHERecHit> recHits_;

  const TransientTrackBuilder    *theTTBuilder_;
  edm::ESHandle<MagneticField>   theMF_;
  TrajectoryStateOnSurface       stateAtHCAL_; 
  mutable PropagatorWithMaterial *forwardPropagator_ ;
  PropagationDirection           dir_;
  BoundCylinder                  *theHCALbarrel_;

  MuonServiceProxy* muonService;
  MuonSegmentMatcher* segmentMatcher;

};




StoppedHSCPMuonTreeProducer::StoppedHSCPMuonTreeProducer(const edm::ParameterSet& iConfig):
  tree_(0),
  event_(0),
  isMC_(iConfig.getUntrackedParameter<bool>("isMC",false)),
  doAK5_(iConfig.getUntrackedParameter<bool>("doAK5",false)),
  doCaloTowers_(iConfig.getUntrackedParameter<bool>("doCaloTowers",false)),
  doRecHits_(iConfig.getUntrackedParameter<bool>("doRecHits",false)),
  doHFRecHits_(iConfig.getUntrackedParameter<bool>("doHFRecHits",false)),
  doCscSegments_(iConfig.getUntrackedParameter<bool>("doCsc",false)),
  doCscRecHits_(iConfig.getUntrackedParameter<bool>("doCscRecHits",false)),
  doDT_(iConfig.getUntrackedParameter<bool>("doDT",false)),
  doRpcRecHits_(iConfig.getUntrackedParameter<bool>("doRpcRecHits",false)),
  doDigis_(iConfig.getUntrackedParameter<bool>("doDigis",false)),
  doHltBit1_(true),
  doHltBit2_(true),
  doHltBit3_(true),
  doHltBit4_(true),
  writeHistos_(iConfig.getUntrackedParameter<bool>("writeHistos",false)),
  condInEdmTag_(iConfig.getUntrackedParameter<edm::InputTag>("conditionsInEdm",std::string("CondInEdmInputTag"))),
  l1JetsTag_(iConfig.getUntrackedParameter<std::string>("l1JetsTag",std::string("l1extraParticles"))),
  l1MuonsTag_(iConfig.getUntrackedParameter<std::string>("l1MuonsTag",std::string("l1extraParticles"))),
  l1BitsTag_(iConfig.getUntrackedParameter<edm::InputTag>("l1BitsTag",edm::InputTag("gtDigis"))),
  l1JetNoBptxName_(iConfig.getUntrackedParameter<std::string>("l1JetNoBptxName",std::string("L1_SingleJet20_NotBptxOR"))),  
  l1JetNoBptxNoHaloName_(iConfig.getUntrackedParameter<std::string>("l1JetNoBptxNoHaloName",std::string("L1_SingleJet20_NotBptxOR_NotMuBeamHalo"))),
  l1Jet32NoBptxNoHaloName_(iConfig.getUntrackedParameter<std::string>("l1Jet32NoBptxNoHaloName",std::string("L1_SingleJet32_NotBptxOR_NotMuBeamHalo"))),
  l1SingleMu16erName_(iConfig.getUntrackedParameter<std::string>("l1SingleMu16erName",std::string("L1_SingleMu16er"))),
  l1SingleMu6NoBptxName_(iConfig.getUntrackedParameter<std::string>("l1SingleMu6NoBptxName",std::string("L1_SingleMu6_NotBptxOR"))),
  
  //  l1BptxPlusName_(iConfig.getUntrackedParameter<std::string>("l1BptxPlusName",std::string(""))),  
  //  l1BptxMinusName_(iConfig.getUntrackedParameter<std::string>("l1BptxMinusName",std::string(""))),  
  l1BptxName_(iConfig.getUntrackedParameter<std::string>("l1BptxName",std::string("L1Tech_BPTX_plus_AND_minus"))),  
  l1MuBeamHaloName_(iConfig.getUntrackedParameter<std::string>("l1MuBeamHaloName",std::string("L1_SingleMuBeamHalo"))),  
  hltResultsTag_(iConfig.getUntrackedParameter<edm::InputTag>("hltResultsTag",edm::InputTag("TriggerResults","","HLT"))),
  hltEventTag_(iConfig.getUntrackedParameter<edm::InputTag>("hltEventTag",edm::InputTag("hltTriggerSummaryAOD","","HLT"))),
  hltPathJetNoBptx_(iConfig.getUntrackedParameter<std::string>("hltPathJetNoBptx",std::string("HLT_JetE30_NoBPTX_v1"))),
  hltPathJetNoBptxNoHalo_(iConfig.getUntrackedParameter<std::string>("hltPathJetNoBptxNoHalo",std::string("HLT_JetE30_NoBPTX_NoHalo_v1"))),
  hltPathJetNoBptx3BXNoHalo_(iConfig.getUntrackedParameter<std::string>("hltPathJetNoBptx3BXNoHalo",std::string("HLT_JetE30_NoBPTX3BX_NoHalo_v1"))),
  hltPathJetE50NoBptx3BXNoHalo_(iConfig.getUntrackedParameter<std::string>("hltPathJetE50NoBptx3BXNoHalo",std::string("HLT_JetE50_NoBPTX3BX_NoHalo_v1"))),
  hltPathL2Mu20eta2p1NoVertex_(iConfig.getUntrackedParameter<std::string>("hltPathL2Mu20eta2p1NoVertex",std::string("HLT_L2Mu20_eta2p1_NoVertex_v"))),
  hltPathL2Mu10NoVertexNoBptx3BX_(iConfig.getUntrackedParameter<std::string>("hltPathL2Mu10NoVertexNoBptx3BX",std::string("HLT_L2Mu10_NoVertex_NoBPTX3BX_v"))),
  hltPathL2Mu20NoVertexNoBptx3BX_(iConfig.getUntrackedParameter<std::string>("hltPathL2Mu20NoVertexNoBptx3BX",std::string("HLT_L2Mu20_NoVertex_NoBPTX3BX_v"))),
  hltPathL2Mu30NoVertexNoBptx3BX_(iConfig.getUntrackedParameter<std::string>("hltPathL2Mu30NoVertexNoBptx3BX",std::string("HLT_L2Mu30_NoVertex_NoBPTX3BX_v"))),
  hltPathL2Mu10NoVertexNoBptx3BXNoHalo_(iConfig.getUntrackedParameter<std::string>("hltPathL2Mu10NoVertexNoBptx3BXNoHalo",std::string("HLT_L2Mu10_NoVertex_NoBPTX3BX_NoHalo_v"))),
  hltPathL2Mu20NoVertexNoBptx3BXNoHalo_(iConfig.getUntrackedParameter<std::string>("hltPathL2Mu20NoVertexNoBptx3BXNoHalo",std::string("HLT_L2Mu20_NoVertex_NoBPTX3BX_NoHalo_v"))),
  hltPathL2Mu30NoVertexNoBptx3BXNoHalo_(iConfig.getUntrackedParameter<std::string>("hltPathL2Mu30NoVertexNoBptx3BXNoHalo",std::string("HLT_L2Mu30_NoVertex_NoBPTX3BX_NoHalo_v"))),
  hltPathL2Mu20NoVertex2ChaNoBptx3BXNoHalo_(iConfig.getUntrackedParameter<std::string>("hltPathL2Mu20NoVertex2ChaNoBptx3BXNoHalo",std::string("HLT_L2Mu20_NoVertex_2Cha_NoBPTX3BX_NoHalo_v"))),
  hltPathL2Mu30NoVertex2ChaNoBptx3BXNoHalo_(iConfig.getUntrackedParameter<std::string>("hltPathL2Mu30NoVertex2ChaNoBptx3BXNoHalo",std::string("HLT_L2Mu30_NoVertex_2Cha_NoBPTX3BX_NoHalo_v"))),
  hltFilterTag_20_(iConfig.getUntrackedParameter<edm::InputTag>("hltFilterTag_20",edm::InputTag("hltL2fL1sMu6NoBPTXL1f0L2Filtered20","","HLT"))),
  hltFilterTag_20Cha2_(iConfig.getUntrackedParameter<edm::InputTag>("hltFilterTag_20Cha2",edm::InputTag("hltL2fL1sMu6NoBPTXL1f0L2Filtered20Cha2","","HLT"))),
  mcTag_(iConfig.getUntrackedParameter<edm::InputTag>("mcTag",edm::InputTag("generator"))),
  mcProducer_ (iConfig.getUntrackedParameter<std::string>("producer", "g4SimHits")),
  hepProducer_ (iConfig.getUntrackedParameter<edm::InputTag>("hepMCProducerTag", edm::InputTag("generator", "", "SIM"))),
  genParticlesTag_(iConfig.getUntrackedParameter<edm::InputTag>("genParticlesTag",edm::InputTag("genParticles"))),
  jetCorrectorServiceName_(iConfig.getUntrackedParameter<std::string>("jetCorrectorServiceName","ic5CaloL1L2L3Residual")),
  jetTag_(iConfig.getUntrackedParameter<edm::InputTag>("jetTag",edm::InputTag("iterativeCone5CaloJets"))),
  jetAK5Tag_(iConfig.getUntrackedParameter<edm::InputTag>("jetAK5Tag",edm::InputTag("ak5CaloJets"))),
  muonTag_(iConfig.getUntrackedParameter<edm::InputTag>("muonTag",edm::InputTag("muons"))),
  cosmicMuonTag_(iConfig.getUntrackedParameter<edm::InputTag>("cosmicMuonTag",edm::InputTag("muonsFromCosmics"))),
  standAloneMuonTag_(iConfig.getUntrackedParameter<edm::InputTag>("standAloneMuonTag",edm::InputTag("standAloneMuons"))),
  refittedStandAloneMuonTag_(iConfig.getUntrackedParameter<edm::InputTag>("refittedStandAloneMuonTag",edm::InputTag("refittedStandAloneMuons"))),
  verticesTag_(iConfig.getUntrackedParameter<edm::InputTag>("verticesTag", edm::InputTag("offlinePrimaryVertices"))),
  tracksTag_(iConfig.getUntrackedParameter<edm::InputTag>("tracksTag", edm::InputTag("generalTracks"))),
  //caloTowerTag_(iConfig.getUntrackedParameter<edm::InputTag>("caloTowerTag",edm::InputTag("towerMaker"))),
  caloRecHitTag_(iConfig.getUntrackedParameter<edm::InputTag>("caloRecHitTag",edm::InputTag("hbhereco"))),
  hcalNoiseTag_(iConfig.getUntrackedParameter<edm::InputTag>("hcalNoiseTag",edm::InputTag("hcalnoise"))),
  hcalNoiseFilterResultTag_(iConfig.getUntrackedParameter<edm::InputTag>("hcalNoiseFilterResultTag",edm::InputTag("HBHENoiseFilterResultProducer"))),
  rbxTag_(iConfig.getUntrackedParameter<edm::InputTag>("rbxTag",edm::InputTag("hcalnoise"))),
  hpdTag_(iConfig.getUntrackedParameter<edm::InputTag>("hpdTag",edm::InputTag("hcalnoise"))),
  hcalRecHitTag_(iConfig.getUntrackedParameter<edm::InputTag>("hcalRecHitTag",edm::InputTag("hbhereco"))),
  hfRecHitTag_(iConfig.getUntrackedParameter<edm::InputTag>("hfRecHitTag",edm::InputTag("hfreco"))),
  hcalDigiTag_(iConfig.getUntrackedParameter<edm::InputTag>("hcalDigiTag",edm::InputTag("hcalDigis"))),
  cscSegmentsTag_(iConfig.getUntrackedParameter<edm::InputTag>("cscSegmentsTag",edm::InputTag("cscSegments"))),
  cscRecHitsTag_(iConfig.getUntrackedParameter<edm::InputTag>("cscRecHitsTag",edm::InputTag("csc2DRecHits"))), 
  DTRecHitsTag_(iConfig.getUntrackedParameter<edm::InputTag>("DTRecHitsTag",edm::InputTag("dt1DRecHits"))),
  DT4DSegmentsTag_(iConfig.getUntrackedParameter<edm::InputTag>("DT4DSegmentsTag",edm::InputTag("dt4DSegments"))),
  timeTag_(iConfig.getUntrackedParameter<edm::InputTag>("timeTag",edm::InputTag("muontimingDelayedMuons"))),
  rpcRecHitsTag_(iConfig.getUntrackedParameter<edm::InputTag>("rpcRecHitsTag",edm::InputTag("rpcRecHits"))),

  recoGenDeltaR_(iConfig.getUntrackedParameter<double>("recoGenDeltaR", 0.1)),
  recoTriggerDeltaR_(iConfig.getUntrackedParameter<double>("recoTriggerDeltaR", 0.1)),
  towerMinEnergy_(iConfig.getUntrackedParameter<double>("towerMinEnergy", 1.)),
  towerMaxEta_(iConfig.getUntrackedParameter<double>("towerMaxEta", 1.3)),
  jetMinEnergy_(iConfig.getUntrackedParameter<double>("jetMinEnergy", 1.)),
  jetMaxEta_(iConfig.getUntrackedParameter<double>("jetMaxEta", 3.)),
  digiMinFc_(iConfig.getUntrackedParameter<double>("digiMinFc", 30)),
  rechitMinEnergy_(iConfig.getUntrackedParameter<double>("rechitMinEnergy", 0.2)),
  GlobalMinNDOF_(iConfig.getUntrackedParameter<int>("GlobalMinNDOF", 8)),
  GlobalMinNDOFDT_(iConfig.getUntrackedParameter<int>("GlobalMinNDOFDT", 6)),
  GlobalMinNDOFCSC_(iConfig.getUntrackedParameter<int>("GlobalMinNDOFCSC", 6)),
  GlobalMaxTOFErr_(iConfig.getUntrackedParameter<double>("GlobalMaxTOFErr", 0.07)),
  GlobalMinTOF_(iConfig.getUntrackedParameter<double>("GlobalMinTOF", 1.0)),
  studyJetMinEta_(iConfig.getUntrackedParameter<double>("studyJetMinEta",1.3)),
  studyJetMaxEta_(iConfig.getUntrackedParameter<double>("studyJetMaxEta",3.0)),
  studyTowerMinEta_(iConfig.getUntrackedParameter<double>("studyTowerMinEta",1.3)),
  studyTowerMaxEta_(iConfig.getUntrackedParameter<double>("studyTowerMaxEta",3.0)),
  badchannelstatus_(iConfig.getUntrackedParameter<int>("badchannelstatus",0)),
  makeReducedNtuples_(iConfig.getUntrackedParameter<bool>("makeReducedNtuples",false)),
  currentFill_(0),
  currentFillL1_(0),
  currentColls_(0),
  currentBunches_(0),
  l1JetsMissing_(false),
  l1MuonsMissing_(false),
  hltMuonsMissing_(false),
  hltMissing_(false),
  mcMissing_(false),
  jetsMissing_(false),
  muonsMissing_(false),
  towersMissing_(false),
  rechitsMissing_(false),
  noiseSumMissing_(false),
  rbxsMissing_(false),
  hpdsMissing_(false),
  digisMissing_(false),
  hcalDetIds_(0),
  hcalDetJets_(0)
{
  // set up output
  tree_=fs_->make<TTree>("StoppedHSCPMuonTree", "");
  tree_->Branch("events", "StoppedHSCPMuonEvent", &event_, 64000, 1);
  
  // log
  std::string log="reco ";
  if (isMC_) log += " mc";
  if (doCaloTowers_) log += " calotowers";
  if (doRecHits_) log += " rechits";

  edm::LogInfo("StoppedHSCPMuonTree") << "Going to fill " << log << std::endl;

  HcalLogicalMapGenerator gen;
  logicalMap_=new HcalLogicalMap(gen.createMap());

  const float epsilon = 0.001;
  Surface::RotationType rot; // unit rotation matrix

  // values taken from CMS NOTE 2005/016
  const float barrelRadius = 287.65;
  const float barrelHalfLength = 433.20;

  theHCALbarrel_ = new BoundCylinder( Surface::PositionType(0,0,0), rot, SimpleCylinderBounds( -epsilon, barrelRadius+epsilon, -barrelHalfLength, barrelHalfLength));

  edm::ParameterSet serviceParameters = iConfig.getParameter<edm::ParameterSet>("ServiceParameters");
  edm::ParameterSet matchParameters = iConfig.getParameter<edm::ParameterSet>("MatchParameters");
  muonService = new MuonServiceProxy(serviceParameters);
  segmentMatcher = new MuonSegmentMatcher(matchParameters, muonService);

}


StoppedHSCPMuonTreeProducer::~StoppedHSCPMuonTreeProducer() {

   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called once each job just before starting event loop  ------------
void 
StoppedHSCPMuonTreeProducer::beginJob()
{
}

// -- called once per run
void 
StoppedHSCPMuonTreeProducer::beginRun(edm::Run const & iRun, edm::EventSetup const& iSetup)
{
  //std::cout<<"starting beginRun"<<std::endl;

  // Get PDT Table if MC
  if (isMC_)
    iSetup.getData(fPDGTable);

  // HLT setup
  bool changed;
  hltConfig_.init(iRun, iSetup, hltResultsTag_.process(), changed);
  
  // HLT Path -- No BPTX
  try{
    hltPathIndexJetNoBptx_=(hltConfig_.triggerNames()).size();  // default setting -- trigger not found
    for (uint i=0;i<(hltConfig_.triggerNames()).size();++i) // loop over trigger names
      {
	std::string trigName=hltConfig_.triggerName(i);
	// Search for first occurrence of trigger name -- store vector of all triggers found at some point?
	if (hltPathJetNoBptx_.size()>0 &&
	    trigName.find(hltPathJetNoBptx_)!= std::string::npos)
	  {
	    hltPathIndexJetNoBptx_ = hltConfig_.triggerIndex(trigName); // could just set to i, but let's be careful...
	  }
      }
    if (hltPathIndexJetNoBptx_==(hltConfig_.triggerNames()).size())
      {
	edm::LogWarning("StoppedHSCPMuonTree") << "HLTJetNoBPTX:  Could not find an HLT path matching "<<hltPathJetNoBptx_<<".  Branch will not be filled."<<std::endl;
	doHltBit1_=false;
      }
    else
      edm::LogInfo("StoppedHSCPMuonTree") << hltPathJetNoBptx_ << " index is " << hltPathIndexJetNoBptx_ << std::endl;
  } // end of try loop
  catch (cms::Exception e) {
    edm::LogWarning("StoppedHSCPMuonTree") << "HLTJetNoBPTX:  Could not find an HLT path matching " << hltPathJetNoBptx_ << ".  Branch will not be filled" << std::endl;
    doHltBit1_ = false;
  }
  // HLT Path -- No BPTX, No Halo
  try {
    hltPathIndexJetNoBptxNoHalo_=(hltConfig_.triggerNames()).size();  // default value
    for (uint i=0;i<(hltConfig_.triggerNames()).size();++i)
      {
	std::string trigName=hltConfig_.triggerName(i);
	// Search triggers for NoBpxtNoHalo name
	if (hltPathJetNoBptxNoHalo_.size()>0 &&
	    trigName.find(hltPathJetNoBptxNoHalo_)!= std::string::npos)
	  {
	    hltPathIndexJetNoBptxNoHalo_ = hltConfig_.triggerIndex(trigName); // could just set to i, but let's be careful...
	  }
      }
    if (hltPathIndexJetNoBptxNoHalo_==(hltConfig_.triggerNames()).size())
      {
	edm::LogWarning("StoppedHSCPMuonTree") << "HLTJetNoBPTXNoHalo:  Could not find an HLT path matching "<<hltPathJetNoBptxNoHalo_<<".  Branch will not be filled."<<std::endl;
	doHltBit2_=false;
      }
    else
      edm::LogInfo("StoppedHSCPMuonTree") << hltPathJetNoBptxNoHalo_ << " index is " << hltPathIndexJetNoBptxNoHalo_ << std::endl;
  }
  catch (cms::Exception e) {
    edm::LogWarning("StoppedHSCPMuonTree") << "HLTJetNoBPTXNoHalo:  Could not find an HLT path matching " << hltPathJetNoBptxNoHalo_ << ".  Branch will not be filled" << std::endl;
    doHltBit2_ = false;
  }
  // HLT Path -- No BPTX, No Halo, 3BX
  try {
    hltPathIndexJetNoBptx3BXNoHalo_=(hltConfig_.triggerNames()).size();  // default value
    for (uint i=0;i<(hltConfig_.triggerNames()).size();++i)
      {
	std::string trigName=hltConfig_.triggerName(i);
	// Search for first occurrence of trigger name
	if (hltPathJetNoBptx3BXNoHalo_.size()>0 &&
	    trigName.find(hltPathJetNoBptx3BXNoHalo_)!= std::string::npos)
	  {
	    hltPathIndexJetNoBptx3BXNoHalo_ = hltConfig_.triggerIndex(trigName); // could just set to i, but let's be careful...
	  }
      }
    edm::LogInfo("StoppedHSCPMuonTree") << hltPathJetNoBptx3BXNoHalo_ << " index is " << hltPathIndexJetNoBptx3BXNoHalo_ << std::endl;
    if (hltPathIndexJetNoBptx3BXNoHalo_==(hltConfig_.triggerNames()).size())
      {
	edm::LogWarning("StoppedHSCPMuonTree") << "HLTJetNoBPTX3BXNoHalo:  Could not find an HLT path matching "<<hltPathJetNoBptx3BXNoHalo_<<".  Branch will not be filled."<<std::endl;
	doHltBit3_=false;
      }
    else
      edm::LogInfo("StoppedHSCPMuonTree") << hltPathJetNoBptx3BXNoHalo_ << " index is " << hltPathIndexJetNoBptx3BXNoHalo_ << std::endl;
  }
  catch (cms::Exception e) {
    edm::LogWarning("StoppedHSCPMuonTree") << "HLTJetNoBPTX3BXNoHalo:  Could not find an HLT path matching " << hltPathJetNoBptx3BXNoHalo_ << ".  Branch will not be filled" << std::endl;
    doHltBit3_ = false;
  }

  // HLT Path -- JetE50 No BPTX, No Halo, 3BX
  try {
    hltPathIndexJetE50NoBptx3BXNoHalo_=(hltConfig_.triggerNames()).size();  // default value
    for (uint i=0;i<(hltConfig_.triggerNames()).size();++i)
      {
	std::string trigName=hltConfig_.triggerName(i);
	// Search for first occurrence of trigger name
	if (hltPathJetE50NoBptx3BXNoHalo_.size()>0 &&
	    trigName.find(hltPathJetE50NoBptx3BXNoHalo_)!= std::string::npos)
	  {
	    hltPathIndexJetE50NoBptx3BXNoHalo_ = hltConfig_.triggerIndex(trigName); // could just set to i, but let's be careful...
	  }
      }
    edm::LogInfo("StoppedHSCPMuonTree") << hltPathJetE50NoBptx3BXNoHalo_ << " index is " << hltPathIndexJetE50NoBptx3BXNoHalo_ << std::endl;
    if (hltPathIndexJetE50NoBptx3BXNoHalo_==(hltConfig_.triggerNames()).size())
      {
	edm::LogWarning("StoppedHSCPMuonTree") << "HLTJetE50NoBPTX3BXNoHalo:  Could not find an HLT path matching "<<hltPathJetE50NoBptx3BXNoHalo_<<".  Branch will not be filled."<<std::endl;
	doHltBit4_=false;
      }
    else
      edm::LogInfo("StoppedHSCPMuonTree") << hltPathJetE50NoBptx3BXNoHalo_ << " index is " << hltPathIndexJetE50NoBptx3BXNoHalo_ << std::endl;
  }
  catch (cms::Exception e) {
    edm::LogWarning("StoppedHSCPMuonTree") << "HLTJetE50NoBPTX3BXNoHalo:  Could not find an HLT path matching " << hltPathJetE50NoBptx3BXNoHalo_ << ".  Branch will not be filled" << std::endl;
    doHltBit4_ = false;
  }

  // HLT Path -- HLT_L2Mu20_eta2p1_NoVertex
  try {
    hltPathIndexL2Mu20eta2p1NoVertex_=(hltConfig_.triggerNames()).size();  // default value
    for (uint i=0;i<(hltConfig_.triggerNames()).size();++i)
      {
	std::string trigName=hltConfig_.triggerName(i);
	// Search for first occurrence of trigger name
	if (hltPathL2Mu20eta2p1NoVertex_.size()>0 &&
	    trigName.find(hltPathL2Mu20eta2p1NoVertex_)!= std::string::npos)
	  {
	    hltPathIndexL2Mu20eta2p1NoVertex_ = hltConfig_.triggerIndex(trigName); // could just set to i, but let's be careful...
	  }
      }
    edm::LogInfo("StoppedHSCPMuonTree") << hltPathL2Mu20eta2p1NoVertex_ << " index is " << hltPathIndexL2Mu20eta2p1NoVertex_ << std::endl;
    if (hltPathIndexL2Mu20eta2p1NoVertex_==(hltConfig_.triggerNames()).size())
      {
	edm::LogWarning("StoppedHSCPMuonTree") << "HLTJetE50NoBPTX3BXNoHalo:  Could not find an HLT path matching "<<hltPathL2Mu20eta2p1NoVertex_<<".  Branch will not be filled."<<std::endl;
	doHltBit5_=false;
      }
    else
      edm::LogInfo("StoppedHSCPMuonTree") << hltPathL2Mu20eta2p1NoVertex_ << " index is " << hltPathIndexL2Mu20eta2p1NoVertex_ << std::endl;
  }
  catch (cms::Exception e) {
    edm::LogWarning("StoppedHSCPMuonTree") << "HLTL2Mu20eta2p1NoVertex:  Could not find an HLT path matching " << hltPathL2Mu20eta2p1NoVertex_ << ".  Branch will not be filled" << std::endl;
    doHltBit5_ = false;
  }

  // HLT Path -- HLT_L2Mu10_NoVertex_NoBPTX3BX
  try {
    hltPathIndexL2Mu10NoVertexNoBptx3BX_=(hltConfig_.triggerNames()).size();  // default value
    for (uint i=0;i<(hltConfig_.triggerNames()).size();++i)
      {
	std::string trigName=hltConfig_.triggerName(i);
	// Search for first occurrence of trigger name
	if (hltPathL2Mu10NoVertexNoBptx3BX_.size()>0 &&
	    trigName.find(hltPathL2Mu10NoVertexNoBptx3BX_)!= std::string::npos)
	  {
	    hltPathIndexL2Mu10NoVertexNoBptx3BX_ = hltConfig_.triggerIndex(trigName); // could just set to i, but let's be careful...
	  }
      }
    edm::LogInfo("StoppedHSCPMuonTree") << hltPathL2Mu10NoVertexNoBptx3BX_ << " index is " << hltPathIndexL2Mu10NoVertexNoBptx3BX_ << std::endl;
    if (hltPathIndexL2Mu10NoVertexNoBptx3BX_==(hltConfig_.triggerNames()).size())
      {
	edm::LogWarning("StoppedHSCPMuonTree") << "HLTJetE50NoBPTX3BXNoHalo:  Could not find an HLT path matching "<<hltPathL2Mu10NoVertexNoBptx3BX_<<".  Branch will not be filled."<<std::endl;
	doHltBit6_=false;
      }
    else
      edm::LogInfo("StoppedHSCPMuonTree") << hltPathL2Mu10NoVertexNoBptx3BX_ << " index is " << hltPathIndexL2Mu10NoVertexNoBptx3BX_ << std::endl;
  }
  catch (cms::Exception e) {
    edm::LogWarning("StoppedHSCPMuonTree") << "HLTL2Mu10NoVertexNoBptx3BX:  Could not find an HLT path matching " << hltPathL2Mu10NoVertexNoBptx3BX_ << ".  Branch will not be filled" << std::endl;
    doHltBit6_ = false;
  }

  // HLT Path -- HLT_L2Mu20_NoVertex_NoBPTX3BX
  try {
    hltPathIndexL2Mu20NoVertexNoBptx3BX_=(hltConfig_.triggerNames()).size();  // default value
    for (uint i=0;i<(hltConfig_.triggerNames()).size();++i)
      {
	std::string trigName=hltConfig_.triggerName(i);
	// Search for first occurrence of trigger name
	if (hltPathL2Mu20NoVertexNoBptx3BX_.size()>0 &&
	    trigName.find(hltPathL2Mu20NoVertexNoBptx3BX_)!= std::string::npos)
	  {
	    hltPathIndexL2Mu20NoVertexNoBptx3BX_ = hltConfig_.triggerIndex(trigName); // could just set to i, but let's be careful...
	  }
      }
    edm::LogInfo("StoppedHSCPMuonTree") << hltPathL2Mu20NoVertexNoBptx3BX_ << " index is " << hltPathIndexL2Mu20NoVertexNoBptx3BX_ << std::endl;
    if (hltPathIndexL2Mu20NoVertexNoBptx3BX_==(hltConfig_.triggerNames()).size())
      {
	edm::LogWarning("StoppedHSCPMuonTree") << "HLTJetE50NoBPTX3BXNoHalo:  Could not find an HLT path matching "<<hltPathL2Mu20NoVertexNoBptx3BX_<<".  Branch will not be filled."<<std::endl;
	doHltBit7_=false;
      }
    else
      edm::LogInfo("StoppedHSCPMuonTree") << hltPathL2Mu20NoVertexNoBptx3BX_ << " index is " << hltPathIndexL2Mu20NoVertexNoBptx3BX_ << std::endl;
  }
  catch (cms::Exception e) {
    edm::LogWarning("StoppedHSCPMuonTree") << "HLTL2Mu20NoVertexNoBptx3BX:  Could not find an HLT path matching " << hltPathL2Mu20NoVertexNoBptx3BX_ << ".  Branch will not be filled" << std::endl;
    doHltBit7_ = false;
  }

  // HLT Path -- HLT_L2Mu30_NoVertex_NoBPTX3BX
  try {
    hltPathIndexL2Mu30NoVertexNoBptx3BX_=(hltConfig_.triggerNames()).size();  // default value
    for (uint i=0;i<(hltConfig_.triggerNames()).size();++i)
      {
	std::string trigName=hltConfig_.triggerName(i);
	// Search for first occurrence of trigger name
	if (hltPathL2Mu30NoVertexNoBptx3BX_.size()>0 &&
	    trigName.find(hltPathL2Mu30NoVertexNoBptx3BX_)!= std::string::npos)
	  {
	    hltPathIndexL2Mu30NoVertexNoBptx3BX_ = hltConfig_.triggerIndex(trigName); // could just set to i, but let's be careful...
	  }
      }
    edm::LogInfo("StoppedHSCPMuonTree") << hltPathL2Mu30NoVertexNoBptx3BX_ << " index is " << hltPathIndexL2Mu30NoVertexNoBptx3BX_ << std::endl;
    if (hltPathIndexL2Mu30NoVertexNoBptx3BX_==(hltConfig_.triggerNames()).size())
      {
	edm::LogWarning("StoppedHSCPMuonTree") << "HLTJetE50NoBPTX3BXNoHalo:  Could not find an HLT path matching "<<hltPathL2Mu30NoVertexNoBptx3BX_<<".  Branch will not be filled."<<std::endl;
	doHltBit8_=false;
      }
    else
      edm::LogInfo("StoppedHSCPMuonTree") << hltPathL2Mu30NoVertexNoBptx3BX_ << " index is " << hltPathIndexL2Mu30NoVertexNoBptx3BX_ << std::endl;
  }
  catch (cms::Exception e) {
    edm::LogWarning("StoppedHSCPMuonTree") << "HLTL2Mu30NoVertexNoBptx3BX:  Could not find an HLT path matching " << hltPathL2Mu30NoVertexNoBptx3BX_ << ".  Branch will not be filled" << std::endl;
    doHltBit8_ = false;
  }


  // HLT Path -- HLT_L2Mu10_NoVertex_NoBPTX3BX_NoHalo
  try {
    hltPathIndexL2Mu10NoVertexNoBptx3BXNoHalo_=(hltConfig_.triggerNames()).size();  // default value
    for (uint i=0;i<(hltConfig_.triggerNames()).size();++i)
      {
	std::string trigName=hltConfig_.triggerName(i);
	// Search for first occurrence of trigger name
	if (hltPathL2Mu10NoVertexNoBptx3BXNoHalo_.size()>0 &&
	    trigName.find(hltPathL2Mu10NoVertexNoBptx3BXNoHalo_)!= std::string::npos)
	  {
	    hltPathIndexL2Mu10NoVertexNoBptx3BXNoHalo_ = hltConfig_.triggerIndex(trigName); // could just set to i, but let's be careful...
	  }
      }
    edm::LogInfo("StoppedHSCPMuonTree") << hltPathL2Mu10NoVertexNoBptx3BXNoHalo_ << " index is " << hltPathIndexL2Mu10NoVertexNoBptx3BXNoHalo_ << std::endl;
    if (hltPathIndexL2Mu10NoVertexNoBptx3BXNoHalo_==(hltConfig_.triggerNames()).size())
      {
	edm::LogWarning("StoppedHSCPMuonTree") << "HLTJetE50NoBPTX3BXNoHaloNoHalo:  Could not find an HLT path matching "<<hltPathL2Mu10NoVertexNoBptx3BXNoHalo_<<".  Branch will not be filled."<<std::endl;
	doHltBit9_=false;
      }
    else
      edm::LogInfo("StoppedHSCPMuonTree") << hltPathL2Mu10NoVertexNoBptx3BXNoHalo_ << " index is " << hltPathIndexL2Mu10NoVertexNoBptx3BXNoHalo_ << std::endl;
  }
  catch (cms::Exception e) {
    edm::LogWarning("StoppedHSCPMuonTree") << "HLTL2Mu10NoVertexNoBptx3BXNoHalo:  Could not find an HLT path matching " << hltPathL2Mu10NoVertexNoBptx3BXNoHalo_ << ".  Branch will not be filled" << std::endl;
    doHltBit9_ = false;
  }

  // HLT Path -- HLT_L2Mu20_NoVertex_NoBPTX3BX_NoHalo
  try {
    hltPathIndexL2Mu20NoVertexNoBptx3BXNoHalo_=(hltConfig_.triggerNames()).size();  // default value
    for (uint i=0;i<(hltConfig_.triggerNames()).size();++i)
      {
	std::string trigName=hltConfig_.triggerName(i);
	// Search for first occurrence of trigger name
	if (hltPathL2Mu20NoVertexNoBptx3BXNoHalo_.size()>0 &&
	    trigName.find(hltPathL2Mu20NoVertexNoBptx3BXNoHalo_)!= std::string::npos)
	  {
	    hltPathIndexL2Mu20NoVertexNoBptx3BXNoHalo_ = hltConfig_.triggerIndex(trigName); // could just set to i, but let's be careful...
	  }
      }
    edm::LogInfo("StoppedHSCPMuonTree") << hltPathL2Mu20NoVertexNoBptx3BXNoHalo_ << " index is " << hltPathIndexL2Mu20NoVertexNoBptx3BXNoHalo_ << std::endl;
    if (hltPathIndexL2Mu20NoVertexNoBptx3BXNoHalo_==(hltConfig_.triggerNames()).size())
      {
	edm::LogWarning("StoppedHSCPMuonTree") << "HLTJetE50NoBPTX3BXNoHaloNoHalo:  Could not find an HLT path matching "<<hltPathL2Mu20NoVertexNoBptx3BXNoHalo_<<".  Branch will not be filled."<<std::endl;
	doHltBit10_=false;
      }
    else
      edm::LogInfo("StoppedHSCPMuonTree") << hltPathL2Mu20NoVertexNoBptx3BXNoHalo_ << " index is " << hltPathIndexL2Mu20NoVertexNoBptx3BXNoHalo_ << std::endl;
  }
  catch (cms::Exception e) {
    edm::LogWarning("StoppedHSCPMuonTree") << "HLTL2Mu20NoVertexNoBptx3BXNoHalo:  Could not find an HLT path matching " << hltPathL2Mu20NoVertexNoBptx3BXNoHalo_ << ".  Branch will not be filled" << std::endl;
    doHltBit10_ = false;
  }

  // HLT Path -- HLT_L2Mu30_NoVertex_NoBPTX3BX_NoHalo
  try {
    hltPathIndexL2Mu30NoVertexNoBptx3BXNoHalo_=(hltConfig_.triggerNames()).size();  // default value
    for (uint i=0;i<(hltConfig_.triggerNames()).size();++i)
      {
	std::string trigName=hltConfig_.triggerName(i);
	// Search for first occurrence of trigger name
	if (hltPathL2Mu30NoVertexNoBptx3BXNoHalo_.size()>0 &&
	    trigName.find(hltPathL2Mu30NoVertexNoBptx3BXNoHalo_)!= std::string::npos)
	  {
	    hltPathIndexL2Mu30NoVertexNoBptx3BXNoHalo_ = hltConfig_.triggerIndex(trigName); // could just set to i, but let's be careful...
	  }
      }
    edm::LogInfo("StoppedHSCPMuonTree") << hltPathL2Mu30NoVertexNoBptx3BXNoHalo_ << " index is " << hltPathIndexL2Mu30NoVertexNoBptx3BXNoHalo_ << std::endl;
    if (hltPathIndexL2Mu30NoVertexNoBptx3BXNoHalo_==(hltConfig_.triggerNames()).size())
      {
	edm::LogWarning("StoppedHSCPMuonTree") << "HLTJetE50NoBPTX3BXNoHaloNoHalo:  Could not find an HLT path matching "<<hltPathL2Mu30NoVertexNoBptx3BXNoHalo_<<".  Branch will not be filled."<<std::endl;
	doHltBit11_=false;
      }
    else
      edm::LogInfo("StoppedHSCPMuonTree") << hltPathL2Mu30NoVertexNoBptx3BXNoHalo_ << " index is " << hltPathIndexL2Mu30NoVertexNoBptx3BXNoHalo_ << std::endl;
  }
  catch (cms::Exception e) {
    edm::LogWarning("StoppedHSCPMuonTree") << "HLTL2Mu30NoVertexNoBptx3BXNoHalo:  Could not find an HLT path matching " << hltPathL2Mu30NoVertexNoBptx3BXNoHalo_ << ".  Branch will not be filled" << std::endl;
    doHltBit11_ = false;
  }

  // HLT Path -- HLT_L2Mu20_NoVertex_2Cha_NoBPTX3BX_NoHalo
  try {
    hltPathIndexL2Mu20NoVertex2ChaNoBptx3BXNoHalo_=(hltConfig_.triggerNames()).size();  // default value
    for (uint i=0;i<(hltConfig_.triggerNames()).size();++i)
      {
	std::string trigName=hltConfig_.triggerName(i);
	// Search for first occurrence of trigger name
	if (hltPathL2Mu20NoVertex2ChaNoBptx3BXNoHalo_.size()>0 &&
	    trigName.find(hltPathL2Mu20NoVertex2ChaNoBptx3BXNoHalo_)!= std::string::npos)
	  {
	    hltPathIndexL2Mu20NoVertex2ChaNoBptx3BXNoHalo_ = hltConfig_.triggerIndex(trigName); // could just set to i, but let's be careful...
	  }
      }
    edm::LogInfo("StoppedHSCPMuonTree") << hltPathL2Mu20NoVertex2ChaNoBptx3BXNoHalo_ << " index is " << hltPathIndexL2Mu20NoVertex2ChaNoBptx3BXNoHalo_ << std::endl;
    if (hltPathIndexL2Mu20NoVertex2ChaNoBptx3BXNoHalo_==(hltConfig_.triggerNames()).size())
      {
	edm::LogWarning("StoppedHSCPMuonTree") << "HLTJetE50NoBPTX3BXNoHaloNoHalo:  Could not find an HLT path matching "<<hltPathL2Mu20NoVertex2ChaNoBptx3BXNoHalo_<<".  Branch will not be filled."<<std::endl;
	doHltBit12_=false;
      }
    else
      edm::LogInfo("StoppedHSCPMuonTree") << hltPathL2Mu20NoVertex2ChaNoBptx3BXNoHalo_ << " index is " << hltPathIndexL2Mu20NoVertex2ChaNoBptx3BXNoHalo_ << std::endl;
  }
  catch (cms::Exception e) {
    edm::LogWarning("StoppedHSCPMuonTree") << "HLTL2Mu20NoVertex2ChaNoBptx3BXNoHalo:  Could not find an HLT path matching " << hltPathL2Mu20NoVertex2ChaNoBptx3BXNoHalo_ << ".  Branch will not be filled" << std::endl;
    doHltBit12_ = false;
  }

  // HLT Path -- HLT_L2Mu30_NoVertex_2Cha_NoBPTX3BX_NoHalo
  try {
    hltPathIndexL2Mu30NoVertex2ChaNoBptx3BXNoHalo_=(hltConfig_.triggerNames()).size();  // default value
    for (uint i=0;i<(hltConfig_.triggerNames()).size();++i)
      {
	std::string trigName=hltConfig_.triggerName(i);
	// Search for first occurrence of trigger name
	if (hltPathL2Mu30NoVertex2ChaNoBptx3BXNoHalo_.size()>0 &&
	    trigName.find(hltPathL2Mu30NoVertex2ChaNoBptx3BXNoHalo_)!= std::string::npos)
	  {
	    hltPathIndexL2Mu30NoVertex2ChaNoBptx3BXNoHalo_ = hltConfig_.triggerIndex(trigName); // could just set to i, but let's be careful...
	  }
      }
    edm::LogInfo("StoppedHSCPMuonTree") << hltPathL2Mu30NoVertex2ChaNoBptx3BXNoHalo_ << " index is " << hltPathIndexL2Mu30NoVertex2ChaNoBptx3BXNoHalo_ << std::endl;
    if (hltPathIndexL2Mu30NoVertex2ChaNoBptx3BXNoHalo_==(hltConfig_.triggerNames()).size())
      {
	edm::LogWarning("StoppedHSCPMuonTree") << "HLTJetE50NoBPTX3BXNoHaloNoHalo:  Could not find an HLT path matching "<<hltPathL2Mu30NoVertex2ChaNoBptx3BXNoHalo_<<".  Branch will not be filled."<<std::endl;
	doHltBit13_=false;
      }
    else
      edm::LogInfo("StoppedHSCPMuonTree") << hltPathL2Mu30NoVertex2ChaNoBptx3BXNoHalo_ << " index is " << hltPathIndexL2Mu30NoVertex2ChaNoBptx3BXNoHalo_ << std::endl;
  }
  catch (cms::Exception e) {
    edm::LogWarning("StoppedHSCPMuonTree") << "HLTL2Mu30NoVertex2ChaNoBptx3BXNoHalo:  Could not find an HLT path matching " << hltPathL2Mu30NoVertex2ChaNoBptx3BXNoHalo_ << ".  Branch will not be filled" << std::endl;
    doHltBit13_ = false;
  }


  // end of HLT checks

  // HCAL geometry to calculate eta/phi for CaloRecHits
  edm::ESHandle<CaloGeometry> caloGeomRec;
  iSetup.get<CaloGeometryRecord>().get(caloGeomRec);
  caloGeom_ = caloGeomRec.product();

  // HCAL bad channel removal
  badChannels_.clear();
  edm::ESHandle<HcalChannelQuality> p;
  iSetup.get<HcalChannelQualityRcd>().get(p);
  //std::cout <<"BEGIN RUN STARTED!"<<std::endl;
  chanquality_= new HcalChannelQuality(*p.product());
  std::vector<DetId> mydetids = chanquality_->getAllChannels();
  for (std::vector<DetId>::const_iterator i = mydetids.begin();i!=mydetids.end();++i)
    {
      if (i->det()!=DetId::Hcal) continue; // not an hcal cell
      // Only consider HB/HE for now; revise when necessary
      if (i->subdetId()!=HcalBarrel && i->subdetId()!=HcalEndcap) continue;
      HcalDetId id=HcalDetId(*i);
      int status=(chanquality_->getValues(id))->getValue();
      //std::cout <<"checking "<<id<<"  STATUS = "<<status<<std::endl;
      if ((status&badchannelstatus_)==0) continue;
      //std::cout <<"\tBAD CHANNEL FOUND!"<<id<<"  STATUS = "<<status<<std::endl;
      badChannels_.insert(id);
    }

  // get ConditionsInRun block
  edm::Handle<edm::ConditionsInRunBlock> condInRunBlock;
  iRun.getByLabel(condInEdmTag_, condInRunBlock);

  if (condInRunBlock.isValid()) {
    currentFillL1_ = condInRunBlock->lhcFillNumber;
  }

  // set filling scheme for this run
  currentColls_ = fills_.getCollisionsFromRun(iRun.runAuxiliary().run());
  currentBunches_ = fills_.getBunchesFromRun(iRun.runAuxiliary().run());
  currentFill_  = fills_.getFillFromRun(iRun.runAuxiliary().run());

  //std::cout<<"end of beginRun"<<std::endl;
}


// ------------ method called once each job just after ending the event loop  ------------
void 
StoppedHSCPMuonTreeProducer::endJob() {
}

// ------------ method called to for each event  ------------
void
StoppedHSCPMuonTreeProducer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  //std::cout<<"_____________________"<<std::endl;
  //std::cout<<"for event "<<std::endl;
 
  event_ = new StoppedHSCPMuonEvent();
  std::vector<DTRecHit1D> DTRecHits;
  reco::TrackRef muonTrack;
  const reco::Vertex::Point PV;
  reco::CompositeCandidateCollection dimuons;

  if (isMC_) doMC(iEvent);
 
  // event & trigger info
  doEventInfo(iEvent);
  doTrigger(iEvent, iSetup);
  //std::cout<<"finished doTrigger"<<std::endl;

  // general RECO info
  //doVertices(iEvent,PV); //now gets done every time doStandAloneMuons is done
  doJets(iEvent, iSetup);
  //std::cout<<"finished doJets"<<std::endl;
  //commenting out doGlobalCalo because gives some errors
  //doGlobalCalo(iEvent); // uses ntuple calotower info for leadingIphiFractionValue
  //std::cout<<"finished doGlobalCalo"<<std::endl;
  doMuons(iEvent, dimuons);
  //std::cout<<"finished doMuons"<<std::endl;
  doCosmicMuons(iEvent);
  doStandAloneMuons(iEvent, iSetup);
  //std::cout<<"finished doStandAloneMuons"<<std::endl;
  doRefittedStandAloneMuons(iEvent, iSetup);


  doBeamHalo(iEvent);
  doTracks(iEvent, iSetup);

  // methods for time of flight variables
  doTOF(iEvent);
  doTOFDT(iEvent);
  doTOFCSC(iEvent);
  doREFITTOF(iEvent);
  doREFITTOFDT(iEvent);
  doREFITTOFCSC(iEvent);

  // HCAL noise summary info
  doHcalNoise(iEvent);

  // HCAL RecHits & flags
  doHcalRecHits(iEvent);
  doHFRecHits(iEvent);

  // CSC segments
  doCscSegments(iEvent, iSetup);
  doCscHits(iEvent, iSetup); 
  //doSlices(iEvent, iSetup);  // HE info

  //std::cout<<"starting doMuonDTs"<<std::endl;
  // DT Segments
  doMuonDTs(iEvent, iSetup, DTRecHits);
  //std::cout<<"finished doMuonDTs"<<std::endl;

  // RPCs
  doMuonRPCs(iEvent,iSetup);

  // digi based variables
  if (doDigis_) {
    doTimingFromDigis(iEvent, iSetup);
  }
 
  // if making reduced ntuples, return without writing event
  // unless basic selection criteria met
  if (makeReducedNtuples_==true)
    {
      // reject cosmics
      if (event_->mu_N>0)
	return;

      // loose jet cuts
      if ( event_->jet_N==0) 
	return;
      bool passloosejetcut=false;
      for (uint z=0;z<event_->jet_N;++z)
	{
	  if (event_->jetE[z]>=50 && fabs(event_->jetEta[z])<1.3)
	    {
	      passloosejetcut=true;
	      break;
	    }
	}
      if (passloosejetcut==false)
	return;
    } // if (makeReducedNtuples_==true)

  // remove calotowers
  if (!doCaloTowers_)
    event_->removeTowers(); // caloTowers don't need to be saved, unless specified in cfg

  // fill TTree
  tree_->Fill();
  
  delete event_;

}



void StoppedHSCPMuonTreeProducer::doMC(const edm::Event& iEvent) {

  edm::Handle<edm::HepMCProduct> mcHandle;
  iEvent.getByLabel(mcTag_,mcHandle);
  
  if (mcHandle.isValid()) {
    
    const edm::HepMCProduct *mcProd = mcHandle.product();
    const HepMC::GenEvent *evt = mcProd->GetEvent();
    
    for(HepMC::GenEvent::vertex_const_iterator pitr = evt->vertices_begin();
	pitr!= evt->vertices_end();
	++pitr) {
      
      if((*pitr)->barcode()==-1)  {

	event_->rHadVtxX = (*pitr)->point3d().x();
	event_->rHadVtxY = (*pitr)->point3d().y();
	event_->rHadVtxZ = (*pitr)->point3d().z();
	event_->rHadVtxT = (*pitr)->position().t();
	
	for(HepMC::GenVertex::particles_out_const_iterator part = (*pitr)->particles_out_const_begin();
	    part!=(*pitr)->particles_out_const_end(); 
	    ++part) {

	  if((*part)->pdg_id()>=1000000)
	    {
	      event_->rHadPdgId = (*part)->pdg_id();
	      event_->rHadPx  = (*part)->momentum().x();
	      event_->rHadPy  = (*part)->momentum().y();
	      event_->rHadPz  = (*part)->momentum().z();
	      event_->rHadPt  = (*part)->momentum().perp();
	      event_->rHadE   = (*part)->momentum().e();

	    }
	}
	
      }
    }
    
  }
  else {
    if (!mcMissing_) edm::LogWarning("MissingProduct") << "MC information not found.  Branch will not be filled" << std::endl;
    mcMissing_ = true;
  }

  // Now fill variables based on the StoppedParticles vectors made by RHStopTracer module
  edm::Handle<std::vector<std::string> > names;
  iEvent.getByLabel (mcProducer_, "StoppedParticlesName", names);
  edm::Handle<std::vector<float> > xs;
  iEvent.getByLabel (mcProducer_, "StoppedParticlesX", xs);
  edm::Handle<std::vector<float> > ys;
  iEvent.getByLabel (mcProducer_, "StoppedParticlesY", ys);
  edm::Handle<std::vector<float> > zs;
  iEvent.getByLabel (mcProducer_, "StoppedParticlesZ", zs);
  edm::Handle<std::vector<float> > times;
  iEvent.getByLabel (mcProducer_, "StoppedParticlesTime", times);
  if (!names.isValid() || !xs.isValid() || !ys.isValid() || !zs.isValid() || !times.isValid()){
    edm::LogError ("MissingProduct") << "StoppedParticles* vectors not available. Branch "
				     << "will not be filled." << std::endl;
  } else if (names->size() != xs->size() || xs->size() != ys->size() || ys->size() != zs->size()) {
    edm::LogError ("StoppedHSCPMuonTreeProducer") << "mismatch array sizes name/x/y/z:"
					      << names->size() << '/' << xs->size() << '/' 
					      << ys->size() << '/' << zs->size() << std::endl;
  } else {
    if (names->size() > 0) {
      for (size_t i = 0; i < names->size(); ++i) {
	float phi = ((*ys)[i]==0 && (*xs)[i]==0) ? 0 : atan2((*ys)[i],(*xs)[i]);
	
	// TODO: find a way to get the pdgid, mass, and charge of the stopped particle 
	// (the name is not in the ParticleDataTable)
	Double_t mass = -1.0;
	Double_t charge = 99.0;
	Int_t pdgid = 0;
	const HepPDT::ParticleData* PData = fPDGTable->particle(names->at(i));
	if (PData == 0) {
	  LogDebug ("StoppedHSCPMuonTreeProducer") << "could not get particle data from the"
					       << " table for " << names->at(i)
					       << std::endl;
	} else {
	  mass = PData->mass();
	  charge = PData->charge();
	  pdgid = PData->ID().pid();
	}
	event_->mcStoppedParticleName.push_back(names->at(i));
	event_->mcStoppedParticleId.push_back(pdgid);
	event_->mcStoppedParticleX.push_back(xs->at(i));
	event_->mcStoppedParticleY.push_back(ys->at(i));
	event_->mcStoppedParticleZ.push_back(zs->at(i));
	event_->mcStoppedParticleR.push_back(sqrt(xs->at(i)*xs->at(i) + ys->at(i)*ys->at(i)));
	event_->mcStoppedParticlePhi.push_back(phi);
	event_->mcStoppedParticleTime.push_back(times->at(i));
	event_->mcStoppedParticle_N++;
      }
    }
  }

  // Search the stage 1 HepMC records for the initial SUSY particle (gluino, stop, stau...)
  // and for the initial R-hadrons
  //edm::Handle<reco::GenParticleCollection> genParticles;
  //iEvent.getByLabel(genParticlesTag_, genParticles);

  edm::Handle<edm::HepMCProduct> hepMCproduct;
  iEvent.getByLabel(hepProducer_, hepMCproduct);
  if (!hepMCproduct.isValid()) {
    edm::LogError ("MissingProduct") << "Stage 1 HepMC product not found. Branch "
				     << "will not be filled." << std::endl;
  }
  else {
    const HepMC::GenEvent* mc = hepMCproduct->GetEvent();
    if( mc == 0 ) {
      throw edm::Exception( edm::errors::InvalidReference ) << "HepMC has null pointer "
							    << "to GenEvent" << std::endl;
    }
    // Uncomment this to print the full HepMC record for each event (for debugging or whatever)
    //mc->print( std::cout );
    
    /*
    //print full HepMC record for each event that has a muon in it
    bool muon_present = false;
    for ( HepMC::GenEvent::particle_const_iterator piter  = mc->particles_begin();
	  piter != mc->particles_end(); 
	  ++piter ) {
      HepMC::GenParticle* p = *piter;
      int partId = fabs(p->pdg_id());
      if (TMath::Abs(partId) == 13) muon_present = true;
    }
    if(muon_present) mc->print( std::cout );
    */

    int index = 0;
    // Iterate over the HepMC particles, look for the sparticles that produce r-hadrons,
    for ( HepMC::GenEvent::particle_const_iterator piter  = mc->particles_begin();
	  piter != mc->particles_end(); 
	  ++piter ) {
      HepMC::GenParticle* p = *piter;
      //reco::GenParticle* p_reco = *piter;
      int partId = fabs(p->pdg_id());
      
      math::XYZTLorentzVector momentum1(p->momentum().px(),
					p->momentum().py(),
					p->momentum().pz(),
					p->momentum().e());
      Double_t phi = momentum1.phi();
      Double_t pt = momentum1.pt();
      Double_t e = momentum1.e();
      Double_t eta = momentum1.eta();
      Double_t mass = p->momentum().m();
      Double_t charge = 999.0;
      const HepPDT::ParticleData* PData = fPDGTable->particle(HepPDT::ParticleID(p->pdg_id()));
      if(PData==0) {
	LogDebug ("StoppedHSCPMuonTreeProducer") << "Error getting HepPDT data table for "
						 << p->pdg_id() << ". Unable to fill charge "
						 << "of sparticle." << std::endl;
      } else {
	charge = PData->charge();
      }
      /*
      event_->mcGenParticleId.push_back(p->pdg_id());
      event_->mcGenParticleMass.push_back(mass);
      event_->mcGenParticleCharge.push_back(charge);
      event_->mcGenParticlePx.push_back(momentum1.x());
      event_->mcGenParticlePy.push_back(momentum1.y());
      event_->mcGenParticlePz.push_back(momentum1.z());
      event_->mcGenParticlePt.push_back(pt);
      event_->mcGenParticleE.push_back(e);
      event_->mcGenParticleEta.push_back(eta);
      event_->mcGenParticlePhi.push_back(phi);
      event_->mcGenParticleStatus.push_back(p->status());
      //int motherId = -1;
      //if(p_reco->mother()) motherId = p_reco->mother()->pdgId();
      //event_->mcGenParticleNMothers.push_back(p_reco->numberOfMothers());
      //event_->mcGenParticleNDaughters.push_back(p_reco->numberOfDaughters());
      event_->mcGenParticle_N++;
      */

      //std::cout<<"for HepMC gen part "<<index<<", pid is: "<<p->pdg_id()<<", pt is: "<<pt<<", eta is: "<<eta<<", phi is: "<<phi<<std::endl;

      //if (!genParticles.isValid()) {
      //edm::LogError ("MissingProduct") << "Stage 1 Gen particle collection not found. Branch "
      //				 << "will not be filled." << std::endl;
      //}
      //else {
      //for(size_t i=0; i<genParticles->size(); i++){
      //const reco::GenParticle & p_reco = (*genParticles)[i];
      //if((p->pdg_id()==p_reco.pdgId()) && (pt+5>p_reco.pt() && p_reco.pt()>pt-5) && (eta+0.5>p_reco.eta() && p_reco.eta()>eta-0.5) && (phi+0.5>p_reco.phi() && p_reco.phi()>phi-0.5)){
      //std::cout<<"  for MATCHED reco gen part "<<i<<", pid is: "<<p_reco.pdgId()<<", pt is: "<<p_reco.pt()<<", eta is: "<<p_reco.eta()<<", phi is: "<<p_reco.phi()<<std::endl;
      //  }

      //}//end of loop over gen particles
      //}




      // Search for the original sparticle (gluino, stop - left and right handed, stau)
      // -- Assumes the first two sparticles found are the correct ones to save.
      if ((partId == 1000021 || partId == 1000006 || partId == 2000006 || partId == 1000015 
	   || partId == 2000015) && event_->mcSparticle_N < 2) {
	math::XYZTLorentzVector momentum1(p->momentum().px(),
					  p->momentum().py(),
					  p->momentum().pz(),
					  p->momentum().e());
	Double_t phi = momentum1.phi();
	Double_t pt = momentum1.pt();
	Double_t e = momentum1.e();
	Double_t eta = momentum1.eta();
	Double_t mass = p->momentum().m();
	Double_t charge = 999.0;
	const HepPDT::ParticleData* PData = fPDGTable->particle(HepPDT::ParticleID(p->pdg_id()));
	if(PData==0) {
	  LogDebug ("StoppedHSCPMuonTreeProducer") << "Error getting HepPDT data table for "
					       << p->pdg_id() << ". Unable to fill charge "
					       << "of sparticle." << std::endl;
	} else {
	  charge = PData->charge();
	}
	event_->mcSparticleId.push_back(p->pdg_id());
	event_->mcSparticleMass.push_back(mass);
	event_->mcSparticleCharge.push_back(charge);
	event_->mcSparticlePx.push_back(momentum1.x());
	event_->mcSparticlePy.push_back(momentum1.y());
	event_->mcSparticlePz.push_back(momentum1.z());
	event_->mcSparticlePt.push_back(pt);
	event_->mcSparticleE.push_back(e);
	event_->mcSparticleEta.push_back(eta);
	event_->mcSparticlePhi.push_back(phi);
	event_->mcSparticle_N++;
      }
    
      // I'm making the (possibly invalid) assumption here that R-hadrons all have numbers 
      // between the SUSY particles and 2,000,000. 
      // -- Assumes the first two r-hadrons we come across are the ones we want.
      // -- This branch may not be filled for stau MC.
      else if (partId > 1000100 && partId < 2000000 && event_->mcRhadron_N < 2) {
	math::XYZTLorentzVector momentum1(p->momentum().px(),
					  p->momentum().py(),
					  p->momentum().pz(),
					  p->momentum().e());
	Double_t phi = momentum1.phi();
	Double_t pt = momentum1.pt();
	Double_t e = momentum1.e();
	Double_t eta = momentum1.eta();
	Double_t mass = p->momentum().m();
	Double_t charge = 999.0;
	const HepPDT::ParticleData* PData = fPDGTable->particle(HepPDT::ParticleID(p->pdg_id()));
	if(PData==0) {
	  LogDebug ("StoppedHSCPMuonTreeProducer") << "Error getting HepPDT data table for "
					       << p->pdg_id() << ". Unable to fill charge "
					       << "of rhadron." << std::endl;
	} else {
	  charge = PData->charge();
	}
	event_->mcRhadronId.push_back(p->pdg_id());
	event_->mcRhadronMass.push_back(mass);
	event_->mcRhadronCharge.push_back(charge);
	event_->mcRhadronPx.push_back(momentum1.x());
	event_->mcRhadronPy.push_back(momentum1.y());
	event_->mcRhadronPz.push_back(momentum1.z());
	event_->mcRhadronPt.push_back(pt);
	event_->mcRhadronE.push_back(e);
	event_->mcRhadronEta.push_back(eta);
	event_->mcRhadronPhi.push_back(phi);
	event_->mcRhadron_N++; 
      }

      index++;
    }//end of loop over gen particles
  }

  edm::Handle<reco::GenParticleCollection> genParticles;
  iEvent.getByLabel(genParticlesTag_, genParticles);
  if (!genParticles.isValid()) {
    edm::LogError ("MissingProduct") << "Stage 1 Gen particle collection not found. Branch "
  			     << "will not be filled." << std::endl;
  }
  else {
    std::vector<GenParticle> genParticles_;
    genParticles_.insert(genParticles_.end(), genParticles->begin(), genParticles->end());
    std::sort(genParticles_.begin(), genParticles_.end(), genParticle_pt());

    for(size_t i=0; i<genParticles_.size(); i++){
      const reco::GenParticle & p = genParticles_.at(i);
      //std::cout<<"for reco gen part "<<i<<", pid is: "<<p.pdgId()<<", pt is: "<<p.pt()<<", eta is: "<<p.eta()<<", phi is: "<<p.phi()<<std::endl;

      Double_t charge_ = 999.0;
      const HepPDT::ParticleData* PData_ = fPDGTable->particle(HepPDT::ParticleID(p.pdgId()));
      if(PData_==0) {
	LogDebug ("StoppedHSCPMuonTreeProducer") << "Error getting HepPDT data table for "
						 << p.pdgId() << ". Unable to fill charge "<< std::endl;
      } else {
	charge_ = PData_->charge();
      }
      
      std::vector<int> daughterId_;
      std::vector<int> daughterStatus_;
      for(size_t j=0; j<p.numberOfDaughters(); j++){
	const reco::Candidate* daughter_ = p.daughter(j);
	daughterId_.push_back(daughter_->pdgId());
	daughterStatus_.push_back(daughter_->status());
      }
      int motherId_ = -999;
      if(p.mother()){
	const reco::Candidate* mother_ = p.mother();
	motherId_ = mother_->pdgId();
      }
	
      event_->mcGenParticleId.push_back(p.pdgId());
      event_->mcGenParticleMass.push_back(p.mass());
      event_->mcGenParticleCharge.push_back(charge_);
      event_->mcGenParticlePx.push_back(p.px());
      event_->mcGenParticlePy.push_back(p.py());
      event_->mcGenParticlePz.push_back(p.pz());
      event_->mcGenParticlePt.push_back(p.pt());
      event_->mcGenParticleP.push_back(p.p());
      event_->mcGenParticleEta.push_back(p.eta());
      event_->mcGenParticlePhi.push_back(p.phi());
      event_->mcGenParticleStatus.push_back(p.status());
      event_->mcGenParticleNMothers.push_back(p.numberOfMothers());
      event_->mcGenParticleMotherId.push_back(motherId_);
      event_->mcGenParticleNDaughters.push_back(p.numberOfDaughters());
      event_->mcGenParticleDaughterId.push_back(daughterId_);
      event_->mcGenParticleDaughterStatus.push_back(daughterStatus_);
      event_->mcGenParticleGenIndex.push_back(i);
      event_->mcGenParticle_N++;

      //look at tau prime (doubly charged Higgs)
      if (TMath::Abs(p.pdgId()) == 17) {
	Double_t charge = 999.0;
	const HepPDT::ParticleData* PData = fPDGTable->particle(HepPDT::ParticleID(p.pdgId()));
	if(PData==0) {
	  LogDebug ("StoppedHSCPMuonTreeProducer") << "Error getting HepPDT data table for "
					       << p.pdgId() << ". Unable to fill charge "
					       << "of tauPrime." << std::endl;
	} else {
	  charge = PData->charge();
	}

	std::vector<int> daughterId;
	std::vector<int> daughterStatus;
	for(size_t j=0; j<p.numberOfDaughters(); j++){
	  const reco::Candidate* daughter = p.daughter(j);
	  daughterId.push_back(daughter->pdgId());
	  daughterStatus.push_back(daughter->status());
	}
	const reco::Candidate* mother = p.mother();
	int motherId = -999;
	if(mother) motherId = mother->pdgId();
	event_->mcTauPrimeId.push_back(p.pdgId());
	event_->mcTauPrimeMass.push_back(p.mass());
	event_->mcTauPrimeCharge.push_back(charge);
	event_->mcTauPrimePx.push_back(p.px());
	event_->mcTauPrimePy.push_back(p.py());
	event_->mcTauPrimePz.push_back(p.pz());
	event_->mcTauPrimePt.push_back(p.pt());
	event_->mcTauPrimeP.push_back(p.p());
	event_->mcTauPrimeEta.push_back(p.eta());
	event_->mcTauPrimePhi.push_back(p.phi());
	event_->mcTauPrimeStatus.push_back(p.status());
	event_->mcTauPrimeNMothers.push_back(p.numberOfMothers());
	event_->mcTauPrimeMotherId.push_back(motherId);
	event_->mcTauPrimeNDaughters.push_back(p.numberOfDaughters());
	event_->mcTauPrimeDaughterId.push_back(daughterId);
	event_->mcTauPrimeDaughterStatus.push_back(daughterStatus);
	event_->mcTauPrimeGenIndex.push_back(i);
	event_->mcTauPrime_N++; 
      }

      //look at gluinos
      if (TMath::Abs(p.pdgId()) == 1000021) {
	Double_t charge = 999.0;
	const HepPDT::ParticleData* PData = fPDGTable->particle(HepPDT::ParticleID(p.pdgId()));
	if(PData==0) {
	  LogDebug ("StoppedHSCPMuonTreeProducer") << "Error getting HepPDT data table for "
					       << p.pdgId() << ". Unable to fill charge "
					       << "of gluino." << std::endl;
	} else {
	  charge = PData->charge();
	}

	std::vector<int> daughterId;
	std::vector<int> daughterStatus;
	for(size_t j=0; j<p.numberOfDaughters(); j++){
	  const reco::Candidate* daughter = p.daughter(j);
	  daughterId.push_back(daughter->pdgId());
	  daughterStatus.push_back(daughter->status());
	}
	const reco::Candidate* mother = p.mother();
	int motherId = -999;
	if(mother) motherId = mother->pdgId();
	event_->mcGluinoId.push_back(p.pdgId());
	event_->mcGluinoMass.push_back(p.mass());
	event_->mcGluinoCharge.push_back(charge);
	event_->mcGluinoPx.push_back(p.px());
	event_->mcGluinoPy.push_back(p.py());
	event_->mcGluinoPz.push_back(p.pz());
	event_->mcGluinoPt.push_back(p.pt());
	event_->mcGluinoP.push_back(p.p());
	event_->mcGluinoEta.push_back(p.eta());
	event_->mcGluinoPhi.push_back(p.phi());
	event_->mcGluinoStatus.push_back(p.status());
	event_->mcGluinoNMothers.push_back(p.numberOfMothers());
	event_->mcGluinoMotherId.push_back(motherId);
	event_->mcGluinoNDaughters.push_back(p.numberOfDaughters());
	event_->mcGluinoDaughterId.push_back(daughterId);
	event_->mcGluinoDaughterStatus.push_back(daughterStatus);
	event_->mcGluinoGenIndex.push_back(i);
	event_->mcGluino_N++; 
      }

      //look at staus
      if (TMath::Abs(p.pdgId()) == 1000015) {
	Double_t charge = 999.0;
	const HepPDT::ParticleData* PData = fPDGTable->particle(HepPDT::ParticleID(p.pdgId()));
	if(PData==0) {
	  LogDebug ("StoppedHSCPMuonTreeProducer") << "Error getting HepPDT data table for "
					       << p.pdgId() << ". Unable to fill charge "
					       << "of stau." << std::endl;
	} else {
	  charge = PData->charge();
	}

	std::vector<int> daughterId;
	std::vector<int> daughterStatus;
	for(size_t j=0; j<p.numberOfDaughters(); j++){
	  const reco::Candidate* daughter = p.daughter(j);
	  daughterId.push_back(daughter->pdgId());
	  daughterStatus.push_back(daughter->status());
	}
	const reco::Candidate* mother = p.mother();
	int motherId = -999;
	if(mother) motherId = mother->pdgId();
	event_->mcStauId.push_back(p.pdgId());
	event_->mcStauMass.push_back(p.mass());
	event_->mcStauCharge.push_back(charge);
	event_->mcStauPx.push_back(p.px());
	event_->mcStauPy.push_back(p.py());
	event_->mcStauPz.push_back(p.pz());
	event_->mcStauPt.push_back(p.pt());
	event_->mcStauP.push_back(p.p());
	event_->mcStauEta.push_back(p.eta());
	event_->mcStauPhi.push_back(p.phi());
	event_->mcStauStatus.push_back(p.status());
	event_->mcStauNMothers.push_back(p.numberOfMothers());
	event_->mcStauMotherId.push_back(motherId);
	event_->mcStauNDaughters.push_back(p.numberOfDaughters());
	event_->mcStauDaughterId.push_back(daughterId);
	event_->mcStauDaughterStatus.push_back(daughterStatus);
	event_->mcStauGenIndex.push_back(i);
	event_->mcStau_N++; 
      }

      //look at stops
      if (TMath::Abs(p.pdgId()) == 1000006) {
	Double_t charge = 999.0;
	const HepPDT::ParticleData* PData = fPDGTable->particle(HepPDT::ParticleID(p.pdgId()));
	if(PData==0) {
	  LogDebug ("StoppedHSCPMuonTreeProducer") << "Error getting HepPDT data table for "
					       << p.pdgId() << ". Unable to fill charge "
					       << "of stop." << std::endl;
	} else {
	  charge = PData->charge();
	}

	std::vector<int> daughterId;
	std::vector<int> daughterStatus;
	for(size_t j=0; j<p.numberOfDaughters(); j++){
	  const reco::Candidate* daughter = p.daughter(j);
	  daughterId.push_back(daughter->pdgId());
	  daughterStatus.push_back(daughter->status());
	}
	const reco::Candidate* mother = p.mother();
	int motherId = -999;
	if(mother) motherId = mother->pdgId();
	event_->mcStopId.push_back(p.pdgId());
	event_->mcStopMass.push_back(p.mass());
	event_->mcStopCharge.push_back(charge);
	event_->mcStopPx.push_back(p.px());
	event_->mcStopPy.push_back(p.py());
	event_->mcStopPz.push_back(p.pz());
	event_->mcStopPt.push_back(p.pt());
	event_->mcStopP.push_back(p.p());
	event_->mcStopEta.push_back(p.eta());
	event_->mcStopPhi.push_back(p.phi());
	event_->mcStopStatus.push_back(p.status());
	event_->mcStopNMothers.push_back(p.numberOfMothers());
	event_->mcStopMotherId.push_back(motherId);
	event_->mcStopNDaughters.push_back(p.numberOfDaughters());
	event_->mcStopDaughterId.push_back(daughterId);
	event_->mcStopDaughterStatus.push_back(daughterStatus);
	event_->mcStopGenIndex.push_back(i);
	event_->mcStop_N++; 
      }

      //look at charginos
      if (TMath::Abs(p.pdgId()) == 1000024) {
	Double_t charge = 999.0;
	const HepPDT::ParticleData* PData = fPDGTable->particle(HepPDT::ParticleID(p.pdgId()));
	if(PData==0) {
	  LogDebug ("StoppedHSCPMuonTreeProducer") << "Error getting HepPDT data table for "
					       << p.pdgId() << ". Unable to fill charge "
					       << "of chargino." << std::endl;
	} else {
	  charge = PData->charge();
	}

	std::vector<int> daughterId;
	std::vector<int> daughterStatus;
	for(size_t j=0; j<p.numberOfDaughters(); j++){
	  const reco::Candidate* daughter = p.daughter(j);
	  daughterId.push_back(daughter->pdgId());
	  daughterStatus.push_back(daughter->status());
	}
	const reco::Candidate* mother = p.mother();
	int motherId = -999;
	if(mother) motherId = mother->pdgId();
	event_->mcCharginoId.push_back(p.pdgId());
	event_->mcCharginoMass.push_back(p.mass());
	event_->mcCharginoCharge.push_back(charge);
	event_->mcCharginoPx.push_back(p.px());
	event_->mcCharginoPy.push_back(p.py());
	event_->mcCharginoPz.push_back(p.pz());
	event_->mcCharginoPt.push_back(p.pt());
	event_->mcCharginoP.push_back(p.p());
	event_->mcCharginoEta.push_back(p.eta());
	event_->mcCharginoPhi.push_back(p.phi());
	event_->mcCharginoStatus.push_back(p.status());
	event_->mcCharginoNMothers.push_back(p.numberOfMothers());
	event_->mcCharginoMotherId.push_back(motherId);
	event_->mcCharginoNDaughters.push_back(p.numberOfDaughters());
	event_->mcCharginoDaughterId.push_back(daughterId);
	event_->mcCharginoDaughterStatus.push_back(daughterStatus);
	event_->mcCharginoGenIndex.push_back(i);
	event_->mcChargino_N++; 
      }

      //look at neutralinos
      if (TMath::Abs(p.pdgId()) == 1000022) {
	Double_t charge = 999.0;
	const HepPDT::ParticleData* PData = fPDGTable->particle(HepPDT::ParticleID(p.pdgId()));
	if(PData==0) {
	  LogDebug ("StoppedHSCPMuonTreeProducer") << "Error getting HepPDT data table for "
					       << p.pdgId() << ". Unable to fill charge "
					       << "of neutralino." << std::endl;
	} else {
	  charge = PData->charge();
	}

	std::vector<int> daughterId;
	std::vector<int> daughterStatus;
	for(size_t j=0; j<p.numberOfDaughters(); j++){
	  const reco::Candidate* daughter = p.daughter(j);
	  daughterId.push_back(daughter->pdgId());
	  daughterStatus.push_back(daughter->status());
	}
	const reco::Candidate* mother = p.mother();
	int motherId = -999;
	if(mother) motherId = mother->pdgId();
	event_->mcNeutralinoId.push_back(p.pdgId());
	event_->mcNeutralinoMass.push_back(p.mass());
	event_->mcNeutralinoCharge.push_back(charge);
	event_->mcNeutralinoPx.push_back(p.px());
	event_->mcNeutralinoPy.push_back(p.py());
	event_->mcNeutralinoPz.push_back(p.pz());
	event_->mcNeutralinoPt.push_back(p.pt());
	event_->mcNeutralinoP.push_back(p.p());
	event_->mcNeutralinoEta.push_back(p.eta());
	event_->mcNeutralinoPhi.push_back(p.phi());
	event_->mcNeutralinoStatus.push_back(p.status());
	event_->mcNeutralinoNMothers.push_back(p.numberOfMothers());
	event_->mcNeutralinoMotherId.push_back(motherId);
	event_->mcNeutralinoNDaughters.push_back(p.numberOfDaughters());
	event_->mcNeutralinoDaughterId.push_back(daughterId);
	event_->mcNeutralinoDaughterStatus.push_back(daughterStatus);
	event_->mcNeutralinoGenIndex.push_back(i);
	event_->mcNeutralino_N++; 
      }

      //look at gravitinos
      if (TMath::Abs(p.pdgId()) == 1000039) {
	Double_t charge = 999.0;
	const HepPDT::ParticleData* PData = fPDGTable->particle(HepPDT::ParticleID(p.pdgId()));
	if(PData==0) {
	  LogDebug ("StoppedHSCPMuonTreeProducer") << "Error getting HepPDT data table for "
					       << p.pdgId() << ". Unable to fill charge "
					       << "of gravitino." << std::endl;
	} else {
	  charge = PData->charge();
	}

	std::vector<int> daughterId;
	std::vector<int> daughterStatus;
	for(size_t j=0; j<p.numberOfDaughters(); j++){
	  const reco::Candidate* daughter = p.daughter(j);
	  daughterId.push_back(daughter->pdgId());
	  daughterStatus.push_back(daughter->status());
	}
	const reco::Candidate* mother = p.mother();
	int motherId = -999;
	if(mother) motherId = mother->pdgId();
	event_->mcGravitinoId.push_back(p.pdgId());
	event_->mcGravitinoMass.push_back(p.mass());
	event_->mcGravitinoCharge.push_back(charge);
	event_->mcGravitinoPx.push_back(p.px());
	event_->mcGravitinoPy.push_back(p.py());
	event_->mcGravitinoPz.push_back(p.pz());
	event_->mcGravitinoPt.push_back(p.pt());
	event_->mcGravitinoP.push_back(p.p());
	event_->mcGravitinoEta.push_back(p.eta());
	event_->mcGravitinoPhi.push_back(p.phi());
	event_->mcGravitinoStatus.push_back(p.status());
	event_->mcGravitinoNMothers.push_back(p.numberOfMothers());
	event_->mcGravitinoMotherId.push_back(motherId);
	event_->mcGravitinoNDaughters.push_back(p.numberOfDaughters());
	event_->mcGravitinoDaughterId.push_back(daughterId);
	event_->mcGravitinoDaughterStatus.push_back(daughterStatus);
	event_->mcGravitinoGenIndex.push_back(i);
	event_->mcGravitino_N++; 
      }

      //look at muon neutrinos
      if (TMath::Abs(p.pdgId()) == 14) {
	Double_t charge = 999.0;
	const HepPDT::ParticleData* PData = fPDGTable->particle(HepPDT::ParticleID(p.pdgId()));
	if(PData==0) {
	  LogDebug ("StoppedHSCPMuonTreeProducer") << "Error getting HepPDT data table for "
					       << p.pdgId() << ". Unable to fill charge "
					       << "of neutrino." << std::endl;
	} else {
	  charge = PData->charge();
	}

	std::vector<int> daughterId;
	std::vector<int> daughterStatus;
	for(size_t j=0; j<p.numberOfDaughters(); j++){
	  const reco::Candidate* daughter = p.daughter(j);
	  daughterId.push_back(daughter->pdgId());
	  daughterStatus.push_back(daughter->status());
	}
	const reco::Candidate* mother = p.mother();
	int motherId = -999;
	if(mother) motherId = mother->pdgId();
	event_->mcNeutrinoId.push_back(p.pdgId());
	event_->mcNeutrinoMass.push_back(p.mass());
	event_->mcNeutrinoCharge.push_back(charge);
	event_->mcNeutrinoPx.push_back(p.px());
	event_->mcNeutrinoPy.push_back(p.py());
	event_->mcNeutrinoPz.push_back(p.pz());
	event_->mcNeutrinoPt.push_back(p.pt());
	event_->mcNeutrinoP.push_back(p.p());
	event_->mcNeutrinoEta.push_back(p.eta());
	event_->mcNeutrinoPhi.push_back(p.phi());
	event_->mcNeutrinoStatus.push_back(p.status());
	event_->mcNeutrinoNMothers.push_back(p.numberOfMothers());
	event_->mcNeutrinoMotherId.push_back(motherId);
	event_->mcNeutrinoNDaughters.push_back(p.numberOfDaughters());
	event_->mcNeutrinoDaughterId.push_back(daughterId);
	event_->mcNeutrinoDaughterStatus.push_back(daughterStatus);
	event_->mcNeutrinoGenIndex.push_back(i);
	event_->mcNeutrino_N++; 
      }

      //look at tops
      if (TMath::Abs(p.pdgId()) == 6) {
	Double_t charge = 999.0;
	const HepPDT::ParticleData* PData = fPDGTable->particle(HepPDT::ParticleID(p.pdgId()));
	if(PData==0) {
	  LogDebug ("StoppedHSCPMuonTreeProducer") << "Error getting HepPDT data table for "
					       << p.pdgId() << ". Unable to fill charge "
					       << "of top." << std::endl;
	} else {
	  charge = PData->charge();
	}

	std::vector<int> daughterId;
	std::vector<int> daughterStatus;
	for(size_t j=0; j<p.numberOfDaughters(); j++){
	  const reco::Candidate* daughter = p.daughter(j);
	  daughterId.push_back(daughter->pdgId());
	  daughterStatus.push_back(daughter->status());
	}
	const reco::Candidate* mother = p.mother();
	int motherId = -999;
	if(mother) motherId = mother->pdgId();
	event_->mcTopId.push_back(p.pdgId());
	event_->mcTopMass.push_back(p.mass());
	event_->mcTopCharge.push_back(charge);
	event_->mcTopPx.push_back(p.px());
	event_->mcTopPy.push_back(p.py());
	event_->mcTopPz.push_back(p.pz());
	event_->mcTopPt.push_back(p.pt());
	event_->mcTopP.push_back(p.p());
	event_->mcTopEta.push_back(p.eta());
	event_->mcTopPhi.push_back(p.phi());
	event_->mcTopStatus.push_back(p.status());
	event_->mcTopNMothers.push_back(p.numberOfMothers());
	event_->mcTopMotherId.push_back(motherId);
	event_->mcTopNDaughters.push_back(p.numberOfDaughters());
	event_->mcTopDaughterId.push_back(daughterId);
	event_->mcTopDaughterStatus.push_back(daughterStatus);
	event_->mcTopGenIndex.push_back(i);
	event_->mcTop_N++; 

      }

      //look at Ws
      if (TMath::Abs(p.pdgId()) == 24) {
	Double_t charge = 999.0;
	const HepPDT::ParticleData* PData = fPDGTable->particle(HepPDT::ParticleID(p.pdgId()));
	if(PData==0) {
	  LogDebug ("StoppedHSCPMuonTreeProducer") << "Error getting HepPDT data table for "
					       << p.pdgId() << ". Unable to fill charge "
					       << "of W." << std::endl;
	} else {
	  charge = PData->charge();
	}

	std::vector<int> daughterId;
	std::vector<int> daughterStatus;
	for(size_t j=0; j<p.numberOfDaughters(); j++){
	  const reco::Candidate* daughter = p.daughter(j);
	  daughterId.push_back(daughter->pdgId());
	  daughterStatus.push_back(daughter->status());
	}
	const reco::Candidate* mother = p.mother();
	int motherId = -999;
	if(mother) motherId = mother->pdgId();
	event_->mcWId.push_back(p.pdgId());
	event_->mcWMass.push_back(p.mass());
	event_->mcWCharge.push_back(charge);
	event_->mcWPx.push_back(p.px());
	event_->mcWPy.push_back(p.py());
	event_->mcWPz.push_back(p.pz());
	event_->mcWPt.push_back(p.pt());
	event_->mcWP.push_back(p.p());
	event_->mcWEta.push_back(p.eta());
	event_->mcWPhi.push_back(p.phi());
	event_->mcWStatus.push_back(p.status());
	event_->mcWNMothers.push_back(p.numberOfMothers());
	event_->mcWMotherId.push_back(motherId);
	event_->mcWNDaughters.push_back(p.numberOfDaughters());
	event_->mcWDaughterId.push_back(daughterId);
	event_->mcWDaughterStatus.push_back(daughterStatus);
	event_->mcWGenIndex.push_back(i);
	event_->mcW_N++; 

      }

      //look at CMshowers
      if (TMath::Abs(p.pdgId()) == 94) {
	Double_t charge = 999.0;
	const HepPDT::ParticleData* PData = fPDGTable->particle(HepPDT::ParticleID(p.pdgId()));
	if(PData==0) {
	  LogDebug ("StoppedHSCPMuonTreeProducer") << "Error getting HepPDT data table for "
					       << p.pdgId() << ". Unable to fill charge "
					       << "of CM shower" << std::endl;
	} else {
	  charge = PData->charge();
	}

	std::vector<int> daughterId;
	std::vector<int> daughterStatus;
	for(size_t j=0; j<p.numberOfDaughters(); j++){
	  const reco::Candidate* daughter = p.daughter(j);
	  daughterId.push_back(daughter->pdgId());
	  daughterStatus.push_back(daughter->status());
	}
	const reco::Candidate* mother = p.mother();
	int motherId = -999;
	if(mother) motherId = mother->pdgId();
	event_->mcCMshowerId.push_back(p.pdgId());
	event_->mcCMshowerMass.push_back(p.mass());
	event_->mcCMshowerCharge.push_back(charge);
	event_->mcCMshowerPx.push_back(p.px());
	event_->mcCMshowerPy.push_back(p.py());
	event_->mcCMshowerPz.push_back(p.pz());
	event_->mcCMshowerPt.push_back(p.pt());
	event_->mcCMshowerP.push_back(p.p());
	event_->mcCMshowerEta.push_back(p.eta());
	event_->mcCMshowerPhi.push_back(p.phi());
	event_->mcCMshowerStatus.push_back(p.status());
	event_->mcCMshowerNMothers.push_back(p.numberOfMothers());
	event_->mcCMshowerMotherId.push_back(motherId);
	event_->mcCMshowerNDaughters.push_back(p.numberOfDaughters());
	event_->mcCMshowerDaughterId.push_back(daughterId);
	event_->mcCMshowerDaughterStatus.push_back(daughterStatus);
	event_->mcCMshowerGenIndex.push_back(i);
	event_->mcCMshower_N++; 

      }

      //look at taus
      if (TMath::Abs(p.pdgId()) == 15) {
	Double_t charge = 999.0;
	const HepPDT::ParticleData* PData = fPDGTable->particle(HepPDT::ParticleID(p.pdgId()));
	if(PData==0) {
	  LogDebug ("StoppedHSCPMuonTreeProducer") << "Error getting HepPDT data table for "
					       << p.pdgId() << ". Unable to fill charge "
					       << "of CM shower" << std::endl;
	} else {
	  charge = PData->charge();
	}

	std::vector<int> daughterId;
	std::vector<int> daughterStatus;
	for(size_t j=0; j<p.numberOfDaughters(); j++){
	  const reco::Candidate* daughter = p.daughter(j);
	  daughterId.push_back(daughter->pdgId());
	  daughterStatus.push_back(daughter->status());
	}
	const reco::Candidate* mother = p.mother();
	int motherId = -999;
	if(mother) motherId = mother->pdgId();
	event_->mcTauId.push_back(p.pdgId());
	event_->mcTauMass.push_back(p.mass());
	event_->mcTauCharge.push_back(charge);
	event_->mcTauPx.push_back(p.px());
	event_->mcTauPy.push_back(p.py());
	event_->mcTauPz.push_back(p.pz());
	event_->mcTauPt.push_back(p.pt());
	event_->mcTauP.push_back(p.p());
	event_->mcTauEta.push_back(p.eta());
	event_->mcTauPhi.push_back(p.phi());
	event_->mcTauStatus.push_back(p.status());
	event_->mcTauNMothers.push_back(p.numberOfMothers());
	event_->mcTauMotherId.push_back(motherId);
	event_->mcTauNDaughters.push_back(p.numberOfDaughters());
	event_->mcTauDaughterId.push_back(daughterId);
	event_->mcTauDaughterStatus.push_back(daughterStatus);
	event_->mcTauGenIndex.push_back(i);
	event_->mcTau_N++; 

      }

      //look at muons
      if (TMath::Abs(p.pdgId()) == 13) {

	//Double_t mass = p->momentum().m();
	Double_t charge = 999.0;
	const HepPDT::ParticleData* PData = fPDGTable->particle(HepPDT::ParticleID(p.pdgId()));
	if(PData==0) {
	  LogDebug ("StoppedHSCPMuonTreeProducer") << "Error getting HepPDT data table for "
					       << p.pdgId() << ". Unable to fill charge "
					       << "of muon." << std::endl;
	} else {
	  charge = PData->charge();
	}

	std::vector<int> daughterId;
	std::vector<int> daughterStatus;
	for(size_t j=0; j<p.numberOfDaughters(); j++){
	  const reco::Candidate* daughter = p.daughter(j);
	  daughterId.push_back(daughter->pdgId());
	  daughterStatus.push_back(daughter->status());
	}
	const reco::Candidate* mother = p.mother();
	int motherId = -999;
	if(mother) motherId = mother->pdgId();
	std::cout<<"muon status is: "<<p.status()<<", pt is: "<<p.pt()<<", eta is: "<<p.eta()<<", phi is: "<<p.phi()<<std::endl;
	std::cout<<"mother of muon is: "<<motherId<<std::endl;
	event_->mcMuonId.push_back(p.pdgId());
	event_->mcMuonMass.push_back(p.mass());
	event_->mcMuonCharge.push_back(charge);
	event_->mcMuonPx.push_back(p.px());
	event_->mcMuonPy.push_back(p.py());
	event_->mcMuonPz.push_back(p.pz());
	event_->mcMuonPt.push_back(p.pt());
	event_->mcMuonP.push_back(p.p());
	event_->mcMuonEta.push_back(p.eta());
	event_->mcMuonPhi.push_back(p.phi());
	event_->mcMuonStatus.push_back(p.status());
	event_->mcMuonNMothers.push_back(p.numberOfMothers());
	event_->mcMuonMotherId.push_back(motherId);
	event_->mcMuonNDaughters.push_back(p.numberOfDaughters());
	event_->mcMuonDaughterId.push_back(daughterId);
	event_->mcMuonDaughterStatus.push_back(daughterStatus);
	event_->mcMuonGenIndex.push_back(i);
	event_->mcMuon_N++; 

	if(mother->mother()){
	  const reco::Candidate* mother2 = mother->mother();
	  int motherId2 = -999;
	  if(mother2) motherId2 = mother2->pdgId();
	  std::cout<<"mother of mother of muon is: "<<motherId2<<std::endl;

	  if(mother2->mother()){
	    const reco::Candidate* mother3 = mother2->mother();
	    int motherId3 = -999;
	    if(mother3) motherId3 = mother3->pdgId();
	    std::cout<<"mother of mother of mother of muon is: "<<motherId3<<std::endl;

	    if(mother3->mother()){
	      const reco::Candidate* mother4 = mother3->mother();
	      int motherId4 = -999;
	      if(mother4) motherId4 = mother4->pdgId();
	      std::cout<<"mother of mother of mother of mother of muon is: "<<motherId4<<std::endl;

	      if(mother4->mother()){
		const reco::Candidate* mother5 = mother4->mother();
		int motherId5 = -999;
		if(mother5) motherId5 = mother5->pdgId();
		std::cout<<"mother of mother of mother of mother of mother of muon is: "<<motherId5<<std::endl;

		if(mother5->mother()){
		  const reco::Candidate* mother6 = mother5->mother();
		  int motherId6 = -999;
		  if(mother6) motherId6 = mother6->pdgId();
		  std::cout<<"mother of mother of mother of mother of mother of mother of muon is: "<<motherId6<<std::endl;

		  if(mother6->mother()){
		    const reco::Candidate* mother7 = mother6->mother();
		    int motherId7 = -999;
		    if(mother7) motherId7 = mother7->pdgId();
		    std::cout<<"mother of mother of mother of mother of mother of mother of mother of muon is: "<<motherId7<<std::endl;

		    if(mother7->mother()){
		      const reco::Candidate* mother8 = mother7->mother();
		      int motherId8 = -999;
		      if(mother8) motherId8 = mother8->pdgId();
		      std::cout<<"mother of mother of mother of mother of mother of mother of mother of mother of muon is: "<<motherId8<<std::endl;

		      if(mother8->mother()){
			const reco::Candidate* mother9 = mother8->mother();
			int motherId9 = -999;
			if(mother9) motherId9 = mother9->pdgId();
			std::cout<<"mother of mother of mother of mother of mother of mother of mother of mother of mother of muon is: "<<motherId9<<std::endl;

			if(mother9->mother()){
			  const reco::Candidate* mother10 = mother9->mother();
			  int motherId10 = -999;
			  if(mother10) motherId10 = mother10->pdgId();
			  std::cout<<"mother of mother of mother of mother of mother of mother of mother of mother of mother of mother of muon is: "<<motherId10<<std::endl;
			  
			  if(mother10->mother()){
			    const reco::Candidate* mother11 = mother10->mother();
			    int motherId11 = -999;
			    if(mother11) motherId11 = mother11->pdgId();
			    std::cout<<"mother of mother of mother of mother of mother of mother of mother of mother of mother of mother of mother of muon is: "<<motherId11<<std::endl;
			  }
			}
		      }
		    }
		  }
		}
	      }
	    }
	  }
	}

	int mother_of_W_Id = -999;
	int mother_of_Z_Id = -999;
	//muons from Ws
	if(TMath::Abs(motherId)==24){
	  const reco::Candidate* mother_of_W = mother->mother();
	  if(mother_of_W) mother_of_W_Id = mother_of_W->pdgId();
	}
	event_->mcMuonMotherOfWId.push_back(mother_of_W_Id);

	//muons from Zs
	if(TMath::Abs(motherId)==23){
	  const reco::Candidate* mother_of_Z = mother->mother();
	  if(mother_of_Z) mother_of_Z_Id = mother_of_Z->pdgId();
	}
	event_->mcMuonMotherOfZId.push_back(mother_of_Z_Id);

      }

    }//end of loop over gen particles
  }

}

void StoppedHSCPMuonTreeProducer::doEventInfo(const edm::Event& iEvent) {

  unsigned long orbitsPerLB = 1<<18;
  unsigned long bxPerOrbit  = 3564;
  unsigned long nsPerBx     = 25;

  unsigned long id          = iEvent.id().event();
  unsigned long bx          = iEvent.bunchCrossing();
  unsigned long orbit       = iEvent.orbitNumber();
  unsigned long lb          = iEvent.luminosityBlock();
  unsigned long run         = iEvent.id().run();
  unsigned long fill        = fills_.getFillFromRun(run);

  double time               = iEvent.time().value();


  // calculate event time from run start + LS, orbit, BX
  ULong64_t bxSinceRunStart = (((lb * orbitsPerLB) + orbit) * bxPerOrbit) + bx;
  

  // find last/next collisions
  int bxAfter = 9999;
  int bxBefore = -9999;
  
  if (! isMC_) {
    int bxLast=-1;
    int bxNext=-1;
    if (currentColls_.size() > 0) {
      // special case if event is before first collision
      if (bx <= currentColls_.at(0)) {
	bxLast   = currentColls_.at(currentColls_.size() - 1);
	bxNext   = currentColls_.at(0);
	bxAfter  = (bx + bxPerOrbit) - bxLast;
	bxBefore = bx - bxNext;	
	//std::cout << bx << " : " << bxLast << " : " << bxNext << " : " << bxAfter << " : " << bxBefore << std::endl;
      }

      // special case if event is after last collision
      else if (bx > currentColls_.at(currentColls_.size() - 1)) {
	bxLast   = currentColls_.at(currentColls_.size()-1);
	bxNext   = currentColls_.at(0);
	bxAfter  = bx - bxLast;
	bxBefore = (bx - bxPerOrbit) - bxNext;
	//std::cout << bx << " : " << bxLast << " : " << bxNext << " : " << bxAfter << " : " << bxBefore << std::endl;
      }

      // general case
      else {      
	for (unsigned c=0; c<(currentColls_.size()-1) && currentColls_.at(c)<bx; ++c) {
	  bxLast = currentColls_.at(c);
	  bxNext = currentColls_.at(c+1);
	  bxAfter = bx - bxLast;
	  bxBefore = bx - bxNext;
	  //std::cout << bx << " : " << bxLast << " : " << bxNext << " : " << bxAfter << " : " << bxBefore << std::endl;
	}
      }
    }
    
  }

  // compute relative BX
  int bxWrt    = ( abs(bxAfter) <= abs(bxBefore) ? bxAfter : bxBefore );

  // find last/next bunch
  int bxAfterBunch = 9999;
  int bxBeforeBunch = -9999;
  
  if (! isMC_) {
    int bxLast=-1;
    int bxNext=-1;
    if (currentBunches_.size() > 0) {
      // special case if event is before first collision
      if (bx <= currentBunches_.at(0)) {
	bxLast   = currentBunches_.at(currentBunches_.size() - 1);
	bxNext   = currentBunches_.at(0);
	bxAfterBunch  = (bx + bxPerOrbit) - bxLast;
	bxBeforeBunch = bx - bxNext;
	
	//std::cout << bx << " : " << bxLast << " : " << bxNext << " : " << bxAfter << " : " << bxBefore << std::endl;

      }
      // special case if event is after last collision
      else if (bx > currentBunches_.at(currentBunches_.size() - 1)) {
	bxLast   = currentBunches_.at(currentBunches_.size()-1);
	bxNext   = currentBunches_.at(0);
	bxAfterBunch  = bx - bxLast;
	bxBeforeBunch = (bx - bxPerOrbit) - bxNext;

	//	std::cout << bx << " : " << bxLast << " : " << bxNext << " : " << bxAfter << " : " << bxBefore << std::endl;
      }
      // general case
      else {      
	for (unsigned c=0; c<(currentBunches_.size()-1) && currentBunches_.at(c)<bx; ++c) {
	  bxLast = currentBunches_.at(c);
	  bxNext = currentBunches_.at(c+1);
	  bxAfterBunch = bx - bxLast;
	  bxBeforeBunch = bx - bxNext;
	}
      }
    }
    
  }

  // compute relative BX
  int bxWrtBunch    = ( abs(bxAfterBunch) <= abs(bxBeforeBunch) ? bxAfterBunch : bxBeforeBunch );
  
  //std::cout << "bxAfterCollision = " << bxAfter
  //        <<"\nbxBeforeCollision = "<< bxBefore
  //        <<"\nbxWrtCollision = "<< bxWrt
  //        <<"\nbxAfterBunch = "<< bxAfterBunch
  //        <<"\nbxBeforeBunch = "<< bxBeforeBunch
  //        <<"\nbxWrtBunch = "<< bxWrtBunch
  //        << std::endl;
  
  // set variables in ntuple
  event_->id = id;
  event_->bx = bx;
  event_->orbit = orbit;
  event_->lb = lb;
  event_->run = run;
  event_->fill = fill;
  event_->fillFromL1 = currentFillL1_;
  event_->time = time;
  event_->time2 = iEvent.getRun().beginTime().value() + (bxSinceRunStart * nsPerBx);  // value() in nanoseconds!?!
  event_->bxAfterCollision = bxAfter;
  event_->bxBeforeCollision = bxBefore;
  event_->bxWrtCollision = bxWrt;
  event_->bxAfterBunch = bxAfterBunch;
  event_->bxBeforeBunch = bxBeforeBunch;
  event_->bxWrtBunch = bxWrtBunch;

  // Get luminosity and intensity info from LumiDetails.
  // NOTE: luminosity values are calibrated but uncorrected
  // see also: https://twiki.cern.ch/twiki/bin/view/CMS/LumiCalc#LumiDetails
  edm::Handle<LumiDetails> lumiDetails;
  iEvent.getLuminosityBlock().getByLabel("lumiProducer",lumiDetails);
  
  if (!lumiDetails.isValid()){
    edm::LogError("MissingProduct") << "Could not retreive LumiDetails collection for "
				    << event_->run << ":" << event_->lb << ":" << event_->id
				    <<std::endl;
    return;
  } else if (!lumiDetails->isValid()) {
    //edm::LogWarning("doEventInfo()") << "LumiDetails collection invalid (empty) for "
    //<< event_->run << ":" << event_->lb << ":"
    //<< event_->id << std::endl;
    return;
  }
  
  // debugging
  //std::cout << "Lumi version: " << lumiDetails->lumiVersion() << std::endl;
  bool debug = false;
  if (bx < 4 || bx > 3560) {
    std::cout << "\nEvent " << event_->run << ":" << event_->lb << ":" << event_->id
	      << "\nbx = " << bx
	      << "\n==================================" << std::endl;
    debug = true;
  }
  
  for (int i = -2; i < 3; i++) {
    int iBx = bx + i;
    if ( iBx < 0 ) iBx += bxPerOrbit;
    if ( iBx > (int)bxPerOrbit-1) iBx -= bxPerOrbit;
    if (debug) std::cout << iBx << "\t";
    
    Double_t lumiByBx = lumiDetails->lumiValue(LumiDetails::kOCC1,iBx)*6.37;
    Double_t beam1Intensity = lumiDetails->lumiBeam1Intensity(iBx);
    Double_t beam2Intensity = lumiDetails->lumiBeam2Intensity(iBx);
    //std::cout << "...Retreived details" << std::endl;
    
    event_->beam1Intensity.at(i+2) = beam1Intensity;
    event_->beam2Intensity.at(i+2) = beam2Intensity;
    event_->lumiByBx.at(i+2) = lumiByBx;
    //std::cout << "...Saved details" << std::endl;
  }
  
  if (debug) {
    std::cout<<std::endl;
    std::cout<<"  x\tbeam1I\tbeam2I\tlumiByBx(ub^-1 s^-1)\n"
	     <<" ------------------------------------------------------------------- "
	     << std::endl;
    for (int x=0; x<5; x++) {
      std::cout << "  " << x
		<< "\t" << event_->beam1Intensity.at(x)
		<< "\t" << event_->beam2Intensity.at(x)
		<< "\t" << event_->lumiByBx.at(x)
		<< std::endl;
    }
  }

  //std::cout<<"finished event info"<<std::endl;
}

//simple matching between standalone muon and generated muon
int StoppedHSCPMuonTreeProducer::getGenParticleMatch(const edm::Event& iEvent, reco::TrackRef Track) {
  double minDeltaR=999;
  int genIndex=-999;

  edm::Handle<reco::GenParticleCollection> genParticles;
  iEvent.getByLabel(genParticlesTag_, genParticles);

  if (genParticles.isValid()) {
    for(size_t i=0; i<genParticles->size(); i++){
      const reco::GenParticle & p = (*genParticles)[i];

      //look at muons
      if (TMath::Abs(p.pdgId()) == 13) {
	if(p.status()==1){
	  
	  // Calculate deltaR between this genParticle and the standalone or refitted standalone muon track
	  double dR=deltaR(Track->eta(),Track->phi(),p.eta(),p.phi());
	  if (dR<minDeltaR) {
	    minDeltaR = dR;
	    genIndex = i;
	  }
	}//end of status==1
      }// end of muons
    }//end of loop over gen particles
  }//end of if gen particles collection is valid

  if (minDeltaR<recoGenDeltaR_) return genIndex;
  else return -999;

}

//simple matching between standalone muon and generated muon
int StoppedHSCPMuonTreeProducer::getGenParticleMatch(const edm::Event& iEvent, std::vector<reco::Track>::const_iterator it) {
  double minDeltaR=999;
  int genIndex=-999;

  edm::Handle<reco::GenParticleCollection> genParticles;
  iEvent.getByLabel(genParticlesTag_, genParticles);

  if (genParticles.isValid()) {
    for(size_t i=0; i<genParticles->size(); i++){
      const reco::GenParticle & p = (*genParticles)[i];

      //look at muons
      if (TMath::Abs(p.pdgId()) == 13) {
	if(p.status()==1){
	  
	  // Calculate deltaR between this genParticle and the standalone or refitted standalone muon track
	  double dR=deltaR(it->eta(),it->phi(),p.eta(),p.phi());
	  if (dR<minDeltaR) {
	    minDeltaR = dR;
	    genIndex = i;
	  }
	} //end of status==1
      }//end of partID==13
    }//end of loop over gen particles
  }//end of if gen particle collection is valid

  if (minDeltaR<recoGenDeltaR_) return genIndex;
  else return -999;

}


//simple matching between standalone muon and HLT muon
int StoppedHSCPMuonTreeProducer::getTriggerObjectMatch20(const edm::Event& iEvent, reco::TrackRef Track) {
  double minDeltaR=999;
  int triggerObjIndex=-999;

  // get HLT muons
  edm::Handle<trigger::TriggerEvent> trgEvent;
  iEvent.getByLabel(hltEventTag_, trgEvent);

  if (trgEvent.isValid()) {
    const unsigned int filterIndex (trgEvent->filterIndex(hltFilterTag_20_) );
    if (filterIndex < trgEvent->sizeFilters()) {
      
      const trigger::TriggerObjectCollection& TOC(trgEvent->getObjects());
      const trigger::Keys& keys( trgEvent->filterKeys(filterIndex) );
      
      for ( unsigned hlto = 0; hlto < keys.size(); hlto++ ) {
	trigger::size_type hltf = keys[hlto];
	const trigger::TriggerObject& obj(TOC[hltf]);
	  
	  // Calculate deltaR between this HLT object and the standalone or refitted standalone muon track
	double dR=deltaR(Track->eta(),Track->phi(),obj.eta(),obj.phi());
	if (dR<minDeltaR) {
	  minDeltaR = dR;
	  triggerObjIndex = hlto;
	}
      }//end of loop over trigger objects
    }//end if filter within total number of filters
  }//end of valid trigger event

  if (minDeltaR<recoTriggerDeltaR_) return triggerObjIndex;
  else return -999;

}

int StoppedHSCPMuonTreeProducer::getTriggerObjectMatch20(const edm::Event& iEvent, std::vector<reco::Track>::const_iterator it) {
  double minDeltaR=999;
  int triggerObjIndex=-999;

  // get HLT muons
  edm::Handle<trigger::TriggerEvent> trgEvent;
  iEvent.getByLabel(hltEventTag_, trgEvent);

  if (trgEvent.isValid()) {
    const unsigned int filterIndex (trgEvent->filterIndex(hltFilterTag_20_) );
    if (filterIndex < trgEvent->sizeFilters()) {
      
      const trigger::TriggerObjectCollection& TOC(trgEvent->getObjects());
      const trigger::Keys& keys( trgEvent->filterKeys(filterIndex) );
      
      for ( unsigned hlto = 0; hlto < keys.size(); hlto++ ) {
	trigger::size_type hltf = keys[hlto];
	const trigger::TriggerObject& obj(TOC[hltf]);
	  
	  // Calculate deltaR between this HLT object and the standalone or refitted standalone muon track
	double dR=deltaR(it->eta(),it->phi(),obj.eta(),obj.phi());
	if (dR<minDeltaR) {
	  minDeltaR = dR;
	  triggerObjIndex = hlto;
	}
      }//end of loop over trigger objects
    }//end if filter within total number of filters
  }//end of valid trigger event

  if (minDeltaR<recoTriggerDeltaR_) return triggerObjIndex;
  else return -999;

}

//simple matching between standalone muon and HLT muon
int StoppedHSCPMuonTreeProducer::getTriggerObjectMatch20Cha2(const edm::Event& iEvent, reco::TrackRef Track) {
  double minDeltaR=999;
  int triggerObjIndex=-999;

  // get HLT muons
  edm::Handle<trigger::TriggerEvent> trgEvent;
  iEvent.getByLabel(hltEventTag_, trgEvent);

  if (trgEvent.isValid()) {
    const unsigned int filterIndex (trgEvent->filterIndex(hltFilterTag_20Cha2_) );
    if (filterIndex < trgEvent->sizeFilters()) {
      
      const trigger::TriggerObjectCollection& TOC(trgEvent->getObjects());
      const trigger::Keys& keys( trgEvent->filterKeys(filterIndex) );
      
      for ( unsigned hlto = 0; hlto < keys.size(); hlto++ ) {
	trigger::size_type hltf = keys[hlto];
	const trigger::TriggerObject& obj(TOC[hltf]);
	  
	  // Calculate deltaR between this HLT object and the standalone or refitted standalone muon track
	double dR=deltaR(Track->eta(),Track->phi(),obj.eta(),obj.phi());
	if (dR<minDeltaR) {
	  minDeltaR = dR;
	  triggerObjIndex = hlto;
	}
      }//end of loop over trigger objects
    }//end if filter within total number of filters
  }//end of valid trigger event

  if (minDeltaR<recoTriggerDeltaR_) return triggerObjIndex;
  else return -999;

}

int StoppedHSCPMuonTreeProducer::getTriggerObjectMatch20Cha2(const edm::Event& iEvent, std::vector<reco::Track>::const_iterator it) {
  double minDeltaR=999;
  int triggerObjIndex=-999;

  // get HLT muons
  edm::Handle<trigger::TriggerEvent> trgEvent;
  iEvent.getByLabel(hltEventTag_, trgEvent);

  if (trgEvent.isValid()) {
    const unsigned int filterIndex (trgEvent->filterIndex(hltFilterTag_20Cha2_) );
    if (filterIndex < trgEvent->sizeFilters()) {
      
      const trigger::TriggerObjectCollection& TOC(trgEvent->getObjects());
      const trigger::Keys& keys( trgEvent->filterKeys(filterIndex) );
      
      for ( unsigned hlto = 0; hlto < keys.size(); hlto++ ) {
	trigger::size_type hltf = keys[hlto];
	const trigger::TriggerObject& obj(TOC[hltf]);
	  
	  // Calculate deltaR between this HLT object and the standalone or refitted standalone muon track
	double dR=deltaR(it->eta(),it->phi(),obj.eta(),obj.phi());
	if (dR<minDeltaR) {
	  minDeltaR = dR;
	  triggerObjIndex = hlto;
	}
      }//end of loop over trigger objects
    }//end if filter within total number of filters
  }//end of valid trigger event

  if (minDeltaR<recoTriggerDeltaR_) return triggerObjIndex;
  else return -999;

}



void StoppedHSCPMuonTreeProducer::doTrigger(const edm::Event& iEvent, const edm::EventSetup& iSetup) {

  // get GT data
  edm::ESHandle<L1GtTriggerMenu> menuRcd;
  iSetup.get<L1GtTriggerMenuRcd>().get(menuRcd) ;
  const L1GtTriggerMenu* menu = menuRcd.product();
  
  edm::Handle<L1GlobalTriggerReadoutRecord> gtReadoutRecord;
  iEvent.getByLabel(l1BitsTag_, gtReadoutRecord);

  // L1 trigger bits (for triggered BX)
  uint64_t gtAlgoWord0(0), gtAlgoWord1(0), gtTechWord(0);

  DecisionWord gtDecisionWord = gtReadoutRecord->decisionWord();
  unsigned i=0;
  for(DecisionWord::const_iterator itr=gtDecisionWord.begin();
      itr != gtDecisionWord.end();
      itr++, i++) {
    if (*itr) {
      if(i<64) { gtAlgoWord0 |= (1LL<<i); }
      else { gtAlgoWord1 |= (1LL<<(i-64)); }
    } 
  }
  
  TechnicalTriggerWord gtTechDecisionWord = gtReadoutRecord->technicalTriggerWord();    
  i=0;
  for(TechnicalTriggerWord::const_iterator itr=gtDecisionWord.begin();
      itr != gtDecisionWord.end();
      itr++, i++) {
    if (*itr) {
      gtTechWord |= (1LL<<i);
    } 
  }

  // Get prescale information
  L1GtUtils* l1gtutils = new L1GtUtils();
  l1gtutils->retrieveL1EventSetup(iSetup);

  int errorAlgo=0;
  int errorTech=0;

  //Are Algo and Trigger prescale indices supposed to be the same?  Save them separately, for now
  event_->algoTriggerPrescaleIndex =l1gtutils->prescaleFactorSetIndex(iEvent,L1GtUtils::AlgorithmTrigger,errorAlgo);
  event_->techTriggerPrescaleIndex =l1gtutils->prescaleFactorSetIndex(iEvent,L1GtUtils::TechnicalTrigger,errorTech);
  if (errorAlgo!=0)
    event_->algoTriggerPrescaleIndex=-999;
  if (errorTech!=0)
    event_->algoTriggerPrescaleIndex=-999;

  event_->gtAlgoWord0 = gtAlgoWord0;
  event_->gtAlgoWord1 = gtAlgoWord1;
  event_->gtTechWord = gtTechWord;
  
  // Get prescales for individual L1 triggers
  
  int errorCode=0;
  event_->l1JetNoBptxPrescale = l1gtutils->prescaleFactor(iEvent,
							  l1JetNoBptxName_,
							  errorCode);
  if (errorCode!=0) event_->l1JetNoBptxPrescale=-999;
  //std::cout <<"PRESCALE l1JetNoBptxPrescale = "<< event_->l1JetNoBptxPrescale <<"  errorCode = "<<errorCode<<std::endl;

  event_->l1JetNoBptxNoHaloPrescale = l1gtutils->prescaleFactor(iEvent,
								l1JetNoBptxNoHaloName_,
								errorCode);
  if (errorCode!=0) event_->l1JetNoBptxNoHaloPrescale=-999;
  //std::cout <<"PRESCALE l1JetNoBptxNoHaloPrescale = "<< event_->l1JetNoBptxNoHaloPrescale <<"  errorCode = "<<errorCode<<std::endl;

  event_->l1Jet32NoBptxNoHaloPrescale = l1gtutils->prescaleFactor(iEvent,
								  l1Jet32NoBptxNoHaloName_,
								  errorCode);
  if (errorCode!=0) event_->l1Jet32NoBptxNoHaloPrescale=-999;
  //std::cout <<"PRESCALE l1Jet32NoBptxNoHaloPrescale = "<< event_->l1Jet32NoBptxNoHaloPrescale <<"  errorCode = "<<errorCode<<std::endl;

  event_->l1SingleMu16erPrescale = l1gtutils->prescaleFactor(iEvent,
								  l1SingleMu16erName_,
								  errorCode);
  if (errorCode!=0) event_->l1SingleMu16erPrescale=-999;
  //std::cout <<"PRESCALE l1SingleMu16erPrescale = "<< event_->l1SingleMu16erPrescale <<"  errorCode = "<<errorCode<<std::endl;

  event_->l1SingleMu6NoBptxPrescale = l1gtutils->prescaleFactor(iEvent,
								  l1SingleMu6NoBptxName_,
								  errorCode);
  if (errorCode!=0) event_->l1SingleMu6NoBptxPrescale=-999;
  //std::cout <<"PRESCALE l1SingleMu6NoBptxPrescale = "<< event_->l1SingleMu6NoBptxPrescale <<"  errorCode = "<<errorCode<<std::endl;


  
  // Test output; need to check error code
  //std::cout <<"PRESCALE 32 = "<< event_->l1Jet32NoBptxNoHaloPrescale <<"  errorCode = "<<errorCode<<std::endl;


  // L1 trigger bits for -2..+2 BX
  int start = -2;
  int end = 3;
  if (isMC_) {  // don't loop over multiple BX for MC
    start=0;
    end=1;
  }
  for (int bx=start; bx<end; ++bx) {

    const DecisionWord decisionWord = gtReadoutRecord->decisionWord(bx);
    const TechnicalTriggerWord technicalWord = gtReadoutRecord->technicalTriggerWord(bx);

    bool l1JetNoBptx         = menu->gtAlgorithmResult(l1JetNoBptxName_,       decisionWord);
    bool l1JetNoBptxNoHalo   = menu->gtAlgorithmResult(l1JetNoBptxNoHaloName_, decisionWord);
    bool l1Jet32NoBptxNoHalo = menu->gtAlgorithmResult(l1Jet32NoBptxNoHaloName_, decisionWord);
    bool l1SingleMu16er      = menu->gtAlgorithmResult(l1SingleMu16erName_, decisionWord);
    bool l1SingleMu6NoBptx   = menu->gtAlgorithmResult(l1SingleMu6NoBptxName_, decisionWord);
    bool l1Bptx              = technicalWord.at(1);
    bool l1MuBeamHalo        = menu->gtAlgorithmResult(l1MuBeamHaloName_,      decisionWord);

    event_->l1JetNoBptx.at(bx+2)       = (l1JetNoBptx ? 1 : 0);
    event_->l1JetNoBptxNoHalo.at(bx+2) = (l1JetNoBptxNoHalo ? 1 : 0);
    event_->l1Jet32NoBptxNoHalo.at(bx+2) = (l1Jet32NoBptxNoHalo ? 1 : 0);
    event_->l1SingleMu16er.at(bx+2) = (l1SingleMu16er ? 1 : 0);
    event_->l1SingleMu6NoBptx.at(bx+2) = (l1SingleMu6NoBptx ? 1 : 0);

    //     event_->l1BptxPlus.at(bx+2)        = l1BptxPlus;
    //     event_->l1BptxMinus.at(bx+2)       = l1BptxMinus;
    event_->l1Bptx.at(bx+2)            = (l1Bptx ? 1 : 0);
    event_->l1MuBeamHalo.at(bx+2)      = (l1MuBeamHalo ? 1 : 0);
    
  }

  //std::cout<<"starting HLT stuff"<<std::endl;
  // HLT config setup
  // moved to beginRun()
  bool hltBitJetNoBptx(false), hltBitJetNoBptxNoHalo(false), hltBitJetNoBptx3BXNoHalo(false), hltBitJetE50NoBptx3BXNoHalo(false), hltBitL2Mu20eta2p1NoVertex(false), hltBitL2Mu10NoVertexNoBptx3BX(false), hltBitL2Mu20NoVertexNoBptx3BX(false), hltBitL2Mu30NoVertexNoBptx3BX(false), hltBitL2Mu10NoVertexNoBptx3BXNoHalo(false), hltBitL2Mu20NoVertexNoBptx3BXNoHalo(false), hltBitL2Mu30NoVertexNoBptx3BXNoHalo(false),  hltBitL2Mu20NoVertex2ChaNoBptx3BXNoHalo(false), hltBitL2Mu30NoVertex2ChaNoBptx3BXNoHalo(false);

  // get HLT results
  edm::Handle<edm::TriggerResults> HLTR;
  iEvent.getByLabel(hltResultsTag_, HLTR);

  if (HLTR.isValid()) {
    // triggerIndex must be less than the size of HLTR or you get a CMSException: _M_range_check
    if (doHltBit1_ && hltPathIndexJetNoBptx_ < HLTR->size()) hltBitJetNoBptx = HLTR->accept(hltPathIndexJetNoBptx_);
    if (doHltBit2_ && hltPathIndexJetNoBptxNoHalo_ < HLTR->size()) hltBitJetNoBptxNoHalo = HLTR->accept(hltPathIndexJetNoBptxNoHalo_); 
    if (doHltBit3_ && hltPathIndexJetNoBptx3BXNoHalo_ < HLTR->size()) hltBitJetNoBptx3BXNoHalo = HLTR->accept(hltPathIndexJetNoBptx3BXNoHalo_); 
    if (doHltBit4_ && hltPathIndexJetE50NoBptx3BXNoHalo_ < HLTR->size()) hltBitJetE50NoBptx3BXNoHalo = HLTR->accept(hltPathIndexJetE50NoBptx3BXNoHalo_);
    if (doHltBit5_ && hltPathIndexL2Mu20eta2p1NoVertex_ < HLTR->size()) hltBitL2Mu20eta2p1NoVertex = HLTR->accept(hltPathIndexL2Mu20eta2p1NoVertex_);
    if (doHltBit6_ && hltPathIndexL2Mu10NoVertexNoBptx3BX_ < HLTR->size()) hltBitL2Mu10NoVertexNoBptx3BX = HLTR->accept(hltPathIndexL2Mu10NoVertexNoBptx3BX_);
    if (doHltBit7_ && hltPathIndexL2Mu20NoVertexNoBptx3BX_ < HLTR->size()) hltBitL2Mu20NoVertexNoBptx3BX = HLTR->accept(hltPathIndexL2Mu20NoVertexNoBptx3BX_);
    if (doHltBit8_ && hltPathIndexL2Mu30NoVertexNoBptx3BX_ < HLTR->size()) hltBitL2Mu30NoVertexNoBptx3BX = HLTR->accept(hltPathIndexL2Mu30NoVertexNoBptx3BX_);
    if (doHltBit9_ && hltPathIndexL2Mu10NoVertexNoBptx3BXNoHalo_ < HLTR->size()) hltBitL2Mu10NoVertexNoBptx3BXNoHalo = HLTR->accept(hltPathIndexL2Mu10NoVertexNoBptx3BXNoHalo_);
    if (doHltBit10_ && hltPathIndexL2Mu20NoVertexNoBptx3BXNoHalo_ < HLTR->size()) hltBitL2Mu20NoVertexNoBptx3BXNoHalo = HLTR->accept(hltPathIndexL2Mu20NoVertexNoBptx3BXNoHalo_);
    if (doHltBit11_ && hltPathIndexL2Mu30NoVertexNoBptx3BXNoHalo_ < HLTR->size()) hltBitL2Mu30NoVertexNoBptx3BXNoHalo = HLTR->accept(hltPathIndexL2Mu30NoVertexNoBptx3BXNoHalo_);
    if (doHltBit12_ && hltPathIndexL2Mu20NoVertex2ChaNoBptx3BXNoHalo_ < HLTR->size()) hltBitL2Mu20NoVertex2ChaNoBptx3BXNoHalo = HLTR->accept(hltPathIndexL2Mu20NoVertex2ChaNoBptx3BXNoHalo_);
    if (doHltBit13_ && hltPathIndexL2Mu30NoVertex2ChaNoBptx3BXNoHalo_ < HLTR->size()) hltBitL2Mu30NoVertex2ChaNoBptx3BXNoHalo = HLTR->accept(hltPathIndexL2Mu30NoVertex2ChaNoBptx3BXNoHalo_);
  }
  else {
    if (doHltBit1_) edm::LogWarning("MissingProduct") << "HLT information not found for HltBit1.  Branch will not be filled" << std::endl;
    if (doHltBit2_) edm::LogWarning("MissingProduct") << "HLT information not found for HltBit2.  Branch will not be filled" << std::endl;
    if (doHltBit3_) edm::LogWarning("MissingProduct") << "HLT information not found for HltBit3.  Branch will not be filled" << std::endl;
    if (doHltBit4_) edm::LogWarning("MissingProduct") << "HLT information not found for HltBit4.  Branch will not be filled" << std::endl;
    if (doHltBit5_) edm::LogWarning("MissingProduct") << "HLT information not found for HltBit5.  Branch will not be filled" << std::endl;
    if (doHltBit6_) edm::LogWarning("MissingProduct") << "HLT information not found for HltBit6.  Branch will not be filled" << std::endl;
    if (doHltBit7_) edm::LogWarning("MissingProduct") << "HLT information not found for HltBit7.  Branch will not be filled" << std::endl;
    if (doHltBit8_) edm::LogWarning("MissingProduct") << "HLT information not found for HltBit8.  Branch will not be filled" << std::endl;
    if (doHltBit9_) edm::LogWarning("MissingProduct") << "HLT information not found for HltBit9.  Branch will not be filled" << std::endl;
    if (doHltBit10_) edm::LogWarning("MissingProduct") << "HLT information not found for HltBit10.  Branch will not be filled" << std::endl;
    if (doHltBit11_) edm::LogWarning("MissingProduct") << "HLT information not found for HltBit11.  Branch will not be filled" << std::endl;
    if (doHltBit12_) edm::LogWarning("MissingProduct") << "HLT information not found for HltBit12.  Branch will not be filled" << std::endl;
    if (doHltBit13_) edm::LogWarning("MissingProduct") << "HLT information not found for HltBit13.  Branch will not be filled" << std::endl;
    doHltBit1_ = false;
    doHltBit2_ = false;
    doHltBit3_ = false;
    doHltBit4_ = false;
    doHltBit5_ = false;
    doHltBit6_ = false;
    doHltBit7_ = false;
    doHltBit8_ = false;
    doHltBit9_ = false;
    doHltBit10_ = false;
    doHltBit11_ = false;
    doHltBit12_ = false;
    doHltBit13_ = false;
  }

  // store bits
  event_->hltJetNoBptx = hltBitJetNoBptx;
  event_->hltJetNoBptxNoHalo = hltBitJetNoBptxNoHalo;
  event_->hltJetNoBptx3BXNoHalo = hltBitJetNoBptx3BXNoHalo;
  event_->hltJetE50NoBptx3BXNoHalo = hltBitJetE50NoBptx3BXNoHalo;
  event_->hltL2Mu20eta2p1NoVertex = hltBitL2Mu20eta2p1NoVertex;
  event_->hltL2Mu10NoVertexNoBptx3BX = hltBitL2Mu10NoVertexNoBptx3BX;
  event_->hltL2Mu20NoVertexNoBptx3BX = hltBitL2Mu20NoVertexNoBptx3BX;
  event_->hltL2Mu30NoVertexNoBptx3BX = hltBitL2Mu30NoVertexNoBptx3BX;
  event_->hltL2Mu10NoVertexNoBptx3BXNoHalo = hltBitL2Mu10NoVertexNoBptx3BXNoHalo;
  event_->hltL2Mu20NoVertexNoBptx3BXNoHalo = hltBitL2Mu20NoVertexNoBptx3BXNoHalo;
  event_->hltL2Mu30NoVertexNoBptx3BXNoHalo = hltBitL2Mu30NoVertexNoBptx3BXNoHalo;
  event_->hltL2Mu20NoVertex2ChaNoBptx3BXNoHalo = hltBitL2Mu20NoVertex2ChaNoBptx3BXNoHalo;
  event_->hltL2Mu30NoVertex2ChaNoBptx3BXNoHalo = hltBitL2Mu30NoVertex2ChaNoBptx3BXNoHalo;
  
  // Store HLT prescale info
  event_->hltPrescaleIndex=hltConfig_.prescaleSet(iEvent, iSetup);
  event_->hltJetNoBptxPrescale=hltConfig_.prescaleValue(iEvent, iSetup, hltPathJetNoBptx_);
  event_->hltJetNoBptxNoHaloPrescale=hltConfig_.prescaleValue(iEvent, iSetup, hltPathJetNoBptxNoHalo_);
  event_->hltJetNoBptx3BXNoHaloPrescale=hltConfig_.prescaleValue(iEvent, iSetup, hltPathJetNoBptx3BXNoHalo_);
  event_->hltJetE50NoBptx3BXNoHaloPrescale=hltConfig_.prescaleValue(iEvent, iSetup, hltPathJetE50NoBptx3BXNoHalo_);
  event_->hltL2Mu20eta2p1NoVertexPrescale=hltConfig_.prescaleValue(iEvent, iSetup, hltPathL2Mu20eta2p1NoVertex_);
  event_->hltL2Mu10NoVertexNoBptx3BXPrescale=hltConfig_.prescaleValue(iEvent, iSetup, hltPathL2Mu10NoVertexNoBptx3BX_);
  event_->hltL2Mu20NoVertexNoBptx3BXPrescale=hltConfig_.prescaleValue(iEvent, iSetup, hltPathL2Mu20NoVertexNoBptx3BX_);
  event_->hltL2Mu30NoVertexNoBptx3BXPrescale=hltConfig_.prescaleValue(iEvent, iSetup, hltPathL2Mu30NoVertexNoBptx3BX_);
  event_->hltL2Mu10NoVertexNoBptx3BXNoHaloPrescale=hltConfig_.prescaleValue(iEvent, iSetup, hltPathL2Mu10NoVertexNoBptx3BXNoHalo_);
  event_->hltL2Mu20NoVertexNoBptx3BXNoHaloPrescale=hltConfig_.prescaleValue(iEvent, iSetup, hltPathL2Mu20NoVertexNoBptx3BXNoHalo_);
  event_->hltL2Mu30NoVertexNoBptx3BXNoHaloPrescale=hltConfig_.prescaleValue(iEvent, iSetup, hltPathL2Mu30NoVertexNoBptx3BXNoHalo_);
  event_->hltL2Mu20NoVertex2ChaNoBptx3BXNoHaloPrescale=hltConfig_.prescaleValue(iEvent, iSetup, hltPathL2Mu20NoVertex2ChaNoBptx3BXNoHalo_);
  event_->hltL2Mu30NoVertex2ChaNoBptx3BXNoHaloPrescale=hltConfig_.prescaleValue(iEvent, iSetup, hltPathL2Mu30NoVertex2ChaNoBptx3BXNoHalo_);
  

  // L1 jets
  edm::Handle<l1extra::L1JetParticleCollection> l1CenJets;
  iEvent.getByLabel(l1JetsTag_, "Central", l1CenJets);  
  edm::Handle<l1extra::L1JetParticleCollection> l1TauJets;
  iEvent.getByLabel(l1JetsTag_, "Tau", l1TauJets);
  
  if (l1CenJets.isValid() && l1TauJets.isValid()) { 

    // merge and sort central and tau jet collections
    std::vector<l1extra::L1JetParticle> l1jets;
    
    l1jets.insert(l1jets.end(), l1CenJets->begin(), l1CenJets->end());
    l1jets.insert(l1jets.end(), l1TauJets->begin(), l1TauJets->end());
    std::sort(l1jets.begin(), l1jets.end(), l1jet_gt());
    
    for (std::vector<l1extra::L1JetParticle>::const_iterator jet=l1jets.begin(); jet!=l1jets.end(); ++jet) {
      shscp::TrigJet j;
      j.type = jet->type();   // 0 = central, 1 = forward, 2 = tau
      j.e = jet->energy();
      j.et = jet->et();
      j.phi = jet->phi();
      j.eta = jet->eta();
      event_->addL1Jet(j);
    }
    
  }
  else {
    if (!l1JetsMissing_) edm::LogWarning("MissingProduct") << "L1 information not found.  Branch will not be filled" << std::endl;
    l1JetsMissing_ = true;
  }

  // L1 muons                                                                                                                                                                                                                   
  edm::Handle<l1extra::L1MuonParticleCollection> l1Muons;
  iEvent.getByLabel(l1MuonsTag_, "", l1Muons);

  if (l1Muons.isValid() ){

    std::vector<l1extra::L1MuonParticle> l1muons;

    l1muons.insert(l1muons.end(), l1Muons->begin(), l1Muons->end());
    std::sort(l1muons.begin(), l1muons.end(), l1muon_pt());

    for (std::vector<l1extra::L1MuonParticle>::const_iterator muon=l1muons.begin(); muon!=l1muons.end(); ++muon) {
      shscp::TrigMuon m;
      m.pt = muon->pt();
      m.phi = muon->phi();
      m.eta = muon->eta();
      event_->addL1Muon(m);
    }

  }
  else {
    if (!l1MuonsMissing_) edm::LogWarning("MissingProduct") << "L1 information not found.  Branch will not be filled" << std::endl;
    l1MuonsMissing_ = true;
  }

  // get HLT muons
  edm::Handle<trigger::TriggerEvent> trgEvent;

  //std::cout <<"hltEventTag = "<<hltEventTag_<<std::endl;
  iEvent.getByLabel(hltEventTag_, trgEvent);

  if (trgEvent.isValid()) {

    // for Stopped HSCPMuon 20 GeV filter
    const unsigned int filterIndex20 (trgEvent->filterIndex(hltFilterTag_20_) );
    //   edm::LogInfo("StoppedHSCPMuon") << "Debugging HLT...  StoppedHSCPMuon index=" << filterIndex 
    //				<< ",  N paths=" << trgEvent->sizeFilters() << std::endl;
    
    if (filterIndex20 < trgEvent->sizeFilters()) {            
      const trigger::TriggerObjectCollection& TOC20(trgEvent->getObjects());
      const trigger::Keys& keys20( trgEvent->filterKeys(filterIndex20) );	
      //      edm::LogInfo("StoppedHSCPMuon") << "Found  " << keys.size() << " HLT jets" << std::endl;
      for ( unsigned hlto = 0; hlto < keys20.size(); hlto++) {
	trigger::size_type hltf = keys20[hlto];
	const trigger::TriggerObject& obj(TOC20[hltf]);
	//	edm::LogInfo("StoppedHSCPMuon") << "HLT jet e=" << obj.energy() << std::endl;
	//std::cout<<"HLT muon pt is:"<<obj.pt()<<", eta is:"<<obj.eta()<<", phi is:"<<obj.phi()<<std::endl;
        
	shscp::TrigMuon m;
	m.pt = obj.pt();
	m.phi = obj.phi();
	m.eta = obj.eta();
	event_->addHlt20Muon(m);
      }      
    }

    // for Stopped HSCPMuon 20 GeV 2Cha filter
    const unsigned int filterIndex20Cha2 (trgEvent->filterIndex(hltFilterTag_20Cha2_) );
    //   edm::LogInfo("StoppedHSCPMuon") << "Debugging HLT...  StoppedHSCPMuon index=" << filterIndex 
    //				<< ",  N paths=" << trgEvent->sizeFilters() << std::endl;
    
    if (filterIndex20Cha2 < trgEvent->sizeFilters()) {            
      const trigger::TriggerObjectCollection& TOC20Cha2(trgEvent->getObjects());
      const trigger::Keys& keys20Cha2( trgEvent->filterKeys(filterIndex20Cha2) );	
      //      edm::LogInfo("StoppedHSCPMuon") << "Found  " << keys.size() << " HLT jets" << std::endl;
      for ( unsigned hlto = 0; hlto < keys20Cha2.size(); hlto++) {
	trigger::size_type hltf = keys20Cha2[hlto];
	const trigger::TriggerObject& obj(TOC20Cha2[hltf]);
	//	edm::LogInfo("StoppedHSCPMuon") << "HLT jet e=" << obj.energy() << std::endl;
	//std::cout<<"HLT muon pt is:"<<obj.pt()<<", eta is:"<<obj.eta()<<", phi is:"<<obj.phi()<<std::endl;
        
	shscp::TrigMuon m;
	m.pt = obj.pt();
	m.phi = obj.phi();
	m.eta = obj.eta();
	event_->addHlt20Cha2Muon(m);
      }      
    }
  }
  else {
    if (!hltMuonsMissing_) edm::LogWarning("MissingProduct") << "TriggerEvent not found.  Branch will not be filled" << std::endl;
    hltMuonsMissing_ = true;
  }
							       
}

void StoppedHSCPMuonTreeProducer::doJets(const edm::Event& iEvent, const edm::EventSetup& iSetup) {

  //std::cout<<"started jets"<<std::endl;
  const JetCorrector* jetCorrector = JetCorrector::getJetCorrector(jetCorrectorServiceName_,iSetup);

   edm::Handle<CaloJetCollection> caloJets;
   iEvent.getByLabel(jetTag_, caloJets);
   unsigned njet=0;

   if (caloJets.isValid()) {
     // sort jets by energy
     std::vector<CaloJet> jets;
     jets.insert(jets.end(), caloJets->begin(), caloJets->end());
     std::sort(jets.begin(), jets.end(), jete_gt() );

     for(CaloJetCollection::const_iterator it=jets.begin(); 
	 it!=jets.end();
	 ++it, ++njet) {
       if (it->energy() > jetMinEnergy_) {

	 edm::RefToBase<reco::Jet> jetRef(edm::Ref<reco::CaloJetCollection>(caloJets,njet));  
	 double scale = jetCorrector->correction(*it,jetRef,iEvent,iSetup);

	 // store jet in TTree
	 shscp::Jet jet;
	 jet.e = it->energy();
	 jet.e_corr = it->energy()*scale;
	 jet.et = it->et();
	 jet.et_corr = it->et()*scale;
	 jet.eta = it->eta();
	 jet.phi = it->phi();
	 jet.eEm = it->emEnergyInEB();
	 jet.eHad = it->hadEnergyInHB();
	 jet.eMaxEcalTow = it->maxEInEmTowers();
	 jet.eMaxHcalTow = it->maxEInHadTowers();
	 jet.n60 = it->n60();
	 jet.n90 = it->n90();

	 // Add to default jet collection and/or to studyJet collection
	 if ((fabs(it->eta()) < jetMaxEta_))
	   event_->addJet(jet);
	 if (fabs(it->eta())>=studyJetMinEta_ && 
	     fabs(it->eta())<studyJetMaxEta_)
	   event_->addStudyJet(jet);
	   // 	 std::cout << "Jet " << std::endl;
// 	 std::cout << "   E=" << it->energy() << " eta=" << it->eta() << " phi=" << it->phi() << std::endl;
	 // get towers
	 
	 for (int i=0; i<it->nConstituents(); ++i) {
	   CaloTowerPtr tower = it->getCaloConstituent(i);
	   
	   if (tower->energy() > towerMinEnergy_ &&
	       fabs(tower->eta()) < towerMaxEta_) {
	     
	     // write tower
	     shscp::Tower tow;
	     tow.e = tower->energy();
	     tow.et = tower->et();
	     tow.eta = tower->eta();
	     tow.phi = tower->phi();
	     tow.ieta = tower->ieta();
	     tow.iphi = tower->iphi();
	     tow.nJet = njet;
	     tow.eHad = tower->hadEnergy();
	     tow.etHad = tower->hadEt();
	     tow.eEm = tower->emEnergy();
	     tow.etEm = tower->emEt();

	     // Always add tower, if within appropriate eta bounds
	     // (if doCaloTowers_==false, tower will be removed
	     //  via removeTowers after leadingIPhiFractionValue computed)
	     if (fabs(tower->eta()) < towerMaxEta_) 
	       event_->addTower(tow);

	     // only add "studyTower" if doCaloTowers_==true
	     if (doCaloTowers_ && 
		 fabs(tower->eta())>=studyTowerMinEta_ && 
		 fabs(it->eta())<studyTowerMaxEta_)
	       event_->addStudyTower(tow);
	     // 	   std::cout << "  Calo tower" << std::endl;
	     // 	   std::cout << "    eta=" << tower->eta() << " phi=" << tower->phi() << std::endl;
	     // 	   std::cout << "    ECAL E=" << tower->emEnergy() << " HCAL E=" << tower->hadEnergy() << std::endl;
	     // 	   std::cout << "    ECAL time : " << tower->ecalTime() << std::endl;
	     // 	   std::cout << "    HCAL time : " << tower->hcalTime() << std::endl;
	     
	   }
	 } // loop over nconstituents
       } // if (it->energy>jetMinEnergy_)
     } // loop over jets
   } // if (caloJets.isValid())
   else {
     if (!jetsMissing_) edm::LogWarning("MissingProduct") << "CaloJets not found.  Branch will not be filled" << std::endl;
     jetsMissing_ = true;
   }
 
   edm::Handle<CaloJetCollection> ak5Jets;
   iEvent.getByLabel(jetAK5Tag_, ak5Jets);
   
   if (ak5Jets.isValid()) {

     // sort jets by energy
     std::vector<CaloJet> jets;
     jets.insert(jets.end(), ak5Jets->begin(), ak5Jets->end());
     std::sort(jets.begin(), jets.end(), jete_gt() );

     for(CaloJetCollection::const_iterator it=jets.begin(); 
	 it!=jets.end();
	 ++it) {

       //       edm::RefToBase<reco::Jet> jetRef(edm::Ref<reco::CaloJetCollection>(ak5Jets,njet));  
       //       double scale = caloJetCorrector->correction(*it,jetRef,iEvent,iSetup);
       
       if (it->energy() > jetMinEnergy_) { 
	 // store jet in TTree
	 shscp::Jet jet;
	 jet.et = it->et();
	 jet.eta = it->eta();
	 jet.phi = it->phi();
	 jet.e = it->energy();
	 jet.eEm = it->emEnergyInEB();
	 jet.eHad = it->hadEnergyInHB();
	 jet.eMaxEcalTow = it->maxEInEmTowers();
	 jet.eMaxHcalTow = it->maxEInHadTowers();
	 jet.n60 = it->n60();
	 jet.n90 = it->n90();
	 if (fabs(it->eta()) < jetMaxEta_)
	   event_->addAK5Jet(jet);
	 if (fabs(it->eta())>=studyJetMinEta_ && 
	     fabs(it->eta())<studyJetMaxEta_)
	   event_->addAK5StudyJet(jet);
       }
     }

   }

   //std::cout<<"finished jets"<<std::endl;  
}



void StoppedHSCPMuonTreeProducer::doMuons(const edm::Event& iEvent, reco::CompositeCandidateCollection& dimuons) {
  //std::cout<<"started muons"<<std::endl;
  // loop over reco muons
  edm::Handle<reco::MuonCollection> muons;
  iEvent.getByLabel(muonTag_,muons);

  if (muons.isValid()) {
    // sort muons by pt
    std::vector<Muon> muons_;
    muons_.insert(muons_.end(), muons->begin(), muons->end());
    std::sort(muons_.begin(), muons_.end(), muon_pt() );
     
    //for(reco::MuonCollection::const_iterator it =muons_.begin();
    //it!=muons_.end();
    //it++) {
    //std::cout<<"muons_.size() is: "<<muons_.size()<<std::endl;
    for(size_t i=0; i<muons_.size(); i++){
      //std::cout<<"i is: "<<i<<std::endl;
      const reco::Muon& mu1 = muons_.at(i);

      shscp::Muon mu;
      mu.px = mu1.px();
      mu.py = mu1.py();
      mu.pz = mu1.pz();
      mu.pt = mu1.pt();
      mu.p = mu1.p();
      mu.eta = mu1.eta();
      mu.phi = mu1.phi();
      mu.hcalEta = 0.;  // TODO extrapolate GlobalMuon track to HCAL surface and store position!
      mu.hcalPhi = 0.;
      mu.type = (0xf & mu1.type());
      mu.sumChargedHadronPt = mu1.pfIsolationR04().sumChargedHadronPt; //Sum Pt of the charged Hadrons
      mu.sumChargedParticlePt = mu1.pfIsolationR04().sumChargedParticlePt; //Sum Pt of all charged particles (including PF electrons and muons).
      mu.sumNeutralHadronEt = mu1.pfIsolationR04().sumNeutralHadronEt; //Sum Et of the neutral hadrons
      mu.sumPhotonEt = mu1.pfIsolationR04().sumPhotonEt; //Sum Et of PF photonds
      mu.sumNeutralHadronEtHighThreshold = mu1.pfIsolationR04().sumNeutralHadronEtHighThreshold; //Sum of the neutral hadron Et with a higher threshold for the candidates(1 GeV instead of 0.5)
      mu.sumPhotonEtHighThreshold = mu1.pfIsolationR04().sumPhotonEtHighThreshold; //Sum of the PF photons Et with higher threshold (1 GeV instead of 0.5)
      mu.sumPUPt = mu1.pfIsolationR04().sumPUPt; //Sum Pt of the charged particles in the cone of interest but with particles not originating from the primary vertex(for PU corrections)       
      mu.iso = 1.0*(mu1.pfIsolationR04().sumChargedHadronPt + mu1.pfIsolationR04().sumNeutralHadronEt + mu1.pfIsolationR04().sumPhotonEt)/mu1.pt(); //recommended this be < 0.20 (loose) or < 0.12 (tight)

      event_->addMuon(mu);

      //std::cout<<"for muon "<<i<<", pt is: "<<mu.pt<<", eta is: "<<mu.eta<<", phi is: "<<mu.phi<<std::endl;

      //for(reco::MuonCollection::const_iterator it2 =it+1;
      //it2!=muons_.end();
      //it2++) {
      //const reco::Muon& mu2 = it2->globalTrack();
      if(muons_.size()>1){
	//std::cout<<"more than 1 muon in the event"<<std::endl;
	for(size_t j=i+1; j<muons_.size(); j++){
	  //std::cout<<"j is: "<<j<<std::endl;
	  const reco::Muon& mu2 = muons_.at(j);
	  
	  const int totalCharge = mu1.charge() + mu2.charge();
	  //std::cout<<"totalCharge is: "<<totalCharge<<std::endl;
	  //if (totalChargeRequired != 999 && totalCharge == totalChargeRequired) //same sign
	  //if (totalChargeRequired != 999 && totalCharge != totalChargeRequired) //opposite sign
	  if (totalCharge != 0) //opposite sign
	    continue;
	  
	  reco::CompositeCandidate di;
	  di.addDaughter(mu1);
	  di.addDaughter(mu2);
	  di.setCharge(totalCharge);
	  di.setP4(mu1.p4() + mu2.p4());
	  dimuons.push_back(di);
	  //std::cout<<"made dimuon candidate"<<std::endl;
	}//end of loop over second muon
      }//end of if more than 1 muon
    }//end of loop over muons

    // What to do with more than one dimuon candidate? Keep the highest
    // mass one? Keep the one made out of the two highest pT muons? Keep
    // all of them? Keep all of them that don't share muons?  In the
    // analysis we kept the highest mass one -- another philosophical
    // choice.

    // Sort candidates so we keep the one with largest invariant
    // mass, and remove all but that one.
    if(dimuons.size()>0){
      shscp::DiMuon di_;
      //std::sort(dimuons.begin(), dimuons.end(), ReverseMassSorter());
      if (dimuons.size() > 1) dimuons.erase(dimuons.begin() + 1, dimuons.end());
      di_.mass = dimuons.begin()->mass();
      //std::cout<<"dimuons mass is: "<<di_.mass<<std::endl;
      event_->addDiMuon(di_);
    }

  }//end of valid muons
  else {
    if (!muonsMissing_) edm::LogWarning("MissingProduct") << "Muons not found.  Branch will not be filled" << std::endl;
    muonsMissing_ = true;
  }

  //std::cout<<"finished muons"<<std::endl;

} // void StoppedHSCPMuonTreeProducer::doMuons()

void StoppedHSCPMuonTreeProducer::doCosmicMuons(const edm::Event& iEvent) {

  // loop over cosmic muons
  edm::Handle<reco::MuonCollection> cosmicMuons;
  iEvent.getByLabel(cosmicMuonTag_,cosmicMuons);
 
  if (cosmicMuons.isValid()) {
    // sort muons by pt
    std::vector<Muon> cosmicMuons_;
    cosmicMuons_.insert(cosmicMuons_.end(), cosmicMuons->begin(), cosmicMuons->end());
    std::sort(cosmicMuons_.begin(), cosmicMuons_.end(), muon_pt() );

    for(reco::MuonCollection::const_iterator it =cosmicMuons_.begin();
	it!=cosmicMuons_.end();
	it++) {
      shscp::Muon mu;
      mu.px = it->px();
      mu.py = it->py();
      mu.pz = it->pz();
      mu.pt = it->pt();
      mu.p = it->p();
      mu.eta = it->eta();
      mu.phi = it->phi();
      mu.hcalEta = 0.;  // TODO extrapolate GlobalMuon track to HCAL surface and store position!
      mu.hcalPhi = 0.;
      mu.type = (0xf & it->type())<<8;
      mu.sumChargedHadronPt = it->pfIsolationR04().sumChargedHadronPt; //Sum Pt of the charged Hadrons
      mu.sumChargedParticlePt = it->pfIsolationR04().sumChargedParticlePt; //Sum Pt of all charged particles (including PF electrons and muons).
      mu.sumNeutralHadronEt = it->pfIsolationR04().sumNeutralHadronEt; //Sum Et of the neutral hadrons
      mu.sumPhotonEt = it->pfIsolationR04().sumPhotonEt; //Sum Et of PF photonds
      mu.sumNeutralHadronEtHighThreshold = it->pfIsolationR04().sumNeutralHadronEtHighThreshold; //Sum of the neutral hadron Et with a higher threshold for the candidates(1 GeV instead of 0.5)
      mu.sumPhotonEtHighThreshold = it->pfIsolationR04().sumPhotonEtHighThreshold; //Sum of the PF photons Et with higher threshold (1 GeV instead of 0.5)
      mu.sumPUPt = it->pfIsolationR04().sumPUPt; //Sum Pt of the charged particles in the cone of interest but with particles not originating from the primary vertex(for PU corrections)       
      mu.iso = 1.0*(it->pfIsolationR04().sumChargedHadronPt + it->pfIsolationR04().sumNeutralHadronEt + it->pfIsolationR04().sumPhotonEt)/it->pt(); //recommended this be < 0.20 (loose) or < 0.12 (tight)
      event_->addCosmicMuon(mu);
    }
  }
  else {
    if (!muonsMissing_) edm::LogWarning("MissingProduct") << "Cosmic muons not found.  Branch will not be filled" << std::endl;
    muonsMissing_ = true;
  }

} // void StoppedHSCPMuonTreeProducer::doCosmicMuons()



void StoppedHSCPMuonTreeProducer::doStandAloneMuons(const edm::Event& iEvent, const edm::EventSetup& iSetup) {

  //std::cout<<"started standalone muons"<<std::endl;  
  const reco::Vertex::Point PV;
  doVertices(iEvent, PV);
  //std::cout<<"PV is: "<<PV<<std::endl;

  // loop over reco muons
  edm::ESHandle<GlobalTrackingGeometry> theTrackingGeometry;
  iSetup.get<GlobalTrackingGeometryRecord>().get(theTrackingGeometry);

  edm::Handle<reco::MuonCollection> muons;
  iEvent.getByLabel(muonTag_,muons);
  reco::MuonCollection Muons = *muons;
  std::auto_ptr<reco::MuonCollection> MuonNoVtxUpdateCollection(new reco::MuonCollection);

  // loop over standalone muon tracks
  edm::Handle<reco::TrackCollection> standAloneMuons;
  iEvent.getByLabel("standAloneMuons","",standAloneMuons);

  edm::Handle<reco::MuonTimeExtraMap> timeMap2;
  iEvent.getByLabel(timeTag_.label(),"dt",timeMap2);
  const reco::MuonTimeExtraMap & timeMapDT = *timeMap2;

  edm::Handle<RPCRecHitCollection> rpcHits;
  iEvent.getByLabel(rpcRecHitsTag_, rpcHits);

  edm::ESHandle<RPCGeometry> rpcGeom;
  iSetup.get<MuonGeometryRecord>().get(rpcGeom);

  // Check collections are valid
  if (muons.isValid() && standAloneMuons.isValid()) {
    //std::cout<<"checked that muon and muon track collections are valid"<<std::endl;
    // Set muon counter, begin looping over muons
    int imucount = 0; 
    for(reco::MuonCollection::const_iterator it = muons->begin();
	it!=muons->end();
	it++) {
      //std::cout<<"imucount is: "<<imucount<<std::endl;
      
      // fill temp muon variable
      reco::Muon muontemp = Muons[imucount];
      
      // is current muon standalone
      if (it->isStandAloneMuon()) { 
	
        // fill temp variable with standalone track ref from muon
	reco::TrackRef standAloneVtxTrack = it->standAloneMuon();	
	
        // set track counter, begin looping over standalone tracks
	int tracknum = 0;
	for (reco::TrackCollection::const_iterator standAloneTrack = standAloneMuons->begin();
	     standAloneTrack!=standAloneMuons->end();
	     standAloneTrack++) {
	  
          // did standAlone track from muon, track from standAlone collection originate from same seeds
	  if (standAloneVtxTrack->seedRef() == standAloneTrack->seedRef()) {
            // make new track ref to matching standAlone track, link it to current muon
	    reco::TrackRef trackMatch(standAloneMuons,tracknum);
	    muontemp.setStandAlone(trackMatch); 
	  }
	  tracknum++;
	}
      }
      // add updated muon to new collection
      MuonNoVtxUpdateCollection->push_back(muontemp);
      imucount++;
    }

    std::vector<Muon> muons_;
    muons_.insert(muons_.end(), MuonNoVtxUpdateCollection->begin(), MuonNoVtxUpdateCollection->end());

    // sort muons by pt
    //std::sort(muons_.begin(), muons_.end(), muon_pt() );
    //std::cout<<"starting to sort by track pt"<<std::endl;
    //sort muons by track pt
    std::vector< std::pair<float, int> > trackPt;
    int count = 0;
    for(reco::MuonCollection::const_iterator it =muons_.begin();
	it!=muons_.end();
	it++) {      
      if (it->isStandAloneMuon()) {	
	reco::TrackRef standAloneTrack = it->standAloneMuon();	

	std::pair<float, int> a;
	a.first = standAloneTrack->pt();
	a.second = count;
	
	trackPt.push_back(a);
      }
      count++;
    }
    std::sort(trackPt.begin(), trackPt.end());

    //std::cout<<"______"<<std::endl;
    //if(trackPt.size() != muons_.size()) std::cout<<"for event: "<<iEvent.id().event()<<", in run: "<<iEvent.id().run()<<"trackPt.size is: "<<trackPt.size()<<", muons_.size is: "<<muons_.size()<<std::endl;
    for (int i=trackPt.size()-1; i>=0; i--){
      //std::cout<<"index is: "<<trackPt[i].second<<", track pt is: "<<trackPt[i].first<<std::endl;
      if (muons_[trackPt[i].second].isStandAloneMuon()) {
	reco::TrackRef standAloneTrack = muons_[trackPt[i].second].standAloneMuon();

	shscp::Track track;
	track.charge = standAloneTrack->charge();
	track.px = standAloneTrack->px();
	track.py = standAloneTrack->py();
	track.pz = standAloneTrack->pz();
	track.pt = standAloneTrack->pt();
	track.p = standAloneTrack->p();
	track.eta = standAloneTrack->eta();
	track.phi = standAloneTrack->phi();
	track.hcalEta = 0.;  // TODO extrapolate GlobalMuon track to HCAL surface and store position!
	track.hcalPhi = 0.;
	track.chi2  = standAloneTrack->chi2();
	track.ndof  = standAloneTrack->ndof();
	track.normalizedChi2  = standAloneTrack->normalizedChi2();
	track.dxy = standAloneTrack->dxy(PV);
	track.dz = standAloneTrack->dz(PV);
	track.nHits = standAloneTrack->numberOfValidHits();
	track.nLost = standAloneTrack->numberOfLostHits();
	//int muonStations (int subdet, int hitType) const
	//subdet = 0(all), 1(DT), 2(CSC), 3(RPC); hitType=-1(all), 0=valid, 3=bad 
	//track.nHitsMuonStations = standAloneTrack->hitPattern().muonStations(0,0);
	track.nStations = standAloneTrack->hitPattern().muonStationsWithValidHits(); //muon stations in SAmuon track; same variable as hitPattern().muonStations(0,0)
	track.nChambersCsc = standAloneTrack->hitPattern().cscStationsWithValidHits(); //csc chambers in SAmuon track
	track.nChambersDt = standAloneTrack->hitPattern().dtStationsWithValidHits(); //dt chambers in SAmuon track
	track.nChambersRpc = standAloneTrack->hitPattern().rpcStationsWithValidHits(); //rpc chambers in SAmuon track
	track.nHitsMuon = standAloneTrack->hitPattern().numberOfValidMuonHits(); //muon hits included in the SAmuon track fit; same variable as standAloneTrack->numberOfValidHits()
	track.nHitsCsc = standAloneTrack->hitPattern().numberOfValidMuonCSCHits(); //CSC hits included in the SAmuon track fit 
	track.nHitsDt = standAloneTrack->hitPattern().numberOfValidMuonDTHits(); //DT hits included in the SAmuon track fit 
	track.nHitsRpc = standAloneTrack->hitPattern().numberOfValidMuonRPCHits(); //RPC hits included in the SAmuon track fit 
	//std::cout<<"nStations is: "<<track.nStations<<std::endl;
	//std::cout<<"nChmabersCsc is: "<<track.nChambersCsc<<", nHitsCsc is: "<<track.nHitsCsc<<std::endl;
	//std::cout<<"nChambersDt is: "<<track.nChambersDt<<", nHitsDt is: "<<track.nHitsDt<<std::endl;
	//std::cout<<"nChambersRpc is: "<<track.nChambersRpc<<", nHitsRpc is: "<<track.nHitsRpc<<std::endl;
	
	reco::TrackBase::TrackQuality q = reco::TrackBase::qualityByName("highPurity");
	track.quality = (standAloneTrack->quality(q) ? 1 : 0);
	
	//matching gen particle index
	//if data, gen particle index will be -1; if no matched gen particle, index will be -999
	int GenParticleIndex = -1;
	if(isMC_) GenParticleIndex = getGenParticleMatch(iEvent, standAloneTrack);
	track.genParticleIndex = GenParticleIndex;

	//matching trigger particle index
	//if MC, trigger particle index will be -1; if no matched trigger particle, index will be -999
	int TriggerParticle20Index = -1;
	TriggerParticle20Index = getTriggerObjectMatch20(iEvent, standAloneTrack);
	track.triggerParticle20Index = TriggerParticle20Index;

	//matching trigger particle index
	//if MC, trigger particle index will be -1; if no matched trigger particle, index will be -999
	int TriggerParticle20Cha2Index = -1;
	TriggerParticle20Cha2Index = getTriggerObjectMatch20Cha2(iEvent, standAloneTrack);
	track.triggerParticle20Cha2Index = TriggerParticle20Cha2Index;
	
	//Loop over the DT hits in the track
	//for( int counter = 0; counter<standAloneTrack->hitPattern().numberOfValidMuonDTHits(); counter++) {
	//}


        // Get current muon reference, Get current MuonTimeExtra from MuonTimeExtraMap 
	reco::MuonRef muonR(muons,trackPt[i].second);
	reco::MuonTimeExtra tofdt = timeMapDT[muonR];
	
	// Store DT TOF Variables 
	track.dtTofDirection = tofdt.direction();
	track.dtTofNDof = tofdt.nDof();
	track.dtTofInverseBeta = tofdt.inverseBeta();
	track.dtTofInverseBetaErr = tofdt.inverseBetaErr();
	track.dtTofFreeInverseBeta = tofdt.freeInverseBeta();
	track.dtTofFreeInverseBetaErr = tofdt.freeInverseBetaErr();
	track.dtTofTimeAtIpInOut = tofdt.timeAtIpInOut();
	track.dtTofTimeAtIpInOutErr = tofdt.timeAtIpInOutErr();
	track.dtTofTimeAtIpOutIn = tofdt.timeAtIpOutIn();
	track.dtTofTimeAtIpOutInErr = tofdt.timeAtIpOutInErr();
	track.dtTofInverseBetaLS = tofdt.invbetaLS();
	track.dtTofInverseBetaLSErr = tofdt.invbetaLSError();
	track.dtTofYIntercept = tofdt.yIntercept();
	track.dtTofYInterceptErr = tofdt.yInterceptError();
	track.dtTofChi2Dof = tofdt.chi2Dof();
	track.dtTofAveHitTimeErr = tofdt.aveHitTimeError();

	//all hits in track
	DTRecSegment4DCollection::const_iterator segmentDT;
	CSCSegmentCollection::const_iterator segmentCSC;
	
	std::vector<int> positionDT;
	std::vector<int> positionCSC;
	//RecHitVector my4DTrack;

	//std::vector<DTRecHit1D> DTRecHits;
	//doMuonDTs(iEvent, iSetup, DTRecHits);
	
	//std::vector<int> cscSegEndcap_;
	//std::vector<int> cscSegRing_;
	//std::vector<int> cscSegStation_;
	//std::vector<int> cscSegChamber_;
	//std::vector<int> cscSegNHits_;
	//std::vector<double> cscSegPhi_;
	//std::vector<double> cscSegZ_;
	//std::vector<double> cscSegR_;
	//std::vector<double> cscSegDirPhi_;
	//std::vector<double> cscSegDirTheta_;
	//std::vector<double> cscSegTime_;
	//doCscSegments(iEvent, iSetup, standAloneTrack, cscSegEndcap_, cscSegRing_, cscSegStation_, cscSegChamber_, cscSegNHits_, cscSegPhi_, cscSegZ_, cscSegR_, cscSegDirPhi_, cscSegDirTheta_, cscSegTime_);
	//std::cout<<"finished doCscSegments"<<std::endl;
	//if(!cscSegEndcap_.empty()){
	//track.cscSegEndcap = cscSegEndcap_;
	//track.cscSegRing = cscSegRing_;
	//track.cscSegStation = cscSegStation_;
	//track.cscSegChamber = cscSegChamber_;
	//track.cscSegNHits = cscSegNHits_;
	//track.cscSegPhi = cscSegPhi_;
	//track.cscSegZ = cscSegZ_;
	//track.cscSegR = cscSegR_;
	//track.cscSegDirPhi = cscSegDirPhi_;
	//track.cscSegDirTheta = cscSegDirTheta_;
	//track.cscSegTime = cscSegTime_;
	  //std::cout<<"First csc segment time is: "<<cscSegTime_[0]<<std::endl;
	//}
	
	
	std::vector<int> rpcHitBx_;
	std::vector<double> rpcHitZ_;
	std::vector<double> rpcHitRho_;
	std::vector<double> rpcHitPhi_;
	std::vector<int> rpcHitRegion_;
	
	//Loop over the hits in the track
	//std::cout<<"number of valid hits is: "<<standAloneTrack->numberOfValidHits()<<std::endl;
	for(size_t i=0; i<standAloneTrack->recHitsSize(); i++) {
	  TrackingRecHitRef myRef = standAloneTrack->recHit(i);
	  const TrackingRecHit *rechit = myRef.get();
	  //std::cout<<"got hit number "<<i<<std::endl;
	  
	  if(rechit->isValid()){
	    const GeomDet* geomDet = theTrackingGeometry->idToDet(rechit->geographicalId());
	    
	    if ( (rechit)->geographicalId().det() == DetId::Muon){
	      
	      //DT Hits
	      if(geomDet->subDetector() == GeomDetEnumerators::DT) {
		//std::cout<<"have DT hit"<<std::endl;
		//loop over DTRecHit1D DT hits, see if any of them are the rechits in the track
		//for(unsigned int j=0; j<DTRecHits.size(); j++) {
		//if(DTRecHits[j].isValid()){
		//if (&(TrackingRecHit*)&DTRecHits[j] == *rechit) {
		//std::cout<<"rechit number "<<i<<" matched to DT rec hit number "<<j<<std::endl;
		//const DTLayer* layer=chamber->layer(D1PhiRecHits[i].wireId().layerId());
		//GlobalPoint glbPointPhi=layer->toGlobal(D1PhiRecHits[i].localPosition());
		
		//D1Phi_time.push_back(D1PhiRecHits[i].digiTime()); //Return the time (ns) of the digi used to build the rechit. 
		//D1Phi_phi.push_back(glbPointPhi.phi());
		//D1Phi_eta.push_back(glbPointPhi.eta());
		//}
		//}
		//}
		
		
		//the layer associated with this hit
		//DTLayerId myLayer(rechit->geographicalId().rawId());	    
		
		//Loop over segments already included in the vector of segments in the actual track
		//for(std::vector<int>::iterator positionIt = positionDT.begin(); positionIt != positionDT.end(); positionIt++) {		
		//}
		//DTChamberId myChamber((*segmentDT).geographicalId().rawId());
		//if(myLayer.wheel() == myChamber.wheel() && myLayer.station() == myChamber.station() && myLayer.sector() == myChamber.sector()) { }
	      }
	      
	      //CSC Hits
	      else if (geomDet->subDetector() == GeomDetEnumerators::CSC) {
		//std::cout<<"have CSC hit"<<std::endl;
		//the layer associated with this hit
		//CSCDetId myLayer(rechit->geographicalId().rawId());
		
		//Loop over segments in the current track
		//for(std::vector<int>::iterator positionIt = positionCSC.begin(); positionIt != positionCSC.end(); positionIt++) {
		//}
		
		//CSCDetId myChamber((*segmentCSC).geographicalId().rawId());
		//myLayer.chamberId();
	      }
	      
	      //RPC Hits
	      else if ( (rechit)->geographicalId().subdetId() == MuonSubdetId::RPC ){
		//else if (geomDet->subDetector() == GeomDetEnumerators::RPCBarrel) {
		//else if (geomDet->subDetector() == GeomDetEnumerators::RPCEndcap) {
		//std::cout<<"have RPC hit"<<std::endl;
		RPCDetId rollId = (RPCDetId)(rechit)->geographicalId();
		
		typedef std::pair<RPCRecHitCollection::const_iterator, RPCRecHitCollection::const_iterator> rangeRecHits;
		rangeRecHits recHitCollection =  rpcHits->get(rollId);
		
		RPCRecHitCollection::const_iterator recHitC;
		int size = 0;
		double z = -99.;
		double rho = -99.;
		double phi = -99.;
		int region = -99;
		int bx=-99;
		
		//std::cout<<"\t \t Looping on the rechits of the same roll"<<std::endl;
		for(recHitC = recHitCollection.first; recHitC != recHitCollection.second ; recHitC++) {
		  const RPCDetId detId = static_cast<const RPCDetId>(recHitC->rpcId());
		  const RPCRoll* roll = dynamic_cast<const RPCRoll*>(rpcGeom->roll(detId));
		  const GlobalPoint rhitglobal = roll->toGlobal(recHitC->localPosition());
		  
		  z = rhitglobal.z();
		  //std::cout<<"rpc rec hit z is: "<<z<<std::endl;
		  rho = rhitglobal.perp();
		  phi = rhitglobal.phi();
		  region = detId.region(); //Region id: 0 for Barrel, +/-1 For +/- Endcap. 
		  bx = (*recHitC).BunchX();
		  //std::cout<<"rpc rec hit bx is: "<<bx<<std::endl;
		  size++;
		}
		//std::cout<<"rpc rec hit size is: "<<size<<std::endl;
		if(size!=1){
		  //std::cout<<"\t \t \t more than one rechit in this roll discarded for filling histograms"<<std::endl;
		}
		else{
		  //std::cout<<"starting to pushback"<<std::endl;
		  rpcHitZ_.push_back(z);
		  rpcHitRho_.push_back(rho);
		  rpcHitPhi_.push_back(phi);
		  rpcHitRegion_.push_back(region);
		  rpcHitBx_.push_back(bx);
		  //std::cout<<"done with pushback"<<std::endl;
		}
		
		//the layer associated with this hit
		//RPCDetId myLayer(rechit->geographicalId().rawId());
		
		//Loop over segments in the current track
		//for(std::vector<int>::iterator positionIt = positionRPC.begin(); positionIt != positionRPC.end(); positionIt++) {			      
		//}
		
		//CSCDetId myChamber((*segmentRPC).geographicalId().rawId());
		//myLayer.chamberId();
		
	      }
	      //std::cout<<"done with RPCs"<<std::endl;
	      
	    } //end of hit is in muon system
	    //std::cout<<"done with muon hits"<<std::endl;
	  } //end of is valid hit
	  //std::cout<<"done with valid hits"<<std::endl;
	}//end of loop over valid hits
	//std::cout<<"done with loop over hits"<<std::endl;
      
	if(!rpcHitZ_.empty()){
	  //std::cout<<"rpcHitZ is not empty"<<std::endl;
	  track.rpcHitZ = rpcHitZ_;
	  track.rpcHitRho = rpcHitRho_;
	  track.rpcHitPhi = rpcHitPhi_;
	  track.rpcHitRegion = rpcHitRegion_;
	  track.rpcHitBx = rpcHitBx_;
	  //std::cout<<"filled track rpc Hit variables"<<std::endl;
	}
	
	event_->addStandAloneMuon(track);
      }//end of if track is standalone muon
    }//end of loop over sorted track pt
    //std::cout<<"done looping over sorted track pt"<<std::endl;
  }
  else {
    if (!muonsMissing_) edm::LogWarning("MissingProduct") << "StandAloneMuons not found.  Branch will not be filled" << std::endl;
    muonsMissing_ = true;
  }

  //std::cout<<"finished standalone muons"<<std::endl;  
} // void StoppedHSCPMuonTreeProducer::doStandAloneMuons()


void StoppedHSCPMuonTreeProducer::doRefittedStandAloneMuons(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
  //std::cout<<"started refitted standalone muons"<<std::endl;  
  // loop over refitted standalone muons
  edm::Handle<reco::TrackCollection> refittedStandAloneMuons;
  iEvent.getByLabel(refittedStandAloneMuonTag_,refittedStandAloneMuons);

  if (refittedStandAloneMuons.isValid()) {
    // sort muon tracks by pt
    std::vector<Track> refittedStandAloneMuons_;
    refittedStandAloneMuons_.insert(refittedStandAloneMuons_.end(), refittedStandAloneMuons->begin(), refittedStandAloneMuons->end());
    std::sort(refittedStandAloneMuons_.begin(), refittedStandAloneMuons_.end(), track_pt() );

    for(reco::TrackCollection::const_iterator it =refittedStandAloneMuons_.begin();
	it!=refittedStandAloneMuons_.end();
	it++) {
      //reco::TrackRef refittedStandAloneTrack = it->standAloneMuon();

      shscp::Track track;

      track.charge = it->charge();
      track.px = it->px();
      track.py = it->py();
      track.pz = it->pz();
      track.pt = it->pt();
      track.p = it->p();
      track.eta = it->eta();
      track.phi = it->phi();
      track.hcalEta = 0.;  // TODO extrapolate GlobalMuon track to HCAL surface and store position!
      track.hcalPhi = 0.;
      track.chi2  = it->chi2();
      track.ndof  = it->ndof();
      track.normalizedChi2  = it->normalizedChi2();
      track.dxy = it->dxy();
      track.dz = it->dz();
      track.nHits = it->numberOfValidHits();
      track.nLost = it->numberOfLostHits();

      //int muonStations (int subdet, int hitType) const
      //subdet = 0(all), 1(DT), 2(CSC), 3(RPC); hitType=-1(all), 0=valid, 3=bad 
      //track.nHitsMuonStations = it->hitPattern().muonStations(0,0);
      track.nStations = it->hitPattern().muonStationsWithValidHits(); //muon stations in refitted SAmuon track; same varaible as hitPattern().muonStations(0,0)
      track.nChambersCsc = it->hitPattern().cscStationsWithValidHits(); //csc chambers in refitted SAmuon track
      track.nChambersDt = it->hitPattern().dtStationsWithValidHits(); //dt chambers in refitted SAmuon track
      track.nChambersRpc = it->hitPattern().rpcStationsWithValidHits(); //rpc chambers in refitted SAmuon track
      track.nHitsMuon = it->hitPattern().numberOfValidMuonHits(); //muon hits included in the refitted SAmuon track fit 
      track.nHitsCsc = it->hitPattern().numberOfValidMuonCSCHits(); //CSC hits included in the refitted SAmuon track fit 
      track.nHitsDt = it->hitPattern().numberOfValidMuonDTHits(); //DT hits included in the refitted SAmuon track fit 
      track.nHitsRpc = it->hitPattern().numberOfValidMuonRPCHits(); //RPC hits included in the refitted SAmuon track fit 

      reco::TrackBase::TrackQuality q = reco::TrackBase::qualityByName("highPurity");
      track.quality = (it->quality(q) ? 1 : 0);

      //matching gen particle index
      //if data, gen particle index will be -1; if no matched gen particle, index will be -999
      int GenParticleIndex = -1;
      if(isMC_) GenParticleIndex = getGenParticleMatch(iEvent, it);
      track.genParticleIndex = GenParticleIndex;

      //matching Trigger particle index
      //if data, Trigger particle index will be -1; if no matched Trigger particle, index will be -999
      int TriggerParticle20Index = -1;
      if(!isMC_) TriggerParticle20Index = getTriggerObjectMatch20(iEvent, it);
      track.triggerParticle20Index = TriggerParticle20Index;

      //matching Trigger particle index
      //if data, Trigger particle index will be -1; if no matched Trigger particle, index will be -999
      int TriggerParticle20Cha2Index = -1;
      if(!isMC_) TriggerParticle20Cha2Index = getTriggerObjectMatch20Cha2(iEvent, it);
      track.triggerParticle20Cha2Index = TriggerParticle20Cha2Index;

      std::vector<int> cscSegEndcap_;
      std::vector<int> cscSegRing_;
      std::vector<int> cscSegStation_;
      std::vector<int> cscSegChamber_;
      std::vector<int> cscSegNHits_;
      std::vector<double> cscSegPhi_;
      std::vector<double> cscSegZ_;
      std::vector<double> cscSegR_;
      std::vector<double> cscSegDirPhi_;
      std::vector<double> cscSegDirTheta_;
      std::vector<double> cscSegTime_;
      //doCscSegments(iEvent, iSetup, it, cscSegEndcap_, cscSegRing_, cscSegStation_, cscSegChamber_, cscSegNHits_, cscSegPhi_, cscSegZ_, cscSegR_, cscSegDirPhi_, cscSegDirTheta_, cscSegTime_);
      //track.cscSegEndcap = cscSegEndcap_;
      //track.cscSegRing = cscSegRing_;
      //track.cscSegStation = cscSegStation_;
      //track.cscSegChamber = cscSegChamber_;
      //track.cscSegNHits = cscSegNHits_;
      //track.cscSegPhi = cscSegPhi_;
      //track.cscSegZ = cscSegZ_;
      //track.cscSegR = cscSegR_;
      //track.cscSegDirPhi = cscSegDirPhi_;
      //track.cscSegDirTheta = cscSegDirTheta_;
      //track.cscSegTime = cscSegTime_;
      
      event_->addRefittedStandAloneMuon(track);
    }
  }
  else {
    if (!muonsMissing_) edm::LogWarning("MissingProduct") << "RefittedStandAloneMuons not found.  Branch will not be filled" << std::endl;
    muonsMissing_ = true;
  }

  //std::cout<<"finished refitted standalone muons"<<std::endl;  
} // void StoppedHSCPMuonTreeProducer::doRefittedStandAloneMuons()
  



void StoppedHSCPMuonTreeProducer::doVertices(const edm::Event& iEvent, const reco::Vertex::Point& PV) {

  edm::Handle<reco::VertexCollection> recoVertices;
  iEvent.getByLabel(verticesTag_, recoVertices);

  event_->nVtx=0;
  if (recoVertices.isValid()) {
    for(reco::VertexCollection::const_iterator it=recoVertices->begin();
	it!=recoVertices->end();
	++it) {
      
      if (!it->isFake()) { //original from stopped HSCP code
      //if (!it->isFake() && it->ndof() > 4 && fabs(it->z()) <= 24. && it->position().rho() <= 2.) { //standard? identification of primary vertex --> take first one in collection (from Zeynep & black holes)
	if(event_->nVtx==0) const reco::Vertex::Point PV = (*it).position();
	event_->vtxNDOF.push_back(it->ndof());
	event_->vtxZ.push_back(it->z());
	event_->vtxRho.push_back(it->position().rho());
	event_->nVtx++;
	event_->vtx_N++;
      }
    }
  }
  else {
    if (!verticesMissing_) {
      edm::LogWarning("MissingProduct") << "Vertices not found.  Branch will not be filled" << std::endl;
      verticesMissing_=true;
    }
  }
  //std::cout<<"PV is: "<<PV<<std::endl;
  
} // void StoppedHSCPMuonTreeProducer::doVertices(const edm::Event& iEvent)


void StoppedHSCPMuonTreeProducer::doTracks(const edm::Event& iEvent, const edm::EventSetup& iSetup) {

  edm::Handle<reco::TrackCollection> recoTracks;
  iEvent.getByLabel(tracksTag_, recoTracks);
 
  edm::ESHandle<TransientTrackBuilder> builder;
  iSetup.get<TransientTrackRecord>().get("TransientTrackBuilder",builder);
  theTTBuilder_ = builder.product();
  iSetup.get<IdealMagneticFieldRecord>().get(theMF_); 
  

  TrackCollection::const_iterator trk;
  for (trk=recoTracks->begin(); trk!=recoTracks->end(); ++trk) {
    shscp::Track track;
    track.chi2  = trk->chi2();
    track.ndof  = trk->ndof();
    track.nHits = trk->numberOfValidHits();
    track.nLost = trk->numberOfLostHits();
    track.p     = trk->p();

    reco::TrackBase::TrackQuality q = reco::TrackBase::qualityByName("highPurity");
    track.quality = (trk->quality(q) ? 1 : 0);

//     bool muontrackavailable = false;
//     edm::Ref<TrackCollection> muontrack = (&*it)->globalTrack();
//     if (muontrack.isNonnull()) { 
//       muontrackavailable = true; 
//     } 
//     else {
//       muontrack = (&*it)->innerTrack();
//       if (muontrack.isNonnull()) { 
// 	muontrackavailable = true; 
//       } 
//       else {
// 	muontrack = (&*it)->outerTrack();
// 	if (muontrack.isNonnull()) { 
// 	  muontrackavailable = true; 
// 	}
//       }
//     }
    
//     if (muontrackavailable) {

    // This doesn't work -- causes occasional crashes.  Jeff, Jan 27.
    /*
    TransientTrack theTransientTrack = theTTBuilder_->build(&*trk);
    const TrajectoryStateOnSurface myTSOS = theTransientTrack.innermostMeasurementState();
    if ( myTSOS.isValid() ) { 
      stateAtHCAL_= forwardPropagator_->propagate( myTSOS, *theHCALbarrel_ );
      if (stateAtHCAL_.isValid()) {
	track.hcalEta = stateAtHCAL_.globalDirection().eta();
	track.hcalPhi = stateAtHCAL_.globalDirection().phi();
      } 
    } 
    */
    event_->addTrack(track);
  }

}

//TOF Checks
void StoppedHSCPMuonTreeProducer::doTOF(const edm::Event& iEvent) {
  
  // get handle on Muons
  edm::Handle<reco::MuonCollection> muons;
  iEvent.getByLabel(muonTag_,muons);
  reco::MuonCollection Muons = *muons;

  // get handle on MuonTimeExtraMap
  edm::Handle<reco::MuonTimeExtraMap> TOFCollH;
  iEvent.getByLabel("muons","combined",TOFCollH);

  // sort muons by pt
  //std::sort(muons_.begin(), muons_.end(), muon_pt() );
  //std::cout<<"starting to sort by track pt"<<std::endl;
  //sort muons by track pt
  std::vector< std::pair<float, int> > trackPt;
  int count = 0;
  for(reco::MuonCollection::const_iterator it=muons->begin();it!=muons->end();it++) {      
    if (it->isStandAloneMuon()) {	
      reco::TrackRef standAloneTrack = it->standAloneMuon();	
      
      std::pair<float, int> a;
      a.first = standAloneTrack->pt();
      a.second = count;
      
      trackPt.push_back(a);
    }
    count++;
  }
  std::sort(trackPt.begin(), trackPt.end());
  
  // Check that collections are valid
  if (muons.isValid() && TOFCollH.isValid()) {
    
    // Loop over all muons
    //for(unsigned int imucount=0; imucount < muons->size(); ++imucount) {
    for (int i=trackPt.size()-1; i>=0; i--){

      if (Muons[trackPt[i].second].isStandAloneMuon()){      
	// Get current muon reference, Get current MuonTimeExtra from MuonTimeExtraMap
	reco::MuonRef muonR(muons,trackPt[i].second);
	const reco::MuonTimeExtra* tof = &TOFCollH->get(muonR.key());
	
	// does this muon meet requirements
	if (tof->nDof()>GlobalMinNDOF_  &&
	    tof->inverseBeta()>GlobalMinTOF_ && 
	    tof->inverseBetaErr()<GlobalMaxTOFErr_) {
	  
	  shscp::MuonTOFMap muontof;
	  
	  // Store TOF Variables
	  muontof.direction = tof->direction();
	  muontof.nDof = tof->nDof();
	  muontof.inverseBeta = tof->inverseBeta();
	  muontof.inverseBetaErr = tof->inverseBetaErr();
	  muontof.freeInverseBeta = tof->freeInverseBeta();
	  muontof.freeInverseBetaErr = tof->freeInverseBetaErr();
	  muontof.timeAtIpInOut = tof->timeAtIpInOut();
	  muontof.timeAtIpInOutErr = tof->timeAtIpInOutErr();
	  muontof.timeAtIpOutIn = tof->timeAtIpOutIn();
	  muontof.timeAtIpOutInErr = tof->timeAtIpOutInErr();

	  event_->addMuonTOFMap(muontof);
	}
      }   
    }
  }
  else {
    if (!muonsMissing_) edm::LogWarning("MissingProduct") << "HSCParticleCollection not found.  Branch will not be filled" << std::endl;
    muonsMissing_ = true;    
  } 
}

//DTTOF Checks
void StoppedHSCPMuonTreeProducer::doTOFDT(const edm::Event& iEvent) {
  
  // get handle on Muons
  edm::Handle<reco::MuonCollection> muons;
  iEvent.getByLabel(muonTag_,muons);
  reco::MuonCollection Muons = *muons;
  
  // get handle on MuonTimeExtraMap
  edm::Handle<reco::MuonTimeExtraMap> DTTOFCollH;
  iEvent.getByLabel("muons","dt",DTTOFCollH);

  // sort muons by pt
  //std::sort(muons_.begin(), muons_.end(), muon_pt() );
  //std::cout<<"starting to sort by track pt"<<std::endl;
  //sort muons by track pt
  std::vector< std::pair<float, int> > trackPt;
  int count = 0;
  for(reco::MuonCollection::const_iterator it=muons->begin();it!=muons->end();it++) {      
    if (it->isStandAloneMuon()) {	
      reco::TrackRef standAloneTrack = it->standAloneMuon();	
      
      std::pair<float, int> a;
      a.first = standAloneTrack->pt();
      a.second = count;
      
      trackPt.push_back(a);
    }
    count++;
  }
  std::sort(trackPt.begin(), trackPt.end());
  
  // Check that collections are valid
  if (muons.isValid() && DTTOFCollH.isValid()) {
    
    // Loop over all muons
    //for(unsigned int imucount=0; imucount < muons->size(); ++imucount) {
    for (int i=trackPt.size()-1; i>=0; i--){

      if (Muons[trackPt[i].second].isStandAloneMuon()){
	// Get current muon reference, Get current MuonTimeExtra from MuonTimeExtraMap
	reco::MuonRef muonR(muons,trackPt[i].second);
	const reco::MuonTimeExtra* tofdt = &DTTOFCollH->get(muonR.key());
	
	// does this HSCP meet requirements
	if (tofdt->nDof()>GlobalMinNDOFDT_  &&
	    tofdt->inverseBeta()>GlobalMinTOF_ && 
	    tofdt->inverseBetaErr()<GlobalMaxTOFErr_) {
	  
	  shscp::MuonTOFMap muondttof;
	  
	  // Store TOF Variables
	  muondttof.direction = tofdt->direction();
	  muondttof.nDof = tofdt->nDof();
	  muondttof.inverseBeta = tofdt->inverseBeta();
	  muondttof.inverseBetaErr = tofdt->inverseBetaErr();
	  muondttof.freeInverseBeta = tofdt->freeInverseBeta();
	  muondttof.freeInverseBetaErr = tofdt->freeInverseBetaErr();
	  muondttof.timeAtIpInOut = tofdt->timeAtIpInOut();
	  muondttof.timeAtIpInOutErr = tofdt->timeAtIpInOutErr();
	  muondttof.timeAtIpOutIn = tofdt->timeAtIpOutIn();
	  muondttof.timeAtIpOutInErr = tofdt->timeAtIpOutInErr();
	  
	  event_->addMuonTOFDTMap(muondttof);
	}
      }   
    }
  }
  else {
    if (!muonsMissing_) edm::LogWarning("MissingProduct") << "HSCParticleCollection not found.  Branch will not be filled" << std::endl;
    muonsMissing_ = true;    
  } 
  
}

//CSCTOF Checks
void StoppedHSCPMuonTreeProducer::doTOFCSC(const edm::Event& iEvent) {
  
  // get handle on Muons
  edm::Handle<reco::MuonCollection> muons;
  iEvent.getByLabel(muonTag_,muons);
  reco::MuonCollection Muons = *muons;
  
  // get handle on MuonTimeExtraMap
  edm::Handle<reco::MuonTimeExtraMap> CSCTOFCollH;
  iEvent.getByLabel("muons","csc",CSCTOFCollH);
  
  // sort muons by pt
  //std::sort(muons_.begin(), muons_.end(), muon_pt() );
  //std::cout<<"starting to sort by track pt"<<std::endl;
  //sort muons by track pt
  std::vector< std::pair<float, int> > trackPt;
  int count = 0;
  for(reco::MuonCollection::const_iterator it=muons->begin();it!=muons->end();it++) {      
    if (it->isStandAloneMuon()) {	
      reco::TrackRef standAloneTrack = it->standAloneMuon();	
      
      std::pair<float, int> a;
      a.first = standAloneTrack->pt();
      a.second = count;
      
      trackPt.push_back(a);
    }
    count++;
  }
  std::sort(trackPt.begin(), trackPt.end());
  
  // Check that collections are valid
  if (muons.isValid() && CSCTOFCollH.isValid()) {
    
    // Loop over all muons
    //for(unsigned int imucount=0; imucount < muons->size(); ++imucount) {
    for (int i=trackPt.size()-1; i>=0; i--){

      if (Muons[trackPt[i].second].isStandAloneMuon()){
	// Get current muon reference, Get current MuonTimeExtra from MuonTimeExtraMap
	reco::MuonRef muonR(muons,trackPt[i].second);
	const reco::MuonTimeExtra* tofcsc = &CSCTOFCollH->get(muonR.key());
	
	// does this HSCP meet requirements
	if (tofcsc->nDof()>GlobalMinNDOFCSC_  &&
	    tofcsc->inverseBeta()>GlobalMinTOF_ && 
	    tofcsc->inverseBetaErr()<GlobalMaxTOFErr_) {

	  shscp::MuonTOFMap muoncsctof;
	  
	  // Store TOF Variables
	  muoncsctof.direction = tofcsc->direction();
	  muoncsctof.nDof = tofcsc->nDof();
	  muoncsctof.inverseBeta = tofcsc->inverseBeta();
	  muoncsctof.inverseBetaErr = tofcsc->inverseBetaErr();
	  muoncsctof.freeInverseBeta = tofcsc->freeInverseBeta();
	  muoncsctof.freeInverseBetaErr = tofcsc->freeInverseBetaErr();
	  muoncsctof.timeAtIpInOut = tofcsc->timeAtIpInOut();
	  muoncsctof.timeAtIpInOutErr = tofcsc->timeAtIpInOutErr();
	  muoncsctof.timeAtIpOutIn = tofcsc->timeAtIpOutIn();
	  muoncsctof.timeAtIpOutInErr = tofcsc->timeAtIpOutInErr();
	  
	  event_->addMuonTOFCSCMap(muoncsctof);
	}
      }   
    }
  }
  else {
    if (!muonsMissing_) edm::LogWarning("MissingProduct") << "HSCParticleCollection not found.  Branch will not be filled" << std::endl;
    muonsMissing_ = true;    
  } 
  
}

//REFIT TOF Checks
void StoppedHSCPMuonTreeProducer::doREFITTOF(const edm::Event& iEvent) {
 
  // get handle on Muon Collection
  edm::Handle<reco::MuonCollection> muons;
  iEvent.getByLabel(muonTag_,muons);
  reco::MuonCollection Muons = *muons;
  
  // get handle on MuonTimeExtraMap
  edm::Handle<reco::MuonTimeExtraMap> REFITTOFCollH;
  iEvent.getByLabel("muontiming","combined",REFITTOFCollH);
  
  // sort muons by pt
  //std::sort(muons_.begin(), muons_.end(), muon_pt() );
  //std::cout<<"starting to sort by track pt"<<std::endl;
  //sort muons by track pt
  std::vector< std::pair<float, int> > trackPt;
  int count = 0;
  for(reco::MuonCollection::const_iterator it=muons->begin();it!=muons->end();it++) {      
    if (it->isStandAloneMuon()) {	
      reco::TrackRef standAloneTrack = it->standAloneMuon();	
      
      std::pair<float, int> a;
      a.first = standAloneTrack->pt();
      a.second = count;
      
      trackPt.push_back(a);
    }
    count++;
  }
  std::sort(trackPt.begin(), trackPt.end());
  
  // Check that collections are valid
  if (muons.isValid() && REFITTOFCollH.isValid()) {
    
    // Loop over all muons
    //for(unsigned int imucount=0; imucount < muons->size(); ++imucount) {
    for (int i=trackPt.size()-1; i>=0; i--){

      if (Muons[trackPt[i].second].isStandAloneMuon()){
	// Get current muon reference, Get current MuonTimeExtra from MuonTimeExtraMap
	reco::MuonRef muonR(muons,trackPt[i].second);
	const reco::MuonTimeExtra* tof = &REFITTOFCollH->get(muonR.key());
	
	// does this muon meet requirements
	if (tof->nDof()>GlobalMinNDOF_  &&
	    tof->inverseBeta()>GlobalMinTOF_ && 
	    tof->inverseBetaErr()<GlobalMaxTOFErr_) {
	  
	  shscp::MuonTOFMap refittof;
	  
	  // Store TOF Variables
	  refittof.direction = tof->direction();
	  refittof.nDof = tof->nDof();
	  refittof.inverseBeta = tof->inverseBeta();
	  refittof.inverseBetaErr = tof->inverseBetaErr();
	  refittof.freeInverseBeta = tof->freeInverseBeta();
	  refittof.freeInverseBetaErr = tof->freeInverseBetaErr();
	  refittof.timeAtIpInOut = tof->timeAtIpInOut();
          refittof.timeAtIpInOutErr = tof->timeAtIpInOutErr();
          refittof.timeAtIpOutIn = tof->timeAtIpOutIn();
          refittof.timeAtIpOutInErr = tof->timeAtIpOutInErr();
		     
          event_->addREFITTOFMap(refittof);
	}
      }               
    }   
  }
  else {
    if (!muonsMissing_) edm::LogWarning("MissingProduct") << "MuonColection not found.  Branch will not be filled" << std::endl;
    muonsMissing_ = true;    
  } 
  
}

//REFIT DTTOF Checks
void StoppedHSCPMuonTreeProducer::doREFITTOFDT(const edm::Event& iEvent) {
 
  // get handle on Muon Collection
  edm::Handle<reco::MuonCollection> muons;
  iEvent.getByLabel(muonTag_,muons);
  reco::MuonCollection Muons = *muons;
  
  // get handle on MuonTimeExtraMap
  edm::Handle<reco::MuonTimeExtraMap> REFITDTTOFCollH;
  iEvent.getByLabel("muontiming","dt",REFITDTTOFCollH);
  
  // sort muons by pt
  //std::sort(muons_.begin(), muons_.end(), muon_pt() );
  //std::cout<<"starting to sort by track pt"<<std::endl;
  //sort muons by track pt
  std::vector< std::pair<float, int> > trackPt;
  int count = 0;
  for(reco::MuonCollection::const_iterator it=muons->begin();it!=muons->end();it++) {      
    if (it->isStandAloneMuon()) {	
      reco::TrackRef standAloneTrack = it->standAloneMuon();	
      
      std::pair<float, int> a;
      a.first = standAloneTrack->pt();
      a.second = count;
      
      trackPt.push_back(a);
    }
    count++;
  }
  std::sort(trackPt.begin(), trackPt.end());
  
  // Check that collections are valid
  if (muons.isValid() && REFITDTTOFCollH.isValid()) {
    
    // Loop over all muons
    //for(unsigned int imucount=0; imucount < muons->size(); ++imucount) {
    for (int i=trackPt.size()-1; i>=0; i--){

      if (Muons[trackPt[i].second].isStandAloneMuon()){
	// Get current muon reference, Get current MuonTimeExtra from MuonTimeExtraMap
	reco::MuonRef muonR(muons,trackPt[i].second);
	const reco::MuonTimeExtra* dttof = &REFITDTTOFCollH->get(muonR.key());
	     
	// does this muon meet requirements
	if (dttof->nDof()>GlobalMinNDOFDT_  &&
	    dttof->inverseBeta()>GlobalMinTOF_ && 
	    dttof->inverseBetaErr()<GlobalMaxTOFErr_) {
	  
	  shscp::MuonTOFMap refitdttof;
	  
	  // Store TOF Variables
	  refitdttof.direction = dttof->direction();
	  refitdttof.nDof = dttof->nDof();
	  refitdttof.inverseBeta = dttof->inverseBeta();
	  refitdttof.inverseBetaErr = dttof->inverseBetaErr();
	  refitdttof.freeInverseBeta = dttof->freeInverseBeta();
	  refitdttof.freeInverseBetaErr = dttof->freeInverseBetaErr();
	  refitdttof.timeAtIpInOut = dttof->timeAtIpInOut();
	  refitdttof.timeAtIpInOutErr = dttof->timeAtIpInOutErr();
	  refitdttof.timeAtIpOutIn = dttof->timeAtIpOutIn();
	  refitdttof.timeAtIpOutInErr = dttof->timeAtIpOutInErr();
	  
	  event_->addREFITTOFDTMap(refitdttof);
	}
      }
    }   
  }
  else {
    if (!muonsMissing_) edm::LogWarning("MissingProduct") << "MuonCollection not found.  Branch will not be filled" << std::endl;
    muonsMissing_ = true;    
  } 
  
}

//REFIT CSCTOF Checks
void StoppedHSCPMuonTreeProducer::doREFITTOFCSC(const edm::Event& iEvent) {
 
  // get handle on Muon Collection
  edm::Handle<reco::MuonCollection> muons;
  iEvent.getByLabel(muonTag_,muons);
  reco::MuonCollection Muons = *muons;
  
  // get handle on MuonTimeExtraMap
  edm::Handle<reco::MuonTimeExtraMap> REFITCSCTOFCollH;
  iEvent.getByLabel("muontiming","csc",REFITCSCTOFCollH);

  // sort muons by pt
  //std::sort(muons_.begin(), muons_.end(), muon_pt() );
  //std::cout<<"starting to sort by track pt"<<std::endl;
  //sort muons by track pt
  std::vector< std::pair<float, int> > trackPt;
  int count = 0;
  for(reco::MuonCollection::const_iterator it=muons->begin();it!=muons->end();it++) {      
    if (it->isStandAloneMuon()) {	
      reco::TrackRef standAloneTrack = it->standAloneMuon();	
      
      std::pair<float, int> a;
      a.first = standAloneTrack->pt();
      a.second = count;
      
      trackPt.push_back(a);
    }
    count++;
  }
  std::sort(trackPt.begin(), trackPt.end());
  
  // Check that collections are valid
  if (muons.isValid() && REFITCSCTOFCollH.isValid()) {
    
    // Loop over all muons
    //for(unsigned int imucount=0; imucount < muons->size(); ++imucount) {
    for (int i=trackPt.size()-1; i>=0; i--){

      if (Muons[trackPt[i].second].isStandAloneMuon()){
	// Get current muon reference, Get current MuonTimeExtra from MuonTimeExtraMap
	reco::MuonRef muonR(muons,trackPt[i].second);
	const reco::MuonTimeExtra* csctof = &REFITCSCTOFCollH->get(muonR.key());
	
	
	// does this muon meet requirements
	if (csctof->nDof()>GlobalMinNDOFDT_  &&
	    csctof->inverseBeta()>GlobalMinTOF_ && 
	    csctof->inverseBetaErr()<GlobalMaxTOFErr_) {
	  
	  shscp::MuonTOFMap refitcsctof;
	  
	  // Store TOF Variables
	  refitcsctof.direction = csctof->direction();
	  refitcsctof.nDof = csctof->nDof();
	  refitcsctof.inverseBeta = csctof->inverseBeta();
	  refitcsctof.inverseBetaErr = csctof->inverseBetaErr();
	  refitcsctof.freeInverseBeta = csctof->freeInverseBeta();
	  refitcsctof.freeInverseBetaErr = csctof->freeInverseBetaErr();
	  refitcsctof.timeAtIpInOut = csctof->timeAtIpInOut();
	  refitcsctof.timeAtIpInOutErr = csctof->timeAtIpInOutErr();
	  refitcsctof.timeAtIpOutIn = csctof->timeAtIpOutIn();
	  refitcsctof.timeAtIpOutInErr = csctof->timeAtIpOutInErr();
	  
	  event_->addREFITTOFCSCMap(refitcsctof);
	}
      }
    }   
  }
  else {
    if (!muonsMissing_) edm::LogWarning("MissingProduct") << "MuonCollection not found.  Branch will not be filled" << std::endl;
    muonsMissing_ = true;    
  } 
  
}


void StoppedHSCPMuonTreeProducer::doMuonDTs(const edm::Event& iEvent, const edm::EventSetup& iSetup,  std::vector<DTRecHit1D>& DTRecHits)
{

  //std::cout<<"started DTs"<<std::endl;  

  if (doDT_==false) return;
  
  edm::ESHandle<DTGeometry> dtGeom;
  iSetup.get<MuonGeometryRecord>().get(dtGeom);

  edm::Handle<DTRecSegment4DCollection> all4DSegments;
  iEvent.getByLabel(DT4DSegmentsTag_, all4DSegments);
  edm::Handle<DTRecHitCollection> dtRecHits;
  iEvent.getByLabel(DTRecHitsTag_,dtRecHits);

  int nsegments=0; // count total number of segments

  // loop over each DT chamber
  DTRecSegment4DCollection::id_iterator chamberId;
  for (chamberId = all4DSegments->id_begin();
       chamberId != all4DSegments->id_end();
       ++chamberId)
    {
      const DTChamber* chamber = dtGeom->chamber(*chamberId); 

      DTRecSegment4DCollection::range range = all4DSegments->get(*chamberId);
      int nchamberseg=0;

      // loop over all segments in chamber
      for (DTRecSegment4DCollection::const_iterator segment4D = range.first;
	   segment4D!=range.second;
	   ++segment4D)
	{
	  // skip invalid values

	  if((*chamberId).station() != 4 && 
	     (*segment4D).dimension() != 4) continue;
	  if((*chamberId).station() == 4 && 
	     (*segment4D).dimension() != 2) continue;

	  ++nchamberseg;

	  const GeomDet* gdet=dtGeom->idToDet(segment4D->geographicalId());
	  const BoundPlane& DTSurface = gdet->surface();
	  LocalPoint segmentLocal = (*segment4D).localPosition();
	  GlobalPoint segmentGlobal = gdet->toGlobal(segment4D->localPosition());

          std::vector<double> D1Phi_time;
          std::vector<double> D1Phi_phi;
          std::vector<double> D1Phi_eta;
          std::vector<double> D1Zed_time;
          std::vector<double> D1Zed_phi;
          std::vector<double> D1Zed_eta;

          if ( (*segment4D).hasPhi() ) {

	    std::vector<DTRecHit1D> D1PhiRecHits=(*segment4D).phiSegment()->specificRecHits();
	    //DTRecHits = D1PhiRecHits;
	    DTRecHits.insert(DTRecHits.end(),D1PhiRecHits.begin(),D1PhiRecHits.end());
	    for(unsigned int i=0;i<D1PhiRecHits.size();i++) {
              const DTLayer* layer=chamber->layer(D1PhiRecHits[i].wireId().layerId());
              GlobalPoint glbPointPhi=layer->toGlobal(D1PhiRecHits[i].localPosition());
              
              D1Phi_time.push_back(D1PhiRecHits[i].digiTime()); //Return the time (ns) of the digi used to build the rechit. 
              D1Phi_phi.push_back(glbPointPhi.phi());
              D1Phi_eta.push_back(glbPointPhi.eta());
            }
          }

          if ( (*segment4D).hasZed() ) {

	    std::vector<DTRecHit1D> D1ZedRecHits=(*segment4D).zSegment()->specificRecHits();
	    DTRecHits.insert(DTRecHits.end(),D1ZedRecHits.begin(),D1ZedRecHits.end());
	    for(unsigned int i=0;i<D1ZedRecHits.size();i++) {              
              const DTLayer* layer=chamber->layer(D1ZedRecHits[i].wireId().layerId());
              GlobalPoint glbPointZed=layer->toGlobal(D1ZedRecHits[i].localPosition());
              
              D1Zed_time.push_back(D1ZedRecHits[i].digiTime());
              D1Zed_phi.push_back(glbPointZed.phi());
              D1Zed_eta.push_back(glbPointZed.eta());
            }
          }

          shscp::DTD1RecHitCollection dtD1PhiRecHitCollection;

          dtD1PhiRecHitCollection.timeCollection = D1Phi_time;
          dtD1PhiRecHitCollection.phiCollection = D1Phi_phi;
          dtD1PhiRecHitCollection.etaCollection = D1Phi_eta;

          event_->addDTD1PhiRecHitCollection(dtD1PhiRecHitCollection);



          shscp::DTD1RecHitCollection dtD1ZedRecHitCollection;

          dtD1ZedRecHitCollection.timeCollection = D1Zed_time;
          dtD1ZedRecHitCollection.phiCollection = D1Zed_phi;
          dtD1ZedRecHitCollection.etaCollection = D1Zed_eta;

          event_->addDTD1ZedRecHitCollection(dtD1ZedRecHitCollection);



	  shscp::DTSegment dt;
	  dt.wheel=(chamber->id()).wheel();
	  dt.station=(chamber->id()).station();
	  dt.sector=(chamber->id()).sector();
	  dt.localX=segmentLocal.x();
	  dt.localY=segmentLocal.y();
	  dt.z=segmentGlobal.z();
	  dt.rho=segmentGlobal.perp();
	  dt.phi=segmentGlobal.phi();
	  dt.eta=segmentGlobal.eta();
	  event_->addDTSegment(dt);

	}
      nsegments+=nchamberseg;
    }
  //std::cout<<"finished DTs"<<std::endl;  
} // void StoppedHSCPMuonTreeProducer::doMuonDTs


void StoppedHSCPMuonTreeProducer::doMuonRPCs(const edm::Event& iEvent,const edm::EventSetup& iSetup )
{
  //std::cout<<"started RPCs"<<std::endl;  

  if (!doRpcRecHits_) return;
  //Jeff
  edm::Handle<RPCRecHitCollection> hits;
  iEvent.getByLabel(rpcRecHitsTag_, hits);
  edm::ESHandle<RPCGeometry> rpcGeom;
  iSetup.get<MuonGeometryRecord>().get(rpcGeom);
  
  //int nRecHits = hits->size();
  int iHit = 0;
  RPCRecHitCollection::const_iterator rpcIter;
  for (rpcIter = hits->begin(); rpcIter != hits->end(); ++rpcIter) {
    ++iHit;
    const RPCDetId detId = static_cast<const RPCDetId>(rpcIter->rpcId());
    const RPCRoll* roll = dynamic_cast<const RPCRoll*>(rpcGeom->roll(detId));
    const GlobalPoint rhitglobal = roll->toGlobal(rpcIter->localPosition());

    shscp::RpcHit h;
    h.z = rhitglobal.z();
    h.rho = rhitglobal.perp();
    h.phi = rhitglobal.phi();
    h.region = detId.region();
    //h.bx = rpcIter->BunchX(); //bunch crossing relative to the L1 accept
    event_->addRpcHit (h);
  } // loop on rpc hits
  //std::cout<<"finished RPCs"<<std::endl;  
} // void StoppedHSCPMuonTreeProducer::doMuonRPCs

void StoppedHSCPMuonTreeProducer::doBeamHalo(const edm::Event& iEvent)
{
    
  edm::Handle<BeamHaloSummary> TheBeamHaloSummary;
  iEvent.getByLabel("BeamHaloSummary",TheBeamHaloSummary);
  bool beamhalo_csctight=false;
  bool beamhalo_cscloose=false;
  bool beamhalo_hcaltight=false;
  bool beamhalo_hcalloose=false;

  if (TheBeamHaloSummary.isValid())
    {
      const BeamHaloSummary TheSummary = (*TheBeamHaloSummary.product() );
      if (TheSummary.CSCTightHaloId()==true)  beamhalo_csctight = true; 
      if (TheSummary.CSCLooseHaloId()==true)  beamhalo_cscloose = true; 
      if (TheSummary.HcalTightHaloId()==true)  beamhalo_hcaltight = true; 
      if (TheSummary.HcalLooseHaloId()==true)  beamhalo_hcalloose = true; 
    }
  event_->beamHalo_CSCTight=beamhalo_csctight;
  event_->beamHalo_CSCLoose=beamhalo_cscloose;
  event_->beamHalo_HcalTight=beamhalo_hcaltight;
  event_->beamHalo_HcalLoose=beamhalo_hcalloose;

  return;
} // void StoppedHSCPMuonTreeProducer::doBeamHalo(iEvent)


/*
// global calo based quantities
void StoppedHSCPMuonTreeProducer::doGlobalCalo(const edm::Event& iEvent) {

  event_->nTowerSameiPhi=0;
  event_->leadingIPhiFractionValue=0;

  // get calo towers
  edm::Handle<CaloTowerCollection> caloTowers;
  iEvent.getByLabel(caloTowerTag_,caloTowers);

  if (caloTowers.isValid()) {
    std::vector<CaloTower> caloTowersTmp;
    caloTowersTmp.insert(caloTowersTmp.end(), caloTowers->begin(), caloTowers->end());
    sort(caloTowersTmp.begin(), caloTowersTmp.end(), calotower_gt());
    
    if(caloTowersTmp.size()>0){
      int iphiFirst=caloTowersTmp.begin()->iphi();
      bool keepgoing=true;
      for(std::vector<CaloTower>::const_iterator twr = caloTowersTmp.begin();
	  twr!=caloTowersTmp.end() && keepgoing;
	  ++twr) {
	
	if (fabs(twr->eta()) < towerMaxEta_) {	
	  
	  // tower same iphi as leading tower
	  if (twr->iphi()==iphiFirst) {
	    event_->nTowerSameiPhi++;
	    event_->nTowerLeadingIPhi++;
	    event_->eHadLeadingIPhi += twr->hadEnergy();
	  }
	  else {
	    keepgoing=false;
	  }
	}  
      } // loop on caloTowers
    }
    event_->leadingIPhiFractionValue=event_->leadingIPhiFraction();
  }
  else {
    if (!towersMissing_) edm::LogWarning("MissingProduct") << "CaloTowers not found.  Branches will not be filled" << std::endl;
    towersMissing_ = true;
  }

} // void StoppedHSCPMuonTreeProducer::doGlobalCalo(const edm::Event& iEvent)
*/


void StoppedHSCPMuonTreeProducer::doHcalNoise(const edm::Event& iEvent) {
  
  // get noise summary
  edm::Handle<HcalNoiseSummary> summary;
  iEvent.getByLabel(hcalNoiseTag_,summary);

  if (summary.isValid()) {
    event_->noiseMinE2Over10TS = summary->minE2Over10TS();
    event_->noiseMaxE2Over10TS = summary->maxE2Over10TS();
    event_->noiseMaxHPDHits = summary->maxHPDHits();
    event_->noiseMaxRBXHits = summary->maxRBXHits();
    event_->noiseMaxHPDNoOtherHits = summary->maxHPDNoOtherHits();
    event_->noiseMaxZeros = summary->maxZeros();
    event_->noiseMin25GeVHitTime = summary->min25GeVHitTime();
    event_->noiseMax25GeVHitTime = summary->max25GeVHitTime();
    event_->noiseMinRBXEMF = summary->minRBXEMF();

    event_->noiseEventEMEnergy = summary->eventEMEnergy();
    event_->noiseEventHadEnergy = summary->eventHadEnergy();
    event_->noiseEventTrackEnergy = summary->eventTrackEnergy();
    event_->noiseNumProblematicRBXs = summary->numProblematicRBXs();
    // The following only work in 3_11_X (?) and above
    //event_->noiseNumIsolatedNoiseChannels = summary->numIsolatedNoiseChannels();
    //event_->noiseIsolatedNoiseSumEt = summary->isolatedNoiseSumEt();
  }
  else {
    if (!noiseSumMissing_) edm::LogWarning("MissingProduct") << "HCALNoiseSummary not found.  Branch will not be filled" << std::endl;
    noiseSumMissing_ = true;
  }

  // get noise filter flag
  edm::Handle<bool> flag;
  iEvent.getByLabel(hcalNoiseFilterResultTag_,flag);

  event_->noiseFilterResult = true;
  if (flag.isValid()) {
    event_->noiseFilterResult = (*flag.product());
  }
  else {
    edm::LogWarning("MissingProduct") << "No HBHE filter flag in Event" << std::endl;
  }


  // get RBX/HPD collection
  edm::Handle<HcalNoiseRBXCollection> rbxs;
  iEvent.getByLabel(rbxTag_,rbxs);
  
  if (rbxs.isValid()) 
    {
      // Store the HPD object with the largest total Charge; used that for forming noise variables
      shscp::HPD maxHPD;
      double maxCharge=0;

      for(HcalNoiseRBXCollection::const_iterator it = rbxs->begin(); 
	  it!=rbxs->end();
	  ++it) {
	
	std::vector<HcalNoiseHPD> hpds = it->HPDs();
	for (std::vector<HcalNoiseHPD>::const_iterator hpd = hpds.begin();
	     hpd!=hpds.end();
	     ++hpd) {
	  
	  shscp::HPD h;
	  h.id = hpd->idnumber();
	  h.totalZeros = hpd->totalZeros();
	  h.maxZeros = hpd->maxZeros();
	  h.nJet = 999;  // TODO - fill nJet
	  h.fc0 = hpd->bigCharge().at(0);
	  h.fc1 = hpd->bigCharge().at(1);
	  h.fc2 = hpd->bigCharge().at(2);
	  h.fc3 = hpd->bigCharge().at(3);
	  h.fc4 = hpd->bigCharge().at(4);
	  h.fc5 = hpd->bigCharge().at(5);
	  h.fc6 = hpd->bigCharge().at(6);
	  h.fc7 = hpd->bigCharge().at(7);
	  h.fc8 = hpd->bigCharge().at(8);
	  h.fc9 = hpd->bigCharge().at(9);
	  h.fc5_0 = hpd->big5Charge().at(0);
	  h.fc5_1 = hpd->big5Charge().at(1);
	  h.fc5_2 = hpd->big5Charge().at(2);
	  h.fc5_3 = hpd->big5Charge().at(3);
	  h.fc5_4 = hpd->big5Charge().at(4);
	  h.fc5_5 = hpd->big5Charge().at(5);
	  h.fc5_6 = hpd->big5Charge().at(6);
	  h.fc5_7 = hpd->big5Charge().at(7);
	  h.fc5_8 = hpd->big5Charge().at(8);
	  h.fc5_9 = hpd->big5Charge().at(9);
	  // Compute total charge for the "top5" of this HPD; compare to maxCharge
	  double totalCharge = 0;
	  totalCharge+= h.fc5_0+h.fc5_1+h.fc5_2+h.fc5_3+h.fc5_4;
	  totalCharge+= h.fc5_5+h.fc5_6+h.fc5_7+h.fc5_8+h.fc5_9;
	  if (totalCharge>maxCharge)
	    {
	      maxCharge=totalCharge;
	      //maxHPD=hpd;
	      maxHPD=h;
	    }
	  event_->addHPD(h);
	  
	} // loop on HPDs
      } // loop on RBXs
      // One maximum HPD has been found, compute NoiseSummary-based R values

      // Fill event vector "topHPD5TimeSamples" with "top5" charges from max HPD
      fillNoiseObjectTop5DigiSamples(maxHPD,event_->topHPD5TimeSamples);

      // Compute noise summary versions of R1, R2, etc. variables
      pulseShapeVariables(event_->topHPD5TimeSamples,
			  event_->topHPD5PeakSample,
			  event_->topHPD5Total,
			  event_->topHPD5R1,
			  event_->topHPD5R2,
			  event_->topHPD5RPeak,
			  event_->topHPD5ROuter);
    }
  else {
    if (!hpdsMissing_) edm::LogWarning("MissingProduct") << "HCALNoiseRBXCollection not found.  Branch will not be filled" << std::endl;
    hpdsMissing_ = true;
  }
  
}// doHcalNoise(...)


void StoppedHSCPMuonTreeProducer::fillNoiseObjectTop5DigiSamples(shscp::HPD& hpd, std::vector<double>& outvec)
{
  /* Fill a pulse shape vector with values from the "top5" digis in a single HPD.
     Only positive charge values are allowed; otherwise, the vector entry is 0.
  */
  outvec.clear();
  outvec.push_back(std::max(0.,hpd.fc5_0));
  outvec.push_back(std::max(0.,hpd.fc5_1));
  outvec.push_back(std::max(0.,hpd.fc5_2));
  outvec.push_back(std::max(0.,hpd.fc5_3));
  outvec.push_back(std::max(0.,hpd.fc5_4));
  outvec.push_back(std::max(0.,hpd.fc5_5));
  outvec.push_back(std::max(0.,hpd.fc5_6));
  outvec.push_back(std::max(0.,hpd.fc5_7));
  outvec.push_back(std::max(0.,hpd.fc5_8));
  outvec.push_back(std::max(0.,hpd.fc5_9));
  return;
}



void StoppedHSCPMuonTreeProducer::fillNoiseObjectTopDigiSamples(shscp::HPD& hpd, std::vector<double>& outvec)
{
  /* Fill a pulse shape vector with values from the digi with the largest charge in a single HPD.
     Only positive charge values are allowed; otherwise, the vector entry is 0.
  */
  outvec.clear();
  outvec.push_back(std::max(0.,hpd.fc0));
  outvec.push_back(std::max(0.,hpd.fc1));
  outvec.push_back(std::max(0.,hpd.fc2));
  outvec.push_back(std::max(0.,hpd.fc3));
  outvec.push_back(std::max(0.,hpd.fc4));
  outvec.push_back(std::max(0.,hpd.fc5));
  outvec.push_back(std::max(0.,hpd.fc6));
  outvec.push_back(std::max(0.,hpd.fc7));
  outvec.push_back(std::max(0.,hpd.fc8));
  outvec.push_back(std::max(0.,hpd.fc9));
  return;
}




/// fill rec hit 
void
StoppedHSCPMuonTreeProducer::doHcalRecHits(const edm::Event& iEvent)
{

  recHits_.clear();

  // get the rechits (to select digis ordered by energy)
  edm::Handle<HBHERecHitCollection> recHits;
  iEvent.getByLabel(hcalRecHitTag_, recHits);

  // copy rechits to internal vector
  if(recHits.isValid()) {
    
    // reject bad status rechits from collection
    for (HBHERecHitCollection::const_iterator it=recHits->begin();
	 it!=recHits->end();++it) {
      
      if (std::find(badChannels_.begin(),
		    badChannels_.end(),
		    it->id())!=badChannels_.end()) {
	continue;
      }

      recHits_.push_back(*it);
      
    }
  }
  else {
    if (!rechitsMissing_) edm::LogWarning("MissingProduct") << "CaloRecHits not found.  Branches will not be filled" << std::endl;
    rechitsMissing_ = true;
  }

  // sort by energy
  sort(recHits_.begin(), recHits_.end(), rechit_gt());
  
  // store to ntuple if required
  if (doRecHits_) {
    
    unsigned count=0;

    for (HBHERecHitCollection::const_iterator hit=recHits_.begin();
	 hit!=recHits_.end() && count < 6000;
	 ++hit, ++count) {
      
      GlobalPoint pos = caloGeom_->getPosition((*hit).detid());
      
      shscp::RecHit rh;
      
      rh.e = (*hit).energy();
      
      if (rh.e > rechitMinEnergy_ ) {
	
	rh.time  = (*hit).time();
	rh.flags = (*hit).flags();
	rh.aux   = (*hit).aux();
	rh.eta   = pos.eta();
	rh.phi   = pos.phi();
	rh.ieta  = (*hit).id().ieta();
	rh.iphi  = (*hit).id().iphi();
	rh.depth = (*hit).id().depth();
	rh.RBXindex = logicalMap_->getHcalFrontEndId(hit->detid()).rbxIndex();
	rh.RMindex  = logicalMap_->getHcalFrontEndId(hit->detid()).rm();
	event_->addRecHit(rh);

	count++;

      }
      
    }
    
  }
  
}


/// fill HF rec hit 
void
StoppedHSCPMuonTreeProducer::doHFRecHits(const edm::Event& iEvent)
{

  // get the rechits (to select digis ordered by energy)
  edm::Handle<HFRecHitCollection> recHits;
  iEvent.getByLabel(hfRecHitTag_, recHits);

  // copy rechits to internal vector
  if(recHits.isValid()) {

    unsigned count=0;
    
    for (HFRecHitCollection::const_iterator it=recHits->begin();
	 it!=recHits->end() && count<1000;
	 ++it) {

      // reject bad status rechits from collection      
//       if (std::find(badChannels_.begin(),
// 		    badChannels_.end(),
// 		    it->id())!=badChannels_.end()) {
// 	continue;
//       }

      GlobalPoint pos = caloGeom_->getPosition(it->detid());
      
      // store E sums for HF+ and HF-
      if (pos.eta()> 0. && it->energy() > rechitMinEnergy_ ) {
	event_->hfPlusTotalE += it->energy();
      }
      if (pos.eta()<0. && it->energy() > rechitMinEnergy_ ) {
	event_->hfMinusTotalE += it->energy();
      }

      if (doHFRecHits_ && it->energy() > rechitMinEnergy_ ) {

	shscp::RecHit rh;
	
	rh.e = it->energy();
	rh.time  = it->time();
	rh.eta   = pos.eta();
	rh.phi   = pos.phi();
	rh.ieta  = it->id().ieta();
	rh.iphi  = it->id().iphi();
	rh.depth = it->id().depth();
	event_->addHFRecHit(rh);

	count++;

      }      
    }

  }
  else {
    if (!rechitsMissing_) edm::LogWarning("MissingProduct") << "CaloRecHits not found.  Branches will not be filled" << std::endl;
    rechitsMissing_ = true;
  }

}


void StoppedHSCPMuonTreeProducer::doCscSegments(const edm::Event& iEvent, const edm::EventSetup& iSetup){

  // get the segments
  edm::Handle<CSCSegmentCollection> segments;
  iEvent.getByLabel(cscSegmentsTag_, segments);

  // Get the geometry :
  edm::ESHandle<CSCGeometry> cscGeom;
  iSetup.get<MuonGeometryRecord>().get(cscGeom);

  //std::cout<<"started doCscSegments"<<std::endl;
  if (doCscSegments_) {
    
    //std::cout<<"doing Csc segments"<<std::endl;
    // write segment info to ntuple
    if(segments.isValid()) {
    
    // get the CSC segments that were used to construct the muon track
    //std::vector<const CSCSegment*> range = segmentMatcher->matchCSC(*muonTrack,iEvent);
    
    unsigned i=0;
    for (CSCSegmentCollection::const_iterator seg=segments->begin();
      seg!=segments->end() && i<1000;
      ++seg, ++i) {

      //for (std::vector<const CSCSegment*>::iterator seg=range.begin(); seg!=range.end(); ++seg) {
      
      //if(segments.isValid()) {

	//std::cout<<"Csc segment is valid"<<std::endl;
	  
	/// code taken from RecoLocalMuon/CSCValidation/src/CSCValidation.cc
	CSCDetId id  = seg->cscDetId();
	LocalPoint localPos = seg->localPosition();
	LocalVector segDir = seg->localDirection();
	const GeomDet* cscDet = cscGeom->idToDet(seg->geographicalId());
	//GlobalPoint globalPos = cscGeom->chamber(id)->toGlobal(localPos);
	GlobalPoint globalPos = cscDet->toGlobal(seg->localPosition());
	GlobalVector globalVec = cscGeom->chamber(id)->toGlobal(segDir);
	//float chisq    = seg->chi2();
	//int nDOF       = 2*nhits-4;
	//double chisqProb = ChiSquaredProbability( (double)chisq, nDOF );
	//float segX     = localPos.x();
	//float segY     = localPos.y();
	//double theta   = segDir.theta();
	
	shscp::CscSegment s;
	s.endcap = id.endcap();
	s.ring = id.ring();
	s.station = id.station();
	s.chamber = id.chamber();
	s.nHits = seg->nRecHits();
	s.phi = globalPos.phi();
	s.eta = globalPos.eta();
	s.z = globalPos.z();
	s.r = sqrt((globalPos.x()*globalPos.x()) + (globalPos.y()*globalPos.y()));
	s.dirTheta = globalVec.theta();
	s.dirPhi = globalVec.phi();
	s.time = seg->time(); //ave of hit times (anodes and cathodes)
	
	event_->addCscSegment(s);
	
      }      
    }//end of loop over segments

    else {
      if (!cscSegsMissing_) edm::LogWarning("MissingProduct") << "CSC Segments not found.  Branches will not be filled" << std::endl;
      cscSegsMissing_ = true;
    }
  }

} // doCscSegments

void StoppedHSCPMuonTreeProducer::doCscHits(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
  if (!doCscRecHits_) return;
  
  edm::Handle<CSCRecHit2DCollection> hits;
  iEvent.getByLabel(cscRecHitsTag_, hits);
  edm::ESHandle<CSCGeometry> cscGeom;
  iSetup.get<MuonGeometryRecord>().get(cscGeom);
  
  //int nRecHits = hits->size();
  int iHit = 0;
  CSCRecHit2DCollection::const_iterator dRHIter;
  for (dRHIter = hits->begin(); dRHIter != hits->end(); dRHIter++) {
    if(dRHIter->isValid()){
      iHit++;
      CSCDetId idrec = (CSCDetId)(*dRHIter).cscDetId();
      // Following variables aren't yet used:
      //int kEndcap  = idrec.endcap();
      //int kRing    = idrec.ring();
      //int kStation = idrec.station();
      //int kChamber = idrec.chamber();
      //int kLayer   = idrec.layer();
      const CSCLayer* csclayer = cscGeom->layer( idrec );
      LocalPoint rhitlocal = (*dRHIter).localPosition();
      GlobalPoint rhitglobal= csclayer->toGlobal(rhitlocal);
      shscp::CscHit h;
      h.z = rhitglobal.z();
      h.rho = rhitglobal.perp();
      h.phi = rhitglobal.phi();
      //h.stripTime = dRHIter->tpeak(); //cathode strips --> slightly better resolution
      //h.wireTime = dRHIter->wireTime(); //anode wires
      event_->addCscHit (h);
    }
  }
} //doCscHits

/*
void StoppedHSCPMuonTreeProducer::doSlices (const edm::Event& iEvent, const edm::EventSetup& iSetup) {
  edm::Handle<CaloTowerCollection> towers;
  iEvent.getByLabel(caloTowerTag_, towers);
  for (int iPhi = 0; iPhi < 36; ++ iPhi) {
    int iAntiPhi = iPhi - 18;
    if (iAntiPhi < 0) iAntiPhi += 36;
    double phi = iPhi < 18 ? 3.1415/18.*(iPhi + 0.5) : 3.1415/18.*(iPhi -36 + 0.5);
    double energyPlus = 0;
    double antienergyPlus = 0;
    double energyMinus = 0;
    double antienergyMinus = 0;
    double energy = 0;
    double antienergy = 0;
    for (size_t itower = 0; itower < towers->size(); ++itower) {
      const CaloTower& tower = (*towers)[itower];
      CaloTowerDetId id = tower.id();
      if (id.ietaAbs() >= 17 && id.ietaAbs() <= 24) { // HE in front of HB
	if (id.iphi() > iPhi*2 && id.iphi() <= (iPhi+1)*2) {
	  if (id.zside() > 0) energyPlus += tower.hadEnergy();
	  else energyMinus += tower.hadEnergy();
	  energy += tower.hadEnergy();
	}
	else if (id.iphi() > iAntiPhi*2 && id.iphi() <= (iAntiPhi+1)*2) {
	  if (id.zside() > 0) antienergyPlus += tower.hadEnergy();
	  else antienergyMinus += tower.hadEnergy();
	  antienergy += tower.hadEnergy();
	}
      }
    }
    event_->addHePlus (energyPlus,  antienergyPlus, phi);
    event_->addHeMinus (energyMinus,  antienergyMinus, phi);
    event_->addHe (energy,  antienergy, phi);
  }
} // doSlices
*/
  
void StoppedHSCPMuonTreeProducer::doTimingFromDigis(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
 // this code taken from John Paul Chou's noise info producer
  // RecoMET/METProducers/src/HcalNoiseInfoProducer.cc

  // get the conditions and channel quality
  edm::ESHandle<HcalDbService> conditions;
  iSetup.get<HcalDbRecord>().get(conditions);
  const HcalQIEShape* shape = conditions->getHcalShape();

  // get the digis themselves
  edm::Handle<HBHEDigiCollection> hcalDigis;
  iEvent.getByLabel(hcalDigiTag_,hcalDigis);

  if (hcalDigis.isValid()) {

    // loop over the digis
    for(HBHEDigiCollection::const_iterator it=hcalDigis->begin(); it!=hcalDigis->end(); ++it) {

      const HBHEDataFrame &digi=(*it);
      HcalDetId cell = digi.id();

      // still need to check on valid digis; don't want to include bad channels in digi check
      if (std::find(badChannels_.begin(),
		    badChannels_.end(),
		    cell)!=badChannels_.end())
	{
	  //std::cout <<"BAD CHANNEL FOUND IN DIGI COLLECTION!";
	  //std::cout <<"\t("<<cell.ieta()<<","<<cell.iphi()<<","<<cell.depth()<<")"<<  std::endl;
	  continue;
	}
      DetId detcell=(DetId)cell;

      // get the calibrations and coder
      const HcalCalibrations& calibrations=conditions->getHcalCalibrations(cell);
      const HcalQIECoder* channelCoder = conditions->getHcalCoder (cell);
      HcalCoderDb coder (*channelCoder, *shape);

      // figure out if this digi corresponds to highest RecHit or top 5 RecHits
      bool isBig=false, isBig5=false;
      unsigned counter=0;

      for(HBHERecHitCollection::const_iterator hit=recHits_.begin();
	  hit!=recHits_.end() && counter < 5;
	  ++hit, ++counter) 
	{
	  if(hit->id() == digi.id()) 
	    {
	      if(counter==0) isBig=true;  // digi is also the highest energy rechit
	      isBig5=true;         // digi is one of 5 highest energy rechits
	      break;
	    }
	}
     
      // correct time slices for pedestal
      CaloSamples tool;
      coder.adc2fC(digi,tool);
      for(int ts=0; ts<tool.size(); ++ts) {
	
	// get the fC's
	double corrfc = tool[ts]-calibrations.pedestal(digi[ts].capid());
	
	// fill the relevant digi arrays
	if(isBig) {
	  event_->leadingDigiTimeSamples.at(ts) += corrfc;
	  event_->leadingDigiIEta = digi.id().ieta();
	  event_->leadingDigiIPhi = digi.id().iphi();
	}
	if(isBig5 && corrfc > 0.) event_->top5DigiTimeSamples.at(ts) += corrfc;
      }

    }

    // find peaks in time samples and totals
    pulseShapeVariables(event_->leadingDigiTimeSamples,
			event_->leadingDigiPeakSample,
			event_->leadingDigiTotal,
			event_->leadingDigiR1,
			event_->leadingDigiR2,
			event_->leadingDigiRPeak,
			event_->leadingDigiROuter);

    pulseShapeVariables(event_->top5DigiTimeSamples,
			event_->top5DigiPeakSample,
			event_->top5DigiTotal,
			event_->top5DigiR1,
			event_->top5DigiR2,
			event_->top5DigiRPeak,
			event_->top5DigiROuter);
    
  }
  else {
    if (!digisMissing_) {
      edm::LogWarning("MissingProduct") << "HBHEDigiCollection not found.  Branch will not be filled" << std::endl;
      digisMissing_ = true;
    }
  }
  
} // void StoppedHSCPMuonTreeProducer::doTimingFromDigis(const edm::Event& iEvent, const edm::EventSetup& iSetup)



void StoppedHSCPMuonTreeProducer::pulseShapeVariables(const std::vector<double>& samples,
						  unsigned& ipeak,
						  double& total,
						  double& r1,
						  double& r2,
						  double& rpeak,
						  double& router) {

  ipeak = 3;
  total = 0.;
  r1 = 0.;
  r2 = 0.;
  rpeak = 0.;
  router = 0.;

  for (int i=0; i<HBHEDataFrame::MAXSAMPLES; ++i) {
    if (samples.at(i) > samples.at(ipeak)) {
      ipeak = i;
    }
      total += samples.at(i);
  }

  if (total==0.) return;
  
  // R1
  if (ipeak < HBHEDataFrame::MAXSAMPLES-1) {
    if (samples.at(ipeak) > 0.) { 
      r1 = samples.at(ipeak+1) / samples.at(ipeak);
    }
    else r1 = 1.;
  }
  
  // R2
  if (ipeak < HBHEDataFrame::MAXSAMPLES-2) {
    if (samples.at(ipeak+1) > 0. &&
	samples.at(ipeak+1) > samples.at(ipeak+2)) {
      r2 = samples.at(ipeak+2) / samples.at(ipeak+1);
    }
    else r2 = 1.;
  }

  // Rpeak - leading digi
  rpeak = samples.at(ipeak) / total;
  
  // Router - leading digi
  double foursample=0.;
  for (int i=-1; i<3; ++i) {
    if (ipeak+i > 0 && ipeak+i<(int)HBHEDataFrame::MAXSAMPLES) { //JIM:  why is this condition "> 0" and not "> = 0"??
      foursample += samples.at(ipeak+i);
    }
  }
  router = 1. - (foursample / total);
  /*
    //  Dump diagnostic information
  std::cout <<"--------------------"<<std::endl;
  std::cout <<"NOISE SUMMARY OUTPUT"<<std::endl;
  for (uint i=0;i<samples.size();++i)
    std::cout <<samples[i]<<"\t";
  std::cout<<std::endl;
  std::cout <<"total = "<<total<<"  foursample = "<<foursample<<std::endl;
  std::cout <<"ipeak = "<<ipeak<<std::endl;
  if (ipeak<(int)HBHEDataFrame::MAXSAMPLES)
    std::cout <<"Peak value = "<<samples.at(ipeak)<<std::endl;
  else
    std::cout <<"Peak value = N/A"<<std::endl;
  std::cout<<std::endl;
  std::cout <<"R1 = "<<r1<<std::endl;
  std::cout <<"R2 = "<<r2<<std::endl;
  std::cout <<"Router = "<<router<<std::endl;
  std::cout <<"Rpeak = "<<rpeak<<std::endl;
  */ 
}





//define this as a plug-in
DEFINE_FWK_MODULE(StoppedHSCPMuonTreeProducer);
