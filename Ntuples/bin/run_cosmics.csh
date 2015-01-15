#!/bin/tcsh
source cuts.csh
source cut_values.csh

#findTreevalues cosmics_allphi $cuts $cut_values > & "cosmics_allphi_"$cuts_ &
findTreevalues cosmicMC $cuts $cut_values > & "cosmicMC_"$cuts_ &


