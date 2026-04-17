 #include<iostream>
#include "TGraphErrors.h"
#include "TCanvas.h"
#include<vector>
#include "TF1.h"

using namespace std;

//PRIMA SALITA

void calibrazione_magnete(){
    vector<double> corrente={
        0,
        0.91,
        1.85,
        2.8,
        3.63,
        4.5,
        5.35,
        6.33,
        7.2,
        8.15,
        9.02,
        9.91
    };
    vector<double> B={
        8.7,
        62.91,
        121.42,
        178.03,
        227.96,
        279.88,
        336.7,
        392.8,
        439.8,
        491.4,
        529.5,
        567.4,
    };
    //
    //errori
    vector<double> err_corrente={
        0.12275,
        0.14625,
        0.17,
        0.19075,
        0.2125,
        0.23375,
        0.25825,
        0.28,
        0.30375,
        0.3255,
        0.34775,
    };
    vector<double> err_B={
      9.69248197270152,
        18.7070602626835,
        27.4289074169457,
        35.1215735256245,
        43.1208369817152,
        51.8750386299253,
        60.5183105845996,
        67.7595544681947,
        75.7095158382694,
        81.5795454545455,
        87.4187612670616,
     };

    //
    int len= corrente.size();
    TGraphErrors* gr1= new TGraphErrors(len, corrente.data(), B.data(), err_corrente.data(), err_B.data());
    //
    TCanvas* c1= new TCanvas("c1", "rampe calibrazione", 800, 600);

    TF1* fit= new TF1("fit", "[0]+[1]*x", 0, 10);



    gr1->Fit("fit", "R");
     gr1->GetXaxis()->SetTitle("corrente [A]");
    gr1->GetYaxis()->SetTitle("B [mT]");
     gr1->SetTitle("calibrazione magnete prima salita");
    gr1->Draw("AP.");
    c1->Print("prima_salita.png", "png");
    cout<<"il pvalue è "<< fit->GetProb() <<endl;



}