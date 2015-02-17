#!/bin/tcsh
source cuts.csh
source cut_values.csh

foreach x (ppstau100_gravitinop0001_723patch1 ppstau126_gravitinop0001_723patch1 ppstau156_gravitinop0001_723patch1 ppstau200_gravitinop0001_723patch1 ppstau247_gravitinop0001_723patch1 ppstau308_gravitinop0001_723patch1 ppstau370_gravitinop0001_723patch1 ppstau432_gravitinop0001_723patch1 ppstau494_gravitinop0001_723patch1)
#foreach x (ppstau494_gravitinop0001_723patch1)
    findTreevalues $x $cuts $cut_values > & "out_"$x &
end

