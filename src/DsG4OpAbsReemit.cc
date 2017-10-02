#include "G4ios.hh"
#include "G4OpProcessSubType.hh"

#include "DsG4OpAbsReemit.h"
#include "G4PhysicalConstants.hh"

DsG4OpAbsReemit::DsG4OpAbsReemit(const G4String& label, const G4String& processName, G4ProcessType type
        )
: G4VDiscreteProcess(processName, type)
{
    SetProcessSubType(fOpWLS);

    theIntegralTable = 0;

    G4cout << GetProcessName() << " by " << label << " is created " << G4endl;

    m_label = label;
    m_label_abslen = label+"ABSLENGTH";
    m_label_reemiprob = label+"REEMISSIONPROB";
    m_label_component = label+"COMPONENT";   // maybe fast/slow
    m_label_timeconst = label+"TIMECONSTANT";// maybe fast/slow

    BuildThePhysicsTable();
}

DsG4OpAbsReemit::~DsG4OpAbsReemit()
{
    delete theIntegralTable;
}

// PostStepDoIt
// -------------
//
    G4VParticleChange*
DsG4OpAbsReemit::PostStepDoIt(const G4Track& aTrack, const G4Step& aStep)
{
    if (verboseLevel>0) {
        // G4cout << m_label << " PostStepDoIt " << G4endl;
    }

    aParticleChange.Initialize(aTrack);

    aParticleChange.ProposeTrackStatus(fStopAndKill);

    if (verboseLevel>0) {
        G4cout << "\n** Photon absorbed! by: " << m_label << " **" << G4endl;
    }

    const G4Material* aMaterial = aTrack.GetMaterial();

    G4StepPoint* pPostStepPoint = aStep.GetPostStepPoint();

    G4MaterialPropertiesTable* aMaterialPropertiesTable =
        aMaterial->GetMaterialPropertiesTable();
    if (!aMaterialPropertiesTable) {
        return G4VDiscreteProcess::PostStepDoIt(aTrack, aStep);
    }

    // re-emit or not?
    const G4MaterialPropertyVector* reemit_prob_vec =
        aMaterialPropertiesTable->GetProperty(m_label_reemiprob);
    if (!reemit_prob_vec) {
        return G4VDiscreteProcess::PostStepDoIt(aTrack, aStep);
    }

    G4double p_reemission = reemit_prob_vec->Value(aTrack.GetKineticEnergy());
    if (G4UniformRand() >= p_reemission) {
        return G4VDiscreteProcess::PostStepDoIt(aTrack, aStep);
    }

    if (verboseLevel>0) {
        G4cout << "*** will be re-emitted by: " << m_label << " **" << G4endl;
    }

    G4int NumPhotons = 1;
    aParticleChange.SetNumberOfSecondaries(NumPhotons);

    // energy and time
    G4double sampledEnergy = 0.;
    G4double deltaTime = 0.;

    G4int materialIndex = aMaterial->GetIndex();
    G4PhysicsOrderedFreeVector* WLSIntegral = 0;
    WLSIntegral =
        (G4PhysicsOrderedFreeVector*)((*theIntegralTable)(materialIndex));

    G4double CIImax = WLSIntegral->GetMaxValue();
    G4double CIIvalue = G4UniformRand()*CIImax;
    sampledEnergy = WLSIntegral->GetEnergy(CIIvalue);

    const G4MaterialPropertyVector* timeconst_vec =
        aMaterialPropertiesTable->GetProperty(m_label_timeconst);
    if (!timeconst_vec) {
        G4cout << "WARNING: can't find property " << m_label_timeconst << std::endl;
        G4cout << "WARNING: TIMECONSTANT of " << m_label << " is set to zero." << std::endl;
        // return G4VDiscreteProcess::PostStepDoIt(aTrack, aStep);
        // Maybe just set it to zero.
    } else {
        deltaTime = timeconst_vec->Value(aTrack.GetKineticEnergy());
    }

    // Generate random photon direction

    G4double cost = 1. - 2.*G4UniformRand();
    G4double sint = std::sqrt((1.-cost)*(1.+cost));

    G4double phi = twopi*G4UniformRand();
    G4double sinp = std::sin(phi);
    G4double cosp = std::cos(phi);

    G4double px = sint*cosp;
    G4double py = sint*sinp;
    G4double pz = cost;

    // Create photon momentum direction vector

    G4ParticleMomentum photonMomentum(px, py, pz);

    // Determine polarization of new photon

    G4double sx = cost*cosp;
    G4double sy = cost*sinp;
    G4double sz = -sint;

    G4ThreeVector photonPolarization(sx, sy, sz);

    G4ThreeVector perp = photonMomentum.cross(photonPolarization);

    phi = twopi*G4UniformRand();
    sinp = std::sin(phi);
    cosp = std::cos(phi);

    photonPolarization = cosp * photonPolarization + sinp * perp;

    photonPolarization = photonPolarization.unit();

    // Generate a new photon:

    G4DynamicParticle* aPhoton =
        new G4DynamicParticle(G4OpticalPhoton::OpticalPhoton(), photonMomentum);
    aPhoton->SetPolarization
        (photonPolarization.x(),
         photonPolarization.y(),
         photonPolarization.z());

    aPhoton->SetKineticEnergy(sampledEnergy);

    // Generate new G4Track object:


    G4double aSecondaryTime = (pPostStepPoint->GetGlobalTime()) + deltaTime;
    G4ThreeVector aSecondaryPosition = pPostStepPoint->GetPosition();

    G4Track* aSecondaryTrack = 
        new G4Track(aPhoton,aSecondaryTime,aSecondaryPosition);

    aSecondaryTrack->SetTouchableHandle(aTrack.GetTouchableHandle()); 
    // aSecondaryTrack->SetTouchableHandle((G4VTouchable*)0);

    aSecondaryTrack->SetParentID(aTrack.GetTrackID());

    aParticleChange.AddSecondary(aSecondaryTrack);

    return G4VDiscreteProcess::PostStepDoIt(aTrack, aStep);
}


