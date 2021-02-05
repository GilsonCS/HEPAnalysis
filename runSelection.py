#!/bin/bash
import os
import time
import sys
import argparse
  
  
#--------------------------------------------------------------------------------------------------------------------------------------------------
# Main Setup
#--------------------------------------------------------------------------------------------------------------------------------------------------
selection = "Example3"
outpath = "/eos/user/g/gcorreia/HEP_Project/CMS_LLGDV/OUTPUT"
treeName = "Events"
LumiWeights = 1

systematics = { 
"CV":             [0,   1],
#"Jets":           [1,   2],
"Luminosity":     [2,   2],
}

analysis_parameters = { 
"TRIGGER              ": 0,        # 0-Any,1-SR,2-CR     
"JET_ETA_CUT          ": 2.4,
"JET_PT_CUT           ": 30,       # GeV
"JET_ID               ": 1,        # 1-loose, 3-tight, 4-tightlepveto 
"MUON_PT_CUT          ": 10,       # GeV
"MUON_ISO             ": 0.2,     
"MUON_ID              ": 2,        # 2-medium, 3-tight
"ELECTRON_PT_CUT      ": 10,       # GeV
"ELECTRON_ISO         ": 0.1,     
"ELECTRON_ID          ": 2,        # 0-veto, 2-medium, 3-tight
"MET_CUT              ": 300,      # GeV
"MHT_CUT              ": 220,      # GeV
"HT_CUT               ": 300,      # GeV
"OMEGA_MIN_CUT        ": 0.4,  
"CorrectMC            ": 0,        # 0-No, 1-Yes 
"Track                ": 0,        # 0 -> Linear, 1 -> Curved
"ExtraVariables       ": 1,
"PileupWeights        ": 0,
}


Get_Image_in_EPS = 0
Get_Image_in_PNG = 1
Get_Image_in_PDF = 0


#--------------------------------------------------------------------------------------------------------------------------------------------------
# Jobs setup
#--------------------------------------------------------------------------------------------------------------------------------------------------
NumMaxEvents = -1
NumFilesPerJob = 99999999
#redirector = 'cmsxrootd.fnal.gov' # recommended in USA
redirector = 'xrootd-cms.infn.it' # recommended in Europe and Asia
#redirector = 'cms-xrd-global.cern.ch' # Global redirector


# If the resubmit list is not empty, only the jobs in this list will be processed!
resubmit = [
#[['TTTo2L2Nu_16', '160200', 'Datasets/Files/files_TTTo2L2Nu_xrootd.txt', 98], 89, 90, 0, 0], 
]

#--------------------------------------------------------------------------------------------------------------------------------------------------
# Dataset files
#--------------------------------------------------------------------------------------------------------------------------------------------------
sys.path.insert(0, 'Datasets')
from Signal import *
from Bkg import *
datasets = []

datasets.extend(Signal_16)
#datasets.extend(Bkg_16) 


#--------------------------------------------------------------------------------------------------------------------------------------------------
# [DO NOT TOUCH THIS PART] 
#-------------------------------------------------------------------------------------------------------------------------------------------------- 
parser = argparse.ArgumentParser()
parser.add_argument("-j", "--job", type=int, default=0)
parser.add_argument("-p", "--proxy", default="none")
parser.add_argument("-t", "--timer", type=int, default=1)
parser.add_argument("-c", "--check", type=bool, default=False)

args = parser.parse_args()
print('Job ID = ' + str(args.job))
print('Timer = ' + str(args.timer))
print('Proxy = ' + args.proxy)   
print('Check = ' + str(args.check))
print('')
if args.proxy != "none":
    os.environ["X509_USER_PROXY"] = args.proxy


#======CREATE LIST OF JOBS=========================================================================
SmallSample = False   # ~10% of the total [Do not change it!]
jobs = []
for dataset in datasets:
    NumFiles = dataset[3]
    if SmallSample :
        NumFiles = int(round(NumFiles/10.))
    Intervals = list(range(0,NumFiles,NumFilesPerJob))
    if NumFiles%NumFilesPerJob == 0:
        Intervals.append(Intervals[-1]+NumFilesPerJob)
    else:
        Intervals.append(Intervals[-1]+NumFiles%NumFilesPerJob)
    if NumMaxEvents > 0:
        Intervals = [Intervals[0], Intervals[1]]
    for i in range(len(Intervals)-1):
        for systematic in systematics.keys():
            jobs += [ [dataset, Intervals[i], Intervals[i+1], systematics[systematic][0], u] for u in range(systematics[systematic][1]) ]

if len(resubmit) > 0:
    jobs = resubmit


#======CASE SELECTION==============================================================================
if args.check:
    outpath = "Metadata"
    datasets = [["Signal_test_16", '160000', "Metadata/signal_nano.root", 0],]
    jobs = [[datasets[0], 0, 1, 0, 0]]
    N = 0
