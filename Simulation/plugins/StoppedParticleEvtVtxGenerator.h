#include "IOMC/EventVertexGenerators/interface/BaseEvtVtxGenerator.h"
#include <fstream>

namespace CLHEP {
  class RandFlat;
}

namespace gen{
  class Pythia6Service;
}

class StoppedParticleEvtVtxGenerator : public BaseEvtVtxGenerator 
{
public:
  StoppedParticleEvtVtxGenerator(const edm::ParameterSet & p);
  virtual ~StoppedParticleEvtVtxGenerator();

  virtual void produce( edm::Event& iEvent, const edm::EventSetup& iSetup);

  void getStoppingPoint(edm::Event& iEvent); 

  /// return a new event vertex
  //virtual CLHEP::Hep3Vector* newVertex();
  //virtual HepMC::FourVector* newVertex() ;
  virtual HepMC::FourVector* newVertex(CLHEP::HepRandomEngine*) ;
  
  virtual TMatrixD* GetInvLorentzBoost() {
    return 0;
  }
private:

  bool mVerbose;

  //gen::Pythia6Service* fPy6Service;

  // repetition of base class private member :-(
  edm::InputTag mSourceLabel;

  // input
  bool mReadFromFile;
  std::string mFileName;
  std::ifstream* mFile;
  std::string mStopPointProducer;

  // time smearing
  double mTimeMin;
  double mTimeMax;
  //CLHEP::RandFlat*  mRandom ;

  // stopped particle vertex
  float mVx;
  float mVy;
  float mVz;
  float mVt;
  bool isStoppedEvent;
};
