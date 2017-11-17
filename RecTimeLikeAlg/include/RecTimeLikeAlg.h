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

#include "EvtNavigator/NavBuffer.h"
#include "TFitterMinuit.h"
#include "TString.h"
#include "Minuit2/FCNBase.h"
#include "SniperKernel/AlgBase.h"
#include "Geometry/RecGeomSvc.h"
#include "Identifier/Identifier.h"
#include <string>
#include "TH1.h"
#include "TF1.h"
#include "TFile.h"
#include "TTree.h"
#include "TVector3.h"

using  std::string;
class RecGeomSvc;
class CdGeom;
        class MyFCN: public ROOT::Minuit2::FCNBase {
         public:
          MyFCN(){}
          double operator() (const std::vector<double>& x)const{
//          Hit_time RATIO(iteration);
           // return num_PMT;
          //return Calculate_Energy_Likelihood(x[0],x[1],x[2],x[3],x[4]);
          return Calculate_Energy_Likelihood(x[0],x[1],x[2],x[3]);
          }
          bool Initialize_value(std::vector<int>&, std::vector<TVector3>&);
    
          //double Calculate_Energy_Likelihood(double,double,double,double,double)const ;
          double Calculate_Energy_Likelihood(double,double,double,double)const ;

          double Up() const {return 0.5;}
          private:
          std::vector<int> tmp_PE;
          std::vector<TVector3> tmp_pos;
       //   int iteration;
          }; 
 
class RecTimeLikeAlg: public AlgBase 
{
    public:
        RecTimeLikeAlg(const std::string& name); 
        ~RecTimeLikeAlg(); 

        bool initialize(); 
        bool execute(); 
        bool finalize(); 
       
        bool Load_LikeFun();
        bool GridSearch(); 
        bool ChargeCenterRec();
        bool ApplyCorrection();
       
        double PoissonValue(double,double);  
      
        double HittimeGoodness(double, double, double,double);
        
        double CalculateTOF( double, double, double, int);
    
        //double Calculate_Energy_Likelihood(double, double, double, double,double);
        double Calculate_Energy_Likelihood(double, double, double, double);

        double Energy_correction(double);
     
        class MyFCN: public ROOT::Minuit2::FCNBase {
         public:
          MyFCN(RecTimeLikeAlg *alg){m_alg =alg;}
          double operator() (const std::vector<double>& x)const{
          //return m_alg->Calculate_Energy_Likelihood(x[0],x[1],x[2],x[3],x[4]);
          return m_alg->Calculate_Energy_Likelihood(x[0],x[1],x[2],x[3]);
          }

          double Up() const {return 0.5;}
          private:
            RecTimeLikeAlg *m_alg;
          };
         
        
  
        

        //Time Likelihood function
        TFile* Time_1hit;
        TFile* Time_2hit;
        TFile* Time_3hit;
        TFile* Time_4hit;
        TFile* Time_5hit;
        TFile* Time_1hit_1ns;
        TFile* Time_2hit_1ns;
        TFile* Time_3hit_1ns;
        TFile* Time_4hit_1ns;
        TFile* Time_5hit_1ns;
        TFile* h_correction_file;
        TFile* f_PmtData;
        TTree* t_PmtData;

        TH1D* pdf_1hit;
        TH1D* pdf_2hit;
        TH1D* pdf_3hit;
        TH1D* pdf_4hit;
        TH1D* pdf_5hit;
        TH1D* pdf_1hit_1ns;
        TH1D* pdf_2hit_1ns;
        TH1D* pdf_3hit_1ns;
        TH1D* pdf_4hit_1ns;
        TH1D* pdf_5hit_1ns;
        TH1D* h_correction; 
    
        TF1* f_non_li_positron;
        TF1* fun_poisson; 
        TF1* f_correction;
       
       // double non_li_parameter[4];

    private:

        int m_iEvt;
        JM::NavBuffer* m_buf; 
        
        int num_PMT;
        double PMT_HIT[17746];
        double TimeSpread[17746];
      
        int pmtId;
        double timeSpread;
        
        double tmp_ve_x;
        double tmp_ve_y;
        double tmp_ve_z;
        double tmp_t_zero;
        double sign_x;
        double sign_y;
        double sign_z;
        double sign_t;
        double m_like_time;
        double m_ratio;
        double min_hit_time;
       
        double relaTime;
       
       //Charge and hit time information
        std::vector<double> Readout_PE;
        std::vector<double> Readout_hit_time; 
        std::vector<TVector3> PMT_pos;
        std::vector<double>  PMT_TTS; 
        std::vector<int>  PMT_ID; 

        //TFile* PMT_Geom;
       
        std::vector<TVector3> ALL_PMT_pos;

       //Charge Center Reconstruction
        double ChaCenRec_x;
        double ChaCenRec_y;
        double ChaCenRec_z;

       //Temporary Residual Time Distribution
       TH1D* tmp_resTime;
       TH1D* tmp_resTime_fix;
       
                
        //center detector geometry
        CdGeom*  m_cdGeom;

        TFitterMinuit* recminuit;
 

        string File_path; 
        double Total_num_PMT;
        double PMT_R ;
        double Ball_R;
        double LS_R;
        double pmt_r;
        double ChaCenRec_ratio;
        double m_Energy_Scale;
        int m_Vtx_Correction;
        int m_Pdf_Value;
        int m_FHS;
       
        double m_effective_attenuation;

        double fap0;
        double fap1;
        double fap2;
        double fap3;
        double fap4;
        double fap5;

        bool BIN_CUT[150];
        bool HIT_CUT[17746];
        bool PMT_HIT_CUT[17746];
       
};
#endif
