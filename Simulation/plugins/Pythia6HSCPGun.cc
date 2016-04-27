#include <iostream>
#include <fstream>
#include <stdio.h>

#include "Pythia6HSCPGun.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/Exception.h"

#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ServiceRegistry/interface/RandomEngineSentry.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"

#include "FWCore/Framework/interface/MakerMacros.h"

using namespace edm;
using namespace gen;

namespace {
  const int specialNumber = 33;
  const int specialPid [specialNumber] = {
    1000993,1009213,1009313,1009323,1009113,
    1009223,1009333,1091114,1092114,1092214,
    1092224,1093114,1093214,1093224,1093314,
    1093324,1093334,
    1000612,1000622,1000632,1000642,1000652,
    1006113,1006211,1006213,1006223,1006311,
    1006313,1006321,1006323,1006333,
    1000015,
    17
  };
  const std::string specialName [specialNumber] = {
      "~g_glueball","~g_rho+","~g_K*0","~g_K*+","~g_rho0",
      "~g_omega","~g_phi","~g_Delta-","~g_Delta0","~g_Delta+",
      "~g_Delta++","~g_Sigma*-","~g_Sigma*0","~g_Sigma*+","~g_Xi*-",
      "~g_Xi*0 ","~g_Omega-",
      "~T+","~T0","~T_s+","~T_c0","~T_b+",
      "~T_dd10","~T_ud0+","~T_ud1+","~T_uu1++","~T_sd00",
      "~T_sd10","~T_su0+","~T_su1+","~T_ss10",
      "~tau1",
      "~HIP6"
  };
  const std::string specialAntiName [specialNumber] = {
    "~g_glueball","~g_rho-","~g_K*bar0","~g_K*-","~g_rho0",
    "~g_omega","~g_phi","~g_Deltabar+","~g_Deltabar0","~g_Deltabar-",
    "~g_Deltabar--","~g_Sigma*bar+","~g_Sigma*bar0","~g_Sigma*bar-","~g_Xi*bar+",
    "~g_Xi*bar0","~g_Omegabar+",
    "~Tbar-","~Tbar0","~Tbar_s-","~Tbar_c0","~Tbar_b-",
    "~Tbar_dd10","~Tbar_ud0-","~Tbar_ud1-","~Tbar_uu1--","~Tbar_sd00",
    "~Tbar_sd10","~Tbar_su0-","~Tbar_su1-","~Tbar_ss10",
    "anti_~tau1",
    "anti_~HIP6"
  };
  int getSpecialId (const std::string& fName) {
    for (int i = 0; i < specialNumber; ++i) {
      if (fName == specialName[i]) return specialPid[i];
      if (fName == specialAntiName[i]) return -specialPid[i];
    }
    return 0;
  }

  void writeCommon (std::ofstream& file) {
    char buffer[1024];

    sprintf (buffer, "DECAY 1000022 0.\n"); 
    file << buffer; //neutralino

    sprintf (buffer, "DECAY 1000039 0.\n");
    file << buffer; //gravitino

    sprintf (buffer, "DECAY 17 1.e-12 \n"); 
    file << buffer; // doubly charged Higgs
    sprintf (buffer, "     1.00000000E+00   2   13        13 \n"); 
    file << buffer;

    sprintf (buffer, "DECAY 1000021 1.e-12 \n"); 
    file << buffer; // gluino
    sprintf (buffer, "     1.00000000E+00   2   1000022   21 \n"); 
    file << buffer;

    sprintf (buffer, "DECAY 1000006 1.e-12 \n"); 
    file << buffer; // stop
    sprintf (buffer, "     1.00000000E+00   2   1000022    6 \n"); 
    file << buffer;

    sprintf (buffer, "DECAY 24 1.e-12 \n");
    file << buffer; //W
    sprintf (buffer, "     1.00000000E+00   2   -13 14 \n");
    file << buffer;

    sprintf (buffer, "DECAY 23 1.e-12 \n");
    file << buffer; //Z
    sprintf (buffer, "     1.00000000E+00   2   13 -13 \n");
    file << buffer;

    sprintf (buffer, "DECAY 1000015 1.e-12 \n"); 
    file << buffer; // stau
    //sprintf (buffer, "     1.00000000E+00   2   1000022   15 \n"); 
    //sprintf (buffer, "     1.00000000E+00   4   1000022   -14   13   16 \n"); 
    sprintf (buffer, "     1.00000000E+00   2   1000039  15 \n"); 
    file << buffer;

    sprintf (buffer, "DECAY 15 1.e-12 \n");
    file << buffer; //tau
    sprintf (buffer, "     1.00000000E+00   3   13   -14   16 \n");
    file << buffer;

  }

