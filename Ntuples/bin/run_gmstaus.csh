#!/bin/tcsh
source cuts.csh
source cut_values.csh

#foreach x (gmstau100_gravitinop0001_reducedNtuples_724 gmstau126_gravitinop0001_reducedNtuples_724 gmstau156_gravitinop0001_reducedNtuples_724)
#foreach x (gmstau200_gravitinop0001_reducedNtuples_724 gmstau247_gravitinop0001_reducedNtuples_724 gmstau308_gravitinop0001_reducedNtuples_724)
foreach x (gmstau370_gravitinop0001_reducedNtuples_724 gmstau432_gravitinop0001_reducedNtuples_724 gmstau494_gravitinop0001_reducedNtuples_724)
    findTreevalues $x $cuts $cut_values > & "out_"$x &
end
