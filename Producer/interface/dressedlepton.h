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
    const int nGenDressedLepton_ = GenDressedLepton_pt_.size();

    typeOut out;

    for ( auto i = 0 ; i < nGenDressedLepton_ ; i++ ){
      if ( !( std::find( std::begin( lepton ), std::end( lepton ), GenDressedLepton_pdgId_[i] ) != std::end( lepton ) ) ) continue;

      Math::PtEtaPhiMVector VX( GenDressedLepton_pt_[i] , GenDressedLepton_eta_[i] , GenDressedLepton_phi_[i] , GenDressedLepton_mass_[i] );
      out.push_back( std::make_pair( VX , GenDressedLepton_pdgId_[i] ) );
    }

    LorentzVec fp( Ncol , Vdummy ); vector<int> id( Ncol , -9999. );
    int ctr=0;
    out = IndexByPt( out );
    for ( auto thepair : out ) {
      fp.at(ctr) = thepair.first; id.at(ctr) = thepair.second;
      ctr++;
      if (ctr == Ncol) break;
    }

    return std::make_tuple( fp , id , static_cast<int>(out.size()) );
  }; 
  
  string colName = "DressedLepton";
  auto dfout = df.Define( 
			 colName + "_tuple" , eval ,
			 {
			   "GenDressedLepton_eta",
			     "GenDressedLepton_mass",
			     "GenDressedLepton_phi",
			     "GenDressedLepton_pt",
			     "GenDressedLepton_pdgId"
			     }
			  );
  return flattendf( dfout , colName );
}

#endif
