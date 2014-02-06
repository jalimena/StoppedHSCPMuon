#include "StoppedHSCPMuon/Ntuples/interface/StoppedHSCPMuonEvent.h"

#include "DataFormats/HcalDigi/interface/HBHEDataFrame.h"

#include <iostream>
#include <algorithm>

using namespace shscp;

StoppedHSCPMuonEvent::StoppedHSCPMuonEvent() :
  rHadPdgId(0),
  rHadVtxX(0.),
  rHadVtxY(0.),
  rHadVtxZ(0.),
  rHadVtxR(0.),
  rHadVtxT(0.),
  rHadE(0.),
  rHadPx(0.),
  rHadPy(0.),
  rHadPz(0.),
  rHadPt(0.),
  mc_N(0),
  mcPDGid(0),
  mcVtxX(0),
  mcVtxY(0),
  mcVtxZ(0),
  mcVtxR(0),
  mcVtxT(0),
  mcE(0),
  mcPx(0),
  mcPy(0),
  mcPz(0),
  mcPt(0),
  mcGenParticle_N(0),
  mcGenParticleId(0),
  mcGenParticleMass(0),
  mcGenParticleCharge(0),
  mcGenParticlePx(0),
  mcGenParticlePy(0),
  mcGenParticlePz(0),
  mcGenParticlePt(0),
  mcGenParticleP(0),
  mcGenParticleE(0),
  mcGenParticlePhi(0),
  mcGenParticleEta(0),
  mcGenParticleStatus(0),
  mcGenParticleNMothers(0),
  mcGenParticleMotherId(0),
  mcGenParticleNDaughters(0),
  mcGenParticleDaughterId(0),
  mcGenParticleDaughterStatus(0),
  mcGenParticleGenIndex(0),
  mcSparticle_N(0),
  mcSparticleId(0),
  mcSparticleMass(0),
  mcSparticleCharge(0),
  mcSparticlePx(0),
  mcSparticlePy(0),
  mcSparticlePz(0),
  mcSparticlePt(0),
  mcSparticleE(0),
  mcSparticlePhi(0),
  mcSparticleEta(0),
  mcRhadron_N(0),
  mcRhadronId(0),
  mcRhadronMass(0),
  mcRhadronCharge(0),
  mcRhadronPx(0),
  mcRhadronPy(0),
  mcRhadronPz(0),
  mcRhadronPt(0),
  mcRhadronE(0),
  mcRhadronPhi(0),
  mcRhadronEta(0),
  mcW_N(0),
  mcWId(0),
  mcWMass(0),
  mcWCharge(0),
  mcWPx(0),
  mcWPy(0),
  mcWPz(0),
  mcWPt(0),
  mcWP(0),
  mcWE(0),
  mcWPhi(0),
  mcWEta(0),
  mcWStatus(0),
  mcWNMothers(0),
  mcWMotherId(0),
  mcWNDaughters(0),
  mcWDaughterId(0),
  mcWDaughterStatus(0),
  mcWGenIndex(0),
  mcCMshower_N(0),
  mcCMshowerId(0),
  mcCMshowerMass(0),
  mcCMshowerCharge(0),
  mcCMshowerPx(0),
  mcCMshowerPy(0),
  mcCMshowerPz(0),
  mcCMshowerPt(0),
  mcCMshowerP(0),
  mcCMshowerE(0),
  mcCMshowerPhi(0),
  mcCMshowerEta(0),
  mcCMshowerStatus(0),
  mcCMshowerNMothers(0),
  mcCMshowerMotherId(0),
  mcCMshowerNDaughters(0),
  mcCMshowerDaughterId(0),
  mcCMshowerDaughterStatus(0),
  mcCMshowerGenIndex(0),
  mcTau_N(0),
  mcTauId(0),
  mcTauMass(0),
  mcTauCharge(0),
  mcTauPx(0),
  mcTauPy(0),
  mcTauPz(0),
  mcTauPt(0),
  mcTauP(0),
  mcTauE(0),
  mcTauPhi(0),
  mcTauEta(0),
  mcTauStatus(0),
  mcTauNMothers(0),
  mcTauMotherId(0),
  mcTauNDaughters(0),
  mcTauDaughterId(0),
  mcTauDaughterStatus(0),
  mcTauGenIndex(0),
  mcTop_N(0),
  mcTopId(0),
  mcTopMass(0),
  mcTopCharge(0),
  mcTopPx(0),
  mcTopPy(0),
  mcTopPz(0),
  mcTopPt(0),
  mcTopP(0),
  mcTopE(0),
  mcTopPhi(0),
  mcTopEta(0),
  mcTopStatus(0),
  mcTopNMothers(0),
  mcTopMotherId(0),
  mcTopNDaughters(0),
  mcTopDaughterId(0),
  mcTopDaughterStatus(0),
  mcTopGenIndex(0),
  mcStop_N(0),
  mcStopId(0),
  mcStopMass(0),
  mcStopCharge(0),
  mcStopPx(0),
  mcStopPy(0),
  mcStopPz(0),
  mcStopPt(0),
  mcStopP(0),
  mcStopE(0),
  mcStopPhi(0),
  mcStopEta(0),
  mcStopStatus(0),
  mcStopNMothers(0),
  mcStopMotherId(0),
  mcStopNDaughters(0),
  mcStopDaughterId(0),
  mcStopDaughterStatus(0),
  mcStopGenIndex(0),
  mcStau_N(0),
  mcStauId(0),
  mcStauMass(0),
  mcStauCharge(0),
  mcStauPx(0),
  mcStauPy(0),
  mcStauPz(0),
  mcStauPt(0),
  mcStauP(0),
  mcStauE(0),
  mcStauPhi(0),
  mcStauEta(0),
  mcStauStatus(0),
  mcStauNMothers(0),
  mcStauMotherId(0),
  mcStauNDaughters(0),
  mcStauDaughterId(0),
  mcStauGenIndex(0),
  mcGluino_N(0),
  mcGluinoId(0),
  mcGluinoMass(0),
  mcGluinoCharge(0),
  mcGluinoPx(0),
  mcGluinoPy(0),
  mcGluinoPz(0),
  mcGluinoPt(0),
  mcGluinoP(0),
  mcGluinoE(0),
  mcGluinoPhi(0),
  mcGluinoEta(0),
  mcGluinoStatus(0),
  mcGluinoNMothers(0),
  mcGluinoMotherId(0),
  mcGluinoNDaughters(0),
  mcGluinoDaughterId(0),
  mcGluinoDaughterStatus(0),
  mcGluinoGenIndex(0),
  mcTauPrime_N(0),
  mcTauPrimeId(0),
  mcTauPrimeMass(0),
  mcTauPrimeCharge(0),
  mcTauPrimePx(0),
  mcTauPrimePy(0),
  mcTauPrimePz(0),
  mcTauPrimePt(0),
  mcTauPrimeP(0),
  mcTauPrimeE(0),
  mcTauPrimePhi(0),
  mcTauPrimeEta(0),
  mcTauPrimeStatus(0),
  mcTauPrimeNMothers(0),
  mcTauPrimeMotherId(0),
  mcTauPrimeNDaughters(0),
  mcTauPrimeDaughterId(0),
  mcTauPrimeDaughterStatus(0),
  mcTauPrimeGenIndex(0),
  mcChargino_N(0),
  mcCharginoId(0),
  mcCharginoMass(0),
  mcCharginoCharge(0),
  mcCharginoPx(0),
  mcCharginoPy(0),
  mcCharginoPz(0),
  mcCharginoPt(0),
  mcCharginoP(0),
  mcCharginoE(0),
  mcCharginoPhi(0),
  mcCharginoEta(0),
  mcCharginoStatus(0),
  mcCharginoNMothers(0),
  mcCharginoMotherId(0),
  mcCharginoNDaughters(0),
  mcCharginoDaughterId(0),
  mcCharginoDaughterStatus(0),
  mcCharginoGenIndex(0),
  mcNeutralino_N(0),
  mcNeutralinoId(0),
  mcNeutralinoMass(0),
  mcNeutralinoCharge(0),
  mcNeutralinoPx(0),
  mcNeutralinoPy(0),
  mcNeutralinoPz(0),
  mcNeutralinoPt(0),
  mcNeutralinoP(0),
  mcNeutralinoE(0),
  mcNeutralinoPhi(0),
  mcNeutralinoEta(0),
  mcNeutralinoStatus(0),
  mcNeutralinoNMothers(0),
  mcNeutralinoMotherId(0),
  mcNeutralinoNDaughters(0),
  mcNeutralinoDaughterId(0),
  mcNeutralinoDaughterStatus(0),
  mcNeutralinoGenIndex(0),
  mcGravitino_N(0),
  mcGravitinoId(0),
  mcGravitinoMass(0),
  mcGravitinoCharge(0),
  mcGravitinoPx(0),
  mcGravitinoPy(0),
  mcGravitinoPz(0),
  mcGravitinoPt(0),
  mcGravitinoP(0),
  mcGravitinoE(0),
  mcGravitinoPhi(0),
  mcGravitinoEta(0),
  mcGravitinoStatus(0),
  mcGravitinoNMothers(0),
  mcGravitinoMotherId(0),
  mcGravitinoNDaughters(0),
  mcGravitinoDaughterId(0),
  mcGravitinoDaughterStatus(0),
  mcGravitinoGenIndex(0),
  mcNeutrino_N(0),
  mcNeutrinoId(0),
  mcNeutrinoMass(0),
  mcNeutrinoCharge(0),
  mcNeutrinoPx(0),
  mcNeutrinoPy(0),
  mcNeutrinoPz(0),
  mcNeutrinoPt(0),
  mcNeutrinoP(0),
  mcNeutrinoE(0),
  mcNeutrinoPhi(0),
  mcNeutrinoEta(0),
  mcNeutrinoStatus(0),
  mcNeutrinoNMothers(0),
  mcNeutrinoMotherId(0),
  mcNeutrinoNDaughters(0),
  mcNeutrinoDaughterId(0),
  mcNeutrinoDaughterStatus(0),
  mcNeutrinoGenIndex(0),
  mcMuon_N(0),
  mcMuonId(0),
  mcMuonMass(0),
  mcMuonCharge(0),
  mcMuonPx(0),
  mcMuonPy(0),
  mcMuonPz(0),
  mcMuonPt(0),
  mcMuonP(0),
  mcMuonE(0),
  mcMuonPhi(0),
  mcMuonEta(0),
  mcMuonStatus(0),
  mcMuonNMothers(0),
  mcMuonMotherId(0),
  mcMuonMotherOfWId(0),
  mcMuonMotherOfZId(0),
  mcMuonNDaughters(0),
  mcMuonDaughterId(0),
  mcMuonDaughterStatus(0),
  mcMuonGenIndex(0),
  mcStoppedParticle_N(0),
  mcStoppedParticleName(0),
  mcStoppedParticleId(0),
  mcStoppedParticleX(0),
  mcStoppedParticleY(0),
  mcStoppedParticleZ(0),
  mcStoppedParticleR(0),
  mcStoppedParticlePhi(0),
  mcStoppedParticleTime(0),
  id(0),
  bx(0),
  orbit(0),
  lb(0),
  run(0),
  fill(0),
  fillFromL1(0),
  time(0), // timestamp from EvF
  time2(0),  // calculated from run start + L1 counters for LS, orbit, BX
  time3(0),  // timestamp from LHC info in L1 data
  bxAfterCollision(0),
  bxBeforeCollision(0),
  bxWrtCollision(-99999),
  bxAfterBunch(0),
  bxBeforeBunch(0),
  bxWrtBunch(-99999),
  beam1Intensity(5),
  beam2Intensity(5),
  lumiByBx(5),
  gtAlgoWord0(0),
  gtAlgoWord1(0),
  gtTechWord(0),
  l1JetNoBptx(5),
  l1JetNoBptxNoHalo(5),
  l1Jet32NoBptxNoHalo(5),
  l1SingleMu16er(5),
  l1SingleMu6NoBptx(5),
  l1Bptx(5),
  l1MuBeamHalo(5),
  hltJetNoBptx(false),
  hltJetNoBptxNoHalo(false),
  hltJetNoBptx3BXNoHalo(false),
  hltL2Mu20eta2p1NoVertex(false),
  hltL2Mu10NoVertexNoBptx3BX(false),
  hltL2Mu20NoVertexNoBptx3BX(false),
  hltL2Mu30NoVertexNoBptx3BX(false),
  hltL2Mu10NoVertexNoBptx3BXNoHalo(false),
  hltL2Mu20NoVertexNoBptx3BXNoHalo(false),
  hltL2Mu30NoVertexNoBptx3BXNoHalo(false),
  hltL2Mu20NoVertex2ChaNoBptx3BXNoHalo(false),
  hltL2Mu30NoVertex2ChaNoBptx3BXNoHalo(false),
  algoTriggerPrescaleIndex(0),
  techTriggerPrescaleIndex(0),
  hltPrescaleIndex(0),
  l1JetNoBptxPrescale(0),
  l1JetNoBptxNoHaloPrescale(0),
  l1Jet32NoBptxNoHaloPrescale(0),
  l1SingleMu16erPrescale(0),
  l1SingleMu6NoBptxPrescale(0),
  hltJetNoBptxPrescale(0),
  hltJetNoBptxNoHaloPrescale(0),
  hltJetNoBptx3BXNoHaloPrescale(0),
  hltJetE50NoBptx3BXNoHaloPrescale(0),
  hltL2Mu20eta2p1NoVertexPrescale(0),
  hltL2Mu10NoVertexNoBptx3BXPrescale(0),
  hltL2Mu20NoVertexNoBptx3BXPrescale(0),
  hltL2Mu30NoVertexNoBptx3BXPrescale(0),
  hltL2Mu10NoVertexNoBptx3BXNoHaloPrescale(0),
  hltL2Mu20NoVertexNoBptx3BXNoHaloPrescale(0),
  hltL2Mu30NoVertexNoBptx3BXNoHaloPrescale(0),
  hltL2Mu20NoVertex2ChaNoBptx3BXNoHaloPrescale(0),
  hltL2Mu30NoVertex2ChaNoBptx3BXNoHaloPrescale(0),
  l1Jet_N(0),
  l1JetType(0),
  l1JetE(0),
  l1JetEt(0),
  l1JetEta(0),
  l1JetPhi(0),
  l1Muon_N(0),
  l1MuonPt(0),
  l1MuonEta(0),
  l1MuonPhi(0),
  hlt20Muon_N(0),
  hlt20MuonPt(0),
  hlt20MuonEta(0),
  hlt20MuonPhi(0),
  hlt20Cha2Muon_N(0),
  hlt20Cha2MuonPt(0),
  hlt20Cha2MuonEta(0),
  hlt20Cha2MuonPhi(0),
  jet_N(0),
  jetE(0),
  jetECorr(0),
  jetEt(0),
  jetEtCorr(0),
  jetEta(0),
  jetPhi(0),
  jetEHad(0),
  jetEEm(0),
  jetEMaxEcalTow(0),
  jetEMaxHcalTow(0),
  jetN60(0),
  jetN90(0),
  jetFHPD(0),
  jetN90Hits(0),
  studyJet_N(0),
  studyJetE(0),
  studyJetECorr(0),
  studyJetEt(0),
  studyJetEtCorr(0),
  studyJetEta(0),
  studyJetPhi(0),
  studyJetEHad(0),
  studyJetEEm(0),
  studyJetEMaxEcalTow(0),
  studyJetEMaxHcalTow(0),
  studyJetN60(0),
  studyJetN90(0),
  studyJetFHPD(0),
  studyJetN90Hits(0),
  jetAK5_N(0),
  jetAK5E(0),
  jetAK5ECorr(0),
  jetAK5Et(0),
  jetAK5EtCorr(0),
  jetAK5Eta(0),
  jetAK5Phi(0),
  jetAK5EHad(0),
  jetAK5EEm(0),
  jetAK5EMaxEcalTow(0),
  jetAK5EMaxHcalTow(0),
  jetAK5N60(0),
  jetAK5N90(0),
  jetAK5FHPD(0),
  jetAK5N90Hits(0),
  studyJetAK5_N(0),
  studyJetAK5E(0),
  studyJetAK5ECorr(0),
  studyJetAK5Et(0),
  studyJetAK5EtCorr(0),
  studyJetAK5Eta(0),
  studyJetAK5Phi(0),
  studyJetAK5EHad(0),
  studyJetAK5EEm(0),
  studyJetAK5EMaxEcalTow(0),
  studyJetAK5EMaxHcalTow(0),
  studyJetAK5N60(0),
  studyJetAK5N90(0),
  studyJetAK5FHPD(0),
  studyJetAK5N90Hits(0),
  mu_N(0),
  muType(0),
  muPx(0),
  muPy(0),
  muPz(0),
  muPt(0),
  muP(0),
  muEta(0),
  muPhi(0),
  muHcalEta(0),
  muHcalPhi(0),
  muSumChargedHadronPt(0),
  muSumChargedParticlePt(0),
  muSumNeutralHadronEt(0),
  muSumPhotonEt(0),
  muSumNeutralHadronEtHighThreshold(0),
  muSumPhotonEtHighThreshold(0),
  muSumPUPt(0),
  muIso(0),
  diMu_N(0),
  diMuMass(0.),
  mu_Cosmic_N(0),
  muCosmicType(0),
  muCosmicPx(0),
  muCosmicPy(0),
  muCosmicPz(0),
  muCosmicPt(0),
  muCosmicP(0),
  muCosmicEta(0),
  muCosmicPhi(0),
  muCosmicHcalEta(0),
  muCosmicHcalPhi(0),
  muCosmicSumChargedHadronPt(0),
  muCosmicSumChargedParticlePt(0),
  muCosmicSumNeutralHadronEt(0),
  muCosmicSumPhotonEt(0),
  muCosmicSumNeutralHadronEtHighThreshold(0),
  muCosmicSumPhotonEtHighThreshold(0),
  muCosmicSumPUPt(0),
  muCosmicIso(0),
  mu_StandAlone_N(0),
  muStandAloneCharge(0),
  muStandAlonePx(0),
  muStandAlonePy(0),
  muStandAlonePz(0),
  muStandAlonePt(0),
  muStandAloneP(0),
  muStandAloneEta(0),
  muStandAlonePhi(0),
  muStandAloneHcalEta(0),
  muStandAloneHcalPhi(0),
  muStandAloneTrackChi2(0),
  muStandAloneTrackNdof(0),
  muStandAloneTrackNormalizedChi2(0),
  muStandAloneTrackDxy(0),
  muStandAloneTrackDz(0),
  muStandAloneTrackNHits(0),
  muStandAloneTrackNLost(0),
  muStandAloneTrackNHitsMuon(0),
  muStandAloneTrackNHitsCsc(0),
  muStandAloneTrackNHitsDt(0),
  muStandAloneTrackNHitsRpc(0),
  muStandAloneTrackNStations(0),
  muStandAloneTrackNChambersCsc(0),
  muStandAloneTrackNChambersDt(0),
  muStandAloneTrackNChambersRpc(0),
  muStandAloneTrackQuality(0),
  muStandAloneTrackGenParticleIndex(0),
  muStandAloneTrackTriggerParticle20Index(0),
  muStandAloneTrackTriggerParticle20Cha2Index(0),
  muStandAloneTrackCscSegEndcap(0),
  muStandAloneTrackCscSegRing(0),
  muStandAloneTrackCscSegStation(0),
  muStandAloneTrackCscSegChamber(0),
  muStandAloneTrackCscSegNHits(0),
  muStandAloneTrackCscSegPhi(0),
  muStandAloneTrackCscSegZ(0),
  muStandAloneTrackCscSegR(0),
  muStandAloneTrackCscSegDirPhi(0),
  muStandAloneTrackCscSegDirTheta(0),
  muStandAloneTrackCscSegTime(0),
  muStandAloneTrackRpcHitZ(0),
  muStandAloneTrackRpcHitRho(0),
  muStandAloneTrackRpcHitPhi(0),
  muStandAloneTrackRpcHitRegion(0),
  muStandAloneTrackRpcHitBx(0),
  muStandAloneTrackDtTofDirection(0),
  muStandAloneTrackDtTofNDof(0),
  muStandAloneTrackDtTofInverseBeta(0),
  muStandAloneTrackDtTofInverseBetaErr(0),
  muStandAloneTrackDtTofFreeInverseBeta(0),
  muStandAloneTrackDtTofFreeInverseBetaErr(0),
  muStandAloneTrackDtTofTimeAtIpInOut(0),
  muStandAloneTrackDtTofTimeAtIpInOutErr(0),
  muStandAloneTrackDtTofTimeAtIpOutIn(0), 
  muStandAloneTrackDtTofTimeAtIpOutInErr(0),
  muStandAloneTrackDtTofInverseBetaLS(0),
  muStandAloneTrackDtTofInverseBetaLSErr(0),
  muStandAloneTrackDtTofYIntercept(0),
  muStandAloneTrackDtTofYInterceptErr(0),
  muStandAloneTrackDtTofChi2Dof(0), 
  muStandAloneTrackDtTofAveHitTimeErr(0), 
  mu_RefittedStandAlone_N(0),
  muRefittedStandAloneCharge(0),
  muRefittedStandAlonePx(0),
  muRefittedStandAlonePy(0),
  muRefittedStandAlonePz(0),
  muRefittedStandAlonePt(0),
  muRefittedStandAloneP(0),
  muRefittedStandAloneEta(0),
  muRefittedStandAlonePhi(0),
  muRefittedStandAloneHcalEta(0),
  muRefittedStandAloneHcalPhi(0),
  muRefittedStandAloneTrackChi2(0),
  muRefittedStandAloneTrackNdof(0),
  muRefittedStandAloneTrackNormalizedChi2(0),
  muRefittedStandAloneTrackDxy(0),
  muRefittedStandAloneTrackDz(0),
  muRefittedStandAloneTrackNHits(0),
  muRefittedStandAloneTrackNLost(0),
  muRefittedStandAloneTrackNHitsMuon(0),
  muRefittedStandAloneTrackNHitsCsc(0),
  muRefittedStandAloneTrackNHitsDt(0),
  muRefittedStandAloneTrackNHitsRpc(0),
  muRefittedStandAloneTrackNStations(0),
  muRefittedStandAloneTrackNChambersCsc(0),
  muRefittedStandAloneTrackNChambersDt(0),
  muRefittedStandAloneTrackNChambersRpc(0),
  muRefittedStandAloneTrackQuality(0),
  muRefittedStandAloneTrackGenParticleIndex(0),
  muRefittedStandAloneTrackTriggerParticle20Index(0),
  muRefittedStandAloneTrackTriggerParticle20Cha2Index(0),
  nVtx(0),
  vtx_N(0),
  vtxNDOF(0),
  vtxZ(0),
  vtxRho(0),
  track_N(0),
  trackChi2(0),
  trackNdof(0),
  trackNHits(0),
  trackNLost(0),
  trackP(0),
  trackQuality(0),
  trackHcalEta(0),
  trackHcalPhi(0),
  muStandAloneTof_N(0),
  muStandAloneTofDirection(0),
  muStandAloneTofNDof(0),
  muStandAloneTofInverseBeta(0),
  muStandAloneTofInverseBetaErr(0),
  muStandAloneTofFreeInverseBeta(0),
  muStandAloneTofFreeInverseBetaErr(0),
  muStandAloneTofTimeAtIpInOut(0),
  muStandAloneTofTimeAtIpInOutErr(0),
  muStandAloneTofTimeAtIpOutIn(0),
  muStandAloneTofTimeAtIpOutInErr(0),
  muStandAloneDTTof_N(0),
  muStandAloneDTTofDirection(0),
  muStandAloneDTTofNDof(0),
  muStandAloneDTTofInverseBeta(0),
  muStandAloneDTTofInverseBetaErr(0),
  muStandAloneDTTofFreeInverseBeta(0),
  muStandAloneDTTofFreeInverseBetaErr(0),
  muStandAloneDTTofTimeAtIpInOut(0),
  muStandAloneDTTofTimeAtIpInOutErr(0),
  muStandAloneDTTofTimeAtIpOutIn(0),
  muStandAloneDTTofTimeAtIpOutInErr(0),
  muStandAloneCSCTof_N(0),
  muStandAloneCSCTofDirection(0),
  muStandAloneCSCTofNDof(0),
  muStandAloneCSCTofInverseBeta(0),
  muStandAloneCSCTofInverseBetaErr(0),
  muStandAloneCSCTofFreeInverseBeta(0),
  muStandAloneCSCTofFreeInverseBetaErr(0),
  muStandAloneCSCTofTimeAtIpInOut(0),
  muStandAloneCSCTofTimeAtIpInOutErr(0),
  muStandAloneCSCTofTimeAtIpOutIn(0),
  muStandAloneCSCTofTimeAtIpOutInErr(0),
  refitMuStandAloneTof_N(0),
  refitMuStandAloneTofDirection(0),
  refitMuStandAloneTofNDof(0),
  refitMuStandAloneTofInverseBeta(0),
  refitMuStandAloneTofInverseBetaErr(0),
  refitMuStandAloneTofFreeInverseBeta(0),
  refitMuStandAloneTofFreeInverseBetaErr(0),
  refitMuStandAloneTofTimeAtIpInOut(0),
  refitMuStandAloneTofTimeAtIpInOutErr(0),
  refitMuStandAloneTofTimeAtIpOutIn(0),
  refitMuStandAloneTofTimeAtIpOutInErr(0),
  refitMuStandAloneDTTof_N(0),
  refitMuStandAloneDTTofDirection(0),
  refitMuStandAloneDTTofNDof(0),
  refitMuStandAloneDTTofInverseBeta(0),
  refitMuStandAloneDTTofInverseBetaErr(0),
  refitMuStandAloneDTTofFreeInverseBeta(0),
  refitMuStandAloneDTTofFreeInverseBetaErr(0),
  refitMuStandAloneDTTofTimeAtIpInOut(0),
  refitMuStandAloneDTTofTimeAtIpInOutErr(0),
  refitMuStandAloneDTTofTimeAtIpOutIn(0),
  refitMuStandAloneDTTofTimeAtIpOutInErr(0),
  refitMuStandAloneCSCTof_N(0),
  refitMuStandAloneCSCTofDirection(0),
  refitMuStandAloneCSCTofNDof(0),
  refitMuStandAloneCSCTofInverseBeta(0),
  refitMuStandAloneCSCTofInverseBetaErr(0),
  refitMuStandAloneCSCTofFreeInverseBeta(0),
  refitMuStandAloneCSCTofFreeInverseBetaErr(0),
  refitMuStandAloneCSCTofTimeAtIpInOut(0),
  refitMuStandAloneCSCTofTimeAtIpInOutErr(0),
  refitMuStandAloneCSCTofTimeAtIpOutIn(0),
  refitMuStandAloneCSCTofTimeAtIpOutInErr(0),
  beamHalo_CSCTight(false),
  beamHalo_CSCLoose(false),
  beamHalo_HcalTight(false),
  beamHalo_HcalLoose(false),
  nTowerSameiPhi(0),
  leadingIPhiFractionValue(0.),
  nTowerLeadingIPhi(0),
  eHadLeadingIPhi(0.),
  hfPlusTotalE(0.),
  hfMinusTotalE(0.),
  noiseMinE2Over10TS(0.),
  noiseMaxE2Over10TS(0.),
  noiseMaxHPDHits(0),
  noiseMaxRBXHits(0),
  noiseMaxHPDNoOtherHits(0),
  noiseMaxZeros(0),
  noiseMin25GeVHitTime(0.),
  noiseMax25GeVHitTime(0.),
  noiseMinRBXEMF(0.),
  noiseFilterResult(0),
  noiseEventEMEnergy(0.),
  noiseEventHadEnergy(0.),
  noiseEventTrackEnergy(0.),
  noiseNumProblematicRBXs(0.),
  topHPD5TimeSamples(HBHEDataFrame::MAXSAMPLES),
  topHPD5PeakSample(0),
  topHPD5Total(-999.),
  topHPD5R1(-999.),
  topHPD5R2(-999.),
  topHPD5RPeak(-999.),
  topHPD5ROuter(-999.),
  hpd_N(0),
  hpdId(0),
  hpdEta(0),
  hpdPhi(0),
  hpdTotalZeros(0),
  hpdMaxZeros(0),
  hpdNJet(0),
  hpdFc0(0), 
  hpdFc1(0), 
  hpdFc2(0), 
  hpdFc3(0), 
  hpdFc4(0), 
  hpdFc5(0), 
  hpdFc6(0), 
  hpdFc7(0), 
  hpdFc8(0), 
  hpdFc9(0),
  hpdFc5_0(0), 
  hpdFc5_1(0), 
  hpdFc5_2(0), 
  hpdFc5_3(0), 
  hpdFc5_4(0), 
  hpdFc5_5(0), 
  hpdFc5_6(0), 
  hpdFc5_7(0), 
  hpdFc5_8(0), 
  hpdFc5_9(0),
  tower_N(0),
  towerE(0),
  towerEt(0),
  towerEta(0),
  towerPhi(0),
  towerIEta(0),
  towerIPhi(0),
  towerNJet(0),
  towerEHad(0),
  towerEtHad(0),
  towerEEm(0),
  towerEtEm(0),
  studyTower_N(0),
  studyTowerE(0),
  studyTowerEt(0),
  studyTowerEta(0),
  studyTowerPhi(0),
  studyTowerIEta(0),
  studyTowerIPhi(0),
  studyTowerNJet(0),
  studyTowerEHad(0),
  studyTowerEtHad(0),
  studyTowerEEm(0),
  studyTowerEtEm(0),
  recHit_N(0),
  recHitE(0),
  recHitTime(0),
  recHitFlags(0),
  recHitAux(0),
  recHitEta(0.),
  recHitPhi(0.),
  recHitIEta(0),
  recHitIPhi(0),
  recHitDepth(0),
  hfRecHit_N(0),
  hfRecHitE(0),
  hfRecHitTime(0),
  hfRecHitEta(0.),
  hfRecHitPhi(0.),
  hfRecHitIEta(0),
  hfRecHitIPhi(0),
  hfRecHitDepth(0),
  cscSeg_N(0),
  cscSegEndcap(0),
  cscSegRing(0),
  cscSegStation(0),
  cscSegChamber(0),
  cscSegNHits(0),
  cscSegPhi(0),
  cscSegZ(0),
  cscSegR(0),
  cscSegDirPhi(0),
  cscSegDirTheta(0),
  cscSegTime(0),
  cscHit_N (0),
  cscHitZ (0),
  cscHitRho (0),
  cscHitPhi (0),
  DTD1PhiRecHitCollection_N(0),
  DTD1PhiRecHitTimeCollection(0),
  DTD1PhiRecHitEtaCollection(0.),
  DTD1PhiRecHitPhiCollection(0.),
  DTD1ZedRecHitCollection_N(0),
  DTD1ZedRecHitTimeCollection(0),
  DTD1ZedRecHitEtaCollection(0.),
  DTD1ZedRecHitPhiCollection(0.),
  DTSegment_N(0),
  DTSegWheel(0),
  DTSegStation(0),
  DTSegSector(0),
  DTSegLocalX(0),
  DTSegLocalY(0),
  DTSegZ(0),
  DTSegRho(0),
  DTSegPhi(0),
  DTSegEta(0),
  //DTSegTime(0),
  rpcHit_N(0),
  rpcHitZ(0),
  rpcHitRho(0),
  rpcHitPhi(0),
  rpcHitRegion(0),
  hePlusEnergy (-999),
  hePlusAntiEnergy (-999),
  hePlusPhi (-999),
  heMinusEnergy (-999),
  heMinusAntiEnergy (-999),
  heMinusPhi (-999),
  heEnergy (-999),
  heAntiEnergy (-999),
  hePhi (-999), 
  leadingDigiIEta(-999),
  leadingDigiIPhi(-999),
  leadingDigiTimeSamples(HBHEDataFrame::MAXSAMPLES),
  leadingDigiPeakSample(0),
  leadingDigiTotal(-999.),
  leadingDigiR1(-999.),
  leadingDigiR2(-999.),
  leadingDigiRPeak(-999.),
  leadingDigiROuter(-999.),
  top5DigiTimeSamples(HBHEDataFrame::MAXSAMPLES),
  top5DigiPeakSample(0),
  top5DigiTotal(-999.),
  top5DigiR1(-999.),
  top5DigiR2(-999.),
  top5DigiRPeak(-999.),
  top5DigiROuter(-999.)
{

  for (int k=0; k<5; ++k) {
    l1JetNoBptx.at(k) = 0;//false;
    l1JetNoBptxNoHalo.at(k) = 0;//false;
    l1Bptx.at(k) = 0;//false;
    l1MuBeamHalo.at(k) = 0;//false;
    beam1Intensity.at(k) = -1.0;
    beam2Intensity.at(k) = -1.0;
    lumiByBx.at(k) = -1.0;
  }
  
  for (int k=0; k<HBHEDataFrame::MAXSAMPLES; ++k) { 
    leadingDigiTimeSamples.at(k)=0.;
    top5DigiTimeSamples.at(k)=0.; 
    topHPD5TimeSamples.at(k)=0.;
  }

}

