#include "StackingAction.hh"
#include "G4TrackStatus.hh"
#include "RunAction.hh"
#include "EventAction.hh"

#include <G4OpticalPhoton.hh>
#include <G4VProcess.hh>
#include <G4Cerenkov.hh>
#include <G4SystemOfUnits.hh>

StackingAction::StackingAction(RunAction* aRunAction, EventAction* aEventAction) :
    G4UserStackingAction(),fRunAction(aRunAction),fEventAction(aEventAction)
{;}

G4ClassificationOfNewTrack StackingAction::ClassifyNewTrack (const G4Track*
        aTrack)
{
    // If the track has energy < 1 MeV, return fKill
    //if (aTrack->GetParentID()) {
    //    if (aTrack->GetKineticEnergy() < 1 * MeV) {
    //        return fKill;
    //    }
    //}

    // Register optical photons
    if (aTrack->GetParticleDefinition() == G4OpticalPhoton::Definition()) {
        fEventAction->AddOP();
        if(aTrack->GetCreatorProcess()!=0){
            if (aTrack->GetCreatorProcess()->GetProcessName() == "Cerenkov") {
                fEventAction->AddCerenkovOP();
            } else if (aTrack->GetCreatorProcess()->GetProcessName() == "Scintillation") {
                fEventAction->AddScintillatorOP();
            }
        }
    }

    // Register only secondaries, i.e. tracks having ParentID > 0
    if (aTrack->GetParentID()) {
        fRunAction->AddSecondary(aTrack->GetParticleDefinition(),
                aTrack->GetKineticEnergy());
    }
    // Do not affect track classification. Just return what would have
    // been returned by the base class
    return G4UserStackingAction::ClassifyNewTrack(aTrack);
}
