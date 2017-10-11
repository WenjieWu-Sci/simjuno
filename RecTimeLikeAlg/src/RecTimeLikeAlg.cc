/*=============================================================================
#
# Author: Jingyu Luo - ljys1234@mail.ustc.edu.cn
# Last modified: 2013-12-20 15:30
# Filename: RecTimeLikeAlg.cc
# Description: The algorithm includes the vertex reconstruction based on realtive
hit time likelihood, the visible energy reconstruction based on charge likelihood
and the non-linearity correction for positron
# Notification: the vertex reconstruction and visible energy reconstrucion got tuned,
  The non-linearity need to be further considered.
=============================================================================*/
#include <boost/python.hpp>
#include "RecTimeLikeAlg.h"
#include "TMath.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TF1.h"
#include "TFitterMinuit.h"
#include "TString.h"
#include "TStopwatch.h"
#include "Minuit2/FCNBase.h"
#include "SniperKernel/AlgFactory.h"
#include "Event/RecHeader.h"
#include "Event/CalibHeader.h"
#include "Geometry/RecGeomSvc.h"
#include "Identifier/Identifier.h"
#include "Identifier/CdID.h"
#include <boost/filesystem.hpp>

#include "DataRegistritionSvc/DataRegistritionSvc.h"
#include "BufferMemMgr/IDataMemMgr.h"
#include "EvtNavigator/NavBuffer.h"

#include <algorithm>

namespace fs = boost::filesystem;

DECLARE_ALGORITHM(RecTimeLikeAlg); 

 RecTimeLikeAlg::RecTimeLikeAlg(const std::string& name)
:   AlgBase(name)
{
    m_iEvt = -1; 

    Total_num_PMT = 17746;
    PMT_R = 19.5;
    Ball_R = 19.316;
    LS_R = 17.7;
    pmt_r = 0.254;
    ChaCenRec_ratio = 1.2;
    m_Energy_Scale = 2780.53;
    m_Vtx_Correction = 0;
    m_Pdf_Value = 0;
    m_FHS = 0;
   
    m_effective_attenuation = 0.026;//0.0365
    std::string base = getenv("RECTIMELIKEALGROOT");
    File_path = (fs::path(base)/"share").string();
    
    fap0 =1;///*0.998941;*/0.99349;// 0.99349;//
    fap1 =-0.0619723;///*-0.0360902;*/ 0.0351846;//-0.0432553;//-0.0360902;//-0.0351816;
    fap2 =-0.128378;///*-0.11531;*/-0.185473;//-0.106736;//-0.11531//-0.116051;
    fap3 =-0.0435327;///*-0.0861813;*/-0.16008;//-0.0810257;//-0.0861813//-0.0847666;
    fap4 = -0.0196508;///*-0.0446783;*/ -0.0591105;//-0.0459026;//-0.0446783//-0.0449179;
    fap5 =-0.051765;///*-0.0116353;*/ 0.041457;//-0.0165357;//-0.0116353//-0.0156252;

    declProp("TotalPMT", Total_num_PMT=17746);
    declProp("PMT_R", PMT_R);
    declProp("Ball_R",Ball_R);
    declProp("LS_R", LS_R);
    declProp("pmt_r", pmt_r);
    declProp("ChaCenRec_ratio", ChaCenRec_ratio);
    declProp("Energy_Scale", m_Energy_Scale);
    declProp("File_path", File_path);
    declProp("Vtx_Correction",m_Vtx_Correction);
    declProp("Pdf_Value",m_Pdf_Value);
    declProp("FHS",m_FHS);
    LogDebug<<"TotalPMT:"<<Total_num_PMT<<std::endl;
    LogDebug<<"PMT_R:"<<PMT_R<<std::endl;
    LogDebug<<"LS_R:"<<LS_R<<std::endl;
    LogDebug<<"Energy_Scale:"<<m_Energy_Scale<<std::endl;
    LogDebug<<"Vtx_Correction:"<<m_Vtx_Correction<<std::endl;
    LogDebug<<"Pdf_Value:"<<m_Pdf_Value<<std::endl;
    LogDebug<<"File_Path:"<<File_path<<std::endl;
   Time_1hit = 0;
   Time_2hit = 0;
   Time_3hit = 0;
   Time_4hit = 0;
   Time_5hit = 0;
   Time_1hit_1ns = 0;
   Time_2hit_1ns = 0;
   Time_3hit_1ns = 0;
   Time_4hit_1ns = 0;
   Time_5hit_1ns = 0;
   h_correction_file =0;
   f_PmtData = 0;
   t_PmtData = 0;
}

RecTimeLikeAlg::~RecTimeLikeAlg()
{
   delete Time_1hit;
   delete Time_2hit;
   delete Time_3hit;
   delete Time_4hit;
   delete Time_5hit;
   delete Time_1hit_1ns;
   delete Time_2hit_1ns;
   delete Time_3hit_1ns;
   delete Time_4hit_1ns;
   delete Time_5hit_1ns;
   delete h_correction_file;
   delete t_PmtData;
   delete f_PmtData;
//   delete PMT_Geom;
}

