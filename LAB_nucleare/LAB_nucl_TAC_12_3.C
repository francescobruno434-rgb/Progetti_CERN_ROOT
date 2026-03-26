#include<iostream>
#include<fstream>
#include<vector>
#include "TH1D.h"
#include "TF1.h"
#include "TCanvas.h"
#include<istream>
using namespace std;



void LAB_nucl_TAC_12_3(){
    char skip_line[3000]; //array spazzatura vuoto, dove ficcheremo le linee da schippare


    TCanvas* c1= new TCanvas("c1", "TCA con 12 cm di distanza", 800, 600);
    TH1D* hist= new TH1D("hist", "gabibbi", 512, 0, 512);
    //apro il file, che ora si chiama gabibbo;
    fstream gabibbo("12_cent.mca", fstream::in);
    if (gabibbo.is_open()){
        cout<<"il file è correttamente aperto e gabibbo è contento"<<endl;
    }
    else {
        cout<<"FERMATI!! IL FILE NON E' APERTO!! SEI PROPRIO UN GABIBBO"<<endl;
    }
    int i=0;
    double value_bin=0;
    while(gabibbo.eof()!=1 & i<526){
        if(i<14){
            gabibbo.getline(skip_line, 3000);
            i++;
        }
        else{
        gabibbo>> value_bin;
        hist->SetBinContent(i-15, value_bin);
        i++;
    
        //cout<<"bin aggiunto: "<<i<<endl;
        //cout<<"valore inserito "<<value_bin<<endl;
        }

    }
    TF1* fit= new TF1("fit", "gaus(0)+gaus(3)+gaus(6)+gaus(9)", 100, 280 ); //i parametri della gaussiana sono ampiezza, media e stdv (in ordine)
    fit->SetParameters(400, 190, 25, 100, 200, 20, 100, 210, 20, 100);
    fit->SetParameter(10, 220);
    fit->SetParameter(11, 10);
   fit->SetParNames("A1", "mu1", "sigma 1", "A2", "mu2", "sigma 2", "A3", "mu 3", "sigma 3", "A4");
   fit->SetParName(10, "mu4");
   fit->SetParName(11, "sigma4");
   //, "A3", "mu 3", "sigma 3"
   fit->SetParLimits(3, 200, 600);
   //fit->SetParLimits(1, 180, 200);
    hist->Rebin(5);
    hist->Fit("fit", "R");
    cout<<"il p-value è :"<<endl;
    cout<<fit->GetProb()<<endl;
    hist->Draw("");

    



















}