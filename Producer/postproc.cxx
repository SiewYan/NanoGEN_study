#include "interface/postproc.h"
#include "interface/genpart.h"
#include "interface/genjetAK4.h"
#include "interface/genjetAK8.h"
#include "interface/dressedlepton.h"

int main() {
  
  //may return 0 when not able to detect   
  const auto processor_count = std::thread::hardware_concurrency();
  
  cout << "ncpu detected : " << processor_count << ", using it all!" << endl;
  EnableImplicitMT(processor_count);

  // typedef map< string, RDataFrame >
  Mapdf dataframes = mapDataframe(  
				  { 
				    { "sherpa" , "./data/samplelist_WWjets_sherpa.txt" } ,
				      { "powheg" , "./data/samplelist_WWjets_powheg.txt" } 
				  } );
  Mapdf dataframes_;
  // apply transformation
  for ( const auto& [ name , rdf ] : dataframes )
    {
      cout << "--> applying transformations : " << name << endl;
      RNode rdff(rdf);
      auto df1 = mkGenpart( rdff , name );
      auto df2 = mkGenjetAK4( df1 );
      auto df3 = mkGenjetAK8( df2 );
      auto df4 = mkDressedLepton( df3 );
      
      dataframes_.insert( { name , df4 } );
    }

  // apply action
  
  for ( const auto& [ name , rdf ] : dataframes_ )
    {
      
      // Initialize time     
      TStopwatch time;
      time.Start();

      cout << "--> applying actions : " << name << endl;
      RNode rdff(rdf);
      rdff.Snapshot( "gen" , name + ".root" , mkoutput(rdff) );
      
      ROOT::RDF::SaveGraph( rdff ,"./graphs/graph_"+name+".dot" );
      auto report = rdff.Report();
      report->Print();
      
      time.Stop();
      time.Print();

      cout << endl;
    }
}
