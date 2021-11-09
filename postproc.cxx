#include "postproc.h"
#include "genpart.h"
#include "genjets.h"

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
  
  for ( const auto& [ name , rdf ] : dataframes )
    {
      cout << "--> name : " << name << endl;
      ROOT::RDF::RNode rdff(rdf);
      auto df1 = mkGenpart( rdff );
      auto df2 = mkGenjet( df1 );
      
    }
  cout << endl;
  
  time.Stop();
  time.Print();
}
