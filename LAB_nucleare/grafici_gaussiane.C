#include<iostream>
#include "TF1.h"
#include "TCanvas.h"
using namespace std;


void grafici_gaussiane(){


TF1* gauss1= new TF1("gauss1", "gaus(0)+gaus(3)", 60, 300 );
gauss1->FixParameter(0, 400);
gauss1->FixParameter(1, 195);
gauss1->FixParameter(2, 5);
gauss1->FixParameter(3, 200);
gauss1->FixParameter(4, 200);
gauss1->FixParameter(5, 5);

TCanvas* c1= new TCanvas("c1", "gaussiane", 800, 600);
gauss1->Draw();
















}