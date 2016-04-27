#include "IOMC/EventVertexGenerators/interface/StoppedParticleEvtVtxGenerator.h"

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <ios>

#include "HepMC/SimpleVector.h"

#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/RandomNumberGenerator.h"
#include "FWCore/Utilities/interface/Exception.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "CLHEP/Random/RandFlat.h"
#include "CLHEP/Units/SystemOfUnits.h"
#include "CLHEP/Units/PhysicalConstants.h"

using namespace edm;
using namespace std;
using namespace CLHEP;

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
    putTwoStoppedInSameEvent(pset.getUntrackedParameter<bool>("PutTwoStoppedInSameEvent", false)),
    stoppedParticleNumber(pset.getUntrackedParameter<int>("StoppedParticleNumber", 0)),
    nStoppedParticles(0),
    mVx_(0.),
    mVy_(0.),
    mVz_(0.),
    mVt_(0.),
    ids_(0.),
    mVx(0.),
    mVy(0.),
    mVz(0.),
    mVt(0.),
    id(0.)
{
  LogDebug("StoppedParticleEvtVtxGenerator")<<"begining constructor of StoppedParticleEvtVtxGenerator"<<std::endl;

  produces<edm::HepMCProduct>();
  if (mReadFromFile) {
    mFile = new std::ifstream (mFileName.c_str());
  }
}

StoppedParticleEvtVtxGenerator::~StoppedParticleEvtVtxGenerator() {}


void StoppedParticleEvtVtxGenerator::produce(edm::Event& evt, const edm::EventSetup& ) {

  LogDebug("StoppedParticleEvtVtxGenerator")<<"starting produce of StoppedParticleEvtVtxGenerator"<<std::endl;
  //gen::Pythia6Service::InstanceWrapper guard(fPy6Service);   // grab Py6 instance                                                                                                                 
  edm::Service<RandomNumberGenerator> rng;
  if (!rng.isAvailable()) {
    throw cms::Exception("Configuration")
      << "Attempt to get a random engine when the RandomNumberGeneratorService is not configured.\n"
      "You must configure the service if you want an engine.\n";
  }
  CLHEP::HepRandomEngine* engine = &rng->getEngine(evt.streamID());
  
  LogDebug("StoppedParticleEvtVtxGenerator")<<"starting getStoppingPoint (StoppedParticleEvtVtxGenerator)"<<std::endl;
  getStoppingPoint(evt);

  Handle<HepMCProduct> HepMCEvt ;
  evt.getByLabel( mSourceLabel, HepMCEvt ) ;
  HepMC::GenEvent * myGenEvent = new  HepMC::GenEvent(*(HepMCEvt->GetEvent()));
  
  if (isStoppedEvent) {
    LogDebug("StoppedParticleEvtVtxGenerator")<<"is StoppedEvent (StoppedParticleEvtVtxGenerator)"<<std::endl;

    for(int i=0; i<nStoppedParticles; i++){
      //EITHER: 
      //if there is more than 1 stopped particle, put them in the same event, and loop over all the particles
      //OR
      //if there is more than 1 stopped particle, look only at the one that matches stoppedParticleNumber
      if(putTwoStoppedInSameEvent || (!putTwoStoppedInSameEvent && i==stoppedParticleNumber)) {     
	
	LogDebug("StoppedParticleEvtVtxGenerator")<<"stopped particle #"<<i<<" (StoppedParticleEvtVtxGenerator)"<<std::endl;
	mVx = mVx_.at(i);
	mVy = mVy_.at(i);
	mVz = mVz_.at(i);
	mVt = mVt_.at(i);
	id = ids_.at(i);
	LogDebug("StoppedParticleEvtVtxGenerator") << "Vertex : " << mVx << '/' << mVy << '/' << mVz << " cm" << '/' <<mVt<< " ns" << std::endl; 

	HepMC::FourVector* vtxShift = newVertex(engine);
	
	for ( HepMC::GenEvent::vertex_iterator vt=myGenEvent->vertices_begin(); vt!=myGenEvent->vertices_end(); ++vt ) {
	  LogDebug("StoppedParticleEvtVtxGenerator")<<"loop over vertices initial: "<<(*vt)->position().x()<<", "<<(*vt)->position().y()<<", "<<(*vt)->position().z()<<std::endl;
	  for ( HepMC::GenVertex::particle_iterator pt=(*vt)->particles_begin(HepMC::ancestors); pt!=(*vt)->particles_end(HepMC::ancestors); ++pt ) {
	    LogDebug("StoppedParticleEvtVtxGenerator")<<"loop over particles (ancestors): "<<(*pt)->pdg_id()<<std::endl;
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
		LogDebug("StoppedParticleEvtVtxGenerator")<<"appliedVtxGen for "<<id<<std::endl;
	      }//end of if ancestor and stopped particle vertices match
	    }//end of if ancestor and stopped particle pdgid match
	  }//end of loop over ancestors
	  LogDebug("StoppedParticleEvtVtxGenerator")<<"loop over vertices final: "<<(*vt)->position().x()<<", "<<(*vt)->position().y()<<", "<<(*vt)->position().z()<<std::endl;
	}//end of loop over vertices
      }//end of if put 2 stopped in same event or if decay only 1
    }//end of loop over stopped particles
      
    LogDebug("StoppedParticleEvtVtxGenerator")<<"isVtxGenApplied is: "<<HepMCEvt->isVtxGenApplied()<<", isVtxBoostApplied is: "<<HepMCEvt->isVtxBoostApplied()<<",  isPBoostApplied is: "<<HepMCEvt->isPBoostApplied()<<std::endl;    

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

    // OK, create a (pseudo)product and put in into edm::Event
    //no longer needed, since adding new HepMCProduct to the event
    //auto_ptr<bool> NewProduct(new bool(true)) ;      
    //evt.put( NewProduct ) ;      
    // LogDebug("StoppedParticleEvtVtxGenerator")<<"put new product in event (StoppedParticleEvtVtxGenerator)"<<std::endl;
    
    if(nStoppedParticles == 2){
      const HepMC::GenEvent* mc = HepMCEvt->GetEvent();    
      mc->print(  std::cout );
    }
    
  }//end of if stopped event
  
  //add (modified) HepMCProduct into event (module label: VtxSmeared)
  std::auto_ptr<HepMCProduct> HepProduct(new HepMCProduct());
  HepProduct->addHepMCData(myGenEvent);
  evt.put(HepProduct);
  
  LogDebug("StoppedParticleEvtVtxGenerator")<<"ending produce of StoppedParticleEvtVtxGenerator"<<std::endl;
  return ;
  
}

