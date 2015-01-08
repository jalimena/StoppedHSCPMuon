#
#  produce stopped HSCPMuon TTree
#  assumes RAW, HLT, RECO data present
#  Run this on StoppedHSCPMuon Skim
#
#  includes a check that the event passed stopped HSCPMuon HLT
#  (may want to turn this off for MC)
#

import FWCore.ParameterSet.Config as cms

process = cms.Process("SHSCPMuonTree")

process.load('Configuration/StandardSequences/Services_cff')
process.load('FWCore/MessageService/MessageLogger_cfi')
process.MessageLogger.cerr.threshold = ''
process.MessageLogger.cerr.FwkReport.reportEvery = 1000


# geometry & magnetic field
#process.load('Configuration/StandardSequences/GeometryIdeal_cff')
process.load('Configuration.Geometry.GeometryIdeal_cff')
process.load("Configuration.StandardSequences.MagneticField_38T_cff")
process.load("Configuration.StandardSequences.Reconstruction_cff")

# conditions
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')

# HLT bit filter
process.load('HLTrigger.HLTfilters.hltHighLevel_cfi')
process.hltHighLevel.TriggerResultsTag = cms.InputTag("TriggerResults","","HLT")
process.hltHighLevel.throw = cms.bool(False)
process.hltHighLevel.HLTPaths = cms.vstring(
    "HLT_JetE30_NoBPTX_v*",
    "HLT_JetE30_NoBPTX3BX_v*",
    "HLT_JetE30_NoBPTX3BX_NoHalo_v*",
    "HLT_JetE50_NoBPTX3BX_v*",
    "HLT_JetE50_NoBPTX3BX_NoHalo_v*",
    "HLT_JetE70_NoBPTX3BX_v*",
    "HLT_JetE70_NoBPTX3BX_NoHalo_v*"
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

# Smart propagator with IP
process.smartPropagatorWithIPESProducer = cms.ESProducer("SmartPropagatorWithIPESProducer",
                                                         ComponentName = cms.string('SmartPropagatorWithIP'),
                                                         TrackerPropagator = cms.string('PropagatorWithMaterial'),
                                                         MuonPropagator = cms.string('SteppingHelixPropagatorAny'),
                                                         PropagationDirection = cms.string('alongMomentum'),
                                                         Epsilon = cms.double(10.0) # the standard one has 5., but uses 10 hardcoded internally...
                                                         )

# path
process.ntuple = cms.Path(

# filter on HLT bit
    process.hltHighLevel

# replicate HLT filter (for early 2011 data)
    +process.hltStoppedHSCPMuonHpdFilter

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


# TTree output file
process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('stoppedHSCPMuonTree.root')
)


# input files
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10000) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
process.source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)


# Global Tag and input files
process.GlobalTag.globaltag = "GR10_P_V10::All"

readFiles.extend( [

    ] )


secFiles.extend( [

    ] )
