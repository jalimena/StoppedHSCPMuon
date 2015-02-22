from CRABClient.UserUtilities import config
config = config()

config.General.requestName = 'Ntuples_mchamp500_5326'
config.General.workArea = 'crab_projects'

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'stoppedHSCPMuonTree_MC.py'

config.Data.inputDataset = '/HSCPmchamp6_M-500_TuneZ2star_8TeV-pythia6/Summer12-START52_V9-v5/GEN-SIM'
config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 500
config.Data.outLFN = '/store/user/jalimena' 
config.Data.publication = True
config.Data.publishDataName = 'Ntuples_mchamp500_5326'

config.Site.storageSite = 'T3_US_Brown'
