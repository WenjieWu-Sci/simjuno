/**
 * \class DsG4Cerenkov
 *
 * \brief A slightly modified version of G4Cerenkov
 *
 * It is modified to take a given weight to use to reduce the number
 * of opticalphotons that are produced.  They can then later be
 * up-weighted.
 *
 * The modification adds the weight, its accessors and adds
 * implementation to AlongStepDoIt().  We must copy-and-modify instead
 * of inherit because certain needed data members are private and so
 * we can not just override AlongStepDoIt() in our own subclass.
 *
 * Despite the tag below, this was taken from G4.8.3.
 *
 * bv@bnl.gov Mon Feb  4 15:52:16 2008
 * Initial mod to support weighted opticalphotons.
 * The mods to dywCerenkov by Jianglai 09-06-2006 were used for guidance.
 *
 */

//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
// $Id: G4Cerenkov.hh,v 1.10 2008/10/22 01:17:36 gum Exp $
// GEANT4 tag $Name: geant4-09-02 $
//
// 
////////////////////////////////////////////////////////////////////////
// Cerenkov Radiation Class Definition 
////////////////////////////////////////////////////////////////////////
//
// File:        G4Cerenkov.hh  
// Description:	Discrete Process - Generation of Cerenkov Photons
// Version:     2.0
// Created:     1996-02-21
// Author:      Juliet Armstrong
// Updated:     2007-09-30 change inheritance to G4VDiscreteProcess
//              2005-07-28 add G4ProcessType to constructor
//              1999-10-29 add method and class descriptors
//              1997-04-09 by Peter Gumplinger
//              > G4MaterialPropertiesTable; new physics/tracking scheme
// mail:        gum@triumf.ca
//
////////////////////////////////////////////////////////////////////////

#ifndef DsG4Cerenkov_h
#define DsG4Cerenkov_h 1

/////////////
// Includes
/////////////

#include "globals.hh"
#include "templates.hh"
#include "Randomize.hh"
#include "G4ThreeVector.hh"
#include "G4ParticleMomentum.hh"
#include "G4Step.hh"
#include "G4VProcess.hh"
#include "G4OpticalPhoton.hh"
#include "G4DynamicParticle.hh"
#include "G4Material.hh" 
#include "G4PhysicsTable.hh"
#include "G4MaterialPropertiesTable.hh"
#include "G4PhysicsOrderedFreeVector.hh"

// Class Description:
// Discrete Process -- Generation of Cerenkov Photons.
// Class inherits publicly from G4VDiscreteProcess.
// Class Description - End:

/////////////////////
// Class Definition
/////////////////////

class DsG4Cerenkov : public G4VProcess
{

private:

        //////////////
        // Operators
        //////////////

	// G4Cerenkov& operator=(const G4Cerenkov &right);

public: // Without description

	////////////////////////////////
	// Constructors and Destructor
	////////////////////////////////

	DsG4Cerenkov(const G4String& processName = "Cerenkov", 
                            G4ProcessType type = fElectromagnetic);

	// G4Cerenkov(const G4Cerenkov &right);

	~DsG4Cerenkov();	

        ////////////
        // Methods
        ////////////

public: // With description

        G4bool IsApplicable(const G4ParticleDefinition& aParticleType);
        // Returns true -> 'is applicable', for all charged particles.

        G4double GetMeanFreePath(const G4Track& aTrack,
                                 G4double ,
                                 G4ForceCondition* );
        // Returns the discrete step limit and sets the 'StronglyForced'
        // condition for the DoIt to be invoked at every step.

        G4double PostStepGetPhysicalInteractionLength(const G4Track& aTrack,
                                                      G4double ,
                                                      G4ForceCondition* );
        // Returns the discrete step limit and sets the 'StronglyForced'
        // condition for the DoIt to be invoked at every step.

	G4VParticleChange* PostStepDoIt(const G4Track& aTrack, 
					const G4Step&  aStep);
        // This is the method implementing the Cerenkov process.

        //  no operation in  AtRestDoIt and  AlongStepDoIt
        virtual G4double AlongStepGetPhysicalInteractionLength(
                               const G4Track&,
                               G4double  ,
                               G4double  ,
                               G4double& ,
                               G4GPILSelection*
                              ) { return -1.0; };

        virtual G4double AtRestGetPhysicalInteractionLength(
                               const G4Track& ,
                               G4ForceCondition*
                              ) { return -1.0; };

        //  no operation in  AtRestDoIt and  AlongStepDoIt
        virtual G4VParticleChange* AtRestDoIt(
                               const G4Track& ,
                               const G4Step&
                              ) {return 0;};

