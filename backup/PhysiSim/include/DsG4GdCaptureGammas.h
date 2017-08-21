//-------------------------------------------------------
// Dice the emission gamma energy and direction based on experimental data.
//-------------------------------------------------------
// Author: Liang Zhan, 2006/01/27
//-------------------------------------------------------

#ifndef DsG4GdCaptureGammas_hh
#define DsG4GdCaptureGammas_hh

#include "G4ReactionProductVector.hh"
#include <vector>

class TFile;
class TH1F;

/////////////////////////////////////////////////////////

class DsG4GdCaptureGammas
{
public:
   
    DsG4GdCaptureGammas();
    ~DsG4GdCaptureGammas();
    G4ReactionProductVector * GetGammas ();
    std::vector<double>  GetEnergy ();

private:
   
    TFile * specfile;
    TH1F  * capspec; // the experimental gamma spectrum.
};

#endif
