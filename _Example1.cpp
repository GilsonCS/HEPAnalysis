#include "HEPAnalysis.h"

//-------------------------------------------------------------------------------------------------
// Define output variables
//-------------------------------------------------------------------------------------------------
namespace Example1{

    //int variable1Name;   [example]
}


//-------------------------------------------------------------------------------------------------
// Define output derivatives
//-------------------------------------------------------------------------------------------------
void HEPAnalysis::SetupExample1() {

    //======SETUP CUTFLOW==========================================================================
    //_cutFlow.insert(pair<string,double>("CutName", 0) );   [example]

    //======SETUP HISTOGRAMS=======================================================================
    makeHist( "MET", 100, 0., 500., "MET [GeV]", "Events" ); 
    makeHist( "MET_triggered", 100, 0., 500., "MET [GeV]", "Events" );
    //makeHist( "histogram2DName", 40, 0., 40., 100, 0., 50., "xlabel",  "ylabel", "zlabel", "COLZ" );   [example]

    //======SETUP SYSTEMATIC HISTOGRAMS============================================================
    //makeSysHist( "histogramSysName", 40, 0., 40., "xlabel", "ylabel" );   [example]

    //======SETUP OUTPUT BRANCHES==================================================================
    //_outputTree->Branch("variable1NameInTheTree", &Example1::variable1Name );  [example]

    return;
}


//-------------------------------------------------------------------------------------------------
// Define the selection region
//-------------------------------------------------------------------------------------------------
bool HEPAnalysis::Example1Region() {

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
void HEPAnalysis::Example1Selection() {

    _histograms1D.at("MET").Fill( MET_pt, evtWeight );
    if( HLT_MET250 ) _histograms1D.at("MET_triggered").Fill( MET_pt, evtWeight );











    //======ASSIGN VALUES TO THE OUTPUT VARIABLES==================================================
    //Example1::variable1Name = 100;      [Example]

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
void HEPAnalysis::Example1Systematic() {

    //FillSystematic( "histogramSysName", var, evtWeight );  [Example]
}


//-------------------------------------------------------------------------------------------------
// Make efficiency plots
//-------------------------------------------------------------------------------------------------
void HEPAnalysis::FinishExample1() {

    MakeEfficiencyPlot( _histograms1D.at("MET_triggered"), _histograms1D.at("MET"), "MET [GeV]" ); 

    return;
}