StoppedHSCPMuonEvent::~StoppedHSCPMuonEvent() { }


void StoppedHSCPMuonEvent::addMCDecay(MCDecay d) { 
  mcPDGid.push_back(d.pdgId);
  mcVtxX.push_back(d.vtxX);
  mcVtxY.push_back(d.vtxY);
  mcVtxZ.push_back(d.vtxZ);
  mcVtxR.push_back(d.vtxR);
  mcVtxT.push_back(d.vtxT);
  mcE.push_back(d.e);
  mcPx.push_back(d.px);
  mcPy.push_back(d.py);
  mcPz.push_back(d.px);
  mcPt.push_back(d.pt);
  ++mc_N;
}


void StoppedHSCPMuonEvent::addL1Jet(TrigJet j) {
  if (l1Jet_N < MAX_N_JETS) {
    l1JetType.push_back(j.type);
    l1JetE.push_back(j.e);
    l1JetEt.push_back(j.et);
    l1JetEta.push_back(j.eta);
    l1JetPhi.push_back(j.phi);
    ++l1Jet_N;
  }
}

void StoppedHSCPMuonEvent::addL1Muon(TrigMuon m) {
  l1MuonPt.push_back(m.pt);
  l1MuonEta.push_back(m.eta);
  l1MuonPhi.push_back(m.phi);
  ++l1Muon_N;
}


