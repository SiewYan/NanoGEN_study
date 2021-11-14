#include <vector>
#include "ROOT/RVec.hxx"
#include "Math/Vector4D.h"
#include "Math/Vector4Dfwd.h"

#ifdef __ROOTCLING__
//#pragma link C++ class vector<ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiM4D<double> > > +;
#pragma link C++ class vector<ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiM4D<double> >,ROOT::Detail::VecOps::RAdoptAllocator<ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiM4D<double> > > > +;
#endif
