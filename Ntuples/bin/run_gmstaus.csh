#!/bin/tcsh
source cuts.csh
source cut_values.csh

foreach x (gmstau100_gravitinop0001 gmstau126_gravitinop0001 gmstau156_gravitinop0001 gmstau200_gravitinop0001 gmstau247_gravitinop0001 gmstau308_gravitinop0001 gmstau370_gravitinop0001 gmstau432_gravitinop0001 gmstau494_gravitinop0001)
    ./findTreevalues_makehistos_Ntuples_allsamples $x $cuts $cut_values > & "out_"$x"_"$cuts_ &
end
