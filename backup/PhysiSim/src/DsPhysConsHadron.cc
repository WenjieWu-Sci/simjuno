#include "DsPhysConsHadron.h"

#include "G4ProcessManager.hh"

/////////////////////////////////////// Hadron Processes

#include "G4TheoFSGenerator.hh"
#include "G4QGSModel.hh"
#include "G4QGSMFragmentation.hh"
#include "G4ExcitedStringDecay.hh"
#include "G4GeneratorPrecompoundInterface.hh"

// elastic fission and capture process for all hadrons
#include "G4HadronElasticProcess.hh"
#include "G4HadronFissionProcess.hh"
#include "G4HadronCaptureProcess.hh"

// inelastice process for each hadron
#include "G4PionPlusInelasticProcess.hh"
#include "G4PionMinusInelasticProcess.hh"
#include "G4KaonPlusInelasticProcess.hh"
#include "G4KaonZeroSInelasticProcess.hh"
#include "G4KaonZeroLInelasticProcess.hh"
#include "G4KaonMinusInelasticProcess.hh"
#include "G4ProtonInelasticProcess.hh"
#include "G4AntiProtonInelasticProcess.hh"
#include "G4NeutronInelasticProcess.hh"
#include "G4AntiNeutronInelasticProcess.hh"
#include "G4LambdaInelasticProcess.hh"
#include "G4AntiLambdaInelasticProcess.hh"
#include "G4SigmaPlusInelasticProcess.hh"
#include "G4SigmaMinusInelasticProcess.hh"
#include "G4AntiSigmaPlusInelasticProcess.hh"
#include "G4AntiSigmaMinusInelasticProcess.hh"
#include "G4XiZeroInelasticProcess.hh"
#include "G4XiMinusInelasticProcess.hh"
#include "G4AntiXiZeroInelasticProcess.hh"
#include "G4AntiXiMinusInelasticProcess.hh"
#include "G4OmegaMinusInelasticProcess.hh"
#include "G4AntiOmegaMinusInelasticProcess.hh"

// Low-energy models

#include "G4LElastic.hh"   
#include "G4LFission.hh"
#include "G4LCapture.hh"

#include "G4UHadronElasticProcess.hh"
#include "G4HadronElastic.hh"
#include "G4PreCompoundModel.hh"
#include "G4BinaryCascade.hh"
#include "G4CascadeInterface.hh"

#include "G4LEPionPlusInelastic.hh"
#include "G4LEPionMinusInelastic.hh"
#include "G4LEKaonPlusInelastic.hh"
#include "G4LEKaonZeroSInelastic.hh"
#include "G4LEKaonZeroLInelastic.hh"
#include "G4LEKaonMinusInelastic.hh"
#include "G4LEProtonInelastic.hh"
#include "G4LEAntiProtonInelastic.hh"
#include "G4LENeutronInelastic.hh"
#include "G4LEAntiNeutronInelastic.hh"
#include "G4LELambdaInelastic.hh"
#include "G4LEAntiLambdaInelastic.hh"
#include "G4LESigmaPlusInelastic.hh"
#include "G4LESigmaMinusInelastic.hh"
#include "G4LEAntiSigmaPlusInelastic.hh"
#include "G4LEAntiSigmaMinusInelastic.hh"
#include "G4LEXiZeroInelastic.hh"
#include "G4LEXiMinusInelastic.hh"
#include "G4LEAntiXiZeroInelastic.hh"
#include "G4LEAntiXiMinusInelastic.hh"
#include "G4LEOmegaMinusInelastic.hh"
#include "G4LEAntiOmegaMinusInelastic.hh"

// High-energy Models

#include "G4HEPionPlusInelastic.hh"
#include "G4HEPionMinusInelastic.hh"
#include "G4HEKaonPlusInelastic.hh"
#include "G4HEKaonZeroInelastic.hh"
#include "G4HEKaonZeroInelastic.hh"
#include "G4HEKaonMinusInelastic.hh"
#include "G4HEProtonInelastic.hh"
#include "G4HEAntiProtonInelastic.hh"
#include "G4HENeutronInelastic.hh"
#include "G4HEAntiNeutronInelastic.hh"
#include "G4HELambdaInelastic.hh"
#include "G4HEAntiLambdaInelastic.hh"
#include "G4HESigmaPlusInelastic.hh"
#include "G4HESigmaMinusInelastic.hh"
#include "G4HEAntiSigmaPlusInelastic.hh"
#include "G4HEAntiSigmaMinusInelastic.hh"
#include "G4HEXiZeroInelastic.hh"
#include "G4HEXiMinusInelastic.hh"
#include "G4HEAntiXiZeroInelastic.hh"
#include "G4HEAntiXiMinusInelastic.hh"
#include "G4HEOmegaMinusInelastic.hh"
#include "G4HEAntiOmegaMinusInelastic.hh"

