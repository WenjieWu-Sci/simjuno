#include <boost/python.hpp>
#define USE_CUSTOM_CERENKOV
#define USE_CUSTOM_SCINTILLATION

#include "DsPhysConsOptical.h"
#include "DsG4OpRayleigh.h"

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

#include "SniperKernel/SniperPtr.h"
#include "SniperKernel/ToolFactory.h"
#include "SniperKernel/SniperLog.h"

DECLARE_TOOL(DsPhysConsOptical);

DsPhysConsOptical::DsPhysConsOptical(const G4String& name): G4VPhysicsConstructor(name)
                                                            , ToolBase(name)
{
    declProp("CerenMaxPhotonsPerStep", m_cerenMaxPhotonPerStep = 300);

    declProp("ScintDoReemission", m_doReemission = true);
    declProp("ScintDoScintAndCeren", m_doScintAndCeren = true);
    declProp("ScintDoReemissionOnly", m_doReemissionOnly = false);

    declProp("UseCerenkov", m_useCerenkov=true);
    declProp("ApplyWaterQe", m_applyWaterQe=true);

    declProp("UseScintillation", m_useScintillation=true);
    declProp("UseScintSimple", m_useScintSimple=false);
    declProp("UseRayleigh", m_useRayleigh=true);
    declProp("UseAbsorption", m_useAbsorption=true);
    declProp("UseAbsReemit", m_useAbsReemit=false);
    declProp("UseFastMu300nsTrick", m_useFastMu300nsTrick=false);
    declProp("ScintillationYieldFactor", m_ScintillationYieldFactor = 1.0);
   
    declProp("UseQuenching", m_enableQuenching=true);
    declProp("BirksConstant1", m_birksConstant1 = 6.5e-3*g/cm2/MeV);
    declProp("BirksConstant2", m_birksConstant2 = 1.5e-6*(g/cm2/MeV)*(g/cm2/MeV));

    declProp("GammaSlowerTime", m_gammaSlowerTime = 190*ns); 
    declProp("GammaSlowerRatio", m_gammaSlowerRatio = 0.15);

    declProp("NeutronSlowerTime", m_neutronSlowerTime = 220*ns);
    declProp("NeutronSlowerRatio", m_neutronSlowerRatio = 0.34);

    declProp("AlphaSlowerTime", m_alphaSlowerTime = 220*ns);
    declProp("AlphaSlowerRatio", m_alphaSlowerRatio = 0.35);

    declProp("UsePMTOpticalModel", m_doFastSim=true); // just the fast simulation

    declProp("doDecayTimeFast", flagDecayTimeFast=true);
    declProp("doDecayTimeSlow", flagDecayTimeSlow=true);

    //m_cerenPhotonScaleWeight = 3.125;
    //m_scintPhotonScaleWeight = 3.125;
    m_cerenPhotonScaleWeight = 1;
    m_scintPhotonScaleWeight = 1;
}

DsPhysConsOptical::~DsPhysConsOptical()
{
}

void DsPhysConsOptical::ConstructParticle()
{
}

void DsPhysConsOptical::ConstructProcess()
{
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
    LogInfo << "DoQuenching: " << m_enableQuenching << std::endl;
    LogInfo << "Birks Constant 1: " 
            << m_birksConstant1/(g/cm2/MeV) 
            << "g/cm2/MeV" << std::endl;
    LogInfo << "Birks Constant 2: "
            << m_birksConstant2/((g/cm2/MeV)*(g/cm2/MeV))
            << "(g/cm2/MeV)*(g/cm2/MeV)" << std::endl;
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
    LogInfo << "Scintillation Physics Process: ScintSimple is used." << std::endl;
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
    scint->SetVerboseLevel(0);
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

        absreemit_PPO->SetVerboseLevel(0);
        absreemit_bisMSB->SetVerboseLevel(0);
    }

    G4OpAbsorption* absorb = 0;
    if (m_useAbsorption) {
        absorb = new G4OpAbsorption();
        if (m_useScintSimple) absorb->SetVerboseLevel(0);
    }

    DsG4OpRayleigh* rayleigh = 0;
    if (m_useRayleigh) {
        rayleigh = new DsG4OpRayleigh();
	//        rayleigh->SetVerboseLevel(2);
    }

    G4OpBoundaryProcess* boundproc = new G4OpBoundaryProcess();
    //DsG4OpBoundaryProcess* boundproc = new DsG4OpBoundaryProcess();
    boundproc->SetModel(unified);

    G4FastSimulationManagerProcess* fast_sim_man = 0;
    if (m_doFastSim) {
        fast_sim_man = new G4FastSimulationManagerProcess("fast_sim_man");
    }
    
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
            if (m_useScintSimple) LogInfo << "Associate Scintillation with Particle " << (particle->GetParticleName()) << std::endl;

            pmanager->AddProcess(scint_);
            pmanager->SetProcessOrderingToLast(scint_, idxAtRest);
            pmanager->SetProcessOrderingToLast(scint_, idxPostStep);
        }

        if (particle == G4OpticalPhoton::Definition()) {
            if (absreemit_PPO)
                pmanager->AddDiscreteProcess(absreemit_PPO);
            if (absreemit_bisMSB)
                pmanager->AddDiscreteProcess(absreemit_bisMSB);
            if (absorb)
                pmanager->AddDiscreteProcess(absorb);
            if (rayleigh)
                pmanager->AddDiscreteProcess(rayleigh);
            pmanager->AddDiscreteProcess(boundproc);
            //pmanager->AddDiscreteProcess(pee);
            if (m_doFastSim) {
                pmanager->AddDiscreteProcess(fast_sim_man);
            }
        }
    }
}
