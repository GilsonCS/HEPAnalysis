#include <iostream>
#include <fstream>
#include <TFile.h>
#include <TChain.h>
#include <TCanvas.h>
#include <TROOT.h>
#include <stdlib.h>
#include <TStyle.h>
#include <TH2D.h>
#include <TLegend.h>
#include <TColor.h>
#include <math.h>
#include <THnSparse.h>
#include <map>
#include <string>
#include <vector>
#include <random>
#include "THnSparse.h"
#include "TF1.h"
#include "TSystem.h"
#include "TLorentzVector.h"
#include "TGraphAsymmErrors.h"
#include <iomanip>
#include <sys/stat.h>
#include <time.h>

using namespace std;

class HEPAnalysis {
    public:
        static HEPAnalysis* GetInstance( char* configFileName );
        ~HEPAnalysis() {}
        
        bool Init();
        void RunEventLoop( int nEventsMax = -1);
        void FinishRun();
        
    private:
        static HEPAnalysis* _instance;

        void RunObjects();
        void PreObjects();
        
        void SetupSgnEff();
        bool SgnEffRegion();
        void SgnEffSelection();
        void SgnEffSystematic();
        void FinishSgnEff();
        void SetupExample1();
        bool Example1Region();
        void Example1Selection();
        void Example1Systematic();
        void FinishExample1();
        void SetupExample2();
        bool Example2Region();
        void Example2Selection();
        void Example2Systematic();
        void FinishExample2();
        void SetupExample3();
        bool Example3Region();
        void Example3Selection();
        void Example3Systematic();
        void FinishExample3();
        // INSERT YOUR SELECTION HERE
        
        // HEPFunctions
        //void Get_JEC_SYS( string filename, vector< vector<float> > &dataVec);
        void makeHist( string nametitle, int nbinsx, double xmin, double xmax, int nbinsy, double ymin, double ymax, string xtitle, string ytitle, string ztitle, string drawOption = "", double xAxisOffset = 1., double yAxisOffset = 1.2, double zAxisOffset = 1. ); 
        void makeHist( string nametitle, int nbins, double xmin, double xmax, string xtitle, string ytitle, string drawOption = "", double xAxisOffset = 1., double yAxisOffset = 1.2 );
        void makeSysHist( string nametitle, int nbins, double xmin, double xmax, string xtitle, string ytitle, string drawOption = "", double xAxisOffset = 1., double yAxisOffset = 1.2 );
        void FillSystematic( string varName, double varEntry, double evtWeight );
        void setStyle(double ytoff = 1.0, bool marker = true, double left_margin = 0.15); 
        void MakeEfficiencyPlot( TH1D hpass, TH1D htotal, string triggerName = "");
        //float MLClassifier( float LeadingMuPt, float NMuons, float LeadingJetPt, float NJets, float MET, float HT );

    private:
        HEPAnalysis() {}
        HEPAnalysis( char* configFileName );
        
        map<string, double>     _cutFlow;
        map<string, TH1D>       _histograms1D;
        map<string, TH2D>       _histograms2D;
        map<string, string>     _histograms1DDrawOptions;
        map<string, string>     _histograms2DDrawOptions;
        
        vector<string>          _inputFileNames;
        string                  _inputTreeName;
        TChain                  *_inputTree;
        string                  _outputFileName;
        string                  _outputDirectory;
        TFile                   *_outputFile;
        TTree                   *_outputTree;
        
        string                  _sysFileName;
        TFile                   *_sysFile;
        map<string, TH1D>       _systematics1D;
        map<string, string>     _systematics1DDrawOptions;
        ofstream                _sysFileTxt;
        int                     _Universe;
        int                     _sysID;
        random_device           _rand;
        
        vector<string>          _plotFormats;
        ofstream                _CutflowFile;
        string                  _CutflowFileName;
        int                     _NumberEntries;
        int                     _EventPosition;
        string                  _SELECTION;
        string                  _datasetName;
        string                  _Files;
        int                     _DatasetID;
        bool                    _applyEventWeights;
        vector<long double>     _StatisticalError;
        bool                    _Show_Timer;
        bool                    _Get_Image_in_EPS;    
        bool                    _Get_Image_in_PNG;    
        bool                    _Get_Image_in_PDF;
        time_t                  _begin;
        time_t                  _end;
        bool                    _check;
        int                     _NumMaxEvents;
        string                  _Redirector;
        
        int SYSJET;
        
        //---------------------------------------------------------------------------------------------------
        // Metadata
        //---------------------------------------------------------------------------------------------------
        double                  _SumOfWeights;
        double PROC_NTOT;       // the total number of events per sample (take it from DAS!)
        double PROC_XSEC;       // the total cross section for the process in pb
        double DATA_LUMI;       // the data luminosity in fb-1 
        double DATA_LUMI_UNC;   // the data luminosity uncertainty in fb-1 
        string                  _MCmetaFileName;
        
        //---------------------------------------------------------------------------------------------------
        // Event weight variables
        //---------------------------------------------------------------------------------------------------      
        double      evtWeight;
        double      dataScaleWeight;
        double      sumGenWeights;
        
        TH1D        *hPU_weights;
        bool        applyPileupWeights;
        double      pileupWeight;
        string      PUFILE;
        
        //---------------------------------------------------------------------------------------------------
        // Cut values
        //---------------------------------------------------------------------------------------------------
        int TRIGGER;
        double JET_ETA_CUT;
        double JET_PT_CUT;
        int JET_ID;
        double MUON_PT_CUT;
        double MUON_ISO;
        int MUON_ID;
        double ELECTRON_PT_CUT;
        double ELECTRON_ISO;
        int ELECTRON_ID;        
        double JET_PT_CUT_SV;
        double JET_PT_CUT_PV;
        double SUBJET_PT_CUT_PV;
        double MET_CUT;
        double MHT_CUT;
        double HT_CUT;
        double OMEGA_MIN_CUT;
        double LEADING_SV_JET_CUT;
        double MJJ_CUT;
        int Track;
        bool ExtraVariables;
        bool CorrectMC;
        
        //---------------------------------------------------------------------------------------------------
        // NANOAOD Variables
        //---------------------------------------------------------------------------------------------------
       
        //UInt_t  nFatJet;                    //[50]  7    3
        //UInt_t  nFsrPhoton;                 //[50]  3    0
        //UInt_t  nGenJetAK8;                 //[50]  9    3
        //UInt_t  nSubGenJetAK8;              //[100] 16   4
        //UInt_t  nGenVisTau;                 //[50]  5    2
        //UInt_t  nPhoton;                    //[50]  9    0
        //UInt_t  nGenIsolatedPhoton;         //[50]  2    0
        
        //======================================================

        UInt_t    run;
        UInt_t    luminosityBlock;
        ULong64_t event;

        Float_t btagWeight_CSVV2;
        Float_t btagWeight_DeepCSVB;
   
        /*
        Float_t CaloMET_phi;
        Float_t CaloMET_pt;
        Float_t CaloMET_sumEt;
        Float_t ChsMET_phi;
        Float_t ChsMET_pt;
        Float_t ChsMET_sumEt;
        UInt_t  nCorrT1METJet;              //[100] 28   6
        Float_t CorrT1METJet_area[100];
        Float_t CorrT1METJet_eta[100];
        Float_t CorrT1METJet_muonSubtrFactor[100];
        Float_t CorrT1METJet_phi[100];
        Float_t CorrT1METJet_rawPt[100];
        Float_t DeepMETResolutionTune_phi;
        Float_t DeepMETResolutionTune_pt;
        Float_t DeepMETResponseTune_phi;
        Float_t DeepMETResponseTune_pt;
        */
        
        UInt_t  nElectron;                  //[50]  9    2
        Float_t Electron_deltaEtaSC[50];
        Float_t Electron_dr03EcalRecHitSumEt[50];
        Float_t Electron_dr03HcalDepth1TowerSumEt[50];
        Float_t Electron_dr03TkSumPt[50];
        Float_t Electron_dr03TkSumPtHEEP[50];
        Float_t Electron_dxy[50];
        Float_t Electron_dxyErr[50];
        Float_t Electron_dz[50];
        Float_t Electron_dzErr[50];
        Float_t Electron_eInvMinusPInv[50];
        Float_t Electron_energyErr[50];
        Float_t Electron_eta[50];
        Float_t Electron_hoe[50];
        Float_t Electron_ip3d[50];
        Float_t Electron_jetPtRelv2[50];
        Float_t Electron_jetRelIso[50];
        Float_t Electron_mass[50];
        Float_t Electron_miniPFRelIso_all[50];
        Float_t Electron_miniPFRelIso_chg[50];
        Float_t Electron_mvaFall17V1Iso[50];
        Float_t Electron_mvaFall17V1noIso[50];
        Float_t Electron_mvaFall17V2Iso[50];
        Float_t Electron_mvaFall17V2noIso[50];
        Float_t Electron_pfRelIso03_all[50];
        Float_t Electron_pfRelIso03_chg[50];
        Float_t Electron_phi[50];
        Float_t Electron_pt[50];
        Float_t Electron_r9[50];
        Float_t Electron_scEtOverPt[50];
        Float_t Electron_sieie[50];
        Float_t Electron_sip3d[50];
        Float_t Electron_mvaTTH[50];
        Int_t   Electron_charge[50];
        Int_t   Electron_cutBased[50];
        Int_t   Electron_cutBased_Fall17_V1[50];
        Int_t   Electron_jetIdx[50];
        Int_t   Electron_pdgId[50];
        Int_t   Electron_photonIdx[50];
        Int_t   Electron_tightCharge[50];
        Int_t   Electron_vidNestedWPBitmap[50];
        Int_t   Electron_vidNestedWPBitmapHEEP[50];
        Bool_t  Electron_convVeto[50];
        Bool_t  Electron_cutBased_HEEP[50];
        Bool_t  Electron_isPFcand[50];
        UChar_t Electron_jetNDauCharged[50];
        UChar_t Electron_lostHits[50];
        Bool_t  Electron_mvaFall17V1Iso_WP80[50];
        Bool_t  Electron_mvaFall17V1Iso_WP90[50];
        Bool_t  Electron_mvaFall17V1Iso_WPL[50];
        Bool_t  Electron_mvaFall17V1noIso_WP80[50];
        Bool_t  Electron_mvaFall17V1noIso_WP90[50];
        Bool_t  Electron_mvaFall17V1noIso_WPL[50];
        Bool_t  Electron_mvaFall17V2Iso_WP80[50];
        Bool_t  Electron_mvaFall17V2Iso_WP90[50];
        Bool_t  Electron_mvaFall17V2Iso_WPL[50];
        Bool_t  Electron_mvaFall17V2noIso_WP80[50];
        Bool_t  Electron_mvaFall17V2noIso_WP90[50];
        Bool_t  Electron_mvaFall17V2noIso_WPL[50];
        UChar_t Electron_seedGain[50];
   
        UInt_t  nGenJet;                    //[100] 23   3
        Float_t GenJet_eta[100];
        Float_t GenJet_mass[100];
        Float_t GenJet_phi[100];
        Float_t GenJet_pt[100];
        
        UInt_t  nGenPart;                   //[500] 143  34
        Float_t GenPart_eta[500];
        Float_t GenPart_mass[500];
        Float_t GenPart_phi[500];
        Float_t GenPart_pt[500];
        Int_t   GenPart_genPartIdxMother[500];
        Int_t   GenPart_pdgId[500];
        Int_t   GenPart_status[500];
        Int_t   GenPart_statusFlags[500];
   
        Float_t Generator_binvar;
        Float_t Generator_scalePDF;
        Float_t Generator_weight;
        Float_t Generator_x1;
        Float_t Generator_x2;
        Float_t Generator_xpdf1;
        Float_t Generator_xpdf2;
        Int_t   Generator_id1;
        Int_t   Generator_id2;
        
        Float_t GenVtx_x;
        Float_t GenVtx_y;
        Float_t GenVtx_z;
     
