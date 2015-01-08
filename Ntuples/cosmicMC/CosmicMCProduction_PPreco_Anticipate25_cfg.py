# Auto generated configuration file
# using: 
# Revision: 1.381.2.18 
# Source: /local/reps/CMSSW/CMSSW/Configuration/PyReleaseValidation/python/ConfigBuilder.py,v 
# with command line options: UndergroundCosmicMu_cfi.py -s GEN,SIM,DIGI,L1,DIGI2RAW,HLT:7E33v4,RAW2DIGI,RECO -n -1 --mc --magField AutoFromDBCurrent --conditions START53_V7A::All --eventcontent RECO --datatier RECO --scenario pp --fileout file:full.root --no_exec --python_filename step23_ALCARECO_PEAK38T_cfg_FULL.py
import FWCore.ParameterSet.Config as cms

process = cms.Process('HLT')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.GeometrySimDB_cff')
process.load('Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff')
process.load('Configuration.StandardSequences.Generator_cff')
# process.load('IOMC.EventVertexGenerators.VtxSmearedRealistic8TeVCollision_cfi')
process.load('Configuration.StandardSequences.VtxSmearedNoSmear_cff')
process.load('GeneratorInterface.Core.genFilterSummary_cff')
# process.load('Configuration.StandardSequences.SimIdeal_cff')
process.load('Configuration.StandardSequences.SimNOBEAM_cff')
process.load('Configuration.StandardSequences.Digi_cff')
process.load('Configuration.StandardSequences.SimL1Emulator_cff')
process.load('Configuration.StandardSequences.DigiToRaw_cff')
process.load('HLTrigger.Configuration.HLT_2014_cff')
process.load('Configuration.StandardSequences.RawToDigi_cff')
process.load('Configuration.StandardSequences.Reconstruction_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    #input = cms.untracked.int32(-1)
    input = cms.untracked.int32(100)
)

# Input source
process.source = cms.Source("EmptySource")

process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.381.2.18 $'),
    annotation = cms.untracked.string('UndergroundCosmicMu_cfi.py nevts:-1'),
    name = cms.untracked.string('PyReleaseValidation')
)

# Random seeds
process.RandomNumberGeneratorService.generator.initialSeed      = 1
process.RandomNumberGeneratorService.VtxSmeared.initialSeed     = 2
process.RandomNumberGeneratorService.g4SimHits.initialSeed      = 3
process.RandomNumberGeneratorService.mix.initialSeed            = 4


# Output definition
process.RECOoutput = cms.OutputModule("PoolOutputModule",
    splitLevel = cms.untracked.int32(0),
    eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
     outputCommands = process.RECOEventContent.outputCommands,
    #outputCommands = cms.untracked.vstring("drop *"),
    fileName = cms.untracked.string('CosmicMC.root'),
    dataset = cms.untracked.PSet(
        filterName = cms.untracked.string(''),
        dataTier = cms.untracked.string('RECO')
    ),
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('generation_step')
    )
)

# Additional output definition
process.RECOoutput.outputCommands.append("keep *_genParticles_*_*")

# Other statements
process.genstepfilter.triggerConditions=cms.vstring("generation_step")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'PRE_STA72_V6::All', '')
#process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run1_mc', '')

process.cosmicInTracker = cms.EDFilter("CosmicGenFilterHelix",
    maxZ = cms.double(1000.0),
    src = cms.InputTag("generator"),
    minPt = cms.double(0.0),
    charges = cms.vint32(1, -1),
    pdgIds = cms.vint32(-13, 13),
    minZ = cms.double(-1000.0),
    radius = cms.double(500.0),
    doMonitor = cms.untracked.bool(False),
    minP = cms.double(0.0),
    propagator = cms.string('SteppingHelixPropagatorAlong')
)


