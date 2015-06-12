# Modify these variables to switch masses, input stopped points files, and flavor of RHadron
SPARTICLE_MASS=1000
NEUTRALINO_MASS=200
GRAVITINO_MASS=0.00001
SAME_EVENT=True
PARTICLE_NUMBER=0
OUTPUTFILE='stage2_GEN-HLT_mchamp' + str(SPARTICLE_MASS)+'.root'

import FWCore.ParameterSet.Config as cms

process = cms.Process('HLT')

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger = cms.Service("MessageLogger",
                                    destinations  = cms.untracked.vstring( 'Info',
                                                                           'Errors',
                                                                           'Warnings',
                                                                           'Debug'),
                                    categories    = cms.untracked.vstring( 'eventNumber',
                                                                           'Root_Information',
                                                                           'EventSetupDependency'
                                                                           ),
                                    Info          = cms.untracked.PSet( threshold = cms.untracked.string('INFO'),
                                                                        #Root_Information     = cms.untracked.PSet( limit = cms.untracked.int32(0) ),
                                                                        #EventSetupDependency = cms.untracked.PSet( limit = cms.untracked.int32(0) )
                                                                        ),
                                    Errors        = cms.untracked.PSet( threshold = cms.untracked.string('ERROR') ),
                                    Warnings      = cms.untracked.PSet( threshold = cms.untracked.string('WARNING') ),
                                    Debug         = cms.untracked.PSet( threshold =  cms.untracked.string('DEBUG') ),
                                    debugModules  = cms.untracked.vstring('*')
                                    )

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.Generator_cff')
process.load('GeneratorInterface.Core.genFilterSummary_cff')
process.load('Configuration.StandardSequences.SimIdeal_cff')
process.load('Configuration.StandardSequences.Digi_cff')
process.load('Configuration.StandardSequences.SimL1Emulator_cff')
process.load('Configuration.StandardSequences.DigiToRaw_cff')
#process.load('HLTrigger.Configuration.HLT_7E33v3_cff')
process.load('HLTrigger.Configuration.HLT_2013_cff')
process.load('Configuration.StandardSequences.RawToDigi_cff')
process.load('Configuration.StandardSequences.L1Reco_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100)
    #input = cms.untracked.int32(50)
    #input = cms.untracked.int32(-1)
    )

process.options = cms.untracked.PSet(
    SkipEvent = cms.untracked.vstring( 'g4SimHits','G4HadronicProcess' )
    )

# Input source
process.source = cms.Source ("PoolSource",
                             fileNames=cms.untracked.vstring(#'file:A841BB4A-CEFE-E111-9F17-A4BADB3CF272.root'
        #'file:../stage1/step1_mchamp500.root'
        'file:/home/alimena/TestStage1Stage2/CMSSW_7_1_0/src/StoppedHSCPMuon/Simulation/stage1/step1_mchamp500.root'
                                                             )
                             )

# Output definition
process.RAWSIMoutput = cms.OutputModule("PoolOutputModule",
                                        #    outputCommands = cms.untracked.vstring('drop *_*_*_SIM',
                                        #   'keep *_*_Stopped*_SIM',
                                        #   'keep *_generator_*_SIM',
                                        #   'keep *_*_*_HLT'),
                                        splitLevel = cms.untracked.int32(0),
                                        eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
                                        outputCommands = process.RAWSIMEventContent.outputCommands,
                                        fileName = cms.untracked.string(OUTPUTFILE),
                                        dataset = cms.untracked.PSet( filterName = cms.untracked.string(''),
                                                                      dataTier = cms.untracked.string('')
                                                                      ),
                                        SelectEvents = cms.untracked.PSet( SelectEvents = cms.vstring('filter_step')
                                                                           )
                                        )

process.RAWSIMoutput.outputCommands.append('drop *_*_*_SIM')
process.RAWSIMoutput.outputCommands.append('drop *_generator_*_HLT')

process.RAWSIMoutput.outputCommands.append('keep *_*_Stopped*_SIM')
process.RAWSIMoutput.outputCommands.append('keep *_generator_*_SIM')
process.RAWSIMoutput.outputCommands.append('keep *_VtxSmeared_*_HLT')

process.eventFilter = cms.EDFilter("MCStoppedEventFilter",
                                   #   StoppedParticlesXLabel = cms.InputTag("StoppedParticlesX")
                                   PutTwoStoppedInSameEvent = cms.untracked.bool(SAME_EVENT),
                                   StoppedParticleNumber = cms.untracked.int32(PARTICLE_NUMBER)
                                   )

# Additional output definition

# Other statements
#process.GlobalTag.globaltag = 'START53_V7A::All'
#process.GlobalTag.globaltag = 'START71_V1::All'
process.GlobalTag.globaltag = 'START71_V8A::All'

