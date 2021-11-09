#ifndef POSTPROC_H
#define POSTPROC_H

#include "ROOT/RDataFrame.hxx"
#include "ROOT/RDFHelpers.hxx"
//#include "ROOT/RDF/RInterface.hxx"
#include "ROOT/RVec.hxx"
#include "ROOT/RSnapshotOptions.hxx"

#include "Math/Vector4D.h"
#include "TStopwatch.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <cmath>
#include <map>

#include "utility" // std::pair 
#include <algorithm> // for std::find
#include <iterator> // for std::begin, std::end
#include <thread>

//#include "TRandom3.h" 
#include "TLorentzVector.h"
//#include <TInterpreter.h>
//#include "AutoDict_vector_TLorentzVector_.cxx"
//gInterpreter->GenerateDictionary("vector<TLorentzVector>", "vector"); 

using namespace ROOT;
//using RNode = ROOT::RDF::RNode;
using namespace std;

typedef map< string, RDataFrame > Mapdf;

vector<string> listvar = {
  "run",
  "luminosityBlock",
  "event",
  "nGenJetAK8",
  "GenJetAK8_eta",
  "GenJetAK8_mass",
  "GenJetAK8_phi",
  "GenJetAK8_pt",
  "nGenJet",
  "GenJet_eta",
  "GenJet_mass",
  "GenJet_phi",
  "GenJet_pt",
  "nGenPart",
  "GenPart_eta",
  "GenPart_mass",
  "GenPart_phi",
  "GenPart_pt",
  "GenPart_genPartIdxMother",
  "GenPart_pdgId",
  "GenPart_status",
  "GenPart_statusFlags",
  "Generator_scalePDF",
  "Generator_weight",
  "GenVtx_x",
  "GenVtx_y",
  "GenVtx_z",
  "genWeight",
  "nPSWeight",
  "PSWeight",
  "GenMET_phi",
  "GenMET_pt",
  "MET_fiducialGenPhi",
  "MET_fiducialGenPt",
  "nGenIsolatedPhoton",
  "GenIsolatedPhoton_eta",
  "GenIsolatedPhoton_mass",
  "GenIsolatedPhoton_phi",
  "GenIsolatedPhoton_pt",
  "GenJetAK8_partonFlavour",
  "GenJetAK8_hadronFlavour",
  "GenJet_partonFlavour",
  "GenJet_hadronFlavour"
};

// 
Mapdf mapDataframe( string fsherpa , string fpowheg ) {

  ifstream fin1( fsherpa.c_str() ), fin2( fpowheg.c_str() );
  vector<string> infiles_1, infiles_2;
  string str1, str2;
  Mapdf mapout;
  
  while ( getline( fin1 , str1 ) ) { infiles_1.push_back( "root://eosuser.cern.ch//" + str1 ); }
  while ( getline( fin2 , str2 ) ) { infiles_2.push_back( "root://xrootd.ba.infn.it//" + str2 ); }
  RDataFrame df1( "Events" , infiles_1 ), df2( "Events" , infiles_2 );
  //RNode rdf1(df1), rdf2(df2);
  
  mapout.insert( { "sherpa" , df1 } );
  mapout.insert( { "powheg" , df2 } );
  
  return mapout;
  
}

auto add_p4 = [](float pt, float eta, float phi)
{
  return Math::PtEtaPhiMVector(pt, eta, phi, 0.);
};

auto pair = [](Math::PtEtaPhiMVector& p4_1, Math::PtEtaPhiMVector& p4_2)
{
  return vector<float>( { float((p4_1+p4_2).Pt()) , float((p4_1+p4_2).Eta()) , float((p4_1+p4_2).Phi()) , float((p4_1+p4_2).M()) } );
};

struct ptsorter {
  bool operator() (TLorentzVector i, TLorentzVector j) { return ( (i.Pt()) > (j.Pt()) ); } // sort in Descending order                                         
};

vector<TLorentzVector> IndexByPt( vector<TLorentzVector> vector ){
  ptsorter comparator;
  sort (vector.begin() , vector.end() , comparator);
  return vector;
}

#endif
