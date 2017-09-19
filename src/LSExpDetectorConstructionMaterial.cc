#include "LSExpDetectorConstructionMaterial.hh"
#include "OpticalProperty.icc"

#include <G4Element.hh>
#include <G4Material.hh>
#include <G4MaterialPropertiesTable.hh>
#include "G4GenericMessenger.hh"

LSExpDetectorConstructionMaterial::LSExpDetectorConstructionMaterial()
    :fMessenger(0),
     fTrueMaterial(true)
{
    initialize();
    fMessenger
            =new G4GenericMessenger(this, "/JUNO/det/","detecter");
    fMessenger
            ->DeclareProperty("setTrueMaterial",
                              fTrueMaterial,
                              "Enable True Material")
            .SetStates(G4State_PreInit,G4State_Init,G4State_Idle);
}

LSExpDetectorConstructionMaterial::~LSExpDetectorConstructionMaterial() {
}

void LSExpDetectorConstructionMaterial::initialize() {
    C = new G4Element("Carbon", "C" , 6., 12.01*g/mole); 
    H = new G4Element("Hydrogen", "H" , 1., 1.01*g/mole);
    O = new G4Element("Oxygen", "O", 8., 16.00*g/mole); 
    N = new G4Element("Nitrogen", "N", 7., 14.01*g/mole);
    S = new G4Element("Sulfur", "S", 16., 32.066*g/mole);
    Ar = new G4Element("Argon", "Ar", 18, 39.948*g/mole);
}

G4Material* LSExpDetectorConstructionMaterial::GetLS() {
    // LS
    LS= new G4Material("LS", 0.859*g/cm3, 5);
    LS->AddElement(C,  0.87924);
    LS->AddElement(H,  0.1201);
    LS->AddElement(O,  0.00034);
    LS->AddElement(N,  0.00027);
    LS->AddElement(S,  0.00005);

    G4MaterialPropertiesTable* LSMPT = new G4MaterialPropertiesTable();

    if(fTrueMaterial){
        LSMPT->AddProperty("ABSLENGTH", GdLSABSEnergy, GdLSABSLength, 502);
        LSMPT->AddProperty("RAYLEIGH", GdLSRayEnergy, GdLSRayLength, 11);
        LSMPT->AddProperty("REEMISSIONPROB", GdLSReemEnergy, GdLSReem, 28);
    }
    LSMPT->AddProperty("RINDEX",   GdLSRefIndexEnergy, GdLSRefIndex, 18);
    LSMPT->AddProperty("FASTCOMPONENT", GdLSComEnergy, GdLSFastComponent, 275);
    LSMPT->AddProperty("SLOWCOMPONENT", GdLSComEnergy, GdLSFastComponent, 275);
    LSMPT->AddConstProperty("SCINTILLATIONYIELD", 11522/MeV);
    LSMPT->AddConstProperty("RESOLUTIONSCALE", 1.);
    LSMPT->AddConstProperty("YIELDRATIO", 1.);
    LSMPT->AddConstProperty("FASTTIMECONSTANT", 4.93*ns);
    LSMPT->AddConstProperty("SLOWTIMECONSTANT", 20.6*ns);
    // add fast/slow time constant for reemission
    LSMPT->AddProperty("ReemissionFASTTIMECONSTANT", component, GdLSReemissionFastTimeConstant,2);
    LSMPT->AddProperty("ReemissionSLOWTIMECONSTANT", component, GdLSReemissionSlowTimeConstant,2);
    LSMPT->AddProperty("ReemissionYIELDRATIO", component, GdLSReemissionYieldRatio,2);

    //LSMPT->AddProperty("GammaYIELDRATIO", component, GdLSYieldRatio,2);

    // add fast/slow time constant for alpha
    LSMPT->AddProperty("AlphaFASTTIMECONSTANT", component, GdLSAlphaFastTimeConstant,2);
    LSMPT->AddProperty("AlphaSLOWTIMECONSTANT", component, GdLSAlphaSlowTimeConstant,2);
    LSMPT->AddProperty("AlphaYIELDRATIO", component, GdLSAlphaYieldRatio,2);

    // add fast/slow time constant for neutron
    LSMPT->AddProperty("NeutronFASTTIMECONSTANT", component, GdLSNeutronFastTimeConstant,2);
    LSMPT->AddProperty("NeutronSLOWTIMECONSTANT", component, GdLSNeutronSlowTimeConstant,2);
    LSMPT->AddProperty("NeutronYIELDRATIO", component, GdLSNeutronYieldRatio,2);

    // Following lines are for new Optical Model.
    // + PART I: Emission by PPO
    // + PART II: Absorption and Re-emission by PPO, bis-MSB and LAB
    //   Need:
    //     + XXXABSLENGTH
    //     + XXXREEMISSIONPROB
    //     + XXXCOMPONENT, maybe FAST/SLOW
    //     + XXXTIMECONSTANT, maybe FAST/SLOW
    //   XXX in [PPO, bisMSB, LAB]
    //LSMPT->AddProperty("PPOABSLENGTH", GdLSABSEnergy, GdLSABSLength, 502);
    //LSMPT->AddProperty("PPOREEMISSIONPROB", GdLSReemEnergy, GdLSReem, 28);
    //LSMPT->AddProperty("PPOCOMPONENT", GdLSComEnergy, GdLSFastComponent, 275);
    //LSMPT->AddProperty("PPOTIMECONSTANT", component, GdLSReemissionFastTimeConstant,2);

    //LSMPT->AddProperty("bisMSBABSLENGTH", GdLSABSEnergy, GdLSABSLength, 502);
    //LSMPT->AddProperty("bisMSBREEMISSIONPROB", GdLSReemEnergy, GdLSReem, 28);
    //LSMPT->AddProperty("bisMSBCOMPONENT", GdLSComEnergy, GdLSFastComponent, 275);
    //LSMPT->AddProperty("bisMSBTIMECONSTANT", component, GdLSReemissionFastTimeConstant,2);

    LS->SetMaterialPropertiesTable(LSMPT);

    return LS;
}

