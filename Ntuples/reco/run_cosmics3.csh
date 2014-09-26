#!/bin/tcsh                                                                                                                                                                                               
foreach x (cosmics_allphi_208593_19   cosmics_allphi_208593_2    cosmics_allphi_208593_20   cosmics_allphi_208593_21   cosmics_allphi_208593_22 )
    cmsRun reco_RAW2DIGI_L1Reco_RECO_$x.py  > & "out_"$x &
end         
