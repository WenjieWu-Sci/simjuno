#include "DsPhysConsEM.h"

#include "G4ProcessManager.hh"

////////////////////////////// Standard EM Process

//#include "G4MultipleScattering.hh"

#include "G4eIonisation.hh"
#include "G4eBremsstrahlung.hh"
#include "G4eplusAnnihilation.hh"

#include "G4MuIonisation.hh"
#include "G4MuBremsstrahlung.hh"
#include "G4MuPairProduction.hh"
#include "G4MuonMinusCaptureAtRest.hh"

/////////////////////////////// Low Energy EM Process

#include "G4LowEnergyRayleigh.hh"
#include "G4LowEnergyPhotoElectric.hh"
#include "G4LowEnergyCompton.hh"  
#include "G4LowEnergyGammaConversion.hh"

#include "G4LowEnergyIonisation.hh"
#include "G4LowEnergyBremsstrahlung.hh"

#include "G4hLowEnergyIonisation.hh"
#include "G4EnergyLossTables.hh"
#include "G4eMultipleScattering.hh"  
#include "G4hMultipleScattering.hh"  
#include "G4MuMultipleScattering.hh"  


DsPhysConsEM::DsPhysConsEM(const G4String& name):  G4VPhysicsConstructor(name)
{
    m_fluorCut=250*eV;
}
DsPhysConsEM::~DsPhysConsEM()
{
}


void DsPhysConsEM::ConstructParticle()
{
}

void DsPhysConsEM::ConstructProcess()
{
    G4LowEnergyPhotoElectric* lowePhot = new G4LowEnergyPhotoElectric();
    G4LowEnergyIonisation* loweIon  = new G4LowEnergyIonisation();
    G4LowEnergyBremsstrahlung* loweBrem = new G4LowEnergyBremsstrahlung();

    // note LowEIon uses proton as basis for its data-base, therefore
    // cannot specify different LowEnergyIonisation models for different
    // particles, but can change model globally for Ion, Alpha and Proton.
   
    //fluorescence apply specific cut for fluorescence from photons, electrons
    //and bremsstrahlung photons:
    lowePhot->SetCutForLowEnSecPhotons(m_fluorCut);
    loweIon->SetCutForLowEnSecPhotons(m_fluorCut);
    loweBrem->SetCutForLowEnSecPhotons(m_fluorCut);
  
    theParticleIterator->reset();
    while((*theParticleIterator)()) {
        G4ParticleDefinition* particle = theParticleIterator->value();
        G4ProcessManager* pmanager = particle->GetProcessManager();
        G4String particleName = particle->GetParticleName();
        if(particleName =="gamma") {  
            // gamma    
            pmanager->AddDiscreteProcess(new G4LowEnergyRayleigh());
            pmanager->AddDiscreteProcess(lowePhot);
            pmanager->AddDiscreteProcess(new G4LowEnergyCompton());
            pmanager->AddDiscreteProcess(new G4LowEnergyGammaConversion());
        }
        else if(particleName=="e-") { 
            // electron
            // process ordering: AddProcess(name, at rest, along step, post step)
            // -1 = not implemented, then ordering	    
            pmanager->AddProcess(new G4eMultipleScattering(),-1, 1, 1);
            pmanager->AddProcess(loweIon,                   -1, 2, 2);
            pmanager->AddProcess(loweBrem,                  -1, -1, 3);
        }
        else if(particleName=="e+") {
            // positron
            pmanager->AddProcess(new G4eMultipleScattering(),-1,1,1);
            pmanager->AddProcess(new G4eIonisation(),       -1,2,2);
            pmanager->AddProcess(new G4eBremsstrahlung(),   -1,-1,3);
            pmanager->AddProcess(new G4eplusAnnihilation(),  0,-1,4);
        }	
        else if(particleName == "mu+" ||particleName == "mu-") {
            // muon
            // LOGINFO(dyb)<<"Construct processes for muon"<<G4endl;
            pmanager->AddProcess(new G4MuMultipleScattering(),-1, 1, 1);
            pmanager->AddProcess(new G4MuIonisation(),      -1, 2, 2);
            pmanager->AddProcess(new G4MuBremsstrahlung(),  -1, 3, 3);
            pmanager->AddProcess(new G4MuPairProduction(),  -1, 4, 4);
		  
            if( particleName == "mu-" ) {
                 // pmanager->AddProcess(new G4MuonMinusCaptureAtRest(), 0,-1,-1);
                 pmanager->AddRestProcess(new G4MuonMinusCaptureAtRest);
            }
        } 
        else if ( !(particle->IsShortLived())&&
                  (particle->GetPDGCharge() != 0.0) &&
                  (particle->GetParticleName() != "chargedgeantino")) {
            // all other charged particles except geantino
            G4hMultipleScattering* aMultipleScattering = new G4hMultipleScattering();
            G4hLowEnergyIonisation* ahadronLowEIon = new G4hLowEnergyIonisation();
            pmanager->AddProcess(aMultipleScattering,-1,1,1);
            pmanager->AddProcess(ahadronLowEIon,-1,2,2);
            //fluorescence switch off for hadrons :
            ahadronLowEIon->SetFluorescence(false);
        }
    }
}


