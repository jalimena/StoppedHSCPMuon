#!/bin/tcsh
source setup.csh
source cuts.csh
source cut_values.csh

foreach x (ABCDtree_data_Run2012BCD_723patch1)
    findTreevalues $x $cuts $cut_values > & "out_"$x &
end
