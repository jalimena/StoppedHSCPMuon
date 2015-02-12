#!/bin/tcsh
source cuts.csh
source cut_values.csh

findTreevalues NoBPTX_Run2012D_cosmics_allphi_723patch1 $cuts $cut_values > & "cosmics_allphi_"$cuts_ &
findTreevalues cosmicMC $cuts $cut_values > & "cosmicMC_"$cuts_ &
findTreevalues cosmicMC_defaultTiming $cuts $cut_values > & "cosmicMC_defaultTiming_"$cuts_ &
findTreevalues cosmicMC_Plus125 $cuts $cut_values > & "cosmicMC_Plus125_"$cuts_ &
findTreevalues cosmicMC_Plus25 $cuts $cut_values > & "cosmicMC_Plus25_"$cuts_ &




