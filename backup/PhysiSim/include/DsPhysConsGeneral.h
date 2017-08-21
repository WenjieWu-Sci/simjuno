/** DsPhysConsGeneral

    Construct general physics particles and processes.

 */

#ifndef DSPHYSCONSGENERAL_H
#define DSPHYSCONSGENERAL_H

#include "G4VPhysicsConstructor.hh"

class DsPhysConsGeneral : public G4VPhysicsConstructor
{
public:
    DsPhysConsGeneral(const G4String& name= "general");

    virtual ~DsPhysConsGeneral();

    // Interface methods
    void ConstructParticle();
    void ConstructProcess();

private:
    /// Set production range
    float m_lowProdCut, m_highProdCut;

    /// Per particle cuts
    float m_gammaCut, m_electronCut, m_positronCut;
};

#endif  // DSPHYSCONSGENERAL_H
