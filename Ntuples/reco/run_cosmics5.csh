#!/bin/tcsh                                                                                                                                                                                               
foreach x (cosmics_allphi_208593_5    cosmics_allphi_208593_6    cosmics_allphi_208593_7    cosmics_allphi_208593_8    cosmics_allphi_208593_9 )
    cmsRun reco_RAW2DIGI_L1Reco_RECO_$x.py  > & "out_"$x &
end         
