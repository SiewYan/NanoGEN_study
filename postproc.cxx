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
      cout << "--> applying transformations on sample : " << name << endl;
      ROOT::RDF::RNode rdff(rdf);
      auto df1 = mkGenpart( rdff );
      auto df2 = mkGenjet( df1 );
      auto df3 = mkDressedLepton( df2 );
    }

  // apply action
  for ( const auto& [ name , rdf ] : dataframes )
    { 
      cout << "--> applying action on sample : " << name << endl;
      ROOT::RDF::RNode rdff(rdf);
      auto defColNames = rdff.GetDefinedColumnNames();
      rdff.Snapshot( "trimmed", name + ".root" , defColNames );
      ROOT::RDF::SaveGraph( rdff ,"graph_flip.dot");
      auto report = rdff.Report();
      report->Print();

      cout << endl;
      time.Stop();
      time.Print();
    }
}
