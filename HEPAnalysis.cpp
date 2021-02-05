#include "HEPAnalysis.h"

//---------------------------------------------------------------------------------------------------------------
// Initiator
//---------------------------------------------------------------------------------------------------------------
HEPAnalysis* HEPAnalysis::GetInstance( char *configFileName ) {
    if( !_instance ) {
        _instance = new HEPAnalysis( configFileName );
    }
    return _instance;
}

HEPAnalysis *HEPAnalysis::_instance = 0;

//---------------------------------------------------------------------------------------------------------------
// Constructor
//---------------------------------------------------------------------------------------------------------------
HEPAnalysis::HEPAnalysis( char *configFileName ) {
    
    //======START TIME=============================================================================
    _begin = time(NULL);
    

    //======READ THE CONTROL VARIABLES FROM THE TEXT FILE==========================================
    ifstream configFile( configFileName, ios::in );
    while( configFile.good() ) {
        string key, value;
        configFile >> key >> ws >> value;
        if( configFile.eof() ) break;
        if( key == "Selection"          )   _SELECTION = value;
        if( key == "Outpath"            )   _outputDirectory = value;
        if( key == "InputFile"          )   _inputFileNames.push_back( value ); 
        if( key == "InputTree"          )   _inputTreeName = value; 
        if( key == "DatasetName"        )   _datasetName = value;
        if( key == "Files"              )   _Files = value;
        if( key == "DatasetID"          )   _DatasetID = atoi(value.c_str());
        if( key == "LumiWeights"        )   _applyEventWeights = ( atoi(value.c_str()) == 1 );
        if( key == "Universe"           )   _Universe = atoi(value.c_str());
        if( key == "SysID"              )   _sysID = atoi(value.c_str());
        if( key == "Show_Timer"         )   _Show_Timer = (bool)(atoi(value.c_str()));
        if( key == "Get_Image_in_EPS"   )   _Get_Image_in_EPS = (bool)(atoi(value.c_str()));
        if( key == "Get_Image_in_PNG"   )   _Get_Image_in_PNG = (bool)(atoi(value.c_str()));
        if( key == "Get_Image_in_PDF"   )   _Get_Image_in_PDF = (bool)(atoi(value.c_str()));
        if( key == "Check"              )   _check = (bool)(atoi(value.c_str()));
        if( key == "NumMaxEvents"       )   _NumMaxEvents = atoi(value.c_str());
        if( key == "Redirector"         )   _Redirector = value;
        
        if( key == "MCmetaFileName"     )   _MCmetaFileName = value;
        if( key == "DATA_LUMI"          )   DATA_LUMI = atof(value.c_str());
        if( key == "DATA_LUMI_UNC"      )   DATA_LUMI_UNC = atof(value.c_str());
        
        if( key == "ApplyPileupWeights" )   applyPileupWeights = ( atoi(value.c_str()) == 1 );
        if( key == "PileupFileName"     )   PUFILE = value;
        
        if( key == "TRIGGER"            )   TRIGGER = atoi(value.c_str());
        if( key == "JET_ETA_CUT"        )   JET_ETA_CUT = atof(value.c_str());
        if( key == "JET_PT_CUT"         )   JET_PT_CUT = atof(value.c_str());
        if( key == "JET_ID"             )   JET_ID = atoi(value.c_str());
        if( key == "MUON_PT_CUT"        )   MUON_PT_CUT = atof(value.c_str()); 
        if( key == "MUON_ISO"           )   MUON_ISO = atof(value.c_str()); 
        if( key == "MUON_ID"            )   MUON_ID = atoi(value.c_str()); 
        if( key == "ELECTRON_PT_CUT"    )   ELECTRON_PT_CUT = atof(value.c_str()); 
        if( key == "ELECTRON_ISO"       )   ELECTRON_ISO = atof(value.c_str()); 
        if( key == "ELECTRON_ID"        )   ELECTRON_ID = atoi(value.c_str()); 
        if( key == "JET_PT_CUT_SV"      )   JET_PT_CUT_SV = atof(value.c_str());
        if( key == "JET_PT_CUT_PV"      )   JET_PT_CUT_PV = atof(value.c_str());
        if( key == "SUBJET_PT_CUT_PV"   )   SUBJET_PT_CUT_PV = atof(value.c_str());
        if( key == "MJJ_CUT"            )   MJJ_CUT = atof(value.c_str());
        if( key == "LEADING_SV_JET_CUT" )   LEADING_SV_JET_CUT = atof(value.c_str());
        if( key == "MET_CUT"            )   MET_CUT = atof(value.c_str()); 
        if( key == "MHT_CUT"            )   MHT_CUT = atof(value.c_str());
        if( key == "HT_CUT"             )   HT_CUT = atof(value.c_str());
        if( key == "OMEGA_MIN_CUT"      )   OMEGA_MIN_CUT = atof(value.c_str());
        
        if( key == "Track"              )   Track = atoi(value.c_str());
        if( key == "ExtraVariables"     )   ExtraVariables = (bool)(atoi(value.c_str()));
        if( key == "CorrectMC"          )   CorrectMC = (bool)(atoi(value.c_str()));
    }
    
    
    //======CREATE OUTPUT DIRECTORY FOR THE DATASET================================================    
    _outputDirectory = _outputDirectory + "/" + _SELECTION + "/" + _datasetName + "_files_" + _Files + "/";
    mkdir(_outputDirectory.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    string sysDirectory = _outputDirectory + "/Systematics"; 
    mkdir(sysDirectory.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        
    //======ADD THE INPUT TREES TO THE TCHAINS=====================================================
    gErrorIgnoreLevel = kError;
    _inputTree = new TChain(_inputTreeName.c_str());
    for( vector<string>::iterator itr = _inputFileNames.begin(); itr != _inputFileNames.end(); ++itr ) {
        string inputFileName = "root://" + _Redirector + "//" + (*itr);
        if( _check || (_datasetName.substr(0,6) == "Signal") ) inputFileName = (*itr);
        _inputTree -> Add( inputFileName.c_str() ); 
    }
    
        
    //======CREATE OUTPUT FILE AND TREE============================================================
    if( _sysID == 0 ) {
        _outputFileName = _outputDirectory + "/Tree.root";
        _outputFile = new TFile( _outputFileName.c_str(), "RECREATE" );
    }
    _outputTree = new TTree( "selection", "selection" );
    
    
    //======CREATE SYSTEMATIC FILE AND TREE========================================================
    _sysFileName = sysDirectory + "/" + to_string(_sysID) + "_" + to_string(_Universe) + ".root";
    _sysFile = new TFile( _sysFileName.c_str(), "RECREATE" );
    _sysFileName = sysDirectory + "/" + to_string(_sysID) + "_" + to_string(_Universe) + ".txt";
    _sysFileTxt.open( _sysFileName.c_str(), ios::out );
    
       
    
    //======PROCESS METADATA AND GET THE DATA SCALE WEIGHT=========================================
    //_metaTree->SetBranchAddress("SumOfWeights", &_SumOfWeights );
    //double nEffEventsProcessed=0;
    //for( int i = 0; i < _metaTree -> GetEntries(); ++i ) {
    //    _metaTree->GetEntry(i);
    //    nEffEventsProcessed += 999;
    //}
    //PROC_NTOT = (_datasetName.substr(0,4) != "Data") ? nEffEventsProcessed : 0;
    
    bool foundMetadata = false;
    PROC_XSEC = 0;
    ifstream metadataFile( _MCmetaFileName.c_str(), ios::in );
    while( metadataFile.good() ) {
        string name, xs, xs_unc, Nevt, source;
        metadataFile >> name >> ws >> xs >> ws >> xs_unc >> ws >> Nevt >> ws >> source;
        if( metadataFile.eof() ) break;
        if( name == _datasetName.substr(0,_datasetName.length()-3) ) {
            PROC_XSEC = atof( xs.c_str() );
            PROC_NTOT = (_datasetName.substr(0,4) != "Data") ? atof( Nevt.c_str() ) : 0;
            foundMetadata = true;
            break;
        }
    }
    
    if( (!foundMetadata) && (_datasetName.substr(0,4) != "Data") ) {
        cout << "Did not find dataset " << _datasetName << " in " << _MCmetaFileName << ". Using standard values for xsec and ntot: " << PROC_XSEC << endl;
    }
    
    _NumberEntries = _inputTree -> GetEntries();
    _inputTree->SetBranchAddress("genWeight", &genWeight );
    if( _NumberEntries > _NumMaxEvents && _NumMaxEvents > 0 ){
        double Nevt = 0;
        for( int i = 0; i < _NumMaxEvents; ++i ) {
            _inputTree->GetEntry(i);
            Nevt += genWeight;
        }
        PROC_NTOT = Nevt;
    }
    
    
    
    if( _applyEventWeights ){    
        dataScaleWeight = (PROC_XSEC/PROC_NTOT) * DATA_LUMI;
    }else{
        dataScaleWeight = 1.;
    }
    
    
    //======GENERATE THE PILEUP REWEIGHTING HISTOGRAM==============================================
    if( applyPileupWeights  && (_datasetName.substr(0,4) != "Data") ) {
      string mcHistogramName   = "Distribution_True_" + _datasetName;
      string dataHistogramName = "Distribution_Data_True_NOMINAL";
      TFile *fPU = new TFile( PUFILE.c_str(), "OPEN" );
      if( !fPU || fPU->IsZombie() ) {
        cout << "FATAL: COULDN'T OPEN PILEUPFILE: " << PUFILE << endl;
        exit(-1);
      }
      TH1D *hdata = (TH1D*)fPU->Get(dataHistogramName.c_str());
      TH1D *hmc = (TH1D*)fPU->Get(mcHistogramName.c_str());
      if( !hdata || !hmc ) {
        std::cout << "FATAL: COULDN'T LOAD HISTOGRAM(S): Distribution_Data or " << mcHistogramName << std::endl;
      }
      hdata->Scale( 1./hdata->Integral() );
      hmc->Scale( 1./hmc->Integral() );
      hPU_weights = new TH1D("PileupWeights", "PileupWeights", hdata->GetXaxis()->GetNbins(), hdata->GetXaxis()->GetBinLowEdge(1), hdata->GetXaxis()->GetBinLowEdge( hdata->GetXaxis()->GetNbins() + 1) );
      for( int iBin = 1; iBin <= hdata->GetXaxis()->GetNbins(); ++iBin ) {
        hPU_weights->SetBinContent( iBin, hdata->GetBinContent(iBin) / hmc->GetBinContent(iBin) );
      }
    }
    
    
    
    string file_up = "Metadata/JEC_SYS_UP.txt";
    string file_down = "Metadata/JEC_SYS_DOWN.txt";
    //vector<vector<float>> JEC_SYS_UP(40, vector<float>(50));
    //vector<vector<float>> JEC_SYS_DOWN(40, vector<float>(50));
    //Get_JEC_SYS( file_up, JEC_SYS_UP);
    //Get_JEC_SYS( file_down, JEC_SYS_DOWN);
    
    int rows = 40;
    int cols = 50;
    vector<vector<float>> dataVec(rows, vector<float>(cols));
    ifstream in;
    in.open(file_up);

    if (in.is_open()){
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                in >> dataVec[i][j];    
            }
        }
        in.close();
    }else{
        cout << "Error opening " << file_up << endl;
    }

    
    cout << "[" << 0 << "][" << 0 << "] = " << dataVec[0][0] << endl;
    //cout << "[" << 39 << "][" << 49 << "] = " << JEC_SYS_DOWN[39][49] << endl;

}