G4Material* LSExpDetectorConstructionMaterial::GetAcrylic() {
    // Acrylic
    Acrylic = new G4Material("Acrylic", 1.18*g/cm3, 3);
    Acrylic->AddElement(C, 0.59984);
    Acrylic->AddElement(H, 0.08055);
    Acrylic->AddElement(O, 0.31961);

    G4MaterialPropertiesTable* AcrylicMPT = new G4MaterialPropertiesTable();
    AcrylicMPT->AddProperty("ABSLENGTH", AcrylicAbsEnergy, AcrylicAbsLength, 9);
    AcrylicMPT->AddProperty("RAYLEIGH", AcrylicRayEnergy, AcrylicRayLength, 11);
    AcrylicMPT->AddProperty("RINDEX", AcrylicRefEnergy, AcrylicRefIndex, 18);

    Acrylic->SetMaterialPropertiesTable(AcrylicMPT);

    return Acrylic;
}

G4Material* LSExpDetectorConstructionMaterial::GetAir() {
    // Air
    G4double density = 1.205e-3*g/cm3;
    Air = new G4Material("Air", density, 4);
    Air->AddElement(N, 0.7550);
    Air->AddElement(O, 0.2321);
    Air->AddElement(Ar, 0.0128);
    Air->AddElement(C, 0.0001);
    G4double airPP[2] =
    {
        1.55*eV, 6.20*eV
    };
    G4double airRINDEX[2] =
    {
        1.000273, 1.000273
    };
    G4double airABSLENGTH[2] =
    {
        10000*m, 10000*m
    };
    G4MaterialPropertiesTable* airMPT = new G4MaterialPropertiesTable();
    airMPT->AddProperty("RINDEX",    airPP, airRINDEX,     2);
    airMPT->AddProperty("ABSLENGTH", airPP, airABSLENGTH,  2);
    Air->SetMaterialPropertiesTable(airMPT);

    return Air;
}

G4Material* LSExpDetectorConstructionMaterial::GetWater() {
    // Water
    G4double density= 1.000*g/cm3;
    Water = new G4Material("Water", density, 2);
    Water->AddElement(H,2);
    Water->AddElement(O,1);
    G4MaterialPropertiesTable* WaterMPT = new G4MaterialPropertiesTable();
    WaterMPT->AddProperty("RINDEX", fPP_Water_RIN, fWaterRINDEX,36);
    //WaterMPT->AddProperty("RINDEX", fPP_Oil_RIN, fOilRINDEX, 9);
    // scale the water absorption length
    double water_abslen_scale_factor = 90.*m/(2651.815*cm);
    for (int j = 0; j < 316; ++j) {
        fWaterABSORPTION[j] *= water_abslen_scale_factor;
    }
    if(fTrueMaterial)
        WaterMPT->AddProperty("ABSLENGTH", fPP_Water_ABS,fWaterABSORPTION, 316);
    //WaterMPT->AddProperty("ABSLENGTH",fPP_Oil_ABS, fOilABSORPTION, 543);
    Water->SetMaterialPropertiesTable(WaterMPT);

    return Water;
}

G4Material* LSExpDetectorConstructionMaterial::GetBlackWater() {
    // Water
    G4double density= 1.000*g/cm3;
    BlackWater = new G4Material("BlackWater", density, 2);
    BlackWater->AddElement(H,2);
    BlackWater->AddElement(O,1);
    G4MaterialPropertiesTable* WaterMPT = new G4MaterialPropertiesTable();
    WaterMPT->AddProperty("RINDEX", fPP_Water_RIN, fWaterRINDEX,36);
    //WaterMPT->AddProperty("RINDEX", fPP_Oil_RIN, fOilRINDEX, 9);
    // scale the water absorption length
    //double water_abslen_scale_factor = 90.*m/(2651.815*cm);
    for (int j = 0; j < 316; ++j) {
        fWaterABSORPTION[j] = 1.*nm;
    }
    if(fTrueMaterial)
        WaterMPT->AddProperty("ABSLENGTH", fPP_Water_ABS,fWaterABSORPTION, 316);
    //WaterMPT->AddProperty("ABSLENGTH",fPP_Oil_ABS, fOilABSORPTION, 543);
    BlackWater->SetMaterialPropertiesTable(WaterMPT);

    return BlackWater;
}
