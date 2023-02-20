*** General Information

This set of tools should (hopefully) allow the user to build the MTuple files for the beam and atmospheric samples for the first iteration of the joint T2K+SK MaCh3 analysis. This assumes that the MC has been provided by SK and T2K-SK groups.

It also includes a set of installation scripts to build a T2KRW stack such that MAQEh weights can be built.

*** Dependancies

This guide will assume the following dependancies have been installed. The provided versions have been tested, although it's likely other versions will work. However, other versions should be tested and validated.

- gcc [4.8.5]
- cmake [3.17.5]
- ROOT [5.34.38]
- imake [1.0.7]
- makedepend [1.0.5]
- CERNLib [2005] -> Installation instructions here: https://t2k.org/asg/xsec/niwgdocs/neut/install_neut
- python2 and python3

In MAQEhTools, a 'setup_Deps.sh' is included. It is assumed the user can correctly modify this script to setup the correct environment variables to load these dependancies.

*** Installing T2KRW Tools to generate MAQEh weights

In order to generate the event-by-event MAQE-hydrogen weights, the T2K-RW tools need to be built and installed. These follow the a reduced set of instructions from: https://github.com/dbarrow257/T2KSKJointFit_SplineTools/tree/master/AdditionalSplinesInstallScripts . 

Working inside the 'MAQEhTools' directory,

- Comment out all the NEUT/NIWGRW/T2KRW/OAGenWeightsApps lines from 'setup.sh'. Then source setup.sh: 'source setup_SK.sh'
- 'sh build_neut.sh' installs and builds neut. If there are any 'autolib' looking errors, follow the instructions: https://github.com/neut-devel/neut . Once built, uncomment the neut lines in 'setup.sh' and resource setup.sh
- 'sh build_niwg.sh' installs and builds NIWGRW. Once built, uncomment the NIWGRW lines in 'setup.sh' and resource setup.sh
- 'sh build_t2krw.sh' installs and builds T2KRW. Once built, uncomment the T2KRW lines in 'setup.sh' and resource setup.sh
- 'sh build_oagenweightsapps.sh' installs and builds OAGenWeightsApps. Once built, uncomment the OAGenWeightsApps lines in 'setup.sh' and resource setup.sh

At this point, there should be a T2KSKJointFit_MTupleTools/MAQEhTools/OAGenWeightsApps/build/Linux/bin/genWeights_T2KSKAtm_MAQE_H executable. This is what will be used to generate the event-by-event weights for both beam and atmospheric samples.

*** SKSamples

To build the atmospheric mtuples, the working directory should be T2KSKJointFit_MTupleTools/SKSamples.

The input files (i.e. those provided by Roger/SK) will be stored in T2KSKJointFit_MTupleTools/SKSamples/FullMC whereas the final mtuples ready for use in MaCh3 will be created in T2KSKJointFit_MTupleTools/SKSamples/SplitMC. To create these directories:

```
$ cd T2KSKJointFit_MTupleTools/SKSamples
$ sh MakeDirectory.sh
```

The macros designed to 'massage' the provided MC into MaCh3's expected format should be copied into the FullMC directory (with the exception of splitMC_AddFFF.C which will be discussed later) and ran from there:

```
$ cp AddAtmpdFriendWeights.cxx FullMC
$ cp AddMAQEWeights.cxx FullMC
$ cp HaddMC_500yr.sh FullMC
$ cp RunScript_T2KReweight_MAQEh.sh FullMC
$ cd FullMC
```

The next step is to download/copy the MC into FullMC directory. The current provided MC is stored on nextcloud: https://nextcloud.nms.kcl.ac.uk/apps/files/?dir=/T2KSK/atm_minituples/SF.2021 . The simplest way to download this is to use cadaver. Instructions for installing cadaver can be found: https://t2k.org/asg/oagroup/gadatastorage/index_html . To download the fils, 'mget sk4*'. 