void StoppedHSCPMuonEvent::addHlt20Muon(TrigMuon m) {
   hlt20MuonPt.push_back(m.pt);
   hlt20MuonEta.push_back(m.eta);
   hlt20MuonPhi.push_back(m.phi);
   ++hlt20Muon_N;
}

void StoppedHSCPMuonEvent::addHlt20Cha2Muon(TrigMuon m) {
   hlt20Cha2MuonPt.push_back(m.pt);
   hlt20Cha2MuonEta.push_back(m.eta);
   hlt20Cha2MuonPhi.push_back(m.phi);
   ++hlt20Cha2Muon_N;
}


void StoppedHSCPMuonEvent::addJet(Jet j) {
  if (jet_N < MAX_N_JETS) {
    jetE.push_back(j.e);
    jetECorr.push_back(j.e_corr);
    jetEt.push_back(j.et);
    jetEtCorr.push_back(j.et_corr);
    jetEta.push_back(j.eta);
    jetPhi.push_back(j.phi);
    jetEHad.push_back(j.eHad);
    jetEEm.push_back(j.eEm);
    jetEMaxEcalTow.push_back(j.eMaxEcalTow);
    jetEMaxHcalTow.push_back(j.eMaxHcalTow);
    jetN60.push_back(j.n60);
    jetN90.push_back(j.n90);
    jetFHPD.push_back(j.fHPD);
    jetN90Hits.push_back(j.n90Hits);
    ++jet_N;
  }
}

