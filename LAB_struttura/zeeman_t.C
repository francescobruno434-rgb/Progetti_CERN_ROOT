#include <iostream>
#include <TGraphErrors.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TH1.h>
#include <iomanip>
#include <TFitResultPtr.h>
#include <TFitResult.h>
#include <TLegend.h>
#include <cmath>


using namespace std;


void zeeman_t(){


const int n=6;


double B[n]={
   9.6894850486,
    162.813355,
    251.685283,
    353.167417,
    451.647121,
    608.974453,};
double D[n]={0, -0.0649516698204875,
        -0.120095195597203,
        -0.169710208800403,
        -0.198121498988744,
        -0.269541998299811,
    };
double err_B[n]={
    7.78612894279188,
    24.3664931038138,
    36.7416786489251,
    51.13525679175,
    65.2025763749299,
    87.7611078087855,};
double err_D[n]={0,
0.0106708507425432,
0.00493935999674321,
0.00421104875145609,
0.0127591476546393,
0.0146494199870778,};
TCanvas *c1 = new TCanvas("c1", "verifica linearità", 800, 600);
    c1->SetGrid();




TGraphErrors *grafico = new TGraphErrors(n, B, D, err_B, err_D);
    grafico->SetMarkerStyle(20);
    grafico->SetMarkerSize(0.8);
    grafico->SetMarkerColor(kBlack);
    grafico->SetLineColor(kBlack);
    grafico->Draw("AP");
    grafico->SetTitle("<#delta>/<#Delta> vs B configurazione longitudinale");
    grafico->GetXaxis()->SetTitle("B [mT]");
    grafico->GetYaxis()->SetTitle("<#delta>/<#Delta>");




TF1 *fit1= new TF1("fit1", "[0]*x+[1]", -1, 650);
    fit1->SetParLimits(0, -1, 0);
    fit1->SetLineColor(8);
    fit1->SetParameters(-0.003, 0);
    grafico->Fit(fit1, "SR+");
   
     TFitResultPtr r = grafico->Fit(fit1, "S R Q");


    // CALCOLO E STAMPA DEL COEFFICIENTE DI CORRELAZIONE LINEARE(r)
    double R = grafico->GetCorrelationFactor();  


     cout<<"il p-value è :"<<endl;
    cout<<fit1->GetProb()<<endl;


grafico->Draw("AP");
fit1->Draw("same");
c1->Print("zeeman_l.png", "png");

}

