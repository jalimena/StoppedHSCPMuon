
# remove pieces of master config so it can run on RECO only

import FWCore.ParameterSet.Config as cms

from StoppedHSCPMuon.Ntuples.stoppedHSCPMuonTree_Master_cfg import *

process.stoppedHSCPMuonTree.isMC = cms.untracked.bool(True)

process.gctDigis.inputLabel = 'rawDataCollector'
process.gtDigis.DaqGtInputTag = 'rawDataCollector'
process.hcalDigis.InputLabel = 'rawDataCollector'


process.ntuple.remove(process.hltHighLevel)
process.ntuple.remove(process.gctDigis)
process.ntuple.remove(process.gtDigis)
process.ntuple.remove(process.l1extraParticles)
process.ntuple.remove(process.hcalDigis)
process.ntuple.remove(process.hltStoppedHSCPMuonHpdFilter)

# 2012 trigger config  (although it's irrelevant for MC as BPTX assumed to fire for all MC)

from StoppedHSCPMuon.Ntuples.StoppedHSCPMuon_Trigger2012_cff import *

process.hltHighLevel.HLTPaths = HLTPaths
process.stoppedHSCPMuonTree.hltPathJetNoBptx = hltPathJetNoBptx
process.stoppedHSCPMuonTree.hltPathJetNoBptxNoHalo = hltPathJetNoBptxNoHalo
process.stoppedHSCPMuonTree.hltPathJetNoBptx3BXNoHalo = hltPathJetNoBptx3BXNoHalo
process.stoppedHSCPMuonTree.hltPathJetE50NoBptx3BXNoHalo = hltPathJetE50NoBptx3BXNoHalo
process.stoppedHSCPMuonTree.hltPathL2Mu20eta2p1NoVertex = hltPathL2Mu20eta2p1NoVertex
process.stoppedHSCPMuonTree.hltPathL2Mu10NoVertexNoBptx3BX = hltPathL2Mu10NoVertexNoBptx3BX
process.stoppedHSCPMuonTree.hltPathL2Mu20NoVertexNoBptx3BX = hltPathL2Mu20NoVertexNoBptx3BX
process.stoppedHSCPMuonTree.hltPathL2Mu30NoVertexNoBptx3BX = hltPathL2Mu30NoVertexNoBptx3BX
process.stoppedHSCPMuonTree.hltPathL2Mu10NoVertexNoBptx3BXNoHalo = hltPathL2Mu10NoVertexNoBptx3BXNoHalo
process.stoppedHSCPMuonTree.hltPathL2Mu20NoVertexNoBptx3BXNoHalo = hltPathL2Mu20NoVertexNoBptx3BXNoHalo
process.stoppedHSCPMuonTree.hltPathL2Mu30NoVertexNoBptx3BXNoHalo = hltPathL2Mu30NoVertexNoBptx3BXNoHalo
process.stoppedHSCPMuonTree.hltPathL2Mu20NoVertex2ChaNoBptx3BXNoHalo = hltPathL2Mu20NoVertex2ChaNoBptx3BXNoHalo
process.stoppedHSCPMuonTree.hltPathL2Mu30NoVertex2ChaNoBptx3BXNoHalo = hltPathL2Mu30NoVertex2ChaNoBptx3BXNoHalo
process.stoppedHSCPMuonTree.hltL3Tag = hltL3Tag
process.stoppedHSCPMuonTree.doDigis=False 
