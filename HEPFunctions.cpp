#include "HEPAnalysis.h"

/*
void Get_JEC_SYS( string filename, vector< vector<float> > &dataVec){

    int rows = 40;
    int cols = 50;
    ifstream in;
    in.open(filename);

    if (in.is_open()){
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                in >> dataVec[i][j];    
            }
        }
        in.close();
    }else{
        cout << "Error opening " << filename << endl;
    }
}
*/

/*
const auto model = fdeep::load_model("Metadata/ML_TTbar/fdeep_model.json");

//---------------------------------------------------------------------------------------------------------------
// MLClassifier
//--------------------------------------------------------------------------------------------------------------- 
float HEPAnalysis::MLClassifier( float LeadingMuPt, float NMuons, float LeadingJetPt, float NJets, float MET, float HT ) {
    
    LeadingMuPt = (LeadingMuPt - 53.7042895)/27.52949744;
    NMuons = (NMuons - 1.04340568)/0.20382527;
    LeadingJetPt = (LeadingJetPt - 65.54868411)/41.42918508;
    NJets = (NJets - 1.45019477)/0.80324801; 
    MET = (MET - 34.04825059)/29.84072119;
    HT = (HT - 89.93011981)/80.31952029;
    float result = model.predict_single_output( {fdeep::tensor(fdeep::tensor_shape(static_cast<std::size_t>(6)), {LeadingMuPt, NMuons, LeadingJetPt, NJets, MET, HT})});
    
    return result;
}
*/


//---------------------------------------------------------------------------------------------------------------
// makeSysHist
//--------------------------------------------------------------------------------------------------------------- 
void HEPAnalysis::makeSysHist( string nametitle, int nbins, double xmin, double xmax, string xtitle, string ytitle, string drawOption, double xAxisOffset, double yAxisOffset ) {
    string universetitle = nametitle + "_" + to_string(_sysID) + "_" + to_string(_Universe);    
    TH1D hist(universetitle.c_str(), universetitle.c_str(), nbins, xmin, xmax );
    hist.GetXaxis()->SetTitle( xtitle.c_str() );
    hist.GetYaxis()->SetTitle( ytitle.c_str() );
    hist.GetYaxis()->SetTitleOffset( yAxisOffset );
    hist.GetXaxis()->SetTitleOffset( xAxisOffset );
    _systematics1D.insert( pair<string, TH1D>( universetitle, hist ) );
    _systematics1DDrawOptions.insert( pair<string,string>( universetitle, drawOption ) );
}


//---------------------------------------------------------------------------------------------------------------
// FillSystematic
//--------------------------------------------------------------------------------------------------------------- 
void HEPAnalysis::FillSystematic( string varName, double varEntry, double evtWeight ){
    
    string varSys = varName + "_" + to_string(_sysID) + "_" + to_string(_Universe); 
    _systematics1D.at(varSys.c_str()).Fill( varEntry, evtWeight ); 
}


//---------------------------------------------------------------------------------------------------------------
// makeHist
//--------------------------------------------------------------------------------------------------------------- 
void HEPAnalysis::makeHist( string nametitle, int nbinsx, double xmin, double xmax, int nbinsy, double ymin, double ymax, string xtitle, string ytitle, string ztitle, string drawOption, double xAxisOffset, double yAxisOffset, double zAxisOffset ) {

    TH2D hist(nametitle.c_str(), nametitle.c_str(), nbinsx, xmin, xmax, nbinsy, ymin, ymax );
    hist.GetXaxis()->SetTitle( xtitle.c_str() );
    hist.GetYaxis()->SetTitle( ytitle.c_str() );
    hist.GetZaxis()->SetTitle( ztitle.c_str() );
    hist.GetXaxis()->SetTitleOffset( xAxisOffset );
    hist.GetYaxis()->SetTitleOffset( yAxisOffset );
    hist.GetZaxis()->SetTitleOffset( zAxisOffset );
    _histograms2D.insert( pair<string, TH2D>( nametitle, hist ) );
    _histograms2DDrawOptions.insert( pair<string,string>( nametitle, drawOption ) );

}

