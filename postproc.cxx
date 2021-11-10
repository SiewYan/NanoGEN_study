#include "postproc.h"
#include "genpart.h"
#include "genjets.h"
#include "dressedlepton.h"

int main() {
  
  //may return 0 when not able to detect   
  const auto processor_count = std::thread::hardware_concurrency();
  
  cout << "ncpu detected : " << processor_count << ", using it all!" << endl;
  EnableImplicitMT(processor_count);

  // Initialize time
  TStopwatch time;
  time.Start();

  // filelist
  Mapdf dataframes = mapDataframe(  "./data/samplelist_WWjets_sherpa.txt" , "./data/samplelist_WWjets_powheg.txt" );
  
  // apply transformation
  for ( const auto& [ name , rdf ] : dataframes )
    {
      if ( name != "sherpa" ) continue;
      cout << "--> applying transformations on sample : " << name << endl;
      RNode rdff(rdf);
      auto df1 = mkGenpart( rdff );
      //auto df2 = mkGenjet( df1 );
      //auto df3 = mkDressedLepton( df2 );
      auto df3 = df1;
      
      cout << "--> applying actions on sample : " << name << endl;
      auto defColNames = df3.GetDefinedColumnNames();
      df3.Snapshot( "flatten" , name + ".root" , { "Lepton1_Pt" } ); //branchout ); //defColNames );
      ROOT::RDF::SaveGraph( df3 ,"graph_postproc.dot");
      auto report = df3.Report();
      report->Print();

      cout << endl;
      time.Stop();
      time.Print();
    }
}
