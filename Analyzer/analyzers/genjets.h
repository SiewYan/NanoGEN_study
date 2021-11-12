#ifndef GENJETS_H
#define GENJETS_H

//* - jet is considered a b jet if there is at least one b "ghost" hadron clustered inside it (hadronFlavour = 5)
//* 
//* - jet is considered a c jet if there is at least one c and no b "ghost" hadrons clustered inside it (hadronFlavour = 4)
//* 
//* - jet is considered a light-flavour jet if there are no b or c "ghost" hadrons clustered inside it (hadronFlavour = 0)

template<typename T>
auto mkGenjet( T &df , const int &njet ) {
  using namespace ROOT::VecOps;
  
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
    int nGenJet_ = GenJet_pt_.size();
    int nGenJetAK8_ = GenJetAK8_pt_.size();

    vector< std::pair< Math::PtEtaPhiMVector , int > > outak4;
    vector< std::pair< Math::PtEtaPhiMVector , int > > outak8;

    //out
    //std::pair< vector< std::pair< Math::PtEtaPhiMVector , int > > , vector< std::pair< Math::PtEtaPhiMVector , int > >  > out;
    
    //AK4
    for ( auto i = 0 ; i < nGenJet_ ; i++ ){
      
      if ( !( std::find( std::begin( parton ), std::end( parton ), GenJet_partonFlavour_[i] ) != std::end( parton ) ) ) continue;

      if ( GenJet_hadronFlavour_[i] != 0 ) continue;
      
      Math::PtEtaPhiMVector VX( GenJet_pt_[i] , GenJet_eta_[i] , GenJet_phi_[i] , GenJet_mass_[i] );
      outak4.push_back( std::make_pair( VX , GenJet_partonFlavour_[i] ) );
      
    }

    //AK8
    for ( auto i = 0 ; i < nGenJetAK8_ ; i++ ){

      if ( !( std::find( std::begin( parton ), std::end( parton ), GenJetAK8_partonFlavour_[i] ) != std::end( parton ) ) ) continue;

      if ( GenJetAK8_hadronFlavour_[i] != 0 )continue;

      Math::PtEtaPhiMVector VX( GenJetAK8_pt_[i] , GenJetAK8_eta_[i] , GenJetAK8_phi_[i] , GenJetAK8_mass_[i] );
      outak8.push_back( std::make_pair( VX , GenJetAK8_partonFlavour_[i] ) );
      
    }

    // sorting in descending pt
    return std::make_tuple( 
			   std::make_pair( IndexByPt( outak4 , njet ) , static_cast<int>( outak4.size() ) ),
			   std::make_pair( IndexByPt( outak8 , njet ) , static_cast<int>( outak4.size() ) )
			    );
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
    .Define( "genjetak4_out"       , "std::get<0>(genjet_out).first"         )
    .Define( "genjetak8_out"       , "std::get<1>(genjet_out).first"         )
    .Define( "nAK4jet"         , "std::get<0>(genjet_out).second" )
    .Define( "nAK8jet"         , "std::get<1>(genjet_out).second" )
    ;
  
  for (auto i = 0; i < njet; ++i){

    //AK4
    dfout = dfout.Define( "AK4jet" + to_string(i+1) + "_pdgId" ,
                          "genjetak4_out[" + to_string(i) + "].second" );
    //AK8
    dfout = dfout.Define( "AK8jet" + to_string(i+1) + "_pdgId" ,
                          "genjetak8_out[" + to_string(i) + "].second" );

    // 4 vector
    // AK4
    for ( auto feature : { "Pt" , "Eta" , "Phi" , "M" } ) {
      string var = "AK4jet" + to_string(i+1) + "_" + feature;
      string def = "genjetak4_out[" + to_string(i) + "].first."+ feature +"()";
      dfout = dfout.Define( var , def );
    }
    
    // AK8 
    for ( auto feature : { "Pt" , "Eta" , "Phi" , "M" } ) {
      string var = "AK8jet" + to_string(i+1) + "_" + feature;
      string def = "genjetak8_out[" + to_string(i) + "].first."+ feature +"()";
      dfout = dfout.Define( var , def );
    }
  }
  
  return dfout;
}

#endif
