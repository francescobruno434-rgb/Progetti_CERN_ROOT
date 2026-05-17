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
    TFitResultPtr rPt1= hmass_Pt1->Fit("funz_Pt1", "S");
    hmass_Pt1->Draw();
    TMatrixDSym cov_Pt1= rPt1->GetCovarianceMatrix();
    double* array_cov_Pt1_b= cov_Pt1.GetSub(0, 2, 0, 2 ).GetMatrixArray();
    vector<double> array_cov_Pt1={};
    for(int i=0; i<9; i++){
        array_cov_Pt1.push_back(array_cov_Pt1_b[i]);
    }
    //
    
    c11->cd(2);
      TFitResultPtr rPt2= hmass_Pt2->Fit("funz_Pt2", "S");
    hmass_Pt2->Draw();
    TMatrixDSym cov_Pt2= rPt2->GetCovarianceMatrix();
    double* array_cov_Pt2_b= cov_Pt2.GetSub(0, 2, 0, 2 ).GetMatrixArray();
     vector<double> array_cov_Pt2={};
    for(int i=0; i<9; i++){
        array_cov_Pt2.push_back(array_cov_Pt2_b[i]);
    }
    //
    
    c11->cd(3);
    TFitResultPtr rPt3= hmass_Pt3->Fit("funz_Pt3", "S");
    hmass_Pt3->Draw();
    TMatrixDSym cov_Pt3= rPt3->GetCovarianceMatrix();
    double* array_cov_Pt3_b= cov_Pt3.GetSub(0, 2, 0, 2 ).GetMatrixArray();
     vector<double> array_cov_Pt3={};
    for(int i=0; i<9; i++){
        array_cov_Pt3.push_back(array_cov_Pt3_b[i]);
    }
    //
   
   c11->cd(4);
      TFitResultPtr rPt4= hmass_Pt4->Fit("funz_Pt4", "S");
    hmass_Pt4->Draw();
    TMatrixDSym cov_Pt4= rPt4->GetCovarianceMatrix();
    double* array_cov_Pt4_b= cov_Pt4.GetSub(0, 2, 0, 2 ).GetMatrixArray();
     vector<double> array_cov_Pt4={};
    for(int i=0; i<9; i++){
        array_cov_Pt4.push_back(array_cov_Pt4_b[i]);
    }
    //
   
  c12->cd(1);
   TFitResultPtr rPt5= hmass_Pt5->Fit("funz_Pt5", "S");
    hmass_Pt5->Draw();
    TMatrixDSym cov_Pt5= rPt5->GetCovarianceMatrix();
    double* array_cov_Pt5_b= cov_Pt5.GetSub(0, 2, 0, 2 ).GetMatrixArray();
     vector<double> array_cov_Pt5={};
    for(int i=0; i<9; i++){
        array_cov_Pt5.push_back(array_cov_Pt5_b[i]);
    }
    //
    
      c12->cd(2);
      TFitResultPtr rPt6= hmass_Pt6->Fit("funz_Pt6", "S");
    hmass_Pt6->Draw();
    TMatrixDSym cov_Pt6= rPt6->GetCovarianceMatrix();
    double* array_cov_Pt6_b= cov_Pt6.GetSub(0, 2, 0, 2 ).GetMatrixArray();
     vector<double> array_cov_Pt6={};
    for(int i=0; i<9; i++){
        array_cov_Pt6.push_back(array_cov_Pt6_b[i]);
    }
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
TF1* gaus_Pt1= new TF1("gaus_Pt1", "gaus(0)",mu_Pt1-3*sigma_Pt1, mu_Pt1+3*sigma_Pt1);
gaus_Pt1->FixParameter(0, A_Pt1);
gaus_Pt1->FixParameter(1, mu_Pt1);
gaus_Pt1->FixParameter(2, sigma_Pt1);
//
TF1* gaus_Pt2= new TF1("gaus_Pt2", "gaus(0)", mu_Pt2-3*sigma_Pt2, mu_Pt2+3*sigma_Pt2);
gaus_Pt2->FixParameter(0, A_Pt2);
gaus_Pt2->FixParameter(1, mu_Pt2);
gaus_Pt2->FixParameter(2, sigma_Pt2);
//
TF1* gaus_Pt3= new TF1("gaus_Pt3", "gaus(0)", mu_Pt3-3*sigma_Pt3, mu_Pt3+3*sigma_Pt3);
gaus_Pt3->FixParameter(0, A_Pt3);
gaus_Pt3->FixParameter(1, mu_Pt3);
gaus_Pt3->FixParameter(2, sigma_Pt3);
//
TF1* gaus_Pt4= new TF1("gaus_Pt4", "gaus(0)", mu_Pt4-3*sigma_Pt4, mu_Pt4+3*sigma_Pt4);
gaus_Pt4->FixParameter(0, A_Pt4);
gaus_Pt4->FixParameter(1, mu_Pt4);
gaus_Pt4->FixParameter(2, sigma_Pt4);
//
TF1* gaus_Pt5= new TF1("gaus_Pt5", "gaus(0)", mu_Pt5-3*sigma_Pt5, mu_Pt5+3*sigma_Pt5);
gaus_Pt5->FixParameter(0, A_Pt5);
gaus_Pt5->FixParameter(1, mu_Pt5);
gaus_Pt5->FixParameter(2, sigma_Pt5);
//
TF1* gaus_Pt6= new TF1("gaus_Pt6", "gaus(0)", mu_Pt6-3*sigma_Pt6, mu_Pt6+3*sigma_Pt6);
gaus_Pt6->FixParameter(0, A_Pt6);
gaus_Pt6->FixParameter(1, mu_Pt6);
gaus_Pt6->FixParameter(2, sigma_Pt6);
//
//
//calcolliamo i risultati dei vari integrali, da dividere per 0.5 vale a dire l'ampiezza dei bin di Pt; SE IL VALORE CAMBIA E' DA MODIFICARE MANUALMENTE!!!!!!!!!!
//INTEGRALI IN 3 SIGMA (ORA SON TROPPO PICCOLE E  ADDIRITTURA ADDIRITTURA NEGATIVE, GLI INTEGRALI VENGONO INSENSATI)

