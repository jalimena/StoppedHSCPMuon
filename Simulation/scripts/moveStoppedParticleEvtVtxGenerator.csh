#!/bin/csh

mv $CMSSW_BASE/src/StoppedHSCPMuon/Simulation/plugins/StoppedParticleEvtVtxGenerator.cc $CMSSW_BASE/src/IOMC/EventVertexGenerators/src
mv $CMSSW_BASE/src/StoppedHSCPMuon/Simulation/plugins/StoppedParticleEvtVtxGenerator.h $CMSSW_BASE/src/IOMC/EventVertexGenerators/interface

cat $CMSSW_BASE/src/IOMC/EventVertexGenerators/src/module.cc $CMSSW_BASE/src/StoppedHSCPMuon/Simulation/scripts/module_addition.cc > $CMSSW_BASE/src/IOMC/EventVertexGenerators/src/module_full.cc
mv $CMSSW_BASE/src/IOMC/EventVertexGenerators/src/module_full.cc $CMSSW_BASE/src/IOMC/EventVertexGenerators/src/module.cc
