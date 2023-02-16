// Quick script to add 'norm' hists to SK minituples (as required in samplePDFNue.cpp and samplePDFNumu.cpp. Should be run in root from the MaCh3 directory:
// " root
//   .L utils/MakeNormHists.cxx++
//   MakeNormHists() "

// Will check for 'norm' hist in the file. If it exists, will update it with the numbers given below. If it doesn't exists, will create it.


#include <stdlib.h>
#include "iostream"

#include "TH1D.h"
#include "TFile.h"

void MakeNormHists()
{
  // Numbers for normalisation
  // Taken from http://www.t2k.org/t2ksk/documentation-page/MCWeighting/MCReweighting14a
  double numerators[12];
  numerators[0]  = 1373.8715753; // NHC numu
  numerators[1]  = 26.224814886; // NHC nue
  numerators[2]  = 48.4951744134; // NHC numubar
  numerators[3]  = 2.74910336093; // NHC nuebar
  numerators[4]  = 1458.3399999; // NHC signue
  numerators[5]  = 50.2120145538; // NHC signuebar
  numerators[6]  = 205.213957312; // RHC numu
  numerators[7]  = 8.79315608601; // RHC nue
  numerators[8]  = 338.496583643; // RHC numubar
  numerators[9]  = 6.52180351576; // RHC nuebar
  numerators[10] = 211.81697101 ; // RHC signue
  numerators[11] = 357.710318015; // RHC signuebar

  double denominators[12];
  denominators[0] = 634441; // NHC numu
  denominators[1] = 127010; // NHC nue
  denominators[2] = 635545; // NHC numubar
  denominators[3] = 126865; // NHC nuebar
  denominators[4] = 127017; // NHC signue
  denominators[5] = 126509; // NHC signuebar
  denominators[6] = 634250; // RHC numu
  denominators[7] = 126829; // RHC nue
  denominators[8] = 634817; // RHC numubar
  denominators[9] = 126982; // RHC nuebar
  denominators[10] = 126923; // RHC signue
  denominators[11] = 126928; // RHC signuebar

  // POT used to create MC
  double pot = 1E21;
  double pot_anu = 1E21;

  //folder containing mtuples
  char* mtuple_folder = "./SplitMC/";
  // Names of SK files 
  // Note: it's important that the first index follows the same order as the indices in 'numerators' and 'denominators' (ie. numu / nue / numubar / nuebar / signue / signuebar)
  char *sk_filenames[12][4];
  sk_filenames[0][0]  = (char *)"t2ksk19b.fqv4r0.fhc.numu_x_numu_numuselec.root"; // NHC numu (numuselec)
  sk_filenames[0][1]  = (char *)"t2ksk19b.fqv4r0.fhc.numu_x_numu_nueselec.root"; // NHC numu (nueselec)
  sk_filenames[0][2]  = (char *)"t2ksk19b.fqv4r0.fhc.numu_x_numu_cc1piselec.root"; // NHC numu (cc1piselec)
  sk_filenames[0][3]  = (char *)"t2ksk19b.fqv4r0.fhc.numu_x_numu_numucc1piselec.root";// NHC numu (numucc1piselec)
  sk_filenames[1][0]  = (char *)"t2ksk19b.fqv4r0.fhc.nue_x_nue_numuselec.root"; // NHC nue (numuselec)
  sk_filenames[1][1]  = (char *)"t2ksk19b.fqv4r0.fhc.nue_x_nue_nueselec.root"; // NHC nue (nueselec)
  sk_filenames[1][2]  = (char *)"t2ksk19b.fqv4r0.fhc.nue_x_nue_cc1piselec.root"; // NHC nue (cc1piselec)
  sk_filenames[1][3]  = (char *)"t2ksk19b.fqv4r0.fhc.nue_x_nue_numucc1piselec.root";// NHC nue (numucc1pi1deselec)
  sk_filenames[2][0]  = (char *)"t2ksk19b.fqv4r0.fhc.numubar_x_numubar_numuselec.root"; // NHC numubar (numuselec)
  sk_filenames[2][1]  = (char *)"t2ksk19b.fqv4r0.fhc.numubar_x_numubar_nueselec.root"; // NHC numubar (nueselec)
  sk_filenames[2][2]  = (char *)"t2ksk19b.fqv4r0.fhc.numubar_x_numubar_cc1piselec.root"; // NHC numubar (cc1piselec)
  sk_filenames[2][3]  = (char *)"t2ksk19b.fqv4r0.fhc.numubar_x_numubar_numucc1piselec.root";// NHC numubar (numucc1piselec)
  sk_filenames[3][0]  = (char *)"t2ksk19b.fqv4r0.fhc.nuebar_x_nuebar_numuselec.root"; // NHC nuebar (numuselec)
  sk_filenames[3][1]  = (char *)"t2ksk19b.fqv4r0.fhc.nuebar_x_nuebar_nueselec.root"; // NHC nuebar (nueselec)
  sk_filenames[3][2]  = (char *)"t2ksk19b.fqv4r0.fhc.nuebar_x_nuebar_cc1piselec.root"; // NHC nuebar (cc1piselec)
  sk_filenames[3][3]  = (char *)"t2ksk19b.fqv4r0.fhc.nuebar_x_nuebar_numucc1piselec.root";// NHC nuebar (numucc1piselec)
  sk_filenames[4][0]  = (char *)"t2ksk19b.fqv4r0.fhc.numu_x_nue_numuselec.root"; // NHC signue (numuselec)
  sk_filenames[4][1]  = (char *)"t2ksk19b.fqv4r0.fhc.numu_x_nue_nueselec.root"; // NHC signue (nueselec)
  sk_filenames[4][2]  = (char *)"t2ksk19b.fqv4r0.fhc.numu_x_nue_cc1piselec.root"; // NHC signue (cc1piselec)
  sk_filenames[4][3]  = (char *)"t2ksk19b.fqv4r0.fhc.numu_x_nue_numucc1piselec.root";// NHC signue (numucc1piselec)
  sk_filenames[5][0]  = (char *)"t2ksk19b.fqv4r0.fhc.numubar_x_nuebar_numuselec.root"; // NHC signuebar (numuselec)
  sk_filenames[5][1]  = (char *)"t2ksk19b.fqv4r0.fhc.numubar_x_nuebar_nueselec.root"; // NHC signuebar (nueselec)
  sk_filenames[5][2]  = (char *)"t2ksk19b.fqv4r0.fhc.numubar_x_nuebar_cc1piselec.root"; // NHC signuebar (cc1piselec)
  sk_filenames[5][3]  = (char *)"t2ksk19b.fqv4r0.fhc.numubar_x_nuebar_numucc1piselec.root";// NHC signuebar (numucc1piselec)
  sk_filenames[6][0]  = (char *)"t2ksk19b.fqv4r0.rhc.numu_x_numu_numuselec.root"; // RHC numu (numuselec)
  sk_filenames[6][1]  = (char *)"t2ksk19b.fqv4r0.rhc.numu_x_numu_nueselec.root"; // RHC numu (nueselec)
  sk_filenames[6][2]  = (char *)"t2ksk19b.fqv4r0.rhc.numu_x_numu_cc1piselec.root"; // RHC numu (cc1piselec)
  sk_filenames[7][0]  = (char *)"t2ksk19b.fqv4r0.rhc.nue_x_nue_numuselec.root"; // RHC nue (numuselec)
  sk_filenames[7][1]  = (char *)"t2ksk19b.fqv4r0.rhc.nue_x_nue_nueselec.root"; // RHC nue (nueselec)
  sk_filenames[7][2]  = (char *)"t2ksk19b.fqv4r0.rhc.nue_x_nue_cc1piselec.root"; // RHC nue (cc1piselec)
  sk_filenames[8][0]  = (char *)"t2ksk19b.fqv4r0.rhc.numubar_x_numubar_numuselec.root"; // RHC numubar (numuselec)
  sk_filenames[8][1]  = (char *)"t2ksk19b.fqv4r0.rhc.numubar_x_numubar_nueselec.root"; // RHC numubar (nueselec)
  sk_filenames[8][2]  = (char *)"t2ksk19b.fqv4r0.rhc.numubar_x_numubar_cc1piselec.root"; // RHC numubar (cc1piselec)
  sk_filenames[9][0]  = (char *)"t2ksk19b.fqv4r0.rhc.nuebar_x_nuebar_numuselec.root"; // RHC nuebar (numuselec)
  sk_filenames[9][1]  = (char *)"t2ksk19b.fqv4r0.rhc.nuebar_x_nuebar_nueselec.root"; // RHC nuebar (nueselec)
  sk_filenames[9][2]  = (char *)"t2ksk19b.fqv4r0.rhc.nuebar_x_nuebar_cc1piselec.root"; // RHC nuebar (cc1piselec)
  sk_filenames[10][0] = (char *)"t2ksk19b.fqv4r0.rhc.numu_x_nue_numuselec.root"; // RHC signue (numuselec)
  sk_filenames[10][1] = (char *)"t2ksk19b.fqv4r0.rhc.numu_x_nue_nueselec.root"; // RHC signue (nueselec)
  sk_filenames[10][2] = (char *)"t2ksk19b.fqv4r0.rhc.numu_x_nue_cc1piselec.root"; // RHC signue (cc1piselec)
  sk_filenames[11][0] = (char *)"t2ksk19b.fqv4r0.rhc.numubar_x_nuebar_numuselec.root"; // RHC signuebar (numuselec)
  sk_filenames[11][1] = (char *)"t2ksk19b.fqv4r0.rhc.numubar_x_nuebar_nueselec.root"; // RHC signuebar (nueselec)
  sk_filenames[11][2] = (char *)"t2ksk19b.fqv4r0.rhc.numubar_x_nuebar_cc1piselec.root"; // RHC signuebar (cc1piselec)

  // For each file, check if TH1D* norm exists, and replace (or create) it
  for (int nutype=0; nutype<12; nutype++)
    {
      for (int selec=0; selec<4; selec++)
	{
	  if(selec>2 && nutype>5){continue;}
	  std::cout << " on selec " << selec << " and nutype " << nutype << std::endl;
	  char FileName[200];
	  sprintf(FileName, "%s/%s", mtuple_folder, sk_filenames[nutype][selec]);
	  std::cout << "on file " << FileName << std::endl;

	  TFile *sk_file = new TFile(FileName,"UPDATE"); 

	  TH1D *norm_old = (TH1D*)sk_file->Get("norm");
	  if(norm_old) // delete histogram from file
	    {
	      sk_file->Delete("norm;*");
	    }

	  TH1D *norm = new TH1D("norm","norm",10,0,10);

	  // Set norm bin 1 content (neutrino type normalisation)
	  double val = numerators[nutype]/denominators[nutype];
	  norm->SetBinContent(1,val);

	  // Set norm bin 2 content (POT used to generate MC)
	  if (nutype<6) // Neutrino mode (normal horn current)
	    {
	      norm->SetBinContent(2,pot);
	    }
	  else // Antuneutrino mode (reverse horn current)
	    {
	      norm->SetBinContent(2,pot_anu);
	    }

	  // Save norm hist to file
	  norm->Write();
	  sk_file->Close();
	}
    }
}
