#ifndef ROOT_FadcRasteredBeam_H 
#define ROOT_FadcRasteredBeam_H

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// FadcRasteredBeam                                                           //
//   Apparatus describing a rastered beam                                     //
//   Adapted from Bodo Reitz (April 2003)                                     //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include "THaBeam.h"
#include "VarDef.h"

#include "TMath.h"
#include "TDatime.h"
#include "TList.h"

#include "FadcRaster.h"
#include "FadcBPM.h"

class FadcRasteredBeam : public THaBeam {

public:
  FadcRasteredBeam( const char* name, const char* description ) ;
  virtual ~FadcRasteredBeam() {}
  virtual Int_t Reconstruct() ;

protected:
  ClassDef(FadcRasteredBeam,0)    // A beam with rastered beam, analyzed event by event using raster currents

};

#endif

