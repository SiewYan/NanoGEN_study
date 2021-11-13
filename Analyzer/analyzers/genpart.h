#ifndef GENPART_H
#define GENPART_H

template<typename T>
auto mkGenpart( T &df , const string &name ) {
  using namespace ROOT::VecOps;
    
  // lambda function
  auto eval = [&](
		  RVec<float>& GenPart_eta_,
		  RVec<float>& GenPart_mass_,
		  RVec<float>& GenPart_phi_,
		  RVec<float>& GenPart_pt_,
		  RVec<int>& GenPart_genPartIdxMother_,
		  RVec<int>& GenPart_pdgId_,
		  RVec<int>& GenPart_status_,
		  RVec<int>& GenPart_statusFlags_
		  ){
    // pt,eta,phi,mass for leading pt of lepton; lepton; w1 ; w2 ; ww
    const int nGenPart_ = GenPart_pt_.size();
    
    //vector< std::pair< Math::PtEtaPhiMVector , int > > out;
    RVec< std::pair<Math::PtEtaPhiMVector , int> > out;
    
    for ( auto i = 0 ; i < nGenPart_ ; i++ ){
      
      if ( !( std::find( std::begin( lepton ), std::end( lepton ), GenPart_pdgId_[i] ) != std::end( lepton ) ) ) 
	continue;
      
      // fromHardProcess
      if ( !(GenPart_statusFlags_[i] >> 8 & 1) ) continue;
      // isPrompt
      if ( !(GenPart_statusFlags_[i] & 1) ) continue;
      // status == 1/3
      if ( 
	  ( GenPart_status_[i] != 1 && name == "powheg" ) || 
	  ( GenPart_status_[i] != 3 && name == "sherpa" )
	   ) continue;
      
      Math::PtEtaPhiMVector VX( GenPart_pt_[i] , GenPart_eta_[i] , GenPart_phi_[i] , GenPart_mass_[i] );
      out.push_back( std::make_pair( VX , GenPart_pdgId_[i] ) );      
      
      /**
      int monIdx = GenPart_genPartIdxMother_[i];
      int monpdgid = GenPart_pdgId_[monIdx];
      
      //check mon
      
      bool isW=false;
      int count=0;
      while ( monIdx > 0 ){
	count++;
	monpdgid = GenPart_pdgId_[monIdx];
	// break while loop if W mom is found for the lepton
	cout << "anchestry --> " << count << " : pdgId :" << monpdgid << " : status : " << 
	  GenPart_status_[monIdx] << " : flag : " << GenPart_statusFlags_[i] << endl;
	
	if ( abs(monpdgid) == 24 && GenPart_status_[monIdx] == 62 ) {
	  VXX.SetPtEtaPhiM( GenPart_pt_[monIdx] , GenPart_eta_[monIdx] ,
			    GenPart_phi_[monIdx] , GenPart_mass_[monIdx]
			    );
	  Bosons.push_back(VXX);
	  isW=true;
	  break;
	}
	monIdx = GenPart_genPartIdxMother_[monIdx];
      }
      
      if (isW) Leptons.push_back(VX);
      **/
      
    }

    //flatten 
    RVec<Math::PtEtaPhiMVector> fp ; RVec<int> id;
    out = IndexByPt( out );
    for ( auto thepair : out ) {
      fp.push_back(thepair.first); id.push_back(thepair.second);
    }
    return std::make_tuple( fp , id );
  };

  auto dfout = df
    .Define( "genpart_out" , eval , { "GenPart_eta" , "GenPart_mass" , "GenPart_phi" , "GenPart_pt" , 
	  "GenPart_genPartIdxMother" , "GenPart_pdgId" , "GenPart_status" , "GenPart_statusFlags" }
      )
    .Define( "Lepton"        , "std::get<0>(genpart_out)"                )
    .Define( "Lepton_pdgId"  , "std::get<1>(genpart_out)"                )
    ;
  
  return dfout;
}

#endif
