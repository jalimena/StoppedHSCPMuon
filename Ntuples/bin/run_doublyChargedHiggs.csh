#!/bin/tcsh
source setup.csh
source cuts.csh
source cut_values.csh

foreach x (doublyChargedHiggs500 tauPrime500)
    findTreevalues $x $cuts $cut_values > & "out_"$x &
end
