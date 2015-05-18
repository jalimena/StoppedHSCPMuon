//makes histograms from ntuples
//file_dataset, bx_cut, cavern_cut, generatorMuon_cut, SA_cut, genMuonMatched_cut, trigger_cut, pt_cut, cha_cut, eta_cut, Upper_cut, RPC_cut, Rpx_Bx_cut

#include "iostream"
#include "string"
#include "sstream"
#include "cmath"
#include "vector"
#include "math.h"
#include "stdlib.h"
#include "TROOT.h"
#include "TRint.h"
#include "TSystem.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TH2F.h"
#include "TClass.h"
#include "TFile.h"
#include "TTree.h"
#include "TMath.h"
#include "TObject.h"
#include "TString.h"
#include "TLorentzVector.h"
#include "Riostream.h"
#include "Cintex/Cintex.h"
#include "StoppedHSCPMuon/Ntuples/interface/StoppedHSCPMuonEvent.h"

using namespace std;


class findTreevalues_findDuplicateEvents{
public:
  findTreevalues_findDuplicateEvents(int argc, char* argv[]) {   

    //define histograms
  }
  
  ~findTreevalues_findDuplicateEvents() {};
  
  virtual void loop(string& file_dataset);

private:

  //define histograms
};



int main(int argc, char* argv[]){
  if(argc!=2){
    cout<<"ERROR, need more arguments!"<<endl;
    cout<<"seeing "<<argc<<" arguments"<<endl;
    return 1;
  }

  string file_dataset;

  file_dataset = "NoBPTX_Run2012B";
  
  if(argc==2){
    file_dataset = argv[1];

    cout<<", file_dataset is: "<<file_dataset<<endl;
  }

  findTreevalues_findDuplicateEvents analyzer(argc, argv);

  cout<<"just before analyzer.loop"<<endl;
  analyzer.loop(file_dataset);
}

void findTreevalues_findDuplicateEvents::loop(string& file_dataset){

  cout<<"just started loop"<<endl;

  string host=getenv("HOST");
  string host_=host.substr(0,4);
  cout<<"host is: "<<host_<<endl;
  cout<<"started function"<<endl;

  //make sure dictionaries can be used for reading
  //converts Reflex dictionary information to CINT data structures used by  ROOT
  ROOT::Cintex::Cintex::Enable();

  gSystem->Load("libStoppedHSCPMuonNtuples");
  cout<<"loaded library"<<endl;
  
  //stop, glui, mcha, gmst, ppst
  //NoBP, Sing, Zmum
  string file_dataset_=file_dataset.substr(0,4);

  TString file = "blah";
  if(host_=="cmsl"){
    //if(resT3=="T3") file = "dcap:///pnfs/cms/WAX/11/store/user/alimena/Ntuples/" + file_dataset + "/stoppedHSCPMuonTree.root";
    //else if(resT3=="res") file = "dcap:///pnfs/cms/WAX/resilient/alimena/Ntuples/" + file_dataset + "/stoppedHSCPMuonTree.root";
    //else cout<<"problem with resT3!!!!!!"<<endl;
    file = "/uscms_data/d3/alimena/Ntuples/" + file_dataset + "/stoppedHSCPMuonTree.root";
  }
  //if(host_=="brux") file = "/mnt/hadoop/users/alimena/CMS/Ntuples/" + file_dataset + "/stoppedHSCPMuonTree.root";
  if(host_=="brux") file = "/mnt/hadoop/store/user/jalimena/Ntuples/" + file_dataset + "/stoppedHSCPMuonTree.root";
  //if(host_=="brux") file = "../test/stoppedHSCPMuonTree.root";
  if(host_=="lxpl") file = "root://eoscms//eos/cms/store/user/jalimena/Ntuples/" + file_dataset + "/stoppedHSCPMuonTree.root";
  //if(host_=="lxpl") file = "/afs/cern.ch/work/j/jalimena/Ntuples/" + file_dataset + "/stoppedHSCPMuonTree.root";



  cout<<"file is: "<<file<<endl;
  TFile* f1;
  if(host_=="brux") f1 = new TFile(file);
  else f1 = TFile::Open(file);

  if(!f1->IsZombie()) cout<<"opened input file"<<endl;
  else {
    cout<<"problem with input file?"<<endl;
    if(host_=="brux"){
      file = "/mnt/hadoop/store/user/jalimena/Ntuples/" + file_dataset + "/stoppedHSCPMuonTree.root";
      f1 = new TFile(file);
      if(!f1->IsZombie()) cout<<"opened input file on second attempt"<<endl;
      else{
	file = "/user_data/alimena/Ntuples/" + file_dataset + "/stoppedHSCPMuonTree.root";
	f1 = new TFile(file);
	if(!f1->IsZombie()) cout<<"opened input file on third attempt"<<endl;
      }
    }
  }

  //setup output text files
  TString outfile_path = "../txtfiles/StoppedParticleDuplicateEvents/duplicateEvents_" + file_dataset + ".txt"; 
  ofstream outfile(outfile_path);

  //get tree
  TTree* tree = (TTree*)f1->Get("stoppedHSCPMuonTree/StoppedHSCPMuonTree");
  //tree->Print();
  //tree->Show(0);

  //StoppedHSCPMuonEvent* events = new StoppedHSCPMuonEvent();
  StoppedHSCPMuonEvent* events = 0;

  //set branch address
  tree->SetBranchAddress("events",&events);

  //get entries for data_tree (read in the old tree), set new variables, fill new tree
  Int_t nentries = tree->GetEntriesFast();
  //Int_t nentries = tree->GetEntries();
  cout<<"number of entries is: "<<nentries<<endl;
  
  //for (Int_t i=0; i<100000; i++) {
    //for (Int_t i=0; i<500000; i++) {
  for (Int_t i=0; i<nentries; i++) {
    //for (Int_t i=0; i<2000; i++) {    
  //for (Int_t i=0; i<100; i++) {
    tree->GetEntry(i);
    //if(i%5000==0) cout<<"i is: "<<i<<endl;

    if(events->mcStoppedParticle_N==2){
      //cout<<"entry # is: "<<i<<", event # is: "<<events->id<<endl;
      outfile<<i<<" "<<events->id<<endl;
    }//end of if 2 stopped particles

  }//end of loop over entries
  //cout<<"end of loop over entries"<<endl;

  //fnew->cd();
  //id_hist->Write();
  
  //return(0);
}