double integrale_Pt1= gaus_Pt1->Integral(mu_Pt1-3*sigma_Pt1, mu_Pt1+3*sigma_Pt1)/0.5;
double integrale_Pt2= gaus_Pt2->Integral(mu_Pt2-3*sigma_Pt2, mu_Pt2+3*sigma_Pt2)/0.5;
double integrale_Pt3= gaus_Pt3->Integral(mu_Pt3-3*sigma_Pt3, mu_Pt3+3*sigma_Pt3)/0.5;
double integrale_Pt4= gaus_Pt4->Integral(mu_Pt4-3*sigma_Pt4, mu_Pt4+3*sigma_Pt4)/0.5;
double integrale_Pt5= gaus_Pt5->Integral(mu_Pt5-3*sigma_Pt5, mu_Pt5+3*sigma_Pt5)/0.5;
double integrale_Pt6= gaus_Pt6->Integral(mu_Pt6-3*sigma_Pt6, mu_Pt6+3*sigma_Pt6)/0.5;


//ERRORI SUGLI INTEGRALI
double err_integrale_Pt1= gaus_Pt1->IntegralError(mu_Pt1-3*sigma_Pt1, mu_Pt1+3*sigma_Pt1, nullptr, array_cov_Pt1.data())/0.5;
double err_integrale_Pt2= gaus_Pt2->IntegralError(mu_Pt2-3*sigma_Pt2, mu_Pt2+3*sigma_Pt2, nullptr, array_cov_Pt2.data())/0.5;
double err_integrale_Pt3= gaus_Pt3->IntegralError(mu_Pt3-3*sigma_Pt3, mu_Pt3+3*sigma_Pt3, nullptr, array_cov_Pt3.data())/0.5;
double err_integrale_Pt4= gaus_Pt4->IntegralError(mu_Pt4-3*sigma_Pt4, mu_Pt4+3*sigma_Pt4, nullptr, array_cov_Pt4.data())/0.5;
double err_integrale_Pt5= gaus_Pt5->IntegralError(mu_Pt5-3*sigma_Pt5, mu_Pt5+3*sigma_Pt5, nullptr, array_cov_Pt5.data())/0.5;
double err_integrale_Pt6= gaus_Pt6->IntegralError(mu_Pt6-3*sigma_Pt6, mu_Pt6+3*sigma_Pt6, nullptr, array_cov_Pt6.data())/0.5;

