import os
from shutil import move

for index in range(1):
#for index in range(64):
    new_index = index+1
    print "new_index =", new_index
    oldCfgName = "reco_RAW2DIGI_L1Reco_RECO_cosmics_allphi_"+str(new_index)+".py"
    newCfgName = "reco_RAW2DIGI_L1Reco_RECO_cosmics_allphi_"+str(new_index)+"_1.py"
    outputFileName = "reco_NoBPTX_Run2012D_cosmics_allphi_"+str(new_index)+".root"
    oldCfg = open(oldCfgName)
    newCfg = open(newCfgName, "w")
    for line in oldCfg:
        line = line.replace("OUTPUTFILE", outputFileName)
        newCfg.write(line)
    oldCfg.close()
    newCfg.close()
    move("reco_RAW2DIGI_L1Reco_RECO_cosmics_allphi_"+str(new_index)+"_1.py","reco_RAW2DIGI_L1Reco_RECO_cosmics_allphi_"+str(new_index)+".py")

    scriptFileName = "runJob_"+str(new_index)
    scriptFile = open(scriptFileName, "w")
    scriptFile.write("""#!/bin/tcsh
setenv VO_CMS_SW_DIR /sharesoft/osg/app/cmssoft/cms/
setenv OSG_APP /sharesoft/osg/app/
setenv SCRAM_ARCH slc6_amd64_gcc481
source /cvmfs/cms.cern.ch/cmsset_default.csh
cd /home/alimena/Analysis/CMSSW_7_2_3_patch1/src/StoppedHSCPMuon/Ntuples/reco/
eval `scram runtime -sh`
cmsRun """+oldCfgName+"""
lcg-cp -b -v -D srmv2 file:./"""+outputFileName+""" srm://srm.hep.brown.edu:8443/srm/v2/server'?'SFN=/mnt/hadoop/store/user/jalimena/cosmics_allphi_reco/"""+outputFileName+"""
rm """+outputFileName+"""
"""
)

    scriptFile.close()

    condorFileName = "condor_"+str(new_index)
    condorFile = open(condorFileName, "w")
    condorFile.write("""
universe = vanilla
Executable = """+scriptFileName+"""
Requirements = Memory >= 199 &&OpSys == \"LINUX\"&& (Arch != \"DUMMY\" )&& Disk > 1000000
Should_Transfer_Files = YES
Transfer_Input_Files = """+oldCfgName+"""
Output = Cosmics_"""+str(new_index)+"""_$(Cluster)_$(Process).stdout
Error = Cosmics_"""+str(new_index)+"""_$(Cluster)_$(Process).stderr
Log = Cosmics_"""+str(new_index)+"""_$(Cluster)_$(Process).log
notify_user = ${LOGNAME}@FNAL.GOV
Queue 1
"""
)
    condorFile.close()


    print "condor_submit "+condorFileName
    os.system("condor_submit "+condorFileName)