void HEPAnalysis::makeHist( string nametitle, int nbins, double xmin, double xmax, string xtitle, string ytitle, string drawOption, double xAxisOffset, double yAxisOffset ) {

    TH1D hist(nametitle.c_str(), nametitle.c_str(), nbins, xmin, xmax );
    hist.GetXaxis()->SetTitle( xtitle.c_str() );
    hist.GetYaxis()->SetTitle( ytitle.c_str() );
    hist.GetYaxis()->SetTitleOffset( yAxisOffset );
    hist.GetXaxis()->SetTitleOffset( xAxisOffset );
    _histograms1D.insert( pair<string, TH1D>( nametitle, hist ) );
    _histograms1DDrawOptions.insert( pair<string,string>( nametitle, drawOption ) );
}


//---------------------------------------------------------------------------------------------------------------
// MakeEfficiencyPlot
//--------------------------------------------------------------------------------------------------------------- 
void HEPAnalysis::MakeEfficiencyPlot( TH1D hpass, TH1D htotal, string triggerName ) {
    TCanvas c("","");
    TGraphAsymmErrors geff;
    geff.BayesDivide( &hpass, &htotal );
    geff.GetXaxis()->SetTitle( hpass.GetXaxis()->GetTitle() );
    string ytitle = "#varepsilon (" + triggerName + ")";
    geff.GetYaxis()->SetTitle( ytitle.c_str() );
    string efftitle = _outputDirectory + "efficiency_" + triggerName;
    geff.SetNameTitle(efftitle.c_str(), efftitle.c_str());
    geff.SetMarkerColor(kBlue);
    geff.Draw("APZ"); 
    for( vector<string>::iterator itr_f = _plotFormats.begin(); itr_f != _plotFormats.end(); ++itr_f ) {
        string thisPlotName = efftitle + (*itr_f);
        c.Print( thisPlotName.c_str() );
    }

}


//---------------------------------------------------------------------------------------------------------------
// setStyle
//--------------------------------------------------------------------------------------------------------------- 
void HEPAnalysis::setStyle( double ytoff, bool marker, double left_margin ) {
// use plain black on white colors
Int_t icol=0;
gStyle->SetFrameBorderMode(icol);
gStyle->SetCanvasBorderMode(icol);
gStyle->SetPadBorderMode(icol);
gStyle->SetPadColor(icol);
gStyle->SetCanvasColor(icol);
gStyle->SetStatColor(icol);
gStyle->SetTitleFillColor(icol);
// set the paper & margin sizes
gStyle->SetPaperSize(20,26);
gStyle->SetPadTopMargin(0.10);
gStyle->SetPadRightMargin(0.15);
gStyle->SetPadBottomMargin(0.16);
gStyle->SetPadLeftMargin(0.15);
// use large fonts
Int_t font=62;
Double_t tsize=0.04;
gStyle->SetTextFont(font);
gStyle->SetTextSize(tsize);
gStyle->SetLabelFont(font,"x");
gStyle->SetTitleFont(font,"x");
gStyle->SetLabelFont(font,"y");
gStyle->SetTitleFont(font,"y");
gStyle->SetLabelFont(font,"z");
gStyle->SetTitleFont(font,"z");
gStyle->SetLabelSize(tsize,"x");
gStyle->SetTitleSize(tsize,"x");
gStyle->SetLabelSize(tsize,"y");
gStyle->SetTitleSize(tsize,"y");
gStyle->SetLabelSize(tsize,"z");
gStyle->SetTitleSize(tsize,"z");
gStyle->SetTitleBorderSize(0);
//use bold lines and markers
if ( marker ) {
  gStyle->SetMarkerStyle(20);
  gStyle->SetMarkerSize(1.2);
}
gStyle->SetHistLineWidth(Width_t(3.));
// postscript dashes
gStyle->SetLineStyleString(2,"[12 12]");
gStyle->SetOptStat(0);
gStyle->SetOptFit(1111);
// put tick marks on top and RHS of plots
gStyle->SetPadTickX(1);
gStyle->SetPadTickY(1);
// DLA overrides
gStyle->SetPadLeftMargin(left_margin);
gStyle->SetPadBottomMargin(0.13);
gStyle->SetTitleYOffset(ytoff);
gStyle->SetTitleXOffset(1.0);
gStyle->SetOptTitle(0);
//gStyle->SetStatStyle(0);
//gStyle->SetStatFontSize();
gStyle->SetStatW(0.17);

}



