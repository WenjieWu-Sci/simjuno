#ifndef PHYSICS_LIST_HH
#define PHYSICS_LIST_HH

#include "G4VUserPhysicsList.hh"

class G4Cerenkov;
class G4Scintillation;
class G4OpAbsorption;
class G4OpRayleigh;
class G4OpMieHG;
class G4OpBoundaryProcess;
class G4OpWLS;

class PhysicsList : public G4VUserPhysicsList
{
    public:
        PhysicsList();
        ~PhysicsList(){;};

    public:
        virtual void ConstructParticle();
        virtual void ConstructProcess();

        virtual void SetCuts();

        // these methods Construct physics processes and register them
        void ConstructDecay();
        void ConstructEM();
        void ConstructOp();

    private:
        static G4ThreadLocal G4Cerenkov* fCerenkovProcess;
        static G4ThreadLocal G4Scintillation* fScintillationProcess;
        static G4ThreadLocal G4OpAbsorption* fAbsorptionProcess;
        static G4ThreadLocal G4OpRayleigh* fRayleighScatteringProcess;
        static G4ThreadLocal G4OpMieHG* fMieHGScatteringProcess;
        static G4ThreadLocal G4OpBoundaryProcess* fBoundaryProcess;
        static G4ThreadLocal G4OpWLS* fWLSProcess;
};

#endif
