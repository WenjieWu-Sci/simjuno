{
TFile* f = new TFile("simjunotest.root","open");
TCanvas c1;
c1.cd();
Int_t num = evt->Draw("nRayleigh","","goff");
Double_t *nRay = evt->GetV1();
Int_t max=TMath::MaxElement(num,nRay);
//cout << max << endl;

gStyle->SetOptStat(false);
TLegend* t = new TLegend(0.6,0.6,0.9,0.9);

for(int i=0;i<=max;i++){
    evt->Draw(Form("Time_Det>>h%d(640,60,700)",i),Form("nRayleigh==%d",i),"goff");
}
for(int i=0;i<=max;i++){
    TH1D* tmp=gDirectory->Get(Form("h%d",i));
    if(i==0){
        tmp->Draw("");
        tmp->SetTitle(";Arrival Time/ns;#");
    }
    else
        tmp->Draw("sames");
    tmp->SetFillStyle(3002);
    tmp->SetFillColor(i+1);
    tmp->SetLineColor(i+1);
    t->AddEntry(tmp,Form("nRayleigh=%d, Average Time=%.1f ns",i,tmp->GetMean()),"lf");
}
t->Draw();
c1.SetLogy();

}