void StoppedHSCPMuonEvent::addStudyJet(Jet j) {
  if (studyJet_N < MAX_N_JETS) {
    studyJetE.push_back(j.e);
    studyJetECorr.push_back(j.e_corr);
    studyJetEt.push_back(j.et);
    studyJetEtCorr.push_back(j.et_corr);
    studyJetEta.push_back(j.eta);
    studyJetPhi.push_back(j.phi);
    studyJetEHad.push_back(j.eHad);
    studyJetEEm.push_back(j.eEm);
    studyJetEMaxEcalTow.push_back(j.eMaxEcalTow);
    studyJetEMaxHcalTow.push_back(j.eMaxHcalTow);
    studyJetN60.push_back(j.n60);
    studyJetN90.push_back(j.n90);
    studyJetFHPD.push_back(j.fHPD);
    studyJetN90Hits.push_back(j.n90Hits);
    ++studyJet_N;
  }
}

void StoppedHSCPMuonEvent::addAK5Jet(Jet j) {
  if (jetAK5_N < MAX_N_JETS) {
    jetAK5E.push_back(j.e);
    jetAK5ECorr.push_back(j.e_corr);
    jetAK5Et.push_back(j.et);
    jetAK5EtCorr.push_back(j.et_corr);
    jetAK5Eta.push_back(j.eta);
    jetAK5Phi.push_back(j.phi);
    jetAK5EHad.push_back(j.eHad);
    jetAK5EEm.push_back(j.eEm);
    jetAK5EMaxEcalTow.push_back(j.eMaxEcalTow);
    jetAK5EMaxHcalTow.push_back(j.eMaxHcalTow);
    jetAK5N60.push_back(j.n60);
    jetAK5N90.push_back(j.n90);
    jetAK5FHPD.push_back(j.fHPD);
    jetAK5N90Hits.push_back(j.n90Hits);
    ++jetAK5_N;
  }
}

