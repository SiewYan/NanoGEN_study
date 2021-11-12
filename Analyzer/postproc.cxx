#include "postproc.h"
#include "genpart.h"
//#include "genjets.h"
//#include "dressedlepton.h"

int main() {
  
  //may return 0 when not able to detect   
  const auto processor_count = std::thread::hardware_concurrency();
  
  cout << "ncpu detected : " << processor_count << ", using it all!" << endl;
  EnableImplicitMT(processor_count);

  // Initialize time
  TStopwatch time;
  time.Start();

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
      //if ( name != "powheg" ) continue;
      cout << "--> applying transformations : " << name << endl;
      RNode rdff(rdf);
      auto df1 = mkGenpart( rdff , name );
      //auto df2 = mkGenjet( df1 );
      //auto df3 = mkDressedLepton( df2 );
      
      auto df3 = df1;
      dataframes_.insert( { name , df3 } );
    }

  // apply action
  
  for ( const auto& [ name , rdf ] : dataframes_ )
    {
      cout << "--> applying actions : " << name << endl;
      RNode rdff(rdf);
      rdff.Snapshot( "flat" , name + ".root" , mkoutput(rdff) );
      
      ROOT::RDF::SaveGraph( rdff ,"graph_"+name+"_postproc.dot" );
      auto report = rdff.Report();
      report->Print();
      
      cout << endl;
    }
  
  time.Stop();
  time.Print();
}
