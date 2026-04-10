#include<iostream>
#include "TCanvas.h"
#include "TGraph.h"
#include "TF1.h"
using namespace std;


void grafici_massa(){

TF1* csi_gr= new TF1("csi_gr", "gaus(0)+ pol3(3)", 1.3, 1.35);

csi_gr->FixParameter(0, 350);
csi_gr->FixParameter(1, 1.32171);
csi_gr->FixParameter(2, 0.003);
csi_gr->FixParameter(3, 20750);
csi_gr->FixParameter(4, -2671);
csi_gr->FixParameter(5, -2280);
csi_gr->FixParameter(6, -3400);


TF1* csi_gr2= new TF1("csi_gr", "gaus(0)+ [3]*exp(-[4]*x)", 1.3, 1.35);
csi_gr2->FixParameter(0, 350);
csi_gr2->FixParameter(1, 1.32171);
csi_gr2->FixParameter(2, 0.003);
csi_gr2->FixParameter(3, 5);
csi_gr2->FixParameter(4, 6);


TCanvas* c1= new TCanvas("c1", "prova fit masse csi", 1800, 400);
csi_gr->Draw();
///csi_gr2->Draw();






















}
