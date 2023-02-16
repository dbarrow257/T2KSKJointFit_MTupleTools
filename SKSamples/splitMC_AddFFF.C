#include <vector>

double returnFFF(float FluxForFlavor[2],int fluxFlavor,int detFlavor) {
  if (fluxFlavor*detFlavor<0) {
    std::cout << "Mismatch in nu/nubar:" << fluxFlavor << " | " << detFlavor << std::endl;
  }
  if ((abs(fluxFlavor) < 1)||(abs(fluxFlavor)>2)) {
    std::cout << "FluxFlavor incorrectly set:" << fluxFlavor << std::endl;
  }
  if ((abs(detFlavor) < 1)||(abs(detFlavor)>3)) {
    std::cout << "DetFlavor incorrectly set:" << detFlavor << std::endl;
  }

  double FFF = -999;

  if (abs(fluxFlavor)==1) {
    if (abs(detFlavor)==1) {
      FFF = FluxForFlavor[0]/FluxForFlavor[0];
    }
    else if ((abs(detFlavor)==2)||(abs(detFlavor)==3)) {
      FFF = FluxForFlavor[0]/FluxForFlavor[1];
    }
  }
  else if (abs(fluxFlavor)==2) {
    if (abs(detFlavor)==1) {
      FFF = FluxForFlavor[1]/FluxForFlavor[0];
    }
    else if ((abs(detFlavor)==2)||(abs(detFlavor)==3)) {
      FFF = FluxForFlavor[1]/FluxForFlavor[1];
    }
  }

  if (FFF==-999) {
    std::cout << "FluxForFlavor variable calculation not correct:" << FFF << std::endl;
  }

  //std::cout << "fluxFlavor: " << std::setw(3) << fluxFlavor << " detFlavor: " << std::setw(3) << detFlavor << " FluxForFlavor: " << std::setw(10) << FluxForFlavor[0] << " , " << std::setw(10) << FluxForFlavor[1] << " FFF: " << std::setw(10) << FFF << std::endl;

  return FFF;
  
}

