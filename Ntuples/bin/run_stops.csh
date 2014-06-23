#!/bin/tcsh
source cuts.csh
source cut_values.csh

foreach x (stop200_neutralino75 stop300_neutralino109 stop400_neutralino214 stop500_neutralino316 stop600_neutralino417 stop700_neutralino518 stop800_neutralino618 stop900_neutralino718 stop1000_neutralino819)
    ./findTreevalues_makehistos_Ntuples_allsamples $x $cuts $cut_values > & "out_"$x"_"$cuts_ &
end
