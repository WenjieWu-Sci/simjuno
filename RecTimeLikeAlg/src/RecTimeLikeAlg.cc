#include "RecTimeLikeAlg.h"
#include "TMath.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TF1.h"
#include "TGraph.h"
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
    Load_LikeFun();
    G4cout   << "   initialized successfully"
             << G4endl;
    return true;

}

bool RecTimeLikeAlg::execute()
{
    ++m_iEvt;

    G4cout << "---------------------------------------" << G4endl;
    G4cout << "Processing Run " << m_iEvt << G4endl;

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
    G4double n_fit = 1e4;

    f_tmp = new TFile("test.root","recreate");
    MyFCN myfcn(this);
    MnUserParameters upar;
    upar.Add("n0",n_fit,1000.);
//    upar.Add("x",ChaCenRec.x(),10000.);
//    upar.Add("y",ChaCenRec.y(),10000.);
//    upar.Add("z",ChaCenRec.z(),10000.);

    upar.Add("x",x_fit,100.);
    upar.Add("y",y_fit,100.);
    upar.Add("z",z_fit,100.);

//    upar.SetLimits("n0",0,1e8);
//    upar.SetLimits("x",-LS_R,LS_R);
//    upar.SetLimits("y",-LS_R,LS_R);
//    upar.SetLimits("z",-LS_R,LS_R);

    MnMigrad migrad(myfcn, upar);

    migrad.Fix(1);
    migrad.Fix(2);
    migrad.Fix(3);

//    MnScan scan(myfcn, upar);
//    std::vector<std::pair<double,double>> points1 = scan.Scan(1,2000);
//    std::vector<std::pair<double,double>> points2 = scan.Scan(2,2000);
//    std::vector<std::pair<double,double>> points3 = scan.Scan(3,2000);

    MnPrint::SetLevel(6);
    G4cout << "Print Level is " << MnPrint::Level() << G4endl;

    FunctionMinimum min = migrad(5000);
    G4cout << min << G4endl;

    G4cout <<"ChaCenRec:("<<ChaCenRec.x()/m<<"m,"<<ChaCenRec.y()/m<<"m,"<<ChaCenRec.z()/m<<"m)"<<G4endl;
    timer.Stop();
    G4double time = timer.RealTime();
    G4cout<<"==========================================================="<<G4endl;
    G4cout<<"The Reconstructed x is "<<x_fit/m <<" m"<<G4endl;
    G4cout<<"The Reconstructed y is "<<y_fit/m <<" m"<<G4endl;
    G4cout<<"The Reconstructed z is "<<z_fit/m <<" m"<<G4endl;
    G4cout<<"The Reconstructed n is "<<n_fit <<G4endl;
    G4cout<<"The Reconstructed To is "<<t_fit/ns << " ns"<<G4endl;
    G4cout<<"The Reconstruction Process Cost "<<time<<G4endl;
//    G4cout<<"The Reconstruction chi2 minimum is " << min.UserState().Value(0) << G4endl;
    G4cout<<"The Complete Reconstrution Process is Completed!"<<G4endl;
    G4cout<<"==========================================================="<<G4endl;

//    TGraph* g1 = new TGraph(points1.size());
//    for(std::vector<std::pair<double,double>>::iterator it = points1.begin(); it!=points1.end(); ++it)
//    {
//        g1->SetPoint(g1->GetN(),it->first,it->second);
//    }
//    g1->SetTitle(TString::Format("g1 %d step",points1.size()));
//    g1->SetMarkerStyle(2);

//    TGraph* g2 = new TGraph(points2.size());
//    for(std::vector<std::pair<double,double>>::iterator it = points2.begin(); it!=points2.end(); ++it)
//    {
//        g2->SetPoint(g2->GetN(),it->first,it->second);
//    }
//    g2->SetTitle(TString::Format("g2 %d step",points2.size()));
//    g2->SetMarkerStyle(2);

//    TGraph* g3 = new TGraph(points3.size());
//    for(std::vector<std::pair<double,double>>::iterator it = points3.begin(); it!=points3.end(); ++it)
//    {
//        g3->SetPoint(g3->GetN(),it->first,it->second);
//    }
//    g3->SetTitle(TString::Format("g3 %d step",points3.size()));
//    g3->SetMarkerStyle(2);
//    f_tmp->cd();
//    g1->Write();
//    g2->Write();
//    g3->Write();

//    delete g1;
//    delete g2;
//    delete g3;

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

bool RecTimeLikeAlg::ChargeCenterRec()
{
    G4ThreeVector v_sum(0,0,0);
    for(EnergyTimeHitVector::iterator it=fAllDetected.begin();
        it != fAllDetected.end(); ++it)
        v_sum += (*it)->GetPostPosition();
    if(!fAllDetected.size())
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

bool RecTimeLikeAlg::GridSearch()
{  m_like_time=1000.0;
    G4cout << "Enter grid search " << G4endl;
    tmp_t_zero = 0;
    for(G4int init_val = 0;init_val < 1;init_val++){
        //Begin with Charge Center Reconstruction;
        tmp_ve_x =(1.2+init_val*0.1)*ChaCenRec.x()/mm;
        tmp_ve_y =(1.2+init_val*0.1)*ChaCenRec.y()/mm;
        tmp_ve_z =(1.2+init_val*0.1)*ChaCenRec.z()/mm;
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
                            G4double tmp_x = tmp_ve_x+bin_x*step_length;
                            G4double tmp_y = tmp_ve_y+bin_y*step_length;
                            G4double tmp_z = tmp_ve_z+bin_z*step_length;
                            if((tmp_x*tmp_x+tmp_y*tmp_y+tmp_z*tmp_z)<17700.*17700.){
                                G4double d = HittimeGoodness(tmp_t_zero+bin_t*step_length/100.0,
                                                             G4ThreeVector(
                                                                 tmp_ve_x+bin_x*step_length,
                                                                 tmp_ve_y+bin_y*step_length,
                                                                 tmp_ve_z+bin_z*step_length)
                                                             );
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

G4double RecTimeLikeAlg::Calculate_Energy_Likelihood(G4double n0,
                                                     G4double m_x,
                                                     G4double m_y,
                                                     G4double m_z)
{
    f_tmp->cd();
    G4double m_Likelihood = 0;
    TH1D* hcos = new TH1D("hcos","hcos",1000,-1,1);
    G4ThreeVector m_v(m_x,m_y,m_z);
    if(m_v.r()>LS_R){
        delete hcos;
        return 1e8;
    }
    for(EnergyTimeHitVector::iterator it=fAllDetected.begin();
        it != fAllDetected.end(); ++it){
        G4ThreeVector m_hit = (*it)->GetPostPosition();
        G4double theta;
        if(!m_v.r())
            theta = m_hit.theta();
        else
            theta = m_v.angle(m_hit)*rad;
        if(theta <= pi && theta>0 ){
            G4double cos_theta = TMath::Cos(theta);
            hcos->SetTitle(TString::Format("x = %g, y = %g, z = %g",m_x,m_y,m_z));
            hcos->Fill(cos_theta);
        }
        else{
            G4cout << "theta out of range: " << theta << G4endl;
        }
    }
    for(G4int i=1;i<=hcos->GetNbinsX();i++){
        G4double obs=(G4double)hcos->GetBinContent(i);
        if(!obs) continue;
        G4double cos_theta = hcos->GetBinCenter(i);
        G4double ratio = m_v.r()/LS_R;
        G4double exp = n0*0.5*(1-ratio*cos_theta)/TMath::Power((1+ratio*ratio-2*ratio*cos_theta),3./2)*hcos->GetBinWidth(i);
        G4double tmp = (obs-exp)/hcos->GetBinError(i);
        m_Likelihood += tmp*tmp;
    }
    TF1* f = new TF1("PDF",PhotoPDF,-1.,1.,5);
    f->SetParameters(n0,m_x,m_y,m_z,2./hcos->GetNbinsX());
    hcos->GetListOfFunctions()->Add(f);
    hcos->Write();
    delete hcos;
    return m_Likelihood;
}

bool RecTimeLikeAlg::finalize()
{
    G4cout   << "   finalized successfully"
             << G4endl;
    f_tmp->Close();
    delete f_tmp;
    return true;
}

double PhotoPDF(double *x, double *par)
{
    G4double ratio = TMath::Sqrt(par[1]*mm*par[1]*mm + par[2]*mm*par[2]*mm +par[3]*mm*par[3]*mm)/(17.7*m);
    G4double exp = par[0]*0.5*(1-ratio*x[0])/TMath::Power((1+ratio*ratio-2*ratio*x[0]),3./2)*par[4];
    return exp;
}
