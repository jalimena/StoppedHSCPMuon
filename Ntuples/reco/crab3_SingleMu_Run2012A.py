from CRABClient.client_utilities import getBasicConfig
config = getBasicConfig()

config.General.requestName = 'Reco_SingleMu_Run2012A_723patch1'
config.General.workArea = 'crab_projects'

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'reco_RAW2DIGI_L1Reco_RECO.py'

config.Data.inputDataset = '/SingleMu/Run2012A-v1/RAW'
config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 20
config.Data.lumiMask = '../data/Cert_190456-208686_8TeV_22Jan2013ReReco_Collisions12_JSON_MuonPhys_Run2012A.txt'
#config.Data.runRange = '193093-193999' # '193093-194075'
config.Data.outLFN = '/store/user/jalimena' 
config.Data.publication = True
config.Data.publishDataName = 'Reco_SingleMu_Run2012A_723patch1'

config.Site.storageSite = 'T3_US_Brown'
