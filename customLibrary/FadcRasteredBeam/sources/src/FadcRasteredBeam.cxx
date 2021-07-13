#include "FadcRasteredBeam.h"
//_____________________________________________________________________________
FadcRasteredBeam::FadcRasteredBeam( const char* name, const char* description ) :
    THaBeam( name, description ) 
{
  AddDetector( new FadcRaster("Raster2","downstream raster") );
  AddDetector( new FadcRaster("Raster","upstream raster") );
  AddDetector( new FadcBPM("BPMA","1st BPM") );
  AddDetector( new FadcBPM("BPMB","2nd BPM") );

}
//_____________________________________________________________________________
Int_t FadcRasteredBeam::Reconstruct()
{

  TIter nextDet( fDetectors ); 

  nextDet.Reset();

  // This apparatus assumes that there is only one detector 
  // in the list. If someone adds detectors by hand, the first 
  // detector in the list will be used to get the beam position
  // the others will be processed

  // This is the target position traditionally

  if (THaBeamDet* theBeamDet=
      static_cast<THaBeamDet*>( nextDet() )) {
    theBeamDet->Process();
    fPosition = theBeamDet->GetPosition();
    fDirection = theBeamDet->GetDirection();
  }
  else {
    Error( Here("Reconstruct"), 
	   "Beamline Detectors Missing in Detector List" );
  }


  // Process any other detectors that may have been added (by default none)
  while (THaBeamDet * theBeamDet=
	 static_cast<THaBeamDet*>( nextDet() )) {
    theBeamDet->Process();
  }

  Update();

  return 0;

}
//______________________________________________________________________________
ClassImp(FadcRasteredBeam)