        Float_t genWeight;
        Float_t LHEWeight_originalXWGTUP;
        UInt_t  nLHEPdfWeight;              //[500] 101  68
        Float_t LHEPdfWeight[500];
        //UInt_t  nLHEReweightingWeight;      //[]  0    0
        //Float_t LHEReweightingWeight[];
        UInt_t  nLHEScaleWeight;            //[50]  9    0
        Float_t LHEScaleWeight[50];
        UInt_t  nPSWeight;                  //[50]  4    0
        Float_t PSWeight[50];
   
        UInt_t  nIsoTrack;                  //[50]  6    1
        Float_t IsoTrack_dxy[50];
        Float_t IsoTrack_dz[50];
        Float_t IsoTrack_eta[50];
        Float_t IsoTrack_pfRelIso03_all[50];
        Float_t IsoTrack_pfRelIso03_chg[50];
        Float_t IsoTrack_phi[50];
        Float_t IsoTrack_pt[50];
        Float_t IsoTrack_miniPFRelIso_all[50];
        Float_t IsoTrack_miniPFRelIso_chg[50];
        Int_t   IsoTrack_fromPV[50];
        Int_t   IsoTrack_pdgId[50];
        Bool_t  IsoTrack_isHighPurityTrack[50];
        Bool_t  IsoTrack_isPFcand[50];
        Bool_t  IsoTrack_isFromLostTrack[50];
   
        UInt_t  nJet;                       //[100] 24   3
        Float_t Jet_area[100];
        Float_t Jet_btagCSVV2[100];
        Float_t Jet_btagDeepB[100];
        Float_t Jet_btagDeepCvB[100];
        Float_t Jet_btagDeepCvL[100];
        Float_t Jet_btagDeepFlavB[100];
        Float_t Jet_btagDeepFlavCvB[100];
        Float_t Jet_btagDeepFlavCvL[100];
        Float_t Jet_btagDeepFlavQG[100];
        Float_t Jet_chEmEF[100];
        Float_t Jet_chFPV0EF[100];
        Float_t Jet_chFPV1EF[100];
        Float_t Jet_chFPV2EF[100];
        Float_t Jet_chFPV3EF[100];
        Float_t Jet_chHEF[100];
        Float_t Jet_eta[100];
        Float_t Jet_mass[100];
        Float_t Jet_muEF[100];
        Float_t Jet_muonSubtrFactor[100];
        Float_t Jet_neEmEF[100];
        Float_t Jet_neHEF[100];
        Float_t Jet_phi[100];
        Float_t Jet_pt[100];
        Float_t Jet_puIdDisc[100];
        Float_t Jet_qgl[100];
        Float_t Jet_rawFactor[100];
        Float_t Jet_bRegCorr[100];
        Float_t Jet_bRegRes[100];
        Float_t Jet_cRegCorr[100];
        Float_t Jet_cRegRes[100];
        Int_t   Jet_electronIdx1[100];
        Int_t   Jet_electronIdx2[100];
        Int_t   Jet_jetId[100];
        Int_t   Jet_muonIdx1[100];
        Int_t   Jet_muonIdx2[100];
        Int_t   Jet_nConstituents[100];
        Int_t   Jet_nElectrons[100];
        Int_t   Jet_nMuons[100];
        Int_t   Jet_puId[100];
   
        /*
        Float_t LHE_HT;
        Float_t LHE_HTIncoming;
        Float_t LHE_Vpt;
        Float_t LHE_AlphaS;
        UChar_t LHE_Njets;
        UChar_t LHE_Nb;
        UChar_t LHE_Nc;
        UChar_t LHE_Nuds;
        UChar_t LHE_Nglu;
        UChar_t LHE_NpNLO;
        UChar_t LHE_NpLO;
        UInt_t  nLHEPart;                   //[50]  8    3
        Float_t LHEPart_pt[50];
        Float_t LHEPart_eta[50];
        Float_t LHEPart_phi[50];
        Float_t LHEPart_mass[50];
        Float_t LHEPart_incomingpz[50];
        Int_t   LHEPart_pdgId[50];
        Int_t   LHEPart_status[50];
        Int_t   LHEPart_spin[50];
        */
        
        Float_t GenMET_phi;
        Float_t GenMET_pt;
        Float_t MET_MetUnclustEnUpDeltaX;
        Float_t MET_MetUnclustEnUpDeltaY;
        Float_t MET_covXX;
        Float_t MET_covXY;
        Float_t MET_covYY;
        Float_t MET_phi;
        Float_t MET_pt;
        Float_t MET_significance;
        Float_t MET_sumEt;
        Float_t MET_sumPtUnclustered;
   
        UInt_t  nMuon;                      //[50]  8    1
        Float_t Muon_dxy[50];
        Float_t Muon_dxyErr[50];
        Float_t Muon_dxybs[50];
        Float_t Muon_dz[50];
        Float_t Muon_dzErr[50];
        Float_t Muon_eta[50];
        Float_t Muon_ip3d[50];
        Float_t Muon_jetPtRelv2[50];
        Float_t Muon_jetRelIso[50];
        Float_t Muon_mass[50];
        Float_t Muon_miniPFRelIso_all[50];
        Float_t Muon_miniPFRelIso_chg[50];
        Float_t Muon_pfRelIso03_all[50];
        Float_t Muon_pfRelIso03_chg[50];
        Float_t Muon_pfRelIso04_all[50];
        Float_t Muon_phi[50];
        Float_t Muon_pt[50];
        Float_t Muon_ptErr[50];
        Float_t Muon_segmentComp[50];
        Float_t Muon_sip3d[50];
        Float_t Muon_softMva[50];
        Float_t Muon_tkRelIso[50];
        Float_t Muon_tunepRelPt[50];
        Float_t Muon_mvaLowPt[50];
        Float_t Muon_mvaTTH[50];
        Int_t   Muon_charge[50];
        Int_t   Muon_jetIdx[50];
        Int_t   Muon_nStations[50];
        Int_t   Muon_nTrackerLayers[50];
        Int_t   Muon_pdgId[50];
        Int_t   Muon_tightCharge[50];
        Int_t   Muon_fsrPhotonIdx[50];
        UChar_t Muon_highPtId[50];
        Bool_t  Muon_highPurity[50];
        Bool_t  Muon_inTimeMuon[50];
        Bool_t  Muon_isGlobal[50];
        Bool_t  Muon_isPFcand[50];
        Bool_t  Muon_isTracker[50];
        UChar_t Muon_jetNDauCharged[50];
        Bool_t  Muon_looseId[50];
        Bool_t  Muon_mediumId[50];
        Bool_t  Muon_mediumPromptId[50];
        UChar_t Muon_miniIsoId[50];
        UChar_t Muon_multiIsoId[50];
        UChar_t Muon_mvaId[50];
        UChar_t Muon_mvaLowPtId[50];
        UChar_t Muon_pfIsoId[50];
        UChar_t Muon_puppiIsoId[50];
        Bool_t  Muon_softId[50];
        Bool_t  Muon_softMvaId[50];
        Bool_t  Muon_tightId[50];
        UChar_t Muon_tkIsoId[50];
        Bool_t  Muon_triggerIdLoose[50];
   
        Float_t Pileup_nTrueInt;
        Float_t Pileup_pudensity;
        Float_t Pileup_gpudensity;
        Int_t   Pileup_nPU;
        Int_t   Pileup_sumEOOT;
        Int_t   Pileup_sumLOOT;
     
        /*
        Float_t fixedGridRhoFastjetAll;
        Float_t fixedGridRhoFastjetCentral;
        Float_t fixedGridRhoFastjetCentralCalo;
        Float_t fixedGridRhoFastjetCentralChargedPileUp;
        Float_t fixedGridRhoFastjetCentralNeutral;
        */
        
        /*
        UInt_t  nGenDressedLepton;          //[50]  4    0
        Float_t GenDressedLepton_eta[50];
        Float_t GenDressedLepton_mass[50];
        Float_t GenDressedLepton_phi[50];
        Float_t GenDressedLepton_pt[50];
        Int_t   GenDressedLepton_pdgId[50];
        Bool_t  GenDressedLepton_hasTauAnc[50];
        */
        
        /*
        UInt_t  nSoftActivityJet;           //[50]  6    0
        Float_t SoftActivityJet_eta[50];
        Float_t SoftActivityJet_phi[50];
        Float_t SoftActivityJet_pt[50];
        Float_t SoftActivityJetHT;
        Float_t SoftActivityJetHT10;
        Float_t SoftActivityJetHT2;
        Float_t SoftActivityJetHT5;
        Int_t   SoftActivityJetNjets10;
        Int_t   SoftActivityJetNjets2;
        Int_t   SoftActivityJetNjets5;
        */
        
        /*
        UInt_t  nSubJet;                    //[100] 10   2
        Float_t SubJet_btagCSVV2[100];
        Float_t SubJet_btagDeepB[100];
        Float_t SubJet_eta[100];
        Float_t SubJet_mass[100];
        Float_t SubJet_n2b1[100];
        Float_t SubJet_n3b1[100];
        Float_t SubJet_phi[100];
        Float_t SubJet_pt[100];
        Float_t SubJet_rawFactor[100];
        Float_t SubJet_tau1[100];
        Float_t SubJet_tau2[100];
        Float_t SubJet_tau3[100];
        Float_t SubJet_tau4[100];
        */
        
        /*
        UInt_t  nTau;                       //[50]  7    1
        Float_t Tau_chargedIso[50];
        Float_t Tau_dxy[50];
        Float_t Tau_dz[50];
        Float_t Tau_eta[50];
        Float_t Tau_leadTkDeltaEta[50];
        Float_t Tau_leadTkDeltaPhi[50];
        Float_t Tau_leadTkPtOverTauPt[50];
        Float_t Tau_mass[50];
        Float_t Tau_neutralIso[50];
        Float_t Tau_phi[50];
        Float_t Tau_photonsOutsideSignalCone[50];
        Float_t Tau_pt[50];
        Float_t Tau_puCorr[50];
        Float_t Tau_rawAntiEle[50];
        Float_t Tau_rawAntiEle2018[50];
        Float_t Tau_rawDeepTau2017v2p1VSe[50];
        Float_t Tau_rawDeepTau2017v2p1VSjet[50];
        Float_t Tau_rawDeepTau2017v2p1VSmu[50];
        Float_t Tau_rawIso[50];
        Float_t Tau_rawIsodR03[50];
        Float_t Tau_rawMVAnewDM2017v2[50];
        Float_t Tau_rawMVAoldDM[50];
        Float_t Tau_rawMVAoldDM2017v1[50];
        Float_t Tau_rawMVAoldDM2017v2[50];
        Float_t Tau_rawMVAoldDMdR032017v2[50];
        Int_t   Tau_charge[50];
        Int_t   Tau_decayMode[50];
        Int_t   Tau_jetIdx[50];
        Int_t   Tau_rawAntiEleCat[50];
        Int_t   Tau_rawAntiEleCat2018[50];
        UChar_t Tau_idAntiEle[50];
        UChar_t Tau_idAntiEle2018[50];
        Bool_t  Tau_idAntiEleDeadECal[50];
        UChar_t Tau_idAntiMu[50];
        Bool_t  Tau_idDecayMode[50];
        Bool_t  Tau_idDecayModeNewDMs[50];
        UChar_t Tau_idDeepTau2017v2p1VSe[50];
        UChar_t Tau_idDeepTau2017v2p1VSjet[50];
        UChar_t Tau_idDeepTau2017v2p1VSmu[50];
        UChar_t Tau_idMVAnewDM2017v2[50];
        UChar_t Tau_idMVAoldDM[50];
        UChar_t Tau_idMVAoldDM2017v1[50];
        UChar_t Tau_idMVAoldDM2017v2[50];
        UChar_t Tau_idMVAoldDMdR032017v2[50];
        */
        
