import FWCore.ParameterSet.Config as cms

from RecoLocalMuon.DTSegment.dt4DSegments_MTPatternReco4D_LinearDriftFromDBLoose_cfi import *
dt4DSegmentsMT = dt4DSegments.clone()
dt4DSegmentsMT.Reco4DAlgoConfig.Reco2DAlgoConfig.AlphaMaxPhi = 1.0
dt4DSegmentsMT.Reco4DAlgoConfig.Reco2DAlgoConfig.AlphaMaxTheta = 0.9
dt4DSegmentsMT.Reco4DAlgoConfig.Reco2DAlgoConfig.segmCleanerMode = 2
dt4DSegmentsMT.Reco4DAlgoConfig.Reco2DAlgoConfig.MaxChi2 = 1.0
dt4DSegmentsMT.Reco4DAlgoConfig.recAlgoConfig.stepTwoFromDigi = True
dt4DSegmentsMT.Reco4DAlgoConfig.Reco2DAlgoConfig.recAlgoConfig.stepTwoFromDigi = True
dt4DSegmentsMT.Reco4DAlgoConfig.Reco2DAlgoConfig.perform_delta_rejecting = cms.bool(True)
dt4DSegmentsMT.Reco4DAlgoConfig.perform_delta_rejecting = cms.bool(True)

#from RecoMuon.MuonIdentification.muontiming_cfi import *
from RecoMuon.MuonIdentification.muonTimingDelayedMuons_cfi import *
muontimingDelayedMuons.MuonCollection = cms.InputTag("muons")
muontimingDelayedMuons.TimingFillerParameters.UseECAL=False
muontimingDelayedMuons.TimingFillerParameters.DTTimingParameters.MatchParameters.DTsegments = "dt4DSegmentsMT"
muontimingDelayedMuons.TimingFillerParameters.DTTimingParameters.HitsMin = 3
muontimingDelayedMuons.TimingFillerParameters.DTTimingParameters.RequireBothProjections = False
muontimingDelayedMuons.TimingFillerParameters.DTTimingParameters.DropTheta = True
muontimingDelayedMuons.TimingFillerParameters.DTTimingParameters.DoWireCorr = True
muontimingDelayedMuons.TimingFillerParameters.DTTimingParameters.MatchParameters.DTradius = 1.0
muontimingDelayedMuons.TimingFillerParameters.DTTimingParameters.HitErrorPhi = 3.
muontimingDelayedMuons.TimingFillerParameters.DTTimingParameters.HitErrorTheta = 6.
muontimingDelayedMuons.TimingFillerParameters.DTTimingParameters.PruneCut = 20.
muontimingDelayedMuons.TimingFillerParameters.DTTimingParameters.debug = False
