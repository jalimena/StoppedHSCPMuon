#
#  produce stopped HSCP TTree
#  assumes RAW, HLT, RECO data present
#  Run this on StoppedHSCP Skim
#
#  includes a check that the event passed stopped HSCP HLT
#  (may want to turn this off for MC)
#

import FWCore.ParameterSet.Config as cms
import os, re
version = os.environ['CMSSW_VERSION']

process = cms.Process("SHSCPMuonTree")

process.load('Configuration/StandardSequences/Services_cff')
process.load('FWCore/MessageService/MessageLogger_cfi')
process.MessageLogger.cerr.threshold = ''
process.MessageLogger.cerr.FwkReport.reportEvery = 1000


# geometry & magnetic field
process.load('Configuration.Geometry.GeometryIdeal_cff') #for CMSSSW 53X, 71X
process.load("Configuration.StandardSequences.MagneticField_38T_cff")
process.load("Configuration.StandardSequences.Reconstruction_cff")

# conditions
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')

# HLT bit filter
process.load('HLTrigger.HLTfilters.hltHighLevel_cfi')
process.hltHighLevel.TriggerResultsTag = cms.InputTag("TriggerResults","","HLT")
process.hltHighLevel.throw = cms.bool(False)
process.hltHighLevel.HLTPaths = cms.vstring(
    "HLT_L2Mu10_NoVertex_NoBPTX3BX_v*",
    "HLT_L2Mu10_NoVertex_NoBPTX3BX_NoHalo_v*"
)

process.hltStoppedHSCPMuonHpdFilter = cms.EDFilter( "HLTHPDFilter",
    inputTag = cms.InputTag( "hbhereco" ),
    energy = cms.double( -99.0 ),
    hpdSpikeEnergy = cms.double( 10.0 ),
    hpdSpikeIsolationEnergy = cms.double( 1.0 ),
    rbxSpikeEnergy = cms.double( 50.0 ),
    rbxSpikeUnbalance = cms.double( 0.2 )
)

# add a flag indicating the HBHE noise 
#process.load('CommonTools/RecoAlgos/HBHENoiseFilterResultProducer_cfi')
#process.HBHENoiseFilterResultProducer.minNumIsolatedNoiseChannels = cms.int32(999999)
#process.HBHENoiseFilterResultProducer.minIsolatedNoiseSumE = cms.double(999999.)
#process.HBHENoiseFilterResultProducer.minIsolatedNoiseSumEt = cms.double(999999.)
#process.HBHENoiseFilterResultProducer.useTS4TS5=False
#process.HBHENoiseFilterResultProducer.maxRatio=0.96
#process.HBHENoiseFilterResultProducer.minRatio=0.70

# get RAW data
process.load('Configuration/StandardSequences/RawToDigi_Data_cff')
process.load('Configuration/StandardSequences/L1Extra_cff')

# Ntuple producer
process.load('StoppedHSCPMuon/Ntuples/stoppedHSCPMuonTree_cfi')

# get jet corrections
process.load('JetMETCorrections.Configuration.DefaultJEC_cff')
process.stoppedHSCPMuonTree.jetCorrectorServiceName = cms.untracked.string("ak5CaloL2L3")
#process.ak5CaloL1Offset.useCondDB = False

# histogram producer
process.load('StoppedHSCPMuon/Ntuples/stoppedHSCPMuonHistograms_cfi')

# TOF Reconstruction
#process.load('StoppedHSCPMuon/Ntuples/muontiming_cff')

# Smart propagator with IP
#process.smartPropagatorWithIPESProducer = cms.ESProducer("SmartPropagatorWithIPESProducer",
                                                         #ComponentName = cms.string('SmartPropagatorWithIP'),
                                                         #TrackerPropagator = cms.string('PropagatorWithMaterial'),
                                                         #MuonPropagator = cms.string('SteppingHelixPropagatorAny'),
                                                         #PropagationDirection = cms.string('alongMomentum'),
                                                         #Epsilon = cms.double(10.0) # the standard one has 5., but uses 10 hardcoded internally...
                                                         #)

# path
process.ntuple = cms.Path(

# refit DT segments/timing
    #process.dt4DSegmentsMT
    #+process.muontiming
    #+process.muontimingDelayedMuons

# filter on HLT bit
    process.hltHighLevel

# replicate HLT filter (for early 2011 data)
    #+process.hltStoppedHSCPMuonHpdFilter

# filter HCAL noise
    #+process.HBHENoiseFilterResultProducer

# get hcal digis
    +process.gctDigis
    +process.gtDigis
    +process.l1extraParticles
    +process.hcalDigis

# generate TTree    
    +process.stoppedHSCPMuonTree

    +process.stoppedHSCPMuonHistograms
)


#process.OUT = cms.OutputModule("PoolOutputModule",
     #outputCommands = cms.untracked.vstring(
         #"keep *",
    #),
    #fileName = cms.untracked.string('/uscms_data/d3/ssirisky/HSCP.root')
#)

#process.endPath = cms.EndPath(process.OUT)

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


# input files
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
process.source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)


# Global Tag and input files
#process.GlobalTag.globaltag = "GR10_P_V10::All"

readFiles.extend( [

    ] )


secFiles.extend( [

    ] )
