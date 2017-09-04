void draw2pieta(){

  //Draw the mass spectrum of pi+ pi-.
  //Compare between sigmc and etaphif0(980).

  gStyle->SetOptStat(0);

  Double_t m_pipieta;
  TChain *chain1 = new TChain("TreeRes");
  chain1->Add("before_cut_sigmc_g4pi2k2.root");
  chain1->SetBranchAddress("m_pipieta",&m_pipieta);

  //f0(980)
  TH1F *h1=new TH1F ("h1","m_pipieta",60,0.85,1.05);
  h1->GetXaxis()->SetTitle("m_{#pi^{+}#pi^{-}#eta} [GeV]");
  setymass(h1);

  //=***********************************
  Long64_t nevent1=chain1->GetEntries();
  //cout<<"nevent_data="<<nevent1<<endl;
  for(Long64_t j=0;j<nevent1;j++)
  {
    chain1->GetEntry(j);
    h1->Fill(m_pipieta);
  }

  
  TCanvas *c1=new TCanvas();
 

  h1->Draw("pe");
drawarrow(0.91,0,40);
drawarrow(0.98,0,40);
}
