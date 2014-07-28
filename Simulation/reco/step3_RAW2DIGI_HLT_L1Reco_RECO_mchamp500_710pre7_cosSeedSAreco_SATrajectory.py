# Auto generated configuration file
# using: 
# Revision: 1.381.2.18 
# Source: /local/reps/CMSSW/CMSSW/Configuration/PyReleaseValidation/python/ConfigBuilder.py,v 
# with command line options: step3 --filein file:step2_DIGI_L1_DIGI2RAW_HLT.root --step RAW2DIGI,HLT:7E33v3,L1Reco,RECO --conditions START53_V19::All --pileup NoPileUp --datamix NODATAMIXER --datatier GEN-SIM-RECO --eventcontent RECOSIM -n -1 --no_exec
import FWCore.ParameterSet.Config as cms

process = cms.Process('HLT2')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.RawToDigi_cff')
#process.load('HLTrigger.Configuration.HLT_7E33v3_cff')
process.load('HLTrigger.Configuration.HLT_2013_cff')
process.load('Configuration.StandardSequences.L1Reco_cff')
process.load('Configuration.StandardSequences.Reconstruction_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    #input = cms.untracked.int32(-1)
    #input = cms.untracked.int32(1000)
    input = cms.untracked.int32(2)
)

# Input source
process.source = cms.Source("PoolSource",
                            secondaryFileNames = cms.untracked.vstring(),
                            fileNames = cms.untracked.vstring('root://eoscms//eos/cms/store/user/jalimena/HSCPmchamp6_M-500_TuneZ2star_8TeV-pythia6/stage2_step1_710pre6/ff147a0c9f55a97f48bbabe25fe1f227/stage2_GEN-HLT_mchamp500_9_1_QAl.root')
                            )

process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.19 $'),
    annotation = cms.untracked.string('step3 nevts:-1'),
    name = cms.untracked.string('Applications')
)

# Output definition

process.RECOSIMoutput = cms.OutputModule("PoolOutputModule",
                                         splitLevel = cms.untracked.int32(0),
                                         eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
                                         outputCommands = process.RECOSIMEventContent.outputCommands,
                                         fileName = cms.untracked.string('step3_RAW2DIGI_HLT_L1Reco_RECO_mchamp500.root'),
                                         #fileName = cms.untracked.string('root://eoscms//eos/cms/store/user/jalimena/HSCPmchamp6_M-500_TuneZ2star_8TeV-pythia6/reco_mchamp500_710pre7_PRESTA71V3_cosSeedSAreco_SATrajectory/step3_RAW2DIGI_HLT_L1Reco_RECO_mchamp500.root'),
                                         dataset = cms.untracked.PSet(
    filterName = cms.untracked.string(''),
    dataTier = cms.untracked.string('GEN-SIM-RECO')
    )
                                         )
process.RECOSIMoutput.outputCommands.append('drop *_*_*_SIM')
process.RECOSIMoutput.outputCommands.append('keep *_*_Stopped*_SIM')
process.RECOSIMoutput.outputCommands.append('keep *_generator_*_SIM')

# Additional output definition

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, 'START53_V19::All', '')
#process.GlobalTag = GlobalTag(process.GlobalTag, 'START71_V1::All', '')
#process.GlobalTag = GlobalTag(process.GlobalTag, 'PRE_LS171_V4::All', '')
#process.GlobalTag = GlobalTag(process.GlobalTag, 'PRE_LS171_V7::All', '')
process.GlobalTag = GlobalTag(process.GlobalTag, 'PRE_STA71_V3::All', '')


# new DT errors
process.GlobalTag.toGet = cms.VPSet(
 cms.PSet(record = cms.string("DTRecoUncertaintiesRcd"),
   tag = cms.string("DTRecoUncertainties_test"),
   connect = cms.untracked.string("sqlite_file:/afs/cern.ch/user/n/namapane/public/DT/DTUncertainties/DTRecoUncertainties_True_v0.db")
 )
)


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
process.RECOSIMoutput_step = cms.EndPath(process.RECOSIMoutput)

# Schedule definition
process.schedule = cms.Schedule(process.raw2digi_step)
process.schedule.extend(process.HLTSchedule)
process.schedule.extend([process.L1Reco_step,process.reconstruction_step,process.endjob_step,process.RECOSIMoutput_step])

# customisation of the process.

# Automatic addition of the customisation function from HLTrigger.Configuration.customizeHLTforMC
from HLTrigger.Configuration.customizeHLTforMC import customizeHLTforMC 

#call to customisation function customizeHLTforMC imported from HLTrigger.Configuration.customizeHLTforMC
process = customizeHLTforMC(process)

# End of customisation functions
