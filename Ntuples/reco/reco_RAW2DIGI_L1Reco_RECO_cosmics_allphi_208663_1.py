# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: reco -s RAW2DIGI,L1Reco,RECO --filein dbs:/NoBPTX/Run2012D-v1/RAW --fileout file:reco_NoBPTX_Run2012D.root --data --conditions GR_R_72_V2::All --eventcontent RECO --datatier RECO -n -1 --no_exec
import FWCore.ParameterSet.Config as cms

process = cms.Process('RECO')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff')
process.load('Configuration.StandardSequences.RawToDigi_Data_cff')
process.load('Configuration.StandardSequences.L1Reco_cff')
process.load('Configuration.StandardSequences.Reconstruction_Data_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
    #input = cms.untracked.int32(10)
)

# Input source
process.source = cms.Source("PoolSource",
    secondaryFileNames = cms.untracked.vstring(),
    fileNames = cms.untracked.vstring(
        'root://xrootd.unl.edu//store/data/Run2012D/NoBPTX/RAW/v1/000/208/593/EE7FE1F8-E93E-E211-893E-BCAEC532971B.root',
        'root://xrootd.unl.edu//store/data/Run2012D/NoBPTX/RAW/v1/000/208/628/ECCF88B4-F73E-E211-8C3C-00237DDC5BBC.root',
        'root://xrootd.unl.edu//store/data/Run2012D/NoBPTX/RAW/v1/000/208/635/D266569B-EE3E-E211-B828-001D09F24024.root',
        'root://xrootd.unl.edu//store/data/Run2012D/NoBPTX/RAW/v1/000/208/636/2022DB00-F13E-E211-B491-001D09F26C5C.root',
        'root://xrootd.unl.edu//store/data/Run2012D/NoBPTX/RAW/v1/000/208/636/36ECE709-F13E-E211-ABF5-001D09F276CF.root',
        'root://xrootd.unl.edu//store/data/Run2012D/NoBPTX/RAW/v1/000/208/636/3EC2C8EA-F13E-E211-B7DF-0025901D5DB8.root',
        'root://xrootd.unl.edu//store/data/Run2012D/NoBPTX/RAW/v1/000/208/636/78B63564-F13E-E211-BE83-5404A63886CE.root',
        'root://xrootd.unl.edu//store/data/Run2012D/NoBPTX/RAW/v1/000/208/636/906F703A-F63E-E211-9EDC-BCAEC532971F.root',
        'root://xrootd.unl.edu//store/data/Run2012D/NoBPTX/RAW/v1/000/208/636/9C95E659-F23E-E211-BDFC-E0CB4E55365C.root',
        'root://xrootd.unl.edu//store/data/Run2012D/NoBPTX/RAW/v1/000/208/636/DE0BCA64-F13E-E211-A928-002481E0D524.root',
        'root://xrootd.unl.edu//store/data/Run2012D/NoBPTX/RAW/v1/000/208/636/EEC47735-F53E-E211-8FF3-0025901D626C.root',
        'root://xrootd.unl.edu//store/data/Run2012D/NoBPTX/RAW/v1/000/208/636/F253EE12-F03E-E211-97BD-5404A63886E6.root',
        'root://xrootd.unl.edu//store/data/Run2012D/NoBPTX/RAW/v1/000/208/651/7C91F310-FD3E-E211-9617-001D09F25041.root',
        'root://xrootd.unl.edu//store/data/Run2012D/NoBPTX/RAW/v1/000/208/651/DE823F0D-FD3E-E211-A00B-003048CF94A8.root',
        'root://xrootd.unl.edu//store/data/Run2012D/NoBPTX/RAW/v1/000/208/655/747BCCC6-FF3E-E211-B238-5404A63886B1.root',
        'root://xrootd.unl.edu//store/data/Run2012D/NoBPTX/RAW/v1/000/208/660/C6DE5519-053F-E211-A895-0030486780A8.root',
        'root://xrootd.unl.edu//store/data/Run2012D/NoBPTX/RAW/v1/000/208/663/20679BD2-053F-E211-8EEF-003048D2BB58.root',
        'root://xrootd.unl.edu//store/data/Run2012D/NoBPTX/RAW/v1/000/208/666/34EE24D6-0A3F-E211-92BC-001D09F23A20.root'
        )
)

process.source.lumisToProcess = cms.untracked.VLuminosityBlockRange(
    #'208593:1-208593:30'
    #'208593:31-208593:60'
    #'208593:61-208593:90'
    #'208593:91-208593:120'
    #'208593:121-208593:150'
    #'208593:151-208593:180'
    #'208593:181-208593:210'
    #'208593:211-208593:245'

    #'208628:1-208628:5'

    #'208635:1-208635:9'

    #'208636:1-208636:17'

    #'208651:1-208651:30'
    #'208651:31-208651:60'
    #'208651:61-208651:90'
    #'208651:91-208651:128'

    #'208655:1-208655:35'

    #'208660:1-208660:30'
    #'208660:31-208660:60'
    #'208660:61-208660:89'

    '208663:1-208663:24'

    #'208664:1-208664:11'

    #'208666:1-208666:30'

    )

process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.19 $'),
    annotation = cms.untracked.string('reco nevts:-1'),
    name = cms.untracked.string('Applications')
)

# Output definition

process.RECOoutput = cms.OutputModule("PoolOutputModule",
    splitLevel = cms.untracked.int32(0),
    eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
    outputCommands = process.RECOEventContent.outputCommands,
    fileName = cms.untracked.string('file:reco_NoBPTX_Run2012D_cosmics_allphi.root'),
    dataset = cms.untracked.PSet(
        filterName = cms.untracked.string(''),
        dataTier = cms.untracked.string('RECO')
    )
)

# Additional output definition

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'GR_R_72_V2::All', '')

from RecoMuon.Configuration.RecoMuonPPonly_cff import *

# Seed generator
from RecoMuon.MuonSeedGenerator.CosmicMuonSeedProducer_cfi import *
CosmicMuonSeed.DTRecSegmentLabel = 'dt4DCosmicSegments'

standAloneMuons.InputObjects = cms.InputTag("CosmicMuonSeed")
refittedStandAloneMuons.InputObjects = cms.InputTag("CosmicMuonSeed")

standAloneMuons.MuonTrajectoryBuilder = cms.string("StandAloneMuonTrajectoryBuilder")
refittedStandAloneMuons.MuonTrajectoryBuilder = cms.string("StandAloneMuonTrajectoryBuilder")

# Muon Tracking sequence
standalonemuontracking = cms.Sequence(CosmicMuonSeed*standAloneMuons*refittedStandAloneMuons)

# Path and EndPath definitions
process.raw2digi_step = cms.Path(process.RawToDigi)
process.L1Reco_step = cms.Path(process.L1Reco)
process.reconstruction_step = cms.Path(process.reconstruction)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.RECOoutput_step = cms.EndPath(process.RECOoutput)

# Schedule definition
process.schedule = cms.Schedule(process.raw2digi_step,process.L1Reco_step,process.reconstruction_step,process.endjob_step,process.RECOoutput_step)


