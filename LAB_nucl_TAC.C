#include<iostream>
#include<fstream>
#include<vector>
#include "TH1D.h"
#include "TF1.h"
#include "TCanvas.h"
#include<istream>
using namespace std;



void LAB_nucl_TAC(){


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
    while(gabibbo.eof()!=1 & i<512){
        istream& ignore(">");
        //mi salta fino al sesto simbolo > che segna l'inizio del file
        gabibbo>> value_bin;
        hist->SetBinContent(i, value_bin);
        i++;

    }
    
    hist->Draw("E");
    



















}