The MC is provided in '100yr' chunks (with the exception of the PC samples which is provided in a single file). For each chunk, there also exists a 'friend' tree which stores event-by-event systematic weights. As MaCh3 doesn't support friend trees, these weights need to be copied into the mtuple file. This is done via:

```
$ root -b AddAtmpdFriendWeights.cxx
```

This will copy the AtmFlux, ATMPDDetector and ATMPDXsec event-by-event weights into the MC in a specific way. The current systematics provided look like an array indexed via:

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

The way these are added to the mtuple files can be found by looking at the 'IndiciesToCopy' vectors.

At this point, the individual '100yr' files can now be hadd-ed together using:

```
$ sh HaddMC_500yr.sh
```

This creates a file called 'sk4_fcmc_tau_pcmc_ummc_fQv4r0_sf_minituple_500yr.root' which contains all the MC events. At this point, the individual files could be deleted to save diskspace (the '100yr' and PC files).

The next step is to create the MAQEh event-by-event weights via:

```
$ sh RunScript_T2KReweight_MAQEh.sh
```

This creates an output file (named 'sk4_fcmc_tau_pcmc_ummc_fQv4r0_sf_minituple_500yr_MAQE_Weights.root') which contains the event-by-event weights. Again, this needs to be added to the mtuple using the following script. After this step, the MAQE_Weights file can be deleted to save diskspace.

```
$ root -b AddMAQEWeights.cxx
```

The final step is to split the MC by the ATMPDEventType (like iclass for those from T2K) and oscillation channel. The PC and Upmu samples don't have any tau events so there will be some combinations which have zero events. Unlike the previous macros (which are run within 'SKSamples/FullMC') this macro should be run from the 'T2KSKJointFit_MTupleTools/SKSamples' directory, via:

```
$ cd T2KSKJointFit_MTupleTools/SKSamples
$ root -b splitMC_AddFFF.C
```

This script takes a while. The final number of MC entries will be larger than that contained within the original MC as each event is used twice (once for assumed nue flux and once for assumed numu flux) and weighted by the FluxForFlavour (FFF) variable.

If everything went well, you should have a set of 228 (19*12) files within T2KSKJointFit_MTupleTools/SKSamples/SplitMC which are now in the MaCh3 expected file format. They can be sym-linked into MaCh3 and should run without problem.

*** T2KSamples

To build the beam mtuples, the working directory should be T2KSKJointFit_MTupleTools/T2KSamples.

The input files (i.e. those provided by Roger/SK) will be stored in T2KSKJointFit_MTupleTools/T2KSamples/FullMC whereas the final mtuples ready for use in MaCh3 will be created in T2KSKJointFit_MTupleTools/T2KSamples/SplitMC. To create these directories:

```
$ cd T2KSKJointFit_MTupleTools/SKSamples
$ sh MakeDirectory.sh
$ cd FullMC
```

The next step is to download/copy the MC into FullMC directory. The current provided MC is stored on nextcloud: https://nextcloud.nms.kcl.ac.uk/apps/files/?dir=/T2KSK/MaCh3/BeamMTuples/FilesProvidedByT2KSK&fileid=1662771 . The simplest way to download this is to use cadaver. Instructions for installing cadaver can be found: https://t2k.org/asg/oagroup/gadatastorage/index_html . This MC was provided by Lakshmi for the 2022 sensitivities. This will be updated once the new MC is ready.

The rest of the scripts are expected to be ran from within the 'T2KSKJointFit_MTupleTools/SKSamples' directory. From there, run the following script to generate the MAQEh event-by-event weights:

```
sh RunScript_T2KReweight_MAQEh.sh
```

This creates a file '*_MAQEh_Weights*' file for each MC file. These weights can be added from the weight files to the mtuple files via:

```
root -b AddMAQEWeights.cxx
```

At this point, the '*_MAQEh_Weights*' files can be deleted to save diskspace. The MC provided for the sensitivities, did not have any momentum cut applied to them. Consequently, the following script needs to be run to apply the standard beam momentum cut from the OA2020 analysis:

