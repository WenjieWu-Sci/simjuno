#include "AnalysisManager.hh"
#include "EnergyTimeSD.hh"

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
    evt->Branch("EventID", &evtID, "EventID/I");
    evt->Branch("nPhotons", &nPhotons, "nPhotons/I");
    evt->Branch("nRayleigh", nRayleigh, "nRayleigh[nPhotons]/I");
    evt->Branch("TID_Det",TID_Det,"TID_Det[nPhotons]/I");
    evt->Branch("Time_Det", Time_Det, "Time_Det[nPhotons]/D");
    evt->Branch("X_Det", X_Det, "X_Det[nPhotons]/D");
    evt->Branch("Y_Det", Y_Det, "Y_Det[nPhotons]/D");
    evt->Branch("Z_Det", Z_Det, "Z_Det[nPhotons]/D");
    evt->Branch("isCerenkov", isCerenkov, "isCerenkov[nPhotons]/I");
    evt->Branch("isScintillation", isScintillation, "isScintillation[nPhotons]/I");
    evt->Branch("isReemission", isReemission, "isReemission[nPhotons]/I");
    evt->Branch("X_Init", X_Init, "X_Init[nPhotons]/D");
    evt->Branch("Y_Init", Y_Init, "Y_Init[nPhotons]/D");
    evt->Branch("Z_Init", Z_Init, "Z_Init[nPhotons]/D");
    evt->Branch("Px_Init", Px_Init, "Px_Init[nPhotons]/D");
    evt->Branch("Py_Init", Py_Init, "Py_Init[nPhotons]/D");
    evt->Branch("Pz_Init", Pz_Init, "Pz_Init[nPhotons]/D");
    evt->Branch("E_Init",E_Init,"E_init[nPhotons]/D");
    evt->Branch("PID", PID, "PID[nPhotons]/I");
}

void AnalysisManager::BeginOfRun() {
    G4cout << "TTree is booked and the run has been started" << G4endl;
    if (thefile) {
        delete thefile;
    }
    if(!AllDetected.empty())
        AllDetected.clear();
    thefile= new TFile(m_filename, "RECREATE");
    bookEvtTree();
}

void AnalysisManager::EndOfRun() {
    evt->Write();
    thefile->Close();
}

void AnalysisManager::BeginOfEvent(const G4Event* event) {
    evtID = event->GetEventID();
    nPhotons= 0;
    for (G4int i= 0; i< 200000; ++i) {
        nRayleigh[i] =0;
        TID_Det[i] = -1;
        Time_Det[i] = 0.;
        X_Det[i] = 0.;
        Y_Det[i] = 0.;
        Z_Det[i] = 0.;
        X_Init[i] = 0.;
        Y_Init[i] = 0.;
        Z_Init[i] = 0.;
        Px_Init[i] = 0.;
        Py_Init[i] = 0.;
        Pz_Init[i] = 0.;
        E_Init[i] = 0.;
        PID[i]= -1;
        isCerenkov[i] = -1;
        isScintillation[i]= -1;
        isReemission[i]= -1;
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
    for (std::vector<G4int>::iterator collectionId = hitCollectionIds.begin();
         collectionId != hitCollectionIds.end(); ++collectionId) {
        if (*collectionId == -1) continue;
        // Get and cast hit collection with EnergyTimeHits
        EnergyTimeHitsCollection* hitCollection= dynamic_cast<EnergyTimeHitsCollection*>(hcofEvent->GetHC(*collectionId));
        if (!hitCollection) continue;

        // Branch: nPhotons, HitTime, isScintillation, isCerenkov, isReemission
        // Branch: ProcessStatus, nRayScattering
        std::vector<EnergyTimeHit*> tmp_hitCol = *hitCollection->GetVector();
        for (std::vector<EnergyTimeHit*>::iterator hit = tmp_hitCol.begin();
             hit != tmp_hitCol.end(); ++hit) {
            if ((*hit)->GetParticle()==20022 && (*hit)->GetBoundaryProcess() && (*hit)->GetTrackStatus()==2 &&
                    (*hit)->GetBoundaryProcessStatus()==10 && (*hit)->GetProcessName()=="Transportation") {
                G4int tmp_nRayScattering= 0;
                nPhotons++;
                if(nPhotons > 0){
                    EnergyTimeHit* tmp_EnergyTimeHit = (*hit)->Clone();
                    AllDetected.push_back(tmp_EnergyTimeHit);
                    X_Det[nPhotons-1]= (*hit)->GetPostPosition().getX();
                    Y_Det[nPhotons-1]= (*hit)->GetPostPosition().getY();
                    Z_Det[nPhotons-1]= (*hit)->GetPostPosition().getZ();
                    Time_Det[nPhotons-1]= (*hit)->GetPostStepTime();
                    PID[nPhotons-1]= (*hit)->GetPID();
                    TID_Det[nPhotons-1]= (*hit)->GetTID();
                    for (std::vector<G4int>::iterator id = hitCollectionIds.begin();
                         id != hitCollectionIds.end(); ++id) {
                        EnergyTimeHitsCollection* hitCol= dynamic_cast<EnergyTimeHitsCollection*>(hcofEvent->GetHC(*id));
                        std::vector<EnergyTimeHit*> tmp_hitCol_cmp = *hitCol->GetVector();
                        for (std::vector<EnergyTimeHit*>::iterator hitprime = tmp_hitCol_cmp.begin();
                             hitprime != tmp_hitCol_cmp.end(); ++hitprime) {
                            // select the same particle using TID
                            if ((*hitprime)->GetTID() == (*hit)->GetTID()) {
                                if ((*hitprime)->GetProcessName()=="OpRayleigh") {
                                    tmp_nRayScattering++;
                                }
                                // select the first step to get their creator process
                                if ((*hitprime)->GetStepNo() == 1) {
                                    if ((*hitprime)->GetCreatorProcess()=="Scintillation") {
                                        isScintillation[nPhotons-1]= 1;
                                    }
                                    if ((*hitprime)->GetCreatorProcess()=="Cerenkov") {
                                        isCerenkov[nPhotons-1]= 1;
                                    }
                                    if ((*hitprime)->GetCreatorProcess()=="OpWLS") {
                                        isReemission[nPhotons-1]= 1;
                                    }
                                }
                            }
                        }
                    }
                    nRayleigh[nPhotons-1]= tmp_nRayScattering;
                    G4PrimaryVertex* primVertex = event->GetPrimaryVertex();
                    G4PrimaryParticle* primPart = primVertex->GetPrimary();
                    E_Init[nPhotons-1] = primPart->GetTotalEnergy();

                    X_Init[nPhotons-1] = primVertex->GetX0();
                    Y_Init[nPhotons-1] = primVertex->GetY0();
                    Z_Init[nPhotons-1] = primVertex->GetZ0();
                    Px_Init[nPhotons-1] = primPart->GetMomentum().x();
                    Py_Init[nPhotons-1] = primPart->GetMomentum().y();
                    Pz_Init[nPhotons-1] = primPart->GetMomentum().z();
                }
            }
        }
    }
    evt->Fill();
}
