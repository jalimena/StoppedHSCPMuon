#!/bin/tcsh                                                                                                                                                                                               
foreach x (cosmics_allphi_208651_8  cosmics_allphi_208651_9  cosmics_allphi_208655_1  cosmics_allphi_208655_2  cosmics_allphi_208655_3 )
    cmsRun reco_RAW2DIGI_L1Reco_RECO_$x.py  > & "out_"$x &
end         
