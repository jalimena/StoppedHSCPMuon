
# remove pieces of master config so it can run on RECO only

import FWCore.ParameterSet.Config as cms

from StoppedHSCPMuon.Ntuples.stoppedHSCPMuonTree_Master_removeTrigger_cfg import *

process.ntuple.remove(process.gctDigis)
process.ntuple.remove(process.gtDigis)
process.ntuple.remove(process.l1extraParticles)
process.ntuple.remove(process.hcalDigis)

# 2012 trigger config

from StoppedHSCPMuon.Ntuples.StoppedHSCPMuon_Trigger2012_cff import *

process.hltHighLevel.HLTPaths = HLTPaths
process.stoppedHSCPMuonTree.hltPathJetNoBptx = hltPathJetNoBptx
process.stoppedHSCPMuonTree.hltPathJetNoBptxNoHalo = hltPathJetNoBptxNoHalo
process.stoppedHSCPMuonTree.hltPathJetNoBptx3BXNoHalo = hltPathJetNoBptx3BXNoHalo
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

# TTree output file
process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('stoppedHSCPMuonTree.root')
                                   #fileName = cms.string('stoppedHSCPMuonTree_onlyNoBPTX_190465_ls68_151.root')
                                   #fileName = cms.string('stoppedHSCPMuonTree_onlyNoBPTX_190465_ls68_110.root')
                                   #fileName = cms.string('stoppedHSCPMuonTree_onlyNoBPTX_190465_ls1_110.root')
                                   #fileName = cms.string('stoppedHSCPMuonTree_onlyNoBPTX_190465_ls122_127.root')
                                   #fileName = cms.string('stoppedHSCPMuonTree_onlyNoBPTX_190456_ls68_151_190465.root')
                                   #fileName = cms.string('rfio:/castor/cern.ch/user/j/jalimena/Ntuples/stoppedHSCPMuonTree_TEST.root')
                                   #fileName = cms.string('rfio:/castor/cern.ch/user/j/jalimena/Ntuples/cosmics_195155/take2/stoppedHSCPMuonTree.root')
                                   #fileName = cms.string('rfio:/castor/cern.ch/user/j/jalimena/Ntuples/stoppedHSCPMuonTree_onlyNoBPTX_191226.root')
                                   
                                   )
