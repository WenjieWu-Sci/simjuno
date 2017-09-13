#include "EnergyTimeSD.hh"

#include <G4SDManager.hh>
#include <G4SystemOfUnits.hh>
#include <G4VProcess.hh>
#include "G4ProcessManager.hh"
#include "G4StepPoint.hh"

EnergyTimeSD::EnergyTimeSD(G4String name) : G4VSensitiveDetector(name) {
    collectionName.insert("energy_time");
}

G4bool EnergyTimeSD::ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist) {
    /***************************************************************************
     * Records:
     * Particle type, Parent ID, Track ID, Step No, PreStepPoint, PostStepPoint,
     * Create process, Process name, isBoundaryProcess, OpBoundaryProcessStatus
     * PostStepPointTime
    ***************************************************************************/
    G4Track* aTrack= aStep->GetTrack();
    G4int TrackStatus= aTrack->GetTrackStatus();
    G4cout << "debug (track status): " << TrackStatus << G4endl;
    G4int ParticleName= aTrack->GetParticleDefinition()->GetPDGEncoding();
    G4int PID= aTrack->GetParentID();
    G4int TID= aTrack->GetTrackID();
    G4int StepNo= aTrack->GetCurrentStepNumber();
    G4StepPoint* PreStep= aStep->GetPreStepPoint();
    G4ThreeVector PrePos= PreStep->GetPosition();
    G4StepPoint* PostStep= aStep->GetPostStepPoint();
    G4ThreeVector PostPos= PostStep->GetPosition();
    G4String CreatorProcess;
    if ( PID> 0 ) {
        CreatorProcess= aTrack->GetCreatorProcess()->GetProcessName();
    } else {
        CreatorProcess= "PrimaryParticle";
    }
    G4cout << "debug (create process): " << CreatorProcess << G4endl;
    G4String ProcessName= PostStep->GetProcessDefinedStep()->GetProcessName();
    static G4ThreadLocal G4OpBoundaryProcess* boundary= NULL;
    G4ProcessManager* pm= aTrack->GetDefinition()->GetProcessManager();
    G4int nprocesses= pm->GetProcessListLength();
    G4ProcessVector* pv= pm->GetProcessList();
    G4int isBoundaryProcess= 0;
    G4int OpBoundaryProcessStatus= -1;
    for (G4int i= 0; i< nprocesses; ++i) {
        if ((*pv)[i]->GetProcessName()=="OpBoundary") {
            isBoundaryProcess= 1;
            boundary= (G4OpBoundaryProcess*)(*pv)[i];
            OpBoundaryProcessStatus= boundary->GetStatus();
            G4cout << "debug (OpBoundaryProcess): " << boundary->GetStatus() << G4endl;
            G4cout << "StepNo: " << StepNo << " " << PrePos.getX() << " " << PostPos.getX() << G4endl;
        }
    }
    G4double PostStepTime= PostStep->GetGlobalTime();

    // extra info
    G4double edep= aStep->GetTotalEnergyDeposit();
    G4String PosVolume= PostStep->GetPhysicalVolume()->GetName();
    G4int StepStatus= PostStep->GetStepStatus();

    // Fill hit information
    EnergyTimeHit* hit = new EnergyTimeHit();
    hit->SetTrackStatus(TrackStatus);
    hit->SetParticle(ParticleName);
    hit->SetPID(PID);
    hit->SetTID(TID);
    hit->SetStepNo(StepNo);
    hit->SetPrePosition(PrePos);
    hit->SetPostPosition(PostPos);
    hit->SetCreatorProcess(CreatorProcess);
    hit->SetProcessName(ProcessName);
    hit->SetBoundaryProcess(isBoundaryProcess);
    hit->SetBoundaryProcessStatus(OpBoundaryProcessStatus);
    hit->SetPostStepTime(PostStepTime);
    fHitsCollection->insert(hit);
    return true;
}

void EnergyTimeSD::Initialize(G4HCofThisEvent* hcof) {
    fHitsCollection = new EnergyTimeHitsCollection(SensitiveDetectorName, collectionName[0]);
    if (fHitsCollectionId < 0) {
        fHitsCollectionId = G4SDManager::GetSDMpointer()->GetCollectionID(GetName() + "/" + collectionName[0]);
    }
    hcof->AddHitsCollection(fHitsCollectionId, fHitsCollection);
}
