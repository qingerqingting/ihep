void select_mctruth(){
//The itopo stands for a decay process
//Get the mass spectrum of a special channel

  TChain *chain = new TChain("TreeRes");

  chain->Add("topo.root");

  Int_t itp;
  itp=3;

  Int_t itopo;
  Int_t pdgid[500];

  Double_t m_2gam;
  Double_t m_2k;
  Double_t m_2pi;
  Double_t m_eta_etap;
  Double_t m_gam_rho;
  Double_t m_phi_eta;
  Double_t m_phi_etap;

  chain->SetBranchAddress("itopo",&itopo);
  chain->SetBranchAddress("pdgid",pdgid);
  chain->SetBranchAddress("m_2gam",&m_2gam);
  chain->SetBranchAddress("m_2k",&m_2k);
  chain->SetBranchAddress("m_2pi",&m_2pi);
  chain->SetBranchAddress("m_eta_etap",&m_eta_etap);
  chain->SetBranchAddress("m_gam_rho",&m_gam_rho);
  chain->SetBranchAddress("m_phi_etap",&m_phi_etap);

  TH1F *h1=new TH1F ("h1","The mass spectrum of 2 gam",60,0.45,0.6);
  h1->GetXaxis()->SetTitle("m_{2#gamma} [GeV]");
  setymass(h1);

  TH1F *h2=new TH1F ("h2","The mass spectrum of 2 pi",100,0.2,1.2);
  h2->GetXaxis()->SetTitle("m_{2#pi} [GeV]");
  setymass(h2);

  TH1F *h3=new TH1F ("h3","The mass spectrum of 2 k",40,1.0,1.04);
  h3->GetXaxis()->SetTitle("m_{2K} [GeV]");
  setymass(h3);

  TH1F *h4=new TH1F ("h4","The mass spectrum of gamma&rho0",50,0.9,1.);
  h4->GetXaxis()->SetTitle("m_{#gamma+#rho^{0}} [GeV]");
  setymass(h4);

  TH1F *h5=new TH1F ("h5","The mass spectrum of phi&etap",70,1.9,2.6);
  h5->GetXaxis()->SetTitle("m_{#phi+#eta'} [GeV]");
  setymass(h5);

  TCanvas *c1=new TCanvas();
  TCanvas *c2=new TCanvas();
  TCanvas *c3=new TCanvas();
  TCanvas *c4=new TCanvas();
  TCanvas *c5=new TCanvas();
 // TCanvas *c6=new TCanvas();

  c1->Divide(1,1);
  c2->Divide(1,1);
  c3->Divide(1,1);
  c4->Divide(1,1);
  c5->Divide(1,1);
 // c6->Divide(1,1);

  Long64_t nevent=chain->GetEntries();
  for(Long64_t j=0;j<nevent;j++)
  {
    chain->GetEntry(j);

    //Get events with special itopo.
    if (itopo>itp) continue;
    if (itopo<itp) continue;

    h1->Fill(m_2gam);
    h2->Fill(m_2pi);
    h3->Fill(m_2k);
    h4->Fill(m_gam_rho);
    h5->Fill(m_phi_etap);  
  }
  c1->cd(1);
  h1->Draw("pe");

  c2->cd(1);
  h2->Draw("pe");

  c3->cd(1);
  h3->Draw("pe");

  c4->cd(1);
  h4->Draw("pe");

  c5->cd(1);
  h5->Draw("pe");
}

