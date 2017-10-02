#include "PrimaryGeneratorAction.hh"

#include <G4ParticleTable.hh>
#include <G4Event.hh>
#include <G4SystemOfUnits.hh>
#include <G4ParticleGun.hh>
#include <Randomize.hh>
#include <G4GeneralParticleSource.hh>

#include <TMath.h>

using namespace std;

PrimaryGeneratorAction::PrimaryGeneratorAction()
{
    fGPS = new G4GeneralParticleSource();

    G4ParticleDefinition* myParticle;
    myParticle= G4ParticleTable::GetParticleTable()->FindParticle("e-");
    fGPS->SetParticleDefinition(myParticle);
    fGPS->GetCurrentSource()->GetEneDist()->SetMonoEnergy(1*MeV);
    fGPS->GetCurrentSource()->GetAngDist()->SetParticleMomentumDirection(G4ThreeVector(1, 0, 0));
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete fGPS;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    G4double x0= 20 * cm;
    G4double y0= 0.;
    G4double z0= 0.;
    G4double dx0= 5 * cm;
    G4double dy0= 5 * cm;
    G4double dz0= 5 * cm;
    x0 += dx0*(G4UniformRand()-0.5);
    y0 += dy0*(G4UniformRand()-0.5);
    z0 += dz0*(G4UniformRand()-0.5);
    fGPS->SetParticlePosition(G4ThreeVector(x0, y0, z0));

    G4double cos_theta= 2*G4UniformRand() - 1;
    G4double phi= 2*TMath::Pi()*G4UniformRand();
    G4double theta= TMath::ACos(cos_theta);
    G4double polx= TMath::Sin(theta)*TMath::Cos(phi);
    G4double poly= TMath::Sin(theta)*TMath::Sin(phi);
    G4double polz= TMath::Cos(theta);
    fGPS->SetParticlePolarization(G4ThreeVector(polx, poly, polz));
    fGPS->GeneratePrimaryVertex(anEvent);
}
