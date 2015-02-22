#!/bin/tcsh

set BxCut = wBxCut
set CavCut = wCavCut
#set GenMuCut = wGenMuCut 
set GenMuCut = woGenMuCut 
#set SACut = wSACut 
set SACut = woSACut 
set GenMuMatchedCut = woGenMuMatchedCut 
#set GenMuMatchedCut = wGenMuMatchedCut 
#set TriggerCut = wTriggerCut 
set TriggerCut = woTriggerCut 
#set TriggerTurnOn = wTriggerTurnOn 
set TriggerTurnOn = woTriggerTurnOn 
#set PtCut = wPtCut 
set PtCut = woPtCut 
#set ChaCut = wChaCut 
set ChaCut = woChaCut 
#set EtaCut = wEtaCut 
set EtaCut = woEtaCut 
set UpperCut = woUpperCut 
#set UpperCut = wUpperCut 
#set RpcCut = wRpcCut 
set RpcCut = woRpcCut 
#set DisStCut = wDisStCut 
set DisStCut = woDisStCut 
set RpcBxCut = woRpcBxCut
#set RpcBxCut = wRpcBxCut
#set DtHitsCut = wDtHitsCut 
set DtHitsCut = woDtHitsCut 
#set InvBetaErrCut = wInvBetaErrCut 
set InvBetaErrCut = woInvBetaErrCut 
#set CscHitsCut = wCscHitsCut 
set CscHitsCut = woCscHitsCut 
#set DtInvBetaCut = wDtInvBetaCut 
set DtInvBetaCut = woDtInvBetaCut 
#set TimeInOutCut = wTimeInOutCut
set TimeInOutCut = woTimeInOutCut
#set TofDirCut = wTofDirCut
set TofDirCut = woTofDirCut
#set OppEtaCut = wOppEtaCut 
set OppEtaCut = woOppEtaCut 
#set OppPhiCut = wOppPhiCut 
set OppPhiCut = woOppPhiCut 
set ChargeCut = woChargeCut
#set ChargeCut = wChargeCut
set TightPhi = woTightPhi
#set CosEnrich = wCosEnrich
set CosEnrich = woCosEnrich
#set resT3 = res
set resT3 = T3
set Printout = woPrintout
#set Printout = wPrintout

if ($Printout == "woPrintout") then
    set cuts_ = $BxCut"_"$CavCut"_"$GenMuCut"_"$SACut"_"$GenMuMatchedCut"_"$TriggerCut"_"$PtCut"_"$ChaCut"_"$EtaCut"_"$UpperCut"_"$RpcCut"_"$DisStCut"_"$RpcBxCut"_"$DtHitsCut"_"$InvBetaErrCut"_"$CscHitsCut"_"$DtInvBetaCut"_"$TimeInOutCut"_"$TofDirCut"_"$OppEtaCut"_"$OppPhiCut"_"$ChargeCut"_"$TightPhi"_"$CosEnrich
else
    set cuts_ = $Printout    
endif

set cuts = "$BxCut $CavCut $GenMuCut $SACut $GenMuMatchedCut $TriggerCut $TriggerTurnOn $PtCut $ChaCut $EtaCut $UpperCut $RpcCut $DisStCut $RpcBxCut $DtHitsCut $InvBetaErrCut $CscHitsCut $DtInvBetaCut $TimeInOutCut $TofDirCut $OppEtaCut $OppPhiCut $ChargeCut $TightPhi $CosEnrich $resT3 $Printout"

