#!/bin/tcsh

#foreach x ( `seq 1 1 3` )
foreach x ( `seq 4 1 7` )
#foreach x ( `seq 8 1 11` )
#foreach x ( `seq 12 1 15` )
#foreach x ( `seq 16 1 19` )
#foreach x ( `seq 20 1 23` )
#foreach x ( `seq 24 1 27` )
#foreach x ( `seq 28 1 31` )
#foreach x ( `seq 32 1 35` )
#foreach x ( `seq 36 1 39` )
#foreach x ( `seq 40 1 43` )
#foreach x ( `seq 44 1 47` )
#foreach x ( `seq 48 1 51` )
#foreach x ( `seq 52 1 55` )
#foreach x ( `seq 56 1 59` )
#foreach x ( `seq 60 1 64` )
    cmsRun reco_RAW2DIGI_L1Reco_RECO_cosmics_allphi_$x.py > & "out_cosmics_allphi_"$x &
end 
