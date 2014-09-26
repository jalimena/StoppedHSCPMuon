#!/bin/tcsh                                                                                                                                                                                               
foreach x (cosmics_allphi_208663_1  cosmics_allphi_208663_2  cosmics_allphi_208663_3  cosmics_allphi_208664_1  cosmics_allphi_208666_1 )
    cmsRun reco_RAW2DIGI_L1Reco_RECO_$x.py  > & "out_"$x &
end         
