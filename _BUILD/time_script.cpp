

double myfunc(double* x,double* par){
    double ratio = TMath::Sqrt(par[1]*par[1]+par[2]*par[2]+par[3]*par[3])/17700.;
    double exp = 0;
    if(ratio == 0)
        exp = 0;
    else
        exp = par[0]*0.25*(1-ratio*ratio+x[0]*x[0])/(TMath::Abs(ratio)*x[0]*x[0])*par[4];
    return exp;
}


int time_script(){
gROOT->Reset();
TFile *f = new TFile("toBeDelete.root");
TTree* t = (TTree*)f->Get("evt");
TLeaf* bx = (TLeaf*)t->GetLeaf("X_Init");
TLeaf* by = (TLeaf*)t->GetLeaf("Y_Init");
TLeaf* bz = (TLeaf*)t->GetLeaf("Z_Init");

t->GetEntry(0);
double x0 = bx->GetValue(0);
double y0 = by->GetValue(0);
double z0 = bz->GetValue(0);

double chi = TMath::Sqrt(x0*x0+y0*y0+z0*z0)/17700; 

TCanvas* c = new TCanvas("c","c",800,600);
TH1D* h = new TH1D("h",";#xi;",100,1.-chi,1.+chi);
t->Draw("Time_Det*1e-9*2.99792458e+8/1.54/17.7>>h","nRayleigh==0");

double n_straight = t->Draw("nRayleigh","nRayleigh==0","goff");

TF1* f1 = new TF1("f1",myfunc,1.-chi,1.+chi,5);
f1->FixParameter(0,n_straight);
f1->FixParameter(1,x0);
f1->FixParameter(2,y0);
f1->FixParameter(3,z0);
double binwidth = h->GetBinWidth(1);
f1->FixParameter(4,binwidth);

h->GetListOfFunctions()->Add(f1);

return 0;

}
