#include<iostream>
#include<cmath>
#include<vector>
#include "TCanvas.h"
#include "TF1.h"
#include "TH1F.h"
#include "TTree.h"
#include "TFile.h"
using namespace std;





void TESIt_tagli_5(){
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
    TH1F* hmass_csi= new TH1F("mass_csi", "massa delle particelle Csi^-", 1000, 1.3, 1.35);
    TH1F* hmass_anti_csi= new TH1F("mass_anti_csi", "massa delle anti particelle Csi^+", 1000, 1.3, 1.35);
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
    //funzione di fit particelle
    TF1* fit_massa_csi2= new TF1("fit_massa_csi2", "gaus(0)+pol3(3)", 1.3, 1.35);
    fit_massa_csi2->SetParameters(110, 1.32171, 0.003, 208715,  -309150, 115000, 0);
    fit_massa_csi2->SetParLimits(1, 1.32, 1.322);
    fit_massa_csi2->SetParLimits(0, 10, 1000);
    fit_massa_csi2->SetParLimits(2, 0, 0.05);
    //
    //funzione di fit antiparticelle
     TF1* fit_massa_anti_csi= new TF1("fit_massa_anti_csi", "gaus(0)+pol3(3)", 1.3, 1.35);
    fit_massa_anti_csi->SetParameters(100, 1.32171, 0.003, 154905, -228850,  85000, 0);
    fit_massa_anti_csi->SetParLimits(1, 1.32, 1.322);
    fit_massa_anti_csi->SetParLimits(0, 10, 1000);
    fit_massa_anti_csi->SetParLimits(2, 0, 0.05);
    //disegniamo gli istogrammi
    c1->cd(1);
    c1->SetGrid();
    hmass_csi->Fit("fit_massa_csi2", "R");
    hmass_csi->Draw();
    hmass_csi->SetTitle("massa della csi");
    cout<<"il p-value è: "<<fit_massa_csi2->GetProb()<<endl;
      c1->cd(2);
    c1->SetGrid();
    hmass_anti_csi->Fit("fit_massa_anti_csi", "R");
    hmass_anti_csi->Draw();
    hmass_anti_csi->SetTitle("massa anti csi");
      cout<<"il p-value è: "<<fit_massa_anti_csi->GetProb()<<endl;
    //
    //variabili con i parametri del fit delle csi-
    double A1= fit_massa_csi2->GetParameter(0);
    double mu1= fit_massa_csi2->GetParameter(1);
    double sigma1= fit_massa_csi2->GetParameter(2);
    double p00= fit_massa_csi2->GetParameter(3);
    double p01= fit_massa_csi2->GetParameter(4);
    double p02= fit_massa_csi2->GetParameter(5);
    double p03= fit_massa_csi2->GetParameter(6);
    //
    //variabili con i parametri del fit delle anti csi (csi+)
    double A2= fit_massa_anti_csi->GetParameter(0);
     double mu2= fit_massa_anti_csi->GetParameter(1);
     double sigma2= fit_massa_anti_csi->GetParameter(2);
     double p10= fit_massa_anti_csi->GetParameter(3);
     double p11= fit_massa_anti_csi->GetParameter(4);
     double p12= fit_massa_anti_csi->GetParameter(5);
     double p13= fit_massa_anti_csi->GetParameter(6);
     //
    c1->cd(0);
    c1->Print("fit_masse_fine.png", "png");

     /*++++++++++++++++DA QUI PARTE DEI PESI++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    
    #################################################################################################################################
    
    ################################################################################################################################*/
    //
    //incomincio con le antiparticelle (csi+)
    TF1* funz_segnale_anti_csi= new TF1("funz_segnale_anti_csi", "(0.8362602442)*gaus(0)", 1.3, 1.35 );
    funz_segnale_anti_csi->FixParameter(0, A2);
    funz_segnale_anti_csi->FixParameter(1, mu2);
    funz_segnale_anti_csi->FixParameter(2, sigma2);
    //
    TF1* funz_anti_csi= new TF1("funz_anti_csi", "(0.8362602442)*gaus(0)+(0.0064450016)*pol3(3)", 1.3, 1.35);
    funz_anti_csi->FixParameter(0, A2);
    funz_anti_csi->FixParameter(1, mu2);
    funz_anti_csi->FixParameter(2, sigma2);
    funz_anti_csi->FixParameter(3, p10);
    funz_anti_csi->FixParameter(4, p11);
    funz_anti_csi->FixParameter(5, p12);
    funz_anti_csi->FixParameter(6, p13);
    //
    TF1* funz_fondo_anti_csi= new TF1("funz_fondo_anti_csi", "(0.0064450016)*pol3(0)", 1.3, 1.35);
    funz_fondo_anti_csi->FixParameter(0, p10);
    funz_fondo_anti_csi->FixParameter(1, p11);
    funz_fondo_anti_csi->FixParameter(2, p12);
    funz_fondo_anti_csi->FixParameter(3, p13);
    //
    //
    double W=0; //è il weight
    double a_W=0; //è 1-W, l'anti-peso

    TH1D* pesi= new TH1D("pesi", "pesi", 100, 0, 1);
    TCanvas* c100= new TCanvas("c100", "pesi", 800, 600);
    for (int i=1; i<1000; i++){
        float mi= hmass_anti_csi->GetBinCenter(i);
        double a=funz_segnale_anti_csi->Eval(mi);
        double b= funz_anti_csi->Eval(mi);
        W= a/b;
        pesi->Fill(W); 
    }
    c100->cd();
    pesi->Draw();
}