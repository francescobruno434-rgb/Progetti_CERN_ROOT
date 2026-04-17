 #include<iostream>
#include "TGraphErrors.h"
#include "TCanvas.h"
#include<vector>
#include "TF1.h"

using namespace std;

//PRIMA SALITA

void calibrazione_magnete_seconda_salita(){
    vector<double> corrente={
        0,
        0.85,
        1.86,
        2.76,
        3.46,
        4.55,
        5.3,
        6.5,
        7.46,
        8.2,
        9.09,
        9.88,
    };
    vector<double> B={
       8.7,
        61.2,
        121.7,
        176.8,
        221,
        285.5,
        334.5,
        399.3,
        454.3,
        494.5,
        532.4,
        564.9,
    };
    //
    //errori
    vector<double> err_corrente={
      0.1,
        0.12125,
        0.1465,
        0.169,
        0.1865,
        0.21375,
        0.2325,
        0.2625,
        0.2865,
        0.305,
        0.32725,
        0.347,  
    };
    vector<double> err_B={
      1.3404004635591,
        9.4290239505537,
        18.7501995879475,
        27.2394025238218,
        34.0492531547773,
        43.9867048673706,
        51.5360867885656,
        61.5197592067989,
        69.9935552407932,
        76.1871297965491,
        82.0263456090652,
        87.0335887200618,
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
     gr1->SetTitle("calibrazione magnete seconda salita");
     gr1->SetMinimum(-10);
    gr1->Draw("AP.");
    c1->Print("seconda_salita.png", "png");
    cout<<"il pvalue è "<< fit->GetProb() <<endl;



}