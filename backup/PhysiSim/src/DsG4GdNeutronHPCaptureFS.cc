//------------------------------------------------------------------------
//                   Final state of neutron captured by Gadolinium            
//                            
// Modified class from original G4NeutronHPCaptureFS class to deexcite and
// add correctly the secondary to the hadronic final state.
//-------------------------------------------------------------------------
// Author: Liang Zhan, 2006/01/27
// Modified: bv@bnl.gov 2008/4/16 for DetSim
//-------------------------------------------------------------------------

#include "DsG4GdNeutronHPCaptureFS.h"

#include "G4Gamma.hh"
#include "G4ReactionProduct.hh"
#include "G4Nucleus.hh"
#include "G4PhotonEvaporation.hh"
#include "G4Fragment.hh"
#include "G4ParticleTable.hh" 
#include "G4NeutronHPDataUsed.hh"
#include "G4NucleiProperties.hh"
#include "G4IonTable.hh"
////////////////////////////////////////////////////////////////////////////////////////

DsG4GdNeutronHPCaptureFS::DsG4GdNeutronHPCaptureFS() 
{
    hasXsec = false; 
    targetMass = 0;
    //    G4cerr << "DsG4GdNeutronHPCaptureFS" << G4endl; 
}
  
DsG4GdNeutronHPCaptureFS::~DsG4GdNeutronHPCaptureFS() 
{ 
}

G4HadFinalState * DsG4GdNeutronHPCaptureFS::ApplyYourself(const G4HadProjectile & theTrack)
{
    G4int i;
    theResult.Clear();
    // prepare neutron
    G4double eKinetic = theTrack.GetKineticEnergy();
    const G4HadProjectile *incidentParticle = &theTrack;
    theNeutron = const_cast<G4ParticleDefinition *>(incidentParticle->GetDefinition()) ;
    theNeutron.SetMomentum( incidentParticle->Get4Momentum().vect() );
    theNeutron.SetKineticEnergy( eKinetic );

    // prepare target
    G4double eps = 0.0001;
    if(targetMass<500*MeV) {
        targetMass = G4NucleiProperties::GetNuclearMass(static_cast<G4int>(theBaseA+eps),
                                                        static_cast<G4int>(theBaseZ+eps))
            / G4Neutron::Neutron()->GetPDGMass();
    }
    G4ThreeVector neutronVelocity = 1./G4Neutron::Neutron()->GetPDGMass()*theNeutron.GetMomentum();
    G4double temperature = theTrack.GetMaterial()->GetTemperature();
    theTarget = aNucleus.GetBiasedThermalNucleus(targetMass, neutronVelocity, temperature);

    // go to nucleus rest system
    theNeutron.Lorentz(theNeutron, -1*theTarget);
    eKinetic = theNeutron.GetKineticEnergy();

    // dice the photons
    // get the emission gammas
    G4ReactionProductVector * thePhotons = NULL; 
    thePhotons = theFinalgammas.GetGammas();    

    // update the nucleus, calculate the target state after gamma emission.
    G4ThreeVector aCMSMomentum = theNeutron.GetMomentum()+theTarget.GetMomentum();
    G4LorentzVector p4(aCMSMomentum, theTarget.GetTotalEnergy() + theNeutron.GetTotalEnergy());
    nucleus = new G4Fragment(static_cast<G4int>(theBaseA+1), static_cast<G4int>(theBaseZ) ,p4);

    G4int nPhotons = 0;
    if(thePhotons!=NULL) nPhotons=thePhotons->size();
  
    for(i=0;i<nPhotons;i++) {
        G4ThreeVector pGamma(thePhotons->operator[](i)->GetMomentum());
        G4LorentzVector gamma(pGamma,thePhotons->operator[](i)->GetTotalEnergy());
        G4Fragment* theOne= new G4Fragment(gamma,G4Gamma::GammaDefinition());
        UpdateNucleus(theOne,thePhotons->operator[](i)->GetTotalEnergy());
    }

    theTwo = new G4DynamicParticle;
    theTwo->SetDefinition(G4ParticleTable::GetParticleTable()
               		  ->FindIon(static_cast<G4int>(theBaseZ), static_cast<G4int>(theBaseA+1), 0, static_cast<G4int>(theBaseZ)));
    theTwo->SetMomentum(nucleus->GetMomentum());

    // add them to the final state

    G4int nParticles = nPhotons;
    if(1==nPhotons) nParticles = 2;

    // back to lab system
    for(i=0; i<nPhotons; i++)
        thePhotons->operator[](i)->Lorentz(*(thePhotons->operator[](i)), theTarget);
        
    // Recoil, if only one gamma
    if (1==nPhotons) {
        G4DynamicParticle * theOne = new G4DynamicParticle;
        G4ParticleDefinition * aRecoil = G4ParticleTable::GetParticleTable()
            ->FindIon(static_cast<G4int>(theBaseZ), static_cast<G4int>(theBaseA+1), 
                      0, static_cast<G4int>(theBaseZ));
        theOne->SetDefinition(aRecoil);
    
        // Now energy; 
        // Can be done slightly better @
        G4ThreeVector aMomentum =  theTrack.Get4Momentum().vect()
            +theTarget.GetMomentum()
            -thePhotons->operator[](0)->GetMomentum();

        G4ThreeVector theMomUnit = aMomentum.unit();
        G4double aKinEnergy =  theTrack.GetKineticEnergy()
            +theTarget.GetKineticEnergy(); // gammas come from Q-value
        G4double theResMass = aRecoil->GetPDGMass();
        G4double theResE = aRecoil->GetPDGMass()+aKinEnergy;
        G4double theAbsMom = std::sqrt(theResE*theResE - theResMass*theResMass);
        G4ThreeVector theMomentum = theAbsMom*theMomUnit;
        theOne->SetMomentum(theMomentum);
        theResult.AddSecondary(theOne);     
    }else{
      //Add deexcited nucleus
      theResult.AddSecondary(theTwo);
    }

    // Now fill in the gammas.
     for(i=0; i<nPhotons; i++) {
        // back to lab system
        G4DynamicParticle * theOne = new G4DynamicParticle;
        theOne->SetDefinition(thePhotons->operator[](i)->GetDefinition());
        theOne->SetMomentum(thePhotons->operator[](i)->GetMomentum());
        theResult.AddSecondary(theOne);
        delete thePhotons->operator[](i);
    }
    delete thePhotons; 
    
    // clean up the primary neutron
    theResult.SetStatusChange(stopAndKill);
    return &theResult;
}

