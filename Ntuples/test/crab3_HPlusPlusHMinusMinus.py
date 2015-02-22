from CRABClient.UserUtilities import config
config = config()

config.General.requestName = 'Ntuples_HPlusPlusHMinus500_5326'
config.General.workArea = 'crab_projects'

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'stoppedHSCPMuonTree_MC.py'

config.Data.inputDataset = '/HPlusPlusHMinusMinusHTo4L_M-500_8TeV-pythia6/Summer12_DR53X-PU_S10_START53_V7C-v1/AODSIM'
config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 500
config.Data.outLFN = '/store/user/jalimena' 
config.Data.publication = True
config.Data.publishDataName = 'Ntuples_HPlusPlusHMinus500_5326'

config.Site.storageSite = 'T3_US_Brown'
