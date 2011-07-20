#ifndef Validation_RecoMuon_RecoMuonValidatorPF_H
#define Validation_RecoMuon_RecoMuonValidatorPF_H

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "CommonTools/RecoAlgos/interface/TrackingParticleSelector.h"
#include "DataFormats/TrackReco/interface/Track.h"

#include "SimMuon/MCTruth/interface/MuonAssociatorByHits.h"

// for selection cut
#include "CommonTools/Utils/interface/StringCutObjectSelector.h"

class DQMStore;
class MonitorElement;
class MuonServiceProxy;
class TrackAssociatorBase;

class RecoMuonValidatorPF : public edm::EDAnalyzer
{
 public:
  RecoMuonValidatorPF(const edm::ParameterSet& pset);
  ~RecoMuonValidatorPF();

  virtual void beginRun(const edm::Run&, const edm::EventSetup& eventSetup);
  virtual void endRun();
  virtual void analyze(const edm::Event& event, const edm::EventSetup& eventSetup);
  virtual int countMuonHits(const reco::Track& track) const;
  virtual int countTrackerHits(const reco::Track& track) const;

 protected:
  unsigned int verbose_;

  edm::InputTag simLabel_;
  edm::InputTag muonLabel_;
  std::string muonSelection_;

  edm::InputTag muAssocLabel_;
  const MuonAssociatorByHits * assoByHits;
  
  std::string outputFileName_;
  std::string subDir_;

  MuonServiceProxy * theMuonService;
  DQMStore * theDQM;
  
  bool doAbsEta_;
  bool doAssoc_;

  TrackingParticleSelector tpSelector_;

  // Track to use
  MuonAssociatorByHits::MuonTrackType trackType_;

  struct MuonME;
  MuonME * muonME_;

  struct CommonME;
  CommonME * commonME_;

 private:
  StringCutObjectSelector<reco::Muon> selector_;

};

#endif
/* vim:set ts=2 sts=2 sw=2 expandtab: */