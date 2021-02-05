#include "HEPAnalysis.h"

//-------------------------------------------------------------------------------------------------
// Define output variables
//-------------------------------------------------------------------------------------------------
namespace SgnEff{
    
}


//-------------------------------------------------------------------------------------------------
// Define output derivatives
//-------------------------------------------------------------------------------------------------
void HEPAnalysis::SetupSgnEff() {

    //======SETUP CUTFLOW==========================================================================
    _cutFlow.insert(pair<string,double>("0_Nelectrons", 0) );
    _cutFlow.insert(pair<string,double>("0_Nmuons", 0) );
    _cutFlow.insert(pair<string,double>("0_Ntaus", 0) );
    _cutFlow.insert(pair<string,double>("0_Nbjets", 0) );
    _cutFlow.insert(pair<string,double>("0_NStartPart", 0) );
    _cutFlow.insert(pair<string,double>("0_Start", 0) );
    _cutFlow.insert(pair<string,double>("1_LepEta", 0) );
    _cutFlow.insert(pair<string,double>("2_LepPt", 0) );
    _cutFlow.insert(pair<string,double>("3_1BJet", 0) );
    _cutFlow.insert(pair<string,double>("4_2BJet", 0) );
    

    //======SETUP HISTOGRAMS=======================================================================
    makeHist( "ipart0", 100, -50., 50., "PDG ID", "Particles" ); 
    makeHist( "ipart1", 100, -50., 50., "PDG ID", "Particles" );
    makeHist( "ipart2", 100, -50., 50., "PDG ID", "Particles" ); 
    makeHist( "ipart3", 100, -50., 50., "PDG ID", "Particles" );
    makeHist( "ipart4", 100, -50., 50., "PDG ID", "Particles" ); 
    makeHist( "ipart5", 100, -50., 50., "PDG ID", "Particles" );
    makeHist( "ipart6", 100, -50., 50., "PDG ID", "Particles" ); 
    makeHist( "ipart7", 100, -50., 50., "PDG ID", "Particles" );
    makeHist( "ipart8", 100, -50., 50., "PDG ID", "Particles" ); 
    makeHist( "ipart9", 100, -50., 50., "PDG ID", "Particles" );

    //makeHist( "histogram2DName", 40, 0., 40., 100, 0., 50., "xlabel",  "ylabel", "zlabel", "COLZ" );   [example]

    //======SETUP SYSTEMATIC HISTOGRAMS============================================================
    //makeSysHist( "histogramSysName", 40, 0., 40., "xlabel", "ylabel" );   [example]

    //======SETUP OUTPUT BRANCHES==================================================================
    //_outputTree->Branch("variable1NameInTheTree", &SgnEff::variable1Name );  [example]

    return;
}


//-------------------------------------------------------------------------------------------------
// Define the selection region
//-------------------------------------------------------------------------------------------------
bool HEPAnalysis::SgnEffRegion() {

       
    //-------------------------------------------------------------------------
    // Cut description
    //-------------------------------------------------------------------------
    //if( !(CutCondition) ) return false;           [Example]
    //_cutFlow.at("CutName") += evtWeight;          [Example]

    return true;
}