void StoppedHSCPMuonEvent::addAK5StudyJet(Jet j) {
  if (studyJetAK5_N < MAX_N_JETS) {
    studyJetAK5E.push_back(j.e);
    studyJetAK5ECorr.push_back(j.e_corr);
    studyJetAK5Et.push_back(j.et);
    studyJetAK5EtCorr.push_back(j.et_corr);
    studyJetAK5Eta.push_back(j.eta);
    studyJetAK5Phi.push_back(j.phi);
    studyJetAK5EHad.push_back(j.eHad);
    studyJetAK5EEm.push_back(j.eEm);
    studyJetAK5EMaxEcalTow.push_back(j.eMaxEcalTow);
    studyJetAK5EMaxHcalTow.push_back(j.eMaxHcalTow);
    studyJetAK5N60.push_back(j.n60);
    studyJetAK5N90.push_back(j.n90);
    studyJetAK5FHPD.push_back(j.fHPD);
    studyJetAK5N90Hits.push_back(j.n90Hits);
    ++studyJetAK5_N;
  }
}


void StoppedHSCPMuonEvent::addMuon(Muon m) { 
  muType.push_back(m.type);
  muPx.push_back(m.px);
  muPy.push_back(m.py);
  muPz.push_back(m.pz);
  muPt.push_back(m.pt);
  muP.push_back(m.p);
  muEta.push_back(m.eta);
  muPhi.push_back(m.phi);
  muHcalEta.push_back(m.hcalEta);
  muHcalPhi.push_back(m.hcalPhi);
  muSumChargedHadronPt.push_back(m.sumChargedHadronPt);
  muSumChargedParticlePt.push_back(m.sumChargedParticlePt);
  muSumNeutralHadronEt.push_back(m.sumNeutralHadronEt);
  muSumPhotonEt.push_back(m.sumPhotonEt);
  muSumNeutralHadronEtHighThreshold.push_back(m.sumNeutralHadronEtHighThreshold);
  muSumPhotonEtHighThreshold.push_back(m.sumPhotonEtHighThreshold);
  muSumPUPt.push_back(m.sumPUPt);
  muIso.push_back(m.iso);

  ++mu_N;
}

void StoppedHSCPMuonEvent::addDiMuon(DiMuon di) { 
  diMuMass.push_back(di.mass);

  ++diMu_N;
}

void StoppedHSCPMuonEvent::addCosmicMuon(Muon m) { 
  muCosmicType.push_back(m.type);
  muCosmicPx.push_back(m.px);
  muCosmicPy.push_back(m.py);
  muCosmicPz.push_back(m.pz);
  muCosmicPt.push_back(m.pt);
  muCosmicP.push_back(m.p);
  muCosmicEta.push_back(m.eta);
  muCosmicPhi.push_back(m.phi);
  muCosmicHcalEta.push_back(m.hcalEta);
  muCosmicHcalPhi.push_back(m.hcalPhi);
  muCosmicSumChargedHadronPt.push_back(m.sumChargedHadronPt);
  muCosmicSumChargedParticlePt.push_back(m.sumChargedParticlePt);
  muCosmicSumNeutralHadronEt.push_back(m.sumNeutralHadronEt);
  muCosmicSumPhotonEt.push_back(m.sumPhotonEt);
  muCosmicSumNeutralHadronEtHighThreshold.push_back(m.sumNeutralHadronEtHighThreshold);
  muCosmicSumPhotonEtHighThreshold.push_back(m.sumPhotonEtHighThreshold);
  muCosmicSumPUPt.push_back(m.sumPUPt);
  muCosmicIso.push_back(m.iso);

  ++mu_Cosmic_N;
}

