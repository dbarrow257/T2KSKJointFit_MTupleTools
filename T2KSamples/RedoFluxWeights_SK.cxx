// Quick script to change flux weights (wgtflx) in SK minituples (as required n samplePDFNue.cpp and samplePDFNumu.cpp). Should be run in root from the MaCh3 directory:
// " root
//   .L utils/RedoFluxWeights_SK.cxx++
//   RedoFluxWeights_SK() "


#include <stdlib.h>
#include "iostream"

#include "TTree.h"
#include "TFile.h"
#include "TBranch.h"
#include "TH1D.h"

void RedoFluxWeights_SK()
{
  // Names of folders where mtuples are saved
  char *mtuple_folder[3];
  mtuple_folder[0] = "./SplitMC/"; // FHC 1Rmu, 1Re
  mtuple_folder[1] = "./SplitMC/"; // RHC 1Rmu, 1Re
  mtuple_folder[2] = "./SplitMC/"; // FHC Nue1pi

  // Something to go in front of the mtuple name, to indicate which flux tuning it uses
  // Commented out for now because it breaks the loading of the mtuples
  char *flux_tuning_name = "";
  
  // Name of file containing flux histograms
  char *flx_filename[2];
  flx_filename[0] = "./Flux/tuned13av7p1/run1-10b_ndto9/sk_tuned13av7p1_13anom_run1-10b_numode_138.root" ; // FHC
  flx_filename[1] = "./Flux/tuned13av7p1/run5c-9d_ndto9/sk_tuned13av7p1_13anom_run5c-9d_antinumode_138.root" ; //RHC

  TFile *f_flx = new TFile(flx_filename[0]);
  TFile *r_flx = new TFile(flx_filename[1]);

  // Names of flux histograms
  char *histname_f[4]; // Forward horn current
  histname_f[0] = "enu_sk_tuned13a_numu_ratio";// numu
  histname_f[1] = "enu_sk_tuned13a_nue_ratio";// nue
  histname_f[2] = "enu_sk_tuned13a_numub_ratio";// numubar
  histname_f[3] = "enu_sk_tuned13a_nueb_ratio";// nuebar
  char *histname_r[4]; // Reverse horn current
  histname_r[0] = "enu_sk_tuned13a_numu_ratio"; // numu
  histname_r[1] = "enu_sk_tuned13a_nue_ratio"; // nue
  histname_r[2] = "enu_sk_tuned13a_numub_ratio"; // numubar
  histname_r[3] = "enu_sk_tuned13a_nueb_ratio"; // nuebar

  // Names of SK files 
  char *sk_filenames[18][3];

  // FHC 1Rmu, 1Re, numuCC1pi 1d.e., numuCC1pi 2d.e
  sk_filenames[0][0] = "t2ksk19b.fqv4r0.fhc.numu_x_numu_numuselec.root"; // FHC numu (numuselec)
  sk_filenames[0][1] = "t2ksk19b.fqv4r0.fhc.numu_x_numu_nueselec.root"; // FHC numu (nueselec)
  sk_filenames[0][2] = "t2ksk19b.fqv4r0.fhc.numu_x_numu_numucc1piselec.root"; // FHC numu (numucc1pi)

  sk_filenames[1][0] = "t2ksk19b.fqv4r0.fhc.nue_x_nue_numuselec.root"; // FHC nue (numuselec)
  sk_filenames[1][1] = "t2ksk19b.fqv4r0.fhc.nue_x_nue_nueselec.root"; // FHC nue (nueselec)
  sk_filenames[1][2] = "t2ksk19b.fqv4r0.fhc.nue_x_nue_numucc1piselec.root"; // FHC nue (numucc1pi)

  sk_filenames[2][0] = "t2ksk19b.fqv4r0.fhc.numubar_x_numubar_numuselec.root"; // FHC numubar (numuselec)
  sk_filenames[2][1] = "t2ksk19b.fqv4r0.fhc.numubar_x_numubar_nueselec.root"; // FHC numubar (nueselec)
  sk_filenames[2][2] = "t2ksk19b.fqv4r0.fhc.numubar_x_numubar_numucc1piselec.root"; // FHC numubar (numucc1pi)

  sk_filenames[3][0] = "t2ksk19b.fqv4r0.fhc.nuebar_x_nuebar_numuselec.root"; // FHC nuebar (numuselec)
  sk_filenames[3][1] = "t2ksk19b.fqv4r0.fhc.nuebar_x_nuebar_nueselec.root"; // FHC nuebar (nueselec)
  sk_filenames[3][2] = "t2ksk19b.fqv4r0.fhc.nuebar_x_nuebar_numucc1piselec.root"; // FHC nuebar (numucc1pi)

  sk_filenames[4][0] = "t2ksk19b.fqv4r0.fhc.numu_x_nue_numuselec.root"; // FHC signue (numuselec)
  sk_filenames[4][1] = "t2ksk19b.fqv4r0.fhc.numu_x_nue_nueselec.root"; // FHC signue (nueselec)
  sk_filenames[4][2] = "t2ksk19b.fqv4r0.fhc.numu_x_nue_numucc1piselec.root"; // FHC signue (numucc1pi)

  sk_filenames[5][0] = "t2ksk19b.fqv4r0.fhc.numubar_x_nuebar_numuselec.root"; // FHC signuebar (numuselec)
  sk_filenames[5][1] = "t2ksk19b.fqv4r0.fhc.numubar_x_nuebar_nueselec.root"; // FHC signuebar (nueselec)
  sk_filenames[5][2] = "t2ksk19b.fqv4r0.fhc.numubar_x_nuebar_numucc1piselec.root"; // FHC signuebar (numucc1pi)

  // RHC 1Rmu, 1Re
  sk_filenames[6][0]  = "t2ksk19b.fqv4r0.rhc.numu_x_numu_numuselec.root"; // RHC numu (numuselec)
  sk_filenames[6][1]  = "t2ksk19b.fqv4r0.rhc.numu_x_numu_nueselec.root"; // RHC numu (nueselec)
  sk_filenames[7][0]  = "t2ksk19b.fqv4r0.rhc.nue_x_nue_numuselec.root"; // RHC nue (numuselec)
  sk_filenames[7][1]  = "t2ksk19b.fqv4r0.rhc.nue_x_nue_nueselec.root"; // RHC nue (nueselec)
  sk_filenames[8][0]  = "t2ksk19b.fqv4r0.rhc.numubar_x_numubar_numuselec.root"; // RHC numubar (numuselec)
  sk_filenames[8][1]  = "t2ksk19b.fqv4r0.rhc.numubar_x_numubar_nueselec.root"; // RHC numubar (nueselec)
  sk_filenames[9][0]  = "t2ksk19b.fqv4r0.rhc.nuebar_x_nuebar_numuselec.root"; // RHC nuebar (numuselec)
  sk_filenames[9][1]  = "t2ksk19b.fqv4r0.rhc.nuebar_x_nuebar_nueselec.root"; // RHC nuebar (nueselec)
  sk_filenames[10][0] = "t2ksk19b.fqv4r0.rhc.numu_x_nue_numuselec.root"; // RHC signue (numuselec)
  sk_filenames[10][1] = "t2ksk19b.fqv4r0.rhc.numu_x_nue_nueselec.root"; // RHC signue (nueselec)
  sk_filenames[11][0] = "t2ksk19b.fqv4r0.rhc.numubar_x_nuebar_numuselec.root"; // RHC signuebar (numuselec)
  sk_filenames[11][1] = "t2ksk19b.fqv4r0.rhc.numubar_x_nuebar_nueselec.root"; // RHC signuebar (nueselec)
 
  // FHC nue1pi
  sk_filenames[12][1] = "t2ksk19b.fqv4r0.fhc.numu_x_numu_cc1piselec.root"; // FHC numu (cc1piselec)
  sk_filenames[13][1] = "t2ksk19b.fqv4r0.fhc.nue_x_nue_cc1piselec.root"; // FHC nue (cc1piselec)
  sk_filenames[14][1] = "t2ksk19b.fqv4r0.fhc.numubar_x_numubar_cc1piselec.root"; // FHC numubar (cc1piselec)
  sk_filenames[15][1] = "t2ksk19b.fqv4r0.fhc.nuebar_x_nuebar_cc1piselec.root"; // FHC nuebar (cc1piselec)
  sk_filenames[16][1] = "t2ksk19b.fqv4r0.fhc.numu_x_nue_cc1piselec.root"; // FHC signue (cc1piselec)
  sk_filenames[17][1] = "t2ksk19b.fqv4r0.fhc.numubar_x_nuebar_cc1piselec.root"; // FHC signuebar (cc1piselec)

  // Loop over files, get trees, and add weights

  for (int i=0; i<18; i++)
    {
      for (int j=0; j<3; j++)
	{
	  std::cout << "On i: " << i << " and j: " << j << std::endl;
	  //	  No such thing as Nue1pi numuselec files (so skip)
	  if (i>=12 && j==0) continue;
	  if (i>5 && j>1) continue;
	  
	  char Filename[200];
	  if (i<6) // FHC 1Rmu, 1Re
	    sprintf(Filename,"%s/%s%s",mtuple_folder[0], flux_tuning_name, sk_filenames[i][j]);
	  else if (i<12) // RHC 1Rmu, 1Re
	    sprintf(Filename,"%s/%s%s",mtuple_folder[1], flux_tuning_name, sk_filenames[i][j]);
	  else // FHC Nue1pi
	    sprintf(Filename,"%s/%s%s",mtuple_folder[2], flux_tuning_name, sk_filenames[i][j]);
	    
  

	  std::cout << "Filename = " << Filename << std::endl;
	  
	  if (i<6 || i>11) // FHC 1Rmu, 1Re or FHC Nue1pi
	    std::cout << "Flux filename = " << flx_filename[0] << std::endl;
	  else // RHC 1Rmu, 1Re
	    std::cout << "Flux filename = " << flx_filename[1] << std::endl;

	  TFile *f_sk = new TFile(Filename,"UPDATE");
	  TTree *mtuple = (TTree*)f_sk->Get("mtuple");
	  // Open correct histogram from flux file
	  TH1D *flxhist;
	  if (i==0 || i==4 || i==12 || i==16) // FHC numu, signalnue
	    flxhist = (TH1D*)f_flx->Get(histname_f[0]);
	  if (i==1 || i==13) // FHC nue
	    flxhist = (TH1D*)f_flx->Get(histname_f[1]);
	  if (i==2 || i==5 || i==14 || i==17) // FHC numubar, signalnuebar
	    flxhist = (TH1D*)f_flx->Get(histname_f[2]);
	  if (i==3 || i==15) // FHC nuebar
	    flxhist = (TH1D*)f_flx->Get(histname_f[3]);
	  else if (i==6 || i==10) // RHC numu, signalnue
	    flxhist = (TH1D*)r_flx->Get(histname_r[0]);
	  else if (i==7) // RHC nue
	    flxhist = (TH1D*)r_flx->Get(histname_r[1]);
	  else if (i==8 || i==11) // RHC numubar, signalnuebar
	    flxhist = (TH1D*)r_flx->Get(histname_r[2]);
	  else if (i==9) // RHC nuebar
	    flxhist = (TH1D*)r_flx->Get(histname_r[3]);
	  std::cout << "Applying weights from flux histogram: " << flxhist->GetName() << std::endl;
	  
	  if (!flxhist)
	    std::cerr << "Error - could not open the correct flux histogram (i=" << i << ", j = " << j << ")" << std::endl;

	  std::cout << "mtuple->GetEntries() = " << mtuple->GetEntries() << std::endl;

	  // Clone mtuple to a new tree (to replace flux weight branch)
	  std::cout << "Cloning tree, excluding existing wgtflx branch" << endl;
	  mtuple->SetBranchStatus("*",1);
	  mtuple->SetBranchStatus("wgtflx",0);
	  TTree *newtree = mtuple->CloneTree();
	  newtree->SetName("newtree");
	  //newtree->CopyEntries(mtuple);

	  // Add branch to tree
	  Double_t wgtflx;
	  float pnu[100];
	  newtree->SetBranchAddress("pnu",&pnu);

	  cout << "Adding extra branch to mtuple" << endl;
	  TBranch *newBranch = newtree->Branch("wgtflx", &wgtflx);

	  for (int entry=0; entry<newtree->GetEntries(); entry++)
	    {
	      newtree->GetEntry(entry);

	      int bin = flxhist->FindBin(pnu[0]);
	      if (bin==0 || bin>flxhist->GetNbinsX())
	  	std::cout << "Error: trying to call bin " << bin << " when maximum number of bins in flxhist is " << flxhist->GetNbinsX() << std::endl;
	      wgtflx = flxhist->GetBinContent(bin);

	      newBranch->Fill();
	    }

	  std::cout << "mtuple entries (after changing flux weights): " << newtree->GetEntries() << std::endl;

	  // Save the new version of mtuple
	  delete mtuple;
	  f_sk->Delete("mtuple;*");
	  //f_sk->Delete("newtree;*");
	  newtree->SetName("mtuple");
	  f_sk->cd();
	  newtree->Write("mtuple", TObject::kOverwrite);
	  f_sk->Close();
	  cout << endl << endl;
	}
    }

  f_flx->Close();
  r_flx->Close();
}
