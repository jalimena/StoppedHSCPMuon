#!/bin/tcsh

foreach x (mchamp100 mchamp200 mchamp300 mchamp400 mchamp500 mchamp600 mchamp700 mchamp800 mchamp900 mchamp1000)
    ./$x"_pt35/toymc/job43/job43.sh" > & $x"_pt35_job43.log" &
    ./$x"_pt40/toymc/job43/job43.sh" > & $x"_pt40_job43.log" &
    ./$x"_pt45/toymc/job43/job43.sh" > & $x"_pt45_job43.log" &
    ./$x"_pt50/toymc/job43/job43.sh" > & $x"_pt50_job43.log" &
    ./$x"_pt60/toymc/job43/job43.sh" > & $x"_pt60_job43.log" &
    ./$x"_pt80/toymc/job43/job43.sh" > & $x"_pt80_job43.log" &
    ./$x"_pt100/toymc/job43/job43.sh" > & $x"_pt100_job43.log" &
    ./$x"_pt150/toymc/job43/job43.sh" > & $x"_pt150_job43.log" &
    ./$x"_pt200/toymc/job43/job43.sh" > & $x"_pt200_job43.log" &
end

