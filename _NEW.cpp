#include "HEPAnalysis.h"

//-------------------------------------------------------------------------------------------------
// Define output variables
//-------------------------------------------------------------------------------------------------
namespace NEW{

    //int variable1Name;   [example]
}


//-------------------------------------------------------------------------------------------------
// Define output derivatives
//-------------------------------------------------------------------------------------------------
void HEPAnalysis::SetupNEW() {

    //======SETUP CUTFLOW==========================================================================
    //_cutFlow.insert(pair<string,double>("CutName", 0) );   [example]

    //======SETUP HISTOGRAMS=======================================================================
    makeHist( "MET", 100, 0., 500., "MET [GeV]", "Events" ); 
    //makeHist( "histogram2DName", 40, 0., 40., 100, 0., 50., "xlabel",  "ylabel", "zlabel", "COLZ" );   [example]

    //======SETUP SYSTEMATIC HISTOGRAMS============================================================
    makeSysHist( "MET", 500, 0., 500., "MET [GeV]", "Events" ); 
    makeSysHist( "MHT", 500, 0., 500., "MHT [GeV]", "Events" ); 

    //======SETUP OUTPUT BRANCHES==================================================================
    _outputTree->Branch("evtWeight", &evtWeight );
    _outputTree->Branch("MET", &_MET );
    _outputTree->Branch("HT", &_HT );

    return;
}


//-------------------------------------------------------------------------------------------------
// Define the selection region
//-------------------------------------------------------------------------------------------------
bool HEPAnalysis::NEWRegion() {

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
void HEPAnalysis::NEWSelection() {













    //======ASSIGN VALUES TO THE OUTPUT VARIABLES==================================================
    //NEW::variable1Name = 100;      [Example]

    //======FILL THE HISTOGRAMS====================================================================
    _histograms1D.at("MET").Fill( _MET, evtWeight );   
    //_histograms2D.at("histogram2DName").Fill( var1, var2, evtWeight );        [Example]

    //======FILL THE OUTPUT TREE===================================================================
    _outputTree->Fill();

    return;
}


//-------------------------------------------------------------------------------------------------
// Produce systematic histograms
//-------------------------------------------------------------------------------------------------
void HEPAnalysis::NEWSystematic() {

    FillSystematic( "MET", _MET, evtWeight);
    FillSystematic( "MHT", _MHT, evtWeight);
}


//-------------------------------------------------------------------------------------------------
// Make efficiency plots
//-------------------------------------------------------------------------------------------------
void HEPAnalysis::FinishNEW() {

    //MakeEfficiencyPlot( _histograms1D.at("Matched_pt"), _histograms1D.at("all_pt"), "Match_pt" );   [example]

    return;
}
