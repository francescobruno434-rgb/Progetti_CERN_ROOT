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


void zeeman_tr(){


const int n=6;


double B[n]={
        11.35567,
    308.49567,
    369.11223,
    430.32307,
    486.77967,
    547.39623,
};
double D[n]={
    0,
    -0.140672299088437,
    -0.171186258722491,
    -0.199802167592311,
    -0.224054328784307,
    -0.243464059255216,
    };
double err_B[n]={
   7.747,
    47.5296251809486,
    56.8687591031799,
    66.2994531619037,
    74.9976661286878,
    84.3368000509191,
};
double err_D[n]={
        0,
    0.0271805727632622,
    0.0311826884803246,
    0.051189494068092,
    0.0405037693045907,
    0.0405037693045907,
};
TCanvas *c1 = new TCanvas("c1", "verifica linearità", 800, 600);
    c1->SetGrid();




TGraphErrors *grafico = new TGraphErrors(n, B, D, err_B, err_D);
    grafico->SetMarkerStyle(20);
    grafico->SetMarkerSize(0.8);
    grafico->SetMarkerColor(kBlack);
    grafico->SetLineColor(kBlack);
    grafico->Draw("AP");
    grafico->SetTitle("<#delta>/<#Delta> vs B configurazione trasversale");
    grafico->GetXaxis()->SetTitle("B [mT]");
    grafico->GetYaxis()->SetTitle("<#delta>/<#Delta>");




TF1 *fit1= new TF1("fit1", "[0]*x+[1]", -1, 650);
    //fit1->SetParLimits(0, -1, 0);
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

