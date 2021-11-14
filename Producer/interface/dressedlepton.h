#ifndef DRESSEDLEPTONS_H
#define DRESSEDLEPTONS_H

template<typename T>
auto mkDressedLepton( T &df ) {
  using namespace ROOT::VecOps;
  
  cout << " --> Registers mkDressedLepton <-- " << endl;

  // lambda function
  auto eval = [&](
		  RVec<float>& GenDressedLepton_eta_,
		  RVec<float>& GenDressedLepton_mass_,
		  RVec<float>& GenDressedLepton_phi_,
		  RVec<float>& GenDressedLepton_pt_,
		  RVec<int>& GenDressedLepton_pdgId_
		  ){
    int nGenDressedLepton_ = GenDressedLepton_pt_.size();

    RVec< std::pair< Math::PtEtaPhiMVector , int > > out;

    for ( auto i = 0 ; i < nGenDressedLepton_ ; i++ ){
      if ( !( std::find( std::begin( lepton ), std::end( lepton ), GenDressedLepton_pdgId_[i] ) != std::end( lepton ) ) ) continue;

      Math::PtEtaPhiMVector VX( GenDressedLepton_pt_[i] , GenDressedLepton_eta_[i] , GenDressedLepton_phi_[i] , GenDressedLepton_mass_[i] );
      out.push_back( std::make_pair( VX , GenDressedLepton_pdgId_[i] ) );
    }

    //flatten                                                                                                                                                                                             
    LorentzVec fp ; pdgIdVec id;
    out = IndexByPt( out );
    for ( auto thepair : out ) {
      fp.push_back(thepair.first); id.push_back(thepair.second);
    }
    return std::make_tuple( fp , id );
  }; 
  
  auto dfout = df
    .Define( "DressedLepton_out" , eval , {
	"GenDressedLepton_eta",
	  "GenDressedLepton_mass",
	  "GenDressedLepton_phi",
	  "GenDressedLepton_pt",
	  "GenDressedLepton_pdgId"
	  }
      )
    .Define( "dressedlepton"         , "std::get<0>(DressedLepton_out)" )
    .Define( "dressedlepton_pdgId"   , "std::get<1>(DressedLepton_out)" )
    ;
  
  return dfout;
}

#endif
