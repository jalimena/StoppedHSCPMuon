#!/bin/tcsh
source cuts.csh
source cut_values.csh

findTreevalues NoBPTX_Run2012D_cosmics_allphi $cuts $cut_values > & "cosmics_allphi_"$cuts_ &
findTreevalues cosmicMC $cuts $cut_values > & "cosmicMC_"$cuts_ &


