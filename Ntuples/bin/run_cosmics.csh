#!/bin/tcsh
source cuts.csh
source cut_values.csh

#findTreevalues NoBPTX_Run2012D_JetTriggers_723patch1_globalMuMatching $cuts $cut_values > & "out_JetTriggers" &

#findTreevalues cosmics_allphi_NoBPTX_Run2012D_723patch1_SingleMuOpen $cuts $cut_values > & "out_cosmics_allphi" &
#findTreevalues cosmics_allphi_NoBPTX_Run2012D_723patch1_globalMuMatching $cuts $cut_values > & "out_cosmics_allphi" &
#findTreevalues cosmicMC_Plus125_take2_updatedSim_globalMuMatching $cuts $cut_values > & "out_cosmicMC_Plus125" &

findTreevalues cosmics_allphi_NoBPTX_Run2012D_723patch1 $cuts $cut_values > & "out_cosmics_allphi" &
findTreevalues cosmicMC_Plus125_take2_updatedSim $cuts $cut_values > & "out_cosmicMC_Plus125" &

#findTreevalues cosmicMC $cuts $cut_values > & "out_cosmicMC" &
#findTreevalues cosmicMC_defaultTiming $cuts $cut_values > & "out_cosmicMC_defaultTiming" &
#findTreevalues cosmicMC_Plus25 $cuts $cut_values > & "out_cosmicMC_Plus25" &




