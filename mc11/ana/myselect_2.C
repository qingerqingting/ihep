void myselect_2(){
 //Jpsi->eta phi(2170)
  //  eta->2gamma phi(2170)->phi f0_2pi(980) phi->2K 
  //    f0_2pi(980)->pi+ pi- 
  //The final selection criteria and draw the graphs.
  //=**********************
  //mark=1:draw the graphs
  //mark=2:store the results of tree.
  //      :Data do not contain information about MCTruth.
  //      :Be careful with TreeRes->Fill()
  //*********************
  Int_t mark=2;

  //The name of tree
  TChain *chain = new TChain("tree");
  //The name of root file
  chain->Add("cut_sigmc_g2pi2k2.root");

  //Store the histograms.

  if (mark==2){
  TFile *ofile=new TFile("output_sigmc_g2pi2k2.root","RECREATE");
  TTree *TreeRes=new TTree("TreeRes","Tree Result");
  }//end with if (mark==2)

  if (mark==1){
  //The canvas;
  TCanvas *c1=new TCanvas();
  TCanvas *c2=new TCanvas();
  TCanvas *c3=new TCanvas();
  TCanvas *c4=new TCanvas();
  TCanvas *c5=new TCanvas();
  TCanvas *c6=new TCanvas();
  TCanvas *c7=new TCanvas();
  TCanvas *c8=new TCanvas();
 
  c1->Divide(1,1);
  c2->Divide(1,1);
  c3->Divide(1,1);
  c4->Divide(1,1);
  c5->Divide(1,1);
  }//end with if (mark==1)

  //The histos;
  TH1F *h1=new TH1F ("h1","The mass spectrum of 2 gam",70,0.4,0.65);
  h1->GetXaxis()->SetTitle("m_{2#gamma} [GeV]");
  setymass(h1);

  TH1F *h2=new TH1F ("h2","The mass spectrum of 2 pi",100,0.2,1.2);
  h2->GetXaxis()->SetTitle("m_{2#pi} [GeV]");
  setymass(h2);

  TH1F *h3=new TH1F ("h3","The mass spectrum of 2 k",50,0.97,1.07);
  h3->GetXaxis()->SetTitle("m_{2K} [GeV]");
  setymass(h3);

  TH1F *h4=new TH1F ("h4","The mass spectrum of phi&2pi",50,0.85,1.05);
  h4->GetXaxis()->SetTitle("m_{#phi+#pi^{+}+#pi^{-}} [GeV]");
  setymass(h4);

  TH1F *h5=new TH1F ("h5","The mass spectrum of J/psi",35,1.9,2.6);
  h5->GetXaxis()->SetTitle("m_{#phi(2170)+#eta} [GeV]");
  setymass(h5);
 
 //Control the style of histos.
  setdivision(h1);
  setdivision(h2);
  setdivision(h3);
  setdivision(h4);

 //Chisq_cut
  Double_t Chisq_low;
 //Mass of particles.
    //eta
  Double_t m_2gam;
    //phi
  Double_t m_2k;
    //f0
  Double_t m_2pi;
    //phi(2170)
  Double_t m_f0_2pi;
    //J/psi
  Double_t m_eta_phi_2170;

  Double_t m_phi_eta;

  Double_t m_eta_etap;

  //P of particles;
    //eta
  TLorentzVector p_2gam;
    //phi
  TLorentzVector p_2k;
    //rho0
  TLorentzVector p_2pi;
    //eta'
  TLorentzVector p_f0_2pi;
    //Y(2175)
  TLorentzVector p_eta_phi_2170;


  gamma1_f = new TLorentzVector();
  gamma2_f = new TLorentzVector();
  pip_f = new TLorentzVector();
  pim_f = new TLorentzVector();
  kp_f = new TLorentzVector();
  km_f = new TLorentzVector();

  chain->SetBranchAddress("gamma1_f",&gamma1_f);
  chain->SetBranchAddress("gamma2_f",&gamma2_f);

  chain->SetBranchAddress("pip_f",&pip_f);
  chain->SetBranchAddress("pim_f",&pim_f);

  chain->SetBranchAddress("kp_f",&kp_f);
  chain->SetBranchAddress("km_f",&km_f);
  chain->SetBranchAddress("Chisq_low",&Chisq_low);
  
  if (mark==2){
    TreeRes->Branch("m_2gam",&m_2gam,"m_2gam/D");
    TreeRes->Branch("m_2k",&m_2k,"m_2k/D");
    TreeRes->Branch("m_2pi",&m_2pi,"m_2pi/D");
    TreeRes->Branch("m_f0_2pi",&m_f0_2pi,"m_f0_2pi/D");
    TreeRes->Branch("m_eta_phi_2170",&m_eta_phi_2170,"m_eta_phi_2170/D");
    TreeRes->Branch("Chisq_low",&Chisq_low,"Chisq_low/D");

    //Store the results about MC Truth.
    //Data don't contain the information about MC Truth.

  Int_t indexmc;
  Int_t pdgid[500];
  Int_t motheridx[500];

  chain->SetBranchAddress("indexmc",&indexmc);
  chain->SetBranchAddress("pdgid",pdgid);
  chain->SetBranchAddress("motheridx",motheridx);

  TTree *TMCTruth=new TTree("TMCTruth","mc truth");
  TMCTruth->Branch("indexmc",&indexmc,"indexmc/I");
  TMCTruth->Branch("pdgid",pdgid,"pdgid[indexmc]/I");
  TMCTruth->Branch("motheridx",motheridx,"motheridx[indexmc]/I");
  }//end with if (mark==2)

  Long64_t nevent=chain->GetEntries();
  for(Long64_t j=0;j<nevent;j++)
  {
    chain->GetEntry(j);

    //eta
    p_2gam=*gamma1_f+ *gamma2_f;
    m_2gam=p_2gam.M();

    //phi
    p_2k=*kp_f+ *km_f;
    m_2k=p_2k.M();

    //f0
    p_2pi=*pip_f+ *pim_f;
    m_2pi=p_2pi.M();

    //phi(2170)
    p_f0_2pi=*kp_f+ *km_f+ *pip_f+ *pim_f;
    m_f0_2pi=p_f0_2pi.M();

    //J/psi
    p_eta_phi_2170=*kp_f+ *km_f+ *gamma1_f+ *gamma2_f+ *pip_f+ *pim_f;
    m_eta_phi_2170=p_eta_phi_2170.M();


    //cut
    //=***************************
    if (m_2gam<0.49) continue;
    if (m_2gam>0.58) continue;

    if (m_2pi<0.8) continue;
    if (m_2pi>1.1) continue;

    if (m_2k<1.0) continue;
    if (m_2k>1.04) continue;

    //=***************************

    h1->Fill(m_2gam);
    h2->Fill(m_2pi);
    h3->Fill(m_2k);
    h4->Fill(m_f0_2pi);
    h5->Fill(m_eta_phi_2170);

  
    //=***************************************************
    //Store Tree Result, with if (mark)==2)
    TreeRes->Fill();
    //=***************************************************
  }

  if (mark==1){
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
 // box(0.77,0.9,h5);


 /* c7->cd(4);
  h2->Draw("pe");
  box(0.77,0.9,h2);*/

  }//end with if (mark==1)
//Store the tree results.

if (mark==2){
  TreeRes->Write();
  ofile->Close();
  }//end with if (mark==2)

}//final end

