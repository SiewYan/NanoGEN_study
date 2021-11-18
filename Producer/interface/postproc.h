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
//#include "TLorentzVector.h"
//#include <TInterpreter.h>
#include "../mydict.cxx"

//TInterpreter groot(); groot.GenerateDictionary( "vector<TLorentzVector>" , "vector" );

using namespace ROOT;
using RNode = ROOT::RDF::RNode;
using namespace std;

typedef map< string, RNode > Mapdf;
typedef std::vector<Math::PtEtaPhiMVector> LorentzVec;
typedef std::vector< std::pair<Math::PtEtaPhiMVector , int> > typeOut;
const int Ncol = 3;
Math::PtEtaPhiMVector Vdummy( -9999. , -9999. , -9999. , -9999. );

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
Mapdf mapDataframe( map<string,string> mapin ) {

  Mapdf mapout;

  for (const auto& [name, filelist] : mapin) {

    ifstream fin1( filelist.c_str() );
    vector<string> infiles;
    string str;
    while ( getline( fin1 , str ) ) { infiles.push_back( "root://eosuser.cern.ch//" + str ); }    

    RDataFrame df( "Events" , infiles );
    
    mapout.insert( { name , df } );
  }
  
  return mapout;  
}

//
struct ptsorter {
  bool operator() ( std::pair< Math::PtEtaPhiMVector , int > i, std::pair< Math::PtEtaPhiMVector , int > j) { return ( (i.first.Pt()) > (j.first.Pt()) ); } // sort in Descending order
};

//
std::vector< std::pair< Math::PtEtaPhiMVector , int > > IndexByPt( std::vector< std::pair< Math::PtEtaPhiMVector , int > > vector ){
  ptsorter comparator; sort (vector.begin() , vector.end() , comparator);
  return vector;
}

//
auto isOut = [](string x){
  return (
	  x.find("_tuple") != std::string::npos ||
	  x.find("_") == std::string::npos
	  );
};

//
template<typename T>
auto flattendf( T &df , string &collection ) {

  auto dfout_ = df
    .Define( collection        , "std::get<0>(" + collection + "_tuple)"  )
    .Define( collection + "Id" , "std::get<1>(" + collection + "_tuple)"  )
    .Define( "n_" + collection  , "std::get<2>(" + collection + "_tuple)" )
    ;
  
  for (auto i = 0; i < Ncol; ++i){
    
    // 4 vector kinematics
    for ( auto feature : { "Pt" , "Eta" , "Phi" , "M" } ) {
      string var = collection + to_string(i+1) + "_" + feature;
      string def = collection + "[" + to_string(i) + "]." + feature +"()";
      dfout_ = dfout_.Define( var , def );
    }
    
    // pdgid
    dfout_ = dfout_.Define( collection + to_string(i+1) + "_pdgId"  , collection + "Id[" + to_string(i) + "]" );
  }
  
  return dfout_;
}

//
auto mkoutput( RNode df ){
  
  auto defColNames = df.GetDefinedColumnNames();
  defColNames.erase(
		    std::remove_if(
				   defColNames.begin(),
				   defColNames.end(),
				   isOut
				   ),
		    defColNames.end()
		    );
  
  cout<<" --> output variables : "<<endl;
  for( auto f : defColNames ) cout<<" --> "<<f<<endl;
  return defColNames;
}

// lambda function
auto add_p4 = [](float pt, float eta, float phi)
{
  return Math::PtEtaPhiMVector(pt, eta, phi, 0.);
};

//
auto pair = [](Math::PtEtaPhiMVector& p4_1, Math::PtEtaPhiMVector& p4_2)
{
  return vector<float>( { float((p4_1+p4_2).Pt()) , float((p4_1+p4_2).Eta()) , float((p4_1+p4_2).Phi()) , float((p4_1+p4_2).M()) } );
};

//auto unp4 = [](TLorentzVector p4)
//{
//  return Math::PtEtaPhiMVector(pt, eta, phi, 0.);
//};
  
#endif
