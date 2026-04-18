#include<iostream>
#include<cmath>
#include<vector>
#include "TCanvas.h"
#include "TF1.h"
#include "TH1F.h"
#include "TTree.h"
#include "TFile.h"
using namespace std;


//AGGIORNATO 18/04/2026; NON USARE IL 3!

/*l'obiettivo di questo file è fare tagli sui seguenti valori:
DCAV0toPrimaryVertex
DCAPosToPv
DCANegToPv
V0radius
V0cosPa (il più importante)
(v0 daughters?)
DCABAchToPv
CascadecosPA (altro importante)
CascDCAToPV
cascDcaToPVxy
CascRadius
V0cosPA
*/

void TESIt_tagli_4(){
    //
    //
    TFile* analisi= new TFile("AnalysisResults_280234.root", "READ");
    //
    TTree* tree= (TTree*) analisi->Get("PWGLF_StrVsMult/fTreeCascade");
    //
    TCanvas* c1= new TCanvas("c1", "MASSA senza tagli", 1000, 800);
    //
    c1->Divide(1, 2);
    //di seguito i nomi delle variabili a cui saranno associati gli address dei TTree
    float mass_csi=0;
    int charge=0;
    //"aiuto ho dimenticato il titolo",
    //creiamo gli istogrammi con dentro solo le masse delle csi e delle anti-csi (antiparticelle di carica positiva)
    TH1F* hmass_csi= new TH1F("mass_csi", "massa delle particelle Csi^-", 300, 1.3, 1.35);
    TH1F* hmass_anti_csi= new TH1F("mass_anti_csi", "massa delle anti particelle Csi^+", 300, 1.3, 1.35);
    int num_bin_massa=300;
    //
    //
    tree->SetBranchAddress("fTreeCascVarMassAsXi", &mass_csi);
    tree->SetBranchAddress("fTreeCascVarCharge", &charge);
    //
    //numero di entries
    int len= tree->GetEntries();
    //
    //
    for(int i=0; i<len; i++){
        tree->GetEntry(i);
        if(charge<=0){
            hmass_csi->Fill(mass_csi);
        }
        if(charge>0){
            hmass_anti_csi->Fill(mass_csi);
        }

    }
    //
    TF1* fit_massa_csi2= new TF1("fit_massa_csi2", "gaus(0)+pol3(3)", 1.3, 1.35);
    fit_massa_csi2->SetParameters(250, 1.32171, 0.003, 285300,  -411500, 150000, 0);
    fit_massa_csi2->SetParLimits(1, 1.32, 1.322);
    fit_massa_csi2->SetParLimits(0, 150, 1000);
    fit_massa_csi2->SetParLimits(2, 0, 0.05);
    //
    //disegniamo gli istogrammi
    c1->cd(1);
    c1->SetGrid();
    //hmass_csi->Fit("fit_massa_csi", "R");
    hmass_csi->Fit("fit_massa_csi2", "R");
    hmass_csi->Draw();
    hmass_csi->SetTitle("massa della csi");
     //
     //queste righe restituiscono i parametri di fit
    double A1= fit_massa_csi2->GetParameter(0);
    double mu1= fit_massa_csi2->GetParameter(1);
    double sigma1= fit_massa_csi2->GetParameter(2);
    double p00= fit_massa_csi2->GetParameter(3);
    double p01= fit_massa_csi2->GetParameter(4);
    double p02= fit_massa_csi2->GetParameter(5);
    double p03= fit_massa_csi2->GetParameter(6);
     //
    cout<<"il p-value è: "<<fit_massa_csi2->GetProb()<<endl;
    //
    TF1* fit_massa_anti_csi= new TF1("fit_massa_anti_csi", "gaus(0)+pol3(3)", 1.3, 1.35);
    fit_massa_anti_csi->SetParameters(150, 1.32171, 0.003, 370100, -542000,  200000, 0);
    fit_massa_anti_csi->SetParLimits(1, 1.32, 1.322);
    fit_massa_anti_csi->SetParLimits(0, 100, 1000);
    fit_massa_anti_csi->SetParLimits(2, 0, 0.05);
    //
    c1->cd(2);
    c1->SetGrid();
    hmass_anti_csi->Fit("fit_massa_anti_csi", "R");
    hmass_anti_csi->Draw();
    hmass_anti_csi->SetTitle("massa anti csi");
     cout<<"il p-value è: "<<fit_massa_anti_csi->GetProb()<<endl;
     //queste righe restituiscono i parametri di git
     double A2= fit_massa_anti_csi->GetParameter(0);
     double mu2= fit_massa_anti_csi->GetParameter(1);
     double sigma2= fit_massa_anti_csi->GetParameter(2);
     double p10= fit_massa_anti_csi->GetParameter(3);
     double p11= fit_massa_anti_csi->GetParameter(4);
     double p12= fit_massa_anti_csi->GetParameter(5);
     double p13= fit_massa_anti_csi->GetParameter(6);
    //
    c1->cd(0);
    c1->Print("fit_masse.png", "png");

    /*++++++++++++++++DA QUI PARTE DEI PESI++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    
    #################################################################################################################################
    
    ################################################################################################################################*/
//
///scriviamo di seguito i nomi delle variabili che ci interessano; poi farò il setbranchaddres
float DCACascDaughters=0;
tree->SetBranchAddress("fTreeCascVarDCACascDaughters", &DCACascDaughters);
float DCABachToPrimVtx=0;
tree->SetBranchAddress("fTreeCascVarDCABachToPrimVtx", &DCABachToPrimVtx);
float DCAV0Daughters=0;
tree->SetBranchAddress("fTreeCascVarDCAV0Daughters", &DCAV0Daughters );
float DCAV0ToPrimVtx=0;
tree->SetBranchAddress("fTreeCascVarDCAV0ToPrimVtx", &DCAV0ToPrimVtx);
float DCAPosToPrimVtx=0;
tree->SetBranchAddress("fTreeCascVarDCAPosToPrimVtx", &DCAPosToPrimVtx);
float DCANegToPrimVtx=0;
tree->SetBranchAddress("fTreeCascVarDCANegToPrimVtx", &DCANegToPrimVtx);
float CascCosToPointingAngle=0;
tree->SetBranchAddress("fTreeCascVarCascCosPointingAngle", &CascCosToPointingAngle);
float CascDCAtoPVxy=0;
tree->SetBranchAddress("fTreeCascVarCascDCAtoPVxy", &CascDCAtoPVxy);
float CascRadius=0;
tree->SetBranchAddress("fTreeCascVarCascRadius", &CascRadius);
float V0CosPointingAngle=0;
tree->SetBranchAddress("fTreeCascVarV0CosPointingAngle", &V0CosPointingAngle);
float V0Radius=0;
tree->SetBranchAddress("fTreeCascVarV0Radius", &V0Radius);
//
/*sia per particelle che per antiparticelle, bisogna fare 3 istogrammi per ogni variabile: uno per la grandezza stessa uno per il fondo e 
uno per il segnale; per comodità, iniziamo dalle antiparticelle*/
//
//############################################################################################
//ISTOGRAMMI ANTIPARTICELLE
//
TH1F* hanti_DCACascDaughters= new TH1F("hanti_DCACascDaughters","aiuto ho dimenticato il titolo",200, 0, 0.51);
TH1F* hanti_DCACascDaughters_fondo= new TH1F("hanti_DCACascDaughters_fondo","aiuto ho dimenticato il titolo", 200, 0, 0.51);
TH1F* hanti_DCACascDaughters_segnale= new TH1F("hanti_DCACascDaughters_segnale", "aiuto ho dimenticato il titolo",200, 0, 0.51);
hanti_DCACascDaughters->SetLineColor(6);  // fucsia l'originale
hanti_DCACascDaughters_fondo->SetLineColor(2); //rosso il fondo
hanti_DCACascDaughters_segnale->SetLineColor(3); //verde segnale
//
TH1F* hanti_DCABachToPrimVtx= new TH1F("hanti_DCABachToPrimVtx","aiuto ho dimenticato il titolo",200, 0, 30);
TH1F* hanti_DCABachToPrimVtx_fondo= new TH1F("hanti_DCABachToPrimVtx_fondo","aiuto ho dimenticato il titolo", 200, 0, 30);
TH1F* hanti_DCABachToPrimVtx_segnale= new TH1F("hanti_DCABachToPrimVtx_segnale","aiuto ho dimenticato il titolo", 200, 0, 30);
hanti_DCABachToPrimVtx->SetLineColor(6);  // fucsia l'originale
hanti_DCABachToPrimVtx_fondo->SetLineColor(2); //rosso il fondo
hanti_DCABachToPrimVtx_segnale->SetLineColor(3); //verde segnale
//
TH1F* hanti_DCAV0Daughters= new TH1F("hanti_DCAV0Daughters","aiuto ho dimenticato il titolo",200, 0, 1.05);
TH1F* hanti_DCAV0Daughters_fondo= new TH1F("hanti_DCAV0Daughters_fondo","aiuto ho dimenticato il titolo", 200, 0, 1.05);
TH1F* hanti_DCAV0Daughters_segnale= new TH1F("hanti_DCAV0Daughters_segnale", "aiuto ho dimenticato il titolo",200, 0, 1.05);
hanti_DCAV0Daughters->SetLineColor(6);  // fucsia l'originale
hanti_DCAV0Daughters_fondo->SetLineColor(2); //rosso il fondo
hanti_DCAV0Daughters_segnale->SetLineColor(3); //verde segnale
//
TH1F* hanti_DCAV0ToPrimVtx= new TH1F("hanti_DCAV0ToPrimVtx","aiuto ho dimenticato il titolo",200, 0, 25);
TH1F* hanti_DCAV0ToPrimVtx_fondo= new TH1F("hanti_DCAV0ToPrimVtx_fondo","aiuto ho dimenticato il titolo", 200, 0, 25);
TH1F* hanti_DCAV0ToPrimVtx_segnale= new TH1F("hanti_DCAV0ToPrimVtx_segnale","aiuto ho dimenticato il titolo", 200, 0, 25);
hanti_DCAV0ToPrimVtx->SetLineColor(6);  // fucsia l'originale
hanti_DCAV0ToPrimVtx_fondo->SetLineColor(2); //rosso il fondo
hanti_DCAV0ToPrimVtx_segnale->SetLineColor(3); //verde segnale
//
TH1F* hanti_DCAPosToPrimVtx= new TH1F("hanti_DCAPosToPrimVtx","aiuto ho dimenticato il titolo",200, 0, 38);
TH1F* hanti_DCAPosToPrimVtx_fondo= new TH1F("hanti_DCAPosToPrimVtx_fondo","aiuto ho dimenticato il titolo", 200, 0, 38);
TH1F* hanti_DCAPosToPrimVtx_segnale= new TH1F("hanti_DCAPosToPrimVtx_segnale","aiuto ho dimenticato il titolo", 200, 0, 38);
hanti_DCAPosToPrimVtx->SetLineColor(6);  // fucsia l'originale
hanti_DCAPosToPrimVtx_fondo->SetLineColor(2); //rosso il fondo
hanti_DCAPosToPrimVtx_segnale->SetLineColor(3); //verde segnale
//
TH1F* hanti_DCANegToPrimVtx= new TH1F("hanti_DCANegToPrimVtx","aiuto ho dimenticato il titolo",200, 0, 38);
TH1F* hanti_DCANegToPrimVtx_fondo= new TH1F("hanti_DCANegToPrimVtx_fondo","aiuto ho dimenticato il titolo", 200, 0, 38);
TH1F* hanti_DCANegToPrimVtx_segnale= new TH1F("hanti_DCANegToPrimVtx_segnale","aiuto ho dimenticato il titolo", 200, 0, 38);
hanti_DCANegToPrimVtx->SetLineColor(6);  // fucsia l'originale
hanti_DCANegToPrimVtx_fondo->SetLineColor(2); //rosso il fondo
hanti_DCANegToPrimVtx_segnale->SetLineColor(3); //verde segnale
//
TH1F* hanti_CascCosToPointingAngle= new TH1F("hanti_CascCosToPointingAngle","aiuto ho dimenticato il titolo",200, 0.948, 1.002);
TH1F* hanti_CascCosToPointingAngle_fondo= new TH1F("hanti_CascCosToPointingAngle_fondo","aiuto ho dimenticato il titolo", 200, 0.948, 1.002);
TH1F* hanti_CascCosToPointingAngle_segnale= new TH1F("hanti_CascCosToPointingAngle_segnale","aiuto ho dimenticato il titolo", 200, 0.948, 1.002);
hanti_CascCosToPointingAngle->SetLineColor(6);  // fucsia l'originale
hanti_CascCosToPointingAngle_fondo->SetLineColor(2); //rosso il fondo
hanti_CascCosToPointingAngle_segnale->SetLineColor(3); //verde segnale
//
TH1F* hanti_CascDCAtoPVxy= new TH1F("hanti_CascDCAtoPVxy","aiuto ho dimenticato il titolo",200, 0, 11);
TH1F* hanti_CascDCAtoPVxy_fondo= new TH1F("hanti_CascDCAtoPVxy_fondo","aiuto ho dimenticato il titolo", 200, 0, 11);
TH1F* hanti_CascDCAtoPVxy_segnale= new TH1F("hanti_CascDCAtoPVxy_segnale","aiuto ho dimenticato il titolo", 200, 0, 11);
hanti_CascDCAtoPVxy->SetLineColor(6);  // fucsia l'originale
hanti_CascDCAtoPVxy_fondo->SetLineColor(2); //rosso il fondo
hanti_CascDCAtoPVxy_segnale->SetLineColor(3); //verde segnale
//
TH1F* hanti_CascRadius= new TH1F("hanti_CascRadius","aiuto ho dimenticato il titolo",200, 0, 95);
TH1F* hanti_CascRadius_fondo= new TH1F("hanti_CascRadius_fondo","aiuto ho dimenticato il titolo", 200, 0, 95);
TH1F* hanti_CascRadius_segnale= new TH1F("hanti_CascRadius_segnale","aiuto ho dimenticato il titolo", 200, 0, 95);
hanti_CascRadius->SetLineColor(6);  // fucsia l'originale
hanti_CascRadius_fondo->SetLineColor(2); //rosso il fondo
hanti_CascRadius_segnale->SetLineColor(3); //verde segnale
//
TH1F* hanti_V0CosPointingAngle= new TH1F("hanti_V0CosPointingAngle","aiuto ho dimenticato il titolo",200, 0.979, 1.001);
TH1F* hanti_V0CosPointingAngle_fondo= new TH1F("hanti_V0CosPointingAngle_fondo", "aiuto ho dimenticato il titolo",200, 0.979, 0.001);
TH1F* hanti_V0CosPointingAngle_segnale= new TH1F("hanti_V0CosPointingAngle_segnale","aiuto ho dimenticato il titolo", 200, 0, 0.6);
hanti_V0CosPointingAngle->SetLineColor(6);  // fucsia l'originale
hanti_V0CosPointingAngle_fondo->SetLineColor(2); //rosso il fondo
hanti_V0CosPointingAngle_segnale->SetLineColor(3); //verde segnale
//
TH1F* hanti_V0Radius= new TH1F("hanti_V0Radius","aiuto ho dimenticato il titolo",200, 0, 200);
TH1F* hanti_V0Radius_fondo= new TH1F("hanti_V0Radius_fondo", "aiuto ho dimenticato il titolo",200, 0, 200);
TH1F* hanti_V0Radius_segnale= new TH1F("hanti_V0Radius_segnale","aiuto ho dimenticato il titolo", 200, 0, 200);
hanti_V0Radius->SetLineColor(6);  // fucsia l'originale
hanti_V0Radius_fondo->SetLineColor(2); //rosso il fondo
hanti_V0Radius_segnale->SetLineColor(3); //verde segnale
//
//
// 
//cominciamo scrivendo le funzioni per le particelle e antiparticelle; chiaramente, hanno i parametri fissati (quelli del fit)
//cominciamo dalle ANTIPARTICELLE
TF1* funz_segnale_anti_csi= new TF1("funz_segnale_anti_csi", "gaus(0)", 1.3, 1.35 );
funz_segnale_anti_csi->FixParameter(0, A2);
funz_segnale_anti_csi->FixParameter(1, mu2);
funz_segnale_anti_csi->FixParameter(2, sigma2);
//
TF1* funz_anti_csi= new TF1("funz_anti_csi", "gaus(0)+pol3(3)", 1.3, 1.35);
funz_anti_csi->FixParameter(0, A2);
funz_anti_csi->FixParameter(1, mu2);
funz_anti_csi->FixParameter(2, sigma2);
funz_anti_csi->FixParameter(0, p10);
funz_anti_csi->FixParameter(1, p11);
funz_anti_csi->FixParameter(2, p12);
funz_anti_csi->FixParameter(3, p13);
//
TF1* funz_fondo_anti_csi= new TF1("funz_fondo_anti_csi", "pol3(0)", 1.3, 1.35);
funz_fondo_anti_csi->FixParameter(0, p10);
funz_fondo_anti_csi->FixParameter(1, p11);
funz_fondo_anti_csi->FixParameter(2, p12);
funz_fondo_anti_csi->FixParameter(3, p13);
//
//ricordiamo che len è una variabile che contiene il numero di elementi del tree
//
double W=0; //è il weight
double a_W=0; //è 1-W, l'anti-peso :)
double somma=0;

for(int i=i; i<=num_bin_massa; i++){//i 300 bin della massa; andiamo dal primo all'ultimo
    double mi= hmass_anti_csi->GetBinCenter(i); //massa invariante al centro di ogni bin del grafico originale delle masse 
    double altezza= funz_segnale_anti_csi->Eval(mi);
    somma+=altezza;
    
}
cout<<"la somma vale "<<somma<<endl;
for(int i=1; i<num_bin_massa; i++){
    double mi= hmass_anti_csi->GetBinCenter(i);
     
    W= funz_segnale_anti_csi->Eval(mi)/somma;//valore del peso
    a_W= 1-W; //valore dell'antipeso}
    //if(1.321<mass_csi && mass_csi<1.322) cout<<W<< " "<<a_W<<endl;
    hanti_DCACascDaughters->Fill(DCACascDaughters); //segnale
    hanti_DCACascDaughters_fondo->Fill(DCACascDaughters, a_W);
    hanti_DCACascDaughters_segnale->Fill(DCACascDaughters, W);
    //
    hanti_DCABachToPrimVtx->Fill(DCABachToPrimVtx);  // fucsia l'originale
    hanti_DCABachToPrimVtx_fondo->Fill(DCABachToPrimVtx, a_W); //rosso il fondo
    hanti_DCABachToPrimVtx_segnale->Fill(DCABachToPrimVtx, W);
    //
    hanti_DCAV0Daughters->Fill(DCAV0Daughters);  // fucsia l'originale
    hanti_DCAV0Daughters_fondo->Fill(DCAV0Daughters, a_W);  //rosso il fondo
    hanti_DCAV0Daughters_segnale->Fill(DCAV0Daughters, W);
    //
    hanti_DCAV0ToPrimVtx->Fill(DCAV0ToPrimVtx); // fucsia l'originale
    hanti_DCAV0ToPrimVtx_fondo->Fill(DCAV0ToPrimVtx, a_W); //rosso il fondo
    hanti_DCAV0ToPrimVtx_segnale->Fill(DCAV0ToPrimVtx, W);
    //
    hanti_DCAPosToPrimVtx->Fill(DCAPosToPrimVtx);  // fucsia l'originale
    hanti_DCAPosToPrimVtx_fondo->Fill(DCAPosToPrimVtx, a_W); //rosso il fondo
    hanti_DCAPosToPrimVtx_segnale->Fill(DCAPosToPrimVtx, W); 
    //
    hanti_DCANegToPrimVtx->Fill(DCANegToPrimVtx); // fucsia l'originale
    hanti_DCANegToPrimVtx_fondo->Fill(DCANegToPrimVtx, a_W); //rosso il fondo
    hanti_DCANegToPrimVtx_segnale->Fill(DCANegToPrimVtx, W);
    //
    hanti_CascCosToPointingAngle->Fill(CascCosToPointingAngle);  // fucsia l'originale
    hanti_CascCosToPointingAngle_fondo->Fill(CascCosToPointingAngle, a_W);  //rosso il fondo
    hanti_CascCosToPointingAngle_segnale->Fill(CascCosToPointingAngle, W);
    //
    hanti_CascDCAtoPVxy->Fill(CascDCAtoPVxy);  // fucsia l'originale
    hanti_CascDCAtoPVxy_fondo->Fill(CascDCAtoPVxy, a_W); //rosso il fondo
    hanti_CascDCAtoPVxy_segnale->Fill(CascDCAtoPVxy, W);
    //
    hanti_CascRadius->Fill(CascRadius); // fucsia l'originale
    hanti_CascRadius_fondo->Fill(CascRadius, a_W);  //rosso il fondo
    hanti_CascRadius_segnale->Fill(CascRadius, W); 
    //
    hanti_V0CosPointingAngle->Fill(V0CosPointingAngle); // fucsia l'originale
    hanti_V0CosPointingAngle_fondo->Fill(V0CosPointingAngle, a_W); //rosso il fondo
    hanti_V0CosPointingAngle_segnale->Fill(V0CosPointingAngle, W);
    //
    hanti_V0Radius->Fill(V0Radius);  // fucsia l'originale
    hanti_V0Radius_fondo->Fill(V0Radius, a_W); //rosso il fondo
    hanti_V0Radius_segnale->Fill(V0Radius, W); //verde segnale
    
}








TCanvas* c2= new TCanvas("c2", "foglio 1 ANTI_CSI", 1000, 800);
c2->Divide(2, 2);
TCanvas* c3= new TCanvas("c3", "foglio 2 ANTI_CSI", 1000, 800);
c3->Divide(2,2);
TCanvas* c4= new TCanvas("c4", "foglio 3 ANTI_CSI", 1000, 800);
c4->Divide(2,2);

c2->cd(1);
hanti_DCACascDaughters->Draw();
hanti_DCACascDaughters->SetTitle("hanti_DCACascDaughters");
hanti_DCACascDaughters_fondo->Draw("SAME"); //rosso il fondo
hanti_DCACascDaughters_segnale->Draw("SAME");
//

c2->cd(2);
hanti_DCABachToPrimVtx->Draw(); 
hanti_DCABachToPrimVtx->SetTitle("hanti_DCABachToPrimVtx");
hanti_DCABachToPrimVtx_fondo->Draw("SAME"); //rosso il fondo
hanti_DCABachToPrimVtx_segnale->Draw("SAME");
//
c2->cd(3);
hanti_DCAV0Daughters->Draw(); 
hanti_DCAV0Daughters->SetTitle("hanti_DCAV0Daughters");
hanti_DCAV0Daughters_fondo->Draw("SAME");//rosso il fondo
hanti_DCAV0Daughters_segnale->Draw("SAME");
//
c2->cd(4);
hanti_DCAV0ToPrimVtx->Draw(); // fucsia l'originale
hanti_DCAV0ToPrimVtx->SetTitle("hanti_DCAV0ToPrimVtx");
hanti_DCAV0ToPrimVtx_fondo->Draw("SAME"); //rosso il fondo
hanti_DCAV0ToPrimVtx_segnale->Draw("SAME");
//
c3->cd(1);
hanti_DCAPosToPrimVtx->Draw(); // fucsia l'originale
hanti_DCAPosToPrimVtx->SetTitle("hanti_DCAPosToPrimVtx");
hanti_DCAPosToPrimVtx_fondo->Draw("SAME"); //rosso il fondo
hanti_DCAPosToPrimVtx_segnale->Draw("SAME");
//
c3->cd(2);
hanti_DCANegToPrimVtx->Draw(); // fucsia l'originale
hanti_DCANegToPrimVtx->SetTitle("hanti_DCANegToPrimVtx");
hanti_DCANegToPrimVtx_fondo->Draw("SAME");//rosso il fondo
hanti_DCANegToPrimVtx_segnale->Draw("SAME"); //verde segnale
//
c3->cd(3);
hanti_CascCosToPointingAngle->Draw(); 
hanti_CascCosToPointingAngle->SetTitle("hanti_CascCosToPointingAngle");// fucsia l'originale
hanti_CascCosToPointingAngle_fondo->Draw("SAME");//rosso il fondo
hanti_CascCosToPointingAngle_segnale->Draw("SAME"); //verde segnale
//
c3->cd(4);
hanti_CascDCAtoPVxy->Draw();  // fucsia l'originale
hanti_CascDCAtoPVxy->SetTitle("hanti_CascDCAtoPVxy");
hanti_CascDCAtoPVxy_fondo->Draw("SAME");  //rosso il fondo
hanti_CascDCAtoPVxy_segnale->Draw("SAME");  //verde segnale
//
c4->cd(1);
hanti_CascRadius->Draw(); 
hanti_CascRadius->SetTitle("hanti_CascRadius"); 
hanti_CascRadius_fondo->Draw("SAME");//rosso il fondo
hanti_CascRadius_segnale->Draw("SAME");
//
c4->cd(2);
hanti_V0CosPointingAngle->Draw();// fucsia l'originale
hanti_V0CosPointingAngle->SetTitle("hanti_V0CosPointingAngle");
hanti_V0CosPointingAngle_fondo->Draw("SAME");//rosso il fondo
hanti_V0CosPointingAngle_segnale->Draw("SAME");
//
c4->cd(3);
hanti_V0Radius->Draw(); // fucsia l'originale
hanti_V0Radius->SetTitle("hanti_V0Radius");
hanti_V0Radius_fondo->Draw("SAME");//rosso il fondo
hanti_V0Radius_segnale->Draw("SAME");//verde segnale




}