bool RecTimeLikeAlg::initialize()
{
  
   MyFCN* fcn = new MyFCN(this);
   recminuit = new TFitterMinuit();
   recminuit->SetMinuitFCN(fcn);
   recminuit->SetPrintLevel(0); 
   //Load the hit time likelihood function
    Load_LikeFun();
    //Event navigator
    SniperDataPtr<JM::NavBuffer>  navBuf(getScope(), "/Event");
    if ( navBuf.invalid() ) {
        LogError << "cannot get the NavBuffer @ /Event" << std::endl;
        return false;
    }
    m_buf = navBuf.data();

    // //DataRegistritionSvc
    // SniperPtr<DataRegistritionSvc> drSvc("DataRegistritionSvc");
    // if ( drSvc.invalid() ) {
    //     LogError << "Failed to get DataRegistritionSvc instance!"
    //         << std::endl;
    //     return false;
    // }
    // drSvc->registerData("JM::RecEvent", "/Event/Rec");

    //Reconstruction Geometry service
    SniperPtr<RecGeomSvc> rgSvc("RecGeomSvc"); 
    if ( rgSvc.invalid()) {
        LogError << "Failed to get RecGeomSvc instance!" << std::endl;
        return false;
    }
    m_cdGeom = rgSvc->getCdGeom(); 

    // Get the geometry service for all PMT;    
    // Total_num_PMT = m_cdGeom->findPmtNum();
    Total_num_PMT = m_cdGeom->findPmt20inchNum();
    LogInfo << "Total PMT: " << Total_num_PMT << std::endl;
    for(int i = 0; i<Total_num_PMT; i++){
        unsigned int all_pmt_id = (unsigned int)i;
        Identifier all_id = Identifier(CdID::id(all_pmt_id,0));
        //std::cout<<"PMTID:"<<I<<",POS:"<<<<std::endl;
        PmtGeom *all_pmt = m_cdGeom->getPmt(all_id);
        if ( !all_pmt ) {
            LogError << "Wrong Pmt Id " << i << std::endl;
        }
        TVector3 all_pmtCenter = all_pmt->getCenter();
        ALL_PMT_pos.push_back(Ball_R/PMT_R*all_pmtCenter);
        t_PmtData->GetEntry(i);
        TimeSpread[i] = timeSpread;
    } 

    //    Identifier pid = Identifier(CdID::id(300001, 0));;
    //    if ( CdID::is20inch(pid) ) {
    //      int lpmtId = CdID::module(pid);
    //      LogInfo << "LINTAO: LPMTID: " << lpmtId << std::endl;
    //    } else if ( CdID::is3inch(pid) ) {
    //      int spmtId = CdID::module(pid) - CdID::module3inchMin() + 300000;
    //      LogInfo << "LINTAO: SPMTID: " << spmtId << std::endl;
    //    }


    LogInfo  << objName()
        << "   initialized successfully"
        << std::endl; 
    return true; 

}

