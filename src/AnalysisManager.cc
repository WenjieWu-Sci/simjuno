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
    evt->Branch("EventID", &evtID, "EventID/I");
    evt->Branch("nPhotons", &nPhotons, "nPhotons/I");
    evt->Branch("nScintillation", &nScintillation, "nScintillation/I");
    evt->Branch("nCerenkov", &nCerenkov, "nCerenkov/I");
    evt->Branch("nStraight", &nStraight, "nStraight/I");
    evt->Branch("TimeStraight", TimeStraight, "TimeStraight[nStraight]/D");
    evt->Branch("nDetected",&nDetected,"nDetected/I");
    evt->Branch("nRayleigh", nRayleigh, "nRayleigh[nDetected]/I");
    evt->Branch("TID_Det",TID_Det,"TID_Det[nDetected]/I");
    evt->Branch("Time_Det", Time_Det, "Time_Det[nDetected]/D");
    evt->Branch("X_Det", X_Det, "X_Det[nDetected]/D");
    evt->Branch("Y_Det", Y_Det, "Y_Det[nDetected]/D");
    evt->Branch("Z_Det", Z_Det, "Z_Det[nDetected]/D");
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

void AnalysisManager::BeginOfEvent(const G4Event* event) {
    evtID = event->GetEventID();
    nPhotons= 0;
    nScintillation= 0;
    nCerenkov= 0;
    nStraight= 0;
    nDetected =0;
    for (G4int i= 0; i< 200000; ++i) {
        TimeStraight[i]= 0;
        nRayleigh[i] =0;
        TID_Det[i] = -1;
        Time_Det[i] = 0.;
    }
}

void AnalysisManager::EndOfEvent(const G4Event* event) {
    G4int NumScatter(0);
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
    if(fDetectorETId < 0) {
        fDetectorETId = sdm->GetCollectionID("IdealDetector/energy_time");
        G4cout << "EventAction: Ideal Detector energy_time scorer ID: " << fDetectorETId << G4endl;
    }

    // Hit collections IDs to be looped over ("Don't Repeat Yourself" principle)
    std::vector<G4int> hitCollectionIds= { fLSETId, fAcrylicETId, fWaterETId, fDetectorETId };
    std::vector<G4int> OPTID;
//    std::vector<G4int> OPTID_Det;
    for (std::vector<G4int>::iterator collectionId = hitCollectionIds.begin();
         collectionId != hitCollectionIds.end(); ++collectionId) {
        if (*collectionId == -1) continue;
        // Get and cast hit collection with EnergyTimeHits
        EnergyTimeHitsCollection* hitCollection= dynamic_cast<EnergyTimeHitsCollection*>(hcofEvent->GetHC(*collectionId));
        if (!hitCollection) continue;

        std::vector<EnergyTimeHit*> tmp_hitCol = *hitCollection->GetVector();
        for (std::vector<EnergyTimeHit*>::iterator hit = tmp_hitCol.begin();
             hit != tmp_hitCol.end(); ++hit) {
            nScintillation+= ((*hit))->IsScintillation();
            nCerenkov+= (*hit)->IsCerenkov();
            nPhotons+= (*hit)->IsOpticalPhoton();
            if ((*hit)->GetOPTID()> 0) {
                OPTID.push_back((*hit)->GetOPTID());
            }
            //G4bool IsNew = (std::find(OPTID_Det.begin(),OPTID_Det.end(),(*hit)->GetTID())==OPTID_Det.end());
            //G4cout << "Track " << (*hit)->GetTID() << " IsNew is " << IsNew <<" StepNo " << (*hit)->GetStepNo() << " Volume " << *collectionId <<" " << (*hit)->GetPosVolume() << G4endl;
            // find the existence of the track id
            if ((*hit)->GetPosVolume() == "Detector" && (*hit)->GetProcessName() == "OpAbsorption") {
//                if ((*hit)->GetParticleID()==0){
//                    OPTID_Det.push_back((*hit)->GetTID());
//                }
                nDetected+= ((*hit)->GetParticleID()==0?1:0);
                G4bool TagStraight= true;
                for (std::vector<G4int>::iterator id = hitCollectionIds.begin();
                     id != hitCollectionIds.end(); ++id) {
                    EnergyTimeHitsCollection* hitCol= dynamic_cast<EnergyTimeHitsCollection*>(hcofEvent->GetHC(*id));

                    std::vector<EnergyTimeHit*> tmp_hitCol_cmp = *hitCol->GetVector();
                    for (std::vector<EnergyTimeHit*>::iterator hitprime = tmp_hitCol_cmp.begin();
                         hitprime != tmp_hitCol_cmp.end(); ++hitprime) {
                        if ((*hitprime)->GetTID() == (*hit)->GetTID()) {
                            if ((*hitprime)->GetProcessName() == "OpRayleigh") {
                                TagStraight= false;
                                NumScatter++;
                                //break;
                            }
                        }
                    }
                    //if (!TagStraight)
                    //    break;
                }
                if (TagStraight){
                    nStraight++;
                    if(nStraight>0)
                        TimeStraight[nStraight-1]=(*hit)->GetTime();
                }
                //G4cout << "Num of scattering for " << (*hit)->GetTID() << " is " << NumScatter << G4endl;
                if(nDetected>0) {
                    TID_Det[nDetected-1]=(*hit)->GetTID();
                    nRayleigh[nDetected-1]=NumScatter;
                    Time_Det[nDetected-1]=(*hit)->GetTime();
                    X_Det[nDetected-1]=(*hit)->GetPosition().getX();
                    Y_Det[nDetected-1]=(*hit)->GetPosition().getY();
                    Z_Det[nDetected-1]=(*hit)->GetPosition().getZ();
                }
                NumScatter=0;
            }
        }
    }

    evt->Fill();
}
