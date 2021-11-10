#ifndef GENPART_H
#define GENPART_H

template<typename T>
auto mkGenpart( T &df ) {
  using namespace ROOT::VecOps;
  
  //vector< vector<TLorentzVector> , vector<TLorentzVector> > out;
  std::pair< vector<TLorentzVector> , vector<TLorentzVector> > out;
  
  // lambda function
  auto eval = [&](
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
    int nGenPart_ = GenPart_pt_.size();
    vector<TLorentzVector> Leptons, Bosons;
    for ( auto i = 0 ; i < nGenPart_ ; i++ ){
      // look at only first 4 candidates
      //if ( i > 4 ) break;
      
      VX.SetPtEtaPhiM(0.,0.,0.,0.);
      VXX.SetPtEtaPhiM(0.,0.,0.,0.);
      if ( !( std::find( std::begin( lepton ), std::end( lepton ), GenPart_pdgId_[i] ) != std::end( lepton ) ) ) 
	continue;
      // fromHardProcess
      //if ( !(GenPart_statusFlags_[i] >> 8 & 1) ) continue;
      // isPrompt
      //if ( !(GenPart_statusFlags_[i] & 1) ) continue;
      // status == 1/3
      if ( GenPart_status_[i] != 1 ) continue;
 
      VX.SetPtEtaPhiM( GenPart_pt_[i] , GenPart_eta_[i] , GenPart_phi_[i] , GenPart_mass_[i] );
      int monIdx = GenPart_genPartIdxMother_[i];
      int monpdgid = GenPart_pdgId_[monIdx];

      // PASSING, but not Wboson selection
      cout << "passing GenPart_pdgId_[i] : " << GenPart_pdgId_[i] << endl;
      
      //check mon
      bool isW=false;
      int count=0;
      while ( monIdx > 0 ){
	count++;
	monpdgid = GenPart_pdgId_[monIdx];
	// break while loop if W mom is found for the lepton
	cout << "anchestry --> " << count << " : pdgId :" << monpdgid << " : status : " << 
	  GenPart_status_[monIdx] << " : flag : " << GenPart_statusFlags_[i] << endl;
	
	if ( abs(monpdgid) == 24 && GenPart_status_[monIdx] == 62 ) {
	  VXX.SetPtEtaPhiM( GenPart_pt_[monIdx] , GenPart_eta_[monIdx] , GenPart_phi_[monIdx] , GenPart_mass_[monIdx] );
	  Bosons.push_back(VXX);
	  isW=true;
	  break;
	}
	monIdx = GenPart_genPartIdxMother_[monIdx];
      }
      
      if (isW) Leptons.push_back(VX);
      cout<<"Leptons size : "<< Leptons.size() <<endl;
    }
    // sorting in descending pt
    //Leptons = IndexByPt( Leptons );
    //Bosons = IndexByPt( Bosons );
    //out = std::make_pair( Leptons , Bosons );
    return out;
  };

  auto dfout = df
    .Define( "genpart" , eval , { "GenPart_eta" , "GenPart_mass" , "GenPart_phi" , "GenPart_pt" , 
	  "GenPart_genPartIdxMother" , "GenPart_pdgId" , "GenPart_status" , "GenPart_statusFlags" }
      )
    //.Define( "Leptons"  , "genpart.first"   )
    
    .Define( "Lepton1_Pt"  , "genpart.first[0].Pt()"   )
    .Define( "Lepton1_Eta" , "genpart.first[0].Eta()"  )
    .Define( "Lepton1_Phi" , "genpart.first[0].Phi()"  )
    .Define( "Lepton1_M"   , "genpart.first[0].M()"    )
    /*
    .Define( "Lepton2_Pt"  , "genpart.first[1].Pt()"   )
    .Define( "Lepton2_Eta" , "genpart.first[1].Eta()"  )
    .Define( "Lepton2_Phi" , "genpart.first[1].Phi()"  )
    .Define( "Lepton2_M"   , "genpart.first[1].M()"    )
    .Define( "Wboson1_Pt"  , "genpart.second[0].Pt()"  )
    .Define( "Wboson1_Eta" , "genpart.second[0].Eta()" )
    .Define( "Wboson1_Phi" , "genpart.second[0].Phi()" )
    .Define( "Wboson1_M"   , "genpart.second[0].M()"   )
    .Define( "Wboson2_Pt"  , "genpart.second[1].Pt()"  )
    .Define( "Wboson2_Eta" , "genpart.second[1].Eta()" )
    .Define( "Wboson2_Phi" , "genpart.second[1].Phi()" )
    .Define( "Wboson2_M"   , "genpart.second[1].M()"   )
    */
    ;
  
  return dfout;
}

#endif
