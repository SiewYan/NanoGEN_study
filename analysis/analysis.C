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
TH1D* Gen_nWQuark;
TH1D* Gen_njet;
TH1D* Gen_nWboson;
TH1D* Gen_nWHboson;
TH1D* Gen_nHboson;
TH1D* Gen_nNeutrino;
TH1D* Gen_nNeutrino1;
TH1D* Gen_nNeutrino2;
TH1D* Gen_met_pt;
TH1D* Gen_met_phi;
TH1D* GenMETpt;
TH1D* GenMETphi;

TH1D* Gen_Hspin;

std::vector<TLorentzVector> Wboson;
std::vector<TLorentzVector> WHboson;
std::vector<TLorentzVector> Hboson;
std::vector<TLorentzVector> lepton1;
std::vector<TLorentzVector> lepton2;
std::vector<TLorentzVector> Wquark;
std::vector<TLorentzVector> genjet;
std::vector<TLorentzVector> Neutrino;
std::vector<TLorentzVector> neutrino1;
std::vector<TLorentzVector> neutrino2;
std::vector<TLorentzVector> MET;

// composite variable
std::vector<TLorentzVector> l1v1;
std::vector<TLorentzVector> l2v2;

std::vector<TLorentzVector> dijets;
std::vector<TLorentzVector> dileptons;
std::vector<TLorentzVector> lep2jets;
std::vector<TLorentzVector> dilep2jets;
std::vector<TLorentzVector> lv2jets;

std::vector<TLorentzVector> diquarks;
std::vector<TLorentzVector> lep2quarks;
std::vector<TLorentzVector> dilep2quarks;
std::vector<TLorentzVector> lv2quarks;

std::vector<Float_t> genjet_matchdR;
std::vector<Int_t> genjet_pdgId;

TFile* out = new TFile( "WHSS.root" , "recreate" );
TTree* gen_tree = new TTree( "gen" , "gen" );

TDirectory* genlevel =  out->mkdir("nGen_object");

void analysis_Begin(TTree*) {

  // generated object number
  Gen_nlepton1    = new TH1D ( "Gen_nlepton1"  , "Gen_nlepton1"   , 10 , 0  , 10     );
  Gen_nlepton2    = new TH1D ( "Gen_nlepton2"  , "Gen_nlepton2"   , 10 , 0  , 10     );
  Gen_nWquark     = new TH1D ( "Gen_nWquark"   , "Gen_nWquark"    , 10 , 0  , 10     );
  Gen_nWQuark     = new TH1D ( "Gen_nWQuark"   , "Gen_nWQuark"    , 10 , 0  , 10     );
  Gen_njet        = new TH1D ( "Gen_njet"      , "Gen_njet"       , 10 , 0  , 10     );
  Gen_nWboson     = new TH1D ( "Gen_nWboson"   , "Gen_nWboson"    , 10 , 0  , 10     );
  Gen_nWHboson    = new TH1D ( "Gen_nWHboson"  , "Gen_nWHboson"    , 10 , 0  , 10     );
  Gen_nHboson     = new TH1D ( "Gen_nHboson"   , "Gen_nHboson"    , 10 , 0  , 10     );
  Gen_nNeutrino   = new TH1D ( "Gen_nNeutrino" , "Gen_nNeutrino"    , 10 , 0  , 10     );
  Gen_nNeutrino1  = new TH1D ( "Gen_nNeutrino1" , "Gen_nNeutrino1"    , 10 , 0  , 10     );
  Gen_nNeutrino2  = new TH1D ( "Gen_nNeutrino2" , "Gen_nNeutrino2"    , 10 , 0  , 10     );
  Gen_met_pt      = new TH1D ( "Gen_met_pt"    , "Gen_met_pt"     , 50 , 0. , 200. );
  Gen_met_phi     = new TH1D ( "Gen_met_phi"   , "Gen_met_phi"     , 30 , 0. , 3.2 );
  GenMETpt        = new TH1D ( "GenMETpt"    , "GenMETpt"     , 50 , 0. , 200. );
  GenMETphi       = new TH1D ( "GenMETphi"   , "GenMETphi"     , 30 , 0. , 3.2 );
  
  Gen_Hspin       = new TH1D ( "Gen_Hspin"   , "Gen_Hspin" , 20 , -1 , 1 );
  
  // initialize branch
  gen_tree->Branch( "Wboson"   , &Wboson );
  gen_tree->Branch( "WHboson"  , &WHboson );
  gen_tree->Branch( "Hboson"   , &Hboson );
  gen_tree->Branch( "lepton1"  , &lepton1 );
  gen_tree->Branch( "lepton2"  , &lepton2 );
  gen_tree->Branch( "Wquark"   , &Wquark );
  gen_tree->Branch( "genjet"   , &genjet );
  gen_tree->Branch( "Neutrino" , &Neutrino );
  gen_tree->Branch( "neutrino1" , &neutrino1 );
  gen_tree->Branch( "neutrino2" , &neutrino2 );
  gen_tree->Branch( "MET"      , &MET );

  gen_tree->Branch( "l1v1"    , &l1v1 );
  gen_tree->Branch( "l2v2"    , &l2v2 );

  gen_tree->Branch( "dijets"    , &dijets );
  gen_tree->Branch( "dileptons" , &dileptons );
  gen_tree->Branch( "lep2jets" , &lep2jets );
  gen_tree->Branch( "dilep2jets" , &dilep2jets );
  gen_tree->Branch( "lv2jets" , &lv2jets );
  gen_tree->Branch( "diquarks"    , &diquarks );
  gen_tree->Branch( "lep2quarks" , &lep2quarks );
  gen_tree->Branch( "dilep2quarks" , &dilep2quarks );
  gen_tree->Branch( "lv2quarks" , &lv2quarks );

  gen_tree->Branch( "genjet_matchdR" , &genjet_matchdR );
  gen_tree->Branch( "genjet_pdgId" , &genjet_pdgId );
  
}

