#!/bin/tcsh                                                                                                                                                                                               
foreach x (cosmics_allphi_208655_4  cosmics_allphi_208660_1  cosmics_allphi_208660_2  cosmics_allphi_208660_3  cosmics_allphi_208660_4 )
    cmsRun reco_RAW2DIGI_L1Reco_RECO_$x.py  > & "out_"$x &
end         
