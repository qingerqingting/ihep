void rootlogon() {
//Set style of graphs.
//By ShanWei.
//Modified by LongYunfei.

gStyle->SetOptTitle(1);
gStyle->SetOptStat(1111111);
gStyle->SetOptFit(1111);
gStyle->SetHistLineWidth(1);

// BES style changed from BABAR style
TStyle *besStyle= new TStyle("BES","BES approved plots style");

// use plain black on white colors
besStyle->SetCanvasBorderMode(0);
besStyle->SetCanvasColor(0);
besStyle->SetFrameBorderMode(0);
besStyle->SetFrameBorderSize(3);
besStyle->SetFrameLineStyle(1);
besStyle->SetFrameLineWidth(2);
besStyle->SetFrameLineColor(0);
besStyle->SetPadBorderMode(0);
besStyle->SetPadColor(0);

besStyle->SetStatColor(0);

// set the paper & margin sizes
besStyle->SetPaperSize(20,26);
besStyle->SetPadTopMargin(0.05);
besStyle->SetPadRightMargin(0.05);
besStyle->SetPadBottomMargin(0.20);
besStyle->SetPadLeftMargin(0.20);

// use large Times-Roman fonts
besStyle->SetTextFont(62);
besStyle->SetTextSize(0.08); 
besStyle->SetTitleFont(62,"x");  // set the all 3 axes title font
besStyle->SetTitleFont(62,"y");    // set the pad title font
besStyle->SetTitleFont(62,"z");    // set the pad title font
besStyle->SetLabelFont(62,"x");
besStyle->SetLabelFont(62,"y");
besStyle->SetLabelFont(62,"z");
besStyle->SetLabelSize(0.07,"x");
besStyle->SetTitleSize(0.09,"x");
besStyle->SetLabelSize(0.07,"y");
besStyle->SetTitleSize(0.09,"y");
besStyle->SetLabelSize(0.06,"z");
besStyle->SetTitleSize(0.06,"z");

// use bold lines and markers
besStyle->SetMarkerStyle(20);
besStyle->SetMarkerSize(1);
besStyle->SetMarkerColor(1);
besStyle->SetLineWidth(3);
besStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes


// do not display any of the standard histogram decorations
besStyle->SetOptTitle(0);
  //statistic box!
//besStyle->SetOptStat(0);
besStyle->SetOptFit(0);

// put tick marks on top and RHS of plots
besStyle->SetPadTickX(1);
besStyle->SetPadTickY(1);

besStyle->SetHistLineWidth(4);

//**************************************
//some useful functions defined by Long.
//**************************************

// set histogram style
void sethistostyle(TH1 *h){
  //centered title
  h->GetXaxis()->CenterTitle(true);
  h->GetYaxis()->CenterTitle(true);
}

// Divisions
void setdivision(TH1 *h){
  //Ndivision
  h->GetXaxis()->SetNdivisions(505);
}

//Y-axis,mass spectrum
void setymass(TH1 *h){
  //Yaxis
  //Valid for the mass spectrum.
  h->GetYaxis()->SetTitle(Form("Events/(%.0fMeV)",h->GetBinWidth(1)*1000));
}

// Draw arrow
void drawarrow(Double_t x,Double_t y1,Double_t y2){
  TArrow *ar=new TArrow(x,y1,x,y2,0.02,"<");
  ar->SetLineColor(kRed);
  ar->SetLineWidth(2);
  ar->Draw();
}

// Write Entries,Mean and RMS
void box(Double_t x, Double_t y,TH1 *h,Char_t sName[]="Entries=%.0f",Char_t mName[]="Mean=%.4f",Char_t rName[]="RMS=%.4f",Double_t sizeTxt=0.06){
  h->SetStats(kFALSE);
  TLatex *ltx=new TLatex();
  ltx->SetNDC(kTRUE);
  ltx->SetTextColor(h->GetLineColor());
  ltx->SetTextFont(22);
  ltx->SetTextSize(sizeTxt);
  ltx->DrawLatex(x,y,Form(sName,h->GetEntries()));
  ltx->DrawLatex(x,y-0.1,Form(mName,h->GetMean()));
  ltx->DrawLatex(x,y-0.2,Form(rName,h->GetRMS()));
  gPad->Modified();
  gPad->Update();
}

//new TBrowser();
printf("Welcome to ROOT!\n");

gROOT->SetStyle("BES");
gStyle->SetLineWidth(4);
gROOT->ForceStyle();
}

