#!/bin/tcsh
source setup.csh

foreach x (mchamp100_separateEvents_725 mchamp200_separateEvents_725 mchamp300_separateEvents_725 mchamp400_separateEvents_725 mchamp500_separateEvents_725 mchamp600_separateEvents_725 mchamp700_separateEvents_725 mchamp800_separateEvents_725 mchamp900_separateEvents_725 mchamp1000_separateEvents_725)
    duplicateEvents $x > & "out_duplicateEvents_"$x &
end
