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

    config.General.requestName = 'stage1_mchamp100_710'
    config.JobType.psetName = 'step1_mchamp100_cfg.py'
    config.Data.primaryDataset = 'HSCPmchamp6_M-100_TuneZ2star_8TeV-pythia6'
    config.Data.publishDataName = 'stage1_mchamp100_710'
    submit(config)

    config.General.requestName = 'stage1_mchamp200_710'
    config.JobType.psetName = 'step1_mchamp200_cfg.py'
    config.Data.primaryDataset = 'HSCPmchamp6_M-200_TuneZ2star_8TeV-pythia6'
    config.Data.publishDataName = 'stage1_mchamp200_710'
    submit(config)

    config.General.requestName = 'stage1_mchamp300_710'
    config.JobType.psetName = 'step1_mchamp300_cfg.py'
    config.Data.primaryDataset = 'HSCPmchamp6_M-300_TuneZ2star_8TeV-pythia6'
    config.Data.publishDataName = 'stage1_mchamp300_710'
    submit(config)

    config.General.requestName = 'stage1_mchamp400_710'
    config.JobType.psetName = 'step1_mchamp400_cfg.py'
    config.Data.primaryDataset = 'HSCPmchamp6_M-400_TuneZ2star_8TeV-pythia6'
    config.Data.publishDataName = 'stage1_mchamp400_710'
    submit(config)

    config.General.requestName = 'stage1_mchamp500_710'
    config.JobType.psetName = 'step1_mchamp500_cfg.py'
    config.Data.primaryDataset = 'HSCPmchamp6_M-500_TuneZ2star_8TeV-pythia6'
    config.Data.publishDataName = 'stage1_mchamp500_710'
    submit(config)

    config.General.requestName = 'stage1_mchamp600_710'
    config.JobType.psetName = 'step1_mchamp600_cfg.py'
    config.Data.primaryDataset = 'HSCPmchamp6_M-600_TuneZ2star_8TeV-pythia6'
    config.Data.publishDataName = 'stage1_mchamp600_710'
    submit(config)

    config.General.requestName = 'stage1_mchamp700_710'
    config.JobType.psetName = 'step1_mchamp700_cfg.py'
    config.Data.primaryDataset = 'HSCPmchamp6_M-700_TuneZ2star_8TeV-pythia6'
    config.Data.publishDataName = 'stage1_mchamp700_710'
    submit(config)

    config.General.requestName = 'stage1_mchamp800_710'
    config.JobType.psetName = 'step1_mchamp800_cfg.py'
    config.Data.primaryDataset = 'HSCPmchamp6_M-800_TuneZ2star_8TeV-pythia6'
    config.Data.publishDataName = 'stage1_mchamp800_710'
    submit(config)

    config.General.requestName = 'stage1_mchamp900_710'
    config.JobType.psetName = 'step1_mchamp900_cfg.py'
    config.Data.primaryDataset = 'HSCPmchamp6_M-900_TuneZ2star_8TeV-pythia6'
    config.Data.publishDataName = 'stage1_mchamp900_710'
    submit(config)

    config.General.requestName = 'stage1_mchamp1000_710'
    config.JobType.psetName = 'step1_mchamp1000_cfg.py'
    config.Data.primaryDataset = 'HSCPmchamp6_M-1000_TuneZ2star_8TeV-pythia6'
    config.Data.publishDataName = 'stage1_mchamp1000_710'
    submit(config)
