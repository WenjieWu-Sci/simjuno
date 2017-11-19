/*=============================================================================
#
# Author: Jingyu Luo - ljys1234@mail.ustc.edu.cn
# Last modified: 2013-12-20 15:30
# Filename: RecTimeLikeAlg.h
# Description: The algorithm includes the vertex reconstruction based on realtive
hit time likelihood, the visible energy reconstruction based on charge likelihood
and the non-linearity correction for positron 
=============================================================================*/
#ifndef RecTimeLikeAlg_h
#define RecTimeLikeAlg_h

#include "TString.h"
#include "Minuit2/FCNBase.h"
#include "Minuit2/FunctionMinimum.h"
#include "Minuit2/MnUserParameterState.h"
#include "Minuit2/MnMigrad.h"
#include <string>
#include "TH1.h"
#include "TF1.h"
#include "TFile.h"
#include "TTree.h"
#include "TVector3.h"
#include "G4SystemOfUnits.hh"
#include "globals.hh"
#include "G4PhysicalConstants.hh"
#include "G4ThreeVector.hh"
#include "EnergyTimeHit.hh"

using  std::string;

typedef std::vector<EnergyTimeHit*> EnergyTimeHitVector;

class RecTimeLikeAlg
{
public:
    RecTimeLikeAlg(EnergyTimeHitVector&);
    ~RecTimeLikeAlg();

    bool initialize();
    bool execute();
    bool finalize();

    bool Load_LikeFun();
    bool GridSearch();
    bool ChargeCenterRec();
    G4double HittimeGoodness(G4double, G4ThreeVector);
    G4double CalculateTOF(G4ThreeVector v0, G4ThreeVector v1);
    G4double Calculate_Energy_Likelihood(G4double, G4double, G4double, G4double);

    //Time Likelihood function
    TFile* Time_1hit;
    TH1D* pdf_1hit;

private:

    G4int m_iEvt;
    G4double timeSpread;

    G4double tmp_ve_x;
    G4double tmp_ve_y;
    G4double tmp_ve_z;
    G4double tmp_t_zero;
    G4double sign_x;
    G4double sign_y;
    G4double sign_z;
    G4double sign_t;
    G4double m_like_time;
    G4double m_ratio;
    G4double min_hit_time;

    G4double relaTime;
    //Charge Center Reconstruction
    G4ThreeVector ChaCenRec;

    //center detector geometry

    string File_path;
    G4double LS_R;
    G4double ChaCenRec_ratio;
    EnergyTimeHitVector fAllDetected;
//    ROOT::Minuit2::VariableMetricMinimizer theMinimizer;
};

//class MyFCN: public ROOT::Minuit2::FCNBase {
//public:
//    MyFCN(RecTimeLikeAlg* alg){m_alg =alg;}
//    G4double operator() (const std::vector<G4double>& x)const{
//        assert(x.size() == 4);
//        return m_alg->Calculate_Energy_Likelihood(x[0],x[1],x[2],x[3]);
//    }

//    G4double Up() const {return 0.5;}
//private:
//    RecTimeLikeAlg* m_alg;
//};
#endif
