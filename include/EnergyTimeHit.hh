#ifndef ENERGYTIMEHIT_HH
#define ENERGYTIMEHIT_HH

#include <G4VHit.hh>
#include <G4THitsMap.hh>
#include <G4ThreeVector.hh>

/**
  * Custom hit class used in task 4d.
  *
  * It holds infomation about energy deposits and position/time when
  * traversing a layer.
  */
class EnergyTimeHit : public G4VHit
{
public:
    // Memory allocation and de-allocation
    inline void* operator new(size_t);
    inline void  operator delete(void*);
    virtual void Print();
    
    // setter
    void SetTrackStatus(G4int trackstatus) { fTrackStatus= trackstatus; }
    void SetParticle(G4int particle) { fParticle= particle; }
    void SetStepNo(G4int stepno) { fStepNo= stepno; }
    void SetTID(G4int tid) { fTID= tid; }
    void SetPID(G4int pid) { fPID= pid; }
    void SetPrePosition(G4ThreeVector pos) { fPrePosition = pos; }
    void SetPostPosition(G4ThreeVector pos) { fPostPosition = pos; }
    void SetCreatorProcess(G4String processname) { fCreatorProcess= processname; }
    void SetPosVolume(G4String posvol) { fPosVolume= posvol; }
    void SetProcessName(G4String processname) { fProcessName= processname; }
    void SetBoundaryProcess(G4int isBoundaryProcess) { fBoundaryProcess= isBoundaryProcess; }
    void SetBoundaryProcessStatus(G4int ProcessStatus) { fOpBoundaryProcessStatus= ProcessStatus; }
    void SetPostStepTime(G4double time) { fPostStepTime= time; }


    // getter
    G4int GetTrackStatus() const { return fTrackStatus; }
    G4int GetParticle() const { return fParticle; }
    G4int GetPID() const { return fPID; }
    G4int GetTID() const { return fTID; }
    G4int GetStepNo() const { return fStepNo; }
    G4String GetPosVolume() const { return fPosVolume; }
    G4ThreeVector GetPrePosition() const { return fPrePosition; }
    G4ThreeVector GetPostPosition() const { return fPostPosition; }
    G4String GetCreatorProcess() const { return fCreatorProcess; }
    G4String GetProcessName() const { return fProcessName; }
    G4int GetBoundaryProcess() const { return fBoundaryProcess; }
    G4int GetBoundaryProcessStatus() const { return fOpBoundaryProcessStatus; }
    G4double GetPostStepTime() const { return fPostStepTime; }

private:
    G4int fTrackStatus;
    G4int fParticle;
    G4int fPID;
    G4int fTID;
    G4int fStepNo;
    G4String fPosVolume;
    G4ThreeVector fPrePosition;
    G4ThreeVector fPostPosition;
    G4String fCreatorProcess;
    G4String fProcessName;
    G4int fBoundaryProcess;
    G4int fOpBoundaryProcessStatus;
    G4double fPostStepTime;
};

using EnergyTimeHitsCollection = G4THitsCollection<EnergyTimeHit>;

extern G4ThreadLocal G4Allocator<EnergyTimeHit> *hitAllocator;

inline void* EnergyTimeHit::operator new(size_t)
{
  if (!hitAllocator)
  {
      hitAllocator = new G4Allocator<EnergyTimeHit>;
  }
  return hitAllocator->MallocSingle();
}

inline void EnergyTimeHit::operator delete(void *aHit)
{
    if (!hitAllocator)
    {
        hitAllocator = new G4Allocator<EnergyTimeHit>;
    }
    hitAllocator->FreeSingle((EnergyTimeHit*) aHit);
}

#endif
