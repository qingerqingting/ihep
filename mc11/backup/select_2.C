void select_2(){
  //Jpsi->eta phi eta'
  //  eta->2gamma phi->2K eta'->pi pi eta
  //    eta->2gamma

  //The final selection criteria and draw the graphs.

  //=**********************
  //MARK=1:draw the graphs
  //MARK=2:store the results of tree.
  //       Be careful with TreeRes->Fill()
  //=**********************
  Int_t MARK=1;

  //The name of tree
  TChain *chain = new TChain("tree");
  //The name of root file
  chain->Add("rightcomb_sigmc_g4pi2k2.root");

  //Store the TreeResults.
  if (MARK==2){
    TFile *ofile=new TFile("output_sigmc_g4pi2k2","RECREATE");
  }//end with if (MARK==2)

  if (MARK==1){
  //The canvas;
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

  }//end with if (MARK==1)

  //The histos;
  TH1F *h1=new TH1F ("h1","The mass spectrum of 2_gam_1",60,0.4,0.7);
  h1->GetXaxis()->SetTitle("m_{2#gamma_{1}} [GeV]");
  setymass(h1);

  TH1F *h2=new TH1F ("h2","The mass spectrum of 2_gam_2",60,0.4,0.7);
  h2->GetXaxis()->SetTitle("m_{2#gamma_{2}} [GeV]");
  setymass(h2);

  TH1F *h3=new TH1F ("h3","The mass spectrum of 2 k",40,0.9,1.1);
  h3->GetXaxis()->SetTitle("m_{2K} [GeV]");
  setymass(h3);

  TH1F *h4=new TH1F ("h4","The mass spectrum of #pi#pi#eta",50,0.7,1.2);
  h4->GetXaxis()->SetTitle("m_{#pi^{+}#pi^{-}#eta} [GeV]");
  setymass(h4);

  TH1F *h5=new TH1F ("h5","The mass spectrum of phi&etap",20,1.9,2.6);
  h5->GetXaxis()->SetTitle("m_{#phi+#eta'} [GeV]");
  setymass(h5);

  //Dalitz plot
  TH2F *h6=new TH2F ("h6","Dalitz plot;#phi+#eta' [GeV^{2}];#phi+#eta [GeV^{2}]",40,3,7,70,1,8);

  TH1F *h7=new TH1F ("h7","The mass spectrum of eta&etap",80,1.4,2.2);
  h7->GetXaxis()->SetTitle("m_{#eta+#eta'} [GeV]");
  setymass(h7);

  //Control the style of histos.
  setdivision(h1);
  setdivision(h2);
  setdivision(h3);
  setdivision(h4);
  //setdivision(h5);

  //Mass of particles.
    //eta
  Double_t m_2gam_1;
  Double_t m_2gam_2;
    //phi
  Double_t m_2k;
    //rho0
  Double_t m_2pi;
    //eta'
  Double_t m_pipieta;
  Double_t m_pipieta_1;
  Double_t m_pipieta_2;
    //Y(2175)
  Double_t m_phi_etap;
  Double_t m_phi_etap_1;
  Double_t m_phi_etap_2;

  Double_t m_phi_eta;

  Double_t m_eta_etap;

  //P of particles;
    //eta
  TLorentzVector p_2gam_1;
  TLorentzVector p_2gam_2;
    //phi
  TLorentzVector p_2k;
    //rho0
  TLorentzVector p_2pi;
    //eta'
  TLorentzVector p_gam_rho;
  TLorentzVector p_gam_rho_1;
  TLorentzVector p_gam_rho_2;
    //Y(2175)
  TLorentzVector p_phi_etap;
  TLorentzVector p_phi_etap_1;
  TLorentzVector p_phi_etap_2;

  TLorentzVector p_phi_eta;

  TLorentzVector p_eta_etap;

  gamma1_f = new TLorentzVector();
  gamma2_f = new TLorentzVector();
  gamma3_f = new TLorentzVector();
  gamma4_f = new TLorentzVector();
  pip_f = new TLorentzVector();
  pim_f = new TLorentzVector();
  kp_f = new TLorentzVector();
  km_f = new TLorentzVector();

  //Read the P from root-file.
  chain->SetBranchAddress("gamma1_f",&gamma1_f);
  chain->SetBranchAddress("gamma2_f",&gamma2_f);
  chain->SetBranchAddress("gamma3_f",&gamma3_f);
  chain->SetBranchAddress("gamma4_f",&gamma4_f);
  chain->SetBranchAddress("pip_f",&pip_f);
  chain->SetBranchAddress("pim_f",&pim_f);
  chain->SetBranchAddress("kp_f",&kp_f);
  chain->SetBranchAddress("km_f",&km_f);
  
  //Store the result in tree.
  if (MARK==2){
    TTree *TreeRes=new TTree("TreeRes","mc truth");
    TreeRes->Branch("m_2gam_1",&m_2gam_1,"m_2gam_1/D");
    TreeRes->Branch("m_2gam_2",&m_2gam_2,"m_2gam_2/D");
    TreeRes->Branch("m_2k",&m_2k,"m_2k/D");
    TreeRes->Branch("m_pipieta",&m_pipieta,"m_pipieta/D");
    TreeRes->Branch("m_phi_etap",&m_phi_etap,"m_phi_etap/D");

    //Store the results about MC Truth.
    //Data don't contain the information about MC Truth.
    Int_t indexmc;
    Int_t pdgid[500];
    Int_t motheridx[500];
    //Read MC Truth
    chain->SetBranchAddress("indexmc",&indexmc);
    chain->SetBranchAddress("pdgid",pdgid);
    chain->SetBranchAddress("motheridx",motheridx);
    //Store MC Truth
    TreeRes->Branch("indexmc",&indexmc,"indexmc/I");
    TreeRes->Branch("pdgid",pdgid,"pdgid[indexmc]/I");
    TreeRes->Branch("motheridx",motheridx,"motheridx[indexmc]/I");
  }//end with if (MARK==2)

  //The mass windows on etap.
  Double_t up=0.98;
  Double_t low=0.91;

  Long64_t nevent=chain->GetEntries();
  for(Long64_t j=0;j<nevent;j++)
  {
    chain->GetEntry(j);

    //eta
    p_2gam_1=*gamma1_f+ *gamma2_f;
    m_2gam_1=p_2gam_1.M();

    p_2gam_2=*gamma3_f+ *gamma4_f;
    m_2gam_2=p_2gam_2.M();
    //phi
    p_2k=*kp_f+ *km_f;
    m_2k=p_2k.M();

    //eta'
    p_pipieta_1=*gamma1_f+ *gamma2_f+ *pip_f+ *pim_f;
    m_pipieta_1=p_pipieta_1.M();

    p_pipieta_2=*gamma3_f+ *gamma4_f+ *pip_f+ *pim_f;
    m_pipieta_2=p_pipieta_2.M();

    //Remove those events with both pipieta in the mass windows of eta'.
    if (((m_pipieta_1>low)&&(m_pipieta_1<up))&&((m_pipieta_2>low)&&(m_pipieta_2<up))) continue;

    if ((m_pipieta_1>low)&&(m_pipieta_1<up)) {
      m_pipieta=m_pipieta_1;
      p_phi_etap=*kp_f+ *km_f+ *gamma1_f+ *gamma2_f+ *pip_f+ *pim_f;
    }//end with if
    else if ((m_pipieta_2>low)&&(m_pipieta_2<up)) {
      m_pipieta=m_pipieta_2;
      p_phi_etap=*kp_f+ *km_f+ *gamma3_f+ *gamma4_f+ *pip_f+ *pim_f;
    }//end with else if
    else {
      continue;
    }//end with else
    m_phi_etap=p_phi_etap.M();

    //cut
    if (m_2gam_1<0.50) continue;
    if (m_2gam_1>0.57) continue;

    if (m_2gam_2<0.50) continue;
    if (m_2gam_2>0.57) continue;

    if (m_2k<1.01) continue;
    if (m_2k>1.03) continue;

    h1->Fill(m_2gam_1);
    h2->Fill(m_2gam_2);
    h3->Fill(m_2k);
    h4->Fill(m_pipieta);
    h5->Fill(m_phi_etap);

    //Dalitz plot
   // h6->Fill(m_phi_etap*m_phi_etap,m_phi_eta*m_phi_eta);

   // h7->Fill(m_eta_etap);
    //=***********************************
    //Store Tree result,with if (MARK==2)
    //TreeRes->Fill();
    //=***********************************
  
  }//end with for
  if (MARK==1){
  c1->cd(1);
  h1->Draw("pe");
  c5->cd(1);
  h2->Draw("pe");

  c2->cd(1);
  h3->Draw("pe");

  c3->cd(1);
  h4->Draw("pe");

  c4->cd(1);
  h5->Draw("pe");

 /* c5->cd(1);
  h6->Draw("pe");

  c6->cd(1);
  h7->Draw("pe");*/
  }//end with if(MARK==1)

//Store the tree results. 
  if (MARK==2){
  TreeRes->Write();
  ofile->Close();
  }//end with if (MARK==2)

}//final end
