#!/bin/tcsh                                                                                                                                                                                               
foreach x (cosmics_allphi_208593_23   cosmics_allphi_208593_24   cosmics_allphi_208593_25   cosmics_allphi_208593_3    cosmics_allphi_208593_4 )
    cmsRun reco_RAW2DIGI_L1Reco_RECO_$x.py  > & "out_"$x &
end         
