//-------------------------------------------------------
// Generate emission gamma energy and direction based on NNDC data.
//-------------------------------------------------------
// Author: Kevin Kuns, 2009/07/27
//-------------------------------------------------------

#ifndef DsG4NNDCCaptureGammas_hh
#define DsG4NNDCCaptureGammas_hh

#include "G4ReactionProductVector.hh"
#include <vector>

/////////////////////////////////////////////////////////

class DsG4NNDCCaptureGammas
{
public:

   DsG4NNDCCaptureGammas();
   ~DsG4NNDCCaptureGammas();
   void Init(int A, int Z);
   G4ReactionProductVector * GetGammas ();
   std::vector<double>  GetEnergy ();
   bool hasData(){ return m_hasData; }

private:

   bool m_hasData;
   std::vector<double> m_probabilities;
   std::vector< std::vector<double> > m_gammaEnergies;
};

#endif // DsG4NNDCCaptureGammas_hh
