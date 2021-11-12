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
    std::pair< vector< std::pair< Math::PtEtaPhiMVector , int > > , vector< std::pair< Math::PtEtaPhiMVector , int > >  > out;
    
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
    out = std::make_pair( IndexByPt( outak4 ) , IndexByPt( outak8 ) );
    return out;
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
    .Define( "genjetak4_out"       , "genjet_out.first"         )
    .Define( "genjetak8_out"       , "genjet_out.second"         )
    .Define( "ngenjet_ak4"         , "static_cast<int>(genjetak4_out.size())" )
    .Define( "ngenjet_ak8"         , "static_cast<int>(genjetak8_out.size())" )
    .Filter( "ngenjet_ak4>=2"    , "filtering out event with less than 2 AK4 jets" )
    .Filter( "ngenjet_ak8>=2"    , "filtering out event with less than 2 AK8 jets" )
    // AK4
    .Define( "AK4jet1_Pt"    , "genjetak4_out[0].first.Pt()"                    )
    .Define( "AK4jet1_Eta"   , "genjetak4_out[0].first.Eta()"                   )
    .Define( "AK4jet1_Phi"   , "genjetak4_out[0].first.Phi()"                   )
    .Define( "AK4jet1_M"     , "genjetak4_out[0].first.M()"                     )
    .Define( "AK4jet1_pdgId" , "genjetak4_out[0].second"                        )
    .Define( "AK4jet2_Pt"    , "genjetak4_out[1].first.Pt()"                    )
    .Define( "AK4jet2_Eta"   , "genjetak4_out[1].first.Eta()"                   )
    .Define( "AK4jet2_Phi"   , "genjetak4_out[1].first.Phi()"                   )
    .Define( "AK4jet2_M"     , "genjetak4_out[1].first.M()"                     )
    .Define( "AK4jet2_pdgId" , "genjetak4_out[1].second"                        )
    // AK8
    .Define( "AK8jet1_Pt"    , "genjetak8_out[0].first.Pt()"                    )
    .Define( "AK8jet1_Eta"   , "genjetak8_out[0].first.Eta()"                   )
    .Define( "AK8jet1_Phi"   , "genjetak8_out[0].first.Phi()"                   )
    .Define( "AK8jet1_M"     , "genjetak8_out[0].first.M()"                     )
    .Define( "AK8jet1_pdgId" , "genjetak8_out[0].second"                        )
    .Define( "AK8jet2_Pt"    , "genjetak8_out[1].first.Pt()"                    )
    .Define( "AK8jet2_Eta"   , "genjetak8_out[1].first.Eta()"                   )
    .Define( "AK8jet2_Phi"   , "genjetak8_out[1].first.Phi()"                   )
    .Define( "AK8jet2_M"     , "genjetak8_out[1].first.M()"                     )
    .Define( "AK8jet2_pdgId" , "genjetak8_out[1].second"                        )
    ;
  
  return dfout;
}

#endif
