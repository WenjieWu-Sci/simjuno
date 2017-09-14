TH1D* drawit(TString, TString, Color_t);

void draw() {
    ifstream listfile;
    listfile.open("list.txt", ios::in);
    if ( !listfile.good() ) {
        cout << "cannot open list file" << endl;
        exit(-1);
    }

    int NumOfFiles= 0;
    TString tmp_filename;
    vector<TString> filename; 
    while (!listfile.eof()) {
        listfile >> tmp_filename;
        if ( !listfile.eof() ) {
            filename.push_back(tmp_filename);
            NumOfFiles++;
        }
    }

    vector<TH1D*> htime;
    vector<TH1D*> hPE;
    TCanvas* c1= new TCanvas("c1", "c1", 800, 600);
    htime.push_back(drawit(filename[0], "time", kBlue));
    htime[0]->Draw("E");
    for (int i= 1; i< NumOfFiles; ++i) {
        htime.push_back(drawit(filename[i], "time", i));
        htime[i]->Draw("E SAME");
    }
    c1->BuildLegend(0.6, 0.6, 0.85, 0.8);
    c1->SaveAs("./figure/time.root");
    c1->SaveAs("./figure/time.pdf");
    c1->SaveAs("./figure/time.png");

    TCanvas* c2= new TCanvas("c2", "c2", 800, 600);
    hPE.push_back(drawit(filename[0], "space", kBlue));
    hPE[0]->GetYaxis()->SetRangeUser(0, 4);
    hPE[0]->Draw("E");
    for (int i= 1; i< NumOfFiles; ++i) {
        hPE.push_back(drawit(filename[i], "space", i));
        hPE[i]->Draw("E SAME");
    }
    c2->BuildLegend(0.6, 0.6, 0.85, 0.8);
    c2->SaveAs("./figure/PE.root");
    c2->SaveAs("./figure/PE.pdf");
    c2->SaveAs("./figure/PE.png");

    /*

    TH1D* hx= new TH1D("hx", "hx", 1000, -20, 20);
    TH1D* hr= new TH1D("hr", "hr", 1000, 0, 20);
    TH1D* hcostheta= new TH1D("hcostheta", "hcostheta", 100, -1, 1);

    TCanvas* c1= new TCanvas("c1", "c1", 800, 600);
    hcostheta->Scale(1./(hcostheta->Integral()*hcostheta->GetBinWidth(1)));
    hcostheta->GetXaxis()->SetTitle("cos(#theta)");
    hcostheta->Draw();


    TString PEDistName= "./figure/" + infileName.Remove(infileName.Length()-5) + "_PE.pdf";
    c1->SaveAs(PEDistName);
    TString TimeDistName= "./figure/" + infileName + "_Time.pdf";
    c2->SaveAs(TimeDistName);
    */
}

TH1D* drawit(TString filename, TString type, Color_t tcolor) {
    TFile* infile= new TFile(filename);
    if (!infile->IsOpen()) {
        cout << "Error opening this file : " << filename << endl;
        exit(-1);
    }
    TTree* evt= (TTree*)infile->Get("evt");
    int Nentries= evt->GetEntries();
    int nPhotons;
    double detX[200000];
    double detY[200000];
    double detZ[200000];
    double hitTime[200000];
    int nRayScattering[200000];
    evt->SetBranchAddress("nPhotons", &nPhotons);
    evt->SetBranchAddress("detX", detX);
    evt->SetBranchAddress("detY", detY);
    evt->SetBranchAddress("detZ", detZ);
    evt->SetBranchAddress("hitTime", hitTime);
    evt->SetBranchAddress("nRayScattering", nRayScattering);

    TString histoName;
    TH1D* h;
    if ( type=="time" ) {
        histoName= "htime_" + filename.Remove(filename.Length()-5);
        h= new TH1D(histoName, histoName, 100, 0, 200);
    } else if ( type=="space" ) {
        histoName= "hspace_" + filename.Remove(filename.Length()-5);
        h= new TH1D(histoName, histoName, 50, -1, 1);
    }
    cout << "Processing " << filename << endl;
    for (int i= 0; i< Nentries; ++i) {
        evt->GetEntry(i);
        for (int j= 0; j< nPhotons; ++j) {
            double R2= TMath::Power(detX[j]/1000.,2) + TMath::Power(detY[j]/1000.,2) + TMath::Power(detZ[j]/1000.,2);
            double R= TMath::Sqrt(R2);
            double cos_theta= detZ[j]/1000./R;
            if (nRayScattering[j]==0) {
                if ( type=="time" ) {
                    h->Fill(hitTime[j]);
                } else if ( type=="space" ) {
                    h->Fill(cos_theta);
                }
            }
        }
    }

    h->Sumw2();
    h->Scale(1./(h->Integral()*h->GetBinWidth(1)));
    if ( type=="time" ) {
        h->GetXaxis()->SetTitle("hit time [ns]");
    } else if ( type=="space" ) {
        h->GetXaxis()->SetTitle("cos(#theta)");
    }
    h->SetMarkerStyle(20);
    h->SetMarkerSize(0.7);
    h->SetMarkerColor(tcolor);
    h->SetLineColor(tcolor);

    return h;
}
