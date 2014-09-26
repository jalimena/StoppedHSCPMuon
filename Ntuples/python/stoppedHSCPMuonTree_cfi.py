import FWCore.ParameterSet.Config as cms
from RecoMuon.TrackingTools.MuonSegmentMatcher_cff import *

stoppedHSCPMuonTree = cms.EDAnalyzer(
    "StoppedHSCPMuonTreeProducer",

    # trigger
    l1BitsTag = cms.untracked.InputTag("gtDigis"),
    l1MuonsTag = cms.untracked.string("l1extraParticles"),
    l1JetsTag = cms.untracked.string("l1extraParticles"),
    l1JetNoBptxName = cms.untracked.string("L1_SingleJet20_NotBptxOR"),  
    l1JetNoBptxNoHaloName = cms.untracked.string("L1_SingleJet20_NotBptxOR_NotMuBeamHalo"),
    l1SingleMu16erName = cms.untracked.string("L1_SingleMu16er"),
    l1SingleMu6NoBptxName = cms.untracked.string("L1_SingleMu6_NotBptxOR"),
    l1BptxName = cms.untracked.string("L1Tech_BPTX_plus_AND_minus"),
    l1MuBeamHaloName = cms.untracked.string("L1_SingleMuBeamHalo"),
    hltResultsTag = cms.untracked.InputTag("TriggerResults","","HLT"),
    hltEventTag = cms.untracked.InputTag("hltTriggerSummaryAOD","","HLT"),
    # Remove '*' from name, so that ntuple Producer can search for strings properly in C++
    hltPathJetNoBptx = cms.untracked.string("HLT_JetE30_NoBPTX_v"),
    hltPathJetNoBptxNoHalo = cms.untracked.string("HLT_JetE30_NoBPTX_NoHalo_v"),
    hltPathJetNoBptx3BXNoHalo = cms.untracked.string("HLT_JetE30_NoBPTX3BX_NoHalo_v"),
    hltPathJetE50NoBptx3BXNoHalo = cms.untracked.string("HLT_JetE50_NoBPTX3BX_NoHalo_v"),
    hltPathL2Mu20eta2p1NoVertex = cms.untracked.string("HLT_L2Mu20_ep2p1_NoVertex_v"),
    hltPathL2Mu10NoVertexNoBptx3BX = cms.untracked.string("HLT_L2Mu10_NoVertex_NoBPTX3BX_v"),
    hltPathL2Mu20NoVertexNoBptx3BX = cms.untracked.string("HLT_L2Mu20_NoVertex_NoBPTX3BX_v"),
    hltPathL2Mu30NoVertexNoBptx3BX = cms.untracked.string("HLT_L2Mu30_NoVertex_NoBPTX3BX_v"),
    hltPathL2Mu10NoVertexNoBptx3BXNoHalo = cms.untracked.string("HLT_L2Mu10_NoVertex_NoBPTX3BX_NoHalo_v"),
    hltPathL2Mu20NoVertexNoBptx3BXNoHalo = cms.untracked.string("HLT_L2Mu20_NoVertex_NoBPTX3BX_NoHalo_v"),
    hltPathL2Mu30NoVertexNoBptx3BXNoHalo = cms.untracked.string("HLT_L2Mu30_NoVertex_NoBPTX3BX_NoHalo_v"),
    hltPathL2Mu20NoVertex2ChaNoBptx3BXNoHalo = cms.untracked.string("HLT_L2Mu20_NoVertex_2Cha_NoBPTX3BX_NoHalo_v"),
    hltPathL2Mu30NoVertex2ChaNoBptx3BXNoHalo = cms.untracked.string("HLT_L2Mu30_NoVertex_2Cha_NoBPTX3BX_NoHalo_v"),
    hltFilterTag_20 = cms.untracked.InputTag("hltL2fL1sMu6NoBPTXL1f0L2Filtered20","","HLT"),
    hltFilterTag_20Cha2 = cms.untracked.InputTag("hltL2fL1sMu6NoBPTXL1f0L2Filtered20Cha2","","HLT"),
    
    # MC
    mcTag = cms.untracked.InputTag("generator"),
    genParticlesTag = cms.untracked.InputTag("genParticles"),
    
    # jets
    jetCorrectorServiceName = cms.untracked.string("ak5CaloJetsL1L2L3Residual"),
    jetTag = cms.untracked.InputTag("iterativeCone5CaloJets"),
    jetAK5Tag = cms.untracked.InputTag("ak5CaloJets"),
    jetMinEnergy = cms.untracked.double(1.),
    jetMaxEta = cms.untracked.double(1.3),

    # objects for study
    studyJetMinEta = cms.untracked.double(1.3),
    studyJetMaxEta = cms.untracked.double(3.0),
    studyTowerMinEta = cms.untracked.double(1.3),
    studyTowerMaxEta = cms.untracked.double(3.0),
    
    
    # muons
    muonTag = cms.untracked.InputTag("muons"),
    muonFromCosmicsTag = cms.untracked.InputTag("muonsFromCosmics"),
    #muonFromCosmicsTag = cms.untracked.InputTag("muonsFromCosmics1Leg"),

    # muon tracks
    standAloneMuonTag = cms.untracked.InputTag("standAloneMuons"),
    refittedStandAloneMuonTag = cms.untracked.InputTag("refittedStandAloneMuons"),
    displacedStandAloneMuonTag = cms.untracked.InputTag("displacedStandAloneMuons"),
    cosmicMuonsTag = cms.untracked.InputTag("cosmicMuons"),
    #as opposed to cosmicMuons1Leg, globalCosmicMuons, or globalCosmicMuons1Leg

    #muon shower info
    muonShowerTag = cms.untracked.InputTag("muons","muonShowerInformation"),    
    
    # calo towers
    #caloTowerTag = cms.untracked.InputTag("towerMaker"),
    towerMinEnergy = cms.untracked.double(1.),
    towerMaxEta = cms.untracked.double(1.3),
    
    # calo rechits
    caloRecHitTag = cms.untracked.InputTag("hbhereco"),
    rechitMinEnergy = cms.untracked.double(0.2),

    #reco-gen matching for muons
    recoGenDeltaR = cms.untracked.double(0.1),

    #reco-HLT matching for muons
    recoTriggerDeltaR = cms.untracked.double(0.5),

    #GlobalMinNDOF = cms.untracked.int32(8),
    #GlobalMinNDOFDT = cms.untracked.int32(6),
    #GlobalMinNDOFCSC = cms.untracked.int32(6),
    #GlobalMaxTOFErr = cms.untracked.double(0.07),
    #GlobalMinTOF = cms.untracked.double(1.0),
    GlobalMinNDOF    = cms.untracked.int32(-999999999),
    GlobalMinNDOFDT  = cms.untracked.int32(-999999999),
    GlobalMinNDOFCSC = cms.untracked.int32(-999999999),
    GlobalMaxTOFErr = cms.untracked.double(999999999),
    GlobalMinTOF    = cms.untracked.double(-999999999.),
 
    # HCAL digis/noise
    hcalNoiseTag = cms.untracked.InputTag("hcalnoise"),
    hcalNoiseFilterResultTag = cms.untracked.InputTag("HBHENoiseFilterResultProducer:HBHENoiseFilterResult"),
    rbxTag = cms.untracked.InputTag("hcalnoise"),
    hpdTag = cms.untracked.InputTag("hcalnoise"),
    hcalDigiTag = cms.untracked.InputTag("hcalDigis"),
    cscSegmentsTag = cms.untracked.InputTag("cscSegments"),
    cscRecHitsTag = cms.untracked.InputTag("csc2DRecHits"),

    DTRecHitsTag=cms.untracked.InputTag("dt1DRecHits"),
    DT4DSegmentsTag=cms.untracked.InputTag("dt4DSegments"),

    #timeTag=cms.untracked.InputTag("muontimingDelayedMuons"),
    timeTag=cms.untracked.InputTag("muons"),
    
    digiMinFc = cms.untracked.double(30.),
    
    # content controls
    isMC = cms.untracked.bool(False),
    doCaloTowers = cms.untracked.bool(False),
    doRecHits = cms.untracked.bool(False),
    doHFRecHits = cms.untracked.bool(False),
    doCsc = cms.untracked.bool(True),
    doCscRecHits = cms.untracked.bool(False),
    doDT    = cms.untracked.bool(True),  # muon Drift Tubes
    doRpcRecHits = cms.untracked.bool(True),
    doDigis = cms.untracked.bool(True),
    writeHistos = cms.untracked.bool(False),

    # bit 0:  off;
    #bit 1:  exclude rechit;
    #bit 5:  dead;
    #bit 6:  hot;
    #bit 18:  exclude from calotower
    badchannelstatus=cms.untracked.int32(1<<0 | 1<<1 | 1<<5 | 1<<6 | 1<<18),
    makeReducedNtuples=cms.untracked.bool(False),

    #TimingParameters = cms.PSet(
    #MuonSegmentMatcher,
    ServiceParameters = cms.PSet(
    Propagators = cms.untracked.vstring('SteppingHelixPropagatorAny',
                                        'PropagatorWithMaterial',
                                        'PropagatorWithMaterialOpposite'),
    RPCLayers = cms.bool(True)
    ),
    #)
    MatchParameters = cms.PSet(
    DTsegments = cms.InputTag("dt4DSegments"),
    DTradius = cms.double(0.01),
    CSCsegments = cms.InputTag("cscSegments"),
    TightMatchDT = cms.bool(False),
    TightMatchCSC = cms.bool(True)
    )
    
    )
