#!/bin/bash

N_datasets=$2
Username=gcorreia
flavor=\"$1\"

if [ "$1" == "help" ]
then
    echo "command: ./submit_grid.sh Flavour NumberOfJobs" 
    echo "Options for Flavour (maximum time to complete all jobs):"
    echo "espresso     = 20 minutes"
    echo "microcentury = 1 hour"
    echo "longlunch    = 2 hours"
    echo "workday      = 8 hours"
    echo "tomorrow     = 1 day"
    echo "testmatch    = 3 days"
    echo "nextweek     = 1 week"
else
    #==================================================================================================
    Proxy_file=/afs/cern.ch/work/${Username:0:1}/${Username}/private/x509up
    voms-proxy-init --voms cms
    cp /tmp/x509up_u$(id -u) ${Proxy_file}
    sed -i "s/.*queue.*/queue ${N_datasets}/" HTCondor/condor.sub
    sed -i "s~.*Proxy_path            =.*~Proxy_path            = ${Proxy_file}~" HTCondor/condor.sub
    sed -i "s~.*arguments.*~arguments             = \$(ProcId) \$(Proxy_path) $(pwd)~" HTCondor/condor.sub
    sed -i "s/.*+JobFlavour.*/+JobFlavour = ${flavor}/" HTCondor/condor.sub

    cd HTCondor
    condor_submit condor.sub
fi
