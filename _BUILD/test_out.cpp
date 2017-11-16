#include <iostream>
#include <algorithm>
#include <TFile.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TLegend.h>
#include <TH1D.h>
#include <TTree.h>
#include <TMath.h>
#include <TApplication.h>
#include <TLeaf.h>

using namespace std;

int main(int argc, char* argv[]){

const Int_t COLORS[]={1,2,3,4,5,6,7,8,9,11,40,41,42,43,44,45,46,47,48,49};

TApplication* rootapp = new TApplication("rootapp",&argc,argv);

TFile* f = new TFile("basic_all.root","open");
TCanvas* c1 = new TCanvas("c1","c1",800,600);
c1->cd();
TTree* evt = (TTree*)f->Get("evt");
Int_t evtNUM = evt->GetEntries();
Int_t nRay=0;
for(int i=0;i<evtNUM;i++){
    evt->GetEntry(i);
    Int_t nDet = evt->GetLeaf("nDetected")->GetValue();
    for(int j=0;j<nDet;j++){
        Int_t nR_tmp = evt->GetLeaf("nRayleigh")->GetValue(j);
        if(nR_tmp > nRay)
            nRay = nR_tmp;
    }
}

const Int_t max=nRay;

gStyle->SetOptStat(false);
TLegend* t = new TLegend(0.6,0.6,0.9,0.9);

for(int i=0;i<=max;i++){
    evt->Draw(Form("Time_Det>>h%d(640,60,700)",i),Form("nRayleigh==%d",i),"goff");
}
for(int i=0;i<=max;i++){
    TH1D* tmp=(TH1D*)gDirectory->Get(Form("h%d",i));
    if(tmp->Integral()==0)
        continue;
    if(i==0){
        tmp->Draw("");
        tmp->SetTitle(";Arrival Time/ns;#");
    }
    else
        tmp->Draw("sames");
    tmp->SetFillStyle(3002);
    tmp->SetFillColor(COLORS[i]);
    tmp->SetLineColor(COLORS[i]);
    t->AddEntry(tmp,Form("nRayleigh=%d, Average Time=%.1f ns, #=%.3g",i,tmp->GetMean(),tmp->Integral()),"lf");
}
t->Draw();
c1->SetLogy();

c1->Update();
c1->Print("output_test.pdf");

rootapp->Run();
return 0;

}
