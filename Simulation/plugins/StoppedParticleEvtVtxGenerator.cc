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

#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"

StoppedParticleEvtVtxGenerator::StoppedParticleEvtVtxGenerator(const edm::ParameterSet & pset) 
  : BaseEvtVtxGenerator(pset),
    mSourceLabel(pset.getParameter<edm::InputTag>("src")),
    mReadFromFile(pset.getUntrackedParameter<bool>("readFromFile", true)),
    mFileName (pset.getParameter<std::string>("stoppedData")),
    mStopPointProducer(pset.getUntrackedParameter<std::string>("stopPointInputTag", "g4SimHits")),
    mTimeMin (pset.getParameter<double>( "timeOffsetMin") * ns * c_light),
    mTimeMax (pset.getParameter<double>( "timeOffsetMax") * ns * c_light),
    //mRandom (new CLHEP::RandFlat(getEngine())),
    mVx_(0.),
    mVy_(0.),
    mVz_(0.),
    ids_(0.),
    mVx(0.),
    mVy(0.),
    mVz(0.),
    mVt(0.),
    id(0.),
    nStoppedParticles(0)
{
  // LogDebug("StoppedHSCPMuon")<<"starting StoppedParticleEvtVtxGenerator...."<<std::endl;
  produces<edm::HepMCProduct>();
  if (mReadFromFile) {
    mFile = new std::ifstream (mFileName.c_str());
  }
}

StoppedParticleEvtVtxGenerator::~StoppedParticleEvtVtxGenerator() {}


void StoppedParticleEvtVtxGenerator::produce(edm::Event& evt, const edm::EventSetup& ) {

   LogDebug("StoppedHSCPMuon")<<"starting produce of StoppedParticleEvtVtxGenerator"<<std::endl;
  //gen::Pythia6Service::InstanceWrapper guard(fPy6Service);   // grab Py6 instance                                                                                                                 
  edm::Service<RandomNumberGenerator> rng;
  if (!rng.isAvailable()) {
    throw cms::Exception("Configuration")
      << "Attempt to get a random engine when the RandomNumberGeneratorService is not configured.\n"
      "You must configure the service if you want an engine.\n";
  }
  CLHEP::HepRandomEngine* engine = &rng->getEngine(evt.streamID());
  
   LogDebug("StoppedHSCPMuon")<<"starting getStoppingPoint (StoppedParticleEvtVtxGenerator)"<<std::endl;
  getStoppingPoint(evt);

  Handle<HepMCProduct> HepMCEvt ;
  evt.getByLabel( mSourceLabel, HepMCEvt ) ;
  HepMC::GenEvent * myGenEvent = new  HepMC::GenEvent(*(HepMCEvt->GetEvent()));
  
  if (isStoppedEvent) {
     LogDebug("StoppedHSCPMuon")<<"is StoppedEvent (StoppedParticleEvtVtxGenerator)"<<std::endl;

    //could simply use applyVtxGen function if there was only 1 stopped particle. if we want to include the possibility of 
    //2 stopped particles, then need to apply separate vertex shifts, as below
    //HepMCEvt->applyVtxGen( newVertex() ) ;
    //HepMCEvt->applyVtxGen( newVertex(fPy6Service->randomEngine()) ) ;
    //////HepMCEvt->applyVtxGen( newVertex(engine) ) ;

    //since no longer using applyVtxGen, adding a null vertex shift so that HepMCEvt->isVtxGenApplied() returns true
    HepMC::FourVector* nullVertex = new HepMC::FourVector(0,0,0,0);
    HepMCEvt->applyVtxGen( nullVertex );

    //HepMCEvt->LorentzBoost( 0., 142.e-6 );
    HepMCEvt->boostToLab( GetInvLorentzBoost(), "vertex" );
    HepMCEvt->boostToLab( GetInvLorentzBoost(), "momentum" );

    for(int i=0; i<nStoppedParticles; i++){
       LogDebug("StoppedHSCPMuon")<<"stopped particle #"<<i<<" (StoppedParticleEvtVtxGenerator)"<<std::endl;
      mVx = mVx_.at(i);
      mVy = mVy_.at(i);
      mVz = mVz_.at(i);
      id = ids_.at(i);
       LogDebug("StoppedHSCPMuon") << "Vertex : " << mVx << '/' << mVy << '/' << mVz << " cm" << std::endl; 
      HepMC::FourVector* vtxShift = newVertex(engine);
            
      for ( HepMC::GenEvent::vertex_iterator vt=myGenEvent->vertices_begin(); vt!=myGenEvent->vertices_end(); ++vt ) {
	 LogDebug("StoppedHSCPMuon")<<"loop over vertices initial: "<<(*vt)->position().x()<<", "<<(*vt)->position().y()<<", "<<(*vt)->position().z()<<std::endl;
	for ( HepMC::GenVertex::particle_iterator pt=(*vt)->particles_begin(HepMC::ancestors); pt!=(*vt)->particles_end(HepMC::ancestors); ++pt ) {
	   LogDebug("StoppedHSCPMuon")<<"loop over particles (ancestors): "<<(*pt)->pdg_id()<<std::endl;
	  //if ancestor of particles in vertex has the same pdg_id as the stopped particle (sign correct too),
	  //and if ancestor and stopped particle has the same vertex position,
	  //then shift the vertex
	  if( (*pt)->pdg_id()==id ){
	    if( (*pt)->production_vertex()->position().x()==mVx && (*pt)->production_vertex()->position().y()==mVy && (*pt)->production_vertex()->position().z()==mVz ){
	      //shift the vertex (see HepMCProduct::applyVtxGen())
	      double x = (*vt)->position().x() + vtxShift->x();
	      double y = (*vt)->position().y() + vtxShift->y();
	      double z = (*vt)->position().z() + vtxShift->z();
	      double t = (*vt)->position().t() + vtxShift->t();
	      (*vt)->set_position(HepMC::FourVector(x,y,z,t));
	       LogDebug("StoppedHSCPMuon")<<"appliedVtxGen for "<<id<<std::endl;
	    }//end of if ancestor and stopped particle vertices match
	  }//end of if ancestor and stopped particle pdgid match
	}//end of loop over ancestors
	 LogDebug("StoppedHSCPMuon")<<"loop over vertices final: "<<(*vt)->position().x()<<", "<<(*vt)->position().y()<<", "<<(*vt)->position().z()<<std::endl;
      }//end of loop over vertices
    }//end of loop over stopped particles

     LogDebug("StoppedHSCPMuon")<<"isVtxGenApplied is: "<<HepMCEvt->isVtxGenApplied()<<", isVtxBoostApplied is: "<<HepMCEvt->isVtxBoostApplied()<<",  isPBoostApplied is: "<<HepMCEvt->isPBoostApplied()<<std::endl;    
      
    // OK, create a (pseudo)product and put in into edm::Event
    //no longer needed, since adding new HepMCProduct to the event
    //auto_ptr<bool> NewProduct(new bool(true)) ;      
    //evt.put( NewProduct ) ;      
    // LogDebug("StoppedHSCPMuon")<<"put new product in event (StoppedParticleEvtVtxGenerator)"<<std::endl;
    
    if(nStoppedParticles == 2){
      const HepMC::GenEvent* mc = HepMCEvt->GetEvent();    
      mc->print(  std::cout );
    }
    
  }//end of if stopped event

  //add (modified) HepMCProduct into event (module label: VtxSmeared)
  std::auto_ptr<HepMCProduct> HepProduct(new HepMCProduct());
  HepProduct->addHepMCData(myGenEvent);
  evt.put(HepProduct);

   LogDebug("StoppedHSCPMuon")<<"ending produce of StoppedParticleEvtVtxGenerator"<<std::endl;
  return ;
  
}

