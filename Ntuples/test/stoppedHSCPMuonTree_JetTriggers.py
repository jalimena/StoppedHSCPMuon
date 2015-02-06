#
#  produce stopped HSCPMuon TTree
#  assumes RAW, HLT, RECO data present
#  Run this on StoppedHSCPMuon Skim
#
import FWCore.ParameterSet.Config as cms
import os, re
version = os.environ['CMSSW_VERSION']
                                        
#from StoppedHSCPMuon.Ntuples.stoppedHSCPMuonTree_MC_2012_cfg import *
from StoppedHSCPMuon.Ntuples.stoppedHSCPMuonTree_RECO_2012_JetTriggers_cfg import *

process.MessageLogger.cerr.INFO.limit = cms.untracked.int32(-1)

# change Global Tag
#process.GlobalTag.globaltag = 'GR_P_V32::All'
#process.GlobalTag.globaltag = 'FT_53_V10_AN2::All' #for Run2012A,B July13_2012 rereco, Run2012C-v1 Aug24_2012 rereco (53X)
#process.GlobalTag.globaltag = 'FT_53_V21_AN3::All' #for Run2012A,B,C,D Jan22_2013 rereco (53X)
#process.GlobalTag.globaltag = 'FT_R_70_V1::All' #for Run2012D Jan22_2013 rerecod in 70X 
process.GlobalTag.globaltag = 'PRE_R_72_V11A::All' #for Run2012A,B,C,D Jan22_2013 rereco in 72X                                                                                      

#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(2000) )

# input files
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
process.source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
        "/store/data/Run2012D/NoBPTX/RECO/22Jan2013-v1/30000/02018186-E689-E211-9775-001E67396FD1.root",
        "/store/data/Run2012D/NoBPTX/RECO/22Jan2013-v1/30000/127F61FC-E889-E211-BE5E-002590200B34.root",
        "/store/data/Run2012D/NoBPTX/RECO/22Jan2013-v1/30000/162F7006-E589-E211-85E0-003048D45F8E.root",
        "/store/data/Run2012D/NoBPTX/RECO/22Jan2013-v1/30000/2060F6CC-E489-E211-91F8-001E673967C5.root",
        "/store/data/Run2012D/NoBPTX/RECO/22Jan2013-v1/30000/281900B2-E489-E211-A8A6-001E67397C79.root",
        "/store/data/Run2012D/NoBPTX/RECO/22Jan2013-v1/30000/2C41833C-E789-E211-8902-F04DA23BCE4C.root",
        "/store/data/Run2012D/NoBPTX/RECO/22Jan2013-v1/30000/5CD4A0BD-E989-E211-99B0-001E67397CB0.root",
        "/store/data/Run2012D/NoBPTX/RECO/22Jan2013-v1/30000/5E3A1306-E589-E211-B356-001E673973D2.root",
        "/store/data/Run2012D/NoBPTX/RECO/22Jan2013-v1/30000/5EEF896C-E489-E211-B483-002481E100DE.root",
        "/store/data/Run2012D/NoBPTX/RECO/22Jan2013-v1/30000/6AEA8CE7-E689-E211-B794-002481E0DCD8.root",
        "/store/data/Run2012D/NoBPTX/RECO/22Jan2013-v1/30000/76DA1C99-E589-E211-AFCA-002481E100DE.root",
        "/store/data/Run2012D/NoBPTX/RECO/22Jan2013-v1/30000/9CD0474C-E689-E211-A987-001E673987D2.root",
        "/store/data/Run2012D/NoBPTX/RECO/22Jan2013-v1/30000/AA9BD23B-E889-E211-8F5B-001E67397B1B.root",
        "/store/data/Run2012D/NoBPTX/RECO/22Jan2013-v1/30000/D28FB27A-E489-E211-A1CC-003048D45FA2.root",
        "/store/data/Run2012D/NoBPTX/RECO/22Jan2013-v1/30000/E609F69D-E589-E211-BB3D-F04DA23BCE4C.root",
        "/store/data/Run2012D/NoBPTX/RECO/22Jan2013-v1/30000/ECDF964A-E989-E211-9216-001E673975EE.root",
        "/store/data/Run2012D/NoBPTX/RECO/22Jan2013-v1/30000/F0274AEF-EA89-E211-A726-003048D45FCA.root",
        "/store/data/Run2012D/NoBPTX/RECO/22Jan2013-v1/30000/F0E68FF7-E289-E211-9B11-001E67398CAA.root",
        "/store/data/Run2012D/NoBPTX/RECO/22Jan2013-v1/30000/F85EC599-E589-E211-A517-003048D479BE.root",
        "/store/data/Run2012D/NoBPTX/RECO/22Jan2013-v1/30000/FAAF99D8-E389-E211-9FAF-003048D4776A.root"
            
    ] );

process.source.lumisToProcess = cms.untracked.VLuminosityBlockRange('207454:139-207454:165',
                                                                    '207454:730-207454:800',
                                                                    '207454:1820-207454:1880',
                                                                    )



