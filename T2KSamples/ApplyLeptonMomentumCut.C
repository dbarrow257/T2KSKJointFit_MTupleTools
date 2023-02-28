#include <vector>

int ApplyCut(TString FileName) {

  TFile* inMC = new TFile(FileName+".root");
  TTree* inTree = (TTree*)inMC->Get("minituple");

  int iclass;
  float fq1rmom[200][7];

  inTree->SetBranchAddress("iclass",&iclass);
  inTree->SetBranchAddress("fq1rmom",&fq1rmom);
  
  int nEntries = inTree->GetEntries();
 
  TFile* outFile = new TFile(FileName+"_wMomentumCut.root","RECREATE");
  TTree* outTree = (TTree*)inTree->CloneTree(0);

  for (int entry=0;entry<nEntries;entry++) {
    
    inTree->GetEntry(entry);
    
    if (iclass==11 || iclass==14) {
      if (fq1rmom[0][1] < 100.) continue;
    } else if (iclass==13) {
      if (fq1rmom[0][2] < 200.) continue;
    } else {
      continue;
    }
    
    outTree->Fill();
  }

  outFile->cd();
  outTree->Write();

  return 0;
} 

int ApplyLeptonMomentumCut() {
  TString FileDir = "./FullMC/";

  std::vector<TString> Prefix(2);
  Prefix[0] = "t2ksk19b.fqv4r0b.fhc";
  Prefix[1] = "t2ksk19b.fqv4r0b.rhc";

  std::vector<TString> Channel(6);
  Channel[0] = "nuebar_x_nuebar";
  Channel[1] = "nue_x_nue";
  Channel[2] = "numubar_x_nuebar";
  Channel[3] = "numubar_x_numubar";
  Channel[4] = "numu_x_nue";
  Channel[5] = "numu_x_numu";

  for (int iPrefix=0;iPrefix<2;iPrefix++) {
    for (int iChannel=0;iChannel<6;iChannel++) {
      TString FileName = FileDir+"/"+Prefix[iPrefix]+"."+Channel[iChannel];
      std::cout << "Starting:" << FileName << std::endl;
      ApplyCut(FileName);
    }
  }
  
  return 0;
}