  void writeRHadron (std::ofstream& file) {
    char buffer[1024];
    for (int id = 0; id < 17; ++id) {
      const char* name = specialName[id].c_str();
      int pid = specialPid[id];
      //LogDebug("GeneratorInterface")<<"writeRHadron pid is: "<<pid<<std::endl;
      if ((pid % 100000) > 90000) { // R-Baryon
	//LogDebug("GeneratorInterface")<<"writeRHadron R-baryon is: "<<pid<<std::endl;
	int quark [3];
	int charge = 0;
	int qid = (pid % 10000) / 10;
	for (int i = 0; i < 3; ++i) {
	  quark[i] = qid % 10;
	  if (quark[i] == 2) charge+=2;
	  else --charge;
	  qid = qid / 10;
	}
	sprintf (buffer, "DECAY     %7d     1.00000000E-05\n", pid); file << buffer;
	sprintf (buffer, "     1.0000000E+00   3   %1d%1d03   %1d   1000021\n",
		 quark[2],quark[1],quark[0]); // decay to quark+diquark+gluino
	file << buffer;
	
	sprintf (buffer, "BLOCK QNUMBERS %7d # %s \n", pid, name); file << buffer;
	sprintf (buffer, "         1 %d \n", charge); file << buffer;
	sprintf (buffer, "         2 2 \n"); file << buffer;
	sprintf (buffer, "         3 1 \n"); file << buffer;
	sprintf (buffer, "         4 1 \n"); file << buffer;
      }
      else if ((pid % 10000) > 9000) { // R-Meson
	//LogDebug("GeneratorInterface")<<"writeRHadron R-meson is: "<<pid<<std::endl;
	int quark [2];
	int qid = (pid % 1000) / 10;
	for (int i = 0; i < 2; ++i) {
	  quark[i] = qid % 10;
	  qid = qid / 10;
	}
	int charge = 0;
	if (quark[0] == 2) charge-=2;
	else charge+=1;
	if (quark[1] == 2) charge+=2;
	else charge-=1;
	
	sprintf (buffer, "DECAY     %7d     1.00000000E-05\n", pid); file << buffer;
	sprintf (buffer, "     1.00000000E+00   3   -%1d   %1d   1000021\n",
		 quark[0], quark[1]); // decay to quark+antiquark+gluino
	file << buffer;
	
	sprintf (buffer, "BLOCK QNUMBERS %7d # %s \n", pid, name); file << buffer;
	sprintf (buffer, "         1 %d \n", charge); file << buffer;
	sprintf (buffer, "         2 2 \n"); file << buffer;
	sprintf (buffer, "         3 1 \n"); file << buffer;
	sprintf (buffer, "         4 1 \n"); file << buffer;
      }
      else { // glueball
	//LogDebug("GeneratorInterface")<<"writeRHadron glueball is: "<<pid<<std::endl;
	sprintf (buffer, "DECAY     %7d     1.00000000E-05\n", pid); file << buffer;
	sprintf (buffer, "     1.00000000E+00   2   21   1000021\n");
	file << buffer;
	sprintf (buffer, "BLOCK QNUMBERS %7d # %s\n", pid, name); file << buffer;
	sprintf (buffer, "         1 0 \n"); file << buffer;
	sprintf (buffer, "         2 2 \n"); file << buffer;
	sprintf (buffer, "         3 1 \n"); file << buffer;
	sprintf (buffer, "         4 1 \n"); file << buffer;
      }
    }
  }

