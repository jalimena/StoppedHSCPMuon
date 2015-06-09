#!/bin/tcsh
source setup.csh
source cuts.csh
source cut_values.csh

#foreach x (doublyChargedHiggs500 tauPrime500)
#foreach x (doublyChargedHiggs200 tauPrime200)
#foreach x (doublyChargedHiggs500_5326 tauPrime500_724)
#foreach x (doublyChargedHiggs110_5326 doublyChargedHiggs200_5326 doublyChargedHiggs300_5326 doublyChargedHiggs400_5326 doublyChargedHiggs500_5326 doublyChargedHiggs600_5326 doublyChargedHiggs700_5326 doublyChargedHiggs800_5326 doublyChargedHiggs900_5326 doublyChargedHiggs1000_5326)
#foreach x (tauPrime100_724 tauPrime200_724 tauPrime300_724 tauPrime400_724 tauPrime500_724 tauPrime600_724 tauPrime700_724 tauPrime800_724 tauPrime900_724 tauPrime1000_724 )
foreach x (tauPrime500_724)
    findTreevalues $x $cuts $cut_values > & "out_"$x &
end
