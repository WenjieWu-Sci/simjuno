#include "DsPhysConsIon.h"


#include "G4ProcessManager.hh"


///////////////////////////////////////////////////

#include "G4HadronElasticProcess.hh"
#include "G4LElastic.hh"   

#include "G4DeuteronInelasticProcess.hh"
#include "G4LEDeuteronInelastic.hh"

#include "G4TritonInelasticProcess.hh"
#include "G4LETritonInelastic.hh"

#include "G4AlphaInelasticProcess.hh"
#include "G4LEAlphaInelastic.hh"

#include "G4BinaryLightIonReaction.hh"
#include "G4TripathiCrossSection.hh"
#include "G4IonsShenCrossSection.hh"


DsPhysConsIon::DsPhysConsIon(const G4String& name) : G4VPhysicsConstructor(name)
{
    m_minEnergyBinaryCascadeLN=80*MeV;
    m_maxEnergyBinaryCascadeLN=40*GeV;
    m_minEnergyBinaryCascadeGenHe3=0*MeV;
    m_maxEnergyBinaryCascadeGenHe3=30*GeV;
    m_maxEnergyInelastic=100*MeV;
}

DsPhysConsIon::~DsPhysConsIon()
{
}

// Interface methods
void DsPhysConsIon::ConstructParticle()
{
}

