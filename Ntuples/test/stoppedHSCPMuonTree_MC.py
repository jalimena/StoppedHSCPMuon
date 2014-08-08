#
#  produce stopped HSCPMuon TTree
#  assumes RAW, HLT, RECO data present
#  Run this on StoppedHSCPMuon Skim
#
import FWCore.ParameterSet.Config as cms
import os, re
version = os.environ['CMSSW_VERSION']
                                        
from StoppedHSCPMuon.Ntuples.stoppedHSCPMuonTree_MC_2012_cfg import *
#from StoppedHSCPMuon.Ntuples.stoppedHSCPMuonTree_RECO_2012_cfg import *

process.MessageLogger.cerr.INFO.limit = cms.untracked.int32(-1)
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(1)

# change Global Tag
#process.GlobalTag.globaltag = 'START53_V19::All' #for 53X reco signal MC
#process.GlobalTag.globaltag = 'START53_V27::All' #for 53X reco signal MC
#process.GlobalTag.globaltag = 'PRE_STA71_V3::All' #for 71X reco signal MC of 2012 MC
process.GlobalTag.globaltag = 'START72_V1::All' #for 72X reco signal MC of 2012 MC


#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )
#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )

# input files
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
process.source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
        #"root://eoscms//eos/cms/store/user/jalimena/HSCPstop_M-600_Tune4C_8TeV-pythia8/reco_stop600_neutralino200_533_noPU/a5fd4cac2592ce07df32b7c4e3a336e1/step3_RAW2DIGI_HLT_L1Reco_RECO_1_1_V7a.root"
        #"root://eoscms//eos/cms//store/user/jalimena/HSCPgluino_M-600_Tune4C_8TeV-pythia8/reco_gluino600_neutralino200_533_noPU/a5fd4cac2592ce07df32b7c4e3a336e1/step3_RAW2DIGI_HLT_L1Reco_RECO_1_1_rKV.root"
        #"file:/afs/cern.ch/user/j/jalimena/scratch0/CMSSW_5_3_9/src/reco/step3_RAW2DIGI_HLT_L1Reco_RECO_ppstau494_p0001.root"
        #"file:/mnt/hadoop/users/alimena/CMS/mchamp600_GEN-SIM/A841BB4A-CEFE-E111-9F17-A4BADB3CF272.root"
        #"root://eoscms//eos/cms/store/user/jalimena/HSCPmchamp6_M-500_TuneZ2star_8TeV-pythia6/reco_mchamp500_710pre7_PRESTA71V3/757fb463512dc747d0567e39a49bf997/step3_RAW2DIGI_HLT_L1Reco_RECO_mchamp500_9_1_cFa.root"
        "root://eoscms//eos/cms/store/user/jalimena/HSCPmchamp6_M-500_TuneZ2star_8TeV-pythia6/reco_mchamp500_720pre3_cosSeedSAreco_SATrajectory/f6a451b5aa7c5090472a2533b8425b2a/step3_RAW2DIGI_HLT_L1Reco_RECO_mchamp500_9_1_PnS.root"
        ] );