        /*
        UInt_t  nTrigObj;                   //[100] 43   10
        Float_t TrigObj_pt[100];
        Float_t TrigObj_eta[100];
        Float_t TrigObj_phi[100];
        Float_t TrigObj_l1pt[100];
        Float_t TrigObj_l1pt_2[100];
        Float_t TrigObj_l2pt[100];
        Int_t   TrigObj_id[100];
        Int_t   TrigObj_l1iso[100];
        Int_t   TrigObj_l1charge[100];
        Int_t   TrigObj_filterBits[100];
        */
        
        /*
        UInt_t  nOtherPV;                   //[50]  3    0
        Float_t OtherPV_z[50];
        Float_t PV_ndof;
        Float_t PV_x;
        Float_t PV_y;
        Float_t PV_z;
        Float_t PV_chi2;
        Float_t PV_score;
        Int_t   PV_npvs;
        Int_t   PV_npvsGood;
        */
        
        /*
        Int_t   Electron_genPartIdx[];
        UChar_t Electron_genPartFlav[];
        Int_t   FatJet_genJetAK8Idx[];
        Int_t   FatJet_hadronFlavour[];
        UChar_t FatJet_nBHadrons[];
        UChar_t FatJet_nCHadrons[];
        Int_t   GenJetAK8_partonFlavour[];
        UChar_t GenJetAK8_hadronFlavour[];
        Int_t   GenJet_partonFlavour[];
        UChar_t GenJet_hadronFlavour[];
        Float_t GenVtx_t0;
        Int_t   Jet_genJetIdx[];
        Int_t   Jet_hadronFlavour[];
        Int_t   Jet_partonFlavour[];
        Int_t   Muon_genPartIdx[];
        UChar_t Muon_genPartFlav[];
        Int_t   Photon_genPartIdx[];
        UChar_t Photon_genPartFlav[];
        Int_t   SubJet_hadronFlavour[];
        UChar_t SubJet_nBHadrons[];
        UChar_t SubJet_nCHadrons[];
        */
        
        UInt_t  nSV;                        //[100] 13   4
        Float_t SV_dlen[100];
        Float_t SV_dlenSig[100];
        Float_t SV_dxy[100];
        Float_t SV_dxySig[100];
        Float_t SV_pAngle[100];
        Float_t SV_chi2[100];
        Float_t SV_eta[100];
        Float_t SV_mass[100];
        Float_t SV_ndof[100];
        Float_t SV_phi[100];
        Float_t SV_pt[100];
        Float_t SV_x[100];
        Float_t SV_y[100];
        Float_t SV_z[100];
        UChar_t SV_ntracks[100];
   
        Bool_t  Flag_HBHENoiseFilter;
        Bool_t  Flag_HBHENoiseIsoFilter;
        Bool_t  Flag_CSCTightHaloFilter;
        Bool_t  Flag_CSCTightHaloTrkMuUnvetoFilter;
        Bool_t  Flag_CSCTightHalo2015Filter;
        Bool_t  Flag_globalTightHalo2016Filter;
        Bool_t  Flag_globalSuperTightHalo2016Filter;
        Bool_t  Flag_HcalStripHaloFilter;
        Bool_t  Flag_hcalLaserEventFilter;
        Bool_t  Flag_EcalDeadCellTriggerPrimitiveFilter;
        Bool_t  Flag_EcalDeadCellBoundaryEnergyFilter;
        Bool_t  Flag_ecalBadCalibFilter;
        Bool_t  Flag_goodVertices;
        Bool_t  Flag_eeBadScFilter;
        Bool_t  Flag_ecalLaserCorrFilter;
        Bool_t  Flag_trkPOGFilters;
        Bool_t  Flag_chargedHadronTrackResolutionFilter;
        Bool_t  Flag_muonBadTrackFilter;
        Bool_t  Flag_BadChargedCandidateFilter;
        Bool_t  Flag_BadPFMuonFilter;
        Bool_t  Flag_BadChargedCandidateSummer16Filter;
        Bool_t  Flag_BadPFMuonSummer16Filter;
        Bool_t  Flag_METFilters;
        
        
        Bool_t  HLT_DoubleEle24_22;
        Bool_t  HLT_DoubleEle25;
        Bool_t  HLT_DoubleEle33;
        Bool_t  HLT_Ele17_Ele8;
        Bool_t  HLT_Ele22;
        Bool_t  HLT_Ele23;
        Bool_t  HLT_Ele24;
        
        
        Bool_t  HLT_MET250;
        /*
        
        
        Bool_t  HLT_Mu16_eta2p1_MET30 = {fReader, "HLT_Mu16_eta2p1_MET30"};
        Bool_t  HLT_IsoMu16_eta2p1_MET30 = {fReader, "HLT_IsoMu16_eta2p1_MET30"};
        Bool_t  HLT_IsoMu17_eta2p1 = {fReader, "HLT_IsoMu17_eta2p1"};
        Bool_t  HLT_IsoMu18 = {fReader, "HLT_IsoMu18"};
        Bool_t  HLT_IsoMu20 = {fReader, "HLT_IsoMu20"};
        Bool_t  HLT_IsoMu22 = {fReader, "HLT_IsoMu22"};
        Bool_t  HLT_IsoMu22_eta2p1 = {fReader, "HLT_IsoMu22_eta2p1"};
        Bool_t  HLT_IsoMu24 = {fReader, "HLT_IsoMu24"};
        */
        