bool RecTimeLikeAlg::execute()
{
    ++m_iEvt;

    LogDebug << "---------------------------------------" << std::endl;
    LogDebug << "Processing event " << m_iEvt << std::endl;
    JM::EvtNavigator* nav = m_buf->curEvt(); 

    //read CalibHit data
    JM::CalibHeader* chcol =(JM::CalibHeader*) nav->getHeader("/Event/Calib"); 
    const std::list<JM::CalibPMTChannel*>& chhlist = chcol->event()->calibPMTCol();
    std::list<JM::CalibPMTChannel*>::const_iterator chit = chhlist.begin();
    double pe_sum = 0;
    for(int i = 0; i<Total_num_PMT; i++){
       PMT_HIT[i] = 0;
       HIT_CUT[i] = true;
       PMT_HIT_CUT[i] = true;
    }
    for(int i = 0; i<150;i++){
     BIN_CUT[i] = true;
    }

    while (chit!=chhlist.end()) {
        const JM::CalibPMTChannel  *calib = *chit++;

        unsigned int pmtId = calib->pmtId();
        Identifier id = Identifier(pmtId);

        // test to decode it to pmtid in detsim
        // Identifier pid = id;
        // if ( CdID::is20inch(pid) ) {
        //   int lpmtId = CdID::module(pid);
        //   LogInfo << "LINTAO: LPMTID: " << lpmtId << std::endl;
        // } else if ( CdID::is3inch(pid) ) {
        //   int spmtId = CdID::module(pid) - CdID::module3inchMin() + 300000;
        //   LogInfo << "LINTAO: SPMTID: " << spmtId << std::endl;
        // }

        if (not CdID::is20inch(id)) {
            continue;
        }
//	std::cout <<CdID::module(id) <<std::endl;
    //    PMT_HIT[CdID::module(id)] += calib->n;

        double nPE = calib->nPE();
        double firstHitTime = calib->firstHitTime();
        PMT_HIT[CdID::module(id)] = nPE;
        Readout_PE.push_back(nPE);
        pe_sum = pe_sum +nPE;
        Readout_hit_time.push_back(firstHitTime);
        PMT_TTS.push_back(TimeSpread[CdID::module(id)]);

        PmtGeom *pmt = m_cdGeom->getPmt(id);
        if ( !pmt ) {
            LogError << "Wrong Pmt Id " << id << std::endl;
        }
        TVector3 pmtCenter = pmt->getCenter();
        PMT_pos.push_back(Ball_R/PMT_R*pmtCenter);
        PMT_ID.push_back(CdID::module(id));

        if (m_iEvt == 0 ) {
        //if (1) {
         /*   LogDebug << "   pmtId : " <<CdID::module(id)
                << "    nPE : " << nPE
                << "    firstHitTime : " << firstHitTime
                << "  pmtCenter : " << pmtCenter.x()
                << "  " <<  pmtCenter.y()
                << "  "  << pmtCenter.z() 
                << "  TTS :"<<TimeSpread[CdID::module(id)]<< std::endl;*/
     //      LogDebug<<firstHitTime<<std::endl;
        }
    }
       
    LogDebug  << "Done to read CalibPMT" << std::endl;

    std::vector<double>::iterator Min_hit_time = min_element(Readout_hit_time.begin(),Readout_hit_time.end());
    min_hit_time = *Min_hit_time;
    std::cout<<"min:"<<min_hit_time<<",a0;"<<Readout_hit_time[0]<<std::endl;

    num_PMT = PMT_pos.size();
    std::cout << "num_PMT:"<<num_PMT <<std::endl;   
    TStopwatch timer;
    timer.Start();

    RecTimeLikeAlg::ChargeCenterRec();
   
    RecTimeLikeAlg::GridSearch();

    if(0)
   // if(m_Vtx_Correction)
    RecTimeLikeAlg::ApplyCorrection();
   // std::cout<<tmp_ve_x<<std::endl; 
    //RecTimeLikeAlg::MyFCN fcn;
    
    double x_fit = tmp_ve_x;
    double y_fit = tmp_ve_y;
    double z_fit = tmp_ve_z;
    double t_fit = tmp_t_zero;
    double n_fit;
    double E_rec;
    double att_length;
    std::cout<<"ChaCenRec:("<<ChaCenRec_x<<","<<ChaCenRec_y<<","<<ChaCenRec_z<<")"<<std::endl;

    fun_poisson=new TF1("fun_poisson","TMath::Poisson(x,[0])",-5,20);

   tmp_resTime_fix = new TH1D("","",150,-250,1250);
   for(int i = 0; i<num_PMT; i++){
       double timeflight = RecTimeLikeAlg::CalculateTOF(x_fit, y_fit, z_fit, i);
       tmp_resTime_fix->Fill(Readout_hit_time.at(i)-timeflight-min_hit_time);
   }

   for(int i = 0; i<150;i++){
      double BinValue = tmp_resTime_fix->GetBinContent(i+1);
      if((BinValue - 5.3) < 8.0)BIN_CUT[i] = true;
      else BIN_CUT[i] = false;
    //std::cout<<"i:"<<i<<",bin_cut:"<<BIN_CUT[i]<<std::endl;
   }

   for(int i = 0; i<num_PMT; i++){
    double timeflight = RecTimeLikeAlg::CalculateTOF(x_fit, y_fit, z_fit, i);
    int NBin = int((Readout_hit_time.at(i) - timeflight - min_hit_time)/10.0) + 25;
    if(BIN_CUT[NBin] == false) {HIT_CUT[i] = false;PMT_HIT_CUT[PMT_ID.at(i)] = false;}
    else if(BIN_CUT[NBin] == true){HIT_CUT[i] = true;PMT_HIT_CUT[PMT_ID.at(i)] = true;}
//    if(HIT_CUT[i] == false)std::cout<<"111ID:"<<PMT_ID.at(i)<<std::endl;
//    if(PMT_HIT_CUT[PMT_ID.at(i)] == false)std::cout<<"222ID:"<<PMT_ID.at(i)<<std::endl;
//    if(PMT_ID.at(i) == 5)std::cout<<"time-tof:"<<Readout_hit_time.at(i) - timeflight<<",bin cut"<<BIN_CUT[NBin]<<std::endl;
   }

   delete tmp_resTime_fix;

    recminuit->SetParameter(0,"n",5000, 0.5,0, 100000);
    recminuit->SetParameter(1,"xpos",x_fit,1000,-18000,18000);
    recminuit->SetParameter(2,"ypos",y_fit,1000,-18000,18000);
    recminuit->SetParameter(3,"zpos",z_fit,1000,-18000,18000);
    //recminuit->SetParameter(4,"att_length",0.026,0.001,0,1);
    
    recminuit->FixParameter(1);
    recminuit->FixParameter(2);
    recminuit->FixParameter(3);
    recminuit->CreateMinimizer();

    int ief = recminuit->Minimize();

    n_fit = recminuit->GetParameter(0);
    //att_length = recminuit->GetParameter(4);
    //Non-linearity Correction for positron
   double  non_li_parameter[4] = {0.122495, 1.04074, 1.78087, 0.00189743};
   double  correction_par[6] = {155.691, -0.187317, 9.01254e-05, -2.13865e-08, 2.50316e-12, -1.1577e-16};

    f_non_li_positron = new TF1("pos","1.022*(([1]+[3]*(x-1.022))*(x-1.022)/(1+[0]*exp(-[2]*(x-1.022)))+0.935802158)/0.935802",0,12);
    f_non_li_positron->SetParameters(non_li_parameter); 
    f_correction = new TF1("corr","[0]+[1]*x+[2]*x*x+[3]*x*x*x+[4]*x*x*x*x+[5]*x*x*x*x*x",0,5600);
    f_correction->SetParameters(correction_par);

    //LogDebug<<"n_fit is"<<n_fit<<std::endl;
    //n_fit = n_fit/m_Energy_Scale;
    //LogDebug<<"Energy_Scale"<<m_Energy_Scale<<std::endl;
    double R = TMath::Sqrt(x_fit*x_fit+y_fit*y_fit+z_fit*z_fit)/1000;
    double R_3 = R*R*R;
/*energy non-uniformity correction*/
    E_rec = 2.005*(n_fit/m_Energy_Scale)/Energy_correction(R);
/**non-linearity correction**/
    E_rec = f_non_li_positron->GetX(E_rec);

    timer.Stop();
    double time = timer.RealTime();
    LogDebug<<"==========================================================="<<std::endl;
    LogDebug<<"The Timestamp is '" << nav->TimeStamp() << "'" << std::endl;
    LogDebug<<"The Reconstructed x is "<<x_fit<<std::endl;
    LogDebug<<"The Reconstructed y is "<<y_fit<<std::endl;
    LogDebug<<"The Reconstructed z is "<<z_fit<<std::endl;
    LogDebug<<"The Reconstructed n is "<<n_fit<<std::endl;
    LogDebug<<"The Reconstructed To is "<<t_fit<<std::endl;
    LogDebug<<"The Reconstructed energy is "<<E_rec<<std::endl;
    LogDebug<<"The Reconstruction Process Cost "<<time<<std::endl;
    LogDebug<<"The Complete Reconstrution Process is Completed!"<<std::endl;
    LogDebug<<"==========================================================="<<std::endl;
     
    JM::RecHeader* aDataHdr = new JM::RecHeader(); //unit: mm,  MeV, ...
    JM::CDRecEvent* aData = new JM::CDRecEvent();
    aData->setX(x_fit); 
    aData->setY(y_fit); 
    aData->setZ(z_fit); 
    aData->setEnergy(n_fit);
    aData->setEprec(E_rec); 
    aData->setPESum(pe_sum); 
    aData->setPx(t_fit); 
    aData->setPy(time); 
    aData->setPz(m_like_time); 
    aDataHdr->setCDEvent(aData);
    nav->addHeader("/Event/Rec", aDataHdr); 

    PMT_pos.clear();
    Readout_PE.clear();
    Readout_hit_time.clear();
    PMT_ID.clear();
    recminuit->Clear();
    delete f_non_li_positron;
    delete f_correction;
    delete fun_poisson;
    return true; 

}

