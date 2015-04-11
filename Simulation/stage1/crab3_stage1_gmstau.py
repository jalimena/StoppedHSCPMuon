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
    NJOBS = 1000  # This is not a configuration parameter, but an auxiliary variable that we use in the next line.                                                                                              
    config.Data.totalUnits = config.Data.unitsPerJob * NJOBS
    config.Data.outLFN = '/store/user/jalimena' 
    config.Data.publication = True

    config.Site.storageSite = 'T3_US_Brown'

    def submit(config):
        try:
            crabCommand('submit', config = config)
        except HTTPException, hte:
            print hte.headers

    config.General.requestName = 'stage1_gmstau100_710'
    config.JobType.psetName = 'step1_gmstau100_cfg.py'
    config.Data.primaryDataset = 'HSCPgmstau_M-100_TuneZ2star_8TeV-pythia6'
    config.Data.publishDataName = 'stage1_gmstau100_710'
    submit(config)

    config.General.requestName = 'stage1_gmstau126_710'
    config.JobType.psetName = 'step1_gmstau126_cfg.py'
    config.Data.primaryDataset = 'HSCPgmstau_M-126_TuneZ2star_8TeV-pythia6'
    config.Data.publishDataName = 'stage1_gmstau126_710'
    submit(config)

    config.General.requestName = 'stage1_gmstau156_710'
    config.JobType.psetName = 'step1_gmstau156_cfg.py'
    config.Data.primaryDataset = 'HSCPgmstau_M-156_TuneZ2star_8TeV-pythia6'
    config.Data.publishDataName = 'stage1_gmstau156_710'
    submit(config)

    config.General.requestName = 'stage1_gmstau200_710'
    config.JobType.psetName = 'step1_gmstau200_cfg.py'
    config.Data.primaryDataset = 'HSCPgmstau_M-200_TuneZ2star_8TeV-pythia6'
    config.Data.publishDataName = 'stage1_gmstau200_710'
    submit(config)

    config.General.requestName = 'stage1_gmstau247_710'
    config.JobType.psetName = 'step1_gmstau247_cfg.py'
    config.Data.primaryDataset = 'HSCPgmstau_M-247_TuneZ2star_8TeV-pythia6'
    config.Data.publishDataName = 'stage1_gmstau247_710'
    submit(config)

    config.General.requestName = 'stage1_gmstau308_710'
    config.JobType.psetName = 'step1_gmstau308_cfg.py'
    config.Data.primaryDataset = 'HSCPgmstau_M-308_TuneZ2star_8TeV-pythia6'
    config.Data.publishDataName = 'stage1_gmstau308_710'
    submit(config)

    config.General.requestName = 'stage1_gmstau370_710'
    config.JobType.psetName = 'step1_gmstau370_cfg.py'
    config.Data.primaryDataset = 'HSCPgmstau_M-370_TuneZ2star_8TeV-pythia6'
    config.Data.publishDataName = 'stage1_gmstau370_710'
    submit(config)

    config.General.requestName = 'stage1_gmstau432_710'
    config.JobType.psetName = 'step1_gmstau432_cfg.py'
    config.Data.primaryDataset = 'HSCPgmstau_M-432_TuneZ2star_8TeV-pythia6'
    config.Data.publishDataName = 'stage1_gmstau432_710'
    submit(config)

    config.General.requestName = 'stage1_gmstau494_710'
    config.JobType.psetName = 'step1_gmstau494_cfg.py'
    config.Data.primaryDataset = 'HSCPgmstau_M-494_TuneZ2star_8TeV-pythia6'
    config.Data.publishDataName = 'stage1_gmstau494_710'
    submit(config)

