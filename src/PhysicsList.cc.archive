#include "PhysicsList.hh"

#include <G4EmStandardPhysics.hh>
#include <G4EmLivermorePhysics.hh>
#include <G4EmExtraPhysics.hh>
#include <G4HadronElasticPhysics.hh>
#include <G4HadronPhysicsFTFP_BERT.hh>
#include <G4DecayPhysics.hh> 
#include <G4ProductionCutsTable.hh>
#include <G4SystemOfUnits.hh>
#include <G4OpticalPhysics.hh>

PhysicsList::PhysicsList() : G4VModularPhysicsList() {
    // Standard EM physics 
    this->RegisterPhysics(new G4EmLivermorePhysics());
    // Add G4EmExtraPhysics
//    RegisterPhysics(new G4EmExtraPhysics());
//    RegisterPhysics(new G4HadronElasticPhysics());
    // Add hadronic physics  
    this->RegisterPhysics(new G4HadronPhysicsFTFP_BERT());

    // Optical Physics
    this->RegisterPhysics(new G4OpticalPhysics());

    // Default Decay Physics
    this->RegisterPhysics(new G4DecayPhysics());
}

void PhysicsList::SetCuts() {
    // The method SetCuts() is mandatory in the interface. Here, one just use 
    // the default SetCuts() provided by the base class.
    G4VUserPhysicsList::SetCuts();

    // Task 3c.1: Temporarily update the production cuts table energy range
    //G4ProductionCutsTable::GetProductionCutsTable()->SetEnergyRange(100*eV, 100.*GeV);

    // In addition, dump the full list of cuts for the materials used in 
    // the setup
    DumpCutValuesTable();
}