void DsPhysConsIon::ConstructProcess()
{
    G4ProcessManager* pmanager = 0;
    // Elastic Process
    G4HadronElasticProcess* theElasticProcess = new G4HadronElasticProcess();
    G4LElastic* theElasticModel = new G4LElastic();
    theElasticProcess->RegisterMe(theElasticModel);
  
    // Generic Ion
    pmanager = G4GenericIon::GenericIon()->GetProcessManager();
    // add process
    pmanager->AddDiscreteProcess(theElasticProcess);

    // preparing inelastic reactions for light nuclei 
    G4BinaryLightIonReaction* theIonCascade;
    G4BinaryLightIonReaction* theGenIonCascade;

    // binary cascade for light nuclei
    // NOTE: Shen XS only up to 10 GeV/n;
    theIonCascade= new G4BinaryLightIonReaction;
    //theIonCascade->SetMinEnergy(80*MeV);
    theIonCascade->SetMinEnergy(m_minEnergyBinaryCascadeLN);
    //theIonCascade->SetMaxEnergy(40*GeV);
    theIonCascade->SetMaxEnergy(m_maxEnergyBinaryCascadeLN);

    // Generic Ion and He3
    // NOTE: Shen XS only up to 10 GeV/n;
    theGenIonCascade = new G4BinaryLightIonReaction;
    //theGenIonCascade->SetMinEnergy(0*MeV);
    theGenIonCascade->SetMinEnergy(m_minEnergyBinaryCascadeGenHe3);
    //theGenIonCascade->SetMaxEnergy(30*GeV);
    theGenIonCascade->SetMaxEnergy(m_maxEnergyBinaryCascadeGenHe3);

    // Cross sections
    G4TripathiCrossSection* theTripathiCrossSection;
    G4IonsShenCrossSection* theShenCrossSection;
    theTripathiCrossSection = new G4TripathiCrossSection;
    theShenCrossSection = new G4IonsShenCrossSection;


    theParticleIterator->reset();
    while( (*theParticleIterator)() ) {
        G4ParticleDefinition* particle = theParticleIterator->value();
        G4ProcessManager* pmanager = particle->GetProcessManager();
        G4String particleName = particle->GetParticleName();

        if(particleName == "deuteron") {
            pmanager->AddDiscreteProcess(theElasticProcess);

            G4DeuteronInelasticProcess* theDeuteronInelasticProcess;
            theDeuteronInelasticProcess = new G4DeuteronInelasticProcess;   
      
            G4LEDeuteronInelastic* theLEDeuteronInelasticModel;
            theLEDeuteronInelasticModel = new G4LEDeuteronInelastic();
            //theLEDeuteronInelasticModel->SetMaxEnergy(100*MeV);
            theLEDeuteronInelasticModel->SetMaxEnergy(m_maxEnergyInelastic);

            theDeuteronInelasticProcess->AddDataSet(theTripathiCrossSection);
            theDeuteronInelasticProcess->AddDataSet(theShenCrossSection);
            theDeuteronInelasticProcess->RegisterMe(theLEDeuteronInelasticModel);
            theDeuteronInelasticProcess->RegisterMe(theIonCascade);
            pmanager->AddDiscreteProcess(theDeuteronInelasticProcess);
        }
        else if (particleName == "triton") {
            pmanager->AddDiscreteProcess(theElasticProcess);

            G4TritonInelasticProcess* theTritonInelasticProcess;
            theTritonInelasticProcess = new G4TritonInelasticProcess; 
      
            G4LETritonInelastic* theLETritonInelasticModel;
            theLETritonInelasticModel = new G4LETritonInelastic();
            //theLETritonInelasticModel->SetMaxEnergy(100*MeV);
            theLETritonInelasticModel->SetMaxEnergy(m_maxEnergyInelastic);

            theTritonInelasticProcess->AddDataSet(theTripathiCrossSection);
            theTritonInelasticProcess->AddDataSet(theShenCrossSection);
            theTritonInelasticProcess->RegisterMe(theLETritonInelasticModel);
            theTritonInelasticProcess->RegisterMe(theIonCascade);
            pmanager->AddDiscreteProcess(theTritonInelasticProcess);
        }
        else if (particleName == "alpha") {
            pmanager->AddDiscreteProcess(theElasticProcess);

            G4AlphaInelasticProcess* theAlphaInelasticProcess;
            theAlphaInelasticProcess = new G4AlphaInelasticProcess;

            G4LEAlphaInelastic* theLEAlphaInelasticModel;
            theLEAlphaInelasticModel = new G4LEAlphaInelastic();
            //theLEAlphaInelasticModel->SetMaxEnergy(100*MeV);
            theLEAlphaInelasticModel->SetMaxEnergy(m_maxEnergyInelastic);

            theAlphaInelasticProcess->AddDataSet(theTripathiCrossSection);
            theAlphaInelasticProcess->AddDataSet(theShenCrossSection);
            theAlphaInelasticProcess->RegisterMe(theLEAlphaInelasticModel);
            theAlphaInelasticProcess->RegisterMe(theIonCascade);
            pmanager->AddDiscreteProcess(theAlphaInelasticProcess);
        }
        else if (particleName == "He3") {
            pmanager->AddDiscreteProcess(theElasticProcess);

            G4HadronInelasticProcess* theHe3InelasticProcess;
            theHe3InelasticProcess = new G4HadronInelasticProcess("He3Inelastic", G4He3::He3());
      
            theHe3InelasticProcess->AddDataSet(theTripathiCrossSection);
            theHe3InelasticProcess->AddDataSet(theShenCrossSection);
            theHe3InelasticProcess->RegisterMe(theGenIonCascade);
            pmanager->AddDiscreteProcess(theHe3InelasticProcess);
        }

        else if (particleName == "GenericIon") {
            pmanager->AddDiscreteProcess(theElasticProcess);

            G4HadronInelasticProcess* theGenericIonInelasticProcess;
            theGenericIonInelasticProcess = new G4HadronInelasticProcess
                ("IonInelastic", G4GenericIon::GenericIon());

            theGenericIonInelasticProcess->AddDataSet(theTripathiCrossSection);
            theGenericIonInelasticProcess->AddDataSet(theShenCrossSection);
            theGenericIonInelasticProcess->RegisterMe(theGenIonCascade);
            pmanager->AddDiscreteProcess(theGenericIonInelasticProcess);
        }
    }
}