void StoppedHSCPMuonEvent::addStandAloneMuon(Track track) { 
  muStandAloneCharge.push_back(track.charge);
  muStandAlonePx.push_back(track.px);
  muStandAlonePy.push_back(track.py);
  muStandAlonePz.push_back(track.pz);
  muStandAlonePt.push_back(track.pt);
  muStandAloneP.push_back(track.p);
  muStandAloneEta.push_back(track.eta);
  muStandAlonePhi.push_back(track.phi);
  muStandAloneHcalEta.push_back(track.hcalEta);
  muStandAloneHcalPhi.push_back(track.hcalPhi);
  muStandAloneTrackChi2.push_back(track.chi2);
  muStandAloneTrackNdof.push_back(track.ndof);
  muStandAloneTrackNormalizedChi2.push_back(track.normalizedChi2);
  muStandAloneTrackDxy.push_back(track.dxy);
  muStandAloneTrackDz.push_back(track.dz);
  muStandAloneTrackNHits.push_back(track.nHits);
  muStandAloneTrackNLost.push_back(track.nLost);
  muStandAloneTrackNHitsMuon.push_back(track.nHitsMuon);
  muStandAloneTrackNHitsCsc.push_back(track.nHitsCsc);
  muStandAloneTrackNHitsDt.push_back(track.nHitsDt);
  muStandAloneTrackNHitsRpc.push_back(track.nHitsRpc);
  muStandAloneTrackNStations.push_back(track.nStations);
  muStandAloneTrackNChambersCsc.push_back(track.nChambersCsc);
  muStandAloneTrackNChambersDt.push_back(track.nChambersDt);
  muStandAloneTrackNChambersRpc.push_back(track.nChambersRpc);
  muStandAloneTrackQuality.push_back(track.quality);
  muStandAloneTrackGenParticleIndex.push_back(track.genParticleIndex);
  muStandAloneTrackTriggerParticle20Index.push_back(track.triggerParticle20Index);
  muStandAloneTrackTriggerParticle20Cha2Index.push_back(track.triggerParticle20Cha2Index);
  muStandAloneTrackCscSegEndcap.push_back(track.cscSegEndcap);
  muStandAloneTrackCscSegRing.push_back(track.cscSegRing);
  muStandAloneTrackCscSegStation.push_back(track.cscSegStation);
  muStandAloneTrackCscSegChamber.push_back(track.cscSegChamber);
  muStandAloneTrackCscSegNHits.push_back(track.cscSegNHits);
  muStandAloneTrackCscSegPhi.push_back(track.cscSegPhi);
  muStandAloneTrackCscSegZ.push_back(track.cscSegZ);
  muStandAloneTrackCscSegR.push_back(track.cscSegR);
  muStandAloneTrackCscSegDirPhi.push_back(track.cscSegDirPhi);
  muStandAloneTrackCscSegDirTheta.push_back(track.cscSegDirTheta);
  muStandAloneTrackCscSegTime.push_back(track.cscSegTime);
  muStandAloneTrackRpcHitZ.push_back(track.rpcHitZ);
  muStandAloneTrackRpcHitRho.push_back(track.rpcHitRho);
  muStandAloneTrackRpcHitPhi.push_back(track.rpcHitPhi);
  muStandAloneTrackRpcHitRegion.push_back(track.rpcHitRegion);
  muStandAloneTrackRpcHitBx.push_back(track.rpcHitBx);
  muStandAloneTrackDtTofDirection.push_back(track.dtTofDirection);
  muStandAloneTrackDtTofNDof.push_back(track.dtTofNDof);
  muStandAloneTrackDtTofInverseBeta.push_back(track.dtTofInverseBeta);
  muStandAloneTrackDtTofInverseBetaErr.push_back(track.dtTofInverseBetaErr);
  muStandAloneTrackDtTofFreeInverseBeta.push_back(track.dtTofFreeInverseBeta);
  muStandAloneTrackDtTofFreeInverseBetaErr.push_back(track.dtTofFreeInverseBetaErr);
  muStandAloneTrackDtTofTimeAtIpInOut.push_back(track.dtTofTimeAtIpInOut);
  muStandAloneTrackDtTofTimeAtIpInOutErr.push_back(track.dtTofTimeAtIpInOutErr);
  muStandAloneTrackDtTofTimeAtIpOutIn.push_back(track.dtTofTimeAtIpOutIn);
  muStandAloneTrackDtTofTimeAtIpOutInErr.push_back(track.dtTofTimeAtIpOutInErr);
  muStandAloneTrackDtTofInverseBetaLS.push_back(track.dtTofInverseBetaLS);
  muStandAloneTrackDtTofInverseBetaLSErr.push_back(track.dtTofInverseBetaLSErr);
  muStandAloneTrackDtTofYIntercept.push_back(track.dtTofYIntercept);
  muStandAloneTrackDtTofYInterceptErr.push_back(track.dtTofYInterceptErr);
  muStandAloneTrackDtTofChi2Dof.push_back(track.dtTofChi2Dof);
  muStandAloneTrackDtTofAveHitTimeErr.push_back(track.dtTofAveHitTimeErr);
  ++mu_StandAlone_N;
}

void StoppedHSCPMuonEvent::addRefittedStandAloneMuon(Track track) {
  muRefittedStandAloneCharge.push_back(track.charge);
  muRefittedStandAlonePx.push_back(track.px);
  muRefittedStandAlonePy.push_back(track.py);
  muRefittedStandAlonePz.push_back(track.pz);
  muRefittedStandAlonePt.push_back(track.pt);
  muRefittedStandAloneP.push_back(track.p);
  muRefittedStandAloneEta.push_back(track.eta);
  muRefittedStandAlonePhi.push_back(track.phi);
  muRefittedStandAloneHcalEta.push_back(track.hcalEta);
  muRefittedStandAloneHcalPhi.push_back(track.hcalPhi);
  muRefittedStandAloneTrackChi2.push_back(track.chi2);
  muRefittedStandAloneTrackNdof.push_back(track.ndof);
  muRefittedStandAloneTrackNormalizedChi2.push_back(track.normalizedChi2);
  muRefittedStandAloneTrackDxy.push_back(track.dxy);
  muRefittedStandAloneTrackDz.push_back(track.dz);
  muRefittedStandAloneTrackNHits.push_back(track.nHits);
  muRefittedStandAloneTrackNLost.push_back(track.nLost);
  muRefittedStandAloneTrackNHitsMuon.push_back(track.nHitsMuon);
  muRefittedStandAloneTrackNHitsCsc.push_back(track.nHitsCsc);
  muRefittedStandAloneTrackNHitsDt.push_back(track.nHitsDt);
  muRefittedStandAloneTrackNHitsRpc.push_back(track.nHitsRpc);
  muRefittedStandAloneTrackNStations.push_back(track.nStations);
  muRefittedStandAloneTrackNChambersCsc.push_back(track.nChambersCsc);
  muRefittedStandAloneTrackNChambersDt.push_back(track.nChambersDt);
  muRefittedStandAloneTrackNChambersRpc.push_back(track.nChambersRpc);
  muRefittedStandAloneTrackQuality.push_back(track.quality);
  muRefittedStandAloneTrackGenParticleIndex.push_back(track.genParticleIndex);
  muRefittedStandAloneTrackTriggerParticle20Index.push_back(track.triggerParticle20Index);
  muRefittedStandAloneTrackTriggerParticle20Cha2Index.push_back(track.triggerParticle20Cha2Index);
  ++mu_RefittedStandAlone_N;
}


void StoppedHSCPMuonEvent::addTower(Tower t) {
  if (tower_N < MAX_N_TOWERS) {
    towerE.push_back(t.e);
    towerEt.push_back(t.et);
    towerEta.push_back(t.eta);
    towerPhi.push_back(t.phi);
    towerIEta.push_back(t.ieta);
    towerIPhi.push_back(t.iphi);
    towerNJet.push_back(t.nJet);
    towerEHad.push_back(t.eHad);
    towerEtHad.push_back(t.etHad);
    towerEEm.push_back(t.eEm);
    towerEtEm.push_back(t.etEm);
    ++tower_N;
  }
}

