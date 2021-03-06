#!/bin/tcsh
source cuts.csh
source cut_values.csh

#foreach x (ppstau100_gravitinop0001_reducedNtuples_724 ppstau126_gravitinop0001_reducedNtuples_724 ppstau156_gravitinop0001_reducedNtuples_724)
#foreach x (ppstau200_gravitinop0001_reducedNtuples_724 ppstau247_gravitinop0001_reducedNtuples_724 ppstau308_gravitinop0001_reducedNtuples_724)
foreach x (ppstau370_gravitinop0001_reducedNtuples_724 ppstau432_gravitinop0001_reducedNtuples_724 ppstau494_gravitinop0001_reducedNtuples_724)
    findTreevalues $x $cuts $cut_values > & "out_"$x &
end

