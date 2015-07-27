#!/bin/tcsh
source setup.csh
source cuts.csh
source cut_values.csh

#foreach x (mchamp100_ABCDtree_723patch1 mchamp200_ABCDtree_723patch1 mchamp300_ABCDtree_723patch1 mchamp400_ABCDtree_723patch1 mchamp500_ABCDtree_723patch1 mchamp600_ABCDtree_723patch1 mchamp700_ABCDtree_723patch1 mchamp800_ABCDtree_723patch1 mchamp900_ABCDtree_723patch1 mchamp1000_ABCDtree_723patch1)
#foreach x (mchamp100_ABCDtree_723patch1 mchamp200_ABCDtree_723patch1 mchamp300_ABCDtree_723patch1 mchamp400_ABCDtree_723patch1 mchamp500_ABCDtree_723patch1)
#foreach x (mchamp600_ABCDtree_723patch1 mchamp700_ABCDtree_723patch1 mchamp800_ABCDtree_723patch1 mchamp900_ABCDtree_723patch1 mchamp1000_ABCDtree_723patch1)
#foreach x (mchamp100_ABCDtree_723patch1)
#foreach x (mchamp200_ABCDtree_723patch1)
#foreach x (mchamp300_ABCDtree_723patch1)
#foreach x (mchamp400_ABCDtree_723patch1 mchamp500_ABCDtree_723patch1 mchamp600_ABCDtree_723patch1)
#foreach x (mchamp700_ABCDtree_723patch1 mchamp800_ABCDtree_723patch1)
foreach x (mchamp900_ABCDtree_723patch1 mchamp1000_ABCDtree_723patch1)
    findTreevalues $x $cuts $cut_values > & "out_"$x &
end
  