bool RecTimeLikeAlg::Load_LikeFun()
{  
   fs::path s(File_path);
   Time_1hit = new TFile(TString((s/"pdf_n1.root").string()));
   Time_2hit = new TFile(TString((s/"pdf_n2.root").string()));
   Time_3hit = new TFile(TString((s/"pdf_n3.root").string()));
   Time_4hit = new TFile(TString((s/"pdf_n4.root").string()));
   Time_5hit = new TFile(TString((s/"pdf_n5.root").string()));
   Time_1hit_1ns = new TFile(TString((s/"pdf_n1_1ns.root").string()));
   Time_2hit_1ns = new TFile(TString((s/"pdf_n2_1ns.root").string()));
   Time_3hit_1ns = new TFile(TString((s/"pdf_n3_1ns.root").string()));
   Time_4hit_1ns = new TFile(TString((s/"pdf_n4_1ns.root").string()));
   Time_5hit_1ns = new TFile(TString((s/"pdf_n5_1ns.root").string()));
   h_correction_file = new TFile(TString((s/"E_calib_2MeV.root").string()));
   f_PmtData = new TFile(TString((s/"PmtData.root").string()));
  
   if(!Time_1hit)
   LogError  << "Failed to get Likelihood Function File!" << std::endl;

   pdf_1hit = (TH1D*)Time_1hit->Get("tim");
   pdf_2hit = (TH1D*)Time_2hit->Get("tim");
   pdf_3hit = (TH1D*)Time_3hit->Get("tim");
   pdf_4hit = (TH1D*)Time_4hit->Get("tim");
   pdf_5hit = (TH1D*)Time_5hit->Get("tim");
   pdf_1hit_1ns = (TH1D*)Time_1hit_1ns->Get("tim");
   pdf_2hit_1ns = (TH1D*)Time_2hit_1ns->Get("tim");
   pdf_3hit_1ns = (TH1D*)Time_3hit_1ns->Get("tim");
   pdf_4hit_1ns = (TH1D*)Time_4hit_1ns->Get("tim");
   pdf_5hit_1ns = (TH1D*)Time_5hit_1ns->Get("tim");
   h_correction = (TH1D*)h_correction_file->Get("energy");
   t_PmtData = (TTree*)f_PmtData->Get("PmtData");
   t_PmtData->SetBranchAddress("pmtId",&pmtId);
   t_PmtData->SetBranchAddress("timeSpread",&timeSpread);   

   return true;

}


