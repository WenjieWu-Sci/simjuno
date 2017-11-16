//#include <boost/python.hpp>
//#define USE_CUSTOM_CERENKOV
#define USE_CUSTOM_SCINTILLATION

#include "DsPhysConsOptical.h"

#ifdef USE_CUSTOM_CERENKOV
#include "DsG4Cerenkov.h"
#else
#include "G4Cerenkov.hh"
#endif

#ifdef USE_CUSTOM_SCINTILLATION
#include "DsG4Scintillation.h"

// DsG4ScintSimple is based on DsG4Scintillation, but remove features such as 
// re-emission. To enable re-emission, we need to use DsG4OpAbsReemit.
//
// -- Tao Lin, 5th Nov. 2016
//
#include "DsG4ScintSimple.h"
#else
#include "G4Scintillation.hh"
#endif

#include "DsG4OpAbsReemit.h"
#include "G4OpAbsorption.hh"
#include "G4OpRayleigh.hh"
#include "G4OpBoundaryProcess.hh"
//#include "DsG4OpBoundaryProcess.h"
#include "G4ProcessManager.hh"
#include "G4FastSimulationManagerProcess.hh"

#include "G4SystemOfUnits.hh"
#include "DsPhysConsOpticalMessenger.hh"

//#include "SniperKernel/SniperPtr.h"
//#include "SniperKernel/ToolFactory.h"
//#include "SniperKernel/SniperLog.h"

//DECLARE_TOOL(DsPhysConsOptical);

G4ThreadLocal G4int DsPhysConsOptical::fVerboseLevel = 1;
G4ThreadLocal G4bool DsPhysConsOptical::fTruePhysics = true;

DsPhysConsOptical::DsPhysConsOptical(const G4String& name):
    G4VPhysicsConstructor(name)
{
    fMessenger = new DsPhysConsOpticalMessenger(this);

}

DsPhysConsOptical::~DsPhysConsOptical()
{
    delete fMessenger;
}

void DsPhysConsOptical::ConstructParticle()
{
}

