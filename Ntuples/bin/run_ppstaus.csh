#!/bin/tcsh
source cuts.csh
source cut_values.csh

#foreach x (ppstau100_gravitinop0001 ppstau126_gravitinop0001 ppstau156_gravitinop0001 ppstau200_gravitinop0001 ppstau247_gravitinop0001 ppstau308_gravitinop0001 ppstau370_gravitinop0001 ppstau432_gravitinop0001 ppstau494_gravitinop0001)
foreach x (ppstau494_gravitinop0001_723patch1)
    findTreevalues $x $cuts $cut_values > & "out_"$x"_"$cuts_ &
end

