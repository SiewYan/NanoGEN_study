#ifndef GENJETS_H
#define GENJETS_H

//* - jet is considered a b jet if there is at least one b "ghost" hadron clustered inside it (hadronFlavour = 5)
//* 
//* - jet is considered a c jet if there is at least one c and no b "ghost" hadrons clustered inside it (hadronFlavour = 4)
//* 
//* - jet is considered a light-flavour jet if there are no b or c "ghost" hadrons clustered inside it (hadronFlavour = 0)

template<typename T>
auto mkGenjet( T &df ) {
  using namespace ROOT::VecOps;
  
  //vector< vector<TLorentzVector> , vector<TLorentzVector> > out;
  std::pair< vector<TLorentzVector> , vector<TLorentzVector> > out;
  
  // lambda function
  auto eval = [&](
		  RVec<float>& GenJetAK8_eta_,
		  RVec<float>& GenJetAK8_mass_,
		  RVec<float>& GenJetAK8_phi_,
		  RVec<float>& GenJetAK8_pt_,
		  RVec<float>& GenJet_eta_,
		  RVec<float>& GenJet_mass_,
		  RVec<float>& GenJet_phi_,
		  RVec<float>& GenJet_pt_,
		  RVec<int>& GenJetAK8_partonFlavour_,
		  RVec<unsigned char>& GenJetAK8_hadronFlavour_,
		  RVec<int>& GenJet_partonFlavour_,
		  RVec<unsigned char>& GenJet_hadronFlavour_
		  ){
    // take final state jet, and sorted it according to descending pt
    TLorentzVector Ak4jet,Ak8jet;
    vector<TLorentzVector> GenJetsAK4, GenJetsAK8;
    int nGenJetAK8_ = GenJetAK8_pt_.size();
    int nGenJet_ = GenJet_pt_.size();
    
    //AK4
    for ( auto i = 0 ; i < nGenJet_ ; i++ ){
      Ak4jet.SetPtEtaPhiM(0.,0.,0.,0.);
      if ( !( std::find( std::begin( parton ), std::end( parton ), GenJet_partonFlavour_[i] ) != std::end( parton ) ) ) continue;
      
      //if ( !(GenJet_hadronFlavour_[i] == 0) ) continue;
      
      Ak4jet.SetPtEtaPhiM( GenJet_pt_[i] , GenJet_eta_[i] , GenJet_phi_[i] , GenJet_mass_[i] );
      GenJetsAK4.push_back( Ak4jet );
    }
    //AK8
    for ( auto i = 0 ; i < nGenJetAK8_ ; i++ ){
      Ak8jet.SetPtEtaPhiM(0.,0.,0.,0.);
      if ( !( std::find( std::begin( parton ), std::end( parton ), GenJetAK8_partonFlavour_[i] ) != std::end( parton ) ) ) continue;
      
      //if ( !(GenJetAK8_hadronFlavour_[i] == 0) ) continue;

      Ak8jet.SetPtEtaPhiM( GenJetAK8_pt_[i] , GenJetAK8_eta_[i] , GenJetAK8_phi_[i] , GenJetAK8_mass_[i] );
      GenJetsAK8.push_back( Ak8jet);
    }

    // sorting in descending pt
    GenJetsAK4 = IndexByPt( GenJetsAK4 );
    GenJetsAK8 = IndexByPt( GenJetsAK8 );
    out = std::make_pair( GenJetsAK4 , GenJetsAK8 );
    return out;
  };

  auto dfout = df
    .Define( "genjet" , eval , {
	  "GenJetAK8_eta",
	  "GenJetAK8_mass",
	  "GenJetAK8_phi",
	  "GenJetAK8_pt",
	  "GenJet_eta",
	  "GenJet_mass",
	  "GenJet_phi",
	  "GenJet_pt",
	  "GenJetAK8_partonFlavour",
	  "GenJetAK8_hadronFlavour",
	  "GenJet_partonFlavour",
	  "GenJet_hadronFlavour"
	  }
      )
    .Define( "genjetak4" , "genjet.first" )
    .Define( "genjetak8" , "genjet.second" )
    ;
  
  return dfout;
}

#endif
