//-------------------------------------------------------------------
// Emission gamma energy spectrum.  
// Based on experimental data, L.V. Groshev et al., Nucl. Data Tab. A5(1968) 1
// The sampling method is derived from DYB Geant3 simulation program.
//------------------------------------------------------------------
// Author: Kevin Kuns, 2009/07/27
// Based on: DsG4GdCaptureGammas.cc
//------------------------------------------------------------------

#include "DsG4NNDCCaptureGammas.h"
#include "Randomize.hh"
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include "G4Gamma.hh"

/////////////////////////////////////////////////////////////////////

using namespace std;
using namespace CLHEP;

DsG4NNDCCaptureGammas::DsG4NNDCCaptureGammas ():
  m_hasData(false)
{
}

DsG4NNDCCaptureGammas::~DsG4NNDCCaptureGammas () 
{
}

void DsG4NNDCCaptureGammas::Init( int A, int Z )
{
   // Gamma files should be placed in $DAYA_DATA_DIR directory.

   // To use the old spectra from nuclear data tables for Gd (gdcap_spec.root)
   // generated with unbiased sampling (see Doc-5750),
   // set the following boolean to true
   // (see also 'useNNDC_GdCapture' in DsG4NeutronHPCapture.cc)
   bool useOldNdtGdSpectra = true; 

   // define a map for Z
   map<int, string> elementName;
   elementName[64] = "Gd";
   elementName[26] = "Fe";
   elementName[28] = "Ni";
   elementName[14] = "Si";
   elementName[15] = "P";
   elementName[25] = "Mn";
   elementName[16] = "S";
   elementName[24] = "Cr";
   elementName[8] = "O";
   elementName[7] = "N";
   elementName[6] = "C";

   string fileName;
   fileName.append(elementName[Z]);
   ostringstream strA;
   strA << A;
   fileName.append(strA.str());
   if( Z == 64 && useOldNdtGdSpectra){
       fileName.append("NDT");
   }
   fileName.append("NeutronCaptureGammas.txt");

   const char* prefix = getenv("DAYA_DATA_DIR");
   if(prefix) {
       if(strlen(prefix)>0) { 
           std::string newname = prefix;
           newname += "/";
           newname += fileName;
           fileName = newname;
       }
   }

   ifstream file(fileName.c_str()); 

   //read data file
   string line;
   double totalProbability = 0;
   while(getline(file,line))
   {
       stringstream streamLine(line);
       double probability = 0.0;
       int numGammas = 0;
       if(streamLine.peek() != '#')
       {
           streamLine >> probability >> numGammas;
           m_probabilities.push_back(probability);
	   totalProbability += probability;
           vector<double> gammas;
           for(int i = 1; i <= numGammas; i++)
           {
               double gammaEnergy = 0.0;
               streamLine >> gammaEnergy;
               gammas.push_back(gammaEnergy/1000.0); // Convert to MeV
           }
           m_gammaEnergies.push_back(gammas);
       }
   }
   file.close();

   if( m_probabilities.size() > 0){
     std::cout << "Loaded " << m_probabilities.size() 
	       << " gamma decay combinations from file " << fileName << endl;
     std::cout << "Rescaling all gamma lines by total probability: " 
	       << totalProbability << endl;
     for(unsigned int i=0; i<m_probabilities.size(); i++){
       m_probabilities[i] /= totalProbability;
     }
     m_hasData = true;
   }else{
     std::cout << "DsG4NNDCCaptureGammas  WARNING: No data loaded for isotope "
	       << "A=" << A << " Z=" << Z 
	       << ".  Cross section will be set to zero."
	       << endl;
     m_hasData = false;
   }
}

G4ReactionProductVector* DsG4NNDCCaptureGammas::GetGammas ()
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

vector<double>  DsG4NNDCCaptureGammas::GetEnergy ()
{
   //pick a decay scheme
   G4double random = G4UniformRand();
   double sum = 0.0;
   unsigned int i = 0;
   while(i < m_probabilities.size() )
   {
       sum += m_probabilities[i];
       if(sum >= random)
       {
	 // cout << "Returning gamma branch " << i << endl;
           return m_gammaEnergies[i];
       }
       i++;
   }
   std::cerr << "Failed to generate gammas!" << endl;
   return vector<double>(0);
}
