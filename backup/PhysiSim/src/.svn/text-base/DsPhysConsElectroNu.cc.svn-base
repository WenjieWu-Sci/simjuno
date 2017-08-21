#include "DsPhysConsElectroNu.h"

#include "G4ProcessManager.hh"

//////////////////////////////ElectroNuclear Prcesses


#include "G4PhotoNuclearProcess.hh"
#include "G4GammaNuclearReaction.hh"
#include "G4GammaParticipants.hh"
#include "G4TheoFSGenerator.hh"
#include "G4QGSModel.hh"
#include "G4QGSMFragmentation.hh"
#include "G4ExcitedStringDecay.hh"
#include "G4GeneratorPrecompoundInterface.hh"
#include "G4PhotoNuclearCrossSection.hh"
#include "G4ElectroNuclearReaction.hh"
#include "G4ElectronNuclearProcess.hh"
#include "G4PositronNuclearProcess.hh"
#include "G4MuNuclearInteraction.hh"
#include "DsG4MuNuclearInteraction.hh"

DsPhysConsElectroNu::DsPhysConsElectroNu(const G4String& name): G4VPhysicsConstructor(name)
{
    m_maxGammaReactionEnergy=3.5*GeV;
    m_minFinalStateEnergy=3.0*GeV;
    m_maxFinalStateEnergy=100*TeV;
    m_muNuclScaledFactor=1.0;
    m_enableMuNucl=true;
}

DsPhysConsElectroNu::~DsPhysConsElectroNu()
{
}

// Interface methods
void DsPhysConsElectroNu::ConstructParticle()
{
}
void DsPhysConsElectroNu::ConstructProcess()
{
    // gamma
    G4ProcessManager* pmanager = G4Gamma::Gamma()->GetProcessManager();

    G4PhotoNuclearProcess * thePhotoNuclearProcess = new G4PhotoNuclearProcess;
    G4GammaNuclearReaction * theGammaReaction = new G4GammaNuclearReaction;
    G4TheoFSGenerator * theModel = new G4TheoFSGenerator;
    G4QGSModel<G4GammaParticipants>* theStringModel = new G4QGSModel<G4GammaParticipants>;
    G4ExcitedStringDecay * theStringDecay = new G4ExcitedStringDecay(new G4QGSMFragmentation);
    theStringModel->SetFragmentationModel(theStringDecay);
    G4GeneratorPrecompoundInterface * theCascade = new G4GeneratorPrecompoundInterface;
    theModel->SetTransport(theCascade);
    theModel->SetHighEnergyGenerator(theStringModel);
    theGammaReaction->SetMaxEnergy(m_maxGammaReactionEnergy);

    thePhotoNuclearProcess->RegisterMe(theGammaReaction);
  
    theModel->SetMinEnergy(m_minFinalStateEnergy);
    theModel->SetMaxEnergy(m_maxFinalStateEnergy);
  
    thePhotoNuclearProcess->RegisterMe(theModel);
  
    pmanager->AddDiscreteProcess(thePhotoNuclearProcess);
 
    // e-
    pmanager = G4Electron::Electron()->GetProcessManager();
     
    G4ElectroNuclearReaction* electroNuclear = new G4ElectroNuclearReaction();
    G4ElectronNuclearProcess* theElectroNuclearProcess = new G4ElectronNuclearProcess();

    theElectroNuclearProcess->RegisterMe(electroNuclear);

    pmanager->AddProcess(theElectroNuclearProcess, -1, -1, 5);
  
    // e+
    pmanager = G4Positron::Positron()->GetProcessManager();

    G4PositronNuclearProcess* thePositronNuclearProcess = new G4PositronNuclearProcess();

    thePositronNuclearProcess->RegisterMe(electroNuclear);

    pmanager->AddProcess(thePositronNuclearProcess, -1, -1, 5); 
  
    // Mu-nuclear reaction
    if(m_enableMuNucl) {
      // mu-  
      pmanager = G4MuonMinus::MuonMinus()->GetProcessManager();

      DsG4MuNuclearInteraction* munucProc = new DsG4MuNuclearInteraction("muNuclear", m_muNuclScaledFactor);
  
      pmanager->AddDiscreteProcess(munucProc);

      // mu+
      pmanager = G4MuonPlus::MuonPlus()->GetProcessManager();
          
      pmanager->AddDiscreteProcess(munucProc);
    }
}


 
