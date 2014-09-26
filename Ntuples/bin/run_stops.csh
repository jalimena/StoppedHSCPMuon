#!/bin/tcsh
source setup.csh
source cuts.csh
source cut_values.csh

#foreach x (stop200_neutralino75 stop300_neutralino109 stop400_neutralino214 stop500_neutralino316 stop600_neutralino417 stop700_neutralino518 stop800_neutralino618 stop900_neutralino718 stop1000_neutralino819)
#foreach x (stop500_neutralino316_720pre4_START72V1_cosSeedSAreco_SATrajectory)
foreach x (stop500_neutralino316_720pre6_PRESTA72V4)
    findTreevalues $x $cuts $cut_values > & "out_stop500_"$cuts_ &
end
