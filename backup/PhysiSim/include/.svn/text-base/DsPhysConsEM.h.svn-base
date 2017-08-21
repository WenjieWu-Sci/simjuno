/**
 * \class DsPhysConsEM
 *
 * \brief ElectroMagentism physics
 *
 * Taken from G4dyb
 *
 *
 *
 * bv@bnl.gov Wed Apr 16 10:05:53 2008
 *
 */



#ifndef DSPHYSCONSEM_H
#define DSPHYSCONSEM_H

#include "G4VPhysicsConstructor.hh"

class DsPhysConsEM : public G4VPhysicsConstructor
{

public:

    DsPhysConsEM(const G4String& name = "EM");
    virtual ~DsPhysConsEM();

    // Interface methods
    void ConstructParticle();
    void ConstructProcess();

private:

    /// FluorCut : cut for fluorescence from photons, electrons and
    /// bremsstrahlung photons:
    double m_fluorCut;
};

#endif  // DSPHYSCONSEM_H
