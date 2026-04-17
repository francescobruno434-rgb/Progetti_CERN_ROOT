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
        0.1,
        0.34825,
        0.324,
        0.30275,
        0.28175,
        0.25825,
        0.236,
        0.215,
        0.18975,
        0.1675,
        0.143,
        0.1235,
    };
    vector<double> err_B={
        1.35580736543909,
        87.1722508369817,
        81.6103592583055,
        75.1702742724698,
        67.9444372907546,
        60.8264486221994,
        52.9381148596446,
        45.2038501158898,
        35.7748261653361,
        27.8094578933814,
        18.4112477465877,
        10.9080865310327,
            };

    //
    int len= corrente.size();
    TGraphErrors* gr1= new TGraphErrors(len, corrente.data(), B.data(), err_corrente.data(), err_B.data());
    //
    TCanvas* c1= new TCanvas("c1", "rampe calibrazione", 800, 600);

    TF1* fit= new TF1("fit", "[0]+[1]*x", 0, 10);


   // gr1->SetMarkerStyle(20);
   gr1->Fit("fit", "R");
    gr1->SetMinimum(-10);
    gr1->GetXaxis()->SetTitle("corrente [A]");
    gr1->GetYaxis()->SetTitle("B [mT]");
     gr1->SetTitle("calibrazione magnete prima discesa");
    gr1->Draw("AP.");
    c1->Print("prima_discesa.png", "png");
    cout<<"il pvalue è "<< fit->GetProb() <<endl;



}