//
//
//GRAFICO SPETTRO IN PT per convenzione si associa come valore quello centrale di ogni bin.
//ATTENTO! MODIFICA SE NECESSARIO IL NUMERO DI DATI DA INSERIRE 
cout<<"l'errore su Pt1 è "<< err_integrale_Pt1<<endl;
cout<<"matrice di covarianza"<<endl;
for (int i=0; i<9;i++){
    cout<<array_cov_Pt1[i]<< " ";
}
cout<<" "<<endl;
//
cout<<"matrice di covarianza"<<endl;
for (int i=0; i<9;i++){
   cout<<array_cov_Pt2[i]<< " ";
}
cout<<" "<<endl;
//
cout<<"matrice di covarianza"<<endl;
for (int i=0; i<9;i++){
     cout<<array_cov_Pt3[i]<< " ";
}
cout<<" "<<endl;
//
cout<<"matrice di covarianza"<<endl;
for (int i=0; i<9;i++){
   cout<<array_cov_Pt4[i]<< " ";
}
cout<<" "<<endl;
//
cout<<"matrice di covarianza"<<endl;
for (int i=0; i<9;i++){
    cout<<array_cov_Pt5[i]<< " ";
}
cout<<" "<<endl;
//
cout<<"matrice di covarianza"<<endl;
for (int i=0; i<9;i++){
    cout<<array_cov_Pt6[i]<< " ";
}
cout<<" "<<endl;





//GRAFICO SPETTRO IN PT per convenzione si associa come valore quello centrale di ogni bin.
//ATTENTO! MODIFICA SE NECESSARIO IL NUMERO DI DATI DA INSERIRE 
vector<double> Pt_x= {0.25, 0.75, 1.25, 1.75, 2.25, 2.75};
vector<double> Pt_y={integrale_Pt1, integrale_Pt2, integrale_Pt3, integrale_Pt4, integrale_Pt5, integrale_Pt6};
vector<double> err_Pt_y={err_integrale_Pt1, err_integrale_Pt2,err_integrale_Pt3,err_integrale_Pt4,err_integrale_Pt5, err_integrale_Pt6};
int size= Pt_x.size();
TGraphErrors* spettro_Pt= new TGraphErrors(size, Pt_x.data(), Pt_y.data(), nullptr, err_Pt_y.data());

TCanvas* c21= new TCanvas("c21", "spettro in Pt", 800, 600);
c21->cd();
spettro_Pt->Draw("AP.");
spettro_Pt->SetMarkerStyle(20);