        /*
        Bool_t  HLTriggerFirstPath = {fReader, "HLTriggerFirstPath"};
        Bool_t  HLT_CaloJet260 = {fReader, "HLT_CaloJet260"};
        Bool_t  HLT_CaloJet500_NoJetID = {fReader, "HLT_CaloJet500_NoJetID"};
        Bool_t  HLT_Dimuon13_PsiPrime = {fReader, "HLT_Dimuon13_PsiPrime"};
        Bool_t  HLT_Dimuon13_Upsilon = {fReader, "HLT_Dimuon13_Upsilon"};
        Bool_t  HLT_Dimuon20_Jpsi = {fReader, "HLT_Dimuon20_Jpsi"};
        
        Bool_t  HLT_DoubleEle33_CaloIdL_MW = {fReader, "HLT_DoubleEle33_CaloIdL_MW"};
        Bool_t  HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_MW = {fReader, "HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_MW"};
        Bool_t  HLT_DoubleEle33_CaloIdL_GsfTrkIdVL = {fReader, "HLT_DoubleEle33_CaloIdL_GsfTrkIdVL"};
        Bool_t  HLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg = {fReader, "HLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg"};
        Bool_t  HLT_DoubleTightCombinedIsoPFTau35_Trk1_eta2p1_Reg = {fReader, "HLT_DoubleTightCombinedIsoPFTau35_Trk1_eta2p1_Reg"};
        Bool_t  HLT_DoubleMediumCombinedIsoPFTau40_Trk1_eta2p1_Reg = {fReader, "HLT_DoubleMediumCombinedIsoPFTau40_Trk1_eta2p1_Reg"};
        Bool_t  HLT_DoubleTightCombinedIsoPFTau40_Trk1_eta2p1_Reg = {fReader, "HLT_DoubleTightCombinedIsoPFTau40_Trk1_eta2p1_Reg"};
        Bool_t  HLT_DoubleMediumCombinedIsoPFTau40_Trk1_eta2p1 = {fReader, "HLT_DoubleMediumCombinedIsoPFTau40_Trk1_eta2p1"};
        Bool_t  HLT_DoubleTightCombinedIsoPFTau40_Trk1_eta2p1 = {fReader, "HLT_DoubleTightCombinedIsoPFTau40_Trk1_eta2p1"};
        Bool_t  HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg = {fReader, "HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg"};
        Bool_t  HLT_DoubleMediumIsoPFTau40_Trk1_eta2p1_Reg = {fReader, "HLT_DoubleMediumIsoPFTau40_Trk1_eta2p1_Reg"};
        Bool_t  HLT_DoubleMediumIsoPFTau40_Trk1_eta2p1 = {fReader, "HLT_DoubleMediumIsoPFTau40_Trk1_eta2p1"};
        Bool_t  HLT_DoubleEle37_Ele27_CaloIdL_GsfTrkIdVL = {fReader, "HLT_DoubleEle37_Ele27_CaloIdL_GsfTrkIdVL"};
        Bool_t  HLT_DoubleMu33NoFiltersNoVtx = {fReader, "HLT_DoubleMu33NoFiltersNoVtx"};
        Bool_t  HLT_DoubleMu38NoFiltersNoVtx = {fReader, "HLT_DoubleMu38NoFiltersNoVtx"};
        Bool_t  HLT_DoubleMu23NoFiltersNoVtxDisplaced = {fReader, "HLT_DoubleMu23NoFiltersNoVtxDisplaced"};
        Bool_t  HLT_DoubleMu28NoFiltersNoVtxDisplaced = {fReader, "HLT_DoubleMu28NoFiltersNoVtxDisplaced"};
        Bool_t  HLT_DoubleMu0 = {fReader, "HLT_DoubleMu0"};
        Bool_t  HLT_DoubleMu4_3_Bs = {fReader, "HLT_DoubleMu4_3_Bs"};
        Bool_t  HLT_DoubleMu4_3_Jpsi_Displaced = {fReader, "HLT_DoubleMu4_3_Jpsi_Displaced"};
        Bool_t  HLT_DoubleMu4_JpsiTrk_Displaced = {fReader, "HLT_DoubleMu4_JpsiTrk_Displaced"};
        Bool_t  HLT_DoubleMu4_LowMassNonResonantTrk_Displaced = {fReader, "HLT_DoubleMu4_LowMassNonResonantTrk_Displaced"};
        Bool_t  HLT_DoubleMu3_Trk_Tau3mu = {fReader, "HLT_DoubleMu3_Trk_Tau3mu"};
        Bool_t  HLT_DoubleMu4_PsiPrimeTrk_Displaced = {fReader, "HLT_DoubleMu4_PsiPrimeTrk_Displaced"};
        Bool_t  HLT_Mu7p5_L2Mu2_Jpsi = {fReader, "HLT_Mu7p5_L2Mu2_Jpsi"};
        Bool_t  HLT_Mu7p5_L2Mu2_Upsilon = {fReader, "HLT_Mu7p5_L2Mu2_Upsilon"};
        Bool_t  HLT_Mu7p5_Track2_Jpsi = {fReader, "HLT_Mu7p5_Track2_Jpsi"};
        Bool_t  HLT_Mu7p5_Track3p5_Jpsi = {fReader, "HLT_Mu7p5_Track3p5_Jpsi"};
        Bool_t  HLT_Mu7p5_Track7_Jpsi = {fReader, "HLT_Mu7p5_Track7_Jpsi"};
        Bool_t  HLT_Mu7p5_Track2_Upsilon = {fReader, "HLT_Mu7p5_Track2_Upsilon"};
        Bool_t  HLT_Mu7p5_Track3p5_Upsilon = {fReader, "HLT_Mu7p5_Track3p5_Upsilon"};
        Bool_t  HLT_Mu7p5_Track7_Upsilon = {fReader, "HLT_Mu7p5_Track7_Upsilon"};
        Bool_t  HLT_Dimuon0er16_Jpsi_NoOS_NoVertexing = {fReader, "HLT_Dimuon0er16_Jpsi_NoOS_NoVertexing"};
        Bool_t  HLT_Dimuon0er16_Jpsi_NoVertexing = {fReader, "HLT_Dimuon0er16_Jpsi_NoVertexing"};
        Bool_t  HLT_Dimuon6_Jpsi_NoVertexing = {fReader, "HLT_Dimuon6_Jpsi_NoVertexing"};
        Bool_t  HLT_Photon150 = {fReader, "HLT_Photon150"};
        Bool_t  HLT_Photon90_CaloIdL_HT300 = {fReader, "HLT_Photon90_CaloIdL_HT300"};
        Bool_t  HLT_HT250_CaloMET70 = {fReader, "HLT_HT250_CaloMET70"};
        Bool_t  HLT_DoublePhoton60 = {fReader, "HLT_DoublePhoton60"};
        Bool_t  HLT_DoublePhoton85 = {fReader, "HLT_DoublePhoton85"};
        
        Bool_t  HLT_Ele20_eta2p1_WPLoose_Gsf_LooseIsoPFTau28 = {fReader, "HLT_Ele20_eta2p1_WPLoose_Gsf_LooseIsoPFTau28"};
        Bool_t  HLT_Ele22_eta2p1_WPLoose_Gsf_LooseIsoPFTau29 = {fReader, "HLT_Ele22_eta2p1_WPLoose_Gsf_LooseIsoPFTau29"};
        
        Bool_t  HLT_Ele22_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1 = {fReader, "HLT_Ele22_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1"};
        
        Bool_t  HLT_Ele23_WPLoose_Gsf_WHbbBoost = {fReader, "HLT_Ele23_WPLoose_Gsf_WHbbBoost"};
        
        Bool_t  HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20 = {fReader, "HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20"};
        Bool_t  HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1 = {fReader, "HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1"};
        Bool_t  HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau30 = {fReader, "HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau30"};
        Bool_t  HLT_Ele25_WPTight_Gsf = {fReader, "HLT_Ele25_WPTight_Gsf"};
        Bool_t  HLT_Ele25_eta2p1_WPLoose_Gsf = {fReader, "HLT_Ele25_eta2p1_WPLoose_Gsf"};
        Bool_t  HLT_Ele25_eta2p1_WPTight_Gsf = {fReader, "HLT_Ele25_eta2p1_WPTight_Gsf"};
        Bool_t  HLT_Ele27_WPLoose_Gsf = {fReader, "HLT_Ele27_WPLoose_Gsf"};
        Bool_t  HLT_Ele27_WPLoose_Gsf_WHbbBoost = {fReader, "HLT_Ele27_WPLoose_Gsf_WHbbBoost"};
        Bool_t  HLT_Ele27_WPTight_Gsf = {fReader, "HLT_Ele27_WPTight_Gsf"};
        Bool_t  HLT_Ele27_WPTight_Gsf_L1JetTauSeeded = {fReader, "HLT_Ele27_WPTight_Gsf_L1JetTauSeeded"};
        Bool_t  HLT_Ele27_eta2p1_WPLoose_Gsf = {fReader, "HLT_Ele27_eta2p1_WPLoose_Gsf"};
        Bool_t  HLT_Ele27_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1 = {fReader, "HLT_Ele27_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1"};
        Bool_t  HLT_Ele27_eta2p1_WPTight_Gsf = {fReader, "HLT_Ele27_eta2p1_WPTight_Gsf"};
        Bool_t  HLT_Ele30_WPTight_Gsf = {fReader, "HLT_Ele30_WPTight_Gsf"};
        Bool_t  HLT_Ele30_eta2p1_WPLoose_Gsf = {fReader, "HLT_Ele30_eta2p1_WPLoose_Gsf"};
        Bool_t  HLT_Ele30_eta2p1_WPTight_Gsf = {fReader, "HLT_Ele30_eta2p1_WPTight_Gsf"};
        Bool_t  HLT_Ele32_WPTight_Gsf = {fReader, "HLT_Ele32_WPTight_Gsf"};
        Bool_t  HLT_Ele32_eta2p1_WPLoose_Gsf = {fReader, "HLT_Ele32_eta2p1_WPLoose_Gsf"};
        Bool_t  HLT_Ele32_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1 = {fReader, "HLT_Ele32_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1"};
        Bool_t  HLT_Ele32_eta2p1_WPTight_Gsf = {fReader, "HLT_Ele32_eta2p1_WPTight_Gsf"};
        Bool_t  HLT_Ele35_WPLoose_Gsf = {fReader, "HLT_Ele35_WPLoose_Gsf"};
        Bool_t  HLT_Ele35_CaloIdVT_GsfTrkIdT_PFJet150_PFJet50 = {fReader, "HLT_Ele35_CaloIdVT_GsfTrkIdT_PFJet150_PFJet50"};
        Bool_t  HLT_Ele36_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1 = {fReader, "HLT_Ele36_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1"};
        Bool_t  HLT_Ele45_WPLoose_Gsf = {fReader, "HLT_Ele45_WPLoose_Gsf"};
        Bool_t  HLT_Ele45_WPLoose_Gsf_L1JetTauSeeded = {fReader, "HLT_Ele45_WPLoose_Gsf_L1JetTauSeeded"};
        Bool_t  HLT_Ele45_CaloIdVT_GsfTrkIdT_PFJet200_PFJet50 = {fReader, "HLT_Ele45_CaloIdVT_GsfTrkIdT_PFJet200_PFJet50"};
        Bool_t  HLT_Ele105_CaloIdVT_GsfTrkIdT = {fReader, "HLT_Ele105_CaloIdVT_GsfTrkIdT"};
        Bool_t  HLT_Ele30WP60_SC4_Mass55 = {fReader, "HLT_Ele30WP60_SC4_Mass55"};
        Bool_t  HLT_Ele30WP60_Ele8_Mass55 = {fReader, "HLT_Ele30WP60_Ele8_Mass55"};
        Bool_t  HLT_HT200 = {fReader, "HLT_HT200"};
        Bool_t  HLT_HT275 = {fReader, "HLT_HT275"};
        Bool_t  HLT_HT325 = {fReader, "HLT_HT325"};
        Bool_t  HLT_HT425 = {fReader, "HLT_HT425"};
        Bool_t  HLT_HT575 = {fReader, "HLT_HT575"};
        Bool_t  HLT_HT410to430 = {fReader, "HLT_HT410to430"};
        Bool_t  HLT_HT430to450 = {fReader, "HLT_HT430to450"};
        Bool_t  HLT_HT450to470 = {fReader, "HLT_HT450to470"};
        Bool_t  HLT_HT470to500 = {fReader, "HLT_HT470to500"};
        Bool_t  HLT_HT500to550 = {fReader, "HLT_HT500to550"};
        Bool_t  HLT_HT550to650 = {fReader, "HLT_HT550to650"};
        Bool_t  HLT_HT650 = {fReader, "HLT_HT650"};
        
        Bool_t  HLT_IsoMu16_eta2p1_MET30_LooseIsoPFTau50_Trk30_eta2p1 = {fReader, "HLT_IsoMu16_eta2p1_MET30_LooseIsoPFTau50_Trk30_eta2p1"};
        
        Bool_t  HLT_IsoMu17_eta2p1_LooseIsoPFTau20 = {fReader, "HLT_IsoMu17_eta2p1_LooseIsoPFTau20"};
        Bool_t  HLT_IsoMu17_eta2p1_LooseIsoPFTau20_SingleL1 = {fReader, "HLT_IsoMu17_eta2p1_LooseIsoPFTau20_SingleL1"};
        Bool_t  HLT_DoubleIsoMu17_eta2p1 = {fReader, "HLT_DoubleIsoMu17_eta2p1"};
        Bool_t  HLT_DoubleIsoMu17_eta2p1_noDzCut = {fReader, "HLT_DoubleIsoMu17_eta2p1_noDzCut"};
        
        Bool_t  HLT_IsoMu19_eta2p1_LooseIsoPFTau20 = {fReader, "HLT_IsoMu19_eta2p1_LooseIsoPFTau20"};
        Bool_t  HLT_IsoMu19_eta2p1_LooseIsoPFTau20_SingleL1 = {fReader, "HLT_IsoMu19_eta2p1_LooseIsoPFTau20_SingleL1"};
        Bool_t  HLT_IsoMu19_eta2p1_MediumIsoPFTau32_Trk1_eta2p1_Reg = {fReader, "HLT_IsoMu19_eta2p1_MediumIsoPFTau32_Trk1_eta2p1_Reg"};
        Bool_t  HLT_IsoMu19_eta2p1_LooseCombinedIsoPFTau20 = {fReader, "HLT_IsoMu19_eta2p1_LooseCombinedIsoPFTau20"};
        Bool_t  HLT_IsoMu19_eta2p1_MediumCombinedIsoPFTau32_Trk1_eta2p1_Reg = {fReader, "HLT_IsoMu19_eta2p1_MediumCombinedIsoPFTau32_Trk1_eta2p1_Reg"};
        Bool_t  HLT_IsoMu19_eta2p1_TightCombinedIsoPFTau32_Trk1_eta2p1_Reg = {fReader, "HLT_IsoMu19_eta2p1_TightCombinedIsoPFTau32_Trk1_eta2p1_Reg"};
        Bool_t  HLT_IsoMu21_eta2p1_MediumCombinedIsoPFTau32_Trk1_eta2p1_Reg = {fReader, "HLT_IsoMu21_eta2p1_MediumCombinedIsoPFTau32_Trk1_eta2p1_Reg"};
        Bool_t  HLT_IsoMu21_eta2p1_TightCombinedIsoPFTau32_Trk1_eta2p1_Reg = {fReader, "HLT_IsoMu21_eta2p1_TightCombinedIsoPFTau32_Trk1_eta2p1_Reg"};
        
        Bool_t  HLT_IsoMu21_eta2p1_LooseIsoPFTau20_SingleL1 = {fReader, "HLT_IsoMu21_eta2p1_LooseIsoPFTau20_SingleL1"};
        Bool_t  HLT_IsoMu21_eta2p1_LooseIsoPFTau50_Trk30_eta2p1_SingleL1 = {fReader, "HLT_IsoMu21_eta2p1_LooseIsoPFTau50_Trk30_eta2p1_SingleL1"};
        Bool_t  HLT_IsoMu21_eta2p1_MediumIsoPFTau32_Trk1_eta2p1_Reg = {fReader, "HLT_IsoMu21_eta2p1_MediumIsoPFTau32_Trk1_eta2p1_Reg"};
        Bool_t  HLT_IsoMu22 = {fReader, "HLT_IsoMu22"};
        Bool_t  HLT_IsoMu22_eta2p1 = {fReader, "HLT_IsoMu22_eta2p1"};
        Bool_t  HLT_IsoMu24 = {fReader, "HLT_IsoMu24"};
        Bool_t  HLT_IsoMu27 = {fReader, "HLT_IsoMu27"};
        Bool_t  HLT_IsoTkMu18 = {fReader, "HLT_IsoTkMu18"};
        Bool_t  HLT_IsoTkMu20 = {fReader, "HLT_IsoTkMu20"};
        Bool_t  HLT_IsoTkMu22 = {fReader, "HLT_IsoTkMu22"};
        Bool_t  HLT_IsoTkMu22_eta2p1 = {fReader, "HLT_IsoTkMu22_eta2p1"};
        Bool_t  HLT_IsoTkMu24 = {fReader, "HLT_IsoTkMu24"};
        Bool_t  HLT_IsoTkMu27 = {fReader, "HLT_IsoTkMu27"};
        Bool_t  HLT_JetE30_NoBPTX3BX = {fReader, "HLT_JetE30_NoBPTX3BX"};
        Bool_t  HLT_JetE30_NoBPTX = {fReader, "HLT_JetE30_NoBPTX"};
        Bool_t  HLT_JetE50_NoBPTX3BX = {fReader, "HLT_JetE50_NoBPTX3BX"};
        Bool_t  HLT_JetE70_NoBPTX3BX = {fReader, "HLT_JetE70_NoBPTX3BX"};
        Bool_t  HLT_L1SingleMu18 = {fReader, "HLT_L1SingleMu18"};
        Bool_t  HLT_L2Mu10 = {fReader, "HLT_L2Mu10"};
        Bool_t  HLT_L1SingleMuOpen = {fReader, "HLT_L1SingleMuOpen"};
        Bool_t  HLT_L1SingleMuOpen_DT = {fReader, "HLT_L1SingleMuOpen_DT"};
        Bool_t  HLT_L2DoubleMu23_NoVertex = {fReader, "HLT_L2DoubleMu23_NoVertex"};
        Bool_t  HLT_L2DoubleMu28_NoVertex_2Cha_Angle2p5_Mass10 = {fReader, "HLT_L2DoubleMu28_NoVertex_2Cha_Angle2p5_Mass10"};
        Bool_t  HLT_L2DoubleMu38_NoVertex_2Cha_Angle2p5_Mass10 = {fReader, "HLT_L2DoubleMu38_NoVertex_2Cha_Angle2p5_Mass10"};
        Bool_t  HLT_L2Mu10_NoVertex_NoBPTX3BX = {fReader, "HLT_L2Mu10_NoVertex_NoBPTX3BX"};
        Bool_t  HLT_L2Mu10_NoVertex_NoBPTX = {fReader, "HLT_L2Mu10_NoVertex_NoBPTX"};
        Bool_t  HLT_L2Mu45_NoVertex_3Sta_NoBPTX3BX = {fReader, "HLT_L2Mu45_NoVertex_3Sta_NoBPTX3BX"};
        Bool_t  HLT_L2Mu40_NoVertex_3Sta_NoBPTX3BX = {fReader, "HLT_L2Mu40_NoVertex_3Sta_NoBPTX3BX"};
        Bool_t  HLT_LooseIsoPFTau50_Trk30_eta2p1 = {fReader, "HLT_LooseIsoPFTau50_Trk30_eta2p1"};
        Bool_t  HLT_LooseIsoPFTau50_Trk30_eta2p1_MET80 = {fReader, "HLT_LooseIsoPFTau50_Trk30_eta2p1_MET80"};
        Bool_t  HLT_LooseIsoPFTau50_Trk30_eta2p1_MET90 = {fReader, "HLT_LooseIsoPFTau50_Trk30_eta2p1_MET90"};
        Bool_t  HLT_LooseIsoPFTau50_Trk30_eta2p1_MET110 = {fReader, "HLT_LooseIsoPFTau50_Trk30_eta2p1_MET110"};
        Bool_t  HLT_LooseIsoPFTau50_Trk30_eta2p1_MET120 = {fReader, "HLT_LooseIsoPFTau50_Trk30_eta2p1_MET120"};
        Bool_t  HLT_PFTau120_eta2p1 = {fReader, "HLT_PFTau120_eta2p1"};
        Bool_t  HLT_PFTau140_eta2p1 = {fReader, "HLT_PFTau140_eta2p1"};
        Bool_t  HLT_VLooseIsoPFTau120_Trk50_eta2p1 = {fReader, "HLT_VLooseIsoPFTau120_Trk50_eta2p1"};
        Bool_t  HLT_VLooseIsoPFTau140_Trk50_eta2p1 = {fReader, "HLT_VLooseIsoPFTau140_Trk50_eta2p1"};
        Bool_t  HLT_Mu17_Mu8 = {fReader, "HLT_Mu17_Mu8"};
        Bool_t  HLT_Mu17_Mu8_DZ = {fReader, "HLT_Mu17_Mu8_DZ"};
        Bool_t  HLT_Mu17_Mu8_SameSign = {fReader, "HLT_Mu17_Mu8_SameSign"};
        Bool_t  HLT_Mu17_Mu8_SameSign_DZ = {fReader, "HLT_Mu17_Mu8_SameSign_DZ"};
        Bool_t  HLT_Mu20_Mu10 = {fReader, "HLT_Mu20_Mu10"};
        Bool_t  HLT_Mu20_Mu10_DZ = {fReader, "HLT_Mu20_Mu10_DZ"};
        Bool_t  HLT_Mu20_Mu10_SameSign = {fReader, "HLT_Mu20_Mu10_SameSign"};
        Bool_t  HLT_Mu20_Mu10_SameSign_DZ = {fReader, "HLT_Mu20_Mu10_SameSign_DZ"};
        Bool_t  HLT_Mu17_TkMu8_DZ = {fReader, "HLT_Mu17_TkMu8_DZ"};
        Bool_t  HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL = {fReader, "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL"};
        Bool_t  HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ = {fReader, "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ"};
        Bool_t  HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL = {fReader, "HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL"};
        Bool_t  HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ = {fReader, "HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ"};
        Bool_t  HLT_Mu25_TkMu0_dEta18_Onia = {fReader, "HLT_Mu25_TkMu0_dEta18_Onia"};
        Bool_t  HLT_Mu27_TkMu8 = {fReader, "HLT_Mu27_TkMu8"};
        Bool_t  HLT_Mu30_TkMu11 = {fReader, "HLT_Mu30_TkMu11"};
        Bool_t  HLT_Mu30_eta2p1_PFJet150_PFJet50 = {fReader, "HLT_Mu30_eta2p1_PFJet150_PFJet50"};
        Bool_t  HLT_Mu40_TkMu11 = {fReader, "HLT_Mu40_TkMu11"};
        Bool_t  HLT_Mu40_eta2p1_PFJet200_PFJet50 = {fReader, "HLT_Mu40_eta2p1_PFJet200_PFJet50"};
        Bool_t  HLT_Mu20 = {fReader, "HLT_Mu20"};
        Bool_t  HLT_TkMu17 = {fReader, "HLT_TkMu17"};
        Bool_t  HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL = {fReader, "HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL"};
        Bool_t  HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ = {fReader, "HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ"};
        Bool_t  HLT_TkMu20 = {fReader, "HLT_TkMu20"};
        Bool_t  HLT_Mu24_eta2p1 = {fReader, "HLT_Mu24_eta2p1"};
        Bool_t  HLT_TkMu24_eta2p1 = {fReader, "HLT_TkMu24_eta2p1"};
        Bool_t  HLT_Mu27 = {fReader, "HLT_Mu27"};
        Bool_t  HLT_TkMu27 = {fReader, "HLT_TkMu27"};
        Bool_t  HLT_Mu45_eta2p1 = {fReader, "HLT_Mu45_eta2p1"};
        Bool_t  HLT_Mu50 = {fReader, "HLT_Mu50"};
        Bool_t  HLT_TkMu50 = {fReader, "HLT_TkMu50"};
        Bool_t  HLT_Mu38NoFiltersNoVtx_Photon38_CaloIdL = {fReader, "HLT_Mu38NoFiltersNoVtx_Photon38_CaloIdL"};
        Bool_t  HLT_Mu42NoFiltersNoVtx_Photon42_CaloIdL = {fReader, "HLT_Mu42NoFiltersNoVtx_Photon42_CaloIdL"};
        Bool_t  HLT_Mu28NoFiltersNoVtxDisplaced_Photon28_CaloIdL = {fReader, "HLT_Mu28NoFiltersNoVtxDisplaced_Photon28_CaloIdL"};
        Bool_t  HLT_Mu33NoFiltersNoVtxDisplaced_Photon33_CaloIdL = {fReader, "HLT_Mu33NoFiltersNoVtxDisplaced_Photon33_CaloIdL"};
        Bool_t  HLT_Mu23NoFiltersNoVtx_Photon23_CaloIdL = {fReader, "HLT_Mu23NoFiltersNoVtx_Photon23_CaloIdL"};
        Bool_t  HLT_DoubleMu18NoFiltersNoVtx = {fReader, "HLT_DoubleMu18NoFiltersNoVtx"};
        Bool_t  HLT_Mu33NoFiltersNoVtxDisplaced_DisplacedJet50_Tight = {fReader, "HLT_Mu33NoFiltersNoVtxDisplaced_DisplacedJet50_Tight"};
        Bool_t  HLT_Mu33NoFiltersNoVtxDisplaced_DisplacedJet50_Loose = {fReader, "HLT_Mu33NoFiltersNoVtxDisplaced_DisplacedJet50_Loose"};
        Bool_t  HLT_Mu28NoFiltersNoVtx_DisplacedJet40_Loose = {fReader, "HLT_Mu28NoFiltersNoVtx_DisplacedJet40_Loose"};
        Bool_t  HLT_Mu38NoFiltersNoVtxDisplaced_DisplacedJet60_Tight = {fReader, "HLT_Mu38NoFiltersNoVtxDisplaced_DisplacedJet60_Tight"};
        Bool_t  HLT_Mu38NoFiltersNoVtxDisplaced_DisplacedJet60_Loose = {fReader, "HLT_Mu38NoFiltersNoVtxDisplaced_DisplacedJet60_Loose"};
        Bool_t  HLT_Mu38NoFiltersNoVtx_DisplacedJet60_Loose = {fReader, "HLT_Mu38NoFiltersNoVtx_DisplacedJet60_Loose"};
        Bool_t  HLT_Mu28NoFiltersNoVtx_CentralCaloJet40 = {fReader, "HLT_Mu28NoFiltersNoVtx_CentralCaloJet40"};
        Bool_t  HLT_PFHT300_PFMET100 = {fReader, "HLT_PFHT300_PFMET100"};
        Bool_t  HLT_PFHT300_PFMET110 = {fReader, "HLT_PFHT300_PFMET110"};
        Bool_t  HLT_PFHT550_4JetPt50 = {fReader, "HLT_PFHT550_4JetPt50"};
        Bool_t  HLT_PFHT650_4JetPt50 = {fReader, "HLT_PFHT650_4JetPt50"};
        Bool_t  HLT_PFHT750_4JetPt50 = {fReader, "HLT_PFHT750_4JetPt50"};
        Bool_t  HLT_PFHT750_4JetPt70 = {fReader, "HLT_PFHT750_4JetPt70"};
        Bool_t  HLT_PFHT750_4JetPt80 = {fReader, "HLT_PFHT750_4JetPt80"};
        Bool_t  HLT_PFHT800_4JetPt50 = {fReader, "HLT_PFHT800_4JetPt50"};
        Bool_t  HLT_PFHT850_4JetPt50 = {fReader, "HLT_PFHT850_4JetPt50"};
        Bool_t  HLT_PFJet15_NoCaloMatched = {fReader, "HLT_PFJet15_NoCaloMatched"};
        Bool_t  HLT_PFJet25_NoCaloMatched = {fReader, "HLT_PFJet25_NoCaloMatched"};
        Bool_t  HLT_DiPFJet15_NoCaloMatched = {fReader, "HLT_DiPFJet15_NoCaloMatched"};
        Bool_t  HLT_DiPFJet25_NoCaloMatched = {fReader, "HLT_DiPFJet25_NoCaloMatched"};
        Bool_t  HLT_DiPFJet15_FBEta3_NoCaloMatched = {fReader, "HLT_DiPFJet15_FBEta3_NoCaloMatched"};
        Bool_t  HLT_DiPFJet25_FBEta3_NoCaloMatched = {fReader, "HLT_DiPFJet25_FBEta3_NoCaloMatched"};
        Bool_t  HLT_DiPFJetAve15_HFJEC = {fReader, "HLT_DiPFJetAve15_HFJEC"};
        Bool_t  HLT_DiPFJetAve25_HFJEC = {fReader, "HLT_DiPFJetAve25_HFJEC"};
        Bool_t  HLT_DiPFJetAve35_HFJEC = {fReader, "HLT_DiPFJetAve35_HFJEC"};
        Bool_t  HLT_PFJet40 = {fReader, "HLT_PFJet40"};
        Bool_t  HLT_PFJet60 = {fReader, "HLT_PFJet60"};
        Bool_t  HLT_PFJet80 = {fReader, "HLT_PFJet80"};
        Bool_t  HLT_PFJet140 = {fReader, "HLT_PFJet140"};
        Bool_t  HLT_PFJet200 = {fReader, "HLT_PFJet200"};
        Bool_t  HLT_PFJet260 = {fReader, "HLT_PFJet260"};
        Bool_t  HLT_PFJet320 = {fReader, "HLT_PFJet320"};
        Bool_t  HLT_PFJet400 = {fReader, "HLT_PFJet400"};
        Bool_t  HLT_PFJet450 = {fReader, "HLT_PFJet450"};
        Bool_t  HLT_PFJet500 = {fReader, "HLT_PFJet500"};
        Bool_t  HLT_DiPFJetAve40 = {fReader, "HLT_DiPFJetAve40"};
        Bool_t  HLT_DiPFJetAve60 = {fReader, "HLT_DiPFJetAve60"};
        Bool_t  HLT_DiPFJetAve80 = {fReader, "HLT_DiPFJetAve80"};
        Bool_t  HLT_DiPFJetAve140 = {fReader, "HLT_DiPFJetAve140"};
        Bool_t  HLT_DiPFJetAve200 = {fReader, "HLT_DiPFJetAve200"};
        Bool_t  HLT_DiPFJetAve260 = {fReader, "HLT_DiPFJetAve260"};
        Bool_t  HLT_DiPFJetAve320 = {fReader, "HLT_DiPFJetAve320"};
        Bool_t  HLT_DiPFJetAve400 = {fReader, "HLT_DiPFJetAve400"};
        Bool_t  HLT_DiPFJetAve500 = {fReader, "HLT_DiPFJetAve500"};
        Bool_t  HLT_DiPFJetAve60_HFJEC = {fReader, "HLT_DiPFJetAve60_HFJEC"};
        Bool_t  HLT_DiPFJetAve80_HFJEC = {fReader, "HLT_DiPFJetAve80_HFJEC"};
        Bool_t  HLT_DiPFJetAve100_HFJEC = {fReader, "HLT_DiPFJetAve100_HFJEC"};
        Bool_t  HLT_DiPFJetAve160_HFJEC = {fReader, "HLT_DiPFJetAve160_HFJEC"};
        Bool_t  HLT_DiPFJetAve220_HFJEC = {fReader, "HLT_DiPFJetAve220_HFJEC"};
        Bool_t  HLT_DiPFJetAve300_HFJEC = {fReader, "HLT_DiPFJetAve300_HFJEC"};
        Bool_t  HLT_DiPFJet40_DEta3p5_MJJ600_PFMETNoMu140 = {fReader, "HLT_DiPFJet40_DEta3p5_MJJ600_PFMETNoMu140"};
        Bool_t  HLT_DiPFJet40_DEta3p5_MJJ600_PFMETNoMu80 = {fReader, "HLT_DiPFJet40_DEta3p5_MJJ600_PFMETNoMu80"};
        Bool_t  HLT_DiCentralPFJet170 = {fReader, "HLT_DiCentralPFJet170"};
        Bool_t  HLT_SingleCentralPFJet170_CFMax0p1 = {fReader, "HLT_SingleCentralPFJet170_CFMax0p1"};
        Bool_t  HLT_DiCentralPFJet170_CFMax0p1 = {fReader, "HLT_DiCentralPFJet170_CFMax0p1"};
        Bool_t  HLT_DiCentralPFJet220_CFMax0p3 = {fReader, "HLT_DiCentralPFJet220_CFMax0p3"};
        Bool_t  HLT_DiCentralPFJet330_CFMax0p5 = {fReader, "HLT_DiCentralPFJet330_CFMax0p5"};
        Bool_t  HLT_DiCentralPFJet430 = {fReader, "HLT_DiCentralPFJet430"};
        Bool_t  HLT_PFHT125 = {fReader, "HLT_PFHT125"};
        Bool_t  HLT_PFHT200 = {fReader, "HLT_PFHT200"};
        Bool_t  HLT_PFHT250 = {fReader, "HLT_PFHT250"};
        Bool_t  HLT_PFHT300 = {fReader, "HLT_PFHT300"};
        Bool_t  HLT_PFHT350 = {fReader, "HLT_PFHT350"};
        Bool_t  HLT_PFHT400 = {fReader, "HLT_PFHT400"};
        Bool_t  HLT_PFHT475 = {fReader, "HLT_PFHT475"};
        Bool_t  HLT_PFHT600 = {fReader, "HLT_PFHT600"};
        Bool_t  HLT_PFHT650 = {fReader, "HLT_PFHT650"};
        Bool_t  HLT_PFHT800 = {fReader, "HLT_PFHT800"};
        Bool_t  HLT_PFHT900 = {fReader, "HLT_PFHT900"};
        Bool_t  HLT_PFHT200_PFAlphaT0p51 = {fReader, "HLT_PFHT200_PFAlphaT0p51"};
        Bool_t  HLT_PFHT200_DiPFJetAve90_PFAlphaT0p57 = {fReader, "HLT_PFHT200_DiPFJetAve90_PFAlphaT0p57"};
        Bool_t  HLT_PFHT200_DiPFJetAve90_PFAlphaT0p63 = {fReader, "HLT_PFHT200_DiPFJetAve90_PFAlphaT0p63"};
        Bool_t  HLT_PFHT250_DiPFJetAve90_PFAlphaT0p55 = {fReader, "HLT_PFHT250_DiPFJetAve90_PFAlphaT0p55"};
        Bool_t  HLT_PFHT250_DiPFJetAve90_PFAlphaT0p58 = {fReader, "HLT_PFHT250_DiPFJetAve90_PFAlphaT0p58"};
        Bool_t  HLT_PFHT300_DiPFJetAve90_PFAlphaT0p53 = {fReader, "HLT_PFHT300_DiPFJetAve90_PFAlphaT0p53"};
        Bool_t  HLT_PFHT300_DiPFJetAve90_PFAlphaT0p54 = {fReader, "HLT_PFHT300_DiPFJetAve90_PFAlphaT0p54"};
        Bool_t  HLT_PFHT350_DiPFJetAve90_PFAlphaT0p52 = {fReader, "HLT_PFHT350_DiPFJetAve90_PFAlphaT0p52"};
        Bool_t  HLT_PFHT350_DiPFJetAve90_PFAlphaT0p53 = {fReader, "HLT_PFHT350_DiPFJetAve90_PFAlphaT0p53"};
        Bool_t  HLT_PFHT400_DiPFJetAve90_PFAlphaT0p51 = {fReader, "HLT_PFHT400_DiPFJetAve90_PFAlphaT0p51"};
        Bool_t  HLT_PFHT400_DiPFJetAve90_PFAlphaT0p52 = {fReader, "HLT_PFHT400_DiPFJetAve90_PFAlphaT0p52"};
        Bool_t  HLT_MET60_IsoTrk35_Loose = {fReader, "HLT_MET60_IsoTrk35_Loose"};
        Bool_t  HLT_MET75_IsoTrk50 = {fReader, "HLT_MET75_IsoTrk50"};
        Bool_t  HLT_MET90_IsoTrk50 = {fReader, "HLT_MET90_IsoTrk50"};
        Bool_t  HLT_PFMET120_BTagCSV_p067 = {fReader, "HLT_PFMET120_BTagCSV_p067"};
        Bool_t  HLT_PFMET120_Mu5 = {fReader, "HLT_PFMET120_Mu5"};
        Bool_t  HLT_PFMET170_NotCleaned = {fReader, "HLT_PFMET170_NotCleaned"};
        Bool_t  HLT_PFMET170_NoiseCleaned = {fReader, "HLT_PFMET170_NoiseCleaned"};
        Bool_t  HLT_PFMET170_HBHECleaned = {fReader, "HLT_PFMET170_HBHECleaned"};
        Bool_t  HLT_PFMET170_JetIdCleaned = {fReader, "HLT_PFMET170_JetIdCleaned"};
        Bool_t  HLT_PFMET170_BeamHaloCleaned = {fReader, "HLT_PFMET170_BeamHaloCleaned"};
        Bool_t  HLT_PFMET170_HBHE_BeamHaloCleaned = {fReader, "HLT_PFMET170_HBHE_BeamHaloCleaned"};
        Bool_t  HLT_PFMETTypeOne190_HBHE_BeamHaloCleaned = {fReader, "HLT_PFMETTypeOne190_HBHE_BeamHaloCleaned"};
        Bool_t  HLT_PFMET90_PFMHT90_IDTight = {fReader, "HLT_PFMET90_PFMHT90_IDTight"};
        Bool_t  HLT_PFMET100_PFMHT100_IDTight = {fReader, "HLT_PFMET100_PFMHT100_IDTight"};
        Bool_t  HLT_PFMET100_PFMHT100_IDTight_BeamHaloCleaned = {fReader, "HLT_PFMET100_PFMHT100_IDTight_BeamHaloCleaned"};
        Bool_t  HLT_PFMET110_PFMHT110_IDTight = {fReader, "HLT_PFMET110_PFMHT110_IDTight"};
        Bool_t  HLT_PFMET120_PFMHT120_IDTight = {fReader, "HLT_PFMET120_PFMHT120_IDTight"};
        Bool_t  HLT_CaloMHTNoPU90_PFMET90_PFMHT90_IDTight_BTagCSV_p067 = {fReader, "HLT_CaloMHTNoPU90_PFMET90_PFMHT90_IDTight_BTagCSV_p067"};
        Bool_t  HLT_CaloMHTNoPU90_PFMET90_PFMHT90_IDTight = {fReader, "HLT_CaloMHTNoPU90_PFMET90_PFMHT90_IDTight"};
        Bool_t  HLT_DoubleJet90_Double30_TripleBTagCSV_p087 = {fReader, "HLT_DoubleJet90_Double30_TripleBTagCSV_p087"};
        Bool_t  HLT_DoubleJet90_Double30_DoubleBTagCSV_p087 = {fReader, "HLT_DoubleJet90_Double30_DoubleBTagCSV_p087"};
        Bool_t  HLT_DoubleJetsC100_DoubleBTagCSV_p026_DoublePFJetsC160 = {fReader, "HLT_DoubleJetsC100_DoubleBTagCSV_p026_DoublePFJetsC160"};
        Bool_t  HLT_DoubleJetsC100_DoubleBTagCSV_p014_DoublePFJetsC100MaxDeta1p6 = {fReader, "HLT_DoubleJetsC100_DoubleBTagCSV_p014_DoublePFJetsC100MaxDeta1p6"};
        Bool_t  HLT_DoubleJetsC112_DoubleBTagCSV_p026_DoublePFJetsC172 = {fReader, "HLT_DoubleJetsC112_DoubleBTagCSV_p026_DoublePFJetsC172"};
        Bool_t  HLT_DoubleJetsC112_DoubleBTagCSV_p014_DoublePFJetsC112MaxDeta1p6 = {fReader, "HLT_DoubleJetsC112_DoubleBTagCSV_p014_DoublePFJetsC112MaxDeta1p6"};
        Bool_t  HLT_DoubleJetsC100_SingleBTagCSV_p026 = {fReader, "HLT_DoubleJetsC100_SingleBTagCSV_p026"};
        Bool_t  HLT_DoubleJetsC100_SingleBTagCSV_p014 = {fReader, "HLT_DoubleJetsC100_SingleBTagCSV_p014"};
        Bool_t  HLT_DoubleJetsC100_SingleBTagCSV_p026_SinglePFJetC350 = {fReader, "HLT_DoubleJetsC100_SingleBTagCSV_p026_SinglePFJetC350"};
        Bool_t  HLT_DoubleJetsC100_SingleBTagCSV_p014_SinglePFJetC350 = {fReader, "HLT_DoubleJetsC100_SingleBTagCSV_p014_SinglePFJetC350"};
        Bool_t  HLT_Mu8_TrkIsoVVL = {fReader, "HLT_Mu8_TrkIsoVVL"};
        Bool_t  HLT_Mu17_TrkIsoVVL = {fReader, "HLT_Mu17_TrkIsoVVL"};
        Bool_t  HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30 = {fReader, "HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30"};
        Bool_t  HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30 = {fReader, "HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30"};
        Bool_t  HLT_Ele17_CaloIdL_TrackIdL_IsoVL_PFJet30 = {fReader, "HLT_Ele17_CaloIdL_TrackIdL_IsoVL_PFJet30"};
        Bool_t  HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30 = {fReader, "HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30"};
        Bool_t  HLT_BTagMu_DiJet20_Mu5 = {fReader, "HLT_BTagMu_DiJet20_Mu5"};
        Bool_t  HLT_BTagMu_DiJet40_Mu5 = {fReader, "HLT_BTagMu_DiJet40_Mu5"};
        Bool_t  HLT_BTagMu_DiJet70_Mu5 = {fReader, "HLT_BTagMu_DiJet70_Mu5"};
        Bool_t  HLT_BTagMu_DiJet110_Mu5 = {fReader, "HLT_BTagMu_DiJet110_Mu5"};
        Bool_t  HLT_BTagMu_DiJet170_Mu5 = {fReader, "HLT_BTagMu_DiJet170_Mu5"};
        Bool_t  HLT_BTagMu_Jet300_Mu5 = {fReader, "HLT_BTagMu_Jet300_Mu5"};
        Bool_t  HLT_BTagMu_AK8Jet300_Mu5 = {fReader, "HLT_BTagMu_AK8Jet300_Mu5"};
        Bool_t  HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ = {fReader, "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ"};
        Bool_t  HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_L1JetTauSeeded = {fReader, "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_L1JetTauSeeded"};
        Bool_t  HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ = {fReader, "HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ"};
        Bool_t  HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL = {fReader, "HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL"};
        Bool_t  HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL = {fReader, "HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL"};
        Bool_t  HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL = {fReader, "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL"};
        Bool_t  HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ = {fReader, "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ"};
        Bool_t  HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL = {fReader, "HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL"};
        Bool_t  HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ = {fReader, "HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ"};
        Bool_t  HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL = {fReader, "HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL"};
        Bool_t  HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL = {fReader, "HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL"};
        Bool_t  HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ = {fReader, "HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ"};
        Bool_t  HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL = {fReader, "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL"};
        Bool_t  HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ = {fReader, "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ"};
        Bool_t  HLT_Mu30_Ele30_CaloIdL_GsfTrkIdVL = {fReader, "HLT_Mu30_Ele30_CaloIdL_GsfTrkIdVL"};
        Bool_t  HLT_Mu33_Ele33_CaloIdL_GsfTrkIdVL = {fReader, "HLT_Mu33_Ele33_CaloIdL_GsfTrkIdVL"};
        Bool_t  HLT_Mu37_Ele27_CaloIdL_GsfTrkIdVL = {fReader, "HLT_Mu37_Ele27_CaloIdL_GsfTrkIdVL"};
        Bool_t  HLT_Mu27_Ele37_CaloIdL_GsfTrkIdVL = {fReader, "HLT_Mu27_Ele37_CaloIdL_GsfTrkIdVL"};
        Bool_t  HLT_Mu8_DiEle12_CaloIdL_TrackIdL = {fReader, "HLT_Mu8_DiEle12_CaloIdL_TrackIdL"};
        Bool_t  HLT_Mu12_Photon25_CaloIdL = {fReader, "HLT_Mu12_Photon25_CaloIdL"};
        Bool_t  HLT_Mu12_Photon25_CaloIdL_L1ISO = {fReader, "HLT_Mu12_Photon25_CaloIdL_L1ISO"};
        Bool_t  HLT_Mu12_Photon25_CaloIdL_L1OR = {fReader, "HLT_Mu12_Photon25_CaloIdL_L1OR"};
        Bool_t  HLT_Mu17_Photon22_CaloIdL_L1ISO = {fReader, "HLT_Mu17_Photon22_CaloIdL_L1ISO"};
        Bool_t  HLT_Mu17_Photon30_CaloIdL_L1ISO = {fReader, "HLT_Mu17_Photon30_CaloIdL_L1ISO"};
        Bool_t  HLT_Mu17_Photon35_CaloIdL_L1ISO = {fReader, "HLT_Mu17_Photon35_CaloIdL_L1ISO"};
        Bool_t  HLT_DiMu9_Ele9_CaloIdL_TrackIdL = {fReader, "HLT_DiMu9_Ele9_CaloIdL_TrackIdL"};
        Bool_t  HLT_TripleMu_5_3_3 = {fReader, "HLT_TripleMu_5_3_3"};
        Bool_t  HLT_TripleMu_12_10_5 = {fReader, "HLT_TripleMu_12_10_5"};
        Bool_t  HLT_Mu3er_PFHT140_PFMET125 = {fReader, "HLT_Mu3er_PFHT140_PFMET125"};
        Bool_t  HLT_Mu6_PFHT200_PFMET80_BTagCSV_p067 = {fReader, "HLT_Mu6_PFHT200_PFMET80_BTagCSV_p067"};
        Bool_t  HLT_Mu6_PFHT200_PFMET100 = {fReader, "HLT_Mu6_PFHT200_PFMET100"};
        Bool_t  HLT_Mu14er_PFMET100 = {fReader, "HLT_Mu14er_PFMET100"};
        Bool_t  HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL = {fReader, "HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL"};
        Bool_t  HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL = {fReader, "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL"};
        Bool_t  HLT_Ele12_CaloIdL_TrackIdL_IsoVL = {fReader, "HLT_Ele12_CaloIdL_TrackIdL_IsoVL"};
        Bool_t  HLT_Ele17_CaloIdL_GsfTrkIdVL = {fReader, "HLT_Ele17_CaloIdL_GsfTrkIdVL"};
        Bool_t  HLT_Ele17_CaloIdL_TrackIdL_IsoVL = {fReader, "HLT_Ele17_CaloIdL_TrackIdL_IsoVL"};
        Bool_t  HLT_Ele23_CaloIdL_TrackIdL_IsoVL = {fReader, "HLT_Ele23_CaloIdL_TrackIdL_IsoVL"};
        Bool_t  HLT_PFHT650_WideJetMJJ900DEtaJJ1p5 = {fReader, "HLT_PFHT650_WideJetMJJ900DEtaJJ1p5"};
        Bool_t  HLT_PFHT650_WideJetMJJ950DEtaJJ1p5 = {fReader, "HLT_PFHT650_WideJetMJJ950DEtaJJ1p5"};
        Bool_t  HLT_Dimuon0_Jpsi_Muon = {fReader, "HLT_Dimuon0_Jpsi_Muon"};
        Bool_t  HLT_Dimuon0_Upsilon_Muon = {fReader, "HLT_Dimuon0_Upsilon_Muon"};
        Bool_t  HLT_HT200_DisplacedDijet40_DisplacedTrack = {fReader, "HLT_HT200_DisplacedDijet40_DisplacedTrack"};
        Bool_t  HLT_HT250_DisplacedDijet40_DisplacedTrack = {fReader, "HLT_HT250_DisplacedDijet40_DisplacedTrack"};
        Bool_t  HLT_HT350_DisplacedDijet40_DisplacedTrack = {fReader, "HLT_HT350_DisplacedDijet40_DisplacedTrack"};
        Bool_t  HLT_HT350_DisplacedDijet80_DisplacedTrack = {fReader, "HLT_HT350_DisplacedDijet80_DisplacedTrack"};
        Bool_t  HLT_HT350_DisplacedDijet80_Tight_DisplacedTrack = {fReader, "HLT_HT350_DisplacedDijet80_Tight_DisplacedTrack"};
        Bool_t  HLT_HT350_DisplacedDijet40_Inclusive = {fReader, "HLT_HT350_DisplacedDijet40_Inclusive"};
        Bool_t  HLT_HT400_DisplacedDijet40_Inclusive = {fReader, "HLT_HT400_DisplacedDijet40_Inclusive"};
        Bool_t  HLT_HT500_DisplacedDijet40_Inclusive = {fReader, "HLT_HT500_DisplacedDijet40_Inclusive"};
        Bool_t  HLT_HT550_DisplacedDijet40_Inclusive = {fReader, "HLT_HT550_DisplacedDijet40_Inclusive"};
        Bool_t  HLT_HT550_DisplacedDijet80_Inclusive = {fReader, "HLT_HT550_DisplacedDijet80_Inclusive"};
        Bool_t  HLT_HT650_DisplacedDijet80_Inclusive = {fReader, "HLT_HT650_DisplacedDijet80_Inclusive"};
        Bool_t  HLT_HT750_DisplacedDijet80_Inclusive = {fReader, "HLT_HT750_DisplacedDijet80_Inclusive"};
        Bool_t  HLT_VBF_DisplacedJet40_DisplacedTrack = {fReader, "HLT_VBF_DisplacedJet40_DisplacedTrack"};
        Bool_t  HLT_VBF_DisplacedJet40_DisplacedTrack_2TrackIP2DSig5 = {fReader, "HLT_VBF_DisplacedJet40_DisplacedTrack_2TrackIP2DSig5"};
        Bool_t  HLT_VBF_DisplacedJet40_TightID_DisplacedTrack = {fReader, "HLT_VBF_DisplacedJet40_TightID_DisplacedTrack"};
        Bool_t  HLT_VBF_DisplacedJet40_Hadronic = {fReader, "HLT_VBF_DisplacedJet40_Hadronic"};
        Bool_t  HLT_VBF_DisplacedJet40_Hadronic_2PromptTrack = {fReader, "HLT_VBF_DisplacedJet40_Hadronic_2PromptTrack"};
        Bool_t  HLT_VBF_DisplacedJet40_TightID_Hadronic = {fReader, "HLT_VBF_DisplacedJet40_TightID_Hadronic"};
        Bool_t  HLT_VBF_DisplacedJet40_VTightID_Hadronic = {fReader, "HLT_VBF_DisplacedJet40_VTightID_Hadronic"};
        Bool_t  HLT_VBF_DisplacedJet40_VVTightID_Hadronic = {fReader, "HLT_VBF_DisplacedJet40_VVTightID_Hadronic"};
        Bool_t  HLT_VBF_DisplacedJet40_VTightID_DisplacedTrack = {fReader, "HLT_VBF_DisplacedJet40_VTightID_DisplacedTrack"};
        Bool_t  HLT_VBF_DisplacedJet40_VVTightID_DisplacedTrack = {fReader, "HLT_VBF_DisplacedJet40_VVTightID_DisplacedTrack"};
        Bool_t  HLT_PFMETNoMu90_PFMHTNoMu90_IDTight = {fReader, "HLT_PFMETNoMu90_PFMHTNoMu90_IDTight"};
        Bool_t  HLT_PFMETNoMu100_PFMHTNoMu100_IDTight = {fReader, "HLT_PFMETNoMu100_PFMHTNoMu100_IDTight"};
        Bool_t  HLT_PFMETNoMu110_PFMHTNoMu110_IDTight = {fReader, "HLT_PFMETNoMu110_PFMHTNoMu110_IDTight"};
        Bool_t  HLT_PFMETNoMu120_PFMHTNoMu120_IDTight = {fReader, "HLT_PFMETNoMu120_PFMHTNoMu120_IDTight"};
        Bool_t  HLT_MonoCentralPFJet80_PFMETNoMu90_PFMHTNoMu90_IDTight = {fReader, "HLT_MonoCentralPFJet80_PFMETNoMu90_PFMHTNoMu90_IDTight"};
        Bool_t  HLT_MonoCentralPFJet80_PFMETNoMu100_PFMHTNoMu100_IDTight = {fReader, "HLT_MonoCentralPFJet80_PFMETNoMu100_PFMHTNoMu100_IDTight"};
        Bool_t  HLT_MonoCentralPFJet80_PFMETNoMu110_PFMHTNoMu110_IDTight = {fReader, "HLT_MonoCentralPFJet80_PFMETNoMu110_PFMHTNoMu110_IDTight"};
        Bool_t  HLT_MonoCentralPFJet80_PFMETNoMu120_PFMHTNoMu120_IDTight = {fReader, "HLT_MonoCentralPFJet80_PFMETNoMu120_PFMHTNoMu120_IDTight"};
        Bool_t  HLT_Ele27_eta2p1_WPLoose_Gsf_HT200 = {fReader, "HLT_Ele27_eta2p1_WPLoose_Gsf_HT200"};
        Bool_t  HLT_Photon90_CaloIdL_PFHT500 = {fReader, "HLT_Photon90_CaloIdL_PFHT500"};
        Bool_t  HLT_DoubleMu8_Mass8_PFHT250 = {fReader, "HLT_DoubleMu8_Mass8_PFHT250"};
        Bool_t  HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT250 = {fReader, "HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT250"};
        Bool_t  HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT250 = {fReader, "HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT250"};
        Bool_t  HLT_DoubleMu8_Mass8_PFHT300 = {fReader, "HLT_DoubleMu8_Mass8_PFHT300"};
        Bool_t  HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT300 = {fReader, "HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT300"};
        Bool_t  HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT300 = {fReader, "HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT300"};
        Bool_t  HLT_Mu10_CentralPFJet30_BTagCSV_p13 = {fReader, "HLT_Mu10_CentralPFJet30_BTagCSV_p13"};
        Bool_t  HLT_DoubleMu3_PFMET50 = {fReader, "HLT_DoubleMu3_PFMET50"};
        Bool_t  HLT_Ele10_CaloIdM_TrackIdM_CentralPFJet30_BTagCSV_p13 = {fReader, "HLT_Ele10_CaloIdM_TrackIdM_CentralPFJet30_BTagCSV_p13"};
        Bool_t  HLT_Ele15_IsoVVVL_BTagCSV_p067_PFHT400 = {fReader, "HLT_Ele15_IsoVVVL_BTagCSV_p067_PFHT400"};
        Bool_t  HLT_Ele15_IsoVVVL_PFHT350_PFMET50 = {fReader, "HLT_Ele15_IsoVVVL_PFHT350_PFMET50"};
        Bool_t  HLT_Ele15_IsoVVVL_PFHT600 = {fReader, "HLT_Ele15_IsoVVVL_PFHT600"};
        Bool_t  HLT_Ele15_IsoVVVL_PFHT350 = {fReader, "HLT_Ele15_IsoVVVL_PFHT350"};
        Bool_t  HLT_Ele15_IsoVVVL_PFHT400_PFMET50 = {fReader, "HLT_Ele15_IsoVVVL_PFHT400_PFMET50"};
        Bool_t  HLT_Ele15_IsoVVVL_PFHT400 = {fReader, "HLT_Ele15_IsoVVVL_PFHT400"};
        Bool_t  HLT_Ele50_IsoVVVL_PFHT400 = {fReader, "HLT_Ele50_IsoVVVL_PFHT400"};
        Bool_t  HLT_Mu8_TrkIsoVVL_DiPFJet40_DEta3p5_MJJ750_HTT300_PFMETNoMu60 = {fReader, "HLT_Mu8_TrkIsoVVL_DiPFJet40_DEta3p5_MJJ750_HTT300_PFMETNoMu60"};
        Bool_t  HLT_Mu10_TrkIsoVVL_DiPFJet40_DEta3p5_MJJ750_HTT350_PFMETNoMu60 = {fReader, "HLT_Mu10_TrkIsoVVL_DiPFJet40_DEta3p5_MJJ750_HTT350_PFMETNoMu60"};
        Bool_t  HLT_Mu15_IsoVVVL_BTagCSV_p067_PFHT400 = {fReader, "HLT_Mu15_IsoVVVL_BTagCSV_p067_PFHT400"};
        Bool_t  HLT_Mu15_IsoVVVL_PFHT350_PFMET50 = {fReader, "HLT_Mu15_IsoVVVL_PFHT350_PFMET50"};
        Bool_t  HLT_Mu15_IsoVVVL_PFHT600 = {fReader, "HLT_Mu15_IsoVVVL_PFHT600"};
        Bool_t  HLT_Mu15_IsoVVVL_PFHT350 = {fReader, "HLT_Mu15_IsoVVVL_PFHT350"};
        Bool_t  HLT_Mu15_IsoVVVL_PFHT400_PFMET50 = {fReader, "HLT_Mu15_IsoVVVL_PFHT400_PFMET50"};
        Bool_t  HLT_Mu15_IsoVVVL_PFHT400 = {fReader, "HLT_Mu15_IsoVVVL_PFHT400"};
        Bool_t  HLT_Mu50_IsoVVVL_PFHT400 = {fReader, "HLT_Mu50_IsoVVVL_PFHT400"};
        Bool_t  HLT_Dimuon16_Jpsi = {fReader, "HLT_Dimuon16_Jpsi"};
        Bool_t  HLT_Dimuon10_Jpsi_Barrel = {fReader, "HLT_Dimuon10_Jpsi_Barrel"};
        Bool_t  HLT_Dimuon8_PsiPrime_Barrel = {fReader, "HLT_Dimuon8_PsiPrime_Barrel"};
        Bool_t  HLT_Dimuon8_Upsilon_Barrel = {fReader, "HLT_Dimuon8_Upsilon_Barrel"};
        Bool_t  HLT_Dimuon0_Phi_Barrel = {fReader, "HLT_Dimuon0_Phi_Barrel"};
        Bool_t  HLT_Mu16_TkMu0_dEta18_Onia = {fReader, "HLT_Mu16_TkMu0_dEta18_Onia"};
        Bool_t  HLT_Mu16_TkMu0_dEta18_Phi = {fReader, "HLT_Mu16_TkMu0_dEta18_Phi"};
        Bool_t  HLT_TrkMu15_DoubleTrkMu5NoFiltersNoVtx = {fReader, "HLT_TrkMu15_DoubleTrkMu5NoFiltersNoVtx"};
        Bool_t  HLT_TrkMu17_DoubleTrkMu8NoFiltersNoVtx = {fReader, "HLT_TrkMu17_DoubleTrkMu8NoFiltersNoVtx"};
        Bool_t  HLT_Mu8 = {fReader, "HLT_Mu8"};
        Bool_t  HLT_Mu17 = {fReader, "HLT_Mu17"};
        Bool_t  HLT_Mu3_PFJet40 = {fReader, "HLT_Mu3_PFJet40"};
        Bool_t  HLT_Ele8_CaloIdM_TrackIdM_PFJet30 = {fReader, "HLT_Ele8_CaloIdM_TrackIdM_PFJet30"};
        Bool_t  HLT_Ele12_CaloIdM_TrackIdM_PFJet30 = {fReader, "HLT_Ele12_CaloIdM_TrackIdM_PFJet30"};
        Bool_t  HLT_Ele17_CaloIdM_TrackIdM_PFJet30 = {fReader, "HLT_Ele17_CaloIdM_TrackIdM_PFJet30"};
        Bool_t  HLT_Ele23_CaloIdM_TrackIdM_PFJet30 = {fReader, "HLT_Ele23_CaloIdM_TrackIdM_PFJet30"};
        Bool_t  HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet140 = {fReader, "HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet140"};
        Bool_t  HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet165 = {fReader, "HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet165"};
        Bool_t  HLT_PFHT400_SixJet30_DoubleBTagCSV_p056 = {fReader, "HLT_PFHT400_SixJet30_DoubleBTagCSV_p056"};
        Bool_t  HLT_PFHT450_SixJet40_BTagCSV_p056 = {fReader, "HLT_PFHT450_SixJet40_BTagCSV_p056"};
        Bool_t  HLT_PFHT400_SixJet30 = {fReader, "HLT_PFHT400_SixJet30"};
        Bool_t  HLT_PFHT450_SixJet40 = {fReader, "HLT_PFHT450_SixJet40"};
        Bool_t  HLT_Ele115_CaloIdVT_GsfTrkIdT = {fReader, "HLT_Ele115_CaloIdVT_GsfTrkIdT"};
        Bool_t  HLT_Mu55 = {fReader, "HLT_Mu55"};
        Bool_t  HLT_Photon42_R9Id85_OR_CaloId24b40e_Iso50T80L_Photon25_AND_HE10_R9Id65_Eta2_Mass15 = {fReader, "HLT_Photon42_R9Id85_OR_CaloId24b40e_Iso50T80L_Photon25_AND_HE10_R9Id65_Eta2_Mass15"};
        Bool_t  HLT_Photon90_CaloIdL_PFHT600 = {fReader, "HLT_Photon90_CaloIdL_PFHT600"};
        Bool_t  HLT_PixelTracks_Multiplicity60ForEndOfFill = {fReader, "HLT_PixelTracks_Multiplicity60ForEndOfFill"};
        Bool_t  HLT_PixelTracks_Multiplicity85ForEndOfFill = {fReader, "HLT_PixelTracks_Multiplicity85ForEndOfFill"};
        Bool_t  HLT_PixelTracks_Multiplicity110ForEndOfFill = {fReader, "HLT_PixelTracks_Multiplicity110ForEndOfFill"};
        Bool_t  HLT_PixelTracks_Multiplicity135ForEndOfFill = {fReader, "HLT_PixelTracks_Multiplicity135ForEndOfFill"};
        Bool_t  HLT_PixelTracks_Multiplicity160ForEndOfFill = {fReader, "HLT_PixelTracks_Multiplicity160ForEndOfFill"};
        Bool_t  HLT_FullTracks_Multiplicity80 = {fReader, "HLT_FullTracks_Multiplicity80"};
        Bool_t  HLT_FullTracks_Multiplicity100 = {fReader, "HLT_FullTracks_Multiplicity100"};
        Bool_t  HLT_FullTracks_Multiplicity130 = {fReader, "HLT_FullTracks_Multiplicity130"};
        Bool_t  HLT_FullTracks_Multiplicity150 = {fReader, "HLT_FullTracks_Multiplicity150"};
        Bool_t  HLT_ECALHT800 = {fReader, "HLT_ECALHT800"};
        Bool_t  HLT_DiSC30_18_EIso_AND_HE_Mass70 = {fReader, "HLT_DiSC30_18_EIso_AND_HE_Mass70"};
        Bool_t  HLT_Photon125 = {fReader, "HLT_Photon125"};
        Bool_t  HLT_MET100 = {fReader, "HLT_MET100"};
        Bool_t  HLT_MET150 = {fReader, "HLT_MET150"};
        Bool_t  HLT_MET200 = {fReader, "HLT_MET200"};
        Bool_t  HLT_Ele27_HighEta_Ele20_Mass55 = {fReader, "HLT_Ele27_HighEta_Ele20_Mass55"};
        Bool_t  HLT_L1FatEvents = {fReader, "HLT_L1FatEvents"};
        Bool_t  HLT_Physics = {fReader, "HLT_Physics"};
        Bool_t  HLT_L1FatEvents_part0 = {fReader, "HLT_L1FatEvents_part0"};
        Bool_t  HLT_L1FatEvents_part1 = {fReader, "HLT_L1FatEvents_part1"};
        Bool_t  HLT_L1FatEvents_part2 = {fReader, "HLT_L1FatEvents_part2"};
        Bool_t  HLT_L1FatEvents_part3 = {fReader, "HLT_L1FatEvents_part3"};
        Bool_t  HLT_Random = {fReader, "HLT_Random"};
        Bool_t  HLT_ZeroBias = {fReader, "HLT_ZeroBias"};
        Bool_t  HLT_Mu300 = {fReader, "HLT_Mu300"};
        Bool_t  HLT_Mu350 = {fReader, "HLT_Mu350"};
        Bool_t  HLT_MET250 = {fReader, "HLT_MET250"};
        Bool_t  HLT_MET300 = {fReader, "HLT_MET300"};
        Bool_t  HLT_MET600 = {fReader, "HLT_MET600"};
        Bool_t  HLT_MET700 = {fReader, "HLT_MET700"};
        Bool_t  HLT_PFMET300 = {fReader, "HLT_PFMET300"};
        Bool_t  HLT_PFMET400 = {fReader, "HLT_PFMET400"};
        Bool_t  HLT_PFMET500 = {fReader, "HLT_PFMET500"};
        Bool_t  HLT_PFMET600 = {fReader, "HLT_PFMET600"};
        Bool_t  HLT_Ele250_CaloIdVT_GsfTrkIdT = {fReader, "HLT_Ele250_CaloIdVT_GsfTrkIdT"};
        Bool_t  HLT_Ele300_CaloIdVT_GsfTrkIdT = {fReader, "HLT_Ele300_CaloIdVT_GsfTrkIdT"};
        Bool_t  HLT_HT2000 = {fReader, "HLT_HT2000"};
        Bool_t  HLT_HT2500 = {fReader, "HLT_HT2500"};
        Bool_t  HLT_IsoTrackHE = {fReader, "HLT_IsoTrackHE"};
        Bool_t  HLT_IsoTrackHB = {fReader, "HLT_IsoTrackHB"};
        Bool_t  HLTriggerFinalPath = {fReader, "HLTriggerFinalPath"};
        Bool_t  L1simulation_step = {fReader, "L1simulation_step"};
        */
        
};
