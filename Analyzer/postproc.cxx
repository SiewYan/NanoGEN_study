#include "postproc.h"
#include "analyzers/genpart.h"
#include "analyzers/genjets.h"
#include "analyzers/dressedlepton.h"

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
  const int npar =2;
  // apply transformation
  for ( const auto& [ name , rdf ] : dataframes )
    {
      //if ( name != "powheg" ) continue;
      cout << "--> applying transformations : " << name << endl;
      RNode rdff(rdf);
      auto df1 = mkGenpart( rdff , name , npar );
      auto df2 = mkGenjet( df1 , npar );
      auto df3 = mkDressedLepton( df2 , npar );
      
      dataframes_.insert( { name , df3 } );
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
