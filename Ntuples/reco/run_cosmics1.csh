#!/bin/tcsh                                                                                                                                                                                               
foreach x (cosmics_allphi_208593_1 cosmics_allphi_208593_10   cosmics_allphi_208593_11   cosmics_allphi_208593_12   cosmics_allphi_208593_13 )
#foreach x (cosmics_allphi_208593_14   cosmics_allphi_208593_15   cosmics_allphi_208593_16   cosmics_allphi_208593_17   cosmics_allphi_208593_18 )
#foreach x (cosmics_allphi_208593_19   cosmics_allphi_208593_2    cosmics_allphi_208593_20   cosmics_allphi_208593_21   cosmics_allphi_208593_22 )
#foreach x (cosmics_allphi_208593_23   cosmics_allphi_208593_24   cosmics_allphi_208593_25   cosmics_allphi_208593_3    cosmics_allphi_208593_4 )
#foreach x (cosmics_allphi_208593_5    cosmics_allphi_208593_6    cosmics_allphi_208593_7    cosmics_allphi_208593_8    cosmics_allphi_208593_9 )
#foreach x (cosmics_allphi_208628_1    cosmics_allphi_208635_1    cosmics_allphi_208636_1    cosmics_allphi_208636_2    cosmics_allphi_208651_1 )
#foreach x (cosmics_allphi_208651_10   cosmics_allphi_208651_11   cosmics_allphi_208651_12   cosmics_allphi_208651_13   cosmics_allphi_208651_2 )
#foreach x (cosmics_allphi_208651_3    cosmics_allphi_208651_4    cosmics_allphi_208651_5    cosmics_allphi_208651_6    cosmics_allphi_208651_7 )
#foreach x (cosmics_allphi_208651_8  cosmics_allphi_208651_9  cosmics_allphi_208655_1  cosmics_allphi_208655_2  cosmics_allphi_208655_3 )
#foreach x (cosmics_allphi_208655_4  cosmics_allphi_208660_1  cosmics_allphi_208660_2  cosmics_allphi_208660_3  cosmics_allphi_208660_4 )
#foreach x (cosmics_allphi_208660_5  cosmics_allphi_208660_6  cosmics_allphi_208660_7  cosmics_allphi_208660_8  cosmics_allphi_208660_9 )
#foreach x (cosmics_allphi_208663_1  cosmics_allphi_208663_2  cosmics_allphi_208663_3  cosmics_allphi_208664_1  cosmics_allphi_208666_1 )
#foreach x (cosmics_allphi_208666_2  cosmics_allphi_208666_3  )
    cmsRun reco_RAW2DIGI_L1Reco_RECO_$x.py  > & "out_"$x &
end         
