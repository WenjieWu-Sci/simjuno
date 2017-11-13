#include "RunAction.hh"
#include <G4Gamma.hh>
#include <G4Electron.hh>
#include <G4OpticalPhoton.hh>
//#include <G4AccumulableManager.hh>
#include <G4SystemOfUnits.hh>

//#include "AnalysisManager.hh"

RunAction::RunAction() :
    G4UserRunAction(),
    fNGammas("NGammas", 0),
    fNElectrons("NElectrons", 0),
    fTotalTrackLength("TotalTrackLength",0.)
{
    // Register created accumulables
//    G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
//    accumulableManager->RegisterAccumulable(fNGammas);
//    accumulableManager->RegisterAccumulable(fNElectrons);
//    accumulableManager->RegisterAccumulable(fTotalTrackLength);
}


void RunAction::BeginOfRunAction(const G4Run*)
{
    // Reset all accumulables to their initial values
//    G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
//    accumulableManager->Reset();

    AnalysisManager* analysis= AnalysisManager::GetInstance();
    analysis->BeginOfRun();
}

void RunAction::EndOfRunAction(const G4Run* run) {
    
    AnalysisManager* analysis= AnalysisManager::GetInstance();
    analysis->EndOfRun();

    //retrieve the number of events produced in the run
    G4int nofEvents = run->GetNumberOfEvent();

    //do nothing, if no events were processed
    if (nofEvents == 0) return;

    // Merge accumulables
//    G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
//    accumulableManager->Merge();

    if (IsMaster()) {
        G4cout
            << "\n--------------------End of Global Run-----------------------"
            << " \n The run was " << nofEvents << " events " << G4endl;
//        if (fNGammas.GetValue())
//            G4cout << " * Produced " << fNGammas.GetValue()/((G4double)nofEvents) <<
//                " secondary gammas/event." << G4endl;
//        else
//            G4cout << " * No secondary gammas produced" << G4endl;
//        if (fNElectrons.GetValue())
//            G4cout << " * Produced " << fNElectrons.GetValue()/((G4double)nofEvents)  <<
//                " secondary electrons/event." << G4endl;
//        else
//            G4cout << " * No secondary electrons produced" << G4endl;
    }
}

RunAction::~RunAction() {;}

//void RunAction::AddSecondary(const G4ParticleDefinition* particle,
//        G4double energy)
//{
//    if (particle == G4Gamma::Definition()) {
//        fNGammas += 1;
//    }
//    else if (particle == G4Electron::Definition()) {
//        fNElectrons += 1;
//    }
//    return;
//}

//void RunAction::AddTrackLength(G4double trackLength)
//{
//    fTotalTrackLength+= trackLength;
//}
