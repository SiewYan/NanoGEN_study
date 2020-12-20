#include "interface/helper.h"
#include "interface/config.h"
#include "interface/SF_maker.h"
#include "interface/bveto.h"

int main(int argc, char **argv) {

  ROOT::EnableImplicitMT(12);

  if(argc != 4) {
    std::cout << "Use executable with following arguments: ./processor name input output" << std::endl;
    return -1;
  }

  const std::string name   = argv[1];
  const std::string input  = argv[2];
  const std::string output = argv[3];

  // init cfg
  config_t mycfg;
  mycfg.year = "2016";
  mycfg.isMC = true;
  mycfg.base = std::getenv("PWD");

  std::cout << ">>> Process is mc: " << mycfg.isMC << std::endl;
  std::cout << ">>> Process input: " << input << std::endl;
  std::cout << ">>> Process output: " << output << std::endl;
  std::cout << ">>> Year: " << mycfg.year << std::endl;

  // Initialize time
  TStopwatch time;
  time.Start();

  // filelist
  std::vector<std::string> infiles;
  std::ifstream file(input);
  std::string str;
  while (std::getline(file, str)) { infiles.push_back(str); }
  
  // set path
  Helper::leptonID(mycfg);
  // electron
  makeSF_ele( mycfg.SF_files_map["electron"]["TightObjWP"][mycfg.year]["idSF"] , mycfg.h_SF_ele );
  makeSF_ele( mycfg.SF_files_map["electron"]["ttHMVA0p7"][mycfg.year]["ttHMVA"] , mycfg.h_SF_ele_ttHMVA );
  // muon
  makeSF_muon( mycfg.SF_files_map["muon"]["TightObjWP"][mycfg.year]["idSF"]  , mycfg.h_SF_mu_Id , "Muon_idSF2D" ); //  IdSF
  makeSF_muon( mycfg.SF_files_map["muon"]["TightObjWP"][mycfg.year]["isoSF"]  , mycfg.h_SF_mu_Iso , "Muon_isoSF2D" ); // IsoSF 
  makeSF_muon( mycfg.SF_files_map["muon"]["ttHMVA0p8"][mycfg.year]["ttHMVA"]  , mycfg.h_SF_mu_ttHMVA , "ttHMVA0p8_TightHWWCut" ); // tthMVA

  ROOT::RDataFrame df( "Events", infiles );
  auto df1 = bveto( df );
  auto df2 = hww_tthmva_sf( df1 , mycfg );
  auto df3 = df2.Define( "gen_promptmatch" , "Lepton_promptgenmatched[0]*Lepton_promptgenmatched[1]");

  auto outdf = df3;
  
  //auto df2 = df1
  //  .Filter( "1==1"   , "All raw event" )
  //  .Filter( "mll>12" , "mll>12" )
  //  .Filter( "Lepton_pt[0]>25 && Lepton_pt[1]>20" , "Lepton_pt[0]>25 && Lepton_pt[1]>20" )
  //  .Filter( "bVeto", "bVeto" )
  //  .Filter( "PuppiMET_pt > 30" , "PuppiMET_pt > 30" );

  // staging out
  std::vector<std::string> outbranch = mycfg.outBranch["mc"];
  outbranch.push_back( mycfg.HWW_WP[mycfg.year] );
  outbranch.push_back( mycfg.HWW_WP_SF[mycfg.year] );
  
  outdf.Snapshot( "Signals" , output, outbranch );
  
  //ROOT::RDF::SaveGraph( outdf ,"signal.dot");
  
  //auto report = outdf.Report();
  //report->Print();
  
  time.Stop();
  time.Print();
}
