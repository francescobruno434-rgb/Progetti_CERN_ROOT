 #include<iostream>
#include "TGraphErrors.h"
#include "TCanvas.h"
#include<vector>
#include "TF1.h"

using namespace std;

//PRIMA SALITA

void calibrazione_magnete_seconda_discesa(){
    vector<double> corrente={
      9.63,
        9.11,
        8.01,
        7.17,
        6.47,
        5.52,
        4.61,
        3.72,
        2.67,
        1.69,
        0.91,
        0,
    };
    vector<double> B={
       
       554.5,
        537,
        484.9,
        444.7,
        399,
        348.6,
        292.6,
        243.8,
        176.7,
        120,
        65.4,
        8.9,
       
       
       
       
    };
    //
    //errori
    vector<double> err_corrente={
        0.34075,
        0.32775,
        0.30025,
        0.27925,
        0.26175,
        0.238,
        0.21525,
        0.193,
        0.16675,
        0.14225,
        0.12275,
        0.1,
    };
    vector<double> err_B={
        85.4312709245429,
        82.7350630955447,
        74.7080672160701,
        68.5144926603142,
        61.4735385011589,
        53.7084599536441,
        45.0805949008499,
        37.5620267834149,
        27.2239956219418,
        18.4882822559876,
        10.0761138295133,
        1.37121426731908,
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
     gr1->SetTitle("calibrazione magnete seconda discesa");
     gr1->SetMinimum(-10);
    gr1->Draw("AP.");
    c1->Print("seconda_discesa.png", "png");
    cout<<"il pvalue è "<< fit->GetProb() <<endl;



}