void DsPhysConsOptical::ConstructProcess()
{
    InitialiseOptions();
#ifdef USE_CUSTOM_CERENKOV

    DsG4Cerenkov* cerenkov = 0;
    LogInfo << "DoCerenkov: " << m_useCerenkov << std::endl;
    if (m_useCerenkov) {
        cerenkov = new DsG4Cerenkov();
        cerenkov->SetMaxNumPhotonsPerStep(m_cerenMaxPhotonPerStep);
        cerenkov->SetApplyPreQE(m_cerenPhotonScaleWeight>1.);
        cerenkov->SetPreQE(1./m_cerenPhotonScaleWeight);

        // wangzhe   Give user a handle to control it.
        cerenkov->SetApplyWaterQe(m_applyWaterQe);
        // wz
        cerenkov->SetTrackSecondariesFirst(true);
    }
#else

    G4Cerenkov* cerenkov = 0;
    if (m_useCerenkov) {
        cerenkov = new G4Cerenkov();
        cerenkov->SetMaxNumPhotonsPerStep(m_cerenMaxPhotonPerStep);
        cerenkov->SetTrackSecondariesFirst(true);
    }
#endif

#ifdef USE_CUSTOM_SCINTILLATION
    G4VProcess* scint_ = 0;

    // summary info
    G4cout << "DoQuenching: " << m_enableQuenching << G4endl;
    G4cout << "Birks Constant 1: "
           << m_birksConstant1/(g/cm2/MeV)
           << "g/cm2/MeV" << G4endl;
    G4cout << "Birks Constant 2: "
           << m_birksConstant2/((g/cm2/MeV)*(g/cm2/MeV))
           << "(g/cm2/MeV)*(g/cm2/MeV)" << G4endl;
    if (1 && (!m_useScintSimple)) {
        DsG4Scintillation* scint = new DsG4Scintillation();
        scint->SetDoQuenching(m_enableQuenching);
        scint->SetBirksConstant1(m_birksConstant1);
        scint->SetBirksConstant2(m_birksConstant2);
        scint->SetGammaSlowerTimeConstant(m_gammaSlowerTime);
        scint->SetGammaSlowerRatio(m_gammaSlowerRatio);
        scint->SetNeutronSlowerTimeConstant(m_neutronSlowerTime);
        scint->SetNeutronSlowerRatio(m_neutronSlowerRatio);
        scint->SetAlphaSlowerTimeConstant(m_alphaSlowerTime);
        scint->SetAlphaSlowerRatio(m_alphaSlowerRatio);
        scint->SetDoReemission(m_doReemission);
        scint->SetDoReemissionOnly(m_doReemissionOnly);
        scint->SetDoBothProcess(m_doScintAndCeren);
        scint->SetApplyPreQE(m_scintPhotonScaleWeight>1.);
        scint->SetPreQE(1./m_scintPhotonScaleWeight);
        scint->SetScintillationYieldFactor(m_ScintillationYieldFactor); //1.);
        scint->SetUseFastMu300nsTrick(m_useFastMu300nsTrick);
        scint->SetTrackSecondariesFirst(true);
        scint->SetFlagDecayTimeFast(flagDecayTimeFast);
        scint->SetFlagDecayTimeSlow(flagDecayTimeSlow);
        if (!m_useScintillation) {
            scint->SetNoOp();
        }
        scint_ = scint;
    } else if (1 && m_useScintSimple) {
        G4cout << "Scintillation Physics Process: ScintSimple is used." << G4endl;
        // simple scint
        DsG4ScintSimple* scint = new DsG4ScintSimple();
        scint->SetDoQuenching(m_enableQuenching);
        scint->SetBirksConstant1(m_birksConstant1);
        scint->SetBirksConstant2(m_birksConstant2);
        scint->SetGammaSlowerTimeConstant(m_gammaSlowerTime);
        scint->SetGammaSlowerRatio(m_gammaSlowerRatio);
        scint->SetNeutronSlowerTimeConstant(m_neutronSlowerTime);
        scint->SetNeutronSlowerRatio(m_neutronSlowerRatio);
        scint->SetAlphaSlowerTimeConstant(m_alphaSlowerTime);
        scint->SetAlphaSlowerRatio(m_alphaSlowerRatio);
        scint->SetDoReemission(m_doReemission);
        scint->SetDoReemissionOnly(m_doReemissionOnly);
        scint->SetDoBothProcess(m_doScintAndCeren);
        scint->SetApplyPreQE(m_scintPhotonScaleWeight>1.);
        scint->SetPreQE(1./m_scintPhotonScaleWeight);
        scint->SetScintillationYieldFactor(m_ScintillationYieldFactor); //1.);
        scint->SetUseFastMu300nsTrick(m_useFastMu300nsTrick);
        scint->SetTrackSecondariesFirst(true);
        scint->SetFlagDecayTimeFast(flagDecayTimeFast);
        scint->SetFlagDecayTimeSlow(flagDecayTimeSlow);
        scint->SetVerboseLevel(fVerboseLevel);
        scint_ = scint;
    }
#else  // standard G4 scint
    G4Scintillation* scint = 0;
    if (m_useScintillation) {
        scint = new G4Scintillation();
        scint->SetScintillationYieldFactor(m_ScintillationYieldFactor); // 1.);
        scint->SetTrackSecondariesFirst(true);
    }
    scint_ = scint;
#endif

    // Note:
    //   Absorption and reemission processes.
    //   This is an experimental feature.
    //
    //   For compatible, the default ABSLENGTH of LS should be set as LAB,
    //   while set PPO, bis-MSB to DsG4OpAbsReemit.
    //
    // -- Tao Lin <lintao>
    DsG4OpAbsReemit* absreemit_PPO = 0;
    DsG4OpAbsReemit* absreemit_bisMSB = 0;
    if (m_useAbsReemit) {
        absreemit_PPO = new DsG4OpAbsReemit("PPO");
        absreemit_bisMSB = new DsG4OpAbsReemit("bisMSB");

        absreemit_PPO->SetVerboseLevel(fVerboseLevel);
        absreemit_bisMSB->SetVerboseLevel(fVerboseLevel);
    }

    G4OpAbsorption* absorb = 0;
    if (m_useAbsorption) {
        absorb = new G4OpAbsorption();
        absorb->SetVerboseLevel(fVerboseLevel);
        //if (m_useScintSimple) absorb->SetVerboseLevel(0);
    }

    G4OpRayleigh* rayleigh = 0;
    if (m_useRayleigh) {
        rayleigh = new G4OpRayleigh();
        rayleigh->SetVerboseLevel(fVerboseLevel);
        G4cout << "OpRay is set as " << fVerboseLevel << G4endl;
    }

    G4OpBoundaryProcess* boundproc = new G4OpBoundaryProcess();
    boundproc->SetVerboseLevel(fVerboseLevel);
    //DsG4OpBoundaryProcess* boundproc = new DsG4OpBoundaryProcess();
    //boundproc->SetModel(unified);

    G4FastSimulationManagerProcess* fast_sim_man = 0;
    if (m_doFastSim) {
        fast_sim_man = new G4FastSimulationManagerProcess("fast_sim_man");
    }

    auto theParticleIterator= GetParticleIterator();
    theParticleIterator->reset();
    while( (*theParticleIterator)() ) {

        G4ParticleDefinition* particle = theParticleIterator->value();
        G4ProcessManager* pmanager = particle->GetProcessManager();

        // Caution: as of G4.9, Cerenkov becomes a Discrete Process.
        // This code assumes a version of G4Cerenkov from before this version.

        if(cerenkov && cerenkov->IsApplicable(*particle)) {
            pmanager->AddProcess(cerenkov);
            pmanager->SetProcessOrdering(cerenkov, idxPostStep);
        }

        if(scint_ && scint_->IsApplicable(*particle)) {
            if (m_useScintSimple)
                G4cout << "Associate Scintillation with Particle " << (particle->GetParticleName()) << G4endl;

            pmanager->AddProcess(scint_);
            pmanager->SetProcessOrderingToLast(scint_, idxAtRest);
            pmanager->SetProcessOrderingToLast(scint_, idxPostStep);
        }

        if (particle == G4OpticalPhoton::Definition()) {
            G4cout << G4endl;
            G4cout << " Add Discrete Process to Optical Photon: ";
            if (absreemit_PPO) {
                pmanager->AddDiscreteProcess(absreemit_PPO);
                G4cout << "absreemit_PPO, ";
            }
            if (absreemit_bisMSB) {
                pmanager->AddDiscreteProcess(absreemit_bisMSB);
                G4cout << "absreemit_bisMSB, ";
            }
            if (absorb) {
                pmanager->AddDiscreteProcess(absorb);
                G4cout << absorb->GetProcessName() << " ";
            }
            if (rayleigh) {
                pmanager->AddDiscreteProcess(rayleigh);
                G4cout << rayleigh->GetProcessName() << " ";
            }
            if (m_doFastSim) {
                pmanager->AddDiscreteProcess(fast_sim_man);
                G4cout << fast_sim_man->GetProcessName() << " ";
            }
            pmanager->AddDiscreteProcess(boundproc);
            G4cout << boundproc->GetProcessName();
            G4cout << G4endl;
            //pmanager->AddDiscreteProcess(pee);
        }
    }
}

