#ifndef GENJETAK8_H
#define GENJETAK8_H

//* - jet is considered a b jet if there is at least one b "ghost" hadron clustered inside it (hadronFlavour = 5)
//* 
//* - jet is considered a c jet if there is at least one c and no b "ghost" hadrons clustered inside it (hadronFlavour = 4)
//* 
//* - jet is considered a light-flavour jet if there are no b or c "ghost" hadrons clustered inside it (hadronFlavour = 0)

template<typename T>
auto mkGenjetAK8( T &df ) {
  using namespace ROOT::VecOps;

  cout << " --> Registers mkGenjetAK8 <-- " << endl;
  
  // lambda function
  auto eval = [&](
		  RVec<float>& GenJet_eta_,
		  RVec<float>& GenJet_mass_,
		  RVec<float>& GenJet_phi_,
		  RVec<float>& GenJet_pt_,
		  RVec<int>& GenJet_partonFlavour_,
		  RVec<unsigned char>& GenJet_hadronFlavour_
		  ){
    const int nGenJet_ = GenJet_pt_.size();

    typeOut out;
    
    //AK4
    for ( auto i = 0 ; i < nGenJet_ ; i++ ){
      
      if ( !( std::find( std::begin( parton ), std::end( parton ), GenJet_partonFlavour_[i] ) != std::end( parton ) ) ) continue;

      if ( GenJet_hadronFlavour_[i] != 0 ) continue;
      
      Math::PtEtaPhiMVector VX( GenJet_pt_[i] , GenJet_eta_[i] , GenJet_phi_[i] , GenJet_mass_[i] );
      out.push_back( std::make_pair( VX , GenJet_partonFlavour_[i] ) );
      
    }
    
    return mktuple( out );
  };
  
  // run module
  string colName = "GenJetAK8";
  auto dfout = df.Define(
			 colName + "_tuple" , eval ,
			 {
			   "GenJetAK8_eta",
			     "GenJetAK8_mass",
			     "GenJetAK8_phi",
			     "GenJetAK8_pt",
			     "GenJetAK8_partonFlavour",
			     "GenJetAK8_hadronFlavour"
			     }
			 );
  return flattendf( dfout , colName );
}

#endif
