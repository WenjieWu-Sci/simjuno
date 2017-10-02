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
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//#include <boost/python.hpp>
#include "LSExpPhysicsList.hh"

//#include "DsPhysConsElectroNu.h"
//#include "DsPhysConsEM.h"
//#include "DsPhysConsGeneral.h"
//#include "DsPhysConsHadron.h"
//#include "DsPhysConsIon.h"
#include "DsPhysConsOptical.h"

#include "G4RegionStore.hh"
#include "G4Region.hh"
#include "G4ProductionCuts.hh"
#include "G4ProcessManager.hh"
#include "G4ParticleTable.hh"

#include "G4ParticleTypes.hh"
#include "G4BosonConstructor.hh"
#include "G4LeptonConstructor.hh"
#include "G4MesonConstructor.hh"
#include "G4BaryonConstructor.hh"
#include "G4IonConstructor.hh"
#include "G4ShortLivedConstructor.hh"
#include "G4Decay.hh"
#include "G4RadioactiveDecay.hh"
//#include "DsG4RadioactiveDecay.hh"
#include "G4ProcessManager.hh"
#include "G4ProductionCutsTable.hh"
#include "G4ParticlePropertyTable.hh"

#include "G4Gamma.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"

#include "G4UnitsTable.hh"
#include "G4LossTableManager.hh"
#include "G4SystemOfUnits.hh"

#include "G4HadronElasticPhysics.hh"
//#include "G4QStoppingPhysics.hh"
#include "G4IonBinaryCascadePhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4NeutronTrackingCut.hh"
#include "G4DecayPhysics.hh"

