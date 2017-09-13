#ifndef DsG4OpAbsReemit_h
#define DsG4OpAbsReemit_h

/*  
 * This class implements the absorption and reemission physics process.
 *
 * For LS, there are LAB, PPO and bis-MSB. Create DsG4OpAbsReemit for each
 * components and register them into physics list. Then geant4 will decide
 * to use which physics process by sampling absorption length.
 *
 * After absorption, it will decide re-emission or not according to the
 * QE of that material. If QE is always zero, that means this material only
 * absorb photons.
 *
 * The re-emission spectrum is sampled to give an energy of that photon.
 *
 * Author: Tao Lin <lintao@ihep.ac.cn>
 * Refs: G4OpWLS.hh and G4Absorption.hh
 */

#include "globals.hh"
#include "templates.hh"
#include "Randomize.hh"
#include "G4Poisson.hh"
#include "G4ThreeVector.hh"
#include "G4ParticleMomentum.hh"
#include "G4Step.hh"
#include "G4VDiscreteProcess.hh"
#include "G4DynamicParticle.hh"
#include "G4Material.hh"
#include "G4OpticalPhoton.hh"
#include "G4PhysicsTable.hh"
#include "G4MaterialPropertiesTable.hh"
#include "G4PhysicsOrderedFreeVector.hh"

class DsG4OpAbsReemit: public G4VDiscreteProcess
{
public:

    DsG4OpAbsReemit(const G4String& label = "PPO",
                        const G4String& processName = "OpAbsReemit",
                        G4ProcessType type = fOptical
                        );
    ~DsG4OpAbsReemit();

public:

    G4bool IsApplicable(const G4ParticleDefinition& aParticleType);
    // Returns true -> 'is applicable' only for an optical photon.

    G4double GetMeanFreePath(const G4Track& aTrack,
            G4double ,
            G4ForceCondition* );
    // Returns the absorption length for bulk absorption of optical
    // photons in media with a specified attenuation length.

    G4VParticleChange* PostStepDoIt(const G4Track& aTrack,
            const G4Step&  aStep);
    // This is the method implementing bulk absorption of optical
    // photons.
    // And then Re-emit according to the QE.

    G4PhysicsTable* GetIntegralTable() const;
    // Returns the address of the integral table.

    void DumpPhysicsTable() const;
    // Prints the integral table.

private:

    void BuildThePhysicsTable();
    // Is the integral table;

protected:

    G4PhysicsTable* theIntegralTable;

    G4String m_label; // indicate PPO, bisMSB, LAB
    // some labels
    G4String m_label_abslen;
    G4String m_label_reemiprob;
    G4String m_label_component;
    G4String m_label_timeconst;
};

inline
G4bool DsG4OpAbsReemit::IsApplicable(const G4ParticleDefinition& aParticleType)
{
    return ( &aParticleType == G4OpticalPhoton::OpticalPhoton() );
}

inline
G4PhysicsTable* DsG4OpAbsReemit::GetIntegralTable() const
{
    return theIntegralTable;
}

inline
void DsG4OpAbsReemit::DumpPhysicsTable() const
{
    G4int PhysicsTableSize = theIntegralTable->entries();
    G4PhysicsOrderedFreeVector *v;

    for (G4int i = 0 ; i < PhysicsTableSize ; i++ )
    {
        v = (G4PhysicsOrderedFreeVector*)(*theIntegralTable)[i];
        v->DumpValues();
    }
}

#endif
