#include<iostream>
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include<vector>
using namespace std;


double EfficiencyFalling(double *x, double *par) {
  return par[0]/(1+exp((x[0] - par[1])/par[2]));
}

double EfficiencyRising(double *x, double *par) {
  return par[0]/(1+exp((par[1] - x[0])/par[2]));
}

//2225 V
void LAB_nucl_V_thr(){
vector<double> V_thr={50,
    151,
    249.8,
    349.5,
    450.6,
    500.8,
    100
};
//
vector<double> eff={0.976833976833977,
    0.74,
    0.408088235294118,
    0.181451612903226,
    0.0889830508474576,
    0.0461538461538462,
    0.950191570881226,

};
//
vector<double> err_V={0.55,
    0.651,
    0.7498,
    0.8495,
    0.9506,
    1.0008,
    0.6
};
//
vector<double> err_eff={0.086346670297987,
    0.0717662873499807,
    0.0459629103622591,
    0.0294010300406849,
    0.0202632080994414,
    0.0136274643034175,
    0.0842604881031613
};
//
//
TCanvas* c1= new TCanvas("c1", "gabibbo", 800, 600);

TGraphErrors* gr1= new TGraphErrors(eff.size(), V_thr.data(), eff.data(), err_V.data(), err_eff.data());
gr1->GetYaxis()->SetRangeUser(0, 1.2);


TF1* fit= new TF1("fit",  EfficiencyFalling, 0, 600, 3 );
fit->SetParameters(1, 0.9, 40);

gr1->Fit("fit", "R");
gr1->GetXaxis()->SetTitle("V_{thr} (mV)");
  gr1->GetYaxis()->SetTitle("efficienza");
gr1->SetTitle("Grafico efficienza-tensione di soglia a 2225 HV (scintillatore B)");
cout<<"il p value è"<<endl;
double p= fit->GetProb();
cout<<p<<endl;



gr1->Draw("AP.");
c1->Print("eff_Vthr.png", "png");









}