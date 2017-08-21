/**
 * \class DsPhysConsIon
 *
 * \brief Ion physics
 *
 * 
 *
 *
 *
 * bv@bnl.gov Wed Apr 16 12:11:32 2008
 *
 */



#ifndef DSPHYSCONSION_H
#define DSPHYSCONSION_H

#include "G4VPhysicsConstructor.hh"

class DsPhysConsIon : public G4VPhysicsConstructor
{

public:

    DsPhysConsIon(const G4String& name = "Ion");
    virtual ~DsPhysConsIon();

    // Interface methods
    void ConstructParticle();
    void ConstructProcess();

private:

    /// MinEnergyBinaryCascadeLN: Minimum energy for binary cascade of
    /// light nuclei
    double m_minEnergyBinaryCascadeLN;

    /// MaxEnergyBinaryCascadeLN: Maximum energy for binary cascade of
    /// light nuclei
    double m_maxEnergyBinaryCascadeLN;

    /// MinEnergyBinaryCascadeGenHe3: Minimum energy for binary
    /// cascade of generic ion and He3
    double m_minEnergyBinaryCascadeGenHe3;

    /// MaxEnergyBinaryCascadeGenHe3: Maximum energy for binary
    /// cascade of generic ion and He3
    double m_maxEnergyBinaryCascadeGenHe3;

    /// MaxEnergyInelastic: Maximum energy for inelastic processes
    double m_maxEnergyInelastic;



};


#endif  // DSPHYSCONSION_H
