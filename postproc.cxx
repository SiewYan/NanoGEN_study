#include "postproc.h"

int main() {

  //may return 0 when not able to detect   
  const auto processor_count = std::thread::hardware_concurrency();
  
  std::cout << "ncpu detected : " << processor_count << ", using it all!" << std::endl;
  ROOT::EnableImplicitMT(processor_count);

  // Initialize time
  TStopwatch time;
  time.Start();

  // filelist
  std::vector<std::string> infiles_1, infiles_2;
  std::ifstream file1("./data/samplelist_WWjets_sherpa.txt"), file2("./data/samplelist_WWjets_powheg.txt") ;
  std::map< std::string, std::vector<std::string> > dataframes;
  std::string str1, str2;

  while ( std::getline( file1 , str1 ) ) { infiles_1.push_back( "root://eosuser.cern.ch//" + str1 ); }
  dataframes["sherpa"] = infiles_1;

  while ( std::getline( file2 , str2 ) ) { infiles_2.push_back( "root://xrootd.ba.infn.it//" + str2 ); }
  dataframes["powheg"] = infiles_2;

  

  //
  
  /*
  if (mycfg.isMC) {
    // set path
    Helper::leptonID(mycfg);
    // electron
    makeSF_ele( mycfg.SF_files_map["electron"]["TightObjWP"][year]["idSF"] , mycfg.h_SF_ele );
    makeSF_ele( mycfg.SF_files_map["electron"]["ttHMVA0p7"][year]["ttHMVA"] , mycfg.h_SF_ele_ttHMVA );
    // muon
    makeSF_muon( mycfg.SF_files_map["muon"]["TightObjWP"][year]["idSF"]  , mycfg.h_SF_mu_Id , "Muon_idSF2D" ); //  IdSF
    makeSF_muon( mycfg.SF_files_map["muon"]["TightObjWP"][year]["isoSF"]  , mycfg.h_SF_mu_Iso , "Muon_isoSF2D" ); // IsoSF 
    makeSF_muon( mycfg.SF_files_map["muon"]["ttHMVA0p8"][year]["ttHMVA"]  , mycfg.h_SF_mu_ttHMVA , "ttHMVA0p8_TightHWWCut" ); // tthMVA
  }

  ROOT::RDataFrame df( "Events", infiles );
  auto df1 = twoLep_selection( df );  
  //auto df1 = threeLep_selection( df );
  auto df2 = df1.Filter("abs(Mll-91.2)<15" , "DY region : ( abs(mll-91.2)<15 )");
  
  // make lepton SF
  auto outdf = hww_tthmva_sf( df2 , mycfg );

  // staging out
  std::vector<std::string> outbranch;
  if ( name.find("Fake_") != std::string::npos ) {
    outbranch = mycfg.outBranch[ "fake_" + year ];
  }
  else{
    outbranch = mycfg.outBranch[ (mycfg.isMC) ? "mc_" + year : "data_" + year ];
  }

  outbranch.push_back( mycfg.HWW_WP[year] );
  if (mycfg.isMC){
    // gen-matching to prompt only (GenLepMatch2l matches to *any* gen lepton)
    outdf = outdf.Define("gen_promptmatch" , "Lepton_promptgenmatched[0]*Lepton_promptgenmatched[1]");
    
    if ( name.find("DY") != std::string::npos ){
      outdf = outdf.Define( "ptllDYW"    , ( name.find("LO") != std::string::npos ) ? mycfg.ptllDYW_LO[year] : mycfg.ptllDYW_NLO[year] );
      outbranch.push_back( "ptllDYW" );
    }
    // push back sf lep
    outbranch.push_back( mycfg.HWW_WP_SF[year] );
  }
  else{
    std::string tname = name;
    std::string s = "Fake_";
    std::string::size_type iss = tname.find(s);
    if (iss != std::string::npos)
      tname.erase(iss, s.length());
    std::cout<<"tname : "<< tname <<std::endl;
    outdf = outdf.Define( "triggers" , mycfg.triggers[tname] );
  }
  
  outdf.Snapshot( "flipper", output, outbranch );
  
  //ROOT::RDF::SaveGraph( outdf ,"graph_flip.dot");
  
  auto report = outdf.Report();
  report->Print();
  */
  time.Stop();
  time.Print();
}
