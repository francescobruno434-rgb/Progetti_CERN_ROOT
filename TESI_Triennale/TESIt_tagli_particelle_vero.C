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




void TESIt_tagli_particelle_vero(){
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
    float CascVarPt=0;
    tree->SetBranchAddress("fTreeCascVarPt", &CascVarPt);
    //     
    //creiamo gli istogrammi con dentro solo le masse delle csi e delle anti-csi (antiparticelle di carica positiva)
    TH1F* hmass_csi= new TH1F("mass_csi", "massa delle particelle #Csi^-", 200, 1.3, 1.35);
    TH1F* hmass_anti_csi= new TH1F("mass_anti_csi", "massa delle anti particelle #Csi^+",200, 1.3, 1.35);
    TH1F* Pt= new TH1F("Pt", "CascVarPt", 10, 0, 5); //NB: SOLO PER PARTICELLE (carica <0)
    TH1F* hmass_Pt1= new TH1F("hmass_Pt1", "Pt1", 40,  1.3, 1.35 );
    TH1F* hmass_Pt2= new TH1F("hmass_Pt2", "Pt2", 60,  1.3, 1.35 );
    TH1F* hmass_Pt3= new TH1F("hmass_Pt3", "Pt3", 30,  1.3, 1.34 );
    TH1F* hmass_Pt4= new TH1F("hmass_Pt4", "Pt4", 30,  1.3, 1.345 );
    TH1F* hmass_Pt5= new TH1F("hmass_Pt5", "Pt5", 30,  1.3, 1.345 );
    TH1F* hmass_Pt6= new TH1F("hmass_Pt6", "Pt6", 30,  1.3, 1.335 );
    TH1F* hmass_Pt7= new TH1F("hmass_Pt7", "Pt7", 30,  1.315, 1.326 );
    TH1F* hmass_Pt8= new TH1F("hmass_Pt8", "Pt8", 30,  1.316, 1.323 );
    TH1F* hmass_Pt9= new TH1F("hmass_Pt9", "Pt9", 30,  1.322, 1.328 );
    TH1F* hmass_Pt10= new TH1F("hmass_P105", "Pt10", 60,  1.319, 1.328 );
    int num_bin_massa=1000;
    //
    //numero di entries
    int len= tree->GetEntries();
    //
    //
    for(int i=0; i<len; i++){
        tree->GetEntry(i);
        //&& CascCosToPointingAngle>0.98 && V0CosPointingAngle>0.99 && DCAV0Daughters<0.3 && DCABachToPrimVtx<5
        if(charge<=0 && DCACascDaughters<0.1 && DCABachToPrimVtx >0.1 &&  DCAV0Daughters<0.01 && DCAV0ToPrimVtx<1 && DCAPosToPrimVtx <1 && DCANegToPrimVtx <1 && CascCosToPointingAngle > 0.999 && CascDCAtoPVxy <0.2 && CascRadius <10 && V0CosPointingAngle>0.999 &&  V0Radius <20){
            hmass_csi->Fill(mass_csi);
            Pt->Fill(CascVarPt);
            int num_bin=Pt->FindBin(CascVarPt); //ottengo il numero del bin da mettere poi per lo spettro di massa invariante
            //cout<<CascVarPt<< " "<<num_bin<<" "<<endl;
            if(num_bin==1){
                hmass_Pt1->Fill(mass_csi); //metti la massa
            }
             else if(num_bin==2){
                hmass_Pt2->Fill(mass_csi); //metti la massa
            }
             else if(num_bin==3){
                hmass_Pt3->Fill(mass_csi); //metti la massa
            }
             else if(num_bin==4){
                hmass_Pt4->Fill(mass_csi); //metti la massa
            }
             else if(num_bin==5){
                hmass_Pt5->Fill(mass_csi); //metti la massa
            }
            else if(num_bin==6){
                hmass_Pt6->Fill(mass_csi); //metti la massa
            }
              else if(num_bin==7){
                hmass_Pt7->Fill(mass_csi); //metti la massa
            }
             else if(num_bin==8){
                hmass_Pt8->Fill(mass_csi); //metti la massa
            }
             else if(num_bin==9){
                hmass_Pt9->Fill(mass_csi); //metti la massa
            }
            else if(num_bin==10){
                hmass_Pt10->Fill(mass_csi); //metti la massa
            }
        }
        if(charge>0 && DCACascDaughters<0.1 && DCABachToPrimVtx >0.1 &&  DCAV0Daughters<0.01 && DCAV0ToPrimVtx<1 && DCAPosToPrimVtx <1 && DCANegToPrimVtx <1 && CascCosToPointingAngle > 0.999 && CascDCAtoPVxy <0.2 && CascRadius <10 && V0CosPointingAngle>0.999 &&  V0Radius <20 ){
            hmass_anti_csi->Fill(mass_csi );
        }

    }
     //funzione di fit particelle
     //FIT MASSA  CSI (CSI-)
    TF1* fit_massa_csi2= new TF1("fit_massa_csi2", "gaus(0)+pol3(3)", 1.3, 1.35);
    fit_massa_csi2->SetParameters(15, 1.32171, 0.005, 1,  0, 0, 0);
    fit_massa_csi2->SetParLimits(1, 1.32, 1.322);
    fit_massa_csi2->SetParLimits(0, 8, 20);
    fit_massa_csi2->SetParLimits(2, 0.0015, 0.01);
    //
    //disegniamo gli istogrammi
    c1->cd(1);
    c1->SetGrid();
    //hmass_csi->Fit("fit_massa_csi", "R");
    hmass_csi->Fit("fit_massa_csi2", "R");
    hmass_csi->Draw();
    hmass_csi->SetTitle("massa della csi");
    cout<<"il p-value è: "<<fit_massa_csi2->GetProb()<<endl;
    //
    //FIT MASSA ANTI CSI (CSI+)
    TF1* fit_massa_anti_csi= new TF1("fit_massa_anti_csi", "gaus(0)+pol3(3)", 1.3, 1.35);
    fit_massa_anti_csi->SetParameters(12, 1.32171, 0.004, 1,  0, 0, 0);
    fit_massa_anti_csi->SetParLimits(1, 1.32, 1.322);
    fit_massa_anti_csi->SetParLimits(0, 6, 20);
    fit_massa_anti_csi->SetParLimits(2, 0.002, 0.01);
    c1->cd(2);
    c1->SetGrid();
    hmass_anti_csi->Fit("fit_massa_anti_csi", "R");
    hmass_anti_csi->Draw();
    hmass_anti_csi->SetTitle("massa anti csi");
    cout<<"il p-value è: "<<fit_massa_anti_csi->GetProb()<<endl;
    //
    //
    c1->cd(0);
    c1->Print("fit_masse_molto_fine_tagli.png", "png");
    

    TCanvas* c2= new TCanvas("c2", "grafico momento trasverso", 1000, 800);
    c2->cd();
    Pt->Draw();

    //FUNZIONI DI FIT
    TF1* funz_Pt1= new TF1("funz_Pt1", "1+gaus(0)", 1.3, 1.35);
    funz_Pt1->SetParameters(2, 1.321, 0.005);
    //
     TF1* funz_Pt2= new TF1("funz_Pt2", "1+gaus(0)", 1.3, 1.35);
    funz_Pt2->SetParameters(2, 1.324, 0.005);
    //
    TF1* funz_Pt3= new TF1("funz_Pt3", "1+gaus(0)", 1.3, 1.34);
    funz_Pt3->SetParameters(3, 1.32, 0.005);
    funz_Pt3->SetParLimits(2, 0.001, 0.01);
    funz_Pt3->SetParLimits(1, 1.32, 1.322);
    //
    TF1* funz_Pt4= new TF1("funz_Pt4", "1+gaus(0)", 1.3, 1.345);
    funz_Pt4->SetParameters(7, 1.32, 0.005);
    //
    TF1* funz_Pt5= new TF1("funz_Pt5", "1+gaus(0)", 1.3, 1.345);
    funz_Pt5->SetParameters(7, 1.32, 0.001);
    //
    TF1* funz_Pt6= new TF1("funz_Pt6", "1+gaus(0)", 1.3, 1.335);
    funz_Pt6->SetParameters(2.5, 1.32, 0.0007);
    funz_Pt6->SetParLimits(0, 2, 3);
    funz_Pt6->SetParLimits(2, 0, 0.005);



   // int len_Pt= Pt->GetEntries(); //dà il numero di elementi nell'istogramma Pt

    TCanvas* c11= new TCanvas("c11", "masse invarianti Pt foglio 1", 1000, 800);
    TCanvas* c12= new TCanvas("c12", "masse invarianti Pt foglio 2", 1000, 800);
    TCanvas* c13= new TCanvas("c13", "masse invarianti Pt foglio 3", 1000,800);
    c11->Divide(2,2);
    c12->Divide(2,2);
    c13->Divide(1,2);
    
    c11->cd(0);

    c11->cd(1);
     hmass_Pt1->Fit("funz_Pt1");
    hmass_Pt1->Draw();
    //
    
    c11->cd(2);
     hmass_Pt2->Fit("funz_Pt2");
    hmass_Pt2->Draw();
    //
    
    c11->cd(3);
     hmass_Pt3->Fit("funz_Pt3");
    hmass_Pt3->Draw();
    //
   
   c11->cd(4);
    hmass_Pt4->Fit("funz_Pt4");
    hmass_Pt4->Draw();
    //
   
  c12->cd(1);
   hmass_Pt5->Fit("funz_Pt5");
    hmass_Pt5->Draw();
    //
    
      c12->cd(2);
     hmass_Pt6->Fit("funz_Pt6");
    hmass_Pt6->Draw();
    //
   
      c12->cd(3);
    hmass_Pt7->Draw();
    //
   
      c12->cd(4);
    hmass_Pt8->Draw();
    //
   
    c13->cd(1);
    hmass_Pt9->Draw();
    //
   
    c13->cd(2);
    hmass_Pt10->Draw();






    













    
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
    /*
    TH1F* h_DCACascDaughters= new TH1F("h_DCACascDaughters","h_DCACascDaughters",50, 0, 0.1);
    TH1F* h_DCACascDaughters_fondo= new TH1F("h_DCACascDaughters_fondo","h_DCACascDaughters", 50, 0, 0.1);
    TH1F* h_DCACascDaughters_segnale= new TH1F("h_DCACascDaughters_segnale", "h_DCACascDaughters",50, 0, 0.1);
    h_DCACascDaughters->SetLineColor(4);  // blu l'originale
    h_DCACascDaughters_fondo->SetLineColor(2); //rosso il fondo
    h_DCACascDaughters_segnale->SetLineColor(3); //verde segnale
    //
    TH1F* h_DCABachToPrimVtx= new TH1F("h_DCABachToPrimVtx","h_DCABachToPrimVtx",50, 0.1, 4);
    TH1F* h_DCABachToPrimVtx_fondo= new TH1F("h_DCABachToPrimVtx_fondo","h_DCABachToPrimVtx", 50, 0.1, 4);
    TH1F* h_DCABachToPrimVtx_segnale= new TH1F("h_DCABachToPrimVtx_segnale","h_DCABachToPrimVtx", 50, 0.1, 4);
    h_DCABachToPrimVtx->SetLineColor(4);  // fucsia l'originale
    h_DCABachToPrimVtx_fondo->SetLineColor(2); //rosso il fondo
    h_DCABachToPrimVtx_segnale->SetLineColor(3); //verde segnale
    //
    TH1F* h_DCAV0Daughters= new TH1F("h_DCAV0Daughters","h_DCAV0Daughters",50, 0, 0.01);
    TH1F* h_DCAV0Daughters_fondo= new TH1F("h_DCAV0Daughters_fondo","h_DCAV0Daughters", 50, 0, 0.01);
    TH1F* h_DCAV0Daughters_segnale= new TH1F("h_DCAV0Daughters_segnale", "h_DCAV0Daughters",50, 0, 0.01);
    h_DCAV0Daughters->SetLineColor(4);  // fucsia l'originale
    h_DCAV0Daughters_fondo->SetLineColor(2); //rosso il fondo
    h_DCAV0Daughters_segnale->SetLineColor(3); //verde segnale
    //
    TH1F* h_DCAV0ToPrimVtx= new TH1F("h_DCAV0ToPrimVtx","h_DCAV0ToPrimVtx",50, 0, 1);
    TH1F* h_DCAV0ToPrimVtx_fondo= new TH1F("h_DCAV0ToPrimVtx_fondo","h_DCAV0ToPrimVtx", 50, 0, 1);
    TH1F* h_DCAV0ToPrimVtx_segnale= new TH1F("h_DCAV0ToPrimVtx_segnale","h_DCAV0ToPrimVtx", 50, 0, 1);
    h_DCAV0ToPrimVtx->SetLineColor(4);  // fucsia l'originale
    h_DCAV0ToPrimVtx_fondo->SetLineColor(2); //rosso il fondo
    h_DCAV0ToPrimVtx_segnale->SetLineColor(3); //verde segnale
    //
    TH1F* h_DCAPosToPrimVtx= new TH1F("h_DCAPosToPrimVtx","h_DCAPosToPrimVtx",50, 0, 1);
    TH1F* h_DCAPosToPrimVtx_fondo= new TH1F("h_DCAPosToPrimVtx_fondo","h_DCAPosToPrimVtx", 50, 0, 1);
    TH1F* h_DCAPosToPrimVtx_segnale= new TH1F("h_DCAPosToPrimVtx_segnale","h_DCAPosToPrimVtx", 50, 0, 1);
    h_DCAPosToPrimVtx->SetLineColor(4);  // fucsia l'originale
    h_DCAPosToPrimVtx_fondo->SetLineColor(2); //rosso il fondo
    h_DCAPosToPrimVtx_segnale->SetLineColor(3); //verde segnale
    //
    TH1F* h_DCANegToPrimVtx= new TH1F("h_DCANegToPrimVtx","h_DCANegToPrimVtx",50, 0, 1);
    TH1F* h_DCANegToPrimVtx_fondo= new TH1F("h_DCANegToPrimVtx_fondo","h_DCANegToPrimVtx", 50, 0, 1);
    TH1F* h_DCANegToPrimVtx_segnale= new TH1F("h_DCANegToPrimVtx_segnale","h_DCANegToPrimVtx", 50, 0, 1);
    h_DCANegToPrimVtx->SetLineColor(4);  // fucsia l'originale
    h_DCANegToPrimVtx_fondo->SetLineColor(2); //rosso il fondo
    h_DCANegToPrimVtx_segnale->SetLineColor(3); //verde segnale
    //
    TH1F* h_CascCosToPointingAngle= new TH1F("h_CascCosToPointingAngle","h_CascCosToPointingAngle",50, 0.999, 1.0002);
    TH1F* h_CascCosToPointingAngle_fondo= new TH1F("h_CascCosToPointingAngle_fondo","h_CascCosToPointingAngle", 50, 0.999, 1.0002);
    TH1F* h_CascCosToPointingAngle_segnale= new TH1F("h_CascCosToPointingAngle_segnale","h_CascCosToPointingAngle", 50, 0.999, 1.0002);
    h_CascCosToPointingAngle->SetLineColor(4);  // fucsia l'originale
    h_CascCosToPointingAngle_fondo->SetLineColor(2); //rosso il fondo
    h_CascCosToPointingAngle_segnale->SetLineColor(3); //verde segnale
    //
    TH1F* h_CascDCAtoPVxy= new TH1F("h_CascDCAtoPVxy","h_CascDCAtoPVxy",50, 0, 0.2);
    TH1F* h_CascDCAtoPVxy_fondo= new TH1F("h_CascDCAtoPVxy_fondo","h_CascDCAtoPVxy", 50, 0, 0.2);
    TH1F* h_CascDCAtoPVxy_segnale= new TH1F("h_CascDCAtoPVxy_segnale","h_CascDCAtoPVxy", 50, 0, 0.2);
    h_CascDCAtoPVxy->SetLineColor(4);  // fucsia l'originale
    h_CascDCAtoPVxy_fondo->SetLineColor(2); //rosso il fondo
    h_CascDCAtoPVxy_segnale->SetLineColor(3); //verde segnale
    //
    TH1F* h_CascRadius= new TH1F("h_CascRadius","h_CascRadius",50, 0, 10);
    TH1F* h_CascRadius_fondo= new TH1F("h_CascRadius_fondo","h_CascRadius", 50, 0, 10);
    TH1F* h_CascRadius_segnale= new TH1F("h_CascRadius_segnale","h_CascRadius", 50, 0, 10);
    h_CascRadius->SetLineColor(4);  // fucsia l'originale
    h_CascRadius_fondo->SetLineColor(2); //rosso il fondo
    h_CascRadius_segnale->SetLineColor(3); //verde segnale
    //
    TH1F* h_V0CosPointingAngle= new TH1F("h_V0CosPointingAngle","h_V0CosPointingAngle",50, 0.999, 1.0001);
    TH1F* h_V0CosPointingAngle_fondo= new TH1F("h_V0CosPointingAngle_fondo", "h_V0CosPointingAngle",50, 0.999,1.0001);
    TH1F* h_V0CosPointingAngle_segnale= new TH1F("h_V0CosPointingAngle_segnale","h_V0CosPointingAngle", 50, 0.999, 1.0001);
    h_V0CosPointingAngle->SetLineColor(4);  // fucsia l'originale
    h_V0CosPointingAngle_fondo->SetLineColor(2); //rosso il fondo
    h_V0CosPointingAngle_segnale->SetLineColor(3); //verde segnale
    //
    TH1F* h_V0Radius= new TH1F("h_V0Radius","h_V0Radius",50, 0, 20);
    TH1F* h_V0Radius_fondo= new TH1F("h_V0Radius_fondo", "h_V0Radius",50, 0, 20);
    TH1F* h_V0Radius_segnale= new TH1F("h_V0Radius_segnale","h_V0Radius", 50, 0, 20);
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
        if(charge<=0 && DCACascDaughters<0.1 && DCABachToPrimVtx >0.1 &&  DCAV0Daughters<0.01 && DCAV0ToPrimVtx<1 && DCAPosToPrimVtx <1 && DCANegToPrimVtx <1 && CascCosToPointingAngle > 0.999 && CascDCAtoPVxy <0.2 && CascRadius <10 && V0CosPointingAngle>0.999 &&  V0Radius <20 ){//piglio solo le anti csi che hanno carica maggiore di 0
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
   
    h_DCACascDaughters->DrawNormalized("HIST ");
    h_DCACascDaughters->SetTitle("h_DCACascDaughters");

    h_DCACascDaughters_fondo->DrawNormalized("HIST SAME"); //rosso il fondo
   
    h_DCACascDaughters_segnale->DrawNormalized("HIST SAME ");
    
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
    c1->Write("csi FIT MASSE INVARIANTI con tagli veri");
    c2->Write("csi foglio 2 con tagli veri");
    c3->Write("csi foglio 3 veri");
    c4->Write("csi foglio 4 con tagli veri");
    output->Close();
    */
    

}