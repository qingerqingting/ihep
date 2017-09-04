void myselect_1(){
  //Jpsi->eta phi(2170)
  //  eta->2gamma phi(2170)->phi f0_2pi(980) phi->2K 
  //    f0_2pi(980)->pi+ pi- 

  //The name of tree
  TChain *chain = new TChain("TreeAna");
  //The name of root file
  chain->Add("sigmc_g2pi2k2.root");
  TFile *ofile=new TFile("cut_sigmc_g2pi2k2.root","RECREATE");

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

  //P of particles;
    //eta
  TLorentzVector p_2gam;
    //phi
  TLorentzVector p_2k;
    //f0
  TLorentzVector p_2pi;
    //phi(2170)
  TLorentzVector p_f0_2pi;


  const Double_t m_eta=0.5479;



  //4-momentum of photons, from root file
  TLorentzVector *gamma1_unfitted;
  TLorentzVector *gamma2_unfitted;

  //2 pi
  TLorentzVector *pip_unfitted;
  TLorentzVector *pim_unfitted;

  //2 K
  TLorentzVector *kp_unfitted;
  TLorentzVector *km_unfitted;

  //After right combination:
  gamma1_f = new TLorentzVector();
  gamma2_f = new TLorentzVector();
  pip_f = new TLorentzVector();
  pim_f = new TLorentzVector();
  kp_f = new TLorentzVector();
  km_f = new TLorentzVector();

  //4-momentum of photons.
  chain->SetBranchAddress("gamma1_unfitted",&gamma1_unfitted);
  chain->SetBranchAddress("gamma2_unfitted",&gamma2_unfitted);

  //2 pi.
  chain->SetBranchAddress("pip_unfitted",&pip_unfitted);
  chain->SetBranchAddress("pim_unfitted",&pim_unfitted);

  //2 K.
  chain->SetBranchAddress("kp_unfitted",&kp_unfitted);
  chain->SetBranchAddress("km_unfitted",&km_unfitted);

  //Chi2.
  chain->SetBranchAddress("Chisq_low",&Chisq_low);

  TTree *tree=new TTree("tree","the right photon combination.");

  tree->Branch("Chisq_low",&Chisq_low,"Chisq_low/D");
  tree->Branch("gamma1_f",&gamma1_f,32000,0);
  tree->Branch("gamma2_f",&gamma2_f,32000,0);
  tree->Branch("pip_f",&pip_f,32000,0);
  tree->Branch("pim_f",&pim_f,32000,0);
  tree->Branch("kp_f",&kp_f,32000,0);
  tree->Branch("km_f",&km_f,32000,0);

  //MC Truth.
  Int_t indexmc;
  Int_t pdgid[500];
  Int_t motheridx[500];

  chain->SetBranchAddress("indexmc",&indexmc);
  chain->SetBranchAddress("pdgid",pdgid);
  chain->SetBranchAddress("motheridx",motheridx);

  tree->Branch("indexmc",&indexmc,"indexmc/I");
  tree->Branch("pdgid",pdgid,"pdgid[indexmc]/I");
  tree->Branch("motheridx",motheridx,"motheridx[indexmc]/I");

  Long64_t nevent=chain->GetEntries();
  for(Long64_t j=0;j<nevent;j++)
  {
    chain->GetEntry(j);
    //Cut on Chisq_4C
    if (Chisq_low>40) continue;
      gamma1_f->SetPxPyPzE(gamma1_unfitted->Px(),gamma1_unfitted->Py(),gamma1_unfitted->Pz(),gamma1_unfitted->E());
      gamma2_f->SetPxPyPzE(gamma2_unfitted->Px(),gamma2_unfitted->Py(),gamma2_unfitted->Pz(),gamma2_unfitted->E());

    pip_f->SetPxPyPzE(pip_unfitted->Px(),pip_unfitted->Py(),pip_unfitted->Pz(),pip_unfitted->E());
    pim_f->SetPxPyPzE(pim_unfitted->Px(),pim_unfitted->Py(),pim_unfitted->Pz(),pim_unfitted->E());
    kp_f->SetPxPyPzE(kp_unfitted->Px(),kp_unfitted->Py(),kp_unfitted->Pz(),kp_unfitted->E());
    km_f->SetPxPyPzE(km_unfitted->Px(),km_unfitted->Py(),km_unfitted->Pz(),km_unfitted->E());

    tree->Fill();

  }//end with for

  tree->Write();
  ofile->Close();

}//final end
