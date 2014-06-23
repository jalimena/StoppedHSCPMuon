#!/bin/tcsh
source cuts.csh
source cut_values.csh

./findTreevalues_makehistos_Ntuples_allsamples Zmumu_Run2012B $cuts $cut_values > & "out_Zmumu_Run2012B_"$cuts_"_forceMuons" &

