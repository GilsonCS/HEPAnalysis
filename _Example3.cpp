#include "HEPAnalysis.h"

//-------------------------------------------------------------------------------------------------
// Define output variables
//-------------------------------------------------------------------------------------------------
namespace Example3{

    //int variable1Name;   [example]
}


//-------------------------------------------------------------------------------------------------
// Define output derivatives
//-------------------------------------------------------------------------------------------------
void HEPAnalysis::SetupExample3() {

    //======SETUP CUTFLOW==========================================================================
    _cutFlow.insert(pair<string,double>("0_TRIG", 0) ); 
    _cutFlow.insert(pair<string,double>("1_MET_300", 0) );

    //======SETUP HISTOGRAMS=======================================================================
    //makeHist( "histogram1DName", 40, 0., 40., "xlabel", "ylabel" );   [example]
    //makeHist( "histogram2DName", 40, 0., 40., 100, 0., 50., "xlabel",  "ylabel", "zlabel", "COLZ" );   [example]

    //======SETUP SYSTEMATIC HISTOGRAMS============================================================
    makeSysHist( "MET", 100, 0., 500., "MET [GeV]", "Events" ); 

    //======SETUP OUTPUT BRANCHES==================================================================
    //_outputTree->Branch("variable1NameInTheTree", &Example3::variable1Name );  [example]

    return;
}


//-------------------------------------------------------------------------------------------------
// Define the selection region
//-------------------------------------------------------------------------------------------------
bool HEPAnalysis::Example3Region() {

    //-------------------------------------------------------------------------
    // Trigger: MET > 250
    //-------------------------------------------------------------------------
    if( !(HLT_MET250) ) return false;           
    _cutFlow.at("0_TRIG") += evtWeight;

    //-------------------------------------------------------------------------
    // RECO MET > 300
    //-------------------------------------------------------------------------
    if( !(MET_pt > MET_CUT) ) return false;           
    _cutFlow.at("1_MET_300") += evtWeight;

    return true;
}


//-------------------------------------------------------------------------------------------------
// Write your analysis code here
//-------------------------------------------------------------------------------------------------
void HEPAnalysis::Example3Selection() {













    //======ASSIGN VALUES TO THE OUTPUT VARIABLES==================================================
    //Example3::variable1Name = 100;      [Example]

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
void HEPAnalysis::Example3Systematic() {

    FillSystematic( "MET", MET_pt, evtWeight ); 
}


//-------------------------------------------------------------------------------------------------
// Make efficiency plots
//-------------------------------------------------------------------------------------------------
void HEPAnalysis::FinishExample3() {

    //MakeEfficiencyPlot( _histograms1D.at("Matched_pt"), _histograms1D.at("all_pt"), "Match_pt" );   [example]

    return;
}
