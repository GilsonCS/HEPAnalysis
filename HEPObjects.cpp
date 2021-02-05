#include "HEPAnalysis.h"

//---------------------------------------------------------------------------------------------------------------
// Pre-Objects Setup
//--------------------------------------------------------------------------------------------------------------- 
void HEPAnalysis::PreObjects() {
       
    //======START_SYS_LUMINOSITY===================================================================
    if( _applyEventWeights && _sysID == 2 ){    
        if( _Universe == 0 ) dataScaleWeight = (PROC_XSEC/PROC_NTOT) * (DATA_LUMI - DATA_LUMI_UNC);
        if( _Universe == 1 ) dataScaleWeight = (PROC_XSEC/PROC_NTOT) * (DATA_LUMI + DATA_LUMI_UNC);
    }
    //======END_SYS_LUMINOSITY=====================================================================
    
}


//---------------------------------------------------------------------------------------------------------------
// Objects Setup
//--------------------------------------------------------------------------------------------------------------- 
void HEPAnalysis::RunObjects() {
    /*
    //======START_SYS_JETS=========================================================================
    // 0 -> NOMINAL, 1 -> UP, 2 -> DOWN
    SYSJET = 0;
    if( _sysID == 1 ){
        if( _Universe == 0 ) SYSJET = 1;
        if( _Universe == 1 ) SYSJET = 2;
    }
    //======END_SYS_JETS===========================================================================

    //---------------------------------------------------------------------------------------------------------------
    // Objects Selection
    //---------------------------------------------------------------------------------------------------------------     
    recoJet_isLeptonLike = new vector<bool>;
    vetoElectrons.clear();
    plateauElectrons.clear();
    vetoMuons.clear();
    plateauMuons.clear();
    selectedJets.clear();
    recoJet_isLeptonLike->clear();
    ISRJets.clear();
    
    //----------------------------------------------------------------------------------------------------
    // first the muons 
   
    for( unsigned int im = 0; im < muon_px->size(); ++im ) {
        double pt = sqrt(muon_px->at(im)*muon_px->at(im) + muon_py->at(im)*muon_py->at(im));
        if( pt < MUON_PT_CUT ) continue;
        if( muon_iso->at(im) > MUON_ISO ) continue;
        if( muon_id->at(im) < MUON_ID ) continue;
        vetoMuons.push_back(im);
        if( pt < 30 ) continue;
        if( muon_iso->at(im) > 0.1 ) continue;
        if( muon_eta->at(im) > 2 ) continue;
        if( muon_id->at(im) < 3 ) continue;
        plateauMuons.push_back(im);
    }
     
    //----------------------------------------------------------------------------------------------------
    // now the electrons
    for( unsigned int ie = 0; ie < electron_px->size(); ++ie ) {
        double pt = sqrt(electron_px->at(ie)*electron_px->at(ie) + electron_py->at(ie)*electron_py->at(ie));
        if( pt < ELECTRON_PT_CUT ) continue;
        if( electron_iso->at(ie) > ELECTRON_ISO ) continue;
        if( electron_id->at(ie) < ELECTRON_ID ) continue;
        vetoElectrons.push_back(ie);
        if( pt < 30 ) continue;
        if( electron_iso->at(ie) > 0.1 ) continue;
        if( electron_eta->at(ie) > 2 ) continue;
        if( electron_id->at(ie) < 3 ) continue;
        plateauElectrons.push_back(ie);
    }
    
    //----------------------------------------------------------------------------------------------------
    // and the jets
    // first, identify lepton-like jets:
    for( unsigned int iJet = 0; iJet < recoJet_pt->size(); ++iJet ) {
      double jeta = recoJet_eta->at(iJet);
      double jphi = recoJet_phi->at(iJet);
      double drMin = 10000;
      
      // remove jets overlapping with electrons
      for( unsigned int ivetoEle = 0; ivetoEle < vetoElectrons.size(); ++ivetoEle ) {
        int iEle = vetoElectrons.at(ivetoEle);
        double eeta = electron_eta->at(iEle);
        double ephi = electron_phi->at(iEle);
        double deta = fabs(eeta - jeta);
        double dphi = fabs( ephi - jphi );
        if( dphi > M_PI ) dphi = 2*M_PI - dphi;
        double dr = sqrt( deta*deta + dphi*dphi );
        if( dr < drMin ) drMin = dr;
      }
      
      //remove jets overlapping with muons:
      for( unsigned int ivetoMuon = 0; ivetoMuon < vetoMuons.size(); ++ivetoMuon ) {
        int iMuon = vetoMuons.at(ivetoMuon);
        double eeta = muon_eta->at(iMuon);
        double ephi = muon_phi->at(iMuon);
        double deta = fabs(eeta - jeta);
        double dphi = fabs( ephi - jphi );
        if( dphi > M_PI ) dphi = 2*M_PI - dphi;
        double dr = sqrt( deta*deta + dphi*dphi );
        if( dr < drMin ) drMin = dr;
      }

      // and fill the recoJet variable:
      recoJet_isLeptonLike->push_back( (drMin < 0.4 ) ? true : false );
    }

    // now fill the signal jets:
    for( unsigned int iJet = 0; iJet < recoJet_pt->size(); ++iJet ) {
        if( recoJet_isLeptonLike->at(iJet) ) continue;
        if( fabs(recoJet_eta->at(iJet)) > JET_ETA_CUT ) continue;
        if( recoJet_pt->at(iJet).at(SYSJET) < JET_PT_CUT ) continue;
        if( recoJet_id->at(iJet) < JET_ID ) continue;

        selectedJets.push_back(iJet);
    }
    
    //----------------------------------------------------------------------------------------------------
    if( _datasetName.substr(0,3) == "TTJ" ) {
        for( unsigned int iselJet = 0; iselJet < CandISRJets->size(); ++iselJet ) {
            int iJet = CandISRJets->at(iselJet);
            if( recoJet_btag_combinedInclusiveSecondaryVertexV2BJetTags->at(iJet) > 0.8484 ) continue;
            if( recoJet_pt->at(iJet).at(SYSJET) < 30 ) continue;
            ISRJets.push_back( iJet );
        }
    }
    if( _datasetName.substr(0,3) == "ZJe" || _datasetName.substr(0,15) == "DYJetsToLL_M-50" ) {
        for( unsigned int iselJet = 0; iselJet < CandISRJets->size(); ++iselJet ) {
            ISRJets.push_back( 1 );
        }
    }
    
    //----------------------------------------------------------------------------------------------------
    if( (_datasetName.substr(0,3) != "ZJe") && (_datasetName.substr(0,15) != "DYJetsToLL_M-50") ) Zmass = -1;
    if( _datasetName.substr(0,15) != "DYJetsToLL_M-50" ) Lep_id = -1;
    
    //----------------------------------------------------------------------------------------------------
    
    _MET = sqrt( met_x->at(SYSJET)*met_x->at(SYSJET) + met_y->at(SYSJET)*met_y->at(SYSJET) );
    
   
    double HPx = 0;
    double HPy = 0;
    for( unsigned int iJet = 0; iJet < recoJet_pt->size(); ++iJet ) {
        if( recoJet_id->at(iJet) < 3 ) continue;
        if( recoJet_pt->at(iJet).at(SYSJET) < 20 ) continue;
        TLorentzVector Jet;
        Jet.SetPtEtaPhiE(recoJet_pt->at(iJet).at(SYSJET), recoJet_eta->at(iJet), recoJet_phi->at(iJet), 0);
        HPx += Jet.Px();
        HPy += Jet.Py();
    }
    _MHT = sqrt(HPx*HPx + HPy*HPy);
    
    double HT = 0;
    for( unsigned int iselJet = 0; iselJet < selectedJets.size(); ++iselJet ) {
        int iJet = selectedJets.at(iselJet);
        if( recoJet_pt->at(iJet).at(SYSJET) < 20 ) continue;
        HT += recoJet_pt->at(iJet).at(SYSJET);
    }
    _HT = HT;
    
    _NBJets = 0;
    for( unsigned int iselJet = 0; iselJet < selectedJets.size(); ++iselJet ) {
        int iJet = selectedJets.at(iselJet);
        if( recoJet_btag_combinedInclusiveSecondaryVertexV2BJetTags->at(iJet) <= 0.8484 ) continue;
        if( recoJet_pt->at(iJet).at(SYSJET) >= 20 ) _NBJets += 1;
    }



    _idJetsToPV.clear();
    _idJetsToSV.clear();
    for( unsigned int iVtx = 0; iVtx < vertex_x->size(); ++iVtx ) {
        vector<int> idx;
        _idJetsToPV.push_back( idx );
    }
	for( unsigned int iVtx = 0; iVtx < secVertex_x->size(); ++iVtx ) {
        vector<int> idx;
        _idJetsToSV.push_back( idx );
    }

	for( unsigned int iselJet = 0; iselJet < selectedJets.size(); ++iselJet ) {
        int iJet = selectedJets.at(iselJet);
        vector<double> position(3,0.);
        if( Track == 0 ){
            position.at(0) = recoJet_vertex_x->at(iJet);
            position.at(1) = recoJet_vertex_y->at(iJet);
            position.at(2) = recoJet_vertex_z->at(iJet);
        }else if( Track == 1 ){
            position.at(0) = recoJet_C_vertex_x->at(iJet);
            position.at(1) = recoJet_C_vertex_y->at(iJet);
            position.at(2) = recoJet_C_vertex_z->at(iJet);
        }
        int nMatch = 0;

        for( unsigned int iVtx = 0; iVtx < vertex_x->size(); ++iVtx ) {
            if( fabs(position.at(0) - vertex_x->at(iVtx) ) < 1.e-10 &&
                fabs(position.at(1) - vertex_y->at(iVtx) ) < 1.e-10 &&
                fabs(position.at(2) - vertex_z->at(iVtx) ) < 1.e-10 ) {
                nMatch += 1;
                if( recoJet_pt->at(iJet).at(SYSJET) >= 30 ) _idJetsToPV.at(iVtx).push_back( iJet );
            }
        }
        for( unsigned int iVtx = 0; iVtx < secVertex_x->size(); ++iVtx ) {
            if( fabs(position.at(0) - secVertex_x->at(iVtx) ) < 1.e-10 &&
                fabs(position.at(1) - secVertex_y->at(iVtx) ) < 1.e-10 &&
                fabs(position.at(2) - secVertex_z->at(iVtx) ) < 1.e-10 ) {
                nMatch += 1;
                _idJetsToSV.at(iVtx).push_back( iJet );
            }
        }
        if( nMatch > 1 ) {
            cout << "WARNING! ASSOCIATED JET TO MORE THAN 1 VERTEX ?!" << endl;
        }
	}

	_LeadingJetPV = -1;
    _SubLeadingJetPV = -1;
    _LeadingJetPV_Pt = 0;
    _SubLeadingJetPV_Pt = 0;

    for( unsigned int iiJet = 0; iiJet < _idJetsToPV.at(0).size(); ++iiJet ) {
        int iJet = _idJetsToPV.at(0).at(iiJet);

        if( recoJet_pt->at(iJet).at(SYSJET) > _LeadingJetPV_Pt ) {
            _SubLeadingJetPV_Pt = _LeadingJetPV_Pt;
            _SubLeadingJetPV = _LeadingJetPV;
            _LeadingJetPV_Pt = recoJet_pt->at(iJet).at(SYSJET);
            _LeadingJetPV = iJet;
        } else if ( recoJet_pt->at(iJet).at(SYSJET) > _SubLeadingJetPV_Pt ) {
            _SubLeadingJetPV_Pt = recoJet_pt->at(iJet).at(SYSJET);
            _SubLeadingJetPV = iJet;
        }
	}

	_SV2Jets.clear();
    _SV1Jet.clear();

    for( unsigned int iSV = 0; iSV < secVertex_x->size(); ++iSV ) {
        if( _idJetsToSV.at(iSV).size() == 2 ) _SV2Jets.push_back( iSV );
        if( _idJetsToSV.at(iSV).size() == 1 ){
            int iJet = _idJetsToSV.at(iSV).at(0);
            if( recoJet_pt->at(iJet).at(SYSJET) >= 14 ) _SV1Jet.push_back( iSV );
        }
	}

	_NJetsPV = _idJetsToPV.at(0).size();
    */

}


    

    



