void StoppedHSCPMuonEvent::removeTowers() {
  // remove towers (used for reduced ntuples,
  // and when doCaloTowers is false
  towerE.clear();
  towerEt.clear();   
  towerEta.clear();  
  towerPhi.clear();  
  towerIEta.clear(); 
  towerIPhi.clear(); 
  towerNJet.clear(); 
  towerEHad.clear(); 
  towerEtHad.clear();
  towerEEm.clear();  
  towerEtEm.clear(); 
  tower_N=0;
} // void StoppedHSCPMuonEvent::removeTowers()


void StoppedHSCPMuonEvent::addStudyTower(Tower t) {
  if (studyTower_N < MAX_N_TOWERS) {
    studyTowerE.push_back(t.e);
    studyTowerEt.push_back(t.et);
    studyTowerEta.push_back(t.eta);
    studyTowerPhi.push_back(t.phi);
    studyTowerIEta.push_back(t.ieta);
    studyTowerIPhi.push_back(t.iphi);
    studyTowerNJet.push_back(t.nJet);
    studyTowerEHad.push_back(t.eHad);
    studyTowerEtHad.push_back(t.etHad);
    studyTowerEEm.push_back(t.eEm);
    studyTowerEtEm.push_back(t.etEm);
    ++studyTower_N;
  }
}

void StoppedHSCPMuonEvent::addRecHit(RecHit r) {
  recHitE.push_back(r.e);
  recHitTime.push_back(r.time);
  recHitFlags.push_back(r.flags);
  recHitAux.push_back(r.aux);
  recHitEta.push_back(r.eta);
  recHitPhi.push_back(r.phi); 
  recHitIEta.push_back(r.ieta);
  recHitIPhi.push_back(r.iphi);
  recHitDepth.push_back(r.depth);
  recHitRBXindex.push_back(r.RBXindex);
  recHitRMindex.push_back(r.RMindex);
  ++recHit_N;
}

void StoppedHSCPMuonEvent::addHFRecHit(RecHit r) {
  hfRecHitE.push_back(r.e);
  hfRecHitTime.push_back(r.time);
  hfRecHitEta.push_back(r.eta);
  hfRecHitPhi.push_back(r.phi); 
  hfRecHitIEta.push_back(r.ieta);
  hfRecHitIPhi.push_back(r.iphi);
  hfRecHitDepth.push_back(r.depth);
  ++hfRecHit_N;
}

void StoppedHSCPMuonEvent::addHPD(HPD h) {
  hpdId.push_back(h.id);
  hpdEta.push_back(h.eta);
  hpdPhi.push_back(h.phi);
  hpdTotalZeros.push_back(h.totalZeros);
  hpdMaxZeros.push_back(h.maxZeros);
  hpdNJet.push_back(h.nJet);
  hpdFc0.push_back(h.fc0);
  hpdFc1.push_back(h.fc1);
  hpdFc2.push_back(h.fc2);
  hpdFc3.push_back(h.fc3);
  hpdFc4.push_back(h.fc4);
  hpdFc5.push_back(h.fc5);
  hpdFc6.push_back(h.fc6);
  hpdFc7.push_back(h.fc7);
  hpdFc8.push_back(h.fc8);
  hpdFc9.push_back(h.fc9);
  hpdFc5_0.push_back(h.fc5_0);
  hpdFc5_1.push_back(h.fc5_1);
  hpdFc5_2.push_back(h.fc5_2);
  hpdFc5_3.push_back(h.fc5_3);
  hpdFc5_4.push_back(h.fc5_4);
  hpdFc5_5.push_back(h.fc5_5);
  hpdFc5_6.push_back(h.fc5_6);
  hpdFc5_7.push_back(h.fc5_7);
  hpdFc5_8.push_back(h.fc5_8);
  hpdFc5_9.push_back(h.fc5_9);
  ++hpd_N;
}

void StoppedHSCPMuonEvent::addCscSegment(CscSegment s) {
  cscSegEndcap.push_back(s.endcap);
  cscSegRing.push_back(s.ring);
  cscSegStation.push_back(s.station);
  cscSegChamber.push_back(s.chamber);
  cscSegNHits.push_back(s.nHits);
  cscSegPhi.push_back(s.phi);
  cscSegEta.push_back(s.eta);
  cscSegZ.push_back(s.z);
  cscSegR.push_back(s.r);
  cscSegDirPhi.push_back(s.dirPhi);
  cscSegDirTheta.push_back(s.dirTheta);
  cscSegTime.push_back(s.time);
  ++cscSeg_N;
}

void StoppedHSCPMuonEvent::addCscHit(CscHit h) {
  cscHitZ.push_back(h.z);
  cscHitRho.push_back(h.rho);
  cscHitPhi.push_back(h.phi);
  cscHitTime.push_back(h.time);
  ++cscHit_N;
}

void StoppedHSCPMuonEvent::addDTSegment(DTSegment dt)
{
  DTSegWheel.push_back(dt.wheel);
  DTSegStation.push_back(dt.station);
  DTSegSector.push_back(dt.sector);
  DTSegLocalX.push_back(dt.localX);
  DTSegLocalY.push_back(dt.localY);
  DTSegZ.push_back(dt.z);
  DTSegRho.push_back(dt.rho);
  DTSegPhi.push_back(dt.phi);
  DTSegEta.push_back(dt.eta);
  //DTSegTime.push_back(dt.time);
  ++DTSegment_N;
}

void StoppedHSCPMuonEvent::addDTD1PhiRecHitCollection(DTD1RecHitCollection dtD1PhiRecHitCollection) {
  DTD1PhiRecHitTimeCollection.push_back(dtD1PhiRecHitCollection.timeCollection);
  DTD1PhiRecHitEtaCollection.push_back(dtD1PhiRecHitCollection.etaCollection);
  DTD1PhiRecHitPhiCollection.push_back(dtD1PhiRecHitCollection.phiCollection); 
  ++DTD1PhiRecHitCollection_N;
}

void StoppedHSCPMuonEvent::addDTD1ZedRecHitCollection(DTD1RecHitCollection dtD1ZedRecHitCollection) {
  DTD1ZedRecHitTimeCollection.push_back(dtD1ZedRecHitCollection.timeCollection);
  DTD1ZedRecHitEtaCollection.push_back(dtD1ZedRecHitCollection.etaCollection);
  DTD1ZedRecHitPhiCollection.push_back(dtD1ZedRecHitCollection.phiCollection); 
  ++DTD1ZedRecHitCollection_N;
}

void StoppedHSCPMuonEvent::addRpcHit(RpcHit h)
{
  rpcHitZ.push_back(h.z);
  rpcHitRho.push_back(h.rho);
  rpcHitPhi.push_back(h.phi);
  rpcHitRegion.push_back(h.region);
  ++rpcHit_N;
}

void StoppedHSCPMuonEvent::addTrack(Track track) {

  trackChi2.push_back(track.chi2);
  trackNdof.push_back(track.ndof);
  trackNHits.push_back(track.nHits);
  trackNLost.push_back(track.nLost);
  trackQuality.push_back(track.quality);
  trackP.push_back(track.p);
  ++track_N;
}

void StoppedHSCPMuonEvent::addMuonTOFMap(MuonTOFMap muontof) {

  muStandAloneTofDirection.push_back(muontof.direction);
  muStandAloneTofNDof.push_back(muontof.nDof);
  muStandAloneTofInverseBeta.push_back(muontof.inverseBeta);
  muStandAloneTofInverseBetaErr.push_back(muontof.inverseBetaErr);
  muStandAloneTofFreeInverseBeta.push_back(muontof.freeInverseBeta);
  muStandAloneTofFreeInverseBetaErr.push_back(muontof.freeInverseBetaErr);
  muStandAloneTofTimeAtIpInOut.push_back(muontof.timeAtIpInOut);
  muStandAloneTofTimeAtIpInOutErr.push_back(muontof.timeAtIpInOutErr);
  muStandAloneTofTimeAtIpOutIn.push_back(muontof.timeAtIpOutIn);
  muStandAloneTofTimeAtIpOutInErr.push_back(muontof.timeAtIpOutInErr);
  ++muStandAloneTof_N;
}

