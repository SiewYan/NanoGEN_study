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
#include <TInterpreter.h>

//gInterpreter->GenerateDictionary( "vector<TLorentzVector>" , "vector" );
//#include "AutoDict_vector_TLorentzVector_.cxx"

using namespace ROOT;
using RNode = ROOT::RDF::RNode;
using namespace std;

typedef map< string, RDataFrame > Mapdf;

int boson[3]   = { 24 , -24 };
//int parton[8] = { 1, -1, 2, -2, 3, -3, 4, -4 };
int parton[11] = { 1, -1, 2, -2, 3, -3, 4, -4 , 5 , -5 }; //21 
int lepton[4]  = { 11, -11, 13, -13 };
int neutrino[6] = { 12 , -12 , 14 , -14 , 16 , -16 };


vector<string> branchout = {
  "run",
  "luminosityBlock",
  "event",
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

struct ptsorter {
  bool operator() (TLorentzVector i, TLorentzVector j) { return ( (i.Pt()) > (j.Pt()) ); } // sort in Descending order                                         
};

vector<TLorentzVector> IndexByPt( vector<TLorentzVector> vector ){
  ptsorter comparator;
  sort (vector.begin() , vector.end() , comparator);
  return vector;
}

// lambda function
auto add_p4 = [](float pt, float eta, float phi)
{
  return Math::PtEtaPhiMVector(pt, eta, phi, 0.);
};

auto pair = [](Math::PtEtaPhiMVector& p4_1, Math::PtEtaPhiMVector& p4_2)
{
  return vector<float>( { float((p4_1+p4_2).Pt()) , float((p4_1+p4_2).Eta()) , float((p4_1+p4_2).Phi()) , float((p4_1+p4_2).M()) } );
};

//auto unp4 = [](TLorentzVector p4)
//{
//  return Math::PtEtaPhiMVector(pt, eta, phi, 0.);
//};


#endif