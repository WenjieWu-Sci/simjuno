#include "EnergyTimeHit.hh"
#include <G4SystemOfUnits.hh>

G4ThreadLocal G4Allocator<EnergyTimeHit>* hitAllocator = nullptr;

void EnergyTimeHit::Print()
{
    G4cout << "Hit in Volume: " << fPosVolume
           << "   time [s]: " << fPostStepTime/s
           << "   position [mm]: " <<  fPostPosition/mm << G4endl;
}

EnergyTimeHit *EnergyTimeHit::Clone() const
{
    EnergyTimeHit *newEnergyTimeHit = new EnergyTimeHit();
    newEnergyTimeHit->fTrackStatus = fTrackStatus;
    newEnergyTimeHit->fParticle = fParticle;
    newEnergyTimeHit->fPID = fPID;
    newEnergyTimeHit->fTID = fTID;
    newEnergyTimeHit->fStepNo = fStepNo;
    newEnergyTimeHit->fPosVolume = fPosVolume;
    newEnergyTimeHit->fPrePosition = fPrePosition;
    newEnergyTimeHit->fPostPosition = fPostPosition;
    newEnergyTimeHit->fCreatorProcess = fCreatorProcess;
    newEnergyTimeHit->fProcessName = fProcessName;
    newEnergyTimeHit->fBoundaryProcess = fBoundaryProcess;
    newEnergyTimeHit->fOpBoundaryProcessStatus = fOpBoundaryProcessStatus;
    newEnergyTimeHit->fPostStepTime = fPostStepTime;
    return newEnergyTimeHit;
}