  void writeStopHadron (std::ofstream& file) {
    char buffer[1024];
    for (int id = 17; id < 31; ++id) {
      const char* name = specialName[id].c_str();
      int pid = specialPid[id];
      if ((pid % 10000) > 6000) { // T-Baryon
	int quark [3];
	int charge = 0;
	int qid = (pid % 10000) / 10;
	for (int i = 0; i < 3; ++i) {
	  quark[i] = qid % 10;
	  if (quark[i] % 2) charge-=1; // d,s,b
	  else charge+=2; // u,c,t
	  qid = qid / 10;
	}
	if (quark[2] != 6) {
	  LogDebug("GeneratorInterface") << "writeStopHadron-> STOP R-hadron is expected, " << pid << " is found" << std::endl;
	  return;
	}
	sprintf (buffer, "DECAY     %7d     1.00000000E-05\n", pid); file << buffer;
	sprintf (buffer, "     1.0000000E+00   2   %1d%1d03   1000006\n",
		 quark[1],quark[0]); // decay to stop+diquark
	file << buffer;
	
	sprintf (buffer, "BLOCK QNUMBERS %7d # %s \n", pid, name); file << buffer;
	sprintf (buffer, "         1 %d \n", charge); file << buffer;
	sprintf (buffer, "         2 2 \n"); file << buffer;
	sprintf (buffer, "         3 1 \n"); file << buffer;
	sprintf (buffer, "         4 1 \n"); file << buffer;
      }
      else if ((pid % 10000) > 600) { // STOP-Meson
	int quark [2];
	int qid = (pid % 1000) / 10;
	for (int i = 0; i < 2; ++i) {
	  quark[i] = qid % 10;
	  qid = qid / 10;
	}
	if (quark[1] != 6) {
	  LogDebug("GeneratorInterface") << "writeStopHadron-> STOP R-hadron is expected, " << pid << " is found" << std::endl;
	  return;
	}
	int charge = 0;
	if (quark[0] % 2) charge+=1; // anti d,s,b
	else charge-=2; // anti u,c,t
	if (quark[1] % 2) charge-=1; // d,s,b
	else charge+=2; // u,c,t
	
	sprintf (buffer, "DECAY     %7d     1.00000000E-05\n", pid); file << buffer;
	sprintf (buffer, "     1.00000000E+00   2   -%1d   1000006\n",
		 quark[0]); // decay to quark+antiquark+gluino
	file << buffer;
	
	sprintf (buffer, "BLOCK QNUMBERS %7d # %s \n", pid, name); file << buffer;
	sprintf (buffer, "         1 %d \n", charge); file << buffer;
	sprintf (buffer, "         2 2 \n"); file << buffer;
	sprintf (buffer, "         3 1 \n"); file << buffer;
	sprintf (buffer, "         4 1 \n"); file << buffer;
      }
      else {
	LogDebug("GeneratorInterface") << "writeStopHadron-> Unknown STop R-hadron: " << pid << std::endl;
      }
    }
  }

  void writeStau (std::ofstream& file) {
  }

  void setAllMasses (std::ofstream& file, double sparticleMass, double neutralinoMass, double gravitinoMass) {
  //void setAllMasses (std::ofstream& file, double sparticleMass, double neutralinoMass) {
    char buffer[1024];
    sprintf (buffer, "BLOCK_MASS\n"); file << buffer;
    sprintf (buffer, "   1000022   %6.1f\n", neutralinoMass); file << buffer;
    sprintf (buffer, "   1000039   %6.1f\n", gravitinoMass); file << buffer;
    sprintf (buffer, "   17        %6.1f\n", sparticleMass); file << buffer;
    sprintf (buffer, "   1000021   %6.1f\n", sparticleMass); file << buffer;
    sprintf (buffer, "   1000006   %6.1f\n", sparticleMass); file << buffer;
    sprintf (buffer, "   1000015   %6.1f\n", sparticleMass); file << buffer;
    double hadronMass = sparticleMass + 2.;
    for (int i = 0; i < specialNumber; ++i) {
      int pid = specialPid[i];
      sprintf (buffer, "   %7d   %6.1f\n", pid, hadronMass); file << buffer;
    }
  }

  void makeParticleTable (const std::string& fName, double fSparticleMass, double fNeutralinoMass, double fGravitinoMass) {
    //void makeParticleTable (const std::string& fName, double fSparticleMass, double fNeutralinoMass) {
    std::ofstream file (fName.c_str());
    writeCommon (file);
    writeRHadron (file);
    //writeStopHadron (file);
    writeStau (file);
    setAllMasses (file, fSparticleMass, fNeutralinoMass, fGravitinoMass);
    //setAllMasses (file, fSparticleMass, fNeutralinoMass);
    LogDebug("GeneratorInterface") << "***** " << fName.c_str() << std::endl;
  }

}// unnamed namespace