double RecTimeLikeAlg::PoissonValue(double x,double par){
  fun_poisson->SetParameter(0,par);
  //std::cout<<">>>call Poisson Fun,mean :"<<par<<std::endl;
  return fun_poisson->Eval(x);
} 

bool RecTimeLikeAlg::ChargeCenterRec()
{
   double x_sum = 0;
   double y_sum = 0;
   double z_sum = 0; 
   double PE_sum = 0;
   
   for(int i = 0; i< num_PMT; i++){
     x_sum = x_sum + PMT_pos.at(i).X()*Readout_PE.at(i);
     y_sum = y_sum + PMT_pos.at(i).Y()*Readout_PE.at(i);
     z_sum = z_sum + PMT_pos.at(i).Z()*Readout_PE.at(i);
     PE_sum = PE_sum + Readout_PE.at(i);
   }
   ChaCenRec_x = x_sum/PE_sum;
   ChaCenRec_y = y_sum/PE_sum;
   ChaCenRec_z = z_sum/PE_sum;
  

   return true;
}

double RecTimeLikeAlg::HittimeGoodness(double T_zero,
                                       double Vert_x,
                                       double Vert_y,
                                       double Vert_z)
{
  /* tmp_resTime = new TH1D("","",150,-250,1250);
   for(int i = 0; i<num_PMT; i++){
       double timeflight = RecTimeLikeAlg::CalculateTOF(Vert_x, Vert_y, Vert_z, i);
       //double timeflight = RecTimeLikeAlg::CalculateTOF(6203.,-1119.98,-4062.31, i);
       tmp_resTime->Fill(Readout_hit_time.at(i)-timeflight);
   }
   
   for(int i = 0; i<150;i++){
      double BinValue = tmp_resTime->GetBinContent(i+1);
      if((BinValue - 5.3) < 8.0)BIN_CUT[i] = true;
      else BIN_CUT[i] = false;
   }
   
   for(int i = 0; i<num_PMT; i++){
    double timeflight = RecTimeLikeAlg::CalculateTOF(Vert_x, Vert_y, Vert_z, i);
    //double timeflight = RecTimeLikeAlg::CalculateTOF(6203.,-1119.98,-4062.31, i);
    int NBin = int((Readout_hit_time.at(i) - timeflight)/10.0) + 25;
    if(BIN_CUT[NBin] == false) HIT_CUT[i] = false;
    else if(BIN_CUT[NBin] == true)HIT_CUT[i] = true;
   }*/

  /*TH1D* tmp_resTime_new = new TH1D("tmp_new","tmp_new",150,-250,1250);
  for(int i = 0; i<num_PMT; i++){
      double timeflight = RecTimeLikeAlg::CalculateTOF(Vert_x, Vert_y, Vert_z, i);
      //double timeflight = RecTimeLikeAlg::CalculateTOF(6203.,-1119.98,-4062.31, i);
      if(HIT_CUT[i] == false)
       tmp_resTime_new->Fill(Readout_hit_time.at(i)-timeflight);
   } 

   std::cout<<"save tmp_res..."<<std::endl;
   TFile* f = new TFile("tmp_new.root","recreate");
   f->WriteTObject(tmp_resTime_new,"tmp_res");
   delete tmp_resTime;*/
   
   double Goodness = 0; 
   double FiredPMT = 0;
   
//     std::cout<<"HittimeGoodness"<<std::endl;
   for(int i = 0; i<num_PMT; i++){
    // if(HIT_CUT[i] == false){
     if(Readout_PE.at(i)!=0){
  //   std::cout<<Readout_hit_time.at(i)<<std::endl;
      double timeflight = RecTimeLikeAlg::CalculateTOF(Vert_x, Vert_y, Vert_z, i);
      relaTime=Readout_hit_time.at(i)-timeflight+T_zero-min_hit_time;
     
      if(relaTime>-30&&relaTime<300){//by default it is 300 ns
        int BinTime = (int)((relaTime+200)*200/7);

        double pdfValue;
    
        if(m_Pdf_Value == 0){
              if(Readout_PE.at(i)<1.5)                             pdfValue = pdf_1hit->GetBinContent(BinTime);
              else if(Readout_PE.at(i)>=1.5&&Readout_PE.at(i)<2.5) pdfValue = pdf_2hit->GetBinContent(BinTime);
              else if(Readout_PE.at(i)>=2.5&&Readout_PE.at(i)<3.5) pdfValue = pdf_3hit->GetBinContent(BinTime);
              else if(Readout_PE.at(i)>=3.5&&Readout_PE.at(i)<4.5) pdfValue = pdf_4hit->GetBinContent(BinTime);
              else pdfValue = pdf_5hit->GetBinContent(BinTime);
        }  
        else if(m_Pdf_Value == 1){
           if(PMT_TTS.at(i)>8.0){
              if(Readout_PE.at(i)<1.5)                             pdfValue = pdf_1hit->GetBinContent(BinTime);
              else if(Readout_PE.at(i)>=1.5&&Readout_PE.at(i)<2.5) pdfValue = pdf_2hit->GetBinContent(BinTime);
              else if(Readout_PE.at(i)>=2.5&&Readout_PE.at(i)<3.5) pdfValue = pdf_3hit->GetBinContent(BinTime);
              else if(Readout_PE.at(i)>=3.5&&Readout_PE.at(i)<4.5) pdfValue = pdf_4hit->GetBinContent(BinTime);
              else pdfValue = pdf_5hit->GetBinContent(BinTime);
             }
           else if(PMT_TTS.at(i)<8.0){
             if(Readout_PE.at(i)<1.5)                              pdfValue = pdf_1hit_1ns->GetBinContent(BinTime);
              else if(Readout_PE.at(i)>=1.5&&Readout_PE.at(i)<2.5) pdfValue = pdf_2hit_1ns->GetBinContent(BinTime);
              else if(Readout_PE.at(i)>=2.5&&Readout_PE.at(i)<3.5) pdfValue = pdf_3hit_1ns->GetBinContent(BinTime);
              else if(Readout_PE.at(i)>=3.5&&Readout_PE.at(i)<4.5) pdfValue = pdf_4hit_1ns->GetBinContent(BinTime);
              else pdfValue = pdf_5hit->GetBinContent(BinTime);
            }
         }
        if(pdfValue!=0){
           Goodness = Goodness-TMath::Log(pdfValue);
        }
        else{
           Goodness = Goodness+0;
        }
       
        FiredPMT++;
      }
     }
   }
   return Goodness/FiredPMT;
}