```
root -b ApplyLeptonMomentumCut.C
```
This applies a 200(100)MeV momentum cut for muon(electron) samples. Now the FullMC have been prepared, they should be split by iclass (equivalent of ATMPDEventType). To do this:

```
sh Go.sh
```

This applies the selection four times (1Re, 1Re, 1Re1de, MRmu) for each oscillation channel. This script calls 'makeSelectedMtuples.py' for each file within FullMC. This requires python2, but could be fairly easily updated to python3 without too much effort. This takes a little bit of time to run so be patient. Once completed, FullMC directory should contain files which look like:

```
fhc_nuebar_x_nuebar_wMomentumCut_cc1piselec.root        fhc_numu_x_nue_wMomentumCut_cc1piselec.root           rhc_numubar_x_nuebar_wMomentumCut_cc1piselec.root
fhc_nuebar_x_nuebar_wMomentumCut_nueselec.root          fhc_numu_x_nue_wMomentumCut_nueselec.root             rhc_numubar_x_nuebar_wMomentumCut_nueselec.root
fhc_nuebar_x_nuebar_wMomentumCut_numucc1piselec.root    fhc_numu_x_nue_wMomentumCut_numucc1piselec.root       rhc_numubar_x_nuebar_wMomentumCut_numucc1piselec.root
fhc_nuebar_x_nuebar_wMomentumCut_numuselec.root  ...
```

To move the important files to the SplitMC directory, run:

```
sh MoveFiles.sh
```

SplitMC should now contain 48 files (6 channels * 4 selections * 2 beam modes). At this point, everything in FullMC can be deleted to save diskspace.
To ensure that the files are named correctly (in accordance with MaCh3 expectation), run:

```
python rename.py
```

To apply the correct flux weights, 13av7 flux histograms have been included within this git-repo. To apply those weights, run:

```
root -b RedoFluxWeights_SK.cxx
```

Finally, the relative oscillation channel normalisation weights need to be included to ensure that the different channels are correctly weighted in the MC prediction. The numbers are taken from: http://www.t2k.org/t2ksk/documentation-page/MCWeighting/MCReweighting14a . I'm skeptical that they are from 14a, rather than 19b which is currently being used.... Either way, this adds a histogram with two bin values: one being the normalisation and the other being the POT the MC is generated assuming. This script is ran via:

```
root -b MakeNormHists.cxx
```

If everything went well, there should now be all the files (in the MaCh3 expected format) in splitMC. The MRmu and RHC 1Re1de samples are not considered validated using this technique as they have not been used. There should be 48 files in total. These can be sym-linked into MaCh3, or the T2KRW stack, for use in the fitter or to build systematic splines.

*** Final Remarks

At this point, there should be 48 files in T2KSKJointFit_MTupleTools/T2KSamples/SplitMC and 228 files in T2KSKJointFit_MTupleTools/SKSamples/SplitMC . If everything worked, congratulations! If it didn't, drop a slack message on #mach3-jointskatmospheric and someone (probably Dan will get back to you). Developments are encouraged, but 'thar be dragons' in this codebase...

```
   (  )   /\   _                 (     
    \ |  (  \ ( \.(               )                      _____
  \  \ \  `  `   ) \             (  ___                 / _   \
 (_`    \+   . x  ( .\            \/   \____-----------/ (o)   \_
- .-               \+  ;          (  O                           \____
                          )        \_____________  `              \  /
(__                +- .( -'.- <. - _  VVVVVVV VV V\                 \/
(_____            ._._: <_ - <- _  (--  _AAAAAAA__A_/                  |
  .    /./.+-  . .- /  +--  - .     \______________//_              \_______
  (__ ' /x  / x _/ (                                  \___'          \     /
 , x / ( '  . / .  /                                      |           \   /
    /  /  _/ /    +                                      /              \/
   '  (__/                                             /                  \   
```