Pythia6HSCPGun::Pythia6HSCPGun( const ParameterSet& pset ) :
  Pythia6ParticleGun(pset),
  mReadFromFile(pset.getUntrackedParameter<bool>("readFromFile", true)),
  mStopPointProducer(pset.getUntrackedParameter<std::string>("stopPointInputTag", "g4SimHits")),
  mFileName(pset.getParameter<std::string>("stoppedData")),
  putTwoStoppedInSameEvent(pset.getUntrackedParameter<bool>("PutTwoStoppedInSameEvent", false)),
  stoppedParticleNumber(pset.getUntrackedParameter<int>("StoppedParticleNumber", 0)),
  nStoppedParticles(0),
  //mPID_(0),
  //mVx_(0.),
  //mVy_(0.),
  //mVz_(0.),
  mPID(0),
  mVx(0.),
  mVy(0.),
  mVz(0.),
  mVt(0.)
{
  LogDebug("GeneratorInterface")<<"begining constructor of Pythia6HSCPGun"<<std::endl;

  if (mReadFromFile) {
    mFile = new std::ifstream (mFileName.c_str());
  }
  
  ParameterSet pgun_params = pset.getParameter<ParameterSet>("PGunParameters");
  std::string decayTable = (pgun_params.getParameter<std::string>( "decayTable"));
  double sparticleMass = (pgun_params.getParameter<double>( "sparticleMass"));
  double neutralinoMass = (pgun_params.getParameter<double>( "neutralinoMass"));
  double gravitinoMass = (pgun_params.getParameter<double>( "gravitinoMass"));
  //bool diJetGluino = (pgun_params.getParameter<bool>( "diJetGluino"));  
  makeParticleTable (decayTable,sparticleMass, neutralinoMass, gravitinoMass);
  //makeParticleTable (decayTable,sparticleMass, neutralinoMass);
 
}

Pythia6HSCPGun::~Pythia6HSCPGun()
{
}


