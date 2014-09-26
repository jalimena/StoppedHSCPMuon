#!/bin/tcsh                                                                                                                                                                                               
foreach x (cosmics_allphi_208593_14   cosmics_allphi_208593_15   cosmics_allphi_208593_16   cosmics_allphi_208593_17   cosmics_allphi_208593_18 )
    cmsRun reco_RAW2DIGI_L1Reco_RECO_$x.py  > & "out_"$x &
end         
