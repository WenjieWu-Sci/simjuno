#include "EnergyTimeSD.hh"

#include <G4SDManager.hh>
#include <G4SystemOfUnits.hh>
#include <G4VProcess.hh>

EnergyTimeSD::EnergyTimeSD(G4String name) :
  G4VSensitiveDetector(name)
{
    collectionName.insert("energy_time");
}

G4bool EnergyTimeSD::ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist) {
    G4Track* aTrack= aStep->GetTrack();
    G4int StepNo= aTrack->GetCurrentStepNumber();
    G4int TID= aTrack->GetTrackID();
    G4int PID= aTrack->GetParentID();
    G4int ParticleName= aTrack->GetParticleDefinition()->GetPDGEncoding();
    G4int OpticalPhotonTag= 0;
    G4int CerenkovTag= 0;
    G4int ScintillationTag= 0;
    G4int OPTIDTag= -1;
    if (ParticleName== 0 && PID== 1 && StepNo== 1) {
        OPTIDTag= TID;
        OpticalPhotonTag= 1;
        G4String CreatorProcess= aTrack->GetCreatorProcess()->GetProcessName();
        if (CreatorProcess== "Cerenkov") {
            CerenkovTag= 1;
        } else if (CreatorProcess== "Scintillation") {
            ScintillationTag= 1;
        }
    }
    G4StepPoint* PreStep= aStep->GetPreStepPoint();
    G4StepPoint* PostStep= aStep->GetPostStepPoint();
    G4double edep= aStep->GetTotalEnergyDeposit();
    G4double Time= PostStep->GetGlobalTime();
    G4ThreeVector Pos= PostStep->GetPosition();
    G4String PosVolume= PostStep->GetPhysicalVolume()->GetName();
    G4String ProcessName= PostStep->GetProcessDefinedStep()->GetProcessName();

    //G4cout << "DEBUG : " << ProcessName << G4endl;

    EnergyTimeHit* hit = new EnergyTimeHit();
    hit->SetStepNo(StepNo);
    hit->SetTID(TID);
    hit->SetPID(PID);
    hit->SetParticle(ParticleName);
    hit->SetOPTIDTag(OPTIDTag);
    hit->SetOpticalPhoton(OpticalPhotonTag);
    hit->SetCerenkov(CerenkovTag);
    hit->SetScintillation(ScintillationTag);
    hit->SetDeltaEnergy(edep);
    hit->SetTime(Time);
    hit->SetPosition(Pos);
    hit->SetPosVolume(PosVolume);
    hit->SetProcessName(ProcessName);
    
    fHitsCollection->insert(hit);
    return true;
}

void EnergyTimeSD::Initialize(G4HCofThisEvent* hcof) {
    fHitsCollection = new EnergyTimeHitsCollection(SensitiveDetectorName, collectionName[0]);
    if (fHitsCollectionId < 0)
    {
        fHitsCollectionId = G4SDManager::GetSDMpointer()->GetCollectionID(GetName() + "/" + collectionName[0]);
    }
    hcof->AddHitsCollection(fHitsCollectionId, fHitsCollection);
}