//---------------------------------------------------------------------------------------------------------------
// Init
//---------------------------------------------------------------------------------------------------------------
bool HEPAnalysis::Init() {
    
    //======SET HISTOGRAMS STYLE===================================================================
    setStyle(1.0,true,0.15);
    
    
    //======SET THE BRANCH ADDRESSES===============================================================
    /*
    _inputTree->SetBranchAddress("nCorrT1METJet", &nCorrT1METJet );
    _inputTree->SetBranchAddress("nElectron", &nElectron );
    _inputTree->SetBranchAddress("nFatJet", &nFatJet );
    _inputTree->SetBranchAddress("nFsrPhoton", &nFsrPhoton );
    _inputTree->SetBranchAddress("nGenJetAK8", &nGenJetAK8 );
    _inputTree->SetBranchAddress("nGenJet", &nGenJet );
    _inputTree->SetBranchAddress("nSubGenJetAK8", &nSubGenJetAK8 );
    _inputTree->SetBranchAddress("nGenVisTau", &nGenVisTau );
    _inputTree->SetBranchAddress("nLHEPdfWeight", &nLHEPdfWeight );
    _inputTree->SetBranchAddress("nLHEReweightingWeight", &nLHEReweightingWeight );
    _inputTree->SetBranchAddress("nLHEScaleWeight", &nLHEScaleWeight );
    _inputTree->SetBranchAddress("nPSWeight", &nPSWeight );
    _inputTree->SetBranchAddress("nIsoTrack", &nIsoTrack );
    _inputTree->SetBranchAddress("nLHEPart", &nLHEPart );
    _inputTree->SetBranchAddress("nMuon", &nMuon );
    _inputTree->SetBranchAddress("nPhoton", &nPhoton );
    _inputTree->SetBranchAddress("nGenDressedLepton", &nGenDressedLepton );
    _inputTree->SetBranchAddress("nGenIsolatedPhoton", &nGenIsolatedPhoton );
    _inputTree->SetBranchAddress("nSoftActivityJet", &nSoftActivityJet );
    _inputTree->SetBranchAddress("nSubJet", &nSubJet );
    _inputTree->SetBranchAddress("nTau", &nTau );
    _inputTree->SetBranchAddress("nTrigObj", &nTrigObj );
    _inputTree->SetBranchAddress("nOtherPV", &nOtherPV );
    _inputTree->SetBranchAddress("nSV", &nSV );
   */
    
    _inputTree->SetBranchAddress("nJet", &nJet );
    _inputTree->SetBranchAddress("Jet_pt", &Jet_pt );
    
    _inputTree->SetBranchAddress("Electron_eta", &Electron_eta );
    _inputTree->SetBranchAddress("Electron_jetRelIso", &Electron_jetRelIso );
    _inputTree->SetBranchAddress("Electron_phi", &Electron_phi );
    _inputTree->SetBranchAddress("Electron_pt", &Electron_pt );
    _inputTree->SetBranchAddress("Electron_charge", &Electron_charge );

    
    _inputTree->SetBranchAddress("MET_phi", &MET_phi );
    _inputTree->SetBranchAddress("MET_pt", &MET_pt );
    
    _inputTree->SetBranchAddress("HLT_DoubleEle24_22_eta2p1_WPLoose_Gsf", &HLT_DoubleEle24_22 );
    _inputTree->SetBranchAddress("HLT_DoubleEle25_CaloIdL_GsfTrkIdVL", &HLT_DoubleEle25 );
    _inputTree->SetBranchAddress("HLT_DoubleEle33_CaloIdL", &HLT_DoubleEle33 );
    _inputTree->SetBranchAddress("HLT_Ele17_Ele8_Gsf", &HLT_Ele17_Ele8 );
    _inputTree->SetBranchAddress("HLT_Ele22_eta2p1_WPLoose_Gsf", &HLT_Ele22 );
    _inputTree->SetBranchAddress("HLT_Ele23_WPLoose_Gsf", &HLT_Ele23 );
    _inputTree->SetBranchAddress("HLT_Ele24_eta2p1_WPLoose_Gsf", &HLT_Ele24 );
    
    _inputTree->SetBranchAddress("HLT_MET250", &HLT_MET250 );
    
    
    if( _datasetName.substr(0,4) != "Data" ) {
        _inputTree->SetBranchAddress("nGenPart", &nGenPart );
        _inputTree->SetBranchAddress("GenPart_eta", &GenPart_eta );
        _inputTree->SetBranchAddress("GenPart_mass", &GenPart_mass );
        _inputTree->SetBranchAddress("GenPart_phi", &GenPart_phi );
        _inputTree->SetBranchAddress("GenPart_pt", &GenPart_pt );
        _inputTree->SetBranchAddress("GenPart_genPartIdxMother", &GenPart_genPartIdxMother );
        _inputTree->SetBranchAddress("GenPart_pdgId", &GenPart_pdgId );
        _inputTree->SetBranchAddress("GenPart_status", &GenPart_status );
        _inputTree->SetBranchAddress("GenPart_statusFlags", &GenPart_statusFlags );
        _inputTree->SetBranchAddress("GenMET_phi", &GenMET_phi );
        _inputTree->SetBranchAddress("GenMET_pt", &GenMET_pt );
    }
    

    
    return true;
}


