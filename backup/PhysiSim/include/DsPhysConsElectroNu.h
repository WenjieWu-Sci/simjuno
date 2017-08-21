/**
 * \class DsPhysConsElectroNu
 *
 * \brief Electro Nuclear processes
 *
 * 
 *
 *
 *
 * bv@bnl.gov Wed Apr 16 11:33:27 2008
 *
 */



#ifndef DSPHYSCONSELECTRONU_H
#define DSPHYSCONSELECTRONU_H

#include "G4VPhysicsConstructor.hh"

class DsPhysConsElectroNu : public G4VPhysicsConstructor
{

public:

    DsPhysConsElectroNu(const G4String& name = "ElectroNu");
    virtual ~DsPhysConsElectroNu();

    // Interface methods
    void ConstructParticle();
    void ConstructProcess();

private:

    /// MaxGammaReactionEnergy : Maximum gamma nuclear reaction energy.
    double m_maxGammaReactionEnergy;

    /// MinFinalStateEnergy : Min energy for final state hadron production.
    double m_minFinalStateEnergy;

    /// MaxFinalStateEnergy : Max energy for final state hadron production.
    double m_maxFinalStateEnergy;

    ///
    double m_muNuclScaledFactor;

    ///
    bool m_enableMuNucl;

};


#endif  // DSPHYSCONSELECTRONU_H
