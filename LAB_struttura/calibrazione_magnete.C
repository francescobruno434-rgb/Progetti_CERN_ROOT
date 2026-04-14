#include<iostream>
#include "TGraphErrors.h"
#include "TCanvas.h"
#include<vector>

using namespace std;

void calibrazione_magnete(){
    vector<double> corrente={};
    vector<double> B={};
    //
    //errori
    vector<double> err_corrente={};
    vector<double> err_B={};

    //
    int len= corrente.size();
    TGraphErrors* gr1= new TGraphErrors(len, corrente, B, err_corrente, err_B);
    //
    TCanvas* c1= new TCanvas("c1", "rampe calibrazione", 800, 600);

    gr1->Draw();




}