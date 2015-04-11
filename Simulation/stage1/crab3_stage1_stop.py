from CRABClient.UserUtilities import config
config = config()

if __name__ == '__main__':

    from CRABAPI.RawCommand import crabCommand
    from httplib import HTTPException

    # We want to put all the CRAB project directories from the tasks we submit here into one common directory.
    # That's why we need to set this parameter (here or above in the configuration file, it does not matter, we will not overwrite it).
    config.General.workArea = 'crab_projects'
    config.JobType.pluginName = 'PrivateMC'

    config.Data.splitting = 'EventBased'
    config.Data.unitsPerJob = 100
    NJOBS = 2000  # This is not a configuration parameter, but an auxiliary variable that we use in the next line.                                                                                              
    config.Data.totalUnits = config.Data.unitsPerJob * NJOBS
    config.Data.outLFN = '/store/user/jalimena' 
    config.Data.publication = True

    config.Site.storageSite = 'T3_US_Brown'

    def submit(config):
        try:
            crabCommand('submit', config = config)
        except HTTPException, hte:
            print hte.headers

    config.General.requestName = 'stage1_stop100_710'
    config.JobType.psetName = 'step1_stop100_cfg.py'
    config.Data.primaryDataset = 'HSCPstop_M-100_Tune4C_8TeV-pythia8'
    config.Data.publishDataName = 'stage1_stop100_710'
    submit(config)

    config.General.requestName = 'stage1_stop200_710'
    config.JobType.psetName = 'step1_stop200_cfg.py'
    config.Data.primaryDataset = 'HSCPstop_M-200_Tune4C_8TeV-pythia8'
    config.Data.publishDataName = 'stage1_stop200_710'
    submit(config)

    config.General.requestName = 'stage1_stop300_710'
    config.JobType.psetName = 'step1_stop300_cfg.py'
    config.Data.primaryDataset = 'HSCPstop_M-300_Tune4C_8TeV-pythia8'
    config.Data.publishDataName = 'stage1_stop300_710'
    submit(config)

    config.General.requestName = 'stage1_stop400_710'
    config.JobType.psetName = 'step1_stop400_cfg.py'
    config.Data.primaryDataset = 'HSCPstop_M-400_Tune4C_8TeV-pythia8'
    config.Data.publishDataName = 'stage1_stop400_710'
    submit(config)

    config.General.requestName = 'stage1_stop500_710'
    config.JobType.psetName = 'step1_stop500_cfg.py'
    config.Data.primaryDataset = 'HSCPstop_M-500_Tune4C_8TeV-pythia8'
    config.Data.publishDataName = 'stage1_stop500_710'
    submit(config)

    config.General.requestName = 'stage1_stop00_710'
    config.JobType.psetName = 'step1_stop00_cfg.py'
    config.Data.primaryDataset = 'HSCPstop_M-600_Tune4C_8TeV-pythia8'
    config.Data.publishDataName = 'stage1_stop00_710'
    submit(config)

    config.General.requestName = 'stage1_stop700_710'
    config.JobType.psetName = 'step1_stop700_cfg.py'
    config.Data.primaryDataset = 'HSCPstop_M-700_Tune4C_8TeV-pythia8'
    config.Data.publishDataName = 'stage1_stop700_710'
    submit(config)

    config.General.requestName = 'stage1_stop800_710'
    config.JobType.psetName = 'step1_stop800_cfg.py'
    config.Data.primaryDataset = 'HSCPstop_M-800_Tune4C_8TeV-pythia8'
    config.Data.publishDataName = 'stage1_stop800_710'
    submit(config)

    config.General.requestName = 'stage1_stop900_710'
    config.JobType.psetName = 'step1_stop900_cfg.py'
    config.Data.primaryDataset = 'HSCPstop_M-900_Tune4C_8TeV-pythia8'
    config.Data.publishDataName = 'stage1_stop900_710'
    submit(config)

    config.General.requestName = 'stage1_stop1000_710'
    config.JobType.psetName = 'step1_stop1000_cfg.py'
    config.Data.primaryDataset = 'HSCPstop_M-1000_Tune4C_8TeV-pythia8'
    config.Data.publishDataName = 'stage1_stop1000_710'
    submit(config)