//-------------------------------------------------------------------------------------------------
// Write your analysis code here
//-------------------------------------------------------------------------------------------------
void HEPAnalysis::SgnEffSelection() {


    _histograms1D.at("ipart0").Fill( GenPart_pdgId[0], 1 );
    _histograms1D.at("ipart1").Fill( GenPart_pdgId[1], 1 );
    _histograms1D.at("ipart2").Fill( GenPart_pdgId[2], 1 );
    _histograms1D.at("ipart3").Fill( GenPart_pdgId[3], 1 );
    _histograms1D.at("ipart4").Fill( GenPart_pdgId[4], 1 );
    _histograms1D.at("ipart5").Fill( GenPart_pdgId[5], 1 );
    _histograms1D.at("ipart6").Fill( GenPart_pdgId[6], 1 );
    _histograms1D.at("ipart7").Fill( GenPart_pdgId[7], 1 );
    _histograms1D.at("ipart8").Fill( GenPart_pdgId[8], 1 );
    _histograms1D.at("ipart9").Fill( GenPart_pdgId[9], 1 );
      
    int LepID = 0;
    float LeadLepPt = 0;
    float SubLepPt = 0;
    float LeadLepEta = 0;
    float SubLepEta = 0;
    float LeadBJetPt = 0;
    float LeadBJetEta = 0;
    float SubBJetPt = 0;
    float SubBJetEta = 0;
    for( unsigned int ipart = 0; ipart < nGenPart; ++ipart ) {
        if( (abs(GenPart_pdgId[ipart]) == 11)  && (GenPart_pdgId[GenPart_genPartIdxMother[ipart]] == 23) ) _cutFlow.at("0_Nelectrons") += 1;
        if( (abs(GenPart_pdgId[ipart]) == 13)  && (GenPart_pdgId[GenPart_genPartIdxMother[ipart]] == 23) ) _cutFlow.at("0_Nmuons") += 1;
        if( (abs(GenPart_pdgId[ipart]) == 15)  && (GenPart_pdgId[GenPart_genPartIdxMother[ipart]] == 23) ) _cutFlow.at("0_Ntaus") += 1;
        if( (abs(GenPart_pdgId[ipart]) == 5)  && (GenPart_genPartIdxMother[ipart] == 0) ) _cutFlow.at("0_Nbjets") += 1;
        if( (GenPart_genPartIdxMother[ipart] == 0) ) _cutFlow.at("0_NStartPart") += 1;
        
        
        if( ((abs(GenPart_pdgId[ipart]) == 11) || (abs(GenPart_pdgId[ipart]) == 13) || (abs(GenPart_pdgId[ipart]) == 15))  && (GenPart_pdgId[GenPart_genPartIdxMother[ipart]] == 23) ){
            LepID = abs(GenPart_pdgId[ipart]);
            if( GenPart_pt[ipart] > LeadLepPt ){ 
                SubLepPt = LeadLepPt;
                SubLepEta = LeadLepEta;
                LeadLepPt = GenPart_pt[ipart];
                LeadLepEta = GenPart_eta[ipart];
            }else if( GenPart_pt[ipart] > SubLepPt ){
                SubLepPt = GenPart_pt[ipart];
                SubLepEta = GenPart_eta[ipart];
            }
        }
        
        if( (abs(GenPart_pdgId[ipart]) == 5)  && (GenPart_genPartIdxMother[ipart] == 0) ){
            if( GenPart_pt[ipart] > LeadBJetPt ){ 
                SubBJetPt = LeadBJetPt;
                SubBJetEta = LeadBJetEta;
                LeadBJetPt = GenPart_pt[ipart];
                LeadBJetEta = GenPart_eta[ipart];
            }else if( GenPart_pt[ipart] > SubBJetPt ){
                SubBJetPt = GenPart_pt[ipart];
                SubBJetEta = GenPart_eta[ipart];
            }
        }
    }
    
    if( LepID == 15 ) return;
    _cutFlow.at("0_Start") += evtWeight;
    
    //-------------------------------------------------------------------------
    // Cut Lep Eta
    //-------------------------------------------------------------------------
    if( !((LeadLepEta < 2.4) && (SubLepEta < 2.4)) ) return; 
    _cutFlow.at("1_LepEta") += evtWeight;
    
    //-------------------------------------------------------------------------
    // Cut Lep Pt
    //-------------------------------------------------------------------------
    if( !((LeadLepPt > 30) && (SubLepPt > 30)) ) return; 
    _cutFlow.at("2_LepPt") += evtWeight;
    
    //-------------------------------------------------------------------------
    // Cut 1BJet 
    //-------------------------------------------------------------------------
    if( !( ((LeadBJetEta < 2.4) && (LeadBJetPt > 25)) || ((SubBJetEta < 2.4) && (SubBJetPt > 25)) ) ) return; 
    _cutFlow.at("3_1BJet") += evtWeight;

    //-------------------------------------------------------------------------
    // Cut 2BJet 
    //-------------------------------------------------------------------------
    if( !( ((LeadBJetEta < 2.4) && (LeadBJetPt > 25)) && ((SubBJetEta < 2.4) && (SubBJetPt > 25)) ) ) return; 
    _cutFlow.at("4_2BJet") += evtWeight;


    //======ASSIGN VALUES TO THE OUTPUT VARIABLES==================================================
    //SgnEff::variable1Name = 100;      [Example]

    //======FILL THE HISTOGRAMS====================================================================
    //_histograms1D.at("histogram1DName").Fill( var, evtWeight );               [Example]
    //_histograms2D.at("histogram2DName").Fill( var1, var2, evtWeight );        [Example]

    //======FILL THE OUTPUT TREE===================================================================
    //_outputTree->Fill();

    return;
}


//-------------------------------------------------------------------------------------------------
// Produce systematic histograms
//-------------------------------------------------------------------------------------------------
void HEPAnalysis::SgnEffSystematic() {

    //FillSystematic( "histogramSysName", var, evtWeight );  [Example]
}


//-------------------------------------------------------------------------------------------------
// Make efficiency plots
//-------------------------------------------------------------------------------------------------
void HEPAnalysis::FinishSgnEff() {

    //MakeEfficiencyPlot( _histograms1D.at("Matched_pt"), _histograms1D.at("all_pt"), "Match_pt" );   [example]

    return;
}
