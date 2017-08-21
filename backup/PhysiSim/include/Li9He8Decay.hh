// This program generates Li9/He8 events.
// Sep. 09,2009  qinghe@princeton.edu

#ifndef Li9He8Decay_H
#define Li9He8Decay_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>

#include <CLHEP/Units/PhysicalConstants.h>
#include "CLHEP/Units/SystemOfUnits.h"
#include "G4ThreeVector.hh"

using namespace std;
using namespace CLHEP;

class Li9He8Decay
{
 public:  
  Li9He8Decay();
  ~Li9He8Decay() {};

  // For broad states, the final energy of the daughter nucleus is thrown according 
  // to a Breit-Wigner form
  //by default, only decays with neutrons are considered.
  //for complete decay, use the -complete_decay option
  void Li9Decay(G4ThreeVector &pElectron, G4ThreeVector &pNeutron,G4ThreeVector &pAlpha1, 
		G4ThreeVector &pAlpha2, double alpha_mass, bool complete_decay );
  
  //He8 decay
  //by default, only decays with neutrons are considered.
  //for complete decay, use the -complete_decay option
  //ref. Nucler Physics A366 (1981) 461-468, Nuclear Physics A487 (1988) 269-278 
  void He8Decay(G4ThreeVector &pElectron, G4ThreeVector &pNeutron, G4ThreeVector &pGamma,
		bool complete_decay);

 private:

  void RandomVector(G4ThreeVector& aVec);
  
  //Generate Li9 alpha sepectrum according data 
  //Nuclear Physics A450(1990) 189-208  fig.4
  double GetLi9AlphaEnergy(int whichcase);
  
  //Generate He8 neutron sepectrum according data 
  //Nuclear Physics A366(1981) 461-468  fig.4
  double GetHe8NeutronEnergy();
  
  // Chooses an intermediate energy for decays with broad levels
  // by thowing according to a Breit-Wigner form.  It is constrained,
  // however, to be >0 and less than the maximum available energy
  double GetIntermediateEnergy(double peak, double width, double max);
  
  //This Fermi function is copyed from Geant4
  double FermiFunc(double T, double Z);
  
  // Unnormalized beta spectrum (allowed approximation, including fermi factor)
  // Z is for daughter nucleus, i.e. 3 for He-8, 4 for Li-9
  double BetaSpectrum(double E, double QOfDecay, double Z);
  
  //Get the spectrum max by sampling 100 events
  double GetSpectrumMax(double QOfDecay, int Z);
  
  // Uses accept/reject method to generate electron energy according to beta spectrum
  // the Z is for the daughter nucleus
  double GetElectronEnergy(double QOfDecay, int Z, double max);
  
  //This is the neutron spectrum line shape for Li9 2.43MeV state 
  //ref. Nuclear Physics A450(1990) 189-208 
  double Li9NeutronLineShape1(double x);
  
  //This is the neutron spectrum line shape for Li9 2.43MeV state 
  //ref. Nuclear Physics A450(1990) 189-208 
  double Li9NeutronLineShape2(double x);
  
  //This is the neutron spectrum line shape for Li9 2.78MeV state 
  //ref. Nuclear Physics A450(1990) 189-208 
  double Li9NeutronLineShape3(double x);
  
  //Get Li9 neutron spectrum from the above line shapes 
  double GetLi9NeutronEnergy(int whichshape, double max);
  
};

#endif  // Li9He8Decay_H
