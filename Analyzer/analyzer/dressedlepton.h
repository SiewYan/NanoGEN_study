#ifndef DRESSEDLEPTONS_H
#define DRESSEDLEPTONS_H

template<typename T>
auto mkDressedLepton( T &df ) {
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
    return IndexByPt( out );
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
    .Define( "ngendressedlepton"       , "static_cast<int>(DressedLepton_out.size())" )
    .Filter( "ngendressedlepton>=2"    , "filtering out event with less than 2 Gen Dressed leptons" )
    .Define( "gendressedlepton1_Pt"    , "DressedLepton_out[0].first.Pt()"                    )
    .Define( "gendressedlepton1_Eta"   , "DressedLepton_out[0].first.Eta()"                   )
    .Define( "gendressedlepton1_Phi"   , "DressedLepton_out[0].first.Phi()"                   )
    .Define( "gendressedlepton1_M"     , "DressedLepton_out[0].first.M()"                     )
    .Define( "gendressedlepton1_pdgId" , "DressedLepton_out[0].second"                        )
    .Define( "gendressedlepton2_Pt"    , "DressedLepton_out[1].first.Pt()"                    )
    .Define( "gendressedlepton2_Eta"   , "DressedLepton_out[1].first.Eta()"                   )
    .Define( "gendressedlepton2_Phi"   , "DressedLepton_out[1].first.Phi()"                   )
    .Define( "gendressedlepton2_M"     , "DressedLepton_out[1].first.M()"                     )
    .Define( "gendressedlepton2_pdgId" , "DressedLepton_out[1].second"                        )
    ;
  
  return dfout;
}

#endif
