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
    messenger= new AnalysisManagerMessenger(this);
    m_filename= "test.root";
}

AnalysisManager::~AnalysisManager() {;}

void AnalysisManager::bookEvtTree() {
    evt= new TTree("evt", "evtTreeInfo");
    evt->Branch("evtID", &evtID, "evtID/I");
    evt->Branch("nPhotons", &nPhotons, "nPhotons/I");
    evt->Branch("detX", detX, "detX[nPhotons]/D");
    evt->Branch("detY", detY, "detY[nPhotons]/D");
    evt->Branch("detZ", detZ, "detZ[nPhotons]/D");
    evt->Branch("hitTime", HitTime, "hitTime[nPhotons]/D");
    evt->Branch("PID", PID, "PID[nPhotons]/I");
    evt->Branch("TID", TID, "TID[nPhotons]/I");
    evt->Branch("isScintillation", isScintillation, "isScintillation[nPhotons]/I");
    evt->Branch("isCerenkov", isCerenkov, "isCerenkov[nPhotons]/I");
    evt->Branch("isReemission", isReemission, "isReemission[nPhotons]/I");
//    evt->Branch("ProcessStatus", ProcessStatus, "ProcessStatus[nPhotons]/I");
    evt->Branch("nRayScattering", nRayScattering, "nRayScattering[nPhotons]/I");
}

void AnalysisManager::BeginOfRun() {
    G4cout << "TTree is booked and the run has been started" << G4endl;
    if (thefile) {
        delete thefile;
    }
    thefile= new TFile(m_filename, "RECREATE");
    bookEvtTree();
}

void AnalysisManager::EndOfRun() {
    evt->Write();
    thefile->Close();
}

void AnalysisManager::BeginOfEvent() {
    nPhotons= 0;
    for (G4int i= 0; i< 200000; ++i) {
        HitTime[i]= 0;
        PID[i]= -1;
        TID[i]= -1;
        isScintillation[i]= 0;
        isCerenkov[i]= 0;
        isReemission[i]= 0;
//        ProcessStatus[i]= 0;
        nRayScattering[i]= 0;
    }
}

void AnalysisManager::EndOfEvent(const G4Event* event) {
    // Branch: evtID
    evtID= event->GetEventID();

    G4SDManager* sdm = G4SDManager::GetSDMpointer();
    // Get the hit collections
    G4HCofThisEvent* hcofEvent = event->GetHCofThisEvent(); 
    // If there is no hit collection, there is nothing to be done
    if(!hcofEvent) return;
    if (fLSETId< 0) {
        fLSETId= sdm->GetCollectionID("LSET/energy_time");
        G4cout << "EventAction: central detector SD ID: " << fLSETId << G4endl;
    }
    if (fAcrylicETId < 0) {
        fAcrylicETId= sdm->GetCollectionID("AcrylicET/energy_time");
        G4cout << "EventAction: Acrylic ball SD ID: " << fAcrylicETId << G4endl;
    }
    if (fWaterETId < 0) {
        fWaterETId= sdm->GetCollectionID("WaterET/energy_time");
        G4cout << "EventAction: Water tank SD ID: " << fWaterETId << G4endl;
    }
    // Hit collections IDs to be looped over ("Don't Repeat Yourself" principle)
    std::vector<G4int> hitCollectionIds= { fLSETId, fAcrylicETId, fWaterETId };
    std::vector<G4int> OPTID;
    for (G4int collectionId : hitCollectionIds) {
        if (collectionId == -1) continue;
        // Get and cast hit collection with EnergyTimeHits
        EnergyTimeHitsCollection* hitCollection= dynamic_cast<EnergyTimeHitsCollection*>(hcofEvent->GetHC(collectionId));
        if (!hitCollection) continue;

        // Branch: nPhotons, HitTime, isScintillation, isCerenkov, isReemission
        // Branch: ProcessStatus, nRayScattering
        for (auto hit: *hitCollection->GetVector()) {
            if (hit->GetParticle()==20022 && hit->GetBoundaryProcess() && hit->GetTrackStatus()==2 &&
                hit->GetBoundaryProcessStatus()==10 && hit->GetProcessName()=="Transportation") {
                G4int tmp_nRayScattering= 0;
//                G4int StraightTag= 0;
                nPhotons++;
                detX[nPhotons-1]= hit->GetPostPosition().getX();
                detY[nPhotons-1]= hit->GetPostPosition().getY();
                detZ[nPhotons-1]= hit->GetPostPosition().getZ();
                HitTime[nPhotons-1]= hit->GetPostStepTime();
                PID[nPhotons-1]= hit->GetPID();
                TID[nPhotons-1]= hit->GetTID();
//                ProcessStatus[nPhotons-1]= hit->GetProcessName();
                for (G4int id : hitCollectionIds) {
                    EnergyTimeHitsCollection* hitCol= dynamic_cast<EnergyTimeHitsCollection*>(hcofEvent->GetHC(id));
                    for (auto hitprime: *hitCol->GetVector()) {
                        // select the same particle using TID
                        if (hitprime->GetTID() == hit->GetTID()) {
                            if (hitprime->GetProcessName()=="OpRayleigh") {
                                tmp_nRayScattering++;
                            }
                            // select the first step to get their creator process
                            if (hitprime->GetStepNo() == 1) {
                                if (hitprime->GetCreatorProcess()=="Scintillation") {
                                    isScintillation[nPhotons-1]= 1;
                                }
                                if (hitprime->GetCreatorProcess()=="Cerenkov") {
                                    isCerenkov[nPhotons-1]= 1;
                                }
                                if (hitprime->GetCreatorProcess()=="OpWLS") {
                                    isReemission[nPhotons-1]= 1;
                                }
                            }
                        }
                    }
                }
                nRayScattering[nPhotons-1]= tmp_nRayScattering;
            }
//            nPhotons+= hit->IsOpticalPhoton();
            /*
            isScintillation= hit->IsScintillation();
            isCerenkov= hit->IsCerenkov();
            if (hit->GetOPTID()> 0) OPTID.push_back(hit->GetOPTID());
            if (hit->GetPosVolume() == "world") {
                G4bool TagStraight= true;
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
            */
        }
    }

    evt->Fill();
}