void StoppedHSCPMuonEvent::addMuonTOFDTMap(MuonTOFMap muontofdt) {


  muStandAloneDTTofDirection.push_back(muontofdt.direction);
  muStandAloneDTTofNDof.push_back(muontofdt.nDof);
  muStandAloneDTTofInverseBeta.push_back(muontofdt.inverseBeta);
  muStandAloneDTTofInverseBetaErr.push_back(muontofdt.inverseBetaErr);
  muStandAloneDTTofFreeInverseBeta.push_back(muontofdt.freeInverseBeta);
  muStandAloneDTTofFreeInverseBetaErr.push_back(muontofdt.freeInverseBetaErr);
  muStandAloneDTTofTimeAtIpInOut.push_back(muontofdt.timeAtIpInOut);
  muStandAloneDTTofTimeAtIpInOutErr.push_back(muontofdt.timeAtIpInOutErr);
  muStandAloneDTTofTimeAtIpOutIn.push_back(muontofdt.timeAtIpOutIn);
  muStandAloneDTTofTimeAtIpOutInErr.push_back(muontofdt.timeAtIpOutInErr);
  ++muStandAloneDTTof_N;
}

void StoppedHSCPMuonEvent::addMuonTOFCSCMap(MuonTOFMap muontofcsc) {

  muStandAloneCSCTofDirection.push_back(muontofcsc.direction);
  muStandAloneCSCTofNDof.push_back(muontofcsc.nDof);
  muStandAloneCSCTofInverseBeta.push_back(muontofcsc.inverseBeta);
  muStandAloneCSCTofInverseBetaErr.push_back(muontofcsc.inverseBetaErr);
  muStandAloneCSCTofFreeInverseBeta.push_back(muontofcsc.freeInverseBeta);
  muStandAloneCSCTofFreeInverseBetaErr.push_back(muontofcsc.freeInverseBetaErr);
  muStandAloneCSCTofTimeAtIpInOut.push_back(muontofcsc.timeAtIpInOut);
  muStandAloneCSCTofTimeAtIpInOutErr.push_back(muontofcsc.timeAtIpInOutErr);
  muStandAloneCSCTofTimeAtIpOutIn.push_back(muontofcsc.timeAtIpOutIn);
  muStandAloneCSCTofTimeAtIpOutInErr.push_back(muontofcsc.timeAtIpOutInErr);
  ++muStandAloneCSCTof_N;
}

void StoppedHSCPMuonEvent::addREFITTOFMap(MuonTOFMap refittof) {

  refitMuStandAloneTofDirection.push_back(refittof.direction);
  refitMuStandAloneTofNDof.push_back(refittof.nDof);
  refitMuStandAloneTofInverseBeta.push_back(refittof.inverseBeta);
  refitMuStandAloneTofInverseBetaErr.push_back(refittof.inverseBetaErr);
  refitMuStandAloneTofFreeInverseBeta.push_back(refittof.freeInverseBeta);
  refitMuStandAloneTofFreeInverseBetaErr.push_back(refittof.freeInverseBetaErr);
  refitMuStandAloneTofTimeAtIpInOut.push_back(refittof.timeAtIpInOut);
  refitMuStandAloneTofTimeAtIpInOutErr.push_back(refittof.timeAtIpInOutErr);
  refitMuStandAloneTofTimeAtIpOutIn.push_back(refittof.timeAtIpOutIn);
  refitMuStandAloneTofTimeAtIpOutInErr.push_back(refittof.timeAtIpOutInErr);
  ++refitMuStandAloneTof_N;
}

void StoppedHSCPMuonEvent::addREFITTOFDTMap(MuonTOFMap refittofdt) {


  refitMuStandAloneDTTofDirection.push_back(refittofdt.direction);
  refitMuStandAloneDTTofNDof.push_back(refittofdt.nDof);
  refitMuStandAloneDTTofInverseBeta.push_back(refittofdt.inverseBeta);
  refitMuStandAloneDTTofInverseBetaErr.push_back(refittofdt.inverseBetaErr);
  refitMuStandAloneDTTofFreeInverseBeta.push_back(refittofdt.freeInverseBeta);
  refitMuStandAloneDTTofFreeInverseBetaErr.push_back(refittofdt.freeInverseBetaErr);
  refitMuStandAloneDTTofTimeAtIpInOut.push_back(refittofdt.timeAtIpInOut);
  refitMuStandAloneDTTofTimeAtIpInOutErr.push_back(refittofdt.timeAtIpInOutErr);
  refitMuStandAloneDTTofTimeAtIpOutIn.push_back(refittofdt.timeAtIpOutIn);
  refitMuStandAloneDTTofTimeAtIpOutInErr.push_back(refittofdt.timeAtIpOutInErr);
  ++refitMuStandAloneDTTof_N;
}

void StoppedHSCPMuonEvent::addREFITTOFCSCMap(MuonTOFMap refittofcsc) {

  refitMuStandAloneCSCTofDirection.push_back(refittofcsc.direction);
  refitMuStandAloneCSCTofNDof.push_back(refittofcsc.nDof);
  refitMuStandAloneCSCTofInverseBeta.push_back(refittofcsc.inverseBeta);
  refitMuStandAloneCSCTofInverseBetaErr.push_back(refittofcsc.inverseBetaErr);
  refitMuStandAloneCSCTofFreeInverseBeta.push_back(refittofcsc.freeInverseBeta);
  refitMuStandAloneCSCTofFreeInverseBetaErr.push_back(refittofcsc.freeInverseBetaErr);
  refitMuStandAloneCSCTofTimeAtIpInOut.push_back(refittofcsc.timeAtIpInOut);
  refitMuStandAloneCSCTofTimeAtIpInOutErr.push_back(refittofcsc.timeAtIpInOutErr);
  refitMuStandAloneCSCTofTimeAtIpOutIn.push_back(refittofcsc.timeAtIpOutIn);
  refitMuStandAloneCSCTofTimeAtIpOutInErr.push_back(refittofcsc.timeAtIpOutInErr);
  ++refitMuStandAloneCSCTof_N;
}

void StoppedHSCPMuonEvent::addHePlus(double energy, double antienergy, double phi) {
  if (hePlusEnergy < energy) {
    hePlusEnergy = energy;
    hePlusAntiEnergy = antienergy;
    hePlusPhi = phi;
  }
}

void StoppedHSCPMuonEvent::addHeMinus(double energy, double antienergy, double phi) {
  if (heMinusEnergy < energy) {
    heMinusEnergy = energy;
    heMinusAntiEnergy = antienergy;
    heMinusPhi = phi;
  }
}

void StoppedHSCPMuonEvent::addHe(double energy, double antienergy, double phi) {
  if (heEnergy < energy) {
    heEnergy = energy;
    heAntiEnergy = antienergy;
    hePhi = phi;
  }
} 

void StoppedHSCPMuonEvent::Dump() {

  using namespace std;

  cout << "New tree info :" << endl;
  cout << "Run          " << run << endl;
  cout << "Event        " << id << endl;
  cout << "LS           " << lb << endl;
  cout << "nTowSameiPhi " << nTowerSameiPhi << endl;
  cout << "nMuon        " << mu_N << endl;
  cout << "BeamHalo     " << beamHalo_CSCLoose << " " << beamHalo_CSCTight << std::endl;

}

// energy fraction at same iphi
double StoppedHSCPMuonEvent::leadingIPhiFraction() const {

    std::vector<double> tmp(75, 0);
    for (unsigned i=0; i<tower_N; ++i) {
      tmp.at(towerIPhi.at(i)) += towerE.at(i);
    }
    std::vector<double>::iterator max=max_element(tmp.begin(), tmp.end());

    double frac=0.;
    if (jet_N>0) frac = (*max)/jetE.at(0);
    return frac;

}


unsigned StoppedHSCPMuonEvent::jetCaloTowers() const {

  std::vector<shscp::Tower> towers;
  for (unsigned i=0; i<tower_N; ++i) {
    if (towerNJet.at(i)==0) {
      Tower t;
      t.iphi=towerIPhi.at(i);
      t.e = towerE.at(i);
      towers.push_back(t);
    }
  }

  std::sort(towers.begin(), towers.end(), shscp::tow_gt());

  unsigned tmp=0;

  if (towers.size() > 0) {
    int iphiFirst=towers.at(0).iphi;
    bool keepgoing=true;
    for (unsigned i=0; i<towers.size() && keepgoing; ++i) {
      if (towers.at(i).iphi==iphiFirst) tmp++;
      else keepgoing=false;
    }
  }

  return tmp;

}


#if !defined(__CINT__)
  ClassImp(StoppedHSCPMuonEvent)
#endif
