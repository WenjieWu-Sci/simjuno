/**
 * \class DsPhysConsHadron
 *
 * \brief Hadron production physics
 *
 * 
 *
 *
 *
 * bv@bnl.gov Wed Apr 16 11:44:11 2008
 *
 */



#ifndef DSPHYSCONSHADRON_H
#define DSPHYSCONSHADRON_H

#include "G4VPhysicsConstructor.hh"

class DsPhysConsHadron : public G4VPhysicsConstructor
{

public:

    DsPhysConsHadron(const G4String& name = "hadron");
    virtual ~DsPhysConsHadron();

    // Interface methods
    void ConstructParticle();
    void ConstructProcess();

private:

    /// MinEnergyForMultiFrag: Minimum energy for multi-fragmentation
    double m_minEnergyForMultiFrag;

    /// MaxEnergyPreEquilProton: Maximum energy for pre-equilibrium
    /// proton
    double m_maxEnergyPreEquilProton;

    /// MinEnergyPreEquilNeutron: Minimum energy for pre-equilibrium
    /// neutron
    double m_minEnergyPreEquilNeutron;

    /// MaxEnergyPreEquilNeutron: Maximum energy for pre-equilibrium
    /// neutron
    double m_maxEnergyPreEquilNeutron;

    /// MinEnergyHEModel: Minimum energy for high-energy mode
    double m_minEnergyHEModel;

    /// MaxEnergyHEModel: Maximum energy for high-energy mode
    double m_maxEnergyHEModel;

    /// LEPUpperLimit: Low-energy parametrized model upper limit
    double m_lepUpperLimit;

    /// LEPpnpiLimit: Low-energy parametrized model pnpi limit
    double m_lepPnpiLimit;

    /// MinEnergyBinaryCascadePN: Minimum energy for p,n low energy
    /// binary cascade
    double m_minEnergyBinaryCascadePN;

    /// MaxEnergyBinaryCascadePN: Maximum energy for p,n low energy
    /// binary cascade
    double m_maxEnergyBinaryCascadePN;

    /// MinEnergyBinaryCascadePi: Minimum energy for pion low energy
    /// binary cascade
    double m_minEnergyBinaryCascadePi;

    /// MaxEnergyBinaryCascadePi: Maximum energy for pion low energy
    /// binary cascade
    double m_maxEnergyBinaryCascadePi;

    /// NeutronElasticEnergyBoundary: Energy boundary between simple
    /// low energy and precision high energy elastic models
    double m_neutronElasticEnergyBoundary;

    /// NeutronInelasticEnergyBoundary: Energy boundary between simple
    /// low energy and precision high energy inelastic models
    double m_neutronInlasticEnergyBoundary;

    /// FissionEnergyBoundary: Energy boundary between simple low
    /// energy and precision high energy fission models
    double m_fissionEnergyBoundary;

    /// CaptureEnergyBoundary: Energy boundary between simple low
    /// energy and precision high energy capture models
    double m_captureEnergyBoundary;
    
};

#endif  // DSPHYSCONSHADRON_H
