int AddWeightToMTuple(TString MTupleFileName, TString MTupleTreeName, TString MTupleBranchName, TString WeightFileName, TString WeightTreeName, TString WeightBranchName);

void AddMAQEWeights() {

  TString MTupleTreeName = "atm_minituple";
  TString MTupleBranchName = "wgts_maqeh";
  TString WeightTreeName = "weightstree";
  TString WeightBranchName = "MAQEh";

  TString MTupleDir = "./";
  TString WeightDir = "./";

  
  TString WeightFileName = "sk4_fcmc_tau_pcmc_ummc_fQv4r0_sf_minituple_500yr_MAQE_Weights.root";
  TString MTupleFileName = "sk4_fcmc_tau_pcmc_ummc_fQv4r0_sf_minituple_500yr.root";
  AddWeightToMTuple(MTupleDir+MTupleFileName,MTupleTreeName,MTupleBranchName,WeightDir+WeightFileName,WeightTreeName,WeightBranchName);

}

int AddWeightToMTuple(TString MTupleFileName, TString MTupleTreeName, TString MTupleBranchName, TString WeightFileName, TString WeightTreeName, TString WeightBranchName)
{
  std::cout << "MTupleFile   = " << MTupleFileName << std::endl;
  std::cout << "MTupleBranch = " << MTupleTreeName << std::endl;
  std::cout << "WeightFile   = " << WeightFileName << std::endl;
  std::cout << "WeightTree   = " << WeightTreeName << std::endl;
  std::cout << "WeightName   = " << WeightBranchName << std::endl;

  TFile *WeightFile = new TFile(WeightFileName.Data(),"READ");
  if (WeightFile->IsZombie()) {
    std::cout << "Weight File not found. Given:" << WeightFileName << std::endl;
    throw;
  }

  TTree *WeightTree = (TTree*)WeightFile->Get(WeightTreeName.Data());
  if (!WeightTree) {
    std::cout << "Weight Tree not found. Given:" << WeightTreeName << std::endl;
    throw;
  }

  TFile *MTupleFile = new TFile(MTupleFileName.Data(),"UPDATE");
  if (MTupleFile->IsZombie()) {
    std::cout << "MTuple File not found. Given:" << MTupleFileName << std::endl;
    throw;
  }
  TTree *MTupleTree = (TTree*)MTupleFile->Get(MTupleTreeName.Data());
  if (!MTupleTree) {
    std::cout << "MTuple Tree not found. Given:" << MTupleTreeName << std::endl;
    throw;
  }

  std::cout << "Entries: -----------------" << std::endl;
  std::cout << "MTuple  = " << std::setw(10) << MTupleTree->GetEntries() << std::endl;
  std::cout << "Weights = " << std::setw(10) << WeightTree->GetEntries() << std::endl;

  if (MTupleTree->GetEntries()!=WeightTree->GetEntries()) {
    std::cout << "Error: Number of entries not equal to number of weights. Exitting" << std::endl;
    throw;
  }

  double Variable;
  TBranch* MTupleBranch = (TBranch*)MTupleTree->Branch(MTupleBranchName.Data(),&Variable);

  double Weight;
  std::cout << "Getting '" << WeightBranchName << "' from '" << WeightTreeName << "' in " << WeightFileName << std::endl;
  WeightTree->SetBranchAddress(WeightBranchName.Data(),&Weight);

  for (int entry=0;entry<MTupleTree->GetEntries();entry++)
    {
      WeightTree->GetEntry(entry);
      Variable = Weight;
      MTupleBranch->Fill();
    }

  MTupleFile->cd();
  MTupleTree->Write("", TObject::kOverwrite);
  MTupleFile->Close();
  WeightFile->Close();

  return 1;

}
