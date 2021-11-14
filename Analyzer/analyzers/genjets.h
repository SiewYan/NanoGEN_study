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

  cout << " --> Registers mkGenjet <-- " << endl;
  
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
    const int nGenJet_ = GenJet_pt_.size();
    const int nGenJetAK8_ = GenJetAK8_pt_.size();

    RVec< std::pair< Math::PtEtaPhiMVector , int > > out_ak4;
    RVec< std::pair< Math::PtEtaPhiMVector , int > > out_ak8;
    
    //AK4
    for ( auto i = 0 ; i < nGenJet_ ; i++ ){
      
      if ( !( std::find( std::begin( parton ), std::end( parton ), GenJet_partonFlavour_[i] ) != std::end( parton ) ) ) continue;

      if ( GenJet_hadronFlavour_[i] != 0 ) continue;
      
      Math::PtEtaPhiMVector VX( GenJet_pt_[i] , GenJet_eta_[i] , GenJet_phi_[i] , GenJet_mass_[i] );
      out_ak4.push_back( std::make_pair( VX , GenJet_partonFlavour_[i] ) );
      
    }

    //AK8
    for ( auto i = 0 ; i < nGenJetAK8_ ; i++ ){

      if ( !( std::find( std::begin( parton ), std::end( parton ), GenJetAK8_partonFlavour_[i] ) != std::end( parton ) ) ) continue;

      if ( GenJetAK8_hadronFlavour_[i] != 0 )continue;

      Math::PtEtaPhiMVector VX( GenJetAK8_pt_[i] , GenJetAK8_eta_[i] , GenJetAK8_phi_[i] , GenJetAK8_mass_[i] );
      out_ak8.push_back( std::make_pair( VX , GenJetAK8_partonFlavour_[i] ) );
      
    }

    // sorting in descending pt
    out_ak4 = IndexByPt( out_ak4 ); out_ak8 = IndexByPt( out_ak8 );
    LorentzVec fp_ak4, fp_ak8; pdgIdVec id_ak4, id_ak8;

    for ( auto thepair : out_ak4 ) {
      fp_ak4.push_back(thepair.first); id_ak4.push_back(thepair.second);
    }
    for ( auto thepair : out_ak8 ) {
      fp_ak8.push_back(thepair.first); id_ak8.push_back(thepair.second);
    }

    return std::make_tuple( fp_ak4 , id_ak4 , fp_ak8 , id_ak8 );
  };
  
  auto dfout = df
    .Define( "genjet_out" , eval , {
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
    .Define( "GenJetAK4"       , "std::get<0>(genjet_out)"         )
    .Define( "GenJetAK4_pdgId" , "std::get<1>(genjet_out)"         )
    .Define( "GenJetAK8"       , "std::get<2>(genjet_out)" )
    .Define( "GenJetAK8_pdgId" , "std::get<3>(genjet_out)" )
    ;
  
  return dfout;
}

#endif