// GetMeanFreePath
// ---------------
//
G4double DsG4OpAbsReemit::GetMeanFreePath(const G4Track& aTrack,
        G4double ,
        G4ForceCondition* )
{
    if (verboseLevel>0) {
        // G4cout << m_label << " GetMeanFreePath " << G4endl;
    }
    const G4DynamicParticle* aParticle = aTrack.GetDynamicParticle();
    const G4Material* aMaterial = aTrack.GetMaterial();

    G4double thePhotonEnergy = aParticle->GetTotalEnergy();

    G4MaterialPropertiesTable* aMaterialPropertyTable;
    G4MaterialPropertyVector* AttenuationLengthVector;

    G4double AttenuationLength = DBL_MAX;

    aMaterialPropertyTable = aMaterial->GetMaterialPropertiesTable();

    if ( aMaterialPropertyTable ) {
        AttenuationLengthVector = aMaterialPropertyTable->
            GetProperty(m_label_abslen);
        if ( AttenuationLengthVector ){
            AttenuationLength= AttenuationLengthVector->Value(thePhotonEnergy);
        }
        else {
            //             G4cout << "No WLS absorption length specified" << G4endl;
        }
    }
    else {
        //           G4cout << "No WLS absortion length specified" << G4endl;
    }

    return AttenuationLength;
}




void DsG4OpAbsReemit::BuildThePhysicsTable()
{
    if (theIntegralTable) return;

    const G4MaterialTable* theMaterialTable = 
        G4Material::GetMaterialTable();
    G4int numOfMaterials = G4Material::GetNumberOfMaterials();

    // create new physics table

    if(!theIntegralTable)theIntegralTable = new G4PhysicsTable(numOfMaterials);

    // loop for materials

    for (G4int i=0 ; i < numOfMaterials; i++)
    {
        G4PhysicsOrderedFreeVector* aPhysicsOrderedFreeVector =
            new G4PhysicsOrderedFreeVector();

        // Retrieve vector of WLS wavelength intensity for
        // the material from the material's optical properties table.

        G4Material* aMaterial = (*theMaterialTable)[i];

        G4MaterialPropertiesTable* aMaterialPropertiesTable =
            aMaterial->GetMaterialPropertiesTable();

        if (aMaterialPropertiesTable) {

            G4MaterialPropertyVector* theWLSVector = 
                aMaterialPropertiesTable->GetProperty(m_label_component);

            if (theWLSVector) {

                // Retrieve the first intensity point in vector
                // of (photon energy, intensity) pairs

                //theWLSVector->ResetIterator();
                //++(*theWLSVector);	// advance to 1st entry 

                G4double currentIN = (*theWLSVector)[0];

                if (currentIN >= 0.0) {

                    // Create first (photon energy) 

                    G4double currentPM = theWLSVector->Energy(0);

                    G4double currentCII = 0.0;

                    aPhysicsOrderedFreeVector->
                        InsertValues(currentPM , currentCII);

                    // Set previous values to current ones prior to loop

                    G4double prevPM  = currentPM;
                    G4double prevCII = currentCII;
                    G4double prevIN  = currentIN;

                    // loop over all (photon energy, intensity)
                    // pairs stored for this material

                    for (size_t ii= 1;
                            ii< theWLSVector->GetVectorLength();
                            ++i)
                    {
                        currentPM= theWLSVector->Energy(ii);
                        currentIN= (*theWLSVector)[ii];

                        currentCII = 0.5 * (prevIN + currentIN);

                        currentCII = prevCII +
                            (currentPM - prevPM) * currentCII;

                        aPhysicsOrderedFreeVector->
                            InsertValues(currentPM, currentCII);

                        prevPM  = currentPM;
                        prevCII = currentCII;
                        prevIN  = currentIN;
                    }
                }
            }
        }
        // The WLS integral for a given material
        // will be inserted in the table according to the
        // position of the material in the material table.

        theIntegralTable->insertAt(i,aPhysicsOrderedFreeVector);
    }
}
