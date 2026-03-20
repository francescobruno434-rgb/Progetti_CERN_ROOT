#include<iostream>
#include "TH1D.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include<vector>
#include <cmath>
using namespace std;






//CURVA DI COINCIDENZA DEGLI SCINTILLATORI GRANDI




//definizione di funzioni che saranno utili
double err_rel_divisione(double err_num, double err_den){
    double err_quad= pow(err_num, 2)+ pow(err_den, 2);
    double err_rel= pow(err_quad, 0.5);
    return err_rel;
}
double EfficiencyFalling(double *x, double *par) {
  return par[0]/(1+exp((x[0] - par[1])/par[2]))+par[3];
}


double EfficiencyRising(double *x, double *par) {
  return par[0]/(1+exp((par[1] - x[0])/par[2]))+par[3];
}


























void LAB_nucl_coincidenza(){


    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++SCRIVERE SOLO IN QUESTA SEZIONE
    vector<double> ritardo={
      40,
        30,
        20,
        10,
        0,
        -10,
        -20,
        -30,
        -40,
        -35,
        -33,
        -32,
        -31,
        -28,
        -26,
        -26,
        35,
        33,
        32,
        31,
        28,
        26,
        7,
        -7,
        3,
        -3,
        15,
        -15

    };
    vector<double> conteggi={
                3,
        3864,
        1354,
        1368,
        1371,
        1337,
        1338,
        3177,
        2,
        47,
        357,
        684,
        1291,
        1206,
        1328,
        1311,
        252,
        1261,
        2431,
        2251,
        1991,
        2041,
        1311,
        1341,
        1319,
        1359,
        1443,
        1324,
    };
    vector<double> tempo_daq={
        300,
        300,
        100,
        100,
        100,
        100,
        100,
        300,
        300,
        200,
        200,
        200,
        200,
        100,
        100,
        100,
        300,
        300,
        300,
        200,
        150,
        150,
        100,
        100,
        100,
        100,
        100,
        100,
    };


    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++STOP NON SCRIVERE PIU'












    //ora in questa sezione mettiamo gli errori su queste grandezze
    vector<double> err_ritardo;
    vector<double> err_conteggi;
    vector<double> err_tempo_daq;


    //ora riempiamo   questi vettori di errori
    //
    int lunghezza= ritardo.size(); //grandezza di questi vettori
    cout<<"I tuoi vettori contengono "<< lunghezza<< "dati"<<endl;
    //
    //errore sui conteggi
    for (int i=0; i<lunghezza; i++){
       double error_conteggi= pow(conteggi[i], 0.5);
       err_conteggi.push_back(error_conteggi);
    }
    //
    //errore sul ritardo
    for(int i=0; i<lunghezza; i++){
        err_ritardo.push_back(0.5); //tutti gli errori sul ritardo posti a mezzo nanosecondo, la risoluzione  
    }
    //
    //errore sul tempo daq
    for (int i=0; i<lunghezza; i++){
        err_tempo_daq.push_back(0.001); //1ms di errore su tutti i tempi, risoluzione dello strumento
    }




    //ora costruiamo e riempiamo gli arrai con i rate misurati (le coincidenze)
    vector<double> R_mis;;
    vector<double> err_R_mis;
    //
    //riempimento del rate
    for(int i=0; i<lunghezza; i++){
        double R_misura= conteggi[i]/tempo_daq[i];
        R_mis.push_back(R_misura);
    }
    //
    //riempimento dell'errore sul rate
    for(int i=0; i<lunghezza; i++){
        double error_rel= err_rel_divisione(err_conteggi[i]/conteggi[i], err_tempo_daq[i]/tempo_daq[i]);
        double error_ass= error_rel * R_mis[i];
        err_R_mis.push_back(error_ass);
    }




    //
    //ora, creiamo il TGraph e il TCanvas
    TCanvas* c1= new TCanvas("c1", "curva di coincidenza", 800, 600);
    //
    TGraphErrors* gr1= new TGraphErrors(lunghezza, ritardo.data(), R_mis.data(), err_ritardo.data(), err_R_mis.data());
    //
    gr1->SetMarkerStyle(21);
    gr1->GetXaxis()->SetTitle("delay (ns)");
    gr1->GetYaxis()->SetTitle("Rate di coincidenze (Hz)");
    gr1->SetTitle("Curva di coincidenza");
    //
   
    gr1->GetYaxis()->SetRangeUser(0, 15);
    gr1->GetYaxis()->SetRangeUser(0, 15);


    //fit function: SALITA
     TF1* fit_coin= new TF1("fit_coin", EfficiencyRising, -40, 0, 4); //
     fit_coin->SetParameters(-13, -37, -0.7, 13);
     fit_coin->SetLineColor(7);
     cout<<"FIT SALITA (A SINISTRA)"<<endl;
     gr1->Fit("fit_coin", "R");
     cout<<"il p value e: "<<endl;
     cout<<fit_coin->GetProb()<<endl;
    
   
    //c1->Print("Grafico_coincidenze.png", "png");

    //FIT FUNCTION: DISCESA
    TF1* fit_discesa= new TF1("fit_discesa", EfficiencyFalling, 10, 40, 4);
    fit_discesa->SetParameters(13, 33, 0.2, 0.6);
    fit_discesa->SetLineColor(3);
    cout<<"FIT DISCESA (A DESTRA)"<<endl;
    gr1->Fit("fit_discesa", "R+");
    cout<<"il p value e: "<<endl;
     cout<<fit_discesa->GetProb()<<endl;


    //FIT DEL PLATEAU
    TF1* fit_plat= new TF1("fit_plat", "[0]", -25, 25);
    fit_plat->SetParameters(13.5);
    cout<<"FIT PLATEAU"<<endl;
    gr1->Fit("fit_plat", "R+");
    cout<<"il p value e: "<<endl;
     cout<<fit_plat->GetProb()<<endl;

    gr1->Draw("AP.");



}





