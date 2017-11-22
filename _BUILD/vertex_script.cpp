

double myfunc(double* x,double* par){
    double ratio = TMath::Sqrt(par[1]*par[1]+par[2]*par[2]+par[3]*par[3])/17700.;
    double exp = 0;
    exp = par[0]*0.5*(1-ratio*x[0])/TMath::Power((1+ratio*ratio-2*ratio*x[0]),3./2)*par[4];
    return exp;
}


int vertex_script(){
gROOT->Reset();
TFile *f = new TFile("toBeDelete.root");
TTree* t = (TTree*)f->Get("evt");
TLeaf* bx = (TLeaf*)t->GetLeaf("X_Init");
TLeaf* by = (TLeaf*)t->GetLeaf("Y_Init");
TLeaf* bz = (TLeaf*)t->GetLeaf("Z_Init");
TLeaf* bx1 = (TLeaf*)t->GetLeaf("X_Det");
TLeaf* by1 = (TLeaf*)t->GetLeaf("Y_Det");
TLeaf* bz1 = (TLeaf*)t->GetLeaf("Z_Det");
TLeaf* nr = (TLeaf*)t->GetLeaf("nRayleigh");

double x_init,y_init, z_init;
TH1D* h = new TH1D("h",";cos(#theta);",100,-1,1.);
for(int i=0;i<t->GetEntries();i++){
    t->GetEntry(i);
    double x0 = bx->GetValue(0);
    double y0 = by->GetValue(0);
    double z0 = bz->GetValue(0);
    double x1 = bx1->GetValue(0);
    double y1 = by1->GetValue(0);
    double z1 = bz1->GetValue(0);
    int nr0 = nr->GetValue(0);
    if(i==0){
        x_init = x0;
        y_init = y0;
        z_init = z0;
    }
    if(nr0 != 0)
        continue;
    TVector3 v0(x0,y0,z0);
    TVector3 v1(x1,y1,z1);
    double cos_theta = 0;
    if(x0 ==0 && y0 == 0 && z0 == 0){
        cos_theta = v1.CosTheta();
    }
    else{
        double angle = v1.Angle(v0);
        if(angle <0 || angle > TMath::Pi()){
            cout << "out of range" << endl;
            return -1;
        }
        else
            cos_theta = TMath::Cos(v1.Angle(v0));
    }
    h->Fill(cos_theta);
}

TCanvas* c = new TCanvas("c","c",800,600);
h->Draw();

double n_straight = t->Draw("nRayleigh","nRayleigh==0","goff");

TF1* f1 = new TF1("f1",myfunc,-1,1,5);
f1->FixParameter(0,n_straight);
f1->FixParameter(1,x_init);
f1->FixParameter(2,y_init);
f1->FixParameter(3,z_init);
double binwidth = h->GetBinWidth(1);
f1->FixParameter(4,binwidth);

h->GetListOfFunctions()->Add(f1);
//h->Fit("f1","","",1-xi,1+xi);

return 0;

}
