from CRABClient.UserUtilities import config 
config = config()
#from CRABClient.client_utilities import getBasicConfig
#config = getBasicConfig()

config.General.requestName = ''
config.General.workArea = 'crab_projects'

config.JobType.pluginName = 'PrivateMC'
config.JobType.psetName = 'CosmicMCProduction_PPreco_Plus125_cfg.py'

config.Data.primaryDataset = 'Cosmics'
config.Data.splitting = 'EventBased'
config.Data.unitsPerJob = 100
NJOBS = 10000  # This is not a configuration parameter, but an auxiliary variable that we use in the next line.
config.Data.totalUnits = config.Data.unitsPerJob * NJOBS
config.Data.outLFN = '/store/user/jalimena'
config.Data.publication = True
config.Data.publishDataName = 'CosmicMC_PPreco_Plus125_RECO_723patch1'

config.Site.storageSite = 'T3_US_Brown'
