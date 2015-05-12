#!/bin/tcsh
# to run use source *.csh

#echo gluinos...
#foreach i (300 400 500 600 700 800 900 1000 1100 1200 1300 1400 1500)
#    if ($i == '300') then 
#	set j=173
#    endif
#    if ($i == '400') then 
#	set j=283
#    endif
#    if ($i == '500') then 
#	set j=387
#    endif
#    if ($i == '600') then 
#	set j=490
#    endif
#    if ($i == '700') then 
#	set j=592
#    endif
#    if ($i == '800') then 
#	set j=693
#    endif
#    if ($i == '900') then 
#	set j=794
#    endif
#    if ($i == '1000') then 
#	set j=894
#    endif
#    if ($i == '1100') then 
#	set j=995
#    endif
#    if ($i == '1200') then 
#	set j=1095
#    endif
#    if ($i == '1300') then 
#	set j=1196
#    endif
#    if ($i == '1400') then 
#	set j=1296
#    endif
#    if ($i == '1500') then 
#	set j=1396
#    endif
#    sed "s/XXX/$i/" stoppedHSCPMuon_stage2HLT_gluinoXXX_neutralinoYYY_cfg.py |sed "s/YYY/$j/" > stoppedHSCPMuon_stage2HLT_gluino${i}_neutralino${j}_cfg.py
#end

#echo stops...
#foreach i (100 200 300 400 500 600 700 800 900 1000)
#    if ($i == '100') then 
#	set j=30
#    endif
#    if ($i == '200') then 
#	set j=75
#    endif
#    if ($i == '300') then 
#	set j=109
#    endif
#    if ($i == '400') then 
#	set j=214
#    endif
#    if ($i == '500') then 
#	set j=316
    #endif
    #if ($i == '600') then 
#	set j=417
    #endif
    #if ($i == '700') then 
#	set j=518
    #endif
    #if ($i == '800') then 
#	set j=618
    #endif
    #if ($i == '900') then 
#	set j=718
    #endif
    #if ($i == '1000') then 
	#set j=819
    #endif
    #sed "s/XXX/$i/" stoppedHSCPMuon_stage2HLT_stopXXX_neutralinoYYY_cfg.py |sed "s/YYY/$j/" > stoppedHSCPMuon_stage2HLT_stop${i}_neutralino${j}_cfg.py
#end

#echo staus... 
#foreach i (100 126 156 200 247 308 370 432 494)
    #sed "s/XXX/$i/" stoppedHSCPMuon_stage2HLT_ppstauXXX_gravitinop0001_cfg.py > stoppedHSCPMuon_stage2HLT_ppstau${i}_gravitinop0001_cfg.py
    #sed "s/XXX/$i/" stoppedHSCPMuon_stage2HLT_gmstauXXX_gravitinop0001_cfg.py > stoppedHSCPMuon_stage2HLT_gmstau${i}_gravitinop0001_cfg.py
#end


echo mchamps...
foreach i (100 200 300 400 500 600 700 800 900 1000)
    #sed "s/XXX/$i/" stoppedHSCPMuon_stage2HLT_mchampXXX_cfg.py > stoppedHSCPMuon_stage2HLT_mchamp${i}_cfg.py
    sed "s/XXX/$i/" stoppedHSCPMuon_stage2HLT_mchampXXX_sameEvent_cfg.py > stoppedHSCPMuon_stage2HLT_mchamp${i}_sameEvent_cfg.py
    sed "s/XXX/$i/" stoppedHSCPMuon_stage2HLT_mchampXXX_separateEvents_particle0_cfg.py > stoppedHSCPMuon_stage2HLT_mchamp${i}_separateEvents_particle0_cfg.py
    sed "s/XXX/$i/" stoppedHSCPMuon_stage2HLT_mchampXXX_separateEvents_particle1_cfg.py > stoppedHSCPMuon_stage2HLT_mchamp${i}_separateEvents_particle1_cfg.py
end



#echo mchamps...
#foreach i (100 200 300 400 500 600 700 800 900 1000)
#   foreach j in 3 6
#   sed "s/XXX/$i/" HSCPhipYYY_M_XXX_13TeV_pythia6_cff.py |sed "s/YYY/$j/" > result_new/HSCPmchamp${j}_M_${i}_TuneZ2star_13TeV_pythia6_cff.py
#   sed "s/XXX/$i/" particles_HIPYYY_stau_XXX_GeV.txt |sed "s/YYY/$j/"> result_new/particles_HIP${j}_stau_${i}_GeV.txt
#   sed "s/XXX/$i/" hscppythiapdtHIPYYYstauXXX.tbl |sed "s/YYY/$j/"> result_new/hscppythiapdtHIP${j}stau${i}.tbl    
#   end 	
#end


#let "j = $i/10"
#sed "s/XX/$j/" hscppythiapdtgluinoXXX.tbl > result_new/hscppythiapdtgluino${i}.tbl


echo "job is finished at" 
date

