#
#  produce stopped HSCPMuon TTree
#  assumes RAW, HLT, RECO data present
#  Run this on StoppedHSCPMuon Skim
#
import FWCore.ParameterSet.Config as cms
import os, re
version = os.environ['CMSSW_VERSION']
                                        
#from StoppedHSCPMuon.Ntuples.stoppedHSCPMuonTree_MC_2012_cfg import *
from StoppedHSCPMuon.Ntuples.stoppedHSCPMuonTree_RECO_2012_removeTrigger_cfg import *

process.MessageLogger.cerr.INFO.limit = cms.untracked.int32(-1)

# change Global Tag
#process.GlobalTag.globaltag = 'GR_P_V32::All'
process.GlobalTag.globaltag = 'FT_R_70_V1::All'

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10) )

# input files
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
process.source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
        '/store/data/Run2012D/HLTPhysics1/RECO/PromptReco-v1/000/208/509/062C87BF-3F40-E211-984E-003048D2C0F0.root',
        '/store/data/Run2012D/HLTPhysics1/RECO/PromptReco-v1/000/208/509/12880FA5-4B40-E211-838E-001D09F2462D.root',
        '/store/data/Run2012D/HLTPhysics1/RECO/PromptReco-v1/000/208/509/1C0983D6-4340-E211-A05B-BCAEC5329708.root',
        '/store/data/Run2012D/HLTPhysics1/RECO/PromptReco-v1/000/208/509/2495200C-4140-E211-A2E4-003048D3C980.root',
        '/store/data/Run2012D/HLTPhysics1/RECO/PromptReco-v1/000/208/509/268B9F6D-3640-E211-B32A-003048D2C01E.root',
        '/store/data/Run2012D/HLTPhysics1/RECO/PromptReco-v1/000/208/509/26F82DE2-2540-E211-894F-002481E0D524.root',
        '/store/data/Run2012D/HLTPhysics1/RECO/PromptReco-v1/000/208/509/346212A8-3A40-E211-AF27-0025B320384C.root',
        '/store/data/Run2012D/HLTPhysics1/RECO/PromptReco-v1/000/208/509/4AA971A6-2A40-E211-B688-BCAEC518FF7A.root',
        '/store/data/Run2012D/HLTPhysics1/RECO/PromptReco-v1/000/208/509/64ABDAA6-1340-E211-9829-003048D2BC42.root',
        '/store/data/Run2012D/HLTPhysics1/RECO/PromptReco-v1/000/208/509/7239E0A4-6940-E211-81B3-0025B32036E2.root',
        '/store/data/Run2012D/HLTPhysics1/RECO/PromptReco-v1/000/208/509/80466D71-3140-E211-B49E-5404A63886B2.root',
        '/store/data/Run2012D/HLTPhysics1/RECO/PromptReco-v1/000/208/509/8ACE3031-2140-E211-964F-001D09F24399.root',
        '/store/data/Run2012D/HLTPhysics1/RECO/PromptReco-v1/000/208/509/90E5DC08-3040-E211-982E-003048F118C4.root',
        '/store/data/Run2012D/HLTPhysics1/RECO/PromptReco-v1/000/208/509/92FF688C-1D40-E211-800C-001D09F2B2CF.root',
        '/store/data/Run2012D/HLTPhysics1/RECO/PromptReco-v1/000/208/509/A28D7A73-3140-E211-87BF-5404A63886EE.root',
        '/store/data/Run2012D/HLTPhysics1/RECO/PromptReco-v1/000/208/509/B0EB86E3-4340-E211-A1DD-5404A63886AF.root',
        '/store/data/Run2012D/HLTPhysics1/RECO/PromptReco-v1/000/208/509/CA6BA3B7-2C40-E211-9BB0-5404A638869E.root',
        '/store/data/Run2012D/HLTPhysics1/RECO/PromptReco-v1/000/208/509/D218F657-5740-E211-A00B-5404A640A639.root',
        '/store/data/Run2012D/HLTPhysics1/RECO/PromptReco-v1/000/208/509/DA365F03-1840-E211-9647-003048D3751E.root',
        '/store/data/Run2012D/HLTPhysics1/RECO/PromptReco-v1/000/208/509/F8A12DFA-2840-E211-BB4D-003048F1C420.root',
        '/store/data/Run2012D/HLTPhysics1/RECO/PromptReco-v1/000/208/509/FC7ECEDE-0D40-E211-9AFF-002481E0D524.root'
        ] );
process.source.lumisToProcess = cms.untracked.VLuminosityBlockRange(
    '208509:71-208509: 232'
    #'190456:1-190456:184',
    #'190465:68-190465:110'
    #'190465:1-190465:110'
    #'190465:122-190465:127'

    #'193834:1-194713:1' #Run2012B, HLT_L2Mu20_NoVertex_NoBPTX3BX_v1
    #'194735:1-197756:1' #Run2012B, HLT_L2Mu20_NoVertex_NoBPTX3BX_NoHalo_v3
    #'197770:1-200000:1' #Run2012B, HLT_L2Mu20_NoVertex_2Cha_NoBPTX3BX_NoHalo_v1, last run is filler number
    )