double RecTimeLikeAlg::Energy_correction(double x){
    double r3 = pow(x,3);
    int prebin = int((r3-6.)/12.) + 1;
    int nextbin = int((r3-6.)/12.) + 2;
    double prebincenter   = h_correction->GetBinCenter(prebin);
    double prebincontent  = h_correction->GetBinContent(prebin);
    double nextbincontent = h_correction->GetBinContent(nextbin);
    double result = prebincontent + (nextbincontent - prebincontent)*(r3-prebincenter)/12.;
    return result;
}

bool RecTimeLikeAlg::GridSearch()
{  m_like_time=1000.0;
   tmp_t_zero = 0;
   for(int init_val = 0;init_val < 1;init_val++){
   //Begin with Charge Center Reconstruction;
   tmp_ve_x =(1.2+init_val*0.1)*ChaCenRec_x;
   tmp_ve_y =(1.2+init_val*0.1)*ChaCenRec_y;
   tmp_ve_z =(1.2+init_val*0.1)*ChaCenRec_z;
//   std::cout<<tmp_ve_x<<std::endl; 
   //tag for grid search
   int tag_x = 4;
   int tag_y = 4;
   int tag_z = 4;
   int tag_t = 10;
  
   double delta = 1e10;
   
   double step_length = 1000;
   
   for(int iteration = 0; iteration < 100; iteration++){//100
       if(step_length<0.1) break;
       for(int bin_t = -4;bin_t<5;bin_t++){//-4,5
       for(int bin_x = -1; bin_x<2; bin_x++){//-1,2
           for(int bin_y = -1; bin_y<2; bin_y++){
               for(int bin_z = -1; bin_z<2; bin_z++){
//	std::cout<<"tst binx:"<<bin_x<<"  biny:"<<bin_y<<"  binz:"<<bin_z<<std::endl;
                   double tmp_x = tmp_ve_x+bin_x*step_length;
                   double tmp_y = tmp_ve_y+bin_y*step_length;
                   double tmp_z = tmp_ve_z+bin_z*step_length;
   //       std::cout<<"vtx:"<<tmp_x<<","<<tmp_y<<","<<tmp_z<<","<<tmp_t_zero+bin_t*step_length/100.0<<std::endl;
                   if((tmp_x*tmp_x+tmp_y*tmp_y+tmp_z*tmp_z)<17700.*17700.){
                   double d = HittimeGoodness(tmp_t_zero+bin_t*step_length/100.0,
                                              tmp_ve_x+bin_x*step_length,
                                              tmp_ve_y+bin_y*step_length,
                                              tmp_ve_z+bin_z*step_length);
//	std::cout<<"tst binx:"<<bin_x<<"  biny:"<<bin_y<<"  binz:"<<bin_z<<std::endl;
                   if(d<delta){
                      tag_x = bin_x;
                      tag_y = bin_y;
                      tag_z = bin_z;
                      tag_t = bin_t;
                      delta = d;
                   }
                  }                
                  else continue;
                 }
               }
           }
        }
        tmp_ve_x = tmp_ve_x + static_cast<double>(tag_x*step_length);
        tmp_ve_y = tmp_ve_y + static_cast<double>(tag_y*step_length);
        tmp_ve_z = tmp_ve_z + static_cast<double>(tag_z*step_length);
        tmp_t_zero = tmp_t_zero + static_cast<double>(tag_t*step_length/100.0);
        
        if(0==tag_x&&0==tag_y&&0==tag_z&&0==tag_t){
           step_length = step_length/2;
        }
        tag_x=tag_y=tag_z=tag_t=0;
    }
     if(delta<m_like_time){
       sign_x = tmp_ve_x;
       sign_y = tmp_ve_y;
       sign_z = tmp_ve_z;
       sign_t = tmp_t_zero;
       m_like_time = delta;
       m_ratio  = 1.2+0.1*init_val;
     }
//  LogDebug<<delta<<std::endl;
  }
    tmp_ve_x = sign_x;
    tmp_ve_y = sign_y;
    tmp_ve_z = sign_z;
    tmp_t_zero = sign_t;
        return true;
}


