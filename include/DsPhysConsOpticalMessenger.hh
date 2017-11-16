#ifndef DsPhysConsOpticalMessenger_hh
#define DsPhysConsOpticalMessenger_hh 1

#include "globals.hh"
#include "G4UImessenger.hh"

class DsPhysConsOptical;
class G4UIdirectory;
class G4UIcmdWithAnInteger;
class G4UIcmdWithABool;

class DsPhysConsOpticalMessenger: public G4UImessenger
{
    public:
        DsPhysConsOpticalMessenger(DsPhysConsOptical*);
        virtual ~DsPhysConsOpticalMessenger();
        virtual void SetNewValue(G4UIcommand*, G4String);
    private:
        DsPhysConsOptical* fOptical;
        G4UIdirectory* fOpDir;
        G4UIdirectory* fOpPhysDir;
        G4UIcmdWithAnInteger* fVerboseCmd;
        G4UIcmdWithABool* fTruePhysics;
};

#endif
