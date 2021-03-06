# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: Configuration/GenProduction/python/EightTeV/HSCPstop_M_1000_Tune4C_8TeV_pythia8_cff.py --fileout file:step1_stop1000.root --mc --eventcontent RAWSIM --datatier GEN-SIM --conditions START71_V8A::All --beamspot Realistic8TeVCollision --step GEN,SIM --python_filename step1_stop1000_cfg.py --no_exec --customise Configuration/DataProcessing/Utils.addMonitoring,SimG4Core/CustomPhysics/Exotica_HSCP_SIM_cfi.customise -n 50
import FWCore.ParameterSet.Config as cms

process = cms.Process('SIM')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.Geometry.GeometrySimDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.Generator_cff')
process.load('IOMC.EventVertexGenerators.VtxSmearedRealistic8TeVCollision_cfi')
process.load('GeneratorInterface.Core.genFilterSummary_cff')
process.load('Configuration.StandardSequences.SimIdeal_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(50)
)

# Input source
process.source = cms.Source("EmptySource")

process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.19 $'),
    annotation = cms.untracked.string('Configuration/GenProduction/python/EightTeV/HSCPstop_M_1000_Tune4C_8TeV_pythia8_cff.py nevts:50'),
    name = cms.untracked.string('Applications')
)

# Output definition

process.RAWSIMoutput = cms.OutputModule("PoolOutputModule",
    splitLevel = cms.untracked.int32(0),
    eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
    outputCommands = process.RAWSIMEventContent.outputCommands,
    fileName = cms.untracked.string('file:step1_stop1000.root'),
    dataset = cms.untracked.PSet(
        filterName = cms.untracked.string(''),
        dataTier = cms.untracked.string('GEN-SIM')
    ),
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('generation_step')
    )
)

# Additional output definition

# Other statements
process.genstepfilter.triggerConditions=cms.vstring("generation_step")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'START71_V8A::All', '')

process.dirhadrongenfilter = cms.EDFilter("MCParticlePairFilter",
    Status = cms.untracked.vint32(1, 1),
    MinPt = cms.untracked.vdouble(0.0, 0.0),
    MaxEta = cms.untracked.vdouble(100.0, 100.0),
    MinEta = cms.untracked.vdouble(-100, -100),
    ParticleCharge = cms.untracked.int32(0),
    MinP = cms.untracked.vdouble(0.0, 0.0),
    ParticleID1 = cms.untracked.vint32(1000612, 1000622, 1000632, 1000642, 1000652, 
        1006113, 1006211, 1006213, 1006223, 1006311, 
        1006313, 1006321, 1006323, 1006333),
    ParticleID2 = cms.untracked.vint32(1000612, 1000622, 1000632, 1000642, 1000652, 
        1006113, 1006211, 1006213, 1006223, 1006311, 
        1006313, 1006321, 1006323, 1006333)
)


process.generator = cms.EDFilter("Pythia8GeneratorFilter",
    pythiaPylistVerbosity = cms.untracked.int32(0),
    filterEfficiency = cms.untracked.double(-1),
    pythiaHepMCVerbosity = cms.untracked.bool(False),
    SLHAFileForPythia8 = cms.string('Configuration/Generator/data/HSCP_stop_1000_SLHA.spc'),
    comEnergy = cms.double(8000.0),
    crossSection = cms.untracked.double(-1),
    maxEventsToPrint = cms.untracked.int32(0),
    PythiaParameters = cms.PSet(
        processParameters = cms.vstring('Tune:pp = 5', 
            'SUSY:all = off', 
            'SUSY:gg2squarkantisquark = on', 
            'SUSY:qqbar2squarkantisquark= on', 
            'RHadrons:allow = on', 
            'RHadrons:allowDecay = off', 
            'RHadrons:setMasses = on'),
        parameterSets = cms.vstring('processParameters')
    ),
    hscpFlavor = cms.untracked.string('stop'),
    massPoint = cms.untracked.int32(1000),
    particleFile = cms.untracked.string('Configuration/Generator/data/particles_stop_1000_GeV.txt'),
    slhaFile = cms.untracked.string('Configuration/Generator/data/HSCP_stop_1000_SLHA.spc'),
    processFile = cms.untracked.string('SimG4Core/CustomPhysics/data/stophadronProcessList.txt'),
    pdtFile = cms.FileInPath('Configuration/Generator/data/hscppythiapdtstop1000.tbl')
)


process.ProductionFilterSequence = cms.Sequence(process.generator+process.dirhadrongenfilter)

# Path and EndPath definitions
process.generation_step = cms.Path(process.pgen)
process.simulation_step = cms.Path(process.psim)
process.genfiltersummary_step = cms.EndPath(process.genFilterSummary)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.RAWSIMoutput_step = cms.EndPath(process.RAWSIMoutput)

# Schedule definition
process.schedule = cms.Schedule(process.generation_step,process.genfiltersummary_step,process.simulation_step,process.endjob_step,process.RAWSIMoutput_step)
# filter all path with the production filter sequence
for path in process.paths:
	getattr(process,path)._seq = process.ProductionFilterSequence * getattr(process,path)._seq 

# customisation of the process.

# Automatic addition of the customisation function from Configuration.DataProcessing.Utils
from Configuration.DataProcessing.Utils import addMonitoring 

#call to customisation function addMonitoring imported from Configuration.DataProcessing.Utils
process = addMonitoring(process)

# Automatic addition of the customisation function from SimG4Core.CustomPhysics.Exotica_HSCP_SIM_cfi
from SimG4Core.CustomPhysics.Exotica_HSCP_SIM_cfi import customise 

#call to customisation function customise imported from SimG4Core.CustomPhysics.Exotica_HSCP_SIM_cfi
process = customise(process)

# End of customisation functions
