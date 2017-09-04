void fit_signal(){
//fit to the mass spectrum of m_{phi+etap}
//from signal MC.
//BW concolve gaussian.

  using namespace RooFit;

  //The range of m_phi_etap
  RooRealVar m_phi_etap("m_phi_etap","m_{#phi+#eta'} [GeV]",1.9,2.4);

  //Read the root file.
  TFile *f1=new TFile ("output_sigmc_g4pi2k2.root");
  TTree *tree =(TTree*) gDirectory->Get("TreeRes");
  RooDataSet y2175("y2175","y2175",tree,m_phi_etap);

  //Signal
  //BW
  RooRealVar mean ("mean","mean",2.175,1.9,2.4);
  RooRealVar Gamma ("Gamma","Gamma",0.061,0,1);
  RooRealVar sigma ("sigma","sigma",0.01,0,1);

    //Fix Gamma
  Gamma.setConstant(kTRUE);
  RooVoigtian sig ("sig","sig",m_phi_etap,mean,Gamma,sigma);

  sig.fitTo(y2175);

  RooPlot * frame=m_phi_etap.frame();
 // y2175.plotOn(frame);
 // sig.plotOn(frame);
  //parameters
  sig.paramOn(frame,Layout(0.2,0.55));

  //Prepare for legend.
  //Signal MC: Y(2175)
  RooPlot *y2175_1= y2175.plotOn(frame,Binning(50));
  RooHist *h_y2175=y2175_1->getHist("h_y2175");

  //Fit to the signal MC
  RooPlot *sig_1= sig.plotOn(frame,Components(sig),LineColor(kBlue));
  RooCurve *c_sig=sig_1->getCurve("sig_Norm[m_phi_etap]_Comp[sig]");

  frame->Draw();

  //Draw the legend.
  TLegend *leg=new TLegend(0.75,0.7,0.95,0.95);
  leg->AddEntry(h_y2175,"Signal MC","LPE");
  leg->AddEntry(c_sig,"BW (x) gaussian","L");
  leg->Draw();
}

