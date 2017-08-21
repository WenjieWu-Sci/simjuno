//------------------------------------------------------------------------
//                   Final state of neutron capture            
//                            
// Modified class from original DsG4GdNeutronHPCaptureFS class 
//-------------------------------------------------------------------------
// Author: Dan Dwyer, 2009/07/27
//-------------------------------------------------------------------------

#ifndef DsG4NNDCNeutronHPCaptureFS_h
#define DsG4NNDCNeutronHPCaptureFS_h 1

#include "globals.hh"
#include "G4HadProjectile.hh"
#include "G4HadFinalState.hh"
#include "G4NeutronHPFinalState.hh"
#include "G4ReactionProductVector.hh"
#include "G4NeutronHPNames.hh"
#include "G4NeutronHPPhotonDist.hh"
#include "G4Nucleus.hh"
#include "G4Fragment.hh"

// the emission gammas of neutron capture from NNDC tables.
#include "DsG4NNDCCaptureGammas.h"

///////////////////////////////////////////////////////////////////////////////

class DsG4NNDCNeutronHPCaptureFS : public G4NeutronHPFinalState
{
public:
  
    DsG4NNDCNeutronHPCaptureFS();
  
    ~DsG4NNDCNeutronHPCaptureFS();
  
    void   UpdateNucleus( const G4Fragment* , G4double );
    void Init (G4double A, G4double Z, G4String & dirName, G4String & aFSType);
  
    G4HadFinalState * ApplyYourself(const G4HadProjectile & theTrack);
    G4NeutronHPFinalState * New() {
        DsG4NNDCNeutronHPCaptureFS * theNew = new DsG4NNDCNeutronHPCaptureFS;
        return theNew;
    }
    G4NeutronHPVector* GetXsec( ){ return &theCrossSection; }
  
private:

    G4Fragment * nucleus;

    G4DynamicParticle * theTwo ;
    G4ReactionProduct theTarget; 
    G4Nucleus aNucleus;
    G4ReactionProduct theNeutron;

    G4double targetMass;
  
    DsG4NNDCCaptureGammas       theFinalgammas;
    G4NeutronHPVector theCrossSection;
};
#endif
