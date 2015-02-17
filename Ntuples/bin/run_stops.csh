#!/bin/tcsh
source setup.csh
source cuts.csh
source cut_values.csh

foreach x (stop100_neutralino30_723patch1 stop200_neutralino75_723patch1 stop300_neutralino109_723patch1 stop400_neutralino214_723patch1 stop500_neutralino316_723patch1 stop600_neutralino417_723patch1 stop700_neutralino518_723patch1 stop800_neutralino618_723patch1 stop900_neutralino718_723patch1 stop1000_neutralino819_723patch1)
#foreach x (stop500_neutralino316_723patch1)
    findTreevalues $x $cuts $cut_values > & "out_"$x &
end
