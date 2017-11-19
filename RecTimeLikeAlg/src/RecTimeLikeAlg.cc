#include "RecTimeLikeAlg.h"
#include "TMath.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TF1.h"
#include "TString.h"
#include "TStopwatch.h"


#include <boost/filesystem.hpp>

#include <algorithm>

namespace fs = boost::filesystem;
using namespace ROOT::Minuit2;

RecTimeLikeAlg::RecTimeLikeAlg(EnergyTimeHitVector& AllDetected)
    :m_iEvt(-1),
      LS_R(17.7*m),
      ChaCenRec_ratio(1.2),
      fAllDetected(AllDetected)
{
    std::string base = getenv("HOME");
    base += "/JUNO/simjuno/RecTimeLikeAlg";
    File_path = (fs::path(base)/"share").string();

    G4cout<<"LS_R:"<<LS_R/m<< " m" << G4endl;
    G4cout<<"File_Path:"<<File_path<<G4endl;
    Time_1hit = 0;
}

RecTimeLikeAlg::~RecTimeLikeAlg()
{
    delete Time_1hit;
}

bool RecTimeLikeAlg::initialize()
{

//    MyFCN* fcn = new MyFCN(this);
    Load_LikeFun();
    G4cout   << "   initialized successfully"
             << G4endl;
    return true;

}

bool RecTimeLikeAlg::execute()
{
    ++m_iEvt;

    G4cout << "---------------------------------------" << G4endl;
    G4cout << "Processing event " << m_iEvt << G4endl;

    min_hit_time = fAllDetected[0]->GetPostStepTime()/ns;
    for(EnergyTimeHitVector::iterator it = fAllDetected.begin();
        it != fAllDetected.end(); ++it){
        G4double min_time_tmp = (*it)->GetPostStepTime()/ns;
        if(min_hit_time > min_time_tmp)
            min_hit_time = min_time_tmp;
    }

    G4cout << "num of Hits for RecTimeLikeAlg:"<<fAllDetected.size() <<G4endl;
    TStopwatch timer;
    timer.Start();

    RecTimeLikeAlg::ChargeCenterRec();
    RecTimeLikeAlg::GridSearch();

    G4double x_fit = tmp_ve_x;
    G4double y_fit = tmp_ve_y;
    G4double z_fit = tmp_ve_z;
    G4double t_fit = tmp_t_zero;
    G4double n_fit;
    G4double E_rec;
    G4cout <<"ChaCenRec:("<<ChaCenRec.x()<<","<<ChaCenRec.y()<<","<<ChaCenRec.z()<<")"<<G4endl;

    //    fun_poisson=new TF1("fun_poisson","TMath::Poisson(x,[0])",-5,20);

    //    tmp_resTime_fix = new TH1D("","",150,-250,1250);
    //    for(EnergyTimeHitVector::iterator it=fAllDetected.begin();
    //        it!=fAllDetected.end();++it){
    //        G4double timeflight = RecTimeLikeAlg::CalculateTOF(G4ThreeVector(x_fit,y_fit,z_fit),
    //                                                           (*it)->GetPostPosition());
    //        tmp_resTime_fix->Fill((*it)->GetPostStepTime()-timeflight-min_hit_time);
    //    }

    //    recminuit->SetParameter(0,"n",5000, 0.5,0, 100000);
    //    recminuit->SetParameter(1,"xpos",x_fit,1000,-18000,18000);
    //    recminuit->SetParameter(2,"ypos",y_fit,1000,-18000,18000);
    //    recminuit->SetParameter(3,"zpos",z_fit,1000,-18000,18000);
    
    //    recminuit->FixParameter(1);
    //    recminuit->FixParameter(2);
    //    recminuit->FixParameter(3);
    //    recminuit->CreateMinimizer();

    //    G4int ief = recminuit->Minimize();

    //    n_fit = recminuit->GetParameter(0);
    //att_length = recminuit->GetParameter(4);
    //Non-linearity Correction for positron
    //    G4double  non_li_parameter[4] = {0.122495, 1.04074, 1.78087, 0.00189743};
    //    G4double  correction_par[6] = {155.691, -0.187317, 9.01254e-05, -2.13865e-08, 2.50316e-12, -1.1577e-16};

    //    f_non_li_positron = new TF1("pos","1.022*(([1]+[3]*(x-1.022))*(x-1.022)/(1+[0]*exp(-[2]*(x-1.022)))+0.935802158)/0.935802",0,12);
    //    f_non_li_positron->SetParameters(non_li_parameter);
    //    f_correction = new TF1("corr","[0]+[1]*x+[2]*x*x+[3]*x*x*x+[4]*x*x*x*x+[5]*x*x*x*x*x",0,5600);
    //    f_correction->SetParameters(correction_par);

    //G4cout<<"n_fit is"<<n_fit<<G4endl;
    //n_fit = n_fit/m_Energy_Scale;
    //G4cout<<"Energy_Scale"<<m_Energy_Scale<<G4endl;
    G4double R = TMath::Sqrt(x_fit*x_fit+y_fit*y_fit+z_fit*z_fit)/1000;
    G4double R_3 = R*R*R;
    /*energy non-uniformity correction*/
    //    E_rec = 2.005*(n_fit/m_Energy_Scale)/Energy_correction(R);
    /**non-linearity correction**/
    //    E_rec = f_non_li_positron->GetX(E_rec);

    timer.Stop();
    G4double time = timer.RealTime();
    G4cout<<"==========================================================="<<G4endl;
    G4cout<<"The Reconstructed x is "<<x_fit<<G4endl;
    G4cout<<"The Reconstructed y is "<<y_fit<<G4endl;
    G4cout<<"The Reconstructed z is "<<z_fit<<G4endl;
    G4cout<<"The Reconstructed n is "<<n_fit<<G4endl;
    G4cout<<"The Reconstructed To is "<<t_fit<<G4endl;
    G4cout<<"The Reconstructed energy is "<<E_rec<<G4endl;
    G4cout<<"The Reconstruction Process Cost "<<time<<G4endl;
    G4cout<<"The Complete Reconstrution Process is Completed!"<<G4endl;
    G4cout<<"==========================================================="<<G4endl;

    //    recminuit->Clear();
    //    delete f_non_li_positron;
    //    delete f_correction;
    //    delete fun_poisson;
    return true;

}