double RecTimeLikeAlg::CalculateTOF(double source_x,
                                     double source_y,
                                     double source_z,
                                     int ID)
{
  double pmt_pos_x = PMT_pos.at(ID).X();
  double pmt_pos_y = PMT_pos.at(ID).Y();
  double pmt_pos_z = PMT_pos.at(ID).Z();
 
  double dx = (source_x - pmt_pos_x)/1000;
  double dy = (source_y - pmt_pos_y)/1000;
  double dz = (source_z - pmt_pos_z)/1000;
  
  double r0 = (TMath::Sqrt(source_x*source_x+source_y*source_y+source_z*source_z))/1000;
  double dist = TMath::Sqrt(dx*dx+dy*dy+dz*dz);
  
  double cos_theta = (Ball_R*Ball_R+dist*dist-r0*r0)/(2*Ball_R*dist);
  
  double theta = TMath::ACos(cos_theta);
  
  double dist_oil = Ball_R*cos_theta-TMath::Sqrt(LS_R*LS_R-Ball_R*Ball_R*TMath::Sin(theta)*TMath::Sin(theta));

  if(m_Pdf_Value == 0){
  //return (dist-dist_oil)*5.13333+dist_oil*4.2;//Luojingyu
//  return (dist-dist_oil)*5.13333+dist_oil*4.4333;//refraction index,by default LS is 5.13333
     return (dist-dist_oil)*1e9*1.54/299792458+dist_oil*1e9*1.33/299792458;//currently
  }
  //return (dist-dist_oil)*1e9*1.54/299792458+dist_oil*1e9*1.47/299792458;//oil
  else if(m_Pdf_Value == 1){
     return (dist-dist_oil)*1e9*1.556/299792458+dist_oil*1e9*1.33/299792458;//currently
  } 

}

  double RecTimeLikeAlg::Calculate_Energy_Likelihood(double n0,
                                            double m_x,
                                            double m_y,
                                            double m_z)
                                           // double m_eff)
{
 /*  tmp_resTime_fix = new TH1D("","",150,-250,1250);
   for(int i = 0; i<num_PMT; i++){
       double timeflight = RecTimeLikeAlg::CalculateTOF(tmp_ve_x, tmp_ve_y, tmp_ve_z, i);
       tmp_resTime_fix->Fill(Readout_hit_time.at(i)-timeflight);
   }

   for(int i = 0; i<150;i++){
      double BinValue = tmp_resTime_fix->GetBinContent(i+1);
      if((BinValue - 5.3) < 8.0)BIN_CUT[i] = true;
      else BIN_CUT[i] = false;
    std::cout<<"i:"<<i<<",bin_cut:"<<BIN_CUT[i]<<std::endl;
   }

   for(int i = 0; i<num_PMT; i++){
    double timeflight = RecTimeLikeAlg::CalculateTOF(tmp_ve_x, tmp_ve_y, tmp_ve_z, i);
    int NBin = int((Readout_hit_time.at(i) - timeflight)/10.0) + 25;
    if(BIN_CUT[NBin] == false) PMT_HIT_CUT[PMT_ID.at(i)] = false;
    else if(BIN_CUT[NBin] == true)PMT_HIT_CUT[PMT_ID.at(i)] = true;
   }
 
   std::cout<<"save tmp_res..."<<std::endl;
   TFile* f = new TFile("tmp.root","recreate");
   f->WriteTObject(tmp_resTime_fix,"tmp_res");

   delete tmp_resTime_fix;*/
   
 //std::cout<<n0<<std::endl;   
  double m_Likelihood = 0;
  //double m_Likelihood = 1.;
  for(int i = 0; i< Total_num_PMT; i++){
     double pmt_pos_x = ALL_PMT_pos.at(i).X()*PMT_R/Ball_R;
     double pmt_pos_y = ALL_PMT_pos.at(i).Y()*PMT_R/Ball_R;
     double pmt_pos_z = ALL_PMT_pos.at(i).Z()*PMT_R/Ball_R;

     double dx = (m_x - pmt_pos_x)/1000;
     double dy = (m_y - pmt_pos_y)/1000;
     double dz = (m_z - pmt_pos_z)/1000;
     
     double r0 = (TMath::Sqrt(m_x*m_x+m_y*m_y+m_z*m_z))/1000;
     double dist = TMath::Sqrt(dx*dx+dy*dy+dz*dz);
    
     double cos_theta = (PMT_R*PMT_R+dist*dist-r0*r0)/(2*PMT_R*dist);
     
     double theta = TMath::ACos(cos_theta);
     
     double f_theta = cos_theta;//fap0+ theta*(fap1 + theta*(fap2 + theta*(fap3 + theta*(fap4+theta*fap5))));//cos_theta;

     double m_expected_PE = f_theta*n0*pmt_r*pmt_r/(4*dist*dist)*TMath::Exp(-dist*m_effective_attenuation) ;//0.0375->dh
     //double m_expected_PE = f_theta*n0*pmt_r*pmt_r/(4*dist*dist)*TMath::Exp(-dist*m_eff);
    
     if(m_Pdf_Value == 0){
        if(PMT_HIT[i]!=0){
            m_Likelihood = m_Likelihood+(m_expected_PE-PMT_HIT[i])+log(PMT_HIT[i]/m_expected_PE)*PMT_HIT[i];
         }
        else
           m_Likelihood = m_Likelihood+m_expected_PE;
     }
     else if(m_Pdf_Value == 1){
        if(!m_FHS){
           if(PMT_HIT[i]!=0){
              m_Likelihood = m_Likelihood+(m_expected_PE-PMT_HIT[i])+log(PMT_HIT[i]/m_expected_PE)*PMT_HIT[i];
           }
           else
             m_Likelihood = m_Likelihood+m_expected_PE;
        }
        else if(m_FHS){
           if(PMT_HIT[i]!=0 && PMT_HIT_CUT[i] == false){
              m_Likelihood = m_Likelihood+(m_expected_PE-PMT_HIT[i])+log(PMT_HIT[i]/m_expected_PE)*PMT_HIT[i];
           }
           else
             m_Likelihood = m_Likelihood+m_expected_PE;
        }
     }
     //if(PMT_HIT[i]!=0){
     //   m_Likelihood = m_Likelihood - log(PoissonValue(PMT_HIT[i],m_expected_PE));
     //}
 
    }

    //m_Likelihood = m_Likelihood + (m_eff-0.026)*(m_eff-0.026)/0.01/0.01;
  // std::cout<<m_Likelihood<<std::endl;
   return m_Likelihood;
}

