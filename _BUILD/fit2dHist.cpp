//
//+   Example to fit two histograms at the same time via TVirtualFitter
//
// To execute this tutorial, you can do:
//
// root > .x fit2dHist.C  (executing via CINT, slow)
//   or
// root > .x fit2dHist.C+     (executing via ACLIC , fast, with Minuit)
// root > .x fit2dHist.C+(2)  (executing via ACLIC , fast, with Minuit2)
//   or using the option to fit independently the 2 histos
// root > .x fit2dHist.C+(10) (via ACLIC, fast, independent fits with Minuit)
// root > .x fit2dHist.C+(12) (via ACLIC, fast, independent fits with Minuit2)
//
// Note that you can also execute this script in batch with eg,
//  root -b -q "fit2dHist.C+(12)"
//
// or execute interactively from the shell
//  root fit2dHist.C+
//  root "fit2dHist.C+(12)"
//
// Authors: Lorenzo Moneta, Rene Brun 18/01/2006

#include "TH1D.h"
#include "TF1.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TRandom3.h"
#include "TVirtualFitter.h"
#include "TList.h"
#include "TMath.h"
#include "TLeaf.h"
#include "TFile.h"
#include "TVector3.h"
#include "assert.h"
#include "TApplication.h"

#include <iostream>

// data need to be globals to be visible by fcn
TH1D *h1, *h2;
Int_t npfits;
Int_t totalnum(0);
double x_init(0.),y_init(0.), z_init(0.);
const UInt_t num_par = 5;
bool option_fix = false;
bool option_allphoton = false;

using namespace std;

double timefunc(double* x,double* par){
    double ratio = TMath::Sqrt(par[1]*par[1]+par[2]*par[2]+par[3]*par[3])/17700.;
    double exp = 0;
    double xi = x[0]-par[4]*1e-9*2.99792458e+8/1.54/17.7;
    if(ratio == 0)
        exp = 0;
    else
        exp = par[0]*0.25*(1-ratio*ratio+xi*xi)/(TMath::Abs(ratio)*xi*xi)*(h1->GetBinWidth(h1->FindBin(xi)));
    return exp;
}

double vertexfunc(double* x,double* par){
    double ratio = TMath::Sqrt(par[1]*par[1]+par[2]*par[2]+par[3]*par[3])/17700.;
    double exp = 0;
    exp = par[0]*0.5*(1-ratio*x[0])/TMath::Power((1+ratio*ratio-2*ratio*x[0]),3./2)*(h2->GetBinWidth(h2->FindBin(x[0])))+0.*par[4];
    return exp;
}

void myFcn(Int_t & /*nPar*/, Double_t * /*grad*/ , Double_t &fval, Double_t *p, Int_t /*iflag */  )
{
    TAxis *xaxis1  = h1->GetXaxis();
    TAxis *xaxis2  = h2->GetXaxis();

    int nbinX1 = h1->GetNbinsX();
    int nbinX2 = h2->GetNbinsX();

    double chi2 = 0;
    double x[1];
    double tmp;
    npfits = 0;
    for (int ix = 1; ix <= nbinX1; ++ix) {
        x[0] = xaxis1->GetBinCenter(ix);
        if ( h1->GetBinError(ix) > 0 ) {
            tmp = (h1->GetBinContent(ix) - timefunc(x,p))/h1->GetBinError(ix); // time function
            chi2 += tmp*tmp;
            npfits++;
        }
    }
    for (int ix = 1; ix <= nbinX2; ++ix) {
        x[0] = xaxis2->GetBinCenter(ix);
        if ( h2->GetBinError(ix) > 0 ) {
            tmp = (h2->GetBinContent(ix) - vertexfunc(x,p))/h2->GetBinError(ix); // vertex function
            chi2 += tmp*tmp;
            npfits++;
        }
    }
    fval = chi2;
}

void FillHisto(TH1D ** h, TTree* t) {
    assert(*h);
    assert(*(h+1));
    TLeaf* bx1 = (TLeaf*)t->GetLeaf("X_Det");
    TLeaf* by1 = (TLeaf*)t->GetLeaf("Y_Det");
    TLeaf* bz1 = (TLeaf*)t->GetLeaf("Z_Det");
    TLeaf* td = (TLeaf*)t->GetLeaf("Time_Det");
    TLeaf* nr = (TLeaf*)t->GetLeaf("nRayleigh");
    TVector3 v0(x_init,y_init,z_init);

    for(int i=0;i<t->GetEntries();i++){
        t->GetEntry(i);
        double x1 = bx1->GetValue(0);
        double y1 = by1->GetValue(0);
        double z1 = bz1->GetValue(0);
        double td1 = td->GetValue(0);
        int nr0 = nr->GetValue(0);
        if(nr0 && !option_allphoton)
            continue;
        TVector3 v1(x1,y1,z1);
        double cos_theta = 0;
        double xi = td1*1e-9*2.99792458e+8/1.54/17.7;
        if(!v0.Mag()){
            cos_theta = v1.CosTheta();
        }
        else{
            double angle = v1.Angle(v0);
            if(angle <0 || angle > TMath::Pi()){
                cout << "out of range" << endl;
                assert(0);
            }
            else
                cos_theta = TMath::Cos(v1.Angle(v0));
        }
        totalnum++;
        h[0]->Fill(xi);
        h[1]->Fill(cos_theta);
    }
}