bool RecTimeLikeAlg::Load_LikeFun()
{  
    fs::path s(File_path);
    Time_1hit = new TFile(TString((s/"pdf_n1.root").string()));

    if(!Time_1hit)
        G4cout  << "Failed to get Likelihood Function File!" << G4endl;

    pdf_1hit = (TH1D*)Time_1hit->Get("tim");

    return true;

}


//G4double RecTimeLikeAlg::PoissonValue(G4double x,G4double par){
//    fun_poisson->SetParameter(0,par);
//    //std::cout<<">>>call Poisson Fun,mean :"<<par<<G4endl;
//    return fun_poisson->Eval(x);
//}

bool RecTimeLikeAlg::ChargeCenterRec()
{
    G4ThreeVector v_sum(0,0,0);
    for(EnergyTimeHitVector::iterator it=fAllDetected.begin();
        it != fAllDetected.end(); ++it)
        v_sum += (*it)->GetPostPosition();
    if(fAllDetected.size())
        return false;
    else{
        ChaCenRec = v_sum/fAllDetected.size();
        return true;
    }
}

G4double RecTimeLikeAlg::HittimeGoodness(G4double T_zero, G4ThreeVector vert)
{
    G4double Goodness = 0;

    for(EnergyTimeHitVector::iterator it = fAllDetected.begin();
        it != fAllDetected.end(); ++it){
        G4ThreeVector det_r = (*it)->GetPostPosition();
        G4double timeflight = RecTimeLikeAlg::CalculateTOF(vert,det_r);
        relaTime=(*it)->GetPostStepTime()/ns-timeflight+T_zero-min_hit_time;

        if(relaTime>-30&&relaTime<300){//by default it is 300 ns
            G4int BinTime = (G4int)((relaTime+200)*200/7);
            G4double pdfValue = pdf_1hit->GetBinContent(BinTime);
            if(pdfValue!=0){
                Goodness = Goodness-TMath::Log(pdfValue);
            }
            else{
                Goodness = Goodness+0;
            }

        }
    }
    return Goodness/fAllDetected.size();
}

//G4double RecTimeLikeAlg::Energy_correction(G4double x){
//    G4double r3 = pow(x,3);
//    G4int prebin = G4int((r3-6.)/12.) + 1;
//    G4int nextbin = G4int((r3-6.)/12.) + 2;
//    G4double prebincenter   = h_correction->GetBinCenter(prebin);
//    G4double prebincontent  = h_correction->GetBinContent(prebin);
//    G4double nextbincontent = h_correction->GetBinContent(nextbin);
//    G4double result = prebincontent + (nextbincontent - prebincontent)*(r3-prebincenter)/12.;
//    return result;
//}

