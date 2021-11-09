#ifndef DRESSEDLEPTONS_H
#define DRESSEDLEPTONS_H

//* - jet is considered a b jet if there is at least one b "ghost" hadron clustered inside it (hadronFlavour = 5)
//* 
//* - jet is considered a c jet if there is at least one c and no b "ghost" hadrons clustered inside it (hadronFlavour = 4)
//* 
//* - jet is considered a light-flavour jet if there are no b or c "ghost" hadrons clustered inside it (hadronFlavour = 0)

template<typename T>
auto mkDressedLepton( T &df ) {
  using namespace ROOT::VecOps;
  
  // lambda function
  auto eval = [&](
		  int nGenDressedLepton_,
		  RVec<float>& GenDressedLepton_eta_,
		  RVec<float>& GenDressedLepton_mass_,
		  RVec<float>& GenDressedLepton_phi_,
		  RVec<float>& GenDressedLepton_pt_,
		  RVec<int>& GenDressedLepton_pdgId_
		  ){
    // take final state jet, and sorted it according to descending pt
    TLorentzVector dressedleptons;
    vector<TLorentzVector> DressedLeptons;
    //AK4
    for ( int i = 0 ; i < nGenDressedLepton_ ; i++ ){
      dressedleptons.SetPtEtaPhiM(0.,0.,0.,0.);
      if ( !( std::find( std::begin( lepton ), std::end( lepton ), GenDressedLepton_pdgId_[i] ) != std::end( lepton ) ) ) continue;
      
      dressedleptons.SetPtEtaPhiM( GenDressedLepton_pt_[i] , GenDressedLepton_eta_[i] , GenDressedLepton_phi_[i] , GenDressedLepton_mass_[i] );
      DressedLeptons.push_back( dressedleptons );
    }

    // sorting in descending pt
    DressedLeptons = IndexByPt( DressedLeptons );
    return DressedLeptons;
  };

  auto dfout = df
    .Define( "DressedLepton" , eval , {
	"nGenDressedLepton",
	  "GenDressedLepton_eta",
	  "GenDressedLepton_mass",
	  "GenDressedLepton_phi",
	  "GenDressedLepton_pt",
	  "GenDressedLepton_pdgId"
	  }
      )
    ;
  
  return dfout;
}

#endif
