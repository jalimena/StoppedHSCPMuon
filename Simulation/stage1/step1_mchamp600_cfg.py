# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: Configuration/GenProduction/python/EightTeV/HSCPmchamp6_M_600_TuneZ2star_8TeV_pythia6_cff.py --fileout file:step1_mchamp600.root --mc --eventcontent RAWSIM --datatier GEN-SIM --conditions START71_V8A::All --beamspot Realistic8TeVCollision --step GEN,SIM --python_filename step1_mchamp600_cfg.py --no_exec --customise Configuration/DataProcessing/Utils.addMonitoring,SimG4Core/CustomPhysics/Exotica_HSCP_SIM_cfi.customise -n 50
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
    annotation = cms.untracked.string('Configuration/GenProduction/python/EightTeV/HSCPmchamp6_M_600_TuneZ2star_8TeV_pythia6_cff.py nevts:50'),
    name = cms.untracked.string('Applications')
)

# Output definition

process.RAWSIMoutput = cms.OutputModule("PoolOutputModule",
    splitLevel = cms.untracked.int32(0),
    eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
    outputCommands = process.RAWSIMEventContent.outputCommands,
    fileName = cms.untracked.string('file:step1_mchamp600.root'),
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

process.generator = cms.EDFilter("Pythia6GeneratorFilter",
    crossSection = cms.untracked.double(-1),
    maxEventsToPrint = cms.untracked.int32(0),
    filterEfficiency = cms.untracked.double(1.0),
    comEnergy = cms.double(8000.0),
    PythiaParameters = cms.PSet(
        pythiaUESettings = cms.vstring('MSTU(21)=1     ! Check on possible errors during program execution', 
            'MSTJ(22)=2     ! Decay those unstable particles', 
            'PARJ(71)=10 .  ! for which ctau  10 mm', 
            'MSTP(33)=0     ! no K factors in hard cross sections', 
            'MSTP(2)=1      ! which order running alphaS', 
            'MSTP(51)=10042 ! structure function chosen (external PDF CTEQ6L1)', 
            'MSTP(52)=2     ! work with LHAPDF', 
            'PARP(82)=1.921 ! pt cutoff for multiparton interactions', 
            'PARP(89)=1800. ! sqrts for which PARP82 is set', 
            'PARP(90)=0.227 ! Multiple interactions: rescaling power', 
            'MSTP(95)=6     ! CR (color reconnection parameters)', 
            'PARP(77)=1.016 ! CR', 
            'PARP(78)=0.538 ! CR', 
            'PARP(80)=0.1   ! Prob. colored parton from BBR', 
            'PARP(83)=0.356 ! Multiple interactions: matter distribution parameter', 
            'PARP(84)=0.651 ! Multiple interactions: matter distribution parameter', 
            'PARP(62)=1.025 ! ISR cutoff', 
            'MSTP(91)=1     ! Gaussian primordial kT', 
            'PARP(93)=10.0  ! primordial kT-max', 
            'MSTP(81)=21    ! multiple parton interactions 1 is Pythia default', 
            'MSTP(82)=4     ! Defines the multi-parton model'),
        processParameters = cms.vstring('MSEL=0 ! User defined processes', 
            'MSUB(1)=1 !', 
            'MSTP(43) = 3 ! complete Z0/gamma* interference', 
            'MSTP(1)=4 !fourth generation', 
            'CKIN(1)=600.000000 !min sqrt(s hat)', 
            'CKIN(2)= -1 ! (no) max sqrt(s hat) (GeV)', 
            'KCHG(17,1)=6 !charge of tauprime', 
            'PMAS(17,1)=600.000000 !tauprime mass', 
            'MDME(174,1) = 0 !Z decay into d dbar', 
            'MDME(175,1) = 0 !Z decay into u ubar', 
            'MDME(176,1) = 0 !Z decay into s sbar', 
            'MDME(177,1) = 0 !Z decay into c cbar', 
            'MDME(178,1) = 0 !Z decay into b bbar', 
            'MDME(179,1) = 0 !Z decay into t tbar', 
            'MDME(180,1) = 0 !Z decay into bprime bprimebar', 
            'MDME(181,1) = 0 !Z decay into tprime tprimebar', 
            'MDME(182,1) = 0 !Z decay into e- e+', 
            'MDME(183,1) = 0 !Z decay into nu_e nu_ebar', 
            'MDME(184,1) = 0 !Z decay into mu- mu+', 
            'MDME(185,1) = 0 !Z decay into nu_mu nu_mubar', 
            'MDME(186,1) = 0 !Z decay into tau- tau+', 
            'MDME(187,1) = 0 !Z decay into nu_tau nu_taubar', 
            'MDME(188,1) = 1 !Z decay into tauprime tauprimebar', 
            'MDME(189,1) = 0 !Z decay into nu_tauprime nu_tauprimebar', 
            'MDCY(17,1)=0 ! set tauprime stable', 
            'MWID(17)=0 ! set tauprime width 0'),
        parameterSets = cms.vstring('pythiaUESettings', 
            'processParameters')
    ),
    hscpFlavor = cms.untracked.string('stau'),
    massPoint = cms.untracked.int32(600),
    slhaFile = cms.untracked.string('None'),
    processFile = cms.untracked.string('SimG4Core/CustomPhysics/data/RhadronProcessList.txt'),
    particleFile = cms.untracked.string('Configuration/Generator/data/particles_HIP6_stau_600_GeV.txt'),
    pdtFile = cms.FileInPath('Configuration/Generator/data/hscppythiapdtHIP6stau600.tbl')
)


process.ProductionFilterSequence = cms.Sequence(process.generator)

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
