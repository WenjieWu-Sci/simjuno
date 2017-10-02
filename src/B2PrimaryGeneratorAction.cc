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
// $Id: B2PrimaryGeneratorAction.cc 68058 2013-03-13 14:47:43Z gcosmo $
//
/// \file B2PrimaryGeneratorAction.cc
/// \brief Implementation of the B2PrimaryGeneratorAction class

#include "B2PrimaryGeneratorAction.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4GenericMessenger.hh"
#include "TMath.h"

#include "Randomize.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B2PrimaryGeneratorAction::B2PrimaryGeneratorAction()
 : G4VUserPrimaryGeneratorAction(),
   fMessenger(0),
   fParticleGun(0),
   fRandom(false)
{
  G4int nofParticles = 1;
  fParticleGun = new G4ParticleGun(nofParticles);

  // default particle kinematic

  G4ParticleDefinition* particleDefinition 
    = G4ParticleTable::GetParticleTable()->FindParticle("e-");

  fParticleGun->SetParticleDefinition(particleDefinition);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  fParticleGun->SetParticleEnergy(1.0*MeV);
  fParticleGun->SetParticlePosition(G4ThreeVector(0.,0.,0.));

  // Generic messenger
  // Define /JUNO/primary commands using generic messenger class
  fMessenger
    = new G4GenericMessenger(this, "/JUNO/primary/", "Primary generator control");

  // Define /JUNO/primary/setRandom command
  fMessenger
    ->DeclareProperty("setRandom",
                      fRandom,
                      "Activate/Inactivate random option");

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B2PrimaryGeneratorAction::~B2PrimaryGeneratorAction()
{
  delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B2PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    if ( fRandom ) {
        // randomized direction
        G4double dtheta = 180.*deg;
        G4double dphi = 360*deg;
        G4double costheta = G4UniformRand()*2-1.;
        G4double theta = TMath::ACos(costheta);
        G4double phi = G4UniformRand()*dphi;
        G4ThreeVector dir_k = G4ThreeVector(sin(theta)*sin(phi), sin(theta)*cos(phi), cos(theta));
        fParticleGun->SetParticleMomentumDirection(dir_k);
        // get a vector perpendicular to dir
        G4ThreeVector tmp_pol = G4ThreeVector(sin(theta+90.*deg)*sin(phi), sin(theta+90.*deg)*cos(phi), cos(theta+90.*deg));
        // rotate randomly between 0 to 180 deg
        G4double pol_random = G4UniformRand()*dtheta;
        G4ThreeVector pol = tmp_pol.rotate(dir_k, pol_random);
        fParticleGun->SetParticlePolarization(pol);
    }
    fParticleGun->GeneratePrimaryVertex(anEvent);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
