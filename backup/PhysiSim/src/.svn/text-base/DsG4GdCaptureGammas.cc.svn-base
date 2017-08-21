//-------------------------------------------------------------------
// Emission gamma energy spectrum.  
// Based on experimental data, L.V. Groshev et al., Nucl. Data Tab. A5(1968) 1
// The sampling method is derived from DYB Geant3 simulation program.
//------------------------------------------------------------------
// Author: Liang Zhan, 2006/01/27
// Modified: bv@bnl.gov, 2008/4/16 for DetSim
//------------------------------------------------------------------

#include "DsG4GdCaptureGammas.h"
#include "Randomize.hh"
#include <TRandom.h>
#include <vector>
#include "G4Gamma.hh"
#include "TROOT.h"
#include "TFile.h"
#include "TH1F.h"
#include "TMath.h"

/////////////////////////////////////////////////////////////////////

using namespace std;
using namespace CLHEP;

DsG4GdCaptureGammas::DsG4GdCaptureGammas () 
{
    //First back up the current TDirectory. This is hard-wired, but at 
    //this point we assume that an output root file has been opened at the
    //very beginning of the run. I will try to find a prettier fix  
    //later. jianglai 05/09/2006
    TDirectory *dirKeep = gDirectory;

    // The experimental spectrum is saved in gdcap_spec.root.
    // This file should be placed in the data/ directory.
    // It will get copied to the InstallArea/${tag}/data directory when
    // the package is 'make'd.
    // The InstallArea/${tag}/data which should be linked to with the $DAYA_DATA_DIR
    // environment variable.

    std::string specfilename = "gdcap_spec.root";
    const char* prefix = getenv("DAYA_DATA_DIR");
    if(prefix) {
        if(strlen(prefix)>0) { 
            std::string newname = prefix;
            newname += "/";
            newname += specfilename;
            specfilename = newname;
        }
    }

    specfile = TFile::Open("/afs/ihep.ac.cn/soft/dayabay/NuWa-64/daily/opt/release/NuWa-trunk/dybgaudi/Database/SimData/data/gdcap_spec.root");

    if(!specfile)
        G4cout << "Can not open gdcap_spec.root. "
               << "Make sure DAYA_DATA_DIR is set to it's location." << G4endl;
    if(!(specfile->IsOpen()))
        G4cout << "Can not open gdcap_spec.root. "
               << "Make sure DAYA_DATA_DIR is set to it's location." << G4endl;

    capspec = (TH1F*)(specfile->Get("h1"));

    // return to the TDirectory used before opening TFile
    if (dirKeep) {
        dirKeep->cd();
    }  
}

DsG4GdCaptureGammas::~DsG4GdCaptureGammas () 
{
  /*
    if(specfile && specfile->IsOpen()) {
        specfile->Close();
        G4cout <<"gdcap_spec.root closed"<<G4endl;
    }
    else 
        G4cout <<"gdcap_spec.root is not closed."<<G4endl;
  */
}

G4ReactionProductVector* DsG4GdCaptureGammas::GetGammas ()
{
    G4ReactionProductVector* theGammas = new G4ReactionProductVector;
    vector<double> energy = GetEnergy();
    for(unsigned int i=0; i<energy.size(); i++) {

        G4ReactionProduct* theOne = new G4ReactionProduct;
        theOne->SetDefinition( G4Gamma::Gamma() );

        // Get the gammas direction. 
        // Isotropic emission.
        G4double costheta = 2.*G4UniformRand()-1;
        G4double theta = acos(costheta);
        G4double phi = twopi*G4UniformRand();
        G4double sinth = sin(theta);
        theOne->SetTotalEnergy( energy[i] );
        G4ThreeVector temp(energy[i]*sinth*cos(phi), 
                           energy[i]*sinth*sin(phi),
                           energy[i]*cos(theta) );
        theOne->SetMomentum( temp ) ;
        theGammas->push_back(theOne);
    }
    return theGammas;
}