void DsPhysConsOptical::SetVerbose(G4int verbose)
{
    fVerboseLevel = verbose;
}

void DsPhysConsOptical::InitialiseOptions(){
    // for test
    if(fTruePhysics){
        if(fVerboseLevel>0)
            G4cout << "using real physics for optical photons" << G4endl;
        m_cerenMaxPhotonPerStep = 300;

        //m_doReemission = true;
        m_doReemission = true;
        m_doScintAndCeren = true;
        m_doReemissionOnly = false;

        m_useCerenkov=true;
        m_applyWaterQe=true;

        m_useScintillation=true;
        m_useScintSimple=false;
        m_useRayleigh=true;
        m_useAbsorption=true;
        m_useAbsReemit=false;
        m_useFastMu300nsTrick=false;
        m_ScintillationYieldFactor = 1.0;

        m_enableQuenching=true;
    }
    else{
        if(fVerboseLevel>0)
            G4cout << "using toy model physics for optical photons" << G4endl;
        m_cerenMaxPhotonPerStep = 300;

        m_doReemission = false;
        m_doScintAndCeren = false;
        m_doReemissionOnly = false;

        m_useCerenkov=false;
        m_applyWaterQe=false;

        m_useScintillation=false;
        m_useScintSimple=false;
        m_useRayleigh=true;
        m_useAbsorption=false;
        m_useAbsReemit=false;
        m_useFastMu300nsTrick=false;
        m_ScintillationYieldFactor = 1.0;

        m_enableQuenching=true;
    }
    m_birksConstant1 = 6.5e-3*g/cm2/MeV;
    m_birksConstant2 = 1.5e-6*(g/cm2/MeV)*(g/cm2/MeV);

    m_gammaSlowerTime = 190*ns;
    m_gammaSlowerRatio = 0.15;

    m_neutronSlowerTime = 220*ns;
    m_neutronSlowerRatio = 0.34;

    m_alphaSlowerTime = 220*ns;
    m_alphaSlowerRatio = 0.35;

    m_doFastSim=false; // just the fast simulation

    flagDecayTimeFast=true;
    flagDecayTimeSlow=true;

    //m_cerenPhotonScaleWeight = 3.125;
    //m_scintPhotonScaleWeight = 3.125;
    m_cerenPhotonScaleWeight = 1;
    m_scintPhotonScaleWeight = 1;
}

void DsPhysConsOptical::SetTruePhysics(G4bool isTruePhysics){fTruePhysics = isTruePhysics;}
