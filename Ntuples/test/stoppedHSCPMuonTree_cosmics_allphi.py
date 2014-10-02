#
#  produce stopped HSCPMuon TTree
#  assumes RAW, HLT, RECO data present
#  Run this on StoppedHSCPMuon Skim
#
import FWCore.ParameterSet.Config as cms
import os, re
version = os.environ['CMSSW_VERSION']
                                        
#from StoppedHSCPMuon.Ntuples.stoppedHSCPMuonTree_MC_2012_cfg import *
from StoppedHSCPMuon.Ntuples.stoppedHSCPMuonTree_RECO_2012_cosmics_allphi_cfg import *

process.MessageLogger.cerr.INFO.limit = cms.untracked.int32(-1)
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(1)

# change Global Tag
#process.GlobalTag.globaltag = 'GR_P_V32::All'
#process.GlobalTag.globaltag = 'FT_53_V10_AN2::All' #for Run2012A,B July13_2012 rereco, Run2012C-v1 Aug24_2012 rereco (53X)
#process.GlobalTag.globaltag = 'FT_53_V21_AN3::All' #for Run2012A,B,C,D Jan22_2013 rereco (53X)
process.GlobalTag.globaltag = 'PRE_R_72_V6A::All' #for Run2012A,B,C,D Jan22_2013 rereco in 72X

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10000) )