//#include "DetSimAlg/DetSimAlg.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LSExpPhysicsList::LSExpPhysicsList() : G4VModularPhysicsList()
{
    cutForGamma     = 1.0*mm;
    cutForElectron  = 0.1*mm;
    cutForPositron  = 0.1*mm;


    //SetVerboseLevel(1);
    SetVerboseLevel(0);

    // default physics
//    electroNuList = new DsPhysConsElectroNu();
//    emPhysicsList = new DsPhysConsEM();
//    generalList = new DsPhysConsGeneral();
//    hadronList = new DsPhysConsHadron();
//    ionList = new DsPhysConsIon();
    opticalList = new DsPhysConsOptical();
    //opticalList = 0;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LSExpPhysicsList::~LSExpPhysicsList()
{
//    delete electroNuList;
//    delete emPhysicsList;
//    delete generalList;
//    delete hadronList;
//    delete ionList;
    delete opticalList;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LSExpPhysicsList::ConstructParticle()
{
    {   // All bosons
        G4BosonConstructor con;
        con.ConstructParticle();
    }
    {   // All leptons
        G4LeptonConstructor con;
        con.ConstructParticle();
    }
    { /* Adopted a subset of mesons to avoid segv at the very end of
       * the run (seems to be related with B mesons and hLowEIoni???).
       * Carbon-copied the meson list from the example in
       * advanced/underground/physics. Jianglai 05/08/2006
       */
        G4PionPlus::PionPlusDefinition();
        G4PionMinus::PionMinusDefinition();
        G4PionZero::PionZeroDefinition();
        G4KaonPlus::KaonPlusDefinition();
        G4KaonMinus::KaonMinusDefinition();
        G4Eta::EtaDefinition();
        G4EtaPrime::EtaPrimeDefinition();
        G4KaonZero::KaonZeroDefinition();
        G4AntiKaonZero::AntiKaonZeroDefinition();
        G4KaonZeroLong::KaonZeroLongDefinition();
        G4KaonZeroShort::KaonZeroShortDefinition();
    }
    {   // All baryons
        G4BaryonConstructor con;
        con.ConstructParticle();
    }
    {   // All ions
        G4IonConstructor con;
        con.ConstructParticle();
    }

    {   // all short lived (resonaces and quarks)
        G4ShortLivedConstructor con;
        con.ConstructParticle();
    }

    /// Special hook: change the PDG encoded value for optical photons to be unique and useful.
    G4ParticlePropertyTable* propTable = G4ParticlePropertyTable::GetParticlePropertyTable();
    assert(propTable);
    G4ParticlePropertyData* photonData = propTable->GetParticleProperty(G4OpticalPhoton::Definition());
    assert(photonData);
    photonData->SetPDGEncoding(20022);
    photonData->SetAntiPDGEncoding(20022);
    if(propTable->SetParticleProperty(*photonData))
        G4cout << "Set PDG code for opticalphoton to " << G4OpticalPhoton::Definition()->GetPDGEncoding() << G4endl;
    else
        G4cout << "Failed to reset PDG code on opticalphoton.. it's still set to "
            << G4OpticalPhoton::Definition()->GetPDGEncoding() << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LSExpPhysicsList::ConstructProcess()
{
    AddTransportation();
    ConstructEM();
    /*
    SniperPtr<DetSimAlg> detsimalg(getScope(), "DetSimAlg");
    if (detsimalg.invalid()) {
        std::cout << "Can't Load DetSimAlg" << std::endl;
        assert(0);
    }
    ToolBase* t = 0;
    std::string toolname;
    */

    //electroNuList->ConstructProcess();
//    generalList->ConstructProcess();
//    emPhysicsList->ConstructProcess();
//    hadronList->ConstructProcess();
//    ionList->ConstructProcess();
    // get the optical list
    /**********
    toolname = "DsPhysConsOptical";
    t = detsimalg->findTool(toolname);
    if (not t) {
        t = detsimalg->createTool(toolname);
    }
    assert(t);
    opticalList = dynamic_cast<G4VPhysicsConstructor*>(t);
    assert(opticalList);
    ***********/
    opticalList->ConstructProcess();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"
#include "G4PhotoElectricEffect.hh"

#include "G4eMultipleScattering.hh"
#include "G4MuMultipleScattering.hh"
#include "G4hMultipleScattering.hh"

#include "G4eIonisation.hh"
#include "G4eBremsstrahlung.hh"
#include "G4eplusAnnihilation.hh"

#include "G4MuIonisation.hh"
#include "G4MuBremsstrahlung.hh"
#include "G4MuPairProduction.hh"

#include "G4hIonisation.hh"

void LSExpPhysicsList::ConstructEM() {
    auto particleIterator=GetParticleIterator();
    particleIterator->reset();
    while( (*particleIterator)() ){
        G4ParticleDefinition* particle = particleIterator->value();
        G4ProcessManager* pmanager = particle->GetProcessManager();
        G4String particleName = particle->GetParticleName();

        if (particleName == "gamma") {
            // gamma
            // Construct processes for gamma
            pmanager->AddDiscreteProcess(new G4GammaConversion());
            pmanager->AddDiscreteProcess(new G4ComptonScattering());
            pmanager->AddDiscreteProcess(new G4PhotoElectricEffect());
        } else if (particleName == "e-") {
            //electron
            // Construct processes for electron
            pmanager->AddProcess(new G4eMultipleScattering(),-1, 1, 1);
            pmanager->AddProcess(new G4eIonisation(),       -1, 2, 2);
            pmanager->AddProcess(new G4eBremsstrahlung(),   -1, 3, 3);

        } else if (particleName == "e+") {
            //positron
            // Construct processes for positron
            pmanager->AddProcess(new G4eMultipleScattering(),-1, 1, 1);
            pmanager->AddProcess(new G4eIonisation(),       -1, 2, 2);
            pmanager->AddProcess(new G4eBremsstrahlung(),   -1, 3, 3);
            pmanager->AddProcess(new G4eplusAnnihilation(),  0,-1, 4);

        } else if( particleName == "mu+" ||
                particleName == "mu-"    ) {
            //muon
            // Construct processes for muon
            pmanager->AddProcess(new G4MuMultipleScattering(),-1, 1, 1);
            pmanager->AddProcess(new G4MuIonisation(),      -1, 2, 2);
            pmanager->AddProcess(new G4MuBremsstrahlung(),  -1, 3, 3);
            pmanager->AddProcess(new G4MuPairProduction(),  -1, 4, 4);

        } else {
            if ((particle->GetPDGCharge() != 0.0) &&
                    (particle->GetParticleName() != "chargedgeantino") &&
                    !particle->IsShortLived()) {
                // all others charged particles except geantino
                pmanager->AddProcess(new G4hMultipleScattering(),-1,1,1);
                pmanager->AddProcess(new G4hIonisation(),       -1,2,2);
            }
        }
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LSExpPhysicsList::SetCuts()
{
    this->SetCutsWithDefault();

    SetCutValue(cutForGamma, "gamma");
    SetCutValue(cutForElectron, "e-");
    SetCutValue(cutForPositron, "e+");

    G4double lowlimit=250*eV;
    G4ProductionCutsTable::GetProductionCutsTable()->SetEnergyRange(lowlimit,100.*TeV);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LSExpPhysicsList::SetCutForGamma(G4double cut)
{
    cutForGamma = cut;
    SetParticleCuts(cutForGamma, G4Gamma::Gamma());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LSExpPhysicsList::SetCutForElectron(G4double cut)
{
    cutForElectron = cut;
    SetParticleCuts(cutForElectron, G4Electron::Electron());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LSExpPhysicsList::SetCutForPositron(G4double cut)
{
    cutForPositron = cut;
    SetParticleCuts(cutForPositron, G4Positron::Positron());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
