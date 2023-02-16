*** SKSamples

cp AddAtmpdFriendWeights.cxx FullMC
cp AddMAQEWeights.cxx FullMC
cp HaddMC_500yr.sh FullMC
cp RunScript_T2KReweight_MAQEh.sh FullMC

cd FullMC
Download MC from: https://nextcloud.nms.kcl.ac.uk/apps/files/?dir=/T2KSK/atm_minituples/SF.2021 using cadaver -> 'mget sk4*'
root -b AddAtmpdFriendWeights.cxx -> Adds ATMPD event-by-event weights from friend tree into mtuple
sh HaddMC_500yr.sh -> Merges all 100yr samples into one file

At this point, can rm *100yr* and pcmc_500yr*

sh RunScript_T2KReweight_MAQEh.sh -> Creates MAQEh weights
root -b AddMAQEWeights.cxx -> Adds MAQEh weights to mtuple

Can delete *_MAQEh_weights*

cd T2KSKJointFit_MTupleTools/SKSamples
root -b splitMC_AddFFF.C -> Splits mtuples by ATMPDEventType
