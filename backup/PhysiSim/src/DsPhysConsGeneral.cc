#include "DsPhysConsGeneral.h"

DsPhysConsGeneral::DsPhysConsGeneral(const G4String& name): G4VPhysicsConstructor(name)
{
    m_lowProdCut=250*eV;
    m_highProdCut=100*GeV;

    m_gammaCut=1.0*mm;
    m_electronCut=100.0*micrometer;
    m_positronCut=100.0*micrometer;
}

DsPhysConsGeneral::~DsPhysConsGeneral()
{
}

#include "G4Decay.hh"
#include "G4RadioactiveDecay.hh"
#include "DsG4RadioactiveDecay.hh"
#include "G4ProcessManager.hh"
#include "G4ProductionCutsTable.hh"
#include "G4ParticlePropertyTable.hh"

void DsPhysConsGeneral::ConstructParticle()
{
} 

void DsPhysConsGeneral::ConstructProcess()
{
    // can't call this from a GiGaPhysConstructorBase, but
    // G4VModularPhysicsList will do it for us.
    // AddTransportation();

    G4Decay* theDecayProcess = new G4Decay();
    theParticleIterator->reset();
    while( (*theParticleIterator)() ) {
        G4ParticleDefinition* particle = theParticleIterator->value();
        G4ProcessManager* pmanager = particle->GetProcessManager();
        if (theDecayProcess->IsApplicable(*particle)) {
            pmanager->AddProcess(theDecayProcess);
            pmanager ->SetProcessOrdering(theDecayProcess, idxPostStep);
            pmanager ->SetProcessOrdering(theDecayProcess, idxAtRest);
        }
    }

    const G4IonTable* theIonTable 
        = G4ParticleTable::GetParticleTable()->GetIonTable();
    //G4RadioactiveDecay* theRadioactiveDecay = new G4RadioactiveDecay();
    DsG4RadioactiveDecay* theRadioactiveDecay = new DsG4RadioactiveDecay();
    for (G4int i=0; i<theIonTable->Entries(); i++) {
        G4String particleName = theIonTable->GetParticle(i)->GetParticleName();
        if (particleName == "GenericIon") {
            G4ProcessManager* pmanager 
                = theIonTable->GetParticle(i)->GetProcessManager();
            pmanager ->AddProcess(theRadioactiveDecay);
            pmanager ->SetProcessOrdering(theRadioactiveDecay, idxPostStep);
            pmanager ->SetProcessOrdering(theRadioactiveDecay, idxAtRest);
        }
    }

}

#if 0
void DsPhysConsGeneral::SetCuts()
{
    // special for low energy physics
    G4ProductionCutsTable::GetProductionCutsTable()->
        SetEnergyRange(m_lowProdCut,m_highProdCut);

    // set cut values for gamma at first and for e- second and next for e+,
    // because some processes for e+/e- need cut values for gamma 
    SetCutValue(m_gammaCut, "gamma");
    SetCutValue(m_electronCut, "e-");
    SetCutValue(m_positronCut, "e+");
}
#endif
