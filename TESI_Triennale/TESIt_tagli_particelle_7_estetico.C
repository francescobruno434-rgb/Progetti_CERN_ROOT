#include<iostream>
#include<cmath>
#include<vector>
#include "TCanvas.h"
#include "TF1.h"
#include "TH1F.h"
#include "TTree.h"
#include "TFile.h"
#include<iomanip>
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

void TESIt_tagli_particelle_7_estetico(){
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
    tree->SetBranchAddress("fTreeCascVarMassAsXi", &mass_csi);
    tree->SetBranchAddress("fTreeCascVarCharge", &charge);  
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
    //creiamo gli istogrammi con dentro solo le masse delle csi e delle anti-csi (antiparticelle di carica positiva)
    TH1F* hmass_csi= new TH1F("mass_csi", "massa delle particelle #Csi^-", 1000, 1.3, 1.35);
    TH1F* hmass_anti_csi= new TH1F("mass_anti_csi", "massa delle anti particelle #Csi^+", 1000, 1.3, 1.35);
    int num_bin_massa=1000;
    //
    //numero di entries
    int len= tree->GetEntries();
    //
    //
    for(int i=0; i<len; i++){
        tree->GetEntry(i);
        //&& CascCosToPointingAngle>0.98 && V0CosPointingAngle>0.99 && DCAV0Daughters<0.3 && DCABachToPrimVtx<5
        if(charge<=0 &&   DCAV0Daughters<0.05 && DCAV0ToPrimVtx<2 && DCAPosToPrimVtx <3 && DCANegToPrimVtx <3 && CascCosToPointingAngle > 0.99 && CascDCAtoPVxy <1 && CascRadius <20 && V0CosPointingAngle>0.995 &&  V0Radius <60){
            hmass_csi->Fill(mass_csi);
        }
        if(charge>0 &&   DCAV0Daughters<0.05 && DCAV0ToPrimVtx<2 && DCAPosToPrimVtx <3 && DCANegToPrimVtx <3 && CascCosToPointingAngle > 0.99 && CascDCAtoPVxy <1 && CascRadius <20 && V0CosPointingAngle>0.995 &&  V0Radius <60  ){
            hmass_anti_csi->Fill(mass_csi );
        }

    }
     //funzione di fit particelle
    TF1* fit_massa_csi2= new TF1("fit_massa_csi2", "gaus(0)+pol3(3)", 1.3, 1.35);
    fit_massa_csi2->SetParameters(25, 1.32171, 0.003, 6371.5,  -9435, 3500, 0);
    fit_massa_csi2->SetParLimits(1, 1.32, 1.322);
    fit_massa_csi2->SetParLimits(0, 0, 300);
    //fit_massa_csi2->SetParLimits(2, 0, 0.05);
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
    fit_massa_anti_csi->SetParameters(15, 1.32171, 0.003, 6371.5,  -9435, 3500, 0);
    fit_massa_anti_csi->SetParLimits(1, 1.32, 1.322);
    fit_massa_anti_csi->SetParLimits(0, 0, 1000);
    //fit_massa_anti_csi->SetParLimits(2, 0, 0.05);
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
    c1->Print("fit_masse_molto_fine.png", "png");

    /*++++++++++++++++DA QUI PARTE DEI PESI++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    
    #################################################################################################################################
    
    ################################################################################################################################*/

    //
    /*sia per particelle che per antiparticelle, bisogna fare 3 istogrammi per ogni variabile: uno per la grandezza stessa uno per il fondo e 
    uno per il segnale; per comodità, iniziamo dalle antiparticelle*/
    //
    //############################################################################################
    //ISTOGRAMMI ANTIPARTICELLE
    //
    TH1F* h_DCACascDaughters= new TH1F("h_DCACascDaughters","h_DCACascDaughters",200, 0, 0.51);
    TH1F* h_DCACascDaughters_fondo= new TH1F("h_DCACascDaughters_fondo","h_DCACascDaughters", 200, 0, 0.51);
    TH1F* h_DCACascDaughters_segnale= new TH1F("h_DCACascDaughters_segnale", "h_DCACascDaughters",200, 0, 0.51);
    h_DCACascDaughters->SetLineColor(4);  // blu l'originale
    h_DCACascDaughters_fondo->SetLineColor(2); //rosso il fondo
    h_DCACascDaughters_segnale->SetLineColor(3); //verde segnale
    //
    TH1F* h_DCABachToPrimVtx= new TH1F("h_DCABachToPrimVtx","h_DCABachToPrimVtx",200, 0, 5);
    TH1F* h_DCABachToPrimVtx_fondo= new TH1F("h_DCABachToPrimVtx_fondo","h_DCABachToPrimVtx", 200, 0, 5);
    TH1F* h_DCABachToPrimVtx_segnale= new TH1F("h_DCABachToPrimVtx_segnale","h_DCABachToPrimVtx", 200, 0, 5);
    h_DCABachToPrimVtx->SetLineColor(4);  // fucsia l'originale
    h_DCABachToPrimVtx_fondo->SetLineColor(2); //rosso il fondo
    h_DCABachToPrimVtx_segnale->SetLineColor(3); //verde segnale
    //
    TH1F* h_DCAV0Daughters= new TH1F("h_DCAV0Daughters","h_DCAV0Daughters",200, 0, 0.05);
    TH1F* h_DCAV0Daughters_fondo= new TH1F("h_DCAV0Daughters_fondo","h_DCAV0Daughters", 200, 0, 0.05);
    TH1F* h_DCAV0Daughters_segnale= new TH1F("h_DCAV0Daughters_segnale", "h_DCAV0Daughters",200, 0, 0.05);
    h_DCAV0Daughters->SetLineColor(4);  // fucsia l'originale
    h_DCAV0Daughters_fondo->SetLineColor(2); //rosso il fondo
    h_DCAV0Daughters_segnale->SetLineColor(3); //verde segnale
    //
    TH1F* h_DCAV0ToPrimVtx= new TH1F("h_DCAV0ToPrimVtx","h_DCAV0ToPrimVtx",200, 0, 2);
    TH1F* h_DCAV0ToPrimVtx_fondo= new TH1F("h_DCAV0ToPrimVtx_fondo","h_DCAV0ToPrimVtx", 200, 0, 2);
    TH1F* h_DCAV0ToPrimVtx_segnale= new TH1F("h_DCAV0ToPrimVtx_segnale","h_DCAV0ToPrimVtx", 200, 0, 2);
    h_DCAV0ToPrimVtx->SetLineColor(4);  // fucsia l'originale
    h_DCAV0ToPrimVtx_fondo->SetLineColor(2); //rosso il fondo
    h_DCAV0ToPrimVtx_segnale->SetLineColor(3); //verde segnale
    //
    TH1F* h_DCAPosToPrimVtx= new TH1F("h_DCAPosToPrimVtx","h_DCAPosToPrimVtx",200, 0, 3);
    TH1F* h_DCAPosToPrimVtx_fondo= new TH1F("h_DCAPosToPrimVtx_fondo","h_DCAPosToPrimVtx", 200, 0, 3);
    TH1F* h_DCAPosToPrimVtx_segnale= new TH1F("h_DCAPosToPrimVtx_segnale","h_DCAPosToPrimVtx", 200, 0, 3);
    h_DCAPosToPrimVtx->SetLineColor(4);  // fucsia l'originale
    h_DCAPosToPrimVtx_fondo->SetLineColor(2); //rosso il fondo
    h_DCAPosToPrimVtx_segnale->SetLineColor(3); //verde segnale
    //
    TH1F* h_DCANegToPrimVtx= new TH1F("h_DCANegToPrimVtx","h_DCANegToPrimVtx",200, 0, 3);
    TH1F* h_DCANegToPrimVtx_fondo= new TH1F("h_DCANegToPrimVtx_fondo","h_DCANegToPrimVtx", 200, 0, 3);
    TH1F* h_DCANegToPrimVtx_segnale= new TH1F("h_DCANegToPrimVtx_segnale","h_DCANegToPrimVtx", 200, 0, 3);
    h_DCANegToPrimVtx->SetLineColor(4);  // fucsia l'originale
    h_DCANegToPrimVtx_fondo->SetLineColor(2); //rosso il fondo
    h_DCANegToPrimVtx_segnale->SetLineColor(3); //verde segnale
    //
    TH1F* h_CascCosToPointingAngle= new TH1F("h_CascCosToPointingAngle","h_CascCosToPointingAngle",200, 0.99, 1.002);
    TH1F* h_CascCosToPointingAngle_fondo= new TH1F("h_CascCosToPointingAngle_fondo","h_CascCosToPointingAngle", 200, 0.99, 1.002);
    TH1F* h_CascCosToPointingAngle_segnale= new TH1F("h_CascCosToPointingAngle_segnale","h_CascCosToPointingAngle", 200, 0.99, 1.002);
    h_CascCosToPointingAngle->SetLineColor(4);  // fucsia l'originale
    h_CascCosToPointingAngle_fondo->SetLineColor(2); //rosso il fondo
    h_CascCosToPointingAngle_segnale->SetLineColor(3); //verde segnale
    //
    TH1F* h_CascDCAtoPVxy= new TH1F("h_CascDCAtoPVxy","h_CascDCAtoPVxy",200, 0, 1);
    TH1F* h_CascDCAtoPVxy_fondo= new TH1F("h_CascDCAtoPVxy_fondo","h_CascDCAtoPVxy", 200, 0, 1);
    TH1F* h_CascDCAtoPVxy_segnale= new TH1F("h_CascDCAtoPVxy_segnale","h_CascDCAtoPVxy", 200, 0, 1);
    h_CascDCAtoPVxy->SetLineColor(4);  // fucsia l'originale
    h_CascDCAtoPVxy_fondo->SetLineColor(2); //rosso il fondo
    h_CascDCAtoPVxy_segnale->SetLineColor(3); //verde segnale
    //
    TH1F* h_CascRadius= new TH1F("h_CascRadius","h_CascRadius",200, 0, 20);
    TH1F* h_CascRadius_fondo= new TH1F("h_CascRadius_fondo","h_CascRadius", 200, 0, 20);
    TH1F* h_CascRadius_segnale= new TH1F("h_CascRadius_segnale","h_CascRadius", 200, 0, 20);
    h_CascRadius->SetLineColor(4);  // fucsia l'originale
    h_CascRadius_fondo->SetLineColor(2); //rosso il fondo
    h_CascRadius_segnale->SetLineColor(3); //verde segnale
    //
    TH1F* h_V0CosPointingAngle= new TH1F("h_V0CosPointingAngle","h_V0CosPointingAngle",200, 0.995, 1.001);
    TH1F* h_V0CosPointingAngle_fondo= new TH1F("h_V0CosPointingAngle_fondo", "h_V0CosPointingAngle",200, 0.995,1.001);
    TH1F* h_V0CosPointingAngle_segnale= new TH1F("h_V0CosPointingAngle_segnale","h_V0CosPointingAngle", 200, 0.995, 1.001);
    h_V0CosPointingAngle->SetLineColor(4);  // fucsia l'originale
    h_V0CosPointingAngle_fondo->SetLineColor(2); //rosso il fondo
    h_V0CosPointingAngle_segnale->SetLineColor(3); //verde segnale
    //
    TH1F* h_V0Radius= new TH1F("h_V0Radius","h_V0Radius",200, 0, 60);
    TH1F* h_V0Radius_fondo= new TH1F("h_V0Radius_fondo", "h_V0Radius",200, 0, 60);
    TH1F* h_V0Radius_segnale= new TH1F("h_V0Radius_segnale","h_V0Radius", 200, 0, 60);
    h_V0Radius->SetLineColor(4);  // fucsia l'originale
    h_V0Radius_fondo->SetLineColor(2); //rosso il fondo
    h_V0Radius_segnale->SetLineColor(3); //verde segnale
    //
    //
    // 
    //cominciamo scrivendo le funzioni per le particelle e antiparticelle; chiaramente, hanno i parametri fissati (quelli del fit)
    //cominciamo dalle ANTIPARTICELLE
    TF1* funz_segnale_anti_csi= new TF1("funz_segnale_anti_csi", " gaus(0)", 1.3, 1.35 );
    funz_segnale_anti_csi->FixParameter(0, A1);
    funz_segnale_anti_csi->FixParameter(1, mu1);
    funz_segnale_anti_csi->FixParameter(2, sigma1);
    //
    TF1* funz_anti_csi= new TF1("funz_anti_csi", "gaus(0)+pol3(3)", 1.3, 1.35);
    funz_anti_csi->FixParameter(0, A1);
    funz_anti_csi->FixParameter(1, mu1);
    funz_anti_csi->FixParameter(2, sigma1);
    funz_anti_csi->FixParameter(3, p00);
    funz_anti_csi->FixParameter(4, p01);
    funz_anti_csi->FixParameter(5, p02);
    funz_anti_csi->FixParameter(6, p03);
    //
    TF1* funz_fondo_anti_csi= new TF1("funz_fondo_anti_csi", "pol3(0)", 1.3, 1.35);
    funz_fondo_anti_csi->FixParameter(0, p00);
    funz_fondo_anti_csi->FixParameter(1, p01);
    funz_fondo_anti_csi->FixParameter(2, p02);
    funz_fondo_anti_csi->FixParameter(3, p03);
    //
    //ricordiamo che len è una variabile che contiene il numero di elementi del tree
    //
    double W=0; //è il weight
    double a_W=0; //è 1-W, l'anti-peso :)
    //SI RIEMPIONO GLI ISTOGRAMMI
    for(int i=0; i<len; i++){
        tree->GetEntry(i);
        if(charge<0 &&  DCAV0Daughters<0.05 &&  DCAV0ToPrimVtx<2 && DCAPosToPrimVtx <3 && DCANegToPrimVtx <3 && CascCosToPointingAngle > 0.99 && CascDCAtoPVxy <1 && CascRadius <20 && V0CosPointingAngle>0.995 &&  V0Radius <60 ){//piglio solo le anti csi che hanno carica maggiore di 0
            W= funz_segnale_anti_csi->Eval(mass_csi)/funz_anti_csi->Eval(mass_csi);//valore del peso
            a_W= 1-W; //valore dell'antipeso}
            h_DCACascDaughters->Fill(DCACascDaughters); //segnale
            h_DCACascDaughters_fondo->Fill(DCACascDaughters, a_W); 
            h_DCACascDaughters_segnale->Fill(DCACascDaughters, W);
            //
            h_DCABachToPrimVtx->Fill(DCABachToPrimVtx);  // fucsia l'originale
            h_DCABachToPrimVtx_fondo->Fill(DCABachToPrimVtx, a_W); //rosso il fondo
            h_DCABachToPrimVtx_segnale->Fill(DCABachToPrimVtx, W);
            //
            h_DCAV0Daughters->Fill(DCAV0Daughters);  // fucsia l'originale
            h_DCAV0Daughters_fondo->Fill(DCAV0Daughters, a_W);  //rosso il fondo
            h_DCAV0Daughters_segnale->Fill(DCAV0Daughters, W);
            //
            h_DCAV0ToPrimVtx->Fill(DCAV0ToPrimVtx); // fucsia l'originale
            h_DCAV0ToPrimVtx_fondo->Fill(DCAV0ToPrimVtx, a_W); //rosso il fondo
            h_DCAV0ToPrimVtx_segnale->Fill(DCAV0ToPrimVtx, W);
            //
            h_DCAPosToPrimVtx->Fill(DCAPosToPrimVtx);  // fucsia l'originale
            h_DCAPosToPrimVtx_fondo->Fill(DCAPosToPrimVtx, a_W); //rosso il fondo
            h_DCAPosToPrimVtx_segnale->Fill(DCAPosToPrimVtx, W); 
            //
            h_DCANegToPrimVtx->Fill(DCANegToPrimVtx); // fucsia l'originale
            h_DCANegToPrimVtx_fondo->Fill(DCANegToPrimVtx, a_W); //rosso il fondo
            h_DCANegToPrimVtx_segnale->Fill(DCANegToPrimVtx, W);
            //
            h_CascCosToPointingAngle->Fill(CascCosToPointingAngle);  // fucsia l'originale
            h_CascCosToPointingAngle_fondo->Fill(CascCosToPointingAngle, a_W);  //rosso il fondo
            h_CascCosToPointingAngle_segnale->Fill(CascCosToPointingAngle, W);
            //
            h_CascDCAtoPVxy->Fill(CascDCAtoPVxy);  // fucsia l'originale
            h_CascDCAtoPVxy_fondo->Fill(CascDCAtoPVxy, a_W); //rosso il fondo
            h_CascDCAtoPVxy_segnale->Fill(CascDCAtoPVxy, W);
            //
            h_CascRadius->Fill(CascRadius); // fucsia l'originale
            h_CascRadius_fondo->Fill(CascRadius, a_W);  //rosso il fondo
            h_CascRadius_segnale->Fill(CascRadius, W); 
            //
            h_V0CosPointingAngle->Fill(V0CosPointingAngle); // fucsia l'originale
            h_V0CosPointingAngle_fondo->Fill(V0CosPointingAngle, a_W); //rosso il fondo
            h_V0CosPointingAngle_segnale->Fill(V0CosPointingAngle, W);
            //
            h_V0Radius->Fill(V0Radius);  // fucsia l'originale
            h_V0Radius_fondo->Fill(V0Radius, a_W); //rosso il fondo
            h_V0Radius_segnale->Fill(V0Radius, W); //verde segnale
        }
    }
    //
    TCanvas* c2= new TCanvas("c2", "foglio 1 CSI", 1000, 800);
    c2->Divide(2, 2);
    TCanvas* c3= new TCanvas("c3", "foglio 2 CSI", 1000, 800);
    c3->Divide(2,2);
    TCanvas* c4= new TCanvas("c4", "foglio 3 CSI", 1000, 800);
    c4->Divide(2,2);
    //
    c2->cd(1);
    h_DCACascDaughters->DrawNormalized();
    h_DCACascDaughters->SetTitle("h_DCACascDaughters");
    h_DCACascDaughters_fondo->DrawNormalized("SAME"); //rosso il fondo
    h_DCACascDaughters_segnale->DrawNormalized("SAME");
    
    //
    c2->cd(2);
    h_DCABachToPrimVtx->DrawNormalized(); 
    h_DCABachToPrimVtx->SetTitle("h_DCABachToPrimVtx");
    h_DCABachToPrimVtx_fondo->DrawNormalized("SAME"); //rosso il fondo
    h_DCABachToPrimVtx_segnale->DrawNormalized("SAME");
    //
    c2->cd(3);
    h_DCAV0Daughters->DrawNormalized(); 
    h_DCAV0Daughters->SetTitle("h_DCAV0Daughters");
    h_DCAV0Daughters_fondo->DrawNormalized("SAME");//rosso il fondo
    h_DCAV0Daughters_segnale->DrawNormalized("SAME");
    //
    c2->cd(4);
    h_DCAV0ToPrimVtx->DrawNormalized(); // fucsia l'originale
    h_DCAV0ToPrimVtx->SetTitle("h_DCAV0ToPrimVtx");
    h_DCAV0ToPrimVtx_fondo->DrawNormalized("SAME"); //rosso il fondo
    h_DCAV0ToPrimVtx_segnale->DrawNormalized("SAME");
    //
    c3->cd(1);
    h_DCAPosToPrimVtx->DrawNormalized(); // fucsia l'originale
    h_DCAPosToPrimVtx->SetTitle("h_DCAPosToPrimVtx");
    h_DCAPosToPrimVtx_fondo->DrawNormalized("SAME"); //rosso il fondo
    h_DCAPosToPrimVtx_segnale->DrawNormalized("SAME");
    //
    c3->cd(2);
    h_DCANegToPrimVtx->DrawNormalized(); // fucsia l'originale
    h_DCANegToPrimVtx->SetTitle("h_DCANegToPrimVtx");
    h_DCANegToPrimVtx_fondo->DrawNormalized("SAME");//rosso il fondo
    h_DCANegToPrimVtx_segnale->DrawNormalized("SAME"); //verde segnale
    //
    c3->cd(3);
    h_CascCosToPointingAngle->DrawNormalized(); 
    h_CascCosToPointingAngle->SetTitle("h_CascCosToPointingAngle");// fucsia l'originale
    h_CascCosToPointingAngle_fondo->DrawNormalized("SAME");//rosso il fondo
    h_CascCosToPointingAngle_segnale->DrawNormalized("SAME"); //verde segnale
    //
    c3->cd(4);
    h_CascDCAtoPVxy->DrawNormalized();  // fucsia l'originale
    h_CascDCAtoPVxy->SetTitle("h_CascDCAtoPVxy");
    h_CascDCAtoPVxy_fondo->DrawNormalized("SAME");  //rosso il fondo
    h_CascDCAtoPVxy_segnale->DrawNormalized("SAME");  //verde segnale
    //
    c4->cd(1);
    h_CascRadius->DrawNormalized(); 
    h_CascRadius->SetTitle("h_CascRadius"); 
    h_CascRadius_fondo->DrawNormalized("SAME");//rosso il fondo
    h_CascRadius_segnale->DrawNormalized("SAME");
    //
    c4->cd(2);
    h_V0CosPointingAngle->DrawNormalized();// fucsia l'originale
    h_V0CosPointingAngle->SetTitle("h_V0CosPointingAngle");
    h_V0CosPointingAngle_fondo->DrawNormalized("SAME");//rosso il fondo
    h_V0CosPointingAngle_segnale->DrawNormalized("SAME");
    //
    c4->cd(3);
    h_V0Radius->DrawNormalized(); // fucsia l'originale
    h_V0Radius->SetTitle("h_V0Radius");
    h_V0Radius_fondo->DrawNormalized("SAME");//rosso il fondo
    h_V0Radius_segnale->DrawNormalized("SAME");//verde segnale
    //
    TFile* output= new TFile("grafici_parametri.root", "UPDATE");
    c1->Write("csi foglio 1");
    c2->Write("csi foglio 2");
    c3->Write("csi foglio 3");
    c4->Write("csi foglio 4");
    output->Close();



}