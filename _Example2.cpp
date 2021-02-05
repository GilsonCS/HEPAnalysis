#include "HEPAnalysis.h"

//-------------------------------------------------------------------------------------------------
// Define output variables
//-------------------------------------------------------------------------------------------------
namespace Example2{

    float HT;   
}


//-------------------------------------------------------------------------------------------------
// Define output derivatives
//-------------------------------------------------------------------------------------------------
void HEPAnalysis::SetupExample2() {

    //======SETUP CUTFLOW==========================================================================
    _cutFlow.insert(pair<string,double>("0_TRIG", 0) ); 
    _cutFlow.insert(pair<string,double>("1_MET_300", 0) );

    //======SETUP HISTOGRAMS=======================================================================
    //makeHist( "histogram1DName", 40, 0., 40., "xlabel", "ylabel" );   [example]
    //makeHist( "histogram2DName", 40, 0., 40., 100, 0., 50., "xlabel",  "ylabel", "zlabel", "COLZ" );   [example]

    //======SETUP SYSTEMATIC HISTOGRAMS============================================================
    //makeSysHist( "histogramSysName", 40, 0., 40., "xlabel", "ylabel" );   [example]

    //======SETUP OUTPUT BRANCHES==================================================================
    _outputTree->Branch("evtWeight", &evtWeight );
    _outputTree->Branch("HT", &Example2::HT );

    return;
}


//-------------------------------------------------------------------------------------------------
// Define the selection region
//-------------------------------------------------------------------------------------------------
bool HEPAnalysis::Example2Region() {

    //-------------------------------------------------------------------------
    // Trigger: MET > 250
    //-------------------------------------------------------------------------
    if( !(HLT_MET250) ) return false;           
    _cutFlow.at("0_TRIG") += evtWeight; 
    

    return true;
}


//-------------------------------------------------------------------------------------------------
// Write your analysis code here
//-------------------------------------------------------------------------------------------------
void HEPAnalysis::Example2Selection() {


    //-------------------------------------------------------------------------
    // RECO MET > 350
    //-------------------------------------------------------------------------
    if( !(MET_pt > MET_CUT) ) return;           
    _cutFlow.at("1_MET_300") += evtWeight;

    Example2::HT = 0;
    for( unsigned int iJet = 0; iJet < nJet; ++iJet ) {
        if( Jet_pt[iJet] > 30 ) Example2::HT += Jet_pt[iJet];
    }


    //======ASSIGN VALUES TO THE OUTPUT VARIABLES==================================================
    //Example2::variable1Name = 100;      [Example]

    //======FILL THE HISTOGRAMS====================================================================
    //_histograms1D.at("histogram1DName").Fill( var, evtWeight );               [Example]
    //_histograms2D.at("histogram2DName").Fill( var1, var2, evtWeight );        [Example]

    //======FILL THE OUTPUT TREE===================================================================
    _outputTree->Fill();

    return;
}


//-------------------------------------------------------------------------------------------------
// Produce systematic histograms
//-------------------------------------------------------------------------------------------------
void HEPAnalysis::Example2Systematic() {

    //FillSystematic( "histogramSysName", var, evtWeight );  [Example]
}


//-------------------------------------------------------------------------------------------------
// Make efficiency plots
//-------------------------------------------------------------------------------------------------
void HEPAnalysis::FinishExample2() {

    //MakeEfficiencyPlot( _histograms1D.at("Matched_pt"), _histograms1D.at("all_pt"), "Match_pt" );   [example]

    return;
}
