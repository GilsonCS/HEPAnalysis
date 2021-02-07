# HEPAnalysis
**Analysis code for the DESY-CBPF-UERJ collaboration**

Quick start
-----------

Inisde your private area in lxplus (NOT in the EOS area and not necessarily inside a CMSSW release), download the code.  
`git clone https://github.com/DESY-CBPF-UERJ/HEPAnalysis.git`

Enter in the HEPAnalysis directory:  
`cd HEPAnalysis`

Get the proxy:  
`voms-proxy-init --voms cms`

Set up your information:  
* Modify the file **runSelection.py**. You need to change the `outpath` variable that indicates where will be stored the outputs. Here, I recommend you use a directory in your EOS area (CERNBOX).  
* Modify the file **submit_grid.sh**. You need to change the `Username` variable.

Compile the code:  
`make --always-make`

Run the code on a test dataset:  
`python runSelection.py -c 1`

Know how many jobs the code is setted to process:  
`python runSelection.py -j -1`

Produce a list of all jobs the code is setted to process:  
`python runSelection.py -j -2`

Run the job in the position **n** of the list:  
`python runSelection.py -j n`

Submit condor jobs:  
1. Make **submit_grid.sh** an executable:  
`chmod +x submit_grid.sh`   
2. See all flavours available for the jobs:  
`./submit_grid.sh help`  
3. Submit all the **N** jobs the code is setted to process (need to provide the proxy):  
`./submit_grid.sh flavour N`
    

Working with anaFiles
---------------------

Create a template for a new anaFile called **TrigEff** and integrate it to the framework:  
`./addSelection.sh TrigEff`

Dissociate **TrigEff** from the framework (the anaFile is not deleted):  
`./removeSelection.sh TrigEff`



