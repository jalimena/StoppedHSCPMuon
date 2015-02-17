#!/bin/tcsh
source setup.csh
source cuts.csh
source cut_values.csh


foreach x (mchampPlus100_723patch1 mchampPlus200_723patch1 mchampPlus300_723patch1 mchampPlus400_723patch1 mchampPlus500_723patch1 mchampPlus600_723patch1 mchampPlus700_723patch1 mchampPlus800_723patch1 mchampPlus900_723patch1 mchampPlus1000_723patch1)
#foreach x (mchampPlus100_723patch1 mchampPlus500_723patch1 mchampPlus1000_723patch1)
    findTreevalues $x $cuts $cut_values > & "out_"$x &
end
   