// high precision model for neutron < 20MeV

#include "G4NeutronHPElastic.hh"
#include "G4NeutronHPInelastic.hh"
#include "G4NeutronHPFission.hh"
//#include "G4NeutronHPCapture.hh"
#include "DsG4NeutronHPCapture.h" // modified class from G4NeutronHPCapture 

#include "G4NeutronHPCaptureData.hh"
#include "G4NeutronHPFissionData.hh"
#include "G4NeutronHPElasticData.hh"
#include "G4NeutronHPInelasticData.hh"

//add thermal scattering
#include "DsG4NeutronHPThermalScatteringData.hh"
//#include "G4NeutronHPThermalScattering.hh"
#include "DsG4NeutronHPThermalScattering.hh"

// Stopping processes
#include "G4AntiProtonAnnihilationAtRest.hh"
#include "G4AntiNeutronAnnihilationAtRest.hh"
#include "G4PionMinusAbsorptionAtRest.hh"
#include "G4KaonMinusAbsorption.hh"

//Cross-section
#include "G4PiNuclearCrossSection.hh"
#include "G4ProtonInelasticCrossSection.hh"
#include "G4NeutronInelasticCrossSection.hh"

DsPhysConsHadron::DsPhysConsHadron(const G4String& name): G4VPhysicsConstructor(name)
{
    m_minEnergyForMultiFrag=3.0*MeV;
    m_maxEnergyPreEquilProton=70*MeV;
    m_minEnergyPreEquilNeutron=20*MeV;
    m_maxEnergyPreEquilNeutron=70*MeV;
    m_minEnergyHEModel=12*GeV;
    m_maxEnergyHEModel=100*TeV;
    m_lepUpperLimit=25*GeV;
    m_lepPnpiLimit=9.5*GeV;
    m_minEnergyBinaryCascadePN=65*MeV;
    m_maxEnergyBinaryCascadePN=9.9*GeV;
    m_minEnergyBinaryCascadePi=0*GeV;
    m_maxEnergyBinaryCascadePi=9.9*GeV;
    m_neutronElasticEnergyBoundary=20*MeV;
    m_neutronInlasticEnergyBoundary=20*MeV;
    m_fissionEnergyBoundary=20*MeV;
    m_captureEnergyBoundary=20*MeV;

}

DsPhysConsHadron::~DsPhysConsHadron()
{
}

// Interface methods
void DsPhysConsHadron::ConstructParticle()
{
}

#include "G4Element.hh"
static void dump_element_table()
{
    const G4ElementTable *theElementTable = G4Element::GetElementTable();
    size_t numberOfElements = theElementTable->size();
    G4cerr << numberOfElements <<" elements:\n";
    for( size_t ind=0; ind<numberOfElements; ++ind ) {
        G4Element* elem = (*theElementTable)[ind];
        G4cerr << ind << ": " << elem->GetName() << " " << elem->GetZ() << "/" << elem->GetA() 
               << " " << elem->GetNumberOfIsotopes() << " isotopes"
               << "\n";
    }
    G4cerr << G4endl;
}


