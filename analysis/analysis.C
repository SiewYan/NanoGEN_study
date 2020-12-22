/*
* Gen level study
* 1.) associated lepton1 distribution
* 2.) lepton2 distribution
* 3.) genjet
*/

// generated object number
TH1D* Gen_nlepton1;
TH1D* Gen_nlepton2;
TH1D* Gen_nWquark;
TH1D* Gen_njet;
TH1D* Gen_nWboson;
TH1D* Gen_nWHboson;
TH1D* Gen_nHboson;
TH1D* Gen_nNeutrino;
TH1D* Gen_met_pt;
TH1D* Gen_met_phi;
TH1D* GenMETpt;
TH1D* GenMETphi;

std::vector<TLorentzVector> Wboson;
std::vector<TLorentzVector> WHboson;
std::vector<TLorentzVector> Hboson;
std::vector<TLorentzVector> lepton1;
std::vector<TLorentzVector> lepton2;
std::vector<TLorentzVector> Wquark;
std::vector<TLorentzVector> genjet;
std::vector<TLorentzVector> Neutrino;
std::vector<TLorentzVector> MET;

std::vector<Float_t> genjet_matchdR;
std::vector<Int_t> genjet_pdgId;

TFile* out = new TFile( "WHSS.root" , "recreate" );
TTree* gen_tree = new TTree( "gen" , "gen" );

TDirectory* genlevel =  out->mkdir("nGen_object");

void analysis_Begin(TTree*) {

  // generated object number
  Gen_nlepton1   = new TH1D ( "Gen_nlepton1"  , "Gen_nlepton1"   , 10 , 0  , 10     );
  Gen_nlepton2   = new TH1D ( "Gen_nlepton2"  , "Gen_nlepton2"   , 10 , 0  , 10     );
  Gen_nWquark    = new TH1D ( "Gen_nWquark"   , "Gen_nWquark"    , 10 , 0  , 10     );  
  Gen_njet       = new TH1D ( "Gen_njet"      , "Gen_njet"       , 10 , 0  , 10     );
  Gen_nWboson    = new TH1D ( "Gen_nWboson"   , "Gen_nWboson"    , 10 , 0  , 10     );
  Gen_nWHboson   = new TH1D ( "Gen_nWHboson"  , "Gen_nWHboson"    , 10 , 0  , 10     );
  Gen_nHboson    = new TH1D ( "Gen_nHboson"   , "Gen_nHboson"    , 10 , 0  , 10     );
  Gen_nNeutrino  = new TH1D ( "Gen_nNeutrino" , "Gen_nNeutrino"    , 10 , 0  , 10     );
  Gen_met_pt     = new TH1D ( "Gen_met_pt"    , "Gen_met_pt"     , 50 , 0. , 200. );
  Gen_met_phi    = new TH1D ( "Gen_met_phi"   , "Gen_met_phi"     , 30 , 0. , 3.2 );
  GenMETpt      = new TH1D ( "GenMETpt"    , "GenMETpt"     , 50 , 0. , 200. );
  GenMETphi     = new TH1D ( "GenMETphi"   , "GenMETphi"     , 30 , 0. , 3.2 );
  
  // initialize branch
  gen_tree->Branch( "Wboson"  , &Wboson );
  gen_tree->Branch( "WHboson" , &WHboson );
  gen_tree->Branch( "Hboson"  , &Hboson );
  gen_tree->Branch( "lepton1" , &lepton1 );
  gen_tree->Branch( "lepton2" , &lepton2 );
  gen_tree->Branch( "Wquark"  , &Wquark );
  gen_tree->Branch( "genjet"  , &genjet );
  gen_tree->Branch( "Neutrino"  , &Neutrino );
  gen_tree->Branch( "MET"       , &MET );

  gen_tree->Branch( "genjet_matchdR" , &genjet_matchdR );
  gen_tree->Branch( "genjet_pdgId" , &genjet_pdgId );
  
}

