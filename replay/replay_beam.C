// FIXME 
// R__LOAD_LIBRARY(/adaqfs/home/a-onl/halla_online_beam_check/customLibrary/FadcRasteredBeam/install/lib64/libfrb.so)

#include <cstdlib>
#include <iostream>
#include <string> 

#include "TStyle.h"
#include "TString.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TH2F.h"

#include "THaRun.h"
#include "THaEvent.h"
#include "THaAnalyzer.h"
#include "THaApparatus.h"
#include "THaVarList.h"
#include "THaInterface.h"
#include "THaHRS.h"
#include "THaDecData.h"

#include "FadcRasteredBeam.h"

void replay_beam_test(const char *filebase,unsigned int nev=-1,const char *experiment="gmn"); 

int main(int argc,char *argv[]){

   new THaInterface( "The Hall A analyzer", &argc, argv, 0, 0, 1 );

   std::string filebase; 

   unsigned int nev = -1;
   if(argc<2 || argc>3){
     cout << "Usage: replay_beam filebase(char*) nev(uint)" << endl;
     return -1;
   }

   filebase = argv[1]; 
   if(argc==3) nev = std::atoi(argv[2]); 

   if(nev>0){
      replay_beam_test(filebase.c_str(),nev);
   }else{
      replay_beam_test(filebase.c_str());
   }

   return 0;
}
//______________________________________________________________________________
void replay_beam_test(const char *filebase,unsigned int nev){

   std::string odef_path = "./def/output_rastersize.def"; 
   std::string cdef_path = "./def/cuts_rastersize.def"; 

   THaEvent* event = new THaEvent;

   // Set up the analyzer
   THaAnalyzer* analyzer = THaAnalyzer::GetInstance();
   if(analyzer){
      analyzer->Close();
   }else{
      analyzer = new THaAnalyzer;
   }
 
  // add the LHRS (where the beam signals are)  
  THaHRS* HRSL = new THaHRS("L","Left arm HRS");
  HRSL->AutoStandardDetectors(kFALSE);
  gHaApps->Add( HRSL );

  // add decoder
  THaApparatus* decL = new THaDecData("DL","Misc. Decoder Data");
  gHaApps->Add( decL );

  // add rastered beam
  THaApparatus* Lrb = new FadcRasteredBeam("Lrb","Raster Beamline for FADC");
  gHaApps->Add(Lrb);

  analyzer->SetEvent( event );
  analyzer->SetOutFile( rootfname );

  analyzer->SetCompressionLevel(1);
  analyzer->SetOdefFile(odef_path.c_str());
  analyzer->SetCutFile(cdef_path.c_str());

  THaRun* run = new THaRun( codafname );
  // run->SetFirstEvent(1);
  run->SetLastEvent(nev);

  TString out_dir = gSystem->Getenv("OUT_DIR");
  if( out_dir.IsNull() ) out_dir = ".";
  TString out_file = out_dir + "/" + Form("replayed_%s.root", filebase);
  
  analyzer->SetOutFile( out_file.Data() );
  cout << "output file " << out_file.Data() << " set up " << endl; 
  // File to record cuts accounting information
  analyzer->SetSummaryFile("sbs_beam_test.log"); // optional
 
  // run analysis 
  analyzer->SetVerbosity(10);   
  analyzer->Process(*run);
 
  // clean up  
  delete analyzer;
  gHaVars->Clear();
  gHaPhysics->Delete();
  gHaApps->Delete();
}