//######PARTE NUOVA (ERRORI INTEGRALE) 16/05/2026###########################################
//l'errore sull'integral viene calcolato nelle righe precedenti con il metodo della matrice di covarianza
//qui noi lo calcoliamo con il metodo dell'errore relativo
//
//integro tutto l'istogramma in un interno di mu+-3 sigma 
//
double hist_Pt1_integral= hmass_Pt1->Integral(mu_Pt1-3*sigma_Pt1, mu_Pt1+ 3* sigma_Pt1) ;
double hist_Pt2_integral= hmass_Pt2->Integral(mu_Pt2-3*sigma_Pt2, mu_Pt2+ 3* sigma_Pt2) ;
double hist_Pt3_integral= hmass_Pt3->Integral(mu_Pt3-3*sigma_Pt3, mu_Pt3+ 3* sigma_Pt3) ;
double hist_Pt4_integral= hmass_Pt4->Integral(mu_Pt4-3*sigma_Pt4, mu_Pt4+ 3* sigma_Pt4) ;
double hist_Pt5_integral= hmass_Pt5->Integral(mu_Pt5-3*sigma_Pt5, mu_Pt5+ 3* sigma_Pt5) ;
double hist_Pt6_integral= hmass_Pt6->Integral(mu_Pt6-3*sigma_Pt6, mu_Pt6+ 3* sigma_Pt6) ;
cout<<"hist_Pt1_integral "<< hist_Pt1_integral<<endl;
//
//qui si calcola l'errore relativo
double err_rel_integral_Pt1= pow(hist_Pt1_integral, 0.5)/hist_Pt1_integral; 
double err_rel_integral_Pt2= pow(hist_Pt2_integral, 0.5)/hist_Pt2_integral;
double err_rel_integral_Pt3= pow(hist_Pt3_integral, 0.5)/hist_Pt3_integral;
double err_rel_integral_Pt4= pow(hist_Pt4_integral, 0.5)/hist_Pt4_integral;
double err_rel_integral_Pt5= pow(hist_Pt5_integral, 0.5)/hist_Pt5_integral;
double err_rel_integral_Pt6= pow(hist_Pt6_integral, 0.5)/hist_Pt6_integral;
cout<<"err_rel_integrale_Pt1 "<<err_rel_integral_Pt1<<endl;
//
//qui si trova l'errore assoluto sugli integrali delle gaussiane
double err_ass_integrale_Pt1= err_rel_integral_Pt1*integrale_Pt1;
double err_ass_integrale_Pt2= err_rel_integral_Pt2*integrale_Pt2;
double err_ass_integrale_Pt3= err_rel_integral_Pt3*integrale_Pt3;
double err_ass_integrale_Pt4= err_rel_integral_Pt4*integrale_Pt4;
double err_ass_integrale_Pt5= err_rel_integral_Pt5*integrale_Pt5;
double err_ass_integrale_Pt6= err_rel_integral_Pt6*integrale_Pt6;
//
//qui adesso rifacciamo i grafici con errori nuovi
vector<double> err_Pt_y_2={err_ass_integrale_Pt1, err_ass_integrale_Pt2, err_ass_integrale_Pt3, err_ass_integrale_Pt4, err_ass_integrale_Pt5, err_ass_integrale_Pt6};



//paragoniamo i due tipi di errori
cout<<"###############################################################################"<<endl;
cout<<"PARAGONE TRA GLI ERRORI OTTENUTI NEI 2 CASI \n"<< endl;
cout<<"Errori con martrice di covarianza: "<<endl;
for(vector<double>::const_iterator it= err_Pt_y.begin(); it != err_Pt_y.end(); it++){
    cout<< *it<< " ";
}
cout<<" "<<endl;
//
cout<<"Errori senza martrice di covarianza (errori relativi): "<<endl;
for(vector<double>::const_iterator it= err_Pt_y_2.begin(); it != err_Pt_y_2.end(); it++){
    cout<< *it<< " ";
}
cout<<" "<<endl;
//
//facciamo un secondo grafico usando nuovi errori
TCanvas* c22= new TCanvas("c22", "grafico con errori senza matrice di covarianza", 800, 600);
TGraphErrors* spettro_Pt_err2= new TGraphErrors(size, Pt_x.data(), Pt_y.data(), nullptr, err_Pt_y_2.data() );
c22->cd();
spettro_Pt_err2->Draw("AP.");
spettro_Pt_err2->SetMarkerStyle(21);

}




    


