#!/bin/tcsh

#foreach x (mchamp100 mchamp200 mchamp300 mchamp400 mchamp500 mchamp600 mchamp700 mchamp800 mchamp900 mchamp1000)
foreach x (mchamp100_1DSA_invbetaP5_p60 mchamp200_1DSA_invbetaP5_p60 mchamp300_1DSA_invbetaP5_p80 mchamp400_1DSA_invbetaP5_p110 mchamp500_1DSA_invbetaP5_p140 mchamp600_1DSA_invbetaP5_p150 mchamp700_1DSA_invbetaP5_p170 mchamp800_1DSA_invbetaP5_p170 mchamp900_1DSA_invbetaP5_p200 mchamp1000_1DSA_invbetaP5_p200)
#foreach x (mchamp100_1DSA_invbetaP5_p60 mchamp200_1DSA_invbetaP5_p60 mchamp300_1DSA_invbetaP5_p80 mchamp400_1DSA_invbetaP5_p110)
#foreach x (mchamp500_1DSA_invbetaP5_p140 mchamp600_1DSA_invbetaP5_p150 mchamp700_1DSA_invbetaP5_p170 mchamp800_1DSA_invbetaP5_p170 mchamp900_1DSA_invbetaP5_p200 mchamp1000_1DSA_invbetaP5_p200)
    #rm -r $x"/toymc"
    #rm -r $x"/"*".pdf"
    #rm -r $x"/"*".png"
    #rm -r $x"/"*".C"
    #rm -r $x"/"*".h"
    #rm -r $x"/"*".so"
    #rm -r $x"/"*".d"

    chmod +x $x"/toymc/job43/job43.sh"
    #./$x"/toymc/runAll_hadd.sh"
    #cp $x"/toymc/runAll.sh" $x"/toymc/runAll_hadd.sh"
    #python makeToyJobs.py $x"_pt35"
    #python makeToyJobs.py $x"_pt40"
    #python makeToyJobs.py $x"_pt45"
    #python makeToyJobs.py $x"_pt50"
    #python makeToyJobs.py $x"_pt60"
    #python makeToyJobs.py $x"_pt80"
    #python makeToyJobs.py $x"_pt100"
    #python makeToyJobs.py $x"_pt150"
    #python makeToyJobs.py $x"_pt200"

    #cp $x"searchLifetimes.txt" $x"_pt35searchLifetimes.txt"
    #cp $x"searchLifetimes.txt" $x"_pt40searchLifetimes.txt"
    #cp $x"searchLifetimes.txt" $x"_pt45searchLifetimes.txt"
    #cp $x"searchLifetimes.txt" $x"_pt50searchLifetimes.txt"
    #cp $x"searchLifetimes.txt" $x"_pt60searchLifetimes.txt"
    #cp $x"searchLifetimes.txt" $x"_pt80searchLifetimes.txt"
    #cp $x"searchLifetimes.txt" $x"_pt100searchLifetimes.txt"
    #cp $x"searchLifetimes.txt" $x"_pt150searchLifetimes.txt"
    #cp $x"searchLifetimes.txt" $x"_pt200searchLifetimes.txt"
    #cp $x"/parameters.txt" $x"_pt35"
    #cp $x"/parameters.txt" $x"_pt40"
    #cp $x"/parameters.txt" $x"_pt45"
    #cp $x"/parameters.txt" $x"_pt50"
    #cp $x"/parameters.txt" $x"_pt60"
    #cp $x"/parameters.txt" $x"_pt80"
    #cp $x"/parameters.txt" $x"_pt100"
    #cp $x"/parameters.txt" $x"_pt150"
    #cp $x"/parameters.txt" $x"_pt200"
end

