#include <cmath>

int AddWeightToMTuple(TString MTupleFileName, TString MTupleTreeName, TString MTupleBranchName, TString WeightFileName, TString WeightTreeName, TString WeightBranchName, int SizeOfArrayToCopy, std::vector<int> IndiciesToCopy)
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

  Float_t* Variable = new Float_t[IndiciesToCopy.size()];
  TString BranchTitle = Form("Weight[%i]/F",int(IndiciesToCopy.size()));
  TBranch* MTupleBranch = (TBranch*)MTupleTree->Branch(MTupleBranchName.Data(),Variable,BranchTitle.Data());

  Float_t* WeightArray = new Float_t[SizeOfArrayToCopy];
  std::cout << "Getting '" << WeightBranchName << "' from '" << WeightTreeName << "' in " << WeightFileName << " and saving it as " << MTupleBranchName << std::endl;
  WeightTree->SetBranchAddress(WeightBranchName.Data(),WeightArray);

  for (int entry=0;entry<MTupleTree->GetEntries();entry++)
    {
      WeightTree->GetEntry(entry);

      for (int iVar=0;iVar<IndiciesToCopy.size();iVar++) {
	Variable[iVar] = WeightArray[IndiciesToCopy[iVar]];
      }

      MTupleBranch->Fill();
    }

  MTupleFile->cd();
  MTupleTree->Write("", TObject::kOverwrite);
  MTupleFile->Close();
  WeightFile->Close();

  return 1;

}

void AddAtmpdFriendWeightsToMTuple(TString WeightFileName, TString MTupleFileName) {

  TString MTupleTreeName = "atm_minituple";
  TString MTupleBranchName;

  TString WeightTreeName = "atmpdsys";
  TString WeightBranchName = "SystValue";

  TString MTupleDir = "./";
  TString WeightDir = "./";

  /*
  *********************************************
  *    Row   *                      ErrorName *
  *********************************************
  *        0 *                     K_pi_ratio *
  *        1 *                        nu_path *
  *        2 *     relative_norm_FC_multi_GeV *
  *        3 *        relative_norm_PC_UpStop *
  *        4 *        up_stop_thru_separation *
  *        5 *              upstop_energy_cut *
  *        6 *            nonshowering_bg_sub *
  *        7 *                  upstop_bg_sub *
  *        8 * PC_stop_through_separation_top *
  *        9 *                 solar_activity *
  *       10 *               showering_bg_sub *
  *       11 *    shower_nonshower_separation *
  *       12 * PC_stop_through_separation_bar *
  *       13 * PC_stop_through_separation_bot *
  *       14 *                  dis_q2_high_W *
  *       15 *                   dis_had_mult *
  *       16 *               dis_q2_vec_low_W *
  *       17 *               dis_q2_axi_low_W *
  *       18 *                fcstopmu_bg_sub *
  */

  std::vector<int> IndiciesToCopy_1(5);
  IndiciesToCopy_1[0] = 0; //k_pi_ratio
  IndiciesToCopy_1[1] = 1; //nu_path
  IndiciesToCopy_1[2] = 9; //solar_activity
  IndiciesToCopy_1[3] = 2; //Relative_norm_FC_MultiGeV
  IndiciesToCopy_1[4] = 3; //Relative_norm_PC_UpStop  

  MTupleBranchName = "wgts_AtmFluxWeights";
  AddWeightToMTuple(MTupleDir+MTupleFileName,MTupleTreeName,MTupleBranchName,WeightDir+WeightFileName,WeightTreeName,WeightBranchName,19,IndiciesToCopy_1);

  std::vector<int> IndiciesToCopy_2(10);
  IndiciesToCopy_2[0] = 4; //Upstop_Thru_Separation
  IndiciesToCopy_2[1] = 5; //Upstop_Energy_cut
  IndiciesToCopy_2[2] = 6; //Non_showering_bg_sub
  IndiciesToCopy_2[3] = 7; //Upstop_bg_sub
  IndiciesToCopy_2[4] = 8; //PC_Stop_Thru_Separation
  IndiciesToCopy_2[5] = 10; //Showering_bg_sub
  IndiciesToCopy_2[6] = 11; //Showering_NonShowering_Separation
  IndiciesToCopy_2[7] = 12; //PC_Stop_Thru_Separation_Bar
  IndiciesToCopy_2[8] = 13; //PC_Stop_Thru_Separation_NuBar
  IndiciesToCopy_2[9] = 18; //fcstopmu_bg_sub

  MTupleBranchName = "wgts_SKCalibWeights";
  AddWeightToMTuple(MTupleDir+MTupleFileName,MTupleTreeName,MTupleBranchName,WeightDir+WeightFileName,WeightTreeName,WeightBranchName,19,IndiciesToCopy_2);

  std::vector<int> IndiciesToCopy_3(4);
  IndiciesToCopy_3[0] = 14; //dis_q2_high_W
  IndiciesToCopy_3[1] = 15; //dis_had_mult
  IndiciesToCopy_3[2] = 16; //dis_q2_vec_low_W
  IndiciesToCopy_3[3] = 17; //dis_q2_axi_low_W

  MTupleBranchName = "wgts_ATMPDXsecWeights";
  AddWeightToMTuple(MTupleDir+MTupleFileName,MTupleTreeName,MTupleBranchName,WeightDir+WeightFileName,WeightTreeName,WeightBranchName,19,IndiciesToCopy_3);
  
}

