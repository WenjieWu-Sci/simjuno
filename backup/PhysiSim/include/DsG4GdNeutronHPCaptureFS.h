//------------------------------------------------------------------------
//                   Final state of neutron captured by Gadolinium            
//                            
// Modified class from original G4NeutronHPCaptureFS class to deexcite and
// add correctly the secondary to the hadronic final state
//-------------------------------------------------------------------------
// Author: Liang Zhan, 2006/01/27
// Modifed: bv@bnl.gov 2008/4/16 for DetSim
//-------------------------------------------------------------------------

#ifndef DsG4GdNeutronHPCaptureFS_h
#define DsG4GdNeutronHPCaptureFS_h 1

#include "globals.hh"
#include "G4HadProjectile.hh"
#include "G4HadFinalState.hh"
#include "G4NeutronHPFinalState.hh"
#include "G4ReactionProductVector.hh"
#include "G4NeutronHPNames.hh"
#include "G4NeutronHPPhotonDist.hh"
#include "G4Nucleus.hh"
#include "G4Fragment.hh"

// the emission gammas of neutron captured by Gd.
#include "DsG4GdCaptureGammas.h"

///////////////////////////////////////////////////////////////////////////////

class DsG4GdNeutronHPCaptureFS : public G4NeutronHPFinalState
{
public:
  
    DsG4GdNeutronHPCaptureFS();
  
    ~DsG4GdNeutronHPCaptureFS();
  
    void   UpdateNucleus( const G4Fragment* , G4double );
    void Init (G4double A, G4double Z, G4String & dirName, G4String & aFSType);
  
    G4HadFinalState * ApplyYourself(const G4HadProjectile & theTrack);
    G4NeutronHPFinalState * New() {
        DsG4GdNeutronHPCaptureFS * theNew = new DsG4GdNeutronHPCaptureFS;
        return theNew;
    }
  
private:

    G4Fragment * nucleus;

    G4DynamicParticle * theTwo ;
    G4ReactionProduct theTarget; 
    G4Nucleus aNucleus;
    G4ReactionProduct theNeutron;

    G4double targetMass;
  
    G4NeutronHPPhotonDist theFinalStatePhotons;
    DsG4GdCaptureGammas       theFinalgammas;
    G4NeutronHPNames theNames;
  
    G4double theCurrentA;
    G4double theCurrentZ;
};
#endif
