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
    
    void SetStepNo(G4int stepno) { fStepNo= stepno; }
    void SetTID(G4int tid) { fTID= tid; }
    void SetPID(G4int pid) { fPID= pid; }
    void SetParticle(G4int particle) { fParticle= particle; }
    void SetOPTIDTag(G4int i) { fOPTID= i; }
    void SetOpticalPhoton(G4int i) { fOpticalPhoton= i; }
    void SetScintillation(G4int i) { fScintillation= i; }
    void SetCerenkov(G4int i) { fCerenkov= i; }
    void SetDeltaEnergy(G4double deltaE) { fDeltaEnergy = deltaE; }
    void SetTime(G4double time) { fTime = time; }
    void SetPosition(G4ThreeVector pos) { fPosition = pos; }
    void SetPosVolume(G4String posvol) { fPosVolume= posvol; }
    void SetProcessName(G4String processname) { fProcessName= processname; }
    void SetFromCerenkov(G4int i) { fFromCerenkov = i; }

    G4int GetStepNo() const { return fStepNo; }
    G4int GetTID() const { return fTID; }
    G4int GetPID() const { return fPID; }
    G4int GetParticleID() const { return fParticle; }
    G4int GetOPTID() const { return fOPTID; }
    G4int IsOpticalPhoton() const { return fOpticalPhoton; }
    G4int IsScintillation() const { return fScintillation; }
    G4int IsCerenkov() const { return fCerenkov; }
    G4double GetDeltaEnergy() const { return fDeltaEnergy; }
    G4double GetTime() const { return fTime; }
    G4ThreeVector GetPosition() const { return fPosition; }
    G4String GetPosVolume() const { return fPosVolume; }
    G4String GetProcessName() const { return fProcessName; }
    G4int IsFromCerenkov() const { return fFromCerenkov; }

private:
    G4int fStepNo;
    G4int fTID;
    G4int fOPTID;
    G4int fOpticalPhoton;
    G4int fScintillation;
    G4int fCerenkov;
    G4int fPID;
    G4int fParticle;
    G4double fDeltaEnergy;
    G4double fTime;
    G4ThreeVector fPosition;
    G4String fPosVolume;
    G4String fProcessName;
    G4int fFromCerenkov;
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