// copied from Pythia6Gun::produce
void Pythia6HSCPGun::produce(edm::Event& evt, const edm::EventSetup& iSetup) {
  LogDebug("GeneratorInterface")<<"starting produce of Pythia6HSCPGun"<<std::endl;
  RandomEngineSentry<Pythia6Service> sentry(fPy6Service, evt.streamID());

  nStoppedParticles = 0;
  bool isStoppedEvent = false;
  const char *initilize[] = {"none","none","none","none","none"};
  std::vector<std::string> name(initilize, std::end(initilize));
  mPID={0,0,0,0,0};
  mVx={0.,0.,0.,0.,0.};
  mVy={0.,0.,0.,0.,0.};
  mVz={0.,0.,0.,0.,0.};
  mVt={0.,0.,0.,0.,0.};

  //mPID=0;
  //mVx=0.;
  //mVy=0.;
  //mVz=0.;
  // get stopping point info
  if (mReadFromFile) {   // read stopping info from file
    
    char buf [1024];
    mFile->getline (buf, 1023);
    if (!mFile->good() || buf[0]=='\n') { // end file: rewind
      delete mFile;
      mFile = new std::ifstream (mFileName.c_str());
      mFile->getline (buf, 1023);
      if (!mFile->good() || buf[0]=='\n') { // something wrong
	edm::LogError("FileError") << "Pythia6HSCPGun::generateEvent-> ERROR: failed to get data from file" << std::endl;
      }
    }
    char nn[32];
    sscanf (buf, "%s %f %f %f", nn, &mVx.at(0), &mVy.at(0), &mVz.at(0));
    name.at(0) = std::string(nn);
    mPID.at(0) = getSpecialId(name.at(0));
    isStoppedEvent = true;
    nStoppedParticles = 1;
  }
  else {  // or from the event

    edm::Handle<std::vector<std::string> > names;
    evt.getByLabel (mStopPointProducer, "StoppedParticlesName", names);
    edm::Handle<std::vector<float> > xs;
    evt.getByLabel (mStopPointProducer, "StoppedParticlesX", xs);
    edm::Handle<std::vector<float> > ys;
    evt.getByLabel (mStopPointProducer, "StoppedParticlesY", ys);
    edm::Handle<std::vector<float> > zs;
    evt.getByLabel (mStopPointProducer, "StoppedParticlesZ", zs);
    edm::Handle<std::vector<float> > ts;
    evt.getByLabel (mStopPointProducer, "StoppedParticlesTime", ts);
    
    if (names->size() != xs->size() || xs->size() != ys->size() || ys->size() != zs->size()) {
      edm::LogError ("Pythia6HSCPGun") << "mismatch array sizes name/x/y/z:"
				       << names->size() << '/' << xs->size() << '/' << ys->size() << '/' << zs->size()
				       << std::endl;
    }
    else {
      // get stopping info from any number of stopped particles (not just 0 or 1, as before)
      LogDebug("GeneratorInterface")<<"names->size is: "<<names->size()<<std::endl;
      nStoppedParticles = names->size();
      if (nStoppedParticles > 0) {

	if(putTwoStoppedInSameEvent){ //if there is more than 1 stopped particle, put them in the same event
	  isStoppedEvent = true;
	  if(nStoppedParticles==1) mVt.at(0) = 0.;
	  else if(nStoppedParticles==2) {
	    double deltaTime = TMath::Abs(ts->at(1)-ts->at(0));
	    if(ts->at(1) > ts->at(0)){
	      mVt.at(0) = 0.;
	      mVt.at(1) = deltaTime;
	    }
	    else{
	      mVt.at(0) = deltaTime;
	      mVt.at(1) = 0.;
	    }
	  }
	  else LogDebug("GeneratorInterface")<<"3 or more stopped particles!!!!!!!!!!!!!!!"<<std::endl;
	}//end of if put 2 stopped particles in same event
	else{ //if put 2 stopped particles in separate events
	  for(int i=0; i<nStoppedParticles; i++){
	    if( i==stoppedParticleNumber) {
	      isStoppedEvent = true;
	      break;
	    }
	  }
	  mVt.at(stoppedParticleNumber) = 0.;
	}

	for(int i=0; i<nStoppedParticles; i++){
	  //EITHER:
	  //if there is more than 1 stopped particle, put them in the same event, and loop over all the particles
	  //OR
	  //if there is more than 1 stopped particle, look only at the one that matches stoppedParticleNumber
	  if(putTwoStoppedInSameEvent || (!putTwoStoppedInSameEvent && i==stoppedParticleNumber)) {
	    name.at(i) = names->at(i);
	    mPID.at(i) = getSpecialId(names->at(i));
	    mVx.at(i)  = xs->at(i);
	    mVy.at(i)  = ys->at(i);
	    mVz.at(i)  = zs->at(i);
	    LogDebug("GeneratorInterface")<<"isStoppedEvent with name "<<name.at(i)<<", mPID "<<mPID.at(i)<<", mVx "<<mVx.at(i)<<", mVy "<<mVy.at(i)<<", mVz "<<mVz.at(i)<<", stopping time "<<ts->at(i)<<std::endl;
	  }//end of if put 2 stopped in same event or if decay only 1
	}//end of loop over stopped particles
	
      }//end of if nStoppedParticles>0
    }//end of if StoppedParticles arrays match
    
    //edm::LogInfo("Pythia6HSCPGun") << "Pythia6HSCPGun::generateEvent-> name/pid vertex: "
    //				   << name << '/' << mPID << '/' << ' '
    //				   << mVx << '/' << mVy << '/' << mVz 
    //				   << std::endl; 
    
  }//end of get stopping info from event (and not file)

  LogDebug("GeneratorInterface")<<"got stopping point info"<<std::endl;
  if (isStoppedEvent) {
    generateEvent(fPy6Service->randomEngine()) ;

    int evtN = evt.id().event();
    fEvt->set_beam_particles(0,0);
    fEvt->set_event_number(evtN) ;
    fEvt->set_signal_process_id(pypars.msti[0]) ;  
    
    attachPy6DecaysToGenEvent();
    
    if ( evtN <= fMaxEventsToPrint ) {
	if ( fPylistVerbosity ) {
	    call_pylist(fPylistVerbosity);
	}
	if ( fHepMCVerbosity ) {
	  if ( fEvt ) fEvt->print();
	}
    }
    loadEvent( evt );
    LogDebug("GeneratorInterface")<<"loaded event"<<std::endl;
  }//end of if stopped event
  LogDebug("GeneratorInterface")<<"end of produce method"<<std::endl;
}//end of produce()

