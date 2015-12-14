#!/bin/tcsh
source setup.csh
source cuts.csh
source cut_values.csh

#foreach x (ABCDtree_2DSAdata_Run2012BCD_pRpcBx)
foreach x (ABCDtree_1DSAdata_Run2012BCD_pRpcBx)
#foreach x (ABCDtree_2DSAdata_Run2012BCD_723patch1)
#foreach x (ABCDtree_1DSAdata_Run2012BCD_723patch1)
#foreach x (ABCDtree_2DSAdata_Run2012BCD_mchamp100_723patch1)
    findTreevalues $x $cuts $cut_values > & "out_"$x &
end