void analysis() {
  //Per event variables
  TLorentzVector VX;
  TLorentzVector VXX;
  
  Wboson.clear();
  WHboson.clear();
  Hboson.clear();
  lepton1.clear();
  lepton2.clear();
  Wquark.clear();
  genjet.clear();
  Neutrino.clear();
  neutrino1.clear();
  neutrino2.clear();
  MET.clear();
  l1v1.clear();
  l2v2.clear();
  dijets.clear();
  dileptons.clear();
  lep2jets.clear();
  dilep2jets.clear();
  lv2jets.clear();
  diquarks.clear();
  lep2quarks.clear();
  dilep2quarks.clear();
  lv2quarks.clear();
  
  genjet_matchdR.clear();
  genjet_pdgId.clear();

  Int_t bosons[3]   = { 24 , -24 , 25 };
  //Int_t partons[8] = { 1, -1, 2, -2, 3, -3, 4, -4 };
  Int_t partons[11] = { 1, -1, 2, -2, 3, -3, 4, -4 , 5 , -5 }; //21
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
      if ( isW && isH ) isW=false;
      monIdx = GenPart_genPartIdxMother[monIdx];
    }
    if (isW && !isH){
      lepton1.push_back(VX);
    }
    else if (!isW && isH){
      lepton2.push_back(VX);
    }
  }
  lepton1 = IndexByPt( lepton1 );
  lepton2 = IndexByPt( lepton2 );

  dileptons.push_back(lepton1[0] + lepton2[0]);
  
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
  Wboson  = IndexByPt( Wboson  );
  WHboson = IndexByPt( WHboson );
  Hboson  = IndexByPt( Hboson  );

  // GenPart (NEUTRINO)
  VXX.SetPtEtaPhiM(0., 0., 0., 0.);
  for ( UInt_t i=0 ; i < nGenPart ; i++ ){
    VX.SetPtEtaPhiM(0.,0.,0.,0.);
    if ( !( std::find(std::begin(neutrinos), std::end(neutrinos), GenPart_pdgId[i]) != std::end(neutrinos) ) ) continue;
    // fromHardProcess
    if ( !(GenPart_statusFlags[i] >> 8 & 1) ) continue;
    // isPrompt
    if ( !(GenPart_statusFlags[i] & 1) ) continue;
    // status == 1
    if (GenPart_status[i] != 1) continue;
    VX.SetPtEtaPhiM( GenPart_pt[i] , GenPart_eta[i] , GenPart_phi[i] , GenPart_mass[i] );
    Neutrino.push_back(VX);
    VXX+=VX;
    
    Int_t monIdx = GenPart_genPartIdxMother[i];
    Int_t monpdgid = GenPart_pdgId[monIdx];
    
    //check mon
    Bool_t isW=false;
    Bool_t isH=false;
    while (monIdx>0){
      monpdgid = GenPart_pdgId[monIdx];
      if ( abs(monpdgid) == 24 ) isW=true;
      if ( abs(monpdgid) == 25 ) isH=true;
      if ( isW && isH ) isW=false;
      monIdx = GenPart_genPartIdxMother[monIdx];
    }
    if (isW && !isH){
      neutrino1.push_back(VX);
    }
    else if (!isW && isH){
      neutrino2.push_back(VX);
    }
  }
  MET.push_back(VXX);

  Neutrino = IndexByPt( Neutrino );
  neutrino1 = IndexByPt( neutrino1 );
  neutrino2 = IndexByPt( neutrino2 );

  l1v1.push_back( lepton1[0] + neutrino1[0] );
  l2v2.push_back( lepton2[0] + neutrino2[0] );
  
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
      //if ( isW && isH ) isW=false;
      monIdx = GenPart_genPartIdxMother[monIdx];
    }
    if ( isH ){
      GenQuark.push_back(VX);
      GenQuark_pdgId.push_back(GenPart_pdgId[i]);
    }
  }
  
  std::vector<std::pair<std::pair<TLorentzVector,TLorentzVector>, std::pair<Float_t,Int_t> >> pair_dR;
  // quark match genjet
  // size of GenQuark is always 2
  //GenQuark = IndexByPt( GenQuark );
  for ( std::vector<TLorentzVector>::iterator it = GenQuark.begin() ; it != GenQuark.end(); ++it ){
    TLorentzVector Q = *it;
    pair_dR.clear();
    for ( UInt_t i=0 ; i < nGenJet ; i++ ){
      VX.SetPtEtaPhiM( GenJet_pt[i] , GenJet_eta[i] , GenJet_phi[i] , GenJet_mass[i] );
      Float_t dR = deltaR( Q.Phi() , Q.Eta() , VX.Phi() , VX.Eta() );
      if (dR > 0.4) continue;
      pair_dR.push_back(std::make_pair(std::make_pair(VX,Q),std::make_pair(dR,GenJet_partonFlavour[i])));
    } // end of genjet
    if (pair_dR.size() == 0 ) continue;
    // for multiple copy of matched genjet, take only the minimum dR's
    pair_dR = IndexBydR( pair_dR );
    
    TLorentzVector genjet_ = pair_dR[0].first.first;
    TLorentzVector Wquark_ = pair_dR[0].first.second;
    Float_t matchDr = pair_dR[0].second.first;
    Int_t genjet_pdgid = pair_dR[0].second.second;
    
    genjet.push_back(genjet_);
    Wquark.push_back(Wquark_);
    genjet_matchdR.push_back(matchDr);
    genjet_pdgId.push_back(genjet_pdgid);
    
  } // end of genquark

  if ( genjet.size() > 0 && Wquark.size() > 0 ){

    // remove duplicate genjet
    if ( genjet.size() == 2 ){
      if (genjet[0].Pt() == genjet[1].Pt())
	genjet.pop_back();
    }

    // sort in pt 
    //genjet = IndexByPt( genjet );
    //Wquark = IndexByPt( Wquark );
    
    TLorentzVector dijet = ( genjet.size()>=2 ) ? genjet[0] + genjet[1] : genjet[0]; // jet system taken inclusively up to 2 jets
    TLorentzVector diquark = ( Wquark.size()>=2 ) ? Wquark[0] + Wquark[1] : Wquark[0]; // quark system taken inclusively up to 2 quarks
    dijets.push_back(dijet);
    diquarks.push_back(diquark);
    // lepton2 + genjet
    lep2jets.push_back(lepton2[0] + dijets[0]);
    dilep2jets.push_back(lepton2[0] + lepton2[0] + dijets[0]);
    lv2jets.push_back( l2v2[0] + dijets[0]);
    // lepton2 + quark
    lep2quarks.push_back(lepton2[0] + diquarks[0]);
    dilep2quarks.push_back(lepton2[0] + lepton2[0] + diquarks[0]);
    lv2quarks.push_back( l2v2[0] + diquarks[0]);
  }
  // 
  //////////////////////////////////////////////////////////
  // evaluation 
  // number of object
  Gen_nlepton1->Fill( lepton1.size() );
  Gen_nlepton2->Fill( lepton2.size() );
  Gen_nWquark->Fill( Wquark.size() );
  Gen_nWQuark->Fill( GenQuark.size() );
  Gen_njet->Fill( genjet.size() );
  Gen_nWboson->Fill( Wboson.size() );
  Gen_nWHboson->Fill( WHboson.size() );
  Gen_nHboson->Fill( Hboson.size() );
  Gen_nNeutrino->Fill( Neutrino.size() );
  Gen_nNeutrino1->Fill( neutrino1.size() );
  Gen_nNeutrino2->Fill( neutrino2.size() );

  Gen_met_pt->Fill( VXX.Pt() );
  Gen_met_phi->Fill( VXX.Phi() );

  GenMETpt->Fill( GenMET_pt );
  GenMETphi->Fill( GenMET_phi );
  
  Gen_Hspin->Fill( TMath::Cos( Hboson[0].Phi() ) );
  // fill tree
  gen_tree->Fill();
}

void analysis_Terminate(){

  gen_tree->Write();

  genlevel->cd();
  Gen_nlepton1->Write();
  Gen_nlepton2->Write();
  Gen_nWquark->Write();
  Gen_nWQuark->Write();
  Gen_njet->Write();
  Gen_nWboson->Write();
  Gen_nWHboson->Write();
  Gen_nHboson->Write();
  Gen_nNeutrino->Write();
  Gen_nNeutrino1->Write();
  Gen_nNeutrino2->Write();
  Gen_met_pt->Write();
  Gen_met_phi->Write();
  GenMETpt->Write();
  GenMETphi->Write();
  Gen_Hspin->Write();

  out->Close();
}
