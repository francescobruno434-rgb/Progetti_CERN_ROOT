#include<iostream>
#include "TF1.h"
#include "TCanvas.h"
using namespace std;


void grafici_gaussiane(){


TF1* gauss1= new TF1("gauss1", "gaus(0)+gaus(3)", 100, 400 );
gauss1->FixParameter(0, 90);
gauss1->FixParameter(1, 230);
gauss1->FixParameter(2, 19);
gauss1->FixParameter(3, 70);
gauss1->FixParameter(4, 280);
gauss1->FixParameter(5, 18);
/*gauss1->FixParameter(6, 100);
gauss1->FixParameter(7, 210);
gauss1->FixParameter(8, 10);*/

TCanvas* c1= new TCanvas("c1", "gaussiane", 800, 600);
gauss1->Draw();
















}