void AddAtmpdFriendWeights() {
  std::vector<TString> WeightFileNames;
  std::vector<TString> MTupleFileNames;

  WeightFileNames.push_back("sk4_fcmc_tau_fQv4r0_sf_minituple_100yr_01.sysfriend.root");
  MTupleFileNames.push_back("sk4_fcmc_tau_fQv4r0_sf_minituple_100yr_01.root");

  WeightFileNames.push_back("sk4_fcmc_tau_fQv4r0_sf_minituple_100yr_02.sysfriend.root");
  MTupleFileNames.push_back("sk4_fcmc_tau_fQv4r0_sf_minituple_100yr_02.root");

  WeightFileNames.push_back("sk4_fcmc_tau_fQv4r0_sf_minituple_100yr_03.sysfriend.root");
  MTupleFileNames.push_back("sk4_fcmc_tau_fQv4r0_sf_minituple_100yr_03.root");

  WeightFileNames.push_back("sk4_fcmc_tau_fQv4r0_sf_minituple_100yr_04.sysfriend.root");
  MTupleFileNames.push_back("sk4_fcmc_tau_fQv4r0_sf_minituple_100yr_04.root");

  WeightFileNames.push_back("sk4_fcmc_tau_fQv4r0_sf_minituple_100yr_05.sysfriend.root");
  MTupleFileNames.push_back("sk4_fcmc_tau_fQv4r0_sf_minituple_100yr_05.root");

  WeightFileNames.push_back("sk4_ummc_fQv4r0_sf_minituple_100yr.01.sysfriend.root");
  MTupleFileNames.push_back("sk4_ummc_fQv4r0_sf_minituple_100yr.01.root");

  WeightFileNames.push_back("sk4_ummc_fQv4r0_sf_minituple_100yr.02.sysfriend.root");
  MTupleFileNames.push_back("sk4_ummc_fQv4r0_sf_minituple_100yr.02.root");

  WeightFileNames.push_back("sk4_ummc_fQv4r0_sf_minituple_100yr.03.sysfriend.root");
  MTupleFileNames.push_back("sk4_ummc_fQv4r0_sf_minituple_100yr.03.root");

  WeightFileNames.push_back("sk4_ummc_fQv4r0_sf_minituple_100yr.04.sysfriend.root");
  MTupleFileNames.push_back("sk4_ummc_fQv4r0_sf_minituple_100yr.04.root");

  WeightFileNames.push_back("sk4_ummc_fQv4r0_sf_minituple_100yr.05.sysfriend.root");
  MTupleFileNames.push_back("sk4_ummc_fQv4r0_sf_minituple_100yr.05.root");

  WeightFileNames.push_back("sk4_pcmc_fQv4r0_sf_minituple_500yr.sysfriend.root");
  MTupleFileNames.push_back("sk4_pcmc_fQv4r0_sf_minituple_500yr.root");

  if (WeightFileNames.size() != MTupleFileNames.size()) {
    std::cerr << "Mismatch in WeightFileNames and MTupleFileNames!" << std::endl;
    throw;
  }

  for (int iFile=0;iFile<WeightFileNames.size();iFile++) {
    AddAtmpdFriendWeightsToMTuple(WeightFileNames[iFile],MTupleFileNames[iFile]);
  }
}
