#!/bin/tcsh
source setup.csh
source cuts.csh
source cut_values.csh

    #tcsh
    #pwd > tmp
    #sed -i 's:src::2' tmp
    #echo $SCRAM_ARCH
    #awk -v scram_arch="$SCRAM_ARCH" '{print "setenv PATH2 \"" $0 "bin/" scram_arch "\""}' tmp > tmp2
    #chmod +x tmp2
    #./tmp2
    #alias findTreevalues2 "$PATH2/findTreevalues"
    #rm tmp
    #rm tmp2

#foreach x (mchamp100_reducedNtuples_724 mchamp200_reducedNtuples_724 mchamp300_reducedNtuples_724 mchamp400_reducedNtuples_724 mchamp500_reducedNtuples_724 mchamp600_reducedNtuples_724 mchamp700_reducedNtuples_724 mchamp800_reducedNtuples_724 mchamp900_reducedNtuples_724 mchamp1000_reducedNtuples_724)
#foreach x (mchamp100_separateEvents_725_updatedSim mchamp200_separateEvents_725_updatedSim mchamp300_separateEvents_725_updatedSim mchamp400_separateEvents_725_updatedSim mchamp500_separateEvents_725_updatedSim mchamp600_separateEvents_725_updatedSim mchamp700_separateEvents_725_updatedSim mchamp800_separateEvents_725_updatedSim mchamp900_separateEvents_725_updatedSim mchamp1000_separateEvents_725_updatedSim)
#foreach x (mchamp100_separateEvents_725_updatedSim mchamp500_separateEvents_725_updatedSim mchamp1000_separateEvents_725_updatedSim)
#foreach x (mchamp500_separateEvents_725_updatedSim)
foreach x (mchamp500_separateEvents_725_updatedSim_fixedMatching)
#foreach x (mchamp100_separateEvents_725_updatedSim)
#foreach x (mchamp500_723patch1)
#foreach x (mchamp500)
    findTreevalues $x $cuts $cut_values > & "out_"$x &
end
   
#findTreevalues cosmicRecoTestmchamp500 $cuts $cut_values > & "cosTestmchamp500_"$cuts_ &

    #./findTreevalues_makehistos_Ntuples_allsamples mchamp500_l1muons $cuts $cut_values > & "out_mchamp500l1_"$cuts_ &
    #./findTreevalues_makehistos_Ntuples_allsamples mchamp100_changeCosmicPt $cuts $cut_values > & "out_mchamp100co_"$cuts_ &
    #./findTreevalues_makehistos_Ntuples_allsamples mchamp1000_changeCosmicPt $cuts $cut_values > & "out_mchamp1000co_"$cuts_ &
    #findTreevalues mchamp500_710pre7_PRESTA71V3 $cuts $cut_values > & "out_mchamp500_"$cuts_ &
    #findTreevalues mchamp500_710pre7_PRESTA71V3_cosSeedSAreco $cuts $cut_values > & "out_mchamp500cs_"$cuts_ &
    #findTreevalues mchamp500_710pre7_PRESTA71V3_cosSeedSAreco_SATrajectory $cuts $cut_values > & "out_mchamp500SA_"$cuts_ &
    #findTreevalues mchamp500_710pre7_PRESTA71V3_cosSeedSAreco_Exhaustive $cuts $cut_values > & "out_mchamp500Exh_"$cuts_ &
    #findTreevalues mchamp500_720pre3_START72V1_cosSeedSAreco_SATrajectory $cuts $cut_values > & "out_mchamp500SA_"$cuts_ &
    #findTreevalues mchamp500_720pre3_START72V1_cosSeedSAreco_Exhaustive $cuts $cut_values > & "out_mchamp500Exh_"$cuts_ &
    #findTreevalues mchamp500_l1muons $cuts $cut_values > & "out_mchamp500old_"$cuts_ &

    #findTreevalues mchamp500_720pre6_PRESTA72V4 $cuts $cut_values > & "out_mchamp500_"$cuts_ &
