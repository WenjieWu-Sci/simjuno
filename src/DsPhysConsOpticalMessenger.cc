//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "DsPhysConsOpticalMessenger.hh"

#include "DsPhysConsOptical.h"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithABool.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DsPhysConsOpticalMessenger::
  DsPhysConsOpticalMessenger(DsPhysConsOptical* pPhys) 
  : G4UImessenger(),
    fOptical(pPhys)
{
  fOpDir = new G4UIdirectory("/Optical/");
  fOpDir->SetGuidance("Set optical process");

  fOpPhysDir = new G4UIdirectory("/Optical/phys/");
  fOpPhysDir->SetGuidance("PhysicsList control");
 
  fVerboseCmd = new G4UIcmdWithAnInteger("/Optical/phys/verbose",this);
  fVerboseCmd->SetGuidance("set verbose for physics processes");
  fVerboseCmd->SetParameterName("verbose",true);
  fVerboseCmd->SetDefaultValue(1);
  fVerboseCmd->SetRange("verbose>=0");
  fVerboseCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
 
  fTruePhysics =
           new G4UIcmdWithABool("/Optical/phys/TruePhysics",this);
  fTruePhysics->SetGuidance("set if use the true physics, false for toymodel");
  fTruePhysics->SetParameterName("TruePhysics",true);
  fTruePhysics->SetDefaultValue(true);
  fTruePhysics->AvailableForStates(G4State_PreInit, G4State_Idle);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DsPhysConsOpticalMessenger::~DsPhysConsOpticalMessenger()
{
  delete fVerboseCmd;
  delete fTruePhysics;
  delete fOpPhysDir;
  delete fOpDir;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DsPhysConsOpticalMessenger::SetNewValue(G4UIcommand* command,
                                               G4String newValue)
{
  if( command == fVerboseCmd )
  {
      fOptical->SetVerbose(fVerboseCmd->GetNewIntValue(newValue));
  }

  if( command == fTruePhysics )
  {
      fOptical->SetTruePhysics(fTruePhysics->GetNewBoolValue(newValue));
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
