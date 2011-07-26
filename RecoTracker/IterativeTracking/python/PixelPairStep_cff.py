import FWCore.ParameterSet.Config as cms


# NEW CLUSTERS (remove previously used clusters)
pixelPairStepClusters = cms.EDProducer("TrackClusterRemover",
    clusterLessSolution = cms.bool(True),
    oldClusterRemovalInfo = cms.InputTag("lowPtTripletStepClusters"),
    trajectories = cms.InputTag("lowPtTripletStepTracks"),
    overrideTrkQuals = cms.InputTag('lowPtTripletStepSelector','lowPtTripletStep'),
    TrackQuality = cms.string('highPurity'),
    pixelClusters = cms.InputTag("siPixelClusters"),
    stripClusters = cms.InputTag("siStripClusters"),
    Common = cms.PSet(
        maxChi2 = cms.double(30.0)
    )
)

# SEEDING LAYERS
pixelPairStepSeedLayers = cms.ESProducer("SeedingLayersESProducer",
    ComponentName = cms.string('pixelPairStepSeedLayers'),
    layerList = cms.vstring('BPix1+BPix2', 'BPix1+BPix3', 'BPix2+BPix3', 
        'BPix1+FPix1_pos', 'BPix1+FPix1_neg', 
        'BPix1+FPix2_pos', 'BPix1+FPix2_neg', 
        'BPix2+FPix1_pos', 'BPix2+FPix1_neg', 
        'BPix2+FPix2_pos', 'BPix2+FPix2_neg', 
        'FPix1_pos+FPix2_pos', 'FPix1_neg+FPix2_neg'),
    BPix = cms.PSet(
        useErrorsFromParam = cms.bool(True),
        hitErrorRPhi = cms.double(0.0027),
        hitErrorRZ = cms.double(0.006),
        TTRHBuilder = cms.string('TTRHBuilderWithoutAngle4PixelPairs'),
        HitProducer = cms.string('siPixelRecHits'),
        skipClusters = cms.InputTag('pixelPairStepClusters')
    ),
    FPix = cms.PSet(
        useErrorsFromParam = cms.bool(True),
        hitErrorRPhi = cms.double(0.0051),
        hitErrorRZ = cms.double(0.0036),
        TTRHBuilder = cms.string('TTRHBuilderWithoutAngle4PixelPairs'),
        HitProducer = cms.string('siPixelRecHits'),
        skipClusters = cms.InputTag('pixelPairStepClusters')
    )
)

# SEEDS
import RecoTracker.TkSeedGenerator.GlobalSeedsFromPairsWithVertices_cff
pixelPairStepSeeds = RecoTracker.TkSeedGenerator.GlobalSeedsFromPairsWithVertices_cff.globalSeedsFromPairsWithVertices.clone()
pixelPairStepSeeds.RegionFactoryPSet.RegionPSet.ptMin = 0.6
pixelPairStepSeeds.RegionFactoryPSet.RegionPSet.originRadius = 0.01
pixelPairStepSeeds.RegionFactoryPSet.RegionPSet.fixedError = 0.03
pixelPairStepSeeds.OrderedHitsFactoryPSet.SeedingLayers = cms.string('pixelPairStepSeedLayers')
pixelPairStepSeeds.ClusterCheckPSet.PixelClusterCollectionLabel = 'siPixelClusters'
pixelPairStepSeeds.ClusterCheckPSet.ClusterCollectionLabel = 'siStripClusters'


# TRACKER DATA CONTROL
import RecoTracker.MeasurementDet.MeasurementTrackerESProducer_cfi
pixelPairStepMeasurementTracker = RecoTracker.MeasurementDet.MeasurementTrackerESProducer_cfi.MeasurementTracker.clone(
    ComponentName = 'pixelPairStepMeasurementTracker',
    pixelClusterProducer = 'siPixelClusters',
    stripClusterProducer = 'siStripClusters',
    skipClusters = cms.InputTag('pixelPairStepClusters')
    )

# QUALITY CUTS DURING TRACK BUILDING
import TrackingTools.TrajectoryFiltering.TrajectoryFilterESProducer_cfi
pixelPairStepTrajectoryFilter = TrackingTools.TrajectoryFiltering.TrajectoryFilterESProducer_cfi.trajectoryFilterESProducer.clone(
    ComponentName = 'pixelPairStepTrajectoryFilter',
    filterPset = TrackingTools.TrajectoryFiltering.TrajectoryFilterESProducer_cfi.trajectoryFilterESProducer.filterPset.clone(
    minimumNumberOfHits = 3,
    minPt = 0.1
    )
    )

# TRACK BUILDING
import RecoTracker.CkfPattern.GroupedCkfTrajectoryBuilderESProducer_cfi
pixelPairStepTrajectoryBuilder = RecoTracker.CkfPattern.GroupedCkfTrajectoryBuilderESProducer_cfi.GroupedCkfTrajectoryBuilder.clone(
    ComponentName = 'pixelPairStepTrajectoryBuilder',
    MeasurementTrackerName = '',
    trajectoryFilterName = 'pixelPairStepTrajectoryFilter',
    clustersToSkip = cms.InputTag('pixelPairStepClusters')
    )

# MAKING OF TRACK CANDIDATES
import RecoTracker.CkfPattern.CkfTrackCandidates_cfi
pixelPairStepTrackCandidates = RecoTracker.CkfPattern.CkfTrackCandidates_cfi.ckfTrackCandidates.clone(
    src = cms.InputTag('pixelPairStepSeeds'),
    TrajectoryBuilder = 'pixelPairStepTrajectoryBuilder'
    )


# TRACK FITTING
import RecoTracker.TrackProducer.TrackProducer_cfi
pixelPairStepTracks = RecoTracker.TrackProducer.TrackProducer_cfi.TrackProducer.clone(
    AlgorithmName = cms.string('iter2'),
    src = 'pixelPairStepTrackCandidates'
    )

# Final selection
import RecoTracker.FinalTrackSelectors.multiTrackSelector_cfi
pixelPairStepSelector = RecoTracker.FinalTrackSelectors.multiTrackSelector_cfi.multiTrackSelector.clone(
    src='pixelPairStepTracks',
    trackSelectors= cms.VPSet(
        RecoTracker.FinalTrackSelectors.multiTrackSelector_cfi.looseMTS.clone(
            name = 'pixelPairStepLoose',
            ), #end of pset
        RecoTracker.FinalTrackSelectors.multiTrackSelector_cfi.tightMTS.clone(
            name = 'pixelPairStepTight',
            preFilterName = 'pixelPairStepLoose',
            ),
        RecoTracker.FinalTrackSelectors.multiTrackSelector_cfi.highpurityMTS.clone(
            name = 'pixelPairStep',
            preFilterName = 'pixelPairStepTight',
            ),
        ) #end of vpset
    ) #end of clone

# Final sequence
PixelPairStep = cms.Sequence(pixelPairStepClusters*
                         pixelPairStepSeeds*
                         pixelPairStepTrackCandidates*
                         pixelPairStepTracks*
                         pixelPairStepSelector)