#!/bin/tcsh
source cuts.csh
source cut_values.csh

./findTreevalues_makehistos_Ntuples_allsamples NoBPTX_cosmics_allphi $cuts $cut_values > & "out_cosmicsallphi_"$cuts_ &
#./findTreevalues_makehistos_Ntuples_allsamples NoBPTX_cosmics_allphi $cuts $cut_values > & "out_cosmicsallphi_"$cuts_"atleast2SAs" &

