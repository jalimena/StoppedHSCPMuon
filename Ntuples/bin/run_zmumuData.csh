#!/bin/tcsh
source cuts.csh
source cut_values.csh

findTreevalues Zmumu_Run2012A_723patch1 $cuts $cut_values > & "out_Zmumu_"$cuts_ &

