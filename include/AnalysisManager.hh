#ifndef ANALYSISMANAGER_HH
#define ANALYSISMANAGER_HH

#include "globals.hh"
#include <G4Event.hh>
#include <TFile.h>
#include <TTree.h>
#include "AnalysisManagerMessenger.hh"

class AnalysisManager {
    public:
        AnalysisManager();
        ~AnalysisManager();
        static AnalysisManager* GetInstance();
        void bookEvtTree();
        void BeginOfRun();
        void EndOfRun();
        void BeginOfEvent();
        void EndOfEvent(const G4Event* event);
        
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
        G4double detX[200000];
        G4double detY[200000];
        G4double detZ[200000];
        G4double HitTime[200000];
        G4int PID[200000];
        G4int TID[200000];
        G4int isScintillation[200000];
        G4int isCerenkov[200000];
        G4int isReemission[200000];
        G4int ProcessStatus[200000];
        G4int nRayScattering[200000];

    private:
        G4int fLSETId { -1 };
        G4int fAcrylicETId { -1 };
        G4int fWaterETId { -1 };
};

#endif
