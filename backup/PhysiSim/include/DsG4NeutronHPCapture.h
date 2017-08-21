//-----------------------------------------------------------------------------
//                    neutron capture model          
//                            
// Modified class from original G4NeutronHPCapture to include the final state
// (the gammas spectrum) of neutron captured by Gadolinium.
//---------------------------------------------------------------------------
// Author: Liang Zhan, 2006/01/27
// Modified for DetSim, bv@bnl.gov 2008/4/16
//---------------------------------------------------------------------------

#ifndef DsG4NeutronHPCapture_h
#define DsG4NeutronHPCapture_h 1

#include "globals.hh"
#include "G4HadronicInteraction.hh"

class G4NeutronHPChannel;

///////////////////////////////////////////////////////////////////////////////

class DsG4NeutronHPCapture : public G4HadronicInteraction
{
public: 
  
    DsG4NeutronHPCapture();

    virtual ~DsG4NeutronHPCapture();

    G4HadFinalState * ApplyYourself(const G4HadProjectile& aTrack, G4Nucleus& aTargetNucleus);

    G4bool DebugMe ; //djaffe

private:
  
    G4double * xSec;
    G4NeutronHPChannel * theCapture;
    G4String dirName;
    G4int numEle;
    G4int it;

    G4HadFinalState theResult;
    G4HadFinalState * result;

};

#endif