void Pythia6HSCPGun::generateEvent(CLHEP::HepRandomEngine*)
//void Pythia6HSCPGun::generateEvent()
{
  //LogDebug("GeneratorInterface")<<"starting generateEvent of Pythia6HSCPGun"<<std::endl;

  // here re-create fEvt (memory)
  fEvt = new HepMC::GenEvent() ;

  Pythia6Service::InstanceWrapper guard(fPy6Service);	// grab Py6 instance
  //LogDebug("GeneratorInterface")<<"grabbed Py6 instance"<<std::endl;
  
  LogDebug("GeneratorInterface")<<"made fEvt"<<std::endl;
  LogDebug("GeneratorInterface")<<"nStoppedParticles is: "<<nStoppedParticles<<std::endl;

  for(int i=0; i<nStoppedParticles; i++){
    //EITHER:
    //if there is more than 1 stopped particle, put them in the same event, and loop over all the particles
    //OR
    //if there is more than 1 stopped particle, look only at the one that matches stoppedParticleNumber
    if(putTwoStoppedInSameEvent || (!putTwoStoppedInSameEvent && i==stoppedParticleNumber)) {
      // check the case where no stopped particle found
      // need to check this doesn't break stuff
      if (mPID.at(i)==0) {
	LogDebug("GeneratorInterface")<<"mPID is 0"<<std::endl;
	return;
      }
      
      HepMC::GenVertex* Vtx = new HepMC::GenVertex( HepMC::FourVector(mVx.at(i), mVy.at(i), mVz.at(i)), mVt.at(i) );
      
      int ip=1+i;
      
      int particleID = mPID.at(i);
      int py6PID = HepPID::translatePDTtoPythia( particleID );
      double mass = pymass_(particleID);
      
      // fill p(ip,5) (in PYJETS) with mass value right now,
      // because the (hardcoded) mstu(10)=1 will make py1ent
      // pick the mass from there
      pyjets.p[4][i]=mass; 	 
      
      double phi = 0.;
      double ee   = mass;
      double eta  = 0;
      double the  = 2.*atan(exp(-eta));
      
      LogDebug("GeneratorInterface")<<"just before py1ent_"<<std::endl;
      py1ent_(ip, py6PID, ee, the, phi);
      LogDebug("GeneratorInterface")<<"did py1ent_"<<std::endl;
      
      double px     = pyjets.p[0][i]; // pt*cos(phi) ;
      double py     = pyjets.p[1][i]; // pt*sin(phi) ;
      double pz     = pyjets.p[2][i]; // mom*cos(the) ;
      
      HepMC::FourVector p(px,py,pz,ee) ;
      HepMC::GenParticle* Part = new HepMC::GenParticle(p,particleID,1);    
      //LogDebug("GeneratorInterface")<<"px="<<px<<", py="<<py<<", pz="<<pz<<", particleID="<<particleID<<std::endl;
      
      Part->suggest_barcode( ip ) ;
      Vtx->add_particle_out(Part);
      
      fEvt->add_vertex(Vtx);
      LogDebug("GeneratorInterface")<<"added event vertex: "<<mVx.at(i)<<", "<<mVy.at(i)<<", "<<mVz.at(i)<<", "<<mVt.at(i)<<std::endl;
      
    }//end of if put 2 stopped in same event or if decay only 1
  }//end of loop over stopped particles

  for ( HepMC::GenEvent::vertex_iterator vt=fEvt->vertices_begin(); vt!=fEvt->vertices_end(); ++vt ) {
    LogDebug("GeneratorInterface")<<"vertex is: "<<(*vt)->position().x()<<", "<<(*vt)->position().y()<<", "<<(*vt)->position().z()<<std::endl;
    for ( HepMC::GenVertex::particle_iterator pt=(*vt)->particles_begin(HepMC::children); pt!=(*vt)->particles_end(HepMC::children); ++pt ) {
      LogDebug("GeneratorInterface")<<"particle is: "<<(*pt)->pdg_id()<<std::endl;
    }
  }

  // run pythia
  pyexec_();
  LogDebug("GeneratorInterface")<<"ran pythia"<<std::endl;

  return;
}

DEFINE_FWK_MODULE(Pythia6HSCPGun);
