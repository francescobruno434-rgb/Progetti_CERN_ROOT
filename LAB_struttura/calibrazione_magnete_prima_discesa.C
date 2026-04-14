#include<iostream>
#include "TGraphErrors.h"
#include "TCanvas.h"
#include<vector>
#include "TF1.h"

using namespace std;



void calibrazione_magnete_prima_discesa(){
    vector<double> corrente={
        0,
        9.93,
        8.96,
        8.11,
        7.27,
        6.33,
        5.44,
        4.6,
        3.59,
        2.7,
        1.72,
        0.94,
    };
    vector<double> B={
        8.8,
        565.8,
        529.7,
        487.9,
        441,
        394.8,
        343.6,
        293.4,
        232.2,
        180.5,
        119.5,
        70.8,
    };
    //
    //errori
    vector<double> err_corrente={
        0.000001,
        0.24825,
        0.224,
        0.20275,
        0.18175,
        0.15825,
        0.136,
        0.115,
        0.08975,
        0.0675,
        0.043,
        0.0235,
    };
    vector<double> err_B={
        0.54,
        29.29,
        27.485,
        25.395,
        23.05,
        20.74,
        18.18,
        14.77,
        11.71,
        9.125,
        6.075,
        3.64,
            };

    //
    int len= corrente.size();
    TGraphErrors* gr1= new TGraphErrors(len, corrente.data(), B.data(), err_corrente.data(), err_B.data());
    //
    TCanvas* c1= new TCanvas("c1", "rampe calibrazione", 800, 600);

    TF1* fit= new TF1("fit", "[0]+[1]*x", 0, 10);


    gr1->SetMarkerStyle(20);
   gr1->Fit("fit", "R");
    gr1->SetMinimum(-10);
    gr1->Draw("AP.");
    c1->Print("prima_discesa.png", "png");
    cout<<"il pvalue è "<< fit->GetProb() <<endl;



}