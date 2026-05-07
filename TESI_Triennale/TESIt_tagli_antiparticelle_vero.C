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




void TESIt_tagli_antiparticelle_vero(){
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
    TH1F* hmass_Pt1= new TH1F("hmass_Pt1", "Pt1", 25,  1.3, 1.35 );
    TH1F* hmass_Pt2= new TH1F("hmass_Pt2", "Pt2", 30,  1.3, 1.35 );
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
        if(charge<=0 && DCACascDaughters<0.1  &&  DCAV0Daughters<0.2 && DCAV0ToPrimVtx<1 && DCAPosToPrimVtx <1 && DCANegToPrimVtx <1 && CascCosToPointingAngle > 0.97 && CascDCAtoPVxy <0.2 && CascRadius <10 && V0CosPointingAngle>0.99 &&  V0Radius <20){
            hmass_csi->Fill(mass_csi);
           
        }
        if(charge>0 && DCACascDaughters<0.1  &&  DCAV0Daughters<0.2 && DCAV0ToPrimVtx<1 && DCAPosToPrimVtx <1 && DCANegToPrimVtx <1 && CascCosToPointingAngle > 0.97 && CascDCAtoPVxy <0.2 && CascRadius <10 && V0CosPointingAngle>0.99 &&  V0Radius <20 ){
            hmass_anti_csi->Fill(mass_csi );
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
    //
    //GRAFICO MOMENTO TRASVERSO
    TCanvas* c2= new TCanvas("c2", "grafico momento trasverso", 1000, 800);
    c2->cd();
    Pt->Draw();

    //FUNZIONI DI FIT
    TF1* funz_Pt1= new TF1("funz_Pt1", "1+gaus(0)", 1.3, 1.35);
    funz_Pt1->SetParameters(2, 1.321, 0.005);
    //
     TF1* funz_Pt2= new TF1("funz_Pt2", "1+gaus(0)", 1.3, 1.35);
    funz_Pt2->SetParameters(3, 1.32, 0.005);
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

    TCanvas* c11= new TCanvas("c11", "masse invarianti antiparticelle Pt foglio 1", 1000, 800);
    TCanvas* c12= new TCanvas("c12", "masse invarianti antiparticelle Pt foglio 2", 1000, 800);
    TCanvas* c13= new TCanvas("c13", "masse invarianti atniparticelle Pt foglio 3", 1000,800);
    c11->Divide(2,2);
    c12->Divide(2,2);
    c13->Divide(1,2);
    
    c11->cd(0);

    c11->cd(1);
    // hmass_Pt1->Fit("funz_Pt1");
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

    c1->Print("spettro_massa_con_tagli_veri.png", "png");
    c11->Print("spettro_antimass_Pt1.png", "png");
    c12->Print("spettro_antimass_Pt2.png", "png");
    c13->Print("spettro_antimass_Pt3.png", "png");


    //###PARTE NUOVA (6 MAGGIO 2026) ###################################################
    //Per ogni fit di Pt, prendiamo i parametri della Gaussiana su cui vogliamo integrale

    double A_Pt1= funz_Pt1->GetParameter(0);
    double mu_Pt1=funz_Pt1->GetParameter(1);
    double sigma_Pt1= funz_Pt1->GetParameter(2);
    //
     double A_Pt2= funz_Pt2->GetParameter(0);
    double mu_Pt2=funz_Pt2->GetParameter(1);
    double sigma_Pt2= funz_Pt2->GetParameter(2);
    //
     double A_Pt3= funz_Pt3->GetParameter(0);
    double mu_Pt3=funz_Pt3->GetParameter(1);
    double sigma_Pt3= funz_Pt3->GetParameter(2);
    //
     double A_Pt4= funz_Pt4->GetParameter(0);
    double mu_Pt4=funz_Pt4->GetParameter(1);
    double sigma_Pt4= funz_Pt4->GetParameter(2);
    //
     double A_Pt5= funz_Pt5->GetParameter(0);
    double mu_Pt5=funz_Pt5->GetParameter(1);
    double sigma_Pt5= funz_Pt5->GetParameter(2);
//
     double A_Pt6= funz_Pt6->GetParameter(0);
    double mu_Pt6=funz_Pt6->GetParameter(1);
    double sigma_Pt6= funz_Pt6->GetParameter(2);
//
//scriviamo le varie funzioni gaussiane per i segnali dei vari Pt
TF1* gaus_Pt1= new TF1("gaus_Pt1", "gaus(0)", -10e4, 10e4);
gaus_Pt1->FixParameter(0, A_Pt1);
gaus_Pt1->FixParameter(1, mu_Pt1);
gaus_Pt1->FixParameter(2, sigma_Pt1);
//
TF1* gaus_Pt2= new TF1("gaus_Pt2", "gaus(0)", -10e4, 10e4);
gaus_Pt2->FixParameter(0, A_Pt2);
gaus_Pt2->FixParameter(1, mu_Pt2);
gaus_Pt2->FixParameter(2, sigma_Pt2);
//
TF1* gaus_Pt3= new TF1("gaus_Pt3", "gaus(0)", -10e4, 10e4);
gaus_Pt3->FixParameter(0, A_Pt3);
gaus_Pt3->FixParameter(1, mu_Pt3);
gaus_Pt3->FixParameter(2, sigma_Pt3);
//
TF1* gaus_Pt4= new TF1("gaus_Pt4", "gaus(0)", -10e4, 10e4);
gaus_Pt4->FixParameter(0, A_Pt4);
gaus_Pt4->FixParameter(1, mu_Pt4);
gaus_Pt4->FixParameter(2, sigma_Pt4);
//
TF1* gaus_Pt5= new TF1("gaus_Pt5", "gaus(0)", -10e4, 10e4);
gaus_Pt5->FixParameter(0, A_Pt5);
gaus_Pt5->FixParameter(1, mu_Pt5);
gaus_Pt5->FixParameter(2, sigma_Pt5);
//
TF1* gaus_Pt6= new TF1("gaus_Pt6", "gaus(0)", -10e4, 10e4);
gaus_Pt6->FixParameter(0, A_Pt6);
gaus_Pt6->FixParameter(1, mu_Pt6);
gaus_Pt6->FixParameter(2, sigma_Pt6);
//
//
//calcolliamo i risultati dei vari integrali, da dividere per 0.5 vale a dire l'ampiezza dei bin di Pt; SE IL VALORE CAMBIA E' DA MODIFICARE MANUALMENTE!!!!!!!!!!




    


}