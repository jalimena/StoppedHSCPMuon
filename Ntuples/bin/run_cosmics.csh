#!/bin/tcsh
source cuts.csh
source cut_values.csh

findTreevalues NoBPTX_Run2012D_cosmics_allphi_723patch1 $cuts $cut_values > & "out_cosmics_allphi" &
#findTreevalues cosmicMC $cuts $cut_values > & "out_cosmicMC" &
#findTreevalues cosmicMC_defaultTiming $cuts $cut_values > & "out_cosmicMC_defaultTiming" &
findTreevalues cosmicMC_Plus125_take2 $cuts $cut_values > & "out_cosmicMC_Plus125_take2" &
#findTreevalues cosmicMC_Plus25 $cuts $cut_values > & "out_cosmicMC_Plus25" &




