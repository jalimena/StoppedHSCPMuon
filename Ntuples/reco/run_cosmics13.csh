#!/bin/tcsh                                                                                                                                                                                               
foreach x (cosmics_allphi_208666_2  cosmics_allphi_208666_3  )
    cmsRun reco_RAW2DIGI_L1Reco_RECO_$x.py  > & "out_"$x &
end         
