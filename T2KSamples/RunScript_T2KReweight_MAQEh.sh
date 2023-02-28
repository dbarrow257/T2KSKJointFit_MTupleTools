DIR=$PWD

cd ../MAQEhTools
source ./setup.sh

./OAGenWeightsApps/build/Linux/bin/genWeights_T2KSKAtm_MAQE_H -s ../T2KSamples/FullMC/t2ksk19b.fqv4r0b.fhc.nuebar_x_nuebar.root -o ../T2KSamples/FullMC/fhc_nuebar_x_nuebar_MAQE_Weights.root
./OAGenWeightsApps/build/Linux/bin/genWeights_T2KSKAtm_MAQE_H -s ../T2KSamples/FullMC/t2ksk19b.fqv4r0b.fhc.numubar_x_nuebar.root -o ../T2KSamples/FullMC/fhc_numubar_x_nuebar_MAQE_Weights.root
./OAGenWeightsApps/build/Linux/bin/genWeights_T2KSKAtm_MAQE_H -s ../T2KSamples/FullMC/t2ksk19b.fqv4r0b.fhc.numu_x_nue.root -o ../T2KSamples/FullMC/fhc_numu_x_nue_MAQE_Weights.root
./OAGenWeightsApps/build/Linux/bin/genWeights_T2KSKAtm_MAQE_H -s ../T2KSamples/FullMC/t2ksk19b.fqv4r0b.fhc.nue_x_nue.root -o ../T2KSamples/FullMC/fhc_nue_x_nue_MAQE_Weights.root
./OAGenWeightsApps/build/Linux/bin/genWeights_T2KSKAtm_MAQE_H -s ../T2KSamples/FullMC/t2ksk19b.fqv4r0b.fhc.numubar_x_numubar.root -o ../T2KSamples/FullMC/fhc_numubar_x_numubar_MAQE_Weights.root
./OAGenWeightsApps/build/Linux/bin/genWeights_T2KSKAtm_MAQE_H -s ../T2KSamples/FullMC/t2ksk19b.fqv4r0b.fhc.numu_x_numu.root -o ../T2KSamples/FullMC/fhc_numu_x_numu_MAQE_Weights.root

./OAGenWeightsApps/build/Linux/bin/genWeights_T2KSKAtm_MAQE_H -s ../T2KSamples/FullMC/t2ksk19b.fqv4r0b.rhc.nuebar_x_nuebar.root -o ../T2KSamples/FullMC/rhc_nuebar_x_nuebar_MAQE_Weights.root
./OAGenWeightsApps/build/Linux/bin/genWeights_T2KSKAtm_MAQE_H -s ../T2KSamples/FullMC/t2ksk19b.fqv4r0b.rhc.numubar_x_nuebar.root -o ../T2KSamples/FullMC/rhc_numubar_x_nuebar_MAQE_Weights.root
./OAGenWeightsApps/build/Linux/bin/genWeights_T2KSKAtm_MAQE_H -s ../T2KSamples/FullMC/t2ksk19b.fqv4r0b.rhc.numu_x_nue.root -o ../T2KSamples/FullMC/rhc_numu_x_nue_MAQE_Weights.root
./OAGenWeightsApps/build/Linux/bin/genWeights_T2KSKAtm_MAQE_H -s ../T2KSamples/FullMC/t2ksk19b.fqv4r0b.rhc.nue_x_nue.root -o ../T2KSamples/FullMC/rhc_nue_x_nue_MAQE_Weights.root
./OAGenWeightsApps/build/Linux/bin/genWeights_T2KSKAtm_MAQE_H -s ../T2KSamples/FullMC/t2ksk19b.fqv4r0b.rhc.numubar_x_numubar.root -o ../T2KSamples/FullMC/rhc_numubar_x_numubar_MAQE_Weights.root
./OAGenWeightsApps/build/Linux/bin/genWeights_T2KSKAtm_MAQE_H -s ../T2KSamples/FullMC/t2ksk19b.fqv4r0b.rhc.numu_x_numu.root -o ../T2KSamples/FullMC/rhc_numu_x_numu_MAQE_Weights.root

cd $DIR