        virtual G4VParticleChange* AlongStepDoIt(
                               const G4Track& ,
                               const G4Step&
                              ) {return 0;};

	void SetTrackSecondariesFirst(const G4bool state);
        // If set, the primary particle tracking is interrupted and any 
        // produced Cerenkov photons are tracked next. When all have 
        // been tracked, the tracking of the primary resumes. 
	
        void SetMaxBetaChangePerStep(const G4double d);
        // Set the maximum allowed change in beta = v/c in % (perCent)
        // per step.

	void SetMaxNumPhotonsPerStep(const G4int NumPhotons);
        // Set the maximum number of Cerenkov photons allowed to be 
        // generated during a tracking step. This is an average ONLY; 
        // the actual number will vary around this average. If invoked, 
        // the maximum photon stack will roughly be of the size set.
        // If not called, the step is not limited by the number of 
        // photons generated.

        G4PhysicsTable* GetPhysicsTable() const;
        // Returns the address of the physics table.

        void DumpPhysicsTable() const;
        // Prints the physics table.

        G4double GetPhotonWeight() const { return fPhotonWeight; }
        void SetPhotonWeight(G4double weight) { fPhotonWeight = weight; }
        
        G4bool GetApplyPreQE() const { return fApplyPreQE; }
        void SetApplyPreQE(G4bool a) { fApplyPreQE = a; }

        G4double GetPreQE() const { return fPreQE; }
        void SetPreQE(G4double a) { fPreQE = a; }
        
        G4bool GetApplyWaterQe() const { return fApplyWaterQe; }
        void SetApplyWaterQe(G4bool ApplyWaterQe) { fApplyWaterQe = ApplyWaterQe; }

        G4double GetQeScale() const { return m_qeScale; }
        void SetQeScale(G4double qeScale) { m_qeScale = qeScale; }

        G4double GetPoolPmtQe(G4double energy) const;
private:

        void BuildThePhysicsTable();

	/////////////////////
	// Helper Functions
	/////////////////////

        G4double GetAverageNumberOfPhotons(const G4double charge,
                                           const G4double beta,
                                           const G4Material *aMaterial,
                                           const G4MaterialPropertyVector* Rindex) const;

        ///////////////////////
        // Class Data Members
        ///////////////////////

protected:

        G4PhysicsTable* thePhysicsTable;
        //  A Physics Table can be either a cross-sections table or
        //  an energy table (or can be used for other specific
        //  purposes).

private:

	G4bool fTrackSecondariesFirst;
	G4double fMaxBetaChange;
	G4int  fMaxPhotons;
    G4double fPhotonWeight;
    G4bool   fApplyPreQE;
    G4double fPreQE;

	// Apply QE for water cerenkov process when OP is created?
	// If it is true the CerenPhotonScaleWeight will be disabled in water,
	// but it still works for AD and others
	G4bool fApplyWaterQe;

	/// QEScale: Upward adjustment of DetSim efficiency to allow
	/// PMT-to-PMT efficiency variation in the electronics simulation.
	/// The value should be the inverse of the mean PMT efficiency
	/// applied in ElecSim.
	G4double m_qeScale;
};

////////////////////
// Inline methods
////////////////////

inline 
G4bool DsG4Cerenkov::IsApplicable(const G4ParticleDefinition& aParticleType)
{
   if (aParticleType.GetParticleName() != "chargedgeantino" ) {
      return (aParticleType.GetPDGCharge() != 0);
   } else {
      return false;
   }
}

inline 
void DsG4Cerenkov::SetTrackSecondariesFirst(const G4bool state) 
{ 
	fTrackSecondariesFirst = state;
}

inline
void DsG4Cerenkov::SetMaxBetaChangePerStep(const G4double value)
{
        fMaxBetaChange = value*perCent;
}

inline
void DsG4Cerenkov::SetMaxNumPhotonsPerStep(const G4int NumPhotons) 
{ 
	fMaxPhotons = NumPhotons;
}

inline
void DsG4Cerenkov::DumpPhysicsTable() const
{
        G4int PhysicsTableSize = thePhysicsTable->entries();
        G4PhysicsOrderedFreeVector *v;

        for (G4int i = 0 ; i < PhysicsTableSize ; i++ )
        {
        	v = (G4PhysicsOrderedFreeVector*)(*thePhysicsTable)[i];
        	v->DumpValues();
        }
}

inline
G4PhysicsTable* DsG4Cerenkov::GetPhysicsTable() const
{
  return thePhysicsTable;
}

#endif /* DsG4Cerenkov_h */
