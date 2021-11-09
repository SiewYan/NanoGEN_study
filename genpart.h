
int boson[3]   = { 24 , -24 };
//int parton[8] = { 1, -1, 2, -2, 3, -3, 4, -4 };
int parton[11] = { 1, -1, 2, -2, 3, -3, 4, -4 , 5 , -5 }; //21
int lepton[4]  = { 11, -11, 13, -13 };
int neutrino[6] = { 12 , -12 , 14 , -14 , 16 , -16 };

template<typename T>
auto mkGen( T &df ) {
  using namespace ROOT::VecOps;
  
  //vector< vector<TLorentzVector> , vector<TLorentzVector> > out;
  std::pair< vector<TLorentzVector> , vector<TLorentzVector> > out;
  
  // lambda function
  auto eval = [&](
		  int nGenPart_,
		  RVec<float>& GenPart_eta_,
		  RVec<float>& GenPart_mass_,
		  RVec<float>& GenPart_phi_,
		  RVec<float>& GenPart_pt_,
		  RVec<int>& GenPart_genPartIdxMother_,
		  RVec<int>& GenPart_pdgId_,
		  RVec<int>& GenPart_status_,
		  RVec<int>& GenPart_statusFlags_
		  ){
    // pt,eta,phi,mass for leading pt of lepton; lepton; w1 ; w2 ; ww
    TLorentzVector VX,VXX;
    vector<TLorentzVector> Leptons, Bosons;
    for ( int i = 0 ; i < nGenPart_ ; i++ ){
      VX.SetPtEtaPhiM(0.,0.,0.,0.);
      VXX.SetPtEtaPhiM(0.,0.,0.,0.);
      if ( !( std::find( std::begin( lepton ), std::end( lepton ), GenPart_pdgId_[i] ) != std::end( lepton ) ) ) continue;
      // fromHardProcess
      if ( !(GenPart_statusFlags_[i] >> 8 & 1) ) continue;
      // isPrompt
      if ( !(GenPart_statusFlags_[i] & 1) ) continue;
      // status == 1
      if (GenPart_status_[i] != 1) continue;
      
      VX.SetPtEtaPhiM( GenPart_pt_[i] , GenPart_eta_[i] , GenPart_phi_[i] , GenPart_mass_[i] );
      int monIdx = GenPart_genPartIdxMother_[i];
      int monpdgid = GenPart_pdgId_[monIdx];
      
      //check mon
      Bool_t isW=false;
      while ( monIdx > 0 ){
	monpdgid = GenPart_pdgId_[monIdx];
	// break while loop if W mom is found for the lepton
	if ( abs(monpdgid) == 24 && GenPart_status_[monIdx] == 62 ) {
	  VXX.SetPtEtaPhiM( GenPart_pt_[monIdx] , GenPart_eta_[monIdx] , GenPart_phi_[monIdx] , GenPart_mass_[monIdx] );
	  Bosons.push_back(VXX);
	  isW=true;
	  break;
	}
	monIdx = GenPart_genPartIdxMother_[monIdx];
      }
      if (isW) Leptons.push_back(VX);  
    }
    // sorting in descending pt
    Leptons = IndexByPt( Leptons );
    Bosons = IndexByPt( Bosons );
    out = std::make_pair( Leptons , Bosons );
    return out;
  };

  auto dfout = df
    .Define( "vector_out" , eval , {
	"nGenPart",
	  "GenPart_eta",
	  "GenPart_mass",
	  "GenPart_phi",
	  "GenPart_pt",
	  "GenPart_genPartIdxMother",
	  "GenPart_pdgId",
	  "GenPart_status",
	  "GenPart_statusFlags"
	  }
      )
    .Define( "leptons" , "vector_out.first" )
    .Define( "bosons" , "vector_out.second" )
    ;
  
  return dfout;
}
