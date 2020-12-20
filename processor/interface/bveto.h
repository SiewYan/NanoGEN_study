#ifndef BVETO_H
#define BVETO_H

#include "helper.h"
#include "config.h"

template < typename T>
auto bveto( T &df ){
  using namespace ROOT::VecOps;

  // Sum$(CleanJet_pt > 20. && abs(CleanJet_eta) < 2.5 && Jet_btagDeepB[CleanJet_jetIdx] > 0.1522) == 0
  auto bveto_maker = [](
			    const RVec<float>& cleanjet_pt     ,
			    const RVec<float>& cleanjet_eta    ,
			    const RVec<float>& jet_btagdeepb   ,
			    const RVec<int>&   cleanjet_jetidx
			    )
    {
      int nbjet = 0;
      for ( size_t ijet=0 ; ijet < cleanjet_pt.size() ; ijet++ ){
	int jetidx = cleanjet_jetidx[ijet];
	if ( cleanjet_pt[ijet]       < 20. ) continue;
	if ( abs(cleanjet_eta[ijet]) > 2.5 ) continue;
	if ( jet_btagdeepb[jetidx]   < 0.1522 ) continue;
	nbjet+=1;			 
      }
      return ( nbjet == 0 ) ? true : false ;
    };
  return df.Define( "bVeto" , bveto_maker , { "CleanJet_pt" , "CleanJet_eta" , "Jet_btagDeepB" , "CleanJet_jetIdx" } );
 
}

#endif
