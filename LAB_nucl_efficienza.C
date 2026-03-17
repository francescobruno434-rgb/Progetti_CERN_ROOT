#include<iostream>
#include "TGraphErrors.h"
#include "TH1D.h"
#include "TF1.h"
#include<vector>
#include<cmath>
#include "TCanvas.h"
using namespace std;


//Obiettivo è il calcolo dell'efficienza dei nostri rivelatori; è la prima parte che richiede una serie analisi dati


void LAB_nucl_efficienza(){
    //
    //SCRIVERE QUA**********************************************************************************************************************
    //creo gli array con i dati (copia-incollali tra le parentesi graffe)
    vector<double> HV={2193, 2143, 2093, 2043, 2000, 1950, 2025, 2075, 2125, 2175, 2225, 2250, 2300, 2350, 2393}; //alta tensione
    //
    vector<double> coin_doppie={252, 244, 250, 276, 256, 260, 275, 271, 271, 245, 261, 252, 266, 258, 248};
    //
    vector<double> coin_triple= {238, 113, 30, 3, 1, 0, 1, 13, 72, 164, 248, 243, 259, 249, 245};
    //
    vector<double> coin_singole= {2933, 938, 236, 15, 6, 0, 11, 110, 472, 1509, 3461, 4951, 8427, 12954, 17980};
    //
    double tempo_daq=100; //intervallo di tempo dell'acquisizione dati
    //
    double err_tempo=0.001; //errore sul tempo di data acquisition
    //
    double err_rel_tempo= err_tempo/tempo_daq; //errore relativo sul tempo di data acquisition
    //
    //STOP SCRITTURA (NON SCRIVERE IN QUESTI ARRAY QUA SOTTO!!!!)**************************************************************************
    //qui scriviamo gli array con i rate
    //
    vector<double> R_doppie;
    //
    vector<double> R_triple;
    //
    vector<double> R_singole;
    //
    //RIEMPIMENTO ARRAY RATE
    //R_doppie
    for(vector<double>::const_iterator it= coin_doppie.begin(); it!= coin_doppie.end(); it++){
        double misura= *it/tempo_daq;
        R_doppie.push_back(misura);
    }
    //R_triple
    for(vector<double>::const_iterator it= coin_triple.begin(); it!= coin_triple.end(); it++){
        double misura= *it/tempo_daq;
        R_triple.push_back(misura);
    }
    //R_singole
    for(vector<double>::const_iterator it= coin_singole.begin(); it!= coin_singole.end(); it++){
        double misura= *it/tempo_daq;
        R_singole.push_back(misura);
    }
    //
    //Ora ARRAY CON GLI ERRORI
    vector<double> err_HV;  //cfr manuale
    //
    vector<double> err_coin_doppie={};
    //
    vector<double> err_coin_triple= {};
    //
    vector<double> err_coin_singole= {};
    //
    vector<double> err_R_doppie={};
    //
    vector<double> err_R_triple;
    //
    vector<double> err_R_singole;
    //
    //
    //RIEMPIMENTO ERRORI
    //
    //Riempimento errori su HV
    for(vector<double>::const_iterator it= HV.begin(); it!= HV.end(); it++){
        double x= *it;
        double err= x/100 + 5; //(errore dell'1% + 5 V da manuale)
        err_HV.push_back(err);
    }
    //
    //riempimento errori su coin_doppie
    for(vector<double>::const_iterator it= coin_doppie.begin(); it!= coin_doppie.end(); it++){
        double x= *it;
        double err= pow(x, 0.5); 
        err_HV.push_back(err);
    }
    //
    //riempimento errori su coin_triple
    for(vector<double>::const_iterator it= coin_triple.begin(); it!= coin_triple.end(); it++){
        double x= *it;
        double err= pow(x, 0.5); 
        err_HV.push_back(err);
    }
    //
    //riempimento errori su coin_singole
    for(vector<double>::const_iterator it= coin_singole.begin(); it!= coin_singole.end(); it++){
        double x= *it;
        double err= pow(x, 0.5);
        err_HV.push_back(err);
    }
    //
    //non usiamo più i const iterator, perchè tanto il numero di elementi è determinato dalla lunghezza di HV
    int numero_elementi= HV.size();
    //
    //riempimento errori su R_doppie
    for(int i=0; i<numero_elementi; i++){
        double err_rel_coin= err_coin_doppie[i]/coin_doppie[i]; //errore relativo coincidenze doppie
        double err_rel_rate_quad= pow(err_rel_coin,2)+ pow(err_rel_tempo, 2); //errore relativo sul rate
        double err_rel_rate= pow(err_rel_rate_quad, 0.5);
        double err_ass_rate= err_rel_rate* R_doppie[i];
        err_R_doppie.push_back(err_ass_rate);
    }
    //
    //riempimento errori su R_triple
    for(int i=0; i<numero_elementi; i++){
        double  err_rel_coin= err_coin_triple[i]/coin_triple[i]; //errore relativo coincidenze triple
        double err_rel_rate_quad= pow(err_rel_coin,2)+ pow(err_rel_tempo, 2); //errore relativo sul rate
        double err_rel_rate= pow(err_rel_rate_quad, 0.5);
        double err_ass_rate= err_rel_rate* R_triple[i];
        err_R_triple.push_back(err_ass_rate);
    }
    //
    //riempimento errori su R_singole
    for(int i=0; i<numero_elementi; i++){
        double err_rel_coin= err_coin_singole[i]/coin_singole[i]; //errore relativo coincidenze singole
        double err_rel_rate_quad= pow(err_rel_coin,2)+ pow(err_rel_tempo, 2); //errore relativo sul rate
        double err_rel_rate= pow(err_rel_rate_quad, 0.5);
        double err_ass_rate= err_rel_rate* R_singole[i];
        err_R_singole.push_back(err_ass_rate);
    }
    //
    //++++++++++++++++++++++++++++++++++++++
    //CALCOLO DELL'EFFICIENZA
    //
    vector<double> eff={};
    vector<double> err_eff={};

    //
    //calcolo efficienza (valore)
    for(int i=0; i<numero_elementi; i++){
        double my_doppia_coin= R_doppie[i];
        double my_tripla_coin= R_triple[i];
        double my_eff= my_tripla_coin/my_doppia_coin;
        eff.push_back(my_eff);
    }
    //
    //calcolo errore sull'efficienza
    for(int i=0; i<numero_elementi; i++){
        double varianza= (eff[i]*(1-eff[i]))/coin_doppie[i];
        double err_ass= pow(varianza, 0.5);
        err_eff.push_back(err_ass);
    }
    //
    //+++++++++++++++++++++++++++++++++++++++++++++++++++GRAFICI+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //
    //EFFICIENZA-TENSIONE
    TCanvas* c1= new TCanvas("c1", "\nepsilon - tensione", 800, 600);
    //
    TGraphErrors* gr1= new TGraphErrors(numero_elementi,HV.data(), eff.data(), err_HV.data(), err_eff.data());
    //
    gr1->Draw("AP");

}




