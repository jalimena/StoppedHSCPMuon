#!/bin/tcsh
source setup.csh
source cuts.csh
source cut_values.csh

#foreach x (stop100_neutralino30_reducedNtuples_724 stop200_neutralino75_reducedNtuples_724 stop300_neutralino109_reducedNtuples_724)
#foreach x (stop400_neutralino214_reducedNtuples_724 stop500_neutralino316_reducedNtuples_724 stop600_neutralino417_reducedNtuples_724)
#foreach x (stop700_neutralino518_reducedNtuples_724 stop800_neutralino618_reducedNtuples_724)
#foreach x (stop900_neutralino718_reducedNtuples_724 stop1000_neutralino819_reducedNtuples_724)

foreach x (stop100_neutralino30_reducedNtuples_724 stop500_neutralino316_reducedNtuples_724 stop1000_neutralino819_reducedNtuples_724)
    findTreevalues $x $cuts $cut_values > & "out_"$x &
end
