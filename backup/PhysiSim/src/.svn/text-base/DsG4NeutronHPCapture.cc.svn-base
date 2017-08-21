//--------------------------------------------------------------------------
//                           neutron capture model         
//                                                               
//Modified class from original G4NeutronHPCapture class to include 
//the gammas spectrum of radiative neutron capture by Gadolinium
//--------------------------------------------------------------------------
// Author: Liang Zhan, 2006/01/27
// Modified: David Jaffe 2006/07/28 increment counters for all neutron
//                                 capture, not just Gd and H.
// Modified: bv@bnl.gov 2008/4/16 for DetSim
// Modified: djaffe@bnl.gov 2009/05/22 Several mods
//                      1) avoid zero and very low energy gammas
//                      2) require at least 1 gamma
//                      3) require correct total gamma energy for nC captures
//                      4) clean-up of messaging
//                      5) targetA is now number of nucleons (GetN), not number of moles (GetA)
//--------------------------------------------------------------------------

#include "DsG4NeutronHPCapture.h"
#include "G4NeutronHPCaptureFS.hh"
#include "G4NeutronHPDeExGammas.hh"
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"
#include "G4NeutronHPChannel.hh"

// the final state of neutron captured by Gd
#include "DsG4GdNeutronHPCaptureFS.h"
#include "DsG4NNDCNeutronHPCaptureFS.h"

#include <vector>

///////////////////////////////////////////////////////////////////////////

DsG4NeutronHPCapture::DsG4NeutronHPCapture()
{
  DebugMe = false;
  if (DebugMe) G4cout  << "Begin DsG4NeutronCapture constructor " << G4endl;

  SetMinEnergy( 0.0 );
  SetMaxEnergy( 20.*MeV );
  
  char* envstr = getenv("G4NEUTRONHPDATA");

  if(!envstr) {
    throw G4HadronicException(__FILE__, __LINE__, 
			      "Please setenv G4NEUTRONHPDATA "
			      "to point to the neutron cross-section files.");
  }
  G4String tString = "/Capture/";
  dirName = envstr;
  dirName = dirName + tString;
  numEle = G4Element::GetNumberOfElements();

  G4cout << "Initializing DsG4NeutronCapture for " << numEle << " neutron HP channels" << G4endl;
  
  theCapture = new G4NeutronHPChannel[numEle];

  G4NeutronHPCaptureFS * theFS = new G4NeutronHPCaptureFS; 
  for (G4int i=0; i<numEle; i++) {
    
    if (DebugMe) G4cout << "initializing theCapture "<<i<<" "<< numEle
	    << " name " << (*(G4Element::GetElementTable()))[i]->GetName()
	    << G4endl; 
    // DEBUG:
    
    G4cout << "initializing theCapture "<<i<<" "<< numEle
	 << ", name " << (*(G4Element::GetElementTable()))[i]->GetName() 
	 << ", symbol " << (*(G4Element::GetElementTable()))[i]->GetSymbol() 
	 << ", z   " << (*(G4Element::GetElementTable()))[i]->GetZ() 
	 << ", n   " << (*(G4Element::GetElementTable()))[i]->GetN() 
	 << ", a   " << (*(G4Element::GetElementTable()))[i]->GetA() 
	 << ", nat " << (*(G4Element::GetElementTable()))[i]->GetNaturalAbandancesFlag() 
	 << ", Niso   " << (*(G4Element::GetElementTable()))[i]->GetNumberOfIsotopes() 
	 << G4endl;

    // Cast Z to nearest integer
    int elemZ = (int)((*(G4Element::GetElementTable()))[i]->GetZ() + 0.5);

    // To use new NNDC Gd Capture Gammas, change this to true
    // To use old Gd Capture Gammas from nuclear data tables (gdcap_spec.root),
    // but generated with an unbiased sampling method (Doc-5750), also need to change this to true
    // (see 'useOldNdtGdSpectra' in DsG4NNDCCaptureGammas.cc for more info)
    bool useNNDC_GdCapture = true; 

    if(elemZ == 64 && !useNNDC_GdCapture) { // Gd.
      // for Gd, DsG4GdNeutronHPCaptureFS is invoked.
      DsG4GdNeutronHPCaptureFS * theGdFS = new DsG4GdNeutronHPCaptureFS;
      theCapture[i].Init((*(G4Element::GetElementTable()))[i], dirName);
      if (DebugMe) G4cout << (*(G4Element::GetElementTable()))[i]->GetName() << G4endl;
      theCapture[i].Register(theGdFS);
      delete theGdFS;
    }
    else if(elemZ == 6 /*C*/
 	    || elemZ == 7 /*N*/
 	    || elemZ == 8 /*O*/
 	    || elemZ == 14 /*Si*/
 	    || elemZ == 15 /*P*/
 	    || elemZ == 16 /*S*/
	    || elemZ == 24 /*Cr*/
            || elemZ == 25 /*Mn*/
	    || elemZ == 26 /*Fe*/
	    || elemZ == 28 /*Ni*/
	    || (elemZ == 64 && useNNDC_GdCapture) /*Gd*/){
      // For these elements, we use hand-generated tables of correlated gammas.
      // These tables ensure conservation of energy
      theCapture[i].Init((*(G4Element::GetElementTable()))[i], dirName);
      DsG4NNDCNeutronHPCaptureFS * theNNDCFS = new DsG4NNDCNeutronHPCaptureFS();
      theCapture[i].Register(theNNDCFS);
      delete theNNDCFS;
    }
    else { 
      theCapture[i].Init((*(G4Element::GetElementTable()))[i], dirName);
      theCapture[i].Register(theFS);
    }
  }
  delete theFS;
}
  
