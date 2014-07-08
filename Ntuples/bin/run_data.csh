#!/bin/tcsh
source setup.csh
source cuts.csh
source cut_values.csh

#foreach x (SingleMu_Run2012A NoBPTX_Run2012B_period1 NoBPTX_Run2012B_period2 NoBPTX_Run2012C NoBPTX_Run2012D)
foreach x (NoBPTX_Run2012D_ControlTriggers NoBPTX_Run2012D_JetTriggers)
    #./findTreevalues_makehistos_Ntuples_allsamples $x $cuts $cut_values > & "out_"$x"_"$cuts_ &
    findTreevalues $x $cuts $cut_values > & "out_"$x &
end