else:
    N = int(args.job)
    if N == -1:
        sys.exit("Number of jobs: " + str(len(jobs)))
    if N == -2:
        for i in range(len(jobs)):
            print(str(i)+"  "+str(jobs[i])+",")
        sys.exit("")
    if N <= -3:
        sys.exit(">> Enter an integer >= -2")
    if N >= len(jobs):
        sys.exit("There are only " + str(len(jobs)) + " jobs")


#======CREATE OUTPUT DIRECTORY FOR THE SELECTION AND MAKE A COPY OF THE cpp FILE THERE=============
if not os.path.exists(os.path.join(outpath, selection)):
    os.makedirs(os.path.join(outpath, selection))

    
#======WRITE INPUT FILE OF THE SELECTION===========================================================
ConfigFile = "Metadata/ConfigFile_" + jobs[N][0][0] + "_" + str(jobs[N][1]) + "_" + str(jobs[N][2]-1) + "_" + str(jobs[N][3]) + "_" + str(jobs[N][4]) + ".txt"
in_file = open(ConfigFile, "w")
in_file.write("Selection            " + selection                              + "\n")
in_file.write("Outpath              " + outpath                                + "\n")
in_file.write("InputTree            " + treeName                               + "\n")
in_file.write("DatasetName          " + jobs[N][0][0]                          + "\n")
in_file.write("Files                " + str(jobs[N][1])+"_"+str(jobs[N][2]-1)  + "\n")
in_file.write("DatasetID            " + jobs[N][0][1]                          + "\n")
in_file.write("NumMaxEvents         " + str(NumMaxEvents)                      + "\n")
in_file.write("Redirector           " + str(redirector)                        + "\n")
    
if args.check:
    in_file.write("Check                " + str(1)                             + "\n")
    in_file.write("InputFile            " + jobs[N][0][2]                      + "\n")
else:
    in_file.write("Check                " + str(0)                             + "\n")
    file_input = open(jobs[N][0][2], 'r')
    lines = file_input.readlines()
    lines = [x.strip() for x in lines]
    iline = 0
    for line in lines:
        if iline >= jobs[N][1] and iline < jobs[N][2]:
            in_file.write("InputFile            " + line                       + "\n")
        iline += 1

if( jobs[N][0][0][:4] == "Data" ):
    in_file.write("LumiWeights          " + str(0)                             + "\n")
    in_file.write("Universe             " + str(1)                             + "\n")
    in_file.write("SysID                " + str(0)                             + "\n")
else:
    in_file.write("LumiWeights          " + str(LumiWeights)                   + "\n")
    in_file.write("Universe             " + str(jobs[N][4])                    + "\n")
    in_file.write("SysID                " + str(jobs[N][3])                    + "\n")
    
in_file.write("PileupFileName       ./Configuration/PileupHistograms.root    " + "\n")
    
#-----METADATA------------------------------------------------------------------------
in_file.write("MCmetaFileName       ./Metadata/MC_Metadata.txt"                + "\n")
meta_file = open("Metadata/Data_Metadata.txt")
for line in meta_file:
    no, ID, data_scale, scale_unc = line.split()
    if( ID == jobs[N][0][1][0:2] ):
        in_file.write("DATA_LUMI            " + data_scale                     + "\n")
        data_scale_unc = float(data_scale)*float(scale_unc)*0.01
        in_file.write("DATA_LUMI_UNC        " + str(data_scale_unc)            + "\n")
#-------------------------------------------------------------------------------------
    
in_file.write("Show_Timer           "  + str(args.timer)                       + "\n")
in_file.write("Get_Image_in_EPS     "  + str(Get_Image_in_EPS)                 + "\n")
in_file.write("Get_Image_in_PNG     "  + str(Get_Image_in_PNG)                 + "\n")
in_file.write("Get_Image_in_PDF     "  + str(Get_Image_in_PDF)                 + "\n")
    
for cut, value in analysis_parameters.items():
    in_file.write( cut + str(value)                                            + "\n")
        
in_file.close()
        

#======RUN SELECTION===============================================================================
runCommand = './RunAnalysis ' + ConfigFile
os.system(runCommand)
    
    
#======REMOVE INPUT FILE OF THE SELECTION==========================================================
removeCommand = "rm " + ConfigFile
#os.system(removeCommand)

 
#======WRITE OUTPUT TXT FILE OF THE SELECTION======================================================
out_file = open(os.path.join(outpath, selection, jobs[N][0][0] + "_files_" + str(jobs[N][1]) + "_" + str(jobs[N][2]-1), "cutflow.txt"), "a")
for cut, value in analysis_parameters.items():
    out_file.write( cut + str(value)  + "\n")
out_file.write("-----------------------------------------------------------------------------------") 
out_file.close()


#======PRINT INFO OF THE SELECTION OVER THE DATASET================================================        
CutflowFile = os.path.join(outpath, selection, jobs[N][0][0] + "_files_" + str(jobs[N][1]) + "_" + str(jobs[N][2]-1), "cutflow.txt")
out = open(CutflowFile, "r")
for line in out:
    if( line.rstrip()[:4] == "Time" ):
        print(line.rstrip())
        print('-----------------------------------------------------------------------------------')
        print(' ')
        break
    else:
        print(line.rstrip())
out.close()


