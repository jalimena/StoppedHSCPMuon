#!/bin/tcsh
source setup.csh
source cuts.csh
source cut_values.csh

#foreach x (doublyChargedHiggs500 tauPrime500)
foreach x (doublyChargedHiggs200 tauPrime200)
    findTreevalues $x $cuts $cut_values > & "out_"$x &
end