// for recoil, calculate the target nucleus state after gamma emission.
void DsG4GdNeutronHPCaptureFS::UpdateNucleus( const G4Fragment* gamma , G4double eGamma )
{
    G4LorentzVector p4Gamma = gamma->GetMomentum();
    G4ThreeVector pGamma(p4Gamma.vect());
  
    G4LorentzVector p4Nucleus(nucleus->GetMomentum() );
  
    G4double m1 = G4ParticleTable::GetParticleTable()->GetIonTable()
        ->GetIonMass(static_cast<G4int>(nucleus->GetZ()),
                     static_cast<G4int>(nucleus->GetA()));
    G4double m2 = nucleus->GetZ() *  G4Proton::Proton()->GetPDGMass() + 
        (nucleus->GetA()- nucleus->GetZ())*G4Neutron::Neutron()->GetPDGMass();
  
    G4double Mass = std::min(m1,m2);
  
    G4double newExcitation = p4Nucleus.mag() - Mass - eGamma;
  
    if(newExcitation < 0)
        newExcitation = 0;
  
    G4ThreeVector p3Residual(p4Nucleus.vect() - pGamma);
    G4double newEnergy = std::sqrt(p3Residual * p3Residual +
                                   (Mass + newExcitation) * (Mass + newExcitation));
    G4LorentzVector p4Residual(p3Residual, newEnergy);
  
    // Update excited nucleus parameters
  
    nucleus->SetMomentum(p4Residual);

    return;
}

void DsG4GdNeutronHPCaptureFS::Init (G4double A, G4double Z, G4String & dirName, G4String & )
{
    G4String tString = "/FS/";
    G4bool dbool;
    G4NeutronHPDataUsed aFile = theNames.GetName(static_cast<G4int>(A), static_cast<G4int>(Z), dirName, tString, dbool);
    G4String filename = aFile.GetName();
    theBaseA = A;
    theBaseZ = G4int(Z+.5);
    if(!dbool || ( Z<2.5 && ( std::abs(theBaseZ - Z)>0.0001 || 
                              std::abs(theBaseA - A)>0.0001))) {
        hasAnyData = false;
        hasFSData = false; 
        hasXsec = false;
        return;
    }
    std::ifstream theData(filename, std::ios::in);
    
    hasFSData = theFinalStatePhotons.InitMean(theData); 
    if(hasFSData) {
        targetMass = theFinalStatePhotons.GetTargetMass();
        theFinalStatePhotons.InitAngular(theData); 
        theFinalStatePhotons.InitEnergies(theData); 
    }
    theData.close();
}


