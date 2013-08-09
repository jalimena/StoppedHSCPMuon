
# override trigger settings for 2012 triggers

import FWCore.ParameterSet.Config as cms
#Wild cards are okay for these names
HLTPaths = cms.vstring(
    "HLT_JetE30_NoBPTX_v*",
    "HLT_JetE30_NoBPTX3BX_v*",
    "HLT_JetE30_NoBPTX3BX_NoHalo_v*",
    "HLT_JetE50_NoBPTX3BX_v*",
    "HLT_JetE50_NoBPTX3BX_NoHalo_v*",
    "HLT_JetE70_NoBPTX3BX_v*",
    "HLT_JetE70_NoBPTX3BX_NoHalo_v*"    
)

# Wild cards are not currently supported for these strings
hltPathJetNoBptx = cms.untracked.string("HLT_JetE30_NoBPTX_v")
hltPathJetNoBptxNoHalo = cms.untracked.string("HLT_JetE30_NoBPTX_NoHalo_v")
hltPathJetNoBptx3BXNoHalo = cms.untracked.string("HLT_JetE30_NoBPTX3BX_NoHalo_v")
hltPathJetE50NoBptx3BXNoHalo = cms.untracked.string("HLT_JetE50_NoBPTX3BX_NoHalo_v")
hltPathL2Mu20eta2p1NoVertex = cms.untracked.string("HLT_L2Mu20_eta2p1_NoVertex_v")
hltPathL2Mu10NoVertexNoBptx3BX = cms.untracked.string("HLT_L2Mu10_NoVertex_NoBPTX3BX_v")
hltPathL2Mu20NoVertexNoBptx3BX = cms.untracked.string("HLT_L2Mu20_NoVertex_NoBPTX3BX_v")
hltPathL2Mu30NoVertexNoBptx3BX = cms.untracked.string("HLT_L2Mu30_NoVertex_NoBPTX3BX_v")
hltPathL2Mu10NoVertexNoBptx3BXNoHalo = cms.untracked.string("HLT_L2Mu10_NoVertex_NoBPTX3BX_NoHalo_v")
hltPathL2Mu20NoVertexNoBptx3BXNoHalo = cms.untracked.string("HLT_L2Mu20_NoVertex_NoBPTX3BX_NoHalo_v")
hltPathL2Mu30NoVertexNoBptx3BXNoHalo = cms.untracked.string("HLT_L2Mu30_NoVertex_NoBPTX3BX_NoHalo_v")
hltPathL2Mu20NoVertex2ChaNoBptx3BXNoHalo = cms.untracked.string("HLT_L2Mu20_NoVertex_2Cha_NoBPTX3BX_NoHalo_v")
hltPathL2Mu30NoVertex2ChaNoBptx3BXNoHalo = cms.untracked.string("HLT_L2Mu30_NoVertex_2Cha_NoBPTX3BX_NoHalo_v")
hltL3Tag = cms.untracked.InputTag("hltStoppedHSCPTight1CaloJetEnergy30","","HLT")

