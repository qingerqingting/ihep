void draw_chi2(){
//Draw the chi2 of Data and SignalMC.
//The name of root file should be changed.

  TCanvas *c1=new TCanvas();

  //Data
  TFile *l1=new TFile("sigmc_g4pi2k2.root");
  TTree *t1=(TTree*) l1->Get("TreeAna");
  TH1F *h1=new TH1F("h1","h1",100,0,200);
  t1->Draw("Chisq_low>>h1");

  //Signal MC
/*  TFile *l2=new TFile("sigmc_g3pi2k2_0912.root");
  TTree *t2=(TTree*) l2->Get("TreeAna");
  TH1F *h2=new TH1F("h2","h2",100,0,200);
  t2->Draw("Chisq_low>>h2");
  h2->GetXaxis()->SetTitle("Chisq_4C");
  h2->GetYaxis()->SetTitle("Events");
*/
  Double_t N1=30000;
 // Double_t N2=10000;

  h1->Scale(N1/h1->Integral());
 // h2->Scale(N2/h2->Integral());

  h1->SetLineColor(kBlack);
 // h2->SetLineColor(kBlue);
  //No statistic box!
  gStyle->SetOptStat(0);
 // h2->GetXaxis()->CenterTitle(true);
 // h2->GetYaxis()->CenterTitle(true);

  //h2->GetXaxis()->SetNdivisions(505);
  
 // h2->Draw();
  h1->Draw("Same");
  drawarrow(40,0,800);

  //legend
 // TLegend leg(.5,.5,.8,.9,"Chisq_4C");
 // leg.SetFillColor(0);
 // leg.AddEntry(h1,"Data","l");
 // leg.AddEntry(h2,"SignalMC","l");
 // leg.DrawClone("same");
  }


