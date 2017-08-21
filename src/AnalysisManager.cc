#include "AnalysisManager.hh"
#include "EnergyTimeSD.hh"
#include "EnergyTimeHit.hh"

#include <G4Event.hh>
#include <G4SDManager.hh>
#include <TFile.h>
#include <TTree.h>
#include <vector>

AnalysisManager* AnalysisManager::instance= 0;

AnalysisManager* AnalysisManager::GetInstance() {
    if (!instance) { 
        instance= new AnalysisManager();
    }
    return instance;
}

AnalysisManager::AnalysisManager() {
    evt= 0;
}

AnalysisManager::~AnalysisManager() {;}

void AnalysisManager::bookEvtTree() {
    evt= new TTree("evt", "evtTreeInfo");
    evt->Branch("nPhotons", &nPhotons, "nPhotons/I");
    evt->Branch("nScintillation", &nScintillation, "nScintillation/I");
    evt->Branch("nCerenkov", &nCerenkov, "nCerenkov/I");
    evt->Branch("nStraight", &nStraight, "nStraight/I");
    evt->Branch("TimeStraight", TimeStraight, "TimeStraight[nStraight]/D");
}

void AnalysisManager::BeginOfRun() {
    G4cout << "TTree is booked and the run has been started" << G4endl;
    if (thefile) {
        delete thefile;
    }
    thefile= new TFile("simjunotest.root", "RECREATE");
    bookEvtTree();
}

void AnalysisManager::EndOfRun() {
    evt->Write();
    thefile->Close();
}

void AnalysisManager::BeginOfEvent() {
    nPhotons= 0;
    nScintillation= 0;
    nCerenkov= 0;
    nStraight= 0;
    for (G4int i= 0; i< 200000; ++i) {
        TimeStraight[i]= 0;
    }
}

void AnalysisManager::EndOfEvent(const G4Event* event) {
    G4SDManager* sdm = G4SDManager::GetSDMpointer();

    // Get the hit collections
    G4HCofThisEvent* hcofEvent = event->GetHCofThisEvent(); 

    // If there is no hit collection, there is nothing to be done
    if(!hcofEvent) return;

    if (fLSETId< 0) {
        fLSETId= sdm->GetCollectionID("LSET/energy_time");
        G4cout << "EventAction: central detector energy_time scorer ID: " << fLSETId << G4endl;
    }
    if (fAcrylicETId < 0) {
        fAcrylicETId= sdm->GetCollectionID("AcrylicET/energy_time");
        G4cout << "EventAction: Acrylic ball energy_time scorer ID: " << fAcrylicETId << G4endl;
    }
    if (fWaterETId < 0) {
        fWaterETId= sdm->GetCollectionID("WaterET/energy_time");
        G4cout << "EventAction: Water tank energy_time scorer ID: " << fWaterETId << G4endl;
    }

    // Hit collections IDs to be looped over ("Don't Repeat Yourself" principle)
    std::vector<G4int> hitCollectionIds= { fLSETId, fAcrylicETId, fWaterETId };
    std::vector<G4int> OPTID;
    for (G4int collectionId : hitCollectionIds) {
        if (collectionId == -1) continue;
        // Get and cast hit collection with EnergyTimeHits
        EnergyTimeHitsCollection* hitCollection= dynamic_cast<EnergyTimeHitsCollection*>(hcofEvent->GetHC(collectionId));
        if (!hitCollection) continue;

        for (auto hit: *hitCollection->GetVector()) {
            nScintillation+= hit->IsScintillation();
            nCerenkov+= hit->IsCerenkov();
            nPhotons+= hit->IsOpticalPhoton();
            if (hit->GetOPTID()> 0) OPTID.push_back(hit->GetOPTID());
            if (hit->GetPosVolume() == "world") {
                G4bool TagStraight= true;
                for (G4int id : hitCollectionIds) {
                    EnergyTimeHitsCollection* hitCol= dynamic_cast<EnergyTimeHitsCollection*>(hcofEvent->GetHC(id));
                    for (auto hitprime: *hitCol->GetVector()) {
                        if (hitprime->GetTID() == hit->GetTID()) {
                            if (hitprime->GetProcessName() == "OpRayleigh") {
                                TagStraight= false;
                                break;
                            }
                        }
                    }
                    if (!TagStraight)
                        break;
                }
                if (TagStraight)
                    nStraight++;
            }
        }
    }

    evt->Fill();
}
