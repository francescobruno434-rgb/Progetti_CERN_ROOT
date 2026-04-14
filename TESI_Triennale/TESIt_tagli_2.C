#include<iostream>
#include<cmath>
#include<vector>
#include "TCanvas.h"
#include "TF1.h"
#include "TH1F.h"
#include "TTree.h"
#include "TFile.h"
using namespace std;


//AGGIORNATO 14/04/2026; NON USARE IL 3!

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

void TESIt_tagli_2(){
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
    //
    //creiamo gli istogrammi con dentro solo le masse delle csi e delle anti-csi (antiparticelle di carica positiva)
    TH1F* hmass_csi= new TH1F("mass_csi", "massa delle particelle \Csi^-", 300, 1.3, 1.35);
    TH1F* hmass_anti_csi= new TH1F("mass_anti_csi", "massa delle anti particelle \Csi^+", 300, 1.3, 1.35);
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
    //funzioni di fit massa csi: GAUSSIANA+POLINOMIALE
    /*TF1* fit_massa_csi= new TF1("fit_massa_csi", "gaus(0)+ pol3(3)", 1.3, 1.35);
    fit_massa_csi->SetParameters(350, 1.32171, 0.003, 20750, -2671, -2280, -3400);
    fit_massa_csi->SetParLimits(0, 300, 350);
    fit_massa_csi->SetParLimits(1, 1.321, 1.32171);
    fit_massa_csi->SetParLimits(2, 0.003, 0.004);
    fit_massa_csi->SetParLimits(3, 17290, 17300);
    fit_massa_csi->SetParLimits(4, -2670, -2671);
    fit_massa_csi->SetParLimits(5, -2240, -2241);
    fit_massa_csi->SetParLimits(6, -2020, -2021);*/
    //FUNZIONE DI PROVA NUMERO 1: GAUSSIANA+ POLINOMIALE
    /*
    TF1* csi_gr= new TF1("csi_gr", "gaus(0)+ pol3(3)", 1.3, 1.35);

    csi_gr->FixParameter(0, 350);
    csi_gr->FixParameter(1, 1.32171);
    csi_gr->FixParameter(2, 0.003);
    csi_gr->FixParameter(3, 20750);
    csi_gr->FixParameter(4, -2671);
    csi_gr->FixParameter(5, -2280);
    csi_gr->FixParameter(6, -3400);
    */
    //
    //
    //
    //FUNZIONE DI FIT MASSA CSI:ESPONENZIALE+ GAUSSIANA
    //

   /*TF1* fit_massa_csi2= new TF1("fit_massa_csi2", "gaus(0)+exp([3]- x*[4])+pol7(5)", 1.3, 1.35);
    fit_massa_csi2->SetParameters(350, 1.32171, 0.003, 16, 5.31,  0,  0, 0 ,  0, 0, 0 );
    fit_massa_csi2->SetParameter(11, 0);
    fit_massa_csi2->SetParameter(12, 0);
    fit_massa_csi2->SetParLimits(1, 1.32, 1.322);
    fit_massa_csi2->SetParLimits(0, 200, 1000);
   fit_massa_csi2->SetParLimits(2, 0, 0.05);
   fit_massa_csi2->SetParLimits(3, 15, 16);
   fit_massa_csi2->SetParLimits(4, 5, 6);*/
    TF1* fit_massa_csi2= new TF1("fit_massa_csi2", "gaus(0)+pol3(3)", 1.3, 1.35);
    fit_massa_csi2->SetParameters(250, 1.32171, 0.003, 285300,  -411500, 150000, 0);
    fit_massa_csi2->SetParLimits(1, 1.32, 1.322);
    fit_massa_csi2->SetParLimits(0, 150, 1000);
   fit_massa_csi2->SetParLimits(2, 0, 0.05);
  





    //disegniamo gli istogrammi
    c1->cd(1);
    c1->SetGrid();
    //hmass_csi->Fit("fit_massa_csi", "R");
    hmass_csi->Fit("fit_massa_csi2", "R");
    hmass_csi->Draw();
     hmass_csi->SetTitle("massa della csi");
     //
     //queste righe restituiscono i parametri di git
     double A1= fit_massa_csi2->GetParameter(0);
     double mu1= fit_massa_csi2->GetParameter(1);
     double sigma1= fit_massa_csi2->GetParameter(2);
     double p00= fit_massa_csi2->GetParameter(3);
     double p01= fit_massa_csi2->GetParameter(4);
     double p02= fit_massa_csi2->GetParameter(5);
     double p03= fit_massa_csi2->GetParameter(6);
    
    cout<<"il p-value è: "<<fit_massa_csi2->GetProb()<<endl;
    














     //funzioni di fit anti csi
   /* TF1* fit_massa_anti_csi= new TF1("fit_massa_anti_csi", "gaus(0)+exp([3]- x*[4])+pol7(5)", 1.3, 1.35);
    fit_massa_anti_csi->SetParameters(350, 1.32171, 0.003, 13.96, 4.46, 0, 0, 0, 0, 0, 0);
    fit_massa_anti_csi->SetParameter(11, 0);
    fit_massa_anti_csi->SetParameter(12, 0);
    fit_massa_anti_csi->SetParLimits(1, 1.32, 1.322);
    fit_massa_anti_csi->SetParLimits(0, 200, 1000);
   fit_massa_anti_csi->SetParLimits(2, 0, 0.05);
   fit_massa_anti_csi->SetParLimits(3, 13.5, 14.5);
   fit_massa_anti_csi->SetParLimits(4, 4, 5);*/
TF1* fit_massa_anti_csi= new TF1("fit_massa_anti_csi", "gaus(0)+pol3(3)", 1.3, 1.35);
    fit_massa_anti_csi->SetParameters(150, 1.32171, 0.003, 370100, -542000,  200000, 0);
    fit_massa_anti_csi->SetParLimits(1, 1.32, 1.322);
    fit_massa_anti_csi->SetParLimits(0, 100, 1000);
   fit_massa_anti_csi->SetParLimits(2, 0, 0.05);
  


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
tree->SetBranchAddress("fTreeCascVarCascCosToPointingAngle", &CascCosToPointingAngle);
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
TH1F* hanti_DCACascDaughters= new TH1F("hanti_DCACascDaughters",200, 0, 0.6);
TH1F* hanti_DCACascDaughters_fondo= new TH1F("hanti_DCACascDaughters_fondo", 200, 0, 0.6);
TH1F* hanti_DCACascDaughters_segnale= new TH1F("hanti_DCACascDaughters_segnale", 200, 0, 0.6);
//



















//cominciamo scrivendo le funzioni per le particelle e antiparticelle; chiaramente, hanno i parametri fissati (quelli del fit)
//cominciamo dalle ANTIPARTICELLE
TF1* funz_peso_anti_csi= new TF1("funz_peso_anti_csi", "gaus(0)+pol3(3)", 1.3, 1.35 );
funz_peso_anti_csi->FixParameter(0, A2);
funz_peso_anti_csi->FixParameter(1, mu2);
funz_peso_anti_csi->FixParameter(2, sigma2);
funz_peso_anti_csi->FixParameter(3, p10);
funz_peso_anti_csi->FixParameter(4, p11);
funz_peso_anti_csi->FixParameter(5, p12);
funz_peso_anti_csi->FixParameter(6, p13);







}