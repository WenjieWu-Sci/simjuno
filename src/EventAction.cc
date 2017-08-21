#include "EventAction.hh"

#include <G4SDManager.hh>
#include <G4THitsMap.hh>
#include <G4SystemOfUnits.hh>
#include <G4Event.hh>
#include <G4AccumulableManager.hh>

#include "AnalysisManager.hh"
#include "EnergyTimeHit.hh"

using namespace std;

EventAction::EventAction() : 
    G4UserEventAction(),
    fNOPs("NOPs", 0),
    fNCerenkovOPs("NCerenkovOPs", 0),
    fNScintillatorOPs("NScintillatorOPs", 0) {
    // Register created accumulables
    G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
    accumulableManager->RegisterAccumulable(fNOPs);
    accumulableManager->RegisterAccumulable(fNCerenkovOPs);
    accumulableManager->RegisterAccumulable(fNScintillatorOPs);
}

EventAction::~EventAction() {;}

void EventAction::BeginOfEventAction(const G4Event* event) {
    // Reset all accumulables to their initial values
    G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
    accumulableManager->Reset();

    AnalysisManager* ana= AnalysisManager::GetInstance();
    ana->BeginOfEvent();
}

void EventAction::EndOfEventAction(const G4Event* event) {
    G4cout << "This is the " << event->GetEventID() << "th event" << G4endl;

    //G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
    //accumulableManager->Merge();
    if (fNOPs.GetValue()) 
        G4cout << " * Produced " << fNOPs.GetValue() << " optical photons." << G4endl;
    else
        G4cout << " * No optical photons produced" << G4endl;
    if (fNCerenkovOPs.GetValue()) 
        G4cout << " * Produced " << fNCerenkovOPs.GetValue() << " cerenkov optical photons." << G4endl;
    else
        G4cout << " * No cerenkov optical photons produced" << G4endl;
    if (fNScintillatorOPs.GetValue()) 
        G4cout << " * Produced " << fNScintillatorOPs.GetValue() << " scintillator optical photons." << G4endl;
    else
        G4cout << " * No scinscintillator optical photons produced" << G4endl;

    AnalysisManager* ana= AnalysisManager::GetInstance();
    ana->EndOfEvent(event);
}

void EventAction::AddOP() {
    fNOPs+= 1;
}

void EventAction::AddCerenkovOP() {
    fNCerenkovOPs+= 1;
}

void EventAction::AddScintillatorOP() {
    fNScintillatorOPs+= 1;
}