bool RecTimeLikeAlg::ApplyCorrection()

{
   double R = TMath::Sqrt(tmp_ve_x*tmp_ve_x+tmp_ve_y*tmp_ve_y+tmp_ve_z*tmp_ve_z)/1000;
   double R_3 = R*R*R;  
   double corr;
   if(R_3<3000)
   corr=78.4754+0.353389*R_3-0.00027036*R_3*R_3+1.04109e-07*R_3*R_3*R_3-1.38761e-11*R_3*R_3*R_3*R_3;
   else
   corr=-58271.2+99.8591*R_3-0.0700915*R_3*R_3+2.59412e-05*R_3*R_3*R_3-5.33931e-09*R_3*R_3*R_3*R_3+5.79932e-13*R_3*R_3*R_3*R_3*R_3-2.59749e-17*R_3*R_3*R_3*R_3*R_3*R_3;
   tmp_ve_x = tmp_ve_x-tmp_ve_x*corr/R/1000;
   tmp_ve_y = tmp_ve_y-tmp_ve_y*corr/R/1000;
   tmp_ve_z = tmp_ve_z-tmp_ve_z*corr/R/1000;
   
   return true;
}

bool RecTimeLikeAlg::finalize()
{
    LogInfo  << objName()
        << "   finalized successfully" 
        << std::endl; 
    return true; 
}


