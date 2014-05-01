#include "StoppedParticleEvtVtxGenerator.h"

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <ios>
#include "TRandom3.h"

#include "HepMC/SimpleVector.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/RandomNumberGenerator.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "CLHEP/Random/RandFlat.h"
#include "CLHEP/Units/SystemOfUnits.h"
//#include "CLHEP/Units/PhysicalConstants.h"
#include "./PhysicalConstants.h"

#include "GeneratorInterface/Pythia6Interface/interface/Pythia6Service.h"
#include "GeneratorInterface/Pythia6Interface/interface/Pythia6Declarations.h"

// dirty trick to work around encapsulation of EventVertexGenerators package
#include "IOMC/EventVertexGenerators/src/BaseEvtVtxGenerator.cc" 

StoppedParticleEvtVtxGenerator::StoppedParticleEvtVtxGenerator(const edm::ParameterSet & pset) 
  : BaseEvtVtxGenerator(pset),
    mVerbose (pset.getUntrackedParameter<bool> ("verbose", false)),
    mSourceLabel(pset.getParameter<edm::InputTag>("src")),
    mReadFromFile(pset.getUntrackedParameter<bool>("readFromFile", true)),
    mFileName (pset.getParameter<std::string>("stoppedData")),
    mStopPointProducer(pset.getUntrackedParameter<std::string>("stopPointInputTag", "g4SimHits")),
    mTimeMin (pset.getParameter<double>( "timeOffsetMin") * ns * c_light),
    mTimeMax (pset.getParameter<double>( "timeOffsetMax") * ns * c_light),
    //mRandom (new CLHEP::RandFlat(getEngine())),
    mVx(0.),
    mVy(0.),
    mVz(0.)
{
  //std::cout<<"starting StoppedParticleEvtVtxGenerator...."<<std::endl;
  if (mReadFromFile) {
    mFile = new std::ifstream (mFileName.c_str());
  }
}

StoppedParticleEvtVtxGenerator::~StoppedParticleEvtVtxGenerator() {}


void StoppedParticleEvtVtxGenerator::produce(edm::Event& evt, const edm::EventSetup& ) {

  //std::cout<<"starting produce of StoppedParticleEvtVtxGenerator"<<std::endl;
  //gen::Pythia6Service::InstanceWrapper guard(fPy6Service);   // grab Py6 instance                                                                                                                 
  edm::Service<RandomNumberGenerator> rng;
  if (!rng.isAvailable()) {
    throw cms::Exception("Configuration")
      << "Attempt to get a random engine when the RandomNumberGeneratorService is not configured.\n"
      "You must configure the service if you want an engine.\n";
  }
  CLHEP::HepRandomEngine* engine = &rng->getEngine(evt.streamID());

  getStoppingPoint(evt);

  if (isStoppedEvent) {
    Handle<HepMCProduct> HepMCEvt ;
    
    evt.getByLabel( mSourceLabel, HepMCEvt ) ;
    
    // generate new vertex & apply the shift 
    //
    //HepMCEvt->applyVtxGen( newVertex() ) ;
    //HepMCEvt->applyVtxGen( newVertex(fPy6Service->randomEngine()) ) ;
    HepMCEvt->applyVtxGen( newVertex(engine) ) ;
    
    //HepMCEvt->LorentzBoost( 0., 142.e-6 );
    HepMCEvt->boostToLab( GetInvLorentzBoost(), "vertex" );
    HepMCEvt->boostToLab( GetInvLorentzBoost(), "momentum" );

    //const HepMC::GenEvent* mc = HepMCEvt->GetEvent();    
    //mc->print( std::cout );

    // OK, create a (pseudo)product and put in into edm::Event
    //
    auto_ptr<bool> NewProduct(new bool(true)) ;      
    evt.put( NewProduct ) ;
  }
  //std::cout<<"ending produce of StoppedParticleEvtVtxGenerator"<<std::endl;
  return ;
  
}

void StoppedParticleEvtVtxGenerator::getStoppingPoint(edm::Event& iEvent) {
  isStoppedEvent = false;
  std::string name;
  mVx=0.;
  mVy=0.;
  mVz=0.;
  mVt=0.;

  // get stopping point info
  if (mReadFromFile) {   // read stopping info from file
    
    char buf [1024];
    mFile->getline (buf, 1023);
    if (!mFile->good() || buf[0]=='\n') { // end file: rewind
      delete mFile;
      mFile = new std::ifstream (mFileName.c_str());
      mFile->getline (buf, 1023);
      if (!mFile->good() || buf[0]=='\n') { // something wrong
	std::cout << "Failed to open stopping points file" << std::endl;
      }
    }
    char nn[32];
    sscanf (buf, "%s %f %f %f", nn, &mVx, &mVy, &mVz);
    name = std::string(nn);
    isStoppedEvent = true;
   }
  else {  // or from the event

    edm::Handle<std::vector<std::string> > names;
    iEvent.getByLabel (mStopPointProducer, "StoppedParticlesName", names);
    edm::Handle<std::vector<float> > xs;
    iEvent.getByLabel (mStopPointProducer, "StoppedParticlesX", xs);
    edm::Handle<std::vector<float> > ys;
    iEvent.getByLabel (mStopPointProducer, "StoppedParticlesY", ys);
    edm::Handle<std::vector<float> > zs;
    iEvent.getByLabel (mStopPointProducer, "StoppedParticlesZ", zs);
    
    if (names->size() != xs->size() || xs->size() != ys->size() || ys->size() != zs->size()) {
      std::cout << "mismatch array sizes name/x/y/z:"
				       << names->size() << '/' << xs->size() << '/' << ys->size() << '/' << zs->size()
				       << std::endl;
    }
     else {

       // TODO - what about when we have two stopped particles?!?
       // currently take the first one, not sure there is anything we can do about this.
       if (names->size() > 0) {
	 name = names->at(0);
	 mVx  = xs->at(0);
	 mVy  = ys->at(0);
	 mVz  = zs->at(0);
	 isStoppedEvent = true;
       }

     }

    std::cout << "Pythia6HSCPGun::generateEvent-> name/pid vertex: "
				     << name << '/' << ' '
				     << mVx << '/' << mVy << '/' << mVz 
				     << std::endl; 
    
  }

}



//HepMC::FourVector* StoppedParticleEvtVtxGenerator::newVertex() {
HepMC::FourVector* StoppedParticleEvtVtxGenerator::newVertex(CLHEP::HepRandomEngine* engine) {

  //mVt = CLHEP::RandFlat::shoot (mTimeMin, mTimeMax);
  mVt = CLHEP::RandFlat::shoot (engine,mTimeMin, mTimeMax);
  if (!fVertex) fVertex = new HepMC::FourVector(mVx, mVy, mVz, mVt);
  else fVertex->set (mVx, mVy, mVz, mVt);

  if (mVerbose) {
    std::cout << "Vertex : " << mVx << '/' << mVy << '/' << mVz << " cm, " << mVt / (ns * c_light) << " ns" << std::endl; 
  }

  return fVertex;
}