DsG4NeutronHPCapture::~DsG4NeutronHPCapture()
{
  delete [] theCapture;
}
  
#include "G4NeutronHPThermalBoost.hh"

G4HadFinalState * DsG4NeutronHPCapture::ApplyYourself(const G4HadProjectile& aTrack, 
                                                      G4Nucleus& )
{
  result = new G4HadFinalState(); 

  // Initialize
  G4int gammaNum = 0; 
  std::vector<G4double> capGammaE; 
  G4double capTime = 0; 
  G4double capGammaEsum = 0;
  
  //if(getenv("NeutronHPCapture")) 
  if ( DebugMe ) {G4cout <<" ### DsG4NeutronHPCapture called"<< G4endl;} 

  // get cross-sections for elements in current material
  const G4Material * theMaterial = aTrack.GetMaterial();
  G4int n = theMaterial->GetNumberOfElements();
  G4int index = theMaterial->GetElement(0)->GetIndex();
  if(n!=1) {
    xSec = new G4double[n];
    G4double sum=0;
    G4int i;
    const G4double * NumAtomsPerVolume = theMaterial->GetVecNbOfAtomsPerVolume();
    G4double rWeight;    
    G4NeutronHPThermalBoost aThermalE;
    for (i=0; i<n; i++) {
      index = theMaterial->GetElement(i)->GetIndex();
      rWeight = NumAtomsPerVolume[i];
      xSec[i] = theCapture[index].GetXsec(
					  aThermalE.GetThermalEnergy(aTrack,
								     theMaterial->GetElement(i),
								     theMaterial->GetTemperature()));

      xSec[i] *= rWeight;
      sum+=xSec[i];
    }
    
    // determine the target nucleus
    G4double random = G4UniformRand();
    G4double running = 0;
    for (i=0; i<n; i++) {
      running += xSec[i];
      index = theMaterial->GetElement(i)->GetIndex();
      if(random<=running/sum) break;
    }
    if(i==n) i=std::max(0, n-1);
    delete [] xSec;
  }

  capTime = aTrack.GetGlobalTime()/(1000*ns);
  
  G4String targetname = (*(G4Element::GetElementTable()))[index]->GetName();
  G4double targetZ = (*(G4Element::GetElementTable()))[index]->GetZ();
  G4double targetA = (*(G4Element::GetElementTable()))[index]->GetN(); 
  
  result = new G4HadFinalState();

  // Allow up to 100 tries to get physically meaningful capture gamma energy and number of gammas
  G4int tries = 100;  
  G4bool done = false;  
  while (!done) { 

    gammaNum = 0; 
    capGammaEsum = 0;

    result = theCapture[index].ApplyYourself(aTrack);
      
    G4int num = result->GetNumberOfSecondaries();

    if (DebugMe) G4cout << "DDEBUG: number of secondaries: " << num << G4endl;
      
    G4String secname;
    G4double seckine;
    for(int ii=0;ii<num;ii++) {
      secname=(result->GetSecondary(ii))->GetParticle()->GetDefinition()->GetParticleName();
      seckine=(result->GetSecondary(ii))->GetParticle()->GetKineticEnergy()/MeV;  

      if (DebugMe) G4cout << "   DDEBUG   name: " << secname << G4endl;	
      // Attention: the recoiling target is one of the secondaries.
      if(secname == "gamma") {
	gammaNum++;
	capGammaE.push_back( seckine );
      }
      if(secname == "gamma") {
	capGammaEsum += seckine;
      }    
    }//end of loop over secondaries
      
    // djaffe: decide if gammas are physically reasonable
      //         Captures on H and Gd give valid results.
      //         Enforce # of gammas and total energy for captures on carbon.
      //         For captures on other nuclei, just avoid zero or very small gamma energy.
      //         This needs to be fixed in the future.
      int iz = (int)(targetZ + 0.5); // convert to integer

      switch (iz) {
      case 1: // hydrogen
	done = true ; // nH always OK
	break;
      case 64: // Gd
	done = true ; // nGd always OK
	break;
	//case 6: // carbon
	// 	done = ((gammaNum == 1) || (gammaNum == 2)) && std::abs(capGammaEsum-4.946*MeV)<0.1*MeV ;
	//	break;
      default: // everything else
	if ( capGammaEsum > 0.01*MeV ) {
	  G4bool zero = false;
	  for (int ii=0; ii<gammaNum; ii++) { if (capGammaE[ii] < 0.001*MeV) zero = true; }
	  done = !zero;
	}
	break;
      }
      --tries; // don't try forever
      if (tries == 0)	{
	done = true; 
	G4cout << " DsG4NeutronHPCapture: GIVING UP. Could not achieve acceptable final state gammas  " << G4endl;
	G4cout << " DsG4NeutronHPCapture: Z,A " <<  targetZ <<","<<targetA
		 <<" "<<targetname << " N(gamma)="
		 << gammaNum << " E(gamma)= " ;                             
	for (int ii=0;ii<gammaNum;ii++){ G4cout << capGammaE[ii] <<", " ;} 
	G4cout << G4endl; 
      }
    } // !done
    
    
    /* recording the capture information --- Wei Wang, Aug 14, 2008 */
    
    return result; 
}