static double getRandomCLHEP(TH1* hh)
{
    // return a random number distributed according the histogram bin contents.
    // This function checks if the bins integral exists. If not, the integral
    // is evaluated, normalized to one.
    // The integral is automatically recomputed if the number of entries
    // is not the same then when the integral was computed.
    // NB Only valid for 1-d histograms. Use GetRandom2 or 3 otherwise.
  
    if (hh->GetDimension()> 1) {
        G4cout << "Error in getRandomCLHEP: Function only valid for 1-d histograms"
               <<endl;
        return 0;
    }
    int nbinsx = hh->GetNbinsX();
    double integral;
  
    double *myIntegral = 0; //array
    myIntegral = hh->GetIntegral();
  
    if (myIntegral) {
        if (myIntegral[nbinsx+1] != hh->GetEntries()) {
            integral = hh->ComputeIntegral();
            //get the pointer to the integral array again
            myIntegral = hh->GetIntegral();
        } 
    } else {
        integral = hh->ComputeIntegral();
        //get the pointer to the integral array again
        myIntegral = hh->GetIntegral(); 
        if (integral == 0 || myIntegral == 0) return 0;
    }
  
    //Here enforce the CLHEP random number generator!
    //Double_t r1 = gRandom->Rndm();
    double r1 = HepRandom::getTheEngine()->flat();
  
    int ibin = TMath::BinarySearch(nbinsx,myIntegral,r1);
    double x = hh->GetBinLowEdge(ibin+1);
    if (r1 > myIntegral[ibin]) 
        x +=
            hh->GetBinWidth(ibin+1)*(r1-myIntegral[ibin])
            /(myIntegral[ibin+1] - myIntegral[ibin]);
    return x;
}


// The total energy of emission gammas is determinate.
// The gammas number and energy can be modified to make the sampling spectrum 
// to be close to the experimental spectrum as best as one can.
// The number of th gammas is about 3.

vector<double>  DsG4GdCaptureGammas::GetEnergy ()
{
    vector<double> Energy;
    G4double TotalEnergy;
    if (G4UniformRand()<0.815)
        TotalEnergy = 7.93; // captured by Gd157
    else
        TotalEnergy = 8.53; // captured by Gd155
    G4double energy_sum = 0.0;
    G4int    gamma_num = 0;
    G4double gamma_energy[100]={0};
    G4double energy_tmp;
  
  sample:
  

    //Use the CLHEP random engine to sample the distribution instead
    //Jianglai 10/01/2006
    //G4double energy=capspec->GetRandom();// sample from the experimental spectrum.
    G4double energy = getRandomCLHEP(capspec);
  
    energy_sum = energy_sum+energy;
    gamma_num = gamma_num+1;
    gamma_energy[gamma_num] = energy;

    if(energy_sum>TotalEnergy) {
        if((energy_sum-TotalEnergy)<0.8) {
            energy_tmp = gamma_energy[gamma_num-1]+energy-(energy_sum-TotalEnergy);
            if(energy_tmp>7.4) {
                energy_sum = energy_sum-energy;
                gamma_num = gamma_num-1;
                goto sample;
            }
            gamma_num = gamma_num-1;
            gamma_energy[gamma_num]=energy_tmp;
            goto goon;
        }
        energy_sum = energy_sum-energy;
        gamma_num = gamma_num-1;
        goto sample;
    }
    goto sample;

  goon:
  
    // set the sequence
    for(int i=gamma_num;i>1;i--) {
        for(int j=1;j<i;j++) {
            if(gamma_energy[j]<gamma_energy[j+1]) {
                energy_tmp = gamma_energy[j+1];
                gamma_energy[j+1] = gamma_energy[j];
                gamma_energy[j] = energy_tmp;
            }
        }
    }
    if(gamma_num<=3)
        goto  ok;
  
    if(gamma_energy[gamma_num]<0.8) {
        energy_tmp = gamma_energy[gamma_num]+gamma_energy[gamma_num-1];
        if(energy_tmp>7.4)
            goto ok;
        gamma_energy[gamma_num-1]=energy_tmp;
        gamma_num=gamma_num-1;
    }
   
  ok:
  
    for(int k=1;k<=gamma_num;k++)
        Energy.push_back(gamma_energy[k]); 
   
    return Energy;
}
