DIR=$PWD

cd ../../MAQEhTools
source ./setup.sh

./OAGenWeightsApps/build/Linux/bin/genWeights_T2KSKAtm_MAQE_H -s ../SKSamples/FullMC/sk4_fcmc_tau_pcmc_ummc_fQv4r0_sf_minituple_500yr.root -o ../SKSamples/FullMC/sk4_fcmc_tau_pcmc_ummc_fQv4r0_sf_minituple_500yr_MAQE_Weights.root

cd $DIR