void analysis() {
  //Per event variables
  TLorentzVector VX;
  
  Wboson.clear();
  WHboson.clear();
  Hboson.clear();
  lepton1.clear();
  lepton2.clear();
  Wquark.clear();
  genjet.clear();
  Neutrino.clear();
  MET.clear();

  genjet_matchdR.clear();
  genjet_pdgId.clear();

  Int_t bosons[3]   = { 24 , -24 , 25 };
  //Int_t partons[8] = { 1, -1, 2, -2, 3, -3, 4, -4 };
  Int_t partons[11] = { 1, -1, 2, -2, 3, -3, 4, -4 , 5 , -5 , 21 };
  Int_t leptons[4]  = { 11, -11, 13, -13 };
  Int_t neutrinos[6] = { 12 , -12 , 14 , -14 , 16 , -16 };

  // GenPart (LEPTON)
  for ( UInt_t i=0 ; i < nGenPart ; i++ ){
    VX.SetPtEtaPhiM(0.,0.,0.,0.);
    // filter non lepton particle
    if ( !( std::find(std::begin(leptons), std::end(leptons), GenPart_pdgId[i]) != std::end(leptons) ) ) continue;
    
    // fromHardProcess
    if ( !(GenPart_statusFlags[i] >> 8 & 1) ) continue;
    // isPrompt
    if ( !(GenPart_statusFlags[i] & 1) ) continue;
    // status == 1
    if (GenPart_status[i] != 1) continue;
    
    VX.SetPtEtaPhiM( GenPart_pt[i] , GenPart_eta[i] , GenPart_phi[i] , GenPart_mass[i] );
    Int_t monIdx = GenPart_genPartIdxMother[i];
    Int_t monpdgid = GenPart_pdgId[monIdx];
    
    //check mon
    Bool_t isW=false;
    Bool_t isH=false;
    while (monIdx>0){
      monpdgid = GenPart_pdgId[monIdx];
      if ( abs(monpdgid) == 24 ) isW=true;
      if ( abs(monpdgid) == 25 ) isH=true;
      monIdx = GenPart_genPartIdxMother[monIdx];
    }
    if (isW && !isH){
      lepton1.push_back(VX);
    }
    else if (isW && isH){
      lepton2.push_back(VX);
    }
    else if (!isW && isH){
      lepton2.push_back(VX);
    }
  }
  
  // GenPart (BOSON)
  for ( UInt_t i=0 ; i < nGenPart ; i++ ){
    VX.SetPtEtaPhiM(0.,0.,0.,0.);
    
    // filter non boson particle
    if ( !( std::find(std::begin(bosons), std::end(bosons), GenPart_pdgId[i]) != std::end(bosons) ) ) continue;
    // LastCopy
    if ( !(GenPart_statusFlags[i] >> 13 & 1) ) continue;
    
    VX.SetPtEtaPhiM( GenPart_pt[i] , GenPart_eta[i] , GenPart_phi[i] , GenPart_mass[i] );
    Int_t monIdx   = GenPart_genPartIdxMother[i];
    Int_t monpdgId = GenPart_pdgId[monIdx];

    Bool_t isH=false;
    while (monIdx>0){
      monpdgId = GenPart_pdgId[monIdx];
      if ( abs(monpdgId) == 25 ) isH=true;
      monIdx = GenPart_genPartIdxMother[monIdx];
    }
    
    // W boson
    if ( abs(GenPart_pdgId[i]) == 24 && !isH ) Wboson.push_back(VX);
    if ( abs(GenPart_pdgId[i]) == 24 && isH ) WHboson.push_back(VX);
    // H boson
    if ( abs(GenPart_pdgId[i]) == 25 ) Hboson.push_back(VX);
  }// end of nleptongen loop

  // GenPart (NEUTRINO)
  TLorentzVector VXX; VXX.SetPtEtaPhiM(0., 0., 0., 0.);
  for ( UInt_t i=0 ; i < nGenPart ; i++ ){
    VX.SetPtEtaPhiM(0.,0.,0.,0.);
    if ( !( std::find(std::begin(neutrinos), std::end(neutrinos), GenPart_pdgId[i]) != std::end(neutrinos) ) ) continue;
    if (GenPart_status[i] != 1) continue;
    VX.SetPtEtaPhiM( GenPart_pt[i] , GenPart_eta[i] , GenPart_phi[i] , GenPart_mass[i] );
    Neutrino.push_back(VX);
    VXX+=VX;
  }
  MET.push_back(VXX);
  
  // GenPart (QUARK)
  std::vector<TLorentzVector> GenQuark;
  std::vector<Int_t> GenQuark_pdgId;
  for ( UInt_t i=0 ; i < nGenPart ; i++ ){
    VX.SetPtEtaPhiM(0.,0.,0.,0.);
    // filter non quark particle
    if ( !( std::find(std::begin(partons), std::end(partons), GenPart_pdgId[i]) != std::end(partons) ) ) continue;
    
    // fromHardProcess
    if ( !(GenPart_statusFlags[i] >> 8 & 1) ) continue;
    // isPrompt
    if ( !(GenPart_statusFlags[i] & 1) ) continue;
    // LastCopy
    if ( !(GenPart_statusFlags[i] >> 13 & 1) ) continue;
    // motherIndx is valid
    if ( GenPart_genPartIdxMother[i] == -1 ) continue;
    
    VX.SetPtEtaPhiM( GenPart_pt[i] , GenPart_eta[i] , GenPart_phi[i] , GenPart_mass[i] );
    Int_t monIdx   = GenPart_genPartIdxMother[i];
    Int_t monpdgId = GenPart_pdgId[monIdx];
    Bool_t isW=false;
    Bool_t isH=false;
    while (monIdx>0){
      monpdgId = GenPart_pdgId[monIdx];
      if ( abs(monpdgId) == 24 ) isW=true;
      if ( abs(monpdgId) == 25 ) isH=true;
      monIdx = GenPart_genPartIdxMother[monIdx];
    }
    if ( ( isH && isW ) || ( isH && !isW ) ){
      GenQuark.push_back(VX);
      GenQuark_pdgId.push_back(GenPart_pdgId[i]);
    }
  }
  
  std::vector<std::pair<std::pair<TLorentzVector,TLorentzVector>, std::pair<Float_t,Int_t> >> pair_dR;
  // only one matches
  for ( UInt_t i=0 ; i < nGenJet ; i++ ){
    pair_dR.clear();
    VX.SetPtEtaPhiM( GenJet_pt[i] , GenJet_eta[i] , GenJet_phi[i] , GenJet_mass[i] );
    Int_t counter=0;
    for ( std::vector<TLorentzVector>::iterator it = GenQuark.begin() ; it != GenQuark.end(); ++it ){
      if ( GenJet_partonFlavour[i] != GenQuark_pdgId[counter] ) continue;
      Float_t dR = deltaR( VX.Phi() , VX.Eta() , it->Phi() , it->Eta() );
      if (dR > 0.3) continue;
      pair_dR.push_back(std::make_pair(std::make_pair(VX,*it),std::make_pair(dR,GenJet_partonFlavour[i]))); 
      counter++;
    } // end of Wquark loop
    if (pair_dR.size()>=1){
      pair_dR = IndexBydR( pair_dR );
      genjet.push_back(pair_dR[0].first.first);
      Wquark.push_back(pair_dR[0].first.second);
      genjet_matchdR.push_back(pair_dR[0].second.first);
      genjet_pdgId.push_back(pair_dR[0].second.second);
    }
  } // end of GenJet loop
  // 
  //////////////////////////////////////////////////////////
  // evaluation 
  // number of object
  Gen_nlepton1->Fill( lepton1.size() );
  Gen_nlepton2->Fill( lepton2.size() );
  Gen_nWquark->Fill( Wquark.size() );
  Gen_njet->Fill( genjet.size() );
  Gen_nWboson->Fill( Wboson.size() );
  Gen_nWHboson->Fill( WHboson.size() );
  Gen_nHboson->Fill( Hboson.size() );
  Gen_nNeutrino->Fill( Neutrino.size() );

  Gen_met_pt->Fill( VXX.Pt() );
  Gen_met_phi->Fill( VXX.Phi() );

  GenMETpt->Fill( GenMET_pt );
  GenMETphi->Fill( GenMET_phi );

  // sort the container in descending pt
  Wboson  = IndexByPt( Wboson  );
  WHboson = IndexByPt( WHboson );
  Hboson  = IndexByPt( Hboson  );
  lepton1 = IndexByPt( lepton1 );
  lepton2 = IndexByPt( lepton2 );
  Wquark  = IndexByPt( Wquark  );
  genjet = IndexByPt( genjet );
  Neutrino = IndexByPt( Neutrino );
  
  // fill tree
  gen_tree->Fill();
}

void analysis_Terminate(){

  gen_tree->Write();

  genlevel->cd();
  Gen_nlepton1->Write();
  Gen_nlepton2->Write();
  Gen_nWquark->Write();
  Gen_njet->Write();
  Gen_nWboson->Write();
  Gen_nWHboson->Write();
  Gen_nHboson->Write();
  Gen_nNeutrino->Write();
  Gen_met_pt->Write();
  Gen_met_phi->Write();
  GenMETpt->Write();
  GenMETphi->Write();

  out->Close();
}