bool RecTimeLikeAlg::GridSearch()
{  m_like_time=1000.0;
    tmp_t_zero = 0;
    for(G4int init_val = 0;init_val < 1;init_val++){
        //Begin with Charge Center Reconstruction;
        tmp_ve_x =(1.2+init_val*0.1)*ChaCenRec.x()/mm;
        tmp_ve_y =(1.2+init_val*0.1)*ChaCenRec.y()/mm;
        tmp_ve_z =(1.2+init_val*0.1)*ChaCenRec.z()/mm;
        //   std::cout<<tmp_ve_x<<G4endl;
        //tag for grid search
        G4int tag_x = 4;
        G4int tag_y = 4;
        G4int tag_z = 4;
        G4int tag_t = 10;

        G4double delta = 1e10;

        G4double step_length = 1000;

        for(G4int iteration = 0; iteration < 100; iteration++){//100
            if(step_length<0.1) break;
            for(G4int bin_t = -4;bin_t<5;bin_t++){//-4,5
                for(G4int bin_x = -1; bin_x<2; bin_x++){//-1,2
                    for(G4int bin_y = -1; bin_y<2; bin_y++){
                        for(G4int bin_z = -1; bin_z<2; bin_z++){
                            //	std::cout<<"tst binx:"<<bin_x<<"  biny:"<<bin_y<<"  binz:"<<bin_z<<G4endl;
                            G4double tmp_x = tmp_ve_x+bin_x*step_length;
                            G4double tmp_y = tmp_ve_y+bin_y*step_length;
                            G4double tmp_z = tmp_ve_z+bin_z*step_length;
                            //       std::cout<<"vtx:"<<tmp_x<<","<<tmp_y<<","<<tmp_z<<","<<tmp_t_zero+bin_t*step_length/100.0<<G4endl;
                            if((tmp_x*tmp_x+tmp_y*tmp_y+tmp_z*tmp_z)<17700.*17700.){
                                G4double d = HittimeGoodness(tmp_t_zero+bin_t*step_length/100.0,
                                                             G4ThreeVector(
                                                                 tmp_ve_x+bin_x*step_length,
                                                                 tmp_ve_y+bin_y*step_length,
                                                                 tmp_ve_z+bin_z*step_length)
                                                             );
                                //	std::cout<<"tst binx:"<<bin_x<<"  biny:"<<bin_y<<"  binz:"<<bin_z<<G4endl;
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
            tmp_ve_x = tmp_ve_x + static_cast<G4double>(tag_x*step_length);
            tmp_ve_y = tmp_ve_y + static_cast<G4double>(tag_y*step_length);
            tmp_ve_z = tmp_ve_z + static_cast<G4double>(tag_z*step_length);
            tmp_t_zero = tmp_t_zero + static_cast<G4double>(tag_t*step_length/100.0);

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
        //  G4cout<<delta<<G4endl;
    }
    tmp_ve_x = sign_x;
    tmp_ve_y = sign_y;
    tmp_ve_z = sign_z;
    tmp_t_zero = sign_t;
    return true;
}


G4double RecTimeLikeAlg::CalculateTOF(G4ThreeVector v0, G4ThreeVector v1)
{
    return (v0-v1).r()*1.54/CLHEP::c_light/ns;
}

//G4double RecTimeLikeAlg::Calculate_Energy_Likelihood(G4double n0,
//                                                     G4double m_x,
//                                                     G4double m_y,
//                                                     G4double m_z)
//{
//    G4double m_Likelihood = 0;
//    for(G4int i = 0; i< Total_num_PMT; i++){
//        G4double pmt_pos_x = ALL_PMT_pos.at(i).X()*PMT_R/Ball_R;
//        G4double pmt_pos_y = ALL_PMT_pos.at(i).Y()*PMT_R/Ball_R;
//        G4double pmt_pos_z = ALL_PMT_pos.at(i).Z()*PMT_R/Ball_R;

//        G4double dx = (m_x - pmt_pos_x)/1000;
//        G4double dy = (m_y - pmt_pos_y)/1000;
//        G4double dz = (m_z - pmt_pos_z)/1000;

//        G4double r0 = (TMath::Sqrt(m_x*m_x+m_y*m_y+m_z*m_z))/1000;
//        G4double dist = TMath::Sqrt(dx*dx+dy*dy+dz*dz);

//        G4double cos_theta = (PMT_R*PMT_R+dist*dist-r0*r0)/(2*PMT_R*dist);

//        G4double theta = TMath::ACos(cos_theta);

//        G4double f_theta = cos_theta;//fap0+ theta*(fap1 + theta*(fap2 + theta*(fap3 + theta*(fap4+theta*fap5))));//cos_theta;

//        G4double m_expected_PE = f_theta*n0*pmt_r*pmt_r/(4*dist*dist)*TMath::Exp(-dist*m_effective_attenuation) ;//0.0375->dh
//        if(PMT_HIT[i]!=0){
//            m_Likelihood = m_Likelihood+(m_expected_PE-PMT_HIT[i])+log(PMT_HIT[i]/m_expected_PE)*PMT_HIT[i];
//        }
//        else
//            m_Likelihood = m_Likelihood+m_expected_PE;
//    }
//    return m_Likelihood;
//    return n0+m_x+m_y+m_z;
//}

bool RecTimeLikeAlg::finalize()
{
    G4cout   << "   finalized successfully"
             << G4endl;
    return true;
}