int main(int argc, char** argv) {
    TApplication theApp("tapp", &argc, argv);
    if(argc>1){
        TString argv1(argv[1]);
        if(argv1=="fix")
            option_fix = true;
        TString argv2(argv[2]);
        if(argv2=="all")
            option_allphoton = true;
    }

    // create two histograms

    TFile* f = new TFile("toBeDelete.root");
    if(!f->IsOpen())
        return -1;
    TTree* t = (TTree*)f->Get("evt");
    TLeaf* lx0 = (TLeaf*)t->GetLeaf("X_Init");
    TLeaf* ly0 = (TLeaf*)t->GetLeaf("Y_Init");
    TLeaf* lz0 = (TLeaf*)t->GetLeaf("Z_Init");
    t->GetEntry(0);
    x_init = lx0->GetValue(0);
    y_init = ly0->GetValue(0);
    z_init = lz0->GetValue(0);

    int nbx1 = 100;
    int nbx2 = 100;

    double ratio = TMath::Sqrt(x_init*x_init+y_init*y_init+z_init*z_init)/17700;

    double xlow1 = 1.-ratio;
    double xup1 = 1.+ratio;
    double xlow2 = -1.;
    double xup2 = 1.;

    h1 = new TH1D("h1","Time Spectrum;#xi;",nbx1,xlow1,xup1);
    h2 = new TH1D("h2","Zenith Spectrum;cos(#theta);",nbx2,xlow2,xup2);

    TH1D** h = new TH1D* [2];
    h[0] = h1;
    h[1] = h2;

    FillHisto(h,t);

    double totalnum_d = static_cast<double>(totalnum);
    double iniParams[num_par] = { totalnum_d, x_init, y_init, z_init, 0. };
    // create fit function
    TF1 * f1 = new TF1("time_fit",timefunc,xlow1,xup1,num_par);
    f1->SetParameters(iniParams);
    TF1 * f2 = new TF1("vertex_fit",vertexfunc,xlow2,xup2,num_par);
    f2->SetParameters(iniParams);

    // fill data structure for fit (coordinates + values + errors)
    std::cout << "Do global fit" << std::endl;
    // fit now all the function together

    //The default minimizer is Minuit, you can also try Minuit2
    TVirtualFitter::SetDefaultFitter("Minuit");
    TVirtualFitter * minuit = TVirtualFitter::Fitter(0,num_par);
    for (UInt_t i = 0; i < num_par; ++i) {
        double err = f1->GetParameter(i)?f1->GetParameter(i)/100.:10.;
        minuit->SetParameter(i, f1->GetParName(i), f1->GetParameter(i),err,0,0);
    }
    minuit->SetFCN(myFcn);

    double arglist[100];
    arglist[0] = 3;
    // set print level
    minuit->ExecuteCommand("SET PRINT",arglist,1);

    // minimize
    arglist[0] = 5000; // number of function calls
    arglist[1] = 0.01; // tolerance
    if(option_fix)
        for (UInt_t i = 0; i < num_par; ++i) {
            minuit->FixParameter(i);
        }
    minuit->ExecuteCommand("MIGRAD",arglist,2);

    //get result
    double minParams[num_par];
    double parErrors[num_par];
    for (UInt_t i = 0; i < num_par; ++i) {
        minParams[i] = minuit->GetParameter(i);
        parErrors[i] = minuit->GetParError(i);
    }
    double chi2, edm, errdef;
    int nvpar, nparx;
    minuit->GetStats(chi2,edm,errdef,nvpar,nparx);

    f1->SetParameters(minParams);
    f2->SetParameters(minParams);
    f1->SetParErrors(parErrors);
    f2->SetParErrors(parErrors);
    f1->SetChisquare(chi2);
    f2->SetChisquare(chi2);
    int ndf = npfits-nvpar;
    f1->SetNDF(ndf);
    f2->SetNDF(ndf);

    // add to list of functions
    h1->GetListOfFunctions()->Add(f1);
    h2->GetListOfFunctions()->Add(f2);

    // Create a new canvas.
    TCanvas * c1 = new TCanvas("c1","c1",100,10,900,800);
    c1->Divide(1,2);
    gStyle->SetOptFit();
    gStyle->SetStatY(0.6);

    c1->cd(1);
    h1->Draw();
    f1->SetRange(xlow1,xup1);
    f1->DrawCopy("same");
    c1->cd(2);
    h2->Draw("");
    f2->SetRange(xlow2,xup2);
    f2->DrawCopy("same");
    theApp.Run();

    delete h1;
    delete h2;
    delete [] h;
    h = NULL;

    return 0;
}
