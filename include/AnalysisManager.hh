#ifndef ANALYSISMANAGER_HH
#define ANALYSISMANAGER_HH

#include "globals.hh"
#include <G4Event.hh>
#include <TFile.h>
#include <TTree.h>
#include "AnalysisManagerMessenger.hh"
#include "EnergyTimeHit.hh"

class AnalysisManager {
    public:
        AnalysisManager();
        ~AnalysisManager();
        static AnalysisManager* GetInstance();
        void bookEvtTree();
        void BeginOfRun();
        void EndOfRun();
        void BeginOfEvent(const G4Event *event);
        void EndOfEvent(const G4Event* event);
        std::vector<EnergyTimeHit*> GetEnergyTimeHitVector() {return AllDetected;}
        
    public:
        void setFileName(G4String i) { m_filename= i; }

    private:
        static AnalysisManager* instance;
        AnalysisManagerMessenger* messenger;

        TFile* thefile;
        TString m_filename;
        TTree* evt;
        G4int evtID;
        G4int nPhotons;
        G4int nRayleigh[200000];
        G4int TID_Det[200000];
        G4double Time_Det[200000];
        G4double X_Det[200000];
        G4double Y_Det[200000];
        G4double Z_Det[200000];
        G4double X_Init[200000];
        G4double Y_Init[200000];
        G4double Z_Init[200000];
        G4double Px_Init[200000];
        G4double Py_Init[200000];
        G4double Pz_Init[200000];
        G4double E_Init[200000];
        G4int isReemission[200000];
        G4int isScintillation[200000];
        G4int isCerenkov[200000];
        G4int PID[200000];


    private:
        G4int fLSETId {-1};
        G4int fAcrylicETId { -1 };
        G4int fWaterETId { -1 };

        std::vector<EnergyTimeHit*> AllDetected;
};

#endif