//---------------------------------------------------------------------------------------------------------------
// RunEventLoop
//---------------------------------------------------------------------------------------------------------------
void HEPAnalysis::RunEventLoop( int ControlEntries ) {

    //gInterpreter->GenerateDictionary("vector<vector<float> >", "vector");
    //gInterpreter->GenerateDictionary("vector<vector<int> >", "vector");
    
    //======GET NUMBER OF EVENTS===================================================================
    if( ControlEntries < 0 ){
        _NumberEntries = _inputTree -> GetEntries();
        if( _NumberEntries > _NumMaxEvents && _NumMaxEvents > 0 ) _NumberEntries = _NumMaxEvents;
    }
    
    //======PRINT INFO ABOUT THE SELECTION PROCESS=================================================
    cout << endl;
    cout << endl;
    cout << "===================================================================================" << endl;
    cout << "RUNNING SELECTION " << _SELECTION << " ON " << _datasetName << " FILES " << _Files << " (SYSID=" << to_string(_sysID) << ", Universe=" << to_string(_Universe) << ")" << endl; 
    cout << "===================================================================================" << endl;
    cout << "Number of files: " << _inputFileNames.size() << endl;
    cout << "Number of entries considered: " << _NumberEntries << endl;
    cout << "-----------------------------------------------------------------------------------" << endl;
    cout << endl;
    
    if( _sysID == 0 ) {
        _CutflowFileName = _outputDirectory + "cutflow.txt";
        _CutflowFile.open( _CutflowFileName.c_str(), ios::out );
        _CutflowFile << "===========================================================================================" << endl;
        _CutflowFile << "RUNNING SELECTION " << _SELECTION << " ON " << _datasetName << " FILES " << _Files << endl; 
        _CutflowFile << "===========================================================================================" << endl;
        _CutflowFile << "Ntuples path:" << endl;
        int pos = _inputFileNames.at(0).find("00/"); 
        string inputDirectory = _inputFileNames.at(0).substr(0,pos+2);
        _CutflowFile << inputDirectory << endl;
        _CutflowFile << "Number of files: " << _inputFileNames.size() << endl;
        _CutflowFile << "Number of entries considered: " << setprecision(12) << _NumberEntries << endl;
    }
    
    //======SETUP SELECTION========================================================================
    if( false );
    else if( _SELECTION == "SgnEff" ) SetupSgnEff();
    else if( _SELECTION == "Example1" ) SetupExample1();
    else if( _SELECTION == "Example2" ) SetupExample2();
    else if( _SELECTION == "Example3" ) SetupExample3();
    // SETUP YOUR SELECTION HERE
    else {
      cout << "Unknown selection requested. Exiting. " << endl;
      return;
    }
    
    //======SETUP STATISTICAL ERROR================================================================
    vector<double> cutflowOld(50, 0.);
    for( int icut = 0; icut < 50; ++icut ){
        _StatisticalError.push_back(0);
    }
    
    //======SETUP TIMER============================================================================
    int itime = 0;
    int hoursEstimated = 0;
    int minutesEstimated = 0;
    int secondsEstimated = 0;
    time_t timeOld;
    timeOld = time(NULL);
    
    //======PRE-OBJECTS SETUP======================================================================
    PreObjects();
    
    //======LOOP OVER THE EVENTS===================================================================
    sumGenWeights = 0;
    
    for( int i = 0; i < _NumberEntries; ++i ) {
        
        //======TIMER====================================================================    
        if( (i+1)/10000 != itime ){
            int timeEstimated = (_NumberEntries-i)*difftime(time(NULL),timeOld)/10000.;
            hoursEstimated = timeEstimated/3600;
            minutesEstimated = (timeEstimated%3600)/60;
            secondsEstimated = (timeEstimated%3600)%60;
            ++itime;
            timeOld = time(NULL);
        }
        if( _Show_Timer ) {
            cout << "NOW RUNNING EVENT " << setw(8) << i << " | TIME TO FINISH: " << setw(2) << hoursEstimated << " hours " << setw(2) << minutesEstimated << " minutes " << setw(2) << secondsEstimated << " seconds." << "\r"; 
            fflush(stdout);
        }

    
        //======SETUP EVENT==============================================================
        _EventPosition = i;
        _inputTree->GetEntry(i);
        
        /*
        //======SIGNAL SETUP=============================================================
        string signalID = to_string(_DatasetID);
        if( signalID.substr(0,2) == "17" || signalID.substr(0,2) == "18" ){
            int NumNeutralinos = 0;
            int NumGluinos = 0;
            double gluino_M;
            double neutralino_M;
            for( unsigned int ipart = 0; ipart < tmct_m->size(); ++ipart ) {
                if( tmct_id->at(ipart) == 1000021 ){
                    if( NumGluinos == 0 ) gluino_M = tmct_m->at(ipart); 
                    NumGluinos += 1;
                }
                if( tmct_id->at(ipart) == 1000022 ){ 
                    if( NumNeutralinos == 0 ) neutralino_M = tmct_m->at(ipart);
                    NumNeutralinos += 1;
                }
                if( NumGluinos > 0 && NumNeutralinos > 0 ) break;
            }
            double DeltaM = gluino_M - neutralino_M;
            if( signalID.substr(4,2) == "11" && (gluino_M != 250 || DeltaM != 30) ) continue;
            if( signalID.substr(4,2) == "12" && (gluino_M != 250 || DeltaM != 40) ) continue;
            if( signalID.substr(4,2) == "13" && (gluino_M != 250 || DeltaM != 60) ) continue;
            if( signalID.substr(4,2) == "14" && (gluino_M != 250 || DeltaM != 80) ) continue;
            if( signalID.substr(4,2) == "15" && (gluino_M != 250 || DeltaM != 100) ) continue;
            if( signalID.substr(4,2) == "21" && (gluino_M != 500 || DeltaM != 30) ) continue;
            if( signalID.substr(4,2) == "22" && (gluino_M != 500 || DeltaM != 40) ) continue;
            if( signalID.substr(4,2) == "23" && (gluino_M != 500 || DeltaM != 60) ) continue;
            if( signalID.substr(4,2) == "24" && (gluino_M != 500 || DeltaM != 80) ) continue;
            if( signalID.substr(4,2) == "25" && (gluino_M != 500 || DeltaM != 100) ) continue;
            if( signalID.substr(4,2) == "31" && (gluino_M != 750 || DeltaM != 30) ) continue;
            if( signalID.substr(4,2) == "32" && (gluino_M != 750 || DeltaM != 40) ) continue;
            if( signalID.substr(4,2) == "33" && (gluino_M != 750 || DeltaM != 60) ) continue;
            if( signalID.substr(4,2) == "34" && (gluino_M != 750 || DeltaM != 80) ) continue;
            if( signalID.substr(4,2) == "35" && (gluino_M != 750 || DeltaM != 100) ) continue;
            if( signalID.substr(4,2) == "41" && (gluino_M != 1000 || DeltaM != 30) ) continue;
            if( signalID.substr(4,2) == "42" && (gluino_M != 1000 || DeltaM != 40) ) continue;
            if( signalID.substr(4,2) == "43" && (gluino_M != 1000 || DeltaM != 60) ) continue;
            if( signalID.substr(4,2) == "44" && (gluino_M != 1000 || DeltaM != 80) ) continue;
            if( signalID.substr(4,2) == "45" && (gluino_M != 1000 || DeltaM != 100) ) continue;
            if( signalID.substr(4,2) == "51" && (gluino_M != 1250 || DeltaM != 30) ) continue;
            if( signalID.substr(4,2) == "52" && (gluino_M != 1250 || DeltaM != 40) ) continue;
            if( signalID.substr(4,2) == "53" && (gluino_M != 1250 || DeltaM != 60) ) continue;
            if( signalID.substr(4,2) == "54" && (gluino_M != 1250 || DeltaM != 80) ) continue;
            if( signalID.substr(4,2) == "55" && (gluino_M != 1250 || DeltaM != 100) ) continue;
        }
        */
        
        //======COMPUTE EVENT WEIGHT=====================================================
        evtWeight = dataScaleWeight;
        if(_datasetName.substr(0,4) != "Data") evtWeight *= genWeight;
        
        pileupWeight = 1.; 
        if( applyPileupWeights  && (_datasetName.substr(0,4) != "Data") ) {
          //int bin = hPU_weights->GetXaxis()->FindBin( NumberOfTrueInteractions );
          //pileupWeight = hPU_weights->GetBinContent( bin );
          //evtWeight *= pileupWeight;
        }
        

            
        //======RUN OBJECTS SETUP========================================================
        RunObjects();
            
        //======RUN REGION SETUP=========================================================
        bool Selected = true;
        if( _SELECTION == "SgnEff" && !SgnEffRegion() ) Selected = false;
        if( _SELECTION == "Example1" && !Example1Region() ) Selected = false;
        if( _SELECTION == "Example2" && !Example2Region() ) Selected = false;
        if( _SELECTION == "Example3" && !Example3Region() ) Selected = false;
        // SET THE REGION OF YOUR SELECTION HERE
        
        
        //======COMPUTE STATISTICAL ERROR================================================
        int icut = 0;
        for ( map<string,double>::iterator it = _cutFlow.begin(); it != _cutFlow.end(); ++it ){
            if( cutflowOld.at(icut) != it->second ){
                _StatisticalError.at(icut) += evtWeight*evtWeight;
                cutflowOld.at(icut) = it->second;
            }
            ++icut;
        }
        
        
        //======GO TO NEXT STEPS ONLY IF THE EVENT IS SELECTED===========================
        if( !Selected ) continue;
        
        
        //======SUM THE GENERATOR WEIGHTS================================================
        sumGenWeights += genWeight;
        
        
        //======RUN SELECTION ON THE MAIN UNIVERSE=======================================
        if( _sysID == 0 ){
            
            if( _SELECTION == "SgnEff" ) SgnEffSelection();
            if( _SELECTION == "Example1" ) Example1Selection();
            if( _SELECTION == "Example2" ) Example2Selection();
            if( _SELECTION == "Example3" ) Example3Selection();
            // CALL YOUR SELECTION HERE
            
        }
              
              
        //======RUN SYSTEMATIC PRODUCTION=================================================
        if( _SELECTION == "SgnEff" ) SgnEffSystematic();
        if( _SELECTION == "Example1" ) Example1Systematic();
        if( _SELECTION == "Example2" ) Example2Systematic();
        if( _SELECTION == "Example3" ) Example3Systematic();
        // PRODUCE THE SYSTEMATIC OF YOUR SELECTION HERE

    
        
    }
    
    
    //======COMPUTE STATISTICAL ERROR==============================================================
    int icut = 0;
    for ( map<string,double>::iterator it = _cutFlow.begin(); it != _cutFlow.end(); ++it ){
        _StatisticalError.at(icut) = sqrt(_StatisticalError.at(icut));
        ++icut;
    }
    
    return;
} 


