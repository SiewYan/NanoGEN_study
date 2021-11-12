#ifndef DRESSEDLEPTONS_H
#define DRESSEDLEPTONS_H

template<typename T>
auto mkDressedLepton( T &df , const int &nlep ) {
  using namespace ROOT::VecOps;
  
  // lambda function
  auto eval = [&](
		  RVec<float>& GenDressedLepton_eta_,
		  RVec<float>& GenDressedLepton_mass_,
		  RVec<float>& GenDressedLepton_phi_,
		  RVec<float>& GenDressedLepton_pt_,
		  RVec<int>& GenDressedLepton_pdgId_
		  ){
    int nGenDressedLepton_ = GenDressedLepton_pt_.size();

    vector< std::pair< Math::PtEtaPhiMVector , int > > out;

    for ( auto i = 0 ; i < nGenDressedLepton_ ; i++ ){
      if ( !( std::find( std::begin( lepton ), std::end( lepton ), GenDressedLepton_pdgId_[i] ) != std::end( lepton ) ) ) continue;

      Math::PtEtaPhiMVector VX( GenDressedLepton_pt_[i] , GenDressedLepton_eta_[i] , GenDressedLepton_phi_[i] , GenDressedLepton_mass_[i] );
      out.push_back( std::make_pair( VX , GenDressedLepton_pdgId_[i] ) );
    }
    
    // sorting in descending pt
    return std::tuple( IndexByPt( out , nlep ) , static_cast<int>(out.size()) );
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
    .Define( "dressedlepton_out"   , "std::get<0>(DressedLepton_out)" )
    .Define( "ngendressedlepton"   , "std::get<1>(DressedLepton_out)" )
    ;
  
  for (auto i = 0; i < nlep; ++i){

    dfout = dfout.Define( "gendressedlepton" + to_string(i+1) + "_pdgId" ,
                          "dressedlepton_out[" + to_string(i) + "].second" );
    
    // 4 vectors                                                                                                      
    for ( auto feature : { "Pt" , "Eta" , "Phi" , "M" } ) {
      string var = "gendressedlepton" + to_string(i+1) + "_" + feature;
      string def = "dressedlepton_out[" + to_string(i) + "].first."+ feature +"()";
      dfout = dfout.Define( var , def );
    }
  }
  
  return dfout;
}

#endif
