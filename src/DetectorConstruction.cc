#include "DetectorConstruction.hh"

#include <G4LogicalVolume.hh>
#include <G4PVPlacement.hh>
#include <G4NistManager.hh>
#include <G4SystemOfUnits.hh>
#include <G4VisAttributes.hh>
#include <G4Box.hh>
#include <G4Orb.hh>
#include <G4SDManager.hh>
#include <G4GlobalMagFieldMessenger.hh>
#include <G4Sphere.hh>
#include <G4PhysicalConstants.hh>
#include <G4OpticalSurface.hh>
#include <G4LogicalBorderSurface.hh>

#include "EnergyTimeSD.hh"
#include "LSExpDetectorConstructionMaterial.hh"

using namespace std;

G4VPhysicalVolume* DetectorConstruction::Construct()
{
    G4NistManager* nist = G4NistManager::Instance();
    LSExpDetectorConstructionMaterial* MatTable= new LSExpDetectorConstructionMaterial();
    G4Material* JUNOAir= MatTable->GetAir();
    G4Material* JUNOLS= MatTable->GetLS();
    G4Material* JUNOAcrylic= MatTable->GetAcrylic();
    G4Material* JUNOWater= MatTable->GetWater();
    G4Material* black_water = MatTable->GetBlackWater();

    G4bool fCheckOverlap= true;

    // create a experimental hall with size 50*50*50 m
    G4double worldSizeX = 50 * m;
    G4double worldSizeY = 50 * m;
    G4double worldSizeZ = 50 * m;
    G4VSolid* worldBox = new G4Box("world", worldSizeX / 2, worldSizeY / 2, worldSizeZ / 2);
    worldLog = new G4LogicalVolume(worldBox, JUNOAir, "world");
    G4VisAttributes* visAttr = new G4VisAttributes();
    visAttr->SetVisibility(false);
    worldLog->SetVisAttributes(visAttr);
    G4VPhysicalVolume* worldPhys = new G4PVPlacement(nullptr, {}, worldLog, "world", nullptr, false, 0);

    // CD with radius equal to 17.7 m
    G4double radius = 17.7 * m;
    G4VSolid* CDSphere= new G4Sphere("CentralDetector", 0, radius, 0, 2*pi, 0, pi);
    CDLog= new G4LogicalVolume(CDSphere, JUNOLS, "CentralDetector");
    G4VisAttributes* CDVis = new G4VisAttributes(G4Colour(0., 0.75, 1.));
    CDVis->SetVisibility(true);
    CDVis->SetForceSolid(false);
    CDLog->SetVisAttributes(CDVis);
    G4VPhysicalVolume* CDPhys= new G4PVPlacement(nullptr, // no Rotation
                                                 G4ThreeVector(0, 0, 0), // no transportation
                                                 CDLog,                  // current logical volume
                                                 "CentralDetector",      // Name
                                                 worldLog,               // mother logical volume
                                                 false,                  // pMany
                                                 0,                      // Copy No
                                                 fCheckOverlap);

    // Acrylic ball with inner radius equal to 17.7 m and thickness equal to 12 cm
    G4double inner_acrylic= 17.7 * m;
    G4double thickness_Acrylic= 12. * cm;
    G4double outer_acrylic= inner_acrylic + thickness_Acrylic;
    G4VSolid* AcrylicSphere= new G4Sphere("AcrylicBall", inner_acrylic, outer_acrylic, 0, 2*pi, 0, pi);
    AcrylicLog= new G4LogicalVolume(AcrylicSphere, JUNOAcrylic, "AcrylicBall");
    G4VisAttributes* AcrylicVis= new G4VisAttributes(G4Colour(0., 0.75, 1.));
    AcrylicVis->SetVisibility(false);
    AcrylicLog->SetVisAttributes(AcrylicVis);
    G4VPhysicalVolume* AcrylicPhys= new G4PVPlacement(nullptr, // no Rotation
                                                      G4ThreeVector(0, 0, 0), // no transportation
                                                      AcrylicLog,             // current logical volume
                                                      "AcrylicBall",          // Name
                                                      worldLog,               // mother logical volume
                                                      false,                  // pMany
                                                      0,                      // Copy No
                                                      fCheckOverlap);

    // water tank with thickness equal to 1 m
    G4double inner_water= outer_acrylic;
    G4double thickness_water= 1. * m;
    G4double outer_water= inner_water + thickness_water;
    G4VSolid* WaterSphere= new G4Sphere("WaterTank", inner_water, outer_water, 0, 2*pi, 0, pi);
    WaterLog= new G4LogicalVolume(WaterSphere, JUNOWater, "WaterTank");
    G4VisAttributes* WaterVis= new G4VisAttributes(G4Colour(0., 0.75, 1.));
    WaterVis->SetVisibility(false);
    WaterLog->SetVisAttributes(WaterVis);
    G4VPhysicalVolume* WaterPhys= new G4PVPlacement(nullptr, // no Rotation
                                                    G4ThreeVector(0, 0, 0), // no transportation
                                                    WaterLog,               // current logical volume
                                                    "WaterTank",            // Name
                                                    worldLog,               // mother logical volume
                                                    false,                  // pMany
                                                    0,                      // Copy No
                                                    fCheckOverlap);
    
    G4OpticalSurface* OpCDSurf= new G4OpticalSurface("CDSurface");
    OpCDSurf->SetType(dielectric_dielectric);
    OpCDSurf->SetFinish(polished);

    G4LogicalBorderSurface* CDSurf= new G4LogicalBorderSurface("CDSurface", CDPhys, AcrylicPhys, OpCDSurf);
    G4LogicalBorderSurface* AcrylicSurf= new G4LogicalBorderSurface("AcrylicSurface", AcrylicPhys, WaterPhys, OpCDSurf);

    // perfect detector
    G4VSolid* detectorSphere = new G4Sphere("Detector",outer_water,outer_water+1.*mm, 0, 2*pi, 0, pi);
    detectorLog = new G4LogicalVolume(detectorSphere, black_water, "Detector");
    G4VisAttributes* detectorVis = new G4VisAttributes();
    detectorVis->SetVisibility(false);
    detectorLog->SetVisAttributes(detectorVis);
    new G4PVPlacement(nullptr,
                      G4ThreeVector(0., 0., 0.),
                      detectorLog,
                      "Detector",
                      worldLog,
                      false,
                      0,
                      fCheckOverlap);


    G4cout << *(G4Material::GetMaterialTable()) << G4endl;

    return worldPhys;
}

void DetectorConstruction::ConstructSDandField() {
    G4SDManager* sdManager = G4SDManager::GetSDMpointer();
    sdManager->SetVerboseLevel(2);

    EnergyTimeSD* LSET= new EnergyTimeSD("LSET");
    CDLog->SetSensitiveDetector(LSET);
    sdManager->AddNewDetector(LSET);
    
    EnergyTimeSD* AcrylicET= new EnergyTimeSD("AcrylicET");
    AcrylicLog->SetSensitiveDetector(AcrylicET);
    sdManager->AddNewDetector(AcrylicET);

    EnergyTimeSD* WaterET= new EnergyTimeSD("WaterET");
    WaterLog->SetSensitiveDetector(WaterET);
    sdManager->AddNewDetector(WaterET);

    EnergyTimeSD* DetectorET = new EnergyTimeSD("IdealDetector");
    detectorLog->SetSensitiveDetector(DetectorET);
    sdManager->AddNewDetector(DetectorET);
}