//---------------------------------------------------------------------------------------------------------------
// FinishRun
//---------------------------------------------------------------------------------------------------------------
void HEPAnalysis::FinishRun() {

    gErrorIgnoreLevel = kWarning;
    
    
    //======HISTOGRAM PLOT FORMATS=================================================================
    if( _Get_Image_in_EPS ) _plotFormats.push_back(".eps");
    if( _Get_Image_in_PNG ) _plotFormats.push_back(".png");
    if( _Get_Image_in_PDF ) _plotFormats.push_back(".pdf");

    
    if( _sysID == 0 ) {
        //======PRODUCE 1D AND 2D HISTOGRAMS===========================================================
        TCanvas c("","");
        for( map<string,TH2D>::iterator itr_h = _histograms2D.begin(); itr_h != _histograms2D.end(); ++itr_h ) {
            (*itr_h).second.Draw( (_histograms2DDrawOptions.at((*itr_h).first)).c_str()  );
            for( vector<string>::iterator itr_f = _plotFormats.begin(); itr_f != _plotFormats.end(); ++itr_f ) {
                string thisPlotName = _outputDirectory + (*itr_h).first + (*itr_f);
                c.Print( thisPlotName.c_str() );
            }
        }
    
        for( map<string,TH1D>::iterator itr_h = _histograms1D.begin(); itr_h != _histograms1D.end(); ++itr_h ) {
            (*itr_h).second.Draw( (_histograms1DDrawOptions.at((*itr_h).first)).c_str() );
            for( vector<string>::iterator itr_f = _plotFormats.begin(); itr_f != _plotFormats.end(); ++itr_f ) {
                string thisPlotName = _outputDirectory + (*itr_h).first + (*itr_f);
                c.Print( thisPlotName.c_str() );
            }
            //(*itr_h).second.Sumw2();
        }
    }
        
    //======FINISH SELECTION=======================================================================
    if( _SELECTION == "SgnEff" ) FinishSgnEff();
    if( _SELECTION == "Example1" ) FinishExample1();
    if( _SELECTION == "Example2" ) FinishExample2();
    if( _SELECTION == "Example3" ) FinishExample3();
    // FINISH YOUR SELECTION HERE
    
    //======PRINT INFO ABOUT THE SELECTION PROCESS================================================= 
    double luminosity = _applyEventWeights ? DATA_LUMI : PROC_NTOT/PROC_XSEC;
    if( _datasetName.substr(0,4) == "Data" ) luminosity = DATA_LUMI; 
    
    if( _sysID == 0 ) {
        _CutflowFile << "-----------------------------------------------------------------------------------" << endl;
        _CutflowFile << "Luminosity: " << luminosity << " pb-¹" << endl;
        _CutflowFile << "Luminosity Weight: " << setprecision(16) << dataScaleWeight << endl;
        _CutflowFile << "Sum of genWeights processed: " << setprecision(16) << sumGenWeights << endl;
        _CutflowFile << "Number of events generated: " << setprecision(16) << PROC_NTOT*dataScaleWeight << endl;
        _CutflowFile << "-----------------------------------------------------------------------------------" << endl;
        _CutflowFile.width(20); _CutflowFile << left << " Cutflow" << " " << setw(20) << setprecision(16) << "Selected Events"
        << " " << setw(20) << setprecision(12) << "Stat. Error" << setw(15) << setprecision(6) << "Efficiency (%)" << endl;
        _CutflowFile << "-----------------------------------------------------------------------------------" << endl;
        int icut = 0;
        for( map<string,double>::iterator itr = _cutFlow.begin(); itr != _cutFlow.end(); ++itr ) {
            _CutflowFile.width(20); _CutflowFile << left << "|" + (*itr).first << " " << setw(20) << setprecision(16) << (*itr).second 
            << " " << setw(20) << setprecision(12) << _StatisticalError.at(icut) 
            << setw(15) << setprecision(6) << (*itr).second*100./(PROC_NTOT*dataScaleWeight) << endl;
            ++icut;
        }
    }
    
    //======STORE HISTOGRAMS IN A ROOT FILE========================================================
    if( _sysID == 0 ) {
        string HistogramsFileName = _outputDirectory + "Histograms.root";
        TFile *fHistOutput = new TFile( HistogramsFileName.c_str(), "RECREATE" );
        for( map<string,TH1D>::iterator itr_h = _histograms1D.begin(); itr_h != _histograms1D.end(); ++itr_h ) {
            (*itr_h).second.Write();
        }
        for( map<string,TH2D>::iterator itr_h = _histograms2D.begin(); itr_h != _histograms2D.end(); ++itr_h ) {
            (*itr_h).second.Write();
        }
        fHistOutput->Close();
    }
    
    
    //======WRITE OUTPUT TREE IN THE OUTPUT ROOT FILE==============================================
    if( _sysID == 0 ) {
        _outputFile->cd();
        _outputTree->Write();
        _outputFile->Close();
    }

    
    //======WRITE OUTPUT SYS IN THE OUTPUT ROOT FILE===============================================
    _sysFile->cd();
    for( map<string,TH1D>::iterator itr_h = _systematics1D.begin(); itr_h != _systematics1D.end(); ++itr_h ) {
        (*itr_h).second.Write();
        _sysFileTxt << (*itr_h).first << "\t\t\t" << (*itr_h).second.GetXaxis()->GetNbins() << "\t" << (*itr_h).second.GetXaxis()->GetBinLowEdge(1) << "\t" << (*itr_h).second.GetXaxis()->GetBinLowEdge( (*itr_h).second.GetXaxis()->GetNbins() + 1) << "\t\t\t";
        for( int iBin = 1; iBin <= (*itr_h).second.GetXaxis()->GetNbins(); ++iBin ) {
            _sysFileTxt << (*itr_h).second.GetBinContent(iBin) << "\t";
        }
        _sysFileTxt << endl;
    }
    _sysFile->Close();
    
    
    //======END TIME===============================================================================
    _end = time(NULL);
    int time_elapsed = difftime(_end,_begin);
    int hours = time_elapsed/3600;
    int minutes = (time_elapsed%3600)/60;
    int seconds = (time_elapsed%3600)%60;
    
    _CutflowFile << "-----------------------------------------------------------------------------------" << endl;
    _CutflowFile << "Time to process the selection: " << hours << " hours " << minutes << " minutes " << seconds << " seconds." << endl;
    _CutflowFile << "-----------------------------------------------------------------------------------" << endl;
    
    
    //======DELETE POINTERS========================================================================
    delete _inputTree;
    //delete _outputTree;
    //if( _sysID == 0 ) delete _outputFile;
    //delete _sysFile;
    
    delete hPU_weights;
    
   

}


