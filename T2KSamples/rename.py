import os

filedir = os.getcwd()+"/SplitMC/"
files = os.listdir(filedir)
for file in files:
    try:
        filename_tmp = (file.split("_wMomentumCut"))[0]+(file.split("_wMomentumCut"))[1]
        filename = "t2ksk19b.fqv4r0."+filename_tmp[17:]
        os.system("mv "+filedir+"/"+file+" "+filedir+"/"+filename)
    except:
        pass
