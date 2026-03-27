#include<iostream>
#include "TF1.h"
#include "TCanvas.h"
using namespace std;



void grafico_coeff_att(){

TF1* fit= new TF1("fit", " [0]*exp(-[1]*x)", 0, 5);
fit->FixParameter(0, 0.45);
fit->FixParameter(1, 0.15);

TCanvas* c1= new TCanvas("c1", "grafico", 800, 600);
fit->Draw();




















}