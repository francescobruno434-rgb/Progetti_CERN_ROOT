#include <iostream>
#include <TGraphErrors.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TMath.h>

using namespace std;

void LAB_nucl_dipendenza_angolare() {
   
    double rate[6] = {
        0.454353280857938,
        0.421942897608395,
        0.292059188456413,
        0.1774832926979,
        0.0996640537513998,
        0.0180351563330287,};
    double theta[6] = {
        0,
        15,
        30,
        45,
        60,
        75,};
    double err_rate[6] = {
        0.0341811784486474,
        0.0323546262014378,
        0.0248500640973371,
        0.0192820847670264,
        0.0189839890140317,
        0.0132063200447791,};
    double err_theta[6] = {1, 1, 1, 1, 1, 1};

    double conteggi[6]={
        301,
        300,
        300,
        254,
        105,
        50
    };
    double err_conteggi[6]={
        17.3493515728975,
        17.3205080756888,
        17.3205080756888,
        15.9373774505092,
        10.2469507659596,
        7.07106781186548,
    }; 

    double tempo[6]={619,
        661,
        926,
        1213,
        798,
        1001,};
    double err_tempo[6]={
        1,
        1,
        1,
        1,
        1,
        1,
    };

    TCanvas *c1 = new TCanvas("c1", "Grafico Dipendenza Angolare", 800, 600);
    c1->SetGrid();

    // 1. Crea e disegna il grafico vuoto con assi e punti
    TGraphErrors *grafico = new TGraphErrors(6, theta, rate, err_theta, err_rate);
    grafico->SetTitle("Rate vs Angolo; Angolo [gradi]; Rate [Hz]");
    grafico->SetMarkerStyle(20);
   // AP = Assi, Punti

    // 2. Definisci la funzione 
    TF1 *fit1 = new TF1("fit1", "[0]*pow(cos(x*TMath::Pi()/180), [1])", 0, 90);
    fit1->SetParameters(0.45, 2.0);
   //fit1->SetParLimits(1, 2, 2.1);
    fit1->SetLineColor(kGreen);
    fit1->SetLineWidth(2);

    // 3. Esegui il fit
    grafico->Fit(fit1, "R"); 
 
    
    grafico->Draw("AP");

    // Risultati 
   /*cout << "\n--- RISULTATI FIT ---" << endl;
    cout << "Chi2/ndf = " << fit1->GetChisquare() << " / " << fit1->GetNDF() << endl;
    cout << "Ro = " << fit1->GetParameter(0) << " ± " << fit1->GetParError(0) << endl;
    cout << "n = " << fit1->GetParameter(1) << " ± " << fit1->GetParError(1) << endl;*/
    cout<<"Il p value è:"<<endl;
    cout<<fit1->GetProb()<<endl;
        cout<<"il cosendo di 90 gradi è"<<cos(180*TMath::Pi()/180)<<endl;
    //c1->Update();

    for( int i=0; i<6; i++){
        //theta, conteggi, tempo, rate
        cout<<"$ ( "<< theta[i]<< " \\pm "<<err_theta[i]<< ") $ & $ ( "<< conteggi[i]<<" \\pm "<<err_conteggi[i]<< ") $ & $ ( "<<tempo[i]<< " \\pm "<< err_tempo[i]<< ") $ & $ ( "<< rate[i]<< " \\pm "<<err_rate[i]<< " ) $ \\\\ \\hline"<<endl;
    }



}