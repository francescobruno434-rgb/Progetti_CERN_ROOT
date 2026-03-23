#include<iostream>
#include<fstream>
#include<vector>
#include "TH1D.h"
#include "TF1.h"
#include "TCanvas.h"
#include<istream>
using namespace std;



void LAB_nucl_TAC(){
    char skip_line[3000]; //array spazzatura vuoto, dove ficcheremo le linee da schippare


    TCanvas* c1= new TCanvas("c1", "gabibbo", 800, 600);
    TH1D* hist= new TH1D("hist", "gabibbi", 512, 0, 512);
    //apro il file, che ora si chiama gabibbo;
    fstream gabibbo("161_5_cent.mca", fstream::in);
    if (gabibbo.is_open()){
        cout<<"il file è cprrettamente aperto e gabibbo è contento"<<endl;
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
        hist->SetBinContent(i, value_bin);
        i++;
        //cout<<"bin aggiunto: "<<i<<endl;
        //cout<<"valore inserito "<<value_bin<<endl;
        }

    }
    TF1* fit= new TF1("fit", "gaus(0)" ); //i parametri della gaussiana sono ampiezza, media e stdv (in ordine)
    fit->SetParameters(23, 250, 50 );
    hist->Fit("fit");
    cout<<"il p-value è :"<<endl;
    cout<<fit->GetProb()<<endl;
    hist->Draw();
    c1->Print("hist_TAC_161_5.png", "png");
    



















}