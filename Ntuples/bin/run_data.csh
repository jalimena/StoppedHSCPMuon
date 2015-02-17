#!/bin/tcsh
source setup.csh
source cuts.csh
source cut_values.csh

#foreach x (SingleMu_Run2012A_723patch1)
foreach x (SingleMu_Run2012A_723patch1 NoBPTX_Run2012B_period1_723patch1 NoBPTX_Run2012B_period2_723patch1 NoBPTX_Run2012C_723patch1 NoBPTX_Run2012D_723patch1)
#foreach x (NoBPTX_Run2012C_ControlTriggers_723patch1)
#foreach x (NoBPTX_Run2012D_723patch1)
#foreach x (NoBPTX_Run2012D_JetTriggers_723patch1)
    findTreevalues $x $cuts $cut_values > & "out_"$x &
end
