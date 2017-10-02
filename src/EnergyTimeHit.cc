#include "EnergyTimeHit.hh"
#include <G4SystemOfUnits.hh>

G4ThreadLocal G4Allocator<EnergyTimeHit>* hitAllocator = nullptr;

void EnergyTimeHit::Print()
{
    G4cout << "Hit in Volume: " << fPosVolume
           << "   time [s]: " << fPostStepTime/s
           << "   position [mm]: " <<  fPostPosition/mm << G4endl;
}
