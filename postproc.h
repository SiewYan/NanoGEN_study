#ifndef POSTPROC_H
#define POSTPROC_H

#include "ROOT/RDataFrame.hxx"
#include "ROOT/RDFHelpers.hxx"
#include "ROOT/RVec.hxx"

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

Float_t deltaPhi(Float_t phi1, Float_t phi2) {
  Float_t PHI = fabs(phi1-phi2);
  if (PHI<=3.14159265)
    return PHI;
  else
    return 2*3.14159265-PHI;
}

Float_t deltaR(Float_t phi1, Float_t eta1, Float_t phi2, Float_t eta2) {
  //return sqrt((eta2-eta1)**2+deltaPhi(phi1,phi2)**2);                                                                                                                                  
  return sqrt( pow((eta2-eta1),2) + pow(deltaPhi(phi1,phi2),2) );
}

Float_t deltaEta(Float_t eta1, Float_t eta2) {
  return fabs(eta1 - eta2);
}

struct ptsorter {
  bool operator() (TLorentzVector i, TLorentzVector j) { return ( (i.Pt()) > (j.Pt()) ); } // sort in Descending order                                         
};

struct minR {
  bool operator() (std::pair<std::pair<TLorentzVector,TLorentzVector>, std::pair<Float_t,Int_t>> i, std::pair<std::pair<TLorentzVector,TLorentzVector>, std::pair<Float_t,Int_t>> j) { return ( (i.second.first) < (j.second.first) ); } // sort in Ascending order
};

std::vector<TLorentzVector> IndexByPt( std::vector<TLorentzVector> vector ){
  ptsorter comparator;
  std::sort (vector.begin() , vector.end() , comparator);
  return vector;
}

std::vector<std::pair<std::pair<TLorentzVector,TLorentzVector>, std::pair<Float_t,Int_t>>> IndexBydR(std::vector<std::pair<std::pair<TLorentzVector,TLorentzVector>, std::pair<Float_t,Int_t>>> vector){
  minR comparator;

  std::sort (vector.begin() , vector.end() , comparator);
  return vector;
}

#endif