void StoppedParticleEvtVtxGenerator::getStoppingPoint(edm::Event& iEvent) {

  nStoppedParticles = 0;
  const char *initilize[] = {"none","none","none","none","none"};
  std::vector<std::string> name_(initilize, std::end(initilize));
  isStoppedEvent = false;
  mVx_={0.,0.,0.,0.,0.};
  mVy_={0.,0.,0.,0.,0.};
  mVz_={0.,0.,0.,0.,0.};
  ids_={0,0,0,0,0};

  // get stopping point info
  if (mReadFromFile) {   // read stopping info from file
    
    char buf [1024];
    mFile->getline (buf, 1023);
    if (!mFile->good() || buf[0]=='\n') { // end file: rewind
      delete mFile;
      mFile = new std::ifstream (mFileName.c_str());
      mFile->getline (buf, 1023);
      if (!mFile->good() || buf[0]=='\n') { // something wrong
	 LogDebug("StoppedHSCPMuon") << "Failed to open stopping points file" << std::endl;
      }
    }
    char nn[32];
    sscanf (buf, "%s %f %f %f", nn, &mVx_.at(0), &mVy_.at(0), &mVz_.at(0));
    name_.at(0) = std::string(nn);
    isStoppedEvent = true;
    nStoppedParticles = 1;
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
    edm::Handle<std::vector<int> > ids;
    iEvent.getByLabel (mStopPointProducer, "StoppedParticlesPdgId", ids);
    
    if (names->size() != xs->size() || xs->size() != ys->size() || ys->size() != zs->size()) {
       LogDebug("StoppedHSCPMuon") << "mismatch array sizes name/x/y/z:"
				       << names->size() << '/' << xs->size() << '/' << ys->size() << '/' << zs->size()
				       << std::endl;
    }
     else {

       // get stopping info from any number of stopped particles (not just 0 or 1, as before)
       if (names->size() > 0) {
	 isStoppedEvent = true;
	 nStoppedParticles = names->size();
	  LogDebug("StoppedHSCPMuon")<<"names->size() is: "<<nStoppedParticles<<" (getStoppingPoint, StoppedParticleEvtVtxGenerator)"<<std::endl;
	 for(int i=0; i<nStoppedParticles; i++){
	   name_.at(i) = names->at(i);
	   mVx_.at(i)  = xs->at(i);
	   mVy_.at(i)  = ys->at(i);
	   mVz_.at(i)  = zs->at(i);
	   ids_.at(i)  = ids->at(i);
	    LogDebug("StoppedHSCPMuon") << "StoppedParticleEvtVtxGenerator::generateEvent-> name/pid vertex: "
		     << name_.at(i) << '/' << ' '
		     << mVx_.at(i) << '/' << mVy_.at(i) << '/' << mVz_.at(i) 
		     << std::endl; 	   
	 }
       }

     }

    
  }

}


//HepMC::FourVector* StoppedParticleEvtVtxGenerator::newVertex() {
HepMC::FourVector* StoppedParticleEvtVtxGenerator::newVertex(CLHEP::HepRandomEngine* engine) {

   LogDebug("StoppedHSCPMuon")<<"starting newVertex"<<std::endl;

  //mVt = CLHEP::RandFlat::shoot (mTimeMin, mTimeMax);
  mVt = CLHEP::RandFlat::shoot (engine,mTimeMin, mTimeMax);
  if (!fVertex) fVertex = new HepMC::FourVector(mVx, mVy, mVz, mVt);
  else fVertex->set (mVx, mVy, mVz, mVt);
  
  LogDebug("StoppedHSCPMuon") << "Vertex : " << mVx << '/' << mVy << '/' << mVz << " cm, " << mVt / (ns * c_light) << " ns" << std::endl; 

  return fVertex;
}