process.generator = cms.EDProducer("Pythia6HSCPGun",
                                   readFromFile = cms.untracked.bool(False),
                                   stoppedData = cms.string(''),
                                   PutTwoStoppedInSameEvent = cms.untracked.bool(SAME_EVENT),
                                   StoppedParticleNumber = cms.untracked.int32(PARTICLE_NUMBER),
                                   PGunParameters = cms.PSet(MinPhi = cms.double(-3.14159265359),
                                                             ParticleID = cms.vint32(11),
                                                             neutralinoMass = cms.double(NEUTRALINO_MASS),
                                                             gravitinoMass = cms.double(GRAVITINO_MASS),
                                                             MinEta = cms.double(-10),
                                                             sparticleMass = cms.double(SPARTICLE_MASS),
                                                             MaxEta = cms.double(10),
                                                             MaxPhi = cms.double(3.14159265359),
                                                             diJetGluino = cms.bool(False),
                                                             decayTable = cms.string('src/stage2ParticlesTable.txt') #for crab
                                                             #decayTable = cms.string('../../../stage2ParticlesTable.txt') #for interactive:  where you do cmsenv
                                                             ),
                                   #pythiaPylistVerbosity = cms.untracked.int32(2),
                                   pythiaPylistVerbosity = cms.untracked.int32(3),
                                   gluinoHadrons = cms.bool(False),
                                   #gluinoHadrons = cms.bool(True),
                                   stopHadrons = cms.bool(True),
                                   #stopHadrons = cms.bool(False),
                                   #pythiaHepMCVerbosity = cms.untracked.bool(False),
                                   pythiaHepMCVerbosity = cms.untracked.bool(True),
                                   maxEventsToPrint = cms.untracked.int32(10),
                                   PythiaParameters = cms.PSet( processParameters = cms.vstring('IMSS(1)=11          ! User defined processes',
                                                                                                'IMSS(11)=1          ! allow process with gravitino as LSP!',
                                                                                                'IMSS(21) = 33       ! LUN number for SLHA File (must be 33) ',
                                                                                                'IMSS(22) = 33       ! Read-in SLHA decay table ',
                                                                                                'KCHG(17,1)=-6        ! set charge of tau prime to be 2'
                                                                                                ),
                                                                parameterSets = cms.vstring('processParameters',
                                                                                            'SLHAParameters'),
                                                                SLHAParameters = cms.vstring('SLHAFILE=stage2ParticlesTable.txt')
                                                                )
                                   )

process.genParticles = cms.EDProducer("GenParticleProducer",
                                      saveBarCodes = cms.untracked.bool(True),
                                      #src = cms.InputTag("generator"),
                                      src = cms.InputTag("VtxSmeared"),
                                      abortOnUnknownPDGCode = cms.untracked.bool(False),
                                      )

process.ProductionFilterSequence = cms.Sequence(process.generator)

# FR Extra stuff
process.load('StoppedHSCPMuon/Simulation/StoppedParticleEvtVtxGenerator_cfi')
process.VtxSmeared.PutTwoStoppedInSameEvent = SAME_EVENT
process.VtxSmeared.StoppedParticleNumber = PARTICLE_NUMBER
process.VtxSmeared.verbose = True

#Unknown particles is OK
process.genParticles.abortOnUnknownPDGCode = False

#Don't use shower library
process.g4SimHits.HCalSD.UseShowerLibrary = False

# FR END Extra stuff
#this is the only place in the GEN-SIM step, other than the input to genParticles above, where it matters to change the input collection to VtxSmeared
process.g4SimHits.Generator.HepMCProductLabel = cms.string("VtxSmeared")

# Path and EndPath definitions
process.filter_step = cms.Path(process.eventFilter)
process.generation_step = cms.Path(process.pgen)
process.simulation_step = cms.Path(process.psim)
process.digitisation_step = cms.Path(process.pdigi)
process.L1simulation_step = cms.Path(process.SimL1Emulator)
process.digi2raw_step = cms.Path(process.DigiToRaw)
process.raw2digi_step = cms.Path(process.RawToDigi)
process.L1Reco_step = cms.Path(process.L1Reco)
process.genfiltersummary_step = cms.EndPath(process.genFilterSummary)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.RAWSIMoutput_step = cms.EndPath(process.RAWSIMoutput)

# Schedule definition
process.schedule = cms.Schedule(process.filter_step,process.generation_step,process.genfiltersummary_step,process.simulation_step,process.digitisation_step,process.L1simulation_step,process.digi2raw_step)
process.schedule.extend(process.HLTSchedule)
process.schedule.extend([process.raw2digi_step,process.L1Reco_step,process.endjob_step,process.RAWSIMoutput_step])
# filter all path with the production filter sequence
for path in process.paths:
    getattr(process,path)._seq = process.ProductionFilterSequence * getattr(process,path)._seq
