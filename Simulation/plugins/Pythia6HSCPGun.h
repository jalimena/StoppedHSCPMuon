#ifndef gen_Pythia6HSCPGun_h
#define gen_Pythia6HSCPGun_h

#include <fstream>

#include "GeneratorInterface/Pythia6Interface/plugins/Pythia6ParticleGun.h"

namespace CLHEP {
  class HepRandomEngine;
}

namespace gen {

   class Pythia6HSCPGun : public Pythia6ParticleGun
   {
   
      public:
      
        Pythia6HSCPGun( const edm::ParameterSet& );
        virtual ~Pythia6HSCPGun();

	void produce( edm::Event& fEvt, const edm::EventSetup& iSetup );
	  
   protected:
	void generateEvent(CLHEP::HepRandomEngine*);
	//void generateEvent();
	
   private:

	bool mReadFromFile;
	std::string mStopPointProducer;
	std::string mFileName;
	std::ifstream* mFile;
	bool putTwoStoppedInSameEvent;
	int stoppedParticleNumber;
	int nStoppedParticles;

	std::vector<int> mPID;
	std::vector<float> mVx;
	std::vector<float> mVy;
	std::vector<float> mVz;
	std::vector<float> mVt;

	//int mPID;
	//float mVx;
	//float mVy;
	//float mVz;

   };
  

}

#endif

