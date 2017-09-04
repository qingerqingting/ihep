void drawgam1(){

  //Draw the mass spectrum of pi+ pi-.
  //Compare between sigmc and etaphif0(980).

  gStyle->SetOptStat(0);

  Double_t m_2gam_1;
  TChain *chain1 = new TChain("TreeRes");
  chain1->Add("before_cut_sigmc_g4pi2k2.root");
  chain1->SetBranchAddress("m_2gam_1",&m_2gam_1);

  //f0(980)
  TH1F *h1=new TH1F ("h1","m_2gam_1",60,0.4,0.7);
  h1->GetXaxis()->SetTitle("m_{2#gamma_{1}} [GeV]");
  setymass(h1);

  //=***********************************
  Long64_t nevent1=chain1->GetEntries();
  //cout<<"nevent_data="<<nevent1<<endl;
  for(Long64_t j=0;j<nevent1;j++)
  {
    chain1->GetEntry(j);
    h1->Fill(m_2gam_1);
  }

  
  TCanvas *c1=new TCanvas();
 

  h1->Draw("pe");
drawarrow(0.5,0,40);
drawarrow(0.57,0,40);
}