void DsPhysConsHadron::ConstructProcess()
{

    // Hadronic Elastic Process and Model (the same for all hadrons except Neutron)

    G4HadronElasticProcess* theElasticProcess = new G4HadronElasticProcess("LElastic");
    G4LElastic* theElasticModel = new G4LElastic();
    theElasticProcess->RegisterMe(theElasticModel);


    // evaporation logic for thermal nucleons

    G4Evaporation* theEvaporation;
    G4FermiBreakUp* theFermiBreakUp;
    G4StatMF* theMF;
    theEvaporation = new G4Evaporation();
    theFermiBreakUp = new G4FermiBreakUp();
    theMF = new G4StatMF();

    G4ExcitationHandler* theHandler;
    theHandler = new G4ExcitationHandler();
    theHandler->SetEvaporation(theEvaporation);
    theHandler->SetFermiModel(theFermiBreakUp);
    theHandler->SetMultiFragmentation(theMF);
    theHandler->SetMaxAandZForFermiBreakUp(12, 6);
    //theHandler->SetMinEForMultiFrag(3.*MeV);
    theHandler->SetMinEForMultiFrag(m_minEnergyForMultiFrag);

    // pre-equilibrium stage for proton
    G4PreCompoundModel* thePreEquilib;
    thePreEquilib = new G4PreCompoundModel(theHandler);
    //thePreEquilib->SetMaxEnergy(70*MeV);
    thePreEquilib->SetMaxEnergy(m_maxEnergyPreEquilProton);

    // pre-equilibrium stage for neutron
    G4PreCompoundModel* thePreEquilib2;
    thePreEquilib2 = new G4PreCompoundModel(theHandler);
    //thePreEquilib2->SetMinEnergy(20*MeV);
    thePreEquilib2->SetMinEnergy(m_minEnergyPreEquilNeutron);
    //thePreEquilib2->SetMaxEnergy(70*MeV);
    thePreEquilib2->SetMaxEnergy(m_maxEnergyPreEquilNeutron);

    // high energy model for proton, neutron, pions and kaons
    G4TheoFSGenerator* theHEModel = new G4TheoFSGenerator();
    G4GeneratorPrecompoundInterface* theCascade2 =
        new G4GeneratorPrecompoundInterface();
    theCascade2->SetDeExcitation(thePreEquilib);
    theHEModel->SetTransport(theCascade2);
    G4QGSMFragmentation* frag = new G4QGSMFragmentation();
    G4ExcitedStringDecay* stringDecay = new G4ExcitedStringDecay(frag);
    G4QGSModel<G4QGSParticipants>* stringModel =
        new G4QGSModel<G4QGSParticipants>();
    stringModel->SetFragmentationModel(stringDecay);
    theHEModel->SetHighEnergyGenerator(stringModel);
    //theHEModel->SetMinEnergy(12*GeV);
    theHEModel->SetMinEnergy(m_minEnergyHEModel);
    //theHEModel->SetMaxEnergy(100*TeV);
    theHEModel->SetMaxEnergy(m_maxEnergyHEModel);

    // Low energy parameterized models : use between 9.5 and 25 GeV for pions
    //G4double LEPUpperLimit = 25*GeV;
    G4double LEPUpperLimit = m_lepUpperLimit;
    //G4double LEPpnpiLimit = 9.5*GeV;
    G4double LEPpnpiLimit = m_lepPnpiLimit;

    // Binary cascade for p, n at low energy
    G4BinaryCascade* theCasc;
    theCasc = new G4BinaryCascade;
    //theCasc->SetMinEnergy(65*MeV);
    theCasc->SetMinEnergy(m_minEnergyBinaryCascadePN);
    theCasc->SetMaxEnergy(m_maxEnergyBinaryCascadePN);

    // Binary cascade crashes on pi. use Bertini instead
    G4CascadeInterface* bertiniModel = new G4CascadeInterface();
    //bertiniModel->SetMinEnergy(0.*GeV);
    bertiniModel->SetMinEnergy(m_minEnergyBinaryCascadePi);
    bertiniModel->SetMaxEnergy(m_maxEnergyBinaryCascadePi);

    G4ProcessManager * pmanager = 0;

    ///////////////////
    //               //
    //  pi+ physics  //
    //               //
    ///////////////////

    pmanager = G4PionPlus::PionPlus()->GetProcessManager();

    // hadron elastic
    pmanager->AddDiscreteProcess(theElasticProcess);

    // hadron inelastic
    G4PionPlusInelasticProcess* pipinelProc = new G4PionPlusInelasticProcess();
    G4PiNuclearCrossSection* pion_XC = new G4PiNuclearCrossSection();
    pipinelProc->AddDataSet(pion_XC);

    pipinelProc->RegisterMe(bertiniModel);

    G4LEPionPlusInelastic* LEPpipModel = new G4LEPionPlusInelastic();
    LEPpipModel->SetMinEnergy(LEPpnpiLimit);
    LEPpipModel->SetMaxEnergy(LEPUpperLimit);

    pipinelProc->RegisterMe(LEPpipModel);
    pipinelProc->RegisterMe(theHEModel);
  
    pmanager->AddDiscreteProcess(pipinelProc);

    ///////////////////
    //               //
    //  pi- physics  //
    //               //
    ///////////////////

    pmanager = G4PionMinus::PionMinus()->GetProcessManager();

    // hadron elastic
    pmanager->AddDiscreteProcess(theElasticProcess);

    // hadron inelastic
    G4PionMinusInelasticProcess* piminelProc = new G4PionMinusInelasticProcess();

    piminelProc->AddDataSet(pion_XC);

    piminelProc->RegisterMe(bertiniModel);

    G4LEPionMinusInelastic* LEPpimModel = new G4LEPionMinusInelastic();
    LEPpimModel->SetMinEnergy(LEPpnpiLimit);
    LEPpimModel->SetMaxEnergy(LEPUpperLimit);
      
    piminelProc->RegisterMe(LEPpimModel);
    piminelProc->RegisterMe(theHEModel);

    pmanager->AddDiscreteProcess(piminelProc);

    // pi- absorption at rest
    G4PionMinusAbsorptionAtRest* pimAbsorb = new G4PionMinusAbsorptionAtRest();
    pmanager->AddRestProcess(pimAbsorb);

    ///////////////////
    //               //
    //  K+ physics   //
    //               //
    ///////////////////

    pmanager = G4KaonPlus::KaonPlus()->GetProcessManager();

    // hadron elastic
    pmanager->AddDiscreteProcess(theElasticProcess);


    // hadron inelastic
    G4KaonPlusInelasticProcess* kpinelProc = new G4KaonPlusInelasticProcess();
    G4LEKaonPlusInelastic* LEPkpModel = new G4LEKaonPlusInelastic();
    LEPkpModel->SetMaxEnergy(LEPUpperLimit);
      
    kpinelProc->RegisterMe(LEPkpModel);
    kpinelProc->RegisterMe(theHEModel);
      
    pmanager->AddDiscreteProcess(kpinelProc);

    ///////////////////
    //               //
    //  K0S physics  //
    //               //
    ///////////////////

    pmanager = G4KaonZeroShort::KaonZeroShort()->GetProcessManager();

    // hadron elastic
    pmanager->AddDiscreteProcess(theElasticProcess);

    // hadron inelastic
    G4KaonZeroSInelasticProcess* k0SinelProc = new G4KaonZeroSInelasticProcess();
    G4LEKaonZeroSInelastic* LEPk0SModel = new G4LEKaonZeroSInelastic();
    LEPk0SModel->SetMaxEnergy(LEPUpperLimit);

    k0SinelProc->RegisterMe(LEPk0SModel);
    k0SinelProc->RegisterMe(theHEModel);
      
    pmanager->AddDiscreteProcess(k0SinelProc);

    ///////////////////
    //               //
    //  K0L physics  //
    //               //
    ///////////////////

    pmanager = G4KaonZeroLong::KaonZeroLong()->GetProcessManager();

    // hadron elastic
    pmanager->AddDiscreteProcess(theElasticProcess);

    // hadron inelastic
    G4KaonZeroLInelasticProcess* k0LinelProc = new G4KaonZeroLInelasticProcess();
    G4LEKaonZeroLInelastic* LEPk0LModel = new G4LEKaonZeroLInelastic();
    LEPk0LModel->SetMaxEnergy(LEPUpperLimit);
      
    k0LinelProc->RegisterMe(LEPk0LModel);
    k0LinelProc->RegisterMe(theHEModel);
      
    pmanager->AddDiscreteProcess(k0LinelProc);

    ///////////////////
    //               //
    //  K- physics   //
    //               //
    ///////////////////

    pmanager = G4KaonMinus::KaonMinus()->GetProcessManager();

    // hadron elastic
    pmanager->AddDiscreteProcess(theElasticProcess);
      
    // hadron inelastic
    G4KaonMinusInelasticProcess* kminelProc = new G4KaonMinusInelasticProcess();
    G4LEKaonMinusInelastic* LEPkmModel = new G4LEKaonMinusInelastic();
    LEPkmModel->SetMaxEnergy(LEPUpperLimit);
      
    kminelProc->RegisterMe(LEPkmModel);
    kminelProc->RegisterMe(theHEModel);
      
    pmanager->AddDiscreteProcess(kminelProc);

    // K- absorption at rest
    G4KaonMinusAbsorption* kmAbsorb = new G4KaonMinusAbsorption();
    pmanager->AddRestProcess(kmAbsorb);
  
    ///////////////////
    //               //
    //    Proton     //
    //               //
    ///////////////////

    pmanager = G4Proton::Proton()->GetProcessManager();

    // hadron elastic
    pmanager->AddDiscreteProcess(theElasticProcess);

    // hadron inelastic
    G4ProtonInelasticProcess* pinelProc = new G4ProtonInelasticProcess();
    G4ProtonInelasticCrossSection* proton_XC = 
        new G4ProtonInelasticCrossSection();
    pinelProc->AddDataSet(proton_XC);

    G4LEProtonInelastic* LEPpModel = new G4LEProtonInelastic();
    LEPpModel->SetMinEnergy(LEPpnpiLimit);
    LEPpModel->SetMaxEnergy(LEPUpperLimit);

    pinelProc->RegisterMe(thePreEquilib);
    pinelProc->RegisterMe(theCasc);
    pinelProc->RegisterMe(LEPpModel);
    pinelProc->RegisterMe(theHEModel);

    pmanager->AddDiscreteProcess(pinelProc);

    ///////////////////
    //               //
    //  Anti-Proton  //
    //               //
    ///////////////////

    pmanager = G4AntiProton::AntiProton()->GetProcessManager();

    // hadron elastic
    pmanager->AddDiscreteProcess(theElasticProcess);

    // hadron inelastic
    G4AntiProtonInelasticProcess* apinelProc = 
        new G4AntiProtonInelasticProcess();
    G4LEAntiProtonInelastic* LEPapModel = new G4LEAntiProtonInelastic(); 
    LEPapModel->SetMaxEnergy(LEPUpperLimit);
    apinelProc->RegisterMe(LEPapModel);

    G4HEAntiProtonInelastic* HEPapModel = new G4HEAntiProtonInelastic(); 
    HEPapModel->SetMinEnergy(LEPUpperLimit);
    apinelProc->RegisterMe(HEPapModel);

    pmanager->AddDiscreteProcess(apinelProc);

    // anti-proton annihilation at rest
    G4AntiProtonAnnihilationAtRest* apAnnihil = 
        new G4AntiProtonAnnihilationAtRest();
    pmanager->AddRestProcess(apAnnihil);
 
    ///////////////////
    //               //
    //    Neutron    //
    //               //
    ///////////////////

    pmanager = G4Neutron::Neutron()->GetProcessManager();

    // elastic scattering
    G4UHadronElasticProcess* theHadronElasticProcess = new G4UHadronElasticProcess("neutronElastic");
    G4HadronElastic* theNeutronElasticModel = new G4HadronElastic();
    G4NeutronHPElastic* theNeutronHPElastic = new G4NeutronHPElastic();
    //theNeutronHPElastic->SetMinEnergy(0.*MeV);
    theNeutronHPElastic->SetMinEnergy(4.0*eV);//caogf
    //theNeutronHPElastic->SetMaxEnergy(20.*MeV);
    theNeutronHPElastic->SetMaxEnergy(m_neutronElasticEnergyBoundary);

    dump_element_table();
    G4NeutronHPElasticData* theHPElasticData = new G4NeutronHPElasticData();
    //theNeutronElasticModel->SetMinEnergy(20.*MeV);
    theNeutronElasticModel->SetMinEnergy(m_neutronElasticEnergyBoundary);

    //add thermal scattering
    DsG4NeutronHPThermalScatteringData* theHPThermalScatteringData = new DsG4NeutronHPThermalScatteringData();
    theHadronElasticProcess->AddDataSet(theHPThermalScatteringData);
    DsG4NeutronHPThermalScattering* theNeutronThermalElasticModel = new DsG4NeutronHPThermalScattering();
    theNeutronThermalElasticModel->SetMaxEnergy(4.0*eV);
  
    theHadronElasticProcess->RegisterMe(theNeutronHPElastic);
    theHadronElasticProcess->AddDataSet(theHPElasticData);
    theHadronElasticProcess->RegisterMe(theNeutronElasticModel);
    theHadronElasticProcess->RegisterMe(theNeutronThermalElasticModel);

    pmanager->AddDiscreteProcess(theHadronElasticProcess);

      
    // inelastic scattering
    G4NeutronInelasticProcess* ninelProc = new G4NeutronInelasticProcess();
    G4NeutronInelasticCrossSection* neutron_XC = 
        new G4NeutronInelasticCrossSection();
    ninelProc->AddDataSet(neutron_XC);
  
    G4NeutronHPInelastic* theNeutronHPInelastic = new G4NeutronHPInelastic();
    //theNeutronHPInelastic->SetMaxEnergy(20.*MeV );
    theNeutronHPInelastic->SetMaxEnergy(m_neutronInlasticEnergyBoundary);
    G4NeutronHPInelasticData* theHPInelasticData = new G4NeutronHPInelasticData();

    G4LENeutronInelastic* LEPnModel = new G4LENeutronInelastic();
    LEPnModel->SetMinEnergy(LEPpnpiLimit);
    LEPnModel->SetMaxEnergy(LEPUpperLimit);

    ninelProc->RegisterMe(theNeutronHPInelastic);
    ninelProc->AddDataSet(theHPInelasticData);
    ninelProc->RegisterMe(thePreEquilib2);
    ninelProc->RegisterMe(theCasc);
    ninelProc->RegisterMe(LEPnModel);
    ninelProc->RegisterMe(theHEModel);

    pmanager->AddDiscreteProcess(ninelProc);

    // fission process 
    G4HadronFissionProcess* theHadronFissionProcess = new G4HadronFissionProcess();
    G4LFission* theNeutronLFission = new G4LFission();
    G4NeutronHPFission* theNeutronHPFission  = new   G4NeutronHPFission();
    //theNeutronHPFission->SetMaxEnergy( 20.*MeV );
    theNeutronHPFission->SetMaxEnergy(m_fissionEnergyBoundary);
    //theNeutronLFission->SetMinEnergy( 20.*MeV );
    theNeutronLFission->SetMinEnergy(m_fissionEnergyBoundary);
    theHadronFissionProcess->RegisterMe( theNeutronHPFission );
    theHadronFissionProcess->RegisterMe( theNeutronLFission );
    //AddDataSet(theHadronFissionProcess, new G4NeutronHPFissionData() );
    theHadronFissionProcess->AddDataSet(new G4NeutronHPFissionData());
    pmanager->AddDiscreteProcess(theHadronFissionProcess);
      
    // capture  
    G4HadronCaptureProcess* theNeutronCaptureProcess = new G4HadronCaptureProcess();
    G4LCapture* theNeutronLCapture = new G4LCapture();

    DsG4NeutronHPCapture* theNeutronHPCapture = new DsG4NeutronHPCapture();

    //theNeutronHPCapture->SetMaxEnergy( 20.*MeV );
    theNeutronHPCapture->SetMaxEnergy(m_captureEnergyBoundary);
    //theNeutronLCapture->SetMinEnergy( 20.*MeV );

    theNeutronLCapture->SetMinEnergy(m_captureEnergyBoundary);
    theNeutronCaptureProcess->RegisterMe( theNeutronHPCapture );
    theNeutronCaptureProcess->RegisterMe( theNeutronLCapture );
    //AddDataSet(theNeutronCaptureProcess, new G4NeutronHPCaptureData());
    theNeutronCaptureProcess->AddDataSet(new G4NeutronHPCaptureData());
    pmanager->AddDiscreteProcess(theNeutronCaptureProcess);

    ///////////////////
    //               //
    // Anti-Neutron  //
    //               //
    ///////////////////

    pmanager = G4AntiNeutron::AntiNeutron()->GetProcessManager();

    // hadron elastic
    pmanager->AddDiscreteProcess(theElasticProcess);

    // hadron inelastic
    G4AntiNeutronInelasticProcess* aninelProc = 
        new G4AntiNeutronInelasticProcess();
    G4LEAntiNeutronInelastic* LEPanModel = new G4LEAntiNeutronInelastic();
    LEPanModel->SetMaxEnergy(LEPUpperLimit); 
    aninelProc->RegisterMe(LEPanModel);
    G4HEAntiNeutronInelastic* HEPanModel = new G4HEAntiNeutronInelastic();
    HEPanModel->SetMinEnergy(LEPUpperLimit);
    aninelProc->RegisterMe(HEPanModel);
    pmanager->AddDiscreteProcess(aninelProc);

    // anti-neutron annihilation at rest
    G4AntiNeutronAnnihilationAtRest* anAnnihil = 
        new G4AntiNeutronAnnihilationAtRest();
    pmanager->AddRestProcess(anAnnihil);

    ///////////////////
    //               //
    //    Lambda     //
    //               //
    ///////////////////

    pmanager = G4Lambda::Lambda()->GetProcessManager();

    // hadron elastic
    pmanager->AddDiscreteProcess(theElasticProcess);

    // hadron inelastic
    G4LambdaInelasticProcess* linelProc = 
        new G4LambdaInelasticProcess();
    G4LELambdaInelastic* LEPlModel = new G4LELambdaInelastic();
    LEPlModel->SetMaxEnergy(LEPUpperLimit); 
    linelProc->RegisterMe(LEPlModel);
    G4HELambdaInelastic* HEPlModel = new G4HELambdaInelastic(); 
    HEPlModel->SetMinEnergy(LEPUpperLimit);
    linelProc->RegisterMe(HEPlModel);
  
    pmanager->AddDiscreteProcess(linelProc);

    ///////////////////
    //               //
    //  Anti-Lambda  //
    //               //
    ///////////////////

    pmanager = G4AntiLambda::AntiLambda()->GetProcessManager();

    // hadron elastic
    pmanager->AddDiscreteProcess(theElasticProcess);

    // hadron inelastic
    G4AntiLambdaInelasticProcess* alinelProc = 
        new G4AntiLambdaInelasticProcess();
    G4LEAntiLambdaInelastic* LEPalModel = new G4LEAntiLambdaInelastic();
    LEPalModel->SetMaxEnergy(LEPUpperLimit); 
    alinelProc->RegisterMe(LEPalModel);
    G4HEAntiLambdaInelastic* HEPalModel = new G4HEAntiLambdaInelastic(); 
    HEPalModel->SetMinEnergy(LEPUpperLimit);
    alinelProc->RegisterMe(HEPalModel);

    pmanager->AddDiscreteProcess(alinelProc);

    ///////////////////
    //               //
    //    Sigma+     //
    //               //
    ///////////////////

    pmanager = G4SigmaPlus::SigmaPlus()->GetProcessManager();

    // hadron elastic
    pmanager->AddDiscreteProcess(theElasticProcess);

    // hadron inelastic
    G4SigmaPlusInelasticProcess* spinelProc = new G4SigmaPlusInelasticProcess();
    G4LESigmaPlusInelastic* LEPspModel = new G4LESigmaPlusInelastic();
    LEPspModel->SetMaxEnergy(LEPUpperLimit);
    spinelProc->RegisterMe(LEPspModel);
    G4HESigmaPlusInelastic* HEPspModel = new G4HESigmaPlusInelastic(); 
    HEPspModel->SetMinEnergy(LEPUpperLimit);
    spinelProc->RegisterMe(HEPspModel);
      
    pmanager->AddDiscreteProcess(spinelProc);

    ///////////////////
    //               //
    //    Sigma-     //
    //               //
    ///////////////////

    pmanager = G4SigmaMinus::SigmaMinus()->GetProcessManager();

    // hadron elastic
    pmanager->AddDiscreteProcess(theElasticProcess);

    // hadron inelastic
    G4SigmaMinusInelasticProcess* sminelProc = 
        new G4SigmaMinusInelasticProcess();
    G4LESigmaMinusInelastic* LEPsmModel = new G4LESigmaMinusInelastic(); 
    LEPsmModel->SetMaxEnergy(LEPUpperLimit);
    sminelProc->RegisterMe(LEPsmModel);
    G4HESigmaMinusInelastic* HEPsmModel = new G4HESigmaMinusInelastic(); 
    HEPsmModel->SetMinEnergy(LEPUpperLimit);
    sminelProc->RegisterMe(HEPsmModel);
      
    pmanager->AddDiscreteProcess(sminelProc);

    ///////////////////
    //               //
    //  Anti-Sigma+  //
    //               //
    ///////////////////

    pmanager = G4AntiSigmaPlus::AntiSigmaPlus()->GetProcessManager();

    // hadron elastic
    pmanager->AddDiscreteProcess(theElasticProcess);

    // hadron inelastic
    G4AntiSigmaPlusInelasticProcess* aspinelProc = 
        new G4AntiSigmaPlusInelasticProcess();
    G4LEAntiSigmaPlusInelastic* LEPaspModel = 
        new G4LEAntiSigmaPlusInelastic(); 
    LEPaspModel->SetMaxEnergy(LEPUpperLimit);
    aspinelProc->RegisterMe(LEPaspModel);
    G4HEAntiSigmaPlusInelastic* HEPaspModel = 
        new G4HEAntiSigmaPlusInelastic(); 
    HEPaspModel->SetMinEnergy(LEPUpperLimit);
    aspinelProc->RegisterMe(HEPaspModel);
    pmanager->AddDiscreteProcess(aspinelProc);

    ///////////////////
    //               //
    //  Anti-Sigma-  //
    //               //
    ///////////////////

    pmanager = G4AntiSigmaMinus::AntiSigmaMinus()->GetProcessManager();

    // hadron elastic
    pmanager->AddDiscreteProcess(theElasticProcess);
      
    // hadron inelastic
    G4AntiSigmaMinusInelasticProcess* asminelProc = 
        new G4AntiSigmaMinusInelasticProcess();
    G4LEAntiSigmaMinusInelastic* LEPasmModel = 
        new G4LEAntiSigmaMinusInelastic(); 
    LEPasmModel->SetMaxEnergy(LEPUpperLimit);
    asminelProc->RegisterMe(LEPasmModel);
    G4HEAntiSigmaMinusInelastic* HEPasmModel = 
        new G4HEAntiSigmaMinusInelastic(); 
    HEPasmModel->SetMinEnergy(LEPUpperLimit);
    asminelProc->RegisterMe(HEPasmModel);

    pmanager->AddDiscreteProcess(asminelProc);

    ///////////////////
    //               //
    //      Xi0      //
    //               //
    ///////////////////

    pmanager = G4XiZero::XiZero()->GetProcessManager();

    // hadron elastic
    pmanager->AddDiscreteProcess(theElasticProcess);

    // hadron inelastic
    G4XiZeroInelasticProcess* x0inelProc = new G4XiZeroInelasticProcess();
    G4LEXiZeroInelastic* LEPx0Model = new G4LEXiZeroInelastic();
    LEPx0Model->SetMaxEnergy(LEPUpperLimit); 
    x0inelProc->RegisterMe(LEPx0Model);
    G4HEXiZeroInelastic* HEPx0Model = new G4HEXiZeroInelastic(); 
    HEPx0Model->SetMinEnergy(LEPUpperLimit);
    x0inelProc->RegisterMe(HEPx0Model);

    pmanager->AddDiscreteProcess(x0inelProc);

    ///////////////////
    //               //
    //      Xi-      //
    //               //
    ///////////////////

    pmanager = G4XiMinus::XiMinus()->GetProcessManager();

    // hadron elastic
    pmanager->AddDiscreteProcess(theElasticProcess);

    // hadron inelastic
    G4XiMinusInelasticProcess* xminelProc = new G4XiMinusInelasticProcess();
    G4LEXiMinusInelastic* LEPxmModel = new G4LEXiMinusInelastic(); 
    LEPxmModel->SetMaxEnergy(LEPUpperLimit);
    xminelProc->RegisterMe(LEPxmModel);
    G4HEXiMinusInelastic* HEPxmModel = new G4HEXiMinusInelastic();
    HEPxmModel->SetMinEnergy(LEPUpperLimit);
    xminelProc->RegisterMe(HEPxmModel);
      
    pmanager->AddDiscreteProcess(xminelProc);

    ///////////////////
    //               //
    //   Anti-Xi0    //
    //               //
    ///////////////////

    pmanager = G4AntiXiZero::AntiXiZero()->GetProcessManager();

    // hadron elastic
    pmanager->AddDiscreteProcess(theElasticProcess);

    // hadron inelastic
    G4AntiXiZeroInelasticProcess* ax0inelProc = 
        new G4AntiXiZeroInelasticProcess();
    G4LEAntiXiZeroInelastic* LEPax0Model = new G4LEAntiXiZeroInelastic();
    LEPax0Model->SetMaxEnergy(LEPUpperLimit); 
    ax0inelProc->RegisterMe(LEPax0Model);
    G4HEAntiXiZeroInelastic* HEPax0Model = new G4HEAntiXiZeroInelastic(); 
    HEPax0Model->SetMinEnergy(LEPUpperLimit);
    ax0inelProc->RegisterMe(HEPax0Model);

    pmanager->AddDiscreteProcess(ax0inelProc);

    ///////////////////
    //               //
    //   Anti-Xi-    //
    //               //
    ///////////////////

    pmanager = G4AntiXiMinus::AntiXiMinus()->GetProcessManager();

    // hadron elastic
    pmanager->AddDiscreteProcess(theElasticProcess);

    // hadron inelastic
    G4AntiXiMinusInelasticProcess* axminelProc = 
        new G4AntiXiMinusInelasticProcess();
    G4LEAntiXiMinusInelastic* LEPaxmModel = new G4LEAntiXiMinusInelastic();
    LEPaxmModel->SetMaxEnergy(LEPUpperLimit);
    axminelProc->RegisterMe(LEPaxmModel);
    G4HEAntiXiMinusInelastic* HEPaxmModel = new G4HEAntiXiMinusInelastic();
    HEPaxmModel->SetMinEnergy(LEPUpperLimit);
    axminelProc->RegisterMe(HEPaxmModel);

    pmanager->AddDiscreteProcess(axminelProc);

    ///////////////////
    //               //
    //    Omega-     //
    //               //
    ///////////////////

    pmanager = G4OmegaMinus::OmegaMinus()->GetProcessManager();

    // hadron elastic
    pmanager->AddDiscreteProcess(theElasticProcess);

    // hadron inelastic
    G4OmegaMinusInelasticProcess* ominelProc = 
        new G4OmegaMinusInelasticProcess();
    G4LEOmegaMinusInelastic* LEPomModel = new G4LEOmegaMinusInelastic();
    LEPomModel->SetMaxEnergy(LEPUpperLimit); 
    ominelProc->RegisterMe(LEPomModel);
    G4HEOmegaMinusInelastic* HEPomModel = new G4HEOmegaMinusInelastic();
    HEPomModel->SetMinEnergy(LEPUpperLimit);
    ominelProc->RegisterMe(HEPomModel);
      
    pmanager->AddDiscreteProcess(ominelProc);

    ///////////////////
    //               //
    //  Anti-Omega-  //
    //               //
    ///////////////////

    pmanager = G4AntiOmegaMinus::AntiOmegaMinus()->GetProcessManager();

    // hadron elastic
    pmanager->AddDiscreteProcess(theElasticProcess);

    // hadron inelastic
    G4AntiOmegaMinusInelasticProcess* aominelProc = 
        new G4AntiOmegaMinusInelasticProcess();
    G4LEAntiOmegaMinusInelastic* LEPaomModel = 
        new G4LEAntiOmegaMinusInelastic();
    LEPaomModel->SetMaxEnergy(LEPUpperLimit);
    aominelProc->RegisterMe(LEPaomModel);
    G4HEAntiOmegaMinusInelastic* HEPaomModel = 
        new G4HEAntiOmegaMinusInelastic(); 
    HEPaomModel->SetMinEnergy(LEPUpperLimit);
    aominelProc->RegisterMe(HEPaomModel);

    pmanager->AddDiscreteProcess(aominelProc);

}

