#!/bin/tcsh                                                                                                                                                                                               
foreach x (cosmics_allphi_208651_3    cosmics_allphi_208651_4    cosmics_allphi_208651_5    cosmics_allphi_208651_6    cosmics_allphi_208651_7 )
    cmsRun reco_RAW2DIGI_L1Reco_RECO_$x.py  > & "out_"$x &
end         
