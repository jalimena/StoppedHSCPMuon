#!/bin/tcsh                                                                                                                                                                                               
foreach x (cosmics_allphi_208651_10   cosmics_allphi_208651_11   cosmics_allphi_208651_12   cosmics_allphi_208651_13   cosmics_allphi_208651_2 )
    cmsRun reco_RAW2DIGI_L1Reco_RECO_$x.py  > & "out_"$x &
end         