process.generator = cms.EDProducer("CosMuoGenProducer",
    AcptAllMu = cms.bool(False),
    ClayWidth = cms.double(50000.0),
    MinP = cms.double(10.0),
    MTCCHalf = cms.bool(False),
    MinPhi = cms.double(0.0),
    TIFOnly_constant = cms.bool(False),
    MaxP = cms.double(3000.0),
    NuProdAlt = cms.double(7500000.0),
    RhoAir = cms.double(0.001214),
    ZDistOfTarget = cms.double(15000.0),
    PlugVx = cms.double(0.0),
    PlugVz = cms.double(-14000.0),
    MultiMuonFileFirstEvent = cms.int32(1),
    MinT0 = cms.double(-37.5),
    RadiusOfTarget = cms.double(8000.0),
    RhoPlug = cms.double(2.5),
    TIFOnly_linear = cms.bool(False),
    MultiMuonNmin = cms.int32(2),
    MaxPhi = cms.double(360.0),
    Verbosity = cms.bool(False),
    MaxT0 = cms.double(-12.5),
    ZCentrOfTarget = cms.double(0.0),
    ElossScaleFactor = cms.double(1.0),
    MinTheta = cms.double(0.0),
    MinP_CMS = cms.double(-1.0),
    RhoRock = cms.double(2.5),
    RhoClay = cms.double(2.3),
    TrackerOnly = cms.bool(False),
    MaxTheta = cms.double(75.0),
    MinEnu = cms.double(10.0),
    MaxEnu = cms.double(10000.0),
    MultiMuon = cms.bool(False),
    MultiMuonFileName = cms.string('CORSIKAmultiMuon.root'),
    RhoWall = cms.double(2.5)
)


process.SteppingHelixPropagatorAlong = cms.ESProducer("SteppingHelixPropagatorESProducer",
    endcapShiftInZNeg = cms.double(0.0),
    PropagationDirection = cms.string('alongMomentum'),
    useMatVolumes = cms.bool(True),
    useTuningForL2Speed = cms.bool(False),
    useIsYokeFlag = cms.bool(True),
    NoErrorPropagation = cms.bool(False),
    SetVBFPointer = cms.bool(False),
    AssumeNoMaterial = cms.bool(False),
    returnTangentPlane = cms.bool(True),
    useInTeslaFromMagField = cms.bool(False),
    VBFName = cms.string('VolumeBasedMagneticField'),
    useEndcapShiftsInZ = cms.bool(False),
    sendLogWarning = cms.bool(False),
    ComponentName = cms.string('SteppingHelixPropagatorAlong'),
    debug = cms.bool(False),
    ApplyRadX0Correction = cms.bool(True),
    useMagVolumes = cms.bool(True),
    endcapShiftInZPos = cms.double(0.0)
)

process.ProductionFilterSequence = cms.Sequence(process.generator+process.cosmicInTracker)

# Path and EndPath definitions
process.generation_step = cms.Path(process.pgen)
process.simulation_step = cms.Path(process.psim)
process.digitisation_step = cms.Path(process.pdigi)
process.L1simulation_step = cms.Path(process.SimL1Emulator)
process.digi2raw_step = cms.Path(process.DigiToRaw)
process.raw2digi_step = cms.Path(process.RawToDigi)
process.reconstruction_step = cms.Path(process.reconstruction)
process.genfiltersummary_step = cms.EndPath(process.genFilterSummary)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.RECOoutput_step = cms.EndPath(process.RECOoutput)

# Schedule definition
process.schedule = cms.Schedule(process.generation_step,process.genfiltersummary_step,process.simulation_step,process.digitisation_step,process.L1simulation_step,process.digi2raw_step)
process.schedule.extend(process.HLTSchedule)
process.schedule.extend([process.raw2digi_step,process.reconstruction_step,process.endjob_step,process.RECOoutput_step])
# filter all path with the production filter sequence
for path in process.paths:
	getattr(process,path)._seq = process.ProductionFilterSequence * getattr(process,path)._seq 

# customisation of the process.

# Automatic addition of the customisation function from HLTrigger.Configuration.customizeHLTforMC
from HLTrigger.Configuration.customizeHLTforMC import customizeHLTforMC 

#call to customisation function customizeHLTforMC imported from HLTrigger.Configuration.customizeHLTforMC
process = customizeHLTforMC(process)

# End of customisation functions

# Customisation from command line
process.generator.MinP=cms.double(7.0) 
process.simSiStripDigis.APVpeakmode = cms.bool(True) 