void StoppedParticleEvtVtxGenerator::getStoppingPoint(edm::Event& iEvent) {
  nStoppedParticles = 0;
  isStoppedEvent = false;
  const char *initilize[] = {"none","none","none","none","none"};
  std::vector<std::string> name_(initilize, std::end(initilize));
  mVx_={0.,0.,0.,0.,0.};
  mVy_={0.,0.,0.,0.,0.};
  mVz_={0.,0.,0.,0.,0.};
  mVt_={0.,0.,0.,0.,0.};
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
	edm::LogError("StoppedParticles") << "Failed to open stopping points file" << std::endl;
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
    edm::Handle<std::vector<float> > ts;
    iEvent.getByLabel (mStopPointProducer, "StoppedParticlesTime", ts);
    edm::Handle<std::vector<int> > ids;
    iEvent.getByLabel (mStopPointProducer, "StoppedParticlesPdgId", ids);

    if (names->size() != xs->size() || xs->size() != ys->size() || ys->size() != zs->size()) {
      edm::LogError ("StoppedParticles") << "mismatch array sizes name/x/y/z:"
				       << names->size() << '/' << xs->size() << '/' << ys->size() << '/' << zs->size()
				       << std::endl;
    }
     else {

       nStoppedParticles = names->size();
       if (nStoppedParticles > 0) {
	 if(putTwoStoppedInSameEvent){ //if there is more than 1 stopped particle, put them in the same event    
	   isStoppedEvent = true;
	   if(nStoppedParticles==1) mVt_.at(0) = 0.;
	   else if(nStoppedParticles==2) {
	     double deltaTime = TMath::Abs(ts->at(1)-ts->at(0));
	     if(ts->at(1) > ts->at(0)){
	       mVt_.at(0) = 0.;
	       mVt_.at(1) = deltaTime;
	     }
	     else{
	       mVt_.at(0) = deltaTime;
	       mVt_.at(1) = 0.;
	     }
	   }
	   else LogDebug("StoppedParticleEvtVtxGenerator")<<"3 or more stopped particles!!!!!!!!!!!!!!!"<<std::endl;
	 }//end of if put 2 stopped particles in same event
	 else{ //if put 2 stopped particles in separate events
	   for(int i=0; i<nStoppedParticles; i++){
	     if( i==stoppedParticleNumber) {
	       isStoppedEvent = true;
	       break;
	     }
	   }
	   mVt_.at(stoppedParticleNumber) = 0.;
	 }
	  
	 for(int i=0; i<nStoppedParticles; i++){
	   //EITHER:
	   //if there is more than 1 stopped particle, put them in the same event, and loop over all the particles
	   //OR
	   //if there is more than 1 stopped particle, look only at the one that matches stoppedParticleNumber
	   if(putTwoStoppedInSameEvent || (!putTwoStoppedInSameEvent && i==stoppedParticleNumber)) {     
	     name_.at(i) = names->at(i);
	     mVx_.at(i)  = xs->at(i);
	     mVy_.at(i)  = ys->at(i);
	     mVz_.at(i)  = zs->at(i);
	     ids_.at(i)  = ids->at(i);
	     LogDebug("StoppedParticleEvtVtxGenerator") << "StoppedParticleEvtVtxGenerator::generateEvent-> name/pid vertex: "
		       << name_.at(i) << '/' << ' '
		       << mVx_.at(i) << '/' << mVy_.at(i) << '/' << mVz_.at(i) <<mVt_.at(i)
		       << std::endl;    
	   }//end of if put 2 stopped in same event or if decay only 1
	 }//end of loop over stopped particles
	 
       }//end of if nStoppedParticles>0
     }//end of if StoppedParticles arrays match
    
    //edm::LogInfo("StoppedParticles") << "Pythia6HSCPGun::generateEvent-> name/pid vertex: "
    //<< name << '/' << ' '
    //				     << mVx << '/' << mVy << '/' << mVz 
    //				     << std::endl; 
    
  }

}



HepMC::FourVector* StoppedParticleEvtVtxGenerator::newVertex(CLHEP::HepRandomEngine* engine) {

  //mVt = CLHEP::RandFlat::shoot (mTimeMin, mTimeMax);
  mVt =(mVt* ns * c_light) + CLHEP::RandFlat::shoot (engine,mTimeMin, mTimeMax);
  if (!fVertex) fVertex = new HepMC::FourVector(mVx, mVy, mVz, mVt);
  else fVertex->set (mVx, mVy, mVz, mVt);

  if (mVerbose) {
    edm::LogInfo("StoppedParticles") << "Vertex : " << mVx << '/' << mVy << '/' << mVz << " cm, " << mVt / (ns * c_light) << " ns" << std::endl; 
  }

  return fVertex;
}