int splitMC_AddFFF() {
  TString FileName = "./FullMC/sk4_fcmc_tau_pcmc_ummc_fQv4r0_sf_minituple_500yr.root";
  TFile* inMC = new TFile(FileName);
  TTree* inTree = (TTree*)inMC->Get("atm_minituple");

  int ATMPDEventType;
  int ipnu[50];
  float FluxForFlavor[2];
  double FFF;
  
  inTree->SetBranchAddress("ATMPDEventType",&ATMPDEventType);
  inTree->SetBranchAddress("ipnu",&ipnu);
  inTree->SetBranchAddress("FluxForFlavor",&FluxForFlavor);

  TBranch* FFF_Branch = (TBranch*)inTree->Branch("FFF",&FFF);
  
  int nSamples = 19;
  int nChannels = 12;
  /*
    1: Nue     -> Nue
    2: Nue     -> Numu
    3: Nue     -> Nutau
    4: Numu    -> Nue
    5: Numu    -> Numu
    6: Numu    -> Nutau

    7: Nueb    -> Nueb
    8: Nueb    -> Numub
    9: Nueb    -> Nutaub
    10: Numub  -> Nueb
    11: Numub  -> Numub
    12: Numub  -> Nutaub 
  */
  
  int MaxIndex = nSamples*nChannels;

  int nEntries = inTree->GetEntries();
 
  std::vector<TTree*> TreeList;
  std::vector<TFile*> FileList;
  TTree* outTree;
  TFile* outFile;
  for (int sample=0;sample<nSamples;sample++) {
    for (int channel=0;channel<nChannels;channel++) {
      outFile = new TFile(Form("./SplitMC/sk4_fcmc_tau_pcmc_ummc_fQv4r0_sf_minituple_500yr_Sample%i_Channel%i.root",sample+1,channel+1),"RECREATE");
      FileList.push_back(outFile);
      outTree = (TTree*)inTree->CloneTree(0);
      TreeList.push_back(outTree);
    }
  }

  if (MaxIndex!=TreeList.size()) {
    std::cout << "Something's gone wrong with Tree Vector size:" << TreeList.size() << std::endl;
  }
  
  int channel;
  int fluxFlavor;
  int detFlavor;
  
  int index;
  for (int entry=0;entry<nEntries;entry++) {
    inTree->GetEntry(entry);
    if (ATMPDEventType==-1) {
      continue;
    }

    fluxFlavor = detFlavor = -1;
    
    if (ipnu[0]==12) {
      channel = 1; //Nue->Nue
      fluxFlavor = 1;
      detFlavor = 1;
    }
    else if (ipnu[0]==-12) {
      channel = 7; //Nueb->Nueb
      fluxFlavor = -1;
      detFlavor = -1;
    }
    else if (ipnu[0]==14) {
      channel = 2; //Nue->Numu
      fluxFlavor = 1;
      detFlavor = 2;
    }
    else if (ipnu[0]==-14) {
      channel = 8; //Neub->Numub
      fluxFlavor = -1;
      detFlavor = -2;
    }
    else if (ipnu[0]==16) {
      channel = 3; //Nue->Nutau
      fluxFlavor = 1;
      detFlavor = 3;
    }
    else if (ipnu[0]==-16) {
      channel = 9; //Nueb->Nutaub
      fluxFlavor = -1;
      detFlavor = -3;
    }
    else {
      std::cout << "Something's gone wrong with channel:" << ipnu[0] << std::endl;
    }

    index = (ATMPDEventType-1)*nChannels+(channel-1);
    if (index>MaxIndex) {
      std::cout << "Something's gone wrong with index:" << index << std::endl;
    }
    //std::cout << "Entry: " << entry << " | Sample: " << ATMPDEventType << " | Channel: " << channel << " | index: " << index << std::endl;
    FFF = returnFFF(FluxForFlavor,fluxFlavor,detFlavor);
    TreeList[index]->Fill();

    if (ipnu[0]==12) {
      channel = 4; //Numu->Nue
      fluxFlavor = 2;
      detFlavor = 1;
    }
    else if (ipnu[0]==-12) {
      channel = 10; //Numub->Nueb
      fluxFlavor = -2;
      detFlavor = -1;
    }
    else if (ipnu[0]==14) {
      channel = 5; //Numu->Numu
      fluxFlavor = 2;
      detFlavor = 2;
    }
    else if (ipnu[0]==-14) {
      channel = 11; //Numub->Numub
      fluxFlavor = -2;
      detFlavor = -2;
    }
    else if (ipnu[0]==16) {
      channel = 6; //Numu->Nutau
      fluxFlavor = 2;
      detFlavor = 3;
    }
    else if (ipnu[0]==-16) {
      channel = 12; //Numub->Nutaub
      fluxFlavor = -2;
      detFlavor = -2;
    }
    else {
      std::cout << "Something's gone wrong with channel:" << ipnu[0] << std::endl;
    }

    index = (ATMPDEventType-1)*nChannels+(channel-1);
    if (index>MaxIndex) {
      std::cout << "Something's gone wrong with index:" << index << std::endl;
    }
    //std::cout << "Entry: " << entry << " | Sample: " << ATMPDEventType << " | Channel: " << channel << " | index: " << index << std::endl;
    FFF = returnFFF(FluxForFlavor,fluxFlavor,detFlavor);
    TreeList[index]->Fill();

  }
  
  int nWrittenTreeEntries = 0;
  for (int sample=0;sample<nSamples;sample++) {
    for (int channel=0;channel<nChannels;channel++) {
      std::cout << "Sample:" << std::setw(2) << sample+1 << " | Channel:" << std::setw(2) << channel << " | Entries:" << TreeList[sample*nChannels+channel]->GetEntries() << std::endl; 
      nWrittenTreeEntries += TreeList[sample*nChannels+channel]->GetEntries();
      FileList[sample*nChannels+channel]->cd();
      TreeList[sample*nChannels+channel]->Write();
      FileList[sample*nChannels+channel]->Close();
    }
  }

  std::cout << "Written Entries      :" << nWrittenTreeEntries << std::endl;
  std::cout << "Entries in input file:" << nEntries << std::endl;

  return 0;

} 