# input files
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
process.source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [

"file:/afs/cern.ch/work/j/jalimena/reco_NoBPTX_cosmics_allphi/reco_NoBPTX_Run2012D_cosmics_allphi_208593_8.root",
"file:/afs/cern.ch/work/j/jalimena/reco_NoBPTX_cosmics_allphi/reco_NoBPTX_Run2012D_cosmics_allphi_208651_4.root",
"file:/afs/cern.ch/work/j/jalimena/reco_NoBPTX_cosmics_allphi/reco_NoBPTX_Run2012D_cosmics_allphi_208655_3.root",
"file:/afs/cern.ch/work/j/jalimena/reco_NoBPTX_cosmics_allphi/reco_NoBPTX_Run2012D_cosmics_allphi_208651_11.root",
"file:/afs/cern.ch/work/j/jalimena/reco_NoBPTX_cosmics_allphi/reco_NoBPTX_Run2012D_cosmics_allphi_208660_2.root",
"file:/afs/cern.ch/work/j/jalimena/reco_NoBPTX_cosmics_allphi/reco_NoBPTX_Run2012D_cosmics_allphi_208655_2.root",
"file:/afs/cern.ch/work/j/jalimena/reco_NoBPTX_cosmics_allphi/reco_NoBPTX_Run2012D_cosmics_allphi_208660_3.root",
"file:/afs/cern.ch/work/j/jalimena/reco_NoBPTX_cosmics_allphi/reco_NoBPTX_Run2012D_cosmics_allphi_208660_4.root",
"file:/afs/cern.ch/work/j/jalimena/reco_NoBPTX_cosmics_allphi/reco_NoBPTX_Run2012D_cosmics_allphi_208660_7.root",
"file:/afs/cern.ch/work/j/jalimena/reco_NoBPTX_cosmics_allphi/reco_NoBPTX_Run2012D_cosmics_allphi_208655_4.root",
"file:/afs/cern.ch/work/j/jalimena/reco_NoBPTX_cosmics_allphi/reco_NoBPTX_Run2012D_cosmics_allphi_208660_5.root",
"file:/afs/cern.ch/work/j/jalimena/reco_NoBPTX_cosmics_allphi/reco_NoBPTX_Run2012D_cosmics_allphi_208666_1.root",
"file:/afs/cern.ch/work/j/jalimena/reco_NoBPTX_cosmics_allphi/reco_NoBPTX_Run2012D_cosmics_allphi_208664_1.root",
"file:/afs/cern.ch/work/j/jalimena/reco_NoBPTX_cosmics_allphi/reco_NoBPTX_Run2012D_cosmics_allphi_208651_7.root",
"file:/afs/cern.ch/work/j/jalimena/reco_NoBPTX_cosmics_allphi/reco_NoBPTX_Run2012D_cosmics_allphi_208636_4.root",
"file:/afs/cern.ch/work/j/jalimena/reco_NoBPTX_cosmics_allphi/reco_NoBPTX_Run2012D_cosmics_allphi_208593_21.root",
"file:/afs/cern.ch/work/j/jalimena/reco_NoBPTX_cosmics_allphi/reco_NoBPTX_Run2012D_cosmics_allphi_208651_3.root",
"file:/afs/cern.ch/work/j/jalimena/reco_NoBPTX_cosmics_allphi/reco_NoBPTX_Run2012D_cosmics_allphi_208593_3.root",
"file:/afs/cern.ch/work/j/jalimena/reco_NoBPTX_cosmics_allphi/reco_NoBPTX_Run2012D_cosmics_allphi_208651_8.root",
"file:/afs/cern.ch/work/j/jalimena/reco_NoBPTX_cosmics_allphi/reco_NoBPTX_Run2012D_cosmics_allphi_208660_1.root",
"file:/afs/cern.ch/work/j/jalimena/reco_NoBPTX_cosmics_allphi/reco_NoBPTX_Run2012D_cosmics_allphi_208655_1.root",
"file:/afs/cern.ch/work/j/jalimena/reco_NoBPTX_cosmics_allphi/reco_NoBPTX_Run2012D_cosmics_allphi_208651_2.root",
"file:/afs/cern.ch/work/j/jalimena/reco_NoBPTX_cosmics_allphi/reco_NoBPTX_Run2012D_cosmics_allphi_208635_1.root",
"file:/afs/cern.ch/work/j/jalimena/reco_NoBPTX_cosmics_allphi/reco_NoBPTX_Run2012D_cosmics_allphi_208636_3.root",
"file:/afs/cern.ch/work/j/jalimena/reco_NoBPTX_cosmics_allphi/reco_NoBPTX_Run2012D_cosmics_allphi_208666_3.root",
"file:/afs/cern.ch/work/j/jalimena/reco_NoBPTX_cosmics_allphi/reco_NoBPTX_Run2012D_cosmics_allphi_208660_6.root",
"file:/afs/cern.ch/work/j/jalimena/reco_NoBPTX_cosmics_allphi/reco_NoBPTX_Run2012D_cosmics_allphi_208593_22.root",
"file:/afs/cern.ch/work/j/jalimena/reco_NoBPTX_cosmics_allphi/reco_NoBPTX_Run2012D_cosmics_allphi_208660_8.root",
"file:/afs/cern.ch/work/j/jalimena/reco_NoBPTX_cosmics_allphi/reco_NoBPTX_Run2012D_cosmics_allphi_208666_2.root",
"file:/afs/cern.ch/work/j/jalimena/reco_NoBPTX_cosmics_allphi/reco_NoBPTX_Run2012D_cosmics_allphi_208593_18.root",
"file:/afs/cern.ch/work/j/jalimena/reco_NoBPTX_cosmics_allphi/reco_NoBPTX_Run2012D_cosmics_allphi_208663_3.root",
"file:/afs/cern.ch/work/j/jalimena/reco_NoBPTX_cosmics_allphi/reco_NoBPTX_Run2012D_cosmics_allphi_208651_1.root",
"file:/afs/cern.ch/work/j/jalimena/reco_NoBPTX_cosmics_allphi/reco_NoBPTX_Run2012D_cosmics_allphi_208593_23.root",
"file:/afs/cern.ch/work/j/jalimena/reco_NoBPTX_cosmics_allphi/reco_NoBPTX_Run2012D_cosmics_allphi_208663_1.root",
"file:/afs/cern.ch/work/j/jalimena/reco_NoBPTX_cosmics_allphi/reco_NoBPTX_Run2012D_cosmics_allphi_208593_1.root",
"file:/afs/cern.ch/work/j/jalimena/reco_NoBPTX_cosmics_allphi/reco_NoBPTX_Run2012D_cosmics_allphi_208651_10.root",
"file:/afs/cern.ch/work/j/jalimena/reco_NoBPTX_cosmics_allphi/reco_NoBPTX_Run2012D_cosmics_allphi_208628_1.root",
"file:/afs/cern.ch/work/j/jalimena/reco_NoBPTX_cosmics_allphi/reco_NoBPTX_Run2012D_cosmics_allphi_208663_2.root",
"file:/afs/cern.ch/work/j/jalimena/reco_NoBPTX_cosmics_allphi/reco_NoBPTX_Run2012D_cosmics_allphi_208593_11.root",
"file:/afs/cern.ch/work/j/jalimena/reco_NoBPTX_cosmics_allphi/reco_NoBPTX_Run2012D_cosmics_allphi_208593_7.root",
"file:/afs/cern.ch/work/j/jalimena/reco_NoBPTX_cosmics_allphi/reco_NoBPTX_Run2012D_cosmics_allphi_208651_9.root",
"file:/afs/cern.ch/work/j/jalimena/reco_NoBPTX_cosmics_allphi/reco_NoBPTX_Run2012D_cosmics_allphi_208593_14.root",
"file:/afs/cern.ch/work/j/jalimena/reco_NoBPTX_cosmics_allphi/reco_NoBPTX_Run2012D_cosmics_allphi_208593_2.root",
"file:/afs/cern.ch/work/j/jalimena/reco_NoBPTX_cosmics_allphi/reco_NoBPTX_Run2012D_cosmics_allphi_208593_5.root",
"file:/afs/cern.ch/work/j/jalimena/reco_NoBPTX_cosmics_allphi/reco_NoBPTX_Run2012D_cosmics_allphi_208593_20.root",
"file:/afs/cern.ch/work/j/jalimena/reco_NoBPTX_cosmics_allphi/reco_NoBPTX_Run2012D_cosmics_allphi_208593_12.root",
"file:/afs/cern.ch/work/j/jalimena/reco_NoBPTX_cosmics_allphi/reco_NoBPTX_Run2012D_cosmics_allphi_208593_10.root",
"file:/afs/cern.ch/work/j/jalimena/reco_NoBPTX_cosmics_allphi/reco_NoBPTX_Run2012D_cosmics_allphi_208593_13.root",
#"file:/afs/cern.ch/work/j/jalimena/reco_NoBPTX_cosmics_allphi/reco_NoBPTX_Run2012D_cosmics_allphi_208636_2.root",
"file:/afs/cern.ch/work/j/jalimena/reco_NoBPTX_cosmics_allphi/reco_NoBPTX_Run2012D_cosmics_allphi_208593_17.root",
"file:/afs/cern.ch/work/j/jalimena/reco_NoBPTX_cosmics_allphi/reco_NoBPTX_Run2012D_cosmics_allphi_208593_16.root",
"file:/afs/cern.ch/work/j/jalimena/reco_NoBPTX_cosmics_allphi/reco_NoBPTX_Run2012D_cosmics_allphi_208593_19.root",
"file:/afs/cern.ch/work/j/jalimena/reco_NoBPTX_cosmics_allphi/reco_NoBPTX_Run2012D_cosmics_allphi_208593_24.root",
"file:/afs/cern.ch/work/j/jalimena/reco_NoBPTX_cosmics_allphi/reco_NoBPTX_Run2012D_cosmics_allphi_208593_4.root",
"file:/afs/cern.ch/work/j/jalimena/reco_NoBPTX_cosmics_allphi/reco_NoBPTX_Run2012D_cosmics_allphi_208593_25.root",
"file:/afs/cern.ch/work/j/jalimena/reco_NoBPTX_cosmics_allphi/reco_NoBPTX_Run2012D_cosmics_allphi_208593_6.root",
"file:/afs/cern.ch/work/j/jalimena/reco_NoBPTX_cosmics_allphi/reco_NoBPTX_Run2012D_cosmics_allphi_208593_9.root",
"file:/afs/cern.ch/work/j/jalimena/reco_NoBPTX_cosmics_allphi/reco_NoBPTX_Run2012D_cosmics_allphi_208651_12.root",
"file:/afs/cern.ch/work/j/jalimena/reco_NoBPTX_cosmics_allphi/reco_NoBPTX_Run2012D_cosmics_allphi_208651_13.root",
"file:/afs/cern.ch/work/j/jalimena/reco_NoBPTX_cosmics_allphi/reco_NoBPTX_Run2012D_cosmics_allphi_208651_5.root",
"file:/afs/cern.ch/work/j/jalimena/reco_NoBPTX_cosmics_allphi/reco_NoBPTX_Run2012D_cosmics_allphi_208651_6.root",
"file:/afs/cern.ch/work/j/jalimena/reco_NoBPTX_cosmics_allphi/reco_NoBPTX_Run2012D_cosmics_allphi_208660_9.root",
"file:/afs/cern.ch/work/j/jalimena/reco_NoBPTX_cosmics_allphi/reco_NoBPTX_Run2012D_cosmics_allphi_208593_15.root",
"file:/afs/cern.ch/work/j/jalimena/reco_NoBPTX_cosmics_allphi/reco_NoBPTX_Run2012D_cosmics_allphi_208636_5.root"
    ] );

process.source.lumisToProcess = cms.untracked.VLuminosityBlockRange(
    '208593:1-208593:245',
    '208628:1-208628:5',
    '208635:1-208635:9',
    '208636:1-208636:17',
    '208651:1-208651:128',
    '208655:1-208655:34',
    '208660:1-208660:89',
    '208663:1-208663:24',
    '208665:1-208665:11',
    '208666:1-208666:30'
    )
