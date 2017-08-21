#ifndef EVENTACTION_HH
#define EVENTACTION_HH

#include <G4UserEventAction.hh>
#include <globals.hh>
#include <G4Accumulable.hh>

class EventAction : public G4UserEventAction
{
    public:
        EventAction();
        ~EventAction();
        void BeginOfEventAction(const G4Event* event) override;
        void EndOfEventAction(const G4Event* event) override;

        void AddOP();
        void AddCerenkovOP();
        void AddScintillatorOP();

    private:
        G4Accumulable<G4int>    fNOPs;
        G4Accumulable<G4int>    fNCerenkovOPs;
        G4Accumulable<G4int>    fNScintillatorOPs;

        // Numerical IDs for hit collections (-1 means unknown yet)
        G4int fLSETId { -1 };
        G4int fAcrylicETId { -1 };
        G4int fWaterETId { -1 };
};

#endif
