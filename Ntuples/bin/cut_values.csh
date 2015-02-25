#!/bin/tcsh

set BxCutValue = 2

set PrePtCutValue = 10.
set PreChaCutValue = 1
#set PreChaCutValue = 2
set PreEtaCutValue = 1.0
#set PreRpcCutValue = 0
set PreRpcCutValue = 1
#set PreRpcCutValue = 2
#set PreRpcCutValue = 3
#set PreDtHitsCutValue = 0
#set PreDtHitsCutValue = 8
set PreDtHitsCutValue = 7
#set PreDtHitsCutValue = 0
set PreInvBetaErrCutValue = 10.
set PreCscHitsCutValue = 0

#set PtCutValue = 10.
#set ChaCutValue = 1
#set EtaCutValue = 1.0
#set RpcCutValue = 1



#set PtCutValue = 20.
set PtCutValue = 30.
set ChaCutValue = 2
#set ChaCutValue = 3
#set EtaCutValue = 1.0
#set RpcCutValue = 0
#set RpcCutValue = 1
set RpcCutValue = 2
#set RpcCutValue = 3
#set RpcCutValue = 4
#set RpcCutValue = 5
#set DisStCutValue = 1
set DisStCutValue = 2
set DtHitsCutValue = 7
#set DtHitsCutValue = 0
set CscHitsCutValue = 0
set DtInvBetaCutValue = 0.2
#set DtInvBetaCutValue = 0.0
#set TimeInOutCutValue = 0.
set TimeInOutCutValue = -20.
set OppEtaCutValue = 0.1
#set OppEtaCutValue = 0.6
set OppPhiCutValue = 0.1
#set OppPhiCutValue = 0.5
#set OppPhiCutValue = 1.0
#set OppPhiCutValue = 2.0
#set OppPhiCutValue = 3.0

set cut_values = "$BxCutValue $PrePtCutValue $PreChaCutValue $PreEtaCutValue $PreRpcCutValue $PreDtHitsCutValue $PreInvBetaErrCutValue $PreCscHitsCutValue $PtCutValue $ChaCutValue $EtaCutValue $RpcCutValue $DisStCutValue $DtHitsCutValue $CscHitsCutValue $DtInvBetaCutValue $TimeInOutCutValue $OppEtaCutValue $OppPhiCutValue"
