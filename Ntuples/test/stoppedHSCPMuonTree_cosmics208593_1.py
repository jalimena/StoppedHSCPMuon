#
#  produce stopped HSCPMuon TTree
#  assumes RAW, HLT, RECO data present
#  Run this on StoppedHSCPMuon Skim
#
import FWCore.ParameterSet.Config as cms
import os, re
version = os.environ['CMSSW_VERSION']
                                        
#from StoppedHSCPMuon.Ntuples.stoppedHSCPMuonTree_MC_2012_cfg import *
from StoppedHSCPMuon.Ntuples.stoppedHSCPMuonTree_RECO_2012_cosmics208593_1_cfg import *

process.MessageLogger.cerr.INFO.limit = cms.untracked.int32(-1)
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(1)

# change Global Tag
#process.GlobalTag.globaltag = 'GR_P_V32::All'
#process.GlobalTag.globaltag = 'FT_53_V10_AN2::All' #for Run2012A,B July13_2012 rereco, Run2012C-v1 Aug24_2012 rereco (53X)
process.GlobalTag.globaltag = 'FT_53_V21_AN3::All' #for Run2012A,B,C,D Jan22_2013 rereco (53X)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10000) )

# input files
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
process.source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/190/456/5E1A8343-F380-E111-8FFD-003048D2BA82.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/190/456/A24CD3A0-0681-E111-AFE8-001D09F2AD4D.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/190/456/BA028006-F480-E111-BAA5-BCAEC5329727.root',
    
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/190/465/4EF8B039-0181-E111-98CC-003048F024DC.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/190/465/92040779-0281-E111-AE7F-BCAEC518FF40.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/190/465/E8032D7B-0281-E111-8B44-0015C5FDE067.root',

    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/04859027-1C88-E111-B1A2-BCAEC518FF67.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/04B48DA3-CE87-E111-B787-003048D2C01A.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/06EFAF4D-D987-E111-B276-001D09F29524.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/08F5C40B-EA87-E111-9C52-5404A63886A2.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/10B2858C-0688-E111-9E53-5404A63886BD.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/1A847CF4-1188-E111-94BE-001D09F28D54.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/1E1A3046-1888-E111-A6A7-BCAEC518FF8E.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/202145C2-0588-E111-8FBB-0030486780AC.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/222802CB-EB87-E111-B03F-002481E0D646.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/22F0F138-DA87-E111-95A0-001D09F2A690.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/24957545-1188-E111-8938-00237DDBE49C.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/265965C4-FF87-E111-9AC6-BCAEC5329700.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/280346E8-E087-E111-8FB8-5404A63886D6.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/28066F34-CD87-E111-B63D-003048D2BF1C.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/2A1A649B-FB87-E111-B63C-BCAEC532970F.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/2A2B9A43-0C88-E111-AE8E-0019B9F72D71.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/2E494DA1-1088-E111-A685-003048D37524.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/30D253D1-E587-E111-A273-0025B32034EA.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/321AB090-DF87-E111-BA97-5404A63886B9.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/342DEBC8-1F88-E111-99D2-0025901D625A.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/3E7085B6-F087-E111-848C-001D09F28EA3.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/405D695E-D587-E111-AB4E-5404A638868F.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/407350BF-D687-E111-9856-E0CB4E55365C.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/46440CB0-0C88-E111-9ADF-BCAEC53296FB.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/48B6DFC4-0588-E111-AC64-001D09F23C73.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/4C61278C-ED87-E111-8B23-0025901D62A0.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/522AD5E4-E087-E111-A0C1-5404A63886D4.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/56771E6B-CA87-E111-96F1-003048D3C90E.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/6028199D-D887-E111-9875-E0CB4E4408E3.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/627EA527-0A88-E111-A67B-BCAEC53296FB.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/62EA198C-0688-E111-8E92-5404A63886A5.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/62EB7C36-DA87-E111-B407-001D09F295FB.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/64D7886F-F287-E111-BA3E-BCAEC518FF68.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/6804CADA-0F88-E111-9726-003048D3751E.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/6A0D8ACA-EB87-E111-B460-00215AEDFD74.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/6AB35653-DC87-E111-AC05-003048678110.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/6C565368-F387-E111-B37F-0025901D5C80.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/6E3B525A-1B88-E111-A05F-0019B9F4A1D7.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/7827A72B-0488-E111-A981-BCAEC518FF80.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/7CC33674-0988-E111-9605-001D09F29597.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/7CF4A4E2-1488-E111-A8F7-001D09F28D4A.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/7E6437C5-0588-E111-80A4-001D09F28F25.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/7E83470F-D387-E111-854A-0025901D5D78.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/7EFEC135-DA87-E111-8C1F-BCAEC518FF76.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/823845DA-0F88-E111-B63B-003048D3C944.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/86AB8797-DF87-E111-9560-0025901D627C.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/86C0F40F-D687-E111-A149-001D09F24D8A.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/86D3D54A-F787-E111-8616-002481E0D73C.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/86EE80FD-E787-E111-8227-0025B32445E0.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/88FE99F3-1188-E111-A36F-0030486733B4.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/8E17B2CB-EE87-E111-AC0E-5404A63886B6.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/8E4CD2A7-F487-E111-B627-5404A63886B7.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/8EEA0994-E287-E111-9F94-5404A63886A0.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/90525F47-D987-E111-AE3B-5404A63886BB.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/96E1736B-CA87-E111-AB2D-0030486780EC.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/9837BC7F-E387-E111-A2EF-0025901D624E.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/9C92F898-0B88-E111-B745-5404A6388699.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/9EF4B1F2-0788-E111-90BC-003048D2BD66.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/A6C8639D-0B88-E111-A370-001D09F2B30B.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/A6FE6FFB-F787-E111-BD4F-003048D3756A.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/AC7F7563-F987-E111-83C2-0025901D6268.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/ACE20099-F887-E111-9E18-BCAEC5329709.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/ACEDCE11-0B88-E111-A4E7-001D09F290BF.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/AE4CA351-DC87-E111-868B-001D09F2960F.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/B40D9AE2-1488-E111-9048-001D09F2437B.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/BA81C5C1-D687-E111-8E6E-5404A63886C5.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/BAF0AF49-D287-E111-9FB2-003048D3C90E.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/C04A54C3-D687-E111-881D-BCAEC5329702.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/C0AAE27C-E387-E111-94EC-BCAEC5364C42.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/C6D63CC2-DA87-E111-9507-BCAEC5329709.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/C6F7E23A-D787-E111-A34F-5404A63886AE.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/C82AF6E9-1688-E111-A55A-BCAEC518FF52.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/CAFAE555-1B88-E111-94FA-001D09F24EE3.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/CC1484F1-0188-E111-B321-BCAEC53296F3.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/D06A475D-F187-E111-B10C-5404A638869E.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/D2CB1162-E787-E111-8478-0025901D5D90.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/D6D69A9E-DB87-E111-AC4B-BCAEC518FF76.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/DAAAAD71-0988-E111-ABCF-0019B9F4A1D7.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/DE5A0817-F687-E111-903B-001D09F2841C.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/E008424D-F487-E111-9707-001D09F248F8.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/E076794D-F487-E111-9DA9-001D09F2B2CF.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/E4638EF2-DF87-E111-B595-E0CB4E5536AE.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/E8E9E961-0388-E111-BA9C-5404A63886B6.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/EAF22770-F287-E111-9A1A-5404A638869E.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/FC44603B-2188-E111-8505-001D09F295FB.root',
    #'/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/191/226/FE158D53-0E88-E111-84C0-E0CB4E5536AE.root',

    #cosmic data
    #'/store/data/Run2012B/NoBPTX/RECO/PromptReco-v1/000/195/155/2E8E0BB2-C0AA-E111-8562-5404A638869B.root',
    #'/store/data/Run2012B/NoBPTX/RECO/PromptReco-v1/000/195/155/6C7AAC49-BDAA-E111-96C0-003048F117EA.root'
    'root://eoscms//eos/cms/store/user/jalimena/NoBPTX_Run2012D_cosmics_allphi_RECO/208593/46518E45-9840-E211-9BB3-E0CB4E4408E3.root'
    #'root://eoscms//eos/cms/store/user/jalimena/NoBPTX_Run2012D_cosmics_allphi_RECO/208651/4AAD6151-9540-E211-8551-0025B32035A2.root' #10.4GB
    #'root://eoscms//eos/cms/store/user/jalimena/NoBPTX_Run2012D_cosmics_allphi_RECO/208660/722C6988-9640-E211-966A-0025901D5D9A.root' #9.0GB

    #Run2012C, run 198230, all LS good
    #'rfio:/castor/cern.ch/cms/store/data/Run2012C/NoBPTX/RECO/PromptReco-v1/000/198/230/0AD096D0-A4C7-E111-A193-001D09F2447F.root',
    #'/store/data/Run2012C/NoBPTX/RECO/PromptReco-v1/000/198/230/A4D557CA-A4C7-E111-A8B8-0025B32034EA.root',
    #'rfio:/castor/cern.ch/cms/store/data/Run2012C/NoBPTX/RECO/PromptReco-v1/000/198/230/A8DABA86-9FC7-E111-ABF9-BCAEC53296F7.root'

    
    ] );
process.source.lumisToProcess = cms.untracked.VLuminosityBlockRange(
    '208593:1-208593:50'
    #'208593:51-208593:100'
    #'208593:101-208593:150'
    #'208593:151-208593:200'
    #'208593:201-208593:245'

    #'208651:1-208651:50'
    #'208651:51-208651:100'
    #'208651:101-208651:128'

    #'208660:1-208660:50'
    #'208660:51-208660:89'

    #'190456:1-190456:184',
    #'190465:68-190465:110'
    #'190465:1-190465:110'
    #'190465:122-190465:127'

    #'193834:1-194713:1' #Run2012B, HLT_L2Mu20_NoVertex_NoBPTX3BX_v1
    #'194735:1-197756:1' #Run2012B, HLT_L2Mu20_NoVertex_NoBPTX3BX_NoHalo_v3
    #'197770:1-200000:1' #Run2012B, HLT_L2Mu20_NoVertex_2Cha_NoBPTX3BX_NoHalo_v1, last run is filler number
    )



