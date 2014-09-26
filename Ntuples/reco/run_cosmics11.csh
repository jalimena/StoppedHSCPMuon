#!/bin/tcsh                                                                                                                                                                                               
foreach x (cosmics_allphi_208660_5  cosmics_allphi_208660_6  cosmics_allphi_208660_7  cosmics_allphi_208660_8  cosmics_allphi_208660_9 )
    cmsRun reco_RAW2DIGI_L1Reco_RECO_$x.py  > & "out_"$x &
end         
