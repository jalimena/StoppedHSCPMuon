#!/bin/tcsh                                                                                                                                                                                               
foreach x (cosmics_allphi_208628_1    cosmics_allphi_208635_1    cosmics_allphi_208636_1    cosmics_allphi_208636_2    cosmics_allphi_208651_1 )
    cmsRun reco_RAW2DIGI_L1Reco_RECO_$x.py  > & "out_"$x &
end         
